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

struct qemu_mmdevcol
{
    /* Guest fields */
    IMMDeviceCollection IMMDeviceCollection_iface;

    /* Host fields */
    IMMDeviceCollection *host;
};

struct qemu_mmdevenum
{
    /* Guest fields */
    IMMDeviceEnumerator IMMDeviceEnumerator_iface;

    /* Host fields */
    IMMDeviceEnumerator *host;
};

struct qemu_mmpropstore
{
    /* Guest fields */
    IPropertyStore IPropertyStore_iface;

    /* Host fields */
    IPropertyStore *host;
};

struct qemu_MMDevice_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmdevice *impl_from_IMMDevice(IMMDevice *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevice, IMMDevice_iface);
}

static inline struct qemu_mmdevice *impl_from_IMMEndpoint(IMMEndpoint *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevice, IMMEndpoint_iface);
}

static HRESULT WINAPI MMDevice_QueryInterface(IMMDevice *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevice_QueryInterface call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static struct list device_list = LIST_INIT(device_list);
static CRITICAL_SECTION mmdevapi_cs = {0, -1, 0, 0, 0, 0};

static struct qemu_mmdevice *device_from_host(IMMDevice *host, BOOL *new_dev)
{
    struct qemu_mmdevice *wrapper;

    EnterCriticalSection(&mmdevapi_cs);

    *new_dev = FALSE;
    LIST_FOR_EACH_ENTRY(wrapper, &device_list, struct qemu_mmdevice, entry)
    {
        if (wrapper->host_device == host)
        {
            LeaveCriticalSection(&mmdevapi_cs);
            WINE_TRACE("Returning existing wrapper %p for host device %p.\n", wrapper, host);
            return wrapper;
        }
    }

    wrapper = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*wrapper));
    if (!wrapper)
    {
        WINE_WARN("Out of memory.\n");
        LeaveCriticalSection(&mmdevapi_cs);
        return NULL;
    }
    WINE_TRACE("Allocated wrapper %p for host device %p.\n", wrapper, host);

    wrapper->host_device = host;
    IMMDevice_QueryInterface(host, &IID_IMMEndpoint, (void **)&wrapper->host_endpoint);
    IMMEndpoint_Release(wrapper->host_endpoint);

    list_add_head(&device_list, &wrapper->entry);
    *new_dev = TRUE;
    LeaveCriticalSection(&mmdevapi_cs);

    return wrapper;
}

