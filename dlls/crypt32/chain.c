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

WINBASEAPI BOOL WINAPI CertCreateCertificateChainEngine(PCERT_CHAIN_ENGINE_CONFIG pConfig,
        HCERTCHAINENGINE *phChainEngine)
{
    struct qemu_CertCreateCertificateChainEngine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATECERTIFICATECHAINENGINE);
    call.pConfig = (ULONG_PTR)pConfig;

    qemu_syscall(&call.super);
    if (call.phChainEngine != 1)
        *phChainEngine = (HCERTCHAINENGINE)(ULONG_PTR)call.phChainEngine;

    return call.super.iret;
}

#else

struct qemu_CERT_CHAIN_ENGINE_CONFIG_NO_EXCLUSIVE_ROOT
{
    DWORD       cbSize;
    qemu_ptr    hRestrictedRoot;
    qemu_ptr    hRestrictedTrust;
    qemu_ptr    hRestrictedOther;
    DWORD       cAdditionalStore;
    qemu_ptr    rghAdditionalStore;
    DWORD       dwFlags;
    DWORD       dwUrlRetrievalTimeout;
    DWORD       MaximumCachedCertificates;
    DWORD       CycleDetectionModulus;
};

void qemu_CertCreateCertificateChainEngine(struct qemu_syscall *call)
{
    struct qemu_CertCreateCertificateChainEngine *c = (struct qemu_CertCreateCertificateChainEngine *)call;
    HCERTCHAINENGINE engine = (HCERTCHAINENGINE)1; /* Assume we're not getting unaligned pointers */
    CERT_CHAIN_ENGINE_CONFIG stack, *cfg = &stack;
    struct qemu_CERT_CHAIN_ENGINE_CONFIG *cfg32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    cfg = QEMU_G2H(c->pConfig);
#else
    cfg32 = QEMU_G2H(c->pConfig);
    if (!cfg32)
        cfg = NULL;
    else if(cfg32->cbSize != sizeof(*cfg32)
            && cfg32->cbSize != sizeof(struct qemu_CERT_CHAIN_ENGINE_CONFIG_NO_EXCLUSIVE_ROOT))
        cfg->cbSize = 0;
    else
        CERT_CHAIN_ENGINE_CONFIG_g2h(cfg, cfg32);
#endif

    c->super.iret = CertCreateCertificateChainEngine(cfg, &engine);
    c->phChainEngine = QEMU_H2G(engine);
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
    WINE_TRACE("\n");
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

WINBASEAPI BOOL WINAPI CertGetCertificateChain(HCERTCHAINENGINE hChainEngine, PCCERT_CONTEXT pCertContext,
        LPFILETIME pTime, HCERTSTORE hAdditionalStore, PCERT_CHAIN_PARA pChainPara, DWORD dwFlags,
        LPVOID pvReserved, PCCERT_CHAIN_CONTEXT* ppChainContext)
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
    const CERT_CONTEXT *context;
    struct qemu_cert_context *context32;
    struct qemu_CERT_CHAIN_PARA *para32;
    CERT_CHAIN_PARA para_stack, *para = &para_stack;
    const CERT_CHAIN_CONTEXT *chain_stack = (const CERT_CHAIN_CONTEXT *)0x1;
    const CERT_CHAIN_CONTEXT **chain64;
    qemu_ptr *chain32;
    struct qemu_cert_chain_context *chain_impl;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    context = QEMU_G2H(c->pCertContext);
    para = QEMU_G2H(c->pChainPara);
    chain64 = QEMU_G2H(c->ppChainContext);
#else
    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    context = context32 ? context32->cert64 : NULL;

    para32 = QEMU_G2H(c->pChainPara);
    if (!para32)
        para = NULL;
    else if (para32->cbSize != sizeof(*para32))
        para->cbSize = 0;
    else
        CERT_CHAIN_PARA_g2h(para, para32);

    chain32 = QEMU_G2H(c->ppChainContext);
    if (chain32)
        chain64 = &chain_stack;
    else
        chain64 = NULL;
#endif

    c->super.iret = CertGetCertificateChain(QEMU_G2H(c->hChainEngine), context,
            QEMU_G2H(c->pTime), cert_store_g2h(c->hAdditionalStore), para, c->dwFlags,
            QEMU_G2H(c->pvReserved), chain64);

#if GUEST_BIT != HOST_BIT
    if (chain_stack && chain_stack != (const CERT_CHAIN_CONTEXT *)0x1)
    {
        /* FIXME: I suppose that for two identical invocations of this function I am supposed
         * to return the same chain. */
        struct qemu_CERT_SIMPLE_CHAIN *simple_chain;
        struct qemu_CERT_CHAIN_ELEMENT *element;

        chain_impl = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*chain_impl));
        if (!chain_impl)
            WINE_ERR("Out of memory\n");

        chain_impl->context64 = chain_stack;
        chain_impl->ref = 1;
        CERT_CHAIN_CONTEXT_h2g(&chain_impl->context32, chain_stack);

        if (chain_stack->rgpChain)
        {
            unsigned int i, j;
            qemu_ptr *ptrs, *ptrs2;
            struct qemu_cert_context *cert_context;

            ptrs = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                    sizeof(*simple_chain) * chain_stack->cChain + sizeof(qemu_ptr) * chain_stack->cChain);
            if (!ptrs)
                WINE_ERR("Out of memory\n");
            simple_chain = (struct qemu_CERT_SIMPLE_CHAIN *)&ptrs[chain_stack->cChain];

            for (i = 0; i < chain_stack->cChain; ++i)
            {
                if (chain_stack->rgpChain[i]->pTrustListInfo)
                    WINE_FIXME("CERT_SIMPLE_CHAIN.pTrustListInfo not handled yet.\n");
                CERT_SIMPLE_CHAIN_h2g(&simple_chain[i], chain_stack->rgpChain[i]);

                ptrs2 = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                        sizeof(*element) * simple_chain[i].cElement + sizeof(qemu_ptr) * simple_chain[i].cElement);
                if (!ptrs2)
                    WINE_ERR("Out of memory\n");
                element = (struct qemu_CERT_CHAIN_ELEMENT *)&ptrs2[simple_chain[i].cElement];

                for (j = 0; j < simple_chain[i].cElement; j++)
                {
                    if (chain_stack->rgpChain[i]->rgpElement[j]->pRevocationInfo)
                        WINE_FIXME("CERT_CHAIN_ELEMENT.pRevocationInfo not handled yet.\n");
                    if (chain_stack->rgpChain[i]->rgpElement[j]->pIssuanceUsage)
                        WINE_FIXME("CERT_CHAIN_ELEMENT.pIssuanceUsage not handled yet.\n");
                    if (chain_stack->rgpChain[i]->rgpElement[j]->pApplicationUsage)
                        WINE_FIXME("CERT_CHAIN_ELEMENT.pApplicationUsage not handled yet.\n");

                    CERT_CHAIN_ELEMENT_h2g(&element[j], chain_stack->rgpChain[i]->rgpElement[j]);
                    cert_context = context32_create(chain_stack->rgpChain[i]->rgpElement[j]->pCertContext);
                    element[j].pCertContext = QEMU_H2G(&cert_context->cert32);

                    ptrs2[j] = QEMU_H2G(&element[j]);
                }

                simple_chain[i].rgpElement = QEMU_H2G(ptrs2);
                ptrs[i] = QEMU_H2G(&simple_chain[i]);
            }

            chain_impl->context32.rgpChain = QEMU_H2G(ptrs);
        }

        if (chain_stack->cLowerQualityChainContext)
        {
            WINE_FIXME("Lower quality chains not handled yet.\n");
            chain_impl->context32.cLowerQualityChainContext = 0;
        }

        *chain32 = QEMU_H2G(chain_impl);
    }
    else if (!chain_stack)
    {
        *chain32 = 0;
    }
