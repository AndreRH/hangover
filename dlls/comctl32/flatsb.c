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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif


struct qemu_InitializeFlatSB
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitializeFlatSB(HWND hwnd)
{
    struct qemu_InitializeFlatSB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZEFLATSB);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeFlatSB(struct qemu_syscall *call)
{
    struct qemu_InitializeFlatSB *c = (struct qemu_InitializeFlatSB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_InitializeFlatSB(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_UninitializeFlatSB
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UninitializeFlatSB(HWND hwnd)
{
    struct qemu_UninitializeFlatSB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNINITIALIZEFLATSB);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UninitializeFlatSB(struct qemu_syscall *call)
{
    struct qemu_UninitializeFlatSB *c = (struct qemu_UninitializeFlatSB *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_UninitializeFlatSB(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_FlatSB_GetScrollProp
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t propIndex;
    uint64_t prop;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlatSB_GetScrollProp(HWND hwnd, INT propIndex, LPINT prop)
{
    struct qemu_FlatSB_GetScrollProp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_GETSCROLLPROP);
    call.hwnd = (ULONG_PTR)hwnd;
    call.propIndex = propIndex;
    call.prop = (ULONG_PTR)prop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_GetScrollProp(struct qemu_syscall *call)
{
    struct qemu_FlatSB_GetScrollProp *c = (struct qemu_FlatSB_GetScrollProp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_GetScrollProp(QEMU_G2H(c->hwnd), c->propIndex, QEMU_G2H(c->prop));
}

#endif

struct qemu_FlatSB_SetScrollProp
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t index;
    uint64_t newValue;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI FlatSB_SetScrollProp(HWND hwnd, UINT index, INT_PTR newValue, WINBOOL flag)
{
    struct qemu_FlatSB_SetScrollProp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_SETSCROLLPROP);
    call.hwnd = (ULONG_PTR)hwnd;
    call.index = index;
    call.newValue = newValue;
    call.flag = flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_SetScrollProp(struct qemu_syscall *call)
{
    struct qemu_FlatSB_SetScrollProp *c = (struct qemu_FlatSB_SetScrollProp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_SetScrollProp(QEMU_G2H(c->hwnd), c->index, c->newValue, c->flag);
}

#endif

struct qemu_FlatSB_EnableScrollBar
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlatSB_EnableScrollBar(HWND hwnd, int nBar, UINT flags)
{
    struct qemu_FlatSB_EnableScrollBar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_ENABLESCROLLBAR);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_EnableScrollBar(struct qemu_syscall *call)
{
    struct qemu_FlatSB_EnableScrollBar *c = (struct qemu_FlatSB_EnableScrollBar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_EnableScrollBar(QEMU_G2H(c->hwnd), c->nBar, c->flags);
}

#endif

struct qemu_FlatSB_ShowScrollBar
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t fShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlatSB_ShowScrollBar(HWND hwnd, int nBar, BOOL fShow)
{
    struct qemu_FlatSB_ShowScrollBar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_SHOWSCROLLBAR);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.fShow = fShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_ShowScrollBar(struct qemu_syscall *call)
{
    struct qemu_FlatSB_ShowScrollBar *c = (struct qemu_FlatSB_ShowScrollBar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_ShowScrollBar(QEMU_G2H(c->hwnd), c->nBar, c->fShow);
}

#endif

struct qemu_FlatSB_GetScrollRange
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t min;
    uint64_t max;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlatSB_GetScrollRange(HWND hwnd, int nBar, LPINT min, LPINT max)
{
    struct qemu_FlatSB_GetScrollRange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_GETSCROLLRANGE);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.min = (ULONG_PTR)min;
    call.max = (ULONG_PTR)max;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_GetScrollRange(struct qemu_syscall *call)
{
    struct qemu_FlatSB_GetScrollRange *c = (struct qemu_FlatSB_GetScrollRange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_GetScrollRange(QEMU_G2H(c->hwnd), c->nBar, QEMU_G2H(c->min), QEMU_G2H(c->max));
}

#endif

struct qemu_FlatSB_GetScrollInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlatSB_GetScrollInfo(HWND hwnd, int nBar, LPSCROLLINFO info)
{
    struct qemu_FlatSB_GetScrollInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_GETSCROLLINFO);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_GetScrollInfo(struct qemu_syscall *call)
{
    struct qemu_FlatSB_GetScrollInfo *c = (struct qemu_FlatSB_GetScrollInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_GetScrollInfo(QEMU_G2H(c->hwnd), c->nBar, QEMU_G2H(c->info));
}

#endif

struct qemu_FlatSB_GetScrollPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FlatSB_GetScrollPos(HWND hwnd, int nBar)
{
    struct qemu_FlatSB_GetScrollPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_GETSCROLLPOS);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_GetScrollPos(struct qemu_syscall *call)
{
    struct qemu_FlatSB_GetScrollPos *c = (struct qemu_FlatSB_GetScrollPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_GetScrollPos(QEMU_G2H(c->hwnd), c->nBar);
}

#endif

struct qemu_FlatSB_SetScrollPos
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t pos;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FlatSB_SetScrollPos(HWND hwnd, int nBar, INT pos, BOOL bRedraw)
{
    struct qemu_FlatSB_SetScrollPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_SETSCROLLPOS);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.pos = pos;
    call.bRedraw = bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_SetScrollPos(struct qemu_syscall *call)
{
    struct qemu_FlatSB_SetScrollPos *c = (struct qemu_FlatSB_SetScrollPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_SetScrollPos(QEMU_G2H(c->hwnd), c->nBar, c->pos, c->bRedraw);
}

#endif

struct qemu_FlatSB_SetScrollInfo
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t info;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FlatSB_SetScrollInfo(HWND hwnd, int nBar, LPSCROLLINFO info, BOOL bRedraw)
{
    struct qemu_FlatSB_SetScrollInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_SETSCROLLINFO);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.info = (ULONG_PTR)info;
    call.bRedraw = bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_SetScrollInfo(struct qemu_syscall *call)
{
    struct qemu_FlatSB_SetScrollInfo *c = (struct qemu_FlatSB_SetScrollInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_SetScrollInfo(QEMU_G2H(c->hwnd), c->nBar, QEMU_G2H(c->info), c->bRedraw);
}

#endif

struct qemu_FlatSB_SetScrollRange
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t nBar;
    uint64_t min;
    uint64_t max;
    uint64_t bRedraw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI FlatSB_SetScrollRange(HWND hwnd, int nBar, INT min, INT max, BOOL bRedraw)
{
    struct qemu_FlatSB_SetScrollRange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATSB_SETSCROLLRANGE);
    call.hwnd = (ULONG_PTR)hwnd;
    call.nBar = nBar;
    call.min = min;
    call.max = max;
    call.bRedraw = bRedraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlatSB_SetScrollRange(struct qemu_syscall *call)
{
    struct qemu_FlatSB_SetScrollRange *c = (struct qemu_FlatSB_SetScrollRange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_FlatSB_SetScrollRange(QEMU_G2H(c->hwnd), c->nBar, c->min, c->max, c->bRedraw);
}

#endif

