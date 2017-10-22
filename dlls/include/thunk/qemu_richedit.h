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

#endif
