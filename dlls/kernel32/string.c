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
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_lstrcatA
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI lstrcatA(LPSTR dst, LPCSTR src)
{
    struct qemu_lstrcatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCATA);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_lstrcatA(struct qemu_syscall *call)
{
    struct qemu_lstrcatA *c = (struct qemu_lstrcatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)lstrcatA(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_lstrcatW
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI lstrcatW(LPWSTR dst, LPCWSTR src)
{
    struct qemu_lstrcatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCATW);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_lstrcatW(struct qemu_syscall *call)
{
    struct qemu_lstrcatW *c = (struct qemu_lstrcatW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)lstrcatW(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_lstrcpyA
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI lstrcpyA(LPSTR dst, LPCSTR src)
{
    struct qemu_lstrcpyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCPYA);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_lstrcpyA(struct qemu_syscall *call)
{
    struct qemu_lstrcpyA *c = (struct qemu_lstrcpyA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)lstrcpyA(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_lstrcpyW
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI lstrcpyW(LPWSTR dst, LPCWSTR src)
{
    struct qemu_lstrcpyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCPYW);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_lstrcpyW(struct qemu_syscall *call)
{
    struct qemu_lstrcpyW *c = (struct qemu_lstrcpyW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)lstrcpyW(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_lstrcpynA
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI lstrcpynA(LPSTR dst, LPCSTR src, INT n)
{
    struct qemu_lstrcpynA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCPYNA);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = n;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_lstrcpynA(struct qemu_syscall *call)
{
    struct qemu_lstrcpynA *c = (struct qemu_lstrcpynA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)lstrcpynA(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n);
}

#endif

struct qemu_lstrcpynW
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI lstrcpynW(LPWSTR dst, LPCWSTR src, INT n)
{
    struct qemu_lstrcpynW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCPYNW);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = n;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_lstrcpynW(struct qemu_syscall *call)
{
    struct qemu_lstrcpynW *c = (struct qemu_lstrcpynW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)lstrcpynW(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n);
}

#endif

struct qemu_lstrlenA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI lstrlenA(LPCSTR str)
{
    struct qemu_lstrlenA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRLENA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrlenA(struct qemu_syscall *call)
{
    struct qemu_lstrlenA *c = (struct qemu_lstrlenA *)call;
    WINE_TRACE("\n");
    c->super.iret = lstrlenA(QEMU_G2H(c->str));
}

#endif

struct qemu_lstrlenW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI lstrlenW(LPCWSTR str)
{
    struct qemu_lstrlenW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRLENW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrlenW(struct qemu_syscall *call)
{
    struct qemu_lstrlenW *c = (struct qemu_lstrlenW *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = lstrlenW(QEMU_G2H(c->str));
}

#endif

