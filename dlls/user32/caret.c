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


struct qemu_CreateCaret
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t bitmap;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CreateCaret(HWND hwnd, HBITMAP bitmap, INT width, INT height)
{
    struct qemu_CreateCaret call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATECARET);
    call.hwnd = (ULONG_PTR)hwnd;
    call.bitmap = (ULONG_PTR)bitmap;
    call.width = (ULONG_PTR)width;
    call.height = (ULONG_PTR)height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateCaret(struct qemu_syscall *call)
{
    struct qemu_CreateCaret *c = (struct qemu_CreateCaret *)call;
    WINE_TRACE("\n");
    c->super.iret = CreateCaret(QEMU_G2H(c->hwnd), QEMU_G2H(c->bitmap), c->width, c->height);
}

#endif

struct qemu_DestroyCaret
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DestroyCaret(void)
{
    struct qemu_DestroyCaret call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESTROYCARET);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyCaret(struct qemu_syscall *call)
{
    struct qemu_DestroyCaret *c = (struct qemu_DestroyCaret *)call;
    WINE_TRACE("\n");
    c->super.iret = DestroyCaret();
}

#endif

struct qemu_SetCaretPos
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetCaretPos(INT x, INT y)
{
    struct qemu_SetCaretPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCARETPOS);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCaretPos(struct qemu_syscall *call)
{
    struct qemu_SetCaretPos *c = (struct qemu_SetCaretPos *)call;
    WINE_TRACE("\n");
    c->super.iret = SetCaretPos(c->x, c->y);
}

#endif

struct qemu_HideCaret
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI HideCaret(HWND hwnd)
{
    struct qemu_HideCaret call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HIDECARET);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HideCaret(struct qemu_syscall *call)
{
    struct qemu_HideCaret *c = (struct qemu_HideCaret *)call;
    WINE_TRACE("\n");
    c->super.iret = HideCaret(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_ShowCaret
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShowCaret(HWND hwnd)
{
    struct qemu_ShowCaret call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWCARET);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShowCaret(struct qemu_syscall *call)
{
    struct qemu_ShowCaret *c = (struct qemu_ShowCaret *)call;
    WINE_TRACE("\n");
    c->super.iret = ShowCaret(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetCaretPos
{
    struct qemu_syscall super;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetCaretPos(LPPOINT pt)
{
    struct qemu_GetCaretPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCARETPOS);
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCaretPos(struct qemu_syscall *call)
{
    struct qemu_GetCaretPos *c = (struct qemu_GetCaretPos *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCaretPos(QEMU_G2H(c->pt));
}

#endif

struct qemu_SetCaretBlinkTime
{
    struct qemu_syscall super;
    uint64_t msecs;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetCaretBlinkTime(UINT msecs)
{
    struct qemu_SetCaretBlinkTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCARETBLINKTIME);
    call.msecs = (ULONG_PTR)msecs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCaretBlinkTime(struct qemu_syscall *call)
{
    struct qemu_SetCaretBlinkTime *c = (struct qemu_SetCaretBlinkTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCaretBlinkTime(c->msecs);
}

#endif

struct qemu_GetCaretBlinkTime
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetCaretBlinkTime(void)
{
    struct qemu_GetCaretBlinkTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCARETBLINKTIME);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCaretBlinkTime(struct qemu_syscall *call)
{
    struct qemu_GetCaretBlinkTime *c = (struct qemu_GetCaretBlinkTime *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCaretBlinkTime();
}

#endif

