/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CreateEventW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t manual_reset;
    uint64_t initial_state;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateEventW( SECURITY_ATTRIBUTES *sa, BOOL manual_reset,
                                       BOOL initial_state, LPCWSTR name )
{
    struct qemu_CreateEventW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEEVENTW);
    call.sa = (uint64_t)sa;
    call.manual_reset = (uint64_t)manual_reset;
    call.initial_state = (uint64_t)initial_state;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateEventW(struct qemu_syscall *call)
{
    struct qemu_CreateEventW *c = (struct qemu_CreateEventW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateEventW(QEMU_G2H(c->sa), c->manual_reset, c->initial_state, QEMU_G2H(c->name));
}

#endif

/* Critical section already destroy the hope of 32 bit emulation in a 64 bit emulator
 * and 64 bit libs. The structure is allocated by the guest app and contains pointers,
 * so it will have a different size in 32 and 64 bit.
 *
 * There are a few options around this for this particular data structure. The best seems
 * to reimplement them ourselves instead of calling Wine and using the LockSemaphore
 * entry to store a pointer or handle to a Win64 sync object. Because we need to limit
 * the address space anyway we can fit this pointer into the 32 bit HANDLE. */
struct qemu_CriticalSectionOp
{
    struct qemu_syscall super;
    uint64_t section;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI InitializeCriticalSection(CRITICAL_SECTION *section)
{
    struct qemu_CriticalSectionOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZECRITICALSECTION);
    call.section = (uint64_t)section;
    qemu_syscall(&call.super);
}

#else

void qemu_InitializeCriticalSection(struct qemu_syscall *call)
{
    struct qemu_CriticalSectionOp *c = (struct qemu_CriticalSectionOp *)call;
    WINE_TRACE("\n");
    InitializeCriticalSection(QEMU_G2H(c->section));
}

#endif

#ifdef QEMU_DLL_GUEST
/* For now the main purpose of this one is to force this library to import ntdll for the RVA Forwards. */
NTSYSAPI NTSTATUS WINAPI RtlInitializeCriticalSectionEx(RTL_CRITICAL_SECTION *,ULONG,ULONG);
WINBASEAPI BOOL WINAPI InitializeCriticalSectionEx(CRITICAL_SECTION *section, DWORD spincount, DWORD flags)
{
    return !RtlInitializeCriticalSectionEx(section, spincount, flags);
}
#endif

struct qemu_Sleep
{
    struct qemu_syscall super;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI Sleep(DWORD timeout)
{
    struct qemu_Sleep call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SLEEP);
    call.timeout = (uint64_t)timeout;
    qemu_syscall(&call.super);
}

#else

void qemu_Sleep(struct qemu_syscall *call)
{
    struct qemu_Sleep *c = (struct qemu_Sleep *)call;
    WINE_TRACE("\n");
    Sleep(c->timeout);
}

#endif
