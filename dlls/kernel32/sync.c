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

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
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

WINBASEAPI void WINAPI DeleteCriticalSection(CRITICAL_SECTION *section)
{
    struct qemu_CriticalSectionOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETECRITICALSECTION);
    call.section = (uint64_t)section;
    qemu_syscall(&call.super);
}

#else

void qemu_DeleteCriticalSection(struct qemu_syscall *call)
{
    struct qemu_CriticalSectionOp *c = (struct qemu_CriticalSectionOp *)call;
    WINE_TRACE("\n");
    DeleteCriticalSection(QEMU_G2H(c->section));
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI EnterCriticalSection(CRITICAL_SECTION *section)
{
    struct qemu_CriticalSectionOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENTERCRITICALSECTION);
    call.section = (uint64_t)section;
    qemu_syscall(&call.super);
}

#else

void qemu_EnterCriticalSection(struct qemu_syscall *call)
{
    struct qemu_CriticalSectionOp *c = (struct qemu_CriticalSectionOp *)call;
    WINE_TRACE("\n");
    EnterCriticalSection(QEMU_G2H(c->section));
}

#endif

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

WINBASEAPI void WINAPI LeaveCriticalSection(CRITICAL_SECTION *section)
{
    struct qemu_CriticalSectionOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LEAVECRITICALSECTION);
    call.section = (uint64_t)section;
    qemu_syscall(&call.super);
}

#else

void qemu_LeaveCriticalSection(struct qemu_syscall *call)
{
    struct qemu_CriticalSectionOp *c = (struct qemu_CriticalSectionOp *)call;
    WINE_TRACE("\n");
    LeaveCriticalSection(QEMU_G2H(c->section));
}

#endif
