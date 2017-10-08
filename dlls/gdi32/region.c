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


struct qemu_OffsetRgn
{
    struct qemu_syscall super;
    uint64_t hrgn;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI OffsetRgn(HRGN hrgn, INT x, INT y)
{
    struct qemu_OffsetRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OFFSETRGN);
    call.hrgn = (ULONG_PTR)hrgn;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OffsetRgn(struct qemu_syscall *call)
{
    struct qemu_OffsetRgn *c = (struct qemu_OffsetRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OffsetRgn(QEMU_G2H(c->hrgn), c->x, c->y);
}

#endif

struct qemu_GetRgnBox
{
    struct qemu_syscall super;
    uint64_t hrgn;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetRgnBox(HRGN hrgn, LPRECT rect)
{
    struct qemu_GetRgnBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRGNBOX);
    call.hrgn = (ULONG_PTR)hrgn;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRgnBox(struct qemu_syscall *call)
{
    struct qemu_GetRgnBox *c = (struct qemu_GetRgnBox *)call;
    WINE_TRACE("\n");
    c->super.iret = GetRgnBox(QEMU_G2H(c->hrgn), QEMU_G2H(c->rect));
}

#endif

struct qemu_CreateRectRgn
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreateRectRgn(INT left, INT top, INT right, INT bottom)
{
    struct qemu_CreateRectRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATERECTRGN);
    call.left = (ULONG_PTR)left;
    call.top = (ULONG_PTR)top;
    call.right = (ULONG_PTR)right;
    call.bottom = (ULONG_PTR)bottom;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateRectRgn(struct qemu_syscall *call)
{
    struct qemu_CreateRectRgn *c = (struct qemu_CreateRectRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateRectRgn(c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_CreateRectRgnIndirect
{
    struct qemu_syscall super;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreateRectRgnIndirect(const RECT* rect)
{
    struct qemu_CreateRectRgnIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATERECTRGNINDIRECT);
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateRectRgnIndirect(struct qemu_syscall *call)
{
    struct qemu_CreateRectRgnIndirect *c = (struct qemu_CreateRectRgnIndirect *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateRectRgnIndirect(QEMU_G2H(c->rect));
}

#endif

struct qemu_SetRectRgn
{
    struct qemu_syscall super;
    uint64_t hrgn;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetRectRgn(HRGN hrgn, INT left, INT top, INT right, INT bottom)
{
    struct qemu_SetRectRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETRECTRGN);
    call.hrgn = (ULONG_PTR)hrgn;
    call.left = (ULONG_PTR)left;
    call.top = (ULONG_PTR)top;
    call.right = (ULONG_PTR)right;
    call.bottom = (ULONG_PTR)bottom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetRectRgn(struct qemu_syscall *call)
{
    struct qemu_SetRectRgn *c = (struct qemu_SetRectRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = SetRectRgn(QEMU_G2H(c->hrgn), c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_CreateRoundRectRgn
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
    uint64_t ellipse_width;
    uint64_t ellipse_height;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreateRoundRectRgn(INT left, INT top, INT right, INT bottom, INT ellipse_width, INT ellipse_height)
{
    struct qemu_CreateRoundRectRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEROUNDRECTRGN);
    call.left = (ULONG_PTR)left;
    call.top = (ULONG_PTR)top;
    call.right = (ULONG_PTR)right;
    call.bottom = (ULONG_PTR)bottom;
    call.ellipse_width = (ULONG_PTR)ellipse_width;
    call.ellipse_height = (ULONG_PTR)ellipse_height;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateRoundRectRgn(struct qemu_syscall *call)
{
    struct qemu_CreateRoundRectRgn *c = (struct qemu_CreateRoundRectRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateRoundRectRgn(c->left, c->top, c->right, c->bottom, c->ellipse_width, c->ellipse_height);
}

#endif

struct qemu_CreateEllipticRgn
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreateEllipticRgn(INT left, INT top, INT right, INT bottom)
{
    struct qemu_CreateEllipticRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEELLIPTICRGN);
    call.left = (ULONG_PTR)left;
    call.top = (ULONG_PTR)top;
    call.right = (ULONG_PTR)right;
    call.bottom = (ULONG_PTR)bottom;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateEllipticRgn(struct qemu_syscall *call)
{
    struct qemu_CreateEllipticRgn *c = (struct qemu_CreateEllipticRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateEllipticRgn(c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_CreateEllipticRgnIndirect
{
    struct qemu_syscall super;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreateEllipticRgnIndirect(const RECT *rect)
{
    struct qemu_CreateEllipticRgnIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEELLIPTICRGNINDIRECT);
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateEllipticRgnIndirect(struct qemu_syscall *call)
{
    struct qemu_CreateEllipticRgnIndirect *c = (struct qemu_CreateEllipticRgnIndirect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateEllipticRgnIndirect(QEMU_G2H(c->rect));
}

#endif

struct qemu_GetRegionData
{
    struct qemu_syscall super;
    uint64_t hrgn;
    uint64_t count;
    uint64_t rgndata;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetRegionData(HRGN hrgn, DWORD count, LPRGNDATA rgndata)
{
    struct qemu_GetRegionData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETREGIONDATA);
    call.hrgn = (ULONG_PTR)hrgn;
    call.count = (ULONG_PTR)count;
    call.rgndata = (ULONG_PTR)rgndata;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRegionData(struct qemu_syscall *call)
{
    struct qemu_GetRegionData *c = (struct qemu_GetRegionData *)call;
    WINE_TRACE("\n");
    c->super.iret = GetRegionData(QEMU_G2H(c->hrgn), c->count, QEMU_G2H(c->rgndata));
}

#endif

struct qemu_ExtCreateRegion
{
    struct qemu_syscall super;
    uint64_t lpXform;
    uint64_t dwCount;
    uint64_t rgndata;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI ExtCreateRegion(const XFORM* lpXform, DWORD dwCount, const RGNDATA* rgndata)
{
    struct qemu_ExtCreateRegion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTCREATEREGION);
    call.lpXform = (ULONG_PTR)lpXform;
    call.dwCount = (ULONG_PTR)dwCount;
    call.rgndata = (ULONG_PTR)rgndata;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ExtCreateRegion(struct qemu_syscall *call)
{
    struct qemu_ExtCreateRegion *c = (struct qemu_ExtCreateRegion *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)ExtCreateRegion(QEMU_G2H(c->lpXform), c->dwCount, QEMU_G2H(c->rgndata));
}

#endif

struct qemu_PtInRegion
{
    struct qemu_syscall super;
    uint64_t hrgn;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PtInRegion(HRGN hrgn, INT x, INT y)
{
    struct qemu_PtInRegion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PTINREGION);
    call.hrgn = (ULONG_PTR)hrgn;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PtInRegion(struct qemu_syscall *call)
{
    struct qemu_PtInRegion *c = (struct qemu_PtInRegion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PtInRegion(QEMU_G2H(c->hrgn), c->x, c->y);
}

#endif

struct qemu_RectInRegion
{
    struct qemu_syscall super;
    uint64_t hrgn;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RectInRegion(HRGN hrgn, const RECT *rect)
{
    struct qemu_RectInRegion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RECTINREGION);
    call.hrgn = (ULONG_PTR)hrgn;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RectInRegion(struct qemu_syscall *call)
{
    struct qemu_RectInRegion *c = (struct qemu_RectInRegion *)call;
    WINE_TRACE("\n");
    c->super.iret = RectInRegion(QEMU_G2H(c->hrgn), QEMU_G2H(c->rect));
}

#endif

struct qemu_EqualRgn
{
    struct qemu_syscall super;
    uint64_t hrgn1;
    uint64_t hrgn2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EqualRgn(HRGN hrgn1, HRGN hrgn2)
{
    struct qemu_EqualRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EQUALRGN);
    call.hrgn1 = (ULONG_PTR)hrgn1;
    call.hrgn2 = (ULONG_PTR)hrgn2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EqualRgn(struct qemu_syscall *call)
{
    struct qemu_EqualRgn *c = (struct qemu_EqualRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = EqualRgn(QEMU_G2H(c->hrgn1), QEMU_G2H(c->hrgn2));
}

#endif

struct qemu_CombineRgn
{
    struct qemu_syscall super;
    uint64_t hDest;
    uint64_t hSrc1;
    uint64_t hSrc2;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CombineRgn(HRGN hDest, HRGN hSrc1, HRGN hSrc2, INT mode)
{
    struct qemu_CombineRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMBINERGN);
    call.hDest = (ULONG_PTR)hDest;
    call.hSrc1 = (ULONG_PTR)hSrc1;
    call.hSrc2 = (ULONG_PTR)hSrc2;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CombineRgn(struct qemu_syscall *call)
{
    struct qemu_CombineRgn *c = (struct qemu_CombineRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = CombineRgn(QEMU_G2H(c->hDest), QEMU_G2H(c->hSrc1), QEMU_G2H(c->hSrc2), c->mode);
}

#endif

struct qemu_MirrorRgn
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hrgn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MirrorRgn(HWND hwnd, HRGN hrgn)
{
    struct qemu_MirrorRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIRRORRGN);
    call.hwnd = (ULONG_PTR)hwnd;
    call.hrgn = (ULONG_PTR)hrgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MirrorRgn(struct qemu_syscall *call)
{
    struct qemu_MirrorRgn *c = (struct qemu_MirrorRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = MirrorRgn(QEMU_G2H(c->hwnd), QEMU_G2H(c->hrgn));
}

#endif

struct qemu_CreatePolyPolygonRgn
{
    struct qemu_syscall super;
    uint64_t Pts;
    uint64_t Count;
    uint64_t nbpolygons;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreatePolyPolygonRgn(const POINT *Pts, const INT *Count, INT nbpolygons, INT mode)
{
    struct qemu_CreatePolyPolygonRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPOLYPOLYGONRGN);
    call.Pts = (ULONG_PTR)Pts;
    call.Count = (ULONG_PTR)Count;
    call.nbpolygons = (ULONG_PTR)nbpolygons;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePolyPolygonRgn(struct qemu_syscall *call)
{
    struct qemu_CreatePolyPolygonRgn *c = (struct qemu_CreatePolyPolygonRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreatePolyPolygonRgn(QEMU_G2H(c->Pts), QEMU_G2H(c->Count), c->nbpolygons, c->mode);
}

#endif

struct qemu_CreatePolygonRgn
{
    struct qemu_syscall super;
    uint64_t points;
    uint64_t count;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI CreatePolygonRgn(const POINT *points, INT count, INT mode)
{
    struct qemu_CreatePolygonRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPOLYGONRGN);
    call.points = (ULONG_PTR)points;
    call.count = (ULONG_PTR)count;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePolygonRgn(struct qemu_syscall *call)
{
    struct qemu_CreatePolygonRgn *c = (struct qemu_CreatePolygonRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreatePolygonRgn(QEMU_G2H(c->points), c->count, c->mode);
}

#endif

