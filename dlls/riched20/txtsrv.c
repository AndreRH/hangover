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
#include <richedit.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_riched20.h"

#ifndef QEMU_DLL_GUEST

#include <wine/debug.h>

/* Mingw's textserv.h is a C++ header. */
#include <textserv.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_riched20);
#endif

struct qemu_CreateTextServices
{
    struct qemu_syscall super;
    uint64_t pUnkOuter;
    uint64_t pITextHost;
    uint64_t ppUnk;
};

#ifdef QEMU_DLL_GUEST

HRESULT WINAPI CreateTextServices(IUnknown *pUnkOuter, void *pITextHost, IUnknown **ppUnk)
{
    struct qemu_CreateTextServices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETEXTSERVICES);
    call.pUnkOuter = (uint64_t)pUnkOuter;
    call.pITextHost = (uint64_t)pITextHost;
    call.ppUnk = (uint64_t)ppUnk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateTextServices(struct qemu_syscall *call)
{
    struct qemu_CreateTextServices *c = (struct qemu_CreateTextServices *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = E_FAIL;
}

#endif

