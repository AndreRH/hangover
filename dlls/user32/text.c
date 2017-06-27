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


struct qemu_DrawTextExW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t i_count;
    uint64_t rect;
    uint64_t flags;
    uint64_t dtp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DrawTextExW(HDC hdc, LPWSTR str, INT i_count, LPRECT rect, UINT flags, LPDRAWTEXTPARAMS dtp)
{
    struct qemu_DrawTextExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWTEXTEXW);
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.i_count = (uint64_t)i_count;
    call.rect = (uint64_t)rect;
    call.flags = (uint64_t)flags;
    call.dtp = (uint64_t)dtp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawTextExW(struct qemu_syscall *call)
{
    struct qemu_DrawTextExW *c = (struct qemu_DrawTextExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawTextExW(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->i_count, QEMU_G2H(c->rect), c->flags, QEMU_G2H(c->dtp));
}

#endif

struct qemu_DrawTextExA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t rect;
    uint64_t flags;
    uint64_t dtp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DrawTextExA(HDC hdc, LPSTR str, INT count, LPRECT rect, UINT flags, LPDRAWTEXTPARAMS dtp)
{
    struct qemu_DrawTextExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWTEXTEXA);
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.rect = (uint64_t)rect;
    call.flags = (uint64_t)flags;
    call.dtp = (uint64_t)dtp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawTextExA(struct qemu_syscall *call)
{
    struct qemu_DrawTextExA *c = (struct qemu_DrawTextExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawTextExA(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->rect), c->flags, QEMU_G2H(c->dtp));
}

#endif

struct qemu_DrawTextW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DrawTextW(HDC hdc, LPCWSTR str, INT count, LPRECT rect, UINT flags)
{
    struct qemu_DrawTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWTEXTW);
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.rect = (uint64_t)rect;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawTextW(struct qemu_syscall *call)
{
    struct qemu_DrawTextW *c = (struct qemu_DrawTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawTextW(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->rect), c->flags);
}

#endif

struct qemu_DrawTextA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t str;
    uint64_t count;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI DrawTextA(HDC hdc, LPCSTR str, INT count, LPRECT rect, UINT flags)
{
    struct qemu_DrawTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWTEXTA);
    call.hdc = (uint64_t)hdc;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.rect = (uint64_t)rect;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawTextA(struct qemu_syscall *call)
{
    struct qemu_DrawTextA *c = (struct qemu_DrawTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawTextA(QEMU_G2H(c->hdc), QEMU_G2H(c->str), c->count, QEMU_G2H(c->rect), c->flags);
}

#endif

struct qemu_GrayStringA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hbr;
    uint64_t gsprc;
    uint64_t lParam;
    uint64_t cch;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GrayStringA(HDC hdc, HBRUSH hbr, GRAYSTRINGPROC gsprc, LPARAM lParam, INT cch, INT x, INT y, INT cx, INT cy)
{
    struct qemu_GrayStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GRAYSTRINGA);
    call.hdc = (uint64_t)hdc;
    call.hbr = (uint64_t)hbr;
    call.gsprc = (uint64_t)gsprc;
    call.lParam = (uint64_t)lParam;
    call.cch = (uint64_t)cch;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GrayStringA(struct qemu_syscall *call)
{
    struct qemu_GrayStringA *c = (struct qemu_GrayStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GrayStringA(QEMU_G2H(c->hdc), QEMU_G2H(c->hbr), QEMU_G2H(c->gsprc), c->lParam, c->cch, c->x, c->y, c->cx, c->cy);
}

#endif

struct qemu_GrayStringW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hbr;
    uint64_t gsprc;
    uint64_t lParam;
    uint64_t cch;
    uint64_t x;
    uint64_t y;
    uint64_t cx;
    uint64_t cy;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GrayStringW(HDC hdc, HBRUSH hbr, GRAYSTRINGPROC gsprc, LPARAM lParam, INT cch, INT x, INT y, INT cx, INT cy)
{
    struct qemu_GrayStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GRAYSTRINGW);
    call.hdc = (uint64_t)hdc;
    call.hbr = (uint64_t)hbr;
    call.gsprc = (uint64_t)gsprc;
    call.lParam = (uint64_t)lParam;
    call.cch = (uint64_t)cch;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.cx = (uint64_t)cx;
    call.cy = (uint64_t)cy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GrayStringW(struct qemu_syscall *call)
{
    struct qemu_GrayStringW *c = (struct qemu_GrayStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GrayStringW(QEMU_G2H(c->hdc), QEMU_G2H(c->hbr), QEMU_G2H(c->gsprc), c->lParam, c->cch, c->x, c->y, c->cx, c->cy);
}

#endif

struct qemu_TabbedTextOutA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t lpstr;
    uint64_t count;
    uint64_t cTabStops;
    uint64_t lpTabPos;
    uint64_t nTabOrg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI TabbedTextOutA(HDC hdc, INT x, INT y, LPCSTR lpstr, INT count, INT cTabStops, const INT *lpTabPos, INT nTabOrg)
{
    struct qemu_TabbedTextOutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TABBEDTEXTOUTA);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.lpstr = (uint64_t)lpstr;
    call.count = (uint64_t)count;
    call.cTabStops = (uint64_t)cTabStops;
    call.lpTabPos = (uint64_t)lpTabPos;
    call.nTabOrg = (uint64_t)nTabOrg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TabbedTextOutA(struct qemu_syscall *call)
{
    struct qemu_TabbedTextOutA *c = (struct qemu_TabbedTextOutA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TabbedTextOutA(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->lpstr), c->count, c->cTabStops, QEMU_G2H(c->lpTabPos), c->nTabOrg);
}

#endif

struct qemu_TabbedTextOutW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t x;
    uint64_t y;
    uint64_t str;
    uint64_t count;
    uint64_t cTabStops;
    uint64_t lpTabPos;
    uint64_t nTabOrg;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI TabbedTextOutW(HDC hdc, INT x, INT y, LPCWSTR str, INT count, INT cTabStops, const INT *lpTabPos, INT nTabOrg)
{
    struct qemu_TabbedTextOutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TABBEDTEXTOUTW);
    call.hdc = (uint64_t)hdc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.str = (uint64_t)str;
    call.count = (uint64_t)count;
    call.cTabStops = (uint64_t)cTabStops;
    call.lpTabPos = (uint64_t)lpTabPos;
    call.nTabOrg = (uint64_t)nTabOrg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TabbedTextOutW(struct qemu_syscall *call)
{
    struct qemu_TabbedTextOutW *c = (struct qemu_TabbedTextOutW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TabbedTextOutW(QEMU_G2H(c->hdc), c->x, c->y, QEMU_G2H(c->str), c->count, c->cTabStops, QEMU_G2H(c->lpTabPos), c->nTabOrg);
}

#endif

struct qemu_GetTabbedTextExtentA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpstr;
    uint64_t count;
    uint64_t cTabStops;
    uint64_t lpTabPos;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetTabbedTextExtentA(HDC hdc, LPCSTR lpstr, INT count, INT cTabStops, const INT *lpTabPos)
{
    struct qemu_GetTabbedTextExtentA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTABBEDTEXTEXTENTA);
    call.hdc = (uint64_t)hdc;
    call.lpstr = (uint64_t)lpstr;
    call.count = (uint64_t)count;
    call.cTabStops = (uint64_t)cTabStops;
    call.lpTabPos = (uint64_t)lpTabPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTabbedTextExtentA(struct qemu_syscall *call)
{
    struct qemu_GetTabbedTextExtentA *c = (struct qemu_GetTabbedTextExtentA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTabbedTextExtentA(QEMU_G2H(c->hdc), QEMU_G2H(c->lpstr), c->count, c->cTabStops, QEMU_G2H(c->lpTabPos));
}

#endif

struct qemu_GetTabbedTextExtentW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lpstr;
    uint64_t count;
    uint64_t cTabStops;
    uint64_t lpTabPos;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetTabbedTextExtentW(HDC hdc, LPCWSTR lpstr, INT count, INT cTabStops, const INT *lpTabPos)
{
    struct qemu_GetTabbedTextExtentW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTABBEDTEXTEXTENTW);
    call.hdc = (uint64_t)hdc;
    call.lpstr = (uint64_t)lpstr;
    call.count = (uint64_t)count;
    call.cTabStops = (uint64_t)cTabStops;
    call.lpTabPos = (uint64_t)lpTabPos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTabbedTextExtentW(struct qemu_syscall *call)
{
    struct qemu_GetTabbedTextExtentW *c = (struct qemu_GetTabbedTextExtentW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTabbedTextExtentW(QEMU_G2H(c->hdc), QEMU_G2H(c->lpstr), c->count, c->cTabStops, QEMU_G2H(c->lpTabPos));
}

#endif

