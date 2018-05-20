#ifndef HAVE_QEMU_THUNK_WINCRYPT_H
#define HAVE_QEMU_THUNK_WINCRYPT_H

struct qemu_CERT_CONTEXT
{
    DWORD      dwCertEncodingType;
    qemu_ptr   pbCertEncoded; /* BYTE * */
    DWORD      cbCertEncoded;
    qemu_ptr   pCertInfo; /* CERT_INFO * */
    qemu_ptr   hCertStore; /* HCERTSTORE */
};

static inline void CERT_CONTEXT_g2h(CERT_CONTEXT *host, const struct qemu_CERT_CONTEXT *guest)
{
    host->dwCertEncodingType = guest->dwCertEncodingType;
    host->pbCertEncoded = (BYTE *)(ULONG_PTR)guest->pbCertEncoded;
    host->cbCertEncoded = guest->cbCertEncoded;
    host->pCertInfo = (CERT_INFO *)(ULONG_PTR)guest->pCertInfo;
    host->hCertStore = (HCERTSTORE)(ULONG_PTR)guest->hCertStore;
}

static inline void CERT_CONTEXT_h2g(struct qemu_CERT_CONTEXT *guest, const CERT_CONTEXT *host)
{
    guest->dwCertEncodingType = host->dwCertEncodingType;
    guest->pbCertEncoded = (ULONG_PTR)host->pbCertEncoded;
    guest->cbCertEncoded = host->cbCertEncoded;
    guest->pCertInfo = (ULONG_PTR)host->pCertInfo;
    guest->hCertStore = (ULONG_PTR)host->hCertStore;
}

struct qemu_CRYPT_DATA_BLOB
{
    DWORD       cbData;
    qemu_ptr    pbData;
};

static inline void CRYPT_DATA_BLOB_g2h(CRYPT_DATA_BLOB *host, const struct qemu_CRYPT_DATA_BLOB *guest)
{
    host->cbData = guest->cbData;
    host->pbData = (BYTE *)(ULONG_PTR)guest->pbData;
}

static inline void CRYPT_DATA_BLOB_h2g(struct qemu_CRYPT_DATA_BLOB *guest, const CRYPT_DATA_BLOB *host)
{
    guest->cbData = host->cbData;
    guest->pbData = (ULONG_PTR)host->pbData;
}

struct qemu_CERT_KEY_CONTEXT
{
    DWORD       cbSize;
    qemu_ptr    hCryptProv;
    DWORD       dwKeySpec;
};

static inline void CERT_KEY_CONTEXT_g2h(CERT_KEY_CONTEXT *host, const struct qemu_CERT_KEY_CONTEXT *guest)
{
    host->cbSize = sizeof(*host);
    host->hCryptProv = (HCRYPTPROV)(ULONG_PTR)guest->hCryptProv;
    host->dwKeySpec = guest->dwKeySpec;
}

static inline void CERT_KEY_CONTEXT_h2g(struct qemu_CERT_KEY_CONTEXT *guest, const CERT_KEY_CONTEXT *host)
{
    guest->hCryptProv = (ULONG_PTR)host->hCryptProv;
    guest->dwKeySpec = host->dwKeySpec;
}

struct qemu_CRYPT_ALGORITHM_IDENTIFIER
{
    qemu_ptr              pszObjId;
    struct qemu_CRYPT_DATA_BLOB  Parameters;
};

static inline void CRYPT_ALGORITHM_IDENTIFIER_g2h(CRYPT_ALGORITHM_IDENTIFIER *host,
        const struct qemu_CRYPT_ALGORITHM_IDENTIFIER *guest)
{
    host->pszObjId = (char *)(ULONG_PTR)guest->pszObjId;
    CRYPT_DATA_BLOB_g2h(&host->Parameters, &guest->Parameters);
}

static inline void CRYPT_ALGORITHM_IDENTIFIER_h2g(struct qemu_CRYPT_ALGORITHM_IDENTIFIER *guest,
        const CRYPT_ALGORITHM_IDENTIFIER *host)
{
    guest->pszObjId = (ULONG_PTR)host->pszObjId;
    CRYPT_DATA_BLOB_h2g(&guest->Parameters, &host->Parameters);
}

struct qemu_CRYPT_BIT_BLOB
{
    DWORD       cbData;
    qemu_ptr    pbData;
    DWORD       cUnusedBits;
};

static inline void CRYPT_BIT_BLOB_g2h(CRYPT_BIT_BLOB *host, const struct qemu_CRYPT_BIT_BLOB *guest)
{
    host->cbData = guest->cbData;
    host->pbData = (BYTE *)(ULONG_PTR)guest->pbData;
    host->cUnusedBits = guest->cUnusedBits;
}

