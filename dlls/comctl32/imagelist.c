/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <commctrl.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_commctrl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif


struct qemu_ImageList_Add
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t hbmImage;
    uint64_t hbmMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ImageList_Add (HIMAGELIST himl, HBITMAP hbmImage, HBITMAP hbmMask)
{
    struct qemu_ImageList_Add call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_ADD);
    call.himl = (ULONG_PTR)himl;
    call.hbmImage = (ULONG_PTR)hbmImage;
    call.hbmMask = (ULONG_PTR)hbmMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Add(struct qemu_syscall *call)
{
    struct qemu_ImageList_Add *c = (struct qemu_ImageList_Add *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_Add(QEMU_G2H(c->himl), QEMU_G2H(c->hbmImage), QEMU_G2H(c->hbmMask));
}

#endif

struct qemu_ImageList_AddIcon
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t hIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI qemu_ImageList_AddIcon (HIMAGELIST himl, HICON hIcon)
{
    struct qemu_ImageList_AddIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_ADDICON);
    call.himl = (ULONG_PTR)himl;
    call.hIcon = (ULONG_PTR)hIcon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_AddIcon(struct qemu_syscall *call)
{
    struct qemu_ImageList_AddIcon *c = (struct qemu_ImageList_AddIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_AddIcon(QEMU_G2H(c->himl), QEMU_G2H(c->hIcon));
}

#endif

struct qemu_ImageList_AddMasked
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t hBitmap;
    uint64_t clrMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ImageList_AddMasked (HIMAGELIST himl, HBITMAP hBitmap, COLORREF clrMask)
{
    struct qemu_ImageList_AddMasked call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_ADDMASKED);
    call.himl = (ULONG_PTR)himl;
    call.hBitmap = (ULONG_PTR)hBitmap;
    call.clrMask = (ULONG_PTR)clrMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_AddMasked(struct qemu_syscall *call)
{
    struct qemu_ImageList_AddMasked *c = (struct qemu_ImageList_AddMasked *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_AddMasked(QEMU_G2H(c->himl), QEMU_G2H(c->hBitmap), c->clrMask);
}

#endif

struct qemu_ImageList_BeginDrag
{
    struct qemu_syscall super;
    uint64_t himlTrack;
    uint64_t iTrack;
    uint64_t dxHotspot;
    uint64_t dyHotspot;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_BeginDrag (HIMAGELIST himlTrack, INT iTrack, INT dxHotspot, INT dyHotspot)
{
    struct qemu_ImageList_BeginDrag call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_BEGINDRAG);
    call.himlTrack = (ULONG_PTR)himlTrack;
    call.iTrack = iTrack;
    call.dxHotspot = dxHotspot;
    call.dyHotspot = dyHotspot;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_BeginDrag(struct qemu_syscall *call)
{
    struct qemu_ImageList_BeginDrag *c = (struct qemu_ImageList_BeginDrag *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_BeginDrag(QEMU_G2H(c->himlTrack), c->iTrack, c->dxHotspot, c->dyHotspot);
}

#endif

struct qemu_ImageList_Copy
{
    struct qemu_syscall super;
    uint64_t himlDst;
    uint64_t iDst;
    uint64_t himlSrc;
    uint64_t iSrc;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_Copy (HIMAGELIST himlDst, INT iDst, HIMAGELIST himlSrc, INT iSrc, UINT uFlags)
{
    struct qemu_ImageList_Copy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_COPY);
    call.himlDst = (ULONG_PTR)himlDst;
    call.iDst = iDst;
    call.himlSrc = (ULONG_PTR)himlSrc;
    call.iSrc = iSrc;
    call.uFlags = uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Copy(struct qemu_syscall *call)
{
    struct qemu_ImageList_Copy *c = (struct qemu_ImageList_Copy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_Copy(QEMU_G2H(c->himlDst), c->iDst, QEMU_G2H(c->himlSrc), c->iSrc, c->uFlags);
}

#endif

struct qemu_ImageList_Create
{
    struct qemu_syscall super;
    uint64_t cx;
    uint64_t cy;
    uint64_t flags;
    uint64_t cInitial;
    uint64_t cGrow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_Create (INT cx, INT cy, UINT flags, INT cInitial, INT cGrow)
{
    struct qemu_ImageList_Create call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_CREATE);
    call.cx = (ULONG_PTR)cx;
    call.cy = (ULONG_PTR)cy;
    call.flags = (ULONG_PTR)flags;
    call.cInitial = (ULONG_PTR)cInitial;
    call.cGrow = (ULONG_PTR)cGrow;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_Create(struct qemu_syscall *call)
{
    struct qemu_ImageList_Create *c = (struct qemu_ImageList_Create *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)ImageList_Create(c->cx, c->cy, c->flags, c->cInitial, c->cGrow);
}

#endif

struct qemu_ImageList_Destroy
{
    struct qemu_syscall super;
    uint64_t himl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_Destroy (HIMAGELIST himl)
{
    struct qemu_ImageList_Destroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DESTROY);
    call.himl = (ULONG_PTR)himl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Destroy(struct qemu_syscall *call)
{
    struct qemu_ImageList_Destroy *c = (struct qemu_ImageList_Destroy *)call;
    WINE_TRACE("\n");
    c->super.iret = ImageList_Destroy(QEMU_G2H(c->himl));
}

#endif

struct qemu_ImageList_DragEnter
{
    struct qemu_syscall super;
    uint64_t hwndLock;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_DragEnter (HWND hwndLock, INT x, INT y)
{
    struct qemu_ImageList_DragEnter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAGENTER);
    call.hwndLock = (ULONG_PTR)hwndLock;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_DragEnter(struct qemu_syscall *call)
{
    struct qemu_ImageList_DragEnter *c = (struct qemu_ImageList_DragEnter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_DragEnter(QEMU_G2H(c->hwndLock), c->x, c->y);
}

#endif

struct qemu_ImageList_DragLeave
{
    struct qemu_syscall super;
    uint64_t hwndLock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_DragLeave (HWND hwndLock)
{
    struct qemu_ImageList_DragLeave call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAGLEAVE);
    call.hwndLock = (ULONG_PTR)hwndLock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_DragLeave(struct qemu_syscall *call)
{
    struct qemu_ImageList_DragLeave *c = (struct qemu_ImageList_DragLeave *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_DragLeave(QEMU_G2H(c->hwndLock));
}

#endif

struct qemu_ImageList_DragMove
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_DragMove (INT x, INT y)
{
    struct qemu_ImageList_DragMove call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAGMOVE);
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_DragMove(struct qemu_syscall *call)
{
    struct qemu_ImageList_DragMove *c = (struct qemu_ImageList_DragMove *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_DragMove(c->x, c->y);
}

#endif

struct qemu_ImageList_DragShowNolock
{
    struct qemu_syscall super;
    uint64_t bShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_DragShowNolock (BOOL bShow)
{
    struct qemu_ImageList_DragShowNolock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAGSHOWNOLOCK);
    call.bShow = bShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_DragShowNolock(struct qemu_syscall *call)
{
    struct qemu_ImageList_DragShowNolock *c = (struct qemu_ImageList_DragShowNolock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_DragShowNolock(c->bShow);
}

#endif

struct qemu_ImageList_Draw
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t fStyle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_Draw (HIMAGELIST himl, INT i, HDC hdc, INT x, INT y, UINT fStyle)
{
    struct qemu_ImageList_Draw call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAW);
    call.himl = (ULONG_PTR)himl;
    call.i = i;
    call.hdc = (ULONG_PTR)hdc;
    call.x = x;
    call.y = y;
    call.fStyle = fStyle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Draw(struct qemu_syscall *call)
{
    struct qemu_ImageList_Draw *c = (struct qemu_ImageList_Draw *)call;
    WINE_TRACE("\n");
    c->super.iret = ImageList_Draw(QEMU_G2H(c->himl), c->i, QEMU_G2H(c->hdc), c->x, c->y, c->fStyle);
}

#endif

struct qemu_ImageList_DrawEx
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t dx;
    uint64_t dy;
    uint64_t rgbBk;
    uint64_t rgbFg;
    uint64_t fStyle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_DrawEx (HIMAGELIST himl, INT i, HDC hdc, INT x, INT y, INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle)
{
    struct qemu_ImageList_DrawEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAWEX);
    call.himl = (ULONG_PTR)himl;
    call.i = i;
    call.hdc = (ULONG_PTR)hdc;
    call.x = x;
    call.y = y;
    call.dx = dx;
    call.dy = dy;
    call.rgbBk = rgbBk;
    call.rgbFg = rgbFg;
    call.fStyle = fStyle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_DrawEx(struct qemu_syscall *call)
{
    struct qemu_ImageList_DrawEx *c = (struct qemu_ImageList_DrawEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_DrawEx(QEMU_G2H(c->himl), c->i, QEMU_G2H(c->hdc), c->x, c->y, c->dx, c->dy, c->rgbBk, c->rgbFg, c->fStyle);
}

#endif

struct qemu_ImageList_DrawIndirect
{
    struct qemu_syscall super;
    uint64_t pimldp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_DrawIndirect (IMAGELISTDRAWPARAMS *pimldp)
{
    struct qemu_ImageList_DrawIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DRAWINDIRECT);
    call.pimldp = (ULONG_PTR)pimldp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_DrawIndirect(struct qemu_syscall *call)
{
    struct qemu_ImageList_DrawIndirect *c = (struct qemu_ImageList_DrawIndirect *)call;
    IMAGELISTDRAWPARAMS stack, *param = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    param = QEMU_G2H(c->pimldp);
#else
    if (QEMU_G2H(c->pimldp))
        IMAGELISTDRAWPARAMS_g2h(param, QEMU_G2H(c->pimldp));
    else
        param = NULL;
#endif

    c->super.iret = ImageList_DrawIndirect(param);
}

#endif

struct qemu_ImageList_Duplicate
{
    struct qemu_syscall super;
    uint64_t himlSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_Duplicate (HIMAGELIST himlSrc)
{
    struct qemu_ImageList_Duplicate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_DUPLICATE);
    call.himlSrc = (ULONG_PTR)himlSrc;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_Duplicate(struct qemu_syscall *call)
{
    struct qemu_ImageList_Duplicate *c = (struct qemu_ImageList_Duplicate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_Duplicate(QEMU_G2H(c->himlSrc));
}

#endif

struct qemu_ImageList_EndDrag
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI ImageList_EndDrag (void)
{
    struct qemu_ImageList_EndDrag call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_ENDDRAG);

    qemu_syscall(&call.super);
}

#else

void qemu_ImageList_EndDrag(struct qemu_syscall *call)
{
    struct qemu_ImageList_EndDrag *c = (struct qemu_ImageList_EndDrag *)call;
    WINE_FIXME("Unverified!\n");
    ImageList_EndDrag();
}

#endif

struct qemu_ImageList_GetBkColor
{
    struct qemu_syscall super;
    uint64_t himl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI COLORREF WINAPI ImageList_GetBkColor (HIMAGELIST himl)
{
    struct qemu_ImageList_GetBkColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETBKCOLOR);
    call.himl = (ULONG_PTR)himl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_GetBkColor(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetBkColor *c = (struct qemu_ImageList_GetBkColor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_GetBkColor(QEMU_G2H(c->himl));
}

#endif

struct qemu_ImageList_GetDragImage
{
    struct qemu_syscall super;
    uint64_t ppt;
    uint64_t pptHotspot;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_GetDragImage (POINT *ppt, POINT *pptHotspot)
{
    struct qemu_ImageList_GetDragImage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETDRAGIMAGE);
    call.ppt = (ULONG_PTR)ppt;
    call.pptHotspot = (ULONG_PTR)pptHotspot;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_GetDragImage(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetDragImage *c = (struct qemu_ImageList_GetDragImage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_GetDragImage(QEMU_G2H(c->ppt), QEMU_G2H(c->pptHotspot));
}

#endif

struct qemu_ImageList_GetFlags
{
    struct qemu_syscall super;
    uint64_t himl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImageList_GetFlags(HIMAGELIST himl)
{
    struct qemu_ImageList_GetFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETFLAGS);
    call.himl = (ULONG_PTR)himl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ImageList_GetFlags to Wine headers? */
extern DWORD WINAPI ImageList_GetFlags(HIMAGELIST himl);
void qemu_ImageList_GetFlags(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetFlags *c = (struct qemu_ImageList_GetFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_GetFlags(QEMU_G2H(c->himl));
}

#endif

struct qemu_ImageList_GetIcon
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t fStyle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ImageList_GetIcon (HIMAGELIST himl, INT i, UINT fStyle)
{
    struct qemu_ImageList_GetIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETICON);
    call.himl = (ULONG_PTR)himl;
    call.i = (ULONG_PTR)i;
    call.fStyle = (ULONG_PTR)fStyle;

    qemu_syscall(&call.super);

    return (HICON)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_GetIcon(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetIcon *c = (struct qemu_ImageList_GetIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_GetIcon(QEMU_G2H(c->himl), c->i, c->fStyle);
}

#endif

struct qemu_ImageList_GetIconSize
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t cx;
    uint64_t cy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_GetIconSize (HIMAGELIST himl, INT *cx, INT *cy)
{
    struct qemu_ImageList_GetIconSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETICONSIZE);
    call.himl = (ULONG_PTR)himl;
    call.cx = (ULONG_PTR)cx;
    call.cy = (ULONG_PTR)cy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_GetIconSize(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetIconSize *c = (struct qemu_ImageList_GetIconSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_GetIconSize(QEMU_G2H(c->himl), QEMU_G2H(c->cx), QEMU_G2H(c->cy));
}

#endif

struct qemu_ImageList_GetImageCount
{
    struct qemu_syscall super;
    uint64_t himl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ImageList_GetImageCount (HIMAGELIST himl)
{
    struct qemu_ImageList_GetImageCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETIMAGECOUNT);
    call.himl = (ULONG_PTR)himl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_GetImageCount(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetImageCount *c = (struct qemu_ImageList_GetImageCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_GetImageCount(QEMU_G2H(c->himl));
}

#endif

struct qemu_ImageList_GetImageInfo
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t pImageInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_GetImageInfo (HIMAGELIST himl, INT i, IMAGEINFO *pImageInfo)
{
    struct qemu_ImageList_GetImageInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETIMAGEINFO);
    call.himl = (ULONG_PTR)himl;
    call.i = i;
    call.pImageInfo = (ULONG_PTR)pImageInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_GetImageInfo(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetImageInfo *c = (struct qemu_ImageList_GetImageInfo *)call;
    IMAGEINFO stack, *info = &stack;
    struct qemu_IMAGEINFO *info32;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->pImageInfo);
#else
    if (!QEMU_G2H(c->pImageInfo))
        info = NULL;
#endif

    c->super.iret = ImageList_GetImageInfo(QEMU_G2H(c->himl), c->i, info);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret)
        IMAGEINFO_h2g(QEMU_G2H(c->pImageInfo), info);
#endif
}

#endif

struct qemu_ImageList_GetImageRect
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t lpRect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_GetImageRect (HIMAGELIST himl, INT i, LPRECT lpRect)
{
    struct qemu_ImageList_GetImageRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_GETIMAGERECT);
    call.himl = (ULONG_PTR)himl;
    call.i = i;
    call.lpRect = (ULONG_PTR)lpRect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_GetImageRect(struct qemu_syscall *call)
{
    struct qemu_ImageList_GetImageRect *c = (struct qemu_ImageList_GetImageRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_GetImageRect(QEMU_G2H(c->himl), c->i, QEMU_G2H(c->lpRect));
}

#endif

struct qemu_ImageList_LoadImageA
{
    struct qemu_syscall super;
    uint64_t hi;
    uint64_t lpbmp;
    uint64_t cx;
    uint64_t cGrow;
    uint64_t clrMask;
    uint64_t uType;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_LoadImageA (HINSTANCE hi, LPCSTR lpbmp, INT cx, INT cGrow, COLORREF clrMask, UINT uType, UINT uFlags)
{
    struct qemu_ImageList_LoadImageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_LOADIMAGEA);
    call.hi = (ULONG_PTR)hi;
    call.lpbmp = (ULONG_PTR)lpbmp;
    call.cx = (ULONG_PTR)cx;
    call.cGrow = (ULONG_PTR)cGrow;
    call.clrMask = (ULONG_PTR)clrMask;
    call.uType = (ULONG_PTR)uType;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_LoadImageA(struct qemu_syscall *call)
{
    struct qemu_ImageList_LoadImageA *c = (struct qemu_ImageList_LoadImageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_LoadImageA(QEMU_G2H(c->hi), QEMU_G2H(c->lpbmp), c->cx, c->cGrow, c->clrMask, c->uType, c->uFlags);
}

#endif

struct qemu_ImageList_LoadImageW
{
    struct qemu_syscall super;
    uint64_t hi;
    uint64_t lpbmp;
    uint64_t cx;
    uint64_t cGrow;
    uint64_t clrMask;
    uint64_t uType;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_LoadImageW (HINSTANCE hi, LPCWSTR lpbmp, INT cx, INT cGrow, COLORREF clrMask, UINT uType, UINT uFlags)
{
    struct qemu_ImageList_LoadImageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_LOADIMAGEW);
    call.hi = (ULONG_PTR)hi;
    call.lpbmp = (ULONG_PTR)lpbmp;
    call.cx = (ULONG_PTR)cx;
    call.cGrow = (ULONG_PTR)cGrow;
    call.clrMask = (ULONG_PTR)clrMask;
    call.uType = (ULONG_PTR)uType;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_LoadImageW(struct qemu_syscall *call)
{
    struct qemu_ImageList_LoadImageW *c = (struct qemu_ImageList_LoadImageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_LoadImageW(QEMU_G2H(c->hi), QEMU_G2H(c->lpbmp), c->cx, c->cGrow, c->clrMask, c->uType, c->uFlags);
}

#endif

struct qemu_ImageList_Merge
{
    struct qemu_syscall super;
    uint64_t himl1;
    uint64_t i1;
    uint64_t himl2;
    uint64_t i2;
    uint64_t dx;
    uint64_t dy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_Merge (HIMAGELIST himl1, INT i1, HIMAGELIST himl2, INT i2, INT dx, INT dy)
{
    struct qemu_ImageList_Merge call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_MERGE);
    call.himl1 = (ULONG_PTR)himl1;
    call.i1 = (ULONG_PTR)i1;
    call.himl2 = (ULONG_PTR)himl2;
    call.i2 = (ULONG_PTR)i2;
    call.dx = (ULONG_PTR)dx;
    call.dy = (ULONG_PTR)dy;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_Merge(struct qemu_syscall *call)
{
    struct qemu_ImageList_Merge *c = (struct qemu_ImageList_Merge *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_Merge(QEMU_G2H(c->himl1), c->i1, QEMU_G2H(c->himl2), c->i2, c->dx, c->dy);
}

#endif

struct qemu_ImageList_Read
{
    struct qemu_syscall super;
    uint64_t pstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HIMAGELIST WINAPI ImageList_Read(IStream *pstm)
{
    struct qemu_ImageList_Read call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_READ);
    call.pstm = (ULONG_PTR)pstm;

    qemu_syscall(&call.super);

    return (HIMAGELIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ImageList_Read(struct qemu_syscall *call)
{
    struct qemu_ImageList_Read *c = (struct qemu_ImageList_Read *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ImageList_Read(QEMU_G2H(c->pstm));
}

#endif

struct qemu_ImageList_Remove
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_Remove (HIMAGELIST himl, INT i)
{
    struct qemu_ImageList_Remove call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_REMOVE);
    call.himl = (ULONG_PTR)himl;
    call.i = i;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Remove(struct qemu_syscall *call)
{
    struct qemu_ImageList_Remove *c = (struct qemu_ImageList_Remove *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_Remove(QEMU_G2H(c->himl), c->i);
}

#endif

struct qemu_ImageList_Replace
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t hbmImage;
    uint64_t hbmMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_Replace (HIMAGELIST himl, INT i, HBITMAP hbmImage, HBITMAP hbmMask)
{
    struct qemu_ImageList_Replace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_REPLACE);
    call.himl = (ULONG_PTR)himl;
    call.i = i;
    call.hbmImage = (ULONG_PTR)hbmImage;
    call.hbmMask = (ULONG_PTR)hbmMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Replace(struct qemu_syscall *call)
{
    struct qemu_ImageList_Replace *c = (struct qemu_ImageList_Replace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_Replace(QEMU_G2H(c->himl), c->i, QEMU_G2H(c->hbmImage), QEMU_G2H(c->hbmMask));
}

#endif

struct qemu_ImageList_ReplaceIcon
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t nIndex;
    uint64_t hIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ImageList_ReplaceIcon (HIMAGELIST himl, INT nIndex, HICON hIcon)
{
    struct qemu_ImageList_ReplaceIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_REPLACEICON);
    call.himl = (ULONG_PTR)himl;
    call.nIndex = (ULONG_PTR)nIndex;
    call.hIcon = (ULONG_PTR)hIcon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_ReplaceIcon(struct qemu_syscall *call)
{
    struct qemu_ImageList_ReplaceIcon *c = (struct qemu_ImageList_ReplaceIcon *)call;
    WINE_TRACE("\n");
    c->super.iret = ImageList_ReplaceIcon(QEMU_G2H(c->himl), c->nIndex, QEMU_G2H(c->hIcon));
}

#endif

struct qemu_ImageList_SetBkColor
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t clrBk;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI COLORREF WINAPI ImageList_SetBkColor (HIMAGELIST himl, COLORREF clrBk)
{
    struct qemu_ImageList_SetBkColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETBKCOLOR);
    call.himl = (ULONG_PTR)himl;
    call.clrBk = (ULONG_PTR)clrBk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_SetBkColor(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetBkColor *c = (struct qemu_ImageList_SetBkColor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_SetBkColor(QEMU_G2H(c->himl), c->clrBk);
}

#endif

struct qemu_ImageList_SetDragCursorImage
{
    struct qemu_syscall super;
    uint64_t himlDrag;
    uint64_t iDrag;
    uint64_t dxHotspot;
    uint64_t dyHotspot;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_SetDragCursorImage (HIMAGELIST himlDrag, INT iDrag, INT dxHotspot, INT dyHotspot)
{
    struct qemu_ImageList_SetDragCursorImage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETDRAGCURSORIMAGE);
    call.himlDrag = (ULONG_PTR)himlDrag;
    call.iDrag = iDrag;
    call.dxHotspot = dxHotspot;
    call.dyHotspot = dyHotspot;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_SetDragCursorImage(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetDragCursorImage *c = (struct qemu_ImageList_SetDragCursorImage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_SetDragCursorImage(QEMU_G2H(c->himlDrag), c->iDrag, c->dxHotspot, c->dyHotspot);
}

#endif

struct qemu_ImageList_SetFilter
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t i;
    uint64_t dwFilter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_SetFilter (HIMAGELIST himl, INT i, DWORD dwFilter)
{
    struct qemu_ImageList_SetFilter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETFILTER);
    call.himl = (ULONG_PTR)himl;
    call.i = i;
    call.dwFilter = dwFilter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ImageList_SetFilter to Wine headers? */
extern BOOL WINAPI ImageList_SetFilter (HIMAGELIST himl, INT i, DWORD dwFilter);
void qemu_ImageList_SetFilter(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetFilter *c = (struct qemu_ImageList_SetFilter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_SetFilter(QEMU_G2H(c->himl), c->i, c->dwFilter);
}

#endif

struct qemu_ImageList_SetFlags
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ImageList_SetFlags(HIMAGELIST himl, DWORD flags)
{
    struct qemu_ImageList_SetFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETFLAGS);
    call.himl = (ULONG_PTR)himl;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ImageList_SetFlags to Wine headers? */
extern DWORD WINAPI ImageList_SetFlags(HIMAGELIST himl, DWORD flags);
void qemu_ImageList_SetFlags(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetFlags *c = (struct qemu_ImageList_SetFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_SetFlags(QEMU_G2H(c->himl), c->flags);
}

#endif

struct qemu_ImageList_SetIconSize
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t cx;
    uint64_t cy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_SetIconSize (HIMAGELIST himl, INT cx, INT cy)
{
    struct qemu_ImageList_SetIconSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETICONSIZE);
    call.himl = (ULONG_PTR)himl;
    call.cx = cx;
    call.cy = cy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_SetIconSize(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetIconSize *c = (struct qemu_ImageList_SetIconSize *)call;
    WINE_TRACE("\n");
    c->super.iret = ImageList_SetIconSize(QEMU_G2H(c->himl), c->cx, c->cy);
}

#endif

struct qemu_ImageList_SetImageCount
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t iImageCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_SetImageCount (HIMAGELIST himl, UINT iImageCount)
{
    struct qemu_ImageList_SetImageCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETIMAGECOUNT);
    call.himl = (ULONG_PTR)himl;
    call.iImageCount = iImageCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_SetImageCount(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetImageCount *c = (struct qemu_ImageList_SetImageCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_SetImageCount(QEMU_G2H(c->himl), c->iImageCount);
}

#endif

struct qemu_ImageList_SetOverlayImage
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t iImage;
    uint64_t iOverlay;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_SetOverlayImage (HIMAGELIST himl, INT iImage, INT iOverlay)
{
    struct qemu_ImageList_SetOverlayImage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETOVERLAYIMAGE);
    call.himl = (ULONG_PTR)himl;
    call.iImage = iImage;
    call.iOverlay = iOverlay;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_SetOverlayImage(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetOverlayImage *c = (struct qemu_ImageList_SetOverlayImage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_SetOverlayImage(QEMU_G2H(c->himl), c->iImage, c->iOverlay);
}

#endif

struct qemu_ImageList_Write
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t pstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ImageList_Write(HIMAGELIST himl, IStream *pstm)
{
    struct qemu_ImageList_Write call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_WRITE);
    call.himl = (ULONG_PTR)himl;
    call.pstm = (ULONG_PTR)pstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_Write(struct qemu_syscall *call)
{
    struct qemu_ImageList_Write *c = (struct qemu_ImageList_Write *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_Write(QEMU_G2H(c->himl), QEMU_G2H(c->pstm));
}

#endif

struct qemu_ImageList_SetColorTable
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t uStartIndex;
    uint64_t cEntries;
    uint64_t prgb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ImageList_SetColorTable(HIMAGELIST himl, UINT uStartIndex, UINT cEntries, const RGBQUAD *prgb)
{
    struct qemu_ImageList_SetColorTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_SETCOLORTABLE);
    call.himl = (ULONG_PTR)himl;
    call.uStartIndex = (ULONG_PTR)uStartIndex;
    call.cEntries = (ULONG_PTR)cEntries;
    call.prgb = (ULONG_PTR)prgb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ImageList_SetColorTable(struct qemu_syscall *call)
{
    struct qemu_ImageList_SetColorTable *c = (struct qemu_ImageList_SetColorTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ImageList_SetColorTable(QEMU_G2H(c->himl), c->uStartIndex, c->cEntries, QEMU_G2H(c->prgb));
}

#endif

struct qemu_ImageList_CoCreateInstance
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t punkOuter;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ImageList_CoCreateInstance (REFCLSID rclsid, const IUnknown *punkOuter, REFIID riid, void **ppv)
{
    struct qemu_ImageList_CoCreateInstance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IMAGELIST_COCREATEINSTANCE);
    call.rclsid = (ULONG_PTR)rclsid;
    call.punkOuter = (ULONG_PTR)punkOuter;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ImageList_CoCreateInstance to Wine headers? */
extern HRESULT WINAPI ImageList_CoCreateInstance (REFCLSID rclsid, const IUnknown *punkOuter, REFIID riid, void **ppv);
void qemu_ImageList_CoCreateInstance(struct qemu_syscall *call)
{
    struct qemu_ImageList_CoCreateInstance *c = (struct qemu_ImageList_CoCreateInstance *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ImageList_CoCreateInstance(QEMU_G2H(c->rclsid), QEMU_G2H(c->punkOuter), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_HIMAGELIST_QueryInterface
{
    struct qemu_syscall super;
    uint64_t himl;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI HIMAGELIST_QueryInterface (HIMAGELIST himl, REFIID riid, void **ppv)
{
    struct qemu_HIMAGELIST_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HIMAGELIST_QUERYINTERFACE);
    call.himl = (ULONG_PTR)himl;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HIMAGELIST_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_HIMAGELIST_QueryInterface *c = (struct qemu_HIMAGELIST_QueryInterface *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HIMAGELIST_QueryInterface(QEMU_G2H(c->himl), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

