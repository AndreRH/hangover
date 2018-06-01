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
#include <d3d11_1.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemudxgi.h"

#ifdef QEMU_DLL_GUEST

#include <dxgi1_2.h>
#include <debug.h>
#include <initguid.h>

DEFINE_GUID(IID_IDXGISurface1, 0x4ae63092, 0x6327, 0x4c1b, 0x80,0xae, 0xbf,0xe1,0x2e,0xa3,0x2b,0x86);

#else

#include <dxgi1_5.h>
#include <wine/debug.h>

#endif

#include "qemu_dxgi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_dxgi_surface_inner_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dxgi_surface *impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_surface, IUnknown_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_surface_inner_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    struct qemu_dxgi_surface_inner_QueryInterface call;
    struct qemu_dxgi_surface *surface = impl_from_IUnknown(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (IsEqualGUID(riid, &IID_IDXGISurface1)
            || IsEqualGUID(riid, &IID_IDXGISurface)
            || IsEqualGUID(riid, &IID_IDXGIDeviceSubObject)
            || IsEqualGUID(riid, &IID_IDXGIObject)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        IDXGISurface_AddRef(&surface->IDXGISurface1_iface);
        *out = &surface->IDXGISurface1_iface;
        return S_OK;
    }

    /* Ask the host if we should know about it. */
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_INNER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;
    qemu_syscall(&call.super);

    WINE_WARN("%s not implemented, returning E_NOINTERFACE\n", wine_dbgstr_guid(riid));

    *out = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_dxgi_surface_inner_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_inner_QueryInterface *c = (struct qemu_dxgi_surface_inner_QueryInterface *)call;
    struct qemu_dxgi_surface *surface;
    IUnknown *out;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_QueryInterface(surface->host, QEMU_G2H(c->riid), (void **)&out);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host surface returned an interface for %s which this wrapper does not know.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(out);
    }
}

#endif

struct qemu_dxgi_surface_inner_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_surface_inner_AddRef(IUnknown *iface)
{
    struct qemu_dxgi_surface_inner_AddRef call;
    struct qemu_dxgi_surface *surface = impl_from_IUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_INNER_ADDREF);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_inner_AddRef(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_inner_AddRef *c = (struct qemu_dxgi_surface_inner_AddRef *)call;
    struct qemu_dxgi_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_AddRef(surface->host);
}

#endif

struct qemu_dxgi_surface_inner_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

void __fastcall dxgi_surface_guest_destroy(struct qemu_dxgi_surface *surface)
{
    wined3d_private_store_cleanup(&surface->private_store);
}

