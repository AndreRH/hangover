/*
 * Copyright 2008 Henri Verbeet for CodeWeavers
 * Copyright 2013 Austin English
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
#include <initguid.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <d3d11.h>
#include <debug.h>
#else
#include <d3d11_2.h>
#include <wine/debug.h>
#endif

#include "qemudxgi.h"
#include "qemu_d3d11.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

struct qemu_layer_get_size
{
    struct qemu_syscall super;
};

struct qemu_layer_create
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t host_device;
    uint64_t immediate_context;
};

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
    struct qemu_layer_get_size call;
    WINE_TRACE("id %#x, args %p, unknown0 %#x\n", id, args, unknown0);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x\n", id);
        return 0;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_LAYER_GET_SIZE);
    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI layer_create(enum dxgi_device_layer_id id, void **layer_base, DWORD unknown0,
        void *device_object, REFIID riid, void **device_layer, uint64_t host_dxgi_device)
{
    struct qemu_layer_create call;
    struct qemu_d3d11_device *object;
    struct qemu_d3d11_device_context *context;

    WINE_TRACE("id %#x, layer_base %p, unknown0 %#x, device_object %p, riid %s, device_layer %p\n",
            id, layer_base, unknown0, device_object, wine_dbgstr_guid(riid), device_layer);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x\n", id);
        *device_layer = NULL;
        return E_NOTIMPL;
    }

    object = *layer_base;
    qemu_d3d11_device_guest_init(object, device_object);
    *device_layer = &object->IUnknown_inner;

    call.super.id = QEMU_SYSCALL_ID(CALL_LAYER_CREATE);
    call.device = (ULONG_PTR)object;
    call.host_device = host_dxgi_device;
    qemu_syscall(&call.super);

    context = (struct qemu_d3d11_device_context *)(ULONG_PTR)call.immediate_context;
    qemu_d3d11_context_guest_init(context);

    WINE_TRACE("Created d3d10 device at %p\n", object);

    return S_OK;
}

static void WINAPI layer_set_feature_level(enum dxgi_device_layer_id id, void *device,
        D3D_FEATURE_LEVEL feature_level)
{
    WINE_TRACE("id %#x, device %p, feature_level %#x.\n", id, device, feature_level);

    if (id != DXGI_DEVICE_LAYER_D3D10_DEVICE)
    {
        WINE_WARN("Unknown layer id %#x.\n", id);
        return;
    }
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

#else

static void qemu_layer_get_size(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = sizeof(struct qemu_d3d11_device);
}

static HRESULT STDMETHODCALLTYPE d3d11_device_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE d3d11_device_priv_data_AddRef(IUnknown *iface)
{
    return 2;
}

static ULONG STDMETHODCALLTYPE d3d11_device_priv_data_Release(IUnknown *iface)
{
    /* Don't bother freeing anything. The wrapper struct dies with the dxgi struct. */
    return 1;
}

static struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    d3d11_device_priv_data_QueryInterface,
    d3d11_device_priv_data_AddRef,
    d3d11_device_priv_data_Release,
};

static void qemu_layer_create(struct qemu_syscall *call)
{
    struct qemu_layer_create *c = (struct qemu_layer_create *)call;
    struct qemu_d3d11_device *device;
    IUnknown *host_device;
    ID3D11DeviceContext1 *immediate_context;
    HRESULT hr;

    device = QEMU_G2H(c->device);
    host_device = QEMU_G2H(c->host_device);
    WINE_TRACE("Initializing device %p host side.\n", device);

    /* Do not hold references, the wrapper shares the refcount with the host device. */
    hr = IUnknown_QueryInterface(host_device, &IID_ID3D11Device2, (void **)&device->host_d3d11);
    if (FAILED(hr))
        WINE_ERR("Could not get ID3D11Device2 host interface.\n");
    ID3D11Device2_Release(device->host_d3d11);

    hr = IUnknown_QueryInterface(host_device, &IID_ID3D10Device1, (void **)&device->host_d3d10);
    if (FAILED(hr))
        WINE_ERR("Could not get ID3D10Device1 host interface.\n");
    ID3D10Device1_Release(device->host_d3d10);

    hr = IUnknown_QueryInterface(host_device, &IID_ID3D10Multithread, (void **)&device->host_mt);
    if (FAILED(hr))
        WINE_ERR("Could not get ID3D10Multithread host interface.\n");
    ID3D10Multithread_Release(device->host_mt);

    ID3D11Device1_GetImmediateContext(device->host_d3d11, (ID3D11DeviceContext **)&immediate_context);
    device->immediate_context.host = immediate_context;
    ID3D11DeviceContext1_Release(immediate_context);

    c->immediate_context = QEMU_H2G(&device->immediate_context);

    device->priv_data_iface.lpVtbl = &priv_data_vtbl;
    ID3D11Device_SetPrivateDataInterface(device->host_d3d11, &IID_d3d11_priv_data, &device->priv_data_iface);
}

#endif

#ifdef QEMU_DLL_GUEST