static inline void CRYPT_BIT_BLOB_h2g(struct qemu_CRYPT_BIT_BLOB *guest, const CRYPT_BIT_BLOB *host)
{
    guest->cbData = host->cbData;
    guest->pbData = (ULONG_PTR)host->pbData;
    guest->cUnusedBits = host->cUnusedBits;
}

struct qemu_CERT_PUBLIC_KEY_INFO
{
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER Algorithm;
    struct qemu_CRYPT_BIT_BLOB             PublicKey;
};

static inline void CERT_PUBLIC_KEY_INFO_g2h(CERT_PUBLIC_KEY_INFO *host, const struct qemu_CERT_PUBLIC_KEY_INFO *guest)
{
    CRYPT_ALGORITHM_IDENTIFIER_g2h(&host->Algorithm, &guest->Algorithm);
    CRYPT_BIT_BLOB_g2h(&host->PublicKey, &guest->PublicKey);
}

static inline void CERT_PUBLIC_KEY_INFO_h2g(struct qemu_CERT_PUBLIC_KEY_INFO *guest, const CERT_PUBLIC_KEY_INFO *host)
{
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->Algorithm, &host->Algorithm);
    CRYPT_BIT_BLOB_h2g(&guest->PublicKey, &host->PublicKey);
}

struct qemu_CERT_INFO
{
    DWORD                                   dwVersion;
    struct qemu_CRYPT_DATA_BLOB             SerialNumber;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm;
    struct qemu_CRYPT_DATA_BLOB             Issuer;
    FILETIME                                NotBefore;
    FILETIME                                NotAfter;
    struct qemu_CRYPT_DATA_BLOB             Subject;
    struct qemu_CERT_PUBLIC_KEY_INFO        SubjectPublicKeyInfo;
    struct qemu_CRYPT_BIT_BLOB              IssuerUniqueId;
    struct qemu_CRYPT_BIT_BLOB              SubjectUniqueId;
    DWORD                                   cExtension;
    qemu_ptr                                rgExtension;
};

static inline void CERT_INFO_g2h(CERT_INFO *host, const struct qemu_CERT_INFO *guest)
{
    host->dwVersion = guest->dwVersion;
    CRYPT_DATA_BLOB_g2h(&host->SerialNumber, &guest->SerialNumber);
    CRYPT_ALGORITHM_IDENTIFIER_g2h(&host->SignatureAlgorithm, &guest->SignatureAlgorithm);
    CRYPT_DATA_BLOB_g2h(&host->Issuer, &guest->Issuer);
    host->NotBefore = guest->NotBefore;
    host->NotAfter = guest->NotAfter;
    CRYPT_DATA_BLOB_g2h(&host->Subject, &guest->Subject);
    CERT_PUBLIC_KEY_INFO_g2h(&host->SubjectPublicKeyInfo, &guest->SubjectPublicKeyInfo);
    CRYPT_BIT_BLOB_g2h(&host->IssuerUniqueId, &guest->IssuerUniqueId);
    CRYPT_BIT_BLOB_g2h(&host->SubjectUniqueId, &guest->SubjectUniqueId);
    host->cExtension = guest->cExtension;
    host->rgExtension = (PCERT_EXTENSION)(ULONG_PTR)guest->rgExtension; /* FIXME */
}

static inline void CERT_INFO_h2g(struct qemu_CERT_INFO *guest, const CERT_INFO *host)
{
    guest->dwVersion = host->dwVersion;
    CRYPT_DATA_BLOB_h2g(&guest->SerialNumber, &host->SerialNumber);
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->SignatureAlgorithm, &host->SignatureAlgorithm);
    CRYPT_DATA_BLOB_h2g(&guest->Issuer, &host->Issuer);
    guest->NotBefore = host->NotBefore;
    guest->NotAfter = host->NotAfter;
    CRYPT_DATA_BLOB_h2g(&guest->Subject, &host->Subject);
    CERT_PUBLIC_KEY_INFO_h2g(&guest->SubjectPublicKeyInfo, &host->SubjectPublicKeyInfo);
    CRYPT_BIT_BLOB_h2g(&guest->IssuerUniqueId, &host->IssuerUniqueId);
    CRYPT_BIT_BLOB_h2g(&guest->SubjectUniqueId, &host->SubjectUniqueId);
    guest->cExtension = host->cExtension;
    guest->rgExtension = (ULONG_PTR)host->rgExtension; /* FIXME */
}

#endif
