#ifndef HAVE_QEMU_WINCRED_H
#define HAVE_QEMU_WINCRED_H

struct qemu_CREDENTIAL
{
    DWORD Flags;
    DWORD Type;
    qemu_ptr TargetName;
    qemu_ptr Comment;
    FILETIME LastWritten;
    DWORD CredentialBlobSize;
    qemu_ptr CredentialBlob;
    DWORD Persist;
    DWORD AttributeCount;
    qemu_ptr Attributes;
    qemu_ptr TargetAlias;
    qemu_ptr UserName;
};

static inline void CREDENTIAL_g2h(CREDENTIALW *host, const struct qemu_CREDENTIAL *guest)
{
    host->Flags = guest->Flags;
    host->Type = guest->Type;
    host->TargetName = (WCHAR *)(ULONG_PTR)guest->TargetName;
    host->Comment = (WCHAR *)(ULONG_PTR)guest->Comment;
    host->LastWritten = guest->LastWritten;
    host->CredentialBlobSize = guest->CredentialBlobSize;
    host->CredentialBlob = (void *)(ULONG_PTR)guest->CredentialBlob;
    host->Persist = guest->Persist;
    host->AttributeCount = guest->AttributeCount;
    host->Attributes = (CREDENTIAL_ATTRIBUTEW *)(ULONG_PTR)guest->Attributes;
    host->TargetAlias = (WCHAR *)(ULONG_PTR)guest->TargetAlias;
    host->UserName = (WCHAR *)(ULONG_PTR)guest->UserName;
}

static inline void CREDENTIAL_h2g(struct qemu_CREDENTIAL *guest, CREDENTIALW *host)
{
    guest->Flags = host->Flags;
    guest->Type = host->Type;
    guest->TargetName = (ULONG_PTR)host->TargetName;
    guest->Comment = (ULONG_PTR)host->Comment;
    guest->LastWritten = host->LastWritten;
    guest->CredentialBlobSize = host->CredentialBlobSize;
    guest->CredentialBlob = (ULONG_PTR)host->CredentialBlob;
    guest->Persist = host->Persist;
    guest->AttributeCount = host->AttributeCount;
    guest->Attributes = (ULONG_PTR)host->Attributes;
    guest->TargetAlias = (ULONG_PTR)host->TargetAlias;
    guest->UserName = (ULONG_PTR)host->UserName;
}

struct qemu_USERNAME_TARGET_CREDENTIAL_INFO
{
    qemu_ptr UserName;
};

static inline void USERNAME_TARGET_CREDENTIAL_INFO_g2h(USERNAME_TARGET_CREDENTIAL_INFO *host,
        const struct qemu_USERNAME_TARGET_CREDENTIAL_INFO *guest)
{
    host->UserName = (WCHAR *)(ULONG_PTR)guest->UserName;
}

static inline void USERNAME_TARGET_CREDENTIAL_INFO_h2g(struct qemu_USERNAME_TARGET_CREDENTIAL_INFO *guest,
        USERNAME_TARGET_CREDENTIAL_INFO *host)
{
    guest->UserName = (ULONG_PTR)host->UserName;
}

#ifndef QEMU_DLL_GUEST
struct qemu_BINARY_BLOB_CREDENTIAL_INFO
{
    ULONG cbBlob;
    qemu_ptr pbBlob;
};

static inline void BINARY_BLOB_CREDENTIAL_INFO_g2h(BINARY_BLOB_CREDENTIAL_INFO *host,
        const struct qemu_BINARY_BLOB_CREDENTIAL_INFO *guest)
{
    host->cbBlob = guest->cbBlob;
    host->pbBlob = (void *)(ULONG_PTR)guest->pbBlob;
}

static inline void BINARY_BLOB_CREDENTIAL_INFO_h2g(struct qemu_BINARY_BLOB_CREDENTIAL_INFO *guest,
        BINARY_BLOB_CREDENTIAL_INFO *host)
{
    guest->cbBlob = host->cbBlob;
    guest->pbBlob = (ULONG_PTR)host->pbBlob;
}
#endif

#endif
