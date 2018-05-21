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
#include <wine/exception.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CertAddEncodedCertificateToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwCertEncodingType;
    uint64_t pbCertEncoded;
    uint64_t cbCertEncoded;
    uint64_t dwAddDisposition;
    uint64_t ppCertContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddEncodedCertificateToStore(HCERTSTORE hCertStore, DWORD dwCertEncodingType,
        const BYTE *pbCertEncoded, DWORD cbCertEncoded, DWORD dwAddDisposition, PCCERT_CONTEXT *ppCertContext)
{
    struct qemu_CertAddEncodedCertificateToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDENCODEDCERTIFICATETOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbCertEncoded = (ULONG_PTR)pbCertEncoded;
    call.cbCertEncoded = cbCertEncoded;
    call.dwAddDisposition = dwAddDisposition;
    call.ppCertContext = (ULONG_PTR)ppCertContext;

    qemu_syscall(&call.super);
    if (call.super.iret && ppCertContext)
        *ppCertContext = (PCCERT_CONTEXT)(ULONG_PTR)call.ppCertContext;

    return call.super.iret;
}

#else

void qemu_CertAddEncodedCertificateToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddEncodedCertificateToStore *c = (struct qemu_CertAddEncodedCertificateToStore *)call;
    const CERT_CONTEXT *context = NULL;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
    c->super.iret = CertAddEncodedCertificateToStore(cert_store_g2h(c->hCertStore), c->dwCertEncodingType,
            QEMU_G2H(c->pbCertEncoded), c->cbCertEncoded, c->dwAddDisposition, c->ppCertContext ? &context : NULL);

#if GUEST_BIT != HOST_BIT
    if (context)
        context = (CERT_CONTEXT *)context32_create(context);
#endif

    c->ppCertContext = QEMU_H2G(context);
}

#endif

struct qemu_CertAddEncodedCertificateToSystemStoreA
{
    struct qemu_syscall super;
    uint64_t pszCertStoreName;
    uint64_t pbCertEncoded;
    uint64_t cbCertEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddEncodedCertificateToSystemStoreA(LPCSTR pszCertStoreName, const BYTE *pbCertEncoded, DWORD cbCertEncoded)
{
    struct qemu_CertAddEncodedCertificateToSystemStoreA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDENCODEDCERTIFICATETOSYSTEMSTOREA);
    call.pszCertStoreName = (ULONG_PTR)pszCertStoreName;
    call.pbCertEncoded = (ULONG_PTR)pbCertEncoded;
    call.cbCertEncoded = cbCertEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddEncodedCertificateToSystemStoreA(struct qemu_syscall *call)
{
    struct qemu_CertAddEncodedCertificateToSystemStoreA *c = (struct qemu_CertAddEncodedCertificateToSystemStoreA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddEncodedCertificateToSystemStoreA(QEMU_G2H(c->pszCertStoreName), QEMU_G2H(c->pbCertEncoded), c->cbCertEncoded);
}

#endif

struct qemu_CertAddEncodedCertificateToSystemStoreW
{
    struct qemu_syscall super;
    uint64_t pszCertStoreName;
    uint64_t pbCertEncoded;
    uint64_t cbCertEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddEncodedCertificateToSystemStoreW(LPCWSTR pszCertStoreName, const BYTE *pbCertEncoded, DWORD cbCertEncoded)
{
    struct qemu_CertAddEncodedCertificateToSystemStoreW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDENCODEDCERTIFICATETOSYSTEMSTOREW);
    call.pszCertStoreName = (ULONG_PTR)pszCertStoreName;
    call.pbCertEncoded = (ULONG_PTR)pbCertEncoded;
    call.cbCertEncoded = cbCertEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddEncodedCertificateToSystemStoreW(struct qemu_syscall *call)
{
    struct qemu_CertAddEncodedCertificateToSystemStoreW *c = (struct qemu_CertAddEncodedCertificateToSystemStoreW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddEncodedCertificateToSystemStoreW(QEMU_G2H(c->pszCertStoreName), QEMU_G2H(c->pbCertEncoded), c->cbCertEncoded);
}

#endif

struct qemu_CertAddCertificateContextToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pCertContext;
    uint64_t dwAddDisposition;
    uint64_t ppStoreContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddCertificateContextToStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pCertContext,
        DWORD dwAddDisposition, PCCERT_CONTEXT *ppStoreContext)
{
    struct qemu_CertAddCertificateContextToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDCERTIFICATECONTEXTTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwAddDisposition = dwAddDisposition;
    call.ppStoreContext = (ULONG_PTR)ppStoreContext;

    qemu_syscall(&call.super);
    if (call.super.iret && ppStoreContext)
        *ppStoreContext = (const CERT_CONTEXT *)(ULONG_PTR)call.ppStoreContext;

    return call.super.iret;
}

#else

void qemu_CertAddCertificateContextToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddCertificateContextToStore *c = (struct qemu_CertAddCertificateContextToStore *)call;
    const CERT_CONTEXT *context = NULL;
    struct qemu_cert_context *cert_in;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = CertAddCertificateContextToStore(cert_store_g2h(c->hCertStore), QEMU_G2H(c->pCertContext),
            c->dwAddDisposition, c->ppStoreContext ? &context : NULL);
    c->ppStoreContext = QEMU_H2G(context);
    return;
#endif

    cert_in = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    c->super.iret = CertAddCertificateContextToStore(cert_store_g2h(c->hCertStore), cert_in ? cert_in->cert64 : NULL,
            c->dwAddDisposition, c->ppStoreContext ? &context : NULL);

    if (context)
        context = (CERT_CONTEXT *)context32_create(context);

    c->ppStoreContext = QEMU_H2G(context);
}

#endif

struct qemu_CertAddCertificateLinkToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pCertContext;
    uint64_t dwAddDisposition;
    uint64_t ppCertContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddCertificateLinkToStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pCertContext,
        DWORD dwAddDisposition, PCCERT_CONTEXT *ppCertContext)
{
    struct qemu_CertAddCertificateLinkToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDCERTIFICATELINKTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwAddDisposition = dwAddDisposition;
    call.ppCertContext = (ULONG_PTR)ppCertContext;

    qemu_syscall(&call.super);
    if (call.super.iret && ppCertContext)
        *ppCertContext = (const CERT_CONTEXT *)(ULONG_PTR)call.ppCertContext;

    return call.super.iret;
}

#else

void qemu_CertAddCertificateLinkToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddCertificateLinkToStore *c = (struct qemu_CertAddCertificateLinkToStore *)call;
    const CERT_CONTEXT *cert_in, *cert_out = NULL;
    struct qemu_cert_context *cert32, *cert_out32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    cert_in = QEMU_G2H(c->pCertContext);
#else
    cert32 = QEMU_G2H(c->pCertContext);
    cert_in = cert32 ? cert32->cert64 : NULL;
#endif

    c->super.iret = CertAddCertificateLinkToStore(cert_store_g2h(c->hCertStore), cert_in,
            c->dwAddDisposition, c->ppCertContext ? &cert_out : NULL);

#if GUEST_BIT != HOST_BIT
    if (cert_out)
    {
        cert_out32 = context32_create(cert_out);
        if (cert_out->pCertInfo == cert_in->pCertInfo)
            cert_out32->cert32.pCertInfo = cert32->cert32.pCertInfo;

        cert_out = (CERT_CONTEXT *)cert_out32;
    }
#endif

    c->ppCertContext = QEMU_H2G(cert_out);
}

#endif

struct qemu_CertCreateCertificateContext
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pbCertEncoded;
    uint64_t cbCertEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertCreateCertificateContext(DWORD dwCertEncodingType, const BYTE *pbCertEncoded,
        DWORD cbCertEncoded)
{
    struct qemu_CertCreateCertificateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATECERTIFICATECONTEXT);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbCertEncoded = (ULONG_PTR)pbCertEncoded;
    call.cbCertEncoded = cbCertEncoded;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertCreateCertificateContext(struct qemu_syscall *call)
{
    struct qemu_CertCreateCertificateContext *c = (struct qemu_CertCreateCertificateContext *)call;
    const CERT_CONTEXT *context;

    WINE_TRACE("\n");
    context = CertCreateCertificateContext(c->dwCertEncodingType, QEMU_G2H(c->pbCertEncoded), c->cbCertEncoded);

#if GUEST_BIT != HOST_BIT
    if (context)
        context = (CERT_CONTEXT *)context32_create(context);
#endif
    c->super.iret = QEMU_H2G(context);
}

