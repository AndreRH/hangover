/*
 * Copyright 2000 Jon Griffiths
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
#include <stdlib.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu_onexit
{
    struct qemu_syscall super;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

/* This code is taken from Wine, without the traces. */
#define LOCK_EXIT   while(0) /*_mlock(_EXIT_LOCK1) */
#define UNLOCK_EXIT while(0) /*_munlock(_EXIT_LOCK1) */

static MSVCRT__onexit_t *MSVCRT_atexit_table = NULL;
static int MSVCRT_atexit_table_size = 0;
static int MSVCRT_atexit_registered = 0; /* Points to free slot */

typedef struct MSVCRT__onexit_table_t
{
    MSVCRT__onexit_t *_first;
    MSVCRT__onexit_t *_last;
    MSVCRT__onexit_t *_end;
} MSVCRT__onexit_table_t;

MSVCRT__onexit_t CDECL __dllonexit(MSVCRT__onexit_t func, MSVCRT__onexit_t **start, MSVCRT__onexit_t **end)
{
    MSVCRT__onexit_t *tmp;
    int len;

    if (!start || !*start || !end || !*end)
    {
        return NULL;
    }

    len = (*end - *start);

    if (++len <= 0)
        return NULL;

    tmp = MSVCRT_realloc(*start, len * sizeof(*tmp));
    if (!tmp)
        return NULL;
    *start = tmp;
    *end = tmp + len;
    tmp[len - 1] = func;
    return func;
}

static int guest_onexit_callback(void)
{
    /* Note: should only be called with the exit lock held */
    /* Last registered gets executed first */
    while (MSVCRT_atexit_registered > 0)
    {
        MSVCRT_atexit_registered--;
        if (MSVCRT_atexit_table[MSVCRT_atexit_registered])
            (*MSVCRT_atexit_table[MSVCRT_atexit_registered])();
    }

    return 0; /* ??* */
}

MSVCRT__onexit_t CDECL MSVCRT__onexit(MSVCRT__onexit_t func)
{
    struct qemu_onexit call;

    if (!func)
        return NULL;

    call.super.id = QEMU_SYSCALL_ID(CALL__ONEXIT);
    call.func = (ULONG_PTR)guest_onexit_callback;

    qemu_syscall(&call.super);

    LOCK_EXIT;
    if (MSVCRT_atexit_registered > MSVCRT_atexit_table_size - 1)
    {
        MSVCRT__onexit_t *newtable;
        newtable = MSVCRT_calloc((MSVCRT_atexit_table_size + 32), sizeof(void *));
        if (!newtable)
        {
            UNLOCK_EXIT;
            return NULL;
        }
        MSVCRT_memcpy (newtable, MSVCRT_atexit_table, MSVCRT_atexit_table_size*sizeof(void *));
        MSVCRT_atexit_table_size += 32;
        MSVCRT_free (MSVCRT_atexit_table);
        MSVCRT_atexit_table = newtable;
    }
    MSVCRT_atexit_table[MSVCRT_atexit_registered] = func;
    MSVCRT_atexit_registered++;
    UNLOCK_EXIT;
    return func;
}

int CDECL MSVCRT_atexit(void (__cdecl *func)(void))
{
    return MSVCRT__onexit((MSVCRT__onexit_t)func) == (MSVCRT__onexit_t)func ? 0 : -1;
}

#else

static void *guest_onexit_callback = 0;

static int CDECL onexit_callback(void)
{
    return qemu_ops->qemu_execute(guest_onexit_callback, 0);
}

void qemu__onexit(struct qemu_syscall *call)
{
    struct qemu_onexit *c = (struct qemu_onexit *)(ULONG_PTR)call;
    WINE_TRACE("\n");

    if (!guest_onexit_callback)
    {
        p__onexit(onexit_callback);
        guest_onexit_callback = QEMU_G2H(c->func);
    }
}


#endif

struct qemu__amsg_exit
{
    struct qemu_syscall super;
    uint64_t errnum;
};

#ifdef QEMU_DLL_GUEST

CDECL void _amsg_exit(int errnum)
{
    struct qemu__amsg_exit call;
    call.super.id = QEMU_SYSCALL_ID(CALL__AMSG_EXIT);
    call.errnum = errnum;

    qemu_syscall(&call.super);
}

#else

void qemu__amsg_exit(struct qemu_syscall *call)
{
    struct qemu__amsg_exit *c = (struct qemu__amsg_exit *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p__amsg_exit(c->errnum);
}

#endif

#ifdef QEMU_DLL_GUEST

void CDECL DECLSPEC_NORETURN MSVCRT_abort(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_ABORT);

    qemu_syscall(&call);

    /* The syscall does not exit, but gcc does not know that. */
    while(1);
}

#else

void qemu_abort(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    p_abort();
}

#endif

struct qemu_exit
{
    struct qemu_syscall super;
    uint64_t code;
};

#ifdef QEMU_DLL_GUEST

CDECL DECLSPEC_NORETURN void __MINGW_NOTHROW MSVCRT__exit(int code)
{
    struct qemu_exit call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EXIT);
    call.code = code;

    qemu_syscall(&call.super);

    /* The syscall does not exit, but gcc does not know that. */
    while(1);
}

CDECL DECLSPEC_NORETURN void __MINGW_NOTHROW MSVCRT_exit(int code)
{
    struct qemu_exit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXIT);
    call.code = code;

    qemu_syscall(&call.super);

    /* The syscall does not exit, but gcc does not know that. */
    while(1);
}

#else

void qemu__exit(struct qemu_syscall *call)
{
    struct qemu_exit *c = (struct qemu_exit *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p__exit(c->code);
}

void qemu_exit(struct qemu_syscall *call)
{
    struct qemu_exit *c = (struct qemu_exit *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p_exit(c->code);
}

#endif

#ifdef QEMU_DLL_GUEST

CDECL void MSVCRT__cexit(int garbble)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__CEXIT);

    qemu_syscall(&call);
}

#else

void qemu__cexit(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    p__cexit();
}

#endif

#ifdef QEMU_DLL_GUEST

CDECL void _purecall(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__PURECALL);

    qemu_syscall(&call);
}

#else

void qemu__purecall(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    p__purecall();
}

#endif

struct qemu__assert
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t file;
    uint64_t line;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__assert(const char* str, const char* file, unsigned int line)
{
    struct qemu__assert call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ASSERT);
    call.str = (ULONG_PTR)str;
    call.file = (ULONG_PTR)file;
    call.line = line;

    qemu_syscall(&call.super);
}

#else

void qemu__assert(struct qemu_syscall *call)
{
    struct qemu__assert *c = (struct qemu__assert *)call;
    WINE_FIXME("Unverified!\n");
    p__assert(QEMU_G2H(c->str), QEMU_G2H(c->file), c->line);
}

#endif
