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

static inline void SecHandle_g2h(SecHandle *host, const struct qemu_SecHandle *guest)
{
    host->dwLower = guest->dwLower;
    host->dwUpper = guest->dwUpper;
}

struct qemu_SecBuffer
{
    ULONG cbBuffer;
    ULONG BufferType;
    qemu_ptr pvBuffer;
};

static inline void SecBuffer_h2g(struct qemu_SecBuffer *guest, const SecBuffer *host)
{
    guest->cbBuffer = host->cbBuffer;
    guest->BufferType = host->BufferType;
    guest->pvBuffer = (ULONG_PTR)host->pvBuffer;
}

static inline void SecBuffer_g2h(SecBuffer *host, const struct qemu_SecBuffer *guest)
{
    host->cbBuffer = guest->cbBuffer;
    host->BufferType = guest->BufferType;
    host->pvBuffer = (void *)(ULONG_PTR)guest->pvBuffer;
}

struct qemu_SecBufferDesc
{
    ULONG      ulVersion;
    ULONG      cBuffers;
    qemu_ptr   pBuffers;
};

/* Note: The caller has to convert the pvBuffer array. */
static inline void SecBufferDesc_h2g(struct qemu_SecBufferDesc *guest, const SecBufferDesc *host)
{
    guest->ulVersion = host->ulVersion;
    guest->cBuffers = host->cBuffers;
    guest->pBuffers = (ULONG_PTR)host->pBuffers;
}

static inline void SecBufferDesc_g2h(SecBufferDesc *host, const struct qemu_SecBufferDesc *guest)
{
    host->ulVersion = guest->ulVersion;
    host->cBuffers = guest->cBuffers;
    host->pBuffers = (void *)(ULONG_PTR)guest->pBuffers;
}

#endif
