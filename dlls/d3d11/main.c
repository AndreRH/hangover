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
#include <d3d11.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d11.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);
#endif

struct qemu_D3D11CoreRegisterLayers
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3D11CoreRegisterLayers(void)
{
    struct qemu_D3D11CoreRegisterLayers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11COREREGISTERLAYERS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern HRESULT WINAPI D3D11CoreRegisterLayers(void);
static void qemu_D3D11CoreRegisterLayers(struct qemu_syscall *call)
{
    struct qemu_D3D11CoreRegisterLayers *c = (struct qemu_D3D11CoreRegisterLayers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3D11CoreRegisterLayers();
}

#endif

struct qemu_D3D11CoreCreateDevice
{
    struct qemu_syscall super;
    uint64_t factory;
    uint64_t adapter;
    uint64_t flags;
    uint64_t feature_levels;
    uint64_t levels;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3D11CoreCreateDevice(IDXGIFactory *factory, IDXGIAdapter *adapter, UINT flags,
        const D3D_FEATURE_LEVEL *feature_levels, UINT levels, ID3D11Device **device)
{
    struct qemu_D3D11CoreCreateDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11CORECREATEDEVICE);
    call.factory = (ULONG_PTR)factory;
    call.adapter = (ULONG_PTR)adapter;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.levels = levels;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern HRESULT WINAPI D3D11CoreCreateDevice(IDXGIFactory *factory, IDXGIAdapter *adapter, UINT flags,
        const D3D_FEATURE_LEVEL *feature_levels, UINT levels, ID3D11Device **device);
static void qemu_D3D11CoreCreateDevice(struct qemu_syscall *call)
{
    struct qemu_D3D11CoreCreateDevice *c = (struct qemu_D3D11CoreCreateDevice *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3D11CoreCreateDevice(QEMU_G2H(c->factory), QEMU_G2H(c->adapter), c->flags,
            QEMU_G2H(c->feature_levels), c->levels, QEMU_G2H(c->device));
}

#endif

struct qemu_D3D11CreateDevice
{
    struct qemu_syscall super;
    uint64_t adapter;
    uint64_t driver_type;
    uint64_t swrast;
    uint64_t flags;
    uint64_t feature_levels;
    uint64_t levels;
    uint64_t sdk_version;
    uint64_t device_out;
    uint64_t obtained_feature_level;
    uint64_t immediate_context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3D11CreateDevice(IDXGIAdapter *adapter, D3D_DRIVER_TYPE driver_type, HMODULE swrast,
        UINT flags, const D3D_FEATURE_LEVEL *feature_levels, UINT levels, UINT sdk_version, ID3D11Device **device_out,
        D3D_FEATURE_LEVEL *obtained_feature_level, ID3D11DeviceContext **immediate_context)
{
    struct qemu_D3D11CreateDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11CREATEDEVICE);
    call.adapter = (ULONG_PTR)adapter;
    call.driver_type = driver_type;
    call.swrast = (ULONG_PTR)swrast;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.levels = levels;
    call.sdk_version = sdk_version;
    call.device_out = (ULONG_PTR)device_out;
    call.obtained_feature_level = (ULONG_PTR)obtained_feature_level;
    call.immediate_context = (ULONG_PTR)immediate_context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_D3D11CreateDevice(struct qemu_syscall *call)
{
    struct qemu_D3D11CreateDevice *c = (struct qemu_D3D11CreateDevice *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3D11CreateDevice(QEMU_G2H(c->adapter), c->driver_type, QEMU_G2H(c->swrast), c->flags,
            QEMU_G2H(c->feature_levels), c->levels, c->sdk_version, QEMU_G2H(c->device_out),
            QEMU_G2H(c->obtained_feature_level), QEMU_G2H(c->immediate_context));
}

#endif

struct qemu_D3D11CreateDeviceAndSwapChain
{
    struct qemu_syscall super;
    uint64_t adapter;
    uint64_t driver_type;
    uint64_t swrast;
    uint64_t flags;
    uint64_t feature_levels;
    uint64_t levels;
    uint64_t sdk_version;
    uint64_t swapchain_desc;
    uint64_t swapchain;
    uint64_t device_out;
    uint64_t obtained_feature_level;
    uint64_t immediate_context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3D11CreateDeviceAndSwapChain(IDXGIAdapter *adapter, D3D_DRIVER_TYPE driver_type,
        HMODULE swrast, UINT flags, const D3D_FEATURE_LEVEL *feature_levels, UINT levels, UINT sdk_version,
        const DXGI_SWAP_CHAIN_DESC *swapchain_desc, IDXGISwapChain **swapchain, ID3D11Device **device_out,
        D3D_FEATURE_LEVEL *obtained_feature_level, ID3D11DeviceContext **immediate_context)
{
    struct qemu_D3D11CreateDeviceAndSwapChain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11CREATEDEVICEANDSWAPCHAIN);
    call.adapter = (ULONG_PTR)adapter;
    call.driver_type = driver_type;
    call.swrast = (ULONG_PTR)swrast;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.levels = levels;
    call.sdk_version = sdk_version;
    call.swapchain_desc = (ULONG_PTR)swapchain_desc;
    call.swapchain = (ULONG_PTR)swapchain;
    call.device_out = (ULONG_PTR)device_out;
    call.obtained_feature_level = (ULONG_PTR)obtained_feature_level;
    call.immediate_context = (ULONG_PTR)immediate_context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_D3D11CreateDeviceAndSwapChain(struct qemu_syscall *call)
{
    struct qemu_D3D11CreateDeviceAndSwapChain *c = (struct qemu_D3D11CreateDeviceAndSwapChain *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3D11CreateDeviceAndSwapChain(QEMU_G2H(c->adapter), c->driver_type, QEMU_G2H(c->swrast),
            c->flags, QEMU_G2H(c->feature_levels), c->levels, c->sdk_version, QEMU_G2H(c->swapchain_desc),
            QEMU_G2H(c->swapchain), QEMU_G2H(c->device_out), QEMU_G2H(c->obtained_feature_level),
            QEMU_G2H(c->immediate_context));
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
    qemu_D3D11CoreCreateDevice,
    qemu_D3D11CoreRegisterLayers,
    qemu_D3D11CreateDevice,
    qemu_D3D11CreateDeviceAndSwapChain,
    qemu_init_dll,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side d3d11 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
