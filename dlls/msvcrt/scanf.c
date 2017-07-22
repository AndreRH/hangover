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
#include "va_helper.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu_scanf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t fmt;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_vsscanf_l(const char *str, const char *fmt, MSVCRT__locale_t locale, va_list list)
{
    struct qemu_scanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VSSCANF);
    call.str = (uint64_t)str;
    call.fmt = (uint64_t)fmt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

int CDECL MSVCRT_sscanf(const char *str, const char *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = MSVCRT_vsscanf_l(str, fmt, NULL, valist);
    va_end(valist);

    return res;
}

#else

void qemu_scanf(struct qemu_syscall *call)
{
    struct qemu_scanf *c = (struct qemu_scanf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;
}

#endif

