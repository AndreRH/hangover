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
#include <wininet.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wininet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wininet);
#endif


struct qemu_GopherCreateLocatorA
{
    struct qemu_syscall super;
    uint64_t lpszHost;
    uint64_t nServerPort;
    uint64_t lpszDisplayString;
    uint64_t lpszSelectorString;
    uint64_t dwGopherType;
    uint64_t lpszLocator;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GopherCreateLocatorA(LPCSTR lpszHost, INTERNET_PORT nServerPort, LPCSTR lpszDisplayString, LPCSTR lpszSelectorString, DWORD dwGopherType, LPSTR lpszLocator, LPDWORD lpdwBufferLength)
{
    struct qemu_GopherCreateLocatorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERCREATELOCATORA);
    call.lpszHost = (ULONG_PTR)lpszHost;
    call.nServerPort = (ULONG_PTR)nServerPort;
    call.lpszDisplayString = (ULONG_PTR)lpszDisplayString;
    call.lpszSelectorString = (ULONG_PTR)lpszSelectorString;
    call.dwGopherType = (ULONG_PTR)dwGopherType;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GopherCreateLocatorA(struct qemu_syscall *call)
{
    struct qemu_GopherCreateLocatorA *c = (struct qemu_GopherCreateLocatorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GopherCreateLocatorA(QEMU_G2H(c->lpszHost), c->nServerPort, QEMU_G2H(c->lpszDisplayString), QEMU_G2H(c->lpszSelectorString), c->dwGopherType, QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_GopherCreateLocatorW
{
    struct qemu_syscall super;
    uint64_t lpszHost;
    uint64_t nServerPort;
    uint64_t lpszDisplayString;
    uint64_t lpszSelectorString;
    uint64_t dwHopherType;
    uint64_t lpszLocator;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GopherCreateLocatorW(LPCWSTR lpszHost, INTERNET_PORT nServerPort, LPCWSTR lpszDisplayString, LPCWSTR lpszSelectorString, DWORD dwHopherType, LPWSTR lpszLocator, LPDWORD lpdwBufferLength)
{
    struct qemu_GopherCreateLocatorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERCREATELOCATORW);
    call.lpszHost = (ULONG_PTR)lpszHost;
    call.nServerPort = (ULONG_PTR)nServerPort;
    call.lpszDisplayString = (ULONG_PTR)lpszDisplayString;
    call.lpszSelectorString = (ULONG_PTR)lpszSelectorString;
    call.dwHopherType = (ULONG_PTR)dwHopherType;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GopherCreateLocatorW(struct qemu_syscall *call)
{
    struct qemu_GopherCreateLocatorW *c = (struct qemu_GopherCreateLocatorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GopherCreateLocatorW(QEMU_G2H(c->lpszHost), c->nServerPort, QEMU_G2H(c->lpszDisplayString), QEMU_G2H(c->lpszSelectorString), c->dwHopherType, QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_GopherFindFirstFileA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocator;
    uint64_t lpszSearchString;
    uint64_t lpFindData;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI GopherFindFirstFileA(HINTERNET hConnect, LPCSTR lpszLocator, LPCSTR lpszSearchString, LPGOPHER_FIND_DATAA lpFindData, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_GopherFindFirstFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERFINDFIRSTFILEA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpszSearchString = (ULONG_PTR)lpszSearchString;
    call.lpFindData = (ULONG_PTR)lpFindData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GopherFindFirstFileA(struct qemu_syscall *call)
{
    struct qemu_GopherFindFirstFileA *c = (struct qemu_GopherFindFirstFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GopherFindFirstFileA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpszSearchString), QEMU_G2H(c->lpFindData), c->dwFlags, c->dwContext);
}

#endif

struct qemu_GopherFindFirstFileW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocator;
    uint64_t lpszSearchString;
    uint64_t lpFindData;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI GopherFindFirstFileW(HINTERNET hConnect, LPCWSTR lpszLocator, LPCWSTR lpszSearchString, LPGOPHER_FIND_DATAW lpFindData, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_GopherFindFirstFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERFINDFIRSTFILEW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpszSearchString = (ULONG_PTR)lpszSearchString;
    call.lpFindData = (ULONG_PTR)lpFindData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GopherFindFirstFileW(struct qemu_syscall *call)
{
    struct qemu_GopherFindFirstFileW *c = (struct qemu_GopherFindFirstFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GopherFindFirstFileW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpszSearchString), QEMU_G2H(c->lpFindData), c->dwFlags, c->dwContext);
}

#endif

struct qemu_GopherGetAttributeA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocator;
    uint64_t lpszAttributeName;
    uint64_t lpBuffer;
    uint64_t dwBufferLength;
    uint64_t lpdwCharactersReturned;
    uint64_t lpfnEnumerator;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GopherGetAttributeA(HINTERNET hConnect, LPCSTR lpszLocator, LPCSTR lpszAttributeName, LPBYTE lpBuffer, DWORD dwBufferLength, LPDWORD lpdwCharactersReturned, GOPHER_ATTRIBUTE_ENUMERATOR lpfnEnumerator, DWORD_PTR dwContext)
{
    struct qemu_GopherGetAttributeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERGETATTRIBUTEA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpszAttributeName = (ULONG_PTR)lpszAttributeName;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwBufferLength = (ULONG_PTR)dwBufferLength;
    call.lpdwCharactersReturned = (ULONG_PTR)lpdwCharactersReturned;
    call.lpfnEnumerator = (ULONG_PTR)lpfnEnumerator;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GopherGetAttributeA(struct qemu_syscall *call)
{
    struct qemu_GopherGetAttributeA *c = (struct qemu_GopherGetAttributeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GopherGetAttributeA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpszAttributeName), QEMU_G2H(c->lpBuffer), c->dwBufferLength, QEMU_G2H(c->lpdwCharactersReturned), QEMU_G2H(c->lpfnEnumerator), c->dwContext);
}

#endif

struct qemu_GopherGetAttributeW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocator;
    uint64_t lpszAttributeName;
    uint64_t lpBuffer;
    uint64_t dwBufferLength;
    uint64_t lpdwCharactersReturned;
    uint64_t lpfnEnumerator;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GopherGetAttributeW(HINTERNET hConnect, LPCWSTR lpszLocator, LPCWSTR lpszAttributeName, LPBYTE lpBuffer, DWORD dwBufferLength, LPDWORD lpdwCharactersReturned, GOPHER_ATTRIBUTE_ENUMERATOR lpfnEnumerator, DWORD_PTR dwContext)
{
    struct qemu_GopherGetAttributeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERGETATTRIBUTEW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpszAttributeName = (ULONG_PTR)lpszAttributeName;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwBufferLength = (ULONG_PTR)dwBufferLength;
    call.lpdwCharactersReturned = (ULONG_PTR)lpdwCharactersReturned;
    call.lpfnEnumerator = (ULONG_PTR)lpfnEnumerator;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GopherGetAttributeW(struct qemu_syscall *call)
{
    struct qemu_GopherGetAttributeW *c = (struct qemu_GopherGetAttributeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GopherGetAttributeW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpszAttributeName), QEMU_G2H(c->lpBuffer), c->dwBufferLength, QEMU_G2H(c->lpdwCharactersReturned), QEMU_G2H(c->lpfnEnumerator), c->dwContext);
}

#endif

struct qemu_GopherGetLocatorTypeA
{
    struct qemu_syscall super;
    uint64_t lpszLocator;
    uint64_t lpdwGopherType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GopherGetLocatorTypeA(LPCSTR lpszLocator, LPDWORD lpdwGopherType)
{
    struct qemu_GopherGetLocatorTypeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERGETLOCATORTYPEA);
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpdwGopherType = (ULONG_PTR)lpdwGopherType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GopherGetLocatorTypeA(struct qemu_syscall *call)
{
    struct qemu_GopherGetLocatorTypeA *c = (struct qemu_GopherGetLocatorTypeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GopherGetLocatorTypeA(QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpdwGopherType));
}

#endif

struct qemu_GopherGetLocatorTypeW
{
    struct qemu_syscall super;
    uint64_t lpszLocator;
    uint64_t lpdwGopherType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GopherGetLocatorTypeW(LPCWSTR lpszLocator, LPDWORD lpdwGopherType)
{
    struct qemu_GopherGetLocatorTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHERGETLOCATORTYPEW);
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpdwGopherType = (ULONG_PTR)lpdwGopherType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GopherGetLocatorTypeW(struct qemu_syscall *call)
{
    struct qemu_GopherGetLocatorTypeW *c = (struct qemu_GopherGetLocatorTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GopherGetLocatorTypeW(QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpdwGopherType));
}

#endif

struct qemu_GopherOpenFileA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocator;
    uint64_t lpszView;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI GopherOpenFileA(HINTERNET hConnect, LPCSTR lpszLocator, LPCSTR lpszView, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_GopherOpenFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHEROPENFILEA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpszView = (ULONG_PTR)lpszView;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GopherOpenFileA(struct qemu_syscall *call)
{
    struct qemu_GopherOpenFileA *c = (struct qemu_GopherOpenFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GopherOpenFileA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpszView), c->dwFlags, c->dwContext);
}

#endif

struct qemu_GopherOpenFileW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocator;
    uint64_t lpszView;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI GopherOpenFileW(HINTERNET hConnect, LPCWSTR lpszLocator, LPCWSTR lpszView, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_GopherOpenFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GOPHEROPENFILEW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocator = (ULONG_PTR)lpszLocator;
    call.lpszView = (ULONG_PTR)lpszView;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GopherOpenFileW(struct qemu_syscall *call)
{
    struct qemu_GopherOpenFileW *c = (struct qemu_GopherOpenFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GopherOpenFileW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocator), QEMU_G2H(c->lpszView), c->dwFlags, c->dwContext);
}

#endif

