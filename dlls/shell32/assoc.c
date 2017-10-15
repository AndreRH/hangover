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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_SHAssocEnumHandlers
{
    struct qemu_syscall super;
    uint64_t extra;
    uint64_t filter;
    uint64_t enumhandlers;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHAssocEnumHandlers(const WCHAR *extra, ASSOC_FILTER filter, IEnumAssocHandlers **enumhandlers)
{
    struct qemu_SHAssocEnumHandlers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHASSOCENUMHANDLERS);
    call.extra = (ULONG_PTR)extra;
    call.filter = filter;
    call.enumhandlers = (ULONG_PTR)enumhandlers;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHAssocEnumHandlers(struct qemu_syscall *call)
{
    struct qemu_SHAssocEnumHandlers *c = (struct qemu_SHAssocEnumHandlers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAssocEnumHandlers(QEMU_G2H(c->extra), c->filter, QEMU_G2H(c->enumhandlers));
}

#endif

