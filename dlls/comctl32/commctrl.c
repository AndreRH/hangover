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


struct qemu_MenuHelp
{
    struct qemu_syscall super;
    uint64_t uMsg;
    uint64_t wParam;
    uint64_t lParam;
    uint64_t hMainMenu;
    uint64_t hInst;
    uint64_t hwndStatus;
    uint64_t lpwIDs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MenuHelp (UINT uMsg, WPARAM wParam, LPARAM lParam, HMENU hMainMenu, HINSTANCE hInst, HWND hwndStatus, UINT* lpwIDs)
{
    struct qemu_MenuHelp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MENUHELP);
    call.uMsg = (ULONG_PTR)uMsg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;
    call.hMainMenu = (ULONG_PTR)hMainMenu;
    call.hInst = (ULONG_PTR)hInst;
    call.hwndStatus = (ULONG_PTR)hwndStatus;
    call.lpwIDs = (ULONG_PTR)lpwIDs;

    qemu_syscall(&call.super);
}

#else

void qemu_MenuHelp(struct qemu_syscall *call)
{
    struct qemu_MenuHelp *c = (struct qemu_MenuHelp *)call;
    WINE_FIXME("Unverified!\n");
    p_MenuHelp(c->uMsg, c->wParam, c->lParam, QEMU_G2H(c->hMainMenu), QEMU_G2H(c->hInst), QEMU_G2H(c->hwndStatus), QEMU_G2H(c->lpwIDs));
}

#endif

struct qemu_ShowHideMenuCtl
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t uFlags;
    uint64_t lpInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ShowHideMenuCtl (HWND hwnd, UINT_PTR uFlags, LPINT lpInfo)
{
    struct qemu_ShowHideMenuCtl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWHIDEMENUCTL);
    call.hwnd = (ULONG_PTR)hwnd;
    call.uFlags = (ULONG_PTR)uFlags;
    call.lpInfo = (ULONG_PTR)lpInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShowHideMenuCtl(struct qemu_syscall *call)
{
    struct qemu_ShowHideMenuCtl *c = (struct qemu_ShowHideMenuCtl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ShowHideMenuCtl(QEMU_G2H(c->hwnd), c->uFlags, QEMU_G2H(c->lpInfo));
}

#endif

struct qemu_GetEffectiveClientRect
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpRect;
    uint64_t lpInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetEffectiveClientRect (HWND hwnd, LPRECT lpRect, const INT *lpInfo)
{
    struct qemu_GetEffectiveClientRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEFFECTIVECLIENTRECT);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpRect = (ULONG_PTR)lpRect;
    call.lpInfo = (ULONG_PTR)lpInfo;

    qemu_syscall(&call.super);
}

#else

void qemu_GetEffectiveClientRect(struct qemu_syscall *call)
{
    struct qemu_GetEffectiveClientRect *c = (struct qemu_GetEffectiveClientRect *)call;
    WINE_FIXME("Unverified!\n");
    p_GetEffectiveClientRect(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpRect), QEMU_G2H(c->lpInfo));
}

#endif

struct qemu_DrawStatusTextW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lprc;
    uint64_t text;
    uint64_t style;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DrawStatusTextW (HDC hdc, LPCRECT lprc, LPCWSTR text, UINT style)
{
    struct qemu_DrawStatusTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWSTATUSTEXTW);
    call.hdc = (ULONG_PTR)hdc;
    call.lprc = (ULONG_PTR)lprc;
    call.text = (ULONG_PTR)text;
    call.style = (ULONG_PTR)style;

    qemu_syscall(&call.super);
}

#else

void qemu_DrawStatusTextW(struct qemu_syscall *call)
{
    struct qemu_DrawStatusTextW *c = (struct qemu_DrawStatusTextW *)call;
    WINE_FIXME("Unverified!\n");
    p_DrawStatusTextW(QEMU_G2H(c->hdc), QEMU_G2H(c->lprc), QEMU_G2H(c->text), c->style);
}

#endif

