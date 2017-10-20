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
#include <shlwapi.h>
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

typedef void *LPFNFMCALLBACK;

struct qemu_FileMenu_Create
{
    struct qemu_syscall super;
    uint64_t crBorderColor;
    uint64_t nBorderWidth;
    uint64_t hBorderBmp;
    uint64_t nSelHeight;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMENU WINAPI FileMenu_Create (COLORREF crBorderColor, int nBorderWidth, HBITMAP hBorderBmp, int nSelHeight, UINT uFlags)
{
    struct qemu_FileMenu_Create call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_CREATE);
    call.crBorderColor = crBorderColor;
    call.nBorderWidth = nBorderWidth;
    call.hBorderBmp = (ULONG_PTR)hBorderBmp;
    call.nSelHeight = nSelHeight;
    call.uFlags = uFlags;

    qemu_syscall(&call.super);

    return (HMENU)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add FileMenu_Create to Wine headers? */
extern HMENU WINAPI FileMenu_Create (COLORREF crBorderColor, int nBorderWidth, HBITMAP hBorderBmp, int nSelHeight, UINT uFlags);
void qemu_FileMenu_Create(struct qemu_syscall *call)
{
    struct qemu_FileMenu_Create *c = (struct qemu_FileMenu_Create *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FileMenu_Create(c->crBorderColor, c->nBorderWidth, QEMU_G2H(c->hBorderBmp), c->nSelHeight, c->uFlags);
}

#endif

struct qemu_FileMenu_Destroy
{
    struct qemu_syscall super;
    uint64_t hmenu;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FileMenu_Destroy (HMENU hmenu)
{
    struct qemu_FileMenu_Destroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DESTROY);
    call.hmenu = (ULONG_PTR)hmenu;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add FileMenu_Destroy to Wine headers? */
extern void WINAPI FileMenu_Destroy (HMENU hmenu);
void qemu_FileMenu_Destroy(struct qemu_syscall *call)
{
    struct qemu_FileMenu_Destroy *c = (struct qemu_FileMenu_Destroy *)call;
    WINE_FIXME("Unverified!\n");
    FileMenu_Destroy(QEMU_G2H(c->hmenu));
}

#endif

struct qemu_FileMenu_AppendItemAW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t lpText;
    uint64_t uID;
    uint64_t icon;
    uint64_t hMenuPopup;
    uint64_t nItemHeight;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_AppendItemAW(HMENU hMenu, LPCVOID lpText, UINT uID, int icon, HMENU hMenuPopup, int nItemHeight)
{
    struct qemu_FileMenu_AppendItemAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_APPENDITEMAW);
    call.hMenu = (ULONG_PTR)hMenu;
    call.lpText = (ULONG_PTR)lpText;
    call.uID = uID;
    call.icon = icon;
    call.hMenuPopup = (ULONG_PTR)hMenuPopup;
    call.nItemHeight = nItemHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_AppendItemAW to Wine headers? */
extern BOOL WINAPI FileMenu_AppendItem(HMENU hMenu, LPCVOID lpText, UINT uID, int icon, HMENU hMenuPopup, int nItemHeight);
void qemu_FileMenu_AppendItemAW(struct qemu_syscall *call)
{
    struct qemu_FileMenu_AppendItemAW *c = (struct qemu_FileMenu_AppendItemAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_AppendItem(QEMU_G2H(c->hMenu), QEMU_G2H(c->lpText), c->uID, c->icon, QEMU_G2H(c->hMenuPopup), c->nItemHeight);
}

#endif

struct qemu_FileMenu_InsertUsingPidl
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t uID;
    uint64_t pidl;
    uint64_t uFlags;
    uint64_t uEnumFlags;
    uint64_t lpfnCallback;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI FileMenu_InsertUsingPidl (HMENU hmenu, UINT uID, LPCITEMIDLIST pidl, UINT uFlags, UINT uEnumFlags, LPFNFMCALLBACK lpfnCallback)
{
    struct qemu_FileMenu_InsertUsingPidl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_INSERTUSINGPIDL);
    call.hmenu = (ULONG_PTR)hmenu;
    call.uID = uID;
    call.pidl = (ULONG_PTR)pidl;
    call.uFlags = uFlags;
    call.uEnumFlags = uEnumFlags;
    call.lpfnCallback = (ULONG_PTR)lpfnCallback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_InsertUsingPidl to Wine headers? */
extern int WINAPI FileMenu_InsertUsingPidl (HMENU hmenu, UINT uID, LPCITEMIDLIST pidl, UINT uFlags, UINT uEnumFlags, LPFNFMCALLBACK lpfnCallback);
void qemu_FileMenu_InsertUsingPidl(struct qemu_syscall *call)
{
    struct qemu_FileMenu_InsertUsingPidl *c = (struct qemu_FileMenu_InsertUsingPidl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_InsertUsingPidl(QEMU_G2H(c->hmenu), c->uID, QEMU_G2H(c->pidl), c->uFlags, c->uEnumFlags, QEMU_G2H(c->lpfnCallback));
}

#endif

struct qemu_FileMenu_ReplaceUsingPidl
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t uID;
    uint64_t pidl;
    uint64_t uEnumFlags;
    uint64_t lpfnCallback;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI FileMenu_ReplaceUsingPidl(HMENU hmenu, UINT uID, LPCITEMIDLIST pidl, UINT uEnumFlags, LPFNFMCALLBACK lpfnCallback)
{
    struct qemu_FileMenu_ReplaceUsingPidl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_REPLACEUSINGPIDL);
    call.hmenu = (ULONG_PTR)hmenu;
    call.uID = uID;
    call.pidl = (ULONG_PTR)pidl;
    call.uEnumFlags = uEnumFlags;
    call.lpfnCallback = (ULONG_PTR)lpfnCallback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_ReplaceUsingPidl to Wine headers? */
extern int WINAPI FileMenu_ReplaceUsingPidl(HMENU hmenu, UINT uID, LPCITEMIDLIST pidl, UINT uEnumFlags, LPFNFMCALLBACK lpfnCallback);
void qemu_FileMenu_ReplaceUsingPidl(struct qemu_syscall *call)
{
    struct qemu_FileMenu_ReplaceUsingPidl *c = (struct qemu_FileMenu_ReplaceUsingPidl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_ReplaceUsingPidl(QEMU_G2H(c->hmenu), c->uID, QEMU_G2H(c->pidl), c->uEnumFlags, QEMU_G2H(c->lpfnCallback));
}

#endif

struct qemu_FileMenu_Invalidate
{
    struct qemu_syscall super;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FileMenu_Invalidate (HMENU hMenu)
{
    struct qemu_FileMenu_Invalidate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_INVALIDATE);
    call.hMenu = (ULONG_PTR)hMenu;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add FileMenu_Invalidate to Wine headers? */
extern void WINAPI FileMenu_Invalidate (HMENU hMenu);
void qemu_FileMenu_Invalidate(struct qemu_syscall *call)
{
    struct qemu_FileMenu_Invalidate *c = (struct qemu_FileMenu_Invalidate *)call;
    WINE_FIXME("Unverified!\n");
    FileMenu_Invalidate(QEMU_G2H(c->hMenu));
}

#endif

struct qemu_FileMenu_FindSubMenuByPidl
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMENU WINAPI FileMenu_FindSubMenuByPidl(HMENU hMenu, LPCITEMIDLIST pidl)
{
    struct qemu_FileMenu_FindSubMenuByPidl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_FINDSUBMENUBYPIDL);
    call.hMenu = (ULONG_PTR)hMenu;
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return (HMENU)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add FileMenu_FindSubMenuByPidl to Wine headers? */
extern HMENU WINAPI FileMenu_FindSubMenuByPidl(HMENU hMenu, LPCITEMIDLIST pidl);
void qemu_FileMenu_FindSubMenuByPidl(struct qemu_syscall *call)
{
    struct qemu_FileMenu_FindSubMenuByPidl *c = (struct qemu_FileMenu_FindSubMenuByPidl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FileMenu_FindSubMenuByPidl(QEMU_G2H(c->hMenu), QEMU_G2H(c->pidl));
}

#endif

struct qemu_FileMenu_AppendFilesForPidl
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t pidl;
    uint64_t bAddSeparator;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI FileMenu_AppendFilesForPidl(HMENU hmenu, LPCITEMIDLIST pidl, BOOL bAddSeparator)
{
    struct qemu_FileMenu_AppendFilesForPidl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_APPENDFILESFORPIDL);
    call.hmenu = (ULONG_PTR)hmenu;
    call.pidl = (ULONG_PTR)pidl;
    call.bAddSeparator = bAddSeparator;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_AppendFilesForPidl to Wine headers? */
extern int WINAPI FileMenu_AppendFilesForPidl(HMENU hmenu, LPCITEMIDLIST pidl, BOOL bAddSeparator);
void qemu_FileMenu_AppendFilesForPidl(struct qemu_syscall *call)
{
    struct qemu_FileMenu_AppendFilesForPidl *c = (struct qemu_FileMenu_AppendFilesForPidl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_AppendFilesForPidl(QEMU_G2H(c->hmenu), QEMU_G2H(c->pidl), c->bAddSeparator);
}

#endif

struct qemu_FileMenu_AddFilesForPidl
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t uReserved;
    uint64_t uID;
    uint64_t pidl;
    uint64_t uFlags;
    uint64_t uEnumFlags;
    uint64_t lpfnCallback;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI FileMenu_AddFilesForPidl (HMENU hmenu, UINT uReserved, UINT uID, LPCITEMIDLIST pidl, UINT uFlags, UINT uEnumFlags, LPFNFMCALLBACK lpfnCallback)
{
    struct qemu_FileMenu_AddFilesForPidl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_ADDFILESFORPIDL);
    call.hmenu = (ULONG_PTR)hmenu;
    call.uReserved = uReserved;
    call.uID = uID;
    call.pidl = (ULONG_PTR)pidl;
    call.uFlags = uFlags;
    call.uEnumFlags = uEnumFlags;
    call.lpfnCallback = (ULONG_PTR)lpfnCallback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_AddFilesForPidl to Wine headers? */
extern int WINAPI FileMenu_AddFilesForPidl (HMENU hmenu, UINT uReserved, UINT uID, LPCITEMIDLIST pidl, UINT uFlags, UINT uEnumFlags, LPFNFMCALLBACK lpfnCallback);
void qemu_FileMenu_AddFilesForPidl(struct qemu_syscall *call)
{
    struct qemu_FileMenu_AddFilesForPidl *c = (struct qemu_FileMenu_AddFilesForPidl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_AddFilesForPidl(QEMU_G2H(c->hmenu), c->uReserved, c->uID, QEMU_G2H(c->pidl), c->uFlags, c->uEnumFlags, QEMU_G2H(c->lpfnCallback));
}

#endif

struct qemu_FileMenu_TrackPopupMenuEx
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uFlags;
    uint64_t x;
    uint64_t y;
    uint64_t hWnd;
    uint64_t lptpm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_TrackPopupMenuEx (HMENU hMenu, UINT uFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm)
{
    struct qemu_FileMenu_TrackPopupMenuEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_TRACKPOPUPMENUEX);
    call.hMenu = (ULONG_PTR)hMenu;
    call.uFlags = uFlags;
    call.x = x;
    call.y = y;
    call.hWnd = (ULONG_PTR)hWnd;
    call.lptpm = (ULONG_PTR)lptpm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_TrackPopupMenuEx to Wine headers? */
extern BOOL WINAPI FileMenu_TrackPopupMenuEx (HMENU hMenu, UINT uFlags, int x, int y, HWND hWnd, LPTPMPARAMS lptpm);
void qemu_FileMenu_TrackPopupMenuEx(struct qemu_syscall *call)
{
    struct qemu_FileMenu_TrackPopupMenuEx *c = (struct qemu_FileMenu_TrackPopupMenuEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_TrackPopupMenuEx(QEMU_G2H(c->hMenu), c->uFlags, c->x, c->y, QEMU_G2H(c->hWnd), QEMU_G2H(c->lptpm));
}

#endif

struct qemu_FileMenu_GetLastSelectedItemPidls
{
    struct qemu_syscall super;
    uint64_t uReserved;
    uint64_t ppidlFolder;
    uint64_t ppidlItem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_GetLastSelectedItemPidls(UINT uReserved, LPCITEMIDLIST *ppidlFolder, LPCITEMIDLIST *ppidlItem)
{
    struct qemu_FileMenu_GetLastSelectedItemPidls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_GETLASTSELECTEDITEMPIDLS);
    call.uReserved = uReserved;
    call.ppidlFolder = (ULONG_PTR)ppidlFolder;
    call.ppidlItem = (ULONG_PTR)ppidlItem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_GetLastSelectedItemPidls to Wine headers? */
extern BOOL WINAPI FileMenu_GetLastSelectedItemPidls(UINT uReserved, LPCITEMIDLIST *ppidlFolder, LPCITEMIDLIST *ppidlItem);
void qemu_FileMenu_GetLastSelectedItemPidls(struct qemu_syscall *call)
{
    struct qemu_FileMenu_GetLastSelectedItemPidls *c = (struct qemu_FileMenu_GetLastSelectedItemPidls *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_GetLastSelectedItemPidls(c->uReserved, QEMU_G2H(c->ppidlFolder), QEMU_G2H(c->ppidlItem));
}

#endif

struct qemu_FileMenu_MeasureItem
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t lpmis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI FileMenu_MeasureItem(HWND hWnd, LPMEASUREITEMSTRUCT lpmis)
{
    struct qemu_FileMenu_MeasureItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_MEASUREITEM);
    call.hWnd = (ULONG_PTR)hWnd;
    call.lpmis = (ULONG_PTR)lpmis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_MeasureItem to Wine headers? */
extern LRESULT WINAPI FileMenu_MeasureItem(HWND hWnd, LPMEASUREITEMSTRUCT lpmis);
void qemu_FileMenu_MeasureItem(struct qemu_syscall *call)
{
    struct qemu_FileMenu_MeasureItem *c = (struct qemu_FileMenu_MeasureItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_MeasureItem(QEMU_G2H(c->hWnd), QEMU_G2H(c->lpmis));
}

#endif

struct qemu_FileMenu_DrawItem
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t lpdis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI FileMenu_DrawItem(HWND hWnd, LPDRAWITEMSTRUCT lpdis)
{
    struct qemu_FileMenu_DrawItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DRAWITEM);
    call.hWnd = (ULONG_PTR)hWnd;
    call.lpdis = (ULONG_PTR)lpdis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_DrawItem to Wine headers? */
extern LRESULT WINAPI FileMenu_DrawItem(HWND hWnd, LPDRAWITEMSTRUCT lpdis);
void qemu_FileMenu_DrawItem(struct qemu_syscall *call)
{
    struct qemu_FileMenu_DrawItem *c = (struct qemu_FileMenu_DrawItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_DrawItem(QEMU_G2H(c->hWnd), QEMU_G2H(c->lpdis));
}

#endif

struct qemu_FileMenu_InitMenuPopup
{
    struct qemu_syscall super;
    uint64_t hmenu;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_InitMenuPopup (HMENU hmenu)
{
    struct qemu_FileMenu_InitMenuPopup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_INITMENUPOPUP);
    call.hmenu = (ULONG_PTR)hmenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_InitMenuPopup to Wine headers? */
extern BOOL WINAPI FileMenu_InitMenuPopup (HMENU hmenu);
void qemu_FileMenu_InitMenuPopup(struct qemu_syscall *call)
{
    struct qemu_FileMenu_InitMenuPopup *c = (struct qemu_FileMenu_InitMenuPopup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_InitMenuPopup(QEMU_G2H(c->hmenu));
}

#endif

struct qemu_FileMenu_HandleMenuChar
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI FileMenu_HandleMenuChar(HMENU hMenu, WPARAM wParam)
{
    struct qemu_FileMenu_HandleMenuChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_HANDLEMENUCHAR);
    call.hMenu = (ULONG_PTR)hMenu;
    call.wParam = wParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_HandleMenuChar to Wine headers? */
extern LRESULT WINAPI FileMenu_HandleMenuChar(HMENU hMenu, WPARAM wParam);
void qemu_FileMenu_HandleMenuChar(struct qemu_syscall *call)
{
    struct qemu_FileMenu_HandleMenuChar *c = (struct qemu_FileMenu_HandleMenuChar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_HandleMenuChar(QEMU_G2H(c->hMenu), c->wParam);
}

#endif

struct qemu_FileMenu_DeleteAllItems
{
    struct qemu_syscall super;
    uint64_t hmenu;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_DeleteAllItems (HMENU hmenu)
{
    struct qemu_FileMenu_DeleteAllItems call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DELETEALLITEMS);
    call.hmenu = (ULONG_PTR)hmenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_DeleteAllItems to Wine headers? */
extern BOOL WINAPI FileMenu_DeleteAllItems (HMENU hmenu);
void qemu_FileMenu_DeleteAllItems(struct qemu_syscall *call)
{
    struct qemu_FileMenu_DeleteAllItems *c = (struct qemu_FileMenu_DeleteAllItems *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_DeleteAllItems(QEMU_G2H(c->hmenu));
}

#endif

struct qemu_FileMenu_DeleteItemByCmd
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_DeleteItemByCmd (HMENU hMenu, UINT uID)
{
    struct qemu_FileMenu_DeleteItemByCmd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DELETEITEMBYCMD);
    call.hMenu = (ULONG_PTR)hMenu;
    call.uID = uID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_DeleteItemByCmd to Wine headers? */
extern BOOL WINAPI FileMenu_DeleteItemByCmd (HMENU hMenu, UINT uID);
void qemu_FileMenu_DeleteItemByCmd(struct qemu_syscall *call)
{
    struct qemu_FileMenu_DeleteItemByCmd *c = (struct qemu_FileMenu_DeleteItemByCmd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_DeleteItemByCmd(QEMU_G2H(c->hMenu), c->uID);
}

#endif

struct qemu_FileMenu_DeleteItemByIndex
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_DeleteItemByIndex (HMENU hMenu, UINT uPos)
{
    struct qemu_FileMenu_DeleteItemByIndex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DELETEITEMBYINDEX);
    call.hMenu = (ULONG_PTR)hMenu;
    call.uPos = uPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_DeleteItemByIndex to Wine headers? */
extern BOOL WINAPI FileMenu_DeleteItemByIndex (HMENU hMenu, UINT uPos);
void qemu_FileMenu_DeleteItemByIndex(struct qemu_syscall *call)
{
    struct qemu_FileMenu_DeleteItemByIndex *c = (struct qemu_FileMenu_DeleteItemByIndex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_DeleteItemByIndex(QEMU_G2H(c->hMenu), c->uPos);
}

#endif

struct qemu_FileMenu_DeleteItemByFirstID
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_DeleteItemByFirstID(HMENU hMenu, UINT uID)
{
    struct qemu_FileMenu_DeleteItemByFirstID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DELETEITEMBYFIRSTID);
    call.hMenu = (ULONG_PTR)hMenu;
    call.uID = uID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_DeleteItemByFirstID to Wine headers? */
extern BOOL WINAPI FileMenu_DeleteItemByFirstID(HMENU hMenu, UINT uID);
void qemu_FileMenu_DeleteItemByFirstID(struct qemu_syscall *call)
{
    struct qemu_FileMenu_DeleteItemByFirstID *c = (struct qemu_FileMenu_DeleteItemByFirstID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_DeleteItemByFirstID(QEMU_G2H(c->hMenu), c->uID);
}

#endif

struct qemu_FileMenu_DeleteSeparator
{
    struct qemu_syscall super;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_DeleteSeparator(HMENU hMenu)
{
    struct qemu_FileMenu_DeleteSeparator call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_DELETESEPARATOR);
    call.hMenu = (ULONG_PTR)hMenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_DeleteSeparator to Wine headers? */
extern BOOL WINAPI FileMenu_DeleteSeparator(HMENU hMenu);
void qemu_FileMenu_DeleteSeparator(struct qemu_syscall *call)
{
    struct qemu_FileMenu_DeleteSeparator *c = (struct qemu_FileMenu_DeleteSeparator *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_DeleteSeparator(QEMU_G2H(c->hMenu));
}

#endif

struct qemu_FileMenu_EnableItemByCmd
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uID;
    uint64_t bEnable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileMenu_EnableItemByCmd(HMENU hMenu, UINT uID, BOOL bEnable)
{
    struct qemu_FileMenu_EnableItemByCmd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_ENABLEITEMBYCMD);
    call.hMenu = (ULONG_PTR)hMenu;
    call.uID = uID;
    call.bEnable = bEnable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_EnableItemByCmd to Wine headers? */
extern BOOL WINAPI FileMenu_EnableItemByCmd(HMENU hMenu, UINT uID, BOOL bEnable);
void qemu_FileMenu_EnableItemByCmd(struct qemu_syscall *call)
{
    struct qemu_FileMenu_EnableItemByCmd *c = (struct qemu_FileMenu_EnableItemByCmd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_EnableItemByCmd(QEMU_G2H(c->hMenu), c->uID, c->bEnable);
}

#endif

struct qemu_FileMenu_GetItemExtent
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uPos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI FileMenu_GetItemExtent (HMENU hMenu, UINT uPos)
{
    struct qemu_FileMenu_GetItemExtent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_GETITEMEXTENT);
    call.hMenu = (ULONG_PTR)hMenu;
    call.uPos = uPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FileMenu_GetItemExtent to Wine headers? */
extern DWORD WINAPI FileMenu_GetItemExtent (HMENU hMenu, UINT uPos);
void qemu_FileMenu_GetItemExtent(struct qemu_syscall *call)
{
    struct qemu_FileMenu_GetItemExtent *c = (struct qemu_FileMenu_GetItemExtent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileMenu_GetItemExtent(QEMU_G2H(c->hMenu), c->uPos);
}

#endif

struct qemu_FileMenu_AbortInitMenu
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FileMenu_AbortInitMenu (void)
{
    struct qemu_FileMenu_AbortInitMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILEMENU_ABORTINITMENU);

    qemu_syscall(&call.super);
}

#else

/* TODO: Add FileMenu_AbortInitMenu to Wine headers? */
extern void WINAPI FileMenu_AbortInitMenu (void);
void qemu_FileMenu_AbortInitMenu(struct qemu_syscall *call)
{
    struct qemu_FileMenu_AbortInitMenu *c = (struct qemu_FileMenu_AbortInitMenu *)call;
    WINE_FIXME("Unverified!\n");
    FileMenu_AbortInitMenu();
}

#endif

struct qemu_SHFind_InitMenuPopup
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t hWndParent;
    uint64_t w;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

SHSTDAPI_(IContextMenu *) SHFind_InitMenuPopup (HMENU hMenu, HWND hWndParent, UINT w, UINT x)
{
    struct qemu_SHFind_InitMenuPopup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFIND_INITMENUPOPUP);
    call.hMenu = (ULONG_PTR)hMenu;
    call.hWndParent = (ULONG_PTR)hWndParent;
    call.w = w;
    call.x = x;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add SHFind_InitMenuPopup to Wine headers? */
extern LPVOID WINAPI SHFind_InitMenuPopup (HMENU hMenu, HWND hWndParent, DWORD w, DWORD x);
void qemu_SHFind_InitMenuPopup(struct qemu_syscall *call)
{
    struct qemu_SHFind_InitMenuPopup *c = (struct qemu_SHFind_InitMenuPopup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SHFind_InitMenuPopup(QEMU_G2H(c->hMenu), QEMU_G2H(c->hWndParent), c->w, c->x);
}

#endif

struct qemu_Shell_MergeMenus
{
    struct qemu_syscall super;
    uint64_t hmDst;
    uint64_t hmSrc;
    uint64_t uInsert;
    uint64_t uIDAdjust;
    uint64_t uIDAdjustMax;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI Shell_MergeMenus (HMENU hmDst, HMENU hmSrc, UINT uInsert, UINT uIDAdjust, UINT uIDAdjustMax, ULONG uFlags)
{
    struct qemu_Shell_MergeMenus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELL_MERGEMENUS);
    call.hmDst = (ULONG_PTR)hmDst;
    call.hmSrc = (ULONG_PTR)hmSrc;
    call.uInsert = uInsert;
    call.uIDAdjust = uIDAdjust;
    call.uIDAdjustMax = uIDAdjustMax;
    call.uFlags = uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Shell_MergeMenus(struct qemu_syscall *call)
{
    struct qemu_Shell_MergeMenus *c = (struct qemu_Shell_MergeMenus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Shell_MergeMenus(QEMU_G2H(c->hmDst), QEMU_G2H(c->hmSrc), c->uInsert, c->uIDAdjust, c->uIDAdjustMax, c->uFlags);
}

#endif

struct qemu_CDefFolderMenu_Create2
{
    struct qemu_syscall super;
    uint64_t pidlFolder;
    uint64_t hwnd;
    uint64_t cidl;
    uint64_t apidl;
    uint64_t psf;
    uint64_t lpfn;
    uint64_t nKeys;
    uint64_t ahkeys;
    uint64_t ppcm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI CDefFolderMenu_Create2(LPCITEMIDLIST pidlFolder, HWND hwnd, UINT cidl, LPCITEMIDLIST *apidl, IShellFolder *psf, LPFNDFMCALLBACK lpfn, UINT nKeys, const HKEY *ahkeys, IContextMenu **ppcm)
{
    struct qemu_CDefFolderMenu_Create2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CDEFFOLDERMENU_CREATE2);
    call.pidlFolder = (ULONG_PTR)pidlFolder;
    call.hwnd = (ULONG_PTR)hwnd;
    call.cidl = cidl;
    call.apidl = (ULONG_PTR)apidl;
    call.psf = (ULONG_PTR)psf;
    call.lpfn = (ULONG_PTR)lpfn;
    call.nKeys = nKeys;
    call.ahkeys = (ULONG_PTR)ahkeys;
    call.ppcm = (ULONG_PTR)ppcm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CDefFolderMenu_Create2(struct qemu_syscall *call)
{
    struct qemu_CDefFolderMenu_Create2 *c = (struct qemu_CDefFolderMenu_Create2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CDefFolderMenu_Create2(QEMU_G2H(c->pidlFolder), QEMU_G2H(c->hwnd), c->cidl, QEMU_G2H(c->apidl), QEMU_G2H(c->psf), QEMU_G2H(c->lpfn), c->nKeys, QEMU_G2H(c->ahkeys), QEMU_G2H(c->ppcm));
}

#endif

struct qemu_SHCreateDefaultContextMenu
{
    struct qemu_syscall super;
    uint64_t pdcm;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateDefaultContextMenu(const DEFCONTEXTMENU *pdcm, REFIID riid, void **ppv)
{
    struct qemu_SHCreateDefaultContextMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEDEFAULTCONTEXTMENU);
    call.pdcm = (ULONG_PTR)pdcm;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateDefaultContextMenu(struct qemu_syscall *call)
{
    struct qemu_SHCreateDefaultContextMenu *c = (struct qemu_SHCreateDefaultContextMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateDefaultContextMenu(QEMU_G2H(c->pdcm), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

