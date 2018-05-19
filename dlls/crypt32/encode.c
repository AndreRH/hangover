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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CryptEncodeObject
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t lpszStructType;
    uint64_t pvStructInfo;
    uint64_t pbEncoded;
    uint64_t pcbEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEncodeObject(DWORD dwCertEncodingType, LPCSTR lpszStructType, const void *pvStructInfo, BYTE *pbEncoded, DWORD *pcbEncoded)
{
    struct qemu_CryptEncodeObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENCODEOBJECT);
    call.dwCertEncodingType = dwCertEncodingType;
    call.lpszStructType = (ULONG_PTR)lpszStructType;
    call.pvStructInfo = (ULONG_PTR)pvStructInfo;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEncodeObject(struct qemu_syscall *call)
{
    struct qemu_CryptEncodeObject *c = (struct qemu_CryptEncodeObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptEncodeObject(c->dwCertEncodingType, QEMU_G2H(c->lpszStructType), QEMU_G2H(c->pvStructInfo), QEMU_G2H(c->pbEncoded), QEMU_G2H(c->pcbEncoded));
}

#endif

struct qemu_CryptEncodeObjectEx
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t lpszStructType;
    uint64_t pvStructInfo;
    uint64_t dwFlags;
    uint64_t pEncodePara;
    uint64_t pvEncoded;
    uint64_t pcbEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEncodeObjectEx(DWORD dwCertEncodingType, LPCSTR lpszStructType, const void *pvStructInfo, DWORD dwFlags, PCRYPT_ENCODE_PARA pEncodePara, void *pvEncoded, DWORD *pcbEncoded)
{
    struct qemu_CryptEncodeObjectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENCODEOBJECTEX);
    call.dwCertEncodingType = dwCertEncodingType;
    call.lpszStructType = (ULONG_PTR)lpszStructType;
    call.pvStructInfo = (ULONG_PTR)pvStructInfo;
    call.dwFlags = dwFlags;
    call.pEncodePara = (ULONG_PTR)pEncodePara;
    call.pvEncoded = (ULONG_PTR)pvEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEncodeObjectEx(struct qemu_syscall *call)
{
    struct qemu_CryptEncodeObjectEx *c = (struct qemu_CryptEncodeObjectEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptEncodeObjectEx(c->dwCertEncodingType, QEMU_G2H(c->lpszStructType), QEMU_G2H(c->pvStructInfo), c->dwFlags, QEMU_G2H(c->pEncodePara), QEMU_G2H(c->pvEncoded), QEMU_G2H(c->pcbEncoded));
}

#endif

struct qemu_PFXExportCertStore
{
    struct qemu_syscall super;
    uint64_t hStore;
    uint64_t pPFX;
    uint64_t szPassword;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PFXExportCertStore(HCERTSTORE hStore, CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword, DWORD dwFlags)
{
    struct qemu_PFXExportCertStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFXEXPORTCERTSTORE);
    call.hStore = (ULONG_PTR)hStore;
    call.pPFX = (ULONG_PTR)pPFX;
    call.szPassword = (ULONG_PTR)szPassword;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PFXExportCertStore(struct qemu_syscall *call)
{
    struct qemu_PFXExportCertStore *c = (struct qemu_PFXExportCertStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PFXExportCertStore(QEMU_G2H(c->hStore), QEMU_G2H(c->pPFX), QEMU_G2H(c->szPassword), c->dwFlags);
}

#endif

struct qemu_PFXExportCertStoreEx
{
    struct qemu_syscall super;
    uint64_t hStore;
    uint64_t pPFX;
    uint64_t szPassword;
    uint64_t pvReserved;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PFXExportCertStoreEx(HCERTSTORE hStore, CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword, void *pvReserved, DWORD dwFlags)
{
    struct qemu_PFXExportCertStoreEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PFXEXPORTCERTSTOREEX);
    call.hStore = (ULONG_PTR)hStore;
    call.pPFX = (ULONG_PTR)pPFX;
    call.szPassword = (ULONG_PTR)szPassword;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PFXExportCertStoreEx(struct qemu_syscall *call)
{
    struct qemu_PFXExportCertStoreEx *c = (struct qemu_PFXExportCertStoreEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PFXExportCertStoreEx(QEMU_G2H(c->hStore), QEMU_G2H(c->pPFX), QEMU_G2H(c->szPassword), QEMU_G2H(c->pvReserved), c->dwFlags);
}

#endif

struct qemu_CryptExportPublicKeyInfo
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwKeySpec;
    uint64_t dwCertEncodingType;
    uint64_t pInfo;
    uint64_t pcbInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptExportPublicKeyInfo(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hCryptProv, DWORD dwKeySpec, DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pInfo, DWORD *pcbInfo)
{
    struct qemu_CryptExportPublicKeyInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTEXPORTPUBLICKEYINFO);
    call.hCryptProv = hCryptProv;
    call.dwKeySpec = dwKeySpec;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pInfo = (ULONG_PTR)pInfo;
    call.pcbInfo = (ULONG_PTR)pcbInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptExportPublicKeyInfo(struct qemu_syscall *call)
{
    struct qemu_CryptExportPublicKeyInfo *c = (struct qemu_CryptExportPublicKeyInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptExportPublicKeyInfo(c->hCryptProv, c->dwKeySpec, c->dwCertEncodingType, QEMU_G2H(c->pInfo), QEMU_G2H(c->pcbInfo));
}

#endif

struct qemu_CryptExportPublicKeyInfoEx
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwKeySpec;
    uint64_t dwCertEncodingType;
    uint64_t pszPublicKeyObjId;
    uint64_t dwFlags;
    uint64_t pvAuxInfo;
    uint64_t pInfo;
    uint64_t pcbInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptExportPublicKeyInfoEx(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hCryptProv, DWORD dwKeySpec, DWORD dwCertEncodingType, LPSTR pszPublicKeyObjId, DWORD dwFlags, void *pvAuxInfo, PCERT_PUBLIC_KEY_INFO pInfo, DWORD *pcbInfo)
{
    struct qemu_CryptExportPublicKeyInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTEXPORTPUBLICKEYINFOEX);
    call.hCryptProv = hCryptProv;
    call.dwKeySpec = dwKeySpec;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pszPublicKeyObjId = (ULONG_PTR)pszPublicKeyObjId;
    call.dwFlags = dwFlags;
    call.pvAuxInfo = (ULONG_PTR)pvAuxInfo;
    call.pInfo = (ULONG_PTR)pInfo;
    call.pcbInfo = (ULONG_PTR)pcbInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptExportPublicKeyInfoEx(struct qemu_syscall *call)
{
    struct qemu_CryptExportPublicKeyInfoEx *c = (struct qemu_CryptExportPublicKeyInfoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptExportPublicKeyInfoEx(c->hCryptProv, c->dwKeySpec, c->dwCertEncodingType, QEMU_G2H(c->pszPublicKeyObjId), c->dwFlags, QEMU_G2H(c->pvAuxInfo), QEMU_G2H(c->pInfo), QEMU_G2H(c->pcbInfo));
}

#endif

struct qemu_CryptImportPublicKeyInfo
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwCertEncodingType;
    uint64_t pInfo;
    uint64_t phKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptImportPublicKeyInfo(HCRYPTPROV hCryptProv, DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pInfo, HCRYPTKEY *phKey)
{
    struct qemu_CryptImportPublicKeyInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTIMPORTPUBLICKEYINFO);
    call.hCryptProv = hCryptProv;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pInfo = (ULONG_PTR)pInfo;
    call.phKey = (ULONG_PTR)phKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptImportPublicKeyInfo(struct qemu_syscall *call)
{
    struct qemu_CryptImportPublicKeyInfo *c = (struct qemu_CryptImportPublicKeyInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptImportPublicKeyInfo(c->hCryptProv, c->dwCertEncodingType, QEMU_G2H(c->pInfo), QEMU_G2H(c->phKey));
}

#endif

struct qemu_CryptImportPublicKeyInfoEx
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwCertEncodingType;
    uint64_t pInfo;
    uint64_t aiKeyAlg;
    uint64_t dwFlags;
    uint64_t pvAuxInfo;
    uint64_t phKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptImportPublicKeyInfoEx(HCRYPTPROV hCryptProv, DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pInfo, ALG_ID aiKeyAlg, DWORD dwFlags, void *pvAuxInfo, HCRYPTKEY *phKey)
{
    struct qemu_CryptImportPublicKeyInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTIMPORTPUBLICKEYINFOEX);
    call.hCryptProv = hCryptProv;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pInfo = (ULONG_PTR)pInfo;
    call.aiKeyAlg = aiKeyAlg;
    call.dwFlags = dwFlags;
    call.pvAuxInfo = (ULONG_PTR)pvAuxInfo;
    call.phKey = (ULONG_PTR)phKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptImportPublicKeyInfoEx(struct qemu_syscall *call)
{
    struct qemu_CryptImportPublicKeyInfoEx *c = (struct qemu_CryptImportPublicKeyInfoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptImportPublicKeyInfoEx(c->hCryptProv, c->dwCertEncodingType, QEMU_G2H(c->pInfo), c->aiKeyAlg, c->dwFlags, QEMU_G2H(c->pvAuxInfo), QEMU_G2H(c->phKey));
}

#endif

