/*
 * Copyright 2017 André Hentschel
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
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_d3d9_vertexbuffer_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_buffer_impl *impl_from_IDirect3DVertexBuffer9(IDirect3DVertexBuffer9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_buffer_impl, IDirect3DVertexBuffer9_iface);
}

static HRESULT WINAPI d3d9_vertexbuffer_QueryInterface(IDirect3DVertexBuffer9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)iface;
    call.riid = (ULONG_PTR)riid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_QueryInterface *c = (struct qemu_d3d9_vertexbuffer_QueryInterface *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_QueryInterface(buffer->hostvb, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_vertexbuffer_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_vertexbuffer_AddRef(IDirect3DVertexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_ADDREF);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_AddRef *c = (struct qemu_d3d9_vertexbuffer_AddRef *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_AddRef(buffer->hostvb);
}

#endif

struct qemu_d3d9_vertexbuffer_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

void __fastcall qemu_d3d9_buffer_destroyed(struct qemu_d3d9_buffer_impl *buffer)
{
    wined3d_private_store_cleanup(&buffer->private_store);
}

static ULONG WINAPI d3d9_vertexbuffer_Release(IDirect3DVertexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_RELEASE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_Release *c = (struct qemu_d3d9_vertexbuffer_Release *)call;
    struct qemu_d3d9_buffer_impl *buffer;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);
    device = buffer->device;

    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DVertexBuffer9_Release(buffer->hostvb);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_vertexbuffer_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_GetDevice(IDirect3DVertexBuffer9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_GETDEVICE);
    call.iface = (ULONG_PTR)iface;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_GetDevice *c = (struct qemu_d3d9_vertexbuffer_GetDevice *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_GetDevice(buffer->hostvb, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_SetPrivateData(IDirect3DVertexBuffer9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    return qemu_d3d9_set_private_data(&buffer->private_store, guid, data, data_size, flags);;
}

#else

void qemu_d3d9_vertexbuffer_SetPrivateData(struct qemu_syscall *call)
{
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_GetPrivateData(IDirect3DVertexBuffer9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    return qemu_d3d9_get_private_data(&buffer->private_store, guid, data, data_size);
}

#else

void qemu_d3d9_vertexbuffer_GetPrivateData(struct qemu_syscall *call)
{
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_FreePrivateData(IDirect3DVertexBuffer9 *iface, REFGUID guid)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    return qemu_d3d9_free_private_data(&buffer->private_store, guid);
}

#else

void qemu_d3d9_vertexbuffer_FreePrivateData(struct qemu_syscall *call)
{
}

#endif

struct qemu_d3d9_vertexbuffer_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_vertexbuffer_SetPriority(IDirect3DVertexBuffer9 *iface, DWORD priority)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_SETPRIORITY);
    call.iface = (ULONG_PTR)iface;
    call.priority = priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_SetPriority *c = (struct qemu_d3d9_vertexbuffer_SetPriority *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_SetPriority(buffer->hostvb, c->priority);
}

#endif

struct qemu_d3d9_vertexbuffer_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_vertexbuffer_GetPriority(IDirect3DVertexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_GETPRIORITY);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_GetPriority *c = (struct qemu_d3d9_vertexbuffer_GetPriority *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_GetPriority(buffer->hostvb);
}

#endif

struct qemu_d3d9_vertexbuffer_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_vertexbuffer_PreLoad(IDirect3DVertexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_PRELOAD);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_vertexbuffer_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_PreLoad *c = (struct qemu_d3d9_vertexbuffer_PreLoad *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    IDirect3DVertexBuffer9_PreLoad(buffer->hostvb);
}

#endif

struct qemu_d3d9_vertexbuffer_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DRESOURCETYPE WINAPI d3d9_vertexbuffer_GetType(IDirect3DVertexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_GETTYPE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_GetType *c = (struct qemu_d3d9_vertexbuffer_GetType *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_GetType(buffer->hostvb);
}

#endif

struct qemu_d3d9_vertexbuffer_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t offset;
    uint64_t size;
    uint64_t data;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_Lock(IDirect3DVertexBuffer9 *iface, UINT offset, UINT size, void **data, DWORD flags)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_Lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_LOCK);
    call.iface = (ULONG_PTR)iface;
    call.offset = offset;
    call.size = size;
    call.data = (ULONG_PTR)data;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_Lock(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_Lock *c = (struct qemu_d3d9_vertexbuffer_Lock *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_Lock(buffer->hostvb, c->offset, c->size, QEMU_G2H(c->data), c->flags);
}

#endif

struct qemu_d3d9_vertexbuffer_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_Unlock(IDirect3DVertexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_Unlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_UNLOCK);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_Unlock(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_Unlock *c = (struct qemu_d3d9_vertexbuffer_Unlock *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_Unlock(buffer->hostvb);
}

#endif

struct qemu_d3d9_vertexbuffer_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexbuffer_GetDesc(IDirect3DVertexBuffer9 *iface, D3DVERTEXBUFFER_DESC *desc)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DVertexBuffer9(iface);
    struct qemu_d3d9_vertexbuffer_GetDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXBUFFER_GETDESC);
    call.iface = (ULONG_PTR)iface;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexbuffer_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexbuffer_GetDesc *c = (struct qemu_d3d9_vertexbuffer_GetDesc *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexBuffer9_GetDesc(buffer->hostvb, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d9_indexbuffer_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_buffer_impl *impl_from_IDirect3DIndexBuffer9(IDirect3DIndexBuffer9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_buffer_impl, IDirect3DIndexBuffer9_iface);
}

static HRESULT WINAPI d3d9_indexbuffer_QueryInterface(IDirect3DIndexBuffer9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)iface;
    call.riid = (ULONG_PTR)riid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_QueryInterface *c = (struct qemu_d3d9_indexbuffer_QueryInterface *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_QueryInterface(buffer->hostib, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_indexbuffer_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_indexbuffer_AddRef(IDirect3DIndexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_ADDREF);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_AddRef *c = (struct qemu_d3d9_indexbuffer_AddRef *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_AddRef(buffer->hostib);
}

#endif

struct qemu_d3d9_indexbuffer_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_indexbuffer_Release(IDirect3DIndexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_RELEASE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_Release *c = (struct qemu_d3d9_indexbuffer_Release *)call;
    struct qemu_d3d9_buffer_impl *buffer;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);
    device = buffer->device;

    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DIndexBuffer9_Release(buffer->hostib);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_indexbuffer_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_GetDevice(IDirect3DIndexBuffer9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_GETDEVICE);
    call.iface = (ULONG_PTR)iface;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_GetDevice *c = (struct qemu_d3d9_indexbuffer_GetDevice *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_GetDevice(buffer->hostib, QEMU_G2H(c->device));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_SetPrivateData(IDirect3DIndexBuffer9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    return qemu_d3d9_set_private_data(&buffer->private_store, guid, data, data_size, flags);;
}

#else

void qemu_d3d9_indexbuffer_SetPrivateData(struct qemu_syscall *call)
{
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_GetPrivateData(IDirect3DIndexBuffer9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    return qemu_d3d9_get_private_data(&buffer->private_store, guid, data, data_size);
}

#else

void qemu_d3d9_indexbuffer_GetPrivateData(struct qemu_syscall *call)
{
}

#endif

struct qemu_d3d9_indexbuffer_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_FreePrivateData(IDirect3DIndexBuffer9 *iface, REFGUID guid)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    return qemu_d3d9_free_private_data(&buffer->private_store, guid);
}

#else

void qemu_d3d9_indexbuffer_FreePrivateData(struct qemu_syscall *call)
{
}

#endif

struct qemu_d3d9_indexbuffer_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_indexbuffer_SetPriority(IDirect3DIndexBuffer9 *iface, DWORD priority)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_SETPRIORITY);
    call.iface = (ULONG_PTR)iface;
    call.priority = priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_SetPriority *c = (struct qemu_d3d9_indexbuffer_SetPriority *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_SetPriority(buffer->hostib, c->priority);
}

#endif

struct qemu_d3d9_indexbuffer_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_indexbuffer_GetPriority(IDirect3DIndexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_GETPRIORITY);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_GetPriority *c = (struct qemu_d3d9_indexbuffer_GetPriority *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_GetPriority(buffer->hostib);
}

#endif

struct qemu_d3d9_indexbuffer_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_indexbuffer_PreLoad(IDirect3DIndexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_PRELOAD);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_indexbuffer_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_PreLoad *c = (struct qemu_d3d9_indexbuffer_PreLoad *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    IDirect3DIndexBuffer9_PreLoad(buffer->hostib);
}

#endif

struct qemu_d3d9_indexbuffer_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DRESOURCETYPE WINAPI d3d9_indexbuffer_GetType(IDirect3DIndexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_GETTYPE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_GetType *c = (struct qemu_d3d9_indexbuffer_GetType *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_GetType(buffer->hostib);
}

#endif

struct qemu_d3d9_indexbuffer_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t offset;
    uint64_t size;
    uint64_t data;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_Lock(IDirect3DIndexBuffer9 *iface, UINT offset, UINT size, void **data, DWORD flags)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_Lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_LOCK);
    call.iface = (ULONG_PTR)iface;
    call.offset = offset;
    call.size = size;
    call.data = (ULONG_PTR)data;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_Lock(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_Lock *c = (struct qemu_d3d9_indexbuffer_Lock *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_Lock(buffer->hostib, c->offset, c->size, QEMU_G2H(c->data), c->flags);
}

#endif

struct qemu_d3d9_indexbuffer_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_Unlock(IDirect3DIndexBuffer9 *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_Unlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_UNLOCK);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_Unlock(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_Unlock *c = (struct qemu_d3d9_indexbuffer_Unlock *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_Unlock(buffer->hostib);
}

#endif

struct qemu_d3d9_indexbuffer_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_indexbuffer_GetDesc(IDirect3DIndexBuffer9 *iface, D3DINDEXBUFFER_DESC *desc)
{
    struct qemu_d3d9_buffer_impl *buffer = impl_from_IDirect3DIndexBuffer9(iface);
    struct qemu_d3d9_indexbuffer_GetDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_INDEXBUFFER_GETDESC);
    call.iface = (ULONG_PTR)iface;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_indexbuffer_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_indexbuffer_GetDesc *c = (struct qemu_d3d9_indexbuffer_GetDesc *)call;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DIndexBuffer9_GetDesc(buffer->hostib, QEMU_G2H(c->desc));
}

#endif

#ifdef QEMU_DLL_GUEST

const IDirect3DVertexBuffer9Vtbl d3d9_vertexbuffer_vtbl =
{
    /* IUnknown */
    d3d9_vertexbuffer_QueryInterface,
    d3d9_vertexbuffer_AddRef,
    d3d9_vertexbuffer_Release,
    /* IDirect3DResource9 */
    d3d9_vertexbuffer_GetDevice,
    d3d9_vertexbuffer_SetPrivateData,
    d3d9_vertexbuffer_GetPrivateData,
    d3d9_vertexbuffer_FreePrivateData,
    d3d9_vertexbuffer_SetPriority,
    d3d9_vertexbuffer_GetPriority,
    d3d9_vertexbuffer_PreLoad,
    d3d9_vertexbuffer_GetType,
    /* IDirect3DVertexBuffer9 */
    d3d9_vertexbuffer_Lock,
    d3d9_vertexbuffer_Unlock,
    d3d9_vertexbuffer_GetDesc,
};

