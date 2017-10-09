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
#include "qemu_comdlg32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);
#endif


struct qemu_ChooseColorW
{
    struct qemu_syscall super;
    uint64_t lpChCol;
    uint64_t guest_wrapper;
};

struct qemu_ChooseColorW_cb
{
    uint64_t guest_proc;
    uint64_t dlg, msg, wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t guest_wrapper(const struct qemu_ChooseColorW_cb *cb)
{
    LPCCHOOKPROC guest_proc = (LPCCHOOKPROC)cb->guest_proc;
    return guest_proc((HWND)cb->dlg, cb->msg, cb->wp, cb->lp);
}

WINBASEAPI BOOL WINAPI ChooseColorW(CHOOSECOLORW *lpChCol)
{
    struct qemu_ChooseColorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSECOLORW);
    call.lpChCol = (uint64_t)lpChCol;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t guest_wrapper;

static UINT_PTR CALLBACK hook_proc_wrapper(HWND dlg, UINT msg, WPARAM wp, LPARAM lp)
{
    struct qemu_ChooseColorW_cb call;
    uint64_t *guest_proc = TlsGetValue(comdlg32_tls);
    UINT_PTR ret;

    WINE_TRACE("Calling guest proc 0x%lx(%p, %u, %lu, %lu).\n", *guest_proc, dlg, msg, wp, lp);
    call.guest_proc = *guest_proc;
    call.dlg = (uint64_t)dlg;
    call.msg = msg;
    call.wp = wp;
    call.lp = lp;

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest proc returned %lu\n", ret);
    return ret;
}

void qemu_ChooseColorW(struct qemu_syscall *call)
{
    struct qemu_ChooseColorW *c = (struct qemu_ChooseColorW *)call;
    uint64_t *old_tls, guest_proc;
    HWND instance;
    CHOOSECOLORW choose;

    WINE_TRACE("\n");
    choose = *(CHOOSECOLORW *)QEMU_G2H(c->lpChCol);
    choose.lStructSize = sizeof(choose);

    guest_proc = (uint64_t)choose.lpfnHook;
    choose.lpfnHook = guest_proc ? hook_proc_wrapper : NULL;
    guest_wrapper = c->guest_wrapper;

    instance = choose.hInstance;
    if (choose.Flags & (CC_ENABLETEMPLATEHANDLE | CC_ENABLETEMPLATE) == CC_ENABLETEMPLATE && !choose.hInstance)
    {
        choose.hInstance = (void *)qemu_ops->qemu_GetModuleHandleEx(
                GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);
    }

    old_tls = TlsGetValue(comdlg32_tls);
    TlsSetValue(comdlg32_tls, &guest_proc);

    c->super.iret = ChooseColorW(&choose);

    choose.hInstance = instance;
    choose.lpfnHook = (void *)guest_proc;
    *(CHOOSECOLORW *)QEMU_G2H(c->lpChCol) = choose;

    TlsSetValue(comdlg32_tls, old_tls);
}

#endif

struct qemu_ChooseColorA
{
    struct qemu_syscall super;
    uint64_t lpChCol;
    uint64_t guest_wrapper;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChooseColorA(LPCHOOSECOLORA lpChCol)
{
    struct qemu_ChooseColorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSECOLORA);
    call.lpChCol = (uint64_t)lpChCol;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChooseColorA(struct qemu_syscall *call)
{
    struct qemu_ChooseColorA *c = (struct qemu_ChooseColorA *)call;
    uint64_t *old_tls, guest_proc;
    HWND instance;
    CHOOSECOLORA choose;

    WINE_TRACE("\n");
    choose = *(CHOOSECOLORA *)QEMU_G2H(c->lpChCol);
    choose.lStructSize = sizeof(choose);

    guest_proc = (uint64_t)choose.lpfnHook;
    choose.lpfnHook = guest_proc ? hook_proc_wrapper : NULL;
    guest_wrapper = c->guest_wrapper;

    instance = choose.hInstance;
    if (choose.Flags & (CC_ENABLETEMPLATEHANDLE | CC_ENABLETEMPLATE) == CC_ENABLETEMPLATE && !choose.hInstance)
    {
        choose.hInstance = (void *)qemu_ops->qemu_GetModuleHandleEx(
                GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);
    }

    old_tls = TlsGetValue(comdlg32_tls);
    TlsSetValue(comdlg32_tls, &guest_proc);

    c->super.iret = ChooseColorA(&choose);

    choose.hInstance = instance;
    choose.lpfnHook = (void *)guest_proc;
    *(CHOOSECOLORA *)QEMU_G2H(c->lpChCol) = choose;

    TlsSetValue(comdlg32_tls, old_tls);
}

#endif

