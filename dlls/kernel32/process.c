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

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
void qemu_dll_register(const struct qemu_op *op)
{
}

#endif

struct qemu_exitprocess
{
    struct qemu_syscall super;
    uint64_t exitcode;
};

#ifdef QEMU_DLL_GUEST
WINBASEAPI DECLSPEC_NORETURN void WINAPI ExitProcess(UINT exitcode)
{
    struct qemu_exitprocess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXITPROCESS);
    call.exitcode = exitcode;
    qemu_syscall(&call.super);
    while(1); /* The syscall does not exit, but gcc does not know that. */
}
#else
void qemu_ExitProcess(struct qemu_syscall *call)
{
    struct qemu_exitprocess *c = (struct qemu_exitprocess *)call;
    ExitProcess(c->exitcode);
}

#endif
