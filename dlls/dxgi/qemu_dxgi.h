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

#ifndef QEMU_DXGI_H
#define QEMU_DXGI_H

enum dxgi_calls
{
    CALL_CREATEDXGIFACTORY = 0,
    CALL_DXGI_ADAPTER_ADDREF,
    CALL_DXGI_ADAPTER_CHECKINTERFACESUPPORT,
    CALL_DXGI_ADAPTER_ENUMOUTPUTS,
    CALL_DXGI_ADAPTER_GETDESC,
    CALL_DXGI_ADAPTER_GETDESC1,
    CALL_DXGI_ADAPTER_GETDESC2,
    CALL_DXGI_ADAPTER_GETPARENT,
    CALL_DXGI_ADAPTER_GETPRIVATEDATA,
    CALL_DXGI_ADAPTER_QUERYINTERFACE,
    CALL_DXGI_ADAPTER_QUERYVIDEOMEMORYINFO,
    CALL_DXGI_ADAPTER_REGISTERHARDWARECONTENTPROTECTIONTEARDOWNSTATUSEVENT,
    CALL_DXGI_ADAPTER_REGISTERVIDEOMEMORYBUDGETCHANGENOTIFICATIONEVENT,
    CALL_DXGI_ADAPTER_RELEASE,
    CALL_DXGI_ADAPTER_SETPRIVATEDATA,
    CALL_DXGI_ADAPTER_SETPRIVATEDATAINTERFACE,
    CALL_DXGI_ADAPTER_SETVIDEOMEMORYRESERVATION,
    CALL_DXGI_ADAPTER_UNREGISTERHARDWARECONTENTPROTECTIONTEARDOWNSTATUS,
    CALL_DXGI_ADAPTER_UNREGISTERVIDEOMEMORYBUDGETCHANGENOTIFICATION,
    CALL_DXGI_DEVICE_ADDREF,
    CALL_DXGI_DEVICE_CREATESURFACE,
    CALL_DXGI_DEVICE_ENQUEUESETEVENT,
    CALL_DXGI_DEVICE_GETADAPTER,
    CALL_DXGI_DEVICE_GETGPUTHREADPRIORITY,
    CALL_DXGI_DEVICE_GETMAXIMUMFRAMELATENCY,
    CALL_DXGI_DEVICE_GETPARENT,
    CALL_DXGI_DEVICE_GETPRIVATEDATA,
    CALL_DXGI_DEVICE_OFFERRESOURCES,
    CALL_DXGI_DEVICE_QUERYINTERFACE,
    CALL_DXGI_DEVICE_QUERYRESOURCERESIDENCY,
    CALL_DXGI_DEVICE_RECLAIMRESOURCES,
    CALL_DXGI_DEVICE_RELEASE,
    CALL_DXGI_DEVICE_SETGPUTHREADPRIORITY,
    CALL_DXGI_DEVICE_SETMAXIMUMFRAMELATENCY,
    CALL_DXGI_DEVICE_SETPRIVATEDATA,
    CALL_DXGI_DEVICE_SETPRIVATEDATAINTERFACE,
    CALL_DXGI_FACTORY_ADDREF,
    CALL_DXGI_FACTORY_CHECKFEATURESUPPORT,
    CALL_DXGI_FACTORY_CREATESOFTWAREADAPTER,
    CALL_DXGI_FACTORY_CREATESWAPCHAIN,
    CALL_DXGI_FACTORY_CREATESWAPCHAINFORCOMPOSITION,
    CALL_DXGI_FACTORY_CREATESWAPCHAINFORCOREWINDOW,
    CALL_DXGI_FACTORY_CREATESWAPCHAINFORHWND,
    CALL_DXGI_FACTORY_ENUMADAPTERBYLUID,
    CALL_DXGI_FACTORY_ENUMADAPTERS,
    CALL_DXGI_FACTORY_ENUMWARPADAPTER,
    CALL_DXGI_FACTORY_GETCREATIONFLAGS,
    CALL_DXGI_FACTORY_GETPARENT,
    CALL_DXGI_FACTORY_GETPRIVATEDATA,
    CALL_DXGI_FACTORY_GETSHAREDRESOURCEADAPTERLUID,
    CALL_DXGI_FACTORY_GETWINDOWASSOCIATION,
    CALL_DXGI_FACTORY_ISCURRENT,
    CALL_DXGI_FACTORY_ISWINDOWEDSTEREOENABLED,
    CALL_DXGI_FACTORY_MAKEWINDOWASSOCIATION,
    CALL_DXGI_FACTORY_QUERYINTERFACE,
    CALL_DXGI_FACTORY_REGISTEROCCLUSIONSTATUSEVENT,
    CALL_DXGI_FACTORY_REGISTEROCCLUSIONSTATUSWINDOW,
    CALL_DXGI_FACTORY_REGISTERSTEREOSTATUSEVENT,
    CALL_DXGI_FACTORY_REGISTERSTEREOSTATUSWINDOW,
    CALL_DXGI_FACTORY_RELEASE,
    CALL_DXGI_FACTORY_SETPRIVATEDATA,
    CALL_DXGI_FACTORY_SETPRIVATEDATAINTERFACE,
    CALL_DXGI_FACTORY_UNREGISTEROCCLUSIONSTATUS,
    CALL_DXGI_FACTORY_UNREGISTERSTEREOSTATUS,
    CALL_DXGI_OUTPUT_ADDREF,
    CALL_DXGI_OUTPUT_CHECKOVERLAYCOLORSPACESUPPORT,
    CALL_DXGI_OUTPUT_CHECKOVERLAYSUPPORT,
    CALL_DXGI_OUTPUT_DUPLICATEOUTPUT,
    CALL_DXGI_OUTPUT_FINDCLOSESTMATCHINGMODE,
    CALL_DXGI_OUTPUT_FINDCLOSESTMATCHINGMODE1,
    CALL_DXGI_OUTPUT_GETDESC,
    CALL_DXGI_OUTPUT_GETDISPLAYMODELIST,
    CALL_DXGI_OUTPUT_GETDISPLAYMODELIST1,
    CALL_DXGI_OUTPUT_GETDISPLAYSURFACEDATA,
    CALL_DXGI_OUTPUT_GETDISPLAYSURFACEDATA1,
    CALL_DXGI_OUTPUT_GETFRAMESTATISTICS,
    CALL_DXGI_OUTPUT_GETGAMMACONTROL,
    CALL_DXGI_OUTPUT_GETGAMMACONTROLCAPABILITIES,
    CALL_DXGI_OUTPUT_GETPARENT,
    CALL_DXGI_OUTPUT_GETPRIVATEDATA,
    CALL_DXGI_OUTPUT_QUERYINTERFACE,
    CALL_DXGI_OUTPUT_RELEASE,
    CALL_DXGI_OUTPUT_RELEASEOWNERSHIP,
    CALL_DXGI_OUTPUT_SETDISPLAYSURFACE,
    CALL_DXGI_OUTPUT_SETGAMMACONTROL,
    CALL_DXGI_OUTPUT_SETPRIVATEDATA,
    CALL_DXGI_OUTPUT_SETPRIVATEDATAINTERFACE,
    CALL_DXGI_OUTPUT_SUPPORTSOVERLAYS,
    CALL_DXGI_OUTPUT_TAKEOWNERSHIP,
    CALL_DXGI_OUTPUT_WAITFORVBLANK,
    CALL_DXGID3D10CREATEDEVICE,
    CALL_DXGID3D10REGISTERLAYERS,
    CALL_INIT_DLL,
};

