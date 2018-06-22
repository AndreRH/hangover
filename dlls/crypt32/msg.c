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
#include <wincon.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CryptMsgOpenToEncode
{
    struct qemu_syscall super;
    uint64_t dwMsgEncodingType;
    uint64_t dwFlags;
    uint64_t dwMsgType;
    uint64_t pvMsgEncodeInfo;
    uint64_t pszInnerContentObjID;
    uint64_t pStreamInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCRYPTMSG WINAPI CryptMsgOpenToEncode(DWORD dwMsgEncodingType, DWORD dwFlags, DWORD dwMsgType, const void *pvMsgEncodeInfo, LPSTR pszInnerContentObjID, PCMSG_STREAM_INFO pStreamInfo)
{
    struct qemu_CryptMsgOpenToEncode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGOPENTOENCODE);
    call.dwMsgEncodingType = dwMsgEncodingType;
    call.dwFlags = dwFlags;
    call.dwMsgType = dwMsgType;
    call.pvMsgEncodeInfo = (ULONG_PTR)pvMsgEncodeInfo;
    call.pszInnerContentObjID = (ULONG_PTR)pszInnerContentObjID;
    call.pStreamInfo = (ULONG_PTR)pStreamInfo;

    qemu_syscall(&call.super);

    return (HCRYPTMSG)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptMsgOpenToEncode(struct qemu_syscall *call)
{
    struct qemu_CryptMsgOpenToEncode *c = (struct qemu_CryptMsgOpenToEncode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CryptMsgOpenToEncode(c->dwMsgEncodingType, c->dwFlags, c->dwMsgType, QEMU_G2H(c->pvMsgEncodeInfo), QEMU_G2H(c->pszInnerContentObjID), QEMU_G2H(c->pStreamInfo)));
}

#endif

struct qemu_CryptMsgOpenToDecode
{
    struct qemu_syscall super;
    uint64_t dwMsgEncodingType;
    uint64_t dwFlags;
    uint64_t dwMsgType;
    uint64_t hCryptProv;
    uint64_t pRecipientInfo;
    uint64_t pStreamInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCRYPTMSG WINAPI CryptMsgOpenToDecode(DWORD dwMsgEncodingType, DWORD dwFlags, DWORD dwMsgType, HCRYPTPROV_LEGACY hCryptProv, PCERT_INFO pRecipientInfo, PCMSG_STREAM_INFO pStreamInfo)
{
    struct qemu_CryptMsgOpenToDecode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGOPENTODECODE);
    call.dwMsgEncodingType = dwMsgEncodingType;
    call.dwFlags = dwFlags;
    call.dwMsgType = dwMsgType;
    call.hCryptProv = hCryptProv;
    call.pRecipientInfo = (ULONG_PTR)pRecipientInfo;
    call.pStreamInfo = (ULONG_PTR)pStreamInfo;

    qemu_syscall(&call.super);

    return (HCRYPTMSG)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptMsgOpenToDecode(struct qemu_syscall *call)
{
    struct qemu_CryptMsgOpenToDecode *c = (struct qemu_CryptMsgOpenToDecode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CryptMsgOpenToDecode(c->dwMsgEncodingType, c->dwFlags, c->dwMsgType, c->hCryptProv, QEMU_G2H(c->pRecipientInfo), QEMU_G2H(c->pStreamInfo)));
}

#endif

struct qemu_CryptMsgDuplicate
{
    struct qemu_syscall super;
    uint64_t hCryptMsg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCRYPTMSG WINAPI CryptMsgDuplicate(HCRYPTMSG hCryptMsg)
{
    struct qemu_CryptMsgDuplicate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGDUPLICATE);
    call.hCryptMsg = (ULONG_PTR)hCryptMsg;

    qemu_syscall(&call.super);

    return (HCRYPTMSG)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptMsgDuplicate(struct qemu_syscall *call)
{
    struct qemu_CryptMsgDuplicate *c = (struct qemu_CryptMsgDuplicate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CryptMsgDuplicate(QEMU_G2H(c->hCryptMsg)));
}

#endif

struct qemu_CryptMsgClose
{
    struct qemu_syscall super;
    uint64_t hCryptMsg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgClose(HCRYPTMSG hCryptMsg)
{
    struct qemu_CryptMsgClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGCLOSE);
    call.hCryptMsg = (ULONG_PTR)hCryptMsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgClose(struct qemu_syscall *call)
{
    struct qemu_CryptMsgClose *c = (struct qemu_CryptMsgClose *)call;
    WINE_TRACE("\n");
    c->super.iret = CryptMsgClose(QEMU_G2H(c->hCryptMsg));
}

#endif

struct qemu_CryptMsgUpdate
{
    struct qemu_syscall super;
    uint64_t hCryptMsg;
    uint64_t pbData;
    uint64_t cbData;
    uint64_t fFinal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgUpdate(HCRYPTMSG hCryptMsg, const BYTE *pbData, DWORD cbData, BOOL fFinal)
{
    struct qemu_CryptMsgUpdate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGUPDATE);
    call.hCryptMsg = (ULONG_PTR)hCryptMsg;
    call.pbData = (ULONG_PTR)pbData;
    call.cbData = cbData;
    call.fFinal = fFinal;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgUpdate(struct qemu_syscall *call)
{
    struct qemu_CryptMsgUpdate *c = (struct qemu_CryptMsgUpdate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgUpdate(QEMU_G2H(c->hCryptMsg), QEMU_G2H(c->pbData), c->cbData, c->fFinal);
}

#endif

struct qemu_CryptMsgGetParam
{
    struct qemu_syscall super;
    uint64_t hCryptMsg;
    uint64_t dwParamType;
    uint64_t dwIndex;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgGetParam(HCRYPTMSG hCryptMsg, DWORD dwParamType, DWORD dwIndex, void *pvData,
        DWORD *pcbData)
{
    struct qemu_CryptMsgGetParam call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGGETPARAM);
    call.hCryptMsg = (ULONG_PTR)hCryptMsg;
    call.dwParamType = dwParamType;
    call.dwIndex = dwIndex;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgGetParam(struct qemu_syscall *call)
{
    struct qemu_CryptMsgGetParam *c = (struct qemu_CryptMsgGetParam *)call;
    DWORD param;
    void *data;

    WINE_FIXME("Hopelessly unfinished.\n");
    param = c->dwParamType;
    data = QEMU_G2H(c->pvData);

    switch (param)
    {
        case CMSG_SIGNER_INFO_PARAM:
            c->super.iret = CryptMsgGetParam(QEMU_G2H(c->hCryptMsg), param, c->dwIndex, data,
                    QEMU_G2H(c->pcbData));
            if (data && c->super.iret)
                CMSG_SIGNER_INFO_h2g(data, data);
            break;

        default:
            c->super.iret = CryptMsgGetParam(QEMU_G2H(c->hCryptMsg), param, c->dwIndex, data,
                    QEMU_G2H(c->pcbData));
    }
}

#endif

struct qemu_CryptMsgControl
{
    struct qemu_syscall super;
    uint64_t hCryptMsg;
    uint64_t dwFlags;
    uint64_t dwCtrlType;
    uint64_t pvCtrlPara;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgControl(HCRYPTMSG hCryptMsg, DWORD dwFlags, DWORD dwCtrlType, const void *pvCtrlPara)
{
    struct qemu_CryptMsgControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGCONTROL);
    call.hCryptMsg = (ULONG_PTR)hCryptMsg;
    call.dwFlags = dwFlags;
    call.dwCtrlType = dwCtrlType;
    call.pvCtrlPara = (ULONG_PTR)pvCtrlPara;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgControl(struct qemu_syscall *call)
{
    struct qemu_CryptMsgControl *c = (struct qemu_CryptMsgControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgControl(QEMU_G2H(c->hCryptMsg), c->dwFlags, c->dwCtrlType, QEMU_G2H(c->pvCtrlPara));
}

#endif

struct qemu_CryptMsgGetAndVerifySigner
{
    struct qemu_syscall super;
    uint64_t hCryptMsg;
    uint64_t cSignerStore;
    uint64_t rghSignerStore;
    uint64_t dwFlags;
    uint64_t ppSigner;
    uint64_t pdwSignerIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgGetAndVerifySigner(HCRYPTMSG hCryptMsg, DWORD cSignerStore, HCERTSTORE *rghSignerStore, DWORD dwFlags, PCCERT_CONTEXT *ppSigner, DWORD *pdwSignerIndex)
{
    struct qemu_CryptMsgGetAndVerifySigner call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGGETANDVERIFYSIGNER);
    call.hCryptMsg = (ULONG_PTR)hCryptMsg;
    call.cSignerStore = cSignerStore;
    call.rghSignerStore = (ULONG_PTR)rghSignerStore;
    call.dwFlags = dwFlags;
    call.ppSigner = (ULONG_PTR)ppSigner;
    call.pdwSignerIndex = (ULONG_PTR)pdwSignerIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgGetAndVerifySigner(struct qemu_syscall *call)
{
    struct qemu_CryptMsgGetAndVerifySigner *c = (struct qemu_CryptMsgGetAndVerifySigner *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgGetAndVerifySigner(QEMU_G2H(c->hCryptMsg), c->cSignerStore, QEMU_G2H(c->rghSignerStore), c->dwFlags, QEMU_G2H(c->ppSigner), QEMU_G2H(c->pdwSignerIndex));
}

#endif

struct qemu_CryptMsgVerifyCountersignatureEncoded
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwEncodingType;
    uint64_t pbSignerInfo;
    uint64_t cbSignerInfo;
    uint64_t pbSignerInfoCountersignature;
    uint64_t cbSignerInfoCountersignature;
    uint64_t pciCountersigner;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgVerifyCountersignatureEncoded(HCRYPTPROV_LEGACY hCryptProv, DWORD dwEncodingType, BYTE *pbSignerInfo, DWORD cbSignerInfo, PBYTE pbSignerInfoCountersignature, DWORD cbSignerInfoCountersignature, CERT_INFO *pciCountersigner)
{
    struct qemu_CryptMsgVerifyCountersignatureEncoded call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGVERIFYCOUNTERSIGNATUREENCODED);
    call.hCryptProv = hCryptProv;
    call.dwEncodingType = dwEncodingType;
    call.pbSignerInfo = (ULONG_PTR)pbSignerInfo;
    call.cbSignerInfo = cbSignerInfo;
    call.pbSignerInfoCountersignature = (ULONG_PTR)pbSignerInfoCountersignature;
    call.cbSignerInfoCountersignature = cbSignerInfoCountersignature;
    call.pciCountersigner = (ULONG_PTR)pciCountersigner;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgVerifyCountersignatureEncoded(struct qemu_syscall *call)
{
    struct qemu_CryptMsgVerifyCountersignatureEncoded *c = (struct qemu_CryptMsgVerifyCountersignatureEncoded *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgVerifyCountersignatureEncoded(c->hCryptProv, c->dwEncodingType, QEMU_G2H(c->pbSignerInfo), c->cbSignerInfo, QEMU_G2H(c->pbSignerInfoCountersignature), c->cbSignerInfoCountersignature, QEMU_G2H(c->pciCountersigner));
}

#endif

struct qemu_CryptMsgVerifyCountersignatureEncodedEx
{
    struct qemu_syscall super;
    uint64_t hCryptProv;
    uint64_t dwEncodingType;
    uint64_t pbSignerInfo;
    uint64_t cbSignerInfo;
    uint64_t pbSignerInfoCountersignature;
    uint64_t cbSignerInfoCountersignature;
    uint64_t dwSignerType;
    uint64_t pvSigner;
    uint64_t dwFlags;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgVerifyCountersignatureEncodedEx(HCRYPTPROV_LEGACY hCryptProv, DWORD dwEncodingType, PBYTE pbSignerInfo, DWORD cbSignerInfo, PBYTE pbSignerInfoCountersignature, DWORD cbSignerInfoCountersignature, DWORD dwSignerType, void *pvSigner, DWORD dwFlags, void *pvReserved)
{
    struct qemu_CryptMsgVerifyCountersignatureEncodedEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGVERIFYCOUNTERSIGNATUREENCODEDEX);
    call.hCryptProv = hCryptProv;
    call.dwEncodingType = dwEncodingType;
    call.pbSignerInfo = (ULONG_PTR)pbSignerInfo;
    call.cbSignerInfo = cbSignerInfo;
    call.pbSignerInfoCountersignature = (ULONG_PTR)pbSignerInfoCountersignature;
    call.cbSignerInfoCountersignature = cbSignerInfoCountersignature;
    call.dwSignerType = dwSignerType;
    call.pvSigner = (ULONG_PTR)pvSigner;
    call.dwFlags = dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgVerifyCountersignatureEncodedEx(struct qemu_syscall *call)
{
    struct qemu_CryptMsgVerifyCountersignatureEncodedEx *c = (struct qemu_CryptMsgVerifyCountersignatureEncodedEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgVerifyCountersignatureEncodedEx(c->hCryptProv, c->dwEncodingType, QEMU_G2H(c->pbSignerInfo), c->cbSignerInfo, QEMU_G2H(c->pbSignerInfoCountersignature), c->cbSignerInfoCountersignature, c->dwSignerType, QEMU_G2H(c->pvSigner), c->dwFlags, QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_CryptMsgEncodeAndSignCTL
{
    struct qemu_syscall super;
    uint64_t dwMsgEncodingType;
    uint64_t pCtlInfo;
    uint64_t pSignInfo;
    uint64_t dwFlags;
    uint64_t pbEncoded;
    uint64_t pcbEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgEncodeAndSignCTL(DWORD dwMsgEncodingType, PCTL_INFO pCtlInfo, PCMSG_SIGNED_ENCODE_INFO pSignInfo, DWORD dwFlags, BYTE *pbEncoded, DWORD *pcbEncoded)
{
    struct qemu_CryptMsgEncodeAndSignCTL call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGENCODEANDSIGNCTL);
    call.dwMsgEncodingType = dwMsgEncodingType;
    call.pCtlInfo = (ULONG_PTR)pCtlInfo;
    call.pSignInfo = (ULONG_PTR)pSignInfo;
    call.dwFlags = dwFlags;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgEncodeAndSignCTL(struct qemu_syscall *call)
{
    struct qemu_CryptMsgEncodeAndSignCTL *c = (struct qemu_CryptMsgEncodeAndSignCTL *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgEncodeAndSignCTL(c->dwMsgEncodingType, QEMU_G2H(c->pCtlInfo), QEMU_G2H(c->pSignInfo), c->dwFlags, QEMU_G2H(c->pbEncoded), QEMU_G2H(c->pcbEncoded));
}

#endif

struct qemu_CryptMsgSignCTL
{
    struct qemu_syscall super;
    uint64_t dwMsgEncodingType;
    uint64_t pbCtlContent;
    uint64_t cbCtlContent;
    uint64_t pSignInfo;
    uint64_t dwFlags;
    uint64_t pbEncoded;
    uint64_t pcbEncoded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptMsgSignCTL(DWORD dwMsgEncodingType, BYTE *pbCtlContent, DWORD cbCtlContent, PCMSG_SIGNED_ENCODE_INFO pSignInfo, DWORD dwFlags, BYTE *pbEncoded, DWORD *pcbEncoded)
{
    struct qemu_CryptMsgSignCTL call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMSGSIGNCTL);
    call.dwMsgEncodingType = dwMsgEncodingType;
    call.pbCtlContent = (ULONG_PTR)pbCtlContent;
    call.cbCtlContent = cbCtlContent;
    call.pSignInfo = (ULONG_PTR)pSignInfo;
    call.dwFlags = dwFlags;
    call.pbEncoded = (ULONG_PTR)pbEncoded;
    call.pcbEncoded = (ULONG_PTR)pcbEncoded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptMsgSignCTL(struct qemu_syscall *call)
{
    struct qemu_CryptMsgSignCTL *c = (struct qemu_CryptMsgSignCTL *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptMsgSignCTL(c->dwMsgEncodingType, QEMU_G2H(c->pbCtlContent), c->cbCtlContent, QEMU_G2H(c->pSignInfo), c->dwFlags, QEMU_G2H(c->pbEncoded), QEMU_G2H(c->pcbEncoded));
}

#endif

