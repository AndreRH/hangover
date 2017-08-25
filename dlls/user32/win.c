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

#include "windows-user-services.h"
#include "dll_list.h"
#include "user32.h"

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
    call.exStyle = (uint64_t)exStyle;
    call.className = (uint64_t)className;
    call.windowName = (uint64_t)windowName;
    call.style = (uint64_t)style;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.parent = (uint64_t)parent;
    call.menu = (uint64_t)menu;
    call.instance = (uint64_t)instance;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateWindowExA(struct qemu_syscall *call)
{
    struct qemu_CreateWindowExA *c = (struct qemu_CreateWindowExA *)call;
    HINSTANCE inst;
    WINE_TRACE("\n");

    /* Do not modify hInstance here, it breaks the tests. Let's see if it is actually necessary. */
    c->super.iret = (uint64_t)CreateWindowExA(c->exStyle, QEMU_G2H(c->className), QEMU_G2H(c->windowName), c->style, c->x, c->y, c->width, c->height, QEMU_G2H(c->parent), QEMU_G2H(c->menu), (HINSTANCE)c->instance, QEMU_G2H(c->data));
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
    call.exStyle = (uint64_t)exStyle;
    call.className = (uint64_t)className;
    call.windowName = (uint64_t)windowName;
    call.style = (uint64_t)style;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.parent = (uint64_t)parent;
    call.menu = (uint64_t)menu;
    call.instance = (uint64_t)instance;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_CreateWindowExW(struct qemu_syscall *call)
{
    struct qemu_CreateWindowExW *c = (struct qemu_CreateWindowExW *)call;
    HINSTANCE inst;
    WINE_TRACE("\n");

    /* Do not modify hInstance here, it breaks the tests. Let's see if it is actually necessary. */
    c->super.iret = (uint64_t)CreateWindowExW(c->exStyle, QEMU_G2H(c->className), QEMU_G2H(c->windowName), c->style, c->x, c->y, c->width, c->height, QEMU_G2H(c->parent), QEMU_G2H(c->menu), (HINSTANCE)c->instance, QEMU_G2H(c->data));
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
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyWindow(struct qemu_syscall *call)
{
    struct qemu_DestroyWindow *c = (struct qemu_DestroyWindow *)call;
    unsigned int i;
    HWND win;

    WINE_TRACE("\n");
    win = (HWND)c->hwnd;
    c->super.iret = DestroyWindow(win);

    if (!c->super.iret)
        return;

    for (i = 0; i < win_wrapper_count; ++i)
    {
        if (win_wrappers[i].win == win)
        {
            WINE_TRACE("Freeing wndproc wrapper for window %p.\n", win);
            win_wrappers[i].win = NULL;
            win_wrappers[i].guest_proc = 0;
        }
    }
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
    call.hwnd = (uint64_t)hwnd;

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
    call.hwnd = (uint64_t)hwnd;

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
    call.parent = (uint64_t)parent;
    call.child = (uint64_t)child;
    call.className = (uint64_t)className;
    call.title = (uint64_t)title;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_FindWindowExW(struct qemu_syscall *call)
{
    struct qemu_FindWindowExW *c = (struct qemu_FindWindowExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindWindowExW(QEMU_G2H(c->parent), QEMU_G2H(c->child), QEMU_G2H(c->className), QEMU_G2H(c->title));
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
    call.className = (uint64_t)className;
    call.title = (uint64_t)title;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_FindWindowA(struct qemu_syscall *call)
{
    struct qemu_FindWindowA *c = (struct qemu_FindWindowA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindWindowA(QEMU_G2H(c->className), QEMU_G2H(c->title));
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
    call.parent = (uint64_t)parent;
    call.child = (uint64_t)child;
    call.className = (uint64_t)className;
    call.title = (uint64_t)title;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_FindWindowExA(struct qemu_syscall *call)
{
    struct qemu_FindWindowExA *c = (struct qemu_FindWindowExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindWindowExA(QEMU_G2H(c->parent), QEMU_G2H(c->child), QEMU_G2H(c->className), QEMU_G2H(c->title));
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
    call.className = (uint64_t)className;
    call.title = (uint64_t)title;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_FindWindowW(struct qemu_syscall *call)
{
    struct qemu_FindWindowW *c = (struct qemu_FindWindowW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindWindowW(QEMU_G2H(c->className), QEMU_G2H(c->title));
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

    return (HWND)call.super.iret;
}

#else

void qemu_GetDesktopWindow(struct qemu_syscall *call)
{
    struct qemu_GetDesktopWindow *c = (struct qemu_GetDesktopWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetDesktopWindow();
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
    call.hwnd = (uint64_t)hwnd;
    call.enable = (uint64_t)enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableWindow(struct qemu_syscall *call)
{
    struct qemu_EnableWindow *c = (struct qemu_EnableWindow *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindowEnabled(struct qemu_syscall *call)
{
    struct qemu_IsWindowEnabled *c = (struct qemu_IsWindowEnabled *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindowUnicode(struct qemu_syscall *call)
{
    struct qemu_IsWindowUnicode *c = (struct qemu_IsWindowUnicode *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

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
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowLongA(struct qemu_syscall *call)
{
    struct qemu_GetWindowLongA *c = (struct qemu_GetWindowLongA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowLongW(struct qemu_syscall *call)
{
    struct qemu_GetWindowLongW *c = (struct qemu_GetWindowLongW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

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
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowLongA(struct qemu_syscall *call)
{
    struct qemu_SetWindowLongA *c = (struct qemu_SetWindowLongA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowLongA(QEMU_G2H(c->hwnd), c->offset, c->newval);
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
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowLongW(struct qemu_syscall *call)
{
    struct qemu_SetWindowLongW *c = (struct qemu_SetWindowLongW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowLongW(QEMU_G2H(c->hwnd), c->offset, c->newval);
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
    call.hwnd = (uint64_t)hwnd;
    call.lpString = (uint64_t)lpString;
    call.nMaxCount = (uint64_t)nMaxCount;

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
    call.hwnd = (uint64_t)hwnd;
    call.lpString = (uint64_t)lpString;
    call.nMaxCount = (uint64_t)nMaxCount;

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
    call.hwnd = (uint64_t)hwnd;
    call.lpString = (uint64_t)lpString;
    call.nMaxCount = (uint64_t)nMaxCount;

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
    call.hwnd = (uint64_t)hwnd;
    call.lpString = (uint64_t)lpString;

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
    call.hwnd = (uint64_t)hwnd;
    call.lpString = (uint64_t)lpString;

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
    call.hwnd = (uint64_t)hwnd;

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
    call.hwnd = (uint64_t)hwnd;

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
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWindow(struct qemu_syscall *call)
{
    struct qemu_IsWindow *c = (struct qemu_IsWindow *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.process = (uint64_t)process;

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
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetParent(struct qemu_syscall *call)
{
    struct qemu_GetParent *c = (struct qemu_GetParent *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetParent(QEMU_G2H(c->hwnd));
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
    call.hwnd = (uint64_t)hwnd;
    call.type = (uint64_t)type;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetAncestor(struct qemu_syscall *call)
{
    struct qemu_GetAncestor *c = (struct qemu_GetAncestor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetAncestor(QEMU_G2H(c->hwnd), c->type);
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
    call.hwnd = (uint64_t)hwnd;
    call.parent = (uint64_t)parent;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_SetParent(struct qemu_syscall *call)
{
    struct qemu_SetParent *c = (struct qemu_SetParent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetParent(QEMU_G2H(c->hwnd), QEMU_G2H(c->parent));
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
    call.parent = (uint64_t)parent;
    call.child = (uint64_t)child;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsChild(struct qemu_syscall *call)
{
    struct qemu_IsChild *c = (struct qemu_IsChild *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;

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
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetTopWindow(struct qemu_syscall *call)
{
    struct qemu_GetTopWindow *c = (struct qemu_GetTopWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetTopWindow(QEMU_G2H(c->hwnd));
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
    call.hwnd = (uint64_t)hwnd;
    call.rel = (uint64_t)rel;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetWindow(struct qemu_syscall *call)
{
    struct qemu_GetWindow *c = (struct qemu_GetWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetWindow(QEMU_G2H(c->hwnd), c->rel);
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
    call.owner = (uint64_t)owner;
    call.fShow = (uint64_t)fShow;

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
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetLastActivePopup(struct qemu_syscall *call)
{
    struct qemu_GetLastActivePopup *c = (struct qemu_GetLastActivePopup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetLastActivePopup(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_EnumWindows
{
    struct qemu_syscall super;
    uint64_t lpEnumFunc;
    uint64_t lParam;
};

struct qemu_WndEnum_cb
{
    uint64_t func;
    uint64_t child;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

static uint64_t WndEnum_guest_cb(struct qemu_WndEnum_cb *call)
{
    WNDENUMPROC func = (WNDENUMPROC)call->func;
    return func((HWND)call->child, call->lparam);
}

WINUSERAPI BOOL WINAPI EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
    struct qemu_EnumWindows call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMWINDOWS);
    call.lpEnumFunc = (uint64_t)lpEnumFunc;
    call.lParam = (uint64_t)lParam;

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

    WINE_TRACE("Calling guest proc 0x%lx(%p, 0x%lx).\n", param->guest_func, child, param->guest_param);
    call.func = param->guest_func;
    call.lparam = param->guest_param;
    call.child = (uint64_t)child;

    ret = qemu_ops->qemu_execute(QEMU_G2H(param->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumWindows(struct qemu_syscall *call)
{
    struct qemu_EnumWindows *c = (struct qemu_EnumWindows *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumWindows(QEMU_G2H(c->lpEnumFunc), c->lParam);
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
    call.id = (uint64_t)id;
    call.func = (uint64_t)func;
    call.lParam = (uint64_t)lParam;
    call.wrapper = (uint64_t)WndEnum_guest_cb;

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
    call.desktop = (uint64_t)desktop;
    call.func = (uint64_t)func;
    call.lparam = (uint64_t)lparam;

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
    call.parent = (uint64_t)parent;
    call.func = (uint64_t)func;
    call.lParam = (uint64_t)lParam;
    call.wrapper = (uint64_t)WndEnum_guest_cb;

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
    call.hWnd = (uint64_t)hWnd;
    call.bInvert = (uint64_t)bInvert;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlashWindow(struct qemu_syscall *call)
{
    struct qemu_FlashWindow *c = (struct qemu_FlashWindow *)call;
    WINE_FIXME("Unverified!\n");
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
    call.pfinfo = (uint64_t)pfinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlashWindowEx(struct qemu_syscall *call)
{
    struct qemu_FlashWindowEx *c = (struct qemu_FlashWindowEx *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;

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
    call.hwnd = (uint64_t)hwnd;
    call.id = (uint64_t)id;

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
    call.hwnd = (uint64_t)hwnd;
    call.module = (uint64_t)module;
    call.size = (uint64_t)size;

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
    call.hwnd = (uint64_t)hwnd;
    call.module = (uint64_t)module;
    call.size = (uint64_t)size;

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
    call.hwnd = (uint64_t)hwnd;
    call.pwi = (uint64_t)pwi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowInfo(struct qemu_syscall *call)
{
    struct qemu_GetWindowInfo *c = (struct qemu_GetWindowInfo *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hDesktop = (uint64_t)hDesktop;

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
    call.hwnd = (uint64_t)hwnd;
    call.key = (uint64_t)key;
    call.alpha = (uint64_t)alpha;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetLayeredWindowAttributes(struct qemu_syscall *call)
{
    struct qemu_SetLayeredWindowAttributes *c = (struct qemu_SetLayeredWindowAttributes *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.key = (uint64_t)key;
    call.alpha = (uint64_t)alpha;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLayeredWindowAttributes(struct qemu_syscall *call)
{
    struct qemu_GetLayeredWindowAttributes *c = (struct qemu_GetLayeredWindowAttributes *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.info = (uint64_t)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateLayeredWindowIndirect(struct qemu_syscall *call)
{
    struct qemu_UpdateLayeredWindowIndirect *c = (struct qemu_UpdateLayeredWindowIndirect *)call;
    WINE_FIXME("Unverified!\n");
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
    call.hwnd = (uint64_t)hwnd;
    call.hdcDst = (uint64_t)hdcDst;
    call.pptDst = (uint64_t)pptDst;
    call.psize = (uint64_t)psize;
    call.hdcSrc = (uint64_t)hdcSrc;
    call.pptSrc = (uint64_t)pptSrc;
    call.crKey = (uint64_t)crKey;
    call.pblend = (uint64_t)pblend;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateLayeredWindow(struct qemu_syscall *call)
{
    struct qemu_UpdateLayeredWindow *c = (struct qemu_UpdateLayeredWindow *)call;
    WINE_FIXME("Unverified!\n");
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
    call.layout = (uint64_t)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessDefaultLayout(struct qemu_syscall *call)
{
    struct qemu_GetProcessDefaultLayout *c = (struct qemu_GetProcessDefaultLayout *)call;
    WINE_FIXME("Unverified!\n");
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
    call.layout = (uint64_t)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessDefaultLayout(struct qemu_syscall *call)
{
    struct qemu_SetProcessDefaultLayout *c = (struct qemu_SetProcessDefaultLayout *)call;
    WINE_FIXME("Unverified!\n");
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

WINUSERAPI LONG_PTR WINAPI GetWindowLongPtrW(HWND hwnd, INT offset)
{
    struct qemu_GetWindowLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWLONGPTRW);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

LONG_PTR get_wndproc(HWND window, BOOL wide)
{
    LONG_PTR proc;
    const struct classproc_wrapper *wrapper;
    struct reverse_classproc_wrapper *reverse_wrapper;

    if (wide)
        proc = GetWindowLongPtrW(window, GWLP_WNDPROC);
    else
        proc = GetWindowLongPtrA(window, GWLP_WNDPROC);

    if (!proc)
    {
        WINE_WARN("Host wndproc is NULL, returning NULL.\n");
        return 0;
    }

    /* Per class and per window wrappers. */
    if ((proc >= (ULONG_PTR)&class_wrappers[0] && proc <= (ULONG_PTR)&class_wrappers[class_wrapper_count])
            || (proc >= (ULONG_PTR)&win_wrappers[0] && proc <= (ULONG_PTR)&win_wrappers[win_wrapper_count]))
    {
        wrapper = (const struct classproc_wrapper *)proc;
        WINE_TRACE("Host wndproc is a wrapper function. Returning guest wndproc 0x%lx\n", wrapper->guest_proc);
        return wrapper->guest_proc;
    }

    /* Wine builtin class. Return a reverse wrapper. */
    reverse_wrapper = find_reverse_wndproc_wrapper((void *)proc);
    reverse_wrapper->guest_func = reverse_classproc_func;
    WINE_TRACE("Returning reverse wrapper %p for host function 0x%lx\n", reverse_wrapper, proc);
    return (ULONG_PTR)reverse_wrapper;
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

WINUSERAPI LONG_PTR WINAPI GetWindowLongPtrA(HWND hwnd, INT offset)
{
    struct qemu_GetWindowLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWLONGPTRA);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;

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

WINUSERAPI LONG_PTR WINAPI SetWindowLongPtrW(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetWindowLongPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWLONGPTRW);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static struct classproc_wrapper *find_free_wndproc_wrapper(void)
{
    unsigned int i;

    /* Find a forward wrapper to call the new guest proc. */
    for (i = 0; i < win_wrapper_count; ++i)
    {
        if (!win_wrappers[i].atom)
        {
            WINE_TRACE("Returning wrapper %p\n", &win_wrappers[i]);
            return &win_wrappers[i];
        }
    }
    WINE_FIXME("All per-window wrappers are in use\n");
    return NULL;
}

static LONG_PTR set_wndproc(HWND win, uint64_t newval, BOOL wide)
{
    uint64_t ret = get_wndproc(win, wide);
    LONG_PTR host_proc;
    struct classproc_wrapper *wrapper;
    struct reverse_classproc_wrapper *reverse_wrapper;

    if (wide)
        host_proc = GetWindowLongPtrW(win, GWLP_WNDPROC);
    else
        host_proc = GetWindowLongPtrA(win, GWLP_WNDPROC);

    if (newval >= (LONG_PTR)&reverse_classproc_wrappers[0]
            && newval <= (LONG_PTR)&reverse_classproc_wrappers[REVERSE_CLASSPROC_WRAPPER_COUNT])
    {
        reverse_wrapper = (struct reverse_classproc_wrapper *)newval;
        WINE_TRACE("Restoring native window function %p\n", reverse_wrapper->host_func);
        if (wide)
            SetWindowLongPtrW(win, GWLP_WNDPROC, (LONG_PTR)reverse_wrapper->host_func);
        else
            SetWindowLongPtrA(win, GWLP_WNDPROC, (LONG_PTR)reverse_wrapper->host_func);

        newval = 0;
    }

    if (host_proc >= (ULONG_PTR)&win_wrappers[0] && host_proc <= (ULONG_PTR)&win_wrappers[win_wrapper_count])
    {
        WINE_TRACE("Old host proc is a per-window wrapper %p.\n", (void *)host_proc);

        wrapper = (struct classproc_wrapper *)host_proc;
        if (wrapper->win != win)
            WINE_ERR("Expected window %p, got %p.\n", wrapper->win, win);

        wrapper->guest_proc = newval;
        wrapper->win = newval ? win : NULL;
        return ret;
    }

    if (!newval)
        WINE_ERR("Did not expect to get here.\n");

    wrapper = find_free_wndproc_wrapper();
    assert(wrapper);

    /* FIXME: Similarly to the case in set_class_wndproc, we won't be able to
     * free up slots in win_wrappers if the application is overwriting the
     * WNDPROC of one of Wine's windows because we do not see the DestroyWindow
     * call. Unlike UnregisterClass this is an actual issue here because we can
     * expect windows to be destroyed and recreated a lot more than classes and
     * there is no upper bound on the number of builtin windows that can be
     * created. */
    WINE_TRACE("Setting new forward wndproc wrapper %p for function 0x%lx.\n",
            wrapper, newval);
    if (wide)
        host_proc = SetWindowLongPtrW(win, GWLP_WNDPROC, (LONG_PTR)wrapper);
    else
        host_proc = SetWindowLongPtrA(win, GWLP_WNDPROC, (LONG_PTR)wrapper);
    WINE_TRACE("SetWindowLongPtr returned 0x%lx.\n", host_proc);

    wrapper->win = win;
    wrapper->guest_proc = newval;

    return ret;
}

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

WINUSERAPI LONG_PTR WINAPI SetWindowLongPtrA(HWND hwnd, INT offset, LONG_PTR newval)
{
    struct qemu_SetWindowLongPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWLONGPTRA);
    call.hwnd = (uint64_t)hwnd;
    call.offset = (uint64_t)offset;
    call.newval = (uint64_t)newval;

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
    call.hwnd = (uint64_t)hwnd;
    call.flags = (uint64_t)flags;

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

