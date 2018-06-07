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

struct qemu_d3d11_vertex_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_shader *impl_from_ID3D11VertexShader(ID3D11VertexShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D11VertexShader_iface);
}

static inline struct qemu_d3d11_shader *impl_from_ID3D10VertexShader(ID3D10VertexShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D10VertexShader_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_vertex_shader_QueryInterface(ID3D11VertexShader *iface, REFIID riid,
        void **object)
{
    struct qemu_d3d11_vertex_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(riid, &IID_ID3D11VertexShader)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        ID3D11VertexShader_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_ID3D10VertexShader)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        IUnknown_AddRef(&shader->ID3D10VertexShader_iface);
        *object = &shader->ID3D10VertexShader_iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_VERTEX_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_vertex_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_vertex_shader_QueryInterface *c = (struct qemu_d3d11_vertex_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;
    IUnknown *obj;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11VertexShader_QueryInterface(shader->host_vs11, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_vertex_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_vertex_shader_AddRef(ID3D11VertexShader *iface)
{
    struct qemu_d3d11_vertex_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_VERTEX_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_vertex_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_vertex_shader_AddRef *c = (struct qemu_d3d11_vertex_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11VertexShader_AddRef(shader->host_vs11);
}

#endif

struct qemu_d3d11_vertex_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_vertex_shader_Release(ID3D11VertexShader *iface)
{
    struct qemu_d3d11_vertex_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_VERTEX_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_vertex_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_vertex_shader_Release *c = (struct qemu_d3d11_vertex_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11VertexShader_Release(shader->host_vs11);
}

#endif

struct qemu_d3d11_vertex_shader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_vertex_shader_GetDevice(ID3D11VertexShader *iface, ID3D11Device **device)
{
    struct qemu_d3d11_vertex_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_VERTEX_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_vertex_shader_GetDevice(ID3D10VertexShader *iface, ID3D10Device **device)
{
    struct qemu_d3d11_vertex_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_VERTEX_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_vertex_shader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_vertex_shader_GetDevice *c = (struct qemu_d3d11_vertex_shader_GetDevice *)call;
    struct qemu_d3d11_shader *shader;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    ID3D11VertexShader_GetDevice(shader->host_vs11, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_vertex_shader_GetPrivateData(ID3D11VertexShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_vertex_shader_SetPrivateData(ID3D11VertexShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_vertex_shader_SetPrivateDataInterface(ID3D11VertexShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11VertexShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d10_vertex_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_vertex_shader_QueryInterface(ID3D10VertexShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_vertex_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_VERTEX_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_vertex_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_vertex_shader_QueryInterface *c = (struct qemu_d3d10_vertex_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10VertexShader_QueryInterface(shader->host_vs10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_vertex_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_vertex_shader_AddRef(ID3D10VertexShader *iface)
{
    struct qemu_d3d10_vertex_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_VERTEX_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_vertex_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_vertex_shader_AddRef *c = (struct qemu_d3d10_vertex_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10VertexShader_AddRef(shader->host_vs10);
}

#endif

struct qemu_d3d10_vertex_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_vertex_shader_Release(ID3D10VertexShader *iface)
{
    struct qemu_d3d10_vertex_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_VERTEX_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_vertex_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_vertex_shader_Release *c = (struct qemu_d3d10_vertex_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10VertexShader_Release(shader->host_vs10);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_vertex_shader_GetPrivateData(ID3D10VertexShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_vertex_shader_SetPrivateData(ID3D10VertexShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_vertex_shader_SetPrivateDataInterface(ID3D10VertexShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10VertexShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d11_hull_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_shader *impl_from_ID3D11HullShader(ID3D11HullShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D11HullShader_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_hull_shader_QueryInterface(ID3D11HullShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_hull_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_HULL_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_hull_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_hull_shader_QueryInterface *c = (struct qemu_d3d11_hull_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11HullShader_QueryInterface(shader->host_hs11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_hull_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_hull_shader_AddRef(ID3D11HullShader *iface)
{
    struct qemu_d3d11_hull_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_HULL_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_hull_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_hull_shader_AddRef *c = (struct qemu_d3d11_hull_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11HullShader_AddRef(shader->host_hs11);
}

#endif

struct qemu_d3d11_hull_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_hull_shader_Release(ID3D11HullShader *iface)
{
    struct qemu_d3d11_hull_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_HULL_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_hull_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_hull_shader_Release *c = (struct qemu_d3d11_hull_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11HullShader_Release(shader->host_hs11);
}

#endif

struct qemu_d3d11_hull_shader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_hull_shader_GetDevice(ID3D11HullShader *iface, ID3D11Device **device)
{
    struct qemu_d3d11_hull_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_HULL_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_hull_shader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_hull_shader_GetDevice *c = (struct qemu_d3d11_hull_shader_GetDevice *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    ID3D11HullShader_GetDevice(shader->host_hs11, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_hull_shader_GetPrivateData(ID3D11HullShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_hull_shader_SetPrivateData(ID3D11HullShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_hull_shader_SetPrivateDataInterface(ID3D11HullShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11HullShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d11_domain_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_shader *impl_from_ID3D11DomainShader(ID3D11DomainShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D11DomainShader_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_domain_shader_QueryInterface(ID3D11DomainShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_domain_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DOMAIN_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_domain_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_domain_shader_QueryInterface *c = (struct qemu_d3d11_domain_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DomainShader_QueryInterface(shader->host_ds11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_domain_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_domain_shader_AddRef(ID3D11DomainShader *iface)
{
    struct qemu_d3d11_domain_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DOMAIN_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_domain_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_domain_shader_AddRef *c = (struct qemu_d3d11_domain_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DomainShader_AddRef(shader->host_ds11);
}

#endif

struct qemu_d3d11_domain_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_domain_shader_Release(ID3D11DomainShader *iface)
{
    struct qemu_d3d11_domain_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DOMAIN_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_domain_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_domain_shader_Release *c = (struct qemu_d3d11_domain_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DomainShader_Release(shader->host_ds11);
}

#endif

struct qemu_d3d11_domain_shader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_domain_shader_GetDevice(ID3D11DomainShader *iface, ID3D11Device **device)
{
    struct qemu_d3d11_domain_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DOMAIN_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_domain_shader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_domain_shader_GetDevice *c = (struct qemu_d3d11_domain_shader_GetDevice *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    ID3D11DomainShader_GetDevice(shader->host_ds11, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_domain_shader_GetPrivateData(ID3D11DomainShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_domain_shader_SetPrivateData(ID3D11DomainShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_domain_shader_SetPrivateDataInterface(ID3D11DomainShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11DomainShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d11_geometry_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_shader *impl_from_ID3D11GeometryShader(ID3D11GeometryShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D11GeometryShader_iface);
}

static inline struct qemu_d3d11_shader *impl_from_ID3D10GeometryShader(ID3D10GeometryShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D10GeometryShader_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_geometry_shader_QueryInterface(ID3D11GeometryShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_geometry_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(riid, &IID_ID3D11GeometryShader)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        ID3D11GeometryShader_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_ID3D10GeometryShader)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        ID3D10GeometryShader_AddRef(&shader->ID3D10GeometryShader_iface);
        *object = &shader->ID3D10GeometryShader_iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_GEOMETRY_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_geometry_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_geometry_shader_QueryInterface *c = (struct qemu_d3d11_geometry_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;
    IUnknown *obj;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11GeometryShader_QueryInterface(shader->host_gs11, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_geometry_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_geometry_shader_AddRef(ID3D11GeometryShader *iface)
{
    struct qemu_d3d11_geometry_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_GEOMETRY_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_geometry_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_geometry_shader_AddRef *c = (struct qemu_d3d11_geometry_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11GeometryShader_AddRef(shader->host_gs11);
}

#endif

struct qemu_d3d11_geometry_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_geometry_shader_Release(ID3D11GeometryShader *iface)
{
    struct qemu_d3d11_geometry_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_GEOMETRY_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_geometry_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_geometry_shader_Release *c = (struct qemu_d3d11_geometry_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11GeometryShader_Release(shader->host_gs11);
}

#endif

struct qemu_d3d11_geometry_shader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_geometry_shader_GetDevice(ID3D11GeometryShader *iface, ID3D11Device **device)
{
    struct qemu_d3d11_geometry_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_GEOMETRY_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_geometry_shader_GetDevice(ID3D10GeometryShader *iface, ID3D10Device **device)
{
    struct qemu_d3d11_geometry_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_GEOMETRY_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_geometry_shader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_geometry_shader_GetDevice *c = (struct qemu_d3d11_geometry_shader_GetDevice *)call;
    struct qemu_d3d11_shader *shader;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    ID3D11GeometryShader_GetDevice(shader->host_gs11, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_geometry_shader_GetPrivateData(ID3D11GeometryShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_geometry_shader_SetPrivateData(ID3D11GeometryShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_geometry_shader_SetPrivateDataInterface(ID3D11GeometryShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11GeometryShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d10_geometry_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_geometry_shader_QueryInterface(ID3D10GeometryShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_geometry_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_GEOMETRY_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_geometry_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_geometry_shader_QueryInterface *c = (struct qemu_d3d10_geometry_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10GeometryShader_QueryInterface(shader->host_gs10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_geometry_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_geometry_shader_AddRef(ID3D10GeometryShader *iface)
{
    struct qemu_d3d10_geometry_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_GEOMETRY_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_geometry_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_geometry_shader_AddRef *c = (struct qemu_d3d10_geometry_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10GeometryShader_AddRef(shader->host_gs10);
}

#endif

struct qemu_d3d10_geometry_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_geometry_shader_Release(ID3D10GeometryShader *iface)
{
    struct qemu_d3d10_geometry_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_GEOMETRY_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_geometry_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_geometry_shader_Release *c = (struct qemu_d3d10_geometry_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10GeometryShader_Release(shader->host_gs10);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_geometry_shader_GetPrivateData(ID3D10GeometryShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_geometry_shader_SetPrivateData(ID3D10GeometryShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_geometry_shader_SetPrivateDataInterface(ID3D10GeometryShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10GeometryShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d11_pixel_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_shader *impl_from_ID3D11PixelShader(ID3D11PixelShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D11PixelShader_iface);
}

static inline struct qemu_d3d11_shader *impl_from_ID3D10PixelShader(ID3D10PixelShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D10PixelShader_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_pixel_shader_QueryInterface(ID3D11PixelShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_pixel_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(riid, &IID_ID3D11PixelShader)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        ID3D11PixelShader_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_ID3D10PixelShader)
            || IsEqualGUID(riid, &IID_ID3D10DeviceChild))
    {
        IUnknown_AddRef(&shader->ID3D10PixelShader_iface);
        *object = &shader->ID3D10PixelShader_iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_PIXEL_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_pixel_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_pixel_shader_QueryInterface *c = (struct qemu_d3d11_pixel_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;
    IUnknown *obj;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11PixelShader_QueryInterface(shader->host_ps11, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_pixel_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_pixel_shader_AddRef(ID3D11PixelShader *iface)
{
    struct qemu_d3d11_pixel_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_PIXEL_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_pixel_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_pixel_shader_AddRef *c = (struct qemu_d3d11_pixel_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11PixelShader_AddRef(shader->host_ps11);
}

#endif

struct qemu_d3d11_pixel_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_pixel_shader_Release(ID3D11PixelShader *iface)
{
    struct qemu_d3d11_pixel_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_PIXEL_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_pixel_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_pixel_shader_Release *c = (struct qemu_d3d11_pixel_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11PixelShader_Release(shader->host_ps11);
}

#endif

struct qemu_d3d11_pixel_shader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_pixel_shader_GetDevice(ID3D11PixelShader *iface, ID3D11Device **device)
{
    struct qemu_d3d11_pixel_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_PIXEL_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&dev_impl->ID3D11Device2_iface;
}

static void STDMETHODCALLTYPE d3d10_pixel_shader_GetDevice(ID3D10PixelShader *iface, ID3D10Device **device)
{
    struct qemu_d3d11_pixel_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);
    struct qemu_d3d11_device *dev_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_PIXEL_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    dev_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D10Device *)&dev_impl->ID3D10Device1_iface;
}

#else

void qemu_d3d11_pixel_shader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_pixel_shader_GetDevice *c = (struct qemu_d3d11_pixel_shader_GetDevice *)call;
    struct qemu_d3d11_shader *shader;
    ID3D11Device2 *host;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    ID3D11PixelShader_GetDevice(shader->host_ps11, (ID3D11Device **)&host);
    c->device = QEMU_H2G(device_from_host(host));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_pixel_shader_GetPrivateData(ID3D11PixelShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_pixel_shader_SetPrivateData(ID3D11PixelShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_pixel_shader_SetPrivateDataInterface(ID3D11PixelShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11PixelShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d10_pixel_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_pixel_shader_QueryInterface(ID3D10PixelShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_pixel_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_PIXEL_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_pixel_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_pixel_shader_QueryInterface *c = (struct qemu_d3d10_pixel_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10PixelShader_QueryInterface(shader->host_ps10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_pixel_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_pixel_shader_AddRef(ID3D10PixelShader *iface)
{
    struct qemu_d3d10_pixel_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_PIXEL_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_pixel_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_pixel_shader_AddRef *c = (struct qemu_d3d10_pixel_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10PixelShader_AddRef(shader->host_ps10);
}

#endif

struct qemu_d3d10_pixel_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_pixel_shader_Release(ID3D10PixelShader *iface)
{
    struct qemu_d3d10_pixel_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_PIXEL_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_pixel_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_pixel_shader_Release *c = (struct qemu_d3d10_pixel_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D10PixelShader_Release(shader->host_ps10);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_pixel_shader_GetPrivateData(ID3D10PixelShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_pixel_shader_SetPrivateData(ID3D10PixelShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n",
            iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_pixel_shader_SetPrivateDataInterface(ID3D10PixelShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D10PixelShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d11_compute_shader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_shader *impl_from_ID3D11ComputeShader(ID3D11ComputeShader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, ID3D11ComputeShader_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_compute_shader_QueryInterface(ID3D11ComputeShader *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_compute_shader_QueryInterface call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_COMPUTE_SHADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)shader;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_compute_shader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_compute_shader_QueryInterface *c = (struct qemu_d3d11_compute_shader_QueryInterface *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ComputeShader_QueryInterface(shader->host_gs11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_compute_shader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_compute_shader_AddRef(ID3D11ComputeShader *iface)
{
    struct qemu_d3d11_compute_shader_AddRef call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_COMPUTE_SHADER_ADDREF);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_compute_shader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_compute_shader_AddRef *c = (struct qemu_d3d11_compute_shader_AddRef *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ComputeShader_AddRef(shader->host_gs11);
}

#endif

struct qemu_d3d11_compute_shader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_compute_shader_Release(ID3D11ComputeShader *iface)
{
    struct qemu_d3d11_compute_shader_Release call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_COMPUTE_SHADER_RELEASE);
    call.iface = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_compute_shader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_compute_shader_Release *c = (struct qemu_d3d11_compute_shader_Release *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ComputeShader_Release(shader->host_gs11);
}

#endif

struct qemu_d3d11_compute_shader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_compute_shader_GetDevice(ID3D11ComputeShader *iface, ID3D11Device **device)
{
    struct qemu_d3d11_compute_shader_GetDevice call;
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_COMPUTE_SHADER_GETDEVICE);
    call.iface = (ULONG_PTR)shader;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_compute_shader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_compute_shader_GetDevice *c = (struct qemu_d3d11_compute_shader_GetDevice *)call;
    struct qemu_d3d11_shader *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    ID3D11ComputeShader_GetDevice(shader->host_gs11, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_compute_shader_GetPrivateData(ID3D11ComputeShader *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_compute_shader_SetPrivateData(ID3D11ComputeShader *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&shader->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_compute_shader_SetPrivateDataInterface(ID3D11ComputeShader *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_shader *shader = impl_from_ID3D11ComputeShader(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&shader->private_store, guid, data);
}

#endif

struct qemu_d3d11_class_linkage_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_class_linkage *impl_from_ID3D11ClassLinkage(ID3D11ClassLinkage *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_class_linkage, ID3D11ClassLinkage_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_class_linkage_QueryInterface(ID3D11ClassLinkage *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_class_linkage_QueryInterface call;
    struct qemu_d3d11_class_linkage *link = impl_from_ID3D11ClassLinkage(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_CLASS_LINKAGE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)link;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_class_linkage_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_class_linkage_QueryInterface *c = (struct qemu_d3d11_class_linkage_QueryInterface *)call;
    struct qemu_d3d11_class_linkage *link;

    WINE_FIXME("Unverified!\n");
    link = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ClassLinkage_QueryInterface(link->host, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_class_linkage_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_class_linkage_AddRef(ID3D11ClassLinkage *iface)
{
    struct qemu_d3d11_class_linkage_AddRef call;
    struct qemu_d3d11_class_linkage *link = impl_from_ID3D11ClassLinkage(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_CLASS_LINKAGE_ADDREF);
    call.iface = (ULONG_PTR)link;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_class_linkage_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_class_linkage_AddRef *c = (struct qemu_d3d11_class_linkage_AddRef *)call;
    struct qemu_d3d11_class_linkage *link;

    WINE_FIXME("Unverified!\n");
    link = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ClassLinkage_AddRef(link->host);
}

#endif

struct qemu_d3d11_class_linkage_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_class_linkage_Release(ID3D11ClassLinkage *iface)
{
    struct qemu_d3d11_class_linkage_Release call;
    struct qemu_d3d11_class_linkage *link = impl_from_ID3D11ClassLinkage(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_CLASS_LINKAGE_RELEASE);
    call.iface = (ULONG_PTR)link;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_class_linkage_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_class_linkage_Release *c = (struct qemu_d3d11_class_linkage_Release *)call;
    struct qemu_d3d11_class_linkage *link;

    WINE_FIXME("Unverified!\n");
    link = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ClassLinkage_Release(link->host);
}

#endif

struct qemu_d3d11_class_linkage_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_class_linkage_GetDevice(ID3D11ClassLinkage *iface, ID3D11Device **device)
{
    struct qemu_d3d11_class_linkage_GetDevice call;
    struct qemu_d3d11_class_linkage *link = impl_from_ID3D11ClassLinkage(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_CLASS_LINKAGE_GETDEVICE);
    call.iface = (ULONG_PTR)link;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_class_linkage_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_class_linkage_GetDevice *c = (struct qemu_d3d11_class_linkage_GetDevice *)call;
    struct qemu_d3d11_class_linkage *link;

    WINE_FIXME("Unverified!\n");
    link = QEMU_G2H(c->iface);

    ID3D11ClassLinkage_GetDevice(link->host, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_class_linkage_GetPrivateData(ID3D11ClassLinkage *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_class_linkage *class_linkage = impl_from_ID3D11ClassLinkage(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&class_linkage->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_class_linkage_SetPrivateData(ID3D11ClassLinkage *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_class_linkage *class_linkage = impl_from_ID3D11ClassLinkage(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&class_linkage->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_class_linkage_SetPrivateDataInterface(ID3D11ClassLinkage *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_class_linkage *class_linkage = impl_from_ID3D11ClassLinkage(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&class_linkage->private_store, guid, data);
}

#endif

struct qemu_d3d11_class_linkage_GetClassInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t instance_name;
    uint64_t instance_index;
    uint64_t class_instance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_class_linkage_GetClassInstance(ID3D11ClassLinkage *iface, const char *instance_name, UINT instance_index, ID3D11ClassInstance **class_instance)
{
    struct qemu_d3d11_class_linkage_GetClassInstance call;
    struct qemu_d3d11_class_linkage *link = impl_from_ID3D11ClassLinkage(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_CLASS_LINKAGE_GETCLASSINSTANCE);
    call.iface = (ULONG_PTR)link;
    call.instance_name = (ULONG_PTR)instance_name;
    call.instance_index = instance_index;
    call.class_instance = (ULONG_PTR)class_instance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_class_linkage_GetClassInstance(struct qemu_syscall *call)
{
    struct qemu_d3d11_class_linkage_GetClassInstance *c = (struct qemu_d3d11_class_linkage_GetClassInstance *)call;
    struct qemu_d3d11_class_linkage *link;

    WINE_FIXME("Unverified!\n");
    link = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ClassLinkage_GetClassInstance(link->host, QEMU_G2H(c->instance_name), c->instance_index, QEMU_G2H(c->class_instance));
}

#endif

struct qemu_d3d11_class_linkage_CreateClassInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type_name;
    uint64_t cb_offset;
    uint64_t cb_vector_offset;
    uint64_t texture_offset;
    uint64_t sampler_offset;
    uint64_t class_instance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_class_linkage_CreateClassInstance(ID3D11ClassLinkage *iface, const char *type_name, UINT cb_offset, UINT cb_vector_offset, UINT texture_offset, UINT sampler_offset, ID3D11ClassInstance **class_instance)
{
    struct qemu_d3d11_class_linkage_CreateClassInstance call;
    struct qemu_d3d11_class_linkage *link = impl_from_ID3D11ClassLinkage(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_CLASS_LINKAGE_CREATECLASSINSTANCE);
    call.iface = (ULONG_PTR)link;
    call.type_name = (ULONG_PTR)type_name;
    call.cb_offset = cb_offset;
    call.cb_vector_offset = cb_vector_offset;
    call.texture_offset = texture_offset;
    call.sampler_offset = sampler_offset;
    call.class_instance = (ULONG_PTR)class_instance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_class_linkage_CreateClassInstance(struct qemu_syscall *call)
{
    struct qemu_d3d11_class_linkage_CreateClassInstance *c = (struct qemu_d3d11_class_linkage_CreateClassInstance *)call;
    struct qemu_d3d11_class_linkage *link;

    WINE_FIXME("Unverified!\n");
    link = QEMU_G2H(c->iface);

    c->super.iret = ID3D11ClassLinkage_CreateClassInstance(link->host, QEMU_G2H(c->type_name), c->cb_offset, c->cb_vector_offset, c->texture_offset, c->sampler_offset, QEMU_G2H(c->class_instance));
}

#endif

#ifdef QEMU_DLL_GUEST

static struct ID3D11VertexShaderVtbl d3d11_vertex_shader_vtbl =
{
    /* IUnknown methods */
    d3d11_vertex_shader_QueryInterface,
    d3d11_vertex_shader_AddRef,
    d3d11_vertex_shader_Release,
    /* ID3D11DeviceChild methods */
    d3d11_vertex_shader_GetDevice,
    d3d11_vertex_shader_GetPrivateData,
    d3d11_vertex_shader_SetPrivateData,
    d3d11_vertex_shader_SetPrivateDataInterface,
};

static struct ID3D10VertexShaderVtbl d3d10_vertex_shader_vtbl =
{
    /* IUnknown methods */
    d3d10_vertex_shader_QueryInterface,
    d3d10_vertex_shader_AddRef,
    d3d10_vertex_shader_Release,
    /* ID3D10DeviceChild methods */
    d3d10_vertex_shader_GetDevice,
    d3d10_vertex_shader_GetPrivateData,
    d3d10_vertex_shader_SetPrivateData,
    d3d10_vertex_shader_SetPrivateDataInterface,
};

static struct ID3D11HullShaderVtbl d3d11_hull_shader_vtbl =
{
    /* IUnknown methods */
    d3d11_hull_shader_QueryInterface,
    d3d11_hull_shader_AddRef,
    d3d11_hull_shader_Release,
    /* ID3D11DeviceChild methods */
    d3d11_hull_shader_GetDevice,
    d3d11_hull_shader_GetPrivateData,
    d3d11_hull_shader_SetPrivateData,
    d3d11_hull_shader_SetPrivateDataInterface,
};

static struct ID3D11DomainShaderVtbl d3d11_domain_shader_vtbl =
{
    /* IUnknown methods */
    d3d11_domain_shader_QueryInterface,
    d3d11_domain_shader_AddRef,
    d3d11_domain_shader_Release,
    /* ID3D11DeviceChild methods */
    d3d11_domain_shader_GetDevice,
    d3d11_domain_shader_GetPrivateData,
    d3d11_domain_shader_SetPrivateData,
    d3d11_domain_shader_SetPrivateDataInterface,
};

static struct ID3D11GeometryShaderVtbl d3d11_geometry_shader_vtbl =
{
    /* IUnknown methods */
    d3d11_geometry_shader_QueryInterface,
    d3d11_geometry_shader_AddRef,
    d3d11_geometry_shader_Release,
    /* ID3D11DeviceChild methods */
    d3d11_geometry_shader_GetDevice,
    d3d11_geometry_shader_GetPrivateData,
    d3d11_geometry_shader_SetPrivateData,
    d3d11_geometry_shader_SetPrivateDataInterface,
};

static struct ID3D10GeometryShaderVtbl d3d10_geometry_shader_vtbl =
{
    /* IUnknown methods */
    d3d10_geometry_shader_QueryInterface,
    d3d10_geometry_shader_AddRef,
    d3d10_geometry_shader_Release,
    /* ID3D10DeviceChild methods */
    d3d10_geometry_shader_GetDevice,
    d3d10_geometry_shader_GetPrivateData,
    d3d10_geometry_shader_SetPrivateData,
    d3d10_geometry_shader_SetPrivateDataInterface,
};

static struct ID3D11PixelShaderVtbl d3d11_pixel_shader_vtbl =
{
    /* IUnknown methods */
    d3d11_pixel_shader_QueryInterface,
    d3d11_pixel_shader_AddRef,
    d3d11_pixel_shader_Release,
    /* ID3D11DeviceChild methods */
    d3d11_pixel_shader_GetDevice,
    d3d11_pixel_shader_GetPrivateData,
    d3d11_pixel_shader_SetPrivateData,
    d3d11_pixel_shader_SetPrivateDataInterface,
};

static struct ID3D10PixelShaderVtbl d3d10_pixel_shader_vtbl =
{
    /* IUnknown methods */
    d3d10_pixel_shader_QueryInterface,
    d3d10_pixel_shader_AddRef,
    d3d10_pixel_shader_Release,
    /* ID3D10DeviceChild methods */
    d3d10_pixel_shader_GetDevice,
    d3d10_pixel_shader_GetPrivateData,
    d3d10_pixel_shader_SetPrivateData,
    d3d10_pixel_shader_SetPrivateDataInterface,
};

static struct ID3D11ComputeShaderVtbl d3d11_compute_shader_vtbl =
{
    /* IUnknown methods */
    d3d11_compute_shader_QueryInterface,
    d3d11_compute_shader_AddRef,
    d3d11_compute_shader_Release,
    /* ID3D11DeviceChild methods */
    d3d11_compute_shader_GetDevice,
    d3d11_compute_shader_GetPrivateData,
    d3d11_compute_shader_SetPrivateData,
    d3d11_compute_shader_SetPrivateDataInterface,
};

static struct ID3D11ClassLinkageVtbl d3d11_class_linkage_vtbl =
{
    /* IUnknown methods */
    d3d11_class_linkage_QueryInterface,
    d3d11_class_linkage_AddRef,
    d3d11_class_linkage_Release,
    /* ID3D11DeviceChild methods */
    d3d11_class_linkage_GetDevice,
    d3d11_class_linkage_GetPrivateData,
    d3d11_class_linkage_SetPrivateData,
    d3d11_class_linkage_SetPrivateDataInterface,
    /* ID3D11ClassLinkage methods */
    d3d11_class_linkage_GetClassInstance,
    d3d11_class_linkage_CreateClassInstance,
};

void qemu_d3d11_pixel_shader_guest_init(struct qemu_d3d11_shader *shader)
{
    shader->ID3D11PixelShader_iface.lpVtbl = &d3d11_pixel_shader_vtbl;
    shader->ID3D10PixelShader_iface.lpVtbl = &d3d10_pixel_shader_vtbl;
    wined3d_private_store_init(&shader->private_store);
}

void qemu_d3d11_vertex_shader_guest_init(struct qemu_d3d11_shader *shader)
{
    shader->ID3D11VertexShader_iface.lpVtbl = &d3d11_vertex_shader_vtbl;
    shader->ID3D10VertexShader_iface.lpVtbl = &d3d10_vertex_shader_vtbl;
    wined3d_private_store_init(&shader->private_store);
}

void qemu_d3d11_geometry_shader_guest_init(struct qemu_d3d11_shader *shader)
{
    shader->ID3D11GeometryShader_iface.lpVtbl = &d3d11_geometry_shader_vtbl;
    shader->ID3D10GeometryShader_iface.lpVtbl = &d3d10_geometry_shader_vtbl;
    wined3d_private_store_init(&shader->private_store);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D11VertexShader(ID3D11VertexShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_vertex_shader_vtbl);*/

    return impl_from_ID3D11VertexShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D10VertexShader(ID3D10VertexShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_vertex_shader_vtbl);*/

    return impl_from_ID3D10VertexShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D11HullShader(ID3D11HullShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_hull_shader_vtbl);*/

    return impl_from_ID3D11HullShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D11DomainShader(ID3D11DomainShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_domain_shader_vtbl);*/

    return impl_from_ID3D11DomainShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D11GeometryShader(ID3D11GeometryShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_geometry_shader_vtbl);*/

    return impl_from_ID3D11GeometryShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D10GeometryShader(ID3D10GeometryShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_geometry_shader_vtbl);*/

    return impl_from_ID3D10GeometryShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D11PixelShader(ID3D11PixelShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d11_pixel_shader_vtbl);*/

    return impl_from_ID3D11PixelShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D10PixelShader(ID3D10PixelShader *iface)
{
    if (!iface)
        return NULL;
    /*assert(iface->lpVtbl == &d3d10_pixel_shader_vtbl);*/

    return impl_from_ID3D10PixelShader(iface);
}

struct qemu_d3d11_shader *unsafe_impl_from_ID3D11ComputeShader(ID3D11ComputeShader *iface)
{
    if (!iface)
        return NULL;
    /* assert(iface->lpVtbl == &d3d11_compute_shader_vtbl); */

    return impl_from_ID3D11ComputeShader(iface);
}

#else

static inline struct qemu_d3d11_shader *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_shader, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_shader_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_shader_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_d3d11_shader *shader = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&shader->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", shader, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE d3d11_shader_priv_data_Release(IUnknown *iface)
{
    struct qemu_d3d11_shader *shader = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&shader->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", shader, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying shader wrapper %p for host shader %p.\n", shader, shader->host_vs11);
        HeapFree(GetProcessHeap(), 0, shader);
    }

    return refcount;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_shader_priv_data_QueryInterface,
    d3d11_shader_priv_data_AddRef,
    d3d11_shader_priv_data_Release,
};

HRESULT qemu_d3d11_shader_create(ID3D11DeviceChild *host, const IID *d3d10iface, struct qemu_d3d11_shader **shader)
{
    struct qemu_d3d11_shader *obj;
    HRESULT hr;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    obj->host_vs11 = (void *)host;
    if (d3d10iface)
    {
        hr = ID3D11DeviceChild_QueryInterface(host, d3d10iface, (void **)&obj->host_vs10);
        if (FAILED(hr))
            WINE_ERR("Failed to QI %s.\n", wine_dbgstr_guid(d3d10iface));
        IUnknown_Release(obj->host_vs10);
    }

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    ID3D11DeviceChild_SetPrivateDataInterface(host, &IID_d3d11_priv_data, &obj->priv_data_iface);

    *shader = obj;
    return S_OK;
}

#endif