#ifdef QEMU_DLL_GUEST

/* Hacks for missing dxgi1_5 headers in mingw. */
typedef IDXGIFactory2 IDXGIFactory5;
typedef IDXGIAdapter2 IDXGIAdapter3;
typedef IDXGIOutput IDXGIOutput4;
typedef enum DXGI_FEATURE
{
    DXGI_FEATURE_PRESENT_ALLOW_TEARING = 0x0
} DXGI_FEATURE;
typedef void DXGI_QUERY_VIDEO_MEMORY_INFO;
typedef enum DXGI_MEMORY_SEGMENT_GROUP {
    DXGI_MEMORY_SEGMENT_GROUP_LOCAL = 0x0,
    DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 0x1
} DXGI_MEMORY_SEGMENT_GROUP;
typedef void DXGI_MODE_DESC1;
typedef enum DXGI_COLOR_SPACE_TYPE
{
    DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709             = 0x00,
    DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709             = 0x01,
    DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709           = 0x02,
    DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020          = 0x03,
    DXGI_COLOR_SPACE_RESERVED                           = 0x04,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601      = 0x05,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601         = 0x06,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601           = 0x07,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709         = 0x08,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709           = 0x09,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020        = 0x0a,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020          = 0x0b,
    DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020          = 0x0c,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020      = 0x0d,
    DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020        = 0x0e,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020     = 0x0f,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020   = 0x10,
    DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020            = 0x11,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020    = 0x12,
    DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020      = 0x13,
    DXGI_COLOR_SPACE_CUSTOM                             = 0xffffffff,
} DXGI_COLOR_SPACE_TYPE;
typedef void IDXGIOutputDuplication;

