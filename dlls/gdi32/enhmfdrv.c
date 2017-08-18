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


struct qemu_CreateEnhMetaFileA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t filename;
    uint64_t rect;
    uint64_t description;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI CreateEnhMetaFileA(HDC hdc, LPCSTR filename, const RECT *rect, LPCSTR description)
{
    struct qemu_CreateEnhMetaFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEENHMETAFILEA);
    call.hdc = (uint64_t)hdc;
    call.filename = (uint64_t)filename;
    call.rect = (uint64_t)rect;
    call.description = (uint64_t)description;

    qemu_syscall(&call.super);

    return (HDC)call.super.iret;
}

#else

void qemu_CreateEnhMetaFileA(struct qemu_syscall *call)
{
    struct qemu_CreateEnhMetaFileA *c = (struct qemu_CreateEnhMetaFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateEnhMetaFileA(QEMU_G2H(c->hdc), QEMU_G2H(c->filename), QEMU_G2H(c->rect), QEMU_G2H(c->description));
}

#endif

struct qemu_CreateEnhMetaFileW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t filename;
    uint64_t rect;
    uint64_t description;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDC WINAPI CreateEnhMetaFileW(HDC hdc, LPCWSTR filename, const RECT* rect, LPCWSTR description)
{
    struct qemu_CreateEnhMetaFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEENHMETAFILEW);
    call.hdc = (uint64_t)hdc;
    call.filename = (uint64_t)filename;
    call.rect = (uint64_t)rect;
    call.description = (uint64_t)description;

    qemu_syscall(&call.super);

    return (HDC)call.super.iret;
}

#else

void qemu_CreateEnhMetaFileW(struct qemu_syscall *call)
{
    struct qemu_CreateEnhMetaFileW *c = (struct qemu_CreateEnhMetaFileW *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CreateEnhMetaFileW(QEMU_G2H(c->hdc), QEMU_G2H(c->filename), QEMU_G2H(c->rect), QEMU_G2H(c->description));
}

#endif

struct qemu_CloseEnhMetaFile
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HENHMETAFILE WINAPI CloseEnhMetaFile(HDC hdc)
{
    struct qemu_CloseEnhMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEENHMETAFILE);
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return (HENHMETAFILE)call.super.iret;
}

#else

void qemu_CloseEnhMetaFile(struct qemu_syscall *call)
{
    struct qemu_CloseEnhMetaFile *c = (struct qemu_CloseEnhMetaFile *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)CloseEnhMetaFile(QEMU_G2H(c->hdc));
}

#endif

