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

struct qemu_calloc
{
    struct qemu_syscall super;
    uint64_t item_count, size;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_calloc(size_t item_count,size_t size)
{
    struct qemu_calloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLOC);
    call.item_count = item_count;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_calloc(struct qemu_syscall *call)
{
    struct qemu_calloc *c = (struct qemu_calloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_calloc(c->item_count, c->size));
}

#endif

struct qemu_free
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_free(void *ptr)
{
    struct qemu_free call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREE);
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);
}

#else

void qemu_free(struct qemu_syscall *call)
{
    struct qemu_free *c = (struct qemu_free *)call;
    WINE_TRACE("\n");
    p_free(QEMU_G2H(c->ptr));
}

#endif

struct qemu_malloc
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_malloc(size_t size)
{
    struct qemu_malloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MALLOC);
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_malloc(struct qemu_syscall *call)
{
    struct qemu_malloc *c = (struct qemu_malloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_malloc(c->size));
}

#endif

struct qemu_realloc
{
    struct qemu_syscall super;
    uint64_t ptr, size;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_realloc(void *ptr, size_t size)
{
    struct qemu_realloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALLOC);
    call.ptr = (uint64_t)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_realloc(struct qemu_syscall *call)
{
    struct qemu_realloc *c = (struct qemu_realloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_realloc(QEMU_G2H(c->ptr), c->size));
}

#endif
