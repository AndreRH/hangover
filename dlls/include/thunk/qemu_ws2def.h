#ifndef HAVE_QEMU_WS2DEF_H
#define HAVE_QEMU_WS2DEF_H
struct qemu_SOCKET_ADDRESS
{
        qemu_ptr        lpSockaddr;
        INT             iSockaddrLength;
};

static inline void SOCKET_ADDRESS_g2h(SOCKET_ADDRESS *host, const struct qemu_SOCKET_ADDRESS *guest)
{
    host->lpSockaddr = (SOCKADDR *)(ULONG_PTR)guest->lpSockaddr;
    host->iSockaddrLength = guest->iSockaddrLength;
}

static inline void SOCKET_ADDRESS_h2g(struct qemu_SOCKET_ADDRESS *guest, const SOCKET_ADDRESS *host)
{
    guest->lpSockaddr = (ULONG_PTR)host->lpSockaddr;
    guest->iSockaddrLength = host->iSockaddrLength;
}

struct qemu_CSADDR_INFO
{
        struct qemu_SOCKET_ADDRESS  LocalAddr;
        struct qemu_SOCKET_ADDRESS  RemoteAddr;
        INT                         iSocketType;
        INT                         iProtocol;
};

static inline void CSADDR_INFO_g2h(CSADDR_INFO *host, const struct qemu_CSADDR_INFO *guest)
{
    SOCKET_ADDRESS_g2h(&host->LocalAddr, &guest->LocalAddr);
    SOCKET_ADDRESS_g2h(&host->RemoteAddr, &guest->RemoteAddr);
    host->iSocketType = guest->iSocketType;
    host->iProtocol = guest->iProtocol;
}

static inline void CSADDR_INFO_h2g(struct qemu_CSADDR_INFO *guest, const CSADDR_INFO *host)
{
    SOCKET_ADDRESS_h2g(&guest->LocalAddr, &host->LocalAddr);
    SOCKET_ADDRESS_h2g(&guest->RemoteAddr, &host->RemoteAddr);
    guest->iSocketType = host->iSocketType;
    guest->iProtocol = host->iProtocol;
}

struct qemu_WSABUF
{
    ULONG       len;
    qemu_ptr    buf;
};

static inline void WSABUF_g2h(WSABUF *host, const struct qemu_WSABUF *guest)
{
    host->len = guest->len;
    host->buf = (CHAR *)(ULONG_PTR)guest->buf;
}

static inline void WSABUF_h2g(struct qemu_WSABUF *guest, const WSABUF *host)
{
    guest->len = host->len;
    guest->buf = (ULONG_PTR)host->buf;
}

struct qemu_WSAMSG
{
    qemu_ptr            name;
    INT                 namelen;
    qemu_ptr            lpBuffers;
    DWORD               dwBufferCount;
    struct qemu_WSABUF  Control;
    DWORD               dwFlags;
};

static inline void WSAMSG_g2h(WSAMSG *host, const struct qemu_WSAMSG *guest)
{
    host->name = (SOCKADDR *)(ULONG_PTR)guest->name; /* SOCKADDR is compatible */
    host->namelen = guest->namelen;
    host->lpBuffers = (WSABUF *)(ULONG_PTR)guest->lpBuffers;
    host->dwBufferCount = guest->dwBufferCount;
    WSABUF_g2h(&host->Control, &guest->Control);
    host->dwFlags = guest->dwFlags;
}

static inline void WSAMSG_h2g(struct qemu_WSAMSG *guest, const WSAMSG *host)
{
    guest->name = (ULONG_PTR)host->name; /* SOCKADDR is compatible */
    guest->namelen = host->namelen;
    guest->lpBuffers = (ULONG_PTR)host->lpBuffers;
    guest->dwBufferCount = host->dwBufferCount;
    WSABUF_h2g(&guest->Control, &host->Control);
    guest->dwFlags = host->dwFlags;
}

#endif
