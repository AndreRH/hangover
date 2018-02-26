#ifndef HAVE_QEMU_PRSHT_H
#define HAVE_QEMU_PRSHT_H

struct qemu_PROPSHEETHEADER
{
    DWORD               dwSize;
    DWORD               dwFlags;
    qemu_handle         hwndParent;
    qemu_handle         hInstance;
    union
    {
      qemu_handle       hIcon;
      qemu_ptr          pszIcon;
    }u_1;
    qemu_ptr            pszCaption;
    UINT                nPages;
    union
    {
        UINT            nStartPage;
        qemu_ptr        pStartPage;
    }u_2;
    union
    {
        qemu_ptr        ppsp;
        qemu_ptr        phpage;
    }u_3;
    qemu_ptr            pfnCallback;
    union
    {
        qemu_handle     hbmWatermark;
        qemu_ptr        pszbmWatermark;
    }u_4;
    qemu_handle         hplWatermark;
    union
    {
        qemu_handle     hbmHeader;
        qemu_ptr        pszbmHeader;
    }u_5;
};

static inline void PROPSHEETHEADER_g2h(PROPSHEETHEADERW *host, const struct qemu_PROPSHEETHEADER *guest)
{
    host->dwSize = sizeof(*host);
    host->dwFlags = guest->dwFlags;
    host->hwndParent = HANDLE_g2h(guest->hwndParent);
    host->hInstance = HANDLE_g2h(guest->hInstance);
    /* FIXME: Need flags to tell if it is a ptr or a handle. */
    host->hIcon = HANDLE_g2h(guest->u_1.hIcon);
    host->pszCaption = (const WCHAR *)(ULONG_PTR)guest->pszCaption;
    host->nPages = guest->nPages;
    /* ptr should do, worst case we do not sign extend the UINT, which is the right thing to do. */
    host->pStartPage = (const WCHAR *)(ULONG_PTR)guest->u_2.pStartPage;
    /* Always a pointer. Note that it needs separate conversion.  */
    host->ppsp = (const PROPSHEETPAGEW *)(ULONG_PTR)guest->u_3.ppsp;
    host->pfnCallback = (PFNPROPSHEETCALLBACK)(ULONG_PTR)guest->pfnCallback;
    /* FIXME: Flags... */
    host->pszbmWatermark = (const WCHAR *)(ULONG_PTR)guest->u_4.pszbmWatermark;
    host->hplWatermark = HANDLE_g2h(guest->hplWatermark);
    /* FIXME: Flags... */
    host->pszbmHeader = (const WCHAR *)(ULONG_PTR)guest->u_5.pszbmHeader;
}

struct qemu_PROPSHEETPAGE
{
    DWORD               dwSize;
    DWORD               dwFlags;
    qemu_handle         hInstance;
    union
    {
        qemu_ptr        pszTemplate;
        qemu_ptr        pResource;
    } u_1;
    union
    {
        qemu_handle     hIcon;
        qemu_ptr        pszIcon;
    } u_2;
    qemu_ptr            pszTitle;
    qemu_ptr            pfnDlgProc;
    qemu_ptr            lParam;
    qemu_ptr            pfnCallback;
    qemu_ptr            pcRefParent;
    qemu_ptr            pszHeaderTitle;
    qemu_ptr            pszHeaderSubTitle;
    qemu_handle         hActCtx;
    union
    {
        qemu_handle     hbmHeader;
        qemu_ptr        pszbmHeader;
    } u_3;
};

#define QEMU_GUEST_PROPSHEETPAGEW_V1_SIZE CCSIZEOF_STRUCT(struct qemu_PROPSHEETPAGE, pcRefParent)
#define QEMU_GUEST_PROPSHEETPAGEW_V2_SIZE CCSIZEOF_STRUCT(struct qemu_PROPSHEETPAGE, pszHeaderSubTitle)
#define QEMU_GUEST_PROPSHEETPAGEW_V3_SIZE CCSIZEOF_STRUCT(struct qemu_PROPSHEETPAGE, hActCtx)
#define QEMU_GUEST_PROPSHEETPAGEW_V4_SIZE sizeof(struct qemu_PROPSHEETPAGE)

