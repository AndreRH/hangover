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
#include <ddraw.h>
#include <d3d.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_d3d_vertex_buffer7_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_vertex_buffer *impl_from_IDirect3DVertexBuffer7(IDirect3DVertexBuffer7 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_vertex_buffer, IDirect3DVertexBuffer7_iface);
}

static HRESULT WINAPI d3d_vertex_buffer7_QueryInterface(IDirect3DVertexBuffer7 *iface, REFIID riid, void  **obj)
{
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), obj);

    *obj = NULL;

    if (IsEqualGUID(&IID_IUnknown, riid))
    {
        IDirect3DVertexBuffer7_AddRef(iface);
        *obj = iface;
        return S_OK;
    }
    if (IsEqualGUID(&IID_IDirect3DVertexBuffer7, riid) && buffer->version == 7)
    {
        IDirect3DVertexBuffer7_AddRef(iface);
        *obj = iface;
        return S_OK;
    }
    if (IsEqualGUID(&IID_IDirect3DVertexBuffer, riid) && buffer->version == 3)
    {
        IDirect3DVertexBuffer7_AddRef(iface);
        *obj = iface;
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d_vertex_buffer7_AddRef(IDirect3DVertexBuffer7 *iface)
{
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    ULONG ref = InterlockedIncrement(&buffer->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", buffer, ref);

    return ref;
}

static ULONG WINAPI d3d_vertex_buffer7_Release(IDirect3DVertexBuffer7 *iface)
{
    struct qemu_d3d_vertex_buffer7_Release call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    ULONG ref = InterlockedDecrement(&buffer->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", buffer, ref);

    if (!ref)
    {
        if (buffer->version == 7)
            IDirectDraw7_Release(&buffer->ddraw->IDirectDraw7_iface);

        call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_RELEASE);
        call.iface = (ULONG_PTR)buffer;
        qemu_syscall(&call.super);
    }

    return ref;
}

#else

void qemu_d3d_vertex_buffer7_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_Release *c = (struct qemu_d3d_vertex_buffer7_Release *)call;
    struct qemu_vertex_buffer *buffer;
    ULONG ref;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    ref = IDirect3DVertexBuffer7_Release(buffer->host);
    if (ref)
        WINE_ERR("Unexpected host vertex buffer ref %u.\n", ref);

    HeapFree(GetProcessHeap(), 0, buffer);
    c->super.iret = ref;
}

#endif

struct qemu_d3d_vertex_buffer7_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_vertex_buffer7_Lock(IDirect3DVertexBuffer7 *iface, DWORD flags, void **data, DWORD *data_size)
{
    struct qemu_d3d_vertex_buffer7_Lock call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_LOCK);
    call.iface = (ULONG_PTR)buffer;
    call.flags = flags;
    call.data_size = (ULONG_PTR)data_size;

    qemu_syscall(&call.super);
    *data = (void *)(ULONG_PTR)call.data;

    return call.super.iret;
}

#else

void qemu_d3d_vertex_buffer7_Lock(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_Lock *c = (struct qemu_d3d_vertex_buffer7_Lock *)call;
    struct qemu_vertex_buffer *buffer;
    void *data;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer7_Lock(buffer->host, c->flags, &data, QEMU_G2H(c->data_size));
    c->data = QEMU_H2G(data);
}

#endif

struct qemu_d3d_vertex_buffer7_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_vertex_buffer7_Unlock(IDirect3DVertexBuffer7 *iface)
{
    struct qemu_d3d_vertex_buffer7_Unlock call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_UNLOCK);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_vertex_buffer7_Unlock(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_Unlock *c = (struct qemu_d3d_vertex_buffer7_Unlock *)call;
    struct qemu_vertex_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer7_Unlock(buffer->host);
}

#endif

struct qemu_d3d_vertex_buffer7_ProcessVertices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vertex_op;
    uint64_t dst_idx;
    uint64_t count;
    uint64_t src_buffer;
    uint64_t src_idx;
    uint64_t device;
    uint64_t flags;
    uint64_t version;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_vertex_buffer7_ProcessVertices(IDirect3DVertexBuffer7 *iface, DWORD vertex_op, DWORD dst_idx,
        DWORD count, IDirect3DVertexBuffer7 *src_buffer, DWORD src_idx, IDirect3DDevice7 *device, DWORD flags)
{
    struct qemu_d3d_vertex_buffer7_ProcessVertices call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    struct qemu_vertex_buffer *src = unsafe_impl_from_IDirect3DVertexBuffer7(src_buffer);
    struct qemu_device *device_impl;

    if (buffer->version == 7)
        device_impl = unsafe_impl_from_IDirect3DDevice7(device);
    else
        device_impl = unsafe_impl_from_IDirect3DDevice3((IDirect3DDevice3 *)device);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_PROCESSVERTICES);
    call.iface = (ULONG_PTR)buffer;
    call.vertex_op = vertex_op;
    call.dst_idx = dst_idx;
    call.count = count;
    call.src_buffer = (ULONG_PTR)src;
    call.src_idx = src_idx;
    call.device = (ULONG_PTR)device_impl;
    call.flags = flags;
    call.version = buffer->version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_vertex_buffer7_ProcessVertices(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_ProcessVertices *c = (struct qemu_d3d_vertex_buffer7_ProcessVertices *)call;
    struct qemu_vertex_buffer *buffer;
    struct qemu_vertex_buffer *src;
    struct qemu_device *device;
    void *device_iface;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_buffer);
    device = QEMU_G2H(c->device);

    if (!device)
        device_iface = NULL;
    else if (c->version == 7)
        device_iface = device->host7;
    else
        device_iface = device->host3;

    c->super.iret = IDirect3DVertexBuffer7_ProcessVertices(buffer->host, c->vertex_op, c->dst_idx, c->count,
            src ? src->host : NULL, c->src_idx, device_iface, c->flags);
}

