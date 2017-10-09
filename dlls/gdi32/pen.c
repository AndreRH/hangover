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


struct qemu_CreatePen
{
    struct qemu_syscall super;
    uint64_t style;
    uint64_t width;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPEN WINAPI CreatePen(INT style, INT width, COLORREF color)
{
    struct qemu_CreatePen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPEN);
    call.style = (ULONG_PTR)style;
    call.width = (ULONG_PTR)width;
    call.color = (ULONG_PTR)color;

    qemu_syscall(&call.super);

    return (HPEN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePen(struct qemu_syscall *call)
{
    struct qemu_CreatePen *c = (struct qemu_CreatePen *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreatePen(c->style, c->width, c->color);
}

#endif

struct qemu_CreatePenIndirect
{
    struct qemu_syscall super;
    uint64_t pen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPEN WINAPI CreatePenIndirect(const LOGPEN * pen)
{
    struct qemu_CreatePenIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPENINDIRECT);
    call.pen = (ULONG_PTR)pen;

    qemu_syscall(&call.super);

    return (HPEN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePenIndirect(struct qemu_syscall *call)
{
    struct qemu_CreatePenIndirect *c = (struct qemu_CreatePenIndirect *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreatePenIndirect(QEMU_G2H(c->pen));
}

#endif

struct qemu_ExtCreatePen
{
    struct qemu_syscall super;
    uint64_t style;
    uint64_t width;
    uint64_t brush;
    uint64_t style_count;
    uint64_t style_bits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPEN WINAPI ExtCreatePen(DWORD style, DWORD width, const LOGBRUSH * brush, DWORD style_count, const DWORD *style_bits)
{
    struct qemu_ExtCreatePen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTCREATEPEN);
    call.style = (ULONG_PTR)style;
    call.width = (ULONG_PTR)width;
    call.brush = (ULONG_PTR)brush;
    call.style_count = (ULONG_PTR)style_count;
    call.style_bits = (ULONG_PTR)style_bits;

    qemu_syscall(&call.super);

    return (HPEN)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ExtCreatePen(struct qemu_syscall *call)
{
    struct qemu_ExtCreatePen *c = (struct qemu_ExtCreatePen *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)ExtCreatePen(c->style, c->width, QEMU_G2H(c->brush), c->style_count, QEMU_G2H(c->style_bits));
}

#endif

