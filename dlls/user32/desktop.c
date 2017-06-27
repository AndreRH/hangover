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
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_PaintDesktop
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PaintDesktop(HDC hdc)
{
    struct qemu_PaintDesktop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PAINTDESKTOP);
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PaintDesktop(struct qemu_syscall *call)
{
    struct qemu_PaintDesktop *c = (struct qemu_PaintDesktop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PaintDesktop(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetDeskWallPaper
{
    struct qemu_syscall super;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetDeskWallPaper(LPCSTR filename)
{
    struct qemu_SetDeskWallPaper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDESKWALLPAPER);
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDeskWallPaper(struct qemu_syscall *call)
{
    struct qemu_SetDeskWallPaper *c = (struct qemu_SetDeskWallPaper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDeskWallPaper(QEMU_G2H(c->filename));
}

#endif

