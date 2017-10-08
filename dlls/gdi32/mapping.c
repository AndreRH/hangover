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


struct qemu_DPtoLP
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t points;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI DPtoLP(HDC hdc, POINT *points, INT count)
{
    struct qemu_DPtoLP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPTOLP);
    call.hdc = (ULONG_PTR)hdc;
    call.points = (ULONG_PTR)points;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPtoLP(struct qemu_syscall *call)
{
    struct qemu_DPtoLP *c = (struct qemu_DPtoLP *)call;
    WINE_TRACE("\n");
    c->super.iret = DPtoLP(QEMU_G2H(c->hdc), QEMU_G2H(c->points), c->count);
}

#endif

struct qemu_LPtoDP
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t points;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI LPtoDP(HDC hdc, POINT *points, INT count)
{
    struct qemu_LPtoDP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LPTODP);
    call.hdc = (ULONG_PTR)hdc;
    call.points = (ULONG_PTR)points;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LPtoDP(struct qemu_syscall *call)
{
    struct qemu_LPtoDP *c = (struct qemu_LPtoDP *)call;
    WINE_TRACE("\n");
    c->super.iret = LPtoDP(QEMU_G2H(c->hdc), QEMU_G2H(c->points), c->count);
}

#endif

struct qemu_SetMapMode
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetMapMode(HDC hdc, INT mode)
{
    struct qemu_SetMapMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMAPMODE);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMapMode(struct qemu_syscall *call)
{
    struct qemu_SetMapMode *c = (struct qemu_SetMapMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetMapMode(QEMU_G2H(c->hdc), c->mode);
}

#endif

struct qemu_SetViewportExtEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetViewportExtEx(HDC hdc, INT x, INT y, LPSIZE size)
{
    struct qemu_SetViewportExtEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVIEWPORTEXTEX);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetViewportExtEx(struct qemu_syscall *call)
{
    struct qemu_SetViewportExtEx *c = (struct qemu_SetViewportExtEx *)call;
    WINE_TRACE("\n");
    c->super.iret = SetViewportExtEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->size));
}

#endif

struct qemu_SetViewportOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetViewportOrgEx(HDC hdc, INT x, INT y, LPPOINT pt)
{
    struct qemu_SetViewportOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVIEWPORTORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetViewportOrgEx(struct qemu_syscall *call)
{
    struct qemu_SetViewportOrgEx *c = (struct qemu_SetViewportOrgEx *)call;
    WINE_TRACE("\n");
    c->super.iret = SetViewportOrgEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->pt));
}

#endif

struct qemu_SetWindowExtEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetWindowExtEx(HDC hdc, INT x, INT y, LPSIZE size)
{
    struct qemu_SetWindowExtEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWEXTEX);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowExtEx(struct qemu_syscall *call)
{
    struct qemu_SetWindowExtEx *c = (struct qemu_SetWindowExtEx *)call;
    WINE_TRACE("\n");
    c->super.iret = SetWindowExtEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->size));
}

#endif

struct qemu_SetWindowOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetWindowOrgEx(HDC hdc, INT x, INT y, LPPOINT pt)
{
    struct qemu_SetWindowOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWindowOrgEx(struct qemu_syscall *call)
{
    struct qemu_SetWindowOrgEx *c = (struct qemu_SetWindowOrgEx *)call;
    WINE_TRACE("\n");
    c->super.iret = SetWindowOrgEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->pt));
}

#endif

struct qemu_OffsetViewportOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI OffsetViewportOrgEx(HDC hdc, INT x, INT y, LPPOINT pt)
{
    struct qemu_OffsetViewportOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OFFSETVIEWPORTORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OffsetViewportOrgEx(struct qemu_syscall *call)
{
    struct qemu_OffsetViewportOrgEx *c = (struct qemu_OffsetViewportOrgEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OffsetViewportOrgEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->pt));
}

#endif

