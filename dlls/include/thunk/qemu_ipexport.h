#ifndef HAVE_QEMU_THUNK_IPEXPORT_H
#define HAVE_QEMU_THUNK_IPEXPORT_H

struct qemu_IP_OPTION_INFORMATION
{
    unsigned char  Ttl;
    unsigned char  Tos;
    unsigned char  Flags;
    unsigned char  OptionsSize;
    qemu_ptr OptionsData;
};

static inline void IP_OPTION_INFORMATION_g2h(IP_OPTION_INFORMATION *host, const struct qemu_IP_OPTION_INFORMATION *guest)
{
    host->Ttl = guest->Ttl;
    host->Tos = guest->Tos;
    host->Flags = guest->Flags;
    host->OptionsSize = guest->OptionsSize;
    host->OptionsData = (char *)(ULONG_PTR)guest->OptionsData;
}

#endif
