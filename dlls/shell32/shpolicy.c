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
#include <shlwapi.h>
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_SHRestricted
{
    struct qemu_syscall super;
    uint64_t policy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHRestricted (RESTRICTIONS policy)
{
    struct qemu_SHRestricted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHRESTRICTED);
    call.policy = policy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHRestricted(struct qemu_syscall *call)
{
    struct qemu_SHRestricted *c = (struct qemu_SHRestricted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRestricted(c->policy);
}

#endif

struct qemu_SHInitRestricted
{
    struct qemu_syscall super;
    uint64_t unused;
    uint64_t inpRegKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHInitRestricted(LPCVOID unused, LPCVOID inpRegKey)
{
    struct qemu_SHInitRestricted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHINITRESTRICTED);
    call.unused = (ULONG_PTR)unused;
    call.inpRegKey = (ULONG_PTR)inpRegKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHInitRestricted to Wine headers? */
extern BOOL WINAPI SHInitRestricted(LPCVOID unused, LPCVOID inpRegKey);
void qemu_SHInitRestricted(struct qemu_syscall *call)
{
    struct qemu_SHInitRestricted *c = (struct qemu_SHInitRestricted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHInitRestricted(QEMU_G2H(c->unused), QEMU_G2H(c->inpRegKey));
}

#endif