void qemu_MMDevice_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevice_QueryInterface *c = (struct qemu_MMDevice_QueryInterface *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_QueryInterface(device->host_device, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevice_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevice_AddRef(IMMDevice *iface)
{
    struct qemu_MMDevice_AddRef call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevice_AddRef *c = (struct qemu_MMDevice_AddRef *)call;
    struct qemu_mmdevice *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_AddRef(device->host_device);
}

#endif

struct qemu_MMDevice_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevice_Release(IMMDevice *iface)
{
    struct qemu_MMDevice_Release call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevice_Release *c = (struct qemu_MMDevice_Release *)call;
    struct qemu_mmdevice *device;

    WINE_TRACE("\n");
    /* No need to release here, devices stay around until the enumerator is freed. */
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_Release(device->host_device);
}

#endif

struct qemu_MMDevice_Activate
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t clsctx;
    uint64_t params;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_Activate(IMMDevice *iface, REFIID riid, DWORD clsctx, PROPVARIANT *params, void **ppv)
{
    struct qemu_MMDevice_Activate call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);
    struct qemu_audioclient *client;
    struct qemu_sessmgr *sessmgr;
    struct qemu_volume *volume;
    HRESULT hr = E_FAIL;

    if (!ppv)
    {
        WINE_WARN("Output pointer is NULL.\n");
        return E_POINTER;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_ACTIVATE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.clsctx = clsctx;
    call.params = (ULONG_PTR)params;
    call.ppv = (ULONG_PTR)ppv;

    if (IsEqualIID(riid, &IID_IAudioClient))
    {
        qemu_syscall(&call.super);
        hr = call.super.iret;

        if (SUCCEEDED(hr))
        {
            client = (struct qemu_audioclient *)(ULONG_PTR)call.ppv;
            qemu_audioclient_guest_init(client);
            *ppv = &client->IAudioClient_iface;
        }
    }
    else if (IsEqualIID(riid, &IID_IAudioEndpointVolume) || IsEqualIID(riid, &IID_IAudioEndpointVolumeEx))
    {
        qemu_syscall(&call.super);
        hr = call.super.iret;
        
        if (SUCCEEDED(hr))
        {
            volume = (struct qemu_volume *)(ULONG_PTR)call.ppv;
            qemu_volume_guest_init(volume);
            *ppv = &volume->IAudioEndpointVolumeEx_iface;
        }
    }
    else if (IsEqualIID(riid, &IID_IAudioSessionManager) || IsEqualIID(riid, &IID_IAudioSessionManager2))
    {
        qemu_syscall(&call.super);
        hr = call.super.iret;

        if (SUCCEEDED(hr))
        {
            sessmgr = (struct qemu_sessmgr *)(ULONG_PTR)call.ppv;
            qemu_sessmgr_guest_init(sessmgr);
            *ppv = &sessmgr->IAudioSessionManager2_iface;
        }
    }
    else if (IsEqualIID(riid, &IID_IBaseFilter))
    {
        /* CoCreateInstance + extras */
        WINE_FIXME("IID_IBaseFilter unsupported\n");
    }
    else if (IsEqualIID(riid, &IID_IDeviceTopology))
    {
        /* Not handled in Wine either */
        WINE_FIXME("IID_IDeviceTopology unsupported\n");
    }
    else if (IsEqualIID(riid, &IID_IDirectSound)
            || IsEqualIID(riid, &IID_IDirectSound8))
    {
        /* CoCreateInstance */
        WINE_FIXME("IID_IDirectSound unsupported\n");
    }
    else if (IsEqualIID(riid, &IID_IDirectSoundCapture))
    {
        /* CoCreateInstance */
        WINE_FIXME("IID_IDirectSoundCapture unsupported\n");
    }
    else
    {
        WINE_ERR("Invalid/unknown iid %s\n", wine_dbgstr_guid(riid));
    }

    return hr;
}

#else

void qemu_MMDevice_Activate(struct qemu_syscall *call)
{
    struct qemu_MMDevice_Activate *c = (struct qemu_MMDevice_Activate *)call;
    struct qemu_mmdevice *device;
    const IID *iid;
    HRESULT hr = E_FAIL;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);
    if (c->params)
        WINE_FIXME("Params not handled yet\n");

    if (IsEqualIID(iid, &IID_IAudioClient))
    {
        IAudioClient *host;
        struct qemu_audioclient *client;

        hr = IMMDevice_Activate(device->host_device, iid, c->clsctx, QEMU_G2H(c->params), (void **)&host);
        if (SUCCEEDED(hr))
        {
            hr = qemu_audioclient_host_create(host, &client);
            if (SUCCEEDED(hr))
                c->ppv = QEMU_H2G(client);
            else
                IAudioClient_Release(host);
        }
    }
    else if (IsEqualIID(iid, &IID_IAudioSessionManager) || IsEqualIID(iid, &IID_IAudioSessionManager2))
    {
        IAudioSessionManager2 *host;
        struct qemu_sessmgr *mgr;
        
        hr = IMMDevice_Activate(device->host_device, &IID_IAudioSessionManager2,
                                c->clsctx, QEMU_G2H(c->params), (void **)&host);
        if (SUCCEEDED(hr))
        {
            hr = qemu_sessmgr_host_create(host, &mgr);
            if (SUCCEEDED(hr))
                c->ppv = QEMU_H2G(mgr);
            else
                IAudioSessionManager2_Release(host);
        }
    }
    else if (IsEqualIID(iid, &IID_IAudioEndpointVolume) || IsEqualIID(iid, &IID_IAudioEndpointVolumeEx))
    {
        IAudioEndpointVolumeEx *host;
        struct qemu_volume *volume;

        hr = IMMDevice_Activate(device->host_device, &IID_IAudioEndpointVolumeEx,
                c->clsctx, QEMU_G2H(c->params), (void **)&host);
        if (SUCCEEDED(hr))
        {
            hr = qemu_volume_host_create(host, &volume);
            if (SUCCEEDED(hr))
                c->ppv = QEMU_H2G(volume);
            else
                IAudioEndpointVolumeEx_Release(host);
        }
    }
    else
    {
        WINE_ERR("Unexpected IID\n");
    }

    c->super.iret = hr;
}

#endif

struct qemu_MMDevice_OpenPropertyStore
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t access;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static const IPropertyStoreVtbl MMDevPropVtbl;
static HRESULT WINAPI MMDevice_OpenPropertyStore(IMMDevice *iface, DWORD access, IPropertyStore **ppv)
{
    struct qemu_MMDevice_OpenPropertyStore call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);
    struct qemu_mmpropstore *store;

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_OPENPROPERTYSTORE);
    call.iface = (ULONG_PTR)device;
    call.access = access;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (ppv)
            *ppv = NULL;
        return call.super.iret;
    }

    store = (struct qemu_mmpropstore *)(ULONG_PTR)call.ppv;
    store->IPropertyStore_iface.lpVtbl = &MMDevPropVtbl;
    *ppv = &store->IPropertyStore_iface;
    
    return call.super.iret;
}

