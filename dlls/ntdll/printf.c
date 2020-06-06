/*
 * Copyright 2017 André Hentschel
 * Copyright 2019 Stefan Dösinger for CodeWeavers
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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "va_helper.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#else

static inline HANDLE ntdll_GetProcessHeap(void)
{
    return ((HANDLE **)NtCurrentTeb())[12][6];
}

#define NtCurrentProcess() ( (HANDLE)(LONG_PTR) -1 )

#endif

struct qemu_snwprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL__snwprintf(WCHAR *str, SIZE_T len, const WCHAR *format, ...)
{
    struct qemu_snwprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL__SNWPRINTF);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL__snwprintf(struct qemu_syscall *call)
{
    struct qemu_snwprintf *c = (struct qemu_snwprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_snwprintf(QEMU_G2H(c->str), c->len, QEMU_G2H(c->format));
}

#endif

struct qemu_NTDLL_swprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL_swprintf(WCHAR *str, const WCHAR *format, ...)
{
    struct qemu_NTDLL_swprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL_SWPRINTF);
    call.str = (ULONG_PTR)str;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL_swprintf(struct qemu_syscall *call)
{
    struct qemu_NTDLL_swprintf *c = (struct qemu_NTDLL_swprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//NTDLL_swprintf(QEMU_G2H(c->str), QEMU_G2H(c->format));
}

#endif

struct qemu_vsnwprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t format;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL__vsnwprintf(WCHAR *str, SIZE_T len, const WCHAR *format, va_list args)
{
    struct qemu_vsnwprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL__VSNWPRINTF);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL__vsnwprintf(struct qemu_syscall *call)
{
    struct qemu_vsnwprintf *c = (struct qemu_vsnwprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_vsnwprintf(QEMU_G2H(c->str), c->len, QEMU_G2H(c->format), c->args);
}

#endif

struct qemu_sprintf
{
    struct qemu_syscall super;
    uint64_t argcount, argcount_float;
    uint64_t str;
    uint64_t len;
    uint64_t charcount;
    uint64_t format;
    struct va_array args[1];
};

#ifdef QEMU_DLL_GUEST

unsigned int count_printf_argsA(const char *format, char *fmts)
{
    unsigned int i, count = 0;
    BOOL fmt_start = FALSE;

    for (i = 0; format[i]; ++i)
    {
        if (!fmt_start)
        {
            if (format[i] != '%')
                continue;
            i++;
        }

        if (format[i] == '%')
            continue;

        switch (format[i])
        {
            case 'A':
            case 'a':
            case 'c':
            case 'd':
            case 'E':
            case 'e':
            case 'F':
            case 'f':
            case 'G':
            case 'g':
            case 'i':
            case 'n':
            case 'o':
            case 'p':
            case 's':
            case 'S':
            case 'u':
            case 'X':
            case 'x':
                if (fmts)
                {
                    fmts[count] = format[i];
                    if (count == 256)
                        ntdll_NtTerminateProcess(NtCurrentProcess(), 255);
                }
                count++;
                fmt_start = FALSE;
                break;

            default:
                fmt_start = TRUE;
                break;
        }
    }

    return count;
}
static int CDECL vsprintf_helper(uint64_t op, char *str, size_t len, size_t charcount, const char *format, va_list args)
{
    struct qemu_sprintf *call;
    int ret;
    char fmts[256] = {0};
    unsigned int count = count_printf_argsA(format, fmts), i, arg = 0;
    union
    {
        double d;
        uint64_t i;
    } conv;

    call = ntdll_RtlAllocateHeap(ntdll_GetProcessHeap(), 0, offsetof(struct qemu_sprintf, args[count]));
    call->super.id = op;
    call->len = len;
    call->argcount = count;
    call->charcount = charcount;
    call->str = (ULONG_PTR)str;
    call->format = (ULONG_PTR)format;
    call->argcount_float = 0;

    for (i = 0; i < count; ++i)
    {
        switch (fmts[i])
        {
            case 'A':
            case 'a':
            case 'E':
            case 'e':
            case 'F':
            case 'f':
            case 'G':
            case 'g':
                conv.d = va_arg(args, double);
                call->args[i].is_float = TRUE;
                call->args[i].arg = conv.i;
                call->argcount_float++;
                break;

            default:
                call->args[i].is_float = FALSE;
                call->args[i].arg = va_arg(args, ULONG_PTR);
                break;
        }
    }

    qemu_syscall(&call->super);
    ret = call->super.iret;

    ntdll_RtlFreeHeap(ntdll_GetProcessHeap(), 0, call);

    return ret;
}
WINBASEAPI int WINAPIV NTDLL_sprintf(char *str, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL_NTDLL_VSPRINTF), str, 0, 0, format, list);
    va_end(list);

    return ret;
}

WINBASEAPI int CDECL NTDLL_vsprintf(char *str, const char *format, va_list args)
{
    return vsprintf_helper(QEMU_SYSCALL_ID(CALL_NTDLL_VSPRINTF), str, 0, 0, format, args);
}

WINBASEAPI int CDECL NTDLL__vsnprintf(char *str, SIZE_T len, const char *format, va_list args)
{
    return vsprintf_helper(QEMU_SYSCALL_ID(CALL_NTDLL__VSNPRINTF), str, len, 0, format, args);
}

WINBASEAPI int CDECL ntdll_vsnprintf_s(char *str, SIZE_T size, SIZE_T len, const char *format, va_list args)
{
    return vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF_S), str, size, len, format, args);
}

WINBASEAPI int WINAPIV ntdll_snprintf_s(char *str, SIZE_T size, SIZE_T len, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF_S), str, size, len, format, list);
    va_end(list);

    return ret;
}

WINBASEAPI int WINAPIV NTDLL__snprintf(char *str, SIZE_T len, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL_NTDLL__VSNPRINTF), str, len, 0, format, list);
    va_end(list);

    return ret;
}

#else

struct sprintf_data
{
    uint64_t op;
    size_t len;
    size_t charcount;
    void *dst;
    void *fmt;
};

static uint64_t CDECL sprintf_wrapper(void *ctx, ...)
{
    __ms_va_list list;
    const struct sprintf_data *data = ctx;
    int ret;

    __ms_va_start(list, ctx);
    switch (data->op)
    {
        case QEMU_SYSCALL_ID(CALL_NTDLL_VSPRINTF):
            ret = p_vsprintf(data->dst, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL_NTDLL__VSNPRINTF):
            ret = p__vsnprintf(data->dst, data->len, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL__VSNPRINTF_S):
            ret = p__vsnprintf_s(data->dst, data->len, data->charcount, data->fmt, list);
            break;
        default:
            WINE_ERR("Unexpected call\n");
    }
    __ms_va_end(list);

    return ret;
}

void qemu_sprintf(struct qemu_syscall *call)
{
    struct qemu_sprintf *c = (struct qemu_sprintf *)(ULONG_PTR)call;
    struct sprintf_data data;
    int ret;
    static int once;

    WINE_TRACE("(%lu floats/%lu args, format \"%s\"\n", (unsigned long)c->argcount_float, (unsigned long)c->argcount,
            (char *)QEMU_G2H(c->format));

    data.op = c->super.id;
    data.len = c->len;
    data.charcount = c->charcount;
    data.dst = QEMU_G2H(c->str);
    data.fmt = QEMU_G2H(c->format);
    ret = call_va(sprintf_wrapper, &data, c->argcount, c->argcount_float, c->args);

    c->super.iret = ret;
}
#endif

