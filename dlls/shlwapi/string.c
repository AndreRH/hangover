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

#include "windows-user-services.h"
#include "dll_list.h"
#include "shlwapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi);
#endif

struct qemu_StrCmpNIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrCmpNIW(LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen)
{
    struct qemu_StrCmpNIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCmpNIW(struct qemu_syscall *call)
{
    struct qemu_StrCmpNIW *c = (struct qemu_StrCmpNIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpNIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif
