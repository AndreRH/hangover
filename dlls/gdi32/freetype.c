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
#include <usp10.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_GetRasterizerCaps
{
    struct qemu_syscall super;
    uint64_t lprs;
    uint64_t cbNumBytes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetRasterizerCaps(LPRASTERIZER_STATUS lprs, UINT cbNumBytes)
{
    struct qemu_GetRasterizerCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRASTERIZERCAPS);
    call.lprs = (ULONG_PTR)lprs;
    call.cbNumBytes = (ULONG_PTR)cbNumBytes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRasterizerCaps(struct qemu_syscall *call)
{
    struct qemu_GetRasterizerCaps *c = (struct qemu_GetRasterizerCaps *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetRasterizerCaps(QEMU_G2H(c->lprs), c->cbNumBytes);
}

#endif

struct qemu_GetFontFileInfo
{
    struct qemu_syscall super;
    uint64_t instance_id;
    uint64_t unknown;
    uint64_t info;
    uint64_t size;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFontFileInfo(DWORD instance_id, DWORD unknown, void *info, DWORD size, DWORD *needed)
{
    struct qemu_GetFontFileInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFONTFILEINFO);
    call.instance_id = (ULONG_PTR)instance_id;
    call.unknown = (ULONG_PTR)unknown;
    call.info = (ULONG_PTR)info;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetFontFileInfo to Wine headers? */
extern BOOL WINAPI GetFontFileInfo(DWORD instance_id, DWORD unknown, void *info, DWORD size, DWORD *needed);
void qemu_GetFontFileInfo(struct qemu_syscall *call)
{
    struct qemu_GetFontFileInfo *c = (struct qemu_GetFontFileInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFontFileInfo(c->instance_id, c->unknown, QEMU_G2H(c->info), c->size, QEMU_G2H(c->needed));
}

#endif
