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

#endif
