#ifndef HAVE_QEMU_COMMCTRL_H
#define HAVE_QEMU_COMMCTRL_H

struct qemu_REBARINFO
{
    UINT        cbSize;
    UINT        fMask;
    qemu_handle himl;
};

static inline void REBARINFO_g2h(REBARINFO *host, const struct qemu_REBARINFO *guest)
{
    host->cbSize = sizeof(*host);
    host->fMask = guest->fMask;
    host->himl = HANDLE_g2h(guest->himl);
}

#endif
