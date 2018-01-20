#ifndef HAVE_QEMU_WINSOCK2_H
#define HAVE_QEMU_WINSOCK2_H

#include "thunk/qemu_ws2def.h"

struct qemu_WSAPOLLFD
{
    qemu_ptr    fd;
    SHORT       events;
    SHORT       revents;
};

static inline void WSAPOLLFD_g2h(WSAPOLLFD *host, const struct qemu_WSAPOLLFD *guest)
{
    host->fd = guest->fd;
    host->events = guest->events;
    host->revents = guest->revents;
}

static inline void WSAPOLLFD_h2g(struct qemu_WSAPOLLFD *guest, const WSAPOLLFD *host)
{
    guest->fd = host->fd;
    guest->events = host->events;
    guest->revents = host->revents;
}

#endif
