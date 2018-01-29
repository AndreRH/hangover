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
#include <dsound.h>
#include <dsconf.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_dsound.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dsound.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);

struct qemu_capture_buffer
{
    /* Guest fields. */
    IDirectSoundCaptureBuffer8          IDirectSoundCaptureBuffer8_iface;
    IDirectSoundNotify                  IDirectSoundNotify_iface;
    LONG                                iface_count;
    LONG                                ref, refn, has_dsc8;

    /* Host fields. */
    IDirectSoundCaptureBuffer8          *host_buffer;
    IDirectSoundNotify                  *host_notify;
};

struct qemu_IDirectSoundCaptureBufferImpl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_capture_buffer *capture_impl_from_IDirectSoundNotify(IDirectSoundNotify *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_capture_buffer, IDirectSoundNotify_iface);
}

static inline struct qemu_capture_buffer *capture_impl_from_IDirectSoundCaptureBuffer8(IDirectSoundCaptureBuffer8 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_capture_buffer, IDirectSoundCaptureBuffer8_iface);
}

static void capturebuffer_destroy(struct qemu_capture_buffer *buffer)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_RELEASE);
    call.iface = (ULONG_PTR)buffer;
    qemu_syscall(&call.super);
}

static HRESULT WINAPI IDirectSoundNotifyImpl_QueryInterface(IDirectSoundNotify *iface, REFIID riid, void **obj)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundNotify(iface);

    WINE_TRACE("(%p,%s,%p)\n", buffer, wine_dbgstr_guid(riid), obj);

    return IDirectSoundCaptureBuffer_QueryInterface(&buffer->IDirectSoundCaptureBuffer8_iface, riid, obj);
}

static ULONG WINAPI IDirectSoundNotifyImpl_AddRef(IDirectSoundNotify *iface)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundNotify(iface);
    ULONG ref = InterlockedIncrement(&buffer->refn);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

static ULONG WINAPI IDirectSoundNotifyImpl_Release(IDirectSoundNotify *iface)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundNotify(iface);
    ULONG ref = InterlockedDecrement(&buffer->refn);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref + 1);

    if (!ref && !InterlockedDecrement(&buffer->iface_count))
        capturebuffer_destroy(buffer);

    return ref;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_Release(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Release *c = (struct qemu_IDirectSoundCaptureBufferImpl_Release *)call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer8_Release(buffer->host_buffer);
    c->super.iret += IDirectSoundNotify_Release(buffer->host_notify);

    if (c->super.iret)
        WINE_ERR("Unexpected refcount %lu.\n", c->super.iret);

}

#endif

struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t howmuch;
    uint64_t notify;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundNotifyImpl_SetNotificationPositions(IDirectSoundNotify *iface, DWORD howmuch, const DSBPOSITIONNOTIFY *notify)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundNotify(iface);
    struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDNOTIFYIMPL_CAPTURE_SETNOTIFICATIONPOSITIONS);
    call.iface = (ULONG_PTR)buffer;
    call.howmuch = howmuch;
    call.notify = (ULONG_PTR)notify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static const IDirectSoundNotifyVtbl capture_notify_vtbl =
{
    IDirectSoundNotifyImpl_QueryInterface,
    IDirectSoundNotifyImpl_AddRef,
    IDirectSoundNotifyImpl_Release,
    IDirectSoundNotifyImpl_SetNotificationPositions
};

#else

