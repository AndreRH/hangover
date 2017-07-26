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


struct qemu_PatBlt
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t left;
    uint64_t top;
    uint64_t width;
    uint64_t height;
    uint64_t rop;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PatBlt(HDC hdc, INT left, INT top, INT width, INT height, DWORD rop)
{
    struct qemu_PatBlt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATBLT);
    call.hdc = (uint64_t)hdc;
    call.left = (uint64_t)left;
    call.top = (uint64_t)top;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.rop = (uint64_t)rop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PatBlt(struct qemu_syscall *call)
{
    struct qemu_PatBlt *c = (struct qemu_PatBlt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PatBlt(QEMU_G2H(c->hdc), c->left, c->top, c->width, c->height, c->rop);
}

#endif

struct qemu_BitBlt
{
    struct qemu_syscall super;
    uint64_t hdcDst;
    uint64_t xDst;
    uint64_t yDst;
    uint64_t width;
    uint64_t height;
    uint64_t hdcSrc;
    uint64_t xSrc;
    uint64_t ySrc;
    uint64_t rop;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BitBlt(HDC hdcDst, INT xDst, INT yDst, INT width, INT height, HDC hdcSrc, INT xSrc, INT ySrc, DWORD rop)
{
    struct qemu_BitBlt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BITBLT);
    call.hdcDst = (uint64_t)hdcDst;
    call.xDst = xDst;
    call.yDst = yDst;
    call.width = width;
    call.height = height;
    call.hdcSrc = hdcSrc;
    call.xSrc = xSrc;
    call.ySrc = ySrc;
    call.rop = rop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BitBlt(struct qemu_syscall *call)
{
    struct qemu_BitBlt *c = (struct qemu_BitBlt *)call;
    WINE_TRACE("\n");
    c->super.iret = BitBlt(QEMU_G2H(c->hdcDst), c->xDst, c->yDst, c->width, c->height, QEMU_G2H(c->hdcSrc), c->xSrc, c->ySrc, c->rop);
}

#endif

struct qemu_StretchBlt
{
    struct qemu_syscall super;
    uint64_t hdcDst;
    uint64_t xDst;
    uint64_t yDst;
    uint64_t widthDst;
    uint64_t heightDst;
    uint64_t hdcSrc;
    uint64_t xSrc;
    uint64_t ySrc;
    uint64_t widthSrc;
    uint64_t heightSrc;
    uint64_t rop;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StretchBlt(HDC hdcDst, INT xDst, INT yDst, INT widthDst, INT heightDst, HDC hdcSrc, INT xSrc, INT ySrc, INT widthSrc, INT heightSrc, DWORD rop)
{
    struct qemu_StretchBlt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRETCHBLT);
    call.hdcDst = (uint64_t)hdcDst;
    call.xDst = (uint64_t)xDst;
    call.yDst = (uint64_t)yDst;
    call.widthDst = (uint64_t)widthDst;
    call.heightDst = (uint64_t)heightDst;
    call.hdcSrc = (uint64_t)hdcSrc;
    call.xSrc = (uint64_t)xSrc;
    call.ySrc = (uint64_t)ySrc;
    call.widthSrc = (uint64_t)widthSrc;
    call.heightSrc = (uint64_t)heightSrc;
    call.rop = (uint64_t)rop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StretchBlt(struct qemu_syscall *call)
{
    struct qemu_StretchBlt *c = (struct qemu_StretchBlt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StretchBlt(QEMU_G2H(c->hdcDst), c->xDst, c->yDst, c->widthDst, c->heightDst, QEMU_G2H(c->hdcSrc), c->xSrc, c->ySrc, c->widthSrc, c->heightSrc, c->rop);
}

#endif

struct qemu_MaskBlt
{
    struct qemu_syscall super;
    uint64_t hdcDest;
    uint64_t nXDest;
    uint64_t nYDest;
    uint64_t nWidth;
    uint64_t nHeight;
    uint64_t hdcSrc;
    uint64_t nXSrc;
    uint64_t nYSrc;
    uint64_t hbmMask;
    uint64_t xMask;
    uint64_t yMask;
    uint64_t dwRop;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MaskBlt(HDC hdcDest, INT nXDest, INT nYDest, INT nWidth, INT nHeight, HDC hdcSrc, INT nXSrc, INT nYSrc, HBITMAP hbmMask, INT xMask, INT yMask, DWORD dwRop)
{
    struct qemu_MaskBlt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MASKBLT);
    call.hdcDest = (uint64_t)hdcDest;
    call.nXDest = (uint64_t)nXDest;
    call.nYDest = (uint64_t)nYDest;
    call.nWidth = (uint64_t)nWidth;
    call.nHeight = (uint64_t)nHeight;
    call.hdcSrc = (uint64_t)hdcSrc;
    call.nXSrc = (uint64_t)nXSrc;
    call.nYSrc = (uint64_t)nYSrc;
    call.hbmMask = (uint64_t)hbmMask;
    call.xMask = (uint64_t)xMask;
    call.yMask = (uint64_t)yMask;
    call.dwRop = (uint64_t)dwRop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MaskBlt(struct qemu_syscall *call)
{
    struct qemu_MaskBlt *c = (struct qemu_MaskBlt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MaskBlt(QEMU_G2H(c->hdcDest), c->nXDest, c->nYDest, c->nWidth, c->nHeight, QEMU_G2H(c->hdcSrc), c->nXSrc, c->nYSrc, QEMU_G2H(c->hbmMask), c->xMask, c->yMask, c->dwRop);
}

#endif

struct qemu_GdiTransparentBlt
{
    struct qemu_syscall super;
    uint64_t hdcDest;
    uint64_t xDest;
    uint64_t yDest;
    uint64_t widthDest;
    uint64_t heightDest;
    uint64_t hdcSrc;
    uint64_t xSrc;
    uint64_t ySrc;
    uint64_t widthSrc;
    uint64_t heightSrc;
    uint64_t crTransparent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GdiTransparentBlt(HDC hdcDest, int xDest, int yDest, int widthDest, int heightDest, HDC hdcSrc, int xSrc, int ySrc, int widthSrc, int heightSrc, UINT crTransparent)
{
    struct qemu_GdiTransparentBlt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDITRANSPARENTBLT);
    call.hdcDest = (uint64_t)hdcDest;
    call.xDest = (uint64_t)xDest;
    call.yDest = (uint64_t)yDest;
    call.widthDest = (uint64_t)widthDest;
    call.heightDest = (uint64_t)heightDest;
    call.hdcSrc = (uint64_t)hdcSrc;
    call.xSrc = (uint64_t)xSrc;
    call.ySrc = (uint64_t)ySrc;
    call.widthSrc = (uint64_t)widthSrc;
    call.heightSrc = (uint64_t)heightSrc;
    call.crTransparent = (uint64_t)crTransparent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiTransparentBlt(struct qemu_syscall *call)
{
    struct qemu_GdiTransparentBlt *c = (struct qemu_GdiTransparentBlt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiTransparentBlt(QEMU_G2H(c->hdcDest), c->xDest, c->yDest, c->widthDest, c->heightDest, QEMU_G2H(c->hdcSrc), c->xSrc, c->ySrc, c->widthSrc, c->heightSrc, c->crTransparent);
}

#endif

struct qemu_GdiAlphaBlend
{
    struct qemu_syscall super;
    uint64_t hdcDst;
    uint64_t xDst;
    uint64_t yDst;
    uint64_t widthDst;
    uint64_t heightDst;
    uint64_t hdcSrc;
    uint64_t xSrc;
    uint64_t ySrc;
    uint64_t widthSrc;
    uint64_t heightSrc;
    uint64_t blendFunction_op;
    uint64_t blendFunction_flags;
    uint64_t blendFunction_const;
    uint64_t blendFunction_fmt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GdiAlphaBlend(HDC hdcDst, int xDst, int yDst, int widthDst, int heightDst, HDC hdcSrc, int xSrc, int ySrc, int widthSrc, int heightSrc, BLENDFUNCTION blendFunction)
{
    struct qemu_GdiAlphaBlend call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIALPHABLEND);
    call.hdcDst = (uint64_t)hdcDst;
    call.xDst = (uint64_t)xDst;
    call.yDst = (uint64_t)yDst;
    call.widthDst = (uint64_t)widthDst;
    call.heightDst = (uint64_t)heightDst;
    call.hdcSrc = (uint64_t)hdcSrc;
    call.xSrc = (uint64_t)xSrc;
    call.ySrc = (uint64_t)ySrc;
    call.widthSrc = (uint64_t)widthSrc;
    call.heightSrc = (uint64_t)heightSrc;
    call.blendFunction_op = (uint64_t)blendFunction.BlendOp;
    call.blendFunction_flags = (uint64_t)blendFunction.BlendFlags;
    call.blendFunction_const = (uint64_t)blendFunction.SourceConstantAlpha;
    call.blendFunction_fmt = (uint64_t)blendFunction.AlphaFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiAlphaBlend(struct qemu_syscall *call)
{
    struct qemu_GdiAlphaBlend *c = (struct qemu_GdiAlphaBlend *)call;
    BLENDFUNCTION func;

    WINE_FIXME("Unverified!\n");
    func.BlendOp = c->blendFunction_op;
    func.BlendFlags = c->blendFunction_flags;
    func.SourceConstantAlpha = c->blendFunction_const;
    func.AlphaFormat = c->blendFunction_fmt;

    c->super.iret = GdiAlphaBlend(QEMU_G2H(c->hdcDst), c->xDst, c->yDst, c->widthDst, c->heightDst, QEMU_G2H(c->hdcSrc), c->xSrc, c->ySrc, c->widthSrc, c->heightSrc, func);
}

#endif

struct qemu_PlgBlt
{
    struct qemu_syscall super;
    uint64_t hdcDest;
    uint64_t lpPoint;
    uint64_t hdcSrc;
    uint64_t nXSrc;
    uint64_t nYSrc;
    uint64_t nWidth;
    uint64_t nHeight;
    uint64_t hbmMask;
    uint64_t xMask;
    uint64_t yMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PlgBlt(HDC hdcDest, const POINT *lpPoint, HDC hdcSrc, INT nXSrc, INT nYSrc, INT nWidth, INT nHeight, HBITMAP hbmMask, INT xMask, INT yMask)
{
    struct qemu_PlgBlt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLGBLT);
    call.hdcDest = (uint64_t)hdcDest;
    call.lpPoint = (uint64_t)lpPoint;
    call.hdcSrc = (uint64_t)hdcSrc;
    call.nXSrc = (uint64_t)nXSrc;
    call.nYSrc = (uint64_t)nYSrc;
    call.nWidth = (uint64_t)nWidth;
    call.nHeight = (uint64_t)nHeight;
    call.hbmMask = (uint64_t)hbmMask;
    call.xMask = (uint64_t)xMask;
    call.yMask = (uint64_t)yMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlgBlt(struct qemu_syscall *call)
{
    struct qemu_PlgBlt *c = (struct qemu_PlgBlt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PlgBlt(QEMU_G2H(c->hdcDest), QEMU_G2H(c->lpPoint), QEMU_G2H(c->hdcSrc), c->nXSrc, c->nYSrc, c->nWidth, c->nHeight, QEMU_G2H(c->hbmMask), c->xMask, c->yMask);
}

#endif

