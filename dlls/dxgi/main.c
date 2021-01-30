/*
 * Copyright 2008 Henri Verbeet for CodeWeavers
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
#define COBJMACROS

#include <windows.h>
#include <stdio.h>
#include <d3d11_1.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#include <dxgi1_5.h>
#include <wine/debug.h>

#include <initguid.h>
#include "qemudxgi.h"

#include "qemu_dxgi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_CreateDXGIFactory
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t iid;
    uint64_t version;
    uint64_t factory;
};

#ifdef QEMU_DLL_GUEST

static HRESULT factory_create(DWORD flags, const IID *iid, DWORD version, void **factory)
{
    struct qemu_CreateDXGIFactory call;
    struct qemu_dxgi_factory *obj;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDXGIFACTORY);
    call.flags = flags;
    call.version = version;
    call.iid = (ULONG_PTR)iid;
    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_dxgi_factory *)(ULONG_PTR)call.factory;
    qemu_dxgi_factory_guest_init(obj);

    hr = IDXGIFactory_QueryInterface(&obj->IDXGIFactory5_iface, iid, factory);
    IDXGIFactory_Release(&obj->IDXGIFactory5_iface);
    return hr;
}

WINBASEAPI HRESULT WINAPI CreateDXGIFactory(REFIID iid, void **factory)
{
    return factory_create(0, iid, 0, factory);
}

WINBASEAPI HRESULT WINAPI CreateDXGIFactory1(REFIID iid, void **factory)
{
    return factory_create(0, iid, 1, factory);
}

WINBASEAPI HRESULT WINAPI CreateDXGIFactory2(UINT flags, REFIID iid, void **factory)
{
    return factory_create(flags, iid, 2, factory);
}

#else

void qemu_CreateDXGIFactory(struct qemu_syscall *call)
{
    struct qemu_CreateDXGIFactory *c = (struct qemu_CreateDXGIFactory *)call;
    struct qemu_dxgi_factory *factory;

    WINE_TRACE("\n");
    c->super.iret = qemu_dxgi_factory_create(c->flags, c->version, &factory);
    c->factory = QEMU_H2G(factory);
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
    uint64_t layer_size;
    uint64_t device;
    uint64_t host_device;
    uint64_t dxgi_size;
};

#ifdef QEMU_DLL_GUEST

struct dxgi_main
{
    HMODULE d3d10core;
    struct dxgi_device_layer *device_layers;
    UINT layer_count;
};
static struct dxgi_main dxgi_main;

static void dxgi_main_cleanup(void)
{
    HeapFree(GetProcessHeap(), 0, dxgi_main.device_layers);
    FreeLibrary(dxgi_main.d3d10core);
}

void wined3d_mutex_lock() {} /* FIXME */
void wined3d_mutex_unlock() {} /* FIXME */

static BOOL get_layer(enum dxgi_device_layer_id id, struct dxgi_device_layer *layer)
{
    UINT i;

    wined3d_mutex_lock();

    for (i = 0; i < dxgi_main.layer_count; ++i)
    {
        if (dxgi_main.device_layers[i].id == id)
        {
            *layer = dxgi_main.device_layers[i];
            wined3d_mutex_unlock();
            return TRUE;
        }
    }

    wined3d_mutex_unlock();
    return FALSE;
}

static HRESULT register_d3d10core_layers(HMODULE d3d10core)
{
    wined3d_mutex_lock();

    if (!dxgi_main.d3d10core)
    {
        HRESULT hr;
        HRESULT (WINAPI *d3d11core_register_layers)(void);
        HMODULE mod;
        BOOL ret;

        if (!(ret = GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (const char *)d3d10core, &mod)))
        {
            wined3d_mutex_unlock();
            return E_FAIL;
        }

        d3d11core_register_layers = (void *)GetProcAddress(mod, "D3D11CoreRegisterLayers");
        hr = d3d11core_register_layers();
        if (FAILED(hr))
        {
            WINE_ERR("Failed to register d3d11 layers, returning %#x.\n", hr);
            FreeLibrary(mod);
            wined3d_mutex_unlock();
            return hr;
        }

        dxgi_main.d3d10core = mod;
    }

    wined3d_mutex_unlock();

    return S_OK;
}