#else

void qemu_MMDevice_OpenPropertyStore(struct qemu_syscall *call)
{
    struct qemu_MMDevice_OpenPropertyStore *c = (struct qemu_MMDevice_OpenPropertyStore *)call;
    struct qemu_mmdevice *device;
    struct qemu_mmpropstore *store;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    store = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*store));
    if (!store)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    
    c->super.iret = IMMDevice_OpenPropertyStore(device->host_device, c->access, c->ppv ? &store->host : NULL);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, store);
        return;
    }
    c->ppv = QEMU_H2G(store);
}

#endif

struct qemu_MMDevice_GetId
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t itemid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_GetId(IMMDevice *iface, WCHAR **itemid)
{
    struct qemu_MMDevice_GetId call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_GETID);
    call.iface = (ULONG_PTR)device;
    call.itemid = (ULONG_PTR)itemid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_GetId(struct qemu_syscall *call)
{
    struct qemu_MMDevice_GetId *c = (struct qemu_MMDevice_GetId *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_GetId(device->host_device, QEMU_G2H(c->itemid));
}

#endif

struct qemu_MMDevice_GetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_GetState(IMMDevice *iface, DWORD *state)
{
    struct qemu_MMDevice_GetState call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_GETSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static const IMMDeviceVtbl MMDeviceVtbl =
{
    MMDevice_QueryInterface,
    MMDevice_AddRef,
    MMDevice_Release,
    MMDevice_Activate,
    MMDevice_OpenPropertyStore,
    MMDevice_GetId,
    MMDevice_GetState
};

#else

void qemu_MMDevice_GetState(struct qemu_syscall *call)
{
    struct qemu_MMDevice_GetState *c = (struct qemu_MMDevice_GetState *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_GetState(device->host_device, QEMU_G2H(c->state));
}

#endif

struct qemu_MMEndpoint_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMEndpoint_QueryInterface(IMMEndpoint *iface, REFIID riid, void **ppv)
{
    struct qemu_MMEndpoint_QueryInterface call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_QueryInterface *c = (struct qemu_MMEndpoint_QueryInterface *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_QueryInterface(device->host_endpoint, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMEndpoint_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMEndpoint_AddRef(IMMEndpoint *iface)
{
    struct qemu_MMEndpoint_AddRef call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_AddRef *c = (struct qemu_MMEndpoint_AddRef *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_AddRef(device->host_endpoint);
}

#endif

struct qemu_MMEndpoint_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMEndpoint_Release(IMMEndpoint *iface)
{
    struct qemu_MMEndpoint_Release call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_Release(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_Release *c = (struct qemu_MMEndpoint_Release *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_Release(device->host_endpoint);
}

#endif

struct qemu_MMEndpoint_GetDataFlow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flow;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMEndpoint_GetDataFlow(IMMEndpoint *iface, EDataFlow *flow)
{
    struct qemu_MMEndpoint_GetDataFlow call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_GETDATAFLOW);
    call.iface = (ULONG_PTR)device;
    call.flow = (ULONG_PTR)flow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static const IMMEndpointVtbl MMEndpointVtbl =
{
    MMEndpoint_QueryInterface,
    MMEndpoint_AddRef,
    MMEndpoint_Release,
    MMEndpoint_GetDataFlow
};

#else

void qemu_MMEndpoint_GetDataFlow(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_GetDataFlow *c = (struct qemu_MMEndpoint_GetDataFlow *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_GetDataFlow(device->host_endpoint, QEMU_G2H(c->flow));
}

#endif

struct qemu_MMDevCol_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmdevcol *impl_from_IMMDeviceCollection(IMMDeviceCollection *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevcol, IMMDeviceCollection_iface);
}

static HRESULT WINAPI MMDevCol_QueryInterface(IMMDeviceCollection *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevCol_QueryInterface call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    WINE_TRACE("(%p)->(%s, %p)\n", col, wine_dbgstr_guid(riid), ppv);
    
    if (!ppv)
        return E_POINTER;

    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IMMDeviceCollection))
        *ppv = &col->IMMDeviceCollection_iface;
    else
        *ppv = NULL;

    if (*ppv)
    {
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)col;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return E_NOINTERFACE;
}

#else

void qemu_MMDevCol_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_QueryInterface *c = (struct qemu_MMDevCol_QueryInterface *)call;
    struct qemu_mmdevcol *col;
    IUnknown *obj;
    
    WINE_TRACE("\n");
    col = QEMU_G2H(c->iface);
    
    c->super.iret = IMMDeviceCollection_QueryInterface(col->host, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                   wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_MMDevCol_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevCol_AddRef(IMMDeviceCollection *iface)
{
    struct qemu_MMDevCol_AddRef call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_ADDREF);
    call.iface = (ULONG_PTR)col;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_AddRef *c = (struct qemu_MMDevCol_AddRef *)call;
    struct qemu_mmdevcol *col;

    WINE_TRACE("\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_AddRef(col->host);
}

#endif

struct qemu_MMDevCol_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevCol_Release(IMMDeviceCollection *iface)
{
    struct qemu_MMDevCol_Release call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_RELEASE);
    call.iface = (ULONG_PTR)col;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_Release *c = (struct qemu_MMDevCol_Release *)call;
    struct qemu_mmdevcol *col;

    WINE_TRACE("\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_Release(col->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying device collection wrapper %p, host %p.\n", col, col->host);
        HeapFree(GetProcessHeap(), 0, col);
    }
}

#endif

struct qemu_MMDevCol_GetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t numdevs;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevCol_GetCount(IMMDeviceCollection *iface, UINT *numdevs)
{
    struct qemu_MMDevCol_GetCount call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_GETCOUNT);
    call.iface = (ULONG_PTR)col;
    call.numdevs = (ULONG_PTR)numdevs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_GetCount(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_GetCount *c = (struct qemu_MMDevCol_GetCount *)call;
    struct qemu_mmdevcol *col;

    WINE_TRACE("\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_GetCount(col->host, QEMU_G2H(c->numdevs));
}

#endif

struct qemu_MMDevCol_Item
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t n;
    uint64_t dev;
    uint64_t new_dev;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevCol_Item(IMMDeviceCollection *iface, UINT n, IMMDevice **dev)
{
    struct qemu_MMDevCol_Item call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);
    struct qemu_mmdevice *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_ITEM);
    call.iface = (ULONG_PTR)col;
    call.n = n;
    call.dev = (ULONG_PTR)dev;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (dev)
            *dev = NULL;
        return call.super.iret;
    }
    
    impl = (struct qemu_mmdevice *)(ULONG_PTR)call.dev;
    if (call.new_dev)
    {
        impl->IMMDevice_iface.lpVtbl = &MMDeviceVtbl;
        impl->IMMEndpoint_iface.lpVtbl = &MMEndpointVtbl;
    }
    *dev = &impl->IMMDevice_iface;
    
    return call.super.iret;
}

#else

void qemu_MMDevCol_Item(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_Item *c = (struct qemu_MMDevCol_Item *)call;
    struct qemu_mmdevcol *col;
    struct qemu_mmdevice *device;
    IMMDevice *host;
    BOOL new_dev;

    WINE_TRACE("\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_Item(col->host, c->n, c->dev ? &host : NULL);
    if (FAILED(c->super.iret))
        return;
    
    device = device_from_host(host, &new_dev);
    if (!device)
    {
        IMMDevice_Release(host);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    c->new_dev = new_dev;
    c->dev = QEMU_H2G(device);
}

#endif

struct qemu_MMDevEnum_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmdevenum *impl_from_IMMDeviceEnumerator(IMMDeviceEnumerator *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevenum, IMMDeviceEnumerator_iface);
}

static HRESULT WINAPI MMDevEnum_QueryInterface(IMMDeviceEnumerator *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevEnum_QueryInterface call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    if (!ppv)
        return E_POINTER;

    if (IsEqualIID(riid, &IID_IUnknown)
            || IsEqualIID(riid, &IID_IMMDeviceEnumerator))
        *ppv = &devenum->IMMDeviceEnumerator_iface;
    else
    {
        *ppv = NULL;

        call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_QUERYINTERFACE);
        call.iface = (ULONG_PTR)devenum;
        call.riid = (ULONG_PTR)riid;
        qemu_syscall(&call.super);
    }

    if (!*ppv)
        return E_NOINTERFACE;

    IUnknown_AddRef((IUnknown*)*ppv);

    return S_OK;
}

#else

static struct qemu_mmdevenum *MMDevEnumerator;

void qemu_MMDevEnum_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_QueryInterface *c = (struct qemu_MMDevEnum_QueryInterface *)call;
    struct qemu_mmdevenum *devenum;
    IUnknown *obj;

    WINE_TRACE("\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_QueryInterface(devenum->host, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_MMDevEnum_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevEnum_AddRef(IMMDeviceEnumerator *iface)
{
    struct qemu_MMDevEnum_AddRef call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_ADDREF);
    call.iface = (ULONG_PTR)devenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_AddRef *c = (struct qemu_MMDevEnum_AddRef *)call;
    struct qemu_mmdevenum *devenum;

    WINE_TRACE("\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_AddRef(devenum->host);
}

#endif

struct qemu_MMDevEnum_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevEnum_Release(IMMDeviceEnumerator *iface)
{
    struct qemu_MMDevEnum_Release call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_RELEASE);
    call.iface = (ULONG_PTR)devenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_Release *c = (struct qemu_MMDevEnum_Release *)call;
    struct qemu_mmdevenum *devenum;
    struct qemu_mmdevice *dev1, *dev2;

    WINE_TRACE("\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_Release(devenum->host);

    if (!c->super.iret)
    {
        WINE_TRACE("Destroying device enumerator proxy %p, host enum %p\n", devenum, devenum->host);
        EnterCriticalSection(&mmdevapi_cs);

        LIST_FOR_EACH_ENTRY_SAFE(dev1, dev2, &device_list, struct qemu_mmdevice, entry)
        {
            list_remove(&dev1->entry);
            WINE_TRACE("Destroying device wrapper %p, host %p.\n", dev1, dev1->host_device);
            HeapFree(GetProcessHeap(), 0, dev1);
        }

        HeapFree(GetProcessHeap(), 0, devenum);
        MMDevEnumerator = NULL;

        LeaveCriticalSection(&mmdevapi_cs);
    }
}

#endif

struct qemu_MMDevEnum_EnumAudioEndpoints
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flow;
    uint64_t mask;
    uint64_t devices;
};

#ifdef QEMU_DLL_GUEST

static const IMMDeviceCollectionVtbl MMDevColVtbl =
{
    MMDevCol_QueryInterface,
    MMDevCol_AddRef,
    MMDevCol_Release,
    MMDevCol_GetCount,
    MMDevCol_Item
};

static HRESULT WINAPI MMDevEnum_EnumAudioEndpoints(IMMDeviceEnumerator *iface, EDataFlow flow, DWORD mask,
        IMMDeviceCollection **devices)
{
    struct qemu_MMDevEnum_EnumAudioEndpoints call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);
    struct qemu_mmdevcol *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_ENUMAUDIOENDPOINTS);
    call.iface = (ULONG_PTR)devenum;
    call.flow = flow;
    call.mask = mask;
    call.devices = (ULONG_PTR)devices;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (devices)
            *devices = NULL;
        return call.super.iret;
    }

    impl = (struct qemu_mmdevcol *)(ULONG_PTR)call.devices;
    impl->IMMDeviceCollection_iface.lpVtbl = &MMDevColVtbl;
    *devices = &impl->IMMDeviceCollection_iface;

    return call.super.iret;
}

#else

void qemu_MMDevEnum_EnumAudioEndpoints(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_EnumAudioEndpoints *c = (struct qemu_MMDevEnum_EnumAudioEndpoints *)call;
    struct qemu_mmdevenum *devenum;
    struct qemu_mmdevcol *col;
    IMMDeviceCollection *host;

    WINE_TRACE("\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_EnumAudioEndpoints(devenum->host, c->flow, c->mask,
            c->devices ? &host : NULL);
    if (FAILED(c->super.iret))
        return;

    col = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*col));
    if (!col)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = E_OUTOFMEMORY;
        IMMDeviceCollection_Release(host);
        return;
    }
    WINE_TRACE("Created IMMDeviceCollection wrapper %p for host iface %p.\n", col, host);
    col->host = host;
    c->devices = QEMU_H2G(col);
}

