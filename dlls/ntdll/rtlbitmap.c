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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "va_helper.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#else
typedef void *PRTL_BITMAP, *PRTL_BITMAP_RUN;
typedef const void *PCRTL_BITMAP;
#endif

struct qemu_RtlInitializeBitMap
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t lpBuff;
    uint64_t ulSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI RtlInitializeBitMap(PRTL_BITMAP lpBits, PULONG lpBuff, ULONG ulSize)
{
    struct qemu_RtlInitializeBitMap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZEBITMAP);
    call.lpBits = (ULONG_PTR)lpBits;
    call.lpBuff = (ULONG_PTR)lpBuff;
    call.ulSize = ulSize;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitializeBitMap(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeBitMap *c = (struct qemu_RtlInitializeBitMap *)call;
    WINE_FIXME("Unverified!\n");
    RtlInitializeBitMap(QEMU_G2H(c->lpBits), QEMU_G2H(c->lpBuff), c->ulSize);
}

#endif

struct qemu_RtlSetAllBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI RtlSetAllBits(PRTL_BITMAP lpBits)
{
    struct qemu_RtlSetAllBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETALLBITS);
    call.lpBits = (ULONG_PTR)lpBits;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSetAllBits(struct qemu_syscall *call)
{
    struct qemu_RtlSetAllBits *c = (struct qemu_RtlSetAllBits *)call;
    WINE_FIXME("Unverified!\n");
    RtlSetAllBits(QEMU_G2H(c->lpBits));
}

#endif

struct qemu_RtlClearAllBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI RtlClearAllBits(PRTL_BITMAP lpBits)
{
    struct qemu_RtlClearAllBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCLEARALLBITS);
    call.lpBits = (ULONG_PTR)lpBits;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlClearAllBits(struct qemu_syscall *call)
{
    struct qemu_RtlClearAllBits *c = (struct qemu_RtlClearAllBits *)call;
    WINE_FIXME("Unverified!\n");
    RtlClearAllBits(QEMU_G2H(c->lpBits));
}

#endif

struct qemu_RtlSetBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t ulCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI RtlSetBits(PRTL_BITMAP lpBits, ULONG ulStart, ULONG ulCount)
{
    struct qemu_RtlSetBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETBITS);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.ulCount = ulCount;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSetBits(struct qemu_syscall *call)
{
    struct qemu_RtlSetBits *c = (struct qemu_RtlSetBits *)call;
    WINE_FIXME("Unverified!\n");
    RtlSetBits(QEMU_G2H(c->lpBits), c->ulStart, c->ulCount);
}

#endif

struct qemu_RtlClearBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t ulCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI RtlClearBits(PRTL_BITMAP lpBits, ULONG ulStart, ULONG ulCount)
{
    struct qemu_RtlClearBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCLEARBITS);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.ulCount = ulCount;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlClearBits(struct qemu_syscall *call)
{
    struct qemu_RtlClearBits *c = (struct qemu_RtlClearBits *)call;
    WINE_FIXME("Unverified!\n");
    RtlClearBits(QEMU_G2H(c->lpBits), c->ulStart, c->ulCount);
}

#endif

