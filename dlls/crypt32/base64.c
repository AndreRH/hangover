/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CryptBinaryToStringA
{
    struct qemu_syscall super;
    uint64_t pbBinary;
    uint64_t cbBinary;
    uint64_t dwFlags;
    uint64_t pszString;
    uint64_t pcchString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptBinaryToStringA(const BYTE *pbBinary, DWORD cbBinary, DWORD dwFlags, LPSTR pszString,
        DWORD *pcchString)
{
    struct qemu_CryptBinaryToStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTBINARYTOSTRINGA);
    call.pbBinary = (ULONG_PTR)pbBinary;
    call.cbBinary = cbBinary;
    call.dwFlags = dwFlags;
    call.pszString = (ULONG_PTR)pszString;
    call.pcchString = (ULONG_PTR)pcchString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptBinaryToStringA(struct qemu_syscall *call)
{
    struct qemu_CryptBinaryToStringA *c = (struct qemu_CryptBinaryToStringA *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptBinaryToStringA(QEMU_G2H(c->pbBinary), c->cbBinary, c->dwFlags, QEMU_G2H(c->pszString),
            QEMU_G2H(c->pcchString));
}

#endif

struct qemu_CryptBinaryToStringW
{
    struct qemu_syscall super;
    uint64_t pbBinary;
    uint64_t cbBinary;
    uint64_t dwFlags;
    uint64_t pszString;
    uint64_t pcchString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptBinaryToStringW(const BYTE *pbBinary, DWORD cbBinary, DWORD dwFlags, LPWSTR pszString,
        DWORD *pcchString)
{
    struct qemu_CryptBinaryToStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTBINARYTOSTRINGW);
    call.pbBinary = (ULONG_PTR)pbBinary;
    call.cbBinary = cbBinary;
    call.dwFlags = dwFlags;
    call.pszString = (ULONG_PTR)pszString;
    call.pcchString = (ULONG_PTR)pcchString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptBinaryToStringW(struct qemu_syscall *call)
{
    struct qemu_CryptBinaryToStringW *c = (struct qemu_CryptBinaryToStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptBinaryToStringW(QEMU_G2H(c->pbBinary), c->cbBinary, c->dwFlags, QEMU_G2H(c->pszString),
            QEMU_G2H(c->pcchString));
}

#endif

struct qemu_CryptStringToBinaryA
{
    struct qemu_syscall super;
    uint64_t pszString;
    uint64_t cchString;
    uint64_t dwFlags;
    uint64_t pbBinary;
    uint64_t pcbBinary;
    uint64_t pdwSkip;
    uint64_t pdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptStringToBinaryA(LPCSTR pszString, DWORD cchString, DWORD dwFlags, BYTE *pbBinary,
        DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags)
{
    struct qemu_CryptStringToBinaryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSTRINGTOBINARYA);
    call.pszString = (ULONG_PTR)pszString;
    call.cchString = cchString;
    call.dwFlags = dwFlags;
    call.pbBinary = (ULONG_PTR)pbBinary;
    call.pcbBinary = (ULONG_PTR)pcbBinary;
    call.pdwSkip = (ULONG_PTR)pdwSkip;
    call.pdwFlags = (ULONG_PTR)pdwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptStringToBinaryA(struct qemu_syscall *call)
{
    struct qemu_CryptStringToBinaryA *c = (struct qemu_CryptStringToBinaryA *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptStringToBinaryA(QEMU_G2H(c->pszString), c->cchString, c->dwFlags, QEMU_G2H(c->pbBinary),
            QEMU_G2H(c->pcbBinary), QEMU_G2H(c->pdwSkip), QEMU_G2H(c->pdwFlags));
}

#endif

struct qemu_CryptStringToBinaryW
{
    struct qemu_syscall super;
    uint64_t pszString;
    uint64_t cchString;
    uint64_t dwFlags;
    uint64_t pbBinary;
    uint64_t pcbBinary;
    uint64_t pdwSkip;
    uint64_t pdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptStringToBinaryW(LPCWSTR pszString, DWORD cchString, DWORD dwFlags, BYTE *pbBinary,
        DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags)
{
    struct qemu_CryptStringToBinaryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSTRINGTOBINARYW);
    call.pszString = (ULONG_PTR)pszString;
    call.cchString = cchString;
    call.dwFlags = dwFlags;
    call.pbBinary = (ULONG_PTR)pbBinary;
    call.pcbBinary = (ULONG_PTR)pcbBinary;
    call.pdwSkip = (ULONG_PTR)pdwSkip;
    call.pdwFlags = (ULONG_PTR)pdwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptStringToBinaryW(struct qemu_syscall *call)
{
    struct qemu_CryptStringToBinaryW *c = (struct qemu_CryptStringToBinaryW *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptStringToBinaryW(QEMU_G2H(c->pszString), c->cchString, c->dwFlags, QEMU_G2H(c->pbBinary),
            QEMU_G2H(c->pcbBinary), QEMU_G2H(c->pdwSkip), QEMU_G2H(c->pdwFlags));
}

#endif

