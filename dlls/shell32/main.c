/*
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
#include "shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_ShellAboutW
{
    struct qemu_syscall super;
    uint64_t win;
    uint64_t app, other;
    uint64_t icon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ShellAboutW(HWND win, const WCHAR *app, const WCHAR *other, HICON icon)
{
    struct qemu_ShellAboutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLABOUTW);
    call.win = (uint64_t)win;
    call.app = (uint64_t)app;
    call.other = (uint64_t)other;
    call.icon = (uint64_t)icon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShellAboutW(struct qemu_syscall *call)
{
    struct qemu_ShellAboutW *c = (struct qemu_ShellAboutW *)call;
    WINE_TRACE("\n");
    c->super.iret = ShellAboutW((HANDLE)c->win, QEMU_G2H(c->app), QEMU_G2H(c->other), (HANDLE)c->icon);
}

#endif

#ifndef QEMU_DLL_GUEST
const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_DllGetClassObject,
    qemu_DragAcceptFiles,
    qemu_DragFinish,
    qemu_DragQueryFileA,
    qemu_DragQueryFileW,
    qemu_DragQueryPoint,
    qemu_SHAlloc,
    qemu_SHCLSIDFromString,
    qemu_SHCoCreateInstance,
    qemu_SHCreateQueryCancelAutoPlayMoniker,
    qemu_ShellAboutW,
    qemu_SHFree,
    qemu_SHGetMalloc,
    qemu_SHPropStgCreate,
    qemu_SHPropStgReadMultiple,
    qemu_SHPropStgWriteMultiple,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE shell32;

    WINE_TRACE("Loading host-side shell32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    shell32 = LoadLibraryA("shell32.dll");
    if (!shell32)
        WINE_ERR("Cannot find shell32.dll\n");

    p_SHCLSIDFromString = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(147));

    return dll_functions;
}

#endif
