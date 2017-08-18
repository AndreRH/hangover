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


struct qemu_SelectClipRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hrgn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SelectClipRgn(HDC hdc, HRGN hrgn)
{
    struct qemu_SelectClipRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SELECTCLIPRGN);
    call.hdc = (uint64_t)hdc;
    call.hrgn = (uint64_t)hrgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SelectClipRgn(struct qemu_syscall *call)
{
    struct qemu_SelectClipRgn *c = (struct qemu_SelectClipRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = SelectClipRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hrgn));
}

#endif

struct qemu_ExtSelectClipRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hrgn;
    uint64_t fnMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ExtSelectClipRgn(HDC hdc, HRGN hrgn, INT fnMode)
{
    struct qemu_ExtSelectClipRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTSELECTCLIPRGN);
    call.hdc = (uint64_t)hdc;
    call.hrgn = (uint64_t)hrgn;
    call.fnMode = (uint64_t)fnMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtSelectClipRgn(struct qemu_syscall *call)
{
    struct qemu_ExtSelectClipRgn *c = (struct qemu_ExtSelectClipRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = ExtSelectClipRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hrgn), c->fnMode);
}

#endif

struct qemu_OffsetClipRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI OffsetClipRgn(HDC hdc, INT x, INT y)
{
    struct qemu_OffsetClipRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OFFSETCLIPRGN);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OffsetClipRgn(struct qemu_syscall *call)
{
    struct qemu_OffsetClipRgn *c = (struct qemu_OffsetClipRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = OffsetClipRgn(QEMU_G2H(c->hdc), c->x, c->y);
}

#endif

struct qemu_ExcludeClipRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ExcludeClipRect(HDC hdc, INT left, INT top, INT right, INT bottom)
{
    struct qemu_ExcludeClipRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXCLUDECLIPRECT);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExcludeClipRect(struct qemu_syscall *call)
{
    struct qemu_ExcludeClipRect *c = (struct qemu_ExcludeClipRect *)call;
    WINE_TRACE("\n");
    c->super.iret = ExcludeClipRect(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_IntersectClipRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t right;
    uint64_t bottom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI IntersectClipRect(HDC hdc, INT left, INT top, INT right, INT bottom)
{
    struct qemu_IntersectClipRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERSECTCLIPRECT);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.right = (uint64_t)right;
    call.bottom = (uint64_t)bottom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IntersectClipRect(struct qemu_syscall *call)
{
    struct qemu_IntersectClipRect *c = (struct qemu_IntersectClipRect *)call;
    WINE_TRACE("\n");
    c->super.iret = IntersectClipRect(QEMU_G2H(c->hdc), c->left, c->top, c->right, c->bottom);
}

#endif

struct qemu_PtVisible
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PtVisible(HDC hdc, INT x, INT y)
{
    struct qemu_PtVisible call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PTVISIBLE);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PtVisible(struct qemu_syscall *call)
{
    struct qemu_PtVisible *c = (struct qemu_PtVisible *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PtVisible(QEMU_G2H(c->hdc), c->x, c->y);
}

#endif

struct qemu_RectVisible
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RectVisible(HDC hdc, const RECT* rect)
{
    struct qemu_RectVisible call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RECTVISIBLE);
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RectVisible(struct qemu_syscall *call)
{
    struct qemu_RectVisible *c = (struct qemu_RectVisible *)call;
    WINE_TRACE("\n");
    c->super.iret = RectVisible(QEMU_G2H(c->hdc), QEMU_G2H(c->rect));
}

#endif

struct qemu_GetClipBox
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetClipBox(HDC hdc, LPRECT rect)
{
    struct qemu_GetClipBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPBOX);
    call.hdc = (uint64_t)hdc;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClipBox(struct qemu_syscall *call)
{
    struct qemu_GetClipBox *c = (struct qemu_GetClipBox *)call;
    WINE_TRACE("\n");
    c->super.iret = GetClipBox(QEMU_G2H(c->hdc), QEMU_G2H(c->rect));
}

#endif

struct qemu_GetClipRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hRgn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetClipRgn(HDC hdc, HRGN hRgn)
{
    struct qemu_GetClipRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCLIPRGN);
    call.hdc = (uint64_t)hdc;
    call.hRgn = (uint64_t)hRgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetClipRgn(struct qemu_syscall *call)
{
    struct qemu_GetClipRgn *c = (struct qemu_GetClipRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = GetClipRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hRgn));
}

#endif

struct qemu_GetMetaRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hRgn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetMetaRgn(HDC hdc, HRGN hRgn)
{
    struct qemu_GetMetaRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMETARGN);
    call.hdc = (uint64_t)hdc;
    call.hRgn = (uint64_t)hRgn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMetaRgn(struct qemu_syscall *call)
{
    struct qemu_GetMetaRgn *c = (struct qemu_GetMetaRgn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMetaRgn(QEMU_G2H(c->hdc), QEMU_G2H(c->hRgn));
}

#endif

struct qemu_GetRandomRgn
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t hRgn;
    uint64_t iCode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetRandomRgn(HDC hDC, HRGN hRgn, INT iCode)
{
    struct qemu_GetRandomRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRANDOMRGN);
    call.hDC = (uint64_t)hDC;
    call.hRgn = (uint64_t)hRgn;
    call.iCode = (uint64_t)iCode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRandomRgn(struct qemu_syscall *call)
{
    struct qemu_GetRandomRgn *c = (struct qemu_GetRandomRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = GetRandomRgn(QEMU_G2H(c->hDC), QEMU_G2H(c->hRgn), c->iCode);
}

#endif

struct qemu_SetMetaRgn
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SetMetaRgn(HDC hdc)
{
    struct qemu_SetMetaRgn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMETARGN);
    call.hdc = (uint64_t)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMetaRgn(struct qemu_syscall *call)
{
    struct qemu_SetMetaRgn *c = (struct qemu_SetMetaRgn *)call;
    WINE_TRACE("\n");
    c->super.iret = SetMetaRgn(QEMU_G2H(c->hdc));
}

#endif

