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


struct qemu_DefFrameProcA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hwndMDIClient;
    uint64_t message;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefFrameProcA(HWND hwnd, HWND hwndMDIClient, UINT message, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefFrameProcA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFFRAMEPROCA);
    call.hwnd = (uint64_t)hwnd;
    call.hwndMDIClient = (uint64_t)hwndMDIClient;
    call.message = (uint64_t)message;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefFrameProcA(struct qemu_syscall *call)
{
    struct qemu_DefFrameProcA *c = (struct qemu_DefFrameProcA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefFrameProcA(QEMU_G2H(c->hwnd), QEMU_G2H(c->hwndMDIClient), c->message, c->wParam, c->lParam);
}

#endif

struct qemu_DefFrameProcW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hwndMDIClient;
    uint64_t message;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefFrameProcW(HWND hwnd, HWND hwndMDIClient, UINT message, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefFrameProcW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFFRAMEPROCW);
    call.hwnd = (uint64_t)hwnd;
    call.hwndMDIClient = (uint64_t)hwndMDIClient;
    call.message = (uint64_t)message;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefFrameProcW(struct qemu_syscall *call)
{
    struct qemu_DefFrameProcW *c = (struct qemu_DefFrameProcW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefFrameProcW(QEMU_G2H(c->hwnd), QEMU_G2H(c->hwndMDIClient), c->message, c->wParam, c->lParam);
}

#endif

struct qemu_DefMDIChildProcA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t message;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefMDIChildProcA(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefMDIChildProcA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFMDICHILDPROCA);
    call.hwnd = (uint64_t)hwnd;
    call.message = (uint64_t)message;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefMDIChildProcA(struct qemu_syscall *call)
{
    struct qemu_DefMDIChildProcA *c = (struct qemu_DefMDIChildProcA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefMDIChildProcA(QEMU_G2H(c->hwnd), c->message, c->wParam, c->lParam);
}

#endif

struct qemu_DefMDIChildProcW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t message;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefMDIChildProcW(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefMDIChildProcW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFMDICHILDPROCW);
    call.hwnd = (uint64_t)hwnd;
    call.message = (uint64_t)message;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefMDIChildProcW(struct qemu_syscall *call)
{
    struct qemu_DefMDIChildProcW *c = (struct qemu_DefMDIChildProcW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefMDIChildProcW(QEMU_G2H(c->hwnd), c->message, c->wParam, c->lParam);
}

#endif

struct qemu_CreateMDIWindowA
{
    struct qemu_syscall super;
    uint64_t lpClassName;
    uint64_t lpWindowName;
    uint64_t dwStyle;
    uint64_t X;
    uint64_t Y;
    uint64_t nWidth;
    uint64_t nHeight;
    uint64_t hWndParent;
    uint64_t hInstance;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateMDIWindowA(LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, INT X, INT Y, INT nWidth, INT nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
    struct qemu_CreateMDIWindowA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMDIWINDOWA);
    call.lpClassName = (uint64_t)lpClassName;
    call.lpWindowName = (uint64_t)lpWindowName;
    call.dwStyle = (uint64_t)dwStyle;
    call.X = (uint64_t)X;
    call.Y = (uint64_t)Y;
    call.nWidth = (uint64_t)nWidth;
    call.nHeight = (uint64_t)nHeight;
    call.hWndParent = (uint64_t)hWndParent;
    call.hInstance = (uint64_t)hInstance;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateMDIWindowA(struct qemu_syscall *call)
{
    struct qemu_CreateMDIWindowA *c = (struct qemu_CreateMDIWindowA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMDIWindowA(QEMU_G2H(c->lpClassName), QEMU_G2H(c->lpWindowName), c->dwStyle, c->X, c->Y, c->nWidth, c->nHeight, QEMU_G2H(c->hWndParent), QEMU_G2H(c->hInstance), c->lParam);
}

#endif

struct qemu_CreateMDIWindowW
{
    struct qemu_syscall super;
    uint64_t lpClassName;
    uint64_t lpWindowName;
    uint64_t dwStyle;
    uint64_t X;
    uint64_t Y;
    uint64_t nWidth;
    uint64_t nHeight;
    uint64_t hWndParent;
    uint64_t hInstance;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateMDIWindowW(LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, INT X, INT Y, INT nWidth, INT nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
    struct qemu_CreateMDIWindowW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMDIWINDOWW);
    call.lpClassName = (uint64_t)lpClassName;
    call.lpWindowName = (uint64_t)lpWindowName;
    call.dwStyle = (uint64_t)dwStyle;
    call.X = (uint64_t)X;
    call.Y = (uint64_t)Y;
    call.nWidth = (uint64_t)nWidth;
    call.nHeight = (uint64_t)nHeight;
    call.hWndParent = (uint64_t)hWndParent;
    call.hInstance = (uint64_t)hInstance;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateMDIWindowW(struct qemu_syscall *call)
{
    struct qemu_CreateMDIWindowW *c = (struct qemu_CreateMDIWindowW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateMDIWindowW(QEMU_G2H(c->lpClassName), QEMU_G2H(c->lpWindowName), c->dwStyle, c->X, c->Y, c->nWidth, c->nHeight, QEMU_G2H(c->hWndParent), QEMU_G2H(c->hInstance), c->lParam);
}

#endif

struct qemu_TranslateMDISysAccel
{
    struct qemu_syscall super;
    uint64_t hwndClient;
    uint64_t msg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI TranslateMDISysAccel(HWND hwndClient, LPMSG msg)
{
    struct qemu_TranslateMDISysAccel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSLATEMDISYSACCEL);
    call.hwndClient = (uint64_t)hwndClient;
    call.msg = (uint64_t)msg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TranslateMDISysAccel(struct qemu_syscall *call)
{
    struct qemu_TranslateMDISysAccel *c = (struct qemu_TranslateMDISysAccel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TranslateMDISysAccel(QEMU_G2H(c->hwndClient), QEMU_G2H(c->msg));
}

#endif

struct qemu_CalcChildScroll
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t scroll;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI CalcChildScroll(HWND hwnd, INT scroll)
{
    struct qemu_CalcChildScroll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALCCHILDSCROLL);
    call.hwnd = (uint64_t)hwnd;
    call.scroll = (uint64_t)scroll;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_CalcChildScroll(struct qemu_syscall *call)
{
    struct qemu_CalcChildScroll *c = (struct qemu_CalcChildScroll *)call;
    WINE_FIXME("Unverified!\n");
    CalcChildScroll(QEMU_G2H(c->hwnd), c->scroll);
}

#endif

struct qemu_ScrollChildren
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI ScrollChildren(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_ScrollChildren call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCROLLCHILDREN);
    call.hWnd = (uint64_t)hWnd;
    call.uMsg = (uint64_t)uMsg;
    call.wParam = (uint64_t)wParam;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_ScrollChildren(struct qemu_syscall *call)
{
    struct qemu_ScrollChildren *c = (struct qemu_ScrollChildren *)call;
    WINE_FIXME("Unverified!\n");
    ScrollChildren(QEMU_G2H(c->hWnd), c->uMsg, c->wParam, c->lParam);
}

#endif

struct qemu_CascadeWindows
{
    struct qemu_syscall super;
    uint64_t hwndParent;
    uint64_t wFlags;
    uint64_t lpRect;
    uint64_t cKids;
    uint64_t lpKids;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI CascadeWindows (HWND hwndParent, UINT wFlags, const RECT *lpRect, UINT cKids, const HWND *lpKids)
{
    struct qemu_CascadeWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CASCADEWINDOWS);
    call.hwndParent = (uint64_t)hwndParent;
    call.wFlags = (uint64_t)wFlags;
    call.lpRect = (uint64_t)lpRect;
    call.cKids = (uint64_t)cKids;
    call.lpKids = (uint64_t)lpKids;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CascadeWindows(struct qemu_syscall *call)
{
    struct qemu_CascadeWindows *c = (struct qemu_CascadeWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CascadeWindows(QEMU_G2H(c->hwndParent), c->wFlags, QEMU_G2H(c->lpRect), c->cKids, QEMU_G2H(c->lpKids));
}

#endif

struct qemu_CascadeChildWindows
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI CascadeChildWindows(HWND parent, UINT flags)
{
    struct qemu_CascadeChildWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CASCADECHILDWINDOWS);
    call.parent = (uint64_t)parent;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CascadeChildWindows to Wine headers? */
extern WORD WINAPI CascadeChildWindows(HWND parent, UINT flags);
void qemu_CascadeChildWindows(struct qemu_syscall *call)
{
    struct qemu_CascadeChildWindows *c = (struct qemu_CascadeChildWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CascadeChildWindows(QEMU_G2H(c->parent), c->flags);
}

#endif

struct qemu_TileWindows
{
    struct qemu_syscall super;
    uint64_t hwndParent;
    uint64_t wFlags;
    uint64_t lpRect;
    uint64_t cKids;
    uint64_t lpKids;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI TileWindows (HWND hwndParent, UINT wFlags, const RECT *lpRect, UINT cKids, const HWND *lpKids)
{
    struct qemu_TileWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TILEWINDOWS);
    call.hwndParent = (uint64_t)hwndParent;
    call.wFlags = (uint64_t)wFlags;
    call.lpRect = (uint64_t)lpRect;
    call.cKids = (uint64_t)cKids;
    call.lpKids = (uint64_t)lpKids;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TileWindows(struct qemu_syscall *call)
{
    struct qemu_TileWindows *c = (struct qemu_TileWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TileWindows(QEMU_G2H(c->hwndParent), c->wFlags, QEMU_G2H(c->lpRect), c->cKids, QEMU_G2H(c->lpKids));
}

#endif

struct qemu_TileChildWindows
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI TileChildWindows(HWND parent, UINT flags)
{
    struct qemu_TileChildWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TILECHILDWINDOWS);
    call.parent = (uint64_t)parent;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add TileChildWindows to Wine headers? */
extern WORD WINAPI TileChildWindows(HWND parent, UINT flags);
void qemu_TileChildWindows(struct qemu_syscall *call)
{
    struct qemu_TileChildWindows *c = (struct qemu_TileChildWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TileChildWindows(QEMU_G2H(c->parent), c->flags);
}

#endif

