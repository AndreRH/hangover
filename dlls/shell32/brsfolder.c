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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_SHBrowseForFolderA
{
    struct qemu_syscall super;
    uint64_t lpbi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI SHBrowseForFolderA (LPBROWSEINFOA lpbi)
{
    struct qemu_SHBrowseForFolderA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHBROWSEFORFOLDERA);
    call.lpbi = (ULONG_PTR)lpbi;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SHBrowseForFolderA(struct qemu_syscall *call)
{
    struct qemu_SHBrowseForFolderA *c = (struct qemu_SHBrowseForFolderA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHBrowseForFolderA(QEMU_G2H(c->lpbi));
}

#endif

struct qemu_SHBrowseForFolderW
{
    struct qemu_syscall super;
    uint64_t lpbi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI SHBrowseForFolderW (LPBROWSEINFOW lpbi)
{
    struct qemu_SHBrowseForFolderW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHBROWSEFORFOLDERW);
    call.lpbi = (ULONG_PTR)lpbi;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SHBrowseForFolderW(struct qemu_syscall *call)
{
    struct qemu_SHBrowseForFolderW *c = (struct qemu_SHBrowseForFolderW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHBrowseForFolderW(QEMU_G2H(c->lpbi));
}

#endif

