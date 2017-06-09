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

/* FIXME: Calling out of the vm for memset is probably a waste of time. */
struct qemu_memset
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t c;
    uint64_t size;
};


#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memset(void *ptr,int c,size_t size)
{
    struct qemu_memset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMSET);
    call.ptr = (uint64_t)ptr;
    call.c = c;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_memset(struct qemu_syscall *call)
{
    struct qemu_memset *c = (struct qemu_memset *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_memset(QEMU_G2H(c->ptr), c->c, c->size);
}

#endif

/* FIXME: Calling out of the vm for memcpy is probably a waste of time. */
struct qemu_memcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t size;
};


#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size)
{
    struct qemu_memcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCPY);
    call.dst = (uint64_t)dst;
    call.src = (uint64_t)src;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_memcpy(struct qemu_syscall *call)
{
    struct qemu_memcpy *c = (struct qemu_memcpy *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_memcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->size);
}

#endif

/* FIXME: Calling out of the vm for strlen is probably a waste of time. */
struct qemu_strlen
{
    struct qemu_syscall super;
    uint64_t str;
};


#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_strlen(const char *str)
{
    struct qemu_strlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRLEN);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strlen(struct qemu_syscall *call)
{
    struct qemu_strlen *c = (struct qemu_strlen *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strlen(QEMU_G2H(c->str));
}

#endif

/* FIXME: Calling out of the vm for strncmp is probably a waste of time. */
struct qemu_strncmp
{
    struct qemu_syscall super;
    uint64_t str1, str2;
    uint64_t len;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strncmp(const char *str1, const char *str2, size_t len)
{
    struct qemu_strncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCMP);
    call.str1 = (uint64_t)str1;
    call.str2 = (uint64_t)str2;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strncmp(struct qemu_syscall *call)
{
    struct qemu_strncmp *c = (struct qemu_strncmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strncmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len);
}

#endif