struct qemu_DrawStatusTextA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lprc;
    uint64_t text;
    uint64_t style;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DrawStatusTextA (HDC hdc, LPCRECT lprc, LPCSTR text, UINT style)
{
    struct qemu_DrawStatusTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWSTATUSTEXTA);
    call.hdc = (ULONG_PTR)hdc;
    call.lprc = (ULONG_PTR)lprc;
    call.text = (ULONG_PTR)text;
    call.style = (ULONG_PTR)style;

    qemu_syscall(&call.super);
}

#else

void qemu_DrawStatusTextA(struct qemu_syscall *call)
{
    struct qemu_DrawStatusTextA *c = (struct qemu_DrawStatusTextA *)call;
    WINE_FIXME("Unverified!\n");
    p_DrawStatusTextA(QEMU_G2H(c->hdc), QEMU_G2H(c->lprc), QEMU_G2H(c->text), c->style);
}

#endif

struct qemu_CreateStatusWindowA
{
    struct qemu_syscall super;
    uint64_t style;
    uint64_t text;
    uint64_t parent;
    uint64_t wid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI CreateStatusWindowA (LONG style, LPCSTR text, HWND parent, UINT wid)
{
    struct qemu_CreateStatusWindowA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESTATUSWINDOWA);
    call.style = (ULONG_PTR)style;
    call.text = (ULONG_PTR)text;
    call.parent = (ULONG_PTR)parent;
    call.wid = (ULONG_PTR)wid;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateStatusWindowA(struct qemu_syscall *call)
{
    struct qemu_CreateStatusWindowA *c = (struct qemu_CreateStatusWindowA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)p_CreateStatusWindowA(c->style, QEMU_G2H(c->text), QEMU_G2H(c->parent), c->wid);
}

#endif

struct qemu_CreateStatusWindowW
{
    struct qemu_syscall super;
    uint64_t style;
    uint64_t text;
    uint64_t parent;
    uint64_t wid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI CreateStatusWindowW (LONG style, LPCWSTR text, HWND parent, UINT wid)
{
    struct qemu_CreateStatusWindowW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESTATUSWINDOWW);
    call.style = (ULONG_PTR)style;
    call.text = (ULONG_PTR)text;
    call.parent = (ULONG_PTR)parent;
    call.wid = (ULONG_PTR)wid;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateStatusWindowW(struct qemu_syscall *call)
{
    struct qemu_CreateStatusWindowW *c = (struct qemu_CreateStatusWindowW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)p_CreateStatusWindowW(c->style, QEMU_G2H(c->text), QEMU_G2H(c->parent), c->wid);
}

#endif

struct qemu_CreateUpDownControl
{
    struct qemu_syscall super;
    uint64_t style;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
    uint64_t parent;
    uint64_t id;
    uint64_t inst;
    uint64_t buddy;
    uint64_t maxVal;
    uint64_t minVal;
    uint64_t curVal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI CreateUpDownControl (DWORD style, INT x, INT y, INT cx, INT cy, HWND parent, INT id, HINSTANCE inst, HWND buddy, INT maxVal, INT minVal, INT curVal)
{
    struct qemu_CreateUpDownControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEUPDOWNCONTROL);
    call.style = (ULONG_PTR)style;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.cx = (ULONG_PTR)cx;
    call.cy = (ULONG_PTR)cy;
    call.parent = (ULONG_PTR)parent;
    call.id = (ULONG_PTR)id;
    call.inst = (ULONG_PTR)inst;
    call.buddy = (ULONG_PTR)buddy;
    call.maxVal = (ULONG_PTR)maxVal;
    call.minVal = (ULONG_PTR)minVal;
    call.curVal = (ULONG_PTR)curVal;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateUpDownControl(struct qemu_syscall *call)
{
    struct qemu_CreateUpDownControl *c = (struct qemu_CreateUpDownControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)p_CreateUpDownControl(c->style, c->x, c->y, c->cx, c->cy, QEMU_G2H(c->parent), c->id, QEMU_G2H(c->inst), QEMU_G2H(c->buddy), c->maxVal, c->minVal, c->curVal);
}

#endif

struct qemu_InitCommonControls
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI InitCommonControls (void)
{
    struct qemu_InitCommonControls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITCOMMONCONTROLS);

