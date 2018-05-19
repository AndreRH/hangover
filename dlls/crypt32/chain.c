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

struct qemu_CertCreateCertificateChainEngine
{
    struct qemu_syscall super;
    uint64_t pConfig;
    uint64_t phChainEngine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertCreateCertificateChainEngine(PCERT_CHAIN_ENGINE_CONFIG pConfig, HCERTCHAINENGINE *phChainEngine)
{
    struct qemu_CertCreateCertificateChainEngine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATECERTIFICATECHAINENGINE);
    call.pConfig = (ULONG_PTR)pConfig;
    call.phChainEngine = (ULONG_PTR)phChainEngine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertCreateCertificateChainEngine(struct qemu_syscall *call)
{
    struct qemu_CertCreateCertificateChainEngine *c = (struct qemu_CertCreateCertificateChainEngine *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertCreateCertificateChainEngine(QEMU_G2H(c->pConfig), QEMU_G2H(c->phChainEngine));
}

#endif

struct qemu_CertFreeCertificateChainEngine
{
    struct qemu_syscall super;
    uint64_t hChainEngine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI CertFreeCertificateChainEngine(HCERTCHAINENGINE hChainEngine)
{
    struct qemu_CertFreeCertificateChainEngine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFREECERTIFICATECHAINENGINE);
    call.hChainEngine = (ULONG_PTR)hChainEngine;

    qemu_syscall(&call.super);
}

#else

void qemu_CertFreeCertificateChainEngine(struct qemu_syscall *call)
{
    struct qemu_CertFreeCertificateChainEngine *c = (struct qemu_CertFreeCertificateChainEngine *)call;
    WINE_FIXME("Unverified!\n");
    CertFreeCertificateChainEngine(QEMU_G2H(c->hChainEngine));
}

#endif

struct qemu_CertGetCertificateChain
{
    struct qemu_syscall super;
    uint64_t hChainEngine;
    uint64_t pCertContext;
    uint64_t pTime;
    uint64_t hAdditionalStore;
    uint64_t pChainPara;
    uint64_t dwFlags;
    uint64_t pvReserved;
    uint64_t ppChainContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetCertificateChain(HCERTCHAINENGINE hChainEngine, PCCERT_CONTEXT pCertContext, LPFILETIME pTime, HCERTSTORE hAdditionalStore, PCERT_CHAIN_PARA pChainPara, DWORD dwFlags, LPVOID pvReserved, PCCERT_CHAIN_CONTEXT* ppChainContext)
{
    struct qemu_CertGetCertificateChain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETCERTIFICATECHAIN);
    call.hChainEngine = (ULONG_PTR)hChainEngine;
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.pTime = (ULONG_PTR)pTime;
    call.hAdditionalStore = (ULONG_PTR)hAdditionalStore;
    call.pChainPara = (ULONG_PTR)pChainPara;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.ppChainContext = (ULONG_PTR)ppChainContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetCertificateChain(struct qemu_syscall *call)
{
    struct qemu_CertGetCertificateChain *c = (struct qemu_CertGetCertificateChain *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetCertificateChain(QEMU_G2H(c->hChainEngine), QEMU_G2H(c->pCertContext), QEMU_G2H(c->pTime), QEMU_G2H(c->hAdditionalStore), QEMU_G2H(c->pChainPara), c->dwFlags, QEMU_G2H(c->pvReserved), QEMU_G2H(c->ppChainContext));
}

#endif

struct qemu_CertDuplicateCertificateChain
{
    struct qemu_syscall super;
    uint64_t pChainContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CHAIN_CONTEXT WINAPI CertDuplicateCertificateChain(PCCERT_CHAIN_CONTEXT pChainContext)
{
    struct qemu_CertDuplicateCertificateChain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDUPLICATECERTIFICATECHAIN);
    call.pChainContext = (ULONG_PTR)pChainContext;

    qemu_syscall(&call.super);

    return (PCCERT_CHAIN_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertDuplicateCertificateChain(struct qemu_syscall *call)
{
    struct qemu_CertDuplicateCertificateChain *c = (struct qemu_CertDuplicateCertificateChain *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertDuplicateCertificateChain(QEMU_G2H(c->pChainContext)));
}

#endif

struct qemu_CertFreeCertificateChain
{
    struct qemu_syscall super;
    uint64_t pChainContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI CertFreeCertificateChain(PCCERT_CHAIN_CONTEXT pChainContext)
{
    struct qemu_CertFreeCertificateChain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFREECERTIFICATECHAIN);
    call.pChainContext = (ULONG_PTR)pChainContext;

    qemu_syscall(&call.super);
}

#else

void qemu_CertFreeCertificateChain(struct qemu_syscall *call)
{
    struct qemu_CertFreeCertificateChain *c = (struct qemu_CertFreeCertificateChain *)call;
    WINE_FIXME("Unverified!\n");
    CertFreeCertificateChain(QEMU_G2H(c->pChainContext));
}

#endif

struct qemu_CertFindChainInStore
{
    struct qemu_syscall super;
    uint64_t store;
    uint64_t certEncodingType;
    uint64_t findFlags;
    uint64_t findType;
    uint64_t findPara;
    uint64_t prevChainContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CHAIN_CONTEXT WINAPI CertFindChainInStore(HCERTSTORE store, DWORD certEncodingType, DWORD findFlags, DWORD findType, const void *findPara, PCCERT_CHAIN_CONTEXT prevChainContext)
{
    struct qemu_CertFindChainInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDCHAININSTORE);
    call.store = (ULONG_PTR)store;
    call.certEncodingType = certEncodingType;
    call.findFlags = findFlags;
    call.findType = findType;
    call.findPara = (ULONG_PTR)findPara;
    call.prevChainContext = (ULONG_PTR)prevChainContext;

    qemu_syscall(&call.super);

    return (PCCERT_CHAIN_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindChainInStore(struct qemu_syscall *call)
{
    struct qemu_CertFindChainInStore *c = (struct qemu_CertFindChainInStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindChainInStore(QEMU_G2H(c->store), c->certEncodingType, c->findFlags, c->findType, QEMU_G2H(c->findPara), QEMU_G2H(c->prevChainContext)));
}

#endif

struct qemu_CertVerifyCertificateChainPolicy
{
    struct qemu_syscall super;
    uint64_t szPolicyOID;
    uint64_t pChainContext;
    uint64_t pPolicyPara;
    uint64_t pPolicyStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertVerifyCertificateChainPolicy(LPCSTR szPolicyOID, PCCERT_CHAIN_CONTEXT pChainContext, PCERT_CHAIN_POLICY_PARA pPolicyPara, PCERT_CHAIN_POLICY_STATUS pPolicyStatus)
{
    struct qemu_CertVerifyCertificateChainPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTVERIFYCERTIFICATECHAINPOLICY);
    call.szPolicyOID = (ULONG_PTR)szPolicyOID;
    call.pChainContext = (ULONG_PTR)pChainContext;
    call.pPolicyPara = (ULONG_PTR)pPolicyPara;
    call.pPolicyStatus = (ULONG_PTR)pPolicyStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertVerifyCertificateChainPolicy(struct qemu_syscall *call)
{
    struct qemu_CertVerifyCertificateChainPolicy *c = (struct qemu_CertVerifyCertificateChainPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertVerifyCertificateChainPolicy(QEMU_G2H(c->szPolicyOID), QEMU_G2H(c->pChainContext), QEMU_G2H(c->pPolicyPara), QEMU_G2H(c->pPolicyStatus));
}

#endif