#endif

struct qemu_dxgi_factory
{
    /* Guest fields */
    IDXGIFactory5 IDXGIFactory5_iface;

    /* Host fields */
    IDXGIFactory5 *host;
};

struct qemu_dxgi_adapter
{
    /* Guest fields */
    IDXGIAdapter3 IDXGIAdapter3_iface;

    /* Host fields */
    IDXGIAdapter3 *host;
    struct qemu_dxgi_factory *factory;
};

struct qemu_dxgi_output
{
    /* Guest fields */
    IDXGIOutput4 IDXGIOutput4_iface;

    /* Host fields */
    IDXGIOutput4 *host;
    struct qemu_dxgi_adapter *adapter;
};

struct qemu_dxgi_device
{
    /* Guest fields */
    IDXGIDevice2 IDXGIDevice2_iface;
    IUnknown *child_layer;

    /* Host fields */
    IDXGIDevice2 *host;
    struct qemu_dxgi_adapter *adapter;
};

#ifdef QEMU_DLL_GUEST

void qemu_dxgi_factory_guest_init(struct qemu_dxgi_factory *factory);
void qemu_dxgi_adapter_guest_init(struct qemu_dxgi_adapter *adapter);
void qemu_dxgi_output_guest_init(struct qemu_dxgi_output *output);
void qemu_dxgi_device_guest_init(struct qemu_dxgi_device *device);

struct qemu_dxgi_factory *unsafe_impl_from_IDXGIFactory(IDXGIFactory *iface);
struct qemu_dxgi_adapter *unsafe_impl_from_IDXGIAdapter(IDXGIAdapter *iface);

#else

extern const struct qemu_ops *qemu_ops;