#endif

struct qemu_MMDevEnum_GetDefaultAudioEndpoint
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flow;
    uint64_t role;
    uint64_t device;
    uint64_t new_dev;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_GetDefaultAudioEndpoint(IMMDeviceEnumerator *iface, EDataFlow flow, ERole role,
        IMMDevice **device)
{
    struct qemu_MMDevEnum_GetDefaultAudioEndpoint call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);
    struct qemu_mmdevice *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_GETDEFAULTAUDIOENDPOINT);
    call.iface = (ULONG_PTR)devenum;
    call.flow = flow;
    call.role = role;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (device)
            *device = NULL;
        return call.super.iret;
    }

    impl = (struct qemu_mmdevice *)(ULONG_PTR)call.device;
    if (call.new_dev)
    {
        impl->IMMDevice_iface.lpVtbl = &MMDeviceVtbl;
        impl->IMMEndpoint_iface.lpVtbl = &MMEndpointVtbl;
    }
    *device = &impl->IMMDevice_iface;

    return call.super.iret;
}

#else

void qemu_MMDevEnum_GetDefaultAudioEndpoint(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_GetDefaultAudioEndpoint *c = (struct qemu_MMDevEnum_GetDefaultAudioEndpoint *)call;
    struct qemu_mmdevenum *devenum;
    struct qemu_mmdevice *device;
    IMMDevice *host;
    BOOL new_dev;

    WINE_TRACE("\n");
    devenum = QEMU_G2H(c->iface);

    c->new_dev = FALSE;
    c->super.iret = IMMDeviceEnumerator_GetDefaultAudioEndpoint(devenum->host, c->flow, c->role,
            c->device ? &host : NULL);
    if (FAILED(c->super.iret))
        return;

    device = device_from_host(host, &new_dev);
    if (!device)
    {
        IMMDevice_Release(host);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    c->new_dev = new_dev;
    c->device = QEMU_H2G(device);
}

#endif

struct qemu_MMDevEnum_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t device;
    uint64_t new_dev;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_GetDevice(IMMDeviceEnumerator *iface, const WCHAR *name, IMMDevice **device)
{
    struct qemu_MMDevEnum_GetDevice call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);
    struct qemu_mmdevice *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_GETDEVICE);
    call.iface = (ULONG_PTR)devenum;
    call.name = (ULONG_PTR)name;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (device)
            *device = NULL;
        return call.super.iret;
    }

    impl = (struct qemu_mmdevice *)(ULONG_PTR)call.device;
    if (call.new_dev)
    {
        impl->IMMDevice_iface.lpVtbl = &MMDeviceVtbl;
        impl->IMMEndpoint_iface.lpVtbl = &MMEndpointVtbl;
    }
    *device = &impl->IMMDevice_iface;

    return call.super.iret;
}

