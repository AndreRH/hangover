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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlGetProductInfo
{
    struct qemu_syscall super;
    uint64_t dwOSMajorVersion;
    uint64_t dwOSMinorVersion;
    uint64_t dwSpMajorVersion;
    uint64_t dwSpMinorVersion;
    uint64_t pdwReturnedProductType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlGetProductInfo(DWORD dwOSMajorVersion, DWORD dwOSMinorVersion, DWORD dwSpMajorVersion, DWORD dwSpMinorVersion, PDWORD pdwReturnedProductType)
{
    struct qemu_RtlGetProductInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETPRODUCTINFO);
    call.dwOSMajorVersion = (ULONG_PTR)dwOSMajorVersion;
    call.dwOSMinorVersion = (ULONG_PTR)dwOSMinorVersion;
    call.dwSpMajorVersion = (ULONG_PTR)dwSpMajorVersion;
    call.dwSpMinorVersion = (ULONG_PTR)dwSpMinorVersion;
    call.pdwReturnedProductType = (ULONG_PTR)pdwReturnedProductType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetProductInfo(struct qemu_syscall *call)
{
    struct qemu_RtlGetProductInfo *c = (struct qemu_RtlGetProductInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetProductInfo(c->dwOSMajorVersion, c->dwOSMinorVersion, c->dwSpMajorVersion, c->dwSpMinorVersion, QEMU_G2H(c->pdwReturnedProductType));
}

#endif

struct qemu_RtlGetVersion
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetVersion(RTL_OSVERSIONINFOEXW *info)
{
    struct qemu_RtlGetVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETVERSION);
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetVersion(struct qemu_syscall *call)
{
    struct qemu_RtlGetVersion *c = (struct qemu_RtlGetVersion *)call;

    /* RTL_OSVERSIONINFOEXW has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = RtlGetVersion(QEMU_G2H(c->info));
}

#endif

struct qemu_RtlGetNtVersionNumbers
{
    struct qemu_syscall super;
    uint64_t major;
    uint64_t minor;
    uint64_t build;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlGetNtVersionNumbers(LPDWORD major, LPDWORD minor, LPDWORD build)
{
    struct qemu_RtlGetNtVersionNumbers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETNTVERSIONNUMBERS);
    call.major = (ULONG_PTR)major;
    call.minor = (ULONG_PTR)minor;
    call.build = (ULONG_PTR)build;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add RtlGetNtVersionNumbers to Wine headers? */
extern void WINAPI RtlGetNtVersionNumbers(LPDWORD major, LPDWORD minor, LPDWORD build);
void qemu_RtlGetNtVersionNumbers(struct qemu_syscall *call)
{
    struct qemu_RtlGetNtVersionNumbers *c = (struct qemu_RtlGetNtVersionNumbers *)call;
    WINE_FIXME("Unverified!\n");
    RtlGetNtVersionNumbers(QEMU_G2H(c->major), QEMU_G2H(c->minor), QEMU_G2H(c->build));
}

#endif

struct qemu_RtlGetNtProductType
{
    struct qemu_syscall super;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlGetNtProductType(LPDWORD type)
{
    struct qemu_RtlGetNtProductType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETNTPRODUCTTYPE);
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetNtProductType(struct qemu_syscall *call)
{
    struct qemu_RtlGetNtProductType *c = (struct qemu_RtlGetNtProductType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetNtProductType(QEMU_G2H(c->type));
}

#endif

struct qemu_RtlVerifyVersionInfo
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t dwTypeMask;
    uint64_t dwlConditionMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlVerifyVersionInfo(const RTL_OSVERSIONINFOEXW *info, DWORD dwTypeMask, DWORDLONG dwlConditionMask)
{
    struct qemu_RtlVerifyVersionInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLVERIFYVERSIONINFO);
    call.info = (ULONG_PTR)info;
    call.dwTypeMask = (ULONG_PTR)dwTypeMask;
    call.dwlConditionMask = (ULONG_PTR)dwlConditionMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlVerifyVersionInfo(struct qemu_syscall *call)
{
    struct qemu_RtlVerifyVersionInfo *c = (struct qemu_RtlVerifyVersionInfo *)call;

    /* RTL_OSVERSIONINFOEXW has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    c->super.iret = RtlVerifyVersionInfo(QEMU_G2H(c->info), c->dwTypeMask, c->dwlConditionMask);
}

#endif

