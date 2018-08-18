#ifndef HAVE_QEMU_RICHEDIT_H
#define HAVE_QEMU_RICHEDIT_H

struct qemu_MSGFILTER
{
    struct qemu_NMHDR  nmhdr;
    UINT        msg;
    qemu_ptr    wParam;
    qemu_ptr    lParam;
};

static void MSGFILTER_h2g(struct qemu_MSGFILTER *guest, const MSGFILTER *host)
{
    NMHDR_h2g(&guest->nmhdr, &host->nmhdr);
    guest->msg = host->msg;
    guest->wParam = host->wParam;
    guest->lParam = host->lParam;
}

static void MSGFILTER_g2h(MSGFILTER *host, const struct qemu_MSGFILTER *guest)
{
    NMHDR_g2h(&host->nmhdr, &guest->nmhdr);
    host->msg = guest->msg;
    host->wParam = guest->wParam;
    host->lParam = guest->lParam;
}

struct qemu_SELCHANGE
{
    struct qemu_NMHDR   nmhdr;
    CHARRANGE           chrg;
    WORD                seltyp;
};

static void SELCHANGE_h2g(struct qemu_SELCHANGE *guest, const SELCHANGE *host)
{
    NMHDR_h2g(&guest->nmhdr, &host->nmhdr);
    guest->chrg.cpMin = host->chrg.cpMin;
    guest->chrg.cpMax = host->chrg.cpMax;
    guest->seltyp = host->seltyp;
}

static void SELCHANGE_g2h(SELCHANGE *host, const struct qemu_SELCHANGE *guest)
{
    NMHDR_g2h(&host->nmhdr, &guest->nmhdr);
    host->chrg.cpMin = guest->chrg.cpMin;
    host->chrg.cpMax = guest->chrg.cpMax;
    host->seltyp = guest->seltyp;
}

struct qemu_EDITSTREAM
{
    qemu_ptr            dwCookie;
    DWORD               dwError;
    qemu_ptr            pfnCallback;
};

static void EDITSTREAM_h2g(struct qemu_EDITSTREAM *guest, const EDITSTREAM *host)
{
    guest->dwCookie = host->dwCookie;
    guest->dwError = host->dwError;
    guest->pfnCallback = (ULONG_PTR)host->pfnCallback;
}

static void EDITSTREAM_g2h(EDITSTREAM *host, const struct qemu_EDITSTREAM *guest)
{
    host->dwCookie = guest->dwCookie;
    host->dwError = guest->dwError;
    host->pfnCallback = (EDITSTREAMCALLBACK)(ULONG_PTR)guest->pfnCallback;
}

struct qemu_FINDTEXT
{
    CHARRANGE  chrg;
    qemu_ptr   lpstrText;
};

static void FINDTEXT_h2g(struct qemu_FINDTEXT *guest, const FINDTEXTW *host)
{
    guest->chrg.cpMin = host->chrg.cpMin;
    guest->chrg.cpMax = host->chrg.cpMax;
    guest->lpstrText = (ULONG_PTR)host->lpstrText;
}

static void FINDTEXT_g2h(FINDTEXTW *host, const struct qemu_FINDTEXT *guest)
{
    host->chrg.cpMin = guest->chrg.cpMin;
    host->chrg.cpMax = guest->chrg.cpMax;
    host->lpstrText = (const WCHAR *)(ULONG_PTR)guest->lpstrText;
}

struct qemu_FINDTEXTEX
{
    CHARRANGE  chrg;
    qemu_ptr   lpstrText;
    CHARRANGE  chrgText;
};

static void FINDTEXTEX_h2g(struct qemu_FINDTEXTEX *guest, const FINDTEXTEXW *host)
{
    guest->chrg.cpMin = host->chrg.cpMin;
    guest->chrg.cpMax = host->chrg.cpMax;
    guest->lpstrText = (ULONG_PTR)host->lpstrText;
    guest->chrgText.cpMin = host->chrgText.cpMin;
    guest->chrgText.cpMax = host->chrgText.cpMax;
}

static void FINDTEXTEX_g2h(FINDTEXTEXW *host, const struct qemu_FINDTEXTEX *guest)
{
    host->chrg.cpMin = guest->chrg.cpMin;
    host->chrg.cpMax = guest->chrg.cpMax;
    host->lpstrText = (const WCHAR *)(ULONG_PTR)guest->lpstrText;
    host->chrgText.cpMin = guest->chrgText.cpMin;
    host->chrgText.cpMax = guest->chrgText.cpMax;
}

struct qemu_FORMATRANGE
{
    qemu_handle hdc;
    qemu_handle hdcTarget;
    RECT        rc;
    RECT        rcPage;
    CHARRANGE   chrg;
};

static void FORMATRANGE_h2g(struct qemu_FORMATRANGE *guest, const FORMATRANGE *host)
{
    guest->hdc = (ULONG_PTR)host->hdc;
    guest->hdcTarget = (ULONG_PTR)host->hdcTarget;
    memcpy(&guest->rc, &host->rc, sizeof(guest->rc));
    memcpy(&guest->rcPage, &host->rc, sizeof(guest->rcPage));
    guest->chrg.cpMin = host->chrg.cpMin;
    guest->chrg.cpMax = host->chrg.cpMax;
}

static void FORMATRANGE_g2h(FORMATRANGE *host, const struct qemu_FORMATRANGE *guest)
{
    host->hdc = HANDLE_g2h(guest->hdc);
    host->hdcTarget = HANDLE_g2h(guest->hdcTarget);
    memcpy(&host->rc, &guest->rc, sizeof(host->rc));
    memcpy(&host->rcPage, &guest->rc, sizeof(host->rcPage));
    host->chrg.cpMin = guest->chrg.cpMin;
    host->chrg.cpMax = guest->chrg.cpMax;
}

struct qemu_TEXTRANGE
{
    CHARRANGE chrg;
    qemu_ptr  lpstrText;
};

static void TEXTRANGE_h2g(struct qemu_TEXTRANGE *guest, const TEXTRANGEW *host)
{
    guest->chrg = host->chrg;
    guest->lpstrText = (ULONG_PTR)host->lpstrText;
}

static void TEXTRANGE_g2h(TEXTRANGEW *host, const struct qemu_TEXTRANGE *guest)
{
    host->chrg = guest->chrg;
    host->lpstrText = (WCHAR *)(ULONG_PTR)guest->lpstrText;
}

struct qemu_GETTEXTEX
{
    DWORD      cb;
    DWORD      flags;
    UINT       codepage;
    qemu_ptr   lpDefaultChar;
    qemu_ptr   lpUsedDefChar;
};

static void GETTEXTEX_h2g(struct qemu_GETTEXTEX *guest, const GETTEXTEX *host)
{
    guest->cb = host->cb;
    guest->flags = host->flags;
    guest->codepage = host->codepage;
    guest->lpDefaultChar = (ULONG_PTR)host->lpDefaultChar;
    guest->lpUsedDefChar = (ULONG_PTR)host->lpUsedDefChar;
}

static void GETTEXTEX_g2h(GETTEXTEX *host, const struct qemu_GETTEXTEX *guest)
{
    host->cb = guest->cb;
    host->flags = guest->flags;
    host->codepage = guest->codepage;
    host->lpDefaultChar = (const char *)(ULONG_PTR)guest->lpDefaultChar;
    host->lpUsedDefChar = (BOOL *)(ULONG_PTR)guest->lpUsedDefChar;
}

#endif
