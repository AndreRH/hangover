/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#define COBJMACROS

#include <windows.h>
#include <stdio.h>
#include <dsound.h>
#include <dsconf.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dsound.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);

struct qemu_dsound
{
    /* Guest fields */
    IUnknown            IUnknown_inner;
    IDirectSound8       IDirectSound8_iface;
    IUnknown            *outer_unk;
    LONG                ref, refds, numIfaces;
    BOOL                has_ds8;

    /* Host fields */
    IDirectSound8       *host;
};

struct qemu_IDirectSound8Impl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dsound *impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound, IUnknown_inner);
}

static void directsound_destroy(struct qemu_dsound *dsound)
{
    struct qemu_IDirectSound8Impl_Release call;

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_RELEASE);
    call.iface = (ULONG_PTR)dsound;

    qemu_syscall(&call.super);
}

/* Inner IUnknown for (internal) aggregation. Implemented on the guest side and copypasted
 * from Wine with style adjustments. */
static HRESULT WINAPI IUnknownImpl_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    struct qemu_dsound *dsound = impl_from_IUnknown(iface);

    WINE_TRACE("(%p,%s,%p)\n", dsound, wine_dbgstr_guid(riid), out);

    if (!out)
    {
        WINE_WARN("invalid parameter\n");
        return E_INVALIDARG;
    }
    *out = NULL;

    if (IsEqualIID(riid, &IID_IUnknown))
    {
        *out = &dsound->IUnknown_inner;
    }
    else if (IsEqualIID(riid, &IID_IDirectSound) ||
            (IsEqualIID(riid, &IID_IDirectSound8) && dsound->has_ds8))
    {
        *out = &dsound->IDirectSound8_iface;
    }
    else
    {
        WINE_WARN("unknown IID %s\n", wine_dbgstr_guid(riid));
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*out);
    return S_OK;
}

static ULONG WINAPI IUnknownImpl_AddRef(IUnknown *iface)
{
    struct qemu_dsound *dsound = impl_from_IUnknown(iface);
    ULONG ref = InterlockedIncrement(&dsound->ref);

    WINE_TRACE("(%p) ref=%u\n", dsound, ref);

    if(ref == 1)
        InterlockedIncrement(&dsound->numIfaces);

    return ref;
}

static ULONG WINAPI IUnknownImpl_Release(IUnknown *iface)
{
    struct qemu_dsound *dsound = impl_from_IUnknown(iface);
    ULONG ref = InterlockedDecrement(&dsound->ref);

    WINE_TRACE("(%p) ref=%u\n", dsound, ref);

    if (!ref && !InterlockedDecrement(&dsound->numIfaces))
        directsound_destroy(dsound);

    return ref;
}

static const IUnknownVtbl unk_vtbl =
{
    IUnknownImpl_QueryInterface,
    IUnknownImpl_AddRef,
    IUnknownImpl_Release
};

#endif

struct qemu_IDirectSound8Impl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dsound *impl_from_IDirectSound8(IDirectSound8 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound, IDirectSound8_iface);
}

/* IUnknown methods, purely implemented in the guest, except for Release, which obviously
 * needs a host callback for the final destroy. */
static HRESULT WINAPI IDirectSound8Impl_QueryInterface(IDirectSound8 *iface, REFIID riid, void **out)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    WINE_TRACE("(%p,%s,%p)\n", dsound, wine_dbgstr_guid(riid), out);
    return IUnknown_QueryInterface(dsound->outer_unk, riid, out);
}

static ULONG WINAPI IDirectSound8Impl_AddRef(IDirectSound8 *iface)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    ULONG ref = InterlockedIncrement(&dsound->refds);

    WINE_TRACE("(%p) refds=%u\n", dsound, ref);

    if(ref == 1)
        InterlockedIncrement(&dsound->numIfaces);

    return ref;
}

static ULONG WINAPI IDirectSound8Impl_Release(IDirectSound8 *iface)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    ULONG ref = InterlockedDecrement(&(dsound->refds));

    WINE_TRACE("(%p) refds=%u\n", dsound, ref);

    if (!ref && !InterlockedDecrement(&dsound->numIfaces))
        directsound_destroy(dsound);

    return ref;
}

#else

