/*
 * Copyright 2008-2012 Henri Verbeet for CodeWeavers
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

DEFINE_GUID(IID_ID3D11Device2, 0x9d06dffa, 0xd1e5, 0x4d07, 0x83,0xa8, 0x1b,0xb1,0x23,0xf2,0xf8,0x41);
DEFINE_GUID(IID_ID3D11Device1, 0xa04bfb29, 0x08ef, 0x43d6, 0xa4,0x9c, 0xa9,0xbd,0xbd,0xcb,0xe6,0x86);
DEFINE_GUID(IID_ID3D11DeviceContext1, 0xbb2c6faa, 0xb5fb, 0x4082, 0x8e,0x6b, 0x38,0x8b,0x8c,0xfa,0x90,0xe1);

#else

#include <d3d11_2.h>
#include <wine/debug.h>

#endif

#include "thunk/qemu_d3d11.h"

#include "qemudxgi.h"
#include "qemu_d3d11.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

struct qemu_d3d11_immediate_context_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_device_context *impl_from_ID3D11DeviceContext1(ID3D11DeviceContext1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device_context, ID3D11DeviceContext1_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_QueryInterface(ID3D11DeviceContext1 *iface, REFIID riid, void **out)
{
    struct qemu_d3d11_immediate_context_QueryInterface call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (IsEqualGUID(riid, &IID_ID3D11DeviceContext1)
            || IsEqualGUID(riid, &IID_ID3D11DeviceContext)
            || IsEqualGUID(riid, &IID_ID3D11DeviceChild)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        ID3D11DeviceContext_AddRef(iface);
        *out = iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)context;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *out = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_d3d11_immediate_context_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_QueryInterface *c = (struct qemu_d3d11_immediate_context_QueryInterface *)call;
    struct qemu_d3d11_device_context *context;
    IUnknown *obj;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DeviceContext1_QueryInterface(context->host, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_d3d11_immediate_context_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_immediate_context_AddRef(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_AddRef call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_ADDREF);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_AddRef *c = (struct qemu_d3d11_immediate_context_AddRef *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DeviceContext1_AddRef(context->host);
}

#endif

struct qemu_d3d11_immediate_context_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_immediate_context_Release(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_Release call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RELEASE);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Release *c = (struct qemu_d3d11_immediate_context_Release *)call;
    struct qemu_d3d11_device_context *context;

    /* As long as we only support the device-embedded immediate context we don't have to do anything here. */
    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DeviceContext1_Release(context->host);
}

#endif

struct qemu_d3d11_immediate_context_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GetDevice(ID3D11DeviceContext1 *iface, ID3D11Device **device)
{
    struct qemu_d3d11_immediate_context_GetDevice call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_device *device_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GETDEVICE);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    device_impl = (struct qemu_d3d11_device *)(ULONG_PTR)call.device;
    *device = (ID3D11Device *)&device_impl->ID3D11Device2_iface;
}

#else

void qemu_d3d11_immediate_context_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GetDevice *c = (struct qemu_d3d11_immediate_context_GetDevice *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Device *device;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    c->device = QEMU_H2G(CONTAINING_RECORD(context, struct qemu_d3d11_device, immediate_context));

    /* For refcounting. */
    ID3D11DeviceContext1_GetDevice(context->host, &device);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_GetPrivateData(ID3D11DeviceContext1 *iface, REFGUID guid,
        UINT *data_size, void *data)
{
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_get_private_data(&context->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_SetPrivateData(ID3D11DeviceContext1 *iface, REFGUID guid,
        UINT data_size, const void *data)
{
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d_set_private_data(&context->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_SetPrivateDataInterface(ID3D11DeviceContext1 *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d_set_private_data_interface(&context->private_store, guid, data);
}

#endif

struct qemu_d3d11_immediate_context_VSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSSetConstantBuffers(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer *const *buffers)
{
    struct qemu_d3d11_immediate_context_VSSetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_VSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSSetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_VSSetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_VSSetConstantBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d11_immediate_context_PSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSSetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView *const *views)
{
    struct qemu_d3d11_immediate_context_PSSetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_PSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSSetShaderResources *c =
            (struct qemu_d3d11_immediate_context_PSSetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_sr11 : NULL;

    ID3D11DeviceContext1_PSSetShaderResources(context->host, c->start_slot, count, views);
}

#endif

struct qemu_d3d11_immediate_context_PSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSSetShader(ID3D11DeviceContext1 *iface,
        ID3D11PixelShader *shader, ID3D11ClassInstance *const *class_instances, UINT class_instance_count)
{
    struct qemu_d3d11_immediate_context_PSSetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *shader_impl = unsafe_impl_from_ID3D11PixelShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSSETSHADER);
    call.iface = (ULONG_PTR)context;
    call.shader = (ULONG_PTR)shader_impl;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = class_instance_count;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_PSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSSetShader *c = (struct qemu_d3d11_immediate_context_PSSetShader *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported.\n");

    ID3D11DeviceContext1_PSSetShader(context->host, shader ? shader->host_ps11 : NULL,
            QEMU_G2H(c->class_instances), c->class_instance_count);
}

#endif

struct qemu_d3d11_immediate_context_PSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSSetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState *const *samplers)
{
    struct qemu_d3d11_immediate_context_PSSetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSSETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_PSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSSetSamplers *c = (struct qemu_d3d11_immediate_context_PSSetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss11 : NULL;

    ID3D11DeviceContext1_PSSetSamplers(context->host, c->start_slot, c->sampler_count, ifaces);
}

#endif

struct qemu_d3d11_immediate_context_VSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSSetShader(ID3D11DeviceContext1 *iface,
        ID3D11VertexShader *shader, ID3D11ClassInstance *const *class_instances, UINT class_instance_count)
{
    struct qemu_d3d11_immediate_context_VSSetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *shader_impl = unsafe_impl_from_ID3D11VertexShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSSETSHADER);
    call.iface = (ULONG_PTR)context;
    call.shader = (ULONG_PTR)shader_impl;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = class_instance_count;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_VSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSSetShader *c = (struct qemu_d3d11_immediate_context_VSSetShader *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported.\n");

    ID3D11DeviceContext1_VSSetShader(context->host, shader ? shader->host_vs11 : NULL, QEMU_G2H(c->class_instances),
            c->class_instance_count);
}

#endif

struct qemu_d3d11_immediate_context_DrawIndexed
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index_count;
    uint64_t start_index_location;
    uint64_t base_vertex_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DrawIndexed(ID3D11DeviceContext1 *iface, UINT index_count,
        UINT start_index_location, INT base_vertex_location)
{
    struct qemu_d3d11_immediate_context_DrawIndexed call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINDEXED);
    call.iface = (ULONG_PTR)context;
    call.index_count = index_count;
    call.start_index_location = start_index_location;
    call.base_vertex_location = base_vertex_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DrawIndexed(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DrawIndexed *c = (struct qemu_d3d11_immediate_context_DrawIndexed *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DrawIndexed(context->host, c->index_count, c->start_index_location, c->base_vertex_location);
}

#endif

struct qemu_d3d11_immediate_context_Draw
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vertex_count;
    uint64_t start_vertex_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_Draw(ID3D11DeviceContext1 *iface, UINT vertex_count,
        UINT start_vertex_location)
{
    struct qemu_d3d11_immediate_context_Draw call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAW);
    call.iface = (ULONG_PTR)context;
    call.vertex_count = vertex_count;
    call.start_vertex_location = start_vertex_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_Draw(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Draw *c = (struct qemu_d3d11_immediate_context_Draw *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_Draw(context->host, c->vertex_count, c->start_vertex_location);
}

#endif

struct qemu_d3d11_immediate_context_Map
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t subresource_idx;
    uint64_t map_type;
    uint64_t map_flags;
    uint64_t mapped_subresource;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_Map(ID3D11DeviceContext1 *iface, ID3D11Resource *resource,
        UINT subresource_idx, D3D11_MAP map_type, UINT map_flags, D3D11_MAPPED_SUBRESOURCE *mapped_subresource)
{
    struct qemu_d3d11_immediate_context_Map call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_MAP);
    call.iface = (ULONG_PTR)context;
    call.subresource_idx = subresource_idx;
    call.map_type = map_type;
    call.map_flags = map_flags;
    call.mapped_subresource = (ULONG_PTR)mapped_subresource;

    ID3D11Resource_GetType(resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)resource);
            call.texture = 0;
            break;
    }

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_Map(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Map *c = (struct qemu_d3d11_immediate_context_Map *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *resource;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;
    D3D11_MAPPED_SUBRESOURCE stack, *mapped_subresource = &stack;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->buffer)
    {
        buf = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buf->host11;
    }
    else if (c->texture)
    {
        tex = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)tex->host11_1d;
    }
#if GUEST_BIT == HOST_BIT
    mapped_subresource = QEMU_G2H(c->mapped_subresource);
#endif

    c->super.iret = ID3D11DeviceContext1_Map(context->host, resource, c->subresource_idx, c->map_type,
            c->map_flags, mapped_subresource);

#if GUEST_BIT != HOST_BIT
    D3D11_MAPPED_SUBRESOURCE_h2g(QEMU_G2H(c->mapped_subresource), mapped_subresource);
#endif
}

#endif

struct qemu_d3d11_immediate_context_Unmap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer, texture;
    uint64_t subresource_idx;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_Unmap(ID3D11DeviceContext1 *iface, ID3D11Resource *resource,
        UINT subresource_idx)
{
    struct qemu_d3d11_immediate_context_Unmap call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_UNMAP);
    call.iface = (ULONG_PTR)context;
    call.subresource_idx = subresource_idx;

    ID3D11Resource_GetType(resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)resource);
            call.texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_Unmap(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Unmap *c = (struct qemu_d3d11_immediate_context_Unmap *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *resource;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->buffer)
    {
        buf = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buf->host11;
    }
    else if (c->texture)
    {
        tex = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)tex->host11_1d;
    }

    ID3D11DeviceContext1_Unmap(context->host, resource, c->subresource_idx);
}

#endif

struct qemu_d3d11_immediate_context_PSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSSetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer *const *buffers)
{
    struct qemu_d3d11_immediate_context_PSSetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_PSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSSetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_PSSetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_PSSetConstantBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d11_immediate_context_IASetInputLayout
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t input_layout;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IASetInputLayout(ID3D11DeviceContext1 *iface,
        ID3D11InputLayout *input_layout)
{
    struct qemu_d3d11_immediate_context_IASetInputLayout call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_input_layout *layout = unsafe_impl_from_ID3D11InputLayout(input_layout);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IASETINPUTLAYOUT);
    call.iface = (ULONG_PTR)context;
    call.input_layout = (ULONG_PTR)layout;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_IASetInputLayout(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IASetInputLayout *c = (struct qemu_d3d11_immediate_context_IASetInputLayout *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_input_layout *layout;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    layout = QEMU_G2H(c->input_layout);

    ID3D11DeviceContext1_IASetInputLayout(context->host, layout ? layout->host11 : NULL);
}

#endif

struct qemu_d3d11_immediate_context_IASetVertexBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t strides;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IASetVertexBuffers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT buffer_count, ID3D11Buffer *const *buffers, const UINT *strides, const UINT *offsets)
{
    struct qemu_d3d11_immediate_context_IASetVertexBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[MAX_STREAMS], *buffer_impl = stack;
    UINT i;

    if (buffer_count > MAX_STREAMS)
        buffer_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*buffer_impl) * buffer_count);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IASETVERTEXBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.strides = (ULONG_PTR)strides;
    call.offsets = (ULONG_PTR)offsets;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);

    if (buffer_impl != stack)
        HeapFree(GetProcessHeap(), 0, buffer_impl);
}

#else

void qemu_d3d11_immediate_context_IASetVertexBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IASetVertexBuffers *c =
            (struct qemu_d3d11_immediate_context_IASetVertexBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **buffer_iface;
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    buffer_iface = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_IASetVertexBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface,
            QEMU_G2H(c->strides), QEMU_G2H(c->offsets));
}

#endif

struct qemu_d3d11_immediate_context_IASetIndexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t format;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IASetIndexBuffer(ID3D11DeviceContext1 *iface,
        ID3D11Buffer *buffer, DXGI_FORMAT format, UINT offset)
{
    struct qemu_d3d11_immediate_context_IASetIndexBuffer call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_buffer *buffer_impl = unsafe_impl_from_ID3D11Buffer(buffer);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IASETINDEXBUFFER);
    call.iface = (ULONG_PTR)context;
    call.buffer = (ULONG_PTR)buffer_impl;
    call.format = format;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_IASetIndexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IASetIndexBuffer *c =
            (struct qemu_d3d11_immediate_context_IASetIndexBuffer *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    ID3D11DeviceContext1_IASetIndexBuffer(context->host, buffer ? buffer->host11 : NULL, c->format, c->offset);
}

#endif

struct qemu_d3d11_immediate_context_DrawIndexedInstanced
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t instance_index_count;
    uint64_t instance_count;
    uint64_t start_index_location;
    uint64_t base_vertex_location;
    uint64_t start_instance_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DrawIndexedInstanced(ID3D11DeviceContext1 *iface, UINT instance_index_count, UINT instance_count, UINT start_index_location, INT base_vertex_location, UINT start_instance_location)
{
    struct qemu_d3d11_immediate_context_DrawIndexedInstanced call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINDEXEDINSTANCED);
    call.iface = (ULONG_PTR)context;
    call.instance_index_count = instance_index_count;
    call.instance_count = instance_count;
    call.start_index_location = start_index_location;
    call.base_vertex_location = base_vertex_location;
    call.start_instance_location = start_instance_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DrawIndexedInstanced(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DrawIndexedInstanced *c = (struct qemu_d3d11_immediate_context_DrawIndexedInstanced *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DrawIndexedInstanced(context->host, c->instance_index_count, c->instance_count, c->start_index_location, c->base_vertex_location, c->start_instance_location);
}

#endif

struct qemu_d3d11_immediate_context_DrawInstanced
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t instance_vertex_count;
    uint64_t instance_count;
    uint64_t start_vertex_location;
    uint64_t start_instance_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DrawInstanced(ID3D11DeviceContext1 *iface,
        UINT instance_vertex_count, UINT instance_count, UINT start_vertex_location,
        UINT start_instance_location)
{
    struct qemu_d3d11_immediate_context_DrawInstanced call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINSTANCED);
    call.iface = (ULONG_PTR)context;
    call.instance_vertex_count = instance_vertex_count;
    call.instance_count = instance_count;
    call.start_vertex_location = start_vertex_location;
    call.start_instance_location = start_instance_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DrawInstanced(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DrawInstanced *c = (struct qemu_d3d11_immediate_context_DrawInstanced *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DrawInstanced(context->host, c->instance_vertex_count, c->instance_count,
            c->start_vertex_location, c->start_instance_location);
}

#endif

struct qemu_d3d11_immediate_context_GSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSSetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer *const *buffers)
{
    struct qemu_d3d11_immediate_context_GSSetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_GSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSSetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_GSSetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_GSSetConstantBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d11_immediate_context_GSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSSetShader(ID3D11DeviceContext1 *iface,
        ID3D11GeometryShader *shader, ID3D11ClassInstance *const *class_instances, UINT class_instance_count)
{
    struct qemu_d3d11_immediate_context_GSSetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *shader_impl = unsafe_impl_from_ID3D11GeometryShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSSETSHADER);
    call.iface = (ULONG_PTR)context;
    call.shader = (ULONG_PTR)shader_impl;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = class_instance_count;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_GSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSSetShader *c = (struct qemu_d3d11_immediate_context_GSSetShader *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not handled yet.\n");

    ID3D11DeviceContext1_GSSetShader(context->host, shader ? shader->host_gs11 : NULL,
            QEMU_G2H(c->class_instances), c->class_instance_count);
}

#endif

struct qemu_d3d11_immediate_context_IASetPrimitiveTopology
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t topology;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IASetPrimitiveTopology(ID3D11DeviceContext1 *iface,
        D3D11_PRIMITIVE_TOPOLOGY topology)
{
    struct qemu_d3d11_immediate_context_IASetPrimitiveTopology call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IASETPRIMITIVETOPOLOGY);
    call.iface = (ULONG_PTR)context;
    call.topology = topology;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_IASetPrimitiveTopology(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IASetPrimitiveTopology *c = (struct qemu_d3d11_immediate_context_IASetPrimitiveTopology *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_IASetPrimitiveTopology(context->host, c->topology);
}

#endif

struct qemu_d3d11_immediate_context_VSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSSetShaderResources(ID3D11DeviceContext1 *iface, UINT start_slot, UINT view_count, ID3D11ShaderResourceView *const *views)
{
    struct qemu_d3d11_immediate_context_VSSetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_VSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSSetShaderResources *c = (struct qemu_d3d11_immediate_context_VSSetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_sr11 : NULL;

    ID3D11DeviceContext1_VSSetShaderResources(context->host, c->start_slot, count, views);
}

#endif

struct qemu_d3d11_immediate_context_VSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSSetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState *const *samplers)
{
    struct qemu_d3d11_immediate_context_VSSetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSSETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_VSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSSetSamplers *c = (struct qemu_d3d11_immediate_context_VSSetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss11 : NULL;

    ID3D11DeviceContext1_VSSetSamplers(context->host, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d11_immediate_context_Begin
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t asynchronous;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_Begin(ID3D11DeviceContext1 *iface, ID3D11Asynchronous *asynchronous)
{
    struct qemu_d3d11_immediate_context_Begin call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_query *query = unsafe_impl_from_ID3D11Asynchronous(asynchronous);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_BEGIN);
    call.iface = (ULONG_PTR)context;
    call.asynchronous = (ULONG_PTR)query;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_Begin(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Begin *c = (struct qemu_d3d11_immediate_context_Begin *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    query = QEMU_G2H(c->asynchronous);

    ID3D11DeviceContext1_Begin(context->host, query ? (ID3D11Asynchronous *)query->host11 : NULL);
}

#endif

struct qemu_d3d11_immediate_context_End
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t asynchronous;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_End(ID3D11DeviceContext1 *iface, ID3D11Asynchronous *asynchronous)
{
    struct qemu_d3d11_immediate_context_End call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_query *query = unsafe_impl_from_ID3D11Asynchronous(asynchronous);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_END);
    call.iface = (ULONG_PTR)context;
    call.asynchronous = (ULONG_PTR)query;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_End(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_End *c = (struct qemu_d3d11_immediate_context_End *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    query = QEMU_G2H(c->asynchronous);

    ID3D11DeviceContext1_End(context->host, query ? (ID3D11Asynchronous *)query->host11 : NULL);
}

#endif

struct qemu_d3d11_immediate_context_GetData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t asynchronous;
    uint64_t data;
    uint64_t data_size;
    uint64_t data_flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_GetData(ID3D11DeviceContext1 *iface,
        ID3D11Asynchronous *asynchronous, void *data, UINT data_size, UINT data_flags)
{
    struct qemu_d3d11_immediate_context_GetData call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_query *query = unsafe_impl_from_ID3D11Asynchronous(asynchronous);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GETDATA);
    call.iface = (ULONG_PTR)context;
    call.asynchronous = (ULONG_PTR)query;
    call.data = (ULONG_PTR)data;
    call.data_size = data_size;
    call.data_flags = data_flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_GetData(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GetData *c = (struct qemu_d3d11_immediate_context_GetData *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    query = QEMU_G2H(c->asynchronous);

    c->super.iret = ID3D11DeviceContext1_GetData(context->host, query ? (ID3D11Asynchronous *)query->host11 : NULL,
            QEMU_G2H(c->data), c->data_size, c->data_flags);
}

#endif

struct qemu_d3d11_immediate_context_SetPredication
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t predicate;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_SetPredication(ID3D11DeviceContext1 *iface,
        ID3D11Predicate *predicate, BOOL value)
{
    struct qemu_d3d11_immediate_context_SetPredication call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_query *query = unsafe_impl_from_ID3D11Query((ID3D11Query *)predicate);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_SETPREDICATION);
    call.iface = (ULONG_PTR)context;
    call.predicate = (ULONG_PTR)query;
    call.value = value;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_SetPredication(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_SetPredication *c = (struct qemu_d3d11_immediate_context_SetPredication *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    query = QEMU_G2H(c->predicate);

    ID3D11DeviceContext1_SetPredication(context->host, query ? (ID3D11Predicate *)query->host11 : NULL, c->value);
}

#endif

struct qemu_d3d11_immediate_context_GSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSSetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView *const *views)
{
    struct qemu_d3d11_immediate_context_GSSetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_GSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSSetShaderResources *c =
            (struct qemu_d3d11_immediate_context_GSSetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_sr11 : NULL;

    ID3D11DeviceContext1_GSSetShaderResources(context->host, c->start_slot, count, views);
}

#endif

struct qemu_d3d11_immediate_context_GSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSSetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState *const *samplers)
{
    struct qemu_d3d11_immediate_context_GSSetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSSETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_GSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSSetSamplers *c = (struct qemu_d3d11_immediate_context_GSSetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss11 : NULL;

    ID3D11DeviceContext1_GSSetSamplers(context->host, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d11_immediate_context_OMSetRenderTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view_count;
    uint64_t render_target_views;
    uint64_t depth_stencil_view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMSetRenderTargets(ID3D11DeviceContext1 *iface,
        UINT render_target_view_count, ID3D11RenderTargetView *const *render_target_views,
        ID3D11DepthStencilView *depth_stencil_view)
{
    struct qemu_d3d11_immediate_context_OMSetRenderTargets call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *ds_view = unsafe_impl_from_ID3D11DepthStencilView(depth_stencil_view);
    uint64_t rt_views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    UINT i;

    for (i = 0; i < render_target_view_count; ++i)
        rt_views[i] = (ULONG_PTR)unsafe_impl_from_ID3D11RenderTargetView(render_target_views[i]);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMSETRENDERTARGETS);
    call.iface = (ULONG_PTR)context;
    call.render_target_view_count = render_target_view_count;
    call.render_target_views = (ULONG_PTR)rt_views;
    call.depth_stencil_view = (ULONG_PTR)ds_view;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_OMSetRenderTargets(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMSetRenderTargets *c =
            (struct qemu_d3d11_immediate_context_OMSetRenderTargets *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *ds_view;
    struct qemu_d3d11_view **rt_views;
    ID3D11RenderTargetView *view_ifaces[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    UINT i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ds_view = QEMU_G2H(c->depth_stencil_view);
    rt_views = QEMU_G2H(c->render_target_views);

    for (i = 0; i < c->render_target_view_count; ++i)
        view_ifaces[i] = rt_views[i] ? rt_views[i]->host_rt11 : NULL;

    ID3D11DeviceContext1_OMSetRenderTargets(context->host, c->render_target_view_count, view_ifaces,
            ds_view ? ds_view->host_ds11 : NULL);
}

#endif

struct qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view_count;
    uint64_t render_target_views;
    uint64_t depth_stencil_view;
    uint64_t unordered_access_view_start_slot;
    uint64_t unordered_access_view_count;
    uint64_t unordered_access_views;
    uint64_t initial_counts;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews(
        ID3D11DeviceContext1 *iface, UINT render_target_view_count, ID3D11RenderTargetView *const *render_target_views,
        ID3D11DepthStencilView *depth_stencil_view, UINT unordered_access_view_start_slot,
        UINT unordered_access_view_count, ID3D11UnorderedAccessView *const *unordered_access_views,
        const UINT *initial_counts)
{
    struct qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *ds_impl = unsafe_impl_from_ID3D11DepthStencilView(depth_stencil_view);
    uint64_t uav_stack[16], *uav = uav_stack;
    uint64_t rt_stack[16], *rt = rt_stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMSETRENDERTARGETSANDUNORDEREDACCESSVIEWS);
    call.iface = (ULONG_PTR)context;
    call.render_target_view_count = render_target_view_count;
    call.depth_stencil_view = (ULONG_PTR)ds_impl;
    call.unordered_access_view_start_slot = unordered_access_view_start_slot;
    call.unordered_access_view_count = unordered_access_view_count;
    call.initial_counts = (ULONG_PTR)initial_counts;

    if (unordered_access_views)
    {
        if (unordered_access_view_count > (sizeof(uav_stack) / sizeof(*uav_stack)))
            uav = HeapAlloc(GetProcessHeap(), 0, sizeof(*uav) * unordered_access_view_count);

        for (i = 0; i < unordered_access_view_count; ++i)
            uav[i] = (ULONG_PTR)unsafe_impl_from_ID3D11UnorderedAccessView(unordered_access_views[i]);

        call.unordered_access_views = (ULONG_PTR)uav;
    }
    else
    {
        call.unordered_access_views = 0;
    }

    if (render_target_views)
    {
        if (render_target_view_count > (sizeof(rt_stack) / sizeof(*rt_stack)))
            rt = HeapAlloc(GetProcessHeap(), 0, sizeof(*rt) * render_target_view_count);

        for (i = 0; i < render_target_view_count; ++i)
            rt[i] = (ULONG_PTR)unsafe_impl_from_ID3D11RenderTargetView(render_target_views[i]);

        call.render_target_views = (ULONG_PTR)rt;
    }
    else
    {
        call.render_target_views = 0;
    }

    qemu_syscall(&call.super);

    if (uav != uav_stack)
        HeapFree(GetProcessHeap(), 0, uav);
    if (rt != rt_stack)
        HeapFree(GetProcessHeap(), 0, rt);
}

#else

void qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews *c =
            (struct qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *ds_impl;
    ID3D11UnorderedAccessView **uav = NULL;
    ID3D11RenderTargetView **rt = NULL;
    struct qemu_d3d11_view **impls;
    UINT i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ds_impl = QEMU_G2H(c->depth_stencil_view);

    if (c->render_target_views)
    {
        rt = QEMU_G2H(c->render_target_views);
        impls = QEMU_G2H(c->render_target_views);
        for (i = 0; i < c->render_target_view_count; ++i)
            rt[i] = impls[i] ? impls[i]->host_rt11 : NULL;
    }

    if (c->unordered_access_views)
    {
        uav = QEMU_G2H(c->unordered_access_views);
        impls = QEMU_G2H(c->unordered_access_views);
        for (i = 0; i < c->unordered_access_view_count; ++i)
            uav[i] = impls[i] ? impls[i]->host_uav : NULL;
    }

    ID3D11DeviceContext1_OMSetRenderTargetsAndUnorderedAccessViews(context->host,
            c->render_target_view_count, rt, ds_impl ? ds_impl->host_ds11 : NULL,
            c->unordered_access_view_start_slot, c->unordered_access_view_count, uav,
            QEMU_G2H(c->initial_counts));
}

#endif

struct qemu_d3d11_immediate_context_OMSetBlendState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t blend_state;
    uint64_t blend_factor;
    uint64_t sample_mask;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMSetBlendState(ID3D11DeviceContext1 *iface,
        ID3D11BlendState *blend_state, const float blend_factor[4], UINT sample_mask)
{
    struct qemu_d3d11_immediate_context_OMSetBlendState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_state *state = unsafe_impl_from_ID3D11BlendState(blend_state);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMSETBLENDSTATE);
    call.iface = (ULONG_PTR)context;
    call.blend_state = (ULONG_PTR)state;
    call.blend_factor = (ULONG_PTR)blend_factor;
    call.sample_mask = sample_mask;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_OMSetBlendState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMSetBlendState *c = (struct qemu_d3d11_immediate_context_OMSetBlendState *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_state *state;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    state = QEMU_G2H(c->blend_state);

    ID3D11DeviceContext1_OMSetBlendState(context->host, state ? state->host_bs11 : NULL,
            QEMU_G2H(c->blend_factor), c->sample_mask);
}

#endif

struct qemu_d3d11_immediate_context_OMSetDepthStencilState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil_state;
    uint64_t stencil_ref;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMSetDepthStencilState(ID3D11DeviceContext1 *iface,
        ID3D11DepthStencilState *depth_stencil_state, UINT stencil_ref)
{
    struct qemu_d3d11_immediate_context_OMSetDepthStencilState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_state *state = unsafe_impl_from_ID3D11DepthStencilState(depth_stencil_state);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMSETDEPTHSTENCILSTATE);
    call.iface = (ULONG_PTR)context;
    call.depth_stencil_state = (ULONG_PTR)state;
    call.stencil_ref = stencil_ref;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_OMSetDepthStencilState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMSetDepthStencilState *c = (struct qemu_d3d11_immediate_context_OMSetDepthStencilState *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_state *state;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    state = QEMU_G2H(c->depth_stencil_state);

    ID3D11DeviceContext1_OMSetDepthStencilState(context->host, state ? state->host_ds11 : NULL, c->stencil_ref);
}

#endif

struct qemu_d3d11_immediate_context_SOSetTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_SOSetTargets(ID3D11DeviceContext1 *iface, UINT buffer_count,
        ID3D11Buffer *const *buffers, const UINT *offsets)
{
    struct qemu_d3d11_immediate_context_SOSetTargets call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_SOSETTARGETS);
    call.iface = (ULONG_PTR)context;
    call.buffer_count = buffer_count;
    call.offsets = (ULONG_PTR)offsets;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    for (i = 0; i < buffer_count; ++i)
        impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_SOSetTargets(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_SOSetTargets *c = (struct qemu_d3d11_immediate_context_SOSetTargets *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **buffers;
    struct qemu_d3d11_buffer **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffers = QEMU_G2H(c->buffers);
    impls = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    for (i = 0; i < count; ++i)
        buffers[i] = impls[i] ? impls[i]->host11 : NULL;

    ID3D11DeviceContext1_SOSetTargets(context->host, count, buffers, QEMU_G2H(c->offsets));
}

#endif

struct qemu_d3d11_immediate_context_DrawAuto
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DrawAuto(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_DrawAuto call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAWAUTO);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DrawAuto(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DrawAuto *c = (struct qemu_d3d11_immediate_context_DrawAuto *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DrawAuto(context->host);
}

#endif

struct qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DrawIndexedInstancedIndirect(ID3D11DeviceContext1 *iface,
        ID3D11Buffer *buffer, UINT offset)
{
    struct qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_buffer *impl = unsafe_impl_from_ID3D11Buffer(buffer);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINDEXEDINSTANCEDINDIRECT);
    call.iface = (ULONG_PTR)context;
    call.buffer = (ULONG_PTR)impl;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect *c =
            (struct qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    ID3D11DeviceContext1_DrawIndexedInstancedIndirect(context->host, buffer ? buffer->host11 : NULL, c->offset);
}

#endif

struct qemu_d3d11_immediate_context_DrawInstancedIndirect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DrawInstancedIndirect(ID3D11DeviceContext1 *iface,
        ID3D11Buffer *buffer, UINT offset)
{
    struct qemu_d3d11_immediate_context_DrawInstancedIndirect call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_buffer *buffer_impl = unsafe_impl_from_ID3D11Buffer(buffer);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DRAWINSTANCEDINDIRECT);
    call.iface = (ULONG_PTR)context;
    call.buffer = (ULONG_PTR)buffer_impl;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DrawInstancedIndirect(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DrawInstancedIndirect *c =
            (struct qemu_d3d11_immediate_context_DrawInstancedIndirect *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    ID3D11DeviceContext1_DrawInstancedIndirect(context->host, buffer ? buffer->host11 : NULL, c->offset);
}

#endif

struct qemu_d3d11_immediate_context_Dispatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t thread_group_count_x;
    uint64_t thread_group_count_y;
    uint64_t thread_group_count_z;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_Dispatch(ID3D11DeviceContext1 *iface, UINT thread_group_count_x,
        UINT thread_group_count_y, UINT thread_group_count_z)
{
    struct qemu_d3d11_immediate_context_Dispatch call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DISPATCH);
    call.iface = (ULONG_PTR)context;
    call.thread_group_count_x = thread_group_count_x;
    call.thread_group_count_y = thread_group_count_y;
    call.thread_group_count_z = thread_group_count_z;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_Dispatch(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Dispatch *c = (struct qemu_d3d11_immediate_context_Dispatch *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_Dispatch(context->host, c->thread_group_count_x, c->thread_group_count_y,
            c->thread_group_count_z);
}

#endif

struct qemu_d3d11_immediate_context_DispatchIndirect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DispatchIndirect(ID3D11DeviceContext1 *iface,
        ID3D11Buffer *buffer, UINT offset)
{
    struct qemu_d3d11_immediate_context_DispatchIndirect call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_buffer *impl = unsafe_impl_from_ID3D11Buffer(buffer);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DISPATCHINDIRECT);
    call.iface = (ULONG_PTR)context;
    call.buffer = (ULONG_PTR)impl;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DispatchIndirect(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DispatchIndirect *c = (struct qemu_d3d11_immediate_context_DispatchIndirect *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    ID3D11DeviceContext1_DispatchIndirect(context->host, buffer ? buffer->host11 : NULL, c->offset);
}

#endif

struct qemu_d3d11_immediate_context_RSSetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rasterizer_state;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_RSSetState(ID3D11DeviceContext1 *iface,
        ID3D11RasterizerState *rasterizer_state)
{
    struct qemu_d3d11_immediate_context_RSSetState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_state *state = unsafe_impl_from_ID3D11RasterizerState(rasterizer_state);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RSSETSTATE);
    call.iface = (ULONG_PTR)context;
    call.rasterizer_state = (ULONG_PTR)state;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_RSSetState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_RSSetState *c = (struct qemu_d3d11_immediate_context_RSSetState *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_state *state;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    state = QEMU_G2H(c->rasterizer_state);

    ID3D11DeviceContext1_RSSetState(context->host, state ? state->host_rs11 : NULL);
}

#endif

struct qemu_d3d11_immediate_context_RSSetViewports
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport_count;
    uint64_t viewports;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_RSSetViewports(ID3D11DeviceContext1 *iface, UINT viewport_count,
        const D3D11_VIEWPORT *viewports)
{
    struct qemu_d3d11_immediate_context_RSSetViewports call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RSSETVIEWPORTS);
    call.iface = (ULONG_PTR)context;
    call.viewport_count = viewport_count;
    call.viewports = (ULONG_PTR)viewports;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_RSSetViewports(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_RSSetViewports *c = (struct qemu_d3d11_immediate_context_RSSetViewports *)call;
    struct qemu_d3d11_device_context *context;
    D3D11_VIEWPORT stack[16], *viewports = stack;

    /* D3D11_VIEWPORT has the same size in 32 and 64 bit and the input array is not an array of pointers. */
    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_RSSetViewports(context->host, c->viewport_count, QEMU_G2H(c->viewports));
}

#endif

struct qemu_d3d11_immediate_context_RSSetScissorRects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_RSSetScissorRects(ID3D11DeviceContext1 *iface, UINT rect_count,
        const D3D11_RECT *rects)
{
    struct qemu_d3d11_immediate_context_RSSetScissorRects call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RSSETSCISSORRECTS);
    call.iface = (ULONG_PTR)context;
    call.rect_count = rect_count;
    call.rects = (ULONG_PTR)rects;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_RSSetScissorRects(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_RSSetScissorRects *c =
            (struct qemu_d3d11_immediate_context_RSSetScissorRects *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_RSSetScissorRects(context->host, c->rect_count, QEMU_G2H(c->rects));
}

#endif

struct qemu_d3d11_immediate_context_CopySubresourceRegion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_texture;
    uint64_t dst_buffer;
    uint64_t dst_subresource_idx;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t dst_z;
    uint64_t src_texture;
    uint64_t src_buffer;
    uint64_t src_subresource_idx;
    uint64_t src_box;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CopySubresourceRegion(ID3D11DeviceContext1 *iface,
        ID3D11Resource *dst_resource, UINT dst_subresource_idx, UINT dst_x, UINT dst_y, UINT dst_z,
        ID3D11Resource *src_resource, UINT src_subresource_idx, const D3D11_BOX *src_box)
{
    struct qemu_d3d11_immediate_context_CopySubresourceRegion call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_COPYSUBRESOURCEREGION);
    call.iface = (ULONG_PTR)context;
    call.dst_subresource_idx = dst_subresource_idx;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.dst_z = dst_z;
    call.src_subresource_idx = src_subresource_idx;
    call.src_box = (ULONG_PTR)src_box;

    if (!dst_resource)
    {
        call.dst_buffer = call.dst_texture = 0;
    }
    else
    {
        ID3D11Resource_GetType(dst_resource, &dim);
        switch (dim)
        {
            case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
                call.dst_buffer = 0;
                call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)dst_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
                call.dst_buffer = 0;
                call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)dst_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
                call.dst_buffer = 0;
                call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)dst_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_BUFFER:
                call.dst_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)dst_resource);
                call.dst_texture = 0;
                break;
        }
    }

    if (!src_resource)
    {
        call.src_buffer = call.src_texture = 0;
    }
    else
    {
        ID3D11Resource_GetType(src_resource, &dim);
        switch (dim)
        {
            case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
                call.src_buffer = 0;
                call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)src_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
                call.src_buffer = 0;
                call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)src_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
                call.src_buffer = 0;
                call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)src_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_BUFFER:
                call.src_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)src_resource);
                call.src_texture = 0;
                break;
        }
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CopySubresourceRegion(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CopySubresourceRegion *c =
            (struct qemu_d3d11_immediate_context_CopySubresourceRegion *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *src = NULL, *dst = NULL;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    if (c->src_buffer)
    {
        buf = QEMU_G2H(c->src_buffer);
        src = (ID3D11Resource *)buf->host11;
    }
    else if (c->src_texture)
    {
        tex = QEMU_G2H(c->src_texture);
        src = (ID3D11Resource *)tex->host11_1d;
    }

    if (c->dst_buffer)
    {
        buf = QEMU_G2H(c->dst_buffer);
        dst = (ID3D11Resource *)buf->host11;
    }
    else if (c->dst_texture)
    {
        tex = QEMU_G2H(c->dst_texture);
        dst = (ID3D11Resource *)tex->host11_1d;
    }

    ID3D11DeviceContext1_CopySubresourceRegion(context->host, dst, c->dst_subresource_idx,
            c->dst_x, c->dst_y, c->dst_z, src, c->src_subresource_idx, QEMU_G2H(c->src_box));
}

#endif

struct qemu_d3d11_immediate_context_CopyResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_buffer;
    uint64_t dst_texture;
    uint64_t src_buffer;
    uint64_t src_texture;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CopyResource(ID3D11DeviceContext1 *iface,
        ID3D11Resource *dst_resource, ID3D11Resource *src_resource)
{
    struct qemu_d3d11_immediate_context_CopyResource call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_COPYRESOURCE);
    call.iface = (ULONG_PTR)context;

    if (!dst_resource)
    {
        call.dst_buffer = call.dst_texture = 0;
    }
    else
    {
        ID3D11Resource_GetType(dst_resource, &dim);
        switch (dim)
        {
            case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
                call.dst_buffer = 0;
                call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)dst_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
                call.dst_buffer = 0;
                call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)dst_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
                call.dst_buffer = 0;
                call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)dst_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_BUFFER:
                call.dst_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)dst_resource);
                call.dst_texture = 0;
                break;
        }
    }

    if (!src_resource)
    {
        call.src_buffer = call.src_texture = 0;
    }
    else
    {
        ID3D11Resource_GetType(src_resource, &dim);
        switch (dim)
        {
            case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
                call.src_buffer = 0;
                call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)src_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
                call.src_buffer = 0;
                call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)src_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
                call.src_buffer = 0;
                call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)src_resource);
                break;

            case D3D11_RESOURCE_DIMENSION_BUFFER:
                call.src_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)src_resource);
                call.src_texture = 0;
                break;
        }
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CopyResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CopyResource *c = (struct qemu_d3d11_immediate_context_CopyResource *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *src = NULL, *dst = NULL;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    if (c->src_buffer)
    {
        buf = QEMU_G2H(c->src_buffer);
        src = (ID3D11Resource *)buf->host11;
    }
    else if (c->src_texture)
    {
        tex = QEMU_G2H(c->src_texture);
        src = (ID3D11Resource *)tex->host11_1d;
    }

    if (c->dst_buffer)
    {
        buf = QEMU_G2H(c->dst_buffer);
        dst = (ID3D11Resource *)buf->host11;
    }
    else if (c->dst_texture)
    {
        tex = QEMU_G2H(c->dst_texture);
        dst = (ID3D11Resource *)tex->host11_1d;
    }

    ID3D11DeviceContext1_CopyResource(context->host, dst, src);
}

#endif

struct qemu_d3d11_immediate_context_UpdateSubresource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t subresource_idx;
    uint64_t box;
    uint64_t data;
    uint64_t row_pitch;
    uint64_t depth_pitch;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_UpdateSubresource(ID3D11DeviceContext1 *iface,
        ID3D11Resource *resource, UINT subresource_idx, const D3D11_BOX *box, const void *data, UINT row_pitch,
        UINT depth_pitch)
{
    struct qemu_d3d11_immediate_context_UpdateSubresource call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_UPDATESUBRESOURCE);
    call.iface = (ULONG_PTR)context;
    call.subresource_idx = subresource_idx;
    call.box = (ULONG_PTR)box;
    call.data = (ULONG_PTR)data;
    call.row_pitch = row_pitch;
    call.depth_pitch = depth_pitch;

    ID3D11Resource_GetType(resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)resource);
            call.texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_UpdateSubresource(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_UpdateSubresource *c = (struct qemu_d3d11_immediate_context_UpdateSubresource *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *resource = NULL;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->texture)
    {
        texture = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)texture->host11_1d;
    }
    else if (c->buffer)
    {
        buffer = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buffer->host11;
    }

    ID3D11DeviceContext1_UpdateSubresource(context->host, resource, c->subresource_idx, QEMU_G2H(c->box),
            QEMU_G2H(c->data), c->row_pitch, c->depth_pitch);
}

