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


struct qemu_BeginPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BeginPath(HDC hdc)
{
    struct qemu_BeginPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BEGINPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BeginPath(struct qemu_syscall *call)
{
    struct qemu_BeginPath *c = (struct qemu_BeginPath *)call;
    WINE_TRACE("\n");
    c->super.iret = BeginPath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_EndPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EndPath(HDC hdc)
{
    struct qemu_EndPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndPath(struct qemu_syscall *call)
{
    struct qemu_EndPath *c = (struct qemu_EndPath *)call;
    WINE_TRACE("\n");
    c->super.iret = EndPath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_AbortPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AbortPath(HDC hdc)
{
    struct qemu_AbortPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ABORTPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AbortPath(struct qemu_syscall *call)
{
    struct qemu_AbortPath *c = (struct qemu_AbortPath *)call;
    WINE_TRACE("\n");
    c->super.iret = AbortPath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_CloseFigure
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseFigure(HDC hdc)
{
    struct qemu_CloseFigure call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEFIGURE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseFigure(struct qemu_syscall *call)
{
    struct qemu_CloseFigure *c = (struct qemu_CloseFigure *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseFigure(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GetPath
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pPoints;
    uint64_t pTypes;
    uint64_t nSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetPath(HDC hdc, LPPOINT pPoints, LPBYTE pTypes, INT nSize)
{
    struct qemu_GetPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPATH);
    call.hdc = (ULONG_PTR)hdc;
    call.pPoints = (ULONG_PTR)pPoints;
    call.pTypes = (ULONG_PTR)pTypes;
    call.nSize = (ULONG_PTR)nSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPath(struct qemu_syscall *call)
{
    struct qemu_GetPath *c = (struct qemu_GetPath *)call;
    WINE_TRACE("\n");
    c->super.iret = GetPath(QEMU_G2H(c->hdc), QEMU_G2H(c->pPoints), QEMU_G2H(c->pTypes), c->nSize);
}

#endif

struct qemu_PathToRegion
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRGN WINAPI PathToRegion(HDC hdc)
{
    struct qemu_PathToRegion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHTOREGION);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return (HRGN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathToRegion(struct qemu_syscall *call)
{
    struct qemu_PathToRegion *c = (struct qemu_PathToRegion *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)PathToRegion(QEMU_G2H(c->hdc));
}

#endif

struct qemu_FillPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FillPath(HDC hdc)
{
    struct qemu_FillPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILLPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FillPath(struct qemu_syscall *call)
{
    struct qemu_FillPath *c = (struct qemu_FillPath *)call;
    WINE_TRACE("\n");
    c->super.iret = FillPath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SelectClipPath
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SelectClipPath(HDC hdc, INT iMode)
{
    struct qemu_SelectClipPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SELECTCLIPPATH);
    call.hdc = (ULONG_PTR)hdc;
    call.iMode = (ULONG_PTR)iMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SelectClipPath(struct qemu_syscall *call)
{
    struct qemu_SelectClipPath *c = (struct qemu_SelectClipPath *)call;
    WINE_TRACE("\n");
    c->super.iret = SelectClipPath(QEMU_G2H(c->hdc), c->iMode);
}

#endif

struct qemu_FlattenPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlattenPath(HDC hdc)
{
    struct qemu_FlattenPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLATTENPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlattenPath(struct qemu_syscall *call)
{
    struct qemu_FlattenPath *c = (struct qemu_FlattenPath *)call;
    WINE_TRACE("\n");
    c->super.iret = FlattenPath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_StrokeAndFillPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrokeAndFillPath(HDC hdc)
{
    struct qemu_StrokeAndFillPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STROKEANDFILLPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrokeAndFillPath(struct qemu_syscall *call)
{
    struct qemu_StrokeAndFillPath *c = (struct qemu_StrokeAndFillPath *)call;
    WINE_TRACE("\n");
    c->super.iret = StrokeAndFillPath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_StrokePath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrokePath(HDC hdc)
{
    struct qemu_StrokePath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STROKEPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrokePath(struct qemu_syscall *call)
{
    struct qemu_StrokePath *c = (struct qemu_StrokePath *)call;
    WINE_TRACE("\n");
    c->super.iret = StrokePath(QEMU_G2H(c->hdc));
}

#endif

struct qemu_WidenPath
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WidenPath(HDC hdc)
{
    struct qemu_WidenPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WIDENPATH);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WidenPath(struct qemu_syscall *call)
{
    struct qemu_WidenPath *c = (struct qemu_WidenPath *)call;
    WINE_TRACE("\n");
    c->super.iret = WidenPath(QEMU_G2H(c->hdc));
}

#endif

