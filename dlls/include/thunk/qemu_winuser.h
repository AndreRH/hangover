#ifndef HAVE_QEMU_WINUSER_H
#define HAVE_QEMU_WINUSER_H

struct qemu_WNDCLASSEX
{
    UINT        cbSize;
    UINT        style;
    qemu_ptr    lpfnWndProc;
    INT         cbClsExtra;
    INT         cbWndExtra;
    qemu_handle hInstance;
    qemu_handle hIcon;
    qemu_handle hCursor;
    qemu_handle hbrBackground;
    qemu_ptr    lpszMenuName;
    qemu_ptr    lpszClassName;
    qemu_handle hIconSm;
};

struct qemu_CREATESTRUCT
{
    qemu_ptr        lpCreateParams;
    qemu_handle     hInstance;
    qemu_handle     hMenu;
    qemu_handle     hwndParent;
    INT             cy;
    INT             cx;
    INT             y;
    INT             x;
    LONG            style;
    qemu_ptr        lpszName;
    qemu_ptr        lpszClass;
    DWORD           dwExStyle;
};

struct qemu_WINDOWPOS
{
    qemu_handle hwnd;
    qemu_handle hwndInsertAfter;
    INT         x;
    INT         y;
    INT         cx;
    INT         cy;
    UINT        flags;
};

static inline void WINDOWPOS_g2h(WINDOWPOS *host, const struct qemu_WINDOWPOS *guest)
{
    host->hwnd = (HWND)(ULONG_PTR)guest->hwnd;
    host->hwndInsertAfter = (HWND)(ULONG_PTR)guest->hwndInsertAfter;
    host->x = guest->x;
    host->y = guest->y;
    host->cx = guest->cx;
    host->cy = guest->cy;
    host->flags = guest->flags;
}

static inline void WINDOWPOS_h2g(struct qemu_WINDOWPOS *guest, const WINDOWPOS *host)
{
    guest->hwnd = (ULONG_PTR)host->hwnd;
    guest->hwndInsertAfter = (ULONG_PTR)host->hwndInsertAfter;
    guest->x = host->x;
    guest->y = host->y;
    guest->cx = host->cx;
    guest->cy = host->cy;
    guest->flags = host->flags;
}

struct qemu_NMHDR
{
    qemu_handle hwndFrom;
    qemu_ptr    idFrom;
    UINT        code;
};

static inline void NMHDR_h2g(struct qemu_NMHDR *guest, const NMHDR *host)
{
    guest->hwndFrom = (ULONG_PTR)host->hwndFrom;
    guest->idFrom = host->idFrom;
    guest->code = host->code;
}

static inline void NMHDR_g2h(NMHDR *host, const struct qemu_NMHDR *guest)
{
    host->hwndFrom = HANDLE_g2h(guest->hwndFrom);
    host->idFrom = guest->idFrom;
    host->code = guest->code;
}

struct qemu_PAINTSTRUCT
{
    qemu_handle     hdc;
    BOOL            fErase;
    RECT            rcPaint;
    BOOL            fRestore;
    BOOL            fIncUpdate;
    BYTE            rgbReserved[32];
};

static inline void PAINTSTRUCT_h2g(struct qemu_PAINTSTRUCT *guest, const PAINTSTRUCT *host)
{
    guest->hdc = (ULONG_PTR)host->hdc;
    guest->fErase = host->fErase;
    memcpy(&guest->rcPaint, &host->rcPaint, sizeof(guest->rcPaint));
    guest->fRestore = host->fRestore;
    guest->fIncUpdate = host->fIncUpdate;
    memcpy(guest->rgbReserved, host->rgbReserved, sizeof(guest->rgbReserved));
}

static inline void PAINTSTRUCT_g2h(PAINTSTRUCT *host, const struct qemu_PAINTSTRUCT *guest)
{
    host->hdc = HANDLE_g2h(guest->hdc);
    host->fErase = guest->fErase;
    memcpy(&host->rcPaint, &guest->rcPaint, sizeof(host->rcPaint));
    host->fRestore = guest->fRestore;
    host->fIncUpdate = guest->fIncUpdate;
    memcpy(host->rgbReserved, guest->rgbReserved, sizeof(host->rgbReserved));
}

struct qemu_MENUITEMINFO
{
    UINT            cbSize;
    UINT            fMask;
    UINT            fType;
    UINT            fState;
    UINT            wID;
    qemu_handle     hSubMenu;
    qemu_handle     hbmpChecked;
    qemu_handle     hbmpUnchecked;
    qemu_ptr        dwItemData;
    qemu_ptr        dwTypeData;
    UINT            cch;
    qemu_handle     hbmpItem;
};

static inline void MENUITEMINFO_g2h(MENUITEMINFOW *host, const struct qemu_MENUITEMINFO *guest)
{
    host->cbSize = sizeof(*host);
    host->fMask = guest->fMask;
    host->fType = guest->fType;
    host->fState = guest->fState;
    host->wID = guest->wID;
    host->hSubMenu = HANDLE_g2h(guest->hSubMenu);
    host->hbmpChecked = HANDLE_g2h(guest->hbmpChecked);
    host->hbmpUnchecked = HANDLE_g2h(guest->hbmpUnchecked);
    host->dwItemData = guest->dwItemData;
    host->dwTypeData = (LPWSTR)(ULONG_PTR)guest->dwTypeData;
    host->cch = guest->cch;
    host->hbmpItem = HANDLE_g2h(guest->hbmpItem);
}

