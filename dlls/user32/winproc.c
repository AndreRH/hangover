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
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLWINDOWPROCA);

    /* For logging. */
    qemu_syscall(&call.super);

    /* My understanding is that this function does two things: It fixes up some CPU registers for apps that
     * write non-compliant window procs, and it does WOW16 wrapping in a similar fashion to what we're doing
     * here. The first part is unimplemented and only necessary on 32 bit. It is easy to copypaste later. The
     * other part won't matter until we have 16 bit in 32 bit support.
     *
     * So for now replicate the NULL ptr check and call func. */
    if (!func) return 0;

    return func(hwnd, msg, wParam, lParam);
}

#else

void qemu_CallWindowProcA(struct qemu_syscall *call)
{
    struct qemu_CallWindowProcA *c = (struct qemu_CallWindowProcA *)call;
    WINE_TRACE("\n");
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
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLWINDOWPROCW);

    /* For logging. */
    qemu_syscall(&call.super);

    /* My understanding is that this function does two things: It fixes up some CPU registers for apps that
     * write non-compliant window procs, and it does WOW16 wrapping in a similar fashion to what we're doing
     * here. The first part is unimplemented and only necessary on 32 bit. It is easy to copypaste later. The
     * other part won't matter until we have 16 bit in 32 bit support.
     *
     * So for now replicate the NULL ptr check and call func. */
    if (!func) return 0;

    return func(hwnd, msg, wParam, lParam);
}

#else

void qemu_CallWindowProcW(struct qemu_syscall *call)
{
    struct qemu_CallWindowProcW *c = (struct qemu_CallWindowProcW *)call;
    WINE_TRACE("\n");
}

#endif

