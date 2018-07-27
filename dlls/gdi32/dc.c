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
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_SaveDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SaveDC(HDC hdc)
{
    struct qemu_SaveDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SAVEDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SaveDC(struct qemu_syscall *call)
{
    struct qemu_SaveDC *c = (struct qemu_SaveDC *)call;
    WINE_TRACE("\n");
    c->super.iret = SaveDC(QEMU_G2H(c->hdc));
}

#endif

struct qemu_RestoreDC
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI RestoreDC(HDC hdc, INT level)
{
    struct qemu_RestoreDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESTOREDC);
    call.hdc = (ULONG_PTR)hdc;
    call.level = (ULONG_PTR)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RestoreDC(struct qemu_syscall *call)
{
    struct qemu_RestoreDC *c = (struct qemu_RestoreDC *)call;
    WINE_TRACE("\n");
    c->super.iret = RestoreDC(QEMU_G2H(c->hdc), c->level);
}

#endif

struct qemu_CreateDCW
{
    struct qemu_syscall super;
    uint64_t driver;
    uint64_t device;
    uint64_t output;
    uint64_t initData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI CreateDCW(LPCWSTR driver, LPCWSTR device, LPCWSTR output, const DEVMODEW *initData)
{
    struct qemu_CreateDCW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDCW);
    call.driver = (ULONG_PTR)driver;
    call.device = (ULONG_PTR)device;
    call.output = (ULONG_PTR)output;
    call.initData = (ULONG_PTR)initData;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateDCW(struct qemu_syscall *call)
{
    struct qemu_CreateDCW *c = (struct qemu_CreateDCW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateDCW(QEMU_G2H(c->driver), QEMU_G2H(c->device), QEMU_G2H(c->output), QEMU_G2H(c->initData));
}

#endif

struct qemu_CreateDCA
{
    struct qemu_syscall super;
    uint64_t driver;
    uint64_t device;
    uint64_t output;
    uint64_t initData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI CreateDCA(LPCSTR driver, LPCSTR device, LPCSTR output, const DEVMODEA *initData)
{
    struct qemu_CreateDCA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDCA);
    call.driver = (ULONG_PTR)driver;
    call.device = (ULONG_PTR)device;
    call.output = (ULONG_PTR)output;
    call.initData = (ULONG_PTR)initData;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateDCA(struct qemu_syscall *call)
{
    struct qemu_CreateDCA *c = (struct qemu_CreateDCA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateDCA(QEMU_G2H(c->driver), QEMU_G2H(c->device), QEMU_G2H(c->output), QEMU_G2H(c->initData));
}

#endif

struct qemu_CreateICA
{
    struct qemu_syscall super;
    uint64_t driver;
    uint64_t device;
    uint64_t output;
    uint64_t initData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI CreateICA(LPCSTR driver, LPCSTR device, LPCSTR output, const DEVMODEA* initData)
{
    struct qemu_CreateICA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEICA);
    call.driver = (ULONG_PTR)driver;
    call.device = (ULONG_PTR)device;
    call.output = (ULONG_PTR)output;
    call.initData = (ULONG_PTR)initData;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateICA(struct qemu_syscall *call)
{
    struct qemu_CreateICA *c = (struct qemu_CreateICA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateICA(QEMU_G2H(c->driver), QEMU_G2H(c->device), QEMU_G2H(c->output), QEMU_G2H(c->initData));
}

#endif

struct qemu_CreateICW
{
    struct qemu_syscall super;
    uint64_t driver;
    uint64_t device;
    uint64_t output;
    uint64_t initData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI CreateICW(LPCWSTR driver, LPCWSTR device, LPCWSTR output, const DEVMODEW* initData)
{
    struct qemu_CreateICW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEICW);
    call.driver = (ULONG_PTR)driver;
    call.device = (ULONG_PTR)device;
    call.output = (ULONG_PTR)output;
    call.initData = (ULONG_PTR)initData;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateICW(struct qemu_syscall *call)
{
    struct qemu_CreateICW *c = (struct qemu_CreateICW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateICW(QEMU_G2H(c->driver), QEMU_G2H(c->device), QEMU_G2H(c->output), QEMU_G2H(c->initData));
}

#endif

struct qemu_CreateCompatibleDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI CreateCompatibleDC(HDC hdc)
{
    struct qemu_CreateCompatibleDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATECOMPATIBLEDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateCompatibleDC(struct qemu_syscall *call)
{
    struct qemu_CreateCompatibleDC *c = (struct qemu_CreateCompatibleDC *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateCompatibleDC((HDC)c->hdc);
}

#endif

struct qemu_DeleteDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI DeleteDC(HDC hdc)
{
    struct qemu_DeleteDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteDC(struct qemu_syscall *call)
{
    struct qemu_DeleteDC *c = (struct qemu_DeleteDC *)call;
    WINE_TRACE("\n");
    c->super.iret = DeleteDC((HDC)c->hdc);
}

#endif

struct qemu_ResetDCW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t devmode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI ResetDCW(HDC hdc, const DEVMODEW *devmode)
{
    struct qemu_ResetDCW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESETDCW);
    call.hdc = (ULONG_PTR)hdc;
    call.devmode = (ULONG_PTR)devmode;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ResetDCW(struct qemu_syscall *call)
{
    struct qemu_ResetDCW *c = (struct qemu_ResetDCW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ResetDCW(QEMU_G2H(c->hdc), QEMU_G2H(c->devmode));
}

#endif

struct qemu_ResetDCA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t devmode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HDC WINAPI ResetDCA(HDC hdc, const DEVMODEA *devmode)
{
    struct qemu_ResetDCA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESETDCA);
    call.hdc = (ULONG_PTR)hdc;
    call.devmode = (ULONG_PTR)devmode;

    qemu_syscall(&call.super);

    return (HDC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ResetDCA(struct qemu_syscall *call)
{
    struct qemu_ResetDCA *c = (struct qemu_ResetDCA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)ResetDCA(QEMU_G2H(c->hdc), QEMU_G2H(c->devmode));
}

#endif

struct qemu_GetDeviceCaps
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t cap;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetDeviceCaps(HDC hdc, INT cap)
{
    struct qemu_GetDeviceCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEVICECAPS);
    call.hdc = (ULONG_PTR)hdc;
    call.cap = (ULONG_PTR)cap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDeviceCaps(struct qemu_syscall *call)
{
    struct qemu_GetDeviceCaps *c = (struct qemu_GetDeviceCaps *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDeviceCaps(QEMU_G2H(c->hdc), c->cap);
}

#endif

struct qemu_GetBkColor
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI GetBkColor(HDC hdc)
{
    struct qemu_GetBkColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBKCOLOR);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBkColor(struct qemu_syscall *call)
{
    struct qemu_GetBkColor *c = (struct qemu_GetBkColor *)call;
    WINE_TRACE("\n");
    c->super.iret = GetBkColor(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetBkColor
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI SetBkColor(HDC hdc, COLORREF color)
{
    struct qemu_SetBkColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETBKCOLOR);
    call.hdc = (ULONG_PTR)hdc;
    call.color = color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetBkColor(struct qemu_syscall *call)
{
    struct qemu_SetBkColor *c = (struct qemu_SetBkColor *)call;
    WINE_TRACE("\n");
    c->super.iret = SetBkColor((HDC)c->hdc, c->color);
}

#endif

struct qemu_GetTextColor
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI GetTextColor(HDC hdc)
{
    struct qemu_GetTextColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTCOLOR);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextColor(struct qemu_syscall *call)
{
    struct qemu_GetTextColor *c = (struct qemu_GetTextColor *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextColor(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetTextColor
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI SetTextColor(HDC hdc, COLORREF color)
{
    struct qemu_SetTextColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTEXTCOLOR);
    call.hdc = (ULONG_PTR)hdc;
    call.color = color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTextColor(struct qemu_syscall *call)
{
    struct qemu_SetTextColor *c = (struct qemu_SetTextColor *)call;
    WINE_TRACE("\n");
    c->super.iret = SetTextColor((HDC)c->hdc, c->color);
}

#endif

struct qemu_GetTextAlign
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetTextAlign(HDC hdc)
{
    struct qemu_GetTextAlign call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTEXTALIGN);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTextAlign(struct qemu_syscall *call)
{
    struct qemu_GetTextAlign *c = (struct qemu_GetTextAlign *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTextAlign(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetTextAlign
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t align;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI SetTextAlign(HDC hdc, UINT align)
{
    struct qemu_SetTextAlign call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTEXTALIGN);
    call.hdc = (ULONG_PTR)hdc;
    call.align = (ULONG_PTR)align;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTextAlign(struct qemu_syscall *call)
{
    struct qemu_SetTextAlign *c = (struct qemu_SetTextAlign *)call;
    WINE_TRACE("\n");
    c->super.iret = SetTextAlign(QEMU_G2H(c->hdc), c->align);
}

#endif

struct qemu_GetDCOrgEx
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t lpp;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetDCOrgEx(HDC hDC, LPPOINT lpp)
{
    struct qemu_GetDCOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDCORGEX);
    call.hDC = (ULONG_PTR)hDC;
    call.lpp = (ULONG_PTR)lpp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDCOrgEx(struct qemu_syscall *call)
{
    struct qemu_GetDCOrgEx *c = (struct qemu_GetDCOrgEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDCOrgEx(QEMU_G2H(c->hDC), QEMU_G2H(c->lpp));
}

#endif

struct qemu_GetGraphicsMode
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetGraphicsMode(HDC hdc)
{
    struct qemu_GetGraphicsMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGRAPHICSMODE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGraphicsMode(struct qemu_syscall *call)
{
    struct qemu_GetGraphicsMode *c = (struct qemu_GetGraphicsMode *)call;
    WINE_TRACE("\n");
    c->super.iret = GetGraphicsMode(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetGraphicsMode
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetGraphicsMode(HDC hdc, INT mode)
{
    struct qemu_SetGraphicsMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETGRAPHICSMODE);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetGraphicsMode(struct qemu_syscall *call)
{
    struct qemu_SetGraphicsMode *c = (struct qemu_SetGraphicsMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetGraphicsMode(QEMU_G2H(c->hdc), c->mode);
}

#endif

struct qemu_GetArcDirection
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetArcDirection(HDC hdc)
{
    struct qemu_GetArcDirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETARCDIRECTION);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetArcDirection(struct qemu_syscall *call)
{
    struct qemu_GetArcDirection *c = (struct qemu_GetArcDirection *)call;
    WINE_TRACE("\n");
    c->super.iret = GetArcDirection(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetArcDirection
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetArcDirection(HDC hdc, INT dir)
{
    struct qemu_SetArcDirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETARCDIRECTION);
    call.hdc = (ULONG_PTR)hdc;
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetArcDirection(struct qemu_syscall *call)
{
    struct qemu_SetArcDirection *c = (struct qemu_SetArcDirection *)call;
    WINE_TRACE("\n");
    c->super.iret = SetArcDirection(QEMU_G2H(c->hdc), c->dir);
}

#endif

struct qemu_GetWorldTransform
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t xform;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetWorldTransform(HDC hdc, LPXFORM xform)
{
    struct qemu_GetWorldTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWORLDTRANSFORM);
    call.hdc = (ULONG_PTR)hdc;
    call.xform = (ULONG_PTR)xform;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWorldTransform(struct qemu_syscall *call)
{
    struct qemu_GetWorldTransform *c = (struct qemu_GetWorldTransform *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWorldTransform(QEMU_G2H(c->hdc), QEMU_G2H(c->xform));
}

#endif

struct qemu_GetTransform
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t which;
    uint64_t xform;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetTransform(HDC hdc, DWORD which, XFORM *xform)
{
    struct qemu_GetTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRANSFORM);
    call.hdc = (ULONG_PTR)hdc;
    call.which = (ULONG_PTR)which;
    call.xform = (ULONG_PTR)xform;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTransform(struct qemu_syscall *call)
{
    struct qemu_GetTransform *c = (struct qemu_GetTransform *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTransform(QEMU_G2H(c->hdc), c->which, QEMU_G2H(c->xform));
}

#endif

struct qemu_CombineTransform
{
    struct qemu_syscall super;
    uint64_t xformResult;
    uint64_t xform1;
    uint64_t xform2;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI CombineTransform(LPXFORM xformResult, const XFORM *xform1, const XFORM *xform2)
{
    struct qemu_CombineTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMBINETRANSFORM);
    call.xformResult = (ULONG_PTR)xformResult;
    call.xform1 = (ULONG_PTR)xform1;
    call.xform2 = (ULONG_PTR)xform2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CombineTransform(struct qemu_syscall *call)
{
    struct qemu_CombineTransform *c = (struct qemu_CombineTransform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CombineTransform(QEMU_G2H(c->xformResult), QEMU_G2H(c->xform1), QEMU_G2H(c->xform2));
}

#endif

struct qemu_SetHookFlags
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI WORD WINAPI SetHookFlags(HDC hdc, WORD flags)
{
    struct qemu_SetHookFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETHOOKFLAGS);
    call.hdc = (ULONG_PTR)hdc;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetHookFlags to Wine headers? */
extern WORD WINAPI SetHookFlags(HDC hdc, WORD flags);
void qemu_SetHookFlags(struct qemu_syscall *call)
{
    struct qemu_SetHookFlags *c = (struct qemu_SetHookFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetHookFlags(QEMU_G2H(c->hdc), c->flags);
}

#endif

struct qemu_SetICMMode
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t iEnableICM;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetICMMode(HDC hdc, INT iEnableICM)
{
    struct qemu_SetICMMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETICMMODE);
    call.hdc = (ULONG_PTR)hdc;
    call.iEnableICM = (ULONG_PTR)iEnableICM;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetICMMode(struct qemu_syscall *call)
{
    struct qemu_SetICMMode *c = (struct qemu_SetICMMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetICMMode(QEMU_G2H(c->hdc), c->iEnableICM);
}

#endif

struct qemu_GetDeviceGammaRamp
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetDeviceGammaRamp(HDC hDC, LPVOID ptr)
{
    struct qemu_GetDeviceGammaRamp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEVICEGAMMARAMP);
    call.hDC = (ULONG_PTR)hDC;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDeviceGammaRamp(struct qemu_syscall *call)
{
    struct qemu_GetDeviceGammaRamp *c = (struct qemu_GetDeviceGammaRamp *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDeviceGammaRamp(QEMU_G2H(c->hDC), QEMU_G2H(c->ptr));
}

#endif

struct qemu_SetDeviceGammaRamp
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetDeviceGammaRamp(HDC hDC, LPVOID ptr)
{
    struct qemu_SetDeviceGammaRamp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEVICEGAMMARAMP);
    call.hDC = (ULONG_PTR)hDC;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDeviceGammaRamp(struct qemu_syscall *call)
{
    struct qemu_SetDeviceGammaRamp *c = (struct qemu_SetDeviceGammaRamp *)call;
    WINE_TRACE("\n");
    c->super.iret = SetDeviceGammaRamp(QEMU_G2H(c->hDC), QEMU_G2H(c->ptr));
}

#endif

struct qemu_GetColorSpace
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HCOLORSPACE WINAPI GetColorSpace(HDC hdc)
{
    struct qemu_GetColorSpace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOLORSPACE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return (HCOLORSPACE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetColorSpace(struct qemu_syscall *call)
{
    struct qemu_GetColorSpace *c = (struct qemu_GetColorSpace *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetColorSpace(QEMU_G2H(c->hdc));
}

#endif

struct qemu_CreateColorSpaceA
{
    struct qemu_syscall super;
    uint64_t lpLogColorSpace;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HCOLORSPACE WINAPI CreateColorSpaceA(LPLOGCOLORSPACEA lpLogColorSpace)
{
    struct qemu_CreateColorSpaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATECOLORSPACEA);
    call.lpLogColorSpace = (ULONG_PTR)lpLogColorSpace;

    qemu_syscall(&call.super);

    return (HCOLORSPACE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateColorSpaceA(struct qemu_syscall *call)
{
    struct qemu_CreateColorSpaceA *c = (struct qemu_CreateColorSpaceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateColorSpaceA(QEMU_G2H(c->lpLogColorSpace));
}

#endif

struct qemu_CreateColorSpaceW
{
    struct qemu_syscall super;
    uint64_t lpLogColorSpace;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HCOLORSPACE WINAPI CreateColorSpaceW(LPLOGCOLORSPACEW lpLogColorSpace)
{
    struct qemu_CreateColorSpaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATECOLORSPACEW);
    call.lpLogColorSpace = (ULONG_PTR)lpLogColorSpace;

    qemu_syscall(&call.super);

    return (HCOLORSPACE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateColorSpaceW(struct qemu_syscall *call)
{
    struct qemu_CreateColorSpaceW *c = (struct qemu_CreateColorSpaceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateColorSpaceW(QEMU_G2H(c->lpLogColorSpace));
}

#endif

struct qemu_DeleteColorSpace
{
    struct qemu_syscall super;
    uint64_t hColorSpace;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI DeleteColorSpace(HCOLORSPACE hColorSpace)
{
    struct qemu_DeleteColorSpace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETECOLORSPACE);
    call.hColorSpace = (ULONG_PTR)hColorSpace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteColorSpace(struct qemu_syscall *call)
{
    struct qemu_DeleteColorSpace *c = (struct qemu_DeleteColorSpace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteColorSpace(QEMU_G2H(c->hColorSpace));
}

#endif

struct qemu_SetColorSpace
{
    struct qemu_syscall super;
    uint64_t hDC;
    uint64_t hColorSpace;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HCOLORSPACE WINAPI SetColorSpace(HDC hDC, HCOLORSPACE hColorSpace)
{
    struct qemu_SetColorSpace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOLORSPACE);
    call.hDC = (ULONG_PTR)hDC;
    call.hColorSpace = (ULONG_PTR)hColorSpace;

    qemu_syscall(&call.super);

    return (HCOLORSPACE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetColorSpace(struct qemu_syscall *call)
{
    struct qemu_SetColorSpace *c = (struct qemu_SetColorSpace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SetColorSpace(QEMU_G2H(c->hDC), QEMU_G2H(c->hColorSpace));
}

#endif

struct qemu_GetBoundsRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetBoundsRect(HDC hdc, LPRECT rect, UINT flags)
{
    struct qemu_GetBoundsRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBOUNDSRECT);
    call.hdc = (ULONG_PTR)hdc;
    call.rect = (ULONG_PTR)rect;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBoundsRect(struct qemu_syscall *call)
{
    struct qemu_GetBoundsRect *c = (struct qemu_GetBoundsRect *)call;
    WINE_TRACE("\n");
    c->super.iret = GetBoundsRect(QEMU_G2H(c->hdc), QEMU_G2H(c->rect), c->flags);
}

#endif

struct qemu_SetBoundsRect
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI SetBoundsRect(HDC hdc, const RECT* rect, UINT flags)
{
    struct qemu_SetBoundsRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETBOUNDSRECT);
    call.hdc = (ULONG_PTR)hdc;
    call.rect = (ULONG_PTR)rect;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetBoundsRect(struct qemu_syscall *call)
{
    struct qemu_SetBoundsRect *c = (struct qemu_SetBoundsRect *)call;
    WINE_TRACE("\n");
    c->super.iret = SetBoundsRect(QEMU_G2H(c->hdc), QEMU_G2H(c->rect), c->flags);
}

#endif

struct qemu_GetRelAbs
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t dwIgnore;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetRelAbs(HDC hdc, DWORD dwIgnore)
{
    struct qemu_GetRelAbs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETRELABS);
    call.hdc = (ULONG_PTR)hdc;
    call.dwIgnore = (ULONG_PTR)dwIgnore;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetRelAbs(struct qemu_syscall *call)
{
    struct qemu_GetRelAbs *c = (struct qemu_GetRelAbs *)call;
    WINE_TRACE("\n");
    c->super.iret = GetRelAbs(QEMU_G2H(c->hdc), c->dwIgnore);
}

#endif

struct qemu_GetBkMode
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetBkMode(HDC hdc)
{
    struct qemu_GetBkMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBKMODE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBkMode(struct qemu_syscall *call)
{
    struct qemu_GetBkMode *c = (struct qemu_GetBkMode *)call;
    WINE_TRACE("\n");
    c->super.iret = GetBkMode(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetBkMode
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetBkMode(HDC hdc, INT mode)
{
    struct qemu_SetBkMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETBKMODE);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetBkMode(struct qemu_syscall *call)
{
    struct qemu_SetBkMode *c = (struct qemu_SetBkMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetBkMode((HDC)c->hdc, c->mode);
}

#endif

struct qemu_GetROP2
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetROP2(HDC hdc)
{
    struct qemu_GetROP2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETROP2);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetROP2(struct qemu_syscall *call)
{
    struct qemu_GetROP2 *c = (struct qemu_GetROP2 *)call;
    WINE_TRACE("\n");
    c->super.iret = GetROP2(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetROP2
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetROP2(HDC hdc, INT mode)
{
    struct qemu_SetROP2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETROP2);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetROP2(struct qemu_syscall *call)
{
    struct qemu_SetROP2 *c = (struct qemu_SetROP2 *)call;
    WINE_TRACE("\n");
    c->super.iret = SetROP2(QEMU_G2H(c->hdc), c->mode);
}

#endif

struct qemu_SetRelAbs
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetRelAbs(HDC hdc, INT mode)
{
    struct qemu_SetRelAbs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETRELABS);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetRelAbs(struct qemu_syscall *call)
{
    struct qemu_SetRelAbs *c = (struct qemu_SetRelAbs *)call;
    WINE_TRACE("\n");
    c->super.iret = SetRelAbs(QEMU_G2H(c->hdc), c->mode);
}

#endif

struct qemu_GetPolyFillMode
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetPolyFillMode(HDC hdc)
{
    struct qemu_GetPolyFillMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPOLYFILLMODE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPolyFillMode(struct qemu_syscall *call)
{
    struct qemu_GetPolyFillMode *c = (struct qemu_GetPolyFillMode *)call;
    WINE_TRACE("\n");
    c->super.iret = GetPolyFillMode(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetPolyFillMode
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetPolyFillMode(HDC hdc, INT mode)
{
    struct qemu_SetPolyFillMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPOLYFILLMODE);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPolyFillMode(struct qemu_syscall *call)
{
    struct qemu_SetPolyFillMode *c = (struct qemu_SetPolyFillMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetPolyFillMode(QEMU_G2H(c->hdc), c->mode);
}

#endif

struct qemu_GetStretchBltMode
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetStretchBltMode(HDC hdc)
{
    struct qemu_GetStretchBltMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSTRETCHBLTMODE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetStretchBltMode(struct qemu_syscall *call)
{
    struct qemu_GetStretchBltMode *c = (struct qemu_GetStretchBltMode *)call;
    WINE_TRACE("\n");
    c->super.iret = GetStretchBltMode(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetStretchBltMode
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetStretchBltMode(HDC hdc, INT mode)
{
    struct qemu_SetStretchBltMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSTRETCHBLTMODE);
    call.hdc = (ULONG_PTR)hdc;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetStretchBltMode(struct qemu_syscall *call)
{
    struct qemu_SetStretchBltMode *c = (struct qemu_SetStretchBltMode *)call;
    WINE_TRACE("\n");
    c->super.iret = SetStretchBltMode(QEMU_G2H(c->hdc), c->mode);
}

#endif

struct qemu_GetMapMode
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI GetMapMode(HDC hdc)
{
    struct qemu_GetMapMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMAPMODE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMapMode(struct qemu_syscall *call)
{
    struct qemu_GetMapMode *c = (struct qemu_GetMapMode *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMapMode(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GetBrushOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetBrushOrgEx(HDC hdc, LPPOINT pt)
{
    struct qemu_GetBrushOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETBRUSHORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetBrushOrgEx(struct qemu_syscall *call)
{
    struct qemu_GetBrushOrgEx *c = (struct qemu_GetBrushOrgEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetBrushOrgEx(QEMU_G2H(c->hdc), QEMU_G2H(c->pt));
}

#endif

struct qemu_GetCurrentPositionEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetCurrentPositionEx(HDC hdc, LPPOINT pt)
{
    struct qemu_GetCurrentPositionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPOSITIONEX);
    call.hdc = (ULONG_PTR)hdc;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentPositionEx(struct qemu_syscall *call)
{
    struct qemu_GetCurrentPositionEx *c = (struct qemu_GetCurrentPositionEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCurrentPositionEx(QEMU_G2H(c->hdc), QEMU_G2H(c->pt));
}

#endif

struct qemu_GetViewportExtEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetViewportExtEx(HDC hdc, LPSIZE size)
{
    struct qemu_GetViewportExtEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVIEWPORTEXTEX);
    call.hdc = (ULONG_PTR)hdc;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetViewportExtEx(struct qemu_syscall *call)
{
    struct qemu_GetViewportExtEx *c = (struct qemu_GetViewportExtEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetViewportExtEx(QEMU_G2H(c->hdc), QEMU_G2H(c->size));
}

#endif

struct qemu_GetViewportOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetViewportOrgEx(HDC hdc, LPPOINT pt)
{
    struct qemu_GetViewportOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVIEWPORTORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetViewportOrgEx(struct qemu_syscall *call)
{
    struct qemu_GetViewportOrgEx *c = (struct qemu_GetViewportOrgEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetViewportOrgEx(QEMU_G2H(c->hdc), QEMU_G2H(c->pt));
}

#endif

struct qemu_GetWindowExtEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetWindowExtEx(HDC hdc, LPSIZE size)
{
    struct qemu_GetWindowExtEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWEXTEX);
    call.hdc = (ULONG_PTR)hdc;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowExtEx(struct qemu_syscall *call)
{
    struct qemu_GetWindowExtEx *c = (struct qemu_GetWindowExtEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowExtEx(QEMU_G2H(c->hdc), QEMU_G2H(c->size));
}

#endif

struct qemu_GetWindowOrgEx
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetWindowOrgEx(HDC hdc, LPPOINT pt)
{
    struct qemu_GetWindowOrgEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINDOWORGEX);
    call.hdc = (ULONG_PTR)hdc;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWindowOrgEx(struct qemu_syscall *call)
{
    struct qemu_GetWindowOrgEx *c = (struct qemu_GetWindowOrgEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWindowOrgEx(QEMU_G2H(c->hdc), QEMU_G2H(c->pt));
}

#endif

struct qemu_GetLayout
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GetLayout(HDC hdc)
{
    struct qemu_GetLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLAYOUT);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLayout(struct qemu_syscall *call)
{
    struct qemu_GetLayout *c = (struct qemu_GetLayout *)call;
    WINE_TRACE("\n");
    c->super.iret = GetLayout(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetLayout
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t layout;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI SetLayout(HDC hdc, DWORD layout)
{
    struct qemu_SetLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLAYOUT);
    call.hdc = (ULONG_PTR)hdc;
    call.layout = (ULONG_PTR)layout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetLayout(struct qemu_syscall *call)
{
    struct qemu_SetLayout *c = (struct qemu_SetLayout *)call;
    WINE_TRACE("\n");
    c->super.iret = SetLayout(QEMU_G2H(c->hdc), c->layout);
}

#endif

struct qemu_GetDCBrushColor
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI GetDCBrushColor(HDC hdc)
{
    struct qemu_GetDCBrushColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDCBRUSHCOLOR);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDCBrushColor(struct qemu_syscall *call)
{
    struct qemu_GetDCBrushColor *c = (struct qemu_GetDCBrushColor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDCBrushColor(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetDCBrushColor
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t crColor;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI SetDCBrushColor(HDC hdc, COLORREF crColor)
{
    struct qemu_SetDCBrushColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDCBRUSHCOLOR);
    call.hdc = (ULONG_PTR)hdc;
    call.crColor = (ULONG_PTR)crColor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDCBrushColor(struct qemu_syscall *call)
{
    struct qemu_SetDCBrushColor *c = (struct qemu_SetDCBrushColor *)call;
    WINE_TRACE("\n");
    c->super.iret = SetDCBrushColor(QEMU_G2H(c->hdc), c->crColor);
}

#endif

struct qemu_GetDCPenColor
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI GetDCPenColor(HDC hdc)
{
    struct qemu_GetDCPenColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDCPENCOLOR);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDCPenColor(struct qemu_syscall *call)
{
    struct qemu_GetDCPenColor *c = (struct qemu_GetDCPenColor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDCPenColor(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetDCPenColor
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t crColor;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI COLORREF WINAPI SetDCPenColor(HDC hdc, COLORREF crColor)
{
    struct qemu_SetDCPenColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDCPENCOLOR);
    call.hdc = (ULONG_PTR)hdc;
    call.crColor = (ULONG_PTR)crColor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDCPenColor(struct qemu_syscall *call)
{
    struct qemu_SetDCPenColor *c = (struct qemu_SetDCPenColor *)call;
    WINE_TRACE("\n");
    c->super.iret = SetDCPenColor(QEMU_G2H(c->hdc), c->crColor);
}

#endif

struct qemu_CancelDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI CancelDC(HDC hdc)
{
    struct qemu_CancelDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CANCELDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CancelDC to Wine headers? */
extern BOOL WINAPI CancelDC(HDC hdc);
void qemu_CancelDC(struct qemu_syscall *call)
{
    struct qemu_CancelDC *c = (struct qemu_CancelDC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CancelDC(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GetMiterLimit
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t peLimit;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GetMiterLimit(HDC hdc, PFLOAT peLimit)
{
    struct qemu_GetMiterLimit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMITERLIMIT);
    call.hdc = (ULONG_PTR)hdc;
    call.peLimit = (ULONG_PTR)peLimit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMiterLimit(struct qemu_syscall *call)
{
    struct qemu_GetMiterLimit *c = (struct qemu_GetMiterLimit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMiterLimit(QEMU_G2H(c->hdc), QEMU_G2H(c->peLimit));
}

#endif

struct qemu_SetMiterLimit
{
    struct qemu_syscall super;
    uint64_t hdc;
    double eNewLimit;
    uint64_t peOldLimit;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI SetMiterLimit(HDC hdc, FLOAT eNewLimit, PFLOAT peOldLimit)
{
    struct qemu_SetMiterLimit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMITERLIMIT);
    call.hdc = (ULONG_PTR)hdc;
    call.eNewLimit = eNewLimit;
    call.peOldLimit = (ULONG_PTR)peOldLimit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetMiterLimit(struct qemu_syscall *call)
{
    struct qemu_SetMiterLimit *c = (struct qemu_SetMiterLimit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetMiterLimit(QEMU_G2H(c->hdc), c->eNewLimit, QEMU_G2H(c->peOldLimit));
}

#endif

struct qemu_GdiIsMetaPrintDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GdiIsMetaPrintDC(HDC hdc)
{
    struct qemu_GdiIsMetaPrintDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIISMETAPRINTDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiIsMetaPrintDC(struct qemu_syscall *call)
{
    struct qemu_GdiIsMetaPrintDC *c = (struct qemu_GdiIsMetaPrintDC *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiIsMetaPrintDC(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GdiIsMetaFileDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GdiIsMetaFileDC(HDC hdc)
{
    struct qemu_GdiIsMetaFileDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIISMETAFILEDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiIsMetaFileDC(struct qemu_syscall *call)
{
    struct qemu_GdiIsMetaFileDC *c = (struct qemu_GdiIsMetaFileDC *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiIsMetaFileDC(QEMU_G2H(c->hdc));
}

#endif

struct qemu_GdiIsPlayMetafileDC
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI GdiIsPlayMetafileDC(HDC hdc)
{
    struct qemu_GdiIsPlayMetafileDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIISPLAYMETAFILEDC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GdiIsPlayMetafileDC(struct qemu_syscall *call)
{
    struct qemu_GdiIsPlayMetafileDC *c = (struct qemu_GdiIsPlayMetafileDC *)call;
    WINE_TRACE("\n");
    c->super.iret = GdiIsPlayMetafileDC(QEMU_G2H(c->hdc));
}

#endif

