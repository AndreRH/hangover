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

#ifdef QEMU_DLL_GUEST

/* FIXME: Passing the IOB and FILE pointers like this only works when they have the same size
 * in guest and host. */
FILE * CDECL MSVCRT___iob_func(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___IOB_FUNC);

    qemu_syscall(&call);

    return (FILE *)call.iret;
}

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
    call.f = (uint64_t)f;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__fileno(struct qemu_syscall *call)
{
    struct qemu__fileno *c = (struct qemu__fileno *)call;
    WINE_TRACE("\n");
    c->super.iret = p__fileno(QEMU_G2H(c->f));
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
    struct qemu__isatty *c = (struct qemu__isatty *)call;
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
    struct qemu__lseek *c = (struct qemu__lseek *)call;
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
    struct qemu__lseeki64 *c = (struct qemu__lseeki64 *)call;
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
    call.dir = (uint64_t)dir;
    call.prefix = (uint64_t)prefix;

    qemu_syscall(&call.super);

    return (char *)call.super.iret;
}

#else

void qemu__tempnam(struct qemu_syscall *call)
{
    struct qemu__tempnam *c = (struct qemu__tempnam *)call;
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
    call.file = (uint64_t)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fflush(struct qemu_syscall *call)
{
    struct qemu_fflush *c = (struct qemu_fflush *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_fflush(QEMU_G2H(c->file));
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
    call.buf = (uint64_t)buf;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__write(struct qemu_syscall *call)
{
    struct qemu__write *c = (struct qemu__write *)call;
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
    uint64_t MSVCRT_FILE_size;
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
    call->file = (uint64_t)file;
    call->format = (uint64_t)format;
    call->MSVCRT_FILE_size = sizeof(FILE);
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
                call->args[i].arg = va_arg(args, uint64_t);
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
    vfprintf_helper(QEMU_SYSCALL_ID(CALL_FPRINTF), file, format, args);
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

static unsigned int count_printf_argsW(const WCHAR *format, WCHAR *fmts)
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
            case 'u':
            case 'X':
            case 'x':
                fmts[count++] = format[i];
                if (count == 256)
                    MSVCRT_exit(255);
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
    call->file = (uint64_t)file;
    call->format = (uint64_t)format;
    call->MSVCRT_FILE_size = sizeof(FILE);
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
                call->args[i].arg = va_arg(args, uint64_t);
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
    vfwprintf_helper(QEMU_SYSCALL_ID(CALL_FWPRINTF), file, format, args);
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

static uint64_t printf_wrapper(void *ctx, ...)
{
    va_list list;
    const struct printf_data *data = ctx;
    int ret;

    va_start(list, ctx);
    if (data->unicode)
        ret = p_vfwprintf(data->file, data->fmt, list);
    else
        ret = p_vfprintf(data->file, data->fmt, list);
    va_end(list);

    return ret;
}

void qemu_fprintf(struct qemu_syscall *call)
{
    struct qemu_fprintf *c = (struct qemu_fprintf *)call;
    int ret;
    void *file;
    struct printf_data data;

    WINE_TRACE("(%lu floats/%lu args, format \"%s\"\n", c->argcount_float, c->argcount, (char *)QEMU_G2H(c->format));

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_PRINTF):
            /* Don't put "stdout" here, it will call the Linux libc __iob_func export.
             * Plus, the size of FILE is different between Linux and Windows, and I
             * haven't found a nice way to get MSVCRT_FILE from Wine, other than
             * copypasting it, so grab the proper offset from the VM. */
            data.file = (BYTE *)p___iob_func() + c->MSVCRT_FILE_size;
            data.unicode = FALSE;
            break;

        case QEMU_SYSCALL_ID(CALL_FPRINTF):
            data.file = QEMU_G2H(c->file);
            data.unicode = FALSE;
            break;

        case QEMU_SYSCALL_ID(CALL_WPRINTF):
            data.file = (BYTE *)p___iob_func() + c->MSVCRT_FILE_size;
            data.unicode = TRUE;
            break;

        case QEMU_SYSCALL_ID(CALL_FWPRINTF):
            data.file = QEMU_G2H(c->file);
            data.unicode = TRUE;
            break;

        default:
            WINE_ERR("Unexpected op %lx\n", c->super.id);
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
    uint64_t charcount;
    uint64_t format;
    struct va_array args[1];
};

#ifdef QEMU_DLL_GUEST

static int CDECL vsprintf_helper(uint64_t op, char *str, size_t charcount, const char *format, va_list args)
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
    call->argcount = count;
    call->charcount = charcount;
    call->str = (uint64_t)str;
    call->format = (uint64_t)format;
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
                call->args[i].arg = va_arg(args, uint64_t);
                break;
        }
    }

    qemu_syscall(&call->super);
    ret = call->super.iret;

    MSVCRT_free(call);

    return ret;
}

