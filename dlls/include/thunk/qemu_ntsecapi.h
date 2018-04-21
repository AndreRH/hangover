#ifndef HAVE_THUNK_NTSECAPI_H
#define HAVE_THUNK_NTSECAPI_H

struct qemu_LSA_TRANSLATED_SID2
{
    SID_NAME_USE Use;
    qemu_ptr Sid;
    LONG DomainIndex;
    ULONG Flags;
};

static inline void LSA_TRANSLATED_SID2_g2h(LSA_TRANSLATED_SID2 *host, const struct qemu_LSA_TRANSLATED_SID2 *guest)
{
    host->Use = guest->Use;
    host->Sid = (PSID)(ULONG_PTR)guest->Sid;
    host->DomainIndex = guest->DomainIndex;
    host->Flags = guest->Flags;
}

static inline void LSA_TRANSLATED_SID2_h2g(struct qemu_LSA_TRANSLATED_SID2 *guest, const LSA_TRANSLATED_SID2 *host)
{
    guest->Use = host->Use;
    guest->Sid = (ULONG_PTR)host->Sid;
    guest->DomainIndex = host->DomainIndex;
    guest->Flags = host->Flags;
}

struct qemu_LSA_TRUST_INFORMATION
{
    struct qemu_UNICODE_STRING Name;
    qemu_ptr Sid;
};

static inline void LSA_TRUST_INFORMATION_g2h(LSA_TRUST_INFORMATION *host,
        const struct qemu_LSA_TRUST_INFORMATION *guest)
{
    UNICODE_STRING_g2h(&host->Name, &guest->Name);
    host->Sid = (PSID)(ULONG_PTR)guest->Sid;
}

static inline void LSA_TRUST_INFORMATION_h2g(struct qemu_LSA_TRUST_INFORMATION *guest,
        const LSA_TRUST_INFORMATION *host)
{
    UNICODE_STRING_h2g(&guest->Name, &host->Name);
    guest->Sid = (ULONG_PTR)host->Sid;
}

struct qemu_LSA_REFERENCED_DOMAIN_LIST
{
    ULONG Entries;
    qemu_ptr Domains;
};

/* Disabled for now until we need it and know how we best allocate the expanded Domains array.
static inline void LSA_REFERENCED_DOMAIN_LIST_g2h(LSA_REFERENCED_DOMAIN_LIST *host,
        const struct qemu_LSA_REFERENCED_DOMAIN_LIST *guest)
{
    ULONG i;

    host->Entries = guest->Entries;
    host->Domains = (LSA_TRUST_INFORMATION *)(ULONG_PTR)guest->Domains;
}
*/

static inline void LSA_REFERENCED_DOMAIN_LIST_h2g(struct qemu_LSA_REFERENCED_DOMAIN_LIST *guest,
        const LSA_REFERENCED_DOMAIN_LIST *host)
{
    ULONG i;

    guest->Entries = host->Entries;
    guest->Domains = (ULONG_PTR)host->Domains;
    for (i = 0; i < guest->Entries; ++i)
        LSA_TRUST_INFORMATION_h2g(&((struct qemu_LSA_TRUST_INFORMATION *)host->Domains)[i], &host->Domains[i]);
}

struct qemu_LSA_TRANSLATED_NAME
{
    SID_NAME_USE Use;
    struct qemu_UNICODE_STRING Name;
    LONG DomainIndex;
};

static inline void LSA_TRANSLATED_NAME_g2h(LSA_TRANSLATED_NAME *host,
        const struct qemu_LSA_TRANSLATED_NAME *guest)
{
    host->Use = guest->Use;
    UNICODE_STRING_g2h(&host->Name, &guest->Name);
    host->DomainIndex = guest->DomainIndex;
}

static inline void LSA_TRANSLATED_NAME_h2g(struct qemu_LSA_TRANSLATED_NAME *guest,
        const LSA_TRANSLATED_NAME *host)
{
    guest->Use = host->Use;
    UNICODE_STRING_h2g(&guest->Name, &host->Name);
    guest->DomainIndex = host->DomainIndex;
}

struct qemu_POLICY_AUDIT_EVENTS_INFO
{
    BOOLEAN AuditingMode;
    qemu_ptr EventAuditingOptions; /* POLICY_AUDIT_EVENT_OPTIONS *, aka ULONG * */
    ULONG MaximumAuditEventCount;
};

