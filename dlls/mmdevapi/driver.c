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
#include <list.h>
#include <debug.h>
#else
#include <wine/list.h>
#include <wine/debug.h>
#endif

#include "qemu_mmdevapi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_mmdevapi);

struct qemu_AudioClient_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_audioclient *impl_from_IAudioClient(IAudioClient *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audioclient, IAudioClient_iface);
}

static inline struct qemu_audioclient *impl_from_IAudioRenderClient(IAudioRenderClient *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audioclient, IAudioRenderClient_iface);
}

static inline struct qemu_audioclient *impl_from_IAudioCaptureClient(IAudioCaptureClient *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audioclient, IAudioCaptureClient_iface);
}

static inline struct qemu_audiosession *impl_from_IAudioSessionControl2(IAudioSessionControl2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audiosession, IAudioSessionControl2_iface);
}

static inline struct qemu_audiosession *impl_from_ISimpleAudioVolume(ISimpleAudioVolume *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audiosession, ISimpleAudioVolume_iface);
}

static inline struct qemu_audiosession *impl_from_IChannelAudioVolume(IChannelAudioVolume *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audiosession, IChannelAudioVolume_iface);
}

static inline struct qemu_audioclient *impl_from_IAudioClock(IAudioClock *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audioclient, IAudioClock_iface);
}

static inline struct qemu_audioclient *impl_from_IAudioClock2(IAudioClock2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audioclient, IAudioClock2_iface);
}

static inline struct qemu_audioclient *impl_from_IAudioStreamVolume(IAudioStreamVolume *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_audioclient, IAudioStreamVolume_iface);
}

static inline struct qemu_sessmgr *impl_from_IAudioSessionManager2(IAudioSessionManager2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_sessmgr, IAudioSessionManager2_iface);
}

static HRESULT WINAPI AudioClient_QueryInterface(IAudioClient *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioClient_QueryInterface call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    WINE_TRACE("(%p)->(%s, %p)\n", iface, wine_dbgstr_guid(riid), ppv);

    if (!ppv)
        return E_POINTER;

    *ppv = NULL;

    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IAudioClient))
        *ppv = iface;

    if (*ppv)
    {
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }

    if (IsEqualIID(riid, &IID_IMarshal))
        return IUnknown_QueryInterface(client->marshal, riid, ppv);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    return E_NOINTERFACE;
}

#else

void qemu_AudioClient_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioClient_QueryInterface *c = (struct qemu_AudioClient_QueryInterface *)call;
    struct qemu_audioclient *client;
    IUnknown *obj;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_QueryInterface(client->host_client, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_AudioClient_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioClient_AddRef(IAudioClient *iface)
{
    struct qemu_AudioClient_AddRef call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_ADDREF);
    call.iface = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_AddRef(struct qemu_syscall *call)
{
    struct qemu_AudioClient_AddRef *c = (struct qemu_AudioClient_AddRef *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_AddRef(client->host_client);
}

#endif

struct qemu_AudioClient_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioClient_Release(IAudioClient *iface)
{
    struct qemu_AudioClient_Release call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);
    IUnknown *marshal = client->marshal;

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_RELEASE);
    call.iface = (ULONG_PTR)client;

    qemu_syscall(&call.super);
    if (!call.super.iret)
        IUnknown_Release(marshal);

    return call.super.iret;
}

#else

static ULONG qemu_AudioClient_Release_internal(struct qemu_audioclient *client)
{
    ULONG ret;

    ret = IAudioClient_Release(client->host_client);

    if (!ret)
    {
        /* FIXME: Do I need to do something about the parent IMMDevice or IMMDeviceEnumerator? */
        WINE_TRACE("Destroying audioclient wrapper %p, host %p\n", client, client->host_client);
        HeapFree(GetProcessHeap(), 0, client);
    }

    return ret;
}

