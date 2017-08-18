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
#include "winmm.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif


struct qemu_SendDriverMessage
{
    struct qemu_syscall super;
    uint64_t hDriver;
    uint64_t msg;
    uint64_t lParam1;
    uint64_t lParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI SendDriverMessage(HDRVR hDriver, UINT msg, LPARAM lParam1, LPARAM lParam2)
{
    struct qemu_SendDriverMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDDRIVERMESSAGE);
    call.hDriver = (uint64_t)hDriver;
    call.msg = (uint64_t)msg;
    call.lParam1 = (uint64_t)lParam1;
    call.lParam2 = (uint64_t)lParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SendDriverMessage(struct qemu_syscall *call)
{
    struct qemu_SendDriverMessage *c = (struct qemu_SendDriverMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendDriverMessage(QEMU_G2H(c->hDriver), c->msg, c->lParam1, c->lParam2);
}

#endif

struct qemu_OpenDriverA
{
    struct qemu_syscall super;
    uint64_t lpDriverName;
    uint64_t lpSectionName;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDRVR WINAPI OpenDriverA(LPCSTR lpDriverName, LPCSTR lpSectionName, LPARAM lParam)
{
    struct qemu_OpenDriverA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENDRIVERA);
    call.lpDriverName = (uint64_t)lpDriverName;
    call.lpSectionName = (uint64_t)lpSectionName;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return (HDRVR)call.super.iret;
}

#else

void qemu_OpenDriverA(struct qemu_syscall *call)
{
    struct qemu_OpenDriverA *c = (struct qemu_OpenDriverA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenDriverA(QEMU_G2H(c->lpDriverName), QEMU_G2H(c->lpSectionName), c->lParam);
}

#endif

struct qemu_OpenDriver
{
    struct qemu_syscall super;
    uint64_t lpDriverName;
    uint64_t lpSectionName;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDRVR WINAPI OpenDriver(LPCWSTR lpDriverName, LPCWSTR lpSectionName, LPARAM lParam)
{
    struct qemu_OpenDriver call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENDRIVER);
    call.lpDriverName = (uint64_t)lpDriverName;
    call.lpSectionName = (uint64_t)lpSectionName;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return (HDRVR)call.super.iret;
}

#else

void qemu_OpenDriver(struct qemu_syscall *call)
{
    struct qemu_OpenDriver *c = (struct qemu_OpenDriver *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenDriver(QEMU_G2H(c->lpDriverName), QEMU_G2H(c->lpSectionName), c->lParam);
}

#endif

struct qemu_CloseDriver
{
    struct qemu_syscall super;
    uint64_t hDrvr;
    uint64_t lParam1;
    uint64_t lParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI CloseDriver(HDRVR hDrvr, LPARAM lParam1, LPARAM lParam2)
{
    struct qemu_CloseDriver call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEDRIVER);
    call.hDrvr = (uint64_t)hDrvr;
    call.lParam1 = (uint64_t)lParam1;
    call.lParam2 = (uint64_t)lParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseDriver(struct qemu_syscall *call)
{
    struct qemu_CloseDriver *c = (struct qemu_CloseDriver *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseDriver(QEMU_G2H(c->hDrvr), c->lParam1, c->lParam2);
}

#endif

struct qemu_GetDriverFlags
{
    struct qemu_syscall super;
    uint64_t hDrvr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetDriverFlags(HDRVR hDrvr)
{
    struct qemu_GetDriverFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDRIVERFLAGS);
    call.hDrvr = (uint64_t)hDrvr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDriverFlags(struct qemu_syscall *call)
{
    struct qemu_GetDriverFlags *c = (struct qemu_GetDriverFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDriverFlags(QEMU_G2H(c->hDrvr));
}

#endif

struct qemu_GetDriverModuleHandle
{
    struct qemu_syscall super;
    uint64_t hDrvr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMODULE WINAPI GetDriverModuleHandle(HDRVR hDrvr)
{
    struct qemu_GetDriverModuleHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDRIVERMODULEHANDLE);
    call.hDrvr = (uint64_t)hDrvr;

    qemu_syscall(&call.super);

    return (HMODULE)call.super.iret;
}

#else

void qemu_GetDriverModuleHandle(struct qemu_syscall *call)
{
    struct qemu_GetDriverModuleHandle *c = (struct qemu_GetDriverModuleHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetDriverModuleHandle(QEMU_G2H(c->hDrvr));
}

#endif

struct qemu_DefDriverProc
{
    struct qemu_syscall super;
    uint64_t dwDriverIdentifier;
    uint64_t hDrv;
    uint64_t Msg;
    uint64_t lParam1;
    uint64_t lParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI DefDriverProc(DWORD_PTR dwDriverIdentifier, HDRVR hDrv, UINT Msg, LPARAM lParam1, LPARAM lParam2)
{
    struct qemu_DefDriverProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEFDRIVERPROC);
    call.dwDriverIdentifier = (uint64_t)dwDriverIdentifier;
    call.hDrv = (uint64_t)hDrv;
    call.Msg = (uint64_t)Msg;
    call.lParam1 = (uint64_t)lParam1;
    call.lParam2 = (uint64_t)lParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DefDriverProc(struct qemu_syscall *call)
{
    struct qemu_DefDriverProc *c = (struct qemu_DefDriverProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DefDriverProc(c->dwDriverIdentifier, QEMU_G2H(c->hDrv), c->Msg, c->lParam1, c->lParam2);
}

#endif

struct qemu_DriverCallback
{
    struct qemu_syscall super;
    uint64_t dwCallBack;
    uint64_t uFlags;
    uint64_t hDev;
    uint64_t wMsg;
    uint64_t dwUser;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DriverCallback(DWORD_PTR dwCallBack, DWORD uFlags, HDRVR hDev, DWORD wMsg, DWORD_PTR dwUser, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_DriverCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRIVERCALLBACK);
    call.dwCallBack = (uint64_t)dwCallBack;
    call.uFlags = (uint64_t)uFlags;
    call.hDev = (uint64_t)hDev;
    call.wMsg = (uint64_t)wMsg;
    call.dwUser = (uint64_t)dwUser;
    call.dwParam1 = (uint64_t)dwParam1;
    call.dwParam2 = (uint64_t)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DriverCallback to Wine headers? */
extern BOOL WINAPI DriverCallback(DWORD_PTR dwCallBack, DWORD uFlags, HDRVR hDev, DWORD wMsg, DWORD_PTR dwUser, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
void qemu_DriverCallback(struct qemu_syscall *call)
{
    struct qemu_DriverCallback *c = (struct qemu_DriverCallback *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DriverCallback(c->dwCallBack, c->uFlags, QEMU_G2H(c->hDev), c->wMsg, c->dwUser, c->dwParam1, c->dwParam2);
}

#endif

