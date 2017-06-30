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
#include "comdlg32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);
#endif


struct qemu_FindTextA
{
    struct qemu_syscall super;
    uint64_t pfr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI FindTextA(LPFINDREPLACEA pfr)
{
    struct qemu_FindTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDTEXTA);
    call.pfr = (uint64_t)pfr;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_FindTextA(struct qemu_syscall *call)
{
    struct qemu_FindTextA *c = (struct qemu_FindTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindTextA(QEMU_G2H(c->pfr));
}

#endif

struct qemu_ReplaceTextA
{
    struct qemu_syscall super;
    uint64_t pfr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI ReplaceTextA(LPFINDREPLACEA pfr)
{
    struct qemu_ReplaceTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPLACETEXTA);
    call.pfr = (uint64_t)pfr;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_ReplaceTextA(struct qemu_syscall *call)
{
    struct qemu_ReplaceTextA *c = (struct qemu_ReplaceTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ReplaceTextA(QEMU_G2H(c->pfr));
}

#endif

struct qemu_FindTextW
{
    struct qemu_syscall super;
    uint64_t pfr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI FindTextW(LPFINDREPLACEW pfr)
{
    struct qemu_FindTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDTEXTW);
    call.pfr = (uint64_t)pfr;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_FindTextW(struct qemu_syscall *call)
{
    struct qemu_FindTextW *c = (struct qemu_FindTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindTextW(QEMU_G2H(c->pfr));
}

#endif

struct qemu_ReplaceTextW
{
    struct qemu_syscall super;
    uint64_t pfr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI ReplaceTextW(LPFINDREPLACEW pfr)
{
    struct qemu_ReplaceTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPLACETEXTW);
    call.pfr = (uint64_t)pfr;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_ReplaceTextW(struct qemu_syscall *call)
{
    struct qemu_ReplaceTextW *c = (struct qemu_ReplaceTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ReplaceTextW(QEMU_G2H(c->pfr));
}

#endif

