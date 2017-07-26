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

struct qemu_d3d9_stateblock_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_stateblock_QueryInterface(IDirect3DStateBlock9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_stateblock_impl *stateblock = impl_from_IDirect3DStateBlock9(iface);
    struct qemu_d3d9_stateblock_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_STATEBLOCK_QUERYINTERFACE);
    call.iface = (uint64_t)stateblock;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_stateblock_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_stateblock_QueryInterface *c = (struct qemu_d3d9_stateblock_QueryInterface *)call;
    struct qemu_d3d9_stateblock_impl *stateblock;

    WINE_FIXME("Unverified!\n");
    stateblock = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DStateBlock9_QueryInterface(stateblock->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_stateblock_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_stateblock_AddRef(IDirect3DStateBlock9 *iface)
{
    struct qemu_d3d9_stateblock_impl *stateblock = impl_from_IDirect3DStateBlock9(iface);
    struct qemu_d3d9_stateblock_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_STATEBLOCK_ADDREF);
    call.iface = (uint64_t)stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_stateblock_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_stateblock_AddRef *c = (struct qemu_d3d9_stateblock_AddRef *)call;
    struct qemu_d3d9_stateblock_impl *stateblock;

    WINE_TRACE("\n");
    stateblock = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DStateBlock9_AddRef(stateblock->host);
}

#endif

struct qemu_d3d9_stateblock_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_stateblock_Release(IDirect3DStateBlock9 *iface)
{
    struct qemu_d3d9_stateblock_impl *stateblock = impl_from_IDirect3DStateBlock9(iface);
    struct qemu_d3d9_stateblock_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_STATEBLOCK_RELEASE);
    call.iface = (uint64_t)stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_stateblock_destroy(struct qemu_d3d9_stateblock_impl *stateblock)
{
    WINE_TRACE("Destroying stateblock wrapper %p\n", stateblock);

    if (stateblock->state.vdecl)
        d3d9_vdecl_internal_release(stateblock->state.vdecl);
    if (stateblock->state.vs)
        d3d9_shader_internal_release(stateblock->state.vs);
    if (stateblock->state.ps)
        d3d9_shader_internal_release(stateblock->state.ps);
    HeapFree(GetProcessHeap(), 0, stateblock);
}

void qemu_d3d9_stateblock_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_stateblock_Release *c = (struct qemu_d3d9_stateblock_Release *)call;
    struct qemu_d3d9_stateblock_impl *stateblock;

    WINE_TRACE("\n");
    stateblock = QEMU_G2H(c->iface);

    d3d9_device_wrapper_addref(stateblock->device);
    c->super.iret = IDirect3DStateBlock9_Release(stateblock->host);
    d3d9_device_wrapper_release(stateblock->device);

    if (!c->super.iret)
        qemu_d3d9_stateblock_destroy(stateblock);
}

#endif

