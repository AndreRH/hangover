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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_SHRegOpenKeyA
{
    struct qemu_syscall super;
    uint64_t hKey;
    uint64_t lpSubKey;
    uint64_t phkResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegOpenKeyA(HKEY hKey, LPSTR lpSubKey, PHKEY phkResult)
{
    struct qemu_SHRegOpenKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGOPENKEYA);
    call.hKey = (ULONG_PTR)hKey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;
    call.phkResult = (ULONG_PTR)phkResult;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegOpenKeyA to Wine headers? */
extern HRESULT WINAPI SHRegOpenKeyA(HKEY hKey, LPSTR lpSubKey, PHKEY phkResult);
void qemu_SHRegOpenKeyA(struct qemu_syscall *call)
{
    struct qemu_SHRegOpenKeyA *c = (struct qemu_SHRegOpenKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegOpenKeyA(QEMU_G2H(c->hKey), QEMU_G2H(c->lpSubKey), QEMU_G2H(c->phkResult));
}

#endif

struct qemu_SHRegOpenKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpszSubKey;
    uint64_t retkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegOpenKeyW (HKEY hkey, LPCWSTR lpszSubKey, PHKEY retkey)
{
    struct qemu_SHRegOpenKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGOPENKEYW);
    call.hkey = (ULONG_PTR)hkey;
    call.lpszSubKey = (ULONG_PTR)lpszSubKey;
    call.retkey = (ULONG_PTR)retkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegOpenKeyW to Wine headers? */
extern HRESULT WINAPI SHRegOpenKeyW (HKEY hkey, LPCWSTR lpszSubKey, PHKEY retkey);
void qemu_SHRegOpenKeyW(struct qemu_syscall *call)
{
    struct qemu_SHRegOpenKeyW *c = (struct qemu_SHRegOpenKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegOpenKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->lpszSubKey), QEMU_G2H(c->retkey));
}

#endif

struct qemu_SHRegQueryValueA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpSubKey;
    uint64_t lpValue;
    uint64_t lpcbValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegQueryValueA(HKEY hkey, LPSTR lpSubKey, LPSTR lpValue, LPDWORD lpcbValue)
{
    struct qemu_SHRegQueryValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGQUERYVALUEA);
    call.hkey = (ULONG_PTR)hkey;
    call.lpSubKey = (ULONG_PTR)lpSubKey;
    call.lpValue = (ULONG_PTR)lpValue;
    call.lpcbValue = (ULONG_PTR)lpcbValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegQueryValueA to Wine headers? */
extern HRESULT WINAPI SHRegQueryValueA(HKEY hkey, LPSTR lpSubKey, LPSTR lpValue, LPDWORD lpcbValue);
void qemu_SHRegQueryValueA(struct qemu_syscall *call)
{
    struct qemu_SHRegQueryValueA *c = (struct qemu_SHRegQueryValueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegQueryValueA(QEMU_G2H(c->hkey), QEMU_G2H(c->lpSubKey), QEMU_G2H(c->lpValue), QEMU_G2H(c->lpcbValue));
}

#endif

struct qemu_SHRegQueryValueExA
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpValueName;
    uint64_t lpReserved;
    uint64_t lpType;
    uint64_t lpData;
    uint64_t lpcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegQueryValueExA(HKEY hkey, LPSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
    struct qemu_SHRegQueryValueExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGQUERYVALUEEXA);
    call.hkey = (ULONG_PTR)hkey;
    call.lpValueName = (ULONG_PTR)lpValueName;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.lpType = (ULONG_PTR)lpType;
    call.lpData = (ULONG_PTR)lpData;
    call.lpcbData = (ULONG_PTR)lpcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegQueryValueExA to Wine headers? */
extern HRESULT WINAPI SHRegQueryValueExA(HKEY hkey, LPSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);
void qemu_SHRegQueryValueExA(struct qemu_syscall *call)
{
    struct qemu_SHRegQueryValueExA *c = (struct qemu_SHRegQueryValueExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegQueryValueExA(QEMU_G2H(c->hkey), QEMU_G2H(c->lpValueName), QEMU_G2H(c->lpReserved), QEMU_G2H(c->lpType), QEMU_G2H(c->lpData), QEMU_G2H(c->lpcbData));
}

#endif

struct qemu_SHRegQueryValueW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t lpszSubKey;
    uint64_t lpszData;
    uint64_t lpcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegQueryValueW(HKEY hkey, LPWSTR lpszSubKey, LPWSTR lpszData, LPDWORD lpcbData)
{
    struct qemu_SHRegQueryValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGQUERYVALUEW);
    call.hkey = (ULONG_PTR)hkey;
    call.lpszSubKey = (ULONG_PTR)lpszSubKey;
    call.lpszData = (ULONG_PTR)lpszData;
    call.lpcbData = (ULONG_PTR)lpcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegQueryValueW to Wine headers? */
extern HRESULT WINAPI SHRegQueryValueW(HKEY hkey, LPWSTR lpszSubKey, LPWSTR lpszData, LPDWORD lpcbData);
void qemu_SHRegQueryValueW(struct qemu_syscall *call)
{
    struct qemu_SHRegQueryValueW *c = (struct qemu_SHRegQueryValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegQueryValueW(QEMU_G2H(c->hkey), QEMU_G2H(c->lpszSubKey), QEMU_G2H(c->lpszData), QEMU_G2H(c->lpcbData));
}

#endif

struct qemu_SHRegQueryValueExW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t pszValue;
    uint64_t pdwReserved;
    uint64_t pdwType;
    uint64_t pvData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegQueryValueExW (HKEY hkey, LPWSTR pszValue, LPDWORD pdwReserved, LPDWORD pdwType, LPVOID pvData, LPDWORD pcbData)
{
    struct qemu_SHRegQueryValueExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGQUERYVALUEEXW);
    call.hkey = (ULONG_PTR)hkey;
    call.pszValue = (ULONG_PTR)pszValue;
    call.pdwReserved = (ULONG_PTR)pdwReserved;
    call.pdwType = (ULONG_PTR)pdwType;
    call.pvData = (ULONG_PTR)pvData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegQueryValueExW to Wine headers? */
extern HRESULT WINAPI SHRegQueryValueExW (HKEY hkey, LPWSTR pszValue, LPDWORD pdwReserved, LPDWORD pdwType, LPVOID pvData, LPDWORD pcbData);
void qemu_SHRegQueryValueExW(struct qemu_syscall *call)
{
    struct qemu_SHRegQueryValueExW *c = (struct qemu_SHRegQueryValueExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegQueryValueExW(QEMU_G2H(c->hkey), QEMU_G2H(c->pszValue), QEMU_G2H(c->pdwReserved), QEMU_G2H(c->pdwType), QEMU_G2H(c->pvData), QEMU_G2H(c->pcbData));
}

#endif

struct qemu_SHRegDeleteKeyW
{
    struct qemu_syscall super;
    uint64_t hkey;
    uint64_t pszSubKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegDeleteKeyW(HKEY hkey, LPCWSTR pszSubKey)
{
    struct qemu_SHRegDeleteKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGDELETEKEYW);
    call.hkey = (ULONG_PTR)hkey;
    call.pszSubKey = (ULONG_PTR)pszSubKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegDeleteKeyW to Wine headers? */
extern HRESULT WINAPI SHRegDeleteKeyW(HKEY hkey, LPCWSTR pszSubKey);
void qemu_SHRegDeleteKeyW(struct qemu_syscall *call)
{
    struct qemu_SHRegDeleteKeyW *c = (struct qemu_SHRegDeleteKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegDeleteKeyW(QEMU_G2H(c->hkey), QEMU_G2H(c->pszSubKey));
}

#endif

struct qemu_SHRegCloseKey
{
    struct qemu_syscall super;
    uint64_t hkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHRegCloseKey (HKEY hkey)
{
    struct qemu_SHRegCloseKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHREGCLOSEKEY);
    call.hkey = (ULONG_PTR)hkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHRegCloseKey to Wine headers? */
extern HRESULT WINAPI SHRegCloseKey (HKEY hkey);
void qemu_SHRegCloseKey(struct qemu_syscall *call)
{
    struct qemu_SHRegCloseKey *c = (struct qemu_SHRegCloseKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHRegCloseKey(QEMU_G2H(c->hkey));
}

#endif

struct qemu_SHCreateSessionKey
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t hkey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateSessionKey(REGSAM access, HKEY *hkey)
{
    struct qemu_SHCreateSessionKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESESSIONKEY);
    call.access = access;
    call.hkey = (ULONG_PTR)hkey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHCreateSessionKey to Wine headers? */
extern HRESULT WINAPI SHCreateSessionKey(REGSAM access, HKEY *hkey);
void qemu_SHCreateSessionKey(struct qemu_syscall *call)
{
    struct qemu_SHCreateSessionKey *c = (struct qemu_SHCreateSessionKey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateSessionKey(c->access, QEMU_G2H(c->hkey));
}

#endif

