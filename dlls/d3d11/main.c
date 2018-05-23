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

    WINE_FIXME("id %#x, layer_base %p, unknown0 %#x, device_object %p, riid %s, device_layer %p\n",
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

static void qemu_layer_create(struct qemu_syscall *call)
{
    struct qemu_layer_create *c = (struct qemu_layer_create *)call;
    struct qemu_d3d11_device *device;
    IUnknown *host_device;
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
    qemu_d3d10_device_AddRef,
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
    qemu_d3d10_device_CreateBuffer,
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
    qemu_d3d10_device_CreateTexture1D,
    qemu_d3d10_device_CreateTexture2D,
    qemu_d3d10_device_CreateTexture3D,
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
    qemu_d3d10_device_QueryInterface,
    qemu_d3d10_device_Release,
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
    qemu_d3d10_multithread_AddRef,
    qemu_d3d10_multithread_Enter,
    qemu_d3d10_multithread_GetMultithreadProtected,
    qemu_d3d10_multithread_Leave,
    qemu_d3d10_multithread_QueryInterface,
    qemu_d3d10_multithread_Release,
    qemu_d3d10_multithread_SetMultithreadProtected,
    qemu_d3d11_device_AddRef,
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
    qemu_d3d11_device_QueryInterface,
    qemu_d3d11_device_Release,
    qemu_d3d11_device_SetExceptionMode,
    qemu_d3d11_device_SetPrivateData,
    qemu_d3d11_device_SetPrivateDataInterface,
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
    qemu_D3D11CreateDevice,
    qemu_D3D11CreateDeviceAndSwapChain,
    qemu_d3d_device_inner_AddRef,
    qemu_d3d_device_inner_QueryInterface,
    qemu_d3d_device_inner_Release,
    qemu_init_dll,
    qemu_layer_create,
    qemu_layer_get_size,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side d3d11 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
