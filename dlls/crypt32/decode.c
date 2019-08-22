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

BOOL WINAPI qemu_CryptDecodeObjectEx(DWORD dwCertEncodingType, LPCSTR lpszStructType,
        const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, PCRYPT_DECODE_PARA pDecodePara,
        void *pvStructInfo, DWORD *pcbStructInfo)
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

    if (call.super.iret)
    {
        if (dwFlags & CRYPT_ENCODE_ALLOC_FLAG)
            *(void **)pvStructInfo = (void *)(ULONG_PTR)call.pvStructInfo;
    }

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI CryptDecodeObject(DWORD dwCertEncodingType, LPCSTR lpszStructType, const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, DWORD *pcbStructInfo)
{
    return qemu_CryptDecodeObjectEx(dwCertEncodingType, lpszStructType,
            pbEncoded, cbEncoded, dwFlags, NULL, pvStructInfo, pcbStructInfo);
}

#else

void qemu_CryptDecodeObjectEx(struct qemu_syscall *call)
{
    struct qemu_CryptDecodeObjectEx *c = (struct qemu_CryptDecodeObjectEx *)call;
    const char *type = QEMU_G2H(c->lpszStructType);
    void *alloc;

    WINE_FIXME("Unfinished, flags %x para %p!\n", (DWORD)c->dwFlags, QEMU_G2H(c->pDecodePara));

    c->super.iret = CryptDecodeObjectEx(c->dwCertEncodingType, type,
            QEMU_G2H(c->pbEncoded), c->cbEncoded, c->dwFlags, QEMU_G2H(c->pDecodePara),
            c->dwFlags & CRYPT_ENCODE_ALLOC_FLAG ? &alloc : QEMU_G2H(c->pvStructInfo),
            QEMU_G2H(c->pcbStructInfo));

    WINE_TRACE("Host result %x\n", (BOOL)c->super.iret);
    if (!c->super.iret)
        return;

    if (c->dwFlags & CRYPT_ENCODE_ALLOC_FLAG)
        c->pvStructInfo = QEMU_H2G(alloc);

    if (c->pvStructInfo)
    {
        __TRY
        {
            if (IS_INTOID(type))
            {
                switch (LOWORD(type))
                {
                case LOWORD(X509_CERT):
                    WINE_FIXME("X509_CERT\n");
                    break;
                case LOWORD(X509_CERT_TO_BE_SIGNED):
                    WINE_FIXME("X509_CERT_TO_BE_SIGNED\n");
                    break;
                case LOWORD(X509_CERT_CRL_TO_BE_SIGNED):
                    WINE_FIXME("X509_CERT_CRL_TO_BE_SIGNED\n");
                    break;
                case LOWORD(X509_EXTENSIONS):
                    WINE_FIXME("X509_EXTENSIONS\n");
                    break;
                case LOWORD(X509_NAME_VALUE):
                    WINE_FIXME("X509_NAME_VALUE\n");
                    break;
                case LOWORD(X509_NAME):
                    WINE_FIXME("X509_NAME\n");
                    break;
                case LOWORD(X509_PUBLIC_KEY_INFO):
                    WINE_FIXME("X509_PUBLIC_KEY_INFO\n");
                    break;
                case LOWORD(X509_AUTHORITY_KEY_ID):
                    WINE_FIXME("X509_AUTHORITY_KEY_ID\n");
                    break;
                case LOWORD(X509_ALTERNATE_NAME):
                    WINE_FIXME("X509_ALTERNATE_NAME\n");
                    break;
                case LOWORD(X509_BASIC_CONSTRAINTS):
                    WINE_FIXME("X509_BASIC_CONSTRAINTS\n");
                    break;
                case LOWORD(X509_BASIC_CONSTRAINTS2):
                    WINE_FIXME("X509_BASIC_CONSTRAINTS2\n");
                    break;
                case LOWORD(X509_CERT_POLICIES):
                    WINE_FIXME("X509_CERT_POLICIES\n");
                    break;
                case LOWORD(RSA_CSP_PUBLICKEYBLOB):
                    WINE_FIXME("RSA_CSP_PUBLICKEYBLOB\n");
                    break;
                case LOWORD(PKCS_RSA_PRIVATE_KEY):
                    WINE_FIXME("PKCS_RSA_PRIVATE_KEY\n");
                    break;
                case LOWORD(X509_UNICODE_NAME):
                    WINE_FIXME("X509_UNICODE_NAME\n");
                    break;
                case LOWORD(PKCS_ATTRIBUTE):
                    WINE_FIXME("PKCS_ATTRIBUTE\n");
                    break;
                case LOWORD(X509_UNICODE_NAME_VALUE):
                    WINE_FIXME("X509_UNICODE_NAME_VALUE\n");
                    break;
                case LOWORD(X509_OCTET_STRING):
                    WINE_FIXME("X509_OCTET_STRING\n");
                    break;
                case LOWORD(X509_BITS):
                    WINE_FIXME("X509_BITS\n");
                    break;
                case LOWORD(X509_KEY_USAGE):
                    WINE_FIXME("X509_KEY_USAGE\n");
                    break;
                case LOWORD(X509_INTEGER):
                    WINE_FIXME("X509_INTEGER\n");
                    break;
                case LOWORD(X509_MULTI_BYTE_INTEGER):
                    WINE_FIXME("X509_MULTI_BYTE_INTEGER\n");
                    break;
                case LOWORD(X509_MULTI_BYTE_UINT):
                    WINE_FIXME("X509_MULTI_BYTE_UINT\n");
                    break;
                case LOWORD(X509_ENUMERATED):
                    WINE_FIXME("X509_ENUMERATED\n");
                    break;
                case LOWORD(X509_CHOICE_OF_TIME):
                    WINE_TRACE("X509_CHOICE_OF_TIME - nothing to do.\n");
                    break;
                case LOWORD(X509_AUTHORITY_KEY_ID2):
                    WINE_FIXME("X509_AUTHORITY_KEY_ID2\n");
                    break;
                case LOWORD(X509_AUTHORITY_INFO_ACCESS):
                    WINE_FIXME("X509_AUTHORITY_INFO_ACCESS\n");
                    break;
                case LOWORD(PKCS_CONTENT_INFO):
                    WINE_FIXME("PKCS_CONTENT_INFO\n");
                    break;
                case LOWORD(X509_SEQUENCE_OF_ANY):
                    WINE_FIXME("X509_SEQUENCE_OF_ANY\n");
                    break;
                case LOWORD(PKCS_UTC_TIME):
                    WINE_FIXME("PKCS_UTC_TIME\n");
                    break;
                case LOWORD(X509_CRL_DIST_POINTS):
                    WINE_FIXME("X509_CRL_DIST_POINTS\n");
                    break;
                case LOWORD(X509_ENHANCED_KEY_USAGE):
                    WINE_FIXME("X509_ENHANCED_KEY_USAGE\n");
                    break;
                case LOWORD(PKCS_CTL):
                    WINE_FIXME("PKCS_CTL\n");
                    break;
                case LOWORD(PKCS_SMIME_CAPABILITIES):
                    WINE_FIXME("PKCS_SMIME_CAPABILITIES\n");
                    break;
                case LOWORD(X509_PKIX_POLICY_QUALIFIER_USERNOTICE):
                    WINE_FIXME("X509_PKIX_POLICY_QUALIFIER_USERNOTICE\n");
                    break;
                case LOWORD(PKCS_ATTRIBUTES):
                    WINE_FIXME("PKCS_ATTRIBUTES\n");
                    break;
                case LOWORD(X509_ISSUING_DIST_POINT):
                    WINE_FIXME("X509_ISSUING_DIST_POINT\n");
                    break;
                case LOWORD(X509_NAME_CONSTRAINTS):
                    WINE_FIXME("X509_NAME_CONSTRAINTS\n");
                    break;
                case LOWORD(X509_POLICY_MAPPINGS):
                    WINE_FIXME("X509_POLICY_MAPPINGS\n");
                    break;
                case LOWORD(X509_POLICY_CONSTRAINTS):
                    WINE_FIXME("X509_POLICY_CONSTRAINTS\n");
                    break;
                case LOWORD(PKCS7_SIGNER_INFO):
                    WINE_FIXME("Converting CMSG_SIGNER_INFO %p\n", QEMU_G2H(c->pvStructInfo));
                    CMSG_SIGNER_INFO_h2g(QEMU_G2H(c->pvStructInfo), QEMU_G2H(c->pvStructInfo));
                    break;
                case LOWORD(CMS_SIGNER_INFO):
                    WINE_TRACE("Converting CMSG_CMS_SIGNER_INFO %p\n", QEMU_G2H(c->pvStructInfo));
                    CMSG_CMS_SIGNER_INFO_h2g(QEMU_G2H(c->pvStructInfo), QEMU_G2H(c->pvStructInfo));
                    break;
                case LOWORD(X509_OBJECT_IDENTIFIER):
                    WINE_FIXME("X509_OBJECT_IDENTIFIER\n");
                    break;
                case LOWORD(X509_ECC_SIGNATURE):
                    WINE_FIXME("X509_ECC_SIGNATURE\n");
                    break;
                default:
                    WINE_FIXME("Unknown? %x\n", LOWORD(type));
                }
            }
            else if (!strcmp(type, SPC_INDIRECT_DATA_OBJID))
            {
                WINE_TRACE("Converting SIP_INDIRECT_DATA.\n");
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

