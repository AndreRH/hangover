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

#endif
