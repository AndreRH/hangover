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

struct qemu_d3d_execute_buffer_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_execute_buffer *impl_from_IDirect3DExecuteBuffer(IDirect3DExecuteBuffer *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_execute_buffer, IDirect3DExecuteBuffer_iface);
}

static HRESULT WINAPI d3d_execute_buffer_QueryInterface(IDirect3DExecuteBuffer *iface, REFIID iid, void **out)
{
    WINE_TRACE("iface %p, iid %s, out %p.\n", iface, wine_dbgstr_guid(iid), out);

    if (IsEqualGUID(&IID_IDirect3DExecuteBuffer, iid) || IsEqualGUID(&IID_IUnknown, iid))
    {
        IDirect3DExecuteBuffer_AddRef(iface);
        *out = iface;
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(iid));

    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d_execute_buffer_AddRef(IDirect3DExecuteBuffer *iface)
{
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    ULONG ref = InterlockedIncrement(&buffer->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", buffer, ref);

    return ref;
}

static ULONG WINAPI d3d_execute_buffer_Release(IDirect3DExecuteBuffer *iface)
{
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    ULONG ref = InterlockedDecrement(&buffer->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", buffer, ref);

    if (!ref)
    {
        WINE_FIXME("Implement destroy\n");
    }

    return ref;
}

#else

void qemu_d3d_execute_buffer_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_Release *c = (struct qemu_d3d_execute_buffer_Release *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_Release(buffer->host);
}

#endif

struct qemu_d3d_execute_buffer_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_Initialize(IDirect3DExecuteBuffer *iface, IDirect3DDevice *device, D3DEXECUTEBUFFERDESC *desc)
{
    struct qemu_d3d_execute_buffer_Initialize call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_INITIALIZE);
    call.iface = (ULONG_PTR)buffer;
    call.device = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_Initialize *c = (struct qemu_d3d_execute_buffer_Initialize *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_Initialize(buffer->host, QEMU_G2H(c->device), QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d_execute_buffer_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_Lock(IDirect3DExecuteBuffer *iface, D3DEXECUTEBUFFERDESC *desc)
{
    struct qemu_d3d_execute_buffer_Lock call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_LOCK);
    call.iface = (ULONG_PTR)buffer;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_Lock(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_Lock *c = (struct qemu_d3d_execute_buffer_Lock *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_Lock(buffer->host, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d_execute_buffer_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_Unlock(IDirect3DExecuteBuffer *iface)
{
    struct qemu_d3d_execute_buffer_Unlock call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_UNLOCK);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_Unlock(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_Unlock *c = (struct qemu_d3d_execute_buffer_Unlock *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_Unlock(buffer->host);
}

#endif

struct qemu_d3d_execute_buffer_SetExecuteData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_SetExecuteData(IDirect3DExecuteBuffer *iface, D3DEXECUTEDATA *data)
{
    struct qemu_d3d_execute_buffer_SetExecuteData call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_SETEXECUTEDATA);
    call.iface = (ULONG_PTR)buffer;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_SetExecuteData(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_SetExecuteData *c = (struct qemu_d3d_execute_buffer_SetExecuteData *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_SetExecuteData(buffer->host, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d_execute_buffer_GetExecuteData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_GetExecuteData(IDirect3DExecuteBuffer *iface, D3DEXECUTEDATA *data)
{
    struct qemu_d3d_execute_buffer_GetExecuteData call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_GETEXECUTEDATA);
    call.iface = (ULONG_PTR)buffer;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_GetExecuteData(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_GetExecuteData *c = (struct qemu_d3d_execute_buffer_GetExecuteData *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_GetExecuteData(buffer->host, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d_execute_buffer_Validate
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t offset;
    uint64_t callback;
    uint64_t context;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_Validate(IDirect3DExecuteBuffer *iface, DWORD *offset, LPD3DVALIDATECALLBACK callback, void *context, DWORD reserved)
{
    struct qemu_d3d_execute_buffer_Validate call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_VALIDATE);
    call.iface = (ULONG_PTR)buffer;
    call.offset = (ULONG_PTR)offset;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.reserved = reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_Validate(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_Validate *c = (struct qemu_d3d_execute_buffer_Validate *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_Validate(buffer->host, QEMU_G2H(c->offset), QEMU_G2H(c->callback), QEMU_G2H(c->context), c->reserved);
}

#endif

struct qemu_d3d_execute_buffer_Optimize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_execute_buffer_Optimize(IDirect3DExecuteBuffer *iface, DWORD reserved)
{
    struct qemu_d3d_execute_buffer_Optimize call;
    struct qemu_execute_buffer *buffer = impl_from_IDirect3DExecuteBuffer(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_EXECUTE_BUFFER_OPTIMIZE);
    call.iface = (ULONG_PTR)buffer;
    call.reserved = reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_execute_buffer_Optimize(struct qemu_syscall *call)
{
    struct qemu_d3d_execute_buffer_Optimize *c = (struct qemu_d3d_execute_buffer_Optimize *)call;
    struct qemu_execute_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DExecuteBuffer_Optimize(buffer->host, c->reserved);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DExecuteBufferVtbl d3d_execute_buffer_vtbl =
{
    d3d_execute_buffer_QueryInterface,
    d3d_execute_buffer_AddRef,
    d3d_execute_buffer_Release,
    d3d_execute_buffer_Initialize,
    d3d_execute_buffer_Lock,
    d3d_execute_buffer_Unlock,
    d3d_execute_buffer_SetExecuteData,
    d3d_execute_buffer_GetExecuteData,
    d3d_execute_buffer_Validate,
    d3d_execute_buffer_Optimize,
};

void d3d_execute_buffer_guest_init(struct qemu_execute_buffer *execute_buffer)
{
    execute_buffer->IDirect3DExecuteBuffer_iface.lpVtbl = &d3d_execute_buffer_vtbl;
    execute_buffer->ref = 1;
}

struct qemu_execute_buffer *unsafe_impl_from_IDirect3DExecuteBuffer(IDirect3DExecuteBuffer *iface)
{
    if (!iface)
        return NULL;
    if (iface->lpVtbl != &d3d_execute_buffer_vtbl)
        WINE_ERR("Invalid IDirect3DExecuteBuffer Vtbl!\n");

    return impl_from_IDirect3DExecuteBuffer(iface);
}

#endif
