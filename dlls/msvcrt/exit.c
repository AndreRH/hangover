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
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu_exit
{
    struct qemu_syscall super;
    uint64_t code;
};


#ifdef QEMU_DLL_GUEST

CDECL DECLSPEC_NORETURN void __MINGW_NOTHROW MSVCRT_exit(int code)
{
    struct qemu_exit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXIT);
    call.code = code;

    qemu_syscall(&call.super);

    /* The syscall does not exit, but gcc does not know that. */
    while(1);
}

#else

void qemu_exit(struct qemu_syscall *call)
{
    struct qemu_exit *c = (struct qemu_exit *)call;
    WINE_TRACE("\n");
    p_exit(c->code);
}

#endif
