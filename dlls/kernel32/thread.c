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

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLastError()
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETLASTERROR);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetLastError(struct qemu_syscall *call)
{
    /* FIXME: This reads the result from the host-side TEB. Ab application
     * that manually reads the TEB will read from the client-side TEB and
     * get a different result. A possible solution is to hook the host-side
     * SetLastError function and update both TEBs. */
    WINE_TRACE("\n");
    call->iret = GetLastError();
}

#endif
struct qemu_SetLastError
{
    struct qemu_syscall super;
    uint64_t error;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SetLastError(DWORD error)
{
    struct qemu_SetLastError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLASTERROR);
    call.error = error;
    qemu_syscall(&call.super);
}

#else

void qemu_SetLastError(struct qemu_syscall *call)
{
    struct qemu_SetLastError *c = (struct qemu_SetLastError *)call;
    WINE_TRACE("\n");
    SetLastError(c->error);
}

#endif