void qemu_IDirectSound8Impl_Release(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_Release *c = (struct qemu_IDirectSound8Impl_Release *)call;
    struct qemu_dsound *dsound;
    WINE_TRACE("\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_Release(dsound->host);
    if (c->super.iret)
        WINE_ERR("Expected to release the only reference held on the host inteface.\n");
}

#endif

struct qemu_IDirectSound8Impl_CreateSoundBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dsbd;
    uint64_t ppdsb;
    uint64_t lpunk;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_CreateSoundBuffer(IDirectSound8 *iface, const DSBUFFERDESC *dsbd, IDirectSoundBuffer **ppdsb, IUnknown *lpunk)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_CreateSoundBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_CREATESOUNDBUFFER);
    call.iface = (ULONG_PTR)dsound;
    call.dsbd = (ULONG_PTR)dsbd;
    call.ppdsb = (ULONG_PTR)ppdsb;
    call.lpunk = (ULONG_PTR)lpunk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_CreateSoundBuffer(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_CreateSoundBuffer *c = (struct qemu_IDirectSound8Impl_CreateSoundBuffer *)call;
    struct qemu_dsound *dsound;
    WINE_TRACE("\n");

    /* FIXME: DSBUFFERDESC will need conversion, WAVEFORMATEX should be fine. */
    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_CreateSoundBuffer(dsound->host, QEMU_G2H(c->dsbd), QEMU_G2H(c->ppdsb), QEMU_G2H(c->lpunk));
}

#endif

struct qemu_IDirectSound8Impl_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dscaps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_GetCaps(IDirectSound8 *iface, DSCAPS *dscaps)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_GETCAPS);
    call.iface = (ULONG_PTR)dsound;
    call.dscaps = (ULONG_PTR)dscaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_GetCaps(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_GetCaps *c = (struct qemu_IDirectSound8Impl_GetCaps *)call;
    struct qemu_dsound *dsound;
    WINE_FIXME("Unverified!\n");

    /* DSCAPS is the same in 32 and 64 bit. */
    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_GetCaps(dsound->host, QEMU_G2H(c->dscaps));
}

#endif

struct qemu_IDirectSound8Impl_DuplicateSoundBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t psb;
    uint64_t ppdsb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_DuplicateSoundBuffer(IDirectSound8 *iface, IDirectSoundBuffer *psb, IDirectSoundBuffer **ppdsb)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_DuplicateSoundBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_DUPLICATESOUNDBUFFER);
    call.iface = (ULONG_PTR)dsound;
    call.psb = (ULONG_PTR)psb;
    call.ppdsb = (ULONG_PTR)ppdsb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_DuplicateSoundBuffer(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_DuplicateSoundBuffer *c = (struct qemu_IDirectSound8Impl_DuplicateSoundBuffer *)call;
    struct qemu_dsound *dsound;
    WINE_FIXME("Unverified!\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_DuplicateSoundBuffer(dsound->host, QEMU_G2H(c->psb), QEMU_G2H(c->ppdsb));
}

#endif

struct qemu_IDirectSound8Impl_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwnd;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_SetCooperativeLevel(IDirectSound8 *iface, HWND hwnd, DWORD level)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_SetCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)dsound;
    call.hwnd = (ULONG_PTR)hwnd;
    call.level = level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_SetCooperativeLevel *c = (struct qemu_IDirectSound8Impl_SetCooperativeLevel *)call;
    struct qemu_dsound *dsound;
    WINE_TRACE("\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_SetCooperativeLevel(dsound->host, QEMU_G2H(c->hwnd), c->level);
}

#endif

