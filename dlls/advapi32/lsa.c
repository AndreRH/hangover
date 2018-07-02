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
#include <ntsecapi.h>
#include <winternl.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_winternl.h"
#include "thunk/qemu_ntsecapi.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_LsaAddAccountRights
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t sid;
    uint64_t rights;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaAddAccountRights(LSA_HANDLE policy, PSID sid, PLSA_UNICODE_STRING rights, ULONG count)
{
    struct qemu_LsaAddAccountRights call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAADDACCOUNTRIGHTS);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;
    call.rights = (ULONG_PTR)rights;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaAddAccountRights(struct qemu_syscall *call)
{
    struct qemu_LsaAddAccountRights *c = (struct qemu_LsaAddAccountRights *)call;
    LSA_UNICODE_STRING stack, *rights = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    rights = QEMU_G2H(c->rights);
#else
    if (c->rights)
        UNICODE_STRING_g2h(rights, QEMU_G2H(c->rights));
    else
        rights = NULL;
#endif

    c->super.iret = LsaAddAccountRights(QEMU_G2H(c->policy), QEMU_G2H(c->sid), rights, c->count);
}

#endif

struct qemu_LsaClose
{
    struct qemu_syscall super;
    uint64_t ObjectHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaClose(LSA_HANDLE ObjectHandle)
{
    struct qemu_LsaClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSACLOSE);
    call.ObjectHandle = (ULONG_PTR)ObjectHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaClose(struct qemu_syscall *call)
{
    struct qemu_LsaClose *c = (struct qemu_LsaClose *)call;
    WINE_TRACE("\n");
    c->super.iret = LsaClose(QEMU_G2H(c->ObjectHandle));
}

#endif

struct qemu_LsaCreateTrustedDomainEx
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t domain_info;
    uint64_t auth_info;
    uint64_t access;
    uint64_t domain;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaCreateTrustedDomainEx(LSA_HANDLE policy, PTRUSTED_DOMAIN_INFORMATION_EX domain_info, PTRUSTED_DOMAIN_AUTH_INFORMATION auth_info, ACCESS_MASK access, PLSA_HANDLE domain)
{
    struct qemu_LsaCreateTrustedDomainEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSACREATETRUSTEDDOMAINEX);
    call.policy = (ULONG_PTR)policy;
    call.domain_info = (ULONG_PTR)domain_info;
    call.auth_info = (ULONG_PTR)auth_info;
    call.access = access;
    call.domain = (ULONG_PTR)domain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaCreateTrustedDomainEx(struct qemu_syscall *call)
{
    struct qemu_LsaCreateTrustedDomainEx *c = (struct qemu_LsaCreateTrustedDomainEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaCreateTrustedDomainEx(QEMU_G2H(c->policy), QEMU_G2H(c->domain_info), QEMU_G2H(c->auth_info), c->access, QEMU_G2H(c->domain));
}

#endif

struct qemu_LsaDeleteTrustedDomain
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t sid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaDeleteTrustedDomain(LSA_HANDLE policy, PSID sid)
{
    struct qemu_LsaDeleteTrustedDomain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSADELETETRUSTEDDOMAIN);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaDeleteTrustedDomain(struct qemu_syscall *call)
{
    struct qemu_LsaDeleteTrustedDomain *c = (struct qemu_LsaDeleteTrustedDomain *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaDeleteTrustedDomain(QEMU_G2H(c->policy), QEMU_G2H(c->sid));
}

#endif

struct qemu_LsaEnumerateAccountRights
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t sid;
    uint64_t rights;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaEnumerateAccountRights(LSA_HANDLE policy, PSID sid,
        PLSA_UNICODE_STRING *rights, PULONG count)
{
    struct qemu_LsaEnumerateAccountRights call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAENUMERATEACCOUNTRIGHTS);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;
    call.rights = (ULONG_PTR)rights;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);
    *rights = (LSA_UNICODE_STRING *)(ULONG_PTR)call.rights;

    return call.super.iret;
}

#else

void qemu_LsaEnumerateAccountRights(struct qemu_syscall *call)
{
    struct qemu_LsaEnumerateAccountRights *c = (struct qemu_LsaEnumerateAccountRights *)call;
    LSA_UNICODE_STRING *rights;

    /* This function is a stub in Wine, but we still need to be careful about the pointer to a pointer it zeroes. */
    WINE_WARN("Unverified!\n");
    c->super.iret = LsaEnumerateAccountRights(QEMU_G2H(c->policy), QEMU_G2H(c->sid), c->rights ? &rights : NULL,
            QEMU_G2H(c->count));
    c->rights = QEMU_H2G(rights);
}

#endif

struct qemu_LsaEnumerateAccountsWithUserRight
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t rights;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaEnumerateAccountsWithUserRight(LSA_HANDLE policy, PLSA_UNICODE_STRING rights, PVOID *buffer, PULONG count)
{
    struct qemu_LsaEnumerateAccountsWithUserRight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAENUMERATEACCOUNTSWITHUSERRIGHT);
    call.policy = (ULONG_PTR)policy;
    call.rights = (ULONG_PTR)rights;
    call.buffer = (ULONG_PTR)buffer;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaEnumerateAccountsWithUserRight(struct qemu_syscall *call)
{
    struct qemu_LsaEnumerateAccountsWithUserRight *c = (struct qemu_LsaEnumerateAccountsWithUserRight *)call;
    LSA_UNICODE_STRING stack, *rights = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    rights = QEMU_G2H(c->rights);
#else
    if (c->rights)
        UNICODE_STRING_g2h(rights, QEMU_G2H(c->rights));
    else
        rights = NULL;
#endif
    c->super.iret = LsaEnumerateAccountsWithUserRight(QEMU_G2H(c->policy), rights, QEMU_G2H(c->buffer), QEMU_G2H(c->count));
}

#endif

struct qemu_LsaEnumerateTrustedDomains
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t EnumerationContext;
    uint64_t Buffer;
    uint64_t PreferredMaximumLength;
    uint64_t CountReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaEnumerateTrustedDomains(LSA_HANDLE PolicyHandle, PLSA_ENUMERATION_HANDLE EnumerationContext, OUT PVOID* Buffer, ULONG PreferredMaximumLength, PULONG CountReturned)
{
    struct qemu_LsaEnumerateTrustedDomains call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAENUMERATETRUSTEDDOMAINS);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.EnumerationContext = (ULONG_PTR)EnumerationContext;
    call.Buffer = (ULONG_PTR)Buffer;
    call.PreferredMaximumLength = PreferredMaximumLength;
    call.CountReturned = (ULONG_PTR)CountReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaEnumerateTrustedDomains(struct qemu_syscall *call)
{
    struct qemu_LsaEnumerateTrustedDomains *c = (struct qemu_LsaEnumerateTrustedDomains *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaEnumerateTrustedDomains(QEMU_G2H(c->PolicyHandle), QEMU_G2H(c->EnumerationContext), QEMU_G2H(c->Buffer), c->PreferredMaximumLength, QEMU_G2H(c->CountReturned));
}

#endif

struct qemu_LsaEnumerateTrustedDomainsEx
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t context;
    uint64_t buffer;
    uint64_t length;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaEnumerateTrustedDomainsEx(LSA_HANDLE policy, PLSA_ENUMERATION_HANDLE context, PVOID *buffer, ULONG length, PULONG count)
{
    struct qemu_LsaEnumerateTrustedDomainsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAENUMERATETRUSTEDDOMAINSEX);
    call.policy = (ULONG_PTR)policy;
    call.context = (ULONG_PTR)context;
    call.buffer = (ULONG_PTR)buffer;
    call.length = length;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaEnumerateTrustedDomainsEx(struct qemu_syscall *call)
{
    struct qemu_LsaEnumerateTrustedDomainsEx *c = (struct qemu_LsaEnumerateTrustedDomainsEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaEnumerateTrustedDomainsEx(QEMU_G2H(c->policy), QEMU_G2H(c->context), QEMU_G2H(c->buffer), c->length, QEMU_G2H(c->count));
}

#endif

struct qemu_LsaFreeMemory
{
    struct qemu_syscall super;
    uint64_t Buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaFreeMemory(PVOID Buffer)
{
    struct qemu_LsaFreeMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAFREEMEMORY);
    call.Buffer = (ULONG_PTR)Buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaFreeMemory(struct qemu_syscall *call)
{
    struct qemu_LsaFreeMemory *c = (struct qemu_LsaFreeMemory *)call;
    WINE_TRACE("\n");
    c->super.iret = LsaFreeMemory(QEMU_G2H(c->Buffer));
}

#endif

struct qemu_LsaLookupNames
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t Count;
    uint64_t Names;
    uint64_t ReferencedDomains;
    uint64_t Sids;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLookupNames(LSA_HANDLE PolicyHandle, ULONG Count, PLSA_UNICODE_STRING Names, PLSA_REFERENCED_DOMAIN_LIST* ReferencedDomains, PLSA_TRANSLATED_SID* Sids)
{
    struct qemu_LsaLookupNames call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOOKUPNAMES);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.Count = Count;
    call.Names = (ULONG_PTR)Names;
    call.ReferencedDomains = (ULONG_PTR)ReferencedDomains;
    call.Sids = (ULONG_PTR)Sids;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaLookupNames(struct qemu_syscall *call)
{
    struct qemu_LsaLookupNames *c = (struct qemu_LsaLookupNames *)call;
    LSA_UNICODE_STRING stack, *names = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    names = QEMU_G2H(c->Names);
#else
    if (c->Names)
        UNICODE_STRING_g2h(names, QEMU_G2H(c->Names));
    else
        names = NULL;
#endif

    c->super.iret = LsaLookupNames(QEMU_G2H(c->PolicyHandle), c->Count, names, QEMU_G2H(c->ReferencedDomains),
            QEMU_G2H(c->Sids));
}

#endif

struct qemu_LsaLookupNames2
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t flags;
    uint64_t count;
    uint64_t names;
    uint64_t domains;
    uint64_t sids;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLookupNames2(LSA_HANDLE policy, ULONG flags, ULONG count, PLSA_UNICODE_STRING names, PLSA_REFERENCED_DOMAIN_LIST *domains, PLSA_TRANSLATED_SID2 *sids)
{
    struct qemu_LsaLookupNames2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOOKUPNAMES2);
    call.policy = (ULONG_PTR)policy;
    call.flags = flags;
    call.count = count;
    call.names = (ULONG_PTR)names;
    call.domains = (ULONG_PTR)domains;
    call.sids = (ULONG_PTR)sids;

    qemu_syscall(&call.super);
    *domains = (LSA_REFERENCED_DOMAIN_LIST *)(ULONG_PTR)call.domains;
    *sids = (LSA_TRANSLATED_SID2 *)(ULONG_PTR)call.sids;

    return call.super.iret;
}

#else

void qemu_LsaLookupNames2(struct qemu_syscall *call)
{
    struct qemu_LsaLookupNames2 *c = (struct qemu_LsaLookupNames2 *)call;
    LSA_UNICODE_STRING stack[10], *names = stack;
    struct qemu_UNICODE_STRING *names32;
    unsigned int i;
    LSA_REFERENCED_DOMAIN_LIST *domains;
    LSA_TRANSLATED_SID2 *sids;
    struct qemu_LSA_TRANSLATED_SID2 *sids32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    names = QEMU_G2H(c->names);
#else
    names32 = QEMU_G2H(c->names);
    if (names32)
    {
        if (c->count > sizeof(stack) / sizeof(stack[0]))
            names = HeapAlloc(GetProcessHeap(), 0, c->count * sizeof(*names));

        for (i = 0; i < c->count; ++i)
            UNICODE_STRING_g2h(&names[i], &names32[i]);
    }
    else
    {
        names = NULL;
    }
#endif

    c->super.iret = LsaLookupNames2(QEMU_G2H(c->policy), c->flags, c->count, names, &domains, &sids);

#if GUEST_BIT != HOST_BIT
    if (names && names != stack)
        HeapFree(GetProcessHeap(), 0, names);

    sids32 = (struct qemu_LSA_TRANSLATED_SID2 *)sids;
    for (i = 0; i < c->count; ++i)
        LSA_TRANSLATED_SID2_h2g(&sids32[i], &sids[i]);

    LSA_REFERENCED_DOMAIN_LIST_h2g((struct qemu_LSA_REFERENCED_DOMAIN_LIST *)domains, domains);
#endif

    c->domains = QEMU_H2G(domains);
    c->sids = QEMU_H2G(sids);
}

#endif

struct qemu_LsaLookupSids
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t Count;
    uint64_t Sids;
    uint64_t ReferencedDomains;
    uint64_t Names;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLookupSids(LSA_HANDLE PolicyHandle, ULONG Count, PSID *Sids, LSA_REFERENCED_DOMAIN_LIST **ReferencedDomains, LSA_TRANSLATED_NAME **Names)
{
    struct qemu_LsaLookupSids call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOOKUPSIDS);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.Count = Count;
    call.Sids = (ULONG_PTR)Sids;

    /* Names and ReferencedDomains are written unconditionally. */
    qemu_syscall(&call.super);
    *ReferencedDomains = (LSA_REFERENCED_DOMAIN_LIST *)(ULONG_PTR)call.ReferencedDomains;
    *Names = (LSA_TRANSLATED_NAME *)(ULONG_PTR)call.Names;

    return call.super.iret;
}

#else

void qemu_LsaLookupSids(struct qemu_syscall *call)
{
    struct qemu_LsaLookupSids *c = (struct qemu_LsaLookupSids *)call;
    PSID stack[10], *sids = stack;
    qemu_ptr *sids32;
    unsigned int i;
    LSA_TRANSLATED_NAME *names;
    LSA_REFERENCED_DOMAIN_LIST *list;
    struct qemu_LSA_TRANSLATED_NAME *names32;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    sids = QEMU_G2H(c->Sids);
#else
    sids32 = QEMU_G2H(c->Sids);
    if (sids32)
    {
        if (c->Count > sizeof(stack) / sizeof(stack[0]))
            sids = HeapAlloc(GetProcessHeap(), 0, c->Count * sizeof(*sids));

        for (i = 0; i < c->Count; ++i)
            sids[i] = (PSID)(ULONG_PTR)sids32[i];
    }
    else
    {
        sids = NULL;
    }
#endif

    c->super.iret = LsaLookupSids(QEMU_G2H(c->PolicyHandle), c->Count, sids, &list, &names);

#if GUEST_BIT != HOST_BIT
    if (sids && sids != stack)
        HeapFree(GetProcessHeap(), 0, sids);

    LSA_REFERENCED_DOMAIN_LIST_h2g((struct qemu_LSA_REFERENCED_DOMAIN_LIST *)list, list);

    names32 = (struct qemu_LSA_TRANSLATED_NAME *)names;
    for (i = 0; i < c->Count; ++i)
        LSA_TRANSLATED_NAME_h2g(&names32[i], &names[i]);
#endif
    c->ReferencedDomains = QEMU_H2G(list);
    c->Names = QEMU_H2G(names);
}

#endif

struct qemu_LsaNtStatusToWinError
{
    struct qemu_syscall super;
    uint64_t Status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI LsaNtStatusToWinError(NTSTATUS Status)
{
    struct qemu_LsaNtStatusToWinError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSANTSTATUSTOWINERROR);
    call.Status = Status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaNtStatusToWinError(struct qemu_syscall *call)
{
    struct qemu_LsaNtStatusToWinError *c = (struct qemu_LsaNtStatusToWinError *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaNtStatusToWinError(c->Status);
}

#endif

struct qemu_LsaOpenPolicy
{
    struct qemu_syscall super;
    uint64_t SystemName;
    uint64_t ObjectAttributes;
    uint64_t DesiredAccess;
    uint64_t PolicyHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaOpenPolicy(PLSA_UNICODE_STRING SystemName, PLSA_OBJECT_ATTRIBUTES ObjectAttributes,
        ACCESS_MASK DesiredAccess, PLSA_HANDLE PolicyHandle)
{
    struct qemu_LsaOpenPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAOPENPOLICY);
    call.SystemName = (ULONG_PTR)SystemName;
    call.ObjectAttributes = (ULONG_PTR)ObjectAttributes;
    call.DesiredAccess = DesiredAccess;
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;

    qemu_syscall(&call.super);
    if (PolicyHandle)
        *PolicyHandle = (LSA_HANDLE)(ULONG_PTR)call.PolicyHandle;

    return call.super.iret;
}

#else

void qemu_LsaOpenPolicy(struct qemu_syscall *call)
{
    struct qemu_LsaOpenPolicy *c = (struct qemu_LsaOpenPolicy *)call;
    LSA_UNICODE_STRING stack, *string = &stack;
    LSA_HANDLE policy;

    /* This is a semi-stub in Wine. */
    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    string = QEMU_G2H(c->SystemName);
#else
    if (c->SystemName)
        UNICODE_STRING_g2h(string, QEMU_G2H(c->SystemName));
    else
        string = NULL;
#endif

    c->super.iret = LsaOpenPolicy(string, QEMU_G2H(c->ObjectAttributes), c->DesiredAccess, &policy);
    c->PolicyHandle = QEMU_H2G(policy);
}

#endif

struct qemu_LsaOpenTrustedDomainByName
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t name;
    uint64_t access;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaOpenTrustedDomainByName(LSA_HANDLE policy, PLSA_UNICODE_STRING name, ACCESS_MASK access, PLSA_HANDLE handle)
{
    struct qemu_LsaOpenTrustedDomainByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAOPENTRUSTEDDOMAINBYNAME);
    call.policy = (ULONG_PTR)policy;
    call.name = (ULONG_PTR)name;
    call.access = access;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaOpenTrustedDomainByName(struct qemu_syscall *call)
{
    struct qemu_LsaOpenTrustedDomainByName *c = (struct qemu_LsaOpenTrustedDomainByName *)call;
    LSA_UNICODE_STRING stack, *name = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    name = QEMU_G2H(c->name);
#else
    if (c->name)
        UNICODE_STRING_g2h(name, QEMU_G2H(c->name));
    else
        name = NULL;
#endif

    c->super.iret = LsaOpenTrustedDomainByName(QEMU_G2H(c->policy), name, c->access, QEMU_G2H(c->handle));
}

#endif

struct qemu_LsaQueryInformationPolicy
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t InformationClass;
    uint64_t Buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaQueryInformationPolicy(LSA_HANDLE PolicyHandle,
        POLICY_INFORMATION_CLASS InformationClass, void **Buffer)
{
    struct qemu_LsaQueryInformationPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAQUERYINFORMATIONPOLICY);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.InformationClass = InformationClass;
    call.Buffer = (ULONG_PTR)Buffer;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *Buffer = (void *)(ULONG_PTR)call.Buffer;

    return call.super.iret;
}

#else

void qemu_LsaQueryInformationPolicy(struct qemu_syscall *call)
{
    struct qemu_LsaQueryInformationPolicy *c = (struct qemu_LsaQueryInformationPolicy *)call;
    void *buffer;

    /* Wine allocates memory for the returned data. All info classes need conversions because there
     * are pointers stored in the structs. We can probably convert this in place. */
    WINE_TRACE("\n");
    c->super.iret = LsaQueryInformationPolicy(QEMU_G2H(c->PolicyHandle), c->InformationClass,
            c->Buffer ? &buffer : NULL);

#if GUEST_BIT != HOST_BIT
    switch (c->InformationClass)
    {
        case PolicyAuditEventsInformation:
            POLICY_AUDIT_EVENTS_INFO_h2g(buffer, buffer);
            break;

        case PolicyPrimaryDomainInformation:
            POLICY_PRIMARY_DOMAIN_INFO_h2g(buffer, buffer);
            break;

        case PolicyAccountDomainInformation:
            POLICY_ACCOUNT_DOMAIN_INFO_h2g(buffer, buffer);
            break;

        case PolicyDnsDomainInformation:
            POLICY_DNS_DOMAIN_INFO_h2g(buffer, buffer);
            break;

        case PolicyAuditLogInformation:
        case PolicyPdAccountInformation:
        case PolicyLsaServerRoleInformation:
        case PolicyReplicaSourceInformation:
        case PolicyDefaultQuotaInformation:
        case PolicyModificationInformation:
        case PolicyAuditFullSetInformation:
        case PolicyAuditFullQueryInformation:
            WINE_FIXME("Unhandled information class %u.\n", (unsigned int)c->InformationClass);
            break;

        default:
            WINE_FIXME("Unexpected information class %u.\n", (unsigned int)c->InformationClass);
    }
#endif

    c->Buffer = QEMU_H2G(buffer);
}

#endif

struct qemu_LsaQueryTrustedDomainInfo
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t sid;
    uint64_t class;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaQueryTrustedDomainInfo(LSA_HANDLE policy, PSID sid, TRUSTED_INFORMATION_CLASS class, PVOID *buffer)
{
    struct qemu_LsaQueryTrustedDomainInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAQUERYTRUSTEDDOMAININFO);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;
    call.class = class;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaQueryTrustedDomainInfo(struct qemu_syscall *call)
{
    struct qemu_LsaQueryTrustedDomainInfo *c = (struct qemu_LsaQueryTrustedDomainInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaQueryTrustedDomainInfo(QEMU_G2H(c->policy), QEMU_G2H(c->sid), c->class, QEMU_G2H(c->buffer));
}

#endif

struct qemu_LsaQueryTrustedDomainInfoByName
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t name;
    uint64_t class;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaQueryTrustedDomainInfoByName(LSA_HANDLE policy, PLSA_UNICODE_STRING name, TRUSTED_INFORMATION_CLASS class, PVOID *buffer)
{
    struct qemu_LsaQueryTrustedDomainInfoByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAQUERYTRUSTEDDOMAININFOBYNAME);
    call.policy = (ULONG_PTR)policy;
    call.name = (ULONG_PTR)name;
    call.class = class;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaQueryTrustedDomainInfoByName(struct qemu_syscall *call)
{
    struct qemu_LsaQueryTrustedDomainInfoByName *c = (struct qemu_LsaQueryTrustedDomainInfoByName *)call;
    LSA_UNICODE_STRING stack, *name = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    name = QEMU_G2H(c->name);
#else
    if (c->name)
        UNICODE_STRING_g2h(name, QEMU_G2H(c->name));
    else
        name = NULL;
#endif

    c->super.iret = LsaQueryTrustedDomainInfoByName(QEMU_G2H(c->policy), name, c->class, QEMU_G2H(c->buffer));
}

#endif

struct qemu_LsaRegisterPolicyChangeNotification
{
    struct qemu_syscall super;
    uint64_t class;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaRegisterPolicyChangeNotification(POLICY_NOTIFICATION_INFORMATION_CLASS class, HANDLE event)
{
    struct qemu_LsaRegisterPolicyChangeNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAREGISTERPOLICYCHANGENOTIFICATION);
    call.class = class;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaRegisterPolicyChangeNotification(struct qemu_syscall *call)
{
    struct qemu_LsaRegisterPolicyChangeNotification *c = (struct qemu_LsaRegisterPolicyChangeNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaRegisterPolicyChangeNotification(c->class, QEMU_G2H(c->event));
}

#endif

struct qemu_LsaRemoveAccountRights
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t sid;
    uint64_t all;
    uint64_t rights;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaRemoveAccountRights(LSA_HANDLE policy, PSID sid, BOOLEAN all, PLSA_UNICODE_STRING rights, ULONG count)
{
    struct qemu_LsaRemoveAccountRights call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAREMOVEACCOUNTRIGHTS);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;
    call.all = all;
    call.rights = (ULONG_PTR)rights;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaRemoveAccountRights(struct qemu_syscall *call)
{
    struct qemu_LsaRemoveAccountRights *c = (struct qemu_LsaRemoveAccountRights *)call;
    LSA_UNICODE_STRING stack, *rights = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    rights = QEMU_G2H(c->rights);
#else
    if (c->rights)
        UNICODE_STRING_g2h(rights, QEMU_G2H(c->rights));
    else
        rights = NULL;
#endif

    c->super.iret = LsaRemoveAccountRights(QEMU_G2H(c->policy), QEMU_G2H(c->sid), c->all, rights, c->count);
}

#endif

struct qemu_LsaRetrievePrivateData
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t KeyName;
    uint64_t PrivateData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaRetrievePrivateData(IN LSA_HANDLE PolicyHandle, IN PLSA_UNICODE_STRING KeyName, OUT PLSA_UNICODE_STRING* PrivateData)
{
    struct qemu_LsaRetrievePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSARETRIEVEPRIVATEDATA);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.KeyName = (ULONG_PTR)KeyName;
    call.PrivateData = (ULONG_PTR)PrivateData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaRetrievePrivateData(struct qemu_syscall *call)
{
    struct qemu_LsaRetrievePrivateData *c = (struct qemu_LsaRetrievePrivateData *)call;
    LSA_UNICODE_STRING stack, *key_name = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    key_name = QEMU_G2H(c->KeyName);
#else
    if (c->KeyName)
        UNICODE_STRING_g2h(key_name, QEMU_G2H(c->KeyName));
    else
        key_name = NULL;
#endif

    c->super.iret = LsaRetrievePrivateData(QEMU_G2H(c->PolicyHandle), key_name, QEMU_G2H(c->PrivateData));
}

#endif

struct qemu_LsaSetInformationPolicy
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t InformationClass;
    uint64_t Buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaSetInformationPolicy(IN LSA_HANDLE PolicyHandle, IN POLICY_INFORMATION_CLASS InformationClass, IN PVOID Buffer)
{
    struct qemu_LsaSetInformationPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSASETINFORMATIONPOLICY);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.InformationClass = InformationClass;
    call.Buffer = (ULONG_PTR)Buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaSetInformationPolicy(struct qemu_syscall *call)
{
    struct qemu_LsaSetInformationPolicy *c = (struct qemu_LsaSetInformationPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaSetInformationPolicy(QEMU_G2H(c->PolicyHandle), c->InformationClass, QEMU_G2H(c->Buffer));
}

#endif

struct qemu_LsaSetSecret
{
    struct qemu_syscall super;
    uint64_t SecretHandle;
    uint64_t EncryptedCurrentValue;
    uint64_t EncryptedOldValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaSetSecret(LSA_HANDLE SecretHandle, PLSA_UNICODE_STRING EncryptedCurrentValue, PLSA_UNICODE_STRING EncryptedOldValue)
{
    struct qemu_LsaSetSecret call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSASETSECRET);
    call.SecretHandle = (ULONG_PTR)SecretHandle;
    call.EncryptedCurrentValue = (ULONG_PTR)EncryptedCurrentValue;
    call.EncryptedOldValue = (ULONG_PTR)EncryptedOldValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI LsaSetSecret(LSA_HANDLE SecretHandle, PLSA_UNICODE_STRING EncryptedCurrentValue, PLSA_UNICODE_STRING EncryptedOldValue);
void qemu_LsaSetSecret(struct qemu_syscall *call)
{
    struct qemu_LsaSetSecret *c = (struct qemu_LsaSetSecret *)call;
    LSA_UNICODE_STRING stack, *cur_value = &stack;
    LSA_UNICODE_STRING stack2, *old_value = &stack2;

#if GUEST_BIT == HOST_BIT
    cur_value = QEMU_G2H(c->EncryptedCurrentValue);
    old_value = QEMU_G2H(c->EncryptedOldValue);
#else
    if (c->EncryptedCurrentValue)
        UNICODE_STRING_g2h(cur_value, QEMU_G2H(c->EncryptedCurrentValue));
    else
        cur_value = NULL;

    if (c->EncryptedCurrentValue)
        UNICODE_STRING_g2h(old_value, QEMU_G2H(c->EncryptedCurrentValue));
    else
        old_value = NULL;
#endif

    c->super.iret = LsaSetSecret(QEMU_G2H(c->SecretHandle), cur_value, old_value);
}

#endif

struct qemu_LsaSetTrustedDomainInfoByName
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t name;
    uint64_t class;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaSetTrustedDomainInfoByName(LSA_HANDLE policy, PLSA_UNICODE_STRING name, TRUSTED_INFORMATION_CLASS class, PVOID buffer)
{
    struct qemu_LsaSetTrustedDomainInfoByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSASETTRUSTEDDOMAININFOBYNAME);
    call.policy = (ULONG_PTR)policy;
    call.name = (ULONG_PTR)name;
    call.class = class;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaSetTrustedDomainInfoByName(struct qemu_syscall *call)
{
    struct qemu_LsaSetTrustedDomainInfoByName *c = (struct qemu_LsaSetTrustedDomainInfoByName *)call;
    LSA_UNICODE_STRING stack, *name = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    name = QEMU_G2H(c->name);
#else
    if (c->name)
        UNICODE_STRING_g2h(name, QEMU_G2H(c->name));
    else
        name = NULL;
#endif

    c->super.iret = LsaSetTrustedDomainInfoByName(QEMU_G2H(c->policy), name, c->class, QEMU_G2H(c->buffer));
}

#endif

struct qemu_LsaSetTrustedDomainInformation
{
    struct qemu_syscall super;
    uint64_t policy;
    uint64_t sid;
    uint64_t class;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaSetTrustedDomainInformation(LSA_HANDLE policy, PSID sid, TRUSTED_INFORMATION_CLASS class, PVOID buffer)
{
    struct qemu_LsaSetTrustedDomainInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSASETTRUSTEDDOMAININFORMATION);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;
    call.class = class;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaSetTrustedDomainInformation(struct qemu_syscall *call)
{
    struct qemu_LsaSetTrustedDomainInformation *c = (struct qemu_LsaSetTrustedDomainInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaSetTrustedDomainInformation(QEMU_G2H(c->policy), QEMU_G2H(c->sid), c->class, QEMU_G2H(c->buffer));
}

#endif

struct qemu_LsaStorePrivateData
{
    struct qemu_syscall super;
    uint64_t PolicyHandle;
    uint64_t KeyName;
    uint64_t PrivateData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaStorePrivateData(IN LSA_HANDLE PolicyHandle, IN PLSA_UNICODE_STRING KeyName, IN PLSA_UNICODE_STRING PrivateData)
{
    struct qemu_LsaStorePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSASTOREPRIVATEDATA);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.KeyName = (ULONG_PTR)KeyName;
    call.PrivateData = (ULONG_PTR)PrivateData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaStorePrivateData(struct qemu_syscall *call)
{
    struct qemu_LsaStorePrivateData *c = (struct qemu_LsaStorePrivateData *)call;
    LSA_UNICODE_STRING stack, *key_name = &stack;

    WINE_FIXME("Unverified!\n");
#if GUEST_BIT == HOST_BIT
    key_name = QEMU_G2H(c->KeyName);
#else
    if (c->KeyName)
        UNICODE_STRING_g2h(key_name, QEMU_G2H(c->KeyName));
    else
        key_name = NULL;
#endif

    c->super.iret = LsaStorePrivateData(QEMU_G2H(c->PolicyHandle), key_name, QEMU_G2H(c->PrivateData));
}

#endif

struct qemu_LsaUnregisterPolicyChangeNotification
{
    struct qemu_syscall super;
    uint64_t class;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaUnregisterPolicyChangeNotification(POLICY_NOTIFICATION_INFORMATION_CLASS class, HANDLE event)
{
    struct qemu_LsaUnregisterPolicyChangeNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAUNREGISTERPOLICYCHANGENOTIFICATION);
    call.class = class;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaUnregisterPolicyChangeNotification(struct qemu_syscall *call)
{
    struct qemu_LsaUnregisterPolicyChangeNotification *c = (struct qemu_LsaUnregisterPolicyChangeNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaUnregisterPolicyChangeNotification(c->class, QEMU_G2H(c->event));
}

#endif

struct qemu_LsaLookupPrivilegeName
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t luid;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLookupPrivilegeName(LSA_HANDLE handle, LUID *luid, UNICODE_STRING **name)
{
    struct qemu_LsaLookupPrivilegeName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOOKUPPRIVILEGENAME);
    call.handle = (ULONG_PTR)handle;
    call.luid = (ULONG_PTR)luid;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);
    if (luid && handle) /* Logic copied from the Wine implementation - not nice. */
        *name = (UNICODE_STRING *)(ULONG_PTR)call.name;

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI LsaLookupPrivilegeName(LSA_HANDLE handle, LUID *luid, UNICODE_STRING **name);
void qemu_LsaLookupPrivilegeName(struct qemu_syscall *call)
{
    struct qemu_LsaLookupPrivilegeName *c = (struct qemu_LsaLookupPrivilegeName *)call;
    UNICODE_STRING *name = NULL;

    WINE_TRACE("\n");
    c->super.iret = LsaLookupPrivilegeName(QEMU_G2H(c->handle), QEMU_G2H(c->luid), c->name ? &name : NULL);

#if GUEST_BIT != HOST_BIT
    if (name)
        UNICODE_STRING_h2g((struct qemu_UNICODE_STRING *)name, name);
#endif
    c->name = QEMU_H2G(name);
}

#endif

struct qemu_LsaLookupPrivilegeDisplayName
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t name;
    uint64_t display_name;
    uint64_t language;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLookupPrivilegeDisplayName(LSA_HANDLE handle, LSA_UNICODE_STRING *name, LSA_UNICODE_STRING **display_name, SHORT *language)
{
    struct qemu_LsaLookupPrivilegeDisplayName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOOKUPPRIVILEGEDISPLAYNAME);
    call.handle = (ULONG_PTR)handle;
    call.name = (ULONG_PTR)name;
    call.display_name = (ULONG_PTR)display_name;
    call.language = (ULONG_PTR)language;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI LsaLookupPrivilegeDisplayName(LSA_HANDLE handle, LSA_UNICODE_STRING *name, LSA_UNICODE_STRING **display_name, SHORT *language);
void qemu_LsaLookupPrivilegeDisplayName(struct qemu_syscall *call)
{
    struct qemu_LsaLookupPrivilegeDisplayName *c = (struct qemu_LsaLookupPrivilegeDisplayName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLookupPrivilegeDisplayName(QEMU_G2H(c->handle), QEMU_G2H(c->name), QEMU_G2H(c->display_name), QEMU_G2H(c->language));
}

#endif
