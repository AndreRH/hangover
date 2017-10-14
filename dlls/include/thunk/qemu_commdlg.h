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

#endif