void qemu_IDirectSoundNotifyImpl_Capture_SetNotificationPositions(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions *c = (struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions *)call;
    struct qemu_capture_buffer *buffer;
    DSBPOSITIONNOTIFY *notify;
    struct qemu_DSBPOSITIONNOTIFY *guest_notify;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    notify = QEMU_G2H(c->notify);
#else
    guest_notify = QEMU_G2H(c->notify);
    if (guest_notify)
    {
        unsigned int i;
        notify = alloca(sizeof(*notify) * c->howmuch);
        for (i = 0; i < c->howmuch; i++)
            DSBPOSITIONNOTIFY_g2h(&notify[i], &guest_notify[i]);
    }
    else
    {
        notify = NULL;
    }
#endif

    c->super.iret = IDirectSoundNotify_SetNotificationPositions(buffer->host_notify, c->howmuch, notify);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_QueryInterface(IDirectSoundCaptureBuffer8 *iface, REFIID riid, void **obj)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);

    WINE_TRACE( "(%p,%s,%p)\n", buffer, wine_dbgstr_guid(riid), obj );

    if (obj == NULL)
    {
        WINE_WARN("invalid parameter\n");
        return E_INVALIDARG;
    }

    *obj = NULL;

    if (IsEqualIID(&IID_IUnknown, riid) || IsEqualIID(&IID_IDirectSoundCaptureBuffer, riid) ||
            (buffer->has_dsc8 && IsEqualIID(&IID_IDirectSoundCaptureBuffer8, riid)))
    {
        IDirectSoundCaptureBuffer8_AddRef(iface);
        *obj = iface;
        return S_OK;
    }

    if (IsEqualGUID( &IID_IDirectSoundNotify, riid ))
    {
        IDirectSoundNotify_AddRef(&buffer->IDirectSoundNotify_iface);
        *obj = &buffer->IDirectSoundNotify_iface;
        return S_OK;
    }

    WINE_FIXME("(%p,%s,%p) unsupported GUID\n", buffer, wine_dbgstr_guid(riid), obj);
    return E_NOINTERFACE;
}

static ULONG WINAPI IDirectSoundCaptureBufferImpl_AddRef(IDirectSoundCaptureBuffer8 *iface)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    ULONG ref = InterlockedIncrement(&buffer->ref);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

