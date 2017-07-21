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
#include "ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

/* FIXME: Calling out of the vm for wcsrchr is probably a waste of time. */
struct qemu_wcsrchr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t ch;
};


#ifdef QEMU_DLL_GUEST

WCHAR * CDECL NTDLL_wcsrchr(WCHAR *str, WCHAR ch)
{
    struct qemu_wcsrchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSRCHR);
    call.str = (uint64_t)str;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (WCHAR *)call.super.iret;
}

#else

void qemu_wcsrchr(struct qemu_syscall *call)
{
    struct qemu_wcsrchr *c = (struct qemu_wcsrchr *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcsrchr(QEMU_G2H(c->str), c->ch));
}

#endif
