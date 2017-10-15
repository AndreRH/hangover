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

struct qemu_SHQueryRecycleBinA
{
    struct qemu_syscall super;
    uint64_t pszRootPath;
    uint64_t pSHQueryRBInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHQueryRecycleBinA(LPCSTR pszRootPath, LPSHQUERYRBINFO pSHQueryRBInfo)
{
    struct qemu_SHQueryRecycleBinA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHQUERYRECYCLEBINA);
    call.pszRootPath = (ULONG_PTR)pszRootPath;
    call.pSHQueryRBInfo = (ULONG_PTR)pSHQueryRBInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHQueryRecycleBinA(struct qemu_syscall *call)
{
    struct qemu_SHQueryRecycleBinA *c = (struct qemu_SHQueryRecycleBinA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHQueryRecycleBinA(QEMU_G2H(c->pszRootPath), QEMU_G2H(c->pSHQueryRBInfo));
}

#endif

struct qemu_SHQueryRecycleBinW
{
    struct qemu_syscall super;
    uint64_t pszRootPath;
    uint64_t pSHQueryRBInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHQueryRecycleBinW(LPCWSTR pszRootPath, LPSHQUERYRBINFO pSHQueryRBInfo)
{
    struct qemu_SHQueryRecycleBinW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHQUERYRECYCLEBINW);
    call.pszRootPath = (ULONG_PTR)pszRootPath;
    call.pSHQueryRBInfo = (ULONG_PTR)pSHQueryRBInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHQueryRecycleBinW(struct qemu_syscall *call)
{
    struct qemu_SHQueryRecycleBinW *c = (struct qemu_SHQueryRecycleBinW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHQueryRecycleBinW(QEMU_G2H(c->pszRootPath), QEMU_G2H(c->pSHQueryRBInfo));
}

#endif

struct qemu_SHEmptyRecycleBinA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pszRootPath;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHEmptyRecycleBinA(HWND hwnd, LPCSTR pszRootPath, DWORD dwFlags)
{
    struct qemu_SHEmptyRecycleBinA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHEMPTYRECYCLEBINA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pszRootPath = (ULONG_PTR)pszRootPath;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHEmptyRecycleBinA(struct qemu_syscall *call)
{
    struct qemu_SHEmptyRecycleBinA *c = (struct qemu_SHEmptyRecycleBinA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHEmptyRecycleBinA(QEMU_G2H(c->hwnd), QEMU_G2H(c->pszRootPath), c->dwFlags);
}

#endif

struct qemu_SHEmptyRecycleBinW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pszRootPath;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHEmptyRecycleBinW(HWND hwnd, LPCWSTR pszRootPath, DWORD dwFlags)
{
    struct qemu_SHEmptyRecycleBinW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHEMPTYRECYCLEBINW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pszRootPath = (ULONG_PTR)pszRootPath;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHEmptyRecycleBinW(struct qemu_syscall *call)
{
    struct qemu_SHEmptyRecycleBinW *c = (struct qemu_SHEmptyRecycleBinW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHEmptyRecycleBinW(QEMU_G2H(c->hwnd), QEMU_G2H(c->pszRootPath), c->dwFlags);
}

#endif

struct qemu_SHUpdateRecycleBinIcon
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHUpdateRecycleBinIcon(void)
{
    struct qemu_SHUpdateRecycleBinIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUPDATERECYCLEBINICON);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHUpdateRecycleBinIcon to Wine headers? */
extern HRESULT WINAPI SHUpdateRecycleBinIcon(void);
void qemu_SHUpdateRecycleBinIcon(struct qemu_syscall *call)
{
    struct qemu_SHUpdateRecycleBinIcon *c = (struct qemu_SHUpdateRecycleBinIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHUpdateRecycleBinIcon();
}

#endif