static ULONG WINAPI IDirectSoundCaptureBufferImpl_Release(IDirectSoundCaptureBuffer8 *iface)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    ULONG ref = InterlockedDecrement(&buffer->ref);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref + 1);

    if (!ref && !InterlockedDecrement(&buffer->iface_count))
        capturebuffer_destroy(buffer);

    return ref;
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDSCBCaps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_GetCaps(IDirectSoundCaptureBuffer8 *iface, DSCBCAPS *lpDSCBCaps)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETCAPS);
    call.iface = (ULONG_PTR)buffer;
    call.lpDSCBCaps = (ULONG_PTR)lpDSCBCaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_GetCaps(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_GetCaps *c = (struct qemu_IDirectSoundCaptureBufferImpl_GetCaps *)call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_GetCaps(buffer->host_buffer, QEMU_G2H(c->lpDSCBCaps));
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_GetCurrentPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdwCapturePosition;
    uint64_t lpdwReadPosition;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_GetCurrentPosition(IDirectSoundCaptureBuffer8 *iface, DWORD *lpdwCapturePosition, DWORD *lpdwReadPosition)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_GetCurrentPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETCURRENTPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.lpdwCapturePosition = (ULONG_PTR)lpdwCapturePosition;
    call.lpdwReadPosition = (ULONG_PTR)lpdwReadPosition;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_GetCurrentPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_GetCurrentPosition *c = (struct qemu_IDirectSoundCaptureBufferImpl_GetCurrentPosition *)call;
    struct qemu_capture_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_GetCurrentPosition(buffer->host_buffer, QEMU_G2H(c->lpdwCapturePosition), QEMU_G2H(c->lpdwReadPosition));
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_GetFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpwfxFormat;
    uint64_t dwSizeAllocated;
    uint64_t lpdwSizeWritten;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_GetFormat(IDirectSoundCaptureBuffer8 *iface, WAVEFORMATEX *lpwfxFormat, DWORD dwSizeAllocated, DWORD *lpdwSizeWritten)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_GetFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETFORMAT);
    call.iface = (ULONG_PTR)buffer;
    call.lpwfxFormat = (ULONG_PTR)lpwfxFormat;
    call.dwSizeAllocated = dwSizeAllocated;
    call.lpdwSizeWritten = (ULONG_PTR)lpdwSizeWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_GetFormat(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_GetFormat *c = (struct qemu_IDirectSoundCaptureBufferImpl_GetFormat *)call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_GetFormat(buffer->host_buffer, QEMU_G2H(c->lpwfxFormat), c->dwSizeAllocated, QEMU_G2H(c->lpdwSizeWritten));
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_GetStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdwStatus;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_GetStatus(IDirectSoundCaptureBuffer8 *iface, DWORD *lpdwStatus)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_GetStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETSTATUS);
    call.iface = (ULONG_PTR)buffer;
    call.lpdwStatus = (ULONG_PTR)lpdwStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_GetStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_GetStatus *c = (struct qemu_IDirectSoundCaptureBufferImpl_GetStatus *)call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_GetStatus(buffer->host_buffer, QEMU_G2H(c->lpdwStatus));
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDSC;
    uint64_t lpcDSCBDesc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_Initialize(IDirectSoundCaptureBuffer8 *iface, IDirectSoundCapture *lpDSC, const DSCBUFFERDESC *lpcDSCBDesc)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)buffer;
    call.lpDSC = (ULONG_PTR)lpDSC;
    call.lpcDSCBDesc = (ULONG_PTR)lpcDSCBDesc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Initialize *c = (struct qemu_IDirectSoundCaptureBufferImpl_Initialize *)call;
    struct qemu_capture_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_Initialize(buffer->host_buffer, QEMU_G2H(c->lpDSC), QEMU_G2H(c->lpcDSCBDesc));
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwReadCusor;
    uint64_t dwReadBytes;
    uint64_t lplpvAudioPtr1;
    uint64_t lpdwAudioBytes1;
    uint64_t lplpvAudioPtr2;
    uint64_t lpdwAudioBytes2;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_Lock(IDirectSoundCaptureBuffer8 *iface, DWORD dwReadCusor,
            DWORD dwReadBytes, void **lplpvAudioPtr1, DWORD *lpdwAudioBytes1, void **lplpvAudioPtr2,
            DWORD *lpdwAudioBytes2, DWORD dwFlags)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_Lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_LOCK);
    call.iface = (ULONG_PTR)buffer;
    call.dwReadCusor = dwReadCusor;
    call.dwReadBytes = dwReadBytes;
    call.lplpvAudioPtr1 = (ULONG_PTR)lplpvAudioPtr1;
    call.lpdwAudioBytes1 = (ULONG_PTR)lpdwAudioBytes1;
    call.lplpvAudioPtr2 = (ULONG_PTR)lplpvAudioPtr2;
    call.lpdwAudioBytes2 = (ULONG_PTR)lpdwAudioBytes2;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        *lplpvAudioPtr1 = (void *)(ULONG_PTR)call.lplpvAudioPtr1;
        if (lplpvAudioPtr2)
            *lplpvAudioPtr2 = (void *)(ULONG_PTR)call.lplpvAudioPtr2;
    }

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_Lock(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Lock *c = (struct qemu_IDirectSoundCaptureBufferImpl_Lock *)call;
    struct qemu_capture_buffer *buffer;
    void *ptr1, *ptr2;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_Lock(buffer->host_buffer, c->dwReadCusor, c->dwReadBytes, &ptr1,
            QEMU_G2H(c->lpdwAudioBytes1), &ptr2, QEMU_G2H(c->lpdwAudioBytes2), c->dwFlags);

    c->lplpvAudioPtr1 = QEMU_H2G(ptr1);
    c->lplpvAudioPtr2 = QEMU_H2G(ptr2);
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_Start
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_Start(IDirectSoundCaptureBuffer8 *iface, DWORD dwFlags)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_Start call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_START);
    call.iface = (ULONG_PTR)buffer;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_Start(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Start *c = (struct qemu_IDirectSoundCaptureBufferImpl_Start *)call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_Start(buffer->host_buffer, c->dwFlags);
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_Stop
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_Stop(IDirectSoundCaptureBuffer8 *iface)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_Stop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_STOP);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_Stop(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Stop *c = (struct qemu_IDirectSoundCaptureBufferImpl_Stop *)call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_Stop(buffer->host_buffer);
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvAudioPtr1;
    uint64_t dwAudioBytes1;
    uint64_t lpvAudioPtr2;
    uint64_t dwAudioBytes2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_Unlock(IDirectSoundCaptureBuffer8 *iface, void *lpvAudioPtr1, DWORD dwAudioBytes1, void *lpvAudioPtr2, DWORD dwAudioBytes2)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_Unlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_UNLOCK);
    call.iface = (ULONG_PTR)buffer;
    call.lpvAudioPtr1 = (ULONG_PTR)lpvAudioPtr1;
    call.dwAudioBytes1 = dwAudioBytes1;
    call.lpvAudioPtr2 = (ULONG_PTR)lpvAudioPtr2;
    call.dwAudioBytes2 = dwAudioBytes2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_Unlock(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_Unlock *c = (struct qemu_IDirectSoundCaptureBufferImpl_Unlock *)call;
    struct qemu_capture_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer_Unlock(buffer->host_buffer, QEMU_G2H(c->lpvAudioPtr1), c->dwAudioBytes1, QEMU_G2H(c->lpvAudioPtr2), c->dwAudioBytes2);
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_GetObjectInPath
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguidObject;
    uint64_t dwIndex;
    uint64_t rguidInterface;
    uint64_t ppObject;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_GetObjectInPath(IDirectSoundCaptureBuffer8 *iface, REFGUID rguidObject, DWORD dwIndex, REFGUID rguidInterface, void **ppObject)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_GetObjectInPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETOBJECTINPATH);
    call.iface = (ULONG_PTR)buffer;
    call.rguidObject = (ULONG_PTR)rguidObject;
    call.dwIndex = dwIndex;
    call.rguidInterface = (ULONG_PTR)rguidInterface;
    call.ppObject = (ULONG_PTR)ppObject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureBufferImpl_GetObjectInPath(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_GetObjectInPath *c = (struct qemu_IDirectSoundCaptureBufferImpl_GetObjectInPath *)call;
    struct qemu_capture_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer8_GetObjectInPath(buffer->host_buffer, QEMU_G2H(c->rguidObject), c->dwIndex, QEMU_G2H(c->rguidInterface), QEMU_G2H(c->ppObject));
}