    qemu_syscall(&call.super);
}

#else

void qemu_InitCommonControls(struct qemu_syscall *call)
{
    struct qemu_InitCommonControls *c = (struct qemu_InitCommonControls *)call;
    WINE_TRACE("\n");
    p_InitCommonControls();
}

#endif

struct qemu_InitCommonControlsEx
{
    struct qemu_syscall super;
    uint64_t lpInitCtrls;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitCommonControlsEx (const INITCOMMONCONTROLSEX *lpInitCtrls)
{
    struct qemu_InitCommonControlsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITCOMMONCONTROLSEX);
    call.lpInitCtrls = (ULONG_PTR)lpInitCtrls;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitCommonControlsEx(struct qemu_syscall *call)
{
    struct qemu_InitCommonControlsEx *c = (struct qemu_InitCommonControlsEx *)call;
    WINE_TRACE("\n");
    c->super.iret = p_InitCommonControlsEx(QEMU_G2H(c->lpInitCtrls));
}

#endif

struct qemu_CreateToolbarEx
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t style;
    uint64_t wID;
    uint64_t nBitmaps;
    uint64_t hBMInst;
    uint64_t wBMID;
    uint64_t lpButtons;
    uint64_t iNumButtons;
    uint64_t dxButton;
    uint64_t dyButton;
    uint64_t dxBitmap;
    uint64_t dyBitmap;
    uint64_t uStructSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI CreateToolbarEx (HWND hwnd, DWORD style, UINT wID, INT nBitmaps, HINSTANCE hBMInst, UINT_PTR wBMID, LPCTBBUTTON lpButtons, INT iNumButtons, INT dxButton, INT dyButton, INT dxBitmap, INT dyBitmap, UINT uStructSize)
{
    struct qemu_CreateToolbarEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETOOLBAREX);
    call.hwnd = (ULONG_PTR)hwnd;
    call.style = (ULONG_PTR)style;
    call.wID = (ULONG_PTR)wID;
    call.nBitmaps = (ULONG_PTR)nBitmaps;
    call.hBMInst = (ULONG_PTR)hBMInst;
    call.wBMID = (ULONG_PTR)wBMID;
    call.lpButtons = (ULONG_PTR)lpButtons;
    call.iNumButtons = (ULONG_PTR)iNumButtons;
    call.dxButton = (ULONG_PTR)dxButton;
    call.dyButton = (ULONG_PTR)dyButton;
    call.dxBitmap = (ULONG_PTR)dxBitmap;
    call.dyBitmap = (ULONG_PTR)dyBitmap;
    call.uStructSize = (ULONG_PTR)uStructSize;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateToolbarEx(struct qemu_syscall *call)
{
    struct qemu_CreateToolbarEx *c = (struct qemu_CreateToolbarEx *)call;
    TBBUTTON *buttons;
    struct qemu_TBBUTTON *buttons32;
    unsigned int count, i;
    WINE_TRACE("\n");

    count = c->iNumButtons;
#if GUEST_BIT == HOST_BIT
    buttons = QEMU_G2H(c->lpButtons);
#else
    buttons32 = QEMU_G2H(c->lpButtons);
    if (buttons32)
    {
        if (c->uStructSize != sizeof(*buttons32))
            WINE_FIXME("Handle custom struct size %lu.\n", c->uStructSize);

        buttons = HeapAlloc(GetProcessHeap(), 0, count * sizeof(*buttons));
        for (i = 0; i < count; i++)
            TBBUTTON_g2h(&buttons[i], &buttons32[i]);
    }
    else
    {
        buttons = NULL;
    }
#endif

    c->super.iret = (ULONG_PTR)p_CreateToolbarEx(QEMU_G2H(c->hwnd), c->style, c->wID, c->nBitmaps, QEMU_G2H(c->hBMInst),
            c->wBMID, buttons, count, c->dxButton, c->dyButton, c->dxBitmap, c->dyBitmap, sizeof(*buttons));

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, buttons);
#endif

}

#endif

struct qemu_CreateMappedBitmap
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t idBitmap;
    uint64_t wFlags;
    uint64_t lpColorMap;
    uint64_t iNumMaps;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HBITMAP WINAPI CreateMappedBitmap (HINSTANCE hInstance, INT_PTR idBitmap, UINT wFlags, LPCOLORMAP lpColorMap, INT iNumMaps)
{
    struct qemu_CreateMappedBitmap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMAPPEDBITMAP);
    call.hInstance = (ULONG_PTR)hInstance;
    call.idBitmap = (ULONG_PTR)idBitmap;
    call.wFlags = (ULONG_PTR)wFlags;
    call.lpColorMap = (ULONG_PTR)lpColorMap;
    call.iNumMaps = (ULONG_PTR)iNumMaps;