WINBASEAPI HRESULT WINAPI DXGID3D10CreateDevice(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device)
{
    struct qemu_DXGID3D10CreateDevice call;
    struct qemu_dxgi_device *obj;
    struct qemu_dxgi_adapter *adapter_impl = unsafe_impl_from_IDXGIAdapter(adapter);
    struct qemu_dxgi_factory *factory_impl = unsafe_impl_from_IDXGIFactory(factory);
    struct dxgi_device_layer d3d10_layer;
    struct layer_get_size_args get_size_args;
    void *layer_base;
    HRESULT hr;
    DWORD count;

    hr = register_d3d10core_layers(d3d10core);
    if (FAILED(hr))
    {
        WINE_ERR("Failed to register d3d10core layers, returning %#x.\n", hr);
        return hr;
    }

    if (!get_layer(DXGI_DEVICE_LAYER_D3D10_DEVICE, &d3d10_layer))
    {
        WINE_ERR("Failed to get D3D10 device layer.\n");
        return E_FAIL;
    }

    count = 0;
    hr = d3d10_layer.init(d3d10_layer.id, &count, NULL);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to initialize D3D10 device layer.\n");
        return E_FAIL;
    }

    get_size_args.unknown0 = 0;
    get_size_args.unknown1 = 0;
    get_size_args.unknown2 = NULL;
    get_size_args.unknown3 = NULL;
    get_size_args.adapter = adapter;
    get_size_args.interface_major = 10;
    get_size_args.interface_minor = 1;
    get_size_args.version_build = 4;
    get_size_args.version_revision = 6000;

    call.layer_size = d3d10_layer.get_size(d3d10_layer.id, &get_size_args, 0);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGID3D10CREATEDEVICE);
    call.d3d10core = (ULONG_PTR)d3d10core;
    call.factory = (ULONG_PTR)factory_impl;
    call.adapter = (ULONG_PTR)adapter_impl;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.level_count = level_count;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        *device = NULL;
        return call.super.iret;
    }

    obj = (struct qemu_dxgi_device *)(ULONG_PTR)call.device;
    *device = &obj->IDXGIDevice2_iface;
    qemu_dxgi_device_guest_init(obj);

    layer_base = ((BYTE *)obj) + call.dxgi_size;
    if (FAILED(hr = d3d10_layer.create(d3d10_layer.id, &layer_base, 0,
            *device, &IID_IUnknown, (void **)&obj->child_layer, call.host_device)))
    {
        /* TODO: This leaks... */
        WINE_FIXME("Failed to create device, returning %#x.\n", hr);
        *device = NULL;
        return hr;
    }

    d3d10_layer.set_feature_level(d3d10_layer.id, obj->child_layer, 0); /* Should not be necessary */
}

#else

void qemu_DXGID3D10CreateDevice(struct qemu_syscall *call)
{
    struct qemu_DXGID3D10CreateDevice *c = (struct qemu_DXGID3D10CreateDevice *)call;
    struct qemu_dxgi_device *obj;
    struct qemu_dxgi_adapter *adapter;
    struct qemu_dxgi_factory *factory;
    HMODULE mod;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->factory);
    adapter = QEMU_G2H(c->adapter);
    mod = qemu_ops->qemu_module_g2h(c->d3d10core);

    c->super.iret = qemu_dxgi_device_create(mod, adapter, factory, c->flags, QEMU_G2H(c->feature_levels),
            c->level_count, c->layer_size, &obj);
    c->device = QEMU_H2G(obj);
    c->host_device = QEMU_H2G(obj->host);
    c->dxgi_size = sizeof(*obj);
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DXGID3D10RegisterLayers(const struct dxgi_device_layer *layers, UINT layer_count)
{
    UINT i;
    struct dxgi_device_layer *new_layers;

    WINE_TRACE("layers %p, layer_count %u\n", layers, layer_count);

    wined3d_mutex_lock();

    if (!dxgi_main.layer_count)
        new_layers = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, layer_count * sizeof(*new_layers));
    else
        new_layers = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dxgi_main.device_layers,
                (dxgi_main.layer_count + layer_count) * sizeof(*new_layers));

    if (!new_layers)
    {
        wined3d_mutex_unlock();
        WINE_ERR("Failed to allocate layer memory\n");
        return E_OUTOFMEMORY;
    }

    for (i = 0; i < layer_count; ++i)
    {
        const struct dxgi_device_layer *layer = &layers[i];

        WINE_TRACE("layer %d: id %#x, init %p, get_size %p, create %p\n",
                i, layer->id, layer->init, layer->get_size, layer->create);

        new_layers[dxgi_main.layer_count + i] = *layer;
    }

    dxgi_main.device_layers = new_layers;
    dxgi_main.layer_count += layer_count;

    wined3d_mutex_unlock();

    return S_OK;
}

