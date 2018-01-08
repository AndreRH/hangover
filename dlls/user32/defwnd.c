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


struct qemu_DefWindowProcA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefWindowProcA(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefWindowProcA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFWINDOWPROCA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefWindowProcA(struct qemu_syscall *call)
{
    struct qemu_DefWindowProcA *c = (struct qemu_DefWindowProcA *)call;
    MSG msg_in = {(HWND)c->hwnd, c->msg, c->wParam, c->lParam};
    MSG msg_out;
    WINE_TRACE("\n");

    msg_guest_to_host(&msg_out, &msg_in);
    c->super.iret = DefWindowProcA(msg_out.hwnd, msg_out.message, msg_out.wParam, msg_out.lParam);
    msg_guest_to_host_return(&msg_in, &msg_out);
}

#endif

struct qemu_DefWindowProcW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI DefWindowProcW(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_DefWindowProcW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFWINDOWPROCW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefWindowProcW(struct qemu_syscall *call)
{
    struct qemu_DefWindowProcW *c = (struct qemu_DefWindowProcW *)call;
    WINE_TRACE("\n");
    MSG msg_in = {(HWND)c->hwnd, c->msg, c->wParam, c->lParam};
    MSG msg_out;

    msg_guest_to_host(&msg_out, &msg_in);
    c->super.iret = DefWindowProcW(msg_out.hwnd, msg_out.message, msg_out.wParam, msg_out.lParam);
    msg_guest_to_host_return(&msg_in, &msg_out);
}

#endif

