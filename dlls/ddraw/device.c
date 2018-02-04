/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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
#include <ddraw.h>
#include <d3d.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_ddraw.h"
#include "thunk/qemu_d3d.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_d3d_device_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_device *impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_device, IUnknown_inner);
}

static inline struct qemu_device *impl_from_IDirect3DDevice(IDirect3DDevice *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice_iface);
}

static inline struct qemu_device *impl_from_IDirect3DDevice2(IDirect3DDevice2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice2_iface);
}

static inline struct qemu_device *impl_from_IDirect3DDevice3(IDirect3DDevice3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice3_iface);
}

static inline struct qemu_device *impl_from_IDirect3DDevice7(IDirect3DDevice7 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice7_iface);
}

static HRESULT WINAPI d3d_device_inner_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    struct qemu_device *device = impl_from_IUnknown(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (!riid)
    {
        *out = NULL;
        return DDERR_INVALIDPARAMS;
    }

    if (IsEqualGUID(&IID_IUnknown, riid))
    {
        IDirect3DDevice7_AddRef(&device->IDirect3DDevice7_iface);
        *out = &device->IDirect3DDevice7_iface;
        return S_OK;
    }

    if (device->version == 7)
    {
        if (IsEqualGUID(&IID_IDirect3DDevice7, riid))
        {
            IDirect3DDevice7_AddRef(&device->IDirect3DDevice7_iface);
            *out = &device->IDirect3DDevice7_iface;
            return S_OK;
        }
    }
    else
    {
        if (IsEqualGUID(&IID_IDirect3DDevice3, riid) && device->version == 3)
        {
            IDirect3DDevice3_AddRef(&device->IDirect3DDevice3_iface);
            *out = &device->IDirect3DDevice3_iface;
            return S_OK;
        }

        if (IsEqualGUID(&IID_IDirect3DDevice2, riid) && device->version >= 2)
        {
            IDirect3DDevice2_AddRef(&device->IDirect3DDevice2_iface);
            *out = &device->IDirect3DDevice2_iface;
            return S_OK;
        }

        if (IsEqualGUID(&IID_IDirect3DDevice, riid))
        {
            IDirect3DDevice_AddRef(&device->IDirect3DDevice_iface);
            *out = &device->IDirect3DDevice_iface;
            return S_OK;
        }
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));

    *out = NULL;
    return E_NOINTERFACE;
}

static HRESULT WINAPI d3d_device7_QueryInterface(IDirect3DDevice7 *iface, REFIID riid, void **out)
{
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    return IUnknown_QueryInterface(device->outer_unknown, riid, out);
}

static HRESULT WINAPI d3d_device3_QueryInterface(IDirect3DDevice3 *iface, REFIID riid, void **out)
{
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    return IUnknown_QueryInterface(device->outer_unknown, riid, out);
}

static HRESULT WINAPI d3d_device2_QueryInterface(IDirect3DDevice2 *iface, REFIID riid, void **out)
{
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    return IUnknown_QueryInterface(device->outer_unknown, riid, out);
}

static HRESULT WINAPI d3d_device1_QueryInterface(IDirect3DDevice *iface, REFIID riid, void **out)
{
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    return IUnknown_QueryInterface(device->outer_unknown, riid, out);
}

static ULONG WINAPI d3d_device_inner_AddRef(IUnknown *iface)
{
    struct qemu_device *device = impl_from_IUnknown(iface);
    ULONG ref = InterlockedIncrement(&device->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", device, ref);

    return ref;
}

static ULONG WINAPI d3d_device7_AddRef(IDirect3DDevice7 *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(device->outer_unknown);
}

static ULONG WINAPI d3d_device3_AddRef(IDirect3DDevice3 *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(device->outer_unknown);
}

static ULONG WINAPI d3d_device2_AddRef(IDirect3DDevice2 *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(device->outer_unknown);
}

static ULONG WINAPI d3d_device1_AddRef(IDirect3DDevice *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(device->outer_unknown);
}

static ULONG WINAPI d3d_device_inner_Release(IUnknown *iface)
{
    struct qemu_device *device = impl_from_IUnknown(iface);
    ULONG ref = InterlockedDecrement(&device->ref);
    struct qemu_d3d_device_Release call;
    IUnknown *rt_iface;

    WINE_TRACE("%p decreasing refcount to %u.\n", device, ref);

    if (!ref)
    {
        rt_iface = device->version != 1 ? device->rt_iface : NULL;
        device->rt_iface = NULL;

        call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_RELEASE);
        call.iface = (ULONG_PTR)device;
        qemu_syscall(&call.super);

        /* Release this after destroying the host device. Otherwise we will get a misleading warning
         * that the host surface has an unexpected refcount because the host device holds the last
         * reference. */
        if (rt_iface)
            IUnknown_Release(rt_iface);
    }

    WINE_TRACE("Done\n");
    return ref;
}

static ULONG WINAPI d3d_device7_Release(IDirect3DDevice7 *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(device->outer_unknown);
}

static ULONG WINAPI d3d_device3_Release(IDirect3DDevice3 *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(device->outer_unknown);
}

static ULONG WINAPI d3d_device2_Release(IDirect3DDevice2 *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(device->outer_unknown);
}

static ULONG WINAPI d3d_device1_Release(IDirect3DDevice *iface)
{
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(device->outer_unknown);
}

#else

void qemu_d3d_device_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_device_Release *c = (struct qemu_d3d_device_Release *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = 0;
    if (device->host7)
        c->super.iret += IDirect3DDevice7_Release(device->host7);
    if (device->host3)
        c->super.iret += IDirect3DDevice3_Release(device->host3);
    if (device->host2)
        c->super.iret += IDirect3DDevice2_Release(device->host2);
    if (device->host1)
        c->super.iret += IDirect3DDevice_Release(device->host1);

    if (c->super.iret)
        WINE_ERR("Unexpected combined host device refcount %lu.\n", c->super.iret);

    HeapFree(GetProcessHeap(), 0, device);
}

#endif

struct qemu_d3d_device1_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t d3d;
    uint64_t guid;
    uint64_t device_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_Initialize(IDirect3DDevice *iface, IDirect3D *d3d, GUID *guid, D3DDEVICEDESC *device_desc)
{
    struct qemu_d3d_device1_Initialize call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_INITIALIZE);
    call.iface = (ULONG_PTR)device;
    call.d3d = (ULONG_PTR)d3d;
    call.guid = (ULONG_PTR)guid;
    call.device_desc = (ULONG_PTR)device_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_Initialize *c = (struct qemu_d3d_device1_Initialize *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_Initialize(device->host1, QEMU_G2H(c->d3d), QEMU_G2H(c->guid), QEMU_G2H(c->device_desc));
}

#endif

struct qemu_d3d_device7_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetCaps(IDirect3DDevice7 *iface, D3DDEVICEDESC7 *desc)
{
    struct qemu_d3d_device7_GetCaps call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETCAPS);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetCaps(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetCaps *c = (struct qemu_d3d_device7_GetCaps *)call;
    struct qemu_device *device;

    /* D3DDEVICEDESC7 has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetCaps(device->host7, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d_device3_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t HWDesc;
    uint64_t HelDesc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetCaps(IDirect3DDevice3 *iface, D3DDEVICEDESC *HWDesc, D3DDEVICEDESC *HelDesc)
{
    struct qemu_d3d_device3_GetCaps call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETCAPS);
    call.iface = (ULONG_PTR)device;
    call.HWDesc = (ULONG_PTR)HWDesc;
    call.HelDesc = (ULONG_PTR)HelDesc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetCaps(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetCaps *c = (struct qemu_d3d_device3_GetCaps *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetCaps(device->host3, QEMU_G2H(c->HWDesc), QEMU_G2H(c->HelDesc));
}

#endif

struct qemu_d3d_device2_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hw_desc;
    uint64_t hel_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_GetCaps(IDirect3DDevice2 *iface, D3DDEVICEDESC *hw_desc, D3DDEVICEDESC *hel_desc)
{
    struct qemu_d3d_device2_GetCaps call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_GETCAPS);
    call.iface = (ULONG_PTR)device;
    call.hw_desc = (ULONG_PTR)hw_desc;
    call.hel_desc = (ULONG_PTR)hel_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_GetCaps(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_GetCaps *c = (struct qemu_d3d_device2_GetCaps *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_GetCaps(device->host2, QEMU_G2H(c->hw_desc), QEMU_G2H(c->hel_desc));
}

#endif

struct qemu_d3d_device1_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hw_desc;
    uint64_t hel_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_GetCaps(IDirect3DDevice *iface, D3DDEVICEDESC *hw_desc, D3DDEVICEDESC *hel_desc)
{
    struct qemu_d3d_device1_GetCaps call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_GETCAPS);
    call.iface = (ULONG_PTR)device;
    call.hw_desc = (ULONG_PTR)hw_desc;
    call.hel_desc = (ULONG_PTR)hel_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_GetCaps(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_GetCaps *c = (struct qemu_d3d_device1_GetCaps *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_GetCaps(device->host1, QEMU_G2H(c->hw_desc), QEMU_G2H(c->hel_desc));
}

#endif

struct qemu_d3d_device2_SwapTextureHandles
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tex1;
    uint64_t tex2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SwapTextureHandles(IDirect3DDevice2 *iface, IDirect3DTexture2 *tex1, IDirect3DTexture2 *tex2)
{
    struct qemu_d3d_device2_SwapTextureHandles call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SWAPTEXTUREHANDLES);
    call.iface = (ULONG_PTR)device;
    call.tex1 = (ULONG_PTR)tex1;
    call.tex2 = (ULONG_PTR)tex2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_SwapTextureHandles(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SwapTextureHandles *c = (struct qemu_d3d_device2_SwapTextureHandles *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_SwapTextureHandles(device->host2, QEMU_G2H(c->tex1), QEMU_G2H(c->tex2));
}

#endif

struct qemu_d3d_device1_SwapTextureHandles
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tex1;
    uint64_t tex2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_SwapTextureHandles(IDirect3DDevice *iface, IDirect3DTexture *tex1, IDirect3DTexture *tex2)
{
    struct qemu_d3d_device1_SwapTextureHandles call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_SWAPTEXTUREHANDLES);
    call.iface = (ULONG_PTR)device;
    call.tex1 = (ULONG_PTR)tex1;
    call.tex2 = (ULONG_PTR)tex2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_SwapTextureHandles(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_SwapTextureHandles *c = (struct qemu_d3d_device1_SwapTextureHandles *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_SwapTextureHandles(device->host1, QEMU_G2H(c->tex1), QEMU_G2H(c->tex2));
}

#endif

struct qemu_d3d_device3_GetStats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Stats;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetStats(IDirect3DDevice3 *iface, D3DSTATS *Stats)
{
    struct qemu_d3d_device3_GetStats call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETSTATS);
    call.iface = (ULONG_PTR)device;
    call.Stats = (ULONG_PTR)Stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetStats(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetStats *c = (struct qemu_d3d_device3_GetStats *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetStats(device->host3, QEMU_G2H(c->Stats));
}

#endif

struct qemu_d3d_device2_GetStats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_GetStats(IDirect3DDevice2 *iface, D3DSTATS *stats)
{
    struct qemu_d3d_device2_GetStats call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_GETSTATS);
    call.iface = (ULONG_PTR)device;
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_GetStats(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_GetStats *c = (struct qemu_d3d_device2_GetStats *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_GetStats(device->host2, QEMU_G2H(c->stats));
}

#endif

struct qemu_d3d_device1_GetStats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_GetStats(IDirect3DDevice *iface, D3DSTATS *stats)
{
    struct qemu_d3d_device1_GetStats call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_GETSTATS);
    call.iface = (ULONG_PTR)device;
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_GetStats(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_GetStats *c = (struct qemu_d3d_device1_GetStats *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_GetStats(device->host1, QEMU_G2H(c->stats));
}

#endif

struct qemu_d3d_device1_CreateExecuteBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer_desc;
    uint64_t ExecuteBuffer;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_CreateExecuteBuffer(IDirect3DDevice *iface, D3DEXECUTEBUFFERDESC *buffer_desc, IDirect3DExecuteBuffer **ExecuteBuffer, IUnknown *outer_unknown)
{
    struct qemu_d3d_device1_CreateExecuteBuffer call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_CREATEEXECUTEBUFFER);
    call.iface = (ULONG_PTR)device;
    call.buffer_desc = (ULONG_PTR)buffer_desc;
    call.ExecuteBuffer = (ULONG_PTR)ExecuteBuffer;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_CreateExecuteBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_CreateExecuteBuffer *c = (struct qemu_d3d_device1_CreateExecuteBuffer *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_CreateExecuteBuffer(device->host1, QEMU_G2H(c->buffer_desc), QEMU_G2H(c->ExecuteBuffer), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d_device1_Execute
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ExecuteBuffer;
    uint64_t viewport;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_Execute(IDirect3DDevice *iface, IDirect3DExecuteBuffer *ExecuteBuffer, IDirect3DViewport *viewport, DWORD flags)
{
    struct qemu_d3d_device1_Execute call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_EXECUTE);
    call.iface = (ULONG_PTR)device;
    call.ExecuteBuffer = (ULONG_PTR)ExecuteBuffer;
    call.viewport = (ULONG_PTR)viewport;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_Execute(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_Execute *c = (struct qemu_d3d_device1_Execute *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_Execute(device->host1, QEMU_G2H(c->ExecuteBuffer), QEMU_G2H(c->viewport), c->flags);
}

#endif

struct qemu_d3d_device3_AddViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_AddViewport(IDirect3DDevice3 *iface, IDirect3DViewport3 *viewport)
{
    struct qemu_d3d_device3_AddViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    struct qemu_viewport *impl = unsafe_impl_from_IDirect3DViewport3(viewport);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_ADDVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    /* FIXME: I'll have to keep a list of viewport to Release them when the device is destroyed. */
    if (SUCCEEDED(call.super.iret))
        IDirect3DViewport3_AddRef(viewport);

    return call.super.iret;
}

