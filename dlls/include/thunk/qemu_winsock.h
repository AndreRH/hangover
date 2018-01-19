#ifndef HAVE_QEMU_WINSOCK_H
#define HAVE_QEMU_WINSOCK_H

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
#endif
