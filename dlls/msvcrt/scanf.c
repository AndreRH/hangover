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
    uint64_t argcount;
    uint64_t input;
    uint64_t length;
    uint64_t fmt;
    uint64_t locale;
    uint64_t options;
    struct va_array args[1];
};


#ifdef QEMU_DLL_GUEST

static int scanf_helper(unsigned __int64 options, const void *input, size_t length, const char *fmt,
        MSVCRT__locale_t locale, uint64_t id, va_list args)
{
    struct qemu_scanf *call;
    int ret;
    unsigned int count = count_printf_argsA(fmt, NULL), i;

    call = MSVCRT_malloc(offsetof(struct qemu_scanf, args[count]));

    call->super.id = id;
    call->options = options;
    call->input = (ULONG_PTR)input;
    call->fmt = (ULONG_PTR)fmt;
    call->locale = (ULONG_PTR)locale;
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

    return scanf_helper(0, str, 0, fmt, locale, QEMU_SYSCALL_ID(CALL_VSSCANF), list);
}

int WINAPIV MSVCRT_sscanf_s(const char *str, const char *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = scanf_helper(0, str, 0, fmt, 0, QEMU_SYSCALL_ID(CALL_VSSCANF_S), valist);
    va_end(valist);

    return res;
}

int WINAPIV MSVCRT_sscanf(const char *str, const char *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = MSVCRT_vsscanf_l(str, fmt, NULL, valist);
    va_end(valist);

    return res;
}

int CDECL MSVCRT_vfscanf_l(FILE *f, const char *fmt, MSVCRT__locale_t locale, va_list list)
{

    return scanf_helper(0, f, 0, fmt, locale, QEMU_SYSCALL_ID(CALL_VFSCANF), list);
}

int WINAPIV MSVCRT_fscanf(FILE *f, const char *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = MSVCRT_vfscanf_l(f, fmt, NULL, valist);
    va_end(valist);

    return res;
}

int CDECL MSVCRT_vsnscanf_l(const char *input, size_t length, const char *fmt, MSVCRT__locale_t locale, va_list list)
{

    return scanf_helper(0, input, length, fmt, locale, QEMU_SYSCALL_ID(CALL_VSNSCANF), list);
}

int WINAPIV MSVCRT__snscanf(char *input, size_t length, const char *format, ...)
{
    va_list valist;
    int res;

    va_start(valist, format);
    res = MSVCRT_vsnscanf_l(input, length, format, NULL, valist);
    va_end(valist);
    return res;
}

int CDECL MSVCRT__stdio_common_vsscanf(unsigned __int64 options,
        const char *input, size_t length, const char *format,
        MSVCRT__locale_t locale, va_list valist)
{
    return scanf_helper(options, input, length, format, locale, QEMU_SYSCALL_ID(CALL_VSSCANF_UCRTBASE), valist);
}

static int swscanf_helper(const WCHAR *input, size_t length, const WCHAR *fmt, MSVCRT__locale_t locale, uint64_t id, va_list args)
{
    struct qemu_scanf *call;
    int ret;
    unsigned int count = count_printf_argsW(fmt, NULL), i;

    call = MSVCRT_malloc(offsetof(struct qemu_scanf, args[count]));

    call->super.id = id;
    call->input = (ULONG_PTR)input;
    call->length = length;
    call->fmt = (ULONG_PTR)fmt;
    call->locale = (ULONG_PTR)locale;
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

int WINAPIV MSVCRT_swscanf_s(const WCHAR *str, const WCHAR *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = swscanf_helper(str, 0, fmt, NULL, QEMU_SYSCALL_ID(CALL_SWSCANF_S), valist);
    va_end(valist);

    return res;
}

int WINAPIV MSVCRT__snwscanf(wchar_t *str, size_t len, const wchar_t *fmt, ...)
{
    va_list valist;
    int res;

    va_start(valist, fmt);
    res = swscanf_helper(str, len, fmt, NULL, QEMU_SYSCALL_ID(CALL_SNWSCANF), valist);
    va_end(valist);
    return res;
}

#else

struct scanf_data
{
    uint64_t options;
    void *input;
    size_t length;
    void *fmt;
    MSVCRT__locale_t locale;
    uint64_t op;
};

static uint64_t WINAPIV scanf_wrapper(void *ctx, ...)
{
    __ms_va_list list;
    const struct scanf_data *data = ctx;
    int ret;

    __ms_va_start(list, ctx);
    ret = p___stdio_common_vsscanf(data->options, data->input, data->length, data->fmt, data->locale, list);
    __ms_va_end(list);

    return ret;
}

void qemu_scanf(struct qemu_syscall *call)
{
    static BOOL warn = TRUE;
    struct qemu_scanf *c = (struct qemu_scanf *)(ULONG_PTR)call;
    struct scanf_data data;

    WINE_TRACE("%lu args, format \"%s\"\n", (unsigned long)c->argcount, (char *)QEMU_G2H(c->fmt));

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_VSSCANF):
            c->super.iret = call_va2((void *)p_sscanf, QEMU_G2H(c->input), QEMU_G2H(c->fmt), c->argcount, c->args);
            break;

        case QEMU_SYSCALL_ID(CALL_VSSCANF_S):
            c->super.iret = call_va2((void *)p_sscanf_s, QEMU_G2H(c->input), QEMU_G2H(c->fmt), c->argcount, c->args);
            break;

        case QEMU_SYSCALL_ID(CALL_VFSCANF):
            c->super.iret = call_va2((void *)p_fscanf, FILE_g2h(c->input), QEMU_G2H(c->fmt), c->argcount, c->args);
            break;

        case QEMU_SYSCALL_ID(CALL_VSNSCANF):
            /* Need a call_va version with 3 fixed args. */
            if (warn)
            {
                WINE_FIXME("Calling sscanf instead of snscanf.\n");
                warn = FALSE;
            }
            c->super.iret = call_va2((void *)p_sscanf, QEMU_G2H(c->input), QEMU_G2H(c->fmt), c->argcount, c->args);
            break;

        case QEMU_SYSCALL_ID(CALL_VSSCANF_UCRTBASE):
            data.op = c->super.id;
            data.options = c->options;
            data.input = QEMU_G2H(c->input);
            data.length = c->length;
            data.fmt = QEMU_G2H(c->fmt);
            data.locale = QEMU_G2H(c->locale);
            c->super.iret = call_va(scanf_wrapper, &data, c->argcount, c->args);
            break;
    }
}

void qemu_wscanf(struct qemu_syscall *call)
{
    struct qemu_scanf *c = (struct qemu_scanf *)(ULONG_PTR)call;
    static BOOL warn = TRUE;

    WINE_TRACE("%lu args, format \"%s\"\n", (unsigned long)c->argcount, wine_dbgstr_w(QEMU_G2H(c->fmt)));

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_SWSCANF_S):
            c->super.iret = call_va2((void *)p_swscanf_s, QEMU_G2H(c->input), QEMU_G2H(c->fmt), c->argcount, c->args);
            break;

        case QEMU_SYSCALL_ID(CALL_SNWSCANF):
            /* Need a call_va version with 3 fixed args. */
            if (warn)
            {
                WINE_FIXME("Calling swscanf instead of snwscanf.\n");
                warn = FALSE;
            }
            c->super.iret = call_va2((void *)p_swscanf, QEMU_G2H(c->input), QEMU_G2H(c->fmt), c->argcount, c->args);
            break;
    }
}

#endif

