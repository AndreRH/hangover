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

/* For the private API. D3DERR_INVALIDCALL will not be used at runtime because we provide the IUnknown ptr. */
#define D3D_OK S_OK
#define D3DERR_INVALIDCALL E_FAIL
#define D3DSPD_IUNKNOWN 1
#include "private_data.h"

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
    CALL_DXGI_ADAPTER_QUERYINTERFACE,
    CALL_DXGI_ADAPTER_QUERYVIDEOMEMORYINFO,
    CALL_DXGI_ADAPTER_REGISTERHARDWARECONTENTPROTECTIONTEARDOWNSTATUSEVENT,
    CALL_DXGI_ADAPTER_REGISTERVIDEOMEMORYBUDGETCHANGENOTIFICATIONEVENT,
    CALL_DXGI_ADAPTER_RELEASE,
    CALL_DXGI_ADAPTER_SETVIDEOMEMORYRESERVATION,
    CALL_DXGI_ADAPTER_UNREGISTERHARDWARECONTENTPROTECTIONTEARDOWNSTATUS,
    CALL_DXGI_ADAPTER_UNREGISTERVIDEOMEMORYBUDGETCHANGENOTIFICATION,
    CALL_DXGI_DEVICE_ADDREF,
    CALL_DXGI_DEVICE_ENQUEUESETEVENT,
    CALL_DXGI_DEVICE_GETADAPTER,
    CALL_DXGI_DEVICE_GETGPUTHREADPRIORITY,
    CALL_DXGI_DEVICE_GETMAXIMUMFRAMELATENCY,
    CALL_DXGI_DEVICE_GETPARENT,
    CALL_DXGI_DEVICE_OFFERRESOURCES,
    CALL_DXGI_DEVICE_QUERYINTERFACE,
    CALL_DXGI_DEVICE_QUERYRESOURCERESIDENCY,
    CALL_DXGI_DEVICE_RECLAIMRESOURCES,
    CALL_DXGI_DEVICE_RELEASE,
    CALL_DXGI_DEVICE_SETGPUTHREADPRIORITY,
    CALL_DXGI_DEVICE_SETMAXIMUMFRAMELATENCY,
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
    CALL_DXGI_OUTPUT_QUERYINTERFACE,
    CALL_DXGI_OUTPUT_RELEASE,
    CALL_DXGI_OUTPUT_RELEASEOWNERSHIP,
    CALL_DXGI_OUTPUT_SETDISPLAYSURFACE,
    CALL_DXGI_OUTPUT_SETGAMMACONTROL,
    CALL_DXGI_OUTPUT_SUPPORTSOVERLAYS,
    CALL_DXGI_OUTPUT_TAKEOWNERSHIP,
    CALL_DXGI_OUTPUT_WAITFORVBLANK,
    CALL_DXGI_SURFACE_GETDC,
    CALL_DXGI_SURFACE_GETDESC,
    CALL_DXGI_SURFACE_GETDEVICE,
    CALL_DXGI_SURFACE_GETPARENT,
    CALL_DXGI_SURFACE_INNER_ADDREF,
    CALL_DXGI_SURFACE_INNER_QUERYINTERFACE,
    CALL_DXGI_SURFACE_INNER_RELEASE,
    CALL_DXGI_SURFACE_MAP,
    CALL_DXGI_SURFACE_RELEASEDC,
    CALL_DXGI_SURFACE_UNMAP,
    CALL_DXGI_SWAPCHAIN_ADDREF,
    CALL_DXGI_SWAPCHAIN_GETBACKGROUNDCOLOR,
    CALL_DXGI_SWAPCHAIN_GETBUFFER,
    CALL_DXGI_SWAPCHAIN_GETCONTAININGOUTPUT,
    CALL_DXGI_SWAPCHAIN_GETCOREWINDOW,
    CALL_DXGI_SWAPCHAIN_GETDESC,
    CALL_DXGI_SWAPCHAIN_GETDESC1,
    CALL_DXGI_SWAPCHAIN_GETDEVICE,
    CALL_DXGI_SWAPCHAIN_GETFRAMESTATISTICS,
    CALL_DXGI_SWAPCHAIN_GETFULLSCREENDESC,
    CALL_DXGI_SWAPCHAIN_GETFULLSCREENSTATE,
    CALL_DXGI_SWAPCHAIN_GETHWND,
    CALL_DXGI_SWAPCHAIN_GETLASTPRESENTCOUNT,
    CALL_DXGI_SWAPCHAIN_GETPARENT,
    CALL_DXGI_SWAPCHAIN_GETRESTRICTTOOUTPUT,
    CALL_DXGI_SWAPCHAIN_GETROTATION,
    CALL_DXGI_SWAPCHAIN_ISTEMPORARYMONOSUPPORTED,
    CALL_DXGI_SWAPCHAIN_PRESENT,
    CALL_DXGI_SWAPCHAIN_PRESENT1,
    CALL_DXGI_SWAPCHAIN_QUERYINTERFACE,
    CALL_DXGI_SWAPCHAIN_RELEASE,
    CALL_DXGI_SWAPCHAIN_RESIZEBUFFERS,
    CALL_DXGI_SWAPCHAIN_RESIZETARGET,
    CALL_DXGI_SWAPCHAIN_SETBACKGROUNDCOLOR,
    CALL_DXGI_SWAPCHAIN_SETFULLSCREENSTATE,
    CALL_DXGI_SWAPCHAIN_SETROTATION,
    CALL_DXGID3D10CREATEDEVICE,
    CALL_INIT_DLL,
    CALL_QEMU_DEVICE_CREATE_SURFACE,
};

