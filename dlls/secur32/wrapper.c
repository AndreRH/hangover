/*
 * Copyright 2017 André Hentschel
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
#include <sspi.h>
#include <ntsecapi.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_sspi.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_secur32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_secur32);
#endif


struct qemu_AcquireCredentialsHandle
{
    struct qemu_syscall super;
    uint64_t pszPrincipal;
    uint64_t pszPackage;
    uint64_t fCredentialUse;
    uint64_t pvLogonId;
    uint64_t pAuthData;
    uint64_t pGetKeyFn;
    uint64_t pvGetKeyArgument;
    uint64_t phCredential;
    uint64_t ptsExpiry;
};

#ifdef QEMU_DLL_GUEST

SECURITY_STATUS WINAPI AcquireCredentialsHandleA(SEC_CHAR *pszPrincipal, SEC_CHAR *pszPackage,
        unsigned __LONG32 fCredentialUse, void *pvLogonId, void *pAuthData, SEC_GET_KEY_FN pGetKeyFn,
        void *pvGetKeyArgument, PCredHandle phCredential, PTimeStamp ptsExpiry)
{
    struct qemu_AcquireCredentialsHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACQUIRECREDENTIALSHANDLEA);
    call.pszPrincipal = (ULONG_PTR)pszPrincipal;
    call.pszPackage = (ULONG_PTR)pszPackage;
    call.fCredentialUse = (ULONG_PTR)fCredentialUse;
    call.pvLogonId = (ULONG_PTR)pvLogonId;
    call.pAuthData = (ULONG_PTR)pAuthData;
    call.pGetKeyFn = (ULONG_PTR)pGetKeyFn;
    call.pvGetKeyArgument = (ULONG_PTR)pvGetKeyArgument;
    call.phCredential = (ULONG_PTR)phCredential;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

KSECDDDECLSPEC SECURITY_STATUS WINAPI AcquireCredentialsHandleW(SEC_WCHAR *pszPrincipal, SEC_WCHAR *pszPackage,
        unsigned __LONG32 fCredentialUse, void *pvLogonId, void *pAuthData, SEC_GET_KEY_FN pGetKeyFn,
        void *pvGetKeyArgument, PCredHandle phCredential, PTimeStamp ptsExpiry)
{
    struct qemu_AcquireCredentialsHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACQUIRECREDENTIALSHANDLEW);
    call.pszPrincipal = (ULONG_PTR)pszPrincipal;
    call.pszPackage = (ULONG_PTR)pszPackage;
    call.fCredentialUse = (ULONG_PTR)fCredentialUse;
    call.pvLogonId = (ULONG_PTR)pvLogonId;
    call.pAuthData = (ULONG_PTR)pAuthData;
    call.pGetKeyFn = (ULONG_PTR)pGetKeyFn;
    call.pvGetKeyArgument = (ULONG_PTR)pvGetKeyArgument;
    call.phCredential = (ULONG_PTR)phCredential;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AcquireCredentialsHandle(struct qemu_syscall *call)
{
    struct qemu_AcquireCredentialsHandle *c = (struct qemu_AcquireCredentialsHandle *)call;
    SEC_WINNT_AUTH_IDENTITY_W stack, *auth = &stack;
    CredHandle handle;

    WINE_TRACE("\n");
    if (c->pGetKeyFn)
        WINE_FIXME("pGetKeyFn not handled yet.\n");

#if GUEST_BIT == HOST_BIT
    auth = QEMU_G2H(c->pAuthData);
#else
    if (c->pAuthData)
        SEC_WINNT_AUTH_IDENTITY_g2h(auth, QEMU_G2H(c->pAuthData));
    else
        auth = NULL;
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_ACQUIRECREDENTIALSHANDLEA))
    {
        c->super.iret = AcquireCredentialsHandleA(QEMU_G2H(c->pszPrincipal), QEMU_G2H(c->pszPackage),
                c->fCredentialUse, QEMU_G2H(c->pvLogonId), auth, QEMU_G2H(c->pGetKeyFn),
                QEMU_G2H(c->pvGetKeyArgument), c->phCredential ? &handle : NULL, QEMU_G2H(c->ptsExpiry));
    }
    else
    {
        c->super.iret = AcquireCredentialsHandleW(QEMU_G2H(c->pszPrincipal), QEMU_G2H(c->pszPackage),
                c->fCredentialUse, QEMU_G2H(c->pvLogonId), auth, QEMU_G2H(c->pGetKeyFn),
                QEMU_G2H(c->pvGetKeyArgument), c->phCredential ? &handle : NULL, QEMU_G2H(c->ptsExpiry));
    }

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == SEC_E_OK)
        SecHandle_h2g(QEMU_G2H(c->phCredential), &handle);
#endif
}

#endif

struct qemu_FreeCredentialsHandle
{
    struct qemu_syscall super;
    uint64_t phCredential;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI FreeCredentialsHandle(PCredHandle phCredential)
{
    struct qemu_FreeCredentialsHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREECREDENTIALSHANDLE);
    call.phCredential = (ULONG_PTR)phCredential;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeCredentialsHandle(struct qemu_syscall *call)
{
    struct qemu_FreeCredentialsHandle *c = (struct qemu_FreeCredentialsHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeCredentialsHandle(QEMU_G2H(c->phCredential));
}

#endif

struct qemu_QueryCredentialsAttributesA
{
    struct qemu_syscall super;
    uint64_t phCredential;
    uint64_t ulAttribute;
    uint64_t pBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QueryCredentialsAttributesA(PCredHandle phCredential, ULONG ulAttribute, void *pBuffer)
{
    struct qemu_QueryCredentialsAttributesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYCREDENTIALSATTRIBUTESA);
    call.phCredential = (ULONG_PTR)phCredential;
    call.ulAttribute = (ULONG_PTR)ulAttribute;
    call.pBuffer = (ULONG_PTR)pBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryCredentialsAttributesA(struct qemu_syscall *call)
{
    struct qemu_QueryCredentialsAttributesA *c = (struct qemu_QueryCredentialsAttributesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryCredentialsAttributesA(QEMU_G2H(c->phCredential), c->ulAttribute, QEMU_G2H(c->pBuffer));
}

#endif

struct qemu_QueryCredentialsAttributesW
{
    struct qemu_syscall super;
    uint64_t phCredential;
    uint64_t ulAttribute;
    uint64_t pBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QueryCredentialsAttributesW(PCredHandle phCredential, ULONG ulAttribute, void *pBuffer)
{
    struct qemu_QueryCredentialsAttributesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYCREDENTIALSATTRIBUTESW);
    call.phCredential = (ULONG_PTR)phCredential;
    call.ulAttribute = (ULONG_PTR)ulAttribute;
    call.pBuffer = (ULONG_PTR)pBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryCredentialsAttributesW(struct qemu_syscall *call)
{
    struct qemu_QueryCredentialsAttributesW *c = (struct qemu_QueryCredentialsAttributesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryCredentialsAttributesW(QEMU_G2H(c->phCredential), c->ulAttribute, QEMU_G2H(c->pBuffer));
}

#endif

struct qemu_InitializeSecurityContextA
{
    struct qemu_syscall super;
    uint64_t phCredential;
    uint64_t phContext;
    uint64_t pszTargetName;
    uint64_t fContextReq;
    uint64_t Reserved1;
    uint64_t TargetDataRep;
    uint64_t pInput;
    uint64_t Reserved2;
    uint64_t phNewContext;
    uint64_t pOutput;
    uint64_t pfContextAttr;
    uint64_t ptsExpiry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI InitializeSecurityContextA(PCredHandle phCredential, PCtxtHandle phContext, SEC_CHAR *pszTargetName, ULONG fContextReq, ULONG Reserved1, ULONG TargetDataRep, PSecBufferDesc pInput, ULONG Reserved2, PCtxtHandle phNewContext, PSecBufferDesc pOutput, ULONG *pfContextAttr, PTimeStamp ptsExpiry)
{
    struct qemu_InitializeSecurityContextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZESECURITYCONTEXTA);
    call.phCredential = (ULONG_PTR)phCredential;
    call.phContext = (ULONG_PTR)phContext;
    call.pszTargetName = (ULONG_PTR)pszTargetName;
    call.fContextReq = (ULONG_PTR)fContextReq;
    call.Reserved1 = (ULONG_PTR)Reserved1;
    call.TargetDataRep = (ULONG_PTR)TargetDataRep;
    call.pInput = (ULONG_PTR)pInput;
    call.Reserved2 = (ULONG_PTR)Reserved2;
    call.phNewContext = (ULONG_PTR)phNewContext;
    call.pOutput = (ULONG_PTR)pOutput;
    call.pfContextAttr = (ULONG_PTR)pfContextAttr;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeSecurityContextA(struct qemu_syscall *call)
{
    struct qemu_InitializeSecurityContextA *c = (struct qemu_InitializeSecurityContextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitializeSecurityContextA(QEMU_G2H(c->phCredential), QEMU_G2H(c->phContext), QEMU_G2H(c->pszTargetName), c->fContextReq, c->Reserved1, c->TargetDataRep, QEMU_G2H(c->pInput), c->Reserved2, QEMU_G2H(c->phNewContext), QEMU_G2H(c->pOutput), QEMU_G2H(c->pfContextAttr), QEMU_G2H(c->ptsExpiry));
}

#endif

struct qemu_InitializeSecurityContextW
{
    struct qemu_syscall super;
    uint64_t phCredential;
    uint64_t phContext;
    uint64_t pszTargetName;
    uint64_t fContextReq;
    uint64_t Reserved1;
    uint64_t TargetDataRep;
    uint64_t pInput;
    uint64_t Reserved2;
    uint64_t phNewContext;
    uint64_t pOutput;
    uint64_t pfContextAttr;
    uint64_t ptsExpiry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI InitializeSecurityContextW(PCredHandle phCredential, PCtxtHandle phContext, SEC_WCHAR *pszTargetName, ULONG fContextReq, ULONG Reserved1, ULONG TargetDataRep, PSecBufferDesc pInput, ULONG Reserved2, PCtxtHandle phNewContext, PSecBufferDesc pOutput, ULONG *pfContextAttr, PTimeStamp ptsExpiry)
{
    struct qemu_InitializeSecurityContextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZESECURITYCONTEXTW);
    call.phCredential = (ULONG_PTR)phCredential;
    call.phContext = (ULONG_PTR)phContext;
    call.pszTargetName = (ULONG_PTR)pszTargetName;
    call.fContextReq = (ULONG_PTR)fContextReq;
    call.Reserved1 = (ULONG_PTR)Reserved1;
    call.TargetDataRep = (ULONG_PTR)TargetDataRep;
    call.pInput = (ULONG_PTR)pInput;
    call.Reserved2 = (ULONG_PTR)Reserved2;
    call.phNewContext = (ULONG_PTR)phNewContext;
    call.pOutput = (ULONG_PTR)pOutput;
    call.pfContextAttr = (ULONG_PTR)pfContextAttr;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeSecurityContextW(struct qemu_syscall *call)
{
    struct qemu_InitializeSecurityContextW *c = (struct qemu_InitializeSecurityContextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitializeSecurityContextW(QEMU_G2H(c->phCredential), QEMU_G2H(c->phContext), QEMU_G2H(c->pszTargetName), c->fContextReq, c->Reserved1, c->TargetDataRep, QEMU_G2H(c->pInput), c->Reserved2, QEMU_G2H(c->phNewContext), QEMU_G2H(c->pOutput), QEMU_G2H(c->pfContextAttr), QEMU_G2H(c->ptsExpiry));
}

#endif

struct qemu_AcceptSecurityContext
{
    struct qemu_syscall super;
    uint64_t phCredential;
    uint64_t phContext;
    uint64_t pInput;
    uint64_t fContextReq;
    uint64_t TargetDataRep;
    uint64_t phNewContext;
    uint64_t pOutput;
    uint64_t pfContextAttr;
    uint64_t ptsExpiry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI AcceptSecurityContext(PCredHandle phCredential, PCtxtHandle phContext, PSecBufferDesc pInput, ULONG fContextReq, ULONG TargetDataRep, PCtxtHandle phNewContext, PSecBufferDesc pOutput, ULONG *pfContextAttr, PTimeStamp ptsExpiry)
{
    struct qemu_AcceptSecurityContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACCEPTSECURITYCONTEXT);
    call.phCredential = (ULONG_PTR)phCredential;
    call.phContext = (ULONG_PTR)phContext;
    call.pInput = (ULONG_PTR)pInput;
    call.fContextReq = (ULONG_PTR)fContextReq;
    call.TargetDataRep = (ULONG_PTR)TargetDataRep;
    call.phNewContext = (ULONG_PTR)phNewContext;
    call.pOutput = (ULONG_PTR)pOutput;
    call.pfContextAttr = (ULONG_PTR)pfContextAttr;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AcceptSecurityContext(struct qemu_syscall *call)
{
    struct qemu_AcceptSecurityContext *c = (struct qemu_AcceptSecurityContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AcceptSecurityContext(QEMU_G2H(c->phCredential), QEMU_G2H(c->phContext), QEMU_G2H(c->pInput), c->fContextReq, c->TargetDataRep, QEMU_G2H(c->phNewContext), QEMU_G2H(c->pOutput), QEMU_G2H(c->pfContextAttr), QEMU_G2H(c->ptsExpiry));
}

#endif

struct qemu_CompleteAuthToken
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t pToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI CompleteAuthToken(PCtxtHandle phContext, PSecBufferDesc pToken)
{
    struct qemu_CompleteAuthToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPLETEAUTHTOKEN);
    call.phContext = (ULONG_PTR)phContext;
    call.pToken = (ULONG_PTR)pToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompleteAuthToken(struct qemu_syscall *call)
{
    struct qemu_CompleteAuthToken *c = (struct qemu_CompleteAuthToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CompleteAuthToken(QEMU_G2H(c->phContext), QEMU_G2H(c->pToken));
}

#endif

struct qemu_DeleteSecurityContext
{
    struct qemu_syscall super;
    uint64_t phContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI DeleteSecurityContext(PCtxtHandle phContext)
{
    struct qemu_DeleteSecurityContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETESECURITYCONTEXT);
    call.phContext = (ULONG_PTR)phContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteSecurityContext(struct qemu_syscall *call)
{
    struct qemu_DeleteSecurityContext *c = (struct qemu_DeleteSecurityContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteSecurityContext(QEMU_G2H(c->phContext));
}

#endif

struct qemu_ApplyControlToken
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t pInput;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI ApplyControlToken(PCtxtHandle phContext, PSecBufferDesc pInput)
{
    struct qemu_ApplyControlToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_APPLYCONTROLTOKEN);
    call.phContext = (ULONG_PTR)phContext;
    call.pInput = (ULONG_PTR)pInput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ApplyControlToken(struct qemu_syscall *call)
{
    struct qemu_ApplyControlToken *c = (struct qemu_ApplyControlToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ApplyControlToken(QEMU_G2H(c->phContext), QEMU_G2H(c->pInput));
}

#endif

struct qemu_QueryContextAttributesA
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t ulAttribute;
    uint64_t pBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QueryContextAttributesA(PCtxtHandle phContext, ULONG ulAttribute, void *pBuffer)
{
    struct qemu_QueryContextAttributesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYCONTEXTATTRIBUTESA);
    call.phContext = (ULONG_PTR)phContext;
    call.ulAttribute = (ULONG_PTR)ulAttribute;
    call.pBuffer = (ULONG_PTR)pBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryContextAttributesA(struct qemu_syscall *call)
{
    struct qemu_QueryContextAttributesA *c = (struct qemu_QueryContextAttributesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryContextAttributesA(QEMU_G2H(c->phContext), c->ulAttribute, QEMU_G2H(c->pBuffer));
}

#endif

struct qemu_QueryContextAttributesW
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t ulAttribute;
    uint64_t pBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QueryContextAttributesW(PCtxtHandle phContext, ULONG ulAttribute, void *pBuffer)
{
    struct qemu_QueryContextAttributesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYCONTEXTATTRIBUTESW);
    call.phContext = (ULONG_PTR)phContext;
    call.ulAttribute = (ULONG_PTR)ulAttribute;
    call.pBuffer = (ULONG_PTR)pBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryContextAttributesW(struct qemu_syscall *call)
{
    struct qemu_QueryContextAttributesW *c = (struct qemu_QueryContextAttributesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryContextAttributesW(QEMU_G2H(c->phContext), c->ulAttribute, QEMU_G2H(c->pBuffer));
}

#endif

struct qemu_ImpersonateSecurityContext
{
    struct qemu_syscall super;
    uint64_t phContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI ImpersonateSecurityContext(PCtxtHandle phContext)
{
    struct qemu_ImpersonateSecurityContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPERSONATESECURITYCONTEXT);
    call.phContext = (ULONG_PTR)phContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImpersonateSecurityContext(struct qemu_syscall *call)
{
    struct qemu_ImpersonateSecurityContext *c = (struct qemu_ImpersonateSecurityContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImpersonateSecurityContext(QEMU_G2H(c->phContext));
}

#endif

struct qemu_RevertSecurityContext
{
    struct qemu_syscall super;
    uint64_t phContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI RevertSecurityContext(PCtxtHandle phContext)
{
    struct qemu_RevertSecurityContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REVERTSECURITYCONTEXT);
    call.phContext = (ULONG_PTR)phContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RevertSecurityContext(struct qemu_syscall *call)
{
    struct qemu_RevertSecurityContext *c = (struct qemu_RevertSecurityContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RevertSecurityContext(QEMU_G2H(c->phContext));
}

#endif

struct qemu_MakeSignature
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t fQOP;
    uint64_t pMessage;
    uint64_t MessageSeqNo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI MakeSignature(PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage, ULONG MessageSeqNo)
{
    struct qemu_MakeSignature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAKESIGNATURE);
    call.phContext = (ULONG_PTR)phContext;
    call.fQOP = (ULONG_PTR)fQOP;
    call.pMessage = (ULONG_PTR)pMessage;
    call.MessageSeqNo = (ULONG_PTR)MessageSeqNo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MakeSignature(struct qemu_syscall *call)
{
    struct qemu_MakeSignature *c = (struct qemu_MakeSignature *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MakeSignature(QEMU_G2H(c->phContext), c->fQOP, QEMU_G2H(c->pMessage), c->MessageSeqNo);
}

#endif

struct qemu_VerifySignature
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t pMessage;
    uint64_t MessageSeqNo;
    uint64_t pfQOP;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI VerifySignature(PCtxtHandle phContext, PSecBufferDesc pMessage, ULONG MessageSeqNo, PULONG pfQOP)
{
    struct qemu_VerifySignature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERIFYSIGNATURE);
    call.phContext = (ULONG_PTR)phContext;
    call.pMessage = (ULONG_PTR)pMessage;
    call.MessageSeqNo = (ULONG_PTR)MessageSeqNo;
    call.pfQOP = (ULONG_PTR)pfQOP;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerifySignature(struct qemu_syscall *call)
{
    struct qemu_VerifySignature *c = (struct qemu_VerifySignature *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerifySignature(QEMU_G2H(c->phContext), QEMU_G2H(c->pMessage), c->MessageSeqNo, QEMU_G2H(c->pfQOP));
}

#endif

struct qemu_QuerySecurityPackageInfoA
{
    struct qemu_syscall super;
    uint64_t pszPackageName;
    uint64_t ppPackageInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QuerySecurityPackageInfoA(SEC_CHAR *pszPackageName, PSecPkgInfoA *ppPackageInfo)
{
    struct qemu_QuerySecurityPackageInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSECURITYPACKAGEINFOA);
    call.pszPackageName = (ULONG_PTR)pszPackageName;

    qemu_syscall(&call.super);
    if (call.super.iret == SEC_E_OK)
        *ppPackageInfo = (SecPkgInfoA *)(ULONG_PTR)call.ppPackageInfo;

    return call.super.iret;
}

#else

void qemu_QuerySecurityPackageInfoA(struct qemu_syscall *call)
{
    struct qemu_QuerySecurityPackageInfoA *c = (struct qemu_QuerySecurityPackageInfoA *)call;
    SecPkgInfoA *info;

    WINE_TRACE("\n");
    c->super.iret = QuerySecurityPackageInfoA(QEMU_G2H(c->pszPackageName), &info);
    c->ppPackageInfo = QEMU_H2G(info);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == SEC_E_OK)
        SecPkgInfo_h2g((void *)info, (SecPkgInfoW *)info);
#endif
}

#endif

struct qemu_QuerySecurityPackageInfoW
{
    struct qemu_syscall super;
    uint64_t pszPackageName;
    uint64_t ppPackageInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QuerySecurityPackageInfoW(SEC_WCHAR *pszPackageName, PSecPkgInfoW *ppPackageInfo)
{
    struct qemu_QuerySecurityPackageInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSECURITYPACKAGEINFOW);
    call.pszPackageName = (ULONG_PTR)pszPackageName;

    qemu_syscall(&call.super);
    if (call.super.iret == SEC_E_OK)
        *ppPackageInfo = (SecPkgInfoW *)(ULONG_PTR)call.ppPackageInfo;

    return call.super.iret;
}

#else

void qemu_QuerySecurityPackageInfoW(struct qemu_syscall *call)
{
    struct qemu_QuerySecurityPackageInfoW *c = (struct qemu_QuerySecurityPackageInfoW *)call;
    SecPkgInfoW *info;

    WINE_TRACE("\n");
    c->super.iret = QuerySecurityPackageInfoW(QEMU_G2H(c->pszPackageName), &info);
    c->ppPackageInfo = QEMU_H2G(info);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == SEC_E_OK)
        SecPkgInfo_h2g((void *)info, info);
#endif
}

#endif

struct qemu_ExportSecurityContext
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t fFlags;
    uint64_t pPackedContext;
    uint64_t pToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI ExportSecurityContext(PCtxtHandle phContext, ULONG fFlags, PSecBuffer pPackedContext, void **pToken)
{
    struct qemu_ExportSecurityContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXPORTSECURITYCONTEXT);
    call.phContext = (ULONG_PTR)phContext;
    call.fFlags = (ULONG_PTR)fFlags;
    call.pPackedContext = (ULONG_PTR)pPackedContext;
    call.pToken = (ULONG_PTR)pToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExportSecurityContext(struct qemu_syscall *call)
{
    struct qemu_ExportSecurityContext *c = (struct qemu_ExportSecurityContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExportSecurityContext(QEMU_G2H(c->phContext), c->fFlags, QEMU_G2H(c->pPackedContext), QEMU_G2H(c->pToken));
}

#endif

struct qemu_ImportSecurityContextA
{
    struct qemu_syscall super;
    uint64_t pszPackage;
    uint64_t pPackedContext;
    uint64_t Token;
    uint64_t phContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI ImportSecurityContextA(SEC_CHAR *pszPackage, PSecBuffer pPackedContext, void *Token, PCtxtHandle phContext)
{
    struct qemu_ImportSecurityContextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPORTSECURITYCONTEXTA);
    call.pszPackage = (ULONG_PTR)pszPackage;
    call.pPackedContext = (ULONG_PTR)pPackedContext;
    call.Token = (ULONG_PTR)Token;
    call.phContext = (ULONG_PTR)phContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImportSecurityContextA(struct qemu_syscall *call)
{
    struct qemu_ImportSecurityContextA *c = (struct qemu_ImportSecurityContextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImportSecurityContextA(QEMU_G2H(c->pszPackage), QEMU_G2H(c->pPackedContext), QEMU_G2H(c->Token), QEMU_G2H(c->phContext));
}

#endif

struct qemu_ImportSecurityContextW
{
    struct qemu_syscall super;
    uint64_t pszPackage;
    uint64_t pPackedContext;
    uint64_t Token;
    uint64_t phContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI ImportSecurityContextW(SEC_WCHAR *pszPackage, PSecBuffer pPackedContext, void *Token, PCtxtHandle phContext)
{
    struct qemu_ImportSecurityContextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPORTSECURITYCONTEXTW);
    call.pszPackage = (ULONG_PTR)pszPackage;
    call.pPackedContext = (ULONG_PTR)pPackedContext;
    call.Token = (ULONG_PTR)Token;
    call.phContext = (ULONG_PTR)phContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImportSecurityContextW(struct qemu_syscall *call)
{
    struct qemu_ImportSecurityContextW *c = (struct qemu_ImportSecurityContextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImportSecurityContextW(QEMU_G2H(c->pszPackage), QEMU_G2H(c->pPackedContext), QEMU_G2H(c->Token), QEMU_G2H(c->phContext));
}

#endif

struct qemu_AddCredentialsA
{
    struct qemu_syscall super;
    uint64_t hCredentials;
    uint64_t pszPrincipal;
    uint64_t pszPackage;
    uint64_t fCredentialUse;
    uint64_t pAuthData;
    uint64_t pGetKeyFn;
    uint64_t pvGetKeyArgument;
    uint64_t ptsExpiry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI AddCredentialsA(PCredHandle hCredentials, SEC_CHAR *pszPrincipal, SEC_CHAR *pszPackage, ULONG fCredentialUse, void *pAuthData, SEC_GET_KEY_FN pGetKeyFn, void *pvGetKeyArgument, PTimeStamp ptsExpiry)
{
    struct qemu_AddCredentialsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDCREDENTIALSA);
    call.hCredentials = (ULONG_PTR)hCredentials;
    call.pszPrincipal = (ULONG_PTR)pszPrincipal;
    call.pszPackage = (ULONG_PTR)pszPackage;
    call.fCredentialUse = (ULONG_PTR)fCredentialUse;
    call.pAuthData = (ULONG_PTR)pAuthData;
    call.pGetKeyFn = (ULONG_PTR)pGetKeyFn;
    call.pvGetKeyArgument = (ULONG_PTR)pvGetKeyArgument;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddCredentialsA(struct qemu_syscall *call)
{
    struct qemu_AddCredentialsA *c = (struct qemu_AddCredentialsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddCredentialsA(QEMU_G2H(c->hCredentials), QEMU_G2H(c->pszPrincipal), QEMU_G2H(c->pszPackage), c->fCredentialUse, QEMU_G2H(c->pAuthData), QEMU_G2H(c->pGetKeyFn), QEMU_G2H(c->pvGetKeyArgument), QEMU_G2H(c->ptsExpiry));
}

#endif

struct qemu_AddCredentialsW
{
    struct qemu_syscall super;
    uint64_t hCredentials;
    uint64_t pszPrincipal;
    uint64_t pszPackage;
    uint64_t fCredentialUse;
    uint64_t pAuthData;
    uint64_t pGetKeyFn;
    uint64_t pvGetKeyArgument;
    uint64_t ptsExpiry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI AddCredentialsW(PCredHandle hCredentials, SEC_WCHAR *pszPrincipal, SEC_WCHAR *pszPackage, ULONG fCredentialUse, void *pAuthData, SEC_GET_KEY_FN pGetKeyFn, void *pvGetKeyArgument, PTimeStamp ptsExpiry)
{
    struct qemu_AddCredentialsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDCREDENTIALSW);
    call.hCredentials = (ULONG_PTR)hCredentials;
    call.pszPrincipal = (ULONG_PTR)pszPrincipal;
    call.pszPackage = (ULONG_PTR)pszPackage;
    call.fCredentialUse = (ULONG_PTR)fCredentialUse;
    call.pAuthData = (ULONG_PTR)pAuthData;
    call.pGetKeyFn = (ULONG_PTR)pGetKeyFn;
    call.pvGetKeyArgument = (ULONG_PTR)pvGetKeyArgument;
    call.ptsExpiry = (ULONG_PTR)ptsExpiry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddCredentialsW(struct qemu_syscall *call)
{
    struct qemu_AddCredentialsW *c = (struct qemu_AddCredentialsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddCredentialsW(QEMU_G2H(c->hCredentials), QEMU_G2H(c->pszPrincipal), QEMU_G2H(c->pszPackage), c->fCredentialUse, QEMU_G2H(c->pAuthData), QEMU_G2H(c->pGetKeyFn), QEMU_G2H(c->pvGetKeyArgument), QEMU_G2H(c->ptsExpiry));
}

#endif

struct qemu_QuerySecurityContextToken
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t phToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI QuerySecurityContextToken(PCtxtHandle phContext, HANDLE *phToken)
{
    struct qemu_QuerySecurityContextToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSECURITYCONTEXTTOKEN);
    call.phContext = (ULONG_PTR)phContext;
    call.phToken = (ULONG_PTR)phToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QuerySecurityContextToken(struct qemu_syscall *call)
{
    struct qemu_QuerySecurityContextToken *c = (struct qemu_QuerySecurityContextToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QuerySecurityContextToken(QEMU_G2H(c->phContext), QEMU_G2H(c->phToken));
}

#endif

struct qemu_EncryptMessage
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t fQOP;
    uint64_t pMessage;
    uint64_t MessageSeqNo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI EncryptMessage(PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage, ULONG MessageSeqNo)
{
    struct qemu_EncryptMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENCRYPTMESSAGE);
    call.phContext = (ULONG_PTR)phContext;
    call.fQOP = (ULONG_PTR)fQOP;
    call.pMessage = (ULONG_PTR)pMessage;
    call.MessageSeqNo = (ULONG_PTR)MessageSeqNo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EncryptMessage(struct qemu_syscall *call)
{
    struct qemu_EncryptMessage *c = (struct qemu_EncryptMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EncryptMessage(QEMU_G2H(c->phContext), c->fQOP, QEMU_G2H(c->pMessage), c->MessageSeqNo);
}

#endif

struct qemu_DecryptMessage
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t pMessage;
    uint64_t MessageSeqNo;
    uint64_t pfQOP;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI DecryptMessage(PCtxtHandle phContext, PSecBufferDesc pMessage, ULONG MessageSeqNo, PULONG pfQOP)
{
    struct qemu_DecryptMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DECRYPTMESSAGE);
    call.phContext = (ULONG_PTR)phContext;
    call.pMessage = (ULONG_PTR)pMessage;
    call.MessageSeqNo = (ULONG_PTR)MessageSeqNo;
    call.pfQOP = (ULONG_PTR)pfQOP;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DecryptMessage(struct qemu_syscall *call)
{
    struct qemu_DecryptMessage *c = (struct qemu_DecryptMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DecryptMessage(QEMU_G2H(c->phContext), QEMU_G2H(c->pMessage), c->MessageSeqNo, QEMU_G2H(c->pfQOP));
}

#endif

struct qemu_SetContextAttributesA
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t ulAttribute;
    uint64_t pBuffer;
    uint64_t cbBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI SetContextAttributesA(PCtxtHandle phContext, ULONG ulAttribute, void *pBuffer, ULONG cbBuffer)
{
    struct qemu_SetContextAttributesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONTEXTATTRIBUTESA);
    call.phContext = (ULONG_PTR)phContext;
    call.ulAttribute = (ULONG_PTR)ulAttribute;
    call.pBuffer = (ULONG_PTR)pBuffer;
    call.cbBuffer = (ULONG_PTR)cbBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetContextAttributesA(struct qemu_syscall *call)
{
    struct qemu_SetContextAttributesA *c = (struct qemu_SetContextAttributesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetContextAttributesA(QEMU_G2H(c->phContext), c->ulAttribute, QEMU_G2H(c->pBuffer), c->cbBuffer);
}

#endif

struct qemu_SetContextAttributesW
{
    struct qemu_syscall super;
    uint64_t phContext;
    uint64_t ulAttribute;
    uint64_t pBuffer;
    uint64_t cbBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI SetContextAttributesW(PCtxtHandle phContext, ULONG ulAttribute, void *pBuffer, ULONG cbBuffer)
{
    struct qemu_SetContextAttributesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCONTEXTATTRIBUTESW);
    call.phContext = (ULONG_PTR)phContext;
    call.ulAttribute = (ULONG_PTR)ulAttribute;
    call.pBuffer = (ULONG_PTR)pBuffer;
    call.cbBuffer = (ULONG_PTR)cbBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetContextAttributesW(struct qemu_syscall *call)
{
    struct qemu_SetContextAttributesW *c = (struct qemu_SetContextAttributesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetContextAttributesW(QEMU_G2H(c->phContext), c->ulAttribute, QEMU_G2H(c->pBuffer), c->cbBuffer);
}

#endif

