/*
 * Copyright 2017 André Hentschel
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
#include <winternl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_RtlEncodePointer
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI RtlEncodePointer(void *ptr)
{
    struct qemu_RtlEncodePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLENCODEPOINTER);
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_RtlEncodePointer(struct qemu_syscall *call)
{
    struct qemu_RtlEncodePointer *c = (struct qemu_RtlEncodePointer *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)RtlEncodePointer((void *)c->ptr);
}

#endif

struct qemu_RtlDecodePointer
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI RtlDecodePointer(void *ptr)
{
    struct qemu_RtlDecodePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDECODEPOINTER);
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_RtlDecodePointer(struct qemu_syscall *call)
{
    struct qemu_RtlDecodePointer *c = (struct qemu_RtlDecodePointer *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)RtlDecodePointer((void *)c->ptr);
}

#endif
