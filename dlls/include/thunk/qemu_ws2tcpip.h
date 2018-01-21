#ifndef HAVE_QEMU_WS2TCPIP_H
#define HAVE_QEMU_WS2TCPIP_H

struct qemu_WS_addrinfo
{
    int                 ai_flags;
    int                 ai_family;
    int                 ai_socktype;
    int                 ai_protocol;
    qemu_ptr            ai_addrlen;
    qemu_ptr            ai_canonname;
    qemu_ptr            ai_addr;
    qemu_ptr            ai_next;
};

/* No conv functions, converting the list is a bit more complicated. */

#endif