#endif

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t dxgi_factory_guest_destroy;
    uint64_t dxgi_adapter_guest_destroy;
    uint64_t dxgi_output_guest_destroy;
    uint64_t dxgi_device_guest_destroy;
    uint64_t dxgi_surface_guest_destroy;
    uint64_t dxgi_swapchain_guest_destroy;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.dxgi_factory_guest_destroy = (ULONG_PTR)dxgi_factory_guest_destroy;
        call.dxgi_adapter_guest_destroy = (ULONG_PTR)dxgi_adapter_guest_destroy;
        call.dxgi_output_guest_destroy = (ULONG_PTR)dxgi_output_guest_destroy;
        call.dxgi_device_guest_destroy = (ULONG_PTR)dxgi_device_guest_destroy;
        call.dxgi_surface_guest_destroy = (ULONG_PTR)dxgi_surface_guest_destroy;
        call.dxgi_swapchain_guest_destroy = (ULONG_PTR)dxgi_swapchain_guest_destroy;

        qemu_syscall(&call.super);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        if (!reserved)
            dxgi_main_cleanup();
    }

    return TRUE;
}

HRESULT dxgi_get_private_data(struct wined3d_private_store *store,
        REFGUID guid, UINT *data_size, void *data)
{
    const struct wined3d_private_data *stored_data;
    DWORD size_in;
    HRESULT hr;

    if (!data_size)
        return E_INVALIDARG;

    wined3d_mutex_lock();
    if (!(stored_data = wined3d_private_store_get_private_data(store, guid)))
    {
        hr = DXGI_ERROR_NOT_FOUND;
        *data_size = 0;
        goto done;
    }

    size_in = *data_size;
    *data_size = stored_data->size;
    if (!data)
    {
        hr = S_OK;
        goto done;
    }
    if (size_in < stored_data->size)
    {
        hr = DXGI_ERROR_MORE_DATA;
        goto done;
    }

    if (stored_data->flags & WINED3DSPD_IUNKNOWN)
        IUnknown_AddRef(stored_data->content.object);
    memcpy(data, stored_data->content.data, stored_data->size);
    hr = S_OK;

done:
    wined3d_mutex_unlock();

    return hr;
}

HRESULT dxgi_set_private_data(struct wined3d_private_store *store,
        REFGUID guid, UINT data_size, const void *data)
{
    struct wined3d_private_data *entry;
    HRESULT hr;

    if (!data)
    {
        wined3d_mutex_lock();
        if (!(entry = wined3d_private_store_get_private_data(store, guid)))
        {
            wined3d_mutex_unlock();
            return S_FALSE;
        }

        wined3d_private_store_free_private_data(store, entry);
        wined3d_mutex_unlock();

        return S_OK;
    }

    wined3d_mutex_lock();
    hr = wined3d_private_store_set_private_data(store, guid, data, data_size, 0);
    wined3d_mutex_unlock();

    return hr;
}

HRESULT dxgi_set_private_data_interface(struct wined3d_private_store *store,
        REFGUID guid, const IUnknown *object)
{
    HRESULT hr;

    if (!object)
        return dxgi_set_private_data(store, guid, sizeof(object), &object);

    wined3d_mutex_lock();
    hr = wined3d_private_store_set_private_data(store,
            guid, object, sizeof(object), WINED3DSPD_IUNKNOWN);
    wined3d_mutex_unlock();

    return hr;
}

#else

