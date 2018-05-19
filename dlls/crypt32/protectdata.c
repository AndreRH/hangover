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

struct qemu_CryptProtectData
{
    struct qemu_syscall super;
    uint64_t pDataIn;
    uint64_t szDataDescr;
    uint64_t pOptionalEntropy;
    uint64_t pvReserved;
    uint64_t pPromptStruct;
    uint64_t dwFlags;
    uint64_t pDataOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptProtectData(DATA_BLOB* pDataIn, LPCWSTR szDataDescr, DATA_BLOB* pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, DATA_BLOB* pDataOut)
{
    struct qemu_CryptProtectData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTPROTECTDATA);
    call.pDataIn = (ULONG_PTR)pDataIn;
    call.szDataDescr = (ULONG_PTR)szDataDescr;
    call.pOptionalEntropy = (ULONG_PTR)pOptionalEntropy;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.pPromptStruct = (ULONG_PTR)pPromptStruct;
    call.dwFlags = dwFlags;
    call.pDataOut = (ULONG_PTR)pDataOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptProtectData(struct qemu_syscall *call)
{
    struct qemu_CryptProtectData *c = (struct qemu_CryptProtectData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptProtectData(QEMU_G2H(c->pDataIn), QEMU_G2H(c->szDataDescr), QEMU_G2H(c->pOptionalEntropy), QEMU_G2H(c->pvReserved), QEMU_G2H(c->pPromptStruct), c->dwFlags, QEMU_G2H(c->pDataOut));
}

#endif

struct qemu_CryptUnprotectData
{
    struct qemu_syscall super;
    uint64_t pDataIn;
    uint64_t ppszDataDescr;
    uint64_t pOptionalEntropy;
    uint64_t pvReserved;
    uint64_t pPromptStruct;
    uint64_t dwFlags;
    uint64_t pDataOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptUnprotectData(DATA_BLOB* pDataIn, LPWSTR * ppszDataDescr, DATA_BLOB* pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, DATA_BLOB* pDataOut)
{
    struct qemu_CryptUnprotectData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTUNPROTECTDATA);
    call.pDataIn = (ULONG_PTR)pDataIn;
    call.ppszDataDescr = (ULONG_PTR)ppszDataDescr;
    call.pOptionalEntropy = (ULONG_PTR)pOptionalEntropy;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.pPromptStruct = (ULONG_PTR)pPromptStruct;
    call.dwFlags = dwFlags;
    call.pDataOut = (ULONG_PTR)pDataOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptUnprotectData(struct qemu_syscall *call)
{
    struct qemu_CryptUnprotectData *c = (struct qemu_CryptUnprotectData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptUnprotectData(QEMU_G2H(c->pDataIn), QEMU_G2H(c->ppszDataDescr), QEMU_G2H(c->pOptionalEntropy), QEMU_G2H(c->pvReserved), QEMU_G2H(c->pPromptStruct), c->dwFlags, QEMU_G2H(c->pDataOut));
}

#endif

