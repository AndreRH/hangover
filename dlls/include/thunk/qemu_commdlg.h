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

static inline void CHOOSEFONT_g2h(CHOOSEFONTW *host, const struct qemu_CHOOSEFONT *guest)
{
    host->lStructSize = sizeof(*host);
    host->hwndOwner = (HWND)(ULONG_PTR)guest->hwndOwner;
    host->hDC = (HDC)(ULONG_PTR)guest->hDC;
    host->lpLogFont = (LOGFONTW *)(ULONG_PTR)guest->lpLogFont;
    host->iPointSize = guest->iPointSize;
    host->Flags = guest->Flags;
    host->rgbColors = guest->rgbColors;
    host->lCustData = guest->lCustData;
    host->lpfnHook = (LPCFHOOKPROC)(ULONG_PTR)guest->lpfnHook;
    host->lpTemplateName = (WCHAR *)(ULONG_PTR)guest->lpTemplateName;
    host->hInstance = (HINSTANCE)(ULONG_PTR)guest->hInstance;
    host->lpszStyle = (WCHAR *)(ULONG_PTR)guest->lpszStyle;
    host->nFontType = guest->nFontType;
    host->___MISSING_ALIGNMENT__ = guest->___MISSING_ALIGNMENT__; /* Hmm... */
    host->nSizeMin = guest->nSizeMin;
    host->nSizeMax = guest->nSizeMax;
}

static inline void CHOOSEFONT_h2g(struct qemu_CHOOSEFONT *guest, const CHOOSEFONTW *host)
{
    guest->lStructSize = sizeof(*guest);
    guest->hwndOwner = (ULONG_PTR)host->hwndOwner;
    guest->hDC = (ULONG_PTR)host->hDC;
    guest->lpLogFont = (ULONG_PTR)host->lpLogFont;
    guest->iPointSize = host->iPointSize;
    guest->Flags = host->Flags;
    guest->rgbColors = host->rgbColors;
    guest->lCustData = host->lCustData;
    guest->lpfnHook = (ULONG_PTR)host->lpfnHook;
    guest->lpTemplateName = (ULONG_PTR)host->lpTemplateName;
    guest->hInstance = (ULONG_PTR)host->hInstance;
    guest->lpszStyle = (ULONG_PTR)host->lpszStyle;
    guest->nFontType = host->nFontType;
    guest->___MISSING_ALIGNMENT__ = host->___MISSING_ALIGNMENT__; /* Hmm... */
    guest->nSizeMin = host->nSizeMin;
    guest->nSizeMax = host->nSizeMax;
}

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

struct qemu_PRINTDLG
{
    DWORD           lStructSize;
    qemu_handle     hwndOwner;
    qemu_handle     hDevMode;
    qemu_handle     hDevNames;
    qemu_handle     hDC;
    DWORD           Flags;
    WORD            nFromPage;
    WORD            nToPage;
    WORD            nMinPage;
    WORD            nMaxPage;
    WORD            nCopies;
    qemu_handle     hInstance;
    qemu_ptr        lCustData;
    qemu_ptr        lpfnPrintHook;
    qemu_ptr        lpfnSetupHook;
    qemu_ptr        lpPrintTemplateName;
    qemu_ptr        lpSetupTemplateName;
    qemu_handle     hPrintTemplate;
    qemu_handle     hSetupTemplate;
};

static inline void PRINTDLG_g2h(PRINTDLGW *host, const struct qemu_PRINTDLG *guest)
{
    host->lStructSize = sizeof(*host);
    host->hwndOwner = (HWND)(ULONG_PTR)guest->hwndOwner;
    host->hDevMode = (HGLOBAL)(ULONG_PTR)guest->hDevMode;
    host->hDevNames = (HGLOBAL)(ULONG_PTR)guest->hDevNames;
    host->hDC = (HDC)(ULONG_PTR)guest->hDC;
    host->Flags = guest->Flags;
    host->nFromPage = guest->nFromPage;
    host->nToPage = guest->nToPage;
    host->nMinPage = guest->nMinPage;
    host->nMaxPage = guest->nMaxPage;
    host->nCopies = guest->nCopies;
    host->hInstance = (HINSTANCE)(ULONG_PTR)guest->hInstance;
    /* Do not touch lCustData, it is used by the calling functions. */
    host->lpfnPrintHook = (LPPRINTHOOKPROC)(ULONG_PTR)guest->lpfnPrintHook;
    host->lpfnSetupHook = (LPSETUPHOOKPROC)(ULONG_PTR)guest->lpfnSetupHook;
    host->lpPrintTemplateName = (const WCHAR *)(ULONG_PTR)guest->lpPrintTemplateName;
    host->lpSetupTemplateName = (const WCHAR *)(ULONG_PTR)guest->lpSetupTemplateName;
    host->hPrintTemplate = (HGLOBAL)(ULONG_PTR)guest->hPrintTemplate;
    host->hSetupTemplate = (HGLOBAL)(ULONG_PTR)guest->hSetupTemplate;
}

