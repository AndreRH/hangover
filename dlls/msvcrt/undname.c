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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif


struct qemu___unDNameEx
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t mangled;
    uint64_t buflen;
    uint64_t memget;
    uint64_t memfree;
    uint64_t unknown;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL __unDNameEx(char* buffer, const char* mangled, int buflen, malloc_func_t memget, free_func_t memfree, void* unknown, unsigned short int flags)
{
    struct qemu___unDNameEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL___UNDNAMEEX);
    call.buffer = (ULONG_PTR)buffer;
    call.mangled = (ULONG_PTR)mangled;
    call.buflen = buflen;
    call.memget = (ULONG_PTR)memget;
    call.memfree = (ULONG_PTR)memfree;
    call.unknown = (ULONG_PTR)unknown;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___unDNameEx(struct qemu_syscall *call)
{
    struct qemu___unDNameEx *c = (struct qemu___unDNameEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___unDNameEx(QEMU_G2H(c->buffer), QEMU_G2H(c->mangled), c->buflen, QEMU_G2H(c->memget), QEMU_G2H(c->memfree), QEMU_G2H(c->unknown), c->flags));
}

#endif

struct qemu___unDName
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t mangled;
    uint64_t buflen;
    uint64_t memget;
    uint64_t memfree;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL __unDName(char* buffer, const char* mangled, int buflen, malloc_func_t memget, free_func_t memfree, unsigned short int flags)
{
    struct qemu___unDName call;
    call.super.id = QEMU_SYSCALL_ID(CALL___UNDNAME);
    call.buffer = (ULONG_PTR)buffer;
    call.mangled = (ULONG_PTR)mangled;
    call.buflen = buflen;
    call.memget = (ULONG_PTR)memget;
    call.memfree = (ULONG_PTR)memfree;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___unDName(struct qemu_syscall *call)
{
    struct qemu___unDName *c = (struct qemu___unDName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___unDName(QEMU_G2H(c->buffer), QEMU_G2H(c->mangled), c->buflen, QEMU_G2H(c->memget), QEMU_G2H(c->memfree), c->flags));
}

#endif

