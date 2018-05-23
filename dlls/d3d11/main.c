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
#include <d3d11.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemudxgi.h"
#include "qemu_d3d11.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

#ifdef QEMU_DLL_GUEST

static const char *debug_d3d_driver_type(D3D_DRIVER_TYPE driver_type)
{
    switch (driver_type)
    {
#define D3D11_TO_STR(x) case x: return #x
        D3D11_TO_STR(D3D_DRIVER_TYPE_UNKNOWN);
        D3D11_TO_STR(D3D_DRIVER_TYPE_HARDWARE);
        D3D11_TO_STR(D3D_DRIVER_TYPE_REFERENCE);
        D3D11_TO_STR(D3D_DRIVER_TYPE_NULL);
        D3D11_TO_STR(D3D_DRIVER_TYPE_SOFTWARE);
        D3D11_TO_STR(D3D_DRIVER_TYPE_WARP);
#undef D3D11_TO_STR
        default:
            return wine_dbg_sprintf("Unrecognized D3D_DRIVER_TYPE %#x\n", driver_type);
    }
}

static HRESULT WINAPI layer_init(enum dxgi_device_layer_id id, DWORD *count, DWORD *values)
{
    WINE_TRACE("id %#x, count %p, values %p\n", id, count, values);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x\n", id);
        return E_NOTIMPL;
    }

    return S_OK;
}

static UINT WINAPI layer_get_size(enum dxgi_device_layer_id id, struct layer_get_size_args *args, DWORD unknown0)
{
    WINE_FIXME("id %#x, args %p, unknown0 %#x\n", id, args, unknown0);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x\n", id);
        return 0;
    }

    return 0;
}

static HRESULT WINAPI layer_create(enum dxgi_device_layer_id id, void **layer_base, DWORD unknown0,
        void *device_object, REFIID riid, void **device_layer)
{
    struct d3d_device *object;

    WINE_FIXME("id %#x, layer_base %p, unknown0 %#x, device_object %p, riid %s, device_layer %p\n",
            id, layer_base, unknown0, device_object, wine_dbgstr_guid(riid), device_layer);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x\n", id);
        *device_layer = NULL;
        return E_NOTIMPL;
    }

//     object = *layer_base;
//     d3d_device_init(object, device_object);
//     *device_layer = &object->IUnknown_inner;

    WINE_TRACE("Created d3d10 device at %p\n", object);

    return S_OK;
}

static void WINAPI layer_set_feature_level(enum dxgi_device_layer_id id, void *device,
        D3D_FEATURE_LEVEL feature_level)
{
//     struct d3d_device *d3d_device = device;

    WINE_FIXME("id %#x, device %p, feature_level %#x.\n", id, device, feature_level);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x.\n", id);
        return;
    }

//     d3d_device->feature_level = feature_level;
}

extern HRESULT WINAPI DXGID3D10RegisterLayers(const struct dxgi_device_layer *layers, UINT layer_count);
WINBASEAPI HRESULT WINAPI D3D11CoreRegisterLayers(void)
{
    static const struct dxgi_device_layer layers[] =
    {
        {DXGI_DEVICE_LAYER_D3D10_DEVICE, layer_init, layer_get_size, layer_create, layer_set_feature_level},
    };

    DXGID3D10RegisterLayers(layers, sizeof(layers) / sizeof(*layers));

    return S_OK;
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI D3D11CoreCreateDevice(IDXGIFactory *factory, IDXGIAdapter *adapter, UINT flags,
        const D3D_FEATURE_LEVEL *feature_levels, UINT levels, ID3D11Device **device)
{
    IUnknown *dxgi_device;
    HMODULE d3d11;
    HRESULT hr;

    WINE_TRACE("factory %p, adapter %p, flags %#x, feature_levels %p, levels %u, device %p.\n",
            factory, adapter, flags, feature_levels, levels, device);

    d3d11 = GetModuleHandleA("d3d11.dll");
    hr = p_DXGID3D10CreateDevice(d3d11, factory, adapter, flags, feature_levels, levels, (void **)&dxgi_device);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create device, returning %#x.\n", hr);
        return hr;
    }

    hr = IUnknown_QueryInterface(dxgi_device, &IID_ID3D11Device, (void **)device);
    IUnknown_Release(dxgi_device);
    if (FAILED(hr))
    {
        WINE_ERR("Failed to query ID3D11Device interface, returning E_FAIL.\n");
        return E_FAIL;
    }

    return S_OK;
}

#else

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

HRESULT (* WINAPI p_DXGID3D10CreateDevice)(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device);

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;
    HMODULE dxgi;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        qemu_syscall(&call.super);

        dxgi = GetModuleHandleA("dxgi");
        if (!dxgi)
            WINE_ERR("Cannot get dxgi.dll.\n");
        p_DXGID3D10CreateDevice = (void *)GetProcAddress(dxgi, "DXGID3D10CreateDevice");
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
