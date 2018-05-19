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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

struct qemu_CryptGetMessageCertificates
{
    struct qemu_syscall super;
    uint64_t dwMsgAndCertEncodingType;
    uint64_t hCryptProv;
    uint64_t dwFlags;
    uint64_t pbSignedBlob;
    uint64_t cbSignedBlob;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCERTSTORE WINAPI CryptGetMessageCertificates(DWORD dwMsgAndCertEncodingType, HCRYPTPROV_LEGACY hCryptProv, DWORD dwFlags, const BYTE* pbSignedBlob, DWORD cbSignedBlob)
{
    struct qemu_CryptGetMessageCertificates call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETMESSAGECERTIFICATES);
    call.dwMsgAndCertEncodingType = dwMsgAndCertEncodingType;
    call.hCryptProv = hCryptProv;
    call.dwFlags = dwFlags;
    call.pbSignedBlob = (ULONG_PTR)pbSignedBlob;
    call.cbSignedBlob = cbSignedBlob;

    qemu_syscall(&call.super);

    return (HCERTSTORE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CryptGetMessageCertificates(struct qemu_syscall *call)
{
    struct qemu_CryptGetMessageCertificates *c = (struct qemu_CryptGetMessageCertificates *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CryptGetMessageCertificates(c->dwMsgAndCertEncodingType, c->hCryptProv, c->dwFlags, QEMU_G2H(c->pbSignedBlob), c->cbSignedBlob));
}

#endif

struct qemu_CryptGetMessageSignerCount
{
    struct qemu_syscall super;
    uint64_t dwMsgEncodingType;
    uint64_t pbSignedBlob;
    uint64_t cbSignedBlob;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI CryptGetMessageSignerCount(DWORD dwMsgEncodingType, const BYTE *pbSignedBlob, DWORD cbSignedBlob)
{
    struct qemu_CryptGetMessageSignerCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTGETMESSAGESIGNERCOUNT);
    call.dwMsgEncodingType = dwMsgEncodingType;
    call.pbSignedBlob = (ULONG_PTR)pbSignedBlob;
    call.cbSignedBlob = cbSignedBlob;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptGetMessageSignerCount(struct qemu_syscall *call)
{
    struct qemu_CryptGetMessageSignerCount *c = (struct qemu_CryptGetMessageSignerCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptGetMessageSignerCount(c->dwMsgEncodingType, QEMU_G2H(c->pbSignedBlob), c->cbSignedBlob);
}

#endif

struct qemu_CryptVerifyDetachedMessageSignature
{
    struct qemu_syscall super;
    uint64_t pVerifyPara;
    uint64_t dwSignerIndex;
    uint64_t pbDetachedSignBlob;
    uint64_t cbDetachedSignBlob;
    uint64_t cToBeSigned;
    uint64_t rgpbToBeSigned;
    uint64_t rgcbToBeSigned;
    uint64_t ppSignerCert;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifyDetachedMessageSignature(PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, DWORD dwSignerIndex, const BYTE *pbDetachedSignBlob, DWORD cbDetachedSignBlob, DWORD cToBeSigned, const BYTE *rgpbToBeSigned[], DWORD rgcbToBeSigned[], PCCERT_CONTEXT *ppSignerCert)
{
    struct qemu_CryptVerifyDetachedMessageSignature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYDETACHEDMESSAGESIGNATURE);
    call.pVerifyPara = (ULONG_PTR)pVerifyPara;
    call.dwSignerIndex = dwSignerIndex;
    call.pbDetachedSignBlob = (ULONG_PTR)pbDetachedSignBlob;
    call.cbDetachedSignBlob = cbDetachedSignBlob;
    call.cToBeSigned = cToBeSigned;
    call.rgpbToBeSigned = (ULONG_PTR)rgpbToBeSigned;
    call.rgcbToBeSigned = (ULONG_PTR)rgcbToBeSigned;
    call.ppSignerCert = (ULONG_PTR)ppSignerCert;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifyDetachedMessageSignature(struct qemu_syscall *call)
{
    struct qemu_CryptVerifyDetachedMessageSignature *c = (struct qemu_CryptVerifyDetachedMessageSignature *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptVerifyDetachedMessageSignature(QEMU_G2H(c->pVerifyPara), c->dwSignerIndex, QEMU_G2H(c->pbDetachedSignBlob), c->cbDetachedSignBlob, c->cToBeSigned, QEMU_G2H(c->rgpbToBeSigned), QEMU_G2H(c->rgcbToBeSigned), QEMU_G2H(c->ppSignerCert));
}

#endif

struct qemu_CryptVerifyMessageSignature
{
    struct qemu_syscall super;
    uint64_t pVerifyPara;
    uint64_t dwSignerIndex;
    uint64_t pbSignedBlob;
    uint64_t cbSignedBlob;
    uint64_t pbDecoded;
    uint64_t pcbDecoded;
    uint64_t ppSignerCert;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifyMessageSignature(PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, DWORD dwSignerIndex, const BYTE* pbSignedBlob, DWORD cbSignedBlob, BYTE* pbDecoded, DWORD* pcbDecoded, PCCERT_CONTEXT* ppSignerCert)
{
    struct qemu_CryptVerifyMessageSignature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYMESSAGESIGNATURE);
    call.pVerifyPara = (ULONG_PTR)pVerifyPara;
    call.dwSignerIndex = dwSignerIndex;
    call.pbSignedBlob = (ULONG_PTR)pbSignedBlob;
    call.cbSignedBlob = cbSignedBlob;
    call.pbDecoded = (ULONG_PTR)pbDecoded;
    call.pcbDecoded = (ULONG_PTR)pcbDecoded;
    call.ppSignerCert = (ULONG_PTR)ppSignerCert;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifyMessageSignature(struct qemu_syscall *call)
{
    struct qemu_CryptVerifyMessageSignature *c = (struct qemu_CryptVerifyMessageSignature *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptVerifyMessageSignature(QEMU_G2H(c->pVerifyPara), c->dwSignerIndex, QEMU_G2H(c->pbSignedBlob), c->cbSignedBlob, QEMU_G2H(c->pbDecoded), QEMU_G2H(c->pcbDecoded), QEMU_G2H(c->ppSignerCert));
}

#endif

struct qemu_CryptHashMessage
{
    struct qemu_syscall super;
    uint64_t pHashPara;
    uint64_t fDetachedHash;
    uint64_t cToBeHashed;
    uint64_t rgpbToBeHashed;
    uint64_t rgcbToBeHashed;
    uint64_t pbHashedBlob;
    uint64_t pcbHashedBlob;
    uint64_t pbComputedHash;
    uint64_t pcbComputedHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptHashMessage(PCRYPT_HASH_MESSAGE_PARA pHashPara, BOOL fDetachedHash, DWORD cToBeHashed, const BYTE *rgpbToBeHashed[], DWORD rgcbToBeHashed[], BYTE *pbHashedBlob, DWORD *pcbHashedBlob, BYTE *pbComputedHash, DWORD *pcbComputedHash)
{
    struct qemu_CryptHashMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTHASHMESSAGE);
    call.pHashPara = (ULONG_PTR)pHashPara;
    call.fDetachedHash = fDetachedHash;
    call.cToBeHashed = cToBeHashed;
    call.rgpbToBeHashed = (ULONG_PTR)rgpbToBeHashed;
    call.rgcbToBeHashed = (ULONG_PTR)rgcbToBeHashed;
    call.pbHashedBlob = (ULONG_PTR)pbHashedBlob;
    call.pcbHashedBlob = (ULONG_PTR)pcbHashedBlob;
    call.pbComputedHash = (ULONG_PTR)pbComputedHash;
    call.pcbComputedHash = (ULONG_PTR)pcbComputedHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptHashMessage(struct qemu_syscall *call)
{
    struct qemu_CryptHashMessage *c = (struct qemu_CryptHashMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptHashMessage(QEMU_G2H(c->pHashPara), c->fDetachedHash, c->cToBeHashed, QEMU_G2H(c->rgpbToBeHashed), QEMU_G2H(c->rgcbToBeHashed), QEMU_G2H(c->pbHashedBlob), QEMU_G2H(c->pcbHashedBlob), QEMU_G2H(c->pbComputedHash), QEMU_G2H(c->pcbComputedHash));
}

#endif

struct qemu_CryptVerifyDetachedMessageHash
{
    struct qemu_syscall super;
    uint64_t pHashPara;
    uint64_t pbDetachedHashBlob;
    uint64_t cbDetachedHashBlob;
    uint64_t cToBeHashed;
    uint64_t rgpbToBeHashed;
    uint64_t rgcbToBeHashed;
    uint64_t pbComputedHash;
    uint64_t pcbComputedHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifyDetachedMessageHash(PCRYPT_HASH_MESSAGE_PARA pHashPara, BYTE *pbDetachedHashBlob, DWORD cbDetachedHashBlob, DWORD cToBeHashed, const BYTE *rgpbToBeHashed[], DWORD rgcbToBeHashed[], BYTE *pbComputedHash, DWORD *pcbComputedHash)
{
    struct qemu_CryptVerifyDetachedMessageHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYDETACHEDMESSAGEHASH);
    call.pHashPara = (ULONG_PTR)pHashPara;
    call.pbDetachedHashBlob = (ULONG_PTR)pbDetachedHashBlob;
    call.cbDetachedHashBlob = cbDetachedHashBlob;
    call.cToBeHashed = cToBeHashed;
    call.rgpbToBeHashed = (ULONG_PTR)rgpbToBeHashed;
    call.rgcbToBeHashed = (ULONG_PTR)rgcbToBeHashed;
    call.pbComputedHash = (ULONG_PTR)pbComputedHash;
    call.pcbComputedHash = (ULONG_PTR)pcbComputedHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifyDetachedMessageHash(struct qemu_syscall *call)
{
    struct qemu_CryptVerifyDetachedMessageHash *c = (struct qemu_CryptVerifyDetachedMessageHash *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptVerifyDetachedMessageHash(QEMU_G2H(c->pHashPara), QEMU_G2H(c->pbDetachedHashBlob), c->cbDetachedHashBlob, c->cToBeHashed, QEMU_G2H(c->rgpbToBeHashed), QEMU_G2H(c->rgcbToBeHashed), QEMU_G2H(c->pbComputedHash), QEMU_G2H(c->pcbComputedHash));
}

#endif

struct qemu_CryptVerifyMessageHash
{
    struct qemu_syscall super;
    uint64_t pHashPara;
    uint64_t pbHashedBlob;
    uint64_t cbHashedBlob;
    uint64_t pbToBeHashed;
    uint64_t pcbToBeHashed;
    uint64_t pbComputedHash;
    uint64_t pcbComputedHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptVerifyMessageHash(PCRYPT_HASH_MESSAGE_PARA pHashPara, BYTE *pbHashedBlob, DWORD cbHashedBlob, BYTE *pbToBeHashed, DWORD *pcbToBeHashed, BYTE *pbComputedHash, DWORD *pcbComputedHash)
{
    struct qemu_CryptVerifyMessageHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTVERIFYMESSAGEHASH);
    call.pHashPara = (ULONG_PTR)pHashPara;
    call.pbHashedBlob = (ULONG_PTR)pbHashedBlob;
    call.cbHashedBlob = cbHashedBlob;
    call.pbToBeHashed = (ULONG_PTR)pbToBeHashed;
    call.pcbToBeHashed = (ULONG_PTR)pcbToBeHashed;
    call.pbComputedHash = (ULONG_PTR)pbComputedHash;
    call.pcbComputedHash = (ULONG_PTR)pcbComputedHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptVerifyMessageHash(struct qemu_syscall *call)
{
    struct qemu_CryptVerifyMessageHash *c = (struct qemu_CryptVerifyMessageHash *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptVerifyMessageHash(QEMU_G2H(c->pHashPara), QEMU_G2H(c->pbHashedBlob), c->cbHashedBlob, QEMU_G2H(c->pbToBeHashed), QEMU_G2H(c->pcbToBeHashed), QEMU_G2H(c->pbComputedHash), QEMU_G2H(c->pcbComputedHash));
}

#endif

struct qemu_CryptSignMessage
{
    struct qemu_syscall super;
    uint64_t pSignPara;
    uint64_t fDetachedSignature;
    uint64_t cToBeSigned;
    uint64_t rgpbToBeSigned;
    uint64_t rgcbToBeSigned;
    uint64_t pbSignedBlob;
    uint64_t pcbSignedBlob;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptSignMessage(PCRYPT_SIGN_MESSAGE_PARA pSignPara, BOOL fDetachedSignature, DWORD cToBeSigned, const BYTE *rgpbToBeSigned[], DWORD rgcbToBeSigned[], BYTE *pbSignedBlob, DWORD *pcbSignedBlob)
{
    struct qemu_CryptSignMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTSIGNMESSAGE);
    call.pSignPara = (ULONG_PTR)pSignPara;
    call.fDetachedSignature = fDetachedSignature;
    call.cToBeSigned = cToBeSigned;
    call.rgpbToBeSigned = (ULONG_PTR)rgpbToBeSigned;
    call.rgcbToBeSigned = (ULONG_PTR)rgcbToBeSigned;
    call.pbSignedBlob = (ULONG_PTR)pbSignedBlob;
    call.pcbSignedBlob = (ULONG_PTR)pcbSignedBlob;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptSignMessage(struct qemu_syscall *call)
{
    struct qemu_CryptSignMessage *c = (struct qemu_CryptSignMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptSignMessage(QEMU_G2H(c->pSignPara), c->fDetachedSignature, c->cToBeSigned, QEMU_G2H(c->rgpbToBeSigned), QEMU_G2H(c->rgcbToBeSigned), QEMU_G2H(c->pbSignedBlob), QEMU_G2H(c->pcbSignedBlob));
}

#endif

struct qemu_CryptEncryptMessage
{
    struct qemu_syscall super;
    uint64_t pEncryptPara;
    uint64_t cRecipientCert;
    uint64_t rgpRecipientCert;
    uint64_t pbToBeEncrypted;
    uint64_t cbToBeEncrypted;
    uint64_t pbEncryptedBlob;
    uint64_t pcbEncryptedBlob;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptEncryptMessage(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, DWORD cRecipientCert, PCCERT_CONTEXT rgpRecipientCert[], const BYTE *pbToBeEncrypted, DWORD cbToBeEncrypted, BYTE *pbEncryptedBlob, DWORD *pcbEncryptedBlob)
{
    struct qemu_CryptEncryptMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTENCRYPTMESSAGE);
    call.pEncryptPara = (ULONG_PTR)pEncryptPara;
    call.cRecipientCert = cRecipientCert;
    call.rgpRecipientCert = (ULONG_PTR)rgpRecipientCert;
    call.pbToBeEncrypted = (ULONG_PTR)pbToBeEncrypted;
    call.cbToBeEncrypted = cbToBeEncrypted;
    call.pbEncryptedBlob = (ULONG_PTR)pbEncryptedBlob;
    call.pcbEncryptedBlob = (ULONG_PTR)pcbEncryptedBlob;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CryptEncryptMessage(struct qemu_syscall *call)
{
    struct qemu_CryptEncryptMessage *c = (struct qemu_CryptEncryptMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptEncryptMessage(QEMU_G2H(c->pEncryptPara), c->cRecipientCert, QEMU_G2H(c->rgpRecipientCert), QEMU_G2H(c->pbToBeEncrypted), c->cbToBeEncrypted, QEMU_G2H(c->pbEncryptedBlob), QEMU_G2H(c->pcbEncryptedBlob));
}

#endif

