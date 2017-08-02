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
#include <accctrl.h>
#include <winsafer.h>
#include <aclapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_OpenProcessToken
{
    struct qemu_syscall super;
    uint64_t ProcessHandle;
    uint64_t DesiredAccess;
    uint64_t TokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI OpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, HANDLE *TokenHandle)
{
    struct qemu_OpenProcessToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENPROCESSTOKEN);
    call.ProcessHandle = (uint64_t)ProcessHandle;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.TokenHandle = (uint64_t)TokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenProcessToken(struct qemu_syscall *call)
{
    struct qemu_OpenProcessToken *c = (struct qemu_OpenProcessToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenProcessToken(QEMU_G2H(c->ProcessHandle), c->DesiredAccess, QEMU_G2H(c->TokenHandle));
}

#endif

struct qemu_OpenThreadToken
{
    struct qemu_syscall super;
    uint64_t ThreadHandle;
    uint64_t DesiredAccess;
    uint64_t OpenAsSelf;
    uint64_t TokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI OpenThreadToken(HANDLE ThreadHandle, DWORD DesiredAccess, BOOL OpenAsSelf, HANDLE *TokenHandle)
{
    struct qemu_OpenThreadToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENTHREADTOKEN);
    call.ThreadHandle = (uint64_t)ThreadHandle;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.OpenAsSelf = (uint64_t)OpenAsSelf;
    call.TokenHandle = (uint64_t)TokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenThreadToken(struct qemu_syscall *call)
{
    struct qemu_OpenThreadToken *c = (struct qemu_OpenThreadToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenThreadToken(QEMU_G2H(c->ThreadHandle), c->DesiredAccess, c->OpenAsSelf, QEMU_G2H(c->TokenHandle));
}

#endif

struct qemu_AdjustTokenGroups
{
    struct qemu_syscall super;
    uint64_t TokenHandle;
    uint64_t ResetToDefault;
    uint64_t NewState;
    uint64_t BufferLength;
    uint64_t PreviousState;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AdjustTokenGroups(HANDLE TokenHandle, BOOL ResetToDefault, PTOKEN_GROUPS NewState, DWORD BufferLength, PTOKEN_GROUPS PreviousState, PDWORD ReturnLength)
{
    struct qemu_AdjustTokenGroups call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADJUSTTOKENGROUPS);
    call.TokenHandle = (uint64_t)TokenHandle;
    call.ResetToDefault = (uint64_t)ResetToDefault;
    call.NewState = (uint64_t)NewState;
    call.BufferLength = (uint64_t)BufferLength;
    call.PreviousState = (uint64_t)PreviousState;
    call.ReturnLength = (uint64_t)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdjustTokenGroups(struct qemu_syscall *call)
{
    struct qemu_AdjustTokenGroups *c = (struct qemu_AdjustTokenGroups *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AdjustTokenGroups(QEMU_G2H(c->TokenHandle), c->ResetToDefault, QEMU_G2H(c->NewState), c->BufferLength, QEMU_G2H(c->PreviousState), QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_AdjustTokenPrivileges
{
    struct qemu_syscall super;
    uint64_t TokenHandle;
    uint64_t DisableAllPrivileges;
    uint64_t NewState;
    uint64_t BufferLength;
    uint64_t PreviousState;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AdjustTokenPrivileges(HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, PDWORD ReturnLength)
{
    struct qemu_AdjustTokenPrivileges call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADJUSTTOKENPRIVILEGES);
    call.TokenHandle = (uint64_t)TokenHandle;
    call.DisableAllPrivileges = (uint64_t)DisableAllPrivileges;
    call.NewState = (uint64_t)NewState;
    call.BufferLength = (uint64_t)BufferLength;
    call.PreviousState = (uint64_t)PreviousState;
    call.ReturnLength = (uint64_t)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdjustTokenPrivileges(struct qemu_syscall *call)
{
    struct qemu_AdjustTokenPrivileges *c = (struct qemu_AdjustTokenPrivileges *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AdjustTokenPrivileges(QEMU_G2H(c->TokenHandle), c->DisableAllPrivileges, QEMU_G2H(c->NewState), c->BufferLength, QEMU_G2H(c->PreviousState), QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_CheckTokenMembership
{
    struct qemu_syscall super;
    uint64_t token;
    uint64_t sid_to_check;
    uint64_t is_member;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CheckTokenMembership(HANDLE token, PSID sid_to_check, PBOOL is_member)
{
    struct qemu_CheckTokenMembership call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKTOKENMEMBERSHIP);
    call.token = (uint64_t)token;
    call.sid_to_check = (uint64_t)sid_to_check;
    call.is_member = (uint64_t)is_member;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckTokenMembership(struct qemu_syscall *call)
{
    struct qemu_CheckTokenMembership *c = (struct qemu_CheckTokenMembership *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckTokenMembership(QEMU_G2H(c->token), QEMU_G2H(c->sid_to_check), QEMU_G2H(c->is_member));
}

#endif

struct qemu_GetTokenInformation
{
    struct qemu_syscall super;
    uint64_t token;
    uint64_t tokeninfoclass;
    uint64_t tokeninfo;
    uint64_t tokeninfolength;
    uint64_t retlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetTokenInformation(HANDLE token, TOKEN_INFORMATION_CLASS tokeninfoclass, LPVOID tokeninfo, DWORD tokeninfolength, LPDWORD retlen)
{
    struct qemu_GetTokenInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTOKENINFORMATION);
    call.token = (uint64_t)token;
    call.tokeninfoclass = (uint64_t)tokeninfoclass;
    call.tokeninfo = (uint64_t)tokeninfo;
    call.tokeninfolength = (uint64_t)tokeninfolength;
    call.retlen = (uint64_t)retlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTokenInformation(struct qemu_syscall *call)
{
    struct qemu_GetTokenInformation *c = (struct qemu_GetTokenInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTokenInformation(QEMU_G2H(c->token), c->tokeninfoclass, QEMU_G2H(c->tokeninfo), c->tokeninfolength, QEMU_G2H(c->retlen));
}

#endif

struct qemu_SetTokenInformation
{
    struct qemu_syscall super;
    uint64_t token;
    uint64_t tokeninfoclass;
    uint64_t tokeninfo;
    uint64_t tokeninfolength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetTokenInformation(HANDLE token, TOKEN_INFORMATION_CLASS tokeninfoclass, LPVOID tokeninfo, DWORD tokeninfolength)
{
    struct qemu_SetTokenInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTOKENINFORMATION);
    call.token = (uint64_t)token;
    call.tokeninfoclass = (uint64_t)tokeninfoclass;
    call.tokeninfo = (uint64_t)tokeninfo;
    call.tokeninfolength = (uint64_t)tokeninfolength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTokenInformation(struct qemu_syscall *call)
{
    struct qemu_SetTokenInformation *c = (struct qemu_SetTokenInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetTokenInformation(QEMU_G2H(c->token), c->tokeninfoclass, QEMU_G2H(c->tokeninfo), c->tokeninfolength);
}

#endif

struct qemu_SetThreadToken
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t token;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadToken(PHANDLE thread, HANDLE token)
{
    struct qemu_SetThreadToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADTOKEN);
    call.thread = (uint64_t)thread;
    call.token = (uint64_t)token;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadToken(struct qemu_syscall *call)
{
    struct qemu_SetThreadToken *c = (struct qemu_SetThreadToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadToken(QEMU_G2H(c->thread), QEMU_G2H(c->token));
}

#endif

struct qemu_CreateRestrictedToken
{
    struct qemu_syscall super;
    uint64_t baseToken;
    uint64_t flags;
    uint64_t nDisableSids;
    uint64_t disableSids;
    uint64_t nDeletePrivs;
    uint64_t deletePrivs;
    uint64_t nRestrictSids;
    uint64_t restrictSids;
    uint64_t newToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateRestrictedToken(HANDLE baseToken, DWORD flags, DWORD nDisableSids, PSID_AND_ATTRIBUTES disableSids, DWORD nDeletePrivs, PLUID_AND_ATTRIBUTES deletePrivs, DWORD nRestrictSids, PSID_AND_ATTRIBUTES restrictSids, PHANDLE newToken)
{
    struct qemu_CreateRestrictedToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATERESTRICTEDTOKEN);
    call.baseToken = (uint64_t)baseToken;
    call.flags = (uint64_t)flags;
    call.nDisableSids = (uint64_t)nDisableSids;
    call.disableSids = (uint64_t)disableSids;
    call.nDeletePrivs = (uint64_t)nDeletePrivs;
    call.deletePrivs = (uint64_t)deletePrivs;
    call.nRestrictSids = (uint64_t)nRestrictSids;
    call.restrictSids = (uint64_t)restrictSids;
    call.newToken = (uint64_t)newToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateRestrictedToken(struct qemu_syscall *call)
{
    struct qemu_CreateRestrictedToken *c = (struct qemu_CreateRestrictedToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateRestrictedToken(QEMU_G2H(c->baseToken), c->flags, c->nDisableSids, QEMU_G2H(c->disableSids), c->nDeletePrivs, QEMU_G2H(c->deletePrivs), c->nRestrictSids, QEMU_G2H(c->restrictSids), QEMU_G2H(c->newToken));
}

#endif

struct qemu_AllocateAndInitializeSid
{
    struct qemu_syscall super;
    uint64_t pIdentifierAuthority;
    uint64_t nSubAuthorityCount;
    uint64_t nSubAuthority0;
    uint64_t nSubAuthority1;
    uint64_t nSubAuthority2;
    uint64_t nSubAuthority3;
    uint64_t nSubAuthority4;
    uint64_t nSubAuthority5;
    uint64_t nSubAuthority6;
    uint64_t nSubAuthority7;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AllocateAndInitializeSid(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7, PSID *pSid)
{
    struct qemu_AllocateAndInitializeSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEANDINITIALIZESID);
    call.pIdentifierAuthority = (uint64_t)pIdentifierAuthority;
    call.nSubAuthorityCount = (uint64_t)nSubAuthorityCount;
    call.nSubAuthority0 = (uint64_t)nSubAuthority0;
    call.nSubAuthority1 = (uint64_t)nSubAuthority1;
    call.nSubAuthority2 = (uint64_t)nSubAuthority2;
    call.nSubAuthority3 = (uint64_t)nSubAuthority3;
    call.nSubAuthority4 = (uint64_t)nSubAuthority4;
    call.nSubAuthority5 = (uint64_t)nSubAuthority5;
    call.nSubAuthority6 = (uint64_t)nSubAuthority6;
    call.nSubAuthority7 = (uint64_t)nSubAuthority7;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AllocateAndInitializeSid(struct qemu_syscall *call)
{
    struct qemu_AllocateAndInitializeSid *c = (struct qemu_AllocateAndInitializeSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateAndInitializeSid(QEMU_G2H(c->pIdentifierAuthority), c->nSubAuthorityCount, c->nSubAuthority0, c->nSubAuthority1, c->nSubAuthority2, c->nSubAuthority3, c->nSubAuthority4, c->nSubAuthority5, c->nSubAuthority6, c->nSubAuthority7, QEMU_G2H(c->pSid));
}

#endif

struct qemu_FreeSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI FreeSid(PSID pSid)
{
    struct qemu_FreeSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREESID);
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return (PVOID)call.super.iret;
}

#else

void qemu_FreeSid(struct qemu_syscall *call)
{
    struct qemu_FreeSid *c = (struct qemu_FreeSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FreeSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_CopySid
{
    struct qemu_syscall super;
    uint64_t nDestinationSidLength;
    uint64_t pDestinationSid;
    uint64_t pSourceSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CopySid(DWORD nDestinationSidLength, PSID pDestinationSid, PSID pSourceSid)
{
    struct qemu_CopySid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYSID);
    call.nDestinationSidLength = (uint64_t)nDestinationSidLength;
    call.pDestinationSid = (uint64_t)pDestinationSid;
    call.pSourceSid = (uint64_t)pSourceSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopySid(struct qemu_syscall *call)
{
    struct qemu_CopySid *c = (struct qemu_CopySid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CopySid(c->nDestinationSidLength, QEMU_G2H(c->pDestinationSid), QEMU_G2H(c->pSourceSid));
}

#endif

struct qemu_CreateWellKnownSid
{
    struct qemu_syscall super;
    uint64_t WellKnownSidType;
    uint64_t DomainSid;
    uint64_t pSid;
    uint64_t cbSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateWellKnownSid(WELL_KNOWN_SID_TYPE WellKnownSidType, PSID DomainSid, PSID pSid, DWORD* cbSid)
{
    struct qemu_CreateWellKnownSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWELLKNOWNSID);
    call.WellKnownSidType = (uint64_t)WellKnownSidType;
    call.DomainSid = (uint64_t)DomainSid;
    call.pSid = (uint64_t)pSid;
    call.cbSid = (uint64_t)cbSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateWellKnownSid(struct qemu_syscall *call)
{
    struct qemu_CreateWellKnownSid *c = (struct qemu_CreateWellKnownSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateWellKnownSid(c->WellKnownSidType, QEMU_G2H(c->DomainSid), QEMU_G2H(c->pSid), QEMU_G2H(c->cbSid));
}

#endif

struct qemu_IsWellKnownSid
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t WellKnownSidType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsWellKnownSid(PSID pSid, WELL_KNOWN_SID_TYPE WellKnownSidType)
{
    struct qemu_IsWellKnownSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWELLKNOWNSID);
    call.pSid = (uint64_t)pSid;
    call.WellKnownSidType = (uint64_t)WellKnownSidType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWellKnownSid(struct qemu_syscall *call)
{
    struct qemu_IsWellKnownSid *c = (struct qemu_IsWellKnownSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsWellKnownSid(QEMU_G2H(c->pSid), c->WellKnownSidType);
}

#endif

struct qemu_IsTokenRestricted
{
    struct qemu_syscall super;
    uint64_t TokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsTokenRestricted(HANDLE TokenHandle)
{
    struct qemu_IsTokenRestricted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTOKENRESTRICTED);
    call.TokenHandle = (uint64_t)TokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsTokenRestricted(struct qemu_syscall *call)
{
    struct qemu_IsTokenRestricted *c = (struct qemu_IsTokenRestricted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsTokenRestricted(QEMU_G2H(c->TokenHandle));
}

#endif

struct qemu_IsValidSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidSid(PSID pSid)
{
    struct qemu_IsValidSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDSID);
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidSid(struct qemu_syscall *call)
{
    struct qemu_IsValidSid *c = (struct qemu_IsValidSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsValidSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_EqualSid
{
    struct qemu_syscall super;
    uint64_t pSid1;
    uint64_t pSid2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EqualSid(PSID pSid1, PSID pSid2)
{
    struct qemu_EqualSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EQUALSID);
    call.pSid1 = (uint64_t)pSid1;
    call.pSid2 = (uint64_t)pSid2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EqualSid(struct qemu_syscall *call)
{
    struct qemu_EqualSid *c = (struct qemu_EqualSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EqualSid(QEMU_G2H(c->pSid1), QEMU_G2H(c->pSid2));
}

#endif

struct qemu_EqualPrefixSid
{
    struct qemu_syscall super;
    uint64_t pSid1;
    uint64_t pSid2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EqualPrefixSid (PSID pSid1, PSID pSid2)
{
    struct qemu_EqualPrefixSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EQUALPREFIXSID);
    call.pSid1 = (uint64_t)pSid1;
    call.pSid2 = (uint64_t)pSid2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EqualPrefixSid(struct qemu_syscall *call)
{
    struct qemu_EqualPrefixSid *c = (struct qemu_EqualPrefixSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EqualPrefixSid(QEMU_G2H(c->pSid1), QEMU_G2H(c->pSid2));
}

#endif

struct qemu_GetSidLengthRequired
{
    struct qemu_syscall super;
    uint64_t nSubAuthorityCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetSidLengthRequired(BYTE nSubAuthorityCount)
{
    struct qemu_GetSidLengthRequired call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSIDLENGTHREQUIRED);
    call.nSubAuthorityCount = (uint64_t)nSubAuthorityCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSidLengthRequired(struct qemu_syscall *call)
{
    struct qemu_GetSidLengthRequired *c = (struct qemu_GetSidLengthRequired *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSidLengthRequired(c->nSubAuthorityCount);
}

#endif

struct qemu_InitializeSid
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t pIdentifierAuthority;
    uint64_t nSubAuthorityCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitializeSid (PSID pSid, PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount)
{
    struct qemu_InitializeSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZESID);
    call.pSid = (uint64_t)pSid;
    call.pIdentifierAuthority = (uint64_t)pIdentifierAuthority;
    call.nSubAuthorityCount = (uint64_t)nSubAuthorityCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeSid(struct qemu_syscall *call)
{
    struct qemu_InitializeSid *c = (struct qemu_InitializeSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitializeSid(QEMU_G2H(c->pSid), QEMU_G2H(c->pIdentifierAuthority), c->nSubAuthorityCount);
}

#endif

struct qemu_GetEffectiveRightsFromAclA
{
    struct qemu_syscall super;
    uint64_t pacl;
    uint64_t pTrustee;
    uint64_t pAccessRights;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetEffectiveRightsFromAclA(PACL pacl, PTRUSTEEA pTrustee, PACCESS_MASK pAccessRights)
{
    struct qemu_GetEffectiveRightsFromAclA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEFFECTIVERIGHTSFROMACLA);
    call.pacl = (uint64_t)pacl;
    call.pTrustee = (uint64_t)pTrustee;
    call.pAccessRights = (uint64_t)pAccessRights;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEffectiveRightsFromAclA(struct qemu_syscall *call)
{
    struct qemu_GetEffectiveRightsFromAclA *c = (struct qemu_GetEffectiveRightsFromAclA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetEffectiveRightsFromAclA(QEMU_G2H(c->pacl), QEMU_G2H(c->pTrustee), QEMU_G2H(c->pAccessRights));
}

#endif

struct qemu_GetEffectiveRightsFromAclW
{
    struct qemu_syscall super;
    uint64_t pacl;
    uint64_t pTrustee;
    uint64_t pAccessRights;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetEffectiveRightsFromAclW(PACL pacl, PTRUSTEEW pTrustee, PACCESS_MASK pAccessRights)
{
    struct qemu_GetEffectiveRightsFromAclW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEFFECTIVERIGHTSFROMACLW);
    call.pacl = (uint64_t)pacl;
    call.pTrustee = (uint64_t)pTrustee;
    call.pAccessRights = (uint64_t)pAccessRights;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEffectiveRightsFromAclW(struct qemu_syscall *call)
{
    struct qemu_GetEffectiveRightsFromAclW *c = (struct qemu_GetEffectiveRightsFromAclW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetEffectiveRightsFromAclW(QEMU_G2H(c->pacl), QEMU_G2H(c->pTrustee), QEMU_G2H(c->pAccessRights));
}

#endif

struct qemu_GetSidIdentifierAuthority
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PSID_IDENTIFIER_AUTHORITY WINAPI GetSidIdentifierAuthority(PSID pSid)
{
    struct qemu_GetSidIdentifierAuthority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSIDIDENTIFIERAUTHORITY);
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return (PSID_IDENTIFIER_AUTHORITY)call.super.iret;
}

#else

void qemu_GetSidIdentifierAuthority(struct qemu_syscall *call)
{
    struct qemu_GetSidIdentifierAuthority *c = (struct qemu_GetSidIdentifierAuthority *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetSidIdentifierAuthority(QEMU_G2H(c->pSid));
}

#endif

struct qemu_GetSidSubAuthority
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t nSubAuthority;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PDWORD WINAPI GetSidSubAuthority(PSID pSid, DWORD nSubAuthority)
{
    struct qemu_GetSidSubAuthority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSIDSUBAUTHORITY);
    call.pSid = (uint64_t)pSid;
    call.nSubAuthority = (uint64_t)nSubAuthority;

    qemu_syscall(&call.super);

    return (PDWORD)call.super.iret;
}

#else

void qemu_GetSidSubAuthority(struct qemu_syscall *call)
{
    struct qemu_GetSidSubAuthority *c = (struct qemu_GetSidSubAuthority *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetSidSubAuthority(QEMU_G2H(c->pSid), c->nSubAuthority);
}

#endif

struct qemu_GetSidSubAuthorityCount
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PUCHAR WINAPI GetSidSubAuthorityCount (PSID pSid)
{
    struct qemu_GetSidSubAuthorityCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSIDSUBAUTHORITYCOUNT);
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return (PUCHAR)call.super.iret;
}

#else

void qemu_GetSidSubAuthorityCount(struct qemu_syscall *call)
{
    struct qemu_GetSidSubAuthorityCount *c = (struct qemu_GetSidSubAuthorityCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetSidSubAuthorityCount(QEMU_G2H(c->pSid));
}

#endif

struct qemu_GetLengthSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetLengthSid (PSID pSid)
{
    struct qemu_GetLengthSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLENGTHSID);
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLengthSid(struct qemu_syscall *call)
{
    struct qemu_GetLengthSid *c = (struct qemu_GetLengthSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLengthSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_BuildSecurityDescriptorA
{
    struct qemu_syscall super;
    uint64_t pOwner;
    uint64_t pGroup;
    uint64_t cCountOfAccessEntries;
    uint64_t pListOfAccessEntries;
    uint64_t cCountOfAuditEntries;
    uint64_t pListofAuditEntries;
    uint64_t pOldSD;
    uint64_t lpdwBufferLength;
    uint64_t pNewSD;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI BuildSecurityDescriptorA(IN PTRUSTEEA pOwner, IN PTRUSTEEA pGroup, IN ULONG cCountOfAccessEntries, IN PEXPLICIT_ACCESSA pListOfAccessEntries, IN ULONG cCountOfAuditEntries, IN PEXPLICIT_ACCESSA pListofAuditEntries, IN PSECURITY_DESCRIPTOR pOldSD, IN OUT PULONG lpdwBufferLength, OUT PSECURITY_DESCRIPTOR* pNewSD)
{
    struct qemu_BuildSecurityDescriptorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDSECURITYDESCRIPTORA);
    call.pOwner = (uint64_t)pOwner;
    call.pGroup = (uint64_t)pGroup;
    call.cCountOfAccessEntries = (uint64_t)cCountOfAccessEntries;
    call.pListOfAccessEntries = (uint64_t)pListOfAccessEntries;
    call.cCountOfAuditEntries = (uint64_t)cCountOfAuditEntries;
    call.pListofAuditEntries = (uint64_t)pListofAuditEntries;
    call.pOldSD = (uint64_t)pOldSD;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;
    call.pNewSD = (uint64_t)pNewSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BuildSecurityDescriptorA(struct qemu_syscall *call)
{
    struct qemu_BuildSecurityDescriptorA *c = (struct qemu_BuildSecurityDescriptorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BuildSecurityDescriptorA(QEMU_G2H(c->pOwner), QEMU_G2H(c->pGroup), c->cCountOfAccessEntries, QEMU_G2H(c->pListOfAccessEntries), c->cCountOfAuditEntries, QEMU_G2H(c->pListofAuditEntries), QEMU_G2H(c->pOldSD), QEMU_G2H(c->lpdwBufferLength), QEMU_G2H(c->pNewSD));
}

#endif

struct qemu_BuildSecurityDescriptorW
{
    struct qemu_syscall super;
    uint64_t pOwner;
    uint64_t pGroup;
    uint64_t cCountOfAccessEntries;
    uint64_t pListOfAccessEntries;
    uint64_t cCountOfAuditEntries;
    uint64_t pListofAuditEntries;
    uint64_t pOldSD;
    uint64_t lpdwBufferLength;
    uint64_t pNewSD;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI BuildSecurityDescriptorW(IN PTRUSTEEW pOwner, IN PTRUSTEEW pGroup, IN ULONG cCountOfAccessEntries, IN PEXPLICIT_ACCESSW pListOfAccessEntries, IN ULONG cCountOfAuditEntries, IN PEXPLICIT_ACCESSW pListofAuditEntries, IN PSECURITY_DESCRIPTOR pOldSD, IN OUT PULONG lpdwBufferLength, OUT PSECURITY_DESCRIPTOR* pNewSD)
{
    struct qemu_BuildSecurityDescriptorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDSECURITYDESCRIPTORW);
    call.pOwner = (uint64_t)pOwner;
    call.pGroup = (uint64_t)pGroup;
    call.cCountOfAccessEntries = (uint64_t)cCountOfAccessEntries;
    call.pListOfAccessEntries = (uint64_t)pListOfAccessEntries;
    call.cCountOfAuditEntries = (uint64_t)cCountOfAuditEntries;
    call.pListofAuditEntries = (uint64_t)pListofAuditEntries;
    call.pOldSD = (uint64_t)pOldSD;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;
    call.pNewSD = (uint64_t)pNewSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BuildSecurityDescriptorW(struct qemu_syscall *call)
{
    struct qemu_BuildSecurityDescriptorW *c = (struct qemu_BuildSecurityDescriptorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BuildSecurityDescriptorW(QEMU_G2H(c->pOwner), QEMU_G2H(c->pGroup), c->cCountOfAccessEntries, QEMU_G2H(c->pListOfAccessEntries), c->cCountOfAuditEntries, QEMU_G2H(c->pListofAuditEntries), QEMU_G2H(c->pOldSD), QEMU_G2H(c->lpdwBufferLength), QEMU_G2H(c->pNewSD));
}

#endif

struct qemu_InitializeSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pDescr;
    uint64_t revision;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitializeSecurityDescriptor(PSECURITY_DESCRIPTOR pDescr, DWORD revision)
{
    struct qemu_InitializeSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZESECURITYDESCRIPTOR);
    call.pDescr = (uint64_t)pDescr;
    call.revision = (uint64_t)revision;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_InitializeSecurityDescriptor *c = (struct qemu_InitializeSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitializeSecurityDescriptor(QEMU_G2H(c->pDescr), c->revision);
}

#endif

struct qemu_MakeAbsoluteSD
{
    struct qemu_syscall super;
    uint64_t pSelfRelativeSecurityDescriptor;
    uint64_t pAbsoluteSecurityDescriptor;
    uint64_t lpdwAbsoluteSecurityDescriptorSize;
    uint64_t pDacl;
    uint64_t lpdwDaclSize;
    uint64_t pSacl;
    uint64_t lpdwSaclSize;
    uint64_t pOwner;
    uint64_t lpdwOwnerSize;
    uint64_t pPrimaryGroup;
    uint64_t lpdwPrimaryGroupSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MakeAbsoluteSD (IN PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, OUT PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, OUT LPDWORD lpdwAbsoluteSecurityDescriptorSize, OUT PACL pDacl, OUT LPDWORD lpdwDaclSize, OUT PACL pSacl, OUT LPDWORD lpdwSaclSize, OUT PSID pOwner, OUT LPDWORD lpdwOwnerSize, OUT PSID pPrimaryGroup, OUT LPDWORD lpdwPrimaryGroupSize)
{
    struct qemu_MakeAbsoluteSD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAKEABSOLUTESD);
    call.pSelfRelativeSecurityDescriptor = (uint64_t)pSelfRelativeSecurityDescriptor;
    call.pAbsoluteSecurityDescriptor = (uint64_t)pAbsoluteSecurityDescriptor;
    call.lpdwAbsoluteSecurityDescriptorSize = (uint64_t)lpdwAbsoluteSecurityDescriptorSize;
    call.pDacl = (uint64_t)pDacl;
    call.lpdwDaclSize = (uint64_t)lpdwDaclSize;
    call.pSacl = (uint64_t)pSacl;
    call.lpdwSaclSize = (uint64_t)lpdwSaclSize;
    call.pOwner = (uint64_t)pOwner;
    call.lpdwOwnerSize = (uint64_t)lpdwOwnerSize;
    call.pPrimaryGroup = (uint64_t)pPrimaryGroup;
    call.lpdwPrimaryGroupSize = (uint64_t)lpdwPrimaryGroupSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MakeAbsoluteSD(struct qemu_syscall *call)
{
    struct qemu_MakeAbsoluteSD *c = (struct qemu_MakeAbsoluteSD *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MakeAbsoluteSD(QEMU_G2H(c->pSelfRelativeSecurityDescriptor), QEMU_G2H(c->pAbsoluteSecurityDescriptor), QEMU_G2H(c->lpdwAbsoluteSecurityDescriptorSize), QEMU_G2H(c->pDacl), QEMU_G2H(c->lpdwDaclSize), QEMU_G2H(c->pSacl), QEMU_G2H(c->lpdwSaclSize), QEMU_G2H(c->pOwner), QEMU_G2H(c->lpdwOwnerSize), QEMU_G2H(c->pPrimaryGroup), QEMU_G2H(c->lpdwPrimaryGroupSize));
}

#endif

struct qemu_GetKernelObjectSecurity
{
    struct qemu_syscall super;
    uint64_t Handle;
    uint64_t RequestedInformation;
    uint64_t pSecurityDescriptor;
    uint64_t nLength;
    uint64_t lpnLengthNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetKernelObjectSecurity(HANDLE Handle, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded)
{
    struct qemu_GetKernelObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETKERNELOBJECTSECURITY);
    call.Handle = (uint64_t)Handle;
    call.RequestedInformation = (uint64_t)RequestedInformation;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.nLength = (uint64_t)nLength;
    call.lpnLengthNeeded = (uint64_t)lpnLengthNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetKernelObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_GetKernelObjectSecurity *c = (struct qemu_GetKernelObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetKernelObjectSecurity(QEMU_G2H(c->Handle), c->RequestedInformation, QEMU_G2H(c->pSecurityDescriptor), c->nLength, QEMU_G2H(c->lpnLengthNeeded));
}

#endif

struct qemu_GetPrivateObjectSecurity
{
    struct qemu_syscall super;
    uint64_t ObjectDescriptor;
    uint64_t SecurityInformation;
    uint64_t ResultantDescriptor;
    uint64_t DescriptorLength;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrivateObjectSecurity(PSECURITY_DESCRIPTOR ObjectDescriptor, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR ResultantDescriptor, DWORD DescriptorLength, PDWORD ReturnLength)
{
    struct qemu_GetPrivateObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIVATEOBJECTSECURITY);
    call.ObjectDescriptor = (uint64_t)ObjectDescriptor;
    call.SecurityInformation = (uint64_t)SecurityInformation;
    call.ResultantDescriptor = (uint64_t)ResultantDescriptor;
    call.DescriptorLength = (uint64_t)DescriptorLength;
    call.ReturnLength = (uint64_t)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrivateObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_GetPrivateObjectSecurity *c = (struct qemu_GetPrivateObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrivateObjectSecurity(QEMU_G2H(c->ObjectDescriptor), c->SecurityInformation, QEMU_G2H(c->ResultantDescriptor), c->DescriptorLength, QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_GetSecurityDescriptorLength
{
    struct qemu_syscall super;
    uint64_t pDescr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetSecurityDescriptorLength(PSECURITY_DESCRIPTOR pDescr)
{
    struct qemu_GetSecurityDescriptorLength call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYDESCRIPTORLENGTH);
    call.pDescr = (uint64_t)pDescr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityDescriptorLength(struct qemu_syscall *call)
{
    struct qemu_GetSecurityDescriptorLength *c = (struct qemu_GetSecurityDescriptorLength *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityDescriptorLength(QEMU_G2H(c->pDescr));
}

#endif

struct qemu_GetSecurityDescriptorOwner
{
    struct qemu_syscall super;
    uint64_t pDescr;
    uint64_t pOwner;
    uint64_t lpbOwnerDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSecurityDescriptorOwner(PSECURITY_DESCRIPTOR pDescr, PSID *pOwner, LPBOOL lpbOwnerDefaulted)
{
    struct qemu_GetSecurityDescriptorOwner call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYDESCRIPTOROWNER);
    call.pDescr = (uint64_t)pDescr;
    call.pOwner = (uint64_t)pOwner;
    call.lpbOwnerDefaulted = (uint64_t)lpbOwnerDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityDescriptorOwner(struct qemu_syscall *call)
{
    struct qemu_GetSecurityDescriptorOwner *c = (struct qemu_GetSecurityDescriptorOwner *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityDescriptorOwner(QEMU_G2H(c->pDescr), QEMU_G2H(c->pOwner), QEMU_G2H(c->lpbOwnerDefaulted));
}

#endif

struct qemu_SetSecurityDescriptorOwner
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t pOwner;
    uint64_t bOwnerDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSecurityDescriptorOwner(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID pOwner, BOOL bOwnerDefaulted)
{
    struct qemu_SetSecurityDescriptorOwner call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSECURITYDESCRIPTOROWNER);
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.pOwner = (uint64_t)pOwner;
    call.bOwnerDefaulted = (uint64_t)bOwnerDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSecurityDescriptorOwner(struct qemu_syscall *call)
{
    struct qemu_SetSecurityDescriptorOwner *c = (struct qemu_SetSecurityDescriptorOwner *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSecurityDescriptorOwner(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->pOwner), c->bOwnerDefaulted);
}

#endif

struct qemu_GetSecurityDescriptorGroup
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t Group;
    uint64_t GroupDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSecurityDescriptorGroup(PSECURITY_DESCRIPTOR SecurityDescriptor, PSID *Group, LPBOOL GroupDefaulted)
{
    struct qemu_GetSecurityDescriptorGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYDESCRIPTORGROUP);
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.Group = (uint64_t)Group;
    call.GroupDefaulted = (uint64_t)GroupDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityDescriptorGroup(struct qemu_syscall *call)
{
    struct qemu_GetSecurityDescriptorGroup *c = (struct qemu_GetSecurityDescriptorGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityDescriptorGroup(QEMU_G2H(c->SecurityDescriptor), QEMU_G2H(c->Group), QEMU_G2H(c->GroupDefaulted));
}

#endif

struct qemu_SetSecurityDescriptorGroup
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t Group;
    uint64_t GroupDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSecurityDescriptorGroup (PSECURITY_DESCRIPTOR SecurityDescriptor, PSID Group, BOOL GroupDefaulted)
{
    struct qemu_SetSecurityDescriptorGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSECURITYDESCRIPTORGROUP);
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.Group = (uint64_t)Group;
    call.GroupDefaulted = (uint64_t)GroupDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSecurityDescriptorGroup(struct qemu_syscall *call)
{
    struct qemu_SetSecurityDescriptorGroup *c = (struct qemu_SetSecurityDescriptorGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSecurityDescriptorGroup(QEMU_G2H(c->SecurityDescriptor), QEMU_G2H(c->Group), c->GroupDefaulted);
}

#endif

struct qemu_IsValidSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidSecurityDescriptor(PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    struct qemu_IsValidSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDSECURITYDESCRIPTOR);
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_IsValidSecurityDescriptor *c = (struct qemu_IsValidSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsValidSecurityDescriptor(QEMU_G2H(c->SecurityDescriptor));
}

#endif

struct qemu_GetSecurityDescriptorDacl
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t lpbDaclPresent;
    uint64_t pDacl;
    uint64_t lpbDaclDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSecurityDescriptorDacl(IN PSECURITY_DESCRIPTOR pSecurityDescriptor, OUT LPBOOL lpbDaclPresent, OUT PACL *pDacl, OUT LPBOOL lpbDaclDefaulted)
{
    struct qemu_GetSecurityDescriptorDacl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYDESCRIPTORDACL);
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.lpbDaclPresent = (uint64_t)lpbDaclPresent;
    call.pDacl = (uint64_t)pDacl;
    call.lpbDaclDefaulted = (uint64_t)lpbDaclDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityDescriptorDacl(struct qemu_syscall *call)
{
    struct qemu_GetSecurityDescriptorDacl *c = (struct qemu_GetSecurityDescriptorDacl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityDescriptorDacl(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->lpbDaclPresent), QEMU_G2H(c->pDacl), QEMU_G2H(c->lpbDaclDefaulted));
}

#endif

struct qemu_SetSecurityDescriptorDacl
{
    struct qemu_syscall super;
    uint64_t lpsd;
    uint64_t daclpresent;
    uint64_t dacl;
    uint64_t dacldefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSecurityDescriptorDacl (PSECURITY_DESCRIPTOR lpsd, BOOL daclpresent, PACL dacl, BOOL dacldefaulted)
{
    struct qemu_SetSecurityDescriptorDacl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSECURITYDESCRIPTORDACL);
    call.lpsd = (uint64_t)lpsd;
    call.daclpresent = (uint64_t)daclpresent;
    call.dacl = (uint64_t)dacl;
    call.dacldefaulted = (uint64_t)dacldefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSecurityDescriptorDacl(struct qemu_syscall *call)
{
    struct qemu_SetSecurityDescriptorDacl *c = (struct qemu_SetSecurityDescriptorDacl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSecurityDescriptorDacl(QEMU_G2H(c->lpsd), c->daclpresent, QEMU_G2H(c->dacl), c->dacldefaulted);
}

#endif

struct qemu_GetSecurityDescriptorSacl
{
    struct qemu_syscall super;
    uint64_t lpsd;
    uint64_t lpbSaclPresent;
    uint64_t pSacl;
    uint64_t lpbSaclDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSecurityDescriptorSacl(IN PSECURITY_DESCRIPTOR lpsd, OUT LPBOOL lpbSaclPresent, OUT PACL *pSacl, OUT LPBOOL lpbSaclDefaulted)
{
    struct qemu_GetSecurityDescriptorSacl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYDESCRIPTORSACL);
    call.lpsd = (uint64_t)lpsd;
    call.lpbSaclPresent = (uint64_t)lpbSaclPresent;
    call.pSacl = (uint64_t)pSacl;
    call.lpbSaclDefaulted = (uint64_t)lpbSaclDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityDescriptorSacl(struct qemu_syscall *call)
{
    struct qemu_GetSecurityDescriptorSacl *c = (struct qemu_GetSecurityDescriptorSacl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityDescriptorSacl(QEMU_G2H(c->lpsd), QEMU_G2H(c->lpbSaclPresent), QEMU_G2H(c->pSacl), QEMU_G2H(c->lpbSaclDefaulted));
}

#endif

struct qemu_SetSecurityDescriptorSacl
{
    struct qemu_syscall super;
    uint64_t lpsd;
    uint64_t saclpresent;
    uint64_t lpsacl;
    uint64_t sacldefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSecurityDescriptorSacl (PSECURITY_DESCRIPTOR lpsd, BOOL saclpresent, PACL lpsacl, BOOL sacldefaulted)
{
    struct qemu_SetSecurityDescriptorSacl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSECURITYDESCRIPTORSACL);
    call.lpsd = (uint64_t)lpsd;
    call.saclpresent = (uint64_t)saclpresent;
    call.lpsacl = (uint64_t)lpsacl;
    call.sacldefaulted = (uint64_t)sacldefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSecurityDescriptorSacl(struct qemu_syscall *call)
{
    struct qemu_SetSecurityDescriptorSacl *c = (struct qemu_SetSecurityDescriptorSacl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSecurityDescriptorSacl(QEMU_G2H(c->lpsd), c->saclpresent, QEMU_G2H(c->lpsacl), c->sacldefaulted);
}

#endif

struct qemu_MakeSelfRelativeSD
{
    struct qemu_syscall super;
    uint64_t pAbsoluteSecurityDescriptor;
    uint64_t pSelfRelativeSecurityDescriptor;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MakeSelfRelativeSD(IN PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, IN PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, IN OUT LPDWORD lpdwBufferLength)
{
    struct qemu_MakeSelfRelativeSD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAKESELFRELATIVESD);
    call.pAbsoluteSecurityDescriptor = (uint64_t)pAbsoluteSecurityDescriptor;
    call.pSelfRelativeSecurityDescriptor = (uint64_t)pSelfRelativeSecurityDescriptor;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MakeSelfRelativeSD(struct qemu_syscall *call)
{
    struct qemu_MakeSelfRelativeSD *c = (struct qemu_MakeSelfRelativeSD *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MakeSelfRelativeSD(QEMU_G2H(c->pAbsoluteSecurityDescriptor), QEMU_G2H(c->pSelfRelativeSecurityDescriptor), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_GetSecurityDescriptorControl
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t pControl;
    uint64_t lpdwRevision;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSecurityDescriptorControl (PSECURITY_DESCRIPTOR pSecurityDescriptor, PSECURITY_DESCRIPTOR_CONTROL pControl, LPDWORD lpdwRevision)
{
    struct qemu_GetSecurityDescriptorControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYDESCRIPTORCONTROL);
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.pControl = (uint64_t)pControl;
    call.lpdwRevision = (uint64_t)lpdwRevision;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityDescriptorControl(struct qemu_syscall *call)
{
    struct qemu_GetSecurityDescriptorControl *c = (struct qemu_GetSecurityDescriptorControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityDescriptorControl(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->pControl), QEMU_G2H(c->lpdwRevision));
}

#endif

struct qemu_SetSecurityDescriptorControl
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t ControlBitsOfInterest;
    uint64_t ControlBitsToSet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSecurityDescriptorControl(PSECURITY_DESCRIPTOR pSecurityDescriptor, SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest, SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet)
{
    struct qemu_SetSecurityDescriptorControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSECURITYDESCRIPTORCONTROL);
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.ControlBitsOfInterest = (uint64_t)ControlBitsOfInterest;
    call.ControlBitsToSet = (uint64_t)ControlBitsToSet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSecurityDescriptorControl(struct qemu_syscall *call)
{
    struct qemu_SetSecurityDescriptorControl *c = (struct qemu_SetSecurityDescriptorControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSecurityDescriptorControl(QEMU_G2H(c->pSecurityDescriptor), c->ControlBitsOfInterest, c->ControlBitsToSet);
}

#endif

struct qemu_GetWindowsAccountDomainSid
{
    struct qemu_syscall super;
    uint64_t sid;
    uint64_t domain_sid;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetWindowsAccountDomainSid(PSID sid, PSID domain_sid, DWORD *size)
{
    struct qemu_GetWindowsAccountDomainSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWSACCOUNTDOMAINSID);
    call.sid = (uint64_t)sid;
    call.domain_sid = (uint64_t)domain_sid;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetWindowsAccountDomainSid to Wine headers? */
extern BOOL WINAPI GetWindowsAccountDomainSid(PSID sid, PSID domain_sid, DWORD *size);
void qemu_GetWindowsAccountDomainSid(struct qemu_syscall *call)
{
    struct qemu_GetWindowsAccountDomainSid *c = (struct qemu_GetWindowsAccountDomainSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWindowsAccountDomainSid(QEMU_G2H(c->sid), QEMU_G2H(c->domain_sid), QEMU_G2H(c->size));
}

#endif

struct qemu_InitializeAcl
{
    struct qemu_syscall super;
    uint64_t acl;
    uint64_t size;
    uint64_t rev;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitializeAcl(PACL acl, DWORD size, DWORD rev)
{
    struct qemu_InitializeAcl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZEACL);
    call.acl = (uint64_t)acl;
    call.size = (uint64_t)size;
    call.rev = (uint64_t)rev;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeAcl(struct qemu_syscall *call)
{
    struct qemu_InitializeAcl *c = (struct qemu_InitializeAcl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitializeAcl(QEMU_G2H(c->acl), c->size, c->rev);
}

#endif

struct qemu_ImpersonateNamedPipeClient
{
    struct qemu_syscall super;
    uint64_t hNamedPipe;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImpersonateNamedPipeClient(HANDLE hNamedPipe)
{
    struct qemu_ImpersonateNamedPipeClient call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPERSONATENAMEDPIPECLIENT);
    call.hNamedPipe = (uint64_t)hNamedPipe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImpersonateNamedPipeClient(struct qemu_syscall *call)
{
    struct qemu_ImpersonateNamedPipeClient *c = (struct qemu_ImpersonateNamedPipeClient *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImpersonateNamedPipeClient(QEMU_G2H(c->hNamedPipe));
}

#endif

struct qemu_AddAccessAllowedAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAccessAllowedAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_AddAccessAllowedAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACCESSALLOWEDACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.AccessMask = (uint64_t)AccessMask;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAccessAllowedAce(struct qemu_syscall *call)
{
    struct qemu_AddAccessAllowedAce *c = (struct qemu_AddAccessAllowedAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAccessAllowedAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_AddAccessAllowedAceEx
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AceFlags;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAccessAllowedAceEx(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AceFlags, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_AddAccessAllowedAceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACCESSALLOWEDACEEX);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.AceFlags = (uint64_t)AceFlags;
    call.AccessMask = (uint64_t)AccessMask;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAccessAllowedAceEx(struct qemu_syscall *call)
{
    struct qemu_AddAccessAllowedAceEx *c = (struct qemu_AddAccessAllowedAceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAccessAllowedAceEx(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AceFlags, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_AddAccessAllowedObjectAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwAceFlags;
    uint64_t dwAccessMask;
    uint64_t pObjectTypeGuid;
    uint64_t pInheritedObjectTypeGuid;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAccessAllowedObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid)
{
    struct qemu_AddAccessAllowedObjectAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACCESSALLOWEDOBJECTACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.dwAceFlags = (uint64_t)dwAceFlags;
    call.dwAccessMask = (uint64_t)dwAccessMask;
    call.pObjectTypeGuid = (uint64_t)pObjectTypeGuid;
    call.pInheritedObjectTypeGuid = (uint64_t)pInheritedObjectTypeGuid;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AddAccessAllowedObjectAce to Wine headers? */
extern BOOL WINAPI AddAccessAllowedObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid);
void qemu_AddAccessAllowedObjectAce(struct qemu_syscall *call)
{
    struct qemu_AddAccessAllowedObjectAce *c = (struct qemu_AddAccessAllowedObjectAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAccessAllowedObjectAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pObjectTypeGuid), QEMU_G2H(c->pInheritedObjectTypeGuid), QEMU_G2H(c->pSid));
}

#endif

struct qemu_AddAccessDeniedAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAccessDeniedAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_AddAccessDeniedAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACCESSDENIEDACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.AccessMask = (uint64_t)AccessMask;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAccessDeniedAce(struct qemu_syscall *call)
{
    struct qemu_AddAccessDeniedAce *c = (struct qemu_AddAccessDeniedAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAccessDeniedAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_AddAccessDeniedAceEx
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AceFlags;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAccessDeniedAceEx(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AceFlags, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_AddAccessDeniedAceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACCESSDENIEDACEEX);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.AceFlags = (uint64_t)AceFlags;
    call.AccessMask = (uint64_t)AccessMask;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAccessDeniedAceEx(struct qemu_syscall *call)
{
    struct qemu_AddAccessDeniedAceEx *c = (struct qemu_AddAccessDeniedAceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAccessDeniedAceEx(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AceFlags, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_AddAccessDeniedObjectAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwAceFlags;
    uint64_t dwAccessMask;
    uint64_t pObjectTypeGuid;
    uint64_t pInheritedObjectTypeGuid;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAccessDeniedObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid)
{
    struct qemu_AddAccessDeniedObjectAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACCESSDENIEDOBJECTACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.dwAceFlags = (uint64_t)dwAceFlags;
    call.dwAccessMask = (uint64_t)dwAccessMask;
    call.pObjectTypeGuid = (uint64_t)pObjectTypeGuid;
    call.pInheritedObjectTypeGuid = (uint64_t)pInheritedObjectTypeGuid;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AddAccessDeniedObjectAce to Wine headers? */
extern BOOL WINAPI AddAccessDeniedObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid);
void qemu_AddAccessDeniedObjectAce(struct qemu_syscall *call)
{
    struct qemu_AddAccessDeniedObjectAce *c = (struct qemu_AddAccessDeniedObjectAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAccessDeniedObjectAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pObjectTypeGuid), QEMU_G2H(c->pInheritedObjectTypeGuid), QEMU_G2H(c->pSid));
}

#endif

struct qemu_AddAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwStartingAceIndex;
    uint64_t pAceList;
    uint64_t nAceListLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwStartingAceIndex, LPVOID pAceList, DWORD nAceListLength)
{
    struct qemu_AddAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.dwStartingAceIndex = (uint64_t)dwStartingAceIndex;
    call.pAceList = (uint64_t)pAceList;
    call.nAceListLength = (uint64_t)nAceListLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAce(struct qemu_syscall *call)
{
    struct qemu_AddAce *c = (struct qemu_AddAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwStartingAceIndex, QEMU_G2H(c->pAceList), c->nAceListLength);
}

#endif

struct qemu_AddMandatoryAce
{
    struct qemu_syscall super;
    uint64_t acl;
    uint64_t ace_revision;
    uint64_t ace_flags;
    uint64_t mandatory_policy;
    uint64_t label_sid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddMandatoryAce(ACL *acl, DWORD ace_revision, DWORD ace_flags, DWORD mandatory_policy, PSID label_sid)
{
    struct qemu_AddMandatoryAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDMANDATORYACE);
    call.acl = (uint64_t)acl;
    call.ace_revision = (uint64_t)ace_revision;
    call.ace_flags = (uint64_t)ace_flags;
    call.mandatory_policy = (uint64_t)mandatory_policy;
    call.label_sid = (uint64_t)label_sid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddMandatoryAce(struct qemu_syscall *call)
{
    struct qemu_AddMandatoryAce *c = (struct qemu_AddMandatoryAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddMandatoryAce(QEMU_G2H(c->acl), c->ace_revision, c->ace_flags, c->mandatory_policy, QEMU_G2H(c->label_sid));
}

#endif

struct qemu_DeleteAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteAce(PACL pAcl, DWORD dwAceIndex)
{
    struct qemu_DeleteAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceIndex = (uint64_t)dwAceIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteAce(struct qemu_syscall *call)
{
    struct qemu_DeleteAce *c = (struct qemu_DeleteAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteAce(QEMU_G2H(c->pAcl), c->dwAceIndex);
}

#endif

struct qemu_FindFirstFreeAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t pAce;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindFirstFreeAce(IN PACL pAcl, LPVOID * pAce)
{
    struct qemu_FindFirstFreeAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTFREEACE);
    call.pAcl = (uint64_t)pAcl;
    call.pAce = (uint64_t)pAce;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindFirstFreeAce(struct qemu_syscall *call)
{
    struct qemu_FindFirstFreeAce *c = (struct qemu_FindFirstFreeAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindFirstFreeAce(QEMU_G2H(c->pAcl), QEMU_G2H(c->pAce));
}

#endif

struct qemu_GetAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceIndex;
    uint64_t pAce;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetAce(PACL pAcl,DWORD dwAceIndex,LPVOID *pAce)
{
    struct qemu_GetAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceIndex = (uint64_t)dwAceIndex;
    call.pAce = (uint64_t)pAce;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAce(struct qemu_syscall *call)
{
    struct qemu_GetAce *c = (struct qemu_GetAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAce(QEMU_G2H(c->pAcl), c->dwAceIndex, QEMU_G2H(c->pAce));
}

#endif

struct qemu_GetAclInformation
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t pAclInformation;
    uint64_t nAclInformationLength;
    uint64_t dwAclInformationClass;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetAclInformation(PACL pAcl, LPVOID pAclInformation, DWORD nAclInformationLength, ACL_INFORMATION_CLASS dwAclInformationClass)
{
    struct qemu_GetAclInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACLINFORMATION);
    call.pAcl = (uint64_t)pAcl;
    call.pAclInformation = (uint64_t)pAclInformation;
    call.nAclInformationLength = (uint64_t)nAclInformationLength;
    call.dwAclInformationClass = (uint64_t)dwAclInformationClass;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAclInformation(struct qemu_syscall *call)
{
    struct qemu_GetAclInformation *c = (struct qemu_GetAclInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAclInformation(QEMU_G2H(c->pAcl), QEMU_G2H(c->pAclInformation), c->nAclInformationLength, c->dwAclInformationClass);
}

#endif

struct qemu_IsValidAcl
{
    struct qemu_syscall super;
    uint64_t pAcl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidAcl(IN PACL pAcl)
{
    struct qemu_IsValidAcl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDACL);
    call.pAcl = (uint64_t)pAcl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsValidAcl(struct qemu_syscall *call)
{
    struct qemu_IsValidAcl *c = (struct qemu_IsValidAcl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsValidAcl(QEMU_G2H(c->pAcl));
}

#endif

struct qemu_AllocateLocallyUniqueId
{
    struct qemu_syscall super;
    uint64_t lpLuid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AllocateLocallyUniqueId(PLUID lpLuid)
{
    struct qemu_AllocateLocallyUniqueId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATELOCALLYUNIQUEID);
    call.lpLuid = (uint64_t)lpLuid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AllocateLocallyUniqueId(struct qemu_syscall *call)
{
    struct qemu_AllocateLocallyUniqueId *c = (struct qemu_AllocateLocallyUniqueId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateLocallyUniqueId(QEMU_G2H(c->lpLuid));
}

#endif

struct qemu_LookupPrivilegeValueW
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpName;
    uint64_t lpLuid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupPrivilegeValueW(LPCWSTR lpSystemName, LPCWSTR lpName, PLUID lpLuid)
{
    struct qemu_LookupPrivilegeValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPPRIVILEGEVALUEW);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpName = (uint64_t)lpName;
    call.lpLuid = (uint64_t)lpLuid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupPrivilegeValueW(struct qemu_syscall *call)
{
    struct qemu_LookupPrivilegeValueW *c = (struct qemu_LookupPrivilegeValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupPrivilegeValueW(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpName), QEMU_G2H(c->lpLuid));
}

#endif

struct qemu_LookupPrivilegeValueA
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpName;
    uint64_t lpLuid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupPrivilegeValueA(LPCSTR lpSystemName, LPCSTR lpName, PLUID lpLuid)
{
    struct qemu_LookupPrivilegeValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPPRIVILEGEVALUEA);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpName = (uint64_t)lpName;
    call.lpLuid = (uint64_t)lpLuid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupPrivilegeValueA(struct qemu_syscall *call)
{
    struct qemu_LookupPrivilegeValueA *c = (struct qemu_LookupPrivilegeValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupPrivilegeValueA(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpName), QEMU_G2H(c->lpLuid));
}

#endif

struct qemu_LookupPrivilegeDisplayNameA
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpName;
    uint64_t lpDisplayName;
    uint64_t cchDisplayName;
    uint64_t lpLanguageId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupPrivilegeDisplayNameA(LPCSTR lpSystemName, LPCSTR lpName, LPSTR lpDisplayName, LPDWORD cchDisplayName, LPDWORD lpLanguageId)
{
    struct qemu_LookupPrivilegeDisplayNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPPRIVILEGEDISPLAYNAMEA);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpName = (uint64_t)lpName;
    call.lpDisplayName = (uint64_t)lpDisplayName;
    call.cchDisplayName = (uint64_t)cchDisplayName;
    call.lpLanguageId = (uint64_t)lpLanguageId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupPrivilegeDisplayNameA(struct qemu_syscall *call)
{
    struct qemu_LookupPrivilegeDisplayNameA *c = (struct qemu_LookupPrivilegeDisplayNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupPrivilegeDisplayNameA(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpName), QEMU_G2H(c->lpDisplayName), QEMU_G2H(c->cchDisplayName), QEMU_G2H(c->lpLanguageId));
}

#endif

struct qemu_LookupPrivilegeDisplayNameW
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpName;
    uint64_t lpDisplayName;
    uint64_t cchDisplayName;
    uint64_t lpLanguageId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupPrivilegeDisplayNameW(LPCWSTR lpSystemName, LPCWSTR lpName, LPWSTR lpDisplayName, LPDWORD cchDisplayName, LPDWORD lpLanguageId)
{
    struct qemu_LookupPrivilegeDisplayNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPPRIVILEGEDISPLAYNAMEW);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpName = (uint64_t)lpName;
    call.lpDisplayName = (uint64_t)lpDisplayName;
    call.cchDisplayName = (uint64_t)cchDisplayName;
    call.lpLanguageId = (uint64_t)lpLanguageId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupPrivilegeDisplayNameW(struct qemu_syscall *call)
{
    struct qemu_LookupPrivilegeDisplayNameW *c = (struct qemu_LookupPrivilegeDisplayNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupPrivilegeDisplayNameW(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpName), QEMU_G2H(c->lpDisplayName), QEMU_G2H(c->cchDisplayName), QEMU_G2H(c->lpLanguageId));
}

#endif

struct qemu_LookupPrivilegeNameA
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpLuid;
    uint64_t lpName;
    uint64_t cchName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupPrivilegeNameA(LPCSTR lpSystemName, PLUID lpLuid, LPSTR lpName, LPDWORD cchName)
{
    struct qemu_LookupPrivilegeNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPPRIVILEGENAMEA);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpLuid = (uint64_t)lpLuid;
    call.lpName = (uint64_t)lpName;
    call.cchName = (uint64_t)cchName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupPrivilegeNameA(struct qemu_syscall *call)
{
    struct qemu_LookupPrivilegeNameA *c = (struct qemu_LookupPrivilegeNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupPrivilegeNameA(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpLuid), QEMU_G2H(c->lpName), QEMU_G2H(c->cchName));
}

#endif

struct qemu_LookupPrivilegeNameW
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpLuid;
    uint64_t lpName;
    uint64_t cchName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupPrivilegeNameW(LPCWSTR lpSystemName, PLUID lpLuid, LPWSTR lpName, LPDWORD cchName)
{
    struct qemu_LookupPrivilegeNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPPRIVILEGENAMEW);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpLuid = (uint64_t)lpLuid;
    call.lpName = (uint64_t)lpName;
    call.cchName = (uint64_t)cchName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupPrivilegeNameW(struct qemu_syscall *call)
{
    struct qemu_LookupPrivilegeNameW *c = (struct qemu_LookupPrivilegeNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupPrivilegeNameW(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpLuid), QEMU_G2H(c->lpName), QEMU_G2H(c->cchName));
}

#endif

struct qemu_GetFileSecurityA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t RequestedInformation;
    uint64_t pSecurityDescriptor;
    uint64_t nLength;
    uint64_t lpnLengthNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileSecurityA(LPCSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded)
{
    struct qemu_GetFileSecurityA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILESECURITYA);
    call.lpFileName = (uint64_t)lpFileName;
    call.RequestedInformation = (uint64_t)RequestedInformation;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.nLength = (uint64_t)nLength;
    call.lpnLengthNeeded = (uint64_t)lpnLengthNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileSecurityA(struct qemu_syscall *call)
{
    struct qemu_GetFileSecurityA *c = (struct qemu_GetFileSecurityA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileSecurityA(QEMU_G2H(c->lpFileName), c->RequestedInformation, QEMU_G2H(c->pSecurityDescriptor), c->nLength, QEMU_G2H(c->lpnLengthNeeded));
}

#endif

struct qemu_GetFileSecurityW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t RequestedInformation;
    uint64_t pSecurityDescriptor;
    uint64_t nLength;
    uint64_t lpnLengthNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileSecurityW(LPCWSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD nLength, LPDWORD lpnLengthNeeded)
{
    struct qemu_GetFileSecurityW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILESECURITYW);
    call.lpFileName = (uint64_t)lpFileName;
    call.RequestedInformation = (uint64_t)RequestedInformation;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.nLength = (uint64_t)nLength;
    call.lpnLengthNeeded = (uint64_t)lpnLengthNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileSecurityW(struct qemu_syscall *call)
{
    struct qemu_GetFileSecurityW *c = (struct qemu_GetFileSecurityW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileSecurityW(QEMU_G2H(c->lpFileName), c->RequestedInformation, QEMU_G2H(c->pSecurityDescriptor), c->nLength, QEMU_G2H(c->lpnLengthNeeded));
}

#endif

struct qemu_LookupAccountSidA
{
    struct qemu_syscall super;
    uint64_t system;
    uint64_t sid;
    uint64_t account;
    uint64_t accountSize;
    uint64_t domain;
    uint64_t domainSize;
    uint64_t name_use;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupAccountSidA(IN LPCSTR system, IN PSID sid, OUT LPSTR account, IN OUT LPDWORD accountSize, OUT LPSTR domain, IN OUT LPDWORD domainSize, OUT PSID_NAME_USE name_use)
{
    struct qemu_LookupAccountSidA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPACCOUNTSIDA);
    call.system = (uint64_t)system;
    call.sid = (uint64_t)sid;
    call.account = (uint64_t)account;
    call.accountSize = (uint64_t)accountSize;
    call.domain = (uint64_t)domain;
    call.domainSize = (uint64_t)domainSize;
    call.name_use = (uint64_t)name_use;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupAccountSidA(struct qemu_syscall *call)
{
    struct qemu_LookupAccountSidA *c = (struct qemu_LookupAccountSidA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupAccountSidA(QEMU_G2H(c->system), QEMU_G2H(c->sid), QEMU_G2H(c->account), QEMU_G2H(c->accountSize), QEMU_G2H(c->domain), QEMU_G2H(c->domainSize), QEMU_G2H(c->name_use));
}

#endif

struct qemu_LookupAccountSidW
{
    struct qemu_syscall super;
    uint64_t system;
    uint64_t sid;
    uint64_t account;
    uint64_t accountSize;
    uint64_t domain;
    uint64_t domainSize;
    uint64_t name_use;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupAccountSidW(IN LPCWSTR system, IN PSID sid, OUT LPWSTR account, IN OUT LPDWORD accountSize, OUT LPWSTR domain, IN OUT LPDWORD domainSize, OUT PSID_NAME_USE name_use)
{
    struct qemu_LookupAccountSidW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPACCOUNTSIDW);
    call.system = (uint64_t)system;
    call.sid = (uint64_t)sid;
    call.account = (uint64_t)account;
    call.accountSize = (uint64_t)accountSize;
    call.domain = (uint64_t)domain;
    call.domainSize = (uint64_t)domainSize;
    call.name_use = (uint64_t)name_use;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupAccountSidW(struct qemu_syscall *call)
{
    struct qemu_LookupAccountSidW *c = (struct qemu_LookupAccountSidW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupAccountSidW(QEMU_G2H(c->system), QEMU_G2H(c->sid), QEMU_G2H(c->account), QEMU_G2H(c->accountSize), QEMU_G2H(c->domain), QEMU_G2H(c->domainSize), QEMU_G2H(c->name_use));
}

#endif

struct qemu_SetFileSecurityA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t RequestedInformation;
    uint64_t pSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileSecurityA(LPCSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor)
{
    struct qemu_SetFileSecurityA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILESECURITYA);
    call.lpFileName = (uint64_t)lpFileName;
    call.RequestedInformation = (uint64_t)RequestedInformation;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileSecurityA(struct qemu_syscall *call)
{
    struct qemu_SetFileSecurityA *c = (struct qemu_SetFileSecurityA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetFileSecurityA(QEMU_G2H(c->lpFileName), c->RequestedInformation, QEMU_G2H(c->pSecurityDescriptor));
}

#endif

struct qemu_SetFileSecurityW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t RequestedInformation;
    uint64_t pSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFileSecurityW(LPCWSTR lpFileName, SECURITY_INFORMATION RequestedInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor)
{
    struct qemu_SetFileSecurityW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFILESECURITYW);
    call.lpFileName = (uint64_t)lpFileName;
    call.RequestedInformation = (uint64_t)RequestedInformation;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFileSecurityW(struct qemu_syscall *call)
{
    struct qemu_SetFileSecurityW *c = (struct qemu_SetFileSecurityW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetFileSecurityW(QEMU_G2H(c->lpFileName), c->RequestedInformation, QEMU_G2H(c->pSecurityDescriptor));
}

#endif

struct qemu_QueryWindows31FilesMigration
{
    struct qemu_syscall super;
    uint64_t x1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryWindows31FilesMigration(DWORD x1)
{
    struct qemu_QueryWindows31FilesMigration call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYWINDOWS31FILESMIGRATION);
    call.x1 = (uint64_t)x1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add QueryWindows31FilesMigration to Wine headers? */
extern BOOL WINAPI QueryWindows31FilesMigration(DWORD x1);
void qemu_QueryWindows31FilesMigration(struct qemu_syscall *call)
{
    struct qemu_QueryWindows31FilesMigration *c = (struct qemu_QueryWindows31FilesMigration *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryWindows31FilesMigration(c->x1);
}

#endif

struct qemu_SynchronizeWindows31FilesAndWindowsNTRegistry
{
    struct qemu_syscall super;
    uint64_t x1;
    uint64_t x2;
    uint64_t x3;
    uint64_t x4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SynchronizeWindows31FilesAndWindowsNTRegistry(DWORD x1, DWORD x2, DWORD x3, DWORD x4)
{
    struct qemu_SynchronizeWindows31FilesAndWindowsNTRegistry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYNCHRONIZEWINDOWS31FILESANDWINDOWSNTREGISTRY);
    call.x1 = (uint64_t)x1;
    call.x2 = (uint64_t)x2;
    call.x3 = (uint64_t)x3;
    call.x4 = (uint64_t)x4;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SynchronizeWindows31FilesAndWindowsNTRegistry to Wine headers? */
extern BOOL WINAPI SynchronizeWindows31FilesAndWindowsNTRegistry(DWORD x1, DWORD x2, DWORD x3, DWORD x4);
void qemu_SynchronizeWindows31FilesAndWindowsNTRegistry(struct qemu_syscall *call)
{
    struct qemu_SynchronizeWindows31FilesAndWindowsNTRegistry *c = (struct qemu_SynchronizeWindows31FilesAndWindowsNTRegistry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SynchronizeWindows31FilesAndWindowsNTRegistry(c->x1, c->x2, c->x3, c->x4);
}

#endif

struct qemu_NotifyBootConfigStatus
{
    struct qemu_syscall super;
    uint64_t x1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI NotifyBootConfigStatus(BOOL x1)
{
    struct qemu_NotifyBootConfigStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYBOOTCONFIGSTATUS);
    call.x1 = (uint64_t)x1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NotifyBootConfigStatus(struct qemu_syscall *call)
{
    struct qemu_NotifyBootConfigStatus *c = (struct qemu_NotifyBootConfigStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyBootConfigStatus(c->x1);
}

#endif

struct qemu_RevertToSelf
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RevertToSelf(void)
{
    struct qemu_RevertToSelf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REVERTTOSELF);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RevertToSelf(struct qemu_syscall *call)
{
    struct qemu_RevertToSelf *c = (struct qemu_RevertToSelf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RevertToSelf();
}

#endif

struct qemu_ImpersonateSelf
{
    struct qemu_syscall super;
    uint64_t ImpersonationLevel;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImpersonateSelf(SECURITY_IMPERSONATION_LEVEL ImpersonationLevel)
{
    struct qemu_ImpersonateSelf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPERSONATESELF);
    call.ImpersonationLevel = (uint64_t)ImpersonationLevel;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImpersonateSelf(struct qemu_syscall *call)
{
    struct qemu_ImpersonateSelf *c = (struct qemu_ImpersonateSelf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImpersonateSelf(c->ImpersonationLevel);
}

#endif

struct qemu_ImpersonateLoggedOnUser
{
    struct qemu_syscall super;
    uint64_t hToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImpersonateLoggedOnUser(HANDLE hToken)
{
    struct qemu_ImpersonateLoggedOnUser call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPERSONATELOGGEDONUSER);
    call.hToken = (uint64_t)hToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImpersonateLoggedOnUser(struct qemu_syscall *call)
{
    struct qemu_ImpersonateLoggedOnUser *c = (struct qemu_ImpersonateLoggedOnUser *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImpersonateLoggedOnUser(QEMU_G2H(c->hToken));
}

#endif

struct qemu_ImpersonateAnonymousToken
{
    struct qemu_syscall super;
    uint64_t thread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImpersonateAnonymousToken(HANDLE thread)
{
    struct qemu_ImpersonateAnonymousToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMPERSONATEANONYMOUSTOKEN);
    call.thread = (uint64_t)thread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ImpersonateAnonymousToken to Wine headers? */
extern BOOL WINAPI ImpersonateAnonymousToken(HANDLE thread);
void qemu_ImpersonateAnonymousToken(struct qemu_syscall *call)
{
    struct qemu_ImpersonateAnonymousToken *c = (struct qemu_ImpersonateAnonymousToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImpersonateAnonymousToken(QEMU_G2H(c->thread));
}

#endif

struct qemu_AccessCheck
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t GenericMapping;
    uint64_t PrivilegeSet;
    uint64_t PrivilegeSetLength;
    uint64_t GrantedAccess;
    uint64_t AccessStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AccessCheck(PSECURITY_DESCRIPTOR SecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, LPDWORD PrivilegeSetLength, LPDWORD GrantedAccess, LPBOOL AccessStatus)
{
    struct qemu_AccessCheck call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACCESSCHECK);
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.ClientToken = (uint64_t)ClientToken;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.GenericMapping = (uint64_t)GenericMapping;
    call.PrivilegeSet = (uint64_t)PrivilegeSet;
    call.PrivilegeSetLength = (uint64_t)PrivilegeSetLength;
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.AccessStatus = (uint64_t)AccessStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AccessCheck(struct qemu_syscall *call)
{
    struct qemu_AccessCheck *c = (struct qemu_AccessCheck *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AccessCheck(QEMU_G2H(c->SecurityDescriptor), QEMU_G2H(c->ClientToken), c->DesiredAccess, QEMU_G2H(c->GenericMapping), QEMU_G2H(c->PrivilegeSet), QEMU_G2H(c->PrivilegeSetLength), QEMU_G2H(c->GrantedAccess), QEMU_G2H(c->AccessStatus));
}

#endif

struct qemu_AccessCheckByType
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t PrincipalSelfSid;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t ObjectTypeList;
    uint64_t ObjectTypeListLength;
    uint64_t GenericMapping;
    uint64_t PrivilegeSet;
    uint64_t PrivilegeSetLength;
    uint64_t GrantedAccess;
    uint64_t AccessStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AccessCheckByType(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID PrincipalSelfSid, HANDLE ClientToken, DWORD DesiredAccess, POBJECT_TYPE_LIST ObjectTypeList, DWORD ObjectTypeListLength, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, LPDWORD PrivilegeSetLength, LPDWORD GrantedAccess, LPBOOL AccessStatus)
{
    struct qemu_AccessCheckByType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACCESSCHECKBYTYPE);
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.PrincipalSelfSid = (uint64_t)PrincipalSelfSid;
    call.ClientToken = (uint64_t)ClientToken;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.ObjectTypeList = (uint64_t)ObjectTypeList;
    call.ObjectTypeListLength = (uint64_t)ObjectTypeListLength;
    call.GenericMapping = (uint64_t)GenericMapping;
    call.PrivilegeSet = (uint64_t)PrivilegeSet;
    call.PrivilegeSetLength = (uint64_t)PrivilegeSetLength;
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.AccessStatus = (uint64_t)AccessStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AccessCheckByType(struct qemu_syscall *call)
{
    struct qemu_AccessCheckByType *c = (struct qemu_AccessCheckByType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AccessCheckByType(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->PrincipalSelfSid), QEMU_G2H(c->ClientToken), c->DesiredAccess, QEMU_G2H(c->ObjectTypeList), c->ObjectTypeListLength, QEMU_G2H(c->GenericMapping), QEMU_G2H(c->PrivilegeSet), QEMU_G2H(c->PrivilegeSetLength), QEMU_G2H(c->GrantedAccess), QEMU_G2H(c->AccessStatus));
}

#endif

struct qemu_MapGenericMask
{
    struct qemu_syscall super;
    uint64_t AccessMask;
    uint64_t GenericMapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MapGenericMask(PDWORD AccessMask, PGENERIC_MAPPING GenericMapping)
{
    struct qemu_MapGenericMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPGENERICMASK);
    call.AccessMask = (uint64_t)AccessMask;
    call.GenericMapping = (uint64_t)GenericMapping;

    qemu_syscall(&call.super);
}

#else

void qemu_MapGenericMask(struct qemu_syscall *call)
{
    struct qemu_MapGenericMask *c = (struct qemu_MapGenericMask *)call;
    WINE_FIXME("Unverified!\n");
    MapGenericMask(QEMU_G2H(c->AccessMask), QEMU_G2H(c->GenericMapping));
}

#endif

struct qemu_SetKernelObjectSecurity
{
    struct qemu_syscall super;
    uint64_t Handle;
    uint64_t SecurityInformation;
    uint64_t SecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetKernelObjectSecurity (IN HANDLE Handle, IN SECURITY_INFORMATION SecurityInformation, IN PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    struct qemu_SetKernelObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETKERNELOBJECTSECURITY);
    call.Handle = (uint64_t)Handle;
    call.SecurityInformation = (uint64_t)SecurityInformation;
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetKernelObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_SetKernelObjectSecurity *c = (struct qemu_SetKernelObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetKernelObjectSecurity((HANDLE)c->Handle, c->SecurityInformation, QEMU_G2H(c->SecurityDescriptor));
}

#endif

struct qemu_AddAuditAccessAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwAccessMask;
    uint64_t pSid;
    uint64_t bAuditSuccess;
    uint64_t bAuditFailure;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAuditAccessAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAccessMask, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure)
{
    struct qemu_AddAuditAccessAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDAUDITACCESSACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.dwAccessMask = (uint64_t)dwAccessMask;
    call.pSid = (uint64_t)pSid;
    call.bAuditSuccess = (uint64_t)bAuditSuccess;
    call.bAuditFailure = (uint64_t)bAuditFailure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAuditAccessAce(struct qemu_syscall *call)
{
    struct qemu_AddAuditAccessAce *c = (struct qemu_AddAuditAccessAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAuditAccessAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAccessMask, QEMU_G2H(c->pSid), c->bAuditSuccess, c->bAuditFailure);
}

#endif

struct qemu_AddAuditAccessAceEx
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwAceFlags;
    uint64_t dwAccessMask;
    uint64_t pSid;
    uint64_t bAuditSuccess;
    uint64_t bAuditFailure;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAuditAccessAceEx(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure)
{
    struct qemu_AddAuditAccessAceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDAUDITACCESSACEEX);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.dwAceFlags = (uint64_t)dwAceFlags;
    call.dwAccessMask = (uint64_t)dwAccessMask;
    call.pSid = (uint64_t)pSid;
    call.bAuditSuccess = (uint64_t)bAuditSuccess;
    call.bAuditFailure = (uint64_t)bAuditFailure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAuditAccessAceEx(struct qemu_syscall *call)
{
    struct qemu_AddAuditAccessAceEx *c = (struct qemu_AddAuditAccessAceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAuditAccessAceEx(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pSid), c->bAuditSuccess, c->bAuditFailure);
}

#endif

struct qemu_AddAuditAccessObjectAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwAceFlags;
    uint64_t dwAccessMask;
    uint64_t pObjectTypeGuid;
    uint64_t pInheritedObjectTypeGuid;
    uint64_t pSid;
    uint64_t bAuditSuccess;
    uint64_t bAuditFailure;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddAuditAccessObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure)
{
    struct qemu_AddAuditAccessObjectAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDAUDITACCESSOBJECTACE);
    call.pAcl = (uint64_t)pAcl;
    call.dwAceRevision = (uint64_t)dwAceRevision;
    call.dwAceFlags = (uint64_t)dwAceFlags;
    call.dwAccessMask = (uint64_t)dwAccessMask;
    call.pObjectTypeGuid = (uint64_t)pObjectTypeGuid;
    call.pInheritedObjectTypeGuid = (uint64_t)pInheritedObjectTypeGuid;
    call.pSid = (uint64_t)pSid;
    call.bAuditSuccess = (uint64_t)bAuditSuccess;
    call.bAuditFailure = (uint64_t)bAuditFailure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AddAuditAccessObjectAce to Wine headers? */
extern BOOL WINAPI AddAuditAccessObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure);
void qemu_AddAuditAccessObjectAce(struct qemu_syscall *call)
{
    struct qemu_AddAuditAccessObjectAce *c = (struct qemu_AddAuditAccessObjectAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddAuditAccessObjectAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pObjectTypeGuid), QEMU_G2H(c->pInheritedObjectTypeGuid), QEMU_G2H(c->pSid), c->bAuditSuccess, c->bAuditFailure);
}

#endif

struct qemu_LookupAccountNameA
{
    struct qemu_syscall super;
    uint64_t system;
    uint64_t account;
    uint64_t sid;
    uint64_t cbSid;
    uint64_t ReferencedDomainName;
    uint64_t cbReferencedDomainName;
    uint64_t name_use;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupAccountNameA(IN LPCSTR system, IN LPCSTR account, OUT PSID sid, OUT LPDWORD cbSid, LPSTR ReferencedDomainName, IN OUT LPDWORD cbReferencedDomainName, OUT PSID_NAME_USE name_use)
{
    struct qemu_LookupAccountNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPACCOUNTNAMEA);
    call.system = (uint64_t)system;
    call.account = (uint64_t)account;
    call.sid = (uint64_t)sid;
    call.cbSid = (uint64_t)cbSid;
    call.ReferencedDomainName = (uint64_t)ReferencedDomainName;
    call.cbReferencedDomainName = (uint64_t)cbReferencedDomainName;
    call.name_use = (uint64_t)name_use;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupAccountNameA(struct qemu_syscall *call)
{
    struct qemu_LookupAccountNameA *c = (struct qemu_LookupAccountNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupAccountNameA(QEMU_G2H(c->system), QEMU_G2H(c->account), QEMU_G2H(c->sid), QEMU_G2H(c->cbSid), QEMU_G2H(c->ReferencedDomainName), QEMU_G2H(c->cbReferencedDomainName), QEMU_G2H(c->name_use));
}

#endif

struct qemu_LookupAccountNameW
{
    struct qemu_syscall super;
    uint64_t lpSystemName;
    uint64_t lpAccountName;
    uint64_t Sid;
    uint64_t cbSid;
    uint64_t ReferencedDomainName;
    uint64_t cchReferencedDomainName;
    uint64_t peUse;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LookupAccountNameW(LPCWSTR lpSystemName, LPCWSTR lpAccountName, PSID Sid, LPDWORD cbSid, LPWSTR ReferencedDomainName, LPDWORD cchReferencedDomainName, PSID_NAME_USE peUse)
{
    struct qemu_LookupAccountNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPACCOUNTNAMEW);
    call.lpSystemName = (uint64_t)lpSystemName;
    call.lpAccountName = (uint64_t)lpAccountName;
    call.Sid = (uint64_t)Sid;
    call.cbSid = (uint64_t)cbSid;
    call.ReferencedDomainName = (uint64_t)ReferencedDomainName;
    call.cchReferencedDomainName = (uint64_t)cchReferencedDomainName;
    call.peUse = (uint64_t)peUse;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LookupAccountNameW(struct qemu_syscall *call)
{
    struct qemu_LookupAccountNameW *c = (struct qemu_LookupAccountNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupAccountNameW(QEMU_G2H(c->lpSystemName), QEMU_G2H(c->lpAccountName), QEMU_G2H(c->Sid), QEMU_G2H(c->cbSid), QEMU_G2H(c->ReferencedDomainName), QEMU_G2H(c->cchReferencedDomainName), QEMU_G2H(c->peUse));
}

#endif

struct qemu_PrivilegeCheck
{
    struct qemu_syscall super;
    uint64_t ClientToken;
    uint64_t RequiredPrivileges;
    uint64_t pfResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrivilegeCheck(HANDLE ClientToken, PPRIVILEGE_SET RequiredPrivileges, LPBOOL pfResult)
{
    struct qemu_PrivilegeCheck call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVILEGECHECK);
    call.ClientToken = (uint64_t)ClientToken;
    call.RequiredPrivileges = (uint64_t)RequiredPrivileges;
    call.pfResult = (uint64_t)pfResult;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivilegeCheck(struct qemu_syscall *call)
{
    struct qemu_PrivilegeCheck *c = (struct qemu_PrivilegeCheck *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivilegeCheck(QEMU_G2H(c->ClientToken), QEMU_G2H(c->RequiredPrivileges), QEMU_G2H(c->pfResult));
}

#endif

struct qemu_AccessCheckAndAuditAlarmA
{
    struct qemu_syscall super;
    uint64_t Subsystem;
    uint64_t HandleId;
    uint64_t ObjectTypeName;
    uint64_t ObjectName;
    uint64_t SecurityDescriptor;
    uint64_t DesiredAccess;
    uint64_t GenericMapping;
    uint64_t ObjectCreation;
    uint64_t GrantedAccess;
    uint64_t AccessStatus;
    uint64_t pfGenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AccessCheckAndAuditAlarmA(LPCSTR Subsystem, LPVOID HandleId, LPSTR ObjectTypeName, LPSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess, LPBOOL AccessStatus, LPBOOL pfGenerateOnClose)
{
    struct qemu_AccessCheckAndAuditAlarmA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACCESSCHECKANDAUDITALARMA);
    call.Subsystem = (uint64_t)Subsystem;
    call.HandleId = (uint64_t)HandleId;
    call.ObjectTypeName = (uint64_t)ObjectTypeName;
    call.ObjectName = (uint64_t)ObjectName;
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.GenericMapping = (uint64_t)GenericMapping;
    call.ObjectCreation = (uint64_t)ObjectCreation;
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.AccessStatus = (uint64_t)AccessStatus;
    call.pfGenerateOnClose = (uint64_t)pfGenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AccessCheckAndAuditAlarmA(struct qemu_syscall *call)
{
    struct qemu_AccessCheckAndAuditAlarmA *c = (struct qemu_AccessCheckAndAuditAlarmA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AccessCheckAndAuditAlarmA(QEMU_G2H(c->Subsystem), QEMU_G2H(c->HandleId), QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->ObjectName), QEMU_G2H(c->SecurityDescriptor), c->DesiredAccess, QEMU_G2H(c->GenericMapping), c->ObjectCreation, QEMU_G2H(c->GrantedAccess), QEMU_G2H(c->AccessStatus), QEMU_G2H(c->pfGenerateOnClose));
}

#endif

struct qemu_AccessCheckAndAuditAlarmW
{
    struct qemu_syscall super;
    uint64_t Subsystem;
    uint64_t HandleId;
    uint64_t ObjectTypeName;
    uint64_t ObjectName;
    uint64_t SecurityDescriptor;
    uint64_t DesiredAccess;
    uint64_t GenericMapping;
    uint64_t ObjectCreation;
    uint64_t GrantedAccess;
    uint64_t AccessStatus;
    uint64_t pfGenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AccessCheckAndAuditAlarmW(LPCWSTR Subsystem, LPVOID HandleId, LPWSTR ObjectTypeName, LPWSTR ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD DesiredAccess, PGENERIC_MAPPING GenericMapping, BOOL ObjectCreation, LPDWORD GrantedAccess, LPBOOL AccessStatus, LPBOOL pfGenerateOnClose)
{
    struct qemu_AccessCheckAndAuditAlarmW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACCESSCHECKANDAUDITALARMW);
    call.Subsystem = (uint64_t)Subsystem;
    call.HandleId = (uint64_t)HandleId;
    call.ObjectTypeName = (uint64_t)ObjectTypeName;
    call.ObjectName = (uint64_t)ObjectName;
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.GenericMapping = (uint64_t)GenericMapping;
    call.ObjectCreation = (uint64_t)ObjectCreation;
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.AccessStatus = (uint64_t)AccessStatus;
    call.pfGenerateOnClose = (uint64_t)pfGenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AccessCheckAndAuditAlarmW(struct qemu_syscall *call)
{
    struct qemu_AccessCheckAndAuditAlarmW *c = (struct qemu_AccessCheckAndAuditAlarmW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AccessCheckAndAuditAlarmW(QEMU_G2H(c->Subsystem), QEMU_G2H(c->HandleId), QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->ObjectName), QEMU_G2H(c->SecurityDescriptor), c->DesiredAccess, QEMU_G2H(c->GenericMapping), c->ObjectCreation, QEMU_G2H(c->GrantedAccess), QEMU_G2H(c->AccessStatus), QEMU_G2H(c->pfGenerateOnClose));
}

#endif

struct qemu_ObjectCloseAuditAlarmA
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t GenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectCloseAuditAlarmA(LPCSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
{
    struct qemu_ObjectCloseAuditAlarmA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTCLOSEAUDITALARMA);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.GenerateOnClose = (uint64_t)GenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectCloseAuditAlarmA(struct qemu_syscall *call)
{
    struct qemu_ObjectCloseAuditAlarmA *c = (struct qemu_ObjectCloseAuditAlarmA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectCloseAuditAlarmA(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), c->GenerateOnClose);
}

#endif

struct qemu_ObjectCloseAuditAlarmW
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t GenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectCloseAuditAlarmW(LPCWSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
{
    struct qemu_ObjectCloseAuditAlarmW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTCLOSEAUDITALARMW);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.GenerateOnClose = (uint64_t)GenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectCloseAuditAlarmW(struct qemu_syscall *call)
{
    struct qemu_ObjectCloseAuditAlarmW *c = (struct qemu_ObjectCloseAuditAlarmW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectCloseAuditAlarmW(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), c->GenerateOnClose);
}

#endif

struct qemu_ObjectDeleteAuditAlarmW
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t GenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectDeleteAuditAlarmW(LPCWSTR SubsystemName, LPVOID HandleId, BOOL GenerateOnClose)
{
    struct qemu_ObjectDeleteAuditAlarmW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTDELETEAUDITALARMW);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.GenerateOnClose = (uint64_t)GenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectDeleteAuditAlarmW(struct qemu_syscall *call)
{
    struct qemu_ObjectDeleteAuditAlarmW *c = (struct qemu_ObjectDeleteAuditAlarmW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectDeleteAuditAlarmW(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), c->GenerateOnClose);
}

#endif

struct qemu_ObjectOpenAuditAlarmA
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t ObjectTypeName;
    uint64_t ObjectName;
    uint64_t pSecurityDescriptor;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t GrantedAccess;
    uint64_t Privileges;
    uint64_t ObjectCreation;
    uint64_t AccessGranted;
    uint64_t GenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectOpenAuditAlarmA(LPCSTR SubsystemName, LPVOID HandleId, LPSTR ObjectTypeName, LPSTR ObjectName, PSECURITY_DESCRIPTOR pSecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess, DWORD GrantedAccess, PPRIVILEGE_SET Privileges, BOOL ObjectCreation, BOOL AccessGranted, LPBOOL GenerateOnClose)
{
    struct qemu_ObjectOpenAuditAlarmA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTOPENAUDITALARMA);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.ObjectTypeName = (uint64_t)ObjectTypeName;
    call.ObjectName = (uint64_t)ObjectName;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.ClientToken = (uint64_t)ClientToken;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.Privileges = (uint64_t)Privileges;
    call.ObjectCreation = (uint64_t)ObjectCreation;
    call.AccessGranted = (uint64_t)AccessGranted;
    call.GenerateOnClose = (uint64_t)GenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectOpenAuditAlarmA(struct qemu_syscall *call)
{
    struct qemu_ObjectOpenAuditAlarmA *c = (struct qemu_ObjectOpenAuditAlarmA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectOpenAuditAlarmA(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->ObjectName), QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->ClientToken), c->DesiredAccess, c->GrantedAccess, QEMU_G2H(c->Privileges), c->ObjectCreation, c->AccessGranted, QEMU_G2H(c->GenerateOnClose));
}

#endif

struct qemu_ObjectOpenAuditAlarmW
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t ObjectTypeName;
    uint64_t ObjectName;
    uint64_t pSecurityDescriptor;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t GrantedAccess;
    uint64_t Privileges;
    uint64_t ObjectCreation;
    uint64_t AccessGranted;
    uint64_t GenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectOpenAuditAlarmW(LPCWSTR SubsystemName, LPVOID HandleId, LPWSTR ObjectTypeName, LPWSTR ObjectName, PSECURITY_DESCRIPTOR pSecurityDescriptor, HANDLE ClientToken, DWORD DesiredAccess, DWORD GrantedAccess, PPRIVILEGE_SET Privileges, BOOL ObjectCreation, BOOL AccessGranted, LPBOOL GenerateOnClose)
{
    struct qemu_ObjectOpenAuditAlarmW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTOPENAUDITALARMW);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.ObjectTypeName = (uint64_t)ObjectTypeName;
    call.ObjectName = (uint64_t)ObjectName;
    call.pSecurityDescriptor = (uint64_t)pSecurityDescriptor;
    call.ClientToken = (uint64_t)ClientToken;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.Privileges = (uint64_t)Privileges;
    call.ObjectCreation = (uint64_t)ObjectCreation;
    call.AccessGranted = (uint64_t)AccessGranted;
    call.GenerateOnClose = (uint64_t)GenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectOpenAuditAlarmW(struct qemu_syscall *call)
{
    struct qemu_ObjectOpenAuditAlarmW *c = (struct qemu_ObjectOpenAuditAlarmW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectOpenAuditAlarmW(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->ObjectName), QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->ClientToken), c->DesiredAccess, c->GrantedAccess, QEMU_G2H(c->Privileges), c->ObjectCreation, c->AccessGranted, QEMU_G2H(c->GenerateOnClose));
}

#endif

struct qemu_ObjectPrivilegeAuditAlarmA
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t Privileges;
    uint64_t AccessGranted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectPrivilegeAuditAlarmA(LPCSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken, DWORD DesiredAccess, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
{
    struct qemu_ObjectPrivilegeAuditAlarmA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTPRIVILEGEAUDITALARMA);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.ClientToken = (uint64_t)ClientToken;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.Privileges = (uint64_t)Privileges;
    call.AccessGranted = (uint64_t)AccessGranted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectPrivilegeAuditAlarmA(struct qemu_syscall *call)
{
    struct qemu_ObjectPrivilegeAuditAlarmA *c = (struct qemu_ObjectPrivilegeAuditAlarmA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectPrivilegeAuditAlarmA(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), QEMU_G2H(c->ClientToken), c->DesiredAccess, QEMU_G2H(c->Privileges), c->AccessGranted);
}

#endif

struct qemu_ObjectPrivilegeAuditAlarmW
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t Privileges;
    uint64_t AccessGranted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ObjectPrivilegeAuditAlarmW(LPCWSTR SubsystemName, LPVOID HandleId, HANDLE ClientToken, DWORD DesiredAccess, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
{
    struct qemu_ObjectPrivilegeAuditAlarmW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OBJECTPRIVILEGEAUDITALARMW);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.HandleId = (uint64_t)HandleId;
    call.ClientToken = (uint64_t)ClientToken;
    call.DesiredAccess = (uint64_t)DesiredAccess;
    call.Privileges = (uint64_t)Privileges;
    call.AccessGranted = (uint64_t)AccessGranted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ObjectPrivilegeAuditAlarmW(struct qemu_syscall *call)
{
    struct qemu_ObjectPrivilegeAuditAlarmW *c = (struct qemu_ObjectPrivilegeAuditAlarmW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ObjectPrivilegeAuditAlarmW(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), QEMU_G2H(c->ClientToken), c->DesiredAccess, QEMU_G2H(c->Privileges), c->AccessGranted);
}

#endif

struct qemu_PrivilegedServiceAuditAlarmA
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t ServiceName;
    uint64_t ClientToken;
    uint64_t Privileges;
    uint64_t AccessGranted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrivilegedServiceAuditAlarmA(LPCSTR SubsystemName, LPCSTR ServiceName, HANDLE ClientToken, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
{
    struct qemu_PrivilegedServiceAuditAlarmA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVILEGEDSERVICEAUDITALARMA);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.ServiceName = (uint64_t)ServiceName;
    call.ClientToken = (uint64_t)ClientToken;
    call.Privileges = (uint64_t)Privileges;
    call.AccessGranted = (uint64_t)AccessGranted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivilegedServiceAuditAlarmA(struct qemu_syscall *call)
{
    struct qemu_PrivilegedServiceAuditAlarmA *c = (struct qemu_PrivilegedServiceAuditAlarmA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivilegedServiceAuditAlarmA(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->ServiceName), QEMU_G2H(c->ClientToken), QEMU_G2H(c->Privileges), c->AccessGranted);
}

#endif

struct qemu_PrivilegedServiceAuditAlarmW
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t ServiceName;
    uint64_t ClientToken;
    uint64_t Privileges;
    uint64_t AccessGranted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrivilegedServiceAuditAlarmW(LPCWSTR SubsystemName, LPCWSTR ServiceName, HANDLE ClientToken, PPRIVILEGE_SET Privileges, BOOL AccessGranted)
{
    struct qemu_PrivilegedServiceAuditAlarmW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVILEGEDSERVICEAUDITALARMW);
    call.SubsystemName = (uint64_t)SubsystemName;
    call.ServiceName = (uint64_t)ServiceName;
    call.ClientToken = (uint64_t)ClientToken;
    call.Privileges = (uint64_t)Privileges;
    call.AccessGranted = (uint64_t)AccessGranted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivilegedServiceAuditAlarmW(struct qemu_syscall *call)
{
    struct qemu_PrivilegedServiceAuditAlarmW *c = (struct qemu_PrivilegedServiceAuditAlarmW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivilegedServiceAuditAlarmW(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->ServiceName), QEMU_G2H(c->ClientToken), QEMU_G2H(c->Privileges), c->AccessGranted);
}

#endif

struct qemu_GetSecurityInfo
{
    struct qemu_syscall super;
    uint64_t hObject;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t ppsidOwner;
    uint64_t ppsidGroup;
    uint64_t ppDacl;
    uint64_t ppSacl;
    uint64_t ppSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetSecurityInfo(HANDLE hObject, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID *ppsidOwner, PSID *ppsidGroup, PACL *ppDacl, PACL *ppSacl, PSECURITY_DESCRIPTOR *ppSecurityDescriptor)
{
    struct qemu_GetSecurityInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYINFO);
    call.hObject = (uint64_t)hObject;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.ppsidOwner = (uint64_t)ppsidOwner;
    call.ppsidGroup = (uint64_t)ppsidGroup;
    call.ppDacl = (uint64_t)ppDacl;
    call.ppSacl = (uint64_t)ppSacl;
    call.ppSecurityDescriptor = (uint64_t)ppSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityInfo(struct qemu_syscall *call)
{
    struct qemu_GetSecurityInfo *c = (struct qemu_GetSecurityInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityInfo(QEMU_G2H(c->hObject), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->ppsidOwner), QEMU_G2H(c->ppsidGroup), QEMU_G2H(c->ppDacl), QEMU_G2H(c->ppSacl), QEMU_G2H(c->ppSecurityDescriptor));
}

#endif

struct qemu_GetSecurityInfoExA
{
    struct qemu_syscall super;
    uint64_t hObject;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t lpProvider;
    uint64_t lpProperty;
    uint64_t ppAccessList;
    uint64_t ppAuditList;
    uint64_t lppOwner;
    uint64_t lppGroup;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetSecurityInfoExA(HANDLE hObject, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, LPCSTR lpProvider, LPCSTR lpProperty, PACTRL_ACCESSA *ppAccessList, PACTRL_AUDITA *ppAuditList, LPSTR *lppOwner, LPSTR *lppGroup)
{
    struct qemu_GetSecurityInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYINFOEXA);
    call.hObject = (uint64_t)hObject;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.lpProvider = (uint64_t)lpProvider;
    call.lpProperty = (uint64_t)lpProperty;
    call.ppAccessList = (uint64_t)ppAccessList;
    call.ppAuditList = (uint64_t)ppAuditList;
    call.lppOwner = (uint64_t)lppOwner;
    call.lppGroup = (uint64_t)lppGroup;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetSecurityInfoExA *c = (struct qemu_GetSecurityInfoExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityInfoExA(QEMU_G2H(c->hObject), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->lpProvider), QEMU_G2H(c->lpProperty), QEMU_G2H(c->ppAccessList), QEMU_G2H(c->ppAuditList), QEMU_G2H(c->lppOwner), QEMU_G2H(c->lppGroup));
}

#endif

struct qemu_GetSecurityInfoExW
{
    struct qemu_syscall super;
    uint64_t hObject;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t lpProvider;
    uint64_t lpProperty;
    uint64_t ppAccessList;
    uint64_t ppAuditList;
    uint64_t lppOwner;
    uint64_t lppGroup;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetSecurityInfoExW(HANDLE hObject, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, LPCWSTR lpProvider, LPCWSTR lpProperty, PACTRL_ACCESSW *ppAccessList, PACTRL_AUDITW *ppAuditList, LPWSTR *lppOwner, LPWSTR *lppGroup)
{
    struct qemu_GetSecurityInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSECURITYINFOEXW);
    call.hObject = (uint64_t)hObject;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.lpProvider = (uint64_t)lpProvider;
    call.lpProperty = (uint64_t)lpProperty;
    call.ppAccessList = (uint64_t)ppAccessList;
    call.ppAuditList = (uint64_t)ppAuditList;
    call.lppOwner = (uint64_t)lppOwner;
    call.lppGroup = (uint64_t)lppGroup;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSecurityInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetSecurityInfoExW *c = (struct qemu_GetSecurityInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSecurityInfoExW(QEMU_G2H(c->hObject), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->lpProvider), QEMU_G2H(c->lpProperty), QEMU_G2H(c->ppAccessList), QEMU_G2H(c->ppAuditList), QEMU_G2H(c->lppOwner), QEMU_G2H(c->lppGroup));
}

#endif

struct qemu_BuildExplicitAccessWithNameA
{
    struct qemu_syscall super;
    uint64_t pExplicitAccess;
    uint64_t pTrusteeName;
    uint64_t AccessPermissions;
    uint64_t AccessMode;
    uint64_t Inheritance;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildExplicitAccessWithNameA(PEXPLICIT_ACCESSA pExplicitAccess, LPSTR pTrusteeName, DWORD AccessPermissions, ACCESS_MODE AccessMode, DWORD Inheritance)
{
    struct qemu_BuildExplicitAccessWithNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDEXPLICITACCESSWITHNAMEA);
    call.pExplicitAccess = (uint64_t)pExplicitAccess;
    call.pTrusteeName = (uint64_t)pTrusteeName;
    call.AccessPermissions = (uint64_t)AccessPermissions;
    call.AccessMode = (uint64_t)AccessMode;
    call.Inheritance = (uint64_t)Inheritance;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildExplicitAccessWithNameA(struct qemu_syscall *call)
{
    struct qemu_BuildExplicitAccessWithNameA *c = (struct qemu_BuildExplicitAccessWithNameA *)call;
    WINE_FIXME("Unverified!\n");
    BuildExplicitAccessWithNameA(QEMU_G2H(c->pExplicitAccess), QEMU_G2H(c->pTrusteeName), c->AccessPermissions, c->AccessMode, c->Inheritance);
}

#endif

struct qemu_BuildExplicitAccessWithNameW
{
    struct qemu_syscall super;
    uint64_t pExplicitAccess;
    uint64_t pTrusteeName;
    uint64_t AccessPermissions;
    uint64_t AccessMode;
    uint64_t Inheritance;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildExplicitAccessWithNameW(PEXPLICIT_ACCESSW pExplicitAccess, LPWSTR pTrusteeName, DWORD AccessPermissions, ACCESS_MODE AccessMode, DWORD Inheritance)
{
    struct qemu_BuildExplicitAccessWithNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDEXPLICITACCESSWITHNAMEW);
    call.pExplicitAccess = (uint64_t)pExplicitAccess;
    call.pTrusteeName = (uint64_t)pTrusteeName;
    call.AccessPermissions = (uint64_t)AccessPermissions;
    call.AccessMode = (uint64_t)AccessMode;
    call.Inheritance = (uint64_t)Inheritance;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildExplicitAccessWithNameW(struct qemu_syscall *call)
{
    struct qemu_BuildExplicitAccessWithNameW *c = (struct qemu_BuildExplicitAccessWithNameW *)call;
    WINE_FIXME("Unverified!\n");
    BuildExplicitAccessWithNameW(QEMU_G2H(c->pExplicitAccess), QEMU_G2H(c->pTrusteeName), c->AccessPermissions, c->AccessMode, c->Inheritance);
}

#endif

struct qemu_BuildTrusteeWithObjectsAndNameA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t pObjName;
    uint64_t ObjectType;
    uint64_t ObjectTypeName;
    uint64_t InheritedObjectTypeName;
    uint64_t Name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithObjectsAndNameA(PTRUSTEEA pTrustee, POBJECTS_AND_NAME_A pObjName, SE_OBJECT_TYPE ObjectType, LPSTR ObjectTypeName, LPSTR InheritedObjectTypeName, LPSTR Name)
{
    struct qemu_BuildTrusteeWithObjectsAndNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHOBJECTSANDNAMEA);
    call.pTrustee = (uint64_t)pTrustee;
    call.pObjName = (uint64_t)pObjName;
    call.ObjectType = (uint64_t)ObjectType;
    call.ObjectTypeName = (uint64_t)ObjectTypeName;
    call.InheritedObjectTypeName = (uint64_t)InheritedObjectTypeName;
    call.Name = (uint64_t)Name;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithObjectsAndNameA(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithObjectsAndNameA *c = (struct qemu_BuildTrusteeWithObjectsAndNameA *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithObjectsAndNameA(QEMU_G2H(c->pTrustee), QEMU_G2H(c->pObjName), c->ObjectType, QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->InheritedObjectTypeName), QEMU_G2H(c->Name));
}

#endif

struct qemu_BuildTrusteeWithObjectsAndNameW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t pObjName;
    uint64_t ObjectType;
    uint64_t ObjectTypeName;
    uint64_t InheritedObjectTypeName;
    uint64_t Name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithObjectsAndNameW(PTRUSTEEW pTrustee, POBJECTS_AND_NAME_W pObjName, SE_OBJECT_TYPE ObjectType, LPWSTR ObjectTypeName, LPWSTR InheritedObjectTypeName, LPWSTR Name)
{
    struct qemu_BuildTrusteeWithObjectsAndNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHOBJECTSANDNAMEW);
    call.pTrustee = (uint64_t)pTrustee;
    call.pObjName = (uint64_t)pObjName;
    call.ObjectType = (uint64_t)ObjectType;
    call.ObjectTypeName = (uint64_t)ObjectTypeName;
    call.InheritedObjectTypeName = (uint64_t)InheritedObjectTypeName;
    call.Name = (uint64_t)Name;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithObjectsAndNameW(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithObjectsAndNameW *c = (struct qemu_BuildTrusteeWithObjectsAndNameW *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithObjectsAndNameW(QEMU_G2H(c->pTrustee), QEMU_G2H(c->pObjName), c->ObjectType, QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->InheritedObjectTypeName), QEMU_G2H(c->Name));
}

#endif

struct qemu_BuildTrusteeWithObjectsAndSidA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t pObjSid;
    uint64_t pObjectGuid;
    uint64_t pInheritedObjectGuid;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithObjectsAndSidA(PTRUSTEEA pTrustee, POBJECTS_AND_SID pObjSid, GUID* pObjectGuid, GUID* pInheritedObjectGuid, PSID pSid)
{
    struct qemu_BuildTrusteeWithObjectsAndSidA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHOBJECTSANDSIDA);
    call.pTrustee = (uint64_t)pTrustee;
    call.pObjSid = (uint64_t)pObjSid;
    call.pObjectGuid = (uint64_t)pObjectGuid;
    call.pInheritedObjectGuid = (uint64_t)pInheritedObjectGuid;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithObjectsAndSidA(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithObjectsAndSidA *c = (struct qemu_BuildTrusteeWithObjectsAndSidA *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithObjectsAndSidA(QEMU_G2H(c->pTrustee), QEMU_G2H(c->pObjSid), QEMU_G2H(c->pObjectGuid), QEMU_G2H(c->pInheritedObjectGuid), QEMU_G2H(c->pSid));
}

#endif

struct qemu_BuildTrusteeWithObjectsAndSidW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t pObjSid;
    uint64_t pObjectGuid;
    uint64_t pInheritedObjectGuid;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithObjectsAndSidW(PTRUSTEEW pTrustee, POBJECTS_AND_SID pObjSid, GUID* pObjectGuid, GUID* pInheritedObjectGuid, PSID pSid)
{
    struct qemu_BuildTrusteeWithObjectsAndSidW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHOBJECTSANDSIDW);
    call.pTrustee = (uint64_t)pTrustee;
    call.pObjSid = (uint64_t)pObjSid;
    call.pObjectGuid = (uint64_t)pObjectGuid;
    call.pInheritedObjectGuid = (uint64_t)pInheritedObjectGuid;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithObjectsAndSidW(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithObjectsAndSidW *c = (struct qemu_BuildTrusteeWithObjectsAndSidW *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithObjectsAndSidW(QEMU_G2H(c->pTrustee), QEMU_G2H(c->pObjSid), QEMU_G2H(c->pObjectGuid), QEMU_G2H(c->pInheritedObjectGuid), QEMU_G2H(c->pSid));
}

#endif

struct qemu_BuildTrusteeWithSidA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithSidA(PTRUSTEEA pTrustee, PSID pSid)
{
    struct qemu_BuildTrusteeWithSidA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHSIDA);
    call.pTrustee = (uint64_t)pTrustee;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithSidA(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithSidA *c = (struct qemu_BuildTrusteeWithSidA *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithSidA(QEMU_G2H(c->pTrustee), QEMU_G2H(c->pSid));
}

#endif

struct qemu_BuildTrusteeWithSidW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithSidW(PTRUSTEEW pTrustee, PSID pSid)
{
    struct qemu_BuildTrusteeWithSidW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHSIDW);
    call.pTrustee = (uint64_t)pTrustee;
    call.pSid = (uint64_t)pSid;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithSidW(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithSidW *c = (struct qemu_BuildTrusteeWithSidW *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithSidW(QEMU_G2H(c->pTrustee), QEMU_G2H(c->pSid));
}

#endif

struct qemu_BuildTrusteeWithNameA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithNameA(PTRUSTEEA pTrustee, LPSTR name)
{
    struct qemu_BuildTrusteeWithNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHNAMEA);
    call.pTrustee = (uint64_t)pTrustee;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithNameA(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithNameA *c = (struct qemu_BuildTrusteeWithNameA *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithNameA(QEMU_G2H(c->pTrustee), QEMU_G2H(c->name));
}

#endif

struct qemu_BuildTrusteeWithNameW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI BuildTrusteeWithNameW(PTRUSTEEW pTrustee, LPWSTR name)
{
    struct qemu_BuildTrusteeWithNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDTRUSTEEWITHNAMEW);
    call.pTrustee = (uint64_t)pTrustee;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);
}

#else

void qemu_BuildTrusteeWithNameW(struct qemu_syscall *call)
{
    struct qemu_BuildTrusteeWithNameW *c = (struct qemu_BuildTrusteeWithNameW *)call;
    WINE_FIXME("Unverified!\n");
    BuildTrusteeWithNameW(QEMU_G2H(c->pTrustee), QEMU_G2H(c->name));
}

#endif

struct qemu_GetTrusteeFormA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRUSTEE_FORM WINAPI GetTrusteeFormA(PTRUSTEEA pTrustee)
{
    struct qemu_GetTrusteeFormA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRUSTEEFORMA);
    call.pTrustee = (uint64_t)pTrustee;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTrusteeFormA(struct qemu_syscall *call)
{
    struct qemu_GetTrusteeFormA *c = (struct qemu_GetTrusteeFormA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTrusteeFormA(QEMU_G2H(c->pTrustee));
}

#endif

struct qemu_GetTrusteeFormW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRUSTEE_FORM WINAPI GetTrusteeFormW(PTRUSTEEW pTrustee)
{
    struct qemu_GetTrusteeFormW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRUSTEEFORMW);
    call.pTrustee = (uint64_t)pTrustee;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTrusteeFormW(struct qemu_syscall *call)
{
    struct qemu_GetTrusteeFormW *c = (struct qemu_GetTrusteeFormW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTrusteeFormW(QEMU_G2H(c->pTrustee));
}

#endif

struct qemu_GetTrusteeNameA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI GetTrusteeNameA(PTRUSTEEA pTrustee)
{
    struct qemu_GetTrusteeNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRUSTEENAMEA);
    call.pTrustee = (uint64_t)pTrustee;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_GetTrusteeNameA(struct qemu_syscall *call)
{
    struct qemu_GetTrusteeNameA *c = (struct qemu_GetTrusteeNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetTrusteeNameA(QEMU_G2H(c->pTrustee));
}

#endif

struct qemu_GetTrusteeNameW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI GetTrusteeNameW(PTRUSTEEW pTrustee)
{
    struct qemu_GetTrusteeNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRUSTEENAMEW);
    call.pTrustee = (uint64_t)pTrustee;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

void qemu_GetTrusteeNameW(struct qemu_syscall *call)
{
    struct qemu_GetTrusteeNameW *c = (struct qemu_GetTrusteeNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetTrusteeNameW(QEMU_G2H(c->pTrustee));
}

#endif

struct qemu_GetTrusteeTypeA
{
    struct qemu_syscall super;
    uint64_t pTrustee;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRUSTEE_TYPE WINAPI GetTrusteeTypeA(PTRUSTEEA pTrustee)
{
    struct qemu_GetTrusteeTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRUSTEETYPEA);
    call.pTrustee = (uint64_t)pTrustee;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTrusteeTypeA(struct qemu_syscall *call)
{
    struct qemu_GetTrusteeTypeA *c = (struct qemu_GetTrusteeTypeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTrusteeTypeA(QEMU_G2H(c->pTrustee));
}

#endif

struct qemu_GetTrusteeTypeW
{
    struct qemu_syscall super;
    uint64_t pTrustee;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRUSTEE_TYPE WINAPI GetTrusteeTypeW(PTRUSTEEW pTrustee)
{
    struct qemu_GetTrusteeTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRUSTEETYPEW);
    call.pTrustee = (uint64_t)pTrustee;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTrusteeTypeW(struct qemu_syscall *call)
{
    struct qemu_GetTrusteeTypeW *c = (struct qemu_GetTrusteeTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTrusteeTypeW(QEMU_G2H(c->pTrustee));
}

#endif

struct qemu_SetAclInformation
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t pAclInformation;
    uint64_t nAclInformationLength;
    uint64_t dwAclInformationClass;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetAclInformation(PACL pAcl, LPVOID pAclInformation, DWORD nAclInformationLength, ACL_INFORMATION_CLASS dwAclInformationClass)
{
    struct qemu_SetAclInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETACLINFORMATION);
    call.pAcl = (uint64_t)pAcl;
    call.pAclInformation = (uint64_t)pAclInformation;
    call.nAclInformationLength = (uint64_t)nAclInformationLength;
    call.dwAclInformationClass = (uint64_t)dwAclInformationClass;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetAclInformation(struct qemu_syscall *call)
{
    struct qemu_SetAclInformation *c = (struct qemu_SetAclInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetAclInformation(QEMU_G2H(c->pAcl), QEMU_G2H(c->pAclInformation), c->nAclInformationLength, c->dwAclInformationClass);
}

#endif

struct qemu_SetEntriesInAclA
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t pEntries;
    uint64_t OldAcl;
    uint64_t NewAcl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetEntriesInAclA(ULONG count, PEXPLICIT_ACCESSA pEntries, PACL OldAcl, PACL* NewAcl)
{
    struct qemu_SetEntriesInAclA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENTRIESINACLA);
    call.count = (uint64_t)count;
    call.pEntries = (uint64_t)pEntries;
    call.OldAcl = (uint64_t)OldAcl;
    call.NewAcl = (uint64_t)NewAcl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEntriesInAclA(struct qemu_syscall *call)
{
    struct qemu_SetEntriesInAclA *c = (struct qemu_SetEntriesInAclA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetEntriesInAclA(c->count, QEMU_G2H(c->pEntries), QEMU_G2H(c->OldAcl), QEMU_G2H(c->NewAcl));
}

#endif

struct qemu_SetEntriesInAclW
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t pEntries;
    uint64_t OldAcl;
    uint64_t NewAcl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetEntriesInAclW(ULONG count, PEXPLICIT_ACCESSW pEntries, PACL OldAcl, PACL* NewAcl)
{
    struct qemu_SetEntriesInAclW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETENTRIESINACLW);
    call.count = (uint64_t)count;
    call.pEntries = (uint64_t)pEntries;
    call.OldAcl = (uint64_t)OldAcl;
    call.NewAcl = (uint64_t)NewAcl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetEntriesInAclW(struct qemu_syscall *call)
{
    struct qemu_SetEntriesInAclW *c = (struct qemu_SetEntriesInAclW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetEntriesInAclW(c->count, QEMU_G2H(c->pEntries), QEMU_G2H(c->OldAcl), QEMU_G2H(c->NewAcl));
}

#endif

struct qemu_SetNamedSecurityInfoA
{
    struct qemu_syscall super;
    uint64_t pObjectName;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t psidOwner;
    uint64_t psidGroup;
    uint64_t pDacl;
    uint64_t pSacl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetNamedSecurityInfoA(LPSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID psidOwner, PSID psidGroup, PACL pDacl, PACL pSacl)
{
    struct qemu_SetNamedSecurityInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETNAMEDSECURITYINFOA);
    call.pObjectName = (uint64_t)pObjectName;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.psidOwner = (uint64_t)psidOwner;
    call.psidGroup = (uint64_t)psidGroup;
    call.pDacl = (uint64_t)pDacl;
    call.pSacl = (uint64_t)pSacl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetNamedSecurityInfoA(struct qemu_syscall *call)
{
    struct qemu_SetNamedSecurityInfoA *c = (struct qemu_SetNamedSecurityInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetNamedSecurityInfoA(QEMU_G2H(c->pObjectName), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->psidOwner), QEMU_G2H(c->psidGroup), QEMU_G2H(c->pDacl), QEMU_G2H(c->pSacl));
}

#endif

struct qemu_SetPrivateObjectSecurity
{
    struct qemu_syscall super;
    uint64_t SecurityInformation;
    uint64_t ModificationDescriptor;
    uint64_t ObjectsSecurityDescriptor;
    uint64_t GenericMapping;
    uint64_t Token;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetPrivateObjectSecurity(SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR ModificationDescriptor, PSECURITY_DESCRIPTOR* ObjectsSecurityDescriptor, PGENERIC_MAPPING GenericMapping, HANDLE Token)
{
    struct qemu_SetPrivateObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRIVATEOBJECTSECURITY);
    call.SecurityInformation = (uint64_t)SecurityInformation;
    call.ModificationDescriptor = (uint64_t)ModificationDescriptor;
    call.ObjectsSecurityDescriptor = (uint64_t)ObjectsSecurityDescriptor;
    call.GenericMapping = (uint64_t)GenericMapping;
    call.Token = (uint64_t)Token;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrivateObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_SetPrivateObjectSecurity *c = (struct qemu_SetPrivateObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrivateObjectSecurity(c->SecurityInformation, QEMU_G2H(c->ModificationDescriptor), QEMU_G2H(c->ObjectsSecurityDescriptor), QEMU_G2H(c->GenericMapping), QEMU_G2H(c->Token));
}

#endif

struct qemu_AreAllAccessesGranted
{
    struct qemu_syscall super;
    uint64_t GrantedAccess;
    uint64_t DesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AreAllAccessesGranted(DWORD GrantedAccess, DWORD DesiredAccess)
{
    struct qemu_AreAllAccessesGranted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AREALLACCESSESGRANTED);
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.DesiredAccess = (uint64_t)DesiredAccess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AreAllAccessesGranted(struct qemu_syscall *call)
{
    struct qemu_AreAllAccessesGranted *c = (struct qemu_AreAllAccessesGranted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AreAllAccessesGranted(c->GrantedAccess, c->DesiredAccess);
}

#endif

struct qemu_AreAnyAccessesGranted
{
    struct qemu_syscall super;
    uint64_t GrantedAccess;
    uint64_t DesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AreAnyAccessesGranted(DWORD GrantedAccess, DWORD DesiredAccess)
{
    struct qemu_AreAnyAccessesGranted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AREANYACCESSESGRANTED);
    call.GrantedAccess = (uint64_t)GrantedAccess;
    call.DesiredAccess = (uint64_t)DesiredAccess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AreAnyAccessesGranted(struct qemu_syscall *call)
{
    struct qemu_AreAnyAccessesGranted *c = (struct qemu_AreAnyAccessesGranted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AreAnyAccessesGranted(c->GrantedAccess, c->DesiredAccess);
}

#endif

struct qemu_SetNamedSecurityInfoW
{
    struct qemu_syscall super;
    uint64_t pObjectName;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t psidOwner;
    uint64_t psidGroup;
    uint64_t pDacl;
    uint64_t pSacl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetNamedSecurityInfoW(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID psidOwner, PSID psidGroup, PACL pDacl, PACL pSacl)
{
    struct qemu_SetNamedSecurityInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETNAMEDSECURITYINFOW);
    call.pObjectName = (uint64_t)pObjectName;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.psidOwner = (uint64_t)psidOwner;
    call.psidGroup = (uint64_t)psidGroup;
    call.pDacl = (uint64_t)pDacl;
    call.pSacl = (uint64_t)pSacl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetNamedSecurityInfoW(struct qemu_syscall *call)
{
    struct qemu_SetNamedSecurityInfoW *c = (struct qemu_SetNamedSecurityInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetNamedSecurityInfoW(QEMU_G2H(c->pObjectName), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->psidOwner), QEMU_G2H(c->psidGroup), QEMU_G2H(c->pDacl), QEMU_G2H(c->pSacl));
}

#endif

struct qemu_GetExplicitEntriesFromAclA
{
    struct qemu_syscall super;
    uint64_t pacl;
    uint64_t pcCountOfExplicitEntries;
    uint64_t pListOfExplicitEntries;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetExplicitEntriesFromAclA(PACL pacl, PULONG pcCountOfExplicitEntries, PEXPLICIT_ACCESSA* pListOfExplicitEntries)
{
    struct qemu_GetExplicitEntriesFromAclA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXPLICITENTRIESFROMACLA);
    call.pacl = (uint64_t)pacl;
    call.pcCountOfExplicitEntries = (uint64_t)pcCountOfExplicitEntries;
    call.pListOfExplicitEntries = (uint64_t)pListOfExplicitEntries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExplicitEntriesFromAclA(struct qemu_syscall *call)
{
    struct qemu_GetExplicitEntriesFromAclA *c = (struct qemu_GetExplicitEntriesFromAclA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExplicitEntriesFromAclA(QEMU_G2H(c->pacl), QEMU_G2H(c->pcCountOfExplicitEntries), QEMU_G2H(c->pListOfExplicitEntries));
}

#endif

struct qemu_GetExplicitEntriesFromAclW
{
    struct qemu_syscall super;
    uint64_t pacl;
    uint64_t pcCountOfExplicitEntries;
    uint64_t pListOfExplicitEntries;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetExplicitEntriesFromAclW(PACL pacl, PULONG pcCountOfExplicitEntries, PEXPLICIT_ACCESSW* pListOfExplicitEntries)
{
    struct qemu_GetExplicitEntriesFromAclW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXPLICITENTRIESFROMACLW);
    call.pacl = (uint64_t)pacl;
    call.pcCountOfExplicitEntries = (uint64_t)pcCountOfExplicitEntries;
    call.pListOfExplicitEntries = (uint64_t)pListOfExplicitEntries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExplicitEntriesFromAclW(struct qemu_syscall *call)
{
    struct qemu_GetExplicitEntriesFromAclW *c = (struct qemu_GetExplicitEntriesFromAclW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExplicitEntriesFromAclW(QEMU_G2H(c->pacl), QEMU_G2H(c->pcCountOfExplicitEntries), QEMU_G2H(c->pListOfExplicitEntries));
}

#endif

struct qemu_GetAuditedPermissionsFromAclA
{
    struct qemu_syscall super;
    uint64_t pacl;
    uint64_t pTrustee;
    uint64_t pSuccessfulAuditedRights;
    uint64_t pFailedAuditRights;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetAuditedPermissionsFromAclA(PACL pacl, PTRUSTEEA pTrustee, PACCESS_MASK pSuccessfulAuditedRights, PACCESS_MASK pFailedAuditRights)
{
    struct qemu_GetAuditedPermissionsFromAclA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETAUDITEDPERMISSIONSFROMACLA);
    call.pacl = (uint64_t)pacl;
    call.pTrustee = (uint64_t)pTrustee;
    call.pSuccessfulAuditedRights = (uint64_t)pSuccessfulAuditedRights;
    call.pFailedAuditRights = (uint64_t)pFailedAuditRights;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetAuditedPermissionsFromAclA to Wine headers? */
extern DWORD WINAPI GetAuditedPermissionsFromAclA(PACL pacl, PTRUSTEEA pTrustee, PACCESS_MASK pSuccessfulAuditedRights, PACCESS_MASK pFailedAuditRights);
void qemu_GetAuditedPermissionsFromAclA(struct qemu_syscall *call)
{
    struct qemu_GetAuditedPermissionsFromAclA *c = (struct qemu_GetAuditedPermissionsFromAclA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAuditedPermissionsFromAclA(QEMU_G2H(c->pacl), QEMU_G2H(c->pTrustee), QEMU_G2H(c->pSuccessfulAuditedRights), QEMU_G2H(c->pFailedAuditRights));
}

#endif

struct qemu_GetAuditedPermissionsFromAclW
{
    struct qemu_syscall super;
    uint64_t pacl;
    uint64_t pTrustee;
    uint64_t pSuccessfulAuditedRights;
    uint64_t pFailedAuditRights;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetAuditedPermissionsFromAclW(PACL pacl, PTRUSTEEW pTrustee, PACCESS_MASK pSuccessfulAuditedRights, PACCESS_MASK pFailedAuditRights)
{
    struct qemu_GetAuditedPermissionsFromAclW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETAUDITEDPERMISSIONSFROMACLW);
    call.pacl = (uint64_t)pacl;
    call.pTrustee = (uint64_t)pTrustee;
    call.pSuccessfulAuditedRights = (uint64_t)pSuccessfulAuditedRights;
    call.pFailedAuditRights = (uint64_t)pFailedAuditRights;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetAuditedPermissionsFromAclW to Wine headers? */
extern DWORD WINAPI GetAuditedPermissionsFromAclW(PACL pacl, PTRUSTEEW pTrustee, PACCESS_MASK pSuccessfulAuditedRights, PACCESS_MASK pFailedAuditRights);
void qemu_GetAuditedPermissionsFromAclW(struct qemu_syscall *call)
{
    struct qemu_GetAuditedPermissionsFromAclW *c = (struct qemu_GetAuditedPermissionsFromAclW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAuditedPermissionsFromAclW(QEMU_G2H(c->pacl), QEMU_G2H(c->pTrustee), QEMU_G2H(c->pSuccessfulAuditedRights), QEMU_G2H(c->pFailedAuditRights));
}

#endif

struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorA
{
    struct qemu_syscall super;
    uint64_t StringSecurityDescriptor;
    uint64_t StringSDRevision;
    uint64_t SecurityDescriptor;
    uint64_t SecurityDescriptorSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertStringSecurityDescriptorToSecurityDescriptorA(LPCSTR StringSecurityDescriptor, DWORD StringSDRevision, PSECURITY_DESCRIPTOR* SecurityDescriptor, PULONG SecurityDescriptorSize)
{
    struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSTRINGSECURITYDESCRIPTORTOSECURITYDESCRIPTORA);
    call.StringSecurityDescriptor = (uint64_t)StringSecurityDescriptor;
    call.StringSDRevision = (uint64_t)StringSDRevision;
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.SecurityDescriptorSize = (uint64_t)SecurityDescriptorSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertStringSecurityDescriptorToSecurityDescriptorA to Wine headers? */
extern BOOL WINAPI ConvertStringSecurityDescriptorToSecurityDescriptorA(LPCSTR StringSecurityDescriptor, DWORD StringSDRevision, PSECURITY_DESCRIPTOR* SecurityDescriptor, PULONG SecurityDescriptorSize);
void qemu_ConvertStringSecurityDescriptorToSecurityDescriptorA(struct qemu_syscall *call)
{
    struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorA *c = (struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertStringSecurityDescriptorToSecurityDescriptorA(QEMU_G2H(c->StringSecurityDescriptor), c->StringSDRevision, QEMU_G2H(c->SecurityDescriptor), QEMU_G2H(c->SecurityDescriptorSize));
}

#endif

struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorW
{
    struct qemu_syscall super;
    uint64_t StringSecurityDescriptor;
    uint64_t StringSDRevision;
    uint64_t SecurityDescriptor;
    uint64_t SecurityDescriptorSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertStringSecurityDescriptorToSecurityDescriptorW(LPCWSTR StringSecurityDescriptor, DWORD StringSDRevision, PSECURITY_DESCRIPTOR* SecurityDescriptor, PULONG SecurityDescriptorSize)
{
    struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSTRINGSECURITYDESCRIPTORTOSECURITYDESCRIPTORW);
    call.StringSecurityDescriptor = (uint64_t)StringSecurityDescriptor;
    call.StringSDRevision = (uint64_t)StringSDRevision;
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.SecurityDescriptorSize = (uint64_t)SecurityDescriptorSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertStringSecurityDescriptorToSecurityDescriptorW to Wine headers? */
extern BOOL WINAPI ConvertStringSecurityDescriptorToSecurityDescriptorW(LPCWSTR StringSecurityDescriptor, DWORD StringSDRevision, PSECURITY_DESCRIPTOR* SecurityDescriptor, PULONG SecurityDescriptorSize);
void qemu_ConvertStringSecurityDescriptorToSecurityDescriptorW(struct qemu_syscall *call)
{
    struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorW *c = (struct qemu_ConvertStringSecurityDescriptorToSecurityDescriptorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertStringSecurityDescriptorToSecurityDescriptorW(QEMU_G2H(c->StringSecurityDescriptor), c->StringSDRevision, QEMU_G2H(c->SecurityDescriptor), QEMU_G2H(c->SecurityDescriptorSize));
}

#endif

struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorW
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t SDRevision;
    uint64_t RequestedInformation;
    uint64_t OutputString;
    uint64_t OutputLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertSecurityDescriptorToStringSecurityDescriptorW(PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD SDRevision, SECURITY_INFORMATION RequestedInformation, LPWSTR *OutputString, PULONG OutputLen)
{
    struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSECURITYDESCRIPTORTOSTRINGSECURITYDESCRIPTORW);
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.SDRevision = (uint64_t)SDRevision;
    call.RequestedInformation = (uint64_t)RequestedInformation;
    call.OutputString = (uint64_t)OutputString;
    call.OutputLen = (uint64_t)OutputLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertSecurityDescriptorToStringSecurityDescriptorW to Wine headers? */
extern BOOL WINAPI ConvertSecurityDescriptorToStringSecurityDescriptorW(PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD SDRevision, SECURITY_INFORMATION RequestedInformation, LPWSTR *OutputString, PULONG OutputLen);
void qemu_ConvertSecurityDescriptorToStringSecurityDescriptorW(struct qemu_syscall *call)
{
    struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorW *c = (struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertSecurityDescriptorToStringSecurityDescriptorW(QEMU_G2H(c->SecurityDescriptor), c->SDRevision, c->RequestedInformation, QEMU_G2H(c->OutputString), QEMU_G2H(c->OutputLen));
}

#endif

struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorA
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t SDRevision;
    uint64_t Information;
    uint64_t OutputString;
    uint64_t OutputLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertSecurityDescriptorToStringSecurityDescriptorA(PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD SDRevision, SECURITY_INFORMATION Information, LPSTR *OutputString, PULONG OutputLen)
{
    struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSECURITYDESCRIPTORTOSTRINGSECURITYDESCRIPTORA);
    call.SecurityDescriptor = (uint64_t)SecurityDescriptor;
    call.SDRevision = (uint64_t)SDRevision;
    call.Information = (uint64_t)Information;
    call.OutputString = (uint64_t)OutputString;
    call.OutputLen = (uint64_t)OutputLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertSecurityDescriptorToStringSecurityDescriptorA to Wine headers? */
extern BOOL WINAPI ConvertSecurityDescriptorToStringSecurityDescriptorA(PSECURITY_DESCRIPTOR SecurityDescriptor, DWORD SDRevision, SECURITY_INFORMATION Information, LPSTR *OutputString, PULONG OutputLen);
void qemu_ConvertSecurityDescriptorToStringSecurityDescriptorA(struct qemu_syscall *call)
{
    struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorA *c = (struct qemu_ConvertSecurityDescriptorToStringSecurityDescriptorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertSecurityDescriptorToStringSecurityDescriptorA(QEMU_G2H(c->SecurityDescriptor), c->SDRevision, c->Information, QEMU_G2H(c->OutputString), QEMU_G2H(c->OutputLen));
}

#endif

struct qemu_ConvertStringSidToSidW
{
    struct qemu_syscall super;
    uint64_t StringSid;
    uint64_t Sid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertStringSidToSidW(LPCWSTR StringSid, PSID* Sid)
{
    struct qemu_ConvertStringSidToSidW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSTRINGSIDTOSIDW);
    call.StringSid = (uint64_t)StringSid;
    call.Sid = (uint64_t)Sid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertStringSidToSidW to Wine headers? */
extern BOOL WINAPI ConvertStringSidToSidW(LPCWSTR StringSid, PSID* Sid);
void qemu_ConvertStringSidToSidW(struct qemu_syscall *call)
{
    struct qemu_ConvertStringSidToSidW *c = (struct qemu_ConvertStringSidToSidW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertStringSidToSidW(QEMU_G2H(c->StringSid), QEMU_G2H(c->Sid));
}

#endif

struct qemu_ConvertStringSidToSidA
{
    struct qemu_syscall super;
    uint64_t StringSid;
    uint64_t Sid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertStringSidToSidA(LPCSTR StringSid, PSID* Sid)
{
    struct qemu_ConvertStringSidToSidA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSTRINGSIDTOSIDA);
    call.StringSid = (uint64_t)StringSid;
    call.Sid = (uint64_t)Sid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertStringSidToSidA to Wine headers? */
extern BOOL WINAPI ConvertStringSidToSidA(LPCSTR StringSid, PSID* Sid);
void qemu_ConvertStringSidToSidA(struct qemu_syscall *call)
{
    struct qemu_ConvertStringSidToSidA *c = (struct qemu_ConvertStringSidToSidA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertStringSidToSidA(QEMU_G2H(c->StringSid), QEMU_G2H(c->Sid));
}

#endif

struct qemu_ConvertSidToStringSidW
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t pstr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertSidToStringSidW(PSID pSid, LPWSTR *pstr)
{
    struct qemu_ConvertSidToStringSidW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSIDTOSTRINGSIDW);
    call.pSid = (uint64_t)pSid;
    call.pstr = (uint64_t)pstr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertSidToStringSidW to Wine headers? */
extern BOOL WINAPI ConvertSidToStringSidW(PSID pSid, LPWSTR *pstr);
void qemu_ConvertSidToStringSidW(struct qemu_syscall *call)
{
    struct qemu_ConvertSidToStringSidW *c = (struct qemu_ConvertSidToStringSidW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertSidToStringSidW(QEMU_G2H(c->pSid), QEMU_G2H(c->pstr));
}

#endif

struct qemu_ConvertSidToStringSidA
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t pstr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertSidToStringSidA(PSID pSid, LPSTR *pstr)
{
    struct qemu_ConvertSidToStringSidA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTSIDTOSTRINGSIDA);
    call.pSid = (uint64_t)pSid;
    call.pstr = (uint64_t)pstr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ConvertSidToStringSidA to Wine headers? */
extern BOOL WINAPI ConvertSidToStringSidA(PSID pSid, LPSTR *pstr);
void qemu_ConvertSidToStringSidA(struct qemu_syscall *call)
{
    struct qemu_ConvertSidToStringSidA *c = (struct qemu_ConvertSidToStringSidA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertSidToStringSidA(QEMU_G2H(c->pSid), QEMU_G2H(c->pstr));
}

#endif

struct qemu_ConvertToAutoInheritPrivateObjectSecurity
{
    struct qemu_syscall super;
    uint64_t pdesc;
    uint64_t cdesc;
    uint64_t ndesc;
    uint64_t objtype;
    uint64_t isdir;
    uint64_t genmap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI ConvertToAutoInheritPrivateObjectSecurity(PSECURITY_DESCRIPTOR pdesc, PSECURITY_DESCRIPTOR cdesc, PSECURITY_DESCRIPTOR* ndesc, GUID* objtype, BOOLEAN isdir, PGENERIC_MAPPING genmap)
{
    struct qemu_ConvertToAutoInheritPrivateObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTTOAUTOINHERITPRIVATEOBJECTSECURITY);
    call.pdesc = (uint64_t)pdesc;
    call.cdesc = (uint64_t)cdesc;
    call.ndesc = (uint64_t)ndesc;
    call.objtype = (uint64_t)objtype;
    call.isdir = (uint64_t)isdir;
    call.genmap = (uint64_t)genmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertToAutoInheritPrivateObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_ConvertToAutoInheritPrivateObjectSecurity *c = (struct qemu_ConvertToAutoInheritPrivateObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertToAutoInheritPrivateObjectSecurity(QEMU_G2H(c->pdesc), QEMU_G2H(c->cdesc), QEMU_G2H(c->ndesc), QEMU_G2H(c->objtype), c->isdir, QEMU_G2H(c->genmap));
}

#endif

struct qemu_CreatePrivateObjectSecurityEx
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t creator;
    uint64_t out;
    uint64_t objtype;
    uint64_t is_directory;
    uint64_t flags;
    uint64_t token;
    uint64_t mapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreatePrivateObjectSecurityEx(PSECURITY_DESCRIPTOR parent, PSECURITY_DESCRIPTOR creator, PSECURITY_DESCRIPTOR *out, GUID *objtype, BOOL is_directory, ULONG flags, HANDLE token, PGENERIC_MAPPING mapping)
{
    struct qemu_CreatePrivateObjectSecurityEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPRIVATEOBJECTSECURITYEX);
    call.parent = (uint64_t)parent;
    call.creator = (uint64_t)creator;
    call.out = (uint64_t)out;
    call.objtype = (uint64_t)objtype;
    call.is_directory = (uint64_t)is_directory;
    call.flags = (uint64_t)flags;
    call.token = (uint64_t)token;
    call.mapping = (uint64_t)mapping;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreatePrivateObjectSecurityEx(struct qemu_syscall *call)
{
    struct qemu_CreatePrivateObjectSecurityEx *c = (struct qemu_CreatePrivateObjectSecurityEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreatePrivateObjectSecurityEx(QEMU_G2H(c->parent), QEMU_G2H(c->creator), QEMU_G2H(c->out), QEMU_G2H(c->objtype), c->is_directory, c->flags, QEMU_G2H(c->token), QEMU_G2H(c->mapping));
}

#endif

struct qemu_CreatePrivateObjectSecurity
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t creator;
    uint64_t out;
    uint64_t is_container;
    uint64_t token;
    uint64_t mapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreatePrivateObjectSecurity(PSECURITY_DESCRIPTOR parent, PSECURITY_DESCRIPTOR creator, PSECURITY_DESCRIPTOR *out, BOOL is_container, HANDLE token, PGENERIC_MAPPING mapping)
{
    struct qemu_CreatePrivateObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPRIVATEOBJECTSECURITY);
    call.parent = (uint64_t)parent;
    call.creator = (uint64_t)creator;
    call.out = (uint64_t)out;
    call.is_container = (uint64_t)is_container;
    call.token = (uint64_t)token;
    call.mapping = (uint64_t)mapping;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreatePrivateObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_CreatePrivateObjectSecurity *c = (struct qemu_CreatePrivateObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreatePrivateObjectSecurity(QEMU_G2H(c->parent), QEMU_G2H(c->creator), QEMU_G2H(c->out), c->is_container, QEMU_G2H(c->token), QEMU_G2H(c->mapping));
}

#endif

struct qemu_CreatePrivateObjectSecurityWithMultipleInheritance
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t creator;
    uint64_t out;
    uint64_t types;
    uint64_t count;
    uint64_t is_container;
    uint64_t flags;
    uint64_t token;
    uint64_t mapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreatePrivateObjectSecurityWithMultipleInheritance(PSECURITY_DESCRIPTOR parent, PSECURITY_DESCRIPTOR creator, PSECURITY_DESCRIPTOR *out, GUID **types, ULONG count, BOOL is_container, ULONG flags, HANDLE token, PGENERIC_MAPPING mapping)
{
    struct qemu_CreatePrivateObjectSecurityWithMultipleInheritance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPRIVATEOBJECTSECURITYWITHMULTIPLEINHERITANCE);
    call.parent = (uint64_t)parent;
    call.creator = (uint64_t)creator;
    call.out = (uint64_t)out;
    call.types = (uint64_t)types;
    call.count = (uint64_t)count;
    call.is_container = (uint64_t)is_container;
    call.flags = (uint64_t)flags;
    call.token = (uint64_t)token;
    call.mapping = (uint64_t)mapping;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreatePrivateObjectSecurityWithMultipleInheritance(struct qemu_syscall *call)
{
    struct qemu_CreatePrivateObjectSecurityWithMultipleInheritance *c = (struct qemu_CreatePrivateObjectSecurityWithMultipleInheritance *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreatePrivateObjectSecurityWithMultipleInheritance(QEMU_G2H(c->parent), QEMU_G2H(c->creator), QEMU_G2H(c->out), QEMU_G2H(c->types), c->count, c->is_container, c->flags, QEMU_G2H(c->token), QEMU_G2H(c->mapping));
}

#endif

struct qemu_DestroyPrivateObjectSecurity
{
    struct qemu_syscall super;
    uint64_t ObjectDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DestroyPrivateObjectSecurity(PSECURITY_DESCRIPTOR* ObjectDescriptor)
{
    struct qemu_DestroyPrivateObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESTROYPRIVATEOBJECTSECURITY);
    call.ObjectDescriptor = (uint64_t)ObjectDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyPrivateObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_DestroyPrivateObjectSecurity *c = (struct qemu_DestroyPrivateObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DestroyPrivateObjectSecurity(QEMU_G2H(c->ObjectDescriptor));
}

#endif

struct qemu_CreateProcessAsUserA
{
    struct qemu_syscall super;
    uint64_t hToken;
    uint64_t lpApplicationName;
    uint64_t lpCommandLine;
    uint64_t lpProcessAttributes;
    uint64_t lpThreadAttributes;
    uint64_t bInheritHandles;
    uint64_t dwCreationFlags;
    uint64_t lpEnvironment;
    uint64_t lpCurrentDirectory;
    uint64_t lpStartupInfo;
    uint64_t lpProcessInformation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateProcessAsUserA(HANDLE hToken, LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    struct qemu_CreateProcessAsUserA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROCESSASUSERA);
    call.hToken = (uint64_t)hToken;
    call.lpApplicationName = (uint64_t)lpApplicationName;
    call.lpCommandLine = (uint64_t)lpCommandLine;
    call.lpProcessAttributes = (uint64_t)lpProcessAttributes;
    call.lpThreadAttributes = (uint64_t)lpThreadAttributes;
    call.bInheritHandles = (uint64_t)bInheritHandles;
    call.dwCreationFlags = (uint64_t)dwCreationFlags;
    call.lpEnvironment = (uint64_t)lpEnvironment;
    call.lpCurrentDirectory = (uint64_t)lpCurrentDirectory;
    call.lpStartupInfo = (uint64_t)lpStartupInfo;
    call.lpProcessInformation = (uint64_t)lpProcessInformation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateProcessAsUserA(struct qemu_syscall *call)
{
    struct qemu_CreateProcessAsUserA *c = (struct qemu_CreateProcessAsUserA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProcessAsUserA(QEMU_G2H(c->hToken), QEMU_G2H(c->lpApplicationName), QEMU_G2H(c->lpCommandLine), QEMU_G2H(c->lpProcessAttributes), QEMU_G2H(c->lpThreadAttributes), c->bInheritHandles, c->dwCreationFlags, QEMU_G2H(c->lpEnvironment), QEMU_G2H(c->lpCurrentDirectory), QEMU_G2H(c->lpStartupInfo), QEMU_G2H(c->lpProcessInformation));
}

#endif

struct qemu_CreateProcessAsUserW
{
    struct qemu_syscall super;
    uint64_t hToken;
    uint64_t lpApplicationName;
    uint64_t lpCommandLine;
    uint64_t lpProcessAttributes;
    uint64_t lpThreadAttributes;
    uint64_t bInheritHandles;
    uint64_t dwCreationFlags;
    uint64_t lpEnvironment;
    uint64_t lpCurrentDirectory;
    uint64_t lpStartupInfo;
    uint64_t lpProcessInformation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateProcessAsUserW(HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    struct qemu_CreateProcessAsUserW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROCESSASUSERW);
    call.hToken = (uint64_t)hToken;
    call.lpApplicationName = (uint64_t)lpApplicationName;
    call.lpCommandLine = (uint64_t)lpCommandLine;
    call.lpProcessAttributes = (uint64_t)lpProcessAttributes;
    call.lpThreadAttributes = (uint64_t)lpThreadAttributes;
    call.bInheritHandles = (uint64_t)bInheritHandles;
    call.dwCreationFlags = (uint64_t)dwCreationFlags;
    call.lpEnvironment = (uint64_t)lpEnvironment;
    call.lpCurrentDirectory = (uint64_t)lpCurrentDirectory;
    call.lpStartupInfo = (uint64_t)lpStartupInfo;
    call.lpProcessInformation = (uint64_t)lpProcessInformation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateProcessAsUserW(struct qemu_syscall *call)
{
    struct qemu_CreateProcessAsUserW *c = (struct qemu_CreateProcessAsUserW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProcessAsUserW(QEMU_G2H(c->hToken), QEMU_G2H(c->lpApplicationName), QEMU_G2H(c->lpCommandLine), QEMU_G2H(c->lpProcessAttributes), QEMU_G2H(c->lpThreadAttributes), c->bInheritHandles, c->dwCreationFlags, QEMU_G2H(c->lpEnvironment), QEMU_G2H(c->lpCurrentDirectory), QEMU_G2H(c->lpStartupInfo), QEMU_G2H(c->lpProcessInformation));
}

#endif

struct qemu_CreateProcessWithLogonW
{
    struct qemu_syscall super;
    uint64_t lpUsername;
    uint64_t lpDomain;
    uint64_t lpPassword;
    uint64_t dwLogonFlags;
    uint64_t lpApplicationName;
    uint64_t lpCommandLine;
    uint64_t dwCreationFlags;
    uint64_t lpEnvironment;
    uint64_t lpCurrentDirectory;
    uint64_t lpStartupInfo;
    uint64_t lpProcessInformation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateProcessWithLogonW(LPCWSTR lpUsername, LPCWSTR lpDomain, LPCWSTR lpPassword, DWORD dwLogonFlags, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
    struct qemu_CreateProcessWithLogonW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROCESSWITHLOGONW);
    call.lpUsername = (uint64_t)lpUsername;
    call.lpDomain = (uint64_t)lpDomain;
    call.lpPassword = (uint64_t)lpPassword;
    call.dwLogonFlags = (uint64_t)dwLogonFlags;
    call.lpApplicationName = (uint64_t)lpApplicationName;
    call.lpCommandLine = (uint64_t)lpCommandLine;
    call.dwCreationFlags = (uint64_t)dwCreationFlags;
    call.lpEnvironment = (uint64_t)lpEnvironment;
    call.lpCurrentDirectory = (uint64_t)lpCurrentDirectory;
    call.lpStartupInfo = (uint64_t)lpStartupInfo;
    call.lpProcessInformation = (uint64_t)lpProcessInformation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateProcessWithLogonW(struct qemu_syscall *call)
{
    struct qemu_CreateProcessWithLogonW *c = (struct qemu_CreateProcessWithLogonW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProcessWithLogonW(QEMU_G2H(c->lpUsername), QEMU_G2H(c->lpDomain), QEMU_G2H(c->lpPassword), c->dwLogonFlags, QEMU_G2H(c->lpApplicationName), QEMU_G2H(c->lpCommandLine), c->dwCreationFlags, QEMU_G2H(c->lpEnvironment), QEMU_G2H(c->lpCurrentDirectory), QEMU_G2H(c->lpStartupInfo), QEMU_G2H(c->lpProcessInformation));
}

#endif

struct qemu_CreateProcessWithTokenW
{
    struct qemu_syscall super;
    uint64_t token;
    uint64_t logon_flags;
    uint64_t application_name;
    uint64_t command_line;
    uint64_t creation_flags;
    uint64_t environment;
    uint64_t current_directory;
    uint64_t startup_info;
    uint64_t process_information;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateProcessWithTokenW(HANDLE token, DWORD logon_flags, LPCWSTR application_name, LPWSTR command_line, DWORD creation_flags, void *environment, LPCWSTR current_directory, STARTUPINFOW *startup_info, PROCESS_INFORMATION *process_information)
{
    struct qemu_CreateProcessWithTokenW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROCESSWITHTOKENW);
    call.token = (uint64_t)token;
    call.logon_flags = (uint64_t)logon_flags;
    call.application_name = (uint64_t)application_name;
    call.command_line = (uint64_t)command_line;
    call.creation_flags = (uint64_t)creation_flags;
    call.environment = (uint64_t)environment;
    call.current_directory = (uint64_t)current_directory;
    call.startup_info = (uint64_t)startup_info;
    call.process_information = (uint64_t)process_information;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CreateProcessWithTokenW to Wine headers? */
extern BOOL WINAPI CreateProcessWithTokenW(HANDLE token, DWORD logon_flags, LPCWSTR application_name, LPWSTR command_line, DWORD creation_flags, void *environment, LPCWSTR current_directory, STARTUPINFOW *startup_info, PROCESS_INFORMATION *process_information);
void qemu_CreateProcessWithTokenW(struct qemu_syscall *call)
{
    struct qemu_CreateProcessWithTokenW *c = (struct qemu_CreateProcessWithTokenW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProcessWithTokenW(QEMU_G2H(c->token), c->logon_flags, QEMU_G2H(c->application_name), QEMU_G2H(c->command_line), c->creation_flags, QEMU_G2H(c->environment), QEMU_G2H(c->current_directory), QEMU_G2H(c->startup_info), QEMU_G2H(c->process_information));
}

#endif

struct qemu_DuplicateTokenEx
{
    struct qemu_syscall super;
    uint64_t ExistingTokenHandle;
    uint64_t dwDesiredAccess;
    uint64_t lpTokenAttributes;
    uint64_t ImpersonationLevel;
    uint64_t TokenType;
    uint64_t DuplicateTokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DuplicateTokenEx(HANDLE ExistingTokenHandle, DWORD dwDesiredAccess, LPSECURITY_ATTRIBUTES lpTokenAttributes, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, TOKEN_TYPE TokenType, PHANDLE DuplicateTokenHandle)
{
    struct qemu_DuplicateTokenEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DUPLICATETOKENEX);
    call.ExistingTokenHandle = (uint64_t)ExistingTokenHandle;
    call.dwDesiredAccess = (uint64_t)dwDesiredAccess;
    call.lpTokenAttributes = (uint64_t)lpTokenAttributes;
    call.ImpersonationLevel = (uint64_t)ImpersonationLevel;
    call.TokenType = (uint64_t)TokenType;
    call.DuplicateTokenHandle = (uint64_t)DuplicateTokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DuplicateTokenEx(struct qemu_syscall *call)
{
    struct qemu_DuplicateTokenEx *c = (struct qemu_DuplicateTokenEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DuplicateTokenEx(QEMU_G2H(c->ExistingTokenHandle), c->dwDesiredAccess, QEMU_G2H(c->lpTokenAttributes), c->ImpersonationLevel, c->TokenType, QEMU_G2H(c->DuplicateTokenHandle));
}

#endif

struct qemu_DuplicateToken
{
    struct qemu_syscall super;
    uint64_t ExistingTokenHandle;
    uint64_t ImpersonationLevel;
    uint64_t DuplicateTokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DuplicateToken(HANDLE ExistingTokenHandle, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, PHANDLE DuplicateTokenHandle)
{
    struct qemu_DuplicateToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DUPLICATETOKEN);
    call.ExistingTokenHandle = (uint64_t)ExistingTokenHandle;
    call.ImpersonationLevel = (uint64_t)ImpersonationLevel;
    call.DuplicateTokenHandle = (uint64_t)DuplicateTokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DuplicateToken(struct qemu_syscall *call)
{
    struct qemu_DuplicateToken *c = (struct qemu_DuplicateToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DuplicateToken(QEMU_G2H(c->ExistingTokenHandle), c->ImpersonationLevel, QEMU_G2H(c->DuplicateTokenHandle));
}

#endif

struct qemu_GetNamedSecurityInfoA
{
    struct qemu_syscall super;
    uint64_t pObjectName;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t ppsidOwner;
    uint64_t ppsidGroup;
    uint64_t ppDacl;
    uint64_t ppSacl;
    uint64_t ppSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNamedSecurityInfoA(LPCSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID* ppsidOwner, PSID* ppsidGroup, PACL* ppDacl, PACL* ppSacl, PSECURITY_DESCRIPTOR* ppSecurityDescriptor)
{
    struct qemu_GetNamedSecurityInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDSECURITYINFOA);
    call.pObjectName = (uint64_t)pObjectName;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.ppsidOwner = (uint64_t)ppsidOwner;
    call.ppsidGroup = (uint64_t)ppsidGroup;
    call.ppDacl = (uint64_t)ppDacl;
    call.ppSacl = (uint64_t)ppSacl;
    call.ppSecurityDescriptor = (uint64_t)ppSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedSecurityInfoA(struct qemu_syscall *call)
{
    struct qemu_GetNamedSecurityInfoA *c = (struct qemu_GetNamedSecurityInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedSecurityInfoA(QEMU_G2H(c->pObjectName), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->ppsidOwner), QEMU_G2H(c->ppsidGroup), QEMU_G2H(c->ppDacl), QEMU_G2H(c->ppSacl), QEMU_G2H(c->ppSecurityDescriptor));
}

#endif

struct qemu_GetNamedSecurityInfoW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t type;
    uint64_t info;
    uint64_t owner;
    uint64_t group;
    uint64_t dacl;
    uint64_t sacl;
    uint64_t descriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNamedSecurityInfoW(LPCWSTR name, SE_OBJECT_TYPE type, SECURITY_INFORMATION info, PSID* owner, PSID* group, PACL* dacl, PACL* sacl, PSECURITY_DESCRIPTOR* descriptor)
{
    struct qemu_GetNamedSecurityInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDSECURITYINFOW);
    call.name = (uint64_t)name;
    call.type = (uint64_t)type;
    call.info = (uint64_t)info;
    call.owner = (uint64_t)owner;
    call.group = (uint64_t)group;
    call.dacl = (uint64_t)dacl;
    call.sacl = (uint64_t)sacl;
    call.descriptor = (uint64_t)descriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNamedSecurityInfoW(struct qemu_syscall *call)
{
    struct qemu_GetNamedSecurityInfoW *c = (struct qemu_GetNamedSecurityInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedSecurityInfoW(QEMU_G2H(c->name), c->type, c->info, QEMU_G2H(c->owner), QEMU_G2H(c->group), QEMU_G2H(c->dacl), QEMU_G2H(c->sacl), QEMU_G2H(c->descriptor));
}

#endif

struct qemu_GetNamedSecurityInfoExW
{
    struct qemu_syscall super;
    uint64_t object;
    uint64_t type;
    uint64_t info;
    uint64_t provider;
    uint64_t property;
    uint64_t access_list;
    uint64_t audit_list;
    uint64_t owner;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNamedSecurityInfoExW(LPCWSTR object, SE_OBJECT_TYPE type, SECURITY_INFORMATION info, LPCWSTR provider, LPCWSTR property, PACTRL_ACCESSW* access_list, PACTRL_AUDITW* audit_list, LPWSTR* owner, LPWSTR* group)
{
    struct qemu_GetNamedSecurityInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDSECURITYINFOEXW);
    call.object = (uint64_t)object;
    call.type = (uint64_t)type;
    call.info = (uint64_t)info;
    call.provider = (uint64_t)provider;
    call.property = (uint64_t)property;
    call.access_list = (uint64_t)access_list;
    call.audit_list = (uint64_t)audit_list;
    call.owner = (uint64_t)owner;
    call.group = (uint64_t)group;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNamedSecurityInfoExW to Wine headers? */
extern DWORD WINAPI GetNamedSecurityInfoExW(LPCWSTR object, SE_OBJECT_TYPE type, SECURITY_INFORMATION info, LPCWSTR provider, LPCWSTR property, PACTRL_ACCESSW* access_list, PACTRL_AUDITW* audit_list, LPWSTR* owner, LPWSTR* group);
void qemu_GetNamedSecurityInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetNamedSecurityInfoExW *c = (struct qemu_GetNamedSecurityInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedSecurityInfoExW(QEMU_G2H(c->object), c->type, c->info, QEMU_G2H(c->provider), QEMU_G2H(c->property), QEMU_G2H(c->access_list), QEMU_G2H(c->audit_list), QEMU_G2H(c->owner), QEMU_G2H(c->group));
}

#endif

struct qemu_GetNamedSecurityInfoExA
{
    struct qemu_syscall super;
    uint64_t object;
    uint64_t type;
    uint64_t info;
    uint64_t provider;
    uint64_t property;
    uint64_t access_list;
    uint64_t audit_list;
    uint64_t owner;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetNamedSecurityInfoExA(LPCSTR object, SE_OBJECT_TYPE type, SECURITY_INFORMATION info, LPCSTR provider, LPCSTR property, PACTRL_ACCESSA* access_list, PACTRL_AUDITA* audit_list, LPSTR* owner, LPSTR* group)
{
    struct qemu_GetNamedSecurityInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEDSECURITYINFOEXA);
    call.object = (uint64_t)object;
    call.type = (uint64_t)type;
    call.info = (uint64_t)info;
    call.provider = (uint64_t)provider;
    call.property = (uint64_t)property;
    call.access_list = (uint64_t)access_list;
    call.audit_list = (uint64_t)audit_list;
    call.owner = (uint64_t)owner;
    call.group = (uint64_t)group;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNamedSecurityInfoExA to Wine headers? */
extern DWORD WINAPI GetNamedSecurityInfoExA(LPCSTR object, SE_OBJECT_TYPE type, SECURITY_INFORMATION info, LPCSTR provider, LPCSTR property, PACTRL_ACCESSA* access_list, PACTRL_AUDITA* audit_list, LPSTR* owner, LPSTR* group);
void qemu_GetNamedSecurityInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetNamedSecurityInfoExA *c = (struct qemu_GetNamedSecurityInfoExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNamedSecurityInfoExA(QEMU_G2H(c->object), c->type, c->info, QEMU_G2H(c->provider), QEMU_G2H(c->property), QEMU_G2H(c->access_list), QEMU_G2H(c->audit_list), QEMU_G2H(c->owner), QEMU_G2H(c->group));
}

#endif

struct qemu_DecryptFileW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DecryptFileW(LPCWSTR lpFileName, DWORD dwReserved)
{
    struct qemu_DecryptFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DECRYPTFILEW);
    call.lpFileName = (uint64_t)lpFileName;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DecryptFileW(struct qemu_syscall *call)
{
    struct qemu_DecryptFileW *c = (struct qemu_DecryptFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DecryptFileW(QEMU_G2H(c->lpFileName), c->dwReserved);
}

#endif

struct qemu_DecryptFileA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DecryptFileA(LPCSTR lpFileName, DWORD dwReserved)
{
    struct qemu_DecryptFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DECRYPTFILEA);
    call.lpFileName = (uint64_t)lpFileName;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DecryptFileA(struct qemu_syscall *call)
{
    struct qemu_DecryptFileA *c = (struct qemu_DecryptFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DecryptFileA(QEMU_G2H(c->lpFileName), c->dwReserved);
}

#endif

struct qemu_EncryptFileW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EncryptFileW(LPCWSTR lpFileName)
{
    struct qemu_EncryptFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENCRYPTFILEW);
    call.lpFileName = (uint64_t)lpFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EncryptFileW(struct qemu_syscall *call)
{
    struct qemu_EncryptFileW *c = (struct qemu_EncryptFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EncryptFileW(QEMU_G2H(c->lpFileName));
}

#endif

struct qemu_EncryptFileA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EncryptFileA(LPCSTR lpFileName)
{
    struct qemu_EncryptFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENCRYPTFILEA);
    call.lpFileName = (uint64_t)lpFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EncryptFileA(struct qemu_syscall *call)
{
    struct qemu_EncryptFileA *c = (struct qemu_EncryptFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EncryptFileA(QEMU_G2H(c->lpFileName));
}

#endif

struct qemu_FileEncryptionStatusW
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t lpStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileEncryptionStatusW(LPCWSTR lpFileName, LPDWORD lpStatus)
{
    struct qemu_FileEncryptionStatusW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEENCRYPTIONSTATUSW);
    call.lpFileName = (uint64_t)lpFileName;
    call.lpStatus = (uint64_t)lpStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileEncryptionStatusW(struct qemu_syscall *call)
{
    struct qemu_FileEncryptionStatusW *c = (struct qemu_FileEncryptionStatusW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileEncryptionStatusW(QEMU_G2H(c->lpFileName), QEMU_G2H(c->lpStatus));
}

#endif

struct qemu_FileEncryptionStatusA
{
    struct qemu_syscall super;
    uint64_t lpFileName;
    uint64_t lpStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileEncryptionStatusA(LPCSTR lpFileName, LPDWORD lpStatus)
{
    struct qemu_FileEncryptionStatusA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEENCRYPTIONSTATUSA);
    call.lpFileName = (uint64_t)lpFileName;
    call.lpStatus = (uint64_t)lpStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileEncryptionStatusA(struct qemu_syscall *call)
{
    struct qemu_FileEncryptionStatusA *c = (struct qemu_FileEncryptionStatusA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileEncryptionStatusA(QEMU_G2H(c->lpFileName), QEMU_G2H(c->lpStatus));
}

#endif

struct qemu_SetSecurityInfo
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t psidOwner;
    uint64_t psidGroup;
    uint64_t pDacl;
    uint64_t pSacl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetSecurityInfo(HANDLE handle, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID psidOwner, PSID psidGroup, PACL pDacl, PACL pSacl)
{
    struct qemu_SetSecurityInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSECURITYINFO);
    call.handle = (uint64_t)handle;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.psidOwner = (uint64_t)psidOwner;
    call.psidGroup = (uint64_t)psidGroup;
    call.pDacl = (uint64_t)pDacl;
    call.pSacl = (uint64_t)pSacl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSecurityInfo(struct qemu_syscall *call)
{
    struct qemu_SetSecurityInfo *c = (struct qemu_SetSecurityInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSecurityInfo(QEMU_G2H(c->handle), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->psidOwner), QEMU_G2H(c->psidGroup), QEMU_G2H(c->pDacl), QEMU_G2H(c->pSacl));
}

#endif

struct qemu_SaferCreateLevel
{
    struct qemu_syscall super;
    uint64_t ScopeId;
    uint64_t LevelId;
    uint64_t OpenFlags;
    uint64_t LevelHandle;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SaferCreateLevel(DWORD ScopeId, DWORD LevelId, DWORD OpenFlags, SAFER_LEVEL_HANDLE* LevelHandle, LPVOID lpReserved)
{
    struct qemu_SaferCreateLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SAFERCREATELEVEL);
    call.ScopeId = (uint64_t)ScopeId;
    call.LevelId = (uint64_t)LevelId;
    call.OpenFlags = (uint64_t)OpenFlags;
    call.LevelHandle = (uint64_t)LevelHandle;
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SaferCreateLevel(struct qemu_syscall *call)
{
    struct qemu_SaferCreateLevel *c = (struct qemu_SaferCreateLevel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SaferCreateLevel(c->ScopeId, c->LevelId, c->OpenFlags, QEMU_G2H(c->LevelHandle), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SaferComputeTokenFromLevel
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t token;
    uint64_t access_token;
    uint64_t flags;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SaferComputeTokenFromLevel(SAFER_LEVEL_HANDLE handle, HANDLE token, PHANDLE access_token, DWORD flags, LPVOID reserved)
{
    struct qemu_SaferComputeTokenFromLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SAFERCOMPUTETOKENFROMLEVEL);
    call.handle = (uint64_t)handle;
    call.token = (uint64_t)token;
    call.access_token = (uint64_t)access_token;
    call.flags = (uint64_t)flags;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SaferComputeTokenFromLevel to Wine headers? */
extern BOOL WINAPI SaferComputeTokenFromLevel(SAFER_LEVEL_HANDLE handle, HANDLE token, PHANDLE access_token, DWORD flags, LPVOID reserved);
void qemu_SaferComputeTokenFromLevel(struct qemu_syscall *call)
{
    struct qemu_SaferComputeTokenFromLevel *c = (struct qemu_SaferComputeTokenFromLevel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SaferComputeTokenFromLevel(QEMU_G2H(c->handle), QEMU_G2H(c->token), QEMU_G2H(c->access_token), c->flags, QEMU_G2H(c->reserved));
}

#endif

struct qemu_SaferCloseLevel
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SaferCloseLevel(SAFER_LEVEL_HANDLE handle)
{
    struct qemu_SaferCloseLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SAFERCLOSELEVEL);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SaferCloseLevel to Wine headers? */
extern BOOL WINAPI SaferCloseLevel(SAFER_LEVEL_HANDLE handle);
void qemu_SaferCloseLevel(struct qemu_syscall *call)
{
    struct qemu_SaferCloseLevel *c = (struct qemu_SaferCloseLevel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SaferCloseLevel(QEMU_G2H(c->handle));
}

#endif

struct qemu_TreeResetNamedSecurityInfoW
{
    struct qemu_syscall super;
    uint64_t pObjectName;
    uint64_t ObjectType;
    uint64_t SecurityInfo;
    uint64_t pOwner;
    uint64_t pGroup;
    uint64_t pDacl;
    uint64_t pSacl;
    uint64_t KeepExplicit;
    uint64_t fnProgress;
    uint64_t ProgressInvokeSetting;
    uint64_t Args;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI TreeResetNamedSecurityInfoW(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID pOwner, PSID pGroup, PACL pDacl, PACL pSacl, BOOL KeepExplicit, FN_PROGRESS fnProgress, PROG_INVOKE_SETTING ProgressInvokeSetting, PVOID Args)
{
    struct qemu_TreeResetNamedSecurityInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TREERESETNAMEDSECURITYINFOW);
    call.pObjectName = (uint64_t)pObjectName;
    call.ObjectType = (uint64_t)ObjectType;
    call.SecurityInfo = (uint64_t)SecurityInfo;
    call.pOwner = (uint64_t)pOwner;
    call.pGroup = (uint64_t)pGroup;
    call.pDacl = (uint64_t)pDacl;
    call.pSacl = (uint64_t)pSacl;
    call.KeepExplicit = (uint64_t)KeepExplicit;
    call.fnProgress = (uint64_t)fnProgress;
    call.ProgressInvokeSetting = (uint64_t)ProgressInvokeSetting;
    call.Args = (uint64_t)Args;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add TreeResetNamedSecurityInfoW to Wine headers? */
extern DWORD WINAPI TreeResetNamedSecurityInfoW(LPWSTR pObjectName, SE_OBJECT_TYPE ObjectType, SECURITY_INFORMATION SecurityInfo, PSID pOwner, PSID pGroup, PACL pDacl, PACL pSacl, BOOL KeepExplicit, FN_PROGRESS fnProgress, PROG_INVOKE_SETTING ProgressInvokeSetting, PVOID Args);
void qemu_TreeResetNamedSecurityInfoW(struct qemu_syscall *call)
{
    struct qemu_TreeResetNamedSecurityInfoW *c = (struct qemu_TreeResetNamedSecurityInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TreeResetNamedSecurityInfoW(QEMU_G2H(c->pObjectName), c->ObjectType, c->SecurityInfo, QEMU_G2H(c->pOwner), QEMU_G2H(c->pGroup), QEMU_G2H(c->pDacl), QEMU_G2H(c->pSacl), c->KeepExplicit, QEMU_G2H(c->fnProgress), c->ProgressInvokeSetting, QEMU_G2H(c->Args));
}

#endif

struct qemu_SaferGetPolicyInformation
{
    struct qemu_syscall super;
    uint64_t scope;
    uint64_t class;
    uint64_t size;
    uint64_t buffer;
    uint64_t required;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SaferGetPolicyInformation(DWORD scope, SAFER_POLICY_INFO_CLASS class, DWORD size, PVOID buffer, PDWORD required, LPVOID lpReserved)
{
    struct qemu_SaferGetPolicyInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SAFERGETPOLICYINFORMATION);
    call.scope = (uint64_t)scope;
    call.class = (uint64_t)class;
    call.size = (uint64_t)size;
    call.buffer = (uint64_t)buffer;
    call.required = (uint64_t)required;
    call.lpReserved = (uint64_t)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SaferGetPolicyInformation(struct qemu_syscall *call)
{
    struct qemu_SaferGetPolicyInformation *c = (struct qemu_SaferGetPolicyInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SaferGetPolicyInformation(c->scope, c->class, c->size, QEMU_G2H(c->buffer), QEMU_G2H(c->required), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SaferSetLevelInformation
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t infotype;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SaferSetLevelInformation(SAFER_LEVEL_HANDLE handle, SAFER_OBJECT_INFO_CLASS infotype, LPVOID buffer, DWORD size)
{
    struct qemu_SaferSetLevelInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SAFERSETLEVELINFORMATION);
    call.handle = (uint64_t)handle;
    call.infotype = (uint64_t)infotype;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SaferSetLevelInformation(struct qemu_syscall *call)
{
    struct qemu_SaferSetLevelInformation *c = (struct qemu_SaferSetLevelInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SaferSetLevelInformation(QEMU_G2H(c->handle), c->infotype, QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_LookupSecurityDescriptorPartsA
{
    struct qemu_syscall super;
    uint64_t owner;
    uint64_t group;
    uint64_t access_count;
    uint64_t access_list;
    uint64_t audit_count;
    uint64_t audit_list;
    uint64_t descriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI LookupSecurityDescriptorPartsA(PTRUSTEE_A *owner, PTRUSTEE_A *group, PULONG access_count, PEXPLICIT_ACCESS_A *access_list, PULONG audit_count, PEXPLICIT_ACCESS_A *audit_list, PSECURITY_DESCRIPTOR descriptor)
{
    struct qemu_LookupSecurityDescriptorPartsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPSECURITYDESCRIPTORPARTSA);
    call.owner = (uint64_t)owner;
    call.group = (uint64_t)group;
    call.access_count = (uint64_t)access_count;
    call.access_list = (uint64_t)access_list;
    call.audit_count = (uint64_t)audit_count;
    call.audit_list = (uint64_t)audit_list;
    call.descriptor = (uint64_t)descriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LookupSecurityDescriptorPartsA to Wine headers? */
extern DWORD WINAPI LookupSecurityDescriptorPartsA(TRUSTEEA *owner, TRUSTEEA *group, ULONG *access_count, EXPLICIT_ACCESSA *access_list, ULONG *audit_count, EXPLICIT_ACCESSA *audit_list, SECURITY_DESCRIPTOR *descriptor);
void qemu_LookupSecurityDescriptorPartsA(struct qemu_syscall *call)
{
    struct qemu_LookupSecurityDescriptorPartsA *c = (struct qemu_LookupSecurityDescriptorPartsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupSecurityDescriptorPartsA(QEMU_G2H(c->owner), QEMU_G2H(c->group), QEMU_G2H(c->access_count), QEMU_G2H(c->access_list), QEMU_G2H(c->audit_count), QEMU_G2H(c->audit_list), QEMU_G2H(c->descriptor));
}

#endif

struct qemu_LookupSecurityDescriptorPartsW
{
    struct qemu_syscall super;
    uint64_t owner;
    uint64_t group;
    uint64_t access_count;
    uint64_t access_list;
    uint64_t audit_count;
    uint64_t audit_list;
    uint64_t descriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI LookupSecurityDescriptorPartsW(PTRUSTEE_W *owner, PTRUSTEE_W *group, PULONG access_count, PEXPLICIT_ACCESS_W *access_list, PULONG audit_count, PEXPLICIT_ACCESS_W *audit_list, PSECURITY_DESCRIPTOR descriptor)
{
    struct qemu_LookupSecurityDescriptorPartsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOOKUPSECURITYDESCRIPTORPARTSW);
    call.owner = (uint64_t)owner;
    call.group = (uint64_t)group;
    call.access_count = (uint64_t)access_count;
    call.access_list = (uint64_t)access_list;
    call.audit_count = (uint64_t)audit_count;
    call.audit_list = (uint64_t)audit_list;
    call.descriptor = (uint64_t)descriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LookupSecurityDescriptorPartsW to Wine headers? */
extern DWORD WINAPI LookupSecurityDescriptorPartsW(TRUSTEEW *owner, TRUSTEEW *group, ULONG *access_count, EXPLICIT_ACCESSW *access_list, ULONG *audit_count, EXPLICIT_ACCESSW *audit_list, SECURITY_DESCRIPTOR *descriptor);
void qemu_LookupSecurityDescriptorPartsW(struct qemu_syscall *call)
{
    struct qemu_LookupSecurityDescriptorPartsW *c = (struct qemu_LookupSecurityDescriptorPartsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LookupSecurityDescriptorPartsW(QEMU_G2H(c->owner), QEMU_G2H(c->group), QEMU_G2H(c->access_count), QEMU_G2H(c->access_list), QEMU_G2H(c->audit_count), QEMU_G2H(c->audit_list), QEMU_G2H(c->descriptor));
}

#endif

