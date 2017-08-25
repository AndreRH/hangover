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


struct qemu_DrawCaption
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hdc;
    uint64_t lpRect;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawCaption (HWND hwnd, HDC hdc, const RECT *lpRect, UINT uFlags)
{
    struct qemu_DrawCaption call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWCAPTION);
    call.hwnd = (uint64_t)hwnd;
    call.hdc = (uint64_t)hdc;
    call.lpRect = (uint64_t)lpRect;
    call.uFlags = (uint64_t)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawCaption(struct qemu_syscall *call)
{
    struct qemu_DrawCaption *c = (struct qemu_DrawCaption *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawCaption(QEMU_G2H(c->hwnd), QEMU_G2H(c->hdc), QEMU_G2H(c->lpRect), c->uFlags);
}

#endif

struct qemu_DrawCaptionTempA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hdc;
    uint64_t rect;
    uint64_t hFont;
    uint64_t hIcon;
    uint64_t str;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawCaptionTempA (HWND hwnd, HDC hdc, const RECT *rect, HFONT hFont, HICON hIcon, LPCSTR str, UINT uFlags)
{
    struct qemu_DrawCaptionTempA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWCAPTIONTEMPA);
    call.hwnd = (uint64_t)hwnd;
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;
    call.hFont = (uint64_t)hFont;
    call.hIcon = (uint64_t)hIcon;
    call.str = (uint64_t)str;
    call.uFlags = (uint64_t)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawCaptionTempA(struct qemu_syscall *call)
{
    struct qemu_DrawCaptionTempA *c = (struct qemu_DrawCaptionTempA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawCaptionTempA(QEMU_G2H(c->hwnd), QEMU_G2H(c->hdc), QEMU_G2H(c->rect), QEMU_G2H(c->hFont), QEMU_G2H(c->hIcon), QEMU_G2H(c->str), c->uFlags);
}

#endif

struct qemu_DrawCaptionTempW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hdc;
    uint64_t rect;
    uint64_t hFont;
    uint64_t hIcon;
    uint64_t str;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawCaptionTempW (HWND hwnd, HDC hdc, const RECT *rect, HFONT hFont, HICON hIcon, LPCWSTR str, UINT uFlags)
{
    struct qemu_DrawCaptionTempW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWCAPTIONTEMPW);
    call.hwnd = (uint64_t)hwnd;
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;
    call.hFont = (uint64_t)hFont;
    call.hIcon = (uint64_t)hIcon;
    call.str = (uint64_t)str;
    call.uFlags = (uint64_t)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawCaptionTempW(struct qemu_syscall *call)
{
    struct qemu_DrawCaptionTempW *c = (struct qemu_DrawCaptionTempW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawCaptionTempW(QEMU_G2H(c->hwnd), QEMU_G2H(c->hdc), QEMU_G2H(c->rect), QEMU_G2H(c->hFont), QEMU_G2H(c->hIcon), QEMU_G2H(c->str), c->uFlags);
}

#endif

struct qemu_AdjustWindowRect
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t style;
    uint64_t menu;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AdjustWindowRect(LPRECT rect, DWORD style, BOOL menu)
{
    struct qemu_AdjustWindowRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADJUSTWINDOWRECT);
    call.rect = (uint64_t)rect;
    call.style = (uint64_t)style;
    call.menu = (uint64_t)menu;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdjustWindowRect(struct qemu_syscall *call)
{
    struct qemu_AdjustWindowRect *c = (struct qemu_AdjustWindowRect *)call;
    WINE_TRACE("\n");
    c->super.iret = AdjustWindowRect(QEMU_G2H(c->rect), c->style, c->menu);
}

#endif

struct qemu_AdjustWindowRectEx
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t style;
    uint64_t menu;
    uint64_t exStyle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AdjustWindowRectEx(LPRECT rect, DWORD style, BOOL menu, DWORD exStyle)
{
    struct qemu_AdjustWindowRectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADJUSTWINDOWRECTEX);
    call.rect = (uint64_t)rect;
    call.style = (uint64_t)style;
    call.menu = (uint64_t)menu;
    call.exStyle = (uint64_t)exStyle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdjustWindowRectEx(struct qemu_syscall *call)
{
    struct qemu_AdjustWindowRectEx *c = (struct qemu_AdjustWindowRectEx *)call;
    WINE_TRACE("\n");
    c->super.iret = AdjustWindowRectEx(QEMU_G2H(c->rect), c->style, c->menu, c->exStyle);
}

#endif

struct qemu_GetTitleBarInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t tbi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetTitleBarInfo(HWND hwnd, PTITLEBARINFO tbi)
{
    struct qemu_GetTitleBarInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTITLEBARINFO);
    call.hwnd = (uint64_t)hwnd;
    call.tbi = (uint64_t)tbi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTitleBarInfo(struct qemu_syscall *call)
{
    struct qemu_GetTitleBarInfo *c = (struct qemu_GetTitleBarInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTitleBarInfo(QEMU_G2H(c->hwnd), QEMU_G2H(c->tbi));
}

#endif

