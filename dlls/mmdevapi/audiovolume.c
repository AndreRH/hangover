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
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <endpointvolume.h>
#include <audiopolicy.h>
#include <dsound.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#include <list.h>
#else
#include <wine/debug.h>
#include <wine/list.h>
#endif

#include "qemu_mmdevapi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_mmdevapi);

struct qemu_AEV_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_volume *impl_from_IAudioEndpointVolumeEx(IAudioEndpointVolumeEx *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_volume, IAudioEndpointVolumeEx_iface);
}

static HRESULT WINAPI AEV_QueryInterface(IAudioEndpointVolumeEx *iface, REFIID riid, void **ppv)
{
    struct qemu_AEV_QueryInterface call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_QUERYINTERFACE);
    call.iface = (ULONG_PTR)volume;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AEV_QueryInterface *c = (struct qemu_AEV_QueryInterface *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_QueryInterface(volume->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_AEV_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AEV_AddRef(IAudioEndpointVolumeEx *iface)
{
    struct qemu_AEV_AddRef call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_ADDREF);
    call.iface = (ULONG_PTR)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_AddRef(struct qemu_syscall *call)
{
    struct qemu_AEV_AddRef *c = (struct qemu_AEV_AddRef *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_AddRef(volume->host);
}

#endif

struct qemu_AEV_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AEV_Release(IAudioEndpointVolumeEx *iface)
{
    struct qemu_AEV_Release call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_RELEASE);
    call.iface = (ULONG_PTR)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_Release(struct qemu_syscall *call)
{
    struct qemu_AEV_Release *c = (struct qemu_AEV_Release *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_Release(volume->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying IAudioEndpointVolumeEx wrapper %p, host %p.\n", volume, volume->host);
        HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, volume);
    }
}

#endif

struct qemu_AEV_RegisterControlChangeNotify
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t notify;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_RegisterControlChangeNotify(IAudioEndpointVolumeEx *iface, IAudioEndpointVolumeCallback *notify)
{
    struct qemu_AEV_RegisterControlChangeNotify call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_REGISTERCONTROLCHANGENOTIFY);
    call.iface = (ULONG_PTR)volume;
    call.notify = (ULONG_PTR)notify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_RegisterControlChangeNotify(struct qemu_syscall *call)
{
    struct qemu_AEV_RegisterControlChangeNotify *c = (struct qemu_AEV_RegisterControlChangeNotify *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_RegisterControlChangeNotify(volume->host, QEMU_G2H(c->notify));
}

#endif

struct qemu_AEV_UnregisterControlChangeNotify
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t notify;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_UnregisterControlChangeNotify(IAudioEndpointVolumeEx *iface, IAudioEndpointVolumeCallback *notify)
{
    struct qemu_AEV_UnregisterControlChangeNotify call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_UNREGISTERCONTROLCHANGENOTIFY);
    call.iface = (ULONG_PTR)volume;
    call.notify = (ULONG_PTR)notify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_UnregisterControlChangeNotify(struct qemu_syscall *call)
{
    struct qemu_AEV_UnregisterControlChangeNotify *c = (struct qemu_AEV_UnregisterControlChangeNotify *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_UnregisterControlChangeNotify(volume->host, QEMU_G2H(c->notify));
}

#endif

struct qemu_AEV_GetChannelCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetChannelCount(IAudioEndpointVolumeEx *iface, UINT *count)
{
    struct qemu_AEV_GetChannelCount call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETCHANNELCOUNT);
    call.iface = (ULONG_PTR)volume;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetChannelCount(struct qemu_syscall *call)
{
    struct qemu_AEV_GetChannelCount *c = (struct qemu_AEV_GetChannelCount *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetChannelCount(volume->host, QEMU_G2H(c->count));
}

#endif

struct qemu_AEV_SetMasterVolumeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    double leveldb;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_SetMasterVolumeLevel(IAudioEndpointVolumeEx *iface, float leveldb, const GUID *ctx)
{
    struct qemu_AEV_SetMasterVolumeLevel call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_SETMASTERVOLUMELEVEL);
    call.iface = (ULONG_PTR)volume;
    call.leveldb = leveldb;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_SetMasterVolumeLevel(struct qemu_syscall *call)
{
    struct qemu_AEV_SetMasterVolumeLevel *c = (struct qemu_AEV_SetMasterVolumeLevel *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_SetMasterVolumeLevel(volume->host, c->leveldb, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_SetMasterVolumeLevelScalar
{
    struct qemu_syscall super;
    uint64_t iface;
    double level;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_SetMasterVolumeLevelScalar(IAudioEndpointVolumeEx *iface, float level, const GUID *ctx)
{
    struct qemu_AEV_SetMasterVolumeLevelScalar call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_SETMASTERVOLUMELEVELSCALAR);
    call.iface = (ULONG_PTR)volume;
    call.level = level;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_SetMasterVolumeLevelScalar(struct qemu_syscall *call)
{
    struct qemu_AEV_SetMasterVolumeLevelScalar *c = (struct qemu_AEV_SetMasterVolumeLevelScalar *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_SetMasterVolumeLevelScalar(volume->host, c->level, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_GetMasterVolumeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t leveldb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetMasterVolumeLevel(IAudioEndpointVolumeEx *iface, float *leveldb)
{
    struct qemu_AEV_GetMasterVolumeLevel call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETMASTERVOLUMELEVEL);
    call.iface = (ULONG_PTR)volume;
    call.leveldb = (ULONG_PTR)leveldb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetMasterVolumeLevel(struct qemu_syscall *call)
{
    struct qemu_AEV_GetMasterVolumeLevel *c = (struct qemu_AEV_GetMasterVolumeLevel *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetMasterVolumeLevel(volume->host, QEMU_G2H(c->leveldb));
}

#endif

struct qemu_AEV_GetMasterVolumeLevelScalar
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetMasterVolumeLevelScalar(IAudioEndpointVolumeEx *iface, float *level)
{
    struct qemu_AEV_GetMasterVolumeLevelScalar call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETMASTERVOLUMELEVELSCALAR);
    call.iface = (ULONG_PTR)volume;
    call.level = (ULONG_PTR)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetMasterVolumeLevelScalar(struct qemu_syscall *call)
{
    struct qemu_AEV_GetMasterVolumeLevelScalar *c = (struct qemu_AEV_GetMasterVolumeLevelScalar *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetMasterVolumeLevelScalar(volume->host, QEMU_G2H(c->level));
}

#endif

struct qemu_AEV_SetChannelVolumeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t chan;
    double leveldb;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_SetChannelVolumeLevel(IAudioEndpointVolumeEx *iface, UINT chan, float leveldb, const GUID *ctx)
{
    struct qemu_AEV_SetChannelVolumeLevel call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_SETCHANNELVOLUMELEVEL);
    call.iface = (ULONG_PTR)volume;
    call.chan = chan;
    call.leveldb = leveldb;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_SetChannelVolumeLevel(struct qemu_syscall *call)
{
    struct qemu_AEV_SetChannelVolumeLevel *c = (struct qemu_AEV_SetChannelVolumeLevel *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_SetChannelVolumeLevel(volume->host, c->chan, c->leveldb, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_SetChannelVolumeLevelScalar
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t chan;
    double level;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_SetChannelVolumeLevelScalar(IAudioEndpointVolumeEx *iface, UINT chan, float level, const GUID *ctx)
{
    struct qemu_AEV_SetChannelVolumeLevelScalar call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_SETCHANNELVOLUMELEVELSCALAR);
    call.iface = (ULONG_PTR)volume;
    call.chan = chan;
    call.level = level;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_SetChannelVolumeLevelScalar(struct qemu_syscall *call)
{
    struct qemu_AEV_SetChannelVolumeLevelScalar *c = (struct qemu_AEV_SetChannelVolumeLevelScalar *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_SetChannelVolumeLevelScalar(volume->host, c->chan, c->level, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_GetChannelVolumeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t chan;
    uint64_t leveldb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetChannelVolumeLevel(IAudioEndpointVolumeEx *iface, UINT chan, float *leveldb)
{
    struct qemu_AEV_GetChannelVolumeLevel call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETCHANNELVOLUMELEVEL);
    call.iface = (ULONG_PTR)volume;
    call.chan = chan;
    call.leveldb = (ULONG_PTR)leveldb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetChannelVolumeLevel(struct qemu_syscall *call)
{
    struct qemu_AEV_GetChannelVolumeLevel *c = (struct qemu_AEV_GetChannelVolumeLevel *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetChannelVolumeLevel(volume->host, c->chan, QEMU_G2H(c->leveldb));
}

#endif

struct qemu_AEV_GetChannelVolumeLevelScalar
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t chan;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetChannelVolumeLevelScalar(IAudioEndpointVolumeEx *iface, UINT chan, float *level)
{
    struct qemu_AEV_GetChannelVolumeLevelScalar call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETCHANNELVOLUMELEVELSCALAR);
    call.iface = (ULONG_PTR)volume;
    call.chan = chan;
    call.level = (ULONG_PTR)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetChannelVolumeLevelScalar(struct qemu_syscall *call)
{
    struct qemu_AEV_GetChannelVolumeLevelScalar *c = (struct qemu_AEV_GetChannelVolumeLevelScalar *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetChannelVolumeLevelScalar(volume->host, c->chan, QEMU_G2H(c->level));
}

#endif

struct qemu_AEV_SetMute
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mute;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_SetMute(IAudioEndpointVolumeEx *iface, BOOL mute, const GUID *ctx)
{
    struct qemu_AEV_SetMute call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_SETMUTE);
    call.iface = (ULONG_PTR)volume;
    call.mute = mute;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_SetMute(struct qemu_syscall *call)
{
    struct qemu_AEV_SetMute *c = (struct qemu_AEV_SetMute *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_SetMute(volume->host, c->mute, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_GetMute
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mute;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetMute(IAudioEndpointVolumeEx *iface, BOOL *mute)
{
    struct qemu_AEV_GetMute call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETMUTE);
    call.iface = (ULONG_PTR)volume;
    call.mute = (ULONG_PTR)mute;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetMute(struct qemu_syscall *call)
{
    struct qemu_AEV_GetMute *c = (struct qemu_AEV_GetMute *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetMute(volume->host, QEMU_G2H(c->mute));
}

#endif

struct qemu_AEV_GetVolumeStepInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stepsize;
    uint64_t stepcount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetVolumeStepInfo(IAudioEndpointVolumeEx *iface, UINT *stepsize, UINT *stepcount)
{
    struct qemu_AEV_GetVolumeStepInfo call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETVOLUMESTEPINFO);
    call.iface = (ULONG_PTR)volume;
    call.stepsize = (ULONG_PTR)stepsize;
    call.stepcount = (ULONG_PTR)stepcount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetVolumeStepInfo(struct qemu_syscall *call)
{
    struct qemu_AEV_GetVolumeStepInfo *c = (struct qemu_AEV_GetVolumeStepInfo *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetVolumeStepInfo(volume->host, QEMU_G2H(c->stepsize), QEMU_G2H(c->stepcount));
}

#endif

struct qemu_AEV_VolumeStepUp
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_VolumeStepUp(IAudioEndpointVolumeEx *iface, const GUID *ctx)
{
    struct qemu_AEV_VolumeStepUp call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_VOLUMESTEPUP);
    call.iface = (ULONG_PTR)volume;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_VolumeStepUp(struct qemu_syscall *call)
{
    struct qemu_AEV_VolumeStepUp *c = (struct qemu_AEV_VolumeStepUp *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_VolumeStepUp(volume->host, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_VolumeStepDown
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_VolumeStepDown(IAudioEndpointVolumeEx *iface, const GUID *ctx)
{
    struct qemu_AEV_VolumeStepDown call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_VOLUMESTEPDOWN);
    call.iface = (ULONG_PTR)volume;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_VolumeStepDown(struct qemu_syscall *call)
{
    struct qemu_AEV_VolumeStepDown *c = (struct qemu_AEV_VolumeStepDown *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_VolumeStepDown(volume->host, QEMU_G2H(c->ctx));
}

#endif

struct qemu_AEV_QueryHardwareSupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_QueryHardwareSupport(IAudioEndpointVolumeEx *iface, DWORD *mask)
{
    struct qemu_AEV_QueryHardwareSupport call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_QUERYHARDWARESUPPORT);
    call.iface = (ULONG_PTR)volume;
    call.mask = (ULONG_PTR)mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_QueryHardwareSupport(struct qemu_syscall *call)
{
    struct qemu_AEV_QueryHardwareSupport *c = (struct qemu_AEV_QueryHardwareSupport *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_QueryHardwareSupport(volume->host, QEMU_G2H(c->mask));
}

#endif

struct qemu_AEV_GetVolumeRange
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mindb;
    uint64_t maxdb;
    uint64_t inc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetVolumeRange(IAudioEndpointVolumeEx *iface, float *mindb, float *maxdb, float *inc)
{
    struct qemu_AEV_GetVolumeRange call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETVOLUMERANGE);
    call.iface = (ULONG_PTR)volume;
    call.mindb = (ULONG_PTR)mindb;
    call.maxdb = (ULONG_PTR)maxdb;
    call.inc = (ULONG_PTR)inc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetVolumeRange(struct qemu_syscall *call)
{
    struct qemu_AEV_GetVolumeRange *c = (struct qemu_AEV_GetVolumeRange *)call;
    struct qemu_volume *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetVolumeRange(volume->host, QEMU_G2H(c->mindb), QEMU_G2H(c->maxdb), QEMU_G2H(c->inc));
}

#endif

struct qemu_AEV_GetVolumeRangeChannel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t chan;
    uint64_t mindb;
    uint64_t maxdb;
    uint64_t inc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AEV_GetVolumeRangeChannel(IAudioEndpointVolumeEx *iface, UINT chan, float *mindb, float *maxdb, float *inc)
{
    struct qemu_AEV_GetVolumeRangeChannel call;
    struct qemu_volume *volume = impl_from_IAudioEndpointVolumeEx(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_AEV_GETVOLUMERANGECHANNEL);
    call.iface = (ULONG_PTR)volume;
    call.chan = chan;
    call.mindb = (ULONG_PTR)mindb;
    call.maxdb = (ULONG_PTR)maxdb;
    call.inc = (ULONG_PTR)inc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AEV_GetVolumeRangeChannel(struct qemu_syscall *call)
{
    struct qemu_AEV_GetVolumeRangeChannel *c = (struct qemu_AEV_GetVolumeRangeChannel *)call;
    struct qemu_volume *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IAudioEndpointVolumeEx_GetVolumeRangeChannel(volume->host, c->chan, QEMU_G2H(c->mindb), QEMU_G2H(c->maxdb), QEMU_G2H(c->inc));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IAudioEndpointVolumeExVtbl AEVImpl_Vtbl =
{
    AEV_QueryInterface,
    AEV_AddRef,
    AEV_Release,
    AEV_RegisterControlChangeNotify,
    AEV_UnregisterControlChangeNotify,
    AEV_GetChannelCount,
    AEV_SetMasterVolumeLevel,
    AEV_SetMasterVolumeLevelScalar,
    AEV_GetMasterVolumeLevel,
    AEV_GetMasterVolumeLevelScalar,
    AEV_SetChannelVolumeLevel,
    AEV_SetChannelVolumeLevelScalar,
    AEV_GetChannelVolumeLevel,
    AEV_GetChannelVolumeLevelScalar,
    AEV_SetMute,
    AEV_GetMute,
    AEV_GetVolumeStepInfo,
    AEV_VolumeStepUp,
    AEV_VolumeStepDown,
    AEV_QueryHardwareSupport,
    AEV_GetVolumeRange,
    AEV_GetVolumeRangeChannel
};

void qemu_volume_guest_init(struct qemu_volume *volume)
{
    volume->IAudioEndpointVolumeEx_iface.lpVtbl = &AEVImpl_Vtbl;
}

#else

HRESULT qemu_volume_host_create(IAudioEndpointVolumeEx *host, struct qemu_volume **volume)
{
    struct qemu_volume *obj;
    
    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }
    
    WINE_TRACE("Created IAudioEndpointVolumeEx wrapper %p for host interface %p.\n", obj, host);
    
    obj->host = host;
    
    *volume = obj;
    return S_OK;

}

#endif