#else

void qemu_d3d_device3_AddViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_AddViewport *c = (struct qemu_d3d_device3_AddViewport *)call;
    struct qemu_device *device;
    struct qemu_viewport *viewport;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    viewport = QEMU_G2H(c->viewport);

    c->super.iret = IDirect3DDevice3_AddViewport(device->host3, viewport ? viewport->host : NULL);
}

#endif

struct qemu_d3d_device2_AddViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_AddViewport(IDirect3DDevice2 *iface, IDirect3DViewport2 *viewport)
{
    struct qemu_d3d_device2_AddViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    struct qemu_viewport *impl = unsafe_impl_from_IDirect3DViewport2(viewport);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_ADDVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
        IDirect3DViewport2_AddRef(viewport);

    return call.super.iret;
}

#else

void qemu_d3d_device2_AddViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_AddViewport *c = (struct qemu_d3d_device2_AddViewport *)call;
    struct qemu_device *device;
    struct qemu_viewport *viewport;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    viewport = QEMU_G2H(c->viewport);

    c->super.iret = IDirect3DDevice2_AddViewport(device->host2, viewport ? (IDirect3DViewport2 *)viewport->host : NULL);
}

#endif

struct qemu_d3d_device1_AddViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_AddViewport(IDirect3DDevice *iface, IDirect3DViewport *viewport)
{
    struct qemu_d3d_device1_AddViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    struct qemu_viewport *impl = unsafe_impl_from_IDirect3DViewport(viewport);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_ADDVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
        IDirect3DViewport_AddRef(viewport);

    return call.super.iret;
}

#else

void qemu_d3d_device1_AddViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_AddViewport *c = (struct qemu_d3d_device1_AddViewport *)call;
    struct qemu_device *device;
    struct qemu_viewport *viewport;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    viewport = QEMU_G2H(c->viewport);

    c->super.iret = IDirect3DDevice_AddViewport(device->host1, viewport ? (IDirect3DViewport *)viewport->host : NULL);
}

#endif

