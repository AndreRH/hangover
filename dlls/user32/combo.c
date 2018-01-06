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


struct qemu_GetComboBoxInfo
{
    struct qemu_syscall super;
    uint64_t hwndCombo;
    uint64_t pcbi;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetComboBoxInfo(HWND hwndCombo, PCOMBOBOXINFO pcbi)
{
    struct qemu_GetComboBoxInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMBOBOXINFO);
    call.hwndCombo = (LONG_PTR)hwndCombo;
    call.pcbi = (ULONG_PTR)pcbi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComboBoxInfo(struct qemu_syscall *call)
{
    struct qemu_GetComboBoxInfo *c = (struct qemu_GetComboBoxInfo *)call;
    WINE_TRACE("\n");
    c->super.iret = GetComboBoxInfo(QEMU_G2H(c->hwndCombo), QEMU_G2H(c->pcbi));
}

#endif

