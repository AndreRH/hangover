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
#include <d3d11_1.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <dxgi1_2.h>
#include <debug.h>
#else
#include <dxgi1_5.h>
#include <wine/debug.h>
#endif

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
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DXGID3D10CreateDevice(HMODULE d3d10core, IDXGIFactory *factory, IDXGIAdapter *adapter,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, void **device)
{
    struct qemu_DXGID3D10CreateDevice call;
    struct qemu_dxgi_device *obj;
    struct qemu_dxgi_adapter *adapter_impl;
    struct qemu_dxgi_factory *factory_impl;

    /* FIXME: Register the d3d10 layer and fetch the proper layer size */

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGID3D10CREATEDEVICE);
    call.d3d10core = (ULONG_PTR)d3d10core;
    call.factory = (ULONG_PTR)factory_impl;
    call.adapter = (ULONG_PTR)adapter_impl;
    call.flags = flags;
    call.feature_levels = (ULONG_PTR)feature_levels;
    call.level_count = level_count;
    call.layer_size = 0;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        *device = NULL;
        return call.super.iret;
    }

    obj = (struct qemu_dxgi_device *)(ULONG_PTR)call.device;
    qemu_dxgi_device_guest_init(obj);

    /* FIXME: Call layer init and store the inner unknown. */
}

#else

void qemu_DXGID3D10CreateDevice(struct qemu_syscall *call)
{
    struct qemu_DXGID3D10CreateDevice *c = (struct qemu_DXGID3D10CreateDevice *)call;
    struct qemu_dxgi_device *obj;
    struct qemu_dxgi_adapter *adapter;
    struct qemu_dxgi_factory *factory;
    HMODULE mod;

    WINE_FIXME("Unfinished!\n");
    factory = QEMU_G2H(c->factory);
    adapter = QEMU_G2H(c->adapter);
    mod = qemu_ops->qemu_module_g2h(c->d3d10core);

    c->super.iret = qemu_dxgi_device_create(mod, adapter, factory, c->flags, QEMU_G2H(c->feature_levels),
            c->level_count, c->layer_size, &obj);
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
    qemu_dxgi_adapter_AddRef,
    qemu_dxgi_adapter_CheckInterfaceSupport,
    qemu_dxgi_adapter_EnumOutputs,
    qemu_dxgi_adapter_GetDesc,
    qemu_dxgi_adapter_GetDesc1,
    qemu_dxgi_adapter_GetDesc2,
    qemu_dxgi_adapter_GetParent,
    qemu_dxgi_adapter_GetPrivateData,
    qemu_dxgi_adapter_QueryInterface,
    qemu_dxgi_adapter_QueryVideoMemoryInfo,
    qemu_dxgi_adapter_RegisterHardwareContentProtectionTeardownStatusEvent,
    qemu_dxgi_adapter_RegisterVideoMemoryBudgetChangeNotificationEvent,
    qemu_dxgi_adapter_Release,
    qemu_dxgi_adapter_SetPrivateData,
    qemu_dxgi_adapter_SetPrivateDataInterface,
    qemu_dxgi_adapter_SetVideoMemoryReservation,
    qemu_dxgi_adapter_UnregisterHardwareContentProtectionTeardownStatus,
    qemu_dxgi_adapter_UnregisterVideoMemoryBudgetChangeNotification,
    qemu_dxgi_device_AddRef,
    qemu_dxgi_device_CreateSurface,
    qemu_dxgi_device_EnqueueSetEvent,
    qemu_dxgi_device_GetAdapter,
    qemu_dxgi_device_GetGPUThreadPriority,
    qemu_dxgi_device_GetMaximumFrameLatency,
    qemu_dxgi_device_GetParent,
    qemu_dxgi_device_GetPrivateData,
    qemu_dxgi_device_OfferResources,
    qemu_dxgi_device_QueryInterface,
    qemu_dxgi_device_QueryResourceResidency,
    qemu_dxgi_device_ReclaimResources,
    qemu_dxgi_device_Release,
    qemu_dxgi_device_SetGPUThreadPriority,
    qemu_dxgi_device_SetMaximumFrameLatency,
    qemu_dxgi_device_SetPrivateData,
    qemu_dxgi_device_SetPrivateDataInterface,
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
    qemu_dxgi_factory_GetPrivateData,
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
    qemu_dxgi_factory_SetPrivateData,
    qemu_dxgi_factory_SetPrivateDataInterface,
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
    qemu_dxgi_output_GetPrivateData,
    qemu_dxgi_output_QueryInterface,
    qemu_dxgi_output_Release,
    qemu_dxgi_output_ReleaseOwnership,
    qemu_dxgi_output_SetDisplaySurface,
    qemu_dxgi_output_SetGammaControl,
    qemu_dxgi_output_SetPrivateData,
    qemu_dxgi_output_SetPrivateDataInterface,
    qemu_dxgi_output_SupportsOverlays,
    qemu_dxgi_output_TakeOwnership,
    qemu_dxgi_output_WaitForVBlank,
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
