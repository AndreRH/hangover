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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CompareStringW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t str1;
    uint64_t len1;
    uint64_t str2;
    uint64_t len2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CompareStringW(LCID lcid, DWORD flags, LPCWSTR str1, INT len1, LPCWSTR str2, INT len2)
{
    struct qemu_CompareStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPARESTRINGW);
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;
    call.str1 = (uint64_t)str1;
    call.len1 = (uint64_t)len1;
    call.str2 = (uint64_t)str2;
    call.len2 = (uint64_t)len2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareStringW(struct qemu_syscall *call)
{
    struct qemu_CompareStringW *c = (struct qemu_CompareStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = CompareStringW(c->lcid, c->flags, QEMU_G2H(c->str1), c->len1, QEMU_G2H(c->str2), c->len2);
}

#endif