#endif

struct qemu_IDirectSoundCaptureBufferImpl_GetFXStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwFXCount;
    uint64_t pdwFXStatus;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureBufferImpl_GetFXStatus(IDirectSoundCaptureBuffer8 *iface, DWORD dwFXCount, DWORD *pdwFXStatus)
{
    struct qemu_capture_buffer *buffer = capture_impl_from_IDirectSoundCaptureBuffer8(iface);
    struct qemu_IDirectSoundCaptureBufferImpl_GetFXStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETFXSTATUS);
    call.iface = (ULONG_PTR)buffer;
    call.dwFXCount = dwFXCount;
    call.pdwFXStatus = (ULONG_PTR)pdwFXStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static const IDirectSoundCaptureBuffer8Vtbl capture_buffer_vtbl =
{
    /* IUnknown methods */
    IDirectSoundCaptureBufferImpl_QueryInterface,
    IDirectSoundCaptureBufferImpl_AddRef,
    IDirectSoundCaptureBufferImpl_Release,

    /* IDirectSoundCaptureBuffer methods */
    IDirectSoundCaptureBufferImpl_GetCaps,
    IDirectSoundCaptureBufferImpl_GetCurrentPosition,
    IDirectSoundCaptureBufferImpl_GetFormat,
    IDirectSoundCaptureBufferImpl_GetStatus,
    IDirectSoundCaptureBufferImpl_Initialize,
    IDirectSoundCaptureBufferImpl_Lock,
    IDirectSoundCaptureBufferImpl_Start,
    IDirectSoundCaptureBufferImpl_Stop,
    IDirectSoundCaptureBufferImpl_Unlock,

    /* IDirectSoundCaptureBuffer methods */
    IDirectSoundCaptureBufferImpl_GetObjectInPath,
    IDirectSoundCaptureBufferImpl_GetFXStatus
};

