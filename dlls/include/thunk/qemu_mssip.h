#ifndef HAVE_QEMU_THUNK_MSSIP_H
#define HAVE_QEMU_THUNK_MSSIP_H

#include <pshpack8.h>
struct qemu_SIP_SUBJECTINFO
{
    DWORD cbSize;
    qemu_ptr pgSubjectType;
    qemu_ptr hFile;
    qemu_ptr pwsFileName;
    qemu_ptr pwsDisplayName;
    
    DWORD dwReserved1;
    DWORD dwIntVersion;
    
    qemu_ptr hProv;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER DigestAlgorithm;
    DWORD dwFlags;
    DWORD dwEncodingType;
    DWORD dwReserved2;
    DWORD fdwCAPISettings;
    DWORD fdwSecuritySettings;
    DWORD dwIndex;
    
    DWORD dwUnionChoice;
    union {
        qemu_ptr            psFlat;
        qemu_ptr            psCatMember;
        qemu_ptr            psBlob;
    } u1;
    
    qemu_ptr pClientData;
};
#include <poppack.h>

static void SIP_SUBJECTINFO_g2h(SIP_SUBJECTINFO *host, const struct qemu_SIP_SUBJECTINFO *guest)
{
    host->cbSize = sizeof(*host);
    host->pgSubjectType = (GUID *)(ULONG_PTR)guest->pgSubjectType;
    host->hFile = (HANDLE)(ULONG_PTR)guest->hFile;
    host->pwsFileName = (const WCHAR *)(ULONG_PTR)guest->pwsFileName;
    host->pwsDisplayName = (const WCHAR *)(ULONG_PTR)guest->pwsDisplayName;
    host->dwReserved1 = guest->dwReserved1;
    host->dwIntVersion = guest->dwIntVersion;
    host->hProv = (HCRYPTPROV)(ULONG_PTR)guest->hProv;
    CRYPT_ALGORITHM_IDENTIFIER_g2h(&host->DigestAlgorithm, &guest->DigestAlgorithm);
    host->dwFlags = guest->dwFlags;
    host->dwEncodingType = guest->dwEncodingType;
    host->dwReserved2 = guest->dwReserved2;
    host->fdwCAPISettings = guest->fdwCAPISettings;
    host->fdwSecuritySettings = guest->fdwSecuritySettings;
    host->dwIndex = guest->dwIndex;

    host->dwUnionChoice = guest->dwUnionChoice;
    host->psFlat = (void *)(ULONG_PTR)guest->u1.psFlat; /* FIXME */

    host->pClientData = (void *)(ULONG_PTR)guest->pClientData;
}

#include <pshpack8.h>
struct qemu_SIP_INDIRECT_DATA
{
    struct qemu_CRYPT_ATTRIBUTE_TYPE_VALUE Data;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER DigestAlgorithm;
    struct qemu_CRYPT_DATA_BLOB            Digest;
};
#include <poppack.h>

static void SIP_INDIRECT_DATA_h2g(struct qemu_SIP_INDIRECT_DATA *guest, const SIP_INDIRECT_DATA *host)
{
    CRYPT_ATTRIBUTE_TYPE_VALUE_h2g(&guest->Data, &host->Data);
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->DigestAlgorithm, &host->DigestAlgorithm);
    CRYPT_DATA_BLOB_h2g(&guest->Digest, &host->Digest);
}

#endif
