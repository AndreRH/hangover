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
