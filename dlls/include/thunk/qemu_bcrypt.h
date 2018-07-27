#ifndef HAVE_QEMU_THUNK_BCRYPT_H
#define HAVE_QEMU_THUNK_BCRYPT_H

struct qemu_BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO
{
    ULONG cbSize;
    ULONG dwInfoVersion;
    qemu_ptr pbNonce;
    ULONG cbNonce;
    qemu_ptr pbAuthData;
    ULONG cbAuthData;
    qemu_ptr pbTag;
    ULONG cbTag;
    qemu_ptr pbMacContext;
    ULONG cbMacContext;
    ULONG cbAAD;
    ULONGLONG cbData;
    ULONG dwFlags;
};

static inline void BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO_g2h(BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO *host,
        const struct qemu_BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO *guest)
{
    host->cbSize = sizeof(*host);
    host->dwInfoVersion = guest->dwInfoVersion;
    host->pbNonce = (UCHAR *)(ULONG_PTR)guest->pbNonce;
    host->cbNonce = guest->cbNonce;
    host->pbAuthData = (UCHAR *)(ULONG_PTR)guest->pbAuthData;
    host->cbAuthData = guest->cbAuthData;
    host->pbTag = (UCHAR *)(ULONG_PTR)guest->pbTag;
    host->cbTag = guest->cbTag;
    host->pbMacContext = (UCHAR *)(ULONG_PTR)guest->pbMacContext;
    host->cbMacContext = guest->cbMacContext;
    host->cbAAD = guest->cbAAD;
    host->cbData = guest->cbData;
    host->dwFlags = guest->dwFlags;
}

#endif