#else

void qemu_IDirectSoundCaptureBufferImpl_GetFXStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureBufferImpl_GetFXStatus *c = (struct qemu_IDirectSoundCaptureBufferImpl_GetFXStatus *)call;
    struct qemu_capture_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCaptureBuffer8_GetFXStatus(buffer->host_buffer, c->dwFXCount, QEMU_G2H(c->pdwFXStatus));
}

#endif

struct qemu_capture
{
    /* Guest fields */
    IUnknown                IUnknown_inner;
    IDirectSoundCapture     IDirectSoundCapture_iface;
    LONG                    ref, refdsc, iface_count;
    IUnknown                 *outer_unk;
    BOOL                    has_dsc8;

    /* Host fields */
    IDirectSoundCapture     *host;
};

struct qemu_IDirectSoundCaptureImpl_Release
{
    struct qemu_syscall super;
    uint64_t capture;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_capture *impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_capture, IUnknown_inner);
}

static inline struct qemu_capture *impl_from_IDirectSoundCapture(IDirectSoundCapture *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_capture, IDirectSoundCapture_iface);
}

static void capture_destroy(struct qemu_capture *capture)
{
    struct qemu_IDirectSoundCaptureImpl_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREIMPL_RELEASE);
    call.capture = (ULONG_PTR)capture;
    qemu_syscall(&call.super);
}

