#ifndef HAVE_QEMU_THUNK_SSPI_H
#define HAVE_QEMU_THUNK_SSPI_H

struct qemu_SecPkgInfo
{
    ULONG      fCapabilities;
    USHORT     wVersion;
    USHORT     wRPCID;
    ULONG      cbMaxToken;
    qemu_ptr   Name;
    qemu_ptr   Comment;
};

static inline void SecPkgInfo_h2g(struct qemu_SecPkgInfo *guest, const SecPkgInfoW *host)
{
    guest->fCapabilities = host->fCapabilities;
    guest->wVersion = host->wVersion;
    guest->wRPCID = host->wRPCID;
    guest->cbMaxToken = host->cbMaxToken;
    guest->Name = (ULONG_PTR)host->Name;
    guest->Comment = (ULONG_PTR)host->Comment;
}

struct qemu_SecHandle
{
    qemu_ptr dwLower;
    qemu_ptr dwUpper;
};

static inline void SecHandle_h2g(struct qemu_SecHandle *guest, const SecHandle *host)
{
    guest->dwLower = host->dwLower;
    guest->dwUpper = host->dwUpper;
}

#endif
