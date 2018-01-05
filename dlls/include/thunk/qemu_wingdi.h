#ifndef HAVE_QEMU_WINGDI_H
#define HAVE_QEMU_WINGDI_H

struct qemu_DOCINFO
{
    INT         cbSize;
    qemu_ptr    lpszDocName;
    qemu_ptr    lpszOutput;
    qemu_ptr    lpszDatatype;
    DWORD       fwType;
};

static inline void DOCINFO_g2h(DOCINFOW *host, const struct qemu_DOCINFO *guest)
{
    host->cbSize = sizeof(*host);
    host->lpszDocName = (const WCHAR *)(ULONG_PTR)guest->lpszDocName;
    host->lpszOutput = (const WCHAR *)(ULONG_PTR)guest->lpszOutput;
    host->lpszDatatype = (const WCHAR *)(ULONG_PTR)guest->lpszDatatype;
    host->fwType = guest->fwType;
}

struct qemu_GCP_RESULTS
{
    DWORD       lStructSize;
    qemu_ptr    lpOutString;
    qemu_ptr    lpOrder;
    qemu_ptr    lpDx;
    qemu_ptr    lpCaretPos;
    qemu_ptr    lpClass;
    qemu_ptr    lpGlyphs;
    UINT        nGlyphs;
    UINT        nMaxFit;
};

static inline void GCP_RESULTS_h2g(struct qemu_GCP_RESULTS *guest, const GCP_RESULTSW *host)
{
    guest->lpOutString = (ULONG_PTR)host->lpOutString;
    guest->lpOrder = (ULONG_PTR)host->lpOrder;
    guest->lpDx = (ULONG_PTR)host->lpDx;
    guest->lpCaretPos = (ULONG_PTR)host->lpCaretPos;
    guest->lpClass = (ULONG_PTR)host->lpClass;
    guest->lpGlyphs = (ULONG_PTR)host->lpGlyphs;
    guest->nGlyphs = host->nGlyphs;
    guest->nMaxFit = host->nMaxFit;
}

static inline void GCP_RESULTS_g2h(GCP_RESULTSW *host, const struct qemu_GCP_RESULTS *guest)
{
    host->lStructSize = sizeof(*host);
    host->lpOutString = (WCHAR *)(ULONG_PTR)guest->lpOutString;
    host->lpOrder = (UINT *)(ULONG_PTR)guest->lpOrder;
    host->lpDx = (INT *)(ULONG_PTR)guest->lpDx;
    host->lpCaretPos = (INT *)(ULONG_PTR)guest->lpCaretPos;
    host->lpClass = (char *)(ULONG_PTR)guest->lpClass;
    host->lpGlyphs = (WCHAR *)(ULONG_PTR)guest->lpGlyphs;
    host->nGlyphs = host->nGlyphs;
    host->nMaxFit = host->nMaxFit;
}

#endif
