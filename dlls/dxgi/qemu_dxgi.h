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
    CALL_DXGI_FACTORY_ADDREF,
    CALL_DXGI_FACTORY_CHECKFEATURESUPPORT,
    CALL_DXGI_FACTORY_CREATESOFTWAREADAPTER,
    CALL_DXGI_FACTORY_CREATESWAPCHAIN,
    CALL_DXGI_FACTORY_CREATESWAPCHAINFORCOMPOSITION,
    CALL_DXGI_FACTORY_CREATESWAPCHAINFORCOREWINDOW,
    CALL_DXGI_FACTORY_CREATESWAPCHAINFORHWND,
    CALL_DXGI_FACTORY_ENUMADAPTERBYLUID,
    CALL_DXGI_FACTORY_ENUMADAPTERS,
    CALL_DXGI_FACTORY_ENUMADAPTERS1,
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
    CALL_DXGID3D10CREATEDEVICE,
    CALL_DXGID3D10REGISTERLAYERS,
    CALL_INIT_DLL,
};

#ifdef QEMU_DLL_GUEST

/* Hacks for missing dxgi1_5 headers in mingw. */
typedef IDXGIFactory2 IDXGIFactory5;
typedef IDXGIAdapter2 IDXGIAdapter3;
typedef enum DXGI_FEATURE
{
    DXGI_FEATURE_PRESENT_ALLOW_TEARING = 0x0
} DXGI_FEATURE;
typedef void DXGI_QUERY_VIDEO_MEMORY_INFO;
typedef enum DXGI_MEMORY_SEGMENT_GROUP {
    DXGI_MEMORY_SEGMENT_GROUP_LOCAL = 0x0,
    DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 0x1
} DXGI_MEMORY_SEGMENT_GROUP;

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
};

#ifdef QEMU_DLL_GUEST

void qemu_dxgi_factory_guest_init(struct qemu_dxgi_factory *factory);
void qemu_dxgi_adapter_guest_init(struct qemu_dxgi_adapter *factory);

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
void qemu_dxgi_factory_AddRef(struct qemu_syscall *call);
void qemu_dxgi_factory_CheckFeatureSupport(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSoftwareAdapter(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChain(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChainForComposition(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChainForCoreWindow(struct qemu_syscall *call);
void qemu_dxgi_factory_CreateSwapChainForHwnd(struct qemu_syscall *call);
void qemu_dxgi_factory_EnumAdapterByLuid(struct qemu_syscall *call);
void qemu_dxgi_factory_EnumAdapters(struct qemu_syscall *call);
void qemu_dxgi_factory_EnumAdapters1(struct qemu_syscall *call);
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

HRESULT qemu_dxgi_factory_create(DWORD flags, DWORD version, struct qemu_dxgi_factory **factory);
HRESULT qemu_dxgi_adapter_create(struct qemu_dxgi_adapter **adapter);

#endif

#endif
