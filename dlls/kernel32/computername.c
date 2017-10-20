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
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetComputerNameW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetComputerNameW(LPWSTR name,LPDWORD size)
{
    struct qemu_GetComputerNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPUTERNAMEW);
    call.name = (ULONG_PTR)name;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComputerNameW(struct qemu_syscall *call)
{
    struct qemu_GetComputerNameW *c = (struct qemu_GetComputerNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetComputerNameW(QEMU_G2H(c->name), QEMU_G2H(c->size));
}

#endif

struct qemu_GetComputerNameA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetComputerNameA(LPSTR name, LPDWORD size)
{
    struct qemu_GetComputerNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPUTERNAMEA);
    call.name = (ULONG_PTR)name;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComputerNameA(struct qemu_syscall *call)
{
    struct qemu_GetComputerNameA *c = (struct qemu_GetComputerNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetComputerNameA(QEMU_G2H(c->name), QEMU_G2H(c->size));
}

#endif

struct qemu_GetComputerNameExA
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetComputerNameExA(COMPUTER_NAME_FORMAT type, LPSTR name, LPDWORD size)
{
    struct qemu_GetComputerNameExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPUTERNAMEEXA);
    call.type = type;
    call.name = (ULONG_PTR)name;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComputerNameExA(struct qemu_syscall *call)
{
    struct qemu_GetComputerNameExA *c = (struct qemu_GetComputerNameExA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetComputerNameExA(c->type, QEMU_G2H(c->name), QEMU_G2H(c->size));
}

#endif

struct qemu_GetComputerNameExW
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t name;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetComputerNameExW(COMPUTER_NAME_FORMAT type, LPWSTR name, LPDWORD size)
{
    struct qemu_GetComputerNameExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMPUTERNAMEEXW);
    call.type = type;
    call.name = (ULONG_PTR)name;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetComputerNameExW(struct qemu_syscall *call)
{
    struct qemu_GetComputerNameExW *c = (struct qemu_GetComputerNameExW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetComputerNameExW(c->type, QEMU_G2H(c->name), QEMU_G2H(c->size));
}

#endif

struct qemu_SetComputerNameW
{
    struct qemu_syscall super;
    uint64_t lpComputerName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetComputerNameW(LPCWSTR lpComputerName)
{
    struct qemu_SetComputerNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMPUTERNAMEW);
    call.lpComputerName = (ULONG_PTR)lpComputerName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetComputerNameW(struct qemu_syscall *call)
{
    struct qemu_SetComputerNameW *c = (struct qemu_SetComputerNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetComputerNameW(QEMU_G2H(c->lpComputerName));
}

#endif

struct qemu_SetComputerNameA
{
    struct qemu_syscall super;
    uint64_t lpComputerName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetComputerNameA(LPCSTR lpComputerName)
{
    struct qemu_SetComputerNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMPUTERNAMEA);
    call.lpComputerName = (ULONG_PTR)lpComputerName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetComputerNameA(struct qemu_syscall *call)
{
    struct qemu_SetComputerNameA *c = (struct qemu_SetComputerNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetComputerNameA(QEMU_G2H(c->lpComputerName));
}

#endif

struct qemu_SetComputerNameExW
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t lpComputerName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetComputerNameExW(COMPUTER_NAME_FORMAT type, LPCWSTR lpComputerName)
{
    struct qemu_SetComputerNameExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMPUTERNAMEEXW);
    call.type = type;
    call.lpComputerName = (ULONG_PTR)lpComputerName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetComputerNameExW(struct qemu_syscall *call)
{
    struct qemu_SetComputerNameExW *c = (struct qemu_SetComputerNameExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetComputerNameExW(c->type, QEMU_G2H(c->lpComputerName));
}

#endif

struct qemu_SetComputerNameExA
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t lpComputerName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetComputerNameExA(COMPUTER_NAME_FORMAT type, LPCSTR lpComputerName)
{
    struct qemu_SetComputerNameExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMPUTERNAMEEXA);
    call.type = type;
    call.lpComputerName = (ULONG_PTR)lpComputerName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetComputerNameExA(struct qemu_syscall *call)
{
    struct qemu_SetComputerNameExA *c = (struct qemu_SetComputerNameExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetComputerNameExA(c->type, QEMU_G2H(c->lpComputerName));
}

#endif

struct qemu_DnsHostnameToComputerNameA
{
    struct qemu_syscall super;
    uint64_t hostname;
    uint64_t computername;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DnsHostnameToComputerNameA(LPCSTR hostname, LPSTR computername, LPDWORD size)
{
    struct qemu_DnsHostnameToComputerNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DNSHOSTNAMETOCOMPUTERNAMEA);
    call.hostname = (ULONG_PTR)hostname;
    call.computername = (ULONG_PTR)computername;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DnsHostnameToComputerNameA(struct qemu_syscall *call)
{
    struct qemu_DnsHostnameToComputerNameA *c = (struct qemu_DnsHostnameToComputerNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DnsHostnameToComputerNameA(QEMU_G2H(c->hostname), QEMU_G2H(c->computername), QEMU_G2H(c->size));
}

#endif

struct qemu_DnsHostnameToComputerNameW
{
    struct qemu_syscall super;
    uint64_t hostname;
    uint64_t computername;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DnsHostnameToComputerNameW(LPCWSTR hostname, LPWSTR computername, LPDWORD size)
{
    struct qemu_DnsHostnameToComputerNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DNSHOSTNAMETOCOMPUTERNAMEW);
    call.hostname = (ULONG_PTR)hostname;
    call.computername = (ULONG_PTR)computername;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DnsHostnameToComputerNameW(struct qemu_syscall *call)
{
    struct qemu_DnsHostnameToComputerNameW *c = (struct qemu_DnsHostnameToComputerNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DnsHostnameToComputerNameW(QEMU_G2H(c->hostname), QEMU_G2H(c->computername), QEMU_G2H(c->size));
}

#endif