void qemu_AudioClient_Release(struct qemu_syscall *call)
{
    struct qemu_AudioClient_Release *c = (struct qemu_AudioClient_Release *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = qemu_AudioClient_Release_internal(client);
}

#endif

struct qemu_AudioClient_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t flags;
    uint64_t duration;
    uint64_t period;
    uint64_t fmt;
    uint64_t sessionguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_Initialize(IAudioClient *iface, AUDCLNT_SHAREMODE mode, DWORD flags,
        REFERENCE_TIME duration, REFERENCE_TIME period, const WAVEFORMATEX *fmt, const GUID *sessionguid)
{
    struct qemu_AudioClient_Initialize call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_INITIALIZE);
    call.iface = (ULONG_PTR)client;
    call.mode = mode;
    call.flags = flags;
    call.duration = duration;
    call.period = period;
    call.fmt = (ULONG_PTR)fmt;
    call.sessionguid = (ULONG_PTR)sessionguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_Initialize(struct qemu_syscall *call)
{
    struct qemu_AudioClient_Initialize *c = (struct qemu_AudioClient_Initialize *)call;
    struct qemu_audioclient *client;

    /* WAVEFORMATEX has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_Initialize(client->host_client, c->mode, c->flags, c->duration, c->period,
            QEMU_G2H(c->fmt), QEMU_G2H(c->sessionguid));
}

#endif

struct qemu_AudioClient_GetBufferSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_GetBufferSize(IAudioClient *iface, UINT32 *out)
{
    struct qemu_AudioClient_GetBufferSize call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_GETBUFFERSIZE);
    call.iface = (ULONG_PTR)client;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_GetBufferSize(struct qemu_syscall *call)
{
    struct qemu_AudioClient_GetBufferSize *c = (struct qemu_AudioClient_GetBufferSize *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_GetBufferSize(client->host_client, QEMU_G2H(c->out));
}

#endif

struct qemu_AudioClient_GetStreamLatency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t latency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_GetStreamLatency(IAudioClient *iface, REFERENCE_TIME *latency)
{
    struct qemu_AudioClient_GetStreamLatency call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_GETSTREAMLATENCY);
    call.iface = (ULONG_PTR)client;
    call.latency = (ULONG_PTR)latency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_GetStreamLatency(struct qemu_syscall *call)
{
    struct qemu_AudioClient_GetStreamLatency *c = (struct qemu_AudioClient_GetStreamLatency *)call;
    struct qemu_audioclient *client;

    /* REFERENCE_TIME has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_GetStreamLatency(client->host_client, QEMU_G2H(c->latency));
}

#endif

struct qemu_AudioClient_GetCurrentPadding
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_GetCurrentPadding(IAudioClient *iface, UINT32 *out)
{
    struct qemu_AudioClient_GetCurrentPadding call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_GETCURRENTPADDING);
    call.iface = (ULONG_PTR)client;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_GetCurrentPadding(struct qemu_syscall *call)
{
    struct qemu_AudioClient_GetCurrentPadding *c = (struct qemu_AudioClient_GetCurrentPadding *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_GetCurrentPadding(client->host_client, QEMU_G2H(c->out));
}

#endif

struct qemu_AudioClient_IsFormatSupported
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t fmt;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_IsFormatSupported(IAudioClient *iface, AUDCLNT_SHAREMODE mode,
        const WAVEFORMATEX *fmt, WAVEFORMATEX **out)
{
    struct qemu_AudioClient_IsFormatSupported call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_ISFORMATSUPPORTED);
    call.iface = (ULONG_PTR)client;
    call.mode = mode;
    call.fmt = (ULONG_PTR)fmt;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);
    if (fmt && out)
        *out = (WAVEFORMATEX *)(ULONG_PTR)call.out;

    return call.super.iret;
}

#else

void qemu_AudioClient_IsFormatSupported(struct qemu_syscall *call)
{
    struct qemu_AudioClient_IsFormatSupported *c = (struct qemu_AudioClient_IsFormatSupported *)call;
    struct qemu_audioclient *client;
    WAVEFORMATEX *out;

    /* WAVEFORMATEX has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_IsFormatSupported(client->host_client, c->mode,
            QEMU_G2H(c->fmt), c->out ? &out : NULL);
    c->out = QEMU_H2G(out);
}

#endif

struct qemu_AudioClient_GetMixFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pwfx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_GetMixFormat(IAudioClient *iface, WAVEFORMATEX **pwfx)
{
    struct qemu_AudioClient_GetMixFormat call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_GETMIXFORMAT);
    call.iface = (ULONG_PTR)client;
    call.pwfx = (ULONG_PTR)pwfx;

    qemu_syscall(&call.super);
    if (pwfx)
        *pwfx = (WAVEFORMATEX *)(ULONG_PTR)call.pwfx;

    return call.super.iret;
}

#else

void qemu_AudioClient_GetMixFormat(struct qemu_syscall *call)
{
    struct qemu_AudioClient_GetMixFormat *c = (struct qemu_AudioClient_GetMixFormat *)call;
    struct qemu_audioclient *client;
    WAVEFORMATEX *fx;

    /* WAVEFORMATEX has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_GetMixFormat(client->host_client, c->pwfx ? &fx : NULL);
    c->pwfx = QEMU_H2G(fx);
}

#endif

struct qemu_AudioClient_GetDevicePeriod
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t defperiod;
    uint64_t minperiod;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_GetDevicePeriod(IAudioClient *iface, REFERENCE_TIME *defperiod,
        REFERENCE_TIME *minperiod)
{
    struct qemu_AudioClient_GetDevicePeriod call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_GETDEVICEPERIOD);
    call.iface = (ULONG_PTR)client;
    call.defperiod = (ULONG_PTR)defperiod;
    call.minperiod = (ULONG_PTR)minperiod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_GetDevicePeriod(struct qemu_syscall *call)
{
    struct qemu_AudioClient_GetDevicePeriod *c = (struct qemu_AudioClient_GetDevicePeriod *)call;
    struct qemu_audioclient *client;

    /* REFERENCE_TIME has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_GetDevicePeriod(client->host_client, QEMU_G2H(c->defperiod), QEMU_G2H(c->minperiod));
}

#endif

struct qemu_AudioClient_Start
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_Start(IAudioClient *iface)
{
    struct qemu_AudioClient_Start call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_START);
    call.iface = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_Start(struct qemu_syscall *call)
{
    struct qemu_AudioClient_Start *c = (struct qemu_AudioClient_Start *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_Start(client->host_client);
}

#endif

struct qemu_AudioClient_Stop
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_Stop(IAudioClient *iface)
{
    struct qemu_AudioClient_Stop call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_STOP);
    call.iface = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_Stop(struct qemu_syscall *call)
{
    struct qemu_AudioClient_Stop *c = (struct qemu_AudioClient_Stop *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_Stop(client->host_client);
}

#endif

struct qemu_AudioClient_Reset
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_Reset(IAudioClient *iface)
{
    struct qemu_AudioClient_Reset call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_RESET);
    call.iface = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_Reset(struct qemu_syscall *call)
{
    struct qemu_AudioClient_Reset *c = (struct qemu_AudioClient_Reset *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_Reset(client->host_client);
}

#endif

struct qemu_AudioClient_SetEventHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClient_SetEventHandle(IAudioClient *iface, HANDLE event)
{
    struct qemu_AudioClient_SetEventHandle call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_SETEVENTHANDLE);
    call.iface = (ULONG_PTR)client;
    call.event = guest_HANDLE_g2h(event);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClient_SetEventHandle(struct qemu_syscall *call)
{
    struct qemu_AudioClient_SetEventHandle *c = (struct qemu_AudioClient_SetEventHandle *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClient_SetEventHandle(client->host_client, QEMU_G2H(c->event));
}

#endif

struct qemu_AudioClient_GetService
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
    uint64_t session;
};

#ifdef QEMU_DLL_GUEST

static void qemu_audiosession_guest_init(struct qemu_audiosession *client);

static HRESULT WINAPI AudioClient_GetService(IAudioClient *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioClient_GetService call;
    struct qemu_audioclient *client = impl_from_IAudioClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLIENT_GETSERVICE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;
    call.session = (ULONG_PTR)client->session;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (ppv)
            *ppv = NULL;
        return call.super.iret;
    }

    if (IsEqualIID(riid, &IID_IAudioRenderClient))
    {
        *ppv = &client->IAudioRenderClient_iface;
    }
    else if (IsEqualIID(riid, &IID_IAudioCaptureClient))
    {
        *ppv = &client->IAudioCaptureClient_iface;
    }
    else if (IsEqualIID(riid, &IID_IAudioClock))
    {
        *ppv = &client->IAudioClock_iface;
    }
    else if (IsEqualIID(riid, &IID_IAudioStreamVolume))
    {
        *ppv = &client->IAudioStreamVolume_iface;
    }
    else if (IsEqualIID(riid, &IID_IAudioSessionControl) || IsEqualIID(riid, &IID_IChannelAudioVolume)
            || IsEqualIID(riid, &IID_ISimpleAudioVolume))
    {
        if (!client->session)
        {
            client->session = (struct qemu_audiosession *)(ULONG_PTR)call.session;
            qemu_audiosession_guest_init(client->session);
        }
        else if (client->session != (struct qemu_audiosession *)(ULONG_PTR)call.session)
        {
            WINE_ERR("qemu_audiosession changed.\n");
        }

        if (IsEqualIID(riid, &IID_IAudioSessionControl))
            *ppv = &client->session->IAudioSessionControl2_iface;
        else if (IsEqualIID(riid, &IID_IChannelAudioVolume))
            *ppv = &client->session->IChannelAudioVolume_iface;
        else if (IsEqualIID(riid, &IID_ISimpleAudioVolume))
            *ppv = &client->session->ISimpleAudioVolume_iface;
    }

    return call.super.iret;
}

#else

static HRESULT qemu_audiosession_host_create(IAudioSessionControl *host, struct qemu_audioclient *client,
        struct qemu_audiosession **session);

void qemu_AudioClient_GetService(struct qemu_syscall *call)
{
    struct qemu_AudioClient_GetService *c = (struct qemu_AudioClient_GetService *)call;
    struct qemu_audioclient *client;
    IUnknown *host;
    const IID *iid;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    /* Which interface(s) are valid may change over the lifetime of the object. Query the host every time
     * the app calls us. */
    c->super.iret = IAudioClient_GetService(client->host_client, iid, c->ppv ? (void **)&host : NULL);
    if (FAILED(c->super.iret))
        return;

    if (IsEqualIID(iid, &IID_IAudioRenderClient))
    {
        if (!client->host_render)
            client->host_render = (IAudioRenderClient *)host;
        else if (client->host_render != (IAudioRenderClient *)host)
            WINE_ERR("IAudioRenderClient iface changed.\n");
    }
    else if (IsEqualIID(iid, &IID_IAudioCaptureClient))
    {
        if (!client->host_capture)
            client->host_capture = (IAudioCaptureClient *)host;
        else if (client->host_capture != (IAudioCaptureClient *)host)
            WINE_ERR("IAudioCaptureClient iface changed.\n");
    }
    else if (IsEqualIID(iid, &IID_IAudioClock))
    {
        if (!client->host_clock)
        {
            client->host_clock = (IAudioClock *)host;
            IAudioClock_QueryInterface(client->host_clock, &IID_IAudioClock2, (void **)&client->host_clock2);
            IAudioClock2_Release(client->host_clock2);
        }
        else if (client->host_clock != (IAudioClock *)host)
            WINE_ERR("IAudioClock iface changed.\n");
    }
    else if (IsEqualIID(iid, &IID_IAudioStreamVolume))
    {
        if (!client->host_volume)
            client->host_volume = (IAudioStreamVolume *)host;
        else if (client->host_volume != (IAudioStreamVolume *)host)
            WINE_ERR("IAudioStreamVolume_iface iface changed.\n");
    }
    else if (IsEqualIID(iid, &IID_IAudioSessionControl) || IsEqualIID(iid, &IID_IChannelAudioVolume)
            || IsEqualIID(iid, &IID_ISimpleAudioVolume))
    {
        struct qemu_audiosession *session = QEMU_G2H(c->session);
        IAudioSessionControl *host_ctrl;

        if (!session)
        {
            c->super.iret = IAudioClient_GetService(client->host_client,
                    &IID_IAudioSessionControl, (void **)&host_ctrl);
            if (FAILED(c->super.iret))
                WINE_ERR("Failed to get IAudioSessionControl.\n");

            c->super.iret = qemu_audiosession_host_create(host_ctrl, client, &session);
            c->session = QEMU_H2G(session);

            IAudioSessionControl_Release(host_ctrl);

            /* Usually out of memory. */
            if (FAILED(c->super.iret))
                IUnknown_Release(host);
        }
    }

    /* Don't release host, we pass the reference on to the application. */
}

#endif

struct qemu_AudioRenderClient_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioRenderClient_QueryInterface(IAudioRenderClient *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioRenderClient_QueryInterface call;
    struct qemu_audioclient *client = impl_from_IAudioRenderClient(iface);

    WINE_TRACE("(%p)->(%s, %p)\n", iface, wine_dbgstr_guid(riid), ppv);

    if (!ppv)
        return E_POINTER;

    *ppv = NULL;

    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IAudioRenderClient))
        *ppv = iface;

    if (*ppv)
    {
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }

    if (IsEqualIID(riid, &IID_IMarshal))
        return IUnknown_QueryInterface(client->marshal, riid, ppv);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIORENDERCLIENT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return E_NOINTERFACE;
}

