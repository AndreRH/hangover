#ifndef HAVE_QEMU_COMMDLG_H
#define HAVE_QEMU_COMMDLG_H

struct qemu_CHOOSEFONT
{
    UINT            lStructSize;
    qemu_handle     hwndOwner;
    qemu_handle     hDC;
    qemu_ptr        lpLogFont;
    INT             iPointSize;
    DWORD           Flags;
    COLORREF        rgbColors;
    qemu_ptr        lCustData;
    qemu_ptr        lpfnHook;
    qemu_ptr        lpTemplateName;
    qemu_handle     hInstance;
    qemu_ptr        lpszStyle;
    WORD            nFontType;
    WORD            ___MISSING_ALIGNMENT__;
    INT             nSizeMin;
    INT             nSizeMax;
};

struct qemu_FINDREPLACE
{
    DWORD           lStructSize;
    qemu_handle     hwndOwner;
    qemu_handle     hInstance;
    DWORD           Flags;
    qemu_ptr        lpstrFindWhat;
    qemu_ptr        lpstrReplaceWith;
    WORD            wFindWhatLen;
    WORD            wReplaceWithLen;
    qemu_ptr        lCustData;
    qemu_ptr        lpfnHook;
    qemu_ptr        lpTemplateName;
};

static inline void FINDREPLACE_g2h(FINDREPLACEW *host, const struct qemu_FINDREPLACE *guest)
{
    host->lStructSize = sizeof(*host);
    host->hwndOwner = (HWND)(ULONG_PTR)guest->hwndOwner;
    host->hInstance = (HINSTANCE)(ULONG_PTR)guest->hInstance;
    host->Flags = guest->Flags;
    host->lpstrFindWhat = (WCHAR *)(ULONG_PTR)guest->lpstrFindWhat;
    host->lpstrReplaceWith = (WCHAR *)(ULONG_PTR)guest->lpstrReplaceWith;
    host->wFindWhatLen = guest->wFindWhatLen;
    host->wReplaceWithLen = guest->wReplaceWithLen;
    /* Do not touch lCustData, it is used by the calling functions. */
    host->lpfnHook = (LPFRHOOKPROC)(ULONG_PTR)guest->lpfnHook;
    host->lpTemplateName = (const WCHAR *)(ULONG_PTR)guest->lpTemplateName;
}

static inline void FINDREPLACE_h2g(struct qemu_FINDREPLACE *guest, const FINDREPLACEW *host)
{
    guest->lStructSize = sizeof(*guest);
    guest->hwndOwner = (ULONG_PTR)host->hwndOwner;
    guest->hInstance = (ULONG_PTR)host->hInstance;
    guest->Flags = host->Flags;
    guest->lpstrFindWhat = (ULONG_PTR)host->lpstrFindWhat;
    guest->lpstrReplaceWith = (ULONG_PTR)host->lpstrReplaceWith;
    guest->wFindWhatLen = host->wFindWhatLen;
    guest->wReplaceWithLen = host->wReplaceWithLen;
    /* Do not touch lCustData, it is used by the calling functions. */
    guest->lpfnHook = (ULONG_PTR)host->lpfnHook;
    guest->lpTemplateName = (ULONG_PTR)host->lpTemplateName;
}

struct qemu_OPENFILENAME
{
    DWORD           lStructSize;
    qemu_handle     hwndOwner;
    qemu_handle     hInstance;
    qemu_ptr        lpstrFilter;
    qemu_ptr        lpstrCustomFilter;
    DWORD           nMaxCustFilter;
    DWORD           nFilterIndex;
    qemu_ptr        lpstrFile;
    DWORD           nMaxFile;
    qemu_ptr        lpstrFileTitle;
    DWORD           nMaxFileTitle;
    qemu_ptr        lpstrInitialDir;
    qemu_ptr        lpstrTitle;
    DWORD           Flags;
    WORD            nFileOffset;
    WORD            nFileExtension;
    qemu_ptr        lpstrDefExt;
    qemu_ptr        lCustData;
    qemu_ptr        lpfnHook;
    qemu_ptr        lpTemplateName;
    qemu_ptr        pvReserved;
    DWORD           dwReserved;
    DWORD           FlagsEx;
};