static HRESULT WINAPI IUnknownImpl_QueryInterface(IUnknown *iface, REFIID riid, void **ppv)
{
    struct qemu_capture *capture = impl_from_IUnknown(iface);

    WINE_TRACE("(%p,%s,%p)\n", capture, wine_dbgstr_guid(riid), ppv);

    if (!ppv)
    {
        WINE_WARN("invalid parameter\n");
        return E_INVALIDARG;
    }
    *ppv = NULL;

    if (IsEqualIID(riid, &IID_IUnknown))
        *ppv = &capture->IUnknown_inner;
    else if (IsEqualIID(riid, &IID_IDirectSoundCapture))
        *ppv = &capture->IDirectSoundCapture_iface;
    else
    {
        WINE_WARN("unknown IID %s\n", wine_dbgstr_guid(riid));
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI IUnknownImpl_AddRef(IUnknown *iface)
{
    struct qemu_capture *capture = impl_from_IUnknown(iface);
    ULONG ref = InterlockedIncrement(&capture->ref);

    WINE_TRACE("(%p) ref=%d\n", capture, ref);

    if(ref == 1)
        InterlockedIncrement(&capture->iface_count);
    return ref;
}

static ULONG WINAPI IUnknownImpl_Release(IUnknown *iface)
{
    struct qemu_capture *capture = impl_from_IUnknown(iface);
    ULONG ref = InterlockedDecrement(&capture->ref);

    WINE_TRACE("(%p) ref=%d\n", capture, ref);

    if (!ref && !InterlockedDecrement(&capture->iface_count))
        capture_destroy(capture);
    return ref;
}

static const IUnknownVtbl inner_unknown_vtbl =
{
    IUnknownImpl_QueryInterface,
    IUnknownImpl_AddRef,
    IUnknownImpl_Release
};

static HRESULT WINAPI IDirectSoundCaptureImpl_QueryInterface(IDirectSoundCapture *iface, REFIID riid, void **obj)
{
    struct qemu_capture *capture = impl_from_IDirectSoundCapture(iface);
    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(riid), obj);
    return IUnknown_QueryInterface(capture->outer_unk, riid, obj);
}

static ULONG WINAPI IDirectSoundCaptureImpl_AddRef(IDirectSoundCapture *iface)
{
    struct qemu_capture *capture = impl_from_IDirectSoundCapture(iface);
    ULONG ref = InterlockedIncrement(&capture->refdsc);

    WINE_TRACE("(%p) ref=%d\n", capture, ref);

    if(ref == 1)
        InterlockedIncrement(&capture->iface_count);
    return ref;
}

static ULONG WINAPI IDirectSoundCaptureImpl_Release(IDirectSoundCapture *iface)
{
    struct qemu_capture *capture = impl_from_IDirectSoundCapture(iface);
    ULONG ref = InterlockedDecrement(&capture->refdsc);

    WINE_TRACE("(%p) ref=%d\n", capture, ref);

    if (!ref && !InterlockedDecrement(&capture->iface_count))
        capture_destroy(capture);
    return ref;
}

#else

void qemu_IDirectSoundCaptureImpl_Release(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureImpl_Release *c = (struct qemu_IDirectSoundCaptureImpl_Release *)call;
    struct qemu_capture *capture;

    WINE_TRACE("\n");
    capture = QEMU_G2H(c->capture);

    c->super.iret = IDirectSoundCapture_Release(capture->host);
    if (c->super.iret)
        WINE_ERR("Got unexpected host refcount %lu\n", c->super.iret);
}

#endif

struct qemu_IDirectSoundCaptureImpl_CreateCaptureBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureImpl_CreateCaptureBuffer(IDirectSoundCapture *iface,
        const DSCBUFFERDESC *desc, IDirectSoundCaptureBuffer **out, IUnknown *outer_unknown)
{
    struct qemu_capture *capture = impl_from_IDirectSoundCapture(iface);
    struct qemu_IDirectSoundCaptureImpl_CreateCaptureBuffer call;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE( "(%p,%p,%p,%p)\n", capture, desc, out, outer_unknown);

    if (outer_unknown)
    {
        WINE_WARN("invalid parameter: outer_unknown != NULL\n");
        return DSERR_NOAGGREGATION;
    }

    if (desc == NULL)
    {
        WINE_WARN("invalid parameter: desc == NULL)\n");
        return DSERR_INVALIDPARAM;
    }

    if (out == NULL)
    {
        WINE_WARN("invalid parameter: out == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREIMPL_CREATECAPTUREBUFFER);
    call.iface = (ULONG_PTR)capture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *out = NULL;
        return call.super.iret;
    }

    buffer = (struct qemu_capture_buffer *)(ULONG_PTR)call.buffer;
    buffer->IDirectSoundCaptureBuffer8_iface.lpVtbl = &capture_buffer_vtbl;
    buffer->IDirectSoundNotify_iface.lpVtbl = &capture_notify_vtbl;
    buffer->ref = buffer->iface_count = 1;
    buffer->has_dsc8 = capture->has_dsc8;

    *out = (IDirectSoundCaptureBuffer *)&buffer->IDirectSoundCaptureBuffer8_iface;

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureImpl_CreateCaptureBuffer(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureImpl_CreateCaptureBuffer *c = (struct qemu_IDirectSoundCaptureImpl_CreateCaptureBuffer *)call;
    struct qemu_capture *capture;
    DSCBUFFERDESC stack, *desc = &stack;
    struct qemu_capture_buffer *buffer;

    WINE_TRACE("\n");
    capture = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    desc = QEMU_G2H(c->desc);
#else
    DSCBUFFERDESC_g2h(desc, QEMU_G2H(c->desc));
#endif

    buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*buffer));
    if (!buffer)
    {
        c->super.iret = DSERR_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirectSoundCapture_CreateCaptureBuffer(capture->host, desc,
            (IDirectSoundCaptureBuffer **)&buffer->host_buffer, NULL);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, buffer);
        return;
    }

    IDirectSoundCaptureBuffer8_QueryInterface(buffer->host_buffer,
            &IID_IDirectSoundNotify, (void **)&buffer->host_notify);
    if (!buffer->host_notify)
        WINE_ERR("Failed to get notify interface of host buffer.\n");

    c->buffer = QEMU_H2G(buffer);
}

