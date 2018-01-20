#ifndef HAVE_QEMU_WINSOCK_H
#define HAVE_QEMU_WINSOCK_H

static inline uint64_t guest_SOCKET_g2h(SOCKET s)
{
#if GUEST_BIT == HOST_BIT
    return s;
#else
    if (s == INVALID_SOCKET)
        return (LONG_PTR)s;
    else
        return (ULONG_PTR)s;
#endif
}


struct qemu_WS_hostent
{
    qemu_ptr h_name;               /* official name of host - char * */
    qemu_ptr h_aliases;            /* alias list - char  ** */
    short h_addrtype;              /* host address type */
    short h_length;                /* length of address */
    qemu_ptr h_addr_list;          /* list of addresses from name server - char ** */
};

struct qemu_WSADATA
{
    WORD                    wVersion;
    WORD                    wHighVersion;
    char                    szDescription[WSADESCRIPTION_LEN+1];
    char                    szSystemStatus[WSASYS_STATUS_LEN+1];
    WORD                    iMaxSockets;
    WORD                    iMaxUdpDg;
    qemu_ptr                lpVendorInfo;
};

static inline void WSADATA_g2h(WSADATA *host, const struct qemu_WSADATA *guest)
{
    host->wVersion = guest->wVersion;
    host->wHighVersion = guest->wHighVersion;
    memcpy(host->szDescription, guest->szDescription, sizeof(host->szDescription));
    memcpy(host->szSystemStatus, guest->szSystemStatus, sizeof(host->szSystemStatus));
    host->iMaxSockets = guest->iMaxSockets;
    host->iMaxUdpDg = guest->iMaxUdpDg;
    host->lpVendorInfo = (char *)(ULONG_PTR)guest->lpVendorInfo;
}

static inline void WSADATA_h2g(struct qemu_WSADATA *guest, const WSADATA *host)
{
    guest->wVersion = host->wVersion;
    guest->wHighVersion = host->wHighVersion;
    memcpy(guest->szDescription, host->szDescription, sizeof(guest->szDescription));
    memcpy(guest->szSystemStatus, host->szSystemStatus, sizeof(guest->szSystemStatus));
    guest->iMaxSockets = host->iMaxSockets;
    guest->iMaxUdpDg = host->iMaxUdpDg;
    guest->lpVendorInfo = (ULONG_PTR)host->lpVendorInfo;
}

struct qemu_WS_fd_set
{
#ifndef USE_WS_PREFIX
    u_int fd_count;                 /* how many are SET? */
#else
    WS_u_int fd_count;                 /* how many are SET? */
#endif
# ifndef USE_WS_PREFIX
    qemu_ptr fd_array[FD_SETSIZE];      /* an array of SOCKETs */
# else
    qemu_ptr fd_array[WS_FD_SETSIZE];   /* an array of SOCKETs */
# endif
};

#ifndef USE_WS_PREFIX
static inline void WS_fd_set_g2h(fd_set *host, const struct qemu_WS_fd_set *guest)
#else
static inline void WS_fd_set_g2h(WS_fd_set *host, const struct qemu_WS_fd_set *guest)
#endif
{
    unsigned int i;
    host->fd_count = guest->fd_count;
    for (i = 0; i < host->fd_count; ++i)
    {
        if (guest->fd_array[i] == (qemu_ptr)INVALID_SOCKET)
            host->fd_array[i] = INVALID_SOCKET;
        else
            host->fd_array[i] = (ULONG_PTR)guest->fd_array[i];
    }
}

#ifndef USE_WS_PREFIX
static inline void WS_fd_set_h2g(struct qemu_WS_fd_set *guest, const fd_set *host)
#else
static inline void WS_fd_set_h2g(struct qemu_WS_fd_set *guest, const WS_fd_set *host)
#endif
{
    unsigned int i;
    guest->fd_count = host->fd_count;
    for (i = 0; i < guest->fd_count; ++i)
        guest->fd_array[i] = host->fd_array[i];
}

struct qemu_WS_servent
{
    qemu_ptr s_name;        /* official service name - char * */
    qemu_ptr s_aliases;     /* alias list - char ** */
    short s_port;           /* port # */
    qemu_ptr s_proto;       /* protocol to use - char * */
};

#endif
