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

struct qemu_CreateFileW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t access;
    uint64_t share;
    uint64_t security;
    uint64_t disposition;
    uint64_t flags;
    uint64_t template;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateFileW(const wchar_t *name, DWORD access, DWORD share,
        SECURITY_ATTRIBUTES *security, DWORD disposition, DWORD flags,
        HANDLE template)
{
    struct qemu_CreateFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFILEW);
    call.name = (uint64_t)name;
    call.access = access;
    call.share = share;
    call.security = (uint64_t)security;
    call.disposition = disposition;
    call.flags = flags;
    call.template = (uint64_t)template;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateFileW(struct qemu_syscall *call)
{
    struct qemu_CreateFileW *c = (struct qemu_CreateFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateFileW(QEMU_G2H(c->name), c->access, c->share,
            QEMU_G2H(c->security), c->disposition, c->flags, (HANDLE)c->template);
}

#endif

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

WINBASEAPI WINBOOL WINAPI WriteFile(HANDLE file, const void *buffer, DWORD to_write, DWORD *written, OVERLAPPED *ovl)
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

    c->super.iret = WriteFile((HANDLE)c->file, QEMU_G2H(c->buffer), c->to_write,
            QEMU_G2H(c->written), QEMU_G2H(c->ovl));
}

#endif

