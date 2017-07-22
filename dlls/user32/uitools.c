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


struct qemu_DrawEdge
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rc;
    uint64_t edge;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawEdge(HDC hdc, LPRECT rc, UINT edge, UINT flags)
{
    struct qemu_DrawEdge call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWEDGE);
    call.hdc = (uint64_t)hdc;
    call.rc = (uint64_t)rc;
    call.edge = (uint64_t)edge;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawEdge(struct qemu_syscall *call)
{
    struct qemu_DrawEdge *c = (struct qemu_DrawEdge *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawEdge(QEMU_G2H(c->hdc), QEMU_G2H(c->rc), c->edge, c->flags);
}

#endif

struct qemu_DrawFrameControl
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rc;
    uint64_t uType;
    uint64_t uState;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawFrameControl(HDC hdc, LPRECT rc, UINT uType, UINT uState)
{
    struct qemu_DrawFrameControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWFRAMECONTROL);
    call.hdc = (uint64_t)hdc;
    call.rc = (uint64_t)rc;
    call.uType = (uint64_t)uType;
    call.uState = (uint64_t)uState;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawFrameControl(struct qemu_syscall *call)
{
    struct qemu_DrawFrameControl *c = (struct qemu_DrawFrameControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawFrameControl(QEMU_G2H(c->hdc), QEMU_G2H(c->rc), c->uType, c->uState);
}

#endif

struct qemu_SetRect
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetRect(LPRECT rect, INT left, INT top, INT right, INT bottom)
{
    struct qemu_SetRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETRECT);
    call.rect = (uint64_t)rect;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetRect(struct qemu_syscall *call)
{
    struct qemu_SetRect *c = (struct qemu_SetRect *)call;
    WINE_TRACE("\n");
    c->super.iret = SetRect(QEMU_G2H(c->rect), c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_SetRectEmpty
{
    struct qemu_syscall super;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetRectEmpty(LPRECT rect)
{
    struct qemu_SetRectEmpty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETRECTEMPTY);
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetRectEmpty(struct qemu_syscall *call)
{
    struct qemu_SetRectEmpty *c = (struct qemu_SetRectEmpty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetRectEmpty(QEMU_G2H(c->rect));
}

#endif

struct qemu_CopyRect
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CopyRect(RECT *dest, const RECT *src)
{
    struct qemu_CopyRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYRECT);
    call.dest = (uint64_t)dest;
    call.src = (uint64_t)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CopyRect(struct qemu_syscall *call)
{
    struct qemu_CopyRect *c = (struct qemu_CopyRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CopyRect(QEMU_G2H(c->dest), QEMU_G2H(c->src));
}

#endif

struct qemu_IsRectEmpty
{
    struct qemu_syscall super;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsRectEmpty(const RECT *rect)
{
    struct qemu_IsRectEmpty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISRECTEMPTY);
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsRectEmpty(struct qemu_syscall *call)
{
    struct qemu_IsRectEmpty *c = (struct qemu_IsRectEmpty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsRectEmpty(QEMU_G2H(c->rect));
}

#endif

struct qemu_OffsetRect
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI OffsetRect(LPRECT rect, INT x, INT y)
{
    struct qemu_OffsetRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OFFSETRECT);
    call.rect = (uint64_t)rect;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OffsetRect(struct qemu_syscall *call)
{
    struct qemu_OffsetRect *c = (struct qemu_OffsetRect *)call;
    WINE_TRACE("\n");
    c->super.iret = OffsetRect(QEMU_G2H(c->rect), c->x, c->y);
}

#endif

struct qemu_PtInRect
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t ptx;
    uint64_t pty;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PtInRect(const RECT *rect, POINT pt)
{
    struct qemu_PtInRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PTINRECT);
    call.rect = (uint64_t)rect;
    call.ptx = pt.x;
    call.pty = pt.y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PtInRect(struct qemu_syscall *call)
{
    struct qemu_PtInRect *c = (struct qemu_PtInRect *)call;
    POINT pt;
    WINE_FIXME("Unverified!\n");
    pt.x = c->ptx;
    pt.y = c->pty;
    c->super.iret = PtInRect(QEMU_G2H(c->rect), pt);
}

#endif

struct qemu_InflateRect
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InflateRect(LPRECT rect, INT x, INT y)
{
    struct qemu_InflateRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INFLATERECT);
    call.rect = (uint64_t)rect;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InflateRect(struct qemu_syscall *call)
{
    struct qemu_InflateRect *c = (struct qemu_InflateRect *)call;
    WINE_TRACE("\n");
    c->super.iret = InflateRect(QEMU_G2H(c->rect), c->x, c->y);
}

#endif

struct qemu_IntersectRect
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src1;
    uint64_t src2;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IntersectRect(LPRECT dest, const RECT *src1, const RECT *src2)
{
    struct qemu_IntersectRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERSECTRECT);
    call.dest = (uint64_t)dest;
    call.src1 = (uint64_t)src1;
    call.src2 = (uint64_t)src2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IntersectRect(struct qemu_syscall *call)
{
    struct qemu_IntersectRect *c = (struct qemu_IntersectRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IntersectRect(QEMU_G2H(c->dest), QEMU_G2H(c->src1), QEMU_G2H(c->src2));
}

#endif

struct qemu_UnionRect
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src1;
    uint64_t src2;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnionRect(LPRECT dest, const RECT *src1, const RECT *src2)
{
    struct qemu_UnionRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNIONRECT);
    call.dest = (uint64_t)dest;
    call.src1 = (uint64_t)src1;
    call.src2 = (uint64_t)src2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnionRect(struct qemu_syscall *call)
{
    struct qemu_UnionRect *c = (struct qemu_UnionRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnionRect(QEMU_G2H(c->dest), QEMU_G2H(c->src1), QEMU_G2H(c->src2));
}

#endif

struct qemu_EqualRect
{
    struct qemu_syscall super;
    uint64_t rect1;
    uint64_t rect2;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EqualRect(const RECT* rect1, const RECT* rect2)
{
    struct qemu_EqualRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EQUALRECT);
    call.rect1 = (uint64_t)rect1;
    call.rect2 = (uint64_t)rect2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EqualRect(struct qemu_syscall *call)
{
    struct qemu_EqualRect *c = (struct qemu_EqualRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EqualRect(QEMU_G2H(c->rect1), QEMU_G2H(c->rect2));
}

#endif

struct qemu_SubtractRect
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src1;
    uint64_t src2;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SubtractRect(LPRECT dest, const RECT *src1, const RECT *src2)
{
    struct qemu_SubtractRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SUBTRACTRECT);
    call.dest = (uint64_t)dest;
    call.src1 = (uint64_t)src1;
    call.src2 = (uint64_t)src2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SubtractRect(struct qemu_syscall *call)
{
    struct qemu_SubtractRect *c = (struct qemu_SubtractRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SubtractRect(QEMU_G2H(c->dest), QEMU_G2H(c->src1), QEMU_G2H(c->src2));
}

#endif

struct qemu_FillRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
    uint64_t hbrush;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI FillRect(HDC hdc, const RECT *rect, HBRUSH hbrush)
{
    struct qemu_FillRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILLRECT);
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;
    call.hbrush = (uint64_t)hbrush;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FillRect(struct qemu_syscall *call)
{
    struct qemu_FillRect *c = (struct qemu_FillRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FillRect(QEMU_G2H(c->hdc), QEMU_G2H(c->rect), QEMU_G2H(c->hbrush));
}

#endif

struct qemu_InvertRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI InvertRect(HDC hdc, const RECT *rect)
{
    struct qemu_InvertRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INVERTRECT);
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InvertRect(struct qemu_syscall *call)
{
    struct qemu_InvertRect *c = (struct qemu_InvertRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InvertRect(QEMU_G2H(c->hdc), QEMU_G2H(c->rect));
}

#endif

struct qemu_FrameRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
    uint64_t hbrush;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI FrameRect(HDC hdc, const RECT *rect, HBRUSH hbrush)
{
    struct qemu_FrameRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FRAMERECT);
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;
    call.hbrush = (uint64_t)hbrush;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FrameRect(struct qemu_syscall *call)
{
    struct qemu_FrameRect *c = (struct qemu_FrameRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FrameRect(QEMU_G2H(c->hdc), QEMU_G2H(c->rect), QEMU_G2H(c->hbrush));
}

#endif

struct qemu_DrawFocusRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawFocusRect(HDC hdc, const RECT* rc)
{
    struct qemu_DrawFocusRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWFOCUSRECT);
    call.hdc = (uint64_t)hdc;
    call.rc = (uint64_t)rc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawFocusRect(struct qemu_syscall *call)
{
    struct qemu_DrawFocusRect *c = (struct qemu_DrawFocusRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawFocusRect(QEMU_G2H(c->hdc), QEMU_G2H(c->rc));
}

#endif

struct qemu_DrawAnimatedRects
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t idAni;
    uint64_t lprcFrom;
    uint64_t lprcTo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawAnimatedRects(HWND hwnd, INT idAni, const RECT* lprcFrom, const RECT* lprcTo)
{
    struct qemu_DrawAnimatedRects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWANIMATEDRECTS);
    call.hwnd = (uint64_t)hwnd;
    call.idAni = (uint64_t)idAni;
    call.lprcFrom = (uint64_t)lprcFrom;
    call.lprcTo = (uint64_t)lprcTo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawAnimatedRects(struct qemu_syscall *call)
{
    struct qemu_DrawAnimatedRects *c = (struct qemu_DrawAnimatedRects *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawAnimatedRects(QEMU_G2H(c->hwnd), c->idAni, QEMU_G2H(c->lprcFrom), QEMU_G2H(c->lprcTo));
}

#endif

struct qemu_DrawStateA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hbr;
    uint64_t func;
    uint64_t ldata;
    uint64_t wdata;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawStateA(HDC hdc, HBRUSH hbr, DRAWSTATEPROC func, LPARAM ldata, WPARAM wdata, INT x, INT y, INT cx, INT cy, UINT flags)
{
    struct qemu_DrawStateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWSTATEA);
    call.hdc = (uint64_t)hdc;
    call.hbr = (uint64_t)hbr;
    call.func = (uint64_t)func;
    call.ldata = (uint64_t)ldata;
    call.wdata = (uint64_t)wdata;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawStateA(struct qemu_syscall *call)
{
    struct qemu_DrawStateA *c = (struct qemu_DrawStateA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawStateA(QEMU_G2H(c->hdc), QEMU_G2H(c->hbr), QEMU_G2H(c->func), c->ldata, c->wdata, c->x, c->y, c->cx, c->cy, c->flags);
}

#endif

struct qemu_DrawStateW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hbr;
    uint64_t func;
    uint64_t ldata;
    uint64_t wdata;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DrawStateW(HDC hdc, HBRUSH hbr, DRAWSTATEPROC func, LPARAM ldata, WPARAM wdata, INT x, INT y, INT cx, INT cy, UINT flags)
{
    struct qemu_DrawStateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWSTATEW);
    call.hdc = (uint64_t)hdc;
    call.hbr = (uint64_t)hbr;
    call.func = (uint64_t)func;
    call.ldata = (uint64_t)ldata;
    call.wdata = (uint64_t)wdata;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawStateW(struct qemu_syscall *call)
{
    struct qemu_DrawStateW *c = (struct qemu_DrawStateW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawStateW(QEMU_G2H(c->hdc), QEMU_G2H(c->hbr), QEMU_G2H(c->func), c->ldata, c->wdata, c->x, c->y, c->cx, c->cy, c->flags);
}

#endif