#endif

struct qemu_d3d_vertex_buffer7_GetVertexBufferDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_vertex_buffer7_GetVertexBufferDesc(IDirect3DVertexBuffer7 *iface, D3DVERTEXBUFFERDESC *desc)
{
    struct qemu_d3d_vertex_buffer7_GetVertexBufferDesc call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_GETVERTEXBUFFERDESC);
    call.iface = (ULONG_PTR)buffer;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_vertex_buffer7_GetVertexBufferDesc(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_GetVertexBufferDesc *c = (struct qemu_d3d_vertex_buffer7_GetVertexBufferDesc *)call;
    struct qemu_vertex_buffer *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer7_GetVertexBufferDesc(buffer->host, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d_vertex_buffer7_Optimize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_vertex_buffer7_Optimize(IDirect3DVertexBuffer7 *iface, IDirect3DDevice7 *device, DWORD flags)
{
    struct qemu_d3d_vertex_buffer7_Optimize call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_OPTIMIZE);
    call.iface = (ULONG_PTR)buffer;
    call.device = (ULONG_PTR)device;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_vertex_buffer7_Optimize(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_Optimize *c = (struct qemu_d3d_vertex_buffer7_Optimize *)call;
    struct qemu_vertex_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer7_Optimize(buffer->host, QEMU_G2H(c->device), c->flags);
}

#endif

struct qemu_d3d_vertex_buffer7_ProcessVerticesStrided
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t vertex_op;
    uint64_t dst_idx;
    uint64_t count;
    uint64_t data;
    uint64_t fvf;
    uint64_t device;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_vertex_buffer7_ProcessVerticesStrided(IDirect3DVertexBuffer7 *iface, DWORD vertex_op, DWORD dst_idx, DWORD count, D3DDRAWPRIMITIVESTRIDEDDATA *data, DWORD fvf, IDirect3DDevice7 *device, DWORD flags)
{
    struct qemu_d3d_vertex_buffer7_ProcessVerticesStrided call;
    struct qemu_vertex_buffer *buffer = impl_from_IDirect3DVertexBuffer7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VERTEX_BUFFER7_PROCESSVERTICESSTRIDED);
    call.iface = (ULONG_PTR)buffer;
    call.vertex_op = vertex_op;
    call.dst_idx = dst_idx;
    call.count = count;
    call.data = (ULONG_PTR)data;
    call.fvf = fvf;
    call.device = (ULONG_PTR)device;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_vertex_buffer7_ProcessVerticesStrided(struct qemu_syscall *call)
{
    struct qemu_d3d_vertex_buffer7_ProcessVerticesStrided *c = (struct qemu_d3d_vertex_buffer7_ProcessVerticesStrided *)call;
    struct qemu_vertex_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer7_ProcessVerticesStrided(buffer->host, c->vertex_op, c->dst_idx, c->count, QEMU_G2H(c->data), c->fvf, QEMU_G2H(c->device), c->flags);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DVertexBuffer7Vtbl d3d_vertex_buffer7_vtbl =
{
    d3d_vertex_buffer7_QueryInterface,
    d3d_vertex_buffer7_AddRef,
    d3d_vertex_buffer7_Release,
    d3d_vertex_buffer7_Lock,
    d3d_vertex_buffer7_Unlock,
    d3d_vertex_buffer7_ProcessVertices,
    d3d_vertex_buffer7_GetVertexBufferDesc,
    d3d_vertex_buffer7_Optimize,
    d3d_vertex_buffer7_ProcessVerticesStrided,
};

struct qemu_vertex_buffer *unsafe_impl_from_IDirect3DVertexBuffer7(IDirect3DVertexBuffer7 *iface)
{
    if (!iface)
        return NULL;
    if (iface->lpVtbl != &d3d_vertex_buffer7_vtbl)
        WINE_ERR("Incorrect vertex buffer vtable!\n");

    return impl_from_IDirect3DVertexBuffer7(iface);
}

void ddraw_vertex_buffer_guest_init(struct qemu_vertex_buffer *buffer, struct qemu_ddraw *ddraw, UINT version)
{
    buffer->IDirect3DVertexBuffer7_iface.lpVtbl = &d3d_vertex_buffer7_vtbl;
    buffer->ref = 1;
    buffer->ddraw = ddraw;
    buffer->version = version;
    if (buffer->version == 7)
        IDirectDraw7_AddRef(&ddraw->IDirectDraw7_iface);
}

#endif