    qemu_syscall(&call.super);

    return (HBITMAP)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateMappedBitmap(struct qemu_syscall *call)
{
    struct qemu_CreateMappedBitmap *c = (struct qemu_CreateMappedBitmap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)p_CreateMappedBitmap(QEMU_G2H(c->hInstance), c->idBitmap, c->wFlags, QEMU_G2H(c->lpColorMap), c->iNumMaps);
}

#endif

struct qemu_CreateToolbar
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t style;
    uint64_t wID;
    uint64_t nBitmaps;
    uint64_t hBMInst;
    uint64_t wBMID;
    uint64_t lpButtons;
    uint64_t iNumButtons;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HWND WINAPI CreateToolbar (HWND hwnd, DWORD style, UINT wID, INT nBitmaps, HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons,INT iNumButtons)
{
    struct qemu_CreateToolbar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETOOLBAR);
    call.hwnd = (ULONG_PTR)hwnd;
    call.style = (ULONG_PTR)style;
    call.wID = (ULONG_PTR)wID;
    call.nBitmaps = (ULONG_PTR)nBitmaps;
    call.hBMInst = (ULONG_PTR)hBMInst;
    call.wBMID = (ULONG_PTR)wBMID;
    call.lpButtons = (ULONG_PTR)lpButtons;
    call.iNumButtons = (ULONG_PTR)iNumButtons;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateToolbar(struct qemu_syscall *call)
{
    struct qemu_CreateToolbar *c = (struct qemu_CreateToolbar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)p_CreateToolbar(QEMU_G2H(c->hwnd), c->style, c->wID, c->nBitmaps, QEMU_G2H(c->hBMInst), c->wBMID, QEMU_G2H(c->lpButtons), c->iNumButtons);
}

#endif

struct qemu_DllGetVersion
{
    struct qemu_syscall super;
    uint64_t pdvi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetVersion (void *pdvi)
{
    struct qemu_DllGetVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLGETVERSION);
    call.pdvi = (ULONG_PTR)pdvi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllGetVersion(struct qemu_syscall *call)
{
    struct qemu_DllGetVersion *c = (struct qemu_DllGetVersion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DllGetVersion(QEMU_G2H(c->pdvi));
}

#endif

struct qemu_DllInstall
{
    struct qemu_syscall super;
    uint64_t bInstall;
    uint64_t cmdline;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllInstall(BOOL bInstall, LPCWSTR cmdline)
{
    struct qemu_DllInstall call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLINSTALL);
    call.bInstall = (ULONG_PTR)bInstall;
    call.cmdline = (ULONG_PTR)cmdline;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllInstall(struct qemu_syscall *call)
{
    struct qemu_DllInstall *c = (struct qemu_DllInstall *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = E_FAIL;
}

#endif

struct qemu__TrackMouseEvent
{
    struct qemu_syscall super;
    uint64_t ptme;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI _TrackMouseEvent (TRACKMOUSEEVENT *ptme)
{
    struct qemu__TrackMouseEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TRACKMOUSEEVENT);
    call.ptme = (ULONG_PTR)ptme;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__TrackMouseEvent(struct qemu_syscall *call)
{
    struct qemu__TrackMouseEvent *c = (struct qemu__TrackMouseEvent *)call;
    TRACKMOUSEEVENT stack, *track = &stack;
    struct qemu_TRACKMOUSEEVENT *track32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    track = QEMU_G2H(c->ptme);
#else
    track32 = QEMU_G2H(c->ptme);
    if (!track32)
        track = NULL;
    else if(track32->cbSize == sizeof(*track32))
        TRACKMOUSEEVENT_g2h(track, QEMU_G2H(c->ptme));
    else
        track->cbSize = 0;
#endif

    c->super.iret = p__TrackMouseEvent(track);

#if GUEST_BIT != HOST_BIT
    if (track32 && track32->cbSize == sizeof(*track32))
        TRACKMOUSEEVENT_h2g(track32, track);
#endif
}

#endif

struct qemu_GetMUILanguage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI GetMUILanguage (VOID)
{
    struct qemu_GetMUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMUILANGUAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMUILanguage(struct qemu_syscall *call)
{
    struct qemu_GetMUILanguage *c = (struct qemu_GetMUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_GetMUILanguage();
}

#endif

struct qemu_InitMUILanguage
{
    struct qemu_syscall super;
    uint64_t uiLang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI InitMUILanguage (LANGID uiLang)
{
    struct qemu_InitMUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITMUILANGUAGE);
    call.uiLang = (ULONG_PTR)uiLang;

    qemu_syscall(&call.super);
}

#else

void qemu_InitMUILanguage(struct qemu_syscall *call)
{
    struct qemu_InitMUILanguage *c = (struct qemu_InitMUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    p_InitMUILanguage(c->uiLang);
}

#endif

struct qemu_SetWindowSubclass
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pfnSubclass;
    uint64_t uIDSubclass;
    uint64_t dwRef;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetWindowSubclass (HWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uIDSubclass, DWORD_PTR dwRef)
{
    struct qemu_SetWindowSubclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSUBCLASS);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pfnSubclass = (ULONG_PTR)pfnSubclass;
    call.uIDSubclass = (ULONG_PTR)uIDSubclass;
    call.dwRef = (ULONG_PTR)dwRef;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowSubclass(struct qemu_syscall *call)
{
    struct qemu_SetWindowSubclass *c = (struct qemu_SetWindowSubclass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_SetWindowSubclass(QEMU_G2H(c->hWnd), QEMU_G2H(c->pfnSubclass), c->uIDSubclass, c->dwRef);
}

#endif

struct qemu_GetWindowSubclass
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pfnSubclass;
    uint64_t uID;
    uint64_t pdwRef;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetWindowSubclass (HWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uID, DWORD_PTR *pdwRef)
{
    struct qemu_GetWindowSubclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWSUBCLASS);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pfnSubclass = (ULONG_PTR)pfnSubclass;
    call.uID = (ULONG_PTR)uID;
    call.pdwRef = (ULONG_PTR)pdwRef;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowSubclass(struct qemu_syscall *call)
{
    struct qemu_GetWindowSubclass *c = (struct qemu_GetWindowSubclass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_GetWindowSubclass(QEMU_G2H(c->hWnd), QEMU_G2H(c->pfnSubclass), c->uID, QEMU_G2H(c->pdwRef));
}

#endif

struct qemu_RemoveWindowSubclass
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pfnSubclass;
    uint64_t uID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RemoveWindowSubclass(HWND hWnd, SUBCLASSPROC pfnSubclass, UINT_PTR uID)
{
    struct qemu_RemoveWindowSubclass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEWINDOWSUBCLASS);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pfnSubclass = (ULONG_PTR)pfnSubclass;
    call.uID = (ULONG_PTR)uID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RemoveWindowSubclass(struct qemu_syscall *call)
{
    struct qemu_RemoveWindowSubclass *c = (struct qemu_RemoveWindowSubclass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_RemoveWindowSubclass(QEMU_G2H(c->hWnd), QEMU_G2H(c->pfnSubclass), c->uID);
}

#endif

struct qemu_DefSubclassProc
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI DefSubclassProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefSubclassProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFSUBCLASSPROC);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefSubclassProc(struct qemu_syscall *call)
{
    struct qemu_DefSubclassProc *c = (struct qemu_DefSubclassProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DefSubclassProc(QEMU_G2H(c->hWnd), c->uMsg, c->wParam, c->lParam);
}

#endif

struct qemu_MirrorIcon
{
    struct qemu_syscall super;
    uint64_t phicon1;
    uint64_t phicon2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MirrorIcon(HICON *phicon1, HICON *phicon2)
{
    struct qemu_MirrorIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIRRORICON);
    call.phicon1 = (ULONG_PTR)phicon1;
    call.phicon2 = (ULONG_PTR)phicon2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add MirrorIcon to Wine headers? */
extern BOOL WINAPI MirrorIcon(HICON *phicon1, HICON *phicon2);
void qemu_MirrorIcon(struct qemu_syscall *call)
{
    struct qemu_MirrorIcon *c = (struct qemu_MirrorIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_MirrorIcon(QEMU_G2H(c->phicon1), QEMU_G2H(c->phicon2));
}

#endif

struct qemu_SetPathWordBreakProc
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t bSet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI SetPathWordBreakProc(HWND hwnd, BOOL bSet)
{
    struct qemu_SetPathWordBreakProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPATHWORDBREAKPROC);
    call.hwnd = (ULONG_PTR)hwnd;
    call.bSet = (ULONG_PTR)bSet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetPathWordBreakProc to Wine headers? */
extern LRESULT WINAPI SetPathWordBreakProc(HWND hwnd, BOOL bSet);
void qemu_SetPathWordBreakProc(struct qemu_syscall *call)
{
    struct qemu_SetPathWordBreakProc *c = (struct qemu_SetPathWordBreakProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_SetPathWordBreakProc(QEMU_G2H(c->hwnd), c->bSet);
}

#endif

struct qemu_DrawShadowText
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t text;
    uint64_t length;
    uint64_t rect;
    uint64_t flags;
    uint64_t crText;
    uint64_t crShadow;
    uint64_t offset_x;
    uint64_t offset_y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI DrawShadowText(HDC hdc, LPCWSTR text, UINT length, RECT *rect, DWORD flags, COLORREF crText, COLORREF crShadow, int offset_x, int offset_y)
{
    struct qemu_DrawShadowText call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWSHADOWTEXT);
    call.hdc = (ULONG_PTR)hdc;
    call.text = (ULONG_PTR)text;
    call.length = (ULONG_PTR)length;
    call.rect = (ULONG_PTR)rect;
    call.flags = (ULONG_PTR)flags;
    call.crText = (ULONG_PTR)crText;
    call.crShadow = (ULONG_PTR)crShadow;
    call.offset_x = (ULONG_PTR)offset_x;
    call.offset_y = (ULONG_PTR)offset_y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawShadowText(struct qemu_syscall *call)
{
    struct qemu_DrawShadowText *c = (struct qemu_DrawShadowText *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DrawShadowText(QEMU_G2H(c->hdc), QEMU_G2H(c->text), c->length, QEMU_G2H(c->rect), c->flags, c->crText, c->crShadow, c->offset_x, c->offset_y);
}

#endif

struct qemu_LoadIconWithScaleDown
{
    struct qemu_syscall super;
    uint64_t hinst;
    uint64_t name;
    uint64_t cx;
    uint64_t cy;
    uint64_t icon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI LoadIconWithScaleDown(HINSTANCE hinst, const WCHAR *name, int cx, int cy, HICON *icon)
{
    struct qemu_LoadIconWithScaleDown call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADICONWITHSCALEDOWN);
    call.hinst = (ULONG_PTR)hinst;
    call.name = (ULONG_PTR)name;
    call.cx = (ULONG_PTR)cx;
    call.cy = (ULONG_PTR)cy;
    call.icon = (ULONG_PTR)icon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LoadIconWithScaleDown(struct qemu_syscall *call)
{
    struct qemu_LoadIconWithScaleDown *c = (struct qemu_LoadIconWithScaleDown *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_LoadIconWithScaleDown(QEMU_G2H(c->hinst), QEMU_G2H(c->name), c->cx, c->cy, QEMU_G2H(c->icon));
}

#endif

struct qemu_LoadIconMetric
{
    struct qemu_syscall super;
    uint64_t hinst;
    uint64_t name;
    uint64_t size;
    uint64_t icon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI LoadIconMetric(HINSTANCE hinst, const WCHAR *name, int size, HICON *icon)
{
    struct qemu_LoadIconMetric call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADICONMETRIC);
    call.hinst = (ULONG_PTR)hinst;
    call.name = (ULONG_PTR)name;
    call.size = (ULONG_PTR)size;
    call.icon = (ULONG_PTR)icon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LoadIconMetric(struct qemu_syscall *call)
{
    struct qemu_LoadIconMetric *c = (struct qemu_LoadIconMetric *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_LoadIconMetric(QEMU_G2H(c->hinst), QEMU_G2H(c->name), c->size, QEMU_G2H(c->icon));
}

#endif