struct qemu_d3d_device3_DeleteViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DeleteViewport(IDirect3DDevice3 *iface, IDirect3DViewport3 *viewport)
{
    struct qemu_d3d_device3_DeleteViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DELETEVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DeleteViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DeleteViewport *c = (struct qemu_d3d_device3_DeleteViewport *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_DeleteViewport(device->host3, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d_device2_DeleteViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_DeleteViewport(IDirect3DDevice2 *iface, IDirect3DViewport2 *viewport)
{
    struct qemu_d3d_device2_DeleteViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_DELETEVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_DeleteViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_DeleteViewport *c = (struct qemu_d3d_device2_DeleteViewport *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_DeleteViewport(device->host2, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d_device1_DeleteViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_DeleteViewport(IDirect3DDevice *iface, IDirect3DViewport *viewport)
{
    struct qemu_d3d_device1_DeleteViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_DELETEVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_DeleteViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_DeleteViewport *c = (struct qemu_d3d_device1_DeleteViewport *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_DeleteViewport(device->host1, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d_device3_NextViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Viewport3;
    uint64_t lplpDirect3DViewport3;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_NextViewport(IDirect3DDevice3 *iface, IDirect3DViewport3 *Viewport3, IDirect3DViewport3 **lplpDirect3DViewport3, DWORD flags)
{
    struct qemu_d3d_device3_NextViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_NEXTVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.Viewport3 = (ULONG_PTR)Viewport3;
    call.lplpDirect3DViewport3 = (ULONG_PTR)lplpDirect3DViewport3;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_NextViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_NextViewport *c = (struct qemu_d3d_device3_NextViewport *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_NextViewport(device->host3, QEMU_G2H(c->Viewport3), QEMU_G2H(c->lplpDirect3DViewport3), c->flags);
}

#endif

struct qemu_d3d_device2_NextViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
    uint64_t next;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_NextViewport(IDirect3DDevice2 *iface, IDirect3DViewport2 *viewport, IDirect3DViewport2 **next, DWORD flags)
{
    struct qemu_d3d_device2_NextViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_NEXTVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;
    call.next = (ULONG_PTR)next;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_NextViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_NextViewport *c = (struct qemu_d3d_device2_NextViewport *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_NextViewport(device->host2, QEMU_G2H(c->viewport), QEMU_G2H(c->next), c->flags);
}

#endif

struct qemu_d3d_device1_NextViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
    uint64_t next;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_NextViewport(IDirect3DDevice *iface, IDirect3DViewport *viewport, IDirect3DViewport **next, DWORD flags)
{
    struct qemu_d3d_device1_NextViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_NEXTVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;
    call.next = (ULONG_PTR)next;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_NextViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_NextViewport *c = (struct qemu_d3d_device1_NextViewport *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_NextViewport(device->host1, QEMU_G2H(c->viewport), QEMU_G2H(c->next), c->flags);
}

#endif

struct qemu_d3d_device1_Pick
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t viewport;
    uint64_t flags;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_Pick(IDirect3DDevice *iface, IDirect3DExecuteBuffer *buffer, IDirect3DViewport *viewport, DWORD flags, D3DRECT *rect)
{
    struct qemu_d3d_device1_Pick call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_PICK);
    call.iface = (ULONG_PTR)device;
    call.buffer = (ULONG_PTR)buffer;
    call.viewport = (ULONG_PTR)viewport;
    call.flags = flags;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_Pick(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_Pick *c = (struct qemu_d3d_device1_Pick *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_Pick(device->host1, QEMU_G2H(c->buffer), QEMU_G2H(c->viewport), c->flags, QEMU_G2H(c->rect));
}

#endif

struct qemu_d3d_device1_GetPickRecords
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t records;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_GetPickRecords(IDirect3DDevice *iface, DWORD *count, D3DPICKRECORD *records)
{
    struct qemu_d3d_device1_GetPickRecords call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_GETPICKRECORDS);
    call.iface = (ULONG_PTR)device;
    call.count = (ULONG_PTR)count;
    call.records = (ULONG_PTR)records;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_GetPickRecords(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_GetPickRecords *c = (struct qemu_d3d_device1_GetPickRecords *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_GetPickRecords(device->host1, QEMU_G2H(c->count), QEMU_G2H(c->records));
}

#endif

struct qemu_d3d_device_EnumTextureFormats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t callback;
    uint64_t context;
    uint64_t wrapper;
};

struct qemu_d3d_device_EnumTextureFormats_cb
{
    uint64_t func;
    uint64_t format;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall d3d_device_EnumTextureFormats_host_cb(struct qemu_d3d_device_EnumTextureFormats_cb *data)
{
    LPD3DENUMPIXELFORMATSCALLBACK cb = (LPD3DENUMPIXELFORMATSCALLBACK)(ULONG_PTR)data->func;
    return cb((DDPIXELFORMAT *)(ULONG_PTR)data->format, (void *)(ULONG_PTR)data->context);
}

static HRESULT WINAPI d3d_device7_EnumTextureFormats(IDirect3DDevice7 *iface,
        LPD3DENUMPIXELFORMATSCALLBACK callback, void *context)
{
    struct qemu_d3d_device_EnumTextureFormats call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_ENUMTEXTUREFORMATS);
    call.iface = (ULONG_PTR)device;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)d3d_device_EnumTextureFormats_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI d3d_device3_EnumTextureFormats(IDirect3DDevice3 *iface,
        LPD3DENUMPIXELFORMATSCALLBACK callback, void *context)
{
    struct qemu_d3d_device_EnumTextureFormats call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_ENUMTEXTUREFORMATS);
    call.iface = (ULONG_PTR)device;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)d3d_device_EnumTextureFormats_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI d3d_device2_EnumTextureFormats(IDirect3DDevice2 *iface,
        LPD3DENUMTEXTUREFORMATSCALLBACK callback, void *context)
{
    struct qemu_d3d_device_EnumTextureFormats call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_ENUMTEXTUREFORMATS);
    call.iface = (ULONG_PTR)device;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)d3d_device_EnumTextureFormats_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI d3d_device1_EnumTextureFormats(IDirect3DDevice *iface,
        LPD3DENUMTEXTUREFORMATSCALLBACK callback, void *context)
{
    struct qemu_d3d_device_EnumTextureFormats call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_ENUMTEXTUREFORMATS);
    call.iface = (ULONG_PTR)device;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)d3d_device_EnumTextureFormats_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_d3d_device_EnumTextureFormats_host_data
{
    uint64_t guest_func, guest_ctx;
    uint64_t wrapper;
};

static HRESULT qemu_d3d_device3_EnumTextureFormats_host_cb(DDPIXELFORMAT *fmt, void *context)
{
    struct qemu_d3d_device_EnumTextureFormats_host_data *ctx = context;
    struct qemu_d3d_device_EnumTextureFormats_cb call;
    HRESULT hr;

    call.func = ctx->guest_func;
    call.format = QEMU_H2G(fmt);
    call.context = ctx->guest_ctx;

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx).\n", call.func, call.format, call.context);
    hr = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", hr);

    return hr;
}

static HRESULT qemu_d3d_device1_EnumTextureFormats_host_cb(DDSURFACEDESC *desc, void *context)
{
    struct qemu_d3d_device_EnumTextureFormats_host_data *ctx = context;
    struct qemu_d3d_device_EnumTextureFormats_cb call;
    HRESULT hr;
    struct qemu_DDSURFACEDESC conv;

    call.func = ctx->guest_func;
    call.context = ctx->guest_ctx;

#if HOST_BIT == GUEST_BIT
    call.format = QEMU_H2G(fmt);
#else
    conv.dwSize = sizeof(conv);
    DDSURFACEDESC_h2g(&conv, desc);
    call.format = QEMU_H2G(&conv);
#endif

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx).\n", call.func, call.format, call.context);
    hr = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", hr);

    return hr;
}

void qemu_d3d_device_EnumTextureFormats(struct qemu_syscall *call)
{
    struct qemu_d3d_device_EnumTextureFormats *c = (struct qemu_d3d_device_EnumTextureFormats *)call;
    struct qemu_device *device;
    struct qemu_d3d_device_EnumTextureFormats_host_data ctx;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ctx.guest_func = c->callback;
    ctx.guest_ctx = c->context;
    ctx.wrapper = c->wrapper;

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_ENUMTEXTUREFORMATS):
            c->super.iret = IDirect3DDevice7_EnumTextureFormats(device->host7,
                    c->callback ? qemu_d3d_device3_EnumTextureFormats_host_cb : NULL, &ctx);
            break;

        case QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_ENUMTEXTUREFORMATS):
            c->super.iret = IDirect3DDevice3_EnumTextureFormats(device->host3,
                    c->callback ? qemu_d3d_device3_EnumTextureFormats_host_cb : NULL, &ctx);
            break;

        case QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_ENUMTEXTUREFORMATS):
            c->super.iret = IDirect3DDevice2_EnumTextureFormats(device->host2,
                    c->callback ? qemu_d3d_device1_EnumTextureFormats_host_cb : NULL, &ctx);
            break;

        case QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_ENUMTEXTUREFORMATS):
            c->super.iret = IDirect3DDevice_EnumTextureFormats(device->host1,
                    c->callback ? qemu_d3d_device1_EnumTextureFormats_host_cb : NULL, &ctx);
            break;
    }
}

#endif

struct qemu_d3d_device1_CreateMatrix
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t D3DMatHandle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_CreateMatrix(IDirect3DDevice *iface, D3DMATRIXHANDLE *D3DMatHandle)
{
    struct qemu_d3d_device1_CreateMatrix call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_CREATEMATRIX);
    call.iface = (ULONG_PTR)device;
    call.D3DMatHandle = (ULONG_PTR)D3DMatHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_CreateMatrix(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_CreateMatrix *c = (struct qemu_d3d_device1_CreateMatrix *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_CreateMatrix(device->host1, QEMU_G2H(c->D3DMatHandle));
}

#endif

struct qemu_d3d_device1_SetMatrix
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t D3DMatHandle;
    uint64_t D3DMatrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_SetMatrix(IDirect3DDevice *iface, D3DMATRIXHANDLE D3DMatHandle, D3DMATRIX *D3DMatrix)
{
    struct qemu_d3d_device1_SetMatrix call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_SETMATRIX);
    call.iface = (ULONG_PTR)device;
    call.D3DMatHandle = D3DMatHandle;
    call.D3DMatrix = (ULONG_PTR)D3DMatrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_SetMatrix(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_SetMatrix *c = (struct qemu_d3d_device1_SetMatrix *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_SetMatrix(device->host1, c->D3DMatHandle, QEMU_G2H(c->D3DMatrix));
}

#endif

struct qemu_d3d_device1_GetMatrix
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t D3DMatHandle;
    uint64_t D3DMatrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_GetMatrix(IDirect3DDevice *iface, D3DMATRIXHANDLE D3DMatHandle, D3DMATRIX *D3DMatrix)
{
    struct qemu_d3d_device1_GetMatrix call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_GETMATRIX);
    call.iface = (ULONG_PTR)device;
    call.D3DMatHandle = D3DMatHandle;
    call.D3DMatrix = (ULONG_PTR)D3DMatrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_GetMatrix(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_GetMatrix *c = (struct qemu_d3d_device1_GetMatrix *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_GetMatrix(device->host1, c->D3DMatHandle, QEMU_G2H(c->D3DMatrix));
}

#endif

struct qemu_d3d_device1_DeleteMatrix
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t D3DMatHandle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_DeleteMatrix(IDirect3DDevice *iface, D3DMATRIXHANDLE D3DMatHandle)
{
    struct qemu_d3d_device1_DeleteMatrix call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_DELETEMATRIX);
    call.iface = (ULONG_PTR)device;
    call.D3DMatHandle = D3DMatHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_DeleteMatrix(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_DeleteMatrix *c = (struct qemu_d3d_device1_DeleteMatrix *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_DeleteMatrix(device->host1, c->D3DMatHandle);
}

#endif

struct qemu_d3d_device7_BeginScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_BeginScene(IDirect3DDevice7 *iface)
{
    struct qemu_d3d_device7_BeginScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_BEGINSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_BeginScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_BeginScene *c = (struct qemu_d3d_device7_BeginScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_BeginScene(device->host7);
}

#endif

struct qemu_d3d_device3_BeginScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_BeginScene(IDirect3DDevice3 *iface)
{
    struct qemu_d3d_device3_BeginScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_BEGINSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_BeginScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_BeginScene *c = (struct qemu_d3d_device3_BeginScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_BeginScene(device->host3);
}

#endif

struct qemu_d3d_device2_BeginScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_BeginScene(IDirect3DDevice2 *iface)
{
    struct qemu_d3d_device2_BeginScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_BEGINSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_BeginScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_BeginScene *c = (struct qemu_d3d_device2_BeginScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_BeginScene(device->host2);
}

#endif

struct qemu_d3d_device1_BeginScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_BeginScene(IDirect3DDevice *iface)
{
    struct qemu_d3d_device1_BeginScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_BEGINSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_BeginScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_BeginScene *c = (struct qemu_d3d_device1_BeginScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_BeginScene(device->host1);
}

#endif

struct qemu_d3d_device7_EndScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_EndScene(IDirect3DDevice7 *iface)
{
    struct qemu_d3d_device7_EndScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_ENDSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_EndScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_EndScene *c = (struct qemu_d3d_device7_EndScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_EndScene(device->host7);
}

#endif

struct qemu_d3d_device3_EndScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_EndScene(IDirect3DDevice3 *iface)
{
    struct qemu_d3d_device3_EndScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_ENDSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_EndScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_EndScene *c = (struct qemu_d3d_device3_EndScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_EndScene(device->host3);
}

#endif

struct qemu_d3d_device2_EndScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_EndScene(IDirect3DDevice2 *iface)
{
    struct qemu_d3d_device2_EndScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_ENDSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_EndScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_EndScene *c = (struct qemu_d3d_device2_EndScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_EndScene(device->host2);
}

#endif

struct qemu_d3d_device1_EndScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device1_EndScene(IDirect3DDevice *iface)
{
    struct qemu_d3d_device1_EndScene call;
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE1_ENDSCENE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device1_EndScene(struct qemu_syscall *call)
{
    struct qemu_d3d_device1_EndScene *c = (struct qemu_d3d_device1_EndScene *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice_EndScene(device->host1);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetDirect3D(IDirect3DDevice7 *iface, IDirect3D7 **d3d)
{
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);

    WINE_TRACE("iface %p, d3d %p.\n", iface, d3d);

    if (!d3d)
        return DDERR_INVALIDPARAMS;

    *d3d = &device->ddraw->IDirect3D7_iface;
    IDirect3D7_AddRef(*d3d);

    WINE_TRACE("Returning interface %p.\n", *d3d);
    return D3D_OK;
}

static HRESULT WINAPI d3d_device3_GetDirect3D(IDirect3DDevice3 *iface, IDirect3D3 **d3d)
{
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);

    WINE_TRACE("iface %p, d3d %p.\n", iface, d3d);

    if (!d3d)
        return DDERR_INVALIDPARAMS;

    *d3d = &device->ddraw->IDirect3D3_iface;
    IDirect3D3_AddRef(*d3d);

    WINE_TRACE("Returning interface %p.\n", *d3d);
    return D3D_OK;
}

static HRESULT WINAPI d3d_device2_GetDirect3D(IDirect3DDevice2 *iface, IDirect3D2 **d3d)
{
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);

    WINE_TRACE("iface %p, d3d %p.\n", iface, d3d);

    if (!d3d)
        return DDERR_INVALIDPARAMS;

    *d3d = &device->ddraw->IDirect3D2_iface;
    IDirect3D2_AddRef(*d3d);

    WINE_TRACE("Returning interface %p.\n", *d3d);
    return D3D_OK;
}

static HRESULT WINAPI d3d_device1_GetDirect3D(IDirect3DDevice *iface, IDirect3D **d3d)
{
    struct qemu_device *device = impl_from_IDirect3DDevice(iface);

    WINE_TRACE("iface %p, d3d %p.\n", iface, d3d);

    if (!d3d)
        return DDERR_INVALIDPARAMS;

    *d3d = &device->ddraw->IDirect3D_iface;
    IDirect3D_AddRef(*d3d);

    WINE_TRACE("Returning interface %p.\n", *d3d);
    return D3D_OK;
}

#endif

struct qemu_d3d_device3_SetCurrentViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetCurrentViewport(IDirect3DDevice3 *iface, IDirect3DViewport3 *viewport)
{
    struct qemu_d3d_device3_SetCurrentViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    struct qemu_viewport *impl = unsafe_impl_from_IDirect3DViewport3(viewport);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETCURRENTVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)impl;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
        device->current_viewport = impl;

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetCurrentViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetCurrentViewport *c = (struct qemu_d3d_device3_SetCurrentViewport *)call;
    struct qemu_device *device;
    struct qemu_viewport *viewport;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    viewport = QEMU_G2H(c->viewport);

    c->super.iret = IDirect3DDevice3_SetCurrentViewport(device->host3, viewport ? viewport->host : NULL);
}

#endif

struct qemu_d3d_device2_SetCurrentViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SetCurrentViewport(IDirect3DDevice2 *iface, IDirect3DViewport2 *viewport)
{
    struct qemu_d3d_device2_SetCurrentViewport call;
    struct qemu_viewport *impl = unsafe_impl_from_IDirect3DViewport2(viewport);

    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SETCURRENTVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)impl;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
        device->current_viewport = impl;

    return call.super.iret;
}

#else

void qemu_d3d_device2_SetCurrentViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SetCurrentViewport *c = (struct qemu_d3d_device2_SetCurrentViewport *)call;
    struct qemu_device *device;
    struct qemu_viewport *viewport;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    viewport = QEMU_G2H(c->viewport);

    c->super.iret = IDirect3DDevice2_SetCurrentViewport(device->host2,
            viewport ? (IDirect3DViewport2 *)viewport->host : NULL);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetCurrentViewport(IDirect3DDevice3 *iface, IDirect3DViewport3 **viewport)
{
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    WINE_TRACE("iface %p, viewport %p.\n", iface, viewport);

    if (!device->current_viewport)
    {
        WINE_WARN("No current viewport, returning D3DERR_NOCURRENTVIEWPORT\n");
        return D3DERR_NOCURRENTVIEWPORT;
    }

    *viewport = &device->current_viewport->IDirect3DViewport3_iface;
    IDirect3DViewport3_AddRef(*viewport);

    WINE_TRACE("Returning interface %p.\n", *viewport);
    return D3D_OK;
}

static HRESULT WINAPI d3d_device2_GetCurrentViewport(IDirect3DDevice2 *iface, IDirect3DViewport2 **viewport)
{
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);

    WINE_TRACE("iface %p, viewport %p.\n", iface, viewport);

    return d3d_device3_GetCurrentViewport(&device->IDirect3DDevice3_iface,
            (IDirect3DViewport3 **)viewport);
}

#endif

struct qemu_d3d_device7_SetRenderTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t NewTarget;
    uint64_t flags;
    uint64_t change;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetRenderTarget(IDirect3DDevice7 *iface, IDirectDrawSurface7 *NewTarget, DWORD flags)
{
    struct qemu_d3d_device7_SetRenderTarget call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    struct qemu_surface *target = unsafe_impl_from_IDirectDrawSurface7(NewTarget);
    struct qemu_surface *refcnt;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETRENDERTARGET);
    call.iface = (ULONG_PTR)device;
    call.NewTarget = (ULONG_PTR)target;
    call.flags = flags;

    qemu_syscall(&call.super);

    if (call.change)
    {
        IDirectDrawSurface7_AddRef(NewTarget);
        IUnknown_Release(device->rt_iface);
        device->rt_iface = (IUnknown *)NewTarget;
    }

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetRenderTarget(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetRenderTarget *c = (struct qemu_d3d_device7_SetRenderTarget *)call;
    struct qemu_device *device;
    struct qemu_surface *target, *old;
    BOOL z_accept = FALSE;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    target = QEMU_G2H(c->NewTarget);

    c->super.iret = IDirect3DDevice7_SetRenderTarget(device->host7, target ? target->host_surface7 : NULL, c->flags);

    if (c->super.iret == DDERR_INVALIDPIXELFORMAT)
    {
        DDSURFACEDESC2 desc;
        desc.dwSize = sizeof(desc);
        IDirectDrawSurface7_GetSurfaceDesc(target->host_surface7, &desc);
        z_accept = desc.ddsCaps.dwCaps & DDSCAPS_ZBUFFER;
    }

    c->change = SUCCEEDED(c->super.iret) || z_accept;
}

#endif

struct qemu_d3d_device3_SetRenderTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t target;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetRenderTarget(IDirect3DDevice3 *iface, IDirectDrawSurface4 *target, DWORD flags)
{
    struct qemu_d3d_device3_SetRenderTarget call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETRENDERTARGET);
    call.iface = (ULONG_PTR)device;
    call.target = (ULONG_PTR)target;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetRenderTarget(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetRenderTarget *c = (struct qemu_d3d_device3_SetRenderTarget *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_SetRenderTarget(device->host3, QEMU_G2H(c->target), c->flags);
}

#endif

struct qemu_d3d_device2_SetRenderTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t target;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SetRenderTarget(IDirect3DDevice2 *iface, IDirectDrawSurface *target, DWORD flags)
{
    struct qemu_d3d_device2_SetRenderTarget call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SETRENDERTARGET);
    call.iface = (ULONG_PTR)device;
    call.target = (ULONG_PTR)target;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_SetRenderTarget(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SetRenderTarget *c = (struct qemu_d3d_device2_SetRenderTarget *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_SetRenderTarget(device->host2, QEMU_G2H(c->target), c->flags);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetRenderTarget(IDirect3DDevice7 *iface, IDirectDrawSurface7 **RenderTarget)
{
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    HRESULT hr;

    WINE_TRACE("iface %p, target %p.\n", iface, RenderTarget);

    if(!RenderTarget)
        return DDERR_INVALIDPARAMS;

    hr = IUnknown_QueryInterface(device->rt_iface, &IID_IDirectDrawSurface7, (void **)RenderTarget);

    return hr;
}

static HRESULT WINAPI d3d_device3_GetRenderTarget(IDirect3DDevice3 *iface, IDirectDrawSurface4 **RenderTarget)
{
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    HRESULT hr;

    WINE_TRACE("iface %p, target %p.\n", iface, RenderTarget);

    if(!RenderTarget)
        return DDERR_INVALIDPARAMS;

    hr = IUnknown_QueryInterface(device->rt_iface, &IID_IDirectDrawSurface4, (void **)RenderTarget);

    return hr;
}

static HRESULT WINAPI d3d_device2_GetRenderTarget(IDirect3DDevice2 *iface, IDirectDrawSurface **RenderTarget)
{
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    HRESULT hr;

    WINE_TRACE("iface %p, target %p.\n", iface, RenderTarget);

    if(!RenderTarget)
        return DDERR_INVALIDPARAMS;

    hr = IUnknown_QueryInterface(device->rt_iface, &IID_IDirectDrawSurface2, (void **)RenderTarget);

    return hr;
}

#endif

struct qemu_d3d_device3_Begin
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t fvf;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_Begin(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE primitive_type, DWORD fvf, DWORD flags)
{
    struct qemu_d3d_device3_Begin call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_BEGIN);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.fvf = fvf;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_Begin(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_Begin *c = (struct qemu_d3d_device3_Begin *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_Begin(device->host3, c->primitive_type, c->fvf, c->flags);
}

#endif

struct qemu_d3d_device2_Begin
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t vertex_type;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_Begin(IDirect3DDevice2 *iface, D3DPRIMITIVETYPE primitive_type, D3DVERTEXTYPE vertex_type, DWORD flags)
{
    struct qemu_d3d_device2_Begin call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_BEGIN);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.vertex_type = vertex_type;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_Begin(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_Begin *c = (struct qemu_d3d_device2_Begin *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_Begin(device->host2, c->primitive_type, c->vertex_type, c->flags);
}

#endif

struct qemu_d3d_device3_BeginIndexed
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t fvf;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_BeginIndexed(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE primitive_type, DWORD fvf, void *vertices, DWORD vertex_count, DWORD flags)
{
    struct qemu_d3d_device3_BeginIndexed call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_BEGININDEXED);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.fvf = fvf;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_BeginIndexed(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_BeginIndexed *c = (struct qemu_d3d_device3_BeginIndexed *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_BeginIndexed(device->host3, c->primitive_type, c->fvf, QEMU_G2H(c->vertices), c->vertex_count, c->flags);
}

#endif

struct qemu_d3d_device2_BeginIndexed
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t vertex_type;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_BeginIndexed(IDirect3DDevice2 *iface, D3DPRIMITIVETYPE primitive_type, D3DVERTEXTYPE vertex_type, void *vertices, DWORD vertex_count, DWORD flags)
{
    struct qemu_d3d_device2_BeginIndexed call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_BEGININDEXED);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.vertex_type = vertex_type;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_BeginIndexed(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_BeginIndexed *c = (struct qemu_d3d_device2_BeginIndexed *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_BeginIndexed(device->host2, c->primitive_type, c->vertex_type, QEMU_G2H(c->vertices), c->vertex_count, c->flags);
}

#endif

struct qemu_d3d_device3_Vertex
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vertex;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_Vertex(IDirect3DDevice3 *iface, void *vertex)
{
    struct qemu_d3d_device3_Vertex call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_VERTEX);
    call.iface = (ULONG_PTR)device;
    call.vertex = (ULONG_PTR)vertex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_Vertex(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_Vertex *c = (struct qemu_d3d_device3_Vertex *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_Vertex(device->host3, QEMU_G2H(c->vertex));
}

#endif

struct qemu_d3d_device2_Vertex
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vertex;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_Vertex(IDirect3DDevice2 *iface, void *vertex)
{
    struct qemu_d3d_device2_Vertex call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_VERTEX);
    call.iface = (ULONG_PTR)device;
    call.vertex = (ULONG_PTR)vertex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_Vertex(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_Vertex *c = (struct qemu_d3d_device2_Vertex *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_Vertex(device->host2, QEMU_G2H(c->vertex));
}

#endif

struct qemu_d3d_device3_Index
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_Index(IDirect3DDevice3 *iface, WORD index)
{
    struct qemu_d3d_device3_Index call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_INDEX);
    call.iface = (ULONG_PTR)device;
    call.index = index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_Index(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_Index *c = (struct qemu_d3d_device3_Index *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_Index(device->host3, c->index);
}

#endif

struct qemu_d3d_device2_Index
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_Index(IDirect3DDevice2 *iface, WORD index)
{
    struct qemu_d3d_device2_Index call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_INDEX);
    call.iface = (ULONG_PTR)device;
    call.index = index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_Index(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_Index *c = (struct qemu_d3d_device2_Index *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_Index(device->host2, c->index);
}

#endif

struct qemu_d3d_device7_GetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetRenderState(IDirect3DDevice7 *iface, D3DRENDERSTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device7_GetRenderState call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETRENDERSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetRenderState *c = (struct qemu_d3d_device7_GetRenderState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetRenderState(device->host7, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device3_GetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetRenderState(IDirect3DDevice3 *iface, D3DRENDERSTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device3_GetRenderState call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETRENDERSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetRenderState *c = (struct qemu_d3d_device3_GetRenderState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetRenderState(device->host3, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device2_GetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_GetRenderState(IDirect3DDevice2 *iface, D3DRENDERSTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device2_GetRenderState call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_GETRENDERSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_GetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_GetRenderState *c = (struct qemu_d3d_device2_GetRenderState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_GetRenderState(device->host2, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device7_SetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetRenderState(IDirect3DDevice7 *iface, D3DRENDERSTATETYPE state, DWORD value)
{
    struct qemu_d3d_device7_SetRenderState call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETRENDERSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetRenderState *c = (struct qemu_d3d_device7_SetRenderState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetRenderState(device->host7, c->state, c->value);
}

#endif

struct qemu_d3d_device3_SetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetRenderState(IDirect3DDevice3 *iface, D3DRENDERSTATETYPE state, DWORD value)
{
    struct qemu_d3d_device3_SetRenderState call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETRENDERSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetRenderState *c = (struct qemu_d3d_device3_SetRenderState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_SetRenderState(device->host3, c->state, c->value);
}

#endif

struct qemu_d3d_device2_SetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SetRenderState(IDirect3DDevice2 *iface, D3DRENDERSTATETYPE state, DWORD value)
{
    struct qemu_d3d_device2_SetRenderState call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SETRENDERSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_SetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SetRenderState *c = (struct qemu_d3d_device2_SetRenderState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_SetRenderState(device->host2, c->state, c->value);
}

#endif

struct qemu_d3d_device3_SetLightState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetLightState(IDirect3DDevice3 *iface, D3DLIGHTSTATETYPE state, DWORD value)
{
    struct qemu_d3d_device3_SetLightState call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETLIGHTSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetLightState(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetLightState *c = (struct qemu_d3d_device3_SetLightState *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_SetLightState(device->host3, c->state, c->value);
}

#endif

struct qemu_d3d_device2_SetLightState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SetLightState(IDirect3DDevice2 *iface, D3DLIGHTSTATETYPE state, DWORD value)
{
    struct qemu_d3d_device2_SetLightState call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SETLIGHTSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_SetLightState(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SetLightState *c = (struct qemu_d3d_device2_SetLightState *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_SetLightState(device->host2, c->state, c->value);
}

#endif

struct qemu_d3d_device3_GetLightState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetLightState(IDirect3DDevice3 *iface, D3DLIGHTSTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device3_GetLightState call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETLIGHTSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetLightState(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetLightState *c = (struct qemu_d3d_device3_GetLightState *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetLightState(device->host3, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device2_GetLightState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_GetLightState(IDirect3DDevice2 *iface, D3DLIGHTSTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device2_GetLightState call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_GETLIGHTSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_GetLightState(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_GetLightState *c = (struct qemu_d3d_device2_GetLightState *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_GetLightState(device->host2, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device7_SetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetTransform(IDirect3DDevice7 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device7_SetTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetTransform *c = (struct qemu_d3d_device7_SetTransform *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetTransform(device->host7, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device3_SetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetTransform(IDirect3DDevice3 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device3_SetTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetTransform *c = (struct qemu_d3d_device3_SetTransform *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_SetTransform(device->host3, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device2_SetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SetTransform(IDirect3DDevice2 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device2_SetTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SETTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_SetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SetTransform *c = (struct qemu_d3d_device2_SetTransform *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_SetTransform(device->host2, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device7_GetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetTransform(IDirect3DDevice7 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device7_GetTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetTransform *c = (struct qemu_d3d_device7_GetTransform *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetTransform(device->host7, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device3_GetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetTransform(IDirect3DDevice3 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device3_GetTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetTransform *c = (struct qemu_d3d_device3_GetTransform *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetTransform(device->host3, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device2_GetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_GetTransform(IDirect3DDevice2 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device2_GetTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_GETTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_GetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_GetTransform *c = (struct qemu_d3d_device2_GetTransform *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_GetTransform(device->host2, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device7_MultiplyTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_MultiplyTransform(IDirect3DDevice7 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device7_MultiplyTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_MULTIPLYTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_MultiplyTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_MultiplyTransform *c = (struct qemu_d3d_device7_MultiplyTransform *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_MultiplyTransform(device->host7, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device3_MultiplyTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_MultiplyTransform(IDirect3DDevice3 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device3_MultiplyTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_MULTIPLYTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_MultiplyTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_MultiplyTransform *c = (struct qemu_d3d_device3_MultiplyTransform *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_MultiplyTransform(device->host3, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device2_MultiplyTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_MultiplyTransform(IDirect3DDevice2 *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d_device2_MultiplyTransform call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_MULTIPLYTRANSFORM);
    call.iface = (ULONG_PTR)device;
    call.state = state;
    call.matrix = (ULONG_PTR)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_MultiplyTransform(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_MultiplyTransform *c = (struct qemu_d3d_device2_MultiplyTransform *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_MultiplyTransform(device->host2, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d_device7_DrawPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t fvf;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DrawPrimitive(IDirect3DDevice7 *iface, D3DPRIMITIVETYPE primitive_type, DWORD fvf,
        void *vertices, DWORD vertex_count, DWORD flags)
{
    struct qemu_d3d_device7_DrawPrimitive call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DRAWPRIMITIVE);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.fvf = fvf;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DrawPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DrawPrimitive *c = (struct qemu_d3d_device7_DrawPrimitive *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_DrawPrimitive(device->host7, c->primitive_type, c->fvf,
            QEMU_G2H(c->vertices), c->vertex_count, c->flags);
}

#endif

struct qemu_d3d_device3_DrawPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t fvf;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DrawPrimitive(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE primitive_type, DWORD fvf,
        void *vertices, DWORD vertex_count, DWORD flags)
{
    struct qemu_d3d_device3_DrawPrimitive call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DRAWPRIMITIVE);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.fvf = fvf;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DrawPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DrawPrimitive *c = (struct qemu_d3d_device3_DrawPrimitive *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_DrawPrimitive(device->host3, c->primitive_type, c->fvf, QEMU_G2H(c->vertices),
            c->vertex_count, c->flags);
}

#endif

struct qemu_d3d_device2_DrawPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t vertex_type;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_DrawPrimitive(IDirect3DDevice2 *iface, D3DPRIMITIVETYPE primitive_type,
        D3DVERTEXTYPE vertex_type, void *vertices, DWORD vertex_count, DWORD flags)
{
    struct qemu_d3d_device2_DrawPrimitive call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_DRAWPRIMITIVE);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.vertex_type = vertex_type;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_DrawPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_DrawPrimitive *c = (struct qemu_d3d_device2_DrawPrimitive *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_DrawPrimitive(device->host2, c->primitive_type, c->vertex_type,
            QEMU_G2H(c->vertices), c->vertex_count, c->flags);
}

#endif

struct qemu_d3d_device7_DrawIndexedPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t fvf;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t indices;
    uint64_t index_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DrawIndexedPrimitive(IDirect3DDevice7 *iface, D3DPRIMITIVETYPE primitive_type,
        DWORD fvf, void *vertices, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags)
{
    struct qemu_d3d_device7_DrawIndexedPrimitive call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DRAWINDEXEDPRIMITIVE);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.fvf = fvf;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.indices = (ULONG_PTR)indices;
    call.index_count = index_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DrawIndexedPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DrawIndexedPrimitive *c = (struct qemu_d3d_device7_DrawIndexedPrimitive *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_DrawIndexedPrimitive(device->host7, c->primitive_type, c->fvf,
            QEMU_G2H(c->vertices), c->vertex_count, QEMU_G2H(c->indices), c->index_count, c->flags);
}

#endif

struct qemu_d3d_device3_DrawIndexedPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t fvf;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t indices;
    uint64_t index_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DrawIndexedPrimitive(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE primitive_type,
        DWORD fvf, void *vertices, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags)
{
    struct qemu_d3d_device3_DrawIndexedPrimitive call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DRAWINDEXEDPRIMITIVE);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.fvf = fvf;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.indices = (ULONG_PTR)indices;
    call.index_count = index_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DrawIndexedPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DrawIndexedPrimitive *c = (struct qemu_d3d_device3_DrawIndexedPrimitive *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_DrawIndexedPrimitive(device->host3, c->primitive_type, c->fvf,
            QEMU_G2H(c->vertices), c->vertex_count, QEMU_G2H(c->indices), c->index_count, c->flags);
}

#endif

struct qemu_d3d_device2_DrawIndexedPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t vertex_type;
    uint64_t vertices;
    uint64_t vertex_count;
    uint64_t indices;
    uint64_t index_count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_DrawIndexedPrimitive(IDirect3DDevice2 *iface, D3DPRIMITIVETYPE primitive_type,
        D3DVERTEXTYPE vertex_type, void *vertices, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags)
{
    struct qemu_d3d_device2_DrawIndexedPrimitive call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_DRAWINDEXEDPRIMITIVE);
    call.iface = (ULONG_PTR)device;
    call.primitive_type = primitive_type;
    call.vertex_type = vertex_type;
    call.vertices = (ULONG_PTR)vertices;
    call.vertex_count = vertex_count;
    call.indices = (ULONG_PTR)indices;
    call.index_count = index_count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_DrawIndexedPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_DrawIndexedPrimitive *c = (struct qemu_d3d_device2_DrawIndexedPrimitive *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_DrawIndexedPrimitive(device->host2, c->primitive_type, c->vertex_type,
            QEMU_G2H(c->vertices), c->vertex_count, QEMU_G2H(c->indices), c->index_count, c->flags);
}

#endif

struct qemu_d3d_device3_End
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_End(IDirect3DDevice3 *iface, DWORD flags)
{
    struct qemu_d3d_device3_End call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_END);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_End(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_End *c = (struct qemu_d3d_device3_End *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_End(device->host3, c->flags);
}

#endif

struct qemu_d3d_device2_End
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_End(IDirect3DDevice2 *iface, DWORD flags)
{
    struct qemu_d3d_device2_End call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_END);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_End(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_End *c = (struct qemu_d3d_device2_End *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_End(device->host2, c->flags);
}

#endif

struct qemu_d3d_device7_SetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetClipStatus(IDirect3DDevice7 *iface, D3DCLIPSTATUS *clip_status)
{
    struct qemu_d3d_device7_SetClipStatus call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETCLIPSTATUS);
    call.iface = (ULONG_PTR)device;
    call.clip_status = (ULONG_PTR)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetClipStatus *c = (struct qemu_d3d_device7_SetClipStatus *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetClipStatus(device->host7, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d_device3_SetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetClipStatus(IDirect3DDevice3 *iface, D3DCLIPSTATUS *clip_status)
{
    struct qemu_d3d_device3_SetClipStatus call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETCLIPSTATUS);
    call.iface = (ULONG_PTR)device;
    call.clip_status = (ULONG_PTR)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetClipStatus *c = (struct qemu_d3d_device3_SetClipStatus *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_SetClipStatus(device->host3, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d_device2_SetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_SetClipStatus(IDirect3DDevice2 *iface, D3DCLIPSTATUS *clip_status)
{
    struct qemu_d3d_device2_SetClipStatus call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_SETCLIPSTATUS);
    call.iface = (ULONG_PTR)device;
    call.clip_status = (ULONG_PTR)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_SetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_SetClipStatus *c = (struct qemu_d3d_device2_SetClipStatus *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_SetClipStatus(device->host2, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d_device7_GetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetClipStatus(IDirect3DDevice7 *iface, D3DCLIPSTATUS *clip_status)
{
    struct qemu_d3d_device7_GetClipStatus call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETCLIPSTATUS);
    call.iface = (ULONG_PTR)device;
    call.clip_status = (ULONG_PTR)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetClipStatus *c = (struct qemu_d3d_device7_GetClipStatus *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetClipStatus(device->host7, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d_device3_GetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetClipStatus(IDirect3DDevice3 *iface, D3DCLIPSTATUS *clip_status)
{
    struct qemu_d3d_device3_GetClipStatus call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETCLIPSTATUS);
    call.iface = (ULONG_PTR)device;
    call.clip_status = (ULONG_PTR)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetClipStatus *c = (struct qemu_d3d_device3_GetClipStatus *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetClipStatus(device->host3, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d_device2_GetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device2_GetClipStatus(IDirect3DDevice2 *iface, D3DCLIPSTATUS *clip_status)
{
    struct qemu_d3d_device2_GetClipStatus call;
    struct qemu_device *device = impl_from_IDirect3DDevice2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE2_GETCLIPSTATUS);
    call.iface = (ULONG_PTR)device;
    call.clip_status = (ULONG_PTR)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device2_GetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d_device2_GetClipStatus *c = (struct qemu_d3d_device2_GetClipStatus *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice2_GetClipStatus(device->host2, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d_device7_DrawPrimitiveStrided
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t VertexType;
    uint64_t D3DDrawPrimStrideData;
    uint64_t VertexCount;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DrawPrimitiveStrided(IDirect3DDevice7 *iface, D3DPRIMITIVETYPE PrimitiveType,
        DWORD VertexType, D3DDRAWPRIMITIVESTRIDEDDATA *D3DDrawPrimStrideData, DWORD VertexCount, DWORD Flags)
{
    struct qemu_d3d_device7_DrawPrimitiveStrided call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DRAWPRIMITIVESTRIDED);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.VertexType = VertexType;
    call.D3DDrawPrimStrideData = (ULONG_PTR)D3DDrawPrimStrideData;
    call.VertexCount = VertexCount;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DrawPrimitiveStrided(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DrawPrimitiveStrided *c = (struct qemu_d3d_device7_DrawPrimitiveStrided *)call;
    struct qemu_device *device;
    D3DDRAWPRIMITIVESTRIDEDDATA stack, *data = &stack;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->D3DDrawPrimStrideData);
#else
    if (c->D3DDrawPrimStrideData)
        D3DDRAWPRIMITIVESTRIDEDDATA_g2h(data, QEMU_G2H(c->D3DDrawPrimStrideData));
    else
        data = NULL;
#endif

    c->super.iret = IDirect3DDevice7_DrawPrimitiveStrided(device->host7, c->PrimitiveType, c->VertexType,
            data, c->VertexCount, c->Flags);
}

#endif

struct qemu_d3d_device3_DrawPrimitiveStrided
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t VertexType;
    uint64_t D3DDrawPrimStrideData;
    uint64_t VertexCount;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DrawPrimitiveStrided(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE PrimitiveType,
        DWORD VertexType, D3DDRAWPRIMITIVESTRIDEDDATA *D3DDrawPrimStrideData, DWORD VertexCount, DWORD Flags)
{
    struct qemu_d3d_device3_DrawPrimitiveStrided call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DRAWPRIMITIVESTRIDED);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.VertexType = VertexType;
    call.D3DDrawPrimStrideData = (ULONG_PTR)D3DDrawPrimStrideData;
    call.VertexCount = VertexCount;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DrawPrimitiveStrided(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DrawPrimitiveStrided *c = (struct qemu_d3d_device3_DrawPrimitiveStrided *)call;
    struct qemu_device *device;
    D3DDRAWPRIMITIVESTRIDEDDATA stack, *data = &stack;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->D3DDrawPrimStrideData);
#else
    if (c->D3DDrawPrimStrideData)
        D3DDRAWPRIMITIVESTRIDEDDATA_g2h(data, QEMU_G2H(c->D3DDrawPrimStrideData));
    else
        data = NULL;
#endif

    c->super.iret = IDirect3DDevice3_DrawPrimitiveStrided(device->host3, c->PrimitiveType, c->VertexType,
            data, c->VertexCount, c->Flags);
}

#endif

struct qemu_d3d_device7_DrawIndexedPrimitiveStrided
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t VertexType;
    uint64_t D3DDrawPrimStrideData;
    uint64_t VertexCount;
    uint64_t Indices;
    uint64_t IndexCount;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DrawIndexedPrimitiveStrided(IDirect3DDevice7 *iface, D3DPRIMITIVETYPE PrimitiveType,
        DWORD VertexType, D3DDRAWPRIMITIVESTRIDEDDATA *D3DDrawPrimStrideData, DWORD VertexCount, WORD *Indices,
        DWORD IndexCount, DWORD Flags)
{
    struct qemu_d3d_device7_DrawIndexedPrimitiveStrided call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DRAWINDEXEDPRIMITIVESTRIDED);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.VertexType = VertexType;
    call.D3DDrawPrimStrideData = (ULONG_PTR)D3DDrawPrimStrideData;
    call.VertexCount = VertexCount;
    call.Indices = (ULONG_PTR)Indices;
    call.IndexCount = IndexCount;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DrawIndexedPrimitiveStrided(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DrawIndexedPrimitiveStrided *c =
            (struct qemu_d3d_device7_DrawIndexedPrimitiveStrided *)call;
    struct qemu_device *device;
    D3DDRAWPRIMITIVESTRIDEDDATA stack, *data = &stack;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->D3DDrawPrimStrideData);
#else
    if (c->D3DDrawPrimStrideData)
        D3DDRAWPRIMITIVESTRIDEDDATA_g2h(data, QEMU_G2H(c->D3DDrawPrimStrideData));
    else
        data = NULL;
#endif

    c->super.iret = IDirect3DDevice7_DrawIndexedPrimitiveStrided(device->host7, c->PrimitiveType, c->VertexType,
            data, c->VertexCount, QEMU_G2H(c->Indices), c->IndexCount, c->Flags);
}

#endif

struct qemu_d3d_device3_DrawIndexedPrimitiveStrided
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t VertexType;
    uint64_t D3DDrawPrimStrideData;
    uint64_t VertexCount;
    uint64_t Indices;
    uint64_t IndexCount;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DrawIndexedPrimitiveStrided(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE PrimitiveType,
        DWORD VertexType, D3DDRAWPRIMITIVESTRIDEDDATA *D3DDrawPrimStrideData, DWORD VertexCount, WORD *Indices,
        DWORD IndexCount, DWORD Flags)
{
    struct qemu_d3d_device3_DrawIndexedPrimitiveStrided call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DRAWINDEXEDPRIMITIVESTRIDED);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.VertexType = VertexType;
    call.D3DDrawPrimStrideData = (ULONG_PTR)D3DDrawPrimStrideData;
    call.VertexCount = VertexCount;
    call.Indices = (ULONG_PTR)Indices;
    call.IndexCount = IndexCount;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DrawIndexedPrimitiveStrided(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DrawIndexedPrimitiveStrided *c = (struct qemu_d3d_device3_DrawIndexedPrimitiveStrided *)call;
    struct qemu_device *device;
    D3DDRAWPRIMITIVESTRIDEDDATA stack, *data = &stack;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->D3DDrawPrimStrideData);
#else
    if (c->D3DDrawPrimStrideData)
        D3DDRAWPRIMITIVESTRIDEDDATA_g2h(data, QEMU_G2H(c->D3DDrawPrimStrideData));
    else
        data = NULL;
#endif

    c->super.iret = IDirect3DDevice3_DrawIndexedPrimitiveStrided(device->host3, c->PrimitiveType, c->VertexType,
            data, c->VertexCount, QEMU_G2H(c->Indices), c->IndexCount, c->Flags);
}

#endif

struct qemu_d3d_device7_DrawPrimitiveVB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t D3DVertexBuf;
    uint64_t StartVertex;
    uint64_t NumVertices;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DrawPrimitiveVB(IDirect3DDevice7 *iface, D3DPRIMITIVETYPE PrimitiveType,
        IDirect3DVertexBuffer7 *D3DVertexBuf, DWORD StartVertex, DWORD NumVertices, DWORD Flags)
{
    struct qemu_d3d_device7_DrawPrimitiveVB call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    struct qemu_vertex_buffer *buffer = unsafe_impl_from_IDirect3DVertexBuffer7(D3DVertexBuf);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DRAWPRIMITIVEVB);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.D3DVertexBuf = (ULONG_PTR)buffer;
    call.StartVertex = StartVertex;
    call.NumVertices = NumVertices;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DrawPrimitiveVB(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DrawPrimitiveVB *c = (struct qemu_d3d_device7_DrawPrimitiveVB *)call;
    struct qemu_device *device;
    struct qemu_vertex_buffer *buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->D3DVertexBuf);

    c->super.iret = IDirect3DDevice7_DrawPrimitiveVB(device->host7, c->PrimitiveType,
            buffer ? buffer->host : NULL, c->StartVertex, c->NumVertices, c->Flags);
}

#endif

struct qemu_d3d_device3_DrawPrimitiveVB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t D3DVertexBuf;
    uint64_t StartVertex;
    uint64_t NumVertices;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DrawPrimitiveVB(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE PrimitiveType,
        IDirect3DVertexBuffer *D3DVertexBuf, DWORD StartVertex, DWORD NumVertices, DWORD Flags)
{
    struct qemu_d3d_device3_DrawPrimitiveVB call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    struct qemu_vertex_buffer *buffer = unsafe_impl_from_IDirect3DVertexBuffer7((IDirect3DVertexBuffer7 *)D3DVertexBuf);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DRAWPRIMITIVEVB);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.D3DVertexBuf = (ULONG_PTR)buffer;
    call.StartVertex = StartVertex;
    call.NumVertices = NumVertices;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DrawPrimitiveVB(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DrawPrimitiveVB *c = (struct qemu_d3d_device3_DrawPrimitiveVB *)call;
    struct qemu_device *device;
    struct qemu_vertex_buffer *buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->D3DVertexBuf);

    c->super.iret = IDirect3DDevice3_DrawPrimitiveVB(device->host3, c->PrimitiveType,
            buffer ? (IDirect3DVertexBuffer *)buffer->host : NULL, c->StartVertex, c->NumVertices, c->Flags);
}

#endif

struct qemu_d3d_device7_DrawIndexedPrimitiveVB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t D3DVertexBuf;
    uint64_t StartVertex;
    uint64_t NumVertices;
    uint64_t Indices;
    uint64_t IndexCount;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DrawIndexedPrimitiveVB(IDirect3DDevice7 *iface, D3DPRIMITIVETYPE PrimitiveType,
        IDirect3DVertexBuffer7 *D3DVertexBuf, DWORD StartVertex, DWORD NumVertices, WORD *Indices, DWORD IndexCount,
        DWORD Flags)
{
    struct qemu_d3d_device7_DrawIndexedPrimitiveVB call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    struct qemu_vertex_buffer *buffer = unsafe_impl_from_IDirect3DVertexBuffer7(D3DVertexBuf);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DRAWINDEXEDPRIMITIVEVB);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.D3DVertexBuf = (ULONG_PTR)buffer;
    call.StartVertex = StartVertex;
    call.NumVertices = NumVertices;
    call.Indices = (ULONG_PTR)Indices;
    call.IndexCount = IndexCount;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DrawIndexedPrimitiveVB(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DrawIndexedPrimitiveVB *c = (struct qemu_d3d_device7_DrawIndexedPrimitiveVB *)call;
    struct qemu_device *device;
    struct qemu_vertex_buffer *buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->D3DVertexBuf);

    c->super.iret = IDirect3DDevice7_DrawIndexedPrimitiveVB(device->host7, c->PrimitiveType,
            buffer ? buffer->host : NULL, c->StartVertex, c->NumVertices, QEMU_G2H(c->Indices), c->IndexCount, c->Flags);
}

#endif

struct qemu_d3d_device3_DrawIndexedPrimitiveVB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PrimitiveType;
    uint64_t D3DVertexBuf;
    uint64_t Indices;
    uint64_t IndexCount;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_DrawIndexedPrimitiveVB(IDirect3DDevice3 *iface, D3DPRIMITIVETYPE PrimitiveType,
        IDirect3DVertexBuffer *D3DVertexBuf, WORD *Indices, DWORD IndexCount, DWORD Flags)
{
    struct qemu_d3d_device3_DrawIndexedPrimitiveVB call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    struct qemu_vertex_buffer *buffer = unsafe_impl_from_IDirect3DVertexBuffer7((IDirect3DVertexBuffer7 *)D3DVertexBuf);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_DRAWINDEXEDPRIMITIVEVB);
    call.iface = (ULONG_PTR)device;
    call.PrimitiveType = PrimitiveType;
    call.D3DVertexBuf = (ULONG_PTR)buffer;
    call.Indices = (ULONG_PTR)Indices;
    call.IndexCount = IndexCount;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_DrawIndexedPrimitiveVB(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_DrawIndexedPrimitiveVB *c = (struct qemu_d3d_device3_DrawIndexedPrimitiveVB *)call;
    struct qemu_device *device;
    struct qemu_vertex_buffer *buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->D3DVertexBuf);

    c->super.iret = IDirect3DDevice3_DrawIndexedPrimitiveVB(device->host3, c->PrimitiveType,
            buffer ? (IDirect3DVertexBuffer *)buffer->host : NULL, QEMU_G2H(c->Indices), c->IndexCount, c->Flags);
}

#endif

struct qemu_d3d_device7_ComputeSphereVisibility
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t centers;
    uint64_t radii;
    uint64_t sphere_count;
    uint64_t flags;
    uint64_t return_values;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_ComputeSphereVisibility(IDirect3DDevice7 *iface, D3DVECTOR *centers, D3DVALUE *radii,
        DWORD sphere_count, DWORD flags, DWORD *return_values)
{
    struct qemu_d3d_device7_ComputeSphereVisibility call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_COMPUTESPHEREVISIBILITY);
    call.iface = (ULONG_PTR)device;
    call.centers = (ULONG_PTR)centers;
    call.radii = (ULONG_PTR)radii;
    call.sphere_count = sphere_count;
    call.flags = flags;
    call.return_values = (ULONG_PTR)return_values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_ComputeSphereVisibility(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_ComputeSphereVisibility *c = (struct qemu_d3d_device7_ComputeSphereVisibility *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_ComputeSphereVisibility(device->host7, QEMU_G2H(c->centers), QEMU_G2H(c->radii),
            c->sphere_count, c->flags, QEMU_G2H(c->return_values));
}

#endif

struct qemu_d3d_device3_ComputeSphereVisibility
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t centers;
    uint64_t radii;
    uint64_t sphere_count;
    uint64_t flags;
    uint64_t return_values;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_ComputeSphereVisibility(IDirect3DDevice3 *iface, D3DVECTOR *centers, D3DVALUE *radii, DWORD sphere_count, DWORD flags, DWORD *return_values)
{
    struct qemu_d3d_device3_ComputeSphereVisibility call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_COMPUTESPHEREVISIBILITY);
    call.iface = (ULONG_PTR)device;
    call.centers = (ULONG_PTR)centers;
    call.radii = (ULONG_PTR)radii;
    call.sphere_count = sphere_count;
    call.flags = flags;
    call.return_values = (ULONG_PTR)return_values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_ComputeSphereVisibility(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_ComputeSphereVisibility *c = (struct qemu_d3d_device3_ComputeSphereVisibility *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_ComputeSphereVisibility(device->host3, QEMU_G2H(c->centers), QEMU_G2H(c->radii), c->sphere_count, c->flags, QEMU_G2H(c->return_values));
}

#endif

struct qemu_d3d_device7_GetTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t Texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetTexture(IDirect3DDevice7 *iface, DWORD stage, IDirectDrawSurface7 **Texture)
{
    struct qemu_d3d_device7_GetTexture call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETTEXTURE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.Texture = (ULONG_PTR)Texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetTexture(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetTexture *c = (struct qemu_d3d_device7_GetTexture *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetTexture(device->host7, c->stage, QEMU_G2H(c->Texture));
}

#endif

struct qemu_d3d_device3_GetTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t Texture2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetTexture(IDirect3DDevice3 *iface, DWORD stage, IDirect3DTexture2 **Texture2)
{
    struct qemu_d3d_device3_GetTexture call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETTEXTURE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.Texture2 = (ULONG_PTR)Texture2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetTexture(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetTexture *c = (struct qemu_d3d_device3_GetTexture *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetTexture(device->host3, c->stage, QEMU_G2H(c->Texture2));
}

#endif

struct qemu_d3d_device7_SetTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetTexture(IDirect3DDevice7 *iface, DWORD stage, IDirectDrawSurface7 *texture)
{
    struct qemu_d3d_device7_SetTexture call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    struct qemu_surface *surface = unsafe_impl_from_IDirectDrawSurface7(texture);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETTEXTURE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.texture = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetTexture(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetTexture *c = (struct qemu_d3d_device7_SetTexture *)call;
    struct qemu_device *device;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    surface = QEMU_G2H(c->texture);

    c->super.iret = IDirect3DDevice7_SetTexture(device->host7, c->stage, surface ? surface->host_surface7 : NULL);
}

#endif

struct qemu_d3d_device3_SetTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetTexture(IDirect3DDevice3 *iface, DWORD stage, IDirect3DTexture2 *texture)
{
    struct qemu_d3d_device3_SetTexture call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    struct qemu_surface *surface = unsafe_impl_from_IDirect3DTexture2(texture);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETTEXTURE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.texture = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetTexture(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetTexture *c = (struct qemu_d3d_device3_SetTexture *)call;
    struct qemu_device *device;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    surface = QEMU_G2H(c->texture);

    c->super.iret = IDirect3DDevice3_SetTexture(device->host3, c->stage, surface ? surface->host_texture2 : NULL);
}

#endif

struct qemu_d3d_device7_GetTextureStageState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetTextureStageState(IDirect3DDevice7 *iface, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device7_GetTextureStageState call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETTEXTURESTAGESTATE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetTextureStageState(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetTextureStageState *c = (struct qemu_d3d_device7_GetTextureStageState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetTextureStageState(device->host7, c->stage, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device3_GetTextureStageState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_GetTextureStageState(IDirect3DDevice3 *iface, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD *value)
{
    struct qemu_d3d_device3_GetTextureStageState call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_GETTEXTURESTAGESTATE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.state = state;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_GetTextureStageState(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_GetTextureStageState *c = (struct qemu_d3d_device3_GetTextureStageState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_GetTextureStageState(device->host3, c->stage, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d_device7_SetTextureStageState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetTextureStageState(IDirect3DDevice7 *iface, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD value)
{
    struct qemu_d3d_device7_SetTextureStageState call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETTEXTURESTAGESTATE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetTextureStageState(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetTextureStageState *c = (struct qemu_d3d_device7_SetTextureStageState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetTextureStageState(device->host7, c->stage, c->state, c->value);
}

#endif

struct qemu_d3d_device3_SetTextureStageState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_SetTextureStageState(IDirect3DDevice3 *iface, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD value)
{
    struct qemu_d3d_device3_SetTextureStageState call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_SETTEXTURESTAGESTATE);
    call.iface = (ULONG_PTR)device;
    call.stage = stage;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_SetTextureStageState(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_SetTextureStageState *c = (struct qemu_d3d_device3_SetTextureStageState *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_SetTextureStageState(device->host3, c->stage, c->state, c->value);
}

#endif

struct qemu_d3d_device7_ValidateDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pass_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_ValidateDevice(IDirect3DDevice7 *iface, DWORD *pass_count)
{
    struct qemu_d3d_device7_ValidateDevice call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_VALIDATEDEVICE);
    call.iface = (ULONG_PTR)device;
    call.pass_count = (ULONG_PTR)pass_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_ValidateDevice(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_ValidateDevice *c = (struct qemu_d3d_device7_ValidateDevice *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_ValidateDevice(device->host7, QEMU_G2H(c->pass_count));
}

#endif

struct qemu_d3d_device3_ValidateDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pass_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device3_ValidateDevice(IDirect3DDevice3 *iface, DWORD *pass_count)
{
    struct qemu_d3d_device3_ValidateDevice call;
    struct qemu_device *device = impl_from_IDirect3DDevice3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE3_VALIDATEDEVICE);
    call.iface = (ULONG_PTR)device;
    call.pass_count = (ULONG_PTR)pass_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device3_ValidateDevice(struct qemu_syscall *call)
{
    struct qemu_d3d_device3_ValidateDevice *c = (struct qemu_d3d_device3_ValidateDevice *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice3_ValidateDevice(device->host3, QEMU_G2H(c->pass_count));
}

#endif

struct qemu_d3d_device7_Clear
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t rects;
    uint64_t flags;
    uint64_t color;
    uint64_t z;
    uint64_t stencil;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_Clear(IDirect3DDevice7 *iface, DWORD count, D3DRECT *rects, DWORD flags, D3DCOLOR color, D3DVALUE z, DWORD stencil)
{
    struct qemu_d3d_device7_Clear call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_CLEAR);
    call.iface = (ULONG_PTR)device;
    call.count = count;
    call.rects = (ULONG_PTR)rects;
    call.flags = flags;
    call.color = color;
    call.z = z;
    call.stencil = stencil;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_Clear(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_Clear *c = (struct qemu_d3d_device7_Clear *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_Clear(device->host7, c->count, QEMU_G2H(c->rects), c->flags, c->color, c->z, c->stencil);
}

#endif

struct qemu_d3d_device7_SetViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetViewport(IDirect3DDevice7 *iface, D3DVIEWPORT7 *viewport)
{
    struct qemu_d3d_device7_SetViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetViewport *c = (struct qemu_d3d_device7_SetViewport *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetViewport(device->host7, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d_device7_GetViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetViewport(IDirect3DDevice7 *iface, D3DVIEWPORT7 *viewport)
{
    struct qemu_d3d_device7_GetViewport call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETVIEWPORT);
    call.iface = (ULONG_PTR)device;
    call.viewport = (ULONG_PTR)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetViewport *c = (struct qemu_d3d_device7_GetViewport *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetViewport(device->host7, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d_device7_SetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetMaterial(IDirect3DDevice7 *iface, D3DMATERIAL7 *material)
{
    struct qemu_d3d_device7_SetMaterial call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETMATERIAL);
    call.iface = (ULONG_PTR)device;
    call.material = (ULONG_PTR)material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetMaterial *c = (struct qemu_d3d_device7_SetMaterial *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetMaterial(device->host7, QEMU_G2H(c->material));
}

#endif

struct qemu_d3d_device7_GetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetMaterial(IDirect3DDevice7 *iface, D3DMATERIAL7 *material)
{
    struct qemu_d3d_device7_GetMaterial call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETMATERIAL);
    call.iface = (ULONG_PTR)device;
    call.material = (ULONG_PTR)material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetMaterial *c = (struct qemu_d3d_device7_GetMaterial *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetMaterial(device->host7, QEMU_G2H(c->material));
}

#endif

struct qemu_d3d_device7_SetLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light_idx;
    uint64_t light;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetLight(IDirect3DDevice7 *iface, DWORD light_idx, D3DLIGHT7 *light)
{
    struct qemu_d3d_device7_SetLight call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETLIGHT);
    call.iface = (ULONG_PTR)device;
    call.light_idx = light_idx;
    call.light = (ULONG_PTR)light;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetLight(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetLight *c = (struct qemu_d3d_device7_SetLight *)call;
    struct qemu_device *device;

    /* D3DLIGHT7 has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetLight(device->host7, c->light_idx, QEMU_G2H(c->light));
}

#endif

struct qemu_d3d_device7_GetLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light_idx;
    uint64_t light;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetLight(IDirect3DDevice7 *iface, DWORD light_idx, D3DLIGHT7 *light)
{
    struct qemu_d3d_device7_GetLight call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETLIGHT);
    call.iface = (ULONG_PTR)device;
    call.light_idx = light_idx;
    call.light = (ULONG_PTR)light;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetLight(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetLight *c = (struct qemu_d3d_device7_GetLight *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetLight(device->host7, c->light_idx, QEMU_G2H(c->light));
}

#endif

struct qemu_d3d_device7_BeginStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_BeginStateBlock(IDirect3DDevice7 *iface)
{
    struct qemu_d3d_device7_BeginStateBlock call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_BEGINSTATEBLOCK);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_BeginStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_BeginStateBlock *c = (struct qemu_d3d_device7_BeginStateBlock *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_BeginStateBlock(device->host7);
}

#endif

struct qemu_d3d_device7_EndStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_EndStateBlock(IDirect3DDevice7 *iface, DWORD *stateblock)
{
    struct qemu_d3d_device7_EndStateBlock call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_ENDSTATEBLOCK);
    call.iface = (ULONG_PTR)device;
    call.stateblock = (ULONG_PTR)stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_EndStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_EndStateBlock *c = (struct qemu_d3d_device7_EndStateBlock *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_EndStateBlock(device->host7, QEMU_G2H(c->stateblock));
}

#endif

struct qemu_d3d_device7_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_PreLoad(IDirect3DDevice7 *iface, IDirectDrawSurface7 *texture)
{
    struct qemu_d3d_device7_PreLoad call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_PRELOAD);
    call.iface = (ULONG_PTR)device;
    call.texture = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_PreLoad *c = (struct qemu_d3d_device7_PreLoad *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_PreLoad(device->host7, QEMU_G2H(c->texture));
}

#endif

struct qemu_d3d_device7_ApplyStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_ApplyStateBlock(IDirect3DDevice7 *iface, DWORD stateblock)
{
    struct qemu_d3d_device7_ApplyStateBlock call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_APPLYSTATEBLOCK);
    call.iface = (ULONG_PTR)device;
    call.stateblock = stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_ApplyStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_ApplyStateBlock *c = (struct qemu_d3d_device7_ApplyStateBlock *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_ApplyStateBlock(device->host7, c->stateblock);
}

#endif

struct qemu_d3d_device7_CaptureStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_CaptureStateBlock(IDirect3DDevice7 *iface, DWORD stateblock)
{
    struct qemu_d3d_device7_CaptureStateBlock call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_CAPTURESTATEBLOCK);
    call.iface = (ULONG_PTR)device;
    call.stateblock = stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_CaptureStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_CaptureStateBlock *c = (struct qemu_d3d_device7_CaptureStateBlock *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_CaptureStateBlock(device->host7, c->stateblock);
}

#endif

struct qemu_d3d_device7_DeleteStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_DeleteStateBlock(IDirect3DDevice7 *iface, DWORD stateblock)
{
    struct qemu_d3d_device7_DeleteStateBlock call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_DELETESTATEBLOCK);
    call.iface = (ULONG_PTR)device;
    call.stateblock = stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_DeleteStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_DeleteStateBlock *c = (struct qemu_d3d_device7_DeleteStateBlock *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_DeleteStateBlock(device->host7, c->stateblock);
}

#endif

struct qemu_d3d_device7_CreateStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_CreateStateBlock(IDirect3DDevice7 *iface, D3DSTATEBLOCKTYPE type, DWORD *stateblock)
{
    struct qemu_d3d_device7_CreateStateBlock call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_CREATESTATEBLOCK);
    call.iface = (ULONG_PTR)device;
    call.type = type;
    call.stateblock = (ULONG_PTR)stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_CreateStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_CreateStateBlock *c = (struct qemu_d3d_device7_CreateStateBlock *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_CreateStateBlock(device->host7, c->type, QEMU_G2H(c->stateblock));
}

#endif

struct qemu_d3d_device7_Load
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_texture;
    uint64_t dst_pos;
    uint64_t src_texture;
    uint64_t src_rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_Load(IDirect3DDevice7 *iface, IDirectDrawSurface7 *dst_texture, POINT *dst_pos,
        IDirectDrawSurface7 *src_texture, RECT *src_rect, DWORD flags)
{
    struct qemu_d3d_device7_Load call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    struct qemu_surface *dst = unsafe_impl_from_IDirectDrawSurface7(dst_texture);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface7(src_texture);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_LOAD);
    call.iface = (ULONG_PTR)device;
    call.dst_texture = (ULONG_PTR)dst;
    call.dst_pos = (ULONG_PTR)dst_pos;
    call.src_texture = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_Load(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_Load *c = (struct qemu_d3d_device7_Load *)call;
    struct qemu_device *device;
    struct qemu_surface *dst, *src;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    dst = QEMU_G2H(c->dst_texture);
    src = QEMU_G2H(c->src_texture);

    c->super.iret = IDirect3DDevice7_Load(device->host7, dst ? dst->host_surface7 : NULL, QEMU_G2H(c->dst_pos),
            src ? src->host_surface7 : NULL, QEMU_G2H(c->src_rect), c->flags);
}

#endif

struct qemu_d3d_device7_LightEnable
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light_idx;
    uint64_t enabled;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_LightEnable(IDirect3DDevice7 *iface, DWORD light_idx, BOOL enabled)
{
    struct qemu_d3d_device7_LightEnable call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_LIGHTENABLE);
    call.iface = (ULONG_PTR)device;
    call.light_idx = light_idx;
    call.enabled = enabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_LightEnable(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_LightEnable *c = (struct qemu_d3d_device7_LightEnable *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_LightEnable(device->host7, c->light_idx, c->enabled);
}

#endif

struct qemu_d3d_device7_GetLightEnable
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light_idx;
    uint64_t enabled;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetLightEnable(IDirect3DDevice7 *iface, DWORD light_idx, BOOL *enabled)
{
    struct qemu_d3d_device7_GetLightEnable call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETLIGHTENABLE);
    call.iface = (ULONG_PTR)device;
    call.light_idx = light_idx;
    call.enabled = (ULONG_PTR)enabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetLightEnable(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetLightEnable *c = (struct qemu_d3d_device7_GetLightEnable *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetLightEnable(device->host7, c->light_idx, QEMU_G2H(c->enabled));
}

#endif

struct qemu_d3d_device7_SetClipPlane
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t idx;
    uint64_t plane;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_SetClipPlane(IDirect3DDevice7 *iface, DWORD idx, D3DVALUE *plane)
{
    struct qemu_d3d_device7_SetClipPlane call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_SETCLIPPLANE);
    call.iface = (ULONG_PTR)device;
    call.idx = idx;
    call.plane = (ULONG_PTR)plane;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_SetClipPlane(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_SetClipPlane *c = (struct qemu_d3d_device7_SetClipPlane *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_SetClipPlane(device->host7, c->idx, QEMU_G2H(c->plane));
}

#endif

struct qemu_d3d_device7_GetClipPlane
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t idx;
    uint64_t plane;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetClipPlane(IDirect3DDevice7 *iface, DWORD idx, D3DVALUE *plane)
{
    struct qemu_d3d_device7_GetClipPlane call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETCLIPPLANE);
    call.iface = (ULONG_PTR)device;
    call.idx = idx;
    call.plane = (ULONG_PTR)plane;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetClipPlane(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetClipPlane *c = (struct qemu_d3d_device7_GetClipPlane *)call;
    struct qemu_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetClipPlane(device->host7, c->idx, QEMU_G2H(c->plane));
}

#endif

struct qemu_d3d_device7_GetInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t info_id;
    uint64_t info;
    uint64_t info_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_device7_GetInfo(IDirect3DDevice7 *iface, DWORD info_id, void *info, DWORD info_size)
{
    struct qemu_d3d_device7_GetInfo call;
    struct qemu_device *device = impl_from_IDirect3DDevice7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE7_GETINFO);
    call.iface = (ULONG_PTR)device;
    call.info_id = info_id;
    call.info = (ULONG_PTR)info;
    call.info_size = info_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device7_GetInfo(struct qemu_syscall *call)
{
    struct qemu_d3d_device7_GetInfo *c = (struct qemu_d3d_device7_GetInfo *)call;
    struct qemu_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice7_GetInfo(device->host7, c->info_id, QEMU_G2H(c->info), c->info_size);
}

#endif

#ifdef QEMU_DLL_GUEST

/* I'm not bothering with fpusetup vs fpupreserve in the client side yet until we spot an issue. */

static const struct IDirect3DDevice7Vtbl d3d_device7_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_device7_QueryInterface,
    d3d_device7_AddRef,
    d3d_device7_Release,
    /*** IDirect3DDevice7 ***/
    d3d_device7_GetCaps,
    d3d_device7_EnumTextureFormats,
    d3d_device7_BeginScene,
    d3d_device7_EndScene,
    d3d_device7_GetDirect3D,
    d3d_device7_SetRenderTarget,
    d3d_device7_GetRenderTarget,
    d3d_device7_Clear,
    d3d_device7_SetTransform,
    d3d_device7_GetTransform,
    d3d_device7_SetViewport,
    d3d_device7_MultiplyTransform,
    d3d_device7_GetViewport,
    d3d_device7_SetMaterial,
    d3d_device7_GetMaterial,
    d3d_device7_SetLight,
    d3d_device7_GetLight,
    d3d_device7_SetRenderState,
    d3d_device7_GetRenderState,
    d3d_device7_BeginStateBlock,
    d3d_device7_EndStateBlock,
    d3d_device7_PreLoad,
    d3d_device7_DrawPrimitive,
    d3d_device7_DrawIndexedPrimitive,
    d3d_device7_SetClipStatus,
    d3d_device7_GetClipStatus,
    d3d_device7_DrawPrimitiveStrided,
    d3d_device7_DrawIndexedPrimitiveStrided,
    d3d_device7_DrawPrimitiveVB,
    d3d_device7_DrawIndexedPrimitiveVB,
    d3d_device7_ComputeSphereVisibility,
    d3d_device7_GetTexture,
    d3d_device7_SetTexture,
    d3d_device7_GetTextureStageState,
    d3d_device7_SetTextureStageState,
    d3d_device7_ValidateDevice,
    d3d_device7_ApplyStateBlock,
    d3d_device7_CaptureStateBlock,
    d3d_device7_DeleteStateBlock,
    d3d_device7_CreateStateBlock,
    d3d_device7_Load,
    d3d_device7_LightEnable,
    d3d_device7_GetLightEnable,
    d3d_device7_SetClipPlane,
    d3d_device7_GetClipPlane,
    d3d_device7_GetInfo
};

static const struct IDirect3DDevice3Vtbl d3d_device3_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_device3_QueryInterface,
    d3d_device3_AddRef,
    d3d_device3_Release,
    /*** IDirect3DDevice3 ***/
    d3d_device3_GetCaps,
    d3d_device3_GetStats,
    d3d_device3_AddViewport,
    d3d_device3_DeleteViewport,
    d3d_device3_NextViewport,
    d3d_device3_EnumTextureFormats,
    d3d_device3_BeginScene,
    d3d_device3_EndScene,
    d3d_device3_GetDirect3D,
    d3d_device3_SetCurrentViewport,
    d3d_device3_GetCurrentViewport,
    d3d_device3_SetRenderTarget,
    d3d_device3_GetRenderTarget,
    d3d_device3_Begin,
    d3d_device3_BeginIndexed,
    d3d_device3_Vertex,
    d3d_device3_Index,
    d3d_device3_End,
    d3d_device3_GetRenderState,
    d3d_device3_SetRenderState,
    d3d_device3_GetLightState,
    d3d_device3_SetLightState,
    d3d_device3_SetTransform,
    d3d_device3_GetTransform,
    d3d_device3_MultiplyTransform,
    d3d_device3_DrawPrimitive,
    d3d_device3_DrawIndexedPrimitive,
    d3d_device3_SetClipStatus,
    d3d_device3_GetClipStatus,
    d3d_device3_DrawPrimitiveStrided,
    d3d_device3_DrawIndexedPrimitiveStrided,
    d3d_device3_DrawPrimitiveVB,
    d3d_device3_DrawIndexedPrimitiveVB,
    d3d_device3_ComputeSphereVisibility,
    d3d_device3_GetTexture,
    d3d_device3_SetTexture,
    d3d_device3_GetTextureStageState,
    d3d_device3_SetTextureStageState,
    d3d_device3_ValidateDevice
};

static const struct IDirect3DDevice2Vtbl d3d_device2_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_device2_QueryInterface,
    d3d_device2_AddRef,
    d3d_device2_Release,
    /*** IDirect3DDevice2 ***/
    d3d_device2_GetCaps,
    d3d_device2_SwapTextureHandles,
    d3d_device2_GetStats,
    d3d_device2_AddViewport,
    d3d_device2_DeleteViewport,
    d3d_device2_NextViewport,
    d3d_device2_EnumTextureFormats,
    d3d_device2_BeginScene,
    d3d_device2_EndScene,
    d3d_device2_GetDirect3D,
    d3d_device2_SetCurrentViewport,
    d3d_device2_GetCurrentViewport,
    d3d_device2_SetRenderTarget,
    d3d_device2_GetRenderTarget,
    d3d_device2_Begin,
    d3d_device2_BeginIndexed,
    d3d_device2_Vertex,
    d3d_device2_Index,
    d3d_device2_End,
    d3d_device2_GetRenderState,
    d3d_device2_SetRenderState,
    d3d_device2_GetLightState,
    d3d_device2_SetLightState,
    d3d_device2_SetTransform,
    d3d_device2_GetTransform,
    d3d_device2_MultiplyTransform,
    d3d_device2_DrawPrimitive,
    d3d_device2_DrawIndexedPrimitive,
    d3d_device2_SetClipStatus,
    d3d_device2_GetClipStatus
};

static const struct IDirect3DDeviceVtbl d3d_device1_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_device1_QueryInterface,
    d3d_device1_AddRef,
    d3d_device1_Release,
    /*** IDirect3DDevice1 ***/
    d3d_device1_Initialize,
    d3d_device1_GetCaps,
    d3d_device1_SwapTextureHandles,
    d3d_device1_CreateExecuteBuffer,
    d3d_device1_GetStats,
    d3d_device1_Execute,
    d3d_device1_AddViewport,
    d3d_device1_DeleteViewport,
    d3d_device1_NextViewport,
    d3d_device1_Pick,
    d3d_device1_GetPickRecords,
    d3d_device1_EnumTextureFormats,
    d3d_device1_CreateMatrix,
    d3d_device1_SetMatrix,
    d3d_device1_GetMatrix,
    d3d_device1_DeleteMatrix,
    d3d_device1_BeginScene,
    d3d_device1_EndScene,
    d3d_device1_GetDirect3D
};

static const struct IUnknownVtbl d3d_device_inner_vtbl =
{
    d3d_device_inner_QueryInterface,
    d3d_device_inner_AddRef,
    d3d_device_inner_Release,
};

struct qemu_device *unsafe_impl_from_IDirect3DDevice7(IDirect3DDevice7 *iface)
{
    if (!iface) return NULL;
    if ((iface->lpVtbl != &d3d_device7_vtbl))
        WINE_ERR("Invalid IDirect3DDevice7 vtable\n");
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice7_iface);
}

struct qemu_device *unsafe_impl_from_IDirect3DDevice3(IDirect3DDevice3 *iface)
{
    if (!iface) return NULL;
    if ((iface->lpVtbl != &d3d_device3_vtbl))
        WINE_ERR("Invalid IDirect3DDevice3 vtable\n");
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice3_iface);
}

struct qemu_device *unsafe_impl_from_IDirect3DDevice2(IDirect3DDevice2 *iface)
{
    if (!iface) return NULL;
    if ((iface->lpVtbl != &d3d_device2_vtbl))
        WINE_ERR("Invalid IDirect3DDevice2 vtable\n");
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice2_iface);
}

struct qemu_device *unsafe_impl_from_IDirect3DDevice(IDirect3DDevice *iface)
{
    if (!iface) return NULL;
    if ((iface->lpVtbl != &d3d_device1_vtbl))
        WINE_ERR("Invalid IDirect3DDevice vtable\n");
    return CONTAINING_RECORD(iface, struct qemu_device, IDirect3DDevice_iface);
}

void ddraw_device_guest_init(struct qemu_device *device, struct qemu_ddraw *ddraw,
        UINT version, IUnknown *rt_iface, IUnknown *outer_unknown)
{
    device->IDirect3DDevice7_iface.lpVtbl = &d3d_device7_vtbl;
    device->IDirect3DDevice3_iface.lpVtbl = &d3d_device3_vtbl;
    device->IDirect3DDevice2_iface.lpVtbl = &d3d_device2_vtbl;
    device->IDirect3DDevice_iface.lpVtbl = &d3d_device1_vtbl;
    device->IUnknown_inner.lpVtbl = &d3d_device_inner_vtbl;
    device->ref = 1;
    device->version = version;

    if (outer_unknown)
        device->outer_unknown = outer_unknown;
    else
        device->outer_unknown = &device->IUnknown_inner;

    device->ddraw = ddraw;
    device->rt_iface = rt_iface;
    if (version != 1)
        IUnknown_AddRef(rt_iface);
}

#endif