static int CDECL vswprintf_helper(uint64_t op, WCHAR *str, size_t charcount, const WCHAR *format, va_list args)
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
    call->str = (uint64_t)str;
    call->charcount = charcount;
    call->format = (uint64_t)format;
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
                call->args[i].arg = va_arg(args, uint64_t);
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
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL_SPRINTF), str, 0, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT__snprintf(char *str, size_t len, const char *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF), str, len, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT__vsnprintf(char *str, size_t len, const char *format, va_list valist)
{
    return vsprintf_helper(QEMU_SYSCALL_ID(CALL__VSNPRINTF), str, len, format, valist);
}

int CDECL MSVCRT_vswprintf_s(WCHAR *str, size_t count, const WCHAR *format, va_list list)
{
    return vswprintf_helper(QEMU_SYSCALL_ID(CALL_SWPRINTF_S), str, count, format, list);
}

int CDECL MSVCRT_swprintf_s(WCHAR *str, size_t count,
        const WCHAR *format, ...)
{
    int ret;
    va_list list;

    va_start(list, format);
    ret = vswprintf_helper(QEMU_SYSCALL_ID(CALL_SWPRINTF_S), str, count, format, list);
    va_end(list);

    return ret;
}

int CDECL MSVCRT__vsnwprintf(WCHAR *str, size_t len, const WCHAR *format, va_list valist)
{
    return vswprintf_helper(QEMU_SYSCALL_ID(CALL__VSNWPRINTF), str, len, format, valist);
}

#else

struct sprintf_data
{
    uint64_t op;
    size_t charcount;
    void *dst;
    void *fmt;
};

static uint64_t sprintf_wrapper(void *ctx, ...)
{
    va_list list;
    const struct sprintf_data *data = ctx;
    int ret;

    va_start(list, ctx);
    switch (data->op)
    {
        case QEMU_SYSCALL_ID(CALL_SPRINTF):
            ret = p_vsprintf(data->dst, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL__VSNPRINTF):
            ret = p__vsnprintf(data->dst, data->charcount, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL_SWPRINTF_S):
            ret = p_vswprintf_s(data->dst, data->charcount, data->fmt, list);
            break;

        case QEMU_SYSCALL_ID(CALL__VSNWPRINTF):
            ret = p__vsnwprintf(data->dst, data->charcount, data->fmt, list);
            break;
    }
    va_end(list);

    return ret;
}

void qemu_sprintf(struct qemu_syscall *call)
{
    struct qemu_sprintf *c = (struct qemu_sprintf *)call;
    struct sprintf_data data;
    int ret;

    WINE_TRACE("(%lu floats/%lu args, format \"%s\"\n", c->argcount_float, c->argcount, (char *)QEMU_G2H(c->format));

    data.op = c->super.id;
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
    call.str = (uint64_t)str;
    call.size = size;
    call.count = count;
    call.file = (uint64_t)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fread(struct qemu_syscall *call)
{
    struct qemu_fread *c = (struct qemu_fread *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_fread(QEMU_G2H(c->str), c->size, c->count, QEMU_G2H(c->file));
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
    call.str = (uint64_t)str;
    call.size = size;
    call.count = count;
    call.file = (uint64_t)file;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_fwrite(struct qemu_syscall *call)
{
    struct qemu_fwrite *c = (struct qemu_fwrite *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_fwrite(QEMU_G2H(c->str), c->size, c->count, QEMU_G2H(c->file));
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
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_puts(struct qemu_syscall *call)
{
    struct qemu_puts *c = (struct qemu_puts *)call;
    WINE_TRACE("\n");
    c->super.iret = p_puts(QEMU_G2H(c->str));
}

#endif