static inline void MENUITEMINFO_h2g(struct qemu_MENUITEMINFO *guest, const MENUITEMINFOW *host)
{
    guest->cbSize = sizeof(*guest);
    guest->fMask = host->fMask;
    guest->fType = host->fType;
    guest->fState = host->fState;
    guest->wID = host->wID;
    guest->hSubMenu = (ULONG_PTR)host->hSubMenu;
    guest->hbmpChecked = (ULONG_PTR)host->hbmpChecked;
    guest->hbmpUnchecked = (ULONG_PTR)host->hbmpUnchecked;
    guest->dwItemData = host->dwItemData;
    guest->dwTypeData = (ULONG_PTR)host->dwTypeData;
    guest->cch = host->cch;
    guest->hbmpItem = (ULONG_PTR)host->hbmpItem;
}

struct qemu_MSGBOXPARAMSW
{
    UINT            cbSize;
    qemu_handle     hwndOwner;
    qemu_handle     hInstance;
    qemu_ptr        lpszText;
    qemu_ptr        lpszCaption;
    DWORD           dwStyle;
    qemu_ptr        lpszIcon;
    qemu_ptr        dwContextHelpId;
    qemu_ptr        lpfnMsgBoxCallback;
    DWORD           dwLanguageId;
};

static inline void MSGBOXPARAMS_g2h(MSGBOXPARAMSW *host, const struct qemu_MSGBOXPARAMSW *guest)
{
    host->cbSize = sizeof(*host);
    host->hwndOwner = HANDLE_g2h(guest->hwndOwner);
    host->hInstance = HANDLE_g2h(guest->hInstance);
    host->lpszText = (const WCHAR *)(ULONG_PTR)guest->lpszText;
    host->lpszCaption = (const WCHAR *)(ULONG_PTR)guest->lpszCaption;
    host->dwStyle = guest->dwStyle;
    host->lpszIcon = (const WCHAR *)(ULONG_PTR)guest->lpszIcon;
    host->dwContextHelpId = guest->dwContextHelpId;
    host->lpfnMsgBoxCallback = (MSGBOXCALLBACK)(ULONG_PTR)guest->lpfnMsgBoxCallback;
    host->dwLanguageId = guest->dwLanguageId;
}

struct qemu_COMBOBOXINFO
{
    DWORD cbSize;
    RECT  rcItem;
    RECT  rcButton;
    DWORD stateButton;
    qemu_handle  hwndCombo;
    qemu_handle  hwndItem;
    qemu_handle  hwndList;
};

static inline void COMBOBOXINFO_g2h(COMBOBOXINFO *host, const struct qemu_COMBOBOXINFO *guest)
{
    host->cbSize = sizeof(*host);
    memcpy(&host->rcItem, &guest->rcItem, sizeof(host->rcItem));
    memcpy(&host->rcButton, &guest->rcButton, sizeof(host->rcButton));
    host->stateButton = guest->stateButton;
    host->hwndCombo = HANDLE_g2h(guest->hwndCombo);
    host->hwndItem = HANDLE_g2h(guest->hwndItem);
    host->hwndList = HANDLE_g2h(guest->hwndList);
}

static inline void COMBOBOXINFO_h2g(struct qemu_COMBOBOXINFO *guest, const COMBOBOXINFO *host)
{
    guest->cbSize = sizeof(*guest);
    memcpy(&guest->rcItem, &host->rcItem, sizeof(guest->rcItem));
    memcpy(&guest->rcButton, &host->rcButton, sizeof(guest->rcButton));
    guest->stateButton = host->stateButton;
    guest->hwndCombo = (ULONG_PTR)host->hwndCombo;
    guest->hwndItem = (ULONG_PTR)host->hwndItem;
    guest->hwndList = (ULONG_PTR)host->hwndList;
}

struct qemu_MSG
{
    qemu_handle     hwnd;
    UINT            message;
    qemu_ptr        wParam;
    qemu_ptr        lParam;
    DWORD           time;
    POINT           pt;
};

static inline void MSG_g2h(MSG *host, const struct qemu_MSG *guest)
{
    host->hwnd = (HWND)(ULONG_PTR)guest->hwnd;
    host->message = guest->message;
    host->wParam = guest->wParam;
    host->lParam = guest->lParam;
    host->time = guest->time;
    host->pt.x = guest->pt.x;
    host->pt.y = guest->pt.y;
}

static inline void MSG_h2g(struct qemu_MSG *guest, const MSG *host)
{
    guest->hwnd = (ULONG_PTR)host->hwnd;
    guest->message = host->message;
    guest->wParam = host->wParam;
    guest->lParam = host->lParam;
    guest->time = host->time;
    guest->pt.x = host->pt.x;
    guest->pt.y = host->pt.y;
}



#endif