#endif

struct qemu_d3d11_immediate_context_CopyStructureCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_buffer;
    uint64_t dst_offset;
    uint64_t src_view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CopyStructureCount(ID3D11DeviceContext1 *iface,
        ID3D11Buffer *dst_buffer, UINT dst_offset, ID3D11UnorderedAccessView *src_view)
{
    struct qemu_d3d11_immediate_context_CopyStructureCount call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_buffer *buffer_impl = unsafe_impl_from_ID3D11Buffer(dst_buffer);
    struct qemu_d3d11_view *view_impl = unsafe_impl_from_ID3D11UnorderedAccessView(src_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_COPYSTRUCTURECOUNT);
    call.iface = (ULONG_PTR)context;
    call.dst_buffer = (ULONG_PTR)buffer_impl;
    call.dst_offset = dst_offset;
    call.src_view = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CopyStructureCount(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CopyStructureCount *c =
            (struct qemu_d3d11_immediate_context_CopyStructureCount *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->src_view);
    buffer = QEMU_G2H(c->dst_buffer);

    ID3D11DeviceContext1_CopyStructureCount(context->host, buffer ? buffer->host11 : NULL, c->dst_offset,
            view ? view->host_uav : NULL);
}

#endif

struct qemu_d3d11_immediate_context_ClearRenderTargetView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view;
    uint64_t color_rgba;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ClearRenderTargetView(ID3D11DeviceContext1 *iface,
        ID3D11RenderTargetView *render_target_view, const float color_rgba[4])
{
    struct qemu_d3d11_immediate_context_ClearRenderTargetView call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *rtv = unsafe_impl_from_ID3D11RenderTargetView(render_target_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CLEARRENDERTARGETVIEW);
    call.iface = (ULONG_PTR)context;
    call.render_target_view = (ULONG_PTR)rtv;
    call.color_rgba = (ULONG_PTR)color_rgba;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ClearRenderTargetView(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ClearRenderTargetView *c =
            (struct qemu_d3d11_immediate_context_ClearRenderTargetView *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *rtv;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    rtv = QEMU_G2H(c->render_target_view);

    ID3D11DeviceContext1_ClearRenderTargetView(context->host, rtv ? rtv->host_rt11 : NULL, QEMU_G2H(c->color_rgba));
}

#endif

struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t unordered_access_view;
    uint64_t values;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ClearUnorderedAccessViewUint(ID3D11DeviceContext1 *iface,
        ID3D11UnorderedAccessView *unordered_access_view, const UINT values[4])
{
    struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *view = unsafe_impl_from_ID3D11UnorderedAccessView(unordered_access_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CLEARUNORDEREDACCESSVIEWUINT);
    call.iface = (ULONG_PTR)context;
    call.unordered_access_view = (ULONG_PTR)view;
    call.values = (ULONG_PTR)values;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint *c =
            (struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->unordered_access_view);

    ID3D11DeviceContext1_ClearUnorderedAccessViewUint(context->host, view ? view->host_uav : NULL,
            QEMU_G2H(c->values));
}

#endif

struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t unordered_access_view;
    uint64_t values;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ClearUnorderedAccessViewFloat(ID3D11DeviceContext1 *iface,
        ID3D11UnorderedAccessView *unordered_access_view, const float values[4])
{
    struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *view = unsafe_impl_from_ID3D11UnorderedAccessView(unordered_access_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CLEARUNORDEREDACCESSVIEWFLOAT);
    call.iface = (ULONG_PTR)context;
    call.unordered_access_view = (ULONG_PTR)view;
    call.values = (ULONG_PTR)values;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat *c = (struct qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->unordered_access_view);

    ID3D11DeviceContext1_ClearUnorderedAccessViewFloat(context->host, view ? view->host_uav : NULL,
            QEMU_G2H(c->values));
}

#endif

struct qemu_d3d11_immediate_context_ClearDepthStencilView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil_view;
    uint64_t flags;
    double depth;
    uint64_t stencil;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ClearDepthStencilView(ID3D11DeviceContext1 *iface,
        ID3D11DepthStencilView *depth_stencil_view, UINT flags, FLOAT depth, UINT8 stencil)
{
    struct qemu_d3d11_immediate_context_ClearDepthStencilView call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *view = unsafe_impl_from_ID3D11DepthStencilView(depth_stencil_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CLEARDEPTHSTENCILVIEW);
    call.iface = (ULONG_PTR)context;
    call.depth_stencil_view = (ULONG_PTR)view;
    call.flags = flags;
    call.depth = depth;
    call.stencil = stencil;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ClearDepthStencilView(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ClearDepthStencilView *c =
            (struct qemu_d3d11_immediate_context_ClearDepthStencilView *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->depth_stencil_view);

    ID3D11DeviceContext1_ClearDepthStencilView(context->host, view ? view->host_ds11 : NULL,
            c->flags, c->depth, c->stencil);
}

#endif

struct qemu_d3d11_immediate_context_GenerateMips
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GenerateMips(ID3D11DeviceContext1 *iface,
        ID3D11ShaderResourceView *view)
{
    struct qemu_d3d11_immediate_context_GenerateMips call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *impl = unsafe_impl_from_ID3D11ShaderResourceView(view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GENERATEMIPS);
    call.iface = (ULONG_PTR)context;
    call.view = (ULONG_PTR)impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_GenerateMips(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GenerateMips *c = (struct qemu_d3d11_immediate_context_GenerateMips *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->view);

    ID3D11DeviceContext1_GenerateMips(context->host, view ? view->host_sr11 : NULL);
}

#endif

struct qemu_d3d11_immediate_context_SetResourceMinLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
    double min_lod;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_SetResourceMinLOD(ID3D11DeviceContext1 *iface,
        ID3D11Resource *resource, FLOAT min_lod)
{
    struct qemu_d3d11_immediate_context_SetResourceMinLOD call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_SETRESOURCEMINLOD);
    call.iface = (ULONG_PTR)context;
    call.resource = (ULONG_PTR)resource;
    call.min_lod = min_lod;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_SetResourceMinLOD(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_SetResourceMinLOD *c = (struct qemu_d3d11_immediate_context_SetResourceMinLOD *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_SetResourceMinLOD(context->host, QEMU_G2H(c->resource), c->min_lod);
}

#endif

struct qemu_d3d11_immediate_context_GetResourceMinLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static FLOAT STDMETHODCALLTYPE d3d11_immediate_context_GetResourceMinLOD(ID3D11DeviceContext1 *iface,
        ID3D11Resource *resource)
{
    struct qemu_d3d11_immediate_context_GetResourceMinLOD call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GETRESOURCEMINLOD);
    call.iface = (ULONG_PTR)context;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_d3d11_immediate_context_GetResourceMinLOD(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GetResourceMinLOD *c = (struct qemu_d3d11_immediate_context_GetResourceMinLOD *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.dret = ID3D11DeviceContext1_GetResourceMinLOD(context->host, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_immediate_context_ResolveSubresource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_buffer;
    uint64_t dst_texture;
    uint64_t dst_subresource_idx;
    uint64_t src_buffer;
    uint64_t src_texture;
    uint64_t src_subresource_idx;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ResolveSubresource(ID3D11DeviceContext1 *iface,
        ID3D11Resource *dst_resource, UINT dst_subresource_idx, ID3D11Resource *src_resource,
        UINT src_subresource_idx, DXGI_FORMAT format)
{
    struct qemu_d3d11_immediate_context_ResolveSubresource call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RESOLVESUBRESOURCE);
    call.iface = (ULONG_PTR)context;
    call.dst_subresource_idx = dst_subresource_idx;
    call.src_subresource_idx = src_subresource_idx;
    call.format = format;

    ID3D11Resource_GetType(dst_resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)dst_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)dst_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)dst_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.dst_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)dst_resource);
            call.dst_texture = 0;
            break;
    }

    ID3D11Resource_GetType(src_resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)src_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)src_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)src_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.src_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)src_resource);
            call.src_texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ResolveSubresource(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ResolveSubresource *c =
            (struct qemu_d3d11_immediate_context_ResolveSubresource *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *src, *dst;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    if (c->src_buffer)
    {
        buf = QEMU_G2H(c->src_buffer);
        src = (ID3D11Resource *)buf->host11;
    }
    else
    {
        tex = QEMU_G2H(c->src_texture);
        src = (ID3D11Resource *)tex->host11_1d;
    }

    if (c->dst_buffer)
    {
        buf = QEMU_G2H(c->dst_buffer);
        dst = (ID3D11Resource *)buf->host11;
    }
    else
    {
        tex = QEMU_G2H(c->dst_texture);
        dst = (ID3D11Resource *)tex->host11_1d;
    }

    ID3D11DeviceContext1_ResolveSubresource(context->host, dst, c->dst_subresource_idx, src,
            c->src_subresource_idx, c->format);
}

#endif

struct qemu_d3d11_immediate_context_ExecuteCommandList
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t command_list;
    uint64_t restore_state;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ExecuteCommandList(ID3D11DeviceContext1 *iface, ID3D11CommandList *command_list, BOOL restore_state)
{
    struct qemu_d3d11_immediate_context_ExecuteCommandList call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_EXECUTECOMMANDLIST);
    call.iface = (ULONG_PTR)context;
    call.command_list = (ULONG_PTR)command_list;
    call.restore_state = restore_state;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ExecuteCommandList(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ExecuteCommandList *c = (struct qemu_d3d11_immediate_context_ExecuteCommandList *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_ExecuteCommandList(context->host, QEMU_G2H(c->command_list), c->restore_state);
}

#endif

struct qemu_d3d11_immediate_context_HSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSSetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView *const *views)
{
    struct qemu_d3d11_immediate_context_HSSetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_HSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSSetShaderResources *c =
            (struct qemu_d3d11_immediate_context_HSSetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_sr11 : NULL;

    ID3D11DeviceContext1_HSSetShaderResources(context->host, c->start_slot, count, views);
}

#endif

struct qemu_d3d11_immediate_context_HSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSSetShader(ID3D11DeviceContext1 *iface,
        ID3D11HullShader *shader, ID3D11ClassInstance *const *class_instances, UINT class_instance_count)
{
    struct qemu_d3d11_immediate_context_HSSetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *shader_impl = unsafe_impl_from_ID3D11HullShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSSETSHADER);
    call.iface = (ULONG_PTR)context;
    call.shader = (ULONG_PTR)shader_impl;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = class_instance_count;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_HSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSSetShader *c = (struct qemu_d3d11_immediate_context_HSSetShader *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported.\n");

    ID3D11DeviceContext1_HSSetShader(context->host, shader ? shader->host_hs11 : NULL,
            QEMU_G2H(c->class_instances), c->class_instance_count);
}

#endif

struct qemu_d3d11_immediate_context_HSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSSetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState *const *samplers)
{
    struct qemu_d3d11_immediate_context_HSSetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSSETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_HSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSSetSamplers *c = (struct qemu_d3d11_immediate_context_HSSetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss11 : NULL;


    ID3D11DeviceContext1_HSSetSamplers(context->host, c->start_slot, c->sampler_count, ifaces);
}

#endif

struct qemu_d3d11_immediate_context_HSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSSetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer *const *buffers)
{
    struct qemu_d3d11_immediate_context_HSSetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_HSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSSetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_HSSetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_HSSetConstantBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d11_immediate_context_DSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSSetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView *const *views)
{
    struct qemu_d3d11_immediate_context_DSSetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_DSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSSetShaderResources *c = (struct qemu_d3d11_immediate_context_DSSetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_sr11 : NULL;

    ID3D11DeviceContext1_DSSetShaderResources(context->host, c->start_slot, count, views);
}

#endif

struct qemu_d3d11_immediate_context_DSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSSetShader(ID3D11DeviceContext1 *iface,
        ID3D11DomainShader *shader, ID3D11ClassInstance *const *class_instances, UINT class_instance_count)
{
    struct qemu_d3d11_immediate_context_DSSetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *shader_impl = unsafe_impl_from_ID3D11DomainShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSSETSHADER);
    call.iface = (ULONG_PTR)context;
    call.shader = (ULONG_PTR)shader_impl;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = class_instance_count;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSSetShader *c = (struct qemu_d3d11_immediate_context_DSSetShader *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported.\n");

    ID3D11DeviceContext1_DSSetShader(context->host, shader ? shader->host_ds11 : NULL,
            QEMU_G2H(c->class_instances), c->class_instance_count);
}

#endif

struct qemu_d3d11_immediate_context_DSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSSetSamplers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT sampler_count, ID3D11SamplerState *const *samplers)
{
    struct qemu_d3d11_immediate_context_DSSetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSSETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_DSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSSetSamplers *c = (struct qemu_d3d11_immediate_context_DSSetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss11 : NULL;

    ID3D11DeviceContext1_DSSetSamplers(context->host, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d11_immediate_context_DSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSSetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer *const *buffers)
{
    struct qemu_d3d11_immediate_context_DSSetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSSetConstantBuffers *c = (struct qemu_d3d11_immediate_context_DSSetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_DSSetConstantBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d11_immediate_context_CSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSSetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView *const *views)
{
    struct qemu_d3d11_immediate_context_CSSetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_CSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSSetShaderResources *c =
            (struct qemu_d3d11_immediate_context_CSSetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_sr11 : NULL;

    ID3D11DeviceContext1_CSSetShaderResources(context->host, c->start_slot, count, views);
}

#endif

struct qemu_d3d11_immediate_context_CSSetUnorderedAccessViews
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
    uint64_t initial_counts;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSSetUnorderedAccessViews(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11UnorderedAccessView *const *views, const UINT *initial_counts)
{
    struct qemu_d3d11_immediate_context_CSSetUnorderedAccessViews call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSSETUNORDEREDACCESSVIEWS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;
    call.initial_counts = (ULONG_PTR)initial_counts;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11UnorderedAccessView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_CSSetUnorderedAccessViews(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSSetUnorderedAccessViews *c =
            (struct qemu_d3d11_immediate_context_CSSetUnorderedAccessViews *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11UnorderedAccessView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? impls[i]->host_uav : NULL;

    ID3D11DeviceContext1_CSSetUnorderedAccessViews(context->host, c->start_slot, count, views,
            QEMU_G2H(c->initial_counts));
}

#endif

struct qemu_d3d11_immediate_context_CSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSSetShader(ID3D11DeviceContext1 *iface,
        ID3D11ComputeShader *shader, ID3D11ClassInstance *const *class_instances, UINT class_instance_count)
{
    struct qemu_d3d11_immediate_context_CSSetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *shader_impl = unsafe_impl_from_ID3D11ComputeShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSSETSHADER);
    call.iface = (ULONG_PTR)context;
    call.shader = (ULONG_PTR)shader_impl;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = class_instance_count;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSSetShader *c = (struct qemu_d3d11_immediate_context_CSSetShader *)call;
    struct qemu_d3d11_device_context *context;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported.\n");

    ID3D11DeviceContext1_CSSetShader(context->host, shader ? shader->host_cs11 : NULL,
            QEMU_G2H(c->class_instances), c->class_instance_count);
}

#endif

struct qemu_d3d11_immediate_context_CSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSSetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot, UINT sampler_count, ID3D11SamplerState *const *samplers)
{
    struct qemu_d3d11_immediate_context_CSSetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSSETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_CSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSSetSamplers *c = (struct qemu_d3d11_immediate_context_CSSetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss11 : NULL;

    ID3D11DeviceContext1_CSSetSamplers(context->host, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d11_immediate_context_CSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSSetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer *const *buffers)
{
    struct qemu_d3d11_immediate_context_CSSetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSSetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_CSSetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host11 : NULL;
    }

    ID3D11DeviceContext1_CSSetConstantBuffers(context->host, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d11_immediate_context_VSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSGetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_VSGetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_VSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSGetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_VSGetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_VSGetConstantBuffers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_PSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSGetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView **views)
{
    struct qemu_d3d11_immediate_context_PSGetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11ShaderResourceView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_PSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSGetShaderResources *c =
            (struct qemu_d3d11_immediate_context_PSGetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_PSGetShaderResources(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_PSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSGetShader(ID3D11DeviceContext1 *iface,
        ID3D11PixelShader **shader, ID3D11ClassInstance **class_instances, UINT *class_instance_count)
{
    struct qemu_d3d11_immediate_context_PSGetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSGETSHADER);
    call.iface = (ULONG_PTR)context;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = (ULONG_PTR)class_instance_count;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D11PixelShader_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_PSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSGetShader *c = (struct qemu_d3d11_immediate_context_PSGetShader *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11PixelShader *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported yet.\n");

    ID3D11DeviceContext1_PSGetShader(context->host, &host, NULL, QEMU_G2H(c->class_instance_count));
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_PSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSGetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState **samplers)
{
    struct qemu_d3d11_immediate_context_PSGetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSGETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D11SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_PSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSGetSamplers *c = (struct qemu_d3d11_immediate_context_PSGetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext1_PSGetSamplers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_VSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSGetShader(ID3D11DeviceContext1 *iface,
        ID3D11VertexShader **shader, ID3D11ClassInstance **class_instances, UINT *class_instance_count)
{
    struct qemu_d3d11_immediate_context_VSGetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSGETSHADER);
    call.iface = (ULONG_PTR)context;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = (ULONG_PTR)class_instance_count;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D11VertexShader_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_VSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSGetShader *c = (struct qemu_d3d11_immediate_context_VSGetShader *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11VertexShader *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported yet.\n");

    ID3D11DeviceContext1_VSGetShader(context->host, &host, NULL, QEMU_G2H(c->class_instance_count));
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_PSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSGetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_PSGetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_PSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSGetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_PSGetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_PSGetConstantBuffers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_IAGetInputLayout
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t input_layout;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IAGetInputLayout(ID3D11DeviceContext1 *iface,
        ID3D11InputLayout **input_layout)
{
    struct qemu_d3d11_immediate_context_IAGetInputLayout call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_input_layout *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IAGETINPUTLAYOUT);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_input_layout *)(ULONG_PTR)call.input_layout;
    *input_layout = impl ? &impl->ID3D11InputLayout_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_IAGetInputLayout(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IAGetInputLayout *c =
            (struct qemu_d3d11_immediate_context_IAGetInputLayout *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11InputLayout *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_IAGetInputLayout(context->host, &host);
    c->input_layout = QEMU_H2G(input_layout_from_host(host));
}

#endif

struct qemu_d3d11_immediate_context_IAGetVertexBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t strides;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IAGetVertexBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *strides, UINT *offsets)
{
    struct qemu_d3d11_immediate_context_IAGetVertexBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IAGETVERTEXBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.strides = (ULONG_PTR)strides;
    call.offsets = (ULONG_PTR)offsets;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_IAGetVertexBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IAGetVertexBuffers *c =
            (struct qemu_d3d11_immediate_context_IAGetVertexBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_IAGetVertexBuffers(context->host, c->start_slot, c->buffer_count, ifaces,
            QEMU_G2H(c->strides), QEMU_G2H(c->offsets));

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_IAGetIndexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t format;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IAGetIndexBuffer(ID3D11DeviceContext1 *iface,
        ID3D11Buffer **buffer, DXGI_FORMAT *format, UINT *offset)
{
    struct qemu_d3d11_immediate_context_IAGetIndexBuffer call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_buffer *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IAGETINDEXBUFFER);
    call.iface = (ULONG_PTR)context;
    call.format = (ULONG_PTR)format;
    call.offset = (ULONG_PTR)offset;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_buffer *)(ULONG_PTR)call.buffer;
    *buffer = impl ? &impl->ID3D11Buffer_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_IAGetIndexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IAGetIndexBuffer *c =
            (struct qemu_d3d11_immediate_context_IAGetIndexBuffer *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_IAGetIndexBuffer(context->host, &host, QEMU_G2H(c->format), QEMU_G2H(c->offset));
    c->buffer = QEMU_H2G(buffer_from_host(host));
}

#endif

struct qemu_d3d11_immediate_context_GSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSGetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_GSGetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_GSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSGetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_GSGetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_GSGetConstantBuffers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_GSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSGetShader(ID3D11DeviceContext1 *iface,
        ID3D11GeometryShader **shader, ID3D11ClassInstance **class_instances, UINT *class_instance_count)
{
    struct qemu_d3d11_immediate_context_GSGetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSGETSHADER);
    call.iface = (ULONG_PTR)context;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = (ULONG_PTR)class_instance_count;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D11GeometryShader_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_GSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSGetShader *c = (struct qemu_d3d11_immediate_context_GSGetShader *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11GeometryShader *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported yet.\n");

    ID3D11DeviceContext1_GSGetShader(context->host, &host, NULL, QEMU_G2H(c->class_instance_count));
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_IAGetPrimitiveTopology
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t topology;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_IAGetPrimitiveTopology(ID3D11DeviceContext1 *iface,
        D3D11_PRIMITIVE_TOPOLOGY *topology)
{
    struct qemu_d3d11_immediate_context_IAGetPrimitiveTopology call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_IAGETPRIMITIVETOPOLOGY);
    call.iface = (ULONG_PTR)context;
    call.topology = (ULONG_PTR)topology;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_IAGetPrimitiveTopology(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_IAGetPrimitiveTopology *c = (struct qemu_d3d11_immediate_context_IAGetPrimitiveTopology *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_IAGetPrimitiveTopology(context->host, QEMU_G2H(c->topology));
}

#endif

struct qemu_d3d11_immediate_context_VSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSGetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView **views)
{
    struct qemu_d3d11_immediate_context_VSGetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11ShaderResourceView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_VSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSGetShaderResources *c =
            (struct qemu_d3d11_immediate_context_VSGetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_VSGetShaderResources(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_VSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSGetSamplers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT sampler_count, ID3D11SamplerState **samplers)
{
    struct qemu_d3d11_immediate_context_VSGetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSGETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D11SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_VSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSGetSamplers *c = (struct qemu_d3d11_immediate_context_VSGetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext1_VSGetSamplers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_GetPredication
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t predicate;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GetPredication(ID3D11DeviceContext1 *iface,
        ID3D11Predicate **predicate, BOOL *value)
{
    struct qemu_d3d11_immediate_context_GetPredication call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_query *query;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GETPREDICATION);
    call.iface = (ULONG_PTR)context;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    query = (struct qemu_d3d11_query *)(ULONG_PTR)call.predicate;
    *predicate = query ? (ID3D11Predicate *)&query->ID3D11Query_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_GetPredication(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GetPredication *c = (struct qemu_d3d11_immediate_context_GetPredication *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Query *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_GetPredication(context->host, (ID3D11Predicate **)&host, QEMU_G2H(c->value));
    c->predicate = QEMU_H2G(query_from_host(host));
}

#endif

struct qemu_d3d11_immediate_context_GSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSGetShaderResources(ID3D11DeviceContext1 *iface, UINT start_slot, UINT view_count, ID3D11ShaderResourceView **views)
{
    struct qemu_d3d11_immediate_context_GSGetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11ShaderResourceView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_GSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSGetShaderResources *c =
            (struct qemu_d3d11_immediate_context_GSGetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_GSGetShaderResources(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_GSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSGetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState **samplers)
{
    struct qemu_d3d11_immediate_context_GSGetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSGETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D11SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_GSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSGetSamplers *c = (struct qemu_d3d11_immediate_context_GSGetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext1_GSGetSamplers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_OMGetRenderTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view_count;
    uint64_t render_target_views;
    uint64_t depth_stencil_view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMGetRenderTargets(ID3D11DeviceContext1 *iface,
        UINT render_target_view_count, ID3D11RenderTargetView **render_target_views,
        ID3D11DepthStencilView **depth_stencil_view)
{
    struct qemu_d3d11_immediate_context_OMGetRenderTargets call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *view;
    uint64_t stack[16], *rtv_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMGETRENDERTARGETS);
    call.iface = (ULONG_PTR)context;
    call.render_target_view_count = render_target_view_count;
    call.depth_stencil_view = (ULONG_PTR)depth_stencil_view;

    if (render_target_view_count > (sizeof(stack) / sizeof(*stack)))
    {
        rtv_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*rtv_impl) * render_target_view_count);
        if (!rtv_impl)
            WINE_ERR("Out of memory\n");
    }

    call.render_target_views = (ULONG_PTR)rtv_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < render_target_view_count; ++i)
    {
        if (!rtv_impl[i])
        {
            render_target_views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)rtv_impl[i];
        render_target_views[i] = &view->ID3D11RenderTargetView_iface;
    }

    if (rtv_impl != stack)
        HeapFree(GetProcessHeap(), 0, rtv_impl);

    if (call.depth_stencil_view)
    {
        view = (struct qemu_d3d11_view *)(ULONG_PTR)call.depth_stencil_view;
        *depth_stencil_view = &view->ID3D11DepthStencilView_iface;
    }
    else if (depth_stencil_view)
    {
        *depth_stencil_view = NULL;
    }
}

#else

void qemu_d3d11_immediate_context_OMGetRenderTargets(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMGetRenderTargets *c =
            (struct qemu_d3d11_immediate_context_OMGetRenderTargets *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11RenderTargetView **ifaces;
    ID3D11DepthStencilView *host_ds = NULL;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->render_target_views);
    view_impl = QEMU_G2H(c->render_target_views);
    count = c->render_target_view_count;

    ID3D11DeviceContext1_OMGetRenderTargets(context->host, count, ifaces, 
            c->depth_stencil_view ? &host_ds : NULL);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);

    c->depth_stencil_view = QEMU_H2G(view_from_host((ID3D11DeviceChild *)host_ds));
}

#endif

struct qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view_count;
    uint64_t render_target_views;
    uint64_t depth_stencil_view;
    uint64_t unordered_access_view_start_slot;
    uint64_t unordered_access_view_count;
    uint64_t unordered_access_views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews(
        ID3D11DeviceContext1 *iface, UINT render_target_view_count, ID3D11RenderTargetView **render_target_views,
        ID3D11DepthStencilView **depth_stencil_view, UINT unordered_access_view_start_slot,
        UINT unordered_access_view_count, ID3D11UnorderedAccessView **unordered_access_views)
{
    struct qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_view *view;
    uint64_t rtv_stack[16], *rtv_impl = rtv_stack;
    uint64_t uav_stack[16], *uav_impl = uav_stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMGETRENDERTARGETSANDUNORDEREDACCESSVIEWS);
    call.iface = (ULONG_PTR)context;
    call.render_target_view_count = render_target_view_count;
    call.depth_stencil_view = (ULONG_PTR)depth_stencil_view;
    call.unordered_access_view_start_slot = unordered_access_view_start_slot;
    call.unordered_access_view_count = unordered_access_view_count;
    call.unordered_access_views = (ULONG_PTR)unordered_access_views;

    if (render_target_view_count > (sizeof(rtv_stack) / sizeof(*rtv_stack)))
    {
        rtv_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*rtv_impl) * render_target_view_count);
        if (!rtv_impl)
            WINE_ERR("Out of memory\n");
    }
    call.render_target_views = (ULONG_PTR)rtv_impl;

    if (unordered_access_view_count > (sizeof(uav_stack) / sizeof(*uav_stack)))
    {
        uav_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*uav_impl) * unordered_access_view_count);
        if (!uav_impl)
            WINE_ERR("Out of memory\n");
    }
    call.unordered_access_views = (ULONG_PTR)uav_impl;

    qemu_syscall(&call.super);

    if (depth_stencil_view)
    {
        view = (struct qemu_d3d11_view *)(ULONG_PTR)call.depth_stencil_view;
        *depth_stencil_view = view ? &view->ID3D11DepthStencilView_iface : NULL;
    }

    for (i = 0; i < render_target_view_count; ++i)
    {
        if (!rtv_impl[i])
        {
            render_target_views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)rtv_impl[i];
        render_target_views[i] = &view->ID3D11RenderTargetView_iface;
    }

    for (i = 0; i < unordered_access_view_count; ++i)
    {
        if (!uav_impl[i])
        {
            unordered_access_views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)uav_impl[i];
        unordered_access_views[i] = &view->ID3D11UnorderedAccessView_iface;
    }

    if (rtv_impl != rtv_stack)
        HeapFree(GetProcessHeap(), 0, rtv_impl);
    if (uav_impl != uav_stack)
        HeapFree(GetProcessHeap(), 0, uav_impl);
}

#else

void qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews *c =
            (struct qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11DepthStencilView *host_ds = NULL;
    ID3D11RenderTargetView **rt_ifaces;
    struct qemu_d3d11_view **rt_impl;
    ID3D11UnorderedAccessView **uav_ifaces;
    struct qemu_d3d11_view **uav_impl;
    UINT i;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    rt_ifaces = QEMU_G2H(c->render_target_views);
    rt_impl = QEMU_G2H(c->render_target_views);
    uav_ifaces = QEMU_G2H(c->unordered_access_views);
    uav_impl = QEMU_G2H(c->unordered_access_views);

    ID3D11DeviceContext1_OMGetRenderTargetsAndUnorderedAccessViews(context->host,
            c->render_target_view_count, rt_ifaces, c->depth_stencil_view ? &host_ds : NULL,
            c->unordered_access_view_start_slot, c->unordered_access_view_count, uav_ifaces);

    c->depth_stencil_view = QEMU_H2G(view_from_host((ID3D11DeviceChild *)host_ds));

    for (i = 0; i < c->render_target_view_count; ++i)
        rt_impl[i] = view_from_host((ID3D11DeviceChild *)rt_ifaces[i]);

    for (i = 0; i < c->unordered_access_view_count; ++i)
        uav_impl[i] = view_from_host((ID3D11DeviceChild *)uav_ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_OMGetBlendState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t blend_state;
    uint64_t blend_factor;
    uint64_t sample_mask;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMGetBlendState(ID3D11DeviceContext1 *iface,
        ID3D11BlendState **blend_state, FLOAT blend_factor[4], UINT *sample_mask)
{
    struct qemu_d3d11_immediate_context_OMGetBlendState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_state *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMGETBLENDSTATE);
    call.iface = (ULONG_PTR)context;
    call.blend_factor = (ULONG_PTR)blend_factor;
    call.sample_mask = (ULONG_PTR)sample_mask;

    qemu_syscall(&call.super);
    impl = (struct qemu_d3d11_state *)(ULONG_PTR)call.blend_state;
    *blend_state = impl ? &impl->ID3D11BlendState_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_OMGetBlendState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMGetBlendState *c =
            (struct qemu_d3d11_immediate_context_OMGetBlendState *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11BlendState *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_OMGetBlendState(context->host, &host, QEMU_G2H(c->blend_factor), QEMU_G2H(c->sample_mask));
    c->blend_state = QEMU_H2G(state_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_OMGetDepthStencilState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil_state;
    uint64_t stencil_ref;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_OMGetDepthStencilState(ID3D11DeviceContext1 *iface,
        ID3D11DepthStencilState **depth_stencil_state, UINT *stencil_ref)
{
    struct qemu_d3d11_immediate_context_OMGetDepthStencilState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_state *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_OMGETDEPTHSTENCILSTATE);
    call.iface = (ULONG_PTR)context;
    call.stencil_ref = (ULONG_PTR)stencil_ref;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_state *)(ULONG_PTR)call.depth_stencil_state;
    *depth_stencil_state = impl ? &impl->ID3D11DepthStencilState_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_OMGetDepthStencilState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_OMGetDepthStencilState *c =
            (struct qemu_d3d11_immediate_context_OMGetDepthStencilState *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11DepthStencilState *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_OMGetDepthStencilState(context->host, &host, QEMU_G2H(c->stencil_ref));
    c->depth_stencil_state = QEMU_H2G(state_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_SOGetTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_SOGetTargets(ID3D11DeviceContext1 *iface,
        UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_SOGetTargets call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_SOGETTARGETS);
    call.iface = (ULONG_PTR)context;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_SOGetTargets(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_SOGetTargets *c = (struct qemu_d3d11_immediate_context_SOGetTargets *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_SOGetTargets(context->host, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_RSGetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rasterizer_state;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_RSGetState(ID3D11DeviceContext1 *iface,
        ID3D11RasterizerState **rasterizer_state)
{
    struct qemu_d3d11_immediate_context_RSGetState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_state *state;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RSGETSTATE);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);
    state = (struct qemu_d3d11_state *)(ULONG_PTR)call.rasterizer_state;

    if (state)
        *rasterizer_state = &state->ID3D11RasterizerState_iface;
    else
        *rasterizer_state = NULL;
}

#else

void qemu_d3d11_immediate_context_RSGetState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_RSGetState *c = (struct qemu_d3d11_immediate_context_RSGetState *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11RasterizerState *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_RSGetState(context->host, &host);
    c->rasterizer_state = QEMU_H2G(state_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_RSGetViewports
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport_count;
    uint64_t viewports;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_RSGetViewports(ID3D11DeviceContext1 *iface,
        UINT *viewport_count, D3D11_VIEWPORT *viewports)
{
    struct qemu_d3d11_immediate_context_RSGetViewports call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RSGETVIEWPORTS);
    call.iface = (ULONG_PTR)context;
    call.viewport_count = (ULONG_PTR)viewport_count;
    call.viewports = (ULONG_PTR)viewports;
    call.size = (ULONG_PTR)sizeof(*viewports);

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_RSGetViewports(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_RSGetViewports *c = (struct qemu_d3d11_immediate_context_RSGetViewports *)call;
    struct qemu_d3d11_device_context *context;

    /* D3D11_VIEWPORT has the same size in 32 and 64 bit and the input array is not an array of pointers. */
    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_RSGetViewports(context->host, QEMU_G2H(c->viewport_count), QEMU_G2H(c->viewports));
}

#endif

struct qemu_d3d11_immediate_context_RSGetScissorRects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_RSGetScissorRects(ID3D11DeviceContext1 *iface,
        UINT *rect_count, D3D11_RECT *rects)
{
    struct qemu_d3d11_immediate_context_RSGetScissorRects call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_RSGETSCISSORRECTS);
    call.iface = (ULONG_PTR)context;
    call.rect_count = (ULONG_PTR)rect_count;
    call.rects = (ULONG_PTR)rects;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_RSGetScissorRects(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_RSGetScissorRects *c =
            (struct qemu_d3d11_immediate_context_RSGetScissorRects *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_RSGetScissorRects(context->host, QEMU_G2H(c->rect_count), QEMU_G2H(c->rects));
}

#endif

struct qemu_d3d11_immediate_context_HSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSGetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView **views)
{
    struct qemu_d3d11_immediate_context_HSGetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11ShaderResourceView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_HSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSGetShaderResources *c =
            (struct qemu_d3d11_immediate_context_HSGetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_HSGetShaderResources(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_HSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSGetShader(ID3D11DeviceContext1 *iface,
        ID3D11HullShader **shader, ID3D11ClassInstance **class_instances, UINT *class_instance_count)
{
    struct qemu_d3d11_immediate_context_HSGetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSGETSHADER);
    call.iface = (ULONG_PTR)context;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = (ULONG_PTR)class_instance_count;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D11HullShader_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_HSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSGetShader *c = (struct qemu_d3d11_immediate_context_HSGetShader *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11HullShader *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported yet.\n");

    ID3D11DeviceContext1_HSGetShader(context->host, &host, NULL, QEMU_G2H(c->class_instance_count));
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_HSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSGetSamplers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT sampler_count, ID3D11SamplerState **samplers)
{
    struct qemu_d3d11_immediate_context_HSGetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSGETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D11SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_HSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSGetSamplers *c = (struct qemu_d3d11_immediate_context_HSGetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext1_HSGetSamplers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_HSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSGetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_HSGetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_HSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSGetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_HSGetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_HSGetConstantBuffers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_DSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSGetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView **views)
{
    struct qemu_d3d11_immediate_context_DSGetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11ShaderResourceView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_DSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSGetShaderResources *c =
            (struct qemu_d3d11_immediate_context_DSGetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_DSGetShaderResources(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_DSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSGetShader(ID3D11DeviceContext1 *iface,
        ID3D11DomainShader **shader, ID3D11ClassInstance **class_instances, UINT *class_instance_count)
{
    struct qemu_d3d11_immediate_context_DSGetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSGETSHADER);
    call.iface = (ULONG_PTR)context;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = (ULONG_PTR)class_instance_count;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D11DomainShader_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_DSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSGetShader *c = (struct qemu_d3d11_immediate_context_DSGetShader *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11DomainShader *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported yet.\n");

    ID3D11DeviceContext1_DSGetShader(context->host, &host, NULL, QEMU_G2H(c->class_instance_count));
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_DSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSGetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState **samplers)
{
    struct qemu_d3d11_immediate_context_DSGetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSGETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D11SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_DSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSGetSamplers *c = (struct qemu_d3d11_immediate_context_DSGetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext1_DSGetSamplers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_DSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSGetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_DSGetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}
#else

void qemu_d3d11_immediate_context_DSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSGetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_DSGetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_DSGetConstantBuffers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_CSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSGetShaderResources(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11ShaderResourceView **views)
{
    struct qemu_d3d11_immediate_context_CSGetShaderResources call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11ShaderResourceView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_CSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSGetShaderResources *c =
            (struct qemu_d3d11_immediate_context_CSGetShaderResources *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_CSGetShaderResources(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_CSGetUnorderedAccessViews
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSGetUnorderedAccessViews(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT view_count, ID3D11UnorderedAccessView **views)
{
    struct qemu_d3d11_immediate_context_CSGetUnorderedAccessViews call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSGETUNORDEREDACCESSVIEWS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = &view->ID3D11UnorderedAccessView_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d11_immediate_context_CSGetUnorderedAccessViews(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSGetUnorderedAccessViews *c =
            (struct qemu_d3d11_immediate_context_CSGetUnorderedAccessViews *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11UnorderedAccessView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_CSGetUnorderedAccessViews(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_CSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
    uint64_t class_instances;
    uint64_t class_instance_count;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSGetShader(ID3D11DeviceContext1 *iface,
        ID3D11ComputeShader **shader, ID3D11ClassInstance **class_instances, UINT *class_instance_count)
{
    struct qemu_d3d11_immediate_context_CSGetShader call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSGETSHADER);
    call.iface = (ULONG_PTR)context;
    call.class_instances = (ULONG_PTR)class_instances;
    call.class_instance_count = (ULONG_PTR)class_instance_count;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D11ComputeShader_iface : NULL;
}

#else

void qemu_d3d11_immediate_context_CSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSGetShader *c = (struct qemu_d3d11_immediate_context_CSGetShader *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11ComputeShader *host;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->class_instances)
        WINE_FIXME("ID3D11ClassInstance not supported yet.\n");

    ID3D11DeviceContext1_CSGetShader(context->host, &host, NULL, QEMU_G2H(c->class_instance_count));
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d11_immediate_context_CSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSGetSamplers(ID3D11DeviceContext1 *iface, UINT start_slot,
        UINT sampler_count, ID3D11SamplerState **samplers)
{
    struct qemu_d3d11_immediate_context_CSGetSamplers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSGETSAMPLERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D11SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d11_immediate_context_CSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSGetSamplers *c = (struct qemu_d3d11_immediate_context_CSGetSamplers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext1_CSGetSamplers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_CSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSGetConstantBuffers(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers)
{
    struct qemu_d3d11_immediate_context_CSGetConstantBuffers call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_CSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSGetConstantBuffers *c =
            (struct qemu_d3d11_immediate_context_CSGetConstantBuffers *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_CSGetConstantBuffers(context->host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_ClearState
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ClearState(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_ClearState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CLEARSTATE);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ClearState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ClearState *c = (struct qemu_d3d11_immediate_context_ClearState *)call;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_ClearState(context->host);
}

#endif

struct qemu_d3d11_immediate_context_Flush
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_Flush(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_Flush call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_FLUSH);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_Flush(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_Flush *c = (struct qemu_d3d11_immediate_context_Flush *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_Flush(context->host);
}

#endif

struct qemu_d3d11_immediate_context_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE d3d11_immediate_context_GetType(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_GetType call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GETTYPE);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GetType *c = (struct qemu_d3d11_immediate_context_GetType *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DeviceContext1_GetType(context->host);
}

#endif

struct qemu_d3d11_immediate_context_GetContextFlags
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_immediate_context_GetContextFlags(ID3D11DeviceContext1 *iface)
{
    struct qemu_d3d11_immediate_context_GetContextFlags call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GETCONTEXTFLAGS);
    call.iface = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_GetContextFlags(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GetContextFlags *c = (struct qemu_d3d11_immediate_context_GetContextFlags *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DeviceContext1_GetContextFlags(context->host);
}

#endif

struct qemu_d3d11_immediate_context_FinishCommandList
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t restore;
    uint64_t command_list;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_immediate_context_FinishCommandList(ID3D11DeviceContext1 *iface, BOOL restore, ID3D11CommandList **command_list)
{
    struct qemu_d3d11_immediate_context_FinishCommandList call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_FINISHCOMMANDLIST);
    call.iface = (ULONG_PTR)context;
    call.restore = restore;
    call.command_list = (ULONG_PTR)command_list;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_immediate_context_FinishCommandList(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_FinishCommandList *c = (struct qemu_d3d11_immediate_context_FinishCommandList *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DeviceContext1_FinishCommandList(context->host, c->restore, QEMU_G2H(c->command_list));
}

#endif

struct qemu_d3d11_immediate_context_CopySubresourceRegion1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_texture;
    uint64_t dst_buffer;
    uint64_t dst_subresource_idx;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t dst_z;
    uint64_t src_texture;
    uint64_t src_buffer;
    uint64_t src_subresource_idx;
    uint64_t src_box;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CopySubresourceRegion1(ID3D11DeviceContext1 *iface,
        ID3D11Resource *dst_resource, UINT dst_subresource_idx, UINT dst_x, UINT dst_y, UINT dst_z,
        ID3D11Resource *src_resource, UINT src_subresource_idx, const D3D11_BOX *src_box, UINT flags)
{
    struct qemu_d3d11_immediate_context_CopySubresourceRegion1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_COPYSUBRESOURCEREGION1);
    call.iface = (ULONG_PTR)context;
    call.dst_subresource_idx = dst_subresource_idx;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.dst_z = dst_z;
    call.src_subresource_idx = src_subresource_idx;
    call.src_box = (ULONG_PTR)src_box;
    call.flags = flags;

    ID3D11Resource_GetType(dst_resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)dst_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)dst_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)dst_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.dst_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)dst_resource);
            call.dst_texture = 0;
            break;
    }

    ID3D11Resource_GetType(src_resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)src_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)src_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)src_resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.src_buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)src_resource);
            call.src_texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CopySubresourceRegion1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CopySubresourceRegion1 *c =
            (struct qemu_d3d11_immediate_context_CopySubresourceRegion1 *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *src, *dst;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    if (c->src_buffer)
    {
        buf = QEMU_G2H(c->src_buffer);
        src = (ID3D11Resource *)buf->host11;
    }
    else if (c->src_texture)
    {
        tex = QEMU_G2H(c->src_texture);
        src = (ID3D11Resource *)tex->host11_1d;
    }

    if (c->dst_buffer)
    {
        buf = QEMU_G2H(c->dst_buffer);
        dst = (ID3D11Resource *)buf->host11;
    }
    else if (c->dst_texture)
    {
        tex = QEMU_G2H(c->dst_texture);
        dst = (ID3D11Resource *)tex->host11_1d;
    }

    ID3D11DeviceContext1_CopySubresourceRegion1(context->host, dst, c->dst_subresource_idx,
            c->dst_x, c->dst_y, c->dst_z, src, c->src_subresource_idx, QEMU_G2H(c->src_box), c->flags);
}

#endif

struct qemu_d3d11_immediate_context_UpdateSubresource1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t subresource_idx;
    uint64_t box;
    uint64_t data;
    uint64_t row_pitch;
    uint64_t depth_pitch;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_UpdateSubresource1(ID3D11DeviceContext1 *iface,
        ID3D11Resource *resource, UINT subresource_idx, const D3D11_BOX *box, const void *data,
        UINT row_pitch, UINT depth_pitch, UINT flags)
{
    struct qemu_d3d11_immediate_context_UpdateSubresource1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    D3D11_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_UPDATESUBRESOURCE1);
    call.iface = (ULONG_PTR)context;
    call.subresource_idx = subresource_idx;
    call.box = (ULONG_PTR)box;
    call.data = (ULONG_PTR)data;
    call.row_pitch = row_pitch;
    call.depth_pitch = depth_pitch;
    call.flags = flags;

    ID3D11Resource_GetType(resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)resource);
            call.texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_UpdateSubresource1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_UpdateSubresource1 *c =
            (struct qemu_d3d11_immediate_context_UpdateSubresource1 *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Resource *resource;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);
    if (c->texture)
    {
        texture = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)texture->host11_1d;
    }
    else
    {
        buffer = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buffer->host11;
    }

    ID3D11DeviceContext1_UpdateSubresource1(context->host, resource, c->subresource_idx,
            QEMU_G2H(c->box), QEMU_G2H(c->data), c->row_pitch, c->depth_pitch, c->flags);
}

#endif

struct qemu_d3d11_immediate_context_DiscardResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DiscardResource(ID3D11DeviceContext1 *iface, ID3D11Resource *resource)
{
    struct qemu_d3d11_immediate_context_DiscardResource call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DISCARDRESOURCE);
    call.iface = (ULONG_PTR)context;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DiscardResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DiscardResource *c = (struct qemu_d3d11_immediate_context_DiscardResource *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DiscardResource(context->host, QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_immediate_context_DiscardView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DiscardView(ID3D11DeviceContext1 *iface, ID3D11View *view)
{
    struct qemu_d3d11_immediate_context_DiscardView call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DISCARDVIEW);
    call.iface = (ULONG_PTR)context;
    call.view = (ULONG_PTR)view;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DiscardView(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DiscardView *c = (struct qemu_d3d11_immediate_context_DiscardView *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DiscardView(context->host, QEMU_G2H(c->view));
}

#endif

struct qemu_d3d11_immediate_context_VSSetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSSetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer * const *buffers, const UINT *first_constant, const UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_VSSetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSSETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_VSSetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSSetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_VSSetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_VSSetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_HSSetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSSetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer * const *buffers, const UINT *first_constant, const UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_HSSetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSSETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_HSSetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSSetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_HSSetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_HSSetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_DSSetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSSetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer * const *buffers, const UINT *first_constant, const UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_DSSetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSSETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DSSetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSSetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_DSSetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DSSetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_GSSetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSSetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer * const *buffers, const UINT *first_constant, const UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_GSSetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSSETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_GSSetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSSetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_GSSetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_GSSetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_PSSetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSSetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer * const *buffers, const UINT *first_constant, const UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_PSSetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSSETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_PSSetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSSetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_PSSetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_PSSetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_CSSetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSSetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer * const *buffers, const UINT *first_constant, const UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_CSSetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSSETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CSSetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSSetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_CSSetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_CSSetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_VSGetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_VSGetConstantBuffers1(ID3D11DeviceContext1 *iface,
        UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *first_constant, UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_VSGetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_VSGETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D11Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d11_immediate_context_VSGetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_VSGetConstantBuffers1 *c =
            (struct qemu_d3d11_immediate_context_VSGetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_FIXME("Untested!\n");
    context = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_VSGetConstantBuffers1(context->host, c->start_slot, count, ifaces,
            QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d11_immediate_context_HSGetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_HSGetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *first_constant, UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_HSGetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_HSGETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_HSGetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_HSGetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_HSGetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_HSGetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_DSGetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DSGetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *first_constant, UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_DSGetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DSGETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DSGetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DSGetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_DSGetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DSGetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_GSGetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_GSGetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *first_constant, UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_GSGetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_GSGETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_GSGetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_GSGetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_GSGetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_GSGetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_PSGetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_PSGetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *first_constant, UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_PSGetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_PSGETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_PSGetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_PSGetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_PSGetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_PSGetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_CSGetConstantBuffers1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t first_constant;
    uint64_t num_constants;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_CSGetConstantBuffers1(ID3D11DeviceContext1 *iface, UINT start_slot, UINT buffer_count, ID3D11Buffer **buffers, UINT *first_constant, UINT *num_constants)
{
    struct qemu_d3d11_immediate_context_CSGetConstantBuffers1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CSGETCONSTANTBUFFERS1);
    call.iface = (ULONG_PTR)context;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.buffers = (ULONG_PTR)buffers;
    call.first_constant = (ULONG_PTR)first_constant;
    call.num_constants = (ULONG_PTR)num_constants;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_CSGetConstantBuffers1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_CSGetConstantBuffers1 *c = (struct qemu_d3d11_immediate_context_CSGetConstantBuffers1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_CSGetConstantBuffers1(context->host, c->start_slot, c->buffer_count, QEMU_G2H(c->buffers), QEMU_G2H(c->first_constant), QEMU_G2H(c->num_constants));
}

#endif

struct qemu_d3d11_immediate_context_SwapDeviceContextState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t prev_state;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_SwapDeviceContextState(ID3D11DeviceContext1 *iface, ID3DDeviceContextState *state, ID3DDeviceContextState **prev_state)
{
    struct qemu_d3d11_immediate_context_SwapDeviceContextState call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_SWAPDEVICECONTEXTSTATE);
    call.iface = (ULONG_PTR)context;
    call.state = (ULONG_PTR)state;
    call.prev_state = (ULONG_PTR)prev_state;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_SwapDeviceContextState(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_SwapDeviceContextState *c = (struct qemu_d3d11_immediate_context_SwapDeviceContextState *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_SwapDeviceContextState(context->host, QEMU_G2H(c->state), QEMU_G2H(c->prev_state));
}

#endif

struct qemu_d3d11_immediate_context_ClearView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view;
    uint64_t color;
    uint64_t rect;
    uint64_t num_rects;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_ClearView(ID3D11DeviceContext1 *iface, ID3D11View *view,
        const FLOAT color[4], const D3D11_RECT *rect, UINT num_rects)
{
    struct qemu_d3d11_immediate_context_ClearView call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_CLEARVIEW);
    call.iface = (ULONG_PTR)context;
    call.view = (ULONG_PTR)view;
    call.color = (ULONG_PTR)color;
    call.rect = (ULONG_PTR)rect;
    call.num_rects = num_rects;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_ClearView(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_ClearView *c = (struct qemu_d3d11_immediate_context_ClearView *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_ClearView(context->host, QEMU_G2H(c->view), QEMU_G2H(c->color), QEMU_G2H(c->rect), c->num_rects);
}

#endif

struct qemu_d3d11_immediate_context_DiscardView1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view;
    uint64_t rects;
    uint64_t num_rects;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_immediate_context_DiscardView1(ID3D11DeviceContext1 *iface, ID3D11View *view, const D3D11_RECT *rects, UINT num_rects)
{
    struct qemu_d3d11_immediate_context_DiscardView1 call;
    struct qemu_d3d11_device_context *context = impl_from_ID3D11DeviceContext1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_IMMEDIATE_CONTEXT_DISCARDVIEW1);
    call.iface = (ULONG_PTR)context;
    call.view = (ULONG_PTR)view;
    call.rects = (ULONG_PTR)rects;
    call.num_rects = num_rects;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_immediate_context_DiscardView1(struct qemu_syscall *call)
{
    struct qemu_d3d11_immediate_context_DiscardView1 *c = (struct qemu_d3d11_immediate_context_DiscardView1 *)call;
    struct qemu_d3d11_device_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_DiscardView1(context->host, QEMU_G2H(c->view), QEMU_G2H(c->rects), c->num_rects);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_QueryInterface(ID3D11Device2 *iface, REFIID riid, void **out)
{
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    return IUnknown_QueryInterface(device->outer_unk, riid, out);
}

static ULONG STDMETHODCALLTYPE d3d11_device_AddRef(ID3D11Device2 *iface)
{
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    return IUnknown_AddRef(device->outer_unk);
}

static ULONG STDMETHODCALLTYPE d3d11_device_Release(ID3D11Device2 *iface)
{
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    return IUnknown_Release(device->outer_unk);
}

#endif

struct qemu_d3d11_device_CreateBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t data;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateBuffer(ID3D11Device2 *iface, const D3D11_BUFFER_DESC *desc,
        const D3D11_SUBRESOURCE_DATA *data, ID3D11Buffer **buffer)
{
    struct qemu_d3d11_device_CreateBuffer call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_buffer *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEBUFFER);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_buffer *)(ULONG_PTR)call.buffer;
    qemu_d3d11_buffer_guest_init(obj);
    *buffer = &obj->ID3D11Buffer_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateBuffer(ID3D10Device1 *iface,
        const D3D10_BUFFER_DESC *desc, const D3D10_SUBRESOURCE_DATA *data, ID3D10Buffer **buffer)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D11_BUFFER_DESC d3d11_desc;
    ID3D11Buffer *buffer11;
    HRESULT hr;

    WINE_TRACE("iface %p, desc %p, data %p, buffer %p.\n", iface, desc, data, buffer);

    d3d11_desc.ByteWidth = desc->ByteWidth;
    d3d11_desc.Usage = d3d11_usage_from_d3d10_usage(desc->Usage);
    d3d11_desc.BindFlags = d3d11_bind_flags_from_d3d10_bind_flags(desc->BindFlags);
    d3d11_desc.CPUAccessFlags = d3d11_cpu_access_flags_from_d3d10_cpu_access_flags(desc->CPUAccessFlags);
    d3d11_desc.MiscFlags = d3d11_resource_misc_flags_from_d3d10_resource_misc_flags(desc->MiscFlags);
    d3d11_desc.StructureByteStride = 0;

    hr = d3d11_device_CreateBuffer(&device->ID3D11Device2_iface, &d3d11_desc,
            (const D3D11_SUBRESOURCE_DATA *)data, &buffer11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11Buffer_QueryInterface(buffer11, &IID_ID3D10Buffer, (void **)buffer);
    ID3D11Buffer_Release(buffer11);
    return hr;
}


#else

void qemu_d3d11_device_CreateBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateBuffer *c = (struct qemu_d3d11_device_CreateBuffer *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_buffer *obj;
    ID3D11Buffer *host;

    D3D11_SUBRESOURCE_DATA stack, *data = &stack;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->data);
#else
    if (c->data)
        D3D11_SUBRESOURCE_DATA_g2h(data, QEMU_G2H(c->data));
    else
        data = NULL;
#endif

    c->super.iret = ID3D11Device2_CreateBuffer(device->host_d3d11, QEMU_G2H(c->desc), data, &host);
    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_buffer_create(host, &obj);
    if (FAILED(c->super.iret))
        ID3D11Buffer_Release(host);

    c->buffer = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateTexture1D
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t data;
    uint64_t texture;
    uint64_t dxgi_surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateTexture1D(ID3D11Device2 *iface, const D3D11_TEXTURE1D_DESC *desc,
        const D3D11_SUBRESOURCE_DATA *data, ID3D11Texture1D **texture)
{
    struct qemu_d3d11_device_CreateTexture1D call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_texture *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATETEXTURE1D);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_texture *)(ULONG_PTR)call.texture;
    qemu_d3d11_texture_guest_init(obj, device, 1, call.dxgi_surface);
    *texture = &obj->ID3D11Texture1D_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateTexture1D(ID3D10Device1 *iface,
        const D3D10_TEXTURE1D_DESC *desc, const D3D10_SUBRESOURCE_DATA *data, ID3D10Texture1D **texture)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D11_TEXTURE1D_DESC d3d11_desc;
    ID3D11Texture1D *tex11;
    HRESULT hr;

    WINE_TRACE("iface %p, desc %p, data %p, texture %p.\n", iface, desc, data, texture);

    d3d11_desc.Width = desc->Width;
    d3d11_desc.MipLevels = desc->MipLevels;
    d3d11_desc.ArraySize = desc->ArraySize;
    d3d11_desc.Format = desc->Format;
    d3d11_desc.Usage = d3d11_usage_from_d3d10_usage(desc->Usage);
    d3d11_desc.BindFlags = d3d11_bind_flags_from_d3d10_bind_flags(desc->BindFlags);
    d3d11_desc.CPUAccessFlags = d3d11_cpu_access_flags_from_d3d10_cpu_access_flags(desc->CPUAccessFlags);
    d3d11_desc.MiscFlags = d3d11_resource_misc_flags_from_d3d10_resource_misc_flags(desc->MiscFlags);

    hr = d3d11_device_CreateTexture1D(&device->ID3D11Device2_iface, &d3d11_desc,
            (const D3D11_SUBRESOURCE_DATA *)data, &tex11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11Texture2D_QueryInterface(tex11, &IID_ID3D10Texture1D, (void **)texture);
    ID3D11Texture2D_Release(tex11);
    return hr;
}

#else

void qemu_d3d11_device_CreateTexture1D(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateTexture1D *c = (struct qemu_d3d11_device_CreateTexture1D *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_texture *obj;
    ID3D11Texture1D *host;
    D3D11_SUBRESOURCE_DATA *data;
    UINT i;
    D3D11_TEXTURE1D_DESC *desc, desc_out;
    struct qemu_D3D11_SUBRESOURCE_DATA *data32;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    desc = QEMU_G2H(c->desc);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->data);
#else
    data32 = QEMU_G2H(c->data);
    if (data32)
    {
        /* We have to know how many subresources there are to convert the data pointers. */
        c->super.iret = ID3D11Device2_CreateTexture1D(device->host_d3d11, desc, NULL, &host);
        if (FAILED(c->super.iret))
            return;

        ID3D11Texture1D_GetDesc(host, &desc_out);
        ID3D11Texture1D_Release(host);

        WINE_TRACE("Converting %u D3D11_SUBRESOURCE_DATA structs.\n", desc_out.MipLevels * desc_out.ArraySize);
        data = HeapAlloc(GetProcessHeap(), 0, sizeof(*data) * desc_out.MipLevels * desc_out.ArraySize);
        if (!data)
            WINE_ERR("Out of memory.\n");

        for (i = 0; i < desc_out.MipLevels * desc_out.ArraySize; ++i)
            D3D11_SUBRESOURCE_DATA_g2h(&data[i], &data32[i]);
    }
    else
    {
        data = NULL;
    }
#endif

    c->super.iret = ID3D11Device2_CreateTexture1D(device->host_d3d11, desc, data, &host);

#if GUEST_BIT != HOST_BIT
    if (data32)
        HeapFree(GetProcessHeap(), 0, data);
#endif

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_texture_create((ID3D11Resource *)host, device, &c->dxgi_surface, 1, &obj);
    if (FAILED(c->super.iret))
        ID3D11Texture1D_Release(host);

    c->texture = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateTexture2D
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t data;
    uint64_t texture;
    uint64_t dxgi_surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateTexture2D(ID3D11Device2 *iface, const D3D11_TEXTURE2D_DESC *desc,
        const D3D11_SUBRESOURCE_DATA *data, ID3D11Texture2D **texture)
{
    struct qemu_d3d11_device_CreateTexture2D call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_texture *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATETEXTURE2D);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_texture *)(ULONG_PTR)call.texture;
    qemu_d3d11_texture_guest_init(obj, device, 2, call.dxgi_surface);
    *texture = &obj->ID3D11Texture2D_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateTexture2D(ID3D10Device1 *iface, const D3D10_TEXTURE2D_DESC *desc,
        const D3D10_SUBRESOURCE_DATA *data, ID3D10Texture2D **texture)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11Texture2D *tex11;
    HRESULT hr;
    D3D11_TEXTURE2D_DESC d3d11_desc;

    WINE_TRACE("iface %p, desc %p, data %p, texture %p.\n", iface, desc, data, texture);

    d3d11_desc.Width = desc->Width;
    d3d11_desc.Height = desc->Height;
    d3d11_desc.MipLevels = desc->MipLevels;
    d3d11_desc.ArraySize = desc->ArraySize;
    d3d11_desc.Format = desc->Format;
    d3d11_desc.SampleDesc = desc->SampleDesc;
    d3d11_desc.Usage = d3d11_usage_from_d3d10_usage(desc->Usage);
    d3d11_desc.BindFlags = d3d11_bind_flags_from_d3d10_bind_flags(desc->BindFlags);
    d3d11_desc.CPUAccessFlags = d3d11_cpu_access_flags_from_d3d10_cpu_access_flags(desc->CPUAccessFlags);
    d3d11_desc.MiscFlags = d3d11_resource_misc_flags_from_d3d10_resource_misc_flags(desc->MiscFlags);

    hr = d3d11_device_CreateTexture2D(&device->ID3D11Device2_iface, &d3d11_desc,
            (const D3D11_SUBRESOURCE_DATA *)data, &tex11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11Texture2D_QueryInterface(tex11, &IID_ID3D10Texture2D, (void **)texture);
    ID3D11Texture2D_Release(tex11);
    return hr;
}

#else

void qemu_d3d11_device_CreateTexture2D(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateTexture2D *c = (struct qemu_d3d11_device_CreateTexture2D *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_texture *obj;
    ID3D11Texture2D *host;
    D3D11_SUBRESOURCE_DATA *data;
    UINT i;
    D3D11_TEXTURE2D_DESC *desc, desc_out;
    struct qemu_D3D11_SUBRESOURCE_DATA *data32;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    desc = QEMU_G2H(c->desc);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->data);
#else
    data32 = QEMU_G2H(c->data);
    if (data32)
    {
        /* We have to know how many subresources there are to convert the data pointers. */
        c->super.iret = ID3D11Device2_CreateTexture2D(device->host_d3d11, desc, NULL, &host);
        if (FAILED(c->super.iret))
            return;

        ID3D11Texture2D_GetDesc(host, &desc_out);
        ID3D11Texture2D_Release(host);

        WINE_TRACE("Converting %u D3D11_SUBRESOURCE_DATA structs.\n", desc_out.MipLevels * desc_out.ArraySize);
        data = HeapAlloc(GetProcessHeap(), 0, sizeof(*data) * desc_out.MipLevels * desc_out.ArraySize);
        if (!data)
            WINE_ERR("Out of memory.\n");

        for (i = 0; i < desc_out.MipLevels * desc_out.ArraySize; ++i)
            D3D11_SUBRESOURCE_DATA_g2h(&data[i], &data32[i]);
    }
    else
    {
        data = NULL;
    }
#endif

    c->super.iret = ID3D11Device2_CreateTexture2D(device->host_d3d11, desc, data, &host);

#if GUEST_BIT != HOST_BIT
    if (data32)
        HeapFree(GetProcessHeap(), 0, data);
#endif

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_texture_create((ID3D11Resource *)host, device, &c->dxgi_surface, 2, &obj);
    if (FAILED(c->super.iret))
        ID3D11Texture2D_Release(host);

    c->texture = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateTexture3D
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t data;
    uint64_t texture;
    uint64_t dxgi_surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateTexture3D(ID3D11Device2 *iface, const D3D11_TEXTURE3D_DESC *desc,
        const D3D11_SUBRESOURCE_DATA *data, ID3D11Texture3D **texture)
{
    struct qemu_d3d11_device_CreateTexture3D call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_texture *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATETEXTURE3D);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_texture *)(ULONG_PTR)call.texture;
    qemu_d3d11_texture_guest_init(obj, device, 3, call.dxgi_surface);
    *texture = &obj->ID3D11Texture3D_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateTexture3D(ID3D10Device1 *iface, const D3D10_TEXTURE3D_DESC *desc,
        const D3D10_SUBRESOURCE_DATA *data, ID3D10Texture3D **texture)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D11_TEXTURE3D_DESC d3d11_desc;
    ID3D11Texture3D *tex11;
    HRESULT hr;

    WINE_TRACE("iface %p, desc %p, data %p, texture %p.\n", iface, desc, data, texture);

    d3d11_desc.Width = desc->Width;
    d3d11_desc.Height = desc->Height;
    d3d11_desc.Depth = desc->Depth;
    d3d11_desc.MipLevels = desc->MipLevels;
    d3d11_desc.Format = desc->Format;
    d3d11_desc.Usage = d3d11_usage_from_d3d10_usage(desc->Usage);
    d3d11_desc.BindFlags = d3d11_bind_flags_from_d3d10_bind_flags(desc->BindFlags);
    d3d11_desc.CPUAccessFlags = d3d11_cpu_access_flags_from_d3d10_cpu_access_flags(desc->CPUAccessFlags);
    d3d11_desc.MiscFlags = d3d11_resource_misc_flags_from_d3d10_resource_misc_flags(desc->MiscFlags);

    hr = d3d11_device_CreateTexture3D(&device->ID3D11Device2_iface, &d3d11_desc,
            (const D3D11_SUBRESOURCE_DATA *)data, &tex11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11Texture3D_QueryInterface(tex11, &IID_ID3D10Texture3D, (void **)texture);
    ID3D11Texture3D_Release(tex11);
    return hr;
}

#else

void qemu_d3d11_device_CreateTexture3D(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateTexture3D *c = (struct qemu_d3d11_device_CreateTexture3D *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_texture *obj;
    ID3D11Texture3D *host;
    D3D11_SUBRESOURCE_DATA *data;
    UINT i;
    D3D11_TEXTURE3D_DESC *desc, desc_out;
    struct qemu_D3D11_SUBRESOURCE_DATA *data32;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    desc = QEMU_G2H(c->desc);

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->data);
#else
    data32 = QEMU_G2H(c->data);
    if (data32)
    {
        /* We have to know how many subresources there are to convert the data pointers. */
        c->super.iret = ID3D11Device2_CreateTexture3D(device->host_d3d11, desc, NULL, &host);
        if (FAILED(c->super.iret))
            return;

        ID3D11Texture3D_GetDesc(host, &desc_out);
        ID3D11Texture3D_Release(host);

        WINE_TRACE("Converting %u D3D11_SUBRESOURCE_DATA structs.\n", desc_out.MipLevels);
        data = HeapAlloc(GetProcessHeap(), 0, sizeof(*data) * desc_out.MipLevels);
        if (!data)
            WINE_ERR("Out of memory.\n");

        for (i = 0; i < desc_out.MipLevels; ++i)
            D3D11_SUBRESOURCE_DATA_g2h(&data[i], &data32[i]);
    }
    else
    {
        data = NULL;
    }
#endif

    c->super.iret = ID3D11Device2_CreateTexture3D(device->host_d3d11, desc, data, &host);

#if GUEST_BIT != HOST_BIT
    if (data32)
        HeapFree(GetProcessHeap(), 0, data);
#endif

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_texture_create((ID3D11Resource *)host, device, &c->dxgi_surface, 3, &obj);
    if (FAILED(c->super.iret))
        ID3D11Texture3D_Release(host);

    c->texture = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateShaderResourceView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t desc;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateShaderResourceView(ID3D11Device2 *iface, ID3D11Resource *resource,
        const D3D11_SHADER_RESOURCE_VIEW_DESC *desc, ID3D11ShaderResourceView **view)
{
    struct qemu_d3d11_device_CreateShaderResourceView call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_view *obj;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_texture *texture;
    ID3D11Buffer *buffer_iface;
    ID3D11Texture1D *tex1d_iface;
    ID3D11Texture2D *tex2d_iface;
    ID3D11Texture3D *tex3d_iface;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATESHADERRESOURCEVIEW);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    if (!resource)
    {
        call.buffer = call.texture = 0;
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Buffer, (void **)&buffer_iface)))
    {
        call.texture = 0;
        call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffer_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture1D, (void **)&tex1d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D(tex1d_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture2D, (void **)&tex2d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D(tex2d_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture3D, (void **)&tex3d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D(tex3d_iface);
        /* Release on the host side */
    }

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_view *)(ULONG_PTR)call.view;
    qemu_d3d11_shader_resource_view_guest_init(obj);
    *view = &obj->ID3D11ShaderResourceView_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateShaderResourceView(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateShaderResourceView *c = (struct qemu_d3d11_device_CreateShaderResourceView *)call;
    struct qemu_d3d11_device *device;
    ID3D11Resource *resource = NULL;
    ID3D11ShaderResourceView *host;
    struct qemu_d3d11_view *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->buffer)
    {
        struct qemu_d3d11_buffer *buffer = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buffer->host11;
    }
    else if (c->texture)
    {
        struct qemu_d3d11_texture *texture = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)texture->host11_1d;
    }

    c->super.iret = ID3D11Device2_CreateShaderResourceView(device->host_d3d11, resource, QEMU_G2H(c->desc), &host);

    /* For the QI we did inside the guest. */
    if (resource)
        ID3D11Resource_Release(resource);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_view_create((ID3D11View *)host, &IID_ID3D10ShaderResourceView, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11ShaderResourceView_Release(host);
        return;
    }
    c->view = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateUnorderedAccessView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t texture;
    uint64_t buffer;
    uint64_t desc;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateUnorderedAccessView(ID3D11Device2 *iface,
        ID3D11Resource *resource, const D3D11_UNORDERED_ACCESS_VIEW_DESC *desc, ID3D11UnorderedAccessView **view)
{
    struct qemu_d3d11_device_CreateUnorderedAccessView call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    D3D11_RESOURCE_DIMENSION dim;
    struct qemu_d3d11_view *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEUNORDEREDACCESSVIEW);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    ID3D11Resource_GetType(resource, &dim);
    switch (dim)
    {
        case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D((ID3D11Texture1D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D((ID3D11Texture2D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D((ID3D11Texture3D *)resource);
            break;

        case D3D11_RESOURCE_DIMENSION_BUFFER:
            call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer((ID3D11Buffer *)resource);
            call.texture = 0;
            break;
    }

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_view *)(ULONG_PTR)call.view;
    qemu_d3d11_unordered_access_view_guest_init(obj);
    *view = &obj->ID3D11UnorderedAccessView_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateUnorderedAccessView(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateUnorderedAccessView *c = (struct qemu_d3d11_device_CreateUnorderedAccessView *)call;
    struct qemu_d3d11_device *device;
    ID3D11Resource *resource;
    ID3D11UnorderedAccessView *host;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->buffer)
    {
        buf = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buf->host11;
    }
    else
    {
        tex = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)tex->host11_1d;
    }

    c->super.iret = ID3D11Device2_CreateUnorderedAccessView(device->host_d3d11, resource, QEMU_G2H(c->desc), &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_view_create((ID3D11View *)host, NULL, &view);
    if (FAILED(c->super.iret))
    {
        ID3D11UnorderedAccessView_Release(host);
        return;
    }

    c->view = QEMU_H2G(view);
}

#endif

struct qemu_d3d11_device_CreateRenderTargetView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t desc;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateRenderTargetView(ID3D11Device2 *iface, ID3D11Resource *resource,
        const D3D11_RENDER_TARGET_VIEW_DESC *desc, ID3D11RenderTargetView **view)
{
    struct qemu_d3d11_device_CreateRenderTargetView call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_view *obj;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_texture *texture;
    ID3D11Buffer *buffer_iface;
    ID3D11Texture1D *tex1d_iface;
    ID3D11Texture2D *tex2d_iface;
    ID3D11Texture3D *tex3d_iface;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATERENDERTARGETVIEW);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    if (!resource)
    {
        call.buffer = call.texture = 0;
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Buffer, (void **)&buffer_iface)))
    {
        call.texture = 0;
        call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffer_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture1D, (void **)&tex1d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D(tex1d_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture2D, (void **)&tex2d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D(tex2d_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture3D, (void **)&tex3d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D(tex3d_iface);
        /* Release on the host side */
    }

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_view *)(ULONG_PTR)call.view;
    qemu_d3d11_render_target_view_guest_init(obj);
    *view = &obj->ID3D11RenderTargetView_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateRenderTargetView(ID3D10Device1 *iface, ID3D10Resource *resource, const D3D10_RENDER_TARGET_VIEW_DESC *desc, ID3D10RenderTargetView **view)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11Resource *d3d11_resource;
    ID3D11RenderTargetView *view11;
    HRESULT hr;

    WINE_TRACE("iface %p, resource %p, desc %p, view %p.\n", iface, resource, desc, view);

    if (!resource)
        return E_INVALIDARG;

    if (FAILED(hr = ID3D10Resource_QueryInterface(resource, &IID_ID3D11Resource, (void **)&d3d11_resource)))
    {
        WINE_ERR("Resource does not implement ID3D11Resource.\n");
        return E_FAIL;
    }

    hr = d3d11_device_CreateRenderTargetView(&device->ID3D11Device2_iface, d3d11_resource,
            (const D3D11_RENDER_TARGET_VIEW_DESC *)desc, &view11);
    ID3D11Resource_Release(d3d11_resource);
    if (FAILED(hr))
        return hr;

    hr = ID3D11RenderTargetView_QueryInterface(view11, &IID_ID3D10RenderTargetView, (void **)view);
    ID3D11RenderTargetView_Release(view11);
    return hr;
}

#else

void qemu_d3d11_device_CreateRenderTargetView(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateRenderTargetView *c = (struct qemu_d3d11_device_CreateRenderTargetView *)call;
    struct qemu_d3d11_device *device;
    ID3D11Resource *resource = NULL;
    ID3D11RenderTargetView *host;
    struct qemu_d3d11_view *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->buffer)
    {
        struct qemu_d3d11_buffer *buffer = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buffer->host11;
    }
    else if (c->texture)
    {
        struct qemu_d3d11_texture *texture = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)texture->host11_1d;
    }

    c->super.iret = ID3D11Device2_CreateRenderTargetView(device->host_d3d11, resource, QEMU_G2H(c->desc), &host);

    /* For the QI we did inside the guest. */
    if (resource)
        ID3D11Resource_Release(resource);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_view_create((ID3D11View *)host, &IID_ID3D10RenderTargetView, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11RenderTargetView_Release(host);
        return;
    }
    c->view = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateDepthStencilView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t desc;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDepthStencilView(ID3D11Device2 *iface, ID3D11Resource *resource,
        const D3D11_DEPTH_STENCIL_VIEW_DESC *desc, ID3D11DepthStencilView **view)
{
    struct qemu_d3d11_device_CreateDepthStencilView call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_view *obj;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_texture *texture;
    ID3D11Buffer *buffer_iface;
    ID3D11Texture1D *tex1d_iface;
    ID3D11Texture2D *tex2d_iface;
    ID3D11Texture3D *tex3d_iface;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDEPTHSTENCILVIEW);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    if (!resource)
    {
        call.buffer = call.texture = 0;
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Buffer, (void **)&buffer_iface)))
    {
        call.texture = 0;
        call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D11Buffer(buffer_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture1D, (void **)&tex1d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture1D(tex1d_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture2D, (void **)&tex2d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture2D(tex2d_iface);
        /* Release on the host side */
    }
    else if (SUCCEEDED(hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture3D, (void **)&tex3d_iface)))
    {
        call.buffer = 0;
        call.texture = (ULONG_PTR)unsafe_impl_from_ID3D11Texture3D(tex3d_iface);
        /* Release on the host side */
    }

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_view *)(ULONG_PTR)call.view;
    qemu_d3d11_depth_stencil_view_guest_init(obj);
    *view = &obj->ID3D11DepthStencilView_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateDepthStencilView(ID3D10Device1 *iface, ID3D10Resource *resource,
        const D3D10_DEPTH_STENCIL_VIEW_DESC *desc, ID3D10DepthStencilView **view)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D11_DEPTH_STENCIL_VIEW_DESC d3d11_desc;
    ID3D11DepthStencilView *view11;
    ID3D11Resource *d3d11_resource;
    HRESULT hr;

    WINE_TRACE("iface %p, resource %p, desc %p, view %p.\n", iface, resource, desc, view);

    if (desc)
    {
        d3d11_desc.Format = desc->Format;
        d3d11_desc.ViewDimension = desc->ViewDimension;
        d3d11_desc.Flags = 0;
        memcpy(&d3d11_desc.Texture2DArray, &desc->Texture2DArray, sizeof(d3d11_desc.Texture2DArray));
    }

    if (FAILED(hr = ID3D10Resource_QueryInterface(resource, &IID_ID3D11Resource, (void **)&d3d11_resource)))
    {
        WINE_ERR("Resource does not implement ID3D11Resource.\n");
        return E_FAIL;
    }

    hr = d3d11_device_CreateDepthStencilView(&device->ID3D11Device2_iface, d3d11_resource,
            desc ? &d3d11_desc : NULL, &view11);
    ID3D11Resource_Release(d3d11_resource);
    if (FAILED(hr))
        return hr;

    hr = ID3D11DepthStencilView_QueryInterface(view11, &IID_ID3D10DepthStencilView, (void **)view);
    ID3D11DepthStencilView_Release(view11);
    return hr;
}

#else

void qemu_d3d11_device_CreateDepthStencilView(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDepthStencilView *c = (struct qemu_d3d11_device_CreateDepthStencilView *)call;
    struct qemu_d3d11_device *device;
    ID3D11Resource *resource = NULL;
    ID3D11DepthStencilView *host;
    struct qemu_d3d11_view *obj;

    /* D3D11_DEPTH_STENCIL_VIEW_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->buffer)
    {
        struct qemu_d3d11_buffer *buffer = QEMU_G2H(c->buffer);
        resource = (ID3D11Resource *)buffer->host11;
    }
    else if (c->texture)
    {
        struct qemu_d3d11_texture *texture = QEMU_G2H(c->texture);
        resource = (ID3D11Resource *)texture->host11_1d;
    }

    c->super.iret = ID3D11Device2_CreateDepthStencilView(device->host_d3d11, resource, QEMU_G2H(c->desc), &host);

    /* For the QI we did inside the guest. */
    if (resource)
        ID3D11Resource_Release(resource);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_view_create((ID3D11View *)host, &IID_ID3D10DepthStencilView, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11DepthStencilView_Release(host);
        return;
    }
    c->view = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateInputLayout
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t element_descs;
    uint64_t element_count;
    uint64_t shader_byte_code;
    uint64_t shader_byte_code_length;
    uint64_t input_layout;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateInputLayout(ID3D11Device2 *iface,
        const D3D11_INPUT_ELEMENT_DESC *element_descs, UINT element_count,
        const void *shader_byte_code, SIZE_T shader_byte_code_length, ID3D11InputLayout **input_layout)
{
    struct qemu_d3d11_device_CreateInputLayout call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_input_layout *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEINPUTLAYOUT);
    call.iface = (ULONG_PTR)device;
    call.element_descs = (ULONG_PTR)element_descs;
    call.element_count = element_count;
    call.shader_byte_code = (ULONG_PTR)shader_byte_code;
    call.shader_byte_code_length = shader_byte_code_length;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_input_layout *)(ULONG_PTR)call.input_layout;
    qemu_d3d11_input_layout_guest_init(obj);
    *input_layout = &obj->ID3D11InputLayout_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateInputLayout(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateInputLayout *c = (struct qemu_d3d11_device_CreateInputLayout *)call;
    struct qemu_d3d11_device *device;
    D3D11_INPUT_ELEMENT_DESC stack[16], *desc = stack;
    struct qemu_D3D11_INPUT_ELEMENT_DESC *desc32;
    ID3D11InputLayout *host;
    struct qemu_d3d11_input_layout *obj;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    count = c->element_count;
#if GUEST_BIT == HOST_BIT
    desc = QEMU_G2H(c->element_descs);
#else
    desc32 = QEMU_G2H(c->element_descs);
    if (!desc32)
    {
        desc = NULL;
    }
    else
    {
        if (count > sizeof(stack) / sizeof(*stack))
        {
            desc = HeapAlloc(GetProcessHeap(), 0, c->element_count * sizeof(*desc));
            if (!desc)
                WINE_ERR("Out of memory\n");
        }

        for (i = 0; i < count; ++i)
            D3D11_INPUT_ELEMENT_DESC_g2h(&desc[i], &desc32[i]);
    }
#endif

    c->super.iret = ID3D11Device2_CreateInputLayout(device->host_d3d11, desc, count,
            QEMU_G2H(c->shader_byte_code), c->shader_byte_code_length, &host);

#if GUEST_BIT != HOST_BIT
    if (desc && desc != stack)
        HeapFree(GetProcessHeap(), 0, desc);
#endif

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_input_layout_create(host, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11InputLayout_Release(host);
        return;
    }
    c->input_layout = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateVertexShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateVertexShader(ID3D11Device2 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D11ClassLinkage *class_linkage, ID3D11VertexShader **shader)
{
    struct qemu_d3d11_device_CreateVertexShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEVERTEXSHADER);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_vertex_shader_guest_init(obj);
    *shader = &obj->ID3D11VertexShader_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateVertexShader(ID3D10Device1 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D10VertexShader **shader)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11VertexShader *shader11;
    HRESULT hr;

    hr = d3d11_device_CreateVertexShader(&device->ID3D11Device2_iface, byte_code, byte_code_length, NULL, &shader11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11VertexShader_QueryInterface(shader11, &IID_ID3D10VertexShader, (void **)shader);
    ID3D11VertexShader_Release(shader11);
    return hr;
}

#else

void qemu_d3d11_device_CreateVertexShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateVertexShader *c = (struct qemu_d3d11_device_CreateVertexShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11VertexShader *host;
    struct qemu_d3d11_shader *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

    c->super.iret = ID3D11Device2_CreateVertexShader(device->host_d3d11, QEMU_G2H(c->byte_code), c->byte_code_length,
            NULL, &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, &IID_ID3D10VertexShader, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11VertexShader_Release(host);
        return;
    }
    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateGeometryShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateGeometryShader(ID3D11Device2 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D11ClassLinkage *class_linkage, ID3D11GeometryShader **shader)
{
    struct qemu_d3d11_device_CreateGeometryShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEGEOMETRYSHADER);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_geometry_shader_guest_init(obj);
    *shader = &obj->ID3D11GeometryShader_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateGeometryShader(ID3D10Device1 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D10GeometryShader **shader)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11GeometryShader *shader11;
    HRESULT hr;

    hr = d3d11_device_CreateGeometryShader(&device->ID3D11Device2_iface, byte_code, byte_code_length, NULL, &shader11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11GeometryShader_QueryInterface(shader11, &IID_ID3D10GeometryShader, (void **)shader);
    ID3D11GeometryShader_Release(shader11);
    return hr;
}

#else

void qemu_d3d11_device_CreateGeometryShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateGeometryShader *c = (struct qemu_d3d11_device_CreateGeometryShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11GeometryShader *host;
    struct qemu_d3d11_shader *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

    c->super.iret = ID3D11Device2_CreateGeometryShader(device->host_d3d11, QEMU_G2H(c->byte_code), c->byte_code_length,
            NULL, &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, &IID_ID3D10GeometryShader, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11GeometryShader_Release(host);
        return;
    }
    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateGeometryShaderWithStreamOutput
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t so_entries;
    uint64_t entry_count;
    uint64_t buffer_strides;
    uint64_t strides_count;
    uint64_t rasterizer_stream;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateGeometryShaderWithStreamOutput(ID3D11Device2 *iface,
        const void *byte_code, SIZE_T byte_code_length, const D3D11_SO_DECLARATION_ENTRY *so_entries,
        UINT entry_count, const UINT *buffer_strides, UINT strides_count, UINT rasterizer_stream,
        ID3D11ClassLinkage *class_linkage, ID3D11GeometryShader **shader)
{
    struct qemu_d3d11_device_CreateGeometryShaderWithStreamOutput call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.so_entries = (ULONG_PTR)so_entries;
    call.entry_count = entry_count;
    call.buffer_strides = (ULONG_PTR)buffer_strides;
    call.strides_count = strides_count;
    call.rasterizer_stream = rasterizer_stream;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        *shader = NULL;
        return call.super.iret;
    }

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_geometry_shader_guest_init(obj);
    *shader = &obj->ID3D11GeometryShader_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateGeometryShaderWithStreamOutput(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateGeometryShaderWithStreamOutput *c =
            (struct qemu_d3d11_device_CreateGeometryShaderWithStreamOutput *)call;
    struct qemu_d3d11_device *device;
    ID3D11GeometryShader *host;
    struct qemu_d3d11_shader *obj;
    D3D11_SO_DECLARATION_ENTRY *so_decl;
    struct qemu_D3D11_SO_DECLARATION_ENTRY *so_decl32;
    UINT i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

#if GUEST_BIT == HOST_BIT
    so_decl = QEMU_G2H(c->so_entries);
#else
    so_decl32 = QEMU_G2H(c->so_entries);
    so_decl = HeapAlloc(GetProcessHeap(), 0, sizeof(*so_decl) * c->entry_count);
    if (!so_decl)
        WINE_ERR("Out of memory\n");

    for (i = 0; i < c->entry_count; ++i)
        D3D11_SO_DECLARATION_ENTRY_g2h(&so_decl[i], &so_decl32[i]);
#endif

    c->super.iret = ID3D11Device2_CreateGeometryShaderWithStreamOutput(device->host_d3d11, QEMU_G2H(c->byte_code),
            c->byte_code_length, so_decl, c->entry_count, QEMU_G2H(c->buffer_strides), c->strides_count,
            c->rasterizer_stream, QEMU_G2H(c->class_linkage), &host);

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, so_decl);
#endif

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, &IID_ID3D10GeometryShader, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11GeometryShader_Release(host);
        return;
    }

    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreatePixelShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreatePixelShader(ID3D11Device2 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D11ClassLinkage *class_linkage, ID3D11PixelShader **shader)
{
    struct qemu_d3d11_device_CreatePixelShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEPIXELSHADER);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_pixel_shader_guest_init(obj);
    *shader = &obj->ID3D11PixelShader_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreatePixelShader(ID3D10Device1 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D10PixelShader **shader)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11PixelShader *shader11;
    HRESULT hr;

    hr = d3d11_device_CreatePixelShader(&device->ID3D11Device2_iface, byte_code, byte_code_length, NULL, &shader11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11PixelShader_QueryInterface(shader11, &IID_ID3D10PixelShader, (void **)shader);
    ID3D11PixelShader_Release(shader11);
    return hr;
}

#else

void qemu_d3d11_device_CreatePixelShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreatePixelShader *c = (struct qemu_d3d11_device_CreatePixelShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11PixelShader *host;
    struct qemu_d3d11_shader *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

    c->super.iret = ID3D11Device2_CreatePixelShader(device->host_d3d11, QEMU_G2H(c->byte_code), c->byte_code_length,
            NULL, &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, &IID_ID3D10PixelShader, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11PixelShader_Release(host);
        return;
    }
    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateHullShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateHullShader(ID3D11Device2 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D11ClassLinkage *class_linkage, ID3D11HullShader **shader)
{
    struct qemu_d3d11_device_CreateHullShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEHULLSHADER);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_hull_shader_guest_init(obj);
    *shader = &obj->ID3D11HullShader_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateHullShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateHullShader *c = (struct qemu_d3d11_device_CreateHullShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11HullShader *host;
    struct qemu_d3d11_shader *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

    c->super.iret = ID3D11Device2_CreateHullShader(device->host_d3d11, QEMU_G2H(c->byte_code), c->byte_code_length,
            NULL, &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, NULL, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11HullShader_Release(host);
        return;
    }
    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateDomainShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDomainShader(ID3D11Device2 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D11ClassLinkage *class_linkage, ID3D11DomainShader **shader)
{
    struct qemu_d3d11_device_CreateDomainShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDOMAINSHADER);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_domain_shader_guest_init(obj);
    *shader = &obj->ID3D11DomainShader_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateDomainShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDomainShader *c = (struct qemu_d3d11_device_CreateDomainShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11DomainShader *host;
    struct qemu_d3d11_shader *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

    c->super.iret = ID3D11Device2_CreateDomainShader(device->host_d3d11, QEMU_G2H(c->byte_code),
            c->byte_code_length, NULL, &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, NULL, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11DomainShader_Release(host);
        return;
    }
    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateComputeShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t class_linkage;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateComputeShader(ID3D11Device2 *iface, const void *byte_code,
        SIZE_T byte_code_length, ID3D11ClassLinkage *class_linkage, ID3D11ComputeShader **shader)
{
    struct qemu_d3d11_device_CreateComputeShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_shader *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATECOMPUTESHADER);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    qemu_d3d11_compute_shader_guest_init(obj);
    *shader = &obj->ID3D11ComputeShader_iface;

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateComputeShader(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateComputeShader *c = (struct qemu_d3d11_device_CreateComputeShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11ComputeShader *host;
    struct qemu_d3d11_shader *obj;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->class_linkage)
        WINE_FIXME("Class linkage is not implemented yet.\n");

    c->super.iret = ID3D11Device2_CreateComputeShader(device->host_d3d11, QEMU_G2H(c->byte_code),
            c->byte_code_length, NULL, &host);

    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_d3d11_shader_create((ID3D11DeviceChild *)host, NULL, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11ComputeShader_Release(host);
        return;
    }
    c->shader = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateClassLinkage
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t class_linkage;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateClassLinkage(ID3D11Device2 *iface, ID3D11ClassLinkage **class_linkage)
{
    struct qemu_d3d11_device_CreateClassLinkage call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATECLASSLINKAGE);
    call.iface = (ULONG_PTR)device;
    call.class_linkage = (ULONG_PTR)class_linkage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateClassLinkage(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateClassLinkage *c = (struct qemu_d3d11_device_CreateClassLinkage *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateClassLinkage(device->host_d3d11, QEMU_G2H(c->class_linkage));
}

#endif

struct qemu_d3d11_device_CreateBlendState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t blend_state;
    uint64_t new_state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateBlendState(ID3D11Device2 *iface, const D3D11_BLEND_DESC *desc,
        ID3D11BlendState **blend_state)
{
    struct qemu_d3d11_device_CreateBlendState call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_state *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEBLENDSTATE);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_state *)(ULONG_PTR)call.blend_state;
    if (call.new_state)
        qemu_d3d11_blend_state_guest_init(obj);
    *blend_state = &obj->ID3D11BlendState_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateBlendState1(ID3D10Device1 *iface, const D3D10_BLEND_DESC1 *desc,
        ID3D10BlendState1 **blend_state)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11BlendState *state11;
    HRESULT hr;

    hr = d3d11_device_CreateBlendState(&device->ID3D11Device2_iface, (const D3D11_BLEND_DESC *)desc,
            &state11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11BlendState_QueryInterface(state11, &IID_ID3D10BlendState1, (void **)blend_state);
    ID3D11BlendState_Release(state11);
    return hr;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateBlendState(ID3D10Device1 *iface,
        const D3D10_BLEND_DESC *desc, ID3D10BlendState **blend_state)
{
    D3D10_BLEND_DESC1 d3d10_1_desc;
    unsigned int i;

    WINE_TRACE("iface %p, desc %p, blend_state %p.\n", iface, desc, blend_state);

    if (!desc)
        return E_INVALIDARG;

    d3d10_1_desc.AlphaToCoverageEnable = desc->AlphaToCoverageEnable;
    d3d10_1_desc.IndependentBlendEnable = FALSE;
    for (i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT - 1; ++i)
    {
        if (desc->BlendEnable[i] != desc->BlendEnable[i + 1]
                || desc->RenderTargetWriteMask[i] != desc->RenderTargetWriteMask[i + 1])
            d3d10_1_desc.IndependentBlendEnable = TRUE;
    }

    for (i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        d3d10_1_desc.RenderTarget[i].BlendEnable = desc->BlendEnable[i];
        d3d10_1_desc.RenderTarget[i].SrcBlend = desc->SrcBlend;
        d3d10_1_desc.RenderTarget[i].DestBlend = desc->DestBlend;
        d3d10_1_desc.RenderTarget[i].BlendOp = desc->BlendOp;
        d3d10_1_desc.RenderTarget[i].SrcBlendAlpha = desc->SrcBlendAlpha;
        d3d10_1_desc.RenderTarget[i].DestBlendAlpha = desc->DestBlendAlpha;
        d3d10_1_desc.RenderTarget[i].BlendOpAlpha = desc->BlendOpAlpha;
        d3d10_1_desc.RenderTarget[i].RenderTargetWriteMask = desc->RenderTargetWriteMask[i];
    }

    return d3d10_device_CreateBlendState1(iface, &d3d10_1_desc, (ID3D10BlendState1 **)blend_state);
}

#else

void qemu_d3d11_device_CreateBlendState(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateBlendState *c = (struct qemu_d3d11_device_CreateBlendState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *obj;
    ID3D11BlendState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateBlendState(device->host_d3d11, QEMU_G2H(c->desc), &host);

    if (FAILED(c->super.iret))
        return;

    if (!(obj = state_from_host((ID3D11DeviceChild *)host)))
    {
        c->super.iret = qemu_d3d11_state_create((ID3D11DeviceChild *)host, &IID_ID3D10BlendState1, &obj);
        if (FAILED(c->super.iret))
        {
            ID3D11BlendState_Release(host);
            return;
        }
        c->new_state = 1;
    }
    else
    {
        c->new_state = 0;
    }

    c->blend_state = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateDepthStencilState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t depth_stencil_state;
    uint64_t new_state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDepthStencilState(ID3D11Device2 *iface,
            const D3D11_DEPTH_STENCIL_DESC *desc, ID3D11DepthStencilState **depth_stencil_state)
{
    struct qemu_d3d11_device_CreateDepthStencilState call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_state *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDEPTHSTENCILSTATE);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_state *)(ULONG_PTR)call.depth_stencil_state;
    if (call.new_state)
        qemu_d3d11_depthstencil_state_guest_init(obj);
    *depth_stencil_state = &obj->ID3D11DepthStencilState_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateDepthStencilState(ID3D10Device1 *iface,
        const D3D10_DEPTH_STENCIL_DESC *desc, ID3D10DepthStencilState **depth_stencil_state)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11DepthStencilState *state11;
    HRESULT hr;

    hr = d3d11_device_CreateDepthStencilState(&device->ID3D11Device2_iface, (const D3D11_DEPTH_STENCIL_DESC *)desc,
            &state11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11DepthStencilState_QueryInterface(state11, &IID_ID3D10DepthStencilState, (void **)depth_stencil_state);
    ID3D11DepthStencilState_Release(state11);
    return hr;
}

#else

void qemu_d3d11_device_CreateDepthStencilState(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDepthStencilState *c = (struct qemu_d3d11_device_CreateDepthStencilState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *obj;
    ID3D11DepthStencilState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateDepthStencilState(device->host_d3d11, QEMU_G2H(c->desc), &host);

    if (FAILED(c->super.iret))
        return;

    if (!(obj = state_from_host((ID3D11DeviceChild *)host)))
    {
        c->super.iret = qemu_d3d11_state_create((ID3D11DeviceChild *)host, &IID_ID3D10DepthStencilState, &obj);
        if (FAILED(c->super.iret))
        {
            ID3D11DepthStencilState_Release(host);
            return;
        }
        c->new_state = 1;
    }
    else
    {
        c->new_state = 0;
    }

    c->depth_stencil_state = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateRasterizerState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t rasterizer_state;
    uint64_t new_state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateRasterizerState(ID3D11Device2 *iface,
        const D3D11_RASTERIZER_DESC *desc, ID3D11RasterizerState **rasterizer_state)
{
    struct qemu_d3d11_device_CreateRasterizerState call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_state *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATERASTERIZERSTATE);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_state *)(ULONG_PTR)call.rasterizer_state;
    if (call.new_state)
        qemu_d3d11_rasterizer_state_guest_init(obj);
    *rasterizer_state = &obj->ID3D11RasterizerState_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateRasterizerState(ID3D10Device1 *iface,
        const D3D10_RASTERIZER_DESC *desc, ID3D10RasterizerState **rasterizer_state)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11RasterizerState *state11;
    HRESULT hr;

    hr = d3d11_device_CreateRasterizerState(&device->ID3D11Device2_iface, (const D3D11_RASTERIZER_DESC *)desc,
            &state11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11RasterizerState_QueryInterface(state11, &IID_ID3D10RasterizerState, (void **)rasterizer_state);
    ID3D11RasterizerState_Release(state11);
    return hr;
}

#else

void qemu_d3d11_device_CreateRasterizerState(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateRasterizerState *c = (struct qemu_d3d11_device_CreateRasterizerState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *obj;
    ID3D11RasterizerState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateRasterizerState(device->host_d3d11, QEMU_G2H(c->desc), &host);

    if (FAILED(c->super.iret))
        return;

    if (!(obj = state_from_host((ID3D11DeviceChild *)host)))
    {
        c->super.iret = qemu_d3d11_state_create((ID3D11DeviceChild *)host, &IID_ID3D10RasterizerState, &obj);
        if (FAILED(c->super.iret))
        {
            ID3D11RasterizerState_Release(host);
            return;
        }
        c->new_state = 1;
    }
    else
    {
        c->new_state = 0;
    }

    c->rasterizer_state = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateSamplerState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t sampler_state;
    uint64_t new;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateSamplerState(ID3D11Device2 *iface, const D3D11_SAMPLER_DESC *desc,
        ID3D11SamplerState **sampler_state)
{
    struct qemu_d3d11_device_CreateSamplerState call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_state *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATESAMPLERSTATE);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_d3d11_state *)(ULONG_PTR)call.sampler_state;
    if (call.new)
        qemu_d3d11_sampler_state_guest_init(obj);
    *sampler_state = &obj->ID3D11SamplerState_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateSamplerState(ID3D10Device1 *iface,
        const D3D10_SAMPLER_DESC *desc, ID3D10SamplerState **sampler_state)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11SamplerState *state11;
    HRESULT hr;

    hr = d3d11_device_CreateSamplerState(&device->ID3D11Device2_iface, (const D3D11_SAMPLER_DESC *)desc,
            &state11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11SamplerState_QueryInterface(state11, &IID_ID3D10SamplerState, (void **)sampler_state);
    ID3D11SamplerState_Release(state11);
    return hr;
}

#else

void qemu_d3d11_device_CreateSamplerState(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateSamplerState *c = (struct qemu_d3d11_device_CreateSamplerState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *obj;
    ID3D11SamplerState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateSamplerState(device->host_d3d11, QEMU_G2H(c->desc), &host);

    if (FAILED(c->super.iret))
        return;

    if (!(obj = state_from_host((ID3D11DeviceChild *)host)))
    {
        c->super.iret = qemu_d3d11_state_create((ID3D11DeviceChild *)host, &IID_ID3D10SamplerState, &obj);
        if (FAILED(c->super.iret))
        {
            ID3D11SamplerState_Release(host);
            return;
        }
        c->new = 1;
    }
    else
    {
        c->new = 0;
    }

    c->sampler_state = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateQuery
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t query;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateQuery(ID3D11Device2 *iface, const D3D11_QUERY_DESC *desc,
        ID3D11Query **query)
{
    struct qemu_d3d11_device_CreateQuery call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_query *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEQUERY);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.query = (ULONG_PTR)query;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret) || !query)
        return call.super.iret;

    obj = (struct qemu_d3d11_query *)(ULONG_PTR)call.query;
    qemu_d3d11_query_guest_init(obj);
    *query = &obj->ID3D11Query_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateQuery(ID3D10Device1 *iface,
        const D3D10_QUERY_DESC *desc, ID3D10Query **query)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11Query *query11;
    HRESULT hr;

    hr = d3d11_device_CreateQuery(&device->ID3D11Device2_iface, (const D3D11_QUERY_DESC *)desc,
            query ? &query11 : NULL);
    if (FAILED(hr) || !query)
        return hr;

    hr = ID3D11Query_QueryInterface(query11, &IID_ID3D10Query, (void **)query);
    ID3D11Query_Release(query11);
    return hr;
}

#else

void qemu_d3d11_device_CreateQuery(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateQuery *c = (struct qemu_d3d11_device_CreateQuery *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_query *obj;
    ID3D11Query *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateQuery(device->host_d3d11, QEMU_G2H(c->desc), c->query ? &host : NULL);

    if (FAILED(c->super.iret) || !c->query)
        return;

    c->super.iret = qemu_d3d11_query_create(host, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11Query_Release(host);
        return;
    }
    c->query = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreatePredicate
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t predicate;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreatePredicate(ID3D11Device2 *iface, const D3D11_QUERY_DESC *desc,
        ID3D11Predicate **predicate)
{
    struct qemu_d3d11_device_CreatePredicate call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_query *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEPREDICATE);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.predicate = (ULONG_PTR)predicate;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret) || !predicate)
        return call.super.iret;

    obj = (struct qemu_d3d11_query *)(ULONG_PTR)call.predicate;
    qemu_d3d11_query_guest_init(obj);
    *predicate = (ID3D11Predicate *)&obj->ID3D11Query_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE d3d10_device_CreatePredicate(ID3D10Device1 *iface, const D3D10_QUERY_DESC *desc,
        ID3D10Predicate **predicate)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11Predicate *query11;
    HRESULT hr;

    hr = d3d11_device_CreatePredicate(&device->ID3D11Device2_iface, (const D3D11_QUERY_DESC *)desc,
            predicate ? &query11 : NULL);
    if (FAILED(hr) || !predicate)
        return hr;

    hr = ID3D11Predicate_QueryInterface(query11, &IID_ID3D10Predicate, (void **)predicate);
    ID3D11Predicate_Release(query11);
    return hr;
}

#else

void qemu_d3d11_device_CreatePredicate(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreatePredicate *c = (struct qemu_d3d11_device_CreatePredicate *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_query *obj;
    ID3D11Query *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreatePredicate(device->host_d3d11, QEMU_G2H(c->desc),
            c->predicate ? (ID3D11Predicate **)&host : NULL);

    if (FAILED(c->super.iret) || !c->predicate)
        return;

    c->super.iret = qemu_d3d11_query_create(host, &obj);
    if (FAILED(c->super.iret))
    {
        ID3D11Query_Release(host);
        return;
    }
    c->predicate = QEMU_H2G(obj);
}

#endif

struct qemu_d3d11_device_CreateCounter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t counter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateCounter(ID3D11Device2 *iface, const D3D11_COUNTER_DESC *desc, ID3D11Counter **counter)
{
    struct qemu_d3d11_device_CreateCounter call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATECOUNTER);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.counter = (ULONG_PTR)counter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateCounter(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateCounter *c = (struct qemu_d3d11_device_CreateCounter *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateCounter(device->host_d3d11, QEMU_G2H(c->desc), QEMU_G2H(c->counter));
}

#endif

struct qemu_d3d11_device_CreateDeferredContext
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDeferredContext(ID3D11Device2 *iface, UINT flags, ID3D11DeviceContext **context)
{
    struct qemu_d3d11_device_CreateDeferredContext call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDEFERREDCONTEXT);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateDeferredContext(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDeferredContext *c = (struct qemu_d3d11_device_CreateDeferredContext *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateDeferredContext(device->host_d3d11, c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_d3d11_device_OpenSharedResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_OpenSharedResource(ID3D11Device2 *iface, HANDLE resource, REFIID riid, void **out)
{
    struct qemu_d3d11_device_OpenSharedResource call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_OPENSHAREDRESOURCE);
    call.iface = (ULONG_PTR)device;
    call.resource = (ULONG_PTR)resource;
    call.riid = (ULONG_PTR)riid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_OpenSharedResource(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_OpenSharedResource *c = (struct qemu_d3d11_device_OpenSharedResource *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_OpenSharedResource(device->host_d3d11, QEMU_G2H(c->resource), QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d11_device_CheckFormatSupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t format_support;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CheckFormatSupport(ID3D11Device2 *iface, DXGI_FORMAT format,
        UINT *format_support)
{
    struct qemu_d3d11_device_CheckFormatSupport call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CHECKFORMATSUPPORT);
    call.iface = (ULONG_PTR)device;
    call.format = format;
    call.format_support = (ULONG_PTR)format_support;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CheckFormatSupport(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CheckFormatSupport *c = (struct qemu_d3d11_device_CheckFormatSupport *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CheckFormatSupport(device->host_d3d11, c->format, QEMU_G2H(c->format_support));
}

#endif

struct qemu_d3d11_device_CheckMultisampleQualityLevels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t sample_count;
    uint64_t quality_level_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CheckMultisampleQualityLevels(ID3D11Device2 *iface, DXGI_FORMAT format,
        UINT sample_count, UINT *quality_level_count)
{
    struct qemu_d3d11_device_CheckMultisampleQualityLevels call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CHECKMULTISAMPLEQUALITYLEVELS);
    call.iface = (ULONG_PTR)device;
    call.format = format;
    call.sample_count = sample_count;
    call.quality_level_count = (ULONG_PTR)quality_level_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CheckMultisampleQualityLevels(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CheckMultisampleQualityLevels *c = (struct qemu_d3d11_device_CheckMultisampleQualityLevels *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CheckMultisampleQualityLevels(device->host_d3d11, c->format, c->sample_count, QEMU_G2H(c->quality_level_count));
}

#endif

struct qemu_d3d11_device_CheckCounterInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_device_CheckCounterInfo(ID3D11Device2 *iface, D3D11_COUNTER_INFO *info)
{
    struct qemu_d3d11_device_CheckCounterInfo call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CHECKCOUNTERINFO);
    call.iface = (ULONG_PTR)device;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_device_CheckCounterInfo(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CheckCounterInfo *c = (struct qemu_d3d11_device_CheckCounterInfo *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D11Device2_CheckCounterInfo(device->host_d3d11, QEMU_G2H(c->info));
}

#endif

struct qemu_d3d11_device_CheckCounter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t type;
    uint64_t active_counter_count;
    uint64_t name;
    uint64_t name_length;
    uint64_t units;
    uint64_t units_length;
    uint64_t description;
    uint64_t description_length;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CheckCounter(ID3D11Device2 *iface, const D3D11_COUNTER_DESC *desc, D3D11_COUNTER_TYPE *type, UINT *active_counter_count, char *name, UINT *name_length, char *units, UINT *units_length, char *description, UINT *description_length)
{
    struct qemu_d3d11_device_CheckCounter call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CHECKCOUNTER);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.type = (ULONG_PTR)type;
    call.active_counter_count = (ULONG_PTR)active_counter_count;
    call.name = (ULONG_PTR)name;
    call.name_length = (ULONG_PTR)name_length;
    call.units = (ULONG_PTR)units;
    call.units_length = (ULONG_PTR)units_length;
    call.description = (ULONG_PTR)description;
    call.description_length = (ULONG_PTR)description_length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CheckCounter(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CheckCounter *c = (struct qemu_d3d11_device_CheckCounter *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CheckCounter(device->host_d3d11, QEMU_G2H(c->desc), QEMU_G2H(c->type), QEMU_G2H(c->active_counter_count), QEMU_G2H(c->name), QEMU_G2H(c->name_length), QEMU_G2H(c->units), QEMU_G2H(c->units_length), QEMU_G2H(c->description), QEMU_G2H(c->description_length));
}

#endif

struct qemu_d3d11_device_CheckFeatureSupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t feature;
    uint64_t feature_support_data;
    uint64_t feature_support_data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CheckFeatureSupport(ID3D11Device2 *iface, D3D11_FEATURE feature,
        void *feature_support_data, UINT feature_support_data_size)
{
    struct qemu_d3d11_device_CheckFeatureSupport call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CHECKFEATURESUPPORT);
    call.iface = (ULONG_PTR)device;
    call.feature = feature;
    call.feature_support_data = (ULONG_PTR)feature_support_data;
    call.feature_support_data_size = feature_support_data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CheckFeatureSupport(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CheckFeatureSupport *c = (struct qemu_d3d11_device_CheckFeatureSupport *)call;
    struct qemu_d3d11_device *device;

    /* Add D3D11_FEATURE_DATA_* structs have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CheckFeatureSupport(device->host_d3d11, c->feature,
            QEMU_G2H(c->feature_support_data), c->feature_support_data_size);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_GetPrivateData(ID3D11Device2 *iface, REFGUID guid,
        UINT *data_size, void *data)
{
    IDXGIDevice *dxgi_device;
    HRESULT hr;

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    if (FAILED(hr = ID3D11Device_QueryInterface(iface, &IID_IDXGIDevice, (void **)&dxgi_device)))
        return hr;
    hr = IDXGIDevice_GetPrivateData(dxgi_device, guid, data_size, data);
    IDXGIDevice_Release(dxgi_device);

    return hr;
}

static HRESULT STDMETHODCALLTYPE d3d11_device_SetPrivateData(ID3D11Device2 *iface, REFGUID guid,
        UINT data_size, const void *data)
{
    IDXGIDevice *dxgi_device;
    HRESULT hr;

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    if (FAILED(hr = ID3D11Device_QueryInterface(iface, &IID_IDXGIDevice, (void **)&dxgi_device)))
        return hr;
    hr = IDXGIDevice_SetPrivateData(dxgi_device, guid, data_size, data);
    IDXGIDevice_Release(dxgi_device);

    return hr;
}

static HRESULT STDMETHODCALLTYPE d3d11_device_SetPrivateDataInterface(ID3D11Device2 *iface, REFGUID guid,
        const IUnknown *data)
{
    IDXGIDevice *dxgi_device;
    HRESULT hr;

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    if (FAILED(hr = ID3D11Device_QueryInterface(iface, &IID_IDXGIDevice, (void **)&dxgi_device)))
        return hr;
    hr = IDXGIDevice_SetPrivateDataInterface(dxgi_device, guid, data);
    IDXGIDevice_Release(dxgi_device);

    return hr;
}

#endif

struct qemu_d3d11_device_GetFeatureLevel
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3D_FEATURE_LEVEL STDMETHODCALLTYPE d3d11_device_GetFeatureLevel(ID3D11Device2 *iface)
{
    struct qemu_d3d11_device_GetFeatureLevel call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETFEATURELEVEL);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_GetFeatureLevel(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetFeatureLevel *c = (struct qemu_d3d11_device_GetFeatureLevel *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_GetFeatureLevel(device->host_d3d11);
}

#endif

struct qemu_d3d11_device_GetCreationFlags
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_device_GetCreationFlags(ID3D11Device2 *iface)
{
    struct qemu_d3d11_device_GetCreationFlags call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETCREATIONFLAGS);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_GetCreationFlags(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetCreationFlags *c = (struct qemu_d3d11_device_GetCreationFlags *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_GetCreationFlags(device->host_d3d11);
}

#endif

struct qemu_d3d11_device_GetDeviceRemovedReason
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_GetDeviceRemovedReason(ID3D11Device2 *iface)
{
    struct qemu_d3d11_device_GetDeviceRemovedReason call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETDEVICEREMOVEDREASON);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_GetDeviceRemovedReason(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetDeviceRemovedReason *c = (struct qemu_d3d11_device_GetDeviceRemovedReason *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_GetDeviceRemovedReason(device->host_d3d11);
}

#endif

struct qemu_d3d11_device_GetImmediateContext
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_device_GetImmediateContext(ID3D11Device2 *iface,
        ID3D11DeviceContext **immediate_context)
{
    struct qemu_d3d11_device_GetImmediateContext call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);
    struct qemu_d3d11_device_context *context;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETIMMEDIATECONTEXT);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    context = (struct qemu_d3d11_device_context *)(ULONG_PTR)call.context;
    *immediate_context = &context->ID3D11DeviceContext1_iface;
}

static void STDMETHODCALLTYPE d3d11_device_GetImmediateContext1(ID3D11Device2 *iface, ID3D11DeviceContext1 **context)
{
    struct qemu_d3d11_device_GetImmediateContext call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETIMMEDIATECONTEXT1);
    call.iface = (ULONG_PTR)device;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

static void STDMETHODCALLTYPE d3d11_device_GetImmediateContext2(ID3D11Device2 *iface, ID3D11DeviceContext2 **context)
{
    struct qemu_d3d11_device_GetImmediateContext call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETIMMEDIATECONTEXT2);
    call.iface = (ULONG_PTR)device;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_device_GetImmediateContext(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetImmediateContext *c = (struct qemu_d3d11_device_GetImmediateContext *)call;
    struct qemu_d3d11_device *device;
    ID3D11DeviceContext1 *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    c->context = QEMU_H2G(&device->immediate_context);

    /* For refcounting */
    ID3D11Device2_GetImmediateContext(device->host_d3d11, (ID3D11DeviceContext **)&host);
    if (host != device->immediate_context.host)
        WINE_ERR("Got context %p, expected %p.\n", host, device->immediate_context.host);
}

void qemu_d3d11_device_GetImmediateContext1(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetImmediateContext *c = (struct qemu_d3d11_device_GetImmediateContext *)call;
    struct qemu_d3d11_device *device;
    ID3D11DeviceContext1 *ctx = (ID3D11DeviceContext1 *)0xdeadbeef;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11Device2_GetImmediateContext1(device->host_d3d11, &ctx);
    if (ctx != (ID3D11DeviceContext1 *)0xdeadbeef)
        WINE_FIXME("Host returned context %p.\n", ctx);
}

void qemu_d3d11_device_GetImmediateContext2(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetImmediateContext *c = (struct qemu_d3d11_device_GetImmediateContext *)call;
    struct qemu_d3d11_device *device;
    ID3D11DeviceContext2 *ctx = (ID3D11DeviceContext2 *)0xdeadbeef;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11Device2_GetImmediateContext2(device->host_d3d11, &ctx);
    if (ctx != (ID3D11DeviceContext2 *)0xdeadbeef)
        WINE_FIXME("Host returned context %p.\n", ctx);
}

#endif

struct qemu_d3d11_device_SetExceptionMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_SetExceptionMode(ID3D11Device2 *iface, UINT flags)
{
    struct qemu_d3d11_device_SetExceptionMode call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_SETEXCEPTIONMODE);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_SetExceptionMode(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_SetExceptionMode *c = (struct qemu_d3d11_device_SetExceptionMode *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_SetExceptionMode(device->host_d3d11, c->flags);
}

#endif

struct qemu_d3d11_device_GetExceptionMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d11_device_GetExceptionMode(ID3D11Device2 *iface)
{
    struct qemu_d3d11_device_GetExceptionMode call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETEXCEPTIONMODE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_GetExceptionMode(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetExceptionMode *c = (struct qemu_d3d11_device_GetExceptionMode *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_GetExceptionMode(device->host_d3d11);
}

#endif

struct qemu_d3d11_device_CreateDeferredContext1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDeferredContext1(ID3D11Device2 *iface, UINT flags, ID3D11DeviceContext1 **context)
{
    struct qemu_d3d11_device_CreateDeferredContext1 call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDEFERREDCONTEXT1);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateDeferredContext1(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDeferredContext1 *c = (struct qemu_d3d11_device_CreateDeferredContext1 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateDeferredContext1(device->host_d3d11, c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_d3d11_device_CreateBlendState1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateBlendState1(ID3D11Device2 *iface, const D3D11_BLEND_DESC1 *desc, ID3D11BlendState1 **state)
{
    struct qemu_d3d11_device_CreateBlendState1 call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEBLENDSTATE1);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateBlendState1(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateBlendState1 *c = (struct qemu_d3d11_device_CreateBlendState1 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateBlendState1(device->host_d3d11, QEMU_G2H(c->desc), QEMU_G2H(c->state));
}

#endif

struct qemu_d3d11_device_CreateRasterizerState1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateRasterizerState1(ID3D11Device2 *iface, const D3D11_RASTERIZER_DESC1 *desc, ID3D11RasterizerState1 **state)
{
    struct qemu_d3d11_device_CreateRasterizerState1 call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATERASTERIZERSTATE1);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateRasterizerState1(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateRasterizerState1 *c = (struct qemu_d3d11_device_CreateRasterizerState1 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateRasterizerState1(device->host_d3d11, QEMU_G2H(c->desc), QEMU_G2H(c->state));
}

#endif

struct qemu_d3d11_device_CreateDeviceContextState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t feature_levels;
    uint64_t feature_levels_count;
    uint64_t sdk_version;
    uint64_t emulated_interface;
    uint64_t chosen_feature_level;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDeviceContextState(ID3D11Device2 *iface, UINT flags, const D3D_FEATURE_LEVEL *feature_levels, UINT feature_levels_count, UINT sdk_version, REFIID emulated_interface, D3D_FEATURE_LEVEL *chosen_feature_level, ID3DDeviceContextState **state)
{
    struct qemu_d3d11_device_CreateDeviceContextState call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDEVICECONTEXTSTATE);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.feature_levels_count = feature_levels_count;
    call.sdk_version = sdk_version;
    call.emulated_interface = (ULONG_PTR)emulated_interface;
    call.chosen_feature_level = (ULONG_PTR)chosen_feature_level;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateDeviceContextState(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDeviceContextState *c = (struct qemu_d3d11_device_CreateDeviceContextState *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateDeviceContextState(device->host_d3d11, c->flags, QEMU_G2H(c->feature_levels), c->feature_levels_count, c->sdk_version, QEMU_G2H(c->emulated_interface), QEMU_G2H(c->chosen_feature_level), QEMU_G2H(c->state));
}

#endif

struct qemu_d3d11_device_OpenSharedResource1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t handle;
    uint64_t riid;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_OpenSharedResource1(ID3D11Device2 *iface, HANDLE handle, REFIID riid, void **resource)
{
    struct qemu_d3d11_device_OpenSharedResource1 call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_OPENSHAREDRESOURCE1);
    call.iface = (ULONG_PTR)device;
    call.handle = (ULONG_PTR)handle;
    call.riid = (ULONG_PTR)riid;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_OpenSharedResource1(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_OpenSharedResource1 *c = (struct qemu_d3d11_device_OpenSharedResource1 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_OpenSharedResource1(device->host_d3d11, QEMU_G2H(c->handle), QEMU_G2H(c->riid), QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_device_OpenSharedResourceByName
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t access;
    uint64_t riid;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_OpenSharedResourceByName(ID3D11Device2 *iface, const WCHAR *name, DWORD access, REFIID riid, void **resource)
{
    struct qemu_d3d11_device_OpenSharedResourceByName call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_OPENSHAREDRESOURCEBYNAME);
    call.iface = (ULONG_PTR)device;
    call.name = (ULONG_PTR)name;
    call.access = access;
    call.riid = (ULONG_PTR)riid;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_OpenSharedResourceByName(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_OpenSharedResourceByName *c = (struct qemu_d3d11_device_OpenSharedResourceByName *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_OpenSharedResourceByName(device->host_d3d11, QEMU_G2H(c->name), c->access, QEMU_G2H(c->riid), QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d11_device_CreateDeferredContext2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CreateDeferredContext2(ID3D11Device2 *iface, UINT flags, ID3D11DeviceContext2 **context)
{
    struct qemu_d3d11_device_CreateDeferredContext2 call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CREATEDEFERREDCONTEXT2);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CreateDeferredContext2(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CreateDeferredContext2 *c = (struct qemu_d3d11_device_CreateDeferredContext2 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CreateDeferredContext2(device->host_d3d11, c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_d3d11_device_GetResourceTiling
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
    uint64_t tile_count;
    uint64_t mip_desc;
    uint64_t tile_shape;
    uint64_t subresource_tiling_count;
    uint64_t first_subresource_tiling;
    uint64_t subresource_tiling;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_device_GetResourceTiling(ID3D11Device2 *iface, ID3D11Resource *resource, UINT *tile_count, D3D11_PACKED_MIP_DESC *mip_desc, D3D11_TILE_SHAPE *tile_shape, UINT *subresource_tiling_count, UINT first_subresource_tiling, D3D11_SUBRESOURCE_TILING *subresource_tiling)
{
    struct qemu_d3d11_device_GetResourceTiling call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_GETRESOURCETILING);
    call.iface = (ULONG_PTR)device;
    call.resource = (ULONG_PTR)resource;
    call.tile_count = (ULONG_PTR)tile_count;
    call.mip_desc = (ULONG_PTR)mip_desc;
    call.tile_shape = (ULONG_PTR)tile_shape;
    call.subresource_tiling_count = (ULONG_PTR)subresource_tiling_count;
    call.first_subresource_tiling = first_subresource_tiling;
    call.subresource_tiling = (ULONG_PTR)subresource_tiling;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_device_GetResourceTiling(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_GetResourceTiling *c = (struct qemu_d3d11_device_GetResourceTiling *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D11Device2_GetResourceTiling(device->host_d3d11, QEMU_G2H(c->resource), QEMU_G2H(c->tile_count), QEMU_G2H(c->mip_desc), QEMU_G2H(c->tile_shape), QEMU_G2H(c->subresource_tiling_count), c->first_subresource_tiling, QEMU_G2H(c->subresource_tiling));
}

#endif

struct qemu_d3d11_device_CheckMultisampleQualityLevels1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t sample_count;
    uint64_t flags;
    uint64_t quality_level_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_device_CheckMultisampleQualityLevels1(ID3D11Device2 *iface, DXGI_FORMAT format, UINT sample_count, UINT flags, UINT *quality_level_count)
{
    struct qemu_d3d11_device_CheckMultisampleQualityLevels1 call;
    struct qemu_d3d11_device *device = impl_from_ID3D11Device2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEVICE_CHECKMULTISAMPLEQUALITYLEVELS1);
    call.iface = (ULONG_PTR)device;
    call.format = format;
    call.sample_count = sample_count;
    call.flags = flags;
    call.quality_level_count = (ULONG_PTR)quality_level_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_device_CheckMultisampleQualityLevels1(struct qemu_syscall *call)
{
    struct qemu_d3d11_device_CheckMultisampleQualityLevels1 *c = (struct qemu_d3d11_device_CheckMultisampleQualityLevels1 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D11Device2_CheckMultisampleQualityLevels1(device->host_d3d11, c->format, c->sample_count, c->flags, QEMU_G2H(c->quality_level_count));
}

#endif

struct qemu_d3d_device_inner_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_device *impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device, IUnknown_inner);
}

static HRESULT STDMETHODCALLTYPE d3d_device_inner_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    struct qemu_d3d_device_inner_QueryInterface call;
    struct qemu_d3d11_device *device = impl_from_IUnknown(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (IsEqualGUID(riid, &IID_ID3D11Device2)
            || IsEqualGUID(riid, &IID_ID3D11Device1)
            || IsEqualGUID(riid, &IID_ID3D11Device)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        *out = &device->ID3D11Device2_iface;
    }
    else if (IsEqualGUID(riid, &IID_ID3D10Device1)
            || IsEqualGUID(riid, &IID_ID3D10Device))
    {
        *out = &device->ID3D10Device1_iface;
    }
    else if (IsEqualGUID(riid, &IID_ID3D10Multithread))
    {
        *out = &device->ID3D10Multithread_iface;
    }
    else if (IsEqualGUID(riid, &IID_IQemuD3D11Device))
    {
        *out = &device->IQemuD3D11Device_iface;
    }
    else
    {
        /* Test if we're supposed to know about it. */
        call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE_INNER_QUERYINTERFACE);
        call.iface = (ULONG_PTR)device;
        call.riid = (ULONG_PTR)riid;

        qemu_syscall(&call.super);

        *out = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown *)*out);
    return S_OK;
}

#else

void qemu_d3d_device_inner_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d_device_inner_QueryInterface *c = (struct qemu_d3d_device_inner_QueryInterface *)call;
    struct qemu_d3d11_device *device;
    IUnknown *out;

    WINE_TRACE("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IUnknown_QueryInterface(device->host_d3d11, QEMU_G2H(c->riid), (void **)&out);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host device returned IID %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(out);
    }
}

#endif

struct qemu_d3d_device_inner_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d_device_inner_AddRef(IUnknown *iface)
{
    struct qemu_d3d_device_inner_AddRef call;
    struct qemu_d3d11_device *device = impl_from_IUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE_INNER_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device_inner_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d_device_inner_AddRef *c = (struct qemu_d3d_device_inner_AddRef *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Did not expect this to be called\n");
    c->super.iret = 2;
}

#endif

struct qemu_d3d_device_inner_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d_device_inner_Release(IUnknown *iface)
{
    struct qemu_d3d_device_inner_Release call;
    struct qemu_d3d11_device *device = impl_from_IUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_DEVICE_INNER_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_device_inner_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_device_inner_Release *c = (struct qemu_d3d_device_inner_Release *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Did not expect this to be called\n");
    c->super.iret = 1;
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_QueryInterface(ID3D10Device1 *iface, REFIID riid,
        void **ppv)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    return IUnknown_QueryInterface(device->outer_unk, riid, ppv);
}

static ULONG STDMETHODCALLTYPE d3d10_device_AddRef(ID3D10Device1 *iface)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    return IUnknown_AddRef(device->outer_unk);
}

static ULONG STDMETHODCALLTYPE d3d10_device_Release(ID3D10Device1 *iface)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    return IUnknown_Release(device->outer_unk);
}

#endif

struct qemu_d3d10_device_VSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSSetConstantBuffers(ID3D10Device1 *iface, UINT start_slot,
        UINT buffer_count, ID3D10Buffer *const *buffers)
{
    struct qemu_d3d10_device_VSSetConstantBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_VSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSSetConstantBuffers *c = (struct qemu_d3d10_device_VSSetConstantBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D10Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host10 : NULL;
    }

    ID3D10Device1_VSSetConstantBuffers(device->host_d3d10, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d10_device_PSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSSetShaderResources(ID3D10Device1 *iface, UINT start_slot,
        UINT view_count, ID3D10ShaderResourceView *const *views)
{
    struct qemu_d3d10_device_PSSetShaderResources call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d10_device_PSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSSetShaderResources *c = (struct qemu_d3d10_device_PSSetShaderResources *)call;
    struct qemu_d3d11_device *device;
    ID3D10ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? (ID3D10ShaderResourceView *)impls[i]->host_sr10 : NULL;

    ID3D10Device1_PSSetShaderResources(device->host_d3d10, c->start_slot, count, views);
}

#endif

struct qemu_d3d10_device_PSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSSetShader(ID3D10Device1 *iface, ID3D10PixelShader *shader)
{
    struct qemu_d3d10_device_PSSetShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_shader *impl = unsafe_impl_from_ID3D10PixelShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSSETSHADER);
    call.iface = (ULONG_PTR)device;
    call.shader = (ULONG_PTR)impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_PSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSSetShader *c = (struct qemu_d3d10_device_PSSetShader *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);

    ID3D10Device1_PSSetShader(device->host_d3d10, shader ? shader->host_ps10 : NULL);
}

#endif

struct qemu_d3d10_device_PSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSSetSamplers(ID3D10Device1 *iface, UINT start_slot, UINT sampler_count, ID3D10SamplerState *const *samplers)
{
    struct qemu_d3d10_device_PSSetSamplers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSSETSAMPLERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d10_device_PSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSSetSamplers *c = (struct qemu_d3d10_device_PSSetSamplers *)call;
    struct qemu_d3d11_device *device;
    ID3D10SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss10 : NULL;

    ID3D10Device1_PSSetSamplers(device->host_d3d10, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d10_device_VSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSSetShader(ID3D10Device1 *iface, ID3D10VertexShader *shader)
{
    struct qemu_d3d10_device_VSSetShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_shader *impl = unsafe_impl_from_ID3D10VertexShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSSETSHADER);
    call.iface = (ULONG_PTR)device;
    call.shader = (ULONG_PTR)impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_VSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSSetShader *c = (struct qemu_d3d10_device_VSSetShader *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);

    ID3D10Device1_VSSetShader(device->host_d3d10, shader ? shader->host_vs10 : NULL);
}

#endif

struct qemu_d3d10_device_DrawIndexed
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index_count;
    uint64_t start_index_location;
    uint64_t base_vertex_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_DrawIndexed(ID3D10Device1 *iface, UINT index_count, UINT start_index_location, INT base_vertex_location)
{
    struct qemu_d3d10_device_DrawIndexed call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_DRAWINDEXED);
    call.iface = (ULONG_PTR)device;
    call.index_count = index_count;
    call.start_index_location = start_index_location;
    call.base_vertex_location = base_vertex_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_DrawIndexed(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_DrawIndexed *c = (struct qemu_d3d10_device_DrawIndexed *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_DrawIndexed(device->host_d3d10, c->index_count, c->start_index_location, c->base_vertex_location);
}

#endif

struct qemu_d3d10_device_Draw
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vertex_count;
    uint64_t start_vertex_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_Draw(ID3D10Device1 *iface, UINT vertex_count, UINT start_vertex_location)
{
    struct qemu_d3d10_device_Draw call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_DRAW);
    call.iface = (ULONG_PTR)device;
    call.vertex_count = vertex_count;
    call.start_vertex_location = start_vertex_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_Draw(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_Draw *c = (struct qemu_d3d10_device_Draw *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_Draw(device->host_d3d10, c->vertex_count, c->start_vertex_location);
}

#endif

struct qemu_d3d10_device_PSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSSetConstantBuffers(ID3D10Device1 *iface, UINT start_slot,
        UINT buffer_count, ID3D10Buffer *const *buffers)
{
    struct qemu_d3d10_device_PSSetConstantBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_PSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSSetConstantBuffers *c = (struct qemu_d3d10_device_PSSetConstantBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D10Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host10 : NULL;
    }

    ID3D10Device1_PSSetConstantBuffers(device->host_d3d10, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d10_device_IASetInputLayout
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t input_layout;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IASetInputLayout(ID3D10Device1 *iface, ID3D10InputLayout *input_layout)
{
    struct qemu_d3d10_device_IASetInputLayout call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_input_layout *layout = unsafe_impl_from_ID3D10InputLayout(input_layout);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IASETINPUTLAYOUT);
    call.iface = (ULONG_PTR)device;
    call.input_layout = (ULONG_PTR)layout;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_IASetInputLayout(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IASetInputLayout *c = (struct qemu_d3d10_device_IASetInputLayout *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_input_layout *layout;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    layout = QEMU_G2H(c->input_layout);

    ID3D10Device1_IASetInputLayout(device->host_d3d10, layout ? layout->host10 : NULL);
}

#endif

struct qemu_d3d10_device_IASetVertexBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t strides;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IASetVertexBuffers(ID3D10Device1 *iface, UINT start_slot, UINT buffer_count, ID3D10Buffer *const *buffers, const UINT *strides, const UINT *offsets)
{
    struct qemu_d3d10_device_IASetVertexBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[MAX_STREAMS], *buffer_impl = stack;
    UINT i;

    if (buffer_count > MAX_STREAMS)
        buffer_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*buffer_impl) * buffer_count);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IASETVERTEXBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.strides = (ULONG_PTR)strides;
    call.offsets = (ULONG_PTR)offsets;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);

    if (buffer_impl != stack)
        HeapFree(GetProcessHeap(), 0, buffer_impl);
}

#else

void qemu_d3d10_device_IASetVertexBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IASetVertexBuffers *c = (struct qemu_d3d10_device_IASetVertexBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D10Buffer **buffer_iface;
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    buffer_iface = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host10 : NULL;
    }

    ID3D10Device1_IASetVertexBuffers(device->host_d3d10, c->start_slot, c->buffer_count,
            buffer_iface, QEMU_G2H(c->strides), QEMU_G2H(c->offsets));
}

#endif

struct qemu_d3d10_device_IASetIndexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t format;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IASetIndexBuffer(ID3D10Device1 *iface, ID3D10Buffer *buffer,
        DXGI_FORMAT format, UINT offset)
{
    struct qemu_d3d10_device_IASetIndexBuffer call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_buffer *buffer_impl = unsafe_impl_from_ID3D10Buffer(buffer);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IASETINDEXBUFFER);
    call.iface = (ULONG_PTR)device;
    call.buffer = (ULONG_PTR)buffer_impl;
    call.format = format;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_IASetIndexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IASetIndexBuffer *c = (struct qemu_d3d10_device_IASetIndexBuffer *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_buffer *buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    ID3D10Device1_IASetIndexBuffer(device->host_d3d10, buffer ? buffer->host10 : NULL, c->format, c->offset);
}

#endif

struct qemu_d3d10_device_DrawIndexedInstanced
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t instance_index_count;
    uint64_t instance_count;
    uint64_t start_index_location;
    uint64_t base_vertex_location;
    uint64_t start_instance_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_DrawIndexedInstanced(ID3D10Device1 *iface, UINT instance_index_count, UINT instance_count, UINT start_index_location, INT base_vertex_location, UINT start_instance_location)
{
    struct qemu_d3d10_device_DrawIndexedInstanced call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_DRAWINDEXEDINSTANCED);
    call.iface = (ULONG_PTR)device;
    call.instance_index_count = instance_index_count;
    call.instance_count = instance_count;
    call.start_index_location = start_index_location;
    call.base_vertex_location = base_vertex_location;
    call.start_instance_location = start_instance_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_DrawIndexedInstanced(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_DrawIndexedInstanced *c = (struct qemu_d3d10_device_DrawIndexedInstanced *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_DrawIndexedInstanced(device->host_d3d10, c->instance_index_count, c->instance_count, c->start_index_location, c->base_vertex_location, c->start_instance_location);
}

#endif

struct qemu_d3d10_device_DrawInstanced
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t instance_vertex_count;
    uint64_t instance_count;
    uint64_t start_vertex_location;
    uint64_t start_instance_location;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_DrawInstanced(ID3D10Device1 *iface, UINT instance_vertex_count, UINT instance_count, UINT start_vertex_location, UINT start_instance_location)
{
    struct qemu_d3d10_device_DrawInstanced call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_DRAWINSTANCED);
    call.iface = (ULONG_PTR)device;
    call.instance_vertex_count = instance_vertex_count;
    call.instance_count = instance_count;
    call.start_vertex_location = start_vertex_location;
    call.start_instance_location = start_instance_location;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_DrawInstanced(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_DrawInstanced *c = (struct qemu_d3d10_device_DrawInstanced *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_DrawInstanced(device->host_d3d10, c->instance_vertex_count, c->instance_count, c->start_vertex_location, c->start_instance_location);
}

#endif

struct qemu_d3d10_device_GSSetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSSetConstantBuffers(ID3D10Device1 *iface, UINT start_slot,
        UINT buffer_count, ID3D10Buffer *const *buffers)
{
    struct qemu_d3d10_device_GSSetConstantBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t buffer_impl[MAX_CONSTANT_BUFFERS];
    UINT i;

    if (buffer_count > MAX_CONSTANT_BUFFERS)
    {
        WINE_FIXME("MAX_CONSTANT_BUFFERS is too small.\n");
        return;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSSETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    for (i = 0; i < buffer_count; ++i)
        buffer_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer(buffers[i]);

    call.buffers = (ULONG_PTR)buffer_impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_GSSetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSSetConstantBuffers *c = (struct qemu_d3d10_device_GSSetConstantBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D10Buffer *buffer_iface[MAX_CONSTANT_BUFFERS];
    UINT i;
    struct qemu_d3d11_buffer *buffer;
    uint64_t *buffer_array;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer_array = QEMU_G2H(c->buffers);
    for (i = 0; i < c->buffer_count; ++i)
    {
        buffer = QEMU_G2H(buffer_array[i]);
        buffer_iface[i] = buffer ? buffer->host10 : NULL;
    }

    ID3D10Device1_GSSetConstantBuffers(device->host_d3d10, c->start_slot, c->buffer_count, buffer_iface);
}

#endif

struct qemu_d3d10_device_GSSetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSSetShader(ID3D10Device1 *iface, ID3D10GeometryShader *shader)
{
    struct qemu_d3d10_device_GSSetShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_shader *impl = unsafe_impl_from_ID3D10GeometryShader(shader);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSSETSHADER);
    call.iface = (ULONG_PTR)device;
    call.shader = (ULONG_PTR)impl;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_GSSetShader(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSSetShader *c = (struct qemu_d3d10_device_GSSetShader *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_shader *shader;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    shader = QEMU_G2H(c->shader);

    ID3D10Device1_GSSetShader(device->host_d3d10, shader ? shader->host_gs10 : NULL);
}

#endif

struct qemu_d3d10_device_IASetPrimitiveTopology
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t topology;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IASetPrimitiveTopology(ID3D10Device1 *iface,
        D3D10_PRIMITIVE_TOPOLOGY topology)
{
    struct qemu_d3d10_device_IASetPrimitiveTopology call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IASETPRIMITIVETOPOLOGY);
    call.iface = (ULONG_PTR)device;
    call.topology = topology;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_IASetPrimitiveTopology(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IASetPrimitiveTopology *c = (struct qemu_d3d10_device_IASetPrimitiveTopology *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_IASetPrimitiveTopology(device->host_d3d10, c->topology);
}

#endif

struct qemu_d3d10_device_VSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSSetShaderResources(ID3D10Device1 *iface, UINT start_slot,
        UINT view_count, ID3D10ShaderResourceView *const *views)
{
    struct qemu_d3d10_device_VSSetShaderResources call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d10_device_VSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSSetShaderResources *c = (struct qemu_d3d10_device_VSSetShaderResources *)call;
    struct qemu_d3d11_device *device;
    ID3D10ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? (ID3D10ShaderResourceView *)impls[i]->host_sr10 : NULL;

    ID3D10Device1_VSSetShaderResources(device->host_d3d10, c->start_slot, count, views);
}

#endif

struct qemu_d3d10_device_VSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSSetSamplers(ID3D10Device1 *iface, UINT start_slot, UINT sampler_count,
        ID3D10SamplerState *const *samplers)
{
    struct qemu_d3d10_device_VSSetSamplers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSSETSAMPLERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d10_device_VSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSSetSamplers *c = (struct qemu_d3d10_device_VSSetSamplers *)call;
    struct qemu_d3d11_device *device;
    ID3D10SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss10 : NULL;

    ID3D10Device1_VSSetSamplers(device->host_d3d10, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d10_device_SetPredication
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t predicate;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_SetPredication(ID3D10Device1 *iface, ID3D10Predicate *predicate, BOOL value)
{
    struct qemu_d3d10_device_SetPredication call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_query *query = unsafe_impl_from_ID3D10Query((ID3D10Query *)predicate);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_SETPREDICATION);
    call.iface = (ULONG_PTR)device;
    call.predicate = (ULONG_PTR)query;
    call.value = value;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_SetPredication(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_SetPredication *c = (struct qemu_d3d10_device_SetPredication *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_query *query;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    query = QEMU_G2H(c->predicate);

    ID3D10Device1_SetPredication(device->host_d3d10, query ? (ID3D10Predicate *)query->host10 : NULL, c->value);
}

#endif

struct qemu_d3d10_device_GSSetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSSetShaderResources(ID3D10Device1 *iface, UINT start_slot,
        UINT view_count, ID3D10ShaderResourceView *const *views)
{
    struct qemu_d3d10_device_GSSetShaderResources call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSSETSHADERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    for (i = 0; i < view_count; ++i)
        view_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10ShaderResourceView(views[i]);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d10_device_GSSetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSSetShaderResources *c = (struct qemu_d3d10_device_GSSetShaderResources *)call;
    struct qemu_d3d11_device *device;
    ID3D10ShaderResourceView **views;
    struct qemu_d3d11_view **impls;
    UINT count, i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    views = QEMU_G2H(c->views);
    impls = QEMU_G2H(c->views);
    count = c->view_count;

    for (i = 0; i < count; ++i)
        views[i] = impls[i] ? (ID3D10ShaderResourceView *)impls[i]->host_sr10 : NULL;

    ID3D10Device1_GSSetShaderResources(device->host_d3d10, c->start_slot, count, views);
}

#endif

struct qemu_d3d10_device_GSSetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSSetSamplers(ID3D10Device1 *iface, UINT start_slot, UINT sampler_count,
        ID3D10SamplerState *const *samplers)
{
    struct qemu_d3d10_device_GSSetSamplers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSSETSAMPLERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    for (i = 0; i < sampler_count; ++i)
        sampler_impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10SamplerState(samplers[i]);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d10_device_GSSetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSSetSamplers *c = (struct qemu_d3d10_device_GSSetSamplers *)call;
    struct qemu_d3d11_device *device;
    ID3D10SamplerState **ifaces;
    UINT i, count;
    struct qemu_d3d11_state **sampler_impl;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    count = c->sampler_count;
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);

    for (i = 0; i < count; ++i)
        ifaces[i] = sampler_impl[i] ? sampler_impl[i]->host_ss10 : NULL;

    ID3D10Device1_GSSetSamplers(device->host_d3d10, c->start_slot, count, ifaces);
}

#endif

struct qemu_d3d10_device_OMSetRenderTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view_count;
    uint64_t render_target_views;
    uint64_t depth_stencil_view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_OMSetRenderTargets(ID3D10Device1 *iface, UINT render_target_view_count,
        ID3D10RenderTargetView *const *render_target_views, ID3D10DepthStencilView *depth_stencil_view)
{
    struct qemu_d3d10_device_OMSetRenderTargets call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_view *ds_view = unsafe_impl_from_ID3D10DepthStencilView(depth_stencil_view);
    uint64_t rt_views[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    UINT i;

    for (i = 0; i < render_target_view_count; ++i)
        rt_views[i] = (ULONG_PTR)unsafe_impl_from_ID3D10RenderTargetView(render_target_views[i]);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OMSETRENDERTARGETS);
    call.iface = (ULONG_PTR)device;
    call.render_target_view_count = render_target_view_count;
    call.render_target_views = (ULONG_PTR)rt_views;
    call.depth_stencil_view = (ULONG_PTR)ds_view;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_OMSetRenderTargets(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OMSetRenderTargets *c =
            (struct qemu_d3d10_device_OMSetRenderTargets *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_view *ds_view;
    struct qemu_d3d11_view **rt_views;
    ID3D10RenderTargetView *view_ifaces[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
    UINT i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ds_view = QEMU_G2H(c->depth_stencil_view);
    rt_views = QEMU_G2H(c->render_target_views);

    for (i = 0; i < c->render_target_view_count; ++i)
        view_ifaces[i] = rt_views[i] ? rt_views[i]->host_rt10 : NULL;

    ID3D10Device1_OMSetRenderTargets(device->host_d3d10, c->render_target_view_count, view_ifaces,
            ds_view ? ds_view->host_ds10 : NULL);
}

#endif

struct qemu_d3d10_device_OMSetBlendState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t blend_state;
    uint64_t blend_factor;
    uint64_t sample_mask;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_OMSetBlendState(ID3D10Device1 *iface, ID3D10BlendState *blend_state,
        const float blend_factor[4], UINT sample_mask)
{
    struct qemu_d3d10_device_OMSetBlendState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_state *state = unsafe_impl_from_ID3D10BlendState(blend_state);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OMSETBLENDSTATE);
    call.iface = (ULONG_PTR)device;
    call.blend_state = (ULONG_PTR)state;
    call.blend_factor = (ULONG_PTR)blend_factor;
    call.sample_mask = sample_mask;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_OMSetBlendState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OMSetBlendState *c = (struct qemu_d3d10_device_OMSetBlendState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *state;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    state = QEMU_G2H(c->blend_state);

    ID3D10Device1_OMSetBlendState(device->host_d3d10, state ? (ID3D10BlendState *)state->host_bs10 : NULL,
            QEMU_G2H(c->blend_factor), c->sample_mask);
}

#endif

struct qemu_d3d10_device_OMSetDepthStencilState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil_state;
    uint64_t stencil_ref;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_OMSetDepthStencilState(ID3D10Device1 *iface,
        ID3D10DepthStencilState *depth_stencil_state, UINT stencil_ref)
{
    struct qemu_d3d10_device_OMSetDepthStencilState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_state *state_impl = unsafe_impl_from_ID3D10DepthStencilState(depth_stencil_state);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OMSETDEPTHSTENCILSTATE);
    call.iface = (ULONG_PTR)device;
    call.depth_stencil_state = (ULONG_PTR)state_impl;
    call.stencil_ref = stencil_ref;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_OMSetDepthStencilState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OMSetDepthStencilState *c = (struct qemu_d3d10_device_OMSetDepthStencilState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *state;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    state = QEMU_G2H(c->depth_stencil_state);

    ID3D10Device1_OMSetDepthStencilState(device->host_d3d10, state ? state->host_ds10 : NULL, c->stencil_ref);
}

#endif

struct qemu_d3d10_device_SOSetTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t target_count;
    uint64_t targets;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_SOSetTargets(ID3D10Device1 *iface, UINT target_count,
        ID3D10Buffer *const *targets, const UINT *offsets)
{
    struct qemu_d3d10_device_SOSetTargets call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_SOSETTARGETS);
    call.iface = (ULONG_PTR)device;
    call.target_count = target_count;
    call.offsets = (ULONG_PTR)offsets;

    if (target_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * target_count);

    for (i = 0; i < target_count; ++i)
        impl[i] = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer(targets[i]);

    call.targets = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d10_device_SOSetTargets(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_SOSetTargets *c = (struct qemu_d3d10_device_SOSetTargets *)call;
    struct qemu_d3d11_device *device;
    ID3D10Buffer **buffers;
    struct qemu_d3d11_buffer **impls;
    UINT count, i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffers = QEMU_G2H(c->targets);
    impls = QEMU_G2H(c->targets);
    count = c->target_count;

    for (i = 0; i < count; ++i)
        buffers[i] = impls[i] ? impls[i]->host10 : NULL;

    ID3D10Device1_SOSetTargets(device->host_d3d10, count, buffers, QEMU_G2H(c->offsets));
}

#endif

struct qemu_d3d10_device_DrawAuto
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_DrawAuto(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_DrawAuto call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_DRAWAUTO);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_DrawAuto(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_DrawAuto *c = (struct qemu_d3d10_device_DrawAuto *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_DrawAuto(device->host_d3d10);
}

#endif

struct qemu_d3d10_device_RSSetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rasterizer_state;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_RSSetState(ID3D10Device1 *iface, ID3D10RasterizerState *rasterizer_state)
{
    struct qemu_d3d10_device_RSSetState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_state *state = unsafe_impl_from_ID3D10RasterizerState(rasterizer_state);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RSSETSTATE);
    call.iface = (ULONG_PTR)device;
    call.rasterizer_state = (ULONG_PTR)state;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_RSSetState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_RSSetState *c = (struct qemu_d3d10_device_RSSetState *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_state *state;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    state = QEMU_G2H(c->rasterizer_state);

    ID3D10Device1_RSSetState(device->host_d3d10, state ? state->host_rs10 : NULL);
}

#endif

struct qemu_d3d10_device_RSSetViewports
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport_count;
    uint64_t viewports;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_RSSetViewports(ID3D10Device1 *iface, UINT viewport_count,
        const D3D10_VIEWPORT *viewports)
{
    struct qemu_d3d10_device_RSSetViewports call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RSSETVIEWPORTS);
    call.iface = (ULONG_PTR)device;
    call.viewport_count = viewport_count;
    call.viewports = (ULONG_PTR)viewports;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_RSSetViewports(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_RSSetViewports *c = (struct qemu_d3d10_device_RSSetViewports *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_RSSetViewports(device->host_d3d10, c->viewport_count, QEMU_G2H(c->viewports));
}

#endif

struct qemu_d3d10_device_RSSetScissorRects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_RSSetScissorRects(ID3D10Device1 *iface, UINT rect_count, const D3D10_RECT *rects)
{
    struct qemu_d3d10_device_RSSetScissorRects call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RSSETSCISSORRECTS);
    call.iface = (ULONG_PTR)device;
    call.rect_count = rect_count;
    call.rects = (ULONG_PTR)rects;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_RSSetScissorRects(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_RSSetScissorRects *c = (struct qemu_d3d10_device_RSSetScissorRects *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_RSSetScissorRects(device->host_d3d10, c->rect_count, QEMU_G2H(c->rects));
}

#endif

struct qemu_d3d10_device_CopySubresourceRegion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_texture;
    uint64_t dst_buffer;
    uint64_t dst_subresource_idx;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t dst_z;
    uint64_t src_texture;
    uint64_t src_buffer;
    uint64_t src_subresource_idx;
    uint64_t src_box;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_CopySubresourceRegion(ID3D10Device1 *iface, ID3D10Resource *dst_resource,
        UINT dst_subresource_idx, UINT dst_x, UINT dst_y, UINT dst_z, ID3D10Resource *src_resource,
        UINT src_subresource_idx, const D3D10_BOX *src_box)
{
    struct qemu_d3d10_device_CopySubresourceRegion call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D10_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_COPYSUBRESOURCEREGION);
    call.iface = (ULONG_PTR)device;
    call.dst_subresource_idx = dst_subresource_idx;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.dst_z = dst_z;
    call.src_subresource_idx = src_subresource_idx;
    call.src_box = (ULONG_PTR)src_box;

    ID3D10Resource_GetType(dst_resource, &dim);
    switch (dim)
    {
        case D3D10_RESOURCE_DIMENSION_TEXTURE1D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture1D((ID3D10Texture1D *)dst_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE2D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture2D((ID3D10Texture2D *)dst_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE3D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture3D((ID3D10Texture3D *)dst_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_BUFFER:
            call.dst_buffer = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer((ID3D10Buffer *)dst_resource);
            call.dst_texture = 0;
            break;
    }

    ID3D10Resource_GetType(src_resource, &dim);
    switch (dim)
    {
        case D3D10_RESOURCE_DIMENSION_TEXTURE1D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture1D((ID3D10Texture1D *)src_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE2D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture2D((ID3D10Texture2D *)src_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE3D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture3D((ID3D10Texture3D *)src_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_BUFFER:
            call.src_buffer = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer((ID3D10Buffer *)src_resource);
            call.src_texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_CopySubresourceRegion(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CopySubresourceRegion *c = (struct qemu_d3d10_device_CopySubresourceRegion *)call;
    struct qemu_d3d11_device *device;
    ID3D10Resource *dst, *src;
    struct qemu_d3d11_buffer *buf;
    struct qemu_d3d11_texture *tex;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    if (c->src_buffer)
    {
        buf = QEMU_G2H(c->src_buffer);
        src = (ID3D10Resource *)buf->host10;
    }
    else
    {
        tex = QEMU_G2H(c->src_texture);
        src = (ID3D10Resource *)tex->host10_1d;
    }

    if (c->dst_buffer)
    {
        buf = QEMU_G2H(c->dst_buffer);
        dst = (ID3D10Resource *)buf->host10;
    }
    else
    {
        tex = QEMU_G2H(c->dst_texture);
        dst = (ID3D10Resource *)tex->host10_1d;
    }

    ID3D10Device1_CopySubresourceRegion(device->host_d3d10, dst, c->dst_subresource_idx, c->dst_x, c->dst_y, c->dst_z,
            src, c->src_subresource_idx, QEMU_G2H(c->src_box));
}

#endif

struct qemu_d3d10_device_CopyResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_buffer;
    uint64_t dst_texture;
    uint64_t src_buffer;
    uint64_t src_texture;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_CopyResource(ID3D10Device1 *iface, ID3D10Resource *dst_resource,
        ID3D10Resource *src_resource)
{
    struct qemu_d3d10_device_CopyResource call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D10_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_COPYRESOURCE);
    call.iface = (ULONG_PTR)device;

    ID3D10Resource_GetType(dst_resource, &dim);
    switch (dim)
    {
        case D3D10_RESOURCE_DIMENSION_TEXTURE1D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture1D((ID3D10Texture1D *)dst_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE2D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture2D((ID3D10Texture2D *)dst_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE3D:
            call.dst_buffer = 0;
            call.dst_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture3D((ID3D10Texture3D *)dst_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_BUFFER:
            call.dst_buffer = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer((ID3D10Buffer *)dst_resource);
            call.dst_texture = 0;
            break;
    }

    ID3D10Resource_GetType(src_resource, &dim);
    switch (dim)
    {
        case D3D10_RESOURCE_DIMENSION_TEXTURE1D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture1D((ID3D10Texture1D *)src_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE2D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture2D((ID3D10Texture2D *)src_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE3D:
            call.src_buffer = 0;
            call.src_texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture3D((ID3D10Texture3D *)src_resource);
            break;

        case D3D10_RESOURCE_DIMENSION_BUFFER:
            call.src_buffer = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer((ID3D10Buffer *)src_resource);
            call.src_texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_CopyResource(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CopyResource *c = (struct qemu_d3d10_device_CopyResource *)call;
    struct qemu_d3d11_device *device;
    ID3D10Resource *src = NULL, *dst = NULL;
    struct qemu_d3d11_texture *tex;
    struct qemu_d3d11_buffer *buf;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->src_buffer)
    {
        buf = QEMU_G2H(c->src_buffer);
        src = (ID3D10Resource *)buf->host10;
    }
    else if (c->src_texture)
    {
        tex = QEMU_G2H(c->src_texture);
        src = (ID3D10Resource *)tex->host10_1d;
    }

    if (c->dst_buffer)
    {
        buf = QEMU_G2H(c->dst_buffer);
        dst = (ID3D10Resource *)buf->host10;
    }
    else if (c->dst_texture)
    {
        tex = QEMU_G2H(c->dst_texture);
        dst = (ID3D10Resource *)tex->host10_1d;
    }

    ID3D10Device1_CopyResource(device->host_d3d10, dst, src);
}

#endif

struct qemu_d3d10_device_UpdateSubresource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t texture;
    uint64_t subresource_idx;
    uint64_t box;
    uint64_t data;
    uint64_t row_pitch;
    uint64_t depth_pitch;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_UpdateSubresource(ID3D10Device1 *iface, ID3D10Resource *resource, UINT subresource_idx, const D3D10_BOX *box, const void *data, UINT row_pitch, UINT depth_pitch)
{
    struct qemu_d3d10_device_UpdateSubresource call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    D3D10_RESOURCE_DIMENSION dim;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_UPDATESUBRESOURCE);
    call.iface = (ULONG_PTR)device;
    call.subresource_idx = subresource_idx;
    call.box = (ULONG_PTR)box;
    call.data = (ULONG_PTR)data;
    call.row_pitch = row_pitch;
    call.depth_pitch = depth_pitch;

    ID3D10Resource_GetType(resource, &dim);
    switch (dim)
    {
        case D3D10_RESOURCE_DIMENSION_TEXTURE1D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture1D((ID3D10Texture1D *)resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE2D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture2D((ID3D10Texture2D *)resource);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE3D:
            call.buffer = 0;
            call.texture = (ULONG_PTR)unsafe_impl_from_ID3D10Texture3D((ID3D10Texture3D *)resource);
            break;

        case D3D10_RESOURCE_DIMENSION_BUFFER:
            call.buffer = (ULONG_PTR)unsafe_impl_from_ID3D10Buffer((ID3D10Buffer *)resource);
            call.texture = 0;
            break;
    }

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_UpdateSubresource(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_UpdateSubresource *c = (struct qemu_d3d10_device_UpdateSubresource *)call;
    struct qemu_d3d11_device *device;
    ID3D10Resource *resource = NULL;
    struct qemu_d3d11_buffer *buffer;
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    if (c->texture)
    {
        texture = QEMU_G2H(c->texture);
        resource = (ID3D10Resource *)texture->host10_1d;
    }
    else if (c->buffer)
    {
        buffer = QEMU_G2H(c->buffer);
        resource = (ID3D10Resource *)buffer->host10;
    }

    ID3D10Device1_UpdateSubresource(device->host_d3d10, resource, c->subresource_idx, QEMU_G2H(c->box),
            QEMU_G2H(c->data), c->row_pitch, c->depth_pitch);
}

#endif

struct qemu_d3d10_device_ClearRenderTargetView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target_view;
    uint64_t color_rgba;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_ClearRenderTargetView(ID3D10Device1 *iface,
        ID3D10RenderTargetView *render_target_view, const float color_rgba[4])
{
    struct qemu_d3d10_device_ClearRenderTargetView call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_view *view = unsafe_impl_from_ID3D10RenderTargetView(render_target_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CLEARRENDERTARGETVIEW);
    call.iface = (ULONG_PTR)device;
    call.render_target_view = (ULONG_PTR)view;
    call.color_rgba = (ULONG_PTR)color_rgba;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_ClearRenderTargetView(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_ClearRenderTargetView *c = (struct qemu_d3d10_device_ClearRenderTargetView *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_view *view;

    WINE_TRACE("Unverified!\n");
    device = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->render_target_view);

    ID3D10Device1_ClearRenderTargetView(device->host_d3d10, view ? view->host_rt10 : NULL, QEMU_G2H(c->color_rgba));
}

#endif

struct qemu_d3d10_device_ClearDepthStencilView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil_view;
    uint64_t flags;
    double depth;
    uint64_t stencil;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_ClearDepthStencilView(ID3D10Device1 *iface,
        ID3D10DepthStencilView *depth_stencil_view, UINT flags, FLOAT depth, UINT8 stencil)
{
    struct qemu_d3d10_device_ClearDepthStencilView call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_view *view = unsafe_impl_from_ID3D10DepthStencilView(depth_stencil_view);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CLEARDEPTHSTENCILVIEW);
    call.iface = (ULONG_PTR)device;
    call.depth_stencil_view = (ULONG_PTR)view;
    call.flags = flags;
    call.depth = depth;
    call.stencil = stencil;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_ClearDepthStencilView(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_ClearDepthStencilView *c = (struct qemu_d3d10_device_ClearDepthStencilView *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_view *view;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    view = QEMU_G2H(c->depth_stencil_view);

    ID3D10Device1_ClearDepthStencilView(device->host_d3d10, view ? view->host_ds10 : NULL,
            c->flags, c->depth, c->stencil);
}

#endif

struct qemu_d3d10_device_GenerateMips
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GenerateMips(ID3D10Device1 *iface, ID3D10ShaderResourceView *view)
{
    struct qemu_d3d10_device_GenerateMips call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GENERATEMIPS);
    call.iface = (ULONG_PTR)device;
    call.view = (ULONG_PTR)view;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_GenerateMips(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GenerateMips *c = (struct qemu_d3d10_device_GenerateMips *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_GenerateMips(device->host_d3d10, QEMU_G2H(c->view));
}

#endif

struct qemu_d3d10_device_ResolveSubresource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_resource;
    uint64_t dst_subresource_idx;
    uint64_t src_resource;
    uint64_t src_subresource_idx;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_ResolveSubresource(ID3D10Device1 *iface, ID3D10Resource *dst_resource, UINT dst_subresource_idx, ID3D10Resource *src_resource, UINT src_subresource_idx, DXGI_FORMAT format)
{
    struct qemu_d3d10_device_ResolveSubresource call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RESOLVESUBRESOURCE);
    call.iface = (ULONG_PTR)device;
    call.dst_resource = (ULONG_PTR)dst_resource;
    call.dst_subresource_idx = dst_subresource_idx;
    call.src_resource = (ULONG_PTR)src_resource;
    call.src_subresource_idx = src_subresource_idx;
    call.format = format;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_ResolveSubresource(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_ResolveSubresource *c = (struct qemu_d3d10_device_ResolveSubresource *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_ResolveSubresource(device->host_d3d10, QEMU_G2H(c->dst_resource), c->dst_subresource_idx, QEMU_G2H(c->src_resource), c->src_subresource_idx, c->format);
}

#endif

struct qemu_d3d10_device_VSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSGetConstantBuffers(ID3D10Device1 *iface, UINT start_slot,
        UINT buffer_count, ID3D10Buffer **buffers)
{
    struct qemu_d3d10_device_VSGetConstantBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D10Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d10_device_VSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSGetConstantBuffers *c = (struct qemu_d3d10_device_VSGetConstantBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_VSGetConstantBuffers(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d10_device_PSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSGetShaderResources(ID3D10Device1 *iface, UINT start_slot, UINT view_count, ID3D10ShaderResourceView **views)
{
    struct qemu_d3d10_device_PSGetShaderResources call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = (ID3D10ShaderResourceView *)&view->ID3D10ShaderResourceView1_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);

}

#else

void qemu_d3d10_device_PSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSGetShaderResources *c = (struct qemu_d3d10_device_PSGetShaderResources *)call;
    struct qemu_d3d11_device *device;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_PSGetShaderResources(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d10_device_PSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSGetShader(ID3D10Device1 *iface, ID3D10PixelShader **shader)
{
    struct qemu_d3d10_device_PSGetShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSGETSHADER);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D10PixelShader_iface : NULL;
}

#else

void qemu_d3d10_device_PSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSGetShader *c = (struct qemu_d3d10_device_PSGetShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11PixelShader *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_PSGetShader(device->immediate_context.host, &host, NULL, NULL);
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d10_device_PSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSGetSamplers(ID3D10Device1 *iface, UINT start_slot, UINT sampler_count, ID3D10SamplerState **samplers)
{
    struct qemu_d3d10_device_PSGetSamplers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSGETSAMPLERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D10SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d10_device_PSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSGetSamplers *c = (struct qemu_d3d10_device_PSGetSamplers *)call;
    struct qemu_d3d11_device *device;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext_PSGetSamplers(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d10_device_VSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSGetShader(ID3D10Device1 *iface, ID3D10VertexShader **shader)
{
    struct qemu_d3d10_device_VSGetShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSGETSHADER);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D10VertexShader_iface : NULL;
}

#else

void qemu_d3d10_device_VSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSGetShader *c = (struct qemu_d3d10_device_VSGetShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11VertexShader *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_VSGetShader(device->immediate_context.host, &host, NULL, NULL);
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d10_device_PSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_PSGetConstantBuffers(ID3D10Device1 *iface, UINT start_slot, UINT buffer_count, ID3D10Buffer **buffers)
{
    struct qemu_d3d10_device_PSGetConstantBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_PSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D10Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d10_device_PSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_PSGetConstantBuffers *c = (struct qemu_d3d10_device_PSGetConstantBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_PSGetConstantBuffers(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d10_device_IAGetInputLayout
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t input_layout;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IAGetInputLayout(ID3D10Device1 *iface, ID3D10InputLayout **input_layout)
{
    struct qemu_d3d10_device_IAGetInputLayout call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_input_layout *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IAGETINPUTLAYOUT);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_input_layout *)(ULONG_PTR)call.input_layout;
    *input_layout = impl ? &impl->ID3D10InputLayout_iface : NULL;
}

#else

void qemu_d3d10_device_IAGetInputLayout(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IAGetInputLayout *c = (struct qemu_d3d10_device_IAGetInputLayout *)call;
    struct qemu_d3d11_device *device;
    ID3D11InputLayout *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_IAGetInputLayout(device->immediate_context.host, &host);
    c->input_layout = QEMU_H2G(input_layout_from_host(host));
}

#endif

struct qemu_d3d10_device_IAGetVertexBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t strides;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IAGetVertexBuffers(ID3D10Device1 *iface, UINT start_slot, UINT buffer_count,
        ID3D10Buffer **buffers, UINT *strides, UINT *offsets)
{
    struct qemu_d3d10_device_IAGetVertexBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IAGETVERTEXBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;
    call.strides = (ULONG_PTR)strides;
    call.offsets = (ULONG_PTR)offsets;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D10Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d10_device_IAGetVertexBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IAGetVertexBuffers *c = (struct qemu_d3d10_device_IAGetVertexBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_IAGetVertexBuffers(device->immediate_context.host, c->start_slot, c->buffer_count, ifaces,
            QEMU_G2H(c->strides), QEMU_G2H(c->offsets));

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d10_device_IAGetIndexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
    uint64_t format;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IAGetIndexBuffer(ID3D10Device1 *iface, ID3D10Buffer **buffer, DXGI_FORMAT *format, UINT *offset)
{
    struct qemu_d3d10_device_IAGetIndexBuffer call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_buffer *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IAGETINDEXBUFFER);
    call.iface = (ULONG_PTR)device;
    call.format = (ULONG_PTR)format;
    call.offset = (ULONG_PTR)offset;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_buffer *)(ULONG_PTR)call.buffer;
    *buffer = impl ? &impl->ID3D10Buffer_iface : NULL;
}

#else

void qemu_d3d10_device_IAGetIndexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IAGetIndexBuffer *c = (struct qemu_d3d10_device_IAGetIndexBuffer *)call;
    struct qemu_d3d11_device *device;
    ID3D11Buffer *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_IAGetIndexBuffer(device->immediate_context.host, &host, QEMU_G2H(c->format),
            QEMU_G2H(c->offset));
    c->buffer = QEMU_H2G(buffer_from_host(host));
}

#endif

struct qemu_d3d10_device_GSGetConstantBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t buffer_count;
    uint64_t buffers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSGetConstantBuffers(ID3D10Device1 *iface, UINT start_slot, UINT buffer_count, ID3D10Buffer **buffers)
{
    struct qemu_d3d10_device_GSGetConstantBuffers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSGETCONSTANTBUFFERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.buffer_count = buffer_count;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D10Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d10_device_GSGetConstantBuffers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSGetConstantBuffers *c = (struct qemu_d3d10_device_GSGetConstantBuffers *)call;
    struct qemu_d3d11_device *device;
    ID3D11Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D11DeviceContext1_GSGetConstantBuffers(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host(ifaces[i]);
}

#endif

struct qemu_d3d10_device_GSGetShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSGetShader(ID3D10Device1 *iface, ID3D10GeometryShader **shader)
{
    struct qemu_d3d10_device_GSGetShader call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_shader *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSGETSHADER);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    impl = (struct qemu_d3d11_shader *)(ULONG_PTR)call.shader;
    *shader = impl ? &impl->ID3D10GeometryShader_iface : NULL;
}

#else

void qemu_d3d10_device_GSGetShader(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSGetShader *c = (struct qemu_d3d10_device_GSGetShader *)call;
    struct qemu_d3d11_device *device;
    ID3D11GeometryShader *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_GSGetShader(device->immediate_context.host, &host, NULL, NULL);
    c->shader = QEMU_H2G(shader_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d10_device_IAGetPrimitiveTopology
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t topology;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_IAGetPrimitiveTopology(ID3D10Device1 *iface,
        D3D10_PRIMITIVE_TOPOLOGY *topology)
{
    struct qemu_d3d10_device_IAGetPrimitiveTopology call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_IAGETPRIMITIVETOPOLOGY);
    call.iface = (ULONG_PTR)device;
    call.topology = (ULONG_PTR)topology;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_IAGetPrimitiveTopology(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_IAGetPrimitiveTopology *c = (struct qemu_d3d10_device_IAGetPrimitiveTopology *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_IAGetPrimitiveTopology(device->host_d3d10, QEMU_G2H(c->topology));
}

#endif

struct qemu_d3d10_device_VSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSGetShaderResources(ID3D10Device1 *iface, UINT start_slot, UINT view_count, ID3D10ShaderResourceView **views)
{
    struct qemu_d3d10_device_VSGetShaderResources call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = (ID3D10ShaderResourceView *)&view->ID3D10ShaderResourceView1_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);
}

#else

void qemu_d3d10_device_VSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSGetShaderResources *c = (struct qemu_d3d10_device_VSGetShaderResources *)call;
    struct qemu_d3d11_device *device;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_VSGetShaderResources(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d10_device_VSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_VSGetSamplers(ID3D10Device1 *iface, UINT start_slot, UINT sampler_count, ID3D10SamplerState **samplers)
{
    struct qemu_d3d10_device_VSGetSamplers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_VSGETSAMPLERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D10SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d10_device_VSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_VSGetSamplers *c = (struct qemu_d3d10_device_VSGetSamplers *)call;
    struct qemu_d3d11_device *device;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext_VSGetSamplers(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d10_device_GetPredication
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t predicate;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GetPredication(ID3D10Device1 *iface, ID3D10Predicate **predicate, BOOL *value)
{
    struct qemu_d3d10_device_GetPredication call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_query *query;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GETPREDICATION);
    call.iface = (ULONG_PTR)device;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    query = (struct qemu_d3d11_query *)(ULONG_PTR)call.predicate;
    *predicate = query ? (ID3D10Predicate *)&query->ID3D10Query_iface : NULL;
}

#else

void qemu_d3d10_device_GetPredication(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GetPredication *c = (struct qemu_d3d10_device_GetPredication *)call;
    struct qemu_d3d11_device *device;
    ID3D11Query *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_GetPredication(device->immediate_context.host, (ID3D11Predicate **)&host, QEMU_G2H(c->value));
    c->predicate = QEMU_H2G(query_from_host(host));
}

#endif

struct qemu_d3d10_device_GSGetShaderResources
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t view_count;
    uint64_t views;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSGetShaderResources(ID3D10Device1 *iface, UINT start_slot, UINT view_count, ID3D10ShaderResourceView **views)
{
    struct qemu_d3d10_device_GSGetShaderResources call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *view_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSGETSHADERRESOURCES);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.view_count = view_count;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
        view_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*view_impl) * view_count);

    call.views = (ULONG_PTR)view_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        struct qemu_d3d11_view *view;

        if (!view_impl[i])
        {
            views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)view_impl[i];
        views[i] = (ID3D10ShaderResourceView *)&view->ID3D10ShaderResourceView1_iface;
    }

    if (view_impl != stack)
        HeapFree(GetProcessHeap(), 0, view_impl);

}

#else

void qemu_d3d10_device_GSGetShaderResources(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSGetShaderResources *c = (struct qemu_d3d10_device_GSGetShaderResources *)call;
    struct qemu_d3d11_device *device;
    ID3D11ShaderResourceView **ifaces;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->views);
    view_impl = QEMU_G2H(c->views);
    count = c->view_count;

    ID3D11DeviceContext1_GSGetShaderResources(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d10_device_GSGetSamplers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start_slot;
    uint64_t sampler_count;
    uint64_t samplers;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GSGetSamplers(ID3D10Device1 *iface, UINT start_slot, UINT sampler_count, ID3D10SamplerState **samplers)
{
    struct qemu_d3d10_device_GSGetSamplers call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GSGETSAMPLERS);
    call.iface = (ULONG_PTR)device;
    call.start_slot = start_slot;
    call.sampler_count = sampler_count;
    uint64_t stack[16], *sampler_impl = stack;
    UINT i;

    if (sampler_count > (sizeof(stack) / sizeof(*stack)))
        sampler_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*sampler_impl) * sampler_count);

    call.samplers = (ULONG_PTR)sampler_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < sampler_count; ++i)
    {
        struct qemu_d3d11_state *sampler;

        if (!sampler_impl[i])
        {
            samplers[i] = NULL;
            continue;
        }

        sampler = (struct qemu_d3d11_state *)(ULONG_PTR)sampler_impl[i];
        samplers[i] = &sampler->ID3D10SamplerState_iface;
    }

    if (sampler_impl != stack)
        HeapFree(GetProcessHeap(), 0, sampler_impl);
}

#else

void qemu_d3d10_device_GSGetSamplers(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GSGetSamplers *c = (struct qemu_d3d10_device_GSGetSamplers *)call;
    struct qemu_d3d11_device *device;
    ID3D11SamplerState **ifaces;
    struct qemu_d3d11_state **sampler_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->samplers);
    sampler_impl = QEMU_G2H(c->samplers);
    count = c->sampler_count;

    ID3D11DeviceContext_GSGetSamplers(device->immediate_context.host, c->start_slot, count, ifaces);

    for (i = 0; i < count; ++i)
        sampler_impl[i] = state_from_host((ID3D11DeviceChild *)ifaces[i]);
}

#endif

struct qemu_d3d10_device_OMGetRenderTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view_count;
    uint64_t render_target_views;
    uint64_t depth_stencil_view;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_OMGetRenderTargets(ID3D10Device1 *iface, UINT view_count,
        ID3D10RenderTargetView **render_target_views, ID3D10DepthStencilView **depth_stencil_view)
{
    struct qemu_d3d10_device_OMGetRenderTargets call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_view *view;
    uint64_t stack[16], *rtv_impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OMGETRENDERTARGETS);
    call.iface = (ULONG_PTR)device;
    call.view_count = view_count;
    call.depth_stencil_view = (ULONG_PTR)depth_stencil_view;

    if (view_count > (sizeof(stack) / sizeof(*stack)))
    {
        rtv_impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*rtv_impl) * view_count);
        if (!rtv_impl)
            WINE_ERR("Out of memory\n");
    }

    call.render_target_views = (ULONG_PTR)rtv_impl;

    qemu_syscall(&call.super);

    for (i = 0; i < view_count; ++i)
    {
        if (!rtv_impl[i])
        {
            render_target_views[i] = NULL;
            continue;
        }

        view = (struct qemu_d3d11_view *)(ULONG_PTR)rtv_impl[i];
        render_target_views[i] = &view->ID3D10RenderTargetView_iface;
    }

    if (rtv_impl != stack)
        HeapFree(GetProcessHeap(), 0, rtv_impl);

    if (call.depth_stencil_view)
    {
        view = (struct qemu_d3d11_view *)(ULONG_PTR)call.depth_stencil_view;
        *depth_stencil_view = &view->ID3D10DepthStencilView_iface;
    }
    else if (depth_stencil_view)
    {
        *depth_stencil_view = NULL;
    }
}

#else

void qemu_d3d10_device_OMGetRenderTargets(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OMGetRenderTargets *c = (struct qemu_d3d10_device_OMGetRenderTargets *)call;
    struct qemu_d3d11_device *device;
    ID3D11RenderTargetView **ifaces;
    ID3D11DepthStencilView *host_ds = NULL;
    struct qemu_d3d11_view **view_impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    ifaces = QEMU_G2H(c->render_target_views);
    view_impl = QEMU_G2H(c->render_target_views);
    count = c->view_count;

    ID3D11DeviceContext1_OMGetRenderTargets(device->immediate_context.host, count, ifaces, 
            c->depth_stencil_view ? &host_ds : NULL);

    for (i = 0; i < count; ++i)
        view_impl[i] = view_from_host((ID3D11DeviceChild *)ifaces[i]);

    c->depth_stencil_view = QEMU_H2G(view_from_host((ID3D11DeviceChild *)host_ds));
}

#endif

struct qemu_d3d10_device_OMGetBlendState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t blend_state;
    uint64_t blend_factor;
    uint64_t sample_mask;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_OMGetBlendState(ID3D10Device1 *iface, ID3D10BlendState **blend_state,
        FLOAT blend_factor[4], UINT *sample_mask)
{
    struct qemu_d3d10_device_OMGetBlendState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_state *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OMGETBLENDSTATE);
    call.iface = (ULONG_PTR)device;
    call.blend_factor = (ULONG_PTR)blend_factor;
    call.sample_mask = (ULONG_PTR)sample_mask;

    qemu_syscall(&call.super);
    impl = (struct qemu_d3d11_state *)(ULONG_PTR)call.blend_state;
    *blend_state = impl ? (ID3D10BlendState *)&impl->ID3D10BlendState1_iface : NULL;
}

#else

void qemu_d3d10_device_OMGetBlendState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OMGetBlendState *c = (struct qemu_d3d10_device_OMGetBlendState *)call;
    struct qemu_d3d11_device *device;
    ID3D11BlendState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_OMGetBlendState(device->immediate_context.host, &host, QEMU_G2H(c->blend_factor),
            QEMU_G2H(c->sample_mask));
    c->blend_state = QEMU_H2G(state_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d10_device_OMGetDepthStencilState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil_state;
    uint64_t stencil_ref;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_OMGetDepthStencilState(ID3D10Device1 *iface,
        ID3D10DepthStencilState **depth_stencil_state, UINT *stencil_ref)
{
    struct qemu_d3d10_device_OMGetDepthStencilState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_state *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OMGETDEPTHSTENCILSTATE);
    call.iface = (ULONG_PTR)device;
    call.stencil_ref = (ULONG_PTR)stencil_ref;

    qemu_syscall(&call.super);
    impl = (struct qemu_d3d11_state *)(ULONG_PTR)call.depth_stencil_state;
    *depth_stencil_state = impl ? &impl->ID3D10DepthStencilState_iface : NULL;
}

#else

void qemu_d3d10_device_OMGetDepthStencilState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OMGetDepthStencilState *c = (struct qemu_d3d10_device_OMGetDepthStencilState *)call;
    struct qemu_d3d11_device *device;
    ID3D11DepthStencilState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_OMGetDepthStencilState(device->immediate_context.host, &host, QEMU_G2H(c->stencil_ref));
    c->depth_stencil_state = QEMU_H2G(state_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d10_device_SOGetTargets
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer_count;
    uint64_t buffers;
    uint64_t offsets;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_SOGetTargets(ID3D10Device1 *iface, UINT buffer_count,
            ID3D10Buffer **buffers, UINT *offsets)
{
    struct qemu_d3d10_device_SOGetTargets call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    uint64_t stack[16], *impl = stack;
    UINT i;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_SOGETTARGETS);
    call.iface = (ULONG_PTR)device;
    call.buffer_count = buffer_count;
    call.offsets = (ULONG_PTR)offsets;

    if (buffer_count > (sizeof(stack) / sizeof(*stack)))
        impl = HeapAlloc(GetProcessHeap(), 0, sizeof(*impl) * buffer_count);

    call.buffers = (ULONG_PTR)impl;

    qemu_syscall(&call.super);

    for (i = 0; i < buffer_count; ++i)
    {
        struct qemu_d3d11_buffer *buffer;

        if (!impl[i])
        {
            buffers[i] = NULL;
            continue;
        }

        buffer = (struct qemu_d3d11_buffer *)(ULONG_PTR)impl[i];
        buffers[i] = &buffer->ID3D10Buffer_iface;
    }

    if (impl != stack)
        HeapFree(GetProcessHeap(), 0, impl);
}

#else

void qemu_d3d10_device_SOGetTargets(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_SOGetTargets *c = (struct qemu_d3d10_device_SOGetTargets *)call;
    struct qemu_d3d11_device *device;
    ID3D10Buffer **ifaces;
    struct qemu_d3d11_buffer **impl;
    UINT i, count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ifaces = QEMU_G2H(c->buffers);
    impl = QEMU_G2H(c->buffers);
    count = c->buffer_count;

    ID3D10Device1_SOGetTargets(device->host_d3d10, count, ifaces, QEMU_G2H(c->offsets));

    for (i = 0; i < count; ++i)
        impl[i] = buffer_from_host10(ifaces[i]);
}

#endif

struct qemu_d3d10_device_RSGetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rasterizer_state;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_RSGetState(ID3D10Device1 *iface, ID3D10RasterizerState **rasterizer_state)
{
    struct qemu_d3d10_device_RSGetState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct qemu_d3d11_state *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RSGETSTATE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);
    impl = (struct qemu_d3d11_state *)(ULONG_PTR)call.rasterizer_state;
    *rasterizer_state = impl ? &impl->ID3D10RasterizerState_iface : NULL;
}

#else

void qemu_d3d10_device_RSGetState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_RSGetState *c = (struct qemu_d3d10_device_RSGetState *)call;
    struct qemu_d3d11_device *device;
    ID3D11RasterizerState *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D11DeviceContext1_RSGetState(device->immediate_context.host, &host);
    c->rasterizer_state = QEMU_H2G(state_from_host((ID3D11DeviceChild *)host));
}

#endif

struct qemu_d3d10_device_RSGetViewports
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport_count;
    uint64_t viewports;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_RSGetViewports(ID3D10Device1 *iface, UINT *viewport_count, D3D10_VIEWPORT *viewports)
{
    struct qemu_d3d10_device_RSGetViewports call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RSGETVIEWPORTS);
    call.iface = (ULONG_PTR)device;
    call.viewport_count = (ULONG_PTR)viewport_count;
    call.viewports = (ULONG_PTR)viewports;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_RSGetViewports(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_RSGetViewports *c = (struct qemu_d3d10_device_RSGetViewports *)call;
    struct qemu_d3d11_device *device;

    /* D3D10_VIEWPORT has the same size in 32 and 64 bit and the input array is not an array of pointers. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_RSGetViewports(device->host_d3d10, QEMU_G2H(c->viewport_count), QEMU_G2H(c->viewports));
}

#endif

struct qemu_d3d10_device_RSGetScissorRects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_RSGetScissorRects(ID3D10Device1 *iface, UINT *rect_count, D3D10_RECT *rects)
{
    struct qemu_d3d10_device_RSGetScissorRects call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_RSGETSCISSORRECTS);
    call.iface = (ULONG_PTR)device;
    call.rect_count = (ULONG_PTR)rect_count;
    call.rects = (ULONG_PTR)rects;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_RSGetScissorRects(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_RSGetScissorRects *c = (struct qemu_d3d10_device_RSGetScissorRects *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_RSGetScissorRects(device->host_d3d10, QEMU_G2H(c->rect_count), QEMU_G2H(c->rects));
}

#endif

struct qemu_d3d10_device_GetDeviceRemovedReason
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_GetDeviceRemovedReason(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_GetDeviceRemovedReason call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GETDEVICEREMOVEDREASON);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_GetDeviceRemovedReason(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GetDeviceRemovedReason *c = (struct qemu_d3d10_device_GetDeviceRemovedReason *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_GetDeviceRemovedReason(device->host_d3d10);
}

#endif

struct qemu_d3d10_device_SetExceptionMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_SetExceptionMode(ID3D10Device1 *iface, UINT flags)
{
    struct qemu_d3d10_device_SetExceptionMode call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_SETEXCEPTIONMODE);
    call.iface = (ULONG_PTR)device;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_SetExceptionMode(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_SetExceptionMode *c = (struct qemu_d3d10_device_SetExceptionMode *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_SetExceptionMode(device->host_d3d10, c->flags);
}

#endif

struct qemu_d3d10_device_GetExceptionMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_device_GetExceptionMode(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_GetExceptionMode call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GETEXCEPTIONMODE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_GetExceptionMode(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GetExceptionMode *c = (struct qemu_d3d10_device_GetExceptionMode *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_GetExceptionMode(device->host_d3d10);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_GetPrivateData(ID3D10Device1 *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d11_device_GetPrivateData(&device->ID3D11Device2_iface, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_device_SetPrivateData(ID3D10Device1 *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return d3d11_device_SetPrivateData(&device->ID3D11Device2_iface, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE d3d10_device_SetPrivateDataInterface(ID3D10Device1 *iface,
        REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    WINE_TRACE("iface %p, guid %s, data %p.\n", iface, wine_dbgstr_guid(guid), data);

    return d3d11_device_SetPrivateDataInterface(&device->ID3D11Device2_iface, guid, data);
}

#endif

struct qemu_d3d10_device_ClearState
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_ClearState(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_ClearState call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CLEARSTATE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_ClearState(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_ClearState *c = (struct qemu_d3d10_device_ClearState *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_ClearState(device->host_d3d10);
}

#endif

struct qemu_d3d10_device_Flush
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_Flush(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_Flush call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_FLUSH);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_Flush(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_Flush *c = (struct qemu_d3d10_device_Flush *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_Flush(device->host_d3d10);
}

#endif

struct qemu_d3d10_device_CreateShaderResourceView1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
    uint64_t desc;
    uint64_t view;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateShaderResourceView1(ID3D10Device1 *iface, ID3D10Resource *resource, const D3D10_SHADER_RESOURCE_VIEW_DESC1 *desc, ID3D10ShaderResourceView1 **view)
{
    struct qemu_d3d10_device_CreateShaderResourceView1 call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CREATESHADERRESOURCEVIEW1);
    call.iface = (ULONG_PTR)device;
    call.resource = (ULONG_PTR)resource;
    call.desc = (ULONG_PTR)desc;
    call.view = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_CreateShaderResourceView1(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CreateShaderResourceView1 *c = (struct qemu_d3d10_device_CreateShaderResourceView1 *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CreateShaderResourceView1(device->host_d3d10, QEMU_G2H(c->resource), QEMU_G2H(c->desc), QEMU_G2H(c->view));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateShaderResourceView(ID3D10Device1 *iface,
        ID3D10Resource *resource, const D3D10_SHADER_RESOURCE_VIEW_DESC *desc, ID3D10ShaderResourceView **view)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    struct d3d_shader_resource_view *object;
    ID3D11Resource *d3d11_resource;
    ID3D11ShaderResourceView *view11;
    HRESULT hr;

    WINE_TRACE("iface %p, resource %p, desc %p, view %p.\n", iface, resource, desc, view);

    if (!resource)
        return E_INVALIDARG;

    if (FAILED(hr = ID3D10Resource_QueryInterface(resource, &IID_ID3D11Resource, (void **)&d3d11_resource)))
    {
        WINE_ERR("Resource does not implement ID3D11Resource.\n");
        return E_FAIL;
    }

    hr = d3d11_device_CreateShaderResourceView(&device->ID3D11Device2_iface, d3d11_resource,
            (const D3D11_SHADER_RESOURCE_VIEW_DESC *)desc, &view11);
    ID3D11Resource_Release(d3d11_resource);
    if (FAILED(hr))
        return hr;

    hr = ID3D11ShaderResourceView_QueryInterface(view11, &IID_ID3D10ShaderResourceView, (void **)view);
    ID3D11ShaderResourceView_Release(view11);
    return hr;
}

#endif

struct qemu_d3d10_device_CreateInputLayout
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t element_descs;
    uint64_t element_count;
    uint64_t shader_byte_code;
    uint64_t shader_byte_code_length;
    uint64_t input_layout;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateInputLayout(ID3D10Device1 *iface,
        const D3D10_INPUT_ELEMENT_DESC *element_descs, UINT element_count, const void *shader_byte_code,
        SIZE_T shader_byte_code_length, ID3D10InputLayout **input_layout)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);
    ID3D11InputLayout *layout11;
    HRESULT hr;

    hr = d3d11_device_CreateInputLayout(&device->ID3D11Device2_iface, (const D3D11_INPUT_ELEMENT_DESC *)element_descs,
            element_count, shader_byte_code, shader_byte_code_length, &layout11);
    if (FAILED(hr))
        return hr;

    hr = ID3D11InputLayout_QueryInterface(layout11, &IID_ID3D10InputLayout, (void **)input_layout);
    ID3D11InputLayout_Release(layout11);
    return hr;
}

#else

void qemu_d3d10_device_CreateInputLayout(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CreateInputLayout *c = (struct qemu_d3d10_device_CreateInputLayout *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CreateInputLayout(device->host_d3d10, QEMU_G2H(c->element_descs), c->element_count, QEMU_G2H(c->shader_byte_code), c->shader_byte_code_length, QEMU_G2H(c->input_layout));
}

#endif

struct qemu_d3d10_device_CreateGeometryShaderWithStreamOutput
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t byte_code_length;
    uint64_t output_stream_decls;
    uint64_t output_stream_decl_count;
    uint64_t output_stream_stride;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateGeometryShaderWithStreamOutput(ID3D10Device1 *iface, const void *byte_code, SIZE_T byte_code_length, const D3D10_SO_DECLARATION_ENTRY *output_stream_decls, UINT output_stream_decl_count, UINT output_stream_stride, ID3D10GeometryShader **shader)
{
    struct qemu_d3d10_device_CreateGeometryShaderWithStreamOutput call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CREATEGEOMETRYSHADERWITHSTREAMOUTPUT);
    call.iface = (ULONG_PTR)device;
    call.byte_code = (ULONG_PTR)byte_code;
    call.byte_code_length = byte_code_length;
    call.output_stream_decls = (ULONG_PTR)output_stream_decls;
    call.output_stream_decl_count = output_stream_decl_count;
    call.output_stream_stride = output_stream_stride;
    call.shader = (ULONG_PTR)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_CreateGeometryShaderWithStreamOutput(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CreateGeometryShaderWithStreamOutput *c = (struct qemu_d3d10_device_CreateGeometryShaderWithStreamOutput *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CreateGeometryShaderWithStreamOutput(device->host_d3d10, QEMU_G2H(c->byte_code), c->byte_code_length, QEMU_G2H(c->output_stream_decls), c->output_stream_decl_count, c->output_stream_stride, QEMU_G2H(c->shader));
}

#endif

struct qemu_d3d10_device_CreateCounter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t counter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CreateCounter(ID3D10Device1 *iface, const D3D10_COUNTER_DESC *desc, ID3D10Counter **counter)
{
    struct qemu_d3d10_device_CreateCounter call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CREATECOUNTER);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.counter = (ULONG_PTR)counter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_CreateCounter(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CreateCounter *c = (struct qemu_d3d10_device_CreateCounter *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CreateCounter(device->host_d3d10, QEMU_G2H(c->desc), QEMU_G2H(c->counter));
}

#endif

struct qemu_d3d10_device_CheckFormatSupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t format_support;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CheckFormatSupport(ID3D10Device1 *iface, DXGI_FORMAT format, UINT *format_support)
{
    struct qemu_d3d10_device_CheckFormatSupport call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CHECKFORMATSUPPORT);
    call.iface = (ULONG_PTR)device;
    call.format = format;
    call.format_support = (ULONG_PTR)format_support;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_CheckFormatSupport(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CheckFormatSupport *c = (struct qemu_d3d10_device_CheckFormatSupport *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CheckFormatSupport(device->host_d3d10, c->format, QEMU_G2H(c->format_support));
}

#endif

struct qemu_d3d10_device_CheckMultisampleQualityLevels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t sample_count;
    uint64_t quality_level_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CheckMultisampleQualityLevels(ID3D10Device1 *iface, DXGI_FORMAT format, UINT sample_count, UINT *quality_level_count)
{
    struct qemu_d3d10_device_CheckMultisampleQualityLevels call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CHECKMULTISAMPLEQUALITYLEVELS);
    call.iface = (ULONG_PTR)device;
    call.format = format;
    call.sample_count = sample_count;
    call.quality_level_count = (ULONG_PTR)quality_level_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_CheckMultisampleQualityLevels(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CheckMultisampleQualityLevels *c = (struct qemu_d3d10_device_CheckMultisampleQualityLevels *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CheckMultisampleQualityLevels(device->host_d3d10, c->format, c->sample_count, QEMU_G2H(c->quality_level_count));
}

#endif

struct qemu_d3d10_device_CheckCounterInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t counter_info;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_CheckCounterInfo(ID3D10Device1 *iface, D3D10_COUNTER_INFO *counter_info)
{
    struct qemu_d3d10_device_CheckCounterInfo call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CHECKCOUNTERINFO);
    call.iface = (ULONG_PTR)device;
    call.counter_info = (ULONG_PTR)counter_info;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_CheckCounterInfo(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CheckCounterInfo *c = (struct qemu_d3d10_device_CheckCounterInfo *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_CheckCounterInfo(device->host_d3d10, QEMU_G2H(c->counter_info));
}

#endif

struct qemu_d3d10_device_CheckCounter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t type;
    uint64_t active_counters;
    uint64_t name;
    uint64_t name_length;
    uint64_t units;
    uint64_t units_length;
    uint64_t description;
    uint64_t description_length;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_CheckCounter(ID3D10Device1 *iface, const D3D10_COUNTER_DESC *desc, D3D10_COUNTER_TYPE *type, UINT *active_counters, char *name, UINT *name_length, char *units, UINT *units_length, char *description, UINT *description_length)
{
    struct qemu_d3d10_device_CheckCounter call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_CHECKCOUNTER);
    call.iface = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.type = (ULONG_PTR)type;
    call.active_counters = (ULONG_PTR)active_counters;
    call.name = (ULONG_PTR)name;
    call.name_length = (ULONG_PTR)name_length;
    call.units = (ULONG_PTR)units;
    call.units_length = (ULONG_PTR)units_length;
    call.description = (ULONG_PTR)description;
    call.description_length = (ULONG_PTR)description_length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_CheckCounter(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_CheckCounter *c = (struct qemu_d3d10_device_CheckCounter *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_CheckCounter(device->host_d3d10, QEMU_G2H(c->desc), QEMU_G2H(c->type), QEMU_G2H(c->active_counters), QEMU_G2H(c->name), QEMU_G2H(c->name_length), QEMU_G2H(c->units), QEMU_G2H(c->units_length), QEMU_G2H(c->description), QEMU_G2H(c->description_length));
}

#endif

struct qemu_d3d10_device_GetCreationFlags
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE d3d10_device_GetCreationFlags(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_GetCreationFlags call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GETCREATIONFLAGS);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_GetCreationFlags(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GetCreationFlags *c = (struct qemu_d3d10_device_GetCreationFlags *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_GetCreationFlags(device->host_d3d10);
}

#endif

struct qemu_d3d10_device_OpenSharedResource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource_handle;
    uint64_t guid;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_device_OpenSharedResource(ID3D10Device1 *iface, HANDLE resource_handle, REFIID guid, void **resource)
{
    struct qemu_d3d10_device_OpenSharedResource call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_OPENSHAREDRESOURCE);
    call.iface = (ULONG_PTR)device;
    call.resource_handle = (ULONG_PTR)resource_handle;
    call.guid = (ULONG_PTR)guid;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_OpenSharedResource(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_OpenSharedResource *c = (struct qemu_d3d10_device_OpenSharedResource *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_OpenSharedResource(device->host_d3d10, QEMU_G2H(c->resource_handle), QEMU_G2H(c->guid), QEMU_G2H(c->resource));
}

#endif

struct qemu_d3d10_device_SetTextFilterSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_SetTextFilterSize(ID3D10Device1 *iface, UINT width, UINT height)
{
    struct qemu_d3d10_device_SetTextFilterSize call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_SETTEXTFILTERSIZE);
    call.iface = (ULONG_PTR)device;
    call.width = width;
    call.height = height;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_SetTextFilterSize(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_SetTextFilterSize *c = (struct qemu_d3d10_device_SetTextFilterSize *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_SetTextFilterSize(device->host_d3d10, c->width, c->height);
}

#endif

struct qemu_d3d10_device_GetTextFilterSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_device_GetTextFilterSize(ID3D10Device1 *iface, UINT *width, UINT *height)
{
    struct qemu_d3d10_device_GetTextFilterSize call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GETTEXTFILTERSIZE);
    call.iface = (ULONG_PTR)device;
    call.width = (ULONG_PTR)width;
    call.height = (ULONG_PTR)height;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_device_GetTextFilterSize(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GetTextFilterSize *c = (struct qemu_d3d10_device_GetTextFilterSize *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Device1_GetTextFilterSize(device->host_d3d10, QEMU_G2H(c->width), QEMU_G2H(c->height));
}

#endif

struct qemu_d3d10_device_GetFeatureLevel
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3D10_FEATURE_LEVEL1 STDMETHODCALLTYPE d3d10_device_GetFeatureLevel(ID3D10Device1 *iface)
{
    struct qemu_d3d10_device_GetFeatureLevel call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Device(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEVICE_GETFEATURELEVEL);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_device_GetFeatureLevel(struct qemu_syscall *call)
{
    struct qemu_d3d10_device_GetFeatureLevel *c = (struct qemu_d3d10_device_GetFeatureLevel *)call;
    struct qemu_d3d11_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Device1_GetFeatureLevel(device->host_d3d10);
}

#endif

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_device *impl_from_ID3D10Multithread(ID3D10Multithread *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device, ID3D10Multithread_iface);
}

static HRESULT STDMETHODCALLTYPE d3d10_multithread_QueryInterface(ID3D10Multithread *iface, REFIID iid, void **out)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    WINE_TRACE("iface %p, iid %s, out %p.\n", iface, wine_dbgstr_guid(iid), out);

    return IUnknown_QueryInterface(device->outer_unk, iid, out);
}

static ULONG STDMETHODCALLTYPE d3d10_multithread_AddRef(ID3D10Multithread *iface)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(device->outer_unk);
}

static ULONG STDMETHODCALLTYPE d3d10_multithread_Release(ID3D10Multithread *iface)
{
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(device->outer_unk);
}

#endif

struct qemu_d3d10_multithread_Enter
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_multithread_Enter(ID3D10Multithread *iface)
{
    struct qemu_d3d10_multithread_Enter call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_MULTITHREAD_ENTER);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_multithread_Enter(struct qemu_syscall *call)
{
    struct qemu_d3d10_multithread_Enter *c = (struct qemu_d3d10_multithread_Enter *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Multithread_Enter(device->host_mt);
}

#endif

struct qemu_d3d10_multithread_Leave
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_multithread_Leave(ID3D10Multithread *iface)
{
    struct qemu_d3d10_multithread_Leave call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_MULTITHREAD_LEAVE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_multithread_Leave(struct qemu_syscall *call)
{
    struct qemu_d3d10_multithread_Leave *c = (struct qemu_d3d10_multithread_Leave *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    ID3D10Multithread_Leave(device->host_mt);
}

#endif

struct qemu_d3d10_multithread_SetMultithreadProtected
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t protect;
};

#ifdef QEMU_DLL_GUEST

static BOOL STDMETHODCALLTYPE d3d10_multithread_SetMultithreadProtected(ID3D10Multithread *iface, BOOL protect)
{
    struct qemu_d3d10_multithread_SetMultithreadProtected call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_MULTITHREAD_SETMULTITHREADPROTECTED);
    call.iface = (ULONG_PTR)device;
    call.protect = protect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_multithread_SetMultithreadProtected(struct qemu_syscall *call)
{
    struct qemu_d3d10_multithread_SetMultithreadProtected *c = (struct qemu_d3d10_multithread_SetMultithreadProtected *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Multithread_SetMultithreadProtected(device->host_mt, c->protect);
}

#endif

struct qemu_d3d10_multithread_GetMultithreadProtected
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static BOOL STDMETHODCALLTYPE d3d10_multithread_GetMultithreadProtected(ID3D10Multithread *iface)
{
    struct qemu_d3d10_multithread_GetMultithreadProtected call;
    struct qemu_d3d11_device *device = impl_from_ID3D10Multithread(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_MULTITHREAD_GETMULTITHREADPROTECTED);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_multithread_GetMultithreadProtected(struct qemu_syscall *call)
{
    struct qemu_d3d10_multithread_GetMultithreadProtected *c = (struct qemu_d3d10_multithread_GetMultithreadProtected *)call;
    struct qemu_d3d11_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = ID3D10Multithread_GetMultithreadProtected(device->host_mt);
}

#endif

struct qemu_wrap_implicit_surface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t host_dxgi;
    uint64_t texture;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_device *impl_from_IQemuD3D11Device(IQemuD3D11Device *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device, IQemuD3D11Device_iface);
}

static HRESULT STDMETHODCALLTYPE qemu_device_QueryInterface(IQemuD3D11Device *iface, REFIID riid, void **out)
{
    struct qemu_d3d11_device *device = impl_from_IQemuD3D11Device(iface);
    return IUnknown_QueryInterface(device->outer_unk, riid, out);
}

static ULONG STDMETHODCALLTYPE qemu_device_AddRef(IQemuD3D11Device *iface)
{
    struct qemu_d3d11_device *device = impl_from_IQemuD3D11Device(iface);
    return IUnknown_AddRef(device->outer_unk);
}

static ULONG STDMETHODCALLTYPE qemu_device_Release(IQemuD3D11Device *iface)
{
    struct qemu_d3d11_device *device = impl_from_IQemuD3D11Device(iface);
    return IUnknown_Release(device->outer_unk);
}

static HRESULT STDMETHODCALLTYPE qemu_device_wrap_implicit_surface(IQemuD3D11Device *iface, uint64_t host,
        IUnknown **surface)
{
    struct qemu_wrap_implicit_surface call;
    struct qemu_d3d11_device *device = impl_from_IQemuD3D11Device(iface);
    struct qemu_d3d11_texture *texture;

    WINE_TRACE("Creating d3d11 texture for host DXGI surface %p.\n", (void *)(ULONG_PTR)host);

    call.super.id = QEMU_SYSCALL_ID(CALL_WRAP_IMPLICIT_SURFACE);
    call.iface = (ULONG_PTR)device;
    call.host_dxgi = host;
    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    texture = (struct qemu_d3d11_texture *)(ULONG_PTR)call.texture;
    qemu_d3d11_texture_guest_init(texture, device, 2, host);
    *surface = (IUnknown *)&texture->ID3D11Texture2D_iface;
    IUnknown_AddRef(*surface);

    return S_OK;
}

static struct IQemuD3D11DeviceVtbl qemu_device_vtbl =
{
    /* IUnknown methods */
    qemu_device_QueryInterface,
    qemu_device_AddRef,
    qemu_device_Release,
    /* IQemuDXGIDeviceVtbl methods */
    qemu_device_wrap_implicit_surface,
};

static struct
{
    ID3D11DeviceContextVtbl vtbl1;
    void *CopySubresourceRegion1;
    void *UpdateSubresource1;
    void *DiscardResource;
    void *DiscardView;
    void *VSSetConstantBuffers1;
    void *HSSetConstantBuffers1;
    void *DSSetConstantBuffers1;
    void *GSSetConstantBuffers1;
    void *PSSetConstantBuffers1;
    void *CSSetConstantBuffers1;
    void *VSGetConstantBuffers1;
    void *HSGetConstantBuffers1;
    void *DSGetConstantBuffers1;
    void *GSGetConstantBuffers1;
    void *PSGetConstantBuffers1;
    void *CSGetConstantBuffers1;
    void *SwapDeviceContextState;
    void *ClearView;
    void *DiscardView1;
}
d3d11_immediate_context_vtbl =
{
    {
        /* IUnknown methods */
        d3d11_immediate_context_QueryInterface,
        d3d11_immediate_context_AddRef,
        d3d11_immediate_context_Release,
        /* ID3D11DeviceChild methods */
        d3d11_immediate_context_GetDevice,
        d3d11_immediate_context_GetPrivateData,
        d3d11_immediate_context_SetPrivateData,
        d3d11_immediate_context_SetPrivateDataInterface,
        /* ID3D11DeviceContext methods */
        d3d11_immediate_context_VSSetConstantBuffers,
        d3d11_immediate_context_PSSetShaderResources,
        d3d11_immediate_context_PSSetShader,
        d3d11_immediate_context_PSSetSamplers,
        d3d11_immediate_context_VSSetShader,
        d3d11_immediate_context_DrawIndexed,
        d3d11_immediate_context_Draw,
        d3d11_immediate_context_Map,
        d3d11_immediate_context_Unmap,
        d3d11_immediate_context_PSSetConstantBuffers,
        d3d11_immediate_context_IASetInputLayout,
        d3d11_immediate_context_IASetVertexBuffers,
        d3d11_immediate_context_IASetIndexBuffer,
        d3d11_immediate_context_DrawIndexedInstanced,
        d3d11_immediate_context_DrawInstanced,
        d3d11_immediate_context_GSSetConstantBuffers,
        d3d11_immediate_context_GSSetShader,
        d3d11_immediate_context_IASetPrimitiveTopology,
        d3d11_immediate_context_VSSetShaderResources,
        d3d11_immediate_context_VSSetSamplers,
        d3d11_immediate_context_Begin,
        d3d11_immediate_context_End,
        d3d11_immediate_context_GetData,
        d3d11_immediate_context_SetPredication,
        d3d11_immediate_context_GSSetShaderResources,
        d3d11_immediate_context_GSSetSamplers,
        d3d11_immediate_context_OMSetRenderTargets,
        d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews,
        d3d11_immediate_context_OMSetBlendState,
        d3d11_immediate_context_OMSetDepthStencilState,
        d3d11_immediate_context_SOSetTargets,
        d3d11_immediate_context_DrawAuto,
        d3d11_immediate_context_DrawIndexedInstancedIndirect,
        d3d11_immediate_context_DrawInstancedIndirect,
        d3d11_immediate_context_Dispatch,
        d3d11_immediate_context_DispatchIndirect,
        d3d11_immediate_context_RSSetState,
        d3d11_immediate_context_RSSetViewports,
        d3d11_immediate_context_RSSetScissorRects,
        d3d11_immediate_context_CopySubresourceRegion,
        d3d11_immediate_context_CopyResource,
        d3d11_immediate_context_UpdateSubresource,
        d3d11_immediate_context_CopyStructureCount,
        d3d11_immediate_context_ClearRenderTargetView,
        d3d11_immediate_context_ClearUnorderedAccessViewUint,
        d3d11_immediate_context_ClearUnorderedAccessViewFloat,
        d3d11_immediate_context_ClearDepthStencilView,
        d3d11_immediate_context_GenerateMips,
        d3d11_immediate_context_SetResourceMinLOD,
        d3d11_immediate_context_GetResourceMinLOD,
        d3d11_immediate_context_ResolveSubresource,
        d3d11_immediate_context_ExecuteCommandList,
        d3d11_immediate_context_HSSetShaderResources,
        d3d11_immediate_context_HSSetShader,
        d3d11_immediate_context_HSSetSamplers,
        d3d11_immediate_context_HSSetConstantBuffers,
        d3d11_immediate_context_DSSetShaderResources,
        d3d11_immediate_context_DSSetShader,
        d3d11_immediate_context_DSSetSamplers,
        d3d11_immediate_context_DSSetConstantBuffers,
        d3d11_immediate_context_CSSetShaderResources,
        d3d11_immediate_context_CSSetUnorderedAccessViews,
        d3d11_immediate_context_CSSetShader,
        d3d11_immediate_context_CSSetSamplers,
        d3d11_immediate_context_CSSetConstantBuffers,
        d3d11_immediate_context_VSGetConstantBuffers,
        d3d11_immediate_context_PSGetShaderResources,
        d3d11_immediate_context_PSGetShader,
        d3d11_immediate_context_PSGetSamplers,
        d3d11_immediate_context_VSGetShader,
        d3d11_immediate_context_PSGetConstantBuffers,
        d3d11_immediate_context_IAGetInputLayout,
        d3d11_immediate_context_IAGetVertexBuffers,
        d3d11_immediate_context_IAGetIndexBuffer,
        d3d11_immediate_context_GSGetConstantBuffers,
        d3d11_immediate_context_GSGetShader,
        d3d11_immediate_context_IAGetPrimitiveTopology,
        d3d11_immediate_context_VSGetShaderResources,
        d3d11_immediate_context_VSGetSamplers,
        d3d11_immediate_context_GetPredication,
        d3d11_immediate_context_GSGetShaderResources,
        d3d11_immediate_context_GSGetSamplers,
        d3d11_immediate_context_OMGetRenderTargets,
        d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews,
        d3d11_immediate_context_OMGetBlendState,
        d3d11_immediate_context_OMGetDepthStencilState,
        d3d11_immediate_context_SOGetTargets,
        d3d11_immediate_context_RSGetState,
        d3d11_immediate_context_RSGetViewports,
        d3d11_immediate_context_RSGetScissorRects,
        d3d11_immediate_context_HSGetShaderResources,
        d3d11_immediate_context_HSGetShader,
        d3d11_immediate_context_HSGetSamplers,
        d3d11_immediate_context_HSGetConstantBuffers,
        d3d11_immediate_context_DSGetShaderResources,
        d3d11_immediate_context_DSGetShader,
        d3d11_immediate_context_DSGetSamplers,
        d3d11_immediate_context_DSGetConstantBuffers,
        d3d11_immediate_context_CSGetShaderResources,
        d3d11_immediate_context_CSGetUnorderedAccessViews,
        d3d11_immediate_context_CSGetShader,
        d3d11_immediate_context_CSGetSamplers,
        d3d11_immediate_context_CSGetConstantBuffers,
        d3d11_immediate_context_ClearState,
        d3d11_immediate_context_Flush,
        d3d11_immediate_context_GetType,
        d3d11_immediate_context_GetContextFlags,
        d3d11_immediate_context_FinishCommandList,
    },
    /* ID3D11DeviceContext1 methods */
    d3d11_immediate_context_CopySubresourceRegion1,
    d3d11_immediate_context_UpdateSubresource1,
    d3d11_immediate_context_DiscardResource,
    d3d11_immediate_context_DiscardView,
    d3d11_immediate_context_VSSetConstantBuffers1,
    d3d11_immediate_context_HSSetConstantBuffers1,
    d3d11_immediate_context_DSSetConstantBuffers1,
    d3d11_immediate_context_GSSetConstantBuffers1,
    d3d11_immediate_context_PSSetConstantBuffers1,
    d3d11_immediate_context_CSSetConstantBuffers1,
    d3d11_immediate_context_VSGetConstantBuffers1,
    d3d11_immediate_context_HSGetConstantBuffers1,
    d3d11_immediate_context_DSGetConstantBuffers1,
    d3d11_immediate_context_GSGetConstantBuffers1,
    d3d11_immediate_context_PSGetConstantBuffers1,
    d3d11_immediate_context_CSGetConstantBuffers1,
    d3d11_immediate_context_SwapDeviceContextState,
    d3d11_immediate_context_ClearView,
    d3d11_immediate_context_DiscardView1,
};

static struct
{
    ID3D11DeviceVtbl vtbl1;
    /* ID3D11Device1 methods */
    void *GetImmediateContext1;
    void *CreateDeferredContext1;
    void *CreateBlendState1;
    void *CreateRasterizerState1;
    void *CreateDeviceContextState;
    void *OpenSharedResource1;
    void *OpenSharedResourceByName;
    /* ID3D11Device2 methods */
    void *GetImmediateContext2;
    void *CreateDeferredContext2;
    void *GetResourceTiling;
    void *CheckMultisampleQualityLevels1;
}
d3d11_device_vtbl =
{
    {
    /* IUnknown methods */
        d3d11_device_QueryInterface,
        d3d11_device_AddRef,
        d3d11_device_Release,
        /* ID3D11Device methods */
        d3d11_device_CreateBuffer,
        d3d11_device_CreateTexture1D,
        d3d11_device_CreateTexture2D,
        d3d11_device_CreateTexture3D,
        d3d11_device_CreateShaderResourceView,
        d3d11_device_CreateUnorderedAccessView,
        d3d11_device_CreateRenderTargetView,
        d3d11_device_CreateDepthStencilView,
        d3d11_device_CreateInputLayout,
        d3d11_device_CreateVertexShader,
        d3d11_device_CreateGeometryShader,
        d3d11_device_CreateGeometryShaderWithStreamOutput,
        d3d11_device_CreatePixelShader,
        d3d11_device_CreateHullShader,
        d3d11_device_CreateDomainShader,
        d3d11_device_CreateComputeShader,
        d3d11_device_CreateClassLinkage,
        d3d11_device_CreateBlendState,
        d3d11_device_CreateDepthStencilState,
        d3d11_device_CreateRasterizerState,
        d3d11_device_CreateSamplerState,
        d3d11_device_CreateQuery,
        d3d11_device_CreatePredicate,
        d3d11_device_CreateCounter,
        d3d11_device_CreateDeferredContext,
        d3d11_device_OpenSharedResource,
        d3d11_device_CheckFormatSupport,
        d3d11_device_CheckMultisampleQualityLevels,
        d3d11_device_CheckCounterInfo,
        d3d11_device_CheckCounter,
        d3d11_device_CheckFeatureSupport,
        d3d11_device_GetPrivateData,
        d3d11_device_SetPrivateData,
        d3d11_device_SetPrivateDataInterface,
        d3d11_device_GetFeatureLevel,
        d3d11_device_GetCreationFlags,
        d3d11_device_GetDeviceRemovedReason,
        d3d11_device_GetImmediateContext,
        d3d11_device_SetExceptionMode,
        d3d11_device_GetExceptionMode,
    },
    /* ID3D11Device1 methods */
    d3d11_device_GetImmediateContext1,
    d3d11_device_CreateDeferredContext1,
    d3d11_device_CreateBlendState1,
    d3d11_device_CreateRasterizerState1,
    d3d11_device_CreateDeviceContextState,
    d3d11_device_OpenSharedResource1,
    d3d11_device_OpenSharedResourceByName,
    /* ID3D11Device2 methods */
    d3d11_device_GetImmediateContext2,
    d3d11_device_CreateDeferredContext2,
    d3d11_device_GetResourceTiling,
    d3d11_device_CheckMultisampleQualityLevels1,
};

static struct ID3D10Device1Vtbl d3d10_device1_vtbl =
{
    /* IUnknown methods */
    d3d10_device_QueryInterface,
    d3d10_device_AddRef,
    d3d10_device_Release,
    /* ID3D10Device methods */
    d3d10_device_VSSetConstantBuffers,
    d3d10_device_PSSetShaderResources,
    d3d10_device_PSSetShader,
    d3d10_device_PSSetSamplers,
    d3d10_device_VSSetShader,
    d3d10_device_DrawIndexed,
    d3d10_device_Draw,
    d3d10_device_PSSetConstantBuffers,
    d3d10_device_IASetInputLayout,
    d3d10_device_IASetVertexBuffers,
    d3d10_device_IASetIndexBuffer,
    d3d10_device_DrawIndexedInstanced,
    d3d10_device_DrawInstanced,
    d3d10_device_GSSetConstantBuffers,
    d3d10_device_GSSetShader,
    d3d10_device_IASetPrimitiveTopology,
    d3d10_device_VSSetShaderResources,
    d3d10_device_VSSetSamplers,
    d3d10_device_SetPredication,
    d3d10_device_GSSetShaderResources,
    d3d10_device_GSSetSamplers,
    d3d10_device_OMSetRenderTargets,
    d3d10_device_OMSetBlendState,
    d3d10_device_OMSetDepthStencilState,
    d3d10_device_SOSetTargets,
    d3d10_device_DrawAuto,
    d3d10_device_RSSetState,
    d3d10_device_RSSetViewports,
    d3d10_device_RSSetScissorRects,
    d3d10_device_CopySubresourceRegion,
    d3d10_device_CopyResource,
    d3d10_device_UpdateSubresource,
    d3d10_device_ClearRenderTargetView,
    d3d10_device_ClearDepthStencilView,
    d3d10_device_GenerateMips,
    d3d10_device_ResolveSubresource,
    d3d10_device_VSGetConstantBuffers,
    d3d10_device_PSGetShaderResources,
    d3d10_device_PSGetShader,
    d3d10_device_PSGetSamplers,
    d3d10_device_VSGetShader,
    d3d10_device_PSGetConstantBuffers,
    d3d10_device_IAGetInputLayout,
    d3d10_device_IAGetVertexBuffers,
    d3d10_device_IAGetIndexBuffer,
    d3d10_device_GSGetConstantBuffers,
    d3d10_device_GSGetShader,
    d3d10_device_IAGetPrimitiveTopology,
    d3d10_device_VSGetShaderResources,
    d3d10_device_VSGetSamplers,
    d3d10_device_GetPredication,
    d3d10_device_GSGetShaderResources,
    d3d10_device_GSGetSamplers,
    d3d10_device_OMGetRenderTargets,
    d3d10_device_OMGetBlendState,
    d3d10_device_OMGetDepthStencilState,
    d3d10_device_SOGetTargets,
    d3d10_device_RSGetState,
    d3d10_device_RSGetViewports,
    d3d10_device_RSGetScissorRects,
    d3d10_device_GetDeviceRemovedReason,
    d3d10_device_SetExceptionMode,
    d3d10_device_GetExceptionMode,
    d3d10_device_GetPrivateData,
    d3d10_device_SetPrivateData,
    d3d10_device_SetPrivateDataInterface,
    d3d10_device_ClearState,
    d3d10_device_Flush,
    d3d10_device_CreateBuffer,
    d3d10_device_CreateTexture1D,
    d3d10_device_CreateTexture2D,
    d3d10_device_CreateTexture3D,
    d3d10_device_CreateShaderResourceView,
    d3d10_device_CreateRenderTargetView,
    d3d10_device_CreateDepthStencilView,
    d3d10_device_CreateInputLayout,
    d3d10_device_CreateVertexShader,
    d3d10_device_CreateGeometryShader,
    d3d10_device_CreateGeometryShaderWithStreamOutput,
    d3d10_device_CreatePixelShader,
    d3d10_device_CreateBlendState,
    d3d10_device_CreateDepthStencilState,
    d3d10_device_CreateRasterizerState,
    d3d10_device_CreateSamplerState,
    d3d10_device_CreateQuery,
    d3d10_device_CreatePredicate,
    d3d10_device_CreateCounter,
    d3d10_device_CheckFormatSupport,
    d3d10_device_CheckMultisampleQualityLevels,
    d3d10_device_CheckCounterInfo,
    d3d10_device_CheckCounter,
    d3d10_device_GetCreationFlags,
    d3d10_device_OpenSharedResource,
    d3d10_device_SetTextFilterSize,
    d3d10_device_GetTextFilterSize,
    d3d10_device_CreateShaderResourceView1,
    d3d10_device_CreateBlendState1,
    d3d10_device_GetFeatureLevel,
};

static struct IUnknownVtbl d3d_device_inner_unknown_vtbl =
{
    /* IUnknown methods */
    d3d_device_inner_QueryInterface,
    d3d_device_inner_AddRef,
    d3d_device_inner_Release,
};

static struct ID3D10MultithreadVtbl d3d10_multithread_vtbl =
{
    d3d10_multithread_QueryInterface,
    d3d10_multithread_AddRef,
    d3d10_multithread_Release,
    d3d10_multithread_Enter,
    d3d10_multithread_Leave,
    d3d10_multithread_SetMultithreadProtected,
    d3d10_multithread_GetMultithreadProtected,
};

void qemu_d3d11_device_guest_init(struct qemu_d3d11_device *device, void *outer_unknown)
{
    device->IUnknown_inner.lpVtbl = &d3d_device_inner_unknown_vtbl;
    device->ID3D11Device2_iface.lpVtbl = &d3d11_device_vtbl.vtbl1;
    device->ID3D10Device1_iface.lpVtbl = &d3d10_device1_vtbl;
    device->ID3D10Multithread_iface.lpVtbl = &d3d10_multithread_vtbl;
    device->IQemuD3D11Device_iface.lpVtbl = &qemu_device_vtbl;
    device->outer_unk = outer_unknown;
}

void qemu_d3d11_context_guest_init(struct qemu_d3d11_device_context *context)
{
    context->ID3D11DeviceContext1_iface.lpVtbl = &d3d11_immediate_context_vtbl.vtbl1;
    wined3d_private_store_init(&context->private_store);
}

void __fastcall d3d11_device_context_guest_destroy(struct qemu_d3d11_device_context *context)
{
    wined3d_private_store_cleanup(&context->private_store);
}

#else

void qemu_wrap_implicit_surface(struct qemu_syscall *call)
{
    struct qemu_wrap_implicit_surface *c = (struct qemu_wrap_implicit_surface *)call;
    struct qemu_d3d11_device *device;
    struct qemu_d3d11_texture *texture;
    ID3D11Texture2D *host;
    uint64_t dummy;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IUnknown_QueryInterface((IUnknown *)QEMU_G2H(c->host_dxgi), &IID_ID3D11Texture2D, (void **)&host);
    if (FAILED(c->super.iret))
        WINE_ERR("Could not get ID3D11Texture2D interface.\n");

    c->super.iret = qemu_d3d11_texture_create((ID3D11Resource *)host, device, &dummy, 2, &texture);
    c->texture = QEMU_H2G(texture);

    ID3D11Texture2D_Release(host);
}

static inline struct qemu_d3d11_device *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_device, priv_data_iface);
}

struct qemu_d3d11_device *device_from_host(ID3D11Device2 *host)
{
    IUnknown *priv;
    DWORD size = sizeof(priv);
    HRESULT hr;

    hr = ID3D11Device2_GetPrivateData(host, &IID_d3d11_priv_data, &size, &priv);
    if (FAILED(hr))
        WINE_ERR("Failed to get private data from host surface %p.\n", host);

    IUnknown_Release(priv);
    return impl_from_priv_data(priv);
}

#endif
