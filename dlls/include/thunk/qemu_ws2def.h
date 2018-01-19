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

#endif
