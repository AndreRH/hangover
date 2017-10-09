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
#include <secext.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_secur32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_secur32);
#endif



struct qemu_FreeContextBuffer
{
    struct qemu_syscall super;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI FreeContextBuffer(PVOID pv)
{
    struct qemu_FreeContextBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREECONTEXTBUFFER);
    call.pv = (uint64_t)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeContextBuffer(struct qemu_syscall *call)
{
    struct qemu_FreeContextBuffer *c = (struct qemu_FreeContextBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeContextBuffer(QEMU_G2H(c->pv));
}

#endif

struct qemu_EnumerateSecurityPackagesW
{
    struct qemu_syscall super;
    uint64_t pcPackages;
    uint64_t ppPackageInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI EnumerateSecurityPackagesW(PULONG pcPackages, PSecPkgInfoW *ppPackageInfo)
{
    struct qemu_EnumerateSecurityPackagesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMERATESECURITYPACKAGESW);
    call.pcPackages = (uint64_t)pcPackages;
    call.ppPackageInfo = (uint64_t)ppPackageInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumerateSecurityPackagesW(struct qemu_syscall *call)
{
    struct qemu_EnumerateSecurityPackagesW *c = (struct qemu_EnumerateSecurityPackagesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumerateSecurityPackagesW(QEMU_G2H(c->pcPackages), QEMU_G2H(c->ppPackageInfo));
}

#endif

struct qemu_EnumerateSecurityPackagesA
{
    struct qemu_syscall super;
    uint64_t pcPackages;
    uint64_t ppPackageInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI EnumerateSecurityPackagesA(PULONG pcPackages, PSecPkgInfoA *ppPackageInfo)
{
    struct qemu_EnumerateSecurityPackagesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMERATESECURITYPACKAGESA);
    call.pcPackages = (uint64_t)pcPackages;
    call.ppPackageInfo = (uint64_t)ppPackageInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumerateSecurityPackagesA(struct qemu_syscall *call)
{
    struct qemu_EnumerateSecurityPackagesA *c = (struct qemu_EnumerateSecurityPackagesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumerateSecurityPackagesA(QEMU_G2H(c->pcPackages), QEMU_G2H(c->ppPackageInfo));
}

#endif

struct qemu_GetComputerObjectNameA
{
    struct qemu_syscall super;
    uint64_t NameFormat;
    uint64_t lpNameBuffer;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI GetComputerObjectNameA(EXTENDED_NAME_FORMAT NameFormat, LPSTR lpNameBuffer, PULONG nSize)
{
    struct qemu_GetComputerObjectNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPUTEROBJECTNAMEA);
    call.NameFormat = (uint64_t)NameFormat;
    call.lpNameBuffer = (uint64_t)lpNameBuffer;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComputerObjectNameA(struct qemu_syscall *call)
{
    struct qemu_GetComputerObjectNameA *c = (struct qemu_GetComputerObjectNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetComputerObjectNameA(c->NameFormat, QEMU_G2H(c->lpNameBuffer), QEMU_G2H(c->nSize));
}

#endif

struct qemu_GetComputerObjectNameW
{
    struct qemu_syscall super;
    uint64_t NameFormat;
    uint64_t lpNameBuffer;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI GetComputerObjectNameW(EXTENDED_NAME_FORMAT NameFormat, LPWSTR lpNameBuffer, PULONG nSize)
{
    struct qemu_GetComputerObjectNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPUTEROBJECTNAMEW);
    call.NameFormat = (uint64_t)NameFormat;
    call.lpNameBuffer = (uint64_t)lpNameBuffer;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComputerObjectNameW(struct qemu_syscall *call)
{
    struct qemu_GetComputerObjectNameW *c = (struct qemu_GetComputerObjectNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetComputerObjectNameW(c->NameFormat, QEMU_G2H(c->lpNameBuffer), QEMU_G2H(c->nSize));
}

#endif

struct qemu_AddSecurityPackageA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI AddSecurityPackageA(LPSTR name, SECURITY_PACKAGE_OPTIONS *options)
{
    struct qemu_AddSecurityPackageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDSECURITYPACKAGEA);
    call.name = (uint64_t)name;
    call.options = (uint64_t)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddSecurityPackageA(struct qemu_syscall *call)
{
    struct qemu_AddSecurityPackageA *c = (struct qemu_AddSecurityPackageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddSecurityPackageA(QEMU_G2H(c->name), QEMU_G2H(c->options));
}

#endif

struct qemu_AddSecurityPackageW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SECURITY_STATUS WINAPI AddSecurityPackageW(LPWSTR name, SECURITY_PACKAGE_OPTIONS *options)
{
    struct qemu_AddSecurityPackageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDSECURITYPACKAGEW);
    call.name = (uint64_t)name;
    call.options = (uint64_t)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddSecurityPackageW(struct qemu_syscall *call)
{
    struct qemu_AddSecurityPackageW *c = (struct qemu_AddSecurityPackageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddSecurityPackageW(QEMU_G2H(c->name), QEMU_G2H(c->options));
}

#endif

struct qemu_GetUserNameExA
{
    struct qemu_syscall super;
    uint64_t NameFormat;
    uint64_t lpNameBuffer;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI GetUserNameExA(EXTENDED_NAME_FORMAT NameFormat, LPSTR lpNameBuffer, PULONG nSize)
{
    struct qemu_GetUserNameExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERNAMEEXA);
    call.NameFormat = (uint64_t)NameFormat;
    call.lpNameBuffer = (uint64_t)lpNameBuffer;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserNameExA(struct qemu_syscall *call)
{
    struct qemu_GetUserNameExA *c = (struct qemu_GetUserNameExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserNameExA(c->NameFormat, QEMU_G2H(c->lpNameBuffer), QEMU_G2H(c->nSize));
}

#endif

struct qemu_GetUserNameExW
{
    struct qemu_syscall super;
    uint64_t NameFormat;
    uint64_t lpNameBuffer;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI GetUserNameExW(EXTENDED_NAME_FORMAT NameFormat, LPWSTR lpNameBuffer, PULONG nSize)
{
    struct qemu_GetUserNameExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERNAMEEXW);
    call.NameFormat = (uint64_t)NameFormat;
    call.lpNameBuffer = (uint64_t)lpNameBuffer;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserNameExW(struct qemu_syscall *call)
{
    struct qemu_GetUserNameExW *c = (struct qemu_GetUserNameExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserNameExW(c->NameFormat, QEMU_G2H(c->lpNameBuffer), QEMU_G2H(c->nSize));
}

#endif

struct qemu_TranslateNameA
{
    struct qemu_syscall super;
    uint64_t lpAccountName;
    uint64_t AccountNameFormat;
    uint64_t DesiredNameFormat;
    uint64_t lpTranslatedName;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI TranslateNameA(LPCSTR lpAccountName, EXTENDED_NAME_FORMAT AccountNameFormat, EXTENDED_NAME_FORMAT DesiredNameFormat, LPSTR lpTranslatedName, PULONG nSize)
{
    struct qemu_TranslateNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATENAMEA);
    call.lpAccountName = (uint64_t)lpAccountName;
    call.AccountNameFormat = (uint64_t)AccountNameFormat;
    call.DesiredNameFormat = (uint64_t)DesiredNameFormat;
    call.lpTranslatedName = (uint64_t)lpTranslatedName;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateNameA(struct qemu_syscall *call)
{
    struct qemu_TranslateNameA *c = (struct qemu_TranslateNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TranslateNameA(QEMU_G2H(c->lpAccountName), c->AccountNameFormat, c->DesiredNameFormat, QEMU_G2H(c->lpTranslatedName), QEMU_G2H(c->nSize));
}

#endif

struct qemu_TranslateNameW
{
    struct qemu_syscall super;
    uint64_t lpAccountName;
    uint64_t AccountNameFormat;
    uint64_t DesiredNameFormat;
    uint64_t lpTranslatedName;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI TranslateNameW(LPCWSTR lpAccountName, EXTENDED_NAME_FORMAT AccountNameFormat, EXTENDED_NAME_FORMAT DesiredNameFormat, LPWSTR lpTranslatedName, PULONG nSize)
{
    struct qemu_TranslateNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATENAMEW);
    call.lpAccountName = (uint64_t)lpAccountName;
    call.AccountNameFormat = (uint64_t)AccountNameFormat;
    call.DesiredNameFormat = (uint64_t)DesiredNameFormat;
    call.lpTranslatedName = (uint64_t)lpTranslatedName;
    call.nSize = (uint64_t)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateNameW(struct qemu_syscall *call)
{
    struct qemu_TranslateNameW *c = (struct qemu_TranslateNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TranslateNameW(QEMU_G2H(c->lpAccountName), c->AccountNameFormat, c->DesiredNameFormat, QEMU_G2H(c->lpTranslatedName), QEMU_G2H(c->nSize));
}

#endif

struct qemu_InitSecurityInterfaceA
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

static SecurityFunctionTableA securityFunctionTableA =
{
    SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION,
    EnumerateSecurityPackagesA,
    QueryCredentialsAttributesA,
    AcquireCredentialsHandleA,
    FreeCredentialsHandle,
    NULL, /* Reserved2 */
    InitializeSecurityContextA,
    AcceptSecurityContext,
    CompleteAuthToken,
    DeleteSecurityContext,
    ApplyControlToken,
    QueryContextAttributesA,
    ImpersonateSecurityContext,
    RevertSecurityContext,
    MakeSignature,
    VerifySignature,
    FreeContextBuffer,
    QuerySecurityPackageInfoA,
    EncryptMessage, /* Reserved3 */
    DecryptMessage, /* Reserved4 */
    ExportSecurityContext,
    ImportSecurityContextA,
    AddCredentialsA,
    NULL, /* Reserved8 */
    QuerySecurityContextToken,
    EncryptMessage,
    DecryptMessage,
    SetContextAttributesA
};

WINBASEAPI PSecurityFunctionTableA WINAPI InitSecurityInterfaceA(void)
{
    struct qemu_InitSecurityInterfaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITSECURITYINTERFACEA);

    qemu_syscall(&call.super);

    return &securityFunctionTableA;
}

#else

void qemu_InitSecurityInterfaceA(struct qemu_syscall *call)
{
    struct qemu_InitSecurityInterfaceA *c = (struct qemu_InitSecurityInterfaceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(InitSecurityInterfaceA());
}

#endif

struct qemu_InitSecurityInterfaceW
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

static SecurityFunctionTableW securityFunctionTableW =
{
    SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION,
    EnumerateSecurityPackagesW,
    QueryCredentialsAttributesW,
    AcquireCredentialsHandleW,
    FreeCredentialsHandle,
    NULL, /* Reserved2 */
    InitializeSecurityContextW,
    AcceptSecurityContext,
    CompleteAuthToken,
    DeleteSecurityContext,
    ApplyControlToken,
    QueryContextAttributesW,
    ImpersonateSecurityContext,
    RevertSecurityContext,
    MakeSignature,
    VerifySignature,
    FreeContextBuffer,
    QuerySecurityPackageInfoW,
    EncryptMessage, /* Reserved3 */
    DecryptMessage, /* Reserved4 */
    ExportSecurityContext,
    ImportSecurityContextW,
    AddCredentialsW,
    NULL, /* Reserved8 */
    QuerySecurityContextToken,
    EncryptMessage,
    DecryptMessage,
    SetContextAttributesW
};

WINBASEAPI PSecurityFunctionTableW WINAPI InitSecurityInterfaceW(void)
{
    struct qemu_InitSecurityInterfaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITSECURITYINTERFACEW);

    qemu_syscall(&call.super);

    return &securityFunctionTableW;
}

#else

void qemu_InitSecurityInterfaceW(struct qemu_syscall *call)
{
    struct qemu_InitSecurityInterfaceW *c = (struct qemu_InitSecurityInterfaceW *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(InitSecurityInterfaceW());
}

#endif