void qemu_dxgi_adapter_AddRef(struct qemu_syscall *call);
void qemu_dxgi_adapter_CheckInterfaceSupport(struct qemu_syscall *call);
void qemu_dxgi_adapter_EnumOutputs(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetDesc(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetDesc1(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetDesc2(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetParent(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_adapter_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_adapter_QueryVideoMemoryInfo(struct qemu_syscall *call);
void qemu_dxgi_adapter_RegisterHardwareContentProtectionTeardownStatusEvent(struct qemu_syscall *call);
void qemu_dxgi_adapter_RegisterVideoMemoryBudgetChangeNotificationEvent(struct qemu_syscall *call);
void qemu_dxgi_adapter_Release(struct qemu_syscall *call);
void qemu_dxgi_adapter_SetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_adapter_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_dxgi_adapter_SetVideoMemoryReservation(struct qemu_syscall *call);
void qemu_dxgi_adapter_UnregisterHardwareContentProtectionTeardownStatus(struct qemu_syscall *call);
void qemu_dxgi_adapter_UnregisterVideoMemoryBudgetChangeNotification(struct qemu_syscall *call);
void qemu_dxgi_device_AddRef(struct qemu_syscall *call);
void qemu_dxgi_device_CreateSurface(struct qemu_syscall *call);
void qemu_dxgi_device_EnqueueSetEvent(struct qemu_syscall *call);
void qemu_dxgi_device_GetAdapter(struct qemu_syscall *call);
void qemu_dxgi_device_GetGPUThreadPriority(struct qemu_syscall *call);
void qemu_dxgi_device_GetMaximumFrameLatency(struct qemu_syscall *call);
void qemu_dxgi_device_GetParent(struct qemu_syscall *call);
void qemu_dxgi_device_GetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_device_OfferResources(struct qemu_syscall *call);
void qemu_dxgi_device_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_device_QueryResourceResidency(struct qemu_syscall *call);
void qemu_dxgi_device_ReclaimResources(struct qemu_syscall *call);
void qemu_dxgi_device_Release(struct qemu_syscall *call);
void qemu_dxgi_device_SetGPUThreadPriority(struct qemu_syscall *call);
void qemu_dxgi_device_SetMaximumFrameLatency(struct qemu_syscall *call);
void qemu_dxgi_device_SetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_device_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_dxgi_factory_AddRef(struct qemu_syscall *call);
void qemu_dxgi_factory_CheckFeatureSupport(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSoftwareAdapter(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChain(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChainForComposition(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChainForCoreWindow(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChainForHwnd(struct qemu_syscall *call);
void qemu_dxgi_factory_EnumAdapterByLuid(struct qemu_syscall *call);
void qemu_dxgi_factory_EnumAdapters(struct qemu_syscall *call);
void qemu_dxgi_factory_EnumWarpAdapter(struct qemu_syscall *call);
void qemu_dxgi_factory_GetCreationFlags(struct qemu_syscall *call);
void qemu_dxgi_factory_GetParent(struct qemu_syscall *call);
void qemu_dxgi_factory_GetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_factory_GetSharedResourceAdapterLuid(struct qemu_syscall *call);
void qemu_dxgi_factory_GetWindowAssociation(struct qemu_syscall *call);
void qemu_dxgi_factory_IsCurrent(struct qemu_syscall *call);
void qemu_dxgi_factory_IsWindowedStereoEnabled(struct qemu_syscall *call);
void qemu_dxgi_factory_MakeWindowAssociation(struct qemu_syscall *call);
void qemu_dxgi_factory_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_factory_RegisterOcclusionStatusEvent(struct qemu_syscall *call);
void qemu_dxgi_factory_RegisterOcclusionStatusWindow(struct qemu_syscall *call);
void qemu_dxgi_factory_RegisterStereoStatusEvent(struct qemu_syscall *call);
void qemu_dxgi_factory_RegisterStereoStatusWindow(struct qemu_syscall *call);
void qemu_dxgi_factory_Release(struct qemu_syscall *call);
void qemu_dxgi_factory_SetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_factory_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_dxgi_factory_UnregisterOcclusionStatus(struct qemu_syscall *call);
void qemu_dxgi_factory_UnregisterStereoStatus(struct qemu_syscall *call);
void qemu_dxgi_output_AddRef(struct qemu_syscall *call);
void qemu_dxgi_output_CheckOverlayColorSpaceSupport(struct qemu_syscall *call);
void qemu_dxgi_output_CheckOverlaySupport(struct qemu_syscall *call);
void qemu_dxgi_output_DuplicateOutput(struct qemu_syscall *call);
void qemu_dxgi_output_FindClosestMatchingMode(struct qemu_syscall *call);
void qemu_dxgi_output_FindClosestMatchingMode1(struct qemu_syscall *call);
void qemu_dxgi_output_GetDesc(struct qemu_syscall *call);
void qemu_dxgi_output_GetDisplayModeList(struct qemu_syscall *call);
void qemu_dxgi_output_GetDisplayModeList1(struct qemu_syscall *call);
void qemu_dxgi_output_GetDisplaySurfaceData(struct qemu_syscall *call);
void qemu_dxgi_output_GetDisplaySurfaceData1(struct qemu_syscall *call);
void qemu_dxgi_output_GetFrameStatistics(struct qemu_syscall *call);
void qemu_dxgi_output_GetGammaControl(struct qemu_syscall *call);
void qemu_dxgi_output_GetGammaControlCapabilities(struct qemu_syscall *call);
void qemu_dxgi_output_GetParent(struct qemu_syscall *call);
void qemu_dxgi_output_GetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_output_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_output_Release(struct qemu_syscall *call);
void qemu_dxgi_output_ReleaseOwnership(struct qemu_syscall *call);
void qemu_dxgi_output_SetDisplaySurface(struct qemu_syscall *call);
void qemu_dxgi_output_SetGammaControl(struct qemu_syscall *call);
void qemu_dxgi_output_SetPrivateData(struct qemu_syscall *call);
void qemu_dxgi_output_SetPrivateDataInterface(struct qemu_syscall *call);
void qemu_dxgi_output_SupportsOverlays(struct qemu_syscall *call);
void qemu_dxgi_output_TakeOwnership(struct qemu_syscall *call);
void qemu_dxgi_output_WaitForVBlank(struct qemu_syscall *call);

HRESULT qemu_dxgi_factory_create(DWORD flags, DWORD version, struct qemu_dxgi_factory **factory);
HRESULT qemu_dxgi_adapter_create(struct qemu_dxgi_factory *factory, UINT idx, struct qemu_dxgi_adapter **adapter);
HRESULT qemu_dxgi_output_create(struct qemu_dxgi_adapter *adapter, UINT idx, struct qemu_dxgi_output **output);
ULONG qemu_dxgi_factory_Release_internal(struct qemu_dxgi_factory *factory);
ULONG qemu_dxgi_adapter_Release_internal(struct qemu_dxgi_adapter *adapter);
HRESULT qemu_dxgi_device_create(HMODULE mod, struct qemu_dxgi_adapter *adapter, struct qemu_dxgi_factory *factory,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, size_t layer_size,
        struct qemu_dxgi_device **device);

#endif

#endif
