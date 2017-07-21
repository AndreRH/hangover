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

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu__strtime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__strtime(char *time)
{
    struct qemu__strtime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTIME);
    call.time = (uint64_t)time;

    qemu_syscall(&call.super);

    return (char *)call.super.iret;
}

#else

void qemu__strtime(struct qemu_syscall *call)
{
    struct qemu__strtime *c = (struct qemu__strtime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strtime(QEMU_G2H(c->time)));
}

#endif

struct qemu__strdate
{
    struct qemu_syscall super;
    uint64_t date;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__strdate(char *date)
{
    struct qemu__strdate call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRDATE);
    call.date = (uint64_t)date;

    qemu_syscall(&call.super);

    return (char *)call.super.iret;
}

#else

void qemu__strdate(struct qemu_syscall *call)
{
    struct qemu__strdate *c = (struct qemu__strdate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strdate(QEMU_G2H(c->date)));
}

#endif
