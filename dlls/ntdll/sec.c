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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_RtlAllocateAndInitializeSid
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

WINBASEAPI NTSTATUS WINAPI RtlAllocateAndInitializeSid (PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7, PSID *pSid)
{
    struct qemu_RtlAllocateAndInitializeSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLALLOCATEANDINITIALIZESID);
    call.pIdentifierAuthority = (ULONG_PTR)pIdentifierAuthority;
    call.nSubAuthorityCount = nSubAuthorityCount;
    call.nSubAuthority0 = nSubAuthority0;
    call.nSubAuthority1 = nSubAuthority1;
    call.nSubAuthority2 = nSubAuthority2;
    call.nSubAuthority3 = nSubAuthority3;
    call.nSubAuthority4 = nSubAuthority4;
    call.nSubAuthority5 = nSubAuthority5;
    call.nSubAuthority6 = nSubAuthority6;
    call.nSubAuthority7 = nSubAuthority7;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAllocateAndInitializeSid(struct qemu_syscall *call)
{
    struct qemu_RtlAllocateAndInitializeSid *c = (struct qemu_RtlAllocateAndInitializeSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAllocateAndInitializeSid(QEMU_G2H(c->pIdentifierAuthority), c->nSubAuthorityCount, c->nSubAuthority0, c->nSubAuthority1, c->nSubAuthority2, c->nSubAuthority3, c->nSubAuthority4, c->nSubAuthority5, c->nSubAuthority6, c->nSubAuthority7, QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlEqualSid
{
    struct qemu_syscall super;
    uint64_t pSid1;
    uint64_t pSid2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlEqualSid(PSID pSid1, PSID pSid2)
{
    struct qemu_RtlEqualSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALSID);
    call.pSid1 = (ULONG_PTR)pSid1;
    call.pSid2 = (ULONG_PTR)pSid2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualSid(struct qemu_syscall *call)
{
    struct qemu_RtlEqualSid *c = (struct qemu_RtlEqualSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualSid(QEMU_G2H(c->pSid1), QEMU_G2H(c->pSid2));
}

#endif

struct qemu_RtlEqualPrefixSid
{
    struct qemu_syscall super;
    uint64_t pSid1;
    uint64_t pSid2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlEqualPrefixSid (PSID pSid1, PSID pSid2)
{
    struct qemu_RtlEqualPrefixSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALPREFIXSID);
    call.pSid1 = (ULONG_PTR)pSid1;
    call.pSid2 = (ULONG_PTR)pSid2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualPrefixSid(struct qemu_syscall *call)
{
    struct qemu_RtlEqualPrefixSid *c = (struct qemu_RtlEqualPrefixSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualPrefixSid(QEMU_G2H(c->pSid1), QEMU_G2H(c->pSid2));
}

#endif

struct qemu_RtlFreeSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlFreeSid(PSID pSid)
{
    struct qemu_RtlFreeSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREESID);
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFreeSid(struct qemu_syscall *call)
{
    struct qemu_RtlFreeSid *c = (struct qemu_RtlFreeSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFreeSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlLengthRequiredSid
{
    struct qemu_syscall super;
    uint64_t nrofsubauths;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlLengthRequiredSid(DWORD nrofsubauths)
{
    struct qemu_RtlLengthRequiredSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLENGTHREQUIREDSID);
    call.nrofsubauths = nrofsubauths;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLengthRequiredSid(struct qemu_syscall *call)
{
    struct qemu_RtlLengthRequiredSid *c = (struct qemu_RtlLengthRequiredSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlLengthRequiredSid(c->nrofsubauths);
}

#endif

struct qemu_RtlLengthSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlLengthSid(PSID pSid)
{
    struct qemu_RtlLengthSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLENGTHSID);
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLengthSid(struct qemu_syscall *call)
{
    struct qemu_RtlLengthSid *c = (struct qemu_RtlLengthSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlLengthSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlInitializeSid
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t pIdentifierAuthority;
    uint64_t nSubAuthorityCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlInitializeSid(PSID pSid, PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount)
{
    struct qemu_RtlInitializeSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZESID);
    call.pSid = (ULONG_PTR)pSid;
    call.pIdentifierAuthority = (ULONG_PTR)pIdentifierAuthority;
    call.nSubAuthorityCount = nSubAuthorityCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitializeSid(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeSid *c = (struct qemu_RtlInitializeSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlInitializeSid(QEMU_G2H(c->pSid), QEMU_G2H(c->pIdentifierAuthority), c->nSubAuthorityCount);
}

#endif

struct qemu_RtlSubAuthoritySid
{
    struct qemu_syscall super;
    uint64_t pSid;
    uint64_t nSubAuthority;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPDWORD WINAPI RtlSubAuthoritySid(PSID pSid, DWORD nSubAuthority)
{
    struct qemu_RtlSubAuthoritySid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSUBAUTHORITYSID);
    call.pSid = (ULONG_PTR)pSid;
    call.nSubAuthority = nSubAuthority;

    qemu_syscall(&call.super);

    return (LPDWORD)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlSubAuthoritySid(struct qemu_syscall *call)
{
    struct qemu_RtlSubAuthoritySid *c = (struct qemu_RtlSubAuthoritySid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RtlSubAuthoritySid(QEMU_G2H(c->pSid), c->nSubAuthority);
}

#endif

struct qemu_RtlIdentifierAuthoritySid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PSID_IDENTIFIER_AUTHORITY WINAPI RtlIdentifierAuthoritySid(PSID pSid)
{
    struct qemu_RtlIdentifierAuthoritySid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIDENTIFIERAUTHORITYSID);
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return (PSID_IDENTIFIER_AUTHORITY)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlIdentifierAuthoritySid(struct qemu_syscall *call)
{
    struct qemu_RtlIdentifierAuthoritySid *c = (struct qemu_RtlIdentifierAuthoritySid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(RtlIdentifierAuthoritySid(QEMU_G2H(c->pSid)));
}

#endif

struct qemu_RtlSubAuthorityCountSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPBYTE WINAPI RtlSubAuthorityCountSid(PSID pSid)
{
    struct qemu_RtlSubAuthorityCountSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSUBAUTHORITYCOUNTSID);
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return (LPBYTE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlSubAuthorityCountSid(struct qemu_syscall *call)
{
    struct qemu_RtlSubAuthorityCountSid *c = (struct qemu_RtlSubAuthorityCountSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RtlSubAuthorityCountSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlCopySid
{
    struct qemu_syscall super;
    uint64_t nDestinationSidLength;
    uint64_t pDestinationSid;
    uint64_t pSourceSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlCopySid(DWORD nDestinationSidLength, PSID pDestinationSid, PSID pSourceSid)
{
    struct qemu_RtlCopySid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYSID);
    call.nDestinationSidLength = nDestinationSidLength;
    call.pDestinationSid = (ULONG_PTR)pDestinationSid;
    call.pSourceSid = (ULONG_PTR)pSourceSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCopySid(struct qemu_syscall *call)
{
    struct qemu_RtlCopySid *c = (struct qemu_RtlCopySid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCopySid(c->nDestinationSidLength, QEMU_G2H(c->pDestinationSid), QEMU_G2H(c->pSourceSid));
}

#endif

struct qemu_RtlValidSid
{
    struct qemu_syscall super;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlValidSid(PSID pSid)
{
    struct qemu_RtlValidSid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLVALIDSID);
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlValidSid(struct qemu_syscall *call)
{
    struct qemu_RtlValidSid *c = (struct qemu_RtlValidSid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlValidSid(QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlCreateSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t lpsd;
    uint64_t rev;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateSecurityDescriptor(PSECURITY_DESCRIPTOR lpsd, DWORD rev)
{
    struct qemu_RtlCreateSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATESECURITYDESCRIPTOR);
    call.lpsd = (ULONG_PTR)lpsd;
    call.rev = rev;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlCreateSecurityDescriptor *c = (struct qemu_RtlCreateSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateSecurityDescriptor(QEMU_G2H(c->lpsd), c->rev);
}

#endif

struct qemu_RtlCopySecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSourceSD;
    uint64_t pDestinationSD;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCopySecurityDescriptor(PSECURITY_DESCRIPTOR pSourceSD, PSECURITY_DESCRIPTOR pDestinationSD)
{
    struct qemu_RtlCopySecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYSECURITYDESCRIPTOR);
    call.pSourceSD = (ULONG_PTR)pSourceSD;
    call.pDestinationSD = (ULONG_PTR)pDestinationSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCopySecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlCopySecurityDescriptor *c = (struct qemu_RtlCopySecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCopySecurityDescriptor(QEMU_G2H(c->pSourceSD), QEMU_G2H(c->pDestinationSD));
}

#endif

struct qemu_RtlValidSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlValidSecurityDescriptor(PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    struct qemu_RtlValidSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLVALIDSECURITYDESCRIPTOR);
    call.SecurityDescriptor = (ULONG_PTR)SecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlValidSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlValidSecurityDescriptor *c = (struct qemu_RtlValidSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlValidSecurityDescriptor(QEMU_G2H(c->SecurityDescriptor));
}

#endif

struct qemu_RtlValidRelativeSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t descriptor;
    uint64_t length;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlValidRelativeSecurityDescriptor(PSECURITY_DESCRIPTOR descriptor, ULONG length, SECURITY_INFORMATION info)
{
    struct qemu_RtlValidRelativeSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLVALIDRELATIVESECURITYDESCRIPTOR);
    call.descriptor = (ULONG_PTR)descriptor;
    call.length = length;
    call.info = info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlValidRelativeSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlValidRelativeSecurityDescriptor *c = (struct qemu_RtlValidRelativeSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlValidRelativeSecurityDescriptor(QEMU_G2H(c->descriptor), c->length, c->info);
}

#endif

struct qemu_RtlLengthSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlLengthSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor)
{
    struct qemu_RtlLengthSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLENGTHSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLengthSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlLengthSecurityDescriptor *c = (struct qemu_RtlLengthSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlLengthSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor));
}

#endif

struct qemu_RtlGetDaclSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t lpbDaclPresent;
    uint64_t pDacl;
    uint64_t lpbDaclDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetDaclSecurityDescriptor(IN PSECURITY_DESCRIPTOR pSecurityDescriptor, OUT PBOOLEAN lpbDaclPresent, OUT PACL *pDacl, OUT PBOOLEAN lpbDaclDefaulted)
{
    struct qemu_RtlGetDaclSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETDACLSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.lpbDaclPresent = (ULONG_PTR)lpbDaclPresent;
    call.pDacl = (ULONG_PTR)pDacl;
    call.lpbDaclDefaulted = (ULONG_PTR)lpbDaclDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetDaclSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlGetDaclSecurityDescriptor *c = (struct qemu_RtlGetDaclSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetDaclSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->lpbDaclPresent), QEMU_G2H(c->pDacl), QEMU_G2H(c->lpbDaclDefaulted));
}

#endif

struct qemu_RtlSetDaclSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t daclpresent;
    uint64_t dacl;
    uint64_t dacldefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetDaclSecurityDescriptor (PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOLEAN daclpresent, PACL dacl, BOOLEAN dacldefaulted)
{
    struct qemu_RtlSetDaclSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETDACLSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.daclpresent = daclpresent;
    call.dacl = (ULONG_PTR)dacl;
    call.dacldefaulted = dacldefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetDaclSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlSetDaclSecurityDescriptor *c = (struct qemu_RtlSetDaclSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetDaclSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), c->daclpresent, QEMU_G2H(c->dacl), c->dacldefaulted);
}

#endif

struct qemu_RtlGetSaclSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t lpbSaclPresent;
    uint64_t pSacl;
    uint64_t lpbSaclDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetSaclSecurityDescriptor(IN PSECURITY_DESCRIPTOR pSecurityDescriptor, OUT PBOOLEAN lpbSaclPresent, OUT PACL *pSacl, OUT PBOOLEAN lpbSaclDefaulted)
{
    struct qemu_RtlGetSaclSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETSACLSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.lpbSaclPresent = (ULONG_PTR)lpbSaclPresent;
    call.pSacl = (ULONG_PTR)pSacl;
    call.lpbSaclDefaulted = (ULONG_PTR)lpbSaclDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetSaclSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlGetSaclSecurityDescriptor *c = (struct qemu_RtlGetSaclSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetSaclSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->lpbSaclPresent), QEMU_G2H(c->pSacl), QEMU_G2H(c->lpbSaclDefaulted));
}

#endif

struct qemu_RtlSetSaclSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t saclpresent;
    uint64_t sacl;
    uint64_t sacldefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetSaclSecurityDescriptor (PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOLEAN saclpresent, PACL sacl, BOOLEAN sacldefaulted)
{
    struct qemu_RtlSetSaclSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETSACLSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.saclpresent = saclpresent;
    call.sacl = (ULONG_PTR)sacl;
    call.sacldefaulted = sacldefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetSaclSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlSetSaclSecurityDescriptor *c = (struct qemu_RtlSetSaclSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetSaclSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), c->saclpresent, QEMU_G2H(c->sacl), c->sacldefaulted);
}

#endif

struct qemu_RtlGetOwnerSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t Owner;
    uint64_t OwnerDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetOwnerSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID *Owner, PBOOLEAN OwnerDefaulted)
{
    struct qemu_RtlGetOwnerSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETOWNERSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.Owner = (ULONG_PTR)Owner;
    call.OwnerDefaulted = (ULONG_PTR)OwnerDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetOwnerSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlGetOwnerSecurityDescriptor *c = (struct qemu_RtlGetOwnerSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetOwnerSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->Owner), QEMU_G2H(c->OwnerDefaulted));
}

#endif

struct qemu_RtlSetOwnerSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t owner;
    uint64_t ownerdefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetOwnerSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID owner, BOOLEAN ownerdefaulted)
{
    struct qemu_RtlSetOwnerSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETOWNERSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.owner = (ULONG_PTR)owner;
    call.ownerdefaulted = ownerdefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetOwnerSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlSetOwnerSecurityDescriptor *c = (struct qemu_RtlSetOwnerSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetOwnerSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->owner), c->ownerdefaulted);
}

#endif

struct qemu_RtlSetGroupSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t group;
    uint64_t groupdefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetGroupSecurityDescriptor (PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID group, BOOLEAN groupdefaulted)
{
    struct qemu_RtlSetGroupSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETGROUPSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.group = (ULONG_PTR)group;
    call.groupdefaulted = (ULONG_PTR)groupdefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetGroupSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlSetGroupSecurityDescriptor *c = (struct qemu_RtlSetGroupSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetGroupSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->group), c->groupdefaulted);
}

#endif

struct qemu_RtlGetGroupSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t Group;
    uint64_t GroupDefaulted;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetGroupSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSID *Group, PBOOLEAN GroupDefaulted)
{
    struct qemu_RtlGetGroupSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETGROUPSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.Group = (ULONG_PTR)Group;
    call.GroupDefaulted = (ULONG_PTR)GroupDefaulted;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetGroupSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlGetGroupSecurityDescriptor *c = (struct qemu_RtlGetGroupSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetGroupSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->Group), QEMU_G2H(c->GroupDefaulted));
}

#endif

struct qemu_RtlMakeSelfRelativeSD
{
    struct qemu_syscall super;
    uint64_t pAbsoluteSecurityDescriptor;
    uint64_t pSelfRelativeSecurityDescriptor;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlMakeSelfRelativeSD(IN PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, IN PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, IN OUT LPDWORD lpdwBufferLength)
{
    struct qemu_RtlMakeSelfRelativeSD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMAKESELFRELATIVESD);
    call.pAbsoluteSecurityDescriptor = (ULONG_PTR)pAbsoluteSecurityDescriptor;
    call.pSelfRelativeSecurityDescriptor = (ULONG_PTR)pSelfRelativeSecurityDescriptor;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlMakeSelfRelativeSD(struct qemu_syscall *call)
{
    struct qemu_RtlMakeSelfRelativeSD *c = (struct qemu_RtlMakeSelfRelativeSD *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlMakeSelfRelativeSD(QEMU_G2H(c->pAbsoluteSecurityDescriptor), QEMU_G2H(c->pSelfRelativeSecurityDescriptor), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_RtlSelfRelativeToAbsoluteSD
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

WINBASEAPI NTSTATUS WINAPI RtlSelfRelativeToAbsoluteSD(IN PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor, OUT PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor, OUT LPDWORD lpdwAbsoluteSecurityDescriptorSize, OUT PACL pDacl, OUT LPDWORD lpdwDaclSize, OUT PACL pSacl, OUT LPDWORD lpdwSaclSize, OUT PSID pOwner, OUT LPDWORD lpdwOwnerSize, OUT PSID pPrimaryGroup, OUT LPDWORD lpdwPrimaryGroupSize)
{
    struct qemu_RtlSelfRelativeToAbsoluteSD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSELFRELATIVETOABSOLUTESD);
    call.pSelfRelativeSecurityDescriptor = (ULONG_PTR)pSelfRelativeSecurityDescriptor;
    call.pAbsoluteSecurityDescriptor = (ULONG_PTR)pAbsoluteSecurityDescriptor;
    call.lpdwAbsoluteSecurityDescriptorSize = (ULONG_PTR)lpdwAbsoluteSecurityDescriptorSize;
    call.pDacl = (ULONG_PTR)pDacl;
    call.lpdwDaclSize = (ULONG_PTR)lpdwDaclSize;
    call.pSacl = (ULONG_PTR)pSacl;
    call.lpdwSaclSize = (ULONG_PTR)lpdwSaclSize;
    call.pOwner = (ULONG_PTR)pOwner;
    call.lpdwOwnerSize = (ULONG_PTR)lpdwOwnerSize;
    call.pPrimaryGroup = (ULONG_PTR)pPrimaryGroup;
    call.lpdwPrimaryGroupSize = (ULONG_PTR)lpdwPrimaryGroupSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSelfRelativeToAbsoluteSD(struct qemu_syscall *call)
{
    struct qemu_RtlSelfRelativeToAbsoluteSD *c = (struct qemu_RtlSelfRelativeToAbsoluteSD *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSelfRelativeToAbsoluteSD(QEMU_G2H(c->pSelfRelativeSecurityDescriptor), QEMU_G2H(c->pAbsoluteSecurityDescriptor), QEMU_G2H(c->lpdwAbsoluteSecurityDescriptorSize), QEMU_G2H(c->pDacl), QEMU_G2H(c->lpdwDaclSize), QEMU_G2H(c->pSacl), QEMU_G2H(c->lpdwSaclSize), QEMU_G2H(c->pOwner), QEMU_G2H(c->lpdwOwnerSize), QEMU_G2H(c->pPrimaryGroup), QEMU_G2H(c->lpdwPrimaryGroupSize));
}

#endif

struct qemu_RtlGetControlSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t pSecurityDescriptor;
    uint64_t pControl;
    uint64_t lpdwRevision;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetControlSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor, PSECURITY_DESCRIPTOR_CONTROL pControl, LPDWORD lpdwRevision)
{
    struct qemu_RtlGetControlSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETCONTROLSECURITYDESCRIPTOR);
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.pControl = (ULONG_PTR)pControl;
    call.lpdwRevision = (ULONG_PTR)lpdwRevision;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetControlSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlGetControlSecurityDescriptor *c = (struct qemu_RtlGetControlSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetControlSecurityDescriptor(QEMU_G2H(c->pSecurityDescriptor), QEMU_G2H(c->pControl), QEMU_G2H(c->lpdwRevision));
}

#endif

struct qemu_RtlSetControlSecurityDescriptor
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t ControlBitsOfInterest;
    uint64_t ControlBitsToSet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetControlSecurityDescriptor(PSECURITY_DESCRIPTOR SecurityDescriptor, SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest, SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet)
{
    struct qemu_RtlSetControlSecurityDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETCONTROLSECURITYDESCRIPTOR);
    call.SecurityDescriptor = (ULONG_PTR)SecurityDescriptor;
    call.ControlBitsOfInterest = ControlBitsOfInterest;
    call.ControlBitsToSet = ControlBitsToSet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetControlSecurityDescriptor(struct qemu_syscall *call)
{
    struct qemu_RtlSetControlSecurityDescriptor *c = (struct qemu_RtlSetControlSecurityDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetControlSecurityDescriptor(QEMU_G2H(c->SecurityDescriptor), c->ControlBitsOfInterest, c->ControlBitsToSet);
}

#endif

struct qemu_RtlAbsoluteToSelfRelativeSD
{
    struct qemu_syscall super;
    uint64_t AbsoluteSecurityDescriptor;
    uint64_t SelfRelativeSecurityDescriptor;
    uint64_t BufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAbsoluteToSelfRelativeSD(PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor, PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor, PULONG BufferLength)
{
    struct qemu_RtlAbsoluteToSelfRelativeSD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLABSOLUTETOSELFRELATIVESD);
    call.AbsoluteSecurityDescriptor = (ULONG_PTR)AbsoluteSecurityDescriptor;
    call.SelfRelativeSecurityDescriptor = (ULONG_PTR)SelfRelativeSecurityDescriptor;
    call.BufferLength = (ULONG_PTR)BufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlConvertToAutoInheritSecurityObject to Wine headers? */
extern NTSTATUS WINAPI RtlAbsoluteToSelfRelativeSD(PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor, PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor, PULONG BufferLength);
void qemu_RtlAbsoluteToSelfRelativeSD(struct qemu_syscall *call)
{
    struct qemu_RtlAbsoluteToSelfRelativeSD *c = (struct qemu_RtlAbsoluteToSelfRelativeSD *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAbsoluteToSelfRelativeSD(QEMU_G2H(c->AbsoluteSecurityDescriptor), QEMU_G2H(c->SelfRelativeSecurityDescriptor), QEMU_G2H(c->BufferLength));
}

#endif

struct qemu_RtlCreateAcl
{
    struct qemu_syscall super;
    uint64_t acl;
    uint64_t size;
    uint64_t rev;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateAcl(PACL acl,DWORD size,DWORD rev)
{
    struct qemu_RtlCreateAcl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEACL);
    call.acl = (ULONG_PTR)acl;
    call.size = size;
    call.rev = rev;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateAcl(struct qemu_syscall *call)
{
    struct qemu_RtlCreateAcl *c = (struct qemu_RtlCreateAcl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateAcl(QEMU_G2H(c->acl), c->size, c->rev);
}

#endif

struct qemu_RtlFirstFreeAce
{
    struct qemu_syscall super;
    uint64_t acl;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlFirstFreeAce(PACL acl, PACE_HEADER *x)
{
    struct qemu_RtlFirstFreeAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFIRSTFREEACE);
    call.acl = (ULONG_PTR)acl;
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFirstFreeAce(struct qemu_syscall *call)
{
    struct qemu_RtlFirstFreeAce *c = (struct qemu_RtlFirstFreeAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFirstFreeAce(QEMU_G2H(c->acl), QEMU_G2H(c->x));
}

#endif

struct qemu_RtlAddAce
{
    struct qemu_syscall super;
    uint64_t acl;
    uint64_t rev;
    uint64_t xnrofaces;
    uint64_t acestart;
    uint64_t acelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAddAce(PACL acl, DWORD rev, DWORD xnrofaces, PACE_HEADER acestart, DWORD acelen)
{
    struct qemu_RtlAddAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACE);
    call.acl = (ULONG_PTR)acl;
    call.rev = rev;
    call.xnrofaces = xnrofaces;
    call.acestart = (ULONG_PTR)acestart;
    call.acelen = acelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAce *c = (struct qemu_RtlAddAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAce(QEMU_G2H(c->acl), c->rev, c->xnrofaces, QEMU_G2H(c->acestart), c->acelen);
}

#endif

struct qemu_RtlDeleteAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeleteAce(PACL pAcl, DWORD dwAceIndex)
{
    struct qemu_RtlDeleteAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETEACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceIndex = dwAceIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeleteAce(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteAce *c = (struct qemu_RtlDeleteAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDeleteAce(QEMU_G2H(c->pAcl), c->dwAceIndex);
}

#endif

struct qemu_RtlAddAccessAllowedAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAddAccessAllowedAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_RtlAddAccessAllowedAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACCESSALLOWEDACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.AccessMask = AccessMask;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAccessAllowedAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAccessAllowedAce *c = (struct qemu_RtlAddAccessAllowedAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAccessAllowedAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlAddAccessAllowedAceEx
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AceFlags;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAddAccessAllowedAceEx(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AceFlags, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_RtlAddAccessAllowedAceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACCESSALLOWEDACEEX);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.AceFlags = AceFlags;
    call.AccessMask = AccessMask;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAccessAllowedAceEx(struct qemu_syscall *call)
{
    struct qemu_RtlAddAccessAllowedAceEx *c = (struct qemu_RtlAddAccessAllowedAceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAccessAllowedAceEx(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AceFlags, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlAddAccessAllowedObjectAce
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

WINBASEAPI NTSTATUS WINAPI RtlAddAccessAllowedObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid)
{
    struct qemu_RtlAddAccessAllowedObjectAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACCESSALLOWEDOBJECTACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.dwAceFlags = dwAceFlags;
    call.dwAccessMask = dwAccessMask;
    call.pObjectTypeGuid = (ULONG_PTR)pObjectTypeGuid;
    call.pInheritedObjectTypeGuid = (ULONG_PTR)pInheritedObjectTypeGuid;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAccessAllowedObjectAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAccessAllowedObjectAce *c = (struct qemu_RtlAddAccessAllowedObjectAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAccessAllowedObjectAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pObjectTypeGuid), QEMU_G2H(c->pInheritedObjectTypeGuid), QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlAddAccessDeniedAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAddAccessDeniedAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_RtlAddAccessDeniedAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACCESSDENIEDACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.AccessMask = AccessMask;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAccessDeniedAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAccessDeniedAce *c = (struct qemu_RtlAddAccessDeniedAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAccessDeniedAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlAddAccessDeniedAceEx
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t AceFlags;
    uint64_t AccessMask;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAddAccessDeniedAceEx(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD AceFlags, IN DWORD AccessMask, IN PSID pSid)
{
    struct qemu_RtlAddAccessDeniedAceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACCESSDENIEDACEEX);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.AceFlags = AceFlags;
    call.AccessMask = AccessMask;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAccessDeniedAceEx(struct qemu_syscall *call)
{
    struct qemu_RtlAddAccessDeniedAceEx *c = (struct qemu_RtlAddAccessDeniedAceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAccessDeniedAceEx(QEMU_G2H(c->pAcl), c->dwAceRevision, c->AceFlags, c->AccessMask, QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlAddAccessDeniedObjectAce
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

WINBASEAPI NTSTATUS WINAPI RtlAddAccessDeniedObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid)
{
    struct qemu_RtlAddAccessDeniedObjectAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDACCESSDENIEDOBJECTACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.dwAceFlags = dwAceFlags;
    call.dwAccessMask = dwAccessMask;
    call.pObjectTypeGuid = (ULONG_PTR)pObjectTypeGuid;
    call.pInheritedObjectTypeGuid = (ULONG_PTR)pInheritedObjectTypeGuid;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAccessDeniedObjectAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAccessDeniedObjectAce *c = (struct qemu_RtlAddAccessDeniedObjectAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAccessDeniedObjectAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pObjectTypeGuid), QEMU_G2H(c->pInheritedObjectTypeGuid), QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlAddAuditAccessAceEx
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

WINBASEAPI NTSTATUS WINAPI RtlAddAuditAccessAceEx(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure)
{
    struct qemu_RtlAddAuditAccessAceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDAUDITACCESSACEEX);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.dwAceFlags = dwAceFlags;
    call.dwAccessMask = dwAccessMask;
    call.pSid = (ULONG_PTR)pSid;
    call.bAuditSuccess = bAuditSuccess;
    call.bAuditFailure = bAuditFailure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAuditAccessAceEx(struct qemu_syscall *call)
{
    struct qemu_RtlAddAuditAccessAceEx *c = (struct qemu_RtlAddAuditAccessAceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAuditAccessAceEx(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pSid), c->bAuditSuccess, c->bAuditFailure);
}

#endif

struct qemu_RtlAddAuditAccessAce
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

WINBASEAPI NTSTATUS WINAPI RtlAddAuditAccessAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAccessMask, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure)
{
    struct qemu_RtlAddAuditAccessAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDAUDITACCESSACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.dwAccessMask = dwAccessMask;
    call.pSid = (ULONG_PTR)pSid;
    call.bAuditSuccess = bAuditSuccess;
    call.bAuditFailure = bAuditFailure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAuditAccessAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAuditAccessAce *c = (struct qemu_RtlAddAuditAccessAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAuditAccessAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAccessMask, QEMU_G2H(c->pSid), c->bAuditSuccess, c->bAuditFailure);
}

#endif

struct qemu_RtlAddAuditAccessObjectAce
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

WINBASEAPI NTSTATUS WINAPI RtlAddAuditAccessObjectAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwAccessMask, IN GUID* pObjectTypeGuid, IN GUID* pInheritedObjectTypeGuid, IN PSID pSid, IN BOOL bAuditSuccess, IN BOOL bAuditFailure)
{
    struct qemu_RtlAddAuditAccessObjectAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDAUDITACCESSOBJECTACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.dwAceFlags = dwAceFlags;
    call.dwAccessMask = dwAccessMask;
    call.pObjectTypeGuid = (ULONG_PTR)pObjectTypeGuid;
    call.pInheritedObjectTypeGuid = (ULONG_PTR)pInheritedObjectTypeGuid;
    call.pSid = (ULONG_PTR)pSid;
    call.bAuditSuccess = bAuditSuccess;
    call.bAuditFailure = bAuditFailure;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddAuditAccessObjectAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddAuditAccessObjectAce *c = (struct qemu_RtlAddAuditAccessObjectAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddAuditAccessObjectAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwAccessMask, QEMU_G2H(c->pObjectTypeGuid), QEMU_G2H(c->pInheritedObjectTypeGuid), QEMU_G2H(c->pSid), c->bAuditSuccess, c->bAuditFailure);
}

#endif

struct qemu_RtlAddMandatoryAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceRevision;
    uint64_t dwAceFlags;
    uint64_t dwMandatoryFlags;
    uint64_t dwAceType;
    uint64_t pSid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAddMandatoryAce(IN OUT PACL pAcl, IN DWORD dwAceRevision, IN DWORD dwAceFlags, IN DWORD dwMandatoryFlags, IN DWORD dwAceType, IN PSID pSid)
{
    struct qemu_RtlAddMandatoryAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDMANDATORYACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceRevision = dwAceRevision;
    call.dwAceFlags = dwAceFlags;
    call.dwMandatoryFlags = dwMandatoryFlags;
    call.dwAceType = dwAceType;
    call.pSid = (ULONG_PTR)pSid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddMandatoryAce(struct qemu_syscall *call)
{
    struct qemu_RtlAddMandatoryAce *c = (struct qemu_RtlAddMandatoryAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAddMandatoryAce(QEMU_G2H(c->pAcl), c->dwAceRevision, c->dwAceFlags, c->dwMandatoryFlags, c->dwAceType, QEMU_G2H(c->pSid));
}

#endif

struct qemu_RtlValidAcl
{
    struct qemu_syscall super;
    uint64_t pAcl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlValidAcl(PACL pAcl)
{
    struct qemu_RtlValidAcl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLVALIDACL);
    call.pAcl = (ULONG_PTR)pAcl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlValidAcl(struct qemu_syscall *call)
{
    struct qemu_RtlValidAcl *c = (struct qemu_RtlValidAcl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlValidAcl(QEMU_G2H(c->pAcl));
}

#endif

struct qemu_RtlGetAce
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t dwAceIndex;
    uint64_t pAce;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetAce(PACL pAcl,DWORD dwAceIndex,LPVOID *pAce)
{
    struct qemu_RtlGetAce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETACE);
    call.pAcl = (ULONG_PTR)pAcl;
    call.dwAceIndex = dwAceIndex;
    call.pAce = (ULONG_PTR)pAce;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetAce(struct qemu_syscall *call)
{
    struct qemu_RtlGetAce *c = (struct qemu_RtlGetAce *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetAce(QEMU_G2H(c->pAcl), c->dwAceIndex, QEMU_G2H(c->pAce));
}

#endif

struct qemu_RtlAdjustPrivilege
{
    struct qemu_syscall super;
    uint64_t Privilege;
    uint64_t Enable;
    uint64_t CurrentThread;
    uint64_t Enabled;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled)
{
    struct qemu_RtlAdjustPrivilege call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADJUSTPRIVILEGE);
    call.Privilege = Privilege;
    call.Enable = Enable;
    call.CurrentThread = CurrentThread;
    call.Enabled = (ULONG_PTR)Enabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAdjustPrivilege(struct qemu_syscall *call)
{
    struct qemu_RtlAdjustPrivilege *c = (struct qemu_RtlAdjustPrivilege *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAdjustPrivilege(c->Privilege, c->Enable, c->CurrentThread, QEMU_G2H(c->Enabled));
}

#endif

struct qemu_RtlImpersonateSelf
{
    struct qemu_syscall super;
    uint64_t ImpersonationLevel;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlImpersonateSelf(SECURITY_IMPERSONATION_LEVEL ImpersonationLevel)
{
    struct qemu_RtlImpersonateSelf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIMPERSONATESELF);
    call.ImpersonationLevel = ImpersonationLevel;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlImpersonateSelf(struct qemu_syscall *call)
{
    struct qemu_RtlImpersonateSelf *c = (struct qemu_RtlImpersonateSelf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlImpersonateSelf(c->ImpersonationLevel);
}

#endif

struct qemu_NtImpersonateAnonymousToken
{
    struct qemu_syscall super;
    uint64_t thread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtImpersonateAnonymousToken(HANDLE thread)
{
    struct qemu_NtImpersonateAnonymousToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTIMPERSONATEANONYMOUSTOKEN);
    call.thread = (ULONG_PTR)thread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtImpersonateAnonymousToken(struct qemu_syscall *call)
{
    struct qemu_NtImpersonateAnonymousToken *c = (struct qemu_NtImpersonateAnonymousToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtImpersonateAnonymousToken(QEMU_G2H(c->thread));
}

#endif

struct qemu_NtAccessCheck
{
    struct qemu_syscall super;
    uint64_t SecurityDescriptor;
    uint64_t ClientToken;
    uint64_t DesiredAccess;
    uint64_t GenericMapping;
    uint64_t PrivilegeSet;
    uint64_t ReturnLength;
    uint64_t GrantedAccess;
    uint64_t AccessStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAccessCheck(PSECURITY_DESCRIPTOR SecurityDescriptor, HANDLE ClientToken, ACCESS_MASK DesiredAccess, PGENERIC_MAPPING GenericMapping, PPRIVILEGE_SET PrivilegeSet, PULONG ReturnLength, PULONG GrantedAccess, NTSTATUS *AccessStatus)
{
    struct qemu_NtAccessCheck call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTACCESSCHECK);
    call.SecurityDescriptor = (ULONG_PTR)SecurityDescriptor;
    call.ClientToken = (ULONG_PTR)ClientToken;
    call.DesiredAccess = DesiredAccess;
    call.GenericMapping = (ULONG_PTR)GenericMapping;
    call.PrivilegeSet = (ULONG_PTR)PrivilegeSet;
    call.ReturnLength = (ULONG_PTR)ReturnLength;
    call.GrantedAccess = (ULONG_PTR)GrantedAccess;
    call.AccessStatus = (ULONG_PTR)AccessStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAccessCheck(struct qemu_syscall *call)
{
    struct qemu_NtAccessCheck *c = (struct qemu_NtAccessCheck *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAccessCheck(QEMU_G2H(c->SecurityDescriptor), QEMU_G2H(c->ClientToken), c->DesiredAccess, QEMU_G2H(c->GenericMapping), QEMU_G2H(c->PrivilegeSet), QEMU_G2H(c->ReturnLength), QEMU_G2H(c->GrantedAccess), QEMU_G2H(c->AccessStatus));
}

#endif

struct qemu_NtSetSecurityObject
{
    struct qemu_syscall super;
    uint64_t Handle;
    uint64_t SecurityInformation;
    uint64_t SecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetSecurityObject(HANDLE Handle, SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    struct qemu_NtSetSecurityObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETSECURITYOBJECT);
    call.Handle = (ULONG_PTR)Handle;
    call.SecurityInformation = SecurityInformation;
    call.SecurityDescriptor = (ULONG_PTR)SecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetSecurityObject(struct qemu_syscall *call)
{
    struct qemu_NtSetSecurityObject *c = (struct qemu_NtSetSecurityObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetSecurityObject(QEMU_G2H(c->Handle), c->SecurityInformation, QEMU_G2H(c->SecurityDescriptor));
}

#endif

struct qemu_RtlConvertSidToUnicodeString
{
    struct qemu_syscall super;
    uint64_t String;
    uint64_t pSid;
    uint64_t AllocateString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlConvertSidToUnicodeString(PUNICODE_STRING String, PSID pSid, BOOLEAN AllocateString)
{
    struct qemu_RtlConvertSidToUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCONVERTSIDTOUNICODESTRING);
    call.String = (ULONG_PTR)String;
    call.pSid = (ULONG_PTR)pSid;
    call.AllocateString = AllocateString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlConvertSidToUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlConvertSidToUnicodeString *c = (struct qemu_RtlConvertSidToUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlConvertSidToUnicodeString(QEMU_G2H(c->String), QEMU_G2H(c->pSid), c->AllocateString);
}

#endif

struct qemu_RtlQueryInformationAcl
{
    struct qemu_syscall super;
    uint64_t pAcl;
    uint64_t pAclInformation;
    uint64_t nAclInformationLength;
    uint64_t dwAclInformationClass;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueryInformationAcl(PACL pAcl, LPVOID pAclInformation, DWORD nAclInformationLength, ACL_INFORMATION_CLASS dwAclInformationClass)
{
    struct qemu_RtlQueryInformationAcl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYINFORMATIONACL);
    call.pAcl = (ULONG_PTR)pAcl;
    call.pAclInformation = (ULONG_PTR)pAclInformation;
    call.nAclInformationLength = nAclInformationLength;
    call.dwAclInformationClass = dwAclInformationClass;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryInformationAcl(struct qemu_syscall *call)
{
    struct qemu_RtlQueryInformationAcl *c = (struct qemu_RtlQueryInformationAcl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlQueryInformationAcl(QEMU_G2H(c->pAcl), QEMU_G2H(c->pAclInformation), c->nAclInformationLength, c->dwAclInformationClass);
}

#endif

struct qemu_RtlConvertToAutoInheritSecurityObject
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

WINBASEAPI BOOL WINAPI RtlConvertToAutoInheritSecurityObject(PSECURITY_DESCRIPTOR pdesc, PSECURITY_DESCRIPTOR cdesc, PSECURITY_DESCRIPTOR* ndesc, GUID* objtype, BOOL isdir, PGENERIC_MAPPING genmap)
{
    struct qemu_RtlConvertToAutoInheritSecurityObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCONVERTTOAUTOINHERITSECURITYOBJECT);
    call.pdesc = (ULONG_PTR)pdesc;
    call.cdesc = (ULONG_PTR)cdesc;
    call.ndesc = (ULONG_PTR)ndesc;
    call.objtype = (ULONG_PTR)objtype;
    call.isdir = isdir;
    call.genmap = (ULONG_PTR)genmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlConvertToAutoInheritSecurityObject to Wine headers? */
extern BOOL WINAPI RtlConvertToAutoInheritSecurityObject(PSECURITY_DESCRIPTOR pdesc, PSECURITY_DESCRIPTOR cdesc, PSECURITY_DESCRIPTOR* ndesc, GUID* objtype, BOOL isdir, PGENERIC_MAPPING genmap);
void qemu_RtlConvertToAutoInheritSecurityObject(struct qemu_syscall *call)
{
    struct qemu_RtlConvertToAutoInheritSecurityObject *c = (struct qemu_RtlConvertToAutoInheritSecurityObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlConvertToAutoInheritSecurityObject(QEMU_G2H(c->pdesc), QEMU_G2H(c->cdesc), QEMU_G2H(c->ndesc), QEMU_G2H(c->objtype), c->isdir, QEMU_G2H(c->genmap));
}

#endif

