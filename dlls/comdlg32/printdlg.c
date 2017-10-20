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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comdlg32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);
#endif

struct qemu_PrintDlgA
{
    struct qemu_syscall super;
    uint64_t lppd;
    uint64_t wrapper;
};

struct qemu_PrintDlgA_cb
{
    uint64_t guest_proc;
    uint64_t dlg, msg, wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall guest_wrapper(const struct qemu_PrintDlgA_cb *cb)
{
    LPPRINTHOOKPROC guest_proc = (LPPRINTHOOKPROC)(ULONG_PTR)cb->guest_proc;
    return guest_proc((HWND)(ULONG_PTR)cb->dlg, cb->msg, cb->wp, cb->lp);
}

WINBASEAPI BOOL WINAPI PrintDlgA(LPPRINTDLGA lppd)
{
    struct qemu_PrintDlgA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTDLGA);
    call.lppd = (ULONG_PTR)lppd;
    call.wrapper = (ULONG_PTR)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t guest_wrapper;

static UINT_PTR CALLBACK print_hook_proc(HWND hdlg, UINT msg, WPARAM wp, LPARAM lp)
{
    struct qemu_PrintDlgA_cb call_local, *call = &call_local;
    uint64_t *guest_proc = TlsGetValue(comdlg32_tls);
    UINT_PTR ret;

#if HOST_BIT != GUEST_BIT
    call = HeapAlloc(GetProcessHeap(), 0, sizeof(*call));
#endif

    WINE_TRACE("Calling guest proc 0x%lx(%p, %x, %lu, %lu).\n", *guest_proc, hdlg, msg, wp, lp);
    call->guest_proc = *guest_proc;
    call->dlg = (ULONG_PTR)hdlg;
    call->msg = msg;
    call->wp = wp;
    call->lp = lp;

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wrapper), QEMU_H2G(call));
    WINE_TRACE("Guest proc returned %lu\n", ret);

    if (call != &call_local)
    {
        HeapFree(GetProcessHeap(), 0, call);
    }

    return ret;
}

void qemu_PrintDlgA(struct qemu_syscall *call)
{
    struct qemu_PrintDlgA *c = (struct qemu_PrintDlgA *)call;
    PRINTDLGA copy;
    uint64_t print_hook, *old_hook = TlsGetValue(comdlg32_tls);
    WINE_TRACE("\n");

    if (!c->lppd)
    {
        c->super.iret = PrintDlgA(NULL);
        return;
    }

    guest_wrapper = c->wrapper;

#if HOST_BIT == GUEST_BIT
        copy = *(PRINTDLGA *)QEMU_G2H(c->lppd);
#else
        PRINTDLG_g2h((PRINTDLGW *)&copy, QEMU_G2H(c->lppd));
        copy.lCustData = (LPARAM)QEMU_G2H(c->lppd);
#endif

    print_hook = (ULONG_PTR)copy.lpfnPrintHook;
    TlsSetValue(comdlg32_tls, &print_hook);
    if (print_hook)
        copy.lpfnPrintHook = print_hook_proc;

    if (copy.lpfnSetupHook)
        WINE_FIXME("Implement a setup hook wrapper.\n");

    c->super.iret = PrintDlgA(&copy);

    TlsSetValue(comdlg32_tls, &old_hook);
    copy.lpfnPrintHook = (LPPRINTHOOKPROC)print_hook;

#if HOST_BIT == GUEST_BIT
    *(PRINTDLGA *)QEMU_G2H(c->lppd) = copy;
#else
    PRINTDLG_h2g(QEMU_G2H(c->lppd), (PRINTDLGW *)&copy);
#endif
}

#endif