struct qemu_dxgi_factory
{
    /* Guest fields */
    IDXGIFactory5 IDXGIFactory5_iface;
    struct wined3d_private_store private_store;

    /* Host fields */
    IDXGIFactory5 *host;
};

struct qemu_dxgi_adapter
{
    /* Guest fields */
    IDXGIAdapter3 IDXGIAdapter3_iface;
    struct wined3d_private_store private_store;

    /* Host fields */
    IDXGIAdapter3 *host;
    struct qemu_dxgi_factory *factory;
};

struct qemu_dxgi_output
{
    /* Guest fields */
    IDXGIOutput4 IDXGIOutput4_iface;
    struct wined3d_private_store private_store;

    /* Host fields */
    IDXGIOutput4 *host;
    struct qemu_dxgi_adapter *adapter;

    /* For finding the wrapper from the host object. */
    ULONG refcount;
    IUnknown priv_data_iface;
};

struct qemu_dxgi_device
{
    /* Guest fields */
    IDXGIDevice2 IDXGIDevice2_iface;
    IQemuDXGIDevice IQemuDXGIDevice_iface;
    IUnknown *child_layer;
    struct wined3d_private_store private_store;

    /* Host fields */
    IDXGIDevice2 *host;
    struct qemu_dxgi_adapter *adapter;
};

struct qemu_dxgi_surface
{
    /* Guest fields */
    IDXGISurface1 IDXGISurface1_iface;
    IUnknown IUnknown_iface;
    IUnknown *outer_unknown;
    struct wined3d_private_store private_store;

    /* Host fields */
    IDXGISurface1 *host;
    struct qemu_dxgi_device *device;

    /* For finding the wrapper from the host object. */
    ULONG refcount;
    IUnknown priv_data_iface;
};

struct qemu_dxgi_swapchain
{
    /* Guest fields */
    IDXGISwapChain1 IDXGISwapChain1_iface;
    struct wined3d_private_store private_store;

    /* Host fields */
    IDXGISwapChain1 *host;
    struct qemu_dxgi_device *device;
    struct qemu_dxgi_factory *factory;
};

#ifdef QEMU_DLL_GUEST

const GUID IID_IDXGISurface1;

static inline struct qemu_dxgi_surface *impl_from_IDXGISurface1(IDXGISurface1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_surface, IDXGISurface1_iface);
}

void qemu_dxgi_factory_guest_init(struct qemu_dxgi_factory *factory);
void qemu_dxgi_adapter_guest_init(struct qemu_dxgi_adapter *adapter);
void qemu_dxgi_output_guest_init(struct qemu_dxgi_output *output);
void qemu_dxgi_device_guest_init(struct qemu_dxgi_device *device);
void qemu_dxgi_surface_guest_init(struct qemu_dxgi_surface *surface, IUnknown *outer_unknown);
void qemu_dxgi_swapchain_guest_init(struct qemu_dxgi_device *device, uint64_t *host_buffers,
        struct qemu_dxgi_swapchain *swapchain);

