/*
 * Copyright 2017 André Hentschel
 * Copyright 2017-2018 Stefan Dösinger (for CodeWeavers)
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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_iphlpapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_iphlpapi);
#endif


struct qemu_AddIPAddress
{
    struct qemu_syscall super;
    uint64_t Address;
    uint64_t IpMask;
    uint64_t IfIndex;
    uint64_t NTEContext;
    uint64_t NTEInstance;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AddIPAddress(IPAddr Address, IPMask IpMask, DWORD IfIndex, PULONG NTEContext, PULONG NTEInstance)
{
    struct qemu_AddIPAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDIPADDRESS);
    call.Address = (ULONG_PTR)Address;
    call.IpMask = (ULONG_PTR)IpMask;
    call.IfIndex = (ULONG_PTR)IfIndex;
    call.NTEContext = (ULONG_PTR)NTEContext;
    call.NTEInstance = (ULONG_PTR)NTEInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddIPAddress(struct qemu_syscall *call)
{
    struct qemu_AddIPAddress *c = (struct qemu_AddIPAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddIPAddress(c->Address, c->IpMask, c->IfIndex, QEMU_G2H(c->NTEContext), QEMU_G2H(c->NTEInstance));
}

#endif

struct qemu_AllocateAndGetIfTableFromStack
{
    struct qemu_syscall super;
    uint64_t ppIfTable;
    uint64_t bOrder;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AllocateAndGetIfTableFromStack(PMIB_IFTABLE *ppIfTable, BOOL bOrder, HANDLE heap, DWORD flags)
{
    struct qemu_AllocateAndGetIfTableFromStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDGETIFTABLEFROMSTACK);
    call.ppIfTable = (ULONG_PTR)ppIfTable;
    call.bOrder = (ULONG_PTR)bOrder;
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateAndGetIfTableFromStack to Wine headers? */
extern DWORD WINAPI AllocateAndGetIfTableFromStack(PMIB_IFTABLE *ppIfTable, BOOL bOrder, HANDLE heap, DWORD flags);
void qemu_AllocateAndGetIfTableFromStack(struct qemu_syscall *call)
{
    struct qemu_AllocateAndGetIfTableFromStack *c = (struct qemu_AllocateAndGetIfTableFromStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndGetIfTableFromStack(QEMU_G2H(c->ppIfTable), c->bOrder, QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_AllocateAndGetIpAddrTableFromStack
{
    struct qemu_syscall super;
    uint64_t ppIpAddrTable;
    uint64_t bOrder;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AllocateAndGetIpAddrTableFromStack(PMIB_IPADDRTABLE *ppIpAddrTable, BOOL bOrder, HANDLE heap, DWORD flags)
{
    struct qemu_AllocateAndGetIpAddrTableFromStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDGETIPADDRTABLEFROMSTACK);
    call.ppIpAddrTable = (ULONG_PTR)ppIpAddrTable;
    call.bOrder = (ULONG_PTR)bOrder;
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateAndGetIpAddrTableFromStack to Wine headers? */
extern DWORD WINAPI AllocateAndGetIpAddrTableFromStack(PMIB_IPADDRTABLE *ppIpAddrTable, BOOL bOrder, HANDLE heap, DWORD flags);
void qemu_AllocateAndGetIpAddrTableFromStack(struct qemu_syscall *call)
{
    struct qemu_AllocateAndGetIpAddrTableFromStack *c = (struct qemu_AllocateAndGetIpAddrTableFromStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndGetIpAddrTableFromStack(QEMU_G2H(c->ppIpAddrTable), c->bOrder, QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_CancelIPChangeNotify
{
    struct qemu_syscall super;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CancelIPChangeNotify(LPOVERLAPPED overlapped)
{
    struct qemu_CancelIPChangeNotify call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELIPCHANGENOTIFY);
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CancelIPChangeNotify(struct qemu_syscall *call)
{
    struct qemu_CancelIPChangeNotify *c = (struct qemu_CancelIPChangeNotify *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelIPChangeNotify(QEMU_G2H(c->overlapped));
}

#endif

struct qemu_CancelMibChangeNotify2
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CancelMibChangeNotify2(HANDLE handle)
{
    struct qemu_CancelMibChangeNotify2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELMIBCHANGENOTIFY2);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CancelMibChangeNotify2 to Wine headers? */
extern DWORD WINAPI CancelMibChangeNotify2(HANDLE handle);
void qemu_CancelMibChangeNotify2(struct qemu_syscall *call)
{
    struct qemu_CancelMibChangeNotify2 *c = (struct qemu_CancelMibChangeNotify2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelMibChangeNotify2(QEMU_G2H(c->handle));
}

#endif

struct qemu_CreateIpForwardEntry
{
    struct qemu_syscall super;
    uint64_t pRoute;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CreateIpForwardEntry(PMIB_IPFORWARDROW pRoute)
{
    struct qemu_CreateIpForwardEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEIPFORWARDENTRY);
    call.pRoute = (ULONG_PTR)pRoute;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateIpForwardEntry(struct qemu_syscall *call)
{
    struct qemu_CreateIpForwardEntry *c = (struct qemu_CreateIpForwardEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateIpForwardEntry(QEMU_G2H(c->pRoute));
}

#endif

struct qemu_CreateIpNetEntry
{
    struct qemu_syscall super;
    uint64_t pArpEntry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CreateIpNetEntry(PMIB_IPNETROW pArpEntry)
{
    struct qemu_CreateIpNetEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEIPNETENTRY);
    call.pArpEntry = (ULONG_PTR)pArpEntry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateIpNetEntry(struct qemu_syscall *call)
{
    struct qemu_CreateIpNetEntry *c = (struct qemu_CreateIpNetEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateIpNetEntry(QEMU_G2H(c->pArpEntry));
}

#endif

struct qemu_CreateProxyArpEntry
{
    struct qemu_syscall super;
    uint64_t dwAddress;
    uint64_t dwMask;
    uint64_t dwIfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CreateProxyArpEntry(DWORD dwAddress, DWORD dwMask, DWORD dwIfIndex)
{
    struct qemu_CreateProxyArpEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROXYARPENTRY);
    call.dwAddress = (ULONG_PTR)dwAddress;
    call.dwMask = (ULONG_PTR)dwMask;
    call.dwIfIndex = (ULONG_PTR)dwIfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateProxyArpEntry(struct qemu_syscall *call)
{
    struct qemu_CreateProxyArpEntry *c = (struct qemu_CreateProxyArpEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProxyArpEntry(c->dwAddress, c->dwMask, c->dwIfIndex);
}

#endif

struct qemu_CreateSortedAddressPairs
{
    struct qemu_syscall super;
    uint64_t src_list;
    uint64_t src_count;
    uint64_t dst_list;
    uint64_t dst_count;
    uint64_t options;
    uint64_t pair_list;
    uint64_t pair_count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CreateSortedAddressPairs(const PSOCKADDR_IN6 src_list, DWORD src_count, const PSOCKADDR_IN6 dst_list, DWORD dst_count, DWORD options, PSOCKADDR_IN6_PAIR *pair_list, DWORD *pair_count)
{
    struct qemu_CreateSortedAddressPairs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESORTEDADDRESSPAIRS);
    call.src_list = (ULONG_PTR)src_list;
    call.src_count = (ULONG_PTR)src_count;
    call.dst_list = (ULONG_PTR)dst_list;
    call.dst_count = (ULONG_PTR)dst_count;
    call.options = (ULONG_PTR)options;
    call.pair_list = (ULONG_PTR)pair_list;
    call.pair_count = (ULONG_PTR)pair_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CreateSortedAddressPairs to Wine headers? */
extern DWORD WINAPI CreateSortedAddressPairs(const PSOCKADDR_IN6 src_list, DWORD src_count, const PSOCKADDR_IN6 dst_list, DWORD dst_count, DWORD options, PSOCKADDR_IN6_PAIR *pair_list, DWORD *pair_count);
void qemu_CreateSortedAddressPairs(struct qemu_syscall *call)
{
    struct qemu_CreateSortedAddressPairs *c = (struct qemu_CreateSortedAddressPairs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateSortedAddressPairs(QEMU_G2H(c->src_list), c->src_count, QEMU_G2H(c->dst_list), c->dst_count, c->options, QEMU_G2H(c->pair_list), QEMU_G2H(c->pair_count));
}

#endif

struct qemu_DeleteIPAddress
{
    struct qemu_syscall super;
    uint64_t NTEContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeleteIPAddress(ULONG NTEContext)
{
    struct qemu_DeleteIPAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEIPADDRESS);
    call.NTEContext = (ULONG_PTR)NTEContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteIPAddress(struct qemu_syscall *call)
{
    struct qemu_DeleteIPAddress *c = (struct qemu_DeleteIPAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteIPAddress(c->NTEContext);
}

#endif

struct qemu_DeleteIpForwardEntry
{
    struct qemu_syscall super;
    uint64_t pRoute;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeleteIpForwardEntry(PMIB_IPFORWARDROW pRoute)
{
    struct qemu_DeleteIpForwardEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEIPFORWARDENTRY);
    call.pRoute = (ULONG_PTR)pRoute;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteIpForwardEntry(struct qemu_syscall *call)
{
    struct qemu_DeleteIpForwardEntry *c = (struct qemu_DeleteIpForwardEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteIpForwardEntry(QEMU_G2H(c->pRoute));
}

#endif

struct qemu_DeleteIpNetEntry
{
    struct qemu_syscall super;
    uint64_t pArpEntry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeleteIpNetEntry(PMIB_IPNETROW pArpEntry)
{
    struct qemu_DeleteIpNetEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEIPNETENTRY);
    call.pArpEntry = (ULONG_PTR)pArpEntry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteIpNetEntry(struct qemu_syscall *call)
{
    struct qemu_DeleteIpNetEntry *c = (struct qemu_DeleteIpNetEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteIpNetEntry(QEMU_G2H(c->pArpEntry));
}

#endif

struct qemu_DeleteProxyArpEntry
{
    struct qemu_syscall super;
    uint64_t dwAddress;
    uint64_t dwMask;
    uint64_t dwIfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeleteProxyArpEntry(DWORD dwAddress, DWORD dwMask, DWORD dwIfIndex)
{
    struct qemu_DeleteProxyArpEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPROXYARPENTRY);
    call.dwAddress = (ULONG_PTR)dwAddress;
    call.dwMask = (ULONG_PTR)dwMask;
    call.dwIfIndex = (ULONG_PTR)dwIfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteProxyArpEntry(struct qemu_syscall *call)
{
    struct qemu_DeleteProxyArpEntry *c = (struct qemu_DeleteProxyArpEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteProxyArpEntry(c->dwAddress, c->dwMask, c->dwIfIndex);
}

#endif

struct qemu_EnableRouter
{
    struct qemu_syscall super;
    uint64_t pHandle;
    uint64_t pOverlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnableRouter(HANDLE * pHandle, OVERLAPPED * pOverlapped)
{
    struct qemu_EnableRouter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLEROUTER);
    call.pHandle = (ULONG_PTR)pHandle;
    call.pOverlapped = (ULONG_PTR)pOverlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableRouter(struct qemu_syscall *call)
{
    struct qemu_EnableRouter *c = (struct qemu_EnableRouter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableRouter(QEMU_G2H(c->pHandle), QEMU_G2H(c->pOverlapped));
}

#endif

struct qemu_FlushIpNetTable
{
    struct qemu_syscall super;
    uint64_t dwIfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI FlushIpNetTable(DWORD dwIfIndex)
{
    struct qemu_FlushIpNetTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHIPNETTABLE);
    call.dwIfIndex = (ULONG_PTR)dwIfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushIpNetTable(struct qemu_syscall *call)
{
    struct qemu_FlushIpNetTable *c = (struct qemu_FlushIpNetTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FlushIpNetTable(c->dwIfIndex);
}

#endif

struct qemu_FreeMibTable
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FreeMibTable(void *ptr)
{
    struct qemu_FreeMibTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEMIBTABLE);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);
}

#else

void qemu_FreeMibTable(struct qemu_syscall *call)
{
    struct qemu_FreeMibTable *c = (struct qemu_FreeMibTable *)call;
    WINE_FIXME("Unverified!\n");
    FreeMibTable(QEMU_G2H(c->ptr));
}

#endif

struct qemu_GetAdapterIndex
{
    struct qemu_syscall super;
    uint64_t AdapterName;
    uint64_t IfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetAdapterIndex(LPWSTR AdapterName, PULONG IfIndex)
{
    struct qemu_GetAdapterIndex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADAPTERINDEX);
    call.AdapterName = (ULONG_PTR)AdapterName;
    call.IfIndex = (ULONG_PTR)IfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAdapterIndex(struct qemu_syscall *call)
{
    struct qemu_GetAdapterIndex *c = (struct qemu_GetAdapterIndex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAdapterIndex(QEMU_G2H(c->AdapterName), QEMU_G2H(c->IfIndex));
}

#endif

struct qemu_GetAdaptersInfo
{
    struct qemu_syscall super;
    uint64_t pAdapterInfo;
    uint64_t pOutBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen)
{
    struct qemu_GetAdaptersInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADAPTERSINFO);
    call.pAdapterInfo = (ULONG_PTR)pAdapterInfo;
    call.pOutBufLen = (ULONG_PTR)pOutBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAdaptersInfo(struct qemu_syscall *call)
{
    struct qemu_GetAdaptersInfo *c = (struct qemu_GetAdaptersInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAdaptersInfo(QEMU_G2H(c->pAdapterInfo), QEMU_G2H(c->pOutBufLen));
}

#endif

struct qemu_GetAdaptersAddresses
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t flags;
    uint64_t reserved;
    uint64_t aa;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI GetAdaptersAddresses(ULONG family, ULONG flags, PVOID reserved, PIP_ADAPTER_ADDRESSES aa, PULONG buflen)
{
    struct qemu_GetAdaptersAddresses call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADAPTERSADDRESSES);
    call.family = (ULONG_PTR)family;
    call.flags = (ULONG_PTR)flags;
    call.reserved = (ULONG_PTR)reserved;
    call.aa = (ULONG_PTR)aa;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAdaptersAddresses(struct qemu_syscall *call)
{
    struct qemu_GetAdaptersAddresses *c = (struct qemu_GetAdaptersAddresses *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAdaptersAddresses(c->family, c->flags, QEMU_G2H(c->reserved), QEMU_G2H(c->aa), QEMU_G2H(c->buflen));
}

#endif

struct qemu_GetBestInterface
{
    struct qemu_syscall super;
    uint64_t dwDestAddr;
    uint64_t pdwBestIfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetBestInterface(IPAddr dwDestAddr, PDWORD pdwBestIfIndex)
{
    struct qemu_GetBestInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBESTINTERFACE);
    call.dwDestAddr = (ULONG_PTR)dwDestAddr;
    call.pdwBestIfIndex = (ULONG_PTR)pdwBestIfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBestInterface(struct qemu_syscall *call)
{
    struct qemu_GetBestInterface *c = (struct qemu_GetBestInterface *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBestInterface(c->dwDestAddr, QEMU_G2H(c->pdwBestIfIndex));
}

#endif

struct qemu_GetBestInterfaceEx
{
    struct qemu_syscall super;
    uint64_t pDestAddr;
    uint64_t pdwBestIfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetBestInterfaceEx(struct sockaddr *pDestAddr, PDWORD pdwBestIfIndex)
{
    struct qemu_GetBestInterfaceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBESTINTERFACEEX);
    call.pDestAddr = (ULONG_PTR)pDestAddr;
    call.pdwBestIfIndex = (ULONG_PTR)pdwBestIfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBestInterfaceEx(struct qemu_syscall *call)
{
    struct qemu_GetBestInterfaceEx *c = (struct qemu_GetBestInterfaceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBestInterfaceEx(QEMU_G2H(c->pDestAddr), QEMU_G2H(c->pdwBestIfIndex));
}

#endif

struct qemu_GetBestRoute
{
    struct qemu_syscall super;
    uint64_t dwDestAddr;
    uint64_t dwSourceAddr;
    uint64_t pBestRoute;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetBestRoute(DWORD dwDestAddr, DWORD dwSourceAddr, PMIB_IPFORWARDROW pBestRoute)
{
    struct qemu_GetBestRoute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBESTROUTE);
    call.dwDestAddr = (ULONG_PTR)dwDestAddr;
    call.dwSourceAddr = (ULONG_PTR)dwSourceAddr;
    call.pBestRoute = (ULONG_PTR)pBestRoute;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBestRoute(struct qemu_syscall *call)
{
    struct qemu_GetBestRoute *c = (struct qemu_GetBestRoute *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBestRoute(c->dwDestAddr, c->dwSourceAddr, QEMU_G2H(c->pBestRoute));
}

#endif

struct qemu_GetFriendlyIfIndex
{
    struct qemu_syscall super;
    uint64_t IfIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFriendlyIfIndex(DWORD IfIndex)
{
    struct qemu_GetFriendlyIfIndex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFRIENDLYIFINDEX);
    call.IfIndex = (ULONG_PTR)IfIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFriendlyIfIndex(struct qemu_syscall *call)
{
    struct qemu_GetFriendlyIfIndex *c = (struct qemu_GetFriendlyIfIndex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFriendlyIfIndex(c->IfIndex);
}

#endif

struct qemu_GetIfEntry
{
    struct qemu_syscall super;
    uint64_t pIfRow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIfEntry(PMIB_IFROW pIfRow)
{
    struct qemu_GetIfEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIFENTRY);
    call.pIfRow = (ULONG_PTR)pIfRow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIfEntry(struct qemu_syscall *call)
{
    struct qemu_GetIfEntry *c = (struct qemu_GetIfEntry *)call;
    /* MIB_IFROW has the same size on 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIfEntry(QEMU_G2H(c->pIfRow));
}

#endif

struct qemu_GetIfEntry2
{
    struct qemu_syscall super;
    uint64_t row2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIfEntry2(MIB_IF_ROW2 *row2)
{
    struct qemu_GetIfEntry2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIFENTRY2);
    call.row2 = (ULONG_PTR)row2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIfEntry2(struct qemu_syscall *call)
{
    struct qemu_GetIfEntry2 *c = (struct qemu_GetIfEntry2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetIfEntry2(QEMU_G2H(c->row2));
}

#endif

struct qemu_GetIfTable
{
    struct qemu_syscall super;
    uint64_t pIfTable;
    uint64_t pdwSize;
    uint64_t bOrder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIfTable(PMIB_IFTABLE pIfTable, PULONG pdwSize, BOOL bOrder)
{
    struct qemu_GetIfTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIFTABLE);
    call.pIfTable = (ULONG_PTR)pIfTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIfTable(struct qemu_syscall *call)
{
    struct qemu_GetIfTable *c = (struct qemu_GetIfTable *)call;
    /* MIB_IFTABLE has the same size on 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIfTable(QEMU_G2H(c->pIfTable), QEMU_G2H(c->pdwSize), c->bOrder);
}

#endif

struct qemu_GetIfTable2Ex
{
    struct qemu_syscall super;
    uint64_t level;
    uint64_t table;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIfTable2Ex(MIB_IF_TABLE_LEVEL level, MIB_IF_TABLE2 **table)
{
    struct qemu_GetIfTable2Ex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIFTABLE2EX);
    call.level = (ULONG_PTR)level;
    call.table = (ULONG_PTR)table;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetIfTable2Ex to Wine headers? */
extern DWORD WINAPI GetIfTable2Ex(MIB_IF_TABLE_LEVEL level, MIB_IF_TABLE2 **table);
void qemu_GetIfTable2Ex(struct qemu_syscall *call)
{
    struct qemu_GetIfTable2Ex *c = (struct qemu_GetIfTable2Ex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetIfTable2Ex(c->level, QEMU_G2H(c->table));
}

#endif

struct qemu_GetIfTable2
{
    struct qemu_syscall super;
    uint64_t table;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIfTable2(MIB_IF_TABLE2 **table)
{
    struct qemu_GetIfTable2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIFTABLE2);
    call.table = (ULONG_PTR)table;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIfTable2(struct qemu_syscall *call)
{
    struct qemu_GetIfTable2 *c = (struct qemu_GetIfTable2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetIfTable2(QEMU_G2H(c->table));
}

#endif

struct qemu_GetInterfaceInfo
{
    struct qemu_syscall super;
    uint64_t pIfTable;
    uint64_t dwOutBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetInterfaceInfo(PIP_INTERFACE_INFO pIfTable, PULONG dwOutBufLen)
{
    struct qemu_GetInterfaceInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETINTERFACEINFO);
    call.pIfTable = (ULONG_PTR)pIfTable;
    call.dwOutBufLen = (ULONG_PTR)dwOutBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetInterfaceInfo(struct qemu_syscall *call)
{
    struct qemu_GetInterfaceInfo *c = (struct qemu_GetInterfaceInfo *)call;
    /* IP_INTERFACE_INFO has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetInterfaceInfo(QEMU_G2H(c->pIfTable), QEMU_G2H(c->dwOutBufLen));
}

#endif

struct qemu_GetIpAddrTable
{
    struct qemu_syscall super;
    uint64_t pIpAddrTable;
    uint64_t pdwSize;
    uint64_t bOrder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIpAddrTable(PMIB_IPADDRTABLE pIpAddrTable, PULONG pdwSize, BOOL bOrder)
{
    struct qemu_GetIpAddrTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIPADDRTABLE);
    call.pIpAddrTable = (ULONG_PTR)pIpAddrTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIpAddrTable(struct qemu_syscall *call)
{
    struct qemu_GetIpAddrTable *c = (struct qemu_GetIpAddrTable *)call;
    /* MIB_IPADDRTABLE has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIpAddrTable(QEMU_G2H(c->pIpAddrTable), QEMU_G2H(c->pdwSize), c->bOrder);
}

#endif

struct qemu_GetIpForwardTable
{
    struct qemu_syscall super;
    uint64_t pIpForwardTable;
    uint64_t pdwSize;
    uint64_t bOrder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIpForwardTable(PMIB_IPFORWARDTABLE pIpForwardTable, PULONG pdwSize, BOOL bOrder)
{
    struct qemu_GetIpForwardTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIPFORWARDTABLE);
    call.pIpForwardTable = (ULONG_PTR)pIpForwardTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIpForwardTable(struct qemu_syscall *call)
{
    struct qemu_GetIpForwardTable *c = (struct qemu_GetIpForwardTable *)call;
    /* MIB_IPFORWARDTABLE has the same size on 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIpForwardTable(QEMU_G2H(c->pIpForwardTable), QEMU_G2H(c->pdwSize), c->bOrder);
}

#endif

struct qemu_GetIpNetTable
{
    struct qemu_syscall super;
    uint64_t pIpNetTable;
    uint64_t pdwSize;
    uint64_t bOrder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIpNetTable(PMIB_IPNETTABLE pIpNetTable, PULONG pdwSize, BOOL bOrder)
{
    struct qemu_GetIpNetTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIPNETTABLE);
    call.pIpNetTable = (ULONG_PTR)pIpNetTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIpNetTable(struct qemu_syscall *call)
{
    struct qemu_GetIpNetTable *c = (struct qemu_GetIpNetTable *)call;
    /* MIB_IPNETTABLE has the same size on 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIpNetTable(QEMU_G2H(c->pIpNetTable), QEMU_G2H(c->pdwSize), c->bOrder);
}

#endif

struct qemu_GetNetworkParams
{
    struct qemu_syscall super;
    uint64_t pFixedInfo;
    uint64_t pOutBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNetworkParams(PFIXED_INFO pFixedInfo, PULONG pOutBufLen)
{
    struct qemu_GetNetworkParams call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNETWORKPARAMS);
    call.pFixedInfo = (ULONG_PTR)pFixedInfo;
    call.pOutBufLen = (ULONG_PTR)pOutBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNetworkParams(struct qemu_syscall *call)
{
    struct qemu_GetNetworkParams *c = (struct qemu_GetNetworkParams *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNetworkParams(QEMU_G2H(c->pFixedInfo), QEMU_G2H(c->pOutBufLen));
}

#endif

struct qemu_GetNumberOfInterfaces
{
    struct qemu_syscall super;
    uint64_t pdwNumIf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNumberOfInterfaces(PDWORD pdwNumIf)
{
    struct qemu_GetNumberOfInterfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBEROFINTERFACES);
    call.pdwNumIf = (ULONG_PTR)pdwNumIf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberOfInterfaces(struct qemu_syscall *call)
{
    struct qemu_GetNumberOfInterfaces *c = (struct qemu_GetNumberOfInterfaces *)call;
    WINE_TRACE("\n");
    c->super.iret = GetNumberOfInterfaces(QEMU_G2H(c->pdwNumIf));
}

#endif

struct qemu_GetPerAdapterInfo
{
    struct qemu_syscall super;
    uint64_t IfIndex;
    uint64_t pPerAdapterInfo;
    uint64_t pOutBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPerAdapterInfo(ULONG IfIndex, PIP_PER_ADAPTER_INFO pPerAdapterInfo, PULONG pOutBufLen)
{
    struct qemu_GetPerAdapterInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPERADAPTERINFO);
    call.IfIndex = (ULONG_PTR)IfIndex;
    call.pPerAdapterInfo = (ULONG_PTR)pPerAdapterInfo;
    call.pOutBufLen = (ULONG_PTR)pOutBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPerAdapterInfo(struct qemu_syscall *call)
{
    struct qemu_GetPerAdapterInfo *c = (struct qemu_GetPerAdapterInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPerAdapterInfo(c->IfIndex, QEMU_G2H(c->pPerAdapterInfo), QEMU_G2H(c->pOutBufLen));
}

#endif

struct qemu_GetRTTAndHopCount
{
    struct qemu_syscall super;
    uint64_t DestIpAddress;
    uint64_t HopCount;
    uint64_t MaxHops;
    uint64_t RTT;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetRTTAndHopCount(IPAddr DestIpAddress, PULONG HopCount, ULONG MaxHops, PULONG RTT)
{
    struct qemu_GetRTTAndHopCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRTTANDHOPCOUNT);
    call.DestIpAddress = (ULONG_PTR)DestIpAddress;
    call.HopCount = (ULONG_PTR)HopCount;
    call.MaxHops = (ULONG_PTR)MaxHops;
    call.RTT = (ULONG_PTR)RTT;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRTTAndHopCount(struct qemu_syscall *call)
{
    struct qemu_GetRTTAndHopCount *c = (struct qemu_GetRTTAndHopCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRTTAndHopCount(c->DestIpAddress, QEMU_G2H(c->HopCount), c->MaxHops, QEMU_G2H(c->RTT));
}

#endif

struct qemu_GetTcpTable
{
    struct qemu_syscall super;
    uint64_t pTcpTable;
    uint64_t pdwSize;
    uint64_t bOrder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTcpTable(PMIB_TCPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder)
{
    struct qemu_GetTcpTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTCPTABLE);
    call.pTcpTable = (ULONG_PTR)pTcpTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTcpTable(struct qemu_syscall *call)
{
    struct qemu_GetTcpTable *c = (struct qemu_GetTcpTable *)call;
    /* MIB_TCPTABLE has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetTcpTable(QEMU_G2H(c->pTcpTable), QEMU_G2H(c->pdwSize), c->bOrder);
}

#endif

struct qemu_GetExtendedTcpTable
{
    struct qemu_syscall super;
    uint64_t pTcpTable;
    uint64_t pdwSize;
    uint64_t bOrder;
    uint64_t ulAf;
    uint64_t TableClass;
    uint64_t Reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetExtendedTcpTable(PVOID pTcpTable, PDWORD pdwSize, BOOL bOrder, ULONG ulAf, TCP_TABLE_CLASS TableClass, ULONG Reserved)
{
    struct qemu_GetExtendedTcpTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXTENDEDTCPTABLE);
    call.pTcpTable = (ULONG_PTR)pTcpTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;
    call.ulAf = (ULONG_PTR)ulAf;
    call.TableClass = (ULONG_PTR)TableClass;
    call.Reserved = (ULONG_PTR)Reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExtendedTcpTable(struct qemu_syscall *call)
{
    struct qemu_GetExtendedTcpTable *c = (struct qemu_GetExtendedTcpTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExtendedTcpTable(QEMU_G2H(c->pTcpTable), QEMU_G2H(c->pdwSize), c->bOrder, c->ulAf, c->TableClass, c->Reserved);
}

#endif

struct qemu_GetUdpTable
{
    struct qemu_syscall super;
    uint64_t pUdpTable;
    uint64_t pdwSize;
    uint64_t bOrder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetUdpTable(PMIB_UDPTABLE pUdpTable, PDWORD pdwSize, BOOL bOrder)
{
    struct qemu_GetUdpTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUDPTABLE);
    call.pUdpTable = (ULONG_PTR)pUdpTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUdpTable(struct qemu_syscall *call)
{
    struct qemu_GetUdpTable *c = (struct qemu_GetUdpTable *)call;
    /* MIB_UDPTABLE has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetUdpTable(QEMU_G2H(c->pUdpTable), QEMU_G2H(c->pdwSize), c->bOrder);
}

#endif

struct qemu_GetExtendedUdpTable
{
    struct qemu_syscall super;
    uint64_t pUdpTable;
    uint64_t pdwSize;
    uint64_t bOrder;
    uint64_t ulAf;
    uint64_t TableClass;
    uint64_t Reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetExtendedUdpTable(PVOID pUdpTable, PDWORD pdwSize, BOOL bOrder, ULONG ulAf, UDP_TABLE_CLASS TableClass, ULONG Reserved)
{
    struct qemu_GetExtendedUdpTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXTENDEDUDPTABLE);
    call.pUdpTable = (ULONG_PTR)pUdpTable;
    call.pdwSize = (ULONG_PTR)pdwSize;
    call.bOrder = (ULONG_PTR)bOrder;
    call.ulAf = (ULONG_PTR)ulAf;
    call.TableClass = (ULONG_PTR)TableClass;
    call.Reserved = (ULONG_PTR)Reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExtendedUdpTable(struct qemu_syscall *call)
{
    struct qemu_GetExtendedUdpTable *c = (struct qemu_GetExtendedUdpTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExtendedUdpTable(QEMU_G2H(c->pUdpTable), QEMU_G2H(c->pdwSize), c->bOrder, c->ulAf, c->TableClass, c->Reserved);
}

#endif

struct qemu_GetUnicastIpAddressEntry
{
    struct qemu_syscall super;
    uint64_t row;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetUnicastIpAddressEntry(MIB_UNICASTIPADDRESS_ROW *row)
{
    struct qemu_GetUnicastIpAddressEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUNICASTIPADDRESSENTRY);
    call.row = (ULONG_PTR)row;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUnicastIpAddressEntry(struct qemu_syscall *call)
{
    struct qemu_GetUnicastIpAddressEntry *c = (struct qemu_GetUnicastIpAddressEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUnicastIpAddressEntry(QEMU_G2H(c->row));
}

#endif

struct qemu_GetUnicastIpAddressTable
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t table;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetUnicastIpAddressTable(ADDRESS_FAMILY family, MIB_UNICASTIPADDRESS_TABLE **table)
{
    struct qemu_GetUnicastIpAddressTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUNICASTIPADDRESSTABLE);
    call.family = (ULONG_PTR)family;
    call.table = (ULONG_PTR)table;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetUnicastIpAddressTable to Wine headers? */
extern DWORD WINAPI GetUnicastIpAddressTable(ADDRESS_FAMILY family, MIB_UNICASTIPADDRESS_TABLE **table);
void qemu_GetUnicastIpAddressTable(struct qemu_syscall *call)
{
    struct qemu_GetUnicastIpAddressTable *c = (struct qemu_GetUnicastIpAddressTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUnicastIpAddressTable(c->family, QEMU_G2H(c->table));
}

#endif

struct qemu_GetUniDirectionalAdapterInfo
{
    struct qemu_syscall super;
    uint64_t pIPIfInfo;
    uint64_t dwOutBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetUniDirectionalAdapterInfo(PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo, PULONG dwOutBufLen)
{
    struct qemu_GetUniDirectionalAdapterInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUNIDIRECTIONALADAPTERINFO);
    call.pIPIfInfo = (ULONG_PTR)pIPIfInfo;
    call.dwOutBufLen = (ULONG_PTR)dwOutBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUniDirectionalAdapterInfo(struct qemu_syscall *call)
{
    struct qemu_GetUniDirectionalAdapterInfo *c = (struct qemu_GetUniDirectionalAdapterInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUniDirectionalAdapterInfo(QEMU_G2H(c->pIPIfInfo), QEMU_G2H(c->dwOutBufLen));
}

#endif

struct qemu_IpReleaseAddress
{
    struct qemu_syscall super;
    uint64_t AdapterInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI IpReleaseAddress(PIP_ADAPTER_INDEX_MAP AdapterInfo)
{
    struct qemu_IpReleaseAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IPRELEASEADDRESS);
    call.AdapterInfo = (ULONG_PTR)AdapterInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IpReleaseAddress(struct qemu_syscall *call)
{
    struct qemu_IpReleaseAddress *c = (struct qemu_IpReleaseAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IpReleaseAddress(QEMU_G2H(c->AdapterInfo));
}

#endif

struct qemu_IpRenewAddress
{
    struct qemu_syscall super;
    uint64_t AdapterInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI IpRenewAddress(PIP_ADAPTER_INDEX_MAP AdapterInfo)
{
    struct qemu_IpRenewAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IPRENEWADDRESS);
    call.AdapterInfo = (ULONG_PTR)AdapterInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IpRenewAddress(struct qemu_syscall *call)
{
    struct qemu_IpRenewAddress *c = (struct qemu_IpRenewAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IpRenewAddress(QEMU_G2H(c->AdapterInfo));
}

#endif

struct qemu_NotifyAddrChange
{
    struct qemu_syscall super;
    uint64_t Handle;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NotifyAddrChange(PHANDLE Handle, LPOVERLAPPED overlapped)
{
    struct qemu_NotifyAddrChange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYADDRCHANGE);
    call.Handle = (ULONG_PTR)Handle;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NotifyAddrChange(struct qemu_syscall *call)
{
    struct qemu_NotifyAddrChange *c = (struct qemu_NotifyAddrChange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyAddrChange(QEMU_G2H(c->Handle), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_NotifyIpInterfaceChange
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t callback;
    uint64_t context;
    uint64_t init_notify;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NotifyIpInterfaceChange(ADDRESS_FAMILY family, PIPINTERFACE_CHANGE_CALLBACK callback, PVOID context, BOOLEAN init_notify, PHANDLE handle)
{
    struct qemu_NotifyIpInterfaceChange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYIPINTERFACECHANGE);
    call.family = (ULONG_PTR)family;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.init_notify = (ULONG_PTR)init_notify;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NotifyIpInterfaceChange to Wine headers? */
extern DWORD WINAPI NotifyIpInterfaceChange(ADDRESS_FAMILY family, PIPINTERFACE_CHANGE_CALLBACK callback, PVOID context, BOOLEAN init_notify, PHANDLE handle);
void qemu_NotifyIpInterfaceChange(struct qemu_syscall *call)
{
    struct qemu_NotifyIpInterfaceChange *c = (struct qemu_NotifyIpInterfaceChange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyIpInterfaceChange(c->family, QEMU_G2H(c->callback), QEMU_G2H(c->context), c->init_notify, QEMU_G2H(c->handle));
}

#endif

struct qemu_NotifyRouteChange
{
    struct qemu_syscall super;
    uint64_t Handle;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NotifyRouteChange(PHANDLE Handle, LPOVERLAPPED overlapped)
{
    struct qemu_NotifyRouteChange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYROUTECHANGE);
    call.Handle = (ULONG_PTR)Handle;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NotifyRouteChange(struct qemu_syscall *call)
{
    struct qemu_NotifyRouteChange *c = (struct qemu_NotifyRouteChange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyRouteChange(QEMU_G2H(c->Handle), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_NotifyUnicastIpAddressChange
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t callback;
    uint64_t context;
    uint64_t init_notify;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NotifyUnicastIpAddressChange(ADDRESS_FAMILY family, PUNICAST_IPADDRESS_CHANGE_CALLBACK callback, PVOID context, BOOLEAN init_notify, PHANDLE handle)
{
    struct qemu_NotifyUnicastIpAddressChange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYUNICASTIPADDRESSCHANGE);
    call.family = (ULONG_PTR)family;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.init_notify = (ULONG_PTR)init_notify;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NotifyUnicastIpAddressChange to Wine headers? */
extern DWORD WINAPI NotifyUnicastIpAddressChange(ADDRESS_FAMILY family, PUNICAST_IPADDRESS_CHANGE_CALLBACK callback, PVOID context, BOOLEAN init_notify, PHANDLE handle);
void qemu_NotifyUnicastIpAddressChange(struct qemu_syscall *call)
{
    struct qemu_NotifyUnicastIpAddressChange *c = (struct qemu_NotifyUnicastIpAddressChange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyUnicastIpAddressChange(c->family, QEMU_G2H(c->callback), QEMU_G2H(c->context), c->init_notify, QEMU_G2H(c->handle));
}

#endif

struct qemu_SendARP
{
    struct qemu_syscall super;
    uint64_t DestIP;
    uint64_t SrcIP;
    uint64_t pMacAddr;
    uint64_t PhyAddrLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SendARP(IPAddr DestIP, IPAddr SrcIP, PVOID pMacAddr, PULONG PhyAddrLen)
{
    struct qemu_SendARP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDARP);
    call.DestIP = (ULONG_PTR)DestIP;
    call.SrcIP = (ULONG_PTR)SrcIP;
    call.pMacAddr = (ULONG_PTR)pMacAddr;
    call.PhyAddrLen = (ULONG_PTR)PhyAddrLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendARP(struct qemu_syscall *call)
{
    struct qemu_SendARP *c = (struct qemu_SendARP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendARP(c->DestIP, c->SrcIP, QEMU_G2H(c->pMacAddr), QEMU_G2H(c->PhyAddrLen));
}

#endif

struct qemu_SetIfEntry
{
    struct qemu_syscall super;
    uint64_t pIfRow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetIfEntry(PMIB_IFROW pIfRow)
{
    struct qemu_SetIfEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETIFENTRY);
    call.pIfRow = (ULONG_PTR)pIfRow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetIfEntry(struct qemu_syscall *call)
{
    struct qemu_SetIfEntry *c = (struct qemu_SetIfEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetIfEntry(QEMU_G2H(c->pIfRow));
}

#endif

struct qemu_SetIpForwardEntry
{
    struct qemu_syscall super;
    uint64_t pRoute;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetIpForwardEntry(PMIB_IPFORWARDROW pRoute)
{
    struct qemu_SetIpForwardEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETIPFORWARDENTRY);
    call.pRoute = (ULONG_PTR)pRoute;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetIpForwardEntry(struct qemu_syscall *call)
{
    struct qemu_SetIpForwardEntry *c = (struct qemu_SetIpForwardEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetIpForwardEntry(QEMU_G2H(c->pRoute));
}

#endif

struct qemu_SetIpNetEntry
{
    struct qemu_syscall super;
    uint64_t pArpEntry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetIpNetEntry(PMIB_IPNETROW pArpEntry)
{
    struct qemu_SetIpNetEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETIPNETENTRY);
    call.pArpEntry = (ULONG_PTR)pArpEntry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetIpNetEntry(struct qemu_syscall *call)
{
    struct qemu_SetIpNetEntry *c = (struct qemu_SetIpNetEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetIpNetEntry(QEMU_G2H(c->pArpEntry));
}

#endif

struct qemu_SetIpStatistics
{
    struct qemu_syscall super;
    uint64_t pIpStats;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetIpStatistics(PMIB_IPSTATS pIpStats)
{
    struct qemu_SetIpStatistics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETIPSTATISTICS);
    call.pIpStats = (ULONG_PTR)pIpStats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetIpStatistics(struct qemu_syscall *call)
{
    struct qemu_SetIpStatistics *c = (struct qemu_SetIpStatistics *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetIpStatistics(QEMU_G2H(c->pIpStats));
}

#endif

struct qemu_SetIpTTL
{
    struct qemu_syscall super;
    uint64_t nTTL;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetIpTTL(UINT nTTL)
{
    struct qemu_SetIpTTL call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETIPTTL);
    call.nTTL = (ULONG_PTR)nTTL;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetIpTTL(struct qemu_syscall *call)
{
    struct qemu_SetIpTTL *c = (struct qemu_SetIpTTL *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetIpTTL(c->nTTL);
}

#endif

struct qemu_SetTcpEntry
{
    struct qemu_syscall super;
    uint64_t pTcpRow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetTcpEntry(PMIB_TCPROW pTcpRow)
{
    struct qemu_SetTcpEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTCPENTRY);
    call.pTcpRow = (ULONG_PTR)pTcpRow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTcpEntry(struct qemu_syscall *call)
{
    struct qemu_SetTcpEntry *c = (struct qemu_SetTcpEntry *)call;
    /* MIB_TCPROW has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = SetTcpEntry(QEMU_G2H(c->pTcpRow));
}

#endif

struct qemu_SetPerTcpConnectionEStats
{
    struct qemu_syscall super;
    uint64_t row;
    uint64_t state;
    uint64_t rw;
    uint64_t version;
    uint64_t size;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetPerTcpConnectionEStats(PMIB_TCPROW row, TCP_ESTATS_TYPE state, PBYTE rw, ULONG version, ULONG size, ULONG offset)
{
    struct qemu_SetPerTcpConnectionEStats call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPERTCPCONNECTIONESTATS);
    call.row = (ULONG_PTR)row;
    call.state = (ULONG_PTR)state;
    call.rw = (ULONG_PTR)rw;
    call.version = (ULONG_PTR)version;
    call.size = (ULONG_PTR)size;
    call.offset = (ULONG_PTR)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetPerTcpConnectionEStats to Wine headers? */
extern DWORD WINAPI SetPerTcpConnectionEStats(PMIB_TCPROW row, TCP_ESTATS_TYPE state, PBYTE rw, ULONG version, ULONG size, ULONG offset);
void qemu_SetPerTcpConnectionEStats(struct qemu_syscall *call)
{
    struct qemu_SetPerTcpConnectionEStats *c = (struct qemu_SetPerTcpConnectionEStats *)call;
    /* MIB_TCPROW has the same size in 32 and 64 bit. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPerTcpConnectionEStats(QEMU_G2H(c->row), c->state, QEMU_G2H(c->rw), c->version, c->size, c->offset);
}

#endif

struct qemu_UnenableRouter
{
    struct qemu_syscall super;
    uint64_t pOverlapped;
    uint64_t lpdwEnableCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI UnenableRouter(OVERLAPPED * pOverlapped, LPDWORD lpdwEnableCount)
{
    struct qemu_UnenableRouter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNENABLEROUTER);
    call.pOverlapped = (ULONG_PTR)pOverlapped;
    call.lpdwEnableCount = (ULONG_PTR)lpdwEnableCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnenableRouter(struct qemu_syscall *call)
{
    struct qemu_UnenableRouter *c = (struct qemu_UnenableRouter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnenableRouter(QEMU_G2H(c->pOverlapped), QEMU_G2H(c->lpdwEnableCount));
}

#endif

struct qemu_PfCreateInterface
{
    struct qemu_syscall super;
    uint64_t dwName;
    uint64_t inAction;
    uint64_t outAction;
    uint64_t bUseLog;
    uint64_t bMustBeUnique;
    uint64_t ppInterface;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI PfCreateInterface(DWORD dwName, PFFORWARD_ACTION inAction, PFFORWARD_ACTION outAction, BOOL bUseLog, BOOL bMustBeUnique, INTERFACE_HANDLE *ppInterface)
{
    struct qemu_PfCreateInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFCREATEINTERFACE);
    call.dwName = (ULONG_PTR)dwName;
    call.inAction = (ULONG_PTR)inAction;
    call.outAction = (ULONG_PTR)outAction;
    call.bUseLog = (ULONG_PTR)bUseLog;
    call.bMustBeUnique = (ULONG_PTR)bMustBeUnique;
    call.ppInterface = (ULONG_PTR)ppInterface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PfCreateInterface(struct qemu_syscall *call)
{
    struct qemu_PfCreateInterface *c = (struct qemu_PfCreateInterface *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__PfCreateInterface(c->dwName, c->inAction, c->outAction, c->bUseLog, c->bMustBeUnique, QEMU_G2H(c->ppInterface));
}

#endif

struct qemu_PfUnBindInterface
{
    struct qemu_syscall super;
    uint64_t interfaceXX;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI PfUnBindInterface(INTERFACE_HANDLE interfaceXX)
{
    struct qemu_PfUnBindInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFUNBINDINTERFACE);
    call.interfaceXX = (ULONG_PTR)interfaceXX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PfUnBindInterface(struct qemu_syscall *call)
{
    struct qemu_PfUnBindInterface *c = (struct qemu_PfUnBindInterface *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__PfUnBindInterface(QEMU_G2H(c->interfaceXX));
}

#endif

struct qemu_PfDeleteInterface
{
    struct qemu_syscall super;
    uint64_t interfaceXX;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI PfDeleteInterface(INTERFACE_HANDLE interfaceXX)
{
    struct qemu_PfDeleteInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFDELETEINTERFACE);
    call.interfaceXX = (ULONG_PTR)interfaceXX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PfDeleteInterface(struct qemu_syscall *call)
{
    struct qemu_PfDeleteInterface *c = (struct qemu_PfDeleteInterface *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__PfDeleteInterface(QEMU_G2H(c->interfaceXX));
}

#endif

struct qemu_PfBindInterfaceToIPAddress
{
    struct qemu_syscall super;
    uint64_t interfaceXX;
    uint64_t type;
    uint64_t ip;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI PfBindInterfaceToIPAddress(INTERFACE_HANDLE interfaceXX, PFADDRESSTYPE type, PBYTE ip)
{
    struct qemu_PfBindInterfaceToIPAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFBINDINTERFACETOIPADDRESS);
    call.interfaceXX = (ULONG_PTR)interfaceXX;
    call.type = (ULONG_PTR)type;
    call.ip = (ULONG_PTR)ip;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PfBindInterfaceToIPAddress(struct qemu_syscall *call)
{
    struct qemu_PfBindInterfaceToIPAddress *c = (struct qemu_PfBindInterfaceToIPAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__PfBindInterfaceToIPAddress(QEMU_G2H(c->interfaceXX), c->type, QEMU_G2H(c->ip));
}

#endif

struct qemu_GetTcpTable2
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t size;
    uint64_t order;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI GetTcpTable2(PMIB_TCPTABLE2 table, PULONG size, BOOL order)
{
    struct qemu_GetTcpTable2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTCPTABLE2);
    call.table = (ULONG_PTR)table;
    call.size = (ULONG_PTR)size;
    call.order = (ULONG_PTR)order;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetTcpTable2 to Wine headers? */
extern ULONG WINAPI GetTcpTable2(PMIB_TCPTABLE2 table, PULONG size, BOOL order);
void qemu_GetTcpTable2(struct qemu_syscall *call)
{
    struct qemu_GetTcpTable2 *c = (struct qemu_GetTcpTable2 *)call;
    /* MIB_TCPTABLE has the same size in 32 and 64 bit. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTcpTable2(QEMU_G2H(c->table), QEMU_G2H(c->size), c->order);
}

#endif

struct qemu_GetTcp6Table
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t size;
    uint64_t order;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI GetTcp6Table(PMIB_TCP6TABLE table, PULONG size, BOOL order)
{
    struct qemu_GetTcp6Table call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTCP6TABLE);
    call.table = (ULONG_PTR)table;
    call.size = (ULONG_PTR)size;
    call.order = (ULONG_PTR)order;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetTcp6Table to Wine headers? */
extern ULONG WINAPI GetTcp6Table(PMIB_TCP6TABLE table, PULONG size, BOOL order);
void qemu_GetTcp6Table(struct qemu_syscall *call)
{
    struct qemu_GetTcp6Table *c = (struct qemu_GetTcp6Table *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTcp6Table(QEMU_G2H(c->table), QEMU_G2H(c->size), c->order);
}

#endif

struct qemu_GetTcp6Table2
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t size;
    uint64_t order;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI GetTcp6Table2(PMIB_TCP6TABLE2 table, PULONG size, BOOL order)
{
    struct qemu_GetTcp6Table2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTCP6TABLE2);
    call.table = (ULONG_PTR)table;
    call.size = (ULONG_PTR)size;
    call.order = (ULONG_PTR)order;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetTcp6Table2 to Wine headers? */
extern ULONG WINAPI GetTcp6Table2(PMIB_TCP6TABLE2 table, PULONG size, BOOL order);
void qemu_GetTcp6Table2(struct qemu_syscall *call)
{
    struct qemu_GetTcp6Table2 *c = (struct qemu_GetTcp6Table2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTcp6Table2(QEMU_G2H(c->table), QEMU_G2H(c->size), c->order);
}

#endif

struct qemu_ConvertInterfaceGuidToLuid
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t luid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceGuidToLuid(const GUID *guid, NET_LUID *luid)
{
    struct qemu_ConvertInterfaceGuidToLuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACEGUIDTOLUID);
    call.guid = (ULONG_PTR)guid;
    call.luid = (ULONG_PTR)luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceGuidToLuid(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceGuidToLuid *c = (struct qemu_ConvertInterfaceGuidToLuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceGuidToLuid(QEMU_G2H(c->guid), QEMU_G2H(c->luid));
}

#endif

struct qemu_ConvertInterfaceIndexToLuid
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t luid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceIndexToLuid(NET_IFINDEX index, NET_LUID *luid)
{
    struct qemu_ConvertInterfaceIndexToLuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACEINDEXTOLUID);
    call.index = (ULONG_PTR)index;
    call.luid = (ULONG_PTR)luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceIndexToLuid(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceIndexToLuid *c = (struct qemu_ConvertInterfaceIndexToLuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceIndexToLuid(c->index, QEMU_G2H(c->luid));
}

#endif

struct qemu_ConvertInterfaceLuidToGuid
{
    struct qemu_syscall super;
    uint64_t luid;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceLuidToGuid(const NET_LUID *luid, GUID *guid)
{
    struct qemu_ConvertInterfaceLuidToGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACELUIDTOGUID);
    call.luid = (ULONG_PTR)luid;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceLuidToGuid(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceLuidToGuid *c = (struct qemu_ConvertInterfaceLuidToGuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceLuidToGuid(QEMU_G2H(c->luid), QEMU_G2H(c->guid));
}

#endif

struct qemu_ConvertInterfaceLuidToIndex
{
    struct qemu_syscall super;
    uint64_t luid;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceLuidToIndex(const NET_LUID *luid, NET_IFINDEX *index)
{
    struct qemu_ConvertInterfaceLuidToIndex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACELUIDTOINDEX);
    call.luid = (ULONG_PTR)luid;
    call.index = (ULONG_PTR)index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceLuidToIndex(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceLuidToIndex *c = (struct qemu_ConvertInterfaceLuidToIndex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceLuidToIndex(QEMU_G2H(c->luid), QEMU_G2H(c->index));
}

#endif

struct qemu_ConvertInterfaceLuidToNameA
{
    struct qemu_syscall super;
    uint64_t luid;
    uint64_t name;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceLuidToNameA(const NET_LUID *luid, char *name, SIZE_T len)
{
    struct qemu_ConvertInterfaceLuidToNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACELUIDTONAMEA);
    call.luid = (ULONG_PTR)luid;
    call.name = (ULONG_PTR)name;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceLuidToNameA(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceLuidToNameA *c = (struct qemu_ConvertInterfaceLuidToNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceLuidToNameA(QEMU_G2H(c->luid), QEMU_G2H(c->name), c->len);
}

#endif

struct qemu_ConvertInterfaceLuidToNameW
{
    struct qemu_syscall super;
    uint64_t luid;
    uint64_t name;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceLuidToNameW(const NET_LUID *luid, WCHAR *name, SIZE_T len)
{
    struct qemu_ConvertInterfaceLuidToNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACELUIDTONAMEW);
    call.luid = (ULONG_PTR)luid;
    call.name = (ULONG_PTR)name;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceLuidToNameW(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceLuidToNameW *c = (struct qemu_ConvertInterfaceLuidToNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceLuidToNameW(QEMU_G2H(c->luid), QEMU_G2H(c->name), c->len);
}

#endif

struct qemu_ConvertInterfaceNameToLuidA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t luid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceNameToLuidA(const char *name, NET_LUID *luid)
{
    struct qemu_ConvertInterfaceNameToLuidA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACENAMETOLUIDA);
    call.name = (ULONG_PTR)name;
    call.luid = (ULONG_PTR)luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceNameToLuidA(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceNameToLuidA *c = (struct qemu_ConvertInterfaceNameToLuidA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceNameToLuidA(QEMU_G2H(c->name), QEMU_G2H(c->luid));
}

#endif

struct qemu_ConvertInterfaceNameToLuidW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t luid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ConvertInterfaceNameToLuidW(const WCHAR *name, NET_LUID *luid)
{
    struct qemu_ConvertInterfaceNameToLuidW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTINTERFACENAMETOLUIDW);
    call.name = (ULONG_PTR)name;
    call.luid = (ULONG_PTR)luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertInterfaceNameToLuidW(struct qemu_syscall *call)
{
    struct qemu_ConvertInterfaceNameToLuidW *c = (struct qemu_ConvertInterfaceNameToLuidW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertInterfaceNameToLuidW(QEMU_G2H(c->name), QEMU_G2H(c->luid));
}

#endif

struct qemu_IPHLP_if_nametoindex
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI IF_INDEX WINAPI IPHLP_if_nametoindex(const char *name)
{
    struct qemu_IPHLP_if_nametoindex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IPHLP_IF_NAMETOINDEX);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IPHLP_if_nametoindex to Wine headers? */
extern IF_INDEX WINAPI IPHLP_if_nametoindex(const char *name);
void qemu_IPHLP_if_nametoindex(struct qemu_syscall *call)
{
    struct qemu_IPHLP_if_nametoindex *c = (struct qemu_IPHLP_if_nametoindex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_if_nametoindex(QEMU_G2H(c->name));
}

#endif