#endif

struct qemu_IDirectSoundCaptureImpl_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureImpl_GetCaps(IDirectSoundCapture *iface, DSCCAPS *caps)
{
    struct qemu_capture *capture = impl_from_IDirectSoundCapture(iface);
    struct qemu_IDirectSoundCaptureImpl_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREIMPL_GETCAPS);
    call.iface = (ULONG_PTR)capture;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundCaptureImpl_GetCaps(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureImpl_GetCaps *c = (struct qemu_IDirectSoundCaptureImpl_GetCaps *)call;
    struct qemu_capture *capture;

    /* DSCCAPS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    capture = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCapture_GetCaps(capture->host, QEMU_G2H(c->caps));
}

#endif

struct qemu_IDirectSoundCaptureImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundCaptureImpl_Initialize(IDirectSoundCapture *iface, const GUID *guid)
{
    struct qemu_capture *capture = impl_from_IDirectSoundCapture(iface);
    struct qemu_IDirectSoundCaptureImpl_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDCAPTUREIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)capture;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static const IDirectSoundCaptureVtbl capture_vtbl =
{
    /* IUnknown methods */
    IDirectSoundCaptureImpl_QueryInterface,
    IDirectSoundCaptureImpl_AddRef,
    IDirectSoundCaptureImpl_Release,

    /* IDirectSoundCapture methods */
    IDirectSoundCaptureImpl_CreateCaptureBuffer,
    IDirectSoundCaptureImpl_GetCaps,
    IDirectSoundCaptureImpl_Initialize
};

#else

void qemu_IDirectSoundCaptureImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundCaptureImpl_Initialize *c = (struct qemu_IDirectSoundCaptureImpl_Initialize *)call;
    struct qemu_capture *capture;

    WINE_TRACE("\n");
    capture = QEMU_G2H(c->iface);

    c->super.iret = IDirectSoundCapture_Initialize(capture->host, QEMU_G2H(c->guid));
}

#endif

struct qemu_DirectSoundCaptureCreate
{
    struct qemu_syscall super;
    uint64_t has_dsc8;
    uint64_t capture;
};

#ifdef QEMU_DLL_GUEST

HRESULT IDirectSoundCaptureImpl_Create(IUnknown *outer_unk, REFIID riid, void **out, BOOL has_dsc8)
{
    struct qemu_DirectSoundCaptureCreate call;
    struct qemu_capture *capture;
    HRESULT hr;
    WINE_TRACE("(%s, %p)\n", wine_dbgstr_guid(riid), out);

    *out = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDCAPTURECREATE);
    call.has_dsc8 = has_dsc8;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    capture = (struct qemu_capture *)(ULONG_PTR)call.capture;

    capture->IUnknown_inner.lpVtbl = &inner_unknown_vtbl;
    capture->IDirectSoundCapture_iface.lpVtbl = &capture_vtbl;
    capture->ref = 1;
    capture->refdsc = 0;
    capture->iface_count = 1;
    capture->has_dsc8 = has_dsc8;

    /* COM aggregation supported only internally */
    if (outer_unk)
        capture->outer_unk = outer_unk;
    else
        capture->outer_unk = &capture->IUnknown_inner;

    hr = IUnknown_QueryInterface(&capture->IUnknown_inner, riid, out);
    IUnknown_Release(&capture->IUnknown_inner);

    return hr;
}

HRESULT DSOUND_CaptureCreate(REFIID riid, void **obj)
{
    return IDirectSoundCaptureImpl_Create(NULL, riid, obj, FALSE);
}

