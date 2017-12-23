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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu_scanf
{
    struct qemu_syscall super;
    uint64_t argcount, argcount_float;
    uint64_t str;
    uint64_t fmt;
    uint64_t locale;
    struct va_array args[1];
};


#ifdef QEMU_DLL_GUEST

static int scanf_helper(const char *str, const char *fmt, MSVCRT__locale_t locale, va_list args)
{
    struct qemu_scanf *call;
    int ret;
    unsigned int count = count_printf_argsA(fmt, NULL), i;

    call = MSVCRT_malloc(offsetof(struct qemu_scanf, args[count]));

    call->super.id = QEMU_SYSCALL_ID(CALL_VSSCANF);
    call->str = (ULONG_PTR)str;
    call->fmt = (ULONG_PTR)fmt;
    call->locale = (ULONG_PTR)locale;
    call->argcount_float = 0;
    call->argcount = count;

    for (i = 0; i < count; ++i)
    {
        call->args[i].is_float = FALSE;
        call->args[i].arg = va_arg(args, ULONG_PTR);
    }

    qemu_syscall(&call->super);
    ret = call->super.iret;

    MSVCRT_free(call);

    return ret;
}

int CDECL MSVCRT_vsscanf_l(const char *str, const char *fmt, MSVCRT__locale_t locale, va_list list)
{

    return scanf_helper(str, fmt, locale, list);
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

static int swscanf_helper(const WCHAR *str, const WCHAR *fmt, MSVCRT__locale_t locale, uint64_t id, va_list args)
{
    struct qemu_scanf *call;
    int ret;
    unsigned int count = count_printf_argsW(fmt, NULL), i;

    call = MSVCRT_malloc(offsetof(struct qemu_scanf, args[count]));

    call->super.id = id;
    call->str = (ULONG_PTR)str;
    call->fmt = (ULONG_PTR)fmt;
    call->locale = (ULONG_PTR)locale;
    call->argcount_float = 0;
    call->argcount = count;

    for (i = 0; i < count; ++i)
    {
        call->args[i].is_float = FALSE;
        call->args[i].arg = va_arg(args, ULONG_PTR);
    }

    qemu_syscall(&call->super);
    ret = call->super.iret;

    MSVCRT_free(call);

    return ret;
}

int CDECL MSVCRT_swscanf_s(const WCHAR *str, const WCHAR *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = swscanf_helper(str, fmt, NULL, QEMU_SYSCALL_ID(CALL_SWSCANF_S), valist);
    va_end(valist);

    return res;
}
#else

void qemu_scanf(struct qemu_syscall *call)
{
    struct qemu_scanf *c = (struct qemu_scanf *)(ULONG_PTR)call;

    WINE_TRACE("(%lu floats/%lu args, format \"%s\"\n", (unsigned long)c->argcount_float, (unsigned long)c->argcount,
            (char *)QEMU_G2H(c->fmt));

    c->super.iret = call_va2((void *)p_sscanf, QEMU_G2H(c->str), QEMU_G2H(c->fmt),
            c->argcount, c->argcount_float, c->args);
}

void qemu_swscanf_s(struct qemu_syscall *call)
{
    struct qemu_scanf *c = (struct qemu_scanf *)(ULONG_PTR)call;

    WINE_TRACE("(%lu floats/%lu args, format \"%s\"\n", (unsigned long)c->argcount_float, (unsigned long)c->argcount,
            (char *)QEMU_G2H(c->fmt));

    c->super.iret = call_va2((void *)p_swscanf_s, QEMU_G2H(c->str), QEMU_G2H(c->fmt), c->argcount,
            c->argcount_float, c->args);
}

#endif

