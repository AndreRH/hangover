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

struct qemu_CreateBitmap
{
    struct qemu_syscall super;
    uint64_t width;
    uint64_t height;
    uint64_t planes;
    uint64_t bpp;
    uint64_t bits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HBITMAP WINAPI CreateBitmap(INT width, INT height, UINT planes, UINT bpp, LPCVOID bits)
{
    struct qemu_CreateBitmap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEBITMAP);
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.planes = (uint64_t)planes;
    call.bpp = (uint64_t)bpp;
    call.bits = (uint64_t)bits;

    qemu_syscall(&call.super);

    return (HBITMAP)call.super.iret;
}

#else

void qemu_CreateBitmap(struct qemu_syscall *call)
{
    struct qemu_CreateBitmap *c = (struct qemu_CreateBitmap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateBitmap(c->width, c->height, c->planes, c->bpp, QEMU_G2H(c->bits));
}

#endif

struct qemu_CreateCompatibleBitmap
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HBITMAP WINAPI CreateCompatibleBitmap(HDC hdc, INT width, INT height)
{
    struct qemu_CreateCompatibleBitmap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATECOMPATIBLEBITMAP);
    call.hdc = (uint64_t)hdc;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;

    qemu_syscall(&call.super);

    return (HBITMAP)call.super.iret;
}

#else

void qemu_CreateCompatibleBitmap(struct qemu_syscall *call)
{
    struct qemu_CreateCompatibleBitmap *c = (struct qemu_CreateCompatibleBitmap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateCompatibleBitmap(QEMU_G2H(c->hdc), c->width, c->height);
}

#endif

struct qemu_CreateBitmapIndirect
{
    struct qemu_syscall super;
    uint64_t bmp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HBITMAP WINAPI CreateBitmapIndirect(const BITMAP *bmp)
{
    struct qemu_CreateBitmapIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEBITMAPINDIRECT);
    call.bmp = (uint64_t)bmp;

    qemu_syscall(&call.super);

    return (HBITMAP)call.super.iret;
}

#else

void qemu_CreateBitmapIndirect(struct qemu_syscall *call)
{
    struct qemu_CreateBitmapIndirect *c = (struct qemu_CreateBitmapIndirect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateBitmapIndirect(QEMU_G2H(c->bmp));
}

#endif

struct qemu_GetBitmapBits
{
    struct qemu_syscall super;
    uint64_t hbitmap;
    uint64_t count;
    uint64_t bits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI GetBitmapBits(HBITMAP hbitmap, LONG count, LPVOID bits)
{
    struct qemu_GetBitmapBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBITMAPBITS);
    call.hbitmap = (uint64_t)hbitmap;
    call.count = (uint64_t)count;
    call.bits = (uint64_t)bits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBitmapBits(struct qemu_syscall *call)
{
    struct qemu_GetBitmapBits *c = (struct qemu_GetBitmapBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBitmapBits(QEMU_G2H(c->hbitmap), c->count, QEMU_G2H(c->bits));
}

#endif

struct qemu_SetBitmapBits
{
    struct qemu_syscall super;
    uint64_t hbitmap;
    uint64_t count;
    uint64_t bits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI SetBitmapBits(HBITMAP hbitmap, DWORD count, LPCVOID bits)
{
    struct qemu_SetBitmapBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETBITMAPBITS);
    call.hbitmap = (uint64_t)hbitmap;
    call.count = (uint64_t)count;
    call.bits = (uint64_t)bits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetBitmapBits(struct qemu_syscall *call)
{
    struct qemu_SetBitmapBits *c = (struct qemu_SetBitmapBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetBitmapBits(QEMU_G2H(c->hbitmap), c->count, QEMU_G2H(c->bits));
}

#endif

struct qemu_CreateDiscardableBitmap
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HBITMAP WINAPI CreateDiscardableBitmap(HDC hdc, INT width, INT height)
{
    struct qemu_CreateDiscardableBitmap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDISCARDABLEBITMAP);
    call.hdc = (uint64_t)hdc;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;

    qemu_syscall(&call.super);

    return (HBITMAP)call.super.iret;
}

#else

void qemu_CreateDiscardableBitmap(struct qemu_syscall *call)
{
    struct qemu_CreateDiscardableBitmap *c = (struct qemu_CreateDiscardableBitmap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateDiscardableBitmap(QEMU_G2H(c->hdc), c->width, c->height);
}

#endif

struct qemu_GetBitmapDimensionEx
{
    struct qemu_syscall super;
    uint64_t hbitmap;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetBitmapDimensionEx(HBITMAP hbitmap, LPSIZE size)
{
    struct qemu_GetBitmapDimensionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBITMAPDIMENSIONEX);
    call.hbitmap = (uint64_t)hbitmap;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBitmapDimensionEx(struct qemu_syscall *call)
{
    struct qemu_GetBitmapDimensionEx *c = (struct qemu_GetBitmapDimensionEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBitmapDimensionEx(QEMU_G2H(c->hbitmap), QEMU_G2H(c->size));
}

#endif

struct qemu_SetBitmapDimensionEx
{
    struct qemu_syscall super;
    uint64_t hbitmap;
    uint64_t x;
    uint64_t y;
    uint64_t prevSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetBitmapDimensionEx(HBITMAP hbitmap, INT x, INT y, LPSIZE prevSize)
{
    struct qemu_SetBitmapDimensionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETBITMAPDIMENSIONEX);
    call.hbitmap = (uint64_t)hbitmap;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.prevSize = (uint64_t)prevSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetBitmapDimensionEx(struct qemu_syscall *call)
{
    struct qemu_SetBitmapDimensionEx *c = (struct qemu_SetBitmapDimensionEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetBitmapDimensionEx(QEMU_G2H(c->hbitmap), c->x, c->y, QEMU_G2H(c->prevSize));
}

#endif

