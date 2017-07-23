/*
 * Copyright 2017 André Hentschel
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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_d3d9_vertex_declaration_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertex_declaration_QueryInterface(IDirect3DVertexDeclaration9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_vertex_declaration_impl *decl = impl_from_IDirect3DVertexDeclaration9(iface);
    struct qemu_d3d9_vertex_declaration_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEX_DECLARATION_QUERYINTERFACE);
    call.iface = (uint64_t)decl;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertex_declaration_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertex_declaration_QueryInterface *c = (struct qemu_d3d9_vertex_declaration_QueryInterface *)call;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    WINE_FIXME("Unverified!\n");
    decl = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexDeclaration9_QueryInterface(decl->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_vertex_declaration_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_vertex_declaration_AddRef(IDirect3DVertexDeclaration9 *iface)
{
    struct qemu_d3d9_vertex_declaration_impl *decl = impl_from_IDirect3DVertexDeclaration9(iface);
    struct qemu_d3d9_vertex_declaration_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEX_DECLARATION_ADDREF);
    call.iface = (uint64_t)decl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG d3d9_vdecl_internal_addref(struct qemu_d3d9_vertex_declaration_impl *decl)
{
    ULONG ref = InterlockedIncrement(&decl->internal_ref);
    WINE_TRACE("%p increasing internal refcount to %u.\n", decl, ref);
    return ref;
}

void qemu_d3d9_vertex_declaration_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertex_declaration_AddRef *c = (struct qemu_d3d9_vertex_declaration_AddRef *)call;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    WINE_TRACE("\n");
    decl = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexDeclaration9_AddRef(decl->host);

    if (c->super.iret == 1)
        d3d9_vdecl_internal_addref(decl);
}

#endif

struct qemu_d3d9_vertex_declaration_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_vertex_declaration_Release(IDirect3DVertexDeclaration9 *iface)
{
    struct qemu_d3d9_vertex_declaration_impl *decl = impl_from_IDirect3DVertexDeclaration9(iface);
    struct qemu_d3d9_vertex_declaration_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEX_DECLARATION_RELEASE);
    call.iface = (uint64_t)decl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else


ULONG d3d9_vdecl_internal_release(struct qemu_d3d9_vertex_declaration_impl *decl)
{
    ULONG ref = InterlockedDecrement(&decl->internal_ref);
    WINE_TRACE("%p decreasing internal refcount to %u.\n", decl, ref);

    if (!ref)
        HeapFree(GetProcessHeap(), 0, decl);

    return ref;
}


void qemu_d3d9_vertex_declaration_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertex_declaration_Release *c = (struct qemu_d3d9_vertex_declaration_Release *)call;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    WINE_TRACE("\n");
    decl = QEMU_G2H(c->iface);

    d3d9_device_wrapper_addref(decl->device);
    c->super.iret = IDirect3DVertexDeclaration9_Release(decl->host);
    d3d9_device_wrapper_release(decl->device);

    if (!c->super.iret)
        d3d9_vdecl_internal_release(decl);
}

#endif

struct qemu_d3d9_vertex_declaration_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertex_declaration_GetDevice(IDirect3DVertexDeclaration9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_vertex_declaration_impl *decl = impl_from_IDirect3DVertexDeclaration9(iface);
    struct qemu_d3d9_vertex_declaration_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEX_DECLARATION_GETDEVICE);
    call.iface = (uint64_t)decl;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertex_declaration_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertex_declaration_GetDevice *c = (struct qemu_d3d9_vertex_declaration_GetDevice *)call;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    WINE_FIXME("Unverified!\n");
    decl = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexDeclaration9_GetDevice(decl->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_vertex_declaration_GetDeclaration
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t elements;
    uint64_t element_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertex_declaration_GetDeclaration(IDirect3DVertexDeclaration9 *iface, D3DVERTEXELEMENT9 *elements, UINT *element_count)
{
    struct qemu_d3d9_vertex_declaration_impl *decl = impl_from_IDirect3DVertexDeclaration9(iface);
    struct qemu_d3d9_vertex_declaration_GetDeclaration call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEX_DECLARATION_GETDECLARATION);
    call.iface = (uint64_t)decl;
    call.elements = (uint64_t)elements;
    call.element_count = (uint64_t)element_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertex_declaration_GetDeclaration(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertex_declaration_GetDeclaration *c = (struct qemu_d3d9_vertex_declaration_GetDeclaration *)call;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    WINE_TRACE("\n");
    decl = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexDeclaration9_GetDeclaration(decl->host, QEMU_G2H(c->elements), QEMU_G2H(c->element_count));
}

#endif

#ifdef QEMU_DLL_GUEST

const struct IDirect3DVertexDeclaration9Vtbl d3d9_vertex_declaration_vtbl =
{
    /* IUnknown */
    d3d9_vertex_declaration_QueryInterface,
    d3d9_vertex_declaration_AddRef,
    d3d9_vertex_declaration_Release,
    /* IDirect3DVertexDeclaration9 */
    d3d9_vertex_declaration_GetDevice,
    d3d9_vertex_declaration_GetDeclaration,
};

#else


#endif
