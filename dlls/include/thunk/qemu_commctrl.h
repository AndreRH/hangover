#ifndef HAVE_QEMU_COMMCTRL_H
#define HAVE_QEMU_COMMCTRL_H

#include "thunk/qemu_prsht.h"

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

static inline void TBBUTTON_h2g(struct qemu_TBBUTTON *guest, const TBBUTTON *host)
{
    guest->iBitmap = host->iBitmap;
    guest->idCommand = host->idCommand;
    guest->fsState = host->fsState;
    guest->fsStyle = host->fsStyle;
    memset(&guest->bReserved, 0, sizeof(guest->bReserved));
    guest->dwData = host->dwData;
    guest->iString = host->iString;
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

struct qemu_NMTOOLTIPSCREATED
{
    struct qemu_NMHDR   hdr;
    qemu_handle         hwndToolTips;
};

static inline void NMTOOLTIPSCREATED_h2g(struct qemu_NMTOOLTIPSCREATED *guest, const NMTOOLTIPSCREATED *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->hwndToolTips = (ULONG_PTR)host->hwndToolTips;
}

static inline void NMTOOLTIPSCREATED_g2h(NMTOOLTIPSCREATED *host, const struct qemu_NMTOOLTIPSCREATED *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->hwndToolTips = HANDLE_g2h(guest->hwndToolTips);
}

struct qemu_NMTBGETINFOTIP
{
    struct qemu_NMHDR   hdr;
    qemu_ptr            pszText;
    INT                 cchTextMax;
    INT                 iItem;
    qemu_ptr            lParam;
};

static inline void NMTBGETINFOTIP_h2g(struct qemu_NMTBGETINFOTIP *guest, const NMTBGETINFOTIPW *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    /* guest->pszText = (ULONG_PTR)host->pszText; - handled by caller */
    guest->cchTextMax = host->cchTextMax;
    guest->iItem = host->iItem;
    guest->lParam = host->lParam;
}

static inline void NMTBGETINFOTIP_g2h(NMTBGETINFOTIPW *host, const struct qemu_NMTBGETINFOTIP *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    /* host->pszText = (WCHAR *)(ULONG_PTR)guest->pszText; - handled by caller */
    host->cchTextMax = guest->cchTextMax;
    host->iItem = guest->iItem;
    host->lParam = guest->lParam;
}

struct qemu_NMCBEENDEDITW
{
    struct qemu_NMHDR   hdr;
    BOOL                fChanged;
    int                 iNewSelection;
    WCHAR               szText[CBEMAXSTRLEN];
    int                 iWhy;
};

static inline void NMCBEENDEDITW_h2g(struct qemu_NMCBEENDEDITW *guest, const NMCBEENDEDITW *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->fChanged = host->fChanged;
    guest->iNewSelection = host->iNewSelection;
    memcpy(guest->szText, host->szText, sizeof(guest->szText));
    guest->iWhy = host->iWhy;
}

static inline void NMCBEENDEDITW_g2h(NMCBEENDEDITW *host, const struct qemu_NMCBEENDEDITW *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->fChanged = guest->fChanged;
    host->iNewSelection = guest->iNewSelection;
    memcpy(host->szText, guest->szText, sizeof(host->szText));
    host->iWhy = guest->iWhy;
}

struct qemu_NMCBEENDEDITA
{
    struct qemu_NMHDR   hdr;
    BOOL                fChanged;
    int                 iNewSelection;
    char                szText[CBEMAXSTRLEN];
    int                 iWhy;
};

static inline void NMCBEENDEDITA_h2g(struct qemu_NMCBEENDEDITA *guest, const NMCBEENDEDITA *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->fChanged = host->fChanged;
    guest->iNewSelection = host->iNewSelection;
    memcpy(guest->szText, host->szText, sizeof(guest->szText));
    guest->iWhy = host->iWhy;
}

static inline void NMCBEENDEDITA_g2h(NMCBEENDEDITA *host, const struct qemu_NMCBEENDEDITA *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->fChanged = guest->fChanged;
    host->iNewSelection = guest->iNewSelection;
    memcpy(host->szText, guest->szText, sizeof(host->szText));
    host->iWhy = guest->iWhy;
}

struct qemu_COMBOBOXEXITEM
{
    UINT        mask;
    qemu_sptr   iItem;
    qemu_ptr    pszText;
    int         cchTextMax;
    int         iImage;
    int         iSelectedImage;
    int         iOverlay;
    int         iIndent;
    qemu_ptr    lParam;
};

static inline void COMBOBOXEXITEM_h2g(struct qemu_COMBOBOXEXITEM *guest, const COMBOBOXEXITEMW *host)
{
    guest->mask = host->mask;
    guest->iItem = host->iItem;
    guest->pszText = (ULONG_PTR)host->pszText;
    guest->cchTextMax = host->cchTextMax;
    guest->iImage = host->iImage;
    guest->iSelectedImage = host->iSelectedImage;
    guest->iOverlay = host->iOverlay;
    guest->iIndent = host->iIndent;
    guest->lParam = host->lParam;
}

static inline void COMBOBOXEXITEM_g2h(COMBOBOXEXITEMW *host, const struct qemu_COMBOBOXEXITEM *guest)
{
    host->mask = guest->mask;
    host->iItem = guest->iItem;
    host->pszText = (WCHAR *)(ULONG_PTR)guest->pszText;
    host->cchTextMax = guest->cchTextMax;
    host->iImage = guest->iImage;
    host->iSelectedImage = guest->iSelectedImage;
    host->iOverlay = guest->iOverlay;
    host->iIndent = guest->iIndent;
    host->lParam = guest->lParam;
}

struct qemu_NMCOMBOBOXEX
{
    struct qemu_NMHDR hdr;
    struct qemu_COMBOBOXEXITEM ceItem;
};

static inline void NMCOMBOBOXEX_h2g(struct qemu_NMCOMBOBOXEX *guest, const NMCOMBOBOXEXW *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    COMBOBOXEXITEM_h2g(&guest->ceItem, &host->ceItem);
}

static inline void NMCOMBOBOXEX_g2h(NMCOMBOBOXEXW *host, const struct qemu_NMCOMBOBOXEX *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    COMBOBOXEXITEM_g2h(&host->ceItem, &guest->ceItem);
}

struct qemu_NMTBHOTITEM
{
    struct qemu_NMHDR hdr;
    int idOld;
    int idNew;
    DWORD dwFlags;
};

static inline void NMTBHOTITEM_h2g(struct qemu_NMTBHOTITEM *guest, const NMTBHOTITEM *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->idOld = host->idOld;
    guest->idNew = host->idNew;
    guest->dwFlags = host->dwFlags;
}

static inline void NMTBHOTITEM_g2h(NMTBHOTITEM *host, const struct qemu_NMTBHOTITEM *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->idOld = guest->idOld;
    host->idNew = guest->idNew;
    host->dwFlags = guest->dwFlags;
}

struct qemu_NMTOOLBAR
{
    struct qemu_NMHDR       hdr;
    INT                     iItem;
    struct qemu_TBBUTTON    tbButton;
    INT                     cchText;
    qemu_ptr                pszText;
    RECT                    rcButton;
};

static inline void NMTOOLBAR_h2g(struct qemu_NMTOOLBAR *guest, const NMTOOLBARW *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->iItem = host->iItem;
    TBBUTTON_h2g(&guest->tbButton, &host->tbButton);
    guest->cchText = host->cchText;
    guest->pszText = (ULONG_PTR)host->pszText;
    memcpy(&guest->rcButton, &host->rcButton, sizeof(guest->rcButton));
}

static inline void NMTOOLBAR_g2h(NMTOOLBARW *host, const struct qemu_NMTOOLBAR *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->iItem = guest->iItem;
    TBBUTTON_g2h(&host->tbButton, &guest->tbButton);
    host->cchText = guest->cchText;
    host->pszText = (WCHAR *)(ULONG_PTR)guest->pszText;
    memcpy(&host->rcButton, &guest->rcButton, sizeof(host->rcButton));
}

struct qemu_NMKEY
{
    struct qemu_NMHDR   hdr;
    UINT                nVKey;
    UINT                uFlags;
};

static inline void NMKEY_h2g(struct qemu_NMKEY *guest, const NMKEY *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->nVKey = host->nVKey;
    guest->uFlags = host->uFlags;
}

static inline void NMKEY_g2h(NMKEY *host, const struct qemu_NMKEY *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->nVKey = guest->nVKey;
    host->uFlags = guest->uFlags;
}

struct qemu_NMTTDISPINFOA
{
    struct qemu_NMHDR   hdr;
    qemu_ptr            lpszText;
    CHAR                szText[80];
    qemu_handle         hinst;
    UINT                uFlags;
    qemu_ptr            lParam;
};

static inline void NMTTDISPINFOA_h2g(struct qemu_NMTTDISPINFOA *guest, const NMTTDISPINFOA *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);

    if (host->lpszText == host->szText)
        guest->lpszText = (ULONG_PTR)guest->szText;
    else
        guest->lpszText = (ULONG_PTR)host->lpszText;

    memcpy(guest->szText, host->szText, sizeof(guest->szText));
    guest->hinst = (ULONG_PTR)host->hinst;
    guest->uFlags = host->uFlags;
    guest->lParam = host->lParam;
}