struct qemu_PrintDlgW
{
    struct qemu_syscall super;
    uint64_t lppd;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrintDlgW(LPPRINTDLGW lppd)
{
    struct qemu_PrintDlgW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTDLGW);
    call.lppd = (ULONG_PTR)lppd;
    call.wrapper = (ULONG_PTR)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrintDlgW(struct qemu_syscall *call)
{
    struct qemu_PrintDlgW *c = (struct qemu_PrintDlgW *)call;
    PRINTDLGW copy;
    uint64_t print_hook, *old_hook = TlsGetValue(comdlg32_tls);
    WINE_TRACE("\n");

    if (!c->lppd)
    {
        c->super.iret = PrintDlgW(NULL);
        return;
    }

    guest_wrapper = c->wrapper;

#if HOST_BIT == GUEST_BIT
    copy = *(PRINTDLGW *)QEMU_G2H(c->lppd);
#else
    PRINTDLG_g2h(&copy, QEMU_G2H(c->lppd));
    copy.lCustData = (LPARAM)QEMU_G2H(c->lppd);
#endif

    print_hook = (ULONG_PTR)copy.lpfnPrintHook;
    TlsSetValue(comdlg32_tls, &print_hook);
    if (print_hook)
        copy.lpfnPrintHook = print_hook_proc;

    if (copy.lpfnSetupHook)
        WINE_FIXME("Implement a setup hook wrapper.\n");

    c->super.iret = PrintDlgW(&copy);

    TlsSetValue(comdlg32_tls, old_hook);
    copy.lpfnPrintHook = (LPPRINTHOOKPROC)print_hook;

#if HOST_BIT != GUEST_BIT
    PRINTDLG_h2g(QEMU_G2H(c->lppd), &copy);
#endif
}

#endif

struct qemu_PageSetupDlgA
{
    struct qemu_syscall super;
    uint64_t setupdlg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PageSetupDlgA(LPPAGESETUPDLGA setupdlg)
{
    struct qemu_PageSetupDlgA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PAGESETUPDLGA);
    call.setupdlg = (ULONG_PTR)setupdlg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PageSetupDlgA(struct qemu_syscall *call)
{
    struct qemu_PageSetupDlgA *c = (struct qemu_PageSetupDlgA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PageSetupDlgA(QEMU_G2H(c->setupdlg));
}

#endif

struct qemu_PageSetupDlgW
{
    struct qemu_syscall super;
    uint64_t setupdlg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PageSetupDlgW(LPPAGESETUPDLGW setupdlg)
{
    struct qemu_PageSetupDlgW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PAGESETUPDLGW);
    call.setupdlg = (ULONG_PTR)setupdlg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PageSetupDlgW(struct qemu_syscall *call)
{
    struct qemu_PageSetupDlgW *c = (struct qemu_PageSetupDlgW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PageSetupDlgW(QEMU_G2H(c->setupdlg));
}

#endif

struct qemu_PrintDlgExA
{
    struct qemu_syscall super;
    uint64_t lppd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI PrintDlgExA(LPPRINTDLGEXA lppd)
{
    struct qemu_PrintDlgExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTDLGEXA);
    call.lppd = (ULONG_PTR)lppd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrintDlgExA(struct qemu_syscall *call)
{
    struct qemu_PrintDlgExA *c = (struct qemu_PrintDlgExA *)call;
    PRINTDLGEXA copy, *dlg = &copy;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    dlg = (PRINTDLGEXA *)QEMU_G2H(c->lppd);
#else
    WINE_FIXME("PRINTDLGEX for 32 bit\n");
#endif

    if (dlg->lpCallback || dlg->lpCallback)
        WINE_FIXME("Implement wrappers for print dialog hooks.\n");

    c->super.iret = PrintDlgExA(dlg);

#if HOST_BIT != GUEST_BIT
    /* TODO */
#endif
}

#endif

struct qemu_PrintDlgExW
{
    struct qemu_syscall super;
    uint64_t lppd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI PrintDlgExW(LPPRINTDLGEXW lppd)
{
    struct qemu_PrintDlgExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTDLGEXW);
    call.lppd = (ULONG_PTR)lppd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrintDlgExW(struct qemu_syscall *call)
{
    struct qemu_PrintDlgExW *c = (struct qemu_PrintDlgExW *)call;
    PRINTDLGEXW copy, *dlg = &copy;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    dlg = (PRINTDLGEXW *)QEMU_G2H(c->lppd);
#else
    WINE_FIXME("PRINTDLGEX for 32 bit\n");
#endif

    if (dlg->lpCallback || dlg->lpCallback)
        WINE_FIXME("Implement wrappers for print dialog hooks.\n");

    c->super.iret = PrintDlgExW(dlg);

#if HOST_BIT != GUEST_BIT
    /* TODO */
#endif
}

#endif