#else

void qemu_AudioRenderClient_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioRenderClient_QueryInterface *c = (struct qemu_AudioRenderClient_QueryInterface *)call;
    struct qemu_audioclient *client;

    IUnknown *obj;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioRenderClient_QueryInterface(client->host_render, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioRenderClient_AddRef(IAudioRenderClient *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioRenderClient(iface);
    return AudioClient_AddRef(&client->IAudioClient_iface);
}

static ULONG WINAPI AudioRenderClient_Release(IAudioRenderClient *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioRenderClient(iface);
    return AudioClient_Release(&client->IAudioClient_iface);
}

#endif

struct qemu_AudioRenderClient_GetBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t frames;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioRenderClient_GetBuffer(IAudioRenderClient *iface, UINT32 frames, BYTE **data)
{
    struct qemu_AudioRenderClient_GetBuffer call;
    struct qemu_audioclient *client = impl_from_IAudioRenderClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIORENDERCLIENT_GETBUFFER);
    call.iface = (ULONG_PTR)client;
    call.frames = frames;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);
    if (data)
        *data = (BYTE *)(ULONG_PTR)call.data;

    return call.super.iret;
}

#else

void qemu_AudioRenderClient_GetBuffer(struct qemu_syscall *call)
{
    struct qemu_AudioRenderClient_GetBuffer *c = (struct qemu_AudioRenderClient_GetBuffer *)call;
    struct qemu_audioclient *client;
    BYTE *data;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioRenderClient_GetBuffer(client->host_render, c->frames, c->data ? &data : NULL);
    c->data = QEMU_H2G(data);
}

#endif

