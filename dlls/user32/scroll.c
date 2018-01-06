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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_SetScrollInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t info;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI SetScrollInfo(HWND hwnd, INT nBar, const SCROLLINFO *info, BOOL bRedraw)
{
    struct qemu_SetScrollInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSCROLLINFO);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.info = (ULONG_PTR)info;
    call.bRedraw = (ULONG_PTR)bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetScrollInfo(struct qemu_syscall *call)
{
    struct qemu_SetScrollInfo *c = (struct qemu_SetScrollInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = SetScrollInfo(QEMU_G2H(c->hwnd), c->nBar, QEMU_G2H(c->info), c->bRedraw);
}

#endif

struct qemu_GetScrollInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetScrollInfo(HWND hwnd, INT nBar, LPSCROLLINFO info)
{
    struct qemu_GetScrollInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSCROLLINFO);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetScrollInfo(struct qemu_syscall *call)
{
    struct qemu_GetScrollInfo *c = (struct qemu_GetScrollInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetScrollInfo(QEMU_G2H(c->hwnd), c->nBar, QEMU_G2H(c->info));
}

#endif

struct qemu_GetScrollBarInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t idObject;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetScrollBarInfo(HWND hwnd, LONG idObject, LPSCROLLBARINFO info)
{
    struct qemu_GetScrollBarInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSCROLLBARINFO);
    call.hwnd = (LONG_PTR)hwnd;
    call.idObject = (ULONG_PTR)idObject;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetScrollBarInfo(struct qemu_syscall *call)
{
    struct qemu_GetScrollBarInfo *c = (struct qemu_GetScrollBarInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetScrollBarInfo(QEMU_G2H(c->hwnd), c->idObject, QEMU_G2H(c->info));
}

#endif

struct qemu_SetScrollPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t nPos;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI SetScrollPos(HWND hwnd, INT nBar, INT nPos, BOOL bRedraw)
{
    struct qemu_SetScrollPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSCROLLPOS);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.nPos = (ULONG_PTR)nPos;
    call.bRedraw = (ULONG_PTR)bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetScrollPos(struct qemu_syscall *call)
{
    struct qemu_SetScrollPos *c = (struct qemu_SetScrollPos *)call;
    WINE_TRACE("\n");
    c->super.iret = SetScrollPos(QEMU_G2H(c->hwnd), c->nBar, c->nPos, c->bRedraw);
}

#endif

struct qemu_GetScrollPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetScrollPos(HWND hwnd, INT nBar)
{
    struct qemu_GetScrollPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSCROLLPOS);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetScrollPos(struct qemu_syscall *call)
{
    struct qemu_GetScrollPos *c = (struct qemu_GetScrollPos *)call;
    WINE_TRACE("\n");
    c->super.iret = GetScrollPos(QEMU_G2H(c->hwnd), c->nBar);
}

#endif

struct qemu_SetScrollRange
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t minVal;
    uint64_t maxVal;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetScrollRange(HWND hwnd, INT nBar, INT minVal, INT maxVal, BOOL bRedraw)
{
    struct qemu_SetScrollRange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSCROLLRANGE);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.minVal = (ULONG_PTR)minVal;
    call.maxVal = (ULONG_PTR)maxVal;
    call.bRedraw = (ULONG_PTR)bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetScrollRange(struct qemu_syscall *call)
{
    struct qemu_SetScrollRange *c = (struct qemu_SetScrollRange *)call;
    WINE_TRACE("\n");
    c->super.iret = SetScrollRange(QEMU_G2H(c->hwnd), c->nBar, c->minVal, c->maxVal, c->bRedraw);
}

#endif

struct qemu_GetScrollRange
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t lpMin;
    uint64_t lpMax;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetScrollRange(HWND hwnd, INT nBar, LPINT lpMin, LPINT lpMax)
{
    struct qemu_GetScrollRange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSCROLLRANGE);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.lpMin = (ULONG_PTR)lpMin;
    call.lpMax = (ULONG_PTR)lpMax;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetScrollRange(struct qemu_syscall *call)
{
    struct qemu_GetScrollRange *c = (struct qemu_GetScrollRange *)call;
    WINE_TRACE("\n");
    c->super.iret = GetScrollRange(QEMU_G2H(c->hwnd), c->nBar, QEMU_G2H(c->lpMin), QEMU_G2H(c->lpMax));
}

#endif

struct qemu_ShowScrollBar
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t fShow;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShowScrollBar(HWND hwnd, INT nBar, BOOL fShow)
{
    struct qemu_ShowScrollBar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWSCROLLBAR);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.fShow = (ULONG_PTR)fShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShowScrollBar(struct qemu_syscall *call)
{
    struct qemu_ShowScrollBar *c = (struct qemu_ShowScrollBar *)call;
    WINE_TRACE("\n");
    c->super.iret = ShowScrollBar(QEMU_G2H(c->hwnd), c->nBar, c->fShow);
}

#endif

struct qemu_EnableScrollBar
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnableScrollBar(HWND hwnd, UINT nBar, UINT flags)
{
    struct qemu_EnableScrollBar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLESCROLLBAR);
    call.hwnd = (LONG_PTR)hwnd;
    call.nBar = (ULONG_PTR)nBar;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableScrollBar(struct qemu_syscall *call)
{
    struct qemu_EnableScrollBar *c = (struct qemu_EnableScrollBar *)call;
    WINE_TRACE("\n");
    c->super.iret = EnableScrollBar(QEMU_G2H(c->hwnd), c->nBar, c->flags);
}

#endif

