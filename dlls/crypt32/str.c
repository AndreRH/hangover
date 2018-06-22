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

struct qemu_CertRDNValueToStrA
{
    struct qemu_syscall super;
    uint64_t dwValueType;
    uint64_t pValue;
    uint64_t psz;
    uint64_t csz;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertRDNValueToStrA(DWORD dwValueType, PCERT_RDN_VALUE_BLOB pValue, LPSTR psz, DWORD csz)
{
    struct qemu_CertRDNValueToStrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTRDNVALUETOSTRA);
    call.dwValueType = dwValueType;
    call.pValue = (ULONG_PTR)pValue;
    call.psz = (ULONG_PTR)psz;
    call.csz = csz;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertRDNValueToStrA(struct qemu_syscall *call)
{
    struct qemu_CertRDNValueToStrA *c = (struct qemu_CertRDNValueToStrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertRDNValueToStrA(c->dwValueType, QEMU_G2H(c->pValue), QEMU_G2H(c->psz), c->csz);
}

#endif

struct qemu_CertRDNValueToStrW
{
    struct qemu_syscall super;
    uint64_t dwValueType;
    uint64_t pValue;
    uint64_t psz;
    uint64_t csz;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertRDNValueToStrW(DWORD dwValueType, PCERT_RDN_VALUE_BLOB pValue, LPWSTR psz, DWORD csz)
{
    struct qemu_CertRDNValueToStrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTRDNVALUETOSTRW);
    call.dwValueType = dwValueType;
    call.pValue = (ULONG_PTR)pValue;
    call.psz = (ULONG_PTR)psz;
    call.csz = csz;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertRDNValueToStrW(struct qemu_syscall *call)
{
    struct qemu_CertRDNValueToStrW *c = (struct qemu_CertRDNValueToStrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertRDNValueToStrW(c->dwValueType, QEMU_G2H(c->pValue), QEMU_G2H(c->psz), c->csz);
}

#endif

struct qemu_CertNameToStrA
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pName;
    uint64_t dwStrType;
    uint64_t psz;
    uint64_t csz;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertNameToStrA(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType, LPSTR psz, DWORD csz)
{
    struct qemu_CertNameToStrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTNAMETOSTRA);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pName = (ULONG_PTR)pName;
    call.dwStrType = dwStrType;
    call.psz = (ULONG_PTR)psz;
    call.csz = csz;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertNameToStrA(struct qemu_syscall *call)
{
    struct qemu_CertNameToStrA *c = (struct qemu_CertNameToStrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertNameToStrA(c->dwCertEncodingType, QEMU_G2H(c->pName), c->dwStrType, QEMU_G2H(c->psz), c->csz);
}

#endif

struct qemu_CertNameToStrW
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pName;
    uint64_t dwStrType;
    uint64_t psz;
    uint64_t csz;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertNameToStrW(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType,
        LPWSTR psz, DWORD csz)
{
    struct qemu_CertNameToStrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTNAMETOSTRW);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pName = (ULONG_PTR)pName;
    call.dwStrType = dwStrType;
    call.psz = (ULONG_PTR)psz;
    call.csz = csz;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertNameToStrW(struct qemu_syscall *call)
{
    struct qemu_CertNameToStrW *c = (struct qemu_CertNameToStrW *)call;
    CRYPT_DATA_BLOB stack, *blob = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    blob = QEMU_G2H(c->pName);
#else
    if (c->pName)
        CRYPT_DATA_BLOB_g2h(blob, QEMU_G2H(c->pName));
    else
        blob = NULL;
#endif

    c->super.iret = CertNameToStrW(c->dwCertEncodingType, blob, c->dwStrType, QEMU_G2H(c->psz), c->csz);
}

#endif

struct qemu_CertStrToNameA
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pszX500;
    uint64_t dwStrType;
    uint64_t pvReserved;
    uint64_t pbEncoded;
    uint64_t pcbEncoded;
    uint64_t ppszError;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertStrToNameA(DWORD dwCertEncodingType, LPCSTR pszX500, DWORD dwStrType, void *pvReserved, BYTE *pbEncoded, DWORD *pcbEncoded, LPCSTR *ppszError)
{
    struct qemu_CertStrToNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSTRTONAMEA);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pszX500 = (ULONG_PTR)pszX500;
    call.dwStrType = dwStrType;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;
    call.ppszError = (ULONG_PTR)ppszError;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertStrToNameA(struct qemu_syscall *call)
{
    struct qemu_CertStrToNameA *c = (struct qemu_CertStrToNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertStrToNameA(c->dwCertEncodingType, QEMU_G2H(c->pszX500), c->dwStrType, QEMU_G2H(c->pvReserved), QEMU_G2H(c->pbEncoded), QEMU_G2H(c->pcbEncoded), QEMU_G2H(c->ppszError));
}

#endif

struct qemu_CertStrToNameW
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t pszX500;
    uint64_t dwStrType;
    uint64_t pvReserved;
    uint64_t pbEncoded;
    uint64_t pcbEncoded;
    uint64_t ppszError;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CertStrToNameW(DWORD dwCertEncodingType, LPCWSTR pszX500, DWORD dwStrType, void *pvReserved,
        BYTE *pbEncoded, DWORD *pcbEncoded, LPCWSTR *ppszError)
{
    struct qemu_CertStrToNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTSTRTONAMEW);
    call.dwCertEncodingType = dwCertEncodingType;
    call.pszX500 = (ULONG_PTR)pszX500;
    call.dwStrType = dwStrType;
    call.pvReserved = (ULONG_PTR)pvReserved;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;
    call.ppszError = (ULONG_PTR)ppszError;

    qemu_syscall(&call.super);
    if (ppszError)
        *ppszError = (const WCHAR *)(ULONG_PTR)call.ppszError;

    return call.super.iret;
}

#else

void qemu_CertStrToNameW(struct qemu_syscall *call)
{
    struct qemu_CertStrToNameW *c = (struct qemu_CertStrToNameW *)call;
    const WCHAR *error;

    WINE_TRACE("\n");
    c->super.iret = CertStrToNameW(c->dwCertEncodingType, QEMU_G2H(c->pszX500), c->dwStrType,
            QEMU_G2H(c->pvReserved), QEMU_G2H(c->pbEncoded), QEMU_G2H(c->pcbEncoded),
            c->ppszError ? &error : NULL);
    c->ppszError = QEMU_H2G(error);
}

#endif

struct qemu_CertGetNameStringA
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwType;
    uint64_t dwFlags;
    uint64_t pvTypePara;
    uint64_t pszNameString;
    uint64_t cchNameString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertGetNameStringA(PCCERT_CONTEXT pCertContext, DWORD dwType, DWORD dwFlags, void *pvTypePara, LPSTR pszNameString, DWORD cchNameString)
{
    struct qemu_CertGetNameStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETNAMESTRINGA);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwType = dwType;
    call.dwFlags = dwFlags;
    call.pvTypePara = (ULONG_PTR)pvTypePara;
    call.pszNameString = (ULONG_PTR)pszNameString;
    call.cchNameString = cchNameString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetNameStringA(struct qemu_syscall *call)
{
    struct qemu_CertGetNameStringA *c = (struct qemu_CertGetNameStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetNameStringA(QEMU_G2H(c->pCertContext), c->dwType, c->dwFlags, QEMU_G2H(c->pvTypePara), QEMU_G2H(c->pszNameString), c->cchNameString);
}

#endif

struct qemu_CertGetNameStringW
{
    struct qemu_syscall super;
    uint64_t pCertContext;
    uint64_t dwType;
    uint64_t dwFlags;
    uint64_t pvTypePara;
    uint64_t pszNameString;
    uint64_t cchNameString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CertGetNameStringW(PCCERT_CONTEXT pCertContext, DWORD dwType, DWORD dwFlags, void *pvTypePara, LPWSTR pszNameString, DWORD cchNameString)
{
    struct qemu_CertGetNameStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CERTGETNAMESTRINGW);
    call.pCertContext = (ULONG_PTR)pCertContext;
    call.dwType = dwType;
    call.dwFlags = dwFlags;
    call.pvTypePara = (ULONG_PTR)pvTypePara;
    call.pszNameString = (ULONG_PTR)pszNameString;
    call.cchNameString = cchNameString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CertGetNameStringW(struct qemu_syscall *call)
{
    struct qemu_CertGetNameStringW *c = (struct qemu_CertGetNameStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CertGetNameStringW(QEMU_G2H(c->pCertContext), c->dwType, c->dwFlags, QEMU_G2H(c->pvTypePara), QEMU_G2H(c->pszNameString), c->cchNameString);
}

#endif

