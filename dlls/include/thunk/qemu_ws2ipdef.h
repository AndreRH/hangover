#ifndef HAVE_QEMU_WS2IPDEF_H
#define HAVE_QEMU_WS2IPDEF_H

struct qemu_SOCKADDR_IN6_PAIR
{
    qemu_ptr SourceAddress;
    qemu_ptr DestinationAddress;
};

static inline void SOCKADDR_IN6_PAIR_h2g(struct qemu_SOCKADDR_IN6_PAIR *guest, const SOCKADDR_IN6_PAIR *host)
{
    guest->SourceAddress = (ULONG_PTR)host->SourceAddress;
    guest->DestinationAddress = (ULONG_PTR)host->DestinationAddress;
}

#endif
