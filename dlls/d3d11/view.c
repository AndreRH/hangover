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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST

#include <d3d11.h>
#include <debug.h>

#include <initguid.h>

#else

#include <d3d11_2.h>
#include <wine/debug.h>

#endif

#include "thunk/qemu_d3d11.h"

#include "qemudxgi.h"
#include "qemu_d3d11.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

struct qemu_d3d11_depthstencil_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_view *impl_from_ID3D11DepthStencilView(ID3D11DepthStencilView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D11DepthStencilView_iface);
}

static inline struct qemu_d3d11_view *impl_from_ID3D10DepthStencilView(ID3D10DepthStencilView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D10DepthStencilView_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_view_QueryInterface(ID3D11DepthStencilView *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_depthstencil_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_QueryInterface *c = (struct qemu_d3d11_depthstencil_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilView_QueryInterface(view->host_ds11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_depthstencil_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_depthstencil_view_AddRef(ID3D11DepthStencilView *iface)
{
    struct qemu_d3d11_depthstencil_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_AddRef *c = (struct qemu_d3d11_depthstencil_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilView_AddRef(view->host_ds11);
}

#endif

struct qemu_d3d11_depthstencil_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_depthstencil_view_Release(ID3D11DepthStencilView *iface)
{
    struct qemu_d3d11_depthstencil_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_Release *c = (struct qemu_d3d11_depthstencil_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilView_Release(view->host_ds11);
}

#endif

struct qemu_d3d11_depthstencil_view_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_depthstencil_view_GetDevice(ID3D11DepthStencilView *iface, ID3D11Device **device)
{
    struct qemu_d3d11_depthstencil_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_depthstencil_view_GetDevice(ID3D10DepthStencilView *iface, ID3D10Device **device)
{
    struct qemu_d3d11_depthstencil_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_depthstencil_view_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_GetDevice *c = (struct qemu_d3d11_depthstencil_view_GetDevice *)call;
    struct qemu_d3d11_view *view;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    ID3D11DepthStencilView_GetDevice(view->host_ds11, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

struct qemu_d3d11_depthstencil_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_view_GetPrivateData(ID3D11DepthStencilView *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_depthstencil_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_GetPrivateData *c = (struct qemu_d3d11_depthstencil_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilView_GetPrivateData(view->host_ds11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_depthstencil_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_view_SetPrivateData(ID3D11DepthStencilView *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_depthstencil_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_SetPrivateData *c = (struct qemu_d3d11_depthstencil_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilView_SetPrivateData(view->host_ds11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_depthstencil_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_view_SetPrivateDataInterface(ID3D11DepthStencilView *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_depthstencil_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_SetPrivateDataInterface *c = (struct qemu_d3d11_depthstencil_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilView_SetPrivateDataInterface(view->host_ds11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_depthstencil_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_depthstencil_view_GetResource(ID3D11DepthStencilView *iface, ID3D11Resource **resource)
{
    struct qemu_d3d11_depthstencil_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_depthstencil_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_GetResource *c = (struct qemu_d3d11_depthstencil_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11DepthStencilView_GetResource(view->host_ds11, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_depthstencil_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_depthstencil_view_GetDesc(ID3D11DepthStencilView *iface, D3D11_DEPTH_STENCIL_VIEW_DESC *desc)
{
    struct qemu_d3d11_depthstencil_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D11DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_depthstencil_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_view_GetDesc *c = (struct qemu_d3d11_depthstencil_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11DepthStencilView_GetDesc(view->host_ds11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_depthstencil_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_view_QueryInterface(ID3D10DepthStencilView *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_depthstencil_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_QueryInterface *c = (struct qemu_d3d10_depthstencil_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilView_QueryInterface(view->host_ds10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_depthstencil_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_depthstencil_view_AddRef(ID3D10DepthStencilView *iface)
{
    struct qemu_d3d10_depthstencil_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_AddRef *c = (struct qemu_d3d10_depthstencil_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilView_AddRef(view->host_ds10);
}

#endif

struct qemu_d3d10_depthstencil_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_depthstencil_view_Release(ID3D10DepthStencilView *iface)
{
    struct qemu_d3d10_depthstencil_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_Release *c = (struct qemu_d3d10_depthstencil_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilView_Release(view->host_ds10);
}

#endif

struct qemu_d3d10_depthstencil_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_view_GetPrivateData(ID3D10DepthStencilView *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_depthstencil_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_GetPrivateData *c = (struct qemu_d3d10_depthstencil_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilView_GetPrivateData(view->host_ds10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_depthstencil_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_view_SetPrivateData(ID3D10DepthStencilView *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_depthstencil_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_SetPrivateData *c = (struct qemu_d3d10_depthstencil_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilView_SetPrivateData(view->host_ds10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_depthstencil_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_view_SetPrivateDataInterface(ID3D10DepthStencilView *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_depthstencil_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_SetPrivateDataInterface *c = (struct qemu_d3d10_depthstencil_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilView_SetPrivateDataInterface(view->host_ds10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_depthstencil_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_depthstencil_view_GetResource(ID3D10DepthStencilView *iface, ID3D10Resource **resource)
{
    struct qemu_d3d10_depthstencil_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_depthstencil_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_GetResource *c = (struct qemu_d3d10_depthstencil_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10DepthStencilView_GetResource(view->host_ds10, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d10_depthstencil_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_depthstencil_view_GetDesc(ID3D10DepthStencilView *iface, D3D10_DEPTH_STENCIL_VIEW_DESC *desc)
{
    struct qemu_d3d10_depthstencil_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D10DepthStencilView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_depthstencil_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_view_GetDesc *c = (struct qemu_d3d10_depthstencil_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10DepthStencilView_GetDesc(view->host_ds10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_rendertarget_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_view *impl_from_ID3D11RenderTargetView(ID3D11RenderTargetView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D11RenderTargetView_iface);
}

static inline struct qemu_d3d11_view *impl_from_ID3D10RenderTargetView(ID3D10RenderTargetView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D10RenderTargetView_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_rendertarget_view_QueryInterface(ID3D11RenderTargetView *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_rendertarget_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rendertarget_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_QueryInterface *c = (struct qemu_d3d11_rendertarget_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RenderTargetView_QueryInterface(view->host_rt11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_rendertarget_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_rendertarget_view_AddRef(ID3D11RenderTargetView *iface)
{
    struct qemu_d3d11_rendertarget_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rendertarget_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_AddRef *c = (struct qemu_d3d11_rendertarget_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RenderTargetView_AddRef(view->host_rt11);
}

#endif

struct qemu_d3d11_rendertarget_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_rendertarget_view_Release(ID3D11RenderTargetView *iface)
{
    struct qemu_d3d11_rendertarget_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rendertarget_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_Release *c = (struct qemu_d3d11_rendertarget_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RenderTargetView_Release(view->host_rt11);
}

#endif

struct qemu_d3d11_rendertarget_view_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_rendertarget_view_GetDevice(ID3D11RenderTargetView *iface, ID3D11Device **device)
{
    struct qemu_d3d11_rendertarget_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_rendertarget_view_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_GetDevice *c = (struct qemu_d3d11_rendertarget_view_GetDevice *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11RenderTargetView_GetDevice(view->host_rt11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_rendertarget_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_rendertarget_view_GetPrivateData(ID3D11RenderTargetView *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_rendertarget_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rendertarget_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_GetPrivateData *c = (struct qemu_d3d11_rendertarget_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RenderTargetView_GetPrivateData(view->host_rt11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_rendertarget_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_rendertarget_view_SetPrivateData(ID3D11RenderTargetView *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_rendertarget_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rendertarget_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_SetPrivateData *c = (struct qemu_d3d11_rendertarget_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RenderTargetView_SetPrivateData(view->host_rt11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_rendertarget_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_rendertarget_view_SetPrivateDataInterface(ID3D11RenderTargetView *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_rendertarget_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rendertarget_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_SetPrivateDataInterface *c = (struct qemu_d3d11_rendertarget_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RenderTargetView_SetPrivateDataInterface(view->host_rt11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_rendertarget_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_rendertarget_view_GetResource(ID3D11RenderTargetView *iface, ID3D11Resource **resource)
{
    struct qemu_d3d11_rendertarget_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_rendertarget_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_GetResource *c = (struct qemu_d3d11_rendertarget_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11RenderTargetView_GetResource(view->host_rt11, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_rendertarget_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_rendertarget_view_GetDesc(ID3D11RenderTargetView *iface, D3D11_RENDER_TARGET_VIEW_DESC *desc)
{
    struct qemu_d3d11_rendertarget_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D11RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RENDERTARGET_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_rendertarget_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_rendertarget_view_GetDesc *c = (struct qemu_d3d11_rendertarget_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11RenderTargetView_GetDesc(view->host_rt11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_rendertarget_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rendertarget_view_QueryInterface(ID3D10RenderTargetView *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_rendertarget_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rendertarget_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_QueryInterface *c = (struct qemu_d3d10_rendertarget_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RenderTargetView_QueryInterface(view->host_rt10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_rendertarget_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_rendertarget_view_AddRef(ID3D10RenderTargetView *iface)
{
    struct qemu_d3d10_rendertarget_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rendertarget_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_AddRef *c = (struct qemu_d3d10_rendertarget_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RenderTargetView_AddRef(view->host_rt10);
}

#endif

struct qemu_d3d10_rendertarget_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_rendertarget_view_Release(ID3D10RenderTargetView *iface)
{
    struct qemu_d3d10_rendertarget_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rendertarget_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_Release *c = (struct qemu_d3d10_rendertarget_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RenderTargetView_Release(view->host_rt10);
}

#endif

struct qemu_d3d10_rendertarget_view_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_rendertarget_view_GetDevice(ID3D10RenderTargetView *iface, ID3D10Device **device)
{
    struct qemu_d3d10_rendertarget_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_rendertarget_view_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_GetDevice *c = (struct qemu_d3d10_rendertarget_view_GetDevice *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10RenderTargetView_GetDevice(view->host_rt10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_rendertarget_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rendertarget_view_GetPrivateData(ID3D10RenderTargetView *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_rendertarget_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rendertarget_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_GetPrivateData *c = (struct qemu_d3d10_rendertarget_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RenderTargetView_GetPrivateData(view->host_rt10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_rendertarget_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rendertarget_view_SetPrivateData(ID3D10RenderTargetView *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_rendertarget_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rendertarget_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_SetPrivateData *c = (struct qemu_d3d10_rendertarget_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RenderTargetView_SetPrivateData(view->host_rt10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_rendertarget_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rendertarget_view_SetPrivateDataInterface(ID3D10RenderTargetView *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_rendertarget_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rendertarget_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_SetPrivateDataInterface *c = (struct qemu_d3d10_rendertarget_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RenderTargetView_SetPrivateDataInterface(view->host_rt10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_rendertarget_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_rendertarget_view_GetResource(ID3D10RenderTargetView *iface, ID3D10Resource **resource)
{
    struct qemu_d3d10_rendertarget_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_rendertarget_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_GetResource *c = (struct qemu_d3d10_rendertarget_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10RenderTargetView_GetResource(view->host_rt10, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d10_rendertarget_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_rendertarget_view_GetDesc(ID3D10RenderTargetView *iface, D3D10_RENDER_TARGET_VIEW_DESC *desc)
{
    struct qemu_d3d10_rendertarget_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D10RenderTargetView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RENDERTARGET_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_rendertarget_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_rendertarget_view_GetDesc *c = (struct qemu_d3d10_rendertarget_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10RenderTargetView_GetDesc(view->host_rt10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_shader_resource_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_view *impl_from_ID3D11ShaderResourceView(ID3D11ShaderResourceView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D11ShaderResourceView_iface);
}

static inline struct qemu_d3d11_view *impl_from_ID3D10ShaderResourceView1(ID3D10ShaderResourceView1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D10ShaderResourceView1_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_shader_resource_view_QueryInterface(ID3D11ShaderResourceView *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_shader_resource_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_shader_resource_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_QueryInterface *c = (struct qemu_d3d11_shader_resource_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ShaderResourceView_QueryInterface(view->host_sr11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_shader_resource_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_shader_resource_view_AddRef(ID3D11ShaderResourceView *iface)
{
    struct qemu_d3d11_shader_resource_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_shader_resource_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_AddRef *c = (struct qemu_d3d11_shader_resource_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ShaderResourceView_AddRef(view->host_sr11);
}

#endif

struct qemu_d3d11_shader_resource_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_shader_resource_view_Release(ID3D11ShaderResourceView *iface)
{
    struct qemu_d3d11_shader_resource_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_shader_resource_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_Release *c = (struct qemu_d3d11_shader_resource_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ShaderResourceView_Release(view->host_sr11);
}

#endif

struct qemu_d3d11_shader_resource_view_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_shader_resource_view_GetDevice(ID3D11ShaderResourceView *iface, ID3D11Device **device)
{
    struct qemu_d3d11_shader_resource_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_shader_resource_view_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_GetDevice *c = (struct qemu_d3d11_shader_resource_view_GetDevice *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11ShaderResourceView_GetDevice(view->host_sr11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_shader_resource_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_shader_resource_view_GetPrivateData(ID3D11ShaderResourceView *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader_resource_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_shader_resource_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_GetPrivateData *c = (struct qemu_d3d11_shader_resource_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ShaderResourceView_GetPrivateData(view->host_sr11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_shader_resource_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_shader_resource_view_SetPrivateData(ID3D11ShaderResourceView *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader_resource_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_shader_resource_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_SetPrivateData *c = (struct qemu_d3d11_shader_resource_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ShaderResourceView_SetPrivateData(view->host_sr11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_shader_resource_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_shader_resource_view_SetPrivateDataInterface(ID3D11ShaderResourceView *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader_resource_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_shader_resource_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_SetPrivateDataInterface *c = (struct qemu_d3d11_shader_resource_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ShaderResourceView_SetPrivateDataInterface(view->host_sr11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_shader_resource_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_shader_resource_view_GetResource(ID3D11ShaderResourceView *iface, ID3D11Resource **resource)
{
    struct qemu_d3d11_shader_resource_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_shader_resource_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_GetResource *c = (struct qemu_d3d11_shader_resource_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11ShaderResourceView_GetResource(view->host_sr11, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_shader_resource_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_shader_resource_view_GetDesc(ID3D11ShaderResourceView *iface, D3D11_SHADER_RESOURCE_VIEW_DESC *desc)
{
    struct qemu_d3d11_shader_resource_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D11ShaderResourceView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SHADER_RESOURCE_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_shader_resource_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_shader_resource_view_GetDesc *c = (struct qemu_d3d11_shader_resource_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11ShaderResourceView_GetDesc(view->host_sr11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_shader_resource_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_shader_resource_view_QueryInterface(ID3D10ShaderResourceView1 *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_shader_resource_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_shader_resource_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_QueryInterface *c = (struct qemu_d3d10_shader_resource_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10ShaderResourceView1_QueryInterface(view->host_sr10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_shader_resource_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_shader_resource_view_AddRef(ID3D10ShaderResourceView1 *iface)
{
    struct qemu_d3d10_shader_resource_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_shader_resource_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_AddRef *c = (struct qemu_d3d10_shader_resource_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10ShaderResourceView1_AddRef(view->host_sr10);
}

#endif

struct qemu_d3d10_shader_resource_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_shader_resource_view_Release(ID3D10ShaderResourceView1 *iface)
{
    struct qemu_d3d10_shader_resource_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_shader_resource_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_Release *c = (struct qemu_d3d10_shader_resource_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10ShaderResourceView1_Release(view->host_sr10);
}

#endif

struct qemu_d3d10_shader_resource_view_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_shader_resource_view_GetDevice(ID3D10ShaderResourceView1 *iface, ID3D10Device **device)
{
    struct qemu_d3d10_shader_resource_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_shader_resource_view_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_GetDevice *c = (struct qemu_d3d10_shader_resource_view_GetDevice *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10ShaderResourceView1_GetDevice(view->host_sr10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_shader_resource_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_shader_resource_view_GetPrivateData(ID3D10ShaderResourceView1 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_shader_resource_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_shader_resource_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_GetPrivateData *c = (struct qemu_d3d10_shader_resource_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10ShaderResourceView1_GetPrivateData(view->host_sr10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_shader_resource_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_shader_resource_view_SetPrivateData(ID3D10ShaderResourceView1 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_shader_resource_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_shader_resource_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_SetPrivateData *c = (struct qemu_d3d10_shader_resource_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10ShaderResourceView1_SetPrivateData(view->host_sr10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_shader_resource_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_shader_resource_view_SetPrivateDataInterface(ID3D10ShaderResourceView1 *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_shader_resource_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_shader_resource_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_SetPrivateDataInterface *c = (struct qemu_d3d10_shader_resource_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D10ShaderResourceView1_SetPrivateDataInterface(view->host_sr10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_shader_resource_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_shader_resource_view_GetResource(ID3D10ShaderResourceView1 *iface, ID3D10Resource **resource)
{
    struct qemu_d3d10_shader_resource_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_shader_resource_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_GetResource *c = (struct qemu_d3d10_shader_resource_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10ShaderResourceView1_GetResource(view->host_sr10, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d10_shader_resource_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_shader_resource_view_GetDesc(ID3D10ShaderResourceView1 *iface, D3D10_SHADER_RESOURCE_VIEW_DESC *desc)
{
    struct qemu_d3d10_shader_resource_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_shader_resource_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_GetDesc *c = (struct qemu_d3d10_shader_resource_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10ShaderResourceView1_GetDesc(view->host_sr10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_shader_resource_view_GetDesc1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_shader_resource_view_GetDesc1(ID3D10ShaderResourceView1 *iface, D3D10_SHADER_RESOURCE_VIEW_DESC1 *desc)
{
    struct qemu_d3d10_shader_resource_view_GetDesc1 call;
    struct qemu_d3d11_view *view = impl_from_ID3D10ShaderResourceView1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SHADER_RESOURCE_VIEW_GETDESC1);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_shader_resource_view_GetDesc1(struct qemu_syscall *call)
{
    struct qemu_d3d10_shader_resource_view_GetDesc1 *c = (struct qemu_d3d10_shader_resource_view_GetDesc1 *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D10ShaderResourceView1_GetDesc1(view->host_sr10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_unordered_access_view_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_view *impl_from_ID3D11UnorderedAccessView(ID3D11UnorderedAccessView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D11UnorderedAccessView_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_unordered_access_view_QueryInterface(ID3D11UnorderedAccessView *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_unordered_access_view_QueryInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_unordered_access_view_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_QueryInterface *c = (struct qemu_d3d11_unordered_access_view_QueryInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11UnorderedAccessView_QueryInterface(view->host_uav, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_unordered_access_view_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_unordered_access_view_AddRef(ID3D11UnorderedAccessView *iface)
{
    struct qemu_d3d11_unordered_access_view_AddRef call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_unordered_access_view_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_AddRef *c = (struct qemu_d3d11_unordered_access_view_AddRef *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11UnorderedAccessView_AddRef(view->host_uav);
}

#endif

struct qemu_d3d11_unordered_access_view_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_unordered_access_view_Release(ID3D11UnorderedAccessView *iface)
{
    struct qemu_d3d11_unordered_access_view_Release call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_unordered_access_view_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_Release *c = (struct qemu_d3d11_unordered_access_view_Release *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11UnorderedAccessView_Release(view->host_uav);
}

#endif

struct qemu_d3d11_unordered_access_view_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_unordered_access_view_GetDevice(ID3D11UnorderedAccessView *iface, ID3D11Device **device)
{
    struct qemu_d3d11_unordered_access_view_GetDevice call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_GETDEVICE);
    call.iface = (ULONG_PTR)view;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_unordered_access_view_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_GetDevice *c = (struct qemu_d3d11_unordered_access_view_GetDevice *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11UnorderedAccessView_GetDevice(view->host_uav, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_unordered_access_view_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_unordered_access_view_GetPrivateData(ID3D11UnorderedAccessView *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_unordered_access_view_GetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_unordered_access_view_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_GetPrivateData *c = (struct qemu_d3d11_unordered_access_view_GetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11UnorderedAccessView_GetPrivateData(view->host_uav, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_unordered_access_view_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_unordered_access_view_SetPrivateData(ID3D11UnorderedAccessView *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_unordered_access_view_SetPrivateData call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_unordered_access_view_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_SetPrivateData *c = (struct qemu_d3d11_unordered_access_view_SetPrivateData *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11UnorderedAccessView_SetPrivateData(view->host_uav, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_unordered_access_view_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_unordered_access_view_SetPrivateDataInterface(ID3D11UnorderedAccessView *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_unordered_access_view_SetPrivateDataInterface call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_unordered_access_view_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_SetPrivateDataInterface *c = (struct qemu_d3d11_unordered_access_view_SetPrivateDataInterface *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = ID3D11UnorderedAccessView_SetPrivateDataInterface(view->host_uav, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_unordered_access_view_GetResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_unordered_access_view_GetResource(ID3D11UnorderedAccessView *iface, ID3D11Resource **resource)
{
    struct qemu_d3d11_unordered_access_view_GetResource call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_GETRESOURCE);
    call.iface = (ULONG_PTR)view;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_unordered_access_view_GetResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_GetResource *c = (struct qemu_d3d11_unordered_access_view_GetResource *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11UnorderedAccessView_GetResource(view->host_uav, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_unordered_access_view_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_unordered_access_view_GetDesc(ID3D11UnorderedAccessView *iface, D3D11_UNORDERED_ACCESS_VIEW_DESC *desc)
{
    struct qemu_d3d11_unordered_access_view_GetDesc call;
    struct qemu_d3d11_view *view = impl_from_ID3D11UnorderedAccessView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_UNORDERED_ACCESS_VIEW_GETDESC);
    call.iface = (ULONG_PTR)view;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_unordered_access_view_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_unordered_access_view_GetDesc *c = (struct qemu_d3d11_unordered_access_view_GetDesc *)call;
    struct qemu_d3d11_view *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    ID3D11UnorderedAccessView_GetDesc(view->host_uav, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11DepthStencilViewVtbl d3d11_depthstencil_view_vtbl =
{
    /* IUnknown methods */
    d3d11_depthstencil_view_QueryInterface,
    d3d11_depthstencil_view_AddRef,
    d3d11_depthstencil_view_Release,
    /* ID3D11DeviceChild methods */
    d3d11_depthstencil_view_GetDevice,
    d3d11_depthstencil_view_GetPrivateData,
    d3d11_depthstencil_view_SetPrivateData,
    d3d11_depthstencil_view_SetPrivateDataInterface,
    /* ID3D11View methods */
    d3d11_depthstencil_view_GetResource,
    /* ID3D11DepthStencilView methods */
    d3d11_depthstencil_view_GetDesc,
};

static struct ID3D10DepthStencilViewVtbl d3d10_depthstencil_view_vtbl =
{
    /* IUnknown methods */
    d3d10_depthstencil_view_QueryInterface,
    d3d10_depthstencil_view_AddRef,
    d3d10_depthstencil_view_Release,
    /* ID3D10DeviceChild methods */
    d3d10_depthstencil_view_GetDevice,
    d3d10_depthstencil_view_GetPrivateData,
    d3d10_depthstencil_view_SetPrivateData,
    d3d10_depthstencil_view_SetPrivateDataInterface,
    /* ID3D10View methods */
    d3d10_depthstencil_view_GetResource,
    /* ID3D10DepthStencilView methods */
    d3d10_depthstencil_view_GetDesc,
};

static struct ID3D11RenderTargetViewVtbl d3d11_rendertarget_view_vtbl =
{
    /* IUnknown methods */
    d3d11_rendertarget_view_QueryInterface,
    d3d11_rendertarget_view_AddRef,
    d3d11_rendertarget_view_Release,
    /* ID3D11DeviceChild methods */
    d3d11_rendertarget_view_GetDevice,
    d3d11_rendertarget_view_GetPrivateData,
    d3d11_rendertarget_view_SetPrivateData,
    d3d11_rendertarget_view_SetPrivateDataInterface,
    /* ID3D11View methods */
    d3d11_rendertarget_view_GetResource,
    /* ID3D11RenderTargetView methods */
    d3d11_rendertarget_view_GetDesc,
};

static struct ID3D10RenderTargetViewVtbl d3d10_rendertarget_view_vtbl =
{
    /* IUnknown methods */
    d3d10_rendertarget_view_QueryInterface,
    d3d10_rendertarget_view_AddRef,
    d3d10_rendertarget_view_Release,
    /* ID3D10DeviceChild methods */
    d3d10_rendertarget_view_GetDevice,
    d3d10_rendertarget_view_GetPrivateData,
    d3d10_rendertarget_view_SetPrivateData,
    d3d10_rendertarget_view_SetPrivateDataInterface,
    /* ID3D10View methods */
    d3d10_rendertarget_view_GetResource,
    /* ID3D10RenderTargetView methods */
    d3d10_rendertarget_view_GetDesc,
};

static struct ID3D10ShaderResourceView1Vtbl d3d10_shader_resource_view_vtbl =
{
    /* IUnknown methods */
    d3d10_shader_resource_view_QueryInterface,
    d3d10_shader_resource_view_AddRef,
    d3d10_shader_resource_view_Release,
    /* ID3D10DeviceChild methods */
    d3d10_shader_resource_view_GetDevice,
    d3d10_shader_resource_view_GetPrivateData,
    d3d10_shader_resource_view_SetPrivateData,
    d3d10_shader_resource_view_SetPrivateDataInterface,
    /* ID3D10View methods */
    d3d10_shader_resource_view_GetResource,
    /* ID3D10ShaderResourceView methods */
    d3d10_shader_resource_view_GetDesc,
    /* ID3D10ShaderResourceView1 methods */
    d3d10_shader_resource_view_GetDesc1,
};

static struct ID3D11ShaderResourceViewVtbl d3d11_shader_resource_view_vtbl =
{
    /* IUnknown methods */
    d3d11_shader_resource_view_QueryInterface,
    d3d11_shader_resource_view_AddRef,
    d3d11_shader_resource_view_Release,
    /* ID3D11DeviceChild methods */
    d3d11_shader_resource_view_GetDevice,
    d3d11_shader_resource_view_GetPrivateData,
    d3d11_shader_resource_view_SetPrivateData,
    d3d11_shader_resource_view_SetPrivateDataInterface,
    /* ID3D11View methods */
    d3d11_shader_resource_view_GetResource,
    /* ID3D11ShaderResourceView methods */
    d3d11_shader_resource_view_GetDesc,
};

static struct ID3D11UnorderedAccessViewVtbl d3d11_unordered_access_view_vtbl =
{
    /* IUnknown methods */
    d3d11_unordered_access_view_QueryInterface,
    d3d11_unordered_access_view_AddRef,
    d3d11_unordered_access_view_Release,
    /* ID3D11DeviceChild methods */
    d3d11_unordered_access_view_GetDevice,
    d3d11_unordered_access_view_GetPrivateData,
    d3d11_unordered_access_view_SetPrivateData,
    d3d11_unordered_access_view_SetPrivateDataInterface,
    /* ID3D11View methods */
    d3d11_unordered_access_view_GetResource,
    /* ID3D11UnorderedAccessView methods */
    d3d11_unordered_access_view_GetDesc,
};

struct qemu_d3d11_view *unsafe_impl_from_ID3D11DepthStencilView(ID3D11DepthStencilView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_depthstencil_view_vtbl);*/

    return impl_from_ID3D11DepthStencilView(iface);
}

struct qemu_d3d11_view *unsafe_impl_from_ID3D10DepthStencilView(ID3D10DepthStencilView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_depthstencil_view_vtbl);*/

    return impl_from_ID3D10DepthStencilView(iface);
}

struct qemu_d3d11_view *unsafe_impl_from_ID3D11RenderTargetView(ID3D11RenderTargetView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_rendertarget_view_vtbl);*/

    return impl_from_ID3D11RenderTargetView(iface);
}

struct qemu_d3d11_view *unsafe_impl_from_ID3D10RenderTargetView(ID3D10RenderTargetView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_rendertarget_view_vtbl);*/

    return impl_from_ID3D10RenderTargetView(iface);
}

struct qemu_d3d11_view *unsafe_impl_from_ID3D11ShaderResourceView(ID3D11ShaderResourceView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_shader_resource_view_vtbl);*/
    return impl_from_ID3D11ShaderResourceView(iface);
}

struct qemu_d3d11_view *unsafe_impl_from_ID3D10ShaderResourceView(ID3D10ShaderResourceView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == (ID3D10ShaderResourceViewVtbl *)&d3d10_shader_resource_view_vtbl);*/
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, ID3D10ShaderResourceView1_iface);
}

struct qemu_d3d11_view *unsafe_impl_from_ID3D11UnorderedAccessView(ID3D11UnorderedAccessView *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_unordered_access_view_vtbl);*/

    return impl_from_ID3D11UnorderedAccessView(iface);
}

void qemu_d3d11_depth_stencil_view_guest_init(struct qemu_d3d11_view *view)
{
    view->ID3D11DepthStencilView_iface.lpVtbl = &d3d11_depthstencil_view_vtbl;
    view->ID3D10DepthStencilView_iface.lpVtbl = &d3d10_depthstencil_view_vtbl;
}

void qemu_d3d11_shader_resource_view_guest_init(struct qemu_d3d11_view *view)
{
    view->ID3D11ShaderResourceView_iface.lpVtbl = &d3d11_shader_resource_view_vtbl;
    view->ID3D10ShaderResourceView1_iface.lpVtbl = &d3d10_shader_resource_view_vtbl;
}

#else

static inline struct qemu_d3d11_view *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_view, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_view_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_view_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_d3d11_view *view = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&view->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", view, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE d3d11_view_priv_data_Release(IUnknown *iface)
{
    struct qemu_d3d11_view *view = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&view->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", view, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying view wrapper %p for host view %p.\n", view, view->host_ds11);
        HeapFree(GetProcessHeap(), 0, view);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_view_priv_data_QueryInterface,
    d3d11_view_priv_data_AddRef,
    d3d11_view_priv_data_Release,
};

HRESULT qemu_d3d11_view_create(ID3D11View *host, const IID *d3d10iface, struct qemu_d3d11_view **view)
{
    struct qemu_d3d11_view *obj;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    obj->host_ds11 = (void *)host;
    if (d3d10iface)
    {
        hr = ID3D11View_QueryInterface(host, d3d10iface, (void **)&obj->host_ds10);
        if (FAILED(hr))
            WINE_ERR("Failed to QI %s.\n", wine_dbgstr_guid(d3d10iface));
        ID3D10View_Release(obj->host_ds10);
    }

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    ID3D11View_SetPrivateDataInterface(host, &IID_d3d11_priv_data, &obj->priv_data_iface);

    *view = obj;
    return S_OK;
}

#endif
