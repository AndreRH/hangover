/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

/* The basic idea behind declaring these structures outside dlls/d3d9/ is that
 * other DLLs like d3dx9 will need them for functions that take an IDirect3D9*
 * interface somewhere. They'll need to wrap the d3d9 stuff in addition to
 * their own interfaces. */

#ifndef QEMU_D3D9_WRAPPER_H
#define QEMU_D3D9_WRAPPER_H

#include "private_data.h"

/* These structures are accessed by both guest and host, including the guest
 * application code. This may need extra care for 32<->64 mapping because
 * we can't just make everything an uint64_t. */

struct qemu_d3d9_impl
{
    IDirect3D9Ex IDirect3D9Ex_iface;
    IDirect3D9Ex *host;
};

#define QEMU_D3D_STATE_HAS_VS       0x1
#define QEMU_D3D_STATE_HAS_PS       0x2
#define QEMU_D3D_STATE_HAS_VDECL    0x4
#define QEMU_D3D_STATE_RECORDED     0x8

/* Shaders and vertex declarations do not have the private data API, so we
 * have to keep track of them ourselves in the device and stateblocks and
 * replicate the hidden refcounting. */
struct qemu_d3d9_state
{
    struct qemu_d3d9_shader_impl *vs, *ps;
    struct qemu_d3d9_vertex_declaration_impl *vdecl;
    DWORD flags;
};

struct qemu_d3d9_device_impl
{
    IDirect3DDevice9Ex IDirect3DDevice9Ex_iface;
    IDirect3DDevice9Ex *host;

    struct qemu_d3d9_impl *d3d9;
    struct qemu_d3d9_state dev_state;
    struct qemu_d3d9_state *state;
    struct qemu_d3d9_stateblock_impl *record_stateblock;
    struct qemu_d3d9_vertex_declaration_impl **fvf_decls;
    unsigned int fvf_decl_count, fvf_decl_size;
};

struct qemu_d3d9_subresource_impl
{
    union
    {
        IDirect3DSurface9 IDirect3DSurface9_iface;
        IDirect3DVolume9 IDirect3DVolume9_iface;
    };
    struct wined3d_private_store private_store;
    BOOL initialized;

    union
    {
        IDirect3DSurface9 *host;
        IDirect3DVolume9 *host_volume;
    };
    struct qemu_d3d9_device_impl *device;
};

static inline struct qemu_d3d9_subresource_impl *unsafe_impl_from_IDirect3DSurface9(IDirect3DSurface9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_surface_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_subresource_impl, IDirect3DSurface9_iface);
}

struct qemu_d3d9_swapchain_impl
{
    IDirect3DSwapChain9Ex IDirect3DSwapChain9Ex_iface;
    IDirect3DSwapChain9Ex *host;

    IUnknown private_data;
    ULONG private_data_ref; /* NOT the externally visible ref! */
    struct qemu_d3d9_device_impl *device;
    DWORD back_buffer_count;
    struct qemu_d3d9_subresource_impl backbuffers[1];
};

static inline struct qemu_d3d9_swapchain_impl *unsafe_impl_from_IDirect3DSwapChain9Ex(IDirect3DSwapChain9Ex *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_swapchain_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_swapchain_impl, IDirect3DSwapChain9Ex_iface);
}

struct qemu_d3d9_texture_impl
{
    IDirect3DBaseTexture9 IDirect3DBaseTexture9_iface;
    struct wined3d_private_store private_store;

    IDirect3DBaseTexture9 *host;

    IUnknown private_data;
    ULONG private_data_ref; /* NOT the externally visible ref! */
    struct qemu_d3d9_device_impl *device;

    UINT sub_resource_count;
    struct qemu_d3d9_subresource_impl subs[1];
};

static inline struct qemu_d3d9_texture_impl *unsafe_impl_from_IDirect3DBaseTexture9(IDirect3DBaseTexture9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_texture_2d_vtbl || iface->lpVtbl == &d3d9_texture_cube_vtbl
     *         || iface->lpVtbl == &d3d9_texture_3d_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_texture_impl, IDirect3DBaseTexture9_iface);
}

struct qemu_d3d9_vertex_declaration_impl
{
    IDirect3DVertexDeclaration9 IDirect3DVertexDeclaration9_iface;
    IDirect3DVertexDeclaration9 *host;

    struct qemu_d3d9_device_impl *device;
    ULONG internal_ref;
    DWORD fvf;
};

static inline struct qemu_d3d9_vertex_declaration_impl *unsafe_impl_from_IDirect3DVertexDeclaration9(IDirect3DVertexDeclaration9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_vertex_declaration_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_vertex_declaration_impl, IDirect3DVertexDeclaration9_iface);
}

struct qemu_d3d9_buffer_impl
{
    union
    {
        IDirect3DVertexBuffer9 IDirect3DVertexBuffer9_iface;
        IDirect3DIndexBuffer9 IDirect3DIndexBuffer9_iface;
    };
    struct wined3d_private_store private_store;

    union
    {
        IDirect3DVertexBuffer9 *hostvb;
        IDirect3DIndexBuffer9 *hostib;
    };

    IUnknown private_data;
    ULONG private_data_ref; /* NOT the externally visible ref! */
    struct qemu_d3d9_device_impl *device;
};

static inline struct qemu_d3d9_buffer_impl *unsafe_impl_from_IDirect3DVertexBuffer9(IDirect3DVertexBuffer9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_vertexbuffer_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_buffer_impl, IDirect3DVertexBuffer9_iface);
}

static inline struct qemu_d3d9_buffer_impl *unsafe_impl_from_IDirect3DIndexBuffer9(IDirect3DIndexBuffer9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_indexbuffer_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_buffer_impl, IDirect3DIndexBuffer9_iface);
}

struct qemu_d3d9_query_impl
{
    IDirect3DQuery9 IDirect3DQuery9_iface;
    IDirect3DQuery9 *host;

    struct qemu_d3d9_device_impl *device;
};

static inline struct qemu_d3d9_query_impl *impl_from_IDirect3DQuery9(IDirect3DQuery9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_query_impl, IDirect3DQuery9_iface);
}

struct qemu_d3d9_shader_impl
{
    union
    {
        IDirect3DVertexShader9 IDirect3DVertexShader9_iface;
        IDirect3DPixelShader9 IDirect3DPixelShader9_iface;
    };
    union
    {
        IDirect3DVertexShader9 *hostvs;
        IDirect3DPixelShader9 *hostps;
    };

    struct qemu_d3d9_device_impl *device;
    ULONG internal_ref;
};

static inline struct qemu_d3d9_shader_impl *unsafe_impl_from_IDirect3DVertexShader9(IDirect3DVertexShader9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_vertexshader_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_shader_impl, IDirect3DVertexShader9_iface);
}

static inline struct qemu_d3d9_shader_impl *unsafe_impl_from_IDirect3DPixelShader9(IDirect3DPixelShader9 *iface)
{
    if (!iface)
        return NULL;
    /* FIXME: assert(iface->lpVtbl == &d3d9_pixelshader_vtbl); */
    return CONTAINING_RECORD(iface, struct qemu_d3d9_shader_impl, IDirect3DPixelShader9_iface);
}

struct qemu_d3d9_stateblock_impl
{
    IDirect3DStateBlock9 IDirect3DStateBlock9_iface;
    IDirect3DStateBlock9 *host;

    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_state state;
};

static inline struct qemu_d3d9_stateblock_impl *impl_from_IDirect3DStateBlock9(IDirect3DStateBlock9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_stateblock_impl, IDirect3DStateBlock9_iface);
}

#endif
