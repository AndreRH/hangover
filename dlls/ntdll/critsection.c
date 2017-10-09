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
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlInitializeCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlInitializeCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlInitializeCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZECRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitializeCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeCriticalSection *c = (struct qemu_RtlInitializeCriticalSection *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlInitializeCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlInitializeCriticalSectionAndSpinCount
{
    struct qemu_syscall super;
    uint64_t crit;
    uint64_t spincount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlInitializeCriticalSectionAndSpinCount(RTL_CRITICAL_SECTION *crit, ULONG spincount)
{
    struct qemu_RtlInitializeCriticalSectionAndSpinCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZECRITICALSECTIONANDSPINCOUNT);
    call.crit = (ULONG_PTR)crit;
    call.spincount = (ULONG_PTR)spincount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitializeCriticalSectionAndSpinCount(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeCriticalSectionAndSpinCount *c = (struct qemu_RtlInitializeCriticalSectionAndSpinCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlInitializeCriticalSectionAndSpinCount(QEMU_G2H(c->crit), c->spincount);
}

#endif

struct qemu_RtlInitializeCriticalSectionEx
{
    struct qemu_syscall super;
    uint64_t crit;
    uint64_t spincount;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlInitializeCriticalSectionEx(RTL_CRITICAL_SECTION *crit, ULONG spincount, ULONG flags)
{
    struct qemu_RtlInitializeCriticalSectionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZECRITICALSECTIONEX);
    call.crit = (ULONG_PTR)crit;
    call.spincount = (ULONG_PTR)spincount;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitializeCriticalSectionEx(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeCriticalSectionEx *c = (struct qemu_RtlInitializeCriticalSectionEx *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlInitializeCriticalSectionEx(QEMU_G2H(c->crit), c->spincount, c->flags);
}

#endif

struct qemu_RtlSetCriticalSectionSpinCount
{
    struct qemu_syscall super;
    uint64_t crit;
    uint64_t spincount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlSetCriticalSectionSpinCount(RTL_CRITICAL_SECTION *crit, ULONG spincount)
{
    struct qemu_RtlSetCriticalSectionSpinCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETCRITICALSECTIONSPINCOUNT);
    call.crit = (ULONG_PTR)crit;
    call.spincount = (ULONG_PTR)spincount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetCriticalSectionSpinCount(struct qemu_syscall *call)
{
    struct qemu_RtlSetCriticalSectionSpinCount *c = (struct qemu_RtlSetCriticalSectionSpinCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetCriticalSectionSpinCount(QEMU_G2H(c->crit), c->spincount);
}

#endif

struct qemu_RtlDeleteCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeleteCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlDeleteCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETECRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeleteCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteCriticalSection *c = (struct qemu_RtlDeleteCriticalSection *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlDeleteCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlpWaitForCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlpWaitForCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlpWaitForCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLPWAITFORCRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlpWaitForCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlpWaitForCriticalSection *c = (struct qemu_RtlpWaitForCriticalSection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlpWaitForCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlpUnWaitCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlpUnWaitCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlpUnWaitCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLPUNWAITCRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlpUnWaitCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlpUnWaitCriticalSection *c = (struct qemu_RtlpUnWaitCriticalSection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlpUnWaitCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlEnterCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlEnterCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlEnterCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLENTERCRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEnterCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlEnterCriticalSection *c = (struct qemu_RtlEnterCriticalSection *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlEnterCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlTryEnterCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlTryEnterCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlTryEnterCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTRYENTERCRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlTryEnterCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlTryEnterCriticalSection *c = (struct qemu_RtlTryEnterCriticalSection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlTryEnterCriticalSection(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlIsCriticalSectionLocked
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlIsCriticalSectionLocked(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlIsCriticalSectionLocked call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISCRITICALSECTIONLOCKED);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsCriticalSectionLocked(struct qemu_syscall *call)
{
    struct qemu_RtlIsCriticalSectionLocked *c = (struct qemu_RtlIsCriticalSectionLocked *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsCriticalSectionLocked(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlIsCriticalSectionLockedByThread
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlIsCriticalSectionLockedByThread(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlIsCriticalSectionLockedByThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISCRITICALSECTIONLOCKEDBYTHREAD);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsCriticalSectionLockedByThread(struct qemu_syscall *call)
{
    struct qemu_RtlIsCriticalSectionLockedByThread *c = (struct qemu_RtlIsCriticalSectionLockedByThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsCriticalSectionLockedByThread(QEMU_G2H(c->crit));
}

#endif

struct qemu_RtlLeaveCriticalSection
{
    struct qemu_syscall super;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlLeaveCriticalSection(RTL_CRITICAL_SECTION *crit)
{
    struct qemu_RtlLeaveCriticalSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLEAVECRITICALSECTION);
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLeaveCriticalSection(struct qemu_syscall *call)
{
    struct qemu_RtlLeaveCriticalSection *c = (struct qemu_RtlLeaveCriticalSection *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlLeaveCriticalSection(QEMU_G2H(c->crit));
}

#endif

