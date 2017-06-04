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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_SetConsoleCtrlHandler
{
    struct qemu_syscall super;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

/* FIXME: Read this from the TEB. */
static PHANDLER_ROUTINE guest_handler;

static uint64_t WINAPI call_ctrl_handler(uint64_t type)
{
    uint64_t ret = FALSE;
    if (guest_handler)
        ret = guest_handler(type);

    return ret;
}

WINBASEAPI BOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE routine, BOOL Add)
{
    struct qemu_SetConsoleCtrlHandler call;

    guest_handler = routine;

    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONSOLECTRLHANDLER);
    call.wrapper = (uint64_t)call_ctrl_handler;
    qemu_syscall(&call.super);
}

#else

static void *console_handler_wrapper;

BOOL WINAPI qemu_console_handler(DWORD type)
{
    BOOL ret = FALSE;
    WINE_TRACE("(%x) calling %p.\n", type, console_handler_wrapper);

    ret = qemu_ops->qemu_execute(console_handler_wrapper, type);
    WINE_TRACE("Got return value %u from guest.\n", ret);

    return TRUE;
}

void qemu_SetConsoleCtrlHandler(struct qemu_syscall *call)
{
    struct qemu_SetConsoleCtrlHandler *c = (struct qemu_SetConsoleCtrlHandler *)call;
    WINE_FIXME("Only partial support.\n");

    if (!console_handler_wrapper)
    {
        SetConsoleCtrlHandler(qemu_console_handler, TRUE);
        console_handler_wrapper = QEMU_G2H(c->wrapper);
    }
    else if (console_handler_wrapper != QEMU_G2H(c->wrapper))
    {
        WINE_ERR("Got different console handler wrappers.\n");
    }
}

#endif
