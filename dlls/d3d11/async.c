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

struct qemu_d3d11_query_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_query *impl_from_ID3D11Query(ID3D11Query *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_query, ID3D11Query_iface);
}

static inline struct qemu_d3d11_query *impl_from_ID3D10Query(ID3D10Query *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_query, ID3D10Query_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_query_QueryInterface(ID3D11Query *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_query_QueryInterface call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_QUERYINTERFACE);
    call.iface = (ULONG_PTR)query;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        *object = NULL;
        return call.super.iret;
    }

    if (IsEqualGUID(riid, &IID_ID3D11Predicate)
            || IsEqualGUID(riid, &IID_ID3D11Query)
            || IsEqualGUID(riid, &IID_ID3D11Asynchronous)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        *object = iface;
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_ID3D10Predicate)
            || IsEqualGUID(riid, &IID_ID3D10Query)
            || IsEqualGUID(riid, &IID_ID3D10Asynchronous)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        *object = &query->ID3D10Query_iface;
        return S_OK;
    }

    WINE_FIXME("Host device returned IID %s which this wrapper does not know about.\n", wine_dbgstr_guid(riid));

    /* Well, technically we don't know if we share refcounts with this unknown interface, but we're likely to
     * crash anyway. */
    ID3D11Query_Release(iface);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_query_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_QueryInterface *c = (struct qemu_d3d11_query_QueryInterface *)call;
    struct qemu_d3d11_query *query;
    IUnknown *out;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_QueryInterface(query->host11, QEMU_G2H(c->riid), (void **)&out);
}

#endif

struct qemu_d3d11_query_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_query_AddRef(ID3D11Query *iface)
{
    struct qemu_d3d11_query_AddRef call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_ADDREF);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_AddRef *c = (struct qemu_d3d11_query_AddRef *)call;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_AddRef(query->host11);
}

#endif

struct qemu_d3d11_query_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_query_Release(ID3D11Query *iface)
{
    struct qemu_d3d11_query_Release call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_RELEASE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_Release *c = (struct qemu_d3d11_query_Release *)call;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_Release(query->host11);
}

#endif

