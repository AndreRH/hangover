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

struct qemu_IDirectSoundBufferImpl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

void secondarybuffer_destroy(struct qemu_dsound_buffer *buffer)
{
    struct qemu_IDirectSoundBufferImpl_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_RELEASE);
    call.iface = (ULONG_PTR)buffer;
    qemu_syscall(&call.super);
}

static HRESULT WINAPI IDirectSoundNotifyImpl_QueryInterface(IDirectSoundNotify *iface, REFIID riid, void **obj)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundNotify(iface);

    WINE_TRACE("(%p,%s,%p)\n", buffer, wine_dbgstr_guid(riid), obj);

    return IDirectSoundBuffer8_QueryInterface(&buffer->IDirectSoundBuffer8_iface, riid, obj);
}

static ULONG WINAPI IDirectSoundNotifyImpl_AddRef(IDirectSoundNotify *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundNotify(iface);
    ULONG ref = InterlockedIncrement(&buffer->refn);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

static ULONG WINAPI IDirectSoundNotifyImpl_Release(IDirectSoundNotify *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundNotify(iface);
    ULONG ref = InterlockedDecrement(&buffer->refn);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref + 1);

    if (!ref && !InterlockedDecrement(&buffer->iface_count))
        secondarybuffer_destroy(buffer);

    return ref;
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
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundNotify(iface);
    struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDNOTIFYIMPL_SETNOTIFICATIONPOSITIONS);
    call.iface = (ULONG_PTR)buffer;
    call.howmuch = howmuch;
    call.notify = (ULONG_PTR)notify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundNotifyImpl_SetNotificationPositions(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions *c = (struct qemu_IDirectSoundNotifyImpl_SetNotificationPositions *)call;
    struct qemu_dsound_buffer *buffer;
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

struct qemu_IDirectSoundBufferImpl_SetFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t wfex;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_SetFormat(IDirectSoundBuffer8 *iface, const WAVEFORMATEX *wfex)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_SetFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_SETFORMAT);
    call.iface = (ULONG_PTR)buffer;
    call.wfex = (ULONG_PTR)wfex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_SetFormat(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_SetFormat *c = (struct qemu_IDirectSoundBufferImpl_SetFormat *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    /* WAVEFORMATEX has the same size in 32 and 64 bit. */
    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_SetFormat(buffer->host_buffer, QEMU_G2H(c->wfex));
}

#endif

struct qemu_IDirectSoundBufferImpl_SetVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vol;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_SetVolume(IDirectSoundBuffer8 *iface, LONG vol)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_SetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_SETVOLUME);
    call.iface = (ULONG_PTR)buffer;
    call.vol = vol;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_SetVolume(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_SetVolume *c = (struct qemu_IDirectSoundBufferImpl_SetVolume *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_SetVolume(buffer->host_buffer, c->vol);
}

#endif

struct qemu_IDirectSoundBufferImpl_GetVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vol;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetVolume(IDirectSoundBuffer8 *iface, LONG *vol)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETVOLUME);
    call.iface = (ULONG_PTR)buffer;
    call.vol = (ULONG_PTR)vol;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetVolume(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetVolume *c = (struct qemu_IDirectSoundBufferImpl_GetVolume *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetVolume(buffer->host_buffer, QEMU_G2H(c->vol));
}

#endif

struct qemu_IDirectSoundBufferImpl_SetFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t freq;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_SetFrequency(IDirectSoundBuffer8 *iface, DWORD freq)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_SetFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_SETFREQUENCY);
    call.iface = (ULONG_PTR)buffer;
    call.freq = freq;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_SetFrequency(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_SetFrequency *c = (struct qemu_IDirectSoundBufferImpl_SetFrequency *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_SetFrequency(buffer->host_buffer, c->freq);
}

#endif

struct qemu_IDirectSoundBufferImpl_Play
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reserved1;
    uint64_t reserved2;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_Play(IDirectSoundBuffer8 *iface, DWORD reserved1, DWORD reserved2, DWORD flags)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_Play call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_PLAY);
    call.iface = (ULONG_PTR)buffer;
    call.reserved1 = reserved1;
    call.reserved2 = reserved2;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_Play(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Play *c = (struct qemu_IDirectSoundBufferImpl_Play *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Play(buffer->host_buffer, c->reserved1, c->reserved2, c->flags);
}

#endif

struct qemu_IDirectSoundBufferImpl_Stop
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_Stop(IDirectSoundBuffer8 *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_Stop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_STOP);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_Stop(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Stop *c = (struct qemu_IDirectSoundBufferImpl_Stop *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Stop(buffer->host_buffer);
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IDirectSoundBufferImpl_AddRef(IDirectSoundBuffer8 *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    ULONG ref = InterlockedIncrement(&buffer->ref);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

static inline BOOL is_primary_buffer(struct qemu_dsound_buffer *buffer)
{
    return (buffer->flags & DSBCAPS_PRIMARYBUFFER) != 0;
}

LONG capped_refcount_dec(LONG *out)
{
    LONG ref, oldref;
    do
    {
        ref = *out;
        if(!ref)
            return 0;
        oldref = InterlockedCompareExchange(out, ref - 1, ref);
    } while(oldref != ref);

    return ref - 1;
}

static ULONG WINAPI IDirectSoundBufferImpl_Release(IDirectSoundBuffer8 *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    ULONG ref;

    if (is_primary_buffer(buffer))
    {
        ref = capped_refcount_dec(&buffer->ref);
        if(!ref)
            capped_refcount_dec(&buffer->iface_count);
        WINE_TRACE("(%p) ref is now: %u\n", buffer, ref);
        return ref;
    }

    ref = InterlockedDecrement(&buffer->ref);
    if (!ref && !InterlockedDecrement(&buffer->iface_count))
            secondarybuffer_destroy(buffer);

    WINE_TRACE("(%p) ref is now %d\n", buffer, ref);

    return ref;
}

#else

void qemu_IDirectSoundBufferImpl_Release(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Release *c = (struct qemu_IDirectSoundBufferImpl_Release *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Release(buffer->host_buffer);
    if (buffer->host_notify)
        c->super.iret += IDirectSoundNotify_Release(buffer->host_notify);
    if (buffer->host_3d_listener)
        c->super.iret += IDirectSound3DListener_Release(buffer->host_3d_listener);
    if (buffer->host_3d_buffer)
        c->super.iret += IDirectSound3DBuffer_Release(buffer->host_3d_buffer);
    if (buffer->host_property)
        c->super.iret += IKsPropertySet_Release(buffer->host_property);

    WINE_TRACE("Host interface count sum is %lu.\n", c->super.iret);
    if (c->super.iret)
        WINE_FIXME("Host interfaces not cleanly released\n");

    HeapFree(GetProcessHeap(), 0, buffer);
}

#endif

struct qemu_IDirectSoundBufferImpl_GetCurrentPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t playpos;
    uint64_t writepos;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetCurrentPosition(IDirectSoundBuffer8 *iface, DWORD *playpos, DWORD *writepos)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetCurrentPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETCURRENTPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.playpos = (ULONG_PTR)playpos;
    call.writepos = (ULONG_PTR)writepos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetCurrentPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetCurrentPosition *c = (struct qemu_IDirectSoundBufferImpl_GetCurrentPosition *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetCurrentPosition(buffer->host_buffer, QEMU_G2H(c->playpos), QEMU_G2H(c->writepos));
}

#endif

struct qemu_IDirectSoundBufferImpl_GetStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetStatus(IDirectSoundBuffer8 *iface, DWORD *status)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETSTATUS);
    call.iface = (ULONG_PTR)buffer;
    call.status = (ULONG_PTR)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetStatus *c = (struct qemu_IDirectSoundBufferImpl_GetStatus *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetStatus(buffer->host_buffer, QEMU_G2H(c->status));
}

#endif

struct qemu_IDirectSoundBufferImpl_GetFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpwf;
    uint64_t wfsize;
    uint64_t wfwritten;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetFormat(IDirectSoundBuffer8 *iface, LPWAVEFORMATEX lpwf,
        DWORD wfsize, DWORD *wfwritten)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETFORMAT);
    call.iface = (ULONG_PTR)buffer;
    call.lpwf = (ULONG_PTR)lpwf;
    call.wfsize = wfsize;
    call.wfwritten = (ULONG_PTR)wfwritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetFormat(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetFormat *c = (struct qemu_IDirectSoundBufferImpl_GetFormat *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetFormat(buffer->host_buffer, QEMU_G2H(c->lpwf), c->wfsize, QEMU_G2H(c->wfwritten));
}

#endif

struct qemu_IDirectSoundBufferImpl_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t writecursor;
    uint64_t writebytes;
    uint64_t lplpaudioptr1;
    uint64_t audiobytes1;
    uint64_t lplpaudioptr2;
    uint64_t audiobytes2;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_Lock(IDirectSoundBuffer8 *iface, DWORD writecursor, DWORD writebytes,
        void **lplpaudioptr1, DWORD *audiobytes1, void **lplpaudioptr2, DWORD *audiobytes2, DWORD flags)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_Lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_LOCK);
    call.iface = (ULONG_PTR)buffer;
    call.writecursor = writecursor;
    call.writebytes = writebytes;
    call.audiobytes1 = (ULONG_PTR)audiobytes1;
    call.audiobytes2 = (ULONG_PTR)audiobytes2;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        *lplpaudioptr1 = (void *)(ULONG_PTR)call.lplpaudioptr1;
        if (lplpaudioptr2)
            *lplpaudioptr2 = (void *)(ULONG_PTR)call.lplpaudioptr2;
    }

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_Lock(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Lock *c = (struct qemu_IDirectSoundBufferImpl_Lock *)call;
    struct qemu_dsound_buffer *buffer;
    void *ptr1, *ptr2;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Lock(buffer->host_buffer, c->writecursor, c->writebytes,
            &ptr1, QEMU_G2H(c->audiobytes1), &ptr2, QEMU_G2H(c->audiobytes2), c->flags);

    c->lplpaudioptr1 = QEMU_H2G(ptr1);
    c->lplpaudioptr2 = QEMU_H2G(ptr2);
}

#endif

struct qemu_IDirectSoundBufferImpl_SetCurrentPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t newpos;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_SetCurrentPosition(IDirectSoundBuffer8 *iface, DWORD newpos)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_SetCurrentPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_SETCURRENTPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.newpos = newpos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_SetCurrentPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_SetCurrentPosition *c = (struct qemu_IDirectSoundBufferImpl_SetCurrentPosition *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_SetCurrentPosition(buffer->host_buffer, c->newpos);
}

#endif

struct qemu_IDirectSoundBufferImpl_SetPan
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pan;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_SetPan(IDirectSoundBuffer8 *iface, LONG pan)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_SetPan call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_SETPAN);
    call.iface = (ULONG_PTR)buffer;
    call.pan = pan;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_SetPan(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_SetPan *c = (struct qemu_IDirectSoundBufferImpl_SetPan *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_SetPan(buffer->host_buffer, c->pan);
}

#endif

struct qemu_IDirectSoundBufferImpl_GetPan
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pan;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetPan(IDirectSoundBuffer8 *iface, LONG *pan)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetPan call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETPAN);
    call.iface = (ULONG_PTR)buffer;
    call.pan = (ULONG_PTR)pan;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetPan(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetPan *c = (struct qemu_IDirectSoundBufferImpl_GetPan *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetPan(buffer->host_buffer, QEMU_G2H(c->pan));
}

#endif

struct qemu_IDirectSoundBufferImpl_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t p1;
    uint64_t x1;
    uint64_t p2;
    uint64_t x2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_Unlock(IDirectSoundBuffer8 *iface, void *p1, DWORD x1, void *p2, DWORD x2)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_Unlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_UNLOCK);
    call.iface = (ULONG_PTR)buffer;
    call.p1 = (ULONG_PTR)p1;
    call.x1 = x1;
    call.p2 = (ULONG_PTR)p2;
    call.x2 = x2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_Unlock(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Unlock *c = (struct qemu_IDirectSoundBufferImpl_Unlock *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Unlock(buffer->host_buffer, QEMU_G2H(c->p1), c->x1, QEMU_G2H(c->p2), c->x2);
}

#endif

struct qemu_IDirectSoundBufferImpl_Restore
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_Restore(IDirectSoundBuffer8 *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_Restore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_RESTORE);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_Restore(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Restore *c = (struct qemu_IDirectSoundBufferImpl_Restore *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Restore(buffer->host_buffer);
}

#endif

struct qemu_IDirectSoundBufferImpl_GetFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t freq;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetFrequency(IDirectSoundBuffer8 *iface, DWORD *freq)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETFREQUENCY);
    call.iface = (ULONG_PTR)buffer;
    call.freq = (ULONG_PTR)freq;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetFrequency(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetFrequency *c = (struct qemu_IDirectSoundBufferImpl_GetFrequency *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetFrequency(buffer->host_buffer, QEMU_G2H(c->freq));
}

#endif

struct qemu_IDirectSoundBufferImpl_SetFX
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwEffectsCount;
    uint64_t pDSFXDesc;
    uint64_t pdwResultCodes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_SetFX(IDirectSoundBuffer8 *iface, DWORD dwEffectsCount, LPDSEFFECTDESC pDSFXDesc, DWORD *pdwResultCodes)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_SetFX call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_SETFX);
    call.iface = (ULONG_PTR)buffer;
    call.dwEffectsCount = dwEffectsCount;
    call.pDSFXDesc = (ULONG_PTR)pDSFXDesc;
    call.pdwResultCodes = (ULONG_PTR)pdwResultCodes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_SetFX(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_SetFX *c = (struct qemu_IDirectSoundBufferImpl_SetFX *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_SetFX(buffer->host_buffer, c->dwEffectsCount, QEMU_G2H(c->pDSFXDesc), QEMU_G2H(c->pdwResultCodes));
}

#endif

struct qemu_IDirectSoundBufferImpl_AcquireResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwFlags;
    uint64_t dwEffectsCount;
    uint64_t pdwResultCodes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_AcquireResources(IDirectSoundBuffer8 *iface, DWORD dwFlags, DWORD dwEffectsCount, DWORD *pdwResultCodes)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_AcquireResources call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_ACQUIRERESOURCES);
    call.iface = (ULONG_PTR)buffer;
    call.dwFlags = dwFlags;
    call.dwEffectsCount = dwEffectsCount;
    call.pdwResultCodes = (ULONG_PTR)pdwResultCodes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_AcquireResources(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_AcquireResources *c = (struct qemu_IDirectSoundBufferImpl_AcquireResources *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_AcquireResources(buffer->host_buffer, c->dwFlags, c->dwEffectsCount, QEMU_G2H(c->pdwResultCodes));
}

#endif

struct qemu_IDirectSoundBufferImpl_GetObjectInPath
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguidObject;
    uint64_t dwIndex;
    uint64_t rguidInterface;
    uint64_t ppObject;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetObjectInPath(IDirectSoundBuffer8 *iface, REFGUID rguidObject, DWORD dwIndex, REFGUID rguidInterface, void **ppObject)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetObjectInPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETOBJECTINPATH);
    call.iface = (ULONG_PTR)buffer;
    call.rguidObject = (ULONG_PTR)rguidObject;
    call.dwIndex = dwIndex;
    call.rguidInterface = (ULONG_PTR)rguidInterface;
    call.ppObject = (ULONG_PTR)ppObject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetObjectInPath(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetObjectInPath *c = (struct qemu_IDirectSoundBufferImpl_GetObjectInPath *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetObjectInPath(buffer->host_buffer, QEMU_G2H(c->rguidObject), c->dwIndex, QEMU_G2H(c->rguidInterface), QEMU_G2H(c->ppObject));
}

#endif

struct qemu_IDirectSoundBufferImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dsound;
    uint64_t dbsd;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_Initialize(IDirectSoundBuffer8 *iface, IDirectSound *dsound, LPCDSBUFFERDESC dbsd)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)buffer;
    call.dsound = (ULONG_PTR)dsound;
    call.dbsd = (ULONG_PTR)dbsd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_Initialize *c = (struct qemu_IDirectSoundBufferImpl_Initialize *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_Initialize(buffer->host_buffer, QEMU_G2H(c->dsound), QEMU_G2H(c->dbsd));
}

#endif

struct qemu_IDirectSoundBufferImpl_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_GetCaps(IDirectSoundBuffer8 *iface, LPDSBCAPS caps)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);
    struct qemu_IDirectSoundBufferImpl_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUNDBUFFERIMPL_GETCAPS);
    call.iface = (ULONG_PTR)buffer;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSoundBufferImpl_GetCaps(struct qemu_syscall *call)
{
    struct qemu_IDirectSoundBufferImpl_GetCaps *c = (struct qemu_IDirectSoundBufferImpl_GetCaps *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IDirectSoundBuffer8_GetCaps(buffer->host_buffer, QEMU_G2H(c->caps));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSoundBufferImpl_QueryInterface(IDirectSoundBuffer8 *iface, REFIID riid, void **obj)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSoundBuffer8(iface);

    WINE_TRACE("(%p,%s,%p)\n", buffer, wine_dbgstr_guid(riid), obj);

    if (obj == NULL)
    {
        WINE_WARN("invalid parameter\n");
        return E_INVALIDARG;
    }

    *obj = NULL;	/* assume failure */

    if (IsEqualGUID(riid, &IID_IUnknown) ||
            IsEqualGUID(riid, &IID_IDirectSoundBuffer))
    {
        IDirectSoundBuffer8_AddRef(iface);
        *obj = iface;
        return S_OK;
    }
    if (IsEqualGUID( &IID_IDirectSoundBuffer8, riid ))
    {
        if (is_primary_buffer(buffer))
        {
            WINE_WARN("app requested DirectSoundBuffer8 on primary buffer\n");
            return E_NOINTERFACE;
        }
        IDirectSoundBuffer8_AddRef(iface);
        *obj = iface;
        return S_OK;
    }

    if (IsEqualGUID(&IID_IDirectSoundNotify, riid))
    {
        if (is_primary_buffer(buffer))
        {
            /* Wine isn't sure if this handling is correct. */
            WINE_ERR("app requested IDirectSoundNotify on primary buffer\n");
            return E_NOINTERFACE;
        }
        IDirectSoundNotify_AddRef(&buffer->IDirectSoundNotify_iface);
        *obj = &buffer->IDirectSoundNotify_iface;
        return S_OK;
    }

    if (IsEqualGUID(&IID_IDirectSound3DBuffer, riid))
    {
        if (is_primary_buffer(buffer))
        {
            WINE_ERR("app requested IDirectSound3DBuffer on primary buffer\n");
            return E_NOINTERFACE;
        }

        if (buffer->flags & DSBCAPS_CTRL3D)
        {
            IDirectSound3DBuffer_AddRef(&buffer->IDirectSound3DBuffer_iface);
            *obj = &buffer->IDirectSound3DBuffer_iface;
            return S_OK;
        }
        WINE_TRACE("app requested IDirectSound3DBuffer on non-3D secondary buffer\n");
        return E_NOINTERFACE;
    }

    if (IsEqualGUID( &IID_IDirectSound3DListener, riid))
    {
        if (!is_primary_buffer(buffer))
        {
            WINE_ERR("app requested IDirectSound3DListener on secondary buffer\n");
            return E_NOINTERFACE;
        }
        *obj = &buffer->IDirectSound3DListener_iface;
        IDirectSound3DListener_AddRef(&buffer->IDirectSound3DListener_iface);
        return S_OK;
    }

    if (IsEqualGUID( &IID_IKsPropertySet, riid))
    {
        IKsPropertySet_AddRef(&buffer->IKsPropertySet_iface);
        *obj = &buffer->IKsPropertySet_iface;
        return S_OK;
    }

    WINE_FIXME("Unknown IID %s\n", wine_dbgstr_guid(riid));

    return E_NOINTERFACE;
}

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IKsPropertySetImpl_QueryInterface(IKsPropertySet *iface, REFIID riid, void **obj)
{
    struct qemu_dsound_buffer *buffer = buffer_impl_from_IKsPropertySet(iface);

    WINE_TRACE("(%p,%s,%p)\n", buffer, wine_dbgstr_guid(riid), obj);

    return IDirectSoundBuffer_QueryInterface(&buffer->IDirectSoundBuffer8_iface, riid, obj);
}

static ULONG WINAPI IKsPropertySetImpl_AddRef(IKsPropertySet *iface)
{
    struct qemu_dsound_buffer *buffer = buffer_impl_from_IKsPropertySet(iface);
    ULONG ref = InterlockedIncrement(&buffer->refiks);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

#endif

static ULONG WINAPI IKsPropertySetImpl_Release(IKsPropertySet *iface)
{
    struct qemu_dsound_buffer *buffer = buffer_impl_from_IKsPropertySet(iface);
    ULONG ref;

    if (is_primary_buffer(buffer))
    {
        ref = capped_refcount_dec(&buffer->refiks);
        if(!ref)
            capped_refcount_dec(&buffer->iface_count);
        WINE_TRACE("(%p) ref is now: %d\n", buffer, ref);
        return ref;
    }

    ref = InterlockedDecrement(&buffer->refiks);
    if (!ref && !InterlockedDecrement(&buffer->iface_count))
        secondarybuffer_destroy(buffer);

    WINE_TRACE("(%p) ref is now %d\n", buffer, ref);

    return ref;
}

#endif

struct qemu_IKsPropertySetImpl_Get
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidPropSet;
    uint64_t dwPropID;
    uint64_t pInstanceData;
    uint64_t cbInstanceData;
    uint64_t pPropData;
    uint64_t cbPropData;
    uint64_t pcbReturned;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IKsPropertySetImpl_Get(IKsPropertySet *iface, REFGUID guidPropSet, ULONG dwPropID, void *pInstanceData, ULONG cbInstanceData, void *pPropData, ULONG cbPropData, ULONG *pcbReturned)
{
    struct qemu_dsound_buffer *buffer = buffer_impl_from_IKsPropertySet(iface);
    struct qemu_IKsPropertySetImpl_Get call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPROPERTYSETIMPL_GET);
    call.iface = (ULONG_PTR)buffer;
    call.guidPropSet = (ULONG_PTR)guidPropSet;
    call.dwPropID = dwPropID;
    call.pInstanceData = (ULONG_PTR)pInstanceData;
    call.cbInstanceData = cbInstanceData;
    call.pPropData = (ULONG_PTR)pPropData;
    call.cbPropData = cbPropData;
    call.pcbReturned = (ULONG_PTR)pcbReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IKsPropertySetImpl_Get(struct qemu_syscall *call)
{
    struct qemu_IKsPropertySetImpl_Get *c = (struct qemu_IKsPropertySetImpl_Get *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IKsPropertySet_Get(buffer->host_property, QEMU_G2H(c->guidPropSet), c->dwPropID, QEMU_G2H(c->pInstanceData), c->cbInstanceData, QEMU_G2H(c->pPropData), c->cbPropData, QEMU_G2H(c->pcbReturned));
}

#endif

struct qemu_IKsPropertySetImpl_Set
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidPropSet;
    uint64_t dwPropID;
    uint64_t pInstanceData;
    uint64_t cbInstanceData;
    uint64_t pPropData;
    uint64_t cbPropData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IKsPropertySetImpl_Set(IKsPropertySet *iface, REFGUID guidPropSet, ULONG dwPropID, void *pInstanceData, ULONG cbInstanceData, void *pPropData, ULONG cbPropData)
{
    struct qemu_dsound_buffer *buffer = buffer_impl_from_IKsPropertySet(iface);
    struct qemu_IKsPropertySetImpl_Set call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPROPERTYSETIMPL_SET);
    call.iface = (ULONG_PTR)buffer;
    call.guidPropSet = (ULONG_PTR)guidPropSet;
    call.dwPropID = dwPropID;
    call.pInstanceData = (ULONG_PTR)pInstanceData;
    call.cbInstanceData = cbInstanceData;
    call.pPropData = (ULONG_PTR)pPropData;
    call.cbPropData = cbPropData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IKsPropertySetImpl_Set(struct qemu_syscall *call)
{
    struct qemu_IKsPropertySetImpl_Set *c = (struct qemu_IKsPropertySetImpl_Set *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_FIXME("Unverified!\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IKsPropertySet_Set(buffer->host_property, QEMU_G2H(c->guidPropSet), c->dwPropID, QEMU_G2H(c->pInstanceData), c->cbInstanceData, QEMU_G2H(c->pPropData), c->cbPropData);
}

#endif

struct qemu_IKsPropertySetImpl_QuerySupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidPropSet;
    uint64_t dwPropID;
    uint64_t pTypeSupport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IKsPropertySetImpl_QuerySupport(IKsPropertySet *iface, REFGUID guidPropSet, ULONG dwPropID, ULONG *pTypeSupport)
{
    struct qemu_dsound_buffer *buffer = buffer_impl_from_IKsPropertySet(iface);
    struct qemu_IKsPropertySetImpl_QuerySupport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPROPERTYSETIMPL_QUERYSUPPORT);
    call.iface = (ULONG_PTR)buffer;
    call.guidPropSet = (ULONG_PTR)guidPropSet;
    call.dwPropID = dwPropID;
    call.pTypeSupport = (ULONG_PTR)pTypeSupport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IKsPropertySetImpl_QuerySupport(struct qemu_syscall *call)
{
    struct qemu_IKsPropertySetImpl_QuerySupport *c = (struct qemu_IKsPropertySetImpl_QuerySupport *)call;
    struct qemu_dsound_buffer *buffer;
    WINE_TRACE("\n");

    buffer = QEMU_G2H(c->iface);
    c->super.iret = IKsPropertySet_QuerySupport(buffer->host_property, QEMU_G2H(c->guidPropSet), c->dwPropID, QEMU_G2H(c->pTypeSupport));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IDirectSoundBuffer8Vtbl buffer_vtbl =
{
    IDirectSoundBufferImpl_QueryInterface,
    IDirectSoundBufferImpl_AddRef,
    IDirectSoundBufferImpl_Release,
    IDirectSoundBufferImpl_GetCaps,
    IDirectSoundBufferImpl_GetCurrentPosition,
    IDirectSoundBufferImpl_GetFormat,
    IDirectSoundBufferImpl_GetVolume,
    IDirectSoundBufferImpl_GetPan,
    IDirectSoundBufferImpl_GetFrequency,
    IDirectSoundBufferImpl_GetStatus,
    IDirectSoundBufferImpl_Initialize,
    IDirectSoundBufferImpl_Lock,
    IDirectSoundBufferImpl_Play,
    IDirectSoundBufferImpl_SetCurrentPosition,
    IDirectSoundBufferImpl_SetFormat,
    IDirectSoundBufferImpl_SetVolume,
    IDirectSoundBufferImpl_SetPan,
    IDirectSoundBufferImpl_SetFrequency,
    IDirectSoundBufferImpl_Stop,
    IDirectSoundBufferImpl_Unlock,
    IDirectSoundBufferImpl_Restore,
    IDirectSoundBufferImpl_SetFX,
    IDirectSoundBufferImpl_AcquireResources,
    IDirectSoundBufferImpl_GetObjectInPath
};

static const IDirectSoundNotifyVtbl notify_vtbl =
{
    IDirectSoundNotifyImpl_QueryInterface,
    IDirectSoundNotifyImpl_AddRef,
    IDirectSoundNotifyImpl_Release,
    IDirectSoundNotifyImpl_SetNotificationPositions,
};

static const IKsPropertySetVtbl property_set_vtbl =
{
    IKsPropertySetImpl_QueryInterface,
    IKsPropertySetImpl_AddRef,
    IKsPropertySetImpl_Release,
    IKsPropertySetImpl_Get,
    IKsPropertySetImpl_Set,
    IKsPropertySetImpl_QuerySupport
};

void buffer_init_guest(struct qemu_dsound_buffer *buffer, DWORD flags)
{
    buffer->IDirectSoundBuffer8_iface.lpVtbl = &buffer_vtbl;
    buffer->IDirectSoundNotify_iface.lpVtbl = &notify_vtbl;
    buffer->IDirectSound3DBuffer_iface.lpVtbl = &buffer_3d_vtbl;
    buffer->IDirectSound3DListener_iface.lpVtbl = &listener_3d_vtbl;
    buffer->IKsPropertySet_iface.lpVtbl = &property_set_vtbl;

    buffer->ref = 1;
    buffer->refn = 0;
    buffer->ref_3d = 0;
    buffer->refiks = 0;
    buffer->iface_count = 1;

    buffer->flags = flags;
}

#endif
