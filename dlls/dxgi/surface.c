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

#ifdef QEMU_DLL_GUEST
#include <dxgi1_2.h>
#include <debug.h>
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

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_INNER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_inner_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_inner_QueryInterface *c = (struct qemu_dxgi_surface_inner_QueryInterface *)call;
    struct qemu_dxgi_surface *surface;
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_QueryInterface(surface->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
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
    
    WINE_FIXME("Unverified!\n");
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
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_Release(surface->host);
}

#endif

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dxgi_surface *impl_from_IDXGISurface1(IDXGISurface1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_surface, IDXGISurface1_iface);
}

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

struct qemu_dxgi_surface_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_SetPrivateData(IDXGISurface1 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_surface_SetPrivateData call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_SetPrivateData *c = (struct qemu_dxgi_surface_SetPrivateData *)call;
    struct qemu_dxgi_surface *surface;
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_SetPrivateData(surface->host, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_surface_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_SetPrivateDataInterface(IDXGISurface1 *iface, REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_surface_SetPrivateDataInterface call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.guid = (ULONG_PTR)guid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_SetPrivateDataInterface *c = (struct qemu_dxgi_surface_SetPrivateDataInterface *)call;
    struct qemu_dxgi_surface *surface;
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_SetPrivateDataInterface(surface->host, QEMU_G2H(c->guid), QEMU_G2H(c->object));
}

#endif

struct qemu_dxgi_surface_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_surface_GetPrivateData(IDXGISurface1 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_surface_GetPrivateData call;
    struct qemu_dxgi_surface *surface = impl_from_IDXGISurface1(iface);
    
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetPrivateData *c = (struct qemu_dxgi_surface_GetPrivateData *)call;
    struct qemu_dxgi_surface *surface;
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_GetPrivateData(surface->host, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
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
    
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SURFACE_GETPARENT);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;
    call.parent = (ULONG_PTR)parent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_surface_GetParent(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetParent *c = (struct qemu_dxgi_surface_GetParent *)call;
    struct qemu_dxgi_surface *surface;
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_GetParent(surface->host, QEMU_G2H(c->riid), QEMU_G2H(c->parent));
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
    
    WINE_FIXME("Unverified!\n");
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

    return call.super.iret;
}

#else

void qemu_dxgi_surface_GetDC(struct qemu_syscall *call)
{
    struct qemu_dxgi_surface_GetDC *c = (struct qemu_dxgi_surface_GetDC *)call;
    struct qemu_dxgi_surface *surface;
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);
    
    c->super.iret = IDXGISurface1_GetDC(surface->host, c->discard, QEMU_G2H(c->hdc));
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
    
    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDXGISurface1_ReleaseDC(surface->host, QEMU_G2H(c->dirty_rect));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct
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

static const struct IUnknownVtbl dxgi_surface_inner_unknown_vtbl =
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

    if (outer_unknown)
        surface->outer_unknown = outer_unknown;
    else
        surface->outer_unknown = &surface->IUnknown_iface;
}

#else

HRESULT qemu_dxgi_surface_create(IDXGISurface1 *host, struct qemu_dxgi_surface **surface)
{
    struct qemu_dxgi_surface *out;

    out = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*out));
    if (!out)
    {
        WINE_WARN("Out of memory.\n");
        return E_OUTOFMEMORY;
    }

    out->host = host;
    *surface = out;
    return S_OK;
}

#endif
