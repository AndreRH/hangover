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
#include "wininet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wininet);
#endif


struct qemu_HttpAddRequestHeadersW
{
    struct qemu_syscall super;
    uint64_t hHttpRequest;
    uint64_t lpszHeader;
    uint64_t dwHeaderLength;
    uint64_t dwModifier;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpAddRequestHeadersW(HINTERNET hHttpRequest, LPCWSTR lpszHeader, DWORD dwHeaderLength, DWORD dwModifier)
{
    struct qemu_HttpAddRequestHeadersW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPADDREQUESTHEADERSW);
    call.hHttpRequest = (uint64_t)hHttpRequest;
    call.lpszHeader = (uint64_t)lpszHeader;
    call.dwHeaderLength = (uint64_t)dwHeaderLength;
    call.dwModifier = (uint64_t)dwModifier;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpAddRequestHeadersW(struct qemu_syscall *call)
{
    struct qemu_HttpAddRequestHeadersW *c = (struct qemu_HttpAddRequestHeadersW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpAddRequestHeadersW(QEMU_G2H(c->hHttpRequest), QEMU_G2H(c->lpszHeader), c->dwHeaderLength, c->dwModifier);
}

#endif

struct qemu_HttpAddRequestHeadersA
{
    struct qemu_syscall super;
    uint64_t hHttpRequest;
    uint64_t lpszHeader;
    uint64_t dwHeaderLength;
    uint64_t dwModifier;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpAddRequestHeadersA(HINTERNET hHttpRequest, LPCSTR lpszHeader, DWORD dwHeaderLength, DWORD dwModifier)
{
    struct qemu_HttpAddRequestHeadersA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPADDREQUESTHEADERSA);
    call.hHttpRequest = (uint64_t)hHttpRequest;
    call.lpszHeader = (uint64_t)lpszHeader;
    call.dwHeaderLength = (uint64_t)dwHeaderLength;
    call.dwModifier = (uint64_t)dwModifier;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpAddRequestHeadersA(struct qemu_syscall *call)
{
    struct qemu_HttpAddRequestHeadersA *c = (struct qemu_HttpAddRequestHeadersA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpAddRequestHeadersA(QEMU_G2H(c->hHttpRequest), QEMU_G2H(c->lpszHeader), c->dwHeaderLength, c->dwModifier);
}

#endif

struct qemu_HttpOpenRequestA
{
    struct qemu_syscall super;
    uint64_t hHttpSession;
    uint64_t lpszVerb;
    uint64_t lpszObjectName;
    uint64_t lpszVersion;
    uint64_t lpszReferrer;
    uint64_t lpszAcceptTypes;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI HttpOpenRequestA(HINTERNET hHttpSession, LPCSTR lpszVerb, LPCSTR lpszObjectName, LPCSTR lpszVersion, LPCSTR lpszReferrer , LPCSTR *lpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_HttpOpenRequestA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPOPENREQUESTA);
    call.hHttpSession = (uint64_t)hHttpSession;
    call.lpszVerb = (uint64_t)lpszVerb;
    call.lpszObjectName = (uint64_t)lpszObjectName;
    call.lpszVersion = (uint64_t)lpszVersion;
    call.lpszReferrer = (uint64_t)lpszReferrer;
    call.lpszAcceptTypes = (uint64_t)lpszAcceptTypes;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwContext = (uint64_t)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)call.super.iret;
}

#else

void qemu_HttpOpenRequestA(struct qemu_syscall *call)
{
    struct qemu_HttpOpenRequestA *c = (struct qemu_HttpOpenRequestA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)HttpOpenRequestA(QEMU_G2H(c->hHttpSession), QEMU_G2H(c->lpszVerb), QEMU_G2H(c->lpszObjectName), QEMU_G2H(c->lpszVersion), QEMU_G2H(c->lpszReferrer), QEMU_G2H(c->lpszAcceptTypes), c->dwFlags, c->dwContext);
}

#endif

struct qemu_HttpOpenRequestW
{
    struct qemu_syscall super;
    uint64_t hHttpSession;
    uint64_t lpszVerb;
    uint64_t lpszObjectName;
    uint64_t lpszVersion;
    uint64_t lpszReferrer;
    uint64_t lpszAcceptTypes;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI HttpOpenRequestW(HINTERNET hHttpSession, LPCWSTR lpszVerb, LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferrer , LPCWSTR *lpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_HttpOpenRequestW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPOPENREQUESTW);
    call.hHttpSession = (uint64_t)hHttpSession;
    call.lpszVerb = (uint64_t)lpszVerb;
    call.lpszObjectName = (uint64_t)lpszObjectName;
    call.lpszVersion = (uint64_t)lpszVersion;
    call.lpszReferrer = (uint64_t)lpszReferrer;
    call.lpszAcceptTypes = (uint64_t)lpszAcceptTypes;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwContext = (uint64_t)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)call.super.iret;
}

#else

void qemu_HttpOpenRequestW(struct qemu_syscall *call)
{
    struct qemu_HttpOpenRequestW *c = (struct qemu_HttpOpenRequestW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)HttpOpenRequestW(QEMU_G2H(c->hHttpSession), QEMU_G2H(c->lpszVerb), QEMU_G2H(c->lpszObjectName), QEMU_G2H(c->lpszVersion), QEMU_G2H(c->lpszReferrer), QEMU_G2H(c->lpszAcceptTypes), c->dwFlags, c->dwContext);
}

#endif

struct qemu_HttpQueryInfoW
{
    struct qemu_syscall super;
    uint64_t hHttpRequest;
    uint64_t dwInfoLevel;
    uint64_t lpBuffer;
    uint64_t lpdwBufferLength;
    uint64_t lpdwIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpQueryInfoW(HINTERNET hHttpRequest, DWORD dwInfoLevel, LPVOID lpBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex)
{
    struct qemu_HttpQueryInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPQUERYINFOW);
    call.hHttpRequest = (uint64_t)hHttpRequest;
    call.dwInfoLevel = (uint64_t)dwInfoLevel;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;
    call.lpdwIndex = (uint64_t)lpdwIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpQueryInfoW(struct qemu_syscall *call)
{
    struct qemu_HttpQueryInfoW *c = (struct qemu_HttpQueryInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpQueryInfoW(QEMU_G2H(c->hHttpRequest), c->dwInfoLevel, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwBufferLength), QEMU_G2H(c->lpdwIndex));
}

#endif

struct qemu_HttpQueryInfoA
{
    struct qemu_syscall super;
    uint64_t hHttpRequest;
    uint64_t dwInfoLevel;
    uint64_t lpBuffer;
    uint64_t lpdwBufferLength;
    uint64_t lpdwIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpQueryInfoA(HINTERNET hHttpRequest, DWORD dwInfoLevel, LPVOID lpBuffer, LPDWORD lpdwBufferLength, LPDWORD lpdwIndex)
{
    struct qemu_HttpQueryInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPQUERYINFOA);
    call.hHttpRequest = (uint64_t)hHttpRequest;
    call.dwInfoLevel = (uint64_t)dwInfoLevel;
    call.lpBuffer = (uint64_t)lpBuffer;
    call.lpdwBufferLength = (uint64_t)lpdwBufferLength;
    call.lpdwIndex = (uint64_t)lpdwIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpQueryInfoA(struct qemu_syscall *call)
{
    struct qemu_HttpQueryInfoA *c = (struct qemu_HttpQueryInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpQueryInfoA(QEMU_G2H(c->hHttpRequest), c->dwInfoLevel, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwBufferLength), QEMU_G2H(c->lpdwIndex));
}

#endif

struct qemu_HttpEndRequestA
{
    struct qemu_syscall super;
    uint64_t hRequest;
    uint64_t lpBuffersOut;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpEndRequestA(HINTERNET hRequest, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_HttpEndRequestA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPENDREQUESTA);
    call.hRequest = (uint64_t)hRequest;
    call.lpBuffersOut = (uint64_t)lpBuffersOut;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwContext = (uint64_t)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpEndRequestA(struct qemu_syscall *call)
{
    struct qemu_HttpEndRequestA *c = (struct qemu_HttpEndRequestA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpEndRequestA(QEMU_G2H(c->hRequest), QEMU_G2H(c->lpBuffersOut), c->dwFlags, c->dwContext);
}

#endif

struct qemu_HttpEndRequestW
{
    struct qemu_syscall super;
    uint64_t hRequest;
    uint64_t lpBuffersOut;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpEndRequestW(HINTERNET hRequest, LPINTERNET_BUFFERSW lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_HttpEndRequestW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPENDREQUESTW);
    call.hRequest = (uint64_t)hRequest;
    call.lpBuffersOut = (uint64_t)lpBuffersOut;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwContext = (uint64_t)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpEndRequestW(struct qemu_syscall *call)
{
    struct qemu_HttpEndRequestW *c = (struct qemu_HttpEndRequestW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpEndRequestW(QEMU_G2H(c->hRequest), QEMU_G2H(c->lpBuffersOut), c->dwFlags, c->dwContext);
}

#endif

struct qemu_HttpSendRequestExA
{
    struct qemu_syscall super;
    uint64_t hRequest;
    uint64_t lpBuffersIn;
    uint64_t lpBuffersOut;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpSendRequestExA(HINTERNET hRequest, LPINTERNET_BUFFERSA lpBuffersIn, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_HttpSendRequestExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPSENDREQUESTEXA);
    call.hRequest = (uint64_t)hRequest;
    call.lpBuffersIn = (uint64_t)lpBuffersIn;
    call.lpBuffersOut = (uint64_t)lpBuffersOut;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwContext = (uint64_t)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpSendRequestExA(struct qemu_syscall *call)
{
    struct qemu_HttpSendRequestExA *c = (struct qemu_HttpSendRequestExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpSendRequestExA(QEMU_G2H(c->hRequest), QEMU_G2H(c->lpBuffersIn), QEMU_G2H(c->lpBuffersOut), c->dwFlags, c->dwContext);
}

#endif

struct qemu_HttpSendRequestExW
{
    struct qemu_syscall super;
    uint64_t hRequest;
    uint64_t lpBuffersIn;
    uint64_t lpBuffersOut;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpSendRequestExW(HINTERNET hRequest, LPINTERNET_BUFFERSW lpBuffersIn, LPINTERNET_BUFFERSW lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_HttpSendRequestExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPSENDREQUESTEXW);
    call.hRequest = (uint64_t)hRequest;
    call.lpBuffersIn = (uint64_t)lpBuffersIn;
    call.lpBuffersOut = (uint64_t)lpBuffersOut;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwContext = (uint64_t)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpSendRequestExW(struct qemu_syscall *call)
{
    struct qemu_HttpSendRequestExW *c = (struct qemu_HttpSendRequestExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpSendRequestExW(QEMU_G2H(c->hRequest), QEMU_G2H(c->lpBuffersIn), QEMU_G2H(c->lpBuffersOut), c->dwFlags, c->dwContext);
}

#endif

struct qemu_HttpSendRequestW
{
    struct qemu_syscall super;
    uint64_t hHttpRequest;
    uint64_t lpszHeaders;
    uint64_t dwHeaderLength;
    uint64_t lpOptional;
    uint64_t dwOptionalLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpSendRequestW(HINTERNET hHttpRequest, LPCWSTR lpszHeaders, DWORD dwHeaderLength, LPVOID lpOptional ,DWORD dwOptionalLength)
{
    struct qemu_HttpSendRequestW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPSENDREQUESTW);
    call.hHttpRequest = (uint64_t)hHttpRequest;
    call.lpszHeaders = (uint64_t)lpszHeaders;
    call.dwHeaderLength = (uint64_t)dwHeaderLength;
    call.lpOptional = (uint64_t)lpOptional;
    call.dwOptionalLength = (uint64_t)dwOptionalLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpSendRequestW(struct qemu_syscall *call)
{
    struct qemu_HttpSendRequestW *c = (struct qemu_HttpSendRequestW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpSendRequestW(QEMU_G2H(c->hHttpRequest), QEMU_G2H(c->lpszHeaders), c->dwHeaderLength, QEMU_G2H(c->lpOptional), c->dwOptionalLength);
}

#endif

struct qemu_HttpSendRequestA
{
    struct qemu_syscall super;
    uint64_t hHttpRequest;
    uint64_t lpszHeaders;
    uint64_t dwHeaderLength;
    uint64_t lpOptional;
    uint64_t dwOptionalLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HttpSendRequestA(HINTERNET hHttpRequest, LPCSTR lpszHeaders, DWORD dwHeaderLength, LPVOID lpOptional ,DWORD dwOptionalLength)
{
    struct qemu_HttpSendRequestA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HTTPSENDREQUESTA);
    call.hHttpRequest = (uint64_t)hHttpRequest;
    call.lpszHeaders = (uint64_t)lpszHeaders;
    call.dwHeaderLength = (uint64_t)dwHeaderLength;
    call.lpOptional = (uint64_t)lpOptional;
    call.dwOptionalLength = (uint64_t)dwOptionalLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HttpSendRequestA(struct qemu_syscall *call)
{
    struct qemu_HttpSendRequestA *c = (struct qemu_HttpSendRequestA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HttpSendRequestA(QEMU_G2H(c->hHttpRequest), QEMU_G2H(c->lpszHeaders), c->dwHeaderLength, QEMU_G2H(c->lpOptional), c->dwOptionalLength);
}

#endif

struct qemu_IsHostInProxyBypassList
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t szHost;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsHostInProxyBypassList(DWORD flags, LPCSTR szHost, DWORD length)
{
    struct qemu_IsHostInProxyBypassList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISHOSTINPROXYBYPASSLIST);
    call.flags = (uint64_t)flags;
    call.szHost = (uint64_t)szHost;
    call.length = (uint64_t)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsHostInProxyBypassList to Wine headers? */
extern BOOL WINAPI IsHostInProxyBypassList(DWORD flags, LPCSTR szHost, DWORD length);
void qemu_IsHostInProxyBypassList(struct qemu_syscall *call)
{
    struct qemu_IsHostInProxyBypassList *c = (struct qemu_IsHostInProxyBypassList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsHostInProxyBypassList(c->flags, QEMU_G2H(c->szHost), c->length);
}

#endif

