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

struct qemu_d3d11_input_layout_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_input_layout *impl_from_ID3D11InputLayout(ID3D11InputLayout *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_input_layout, ID3D11InputLayout_iface);
}

static inline struct qemu_d3d11_input_layout *impl_from_ID3D10InputLayout(ID3D10InputLayout *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_input_layout, ID3D10InputLayout_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_input_layout_QueryInterface(ID3D11InputLayout *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_input_layout_QueryInterface call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(riid, &IID_ID3D11InputLayout)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        ID3D11InputLayout_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_ID3D10InputLayout)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        ID3D10InputLayout_AddRef(&layout->ID3D10InputLayout_iface);
        *object = &layout->ID3D10InputLayout_iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_INPUT_LAYOUT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)layout;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_input_layout_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_input_layout_QueryInterface *c = (struct qemu_d3d11_input_layout_QueryInterface *)call;
    struct qemu_d3d11_input_layout *layout;
    IUnknown *obj;

    WINE_TRACE("\n");
    layout = QEMU_G2H(c->iface);

    c->super.iret = ID3D11InputLayout_QueryInterface(layout->host11, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_input_layout_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_input_layout_AddRef(ID3D11InputLayout *iface)
{
    struct qemu_d3d11_input_layout_AddRef call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_INPUT_LAYOUT_ADDREF);
    call.iface = (ULONG_PTR)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_input_layout_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_input_layout_AddRef *c = (struct qemu_d3d11_input_layout_AddRef *)call;
    struct qemu_d3d11_input_layout *layout;

    WINE_TRACE("\n");
    layout = QEMU_G2H(c->iface);

    c->super.iret = ID3D11InputLayout_AddRef(layout->host11);
}

#endif

struct qemu_d3d11_input_layout_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_input_layout_Release(ID3D11InputLayout *iface)
{
    struct qemu_d3d11_input_layout_Release call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_INPUT_LAYOUT_RELEASE);
    call.iface = (ULONG_PTR)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_input_layout_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_input_layout_Release *c = (struct qemu_d3d11_input_layout_Release *)call;
    struct qemu_d3d11_input_layout *layout;

    WINE_TRACE("\n");
    layout = QEMU_G2H(c->iface);

    c->super.iret = ID3D11InputLayout_Release(layout->host11);
}

#endif

