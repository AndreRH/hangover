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


struct qemu_SwitchToThisWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t alt_tab;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI SwitchToThisWindow(HWND hwnd, BOOL alt_tab)
{
    struct qemu_SwitchToThisWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SWITCHTOTHISWINDOW);
    call.hwnd = (uint64_t)hwnd;
    call.alt_tab = (uint64_t)alt_tab;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_SwitchToThisWindow(struct qemu_syscall *call)
{
    struct qemu_SwitchToThisWindow *c = (struct qemu_SwitchToThisWindow *)call;
    WINE_FIXME("Unverified!\n");
    SwitchToThisWindow(QEMU_G2H(c->hwnd), c->alt_tab);
}

#endif

struct qemu_GetWindowRect
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetWindowRect(HWND hwnd, LPRECT rect)
{
    struct qemu_GetWindowRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWRECT);
    call.hwnd = (uint64_t)hwnd;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowRect(struct qemu_syscall *call)
{
    struct qemu_GetWindowRect *c = (struct qemu_GetWindowRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWindowRect(QEMU_G2H(c->hwnd), QEMU_G2H(c->rect));
}

#endif

struct qemu_GetWindowRgn
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hrgn;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI int WINAPI GetWindowRgn (HWND hwnd, HRGN hrgn)
{
    struct qemu_GetWindowRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWRGN);
    call.hwnd = (uint64_t)hwnd;
    call.hrgn = (uint64_t)hrgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowRgn(struct qemu_syscall *call)
{
    struct qemu_GetWindowRgn *c = (struct qemu_GetWindowRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWindowRgn(QEMU_G2H(c->hwnd), QEMU_G2H(c->hrgn));
}

#endif

struct qemu_GetWindowRgnBox
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t prect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI int WINAPI GetWindowRgnBox(HWND hwnd, LPRECT prect)
{
    struct qemu_GetWindowRgnBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWRGNBOX);
    call.hwnd = (uint64_t)hwnd;
    call.prect = (uint64_t)prect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetWindowRgnBox to Wine headers? */
extern int WINAPI GetWindowRgnBox(HWND hwnd, LPRECT prect);
void qemu_GetWindowRgnBox(struct qemu_syscall *call)
{
    struct qemu_GetWindowRgnBox *c = (struct qemu_GetWindowRgnBox *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWindowRgnBox(QEMU_G2H(c->hwnd), QEMU_G2H(c->prect));
}

#endif

struct qemu_SetWindowRgn
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hrgn;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI int WINAPI SetWindowRgn(HWND hwnd, HRGN hrgn, BOOL bRedraw)
{
    struct qemu_SetWindowRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWRGN);
    call.hwnd = (uint64_t)hwnd;
    call.hrgn = (uint64_t)hrgn;
    call.bRedraw = (uint64_t)bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowRgn(struct qemu_syscall *call)
{
    struct qemu_SetWindowRgn *c = (struct qemu_SetWindowRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowRgn(QEMU_G2H(c->hwnd), QEMU_G2H(c->hrgn), c->bRedraw);
}

#endif

struct qemu_GetClientRect
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetClientRect(HWND hwnd, LPRECT rect)
{
    struct qemu_GetClientRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIENTRECT);
    call.hwnd = (uint64_t)hwnd;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClientRect(struct qemu_syscall *call)
{
    struct qemu_GetClientRect *c = (struct qemu_GetClientRect *)call;
    WINE_TRACE("\n");
    c->super.iret = GetClientRect(QEMU_G2H(c->hwnd), QEMU_G2H(c->rect));
}

#endif

struct qemu_MapWindowPoints
{
    struct qemu_syscall super;
    uint64_t hwndFrom;
    uint64_t hwndTo;
    uint64_t lppt;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MapWindowPoints(HWND hwndFrom, HWND hwndTo, LPPOINT lppt, UINT count)
{
    struct qemu_MapWindowPoints call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAPWINDOWPOINTS);
    call.hwndFrom = (uint64_t)hwndFrom;
    call.hwndTo = (uint64_t)hwndTo;
    call.lppt = (uint64_t)lppt;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MapWindowPoints(struct qemu_syscall *call)
{
    struct qemu_MapWindowPoints *c = (struct qemu_MapWindowPoints *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MapWindowPoints(QEMU_G2H(c->hwndFrom), QEMU_G2H(c->hwndTo), QEMU_G2H(c->lppt), c->count);
}

#endif

struct qemu_ClientToScreen
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lppnt;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ClientToScreen(HWND hwnd, LPPOINT lppnt)
{
    struct qemu_ClientToScreen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLIENTTOSCREEN);
    call.hwnd = (uint64_t)hwnd;
    call.lppnt = (uint64_t)lppnt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClientToScreen(struct qemu_syscall *call)
{
    struct qemu_ClientToScreen *c = (struct qemu_ClientToScreen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ClientToScreen(QEMU_G2H(c->hwnd), QEMU_G2H(c->lppnt));
}

#endif

struct qemu_ScreenToClient
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lppnt;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ScreenToClient(HWND hwnd, LPPOINT lppnt)
{
    struct qemu_ScreenToClient call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCREENTOCLIENT);
    call.hwnd = (uint64_t)hwnd;
    call.lppnt = (uint64_t)lppnt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScreenToClient(struct qemu_syscall *call)
{
    struct qemu_ScreenToClient *c = (struct qemu_ScreenToClient *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScreenToClient(QEMU_G2H(c->hwnd), QEMU_G2H(c->lppnt));
}

#endif

struct qemu_IsIconic
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsIconic(HWND hWnd)
{
    struct qemu_IsIconic call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISICONIC);
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsIconic(struct qemu_syscall *call)
{
    struct qemu_IsIconic *c = (struct qemu_IsIconic *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsIconic(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_IsZoomed
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsZoomed(HWND hWnd)
{
    struct qemu_IsZoomed call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISZOOMED);
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsZoomed(struct qemu_syscall *call)
{
    struct qemu_IsZoomed *c = (struct qemu_IsZoomed *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsZoomed(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_AllowSetForegroundWindow
{
    struct qemu_syscall super;
    uint64_t procid;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AllowSetForegroundWindow(DWORD procid)
{
    struct qemu_AllowSetForegroundWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOWSETFOREGROUNDWINDOW);
    call.procid = (uint64_t)procid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AllowSetForegroundWindow(struct qemu_syscall *call)
{
    struct qemu_AllowSetForegroundWindow *c = (struct qemu_AllowSetForegroundWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllowSetForegroundWindow(c->procid);
}

#endif

struct qemu_LockSetForegroundWindow
{
    struct qemu_syscall super;
    uint64_t lockcode;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI LockSetForegroundWindow(UINT lockcode)
{
    struct qemu_LockSetForegroundWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCKSETFOREGROUNDWINDOW);
    call.lockcode = (uint64_t)lockcode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LockSetForegroundWindow(struct qemu_syscall *call)
{
    struct qemu_LockSetForegroundWindow *c = (struct qemu_LockSetForegroundWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LockSetForegroundWindow(c->lockcode);
}

#endif

struct qemu_BringWindowToTop
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI BringWindowToTop(HWND hwnd)
{
    struct qemu_BringWindowToTop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BRINGWINDOWTOTOP);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BringWindowToTop(struct qemu_syscall *call)
{
    struct qemu_BringWindowToTop *c = (struct qemu_BringWindowToTop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BringWindowToTop(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_MoveWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
    uint64_t repaint;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI MoveWindow(HWND hwnd, INT x, INT y, INT cx, INT cy, BOOL repaint)
{
    struct qemu_MoveWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVEWINDOW);
    call.hwnd = (uint64_t)hwnd;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;
    call.repaint = (uint64_t)repaint;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveWindow(struct qemu_syscall *call)
{
    struct qemu_MoveWindow *c = (struct qemu_MoveWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MoveWindow(QEMU_G2H(c->hwnd), c->x, c->y, c->cx, c->cy, c->repaint);
}

#endif

struct qemu_ShowWindowAsync
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t cmd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShowWindowAsync(HWND hwnd, INT cmd)
{
    struct qemu_ShowWindowAsync call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWWINDOWASYNC);
    call.hwnd = (uint64_t)hwnd;
    call.cmd = (uint64_t)cmd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShowWindowAsync(struct qemu_syscall *call)
{
    struct qemu_ShowWindowAsync *c = (struct qemu_ShowWindowAsync *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ShowWindowAsync(QEMU_G2H(c->hwnd), c->cmd);
}

#endif

struct qemu_ShowWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t cmd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShowWindow(HWND hwnd, INT cmd)
{
    struct qemu_ShowWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWWINDOW);
    call.hwnd = (uint64_t)hwnd;
    call.cmd = (uint64_t)cmd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShowWindow(struct qemu_syscall *call)
{
    struct qemu_ShowWindow *c = (struct qemu_ShowWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = ShowWindow(QEMU_G2H(c->hwnd), c->cmd);
}

#endif

struct qemu_GetInternalWindowPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t rectWnd;
    uint64_t ptIcon;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetInternalWindowPos(HWND hwnd, LPRECT rectWnd, LPPOINT ptIcon)
{
    struct qemu_GetInternalWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETINTERNALWINDOWPOS);
    call.hwnd = (uint64_t)hwnd;
    call.rectWnd = (uint64_t)rectWnd;
    call.ptIcon = (uint64_t)ptIcon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetInternalWindowPos(struct qemu_syscall *call)
{
    struct qemu_GetInternalWindowPos *c = (struct qemu_GetInternalWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetInternalWindowPos(QEMU_G2H(c->hwnd), QEMU_G2H(c->rectWnd), QEMU_G2H(c->ptIcon));
}

#endif

struct qemu_GetWindowPlacement
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t wndpl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetWindowPlacement(HWND hwnd, WINDOWPLACEMENT *wndpl)
{
    struct qemu_GetWindowPlacement call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWPLACEMENT);
    call.hwnd = (uint64_t)hwnd;
    call.wndpl = (uint64_t)wndpl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowPlacement(struct qemu_syscall *call)
{
    struct qemu_GetWindowPlacement *c = (struct qemu_GetWindowPlacement *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowPlacement(QEMU_G2H(c->hwnd), QEMU_G2H(c->wndpl));
}

#endif

struct qemu_SetWindowPlacement
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t wpl;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetWindowPlacement(HWND hwnd, const WINDOWPLACEMENT *wpl)
{
    struct qemu_SetWindowPlacement call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWPLACEMENT);
    call.hwnd = (uint64_t)hwnd;
    call.wpl = (uint64_t)wpl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowPlacement(struct qemu_syscall *call)
{
    struct qemu_SetWindowPlacement *c = (struct qemu_SetWindowPlacement *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowPlacement(QEMU_G2H(c->hwnd), QEMU_G2H(c->wpl));
}

#endif

struct qemu_AnimateWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t dwTime;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AnimateWindow(HWND hwnd, DWORD dwTime, DWORD dwFlags)
{
    struct qemu_AnimateWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ANIMATEWINDOW);
    call.hwnd = (uint64_t)hwnd;
    call.dwTime = (uint64_t)dwTime;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AnimateWindow(struct qemu_syscall *call)
{
    struct qemu_AnimateWindow *c = (struct qemu_AnimateWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AnimateWindow(QEMU_G2H(c->hwnd), c->dwTime, c->dwFlags);
}

#endif

struct qemu_SetInternalWindowPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t showCmd;
    uint64_t rect;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI SetInternalWindowPos(HWND hwnd, UINT showCmd, LPRECT rect, LPPOINT pt)
{
    struct qemu_SetInternalWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETINTERNALWINDOWPOS);
    call.hwnd = (uint64_t)hwnd;
    call.showCmd = (uint64_t)showCmd;
    call.rect = (uint64_t)rect;
    call.pt = (uint64_t)pt;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_SetInternalWindowPos(struct qemu_syscall *call)
{
    struct qemu_SetInternalWindowPos *c = (struct qemu_SetInternalWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    SetInternalWindowPos(QEMU_G2H(c->hwnd), c->showCmd, QEMU_G2H(c->rect), QEMU_G2H(c->pt));
}

#endif

struct qemu_SetWindowPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hwndInsertAfter;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetWindowPos(HWND hwnd, HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy, UINT flags)
{
    struct qemu_SetWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWPOS);
    call.hwnd = (uint64_t)hwnd;
    call.hwndInsertAfter = (uint64_t)hwndInsertAfter;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowPos(struct qemu_syscall *call)
{
    struct qemu_SetWindowPos *c = (struct qemu_SetWindowPos *)call;
    WINE_TRACE("\n");
    c->super.iret = SetWindowPos(QEMU_G2H(c->hwnd), QEMU_G2H(c->hwndInsertAfter), c->x, c->y, c->cx, c->cy, c->flags);
}

#endif

struct qemu_BeginDeferWindowPos
{
    struct qemu_syscall super;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDWP WINAPI BeginDeferWindowPos(INT count)
{
    struct qemu_BeginDeferWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BEGINDEFERWINDOWPOS);
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return (HDWP)call.super.iret;
}

#else

void qemu_BeginDeferWindowPos(struct qemu_syscall *call)
{
    struct qemu_BeginDeferWindowPos *c = (struct qemu_BeginDeferWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)BeginDeferWindowPos(c->count);
}

#endif

struct qemu_DeferWindowPos
{
    struct qemu_syscall super;
    uint64_t hdwp;
    uint64_t hwnd;
    uint64_t hwndAfter;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDWP WINAPI DeferWindowPos(HDWP hdwp, HWND hwnd, HWND hwndAfter, INT x, INT y, INT cx, INT cy, UINT flags)
{
    struct qemu_DeferWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFERWINDOWPOS);
    call.hdwp = (uint64_t)hdwp;
    call.hwnd = (uint64_t)hwnd;
    call.hwndAfter = (uint64_t)hwndAfter;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HDWP)call.super.iret;
}

#else

void qemu_DeferWindowPos(struct qemu_syscall *call)
{
    struct qemu_DeferWindowPos *c = (struct qemu_DeferWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)DeferWindowPos(QEMU_G2H(c->hdwp), QEMU_G2H(c->hwnd), QEMU_G2H(c->hwndAfter), c->x, c->y, c->cx, c->cy, c->flags);
}

#endif

struct qemu_EndDeferWindowPos
{
    struct qemu_syscall super;
    uint64_t hdwp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EndDeferWindowPos(HDWP hdwp)
{
    struct qemu_EndDeferWindowPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDDEFERWINDOWPOS);
    call.hdwp = (uint64_t)hdwp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndDeferWindowPos(struct qemu_syscall *call)
{
    struct qemu_EndDeferWindowPos *c = (struct qemu_EndDeferWindowPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndDeferWindowPos(QEMU_G2H(c->hdwp));
}

#endif

struct qemu_ArrangeIconicWindows
{
    struct qemu_syscall super;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI ArrangeIconicWindows(HWND parent)
{
    struct qemu_ArrangeIconicWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ARRANGEICONICWINDOWS);
    call.parent = (uint64_t)parent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ArrangeIconicWindows(struct qemu_syscall *call)
{
    struct qemu_ArrangeIconicWindows *c = (struct qemu_ArrangeIconicWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ArrangeIconicWindows(QEMU_G2H(c->parent));
}

#endif

struct qemu_LogicalToPhysicalPoint
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t point;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI LogicalToPhysicalPoint(HWND hwnd, POINT *point)
{
    struct qemu_LogicalToPhysicalPoint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOGICALTOPHYSICALPOINT);
    call.hwnd = (uint64_t)hwnd;
    call.point = (uint64_t)point;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LogicalToPhysicalPoint to Wine headers? */
extern BOOL WINAPI LogicalToPhysicalPoint(HWND hwnd, POINT *point);
void qemu_LogicalToPhysicalPoint(struct qemu_syscall *call)
{
    struct qemu_LogicalToPhysicalPoint *c = (struct qemu_LogicalToPhysicalPoint *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LogicalToPhysicalPoint(QEMU_G2H(c->hwnd), QEMU_G2H(c->point));
}

#endif

struct qemu_PhysicalToLogicalPoint
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t point;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI PhysicalToLogicalPoint(HWND hwnd, POINT *point)
{
    struct qemu_PhysicalToLogicalPoint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PHYSICALTOLOGICALPOINT);
    call.hwnd = (uint64_t)hwnd;
    call.point = (uint64_t)point;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PhysicalToLogicalPoint to Wine headers? */
extern BOOL WINAPI PhysicalToLogicalPoint(HWND hwnd, POINT *point);
void qemu_PhysicalToLogicalPoint(struct qemu_syscall *call)
{
    struct qemu_PhysicalToLogicalPoint *c = (struct qemu_PhysicalToLogicalPoint *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PhysicalToLogicalPoint(QEMU_G2H(c->hwnd), QEMU_G2H(c->point));
}

#endif