#endif

struct qemu_CertDuplicateCertificateContext
{
    struct qemu_syscall super;
    uint64_t pCertContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertDuplicateCertificateContext(PCCERT_CONTEXT pCertContext)
{
    struct qemu_CertDuplicateCertificateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDUPLICATECERTIFICATECONTEXT);
    call.pCertContext = (ULONG_PTR)pCertContext;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertDuplicateCertificateContext(struct qemu_syscall *call)
{
    struct qemu_CertDuplicateCertificateContext *c = (struct qemu_CertDuplicateCertificateContext *)call;
    struct qemu_cert_context *context32;
    const CERT_CONTEXT *context64;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = QEMU_H2G(CertDuplicateCertificateContext(QEMU_G2H(c->pCertContext)));
    return;
#endif

    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    if (!context32)
    {
        c->super.iret = QEMU_H2G(CertDuplicateCertificateContext(NULL));
        return;
    }

    context64 = CertDuplicateCertificateContext(context32->cert64);
    if (context64 != context32->cert64)
        WINE_FIXME("Unexpected host library behavior.\n");
    InterlockedIncrement(&context32->ref);

    c->super.iret = QEMU_H2G(&context32->cert32);
}

#endif

struct qemu_CertFreeCertificateContext
{
    struct qemu_syscall super;
    uint64_t pCertContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertFreeCertificateContext(PCCERT_CONTEXT pCertContext)
{
    struct qemu_CertFreeCertificateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFREECERTIFICATECONTEXT);
    call.pCertContext = (ULONG_PTR)pCertContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertFreeCertificateContext(struct qemu_syscall *call)
{
    struct qemu_CertFreeCertificateContext *c = (struct qemu_CertFreeCertificateContext *)call;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = CertFreeCertificateContext(QEMU_G2H(c->pCertContext));
    return;
#endif

    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    if (!context32)
    {
        c->super.iret = CertFreeCertificateContext(NULL);
        return;
    }

    c->super.iret = CertFreeCertificateContext(context32->cert64);
    context32_decref(context32);
}

#endif

struct qemu_CertEnumCertificateContextProperties
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwPropId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertEnumCertificateContextProperties(PCCERT_CONTEXT pCertContext, DWORD dwPropId)
{
    struct qemu_CertEnumCertificateContextProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMCERTIFICATECONTEXTPROPERTIES);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwPropId = dwPropId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertEnumCertificateContextProperties(struct qemu_syscall *call)
{
    struct qemu_CertEnumCertificateContextProperties *c = (struct qemu_CertEnumCertificateContextProperties *)call;
    const CERT_CONTEXT *context;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    context = QEMU_G2H(c->pCertContext);
#else
    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    context = context32 ? context32->cert64 : NULL;
#endif
    c->super.iret = CertEnumCertificateContextProperties(context, c->dwPropId);
}

#endif

struct qemu_CertGetCertificateContextProperty
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwPropId;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetCertificateContextProperty(PCCERT_CONTEXT pCertContext, DWORD dwPropId, void *pvData, DWORD *pcbData)
{
    struct qemu_CertGetCertificateContextProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETCERTIFICATECONTEXTPROPERTY);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwPropId = dwPropId;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetCertificateContextProperty(struct qemu_syscall *call)
{
    struct qemu_CertGetCertificateContextProperty *c = (struct qemu_CertGetCertificateContextProperty *)call;
    const CERT_CONTEXT *context;
    struct qemu_cert_context *context32;
    DWORD property;
    void *data;
    DWORD *size, my_size = 0;
    CERT_KEY_CONTEXT key_ctx;
    HANDLE handle;

    WINE_TRACE("\n");
    property = c->dwPropId;
    data = QEMU_G2H(c->pvData);
    size = QEMU_G2H(c->pcbData);

#if GUEST_BIT == HOST_BIT
    context = QEMU_G2H(c->pCertContext);
#else
    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    context = context32 ? context32->cert64 : NULL;

    switch (c->dwPropId)
    {
        case CERT_KEY_PROV_HANDLE_PROP_ID:
            if (data)
                data = &handle;
            if (size)
            {
                if (*size == sizeof(qemu_ptr))
                    my_size = sizeof(handle);
                *size = sizeof(qemu_ptr);
                size = &my_size;
            }
            break;

        case CERT_KEY_CONTEXT_PROP_ID:
            if (data)
                data = &key_ctx;
            if (size)
            {
                if (*size == sizeof(struct qemu_CERT_KEY_CONTEXT))
                    my_size = sizeof(key_ctx);
                *size = sizeof(key_ctx);
                size = &my_size;
            }
            break;

        case CERT_SHA1_HASH_PROP_ID: /* Apparently fixed size */
        case CERT_MD5_HASH_PROP_ID: /* Apparently fixed size */
        case CERT_ACCESS_STATE_PROP_ID: /* DWORD */
        case CERT_SIGNATURE_HASH_PROP_ID: /* Apparently fixed size */
        case CERT_ARCHIVED_PROP_ID: /* No data */
        case CERT_KEY_IDENTIFIER_PROP_ID: /* Dynamic size */
        case CERT_KEY_PROV_INFO_PROP_ID: /* Dynamic size */
            break;

        default:
            WINE_FIXME("Unchecked property %u.\n", property);
    }
#endif

    c->super.iret = CertGetCertificateContextProperty(context, property, data, size);

    /* FIXME: Report the correct size */
#if GUEST_BIT != HOST_BIT
    if (!c->super.iret)
        return;

