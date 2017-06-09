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

struct qemu__lock
{
    struct qemu_syscall super;
    uint64_t locknum;
};

#ifdef QEMU_DLL_GUEST

void CDECL _lock(int locknum)
{
    struct qemu__lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCK);
    call.locknum = (uint64_t)locknum;

    qemu_syscall(&call.super);
}

#else

void qemu__lock(struct qemu_syscall *call)
{
    struct qemu__lock *c = (struct qemu__lock *)call;
    WINE_TRACE("\n");
    p__lock(c->locknum);
}

#endif

#ifdef QEMU_DLL_GUEST

void CDECL _unlock(int locknum)
{
    struct qemu__lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLOCK);
    call.locknum = (uint64_t)locknum;

    qemu_syscall(&call.super);
}

#else

void qemu__unlock(struct qemu_syscall *call)
{
    struct qemu__lock *c = (struct qemu__lock *)call;
    WINE_TRACE("\n");
    p__unlock(c->locknum);
}

#endif
