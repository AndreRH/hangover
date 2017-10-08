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

#include "windows-user-services.h"
#include "dll_list.h"
#include "gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_CreateMetaFileW
{
    struct qemu_syscall super;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI CreateMetaFileW(LPCWSTR filename)
{
    struct qemu_CreateMetaFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMETAFILEW);
    call.filename = (ULONG_PTR)filename;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMetaFileW(struct qemu_syscall *call)
{
    struct qemu_CreateMetaFileW *c = (struct qemu_CreateMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateMetaFileW(QEMU_G2H(c->filename));
}

#endif

struct qemu_CreateMetaFileA
{
    struct qemu_syscall super;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI CreateMetaFileA(LPCSTR filename)
{
    struct qemu_CreateMetaFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMETAFILEA);
    call.filename = (ULONG_PTR)filename;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMetaFileA(struct qemu_syscall *call)
{
    struct qemu_CreateMetaFileA *c = (struct qemu_CreateMetaFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateMetaFileA(QEMU_G2H(c->filename));
}

#endif

struct qemu_CloseMetaFile
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMETAFILE WINAPI CloseMetaFile(HDC hdc)
{
    struct qemu_CloseMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEMETAFILE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return (HMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CloseMetaFile(struct qemu_syscall *call)
{
    struct qemu_CloseMetaFile *c = (struct qemu_CloseMetaFile *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CloseMetaFile(QEMU_G2H(c->hdc));
}

#endif

