/*
 * Copyright 2017 Stefan Dösinger
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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

typedef void LDR_MODULE;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_LdrFindEntryForAddress
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t mod;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_LdrFindEntryForAddress(const void *addr, LDR_MODULE **mod)
{
    /* FIXME: With proper data in the PEB we should be able to do this on the
     * client side.
     *
     * FIXME 2: HMODULE != LDR_MODULE, but for now it is good enough for our little
     * PE loader. */
    struct qemu_LdrFindEntryForAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRFINDENTRYFORADDRESS);
    call.addr = (uint64_t)addr;
    call.mod = (uint64_t)mod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrFindEntryForAddress(struct qemu_syscall *call)
{
    struct qemu_LdrFindEntryForAddress *c = (struct qemu_LdrFindEntryForAddress *)call;
    HMODULE mod;
    WINE_TRACE("\n");

    if (qemu_ops->qemu_FindEntryForAddress(QEMU_G2H(c->addr), &mod))
        c->super.iret = STATUS_SUCCESS;
    else
        c->super.iret = STATUS_NO_MORE_ENTRIES;

    *(uint64_t *)QEMU_G2H(c->mod) = (uint64_t)mod;
}

#endif