struct qemu_d3d9_stateblock_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_stateblock_GetDevice(IDirect3DStateBlock9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_stateblock_impl *stateblock = impl_from_IDirect3DStateBlock9(iface);
    struct qemu_d3d9_stateblock_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_STATEBLOCK_GETDEVICE);
    call.iface = (uint64_t)stateblock;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_stateblock_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_stateblock_GetDevice *c = (struct qemu_d3d9_stateblock_GetDevice *)call;
    struct qemu_d3d9_stateblock_impl *stateblock;

    WINE_FIXME("Unverified!\n");
    stateblock = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DStateBlock9_GetDevice(stateblock->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_stateblock_Capture
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_stateblock_Capture(IDirect3DStateBlock9 *iface)
{
    struct qemu_d3d9_stateblock_impl *stateblock = impl_from_IDirect3DStateBlock9(iface);
    struct qemu_d3d9_stateblock_Capture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_STATEBLOCK_CAPTURE);
    call.iface = (uint64_t)stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_stateblock_Capture(struct qemu_syscall *call)
{
    struct qemu_d3d9_stateblock_Capture *c = (struct qemu_d3d9_stateblock_Capture *)call;
    struct qemu_d3d9_stateblock_impl *stateblock;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    stateblock = QEMU_G2H(c->iface);
    device = stateblock->device;

    c->super.iret = IDirect3DStateBlock9_Capture(stateblock->host);
    if (SUCCEEDED(c->super.iret))
    {
        if (stateblock->state.flags & QEMU_D3D_STATE_HAS_VDECL)
        {
            if (device->state->vdecl)
                d3d9_vdecl_internal_addref(device->state->vdecl);
            if (stateblock->state.vdecl)
                d3d9_vdecl_internal_release(stateblock->state.vdecl);
            stateblock->state.vdecl = device->state->vdecl;
        }
        if (stateblock->state.flags & QEMU_D3D_STATE_HAS_VS)
        {
            if (device->state->vs)
                d3d9_shader_internal_addref(device->state->vs);
            if (stateblock->state.vs)
                d3d9_shader_internal_release(stateblock->state.vs);
            stateblock->state.vs = device->state->vs;
        }
        if (stateblock->state.flags & QEMU_D3D_STATE_HAS_PS)
        {
            if (device->state->ps)
                d3d9_shader_internal_addref(device->state->ps);
            if (stateblock->state.ps)
                d3d9_shader_internal_release(stateblock->state.ps);
            stateblock->state.ps = device->state->ps;
        }
    }
}

#endif

struct qemu_d3d9_stateblock_Apply
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_stateblock_Apply(IDirect3DStateBlock9 *iface)
{
    struct qemu_d3d9_stateblock_impl *stateblock = impl_from_IDirect3DStateBlock9(iface);
    struct qemu_d3d9_stateblock_Apply call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_STATEBLOCK_APPLY);
    call.iface = (uint64_t)stateblock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_stateblock_Apply(struct qemu_syscall *call)
{
    struct qemu_d3d9_stateblock_Apply *c = (struct qemu_d3d9_stateblock_Apply *)call;
    struct qemu_d3d9_stateblock_impl *stateblock;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    stateblock = QEMU_G2H(c->iface);
    device = stateblock->device;

    c->super.iret = IDirect3DStateBlock9_Apply(stateblock->host);

    if (SUCCEEDED(c->super.iret))
    {
        /* Do not apply a NULL vertex declaration from the stateblock. */
        if (stateblock->state.flags & QEMU_D3D_STATE_HAS_VDECL && stateblock->state.vdecl)
        {
            if (stateblock->state.vdecl)
                d3d9_vdecl_internal_addref(stateblock->state.vdecl);
            if (device->state->vdecl)
                d3d9_vdecl_internal_release(device->state->vdecl);
            device->state->vdecl = stateblock->state.vdecl;
        }
        if (stateblock->state.flags & QEMU_D3D_STATE_HAS_VS)
        {
            if (stateblock->state.vs)
                d3d9_shader_internal_addref(stateblock->state.vs);
            if (device->state->vs)
                d3d9_shader_internal_release(device->state->vs);
            device->state->vs = stateblock->state.vs;
        }
        if (stateblock->state.flags & QEMU_D3D_STATE_HAS_PS)
        {
            if (stateblock->state.ps)
                d3d9_shader_internal_addref(stateblock->state.ps);
            if (device->state->ps)
                d3d9_shader_internal_release(device->state->ps);
            device->state->ps = stateblock->state.ps;
        }
    }
}

#endif

#ifdef QEMU_DLL_GUEST

const struct IDirect3DStateBlock9Vtbl d3d9_stateblock_vtbl =
{
    /* IUnknown */
    d3d9_stateblock_QueryInterface,
    d3d9_stateblock_AddRef,
    d3d9_stateblock_Release,
    /* IDirect3DStateBlock9 */
    d3d9_stateblock_GetDevice,
    d3d9_stateblock_Capture,
    d3d9_stateblock_Apply,
};

#else

#endif