HRESULT WINAPI D3D11CoreCreateDevice(IDXGIFactory *factory, IDXGIAdapter *adapter, UINT flags,
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

HRESULT WINAPI D3D11CreateDevice(IDXGIAdapter *adapter, D3D_DRIVER_TYPE driver_type, HMODULE swrast,
        UINT flags, const D3D_FEATURE_LEVEL *feature_levels, UINT levels, UINT sdk_version, ID3D11Device **device_out,
        D3D_FEATURE_LEVEL *obtained_feature_level, ID3D11DeviceContext **immediate_context)
{
    static const D3D_FEATURE_LEVEL default_feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };
    IDXGIFactory *factory;
    ID3D11Device *device;
    HRESULT hr;

    WINE_TRACE("adapter %p, driver_type %x, swrast %p, flags %#x, feature_levels %p, levels %u, sdk_version %u, "
            "device %p, obtained_feature_level %p, immediate_context %p.\n",
            adapter, driver_type, swrast, flags, feature_levels, levels, sdk_version,
            device_out, obtained_feature_level, immediate_context);

    if (device_out)
        *device_out = NULL;
    if (obtained_feature_level)
        *obtained_feature_level = 0;
    if (immediate_context)
        *immediate_context = NULL;

    if (adapter)
    {
        IDXGIAdapter_AddRef(adapter);
        hr = IDXGIAdapter_GetParent(adapter, &IID_IDXGIFactory, (void **)&factory);
        if (FAILED(hr))
        {
            WINE_WARN("Failed to get dxgi factory, returning %#x.\n", hr);
            return hr;
        }
    }
    else
    {
        hr = CreateDXGIFactory1(&IID_IDXGIFactory, (void **)&factory);
        if (FAILED(hr))
        {
            WINE_WARN("Failed to create dxgi factory, returning %#x.\n", hr);
            return hr;
        }

        switch(driver_type)
        {
            case D3D_DRIVER_TYPE_HARDWARE:
            {
                hr = IDXGIFactory_EnumAdapters(factory, 0, &adapter);
                if (FAILED(hr))
                {
                    WINE_WARN("No adapters found, returning %#x.\n", hr);
                    IDXGIFactory_Release(factory);
                    return hr;
                }
                break;
            }

            case D3D_DRIVER_TYPE_NULL:
                WINE_FIXME("NULL device not implemented, falling back to refrast.\n");
                /* fall through, for now */
            case D3D_DRIVER_TYPE_REFERENCE:
            {
                HMODULE refrast = LoadLibraryA("d3d11ref.dll");
                if (!refrast)
                {
                    WINE_WARN("Failed to load refrast, returning E_FAIL.\n");
                    IDXGIFactory_Release(factory);
                    return E_FAIL;
                }
                hr = IDXGIFactory_CreateSoftwareAdapter(factory, refrast, &adapter);
                FreeLibrary(refrast);
                if (FAILED(hr))
                {
                    WINE_WARN("Failed to create a software adapter, returning %#x.\n", hr);
                    IDXGIFactory_Release(factory);
                    return hr;
                }
                break;
            }

            case D3D_DRIVER_TYPE_SOFTWARE:
            {
                if (!swrast)
                {
                    WINE_WARN("Software device requested, but NULL swrast passed, returning E_FAIL.\n");
                    IDXGIFactory_Release(factory);
                    return E_FAIL;
                }
                hr = IDXGIFactory_CreateSoftwareAdapter(factory, swrast, &adapter);
                if (FAILED(hr))
                {
                    WINE_WARN("Failed to create a software adapter, returning %#x.\n", hr);
                    IDXGIFactory_Release(factory);
                    return hr;
                }
                break;
            }

            default:
                WINE_FIXME("Unhandled driver type %#x.\n", driver_type);
                IDXGIFactory_Release(factory);
                return E_FAIL;
        }
    }

    if (!feature_levels)
    {
        feature_levels = default_feature_levels;
        levels = sizeof(default_feature_levels) / sizeof(*default_feature_levels);
    }
    hr = D3D11CoreCreateDevice(factory, adapter, flags, feature_levels, levels, &device);
    IDXGIAdapter_Release(adapter);
    IDXGIFactory_Release(factory);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create a device, returning %#x.\n", hr);
        return hr;
    }

    WINE_TRACE("Created ID3D11Device %p.\n", device);

    if (obtained_feature_level)
        *obtained_feature_level = ID3D11Device_GetFeatureLevel(device);

    if (immediate_context)
        ID3D11Device_GetImmediateContext(device, immediate_context);

    if (device_out)
        *device_out = device;
    else
        ID3D11Device_Release(device);

    return (device_out || immediate_context) ? S_OK : S_FALSE;
}

WINBASEAPI HRESULT WINAPI D3D11CreateDeviceAndSwapChain(IDXGIAdapter *adapter, D3D_DRIVER_TYPE driver_type,
        HMODULE swrast, UINT flags, const D3D_FEATURE_LEVEL *feature_levels, UINT levels, UINT sdk_version,
        const DXGI_SWAP_CHAIN_DESC *swapchain_desc, IDXGISwapChain **swapchain, ID3D11Device **device_out,
        D3D_FEATURE_LEVEL *obtained_feature_level, ID3D11DeviceContext **immediate_context)
{
    DXGI_SWAP_CHAIN_DESC desc;
    IDXGIDevice *dxgi_device;
    IDXGIFactory *factory;
    ID3D11Device *device;
    HRESULT hr;

    WINE_TRACE("adapter %p, driver_type %x, swrast %p, flags %#x, feature_levels %p, levels %u, sdk_version %u, "
            "swapchain_desc %p, swapchain %p, device %p, obtained_feature_level %p, immediate_context %p.\n",
            adapter, driver_type, swrast, flags, feature_levels, levels, sdk_version,
            swapchain_desc, swapchain, device_out, obtained_feature_level, immediate_context);

    if (swapchain)
        *swapchain = NULL;
    if (device_out)
        *device_out = NULL;

    if (FAILED(hr = D3D11CreateDevice(adapter, driver_type, swrast, flags, feature_levels, levels, sdk_version,
            &device, obtained_feature_level, immediate_context)))
    {
        WINE_WARN("Failed to create a device, returning %#x.\n", hr);
        return hr;
    }

    if (swapchain)
    {
        if (FAILED(hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (void **)&dxgi_device)))
        {
            WINE_ERR("Failed to get a dxgi device from the d3d11 device, returning %#x.\n", hr);
            goto cleanup;
        }

        hr = IDXGIDevice_GetAdapter(dxgi_device, &adapter);
        IDXGIDevice_Release(dxgi_device);
        if (FAILED(hr))
        {
            WINE_ERR("Failed to get the device adapter, returning %#x.\n", hr);
            goto cleanup;
        }

        hr = IDXGIAdapter_GetParent(adapter, &IID_IDXGIFactory, (void **)&factory);
        IDXGIAdapter_Release(adapter);
        if (FAILED(hr))
        {
            WINE_ERR("Failed to get the adapter factory, returning %#x.\n", hr);
            goto cleanup;
        }

        desc = *swapchain_desc;
        hr = IDXGIFactory_CreateSwapChain(factory, (IUnknown *)device, &desc, swapchain);
        IDXGIFactory_Release(factory);
        if (FAILED(hr))
        {
            WINE_WARN("Failed to create a swapchain, returning %#x.\n", hr);
            goto cleanup;
        }

        WINE_TRACE("Created IDXGISwapChain %p.\n", *swapchain);
    }

    if (device_out)
        *device_out = device;
    else
        ID3D11Device_Release(device);

    return (swapchain || device_out || immediate_context) ? S_OK : S_FALSE;

