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

struct qemu_I_CertUpdateStore
{
    struct qemu_syscall super;
    uint64_t store1;
    uint64_t store2;
    uint64_t unk0;
    uint64_t unk1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CertUpdateStore(HCERTSTORE store1, HCERTSTORE store2, DWORD unk0, DWORD unk1)
{
    struct qemu_I_CertUpdateStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CERTUPDATESTORE);
    call.store1 = (ULONG_PTR)store1;
    call.store2 = (ULONG_PTR)store2;
    call.unk0 = unk0;
    call.unk1 = unk1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CertUpdateStore(HCERTSTORE store1, HCERTSTORE store2, DWORD unk0, DWORD unk1);
void qemu_I_CertUpdateStore(struct qemu_syscall *call)
{
    struct qemu_I_CertUpdateStore *c = (struct qemu_I_CertUpdateStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CertUpdateStore(QEMU_G2H(c->store1), QEMU_G2H(c->store2), c->unk0, c->unk1);
}

#endif

struct qemu_CertOpenStore
{
    struct qemu_syscall super;
    uint64_t lpszStoreProvider;
    uint64_t dwMsgAndCertEncodingType;
    uint64_t hCryptProv;
    uint64_t dwFlags;
    uint64_t pvPara;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCERTSTORE WINAPI CertOpenStore(LPCSTR lpszStoreProvider, DWORD dwMsgAndCertEncodingType,
        HCRYPTPROV_LEGACY hCryptProv, DWORD dwFlags, const void* pvPara)
{
    struct qemu_CertOpenStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTOPENSTORE);
    call.lpszStoreProvider = (ULONG_PTR)lpszStoreProvider;
    call.dwMsgAndCertEncodingType = dwMsgAndCertEncodingType;
    call.hCryptProv = hCryptProv;
    call.dwFlags = dwFlags;
    call.pvPara = (ULONG_PTR)pvPara;

    qemu_syscall(&call.super);

    return (HCERTSTORE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertOpenStore(struct qemu_syscall *call)
{
    struct qemu_CertOpenStore *c = (struct qemu_CertOpenStore *)call;

    /* pvPara looks like either a HANDLE or filename, depending on the store type. */
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(CertOpenStore(QEMU_G2H(c->lpszStoreProvider), c->dwMsgAndCertEncodingType,
            c->hCryptProv, c->dwFlags, QEMU_G2H(c->pvPara)));
}

#endif

struct qemu_CertOpenSystemStoreA
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t szSubSystemProtocol;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCERTSTORE WINAPI CertOpenSystemStoreA(HCRYPTPROV_LEGACY hProv, LPCSTR szSubSystemProtocol)
{
    struct qemu_CertOpenSystemStoreA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTOPENSYSTEMSTOREA);
    call.hProv = hProv;
    call.szSubSystemProtocol = (ULONG_PTR)szSubSystemProtocol;

    qemu_syscall(&call.super);

    return (HCERTSTORE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertOpenSystemStoreA(struct qemu_syscall *call)
{
    struct qemu_CertOpenSystemStoreA *c = (struct qemu_CertOpenSystemStoreA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertOpenSystemStoreA(c->hProv, QEMU_G2H(c->szSubSystemProtocol)));
}

#endif

struct qemu_CertOpenSystemStoreW
{
    struct qemu_syscall super;
    uint64_t hProv;
    uint64_t szSubSystemProtocol;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCERTSTORE WINAPI CertOpenSystemStoreW(HCRYPTPROV_LEGACY hProv, LPCWSTR szSubSystemProtocol)
{
    struct qemu_CertOpenSystemStoreW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTOPENSYSTEMSTOREW);
    call.hProv = hProv;
    call.szSubSystemProtocol = (ULONG_PTR)szSubSystemProtocol;

    qemu_syscall(&call.super);

    return (HCERTSTORE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertOpenSystemStoreW(struct qemu_syscall *call)
{
    struct qemu_CertOpenSystemStoreW *c = (struct qemu_CertOpenSystemStoreW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertOpenSystemStoreW(c->hProv, QEMU_G2H(c->szSubSystemProtocol)));
}

#endif

struct qemu_CertEnumCertificatesInStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pPrev;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCERT_CONTEXT WINAPI CertEnumCertificatesInStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pPrev)
{
    struct qemu_CertEnumCertificatesInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMCERTIFICATESINSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pPrev = (ULONG_PTR)pPrev;

    qemu_syscall(&call.super);

    return (PCCERT_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertEnumCertificatesInStore(struct qemu_syscall *call)
{
    struct qemu_CertEnumCertificatesInStore *c = (struct qemu_CertEnumCertificatesInStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertEnumCertificatesInStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pPrev)));
}

#endif

struct qemu_CertDeleteCertificateFromStore
{
    struct qemu_syscall super;
    uint64_t pCertContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertDeleteCertificateFromStore(PCCERT_CONTEXT pCertContext)
{
    struct qemu_CertDeleteCertificateFromStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDELETECERTIFICATEFROMSTORE);
    call.pCertContext = (ULONG_PTR)pCertContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertDeleteCertificateFromStore(struct qemu_syscall *call)
{
    struct qemu_CertDeleteCertificateFromStore *c = (struct qemu_CertDeleteCertificateFromStore *)call;
    struct qemu_cert_context *context32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    c->super.iret = CertDeleteCertificateFromStore(QEMU_G2H(c->pCertContext));
    return;
#endif

    context32 = context_impl_from_context32(QEMU_G2H(c->pCertContext));
    c->super.iret = CertDeleteCertificateFromStore(context32 ? context32->cert64 : NULL);
}

#endif

struct qemu_CertAddCRLContextToStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pCrlContext;
    uint64_t dwAddDisposition;
    uint64_t ppStoreContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertAddCRLContextToStore(HCERTSTORE hCertStore, PCCRL_CONTEXT pCrlContext, DWORD dwAddDisposition, PCCRL_CONTEXT* ppStoreContext)
{
    struct qemu_CertAddCRLContextToStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTADDCRLCONTEXTTOSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pCrlContext = (ULONG_PTR)pCrlContext;
    call.dwAddDisposition = dwAddDisposition;
    call.ppStoreContext = (ULONG_PTR)ppStoreContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertAddCRLContextToStore(struct qemu_syscall *call)
{
    struct qemu_CertAddCRLContextToStore *c = (struct qemu_CertAddCRLContextToStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertAddCRLContextToStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pCrlContext), c->dwAddDisposition, QEMU_G2H(c->ppStoreContext));
}

#endif

struct qemu_CertDeleteCRLFromStore
{
    struct qemu_syscall super;
    uint64_t pCrlContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertDeleteCRLFromStore(PCCRL_CONTEXT pCrlContext)
{
    struct qemu_CertDeleteCRLFromStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDELETECRLFROMSTORE);
    call.pCrlContext = (ULONG_PTR)pCrlContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertDeleteCRLFromStore(struct qemu_syscall *call)
{
    struct qemu_CertDeleteCRLFromStore *c = (struct qemu_CertDeleteCRLFromStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertDeleteCRLFromStore(QEMU_G2H(c->pCrlContext));
}

#endif

struct qemu_CertEnumCRLsInStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t pPrev;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCRL_CONTEXT WINAPI CertEnumCRLsInStore(HCERTSTORE hCertStore, PCCRL_CONTEXT pPrev)
{
    struct qemu_CertEnumCRLsInStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMCRLSINSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.pPrev = (ULONG_PTR)pPrev;

    qemu_syscall(&call.super);

    return (PCCRL_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertEnumCRLsInStore(struct qemu_syscall *call)
{
    struct qemu_CertEnumCRLsInStore *c = (struct qemu_CertEnumCRLsInStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertEnumCRLsInStore(QEMU_G2H(c->hCertStore), QEMU_G2H(c->pPrev)));
}

#endif

struct qemu_CertDuplicateStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCERTSTORE WINAPI CertDuplicateStore(HCERTSTORE hCertStore)
{
    struct qemu_CertDuplicateStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTDUPLICATESTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;

    qemu_syscall(&call.super);

    return (HCERTSTORE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertDuplicateStore(struct qemu_syscall *call)
{
    struct qemu_CertDuplicateStore *c = (struct qemu_CertDuplicateStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CertDuplicateStore(QEMU_G2H(c->hCertStore)));
}

#endif

struct qemu_CertCloseStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertCloseStore(HCERTSTORE hCertStore, DWORD dwFlags)
{
    struct qemu_CertCloseStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCLOSESTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertCloseStore(struct qemu_syscall *call)
{
    struct qemu_CertCloseStore *c = (struct qemu_CertCloseStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertCloseStore(QEMU_G2H(c->hCertStore), c->dwFlags);
}

#endif

struct qemu_CertControlStore
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwFlags;
    uint64_t dwCtrlType;
    uint64_t pvCtrlPara;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertControlStore(HCERTSTORE hCertStore, DWORD dwFlags, DWORD dwCtrlType, void const *pvCtrlPara)
{
    struct qemu_CertControlStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTCONTROLSTORE);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwFlags = dwFlags;
    call.dwCtrlType = dwCtrlType;
    call.pvCtrlPara = (ULONG_PTR)pvCtrlPara;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertControlStore(struct qemu_syscall *call)
{
    struct qemu_CertControlStore *c = (struct qemu_CertControlStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertControlStore(QEMU_G2H(c->hCertStore), c->dwFlags, c->dwCtrlType, QEMU_G2H(c->pvCtrlPara));
}

#endif

struct qemu_CertGetStoreProperty
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwPropId;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertGetStoreProperty(HCERTSTORE hCertStore, DWORD dwPropId, void *pvData, DWORD *pcbData)
{
    struct qemu_CertGetStoreProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETSTOREPROPERTY);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwPropId = dwPropId;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetStoreProperty(struct qemu_syscall *call)
{
    struct qemu_CertGetStoreProperty *c = (struct qemu_CertGetStoreProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetStoreProperty(QEMU_G2H(c->hCertStore), c->dwPropId, QEMU_G2H(c->pvData), QEMU_G2H(c->pcbData));
}

#endif

struct qemu_CertSetStoreProperty
{
    struct qemu_syscall super;
    uint64_t hCertStore;
    uint64_t dwPropId;
    uint64_t dwFlags;
    uint64_t pvData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertSetStoreProperty(HCERTSTORE hCertStore, DWORD dwPropId, DWORD dwFlags, const void *pvData)
{
    struct qemu_CertSetStoreProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSETSTOREPROPERTY);
    call.hCertStore = (ULONG_PTR)hCertStore;
    call.dwPropId = dwPropId;
    call.dwFlags = dwFlags;
    call.pvData = (ULONG_PTR)pvData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertSetStoreProperty(struct qemu_syscall *call)
{
    struct qemu_CertSetStoreProperty *c = (struct qemu_CertSetStoreProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertSetStoreProperty(QEMU_G2H(c->hCertStore), c->dwPropId, c->dwFlags, QEMU_G2H(c->pvData));
}

#endif

struct qemu_CertEnumSystemStore
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t pvSystemStoreLocationPara;
    uint64_t pvArg;
    uint64_t pfnEnum;
};

#ifdef QEMU_DLL_GUEST
// 
WINBASEAPI BOOL WINAPI CertEnumSystemStore(DWORD dwFlags, void *pvSystemStoreLocationPara, void *pvArg, PFN_CERT_ENUM_SYSTEM_STORE pfnEnum)
{
    struct qemu_CertEnumSystemStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMSYSTEMSTORE);
    call.dwFlags = dwFlags;
    call.pvSystemStoreLocationPara = (ULONG_PTR)pvSystemStoreLocationPara;
    call.pvArg = (ULONG_PTR)pvArg;
    call.pfnEnum = (ULONG_PTR)pfnEnum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertEnumSystemStore(struct qemu_syscall *call)
{
    struct qemu_CertEnumSystemStore *c = (struct qemu_CertEnumSystemStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertEnumSystemStore(c->dwFlags, QEMU_G2H(c->pvSystemStoreLocationPara), QEMU_G2H(c->pvArg), QEMU_G2H(c->pfnEnum));
}

#endif

struct qemu_CertEnumPhysicalStore
{
    struct qemu_syscall super;
    uint64_t pvSystemStore;
    uint64_t dwFlags;
    uint64_t pvArg;
    uint64_t pfnEnum;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertEnumPhysicalStore(const void *pvSystemStore, DWORD dwFlags, void *pvArg, PFN_CERT_ENUM_PHYSICAL_STORE pfnEnum)
{
    struct qemu_CertEnumPhysicalStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTENUMPHYSICALSTORE);
    call.pvSystemStore = (ULONG_PTR)pvSystemStore;
    call.dwFlags = dwFlags;
    call.pvArg = (ULONG_PTR)pvArg;
    call.pfnEnum = (ULONG_PTR)pfnEnum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertEnumPhysicalStore(struct qemu_syscall *call)
{
    struct qemu_CertEnumPhysicalStore *c = (struct qemu_CertEnumPhysicalStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertEnumPhysicalStore(QEMU_G2H(c->pvSystemStore), c->dwFlags, QEMU_G2H(c->pvArg), QEMU_G2H(c->pfnEnum));
}

#endif

struct qemu_CertRegisterPhysicalStore
{
    struct qemu_syscall super;
    uint64_t pvSystemStore;
    uint64_t dwFlags;
    uint64_t pwszStoreName;
    uint64_t pStoreInfo;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertRegisterPhysicalStore(const void *pvSystemStore, DWORD dwFlags, LPCWSTR pwszStoreName, PCERT_PHYSICAL_STORE_INFO pStoreInfo, void *pvReserved)
{
    struct qemu_CertRegisterPhysicalStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTREGISTERPHYSICALSTORE);
    call.pvSystemStore = (ULONG_PTR)pvSystemStore;
    call.dwFlags = dwFlags;
    call.pwszStoreName = (ULONG_PTR)pwszStoreName;
    call.pStoreInfo = (ULONG_PTR)pStoreInfo;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertRegisterPhysicalStore(struct qemu_syscall *call)
{
    struct qemu_CertRegisterPhysicalStore *c = (struct qemu_CertRegisterPhysicalStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertRegisterPhysicalStore(QEMU_G2H(c->pvSystemStore), c->dwFlags, QEMU_G2H(c->pwszStoreName), QEMU_G2H(c->pStoreInfo), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CertUnregisterPhysicalStore
{
    struct qemu_syscall super;
    uint64_t pvSystemStore;
    uint64_t dwFlags;
    uint64_t pwszStoreName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertUnregisterPhysicalStore(const void *pvSystemStore, DWORD dwFlags, LPCWSTR pwszStoreName)
{
    struct qemu_CertUnregisterPhysicalStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTUNREGISTERPHYSICALSTORE);
    call.pvSystemStore = (ULONG_PTR)pvSystemStore;
    call.dwFlags = dwFlags;
    call.pwszStoreName = (ULONG_PTR)pwszStoreName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertUnregisterPhysicalStore(struct qemu_syscall *call)
{
    struct qemu_CertUnregisterPhysicalStore *c = (struct qemu_CertUnregisterPhysicalStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertUnregisterPhysicalStore(QEMU_G2H(c->pvSystemStore), c->dwFlags, QEMU_G2H(c->pwszStoreName));
}

#endif

struct qemu_CertRegisterSystemStore
{
    struct qemu_syscall super;
    uint64_t pvSystemStore;
    uint64_t dwFlags;
    uint64_t pStoreInfo;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertRegisterSystemStore(const void *pvSystemStore, DWORD dwFlags, PCERT_SYSTEM_STORE_INFO pStoreInfo, void *pvReserved)
{
    struct qemu_CertRegisterSystemStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTREGISTERSYSTEMSTORE);
    call.pvSystemStore = (ULONG_PTR)pvSystemStore;
    call.dwFlags = dwFlags;
    call.pStoreInfo = (ULONG_PTR)pStoreInfo;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertRegisterSystemStore(struct qemu_syscall *call)
{
    struct qemu_CertRegisterSystemStore *c = (struct qemu_CertRegisterSystemStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertRegisterSystemStore(QEMU_G2H(c->pvSystemStore), c->dwFlags, QEMU_G2H(c->pStoreInfo), QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CertUnregisterSystemStore
{
    struct qemu_syscall super;
    uint64_t pvSystemStore;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertUnregisterSystemStore(const void *pvSystemStore, DWORD dwFlags)
{
    struct qemu_CertUnregisterSystemStore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTUNREGISTERSYSTEMSTORE);
    call.pvSystemStore = (ULONG_PTR)pvSystemStore;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertUnregisterSystemStore(struct qemu_syscall *call)
{
    struct qemu_CertUnregisterSystemStore *c = (struct qemu_CertUnregisterSystemStore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertUnregisterSystemStore(QEMU_G2H(c->pvSystemStore), c->dwFlags);
}

#endif

