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

struct qemu_PrintDlgA
{
    struct qemu_syscall super;
    uint64_t lppd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrintDlgA(LPPRINTDLGA lppd)
{
    struct qemu_PrintDlgA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTDLGA);
    call.lppd = (ULONG_PTR)lppd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrintDlgA(struct qemu_syscall *call)
{
    struct qemu_PrintDlgA *c = (struct qemu_PrintDlgA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrintDlgA(QEMU_G2H(c->lppd));
}

#endif

struct qemu_PrintDlgW
{
    struct qemu_syscall super;
    uint64_t lppd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrintDlgW(LPPRINTDLGW lppd)
{
    struct qemu_PrintDlgW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTDLGW);
    call.lppd = (ULONG_PTR)lppd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrintDlgW(struct qemu_syscall *call)
{
    struct qemu_PrintDlgW *c = (struct qemu_PrintDlgW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrintDlgW(QEMU_G2H(c->lppd));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrintDlgExA(QEMU_G2H(c->lppd));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrintDlgExW(QEMU_G2H(c->lppd));
}

#endif