uint64_t dxgi_factory_guest_destroy;
uint64_t dxgi_adapter_guest_destroy;
uint64_t dxgi_output_guest_destroy;
uint64_t dxgi_device_guest_destroy;
uint64_t dxgi_surface_guest_destroy;
uint64_t dxgi_swapchain_guest_destroy;

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;

    dxgi_factory_guest_destroy = c->dxgi_factory_guest_destroy;
    dxgi_adapter_guest_destroy = c->dxgi_adapter_guest_destroy;
    dxgi_output_guest_destroy = c->dxgi_output_guest_destroy;
    dxgi_device_guest_destroy = c->dxgi_device_guest_destroy;
    dxgi_surface_guest_destroy = c->dxgi_surface_guest_destroy;
    dxgi_swapchain_guest_destroy = c->dxgi_swapchain_guest_destroy;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CreateDXGIFactory,
    qemu_dxgi_adapter_AddRef,
    qemu_dxgi_adapter_CheckInterfaceSupport,
    qemu_dxgi_adapter_EnumOutputs,
    qemu_dxgi_adapter_GetDesc,
    qemu_dxgi_adapter_GetDesc1,
    qemu_dxgi_adapter_GetDesc2,
    qemu_dxgi_adapter_GetParent,
    qemu_dxgi_adapter_QueryInterface,
    qemu_dxgi_adapter_QueryVideoMemoryInfo,
    qemu_dxgi_adapter_RegisterHardwareContentProtectionTeardownStatusEvent,
    qemu_dxgi_adapter_RegisterVideoMemoryBudgetChangeNotificationEvent,
    qemu_dxgi_adapter_Release,
    qemu_dxgi_adapter_SetVideoMemoryReservation,
    qemu_dxgi_adapter_UnregisterHardwareContentProtectionTeardownStatus,
    qemu_dxgi_adapter_UnregisterVideoMemoryBudgetChangeNotification,
    qemu_dxgi_device_AddRef,
    qemu_dxgi_device_EnqueueSetEvent,
    qemu_dxgi_device_GetAdapter,
    qemu_dxgi_device_GetGPUThreadPriority,
    qemu_dxgi_device_GetMaximumFrameLatency,
    qemu_dxgi_device_GetParent,
    qemu_dxgi_device_OfferResources,
    qemu_dxgi_device_QueryInterface,
    qemu_dxgi_device_QueryResourceResidency,
    qemu_dxgi_device_ReclaimResources,
    qemu_dxgi_device_Release,
    qemu_dxgi_device_SetGPUThreadPriority,
    qemu_dxgi_device_SetMaximumFrameLatency,
    qemu_dxgi_factory_AddRef,
    qemu_dxgi_factory_CheckFeatureSupport,
    qemu_dxgi_factory_CreateSoftwareAdapter,
    qemu_dxgi_factory_CreateSwapChain,
    qemu_dxgi_factory_CreateSwapChainForComposition,
    qemu_dxgi_factory_CreateSwapChainForCoreWindow,
    qemu_dxgi_factory_CreateSwapChainForHwnd,
    qemu_dxgi_factory_EnumAdapterByLuid,
    qemu_dxgi_factory_EnumAdapters,
    qemu_dxgi_factory_EnumWarpAdapter,
    qemu_dxgi_factory_GetCreationFlags,
    qemu_dxgi_factory_GetParent,
    qemu_dxgi_factory_GetSharedResourceAdapterLuid,
    qemu_dxgi_factory_GetWindowAssociation,
    qemu_dxgi_factory_IsCurrent,
    qemu_dxgi_factory_IsWindowedStereoEnabled,
    qemu_dxgi_factory_MakeWindowAssociation,
    qemu_dxgi_factory_QueryInterface,
    qemu_dxgi_factory_RegisterOcclusionStatusEvent,
    qemu_dxgi_factory_RegisterOcclusionStatusWindow,
    qemu_dxgi_factory_RegisterStereoStatusEvent,
    qemu_dxgi_factory_RegisterStereoStatusWindow,
    qemu_dxgi_factory_Release,
    qemu_dxgi_factory_UnregisterOcclusionStatus,
    qemu_dxgi_factory_UnregisterStereoStatus,
    qemu_dxgi_output_AddRef,
    qemu_dxgi_output_CheckOverlayColorSpaceSupport,
    qemu_dxgi_output_CheckOverlaySupport,
    qemu_dxgi_output_DuplicateOutput,
    qemu_dxgi_output_FindClosestMatchingMode,
    qemu_dxgi_output_FindClosestMatchingMode1,
    qemu_dxgi_output_GetDesc,
    qemu_dxgi_output_GetDisplayModeList,
    qemu_dxgi_output_GetDisplayModeList1,
    qemu_dxgi_output_GetDisplaySurfaceData,
    qemu_dxgi_output_GetDisplaySurfaceData1,
    qemu_dxgi_output_GetFrameStatistics,
    qemu_dxgi_output_GetGammaControl,
    qemu_dxgi_output_GetGammaControlCapabilities,
    qemu_dxgi_output_GetParent,
    qemu_dxgi_output_QueryInterface,
    qemu_dxgi_output_Release,
    qemu_dxgi_output_ReleaseOwnership,
    qemu_dxgi_output_SetDisplaySurface,
    qemu_dxgi_output_SetGammaControl,
    qemu_dxgi_output_SupportsOverlays,
    qemu_dxgi_output_TakeOwnership,
    qemu_dxgi_output_WaitForVBlank,
    qemu_dxgi_surface_GetDC,
    qemu_dxgi_surface_GetDesc,
    qemu_dxgi_surface_GetDevice,
    qemu_dxgi_surface_GetParent,
    qemu_dxgi_surface_inner_AddRef,
    qemu_dxgi_surface_inner_QueryInterface,
    qemu_dxgi_surface_inner_Release,
    qemu_dxgi_surface_Map,
    qemu_dxgi_surface_ReleaseDC,
    qemu_dxgi_surface_Unmap,
    qemu_dxgi_swapchain_AddRef,
    qemu_dxgi_swapchain_GetBackgroundColor,
    qemu_dxgi_swapchain_GetBuffer,
    qemu_dxgi_swapchain_GetContainingOutput,
    qemu_dxgi_swapchain_GetCoreWindow,
    qemu_dxgi_swapchain_GetDesc,
    qemu_dxgi_swapchain_GetDesc1,
    qemu_dxgi_swapchain_GetDevice,
    qemu_dxgi_swapchain_GetFrameStatistics,
    qemu_dxgi_swapchain_GetFullscreenDesc,
    qemu_dxgi_swapchain_GetFullscreenState,
    qemu_dxgi_swapchain_GetHwnd,
    qemu_dxgi_swapchain_GetLastPresentCount,
    qemu_dxgi_swapchain_GetParent,
    qemu_dxgi_swapchain_GetRestrictToOutput,
    qemu_dxgi_swapchain_GetRotation,
    qemu_dxgi_swapchain_IsTemporaryMonoSupported,
    qemu_dxgi_swapchain_Present,
    qemu_dxgi_swapchain_Present1,
    qemu_dxgi_swapchain_QueryInterface,
    qemu_dxgi_swapchain_Release,
    qemu_dxgi_swapchain_ResizeBuffers,
    qemu_dxgi_swapchain_ResizeTarget,
    qemu_dxgi_swapchain_SetBackgroundColor,
    qemu_dxgi_swapchain_SetFullscreenState,
    qemu_dxgi_swapchain_SetRotation,
    qemu_DXGID3D10CreateDevice,
    qemu_init_dll,
    qemu_dxgi_device_create_surface,
};

