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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif

struct qemu_CallWindowProcA
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#define WINPROC_HANDLE (~0u >> 16)

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI CallWindowProcA(WNDPROC func, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_CallWindowProcA call;

    if (!func)
        return 0;

    /* Most of the time we'll deal with a WINDOWPROC handle. Forward it to native, as it
     * has the lookup table, and we have a stable guest -> host mapping. For everything
     * that is not a handle just call it.
     *
     * TODO: We may be able to improve performance if we keep track of which handles map
     * to a WNDPROC provided by the guest app and call it here directly instead of going
     * out of the VM to Wine's CallWindowProc and back in. That will require duplicating
     * the ASCII <-> Unicode mapping. */
    if (!wndproc_is_handle((LONG_PTR)func))
        return func(hwnd, msg, wParam, lParam);

    call.super.id = QEMU_SYSCALL_ID(CALL_CALLWINDOWPROCA);
    call.func = (ULONG_PTR)func;
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = msg;
    call.wParam = wParam;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallWindowProcA(struct qemu_syscall *call)
{
    struct qemu_CallWindowProcA *c = (struct qemu_CallWindowProcA *)call;
    WINE_TRACE("\n");
    c->super.iret = CallWindowProcA(QEMU_G2H(c->func), QEMU_G2H(c->hwnd), c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_CallWindowProcW
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI CallWindowProcW(WNDPROC func, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_CallWindowProcW call;

    if (!func)
        return 0;
    if (!wndproc_is_handle((LONG_PTR)func))
        return func(hwnd, msg, wParam, lParam);

    call.super.id = QEMU_SYSCALL_ID(CALL_CALLWINDOWPROCW);
    call.func = (ULONG_PTR)func;
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = msg;
    call.wParam = wParam;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallWindowProcW(struct qemu_syscall *call)
{
    struct qemu_CallWindowProcW *c = (struct qemu_CallWindowProcW *)call;
    WINE_TRACE("\n");
    c->super.iret = CallWindowProcW(QEMU_G2H(c->func), QEMU_G2H(c->hwnd), c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_UserRegisterWowHandlers
{
    struct qemu_syscall super;
    uint64_t new;
    uint64_t orig;
};

struct wow_handlers32;
struct wow_handlers16;

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI UserRegisterWowHandlers(const struct wow_handlers16 *new, struct wow_handlers32 *orig)
{
    struct qemu_UserRegisterWowHandlers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERREGISTERWOWHANDLERS);
    call.new = (ULONG_PTR)new;
    call.orig = (ULONG_PTR)orig;

    qemu_syscall(&call.super);
}

#else

extern void WINAPI UserRegisterWowHandlers(const struct wow_handlers16 *new, struct wow_handlers32 *orig);
void qemu_UserRegisterWowHandlers(struct qemu_syscall *call)
{
    struct qemu_UserRegisterWowHandlers *c = (struct qemu_UserRegisterWowHandlers *)call;
    WINE_FIXME("Unverified!\n");
    UserRegisterWowHandlers(QEMU_G2H(c->new), QEMU_G2H(c->orig));
}

#endif
struct qemu_EditWndProcA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI EditWndProcA(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_EditWndProcA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EDITWNDPROCA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = msg;
    call.wParam = wParam;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern LRESULT WINAPI EditWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void qemu_EditWndProcA(struct qemu_syscall *call)
{
    struct qemu_EditWndProcA *c = (struct qemu_EditWndProcA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EditWndProc(QEMU_G2H(c->hwnd), c->msg, c->wParam, c->lParam);
}

#endif
