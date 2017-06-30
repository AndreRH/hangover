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
#include "comdlg32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);
#endif


struct qemu_GetOpenFileNameA
{
    struct qemu_syscall super;
    uint64_t ofn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetOpenFileNameA(OPENFILENAMEA *ofn)
{
    struct qemu_GetOpenFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEA);
    call.ofn = (uint64_t)ofn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOpenFileNameA(struct qemu_syscall *call)
{
    struct qemu_GetOpenFileNameA *c = (struct qemu_GetOpenFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetOpenFileNameA(QEMU_G2H(c->ofn));
}

#endif

struct qemu_GetOpenFileNameW
{
    struct qemu_syscall super;
    uint64_t ofn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetOpenFileNameW(OPENFILENAMEW *ofn)
{
    struct qemu_GetOpenFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEW);
    call.ofn = (uint64_t)ofn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOpenFileNameW(struct qemu_syscall *call)
{
    struct qemu_GetOpenFileNameW *c = (struct qemu_GetOpenFileNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetOpenFileNameW(QEMU_G2H(c->ofn));
}

#endif

struct qemu_GetSaveFileNameA
{
    struct qemu_syscall super;
    uint64_t ofn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSaveFileNameA(OPENFILENAMEA *ofn)
{
    struct qemu_GetSaveFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEA);
    call.ofn = (uint64_t)ofn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSaveFileNameA(struct qemu_syscall *call)
{
    struct qemu_GetSaveFileNameA *c = (struct qemu_GetSaveFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSaveFileNameA(QEMU_G2H(c->ofn));
}

#endif

struct qemu_GetSaveFileNameW
{
    struct qemu_syscall super;
    uint64_t ofn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSaveFileNameW(LPOPENFILENAMEW ofn)
{
    struct qemu_GetSaveFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEW);
    call.ofn = (uint64_t)ofn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSaveFileNameW(struct qemu_syscall *call)
{
    struct qemu_GetSaveFileNameW *c = (struct qemu_GetSaveFileNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSaveFileNameW(QEMU_G2H(c->ofn));
}

#endif

struct qemu_GetFileTitleA
{
    struct qemu_syscall super;
    uint64_t lpFile;
    uint64_t lpTitle;
    uint64_t cbBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short WINAPI GetFileTitleA(LPCSTR lpFile, LPSTR lpTitle, WORD cbBuf)
{
    struct qemu_GetFileTitleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILETITLEA);
    call.lpFile = (uint64_t)lpFile;
    call.lpTitle = (uint64_t)lpTitle;
    call.cbBuf = (uint64_t)cbBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileTitleA(struct qemu_syscall *call)
{
    struct qemu_GetFileTitleA *c = (struct qemu_GetFileTitleA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileTitleA(QEMU_G2H(c->lpFile), QEMU_G2H(c->lpTitle), c->cbBuf);
}

#endif

struct qemu_GetFileTitleW
{
    struct qemu_syscall super;
    uint64_t lpFile;
    uint64_t lpTitle;
    uint64_t cbBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short WINAPI GetFileTitleW(LPCWSTR lpFile, LPWSTR lpTitle, WORD cbBuf)
{
    struct qemu_GetFileTitleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILETITLEW);
    call.lpFile = (uint64_t)lpFile;
    call.lpTitle = (uint64_t)lpTitle;
    call.cbBuf = (uint64_t)cbBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileTitleW(struct qemu_syscall *call)
{
    struct qemu_GetFileTitleW *c = (struct qemu_GetFileTitleW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileTitleW(QEMU_G2H(c->lpFile), QEMU_G2H(c->lpTitle), c->cbBuf);
}

#endif