static inline void OPENFILENAME_g2h(OPENFILENAMEW *host, const struct qemu_OPENFILENAME *guest)
{
    host->lStructSize = sizeof(*host);
    host->hwndOwner = (HWND)(ULONG_PTR)guest->hwndOwner;
    host->hInstance = (HINSTANCE)(ULONG_PTR)guest->hInstance;
    host->lpstrFilter = (LPCWSTR)(ULONG_PTR)guest->lpstrFilter;
    host->lpstrCustomFilter = (LPWSTR)(ULONG_PTR)guest->lpstrCustomFilter;
    host->nMaxCustFilter = guest->nMaxCustFilter;
    host->nFilterIndex = guest->nFilterIndex;
    host->lpstrFile = (LPWSTR)(ULONG_PTR)guest->lpstrFile;
    host->nMaxFile = guest->nMaxFile;
    host->lpstrFileTitle = (LPWSTR)(ULONG_PTR)guest->lpstrFileTitle;
    host->nMaxFileTitle = guest->nMaxFileTitle;
    host->lpstrInitialDir = (LPCWSTR)(ULONG_PTR)guest->lpstrInitialDir;
    host->lpstrTitle = (LPCWSTR)(ULONG_PTR)guest->lpstrTitle;
    host->Flags = guest->Flags;
    host->nFileOffset = guest->nFileOffset;
    host->nFileExtension = guest->nFileExtension;
    host->lpstrDefExt = (LPCWSTR)(ULONG_PTR)guest->lpstrDefExt;
    /* Do not touch lCustData, it is used by the calling functions. */
    host->lpfnHook = (LPOFNHOOKPROC)(ULONG_PTR)guest->lpfnHook;
    host->lpTemplateName = (LPCWSTR)(ULONG_PTR)guest->lpTemplateName;
    host->pvReserved = (void *)(ULONG_PTR)guest->pvReserved;
    host->dwReserved = guest->dwReserved;
    host->FlagsEx = guest->FlagsEx;
}

static inline void OPENFILENAME_h2g(struct qemu_OPENFILENAME *guest, const OPENFILENAMEW *host)
{
    guest->lStructSize = sizeof(*guest);
    guest->hwndOwner = (ULONG_PTR)host->hwndOwner;
    guest->hInstance = (ULONG_PTR)host->hInstance;
    guest->lpstrFilter = (ULONG_PTR)host->lpstrFilter;
    guest->lpstrCustomFilter = (ULONG_PTR)host->lpstrCustomFilter;
    guest->nMaxCustFilter = host->nMaxCustFilter;
    guest->nFilterIndex = host->nFilterIndex;
    guest->lpstrFile = (ULONG_PTR)host->lpstrFile;
    guest->nMaxFile = host->nMaxFile;
    guest->lpstrFileTitle = (ULONG_PTR)host->lpstrFileTitle;
    guest->nMaxFileTitle = host->nMaxFileTitle;
    guest->lpstrInitialDir = (ULONG_PTR)host->lpstrInitialDir;
    guest->lpstrTitle = (ULONG_PTR)host->lpstrTitle;
    guest->Flags = host->Flags;
    guest->nFileOffset = host->nFileOffset;
    guest->nFileExtension = host->nFileExtension;
    guest->lpstrDefExt = (ULONG_PTR)host->lpstrDefExt;
    /* Do not touch lCustData, it is used by the calling functions. */
    guest->lpfnHook = (ULONG_PTR)host->lpfnHook;
    guest->lpTemplateName = (ULONG_PTR)host->lpTemplateName;
    guest->pvReserved = (ULONG_PTR)host->pvReserved;
    guest->dwReserved = host->dwReserved;
    guest->FlagsEx = host->FlagsEx;
}

struct qemu_OFNOTIFY
{
    struct qemu_NMHDR   hdr;
    qemu_ptr            lpOFN;
    qemu_ptr            pszFile;
};

#endif
