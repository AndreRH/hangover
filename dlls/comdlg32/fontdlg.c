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
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChooseFontW(LPCHOOSEFONTW lpChFont)
{
    struct qemu_ChooseFontW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSEFONTW);
    call.lpChFont = (ULONG_PTR)lpChFont;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static inline void CHOOSEFONT_g2h(CHOOSEFONTW *host, const struct qemu_CHOOSEFONT *guest)
{
    host->lStructSize = sizeof(*host);
    host->hwndOwner = (HWND)(ULONG_PTR)guest->hwndOwner;
    host->hDC = (HDC)(ULONG_PTR)guest->hDC;
    host->lpLogFont = (LOGFONTW *)(ULONG_PTR)guest->lpLogFont;
    host->iPointSize = guest->iPointSize;
    host->Flags = guest->Flags;
    host->rgbColors = guest->rgbColors;
    host->lCustData = guest->lCustData;
    host->lpfnHook = (LPCFHOOKPROC)(ULONG_PTR)guest->lpfnHook;
    host->lpTemplateName = (WCHAR *)(ULONG_PTR)guest->lpTemplateName;
    host->hInstance = (HINSTANCE)(ULONG_PTR)guest->hInstance;
    host->lpszStyle = (WCHAR *)(ULONG_PTR)guest->lpszStyle;
    host->nFontType = guest->nFontType;
    host->___MISSING_ALIGNMENT__ = guest->___MISSING_ALIGNMENT__; /* Hmm... */
    host->nSizeMin = guest->nSizeMin;
    host->nSizeMax = guest->nSizeMax;
}

void qemu_ChooseFontW(struct qemu_syscall *call)
{
    struct qemu_ChooseFontW *c = (struct qemu_ChooseFontW *)call;
    CHOOSEFONTW cf;
    struct qemu_CHOOSEFONT *struct32 = (struct qemu_CHOOSEFONT *)QEMU_G2H(c->lpChFont);
    WINE_TRACE("\n");

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

    if (cf.Flags & (CF_ENABLETEMPLATEHANDLE | CF_ENABLETEMPLATE) == CF_ENABLETEMPLATE && !cf.hInstance)
        cf.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    c->super.iret = ChooseFontW(QEMU_G2H(&cf));
}

#endif

struct qemu_ChooseFontA
{
    struct qemu_syscall super;
    uint64_t lpChFont;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChooseFontA(LPCHOOSEFONTA lpChFont)
{
    struct qemu_ChooseFontA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSEFONTA);
    call.lpChFont = (ULONG_PTR)lpChFont;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChooseFontA(struct qemu_syscall *call)
{
    struct qemu_ChooseFontA *c = (struct qemu_ChooseFontA *)call;
    CHOOSEFONTA cf;
    struct qemu_CHOOSEFONT *struct32 = (struct qemu_CHOOSEFONT *)QEMU_G2H(c->lpChFont);
    WINE_TRACE("\n");

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

    if (cf.Flags & (CF_ENABLETEMPLATEHANDLE | CF_ENABLETEMPLATE) == CF_ENABLETEMPLATE && !cf.hInstance)
        cf.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    c->super.iret = ChooseFontA(&cf);
}

#endif