struct qemu_d3d11_input_layout_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_input_layout_GetDevice(ID3D11InputLayout *iface, ID3D11Device **device)
{
    struct qemu_d3d11_input_layout_GetDevice call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_INPUT_LAYOUT_GETDEVICE);
    call.iface = (ULONG_PTR)layout;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_input_layout_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_input_layout_GetDevice *c = (struct qemu_d3d11_input_layout_GetDevice *)call;
    struct qemu_d3d11_input_layout *layout;

    WINE_FIXME("Unverified!\n");
    layout = QEMU_G2H(c->iface);

    ID3D11InputLayout_GetDevice(layout->host11, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_input_layout_GetPrivateData(ID3D11InputLayout *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&layout->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_input_layout_SetPrivateData(ID3D11InputLayout *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&layout->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_input_layout_SetPrivateDataInterface(ID3D11InputLayout *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D11InputLayout(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&layout->private_store, guid, data);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_input_layout_QueryInterface(ID3D10InputLayout *iface,
        REFIID riid, void **object)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return d3d11_input_layout_QueryInterface(&layout->ID3D11InputLayout_iface, riid, object);
}

#endif

struct qemu_d3d10_input_layout_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_input_layout_AddRef(ID3D10InputLayout *iface)
{
    struct qemu_d3d10_input_layout_AddRef call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_INPUT_LAYOUT_ADDREF);
    call.iface = (ULONG_PTR)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_input_layout_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_input_layout_AddRef *c = (struct qemu_d3d10_input_layout_AddRef *)call;
    struct qemu_d3d11_input_layout *layout;

    WINE_TRACE("\n");
    layout = QEMU_G2H(c->iface);

    c->super.iret = ID3D10InputLayout_AddRef(layout->host10);
}

#endif

struct qemu_d3d10_input_layout_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_input_layout_Release(ID3D10InputLayout *iface)
{
    struct qemu_d3d10_input_layout_Release call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_INPUT_LAYOUT_RELEASE);
    call.iface = (ULONG_PTR)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_input_layout_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_input_layout_Release *c = (struct qemu_d3d10_input_layout_Release *)call;
    struct qemu_d3d11_input_layout *layout;

    WINE_TRACE("\n");
    layout = QEMU_G2H(c->iface);

    c->super.iret = ID3D10InputLayout_Release(layout->host10);
}

#endif

struct qemu_d3d10_input_layout_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_input_layout_GetDevice(ID3D10InputLayout *iface, ID3D10Device **device)
{
    struct qemu_d3d10_input_layout_GetDevice call;
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_INPUT_LAYOUT_GETDEVICE);
    call.iface = (ULONG_PTR)layout;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_input_layout_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_input_layout_GetDevice *c = (struct qemu_d3d10_input_layout_GetDevice *)call;
    struct qemu_d3d11_input_layout *layout;

    WINE_FIXME("Unverified!\n");
    layout = QEMU_G2H(c->iface);

    ID3D10InputLayout_GetDevice(layout->host10, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_input_layout_GetPrivateData(ID3D10InputLayout *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&layout->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_input_layout_SetPrivateData(ID3D10InputLayout *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&layout->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_input_layout_SetPrivateDataInterface(ID3D10InputLayout *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_input_layout *layout = impl_from_ID3D10InputLayout(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&layout->private_store, guid, data);
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11InputLayoutVtbl d3d11_input_layout_vtbl =
{
    /* IUnknown methods */
    d3d11_input_layout_QueryInterface,
    d3d11_input_layout_AddRef,
    d3d11_input_layout_Release,
    /* ID3D11DeviceChild methods */
    d3d11_input_layout_GetDevice,
    d3d11_input_layout_GetPrivateData,
    d3d11_input_layout_SetPrivateData,
    d3d11_input_layout_SetPrivateDataInterface,
};

static struct ID3D10InputLayoutVtbl d3d10_input_layout_vtbl =
{
    /* IUnknown methods */
    d3d10_input_layout_QueryInterface,
    d3d10_input_layout_AddRef,
    d3d10_input_layout_Release,
    /* ID3D10DeviceChild methods */
    d3d10_input_layout_GetDevice,
    d3d10_input_layout_GetPrivateData,
    d3d10_input_layout_SetPrivateData,
    d3d10_input_layout_SetPrivateDataInterface,
};

void qemu_d3d11_input_layout_guest_init(struct qemu_d3d11_input_layout *layout)
{
    layout->ID3D11InputLayout_iface.lpVtbl = &d3d11_input_layout_vtbl;
    layout->ID3D10InputLayout_iface.lpVtbl = &d3d10_input_layout_vtbl;
    wined3d_private_store_init(&layout->private_store);
}

void __fastcall d3d11_input_layout_guest_destroy(struct qemu_d3d11_input_layout *layout)
{
    wined3d_private_store_cleanup(&layout->private_store);
}

struct qemu_d3d11_input_layout *unsafe_impl_from_ID3D11InputLayout(ID3D11InputLayout *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_input_layout_vtbl);*/

    return impl_from_ID3D11InputLayout(iface);
}

struct qemu_d3d11_input_layout *unsafe_impl_from_ID3D10InputLayout(ID3D10InputLayout *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_input_layout_vtbl);*/

    return impl_from_ID3D10InputLayout(iface);
}

#else

static inline struct qemu_d3d11_input_layout *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_input_layout, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_input_layout_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_input_layout_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_d3d11_input_layout *layout = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&layout->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", layout, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE d3d11_input_layout_priv_data_Release(IUnknown *iface)
{
    struct qemu_d3d11_input_layout *layout = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&layout->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", layout, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying layout wrapper %p for host layout %p.\n", layout, layout->host11);
        qemu_ops->qemu_execute(QEMU_G2H(d3d11_input_layout_guest_destroy), QEMU_H2G(layout));
        HeapFree(GetProcessHeap(), 0, layout);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_input_layout_priv_data_QueryInterface,
    d3d11_input_layout_priv_data_AddRef,
    d3d11_input_layout_priv_data_Release,
};

HRESULT qemu_d3d11_input_layout_create(ID3D11InputLayout *host, struct qemu_d3d11_input_layout **layout)
{
    struct qemu_d3d11_input_layout *obj;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    obj->host11 = (void *)host;
    hr = ID3D11InputLayout_QueryInterface(host, &IID_ID3D10InputLayout, (void **)&obj->host10);
    if (FAILED(hr))
        WINE_ERR("Failed to QI ID3D11InputLayout.\n");
    ID3D10InputLayout_Release(obj->host10);

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    ID3D11View_SetPrivateDataInterface(host, &IID_d3d11_priv_data, &obj->priv_data_iface);

    *layout = obj;
    return S_OK;
}

struct qemu_d3d11_input_layout *input_layout_from_host(ID3D11InputLayout *host)
{
    IUnknown *priv;
    DWORD size = sizeof(priv);
    HRESULT hr;

    if (!host)
        return NULL;

    hr = ID3D11InputLayout_GetPrivateData(host, &IID_d3d11_priv_data, &size, &priv);
    if (FAILED(hr))
    {
        WINE_TRACE("Failed to get private data from host state %p.\n", host);
        return NULL;
    }

    IUnknown_Release(priv);
    return impl_from_priv_data(priv);
}

#endif