static ULONG STDMETHODCALLTYPE dxgi_surface_inner_Release(IUnknown *iface)
{
    struct qemu_dxgi_surface_inner_Release call;
    struct qemu_dxgi_surface *surface = impl_from_IUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_INNER_RELEASE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_inner_Release(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_inner_Release *c = (struct qemu_dxgi_surface_inner_Release *)call;
    struct qemu_dxgi_surface *surface;
    struct qemu_dxgi_device *device;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    device = surface->device;

    IDXGIDevice2_AddRef(device->host);
    c->super.iret = IDXGISurface1_Release(surface->host);
    qemu_dxgi_device_Release_internal(device);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_QueryInterface(IDXGISurface1 *iface, REFIID riid,
                                                             void **object)
{
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    WINE_TRACE("Forwarding to outer IUnknown\n");
    return IUnknown_QueryInterface(surface->outer_unknown, riid, object);
}

static ULONG STDMETHODCALLTYPE dxgi_surface_AddRef(IDXGISurface1 *iface)
{
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    WINE_TRACE("Forwarding to outer IUnknown\n");
    return IUnknown_AddRef(surface->outer_unknown);
}

static ULONG STDMETHODCALLTYPE dxgi_surface_Release(IDXGISurface1 *iface)
{
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    WINE_TRACE("Forwarding to outer IUnknown\n");
    return IUnknown_Release(surface->outer_unknown);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_SetPrivateData(IDXGISurface1 *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return dxgi_set_private_data(&surface->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE dxgi_surface_SetPrivateDataInterface(IDXGISurface1 *iface,
        REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    WINE_TRACE("iface %p, guid %s, object %p.\n", iface, wine_dbgstr_guid(guid), object);

    return dxgi_set_private_data_interface(&surface->private_store, guid, object);
}

static HRESULT STDMETHODCALLTYPE dxgi_surface_GetPrivateData(IDXGISurface1 *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return dxgi_get_private_data(&surface->private_store, guid, data_size, data);
}

#endif

struct qemu_dxgi_surface_GetParent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_GetParent(IDXGISurface1 *iface, REFIID riid, void **parent)
{
    struct qemu_dxgi_surface_GetParent call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    struct qemu_dxgi_device *device;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_GETPARENT);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);
    device = (struct qemu_dxgi_device *)(ULONG_PTR)call.parent;

    return IDXGIDevice_QueryInterface(&device->IDXGIDevice2_iface, riid, parent);
}

#else

void qemu_dxgi_surface_GetParent(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetParent *c = (struct qemu_dxgi_surface_GetParent *)call;
    struct qemu_dxgi_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    c->parent = QEMU_H2G(surface->device);
}

#endif

struct qemu_dxgi_surface_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_GetDevice(IDXGISurface1 *iface, REFIID riid, void **device)
{
    struct qemu_dxgi_surface_GetDevice call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_GETDEVICE);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_GetDevice(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetDevice *c = (struct qemu_dxgi_surface_GetDevice *)call;
    struct qemu_dxgi_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_GetDevice(surface->host, QEMU_G2H(c->riid), QEMU_G2H(c->device));
}

#endif

struct qemu_dxgi_surface_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_GetDesc(IDXGISurface1 *iface, DXGI_SURFACE_DESC *desc)
{
    struct qemu_dxgi_surface_GetDesc call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_GETDESC);
    call.iface = (ULONG_PTR)surface;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_GetDesc(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetDesc *c = (struct qemu_dxgi_surface_GetDesc *)call;
    struct qemu_dxgi_surface *surface;

    /* DXGI_SURFACE_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_GetDesc(surface->host, QEMU_G2H(c->desc));
}

#endif

struct qemu_dxgi_surface_Map
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mapped_rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_Map(IDXGISurface1 *iface, DXGI_MAPPED_RECT *mapped_rect, UINT flags)
{
    struct qemu_dxgi_surface_Map call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_MAP);
    call.iface = (ULONG_PTR)surface;
    call.mapped_rect = (ULONG_PTR)mapped_rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_Map(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_Map *c = (struct qemu_dxgi_surface_Map *)call;
    struct qemu_dxgi_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_Map(surface->host, QEMU_G2H(c->mapped_rect), c->flags);
}

#endif

struct qemu_dxgi_surface_Unmap
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_Unmap(IDXGISurface1 *iface)
{
    struct qemu_dxgi_surface_Unmap call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_UNMAP);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_Unmap(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_Unmap *c = (struct qemu_dxgi_surface_Unmap *)call;
    struct qemu_dxgi_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_Unmap(surface->host);
}

#endif

struct qemu_dxgi_surface_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t discard;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_GetDC(IDXGISurface1 *iface, BOOL discard, HDC *hdc)
{
    struct qemu_dxgi_surface_GetDC call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_GETDC);
    call.iface = (ULONG_PTR)surface;
    call.discard = discard;
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
        *hdc = (HDC)(ULONG_PTR)call.hdc;

    return call.super.iret;
}

#else

void qemu_dxgi_surface_GetDC(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetDC *c = (struct qemu_dxgi_surface_GetDC *)call;
    struct qemu_dxgi_surface *surface;
    HDC dc;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_GetDC(surface->host, c->discard, c->hdc ? &dc : NULL);
    c->hdc = QEMU_H2G(dc);
}

#endif

struct qemu_dxgi_surface_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dirty_rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_ReleaseDC(IDXGISurface1 *iface, RECT *dirty_rect)
{
    struct qemu_dxgi_surface_ReleaseDC call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dirty_rect = (ULONG_PTR)dirty_rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_ReleaseDC *c = (struct qemu_dxgi_surface_ReleaseDC *)call;
    struct qemu_dxgi_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_ReleaseDC(surface->host, QEMU_G2H(c->dirty_rect));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct
{
    IDXGISurfaceVtbl vtbl1;
    void *GetDC;
    void *ReleaseDC;
}
dxgi_surface_vtbl =
{
    {
        /* IUnknown methods */
        dxgi_surface_QueryInterface,
        dxgi_surface_AddRef,
        dxgi_surface_Release,
        /* IDXGIObject methods */
        dxgi_surface_SetPrivateData,
        dxgi_surface_SetPrivateDataInterface,
        dxgi_surface_GetPrivateData,
        dxgi_surface_GetParent,
        /* IDXGIDeviceSubObject methods */
        dxgi_surface_GetDevice,
        /* IDXGISurface methods */
        dxgi_surface_GetDesc,
        dxgi_surface_Map,
        dxgi_surface_Unmap,
    },
    /* IDXGISurface1 methods */
    dxgi_surface_GetDC,
    dxgi_surface_ReleaseDC,
};

static struct IUnknownVtbl dxgi_surface_inner_unknown_vtbl =
{
    /* IUnknown methods */
    dxgi_surface_inner_QueryInterface,
    dxgi_surface_inner_AddRef,
    dxgi_surface_inner_Release,
};

void qemu_dxgi_surface_guest_init(struct qemu_dxgi_surface *surface, IUnknown *outer_unknown)
{
    surface->IDXGISurface1_iface.lpVtbl = &dxgi_surface_vtbl.vtbl1;
    surface->IUnknown_iface.lpVtbl = &dxgi_surface_inner_unknown_vtbl;
    wined3d_private_store_init(&surface->private_store);

    if (outer_unknown)
        surface->outer_unknown = outer_unknown;
    else
        surface->outer_unknown = &surface->IUnknown_iface;
}

#else

static inline struct qemu_dxgi_surface *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_surface, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_surface_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE dxgi_surface_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_dxgi_surface *surface = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&surface->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", surface, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE dxgi_surface_priv_data_Release(IUnknown *iface)
{
    struct qemu_dxgi_surface *surface = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&surface->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", surface, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying surface wrapper %p for host surface %p.\n", surface, surface->host);
        qemu_ops->qemu_execute(QEMU_G2H(dxgi_surface_guest_destroy), QEMU_H2G(surface));
        HeapFree(GetProcessHeap(), 0, surface);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    dxgi_surface_priv_data_QueryInterface,
    dxgi_surface_priv_data_AddRef,
    dxgi_surface_priv_data_Release,
};

#include <initguid.h>

DEFINE_GUID(IID_Qemu_surface_priv_data, 0xfd2efa6f, 0xaf8d, 0x4b6b, 0xbd, 0x1d, 0x12, 0x06, 0x3e, 0x15, 0x23, 0x32);

struct qemu_dxgi_surface *surface_from_host(IDXGISurface1 *host)
{
    IUnknown *priv;
    DWORD size = sizeof(priv);
    HRESULT hr;

    hr = IDXGISurface1_GetPrivateData(host, &IID_Qemu_surface_priv_data, &size, &priv);
    if (FAILED(hr))
        WINE_ERR("Failed to get private data from host surface %p.\n", host);

    IUnknown_Release(priv);
    return impl_from_priv_data(priv);
}

HRESULT qemu_dxgi_surface_create(IDXGISurface1 *host, struct qemu_dxgi_device *device,
        struct qemu_dxgi_surface **surface)
{
    struct qemu_dxgi_surface *out;

    out = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*out));
    if (!out)
    {
        WINE_WARN("Out of memory.\n");
        return E_OUTOFMEMORY;
    }

    out->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    IDXGISurface1_SetPrivateDataInterface(host, &IID_Qemu_surface_priv_data, &out->priv_data_iface);

    out->host = host;
    out->device = device;
    *surface = out;
    return S_OK;
}

#endif