void __fastcall dxgi_factory_guest_destroy(struct qemu_dxgi_factory *factory);
void __fastcall dxgi_adapter_guest_destroy(struct qemu_dxgi_adapter *adapter);
void __fastcall dxgi_output_guest_destroy(struct qemu_dxgi_output *output);
void __fastcall dxgi_device_guest_destroy(struct qemu_dxgi_device *device);
void __fastcall dxgi_surface_guest_destroy(struct qemu_dxgi_surface *surface);
void __fastcall dxgi_swapchain_guest_destroy(struct qemu_dxgi_swapchain *swapchain);

struct qemu_dxgi_factory *unsafe_impl_from_IDXGIFactory(IDXGIFactory *iface);
struct qemu_dxgi_adapter *unsafe_impl_from_IDXGIAdapter(IDXGIAdapter *iface);
struct qemu_dxgi_device *unsafe_impl_from_IDXGIDevice(IUnknown *iface);
struct qemu_dxgi_output *unsafe_impl_from_IDXGIOutput(IUnknown *iface);

HRESULT dxgi_get_private_data(struct wined3d_private_store *store,
        REFGUID guid, UINT *data_size, void *data);
HRESULT dxgi_set_private_data(struct wined3d_private_store *store,
        REFGUID guid, UINT data_size, const void *data);
HRESULT dxgi_set_private_data_interface(struct wined3d_private_store *store,
        REFGUID guid, const IUnknown *object);

#else

extern const struct qemu_ops *qemu_ops;

extern uint64_t dxgi_factory_guest_destroy;
extern uint64_t dxgi_adapter_guest_destroy;
extern uint64_t dxgi_output_guest_destroy;
extern uint64_t dxgi_device_guest_destroy;
extern uint64_t dxgi_surface_guest_destroy;
extern uint64_t dxgi_swapchain_guest_destroy;

