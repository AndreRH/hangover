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

struct qemu_TBADDBITMAP
{
    qemu_handle hInst;
    qemu_ptr    nID;
};

static inline void TBADDBITMAP_g2h(TBADDBITMAP *host, const struct qemu_TBADDBITMAP *guest)
{
    host->hInst = HANDLE_g2h(guest->hInst);
    host->nID = guest->nID;
}

struct qemu_TBBUTTON
{
    INT         iBitmap;
    INT         idCommand;
    BYTE        fsState;
    BYTE        fsStyle;
    BYTE        bReserved[2];
    qemu_ptr    dwData;
    qemu_sptr   iString;
};

static inline void TBBUTTON_g2h(TBBUTTON *host, const struct qemu_TBBUTTON *guest)
{
    host->iBitmap = guest->iBitmap;
    host->idCommand = guest->idCommand;
    host->fsState = guest->fsState;
    host->fsStyle = guest->fsStyle;
    memset(&host->bReserved, 0, sizeof(host->bReserved));
    host->dwData = guest->dwData;
    host->iString = guest->iString;
}

#endif
