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

struct qemu_REBARBANDINFO
{
    UINT    cbSize;
    UINT    fMask;
    UINT    fStyle;
    COLORREF  clrFore;
    COLORREF  clrBack;
    qemu_ptr    lpText;
    UINT    cch;
    INT     iImage;
    qemu_handle    hwndChild;
    UINT    cxMinChild;
    UINT    cyMinChild;
    UINT    cx;
    qemu_handle hbmBack;
    UINT    wID;
    UINT    cyChild;
    UINT    cyMaxChild;
    UINT    cyIntegral;
    UINT    cxIdeal;
    qemu_ptr    lParam;
    UINT    cxHeader;
    /* _WIN32_WINNT >= 0x0600 */
    RECT    rcChevronLocation;
    UINT    uChevronState;
};

static inline void REBARBANDINFO_g2h(REBARBANDINFOW *host, const struct qemu_REBARBANDINFO *guest)
{
    host->cbSize = sizeof(*host);
    host->fMask = guest->fMask;
    host->fStyle = guest->fStyle;
    host->clrFore = guest->clrFore;
    host->clrBack = guest->clrBack;
    host->lpText = (WCHAR *)(ULONG_PTR)guest->lpText;
    host->cch = guest->cch;
    host->iImage = guest->iImage;
    host->hwndChild = HANDLE_g2h(guest->hwndChild);
    host->cxMinChild = guest->cxMinChild;
    host->cyMinChild = guest->cyMinChild;
    host->cx = guest->cx;
    host->hbmBack = HANDLE_g2h(guest->hbmBack);
    host->wID = guest->wID;
    host->cyChild = guest->cyChild;
    host->cyMaxChild = guest->cyMaxChild;
    host->cyIntegral = guest->cyIntegral;
    host->cxIdeal = guest->cxIdeal;
    host->lParam = guest->lParam;
    host->cxHeader = guest->cxHeader;
    host->rcChevronLocation.left = guest->rcChevronLocation.left;
    host->rcChevronLocation.top = guest->rcChevronLocation.top;
    host->rcChevronLocation.right = guest->rcChevronLocation.right;
    host->rcChevronLocation.bottom = guest->rcChevronLocation.bottom;
    host->uChevronState = guest->uChevronState;
}

struct qemu_NMREBARCHILDSIZE
{
    struct qemu_NMHDR  hdr;
    UINT uBand;
    UINT wID;
    RECT rcChild;
    RECT rcBand;
};

static inline void NMREBARCHILDSIZE_h2g(struct qemu_NMREBARCHILDSIZE *guest, const NMREBARCHILDSIZE *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->uBand = host->uBand;
    guest->wID = host->wID;
    memcpy(&guest->rcChild, &host->rcChild, sizeof(guest->rcChild));
    memcpy(&guest->rcBand, &host->rcBand, sizeof(guest->rcBand));
}

#endif
