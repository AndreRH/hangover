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

static inline void NMREBARCHILDSIZE_g2h(NMREBARCHILDSIZE *host, const struct qemu_NMREBARCHILDSIZE *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->uBand = guest->uBand;
    host->wID = guest->wID;
    memcpy(&host->rcChild, &guest->rcChild, sizeof(host->rcChild));
    memcpy(&host->rcBand, &guest->rcBand, sizeof(host->rcBand));
}

struct qemu_NMRBAUTOSIZE
{
    struct qemu_NMHDR hdr;
    BOOL fChanged;
    RECT rcTarget;
    RECT rcActual;
};

static inline void NMRBAUTOSIZE_h2g(struct qemu_NMRBAUTOSIZE *guest, const NMRBAUTOSIZE *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->fChanged = host->fChanged;
    memcpy(&guest->rcTarget, &host->rcTarget, sizeof(guest->rcTarget));
    memcpy(&guest->rcActual, &host->rcActual, sizeof(guest->rcActual));
}

static inline void NMRBAUTOSIZE_g2h(NMRBAUTOSIZE *host, const struct qemu_NMRBAUTOSIZE *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->fChanged = guest->fChanged;
    memcpy(&host->rcTarget, &guest->rcTarget, sizeof(host->rcTarget));
    memcpy(&host->rcActual, &guest->rcActual, sizeof(host->rcActual));
}

struct qemu_NMCUSTOMDRAW
{
    struct qemu_NMHDR   hdr;
    DWORD               dwDrawStage;
    qemu_handle         hdc;
    RECT                rc;
    qemu_ptr            dwItemSpec;
    UINT                uItemState;
    qemu_ptr            lItemlParam;
};

static inline void NMCUSTOMDRAW_h2g(struct qemu_NMCUSTOMDRAW *guest, const NMCUSTOMDRAW *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->dwDrawStage = host->dwDrawStage;
    guest->hdc = (ULONG_PTR)host->hdc;
    memcpy(&guest->rc, &host->rc, sizeof(guest->rc));
    guest->dwItemSpec = host->dwItemSpec;
    guest->uItemState = host->uItemState;
    guest->lItemlParam = host->lItemlParam;
}

static inline void NMCUSTOMDRAW_g2h(NMCUSTOMDRAW *host, const struct qemu_NMCUSTOMDRAW *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->dwDrawStage = guest->dwDrawStage;
    host->hdc = (HDC)HANDLE_g2h(guest->hdc);
    memcpy(&host->rc, &guest->rc, sizeof(host->rc));
    host->dwItemSpec = guest->dwItemSpec;
    host->uItemState = guest->uItemState;
    host->lItemlParam = guest->lItemlParam;
}

struct qemu_NMTBCUSTOMDRAW
{
    struct qemu_NMCUSTOMDRAW nmcd;
    qemu_handle hbrMonoDither;
    qemu_handle hbrLines;
    qemu_handle hpenLines;
    COLORREF clrText;
    COLORREF clrMark;
    COLORREF clrTextHighlight;
    COLORREF clrBtnFace;
    COLORREF clrBtnHighlight;
    COLORREF clrHighlightHotTrack;
    RECT rcText;
    int nStringBkMode;
    int nHLStringBkMode;
    int iListGap;
};

static inline void NMTBCUSTOMDRAW_h2g(struct qemu_NMTBCUSTOMDRAW *guest, const NMTBCUSTOMDRAW *host)
{
    NMCUSTOMDRAW_h2g(&guest->nmcd, &host->nmcd);
    guest->hbrMonoDither = (ULONG_PTR)host->hbrMonoDither;
    guest->hbrLines = (ULONG_PTR)host->hbrLines;
    guest->hpenLines = (ULONG_PTR)host->hpenLines;
    guest->clrText = host->clrText;
    guest->clrMark = host->clrMark;
    guest->clrTextHighlight = host->clrTextHighlight;
    guest->clrBtnFace = host->clrBtnFace;
    guest->clrBtnHighlight = host->clrBtnHighlight;
    guest->clrHighlightHotTrack = host->clrHighlightHotTrack;
    memcpy(&guest->rcText, &host->rcText, sizeof(guest->rcText));
    guest->nStringBkMode = host->nStringBkMode;
    guest->nHLStringBkMode = host->nHLStringBkMode;
    guest->iListGap = host->iListGap;
}

static inline void NMTBCUSTOMDRAW_g2h(NMTBCUSTOMDRAW *host, const struct qemu_NMTBCUSTOMDRAW *guest)
{
    NMCUSTOMDRAW_g2h(&host->nmcd, &guest->nmcd);
    host->hbrMonoDither = HANDLE_g2h(guest->hbrMonoDither);
    host->hbrLines = HANDLE_g2h(guest->hbrLines);
    host->hpenLines = HANDLE_g2h(guest->hpenLines);
    host->clrText = guest->clrText;
    host->clrMark = guest->clrMark;
    host->clrTextHighlight = guest->clrTextHighlight;
    host->clrBtnFace = guest->clrBtnFace;
    host->clrBtnHighlight = guest->clrBtnHighlight;
    host->clrHighlightHotTrack = guest->clrHighlightHotTrack;
    memcpy(&host->rcText, &guest->rcText, sizeof(guest->rcText));
    host->nStringBkMode = guest->nStringBkMode;
    host->nHLStringBkMode = guest->nHLStringBkMode;
    host->iListGap = guest->iListGap;
}

struct qemu_NMMOUSE
{
    struct qemu_NMHDR   hdr;
    qemu_ptr            dwItemSpec;
    qemu_ptr            dwItemData;
    POINT               pt;
    DWORD               dwHitInfo;
};

static inline void NMMOUSE_h2g(struct qemu_NMMOUSE *guest, const NMMOUSE *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->dwItemSpec = host->dwItemSpec;
    guest->dwItemData = host->dwItemData;
    guest->pt.x = host->pt.x;
    guest->pt.y = host->pt.y;
    guest->dwHitInfo = host->dwHitInfo;
}

static inline void NMMOUSE_g2h(NMMOUSE *host, const struct qemu_NMMOUSE *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->dwItemSpec = guest->dwItemSpec;
    host->dwItemData = guest->dwItemData;
    host->pt.x = guest->pt.x;
    host->pt.y = guest->pt.y;
    host->dwHitInfo = guest->dwHitInfo;
}

#endif
