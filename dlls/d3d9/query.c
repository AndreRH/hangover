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


struct qemu_d3d9_query_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_query_QueryInterface(IDirect3DQuery9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_QUERYINTERFACE);
    call.iface = (uint64_t)query;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_QueryInterface *c = (struct qemu_d3d9_query_QueryInterface *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_QueryInterface(query->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_query_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_query_AddRef(IDirect3DQuery9 *iface)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_ADDREF);
    call.iface = (uint64_t)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_AddRef *c = (struct qemu_d3d9_query_AddRef *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_AddRef(query->host);
}

#endif

struct qemu_d3d9_query_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_query_Release(IDirect3DQuery9 *iface)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_RELEASE);
    call.iface = (uint64_t)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_Release *c = (struct qemu_d3d9_query_Release *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    d3d9_device_wrapper_addref(query->device);
    c->super.iret = IDirect3DQuery9_Release(query->host);
    d3d9_device_wrapper_release(query->device);

    if (!c->super.iret)
        HeapFree(GetProcessHeap(), 0, query);
}

#endif

struct qemu_d3d9_query_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_query_GetDevice(IDirect3DQuery9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_GETDEVICE);
    call.iface = (uint64_t)query;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_GetDevice *c = (struct qemu_d3d9_query_GetDevice *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_GetDevice(query->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_query_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DQUERYTYPE WINAPI d3d9_query_GetType(IDirect3DQuery9 *iface)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_GETTYPE);
    call.iface = (uint64_t)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_GetType *c = (struct qemu_d3d9_query_GetType *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_GetType(query->host);
}

#endif

struct qemu_d3d9_query_GetDataSize
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_query_GetDataSize(IDirect3DQuery9 *iface)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_GetDataSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_GETDATASIZE);
    call.iface = (uint64_t)query;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_GetDataSize(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_GetDataSize *c = (struct qemu_d3d9_query_GetDataSize *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_GetDataSize(query->host);
}

#endif

struct qemu_d3d9_query_Issue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_query_Issue(IDirect3DQuery9 *iface, DWORD flags)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_Issue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_ISSUE);
    call.iface = (uint64_t)query;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_Issue(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_Issue *c = (struct qemu_d3d9_query_Issue *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_Issue(query->host, c->flags);
}

#endif

struct qemu_d3d9_query_GetData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_query_GetData(IDirect3DQuery9 *iface, void *data, DWORD size, DWORD flags)
{
    struct qemu_d3d9_query_impl *query = impl_from_IDirect3DQuery9(iface);
    struct qemu_d3d9_query_GetData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERY_GETDATA);
    call.iface = (uint64_t)query;
    call.data = (uint64_t)data;
    call.size = (uint64_t)size;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_query_GetData(struct qemu_syscall *call)
{
    struct qemu_d3d9_query_GetData *c = (struct qemu_d3d9_query_GetData *)call;
    struct qemu_d3d9_query_impl *query;

    WINE_FIXME("Unverified!\n");
    query = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DQuery9_GetData(query->host, QEMU_G2H(c->data), c->size, c->flags);
}

#endif

#ifdef QEMU_DLL_GUEST

const struct IDirect3DQuery9Vtbl d3d9_query_vtbl =
{
    d3d9_query_QueryInterface,
    d3d9_query_AddRef,
    d3d9_query_Release,
    d3d9_query_GetDevice,
    d3d9_query_GetType,
    d3d9_query_GetDataSize,
    d3d9_query_Issue,
    d3d9_query_GetData,
};

#else

#endif
