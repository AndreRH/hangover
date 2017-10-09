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


struct qemu_UserRealizePalette
{
    struct qemu_syscall super;
    uint64_t hDC;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI UserRealizePalette(HDC hDC)
{
    struct qemu_UserRealizePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERREALIZEPALETTE);
    call.hDC = (ULONG_PTR)hDC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UserRealizePalette(struct qemu_syscall *call)
{
    struct qemu_UserRealizePalette *c = (struct qemu_UserRealizePalette *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserRealizePalette(QEMU_G2H(c->hDC));
}

#endif

struct qemu_ExitWindowsEx
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t reason;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ExitWindowsEx(UINT flags, DWORD reason)
{
    struct qemu_ExitWindowsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXITWINDOWSEX);
    call.flags = (ULONG_PTR)flags;
    call.reason = (ULONG_PTR)reason;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExitWindowsEx(struct qemu_syscall *call)
{
    struct qemu_ExitWindowsEx *c = (struct qemu_ExitWindowsEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExitWindowsEx(c->flags, c->reason);
}

#endif

struct qemu_LockWorkStation
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI LockWorkStation(void)
{
    struct qemu_LockWorkStation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCKWORKSTATION);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LockWorkStation to Wine headers? */
extern BOOL WINAPI LockWorkStation(void);
void qemu_LockWorkStation(struct qemu_syscall *call)
{
    struct qemu_LockWorkStation *c = (struct qemu_LockWorkStation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LockWorkStation();
}

#endif

struct qemu_RegisterServicesProcess
{
    struct qemu_syscall super;
    uint64_t ServicesProcessId;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI int WINAPI RegisterServicesProcess(DWORD ServicesProcessId)
{
    struct qemu_RegisterServicesProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSERVICESPROCESS);
    call.ServicesProcessId = (ULONG_PTR)ServicesProcessId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterServicesProcess to Wine headers? */
extern int WINAPI RegisterServicesProcess(DWORD ServicesProcessId);
void qemu_RegisterServicesProcess(struct qemu_syscall *call)
{
    struct qemu_RegisterServicesProcess *c = (struct qemu_RegisterServicesProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterServicesProcess(c->ServicesProcessId);
}

#endif

struct qemu_ShutdownBlockReasonCreate
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t reason;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShutdownBlockReasonCreate(HWND hwnd, LPCWSTR reason)
{
    struct qemu_ShutdownBlockReasonCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUTDOWNBLOCKREASONCREATE);
    call.hwnd = (ULONG_PTR)hwnd;
    call.reason = (ULONG_PTR)reason;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShutdownBlockReasonCreate(struct qemu_syscall *call)
{
    struct qemu_ShutdownBlockReasonCreate *c = (struct qemu_ShutdownBlockReasonCreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ShutdownBlockReasonCreate(QEMU_G2H(c->hwnd), QEMU_G2H(c->reason));
}

#endif

struct qemu_ShutdownBlockReasonDestroy
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI ShutdownBlockReasonDestroy(HWND hwnd)
{
    struct qemu_ShutdownBlockReasonDestroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUTDOWNBLOCKREASONDESTROY);
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShutdownBlockReasonDestroy(struct qemu_syscall *call)
{
    struct qemu_ShutdownBlockReasonDestroy *c = (struct qemu_ShutdownBlockReasonDestroy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ShutdownBlockReasonDestroy(QEMU_G2H(c->hwnd));
}

#endif

