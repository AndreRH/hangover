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


struct qemu_MakeDragList
{
    struct qemu_syscall super;
    uint64_t hwndLB;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI MakeDragList (HWND hwndLB)
{
    struct qemu_MakeDragList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MAKEDRAGLIST);
    call.hwndLB = (ULONG_PTR)hwndLB;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MakeDragList(struct qemu_syscall *call)
{
    struct qemu_MakeDragList *c = (struct qemu_MakeDragList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_MakeDragList(QEMU_G2H(c->hwndLB));
}

#endif

struct qemu_DrawInsert
{
    struct qemu_syscall super;
    uint64_t hwndParent;
    uint64_t hwndLB;
    uint64_t nItem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI DrawInsert (HWND hwndParent, HWND hwndLB, INT nItem)
{
    struct qemu_DrawInsert call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWINSERT);
    call.hwndParent = (ULONG_PTR)hwndParent;
    call.hwndLB = (ULONG_PTR)hwndLB;
    call.nItem = nItem;

    qemu_syscall(&call.super);
}

#else

void qemu_DrawInsert(struct qemu_syscall *call)
{
    struct qemu_DrawInsert *c = (struct qemu_DrawInsert *)call;
    WINE_FIXME("Unverified!\n");
    p_DrawInsert(QEMU_G2H(c->hwndParent), QEMU_G2H(c->hwndLB), c->nItem);
}

#endif

struct qemu_LBItemFromPt
{
    struct qemu_syscall super;
    uint64_t hwndLB;
    uint64_t ptX, ptY;
    uint64_t bAutoScroll;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LBItemFromPt (HWND hwndLB, POINT pt, BOOL bAutoScroll)
{
    struct qemu_LBItemFromPt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LBITEMFROMPT);
    call.hwndLB = (ULONG_PTR)hwndLB;
    call.ptX = pt.x;
    call.ptY = pt.y;
    call.bAutoScroll = bAutoScroll;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LBItemFromPt(struct qemu_syscall *call)
{
    struct qemu_LBItemFromPt *c = (struct qemu_LBItemFromPt *)call;
    POINT pt;
    WINE_FIXME("Unverified!\n");

    pt.x = c->ptX;
    pt.y = c->ptY;
    c->super.iret = p_LBItemFromPt(QEMU_G2H(c->hwndLB), pt, c->bAutoScroll);
}

#endif

