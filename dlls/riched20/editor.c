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
#include <richedit.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_riched20.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_riched20);
#endif


struct qemu_REExtendedRegisterClass
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI REExtendedRegisterClass(void)
{
    struct qemu_REExtendedRegisterClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REEXTENDEDREGISTERCLASS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add REExtendedRegisterClass to Wine headers? */
void qemu_REExtendedRegisterClass(struct qemu_syscall *call)
{
    struct qemu_REExtendedRegisterClass *c = (struct qemu_REExtendedRegisterClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = pREExtendedRegisterClass();
}

#endif

struct qemu_RichEdit10ANSIWndProc
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI RichEdit10ANSIWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_RichEdit10ANSIWndProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RICHEDIT10ANSIWNDPROC);
    call.hWnd = (ULONG_PTR)hWnd;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RichEdit10ANSIWndProc to Wine headers? */
extern LRESULT WINAPI RichEdit10ANSIWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void qemu_RichEdit10ANSIWndProc(struct qemu_syscall *call)
{
    struct qemu_RichEdit10ANSIWndProc *c = (struct qemu_RichEdit10ANSIWndProc *)call;
    HWND window;
    WINE_FIXME("Unverified!\n");

    window = QEMU_G2H(c->hWnd);
    c->super.iret = wrap_proc_10a(window, c->msg, c->wParam, c->lParam);
}

#endif

struct qemu_RichEditANSIWndProc
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t msg;
    uint64_t wParam;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI RichEditANSIWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    struct qemu_RichEditANSIWndProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RICHEDITANSIWNDPROC);
    call.hWnd = (ULONG_PTR)hWnd;
    call.msg = (ULONG_PTR)msg;
    call.wParam = (ULONG_PTR)wParam;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RichEditANSIWndProc(struct qemu_syscall *call)
{
    struct qemu_RichEditANSIWndProc *c = (struct qemu_RichEditANSIWndProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = wrap_proc_a(QEMU_G2H(c->hWnd), c->msg, c->wParam, c->lParam);
}

#endif

