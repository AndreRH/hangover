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

/* FIXME */
#define g2h(a)((void *)(a))

struct qemu_WriteFile
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buffer;
    uint64_t to_write;
    uint64_t written;
    uint64_t ovl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI WriteFile (HANDLE file, const void *buffer, DWORD to_write, DWORD *written, OVERLAPPED *ovl)
{
    struct qemu_WriteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEFILE);
    call.file = (uint64_t)file;
    call.buffer = (uint64_t)buffer;
    call.to_write = to_write;
    call.written = (uint64_t)written;
    call.ovl = (uint64_t)ovl;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_WriteFile(struct qemu_syscall *call)
{
    struct qemu_WriteFile *c = (struct qemu_WriteFile *)call;
    WINE_TRACE("\n");

    /* This structure probably works just fine when just passed on, but write a FIXME until tested. */
    if (c->ovl)
        WINE_FIXME("OVERLAPPED structure not handled yet.\n");

    c->super.iret = WriteFile((HANDLE)c->file, g2h(c->buffer), c->to_write, g2h(c->written), g2h(c->ovl));
}

#endif