const IDirect3DIndexBuffer9Vtbl d3d9_indexbuffer_vtbl =
{
    /* IUnknown */
    d3d9_indexbuffer_QueryInterface,
    d3d9_indexbuffer_AddRef,
    d3d9_indexbuffer_Release,
    /* IDirect3DResource9 */
    d3d9_indexbuffer_GetDevice,
    d3d9_indexbuffer_SetPrivateData,
    d3d9_indexbuffer_GetPrivateData,
    d3d9_indexbuffer_FreePrivateData,
    d3d9_indexbuffer_SetPriority,
    d3d9_indexbuffer_GetPriority,
    d3d9_indexbuffer_PreLoad,
    d3d9_indexbuffer_GetType,
    /* IDirect3DIndexBuffer9 */
    d3d9_indexbuffer_Lock,
    d3d9_indexbuffer_Unlock,
    d3d9_indexbuffer_GetDesc,
};

#else

struct qemu_d3d9_buffer_impl *buffer_impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_buffer_impl, private_data);
}

static HRESULT WINAPI d3d9_buffer_priv_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d9_buffer_priv_AddRef(IUnknown *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = buffer_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedIncrement(&buffer->private_data_ref);

    WINE_TRACE("%p increasing refcount to %u.\n", buffer, refcount);
    return refcount;
}

