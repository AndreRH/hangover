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
#include <mssip.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_mssip.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CryptSIPRemoveProvider
{
    struct qemu_syscall super;
    uint64_t pgProv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSIPRemoveProvider(GUID *pgProv)
{
    struct qemu_CryptSIPRemoveProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPREMOVEPROVIDER);
    call.pgProv = (ULONG_PTR)pgProv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPRemoveProvider(struct qemu_syscall *call)
{
    struct qemu_CryptSIPRemoveProvider *c = (struct qemu_CryptSIPRemoveProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPRemoveProvider(QEMU_G2H(c->pgProv));
}

#endif

struct qemu_CryptSIPAddProvider
{
    struct qemu_syscall super;
    uint64_t psNewProv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSIPAddProvider(SIP_ADD_NEWPROVIDER *psNewProv)
{
    struct qemu_CryptSIPAddProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPADDPROVIDER);
    call.psNewProv = (ULONG_PTR)psNewProv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPAddProvider(struct qemu_syscall *call)
{
    struct qemu_CryptSIPAddProvider *c = (struct qemu_CryptSIPAddProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPAddProvider(QEMU_G2H(c->psNewProv));
}

#endif

struct qemu_CryptSIPRetrieveSubjectGuid
{
    struct qemu_syscall super;
    uint64_t FileName;
    uint64_t hFileIn;
    uint64_t pgSubject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSIPRetrieveSubjectGuid (LPCWSTR FileName, HANDLE hFileIn, GUID *pgSubject)
{
    struct qemu_CryptSIPRetrieveSubjectGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPRETRIEVESUBJECTGUID);
    call.FileName = (ULONG_PTR)FileName;
    call.hFileIn = (ULONG_PTR)hFileIn;
    call.pgSubject = (ULONG_PTR)pgSubject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPRetrieveSubjectGuid(struct qemu_syscall *call)
{
    struct qemu_CryptSIPRetrieveSubjectGuid *c = (struct qemu_CryptSIPRetrieveSubjectGuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPRetrieveSubjectGuid(QEMU_G2H(c->FileName), QEMU_G2H(c->hFileIn), QEMU_G2H(c->pgSubject));
}

#endif

struct qemu_CryptSIPCreateIndirectData
{
    struct qemu_syscall super;
    uint64_t pSubjectInfo;
    uint64_t pcbIndirectData;
    uint64_t pIndirectData;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI crypt32_CryptSIPCreateIndirectData(SIP_SUBJECTINFO* pSubjectInfo, DWORD* pcbIndirectData, SIP_INDIRECT_DATA* pIndirectData)
{
    struct qemu_CryptSIPCreateIndirectData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPCREATEINDIRECTDATA);
    call.pSubjectInfo = (ULONG_PTR)pSubjectInfo;
    call.pcbIndirectData = (ULONG_PTR)pcbIndirectData;
    call.pIndirectData = (ULONG_PTR)pIndirectData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPCreateIndirectData(struct qemu_syscall *call)
{
    struct qemu_CryptSIPCreateIndirectData *c = (struct qemu_CryptSIPCreateIndirectData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPCreateIndirectData(QEMU_G2H(c->pSubjectInfo), QEMU_G2H(c->pcbIndirectData), QEMU_G2H(c->pIndirectData));
}

#endif

struct qemu_CryptSIPGetSignedDataMsg
{
    struct qemu_syscall super;
    uint64_t pSubjectInfo;
    uint64_t pdwEncodingType;
    uint64_t dwIndex;
    uint64_t pcbSignedDataMsg;
    uint64_t pbSignedDataMsg;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI crypt32_CryptSIPGetSignedDataMsg(SIP_SUBJECTINFO* pSubjectInfo, DWORD* pdwEncodingType, DWORD dwIndex, DWORD* pcbSignedDataMsg, BYTE* pbSignedDataMsg)
{
    struct qemu_CryptSIPGetSignedDataMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPGETSIGNEDDATAMSG);
    call.pSubjectInfo = (ULONG_PTR)pSubjectInfo;
    call.pdwEncodingType = (ULONG_PTR)pdwEncodingType;
    call.dwIndex = dwIndex;
    call.pcbSignedDataMsg = (ULONG_PTR)pcbSignedDataMsg;
    call.pbSignedDataMsg = (ULONG_PTR)pbSignedDataMsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPGetSignedDataMsg(struct qemu_syscall *call)
{
    struct qemu_CryptSIPGetSignedDataMsg *c = (struct qemu_CryptSIPGetSignedDataMsg *)call;
    SIP_SUBJECTINFO stack, *subject = &stack;

    WINE_FIXME("Possibly unfinished!\n");
#if GUEST_BIT == HOST_BIT
    subject = QEMU_G2H(c->pSubjectInfo);
#else
    if (QEMU_G2H(c->pSubjectInfo))
        SIP_SUBJECTINFO_g2h(subject, QEMU_G2H(c->pSubjectInfo));
    else
        subject = NULL;
#endif

    c->super.iret = CryptSIPGetSignedDataMsg(subject, QEMU_G2H(c->pdwEncodingType), c->dwIndex,
            QEMU_G2H(c->pcbSignedDataMsg), QEMU_G2H(c->pbSignedDataMsg));
}

#endif

struct qemu_CryptSIPPutSignedDataMsg
{
    struct qemu_syscall super;
    uint64_t pSubjectInfo;
    uint64_t pdwEncodingType;
    uint64_t pdwIndex;
    uint64_t cbSignedDataMsg;
    uint64_t pbSignedDataMsg;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI crypt32_CryptSIPPutSignedDataMsg(SIP_SUBJECTINFO* pSubjectInfo, DWORD pdwEncodingType, DWORD* pdwIndex, DWORD cbSignedDataMsg, BYTE* pbSignedDataMsg)
{
    struct qemu_CryptSIPPutSignedDataMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPPUTSIGNEDDATAMSG);
    call.pSubjectInfo = (ULONG_PTR)pSubjectInfo;
    call.pdwEncodingType = pdwEncodingType;
    call.pdwIndex = (ULONG_PTR)pdwIndex;
    call.cbSignedDataMsg = cbSignedDataMsg;
    call.pbSignedDataMsg = (ULONG_PTR)pbSignedDataMsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPPutSignedDataMsg(struct qemu_syscall *call)
{
    struct qemu_CryptSIPPutSignedDataMsg *c = (struct qemu_CryptSIPPutSignedDataMsg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPPutSignedDataMsg(QEMU_G2H(c->pSubjectInfo), c->pdwEncodingType, QEMU_G2H(c->pdwIndex), c->cbSignedDataMsg, QEMU_G2H(c->pbSignedDataMsg));
}

#endif

struct qemu_CryptSIPRemoveSignedDataMsg
{
    struct qemu_syscall super;
    uint64_t pSubjectInfo;
    uint64_t dwIndex;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI crypt32_CryptSIPRemoveSignedDataMsg(SIP_SUBJECTINFO* pSubjectInfo, DWORD dwIndex)
{
    struct qemu_CryptSIPRemoveSignedDataMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPREMOVESIGNEDDATAMSG);
    call.pSubjectInfo = (ULONG_PTR)pSubjectInfo;
    call.dwIndex = dwIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPRemoveSignedDataMsg(struct qemu_syscall *call)
{
    struct qemu_CryptSIPRemoveSignedDataMsg *c = (struct qemu_CryptSIPRemoveSignedDataMsg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPRemoveSignedDataMsg(QEMU_G2H(c->pSubjectInfo), c->dwIndex);
}

#endif

struct qemu_CryptSIPVerifyIndirectData
{
    struct qemu_syscall super;
    uint64_t pSubjectInfo;
    uint64_t pIndirectData;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI crypt32_CryptSIPVerifyIndirectData(SIP_SUBJECTINFO* pSubjectInfo,
        SIP_INDIRECT_DATA* pIndirectData)
{
    struct qemu_CryptSIPVerifyIndirectData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPVERIFYINDIRECTDATA);
    call.pSubjectInfo = (ULONG_PTR)pSubjectInfo;
    call.pIndirectData = (ULONG_PTR)pIndirectData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPVerifyIndirectData(struct qemu_syscall *call)
{
    struct qemu_CryptSIPVerifyIndirectData *c = (struct qemu_CryptSIPVerifyIndirectData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPVerifyIndirectData(QEMU_G2H(c->pSubjectInfo), QEMU_G2H(c->pIndirectData));
}

#endif

struct qemu_CryptSIPLoad
{
    struct qemu_syscall super;
    uint64_t pgSubject;
    uint64_t dwFlags;
    uint64_t pSipDispatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSIPLoad (const GUID *pgSubject, DWORD dwFlags,
                                     SIP_DISPATCH_INFO *pSipDispatch)
{
    struct qemu_CryptSIPLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPLOAD);
    call.pgSubject = (ULONG_PTR)pgSubject;
    call.dwFlags = dwFlags;
    call.pSipDispatch = (ULONG_PTR)pSipDispatch;

    qemu_syscall(&call.super);
    if (call.super.iret)
    {
        pSipDispatch->hSIP = NULL;
        pSipDispatch->pfGet = crypt32_CryptSIPGetSignedDataMsg;
        pSipDispatch->pfPut = crypt32_CryptSIPPutSignedDataMsg;
        pSipDispatch->pfCreate = crypt32_CryptSIPCreateIndirectData;
        pSipDispatch->pfVerify = crypt32_CryptSIPVerifyIndirectData;
        pSipDispatch->pfRemove = crypt32_CryptSIPRemoveSignedDataMsg;
    }

    return call.super.iret;
}

#else

void qemu_CryptSIPLoad(struct qemu_syscall *call)
{
    struct qemu_CryptSIPLoad *c = (struct qemu_CryptSIPLoad *)call;
    SIP_DISPATCH_INFO stack, *info= &stack;
    WINE_TRACE("\n");

    if (!QEMU_G2H(c->pSipDispatch))
        info = NULL;

    c->super.iret = CryptSIPLoad(QEMU_G2H(c->pgSubject), c->dwFlags, info);

    if (c->super.iret)
    {
        HMODULE crypt32 = GetModuleHandleA("crypt32");
        void *p_CryptSIPGetSignedDataMsg = GetProcAddress(crypt32, "CryptSIPGetSignedDataMsg");
        void *p_CryptSIPPutSignedDataMsg = GetProcAddress(crypt32, "CryptSIPPutSignedDataMsg");
        if (info->pfGet != p_CryptSIPGetSignedDataMsg)
            WINE_ERR("Got unexpected pfGet pointer\n");
        if (info->pfPut != p_CryptSIPPutSignedDataMsg)
            WINE_ERR("Got unexpected pfPut pointer\n");
    }
}

#endif

struct qemu_CryptSIPRetrieveSubjectGuidForCatalogFile
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t handle;
    uint64_t subject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSIPRetrieveSubjectGuidForCatalogFile(LPCWSTR filename, HANDLE handle, GUID *subject)
{
    struct qemu_CryptSIPRetrieveSubjectGuidForCatalogFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIPRETRIEVESUBJECTGUIDFORCATALOGFILE);
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;
    call.subject = (ULONG_PTR)subject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSIPRetrieveSubjectGuidForCatalogFile(struct qemu_syscall *call)
{
    struct qemu_CryptSIPRetrieveSubjectGuidForCatalogFile *c = (struct qemu_CryptSIPRetrieveSubjectGuidForCatalogFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSIPRetrieveSubjectGuidForCatalogFile(QEMU_G2H(c->filename), QEMU_G2H(c->handle), QEMU_G2H(c->subject));
}

#endif