static inline void NMTTDISPINFOA_g2h(NMTTDISPINFOA *host, const struct qemu_NMTTDISPINFOA *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);

    if (guest->lpszText == (ULONG_PTR)guest->szText)
        host->lpszText = host->szText;
    else
        host->lpszText = (CHAR *)(ULONG_PTR)guest->lpszText;

    memcpy(host->szText, guest->szText, sizeof(host->szText));
    host->hinst = HANDLE_g2h(guest->hinst);
    host->uFlags = guest->uFlags;
    host->lParam = guest->lParam;
}

struct qemu_NMTTDISPINFOW
{
    struct qemu_NMHDR   hdr;
    qemu_ptr            lpszText;
    WCHAR               szText[80];
    qemu_handle         hinst;
    UINT                uFlags;
    qemu_ptr            lParam;
};

static inline void NMTTDISPINFOW_h2g(struct qemu_NMTTDISPINFOW *guest, const NMTTDISPINFOW *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    if (host->lpszText == host->szText)
        guest->lpszText = (ULONG_PTR)guest->szText;
    else
        guest->lpszText = (ULONG_PTR)host->lpszText;
    memcpy(guest->szText, host->szText, sizeof(guest->szText));
    guest->hinst = (ULONG_PTR)host->hinst;
    guest->uFlags = host->uFlags;
    guest->lParam = host->lParam;
}