static inline void POLICY_AUDIT_EVENTS_INFO_g2h(POLICY_AUDIT_EVENTS_INFO *host,
        const struct qemu_POLICY_AUDIT_EVENTS_INFO *guest)
{
    host->AuditingMode = guest->AuditingMode;
    host->EventAuditingOptions = (POLICY_AUDIT_EVENT_OPTIONS *)(ULONG_PTR)guest->EventAuditingOptions;
    host->MaximumAuditEventCount = guest->MaximumAuditEventCount;
}

static inline void POLICY_AUDIT_EVENTS_INFO_h2g(struct qemu_POLICY_AUDIT_EVENTS_INFO *guest,
        const POLICY_AUDIT_EVENTS_INFO *host)
{
    guest->AuditingMode = host->AuditingMode;
    guest->EventAuditingOptions = (ULONG_PTR)host->EventAuditingOptions;
    guest->MaximumAuditEventCount = host->MaximumAuditEventCount;
}

struct qemu_POLICY_PRIMARY_DOMAIN_INFO
{
    struct qemu_UNICODE_STRING Name;
    qemu_ptr Sid;
};

static inline void POLICY_PRIMARY_DOMAIN_INFO_g2h(POLICY_PRIMARY_DOMAIN_INFO *host,
        const struct qemu_POLICY_PRIMARY_DOMAIN_INFO *guest)
{
    UNICODE_STRING_g2h(&host->Name, &guest->Name);
    host->Sid = (PSID)(ULONG_PTR)guest->Sid;
}

static inline void POLICY_PRIMARY_DOMAIN_INFO_h2g(struct qemu_POLICY_PRIMARY_DOMAIN_INFO *guest,
        const POLICY_PRIMARY_DOMAIN_INFO *host)
{
    UNICODE_STRING_h2g(&guest->Name, &host->Name);
    guest->Sid = (ULONG_PTR)host->Sid;
}

struct qemu_POLICY_DNS_DOMAIN_INFO
{
    struct qemu_UNICODE_STRING Name;
    struct qemu_UNICODE_STRING DnsDomainName;
    struct qemu_UNICODE_STRING DnsForestName;
    GUID DomainGuid;
    qemu_ptr Sid;
};

static inline void POLICY_DNS_DOMAIN_INFO_g2h(POLICY_DNS_DOMAIN_INFO *host,
        const struct qemu_POLICY_DNS_DOMAIN_INFO *guest)
{
    UNICODE_STRING_g2h(&host->Name, &guest->Name);
    UNICODE_STRING_g2h(&host->DnsDomainName, &guest->DnsDomainName);
    UNICODE_STRING_g2h(&host->DnsForestName, &guest->DnsForestName);
    host->DomainGuid = guest->DomainGuid;
    host->Sid = (PSID)(ULONG_PTR)guest->Sid;
}

static inline void POLICY_DNS_DOMAIN_INFO_h2g(struct qemu_POLICY_DNS_DOMAIN_INFO *guest,
        const POLICY_DNS_DOMAIN_INFO *host)
{
    UNICODE_STRING_h2g(&guest->Name, &host->Name);
    UNICODE_STRING_h2g(&guest->DnsDomainName, &host->DnsDomainName);
    UNICODE_STRING_h2g(&guest->DnsForestName, &host->DnsForestName);
    guest->DomainGuid = host->DomainGuid;
    guest->Sid = (ULONG_PTR)host->Sid;
}

struct qemu_POLICY_ACCOUNT_DOMAIN_INFO
{
    struct qemu_UNICODE_STRING DomainName;
    qemu_ptr DomainSid;
};

static inline void POLICY_ACCOUNT_DOMAIN_INFO_g2h(POLICY_ACCOUNT_DOMAIN_INFO *host,
        const struct qemu_POLICY_ACCOUNT_DOMAIN_INFO *guest)
{
    UNICODE_STRING_g2h(&host->DomainName, &guest->DomainName);
    host->DomainSid = (PSID)(ULONG_PTR)guest->DomainSid;
}

static inline void POLICY_ACCOUNT_DOMAIN_INFO_h2g(struct qemu_POLICY_ACCOUNT_DOMAIN_INFO *guest,
        const POLICY_ACCOUNT_DOMAIN_INFO *host)
{
    UNICODE_STRING_h2g(&guest->DomainName, &host->DomainName);
    guest->DomainSid = (ULONG_PTR)host->DomainSid;
}

#endif