static inline void PRINTDLG_h2g(struct qemu_PRINTDLG *guest, const PRINTDLGW *host)
{
    guest->lStructSize = sizeof(*guest);
    guest->hwndOwner = (ULONG_PTR)host->hwndOwner;
    guest->hDevMode = (ULONG_PTR)host->hDevMode;
    guest->hDevNames = (ULONG_PTR)host->hDevNames;
    guest->hDC = (ULONG_PTR)host->hDC;
    guest->Flags = host->Flags;
    guest->nFromPage = host->nFromPage;
    guest->nToPage = host->nToPage;
    guest->nMinPage = host->nMinPage;
    guest->nMaxPage = host->nMaxPage;
    guest->nCopies = host->nCopies;
    guest->hInstance = (ULONG_PTR)host->hInstance;
    /* Do not touch lCustData, it is used by the calling functions. */
    guest->lpfnPrintHook = (ULONG_PTR)host->lpfnPrintHook;
    guest->lpfnSetupHook = (ULONG_PTR)host->lpfnSetupHook;
    guest->lpPrintTemplateName = (ULONG_PTR)host->lpPrintTemplateName;
    guest->lpSetupTemplateName = (ULONG_PTR)host->lpSetupTemplateName;
    guest->hPrintTemplate = (ULONG_PTR)host->hPrintTemplate;
    guest->hSetupTemplate = (ULONG_PTR)host->hSetupTemplate;
}

struct qemu_PAGESETUPDLG
{
    DWORD           lStructSize;
    qemu_handle     hwndOwner;
    qemu_handle     hDevMode;
    qemu_handle     hDevNames;
    DWORD           Flags;
    POINT           ptPaperSize;
    RECT            rtMinMargin;
    RECT            rtMargin;
    qemu_handle     hInstance;
    qemu_ptr        lCustData;
    qemu_ptr        lpfnPageSetupHook;
    qemu_ptr        lpfnPagePaintHook;
    qemu_ptr        lpPageSetupTemplateName;
    qemu_handle     hPageSetupTemplate;
};

static inline void PAGESETUPDLG_g2h(PAGESETUPDLGW *host, const struct qemu_PAGESETUPDLG *guest)
{
    host->lStructSize = sizeof(*host);
    host->hwndOwner = (HWND)(ULONG_PTR)guest->hwndOwner;
    host->hDevMode = (HGLOBAL)(ULONG_PTR)guest->hDevMode;
    host->hDevNames = (HGLOBAL)(ULONG_PTR)guest->hDevNames;
    host->Flags = guest->Flags;
    memcpy(&host->ptPaperSize, &guest->ptPaperSize, sizeof(host->ptPaperSize));
    memcpy(&host->rtMinMargin, &guest->rtMinMargin, sizeof(host->rtMinMargin));
    memcpy(&host->rtMargin, &guest->rtMargin, sizeof(host->rtMargin));
    host->hInstance = (HINSTANCE)(ULONG_PTR)guest->hInstance;
    host->lCustData = guest->lCustData;
    host->lpfnPageSetupHook = (LPPAGESETUPHOOK)(ULONG_PTR)guest->lpfnPageSetupHook;
    host->lpfnPagePaintHook = (LPPAGEPAINTHOOK)(ULONG_PTR) guest->lpfnPagePaintHook;
    host->lpPageSetupTemplateName = (const WCHAR *)(ULONG_PTR)guest->lpPageSetupTemplateName;
    host->hPageSetupTemplate = (HGLOBAL)(ULONG_PTR)guest->hPageSetupTemplate;
}

static inline void PAGESETUPDLG_h2g(struct qemu_PAGESETUPDLG *guest, const PAGESETUPDLGW *host)
{
    guest->lStructSize = sizeof(*guest);
    guest->hwndOwner = (ULONG_PTR)host->hwndOwner;
    guest->hDevMode = (ULONG_PTR)host->hDevMode;
    guest->hDevNames = (ULONG_PTR)host->hDevNames;
    guest->Flags = host->Flags;
    memcpy(&guest->ptPaperSize, &host->ptPaperSize, sizeof(guest->ptPaperSize));
    memcpy(&guest->rtMinMargin, &host->rtMinMargin, sizeof(guest->rtMinMargin));
    memcpy(&guest->rtMargin, &host->rtMargin, sizeof(guest->rtMargin));
    guest->hInstance = (ULONG_PTR)host->hInstance;
    guest->lCustData = host->lCustData;
    guest->lpfnPageSetupHook = (ULONG_PTR)host->lpfnPageSetupHook;
    guest->lpfnPagePaintHook = (ULONG_PTR)host->lpfnPagePaintHook;
    guest->lpPageSetupTemplateName = (ULONG_PTR)host->lpPageSetupTemplateName;
    guest->hPageSetupTemplate = (ULONG_PTR)host->hPageSetupTemplate;
}

#endif