HRESULT (WINAPI *pCreateDXGIFactory)(REFIID iid, void **factory);
HRESULT (WINAPI *pCreateDXGIFactory1)(REFIID iid, void **factory);
HRESULT (WINAPI *pCreateDXGIFactory2)(UINT flags, REFIID iid, void **factory);
HRESULT (WINAPI *pDXGID3D10CreateDevice)(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device);


const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE dxgi;
    WINE_TRACE("Loading host-side dxgi wrapper.\n");

    dxgi = LoadLibraryA("dxgi.dll");
    if (!dxgi)
    {
        WINE_FIXME("Failed to load host dxgi.dll\n");
        return NULL;
    }

    pCreateDXGIFactory = (void *)GetProcAddress(dxgi, "CreateDXGIFactory");
    if (!pCreateDXGIFactory)
        WINE_ERR("Cannot find CreateDXGIFactory in dxgi.dll.\n");
    pCreateDXGIFactory1 = (void *)GetProcAddress(dxgi, "CreateDXGIFactory1");
    if (!pCreateDXGIFactory1)
        WINE_ERR("Cannot find CreateDXGIFactory1 in dxgi.dll.\n");
    pCreateDXGIFactory2 = (void *)GetProcAddress(dxgi, "CreateDXGIFactory2");
    if (!pCreateDXGIFactory2)
        WINE_ERR("Cannot find CreateDXGIFactory2 in dxgi.dll.\n");
    pDXGID3D10CreateDevice = (void *)GetProcAddress(dxgi, "DXGID3D10CreateDevice");
    if (!pDXGID3D10CreateDevice)
        WINE_ERR("Cannot find DXGID3D10CreateDevice in dxgi.dll.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
