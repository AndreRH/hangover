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

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <dxgi1_2.h>
#include <debug.h>
#else
#include <dxgi1_5.h>
#include <wine/debug.h>
#endif

#include "qemu_dxgi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_dxgi_device_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dxgi_device *impl_from_IDXGIDevice2(IDXGIDevice2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_device, IDXGIDevice2_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_device_QueryInterface(IDXGIDevice2 *iface, REFIID riid, void **object)
{
    struct qemu_dxgi_device_QueryInterface call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_QueryInterface *c = (struct qemu_dxgi_device_QueryInterface *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_QueryInterface(device->host, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_dxgi_device_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_device_AddRef(IDXGIDevice2 *iface)
{
    struct qemu_dxgi_device_AddRef call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_AddRef(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_AddRef *c = (struct qemu_dxgi_device_AddRef *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_AddRef(device->host);
}

#endif

struct qemu_dxgi_device_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_device_Release(IDXGIDevice2 *iface)
{
    struct qemu_dxgi_device_Release call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_Release(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_Release *c = (struct qemu_dxgi_device_Release *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_Release(device->host);
}

#endif

struct qemu_dxgi_device_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_SetPrivateData(IDXGIDevice2 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_device_SetPrivateData call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)device;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_SetPrivateData *c = (struct qemu_dxgi_device_SetPrivateData *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_SetPrivateData(device->host, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_device_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_SetPrivateDataInterface(IDXGIDevice2 *iface, REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_device_SetPrivateDataInterface call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.guid = (ULONG_PTR)guid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_SetPrivateDataInterface *c = (struct qemu_dxgi_device_SetPrivateDataInterface *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_SetPrivateDataInterface(device->host, QEMU_G2H(c->guid), QEMU_G2H(c->object));
}

#endif

struct qemu_dxgi_device_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_GetPrivateData(IDXGIDevice2 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_device_GetPrivateData call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)device;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_GetPrivateData *c = (struct qemu_dxgi_device_GetPrivateData *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_GetPrivateData(device->host, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_device_GetParent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_GetParent(IDXGIDevice2 *iface, REFIID riid, void **parent)
{
    struct qemu_dxgi_device_GetParent call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_GETPARENT);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.parent = (ULONG_PTR)parent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_GetParent(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_GetParent *c = (struct qemu_dxgi_device_GetParent *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_GetParent(device->host, QEMU_G2H(c->riid), QEMU_G2H(c->parent));
}

#endif

struct qemu_dxgi_device_GetAdapter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_GetAdapter(IDXGIDevice2 *iface, IDXGIAdapter **adapter)
{
    struct qemu_dxgi_device_GetAdapter call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_GETADAPTER);
    call.iface = (ULONG_PTR)device;
    call.adapter = (ULONG_PTR)adapter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_GetAdapter(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_GetAdapter *c = (struct qemu_dxgi_device_GetAdapter *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_GetAdapter(device->host, QEMU_G2H(c->adapter));
}

#endif

struct qemu_dxgi_device_CreateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t surface_count;
    uint64_t usage;
    uint64_t shared_resource;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_CreateSurface(IDXGIDevice2 *iface, const DXGI_SURFACE_DESC *desc, UINT surface_count, DXGI_USAGE usage, const DXGI_SHARED_RESOURCE *shared_resource, IDXGISurface **surface)
{
    struct qemu_dxgi_device_CreateSurface call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_CREATESURFACE);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.surface_count = surface_count;
    call.usage = usage;
    call.shared_resource = (ULONG_PTR)shared_resource;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_CreateSurface(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_CreateSurface *c = (struct qemu_dxgi_device_CreateSurface *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_CreateSurface(device->host, QEMU_G2H(c->desc), c->surface_count, c->usage, QEMU_G2H(c->shared_resource), QEMU_G2H(c->surface));
}

#endif

struct qemu_dxgi_device_QueryResourceResidency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resources;
    uint64_t residency;
    uint64_t resource_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_QueryResourceResidency(IDXGIDevice2 *iface, IUnknown *const *resources, DXGI_RESIDENCY *residency, UINT resource_count)
{
    struct qemu_dxgi_device_QueryResourceResidency call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_QUERYRESOURCERESIDENCY);
    call.iface = (ULONG_PTR)device;
    call.resources = (ULONG_PTR)resources;
    call.residency = (ULONG_PTR)residency;
    call.resource_count = resource_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_QueryResourceResidency(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_QueryResourceResidency *c = (struct qemu_dxgi_device_QueryResourceResidency *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_QueryResourceResidency(device->host, QEMU_G2H(c->resources), QEMU_G2H(c->residency), c->resource_count);
}

#endif

struct qemu_dxgi_device_SetGPUThreadPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_SetGPUThreadPriority(IDXGIDevice2 *iface, INT priority)
{
    struct qemu_dxgi_device_SetGPUThreadPriority call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_SETGPUTHREADPRIORITY);
    call.iface = (ULONG_PTR)device;
    call.priority = priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_SetGPUThreadPriority(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_SetGPUThreadPriority *c = (struct qemu_dxgi_device_SetGPUThreadPriority *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_SetGPUThreadPriority(device->host, c->priority);
}

#endif

struct qemu_dxgi_device_GetGPUThreadPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_GetGPUThreadPriority(IDXGIDevice2 *iface, INT *priority)
{
    struct qemu_dxgi_device_GetGPUThreadPriority call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_GETGPUTHREADPRIORITY);
    call.iface = (ULONG_PTR)device;
    call.priority = (ULONG_PTR)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_GetGPUThreadPriority(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_GetGPUThreadPriority *c = (struct qemu_dxgi_device_GetGPUThreadPriority *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_GetGPUThreadPriority(device->host, QEMU_G2H(c->priority));
}

#endif

struct qemu_dxgi_device_SetMaximumFrameLatency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t max_latency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_SetMaximumFrameLatency(IDXGIDevice2 *iface, UINT max_latency)
{
    struct qemu_dxgi_device_SetMaximumFrameLatency call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_SETMAXIMUMFRAMELATENCY);
    call.iface = (ULONG_PTR)device;
    call.max_latency = max_latency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_SetMaximumFrameLatency(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_SetMaximumFrameLatency *c = (struct qemu_dxgi_device_SetMaximumFrameLatency *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_SetMaximumFrameLatency(device->host, c->max_latency);
}

#endif

struct qemu_dxgi_device_GetMaximumFrameLatency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t max_latency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_GetMaximumFrameLatency(IDXGIDevice2 *iface, UINT *max_latency)
{
    struct qemu_dxgi_device_GetMaximumFrameLatency call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_GETMAXIMUMFRAMELATENCY);
    call.iface = (ULONG_PTR)device;
    call.max_latency = (ULONG_PTR)max_latency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_GetMaximumFrameLatency(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_GetMaximumFrameLatency *c = (struct qemu_dxgi_device_GetMaximumFrameLatency *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_GetMaximumFrameLatency(device->host, QEMU_G2H(c->max_latency));
}

#endif

struct qemu_dxgi_device_OfferResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_count;
    uint64_t resources;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_OfferResources(IDXGIDevice2 *iface, UINT resource_count, IDXGIResource * const *resources, DXGI_OFFER_RESOURCE_PRIORITY priority)
{
    struct qemu_dxgi_device_OfferResources call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_OFFERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.resource_count = resource_count;
    call.resources = (ULONG_PTR)resources;
    call.priority = priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_OfferResources(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_OfferResources *c = (struct qemu_dxgi_device_OfferResources *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_OfferResources(device->host, c->resource_count, QEMU_G2H(c->resources), c->priority);
}

#endif

struct qemu_dxgi_device_ReclaimResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_count;
    uint64_t resources;
    uint64_t discarded;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_ReclaimResources(IDXGIDevice2 *iface, UINT resource_count, IDXGIResource * const *resources, BOOL *discarded)
{
    struct qemu_dxgi_device_ReclaimResources call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_RECLAIMRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.resource_count = resource_count;
    call.resources = (ULONG_PTR)resources;
    call.discarded = (ULONG_PTR)discarded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_ReclaimResources(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_ReclaimResources *c = (struct qemu_dxgi_device_ReclaimResources *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_ReclaimResources(device->host, c->resource_count, QEMU_G2H(c->resources), QEMU_G2H(c->discarded));
}

#endif

struct qemu_dxgi_device_EnqueueSetEvent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_device_EnqueueSetEvent(IDXGIDevice2 *iface, HANDLE event)
{
    struct qemu_dxgi_device_EnqueueSetEvent call;
    struct qemu_dxgi_device *device = impl_from_IDXGIDevice2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_DEVICE_ENQUEUESETEVENT);
    call.iface = (ULONG_PTR)device;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_device_EnqueueSetEvent(struct qemu_syscall *call)
{
    struct qemu_dxgi_device_EnqueueSetEvent *c = (struct qemu_dxgi_device_EnqueueSetEvent *)call;
    struct qemu_dxgi_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDXGIDevice2_EnqueueSetEvent(device->host, QEMU_G2H(c->event));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDXGIDevice2Vtbl dxgi_device_vtbl =
{
    /* IUnknown methods */
    dxgi_device_QueryInterface,
    dxgi_device_AddRef,
    dxgi_device_Release,
    /* IDXGIObject methods */
    dxgi_device_SetPrivateData,
    dxgi_device_SetPrivateDataInterface,
    dxgi_device_GetPrivateData,
    dxgi_device_GetParent,
    /* IDXGIDevice methods */
    dxgi_device_GetAdapter,
    dxgi_device_CreateSurface,
    dxgi_device_QueryResourceResidency,
    dxgi_device_SetGPUThreadPriority,
    dxgi_device_GetGPUThreadPriority,
    /* IDXGIDevice1 methods */
    dxgi_device_SetMaximumFrameLatency,
    dxgi_device_GetMaximumFrameLatency,
    /* IDXGIDevice2 methods */
    dxgi_device_OfferResources,
    dxgi_device_ReclaimResources,
    dxgi_device_EnqueueSetEvent,
};

void qemu_dxgi_device_guest_init(struct qemu_dxgi_device *device)
{
    device->IDXGIDevice2_iface.lpVtbl = &dxgi_device_vtbl;
}

#else

#endif