struct qemu_d3d11_query_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_query_GetDevice(ID3D11Query *iface, ID3D11Device **device)
{
    struct qemu_d3d11_query_GetDevice call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDEVICE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_query_GetDevice(ID3D10Query *iface, ID3D10Device **device)
{
    struct qemu_d3d11_query_GetDevice call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDEVICE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_query_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetDevice *c = (struct qemu_d3d11_query_GetDevice *)call;
    struct qemu_d3d11_query *query;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    ID3D11Query_GetDevice(query->host11, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_query_GetPrivateData(ID3D11Query *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&query->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_query_SetPrivateData(ID3D11Query *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&query->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_query_SetPrivateDataInterface(ID3D11Query *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&query->private_store, guid, data);
}

#endif

struct qemu_d3d11_query_GetDataSize
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_query_GetDataSize(ID3D11Query *iface)
{
    struct qemu_d3d11_query_GetDataSize call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDATASIZE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_query_GetDataSize(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetDataSize *c = (struct qemu_d3d11_query_GetDataSize *)call;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Query_GetDataSize(query->host11);
}

#endif

struct qemu_d3d11_query_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_query_GetDesc(ID3D11Query *iface, D3D11_QUERY_DESC *desc)
{
    struct qemu_d3d11_query_GetDesc call;
    struct qemu_d3d11_query *query = impl_from_ID3D11Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_QUERY_GETDESC);
    call.iface = (ULONG_PTR)query;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_query_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_query_GetDesc *c = (struct qemu_d3d11_query_GetDesc *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D11Query_GetDesc(query->host11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_query_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_QueryInterface(ID3D10Query *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_query_QueryInterface call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_QUERYINTERFACE);
    call.iface = (ULONG_PTR)query;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_QueryInterface *c = (struct qemu_d3d10_query_QueryInterface *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_QueryInterface(query->host10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_query_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_query_AddRef(ID3D10Query *iface)
{
    struct qemu_d3d10_query_AddRef call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_ADDREF);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_AddRef *c = (struct qemu_d3d10_query_AddRef *)call;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_AddRef(query->host10);
}

#endif

struct qemu_d3d10_query_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_query_Release(ID3D10Query *iface)
{
    struct qemu_d3d10_query_Release call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_RELEASE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_Release *c = (struct qemu_d3d10_query_Release *)call;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_Release(query->host10);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_GetPrivateData(ID3D10Query *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&query->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_query_SetPrivateData(ID3D10Query *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&query->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_query_SetPrivateDataInterface(ID3D10Query *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&query->private_store, guid, data);
}

#endif

struct qemu_d3d10_query_Begin
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_Begin(ID3D10Query *iface)
{
    struct qemu_d3d10_query_Begin call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_BEGIN);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_Begin(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_Begin *c = (struct qemu_d3d10_query_Begin *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_Begin(query->host10);
}

#endif

struct qemu_d3d10_query_End
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_End(ID3D10Query *iface)
{
    struct qemu_d3d10_query_End call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_END);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_End(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_End *c = (struct qemu_d3d10_query_End *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_End(query->host10);
}

#endif

struct qemu_d3d10_query_GetData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_query_GetData(ID3D10Query *iface, void *data, UINT data_size, UINT flags)
{
    struct qemu_d3d10_query_GetData call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDATA);
    call.iface = (ULONG_PTR)query;
    call.data = (ULONG_PTR)data;
    call.data_size = data_size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_GetData(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetData *c = (struct qemu_d3d10_query_GetData *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_GetData(query->host10, QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d10_query_GetDataSize
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_query_GetDataSize(ID3D10Query *iface)
{
    struct qemu_d3d10_query_GetDataSize call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDATASIZE);
    call.iface = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_query_GetDataSize(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetDataSize *c = (struct qemu_d3d10_query_GetDataSize *)call;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Query_GetDataSize(query->host10);
}

#endif

struct qemu_d3d10_query_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_query_GetDesc(ID3D10Query *iface, D3D10_QUERY_DESC *desc)
{
    struct qemu_d3d10_query_GetDesc call;
    struct qemu_d3d11_query *query = impl_from_ID3D10Query(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_QUERY_GETDESC);
    call.iface = (ULONG_PTR)query;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_query_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_query_GetDesc *c = (struct qemu_d3d10_query_GetDesc *)call;
    struct qemu_d3d11_query *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    ID3D10Query_GetDesc(query->host10, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11QueryVtbl d3d11_query_vtbl =
{
    /* IUnknown methods */
    d3d11_query_QueryInterface,
    d3d11_query_AddRef,
    d3d11_query_Release,
    /* ID3D11DeviceChild methods */
    d3d11_query_GetDevice,
    d3d11_query_GetPrivateData,
    d3d11_query_SetPrivateData,
    d3d11_query_SetPrivateDataInterface,
    /* ID3D11Asynchronous methods */
    d3d11_query_GetDataSize,
    /* ID3D11Query methods */
    d3d11_query_GetDesc,
};

static struct ID3D10QueryVtbl d3d10_query_vtbl =
{
    /* IUnknown methods */
    d3d10_query_QueryInterface,
    d3d10_query_AddRef,
    d3d10_query_Release,
    /* ID3D10DeviceChild methods */
    d3d10_query_GetDevice,
    d3d10_query_GetPrivateData,
    d3d10_query_SetPrivateData,
    d3d10_query_SetPrivateDataInterface,
    /* ID3D10Asynchronous methods */
    d3d10_query_Begin,
    d3d10_query_End,
    d3d10_query_GetData,
    d3d10_query_GetDataSize,
    /* ID3D10Query methods */
    d3d10_query_GetDesc,
};

void qemu_d3d11_query_guest_init(struct qemu_d3d11_query *query)
{
    query->ID3D11Query_iface.lpVtbl = &d3d11_query_vtbl;
    query->ID3D10Query_iface.lpVtbl = &d3d10_query_vtbl;
    wined3d_private_store_init(&query->private_store);
}

struct qemu_d3d11_query *unsafe_impl_from_ID3D11Query(ID3D11Query *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_query_vtbl);*/
    return CONTAINING_RECORD(iface, struct qemu_d3d11_query, ID3D11Query_iface);
}

struct qemu_d3d11_query *unsafe_impl_from_ID3D11Asynchronous(ID3D11Asynchronous *iface)
{
    return unsafe_impl_from_ID3D11Query((ID3D11Query *)iface);
}

#else

static inline struct qemu_d3d11_query *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_query, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_query_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_query_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_d3d11_query *query = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&query->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", query, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE d3d11_query_priv_data_Release(IUnknown *iface)
{
    struct qemu_d3d11_query *query = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&query->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", query, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying query wrapper %p for host query %p.\n", query, query->host11);
        HeapFree(GetProcessHeap(), 0, query);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_query_priv_data_QueryInterface,
    d3d11_query_priv_data_AddRef,
    d3d11_query_priv_data_Release,
};

HRESULT qemu_d3d11_query_create(ID3D11Query *host, struct qemu_d3d11_query **query)
{
    struct qemu_d3d11_query *obj;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    obj->host11 = host;
    hr = ID3D11View_QueryInterface(host, &IID_ID3D10Query, (void **)&obj->host10);
    if (FAILED(hr))
        WINE_ERR("Failed to QI ID3D10Query.\n");
    ID3D11Query_Release(obj->host10);

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    ID3D11View_SetPrivateDataInterface(host, &IID_d3d11_priv_data, &obj->priv_data_iface);

    *query = obj;
    return S_OK;
}

#endif
