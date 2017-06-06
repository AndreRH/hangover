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

struct qemu_GetSystemTimeAsFileTime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI GetSystemTimeAsFileTime(FILETIME *time)
{
    struct qemu_GetSystemTimeAsFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMTIMEASFILETIME);
    call.time = (uint64_t)time;
    qemu_syscall(&call.super);
}

#else

void qemu_GetSystemTimeAsFileTime(struct qemu_syscall *call)
{
    struct qemu_GetSystemTimeAsFileTime *c = (struct qemu_GetSystemTimeAsFileTime *)call;
    WINE_TRACE("\n");
    GetSystemTimeAsFileTime(QEMU_G2H(c->time));
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTickCount(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETTICKCOUNT);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetTickCount(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetTickCount();
}

#endif
