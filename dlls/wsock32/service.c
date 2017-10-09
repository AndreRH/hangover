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

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <nspapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wsock32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wsock32);
#endif


struct qemu_GetAddressByNameA
{
    struct qemu_syscall super;
    uint64_t dwNameSpace;
    uint64_t lpServiceType;
    uint64_t lpServiceName;
    uint64_t lpiProtocols;
    uint64_t dwResolution;
    uint64_t lpServiceAsyncInfo;
    uint64_t lpCsaddrBuffer;
    uint64_t lpdwBufferLength;
    uint64_t lpAliasBuffer;
    uint64_t lpdwAliasBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetAddressByNameA(DWORD dwNameSpace, LPGUID lpServiceType, LPSTR lpServiceName, LPINT lpiProtocols, DWORD dwResolution, LPSERVICE_ASYNC_INFO lpServiceAsyncInfo, LPVOID lpCsaddrBuffer, LPDWORD lpdwBufferLength, LPSTR lpAliasBuffer, LPDWORD lpdwAliasBufferLength)
{
    struct qemu_GetAddressByNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADDRESSBYNAMEA);
    call.dwNameSpace = (uint64_t)dwNameSpace;
    call.lpServiceType = (uint64_t)lpServiceType;
    call.lpServiceName = (uint64_t)lpServiceName;
    call.lpiProtocols = (uint64_t)lpiProtocols;
    call.dwResolution = (uint64_t)dwResolution;
    call.lpServiceAsyncInfo = (uint64_t)lpServiceAsyncInfo;
    call.lpCsaddrBuffer = (uint64_t)lpCsaddrBuffer;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;
    call.lpAliasBuffer = (uint64_t)lpAliasBuffer;
    call.lpdwAliasBufferLength = (uint64_t)lpdwAliasBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetAddressByNameA to Wine headers? */
extern INT WINAPI GetAddressByNameA(DWORD dwNameSpace, LPGUID lpServiceType, LPSTR lpServiceName, LPINT lpiProtocols, DWORD dwResolution, LPSERVICE_ASYNC_INFO lpServiceAsyncInfo, LPVOID lpCsaddrBuffer, LPDWORD lpdwBufferLength, LPSTR lpAliasBuffer, LPDWORD lpdwAliasBufferLength);
void qemu_GetAddressByNameA(struct qemu_syscall *call)
{
    struct qemu_GetAddressByNameA *c = (struct qemu_GetAddressByNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAddressByNameA(c->dwNameSpace, QEMU_G2H(c->lpServiceType), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpiProtocols), c->dwResolution, QEMU_G2H(c->lpServiceAsyncInfo), QEMU_G2H(c->lpCsaddrBuffer), QEMU_G2H(c->lpdwBufferLength), QEMU_G2H(c->lpAliasBuffer), QEMU_G2H(c->lpdwAliasBufferLength));
}

#endif

struct qemu_GetAddressByNameW
{
    struct qemu_syscall super;
    uint64_t dwNameSpace;
    uint64_t lpServiceType;
    uint64_t lpServiceName;
    uint64_t lpiProtocols;
    uint64_t dwResolution;
    uint64_t lpServiceAsyncInfo;
    uint64_t lpCsaddrBuffer;
    uint64_t lpdwBufferLength;
    uint64_t lpAliasBuffer;
    uint64_t lpdwAliasBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetAddressByNameW(DWORD dwNameSpace, LPGUID lpServiceType, LPWSTR lpServiceName, LPINT lpiProtocols, DWORD dwResolution, LPSERVICE_ASYNC_INFO lpServiceAsyncInfo, LPVOID lpCsaddrBuffer, LPDWORD lpdwBufferLength, LPWSTR lpAliasBuffer, LPDWORD lpdwAliasBufferLength)
{
    struct qemu_GetAddressByNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADDRESSBYNAMEW);
    call.dwNameSpace = (uint64_t)dwNameSpace;
    call.lpServiceType = (uint64_t)lpServiceType;
    call.lpServiceName = (uint64_t)lpServiceName;
    call.lpiProtocols = (uint64_t)lpiProtocols;
    call.dwResolution = (uint64_t)dwResolution;
    call.lpServiceAsyncInfo = (uint64_t)lpServiceAsyncInfo;
    call.lpCsaddrBuffer = (uint64_t)lpCsaddrBuffer;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;
    call.lpAliasBuffer = (uint64_t)lpAliasBuffer;
    call.lpdwAliasBufferLength = (uint64_t)lpdwAliasBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAddressByNameW(struct qemu_syscall *call)
{
    struct qemu_GetAddressByNameW *c = (struct qemu_GetAddressByNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAddressByNameW(c->dwNameSpace, QEMU_G2H(c->lpServiceType), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpiProtocols), c->dwResolution, QEMU_G2H(c->lpServiceAsyncInfo), QEMU_G2H(c->lpCsaddrBuffer), QEMU_G2H(c->lpdwBufferLength), QEMU_G2H(c->lpAliasBuffer), QEMU_G2H(c->lpdwAliasBufferLength));
}

#endif

struct qemu_GetTypeByNameA
{
    struct qemu_syscall super;
    uint64_t lpServiceName;
    uint64_t lpServiceType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetTypeByNameA(LPSTR lpServiceName, LPGUID lpServiceType)
{
    struct qemu_GetTypeByNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTYPEBYNAMEA);
    call.lpServiceName = (uint64_t)lpServiceName;
    call.lpServiceType = (uint64_t)lpServiceType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTypeByNameA(struct qemu_syscall *call)
{
    struct qemu_GetTypeByNameA *c = (struct qemu_GetTypeByNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTypeByNameA(QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpServiceType));
}

#endif

struct qemu_GetTypeByNameW
{
    struct qemu_syscall super;
    uint64_t lpServiceName;
    uint64_t lpServiceType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetTypeByNameW(LPWSTR lpServiceName, LPGUID lpServiceType)
{
    struct qemu_GetTypeByNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTYPEBYNAMEW);
    call.lpServiceName = (uint64_t)lpServiceName;
    call.lpServiceType = (uint64_t)lpServiceType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTypeByNameW(struct qemu_syscall *call)
{
    struct qemu_GetTypeByNameW *c = (struct qemu_GetTypeByNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTypeByNameW(QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpServiceType));
}

#endif

struct qemu_SetServiceA
{
    struct qemu_syscall super;
    uint64_t dwNameSpace;
    uint64_t dwOperation;
    uint64_t dwFlags;
    uint64_t lpServiceInfo;
    uint64_t lpServiceAsyncInfo;
    uint64_t lpdwStatusFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SetServiceA(DWORD dwNameSpace, DWORD dwOperation, DWORD dwFlags, LPSERVICE_INFOA lpServiceInfo, LPSERVICE_ASYNC_INFO lpServiceAsyncInfo, LPDWORD lpdwStatusFlags)
{
    struct qemu_SetServiceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSERVICEA);
    call.dwNameSpace = (uint64_t)dwNameSpace;
    call.dwOperation = (uint64_t)dwOperation;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpServiceInfo = (uint64_t)lpServiceInfo;
    call.lpServiceAsyncInfo = (uint64_t)lpServiceAsyncInfo;
    call.lpdwStatusFlags = (uint64_t)lpdwStatusFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetServiceA(struct qemu_syscall *call)
{
    struct qemu_SetServiceA *c = (struct qemu_SetServiceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetServiceA(c->dwNameSpace, c->dwOperation, c->dwFlags, QEMU_G2H(c->lpServiceInfo), QEMU_G2H(c->lpServiceAsyncInfo), QEMU_G2H(c->lpdwStatusFlags));
}

#endif

struct qemu_SetServiceW
{
    struct qemu_syscall super;
    uint64_t dwNameSpace;
    uint64_t dwOperation;
    uint64_t dwFlags;
    uint64_t lpServiceInfo;
    uint64_t lpServiceAsyncInfo;
    uint64_t lpdwStatusFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SetServiceW(DWORD dwNameSpace, DWORD dwOperation, DWORD dwFlags, LPSERVICE_INFOW lpServiceInfo, LPSERVICE_ASYNC_INFO lpServiceAsyncInfo, LPDWORD lpdwStatusFlags)
{
    struct qemu_SetServiceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSERVICEW);
    call.dwNameSpace = (uint64_t)dwNameSpace;
    call.dwOperation = (uint64_t)dwOperation;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpServiceInfo = (uint64_t)lpServiceInfo;
    call.lpServiceAsyncInfo = (uint64_t)lpServiceAsyncInfo;
    call.lpdwStatusFlags = (uint64_t)lpdwStatusFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetServiceW(struct qemu_syscall *call)
{
    struct qemu_SetServiceW *c = (struct qemu_SetServiceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetServiceW(c->dwNameSpace, c->dwOperation, c->dwFlags, QEMU_G2H(c->lpServiceInfo), QEMU_G2H(c->lpServiceAsyncInfo), QEMU_G2H(c->lpdwStatusFlags));
}

#endif

struct qemu_GetServiceA
{
    struct qemu_syscall super;
    uint64_t dwNameSpace;
    uint64_t lpGuid;
    uint64_t lpServiceName;
    uint64_t dwProperties;
    uint64_t lpBuffer;
    uint64_t lpdwBufferSize;
    uint64_t lpServiceAsyncInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetServiceA(DWORD dwNameSpace, LPGUID lpGuid, LPSTR lpServiceName, DWORD dwProperties, LPVOID lpBuffer, LPDWORD lpdwBufferSize, LPSERVICE_ASYNC_INFO lpServiceAsyncInfo)
{
    struct qemu_GetServiceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSERVICEA);
    call.dwNameSpace = (uint64_t)dwNameSpace;
    call.lpGuid = (uint64_t)lpGuid;
    call.lpServiceName = (uint64_t)lpServiceName;
    call.dwProperties = (uint64_t)dwProperties;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.lpdwBufferSize = (uint64_t)lpdwBufferSize;
    call.lpServiceAsyncInfo = (uint64_t)lpServiceAsyncInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetServiceA(struct qemu_syscall *call)
{
    struct qemu_GetServiceA *c = (struct qemu_GetServiceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetServiceA(c->dwNameSpace, QEMU_G2H(c->lpGuid), QEMU_G2H(c->lpServiceName), c->dwProperties, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwBufferSize), QEMU_G2H(c->lpServiceAsyncInfo));
}

#endif

struct qemu_GetServiceW
{
    struct qemu_syscall super;
    uint64_t dwNameSpace;
    uint64_t lpGuid;
    uint64_t lpServiceName;
    uint64_t dwProperties;
    uint64_t lpBuffer;
    uint64_t lpdwBufferSize;
    uint64_t lpServiceAsyncInfo;
};

#ifdef QEMU_DLL_GUEST

INT WINAPI GetServiceW(DWORD dwNameSpace,LPGUID lpGuid,LPWSTR lpServiceName,DWORD dwProperties,LPVOID lpBuffer,LPDWORD lpdwBufferSize,LPSERVICE_ASYNC_INFO lpServiceAsyncInfo)
{
    struct qemu_GetServiceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSERVICEW);
    call.dwNameSpace = (uint64_t)dwNameSpace;
    call.lpGuid = (uint64_t)lpGuid;
    call.lpServiceName = (uint64_t)lpServiceName;
    call.dwProperties = (uint64_t)dwProperties;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.lpdwBufferSize = (uint64_t)lpdwBufferSize;
    call.lpServiceAsyncInfo = (uint64_t)lpServiceAsyncInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetServiceW(struct qemu_syscall *call)
{
    struct qemu_GetServiceW *c = (struct qemu_GetServiceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetServiceW(c->dwNameSpace, QEMU_G2H(c->lpGuid), QEMU_G2H(c->lpServiceName), c->dwProperties, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwBufferSize), QEMU_G2H(c->lpServiceAsyncInfo));
}

#endif