#else

void qemu_MMDevEnum_GetDevice(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_GetDevice *c = (struct qemu_MMDevEnum_GetDevice *)call;
    struct qemu_mmdevenum *devenum;
    struct qemu_mmdevice *device;
    IMMDevice *host;
    BOOL new_dev;

    WINE_TRACE("\n");
    devenum = QEMU_G2H(c->iface);

    c->new_dev = FALSE;
    c->super.iret = IMMDeviceEnumerator_GetDevice(devenum->host, QEMU_G2H(c->name), c->device ? &host : NULL);
    if (FAILED(c->super.iret))
        return;
    
    device = device_from_host(host, &new_dev);
    if (!device)
    {
        IMMDevice_Release(host);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    c->new_dev = new_dev;
    c->device = QEMU_H2G(device);
}

#endif

struct qemu_MMDevEnum_RegisterEndpointNotificationCallback
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t client;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_RegisterEndpointNotificationCallback(IMMDeviceEnumerator *iface, IMMNotificationClient *client)
{
    struct qemu_MMDevEnum_RegisterEndpointNotificationCallback call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_REGISTERENDPOINTNOTIFICATIONCALLBACK);
    call.iface = (ULONG_PTR)devenum;
    call.client = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_RegisterEndpointNotificationCallback(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_RegisterEndpointNotificationCallback *c = (struct qemu_MMDevEnum_RegisterEndpointNotificationCallback *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_RegisterEndpointNotificationCallback(devenum->host, QEMU_G2H(c->client));
}

#endif

struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t client;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_UnregisterEndpointNotificationCallback(IMMDeviceEnumerator *iface, IMMNotificationClient *client)
{
    struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_UNREGISTERENDPOINTNOTIFICATIONCALLBACK);
    call.iface = (ULONG_PTR)devenum;
    call.client = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_UnregisterEndpointNotificationCallback(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback *c = (struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_UnregisterEndpointNotificationCallback(devenum->host, QEMU_G2H(c->client));
}

#endif

struct qemu_MMDevPropStore_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmpropstore *impl_from_IPropertyStore(IPropertyStore *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmpropstore, IPropertyStore_iface);
}

static HRESULT WINAPI MMDevPropStore_QueryInterface(IPropertyStore *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevPropStore_QueryInterface call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)store;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_QueryInterface *c = (struct qemu_MMDevPropStore_QueryInterface *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_QueryInterface(store->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevPropStore_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevPropStore_AddRef(IPropertyStore *iface)
{
    struct qemu_MMDevPropStore_AddRef call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_ADDREF);
    call.iface = (ULONG_PTR)store;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_AddRef *c = (struct qemu_MMDevPropStore_AddRef *)call;
    struct qemu_mmpropstore *store;

    WINE_TRACE("\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_AddRef(store->host);
}

#endif

struct qemu_MMDevPropStore_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevPropStore_Release(IPropertyStore *iface)
{
    struct qemu_MMDevPropStore_Release call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_RELEASE);
    call.iface = (ULONG_PTR)store;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_Release *c = (struct qemu_MMDevPropStore_Release *)call;
    struct qemu_mmpropstore *store;

    WINE_TRACE("\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_Release(store->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying IPropertyStore wrapper %p, host %p.\n", store, store->host);
        HeapFree(GetProcessHeap(), 0, store);
    }
}

#endif

struct qemu_MMDevPropStore_GetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t nprops;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_GetCount(IPropertyStore *iface, DWORD *nprops)
{
    struct qemu_MMDevPropStore_GetCount call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_GETCOUNT);
    call.iface = (ULONG_PTR)store;
    call.nprops = (ULONG_PTR)nprops;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_GetCount(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_GetCount *c = (struct qemu_MMDevPropStore_GetCount *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_GetCount(store->host, QEMU_G2H(c->nprops));
}

#endif

struct qemu_MMDevPropStore_GetAt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prop;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_GetAt(IPropertyStore *iface, DWORD prop, PROPERTYKEY *key)
{
    struct qemu_MMDevPropStore_GetAt call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_GETAT);
    call.iface = (ULONG_PTR)store;
    call.prop = prop;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_GetAt(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_GetAt *c = (struct qemu_MMDevPropStore_GetAt *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_GetAt(store->host, c->prop, QEMU_G2H(c->key));
}

#endif

struct qemu_MMDevPropStore_GetValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t key;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_GetValue(IPropertyStore *iface, REFPROPERTYKEY key, PROPVARIANT *pv)
{
    struct qemu_MMDevPropStore_GetValue call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_GETVALUE);
    call.iface = (ULONG_PTR)store;
    call.key = (ULONG_PTR)key;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_GetValue(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_GetValue *c = (struct qemu_MMDevPropStore_GetValue *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_GetValue(store->host, QEMU_G2H(c->key), QEMU_G2H(c->pv));
}

#endif

struct qemu_MMDevPropStore_SetValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t key;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_SetValue(IPropertyStore *iface, REFPROPERTYKEY key, REFPROPVARIANT pv)
{
    struct qemu_MMDevPropStore_SetValue call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_SETVALUE);
    call.iface = (ULONG_PTR)store;
    call.key = (ULONG_PTR)key;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_SetValue(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_SetValue *c = (struct qemu_MMDevPropStore_SetValue *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_SetValue(store->host, QEMU_G2H(c->key), QEMU_G2H(c->pv));
}

#endif

struct qemu_MMDevPropStore_Commit
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_Commit(IPropertyStore *iface)
{
    struct qemu_MMDevPropStore_Commit call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_COMMIT);
    call.iface = (ULONG_PTR)store;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static const IPropertyStoreVtbl MMDevPropVtbl =
{
    MMDevPropStore_QueryInterface,
    MMDevPropStore_AddRef,
    MMDevPropStore_Release,
    MMDevPropStore_GetCount,
    MMDevPropStore_GetAt,
    MMDevPropStore_GetValue,
    MMDevPropStore_SetValue,
    MMDevPropStore_Commit
};

#else

void qemu_MMDevPropStore_Commit(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_Commit *c = (struct qemu_MMDevPropStore_Commit *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_Commit(store->host);
}

#endif

struct qemu_MMDevEnum_Create
{
    struct qemu_syscall super;
    uint64_t new_object;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static const IMMDeviceEnumeratorVtbl MMDevEnumVtbl =
{
    MMDevEnum_QueryInterface,
    MMDevEnum_AddRef,
    MMDevEnum_Release,
    MMDevEnum_EnumAudioEndpoints,
    MMDevEnum_GetDefaultAudioEndpoint,
    MMDevEnum_GetDevice,
    MMDevEnum_RegisterEndpointNotificationCallback,
    MMDevEnum_UnregisterEndpointNotificationCallback
};

HRESULT MMDevEnum_Create(const IID *iid, void **ppv)
{
    struct qemu_MMDevEnum_Create call;
    struct qemu_mmdevenum *devenum;
    HRESULT hr;

    WINE_TRACE("\n");
    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_CREATE);
    qemu_syscall(&call.super);

    devenum = (struct qemu_mmdevenum *)(ULONG_PTR)call.object;

    if (FAILED(call.super.iret))
        return call.super.iret;

    if (call.new_object)
        devenum->IMMDeviceEnumerator_iface.lpVtbl = &MMDevEnumVtbl;

    hr = IMMDeviceEnumerator_QueryInterface(&devenum->IMMDeviceEnumerator_iface, iid, ppv);
    IMMDeviceEnumerator_Release(&devenum->IMMDeviceEnumerator_iface);
    return hr;
}

#else

void qemu_MMDevEnum_Create(struct qemu_syscall *call)
{
    /* FIXME: Do I need any kind of lock for the globals? */
    struct qemu_MMDevEnum_Create *c = (struct qemu_MMDevEnum_Create *)call;
    struct qemu_mmdevenum *devenum = MMDevEnumerator;
    HRESULT hr;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *factory;

    c->new_object = FALSE;
    if (devenum)
    {
        c->super.iret = S_OK;
        c->object = QEMU_H2G(devenum);
        return;
    }

    devenum = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*devenum));
    if (!devenum)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    p_DllGetClassObject = (void *)GetProcAddress(mmdevapi_mod, "DllGetClassObject");
    if (!p_DllGetClassObject)
        WINE_ERR("Cannot get DllGetClassObject in mmdevapi.dll.\n");

    hr = p_DllGetClassObject(&CLSID_MMDeviceEnumerator, &IID_IClassFactory, (void *)&factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(factory, NULL, &IID_IMMDeviceEnumerator, (void **)&devenum->host);
    IClassFactory_Release(factory);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IIMMDeviceEnumerator object.\n");
        HeapFree(GetProcessHeap(), 0, devenum);
        c->super.iret = hr;
        return;
    }

    c->super.iret = hr;
    c->object = QEMU_H2G(devenum);
    c->new_object = TRUE;
    MMDevEnumerator = devenum;
    WINE_TRACE("Created device enumerator %p, wrapper %p\n", devenum->host, devenum);
}

#endif
