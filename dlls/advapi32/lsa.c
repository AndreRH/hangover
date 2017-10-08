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
#include <ntsecapi.h>

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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaAddAccountRights(QEMU_G2H(c->policy), QEMU_G2H(c->sid), QEMU_G2H(c->rights), c->count);
}

#endif

struct qemu_LsaClose
{
    struct qemu_syscall super;
    uint64_t ObjectHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaClose(IN LSA_HANDLE ObjectHandle)
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
    WINE_FIXME("Unverified!\n");
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

WINBASEAPI NTSTATUS WINAPI LsaEnumerateAccountRights(LSA_HANDLE policy, PSID sid, PLSA_UNICODE_STRING *rights, PULONG count)
{
    struct qemu_LsaEnumerateAccountRights call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAENUMERATEACCOUNTRIGHTS);
    call.policy = (ULONG_PTR)policy;
    call.sid = (ULONG_PTR)sid;
    call.rights = (ULONG_PTR)rights;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaEnumerateAccountRights(struct qemu_syscall *call)
{
    struct qemu_LsaEnumerateAccountRights *c = (struct qemu_LsaEnumerateAccountRights *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaEnumerateAccountRights(QEMU_G2H(c->policy), QEMU_G2H(c->sid), QEMU_G2H(c->rights), QEMU_G2H(c->count));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaEnumerateAccountsWithUserRight(QEMU_G2H(c->policy), QEMU_G2H(c->rights), QEMU_G2H(c->buffer), QEMU_G2H(c->count));
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
    WINE_FIXME("Unverified!\n");
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLookupNames(QEMU_G2H(c->PolicyHandle), c->Count, QEMU_G2H(c->Names), QEMU_G2H(c->ReferencedDomains), QEMU_G2H(c->Sids));
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

    return call.super.iret;
}

#else

void qemu_LsaLookupNames2(struct qemu_syscall *call)
{
    struct qemu_LsaLookupNames2 *c = (struct qemu_LsaLookupNames2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLookupNames2(QEMU_G2H(c->policy), c->flags, c->count, QEMU_G2H(c->names), QEMU_G2H(c->domains), QEMU_G2H(c->sids));
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
    call.ReferencedDomains = (ULONG_PTR)ReferencedDomains;
    call.Names = (ULONG_PTR)Names;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaLookupSids(struct qemu_syscall *call)
{
    struct qemu_LsaLookupSids *c = (struct qemu_LsaLookupSids *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLookupSids(QEMU_G2H(c->PolicyHandle), c->Count, QEMU_G2H(c->Sids), QEMU_G2H(c->ReferencedDomains), QEMU_G2H(c->Names));
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

WINBASEAPI NTSTATUS WINAPI LsaOpenPolicy(PLSA_UNICODE_STRING SystemName, PLSA_OBJECT_ATTRIBUTES ObjectAttributes, ACCESS_MASK DesiredAccess, PLSA_HANDLE PolicyHandle)
{
    struct qemu_LsaOpenPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAOPENPOLICY);
    call.SystemName = (ULONG_PTR)SystemName;
    call.ObjectAttributes = (ULONG_PTR)ObjectAttributes;
    call.DesiredAccess = DesiredAccess;
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaOpenPolicy(struct qemu_syscall *call)
{
    struct qemu_LsaOpenPolicy *c = (struct qemu_LsaOpenPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaOpenPolicy(QEMU_G2H(c->SystemName), QEMU_G2H(c->ObjectAttributes), c->DesiredAccess, QEMU_G2H(c->PolicyHandle));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaOpenTrustedDomainByName(QEMU_G2H(c->policy), QEMU_G2H(c->name), c->access, QEMU_G2H(c->handle));
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

WINBASEAPI NTSTATUS WINAPI LsaQueryInformationPolicy(IN LSA_HANDLE PolicyHandle, IN POLICY_INFORMATION_CLASS InformationClass, OUT PVOID *Buffer)
{
    struct qemu_LsaQueryInformationPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAQUERYINFORMATIONPOLICY);
    call.PolicyHandle = (ULONG_PTR)PolicyHandle;
    call.InformationClass = InformationClass;
    call.Buffer = (ULONG_PTR)Buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaQueryInformationPolicy(struct qemu_syscall *call)
{
    struct qemu_LsaQueryInformationPolicy *c = (struct qemu_LsaQueryInformationPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaQueryInformationPolicy(QEMU_G2H(c->PolicyHandle), c->InformationClass, QEMU_G2H(c->Buffer));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaQueryTrustedDomainInfoByName(QEMU_G2H(c->policy), QEMU_G2H(c->name), c->class, QEMU_G2H(c->buffer));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaRemoveAccountRights(QEMU_G2H(c->policy), QEMU_G2H(c->sid), c->all, QEMU_G2H(c->rights), c->count);
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaRetrievePrivateData(QEMU_G2H(c->PolicyHandle), QEMU_G2H(c->KeyName), QEMU_G2H(c->PrivateData));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaSetSecret(QEMU_G2H(c->SecretHandle), QEMU_G2H(c->EncryptedCurrentValue), QEMU_G2H(c->EncryptedOldValue));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaSetTrustedDomainInfoByName(QEMU_G2H(c->policy), QEMU_G2H(c->name), c->class, QEMU_G2H(c->buffer));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaStorePrivateData(QEMU_G2H(c->PolicyHandle), QEMU_G2H(c->KeyName), QEMU_G2H(c->PrivateData));
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

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI LsaLookupPrivilegeName(LSA_HANDLE handle, LUID *luid, UNICODE_STRING **name);
void qemu_LsaLookupPrivilegeName(struct qemu_syscall *call)
{
    struct qemu_LsaLookupPrivilegeName *c = (struct qemu_LsaLookupPrivilegeName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLookupPrivilegeName(QEMU_G2H(c->handle), QEMU_G2H(c->luid), QEMU_G2H(c->name));
}

#endif

