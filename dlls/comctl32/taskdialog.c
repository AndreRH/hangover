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
#include <commctrl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif


struct qemu_TaskDialogIndirect
{
    struct qemu_syscall super;
    uint64_t taskconfig;
    uint64_t button;
    uint64_t radio_button;
    uint64_t verification_flag_checked;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI TaskDialogIndirect(const TASKDIALOGCONFIG *taskconfig, int *button, int *radio_button, BOOL *verification_flag_checked)
{
    struct qemu_TaskDialogIndirect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TASKDIALOGINDIRECT);
    call.taskconfig = (ULONG_PTR)taskconfig;
    call.button = (ULONG_PTR)button;
    call.radio_button = (ULONG_PTR)radio_button;
    call.verification_flag_checked = (ULONG_PTR)verification_flag_checked;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TaskDialogIndirect(struct qemu_syscall *call)
{
    struct qemu_TaskDialogIndirect *c = (struct qemu_TaskDialogIndirect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TaskDialogIndirect(QEMU_G2H(c->taskconfig), QEMU_G2H(c->button), QEMU_G2H(c->radio_button), QEMU_G2H(c->verification_flag_checked));
}

#endif

struct qemu_TaskDialog
{
    struct qemu_syscall super;
    uint64_t owner;
    uint64_t hinst;
    uint64_t title;
    uint64_t main_instruction;
    uint64_t content;
    uint64_t common_buttons;
    uint64_t icon;
    uint64_t button;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI TaskDialog(HWND owner, HINSTANCE hinst, const WCHAR *title, const WCHAR *main_instruction, const WCHAR *content, TASKDIALOG_COMMON_BUTTON_FLAGS common_buttons, const WCHAR *icon, int *button)
{
    struct qemu_TaskDialog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TASKDIALOG);
    call.owner = (ULONG_PTR)owner;
    call.hinst = (ULONG_PTR)hinst;
    call.title = (ULONG_PTR)title;
    call.main_instruction = (ULONG_PTR)main_instruction;
    call.content = (ULONG_PTR)content;
    call.common_buttons = common_buttons;
    call.icon = (ULONG_PTR)icon;
    call.button = (ULONG_PTR)button;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TaskDialog(struct qemu_syscall *call)
{
    struct qemu_TaskDialog *c = (struct qemu_TaskDialog *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TaskDialog(QEMU_G2H(c->owner), QEMU_G2H(c->hinst), QEMU_G2H(c->title), QEMU_G2H(c->main_instruction), QEMU_G2H(c->content), c->common_buttons, QEMU_G2H(c->icon), QEMU_G2H(c->button));
}

#endif

