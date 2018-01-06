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
#include <assert.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif

struct qemu_CreateWindowExA
{
    struct qemu_syscall super;
    uint64_t exStyle;
    uint64_t className;
    uint64_t windowName;
    uint64_t style;
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;
    uint64_t parent;
    uint64_t menu;
    uint64_t instance;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateWindowExA(DWORD exStyle, LPCSTR className, LPCSTR windowName, DWORD style, INT x, INT y, INT width, INT height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID data)
{
    struct qemu_CreateWindowExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWINDOWEXA);
    call.exStyle = exStyle;
    call.className = (ULONG_PTR)className;
    call.windowName = (ULONG_PTR)windowName;
    call.style = style;
    call.x = x;
    call.y = y;
    call.width = width;
    call.height = height;
    call.parent = (ULONG_PTR)parent;
    call.menu = (ULONG_PTR)menu;
    call.instance = (ULONG_PTR)instance;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWindowExA(struct qemu_syscall *call)
{
    struct qemu_CreateWindowExA *c = (struct qemu_CreateWindowExA *)call;
    HINSTANCE inst;
    WINE_TRACE("\n");

    /* Do not modify hInstance here, it breaks the tests. Let's see if it is actually necessary. */
    c->super.iret = (ULONG_PTR)CreateWindowExA(c->exStyle, QEMU_G2H(c->className), QEMU_G2H(c->windowName), c->style, c->x, c->y, c->width, c->height, QEMU_G2H(c->parent), QEMU_G2H(c->menu), (HINSTANCE)c->instance, QEMU_G2H(c->data));
}

#endif

struct qemu_CreateWindowExW
{
    struct qemu_syscall super;
    uint64_t exStyle;
    uint64_t className;
    uint64_t windowName;
    uint64_t style;
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;
    uint64_t parent;
    uint64_t menu;
    uint64_t instance;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI CreateWindowExW(DWORD exStyle, LPCWSTR className, LPCWSTR windowName, DWORD style, INT x, INT y, INT width, INT height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID data)
{
    struct qemu_CreateWindowExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWINDOWEXW);
    call.exStyle = exStyle;
    call.className = (ULONG_PTR)className;
    call.windowName = (ULONG_PTR)windowName;
    call.style = (ULONG_PTR)style;
    call.x = x;
    call.y = y;
    call.width = width;
    call.height = height;
    call.parent = (ULONG_PTR)parent;
    call.menu = (ULONG_PTR)menu;
    call.instance = (ULONG_PTR)instance;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWindowExW(struct qemu_syscall *call)
{
    struct qemu_CreateWindowExW *c = (struct qemu_CreateWindowExW *)call;
    HINSTANCE inst;
    WINE_TRACE("\n");

    /* Do not modify hInstance here, it breaks the tests. Let's see if it is actually necessary. */
    c->super.iret = (ULONG_PTR)CreateWindowExW(c->exStyle, QEMU_G2H(c->className), QEMU_G2H(c->windowName), c->style, c->x, c->y, c->width, c->height, QEMU_G2H(c->parent), QEMU_G2H(c->menu), (HINSTANCE)c->instance, QEMU_G2H(c->data));
}

#endif

struct qemu_DestroyWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DestroyWindow(HWND hwnd)
{
    struct qemu_DestroyWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESTROYWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyWindow(struct qemu_syscall *call)
{
    struct qemu_DestroyWindow *c = (struct qemu_DestroyWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = DestroyWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_CloseWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CloseWindow(HWND hwnd)
{
    struct qemu_CloseWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseWindow(struct qemu_syscall *call)
{
    struct qemu_CloseWindow *c = (struct qemu_CloseWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_OpenIcon
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OpenIcon(HWND hwnd)
{
    struct qemu_OpenIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENICON);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OpenIcon(struct qemu_syscall *call)
{
    struct qemu_OpenIcon *c = (struct qemu_OpenIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OpenIcon(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_FindWindowExW
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t child;
    uint64_t className;
    uint64_t title;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI FindWindowExW(HWND parent, HWND child, LPCWSTR className, LPCWSTR title)
{
    struct qemu_FindWindowExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDWINDOWEXW);
    call.parent = (ULONG_PTR)parent;
    call.child = (ULONG_PTR)child;
    call.className = (ULONG_PTR)className;
    call.title = (ULONG_PTR)title;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindWindowExW(struct qemu_syscall *call)
{
    struct qemu_FindWindowExW *c = (struct qemu_FindWindowExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindWindowExW(QEMU_G2H(c->parent), QEMU_G2H(c->child), QEMU_G2H(c->className), QEMU_G2H(c->title));
}

#endif

struct qemu_FindWindowA
{
    struct qemu_syscall super;
    uint64_t className;
    uint64_t title;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI FindWindowA(LPCSTR className, LPCSTR title)
{
    struct qemu_FindWindowA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDWINDOWA);
    call.className = (ULONG_PTR)className;
    call.title = (ULONG_PTR)title;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindWindowA(struct qemu_syscall *call)
{
    struct qemu_FindWindowA *c = (struct qemu_FindWindowA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)FindWindowA(QEMU_G2H(c->className), QEMU_G2H(c->title));
}

#endif

struct qemu_FindWindowExA
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t child;
    uint64_t className;
    uint64_t title;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI FindWindowExA(HWND parent, HWND child, LPCSTR className, LPCSTR title)
{
    struct qemu_FindWindowExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDWINDOWEXA);
    call.parent = (ULONG_PTR)parent;
    call.child = (ULONG_PTR)child;
    call.className = (ULONG_PTR)className;
    call.title = (ULONG_PTR)title;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindWindowExA(struct qemu_syscall *call)
{
    struct qemu_FindWindowExA *c = (struct qemu_FindWindowExA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)FindWindowExA(QEMU_G2H(c->parent), QEMU_G2H(c->child), QEMU_G2H(c->className), QEMU_G2H(c->title));
}

#endif

struct qemu_FindWindowW
{
    struct qemu_syscall super;
    uint64_t className;
    uint64_t title;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI FindWindowW(LPCWSTR className, LPCWSTR title)
{
    struct qemu_FindWindowW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDWINDOWW);
    call.className = (ULONG_PTR)className;
    call.title = (ULONG_PTR)title;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindWindowW(struct qemu_syscall *call)
{
    struct qemu_FindWindowW *c = (struct qemu_FindWindowW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)FindWindowW(QEMU_G2H(c->className), QEMU_G2H(c->title));
}

#endif

struct qemu_GetDesktopWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetDesktopWindow(void)
{
    struct qemu_GetDesktopWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDESKTOPWINDOW);

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetDesktopWindow(struct qemu_syscall *call)
{
    struct qemu_GetDesktopWindow *c = (struct qemu_GetDesktopWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetDesktopWindow();
}

#endif

struct qemu_EnableWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnableWindow(HWND hwnd, BOOL enable)
{
    struct qemu_EnableWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLEWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.enable = enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableWindow(struct qemu_syscall *call)
{
    struct qemu_EnableWindow *c = (struct qemu_EnableWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = EnableWindow(QEMU_G2H(c->hwnd), c->enable);
}

#endif

struct qemu_IsWindowEnabled
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsWindowEnabled(HWND hWnd)
{
    struct qemu_IsWindowEnabled call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWINDOWENABLED);
    call.hWnd = (ULONG_PTR)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindowEnabled(struct qemu_syscall *call)
{
    struct qemu_IsWindowEnabled *c = (struct qemu_IsWindowEnabled *)call;
    WINE_TRACE("\n");
    c->super.iret = IsWindowEnabled(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_IsWindowUnicode
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsWindowUnicode(HWND hwnd)
{
    struct qemu_IsWindowUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWINDOWUNICODE);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindowUnicode(struct qemu_syscall *call)
{
    struct qemu_IsWindowUnicode *c = (struct qemu_IsWindowUnicode *)call;
    WINE_TRACE("\n");
    c->super.iret = IsWindowUnicode(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetWindowWord
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI GetWindowWord(HWND hwnd, INT offset)
{
    struct qemu_GetWindowWord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWWORD);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowWord(struct qemu_syscall *call)
{
    struct qemu_GetWindowWord *c = (struct qemu_GetWindowWord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWindowWord(QEMU_G2H(c->hwnd), c->offset);
}

#endif

struct qemu_GetWindowLongA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI GetWindowLongA(HWND hwnd, INT offset)
{
    struct qemu_GetWindowLongA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWLONGA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowLongA(struct qemu_syscall *call)
{
    struct qemu_GetWindowLongA *c = (struct qemu_GetWindowLongA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowLongA(QEMU_G2H(c->hwnd), c->offset);
}

#endif

struct qemu_GetWindowLongW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI GetWindowLongW(HWND hwnd, INT offset)
{
    struct qemu_GetWindowLongW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWLONGW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowLongW(struct qemu_syscall *call)
{
    struct qemu_GetWindowLongW *c = (struct qemu_GetWindowLongW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowLongW(QEMU_G2H(c->hwnd), c->offset);
}

#endif

struct qemu_SetWindowWord
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI SetWindowWord(HWND hwnd, INT offset, WORD newval)
{
    struct qemu_SetWindowWord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWWORD);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowWord(struct qemu_syscall *call)
{
    struct qemu_SetWindowWord *c = (struct qemu_SetWindowWord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowWord(QEMU_G2H(c->hwnd), c->offset, c->newval);
}

#endif

struct qemu_SetWindowLongA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI SetWindowLongA(HWND hwnd, INT offset, LONG newval)
{
    struct qemu_SetWindowLongA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWLONGA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static LONG_PTR set_wndproc(HWND win, uint64_t newval, BOOL wide)
{
    LONG_PTR host_proc = (LONG_PTR)wndproc_guest_to_host(newval);
    LONG_PTR old;
    ULONG_PTR guest_old;

    WINE_TRACE("Application is setting the class proc to 0x%lx, setting host proc 0x%lx.\n",
            (unsigned long)newval, host_proc);

    if (wide)
        old = SetWindowLongPtrW(win, GWLP_WNDPROC, (LONG_PTR)host_proc);
    else
        old = SetWindowLongPtrA(win, GWLP_WNDPROC, (LONG_PTR)host_proc);

    guest_old = wndproc_host_to_guest((WNDPROC)old);

    WINE_TRACE("Returning old wndproc 0x%lx for host wndproc 0x%lx.\n", guest_old, old);

    return guest_old;
}

void qemu_SetWindowLongA(struct qemu_syscall *call)
{
    struct qemu_SetWindowLongA *c = (struct qemu_SetWindowLongA *)call;
    HWND win;
    WINE_TRACE("\n");

    win = HANDLE_g2h(c->hwnd);
    switch (c->offset)
    {
        case GWLP_WNDPROC:
            c->super.iret = set_wndproc(win, c->newval, FALSE);
            break;

        default:
            c->super.iret = SetWindowLongA(win, c->offset, c->newval);
            break;
    }
}

#endif

struct qemu_SetWindowLongW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI SetWindowLongW(HWND hwnd, INT offset, LONG newval)
{
    struct qemu_SetWindowLongW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWLONGW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowLongW(struct qemu_syscall *call)
{
    struct qemu_SetWindowLongW *c = (struct qemu_SetWindowLongW *)call;
    HWND win;
    WINE_TRACE("\n");

    win = HANDLE_g2h(c->hwnd);
    switch (c->offset)
    {
        case GWLP_WNDPROC:
            c->super.iret = set_wndproc(win, c->newval, TRUE);
            break;

        default:
            c->super.iret = SetWindowLongW(win, c->offset, c->newval);
            break;
    }
}

#endif

struct qemu_GetWindowTextA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpString;
    uint64_t nMaxCount;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetWindowTextA(HWND hwnd, LPSTR lpString, INT nMaxCount)
{
    struct qemu_GetWindowTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWTEXTA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpString = (ULONG_PTR)lpString;
    call.nMaxCount = nMaxCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowTextA(struct qemu_syscall *call)
{
    struct qemu_GetWindowTextA *c = (struct qemu_GetWindowTextA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowTextA(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpString), c->nMaxCount);
}

#endif

struct qemu_InternalGetWindowText
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpString;
    uint64_t nMaxCount;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI InternalGetWindowText(HWND hwnd,LPWSTR lpString,INT nMaxCount)
{
    struct qemu_InternalGetWindowText call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNALGETWINDOWTEXT);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpString = (ULONG_PTR)lpString;
    call.nMaxCount = nMaxCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternalGetWindowText(struct qemu_syscall *call)
{
    struct qemu_InternalGetWindowText *c = (struct qemu_InternalGetWindowText *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternalGetWindowText(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpString), c->nMaxCount);
}

#endif

struct qemu_GetWindowTextW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpString;
    uint64_t nMaxCount;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetWindowTextW(HWND hwnd, LPWSTR lpString, INT nMaxCount)
{
    struct qemu_GetWindowTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWTEXTW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpString = (ULONG_PTR)lpString;
    call.nMaxCount = nMaxCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowTextW(struct qemu_syscall *call)
{
    struct qemu_GetWindowTextW *c = (struct qemu_GetWindowTextW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowTextW(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpString), c->nMaxCount);
}

#endif

struct qemu_SetWindowTextA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpString;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetWindowTextA(HWND hwnd, LPCSTR lpString)
{
    struct qemu_SetWindowTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWTEXTA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpString = (ULONG_PTR)lpString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowTextA(struct qemu_syscall *call)
{
    struct qemu_SetWindowTextA *c = (struct qemu_SetWindowTextA *)call;
    WINE_TRACE("\n");
    c->super.iret = SetWindowTextA(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpString));
}

#endif

struct qemu_SetWindowTextW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpString;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetWindowTextW(HWND hwnd, LPCWSTR lpString)
{
    struct qemu_SetWindowTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWTEXTW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpString = (ULONG_PTR)lpString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowTextW(struct qemu_syscall *call)
{
    struct qemu_SetWindowTextW *c = (struct qemu_SetWindowTextW *)call;
    WINE_TRACE("\n");
    c->super.iret = SetWindowTextW(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpString));
}

#endif

struct qemu_GetWindowTextLengthA
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetWindowTextLengthA(HWND hwnd)
{
    struct qemu_GetWindowTextLengthA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWTEXTLENGTHA);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowTextLengthA(struct qemu_syscall *call)
{
    struct qemu_GetWindowTextLengthA *c = (struct qemu_GetWindowTextLengthA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowTextLengthA(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetWindowTextLengthW
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetWindowTextLengthW(HWND hwnd)
{
    struct qemu_GetWindowTextLengthW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWTEXTLENGTHW);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowTextLengthW(struct qemu_syscall *call)
{
    struct qemu_GetWindowTextLengthW *c = (struct qemu_GetWindowTextLengthW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowTextLengthW(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_IsWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsWindow(HWND hwnd)
{
    struct qemu_IsWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindow(struct qemu_syscall *call)
{
    struct qemu_IsWindow *c = (struct qemu_IsWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = IsWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetWindowThreadProcessId
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t process;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetWindowThreadProcessId(HWND hwnd, LPDWORD process)
{
    struct qemu_GetWindowThreadProcessId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWTHREADPROCESSID);
    call.hwnd = (ULONG_PTR)hwnd;
    call.process = (ULONG_PTR)process;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowThreadProcessId(struct qemu_syscall *call)
{
    struct qemu_GetWindowThreadProcessId *c = (struct qemu_GetWindowThreadProcessId *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowThreadProcessId(QEMU_G2H(c->hwnd), QEMU_G2H(c->process));
}

#endif

struct qemu_GetParent
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetParent(HWND hwnd)
{
    struct qemu_GetParent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPARENT);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetParent(struct qemu_syscall *call)
{
    struct qemu_GetParent *c = (struct qemu_GetParent *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetParent(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetAncestor
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetAncestor(HWND hwnd, UINT type)
{
    struct qemu_GetAncestor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETANCESTOR);
    call.hwnd = (ULONG_PTR)hwnd;
    call.type = type;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetAncestor(struct qemu_syscall *call)
{
    struct qemu_GetAncestor *c = (struct qemu_GetAncestor *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetAncestor(QEMU_G2H(c->hwnd), c->type);
}

#endif

struct qemu_SetParent
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetParent(HWND hwnd, HWND parent)
{
    struct qemu_SetParent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPARENT);
    call.hwnd = (ULONG_PTR)hwnd;
    call.parent = (ULONG_PTR)parent;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetParent(struct qemu_syscall *call)
{
    struct qemu_SetParent *c = (struct qemu_SetParent *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)SetParent(QEMU_G2H(c->hwnd), QEMU_G2H(c->parent));
}

#endif

struct qemu_IsChild
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t child;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsChild(HWND parent, HWND child)
{
    struct qemu_IsChild call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHILD);
    call.parent = (ULONG_PTR)parent;
    call.child = (ULONG_PTR)child;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsChild(struct qemu_syscall *call)
{
    struct qemu_IsChild *c = (struct qemu_IsChild *)call;
    WINE_TRACE("\n");
    c->super.iret = IsChild(QEMU_G2H(c->parent), QEMU_G2H(c->child));
}

#endif

struct qemu_IsWindowVisible
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsWindowVisible(HWND hwnd)
{
    struct qemu_IsWindowVisible call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWINDOWVISIBLE);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindowVisible(struct qemu_syscall *call)
{
    struct qemu_IsWindowVisible *c = (struct qemu_IsWindowVisible *)call;
    WINE_TRACE("\n");
    c->super.iret = IsWindowVisible(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetTopWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetTopWindow(HWND hwnd)
{
    struct qemu_GetTopWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTOPWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetTopWindow(struct qemu_syscall *call)
{
    struct qemu_GetTopWindow *c = (struct qemu_GetTopWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetTopWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t rel;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetWindow(HWND hwnd, UINT rel)
{
    struct qemu_GetWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.rel = rel;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetWindow(struct qemu_syscall *call)
{
    struct qemu_GetWindow *c = (struct qemu_GetWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetWindow(QEMU_G2H(c->hwnd), c->rel);
}

#endif

struct qemu_ShowOwnedPopups
{
    struct qemu_syscall super;
    uint64_t owner;
    uint64_t fShow;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShowOwnedPopups(HWND owner, BOOL fShow)
{
    struct qemu_ShowOwnedPopups call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWOWNEDPOPUPS);
    call.owner = (ULONG_PTR)owner;
    call.fShow = fShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShowOwnedPopups(struct qemu_syscall *call)
{
    struct qemu_ShowOwnedPopups *c = (struct qemu_ShowOwnedPopups *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ShowOwnedPopups(QEMU_G2H(c->owner), c->fShow);
}

#endif

struct qemu_GetLastActivePopup
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetLastActivePopup(HWND hwnd)
{
    struct qemu_GetLastActivePopup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLASTACTIVEPOPUP);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return (HWND)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetLastActivePopup(struct qemu_syscall *call)
{
    struct qemu_GetLastActivePopup *c = (struct qemu_GetLastActivePopup *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetLastActivePopup(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_EnumWindows
{
    struct qemu_syscall super;
    uint64_t lpEnumFunc;
    uint64_t lParam;
    uint64_t wrapper;
};

struct qemu_WndEnum_cb
{
    uint64_t func;
    uint64_t child;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall WndEnum_guest_cb(struct qemu_WndEnum_cb *call)
{
    WNDENUMPROC func = (WNDENUMPROC)(ULONG_PTR)call->func;
    return func((HWND)(ULONG_PTR)call->child, call->lparam);
}

WINUSERAPI BOOL WINAPI EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
    struct qemu_EnumWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMWINDOWS);
    call.lpEnumFunc = (ULONG_PTR)lpEnumFunc;
    call.lParam = (LPARAM)lParam;
    call.wrapper = (ULONG_PTR)WndEnum_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_WndEnum_host_param
{
    uint64_t wrapper, guest_func;
    uint64_t guest_param;
};


static BOOL CALLBACK qemu_WndEnum_host_cb(HWND child, LPARAM lp)
{
    struct qemu_WndEnum_host_param *param = (struct qemu_WndEnum_host_param *)lp;
    struct qemu_WndEnum_cb call;
    BOOL ret;

    WINE_TRACE("Calling guest proc 0x%lx(%p, 0x%lx).\n", (unsigned long)param->guest_func, child,
            (unsigned long)param->guest_param);
    call.func = param->guest_func;
    call.lparam = param->guest_param;
    call.child = (ULONG_PTR)child;

    ret = qemu_ops->qemu_execute(QEMU_G2H(param->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumWindows(struct qemu_syscall *call)
{
    struct qemu_EnumWindows *c = (struct qemu_EnumWindows *)call;
    struct qemu_WndEnum_host_param data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->lpEnumFunc;
    data.guest_param = c->lParam;

    c->super.iret = EnumWindows(c->lpEnumFunc ? qemu_WndEnum_host_cb : NULL, (LPARAM)&data);
}

#endif

struct qemu_EnumThreadWindows
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t func;
    uint64_t lParam;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumThreadWindows(DWORD id, WNDENUMPROC func, LPARAM lParam)
{
    struct qemu_EnumThreadWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMTHREADWINDOWS);
    call.id = id;
    call.func = (ULONG_PTR)func;
    call.lParam = (LPARAM)lParam;
    call.wrapper = (ULONG_PTR)WndEnum_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumThreadWindows(struct qemu_syscall *call)
{
    struct qemu_EnumThreadWindows *c = (struct qemu_EnumThreadWindows *)call;
    struct qemu_WndEnum_host_param data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->func;
    data.guest_param = c->lParam;

    c->super.iret = EnumThreadWindows(c->id, c->func ? qemu_WndEnum_host_cb : NULL, (LPARAM)&data);
}

#endif

struct qemu_EnumDesktopWindows
{
    struct qemu_syscall super;
    uint64_t desktop;
    uint64_t func;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDesktopWindows(HDESK desktop, WNDENUMPROC func, LPARAM lparam)
{
    struct qemu_EnumDesktopWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDESKTOPWINDOWS);
    call.desktop = (ULONG_PTR)desktop;
    call.func = (ULONG_PTR)func;
    call.lparam = lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDesktopWindows(struct qemu_syscall *call)
{
    struct qemu_EnumDesktopWindows *c = (struct qemu_EnumDesktopWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDesktopWindows(QEMU_G2H(c->desktop), QEMU_G2H(c->func), c->lparam);
}

#endif

struct qemu_EnumChildWindows
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t func;
    uint64_t lParam;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumChildWindows(HWND parent, WNDENUMPROC func, LPARAM lParam)
{
    struct qemu_EnumChildWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCHILDWINDOWS);
    call.parent = (ULONG_PTR)parent;
    call.func = (ULONG_PTR)func;
    call.lParam = (LPARAM)lParam;
    call.wrapper = (ULONG_PTR)WndEnum_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumChildWindows(struct qemu_syscall *call)
{
    struct qemu_EnumChildWindows *c = (struct qemu_EnumChildWindows *)call;
    struct qemu_WndEnum_host_param data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->func;
    data.guest_param = c->lParam;

    c->super.iret = EnumChildWindows(QEMU_G2H(c->parent), c->func ? qemu_WndEnum_host_cb : NULL, (LPARAM)&data);
}

#endif

struct qemu_AnyPopup
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AnyPopup(void)
{
    struct qemu_AnyPopup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ANYPOPUP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AnyPopup(struct qemu_syscall *call)
{
    struct qemu_AnyPopup *c = (struct qemu_AnyPopup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AnyPopup();
}

#endif

struct qemu_FlashWindow
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t bInvert;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI FlashWindow(HWND hWnd, BOOL bInvert)
{
    struct qemu_FlashWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLASHWINDOW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.bInvert = bInvert;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlashWindow(struct qemu_syscall *call)
{
    struct qemu_FlashWindow *c = (struct qemu_FlashWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = FlashWindow(QEMU_G2H(c->hWnd), c->bInvert);
}

#endif

struct qemu_FlashWindowEx
{
    struct qemu_syscall super;
    uint64_t pfinfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI FlashWindowEx(PFLASHWINFO pfinfo)
{
    struct qemu_FlashWindowEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLASHWINDOWEX);
    call.pfinfo = (ULONG_PTR)pfinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlashWindowEx(struct qemu_syscall *call)
{
    struct qemu_FlashWindowEx *c = (struct qemu_FlashWindowEx *)call;
    WINE_TRACE("\n");
    c->super.iret = FlashWindowEx(QEMU_G2H(c->pfinfo));
}

#endif

struct qemu_GetWindowContextHelpId
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetWindowContextHelpId(HWND hwnd)
{
    struct qemu_GetWindowContextHelpId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWCONTEXTHELPID);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowContextHelpId(struct qemu_syscall *call)
{
    struct qemu_GetWindowContextHelpId *c = (struct qemu_GetWindowContextHelpId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWindowContextHelpId(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_SetWindowContextHelpId
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetWindowContextHelpId(HWND hwnd, DWORD id)
{
    struct qemu_SetWindowContextHelpId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWCONTEXTHELPID);
    call.hwnd = (ULONG_PTR)hwnd;
    call.id = id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowContextHelpId(struct qemu_syscall *call)
{
    struct qemu_SetWindowContextHelpId *c = (struct qemu_SetWindowContextHelpId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowContextHelpId(QEMU_G2H(c->hwnd), c->id);
}

#endif

struct qemu_GetWindowModuleFileNameA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t module;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetWindowModuleFileNameA(HWND hwnd, LPSTR module, UINT size)
{
    struct qemu_GetWindowModuleFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWMODULEFILENAMEA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.module = (ULONG_PTR)module;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowModuleFileNameA(struct qemu_syscall *call)
{
    struct qemu_GetWindowModuleFileNameA *c = (struct qemu_GetWindowModuleFileNameA *)call;
    DWORD pid;
    HWND hwnd;
    HINSTANCE inst;
    WCHAR *wbuf;
    char *out;

    WINE_TRACE("\n");
    hwnd = (HWND)c->hwnd;
    out = QEMU_G2H(c->module);

    c->super.iret = 0;
    if (!GetWindowThreadProcessId(hwnd, &pid))
        return;

    if (pid != GetCurrentProcessId())
        return;

    inst = (HINSTANCE)GetWindowLongPtrA(hwnd, GWLP_HINSTANCE);

    wbuf = HeapAlloc(GetProcessHeap(), 0, sizeof(*wbuf) * c->size);
    if (!wbuf)
    {
        SetLastError( ERROR_NOT_ENOUGH_MEMORY );
        c->super.iret = 0;
        return;
    }

    c->super.iret = qemu_ops->qemu_GetModuleFileName(inst, wbuf, c->size);

    if (c->super.iret)
    {
        c->super.iret = WideCharToMultiByte(CP_ACP, 0, wbuf, c->super.iret,
                out, c->size, NULL, NULL);
        if (c->super.iret < c->size)
            out[c->super.iret] = '\0';
        else
            SetLastError( ERROR_INSUFFICIENT_BUFFER );
    }

    HeapFree(GetProcessHeap(), 0, wbuf);
}

#endif

struct qemu_GetWindowModuleFileNameW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t module;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetWindowModuleFileNameW(HWND hwnd, LPWSTR module, UINT size)
{
    struct qemu_GetWindowModuleFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWMODULEFILENAMEW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.module = (ULONG_PTR)module;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowModuleFileNameW(struct qemu_syscall *call)
{
    struct qemu_GetWindowModuleFileNameW *c = (struct qemu_GetWindowModuleFileNameW *)call;
    DWORD pid;
    HWND hwnd;
    HINSTANCE inst;

    WINE_TRACE("\n");
    hwnd = (HWND)c->hwnd;

    /* Checking the different error conditions without user32 internals is difficult.
     * We can't forward it 1:1 because otherwise we'd get an error because the module
     * entry can't be found in the host's module database. */
    c->super.iret = 0;
    if (!GetWindowThreadProcessId(hwnd, &pid))
        return;

    if (pid != GetCurrentProcessId())
        return;

    inst = (HINSTANCE)GetWindowLongPtrW(hwnd, GWLP_HINSTANCE);
    c->super.iret = qemu_ops->qemu_GetModuleFileName(inst, QEMU_G2H(c->module), c->size);
}

#endif

struct qemu_GetWindowInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pwi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetWindowInfo(HWND hwnd, PWINDOWINFO pwi)
{
    struct qemu_GetWindowInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWINFO);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pwi = (ULONG_PTR)pwi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowInfo(struct qemu_syscall *call)
{
    struct qemu_GetWindowInfo *c = (struct qemu_GetWindowInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowInfo(QEMU_G2H(c->hwnd), QEMU_G2H(c->pwi));
}

#endif

struct qemu_SwitchDesktop
{
    struct qemu_syscall super;
    uint64_t hDesktop;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SwitchDesktop(HDESK hDesktop)
{
    struct qemu_SwitchDesktop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SWITCHDESKTOP);
    call.hDesktop = (ULONG_PTR)hDesktop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SwitchDesktop(struct qemu_syscall *call)
{
    struct qemu_SwitchDesktop *c = (struct qemu_SwitchDesktop *)call;
    WINE_TRACE("\n");
    c->super.iret = SwitchDesktop(QEMU_G2H(c->hDesktop));
}

#endif

struct qemu_SetLayeredWindowAttributes
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t key;
    uint64_t alpha;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetLayeredWindowAttributes(HWND hwnd, COLORREF key, BYTE alpha, DWORD flags)
{
    struct qemu_SetLayeredWindowAttributes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLAYEREDWINDOWATTRIBUTES);
    call.hwnd = (ULONG_PTR)hwnd;
    call.key = key;
    call.alpha = alpha;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetLayeredWindowAttributes(struct qemu_syscall *call)
{
    struct qemu_SetLayeredWindowAttributes *c = (struct qemu_SetLayeredWindowAttributes *)call;
    WINE_TRACE("\n");
    c->super.iret = SetLayeredWindowAttributes(QEMU_G2H(c->hwnd), c->key, c->alpha, c->flags);
}

#endif

struct qemu_GetLayeredWindowAttributes
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t key;
    uint64_t alpha;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetLayeredWindowAttributes(HWND hwnd, COLORREF *key, BYTE *alpha, DWORD *flags)
{
    struct qemu_GetLayeredWindowAttributes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLAYEREDWINDOWATTRIBUTES);
    call.hwnd = (ULONG_PTR)hwnd;
    call.key = (ULONG_PTR)key;
    call.alpha = (ULONG_PTR)alpha;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLayeredWindowAttributes(struct qemu_syscall *call)
{
    struct qemu_GetLayeredWindowAttributes *c = (struct qemu_GetLayeredWindowAttributes *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLayeredWindowAttributes(QEMU_G2H(c->hwnd), QEMU_G2H(c->key), QEMU_G2H(c->alpha), QEMU_G2H(c->flags));
}

#endif

struct qemu_UpdateLayeredWindowIndirect
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UpdateLayeredWindowIndirect(HWND hwnd, const UPDATELAYEREDWINDOWINFO *info)
{
    struct qemu_UpdateLayeredWindowIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATELAYEREDWINDOWINDIRECT);
    call.hwnd = (ULONG_PTR)hwnd;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateLayeredWindowIndirect(struct qemu_syscall *call)
{
    struct qemu_UpdateLayeredWindowIndirect *c = (struct qemu_UpdateLayeredWindowIndirect *)call;
    WINE_TRACE("\n");
    c->super.iret = UpdateLayeredWindowIndirect(QEMU_G2H(c->hwnd), QEMU_G2H(c->info));
}

#endif

struct qemu_UpdateLayeredWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hdcDst;
    uint64_t pptDst;
    uint64_t psize;
    uint64_t hdcSrc;
    uint64_t pptSrc;
    uint64_t crKey;
    uint64_t pblend;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UpdateLayeredWindow(HWND hwnd, HDC hdcDst, POINT *pptDst, SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD flags)
{
    struct qemu_UpdateLayeredWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATELAYEREDWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.hdcDst = (ULONG_PTR)hdcDst;
    call.pptDst = (ULONG_PTR)pptDst;
    call.psize = (ULONG_PTR)psize;
    call.hdcSrc = (ULONG_PTR)hdcSrc;
    call.pptSrc = (ULONG_PTR)pptSrc;
    call.crKey = crKey;
    call.pblend = (ULONG_PTR)pblend;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateLayeredWindow(struct qemu_syscall *call)
{
    struct qemu_UpdateLayeredWindow *c = (struct qemu_UpdateLayeredWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = UpdateLayeredWindow(QEMU_G2H(c->hwnd), QEMU_G2H(c->hdcDst), QEMU_G2H(c->pptDst), QEMU_G2H(c->psize), QEMU_G2H(c->hdcSrc), QEMU_G2H(c->pptSrc), c->crKey, QEMU_G2H(c->pblend), c->flags);
}

#endif

struct qemu_GetProcessDefaultLayout
{
    struct qemu_syscall super;
    uint64_t layout;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetProcessDefaultLayout(DWORD *layout)
{
    struct qemu_GetProcessDefaultLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSDEFAULTLAYOUT);
    call.layout = (ULONG_PTR)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessDefaultLayout(struct qemu_syscall *call)
{
    struct qemu_GetProcessDefaultLayout *c = (struct qemu_GetProcessDefaultLayout *)call;
    WINE_TRACE("\n");
    c->super.iret = GetProcessDefaultLayout(QEMU_G2H(c->layout));
}

#endif

struct qemu_SetProcessDefaultLayout
{
    struct qemu_syscall super;
    uint64_t layout;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetProcessDefaultLayout(DWORD layout)
{
    struct qemu_SetProcessDefaultLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSDEFAULTLAYOUT);
    call.layout = layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessDefaultLayout(struct qemu_syscall *call)
{
    struct qemu_SetProcessDefaultLayout *c = (struct qemu_SetProcessDefaultLayout *)call;
    WINE_TRACE("\n");
    c->super.iret = SetProcessDefaultLayout(c->layout);
}

#endif

struct qemu_GetWindowLongPtrW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

LONG_PTR WINAPI user32_GetWindowLongPtrW(HWND hwnd, INT offset)
{
    struct qemu_GetWindowLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWLONGPTRW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

LONG_PTR get_wndproc(HWND window, BOOL wide)
{
    LONG_PTR proc;

    if (wide)
        proc = GetWindowLongPtrW(window, GWLP_WNDPROC);
    else
        proc = GetWindowLongPtrA(window, GWLP_WNDPROC);

    return wndproc_host_to_guest((WNDPROC)proc);
}

void qemu_GetWindowLongPtrW(struct qemu_syscall *call)
{
    struct qemu_GetWindowLongPtrW *c = (struct qemu_GetWindowLongPtrW *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GWLP_WNDPROC:
            c->super.iret = get_wndproc(win, TRUE);
            break;

        default:
            c->super.iret = GetWindowLongPtrW(win, c->offset);
            break;
    }
}

#endif

struct qemu_GetWindowLongPtrA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

LONG_PTR WINAPI user32_GetWindowLongPtrA(HWND hwnd, INT offset)
{
    struct qemu_GetWindowLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWLONGPTRA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowLongPtrA(struct qemu_syscall *call)
{
    struct qemu_GetWindowLongPtrA *c = (struct qemu_GetWindowLongPtrA *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GWLP_WNDPROC:
            c->super.iret = get_wndproc(win, FALSE);
            break;

        default:
            c->super.iret = GetWindowLongPtrA(win, c->offset);
            break;
    }
}

#endif

struct qemu_SetWindowLongPtrW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

LONG_PTR WINAPI user32_SetWindowLongPtrW(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetWindowLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWLONGPTRW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowLongPtrW(struct qemu_syscall *call)
{
    struct qemu_SetWindowLongPtrW *c = (struct qemu_SetWindowLongPtrW *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GWLP_WNDPROC:
            c->super.iret = set_wndproc(win, c->newval, TRUE);
            break;

        default:
            c->super.iret = SetWindowLongPtrW(QEMU_G2H(c->hwnd), c->offset, c->newval);
            break;
    }
}

#endif

struct qemu_SetWindowLongPtrA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t offset;
    uint64_t newval;
};

#ifdef QEMU_DLL_GUEST

LONG_PTR WINAPI user32_SetWindowLongPtrA(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetWindowLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWLONGPTRA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.offset = offset;
    call.newval = newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowLongPtrA(struct qemu_syscall *call)
{
    struct qemu_SetWindowLongPtrA *c = (struct qemu_SetWindowLongPtrA *)call;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;

    switch (c->offset)
    {
        case GWLP_WNDPROC:
            c->super.iret = set_wndproc(win, c->newval, FALSE);
            break;

        default:
            c->super.iret = SetWindowLongPtrA(QEMU_G2H(c->hwnd), c->offset, c->newval);
            break;
    }
}

#endif

struct qemu_RegisterTouchWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI RegisterTouchWindow(HWND hwnd, ULONG flags)
{
    struct qemu_RegisterTouchWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERTOUCHWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterTouchWindow to Wine headers? */
extern BOOL WINAPI RegisterTouchWindow(HWND hwnd, ULONG flags);
void qemu_RegisterTouchWindow(struct qemu_syscall *call)
{
    struct qemu_RegisterTouchWindow *c = (struct qemu_RegisterTouchWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterTouchWindow(QEMU_G2H(c->hwnd), c->flags);
}

#endif

struct qemu_DragDetect
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t ptX, ptY;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DragDetect(HWND hWnd, POINT pt)
{
    struct qemu_DragDetect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAGDETECT);
    call.hWnd = (ULONG_PTR)hWnd;
    call.ptX = pt.x;
    call.ptY = pt.y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DragDetect(struct qemu_syscall *call)
{
    struct qemu_DragDetect *c = (struct qemu_DragDetect *)call;
    POINT pt;
    WINE_FIXME("Unverified!\n");

    pt.x = c->ptX;
    pt.y = c->ptY;
    c->super.iret = DragDetect(QEMU_G2H(c->hWnd), pt);
}

#endif
struct qemu_CloseTouchInputHandle
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseTouchInputHandle(HTOUCHINPUT handle)
{
    struct qemu_CloseTouchInputHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSETOUCHINPUTHANDLE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseTouchInputHandle(struct qemu_syscall *call)
{
    struct qemu_CloseTouchInputHandle *c = (struct qemu_CloseTouchInputHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseTouchInputHandle(QEMU_G2H(c->handle));
}

#endif
struct qemu_UnregisterTouchWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnregisterTouchWindow(HWND hwnd)
{
    struct qemu_UnregisterTouchWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERTOUCHWINDOW);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterTouchWindow(struct qemu_syscall *call)
{
    struct qemu_UnregisterTouchWindow *c = (struct qemu_UnregisterTouchWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnregisterTouchWindow(QEMU_G2H(c->hwnd));
}

#endif
struct qemu_GetTouchInputInfo
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetTouchInputInfo(HTOUCHINPUT handle, UINT count, TOUCHINPUT *ptr, int size)
{
    struct qemu_GetTouchInputInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTOUCHINPUTINFO);
    call.handle = (ULONG_PTR)handle;
    call.count = count;
    call.ptr = (ULONG_PTR)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTouchInputInfo(struct qemu_syscall *call)
{
    struct qemu_GetTouchInputInfo *c = (struct qemu_GetTouchInputInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTouchInputInfo(QEMU_G2H(c->handle), c->count, QEMU_G2H(c->ptr), c->size);
}

#endif
struct qemu_GetGestureInfo
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetGestureInfo(HGESTUREINFO handle, PGESTUREINFO ptr)
{
    struct qemu_GetGestureInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGESTUREINFO);
    call.handle = (ULONG_PTR)handle;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGestureInfo(struct qemu_syscall *call)
{
    struct qemu_GetGestureInfo *c = (struct qemu_GetGestureInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetGestureInfo(QEMU_G2H(c->handle), QEMU_G2H(c->ptr));
}

#endif