struct qemu_AudioRenderClient_ReleaseBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t written_frames;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioRenderClient_ReleaseBuffer(IAudioRenderClient *iface, UINT32 written_frames, DWORD flags)
{
    struct qemu_AudioRenderClient_ReleaseBuffer call;
    struct qemu_audioclient *client = impl_from_IAudioRenderClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIORENDERCLIENT_RELEASEBUFFER);
    call.iface = (ULONG_PTR)client;
    call.written_frames = written_frames;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioRenderClient_ReleaseBuffer(struct qemu_syscall *call)
{
    struct qemu_AudioRenderClient_ReleaseBuffer *c = (struct qemu_AudioRenderClient_ReleaseBuffer *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioRenderClient_ReleaseBuffer(client->host_render, c->written_frames, c->flags);
}

#endif

struct qemu_AudioCaptureClient_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioCaptureClient_QueryInterface(IAudioCaptureClient *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioCaptureClient_QueryInterface call;
    struct qemu_audioclient *client = impl_from_IAudioCaptureClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCAPTURECLIENT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioCaptureClient_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioCaptureClient_QueryInterface *c = (struct qemu_AudioCaptureClient_QueryInterface *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioCaptureClient_QueryInterface(client->host_capture, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioCaptureClient_AddRef(IAudioCaptureClient *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioCaptureClient(iface);
    return IAudioClient_AddRef(&client->IAudioClient_iface);
}

static ULONG WINAPI AudioCaptureClient_Release(IAudioCaptureClient *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioCaptureClient(iface);
    return IAudioClient_Release(&client->IAudioClient_iface);
}

#endif

struct qemu_AudioCaptureClient_GetBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
    uint64_t frames;
    uint64_t flags;
    uint64_t devpos;
    uint64_t qpcpos;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioCaptureClient_GetBuffer(IAudioCaptureClient *iface, BYTE **data, UINT32 *frames, DWORD *flags, UINT64 *devpos, UINT64 *qpcpos)
{
    struct qemu_AudioCaptureClient_GetBuffer call;
    struct qemu_audioclient *client = impl_from_IAudioCaptureClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCAPTURECLIENT_GETBUFFER);
    call.iface = (ULONG_PTR)client;
    call.data = (ULONG_PTR)data;
    call.frames = (ULONG_PTR)frames;
    call.flags = (ULONG_PTR)flags;
    call.devpos = (ULONG_PTR)devpos;
    call.qpcpos = (ULONG_PTR)qpcpos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioCaptureClient_GetBuffer(struct qemu_syscall *call)
{
    struct qemu_AudioCaptureClient_GetBuffer *c = (struct qemu_AudioCaptureClient_GetBuffer *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioCaptureClient_GetBuffer(client->host_capture, QEMU_G2H(c->data), QEMU_G2H(c->frames), QEMU_G2H(c->flags), QEMU_G2H(c->devpos), QEMU_G2H(c->qpcpos));
}

#endif

struct qemu_AudioCaptureClient_ReleaseBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t done;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioCaptureClient_ReleaseBuffer(IAudioCaptureClient *iface, UINT32 done)
{
    struct qemu_AudioCaptureClient_ReleaseBuffer call;
    struct qemu_audioclient *client = impl_from_IAudioCaptureClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCAPTURECLIENT_RELEASEBUFFER);
    call.iface = (ULONG_PTR)client;
    call.done = done;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioCaptureClient_ReleaseBuffer(struct qemu_syscall *call)
{
    struct qemu_AudioCaptureClient_ReleaseBuffer *c = (struct qemu_AudioCaptureClient_ReleaseBuffer *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioCaptureClient_ReleaseBuffer(client->host_capture, c->done);
}

#endif

struct qemu_AudioCaptureClient_GetNextPacketSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t frames;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioCaptureClient_GetNextPacketSize(IAudioCaptureClient *iface, UINT32 *frames)
{
    struct qemu_AudioCaptureClient_GetNextPacketSize call;
    struct qemu_audioclient *client = impl_from_IAudioCaptureClient(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCAPTURECLIENT_GETNEXTPACKETSIZE);
    call.iface = (ULONG_PTR)client;
    call.frames = (ULONG_PTR)frames;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioCaptureClient_GetNextPacketSize(struct qemu_syscall *call)
{
    struct qemu_AudioCaptureClient_GetNextPacketSize *c = (struct qemu_AudioCaptureClient_GetNextPacketSize *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioCaptureClient_GetNextPacketSize(client->host_capture, QEMU_G2H(c->frames));
}

#endif

struct qemu_AudioClock_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClock_QueryInterface(IAudioClock *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioClock_QueryInterface call;
    struct qemu_audioclient *client = impl_from_IAudioClock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLOCK_QUERYINTERFACE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClock_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioClock_QueryInterface *c = (struct qemu_AudioClock_QueryInterface *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClock_QueryInterface(client->host_clock, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioClock_AddRef(IAudioClock *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioClock(iface);
    return IAudioClient_AddRef(&client->IAudioClient_iface);
}

static ULONG WINAPI AudioClock_Release(IAudioClock *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioClock(iface);
    return IAudioClient_Release(&client->IAudioClient_iface);
}

#endif

struct qemu_AudioClock_GetFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t freq;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClock_GetFrequency(IAudioClock *iface, UINT64 *freq)
{
    struct qemu_AudioClock_GetFrequency call;
    struct qemu_audioclient *client = impl_from_IAudioClock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLOCK_GETFREQUENCY);
    call.iface = (ULONG_PTR)client;
    call.freq = (ULONG_PTR)freq;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClock_GetFrequency(struct qemu_syscall *call)
{
    struct qemu_AudioClock_GetFrequency *c = (struct qemu_AudioClock_GetFrequency *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClock_GetFrequency(client->host_clock, QEMU_G2H(c->freq));
}

#endif

struct qemu_AudioClock_GetPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pos;
    uint64_t qpctime;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClock_GetPosition(IAudioClock *iface, UINT64 *pos, UINT64 *qpctime)
{
    struct qemu_AudioClock_GetPosition call;
    struct qemu_audioclient *client = impl_from_IAudioClock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLOCK_GETPOSITION);
    call.iface = (ULONG_PTR)client;
    call.pos = (ULONG_PTR)pos;
    call.qpctime = (ULONG_PTR)qpctime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClock_GetPosition(struct qemu_syscall *call)
{
    struct qemu_AudioClock_GetPosition *c = (struct qemu_AudioClock_GetPosition *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClock_GetPosition(client->host_clock, QEMU_G2H(c->pos), QEMU_G2H(c->qpctime));
}

#endif

struct qemu_AudioClock_GetCharacteristics
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t chars;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClock_GetCharacteristics(IAudioClock *iface, DWORD *chars)
{
    struct qemu_AudioClock_GetCharacteristics call;
    struct qemu_audioclient *client = impl_from_IAudioClock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLOCK_GETCHARACTERISTICS);
    call.iface = (ULONG_PTR)client;
    call.chars = (ULONG_PTR)chars;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClock_GetCharacteristics(struct qemu_syscall *call)
{
    struct qemu_AudioClock_GetCharacteristics *c = (struct qemu_AudioClock_GetCharacteristics *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClock_GetCharacteristics(client->host_clock, QEMU_G2H(c->chars));
}

#endif

struct qemu_AudioClock2_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClock2_QueryInterface(IAudioClock2 *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioClock2_QueryInterface call;
    struct qemu_audioclient *client = impl_from_IAudioClock2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLOCK2_QUERYINTERFACE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClock2_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioClock2_QueryInterface *c = (struct qemu_AudioClock2_QueryInterface *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClock2_QueryInterface(client->host_clock2, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioClock2_AddRef(IAudioClock2 *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioClock2(iface);
    return IAudioClient_AddRef(&client->IAudioClient_iface);
}

static ULONG WINAPI AudioClock2_Release(IAudioClock2 *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioClock2(iface);
    return IAudioClient_Release(&client->IAudioClient_iface);
}

#endif

struct qemu_AudioClock2_GetDevicePosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pos;
    uint64_t qpctime;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioClock2_GetDevicePosition(IAudioClock2 *iface, UINT64 *pos, UINT64 *qpctime)
{
    struct qemu_AudioClock2_GetDevicePosition call;
    struct qemu_audioclient *client = impl_from_IAudioClock2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOCLOCK2_GETDEVICEPOSITION);
    call.iface = (ULONG_PTR)client;
    call.pos = (ULONG_PTR)pos;
    call.qpctime = (ULONG_PTR)qpctime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioClock2_GetDevicePosition(struct qemu_syscall *call)
{
    struct qemu_AudioClock2_GetDevicePosition *c = (struct qemu_AudioClock2_GetDevicePosition *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioClock2_GetPosition(client->host_clock2, QEMU_G2H(c->pos), QEMU_G2H(c->qpctime));
}

#endif

struct qemu_AudioStreamVolume_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioStreamVolume_QueryInterface(IAudioStreamVolume *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioStreamVolume_QueryInterface call;
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSTREAMVOLUME_QUERYINTERFACE);
    call.iface = (ULONG_PTR)client;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioStreamVolume_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioStreamVolume_QueryInterface *c = (struct qemu_AudioStreamVolume_QueryInterface *)call;
    struct qemu_audioclient *client;

    WINE_FIXME("Unverified!\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioStreamVolume_QueryInterface(client->host_volume, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioStreamVolume_AddRef(IAudioStreamVolume *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);
    return IAudioClient_AddRef(&client->IAudioClient_iface);
}

static ULONG WINAPI AudioStreamVolume_Release(IAudioStreamVolume *iface)
{
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);
    return IAudioClient_Release(&client->IAudioClient_iface);
}

#endif

struct qemu_AudioStreamVolume_GetChannelCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioStreamVolume_GetChannelCount(IAudioStreamVolume *iface, UINT32 *out)
{
    struct qemu_AudioStreamVolume_GetChannelCount call;
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSTREAMVOLUME_GETCHANNELCOUNT);
    call.iface = (ULONG_PTR)client;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioStreamVolume_GetChannelCount(struct qemu_syscall *call)
{
    struct qemu_AudioStreamVolume_GetChannelCount *c = (struct qemu_AudioStreamVolume_GetChannelCount *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioStreamVolume_GetChannelCount(client->host_volume, QEMU_G2H(c->out));
}

#endif

struct qemu_AudioStreamVolume_SetAllVolumes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t levels;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioStreamVolume_SetAllVolumes(IAudioStreamVolume *iface, UINT32 count, const float *levels)
{
    struct qemu_AudioStreamVolume_SetAllVolumes call;
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSTREAMVOLUME_SETALLVOLUMES);
    call.iface = (ULONG_PTR)client;
    call.count = count;
    call.levels = (ULONG_PTR)levels;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioStreamVolume_SetAllVolumes(struct qemu_syscall *call)
{
    struct qemu_AudioStreamVolume_SetAllVolumes *c = (struct qemu_AudioStreamVolume_SetAllVolumes *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioStreamVolume_SetAllVolumes(client->host_volume, c->count, QEMU_G2H(c->levels));
}

#endif

struct qemu_AudioStreamVolume_GetAllVolumes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t levels;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioStreamVolume_GetAllVolumes(IAudioStreamVolume *iface, UINT32 count, float *levels)
{
    struct qemu_AudioStreamVolume_GetAllVolumes call;
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSTREAMVOLUME_GETALLVOLUMES);
    call.iface = (ULONG_PTR)client;
    call.count = count;
    call.levels = (ULONG_PTR)levels;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioStreamVolume_GetAllVolumes(struct qemu_syscall *call)
{
    struct qemu_AudioStreamVolume_GetAllVolumes *c = (struct qemu_AudioStreamVolume_GetAllVolumes *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioStreamVolume_GetAllVolumes(client->host_volume, c->count, QEMU_G2H(c->levels));
}

#endif

struct qemu_AudioStreamVolume_SetChannelVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    double level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioStreamVolume_SetChannelVolume(IAudioStreamVolume *iface, UINT32 index, float level)
{
    struct qemu_AudioStreamVolume_SetChannelVolume call;
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSTREAMVOLUME_SETCHANNELVOLUME);
    call.iface = (ULONG_PTR)client;
    call.index = index;
    call.level = level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioStreamVolume_SetChannelVolume(struct qemu_syscall *call)
{
    struct qemu_AudioStreamVolume_SetChannelVolume *c = (struct qemu_AudioStreamVolume_SetChannelVolume *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioStreamVolume_SetChannelVolume(client->host_volume, c->index, c->level);
}

#endif

struct qemu_AudioStreamVolume_GetChannelVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioStreamVolume_GetChannelVolume(IAudioStreamVolume *iface, UINT32 index, float *level)
{
    struct qemu_AudioStreamVolume_GetChannelVolume call;
    struct qemu_audioclient *client = impl_from_IAudioStreamVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSTREAMVOLUME_GETCHANNELVOLUME);
    call.iface = (ULONG_PTR)client;
    call.index = index;
    call.level = (ULONG_PTR)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioStreamVolume_GetChannelVolume(struct qemu_syscall *call)
{
    struct qemu_AudioStreamVolume_GetChannelVolume *c = (struct qemu_AudioStreamVolume_GetChannelVolume *)call;
    struct qemu_audioclient *client;

    WINE_TRACE("\n");
    client = QEMU_G2H(c->iface);

    c->super.iret = IAudioStreamVolume_GetChannelVolume(client->host_volume, c->index, QEMU_G2H(c->level));
}

#endif

struct qemu_AudioSessionControl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_QueryInterface(IAudioSessionControl2 *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioSessionControl_QueryInterface call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)session;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_QueryInterface *c = (struct qemu_AudioSessionControl_QueryInterface *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_QueryInterface(session->host_control, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_AudioSessionControl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioSessionControl_AddRef(IAudioSessionControl2 *iface)
{
    struct qemu_AudioSessionControl_AddRef call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_ADDREF);
    call.iface = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_AddRef(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_AddRef *c = (struct qemu_AudioSessionControl_AddRef *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_AddRef(session->host_control);
}

#endif

struct qemu_AudioSessionControl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioSessionControl_Release(IAudioSessionControl2 *iface)
{
    struct qemu_AudioSessionControl_Release call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_RELEASE);
    call.iface = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_Release(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_Release *c = (struct qemu_AudioSessionControl_Release *)call;
    struct qemu_audiosession *session;
    struct qemu_audioclient *client = session->client;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);
    client = session->client;

    if (client)
        IAudioClient_AddRef(client->host_client);

    c->super.iret = IAudioSessionControl2_Release(session->host_control);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying session control wrapper %p, host %p.\n", session, session->host_control);
        HeapFree(GetProcessHeap(), 0, session);
    }

    if (client)
        qemu_AudioClient_Release_internal(client);
}

#endif

struct qemu_AudioSessionControl_GetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetState(IAudioSessionControl2 *iface, AudioSessionState *state)
{
    struct qemu_AudioSessionControl_GetState call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETSTATE);
    call.iface = (ULONG_PTR)session;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetState(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetState *c = (struct qemu_AudioSessionControl_GetState *)call;
    struct qemu_audiosession *session;

    /* AudioSessionState is a 4 byte enum on 32 and 64 bit. */
    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetState(session->host_control, QEMU_G2H(c->state));
}

#endif

struct qemu_AudioSessionControl_GetDisplayName
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetDisplayName(IAudioSessionControl2 *iface, WCHAR **name)
{
    struct qemu_AudioSessionControl_GetDisplayName call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETDISPLAYNAME);
    call.iface = (ULONG_PTR)session;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetDisplayName(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetDisplayName *c = (struct qemu_AudioSessionControl_GetDisplayName *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetDisplayName(session->host_control, QEMU_G2H(c->name));
}

#endif

struct qemu_AudioSessionControl_SetDisplayName
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t session;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_SetDisplayName(IAudioSessionControl2 *iface, const WCHAR *name, const GUID *session)
{
    struct qemu_AudioSessionControl_SetDisplayName call;
    struct qemu_audiosession *This = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_SETDISPLAYNAME);
    call.iface = (ULONG_PTR)This;
    call.name = (ULONG_PTR)name;
    call.session = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_SetDisplayName(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_SetDisplayName *c = (struct qemu_AudioSessionControl_SetDisplayName *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_SetDisplayName(session->host_control, QEMU_G2H(c->name), QEMU_G2H(c->session));
}

#endif

struct qemu_AudioSessionControl_GetIconPath
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetIconPath(IAudioSessionControl2 *iface, WCHAR **path)
{
    struct qemu_AudioSessionControl_GetIconPath call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETICONPATH);
    call.iface = (ULONG_PTR)session;
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetIconPath(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetIconPath *c = (struct qemu_AudioSessionControl_GetIconPath *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetIconPath(session->host_control, QEMU_G2H(c->path));
}

#endif

struct qemu_AudioSessionControl_SetIconPath
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t path;
    uint64_t session;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_SetIconPath(IAudioSessionControl2 *iface, const WCHAR *path, const GUID *session)
{
    struct qemu_AudioSessionControl_SetIconPath call;
    struct qemu_audiosession *This = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_SETICONPATH);
    call.iface = (ULONG_PTR)This;
    call.path = (ULONG_PTR)path;
    call.session = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_SetIconPath(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_SetIconPath *c = (struct qemu_AudioSessionControl_SetIconPath *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_SetIconPath(session->host_control, QEMU_G2H(c->path), QEMU_G2H(c->session));
}

#endif

struct qemu_AudioSessionControl_GetGroupingParam
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetGroupingParam(IAudioSessionControl2 *iface, GUID *group)
{
    struct qemu_AudioSessionControl_GetGroupingParam call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETGROUPINGPARAM);
    call.iface = (ULONG_PTR)session;
    call.group = (ULONG_PTR)group;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetGroupingParam(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetGroupingParam *c = (struct qemu_AudioSessionControl_GetGroupingParam *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetGroupingParam(session->host_control, QEMU_G2H(c->group));
}

#endif

struct qemu_AudioSessionControl_SetGroupingParam
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t group;
    uint64_t session;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_SetGroupingParam(IAudioSessionControl2 *iface, const GUID *group, const GUID *session)
{
    struct qemu_AudioSessionControl_SetGroupingParam call;
    struct qemu_audiosession *This = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_SETGROUPINGPARAM);
    call.iface = (ULONG_PTR)This;
    call.group = (ULONG_PTR)group;
    call.session = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_SetGroupingParam(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_SetGroupingParam *c = (struct qemu_AudioSessionControl_SetGroupingParam *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_SetGroupingParam(session->host_control, QEMU_G2H(c->group), QEMU_G2H(c->session));
}

#endif

struct qemu_AudioSessionControl_RegisterAudioSessionNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t events;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_RegisterAudioSessionNotification(IAudioSessionControl2 *iface, IAudioSessionEvents *events)
{
    struct qemu_AudioSessionControl_RegisterAudioSessionNotification call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_REGISTERAUDIOSESSIONNOTIFICATION);
    call.iface = (ULONG_PTR)session;
    call.events = (ULONG_PTR)events;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_RegisterAudioSessionNotification(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_RegisterAudioSessionNotification *c = (struct qemu_AudioSessionControl_RegisterAudioSessionNotification *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_RegisterAudioSessionNotification(session->host_control, QEMU_G2H(c->events));
}

#endif

struct qemu_AudioSessionControl_UnregisterAudioSessionNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t events;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_UnregisterAudioSessionNotification(IAudioSessionControl2 *iface, IAudioSessionEvents *events)
{
    struct qemu_AudioSessionControl_UnregisterAudioSessionNotification call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_UNREGISTERAUDIOSESSIONNOTIFICATION);
    call.iface = (ULONG_PTR)session;
    call.events = (ULONG_PTR)events;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_UnregisterAudioSessionNotification(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_UnregisterAudioSessionNotification *c = (struct qemu_AudioSessionControl_UnregisterAudioSessionNotification *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_UnregisterAudioSessionNotification(session->host_control, QEMU_G2H(c->events));
}

#endif

struct qemu_AudioSessionControl_GetSessionIdentifier
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetSessionIdentifier(IAudioSessionControl2 *iface, WCHAR **id)
{
    struct qemu_AudioSessionControl_GetSessionIdentifier call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETSESSIONIDENTIFIER);
    call.iface = (ULONG_PTR)session;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetSessionIdentifier(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetSessionIdentifier *c = (struct qemu_AudioSessionControl_GetSessionIdentifier *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetSessionIdentifier(session->host_control, QEMU_G2H(c->id));
}

#endif

struct qemu_AudioSessionControl_GetSessionInstanceIdentifier
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetSessionInstanceIdentifier(IAudioSessionControl2 *iface, WCHAR **id)
{
    struct qemu_AudioSessionControl_GetSessionInstanceIdentifier call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETSESSIONINSTANCEIDENTIFIER);
    call.iface = (ULONG_PTR)session;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetSessionInstanceIdentifier(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetSessionInstanceIdentifier *c = (struct qemu_AudioSessionControl_GetSessionInstanceIdentifier *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetSessionInstanceIdentifier(session->host_control, QEMU_G2H(c->id));
}

#endif

struct qemu_AudioSessionControl_GetProcessId
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_GetProcessId(IAudioSessionControl2 *iface, DWORD *pid)
{
    struct qemu_AudioSessionControl_GetProcessId call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_GETPROCESSID);
    call.iface = (ULONG_PTR)session;
    call.pid = (ULONG_PTR)pid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_GetProcessId(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_GetProcessId *c = (struct qemu_AudioSessionControl_GetProcessId *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_GetProcessId(session->host_control, QEMU_G2H(c->pid));
}

#endif

struct qemu_AudioSessionControl_IsSystemSoundsSession
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_IsSystemSoundsSession(IAudioSessionControl2 *iface)
{
    struct qemu_AudioSessionControl_IsSystemSoundsSession call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_ISSYSTEMSOUNDSSESSION);
    call.iface = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_IsSystemSoundsSession(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_IsSystemSoundsSession *c = (struct qemu_AudioSessionControl_IsSystemSoundsSession *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_IsSystemSoundsSession(session->host_control);
}

#endif

struct qemu_AudioSessionControl_SetDuckingPreference
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t optout;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionControl_SetDuckingPreference(IAudioSessionControl2 *iface, BOOL optout)
{
    struct qemu_AudioSessionControl_SetDuckingPreference call;
    struct qemu_audiosession *session = impl_from_IAudioSessionControl2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONCONTROL_SETDUCKINGPREFERENCE);
    call.iface = (ULONG_PTR)session;
    call.optout = optout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionControl_SetDuckingPreference(struct qemu_syscall *call)
{
    struct qemu_AudioSessionControl_SetDuckingPreference *c = (struct qemu_AudioSessionControl_SetDuckingPreference *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionControl2_SetDuckingPreferences(session->host_control, c->optout);
}

#endif

struct qemu_AudioSessionManager_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_QueryInterface(IAudioSessionManager2 *iface, REFIID riid, void **ppv)
{
    struct qemu_AudioSessionManager_QueryInterface call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)mgr;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_QueryInterface *c = (struct qemu_AudioSessionManager_QueryInterface *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_QueryInterface(mgr->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_AudioSessionManager_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioSessionManager_AddRef(IAudioSessionManager2 *iface)
{
    struct qemu_AudioSessionManager_AddRef call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_ADDREF);
    call.iface = (ULONG_PTR)mgr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_AddRef(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_AddRef *c = (struct qemu_AudioSessionManager_AddRef *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_AddRef(mgr->host);
}

#endif

struct qemu_AudioSessionManager_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI AudioSessionManager_Release(IAudioSessionManager2 *iface)
{
    struct qemu_AudioSessionManager_Release call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_RELEASE);
    call.iface = (ULONG_PTR)mgr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_Release(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_Release *c = (struct qemu_AudioSessionManager_Release *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_Release(mgr->host);
}

#endif

struct qemu_AudioSessionManager_GetAudioSessionControl
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t session_guid;
    uint64_t flags;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_GetAudioSessionControl(IAudioSessionManager2 *iface, const GUID *session_guid, DWORD flags, IAudioSessionControl **out)
{
    struct qemu_AudioSessionManager_GetAudioSessionControl call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_GETAUDIOSESSIONCONTROL);
    call.iface = (ULONG_PTR)mgr;
    call.session_guid = (ULONG_PTR)session_guid;
    call.flags = flags;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_GetAudioSessionControl(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_GetAudioSessionControl *c = (struct qemu_AudioSessionManager_GetAudioSessionControl *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_GetAudioSessionControl(mgr->host, QEMU_G2H(c->session_guid), c->flags, QEMU_G2H(c->out));
}

#endif

struct qemu_AudioSessionManager_GetSimpleAudioVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t session_guid;
    uint64_t flags;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_GetSimpleAudioVolume(IAudioSessionManager2 *iface, const GUID *session_guid, DWORD flags, ISimpleAudioVolume **out)
{
    struct qemu_AudioSessionManager_GetSimpleAudioVolume call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_GETSIMPLEAUDIOVOLUME);
    call.iface = (ULONG_PTR)mgr;
    call.session_guid = (ULONG_PTR)session_guid;
    call.flags = flags;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_GetSimpleAudioVolume(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_GetSimpleAudioVolume *c = (struct qemu_AudioSessionManager_GetSimpleAudioVolume *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_GetSimpleAudioVolume(mgr->host, QEMU_G2H(c->session_guid), c->flags, QEMU_G2H(c->out));
}

#endif

struct qemu_AudioSessionManager_GetSessionEnumerator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_GetSessionEnumerator(IAudioSessionManager2 *iface, IAudioSessionEnumerator **out)
{
    struct qemu_AudioSessionManager_GetSessionEnumerator call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_GETSESSIONENUMERATOR);
    call.iface = (ULONG_PTR)mgr;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_GetSessionEnumerator(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_GetSessionEnumerator *c = (struct qemu_AudioSessionManager_GetSessionEnumerator *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_GetSessionEnumerator(mgr->host, QEMU_G2H(c->out));
}

#endif

struct qemu_AudioSessionManager_RegisterSessionNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t notification;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_RegisterSessionNotification(IAudioSessionManager2 *iface, IAudioSessionNotification *notification)
{
    struct qemu_AudioSessionManager_RegisterSessionNotification call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_REGISTERSESSIONNOTIFICATION);
    call.iface = (ULONG_PTR)mgr;
    call.notification = (ULONG_PTR)notification;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_RegisterSessionNotification(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_RegisterSessionNotification *c = (struct qemu_AudioSessionManager_RegisterSessionNotification *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_RegisterSessionNotification(mgr->host, QEMU_G2H(c->notification));
}

#endif

struct qemu_AudioSessionManager_UnregisterSessionNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t notification;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_UnregisterSessionNotification(IAudioSessionManager2 *iface, IAudioSessionNotification *notification)
{
    struct qemu_AudioSessionManager_UnregisterSessionNotification call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_UNREGISTERSESSIONNOTIFICATION);
    call.iface = (ULONG_PTR)mgr;
    call.notification = (ULONG_PTR)notification;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_UnregisterSessionNotification(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_UnregisterSessionNotification *c = (struct qemu_AudioSessionManager_UnregisterSessionNotification *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_UnregisterSessionNotification(mgr->host, QEMU_G2H(c->notification));
}

#endif

struct qemu_AudioSessionManager_RegisterDuckNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t session_id;
    uint64_t notification;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_RegisterDuckNotification(IAudioSessionManager2 *iface, const WCHAR *session_id, IAudioVolumeDuckNotification *notification)
{
    struct qemu_AudioSessionManager_RegisterDuckNotification call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_REGISTERDUCKNOTIFICATION);
    call.iface = (ULONG_PTR)mgr;
    call.session_id = (ULONG_PTR)session_id;
    call.notification = (ULONG_PTR)notification;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_RegisterDuckNotification(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_RegisterDuckNotification *c = (struct qemu_AudioSessionManager_RegisterDuckNotification *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_RegisterDuckNotification(mgr->host, QEMU_G2H(c->session_id), QEMU_G2H(c->notification));
}

#endif

struct qemu_AudioSessionManager_UnregisterDuckNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t notification;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI AudioSessionManager_UnregisterDuckNotification(IAudioSessionManager2 *iface, IAudioVolumeDuckNotification *notification)
{
    struct qemu_AudioSessionManager_UnregisterDuckNotification call;
    struct qemu_sessmgr *mgr = impl_from_IAudioSessionManager2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_AUDIOSESSIONMANAGER_UNREGISTERDUCKNOTIFICATION);
    call.iface = (ULONG_PTR)mgr;
    call.notification = (ULONG_PTR)notification;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AudioSessionManager_UnregisterDuckNotification(struct qemu_syscall *call)
{
    struct qemu_AudioSessionManager_UnregisterDuckNotification *c = (struct qemu_AudioSessionManager_UnregisterDuckNotification *)call;
    struct qemu_sessmgr *mgr;

    WINE_FIXME("Unverified!\n");
    mgr = QEMU_G2H(c->iface);

    c->super.iret = IAudioSessionManager2_UnregisterDuckNotification(mgr->host, QEMU_G2H(c->notification));
}

#endif

struct qemu_SimpleAudioVolume_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI SimpleAudioVolume_QueryInterface(ISimpleAudioVolume *iface, REFIID riid, void **ppv)
{
    struct qemu_SimpleAudioVolume_QueryInterface call;
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SIMPLEAUDIOVOLUME_QUERYINTERFACE);
    call.iface = (ULONG_PTR)session;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SimpleAudioVolume_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_SimpleAudioVolume_QueryInterface *c = (struct qemu_SimpleAudioVolume_QueryInterface *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = ISimpleAudioVolume_QueryInterface(session->host_simple_vol, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI SimpleAudioVolume_AddRef(ISimpleAudioVolume *iface)
{
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);
    return AudioSessionControl_AddRef(&session->IAudioSessionControl2_iface);
}

static ULONG WINAPI SimpleAudioVolume_Release(ISimpleAudioVolume *iface)
{
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);
    return AudioSessionControl_Release(&session->IAudioSessionControl2_iface);
}

#endif

struct qemu_SimpleAudioVolume_SetMasterVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    double level;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI SimpleAudioVolume_SetMasterVolume(ISimpleAudioVolume *iface, float level, const GUID *context)
{
    struct qemu_SimpleAudioVolume_SetMasterVolume call;
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SIMPLEAUDIOVOLUME_SETMASTERVOLUME);
    call.iface = (ULONG_PTR)session;
    call.level = level;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SimpleAudioVolume_SetMasterVolume(struct qemu_syscall *call)
{
    struct qemu_SimpleAudioVolume_SetMasterVolume *c = (struct qemu_SimpleAudioVolume_SetMasterVolume *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = ISimpleAudioVolume_SetMasterVolume(session->host_simple_vol, c->level, QEMU_G2H(c->context));
}

#endif

struct qemu_SimpleAudioVolume_GetMasterVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI SimpleAudioVolume_GetMasterVolume(ISimpleAudioVolume *iface, float *level)
{
    struct qemu_SimpleAudioVolume_GetMasterVolume call;
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SIMPLEAUDIOVOLUME_GETMASTERVOLUME);
    call.iface = (ULONG_PTR)session;
    call.level = (ULONG_PTR)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SimpleAudioVolume_GetMasterVolume(struct qemu_syscall *call)
{
    struct qemu_SimpleAudioVolume_GetMasterVolume *c = (struct qemu_SimpleAudioVolume_GetMasterVolume *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = ISimpleAudioVolume_GetMasterVolume(session->host_simple_vol, QEMU_G2H(c->level));
}

#endif

struct qemu_SimpleAudioVolume_SetMute
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mute;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI SimpleAudioVolume_SetMute(ISimpleAudioVolume *iface, BOOL mute, const GUID *context)
{
    struct qemu_SimpleAudioVolume_SetMute call;
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SIMPLEAUDIOVOLUME_SETMUTE);
    call.iface = (ULONG_PTR)session;
    call.mute = mute;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SimpleAudioVolume_SetMute(struct qemu_syscall *call)
{
    struct qemu_SimpleAudioVolume_SetMute *c = (struct qemu_SimpleAudioVolume_SetMute *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = ISimpleAudioVolume_SetMute(session->host_simple_vol, c->mute, QEMU_G2H(c->context));
}

#endif

struct qemu_SimpleAudioVolume_GetMute
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mute;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI SimpleAudioVolume_GetMute(ISimpleAudioVolume *iface, BOOL *mute)
{
    struct qemu_SimpleAudioVolume_GetMute call;
    struct qemu_audiosession *session = impl_from_ISimpleAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SIMPLEAUDIOVOLUME_GETMUTE);
    call.iface = (ULONG_PTR)session;
    call.mute = (ULONG_PTR)mute;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SimpleAudioVolume_GetMute(struct qemu_syscall *call)
{
    struct qemu_SimpleAudioVolume_GetMute *c = (struct qemu_SimpleAudioVolume_GetMute *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = ISimpleAudioVolume_GetMute(session->host_simple_vol, QEMU_G2H(c->mute));
}

#endif

struct qemu_ChannelAudioVolume_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ChannelAudioVolume_QueryInterface(IChannelAudioVolume *iface, REFIID riid, void **ppv)
{
    struct qemu_ChannelAudioVolume_QueryInterface call;
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CHANNELAUDIOVOLUME_QUERYINTERFACE);
    call.iface = (ULONG_PTR)session;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChannelAudioVolume_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ChannelAudioVolume_QueryInterface *c = (struct qemu_ChannelAudioVolume_QueryInterface *)call;
    struct qemu_audiosession *session;

    WINE_FIXME("Unverified!\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IChannelAudioVolume_QueryInterface(session->host_chan_vol, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ChannelAudioVolume_AddRef(IChannelAudioVolume *iface)
{
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);
    return AudioSessionControl_AddRef(&session->IAudioSessionControl2_iface);
}

static ULONG WINAPI ChannelAudioVolume_Release(IChannelAudioVolume *iface)
{
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);
    return AudioSessionControl_Release(&session->IAudioSessionControl2_iface);
}

#endif

struct qemu_ChannelAudioVolume_GetChannelCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ChannelAudioVolume_GetChannelCount(IChannelAudioVolume *iface, UINT32 *out)
{
    struct qemu_ChannelAudioVolume_GetChannelCount call;
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CHANNELAUDIOVOLUME_GETCHANNELCOUNT);
    call.iface = (ULONG_PTR)session;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChannelAudioVolume_GetChannelCount(struct qemu_syscall *call)
{
    struct qemu_ChannelAudioVolume_GetChannelCount *c = (struct qemu_ChannelAudioVolume_GetChannelCount *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IChannelAudioVolume_GetChannelCount(session->host_chan_vol, QEMU_G2H(c->out));
}

#endif

struct qemu_ChannelAudioVolume_SetChannelVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    double level;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ChannelAudioVolume_SetChannelVolume(IChannelAudioVolume *iface, UINT32 index, float level,
        const GUID *context)
{
    struct qemu_ChannelAudioVolume_SetChannelVolume call;
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CHANNELAUDIOVOLUME_SETCHANNELVOLUME);
    call.iface = (ULONG_PTR)session;
    call.index = index;
    call.level = level;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChannelAudioVolume_SetChannelVolume(struct qemu_syscall *call)
{
    struct qemu_ChannelAudioVolume_SetChannelVolume *c = (struct qemu_ChannelAudioVolume_SetChannelVolume *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IChannelAudioVolume_SetChannelVolume(session->host_chan_vol, c->index, c->level,
            QEMU_G2H(c->context));
}

#endif

struct qemu_ChannelAudioVolume_GetChannelVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ChannelAudioVolume_GetChannelVolume(IChannelAudioVolume *iface, UINT32 index, float *level)
{
    struct qemu_ChannelAudioVolume_GetChannelVolume call;
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CHANNELAUDIOVOLUME_GETCHANNELVOLUME);
    call.iface = (ULONG_PTR)session;
    call.index = index;
    call.level = (ULONG_PTR)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChannelAudioVolume_GetChannelVolume(struct qemu_syscall *call)
{
    struct qemu_ChannelAudioVolume_GetChannelVolume *c = (struct qemu_ChannelAudioVolume_GetChannelVolume *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IChannelAudioVolume_GetChannelVolume(session->host_chan_vol, c->index, QEMU_G2H(c->level));
}

#endif

struct qemu_ChannelAudioVolume_SetAllVolumes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t levels;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ChannelAudioVolume_SetAllVolumes(IChannelAudioVolume *iface, UINT32 count, const float *levels,
        const GUID *context)
{
    struct qemu_ChannelAudioVolume_SetAllVolumes call;
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CHANNELAUDIOVOLUME_SETALLVOLUMES);
    call.iface = (ULONG_PTR)session;
    call.count = count;
    call.levels = (ULONG_PTR)levels;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChannelAudioVolume_SetAllVolumes(struct qemu_syscall *call)
{
    struct qemu_ChannelAudioVolume_SetAllVolumes *c = (struct qemu_ChannelAudioVolume_SetAllVolumes *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IChannelAudioVolume_SetAllVolumes(session->host_chan_vol, c->count, QEMU_G2H(c->levels),
            QEMU_G2H(c->context));
}

#endif

struct qemu_ChannelAudioVolume_GetAllVolumes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t levels;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ChannelAudioVolume_GetAllVolumes(IChannelAudioVolume *iface, UINT32 count, float *levels)
{
    struct qemu_ChannelAudioVolume_GetAllVolumes call;
    struct qemu_audiosession *session = impl_from_IChannelAudioVolume(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CHANNELAUDIOVOLUME_GETALLVOLUMES);
    call.iface = (ULONG_PTR)session;
    call.count = count;
    call.levels = (ULONG_PTR)levels;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChannelAudioVolume_GetAllVolumes(struct qemu_syscall *call)
{
    struct qemu_ChannelAudioVolume_GetAllVolumes *c = (struct qemu_ChannelAudioVolume_GetAllVolumes *)call;
    struct qemu_audiosession *session;

    WINE_TRACE("\n");
    session = QEMU_G2H(c->iface);

    c->super.iret = IChannelAudioVolume_GetAllVolumes(session->host_chan_vol, c->count, QEMU_G2H(c->levels));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IAudioClientVtbl AudioClient_Vtbl =
{
    AudioClient_QueryInterface,
    AudioClient_AddRef,
    AudioClient_Release,
    AudioClient_Initialize,
    AudioClient_GetBufferSize,
    AudioClient_GetStreamLatency,
    AudioClient_GetCurrentPadding,
    AudioClient_IsFormatSupported,
    AudioClient_GetMixFormat,
    AudioClient_GetDevicePeriod,
    AudioClient_Start,
    AudioClient_Stop,
    AudioClient_Reset,
    AudioClient_SetEventHandle,
    AudioClient_GetService
};

static const IAudioRenderClientVtbl AudioRenderClient_Vtbl =
{
    AudioRenderClient_QueryInterface,
    AudioRenderClient_AddRef,
    AudioRenderClient_Release,
    AudioRenderClient_GetBuffer,
    AudioRenderClient_ReleaseBuffer
};

static const IAudioCaptureClientVtbl AudioCaptureClient_Vtbl =
{
    AudioCaptureClient_QueryInterface,
    AudioCaptureClient_AddRef,
    AudioCaptureClient_Release,
    AudioCaptureClient_GetBuffer,
    AudioCaptureClient_ReleaseBuffer,
    AudioCaptureClient_GetNextPacketSize
};

static const IAudioClockVtbl AudioClock_Vtbl =
{
    AudioClock_QueryInterface,
    AudioClock_AddRef,
    AudioClock_Release,
    AudioClock_GetFrequency,
    AudioClock_GetPosition,
    AudioClock_GetCharacteristics
};

static const IAudioClock2Vtbl AudioClock2_Vtbl =
{
    AudioClock2_QueryInterface,
    AudioClock2_AddRef,
    AudioClock2_Release,
    AudioClock2_GetDevicePosition
};

static const IAudioStreamVolumeVtbl AudioStreamVolume_Vtbl =
{
    AudioStreamVolume_QueryInterface,
    AudioStreamVolume_AddRef,
    AudioStreamVolume_Release,
    AudioStreamVolume_GetChannelCount,
    AudioStreamVolume_SetChannelVolume,
    AudioStreamVolume_GetChannelVolume,
    AudioStreamVolume_SetAllVolumes,
    AudioStreamVolume_GetAllVolumes
};

static const IAudioSessionControl2Vtbl AudioSessionControl2_Vtbl =
{
    AudioSessionControl_QueryInterface,
    AudioSessionControl_AddRef,
    AudioSessionControl_Release,
    AudioSessionControl_GetState,
    AudioSessionControl_GetDisplayName,
    AudioSessionControl_SetDisplayName,
    AudioSessionControl_GetIconPath,
    AudioSessionControl_SetIconPath,
    AudioSessionControl_GetGroupingParam,
    AudioSessionControl_SetGroupingParam,
    AudioSessionControl_RegisterAudioSessionNotification,
    AudioSessionControl_UnregisterAudioSessionNotification,
    AudioSessionControl_GetSessionIdentifier,
    AudioSessionControl_GetSessionInstanceIdentifier,
    AudioSessionControl_GetProcessId,
    AudioSessionControl_IsSystemSoundsSession,
    AudioSessionControl_SetDuckingPreference
};

static const IChannelAudioVolumeVtbl ChannelAudioVolume_Vtbl =
{
    ChannelAudioVolume_QueryInterface,
    ChannelAudioVolume_AddRef,
    ChannelAudioVolume_Release,
    ChannelAudioVolume_GetChannelCount,
    ChannelAudioVolume_SetChannelVolume,
    ChannelAudioVolume_GetChannelVolume,
    ChannelAudioVolume_SetAllVolumes,
    ChannelAudioVolume_GetAllVolumes
};

static const ISimpleAudioVolumeVtbl SimpleAudioVolume_Vtbl  =
{
    SimpleAudioVolume_QueryInterface,
    SimpleAudioVolume_AddRef,
    SimpleAudioVolume_Release,
    SimpleAudioVolume_SetMasterVolume,
    SimpleAudioVolume_GetMasterVolume,
    SimpleAudioVolume_SetMute,
    SimpleAudioVolume_GetMute
};

void qemu_audioclient_guest_init(struct qemu_audioclient *client)
{
    HRESULT hr;

    client->IAudioClient_iface.lpVtbl = &AudioClient_Vtbl;
    client->IAudioRenderClient_iface.lpVtbl = &AudioRenderClient_Vtbl;
    client->IAudioCaptureClient_iface.lpVtbl = &AudioCaptureClient_Vtbl;
    client->IAudioClock_iface.lpVtbl = &AudioClock_Vtbl;
    client->IAudioClock2_iface.lpVtbl = &AudioClock2_Vtbl;
    client->IAudioStreamVolume_iface.lpVtbl = &AudioStreamVolume_Vtbl;

    hr = CoCreateFreeThreadedMarshaler((IUnknown *)&client->IAudioClient_iface, &client->marshal);
    if (hr)
        WINE_ERR("CoCreateFreeThreadedMarshaler failed.\n");

}

static void qemu_audiosession_guest_init(struct qemu_audiosession *client)
{
    client->IAudioSessionControl2_iface.lpVtbl = &AudioSessionControl2_Vtbl;
    client->ISimpleAudioVolume_iface.lpVtbl = &SimpleAudioVolume_Vtbl;
    client->IChannelAudioVolume_iface.lpVtbl = &ChannelAudioVolume_Vtbl;
}

#else

HRESULT qemu_audioclient_host_create(IAudioClient *host, struct qemu_audioclient **client)
{
    struct qemu_audioclient *obj;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    WINE_TRACE("Created IAudioClient wrapper %p for host interface %p.\n", obj, host);

    obj->host_client = host;
    /* The other interfaces are queried via GetService, which doesn't work quite like
     * QueryInterface. In particular, it may return an error before the client is initialized,
     * and success afterwards. So query them when the app queries them. */

    *client = obj;
    return S_OK;
}

static HRESULT qemu_audiosession_host_create(IAudioSessionControl *host, struct qemu_audioclient *client,
        struct qemu_audiosession **session)
{
    struct qemu_audiosession *obj;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory.\n");
        return E_OUTOFMEMORY;
    }

    WINE_TRACE("Created IAudioSessionControl wrapper %p for host interface %p.\n", obj, host);

    hr = IAudioSessionControl_QueryInterface(host, &IID_IAudioSessionControl2, (void **)&obj->host_control);
    if (FAILED(hr))
        WINE_ERR("Failed to get IAudioSessionControl2\n");
    IAudioSessionControl2_Release(obj->host_control);

    obj->client = client;
    if (client)
    {
        hr = IAudioClient_GetService(client->host_client, &IID_IChannelAudioVolume, (void **)&obj->host_chan_vol);
        if (FAILED(hr))
            WINE_ERR("Failed to get IChannelAudioVolume\n");
        IChannelAudioVolume_Release(obj->host_chan_vol);

        hr = IAudioClient_GetService(client->host_client, &IID_ISimpleAudioVolume, (void **)&obj->host_simple_vol);
        if (FAILED(hr))
            WINE_ERR("Failed to get ISimpleAudioVolume\n");
        ISimpleAudioVolume_Release(obj->host_simple_vol);
    }

    *session = obj;
    return S_OK;
}

#endif
