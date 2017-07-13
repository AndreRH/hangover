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
#include "comdlg32.h"

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
    call.lpChFont = (uint64_t)lpChFont;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChooseFontW(struct qemu_syscall *call)
{
    struct qemu_ChooseFontW *c = (struct qemu_ChooseFontW *)call;
    CHOOSEFONTW cf;
    WINE_TRACE("\n");

    cf = *(CHOOSEFONTW *)QEMU_G2H(c->lpChFont);
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
    call.lpChFont = (uint64_t)lpChFont;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChooseFontA(struct qemu_syscall *call)
{
    struct qemu_ChooseFontA *c = (struct qemu_ChooseFontA *)call;
    CHOOSEFONTA cf;
    WINE_TRACE("\n");

    cf = *(CHOOSEFONTA *)QEMU_G2H(c->lpChFont);
    if (cf.Flags & (CF_ENABLETEMPLATEHANDLE | CF_ENABLETEMPLATE) == CF_ENABLETEMPLATE && !cf.hInstance)
        cf.hInstance = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);

    c->super.iret = ChooseFontA(&cf);
}

#endif