#endif
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
    struct qemu_cert_chain_context *chain32;
    const CERT_CHAIN_CONTEXT *chain64;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = QEMU_H2G(CertDuplicateCertificateChain(QEMU_G2H(c->pChainContext)));
    return;
#endif

    chain32 = QEMU_G2H(c->pChainContext);
    if (!chain32)
    {
        chain64 = CertDuplicateCertificateChain(NULL);
        if (chain64)
            WINE_ERR("Duplicating a NULL chain returned a non-NULL chain.\n");

        c->super.iret = QEMU_H2G(chain64);
        return;
    }

    chain64 = CertDuplicateCertificateChain(chain32->context64);
    if (chain64 != chain32->context64)
        WINE_ERR("CertDuplicateCertificateChain returned a different pointer\n");

    InterlockedIncrement(&chain32->ref);
    c->super.iret = c->pChainContext;
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
    struct qemu_cert_chain_context *chain32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    CertFreeCertificateChain(QEMU_G2H(c->pChainContext));
    return;
#endif

    chain32 = QEMU_G2H(c->pChainContext);
    if (!chain32)
    {
        CertFreeCertificateChain(NULL);
        return;
    }
    CertFreeCertificateChain(chain32->context64);
    if (InterlockedDecrement(&chain32->ref) == 0)
    {
        if (chain32->context32.rgpChain)
        {
            qemu_ptr *chains = QEMU_G2H((ULONG_PTR)chain32->context32.rgpChain);
            unsigned int i;

            for (i = 0; i < chain32->context32.cChain; ++i)
            {
                struct qemu_CERT_SIMPLE_CHAIN *elem = QEMU_G2H((ULONG_PTR)chains[i]);
                /* FIXME: Do I have to decref elem->rgpElement[j]->pCertContext ? */
                HeapFree(GetProcessHeap(), 0, QEMU_G2H((ULONG_PTR)elem->rgpElement));
            }

            HeapFree(GetProcessHeap(), 0, chains);
        }

        HeapFree(GetProcessHeap(), 0, chain32);
    }
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

