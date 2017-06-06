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
#include "ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <winternl.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_RtlAddFunctionTable
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t entry_count;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

NTSYSAPI BOOLEAN CDECL RtlAddFunctionTable(PRUNTIME_FUNCTION func, DWORD entry_count, DWORD64 base)
{
    struct qemu_RtlAddFunctionTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDFUNCTIONTABLE);
    call.func = (uint64_t)func;
    call.entry_count = entry_count;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddFunctionTable(struct qemu_syscall *call)
{
    struct qemu_RtlAddFunctionTable *c = (struct qemu_RtlAddFunctionTable *)call;
    WINE_FIXME("(%p, %lu, %#lx) Stub!\n", QEMU_G2H(c->func), c->entry_count, c->base);
    c->super.iret = FALSE;
}

#endif
