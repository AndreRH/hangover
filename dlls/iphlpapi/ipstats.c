/*
 * Copyright 2017 André Hentschel
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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_iphlpapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_iphlpapi);
#endif


struct qemu_GetIcmpStatistics
{
    struct qemu_syscall super;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIcmpStatistics(PMIB_ICMP stats)
{
    struct qemu_GetIcmpStatistics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETICMPSTATISTICS);
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIcmpStatistics(struct qemu_syscall *call)
{
    struct qemu_GetIcmpStatistics *c = (struct qemu_GetIcmpStatistics *)call;
    /* MIB_ICM has the same size on 32 and 64 bit .*/
    WINE_TRACE("\n");
    c->super.iret = GetIcmpStatistics(QEMU_G2H(c->stats));
}

#endif

struct qemu_GetIcmpStatisticsEx
{
    struct qemu_syscall super;
    uint64_t stats;
    uint64_t family;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIcmpStatisticsEx(PMIB_ICMP_EX stats, DWORD family)
{
    struct qemu_GetIcmpStatisticsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETICMPSTATISTICSEX);
    call.stats = (ULONG_PTR)stats;
    call.family = (ULONG_PTR)family;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetIcmpStatisticsEx to Wine headers? */
extern DWORD WINAPI GetIcmpStatisticsEx(PMIB_ICMP_EX stats, DWORD family);
void qemu_GetIcmpStatisticsEx(struct qemu_syscall *call)
{
    struct qemu_GetIcmpStatisticsEx *c = (struct qemu_GetIcmpStatisticsEx *)call;
    /* MIB_ICMP_EX has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIcmpStatisticsEx(QEMU_G2H(c->stats), c->family);
}

#endif

struct qemu_GetIpStatisticsEx
{
    struct qemu_syscall super;
    uint64_t stats;
    uint64_t family;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIpStatisticsEx(PMIB_IPSTATS stats, DWORD family)
{
    struct qemu_GetIpStatisticsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIPSTATISTICSEX);
    call.stats = (ULONG_PTR)stats;
    call.family = (ULONG_PTR)family;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIpStatisticsEx(struct qemu_syscall *call)
{
    struct qemu_GetIpStatisticsEx *c = (struct qemu_GetIpStatisticsEx *)call;
    /* MIB_IPSTATS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIpStatisticsEx(QEMU_G2H(c->stats), c->family);
}

#endif

struct qemu_GetIpStatistics
{
    struct qemu_syscall super;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetIpStatistics(PMIB_IPSTATS stats)
{
    struct qemu_GetIpStatistics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETIPSTATISTICS);
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetIpStatistics(struct qemu_syscall *call)
{
    struct qemu_GetIpStatistics *c = (struct qemu_GetIpStatistics *)call;
    /* MIB_IPSTATS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetIpStatistics(QEMU_G2H(c->stats));
}

#endif

struct qemu_GetTcpStatisticsEx
{
    struct qemu_syscall super;
    uint64_t stats;
    uint64_t family;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTcpStatisticsEx(PMIB_TCPSTATS stats, DWORD family)
{
    struct qemu_GetTcpStatisticsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTCPSTATISTICSEX);
    call.stats = (ULONG_PTR)stats;
    call.family = (ULONG_PTR)family;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTcpStatisticsEx(struct qemu_syscall *call)
{
    struct qemu_GetTcpStatisticsEx *c = (struct qemu_GetTcpStatisticsEx *)call;
    /* MIB_TCPSTATS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetTcpStatisticsEx(QEMU_G2H(c->stats), c->family);
}

#endif

struct qemu_GetTcpStatistics
{
    struct qemu_syscall super;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTcpStatistics(PMIB_TCPSTATS stats)
{
    struct qemu_GetTcpStatistics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTCPSTATISTICS);
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTcpStatistics(struct qemu_syscall *call)
{
    struct qemu_GetTcpStatistics *c = (struct qemu_GetTcpStatistics *)call;
    /* MIB_TCPSTATS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetTcpStatistics(QEMU_G2H(c->stats));
}

#endif

struct qemu_GetUdpStatisticsEx
{
    struct qemu_syscall super;
    uint64_t stats;
    uint64_t family;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetUdpStatisticsEx(PMIB_UDPSTATS stats, DWORD family)
{
    struct qemu_GetUdpStatisticsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUDPSTATISTICSEX);
    call.stats = (ULONG_PTR)stats;
    call.family = (ULONG_PTR)family;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUdpStatisticsEx(struct qemu_syscall *call)
{
    struct qemu_GetUdpStatisticsEx *c = (struct qemu_GetUdpStatisticsEx *)call;
    /* MIB_UDPSTATS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetUdpStatisticsEx(QEMU_G2H(c->stats), c->family);
}

#endif

struct qemu_GetUdpStatistics
{
    struct qemu_syscall super;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetUdpStatistics(PMIB_UDPSTATS stats)
{
    struct qemu_GetUdpStatistics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUDPSTATISTICS);
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUdpStatistics(struct qemu_syscall *call)
{
    struct qemu_GetUdpStatistics *c = (struct qemu_GetUdpStatistics *)call;
    /* MIB_UDPSTATS has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = GetUdpStatistics(QEMU_G2H(c->stats));
}

#endif

struct qemu_AllocateAndGetIpForwardTableFromStack
{
    struct qemu_syscall super;
    uint64_t ppIpForwardTable;
    uint64_t bOrder;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AllocateAndGetIpForwardTableFromStack(PMIB_IPFORWARDTABLE *ppIpForwardTable, BOOL bOrder, HANDLE heap, DWORD flags)
{
    struct qemu_AllocateAndGetIpForwardTableFromStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDGETIPFORWARDTABLEFROMSTACK);
    call.ppIpForwardTable = (ULONG_PTR)ppIpForwardTable;
    call.bOrder = (ULONG_PTR)bOrder;
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateAndGetIpForwardTableFromStack to Wine headers? */
extern DWORD WINAPI AllocateAndGetIpForwardTableFromStack(PMIB_IPFORWARDTABLE *ppIpForwardTable, BOOL bOrder, HANDLE heap, DWORD flags);
void qemu_AllocateAndGetIpForwardTableFromStack(struct qemu_syscall *call)
{
    struct qemu_AllocateAndGetIpForwardTableFromStack *c = (struct qemu_AllocateAndGetIpForwardTableFromStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndGetIpForwardTableFromStack(QEMU_G2H(c->ppIpForwardTable), c->bOrder, QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_AllocateAndGetIpNetTableFromStack
{
    struct qemu_syscall super;
    uint64_t ppIpNetTable;
    uint64_t bOrder;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AllocateAndGetIpNetTableFromStack(PMIB_IPNETTABLE *ppIpNetTable, BOOL bOrder, HANDLE heap, DWORD flags)
{
    struct qemu_AllocateAndGetIpNetTableFromStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDGETIPNETTABLEFROMSTACK);
    call.ppIpNetTable = (ULONG_PTR)ppIpNetTable;
    call.bOrder = (ULONG_PTR)bOrder;
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateAndGetIpNetTableFromStack to Wine headers? */
extern DWORD WINAPI AllocateAndGetIpNetTableFromStack(PMIB_IPNETTABLE *ppIpNetTable, BOOL bOrder, HANDLE heap, DWORD flags);
void qemu_AllocateAndGetIpNetTableFromStack(struct qemu_syscall *call)
{
    struct qemu_AllocateAndGetIpNetTableFromStack *c = (struct qemu_AllocateAndGetIpNetTableFromStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndGetIpNetTableFromStack(QEMU_G2H(c->ppIpNetTable), c->bOrder, QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_AllocateAndGetTcpTableFromStack
{
    struct qemu_syscall super;
    uint64_t ppTcpTable;
    uint64_t bOrder;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AllocateAndGetTcpTableFromStack(PMIB_TCPTABLE *ppTcpTable, BOOL bOrder, HANDLE heap, DWORD flags)
{
    struct qemu_AllocateAndGetTcpTableFromStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDGETTCPTABLEFROMSTACK);
    call.ppTcpTable = (ULONG_PTR)ppTcpTable;
    call.bOrder = (ULONG_PTR)bOrder;
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateAndGetTcpTableFromStack to Wine headers? */
extern DWORD WINAPI AllocateAndGetTcpTableFromStack(PMIB_TCPTABLE *ppTcpTable, BOOL bOrder, HANDLE heap, DWORD flags);
void qemu_AllocateAndGetTcpTableFromStack(struct qemu_syscall *call)
{
    struct qemu_AllocateAndGetTcpTableFromStack *c = (struct qemu_AllocateAndGetTcpTableFromStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndGetTcpTableFromStack(QEMU_G2H(c->ppTcpTable), c->bOrder, QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_AllocateAndGetUdpTableFromStack
{
    struct qemu_syscall super;
    uint64_t ppUdpTable;
    uint64_t bOrder;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI AllocateAndGetUdpTableFromStack(PMIB_UDPTABLE *ppUdpTable, BOOL bOrder, HANDLE heap, DWORD flags)
{
    struct qemu_AllocateAndGetUdpTableFromStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDGETUDPTABLEFROMSTACK);
    call.ppUdpTable = (ULONG_PTR)ppUdpTable;
    call.bOrder = (ULONG_PTR)bOrder;
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateAndGetUdpTableFromStack to Wine headers? */
extern DWORD WINAPI AllocateAndGetUdpTableFromStack(PMIB_UDPTABLE *ppUdpTable, BOOL bOrder, HANDLE heap, DWORD flags);
void qemu_AllocateAndGetUdpTableFromStack(struct qemu_syscall *call)
{
    struct qemu_AllocateAndGetUdpTableFromStack *c = (struct qemu_AllocateAndGetUdpTableFromStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndGetUdpTableFromStack(QEMU_G2H(c->ppUdpTable), c->bOrder, QEMU_G2H(c->heap), c->flags);
}

#endif