    if (data)
    {
        switch (c->dwPropId)
        {
            case CERT_KEY_PROV_HANDLE_PROP_ID:
                *((qemu_ptr *)data) = QEMU_H2G(handle);
                break;

            case CERT_KEY_CONTEXT_PROP_ID:
                CERT_KEY_CONTEXT_h2g(data, &key_ctx);
                break;

            case CERT_KEY_PROV_INFO_PROP_ID:
                WINE_WARN("Leaving a hole in the struct.\n");
                CRYPT_KEY_PROV_INFO_h2g(data, data);
                break;
        }
    }
#endif
}

#endif

struct qemu_CertSetCertificateContextProperty
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwPropId;
    uint64_t dwFlags;
    uint64_t pvData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSetCertificateContextProperty(PCCERT_CONTEXT pCertContext, DWORD dwPropId, DWORD dwFlags,
        const void *pvData)
{
    struct qemu_CertSetCertificateContextProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSETCERTIFICATECONTEXTPROPERTY);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwPropId = dwPropId;
    call.dwFlags = dwFlags;
    call.pvData = (ULONG_PTR)pvData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSetCertificateContextProperty(struct qemu_syscall *call)
{
    struct qemu_CertSetCertificateContextProperty *c = (struct qemu_CertSetCertificateContextProperty *)call;
    struct qemu_cert_context *context32;
    CRYPT_DATA_BLOB stack, *blob = &stack;
    CERT_KEY_CONTEXT key_ctx;
    struct qemu_CERT_KEY_CONTEXT *key_ctx32;
    void *data;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = CertSetCertificateContextProperty(QEMU_G2H(c->pCertContext), c->dwPropId, c->dwFlags,
            QEMU_G2H(c->pvData));
    return;
#endif

    data = QEMU_G2H(c->pvData);
    if (data)
    {
        switch (c->dwPropId)
        {
            case CERT_HASH_PROP_ID:
                CRYPT_DATA_BLOB_g2h(blob, data);
                data = blob;
                break;

            case CERT_KEY_CONTEXT_PROP_ID:
                key_ctx32 = data;
                if (key_ctx32->cbSize == sizeof(*key_ctx32))
                    CERT_KEY_CONTEXT_g2h(&key_ctx, data);
                else
                    key_ctx.cbSize = 0;
                data = &key_ctx;
                break;

            default:
                WINE_FIXME("Unknown prop id %x.\n", (DWORD)c->dwPropId);
        }
    }

    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    c->super.iret = CertSetCertificateContextProperty(context32 ? context32->cert64 : NULL, c->dwPropId, c->dwFlags,
            data);
}

#endif

struct qemu_CryptAcquireCertificatePrivateKey
{
    struct qemu_syscall super;
    uint64_t pCert;
    uint64_t dwFlags;
    uint64_t pvReserved;
    uint64_t phCryptProv;
    uint64_t pdwKeySpec;
    uint64_t pfCallerFreeProv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptAcquireCertificatePrivateKey(PCCERT_CONTEXT pCert, DWORD dwFlags, void *pvReserved, HCRYPTPROV_OR_NCRYPT_KEY_HANDLE *phCryptProv, DWORD *pdwKeySpec, BOOL *pfCallerFreeProv)
{
    struct qemu_CryptAcquireCertificatePrivateKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTACQUIRECERTIFICATEPRIVATEKEY);
    call.pCert = (ULONG_PTR)pCert;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.phCryptProv = (ULONG_PTR)phCryptProv;
    call.pdwKeySpec = (ULONG_PTR)pdwKeySpec;
    call.pfCallerFreeProv = (ULONG_PTR)pfCallerFreeProv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptAcquireCertificatePrivateKey(struct qemu_syscall *call)
{
    struct qemu_CryptAcquireCertificatePrivateKey *c = (struct qemu_CryptAcquireCertificatePrivateKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptAcquireCertificatePrivateKey(QEMU_G2H(c->pCert), c->dwFlags, QEMU_G2H(c->pvReserved), QEMU_G2H(c->phCryptProv), QEMU_G2H(c->pdwKeySpec), QEMU_G2H(c->pfCallerFreeProv));
}

#endif

struct qemu_CryptFindCertificateKeyProvInfo
{
    struct qemu_syscall super;
    uint64_t pCert;
    uint64_t dwFlags;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptFindCertificateKeyProvInfo(PCCERT_CONTEXT pCert, DWORD dwFlags, void *pvReserved)
{
    struct qemu_CryptFindCertificateKeyProvInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTFINDCERTIFICATEKEYPROVINFO);
    call.pCert = (ULONG_PTR)pCert;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptFindCertificateKeyProvInfo(struct qemu_syscall *call)
{
    struct qemu_CryptFindCertificateKeyProvInfo *c = (struct qemu_CryptFindCertificateKeyProvInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptFindCertificateKeyProvInfo(QEMU_G2H(c->pCert), c->dwFlags, QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CertCompareCertificate
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pCertId1;
    uint64_t pCertId2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertCompareCertificate(DWORD dwCertEncodingType, PCERT_INFO pCertId1, PCERT_INFO pCertId2)
{
    struct qemu_CertCompareCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCOMPARECERTIFICATE);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pCertId1 = (ULONG_PTR)pCertId1;
    call.pCertId2 = (ULONG_PTR)pCertId2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertCompareCertificate(struct qemu_syscall *call)
{
    struct qemu_CertCompareCertificate *c = (struct qemu_CertCompareCertificate *)call;
    CERT_INFO s1, *info1 = &s1;
    CERT_INFO s2, *info2 = &s2;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info1 = QEMU_G2H(c->pCertId1);
    info2 = QEMU_G2H(c->pCertId2);
#else
    if (c->pCertId1)
    {
        CERT_INFO_g2h(info1, QEMU_G2H(c->pCertId1));
        if (info1->cExtension && info1->rgExtension)
            WINE_FIXME("Extension not handled\n");
    }
    else
    {
        info1 = NULL;
    }

    if (c->pCertId2)
    {
        CERT_INFO_g2h(info2, QEMU_G2H(c->pCertId2));
        if (info2->cExtension && info2->rgExtension)
            WINE_FIXME("Extension not handled\n");
    }
    else
    {
        info2 = NULL;
    }
#endif

    c->super.iret = CertCompareCertificate(c->dwCertEncodingType, info1, info2);
}

#endif

struct qemu_CertCompareCertificateName
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pCertName1;
    uint64_t pCertName2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertCompareCertificateName(DWORD dwCertEncodingType, PCERT_NAME_BLOB pCertName1,
        PCERT_NAME_BLOB pCertName2)
{
    struct qemu_CertCompareCertificateName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCOMPARECERTIFICATENAME);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pCertName1 = (ULONG_PTR)pCertName1;
    call.pCertName2 = (ULONG_PTR)pCertName2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertCompareCertificateName(struct qemu_syscall *call)
{
    struct qemu_CertCompareCertificateName *c = (struct qemu_CertCompareCertificateName *)call;
    CERT_NAME_BLOB stack1, stack2, *name1 = &stack1, *name2 = &stack2;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    name1 = QEMU_G2H(c->pCertName1);
    name2 = QEMU_G2H(c->pCertName2);
#else
    if (c->pCertName1)
        CRYPT_DATA_BLOB_g2h(name1, QEMU_G2H(c->pCertName1));
    else
        name1 = NULL;

    if (c->pCertName2)
        CRYPT_DATA_BLOB_g2h(name2, QEMU_G2H(c->pCertName2));
    else
        name2 = NULL;
#endif

    c->super.iret = CertCompareCertificateName(c->dwCertEncodingType, name1, name2);
}

#endif

struct qemu_CertCompareIntegerBlob
{
    struct qemu_syscall super;
    uint64_t pInt1;
    uint64_t pInt2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertCompareIntegerBlob(PCRYPT_INTEGER_BLOB pInt1, PCRYPT_INTEGER_BLOB pInt2)
{
    struct qemu_CertCompareIntegerBlob call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCOMPAREINTEGERBLOB);
    call.pInt1 = (ULONG_PTR)pInt1;
    call.pInt2 = (ULONG_PTR)pInt2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertCompareIntegerBlob(struct qemu_syscall *call)
{
    struct qemu_CertCompareIntegerBlob *c = (struct qemu_CertCompareIntegerBlob *)call;
    CRYPT_INTEGER_BLOB stack1, stack2, *int1 = &stack1, *int2 = &stack2;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    int1 = QEMU_G2H(c->pInt1);
    int2 = QEMU_G2H(c->pInt2);
#else
    if (c->pInt1)
        CRYPT_DATA_BLOB_g2h(int1, QEMU_G2H(c->pInt1));
    else
        int1 = NULL;

    if (c->pInt2)
        CRYPT_DATA_BLOB_g2h(int2, QEMU_G2H(c->pInt2));
    else
        int2 = NULL;
#endif

    c->super.iret = CertCompareIntegerBlob(int1, int2);
}

#endif

struct qemu_CertComparePublicKeyInfo
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pPublicKey1;
    uint64_t pPublicKey2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertComparePublicKeyInfo(DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pPublicKey1, PCERT_PUBLIC_KEY_INFO pPublicKey2)
{
    struct qemu_CertComparePublicKeyInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCOMPAREPUBLICKEYINFO);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pPublicKey1 = (ULONG_PTR)pPublicKey1;
    call.pPublicKey2 = (ULONG_PTR)pPublicKey2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertComparePublicKeyInfo(struct qemu_syscall *call)
{
    struct qemu_CertComparePublicKeyInfo *c = (struct qemu_CertComparePublicKeyInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertComparePublicKeyInfo(c->dwCertEncodingType, QEMU_G2H(c->pPublicKey1), QEMU_G2H(c->pPublicKey2));
}

#endif

struct qemu_CertGetPublicKeyLength
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pPublicKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertGetPublicKeyLength(DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pPublicKey)
{
    struct qemu_CertGetPublicKeyLength call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETPUBLICKEYLENGTH);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pPublicKey = (ULONG_PTR)pPublicKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetPublicKeyLength(struct qemu_syscall *call)
{
    struct qemu_CertGetPublicKeyLength *c = (struct qemu_CertGetPublicKeyLength *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetPublicKeyLength(c->dwCertEncodingType, QEMU_G2H(c->pPublicKey));
}

#endif

struct qemu_CertFindCertificateInStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwCertEncodingType;
    uint64_t dwFlags;
    uint64_t dwType;
    uint64_t pvPara;
    uint64_t pPrevCertContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertFindCertificateInStore(HCERTSTORE hCertStore, DWORD dwCertEncodingType,
        DWORD dwFlags, DWORD dwType, const void *pvPara, PCCERT_CONTEXT pPrevCertContext)
{
    struct qemu_CertFindCertificateInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDCERTIFICATEINSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwCertEncodingType = dwCertEncodingType;
    call.dwFlags = dwFlags;
    call.dwType = dwType;
    call.pvPara = (ULONG_PTR)pvPara;
    call.pPrevCertContext = (ULONG_PTR)pPrevCertContext;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindCertificateInStore(struct qemu_syscall *call)
{
    struct qemu_CertFindCertificateInStore *c = (struct qemu_CertFindCertificateInStore *)call;
    const void *param;
    DWORD type;
    CRYPT_DATA_BLOB blob;
    CERT_INFO ci;
    const CERT_CONTEXT *context;
    struct qemu_cert_context *context32, *compare32;

    WINE_TRACE("\n");

    type = c->dwType;
    param = QEMU_G2H(c->pvPara);
#if GUEST_BIT == HOST_BIT
    context = QEMU_G2H(c->pPrevCertContext);
#else
    context32 = QEMU_G2H(c->pPrevCertContext);
    context = context32 ? context32->cert64 : NULL;

    if (param)
    {
        switch (type >> CERT_COMPARE_SHIFT)
        {
            case CERT_COMPARE_ANY: /* param ignored or a simple type */
            case CERT_COMPARE_NAME_STR_A:
            case CERT_COMPARE_NAME_STR_W:
                break;

            case CERT_COMPARE_MD5_HASH:
            case CERT_COMPARE_SHA1_HASH:
            case CERT_COMPARE_NAME:
            case CERT_COMPARE_SIGNATURE_HASH:
                CRYPT_DATA_BLOB_g2h(&blob, param);
                param = &blob;
                break;

            case CERT_COMPARE_PUBLIC_KEY:
                WINE_FIXME("CERT_COMPARE_PUBLIC_KEY conversion not implemented\n");
                break;

            case CERT_COMPARE_SUBJECT_CERT:
                CERT_INFO_g2h(&ci, param);
                param = &ci;
                break;

            case CERT_COMPARE_CERT_ID:
                WINE_FIXME("CERT_ID conversion not implemented\n");
                break;

            case CERT_COMPARE_ISSUER_OF:
            case CERT_COMPARE_EXISTING:
                context32 = QEMU_G2H(param);
                param = context32->cert64;
                break;

            default:
                WINE_FIXME("Unknown compare type %x\n", type);
                break;
        }
    }
#endif

    context = CertFindCertificateInStore(cert_store_g2h(c->hCertStore), c->dwCertEncodingType,
            c->dwFlags, type, param, context);

#if GUEST_BIT != HOST_BIT
    if (context)
        context = (CERT_CONTEXT *)context32_create(context);
#endif

    c->super.iret = QEMU_H2G(context);
}

#endif

struct qemu_CertGetSubjectCertificateFromStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwCertEncodingType;
    uint64_t pCertId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertGetSubjectCertificateFromStore(HCERTSTORE hCertStore, DWORD dwCertEncodingType,
        PCERT_INFO pCertId)
{
    struct qemu_CertGetSubjectCertificateFromStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETSUBJECTCERTIFICATEFROMSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pCertId = (ULONG_PTR)pCertId;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertGetSubjectCertificateFromStore(struct qemu_syscall *call)
{
    struct qemu_CertGetSubjectCertificateFromStore *c = (struct qemu_CertGetSubjectCertificateFromStore *)call;
    CERT_INFO stack, *info = &stack;
    const CERT_CONTEXT *context;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->pCertId);
#else
    if (c->pCertId)
        CERT_INFO_g2h(info, QEMU_G2H(c->pCertId));
    else
        info = NULL;
#endif

    context = CertGetSubjectCertificateFromStore(cert_store_g2h(c->hCertStore), c->dwCertEncodingType, info);

#if GUEST_BIT != HOST_BIT
    if (context)
        context = (CERT_CONTEXT *)context32_create(context);
#endif

    c->super.iret = QEMU_H2G(context);
}

#endif

struct qemu_CertVerifySubjectCertificateContext
{
    struct qemu_syscall super;
    uint64_t pSubject;
    uint64_t pIssuer;
    uint64_t pdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertVerifySubjectCertificateContext(PCCERT_CONTEXT pSubject, PCCERT_CONTEXT pIssuer, DWORD *pdwFlags)
{
    struct qemu_CertVerifySubjectCertificateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYSUBJECTCERTIFICATECONTEXT);
    call.pSubject = (ULONG_PTR)pSubject;
    call.pIssuer = (ULONG_PTR)pIssuer;
    call.pdwFlags = (ULONG_PTR)pdwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifySubjectCertificateContext(struct qemu_syscall *call)
{
    struct qemu_CertVerifySubjectCertificateContext *c = (struct qemu_CertVerifySubjectCertificateContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifySubjectCertificateContext(QEMU_G2H(c->pSubject), QEMU_G2H(c->pIssuer), QEMU_G2H(c->pdwFlags));
}

#endif

struct qemu_CertGetIssuerCertificateFromStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pSubjectContext;
    uint64_t pPrevIssuerContext;
    uint64_t pdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertGetIssuerCertificateFromStore(HCERTSTORE hCertStore,
        PCCERT_CONTEXT pSubjectContext, PCCERT_CONTEXT pPrevIssuerContext, DWORD *pdwFlags)
{
    struct qemu_CertGetIssuerCertificateFromStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETISSUERCERTIFICATEFROMSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pSubjectContext = (ULONG_PTR)pSubjectContext;
    call.pPrevIssuerContext = (ULONG_PTR)pPrevIssuerContext;
    call.pdwFlags = (ULONG_PTR)pdwFlags;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertGetIssuerCertificateFromStore(struct qemu_syscall *call)
{
    struct qemu_CertGetIssuerCertificateFromStore *c = (struct qemu_CertGetIssuerCertificateFromStore *)call;
    const CERT_CONTEXT *context, stack1, *subject = &stack1, stack2, *issuer = &stack2;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    subject = QEMU_G2H(c->pSubjectContext);
    issuer = QEMU_G2H(c->pPrevIssuerContext);
#else
    context32 = context_impl_from_context32(QEMU_G2H(c->pSubjectContext));
    subject = context32 ? context32->cert64 : NULL;
    context32 = context_impl_from_context32(QEMU_G2H(c->pPrevIssuerContext));
    issuer = context32 ? context32->cert64 : NULL;
#endif

    context = CertGetIssuerCertificateFromStore(cert_store_g2h(c->hCertStore), subject, issuer, QEMU_G2H(c->pdwFlags));

#if GUEST_BIT != HOST_BIT
    if (context)
        context = (CERT_CONTEXT *)context32_create(context);
#endif

    c->super.iret = QEMU_H2G(context);
}

#endif

struct qemu_CertVerifyRevocation
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t dwRevType;
    uint64_t cContext;
    uint64_t rgpvContext;
    uint64_t dwFlags;
    uint64_t pRevPara;
    uint64_t pRevStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI CertVerifyRevocation(DWORD dwEncodingType, DWORD dwRevType, DWORD cContext,
        PVOID rgpvContext[], DWORD dwFlags, PCERT_REVOCATION_PARA pRevPara, PCERT_REVOCATION_STATUS pRevStatus)
{
    struct qemu_CertVerifyRevocation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYREVOCATION);
    call.dwEncodingType = dwEncodingType;
    call.dwRevType = dwRevType;
    call.cContext = cContext;
    call.rgpvContext = (ULONG_PTR)rgpvContext;
    call.dwFlags = dwFlags;
    call.pRevPara = (ULONG_PTR)pRevPara;
    call.pRevStatus = (ULONG_PTR)pRevStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyRevocation(struct qemu_syscall *call)
{
    struct qemu_CertVerifyRevocation *c = (struct qemu_CertVerifyRevocation *)call;
    const CERT_CONTEXT **certs = NULL;
    struct qemu_cert_context *context32;
    qemu_ptr *certs32;
    DWORD count, i;

    WINE_FIXME("unfinished\n");
    count = c->cContext;

#if GUEST_BIT == HOST_BIT
    certs = QEMU_G2H(c->rgpvContext);
#else
    /* FIXME: Is it always an array of contexts? The actual implementation looks up DLLs in the registry... */
    certs32 = QEMU_G2H(c->rgpvContext);
    if (certs32)
    {
        certs = HeapAlloc(GetProcessHeap(), 0, sizeof(*certs) * count);
        if (!certs)
            WINE_ERR("Out of memory\n");

        for (i = 0; i < count; ++i)
        {
            context32 = context_impl_from_context32((uint64_t)certs32[i]);
            certs[i] = context32 ? context32->cert64 : NULL;
        }
    }
#endif

    c->super.iret = CertVerifyRevocation(c->dwEncodingType, c->dwRevType, count, (void **)certs,
            c->dwFlags, QEMU_G2H(c->pRevPara), QEMU_G2H(c->pRevStatus));

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, certs);
#endif
}

#endif

struct qemu_CertFindAttribute
{
    struct qemu_syscall super;
    uint64_t pszObjId;
    uint64_t cAttr;
    uint64_t rgAttr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCRYPT_ATTRIBUTE WINAPI CertFindAttribute(LPCSTR pszObjId, DWORD cAttr, CRYPT_ATTRIBUTE rgAttr[])
{
    struct qemu_CertFindAttribute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDATTRIBUTE);
    call.pszObjId = (ULONG_PTR)pszObjId;
    call.cAttr = cAttr;
    call.rgAttr = (ULONG_PTR)rgAttr;

    qemu_syscall(&call.super);

    return (PCRYPT_ATTRIBUTE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindAttribute(struct qemu_syscall *call)
{
    struct qemu_CertFindAttribute *c = (struct qemu_CertFindAttribute *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindAttribute(QEMU_G2H(c->pszObjId), c->cAttr, QEMU_G2H(c->rgAttr)));
}

#endif

struct qemu_CertFindExtension
{
    struct qemu_syscall super;
    uint64_t pszObjId;
    uint64_t cExtensions;
    uint64_t rgExtensions;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCERT_EXTENSION WINAPI CertFindExtension(LPCSTR pszObjId, DWORD cExtensions, CERT_EXTENSION rgExtensions[])
{
    struct qemu_CertFindExtension call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDEXTENSION);
    call.pszObjId = (ULONG_PTR)pszObjId;
    call.cExtensions = cExtensions;
    call.rgExtensions = (ULONG_PTR)rgExtensions;

    qemu_syscall(&call.super);

    return (PCERT_EXTENSION)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindExtension(struct qemu_syscall *call)
{
    struct qemu_CertFindExtension *c = (struct qemu_CertFindExtension *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindExtension(QEMU_G2H(c->pszObjId), c->cExtensions, QEMU_G2H(c->rgExtensions)));
}

#endif

struct qemu_CertFindRDNAttr
{
    struct qemu_syscall super;
    uint64_t pszObjId;
    uint64_t pName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCERT_RDN_ATTR WINAPI CertFindRDNAttr(LPCSTR pszObjId, PCERT_NAME_INFO pName)
{
    struct qemu_CertFindRDNAttr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDRDNATTR);
    call.pszObjId = (ULONG_PTR)pszObjId;
    call.pName = (ULONG_PTR)pName;

    qemu_syscall(&call.super);

    return (PCERT_RDN_ATTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindRDNAttr(struct qemu_syscall *call)
{
    struct qemu_CertFindRDNAttr *c = (struct qemu_CertFindRDNAttr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindRDNAttr(QEMU_G2H(c->pszObjId), QEMU_G2H(c->pName)));
}

#endif

struct qemu_CertIsRDNAttrsInCertificateName
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t dwFlags;
    uint64_t pCertName;
    uint64_t pRDN;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertIsRDNAttrsInCertificateName(DWORD dwCertEncodingType, DWORD dwFlags, PCERT_NAME_BLOB pCertName, PCERT_RDN pRDN)
{
    struct qemu_CertIsRDNAttrsInCertificateName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTISRDNATTRSINCERTIFICATENAME);
    call.dwCertEncodingType = dwCertEncodingType;
    call.dwFlags = dwFlags;
    call.pCertName = (ULONG_PTR)pCertName;
    call.pRDN = (ULONG_PTR)pRDN;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertIsRDNAttrsInCertificateName(struct qemu_syscall *call)
{
    struct qemu_CertIsRDNAttrsInCertificateName *c = (struct qemu_CertIsRDNAttrsInCertificateName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertIsRDNAttrsInCertificateName(c->dwCertEncodingType, c->dwFlags, QEMU_G2H(c->pCertName), QEMU_G2H(c->pRDN));
}

#endif

struct qemu_CertVerifyTimeValidity
{
    struct qemu_syscall super;
    uint64_t pTimeToVerify;
    uint64_t pCertInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI CertVerifyTimeValidity(LPFILETIME pTimeToVerify, PCERT_INFO pCertInfo)
{
    struct qemu_CertVerifyTimeValidity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYTIMEVALIDITY);
    call.pTimeToVerify = (ULONG_PTR)pTimeToVerify;
    call.pCertInfo = (ULONG_PTR)pCertInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyTimeValidity(struct qemu_syscall *call)
{
    struct qemu_CertVerifyTimeValidity *c = (struct qemu_CertVerifyTimeValidity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifyTimeValidity(QEMU_G2H(c->pTimeToVerify), QEMU_G2H(c->pCertInfo));
}

#endif

struct qemu_CertVerifyValidityNesting
{
    struct qemu_syscall super;
    uint64_t pSubjectInfo;
    uint64_t pIssuerInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertVerifyValidityNesting(PCERT_INFO pSubjectInfo, PCERT_INFO pIssuerInfo)
{
    struct qemu_CertVerifyValidityNesting call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYVALIDITYNESTING);
    call.pSubjectInfo = (ULONG_PTR)pSubjectInfo;
    call.pIssuerInfo = (ULONG_PTR)pIssuerInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyValidityNesting(struct qemu_syscall *call)
{
    struct qemu_CertVerifyValidityNesting *c = (struct qemu_CertVerifyValidityNesting *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifyValidityNesting(QEMU_G2H(c->pSubjectInfo), QEMU_G2H(c->pIssuerInfo));
}

#endif

struct qemu_CryptHashCertificate
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t Algid;
    uint64_t dwFlags;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t pbComputedHash;
    uint64_t pcbComputedHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptHashCertificate(HCRYPTPROV_LEGACY hCryptProv, ALG_ID Algid, DWORD dwFlags,
        const BYTE *pbEncoded, DWORD cbEncoded, BYTE *pbComputedHash, DWORD *pcbComputedHash)
{
    struct qemu_CryptHashCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTHASHCERTIFICATE);
    call.hCryptProv = hCryptProv;
    call.Algid = Algid;
    call.dwFlags = dwFlags;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.pbComputedHash = (ULONG_PTR)pbComputedHash;
    call.pcbComputedHash = (ULONG_PTR)pcbComputedHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptHashCertificate(struct qemu_syscall *call)
{
    struct qemu_CryptHashCertificate *c = (struct qemu_CryptHashCertificate *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptHashCertificate(c->hCryptProv, c->Algid, c->dwFlags, QEMU_G2H(c->pbEncoded), c->cbEncoded,
            QEMU_G2H(c->pbComputedHash), QEMU_G2H(c->pcbComputedHash));
}

#endif

struct qemu_CryptHashPublicKeyInfo
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t Algid;
    uint64_t dwFlags;
    uint64_t dwCertEncodingType;
    uint64_t pInfo;
    uint64_t pbComputedHash;
    uint64_t pcbComputedHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptHashPublicKeyInfo(HCRYPTPROV_LEGACY hCryptProv, ALG_ID Algid, DWORD dwFlags, DWORD dwCertEncodingType, PCERT_PUBLIC_KEY_INFO pInfo, BYTE *pbComputedHash, DWORD *pcbComputedHash)
{
    struct qemu_CryptHashPublicKeyInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTHASHPUBLICKEYINFO);
    call.hCryptProv = hCryptProv;
    call.Algid = Algid;
    call.dwFlags = dwFlags;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pInfo = (ULONG_PTR)pInfo;
    call.pbComputedHash = (ULONG_PTR)pbComputedHash;
    call.pcbComputedHash = (ULONG_PTR)pcbComputedHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptHashPublicKeyInfo(struct qemu_syscall *call)
{
    struct qemu_CryptHashPublicKeyInfo *c = (struct qemu_CryptHashPublicKeyInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptHashPublicKeyInfo(c->hCryptProv, c->Algid, c->dwFlags, c->dwCertEncodingType, QEMU_G2H(c->pInfo), QEMU_G2H(c->pbComputedHash), QEMU_G2H(c->pcbComputedHash));
}

#endif

struct qemu_CryptHashToBeSigned
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwCertEncodingType;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t pbComputedHash;
    uint64_t pcbComputedHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptHashToBeSigned(HCRYPTPROV_LEGACY hCryptProv, DWORD dwCertEncodingType, const BYTE *pbEncoded, DWORD cbEncoded, BYTE *pbComputedHash, DWORD *pcbComputedHash)
{
    struct qemu_CryptHashToBeSigned call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTHASHTOBESIGNED);
    call.hCryptProv = hCryptProv;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.pbComputedHash = (ULONG_PTR)pbComputedHash;
    call.pcbComputedHash = (ULONG_PTR)pcbComputedHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptHashToBeSigned(struct qemu_syscall *call)
{
    struct qemu_CryptHashToBeSigned *c = (struct qemu_CryptHashToBeSigned *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptHashToBeSigned(c->hCryptProv, c->dwCertEncodingType, QEMU_G2H(c->pbEncoded), c->cbEncoded, QEMU_G2H(c->pbComputedHash), QEMU_G2H(c->pcbComputedHash));
}

#endif

struct qemu_CryptSignCertificate
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwKeySpec;
    uint64_t dwCertEncodingType;
    uint64_t pbEncodedToBeSigned;
    uint64_t cbEncodedToBeSigned;
    uint64_t pSignatureAlgorithm;
    uint64_t pvHashAuxInfo;
    uint64_t pbSignature;
    uint64_t pcbSignature;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSignCertificate(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hCryptProv, DWORD dwKeySpec,
        DWORD dwCertEncodingType, const BYTE *pbEncodedToBeSigned, DWORD cbEncodedToBeSigned,
        PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm, const void *pvHashAuxInfo, BYTE *pbSignature,
        DWORD *pcbSignature)
{
    struct qemu_CryptSignCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIGNCERTIFICATE);
    call.hCryptProv = hCryptProv;
    call.dwKeySpec = dwKeySpec;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbEncodedToBeSigned = (ULONG_PTR)pbEncodedToBeSigned;
    call.cbEncodedToBeSigned = cbEncodedToBeSigned;
    call.pSignatureAlgorithm = (ULONG_PTR)pSignatureAlgorithm;
    call.pvHashAuxInfo = (ULONG_PTR)pvHashAuxInfo;
    call.pbSignature = (ULONG_PTR)pbSignature;
    call.pcbSignature = (ULONG_PTR)pcbSignature;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSignCertificate(struct qemu_syscall *call)
{
    struct qemu_CryptSignCertificate *c = (struct qemu_CryptSignCertificate *)call;
    CRYPT_ALGORITHM_IDENTIFIER stack, *alg = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    alg = QEMU_G2H(c->pSignatureAlgorithm);
#else
    if (c->pvHashAuxInfo)
        WINE_FIXME("Aux info not handled yet.\n");

    if (c->pSignatureAlgorithm)
        CRYPT_ALGORITHM_IDENTIFIER_g2h(alg, QEMU_G2H(c->pSignatureAlgorithm));
    else
        alg = NULL;
#endif

    c->super.iret = CryptSignCertificate(c->hCryptProv, c->dwKeySpec, c->dwCertEncodingType,
            QEMU_G2H(c->pbEncodedToBeSigned), c->cbEncodedToBeSigned, alg,
            QEMU_G2H(c->pvHashAuxInfo), QEMU_G2H(c->pbSignature), QEMU_G2H(c->pcbSignature));
}

#endif

struct qemu_CryptSignAndEncodeCertificate
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwKeySpec;
    uint64_t dwCertEncodingType;
    uint64_t lpszStructType;
    uint64_t pvStructInfo;
    uint64_t pSignatureAlgorithm;
    uint64_t pvHashAuxInfo;
    uint64_t pbEncoded;
    uint64_t pcbEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSignAndEncodeCertificate(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hCryptProv, DWORD dwKeySpec,
        DWORD dwCertEncodingType, LPCSTR lpszStructType, const void *pvStructInfo,
        PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm, const void *pvHashAuxInfo, BYTE *pbEncoded, DWORD *pcbEncoded)
{
    struct qemu_CryptSignAndEncodeCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIGNANDENCODECERTIFICATE);
    call.hCryptProv = hCryptProv;
    call.dwKeySpec = dwKeySpec;
    call.dwCertEncodingType = dwCertEncodingType;
    call.lpszStructType = (ULONG_PTR)lpszStructType;
    call.pvStructInfo = (ULONG_PTR)pvStructInfo;
    call.pSignatureAlgorithm = (ULONG_PTR)pSignatureAlgorithm;
    call.pvHashAuxInfo = (ULONG_PTR)pvHashAuxInfo;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSignAndEncodeCertificate(struct qemu_syscall *call)
{
    struct qemu_CryptSignAndEncodeCertificate *c = (struct qemu_CryptSignAndEncodeCertificate *)call;
    CRYPT_ALGORITHM_IDENTIFIER alg_stack, *alg = &alg_stack;
    CERT_SIGNED_CONTENT_INFO signed_cert_info;
    CERT_INFO cert_info;
    BOOL success = FALSE;
    const char *type;
    void *info;

    WINE_TRACE("\n");
    type = QEMU_G2H(c->lpszStructType);
    info = QEMU_G2H(c->pvStructInfo);

#if GUEST_BIT == HOST_BIT
    alg = QEMU_G2H(c->pSignatureAlgorithm);
#else
    if (c->pSignatureAlgorithm)
        CRYPT_ALGORITHM_IDENTIFIER_g2h(alg, QEMU_G2H(c->pSignatureAlgorithm));
    else
        alg = NULL;

    if (info)
    {
        __TRY
        {
            if (IS_INTOID(type))
            {
                switch (LOWORD(type))
                {
                    case 0:
                        success = TRUE;
                        break;

                    case LOWORD(X509_CERT):
                        CERT_SIGNED_CONTENT_INFO_g2h(&signed_cert_info, info);
                        info = &signed_cert_info;
                        success = TRUE;
                        break;

                    case LOWORD(X509_CERT_TO_BE_SIGNED):
                        CERT_INFO_g2h(&cert_info, info);
                        info = &cert_info;
                        success = TRUE;
                        break;

                    default:
                        WINE_FIXME("Unhandled struct type %x.\n", LOWORD(type));
                        success = TRUE; /* Try my luck */
                }
            }
            else
            {
                WINE_FIXME("String struct types not handled yet.\n");
                WINE_FIXME("Type is \"%s\"\n", type);
                success = TRUE; /* Try my luck */
            }
        }
        __EXCEPT_PAGE_FAULT
        {
            SetLastError(STATUS_ACCESS_VIOLATION);
            c->super.iret = FALSE;
        }
        __ENDTRY

        if (!success)
            return;
    }

    if (c->pvHashAuxInfo)
        WINE_FIXME("Hash aux info not handled yet.\n");
#endif

    c->super.iret = CryptSignAndEncodeCertificate(c->hCryptProv, c->dwKeySpec, c->dwCertEncodingType,
            type, info, alg, QEMU_G2H(c->pvHashAuxInfo), QEMU_G2H(c->pbEncoded), QEMU_G2H(c->pcbEncoded));
}

#endif

struct qemu_CryptVerifyCertificateSignature
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwCertEncodingType;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t pPublicKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifyCertificateSignature(HCRYPTPROV_LEGACY hCryptProv, DWORD dwCertEncodingType,
        const BYTE *pbEncoded, DWORD cbEncoded, PCERT_PUBLIC_KEY_INFO pPublicKey)
{
    struct qemu_CryptVerifyCertificateSignature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYCERTIFICATESIGNATURE);
    call.hCryptProv = hCryptProv;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.pPublicKey = (ULONG_PTR)pPublicKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifyCertificateSignature(struct qemu_syscall *call)
{
    struct qemu_CryptVerifyCertificateSignature *c = (struct qemu_CryptVerifyCertificateSignature *)call;
    CERT_PUBLIC_KEY_INFO stack, *info = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->pPublicKey);
#else
    if (c->pPublicKey)
        CERT_PUBLIC_KEY_INFO_g2h(info, QEMU_G2H(c->pPublicKey));
    else
        info = NULL;
#endif

    c->super.iret = CryptVerifyCertificateSignature(c->hCryptProv, c->dwCertEncodingType,
            QEMU_G2H(c->pbEncoded), c->cbEncoded, info);
}

#endif

struct qemu_CryptVerifyCertificateSignatureEx
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwCertEncodingType;
    uint64_t dwSubjectType;
    uint64_t pvSubject;
    uint64_t dwIssuerType;
    uint64_t pvIssuer;
    uint64_t dwFlags;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifyCertificateSignatureEx(HCRYPTPROV_LEGACY hCryptProv, DWORD dwCertEncodingType,
        DWORD dwSubjectType, void *pvSubject, DWORD dwIssuerType, void *pvIssuer, DWORD dwFlags, void *pvReserved)
{
    struct qemu_CryptVerifyCertificateSignatureEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYCERTIFICATESIGNATUREEX);
    call.hCryptProv = hCryptProv;
    call.dwCertEncodingType = dwCertEncodingType;
    call.dwSubjectType = dwSubjectType;
    call.pvSubject = (ULONG_PTR)pvSubject;
    call.dwIssuerType = dwIssuerType;
    call.pvIssuer = (ULONG_PTR)pvIssuer;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifyCertificateSignatureEx(struct qemu_syscall *call)
{
    struct qemu_CryptVerifyCertificateSignatureEx *c = (struct qemu_CryptVerifyCertificateSignatureEx *)call;
    CERT_PUBLIC_KEY_INFO pubkey;
    CRYPT_DATA_BLOB blob;
    void *issuer, *subject;

    WINE_TRACE("\n");
    issuer = QEMU_G2H(c->pvIssuer);
    subject = QEMU_G2H(c->pvSubject);
#if GUEST_BIT == HOST_BIT
    /* Nothing to do */
#else
    if (issuer)
    {
        switch (c->dwIssuerType)
        {
            case CRYPT_VERIFY_CERT_SIGN_ISSUER_PUBKEY:
                CERT_PUBLIC_KEY_INFO_g2h(&pubkey, issuer);
                issuer = &pubkey;
                break;

            case CRYPT_VERIFY_CERT_SIGN_ISSUER_CERT:
                WINE_FIXME("Unimplemented CRYPT_VERIFY_CERT_SIGN_ISSUER_CERT.\n");
                break;

            case CRYPT_VERIFY_CERT_SIGN_ISSUER_CHAIN:
                WINE_FIXME("Unimplemented CRYPT_VERIFY_CERT_SIGN_ISSUER_CHAIN.\n");
                break;

            case CRYPT_VERIFY_CERT_SIGN_ISSUER_NULL:
                WINE_FIXME("Unimplemented CRYPT_VERIFY_CERT_SIGN_ISSUER_NULL.\n");
                break;

            default:
                WINE_FIXME("Unimplemented issuer type %x.\n", (DWORD)c->dwIssuerType);
        }
    }

    if (subject)
    {
        switch (c->dwSubjectType)
        {
            case CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB:
                CRYPT_DATA_BLOB_g2h(&blob, subject);
                subject = &blob;
                break;

            case CRYPT_VERIFY_CERT_SIGN_SUBJECT_CERT:
                WINE_FIXME("Unimplemented CRYPT_VERIFY_CERT_SIGN_SUBJECT_CERT.\n");
                break;

            case CRYPT_VERIFY_CERT_SIGN_SUBJECT_CRL:
                WINE_FIXME("Unimplemented CRYPT_VERIFY_CERT_SIGN_SUBJECT_CRL.\n");
                break;

            default:
                WINE_FIXME("Unimplemented subject type %x.\n", (DWORD)c->dwSubjectType);
        }
    }
    if (c->pvReserved)
        WINE_FIXME("Unhandled pvReserved.\n");

#endif

    c->super.iret = CryptVerifyCertificateSignatureEx(c->hCryptProv, c->dwCertEncodingType, c->dwSubjectType,
            subject, c->dwIssuerType, issuer, c->dwFlags, QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CertGetIntendedKeyUsage
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pCertInfo;
    uint64_t pbKeyUsage;
    uint64_t cbKeyUsage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetIntendedKeyUsage(DWORD dwCertEncodingType, PCERT_INFO pCertInfo,
        BYTE *pbKeyUsage, DWORD cbKeyUsage)
{
    struct qemu_CertGetIntendedKeyUsage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETINTENDEDKEYUSAGE);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pCertInfo = (ULONG_PTR)pCertInfo;
    call.pbKeyUsage = (ULONG_PTR)pbKeyUsage;
    call.cbKeyUsage = cbKeyUsage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetIntendedKeyUsage(struct qemu_syscall *call)
{
    struct qemu_CertGetIntendedKeyUsage *c = (struct qemu_CertGetIntendedKeyUsage *)call;
    CERT_INFO stack, *info = &stack;
    CERT_EXTENSION *exts = NULL;
    DWORD count, i;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->pCertInfo);
#else
    if (c->pCertInfo)
    {
        CERT_INFO_g2h(info, QEMU_G2H(c->pCertInfo));

        count = info->cExtension;
        if (count && info->rgExtension)
        {
            exts = HeapAlloc(GetProcessHeap(), 0, sizeof(*exts) * count);
            for (i = 0; i < count; ++i)
                CERT_EXTENSION_g2h(&exts[i], &((struct qemu_CERT_EXTENSION *)info->rgExtension)[i]);
            info->rgExtension = exts;
        }
    }
    else
        info = NULL;
#endif

    c->super.iret = CertGetIntendedKeyUsage(c->dwCertEncodingType, info, QEMU_G2H(c->pbKeyUsage), c->cbKeyUsage);
    HeapFree(GetProcessHeap(), 0, exts);
}

#endif

struct qemu_CertGetEnhancedKeyUsage
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwFlags;
    uint64_t pUsage;
    uint64_t pcbUsage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetEnhancedKeyUsage(PCCERT_CONTEXT pCertContext, DWORD dwFlags,
        PCERT_ENHKEY_USAGE pUsage, DWORD *pcbUsage)
{
    struct qemu_CertGetEnhancedKeyUsage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETENHANCEDKEYUSAGE);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwFlags = dwFlags;
    call.pUsage = (ULONG_PTR)pUsage;
    call.pcbUsage = (ULONG_PTR)pcbUsage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetEnhancedKeyUsage(struct qemu_syscall *call)
{
    struct qemu_CertGetEnhancedKeyUsage *c = (struct qemu_CertGetEnhancedKeyUsage *)call;
    const CERT_CONTEXT *context;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    context = QEMU_G2H(c->pCertContext);
#else
    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    context = context32 ? context32->cert64 : NULL;
    WINE_FIXME("Output not handled yet.\n");
#endif

    /* No cheating with the size here, the test depends on the exact size */
    c->super.iret = CertGetEnhancedKeyUsage(context, c->dwFlags, QEMU_G2H(c->pUsage), QEMU_G2H(c->pcbUsage));
}

#endif

struct qemu_CertSetEnhancedKeyUsage
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t pUsage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSetEnhancedKeyUsage(PCCERT_CONTEXT pCertContext, PCERT_ENHKEY_USAGE pUsage)
{
    struct qemu_CertSetEnhancedKeyUsage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSETENHANCEDKEYUSAGE);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.pUsage = (ULONG_PTR)pUsage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSetEnhancedKeyUsage(struct qemu_syscall *call)
{
    struct qemu_CertSetEnhancedKeyUsage *c = (struct qemu_CertSetEnhancedKeyUsage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSetEnhancedKeyUsage(QEMU_G2H(c->pCertContext), QEMU_G2H(c->pUsage));
}

#endif

struct qemu_CertAddEnhancedKeyUsageIdentifier
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t pszUsageIdentifier;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddEnhancedKeyUsageIdentifier(PCCERT_CONTEXT pCertContext, LPCSTR pszUsageIdentifier)
{
    struct qemu_CertAddEnhancedKeyUsageIdentifier call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDENHANCEDKEYUSAGEIDENTIFIER);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.pszUsageIdentifier = (ULONG_PTR)pszUsageIdentifier;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddEnhancedKeyUsageIdentifier(struct qemu_syscall *call)
{
    struct qemu_CertAddEnhancedKeyUsageIdentifier *c = (struct qemu_CertAddEnhancedKeyUsageIdentifier *)call;
    const CERT_CONTEXT *context;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    context = QEMU_G2H(c->pCertContext);
#else
    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    context = context32 ? context32->cert64 : NULL;
#endif

    c->super.iret = CertAddEnhancedKeyUsageIdentifier(context, QEMU_G2H(c->pszUsageIdentifier));
}

#endif

struct qemu_CertRemoveEnhancedKeyUsageIdentifier
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t pszUsageIdentifier;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertRemoveEnhancedKeyUsageIdentifier(PCCERT_CONTEXT pCertContext, LPCSTR pszUsageIdentifier)
{
    struct qemu_CertRemoveEnhancedKeyUsageIdentifier call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTREMOVEENHANCEDKEYUSAGEIDENTIFIER);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.pszUsageIdentifier = (ULONG_PTR)pszUsageIdentifier;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertRemoveEnhancedKeyUsageIdentifier(struct qemu_syscall *call)
{
    struct qemu_CertRemoveEnhancedKeyUsageIdentifier *c = (struct qemu_CertRemoveEnhancedKeyUsageIdentifier *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertRemoveEnhancedKeyUsageIdentifier(QEMU_G2H(c->pCertContext), QEMU_G2H(c->pszUsageIdentifier));
}

#endif

struct qemu_CertGetValidUsages
{
    struct qemu_syscall super;
    uint64_t cCerts;
    uint64_t rghCerts;
    uint64_t cNumOIDs;
    uint64_t rghOIDs;
    uint64_t pcbOIDs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetValidUsages(DWORD cCerts, PCCERT_CONTEXT *rghCerts, int *cNumOIDs,
        LPSTR *rghOIDs, DWORD *pcbOIDs)
{
    struct qemu_CertGetValidUsages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETVALIDUSAGES);
    call.cCerts = cCerts;
    call.rghCerts = (ULONG_PTR)rghCerts;
    call.cNumOIDs = (ULONG_PTR)cNumOIDs;
    call.rghOIDs = (ULONG_PTR)rghOIDs;
    call.pcbOIDs = (ULONG_PTR)pcbOIDs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetValidUsages(struct qemu_syscall *call)
{
    struct qemu_CertGetValidUsages *c = (struct qemu_CertGetValidUsages *)call;
    const CERT_CONTEXT **contexts = NULL;
    struct qemu_cert_context *context32;
    qemu_ptr *contexts32;
    DWORD count, i;
    char **oids;

    WINE_TRACE("\n");
    count = c->cCerts;
    oids = QEMU_G2H(c->rghOIDs);
#if GUEST_BIT == HOST_BIT
    contexts = QEMU_G2H(c->rghCerts);
#else
    contexts32 = QEMU_G2H(c->rghCerts);

    if (count && contexts32)
    {
        contexts = HeapAlloc(GetProcessHeap(), 0, sizeof(*contexts) * count);
        if (!contexts)
            WINE_ERR("Out of memory\n");

        for (i = 0; i < count; ++i)
        {
            context32 = context_impl_from_context32(QEMU_G2H((uint64_t)contexts32[i]));
            contexts[i] = context32 ? context32->cert64 : NULL;
        }
    }
#endif

    c->super.iret = CertGetValidUsages(count, contexts, QEMU_G2H(c->cNumOIDs), oids, QEMU_G2H(c->pcbOIDs));

#if GUEST_BIT != HOST_BIT
    if (c->super.iret && oids)
    {
        qemu_ptr *array32 = (void *)oids;
        count = *((DWORD *)QEMU_G2H(c->cNumOIDs));
        for (i = 0; i < count; ++i)
            array32[i] = QEMU_H2G(oids[i]);
    }
    HeapFree(GetProcessHeap(), 0, contexts);
#endif
}

#endif

struct qemu_CertCreateSelfSignCertificate
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t pSubjectIssuerBlob;
    uint64_t dwFlags;
    uint64_t pKeyProvInfo;
    uint64_t pSignatureAlgorithm;
    uint64_t pStartTime;
    uint64_t pEndTime;
    uint64_t pExtensions;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertCreateSelfSignCertificate(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hProv,
        PCERT_NAME_BLOB pSubjectIssuerBlob, DWORD dwFlags, PCRYPT_KEY_PROV_INFO pKeyProvInfo,
        PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm, PSYSTEMTIME pStartTime, PSYSTEMTIME pEndTime,
        PCERT_EXTENSIONS pExtensions)
{
    struct qemu_CertCreateSelfSignCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATESELFSIGNCERTIFICATE);
    call.hProv = hProv;
    call.pSubjectIssuerBlob = (ULONG_PTR)pSubjectIssuerBlob;
    call.dwFlags = dwFlags;
    call.pKeyProvInfo = (ULONG_PTR)pKeyProvInfo;
    call.pSignatureAlgorithm = (ULONG_PTR)pSignatureAlgorithm;
    call.pStartTime = (ULONG_PTR)pStartTime;
    call.pEndTime = (ULONG_PTR)pEndTime;
    call.pExtensions = (ULONG_PTR)pExtensions;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertCreateSelfSignCertificate(struct qemu_syscall *call)
{
    struct qemu_CertCreateSelfSignCertificate *c = (struct qemu_CertCreateSelfSignCertificate *)call;
    const CERT_CONTEXT *context;
    CERT_NAME_BLOB stack, *issuer = &stack;
    CRYPT_ALGORITHM_IDENTIFIER alg_s, *alg = &alg_s;
    CRYPT_KEY_PROV_INFO info_s, *info = &info_s;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    issuer = QEMU_G2H(c->pSubjectIssuerBlob);
    alg = QEMU_G2H(c->pSignatureAlgorithm);
    info = QEMU_G2H(c->pKeyProvInfo);
#else
    if (c->pSubjectIssuerBlob)
        CRYPT_DATA_BLOB_g2h(issuer, QEMU_G2H(c->pSubjectIssuerBlob));
    else
        issuer = NULL;

    if (c->pSignatureAlgorithm)
        CRYPT_ALGORITHM_IDENTIFIER_g2h(alg, QEMU_G2H(c->pSignatureAlgorithm));
    else
        alg = NULL;

    if (c->pKeyProvInfo)
    {
        CRYPT_KEY_PROV_INFO_g2h(info, QEMU_G2H(c->pKeyProvInfo));
        if (info->cProvParam || info->rgProvParam)
            WINE_FIXME("Convert info parameters\n");
    }
    else
    {
        info = NULL;
    }

    if (c->pExtensions)
        WINE_FIXME("Extension pointer not handled yet.\n");
#endif

    context = CertCreateSelfSignCertificate(c->hProv, issuer, c->dwFlags, info, alg,
            QEMU_G2H(c->pStartTime), QEMU_G2H(c->pEndTime), QEMU_G2H(c->pExtensions));

#if GUEST_BIT != HOST_BIT
    if (context)
        context = (CERT_CONTEXT *)context32_create(context);
#endif

    c->super.iret = QEMU_H2G(context);
}

#endif

struct qemu_CertVerifyCTLUsage
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t dwSubjectType;
    uint64_t pvSubject;
    uint64_t pSubjectUsage;
    uint64_t dwFlags;
    uint64_t pVerifyUsagePara;
    uint64_t pVerifyUsageStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertVerifyCTLUsage(DWORD dwEncodingType, DWORD dwSubjectType, void *pvSubject, PCTL_USAGE pSubjectUsage, DWORD dwFlags, PCTL_VERIFY_USAGE_PARA pVerifyUsagePara, PCTL_VERIFY_USAGE_STATUS pVerifyUsageStatus)
{
    struct qemu_CertVerifyCTLUsage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYCTLUSAGE);
    call.dwEncodingType = dwEncodingType;
    call.dwSubjectType = dwSubjectType;
    call.pvSubject = (ULONG_PTR)pvSubject;
    call.pSubjectUsage = (ULONG_PTR)pSubjectUsage;
    call.dwFlags = dwFlags;
    call.pVerifyUsagePara = (ULONG_PTR)pVerifyUsagePara;
    call.pVerifyUsageStatus = (ULONG_PTR)pVerifyUsageStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyCTLUsage(struct qemu_syscall *call)
{
    struct qemu_CertVerifyCTLUsage *c = (struct qemu_CertVerifyCTLUsage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifyCTLUsage(c->dwEncodingType, c->dwSubjectType, QEMU_G2H(c->pvSubject), QEMU_G2H(c->pSubjectUsage), c->dwFlags, QEMU_G2H(c->pVerifyUsagePara), QEMU_G2H(c->pVerifyUsageStatus));
}

#endif

struct qemu_CertCreateContext
{
    struct qemu_syscall super;
    uint64_t dwContextType;
    uint64_t dwEncodingType;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t dwFlags;
    uint64_t pCreatePara;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const void * WINAPI CertCreateContext(DWORD dwContextType, DWORD dwEncodingType, const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, PCERT_CREATE_CONTEXT_PARA pCreatePara)
{
    struct qemu_CertCreateContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATECONTEXT);
    call.dwContextType = dwContextType;
    call.dwEncodingType = dwEncodingType;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.dwFlags = dwFlags;
    call.pCreatePara = (ULONG_PTR)pCreatePara;

    qemu_syscall(&call.super);

    return (const void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertCreateContext(struct qemu_syscall *call)
{
    struct qemu_CertCreateContext *c = (struct qemu_CertCreateContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertCreateContext(c->dwContextType, c->dwEncodingType, QEMU_G2H(c->pbEncoded), c->cbEncoded, c->dwFlags, QEMU_G2H(c->pCreatePara)));
}

#endif