struct qemu_OffsetWindowOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI OffsetWindowOrgEx(HDC hdc, INT x, INT y, LPPOINT pt)
{
    struct qemu_OffsetWindowOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OFFSETWINDOWORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OffsetWindowOrgEx(struct qemu_syscall *call)
{
    struct qemu_OffsetWindowOrgEx *c = (struct qemu_OffsetWindowOrgEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = OffsetWindowOrgEx(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->pt));
}

#endif

struct qemu_ScaleViewportExtEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t xNum;
    uint64_t xDenom;
    uint64_t yNum;
    uint64_t yDenom;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI ScaleViewportExtEx(HDC hdc, INT xNum, INT xDenom, INT yNum, INT yDenom, LPSIZE size)
{
    struct qemu_ScaleViewportExtEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCALEVIEWPORTEXTEX);
    call.hdc = (ULONG_PTR)hdc;
    call.xNum = (ULONG_PTR)xNum;
    call.xDenom = (ULONG_PTR)xDenom;
    call.yNum = (ULONG_PTR)yNum;
    call.yDenom = (ULONG_PTR)yDenom;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScaleViewportExtEx(struct qemu_syscall *call)
{
    struct qemu_ScaleViewportExtEx *c = (struct qemu_ScaleViewportExtEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScaleViewportExtEx(QEMU_G2H(c->hdc), c->xNum, c->xDenom, c->yNum, c->yDenom, QEMU_G2H(c->size));
}

#endif

struct qemu_ScaleWindowExtEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t xNum;
    uint64_t xDenom;
    uint64_t yNum;
    uint64_t yDenom;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI ScaleWindowExtEx(HDC hdc, INT xNum, INT xDenom, INT yNum, INT yDenom, LPSIZE size)
{
    struct qemu_ScaleWindowExtEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCALEWINDOWEXTEX);
    call.hdc = (ULONG_PTR)hdc;
    call.xNum = (ULONG_PTR)xNum;
    call.xDenom = (ULONG_PTR)xDenom;
    call.yNum = (ULONG_PTR)yNum;
    call.yDenom = (ULONG_PTR)yDenom;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScaleWindowExtEx(struct qemu_syscall *call)
{
    struct qemu_ScaleWindowExtEx *c = (struct qemu_ScaleWindowExtEx *)call;
    WINE_TRACE("\n");
    c->super.iret = ScaleWindowExtEx(QEMU_G2H(c->hdc), c->xNum, c->xDenom, c->yNum, c->yDenom, QEMU_G2H(c->size));
}

#endif

struct qemu_ModifyWorldTransform
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t xform;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI ModifyWorldTransform(HDC hdc, const XFORM *xform, DWORD mode)
{
    struct qemu_ModifyWorldTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MODIFYWORLDTRANSFORM);
    call.hdc = (ULONG_PTR)hdc;
    call.xform = (ULONG_PTR)xform;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ModifyWorldTransform(struct qemu_syscall *call)
{
    struct qemu_ModifyWorldTransform *c = (struct qemu_ModifyWorldTransform *)call;
    WINE_TRACE("\n");
    c->super.iret = ModifyWorldTransform(QEMU_G2H(c->hdc), QEMU_G2H(c->xform), c->mode);
}

#endif

struct qemu_SetWorldTransform
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t xform;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetWorldTransform(HDC hdc, const XFORM *xform)
{
    struct qemu_SetWorldTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWORLDTRANSFORM);
    call.hdc = (ULONG_PTR)hdc;
    call.xform = (ULONG_PTR)xform;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetWorldTransform(struct qemu_syscall *call)
{
    struct qemu_SetWorldTransform *c = (struct qemu_SetWorldTransform *)call;
    WINE_TRACE("\n");
    c->super.iret = SetWorldTransform(QEMU_G2H(c->hdc), QEMU_G2H(c->xform));
}

#endif

struct qemu_SetVirtualResolution
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t horz_res;
    uint64_t vert_res;
    uint64_t horz_size;
    uint64_t vert_size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetVirtualResolution(HDC hdc, DWORD horz_res, DWORD vert_res, DWORD horz_size, DWORD vert_size)
{
    struct qemu_SetVirtualResolution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETVIRTUALRESOLUTION);
    call.hdc = (ULONG_PTR)hdc;
    call.horz_res = (ULONG_PTR)horz_res;
    call.vert_res = (ULONG_PTR)vert_res;
    call.horz_size = (ULONG_PTR)horz_size;
    call.vert_size = (ULONG_PTR)vert_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetVirtualResolution to Wine headers? */
extern BOOL WINAPI SetVirtualResolution(HDC hdc, DWORD horz_res, DWORD vert_res, DWORD horz_size, DWORD vert_size);
void qemu_SetVirtualResolution(struct qemu_syscall *call)
{
    struct qemu_SetVirtualResolution *c = (struct qemu_SetVirtualResolution *)call;
    WINE_TRACE("\n");
    c->super.iret = SetVirtualResolution(QEMU_G2H(c->hdc), c->horz_res, c->vert_res, c->horz_size, c->vert_size);
}

#endif

