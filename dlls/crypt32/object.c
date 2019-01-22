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

struct qemu_CryptQueryObject
{
    struct qemu_syscall super;
    uint64_t dwObjectType;
    uint64_t pvObject;
    uint64_t dwExpectedContentTypeFlags;
    uint64_t dwExpectedFormatTypeFlags;
    uint64_t dwFlags;
    uint64_t pdwMsgAndCertEncodingType;
    uint64_t pdwContentType;
    uint64_t pdwFormatType;
    uint64_t phCertStore;
    uint64_t phMsg;
    uint64_t ppvContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptQueryObject(DWORD dwObjectType, const void *pvObject, DWORD dwExpectedContentTypeFlags,
        DWORD dwExpectedFormatTypeFlags, DWORD dwFlags, DWORD *pdwMsgAndCertEncodingType, DWORD *pdwContentType,
        DWORD *pdwFormatType, HCERTSTORE *phCertStore, HCRYPTMSG *phMsg, const void **ppvContext)
{
    struct qemu_CryptQueryObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTQUERYOBJECT);
    call.dwObjectType = dwObjectType;
    call.pvObject = (ULONG_PTR)pvObject;
    call.dwExpectedContentTypeFlags = dwExpectedContentTypeFlags;
    call.dwExpectedFormatTypeFlags = dwExpectedFormatTypeFlags;
    call.dwFlags = dwFlags;
    call.pdwMsgAndCertEncodingType = (ULONG_PTR)pdwMsgAndCertEncodingType;
    call.pdwContentType = (ULONG_PTR)pdwContentType;
    call.pdwFormatType = (ULONG_PTR)pdwFormatType;
    call.phCertStore = (ULONG_PTR)phCertStore;
    call.phMsg = (ULONG_PTR)phMsg;
    call.ppvContext = (ULONG_PTR)ppvContext;

    qemu_syscall(&call.super);
    if (phCertStore)
        *phCertStore = (HCERTSTORE)(ULONG_PTR)call.phCertStore;
    if (phMsg)
        *phMsg = (HCRYPTMSG)(ULONG_PTR)call.phMsg;

    return call.super.iret;
}

#else

void qemu_CryptQueryObject(struct qemu_syscall *call)
{
    struct qemu_CryptQueryObject *c = (struct qemu_CryptQueryObject *)call;
    HCERTSTORE store = NULL;
    HCRYPTMSG msg = NULL;

    WINE_FIXME("This is probably not right yet.\n");

    c->super.iret = CryptQueryObject(c->dwObjectType, QEMU_G2H(c->pvObject), c->dwExpectedContentTypeFlags,
            c->dwExpectedFormatTypeFlags, c->dwFlags, QEMU_G2H(c->pdwMsgAndCertEncodingType),
            QEMU_G2H(c->pdwContentType), QEMU_G2H(c->pdwFormatType), c->phCertStore ? &store : NULL,
            c->phMsg ? &msg : NULL, QEMU_G2H(c->ppvContext));

    c->phCertStore = QEMU_H2G(store);

#if GUEST_BIT != HOST_BIT
    if (store == empty_store)
        c->phCertStore = empty_store_replace;
#endif

    c->phMsg = QEMU_H2G(msg);
}

#endif

struct qemu_CryptFormatObject
{
    struct qemu_syscall super;
    uint64_t dwCertEncodingType;
    uint64_t dwFormatType;
    uint64_t dwFormatStrType;
    uint64_t pFormatStruct;
    uint64_t lpszStructType;
    uint64_t pbEncoded;
    uint64_t cbEncoded;
    uint64_t pbFormat;
    uint64_t pcbFormat;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptFormatObject(DWORD dwCertEncodingType, DWORD dwFormatType, DWORD dwFormatStrType, void *pFormatStruct, LPCSTR lpszStructType, const BYTE *pbEncoded, DWORD cbEncoded, void *pbFormat, DWORD *pcbFormat)
{
    struct qemu_CryptFormatObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTFORMATOBJECT);
    call.dwCertEncodingType = dwCertEncodingType;
    call.dwFormatType = dwFormatType;
    call.dwFormatStrType = dwFormatStrType;
    call.pFormatStruct = (ULONG_PTR)pFormatStruct;
    call.lpszStructType = (ULONG_PTR)lpszStructType;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.cbEncoded = cbEncoded;
    call.pbFormat = (ULONG_PTR)pbFormat;
    call.pcbFormat = (ULONG_PTR)pcbFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptFormatObject(struct qemu_syscall *call)
{
    struct qemu_CryptFormatObject *c = (struct qemu_CryptFormatObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptFormatObject(c->dwCertEncodingType, c->dwFormatType, c->dwFormatStrType, QEMU_G2H(c->pFormatStruct), QEMU_G2H(c->lpszStructType), QEMU_G2H(c->pbEncoded), c->cbEncoded, QEMU_G2H(c->pbFormat), QEMU_G2H(c->pcbFormat));
}

#endif

