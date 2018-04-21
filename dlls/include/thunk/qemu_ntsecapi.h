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

#endif
