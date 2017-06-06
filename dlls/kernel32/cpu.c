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

struct qemu_QueryPerformanceCounter
{
    struct qemu_syscall super;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *count)
{
    struct qemu_QueryPerformanceCounter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYPERFORMANCECOUNTER);
    call.count = (uint64_t)count;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_QueryPerformanceCounter(struct qemu_syscall *call)
{
    struct qemu_QueryPerformanceCounter *c = (struct qemu_QueryPerformanceCounter *)call;
    WINE_TRACE("\n");
    c->super.iret = QueryPerformanceCounter(QEMU_G2H(c->count));
}

#endif