struct qemu_IDirectSound8Impl_Compact
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_Compact(IDirectSound8 *iface)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_Compact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_COMPACT);
    call.iface = (ULONG_PTR)dsound;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_Compact(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_Compact *c = (struct qemu_IDirectSound8Impl_Compact *)call;
    struct qemu_dsound *dsound;
    WINE_FIXME("Unverified!\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_Compact(dsound->host);
}

#endif

struct qemu_IDirectSound8Impl_GetSpeakerConfig
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t config;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_GetSpeakerConfig(IDirectSound8 *iface, DWORD *config)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_GetSpeakerConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_GETSPEAKERCONFIG);
    call.iface = (ULONG_PTR)dsound;
    call.config = (ULONG_PTR)config;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_GetSpeakerConfig(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_GetSpeakerConfig *c = (struct qemu_IDirectSound8Impl_GetSpeakerConfig *)call;
    struct qemu_dsound *dsound;
    WINE_FIXME("Unverified!\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_GetSpeakerConfig(dsound->host, QEMU_G2H(c->config));
}

#endif

struct qemu_IDirectSound8Impl_SetSpeakerConfig
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t config;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_SetSpeakerConfig(IDirectSound8 *iface, DWORD config)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_SetSpeakerConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_SETSPEAKERCONFIG);
    call.iface = (ULONG_PTR)dsound;
    call.config = config;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_SetSpeakerConfig(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_SetSpeakerConfig *c = (struct qemu_IDirectSound8Impl_SetSpeakerConfig *)call;
    struct qemu_dsound *dsound;
    WINE_FIXME("Unverified!\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_SetSpeakerConfig(dsound->host, c->config);
}

#endif

struct qemu_IDirectSound8Impl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpcGuid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_Initialize(IDirectSound8 *iface, const GUID *lpcGuid)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_INITIALIZE);
    call.iface = (ULONG_PTR)dsound;
    call.lpcGuid = (ULONG_PTR)lpcGuid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_Initialize *c = (struct qemu_IDirectSound8Impl_Initialize *)call;
    struct qemu_dsound *dsound;
    WINE_TRACE("\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_Initialize(dsound->host, QEMU_G2H(c->lpcGuid));
}

#endif

struct qemu_IDirectSound8Impl_VerifyCertification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t certified;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound8Impl_VerifyCertification(IDirectSound8 *iface, DWORD *certified)
{
    struct qemu_dsound *dsound = impl_from_IDirectSound8(iface);
    struct qemu_IDirectSound8Impl_VerifyCertification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND8IMPL_VERIFYCERTIFICATION);
    call.iface = (ULONG_PTR)dsound;
    call.certified = (ULONG_PTR)certified;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound8Impl_VerifyCertification(struct qemu_syscall *call)
{
    struct qemu_IDirectSound8Impl_VerifyCertification *c = (struct qemu_IDirectSound8Impl_VerifyCertification *)call;
    struct qemu_dsound *dsound;
    WINE_FIXME("Unverified!\n");

    dsound = QEMU_G2H(c->iface);
    c->super.iret = IDirectSound8_VerifyCertification(dsound->host, QEMU_G2H(c->certified));
}

#endif

struct qemu_DirectSoundCreate
{
    struct qemu_syscall super;
    uint64_t has_ds8;
    uint64_t dsound;
};

#ifdef QEMU_DLL_GUEST

static const IDirectSound8Vtbl ds8_vtbl =
{
    IDirectSound8Impl_QueryInterface,
    IDirectSound8Impl_AddRef,
    IDirectSound8Impl_Release,
    IDirectSound8Impl_CreateSoundBuffer,
    IDirectSound8Impl_GetCaps,
    IDirectSound8Impl_DuplicateSoundBuffer,
    IDirectSound8Impl_SetCooperativeLevel,
    IDirectSound8Impl_Compact,
    IDirectSound8Impl_GetSpeakerConfig,
    IDirectSound8Impl_SetSpeakerConfig,
    IDirectSound8Impl_Initialize,
    IDirectSound8Impl_VerifyCertification
};

static HRESULT IDirectSoundImpl_Create(IUnknown *outer, REFIID riid, void **out, BOOL has_ds8)
{
    struct qemu_DirectSoundCreate call;
    struct qemu_dsound *dsound;
    HRESULT hr;
    WINE_TRACE("(%s, %p)\n", wine_dbgstr_guid(riid), out);

    *out = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDCREATE);
    call.has_ds8 = has_ds8;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    dsound = (struct qemu_dsound *)(ULONG_PTR)call.dsound;

    dsound->IUnknown_inner.lpVtbl = &unk_vtbl;
    dsound->IDirectSound8_iface.lpVtbl = &ds8_vtbl;
    dsound->ref = 1;
    dsound->refds = 0;
    dsound->numIfaces = 1;
    dsound->has_ds8 = has_ds8;

    /* COM aggregation supported only internally */
    if (outer)
        dsound->outer_unk = outer;
    else
        dsound->outer_unk = &dsound->IUnknown_inner;

    hr = IUnknown_QueryInterface(&dsound->IUnknown_inner, riid, out);
    IUnknown_Release(&dsound->IUnknown_inner);

    return hr;
}

