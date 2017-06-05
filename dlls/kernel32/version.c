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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetVersion(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETVERSION);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetVersion(struct qemu_syscall *call)
{
    call->iret = GetVersion();
}

#endif

struct qemu_GetVersionExA
{
    struct qemu_syscall super;
    uint64_t v;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVersionExA(OSVERSIONINFOA *v)
{
    struct qemu_GetVersionExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONEXA);
    call.v = (uint64_t)v;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_GetVersionExA(struct qemu_syscall *call)
{
    struct qemu_GetVersionExA *c = (struct qemu_GetVersionExA *)call;
    c->super.iret = GetVersionExA(QEMU_G2H(c->v));
}

#endif

struct qemu_GetVersionExW
{
    struct qemu_syscall super;
    uint64_t v;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetVersionExW(OSVERSIONINFOW *v)
{
    struct qemu_GetVersionExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONEXW);
    call.v = (uint64_t)v;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_GetVersionExW(struct qemu_syscall *call)
{
    struct qemu_GetVersionExW *c = (struct qemu_GetVersionExW *)call;
    c->super.iret = GetVersionExW(QEMU_G2H(c->v));
}

#endif

struct qemu_VerifyVersionInfoA
{
    struct qemu_syscall super;
    uint64_t lpVersionInfo;
    uint64_t dwTypeMask;
    uint64_t dwlConditionMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerifyVersionInfoA(LPOSVERSIONINFOEXA lpVersionInfo, DWORD dwTypeMask,
                                          DWORDLONG dwlConditionMask)
{
    struct qemu_VerifyVersionInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERIFYVERSIONINFOA);
    call.lpVersionInfo = (uint64_t)lpVersionInfo;
    call.dwTypeMask = (uint64_t)dwTypeMask;
    call.dwlConditionMask = (uint64_t)dwlConditionMask;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_VerifyVersionInfoA(struct qemu_syscall *call)
{
    struct qemu_VerifyVersionInfoA *c = (struct qemu_VerifyVersionInfoA *)call;
    c->super.iret = VerifyVersionInfoA(QEMU_G2H(c->lpVersionInfo), c->dwTypeMask, c->dwlConditionMask);
}

#endif

struct qemu_VerifyVersionInfoW
{
    struct qemu_syscall super;
    uint64_t lpVersionInfo;
    uint64_t dwTypeMask;
    uint64_t dwlConditionMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerifyVersionInfoW(LPOSVERSIONINFOEXW lpVersionInfo, DWORD dwTypeMask,
                                          DWORDLONG dwlConditionMask)
{
    struct qemu_VerifyVersionInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERIFYVERSIONINFOW);
    call.lpVersionInfo = (uint64_t)lpVersionInfo;
    call.dwTypeMask = (uint64_t)dwTypeMask;
    call.dwlConditionMask = (uint64_t)dwlConditionMask;
    qemu_syscall(&call.super);
    return call.super.iret;
}

#else

void qemu_VerifyVersionInfoW(struct qemu_syscall *call)
{
    struct qemu_VerifyVersionInfoW *c = (struct qemu_VerifyVersionInfoW *)call;
    c->super.iret = VerifyVersionInfoW(QEMU_G2H(c->lpVersionInfo), c->dwTypeMask, c->dwlConditionMask);
}

#endif
