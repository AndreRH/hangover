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
#include <sys/stat.h>
#include <fcntl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "va_helper.h"
#include "qemu_msvcrt.h"

#ifdef QEMU_DLL_GUEST
#include <sys/utime.h>
#else
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

#ifndef __x86_64__

FILE guest_iob[GUEST_IOB_SIZE];

FILE * CDECL MSVCRT___iob_func(void)
{
    return guest_iob;
}

#else

FILE * CDECL MSVCRT___iob_func(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___IOB_FUNC);

    qemu_syscall(&call);

    return (FILE *)(ULONG_PTR)call.iret;
}

#endif

#else

void qemu___iob_func(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    c->iret = QEMU_H2G(p___iob_func());
}

#endif

struct qemu__fileno
{
    struct qemu_syscall super;
    uint64_t f;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fileno(FILE *f)
{
    struct qemu__fileno call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FILENO);
    call.f = (ULONG_PTR)f;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fileno(struct qemu_syscall *call)
{
    struct qemu__fileno *c = (struct qemu__fileno *)(ULONG_PTR)call;
    MSVCRT_FILE *f;

    WINE_TRACE("\n");
    f = FILE_g2h(c->f);
    c->super.iret = p__fileno(f);
}

#endif

struct qemu__isatty
{
    struct qemu_syscall super;
    uint64_t fd;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__isatty(int fd)
{
    struct qemu__isatty call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISATTY);
    call.fd = fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__isatty(struct qemu_syscall *call)
{
    struct qemu__isatty *c = (struct qemu__isatty *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__isatty(c->fd);
}

#endif

struct qemu__lseek
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t offset;
    uint64_t whence;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT__lseek(int fd, LONG offset, int whence)
{
    struct qemu__lseek call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LSEEK);
    call.fd = fd;
    call.offset = offset;
    call.whence = whence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lseek(struct qemu_syscall *call)
{
    struct qemu__lseek *c = (struct qemu__lseek *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__lseek(c->fd, c->offset, c->whence);
}

#endif

struct qemu__lseeki64
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t offset;
    uint64_t whence;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL MSVCRT__lseeki64(int fd, __int64 offset, int whence)
{
    struct qemu__lseeki64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LSEEKI64);
    call.fd = fd;
    call.offset = offset;
    call.whence = whence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__lseeki64(struct qemu_syscall *call)
{
    struct qemu__lseeki64 *c = (struct qemu__lseeki64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__lseeki64(c->fd, c->offset, c->whence);
}

#endif

struct qemu__tempnam
{
    struct qemu_syscall super;
    uint64_t dir;
    uint64_t prefix;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__tempnam(const char *dir, const char *prefix)
{
    struct qemu__tempnam call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TEMPNAM);
    call.dir = (ULONG_PTR)dir;
    call.prefix = (ULONG_PTR)prefix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__tempnam(struct qemu_syscall *call)
{
    struct qemu__tempnam *c = (struct qemu__tempnam *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__tempnam(QEMU_G2H(c->dir), QEMU_G2H(c->prefix)));
}

#endif

struct qemu_fflush
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fflush(FILE *file)
{
    struct qemu_fflush call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FFLUSH);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fflush(struct qemu_syscall *call)
{
    struct qemu_fflush *c = (struct qemu_fflush *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_fflush(FILE_g2h(c->file));
}

#endif

struct qemu__write
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
    uint64_t count;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__write(int fd, const void *buf, unsigned int count)
{
    struct qemu__write call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WRITE);
    call.fd = fd;
    call.buf = (ULONG_PTR)buf;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__write(struct qemu_syscall *call)
{
    struct qemu__write *c = (struct qemu__write *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__write(c->fd, QEMU_G2H(c->buf), c->count);
}

#endif
struct qemu_fprintf
{
    struct qemu_syscall super;
    uint64_t argcount, argcount_float;
    uint64_t file;
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
                        MSVCRT_exit(255);
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

/* Looking up "stdout" requires a call out of the VM to get __iob, so do
 * the printf(...) -> fprintf(stdout, ...) wrapping outside the VM. */
static int CDECL vfprintf_helper(uint64_t op, FILE *file, const char *format, va_list args)
{
    struct qemu_fprintf *call;
    int ret;
    char fmts[256] = {0};
    unsigned int count = count_printf_argsA(format, fmts), i, arg = 0;
    union
    {
        double d;
        uint64_t i;
    } conv;

    call = MSVCRT_malloc(offsetof(struct qemu_fprintf, args[count]));
    call->super.id = op;
    call->argcount = count;
    call->file = (ULONG_PTR)file;
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

    MSVCRT_free(call);

    return ret;
}

int CDECL MSVCRT_vfprintf(FILE *file, const char *format, va_list args)
{
    return vfprintf_helper(QEMU_SYSCALL_ID(CALL_FPRINTF), file, format, args);
}

int CDECL MSVCRT_fprintf(FILE *file, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vfprintf_helper(QEMU_SYSCALL_ID(CALL_FPRINTF), file, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT_printf(const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vfprintf_helper(QEMU_SYSCALL_ID(CALL_PRINTF), NULL, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT_vprintf(const char *format, va_list list)
{
    return vfprintf_helper(QEMU_SYSCALL_ID(CALL_PRINTF), NULL, format, list);
}

unsigned int count_printf_argsW(const WCHAR *format, WCHAR *fmts)
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
                        MSVCRT_exit(255);
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

static int CDECL vfwprintf_helper(uint64_t op, FILE *file, const WCHAR *format, va_list args)
{
    struct qemu_fprintf *call;
    int ret;
    WCHAR fmts[256] = {0};
    unsigned int count = count_printf_argsW(format, fmts), i, arg = 0;
    union
    {
        double d;
        uint64_t i;
    } conv;

    call = MSVCRT_malloc(offsetof(struct qemu_fprintf, args[count]));
    call->super.id = op;
    call->argcount = count;
    call->file = (ULONG_PTR)file;
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

    MSVCRT_free(call);

    return ret;
}

int CDECL MSVCRT_vfwprintf(FILE *file, const WCHAR *format, va_list args)
{
    return vfwprintf_helper(QEMU_SYSCALL_ID(CALL_FWPRINTF), file, format, args);
}

int CDECL MSVCRT_fwprintf(FILE *file, const WCHAR *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vfwprintf_helper(QEMU_SYSCALL_ID(CALL_FWPRINTF), file, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT_wprintf(const WCHAR *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vfwprintf_helper(QEMU_SYSCALL_ID(CALL_WPRINTF), NULL, format, list);
    va_end(list);

    return ret;
}

#else

struct printf_data
{
    void *file;
    void *fmt; 
    BOOL unicode;
};

static uint64_t CDECL printf_wrapper(void *ctx, ...)
{
    __ms_va_list list;
    const struct printf_data *data = ctx;
    int ret;

    __ms_va_start(list, ctx);
    if (data->unicode)
        ret = p_vfwprintf(data->file, data->fmt, list);
    else
        ret = p_vfprintf(data->file, data->fmt, list);
    __ms_va_end(list);

    return ret;
}

void qemu_fprintf(struct qemu_syscall *call)
{
    struct qemu_fprintf *c = (struct qemu_fprintf *)(ULONG_PTR)call;
    int ret;
    void *file;
    struct printf_data data;

    WINE_TRACE("(%lu floats/%lu args, format \"%s\"\n", (unsigned long)c->argcount_float, (unsigned long)c->argcount,
            (char *)QEMU_G2H(c->format));

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_PRINTF):
            /* Don't put "stdout" here, it will call the Linux libc __iob_func export. */
            data.file = p___iob_func() + 1;
            data.unicode = FALSE;
            break;

        case QEMU_SYSCALL_ID(CALL_FPRINTF):
            data.file = FILE_g2h(c->file);
            data.unicode = FALSE;
            break;

        case QEMU_SYSCALL_ID(CALL_WPRINTF):
            data.file = p___iob_func() + 1;
            data.unicode = TRUE;
            break;

        case QEMU_SYSCALL_ID(CALL_FWPRINTF):
            data.file = FILE_g2h(c->file);
            data.unicode = TRUE;
            break;

        default:
            WINE_ERR("Unexpected op %lx\n", (unsigned long)c->super.id);
    }
    data.fmt = QEMU_G2H(c->format);

    ret = call_va(printf_wrapper, &data, c->argcount, c->argcount_float, c->args);

    c->super.iret = ret;
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

    call = MSVCRT_malloc(offsetof(struct qemu_sprintf, args[count]));
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

    MSVCRT_free(call);

    return ret;
}

static int CDECL vswprintf_helper(uint64_t op, WCHAR *str, size_t len, size_t charcount, const WCHAR *format, va_list args)
{
    struct qemu_sprintf *call;
    int ret;
    WCHAR fmts[256] = {0};
    unsigned int count = count_printf_argsW(format, fmts), i, arg = 0;
    union
    {
        double d;
        uint64_t i;
    } conv;

    call = MSVCRT_malloc(offsetof(struct qemu_sprintf, args[count]));
    call->super.id = op;
    call->argcount = count;
    call->str = (ULONG_PTR)str;
    call->len = len;
    call->charcount = charcount;
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

    MSVCRT_free(call);

    return ret;
}

int CDECL MSVCRT_sprintf(char *str, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL_SPRINTF), str, 0, 0, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT_vsprintf(char *str, const char *format, va_list list)
{
    return vsprintf_helper(QEMU_SYSCALL_ID(CALL_SPRINTF), str, 0, 0, format, list);
}

int CDECL MSVCRT_sprintf_s(char *str, size_t num, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL_SPRINTF_S), str, 0, num, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT_vsprintf_s(char *str, size_t num, const char *format, va_list list)
{
    int ret;

    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL_SPRINTF_S), str, 0, num, format, list);

    return ret;
}

int CDECL MSVCRT__snprintf(char *str, size_t len, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF), str, len, 0, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT__snprintf_s(char *str, unsigned int len, unsigned int count, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF_S), str, len, count, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT__vsnprintf(char *str, size_t len, const char *format, va_list valist)
{
    return vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF), str, len, 0, format, valist);
}

int CDECL MSVCRT__vscprintf(const char *format, va_list valist)
{
    return MSVCRT__vsnprintf(NULL, INT_MAX, format, valist);
}

int CDECL MSVCRT_vswprintf_s(WCHAR *str, size_t count, const WCHAR *format, va_list list)
{
    return vswprintf_helper(QEMU_SYSCALL_ID(CALL_SWPRINTF_S), str, 0, count, format, list);
}

int CDECL MSVCRT_swprintf_s(WCHAR *str, size_t count,
        const WCHAR *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vswprintf_helper(QEMU_SYSCALL_ID(CALL_SWPRINTF_S), str, 0, count, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT__vsnwprintf(WCHAR *str, size_t len, const WCHAR *format, va_list valist)
{
    return vswprintf_helper(QEMU_SYSCALL_ID(CALL__VSNWPRINTF), str, len, 0, format, valist);
}

int CDECL MSVCRT__vscwprintf( const wchar_t *format, va_list args )
{
    return MSVCRT__vsnwprintf( NULL, INT_MAX, format, args );
}

int CDECL MSVCRT_vswprintf( wchar_t *str, const wchar_t *format, va_list args )
{
    return MSVCRT__vsnwprintf( str, INT_MAX, format, args );
}

int CDECL MSVCRT__snwprintf(WCHAR *str, unsigned int len, const WCHAR *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vswprintf_helper(QEMU_SYSCALL_ID(CALL__VSNWPRINTF), str, len, 0, format, list);
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
        case QEMU_SYSCALL_ID(CALL_SPRINTF):
            ret = p_vsprintf(data->dst, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL_SPRINTF_S):
            ret = p_vsprintf_s(data->dst, data->charcount, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL__VSNPRINTF):
            ret = p__vsnprintf(data->dst, data->len, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL__VSNPRINTF_S):
            ret = p__vsnprintf_s(data->dst, data->len, data->charcount, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL_SWPRINTF_S):
            ret = p_vswprintf_s(data->dst, data->charcount, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL__VSNWPRINTF):
            ret = p__vsnwprintf(data->dst, data->len, data->fmt, list);
            break;
    }
    __ms_va_end(list);

    return ret;
}

void qemu_sprintf(struct qemu_syscall *call)
{
    struct qemu_sprintf *c = (struct qemu_sprintf *)(ULONG_PTR)call;
    struct sprintf_data data;
    int ret;

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

struct qemu_fread
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size, count;
    uint64_t file;
};


#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_fread(const void *str, size_t size, size_t count, FILE *file)
{
    struct qemu_fread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREAD);
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.count = count;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fread(struct qemu_syscall *call)
{
    struct qemu_fread *c = (struct qemu_fread *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)p_fread(QEMU_G2H(c->str), c->size, c->count, FILE_g2h(c->file));
}

#endif

struct qemu_fwrite
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size, count;
    uint64_t file;
};


#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_fwrite(const void *str, size_t size, size_t count, FILE *file)
{
    struct qemu_fwrite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FWRITE);
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.count = count;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fwrite(struct qemu_syscall *call)
{
    struct qemu_fwrite *c = (struct qemu_fwrite *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)p_fwrite(QEMU_G2H(c->str), c->size, c->count, FILE_g2h(c->file));
}

#endif

struct qemu_puts
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_puts(const char *str)
{
    struct qemu_puts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PUTS);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_puts(struct qemu_syscall *call)
{
    struct qemu_puts *c = (struct qemu_puts *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_puts(QEMU_G2H(c->str));
}

#endif

struct qemu_setvbuf
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buf;
    uint64_t mode;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_setvbuf(FILE *file, char *buf, int mode, size_t size)
{
    struct qemu_setvbuf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVBUF);
    call.file = (ULONG_PTR)file;
    call.buf = (ULONG_PTR)buf;
    call.mode = mode;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_setvbuf(struct qemu_syscall *call)
{
    struct qemu_setvbuf *c = (struct qemu_setvbuf *)(ULONG_PTR)call;
    MSVCRT_FILE *f;

    WINE_TRACE("\n");
    f = FILE_g2h(c->file);
    c->super.iret = p_setvbuf(f, QEMU_G2H(c->buf), c->mode, c->size);
}

#endif

struct qemu___acrt_iob_func
{
    struct qemu_syscall super;
    uint64_t idx;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT___acrt_iob_func(unsigned idx)
{
    struct qemu___acrt_iob_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ACRT_IOB_FUNC);
    call.idx = (ULONG_PTR)idx;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___acrt_iob_func(struct qemu_syscall *call)
{
    struct qemu___acrt_iob_func *c = (struct qemu___acrt_iob_func *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___acrt_iob_func(c->idx));
}

#endif

struct qemu__access
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__access(const char *filename, int mode)
{
    struct qemu__access call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ACCESS);
    call.filename = (ULONG_PTR)filename;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__access(struct qemu_syscall *call)
{
    struct qemu__access *c = (struct qemu__access *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__access(QEMU_G2H(c->filename), c->mode);
}

#endif

struct qemu__access_s
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__access_s(const char *filename, int mode)
{
    struct qemu__access_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ACCESS_S);
    call.filename = (ULONG_PTR)filename;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__access_s(struct qemu_syscall *call)
{
    struct qemu__access_s *c = (struct qemu__access_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__access_s(QEMU_G2H(c->filename), c->mode);
}

#endif

struct qemu__waccess
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__waccess(const WCHAR *filename, int mode)
{
    struct qemu__waccess call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WACCESS);
    call.filename = (ULONG_PTR)filename;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__waccess(struct qemu_syscall *call)
{
    struct qemu__waccess *c = (struct qemu__waccess *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__waccess(QEMU_G2H(c->filename), c->mode);
}

#endif

struct qemu__waccess_s
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__waccess_s(const WCHAR *filename, int mode)
{
    struct qemu__waccess_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WACCESS_S);
    call.filename = (ULONG_PTR)filename;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__waccess_s(struct qemu_syscall *call)
{
    struct qemu__waccess_s *c = (struct qemu__waccess_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__waccess_s(QEMU_G2H(c->filename), c->mode);
}

#endif

struct qemu__chmod
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__chmod(const char *path, int flags)
{
    struct qemu__chmod call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHMOD);
    call.path = (ULONG_PTR)path;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__chmod(struct qemu_syscall *call)
{
    struct qemu__chmod *c = (struct qemu__chmod *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__chmod(QEMU_G2H(c->path), c->flags);
}

#endif

struct qemu__wchmod
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wchmod(const WCHAR *path, int flags)
{
    struct qemu__wchmod call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCHMOD);
    call.path = (ULONG_PTR)path;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wchmod(struct qemu_syscall *call)
{
    struct qemu__wchmod *c = (struct qemu__wchmod *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wchmod(QEMU_G2H(c->path), c->flags);
}

#endif

struct qemu__unlink
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__unlink(const char *path)
{
    struct qemu__unlink call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLINK);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__unlink(struct qemu_syscall *call)
{
    struct qemu__unlink *c = (struct qemu__unlink *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__unlink(QEMU_G2H(c->path));
}

#endif

struct qemu__wunlink
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wunlink(const WCHAR *path)
{
    struct qemu__wunlink call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WUNLINK);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wunlink(struct qemu_syscall *call)
{
    struct qemu__wunlink *c = (struct qemu__wunlink *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wunlink(QEMU_G2H(c->path));
}

#endif

struct qemu__commit
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__commit(int fd)
{
    struct qemu__commit call;
    call.super.id = QEMU_SYSCALL_ID(CALL__COMMIT);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__commit(struct qemu_syscall *call)
{
    struct qemu__commit *c = (struct qemu__commit *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__commit(c->fd);
}

#endif

struct qemu__flushall
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__flushall(void)
{
    struct qemu__flushall call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FLUSHALL);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__flushall(struct qemu_syscall *call)
{
    struct qemu__flushall *c = (struct qemu__flushall *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__flushall();
}

#endif

struct qemu__fflush_nolock
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fflush_nolock(FILE* file)
{
    struct qemu__fflush_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FFLUSH_NOLOCK);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fflush_nolock(struct qemu_syscall *call)
{
    struct qemu__fflush_nolock *c = (struct qemu__fflush_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fflush_nolock(FILE_g2h(c->file));
}

#endif

struct qemu__close
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__close(int fd)
{
    struct qemu__close call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CLOSE);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__close(struct qemu_syscall *call)
{
    struct qemu__close *c = (struct qemu__close *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__close(c->fd);
}

#endif

struct qemu__dup2
{
    struct qemu_syscall super;
    uint64_t od;
    uint64_t nd;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__dup2(int od, int nd)
{
    struct qemu__dup2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DUP2);
    call.od = (ULONG_PTR)od;
    call.nd = (ULONG_PTR)nd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dup2(struct qemu_syscall *call)
{
    struct qemu__dup2 *c = (struct qemu__dup2 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dup2(c->od, c->nd);
}

#endif

struct qemu__dup
{
    struct qemu_syscall super;
    uint64_t od;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__dup(int od)
{
    struct qemu__dup call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DUP);
    call.od = (ULONG_PTR)od;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__dup(struct qemu_syscall *call)
{
    struct qemu__dup *c = (struct qemu__dup *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__dup(c->od);
}

#endif

struct qemu__eof
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__eof(int fd)
{
    struct qemu__eof call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EOF);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__eof(struct qemu_syscall *call)
{
    struct qemu__eof *c = (struct qemu__eof *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__eof(c->fd);
}

#endif

struct qemu__fcloseall
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fcloseall(void)
{
    struct qemu__fcloseall call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FCLOSEALL);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fcloseall(struct qemu_syscall *call)
{
    struct qemu__fcloseall *c = (struct qemu__fcloseall *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fcloseall();
}

#endif

struct qemu__lock_file
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__lock_file(FILE *file)
{
    struct qemu__lock_file call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCK_FILE);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);
}

#else

void qemu__lock_file(struct qemu_syscall *call)
{
    struct qemu__lock_file *c = (struct qemu__lock_file *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p__lock_file(FILE_g2h(c->file));
}

#endif

struct qemu__unlock_file
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__unlock_file(FILE *file)
{
    struct qemu__unlock_file call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLOCK_FILE);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);
}

#else

void qemu__unlock_file(struct qemu_syscall *call)
{
    struct qemu__unlock_file *c = (struct qemu__unlock_file *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p__unlock_file(FILE_g2h(c->file));
}

#endif

struct qemu__locking
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t mode;
    uint64_t nbytes;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__locking(int fd, int mode, LONG nbytes)
{
    struct qemu__locking call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCKING);
    call.fd = (ULONG_PTR)fd;
    call.mode = (ULONG_PTR)mode;
    call.nbytes = (ULONG_PTR)nbytes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__locking(struct qemu_syscall *call)
{
    struct qemu__locking *c = (struct qemu__locking *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__locking(c->fd, c->mode, c->nbytes);
}

#endif

struct qemu__fseeki64
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t offset;
    uint64_t whence;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fseeki64(FILE* file, __int64 offset, int whence)
{
    struct qemu__fseeki64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSEEKI64);
    call.file = (ULONG_PTR)file;
    call.offset = (ULONG_PTR)offset;
    call.whence = (ULONG_PTR)whence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fseeki64(struct qemu_syscall *call)
{
    struct qemu__fseeki64 *c = (struct qemu__fseeki64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fseeki64(FILE_g2h(c->file), c->offset, c->whence);
}

#endif

struct qemu__fseeki64_nolock
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t offset;
    uint64_t whence;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fseeki64_nolock(FILE* file, __int64 offset, int whence)
{
    struct qemu__fseeki64_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSEEKI64_NOLOCK);
    call.file = (ULONG_PTR)file;
    call.offset = (ULONG_PTR)offset;
    call.whence = (ULONG_PTR)whence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fseeki64_nolock(struct qemu_syscall *call)
{
    struct qemu__fseeki64_nolock *c = (struct qemu__fseeki64_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fseeki64_nolock(FILE_g2h(c->file), c->offset, c->whence);
}

#endif

struct qemu_fseek
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t offset;
    uint64_t whence;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fseek(FILE* file, LONG offset, int whence)
{
    struct qemu_fseek call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FSEEK);
    call.file = (ULONG_PTR)file;
    call.offset = (ULONG_PTR)offset;
    call.whence = (ULONG_PTR)whence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fseek(struct qemu_syscall *call)
{
    struct qemu_fseek *c = (struct qemu_fseek *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fseek(FILE_g2h(c->file), c->offset, c->whence);
}

#endif

struct qemu__fseek_nolock
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t offset;
    uint64_t whence;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fseek_nolock(FILE* file, LONG offset, int whence)
{
    struct qemu__fseek_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSEEK_NOLOCK);
    call.file = (ULONG_PTR)file;
    call.offset = (ULONG_PTR)offset;
    call.whence = (ULONG_PTR)whence;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fseek_nolock(struct qemu_syscall *call)
{
    struct qemu__fseek_nolock *c = (struct qemu__fseek_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fseek_nolock(FILE_g2h(c->file), c->offset, c->whence);
}

#endif

struct qemu__chsize_s
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__chsize_s(int fd, __int64 size)
{
    struct qemu__chsize_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHSIZE_S);
    call.fd = (ULONG_PTR)fd;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__chsize_s(struct qemu_syscall *call)
{
    struct qemu__chsize_s *c = (struct qemu__chsize_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__chsize_s(c->fd, c->size);
}

#endif

struct qemu__chsize
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__chsize(int fd, LONG size)
{
    struct qemu__chsize call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CHSIZE);
    call.fd = (ULONG_PTR)fd;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__chsize(struct qemu_syscall *call)
{
    struct qemu__chsize *c = (struct qemu__chsize *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__chsize(c->fd, c->size);
}

#endif

struct qemu_clearerr
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_clearerr(FILE* file)
{
    struct qemu_clearerr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEARERR);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);
}

#else

void qemu_clearerr(struct qemu_syscall *call)
{
    struct qemu_clearerr *c = (struct qemu_clearerr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_clearerr(FILE_g2h(c->file));
}

#endif

struct qemu_rewind
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_rewind(FILE* file)
{
    struct qemu_rewind call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REWIND);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);
}

#else

void qemu_rewind(struct qemu_syscall *call)
{
    struct qemu_rewind *c = (struct qemu_rewind *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_rewind(FILE_g2h(c->file));
}

#endif

struct qemu__fdopen
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT__fdopen(int fd, const char *mode)
{
    struct qemu__fdopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FDOPEN);
    call.fd = (ULONG_PTR)fd;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__fdopen(struct qemu_syscall *call)
{
    struct qemu__fdopen *c = (struct qemu__fdopen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__fdopen(c->fd, QEMU_G2H(c->mode)));
}

#endif

struct qemu__wfdopen
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT__wfdopen(int fd, const WCHAR *mode)
{
    struct qemu__wfdopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFDOPEN);
    call.fd = (ULONG_PTR)fd;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wfdopen(struct qemu_syscall *call)
{
    struct qemu__wfdopen *c = (struct qemu__wfdopen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wfdopen(c->fd, QEMU_G2H(c->mode)));
}

#endif

struct qemu__filelength
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT__filelength(int fd)
{
    struct qemu__filelength call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FILELENGTH);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__filelength(struct qemu_syscall *call)
{
    struct qemu__filelength *c = (struct qemu__filelength *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__filelength(c->fd);
}

#endif

struct qemu__filelengthi64
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL MSVCRT__filelengthi64(int fd)
{
    struct qemu__filelengthi64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FILELENGTHI64);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__filelengthi64(struct qemu_syscall *call)
{
    struct qemu__filelengthi64 *c = (struct qemu__filelengthi64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__filelengthi64(c->fd);
}

#endif

struct qemu__fstat64
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fstat64(int fd, struct __stat64* buf)
{
    struct qemu__fstat64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSTAT64);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fstat64(struct qemu_syscall *call)
{
    struct qemu__fstat64 *c = (struct qemu__fstat64 *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__fstat64(c->fd, QEMU_G2H(c->buf));
}

#endif

struct qemu__fstati64
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fstati64(int fd, struct _stati64* buf)
{
    struct qemu__fstati64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSTATI64);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fstati64(struct qemu_syscall *call)
{
    struct qemu__fstati64 *c = (struct qemu__fstati64 *)(ULONG_PTR)call;
    /* stati64 has the same size on 32 and 64 bit, apparently because stati64 is
     * strategically defined on 32 bit to have this property :-) . */
    WINE_TRACE("\n");
    c->super.iret = p__fstati64(c->fd, QEMU_G2H(c->buf));
}

#endif

struct qemu__fstat
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fstat(int fd, struct _stat* buf)
{
    struct qemu__fstat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSTAT);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fstat(struct qemu_syscall *call)
{
    struct qemu__fstat *c = (struct qemu__fstat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fstat(c->fd, QEMU_G2H(c->buf));
}

#endif

struct qemu__fstat32
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fstat32(int fd, struct _stat32* buf)
{
    struct qemu__fstat32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSTAT32);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fstat32(struct qemu_syscall *call)
{
    struct qemu__fstat32 *c = (struct qemu__fstat32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fstat32(c->fd, QEMU_G2H(c->buf));
}

#endif

struct qemu__fstat32i64
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fstat32i64(int fd, struct _stat32i64* buf)
{
    struct qemu__fstat32i64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSTAT32I64);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fstat32i64(struct qemu_syscall *call)
{
    struct qemu__fstat32i64 *c = (struct qemu__fstat32i64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fstat32i64(c->fd, QEMU_G2H(c->buf));
}

#endif

struct qemu__fstat64i32
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fstat64i32(int fd, struct _stat64i32* buf)
{
    struct qemu__fstat64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSTAT64I32);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fstat64i32(struct qemu_syscall *call)
{
    struct qemu__fstat64i32 *c = (struct qemu__fstat64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fstat64i32(c->fd, QEMU_G2H(c->buf));
}

#endif

struct qemu__futime64
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__futime64(int fd, struct __utimbuf64 *t)
{
    struct qemu__futime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FUTIME64);
    call.fd = (ULONG_PTR)fd;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__futime64(struct qemu_syscall *call)
{
    struct qemu__futime64 *c = (struct qemu__futime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__futime64(c->fd, QEMU_G2H(c->t));
}

#endif

struct qemu__futime32
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__futime32(int fd, struct __utimbuf32 *t)
{
    struct qemu__futime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FUTIME32);
    call.fd = (ULONG_PTR)fd;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__futime32(struct qemu_syscall *call)
{
    struct qemu__futime32 *c = (struct qemu__futime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__futime32(c->fd, QEMU_G2H(c->t));
}

#endif

struct qemu__futime
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__futime(int fd, struct __utimbuf64 *t)
{
    struct qemu__futime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FUTIME);
    call.fd = (ULONG_PTR)fd;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__futime(struct qemu_syscall *call)
{
    struct qemu__futime *c = (struct qemu__futime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__futime(c->fd, QEMU_G2H(c->t));
}

#endif

struct qemu__get_osfhandle
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

intptr_t CDECL MSVCRT__get_osfhandle(int fd)
{
    struct qemu__get_osfhandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_OSFHANDLE);
    call.fd = fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_osfhandle(struct qemu_syscall *call)
{
    struct qemu__get_osfhandle *c = (struct qemu__get_osfhandle *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__get_osfhandle(c->fd);
}

#endif

struct qemu__mktemp_s
{
    struct qemu_syscall super;
    uint64_t pattern;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__mktemp_s(char *pattern, size_t size)
{
    struct qemu__mktemp_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKTEMP_S);
    call.pattern = (ULONG_PTR)pattern;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mktemp_s(struct qemu_syscall *call)
{
    struct qemu__mktemp_s *c = (struct qemu__mktemp_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mktemp_s(QEMU_G2H(c->pattern), c->size);
}

#endif

struct qemu__mktemp
{
    struct qemu_syscall super;
    uint64_t pattern;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__mktemp(char *pattern)
{
    struct qemu__mktemp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKTEMP);
    call.pattern = (ULONG_PTR)pattern;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mktemp(struct qemu_syscall *call)
{
    struct qemu__mktemp *c = (struct qemu__mktemp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mktemp(QEMU_G2H(c->pattern)));
}

#endif

struct qemu__wmktemp_s
{
    struct qemu_syscall super;
    uint64_t pattern;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wmktemp_s(WCHAR *pattern, size_t size)
{
    struct qemu__wmktemp_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WMKTEMP_S);
    call.pattern = (ULONG_PTR)pattern;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wmktemp_s(struct qemu_syscall *call)
{
    struct qemu__wmktemp_s *c = (struct qemu__wmktemp_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wmktemp_s(QEMU_G2H(c->pattern), c->size);
}

#endif

struct qemu__wmktemp
{
    struct qemu_syscall super;
    uint64_t pattern;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT__wmktemp(WCHAR *pattern)
{
    struct qemu__wmktemp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WMKTEMP);
    call.pattern = (ULONG_PTR)pattern;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wmktemp(struct qemu_syscall *call)
{
    struct qemu__wmktemp *c = (struct qemu__wmktemp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wmktemp(QEMU_G2H(c->pattern)));
}

#endif

struct qemu__pipe
{
    struct qemu_syscall super;
    uint64_t pfds;
    uint64_t psize;
    uint64_t textmode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__pipe(int *pfds, unsigned int psize, int textmode)
{
    struct qemu__pipe call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PIPE);
    call.pfds = (ULONG_PTR)pfds;
    call.psize = (ULONG_PTR)psize;
    call.textmode = (ULONG_PTR)textmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__pipe(struct qemu_syscall *call)
{
    struct qemu__pipe *c = (struct qemu__pipe *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__pipe(QEMU_G2H(c->pfds), c->psize, c->textmode);
}

#endif

struct qemu__wsopen_dispatch
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t oflags;
    uint64_t shflags;
    uint64_t pmode;
    uint64_t fd;
    uint64_t secure;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wsopen_dispatch(const WCHAR* path, int oflags, int shflags, int pmode, int *fd, int secure)
{
    struct qemu__wsopen_dispatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSOPEN_DISPATCH);
    call.path = (ULONG_PTR)path;
    call.oflags = (ULONG_PTR)oflags;
    call.shflags = (ULONG_PTR)shflags;
    call.pmode = (ULONG_PTR)pmode;
    call.fd = (ULONG_PTR)fd;
    call.secure = (ULONG_PTR)secure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wsopen_dispatch(struct qemu_syscall *call)
{
    struct qemu__wsopen_dispatch *c = (struct qemu__wsopen_dispatch *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wsopen_dispatch(QEMU_G2H(c->path), c->oflags, c->shflags, c->pmode, QEMU_G2H(c->fd), c->secure);
}

#endif

struct qemu__wsopen_s
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t path;
    uint64_t oflags;
    uint64_t shflags;
    uint64_t pmode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wsopen_s(int *fd, const WCHAR* path, int oflags, int shflags, int pmode)
{
    struct qemu__wsopen_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSOPEN_S);
    call.fd = (ULONG_PTR)fd;
    call.path = (ULONG_PTR)path;
    call.oflags = (ULONG_PTR)oflags;
    call.shflags = (ULONG_PTR)shflags;
    call.pmode = (ULONG_PTR)pmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wsopen_s(struct qemu_syscall *call)
{
    struct qemu__wsopen_s *c = (struct qemu__wsopen_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wsopen_s(QEMU_G2H(c->fd), QEMU_G2H(c->path), c->oflags, c->shflags, c->pmode);
}

#endif

struct qemu__sopen_dispatch
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t oflags;
    uint64_t shflags;
    uint64_t pmode;
    uint64_t fd;
    uint64_t secure;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__sopen_dispatch(const char *path, int oflags, int shflags, int pmode, int *fd, int secure)
{
    struct qemu__sopen_dispatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SOPEN_DISPATCH);
    call.path = (ULONG_PTR)path;
    call.oflags = (ULONG_PTR)oflags;
    call.shflags = (ULONG_PTR)shflags;
    call.pmode = (ULONG_PTR)pmode;
    call.fd = (ULONG_PTR)fd;
    call.secure = (ULONG_PTR)secure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__sopen_dispatch(struct qemu_syscall *call)
{
    struct qemu__sopen_dispatch *c = (struct qemu__sopen_dispatch *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__sopen_dispatch(QEMU_G2H(c->path), c->oflags, c->shflags, c->pmode, QEMU_G2H(c->fd), c->secure);
}

#endif

struct qemu__sopen_s
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t path;
    uint64_t oflags;
    uint64_t shflags;
    uint64_t pmode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__sopen_s(int *fd, const char *path, int oflags, int shflags, int pmode)
{
    struct qemu__sopen_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SOPEN_S);
    call.fd = (ULONG_PTR)fd;
    call.path = (ULONG_PTR)path;
    call.oflags = (ULONG_PTR)oflags;
    call.shflags = (ULONG_PTR)shflags;
    call.pmode = (ULONG_PTR)pmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__sopen_s(struct qemu_syscall *call)
{
    struct qemu__sopen_s *c = (struct qemu__sopen_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__sopen_s(QEMU_G2H(c->fd), QEMU_G2H(c->path), c->oflags, c->shflags, c->pmode);
}

#endif

struct qemu__creat
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t pmode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__creat(const char *path, int pmode)
{
    struct qemu__creat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CREAT);
    call.path = (ULONG_PTR)path;
    call.pmode = (ULONG_PTR)pmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__creat(struct qemu_syscall *call)
{
    struct qemu__creat *c = (struct qemu__creat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__creat(QEMU_G2H(c->path), c->pmode);
}

#endif

struct qemu__wcreat
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t pmode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wcreat(const WCHAR *path, int pmode)
{
    struct qemu__wcreat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCREAT);
    call.path = (ULONG_PTR)path;
    call.pmode = (ULONG_PTR)pmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcreat(struct qemu_syscall *call)
{
    struct qemu__wcreat *c = (struct qemu__wcreat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcreat(QEMU_G2H(c->path), c->pmode);
}

#endif

struct qemu__open_osfhandle
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t oflags;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__open_osfhandle(intptr_t handle, int oflags)
{
    struct qemu__open_osfhandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL__OPEN_OSFHANDLE);
    call.handle = (ULONG_PTR)handle;
    call.oflags = (ULONG_PTR)oflags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__open_osfhandle(struct qemu_syscall *call)
{
    struct qemu__open_osfhandle *c = (struct qemu__open_osfhandle *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__open_osfhandle(c->handle, c->oflags);
}

#endif

struct qemu__rmtmp
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__rmtmp(void)
{
    struct qemu__rmtmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__RMTMP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__rmtmp(struct qemu_syscall *call)
{
    struct qemu__rmtmp *c = (struct qemu__rmtmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__rmtmp();
}

#endif

struct qemu__read
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t buf;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__read(int fd, void *buf, unsigned int count)
{
    struct qemu__read call;
    call.super.id = QEMU_SYSCALL_ID(CALL__READ);
    call.fd = (ULONG_PTR)fd;
    call.buf = (ULONG_PTR)buf;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__read(struct qemu_syscall *call)
{
    struct qemu__read *c = (struct qemu__read *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__read(c->fd, QEMU_G2H(c->buf), c->count);
}

#endif

struct qemu__setmode
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__setmode(int fd,int mode)
{
    struct qemu__setmode call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SETMODE);
    call.fd = (ULONG_PTR)fd;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__setmode(struct qemu_syscall *call)
{
    struct qemu__setmode *c = (struct qemu__setmode *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__setmode(c->fd, c->mode);
}

#endif

struct qemu__stat64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__stat64(const char* path, struct __stat64 * buf)
{
    struct qemu__stat64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STAT64);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stat64(struct qemu_syscall *call)
{
    struct qemu__stat64 *c = (struct qemu__stat64 *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__stat64(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu_stati64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_stati64(const char* path, struct _stati64 * buf)
{
    struct qemu_stati64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STATI64);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_stati64(struct qemu_syscall *call)
{
    struct qemu_stati64 *c = (struct qemu_stati64 *)(ULONG_PTR)call;
    /* stati64 has the same size on 32 and 64 bit, apparently because stati64 is
     * strategically defined on 32 bit to have this property :-) . */
    c->super.iret = p_stati64(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu_stat
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_stat(const char* path, struct _stat * buf)
{
    struct qemu_stat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STAT);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_stat(struct qemu_syscall *call)
{
    struct qemu_stat *c = (struct qemu_stat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_stat(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__stat32
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__stat32(const char *path, struct _stat32 *buf)
{
    struct qemu__stat32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STAT32);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stat32(struct qemu_syscall *call)
{
    struct qemu__stat32 *c = (struct qemu__stat32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__stat32(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__stat32i64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__stat32i64(const char *path, struct _stat32i64 *buf)
{
    struct qemu__stat32i64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STAT32I64);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stat32i64(struct qemu_syscall *call)
{
    struct qemu__stat32i64 *c = (struct qemu__stat32i64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__stat32i64(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__stat64i32
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__stat64i32(const char* path, struct _stat64i32 *buf)
{
    struct qemu__stat64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STAT64I32);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stat64i32(struct qemu_syscall *call)
{
    struct qemu__stat64i32 *c = (struct qemu__stat64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__stat64i32(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__wstat64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wstat64(const WCHAR* path, struct __stat64 * buf)
{
    struct qemu__wstat64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTAT64);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstat64(struct qemu_syscall *call)
{
    struct qemu__wstat64 *c = (struct qemu__wstat64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstat64(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__wstati64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wstati64(const WCHAR* path, struct _stati64 * buf)
{
    struct qemu__wstati64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTATI64);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstati64(struct qemu_syscall *call)
{
    struct qemu__wstati64 *c = (struct qemu__wstati64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstati64(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__wstat
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wstat(const WCHAR* path, struct _stat * buf)
{
    struct qemu__wstat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTAT);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstat(struct qemu_syscall *call)
{
    struct qemu__wstat *c = (struct qemu__wstat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstat(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__wstat32
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wstat32(const WCHAR *path, struct _stat32 *buf)
{
    struct qemu__wstat32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTAT32);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstat32(struct qemu_syscall *call)
{
    struct qemu__wstat32 *c = (struct qemu__wstat32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstat32(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__wstat32i64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wstat32i64(const WCHAR *path, struct _stat32i64 *buf)
{
    struct qemu__wstat32i64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTAT32I64);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstat32i64(struct qemu_syscall *call)
{
    struct qemu__wstat32i64 *c = (struct qemu__wstat32i64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstat32i64(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__wstat64i32
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wstat64i32(const WCHAR *path, struct _stat64i32 *buf)
{
    struct qemu__wstat64i32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTAT64I32);
    call.path = (ULONG_PTR)path;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstat64i32(struct qemu_syscall *call)
{
    struct qemu__wstat64i32 *c = (struct qemu__wstat64i32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstat64i32(QEMU_G2H(c->path), QEMU_G2H(c->buf));
}

#endif

struct qemu__tell
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT__tell(int fd)
{
    struct qemu__tell call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TELL);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__tell(struct qemu_syscall *call)
{
    struct qemu__tell *c = (struct qemu__tell *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__tell(c->fd);
}

#endif

struct qemu__telli64
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL _telli64(int fd)
{
    struct qemu__telli64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TELLI64);
    call.fd = (ULONG_PTR)fd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__telli64(struct qemu_syscall *call)
{
    struct qemu__telli64 *c = (struct qemu__telli64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__telli64(c->fd);
}

#endif

struct qemu__wtempnam
{
    struct qemu_syscall super;
    uint64_t dir;
    uint64_t prefix;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT__wtempnam(const WCHAR *dir, const WCHAR *prefix)
{
    struct qemu__wtempnam call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTEMPNAM);
    call.dir = (ULONG_PTR)dir;
    call.prefix = (ULONG_PTR)prefix;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wtempnam(struct qemu_syscall *call)
{
    struct qemu__wtempnam *c = (struct qemu__wtempnam *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wtempnam(QEMU_G2H(c->dir), QEMU_G2H(c->prefix)));
}

#endif

struct qemu__umask
{
    struct qemu_syscall super;
    uint64_t umask;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__umask(int umask)
{
    struct qemu__umask call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UMASK);
    call.umask = (ULONG_PTR)umask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__umask(struct qemu_syscall *call)
{
    struct qemu__umask *c = (struct qemu__umask *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__umask(c->umask);
}

#endif

struct qemu__utime64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__utime64(const char* path, struct __utimbuf64 *t)
{
    struct qemu__utime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UTIME64);
    call.path = (ULONG_PTR)path;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__utime64(struct qemu_syscall *call)
{
    struct qemu__utime64 *c = (struct qemu__utime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__utime64(QEMU_G2H(c->path), QEMU_G2H(c->t));
}

#endif

struct qemu__utime32
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__utime32(const char* path, struct __utimbuf32 *t)
{
    struct qemu__utime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UTIME32);
    call.path = (ULONG_PTR)path;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__utime32(struct qemu_syscall *call)
{
    struct qemu__utime32 *c = (struct qemu__utime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__utime32(QEMU_G2H(c->path), QEMU_G2H(c->t));
}

#endif

struct qemu__utime
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__utime(const char* path, struct __utimbuf64 *t)
{
    struct qemu__utime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UTIME);
    call.path = (ULONG_PTR)path;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__utime(struct qemu_syscall *call)
{
    struct qemu__utime *c = (struct qemu__utime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__utime(QEMU_G2H(c->path), QEMU_G2H(c->t));
}

#endif

struct qemu__wutime64
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wutime64(const WCHAR* path, struct __utimbuf64 *t)
{
    struct qemu__wutime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WUTIME64);
    call.path = (ULONG_PTR)path;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wutime64(struct qemu_syscall *call)
{
    struct qemu__wutime64 *c = (struct qemu__wutime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wutime64(QEMU_G2H(c->path), QEMU_G2H(c->t));
}

#endif

struct qemu__wutime32
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wutime32(const WCHAR* path, struct __utimbuf32 *t)
{
    struct qemu__wutime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WUTIME32);
    call.path = (ULONG_PTR)path;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wutime32(struct qemu_syscall *call)
{
    struct qemu__wutime32 *c = (struct qemu__wutime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wutime32(QEMU_G2H(c->path), QEMU_G2H(c->t));
}

#endif

struct qemu__wutime
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t t;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wutime(const WCHAR* path, struct __utimbuf64 *t)
{
    struct qemu__wutime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WUTIME);
    call.path = (ULONG_PTR)path;
    call.t = (ULONG_PTR)t;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wutime(struct qemu_syscall *call)
{
    struct qemu__wutime *c = (struct qemu__wutime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wutime(QEMU_G2H(c->path), QEMU_G2H(c->t));
}

#endif

struct qemu__putw
{
    struct qemu_syscall super;
    uint64_t val;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__putw(int val, FILE* file)
{
    struct qemu__putw call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTW);
    call.val = (ULONG_PTR)val;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putw(struct qemu_syscall *call)
{
    struct qemu__putw *c = (struct qemu__putw *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putw(c->val, QEMU_G2H(c->file));
}

#endif

struct qemu_fclose
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fclose(FILE* file)
{
    struct qemu_fclose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FCLOSE);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fclose(struct qemu_syscall *call)
{
    struct qemu_fclose *c = (struct qemu_fclose *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_fclose(FILE_g2h(c->file));
}

#endif

struct qemu__fclose_nolock
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fclose_nolock(FILE* file)
{
    struct qemu__fclose_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FCLOSE_NOLOCK);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fclose_nolock(struct qemu_syscall *call)
{
    struct qemu__fclose_nolock *c = (struct qemu__fclose_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fclose_nolock(FILE_g2h(c->file));
}

#endif

struct qemu_feof
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_feof(FILE* file)
{
    struct qemu_feof call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FEOF);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_feof(struct qemu_syscall *call)
{
    struct qemu_feof *c = (struct qemu_feof *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_feof(FILE_g2h(c->file));
}

#endif

struct qemu_ferror
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_ferror(FILE* file)
{
    struct qemu_ferror call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FERROR);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ferror(struct qemu_syscall *call)
{
    struct qemu_ferror *c = (struct qemu_ferror *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ferror(FILE_g2h(c->file));
}

#endif

struct qemu__filbuf
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__filbuf(FILE* file)
{
    struct qemu__filbuf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FILBUF);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__filbuf(struct qemu_syscall *call)
{
    struct qemu__filbuf *c = (struct qemu__filbuf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__filbuf(FILE_g2h(c->file));
}

#endif

struct qemu_fgetc
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fgetc(FILE* file)
{
    struct qemu_fgetc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FGETC);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fgetc(struct qemu_syscall *call)
{
    struct qemu_fgetc *c = (struct qemu_fgetc *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_fgetc(FILE_g2h(c->file));
}

#endif

struct qemu__fgetc_nolock
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fgetc_nolock(FILE* file)
{
    struct qemu__fgetc_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FGETC_NOLOCK);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fgetc_nolock(struct qemu_syscall *call)
{
    struct qemu__fgetc_nolock *c = (struct qemu__fgetc_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fgetc_nolock(FILE_g2h(c->file));
}

#endif

struct qemu__fgetchar
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fgetchar(void)
{
    struct qemu__fgetchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FGETCHAR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fgetchar(struct qemu_syscall *call)
{
    struct qemu__fgetchar *c = (struct qemu__fgetchar *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fgetchar();
}

#endif

struct qemu_fgets
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t size;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_fgets(char *s, int size, FILE* file)
{
    struct qemu_fgets call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FGETS);
    call.s = (ULONG_PTR)s;
    call.size = (ULONG_PTR)size;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_fgets(struct qemu_syscall *call)
{
    struct qemu_fgets *c = (struct qemu_fgets *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_fgets(QEMU_G2H(c->s), c->size, FILE_g2h(c->file)));
}

#endif

struct qemu_fgetwc
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT_fgetwc(FILE* file)
{
    struct qemu_fgetwc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FGETWC);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fgetwc(struct qemu_syscall *call)
{
    struct qemu_fgetwc *c = (struct qemu_fgetwc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fgetwc(FILE_g2h(c->file));
}

#endif

struct qemu__fgetwc_nolock
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT__fgetwc_nolock(FILE* file)
{
    struct qemu__fgetwc_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FGETWC_NOLOCK);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fgetwc_nolock(struct qemu_syscall *call)
{
    struct qemu__fgetwc_nolock *c = (struct qemu__fgetwc_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fgetwc_nolock(FILE_g2h(c->file));
}

#endif

struct qemu__getw
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__getw(FILE* file)
{
    struct qemu__getw call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETW);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getw(struct qemu_syscall *call)
{
    struct qemu__getw *c = (struct qemu__getw *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getw(FILE_g2h(c->file));
}

#endif

struct qemu_getwc
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT_getwc(FILE* file)
{
    struct qemu_getwc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWC);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_getwc(struct qemu_syscall *call)
{
    struct qemu_getwc *c = (struct qemu_getwc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getwc(FILE_g2h(c->file));
}

#endif

struct qemu__fgetwchar
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT__fgetwchar(void)
{
    struct qemu__fgetwchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FGETWCHAR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fgetwchar(struct qemu_syscall *call)
{
    struct qemu__fgetwchar *c = (struct qemu__fgetwchar *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fgetwchar();
}

#endif

struct qemu_getwchar
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT_getwchar(void)
{
    struct qemu_getwchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWCHAR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_getwchar(struct qemu_syscall *call)
{
    struct qemu_getwchar *c = (struct qemu_getwchar *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getwchar();
}

#endif

struct qemu_fgetws
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t size;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT_fgetws(WCHAR *s, int size, FILE* file)
{
    struct qemu_fgetws call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FGETWS);
    call.s = (ULONG_PTR)s;
    call.size = (ULONG_PTR)size;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_fgetws(struct qemu_syscall *call)
{
    struct qemu_fgetws *c = (struct qemu_fgetws *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_fgetws(QEMU_G2H(c->s), c->size, FILE_g2h(c->file)));
}

#endif

struct qemu__flsbuf
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__flsbuf(int c, FILE* file)
{
    struct qemu__flsbuf call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FLSBUF);
    call.c = (ULONG_PTR)c;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__flsbuf(struct qemu_syscall *call)
{
    struct qemu__flsbuf *c = (struct qemu__flsbuf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__flsbuf(c->c, FILE_g2h(c->file));
}

#endif

struct qemu__fwrite_nolock
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
    uint64_t nmemb;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__fwrite_nolock(const void *ptr, size_t size, size_t nmemb, FILE* file)
{
    struct qemu__fwrite_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FWRITE_NOLOCK);
    call.ptr = (ULONG_PTR)ptr;
    call.size = (ULONG_PTR)size;
    call.nmemb = (ULONG_PTR)nmemb;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fwrite_nolock(struct qemu_syscall *call)
{
    struct qemu__fwrite_nolock *c = (struct qemu__fwrite_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fwrite_nolock(QEMU_G2H(c->ptr), c->size, c->nmemb, FILE_g2h(c->file));
}

#endif

struct qemu_fputwc
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT_fputwc(wint_t wc, FILE* file)
{
    struct qemu_fputwc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FPUTWC);
    call.wc = (ULONG_PTR)wc;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fputwc(struct qemu_syscall *call)
{
    struct qemu_fputwc *c = (struct qemu_fputwc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fputwc(c->wc, FILE_g2h(c->file));
}

#endif

struct qemu__fputwc_nolock
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT__fputwc_nolock(wint_t wc, FILE* file)
{
    struct qemu__fputwc_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FPUTWC_NOLOCK);
    call.wc = (ULONG_PTR)wc;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fputwc_nolock(struct qemu_syscall *call)
{
    struct qemu__fputwc_nolock *c = (struct qemu__fputwc_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fputwc_nolock(c->wc, FILE_g2h(c->file));
}

#endif

struct qemu__fputwchar
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT__fputwchar(wint_t wc)
{
    struct qemu__fputwchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FPUTWCHAR);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fputwchar(struct qemu_syscall *call)
{
    struct qemu__fputwchar *c = (struct qemu__fputwchar *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fputwchar(c->wc);
}

#endif

struct qemu__wfsopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
    uint64_t share;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT__wfsopen(const WCHAR *path, const WCHAR *mode, int share)
{
    struct qemu__wfsopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFSOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;
    call.share = (ULONG_PTR)share;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wfsopen(struct qemu_syscall *call)
{
    struct qemu__wfsopen *c = (struct qemu__wfsopen *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p__wfsopen(QEMU_G2H(c->path), QEMU_G2H(c->mode), c->share));
}

#endif

struct qemu__fsopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
    uint64_t share;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT__fsopen(const char *path, const char *mode, int share)
{
    struct qemu__fsopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FSOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;
    call.share = (ULONG_PTR)share;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__fsopen(struct qemu_syscall *call)
{
    struct qemu__fsopen *c = (struct qemu__fsopen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__fsopen(QEMU_G2H(c->path), QEMU_G2H(c->mode), c->share));
}

#endif

struct qemu_fopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT_fopen(const char *path, const char *mode)
{
    struct qemu_fopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_fopen(struct qemu_syscall *call)
{
    struct qemu_fopen *c = (struct qemu_fopen *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_fopen(QEMU_G2H(c->path), QEMU_G2H(c->mode)));
}

#endif

struct qemu_fopen_s
{
    struct qemu_syscall super;
    uint64_t pFile;
    uint64_t filename;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fopen_s(FILE** pFile, const char *filename, const char *mode)
{
    struct qemu_fopen_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FOPEN_S);
    call.pFile = (ULONG_PTR)pFile;
    call.filename = (ULONG_PTR)filename;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fopen_s(struct qemu_syscall *call)
{
    struct qemu_fopen_s *c = (struct qemu_fopen_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fopen_s(QEMU_G2H(c->pFile), QEMU_G2H(c->filename), QEMU_G2H(c->mode));
}

#endif

struct qemu__wfopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT__wfopen(const WCHAR *path, const WCHAR *mode)
{
    struct qemu__wfopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wfopen(struct qemu_syscall *call)
{
    struct qemu__wfopen *c = (struct qemu__wfopen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wfopen(QEMU_G2H(c->path), QEMU_G2H(c->mode)));
}

#endif

struct qemu__wfopen_s
{
    struct qemu_syscall super;
    uint64_t pFile;
    uint64_t filename;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfopen_s(FILE** pFile, const WCHAR *filename, const WCHAR *mode)
{
    struct qemu__wfopen_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFOPEN_S);
    call.pFile = (ULONG_PTR)pFile;
    call.filename = (ULONG_PTR)filename;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfopen_s(struct qemu_syscall *call)
{
    struct qemu__wfopen_s *c = (struct qemu__wfopen_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfopen_s(QEMU_G2H(c->pFile), QEMU_G2H(c->filename), QEMU_G2H(c->mode));
}

#endif

struct qemu_fputc
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fputc(int c, FILE* file)
{
    struct qemu_fputc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FPUTC);
    call.c = (ULONG_PTR)c;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fputc(struct qemu_syscall *call)
{
    struct qemu_fputc *c = (struct qemu_fputc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fputc(c->c, FILE_g2h(c->file));
}

#endif

struct qemu__fputc_nolock
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fputc_nolock(int c, FILE* file)
{
    struct qemu__fputc_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FPUTC_NOLOCK);
    call.c = (ULONG_PTR)c;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fputc_nolock(struct qemu_syscall *call)
{
    struct qemu__fputc_nolock *c = (struct qemu__fputc_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fputc_nolock(c->c, FILE_g2h(c->file));
}

#endif

struct qemu__fputchar
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__fputchar(int c)
{
    struct qemu__fputchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FPUTCHAR);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fputchar(struct qemu_syscall *call)
{
    struct qemu__fputchar *c = (struct qemu__fputchar *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fputchar(c->c);
}

#endif

struct qemu__fread_nolock
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
    uint64_t nmemb;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__fread_nolock(void *ptr, size_t size, size_t nmemb, FILE* file)
{
    struct qemu__fread_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FREAD_NOLOCK);
    call.ptr = (ULONG_PTR)ptr;
    call.size = (ULONG_PTR)size;
    call.nmemb = (ULONG_PTR)nmemb;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fread_nolock(struct qemu_syscall *call)
{
    struct qemu__fread_nolock *c = (struct qemu__fread_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fread_nolock(QEMU_G2H(c->ptr), c->size, c->nmemb, FILE_g2h(c->file));
}

#endif

struct qemu_fread_s
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t buf_size;
    uint64_t elem_size;
    uint64_t count;
    uint64_t stream;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_fread_s(void *buf, size_t buf_size, size_t elem_size, size_t count, FILE *stream)
{
    struct qemu_fread_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREAD_S);
    call.buf = (ULONG_PTR)buf;
    call.buf_size = (ULONG_PTR)buf_size;
    call.elem_size = (ULONG_PTR)elem_size;
    call.count = (ULONG_PTR)count;
    call.stream = (ULONG_PTR)stream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fread_s(struct qemu_syscall *call)
{
    struct qemu_fread_s *c = (struct qemu_fread_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fread_s(QEMU_G2H(c->buf), c->buf_size, c->elem_size, c->count, FILE_g2h(c->stream));
}

#endif

struct qemu__fread_nolock_s
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t buf_size;
    uint64_t elem_size;
    uint64_t count;
    uint64_t stream;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__fread_nolock_s(void *buf, size_t buf_size, size_t elem_size, size_t count, FILE *stream)
{
    struct qemu__fread_nolock_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FREAD_NOLOCK_S);
    call.buf = (ULONG_PTR)buf;
    call.buf_size = (ULONG_PTR)buf_size;
    call.elem_size = (ULONG_PTR)elem_size;
    call.count = (ULONG_PTR)count;
    call.stream = (ULONG_PTR)stream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fread_nolock_s(struct qemu_syscall *call)
{
    struct qemu__fread_nolock_s *c = (struct qemu__fread_nolock_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__fread_nolock_s(QEMU_G2H(c->buf), c->buf_size, c->elem_size, c->count, FILE_g2h(c->stream));
}

#endif

struct qemu__wfreopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT__wfreopen(const WCHAR *path, const WCHAR *mode, FILE* file)
{
    struct qemu__wfreopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFREOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wfreopen(struct qemu_syscall *call)
{
    struct qemu__wfreopen *c = (struct qemu__wfreopen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wfreopen(QEMU_G2H(c->path), QEMU_G2H(c->mode), FILE_g2h(c->file)));
}

#endif

struct qemu__wfreopen_s
{
    struct qemu_syscall super;
    uint64_t pFile;
    uint64_t path;
    uint64_t mode;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wfreopen_s(FILE** pFile, const WCHAR *path, const WCHAR *mode, FILE* file)
{
    struct qemu__wfreopen_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WFREOPEN_S);
    call.pFile = (ULONG_PTR)pFile;
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wfreopen_s(struct qemu_syscall *call)
{
    struct qemu__wfreopen_s *c = (struct qemu__wfreopen_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wfreopen_s(QEMU_G2H(c->pFile), QEMU_G2H(c->path), QEMU_G2H(c->mode), FILE_g2h(c->file));
}

#endif

struct qemu_freopen
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t mode;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT_freopen(const char *path, const char *mode, FILE* file)
{
    struct qemu_freopen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREOPEN);
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_freopen(struct qemu_syscall *call)
{
    struct qemu_freopen *c = (struct qemu_freopen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_freopen(QEMU_G2H(c->path), QEMU_G2H(c->mode), FILE_g2h(c->file)));
}

#endif

struct qemu_freopen_s
{
    struct qemu_syscall super;
    uint64_t pFile;
    uint64_t path;
    uint64_t mode;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_freopen_s(FILE** pFile, const char *path, const char *mode, FILE* file)
{
    struct qemu_freopen_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREOPEN_S);
    call.pFile = (ULONG_PTR)pFile;
    call.path = (ULONG_PTR)path;
    call.mode = (ULONG_PTR)mode;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_freopen_s(struct qemu_syscall *call)
{
    struct qemu_freopen_s *c = (struct qemu_freopen_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_freopen_s(QEMU_G2H(c->pFile), QEMU_G2H(c->path), QEMU_G2H(c->mode), FILE_g2h(c->file));
}

#endif

struct qemu_fsetpos
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t pos;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fsetpos(FILE* file, fpos_t *pos)
{
    struct qemu_fsetpos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FSETPOS);
    call.file = (ULONG_PTR)file;
    call.pos = (ULONG_PTR)pos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fsetpos(struct qemu_syscall *call)
{
    struct qemu_fsetpos *c = (struct qemu_fsetpos *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fsetpos(FILE_g2h(c->file), QEMU_G2H(c->pos));
}

#endif

struct qemu__ftelli64
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL MSVCRT__ftelli64(FILE* file)
{
    struct qemu__ftelli64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTELLI64);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ftelli64(struct qemu_syscall *call)
{
    struct qemu__ftelli64 *c = (struct qemu__ftelli64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ftelli64(FILE_g2h(c->file));
}

#endif

struct qemu__ftelli64_nolock
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL MSVCRT__ftelli64_nolock(FILE* file)
{
    struct qemu__ftelli64_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTELLI64_NOLOCK);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ftelli64_nolock(struct qemu_syscall *call)
{
    struct qemu__ftelli64_nolock *c = (struct qemu__ftelli64_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ftelli64_nolock(FILE_g2h(c->file));
}

#endif

struct qemu_ftell
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT_ftell(FILE* file)
{
    struct qemu_ftell call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTELL);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ftell(struct qemu_syscall *call)
{
    struct qemu_ftell *c = (struct qemu_ftell *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ftell(FILE_g2h(c->file));
}

#endif

struct qemu__ftell_nolock
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT__ftell_nolock(FILE* file)
{
    struct qemu__ftell_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTELL_NOLOCK);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ftell_nolock(struct qemu_syscall *call)
{
    struct qemu__ftell_nolock *c = (struct qemu__ftell_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ftell_nolock(FILE_g2h(c->file));
}

#endif

struct qemu_fgetpos
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t pos;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fgetpos(FILE* file, fpos_t *pos)
{
    struct qemu_fgetpos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FGETPOS);
    call.file = (ULONG_PTR)file;
    call.pos = (ULONG_PTR)pos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fgetpos(struct qemu_syscall *call)
{
    struct qemu_fgetpos *c = (struct qemu_fgetpos *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fgetpos(FILE_g2h(c->file), QEMU_G2H(c->pos));
}

#endif

struct qemu_fputs
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fputs(const char *s, FILE* file)
{
    struct qemu_fputs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FPUTS);
    call.s = (ULONG_PTR)s;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fputs(struct qemu_syscall *call)
{
    struct qemu_fputs *c = (struct qemu_fputs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fputs(QEMU_G2H(c->s), FILE_g2h(c->file));
}

#endif

struct qemu_fputws
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_fputws(const WCHAR *s, FILE* file)
{
    struct qemu_fputws call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FPUTWS);
    call.s = (ULONG_PTR)s;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fputws(struct qemu_syscall *call)
{
    struct qemu_fputws *c = (struct qemu_fputws *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fputws(QEMU_G2H(c->s), FILE_g2h(c->file));
}

#endif

struct qemu_getchar
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_getchar(void)
{
    struct qemu_getchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCHAR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_getchar(struct qemu_syscall *call)
{
    struct qemu_getchar *c = (struct qemu_getchar *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getchar();
}

#endif

struct qemu_getc
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_getc(FILE* file)
{
    struct qemu_getc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETC);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_getc(struct qemu_syscall *call)
{
    struct qemu_getc *c = (struct qemu_getc *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_getc(FILE_g2h(c->file));
}

#endif

struct qemu_gets
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_gets(char *buf)
{
    struct qemu_gets call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETS);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_gets(struct qemu_syscall *call)
{
    struct qemu_gets *c = (struct qemu_gets *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_gets(QEMU_G2H(c->buf)));
}

#endif

struct qemu__getws
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WCHAR* CDECL MSVCRT__getws(WCHAR* buf)
{
    struct qemu__getws call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETWS);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__getws(struct qemu_syscall *call)
{
    struct qemu__getws *c = (struct qemu__getws *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__getws(QEMU_G2H(c->buf)));
}

#endif

struct qemu_putc
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_putc(int c, FILE* file)
{
    struct qemu_putc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PUTC);
    call.c = (ULONG_PTR)c;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_putc(struct qemu_syscall *call)
{
    struct qemu_putc *c = (struct qemu_putc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_putc(c->c, FILE_g2h(c->file));
}

#endif

struct qemu_putchar
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_putchar(int c)
{
    struct qemu_putchar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PUTCHAR);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_putchar(struct qemu_syscall *call)
{
    struct qemu_putchar *c = (struct qemu_putchar *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_putchar(c->c);
}

#endif

struct qemu__putws
{
    struct qemu_syscall super;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__putws(const WCHAR *s)
{
    struct qemu__putws call;
    call.super.id = QEMU_SYSCALL_ID(CALL__PUTWS);
    call.s = (ULONG_PTR)s;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__putws(struct qemu_syscall *call)
{
    struct qemu__putws *c = (struct qemu__putws *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__putws(QEMU_G2H(c->s));
}

#endif

struct qemu_remove
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_remove(const char *path)
{
    struct qemu_remove call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVE);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_remove(struct qemu_syscall *call)
{
    struct qemu_remove *c = (struct qemu_remove *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_remove(QEMU_G2H(c->path));
}

#endif

struct qemu__wremove
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wremove(const WCHAR *path)
{
    struct qemu__wremove call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WREMOVE);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wremove(struct qemu_syscall *call)
{
    struct qemu__wremove *c = (struct qemu__wremove *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wremove(QEMU_G2H(c->path));
}

#endif

struct qemu_rename
{
    struct qemu_syscall super;
    uint64_t oldpath;
    uint64_t newpath;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_rename(const char *oldpath,const char *newpath)
{
    struct qemu_rename call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RENAME);
    call.oldpath = (ULONG_PTR)oldpath;
    call.newpath = (ULONG_PTR)newpath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_rename(struct qemu_syscall *call)
{
    struct qemu_rename *c = (struct qemu_rename *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_rename(QEMU_G2H(c->oldpath), QEMU_G2H(c->newpath));
}

#endif

struct qemu__wrename
{
    struct qemu_syscall super;
    uint64_t oldpath;
    uint64_t newpath;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wrename(const WCHAR *oldpath,const WCHAR *newpath)
{
    struct qemu__wrename call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WRENAME);
    call.oldpath = (ULONG_PTR)oldpath;
    call.newpath = (ULONG_PTR)newpath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wrename(struct qemu_syscall *call)
{
    struct qemu__wrename *c = (struct qemu__wrename *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wrename(QEMU_G2H(c->oldpath), QEMU_G2H(c->newpath));
}

#endif

struct qemu_setbuf
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_setbuf(FILE* file, char *buf)
{
    struct qemu_setbuf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETBUF);
    call.file = (ULONG_PTR)file;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);
}

#else

void qemu_setbuf(struct qemu_syscall *call)
{
    struct qemu_setbuf *c = (struct qemu_setbuf *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_setbuf(FILE_g2h(c->file), QEMU_G2H(c->buf));
}

#endif

struct qemu_tmpnam_s
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_tmpnam_s(char *s, size_t size)
{
    struct qemu_tmpnam_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TMPNAM_S);
    call.s = (ULONG_PTR)s;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_tmpnam_s(struct qemu_syscall *call)
{
    struct qemu_tmpnam_s *c = (struct qemu_tmpnam_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_tmpnam_s(QEMU_G2H(c->s), c->size);
}

#endif

struct qemu_tmpnam
{
    struct qemu_syscall super;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_tmpnam(char *s)
{
    struct qemu_tmpnam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TMPNAM);
    call.s = (ULONG_PTR)s;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_tmpnam(struct qemu_syscall *call)
{
    struct qemu_tmpnam *c = (struct qemu_tmpnam *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_tmpnam(QEMU_G2H(c->s)));
}

#endif

struct qemu__wtmpnam_s
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wtmpnam_s(WCHAR *s, size_t size)
{
    struct qemu__wtmpnam_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTMPNAM_S);
    call.s = (ULONG_PTR)s;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtmpnam_s(struct qemu_syscall *call)
{
    struct qemu__wtmpnam_s *c = (struct qemu__wtmpnam_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtmpnam_s(QEMU_G2H(c->s), c->size);
}

#endif

struct qemu__wtmpnam
{
    struct qemu_syscall super;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT__wtmpnam(WCHAR *s)
{
    struct qemu__wtmpnam call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTMPNAM);
    call.s = (ULONG_PTR)s;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wtmpnam(struct qemu_syscall *call)
{
    struct qemu__wtmpnam *c = (struct qemu__wtmpnam *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wtmpnam(QEMU_G2H(c->s)));
}

#endif

struct qemu_tmpfile
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

FILE * CDECL MSVCRT_tmpfile(void)
{
    struct qemu_tmpfile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TMPFILE);

    qemu_syscall(&call.super);

    return (FILE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_tmpfile(struct qemu_syscall *call)
{
    struct qemu_tmpfile *c = (struct qemu_tmpfile *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_tmpfile());
}

#endif

struct qemu_tmpfile_s
{
    struct qemu_syscall super;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_tmpfile_s(FILE** file)
{
    struct qemu_tmpfile_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TMPFILE_S);
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_tmpfile_s(struct qemu_syscall *call)
{
    struct qemu_tmpfile_s *c = (struct qemu_tmpfile_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_tmpfile_s(QEMU_G2H(c->file));
}

#endif

struct qemu_ungetc
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_ungetc(int c, FILE * file)
{
    struct qemu_ungetc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNGETC);
    call.c = (ULONG_PTR)c;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ungetc(struct qemu_syscall *call)
{
    struct qemu_ungetc *c = (struct qemu_ungetc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ungetc(c->c, FILE_g2h(c->file));
}

#endif

struct qemu__ungetc_nolock
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ungetc_nolock(int c, FILE * file)
{
    struct qemu__ungetc_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNGETC_NOLOCK);
    call.c = (ULONG_PTR)c;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ungetc_nolock(struct qemu_syscall *call)
{
    struct qemu__ungetc_nolock *c = (struct qemu__ungetc_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ungetc_nolock(c->c, FILE_g2h(c->file));
}

#endif

struct qemu_ungetwc
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT_ungetwc(wint_t wc, FILE * file)
{
    struct qemu_ungetwc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNGETWC);
    call.wc = (ULONG_PTR)wc;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ungetwc(struct qemu_syscall *call)
{
    struct qemu_ungetwc *c = (struct qemu_ungetwc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ungetwc(c->wc, FILE_g2h(c->file));
}

#endif

struct qemu__ungetwc_nolock
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

wint_t CDECL MSVCRT__ungetwc_nolock(wint_t wc, FILE * file)
{
    struct qemu__ungetwc_nolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNGETWC_NOLOCK);
    call.wc = (ULONG_PTR)wc;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ungetwc_nolock(struct qemu_syscall *call)
{
    struct qemu__ungetwc_nolock *c = (struct qemu__ungetwc_nolock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ungetwc_nolock(c->wc, FILE_g2h(c->file));
}

#endif

struct qemu__getmaxstdio
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__getmaxstdio(void)
{
    struct qemu__getmaxstdio call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETMAXSTDIO);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getmaxstdio(struct qemu_syscall *call)
{
    struct qemu__getmaxstdio *c = (struct qemu__getmaxstdio *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getmaxstdio();
}

#endif

struct qemu__setmaxstdio
{
    struct qemu_syscall super;
    uint64_t newmax;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__setmaxstdio(int newmax)
{
    struct qemu__setmaxstdio call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SETMAXSTDIO);
    call.newmax = (ULONG_PTR)newmax;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__setmaxstdio(struct qemu_syscall *call)
{
    struct qemu__setmaxstdio *c = (struct qemu__setmaxstdio *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__setmaxstdio(c->newmax);
}

#endif

struct qemu__get_stream_buffer_pointers
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t base;
    uint64_t ptr;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__get_stream_buffer_pointers(FILE *file, char*** base, char*** ptr, int** count)
{
    struct qemu__get_stream_buffer_pointers call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_STREAM_BUFFER_POINTERS);
    call.file = (ULONG_PTR)file;
    call.base = (ULONG_PTR)base;
    call.ptr = (ULONG_PTR)ptr;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_stream_buffer_pointers(struct qemu_syscall *call)
{
    struct qemu__get_stream_buffer_pointers *c = (struct qemu__get_stream_buffer_pointers *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_stream_buffer_pointers(FILE_g2h(c->file), QEMU_G2H(c->base), QEMU_G2H(c->ptr), QEMU_G2H(c->count));
}

#endif

struct qemu__open
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t flags;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__open(const char *path, int flags, ...)
{
    struct qemu__open call;
    va_list list;

    call.super.id = QEMU_SYSCALL_ID(CALL__OPEN);
    call.path = (ULONG_PTR)path;
    call.flags = flags;
    if (flags & _O_CREAT)
    {
        va_start(list, flags);
        call.mode = va_arg(list, int);
        va_end(list);
    }

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

#define MSVCRT__O_CREAT       0x0100
void qemu__open(struct qemu_syscall *call)
{
    struct qemu__open *c = (struct qemu__open *)(ULONG_PTR)call;

    WINE_FIXME("Unverified!\n");
    if (c->flags & MSVCRT__O_CREAT)
    {
        c->super.iret = p__open(QEMU_G2H(c->path), c->flags, c->mode);
    }
    else
    {
        c->super.iret = p__open(QEMU_G2H(c->path), c->flags);
    }
}

#endif

struct qemu_realpath
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t resolved_path;
};

#ifdef QEMU_DLL_GUEST

char * CDECL __hangover_realpath(const char *path, char *resolved_path)
{
    struct qemu_realpath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALPATH);
    call.path = (ULONG_PTR)path;
    call.resolved_path = (ULONG_PTR)resolved_path;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_realpath(struct qemu_syscall *call)
{
    struct qemu_realpath *c = (struct qemu_realpath *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    /* This deliberately calls Unix libc. */
    c->super.iret = QEMU_H2G(realpath(QEMU_G2H(c->path), QEMU_G2H(c->resolved_path)));
}

#endif

struct qemu_getgrgid
{
    struct qemu_syscall super;
    uint64_t gid;
};

#ifdef QEMU_DLL_GUEST

/* Not quite right, but should be compatible. */
void * CDECL __hangover_getgrgid(int gid)
{
    struct qemu_getgrgid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGRGID);
    call.gid = (ULONG_PTR)gid;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

#include <pwd.h>
#include <grp.h>

void qemu_getgrgid(struct qemu_syscall *call)
{
    struct qemu_getgrgid *c = (struct qemu_getgrgid *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    /* This deliberately calls Unix libc. */
    c->super.iret = QEMU_H2G(getgrgid(c->gid));
}

#endif

struct qemu_getpwuid
{
    struct qemu_syscall super;
    uint64_t uid;
};

#ifdef QEMU_DLL_GUEST

/* Not quite right, but should be compatible. */
void * CDECL __hangover_getpwuid(int uid)
{
    struct qemu_getpwuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPWUID);
    call.uid = (ULONG_PTR)uid;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_getpwuid(struct qemu_syscall *call)
{
    struct qemu_getpwuid *c = (struct qemu_getpwuid *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    /* This deliberately calls Unix libc. */
    c->super.iret = QEMU_H2G(getpwuid(c->uid));
}

#endif
