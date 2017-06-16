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
    c->iret = QEMU_H2G(p___iob_func());
}

#endif

struct qemu_fprintf
{
    struct qemu_syscall super;
    uint64_t argcount, argcount_float;
    uint64_t file;
    uint64_t format;
    uint64_t MSVCRT_FILE_size;
    struct _args
    {
        uint64_t is_float;
        uint64_t arg;
    } args[1];
};

#ifdef QEMU_DLL_GUEST

static unsigned int count_printf_argsA(const char *format, char *fmts)
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

#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl " #name suffix "\n\t.type " #name suffix ",@function\n" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc\n\t.previous");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)
extern int CDECL call_fprintf( FILE *file, const char *format, void *func, int nb_args, int nb_onstack, const void *args );
__ASM_GLOBAL_FUNC( call_fprintf,
                   "stp x29, x30, [SP,#-16]!\n\t"           /* push FP & LR */
                   "stp x19, x20, [SP,#-16]!\n\t"           /* push some regs we'll use */
                   "add x9, x5, x3, lsl #4\n\t"             /* end=args+nb_args*sizeof(args[0]) */
                   "mov x10, x2\n\t"                        /* remember func */
                   "mov x11, x5\n\t"                        /* remember args */
                   "mov x12, #0\n\t"                        /* init arg counter */
                   "mov x13, #0\n\t"                        /* init float arg counter */
                   "mov x19, #0\n\t"                        /* init align */
                   "mov x20, #0\n\t"                        /* init stack arg counter */
                   "cbz x4, 1f\n\t"                         /* if nb_onstack == 0 goto 1 */
                   "lsl x4, x4, #3\n\t"                     /* nb_onstack *= 8 */
                   "add x4, x4, #0x16\n\t"                  /* align helper */
                   "and x4, x4, #0xfffffffffffffff0\n\t"    /* align */
                   "sub SP, SP, x4\n\t"                     /* allocate space on stack for later */
                   "mov x19, x4\n\t"                        /* remember align */
                   "1: cbz x3, 11f\n\t"                     /* if nb_args == 0 goto 4 */
                   /* init  done */
                   "2: ldr x14, [x11]\n\t"                  /* is_float */
                   "cbz x14, 6f\n\t"                        /* if !is_float goto 97 */
                   "cmp x13, #8\n\t"                        /* if floats exceed 8, */
                   "b.eq 5f\n\t"                            /* they need to continue on the stack */
                   /* floats -> regs */
                   "adr x14, 3f\n\t"                        /* different reg per arg nubmer */
                   "add x14, x14, x13, lsl #3\n\t"          /* some kind of switch statement */
                   "br x14\n\t"
                   "3: ldr d0, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d1, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d2, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d3, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d4, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d5, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d6, [x11,#8]\n\t"
                   "b 4f\n\t"
                   "ldr d7, [x11,#8]\n\t"
                   "4: add x13, x13, #1\n\t"                /* increment the float arg counter */
                   "b 10f\n\t"                              /* next */
                   /* floats -> stack */
                   "5: add x17, sp, x20, lsl #3\n\t"        /* pos = 8 * stack arg count + SP */
                   "ldr x16, [x11,#8]\n\t"                  /* load the value */
                   "str x16, [x17]\n\t"                     /* store it at the calculated position */
                   "add x20, x20, #1\n\t"                   /* increment the stack arg counter */
                   "b 10f\n\t"                              /* next */
                   "6: cmp x12, #6\n\t"                     /* if args exceed file+fmt+6, */
                   "b.eq 9f\n\t"                            /* they need to continue on the stack */
                   /* ints -> reg */
                   "adr x14, 7f\n\t"                        /* different reg per arg nubmer */
                   "add x14, x14, x12, lsl #3\n\t"          /* some kind of switch statement */
                   "br x14\n\t"
                   "7: ldr x2, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x3, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x4, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x5, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x6, [x11,#8]\n\t"
                   "b 8f\n\t"
                   "ldr x7, [x11,#8]\n\t"
                   "8: add x12, x12, #1\n\t"                /* increment the arg counter */
                   "b 10f\n\t"                              /* next */
                   /* ints -> stack */
                   "9: add x17, sp, x20, lsl #3\n\t"        /* pos = 8 * stack arg count + SP */
                   "ldr x16, [x11,#8]\n\t"                  /* load the value */
                   "str x16, [x17]\n\t"                     /* store it at the calculated position */
                   "add x20, x20, #1\n\t"                   /* increment the stack arg counter */
                   "10: add x11, x11, #0x10\n\t"            /* next in args */
                   "cmp	x11, x9\n\t"                        /* end? */
                   "b.ne 2b\n\t"                            /* if not, loop */
                   "11: blr x10\n\t"                        /* call func */
                   "add SP, SP, x19\n\t"                    /* restore stack */
                   "ldp x19, x20, [SP], #16\n\t"            /* pop local regs */
                   "ldp x29, x30, [SP], #16\n\t"            /* pop FP & LR */
                   "ret\n\t" )

void qemu_fprintf(struct qemu_syscall *call)
{
    struct qemu_fprintf *c = (struct qemu_fprintf *)call;
    int ret, onstack = 0;
    void *file, *func;

    if (c->argcount - c->argcount_float > 6)
        onstack = c->argcount - c->argcount_float - 6;
    if (c->argcount_float > 8)
        onstack += c->argcount_float - 8;

    WINE_TRACE("(%lu floats/%lu args, onstack %i, format \"%s\"\n", c->argcount_float, c->argcount, onstack, (char *)QEMU_G2H(c->format));

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_PRINTF):
            /* Don't put "stdout" here, it will call the Linux libc __iob_func export.
             * Plus, the size of FILE is different between Linux and Windows, and I
             * haven't found a nice way to get MSVCRT_FILE from Wine, other than
             * copypasting it, so grab the proper offset from the VM. */
            file = (BYTE *)p___iob_func() + c->MSVCRT_FILE_size;
            func = p_fprintf;
            break;

        case QEMU_SYSCALL_ID(CALL_FPRINTF):
            file = QEMU_G2H(c->file);
            func = p_fprintf;
            break;

        case QEMU_SYSCALL_ID(CALL_WPRINTF):
            file = (BYTE *)p___iob_func() + c->MSVCRT_FILE_size;
            func = p_fwprintf;
            break;

        case QEMU_SYSCALL_ID(CALL_FWPRINTF):
            file = QEMU_G2H(c->file);
            func = p_fwprintf;
            break;

        default:
            WINE_ERR("Unexpected op %lx\n", c->super.id);
    }

    ret = call_fprintf(file, QEMU_G2H(c->format), func, c->argcount, onstack, c->args);

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