cleanup:
    ID3D11Device_Release(device);
    if (obtained_feature_level)
        *obtained_feature_level = 0;
    if (immediate_context)
    {
        ID3D11DeviceContext_Release(*immediate_context);
        *immediate_context = NULL;
    }

    return hr;
}

#endif

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t reason;
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
        call.reason = DLL_PROCESS_ATTACH;
        qemu_syscall(&call.super);

        dxgi = GetModuleHandleA("dxgi");
        if (!dxgi)
            WINE_ERR("Cannot get dxgi.dll.\n");
        p_DXGID3D10CreateDevice = (void *)GetProcAddress(dxgi, "DXGID3D10CreateDevice");
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_DETACH;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

enum D3D11_USAGE d3d11_usage_from_d3d10_usage(enum D3D10_USAGE usage)
{
    switch (usage)
    {
        case D3D10_USAGE_DEFAULT: return D3D11_USAGE_DEFAULT;
        case D3D10_USAGE_IMMUTABLE: return D3D11_USAGE_IMMUTABLE;
        case D3D10_USAGE_DYNAMIC: return D3D11_USAGE_DYNAMIC;
        case D3D10_USAGE_STAGING: return D3D11_USAGE_STAGING;
        default:
            WINE_FIXME("Unhandled usage %#x.\n", usage);
            return D3D11_USAGE_DEFAULT;
    }
}

UINT d3d11_bind_flags_from_d3d10_bind_flags(UINT bind_flags)
{
    static const UINT handled_flags = D3D10_BIND_VERTEX_BUFFER
            | D3D10_BIND_INDEX_BUFFER
            | D3D10_BIND_CONSTANT_BUFFER
            | D3D10_BIND_SHADER_RESOURCE
            | D3D10_BIND_STREAM_OUTPUT
            | D3D10_BIND_RENDER_TARGET
            | D3D10_BIND_DEPTH_STENCIL;
    UINT d3d11_bind_flags = bind_flags & handled_flags;

    if (bind_flags & ~handled_flags)
        WINE_FIXME("Unhandled bind flags %#x.\n", bind_flags & ~handled_flags);

    return d3d11_bind_flags;
}

UINT d3d11_cpu_access_flags_from_d3d10_cpu_access_flags(UINT cpu_access_flags)
{
    static const UINT handled_flags = D3D10_CPU_ACCESS_WRITE
            | D3D10_CPU_ACCESS_READ;
    UINT d3d11_cpu_access_flags = cpu_access_flags & handled_flags;

    if (cpu_access_flags & ~handled_flags)
        WINE_FIXME("Unhandled cpu access flags %#x.\n", cpu_access_flags & ~handled_flags);

    return d3d11_cpu_access_flags;
}

UINT d3d11_resource_misc_flags_from_d3d10_resource_misc_flags(UINT resource_misc_flags)
{
    static const UINT bitwise_identical_flags = D3D10_RESOURCE_MISC_GENERATE_MIPS
            | D3D10_RESOURCE_MISC_SHARED
            | D3D10_RESOURCE_MISC_TEXTURECUBE;
    const UINT handled_flags = bitwise_identical_flags
            | D3D10_RESOURCE_MISC_SHARED_KEYEDMUTEX
            | D3D10_RESOURCE_MISC_GDI_COMPATIBLE;
    UINT d3d11_resource_misc_flags = resource_misc_flags & bitwise_identical_flags;

    if (resource_misc_flags & D3D10_RESOURCE_MISC_SHARED_KEYEDMUTEX)
        d3d11_resource_misc_flags |= D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
    if (resource_misc_flags & D3D10_RESOURCE_MISC_GDI_COMPATIBLE)
        d3d11_resource_misc_flags |= D3D11_RESOURCE_MISC_GDI_COMPATIBLE;

    if (resource_misc_flags & ~handled_flags)
        WINE_FIXME("Unhandled resource misc flags %#x.\n", resource_misc_flags & ~handled_flags);

    return d3d11_resource_misc_flags;
}