HRESULT DSOUND_Create(REFIID riid, void **ppv)
{
    return IDirectSoundImpl_Create(NULL, riid, ppv, FALSE);
}

HRESULT DSOUND_Create8(REFIID riid, void **ppv)
{
    return IDirectSoundImpl_Create(NULL, riid, ppv, TRUE);
}

WINBASEAPI HRESULT WINAPI DirectSoundCreate(const GUID *guid, IDirectSound **ds, IUnknown *outer)
{
    HRESULT hr;
    IDirectSound *obj;

    WINE_TRACE("(%s,%p,%p)\n", wine_dbgstr_guid(guid), ds, outer);

    if (!ds)
    {
        WINE_WARN("invalid parameter: ds == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (outer)
    {
        WINE_WARN("invalid parameter: outer != NULL\n");
        *ds = NULL;
        return DSERR_INVALIDPARAM;
    }

    hr = DSOUND_Create(&IID_IDirectSound, (void **)&obj);
    if (hr == DS_OK)
    {
        hr = IDirectSound_Initialize(obj, guid);
        if (hr != DS_OK)
        {
            if (hr != DSERR_ALREADYINITIALIZED)
            {
                IDirectSound_Release(obj);
                obj = 0;
            }
            else
            {
                hr = DS_OK;
            }
        }
    }

    *ds = obj;

    return hr;
}

WINBASEAPI HRESULT WINAPI DirectSoundCreate8(const GUID *guid, IDirectSound8 **ds, IUnknown *outer)
{
    HRESULT hr;
    IDirectSound8 *obj;

    WINE_TRACE("(%s,%p,%p)\n", wine_dbgstr_guid(guid), ds, outer);

    if (!ds)
    {
        WINE_WARN("invalid parameter: ds == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (outer)
    {
        WINE_WARN("invalid parameter: outer != NULL\n");
        *ds = NULL;
        return DSERR_INVALIDPARAM;
    }

    hr = DSOUND_Create8(&IID_IDirectSound8, (void **)&obj);
    if (hr == DS_OK)
    {
        hr = IDirectSound8_Initialize(obj, guid);
        if (hr != DS_OK)
        {
            if (hr != DSERR_ALREADYINITIALIZED)
            {
                IDirectSound8_Release(obj);
                obj = 0;
            }
            else
            {
                hr = DS_OK;
            }
        }
    }

    WINE_TRACE("Returning dsound interface %p\n", obj);
    *ds = obj;

    return hr;
}


#else

void qemu_DirectSoundCreate(struct qemu_syscall *call)
{
    struct qemu_DirectSoundCreate *c = (struct qemu_DirectSoundCreate *)call;
    struct qemu_dsound *dsound;
    HRESULT hr;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *factory;
    WINE_TRACE("\n");

    c->dsound = 0;

    /* Because we copypasted the init code from Wine we'll call Initialize with the
     * desired device GUID later. Don't call DirectSoundCreate here and instead use
     * CoCreateInstance to create an uninitialized object. We also need to be able
     * to create uninitialized devices if the guest calls us through CoCreateInstance.
     *
     * Except that we can't use CoCreateInstance because the host-side ole32 is
     * probably not initialized. So navigate out way through DllGetClassObject like
     * ole32 would. */
    lib = GetModuleHandleA("dsound");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(c->has_ds8 ? &CLSID_DirectSound8 : &CLSID_DirectSound,
            &IID_IClassFactory, (void *)&factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    dsound = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*dsound));
    if (!dsound)
    {
        WINE_WARN("Out of memory.\n");
        c->super.iret = DSERR_OUTOFMEMORY;
        IClassFactory_Release(factory);
        return;
    }

    hr = IClassFactory_CreateInstance(factory, NULL,
            c->has_ds8 ? &IID_IDirectSound8 : &IID_IDirectSound, (void **)&dsound->host);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IDirectSound%s object.\n", c->has_ds8 ? "8" : "");
        HeapFree(GetProcessHeap(), 0, dsound);
        dsound = NULL;
    }

    c->dsound = QEMU_H2G(dsound);
    c->super.iret = hr;
    IClassFactory_Release(factory);
}

#endif
