#ifndef HAVE_QEMU_MSWSOCK_H
#define HAVE_QEMU_MSWSOCK_H

struct qemu_TRANSMIT_FILE_BUFFERS
{
    qemu_ptr    Head;
    DWORD       HeadLength;
    qemu_ptr    Tail;
    DWORD       TailLength;
};

static inline void TRANSMIT_FILE_BUFFERS_g2h(TRANSMIT_FILE_BUFFERS *host,
        const struct qemu_TRANSMIT_FILE_BUFFERS *guest)
{
    host->Head = (void *)(ULONG_PTR)guest->Head;
    host->HeadLength = guest->HeadLength;
    host->Tail = (void *)(ULONG_PTR)guest->Tail;
    host->TailLength = guest->TailLength;
}

#endif
