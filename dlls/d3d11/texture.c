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

#include "qemudxgi.h"
#include "qemu_d3d11.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

struct qemu_d3d11_texture1d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_texture *impl_from_ID3D11Texture1D(ID3D11Texture1D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, ID3D11Texture1D_iface);
}

static inline struct qemu_d3d11_texture *impl_from_ID3D10Texture1D(ID3D10Texture1D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, ID3D10Texture1D_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_texture1d_QueryInterface(ID3D11Texture1D *iface, REFIID iid, void **out)
{
    struct qemu_d3d11_texture1d_QueryInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    WINE_TRACE("iface %p, iid %s, out %p.\n", iface, wine_dbgstr_guid(iid), out);

    if (IsEqualGUID(iid, &IID_ID3D11Texture1D)
            || IsEqualGUID(iid, &IID_ID3D11Resource)
            || IsEqualGUID(iid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(iid, &IID_IUnknown))
    {
        *out = iface;
        IUnknown_AddRef(iface);
        return S_OK;
    }

    if (IsEqualGUID(iid, &IID_ID3D10Texture1D)
            || IsEqualGUID(iid, &IID_ID3D10Resource)
            || IsEqualGUID(iid, &IID_ID3D10DeviceChild))
    {
        *out = &texture->ID3D10Texture1D_iface;
        IUnknown_AddRef((IUnknown *)*out);
        return S_OK;
    }

    if (texture->dxgi_surface)
    {
        WINE_TRACE("Forwarding to dxgi surface.\n");
        return IUnknown_QueryInterface(texture->dxgi_surface, iid, out);
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(iid));

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_QUERYINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    *out = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_texture1d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_QueryInterface *c = (struct qemu_d3d11_texture1d_QueryInterface *)call;
    struct qemu_d3d11_texture *texture;
    IUnknown *obj;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_QueryInterface(texture->host11_1d, QEMU_G2H(c->iid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->iid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_texture1d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_texture1d_AddRef(ID3D11Texture1D *iface)
{
    struct qemu_d3d11_texture1d_AddRef call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_ADDREF);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture1d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_AddRef *c = (struct qemu_d3d11_texture1d_AddRef *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_AddRef(texture->host11_1d);
}

#endif

struct qemu_d3d11_texture1d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_texture1d_Release(ID3D11Texture1D *iface)
{
    struct qemu_d3d11_texture1d_Release call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_RELEASE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture1d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_Release *c = (struct qemu_d3d11_texture1d_Release *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_Release(texture->host11_1d);
}

#endif

struct qemu_d3d11_texture1d_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture1d_GetDevice(ID3D11Texture1D *iface, ID3D11Device **device)
{
    struct qemu_d3d11_texture1d_GetDevice call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_GETDEVICE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_texture1d_GetDevice(ID3D10Texture1D *iface, ID3D10Device **device)
{
    struct qemu_d3d11_texture1d_GetDevice call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_GETDEVICE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_texture1d_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_GetDevice *c = (struct qemu_d3d11_texture1d_GetDevice *)call;
    struct qemu_d3d11_texture *texture;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture1D_GetDevice(texture->host11_1d, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

struct qemu_d3d11_texture1d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture1d_GetPrivateData(ID3D11Texture1D *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_texture1d_GetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture1d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_GetPrivateData *c = (struct qemu_d3d11_texture1d_GetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_GetPrivateData(texture->host11_1d, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture1d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture1d_SetPrivateData(ID3D11Texture1D *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_texture1d_SetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture1d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_SetPrivateData *c = (struct qemu_d3d11_texture1d_SetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_SetPrivateData(texture->host11_1d, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture1d_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture1d_SetPrivateDataInterface(ID3D11Texture1D *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_texture1d_SetPrivateDataInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture1d_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_SetPrivateDataInterface *c = (struct qemu_d3d11_texture1d_SetPrivateDataInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_SetPrivateDataInterface(texture->host11_1d, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture1d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture1d_GetType(ID3D11Texture1D *iface, D3D11_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d11_texture1d_GetType call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_GETTYPE);
    call.iface = (ULONG_PTR)texture;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture1d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_GetType *c = (struct qemu_d3d11_texture1d_GetType *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture1D_GetType(texture->host11_1d, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d11_texture1d_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture1d_SetEvictionPriority(ID3D11Texture1D *iface, UINT eviction_priority)
{
    struct qemu_d3d11_texture1d_SetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture1d_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_SetEvictionPriority *c = (struct qemu_d3d11_texture1d_SetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture1D_SetEvictionPriority(texture->host11_1d, c->eviction_priority);
}

#endif

struct qemu_d3d11_texture1d_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_texture1d_GetEvictionPriority(ID3D11Texture1D *iface)
{
    struct qemu_d3d11_texture1d_GetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture1d_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_GetEvictionPriority *c = (struct qemu_d3d11_texture1d_GetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture1D_GetEvictionPriority(texture->host11_1d);
}

#endif

struct qemu_d3d11_texture1d_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture1d_GetDesc(ID3D11Texture1D *iface, D3D11_TEXTURE1D_DESC *desc)
{
    struct qemu_d3d11_texture1d_GetDesc call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE1D_GETDESC);
    call.iface = (ULONG_PTR)texture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture1d_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture1d_GetDesc *c = (struct qemu_d3d11_texture1d_GetDesc *)call;
    struct qemu_d3d11_texture *texture;

    /* D3D11_TEXTURE1D_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture1D_GetDesc(texture->host11_1d, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture1d_QueryInterface(ID3D10Texture1D *iface, REFIID iid, void **out)
{
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    WINE_TRACE("iface %p, iid %s, out %p.\n", iface, wine_dbgstr_guid(iid), out);

    return d3d11_texture1d_QueryInterface(&texture->ID3D11Texture1D_iface, iid, out);
}

#endif

struct qemu_d3d10_texture1d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_texture1d_AddRef(ID3D10Texture1D *iface)
{
    struct qemu_d3d10_texture1d_AddRef call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_ADDREF);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_AddRef *c = (struct qemu_d3d10_texture1d_AddRef *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_AddRef(texture->host10_1d);
}

#endif

struct qemu_d3d10_texture1d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_texture1d_Release(ID3D10Texture1D *iface)
{
    struct qemu_d3d10_texture1d_Release call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_RELEASE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_Release *c = (struct qemu_d3d10_texture1d_Release *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_Release(texture->host10_1d);
}

#endif

struct qemu_d3d10_texture1d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture1d_GetPrivateData(ID3D10Texture1D *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_texture1d_GetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_GetPrivateData *c = (struct qemu_d3d10_texture1d_GetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_GetPrivateData(texture->host10_1d, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture1d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture1d_SetPrivateData(ID3D10Texture1D *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_texture1d_SetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_SetPrivateData *c = (struct qemu_d3d10_texture1d_SetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_SetPrivateData(texture->host10_1d, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture1d_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture1d_SetPrivateDataInterface(ID3D10Texture1D *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_texture1d_SetPrivateDataInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_SetPrivateDataInterface *c = (struct qemu_d3d10_texture1d_SetPrivateDataInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_SetPrivateDataInterface(texture->host10_1d, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture1d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture1d_GetType(ID3D10Texture1D *iface, D3D10_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d10_texture1d_GetType call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_GETTYPE);
    call.iface = (ULONG_PTR)texture;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture1d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_GetType *c = (struct qemu_d3d10_texture1d_GetType *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture1D_GetType(texture->host10_1d, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d10_texture1d_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture1d_SetEvictionPriority(ID3D10Texture1D *iface, UINT eviction_priority)
{
    struct qemu_d3d10_texture1d_SetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture1d_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_SetEvictionPriority *c = (struct qemu_d3d10_texture1d_SetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture1D_SetEvictionPriority(texture->host10_1d, c->eviction_priority);
}

#endif

struct qemu_d3d10_texture1d_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_texture1d_GetEvictionPriority(ID3D10Texture1D *iface)
{
    struct qemu_d3d10_texture1d_GetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_GetEvictionPriority *c = (struct qemu_d3d10_texture1d_GetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_GetEvictionPriority(texture->host10_1d);
}

#endif

struct qemu_d3d10_texture1d_Map
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sub_resource_idx;
    uint64_t map_type;
    uint64_t map_flags;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture1d_Map(ID3D10Texture1D *iface, UINT sub_resource_idx, D3D10_MAP map_type, UINT map_flags, void **data)
{
    struct qemu_d3d10_texture1d_Map call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_MAP);
    call.iface = (ULONG_PTR)texture;
    call.sub_resource_idx = sub_resource_idx;
    call.map_type = map_type;
    call.map_flags = map_flags;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture1d_Map(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_Map *c = (struct qemu_d3d10_texture1d_Map *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture1D_Map(texture->host10_1d, c->sub_resource_idx, c->map_type, c->map_flags, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture1d_Unmap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sub_resource_idx;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture1d_Unmap(ID3D10Texture1D *iface, UINT sub_resource_idx)
{
    struct qemu_d3d10_texture1d_Unmap call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_UNMAP);
    call.iface = (ULONG_PTR)texture;
    call.sub_resource_idx = sub_resource_idx;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture1d_Unmap(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_Unmap *c = (struct qemu_d3d10_texture1d_Unmap *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture1D_Unmap(texture->host10_1d, c->sub_resource_idx);
}

#endif

struct qemu_d3d10_texture1d_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture1d_GetDesc(ID3D10Texture1D *iface, D3D10_TEXTURE1D_DESC *desc)
{
    struct qemu_d3d10_texture1d_GetDesc call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture1D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE1D_GETDESC);
    call.iface = (ULONG_PTR)texture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture1d_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture1d_GetDesc *c = (struct qemu_d3d10_texture1d_GetDesc *)call;
    struct qemu_d3d11_texture *texture;

    /* D3D10_TEXTURE1D_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture1D_GetDesc(texture->host10_1d, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_texture2d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_texture *impl_from_ID3D11Texture2D(ID3D11Texture2D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, ID3D11Texture2D_iface);
}

static inline struct qemu_d3d11_texture *impl_from_ID3D10Texture2D(ID3D10Texture2D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, ID3D10Texture2D_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_texture2d_QueryInterface(ID3D11Texture2D *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_texture2d_QueryInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    if (IsEqualGUID(riid, &IID_ID3D11Texture2D)
            || IsEqualGUID(riid, &IID_ID3D11Resource)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        *object = &texture->ID3D11Texture2D_iface;
        IUnknown_AddRef((IUnknown *)*object);
        return S_OK;
    }
    else if (IsEqualGUID(riid, &IID_ID3D10Texture2D)
            || IsEqualGUID(riid, &IID_ID3D10Resource)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        *object = &texture->ID3D10Texture2D_iface;
        IUnknown_AddRef((IUnknown *)*object);
        return S_OK;
    }

    if (texture->dxgi_surface)
    {
        WINE_TRACE("Forwarding to dxgi surface.\n");
        return IUnknown_QueryInterface(texture->dxgi_surface, riid, object);
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_QUERYINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_texture2d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_QueryInterface *c = (struct qemu_d3d11_texture2d_QueryInterface *)call;
    struct qemu_d3d11_texture *texture;
    IUnknown *obj;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_QueryInterface(texture->host11_2d, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_texture2d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_texture2d_AddRef(ID3D11Texture2D *iface)
{
    struct qemu_d3d11_texture2d_AddRef call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_ADDREF);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture2d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_AddRef *c = (struct qemu_d3d11_texture2d_AddRef *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_AddRef(texture->host11_2d);
}

#endif

struct qemu_d3d11_texture2d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_texture2d_Release(ID3D11Texture2D *iface)
{
    struct qemu_d3d11_texture2d_Release call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_RELEASE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture2d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_Release *c = (struct qemu_d3d11_texture2d_Release *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_Release(texture->host11_2d);
}

#endif

struct qemu_d3d11_texture2d_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture2d_GetDevice(ID3D11Texture2D *iface, ID3D11Device **device)
{
    struct qemu_d3d11_texture2d_GetDevice call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_GETDEVICE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_texture2d_GetDevice(ID3D10Texture2D *iface, ID3D10Device **device)
{
    struct qemu_d3d11_texture2d_GetDevice call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_GETDEVICE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_texture2d_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_GetDevice *c = (struct qemu_d3d11_texture2d_GetDevice *)call;
    struct qemu_d3d11_texture *texture;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture2D_GetDevice(texture->host11_1d, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

struct qemu_d3d11_texture2d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture2d_GetPrivateData(ID3D11Texture2D *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_texture2d_GetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture2d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_GetPrivateData *c = (struct qemu_d3d11_texture2d_GetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_GetPrivateData(texture->host11_2d, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture2d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture2d_SetPrivateData(ID3D11Texture2D *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_texture2d_SetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture2d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_SetPrivateData *c = (struct qemu_d3d11_texture2d_SetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_SetPrivateData(texture->host11_2d, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture2d_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture2d_SetPrivateDataInterface(ID3D11Texture2D *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_texture2d_SetPrivateDataInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture2d_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_SetPrivateDataInterface *c = (struct qemu_d3d11_texture2d_SetPrivateDataInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_SetPrivateDataInterface(texture->host11_2d, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture2d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture2d_GetType(ID3D11Texture2D *iface, D3D11_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d11_texture2d_GetType call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_GETTYPE);
    call.iface = (ULONG_PTR)texture;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture2d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_GetType *c = (struct qemu_d3d11_texture2d_GetType *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture2D_GetType(texture->host11_2d, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d11_texture2d_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture2d_SetEvictionPriority(ID3D11Texture2D *iface, UINT eviction_priority)
{
    struct qemu_d3d11_texture2d_SetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture2d_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_SetEvictionPriority *c = (struct qemu_d3d11_texture2d_SetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture2D_SetEvictionPriority(texture->host11_2d, c->eviction_priority);
}

#endif

struct qemu_d3d11_texture2d_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_texture2d_GetEvictionPriority(ID3D11Texture2D *iface)
{
    struct qemu_d3d11_texture2d_GetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture2d_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_GetEvictionPriority *c = (struct qemu_d3d11_texture2d_GetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture2D_GetEvictionPriority(texture->host11_2d);
}

#endif

struct qemu_d3d11_texture2d_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture2d_GetDesc(ID3D11Texture2D *iface, D3D11_TEXTURE2D_DESC *desc)
{
    struct qemu_d3d11_texture2d_GetDesc call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE2D_GETDESC);
    call.iface = (ULONG_PTR)texture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture2d_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture2d_GetDesc *c = (struct qemu_d3d11_texture2d_GetDesc *)call;
    struct qemu_d3d11_texture *texture;

    /* D3D11_TEXTURE2D_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture2D_GetDesc(texture->host11_2d, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_texture2d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture2d_QueryInterface(ID3D10Texture2D *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_texture2d_QueryInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_QUERYINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_QueryInterface *c = (struct qemu_d3d10_texture2d_QueryInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_QueryInterface(texture->host10_2d, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_texture2d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_texture2d_AddRef(ID3D10Texture2D *iface)
{
    struct qemu_d3d10_texture2d_AddRef call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_ADDREF);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_AddRef *c = (struct qemu_d3d10_texture2d_AddRef *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_AddRef(texture->host10_2d);
}

#endif

struct qemu_d3d10_texture2d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_texture2d_Release(ID3D10Texture2D *iface)
{
    struct qemu_d3d10_texture2d_Release call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_RELEASE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_Release *c = (struct qemu_d3d10_texture2d_Release *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_Release(texture->host10_2d);
}

#endif

struct qemu_d3d10_texture2d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture2d_GetPrivateData(ID3D10Texture2D *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_texture2d_GetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_GetPrivateData *c = (struct qemu_d3d10_texture2d_GetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_GetPrivateData(texture->host10_2d, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture2d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture2d_SetPrivateData(ID3D10Texture2D *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_texture2d_SetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_SetPrivateData *c = (struct qemu_d3d10_texture2d_SetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_SetPrivateData(texture->host10_2d, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture2d_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture2d_SetPrivateDataInterface(ID3D10Texture2D *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_texture2d_SetPrivateDataInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_SetPrivateDataInterface *c = (struct qemu_d3d10_texture2d_SetPrivateDataInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_SetPrivateDataInterface(texture->host10_2d, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture2d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture2d_GetType(ID3D10Texture2D *iface, D3D10_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d10_texture2d_GetType call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_GETTYPE);
    call.iface = (ULONG_PTR)texture;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture2d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_GetType *c = (struct qemu_d3d10_texture2d_GetType *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture2D_GetType(texture->host10_2d, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d10_texture2d_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture2d_SetEvictionPriority(ID3D10Texture2D *iface, UINT eviction_priority)
{
    struct qemu_d3d10_texture2d_SetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture2d_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_SetEvictionPriority *c = (struct qemu_d3d10_texture2d_SetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture2D_SetEvictionPriority(texture->host10_2d, c->eviction_priority);
}

#endif

struct qemu_d3d10_texture2d_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_texture2d_GetEvictionPriority(ID3D10Texture2D *iface)
{
    struct qemu_d3d10_texture2d_GetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_GetEvictionPriority *c = (struct qemu_d3d10_texture2d_GetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_GetEvictionPriority(texture->host10_2d);
}

#endif

struct qemu_d3d10_texture2d_Map
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sub_resource_idx;
    uint64_t map_type;
    uint64_t map_flags;
    uint64_t mapped_texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture2d_Map(ID3D10Texture2D *iface, UINT sub_resource_idx, D3D10_MAP map_type, UINT map_flags, D3D10_MAPPED_TEXTURE2D *mapped_texture)
{
    struct qemu_d3d10_texture2d_Map call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_MAP);
    call.iface = (ULONG_PTR)texture;
    call.sub_resource_idx = sub_resource_idx;
    call.map_type = map_type;
    call.map_flags = map_flags;
    call.mapped_texture = (ULONG_PTR)mapped_texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture2d_Map(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_Map *c = (struct qemu_d3d10_texture2d_Map *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture2D_Map(texture->host10_2d, c->sub_resource_idx, c->map_type, c->map_flags, QEMU_G2H(c->mapped_texture));
}

#endif

struct qemu_d3d10_texture2d_Unmap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sub_resource_idx;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture2d_Unmap(ID3D10Texture2D *iface, UINT sub_resource_idx)
{
    struct qemu_d3d10_texture2d_Unmap call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_UNMAP);
    call.iface = (ULONG_PTR)texture;
    call.sub_resource_idx = sub_resource_idx;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture2d_Unmap(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_Unmap *c = (struct qemu_d3d10_texture2d_Unmap *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture2D_Unmap(texture->host10_2d, c->sub_resource_idx);
}

#endif

struct qemu_d3d10_texture2d_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture2d_GetDesc(ID3D10Texture2D *iface, D3D10_TEXTURE2D_DESC *desc)
{
    struct qemu_d3d10_texture2d_GetDesc call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture2D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE2D_GETDESC);
    call.iface = (ULONG_PTR)texture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture2d_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture2d_GetDesc *c = (struct qemu_d3d10_texture2d_GetDesc *)call;
    struct qemu_d3d11_texture *texture;

    /* D3D10_TEXTURE2D_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture2D_GetDesc(texture->host10_2d, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_texture3d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_texture *impl_from_ID3D11Texture3D(ID3D11Texture3D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, ID3D11Texture3D_iface);
}

static inline struct qemu_d3d11_texture *impl_from_ID3D10Texture3D(ID3D10Texture3D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, ID3D10Texture3D_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_texture3d_QueryInterface(ID3D11Texture3D *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_texture3d_QueryInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_QUERYINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_QueryInterface *c = (struct qemu_d3d11_texture3d_QueryInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_QueryInterface(texture->host11_3d, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_texture3d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_texture3d_AddRef(ID3D11Texture3D *iface)
{
    struct qemu_d3d11_texture3d_AddRef call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_ADDREF);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_AddRef *c = (struct qemu_d3d11_texture3d_AddRef *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_AddRef(texture->host11_3d);
}

#endif

struct qemu_d3d11_texture3d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_texture3d_Release(ID3D11Texture3D *iface)
{
    struct qemu_d3d11_texture3d_Release call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_RELEASE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_Release *c = (struct qemu_d3d11_texture3d_Release *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_Release(texture->host11_3d);
}

#endif

struct qemu_d3d11_texture3d_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture3d_GetDevice(ID3D11Texture3D *iface, ID3D11Device **device)
{
    struct qemu_d3d11_texture3d_GetDevice call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_GETDEVICE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_texture3d_GetDevice(ID3D10Texture3D *iface, ID3D10Device **device)
{
    struct qemu_d3d11_texture3d_GetDevice call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_GETDEVICE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_texture3d_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_GetDevice *c = (struct qemu_d3d11_texture3d_GetDevice *)call;
    struct qemu_d3d11_texture *texture;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture3D_GetDevice(texture->host11_3d, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

struct qemu_d3d11_texture3d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture3d_GetPrivateData(ID3D11Texture3D *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_texture3d_GetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_GetPrivateData *c = (struct qemu_d3d11_texture3d_GetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_GetPrivateData(texture->host11_3d, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture3d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture3d_SetPrivateData(ID3D11Texture3D *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_texture3d_SetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_SetPrivateData *c = (struct qemu_d3d11_texture3d_SetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_SetPrivateData(texture->host11_3d, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture3d_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_texture3d_SetPrivateDataInterface(ID3D11Texture3D *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_texture3d_SetPrivateDataInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_SetPrivateDataInterface *c = (struct qemu_d3d11_texture3d_SetPrivateDataInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_SetPrivateDataInterface(texture->host11_3d, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_texture3d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture3d_GetType(ID3D11Texture3D *iface, D3D11_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d11_texture3d_GetType call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_GETTYPE);
    call.iface = (ULONG_PTR)texture;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture3d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_GetType *c = (struct qemu_d3d11_texture3d_GetType *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture3D_GetType(texture->host11_3d, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d11_texture3d_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture3d_SetEvictionPriority(ID3D11Texture3D *iface, UINT eviction_priority)
{
    struct qemu_d3d11_texture3d_SetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture3d_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_SetEvictionPriority *c = (struct qemu_d3d11_texture3d_SetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture3D_SetEvictionPriority(texture->host11_3d, c->eviction_priority);
}

#endif

struct qemu_d3d11_texture3d_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_texture3d_GetEvictionPriority(ID3D11Texture3D *iface)
{
    struct qemu_d3d11_texture3d_GetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_texture3d_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_GetEvictionPriority *c = (struct qemu_d3d11_texture3d_GetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Texture3D_GetEvictionPriority(texture->host11_3d);
}

#endif

struct qemu_d3d11_texture3d_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_texture3d_GetDesc(ID3D11Texture3D *iface, D3D11_TEXTURE3D_DESC *desc)
{
    struct qemu_d3d11_texture3d_GetDesc call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D11Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_TEXTURE3D_GETDESC);
    call.iface = (ULONG_PTR)texture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_texture3d_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_texture3d_GetDesc *c = (struct qemu_d3d11_texture3d_GetDesc *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D11Texture3D_GetDesc(texture->host11_3d, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_texture3d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture3d_QueryInterface(ID3D10Texture3D *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_texture3d_QueryInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_QUERYINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_QueryInterface *c = (struct qemu_d3d10_texture3d_QueryInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_QueryInterface(texture->host10_3d, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_texture3d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_texture3d_AddRef(ID3D10Texture3D *iface)
{
    struct qemu_d3d10_texture3d_AddRef call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_ADDREF);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_AddRef *c = (struct qemu_d3d10_texture3d_AddRef *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_AddRef(texture->host10_3d);
}

#endif

struct qemu_d3d10_texture3d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_texture3d_Release(ID3D10Texture3D *iface)
{
    struct qemu_d3d10_texture3d_Release call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_RELEASE);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_Release *c = (struct qemu_d3d10_texture3d_Release *)call;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_Release(texture->host10_3d);
}

#endif

struct qemu_d3d10_texture3d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture3d_GetPrivateData(ID3D10Texture3D *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_texture3d_GetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_GetPrivateData *c = (struct qemu_d3d10_texture3d_GetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_GetPrivateData(texture->host10_3d, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture3d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture3d_SetPrivateData(ID3D10Texture3D *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_texture3d_SetPrivateData call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_SetPrivateData *c = (struct qemu_d3d10_texture3d_SetPrivateData *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_SetPrivateData(texture->host10_3d, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture3d_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture3d_SetPrivateDataInterface(ID3D10Texture3D *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_texture3d_SetPrivateDataInterface call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)texture;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_SetPrivateDataInterface *c = (struct qemu_d3d10_texture3d_SetPrivateDataInterface *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_SetPrivateDataInterface(texture->host10_3d, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_texture3d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_dimension;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture3d_GetType(ID3D10Texture3D *iface, D3D10_RESOURCE_DIMENSION *resource_dimension)
{
    struct qemu_d3d10_texture3d_GetType call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_GETTYPE);
    call.iface = (ULONG_PTR)texture;
    call.resource_dimension = (ULONG_PTR)resource_dimension;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture3d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_GetType *c = (struct qemu_d3d10_texture3d_GetType *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture3D_GetType(texture->host10_3d, QEMU_G2H(c->resource_dimension));
}

#endif

struct qemu_d3d10_texture3d_SetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t eviction_priority;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture3d_SetEvictionPriority(ID3D10Texture3D *iface, UINT eviction_priority)
{
    struct qemu_d3d10_texture3d_SetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_SETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;
    call.eviction_priority = eviction_priority;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture3d_SetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_SetEvictionPriority *c = (struct qemu_d3d10_texture3d_SetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture3D_SetEvictionPriority(texture->host10_3d, c->eviction_priority);
}

#endif

struct qemu_d3d10_texture3d_GetEvictionPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_texture3d_GetEvictionPriority(ID3D10Texture3D *iface)
{
    struct qemu_d3d10_texture3d_GetEvictionPriority call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_GETEVICTIONPRIORITY);
    call.iface = (ULONG_PTR)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_GetEvictionPriority(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_GetEvictionPriority *c = (struct qemu_d3d10_texture3d_GetEvictionPriority *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_GetEvictionPriority(texture->host10_3d);
}

#endif

struct qemu_d3d10_texture3d_Map
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sub_resource_idx;
    uint64_t map_type;
    uint64_t map_flags;
    uint64_t mapped_texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_texture3d_Map(ID3D10Texture3D *iface, UINT sub_resource_idx, D3D10_MAP map_type, UINT map_flags, D3D10_MAPPED_TEXTURE3D *mapped_texture)
{
    struct qemu_d3d10_texture3d_Map call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_MAP);
    call.iface = (ULONG_PTR)texture;
    call.sub_resource_idx = sub_resource_idx;
    call.map_type = map_type;
    call.map_flags = map_flags;
    call.mapped_texture = (ULONG_PTR)mapped_texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_texture3d_Map(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_Map *c = (struct qemu_d3d10_texture3d_Map *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Texture3D_Map(texture->host10_3d, c->sub_resource_idx, c->map_type, c->map_flags, QEMU_G2H(c->mapped_texture));
}

#endif

struct qemu_d3d10_texture3d_Unmap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sub_resource_idx;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture3d_Unmap(ID3D10Texture3D *iface, UINT sub_resource_idx)
{
    struct qemu_d3d10_texture3d_Unmap call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_UNMAP);
    call.iface = (ULONG_PTR)texture;
    call.sub_resource_idx = sub_resource_idx;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture3d_Unmap(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_Unmap *c = (struct qemu_d3d10_texture3d_Unmap *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture3D_Unmap(texture->host10_3d, c->sub_resource_idx);
}

#endif

struct qemu_d3d10_texture3d_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_texture3d_GetDesc(ID3D10Texture3D *iface, D3D10_TEXTURE3D_DESC *desc)
{
    struct qemu_d3d10_texture3d_GetDesc call;
    struct qemu_d3d11_texture *texture = impl_from_ID3D10Texture3D(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_TEXTURE3D_GETDESC);
    call.iface = (ULONG_PTR)texture;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_texture3d_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_texture3d_GetDesc *c = (struct qemu_d3d10_texture3d_GetDesc *)call;
    struct qemu_d3d11_texture *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    ID3D10Texture3D_GetDesc(texture->host10_3d, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11Texture1DVtbl d3d11_texture1d_vtbl =
{
    /* IUnknown methods */
    d3d11_texture1d_QueryInterface,
    d3d11_texture1d_AddRef,
    d3d11_texture1d_Release,
    /* ID3D11DeviceChild methods */
    d3d11_texture1d_GetDevice,
    d3d11_texture1d_GetPrivateData,
    d3d11_texture1d_SetPrivateData,
    d3d11_texture1d_SetPrivateDataInterface,
    /* ID3D11Resource methods */
    d3d11_texture1d_GetType,
    d3d11_texture1d_SetEvictionPriority,
    d3d11_texture1d_GetEvictionPriority,
    /* ID3D11Texture1D methods */
    d3d11_texture1d_GetDesc,
};

static struct ID3D10Texture1DVtbl d3d10_texture1d_vtbl =
{
    /* IUnknown methods */
    d3d10_texture1d_QueryInterface,
    d3d10_texture1d_AddRef,
    d3d10_texture1d_Release,
    /* ID3D10DeviceChild methods */
    d3d10_texture1d_GetDevice,
    d3d10_texture1d_GetPrivateData,
    d3d10_texture1d_SetPrivateData,
    d3d10_texture1d_SetPrivateDataInterface,
    /* ID3D10Resource methods */
    d3d10_texture1d_GetType,
    d3d10_texture1d_SetEvictionPriority,
    d3d10_texture1d_GetEvictionPriority,
    /* ID3D10Texture1D methods */
    d3d10_texture1d_Map,
    d3d10_texture1d_Unmap,
    d3d10_texture1d_GetDesc,
};

static struct ID3D11Texture2DVtbl d3d11_texture2d_vtbl =
{
    /* IUnknown methods */
    d3d11_texture2d_QueryInterface,
    d3d11_texture2d_AddRef,
    d3d11_texture2d_Release,
    /* ID3D11DeviceChild methods */
    d3d11_texture2d_GetDevice,
    d3d11_texture2d_GetPrivateData,
    d3d11_texture2d_SetPrivateData,
    d3d11_texture2d_SetPrivateDataInterface,
    /* ID3D11Resource methods */
    d3d11_texture2d_GetType,
    d3d11_texture2d_SetEvictionPriority,
    d3d11_texture2d_GetEvictionPriority,
    /* ID3D11Texture2D methods */
    d3d11_texture2d_GetDesc,
};

static struct ID3D10Texture2DVtbl d3d10_texture2d_vtbl =
{
    /* IUnknown methods */
    d3d10_texture2d_QueryInterface,
    d3d10_texture2d_AddRef,
    d3d10_texture2d_Release,
    /* ID3D10DeviceChild methods */
    d3d10_texture2d_GetDevice,
    d3d10_texture2d_GetPrivateData,
    d3d10_texture2d_SetPrivateData,
    d3d10_texture2d_SetPrivateDataInterface,
    /* ID3D10Resource methods */
    d3d10_texture2d_GetType,
    d3d10_texture2d_SetEvictionPriority,
    d3d10_texture2d_GetEvictionPriority,
    /* ID3D10Texture2D methods */
    d3d10_texture2d_Map,
    d3d10_texture2d_Unmap,
    d3d10_texture2d_GetDesc,
};

static struct ID3D11Texture3DVtbl d3d11_texture3d_vtbl =
{
    /* IUnknown methods */
    d3d11_texture3d_QueryInterface,
    d3d11_texture3d_AddRef,
    d3d11_texture3d_Release,
    /* ID3D11DeviceChild methods */
    d3d11_texture3d_GetDevice,
    d3d11_texture3d_GetPrivateData,
    d3d11_texture3d_SetPrivateData,
    d3d11_texture3d_SetPrivateDataInterface,
    /* ID3D11Resource methods */
    d3d11_texture3d_GetType,
    d3d11_texture3d_SetEvictionPriority,
    d3d11_texture3d_GetEvictionPriority,
    /* ID3D11Texture3D methods */
    d3d11_texture3d_GetDesc,
};

static struct ID3D10Texture3DVtbl d3d10_texture3d_vtbl =
{
    /* IUnknown methods */
    d3d10_texture3d_QueryInterface,
    d3d10_texture3d_AddRef,
    d3d10_texture3d_Release,
    /* ID3D10DeviceChild methods */
    d3d10_texture3d_GetDevice,
    d3d10_texture3d_GetPrivateData,
    d3d10_texture3d_SetPrivateData,
    d3d10_texture3d_SetPrivateDataInterface,
    /* ID3D10Resource methods */
    d3d10_texture3d_GetType,
    d3d10_texture3d_SetEvictionPriority,
    d3d10_texture3d_GetEvictionPriority,
    /* ID3D10Texture3D methods */
    d3d10_texture3d_Map,
    d3d10_texture3d_Unmap,
    d3d10_texture3d_GetDesc,
};

void qemu_d3d11_texture_guest_init(struct qemu_d3d11_texture *texture, struct qemu_d3d11_device *device,
        unsigned int dim, uint64_t dxgi_surface)
{
    HRESULT hr;

    switch (dim)
    {
        case 1:
            texture->ID3D11Texture1D_iface.lpVtbl = &d3d11_texture1d_vtbl;
            texture->ID3D10Texture1D_iface.lpVtbl = &d3d10_texture1d_vtbl;
            break;
        case 2:
            texture->ID3D11Texture2D_iface.lpVtbl = &d3d11_texture2d_vtbl;
            texture->ID3D10Texture2D_iface.lpVtbl = &d3d10_texture2d_vtbl;
            break;
        case 3:
            texture->ID3D11Texture3D_iface.lpVtbl = &d3d11_texture3d_vtbl;
            texture->ID3D10Texture3D_iface.lpVtbl = &d3d10_texture3d_vtbl;
            break;
    }

    if (dxgi_surface)
    {
        IQemuDXGIDevice *dxgi_device;

        WINE_TRACE("Creating DXGI surface wrapper for texture %p.\n", texture);
        hr = ID3D11Device_QueryInterface(&device->ID3D11Device2_iface, &IID_IQemuDXGIDevice, (void **)&dxgi_device);
        if (FAILED(hr))
            WINE_ERR("Failed to QI IQemuDXGIDevice.\n");

        hr = dxgi_device->lpVtbl->create_surface(dxgi_device, dxgi_surface,
                &texture->dxgi_surface, (IUnknown *)&texture->ID3D11Texture1D_iface);
        if (FAILED(hr))
            WINE_ERR("Failed to create a IDXGISurface for the texture.\n");

        WINE_TRACE("Created dxgi surface %p for texture %p.\n", texture->dxgi_surface, texture);
        dxgi_device->lpVtbl->Release(dxgi_device);
    }
}

void qemu_d3d11_texture3d_guest_init(struct qemu_d3d11_texture *texture, struct qemu_d3d11_device *device,
        uint64_t dxgi_surface)
{
    texture->ID3D11Texture3D_iface.lpVtbl = &d3d11_texture3d_vtbl;
    texture->ID3D10Texture3D_iface.lpVtbl = &d3d10_texture3d_vtbl;
}

#else

static inline struct qemu_d3d11_texture *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_texture, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_texture_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_texture_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_d3d11_texture *texture = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&texture->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", texture, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE d3d11_texture_priv_data_Release(IUnknown *iface)
{
    struct qemu_d3d11_texture *texture = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&texture->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", texture, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying texture wrapper %p for host texture %p.\n", texture, texture->host11_2d);
        HeapFree(GetProcessHeap(), 0, texture);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_texture_priv_data_QueryInterface,
    d3d11_texture_priv_data_AddRef,
    d3d11_texture_priv_data_Release,
};

#include <initguid.h>

/* Do not make this the same as IID_Qemu_surface_priv_data */

HRESULT qemu_d3d11_texture_create(ID3D11Resource *host, struct qemu_d3d11_device *device,
        uint64_t *dxgi_surface, unsigned int dim, struct qemu_d3d11_texture **texture)
{
    struct qemu_d3d11_texture *obj;
    IDXGISurface *surface_iface;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    /* Note that we share the refcount with the host object, so we don't want to keep only one
     * reference to it. */
    switch (dim)
    {
        case 1:
            obj->host11_1d = (ID3D11Texture1D *)host;
            hr = ID3D11Resource_QueryInterface(host, &IID_ID3D10Texture1D, (void **)&obj->host10_1d);
            if (FAILED(hr))
                WINE_ERR("Failed to QI ID3D10Texture1D.\n");
            ID3D10Texture1D_Release(obj->host10_1d);
            break;
        case 2:
            obj->host11_2d = (ID3D11Texture2D *)host;
            hr = ID3D11Resource_QueryInterface(host, &IID_ID3D10Texture2D, (void **)&obj->host10_2d);
            if (FAILED(hr))
                WINE_ERR("Failed to QI ID3D10Texture1D.\n");
            ID3D10Texture2D_Release(obj->host10_2d);
            break;
        case 3:
            obj->host11_3d = (ID3D11Texture3D *)host;
            hr = ID3D11Resource_QueryInterface(host, &IID_ID3D10Texture3D, (void **)&obj->host10_3d);
            if (FAILED(hr))
                WINE_ERR("Failed to QI ID3D10Texture1D.\n");
            ID3D10Texture3D_Release(obj->host10_3d);
            break;
    }

    hr = ID3D11Resource_QueryInterface(host, &IID_IDXGISurface, (void **)&surface_iface);
    if (SUCCEEDED(hr))
    {
        *dxgi_surface = QEMU_H2G(surface_iface);
        IDXGISurface_Release(surface_iface);
    }
    else
    {
        *dxgi_surface = 0;
    }

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    ID3D11Resource_SetPrivateDataInterface(host, &IID_d3d11_priv_data, &obj->priv_data_iface);

    *texture = obj;
    return S_OK;
}


#endif
