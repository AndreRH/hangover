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

struct qemu_CertSerializeCertificateStoreElement
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwFlags;
    uint64_t pbElement;
    uint64_t pcbElement;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSerializeCertificateStoreElement(PCCERT_CONTEXT pCertContext, DWORD dwFlags, BYTE *pbElement, DWORD *pcbElement)
{
    struct qemu_CertSerializeCertificateStoreElement call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSERIALIZECERTIFICATESTOREELEMENT);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwFlags = dwFlags;
    call.pbElement = (ULONG_PTR)pbElement;
    call.pcbElement = (ULONG_PTR)pcbElement;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSerializeCertificateStoreElement(struct qemu_syscall *call)
{
    struct qemu_CertSerializeCertificateStoreElement *c = (struct qemu_CertSerializeCertificateStoreElement *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSerializeCertificateStoreElement(QEMU_G2H(c->pCertContext), c->dwFlags, QEMU_G2H(c->pbElement), QEMU_G2H(c->pcbElement));
}

#endif

struct qemu_CertSerializeCRLStoreElement
{
    struct qemu_syscall super;
    uint64_t pCrlContext;
    uint64_t dwFlags;
    uint64_t pbElement;
    uint64_t pcbElement;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSerializeCRLStoreElement(PCCRL_CONTEXT pCrlContext, DWORD dwFlags, BYTE *pbElement, DWORD *pcbElement)
{
    struct qemu_CertSerializeCRLStoreElement call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSERIALIZECRLSTOREELEMENT);
    call.pCrlContext = (ULONG_PTR)pCrlContext;
    call.dwFlags = dwFlags;
    call.pbElement = (ULONG_PTR)pbElement;
    call.pcbElement = (ULONG_PTR)pcbElement;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSerializeCRLStoreElement(struct qemu_syscall *call)
{
    struct qemu_CertSerializeCRLStoreElement *c = (struct qemu_CertSerializeCRLStoreElement *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSerializeCRLStoreElement(QEMU_G2H(c->pCrlContext), c->dwFlags, QEMU_G2H(c->pbElement), QEMU_G2H(c->pcbElement));
}

#endif

struct qemu_CertSerializeCTLStoreElement
{
    struct qemu_syscall super;
    uint64_t pCtlContext;
    uint64_t dwFlags;
    uint64_t pbElement;
    uint64_t pcbElement;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSerializeCTLStoreElement(PCCTL_CONTEXT pCtlContext, DWORD dwFlags, BYTE *pbElement, DWORD *pcbElement)
{
    struct qemu_CertSerializeCTLStoreElement call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSERIALIZECTLSTOREELEMENT);
    call.pCtlContext = (ULONG_PTR)pCtlContext;
    call.dwFlags = dwFlags;
    call.pbElement = (ULONG_PTR)pbElement;
    call.pcbElement = (ULONG_PTR)pcbElement;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSerializeCTLStoreElement(struct qemu_syscall *call)
{
    struct qemu_CertSerializeCTLStoreElement *c = (struct qemu_CertSerializeCTLStoreElement *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSerializeCTLStoreElement(QEMU_G2H(c->pCtlContext), c->dwFlags, QEMU_G2H(c->pbElement), QEMU_G2H(c->pcbElement));
}

#endif

struct qemu_CertSaveStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwMsgAndCertEncodingType;
    uint64_t dwSaveAs;
    uint64_t dwSaveTo;
    uint64_t pvSaveToPara;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSaveStore(HCERTSTORE hCertStore, DWORD dwMsgAndCertEncodingType, DWORD dwSaveAs, DWORD dwSaveTo, void *pvSaveToPara, DWORD dwFlags)
{
    struct qemu_CertSaveStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSAVESTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwMsgAndCertEncodingType = dwMsgAndCertEncodingType;
    call.dwSaveAs = dwSaveAs;
    call.dwSaveTo = dwSaveTo;
    call.pvSaveToPara = (ULONG_PTR)pvSaveToPara;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSaveStore(struct qemu_syscall *call)
{
    struct qemu_CertSaveStore *c = (struct qemu_CertSaveStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSaveStore(QEMU_G2H(c->hCertStore), c->dwMsgAndCertEncodingType, c->dwSaveAs, c->dwSaveTo, QEMU_G2H(c->pvSaveToPara), c->dwFlags);
}

#endif

struct qemu_CertAddSerializedElementToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pbElement;
    uint64_t cbElement;
    uint64_t dwAddDisposition;
    uint64_t dwFlags;
    uint64_t dwContextTypeFlags;
    uint64_t pdwContentType;
    uint64_t ppvContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddSerializedElementToStore(HCERTSTORE hCertStore, const BYTE *pbElement, DWORD cbElement, DWORD dwAddDisposition, DWORD dwFlags, DWORD dwContextTypeFlags, DWORD *pdwContentType, const void **ppvContext)
{
    struct qemu_CertAddSerializedElementToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDSERIALIZEDELEMENTTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pbElement = (ULONG_PTR)pbElement;
    call.cbElement = cbElement;
    call.dwAddDisposition = dwAddDisposition;
    call.dwFlags = dwFlags;
    call.dwContextTypeFlags = dwContextTypeFlags;
    call.pdwContentType = (ULONG_PTR)pdwContentType;
    call.ppvContext = (ULONG_PTR)ppvContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddSerializedElementToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddSerializedElementToStore *c = (struct qemu_CertAddSerializedElementToStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddSerializedElementToStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pbElement), c->cbElement, c->dwAddDisposition, c->dwFlags, c->dwContextTypeFlags, QEMU_G2H(c->pdwContentType), QEMU_G2H(c->ppvContext));
}

#endif

