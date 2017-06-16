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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetProcessHeap()
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETPROCESSHEAP);

    qemu_syscall(&call);

    return (HANDLE)call.iret;
}

#else

void qemu_GetProcessHeap(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    c->iret = (uint64_t)GetProcessHeap();
}

#endif

struct qemu_HeapAlloc
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI HeapAlloc(HANDLE heap, DWORD flags, size_t size)
{
    struct qemu_HeapAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPALLOC);
    call.heap = (uint64_t)heap;
    call.flags = flags;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_HeapAlloc(struct qemu_syscall *call)
{
    struct qemu_HeapAlloc *c = (struct qemu_HeapAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(HeapAlloc((HANDLE)c->heap, c->flags, c->size));
}

#endif

struct qemu_HeapFree
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t mem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI HeapFree(HANDLE heap, DWORD flags, void *mem)
{
    struct qemu_HeapFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPFREE);
    call.heap = (uint64_t)heap;
    call.flags = flags;
    call.mem = (uint64_t)mem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapFree(struct qemu_syscall *call)
{
    struct qemu_HeapFree *c = (struct qemu_HeapFree *)call;
    WINE_TRACE("\n");
    c->super.iret = HeapFree((HANDLE)c->heap, c->flags, QEMU_G2H(c->mem));
}

#endif

struct qemu_LocalFree
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HLOCAL WINAPI LocalFree(HLOCAL ptr)
{
    struct qemu_LocalFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALFREE);
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);

    return (HLOCAL)call.super.iret;
}

#else

void qemu_LocalFree(struct qemu_syscall *call)
{
    struct qemu_LocalFree *c = (struct qemu_LocalFree *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(LocalFree(QEMU_G2H(c->ptr)));
}

#endif
