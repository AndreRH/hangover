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

struct qemu_ChooseFontW
{
    struct qemu_syscall super;
    uint64_t lpChFont;
    uint64_t wrapper;
};

struct qemu_ChooseFont_cb
{
    uint64_t guest_proc;
    uint64_t dlg, msg, wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall guest_wrapper(const struct qemu_ChooseFont_cb *cb)
{
    LPCFHOOKPROC guest_proc = (LPCFHOOKPROC)(ULONG_PTR)cb->guest_proc;
    return guest_proc((HWND)(ULONG_PTR)cb->dlg, cb->msg, cb->wp, cb->lp);
}

WINBASEAPI BOOL WINAPI ChooseFontW(LPCHOOSEFONTW lpChFont)
{
    struct qemu_ChooseFontW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSEFONTW);
    call.lpChFont = (ULONG_PTR)lpChFont;
    call.wrapper = (ULONG_PTR)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t guest_wrapper;

static UINT_PTR CALLBACK hook_proc_wrapper(HWND dlg, UINT msg, WPARAM wp, LPARAM lp)
{
    struct qemu_ChooseFont_cb call_local, *call = &call_local;
    uint64_t *guest_proc = TlsGetValue(comdlg32_tls);
    UINT_PTR ret;
    struct qemu_OFNOTIFY *notify = NULL;

#if HOST_BIT != GUEST_BIT
    call = HeapAlloc(GetProcessHeap(), 0, sizeof(*call));
#endif

    WINE_TRACE("Calling guest proc 0x%lx(%p, %x, %lu, %lu).\n", (unsigned long)*guest_proc, dlg, msg,
            wp, lp);
    call->guest_proc = *guest_proc;
    call->dlg = (ULONG_PTR)dlg;
    call->msg = msg;
    call->wp = wp;
    call->lp = lp;

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wrapper), QEMU_H2G(call));
    WINE_TRACE("Guest proc returned %lu\n", ret);

    if (call != &call_local)
    {
        HeapFree(GetProcessHeap(), 0, call);
        HeapFree(GetProcessHeap(), 0, notify);
    }

    return ret;
}

void qemu_ChooseFontW(struct qemu_syscall *call)
{
    struct qemu_ChooseFontW *c = (struct qemu_ChooseFontW *)call;
    CHOOSEFONTW cf;
    struct qemu_CHOOSEFONT *struct32 = (struct qemu_CHOOSEFONT *)QEMU_G2H(c->lpChFont);
    uint64_t guest_proc, *old_proc = TlsGetValue(comdlg32_tls);
    HINSTANCE orig_instance;
    WINE_TRACE("\n");

    guest_wrapper = c->wrapper;

#if HOST_BIT == GUEST_BIT
    cf = *(CHOOSEFONTW *)QEMU_G2H(c->lpChFont);
#else
    if (struct32->lStructSize != sizeof(*struct32))
    {
        WINE_ERR("structure size failure!!!\n");
        c->super.iret = FALSE;
        return;
    }

    CHOOSEFONT_g2h(&cf, struct32);
#endif

    orig_instance = cf.hInstance;
    if ((cf.Flags & (CF_ENABLETEMPLATEHANDLE | CF_ENABLETEMPLATE)) == CF_ENABLETEMPLATE && !cf.hInstance)
        cf.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    guest_proc = (ULONG_PTR)cf.lpfnHook;
    TlsSetValue(comdlg32_tls, &guest_proc);
    cf.lpfnHook = hook_proc_wrapper;

    c->super.iret = p_ChooseFontW(QEMU_G2H(&cf));

    TlsSetValue(comdlg32_tls, old_proc);

    cf.lpfnHook = (LPCFHOOKPROC)guest_proc;
    cf.hInstance = orig_instance;
#if HOST_BIT == GUEST_BIT
    *(CHOOSEFONTW *)QEMU_G2H(c->lpChFont) = cf;
#else
    CHOOSEFONT_h2g(struct32, &cf);
#endif
}

#endif

struct qemu_ChooseFontA
{
    struct qemu_syscall super;
    uint64_t lpChFont;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChooseFontA(LPCHOOSEFONTA lpChFont)
{
    struct qemu_ChooseFontA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSEFONTA);
    call.lpChFont = (ULONG_PTR)lpChFont;
    call.wrapper = (ULONG_PTR)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChooseFontA(struct qemu_syscall *call)
{
    struct qemu_ChooseFontA *c = (struct qemu_ChooseFontA *)call;
    CHOOSEFONTA cf;
    struct qemu_CHOOSEFONT *struct32 = (struct qemu_CHOOSEFONT *)QEMU_G2H(c->lpChFont);
    uint64_t guest_proc, *old_proc = TlsGetValue(comdlg32_tls);
    HINSTANCE orig_instance;
    WINE_TRACE("\n");

    guest_wrapper = c->wrapper;

#if HOST_BIT == GUEST_BIT
    cf = *(CHOOSEFONTA *)QEMU_G2H(c->lpChFont);
#else
    if (struct32->lStructSize != sizeof(*struct32))
    {
        WINE_ERR("structure size failure!!!\n");
        c->super.iret = FALSE;
        return;
    }

    CHOOSEFONT_g2h((CHOOSEFONTW *)&cf, struct32);
#endif

    orig_instance = cf.hInstance;
    if ((cf.Flags & (CF_ENABLETEMPLATEHANDLE | CF_ENABLETEMPLATE)) == CF_ENABLETEMPLATE && !cf.hInstance)
        cf.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    guest_proc = (ULONG_PTR)cf.lpfnHook;
    TlsSetValue(comdlg32_tls, &guest_proc);
    cf.lpfnHook = hook_proc_wrapper;

    c->super.iret = p_ChooseFontA(&cf);

    TlsSetValue(comdlg32_tls, old_proc);

    cf.lpfnHook = (LPCFHOOKPROC)guest_proc;
    cf.hInstance = orig_instance;
#if HOST_BIT == GUEST_BIT
    *(CHOOSEFONTA *)QEMU_G2H(c->lpChFont) = cf;
#else
    CHOOSEFONT_h2g(struct32, (CHOOSEFONTW *)&cf);
#endif
}

#endif