WINBASEAPI PCCERT_CHAIN_CONTEXT WINAPI CertFindChainInStore(HCERTSTORE store, DWORD certEncodingType, DWORD findFlags,
        DWORD findType, const void *findPara, PCCERT_CHAIN_CONTEXT prevChainContext)
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
    /* The Wine implementation is a stub at the time of the writing of this comment. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindChainInStore(QEMU_G2H(c->store), c->certEncodingType, c->findFlags, c->findType,
            QEMU_G2H(c->findPara), QEMU_G2H(c->prevChainContext)));
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

WINBASEAPI BOOL WINAPI CertVerifyCertificateChainPolicy(LPCSTR szPolicyOID, PCCERT_CHAIN_CONTEXT pChainContext,
        PCERT_CHAIN_POLICY_PARA pPolicyPara, PCERT_CHAIN_POLICY_STATUS pPolicyStatus)
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
    CERT_CHAIN_POLICY_STATUS status = {0};
    struct qemu_CERT_CHAIN_POLICY_STATUS *status32;
    CERT_CHAIN_POLICY_PARA para;
    struct qemu_CERT_CHAIN_POLICY_PARA *para32;
    CERT_CHAIN_CONTEXT context;
    CERT_SIMPLE_CHAIN *chain64;
    const struct qemu_CERT_CHAIN_CONTEXT *context32;
    unsigned int i, j, chain_count, elem_count;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = CertVerifyCertificateChainPolicy(QEMU_G2H(c->szPolicyOID), QEMU_G2H(c->pChainContext),
            QEMU_G2H(c->pPolicyPara), QEMU_G2H(c->pPolicyStatus));
    return;
#endif

    status32 = QEMU_G2H(c->pPolicyStatus);
    para32 = QEMU_G2H(c->pPolicyPara);
    context32 = QEMU_G2H(c->pChainContext);

    if (para32)
    {
        CERT_CHAIN_POLICY_PARA_g2h(&para, para32);
        if (para.pvExtraPolicyPara)
        {
            WINE_FIXME("Convert pvExtraPolicyPara.\n");
            para.pvExtraPolicyPara = NULL;
        }
    }

    if (context32)
    {
        /* Don't rely on context32 pointing to a qemu_cert_chain_context. */
        qemu_ptr *chains32, *elem32;
        CERT_SIMPLE_CHAIN **ptr_array;
        CERT_CHAIN_ELEMENT **elem_array;
        CERT_CHAIN_ELEMENT *elem64;

        CERT_CHAIN_CONTEXT_g2h(&context, context32);

        if (context.rgpLowerQualityChainContext)
        {
            WINE_FIXME("Lower quality contexts not supported.\n");
            context.rgpLowerQualityChainContext = NULL;
            context.cLowerQualityChainContext = 0;
        }

        if (context.rgpChain)
        {
            chains32 = (qemu_ptr *)context.rgpChain;
            chain_count = context.cChain;

            ptr_array = HeapAlloc(GetProcessHeap(), 0,
                    (sizeof(*ptr_array) + sizeof(*chain64)) * chain_count);
            if (!ptr_array)
                WINE_ERR("Out of memory\n");
            chain64 = (CERT_SIMPLE_CHAIN *)&ptr_array[chain_count];

            for (i = 0; i < chain_count; ++i)
            {
                ptr_array[i] = &chain64[i];
                CERT_SIMPLE_CHAIN_g2h(&chain64[i], QEMU_G2H((ULONG_PTR)chains32[i]));
                elem32 = (qemu_ptr *)chain64[i].rgpElement;

                elem_count = chain64[i].cElement;
                if (chain64[i].pTrustListInfo)
                {
                    WINE_FIXME("CERT_SIMPLE_CHAIN.pTrustListInfo not supported yet.\n");
                    chain64[i].pTrustListInfo = NULL;
                }

                elem_array = HeapAlloc(GetProcessHeap(), 0,
                        (sizeof(*elem_array) + sizeof(*elem64)) * elem_count);
                if (!elem_array)
                    WINE_ERR("Out of memory\n");
                elem64 = (CERT_CHAIN_ELEMENT *)&elem_array[elem_count];

                for (j = 0; j < elem_count; ++j)
                {
                    struct qemu_cert_context *cert_context;

                    elem_array[j] = &elem64[j];
                    CERT_CHAIN_ELEMENT_g2h(&elem64[j], QEMU_G2H((ULONG_PTR)elem32[j]));
                    cert_context = context_impl_from_context32(QEMU_G2H(elem64[j].pCertContext));
                    elem64[j].pCertContext = cert_context ? cert_context->cert64 : NULL;
                }

                chain64[i].rgpElement = elem_array;
            }
            context.rgpChain = ptr_array;
        }
    }

    c->super.iret = CertVerifyCertificateChainPolicy(QEMU_G2H(c->szPolicyOID), para32 ? &context : NULL,
            para32 ? &para : NULL, status32 ? &status : NULL);

    if (status32)
    {
        /* Wine currently never sets this. */
        if (status.pvExtraPolicyStatus)
            WINE_FIXME("CERT_CHAIN_POLICY_STATUS.pvExtraPolicyStatus not handled yet.\n");
        CERT_CHAIN_POLICY_STATUS_h2g(status32, &status);
    }

    if (context32)
    {
        for (i = 0; i < chain_count; ++i)
            HeapFree(GetProcessHeap(), 0, chain64[i].rgpElement);
        HeapFree(GetProcessHeap(), 0, context.rgpChain);
    }
}

#endif

