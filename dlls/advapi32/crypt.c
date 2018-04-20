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
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_CloseEncryptedFileRaw
{
    struct qemu_syscall super;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CloseEncryptedFileRaw(PVOID context)
{
    struct qemu_CloseEncryptedFileRaw call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEENCRYPTEDFILERAW);
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

#else

void qemu_CloseEncryptedFileRaw(struct qemu_syscall *call)
{
    struct qemu_CloseEncryptedFileRaw *c = (struct qemu_CloseEncryptedFileRaw *)call;
    WINE_FIXME("Unverified!\n");
    CloseEncryptedFileRaw(QEMU_G2H(c->context));
}

#endif

struct qemu_CryptAcquireContext
{
    struct qemu_syscall super;
    uint64_t phProv;
    uint64_t pszContainer;
    uint64_t pszProvider;
    uint64_t dwProvType;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptAcquireContextW (HCRYPTPROV *phProv, LPCWSTR pszContainer, LPCWSTR pszProvider, DWORD dwProvType, DWORD dwFlags)
{
    struct qemu_CryptAcquireContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTACQUIRECONTEXTW);
    call.phProv = (ULONG_PTR)phProv;
    call.pszContainer = (ULONG_PTR)pszContainer;
    call.pszProvider = (ULONG_PTR)pszProvider;
    call.dwProvType = (ULONG_PTR)dwProvType;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phProv = (HCRYPTPROV)(ULONG_PTR)call.phProv;

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI CryptAcquireContextA (HCRYPTPROV *phProv, LPCSTR pszContainer, LPCSTR pszProvider, DWORD dwProvType, DWORD dwFlags)
{
    struct qemu_CryptAcquireContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTACQUIRECONTEXTA);
    call.phProv = (ULONG_PTR)phProv;
    call.pszContainer = (ULONG_PTR)pszContainer;
    call.pszProvider = (ULONG_PTR)pszProvider;
    call.dwProvType = (ULONG_PTR)dwProvType;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phProv = (HCRYPTPROV)(ULONG_PTR)call.phProv;

    return call.super.iret;
}

#else

void qemu_CryptAcquireContext(struct qemu_syscall *call)
{
    struct qemu_CryptAcquireContext *c = (struct qemu_CryptAcquireContext *)call;
    HCRYPTPROV prov;

    WINE_TRACE("\n");
    if (c->super.id == QEMU_SYSCALL_ID(CALL_CRYPTACQUIRECONTEXTA))
    {
        c->super.iret = CryptAcquireContextA(c->phProv ? &prov : NULL, QEMU_G2H(c->pszContainer),
                QEMU_G2H(c->pszProvider), c->dwProvType, c->dwFlags);
    }
    else
    {
        c->super.iret = CryptAcquireContextW(c->phProv ? &prov : NULL, QEMU_G2H(c->pszContainer),
                QEMU_G2H(c->pszProvider), c->dwProvType, c->dwFlags);
    }

    c->phProv = QEMU_H2G(prov);
}

#endif

struct qemu_CryptContextAddRef
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t pdwReserved;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptContextAddRef (HCRYPTPROV hProv, DWORD *pdwReserved, DWORD dwFlags)
{
    struct qemu_CryptContextAddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTCONTEXTADDREF);
    call.hProv = (ULONG_PTR)hProv;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptContextAddRef(struct qemu_syscall *call)
{
    struct qemu_CryptContextAddRef *c = (struct qemu_CryptContextAddRef *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptContextAddRef(c->hProv, QEMU_G2H(c->pdwReserved), c->dwFlags);
}

#endif

struct qemu_CryptReleaseContext
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI CryptReleaseContext (HCRYPTPROV hProv, DWORD dwFlags)
{
    struct qemu_CryptReleaseContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTRELEASECONTEXT);
    call.hProv = (ULONG_PTR)hProv;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptReleaseContext(struct qemu_syscall *call)
{
    struct qemu_CryptReleaseContext *c = (struct qemu_CryptReleaseContext *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptReleaseContext(c->hProv, c->dwFlags);
}

#endif

struct qemu_CryptGenRandom
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t dwLen;
    uint64_t pbBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGenRandom (HCRYPTPROV hProv, DWORD dwLen, BYTE *pbBuffer)
{
    struct qemu_CryptGenRandom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGENRANDOM);
    call.hProv = (ULONG_PTR)hProv;
    call.dwLen = (ULONG_PTR)dwLen;
    call.pbBuffer = (ULONG_PTR)pbBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGenRandom(struct qemu_syscall *call)
{
    struct qemu_CryptGenRandom *c = (struct qemu_CryptGenRandom *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptGenRandom(c->hProv, c->dwLen, QEMU_G2H(c->pbBuffer));
}

#endif

struct qemu_CryptCreateHash
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t Algid;
    uint64_t hKey;
    uint64_t dwFlags;
    uint64_t phHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptCreateHash (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH *phHash)
{
    struct qemu_CryptCreateHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTCREATEHASH);
    call.hProv = (ULONG_PTR)hProv;
    call.Algid = (ULONG_PTR)Algid;
    call.hKey = (ULONG_PTR)hKey;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phHash = (ULONG_PTR)phHash;

    qemu_syscall(&call.super);

    if (phHash)
        *phHash = call.phHash;

    return call.super.iret;
}

#else

void qemu_CryptCreateHash(struct qemu_syscall *call)
{
    struct qemu_CryptCreateHash *c = (struct qemu_CryptCreateHash *)call;
    HCRYPTHASH hash;
    WINE_TRACE("\n");

    if (!c->phHash)
    {
        c->super.iret = CryptCreateHash(c->hProv, c->Algid, c->hKey, c->dwFlags, NULL);
        return;
    }

#if GUEST_BIT == HOST_BIT
    hash = *(HCRYPTHASH *)QEMU_G2H(c->phHash);
#else
    hash = (HCRYPTHASH)(ULONG_PTR)*(qemu_ptr *)QEMU_G2H(c->phHash);
#endif

    c->super.iret = CryptCreateHash(c->hProv, c->Algid, c->hKey, c->dwFlags, &hash);

    c->phHash = QEMU_H2G(hash);
}

#endif

struct qemu_CryptDecrypt
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t hHash;
    uint64_t Final;
    uint64_t dwFlags;
    uint64_t pbData;
    uint64_t pdwDataLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDecrypt (HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen)
{
    struct qemu_CryptDecrypt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDECRYPT);
    call.hKey = (ULONG_PTR)hKey;
    call.hHash = (ULONG_PTR)hHash;
    call.Final = (ULONG_PTR)Final;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pbData = (ULONG_PTR)pbData;
    call.pdwDataLen = (ULONG_PTR)pdwDataLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDecrypt(struct qemu_syscall *call)
{
    struct qemu_CryptDecrypt *c = (struct qemu_CryptDecrypt *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptDecrypt(c->hKey, c->hHash, c->Final, c->dwFlags, QEMU_G2H(c->pbData), QEMU_G2H(c->pdwDataLen));
}

#endif

struct qemu_CryptDeriveKey
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t Algid;
    uint64_t hBaseData;
    uint64_t dwFlags;
    uint64_t phKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDeriveKey (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTHASH hBaseData, DWORD dwFlags, HCRYPTKEY *phKey)
{
    struct qemu_CryptDeriveKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDERIVEKEY);
    call.hProv = (ULONG_PTR)hProv;
    call.Algid = (ULONG_PTR)Algid;
    call.hBaseData = (ULONG_PTR)hBaseData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phKey = (ULONG_PTR)phKey;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phKey = (HCRYPTKEY)(ULONG_PTR)call.phKey;

    return call.super.iret;
}

#else

void qemu_CryptDeriveKey(struct qemu_syscall *call)
{
    struct qemu_CryptDeriveKey *c = (struct qemu_CryptDeriveKey *)call;
    HCRYPTKEY key;

    WINE_TRACE("Unverified!\n");

    c->super.iret = CryptDeriveKey(c->hProv, c->Algid, c->hBaseData, c->dwFlags, c->phKey ? &key : NULL);
    c->phKey = QEMU_H2G(key);
}

#endif

struct qemu_CryptDestroyHash
{
    struct qemu_syscall super;
    uint64_t hHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDestroyHash (HCRYPTHASH hHash)
{
    struct qemu_CryptDestroyHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDESTROYHASH);
    call.hHash = (ULONG_PTR)hHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDestroyHash(struct qemu_syscall *call)
{
    struct qemu_CryptDestroyHash *c = (struct qemu_CryptDestroyHash *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptDestroyHash(c->hHash);
}

#endif

struct qemu_CryptDestroyKey
{
    struct qemu_syscall super;
    uint64_t hKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDestroyKey (HCRYPTKEY hKey)
{
    struct qemu_CryptDestroyKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDESTROYKEY);
    call.hKey = (ULONG_PTR)hKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDestroyKey(struct qemu_syscall *call)
{
    struct qemu_CryptDestroyKey *c = (struct qemu_CryptDestroyKey *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptDestroyKey(c->hKey);
}

#endif

struct qemu_CryptDuplicateHash
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t phHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDuplicateHash (HCRYPTHASH hHash, DWORD *pdwReserved, DWORD dwFlags, HCRYPTHASH *phHash)
{
    struct qemu_CryptDuplicateHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDUPLICATEHASH);
    call.hHash = (ULONG_PTR)hHash;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phHash = (ULONG_PTR)phHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDuplicateHash(struct qemu_syscall *call)
{
    struct qemu_CryptDuplicateHash *c = (struct qemu_CryptDuplicateHash *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptDuplicateHash(c->hHash, QEMU_G2H(c->pdwReserved), c->dwFlags, QEMU_G2H(c->phHash));
}

#endif

struct qemu_CryptDuplicateKey
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t phKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptDuplicateKey (HCRYPTKEY hKey, DWORD *pdwReserved, DWORD dwFlags, HCRYPTKEY *phKey)
{
    struct qemu_CryptDuplicateKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTDUPLICATEKEY);
    call.hKey = (ULONG_PTR)hKey;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phKey = (ULONG_PTR)phKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptDuplicateKey(struct qemu_syscall *call)
{
    struct qemu_CryptDuplicateKey *c = (struct qemu_CryptDuplicateKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptDuplicateKey(c->hKey, QEMU_G2H(c->pdwReserved), c->dwFlags, QEMU_G2H(c->phKey));
}

#endif

struct qemu_CryptEncrypt
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t hHash;
    uint64_t Final;
    uint64_t dwFlags;
    uint64_t pbData;
    uint64_t pdwDataLen;
    uint64_t dwBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEncrypt (HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen, DWORD dwBufLen)
{
    struct qemu_CryptEncrypt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENCRYPT);
    call.hKey = (ULONG_PTR)hKey;
    call.hHash = (ULONG_PTR)hHash;
    call.Final = (ULONG_PTR)Final;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pbData = (ULONG_PTR)pbData;
    call.pdwDataLen = (ULONG_PTR)pdwDataLen;
    call.dwBufLen = (ULONG_PTR)dwBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEncrypt(struct qemu_syscall *call)
{
    struct qemu_CryptEncrypt *c = (struct qemu_CryptEncrypt *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptEncrypt(c->hKey, c->hHash, c->Final, c->dwFlags, QEMU_G2H(c->pbData), QEMU_G2H(c->pdwDataLen), c->dwBufLen);
}

#endif

struct qemu_CryptEnumProvidersW
{
    struct qemu_syscall super;
    uint64_t dwIndex;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t pdwProvType;
    uint64_t pszProvName;
    uint64_t pcbProvName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEnumProvidersW (DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType,
        LPWSTR pszProvName, DWORD *pcbProvName)
{
    struct qemu_CryptEnumProvidersW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENUMPROVIDERSW);
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pdwProvType = (ULONG_PTR)pdwProvType;
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.pcbProvName = (ULONG_PTR)pcbProvName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEnumProvidersW(struct qemu_syscall *call)
{
    struct qemu_CryptEnumProvidersW *c = (struct qemu_CryptEnumProvidersW *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptEnumProvidersW(c->dwIndex, QEMU_G2H(c->pdwReserved), c->dwFlags, QEMU_G2H(c->pdwProvType),
            QEMU_G2H(c->pszProvName), QEMU_G2H(c->pcbProvName));
}

#endif

struct qemu_CryptEnumProvidersA
{
    struct qemu_syscall super;
    uint64_t dwIndex;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t pdwProvType;
    uint64_t pszProvName;
    uint64_t pcbProvName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEnumProvidersA (DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType,
        LPSTR pszProvName, DWORD *pcbProvName)
{
    struct qemu_CryptEnumProvidersA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENUMPROVIDERSA);
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pdwProvType = (ULONG_PTR)pdwProvType;
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.pcbProvName = (ULONG_PTR)pcbProvName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEnumProvidersA(struct qemu_syscall *call)
{
    struct qemu_CryptEnumProvidersA *c = (struct qemu_CryptEnumProvidersA *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptEnumProvidersA(c->dwIndex, QEMU_G2H(c->pdwReserved), c->dwFlags, QEMU_G2H(c->pdwProvType),
            QEMU_G2H(c->pszProvName), QEMU_G2H(c->pcbProvName));
}

#endif

struct qemu_CryptEnumProviderTypesW
{
    struct qemu_syscall super;
    uint64_t dwIndex;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t pdwProvType;
    uint64_t pszTypeName;
    uint64_t pcbTypeName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEnumProviderTypesW (DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType,
        LPWSTR pszTypeName, DWORD *pcbTypeName)
{
    struct qemu_CryptEnumProviderTypesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENUMPROVIDERTYPESW);
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pdwProvType = (ULONG_PTR)pdwProvType;
    call.pszTypeName = (ULONG_PTR)pszTypeName;
    call.pcbTypeName = (ULONG_PTR)pcbTypeName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEnumProviderTypesW(struct qemu_syscall *call)
{
    struct qemu_CryptEnumProviderTypesW *c = (struct qemu_CryptEnumProviderTypesW *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptEnumProviderTypesW(c->dwIndex, QEMU_G2H(c->pdwReserved), c->dwFlags, QEMU_G2H(c->pdwProvType),
            QEMU_G2H(c->pszTypeName), QEMU_G2H(c->pcbTypeName));
}

#endif

struct qemu_CryptEnumProviderTypesA
{
    struct qemu_syscall super;
    uint64_t dwIndex;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t pdwProvType;
    uint64_t pszTypeName;
    uint64_t pcbTypeName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEnumProviderTypesA (DWORD dwIndex, DWORD *pdwReserved, DWORD dwFlags, DWORD *pdwProvType,
        LPSTR pszTypeName, DWORD *pcbTypeName)
{
    struct qemu_CryptEnumProviderTypesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENUMPROVIDERTYPESA);
    call.dwIndex = (ULONG_PTR)dwIndex;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pdwProvType = (ULONG_PTR)pdwProvType;
    call.pszTypeName = (ULONG_PTR)pszTypeName;
    call.pcbTypeName = (ULONG_PTR)pcbTypeName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEnumProviderTypesA(struct qemu_syscall *call)
{
    struct qemu_CryptEnumProviderTypesA *c = (struct qemu_CryptEnumProviderTypesA *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptEnumProviderTypesA(c->dwIndex, QEMU_G2H(c->pdwReserved), c->dwFlags, QEMU_G2H(c->pdwProvType),
            QEMU_G2H(c->pszTypeName), QEMU_G2H(c->pcbTypeName));
}

#endif

struct qemu_CryptExportKey
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t hExpKey;
    uint64_t dwBlobType;
    uint64_t dwFlags;
    uint64_t pbData;
    uint64_t pdwDataLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptExportKey (HCRYPTKEY hKey, HCRYPTKEY hExpKey, DWORD dwBlobType, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen)
{
    struct qemu_CryptExportKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTEXPORTKEY);
    call.hKey = (ULONG_PTR)hKey;
    call.hExpKey = (ULONG_PTR)hExpKey;
    call.dwBlobType = (ULONG_PTR)dwBlobType;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pbData = (ULONG_PTR)pbData;
    call.pdwDataLen = (ULONG_PTR)pdwDataLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptExportKey(struct qemu_syscall *call)
{
    struct qemu_CryptExportKey *c = (struct qemu_CryptExportKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptExportKey(c->hKey, c->hExpKey, c->dwBlobType, c->dwFlags, QEMU_G2H(c->pbData), QEMU_G2H(c->pdwDataLen));
}

#endif

struct qemu_CryptGenKey
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t Algid;
    uint64_t dwFlags;
    uint64_t phKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGenKey (HCRYPTPROV hProv, ALG_ID Algid, DWORD dwFlags, HCRYPTKEY *phKey)
{
    struct qemu_CryptGenKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGENKEY);
    call.hProv = (ULONG_PTR)hProv;
    call.Algid = (ULONG_PTR)Algid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phKey = (ULONG_PTR)phKey;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phKey = (HCRYPTKEY)(ULONG_PTR)call.phKey;

    return call.super.iret;
}

#else

void qemu_CryptGenKey(struct qemu_syscall *call)
{
    struct qemu_CryptGenKey *c = (struct qemu_CryptGenKey *)call;
    HCRYPTKEY key;

    WINE_TRACE("\n");

    c->super.iret = CryptGenKey(c->hProv, c->Algid, c->dwFlags, c->phKey ? &key : NULL);
    c->phKey = QEMU_H2G(key);
}

#endif

struct qemu_CryptGetDefaultProviderW
{
    struct qemu_syscall super;
    uint64_t dwProvType;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t pszProvName;
    uint64_t pcbProvName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetDefaultProviderW (DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags,
        LPWSTR pszProvName, DWORD *pcbProvName)
{
    struct qemu_CryptGetDefaultProviderW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETDEFAULTPROVIDERW);
    call.dwProvType = (ULONG_PTR)dwProvType;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.pcbProvName = (ULONG_PTR)pcbProvName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetDefaultProviderW(struct qemu_syscall *call)
{
    struct qemu_CryptGetDefaultProviderW *c = (struct qemu_CryptGetDefaultProviderW *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptGetDefaultProviderW(c->dwProvType, QEMU_G2H(c->pdwReserved), c->dwFlags,
            QEMU_G2H(c->pszProvName), QEMU_G2H(c->pcbProvName));
}

#endif

struct qemu_CryptGetDefaultProviderA
{
    struct qemu_syscall super;
    uint64_t dwProvType;
    uint64_t pdwReserved;
    uint64_t dwFlags;
    uint64_t pszProvName;
    uint64_t pcbProvName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetDefaultProviderA (DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags,
        LPSTR pszProvName, DWORD *pcbProvName)
{
    struct qemu_CryptGetDefaultProviderA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETDEFAULTPROVIDERA);
    call.dwProvType = (ULONG_PTR)dwProvType;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.pcbProvName = (ULONG_PTR)pcbProvName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetDefaultProviderA(struct qemu_syscall *call)
{
    struct qemu_CryptGetDefaultProviderA *c = (struct qemu_CryptGetDefaultProviderA *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptGetDefaultProviderA(c->dwProvType, QEMU_G2H(c->pdwReserved), c->dwFlags,
            QEMU_G2H(c->pszProvName), QEMU_G2H(c->pcbProvName));
}

#endif

struct qemu_CryptGetHashParam
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t dwParam;
    uint64_t pbData;
    uint64_t pdwDataLen;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetHashParam (HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags)
{
    struct qemu_CryptGetHashParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETHASHPARAM);
    call.hHash = (ULONG_PTR)hHash;
    call.dwParam = (ULONG_PTR)dwParam;
    call.pbData = (ULONG_PTR)pbData;
    call.pdwDataLen = (ULONG_PTR)pdwDataLen;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetHashParam(struct qemu_syscall *call)
{
    struct qemu_CryptGetHashParam *c = (struct qemu_CryptGetHashParam *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptGetHashParam(c->hHash, c->dwParam, QEMU_G2H(c->pbData), QEMU_G2H(c->pdwDataLen), c->dwFlags);
}

#endif

struct qemu_CryptGetKeyParam
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t dwParam;
    uint64_t pbData;
    uint64_t pdwDataLen;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetKeyParam (HCRYPTKEY hKey, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags)
{
    struct qemu_CryptGetKeyParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETKEYPARAM);
    call.hKey = (ULONG_PTR)hKey;
    call.dwParam = (ULONG_PTR)dwParam;
    call.pbData = (ULONG_PTR)pbData;
    call.pdwDataLen = (ULONG_PTR)pdwDataLen;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetKeyParam(struct qemu_syscall *call)
{
    struct qemu_CryptGetKeyParam *c = (struct qemu_CryptGetKeyParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetKeyParam(c->hKey, c->dwParam, QEMU_G2H(c->pbData), QEMU_G2H(c->pdwDataLen), c->dwFlags);
}

#endif

struct qemu_CryptGetProvParam
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t dwParam;
    uint64_t pbData;
    uint64_t pdwDataLen;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetProvParam (HCRYPTPROV hProv, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags)
{
    struct qemu_CryptGetProvParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETPROVPARAM);
    call.hProv = (ULONG_PTR)hProv;
    call.dwParam = (ULONG_PTR)dwParam;
    call.pbData = (ULONG_PTR)pbData;
    call.pdwDataLen = (ULONG_PTR)pdwDataLen;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetProvParam(struct qemu_syscall *call)
{
    struct qemu_CryptGetProvParam *c = (struct qemu_CryptGetProvParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetProvParam(c->hProv, c->dwParam, QEMU_G2H(c->pbData), QEMU_G2H(c->pdwDataLen), c->dwFlags);
}

#endif

struct qemu_CryptGetUserKey
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t dwKeySpec;
    uint64_t phUserKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetUserKey (HCRYPTPROV hProv, DWORD dwKeySpec, HCRYPTKEY *phUserKey)
{
    struct qemu_CryptGetUserKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETUSERKEY);
    call.hProv = (ULONG_PTR)hProv;
    call.dwKeySpec = (ULONG_PTR)dwKeySpec;
    call.phUserKey = (ULONG_PTR)phUserKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetUserKey(struct qemu_syscall *call)
{
    struct qemu_CryptGetUserKey *c = (struct qemu_CryptGetUserKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetUserKey(c->hProv, c->dwKeySpec, QEMU_G2H(c->phUserKey));
}

#endif

struct qemu_CryptHashData
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t pbData;
    uint64_t dwDataLen;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptHashData (HCRYPTHASH hHash, const BYTE *pbData, DWORD dwDataLen, DWORD dwFlags)
{
    struct qemu_CryptHashData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTHASHDATA);
    call.hHash = (ULONG_PTR)hHash;
    call.pbData = (ULONG_PTR)pbData;
    call.dwDataLen = (ULONG_PTR)dwDataLen;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptHashData(struct qemu_syscall *call)
{
    struct qemu_CryptHashData *c = (struct qemu_CryptHashData *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptHashData(c->hHash, QEMU_G2H(c->pbData), c->dwDataLen, c->dwFlags);
}

#endif

struct qemu_CryptHashSessionKey
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t hKey;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptHashSessionKey (HCRYPTHASH hHash, HCRYPTKEY hKey, DWORD dwFlags)
{
    struct qemu_CryptHashSessionKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTHASHSESSIONKEY);
    call.hHash = (ULONG_PTR)hHash;
    call.hKey = (ULONG_PTR)hKey;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptHashSessionKey(struct qemu_syscall *call)
{
    struct qemu_CryptHashSessionKey *c = (struct qemu_CryptHashSessionKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptHashSessionKey(c->hHash, c->hKey, c->dwFlags);
}

#endif

struct qemu_CryptImportKey
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t pbData;
    uint64_t dwDataLen;
    uint64_t hPubKey;
    uint64_t dwFlags;
    uint64_t phKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptImportKey (HCRYPTPROV hProv, const BYTE *pbData, DWORD dwDataLen, HCRYPTKEY hPubKey, DWORD dwFlags, HCRYPTKEY *phKey)
{
    struct qemu_CryptImportKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTIMPORTKEY);
    call.hProv = (ULONG_PTR)hProv;
    call.pbData = (ULONG_PTR)pbData;
    call.dwDataLen = (ULONG_PTR)dwDataLen;
    call.hPubKey = (ULONG_PTR)hPubKey;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.phKey = (ULONG_PTR)phKey;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phKey = (HCRYPTKEY)(ULONG_PTR)call.phKey;

    return call.super.iret;
}

#else

void qemu_CryptImportKey(struct qemu_syscall *call)
{
    struct qemu_CryptImportKey *c = (struct qemu_CryptImportKey *)call;
    HCRYPTKEY key;

    /* pbData has a struct BLOBHEADER followed by a DWORD. Both of them are the same in 32 and 64 bit. There
     * may be key-specific other structs though. */
    WINE_TRACE("\n");
    c->super.iret = CryptImportKey(c->hProv, QEMU_G2H(c->pbData), c->dwDataLen, c->hPubKey, c->dwFlags,
            c->phKey ? &key : NULL);
    c->phKey = QEMU_H2G(key);
}

#endif

struct qemu_CryptSignHashW
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t dwKeySpec;
    uint64_t sDescription;
    uint64_t dwFlags;
    uint64_t pbSignature;
    uint64_t pdwSigLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSignHashW (HCRYPTHASH hHash, DWORD dwKeySpec, LPCWSTR sDescription, DWORD dwFlags, BYTE *pbSignature, DWORD *pdwSigLen)
{
    struct qemu_CryptSignHashW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIGNHASHW);
    call.hHash = (ULONG_PTR)hHash;
    call.dwKeySpec = (ULONG_PTR)dwKeySpec;
    call.sDescription = (ULONG_PTR)sDescription;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pbSignature = (ULONG_PTR)pbSignature;
    call.pdwSigLen = (ULONG_PTR)pdwSigLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSignHashW(struct qemu_syscall *call)
{
    struct qemu_CryptSignHashW *c = (struct qemu_CryptSignHashW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSignHashW(c->hHash, c->dwKeySpec, QEMU_G2H(c->sDescription), c->dwFlags, QEMU_G2H(c->pbSignature), QEMU_G2H(c->pdwSigLen));
}

#endif

struct qemu_CryptSignHashA
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t dwKeySpec;
    uint64_t sDescription;
    uint64_t dwFlags;
    uint64_t pbSignature;
    uint64_t pdwSigLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSignHashA (HCRYPTHASH hHash, DWORD dwKeySpec, LPCSTR sDescription, DWORD dwFlags, BYTE *pbSignature, DWORD *pdwSigLen)
{
    struct qemu_CryptSignHashA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIGNHASHA);
    call.hHash = (ULONG_PTR)hHash;
    call.dwKeySpec = (ULONG_PTR)dwKeySpec;
    call.sDescription = (ULONG_PTR)sDescription;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pbSignature = (ULONG_PTR)pbSignature;
    call.pdwSigLen = (ULONG_PTR)pdwSigLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSignHashA(struct qemu_syscall *call)
{
    struct qemu_CryptSignHashA *c = (struct qemu_CryptSignHashA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSignHashA(c->hHash, c->dwKeySpec, QEMU_G2H(c->sDescription), c->dwFlags, QEMU_G2H(c->pbSignature), QEMU_G2H(c->pdwSigLen));
}

#endif

struct qemu_CryptSetHashParam
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t dwParam;
    uint64_t pbData;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetHashParam (HCRYPTHASH hHash, DWORD dwParam, const BYTE *pbData, DWORD dwFlags)
{
    struct qemu_CryptSetHashParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETHASHPARAM);
    call.hHash = (ULONG_PTR)hHash;
    call.dwParam = (ULONG_PTR)dwParam;
    call.pbData = (ULONG_PTR)pbData;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetHashParam(struct qemu_syscall *call)
{
    struct qemu_CryptSetHashParam *c = (struct qemu_CryptSetHashParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSetHashParam(c->hHash, c->dwParam, QEMU_G2H(c->pbData), c->dwFlags);
}

#endif

struct qemu_CryptSetKeyParam
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t dwParam;
    uint64_t pbData;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetKeyParam (HCRYPTKEY hKey, DWORD dwParam, const BYTE *pbData, DWORD dwFlags)
{
    struct qemu_CryptSetKeyParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETKEYPARAM);
    call.hKey = (ULONG_PTR)hKey;
    call.dwParam = (ULONG_PTR)dwParam;
    call.pbData = (ULONG_PTR)pbData;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetKeyParam(struct qemu_syscall *call)
{
    struct qemu_CryptSetKeyParam *c = (struct qemu_CryptSetKeyParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSetKeyParam(c->hKey, c->dwParam, QEMU_G2H(c->pbData), c->dwFlags);
}

#endif

struct qemu_CryptSetProviderA
{
    struct qemu_syscall super;
    uint64_t pszProvName;
    uint64_t dwProvType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetProviderA (LPCSTR pszProvName, DWORD dwProvType)
{
    struct qemu_CryptSetProviderA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETPROVIDERA);
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.dwProvType = (ULONG_PTR)dwProvType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetProviderA(struct qemu_syscall *call)
{
    struct qemu_CryptSetProviderA *c = (struct qemu_CryptSetProviderA *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptSetProviderA(QEMU_G2H(c->pszProvName), c->dwProvType);
}

#endif

struct qemu_CryptSetProviderW
{
    struct qemu_syscall super;
    uint64_t pszProvName;
    uint64_t dwProvType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetProviderW (LPCWSTR pszProvName, DWORD dwProvType)
{
    struct qemu_CryptSetProviderW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETPROVIDERW);
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.dwProvType = (ULONG_PTR)dwProvType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetProviderW(struct qemu_syscall *call)
{
    struct qemu_CryptSetProviderW *c = (struct qemu_CryptSetProviderW *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptSetProviderW(QEMU_G2H(c->pszProvName), c->dwProvType);
}

#endif

struct qemu_CryptSetProviderExW
{
    struct qemu_syscall super;
    uint64_t pszProvName;
    uint64_t dwProvType;
    uint64_t pdwReserved;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetProviderExW (LPCWSTR pszProvName, DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags)
{
    struct qemu_CryptSetProviderExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETPROVIDEREXW);
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.dwProvType = (ULONG_PTR)dwProvType;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetProviderExW(struct qemu_syscall *call)
{
    struct qemu_CryptSetProviderExW *c = (struct qemu_CryptSetProviderExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSetProviderExW(QEMU_G2H(c->pszProvName), c->dwProvType, QEMU_G2H(c->pdwReserved), c->dwFlags);
}

#endif

struct qemu_CryptSetProviderExA
{
    struct qemu_syscall super;
    uint64_t pszProvName;
    uint64_t dwProvType;
    uint64_t pdwReserved;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetProviderExA (LPCSTR pszProvName, DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags)
{
    struct qemu_CryptSetProviderExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETPROVIDEREXA);
    call.pszProvName = (ULONG_PTR)pszProvName;
    call.dwProvType = (ULONG_PTR)dwProvType;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetProviderExA(struct qemu_syscall *call)
{
    struct qemu_CryptSetProviderExA *c = (struct qemu_CryptSetProviderExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSetProviderExA(QEMU_G2H(c->pszProvName), c->dwProvType, QEMU_G2H(c->pdwReserved), c->dwFlags);
}

#endif

struct qemu_CryptSetProvParam
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t dwParam;
    uint64_t pbData;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetProvParam (HCRYPTPROV hProv, DWORD dwParam, const BYTE *pbData, DWORD dwFlags)
{
    struct qemu_CryptSetProvParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETPROVPARAM);
    call.hProv = (ULONG_PTR)hProv;
    call.dwParam = (ULONG_PTR)dwParam;
    call.pbData = (ULONG_PTR)pbData;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetProvParam(struct qemu_syscall *call)
{
    struct qemu_CryptSetProvParam *c = (struct qemu_CryptSetProvParam *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSetProvParam(c->hProv, c->dwParam, QEMU_G2H(c->pbData), c->dwFlags);
}

#endif

struct qemu_CryptVerifySignatureW
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t pbSignature;
    uint64_t dwSigLen;
    uint64_t hPubKey;
    uint64_t sDescription;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifySignatureW (HCRYPTHASH hHash, const BYTE *pbSignature, DWORD dwSigLen, HCRYPTKEY hPubKey, LPCWSTR sDescription, DWORD dwFlags)
{
    struct qemu_CryptVerifySignatureW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYSIGNATUREW);
    call.hHash = (ULONG_PTR)hHash;
    call.pbSignature = (ULONG_PTR)pbSignature;
    call.dwSigLen = (ULONG_PTR)dwSigLen;
    call.hPubKey = (ULONG_PTR)hPubKey;
    call.sDescription = (ULONG_PTR)sDescription;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifySignatureW(struct qemu_syscall *call)
{
    struct qemu_CryptVerifySignatureW *c = (struct qemu_CryptVerifySignatureW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptVerifySignatureW(c->hHash, QEMU_G2H(c->pbSignature), c->dwSigLen, c->hPubKey, QEMU_G2H(c->sDescription), c->dwFlags);
}

#endif

struct qemu_CryptVerifySignatureA
{
    struct qemu_syscall super;
    uint64_t hHash;
    uint64_t pbSignature;
    uint64_t dwSigLen;
    uint64_t hPubKey;
    uint64_t sDescription;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifySignatureA (HCRYPTHASH hHash, const BYTE *pbSignature, DWORD dwSigLen, HCRYPTKEY hPubKey, LPCSTR sDescription, DWORD dwFlags)
{
    struct qemu_CryptVerifySignatureA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYSIGNATUREA);
    call.hHash = (ULONG_PTR)hHash;
    call.pbSignature = (ULONG_PTR)pbSignature;
    call.dwSigLen = (ULONG_PTR)dwSigLen;
    call.hPubKey = (ULONG_PTR)hPubKey;
    call.sDescription = (ULONG_PTR)sDescription;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifySignatureA(struct qemu_syscall *call)
{
    struct qemu_CryptVerifySignatureA *c = (struct qemu_CryptVerifySignatureA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptVerifySignatureA(c->hHash, QEMU_G2H(c->pbSignature), c->dwSigLen, c->hPubKey, QEMU_G2H(c->sDescription), c->dwFlags);
}

#endif

struct qemu_OpenEncryptedFileRawA
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI OpenEncryptedFileRawA(LPCSTR filename, ULONG flags, PVOID *context)
{
    struct qemu_OpenEncryptedFileRawA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENENCRYPTEDFILERAWA);
    call.filename = (ULONG_PTR)filename;
    call.flags = (ULONG_PTR)flags;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenEncryptedFileRawA(struct qemu_syscall *call)
{
    struct qemu_OpenEncryptedFileRawA *c = (struct qemu_OpenEncryptedFileRawA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenEncryptedFileRawA(QEMU_G2H(c->filename), c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_OpenEncryptedFileRawW
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI OpenEncryptedFileRawW(LPCWSTR filename, ULONG flags, PVOID *context)
{
    struct qemu_OpenEncryptedFileRawW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENENCRYPTEDFILERAWW);
    call.filename = (ULONG_PTR)filename;
    call.flags = (ULONG_PTR)flags;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenEncryptedFileRawW(struct qemu_syscall *call)
{
    struct qemu_OpenEncryptedFileRawW *c = (struct qemu_OpenEncryptedFileRawW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenEncryptedFileRawW(QEMU_G2H(c->filename), c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_ReadEncryptedFileRaw
{
    struct qemu_syscall super;
    uint64_t export;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ReadEncryptedFileRaw(PFE_EXPORT_FUNC export, PVOID callback, PVOID context)
{
    struct qemu_ReadEncryptedFileRaw call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READENCRYPTEDFILERAW);
    call.export = (ULONG_PTR)export;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadEncryptedFileRaw(struct qemu_syscall *call)
{
    struct qemu_ReadEncryptedFileRaw *c = (struct qemu_ReadEncryptedFileRaw *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadEncryptedFileRaw(QEMU_G2H(c->export), QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_SystemFunction030
{
    struct qemu_syscall super;
    uint64_t b1;
    uint64_t b2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SystemFunction030(LPCVOID b1, LPCVOID b2)
{
    struct qemu_SystemFunction030 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION030);
    call.b1 = (ULONG_PTR)b1;
    call.b2 = (ULONG_PTR)b2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SystemFunction030 to Wine headers? */
extern BOOL WINAPI SystemFunction030(LPCVOID b1, LPCVOID b2);
void qemu_SystemFunction030(struct qemu_syscall *call)
{
    struct qemu_SystemFunction030 *c = (struct qemu_SystemFunction030 *)call;
    WINE_TRACE("\n");
    c->super.iret = SystemFunction030(QEMU_G2H(c->b1), QEMU_G2H(c->b2));
}

#endif

struct qemu_SystemFunction035
{
    struct qemu_syscall super;
    uint64_t lpszDllFilePath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SystemFunction035(LPCSTR lpszDllFilePath)
{
    struct qemu_SystemFunction035 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION035);
    call.lpszDllFilePath = (ULONG_PTR)lpszDllFilePath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SystemFunction035 to Wine headers? */
extern BOOL WINAPI SystemFunction035(LPCSTR lpszDllFilePath);
void qemu_SystemFunction035(struct qemu_syscall *call)
{
    struct qemu_SystemFunction035 *c = (struct qemu_SystemFunction035 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction035(QEMU_G2H(c->lpszDllFilePath));
}

#endif

struct qemu_SystemFunction036
{
    struct qemu_syscall super;
    uint64_t pbBuffer;
    uint64_t dwLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI SystemFunction036(PVOID pbBuffer, ULONG dwLen)
{
    struct qemu_SystemFunction036 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION036);
    call.pbBuffer = (ULONG_PTR)pbBuffer;
    call.dwLen = (ULONG_PTR)dwLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SystemFunction036 to Wine headers? */
extern BOOLEAN WINAPI SystemFunction036(PVOID pbBuffer, ULONG dwLen);
void qemu_SystemFunction036(struct qemu_syscall *call)
{
    struct qemu_SystemFunction036 *c = (struct qemu_SystemFunction036 *)call;
    WINE_TRACE("\n");
    c->super.iret = SystemFunction036(QEMU_G2H(c->pbBuffer), c->dwLen);
}

#endif

struct qemu_SystemFunction040
{
    struct qemu_syscall super;
    uint64_t memory;
    uint64_t length;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction040(PVOID memory, ULONG length, ULONG flags)
{
    struct qemu_SystemFunction040 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION040);
    call.memory = (ULONG_PTR)memory;
    call.length = (ULONG_PTR)length;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SystemFunction040 to Wine headers? */
extern NTSTATUS WINAPI SystemFunction040(PVOID memory, ULONG length, ULONG flags);
void qemu_SystemFunction040(struct qemu_syscall *call)
{
    struct qemu_SystemFunction040 *c = (struct qemu_SystemFunction040 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction040(QEMU_G2H(c->memory), c->length, c->flags);
}

#endif

struct qemu_SystemFunction041
{
    struct qemu_syscall super;
    uint64_t memory;
    uint64_t length;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction041(PVOID memory, ULONG length, ULONG flags)
{
    struct qemu_SystemFunction041 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION041);
    call.memory = (ULONG_PTR)memory;
    call.length = (ULONG_PTR)length;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SystemFunction041 to Wine headers? */
extern NTSTATUS WINAPI SystemFunction041(PVOID memory, ULONG length, ULONG flags);
void qemu_SystemFunction041(struct qemu_syscall *call)
{
    struct qemu_SystemFunction041 *c = (struct qemu_SystemFunction041 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction041(QEMU_G2H(c->memory), c->length, c->flags);
}

#endif

struct qemu_WriteEncryptedFileRaw
{
    struct qemu_syscall super;
    uint64_t import;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WriteEncryptedFileRaw(PFE_IMPORT_FUNC import, PVOID callback, PVOID context)
{
    struct qemu_WriteEncryptedFileRaw call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEENCRYPTEDFILERAW);
    call.import = (ULONG_PTR)import;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteEncryptedFileRaw(struct qemu_syscall *call)
{
    struct qemu_WriteEncryptedFileRaw *c = (struct qemu_WriteEncryptedFileRaw *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteEncryptedFileRaw(QEMU_G2H(c->import), QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

