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

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_QueryPerformanceCounter
{
    struct qemu_syscall super;
    uint64_t counter;
};

#ifdef QEMU_DLL_GUEST

/* Implementing this with a call out of the VM is probably way too expensive.
 * It probably needs the automatic update by wineserver that was discussed
 * on wine-devel at some point. */
WINBASEAPI BOOL WINAPI QueryPerformanceCounter(PLARGE_INTEGER counter)
{
    struct qemu_QueryPerformanceCounter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYPERFORMANCECOUNTER);
    call.counter = (ULONG_PTR)counter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryPerformanceCounter(struct qemu_syscall *call)
{
    struct qemu_QueryPerformanceCounter *c = (struct qemu_QueryPerformanceCounter *)call;
    WINE_TRACE("\n");
    c->super.iret = QueryPerformanceCounter(QEMU_G2H(c->counter));
}

#endif

struct qemu_QueryPerformanceFrequency
{
    struct qemu_syscall super;
    uint64_t frequency;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryPerformanceFrequency(PLARGE_INTEGER frequency)
{
    struct qemu_QueryPerformanceFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYPERFORMANCEFREQUENCY);
    call.frequency = (ULONG_PTR)frequency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryPerformanceFrequency(struct qemu_syscall *call)
{
    struct qemu_QueryPerformanceFrequency *c = (struct qemu_QueryPerformanceFrequency *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = QueryPerformanceFrequency(QEMU_G2H(c->frequency));
}

#endif

struct qemu_GetSystemInfo
{
    struct qemu_syscall super;
    uint64_t si;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetSystemInfo(LPSYSTEM_INFO si)
{
    struct qemu_GetSystemInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMINFO);
    call.si = (ULONG_PTR)si;

    qemu_syscall(&call.super);
}

#else

void qemu_GetSystemInfo(struct qemu_syscall *call)
{
    struct qemu_GetSystemInfo *c = (struct qemu_GetSystemInfo *)call;
    SYSTEM_INFO stack, *si = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    si = QEMU_G2H(c->si);
#else
    if (!c->si)
        si = NULL;
#endif

    GetSystemInfo(si);

#if GUEST_BIT != HOST_BIT
    if (c->si)
        SYSTEM_INFO_h2g(QEMU_G2H(c->si), si);
#endif
}

#endif

struct qemu_GetNativeSystemInfo
{
    struct qemu_syscall super;
    uint64_t si;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetNativeSystemInfo(LPSYSTEM_INFO si)
{
    struct qemu_GetNativeSystemInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNATIVESYSTEMINFO);
    call.si = (ULONG_PTR)si;

    qemu_syscall(&call.super);
}

#else

void qemu_GetNativeSystemInfo(struct qemu_syscall *call)
{
    struct qemu_GetNativeSystemInfo *c = (struct qemu_GetNativeSystemInfo *)call;
    SYSTEM_INFO stack, *si = &stack;

    WINE_FIXME("May need to overwrite some info.\n");
#if GUEST_BIT == HOST_BIT
    si = QEMU_G2H(c->si);
#else
    if (!c->si)
        si = NULL;
#endif

    GetNativeSystemInfo(si);

#if GUEST_BIT != HOST_BIT
    if (c->si)
        SYSTEM_INFO_h2g(QEMU_G2H(c->si), si);
#endif
}

#endif

struct qemu_IsProcessorFeaturePresent
{
    struct qemu_syscall super;
    uint64_t feature;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsProcessorFeaturePresent (DWORD feature)
{
    struct qemu_IsProcessorFeaturePresent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPROCESSORFEATUREPRESENT);
    call.feature = feature;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsProcessorFeaturePresent(struct qemu_syscall *call)
{
    struct qemu_IsProcessorFeaturePresent *c = (struct qemu_IsProcessorFeaturePresent *)call;
    /* This should probably do some translation and lookup inside qemu, but Wine's implementation
     * just returns FALSE anyway. */
    WINE_TRACE("\n");
    c->super.iret = IsProcessorFeaturePresent(c->feature);
}

#endif

struct qemu_K32GetPerformanceInfo
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32GetPerformanceInfo(PPERFORMANCE_INFORMATION info, DWORD size)
{
    struct qemu_K32GetPerformanceInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETPERFORMANCEINFO);
    call.info = (ULONG_PTR)info;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetPerformanceInfo(struct qemu_syscall *call)
{
    struct qemu_K32GetPerformanceInfo *c = (struct qemu_K32GetPerformanceInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetPerformanceInfo(QEMU_G2H(c->info), c->size);
}

#endif

struct qemu_GetLargePageMinimum
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI GetLargePageMinimum(void)
{
    struct qemu_GetLargePageMinimum call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLARGEPAGEMINIMUM);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetLargePageMinimum to Wine headers? */
extern SIZE_T WINAPI GetLargePageMinimum(void);
void qemu_GetLargePageMinimum(struct qemu_syscall *call)
{
    struct qemu_GetLargePageMinimum *c = (struct qemu_GetLargePageMinimum *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLargePageMinimum();
}

#endif

struct qemu_GetActiveProcessorGroupCount
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WORD WINAPI GetActiveProcessorGroupCount(void)
{
    struct qemu_GetActiveProcessorGroupCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACTIVEPROCESSORGROUPCOUNT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetActiveProcessorGroupCount to Wine headers? */
extern WORD WINAPI GetActiveProcessorGroupCount(void);
void qemu_GetActiveProcessorGroupCount(struct qemu_syscall *call)
{
    struct qemu_GetActiveProcessorGroupCount *c = (struct qemu_GetActiveProcessorGroupCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetActiveProcessorGroupCount();
}

#endif

struct qemu_GetActiveProcessorCount
{
    struct qemu_syscall super;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetActiveProcessorCount(WORD group)
{
    struct qemu_GetActiveProcessorCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACTIVEPROCESSORCOUNT);
    call.group = group;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetActiveProcessorCount to Wine headers? */
extern DWORD WINAPI GetActiveProcessorCount(WORD group);
void qemu_GetActiveProcessorCount(struct qemu_syscall *call)
{
    struct qemu_GetActiveProcessorCount *c = (struct qemu_GetActiveProcessorCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetActiveProcessorCount(c->group);
}

#endif

