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
#include <commctrl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif

struct qemu_SmoothScrollWindow
{
    struct qemu_syscall super;
    uint64_t smooth;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SmoothScrollWindow(const SMOOTHSCROLLSTRUCT *smooth)
{
    struct qemu_SmoothScrollWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SMOOTHSCROLLWINDOW);
    call.smooth = (ULONG_PTR)smooth;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI SmoothScrollWindow(const SMOOTHSCROLLSTRUCT *smooth);
void qemu_SmoothScrollWindow(struct qemu_syscall *call)
{
    struct qemu_SmoothScrollWindow *c = (struct qemu_SmoothScrollWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_SmoothScrollWindow(QEMU_G2H(c->smooth));
}

#endif

