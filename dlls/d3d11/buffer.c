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

struct qemu_d3d11_buffer_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_buffer *impl_from_ID3D11Buffer(ID3D11Buffer *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_buffer, ID3D11Buffer_iface);
}

static inline struct qemu_d3d11_buffer *impl_from_ID3D10Buffer(ID3D10Buffer *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_buffer, ID3D10Buffer_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_buffer_QueryInterface(ID3D11Buffer *iface, REFIID riid, void **out)
{
    struct qemu_d3d11_buffer_QueryInterface call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (IsEqualGUID(riid, &IID_ID3D11Buffer)
            || IsEqualGUID(riid, &IID_ID3D11Resource)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        ID3D11Buffer_AddRef(iface);
        *out = iface;
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_ID3D10Buffer)
            || IsEqualGUID(riid, &IID_ID3D10Resource)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        ID3D10Buffer_AddRef(&buffer->ID3D10Buffer_iface);
        *out = &buffer->ID3D10Buffer_iface;
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)buffer;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *out = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_buffer_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_QueryInterface *c = (struct qemu_d3d11_buffer_QueryInterface *)call;
    struct qemu_d3d11_buffer *buffer;
    IUnknown *obj;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Buffer_QueryInterface(buffer->host11, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_buffer_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_buffer_AddRef(ID3D11Buffer *iface)
{
    struct qemu_d3d11_buffer_AddRef call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_ADDREF);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_buffer_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_AddRef *c = (struct qemu_d3d11_buffer_AddRef *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Buffer_AddRef(buffer->host11);
}

#endif

struct qemu_d3d11_buffer_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_buffer_Release(ID3D11Buffer *iface)
{
    struct qemu_d3d11_buffer_Release call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_RELEASE);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_buffer_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_Release *c = (struct qemu_d3d11_buffer_Release *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Buffer_Release(buffer->host11);
}

#endif

struct qemu_d3d11_buffer_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_buffer_GetDevice(ID3D11Buffer *iface, ID3D11Device **device)
{
    struct qemu_d3d11_buffer_GetDevice call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_GETDEVICE);
    call.iface = (ULONG_PTR)buffer;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_buffer_GetDevice(ID3D10Buffer *iface, ID3D10Device **device)
{
    struct qemu_d3d11_buffer_GetDevice call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_GETDEVICE);
    call.iface = (ULONG_PTR)buffer;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_buffer_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_GetDevice *c = (struct qemu_d3d11_buffer_GetDevice *)call;
    struct qemu_d3d11_buffer *buffer;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    ID3D11Buffer_GetDevice(buffer->host11, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_buffer_GetPrivateData(ID3D11Buffer *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&buffer->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_buffer_SetPrivateData(ID3D11Buffer *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&buffer->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_buffer_SetPrivateDataInterface(ID3D11Buffer *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&buffer->private_store, guid, data);
}

#endif

struct qemu_d3d11_buffer_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_buffer_GetType(ID3D11Buffer *iface, D3D11_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d11_buffer_GetType call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_GETTYPE);
    call.iface = (ULONG_PTR)buffer;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_buffer_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_GetType *c = (struct qemu_d3d11_buffer_GetType *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    ID3D11Buffer_GetType(buffer->host11, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d11_buffer_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_buffer_SetEvictionPriority(ID3D11Buffer *iface, UINT eviction_priority)
{
    struct qemu_d3d11_buffer_SetEvictionPriority call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)buffer;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_buffer_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_SetEvictionPriority *c = (struct qemu_d3d11_buffer_SetEvictionPriority *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    ID3D11Buffer_SetEvictionPriority(buffer->host11, c->eviction_priority);
}

#endif

struct qemu_d3d11_buffer_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_buffer_GetEvictionPriority(ID3D11Buffer *iface)
{
    struct qemu_d3d11_buffer_GetEvictionPriority call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_buffer_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_GetEvictionPriority *c = (struct qemu_d3d11_buffer_GetEvictionPriority *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Buffer_GetEvictionPriority(buffer->host11);
}

#endif

struct qemu_d3d11_buffer_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_buffer_GetDesc(ID3D11Buffer *iface, D3D11_BUFFER_DESC *desc)
{
    struct qemu_d3d11_buffer_GetDesc call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D11Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BUFFER_GETDESC);
    call.iface = (ULONG_PTR)buffer;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_buffer_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_buffer_GetDesc *c = (struct qemu_d3d11_buffer_GetDesc *)call;
    struct qemu_d3d11_buffer *buffer;

    /* D3D11_BUFFER_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    ID3D11Buffer_GetDesc(buffer->host11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_buffer_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_buffer_QueryInterface(ID3D10Buffer *iface, REFIID riid, void **out)
{
    struct qemu_d3d10_buffer_QueryInterface call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)buffer;
    call.riid = (ULONG_PTR)riid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_buffer_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_QueryInterface *c = (struct qemu_d3d10_buffer_QueryInterface *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Buffer_QueryInterface(buffer->host10, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d10_buffer_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_buffer_AddRef(ID3D10Buffer *iface)
{
    struct qemu_d3d10_buffer_AddRef call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_ADDREF);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_buffer_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_AddRef *c = (struct qemu_d3d10_buffer_AddRef *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Buffer_AddRef(buffer->host10);
}

#endif

struct qemu_d3d10_buffer_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_buffer_Release(ID3D10Buffer *iface)
{
    struct qemu_d3d10_buffer_Release call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_RELEASE);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_buffer_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_Release *c = (struct qemu_d3d10_buffer_Release *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Buffer_Release(buffer->host10);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_buffer_GetPrivateData(ID3D10Buffer *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&buffer->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_buffer_SetPrivateData(ID3D10Buffer *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&buffer->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_buffer_SetPrivateDataInterface(ID3D10Buffer *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&buffer->private_store, guid, data);
}

#endif

struct qemu_d3d10_buffer_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_buffer_GetType(ID3D10Buffer *iface, D3D10_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d10_buffer_GetType call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_GETTYPE);
    call.iface = (ULONG_PTR)buffer;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_buffer_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_GetType *c = (struct qemu_d3d10_buffer_GetType *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    ID3D10Buffer_GetType(buffer->host10, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d10_buffer_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_buffer_SetEvictionPriority(ID3D10Buffer *iface, UINT eviction_priority)
{
    struct qemu_d3d10_buffer_SetEvictionPriority call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)buffer;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_buffer_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_SetEvictionPriority *c = (struct qemu_d3d10_buffer_SetEvictionPriority *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    ID3D10Buffer_SetEvictionPriority(buffer->host10, c->eviction_priority);
}

#endif

struct qemu_d3d10_buffer_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_buffer_GetEvictionPriority(ID3D10Buffer *iface)
{
    struct qemu_d3d10_buffer_GetEvictionPriority call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_buffer_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_GetEvictionPriority *c = (struct qemu_d3d10_buffer_GetEvictionPriority *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Buffer_GetEvictionPriority(buffer->host10);
}

#endif

struct qemu_d3d10_buffer_Map
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t map_type;
    uint64_t map_flags;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_buffer_Map(ID3D10Buffer *iface, D3D10_MAP map_type, UINT map_flags, void **data)
{
    struct qemu_d3d10_buffer_Map call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_MAP);
    call.iface = (ULONG_PTR)buffer;
    call.map_type = map_type;
    call.map_flags = map_flags;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_buffer_Map(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_Map *c = (struct qemu_d3d10_buffer_Map *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Buffer_Map(buffer->host10, c->map_type, c->map_flags, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_buffer_Unmap
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_buffer_Unmap(ID3D10Buffer *iface)
{
    struct qemu_d3d10_buffer_Unmap call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_UNMAP);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_buffer_Unmap(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_Unmap *c = (struct qemu_d3d10_buffer_Unmap *)call;
    struct qemu_d3d11_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    ID3D10Buffer_Unmap(buffer->host10);
}

#endif

struct qemu_d3d10_buffer_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_buffer_GetDesc(ID3D10Buffer *iface, D3D10_BUFFER_DESC *desc)
{
    struct qemu_d3d10_buffer_GetDesc call;
    struct qemu_d3d11_buffer *buffer = impl_from_ID3D10Buffer(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BUFFER_GETDESC);
    call.iface = (ULONG_PTR)buffer;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_buffer_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_buffer_GetDesc *c = (struct qemu_d3d10_buffer_GetDesc *)call;
    struct qemu_d3d11_buffer *buffer;

    /* D3D10_BUFFER_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    ID3D10Buffer_GetDesc(buffer->host10, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11BufferVtbl d3d11_buffer_vtbl =
{
    /* IUnknown methods */
    d3d11_buffer_QueryInterface,
    d3d11_buffer_AddRef,
    d3d11_buffer_Release,
    /* ID3D11DeviceChild methods */
    d3d11_buffer_GetDevice,
    d3d11_buffer_GetPrivateData,
    d3d11_buffer_SetPrivateData,
    d3d11_buffer_SetPrivateDataInterface,
    /* ID3D11Resource methods */
    d3d11_buffer_GetType,
    d3d11_buffer_SetEvictionPriority,
    d3d11_buffer_GetEvictionPriority,
    /* ID3D11Buffer methods */
    d3d11_buffer_GetDesc,
};

struct qemu_d3d11_buffer *unsafe_impl_from_ID3D11Buffer(ID3D11Buffer *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_buffer_vtbl);*/
    return CONTAINING_RECORD(iface, struct qemu_d3d11_buffer, ID3D11Buffer_iface);
}

static struct ID3D10BufferVtbl d3d10_buffer_vtbl =
{
    /* IUnknown methods */
    d3d10_buffer_QueryInterface,
    d3d10_buffer_AddRef,
    d3d10_buffer_Release,
    /* ID3D10DeviceChild methods */
    d3d10_buffer_GetDevice,
    d3d10_buffer_GetPrivateData,
    d3d10_buffer_SetPrivateData,
    d3d10_buffer_SetPrivateDataInterface,
    /* ID3D10Resource methods */
    d3d10_buffer_GetType,
    d3d10_buffer_SetEvictionPriority,
    d3d10_buffer_GetEvictionPriority,
    /* ID3D10Buffer methods */
    d3d10_buffer_Map,
    d3d10_buffer_Unmap,
    d3d10_buffer_GetDesc,
};

struct qemu_d3d11_buffer *unsafe_impl_from_ID3D10Buffer(ID3D10Buffer *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_buffer_vtbl);*/
    return CONTAINING_RECORD(iface, struct qemu_d3d11_buffer, ID3D10Buffer_iface);
}

void qemu_d3d11_buffer_guest_init(struct qemu_d3d11_buffer *buffer)
{
    buffer->ID3D11Buffer_iface.lpVtbl = &d3d11_buffer_vtbl;
    buffer->ID3D10Buffer_iface.lpVtbl = &d3d10_buffer_vtbl;
    wined3d_private_store_init(&buffer->private_store);
}

void __fastcall d3d11_buffer_guest_destroy(struct qemu_d3d11_buffer *buffer)
{
    wined3d_private_store_cleanup(&buffer->private_store);
}

#else

static inline struct qemu_d3d11_buffer *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_buffer, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_buffer_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_buffer_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_d3d11_buffer *buffer = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&buffer->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", buffer, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE d3d11_buffer_priv_data_Release(IUnknown *iface)
{
    struct qemu_d3d11_buffer *buffer = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&buffer->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", buffer, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying buffer wrapper %p for host buffer %p.\n", buffer, buffer->host11);
        qemu_ops->qemu_execute(QEMU_G2H(d3d11_buffer_guest_destroy), QEMU_H2G(buffer));
        HeapFree(GetProcessHeap(), 0, buffer);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_buffer_priv_data_QueryInterface,
    d3d11_buffer_priv_data_AddRef,
    d3d11_buffer_priv_data_Release,
};

HRESULT qemu_d3d11_buffer_create(ID3D11Buffer *host, struct qemu_d3d11_buffer **buffer)
{
    struct qemu_d3d11_buffer *obj;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    obj->host11 = host;
    hr = ID3D11Buffer_QueryInterface(host, &IID_ID3D10Buffer, (void **)&obj->host10);
    if (FAILED(hr))
        WINE_ERR("Failed to QI ID3D10Buffer.\n");
    ID3D10Texture3D_Release(obj->host10);

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    ID3D11Buffer_SetPrivateDataInterface(host, &IID_d3d11_priv_data, &obj->priv_data_iface);

    *buffer = obj;
    return S_OK;
}

#endif
