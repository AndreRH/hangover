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
#include <wintrust.h>
#include <mssip.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_mssip.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <wine/exception.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CryptDecodeObject
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t lpszStructType;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t dwFlags;
    uint64_t pvStructInfo;
    uint64_t pcbStructInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDecodeObject(DWORD dwCertEncodingType, LPCSTR lpszStructType, const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, DWORD *pcbStructInfo)
{
    struct qemu_CryptDecodeObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDECODEOBJECT);
    call.dwCertEncodingType = dwCertEncodingType;
    call.lpszStructType = (ULONG_PTR)lpszStructType;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.dwFlags = dwFlags;
    call.pvStructInfo = (ULONG_PTR)pvStructInfo;
    call.pcbStructInfo = (ULONG_PTR)pcbStructInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDecodeObject(struct qemu_syscall *call)
{
    struct qemu_CryptDecodeObject *c = (struct qemu_CryptDecodeObject *)call;
    const char *type = QEMU_G2H(c->lpszStructType);

    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptDecodeObject(c->dwCertEncodingType, QEMU_G2H(c->lpszStructType), QEMU_G2H(c->pbEncoded),
            c->cbEncoded, c->dwFlags, QEMU_G2H(c->pvStructInfo), QEMU_G2H(c->pcbStructInfo));

    if (c->pvStructInfo)
    {
        __TRY
        {
            if (IS_INTOID(type))
            {
                WINE_FIXME("Intoid not handled yet.\n");
            }
            else if (!strcmp(type, SPC_INDIRECT_DATA_OBJID))
            {
                SIP_INDIRECT_DATA_h2g(QEMU_G2H(c->pvStructInfo), QEMU_G2H(c->pvStructInfo));
            }
            else
            {
                WINE_FIXME("String struct types not handled yet.\n");
                WINE_FIXME("Type is \"%s\"\n", type);
            }
        }
        __EXCEPT_PAGE_FAULT
        {
            WINE_ERR("page fault\n");
        }
        __ENDTRY
    }
}

#endif

struct qemu_CryptDecodeObjectEx
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t lpszStructType;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t dwFlags;
    uint64_t pDecodePara;
    uint64_t pvStructInfo;
    uint64_t pcbStructInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDecodeObjectEx(DWORD dwCertEncodingType, LPCSTR lpszStructType, const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, PCRYPT_DECODE_PARA pDecodePara, void *pvStructInfo, DWORD *pcbStructInfo)
{
    struct qemu_CryptDecodeObjectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDECODEOBJECTEX);
    call.dwCertEncodingType = dwCertEncodingType;
    call.lpszStructType = (ULONG_PTR)lpszStructType;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.dwFlags = dwFlags;
    call.pDecodePara = (ULONG_PTR)pDecodePara;
    call.pvStructInfo = (ULONG_PTR)pvStructInfo;
    call.pcbStructInfo = (ULONG_PTR)pcbStructInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDecodeObjectEx(struct qemu_syscall *call)
{
    struct qemu_CryptDecodeObjectEx *c = (struct qemu_CryptDecodeObjectEx *)call;
    const char *type = QEMU_G2H(c->pvStructInfo);

    WINE_FIXME("Unverified!\n");

    c->super.iret = CryptDecodeObjectEx(c->dwCertEncodingType, QEMU_G2H(c->lpszStructType), QEMU_G2H(c->pbEncoded), c->cbEncoded, c->dwFlags, QEMU_G2H(c->pDecodePara), type, QEMU_G2H(c->pcbStructInfo));
}

#endif

struct qemu_PFXIsPFXBlob
{
    struct qemu_syscall super;
    uint64_t pPFX;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PFXIsPFXBlob(CRYPT_DATA_BLOB *pPFX)
{
    struct qemu_PFXIsPFXBlob call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFXISPFXBLOB);
    call.pPFX = (ULONG_PTR)pPFX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PFXIsPFXBlob(struct qemu_syscall *call)
{
    struct qemu_PFXIsPFXBlob *c = (struct qemu_PFXIsPFXBlob *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PFXIsPFXBlob(QEMU_G2H(c->pPFX));
}

#endif

struct qemu_PFXImportCertStore
{
    struct qemu_syscall super;
    uint64_t pPFX;
    uint64_t szPassword;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCERTSTORE WINAPI PFXImportCertStore(CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword, DWORD dwFlags)
{
    struct qemu_PFXImportCertStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFXIMPORTCERTSTORE);
    call.pPFX = (ULONG_PTR)pPFX;
    call.szPassword = (ULONG_PTR)szPassword;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return (HCERTSTORE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PFXImportCertStore(struct qemu_syscall *call)
{
    struct qemu_PFXImportCertStore *c = (struct qemu_PFXImportCertStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(PFXImportCertStore(QEMU_G2H(c->pPFX), QEMU_G2H(c->szPassword), c->dwFlags));
}

#endif

struct qemu_PFXVerifyPassword
{
    struct qemu_syscall super;
    uint64_t pPFX;
    uint64_t szPassword;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PFXVerifyPassword(CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword, DWORD dwFlags)
{
    struct qemu_PFXVerifyPassword call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFXVERIFYPASSWORD);
    call.pPFX = (ULONG_PTR)pPFX;
    call.szPassword = (ULONG_PTR)szPassword;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PFXVerifyPassword(struct qemu_syscall *call)
{
    struct qemu_PFXVerifyPassword *c = (struct qemu_PFXVerifyPassword *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PFXVerifyPassword(QEMU_G2H(c->pPFX), QEMU_G2H(c->szPassword), c->dwFlags);
}

#endif

