#ifndef QEMU_IPHLPAPI_H
#define QEMU_IPHLPAPI_H

#include <stdlib.h>

enum iphlpapi_calls
{
    CALL_ADDIPADDRESS = 0,
    CALL_ALLOCATEANDGETIFTABLEFROMSTACK,
    CALL_ALLOCATEANDGETIPADDRTABLEFROMSTACK,
    CALL_ALLOCATEANDGETIPFORWARDTABLEFROMSTACK,
    CALL_ALLOCATEANDGETIPNETTABLEFROMSTACK,
    CALL_ALLOCATEANDGETTCPTABLEFROMSTACK,
    CALL_ALLOCATEANDGETUDPTABLEFROMSTACK,
    CALL_CANCELIPCHANGENOTIFY,
    CALL_CANCELMIBCHANGENOTIFY2,
    CALL_CONVERTINTERFACEGUIDTOLUID,
    CALL_CONVERTINTERFACEINDEXTOLUID,
    CALL_CONVERTINTERFACELUIDTOGUID,
    CALL_CONVERTINTERFACELUIDTOINDEX,
    CALL_CONVERTINTERFACELUIDTONAMEA,
    CALL_CONVERTINTERFACELUIDTONAMEW,
    CALL_CONVERTINTERFACENAMETOLUIDA,
    CALL_CONVERTINTERFACENAMETOLUIDW,
    CALL_CONVERTLENGTHTOIPV4MASK,
    CALL_CREATEIPFORWARDENTRY,
    CALL_CREATEIPNETENTRY,
    CALL_CREATEPROXYARPENTRY,
    CALL_CREATESORTEDADDRESSPAIRS,
    CALL_DELETEIPADDRESS,
    CALL_DELETEIPFORWARDENTRY,
    CALL_DELETEIPNETENTRY,
    CALL_DELETEPROXYARPENTRY,
    CALL_ENABLEROUTER,
    CALL_FLUSHIPNETTABLE,
    CALL_FREEMIBTABLE,
    CALL_GETADAPTERINDEX,
    CALL_GETADAPTERSADDRESSES,
    CALL_GETADAPTERSINFO,
    CALL_GETBESTINTERFACE,
    CALL_GETBESTINTERFACEEX,
    CALL_GETBESTROUTE,
    CALL_GETEXTENDEDTCPTABLE,
    CALL_GETEXTENDEDUDPTABLE,
    CALL_GETFRIENDLYIFINDEX,
    CALL_GETICMPSTATISTICS,
    CALL_GETICMPSTATISTICSEX,
    CALL_GETIFENTRY,
    CALL_GETIFENTRY2,
    CALL_GETIFTABLE,
    CALL_GETIFTABLE2,
    CALL_GETIFTABLE2EX,
    CALL_GETINTERFACEINFO,
    CALL_GETIPADDRTABLE,
    CALL_GETIPFORWARDTABLE,
    CALL_GETIPFORWARDTABLE2,
    CALL_GETIPNETTABLE,
    CALL_GETIPSTATISTICS,
    CALL_GETIPSTATISTICSEX,
    CALL_GETNETWORKPARAMS,
    CALL_GETNUMBEROFINTERFACES,
    CALL_GETPERADAPTERINFO,
    CALL_GETRTTANDHOPCOUNT,
    CALL_GETTCP6TABLE,
    CALL_GETTCP6TABLE2,
    CALL_GETTCPSTATISTICS,
    CALL_GETTCPSTATISTICSEX,
    CALL_GETTCPTABLE,
    CALL_GETTCPTABLE2,
    CALL_GETUDPSTATISTICS,
    CALL_GETUDPSTATISTICSEX,
    CALL_GETUDPTABLE,
    CALL_GETUNICASTIPADDRESSENTRY,
    CALL_GETUNICASTIPADDRESSTABLE,
    CALL_GETUNIDIRECTIONALADAPTERINFO,
    CALL_ICMP6CREATEFILE,
    CALL_ICMP6SENDECHO2,
    CALL_ICMPCLOSEHANDLE,
    CALL_ICMPCREATEFILE,
    CALL_ICMPSENDECHO,
    CALL_ICMPSENDECHO2,
    CALL_ICMPSENDECHO2EX,
    CALL_IPHLP_IF_INDEXTONAME,
    CALL_IPHLP_IF_NAMETOINDEX,
    CALL_IPRELEASEADDRESS,
    CALL_IPRENEWADDRESS,
    CALL_NOTIFYADDRCHANGE,
    CALL_NOTIFYIPINTERFACECHANGE,
    CALL_NOTIFYROUTECHANGE,
    CALL_NOTIFYUNICASTIPADDRESSCHANGE,
    CALL_PFBINDINTERFACETOIPADDRESS,
    CALL_PFCREATEINTERFACE,
    CALL_PFDELETEINTERFACE,
    CALL_PFUNBINDINTERFACE,
    CALL_SENDARP,
    CALL_SETIFENTRY,
    CALL_SETIPFORWARDENTRY,
    CALL_SETIPNETENTRY,
    CALL_SETIPSTATISTICS,
    CALL_SETIPTTL,
    CALL_SETPERTCPCONNECTIONESTATS,
    CALL_SETTCPENTRY,
    CALL_UNENABLEROUTER,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_AddIPAddress(struct qemu_syscall *call);
void qemu_AllocateAndGetIfTableFromStack(struct qemu_syscall *call);
void qemu_AllocateAndGetIpAddrTableFromStack(struct qemu_syscall *call);
void qemu_AllocateAndGetIpForwardTableFromStack(struct qemu_syscall *call);
void qemu_AllocateAndGetIpNetTableFromStack(struct qemu_syscall *call);
void qemu_AllocateAndGetTcpTableFromStack(struct qemu_syscall *call);
void qemu_AllocateAndGetUdpTableFromStack(struct qemu_syscall *call);
void qemu_CancelIPChangeNotify(struct qemu_syscall *call);
void qemu_CancelMibChangeNotify2(struct qemu_syscall *call);
void qemu_ConvertInterfaceGuidToLuid(struct qemu_syscall *call);
void qemu_ConvertInterfaceIndexToLuid(struct qemu_syscall *call);
void qemu_ConvertInterfaceLuidToGuid(struct qemu_syscall *call);
void qemu_ConvertInterfaceLuidToIndex(struct qemu_syscall *call);
void qemu_ConvertInterfaceLuidToNameA(struct qemu_syscall *call);
void qemu_ConvertInterfaceLuidToNameW(struct qemu_syscall *call);
void qemu_ConvertInterfaceNameToLuidA(struct qemu_syscall *call);
void qemu_ConvertInterfaceNameToLuidW(struct qemu_syscall *call);
void qemu_ConvertLengthToIpv4Mask(struct qemu_syscall *call);
void qemu_CreateIpForwardEntry(struct qemu_syscall *call);
void qemu_CreateIpNetEntry(struct qemu_syscall *call);
void qemu_CreateProxyArpEntry(struct qemu_syscall *call);
void qemu_CreateSortedAddressPairs(struct qemu_syscall *call);
void qemu_DeleteIPAddress(struct qemu_syscall *call);
void qemu_DeleteIpForwardEntry(struct qemu_syscall *call);
void qemu_DeleteIpNetEntry(struct qemu_syscall *call);
void qemu_DeleteProxyArpEntry(struct qemu_syscall *call);
void qemu_EnableRouter(struct qemu_syscall *call);
void qemu_FlushIpNetTable(struct qemu_syscall *call);
void qemu_FreeMibTable(struct qemu_syscall *call);
void qemu_GetAdapterIndex(struct qemu_syscall *call);
void qemu_GetAdaptersAddresses(struct qemu_syscall *call);
void qemu_GetAdaptersInfo(struct qemu_syscall *call);
void qemu_GetBestInterface(struct qemu_syscall *call);
void qemu_GetBestInterfaceEx(struct qemu_syscall *call);
void qemu_GetBestRoute(struct qemu_syscall *call);
void qemu_GetExtendedTcpTable(struct qemu_syscall *call);
void qemu_GetExtendedUdpTable(struct qemu_syscall *call);
void qemu_GetFriendlyIfIndex(struct qemu_syscall *call);
void qemu_GetIcmpStatistics(struct qemu_syscall *call);
void qemu_GetIcmpStatisticsEx(struct qemu_syscall *call);
void qemu_GetIfEntry(struct qemu_syscall *call);
void qemu_GetIfEntry2(struct qemu_syscall *call);
void qemu_GetIfTable(struct qemu_syscall *call);
void qemu_GetIfTable2(struct qemu_syscall *call);
void qemu_GetIfTable2Ex(struct qemu_syscall *call);
void qemu_GetInterfaceInfo(struct qemu_syscall *call);
void qemu_GetIpAddrTable(struct qemu_syscall *call);
void qemu_GetIpForwardTable(struct qemu_syscall *call);
void qemu_GetIpForwardTable2(struct qemu_syscall *call);
void qemu_GetIpNetTable(struct qemu_syscall *call);
void qemu_GetIpStatistics(struct qemu_syscall *call);
void qemu_GetIpStatisticsEx(struct qemu_syscall *call);
void qemu_GetNetworkParams(struct qemu_syscall *call);
void qemu_GetNumberOfInterfaces(struct qemu_syscall *call);
void qemu_GetPerAdapterInfo(struct qemu_syscall *call);
void qemu_GetRTTAndHopCount(struct qemu_syscall *call);
void qemu_GetTcp6Table(struct qemu_syscall *call);
void qemu_GetTcp6Table2(struct qemu_syscall *call);
void qemu_GetTcpStatistics(struct qemu_syscall *call);
void qemu_GetTcpStatisticsEx(struct qemu_syscall *call);
void qemu_GetTcpTable(struct qemu_syscall *call);
void qemu_GetTcpTable2(struct qemu_syscall *call);
void qemu_GetUdpStatistics(struct qemu_syscall *call);
void qemu_GetUdpStatisticsEx(struct qemu_syscall *call);
void qemu_GetUdpTable(struct qemu_syscall *call);
void qemu_GetUnicastIpAddressEntry(struct qemu_syscall *call);
void qemu_GetUnicastIpAddressTable(struct qemu_syscall *call);
void qemu_GetUniDirectionalAdapterInfo(struct qemu_syscall *call);
void qemu_Icmp6CreateFile(struct qemu_syscall *call);
void qemu_Icmp6SendEcho2(struct qemu_syscall *call);
void qemu_IcmpCloseHandle(struct qemu_syscall *call);
void qemu_IcmpCreateFile(struct qemu_syscall *call);
void qemu_IcmpSendEcho(struct qemu_syscall *call);
void qemu_IcmpSendEcho2(struct qemu_syscall *call);
void qemu_IcmpSendEcho2Ex(struct qemu_syscall *call);
void qemu_IPHLP_if_indextoname(struct qemu_syscall *call);
void qemu_IPHLP_if_nametoindex(struct qemu_syscall *call);
void qemu_IpReleaseAddress(struct qemu_syscall *call);
void qemu_IpRenewAddress(struct qemu_syscall *call);
void qemu_NotifyAddrChange(struct qemu_syscall *call);
void qemu_NotifyIpInterfaceChange(struct qemu_syscall *call);
void qemu_NotifyRouteChange(struct qemu_syscall *call);
void qemu_NotifyUnicastIpAddressChange(struct qemu_syscall *call);
void qemu_PfBindInterfaceToIPAddress(struct qemu_syscall *call);
void qemu_PfCreateInterface(struct qemu_syscall *call);
void qemu_PfDeleteInterface(struct qemu_syscall *call);
void qemu_PfUnBindInterface(struct qemu_syscall *call);
void qemu_SendARP(struct qemu_syscall *call);
void qemu_SetIfEntry(struct qemu_syscall *call);
void qemu_SetIpForwardEntry(struct qemu_syscall *call);
void qemu_SetIpNetEntry(struct qemu_syscall *call);
void qemu_SetIpStatistics(struct qemu_syscall *call);
void qemu_SetIpTTL(struct qemu_syscall *call);
void qemu_SetPerTcpConnectionEStats(struct qemu_syscall *call);
void qemu_SetTcpEntry(struct qemu_syscall *call);
void qemu_UnenableRouter(struct qemu_syscall *call);

CHAR * (* WINAPI p_if_indextoname)(NET_IFINDEX index, CHAR *name);
IF_INDEX (* WINAPI p_if_nametoindex)(const char *name);
DWORD (* WINAPI p__PfCreateInterface)(DWORD dwName,PFFORWARD_ACTION inAction,PFFORWARD_ACTION outAction,BOOL bUseLog,BOOL bMustBeUnique,INTERFACE_HANDLE *ppInterface);
DWORD (* WINAPI p__PfUnBindInterface)(INTERFACE_HANDLE interfaceXX);
DWORD (* WINAPI p__PfDeleteInterface)(INTERFACE_HANDLE interfaceXX);
DWORD (* WINAPI p__PfBindInterfaceToIPAddress)(INTERFACE_HANDLE interfaceXX, PFADDRESSTYPE type, PBYTE ip);

#endif

#endif
