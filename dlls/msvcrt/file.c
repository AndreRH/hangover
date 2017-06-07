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
    c->iret = (uint64_t)p___iob_func();
}

#endif

struct qemu_fprintf
{
    struct qemu_syscall super;
    uint64_t argcount, warn_float;
    uint64_t file;
    uint64_t format;
    uint64_t args[1];
};

#ifdef QEMU_DLL_GUEST

static unsigned int count_printf_args(const char *format, char *fmts)
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

int CDECL MSVCRT_fprintf(FILE *file, const char *format, ...)
{
    struct qemu_fprintf *call;
    int ret;
    char fmts[256] = {0};
    unsigned int count = count_printf_args(format, fmts), i, arg = 0;
    va_list list;
    union
    {
        double d;
        uint64_t i;
    } conv;

    call = MSVCRT_malloc(sizeof(*call) + (count - 1) * sizeof(call->args));
    call->super.id = QEMU_SYSCALL_ID(CALL_FPRINTF);
    call->argcount = count;
    call->file = (uint64_t)file;
    call->format = (uint64_t)format;
    call->warn_float = FALSE;

    va_start(list, format);
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
                conv.d = va_arg(list, double);
                call->args[i] = conv.i;
                call->warn_float = TRUE;
                break;

            default:
                call->args[i] = va_arg(list, uint64_t);
                break;
        }
    }
    va_end(list);

    qemu_syscall(&call->super);
    ret = call->super.iret;

    MSVCRT_free(call);

    return ret;
}

#else

void qemu_fprintf(struct qemu_syscall *call)
{
    struct qemu_fprintf *c = (struct qemu_fprintf *)call;
    int ret;
    WINE_TRACE("(%lu args, format \"%s\"\n", c->argcount, (char *)QEMU_G2H(c->format));
    union
    {
        double d;
        uint64_t i;
    } conv;

    /* This is obviously not nice. I haven't found a way in C to push varargs into
     * registers / the stack or construct a va_list. It probably needs arch-specific
     * assembler code.
     *
     * This also doesn't pass doubles correctly. The double arrives correctly in
     * the call structure but apparently needs to be re-interpreted as a float before
     * being passed to fprintf, similarly to what the guest side does. */
    switch (c->argcount)
    {
        case 0:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format));
            break;
        case 1:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0]);
            break;
        case 2:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0], c->args[1]);
            break;
        case 3:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0], c->args[1], c->args[2]);
            break;
        case 4:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0], c->args[1], c->args[2],
                    c->args[3]);
            break;
        case 5:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0], c->args[1], c->args[2],
                    c->args[3], c->args[4]);
            break;
        case 6:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0], c->args[1], c->args[2],
                    c->args[3], c->args[4], c->args[5]);
            break;
        case 7:
            ret = p_fprintf(QEMU_G2H(c->file), QEMU_G2H(c->format), c->args[0], c->args[1], c->args[2],
                    c->args[3], c->args[4], c->args[5], c->args[6]);
            break;
        default:
            WINE_FIXME("Write assembler code to push fprintf args onto the stack.\n");
    }
    if (c->warn_float)
        WINE_FIXME("Floating point numbers not handled yet.\n");

    c->super.iret = ret;
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
    call.size = (uint64_t)size;
    call.count = (uint64_t)count;
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