#else

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
    HMODULE host_d3d11;

    /* We don't call anything from d3d11 directly, so the build system won't link to it. But we need the
     * host library present so that the dxgi wrapper will correctly translate the HMODULE passed to
     * DXGID3D10CreateDevice via qemu_ops->qemu_module_g2h. */
    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            host_d3d11 = LoadLibraryA("d3d11");
            if (!host_d3d11)
                WINE_ERR("Failed to load d3d11.dll, expect problems.\n");
            break;

        case DLL_PROCESS_DETACH:
            FreeLibrary(host_d3d11);
            break;
    }
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_d3d10_buffer_AddRef,
    qemu_d3d10_buffer_GetDesc,
    qemu_d3d10_buffer_GetEvictionPriority,
    qemu_d3d10_buffer_GetPrivateData,
    qemu_d3d10_buffer_GetType,
    qemu_d3d10_buffer_Map,
    qemu_d3d10_buffer_QueryInterface,
    qemu_d3d10_buffer_Release,
    qemu_d3d10_buffer_SetEvictionPriority,
    qemu_d3d10_buffer_SetPrivateData,
    qemu_d3d10_buffer_SetPrivateDataInterface,
    qemu_d3d10_buffer_Unmap,
    qemu_d3d10_depthstencil_view_AddRef,
    qemu_d3d10_depthstencil_view_GetDesc,
    qemu_d3d10_depthstencil_view_GetPrivateData,
    qemu_d3d10_depthstencil_view_GetResource,
    qemu_d3d10_depthstencil_view_QueryInterface,
    qemu_d3d10_depthstencil_view_Release,
    qemu_d3d10_depthstencil_view_SetPrivateData,
    qemu_d3d10_depthstencil_view_SetPrivateDataInterface,
    qemu_d3d10_device_CheckCounter,
    qemu_d3d10_device_CheckCounterInfo,
    qemu_d3d10_device_CheckFormatSupport,
    qemu_d3d10_device_CheckMultisampleQualityLevels,
    qemu_d3d10_device_ClearDepthStencilView,
    qemu_d3d10_device_ClearRenderTargetView,
    qemu_d3d10_device_ClearState,
    qemu_d3d10_device_CopyResource,
    qemu_d3d10_device_CopySubresourceRegion,
    qemu_d3d10_device_CreateBlendState,
    qemu_d3d10_device_CreateBlendState1,
    qemu_d3d10_device_CreateCounter,
    qemu_d3d10_device_CreateDepthStencilState,
    qemu_d3d10_device_CreateDepthStencilView,
    qemu_d3d10_device_CreateGeometryShader,
    qemu_d3d10_device_CreateGeometryShaderWithStreamOutput,
    qemu_d3d10_device_CreateInputLayout,
    qemu_d3d10_device_CreatePixelShader,
    qemu_d3d10_device_CreatePredicate,
    qemu_d3d10_device_CreateQuery,
    qemu_d3d10_device_CreateRasterizerState,
    qemu_d3d10_device_CreateRenderTargetView,
    qemu_d3d10_device_CreateSamplerState,
    qemu_d3d10_device_CreateShaderResourceView,
    qemu_d3d10_device_CreateShaderResourceView1,
    qemu_d3d10_device_CreateVertexShader,
    qemu_d3d10_device_Draw,
    qemu_d3d10_device_DrawAuto,
    qemu_d3d10_device_DrawIndexed,
    qemu_d3d10_device_DrawIndexedInstanced,
    qemu_d3d10_device_DrawInstanced,
    qemu_d3d10_device_Flush,
    qemu_d3d10_device_GenerateMips,
    qemu_d3d10_device_GetCreationFlags,
    qemu_d3d10_device_GetDeviceRemovedReason,
    qemu_d3d10_device_GetExceptionMode,
    qemu_d3d10_device_GetFeatureLevel,
    qemu_d3d10_device_GetPredication,
    qemu_d3d10_device_GetPrivateData,
    qemu_d3d10_device_GetTextFilterSize,
    qemu_d3d10_device_GSGetConstantBuffers,
    qemu_d3d10_device_GSGetSamplers,
    qemu_d3d10_device_GSGetShader,
    qemu_d3d10_device_GSGetShaderResources,
    qemu_d3d10_device_GSSetConstantBuffers,
    qemu_d3d10_device_GSSetSamplers,
    qemu_d3d10_device_GSSetShader,
    qemu_d3d10_device_GSSetShaderResources,
    qemu_d3d10_device_IAGetIndexBuffer,
    qemu_d3d10_device_IAGetInputLayout,
    qemu_d3d10_device_IAGetPrimitiveTopology,
    qemu_d3d10_device_IAGetVertexBuffers,
    qemu_d3d10_device_IASetIndexBuffer,
    qemu_d3d10_device_IASetInputLayout,
    qemu_d3d10_device_IASetPrimitiveTopology,
    qemu_d3d10_device_IASetVertexBuffers,
    qemu_d3d10_device_OMGetBlendState,
    qemu_d3d10_device_OMGetDepthStencilState,
    qemu_d3d10_device_OMGetRenderTargets,
    qemu_d3d10_device_OMSetBlendState,
    qemu_d3d10_device_OMSetDepthStencilState,
    qemu_d3d10_device_OMSetRenderTargets,
    qemu_d3d10_device_OpenSharedResource,
    qemu_d3d10_device_PSGetConstantBuffers,
    qemu_d3d10_device_PSGetSamplers,
    qemu_d3d10_device_PSGetShader,
    qemu_d3d10_device_PSGetShaderResources,
    qemu_d3d10_device_PSSetConstantBuffers,
    qemu_d3d10_device_PSSetSamplers,
    qemu_d3d10_device_PSSetShader,
    qemu_d3d10_device_PSSetShaderResources,
    qemu_d3d10_device_ResolveSubresource,
    qemu_d3d10_device_RSGetScissorRects,
    qemu_d3d10_device_RSGetState,
    qemu_d3d10_device_RSGetViewports,
    qemu_d3d10_device_RSSetScissorRects,
    qemu_d3d10_device_RSSetState,
    qemu_d3d10_device_RSSetViewports,
    qemu_d3d10_device_SetExceptionMode,
    qemu_d3d10_device_SetPredication,
    qemu_d3d10_device_SetPrivateData,
    qemu_d3d10_device_SetPrivateDataInterface,
    qemu_d3d10_device_SetTextFilterSize,
    qemu_d3d10_device_SOGetTargets,
    qemu_d3d10_device_SOSetTargets,
    qemu_d3d10_device_UpdateSubresource,
    qemu_d3d10_device_VSGetConstantBuffers,
    qemu_d3d10_device_VSGetSamplers,
    qemu_d3d10_device_VSGetShader,
    qemu_d3d10_device_VSGetShaderResources,
    qemu_d3d10_device_VSSetConstantBuffers,
    qemu_d3d10_device_VSSetSamplers,
    qemu_d3d10_device_VSSetShader,
    qemu_d3d10_device_VSSetShaderResources,
    qemu_d3d10_geometry_shader_AddRef,
    qemu_d3d10_geometry_shader_GetDevice,
    qemu_d3d10_geometry_shader_GetPrivateData,
    qemu_d3d10_geometry_shader_QueryInterface,
    qemu_d3d10_geometry_shader_Release,
    qemu_d3d10_geometry_shader_SetPrivateData,
    qemu_d3d10_geometry_shader_SetPrivateDataInterface,
    qemu_d3d10_multithread_Enter,
    qemu_d3d10_multithread_GetMultithreadProtected,
    qemu_d3d10_multithread_Leave,
    qemu_d3d10_multithread_SetMultithreadProtected,
    qemu_d3d10_pixel_shader_AddRef,
    qemu_d3d10_pixel_shader_GetDevice,
    qemu_d3d10_pixel_shader_GetPrivateData,
    qemu_d3d10_pixel_shader_QueryInterface,
    qemu_d3d10_pixel_shader_Release,
    qemu_d3d10_pixel_shader_SetPrivateData,
    qemu_d3d10_pixel_shader_SetPrivateDataInterface,
    qemu_d3d10_rendertarget_view_AddRef,
    qemu_d3d10_rendertarget_view_GetDesc,
    qemu_d3d10_rendertarget_view_GetPrivateData,
    qemu_d3d10_rendertarget_view_GetResource,
    qemu_d3d10_rendertarget_view_QueryInterface,
    qemu_d3d10_rendertarget_view_Release,
    qemu_d3d10_rendertarget_view_SetPrivateData,
    qemu_d3d10_rendertarget_view_SetPrivateDataInterface,
    qemu_d3d10_shader_resource_view_AddRef,
    qemu_d3d10_shader_resource_view_GetDesc,
    qemu_d3d10_shader_resource_view_GetDesc1,
    qemu_d3d10_shader_resource_view_GetPrivateData,
    qemu_d3d10_shader_resource_view_GetResource,
    qemu_d3d10_shader_resource_view_QueryInterface,
    qemu_d3d10_shader_resource_view_Release,
    qemu_d3d10_shader_resource_view_SetPrivateData,
    qemu_d3d10_shader_resource_view_SetPrivateDataInterface,
    qemu_d3d10_texture1d_AddRef,
    qemu_d3d10_texture1d_GetDesc,
    qemu_d3d10_texture1d_GetEvictionPriority,
    qemu_d3d10_texture1d_GetPrivateData,
    qemu_d3d10_texture1d_GetType,
    qemu_d3d10_texture1d_Map,
    qemu_d3d10_texture1d_Release,
    qemu_d3d10_texture1d_SetEvictionPriority,
    qemu_d3d10_texture1d_SetPrivateData,
    qemu_d3d10_texture1d_SetPrivateDataInterface,
    qemu_d3d10_texture1d_Unmap,
    qemu_d3d10_texture2d_AddRef,
    qemu_d3d10_texture2d_GetDesc,
    qemu_d3d10_texture2d_GetEvictionPriority,
    qemu_d3d10_texture2d_GetPrivateData,
    qemu_d3d10_texture2d_GetType,
    qemu_d3d10_texture2d_Map,
    qemu_d3d10_texture2d_QueryInterface,
    qemu_d3d10_texture2d_Release,
    qemu_d3d10_texture2d_SetEvictionPriority,
    qemu_d3d10_texture2d_SetPrivateData,
    qemu_d3d10_texture2d_SetPrivateDataInterface,
    qemu_d3d10_texture2d_Unmap,
    qemu_d3d10_texture3d_AddRef,
    qemu_d3d10_texture3d_GetDesc,
    qemu_d3d10_texture3d_GetEvictionPriority,
    qemu_d3d10_texture3d_GetPrivateData,
    qemu_d3d10_texture3d_GetType,
    qemu_d3d10_texture3d_Map,
    qemu_d3d10_texture3d_QueryInterface,
    qemu_d3d10_texture3d_Release,
    qemu_d3d10_texture3d_SetEvictionPriority,
    qemu_d3d10_texture3d_SetPrivateData,
    qemu_d3d10_texture3d_SetPrivateDataInterface,
    qemu_d3d10_texture3d_Unmap,
    qemu_d3d10_vertex_shader_AddRef,
    qemu_d3d10_vertex_shader_GetPrivateData,
    qemu_d3d10_vertex_shader_QueryInterface,
    qemu_d3d10_vertex_shader_Release,
    qemu_d3d10_vertex_shader_SetPrivateData,
    qemu_d3d10_vertex_shader_SetPrivateDataInterface,
    qemu_d3d11_buffer_AddRef,
    qemu_d3d11_buffer_GetDesc,
    qemu_d3d11_buffer_GetDevice,
    qemu_d3d11_buffer_GetEvictionPriority,
    qemu_d3d11_buffer_GetPrivateData,
    qemu_d3d11_buffer_GetType,
    qemu_d3d11_buffer_QueryInterface,
    qemu_d3d11_buffer_Release,
    qemu_d3d11_buffer_SetEvictionPriority,
    qemu_d3d11_buffer_SetPrivateData,
    qemu_d3d11_buffer_SetPrivateDataInterface,
    qemu_d3d11_class_linkage_AddRef,
    qemu_d3d11_class_linkage_CreateClassInstance,
    qemu_d3d11_class_linkage_GetClassInstance,
    qemu_d3d11_class_linkage_GetDevice,
    qemu_d3d11_class_linkage_GetPrivateData,
    qemu_d3d11_class_linkage_QueryInterface,
    qemu_d3d11_class_linkage_Release,
    qemu_d3d11_class_linkage_SetPrivateData,
    qemu_d3d11_class_linkage_SetPrivateDataInterface,
    qemu_d3d11_compute_shader_AddRef,
    qemu_d3d11_compute_shader_GetDevice,
    qemu_d3d11_compute_shader_GetPrivateData,
    qemu_d3d11_compute_shader_QueryInterface,
    qemu_d3d11_compute_shader_Release,
    qemu_d3d11_compute_shader_SetPrivateData,
    qemu_d3d11_compute_shader_SetPrivateDataInterface,
    qemu_d3d11_depthstencil_view_AddRef,
    qemu_d3d11_depthstencil_view_GetDesc,
    qemu_d3d11_depthstencil_view_GetDevice,
    qemu_d3d11_depthstencil_view_GetPrivateData,
    qemu_d3d11_depthstencil_view_GetResource,
    qemu_d3d11_depthstencil_view_QueryInterface,
    qemu_d3d11_depthstencil_view_Release,
    qemu_d3d11_depthstencil_view_SetPrivateData,
    qemu_d3d11_depthstencil_view_SetPrivateDataInterface,
    qemu_d3d11_device_CheckCounter,
    qemu_d3d11_device_CheckCounterInfo,
    qemu_d3d11_device_CheckFeatureSupport,
    qemu_d3d11_device_CheckFormatSupport,
    qemu_d3d11_device_CheckMultisampleQualityLevels,
    qemu_d3d11_device_CheckMultisampleQualityLevels1,
    qemu_d3d11_device_CreateBlendState,
    qemu_d3d11_device_CreateBlendState1,
    qemu_d3d11_device_CreateBuffer,
    qemu_d3d11_device_CreateClassLinkage,
    qemu_d3d11_device_CreateComputeShader,
    qemu_d3d11_device_CreateCounter,
    qemu_d3d11_device_CreateDeferredContext,
    qemu_d3d11_device_CreateDeferredContext1,
    qemu_d3d11_device_CreateDeferredContext2,
    qemu_d3d11_device_CreateDepthStencilState,
    qemu_d3d11_device_CreateDepthStencilView,
    qemu_d3d11_device_CreateDeviceContextState,
    qemu_d3d11_device_CreateDomainShader,
    qemu_d3d11_device_CreateGeometryShader,
    qemu_d3d11_device_CreateGeometryShaderWithStreamOutput,
    qemu_d3d11_device_CreateHullShader,
    qemu_d3d11_device_CreateInputLayout,
    qemu_d3d11_device_CreatePixelShader,
    qemu_d3d11_device_CreatePredicate,
    qemu_d3d11_device_CreateQuery,
    qemu_d3d11_device_CreateRasterizerState,
    qemu_d3d11_device_CreateRasterizerState1,
    qemu_d3d11_device_CreateRenderTargetView,
    qemu_d3d11_device_CreateSamplerState,
    qemu_d3d11_device_CreateShaderResourceView,
    qemu_d3d11_device_CreateTexture1D,
    qemu_d3d11_device_CreateTexture2D,
    qemu_d3d11_device_CreateTexture3D,
    qemu_d3d11_device_CreateUnorderedAccessView,
    qemu_d3d11_device_CreateVertexShader,
    qemu_d3d11_device_GetCreationFlags,
    qemu_d3d11_device_GetDeviceRemovedReason,
    qemu_d3d11_device_GetExceptionMode,
    qemu_d3d11_device_GetFeatureLevel,
    qemu_d3d11_device_GetImmediateContext,
    qemu_d3d11_device_GetImmediateContext1,
    qemu_d3d11_device_GetImmediateContext2,
    qemu_d3d11_device_GetPrivateData,
    qemu_d3d11_device_GetResourceTiling,
    qemu_d3d11_device_OpenSharedResource,
    qemu_d3d11_device_OpenSharedResource1,
    qemu_d3d11_device_OpenSharedResourceByName,
    qemu_d3d11_device_SetExceptionMode,
    qemu_d3d11_device_SetPrivateData,
    qemu_d3d11_device_SetPrivateDataInterface,
    qemu_d3d11_domain_shader_AddRef,
    qemu_d3d11_domain_shader_GetDevice,
    qemu_d3d11_domain_shader_GetPrivateData,
    qemu_d3d11_domain_shader_QueryInterface,
    qemu_d3d11_domain_shader_Release,
    qemu_d3d11_domain_shader_SetPrivateData,
    qemu_d3d11_domain_shader_SetPrivateDataInterface,
    qemu_d3d11_geometry_shader_AddRef,
    qemu_d3d11_geometry_shader_GetDevice,
    qemu_d3d11_geometry_shader_GetPrivateData,
    qemu_d3d11_geometry_shader_QueryInterface,
    qemu_d3d11_geometry_shader_Release,
    qemu_d3d11_geometry_shader_SetPrivateData,
    qemu_d3d11_geometry_shader_SetPrivateDataInterface,
    qemu_d3d11_hull_shader_AddRef,
    qemu_d3d11_hull_shader_GetDevice,
    qemu_d3d11_hull_shader_GetPrivateData,
    qemu_d3d11_hull_shader_QueryInterface,
    qemu_d3d11_hull_shader_Release,
    qemu_d3d11_hull_shader_SetPrivateData,
    qemu_d3d11_hull_shader_SetPrivateDataInterface,
    qemu_d3d11_immediate_context_AddRef,
    qemu_d3d11_immediate_context_Begin,
    qemu_d3d11_immediate_context_ClearDepthStencilView,
    qemu_d3d11_immediate_context_ClearRenderTargetView,
    qemu_d3d11_immediate_context_ClearState,
    qemu_d3d11_immediate_context_ClearUnorderedAccessViewFloat,
    qemu_d3d11_immediate_context_ClearUnorderedAccessViewUint,
    qemu_d3d11_immediate_context_ClearView,
    qemu_d3d11_immediate_context_CopyResource,
    qemu_d3d11_immediate_context_CopyStructureCount,
    qemu_d3d11_immediate_context_CopySubresourceRegion,
    qemu_d3d11_immediate_context_CopySubresourceRegion1,
    qemu_d3d11_immediate_context_CSGetConstantBuffers,
    qemu_d3d11_immediate_context_CSGetConstantBuffers1,
    qemu_d3d11_immediate_context_CSGetSamplers,
    qemu_d3d11_immediate_context_CSGetShader,
    qemu_d3d11_immediate_context_CSGetShaderResources,
    qemu_d3d11_immediate_context_CSGetUnorderedAccessViews,
    qemu_d3d11_immediate_context_CSSetConstantBuffers,
    qemu_d3d11_immediate_context_CSSetConstantBuffers1,
    qemu_d3d11_immediate_context_CSSetSamplers,
    qemu_d3d11_immediate_context_CSSetShader,
    qemu_d3d11_immediate_context_CSSetShaderResources,
    qemu_d3d11_immediate_context_CSSetUnorderedAccessViews,
    qemu_d3d11_immediate_context_DiscardResource,
    qemu_d3d11_immediate_context_DiscardView,
    qemu_d3d11_immediate_context_DiscardView1,
    qemu_d3d11_immediate_context_Dispatch,
    qemu_d3d11_immediate_context_DispatchIndirect,
    qemu_d3d11_immediate_context_Draw,
    qemu_d3d11_immediate_context_DrawAuto,
    qemu_d3d11_immediate_context_DrawIndexed,
    qemu_d3d11_immediate_context_DrawIndexedInstanced,
    qemu_d3d11_immediate_context_DrawIndexedInstancedIndirect,
    qemu_d3d11_immediate_context_DrawInstanced,
    qemu_d3d11_immediate_context_DrawInstancedIndirect,
    qemu_d3d11_immediate_context_DSGetConstantBuffers,
    qemu_d3d11_immediate_context_DSGetConstantBuffers1,
    qemu_d3d11_immediate_context_DSGetSamplers,
    qemu_d3d11_immediate_context_DSGetShader,
    qemu_d3d11_immediate_context_DSGetShaderResources,
    qemu_d3d11_immediate_context_DSSetConstantBuffers,
    qemu_d3d11_immediate_context_DSSetConstantBuffers1,
    qemu_d3d11_immediate_context_DSSetSamplers,
    qemu_d3d11_immediate_context_DSSetShader,
    qemu_d3d11_immediate_context_DSSetShaderResources,
    qemu_d3d11_immediate_context_End,
    qemu_d3d11_immediate_context_ExecuteCommandList,
    qemu_d3d11_immediate_context_FinishCommandList,
    qemu_d3d11_immediate_context_Flush,
    qemu_d3d11_immediate_context_GenerateMips,
    qemu_d3d11_immediate_context_GetContextFlags,
    qemu_d3d11_immediate_context_GetData,
    qemu_d3d11_immediate_context_GetDevice,
    qemu_d3d11_immediate_context_GetPredication,
    qemu_d3d11_immediate_context_GetPrivateData,
    qemu_d3d11_immediate_context_GetResourceMinLOD,
    qemu_d3d11_immediate_context_GetType,
    qemu_d3d11_immediate_context_GSGetConstantBuffers,
    qemu_d3d11_immediate_context_GSGetConstantBuffers1,
    qemu_d3d11_immediate_context_GSGetSamplers,
    qemu_d3d11_immediate_context_GSGetShader,
    qemu_d3d11_immediate_context_GSGetShaderResources,
    qemu_d3d11_immediate_context_GSSetConstantBuffers,
    qemu_d3d11_immediate_context_GSSetConstantBuffers1,
    qemu_d3d11_immediate_context_GSSetSamplers,
    qemu_d3d11_immediate_context_GSSetShader,
    qemu_d3d11_immediate_context_GSSetShaderResources,
    qemu_d3d11_immediate_context_HSGetConstantBuffers,
    qemu_d3d11_immediate_context_HSGetConstantBuffers1,
    qemu_d3d11_immediate_context_HSGetSamplers,
    qemu_d3d11_immediate_context_HSGetShader,
    qemu_d3d11_immediate_context_HSGetShaderResources,
    qemu_d3d11_immediate_context_HSSetConstantBuffers,
    qemu_d3d11_immediate_context_HSSetConstantBuffers1,
    qemu_d3d11_immediate_context_HSSetSamplers,
    qemu_d3d11_immediate_context_HSSetShader,
    qemu_d3d11_immediate_context_HSSetShaderResources,
    qemu_d3d11_immediate_context_IAGetIndexBuffer,
    qemu_d3d11_immediate_context_IAGetInputLayout,
    qemu_d3d11_immediate_context_IAGetPrimitiveTopology,
    qemu_d3d11_immediate_context_IAGetVertexBuffers,
    qemu_d3d11_immediate_context_IASetIndexBuffer,
    qemu_d3d11_immediate_context_IASetInputLayout,
    qemu_d3d11_immediate_context_IASetPrimitiveTopology,
    qemu_d3d11_immediate_context_IASetVertexBuffers,
    qemu_d3d11_immediate_context_Map,
    qemu_d3d11_immediate_context_OMGetBlendState,
    qemu_d3d11_immediate_context_OMGetDepthStencilState,
    qemu_d3d11_immediate_context_OMGetRenderTargets,
    qemu_d3d11_immediate_context_OMGetRenderTargetsAndUnorderedAccessViews,
    qemu_d3d11_immediate_context_OMSetBlendState,
    qemu_d3d11_immediate_context_OMSetDepthStencilState,
    qemu_d3d11_immediate_context_OMSetRenderTargets,
    qemu_d3d11_immediate_context_OMSetRenderTargetsAndUnorderedAccessViews,
    qemu_d3d11_immediate_context_PSGetConstantBuffers,
    qemu_d3d11_immediate_context_PSGetConstantBuffers1,
    qemu_d3d11_immediate_context_PSGetSamplers,
    qemu_d3d11_immediate_context_PSGetShader,
    qemu_d3d11_immediate_context_PSGetShaderResources,
    qemu_d3d11_immediate_context_PSSetConstantBuffers,
    qemu_d3d11_immediate_context_PSSetConstantBuffers1,
    qemu_d3d11_immediate_context_PSSetSamplers,
    qemu_d3d11_immediate_context_PSSetShader,
    qemu_d3d11_immediate_context_PSSetShaderResources,
    qemu_d3d11_immediate_context_QueryInterface,
    qemu_d3d11_immediate_context_Release,
    qemu_d3d11_immediate_context_ResolveSubresource,
    qemu_d3d11_immediate_context_RSGetScissorRects,
    qemu_d3d11_immediate_context_RSGetState,
    qemu_d3d11_immediate_context_RSGetViewports,
    qemu_d3d11_immediate_context_RSSetScissorRects,
    qemu_d3d11_immediate_context_RSSetState,
    qemu_d3d11_immediate_context_RSSetViewports,
    qemu_d3d11_immediate_context_SetPredication,
    qemu_d3d11_immediate_context_SetPrivateData,
    qemu_d3d11_immediate_context_SetPrivateDataInterface,
    qemu_d3d11_immediate_context_SetResourceMinLOD,
    qemu_d3d11_immediate_context_SOGetTargets,
    qemu_d3d11_immediate_context_SOSetTargets,
    qemu_d3d11_immediate_context_SwapDeviceContextState,
    qemu_d3d11_immediate_context_Unmap,
    qemu_d3d11_immediate_context_UpdateSubresource,
    qemu_d3d11_immediate_context_UpdateSubresource1,
    qemu_d3d11_immediate_context_VSGetConstantBuffers,
    qemu_d3d11_immediate_context_VSGetConstantBuffers1,
    qemu_d3d11_immediate_context_VSGetSamplers,
    qemu_d3d11_immediate_context_VSGetShader,
    qemu_d3d11_immediate_context_VSGetShaderResources,
    qemu_d3d11_immediate_context_VSSetConstantBuffers,
    qemu_d3d11_immediate_context_VSSetConstantBuffers1,
    qemu_d3d11_immediate_context_VSSetSamplers,
    qemu_d3d11_immediate_context_VSSetShader,
    qemu_d3d11_immediate_context_VSSetShaderResources,
    qemu_d3d11_pixel_shader_AddRef,
    qemu_d3d11_pixel_shader_GetDevice,
    qemu_d3d11_pixel_shader_GetPrivateData,
    qemu_d3d11_pixel_shader_QueryInterface,
    qemu_d3d11_pixel_shader_Release,
    qemu_d3d11_pixel_shader_SetPrivateData,
    qemu_d3d11_pixel_shader_SetPrivateDataInterface,
    qemu_d3d11_rendertarget_view_AddRef,
    qemu_d3d11_rendertarget_view_GetDesc,
    qemu_d3d11_rendertarget_view_GetDevice,
    qemu_d3d11_rendertarget_view_GetPrivateData,
    qemu_d3d11_rendertarget_view_GetResource,
    qemu_d3d11_rendertarget_view_QueryInterface,
    qemu_d3d11_rendertarget_view_Release,
    qemu_d3d11_rendertarget_view_SetPrivateData,
    qemu_d3d11_rendertarget_view_SetPrivateDataInterface,
    qemu_d3d11_shader_resource_view_AddRef,
    qemu_d3d11_shader_resource_view_GetDesc,
    qemu_d3d11_shader_resource_view_GetDevice,
    qemu_d3d11_shader_resource_view_GetPrivateData,
    qemu_d3d11_shader_resource_view_GetResource,
    qemu_d3d11_shader_resource_view_QueryInterface,
    qemu_d3d11_shader_resource_view_Release,
    qemu_d3d11_shader_resource_view_SetPrivateData,
    qemu_d3d11_shader_resource_view_SetPrivateDataInterface,
    qemu_d3d11_texture1d_AddRef,
    qemu_d3d11_texture1d_GetDesc,
    qemu_d3d11_texture1d_GetDevice,
    qemu_d3d11_texture1d_GetEvictionPriority,
    qemu_d3d11_texture1d_GetPrivateData,
    qemu_d3d11_texture1d_GetType,
    qemu_d3d11_texture1d_QueryInterface,
    qemu_d3d11_texture1d_Release,
    qemu_d3d11_texture1d_SetEvictionPriority,
    qemu_d3d11_texture1d_SetPrivateData,
    qemu_d3d11_texture1d_SetPrivateDataInterface,
    qemu_d3d11_texture2d_AddRef,
    qemu_d3d11_texture2d_GetDesc,
    qemu_d3d11_texture2d_GetDevice,
    qemu_d3d11_texture2d_GetEvictionPriority,
    qemu_d3d11_texture2d_GetPrivateData,
    qemu_d3d11_texture2d_GetType,
    qemu_d3d11_texture2d_QueryInterface,
    qemu_d3d11_texture2d_Release,
    qemu_d3d11_texture2d_SetEvictionPriority,
    qemu_d3d11_texture2d_SetPrivateData,
    qemu_d3d11_texture2d_SetPrivateDataInterface,
    qemu_d3d11_texture3d_AddRef,
    qemu_d3d11_texture3d_GetDesc,
    qemu_d3d11_texture3d_GetDevice,
    qemu_d3d11_texture3d_GetEvictionPriority,
    qemu_d3d11_texture3d_GetPrivateData,
    qemu_d3d11_texture3d_GetType,
    qemu_d3d11_texture3d_QueryInterface,
    qemu_d3d11_texture3d_Release,
    qemu_d3d11_texture3d_SetEvictionPriority,
    qemu_d3d11_texture3d_SetPrivateData,
    qemu_d3d11_texture3d_SetPrivateDataInterface,
    qemu_d3d11_unordered_access_view_AddRef,
    qemu_d3d11_unordered_access_view_GetDesc,
    qemu_d3d11_unordered_access_view_GetDevice,
    qemu_d3d11_unordered_access_view_GetPrivateData,
    qemu_d3d11_unordered_access_view_GetResource,
    qemu_d3d11_unordered_access_view_QueryInterface,
    qemu_d3d11_unordered_access_view_Release,
    qemu_d3d11_unordered_access_view_SetPrivateData,
    qemu_d3d11_unordered_access_view_SetPrivateDataInterface,
    qemu_d3d11_vertex_shader_AddRef,
    qemu_d3d11_vertex_shader_GetDevice,
    qemu_d3d11_vertex_shader_GetPrivateData,
    qemu_d3d11_vertex_shader_QueryInterface,
    qemu_d3d11_vertex_shader_Release,
    qemu_d3d11_vertex_shader_SetPrivateData,
    qemu_d3d11_vertex_shader_SetPrivateDataInterface,
    qemu_d3d_device_inner_AddRef,
    qemu_d3d_device_inner_QueryInterface,
    qemu_d3d_device_inner_Release,
    qemu_init_dll,
    qemu_layer_create,
    qemu_layer_get_size,
    qemu_wrap_implicit_surface,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side d3d11 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
