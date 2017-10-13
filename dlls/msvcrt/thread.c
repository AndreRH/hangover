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

struct qemu__endthread
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__endthread(void)
{
    struct qemu__endthread call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ENDTHREAD);

    qemu_syscall(&call.super);
}

#else

void qemu__endthread(struct qemu_syscall *call)
{
    struct qemu__endthread *c = (struct qemu__endthread *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__endthread();
}

#endif

struct qemu__endthreadex
{
    struct qemu_syscall super;
    uint64_t retval;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__endthreadex(unsigned int retval)
{
    struct qemu__endthreadex call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ENDTHREADEX);
    call.retval = retval;

    qemu_syscall(&call.super);
}

#else

void qemu__endthreadex(struct qemu_syscall *call)
{
    struct qemu__endthreadex *c = (struct qemu__endthreadex *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__endthreadex(c->retval);
}

#endif

struct qemu__beginthread
{
    struct qemu_syscall super;
    uint64_t start_address;
    uint64_t arglist;
};

#ifdef QEMU_DLL_GUEST

uintptr_t CDECL MSVCRT__beginthread(MSVCRT__beginthread_start_routine_t start_address, void *arglist)
{
    struct qemu__beginthread call;
    call.super.id = QEMU_SYSCALL_ID(CALL__BEGINTHREAD);
    call.start_address = (ULONG_PTR)start_address;
    call.arglist = (ULONG_PTR)arglist;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__beginthread(struct qemu_syscall *call)
{
    struct qemu__beginthread *c = (struct qemu__beginthread *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__beginthread(QEMU_G2H(c->start_address), QEMU_G2H(c->arglist));
}

#endif

struct qemu__beginthreadex
{
    struct qemu_syscall super;
    uint64_t security;
    uint64_t stack_size;
    uint64_t start_address;
    uint64_t arglist;
    uint64_t initflag;
    uint64_t thrdaddr;
};

#ifdef QEMU_DLL_GUEST

uintptr_t CDECL MSVCRT__beginthreadex(void *security, unsigned int stack_size, MSVCRT__beginthreadex_start_routine_t start_address, void *arglist, unsigned int initflag, unsigned int *thrdaddr)
{
    struct qemu__beginthreadex call;
    call.super.id = QEMU_SYSCALL_ID(CALL__BEGINTHREADEX);
    call.security = (ULONG_PTR)security;
    call.stack_size = stack_size;
    call.start_address = (ULONG_PTR)start_address;
    call.arglist = (ULONG_PTR)arglist;
    call.initflag = initflag;
    call.thrdaddr = (ULONG_PTR)thrdaddr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__beginthreadex(struct qemu_syscall *call)
{
    struct qemu__beginthreadex *c = (struct qemu__beginthreadex *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__beginthreadex(QEMU_G2H(c->security), c->stack_size, QEMU_G2H(c->start_address), QEMU_G2H(c->arglist), c->initflag, QEMU_G2H(c->thrdaddr));
}

#endif

struct qemu__getptd
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

thread_data_t* CDECL MSVCRT__getptd(void)
{
    struct qemu__getptd call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETPTD);

    qemu_syscall(&call.super);

    return (thread_data_t *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__getptd(struct qemu_syscall *call)
{
    struct qemu__getptd *c = (struct qemu__getptd *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__getptd());
}

#endif

