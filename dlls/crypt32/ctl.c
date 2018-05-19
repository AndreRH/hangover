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

struct qemu_CertAddCTLContextToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pCtlContext;
    uint64_t dwAddDisposition;
    uint64_t ppStoreContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddCTLContextToStore(HCERTSTORE hCertStore, PCCTL_CONTEXT pCtlContext, DWORD dwAddDisposition, PCCTL_CONTEXT* ppStoreContext)
{
    struct qemu_CertAddCTLContextToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDCTLCONTEXTTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pCtlContext = (ULONG_PTR)pCtlContext;
    call.dwAddDisposition = dwAddDisposition;
    call.ppStoreContext = (ULONG_PTR)ppStoreContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddCTLContextToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddCTLContextToStore *c = (struct qemu_CertAddCTLContextToStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddCTLContextToStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pCtlContext), c->dwAddDisposition, QEMU_G2H(c->ppStoreContext));
}

#endif

struct qemu_CertAddEncodedCTLToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwMsgAndCertEncodingType;
    uint64_t pbCtlEncoded;
    uint64_t cbCtlEncoded;
    uint64_t dwAddDisposition;
    uint64_t ppCtlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddEncodedCTLToStore(HCERTSTORE hCertStore, DWORD dwMsgAndCertEncodingType, const BYTE *pbCtlEncoded, DWORD cbCtlEncoded, DWORD dwAddDisposition, PCCTL_CONTEXT *ppCtlContext)
{
    struct qemu_CertAddEncodedCTLToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDENCODEDCTLTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwMsgAndCertEncodingType = dwMsgAndCertEncodingType;
    call.pbCtlEncoded = (ULONG_PTR)pbCtlEncoded;
    call.cbCtlEncoded = cbCtlEncoded;
    call.dwAddDisposition = dwAddDisposition;
    call.ppCtlContext = (ULONG_PTR)ppCtlContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddEncodedCTLToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddEncodedCTLToStore *c = (struct qemu_CertAddEncodedCTLToStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddEncodedCTLToStore(QEMU_G2H(c->hCertStore), c->dwMsgAndCertEncodingType, QEMU_G2H(c->pbCtlEncoded), c->cbCtlEncoded, c->dwAddDisposition, QEMU_G2H(c->ppCtlContext));
}

#endif

struct qemu_CertEnumCTLsInStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pPrev;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCTL_CONTEXT WINAPI CertEnumCTLsInStore(HCERTSTORE hCertStore, PCCTL_CONTEXT pPrev)
{
    struct qemu_CertEnumCTLsInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMCTLSINSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pPrev = (ULONG_PTR)pPrev;

    qemu_syscall(&call.super);

    return (PCCTL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertEnumCTLsInStore(struct qemu_syscall *call)
{
    struct qemu_CertEnumCTLsInStore *c = (struct qemu_CertEnumCTLsInStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertEnumCTLsInStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pPrev)));
}

#endif

struct qemu_CertFindCTLInStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwCertEncodingType;
    uint64_t dwFindFlags;
    uint64_t dwFindType;
    uint64_t pvFindPara;
    uint64_t pPrevCtlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCTL_CONTEXT WINAPI CertFindCTLInStore(HCERTSTORE hCertStore, DWORD dwCertEncodingType, DWORD dwFindFlags, DWORD dwFindType, const void *pvFindPara, PCCTL_CONTEXT pPrevCtlContext)
{
    struct qemu_CertFindCTLInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFINDCTLINSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwCertEncodingType = dwCertEncodingType;
    call.dwFindFlags = dwFindFlags;
    call.dwFindType = dwFindType;
    call.pvFindPara = (ULONG_PTR)pvFindPara;
    call.pPrevCtlContext = (ULONG_PTR)pPrevCtlContext;

    qemu_syscall(&call.super);

    return (PCCTL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertFindCTLInStore(struct qemu_syscall *call)
{
    struct qemu_CertFindCTLInStore *c = (struct qemu_CertFindCTLInStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertFindCTLInStore(QEMU_G2H(c->hCertStore), c->dwCertEncodingType, c->dwFindFlags, c->dwFindType, QEMU_G2H(c->pvFindPara), QEMU_G2H(c->pPrevCtlContext)));
}

#endif

struct qemu_CertDeleteCTLFromStore
{
    struct qemu_syscall super;
    uint64_t pCtlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertDeleteCTLFromStore(PCCTL_CONTEXT pCtlContext)
{
    struct qemu_CertDeleteCTLFromStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDELETECTLFROMSTORE);
    call.pCtlContext = (ULONG_PTR)pCtlContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertDeleteCTLFromStore(struct qemu_syscall *call)
{
    struct qemu_CertDeleteCTLFromStore *c = (struct qemu_CertDeleteCTLFromStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertDeleteCTLFromStore(QEMU_G2H(c->pCtlContext));
}

#endif

struct qemu_CertCreateCTLContext
{
    struct qemu_syscall super;
    uint64_t dwMsgAndCertEncodingType;
    uint64_t pbCtlEncoded;
    uint64_t cbCtlEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCTL_CONTEXT WINAPI CertCreateCTLContext(DWORD dwMsgAndCertEncodingType, const BYTE *pbCtlEncoded, DWORD cbCtlEncoded)
{
    struct qemu_CertCreateCTLContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCREATECTLCONTEXT);
    call.dwMsgAndCertEncodingType = dwMsgAndCertEncodingType;
    call.pbCtlEncoded = (ULONG_PTR)pbCtlEncoded;
    call.cbCtlEncoded = cbCtlEncoded;

    qemu_syscall(&call.super);

    return (PCCTL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertCreateCTLContext(struct qemu_syscall *call)
{
    struct qemu_CertCreateCTLContext *c = (struct qemu_CertCreateCTLContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertCreateCTLContext(c->dwMsgAndCertEncodingType, QEMU_G2H(c->pbCtlEncoded), c->cbCtlEncoded));
}

#endif

struct qemu_CertDuplicateCTLContext
{
    struct qemu_syscall super;
    uint64_t pCtlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCTL_CONTEXT WINAPI CertDuplicateCTLContext(PCCTL_CONTEXT pCtlContext)
{
    struct qemu_CertDuplicateCTLContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDUPLICATECTLCONTEXT);
    call.pCtlContext = (ULONG_PTR)pCtlContext;

    qemu_syscall(&call.super);

    return (PCCTL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertDuplicateCTLContext(struct qemu_syscall *call)
{
    struct qemu_CertDuplicateCTLContext *c = (struct qemu_CertDuplicateCTLContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertDuplicateCTLContext(QEMU_G2H(c->pCtlContext)));
}

#endif

struct qemu_CertFreeCTLContext
{
    struct qemu_syscall super;
    uint64_t pCTLContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertFreeCTLContext(PCCTL_CONTEXT pCTLContext)
{
    struct qemu_CertFreeCTLContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTFREECTLCONTEXT);
    call.pCTLContext = (ULONG_PTR)pCTLContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertFreeCTLContext(struct qemu_syscall *call)
{
    struct qemu_CertFreeCTLContext *c = (struct qemu_CertFreeCTLContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertFreeCTLContext(QEMU_G2H(c->pCTLContext));
}

#endif

struct qemu_CertEnumCTLContextProperties
{
    struct qemu_syscall super;
    uint64_t pCTLContext;
    uint64_t dwPropId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertEnumCTLContextProperties(PCCTL_CONTEXT pCTLContext, DWORD dwPropId)
{
    struct qemu_CertEnumCTLContextProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMCTLCONTEXTPROPERTIES);
    call.pCTLContext = (ULONG_PTR)pCTLContext;
    call.dwPropId = dwPropId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertEnumCTLContextProperties(struct qemu_syscall *call)
{
    struct qemu_CertEnumCTLContextProperties *c = (struct qemu_CertEnumCTLContextProperties *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertEnumCTLContextProperties(QEMU_G2H(c->pCTLContext), c->dwPropId);
}

#endif

struct qemu_CertGetCTLContextProperty
{
    struct qemu_syscall super;
    uint64_t pCTLContext;
    uint64_t dwPropId;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetCTLContextProperty(PCCTL_CONTEXT pCTLContext, DWORD dwPropId, void *pvData, DWORD *pcbData)
{
    struct qemu_CertGetCTLContextProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETCTLCONTEXTPROPERTY);
    call.pCTLContext = (ULONG_PTR)pCTLContext;
    call.dwPropId = dwPropId;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetCTLContextProperty(struct qemu_syscall *call)
{
    struct qemu_CertGetCTLContextProperty *c = (struct qemu_CertGetCTLContextProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetCTLContextProperty(QEMU_G2H(c->pCTLContext), c->dwPropId, QEMU_G2H(c->pvData), QEMU_G2H(c->pcbData));
}

#endif

struct qemu_CertSetCTLContextProperty
{
    struct qemu_syscall super;
    uint64_t pCTLContext;
    uint64_t dwPropId;
    uint64_t dwFlags;
    uint64_t pvData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSetCTLContextProperty(PCCTL_CONTEXT pCTLContext, DWORD dwPropId, DWORD dwFlags, const void *pvData)
{
    struct qemu_CertSetCTLContextProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSETCTLCONTEXTPROPERTY);
    call.pCTLContext = (ULONG_PTR)pCTLContext;
    call.dwPropId = dwPropId;
    call.dwFlags = dwFlags;
    call.pvData = (ULONG_PTR)pvData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSetCTLContextProperty(struct qemu_syscall *call)
{
    struct qemu_CertSetCTLContextProperty *c = (struct qemu_CertSetCTLContextProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSetCTLContextProperty(QEMU_G2H(c->pCTLContext), c->dwPropId, c->dwFlags, QEMU_G2H(c->pvData));
}

#endif

