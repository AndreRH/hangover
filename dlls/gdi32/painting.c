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
#include "gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_LineTo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LineTo(HDC hdc, INT x, INT y)
{
    struct qemu_LineTo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LINETO);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LineTo(struct qemu_syscall *call)
{
    struct qemu_LineTo *c = (struct qemu_LineTo *)call;
    WINE_TRACE("\n");
    c->super.iret = LineTo(QEMU_G2H(c->hdc), c->x, c->y);
}

#endif

struct qemu_MoveToEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MoveToEx(HDC hdc, INT x, INT y, LPPOINT pt)
{
    struct qemu_MoveToEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MOVETOEX);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.pt = (uint64_t)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MoveToEx(struct qemu_syscall *call)
{
    struct qemu_MoveToEx *c = (struct qemu_MoveToEx *)call;
    WINE_TRACE("\n");
    c->super.iret = MoveToEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->pt));
}

#endif

struct qemu_Arc
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
    uint64_t xstart;
    uint64_t ystart;
    uint64_t xend;
    uint64_t yend;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Arc(HDC hdc, INT left, INT top, INT right, INT bottom, INT xstart, INT ystart, INT xend, INT yend)
{
    struct qemu_Arc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ARC);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;
    call.xstart = (uint64_t)xstart;
    call.ystart = (uint64_t)ystart;
    call.xend = (uint64_t)xend;
    call.yend = (uint64_t)yend;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Arc(struct qemu_syscall *call)
{
    struct qemu_Arc *c = (struct qemu_Arc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Arc(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom, c->xstart, c->ystart, c->xend, c->yend);
}

#endif

struct qemu_ArcTo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
    uint64_t xstart;
    uint64_t ystart;
    uint64_t xend;
    uint64_t yend;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ArcTo(HDC hdc, INT left, INT top, INT right, INT bottom, INT xstart, INT ystart, INT xend, INT yend)
{
    struct qemu_ArcTo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ARCTO);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;
    call.xstart = (uint64_t)xstart;
    call.ystart = (uint64_t)ystart;
    call.xend = (uint64_t)xend;
    call.yend = (uint64_t)yend;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ArcTo(struct qemu_syscall *call)
{
    struct qemu_ArcTo *c = (struct qemu_ArcTo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ArcTo(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom, c->xstart, c->ystart, c->xend, c->yend);
}

#endif

struct qemu_Pie
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
    uint64_t xstart;
    uint64_t ystart;
    uint64_t xend;
    uint64_t yend;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Pie(HDC hdc, INT left, INT top, INT right, INT bottom, INT xstart, INT ystart, INT xend, INT yend)
{
    struct qemu_Pie call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PIE);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;
    call.xstart = (uint64_t)xstart;
    call.ystart = (uint64_t)ystart;
    call.xend = (uint64_t)xend;
    call.yend = (uint64_t)yend;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Pie(struct qemu_syscall *call)
{
    struct qemu_Pie *c = (struct qemu_Pie *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Pie(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom, c->xstart, c->ystart, c->xend, c->yend);
}

#endif

struct qemu_Chord
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
    uint64_t xstart;
    uint64_t ystart;
    uint64_t xend;
    uint64_t yend;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Chord(HDC hdc, INT left, INT top, INT right, INT bottom, INT xstart, INT ystart, INT xend, INT yend)
{
    struct qemu_Chord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHORD);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;
    call.xstart = (uint64_t)xstart;
    call.ystart = (uint64_t)ystart;
    call.xend = (uint64_t)xend;
    call.yend = (uint64_t)yend;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Chord(struct qemu_syscall *call)
{
    struct qemu_Chord *c = (struct qemu_Chord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Chord(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom, c->xstart, c->ystart, c->xend, c->yend);
}

#endif

struct qemu_Ellipse
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Ellipse(HDC hdc, INT left, INT top, INT right, INT bottom)
{
    struct qemu_Ellipse call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ELLIPSE);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Ellipse(struct qemu_syscall *call)
{
    struct qemu_Ellipse *c = (struct qemu_Ellipse *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Ellipse(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_Rectangle
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Rectangle(HDC hdc, INT left, INT top, INT right, INT bottom)
{
    struct qemu_Rectangle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RECTANGLE);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Rectangle(struct qemu_syscall *call)
{
    struct qemu_Rectangle *c = (struct qemu_Rectangle *)call;
    WINE_TRACE("\n");
    c->super.iret = Rectangle(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_RoundRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
    uint64_t ell_width;
    uint64_t ell_height;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RoundRect(HDC hdc, INT left, INT top, INT right, INT bottom, INT ell_width, INT ell_height)
{
    struct qemu_RoundRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ROUNDRECT);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;
    call.ell_width = (uint64_t)ell_width;
    call.ell_height = (uint64_t)ell_height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RoundRect(struct qemu_syscall *call)
{
    struct qemu_RoundRect *c = (struct qemu_RoundRect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RoundRect(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom, c->ell_width, c->ell_height);
}

#endif

struct qemu_SetPixel
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI COLORREF WINAPI SetPixel(HDC hdc, INT x, INT y, COLORREF color)
{
    struct qemu_SetPixel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPIXEL);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.color = (uint64_t)color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPixel(struct qemu_syscall *call)
{
    struct qemu_SetPixel *c = (struct qemu_SetPixel *)call;
    WINE_TRACE("\n");
    c->super.iret = SetPixel(QEMU_G2H(c->hdc), c->x, c->y, c->color);
}

#endif

struct qemu_SetPixelV
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetPixelV(HDC hdc, INT x, INT y, COLORREF color)
{
    struct qemu_SetPixelV call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPIXELV);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.color = (uint64_t)color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPixelV(struct qemu_syscall *call)
{
    struct qemu_SetPixelV *c = (struct qemu_SetPixelV *)call;
    WINE_TRACE("\n");
    c->super.iret = SetPixelV(QEMU_G2H(c->hdc), c->x, c->y, c->color);
}

#endif

struct qemu_GetPixel
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI COLORREF WINAPI GetPixel(HDC hdc, INT x, INT y)
{
    struct qemu_GetPixel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPIXEL);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPixel(struct qemu_syscall *call)
{
    struct qemu_GetPixel *c = (struct qemu_GetPixel *)call;
    WINE_TRACE("\n");
    c->super.iret = GetPixel(QEMU_G2H(c->hdc), c->x, c->y);
}

#endif

struct qemu_GdiSetPixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t descr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GdiSetPixelFormat(HDC hdc, INT format, const PIXELFORMATDESCRIPTOR *descr)
{
    struct qemu_GdiSetPixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDISETPIXELFORMAT);
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.descr = (uint64_t)descr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiSetPixelFormat to Wine headers? */
extern BOOL WINAPI GdiSetPixelFormat(HDC hdc, INT format, const PIXELFORMATDESCRIPTOR *descr);
void qemu_GdiSetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_GdiSetPixelFormat *c = (struct qemu_GdiSetPixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiSetPixelFormat(QEMU_G2H(c->hdc), c->format, QEMU_G2H(c->descr));
}

#endif

struct qemu_GdiDescribePixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t format;
    uint64_t size;
    uint64_t descr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GdiDescribePixelFormat(HDC hdc, INT format, UINT size, PIXELFORMATDESCRIPTOR *descr)
{
    struct qemu_GdiDescribePixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIDESCRIBEPIXELFORMAT);
    call.hdc = (uint64_t)hdc;
    call.format = (uint64_t)format;
    call.size = (uint64_t)size;
    call.descr = (uint64_t)descr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiDescribePixelFormat to Wine headers? */
extern INT WINAPI GdiDescribePixelFormat(HDC hdc, INT format, UINT size, PIXELFORMATDESCRIPTOR *descr);
void qemu_GdiDescribePixelFormat(struct qemu_syscall *call)
{
    struct qemu_GdiDescribePixelFormat *c = (struct qemu_GdiDescribePixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiDescribePixelFormat(QEMU_G2H(c->hdc), c->format, c->size, QEMU_G2H(c->descr));
}

#endif

struct qemu_GdiSwapBuffers
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GdiSwapBuffers(HDC hdc)
{
    struct qemu_GdiSwapBuffers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDISWAPBUFFERS);
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiSwapBuffers to Wine headers? */
extern BOOL WINAPI GdiSwapBuffers(HDC hdc);
void qemu_GdiSwapBuffers(struct qemu_syscall *call)
{
    struct qemu_GdiSwapBuffers *c = (struct qemu_GdiSwapBuffers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiSwapBuffers(QEMU_G2H(c->hdc));
}

#endif

struct qemu_PaintRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hrgn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PaintRgn(HDC hdc, HRGN hrgn)
{
    struct qemu_PaintRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PAINTRGN);
    call.hdc = (uint64_t)hdc;
    call.hrgn = (uint64_t)hrgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PaintRgn(struct qemu_syscall *call)
{
    struct qemu_PaintRgn *c = (struct qemu_PaintRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = PaintRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hrgn));
}

#endif

struct qemu_FillRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hrgn;
    uint64_t hbrush;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FillRgn(HDC hdc, HRGN hrgn, HBRUSH hbrush)
{
    struct qemu_FillRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILLRGN);
    call.hdc = (uint64_t)hdc;
    call.hrgn = (uint64_t)hrgn;
    call.hbrush = (uint64_t)hbrush;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FillRgn(struct qemu_syscall *call)
{
    struct qemu_FillRgn *c = (struct qemu_FillRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FillRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hrgn), QEMU_G2H(c->hbrush));
}

#endif

struct qemu_FrameRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hrgn;
    uint64_t hbrush;
    uint64_t nWidth;
    uint64_t nHeight;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FrameRgn(HDC hdc, HRGN hrgn, HBRUSH hbrush, INT nWidth, INT nHeight)
{
    struct qemu_FrameRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FRAMERGN);
    call.hdc = (uint64_t)hdc;
    call.hrgn = (uint64_t)hrgn;
    call.hbrush = (uint64_t)hbrush;
    call.nWidth = (uint64_t)nWidth;
    call.nHeight = (uint64_t)nHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FrameRgn(struct qemu_syscall *call)
{
    struct qemu_FrameRgn *c = (struct qemu_FrameRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FrameRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hrgn), QEMU_G2H(c->hbrush), c->nWidth, c->nHeight);
}

#endif

struct qemu_InvertRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hrgn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InvertRgn(HDC hdc, HRGN hrgn)
{
    struct qemu_InvertRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INVERTRGN);
    call.hdc = (uint64_t)hdc;
    call.hrgn = (uint64_t)hrgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InvertRgn(struct qemu_syscall *call)
{
    struct qemu_InvertRgn *c = (struct qemu_InvertRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InvertRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hrgn));
}

#endif

struct qemu_Polyline
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Polyline(HDC hdc, const POINT* pt, INT count)
{
    struct qemu_Polyline call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYLINE);
    call.hdc = (uint64_t)hdc;
    call.pt = (uint64_t)pt;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Polyline(struct qemu_syscall *call)
{
    struct qemu_Polyline *c = (struct qemu_Polyline *)call;
    WINE_TRACE("\n");
    c->super.iret = Polyline(QEMU_G2H(c->hdc), QEMU_G2H(c->pt), c->count);
}

#endif

struct qemu_PolylineTo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
    uint64_t cCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PolylineTo(HDC hdc, const POINT* pt, DWORD cCount)
{
    struct qemu_PolylineTo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYLINETO);
    call.hdc = (uint64_t)hdc;
    call.pt = (uint64_t)pt;
    call.cCount = (uint64_t)cCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolylineTo(struct qemu_syscall *call)
{
    struct qemu_PolylineTo *c = (struct qemu_PolylineTo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolylineTo(QEMU_G2H(c->hdc), QEMU_G2H(c->pt), c->cCount);
}

#endif

struct qemu_Polygon
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Polygon(HDC hdc, const POINT* pt, INT count)
{
    struct qemu_Polygon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYGON);
    call.hdc = (uint64_t)hdc;
    call.pt = (uint64_t)pt;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Polygon(struct qemu_syscall *call)
{
    struct qemu_Polygon *c = (struct qemu_Polygon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Polygon(QEMU_G2H(c->hdc), QEMU_G2H(c->pt), c->count);
}

#endif

struct qemu_PolyPolygon
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
    uint64_t counts;
    uint64_t polygons;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PolyPolygon(HDC hdc, const POINT* pt, const INT* counts, int polygons)
{
    struct qemu_PolyPolygon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYPOLYGON);
    call.hdc = (uint64_t)hdc;
    call.pt = (uint64_t)pt;
    call.counts = (uint64_t)counts;
    call.polygons = polygons;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyPolygon(struct qemu_syscall *call)
{
    struct qemu_PolyPolygon *c = (struct qemu_PolyPolygon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolyPolygon((HDC)c->hdc, QEMU_G2H(c->pt), QEMU_G2H(c->counts), c->polygons);
}

#endif

struct qemu_PolyPolyline
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
    uint64_t counts;
    uint64_t polylines;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PolyPolyline(HDC hdc, const POINT* pt, const DWORD* counts, DWORD polylines)
{
    struct qemu_PolyPolyline call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYPOLYLINE);
    call.hdc = (uint64_t)hdc;
    call.pt = (uint64_t)pt;
    call.counts = (uint64_t)counts;
    call.polylines = (uint64_t)polylines;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyPolyline(struct qemu_syscall *call)
{
    struct qemu_PolyPolyline *c = (struct qemu_PolyPolyline *)call;
    WINE_TRACE("\n");
    c->super.iret = PolyPolyline(QEMU_G2H(c->hdc), QEMU_G2H(c->pt), QEMU_G2H(c->counts), c->polylines);
}

#endif

struct qemu_ExtFloodFill
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t color;
    uint64_t fillType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ExtFloodFill(HDC hdc, INT x, INT y, COLORREF color, UINT fillType)
{
    struct qemu_ExtFloodFill call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTFLOODFILL);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.color = (uint64_t)color;
    call.fillType = (uint64_t)fillType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtFloodFill(struct qemu_syscall *call)
{
    struct qemu_ExtFloodFill *c = (struct qemu_ExtFloodFill *)call;
    WINE_TRACE("\n");
    c->super.iret = ExtFloodFill(QEMU_G2H(c->hdc), c->x, c->y, c->color, c->fillType);
}

#endif

struct qemu_FloodFill
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FloodFill(HDC hdc, INT x, INT y, COLORREF color)
{
    struct qemu_FloodFill call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLOODFILL);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.color = (uint64_t)color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FloodFill(struct qemu_syscall *call)
{
    struct qemu_FloodFill *c = (struct qemu_FloodFill *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FloodFill(QEMU_G2H(c->hdc), c->x, c->y, c->color);
}

#endif

struct qemu_PolyBezier
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lppt;
    uint64_t cPoints;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PolyBezier(HDC hdc, const POINT* lppt, DWORD cPoints)
{
    struct qemu_PolyBezier call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYBEZIER);
    call.hdc = (uint64_t)hdc;
    call.lppt = (uint64_t)lppt;
    call.cPoints = (uint64_t)cPoints;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyBezier(struct qemu_syscall *call)
{
    struct qemu_PolyBezier *c = (struct qemu_PolyBezier *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolyBezier(QEMU_G2H(c->hdc), QEMU_G2H(c->lppt), c->cPoints);
}

#endif

struct qemu_PolyBezierTo
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lppt;
    uint64_t cPoints;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PolyBezierTo(HDC hdc, const POINT* lppt, DWORD cPoints)
{
    struct qemu_PolyBezierTo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYBEZIERTO);
    call.hdc = (uint64_t)hdc;
    call.lppt = (uint64_t)lppt;
    call.cPoints = (uint64_t)cPoints;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyBezierTo(struct qemu_syscall *call)
{
    struct qemu_PolyBezierTo *c = (struct qemu_PolyBezierTo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolyBezierTo(QEMU_G2H(c->hdc), QEMU_G2H(c->lppt), c->cPoints);
}

#endif

struct qemu_AngleArc
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t dwRadius;
    double eStartAngle;
    double eSweepAngle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AngleArc(HDC hdc, INT x, INT y, DWORD dwRadius, FLOAT eStartAngle, FLOAT eSweepAngle)
{
    struct qemu_AngleArc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ANGLEARC);
    call.hdc = (uint64_t)hdc;
    call.x = x;
    call.y = y;
    call.dwRadius = dwRadius;
    call.eStartAngle = eStartAngle;
    call.eSweepAngle = eSweepAngle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AngleArc(struct qemu_syscall *call)
{
    struct qemu_AngleArc *c = (struct qemu_AngleArc *)call;
    WINE_TRACE("\n");
    c->super.iret = AngleArc((HDC)c->hdc, c->x, c->y, c->dwRadius, c->eStartAngle, c->eSweepAngle);
}

#endif

struct qemu_PolyDraw
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lppt;
    uint64_t lpbTypes;
    uint64_t cCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PolyDraw(HDC hdc, const POINT *lppt, const BYTE *lpbTypes, int cCount)
{
    struct qemu_PolyDraw call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POLYDRAW);
    call.hdc = (uint64_t)hdc;
    call.lppt = (uint64_t)lppt;
    call.lpbTypes = (uint64_t)lpbTypes;
    call.cCount = (uint64_t)cCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PolyDraw(struct qemu_syscall *call)
{
    struct qemu_PolyDraw *c = (struct qemu_PolyDraw *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PolyDraw((HDC)c->hdc, QEMU_G2H(c->lppt), QEMU_G2H(c->lpbTypes), c->cCount);
}

#endif

struct qemu_LineDDA
{
    struct qemu_syscall super;
    uint64_t nXStart;
    uint64_t nYStart;
    uint64_t nXEnd;
    uint64_t nYEnd;
    uint64_t callback;
    uint64_t lParam;
    uint64_t wrapper;
};

struct qemu_LineDDA_cb
{
    uint64_t proc;
    uint64_t x, y;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t LineDDA_guest_cb(struct qemu_LineDDA_cb *data)
{
    LINEDDAPROC proc = (LINEDDAPROC)data->proc;
    proc(data->x, data->y, data->param);
}

WINBASEAPI BOOL WINAPI LineDDA(INT nXStart, INT nYStart, INT nXEnd, INT nYEnd, LINEDDAPROC callback, LPARAM lParam)
{
    struct qemu_LineDDA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LINEDDA);
    call.nXStart = nXStart;
    call.nYStart = nYStart;
    call.nXEnd = nXEnd;
    call.nYEnd = nYEnd;
    call.callback = (uint64_t)callback;
    call.lParam = lParam;
    call.wrapper = (uint64_t)LineDDA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_LineDDA_host_data
{
    uint64_t wrapper, guest_func;
    uint64_t guest_data;
};

static void WINAPI qemu_LineDDA_host_proc(INT x, INT y, LPARAM param)
{
    struct qemu_LineDDA_host_data *data = (struct qemu_LineDDA_host_data *)param;
    struct qemu_LineDDA_cb call;

    WINE_TRACE("Calling guest callback 0x%lx(%d, %d 0x%lx).\n", data->guest_func, x, y, data->guest_data);
    call.proc = data->guest_func;
    call.x = x;
    call.y = y;
    call.param = data->guest_data;

    qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned.\n");
}

void qemu_LineDDA(struct qemu_syscall *call)
{
    struct qemu_LineDDA *c = (struct qemu_LineDDA *)call;
    struct qemu_LineDDA_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->callback;
    data.guest_data = c->lParam;

    c->super.iret = LineDDA(c->nXStart, c->nYStart, c->nXEnd, c->nYEnd,
            c->callback ? qemu_LineDDA_host_proc : NULL, (LPARAM)&data);
}

#endif

struct qemu_GdiGradientFill
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t vert_array;
    uint64_t nvert;
    uint64_t grad_array;
    uint64_t ngrad;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GdiGradientFill(HDC hdc, TRIVERTEX *vert_array, ULONG nvert, void *grad_array, ULONG ngrad, ULONG mode)
{
    struct qemu_GdiGradientFill call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIGRADIENTFILL);
    call.hdc = (uint64_t)hdc;
    call.vert_array = (uint64_t)vert_array;
    call.nvert = (uint64_t)nvert;
    call.grad_array = (uint64_t)grad_array;
    call.ngrad = (uint64_t)ngrad;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiGradientFill(struct qemu_syscall *call)
{
    struct qemu_GdiGradientFill *c = (struct qemu_GdiGradientFill *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiGradientFill(QEMU_G2H(c->hdc), QEMU_G2H(c->vert_array), c->nvert, QEMU_G2H(c->grad_array), c->ngrad, c->mode);
}

#endif

struct qemu_GdiDrawStream
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t in;
    uint64_t pvin;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GdiDrawStream(HDC hdc, ULONG in, void * pvin)
{
    struct qemu_GdiDrawStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIDRAWSTREAM);
    call.hdc = (uint64_t)hdc;
    call.in = (uint64_t)in;
    call.pvin = (uint64_t)pvin;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiDrawStream to Wine headers? */
extern BOOL WINAPI GdiDrawStream(HDC hdc, ULONG in, void * pvin);
void qemu_GdiDrawStream(struct qemu_syscall *call)
{
    struct qemu_GdiDrawStream *c = (struct qemu_GdiDrawStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiDrawStream(QEMU_G2H(c->hdc), c->in, QEMU_G2H(c->pvin));
}

#endif