HRESULT DSOUND_CaptureCreate8(REFIID riid, void **obj)
{
    return IDirectSoundCaptureImpl_Create(NULL, riid, obj, TRUE);
}

WINBASEAPI HRESULT WINAPI DirectSoundCaptureCreate(LPCGUID guid, IDirectSoundCapture **obj, IUnknown *unk_outer)
{
    HRESULT hr;
    IDirectSoundCapture *capture;

    WINE_TRACE("(%s,%p,%p)\n", wine_dbgstr_guid(guid), obj, unk_outer);

    if (obj == NULL)
    {
        WINE_WARN("invalid parameter: obj == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (unk_outer)
    {
        WINE_WARN("invalid parameter: unk_outer != NULL\n");
        return DSERR_NOAGGREGATION;
    }

    hr = DSOUND_CaptureCreate(&IID_IDirectSoundCapture, (void**)&capture);
    if (hr == DS_OK)
    {
        hr = IDirectSoundCapture_Initialize(capture, guid);
        if (hr != DS_OK)
        {
            IDirectSoundCapture_Release(capture);
            capture = NULL;
        }
    }

    *obj = capture;

    return hr;
}

WINBASEAPI HRESULT WINAPI DirectSoundCaptureCreate8(const GUID *guid, IDirectSoundCapture8 **obj, IUnknown *unk_outer)
{
    HRESULT hr;
    IDirectSoundCapture8 *capture;
    WINE_TRACE("(%s,%p,%p)\n", wine_dbgstr_guid(guid), obj, unk_outer);

    if (obj == NULL)
    {
        WINE_WARN("invalid parameter: obj == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (unk_outer)
    {
        WINE_WARN("invalid parameter: unk_outer != NULL\n");
        *obj = NULL;
        return DSERR_NOAGGREGATION;
    }

    hr = DSOUND_CaptureCreate8(&IID_IDirectSoundCapture8, (void**)&capture);
    if (hr == DS_OK)
    {
        hr = IDirectSoundCapture_Initialize(capture, guid);
        if (hr != DS_OK)
        {
            IDirectSoundCapture_Release(capture);
            capture = NULL;
        }
    }

    *obj = capture;

    return hr;
}

#else

void qemu_DirectSoundCaptureCreate(struct qemu_syscall *call)
{
    struct qemu_DirectSoundCaptureCreate *c = (struct qemu_DirectSoundCaptureCreate *)call;
    struct qemu_capture *capture;
    HRESULT hr;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *factory;
    WINE_TRACE("\n");

    c->capture = 0;

    /* Because we copypasted the init code from Wine we'll call Initialize with the
     * desired device GUID later. Don't call DirectSoundCaptureCreate here and instead
     * use CoCreateInstance to create an uninitialized object. We also need to be able
     * to create uninitialized devices if the guest calls us through CoCreateInstance.
     *
     * Except that we can't use CoCreateInstance because the host-side ole32 is
     * probably not initialized. So navigate out way through DllGetClassObject like
     * ole32 would. */
    lib = GetModuleHandleA("dsound");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(c->has_dsc8 ? &CLSID_DirectSoundCapture8 : &CLSID_DirectSoundCapture,
            &IID_IClassFactory, (void *)&factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    capture = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*capture));
    if (!capture)
    {
        WINE_WARN("Out of memory.\n");
        c->super.iret = DSERR_OUTOFMEMORY;
        IClassFactory_Release(factory);
        return;
    }

    hr = IClassFactory_CreateInstance(factory, NULL,
            c->has_dsc8 ? &IID_IDirectSoundCapture8 : &IID_IDirectSoundCapture, (void **)&capture->host);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IDirectSoundCapture%s object.\n", c->has_dsc8 ? "8" : "");
        HeapFree(GetProcessHeap(), 0, capture);
        capture = NULL;
    }

    c->capture = QEMU_H2G(capture);
    c->super.iret = hr;
    IClassFactory_Release(factory);
}

#endif

