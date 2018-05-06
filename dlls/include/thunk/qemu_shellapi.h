#ifndef HAVE_QEMU_THUNK_SHELLAPI_H
#define HAVE_QEMU_THUNK_SHELLAPI_H

struct qemu_NOTIFYICONDATAA
{
    DWORD cbSize;
    qemu_ptr hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    qemu_ptr hIcon;
    CHAR szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    CHAR szInfo[256];
    union
    {
        UINT uTimeout;
        UINT uVersion;
    } u1;
    CHAR szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
    qemu_ptr hBalloonIcon;
};

#define qemu_NOTIFYICONDATAA_V1_SIZE FIELD_OFFSET(struct qemu_NOTIFYICONDATAA, szTip[64])

/* pre Window XP */
#define qemu_NOTIFYICONDATAA_V2_SIZE FIELD_OFFSET(struct qemu_NOTIFYICONDATAA, guidItem)

/* pre Window Vista */
#define qemu_NOTIFYICONDATAA_V3_SIZE FIELD_OFFSET(struct qemu_NOTIFYICONDATAA, hBalloonIcon)

static inline void NOTIFYICONDATAA_g2h(NOTIFYICONDATAA *host, const struct qemu_NOTIFYICONDATAA *guest)
{
    if (guest->cbSize == sizeof(*guest))
        host->cbSize = sizeof(*host);
    else if (guest->cbSize == qemu_NOTIFYICONDATAA_V1_SIZE)
        host->cbSize = NOTIFYICONDATAA_V1_SIZE;
    else if (guest->cbSize == qemu_NOTIFYICONDATAA_V2_SIZE)
        host->cbSize = NOTIFYICONDATAA_V2_SIZE;
    else
        host->cbSize = 0;

    host->hWnd = (HWND)(ULONG_PTR)guest->hWnd;
    host->uID = guest->uID;
    host->uFlags = guest->uFlags;
    host->uCallbackMessage = guest->uCallbackMessage;
    host->hIcon = (HICON)(ULONG_PTR)guest->hIcon;
    memcpy(host->szTip, guest->szTip, sizeof(host->szTip));

    if (host->cbSize <= NOTIFYICONDATAA_V1_SIZE)
        return;

    host->dwState = guest->dwState;
    host->dwStateMask = guest->dwStateMask;
    memcpy(host->szInfo, guest->szInfo, sizeof(host->szInfo));
    host->uTimeout = guest->u1.uTimeout;
    memcpy(host->szInfoTitle, guest->szInfoTitle, sizeof(host->szInfoTitle));
    host->dwInfoFlags = guest->dwInfoFlags;
    host->guidItem = guest->guidItem;

    if (host->cbSize == NOTIFYICONDATAA_V2_SIZE)
        return;

    host->hBalloonIcon = (HICON)(ULONG_PTR)guest->hBalloonIcon;
}

struct qemu_NOTIFYICONDATAW
{
    DWORD cbSize;
    qemu_ptr hWnd;
    UINT uID;
    UINT uFlags;
    UINT uCallbackMessage;
    qemu_ptr hIcon;
    WCHAR szTip[128];
    DWORD dwState;
    DWORD dwStateMask;
    WCHAR szInfo[256];
    union
    {
        UINT uTimeout;
        UINT uVersion;
    } u1;
    WCHAR szInfoTitle[64];
    DWORD dwInfoFlags;
    GUID guidItem;
    qemu_ptr hBalloonIcon;
};

#define qemu_NOTIFYICONDATAW_V2_SIZE FIELD_OFFSET(struct qemu_NOTIFYICONDATAW, guidItem)
#define qemu_NOTIFYICONDATAW_V1_SIZE FIELD_OFFSET(struct qemu_NOTIFYICONDATAW, szTip[64])
#define qemu_NOTIFYICONDATAW_V3_SIZE FIELD_OFFSET(struct qemu_NOTIFYICONDATAW, hBalloonIcon)

