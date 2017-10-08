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


struct qemu_WinHelpA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t lpHelpFile;
    uint64_t wCommand;
    uint64_t dwData;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI WinHelpA(HWND hWnd, LPCSTR lpHelpFile, UINT wCommand, ULONG_PTR dwData)
{
    struct qemu_WinHelpA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINHELPA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.lpHelpFile = (ULONG_PTR)lpHelpFile;
    call.wCommand = (ULONG_PTR)wCommand;
    call.dwData = (ULONG_PTR)dwData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WinHelpA(struct qemu_syscall *call)
{
    struct qemu_WinHelpA *c = (struct qemu_WinHelpA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WinHelpA(QEMU_G2H(c->hWnd), QEMU_G2H(c->lpHelpFile), c->wCommand, c->dwData);
}

#endif

struct qemu_WinHelpW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t helpFile;
    uint64_t command;
    uint64_t dwData;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI WinHelpW(HWND hWnd, LPCWSTR helpFile, UINT command, ULONG_PTR dwData)
{
    struct qemu_WinHelpW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINHELPW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.helpFile = (ULONG_PTR)helpFile;
    call.command = (ULONG_PTR)command;
    call.dwData = (ULONG_PTR)dwData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WinHelpW(struct qemu_syscall *call)
{
    struct qemu_WinHelpW *c = (struct qemu_WinHelpW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WinHelpW(QEMU_G2H(c->hWnd), QEMU_G2H(c->helpFile), c->command, c->dwData);
}

#endif

