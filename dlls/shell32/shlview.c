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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_SHCreateShellFolderView
{
    struct qemu_syscall super;
    uint64_t desc;
    uint64_t shellview;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellFolderView(const SFV_CREATE *desc, IShellView **shellview)
{
    struct qemu_SHCreateShellFolderView call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLFOLDERVIEW);
    call.desc = (ULONG_PTR)desc;
    call.shellview = (ULONG_PTR)shellview;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellFolderView(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellFolderView *c = (struct qemu_SHCreateShellFolderView *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellFolderView(QEMU_G2H(c->desc), QEMU_G2H(c->shellview));
}

#endif

struct qemu_SHCreateShellFolderViewEx
{
    struct qemu_syscall super;
    uint64_t desc;
    uint64_t shellview;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellFolderViewEx(CSFV *desc, IShellView **shellview)
{
    struct qemu_SHCreateShellFolderViewEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLFOLDERVIEWEX);
    call.desc = (ULONG_PTR)desc;
    call.shellview = (ULONG_PTR)shellview;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellFolderViewEx(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellFolderViewEx *c = (struct qemu_SHCreateShellFolderViewEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellFolderViewEx(QEMU_G2H(c->desc), QEMU_G2H(c->shellview));
}

#endif