struct qemu_RtlAreBitsSet
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t ulCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlAreBitsSet(PCRTL_BITMAP lpBits, ULONG ulStart, ULONG ulCount)
{
    struct qemu_RtlAreBitsSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAREBITSSET);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.ulCount = ulCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAreBitsSet(struct qemu_syscall *call)
{
    struct qemu_RtlAreBitsSet *c = (struct qemu_RtlAreBitsSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAreBitsSet(QEMU_G2H(c->lpBits), c->ulStart, c->ulCount);
}

#endif

struct qemu_RtlAreBitsClear
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t ulCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlAreBitsClear(PCRTL_BITMAP lpBits, ULONG ulStart, ULONG ulCount)
{
    struct qemu_RtlAreBitsClear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAREBITSCLEAR);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.ulCount = ulCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAreBitsClear(struct qemu_syscall *call)
{
    struct qemu_RtlAreBitsClear *c = (struct qemu_RtlAreBitsClear *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAreBitsClear(QEMU_G2H(c->lpBits), c->ulStart, c->ulCount);
}

#endif

struct qemu_RtlFindSetBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulCount;
    uint64_t ulHint;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindSetBits(PCRTL_BITMAP lpBits, ULONG ulCount, ULONG ulHint)
{
    struct qemu_RtlFindSetBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDSETBITS);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulCount = ulCount;
    call.ulHint = ulHint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindSetBits(struct qemu_syscall *call)
{
    struct qemu_RtlFindSetBits *c = (struct qemu_RtlFindSetBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindSetBits(QEMU_G2H(c->lpBits), c->ulCount, c->ulHint);
}

#endif

struct qemu_RtlFindClearBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulCount;
    uint64_t ulHint;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindClearBits(PCRTL_BITMAP lpBits, ULONG ulCount, ULONG ulHint)
{
    struct qemu_RtlFindClearBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDCLEARBITS);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulCount = ulCount;
    call.ulHint = ulHint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindClearBits(struct qemu_syscall *call)
{
    struct qemu_RtlFindClearBits *c = (struct qemu_RtlFindClearBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindClearBits(QEMU_G2H(c->lpBits), c->ulCount, c->ulHint);
}

#endif

struct qemu_RtlFindSetBitsAndClear
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulCount;
    uint64_t ulHint;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindSetBitsAndClear(PRTL_BITMAP lpBits, ULONG ulCount, ULONG ulHint)
{
    struct qemu_RtlFindSetBitsAndClear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDSETBITSANDCLEAR);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulCount = ulCount;
    call.ulHint = ulHint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindSetBitsAndClear(struct qemu_syscall *call)
{
    struct qemu_RtlFindSetBitsAndClear *c = (struct qemu_RtlFindSetBitsAndClear *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindSetBitsAndClear(QEMU_G2H(c->lpBits), c->ulCount, c->ulHint);
}

#endif

struct qemu_RtlFindClearBitsAndSet
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulCount;
    uint64_t ulHint;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindClearBitsAndSet(PRTL_BITMAP lpBits, ULONG ulCount, ULONG ulHint)
{
    struct qemu_RtlFindClearBitsAndSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDCLEARBITSANDSET);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulCount = ulCount;
    call.ulHint = ulHint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindClearBitsAndSet(struct qemu_syscall *call)
{
    struct qemu_RtlFindClearBitsAndSet *c = (struct qemu_RtlFindClearBitsAndSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindClearBitsAndSet(QEMU_G2H(c->lpBits), c->ulCount, c->ulHint);
}

#endif

struct qemu_RtlNumberOfSetBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlNumberOfSetBits(PCRTL_BITMAP lpBits)
{
    struct qemu_RtlNumberOfSetBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNUMBEROFSETBITS);
    call.lpBits = (ULONG_PTR)lpBits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlNumberOfSetBits(struct qemu_syscall *call)
{
    struct qemu_RtlNumberOfSetBits *c = (struct qemu_RtlNumberOfSetBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlNumberOfSetBits(QEMU_G2H(c->lpBits));
}

#endif

struct qemu_RtlNumberOfClearBits
{
    struct qemu_syscall super;
    uint64_t lpBits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlNumberOfClearBits(PCRTL_BITMAP lpBits)
{
    struct qemu_RtlNumberOfClearBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNUMBEROFCLEARBITS);
    call.lpBits = (ULONG_PTR)lpBits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlNumberOfClearBits(struct qemu_syscall *call)
{
    struct qemu_RtlNumberOfClearBits *c = (struct qemu_RtlNumberOfClearBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlNumberOfClearBits(QEMU_G2H(c->lpBits));
}

#endif

struct qemu_RtlFindMostSignificantBit
{
    struct qemu_syscall super;
    uint64_t ulLong;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI CCHAR WINAPI RtlFindMostSignificantBit(ULONGLONG ulLong)
{
    struct qemu_RtlFindMostSignificantBit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDMOSTSIGNIFICANTBIT);
    call.ulLong = ulLong;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindMostSignificantBit(struct qemu_syscall *call)
{
    struct qemu_RtlFindMostSignificantBit *c = (struct qemu_RtlFindMostSignificantBit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindMostSignificantBit(c->ulLong);
}

#endif

struct qemu_RtlFindLeastSignificantBit
{
    struct qemu_syscall super;
    uint64_t ulLong;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI CCHAR WINAPI RtlFindLeastSignificantBit(ULONGLONG ulLong)
{
    struct qemu_RtlFindLeastSignificantBit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDLEASTSIGNIFICANTBIT);
    call.ulLong = ulLong;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindLeastSignificantBit(struct qemu_syscall *call)
{
    struct qemu_RtlFindLeastSignificantBit *c = (struct qemu_RtlFindLeastSignificantBit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindLeastSignificantBit(c->ulLong);
}

#endif

struct qemu_RtlFindNextForwardRunSet
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t lpPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindNextForwardRunSet(PCRTL_BITMAP lpBits, ULONG ulStart, PULONG lpPos)
{
    struct qemu_RtlFindNextForwardRunSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDNEXTFORWARDRUNSET);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.lpPos = (ULONG_PTR)lpPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindNextForwardRunSet(struct qemu_syscall *call)
{
    struct qemu_RtlFindNextForwardRunSet *c = (struct qemu_RtlFindNextForwardRunSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindNextForwardRunSet(QEMU_G2H(c->lpBits), c->ulStart, QEMU_G2H(c->lpPos));
}

#endif

struct qemu_RtlFindNextForwardRunClear
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t lpPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindNextForwardRunClear(PCRTL_BITMAP lpBits, ULONG ulStart, PULONG lpPos)
{
    struct qemu_RtlFindNextForwardRunClear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDNEXTFORWARDRUNCLEAR);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.lpPos = (ULONG_PTR)lpPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindNextForwardRunClear(struct qemu_syscall *call)
{
    struct qemu_RtlFindNextForwardRunClear *c = (struct qemu_RtlFindNextForwardRunClear *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindNextForwardRunClear(QEMU_G2H(c->lpBits), c->ulStart, QEMU_G2H(c->lpPos));
}

#endif

struct qemu_RtlFindLastBackwardRunSet
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t lpPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindLastBackwardRunSet(PCRTL_BITMAP lpBits, ULONG ulStart, PULONG lpPos)
{
    struct qemu_RtlFindLastBackwardRunSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDLASTBACKWARDRUNSET);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.lpPos = (ULONG_PTR)lpPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindLastBackwardRunSet(struct qemu_syscall *call)
{
    struct qemu_RtlFindLastBackwardRunSet *c = (struct qemu_RtlFindLastBackwardRunSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindLastBackwardRunSet(QEMU_G2H(c->lpBits), c->ulStart, QEMU_G2H(c->lpPos));
}

#endif

struct qemu_RtlFindLastBackwardRunClear
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t ulStart;
    uint64_t lpPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindLastBackwardRunClear(PCRTL_BITMAP lpBits, ULONG ulStart, PULONG lpPos)
{
    struct qemu_RtlFindLastBackwardRunClear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDLASTBACKWARDRUNCLEAR);
    call.lpBits = (ULONG_PTR)lpBits;
    call.ulStart = ulStart;
    call.lpPos = (ULONG_PTR)lpPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindLastBackwardRunClear(struct qemu_syscall *call)
{
    struct qemu_RtlFindLastBackwardRunClear *c = (struct qemu_RtlFindLastBackwardRunClear *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindLastBackwardRunClear(QEMU_G2H(c->lpBits), c->ulStart, QEMU_G2H(c->lpPos));
}

#endif

struct qemu_RtlFindSetRuns
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t lpSeries;
    uint64_t ulCount;
    uint64_t bLongest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindSetRuns(PCRTL_BITMAP lpBits, PRTL_BITMAP_RUN lpSeries, ULONG ulCount, BOOLEAN bLongest)
{
    struct qemu_RtlFindSetRuns call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDSETRUNS);
    call.lpBits = (ULONG_PTR)lpBits;
    call.lpSeries = (ULONG_PTR)lpSeries;
    call.ulCount = ulCount;
    call.bLongest = bLongest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindSetRuns(struct qemu_syscall *call)
{
    struct qemu_RtlFindSetRuns *c = (struct qemu_RtlFindSetRuns *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindSetRuns(QEMU_G2H(c->lpBits), QEMU_G2H(c->lpSeries), c->ulCount, c->bLongest);
}

#endif

struct qemu_RtlFindClearRuns
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t lpSeries;
    uint64_t ulCount;
    uint64_t bLongest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindClearRuns(PCRTL_BITMAP lpBits, PRTL_BITMAP_RUN lpSeries, ULONG ulCount, BOOLEAN bLongest)
{
    struct qemu_RtlFindClearRuns call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDCLEARRUNS);
    call.lpBits = (ULONG_PTR)lpBits;
    call.lpSeries = (ULONG_PTR)lpSeries;
    call.ulCount = ulCount;
    call.bLongest = bLongest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindClearRuns(struct qemu_syscall *call)
{
    struct qemu_RtlFindClearRuns *c = (struct qemu_RtlFindClearRuns *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindClearRuns(QEMU_G2H(c->lpBits), QEMU_G2H(c->lpSeries), c->ulCount, c->bLongest);
}

#endif

struct qemu_RtlFindLongestRunSet
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t pulStart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindLongestRunSet(PCRTL_BITMAP lpBits, PULONG pulStart)
{
    struct qemu_RtlFindLongestRunSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDLONGESTRUNSET);
    call.lpBits = (ULONG_PTR)lpBits;
    call.pulStart = (ULONG_PTR)pulStart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindLongestRunSet(struct qemu_syscall *call)
{
    struct qemu_RtlFindLongestRunSet *c = (struct qemu_RtlFindLongestRunSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindLongestRunSet(QEMU_G2H(c->lpBits), QEMU_G2H(c->pulStart));
}

#endif

struct qemu_RtlFindLongestRunClear
{
    struct qemu_syscall super;
    uint64_t lpBits;
    uint64_t pulStart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlFindLongestRunClear(PCRTL_BITMAP lpBits, PULONG pulStart)
{
    struct qemu_RtlFindLongestRunClear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDLONGESTRUNCLEAR);
    call.lpBits = (ULONG_PTR)lpBits;
    call.pulStart = (ULONG_PTR)pulStart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindLongestRunClear(struct qemu_syscall *call)
{
    struct qemu_RtlFindLongestRunClear *c = (struct qemu_RtlFindLongestRunClear *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindLongestRunClear(QEMU_G2H(c->lpBits), QEMU_G2H(c->pulStart));
}

#endif

