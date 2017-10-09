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
#include "qemu_comdlg32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);
#endif


struct qemu_CommDlgExtendedError
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CommDlgExtendedError(void)
{
    struct qemu_CommDlgExtendedError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMDLGEXTENDEDERROR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CommDlgExtendedError(struct qemu_syscall *call)
{
    struct qemu_CommDlgExtendedError *c = (struct qemu_CommDlgExtendedError *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CommDlgExtendedError();
}

#endif

struct qemu_DllGetClassObject
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    struct qemu_DllGetClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLGETCLASSOBJECT);
    call.rclsid = (ULONG_PTR)rclsid;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllGetClassObject(struct qemu_syscall *call)
{
    struct qemu_DllGetClassObject *c = (struct qemu_DllGetClassObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DllGetClassObject(QEMU_G2H(c->rclsid), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_DllRegisterServer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllRegisterServer(void)
{
    struct qemu_DllRegisterServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLREGISTERSERVER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllRegisterServer(struct qemu_syscall *call)
{
    struct qemu_DllRegisterServer *c = (struct qemu_DllRegisterServer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DllRegisterServer();
}

#endif

struct qemu_DllUnregisterServer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllUnregisterServer(void)
{
    struct qemu_DllUnregisterServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLUNREGISTERSERVER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllUnregisterServer(struct qemu_syscall *call)
{
    struct qemu_DllUnregisterServer *c = (struct qemu_DllUnregisterServer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DllUnregisterServer();
}

#endif

