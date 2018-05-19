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

struct qemu_CertCreateCRLContext
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pbCrlEncoded;
    uint64_t cbCrlEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCRL_CONTEXT WINAPI CertCreateCRLContext(DWORD dwCertEncodingType, const BYTE* pbCrlEncoded, DWORD cbCrlEncoded)
{
    struct qemu_CertCreateCRLContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATECRLCONTEXT);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbCrlEncoded = (ULONG_PTR)pbCrlEncoded;
    call.cbCrlEncoded = cbCrlEncoded;

    qemu_syscall(&call.super);

    return (PCCRL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertCreateCRLContext(struct qemu_syscall *call)
{
    struct qemu_CertCreateCRLContext *c = (struct qemu_CertCreateCRLContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertCreateCRLContext(c->dwCertEncodingType, QEMU_G2H(c->pbCrlEncoded), c->cbCrlEncoded));
}

#endif

struct qemu_CertAddEncodedCRLToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwCertEncodingType;
    uint64_t pbCrlEncoded;
    uint64_t cbCrlEncoded;
    uint64_t dwAddDisposition;
    uint64_t ppCrlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddEncodedCRLToStore(HCERTSTORE hCertStore, DWORD dwCertEncodingType, const BYTE *pbCrlEncoded, DWORD cbCrlEncoded, DWORD dwAddDisposition, PCCRL_CONTEXT *ppCrlContext)
{
    struct qemu_CertAddEncodedCRLToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDENCODEDCRLTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwCertEncodingType = dwCertEncodingType;
    call.pbCrlEncoded = (ULONG_PTR)pbCrlEncoded;
    call.cbCrlEncoded = cbCrlEncoded;
    call.dwAddDisposition = dwAddDisposition;
    call.ppCrlContext = (ULONG_PTR)ppCrlContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddEncodedCRLToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddEncodedCRLToStore *c = (struct qemu_CertAddEncodedCRLToStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddEncodedCRLToStore(QEMU_G2H(c->hCertStore), c->dwCertEncodingType, QEMU_G2H(c->pbCrlEncoded), c->cbCrlEncoded, c->dwAddDisposition, QEMU_G2H(c->ppCrlContext));
}

#endif

struct qemu_CertFindCRLInStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwCertEncodingType;
    uint64_t dwFindFlags;
    uint64_t dwFindType;
    uint64_t pvFindPara;
    uint64_t pPrevCrlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCRL_CONTEXT WINAPI CertFindCRLInStore(HCERTSTORE hCertStore, DWORD dwCertEncodingType, DWORD dwFindFlags, DWORD dwFindType, const void *pvFindPara, PCCRL_CONTEXT pPrevCrlContext)
{
    struct qemu_CertFindCRLInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDCRLINSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwCertEncodingType = dwCertEncodingType;
    call.dwFindFlags = dwFindFlags;
    call.dwFindType = dwFindType;
    call.pvFindPara = (ULONG_PTR)pvFindPara;
    call.pPrevCrlContext = (ULONG_PTR)pPrevCrlContext;

    qemu_syscall(&call.super);

    return (PCCRL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindCRLInStore(struct qemu_syscall *call)
{
    struct qemu_CertFindCRLInStore *c = (struct qemu_CertFindCRLInStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindCRLInStore(QEMU_G2H(c->hCertStore), c->dwCertEncodingType, c->dwFindFlags, c->dwFindType, QEMU_G2H(c->pvFindPara), QEMU_G2H(c->pPrevCrlContext)));
}

#endif

struct qemu_CertGetCRLFromStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pIssuerContext;
    uint64_t pPrevCrlContext;
    uint64_t pdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCRL_CONTEXT WINAPI CertGetCRLFromStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pIssuerContext, PCCRL_CONTEXT pPrevCrlContext, DWORD *pdwFlags)
{
    struct qemu_CertGetCRLFromStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETCRLFROMSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pIssuerContext = (ULONG_PTR)pIssuerContext;
    call.pPrevCrlContext = (ULONG_PTR)pPrevCrlContext;
    call.pdwFlags = (ULONG_PTR)pdwFlags;

    qemu_syscall(&call.super);

    return (PCCRL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertGetCRLFromStore(struct qemu_syscall *call)
{
    struct qemu_CertGetCRLFromStore *c = (struct qemu_CertGetCRLFromStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertGetCRLFromStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pIssuerContext), QEMU_G2H(c->pPrevCrlContext), QEMU_G2H(c->pdwFlags)));
}

#endif

struct qemu_CertDuplicateCRLContext
{
    struct qemu_syscall super;
    uint64_t pCrlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCRL_CONTEXT WINAPI CertDuplicateCRLContext(PCCRL_CONTEXT pCrlContext)
{
    struct qemu_CertDuplicateCRLContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDUPLICATECRLCONTEXT);
    call.pCrlContext = (ULONG_PTR)pCrlContext;

    qemu_syscall(&call.super);

    return (PCCRL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertDuplicateCRLContext(struct qemu_syscall *call)
{
    struct qemu_CertDuplicateCRLContext *c = (struct qemu_CertDuplicateCRLContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertDuplicateCRLContext(QEMU_G2H(c->pCrlContext)));
}

#endif

struct qemu_CertFreeCRLContext
{
    struct qemu_syscall super;
    uint64_t pCrlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertFreeCRLContext(PCCRL_CONTEXT pCrlContext)
{
    struct qemu_CertFreeCRLContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFREECRLCONTEXT);
    call.pCrlContext = (ULONG_PTR)pCrlContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertFreeCRLContext(struct qemu_syscall *call)
{
    struct qemu_CertFreeCRLContext *c = (struct qemu_CertFreeCRLContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertFreeCRLContext(QEMU_G2H(c->pCrlContext));
}

#endif

struct qemu_CertEnumCRLContextProperties
{
    struct qemu_syscall super;
    uint64_t pCRLContext;
    uint64_t dwPropId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertEnumCRLContextProperties(PCCRL_CONTEXT pCRLContext, DWORD dwPropId)
{
    struct qemu_CertEnumCRLContextProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMCRLCONTEXTPROPERTIES);
    call.pCRLContext = (ULONG_PTR)pCRLContext;
    call.dwPropId = dwPropId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertEnumCRLContextProperties(struct qemu_syscall *call)
{
    struct qemu_CertEnumCRLContextProperties *c = (struct qemu_CertEnumCRLContextProperties *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertEnumCRLContextProperties(QEMU_G2H(c->pCRLContext), c->dwPropId);
}

#endif

struct qemu_CertGetCRLContextProperty
{
    struct qemu_syscall super;
    uint64_t pCRLContext;
    uint64_t dwPropId;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetCRLContextProperty(PCCRL_CONTEXT pCRLContext, DWORD dwPropId, void *pvData, DWORD *pcbData)
{
    struct qemu_CertGetCRLContextProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETCRLCONTEXTPROPERTY);
    call.pCRLContext = (ULONG_PTR)pCRLContext;
    call.dwPropId = dwPropId;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetCRLContextProperty(struct qemu_syscall *call)
{
    struct qemu_CertGetCRLContextProperty *c = (struct qemu_CertGetCRLContextProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetCRLContextProperty(QEMU_G2H(c->pCRLContext), c->dwPropId, QEMU_G2H(c->pvData), QEMU_G2H(c->pcbData));
}

#endif

struct qemu_CertSetCRLContextProperty
{
    struct qemu_syscall super;
    uint64_t pCRLContext;
    uint64_t dwPropId;
    uint64_t dwFlags;
    uint64_t pvData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSetCRLContextProperty(PCCRL_CONTEXT pCRLContext, DWORD dwPropId, DWORD dwFlags, const void *pvData)
{
    struct qemu_CertSetCRLContextProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSETCRLCONTEXTPROPERTY);
    call.pCRLContext = (ULONG_PTR)pCRLContext;
    call.dwPropId = dwPropId;
    call.dwFlags = dwFlags;
    call.pvData = (ULONG_PTR)pvData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSetCRLContextProperty(struct qemu_syscall *call)
{
    struct qemu_CertSetCRLContextProperty *c = (struct qemu_CertSetCRLContextProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSetCRLContextProperty(QEMU_G2H(c->pCRLContext), c->dwPropId, c->dwFlags, QEMU_G2H(c->pvData));
}

#endif

struct qemu_CertIsValidCRLForCertificate
{
    struct qemu_syscall super;
    uint64_t pCert;
    uint64_t pCrl;
    uint64_t dwFlags;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertIsValidCRLForCertificate(PCCERT_CONTEXT pCert, PCCRL_CONTEXT pCrl, DWORD dwFlags, void *pvReserved)
{
    struct qemu_CertIsValidCRLForCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTISVALIDCRLFORCERTIFICATE);
    call.pCert = (ULONG_PTR)pCert;
    call.pCrl = (ULONG_PTR)pCrl;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertIsValidCRLForCertificate(struct qemu_syscall *call)
{
    struct qemu_CertIsValidCRLForCertificate *c = (struct qemu_CertIsValidCRLForCertificate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertIsValidCRLForCertificate(QEMU_G2H(c->pCert), QEMU_G2H(c->pCrl), c->dwFlags, QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CertFindCertificateInCRL
{
    struct qemu_syscall super;
    uint64_t pCert;
    uint64_t pCrlContext;
    uint64_t dwFlags;
    uint64_t pvReserved;
    uint64_t ppCrlEntry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertFindCertificateInCRL(PCCERT_CONTEXT pCert, PCCRL_CONTEXT pCrlContext, DWORD dwFlags, void *pvReserved, PCRL_ENTRY *ppCrlEntry)
{
    struct qemu_CertFindCertificateInCRL call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDCERTIFICATEINCRL);
    call.pCert = (ULONG_PTR)pCert;
    call.pCrlContext = (ULONG_PTR)pCrlContext;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.ppCrlEntry = (ULONG_PTR)ppCrlEntry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertFindCertificateInCRL(struct qemu_syscall *call)
{
    struct qemu_CertFindCertificateInCRL *c = (struct qemu_CertFindCertificateInCRL *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertFindCertificateInCRL(QEMU_G2H(c->pCert), QEMU_G2H(c->pCrlContext), c->dwFlags, QEMU_G2H(c->pvReserved), QEMU_G2H(c->ppCrlEntry));
}

#endif

struct qemu_CertVerifyCRLRevocation
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pCertId;
    uint64_t cCrlInfo;
    uint64_t rgpCrlInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertVerifyCRLRevocation(DWORD dwCertEncodingType, PCERT_INFO pCertId, DWORD cCrlInfo, PCRL_INFO rgpCrlInfo[])
{
    struct qemu_CertVerifyCRLRevocation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYCRLREVOCATION);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pCertId = (ULONG_PTR)pCertId;
    call.cCrlInfo = cCrlInfo;
    call.rgpCrlInfo = (ULONG_PTR)rgpCrlInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyCRLRevocation(struct qemu_syscall *call)
{
    struct qemu_CertVerifyCRLRevocation *c = (struct qemu_CertVerifyCRLRevocation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifyCRLRevocation(c->dwCertEncodingType, QEMU_G2H(c->pCertId), c->cCrlInfo, QEMU_G2H(c->rgpCrlInfo));
}

#endif

struct qemu_CertVerifyCRLTimeValidity
{
    struct qemu_syscall super;
    uint64_t pTimeToVerify;
    uint64_t pCrlInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI CertVerifyCRLTimeValidity(LPFILETIME pTimeToVerify, PCRL_INFO pCrlInfo)
{
    struct qemu_CertVerifyCRLTimeValidity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYCRLTIMEVALIDITY);
    call.pTimeToVerify = (ULONG_PTR)pTimeToVerify;
    call.pCrlInfo = (ULONG_PTR)pCrlInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyCRLTimeValidity(struct qemu_syscall *call)
{
    struct qemu_CertVerifyCRLTimeValidity *c = (struct qemu_CertVerifyCRLTimeValidity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifyCRLTimeValidity(QEMU_G2H(c->pTimeToVerify), QEMU_G2H(c->pCrlInfo));
}

#endif

