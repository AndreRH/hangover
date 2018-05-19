/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_dll_init
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);

        qemu_syscall(&call.super);
    }

    return TRUE;
}

#else

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{

    qemu_init_dll,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side crypt32 wrapper.\n");
    HMODULE crypt32 = GetModuleHandleA("crypt32");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
