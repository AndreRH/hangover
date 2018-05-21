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

#include <windows.h>
#include <stdio.h>
#include <d3d10_1.h>
#include <dxgi1_2.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dxgi.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_CreateDXGIFactory2
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t iid;
    uint64_t factory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CreateDXGIFactory2(UINT flags, REFIID iid, void **factory)
{
    struct qemu_CreateDXGIFactory2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDXGIFACTORY2);
    call.flags = flags;
    call.iid = (ULONG_PTR)iid;
    call.factory = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern HRESULT WINAPI CreateDXGIFactory2(UINT flags, REFIID iid, void **factory);
void qemu_CreateDXGIFactory2(struct qemu_syscall *call)
{
    struct qemu_CreateDXGIFactory2 *c = (struct qemu_CreateDXGIFactory2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateDXGIFactory2(c->flags, QEMU_G2H(c->iid), QEMU_G2H(c->factory));
}

#endif

struct qemu_CreateDXGIFactory1
{
    struct qemu_syscall super;
    uint64_t iid;
    uint64_t factory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CreateDXGIFactory1(REFIID iid, void **factory)
{
    struct qemu_CreateDXGIFactory1 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDXGIFACTORY1);
    call.iid = (ULONG_PTR)iid;
    call.factory = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateDXGIFactory1(struct qemu_syscall *call)
{
    struct qemu_CreateDXGIFactory1 *c = (struct qemu_CreateDXGIFactory1 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateDXGIFactory1(QEMU_G2H(c->iid), QEMU_G2H(c->factory));
}

#endif

struct qemu_CreateDXGIFactory
{
    struct qemu_syscall super;
    uint64_t iid;
    uint64_t factory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CreateDXGIFactory(REFIID iid, void **factory)
{
    struct qemu_CreateDXGIFactory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDXGIFACTORY);
    call.iid = (ULONG_PTR)iid;
    call.factory = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateDXGIFactory(struct qemu_syscall *call)
{
    struct qemu_CreateDXGIFactory *c = (struct qemu_CreateDXGIFactory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateDXGIFactory(QEMU_G2H(c->iid), QEMU_G2H(c->factory));
}

#endif

struct qemu_DXGID3D10CreateDevice
{
    struct qemu_syscall super;
    uint64_t d3d10core;
    uint64_t factory;
    uint64_t adapter;
    uint64_t flags;
    uint64_t feature_levels;
    uint64_t level_count;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DXGID3D10CreateDevice(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device)
{
    struct qemu_DXGID3D10CreateDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGID3D10CREATEDEVICE);
    call.d3d10core = (ULONG_PTR)d3d10core;
    call.factory = (ULONG_PTR)factory;
    call.adapter = (ULONG_PTR)adapter;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.level_count = level_count;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern HRESULT WINAPI DXGID3D10CreateDevice(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device);
void qemu_DXGID3D10CreateDevice(struct qemu_syscall *call)
{
    struct qemu_DXGID3D10CreateDevice *c = (struct qemu_DXGID3D10CreateDevice *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DXGID3D10CreateDevice(QEMU_G2H(c->d3d10core), QEMU_G2H(c->factory), QEMU_G2H(c->adapter),
            c->flags, QEMU_G2H(c->feature_levels), c->level_count, QEMU_G2H(c->device));
}

#endif

struct qemu_DXGID3D10RegisterLayers
{
    struct qemu_syscall super;
    uint64_t layers;
    uint64_t layer_count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DXGID3D10RegisterLayers(const void *layers, UINT layer_count)
{
    struct qemu_DXGID3D10RegisterLayers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DXGID3D10REGISTERLAYERS);
    call.layers = (ULONG_PTR)layers;
    call.layer_count = layer_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern HRESULT WINAPI DXGID3D10RegisterLayers(const void *layers, UINT layer_count);
void qemu_DXGID3D10RegisterLayers(struct qemu_syscall *call)
{
    struct qemu_DXGID3D10RegisterLayers *c = (struct qemu_DXGID3D10RegisterLayers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DXGID3D10RegisterLayers(QEMU_G2H(c->layers), c->layer_count);
}

#endif

struct qemu_dll_init
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        qemu_syscall(&call.super);
    }

    return TRUE;
}

#else

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CreateDXGIFactory,
    qemu_CreateDXGIFactory1,
    qemu_CreateDXGIFactory2,
    qemu_DXGID3D10CreateDevice,
    qemu_DXGID3D10RegisterLayers,
    qemu_init_dll,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side dxgi wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
