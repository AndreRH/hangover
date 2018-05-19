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

#endif