static inline void NOTIFYICONDATAW_g2h(NOTIFYICONDATAW *host, const struct qemu_NOTIFYICONDATAW *guest)
{
    if (guest->cbSize == sizeof(*guest))
        host->cbSize = sizeof(*host);
    else if (guest->cbSize == qemu_NOTIFYICONDATAW_V1_SIZE)
        host->cbSize = NOTIFYICONDATAW_V1_SIZE;
    else if (guest->cbSize == qemu_NOTIFYICONDATAW_V2_SIZE)
        host->cbSize = NOTIFYICONDATAW_V2_SIZE;
    else
        host->cbSize = 0;

    host->hWnd = (HWND)(ULONG_PTR)guest->hWnd;
    host->uID = guest->uID;
    host->uFlags = guest->uFlags;
    host->uCallbackMessage = guest->uCallbackMessage;
    host->hIcon = (HICON)(ULONG_PTR)guest->hIcon;
    memcpy(host->szTip, guest->szTip, sizeof(host->szTip));

    if (host->cbSize <= NOTIFYICONDATAW_V1_SIZE)
        return;

    host->dwState = guest->dwState;
    host->dwStateMask = guest->dwStateMask;
    memcpy(host->szInfo, guest->szInfo, sizeof(host->szInfo));
    host->uTimeout = guest->u1.uTimeout;
    memcpy(host->szInfoTitle, guest->szInfoTitle, sizeof(host->szInfoTitle));
    host->dwInfoFlags = guest->dwInfoFlags;
    host->guidItem = guest->guidItem;

    if (host->cbSize == NOTIFYICONDATAW_V2_SIZE)
        return;

    host->hBalloonIcon = (HICON)(ULONG_PTR)guest->hBalloonIcon;
}

struct qemu_SHFILEINFOA
{
    qemu_ptr    hIcon;
    int         iIcon;
    DWORD       dwAttributes;
    CHAR        szDisplayName[MAX_PATH];
    CHAR        szTypeName[80];
};

static inline void SHFILEINFOA_g2h(SHFILEINFOA *host, const struct qemu_SHFILEINFOA *guest)
{
    host->hIcon = (HICON)(ULONG_PTR)guest->hIcon;
    host->iIcon = guest->iIcon;
    host->dwAttributes = guest->dwAttributes;
    memcpy(host->szDisplayName, guest->szDisplayName, sizeof(host->szDisplayName));
    memcpy(host->szTypeName, guest->szTypeName, sizeof(host->szTypeName));
}

static inline void SHFILEINFOA_h2g(struct qemu_SHFILEINFOA *guest, const SHFILEINFOA *host)
{
    guest->hIcon = (ULONG_PTR)host->hIcon;
    guest->iIcon = host->iIcon;
    guest->dwAttributes = host->dwAttributes;
    memcpy(guest->szDisplayName, host->szDisplayName, sizeof(guest->szDisplayName));
    memcpy(guest->szTypeName, host->szTypeName, sizeof(guest->szTypeName));
}

struct qemu_SHFILEINFOW
{
    qemu_ptr    hIcon;
    int         iIcon;
    DWORD	dwAttributes;
    WCHAR	szDisplayName[MAX_PATH];
    WCHAR	szTypeName[80];
};

static inline void SHFILEINFOW_g2h(SHFILEINFOW *host, const struct qemu_SHFILEINFOW *guest)
{
    host->hIcon = (HICON)(ULONG_PTR)guest->hIcon;
    host->iIcon = guest->iIcon;
    host->dwAttributes = guest->dwAttributes;
    memcpy(host->szDisplayName, guest->szDisplayName, sizeof(host->szDisplayName));
    memcpy(host->szTypeName, guest->szTypeName, sizeof(host->szTypeName));
}

static inline void SHFILEINFOW_h2g(struct qemu_SHFILEINFOW *guest, const SHFILEINFOW *host)
{
    guest->hIcon = (ULONG_PTR)host->hIcon;
    guest->iIcon = host->iIcon;
    guest->dwAttributes = host->dwAttributes;
    memcpy(guest->szDisplayName, host->szDisplayName, sizeof(guest->szDisplayName));
    memcpy(guest->szTypeName, host->szTypeName, sizeof(guest->szTypeName));
}

#endif