void qemu_dxgi_adapter_AddRef(struct qemu_syscall *call);
void qemu_dxgi_adapter_CheckInterfaceSupport(struct qemu_syscall *call);
void qemu_dxgi_adapter_EnumOutputs(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetDesc(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetDesc1(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetDesc2(struct qemu_syscall *call);
void qemu_dxgi_adapter_GetParent(struct qemu_syscall *call);
void qemu_dxgi_adapter_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_adapter_QueryVideoMemoryInfo(struct qemu_syscall *call);
void qemu_dxgi_adapter_RegisterHardwareContentProtectionTeardownStatusEvent(struct qemu_syscall *call);
void qemu_dxgi_adapter_RegisterVideoMemoryBudgetChangeNotificationEvent(struct qemu_syscall *call);
void qemu_dxgi_adapter_Release(struct qemu_syscall *call);
void qemu_dxgi_adapter_SetVideoMemoryReservation(struct qemu_syscall *call);
void qemu_dxgi_adapter_UnregisterHardwareContentProtectionTeardownStatus(struct qemu_syscall *call);
void qemu_dxgi_adapter_UnregisterVideoMemoryBudgetChangeNotification(struct qemu_syscall *call);
void qemu_dxgi_device_AddRef(struct qemu_syscall *call);
void qemu_dxgi_device_EnqueueSetEvent(struct qemu_syscall *call);
void qemu_dxgi_device_GetAdapter(struct qemu_syscall *call);
void qemu_dxgi_device_GetGPUThreadPriority(struct qemu_syscall *call);
void qemu_dxgi_device_GetMaximumFrameLatency(struct qemu_syscall *call);
void qemu_dxgi_device_GetParent(struct qemu_syscall *call);
void qemu_dxgi_device_OfferResources(struct qemu_syscall *call);
void qemu_dxgi_device_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_device_QueryResourceResidency(struct qemu_syscall *call);
void qemu_dxgi_device_ReclaimResources(struct qemu_syscall *call);
void qemu_dxgi_device_Release(struct qemu_syscall *call);
void qemu_dxgi_device_SetGPUThreadPriority(struct qemu_syscall *call);
void qemu_dxgi_device_SetMaximumFrameLatency(struct qemu_syscall *call);
void qemu_dxgi_device_create_surface(struct qemu_syscall *call);
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
void qemu_dxgi_output_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_output_Release(struct qemu_syscall *call);
void qemu_dxgi_output_ReleaseOwnership(struct qemu_syscall *call);
void qemu_dxgi_output_SetDisplaySurface(struct qemu_syscall *call);
void qemu_dxgi_output_SetGammaControl(struct qemu_syscall *call);
void qemu_dxgi_output_SupportsOverlays(struct qemu_syscall *call);
void qemu_dxgi_output_TakeOwnership(struct qemu_syscall *call);
void qemu_dxgi_output_WaitForVBlank(struct qemu_syscall *call);
void qemu_dxgi_surface_GetDC(struct qemu_syscall *call);
void qemu_dxgi_surface_GetDesc(struct qemu_syscall *call);
void qemu_dxgi_surface_GetDevice(struct qemu_syscall *call);
void qemu_dxgi_surface_GetParent(struct qemu_syscall *call);
void qemu_dxgi_surface_Map(struct qemu_syscall *call);
void qemu_dxgi_surface_ReleaseDC(struct qemu_syscall *call);
void qemu_dxgi_surface_Unmap(struct qemu_syscall *call);
void qemu_dxgi_surface_inner_AddRef(struct qemu_syscall *call);
void qemu_dxgi_surface_inner_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_surface_inner_Release(struct qemu_syscall *call);
void qemu_dxgi_swapchain_AddRef(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetBackgroundColor(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetBuffer(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetContainingOutput(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetCoreWindow(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetDesc(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetDesc1(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetDevice(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetFrameStatistics(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetFullscreenDesc(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetFullscreenState(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetHwnd(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetLastPresentCount(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetParent(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetRestrictToOutput(struct qemu_syscall *call);
void qemu_dxgi_swapchain_GetRotation(struct qemu_syscall *call);
void qemu_dxgi_swapchain_IsTemporaryMonoSupported(struct qemu_syscall *call);
void qemu_dxgi_swapchain_Present(struct qemu_syscall *call);
void qemu_dxgi_swapchain_Present1(struct qemu_syscall *call);
void qemu_dxgi_swapchain_QueryInterface(struct qemu_syscall *call);
void qemu_dxgi_swapchain_Release(struct qemu_syscall *call);
void qemu_dxgi_swapchain_ResizeBuffers(struct qemu_syscall *call);
void qemu_dxgi_swapchain_ResizeTarget(struct qemu_syscall *call);
void qemu_dxgi_swapchain_SetBackgroundColor(struct qemu_syscall *call);
void qemu_dxgi_swapchain_SetFullscreenState(struct qemu_syscall *call);
void qemu_dxgi_swapchain_SetRotation(struct qemu_syscall *call);

HRESULT qemu_dxgi_factory_create(DWORD flags, DWORD version, struct qemu_dxgi_factory **factory);
HRESULT qemu_dxgi_adapter_create(struct qemu_dxgi_factory *factory, IDXGIAdapter3 *host,
        struct qemu_dxgi_adapter **adapter);
HRESULT qemu_dxgi_output_create(struct qemu_dxgi_adapter *adapter, IDXGIOutput4 *host, struct qemu_dxgi_output **output);
ULONG qemu_dxgi_factory_Release_internal(struct qemu_dxgi_factory *factory);
ULONG qemu_dxgi_adapter_Release_internal(struct qemu_dxgi_adapter *adapter);
ULONG qemu_dxgi_device_Release_internal(struct qemu_dxgi_device *device);

HRESULT qemu_dxgi_device_create(HMODULE mod, struct qemu_dxgi_adapter *adapter, struct qemu_dxgi_factory *factory,
        unsigned int flags, const D3D_FEATURE_LEVEL *feature_levels, unsigned int level_count, size_t layer_size,
        struct qemu_dxgi_device **device);
HRESULT qemu_dxgi_surface_create(IDXGISurface1 *host, struct qemu_dxgi_device *device,
        struct qemu_dxgi_surface **surface);
HRESULT qemu_dxgi_swapchain_create(IDXGISwapChain1 *host, struct qemu_dxgi_device *device,
        struct qemu_dxgi_factory *factory, uint64_t **host_buffers, struct qemu_dxgi_swapchain **swapchain);

struct qemu_dxgi_surface *surface_from_host(IDXGISurface1 *host);
struct qemu_dxgi_output *output_from_host(IDXGIOutput4 *host);

#endif

#endif
