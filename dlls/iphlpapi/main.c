/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <ws2tcpip.h>
#include <winternl.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <fltdefs.h>
#include <netioapi.h>
#include <tcpestats.h>

#ifdef QEMU_DLL_GUEST

#else

#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "iphlpapi.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_iphlpapi);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AddIPAddress,
    qemu_AllocateAndGetIfTableFromStack,
    qemu_AllocateAndGetIpAddrTableFromStack,
    qemu_AllocateAndGetIpForwardTableFromStack,
    qemu_AllocateAndGetIpNetTableFromStack,
    qemu_AllocateAndGetTcpTableFromStack,
    qemu_AllocateAndGetUdpTableFromStack,
    qemu_CancelIPChangeNotify,
    qemu_CancelMibChangeNotify2,
    qemu_ConvertInterfaceGuidToLuid,
    qemu_ConvertInterfaceIndexToLuid,
    qemu_ConvertInterfaceLuidToGuid,
    qemu_ConvertInterfaceLuidToIndex,
    qemu_ConvertInterfaceLuidToNameA,
    qemu_ConvertInterfaceLuidToNameW,
    qemu_ConvertInterfaceNameToLuidA,
    qemu_ConvertInterfaceNameToLuidW,
    qemu_CreateIpForwardEntry,
    qemu_CreateIpNetEntry,
    qemu_CreateProxyArpEntry,
    qemu_CreateSortedAddressPairs,
    qemu_DeleteIPAddress,
    qemu_DeleteIpForwardEntry,
    qemu_DeleteIpNetEntry,
    qemu_DeleteProxyArpEntry,
    qemu_EnableRouter,
    qemu_FlushIpNetTable,
    qemu_FreeMibTable,
    qemu_GetAdapterIndex,
    qemu_GetAdaptersAddresses,
    qemu_GetAdaptersInfo,
    qemu_GetBestInterface,
    qemu_GetBestInterfaceEx,
    qemu_GetBestRoute,
    qemu_GetExtendedTcpTable,
    qemu_GetExtendedUdpTable,
    qemu_GetFriendlyIfIndex,
    qemu_GetIcmpStatistics,
    qemu_GetIcmpStatisticsEx,
    qemu_GetIfEntry,
    qemu_GetIfEntry2,
    qemu_GetIfTable,
    qemu_GetIfTable2,
    qemu_GetIfTable2Ex,
    qemu_GetInterfaceInfo,
    qemu_GetIpAddrTable,
    qemu_GetIpForwardTable,
    qemu_GetIpNetTable,
    qemu_GetIpStatistics,
    qemu_GetIpStatisticsEx,
    qemu_GetNetworkParams,
    qemu_GetNumberOfInterfaces,
    qemu_GetPerAdapterInfo,
    qemu_GetRTTAndHopCount,
    qemu_GetTcp6Table,
    qemu_GetTcp6Table2,
    qemu_GetTcpStatistics,
    qemu_GetTcpStatisticsEx,
    qemu_GetTcpTable,
    qemu_GetTcpTable2,
    qemu_GetUdpStatistics,
    qemu_GetUdpStatisticsEx,
    qemu_GetUdpTable,
    qemu_GetUnicastIpAddressEntry,
    qemu_GetUnicastIpAddressTable,
    qemu_GetUniDirectionalAdapterInfo,
    qemu_Icmp6CreateFile,
    qemu_Icmp6SendEcho2,
    qemu_IcmpCloseHandle,
    qemu_IcmpCreateFile,
    qemu_IcmpSendEcho,
    qemu_IcmpSendEcho2,
    qemu_IcmpSendEcho2Ex,
    qemu_IPHLP_if_nametoindex,
    qemu_IpReleaseAddress,
    qemu_IpRenewAddress,
    qemu_NotifyAddrChange,
    qemu_NotifyIpInterfaceChange,
    qemu_NotifyRouteChange,
    qemu_NotifyUnicastIpAddressChange,
    qemu_PfBindInterfaceToIPAddress,
    qemu_PfCreateInterface,
    qemu_PfDeleteInterface,
    qemu_PfUnBindInterface,
    qemu_SendARP,
    qemu_SetIfEntry,
    qemu_SetIpForwardEntry,
    qemu_SetIpNetEntry,
    qemu_SetIpStatistics,
    qemu_SetIpTTL,
    qemu_SetPerTcpConnectionEStats,
    qemu_SetTcpEntry,
    qemu_UnenableRouter,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE iphlpapi;
    WINE_TRACE("Loading host-side iphlpapi wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    iphlpapi = LoadLibraryA("iphlpapi");
    if (!iphlpapi)
        WINE_ERR("Cannot find iphlpapi.dll.\n");

    p_if_nametoindex = (void *)GetProcAddress(iphlpapi, "if_nametoindex");
    p__PfCreateInterface = (void *)GetProcAddress(iphlpapi, "_PfCreateInterface@24");
    p__PfUnBindInterface = (void *)GetProcAddress(iphlpapi, "_PfUnBindInterface@4");
    p__PfDeleteInterface = (void *)GetProcAddress(iphlpapi, "_PfDeleteInterface@4");
    p__PfBindInterfaceToIPAddress = (void *)GetProcAddress(iphlpapi, "_PfBindInterfaceToIPAddress@12");

    return dll_functions;
}

#endif
