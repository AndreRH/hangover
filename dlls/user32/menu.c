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

#include "windows-user-services.h"
#include "dll_list.h"
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_TrackPopupMenuEx
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wFlags;
    uint64_t x;
    uint64_t y;
    uint64_t hWnd;
    uint64_t lpTpm;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI TrackPopupMenuEx(HMENU hMenu, UINT wFlags, INT x, INT y, HWND hWnd, LPTPMPARAMS lpTpm)
{
    struct qemu_TrackPopupMenuEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACKPOPUPMENUEX);
    call.hMenu = (uint64_t)hMenu;
    call.wFlags = (uint64_t)wFlags;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.hWnd = (uint64_t)hWnd;
    call.lpTpm = (uint64_t)lpTpm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TrackPopupMenuEx(struct qemu_syscall *call)
{
    struct qemu_TrackPopupMenuEx *c = (struct qemu_TrackPopupMenuEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TrackPopupMenuEx(QEMU_G2H(c->hMenu), c->wFlags, c->x, c->y, QEMU_G2H(c->hWnd), QEMU_G2H(c->lpTpm));
}

#endif

struct qemu_TrackPopupMenu
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wFlags;
    uint64_t x;
    uint64_t y;
    uint64_t nReserved;
    uint64_t hWnd;
    uint64_t lpRect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI TrackPopupMenu(HMENU hMenu, UINT wFlags, INT x, INT y, INT nReserved, HWND hWnd, const RECT *lpRect)
{
    struct qemu_TrackPopupMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACKPOPUPMENU);
    call.hMenu = (uint64_t)hMenu;
    call.wFlags = (uint64_t)wFlags;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.nReserved = (uint64_t)nReserved;
    call.hWnd = (uint64_t)hWnd;
    call.lpRect = (uint64_t)lpRect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TrackPopupMenu(struct qemu_syscall *call)
{
    struct qemu_TrackPopupMenu *c = (struct qemu_TrackPopupMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TrackPopupMenu(QEMU_G2H(c->hMenu), c->wFlags, c->x, c->y, c->nReserved, QEMU_G2H(c->hWnd), QEMU_G2H(c->lpRect));
}

#endif

struct qemu_ChangeMenuA
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pos;
    uint64_t data;
    uint64_t id;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ChangeMenuA(HMENU hMenu, UINT pos, LPCSTR data, UINT id, UINT flags)
{
    struct qemu_ChangeMenuA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEMENUA);
    call.hMenu = (uint64_t)hMenu;
    call.pos = (uint64_t)pos;
    call.data = (uint64_t)data;
    call.id = (uint64_t)id;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeMenuA(struct qemu_syscall *call)
{
    struct qemu_ChangeMenuA *c = (struct qemu_ChangeMenuA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeMenuA(QEMU_G2H(c->hMenu), c->pos, QEMU_G2H(c->data), c->id, c->flags);
}

#endif

struct qemu_ChangeMenuW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pos;
    uint64_t data;
    uint64_t id;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ChangeMenuW(HMENU hMenu, UINT pos, LPCWSTR data, UINT id, UINT flags)
{
    struct qemu_ChangeMenuW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEMENUW);
    call.hMenu = (uint64_t)hMenu;
    call.pos = (uint64_t)pos;
    call.data = (uint64_t)data;
    call.id = (uint64_t)id;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeMenuW(struct qemu_syscall *call)
{
    struct qemu_ChangeMenuW *c = (struct qemu_ChangeMenuW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeMenuW(QEMU_G2H(c->hMenu), c->pos, QEMU_G2H(c->data), c->id, c->flags);
}

#endif

struct qemu_CheckMenuItem
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t id;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI CheckMenuItem(HMENU hMenu, UINT id, UINT flags)
{
    struct qemu_CheckMenuItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKMENUITEM);
    call.hMenu = (uint64_t)hMenu;
    call.id = (uint64_t)id;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckMenuItem(struct qemu_syscall *call)
{
    struct qemu_CheckMenuItem *c = (struct qemu_CheckMenuItem *)call;
    WINE_TRACE("\n");
    c->super.iret = CheckMenuItem(QEMU_G2H(c->hMenu), c->id, c->flags);
}

#endif

struct qemu_EnableMenuItem
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wItemID;
    uint64_t wFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnableMenuItem(HMENU hMenu, UINT wItemID, UINT wFlags)
{
    struct qemu_EnableMenuItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLEMENUITEM);
    call.hMenu = (uint64_t)hMenu;
    call.wItemID = (uint64_t)wItemID;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableMenuItem(struct qemu_syscall *call)
{
    struct qemu_EnableMenuItem *c = (struct qemu_EnableMenuItem *)call;
    WINE_TRACE("\n");
    c->super.iret = EnableMenuItem(QEMU_G2H(c->hMenu), c->wItemID, c->wFlags);
}

#endif

struct qemu_GetMenuStringA
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wItemID;
    uint64_t str;
    uint64_t nMaxSiz;
    uint64_t wFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetMenuStringA(HMENU hMenu, UINT wItemID, LPSTR str, INT nMaxSiz, UINT wFlags)
{
    struct qemu_GetMenuStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUSTRINGA);
    call.hMenu = (uint64_t)hMenu;
    call.wItemID = (uint64_t)wItemID;
    call.str = (uint64_t)str;
    call.nMaxSiz = (uint64_t)nMaxSiz;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuStringA(struct qemu_syscall *call)
{
    struct qemu_GetMenuStringA *c = (struct qemu_GetMenuStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuStringA(QEMU_G2H(c->hMenu), c->wItemID, QEMU_G2H(c->str), c->nMaxSiz, c->wFlags);
}

#endif

struct qemu_GetMenuStringW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wItemID;
    uint64_t str;
    uint64_t nMaxSiz;
    uint64_t wFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetMenuStringW(HMENU hMenu, UINT wItemID, LPWSTR str, INT nMaxSiz, UINT wFlags)
{
    struct qemu_GetMenuStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUSTRINGW);
    call.hMenu = (uint64_t)hMenu;
    call.wItemID = (uint64_t)wItemID;
    call.str = (uint64_t)str;
    call.nMaxSiz = (uint64_t)nMaxSiz;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuStringW(struct qemu_syscall *call)
{
    struct qemu_GetMenuStringW *c = (struct qemu_GetMenuStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuStringW(QEMU_G2H(c->hMenu), c->wItemID, QEMU_G2H(c->str), c->nMaxSiz, c->wFlags);
}

#endif

struct qemu_HiliteMenuItem
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hMenu;
    uint64_t wItemID;
    uint64_t wHilite;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI HiliteMenuItem(HWND hWnd, HMENU hMenu, UINT wItemID, UINT wHilite)
{
    struct qemu_HiliteMenuItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HILITEMENUITEM);
    call.hWnd = (uint64_t)hWnd;
    call.hMenu = (uint64_t)hMenu;
    call.wItemID = (uint64_t)wItemID;
    call.wHilite = (uint64_t)wHilite;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HiliteMenuItem(struct qemu_syscall *call)
{
    struct qemu_HiliteMenuItem *c = (struct qemu_HiliteMenuItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HiliteMenuItem(QEMU_G2H(c->hWnd), QEMU_G2H(c->hMenu), c->wItemID, c->wHilite);
}

#endif

struct qemu_GetMenuState
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t wItemID;
    uint64_t wFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetMenuState(HMENU hMenu, UINT wItemID, UINT wFlags)
{
    struct qemu_GetMenuState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUSTATE);
    call.hMenu = (uint64_t)hMenu;
    call.wItemID = (uint64_t)wItemID;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuState(struct qemu_syscall *call)
{
    struct qemu_GetMenuState *c = (struct qemu_GetMenuState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuState(QEMU_G2H(c->hMenu), c->wItemID, c->wFlags);
}

#endif

struct qemu_GetMenuItemCount
{
    struct qemu_syscall super;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetMenuItemCount(HMENU hMenu)
{
    struct qemu_GetMenuItemCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUITEMCOUNT);
    call.hMenu = (uint64_t)hMenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuItemCount(struct qemu_syscall *call)
{
    struct qemu_GetMenuItemCount *c = (struct qemu_GetMenuItemCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuItemCount(QEMU_G2H(c->hMenu));
}

#endif

struct qemu_GetMenuItemID
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t nPos;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetMenuItemID(HMENU hMenu, INT nPos)
{
    struct qemu_GetMenuItemID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUITEMID);
    call.hMenu = (uint64_t)hMenu;
    call.nPos = (uint64_t)nPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuItemID(struct qemu_syscall *call)
{
    struct qemu_GetMenuItemID *c = (struct qemu_GetMenuItemID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuItemID(QEMU_G2H(c->hMenu), c->nPos);
}

#endif

struct qemu_InsertMenuW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pos;
    uint64_t flags;
    uint64_t id;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InsertMenuW(HMENU hMenu, UINT pos, UINT flags, UINT_PTR id, LPCWSTR str)
{
    struct qemu_InsertMenuW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INSERTMENUW);
    call.hMenu = (uint64_t)hMenu;
    call.pos = (uint64_t)pos;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InsertMenuW(struct qemu_syscall *call)
{
    struct qemu_InsertMenuW *c = (struct qemu_InsertMenuW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InsertMenuW(QEMU_G2H(c->hMenu), c->pos, c->flags, c->id, QEMU_G2H(c->str));
}

#endif

struct qemu_InsertMenuA
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pos;
    uint64_t flags;
    uint64_t id;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InsertMenuA(HMENU hMenu, UINT pos, UINT flags, UINT_PTR id, LPCSTR str)
{
    struct qemu_InsertMenuA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INSERTMENUA);
    call.hMenu = (uint64_t)hMenu;
    call.pos = (uint64_t)pos;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InsertMenuA(struct qemu_syscall *call)
{
    struct qemu_InsertMenuA *c = (struct qemu_InsertMenuA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InsertMenuA(QEMU_G2H(c->hMenu), c->pos, c->flags, c->id, QEMU_G2H(c->str));
}

#endif

struct qemu_AppendMenuA
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t flags;
    uint64_t id;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AppendMenuA(HMENU hMenu, UINT flags, UINT_PTR id, LPCSTR data)
{
    struct qemu_AppendMenuA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_APPENDMENUA);
    call.hMenu = (uint64_t)hMenu;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AppendMenuA(struct qemu_syscall *call)
{
    struct qemu_AppendMenuA *c = (struct qemu_AppendMenuA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AppendMenuA(QEMU_G2H(c->hMenu), c->flags, c->id, QEMU_G2H(c->data));
}

#endif

struct qemu_AppendMenuW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t flags;
    uint64_t id;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AppendMenuW(HMENU hMenu, UINT flags, UINT_PTR id, LPCWSTR data)
{
    struct qemu_AppendMenuW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_APPENDMENUW);
    call.hMenu = (uint64_t)hMenu;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AppendMenuW(struct qemu_syscall *call)
{
    struct qemu_AppendMenuW *c = (struct qemu_AppendMenuW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AppendMenuW(QEMU_G2H(c->hMenu), c->flags, c->id, QEMU_G2H(c->data));
}

#endif

struct qemu_RemoveMenu
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t nPos;
    uint64_t wFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI RemoveMenu(HMENU hMenu, UINT nPos, UINT wFlags)
{
    struct qemu_RemoveMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEMENU);
    call.hMenu = (uint64_t)hMenu;
    call.nPos = (uint64_t)nPos;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveMenu(struct qemu_syscall *call)
{
    struct qemu_RemoveMenu *c = (struct qemu_RemoveMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RemoveMenu(QEMU_G2H(c->hMenu), c->nPos, c->wFlags);
}

#endif

struct qemu_DeleteMenu
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t nPos;
    uint64_t wFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DeleteMenu(HMENU hMenu, UINT nPos, UINT wFlags)
{
    struct qemu_DeleteMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEMENU);
    call.hMenu = (uint64_t)hMenu;
    call.nPos = (uint64_t)nPos;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteMenu(struct qemu_syscall *call)
{
    struct qemu_DeleteMenu *c = (struct qemu_DeleteMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteMenu(QEMU_G2H(c->hMenu), c->nPos, c->wFlags);
}

#endif

struct qemu_ModifyMenuW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pos;
    uint64_t flags;
    uint64_t id;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ModifyMenuW(HMENU hMenu, UINT pos, UINT flags, UINT_PTR id, LPCWSTR str)
{
    struct qemu_ModifyMenuW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODIFYMENUW);
    call.hMenu = (uint64_t)hMenu;
    call.pos = (uint64_t)pos;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ModifyMenuW(struct qemu_syscall *call)
{
    struct qemu_ModifyMenuW *c = (struct qemu_ModifyMenuW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ModifyMenuW(QEMU_G2H(c->hMenu), c->pos, c->flags, c->id, QEMU_G2H(c->str));
}

#endif

struct qemu_ModifyMenuA
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t pos;
    uint64_t flags;
    uint64_t id;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ModifyMenuA(HMENU hMenu, UINT pos, UINT flags, UINT_PTR id, LPCSTR str)
{
    struct qemu_ModifyMenuA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODIFYMENUA);
    call.hMenu = (uint64_t)hMenu;
    call.pos = (uint64_t)pos;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ModifyMenuA(struct qemu_syscall *call)
{
    struct qemu_ModifyMenuA *c = (struct qemu_ModifyMenuA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ModifyMenuA(QEMU_G2H(c->hMenu), c->pos, c->flags, c->id, QEMU_G2H(c->str));
}

#endif

struct qemu_CreatePopupMenu
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI CreatePopupMenu(void)
{
    struct qemu_CreatePopupMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPOPUPMENU);

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_CreatePopupMenu(struct qemu_syscall *call)
{
    struct qemu_CreatePopupMenu *c = (struct qemu_CreatePopupMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreatePopupMenu();
}

#endif

struct qemu_SetMenuItemBitmaps
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t nPos;
    uint64_t wFlags;
    uint64_t hNewUnCheck;
    uint64_t hNewCheck;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenuItemBitmaps(HMENU hMenu, UINT nPos, UINT wFlags, HBITMAP hNewUnCheck, HBITMAP hNewCheck)
{
    struct qemu_SetMenuItemBitmaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENUITEMBITMAPS);
    call.hMenu = (uint64_t)hMenu;
    call.nPos = (uint64_t)nPos;
    call.wFlags = (uint64_t)wFlags;
    call.hNewUnCheck = (uint64_t)hNewUnCheck;
    call.hNewCheck = (uint64_t)hNewCheck;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenuItemBitmaps(struct qemu_syscall *call)
{
    struct qemu_SetMenuItemBitmaps *c = (struct qemu_SetMenuItemBitmaps *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenuItemBitmaps(QEMU_G2H(c->hMenu), c->nPos, c->wFlags, QEMU_G2H(c->hNewUnCheck), QEMU_G2H(c->hNewCheck));
}

#endif

struct qemu_CreateMenu
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI CreateMenu(void)
{
    struct qemu_CreateMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMENU);

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_CreateMenu(struct qemu_syscall *call)
{
    struct qemu_CreateMenu *c = (struct qemu_CreateMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMenu();
}

#endif

struct qemu_DestroyMenu
{
    struct qemu_syscall super;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DestroyMenu(HMENU hMenu)
{
    struct qemu_DestroyMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESTROYMENU);
    call.hMenu = (uint64_t)hMenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyMenu(struct qemu_syscall *call)
{
    struct qemu_DestroyMenu *c = (struct qemu_DestroyMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DestroyMenu(QEMU_G2H(c->hMenu));
}

#endif

struct qemu_GetSystemMenu
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t bRevert;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI GetSystemMenu(HWND hWnd, BOOL bRevert)
{
    struct qemu_GetSystemMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMMENU);
    call.hWnd = (uint64_t)hWnd;
    call.bRevert = (uint64_t)bRevert;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_GetSystemMenu(struct qemu_syscall *call)
{
    struct qemu_GetSystemMenu *c = (struct qemu_GetSystemMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetSystemMenu(QEMU_G2H(c->hWnd), c->bRevert);
}

#endif

struct qemu_SetSystemMenu
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetSystemMenu(HWND hwnd, HMENU hMenu)
{
    struct qemu_SetSystemMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSTEMMENU);
    call.hwnd = (uint64_t)hwnd;
    call.hMenu = (uint64_t)hMenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSystemMenu(struct qemu_syscall *call)
{
    struct qemu_SetSystemMenu *c = (struct qemu_SetSystemMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSystemMenu(QEMU_G2H(c->hwnd), QEMU_G2H(c->hMenu));
}

#endif

struct qemu_GetMenu
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI GetMenu(HWND hWnd)
{
    struct qemu_GetMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENU);
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_GetMenu(struct qemu_syscall *call)
{
    struct qemu_GetMenu *c = (struct qemu_GetMenu *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetMenu(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_GetMenuBarInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t idObject;
    uint64_t idItem;
    uint64_t pmbi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMenuBarInfo(HWND hwnd, LONG idObject, LONG idItem, PMENUBARINFO pmbi)
{
    struct qemu_GetMenuBarInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUBARINFO);
    call.hwnd = (uint64_t)hwnd;
    call.idObject = (uint64_t)idObject;
    call.idItem = (uint64_t)idItem;
    call.pmbi = (uint64_t)pmbi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuBarInfo(struct qemu_syscall *call)
{
    struct qemu_GetMenuBarInfo *c = (struct qemu_GetMenuBarInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuBarInfo(QEMU_G2H(c->hwnd), c->idObject, c->idItem, QEMU_G2H(c->pmbi));
}

#endif

struct qemu_SetMenu
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenu(HWND hWnd, HMENU hMenu)
{
    struct qemu_SetMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENU);
    call.hWnd = (uint64_t)hWnd;
    call.hMenu = (uint64_t)hMenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenu(struct qemu_syscall *call)
{
    struct qemu_SetMenu *c = (struct qemu_SetMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenu(QEMU_G2H(c->hWnd), QEMU_G2H(c->hMenu));
}

#endif

struct qemu_GetSubMenu
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t nPos;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI GetSubMenu(HMENU hMenu, INT nPos)
{
    struct qemu_GetSubMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSUBMENU);
    call.hMenu = (uint64_t)hMenu;
    call.nPos = (uint64_t)nPos;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_GetSubMenu(struct qemu_syscall *call)
{
    struct qemu_GetSubMenu *c = (struct qemu_GetSubMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetSubMenu(QEMU_G2H(c->hMenu), c->nPos);
}

#endif

struct qemu_DrawMenuBar
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawMenuBar(HWND hWnd)
{
    struct qemu_DrawMenuBar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWMENUBAR);
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawMenuBar(struct qemu_syscall *call)
{
    struct qemu_DrawMenuBar *c = (struct qemu_DrawMenuBar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawMenuBar(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_DrawMenuBarTemp
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hDC;
    uint64_t lprect;
    uint64_t hMenu;
    uint64_t hFont;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI DrawMenuBarTemp(HWND hwnd, HDC hDC, LPRECT lprect, HMENU hMenu, HFONT hFont)
{
    struct qemu_DrawMenuBarTemp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWMENUBARTEMP);
    call.hwnd = (uint64_t)hwnd;
    call.hDC = (uint64_t)hDC;
    call.lprect = (uint64_t)lprect;
    call.hMenu = (uint64_t)hMenu;
    call.hFont = (uint64_t)hFont;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DrawMenuBarTemp to Wine headers? */
extern DWORD WINAPI DrawMenuBarTemp(HWND hwnd, HDC hDC, LPRECT lprect, HMENU hMenu, HFONT hFont);
void qemu_DrawMenuBarTemp(struct qemu_syscall *call)
{
    struct qemu_DrawMenuBarTemp *c = (struct qemu_DrawMenuBarTemp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawMenuBarTemp(QEMU_G2H(c->hwnd), QEMU_G2H(c->hDC), QEMU_G2H(c->lprect), QEMU_G2H(c->hMenu), QEMU_G2H(c->hFont));
}

#endif

struct qemu_EndMenu
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EndMenu(void)
{
    struct qemu_EndMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDMENU);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndMenu(struct qemu_syscall *call)
{
    struct qemu_EndMenu *c = (struct qemu_EndMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndMenu();
}

#endif

struct qemu_LoadMenuA
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI LoadMenuA(HINSTANCE instance, LPCSTR name)
{
    struct qemu_LoadMenuA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADMENUA);
    call.instance = (uint64_t)instance;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_LoadMenuA(struct qemu_syscall *call)
{
    struct qemu_LoadMenuA *c = (struct qemu_LoadMenuA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)LoadMenuA(QEMU_G2H(c->instance), QEMU_G2H(c->name));
}

#endif

struct qemu_LoadMenuW
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI LoadMenuW(HINSTANCE instance, LPCWSTR name)
{
    struct qemu_LoadMenuW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADMENUW);
    call.instance = (uint64_t)instance;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_LoadMenuW(struct qemu_syscall *call)
{
    struct qemu_LoadMenuW *c = (struct qemu_LoadMenuW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)LoadMenuW(QEMU_G2H(c->instance), QEMU_G2H(c->name));
}

#endif

struct qemu_LoadMenuIndirectW
{
    struct qemu_syscall super;
    uint64_t template;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI LoadMenuIndirectW(LPCVOID template)
{
    struct qemu_LoadMenuIndirectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADMENUINDIRECTW);
    call.template = (uint64_t)template;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_LoadMenuIndirectW(struct qemu_syscall *call)
{
    struct qemu_LoadMenuIndirectW *c = (struct qemu_LoadMenuIndirectW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)LoadMenuIndirectW(QEMU_G2H(c->template));
}

#endif

struct qemu_LoadMenuIndirectA
{
    struct qemu_syscall super;
    uint64_t template;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMENU WINAPI LoadMenuIndirectA(LPCVOID template)
{
    struct qemu_LoadMenuIndirectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADMENUINDIRECTA);
    call.template = (uint64_t)template;

    qemu_syscall(&call.super);

    return (HMENU)call.super.iret;
}

#else

void qemu_LoadMenuIndirectA(struct qemu_syscall *call)
{
    struct qemu_LoadMenuIndirectA *c = (struct qemu_LoadMenuIndirectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)LoadMenuIndirectA(QEMU_G2H(c->template));
}

#endif

struct qemu_IsMenu
{
    struct qemu_syscall super;
    uint64_t hmenu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsMenu(HMENU hmenu)
{
    struct qemu_IsMenu call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISMENU);
    call.hmenu = (uint64_t)hmenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsMenu(struct qemu_syscall *call)
{
    struct qemu_IsMenu *c = (struct qemu_IsMenu *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsMenu(QEMU_G2H(c->hmenu));
}

#endif

struct qemu_GetMenuItemInfoA
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t item;
    uint64_t bypos;
    uint64_t lpmii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMenuItemInfoA(HMENU hmenu, UINT item, BOOL bypos, LPMENUITEMINFOA lpmii)
{
    struct qemu_GetMenuItemInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUITEMINFOA);
    call.hmenu = (uint64_t)hmenu;
    call.item = (uint64_t)item;
    call.bypos = (uint64_t)bypos;
    call.lpmii = (uint64_t)lpmii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuItemInfoA(struct qemu_syscall *call)
{
    struct qemu_GetMenuItemInfoA *c = (struct qemu_GetMenuItemInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuItemInfoA(QEMU_G2H(c->hmenu), c->item, c->bypos, QEMU_G2H(c->lpmii));
}

#endif

struct qemu_GetMenuItemInfoW
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t item;
    uint64_t bypos;
    uint64_t lpmii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMenuItemInfoW(HMENU hmenu, UINT item, BOOL bypos, LPMENUITEMINFOW lpmii)
{
    struct qemu_GetMenuItemInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUITEMINFOW);
    call.hmenu = (uint64_t)hmenu;
    call.item = (uint64_t)item;
    call.bypos = (uint64_t)bypos;
    call.lpmii = (uint64_t)lpmii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuItemInfoW(struct qemu_syscall *call)
{
    struct qemu_GetMenuItemInfoW *c = (struct qemu_GetMenuItemInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuItemInfoW(QEMU_G2H(c->hmenu), c->item, c->bypos, QEMU_G2H(c->lpmii));
}

#endif

struct qemu_SetMenuItemInfoA
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t item;
    uint64_t bypos;
    uint64_t lpmii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenuItemInfoA(HMENU hmenu, UINT item, BOOL bypos, const MENUITEMINFOA *lpmii)
{
    struct qemu_SetMenuItemInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENUITEMINFOA);
    call.hmenu = (uint64_t)hmenu;
    call.item = (uint64_t)item;
    call.bypos = (uint64_t)bypos;
    call.lpmii = (uint64_t)lpmii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenuItemInfoA(struct qemu_syscall *call)
{
    struct qemu_SetMenuItemInfoA *c = (struct qemu_SetMenuItemInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenuItemInfoA(QEMU_G2H(c->hmenu), c->item, c->bypos, QEMU_G2H(c->lpmii));
}

#endif

struct qemu_SetMenuItemInfoW
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t item;
    uint64_t bypos;
    uint64_t lpmii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenuItemInfoW(HMENU hmenu, UINT item, BOOL bypos, const MENUITEMINFOW *lpmii)
{
    struct qemu_SetMenuItemInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENUITEMINFOW);
    call.hmenu = (uint64_t)hmenu;
    call.item = (uint64_t)item;
    call.bypos = (uint64_t)bypos;
    call.lpmii = (uint64_t)lpmii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenuItemInfoW(struct qemu_syscall *call)
{
    struct qemu_SetMenuItemInfoW *c = (struct qemu_SetMenuItemInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenuItemInfoW(QEMU_G2H(c->hmenu), c->item, c->bypos, QEMU_G2H(c->lpmii));
}

#endif

struct qemu_SetMenuDefaultItem
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t uItem;
    uint64_t bypos;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenuDefaultItem(HMENU hmenu, UINT uItem, UINT bypos)
{
    struct qemu_SetMenuDefaultItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENUDEFAULTITEM);
    call.hmenu = (uint64_t)hmenu;
    call.uItem = (uint64_t)uItem;
    call.bypos = (uint64_t)bypos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenuDefaultItem(struct qemu_syscall *call)
{
    struct qemu_SetMenuDefaultItem *c = (struct qemu_SetMenuDefaultItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenuDefaultItem(QEMU_G2H(c->hmenu), c->uItem, c->bypos);
}

#endif

struct qemu_GetMenuDefaultItem
{
    struct qemu_syscall super;
    uint64_t hmenu;
    uint64_t bypos;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetMenuDefaultItem(HMENU hmenu, UINT bypos, UINT flags)
{
    struct qemu_GetMenuDefaultItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUDEFAULTITEM);
    call.hmenu = (uint64_t)hmenu;
    call.bypos = (uint64_t)bypos;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuDefaultItem(struct qemu_syscall *call)
{
    struct qemu_GetMenuDefaultItem *c = (struct qemu_GetMenuDefaultItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuDefaultItem(QEMU_G2H(c->hmenu), c->bypos, c->flags);
}

#endif

struct qemu_InsertMenuItemA
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uItem;
    uint64_t bypos;
    uint64_t lpmii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InsertMenuItemA(HMENU hMenu, UINT uItem, BOOL bypos, const MENUITEMINFOA *lpmii)
{
    struct qemu_InsertMenuItemA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INSERTMENUITEMA);
    call.hMenu = (uint64_t)hMenu;
    call.uItem = (uint64_t)uItem;
    call.bypos = (uint64_t)bypos;
    call.lpmii = (uint64_t)lpmii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InsertMenuItemA(struct qemu_syscall *call)
{
    struct qemu_InsertMenuItemA *c = (struct qemu_InsertMenuItemA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InsertMenuItemA(QEMU_G2H(c->hMenu), c->uItem, c->bypos, QEMU_G2H(c->lpmii));
}

#endif

struct qemu_InsertMenuItemW
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t uItem;
    uint64_t bypos;
    uint64_t lpmii;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InsertMenuItemW(HMENU hMenu, UINT uItem, BOOL bypos, const MENUITEMINFOW *lpmii)
{
    struct qemu_InsertMenuItemW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INSERTMENUITEMW);
    call.hMenu = (uint64_t)hMenu;
    call.uItem = (uint64_t)uItem;
    call.bypos = (uint64_t)bypos;
    call.lpmii = (uint64_t)lpmii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InsertMenuItemW(struct qemu_syscall *call)
{
    struct qemu_InsertMenuItemW *c = (struct qemu_InsertMenuItemW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InsertMenuItemW(QEMU_G2H(c->hMenu), c->uItem, c->bypos, QEMU_G2H(c->lpmii));
}

#endif

struct qemu_CheckMenuRadioItem
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t first;
    uint64_t last;
    uint64_t check;
    uint64_t bypos;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CheckMenuRadioItem(HMENU hMenu, UINT first, UINT last, UINT check, UINT bypos)
{
    struct qemu_CheckMenuRadioItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKMENURADIOITEM);
    call.hMenu = (uint64_t)hMenu;
    call.first = (uint64_t)first;
    call.last = (uint64_t)last;
    call.check = (uint64_t)check;
    call.bypos = (uint64_t)bypos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CheckMenuRadioItem(struct qemu_syscall *call)
{
    struct qemu_CheckMenuRadioItem *c = (struct qemu_CheckMenuRadioItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckMenuRadioItem(QEMU_G2H(c->hMenu), c->first, c->last, c->check, c->bypos);
}

#endif

struct qemu_GetMenuItemRect
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hMenu;
    uint64_t uItem;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMenuItemRect(HWND hwnd, HMENU hMenu, UINT uItem, RECT *rect)
{
    struct qemu_GetMenuItemRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUITEMRECT);
    call.hwnd = (uint64_t)hwnd;
    call.hMenu = (uint64_t)hMenu;
    call.uItem = (uint64_t)uItem;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuItemRect(struct qemu_syscall *call)
{
    struct qemu_GetMenuItemRect *c = (struct qemu_GetMenuItemRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuItemRect(QEMU_G2H(c->hwnd), QEMU_G2H(c->hMenu), c->uItem, QEMU_G2H(c->rect));
}

#endif

struct qemu_SetMenuInfo
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t lpmi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenuInfo (HMENU hMenu, LPCMENUINFO lpmi)
{
    struct qemu_SetMenuInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENUINFO);
    call.hMenu = (uint64_t)hMenu;
    call.lpmi = (uint64_t)lpmi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenuInfo(struct qemu_syscall *call)
{
    struct qemu_SetMenuInfo *c = (struct qemu_SetMenuInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenuInfo(QEMU_G2H(c->hMenu), QEMU_G2H(c->lpmi));
}

#endif

struct qemu_GetMenuInfo
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t lpmi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMenuInfo (HMENU hMenu, LPMENUINFO lpmi)
{
    struct qemu_GetMenuInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUINFO);
    call.hMenu = (uint64_t)hMenu;
    call.lpmi = (uint64_t)lpmi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuInfo(struct qemu_syscall *call)
{
    struct qemu_GetMenuInfo *c = (struct qemu_GetMenuInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuInfo(QEMU_G2H(c->hMenu), QEMU_G2H(c->lpmi));
}

#endif

struct qemu_SetMenuContextHelpId
{
    struct qemu_syscall super;
    uint64_t hMenu;
    uint64_t dwContextHelpID;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetMenuContextHelpId(HMENU hMenu, DWORD dwContextHelpID)
{
    struct qemu_SetMenuContextHelpId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMENUCONTEXTHELPID);
    call.hMenu = (uint64_t)hMenu;
    call.dwContextHelpID = (uint64_t)dwContextHelpID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMenuContextHelpId(struct qemu_syscall *call)
{
    struct qemu_SetMenuContextHelpId *c = (struct qemu_SetMenuContextHelpId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMenuContextHelpId(QEMU_G2H(c->hMenu), c->dwContextHelpID);
}

#endif

struct qemu_GetMenuContextHelpId
{
    struct qemu_syscall super;
    uint64_t hMenu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetMenuContextHelpId(HMENU hMenu)
{
    struct qemu_GetMenuContextHelpId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMENUCONTEXTHELPID);
    call.hMenu = (uint64_t)hMenu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMenuContextHelpId(struct qemu_syscall *call)
{
    struct qemu_GetMenuContextHelpId *c = (struct qemu_GetMenuContextHelpId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMenuContextHelpId(QEMU_G2H(c->hMenu));
}

#endif

struct qemu_TranslateAcceleratorA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hAccel;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI TranslateAcceleratorA(HWND hWnd, HACCEL hAccel, LPMSG msg)
{
    struct qemu_TranslateAcceleratorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEACCELERATORA);
    call.hWnd = (uint64_t)hWnd;
    call.hAccel = (uint64_t)hAccel;
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateAcceleratorA(struct qemu_syscall *call)
{
    struct qemu_TranslateAcceleratorA *c = (struct qemu_TranslateAcceleratorA *)call;
    WINE_TRACE("\n");
    c->super.iret = TranslateAcceleratorA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hAccel), QEMU_G2H(c->msg));
}

#endif

struct qemu_TranslateAcceleratorW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hAccel;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI TranslateAcceleratorW(HWND hWnd, HACCEL hAccel, LPMSG msg)
{
    struct qemu_TranslateAcceleratorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEACCELERATORW);
    call.hWnd = (uint64_t)hWnd;
    call.hAccel = (uint64_t)hAccel;
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateAcceleratorW(struct qemu_syscall *call)
{
    struct qemu_TranslateAcceleratorW *c = (struct qemu_TranslateAcceleratorW *)call;
    WINE_TRACE("\n");
    c->super.iret = TranslateAcceleratorW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hAccel), QEMU_G2H(c->msg));
}

#endif