#define QEMU_HOST_PROPSHEETPAGEW_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEW, pcRefParent)
#define QEMU_HOST_PROPSHEETPAGEW_V2_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEW, pszHeaderSubTitle)
#define QEMU_HOST_PROPSHEETPAGEW_V3_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEW, hActCtx)
#define QEMU_HOST_PROPSHEETPAGEW_V4_SIZE sizeof(PROPSHEETPAGEW)

static inline void PROPSHEETPAGE_g2h(PROPSHEETPAGEW *host, const struct qemu_PROPSHEETPAGE *guest)
{
    memset(host, 0, sizeof(*host));

    if (guest->dwSize >= sizeof(*guest))
        host->dwSize = sizeof(*host);
    else if (guest->dwSize >= QEMU_GUEST_PROPSHEETPAGEW_V3_SIZE)
        host->dwSize = QEMU_HOST_PROPSHEETPAGEW_V3_SIZE;
    else if (guest->dwSize >= QEMU_GUEST_PROPSHEETPAGEW_V2_SIZE)
        host->dwSize = QEMU_HOST_PROPSHEETPAGEW_V2_SIZE;
    else if (guest->dwSize >= QEMU_GUEST_PROPSHEETPAGEW_V1_SIZE + 1) /* Needed for Addref handling. */
        host->dwSize = QEMU_HOST_PROPSHEETPAGEW_V1_SIZE + 1;
    else if (guest->dwSize >= QEMU_GUEST_PROPSHEETPAGEW_V1_SIZE)
        host->dwSize = QEMU_HOST_PROPSHEETPAGEW_V1_SIZE;
    else
        host->dwSize = 0;

    host->dwFlags = guest->dwFlags;
    host->hInstance = HANDLE_g2h(guest->hInstance);
    host->pResource = (void *)(ULONG_PTR)guest->u_1.pResource;
    /* FIXME: Flags. */
    host->pszIcon = (void *)(ULONG_PTR)guest->u_2.pszIcon;
    host->pszTitle = (void *)(ULONG_PTR)guest->pszTitle;
    host->pfnDlgProc = (void *)(ULONG_PTR)guest->pfnDlgProc;
    host->lParam = guest->lParam;
    host->pfnCallback = (void *)(ULONG_PTR)guest->pfnCallback;
    host->pcRefParent = (void *)(ULONG_PTR)guest->pcRefParent;
    if (guest->dwSize <= QEMU_GUEST_PROPSHEETPAGEW_V1_SIZE)
        return;

    host->pszHeaderTitle = (void *)(ULONG_PTR)guest->pszHeaderTitle;
    host->pszHeaderSubTitle = (void *)(ULONG_PTR)guest->pszHeaderSubTitle;
    if (guest->dwSize <= QEMU_GUEST_PROPSHEETPAGEW_V2_SIZE)
        return;

    host->hActCtx = HANDLE_g2h(guest->hActCtx);
    if (guest->dwSize <= QEMU_GUEST_PROPSHEETPAGEW_V3_SIZE)
        return;

    /* Why does this not exist??? */
    /* host->pszbmHeader = (void *)(ULONG_PTR)guest->u_3.pszbmHeader; */
}

struct qemu_PSHNOTIFY
{
   struct qemu_NMHDR hdr;
   qemu_ptr lParam;
};

static inline void PSHNOTIFY_g2h(PSHNOTIFY *host, const struct qemu_PSHNOTIFY *guest)
{
    NMHDR_g2h(&host->hdr, &guest->hdr);
    host->lParam = guest->lParam;
}

static inline void PSHNOTIFY_h2g(struct qemu_PSHNOTIFY *guest, const PSHNOTIFY *host)
{
    NMHDR_h2g(&guest->hdr, &host->hdr);
    guest->lParam = host->lParam;
}

#endif