static inline void NMTTDISPINFOW_g2h(NMTTDISPINFOW *host, const struct qemu_NMTTDISPINFOW *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);

    if (guest->lpszText == (ULONG_PTR)guest->szText)
        host->lpszText = host->szText;
    else
        host->lpszText = (WCHAR *)(ULONG_PTR)guest->lpszText;

    memcpy(host->szText, guest->szText, sizeof(host->szText));
    host->hinst = HANDLE_g2h(guest->hinst);
    host->uFlags = guest->uFlags;
    host->lParam = guest->lParam;
}

struct qemu_NMTTCUSTOMDRAW
{
    struct qemu_NMCUSTOMDRAW nmcd;
    UINT uDrawFlags;
};

static inline void NMTTCUSTOMDRAW_h2g(struct qemu_NMTTCUSTOMDRAW *guest, const NMTTCUSTOMDRAW *host)
{
    NMCUSTOMDRAW_h2g(&guest->nmcd, &host->nmcd);
    guest->uDrawFlags = host->uDrawFlags;
}

static inline void NMTTCUSTOMDRAW_g2h(NMTTCUSTOMDRAW *host, const struct qemu_NMTTCUSTOMDRAW *guest)
{
    NMCUSTOMDRAW_g2h(&host->nmcd, &guest->nmcd);
    host->uDrawFlags = guest->uDrawFlags;
}

struct qemu_NMREBAR
{
    struct qemu_NMHDR   hdr;
    DWORD               dwMask;
    UINT                uBand;
    UINT                fStyle;
    UINT                wID;
    qemu_ptr            lParam;
};

static inline void NMREBAR_h2g(struct qemu_NMREBAR *guest, const NMREBAR *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->dwMask = host->dwMask;
    guest->uBand = host->uBand;
    guest->fStyle = host->fStyle;
    guest->wID = host->wID;
    guest->lParam = host->lParam;
}

static inline void NMREBAR_g2h(NMREBAR *host, const struct qemu_NMREBAR *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->dwMask = guest->dwMask;
    host->uBand = guest->uBand;
    host->fStyle = guest->fStyle;
    host->wID = guest->wID;
    host->lParam = guest->lParam;
}

#include <pshpack1.h>
struct qemu_NMTCKEYDOWN
{
    struct qemu_NMHDR hdr;
    WORD wVKey;
    UINT flags;
};
#include <poppack.h>

static inline void NMTCKEYDOWN_h2g(struct qemu_NMTCKEYDOWN *guest, const NMTCKEYDOWN *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->wVKey = host->wVKey;
    guest->flags = host->flags;
}

static inline void TCKEYDOWN_g2h(NMTCKEYDOWN *host, const struct qemu_NMTCKEYDOWN *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->wVKey = guest->wVKey;
    host->flags = guest->flags;
}

struct qemu_TCITEM
{
    UINT        mask;
    DWORD       dwState;
    DWORD       dwStateMask;
    qemu_ptr    pszText;
    INT         cchTextMax;
    INT         iImage;
    qemu_ptr    lParam;
};

static inline void TCITEM_h2g(struct qemu_TCITEM *guest, const TCITEMW *host)
{
    guest->mask = host->mask;
    guest->dwState = host->dwState;
    guest->dwStateMask = host->dwStateMask;
    guest->pszText = (ULONG_PTR)host->pszText;
    guest->cchTextMax = host->cchTextMax;
    guest->iImage = host->iImage;
    guest->lParam = host->lParam;
}

static inline void TCITEM_g2h(TCITEMW *host, const struct qemu_TCITEM *guest)
{
    host->mask = guest->mask;
    host->dwState = guest->dwState;
    host->dwStateMask = guest->dwStateMask;
    host->pszText = (WCHAR *)(ULONG_PTR)guest->pszText;
    host->cchTextMax = guest->cchTextMax;
    host->iImage = guest->iImage;
    host->lParam = guest->lParam;
}

#endif