static ULONG WINAPI d3d9_buffer_priv_Release(IUnknown *iface)
{
    struct qemu_d3d9_buffer_impl *buffer = buffer_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedDecrement(&buffer->private_data_ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", buffer, refcount);
    if (!refcount)
    {
        /* This means the private data has been released, which only happens
         * when the real interface has been destroyed. */
        qemu_ops->qemu_execute(QEMU_G2H(qemu_d3d9_buffer_destroyed), QEMU_H2G(buffer));
        HeapFree(GetProcessHeap(), 0, buffer);
    }

    return refcount;
}

static const struct IUnknownVtbl buffer_priv_vtbl =
{
    /* IUnknown */
    d3d9_buffer_priv_QueryInterface,
    d3d9_buffer_priv_AddRef,
    d3d9_buffer_priv_Release,
};

void d3d9_buffer_init(struct qemu_d3d9_buffer_impl *buffer, IDirect3DResource9 *host, struct qemu_d3d9_device_impl *device)
{
    DWORD i, level_count;
    IDirect3DSurface9 *surface;
    D3DRESOURCETYPE rtype;

    buffer->private_data.lpVtbl = &buffer_priv_vtbl;
    buffer->private_data_ref = 0;
    buffer->device = device;
    switch (IDirect3DResource9_GetType(host))
    {
        case D3DRTYPE_VERTEXBUFFER:
            buffer->hostvb = (IDirect3DVertexBuffer9 *)host;
            break;

        case D3DRTYPE_INDEXBUFFER:
            buffer->hostib = (IDirect3DIndexBuffer9 *)host;
            break;

        default:
            WINE_ERR("Unexpected resource type.\n");
    }

    IDirect3DResource9_SetPrivateData(host, &qemu_d3d9_buffer_guid, &buffer->private_data,
            sizeof(IUnknown *), D3DSPD_IUNKNOWN);
}

#endif
