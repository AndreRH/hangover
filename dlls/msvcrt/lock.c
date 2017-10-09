/*
 * Copyright 2017 André Hentschel
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
#include "qemu_msvcrt.h"

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
    call.locknum = locknum;

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

struct qemu__unlock
{
    struct qemu_syscall super;
    uint64_t locknum;
};

#ifdef QEMU_DLL_GUEST

void CDECL _unlock(int locknum)
{
    struct qemu__unlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLOCK);
    call.locknum = locknum;

    qemu_syscall(&call.super);
}

#else

void qemu__unlock(struct qemu_syscall *call)
{
    struct qemu__unlock *c = (struct qemu__unlock *)call;
    WINE_TRACE("\n");
    p__unlock(c->locknum);
}

#endif

struct qemu_SpinCount__Value
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL SpinCount__Value(void)
{
    struct qemu_SpinCount__Value call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SPINCOUNT__VALUE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SpinCount__Value(struct qemu_syscall *call)
{
    struct qemu_SpinCount__Value *c = (struct qemu_SpinCount__Value *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_SpinCount__Value();
}

#endif

struct qemu__GetConcurrency
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL _GetConcurrency(void)
{
    struct qemu__GetConcurrency call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETCONCURRENCY);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__GetConcurrency(struct qemu_syscall *call)
{
    struct qemu__GetConcurrency *c = (struct qemu__GetConcurrency *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__GetConcurrency();
}

#endif

struct qemu_event_wait_for_multiple
{
    struct qemu_syscall super;
    uint64_t events;
    uint64_t count;
    uint64_t wait_all;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL event_wait_for_multiple(void **events, size_t count, BOOL wait_all, unsigned int timeout)
{
    struct qemu_event_wait_for_multiple call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EVENT_WAIT_FOR_MULTIPLE);
    call.events = (ULONG_PTR)events;
    call.count = count;
    call.wait_all = wait_all;
    call.timeout = timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_event_wait_for_multiple(struct qemu_syscall *call)
{
    struct qemu_event_wait_for_multiple *c = (struct qemu_event_wait_for_multiple *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_event_wait_for_multiple(QEMU_G2H(c->events), c->count, c->wait_all, c->timeout);
}

#endif

struct qemu__Lock_shared_ptr_spin_lock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _Lock_shared_ptr_spin_lock(void)
{
    struct qemu__Lock_shared_ptr_spin_lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCK_SHARED_PTR_SPIN_LOCK);

    qemu_syscall(&call.super);
}

#else

void qemu__Lock_shared_ptr_spin_lock(struct qemu_syscall *call)
{
    struct qemu__Lock_shared_ptr_spin_lock *c = (struct qemu__Lock_shared_ptr_spin_lock *)call;
    WINE_FIXME("Unverified!\n");
    p__Lock_shared_ptr_spin_lock();
}

#endif

struct qemu__Unlock_shared_ptr_spin_lock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _Unlock_shared_ptr_spin_lock(void)
{
    struct qemu__Unlock_shared_ptr_spin_lock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLOCK_SHARED_PTR_SPIN_LOCK);

    qemu_syscall(&call.super);
}

#else

void qemu__Unlock_shared_ptr_spin_lock(struct qemu_syscall *call)
{
    struct qemu__Unlock_shared_ptr_spin_lock *c = (struct qemu__Unlock_shared_ptr_spin_lock *)call;
    WINE_FIXME("Unverified!\n");
    p__Unlock_shared_ptr_spin_lock();
}

#endif

