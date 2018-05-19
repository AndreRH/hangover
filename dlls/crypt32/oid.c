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

struct qemu_CryptInitOIDFunctionSet
{
    struct qemu_syscall super;
    uint64_t pszFuncName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCRYPTOIDFUNCSET WINAPI CryptInitOIDFunctionSet(LPCSTR pszFuncName, DWORD dwFlags)
{
    struct qemu_CryptInitOIDFunctionSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTINITOIDFUNCTIONSET);
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return (HCRYPTOIDFUNCSET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptInitOIDFunctionSet(struct qemu_syscall *call)
{
    struct qemu_CryptInitOIDFunctionSet *c = (struct qemu_CryptInitOIDFunctionSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CryptInitOIDFunctionSet(QEMU_G2H(c->pszFuncName), c->dwFlags));
}

#endif

struct qemu_CryptGetDefaultOIDDllList
{
    struct qemu_syscall super;
    uint64_t hFuncSet;
    uint64_t dwEncodingType;
    uint64_t pwszDllList;
    uint64_t pcchDllList;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetDefaultOIDDllList(HCRYPTOIDFUNCSET hFuncSet, DWORD dwEncodingType, LPWSTR pwszDllList, DWORD *pcchDllList)
{
    struct qemu_CryptGetDefaultOIDDllList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETDEFAULTOIDDLLLIST);
    call.hFuncSet = (ULONG_PTR)hFuncSet;
    call.dwEncodingType = dwEncodingType;
    call.pwszDllList = (ULONG_PTR)pwszDllList;
    call.pcchDllList = (ULONG_PTR)pcchDllList;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetDefaultOIDDllList(struct qemu_syscall *call)
{
    struct qemu_CryptGetDefaultOIDDllList *c = (struct qemu_CryptGetDefaultOIDDllList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetDefaultOIDDllList(QEMU_G2H(c->hFuncSet), c->dwEncodingType, QEMU_G2H(c->pwszDllList), QEMU_G2H(c->pcchDllList));
}

#endif

struct qemu_CryptInstallOIDFunctionAddress
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t cFuncEntry;
    uint64_t rgFuncEntry;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptInstallOIDFunctionAddress(HMODULE hModule, DWORD dwEncodingType, LPCSTR pszFuncName, DWORD cFuncEntry, const CRYPT_OID_FUNC_ENTRY rgFuncEntry[], DWORD dwFlags)
{
    struct qemu_CryptInstallOIDFunctionAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTINSTALLOIDFUNCTIONADDRESS);
    call.hModule = (ULONG_PTR)hModule;
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.cFuncEntry = cFuncEntry;
    call.rgFuncEntry = (ULONG_PTR)rgFuncEntry;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptInstallOIDFunctionAddress(struct qemu_syscall *call)
{
    struct qemu_CryptInstallOIDFunctionAddress *c = (struct qemu_CryptInstallOIDFunctionAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptInstallOIDFunctionAddress(QEMU_G2H(c->hModule), c->dwEncodingType, QEMU_G2H(c->pszFuncName), c->cFuncEntry, QEMU_G2H(c->rgFuncEntry), c->dwFlags);
}

#endif

struct qemu_CryptGetOIDFunctionAddress
{
    struct qemu_syscall super;
    uint64_t hFuncSet;
    uint64_t dwEncodingType;
    uint64_t pszOID;
    uint64_t dwFlags;
    uint64_t ppvFuncAddr;
    uint64_t phFuncAddr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetOIDFunctionAddress(HCRYPTOIDFUNCSET hFuncSet, DWORD dwEncodingType, LPCSTR pszOID, DWORD dwFlags, void **ppvFuncAddr, HCRYPTOIDFUNCADDR *phFuncAddr)
{
    struct qemu_CryptGetOIDFunctionAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETOIDFUNCTIONADDRESS);
    call.hFuncSet = (ULONG_PTR)hFuncSet;
    call.dwEncodingType = dwEncodingType;
    call.pszOID = (ULONG_PTR)pszOID;
    call.dwFlags = dwFlags;
    call.ppvFuncAddr = (ULONG_PTR)ppvFuncAddr;
    call.phFuncAddr = (ULONG_PTR)phFuncAddr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetOIDFunctionAddress(struct qemu_syscall *call)
{
    struct qemu_CryptGetOIDFunctionAddress *c = (struct qemu_CryptGetOIDFunctionAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetOIDFunctionAddress(QEMU_G2H(c->hFuncSet), c->dwEncodingType, QEMU_G2H(c->pszOID), c->dwFlags, QEMU_G2H(c->ppvFuncAddr), QEMU_G2H(c->phFuncAddr));
}

#endif

struct qemu_CryptFreeOIDFunctionAddress
{
    struct qemu_syscall super;
    uint64_t hFuncAddr;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptFreeOIDFunctionAddress(HCRYPTOIDFUNCADDR hFuncAddr, DWORD dwFlags)
{
    struct qemu_CryptFreeOIDFunctionAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTFREEOIDFUNCTIONADDRESS);
    call.hFuncAddr = (ULONG_PTR)hFuncAddr;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptFreeOIDFunctionAddress(struct qemu_syscall *call)
{
    struct qemu_CryptFreeOIDFunctionAddress *c = (struct qemu_CryptFreeOIDFunctionAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptFreeOIDFunctionAddress(QEMU_G2H(c->hFuncAddr), c->dwFlags);
}

#endif

struct qemu_CryptGetDefaultOIDFunctionAddress
{
    struct qemu_syscall super;
    uint64_t hFuncSet;
    uint64_t dwEncodingType;
    uint64_t pwszDll;
    uint64_t dwFlags;
    uint64_t ppvFuncAddr;
    uint64_t phFuncAddr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetDefaultOIDFunctionAddress(HCRYPTOIDFUNCSET hFuncSet, DWORD dwEncodingType, LPCWSTR pwszDll, DWORD dwFlags, void **ppvFuncAddr, HCRYPTOIDFUNCADDR *phFuncAddr)
{
    struct qemu_CryptGetDefaultOIDFunctionAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETDEFAULTOIDFUNCTIONADDRESS);
    call.hFuncSet = (ULONG_PTR)hFuncSet;
    call.dwEncodingType = dwEncodingType;
    call.pwszDll = (ULONG_PTR)pwszDll;
    call.dwFlags = dwFlags;
    call.ppvFuncAddr = (ULONG_PTR)ppvFuncAddr;
    call.phFuncAddr = (ULONG_PTR)phFuncAddr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetDefaultOIDFunctionAddress(struct qemu_syscall *call)
{
    struct qemu_CryptGetDefaultOIDFunctionAddress *c = (struct qemu_CryptGetDefaultOIDFunctionAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetDefaultOIDFunctionAddress(QEMU_G2H(c->hFuncSet), c->dwEncodingType, QEMU_G2H(c->pwszDll), c->dwFlags, QEMU_G2H(c->ppvFuncAddr), QEMU_G2H(c->phFuncAddr));
}

#endif

struct qemu_CryptRegisterOIDFunction
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t pszOID;
    uint64_t pwszDll;
    uint64_t pszOverrideFuncName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptRegisterOIDFunction(DWORD dwEncodingType, LPCSTR pszFuncName, LPCSTR pszOID, LPCWSTR pwszDll, LPCSTR pszOverrideFuncName)
{
    struct qemu_CryptRegisterOIDFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTREGISTEROIDFUNCTION);
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.pszOID = (ULONG_PTR)pszOID;
    call.pwszDll = (ULONG_PTR)pwszDll;
    call.pszOverrideFuncName = (ULONG_PTR)pszOverrideFuncName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptRegisterOIDFunction(struct qemu_syscall *call)
{
    struct qemu_CryptRegisterOIDFunction *c = (struct qemu_CryptRegisterOIDFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptRegisterOIDFunction(c->dwEncodingType, QEMU_G2H(c->pszFuncName), QEMU_G2H(c->pszOID), QEMU_G2H(c->pwszDll), QEMU_G2H(c->pszOverrideFuncName));
}

#endif

struct qemu_CryptRegisterOIDInfo
{
    struct qemu_syscall super;
    uint64_t pInfo;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptRegisterOIDInfo(PCCRYPT_OID_INFO pInfo, DWORD dwFlags)
{
    struct qemu_CryptRegisterOIDInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTREGISTEROIDINFO);
    call.pInfo = (ULONG_PTR)pInfo;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptRegisterOIDInfo(struct qemu_syscall *call)
{
    struct qemu_CryptRegisterOIDInfo *c = (struct qemu_CryptRegisterOIDInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptRegisterOIDInfo(QEMU_G2H(c->pInfo), c->dwFlags);
}

#endif

struct qemu_CryptUnregisterOIDFunction
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t pszOID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptUnregisterOIDFunction(DWORD dwEncodingType, LPCSTR pszFuncName, LPCSTR pszOID)
{
    struct qemu_CryptUnregisterOIDFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTUNREGISTEROIDFUNCTION);
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.pszOID = (ULONG_PTR)pszOID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptUnregisterOIDFunction(struct qemu_syscall *call)
{
    struct qemu_CryptUnregisterOIDFunction *c = (struct qemu_CryptUnregisterOIDFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptUnregisterOIDFunction(c->dwEncodingType, QEMU_G2H(c->pszFuncName), QEMU_G2H(c->pszOID));
}

#endif

struct qemu_CryptGetOIDFunctionValue
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t pszOID;
    uint64_t pwszValueName;
    uint64_t pdwValueType;
    uint64_t pbValueData;
    uint64_t pcbValueData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptGetOIDFunctionValue(DWORD dwEncodingType, LPCSTR pszFuncName, LPCSTR pszOID, LPCWSTR pwszValueName, DWORD *pdwValueType, BYTE *pbValueData, DWORD *pcbValueData)
{
    struct qemu_CryptGetOIDFunctionValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETOIDFUNCTIONVALUE);
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.pszOID = (ULONG_PTR)pszOID;
    call.pwszValueName = (ULONG_PTR)pwszValueName;
    call.pdwValueType = (ULONG_PTR)pdwValueType;
    call.pbValueData = (ULONG_PTR)pbValueData;
    call.pcbValueData = (ULONG_PTR)pcbValueData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetOIDFunctionValue(struct qemu_syscall *call)
{
    struct qemu_CryptGetOIDFunctionValue *c = (struct qemu_CryptGetOIDFunctionValue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetOIDFunctionValue(c->dwEncodingType, QEMU_G2H(c->pszFuncName), QEMU_G2H(c->pszOID), QEMU_G2H(c->pwszValueName), QEMU_G2H(c->pdwValueType), QEMU_G2H(c->pbValueData), QEMU_G2H(c->pcbValueData));
}

#endif

struct qemu_CryptSetOIDFunctionValue
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t pszOID;
    uint64_t pwszValueName;
    uint64_t dwValueType;
    uint64_t pbValueData;
    uint64_t cbValueData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSetOIDFunctionValue(DWORD dwEncodingType, LPCSTR pszFuncName, LPCSTR pszOID, LPCWSTR pwszValueName, DWORD dwValueType, const BYTE *pbValueData, DWORD cbValueData)
{
    struct qemu_CryptSetOIDFunctionValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSETOIDFUNCTIONVALUE);
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.pszOID = (ULONG_PTR)pszOID;
    call.pwszValueName = (ULONG_PTR)pwszValueName;
    call.dwValueType = dwValueType;
    call.pbValueData = (ULONG_PTR)pbValueData;
    call.cbValueData = cbValueData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSetOIDFunctionValue(struct qemu_syscall *call)
{
    struct qemu_CryptSetOIDFunctionValue *c = (struct qemu_CryptSetOIDFunctionValue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSetOIDFunctionValue(c->dwEncodingType, QEMU_G2H(c->pszFuncName), QEMU_G2H(c->pszOID), QEMU_G2H(c->pwszValueName), c->dwValueType, QEMU_G2H(c->pbValueData), c->cbValueData);
}

#endif

struct qemu_CryptRegisterDefaultOIDFunction
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t dwIndex;
    uint64_t pwszDll;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptRegisterDefaultOIDFunction(DWORD dwEncodingType, LPCSTR pszFuncName, DWORD dwIndex, LPCWSTR pwszDll)
{
    struct qemu_CryptRegisterDefaultOIDFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTREGISTERDEFAULTOIDFUNCTION);
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.dwIndex = dwIndex;
    call.pwszDll = (ULONG_PTR)pwszDll;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptRegisterDefaultOIDFunction(struct qemu_syscall *call)
{
    struct qemu_CryptRegisterDefaultOIDFunction *c = (struct qemu_CryptRegisterDefaultOIDFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptRegisterDefaultOIDFunction(c->dwEncodingType, QEMU_G2H(c->pszFuncName), c->dwIndex, QEMU_G2H(c->pwszDll));
}

#endif

struct qemu_CryptUnregisterDefaultOIDFunction
{
    struct qemu_syscall super;
    uint64_t dwEncodingType;
    uint64_t pszFuncName;
    uint64_t pwszDll;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptUnregisterDefaultOIDFunction(DWORD dwEncodingType, LPCSTR pszFuncName, LPCWSTR pwszDll)
{
    struct qemu_CryptUnregisterDefaultOIDFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTUNREGISTERDEFAULTOIDFUNCTION);
    call.dwEncodingType = dwEncodingType;
    call.pszFuncName = (ULONG_PTR)pszFuncName;
    call.pwszDll = (ULONG_PTR)pwszDll;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptUnregisterDefaultOIDFunction(struct qemu_syscall *call)
{
    struct qemu_CryptUnregisterDefaultOIDFunction *c = (struct qemu_CryptUnregisterDefaultOIDFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptUnregisterDefaultOIDFunction(c->dwEncodingType, QEMU_G2H(c->pszFuncName), QEMU_G2H(c->pwszDll));
}

#endif

struct qemu_CryptFindLocalizedName
{
    struct qemu_syscall super;
    uint64_t pwszCryptName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPCWSTR WINAPI CryptFindLocalizedName(LPCWSTR pwszCryptName)
{
    struct qemu_CryptFindLocalizedName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTFINDLOCALIZEDNAME);
    call.pwszCryptName = (ULONG_PTR)pwszCryptName;

    qemu_syscall(&call.super);

    return (LPCWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptFindLocalizedName(struct qemu_syscall *call)
{
    struct qemu_CryptFindLocalizedName *c = (struct qemu_CryptFindLocalizedName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CryptFindLocalizedName(QEMU_G2H(c->pwszCryptName));
}

#endif

struct qemu_CryptEnumOIDInfo
{
    struct qemu_syscall super;
    uint64_t dwGroupId;
    uint64_t dwFlags;
    uint64_t pvArg;
    uint64_t pfnEnumOIDInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEnumOIDInfo(DWORD dwGroupId, DWORD dwFlags, void *pvArg, PFN_CRYPT_ENUM_OID_INFO pfnEnumOIDInfo)
{
    struct qemu_CryptEnumOIDInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENUMOIDINFO);
    call.dwGroupId = dwGroupId;
    call.dwFlags = dwFlags;
    call.pvArg = (ULONG_PTR)pvArg;
    call.pfnEnumOIDInfo = (ULONG_PTR)pfnEnumOIDInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEnumOIDInfo(struct qemu_syscall *call)
{
    struct qemu_CryptEnumOIDInfo *c = (struct qemu_CryptEnumOIDInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptEnumOIDInfo(c->dwGroupId, c->dwFlags, QEMU_G2H(c->pvArg), QEMU_G2H(c->pfnEnumOIDInfo));
}

#endif

struct qemu_CryptFindOIDInfo
{
    struct qemu_syscall super;
    uint64_t dwKeyType;
    uint64_t pvKey;
    uint64_t dwGroupId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCCRYPT_OID_INFO WINAPI CryptFindOIDInfo(DWORD dwKeyType, void *pvKey, DWORD dwGroupId)
{
    struct qemu_CryptFindOIDInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTFINDOIDINFO);
    call.dwKeyType = dwKeyType;
    call.pvKey = (ULONG_PTR)pvKey;
    call.dwGroupId = dwGroupId;

    qemu_syscall(&call.super);

    return (PCCRYPT_OID_INFO)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptFindOIDInfo(struct qemu_syscall *call)
{
    struct qemu_CryptFindOIDInfo *c = (struct qemu_CryptFindOIDInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CryptFindOIDInfo(c->dwKeyType, QEMU_G2H(c->pvKey), c->dwGroupId));
}

#endif

struct qemu_CertAlgIdToOID
{
    struct qemu_syscall super;
    uint64_t dwAlgId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPCSTR WINAPI CertAlgIdToOID(DWORD dwAlgId)
{
    struct qemu_CertAlgIdToOID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTALGIDTOOID);
    call.dwAlgId = dwAlgId;

    qemu_syscall(&call.super);

    return (LPCSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CertAlgIdToOID(struct qemu_syscall *call)
{
    struct qemu_CertAlgIdToOID *c = (struct qemu_CertAlgIdToOID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CertAlgIdToOID(c->dwAlgId);
}

#endif

struct qemu_CertOIDToAlgId
{
    struct qemu_syscall super;
    uint64_t pszObjId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertOIDToAlgId(LPCSTR pszObjId)
{
    struct qemu_CertOIDToAlgId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTOIDTOALGID);
    call.pszObjId = (ULONG_PTR)pszObjId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertOIDToAlgId(struct qemu_syscall *call)
{
    struct qemu_CertOIDToAlgId *c = (struct qemu_CertOIDToAlgId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertOIDToAlgId(QEMU_G2H(c->pszObjId));
}

#endif

