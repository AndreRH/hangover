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
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_Shell_NotifyIconA
{
    struct qemu_syscall super;
    uint64_t dwMessage;
    uint64_t pnid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Shell_NotifyIconA(DWORD dwMessage, PNOTIFYICONDATAA pnid)
{
    struct qemu_Shell_NotifyIconA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELL_NOTIFYICONA);
    call.dwMessage = (uint64_t)dwMessage;
    call.pnid = (uint64_t)pnid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Shell_NotifyIconA(struct qemu_syscall *call)
{
    struct qemu_Shell_NotifyIconA *c = (struct qemu_Shell_NotifyIconA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Shell_NotifyIconA(c->dwMessage, QEMU_G2H(c->pnid));
}

#endif

struct qemu_Shell_NotifyIconW
{
    struct qemu_syscall super;
    uint64_t dwMessage;
    uint64_t nid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Shell_NotifyIconW(DWORD dwMessage, PNOTIFYICONDATAW nid)
{
    struct qemu_Shell_NotifyIconW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELL_NOTIFYICONW);
    call.dwMessage = (uint64_t)dwMessage;
    call.nid = (uint64_t)nid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Shell_NotifyIconW(struct qemu_syscall *call)
{
    struct qemu_Shell_NotifyIconW *c = (struct qemu_Shell_NotifyIconW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Shell_NotifyIconW(c->dwMessage, QEMU_G2H(c->nid));
}

#endif

