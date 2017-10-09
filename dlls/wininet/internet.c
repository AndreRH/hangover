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

struct qemu_InternetInitializeAutoProxyDll
{
    struct qemu_syscall super;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetInitializeAutoProxyDll(DWORD dwReserved)
{
    struct qemu_InternetInitializeAutoProxyDll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETINITIALIZEAUTOPROXYDLL);
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetInitializeAutoProxyDll(struct qemu_syscall *call)
{
    struct qemu_InternetInitializeAutoProxyDll *c = (struct qemu_InternetInitializeAutoProxyDll *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetInitializeAutoProxyDll(c->dwReserved);
}

#endif

struct qemu_DetectAutoProxyUrl
{
    struct qemu_syscall super;
    uint64_t lpszAutoProxyUrl;
    uint64_t dwAutoProxyUrlLength;
    uint64_t dwDetectFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DetectAutoProxyUrl(LPSTR lpszAutoProxyUrl, DWORD dwAutoProxyUrlLength, DWORD dwDetectFlags)
{
    struct qemu_DetectAutoProxyUrl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DETECTAUTOPROXYURL);
    call.lpszAutoProxyUrl = (ULONG_PTR)lpszAutoProxyUrl;
    call.dwAutoProxyUrlLength = (ULONG_PTR)dwAutoProxyUrlLength;
    call.dwDetectFlags = (ULONG_PTR)dwDetectFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DetectAutoProxyUrl(struct qemu_syscall *call)
{
    struct qemu_DetectAutoProxyUrl *c = (struct qemu_DetectAutoProxyUrl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DetectAutoProxyUrl(QEMU_G2H(c->lpszAutoProxyUrl), c->dwAutoProxyUrlLength, c->dwDetectFlags);
}

#endif

struct qemu_InternetOpenW
{
    struct qemu_syscall super;
    uint64_t lpszAgent;
    uint64_t dwAccessType;
    uint64_t lpszProxy;
    uint64_t lpszProxyBypass;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI InternetOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
    struct qemu_InternetOpenW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETOPENW);
    call.lpszAgent = (ULONG_PTR)lpszAgent;
    call.dwAccessType = (ULONG_PTR)dwAccessType;
    call.lpszProxy = (ULONG_PTR)lpszProxy;
    call.lpszProxyBypass = (ULONG_PTR)lpszProxyBypass;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetOpenW(struct qemu_syscall *call)
{
    struct qemu_InternetOpenW *c = (struct qemu_InternetOpenW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetOpenW(QEMU_G2H(c->lpszAgent), c->dwAccessType, QEMU_G2H(c->lpszProxy), QEMU_G2H(c->lpszProxyBypass), c->dwFlags);
}

#endif

struct qemu_InternetOpenA
{
    struct qemu_syscall super;
    uint64_t lpszAgent;
    uint64_t dwAccessType;
    uint64_t lpszProxy;
    uint64_t lpszProxyBypass;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI InternetOpenA(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags)
{
    struct qemu_InternetOpenA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETOPENA);
    call.lpszAgent = (ULONG_PTR)lpszAgent;
    call.dwAccessType = (ULONG_PTR)dwAccessType;
    call.lpszProxy = (ULONG_PTR)lpszProxy;
    call.lpszProxyBypass = (ULONG_PTR)lpszProxyBypass;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetOpenA(struct qemu_syscall *call)
{
    struct qemu_InternetOpenA *c = (struct qemu_InternetOpenA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetOpenA(QEMU_G2H(c->lpszAgent), c->dwAccessType, QEMU_G2H(c->lpszProxy), QEMU_G2H(c->lpszProxyBypass), c->dwFlags);
}

#endif

struct qemu_InternetGetLastResponseInfoA
{
    struct qemu_syscall super;
    uint64_t lpdwError;
    uint64_t lpszBuffer;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetLastResponseInfoA(LPDWORD lpdwError, LPSTR lpszBuffer, LPDWORD lpdwBufferLength)
{
    struct qemu_InternetGetLastResponseInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETLASTRESPONSEINFOA);
    call.lpdwError = (ULONG_PTR)lpdwError;
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetLastResponseInfoA(struct qemu_syscall *call)
{
    struct qemu_InternetGetLastResponseInfoA *c = (struct qemu_InternetGetLastResponseInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetLastResponseInfoA(QEMU_G2H(c->lpdwError), QEMU_G2H(c->lpszBuffer), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_InternetGetLastResponseInfoW
{
    struct qemu_syscall super;
    uint64_t lpdwError;
    uint64_t lpszBuffer;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetLastResponseInfoW(LPDWORD lpdwError, LPWSTR lpszBuffer, LPDWORD lpdwBufferLength)
{
    struct qemu_InternetGetLastResponseInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETLASTRESPONSEINFOW);
    call.lpdwError = (ULONG_PTR)lpdwError;
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetLastResponseInfoW(struct qemu_syscall *call)
{
    struct qemu_InternetGetLastResponseInfoW *c = (struct qemu_InternetGetLastResponseInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetLastResponseInfoW(QEMU_G2H(c->lpdwError), QEMU_G2H(c->lpszBuffer), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_InternetGetConnectedState
{
    struct qemu_syscall super;
    uint64_t lpdwStatus;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetConnectedState(LPDWORD lpdwStatus, DWORD dwReserved)
{
    struct qemu_InternetGetConnectedState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCONNECTEDSTATE);
    call.lpdwStatus = (ULONG_PTR)lpdwStatus;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetConnectedState(struct qemu_syscall *call)
{
    struct qemu_InternetGetConnectedState *c = (struct qemu_InternetGetConnectedState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetConnectedState(QEMU_G2H(c->lpdwStatus), c->dwReserved);
}

#endif

struct qemu_InternetGetConnectedStateExW
{
    struct qemu_syscall super;
    uint64_t lpdwStatus;
    uint64_t lpszConnectionName;
    uint64_t dwNameLen;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetConnectedStateExW(LPDWORD lpdwStatus, LPWSTR lpszConnectionName, DWORD dwNameLen, DWORD dwReserved)
{
    struct qemu_InternetGetConnectedStateExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCONNECTEDSTATEEXW);
    call.lpdwStatus = (ULONG_PTR)lpdwStatus;
    call.lpszConnectionName = (ULONG_PTR)lpszConnectionName;
    call.dwNameLen = (ULONG_PTR)dwNameLen;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetConnectedStateExW(struct qemu_syscall *call)
{
    struct qemu_InternetGetConnectedStateExW *c = (struct qemu_InternetGetConnectedStateExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetConnectedStateExW(QEMU_G2H(c->lpdwStatus), QEMU_G2H(c->lpszConnectionName), c->dwNameLen, c->dwReserved);
}

#endif

struct qemu_InternetGetConnectedStateExA
{
    struct qemu_syscall super;
    uint64_t lpdwStatus;
    uint64_t lpszConnectionName;
    uint64_t dwNameLen;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetConnectedStateExA(LPDWORD lpdwStatus, LPSTR lpszConnectionName, DWORD dwNameLen, DWORD dwReserved)
{
    struct qemu_InternetGetConnectedStateExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCONNECTEDSTATEEXA);
    call.lpdwStatus = (ULONG_PTR)lpdwStatus;
    call.lpszConnectionName = (ULONG_PTR)lpszConnectionName;
    call.dwNameLen = (ULONG_PTR)dwNameLen;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetConnectedStateExA(struct qemu_syscall *call)
{
    struct qemu_InternetGetConnectedStateExA *c = (struct qemu_InternetGetConnectedStateExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetConnectedStateExA(QEMU_G2H(c->lpdwStatus), QEMU_G2H(c->lpszConnectionName), c->dwNameLen, c->dwReserved);
}

#endif

struct qemu_InternetConnectW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpszServerName;
    uint64_t nServerPort;
    uint64_t lpszUserName;
    uint64_t lpszPassword;
    uint64_t dwService;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI InternetConnectW(HINTERNET hInternet, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, LPCWSTR lpszUserName, LPCWSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetConnectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCONNECTW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpszServerName = (ULONG_PTR)lpszServerName;
    call.nServerPort = (ULONG_PTR)nServerPort;
    call.lpszUserName = (ULONG_PTR)lpszUserName;
    call.lpszPassword = (ULONG_PTR)lpszPassword;
    call.dwService = (ULONG_PTR)dwService;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetConnectW(struct qemu_syscall *call)
{
    struct qemu_InternetConnectW *c = (struct qemu_InternetConnectW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetConnectW(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpszServerName), c->nServerPort, QEMU_G2H(c->lpszUserName), QEMU_G2H(c->lpszPassword), c->dwService, c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetConnectA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpszServerName;
    uint64_t nServerPort;
    uint64_t lpszUserName;
    uint64_t lpszPassword;
    uint64_t dwService;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI InternetConnectA(HINTERNET hInternet, LPCSTR lpszServerName, INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetConnectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCONNECTA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpszServerName = (ULONG_PTR)lpszServerName;
    call.nServerPort = (ULONG_PTR)nServerPort;
    call.lpszUserName = (ULONG_PTR)lpszUserName;
    call.lpszPassword = (ULONG_PTR)lpszPassword;
    call.dwService = (ULONG_PTR)dwService;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetConnectA(struct qemu_syscall *call)
{
    struct qemu_InternetConnectA *c = (struct qemu_InternetConnectA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetConnectA(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpszServerName), c->nServerPort, QEMU_G2H(c->lpszUserName), QEMU_G2H(c->lpszPassword), c->dwService, c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetFindNextFileA
{
    struct qemu_syscall super;
    uint64_t hFind;
    uint64_t lpvFindData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetFindNextFileA(HINTERNET hFind, LPVOID lpvFindData)
{
    struct qemu_InternetFindNextFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETFINDNEXTFILEA);
    call.hFind = (ULONG_PTR)hFind;
    call.lpvFindData = (ULONG_PTR)lpvFindData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetFindNextFileA(struct qemu_syscall *call)
{
    struct qemu_InternetFindNextFileA *c = (struct qemu_InternetFindNextFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetFindNextFileA(QEMU_G2H(c->hFind), QEMU_G2H(c->lpvFindData));
}

#endif

struct qemu_InternetFindNextFileW
{
    struct qemu_syscall super;
    uint64_t hFind;
    uint64_t lpvFindData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetFindNextFileW(HINTERNET hFind, LPVOID lpvFindData)
{
    struct qemu_InternetFindNextFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETFINDNEXTFILEW);
    call.hFind = (ULONG_PTR)hFind;
    call.lpvFindData = (ULONG_PTR)lpvFindData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetFindNextFileW(struct qemu_syscall *call)
{
    struct qemu_InternetFindNextFileW *c = (struct qemu_InternetFindNextFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetFindNextFileW(QEMU_G2H(c->hFind), QEMU_G2H(c->lpvFindData));
}

#endif

struct qemu_InternetCloseHandle
{
    struct qemu_syscall super;
    uint64_t hInternet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCloseHandle(HINTERNET hInternet)
{
    struct qemu_InternetCloseHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCLOSEHANDLE);
    call.hInternet = (ULONG_PTR)hInternet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCloseHandle(struct qemu_syscall *call)
{
    struct qemu_InternetCloseHandle *c = (struct qemu_InternetCloseHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCloseHandle(QEMU_G2H(c->hInternet));
}

#endif

struct qemu_InternetCrackUrlA
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t url_length;
    uint64_t flags;
    uint64_t ret_comp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCrackUrlA(const char *url, DWORD url_length, DWORD flags, URL_COMPONENTSA *ret_comp)
{
    struct qemu_InternetCrackUrlA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCRACKURLA);
    call.url = (ULONG_PTR)url;
    call.url_length = (ULONG_PTR)url_length;
    call.flags = (ULONG_PTR)flags;
    call.ret_comp = (ULONG_PTR)ret_comp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCrackUrlA(struct qemu_syscall *call)
{
    struct qemu_InternetCrackUrlA *c = (struct qemu_InternetCrackUrlA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCrackUrlA(QEMU_G2H(c->url), c->url_length, c->flags, QEMU_G2H(c->ret_comp));
}

#endif

struct qemu_InternetCrackUrlW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t dwUrlLength;
    uint64_t dwFlags;
    uint64_t lpUC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCrackUrlW(const WCHAR *lpszUrl, DWORD dwUrlLength, DWORD dwFlags, URL_COMPONENTSW *lpUC)
{
    struct qemu_InternetCrackUrlW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCRACKURLW);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.dwUrlLength = (ULONG_PTR)dwUrlLength;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpUC = (ULONG_PTR)lpUC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCrackUrlW(struct qemu_syscall *call)
{
    struct qemu_InternetCrackUrlW *c = (struct qemu_InternetCrackUrlW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCrackUrlW(QEMU_G2H(c->lpszUrl), c->dwUrlLength, c->dwFlags, QEMU_G2H(c->lpUC));
}

#endif

struct qemu_InternetAttemptConnect
{
    struct qemu_syscall super;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetAttemptConnect(DWORD dwReserved)
{
    struct qemu_InternetAttemptConnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETATTEMPTCONNECT);
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetAttemptConnect(struct qemu_syscall *call)
{
    struct qemu_InternetAttemptConnect *c = (struct qemu_InternetAttemptConnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetAttemptConnect(c->dwReserved);
}

#endif

struct qemu_InternetCanonicalizeUrlA
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpszBuffer;
    uint64_t lpdwBufferLength;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCanonicalizeUrlA(LPCSTR lpszUrl, LPSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)
{
    struct qemu_InternetCanonicalizeUrlA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCANONICALIZEURLA);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCanonicalizeUrlA(struct qemu_syscall *call)
{
    struct qemu_InternetCanonicalizeUrlA *c = (struct qemu_InternetCanonicalizeUrlA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCanonicalizeUrlA(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszBuffer), QEMU_G2H(c->lpdwBufferLength), c->dwFlags);
}

#endif

struct qemu_InternetCanonicalizeUrlW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpszBuffer;
    uint64_t lpdwBufferLength;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCanonicalizeUrlW(LPCWSTR lpszUrl, LPWSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)
{
    struct qemu_InternetCanonicalizeUrlW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCANONICALIZEURLW);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCanonicalizeUrlW(struct qemu_syscall *call)
{
    struct qemu_InternetCanonicalizeUrlW *c = (struct qemu_InternetCanonicalizeUrlW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCanonicalizeUrlW(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszBuffer), QEMU_G2H(c->lpdwBufferLength), c->dwFlags);
}

#endif

struct qemu_InternetSetStatusCallbackA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpfnIntCB;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INTERNET_STATUS_CALLBACK WINAPI InternetSetStatusCallbackA(HINTERNET hInternet ,INTERNET_STATUS_CALLBACK lpfnIntCB)
{
    struct qemu_InternetSetStatusCallbackA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETSTATUSCALLBACKA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpfnIntCB = (ULONG_PTR)lpfnIntCB;

    qemu_syscall(&call.super);

    return (INTERNET_STATUS_CALLBACK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetSetStatusCallbackA(struct qemu_syscall *call)
{
    struct qemu_InternetSetStatusCallbackA *c = (struct qemu_InternetSetStatusCallbackA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetSetStatusCallbackA(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpfnIntCB));
}

#endif

struct qemu_InternetSetStatusCallbackW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpfnIntCB;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INTERNET_STATUS_CALLBACK WINAPI InternetSetStatusCallbackW(HINTERNET hInternet ,INTERNET_STATUS_CALLBACK lpfnIntCB)
{
    struct qemu_InternetSetStatusCallbackW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETSTATUSCALLBACKW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpfnIntCB = (ULONG_PTR)lpfnIntCB;

    qemu_syscall(&call.super);

    return (INTERNET_STATUS_CALLBACK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetSetStatusCallbackW(struct qemu_syscall *call)
{
    struct qemu_InternetSetStatusCallbackW *c = (struct qemu_InternetSetStatusCallbackW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetSetStatusCallbackW(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpfnIntCB));
}

#endif

struct qemu_InternetSetFilePointer
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lDistanceToMove;
    uint64_t pReserved;
    uint64_t dwMoveContext;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetSetFilePointer(HINTERNET hFile, LONG lDistanceToMove, PVOID pReserved, DWORD dwMoveContext, DWORD_PTR dwContext)
{
    struct qemu_InternetSetFilePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETFILEPOINTER);
    call.hFile = (ULONG_PTR)hFile;
    call.lDistanceToMove = (ULONG_PTR)lDistanceToMove;
    call.pReserved = (ULONG_PTR)pReserved;
    call.dwMoveContext = (ULONG_PTR)dwMoveContext;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetFilePointer(struct qemu_syscall *call)
{
    struct qemu_InternetSetFilePointer *c = (struct qemu_InternetSetFilePointer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetFilePointer(QEMU_G2H(c->hFile), c->lDistanceToMove, QEMU_G2H(c->pReserved), c->dwMoveContext, c->dwContext);
}

#endif

struct qemu_InternetWriteFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpBuffer;
    uint64_t dwNumOfBytesToWrite;
    uint64_t lpdwNumOfBytesWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetWriteFile(HINTERNET hFile, LPCVOID lpBuffer, DWORD dwNumOfBytesToWrite, LPDWORD lpdwNumOfBytesWritten)
{
    struct qemu_InternetWriteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETWRITEFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwNumOfBytesToWrite = (ULONG_PTR)dwNumOfBytesToWrite;
    call.lpdwNumOfBytesWritten = (ULONG_PTR)lpdwNumOfBytesWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetWriteFile(struct qemu_syscall *call)
{
    struct qemu_InternetWriteFile *c = (struct qemu_InternetWriteFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetWriteFile(QEMU_G2H(c->hFile), QEMU_G2H(c->lpBuffer), c->dwNumOfBytesToWrite, QEMU_G2H(c->lpdwNumOfBytesWritten));
}

#endif

struct qemu_InternetReadFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpBuffer;
    uint64_t dwNumOfBytesToRead;
    uint64_t pdwNumOfBytesRead;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetReadFile(HINTERNET hFile, LPVOID lpBuffer, DWORD dwNumOfBytesToRead, LPDWORD pdwNumOfBytesRead)
{
    struct qemu_InternetReadFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETREADFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwNumOfBytesToRead = (ULONG_PTR)dwNumOfBytesToRead;
    call.pdwNumOfBytesRead = (ULONG_PTR)pdwNumOfBytesRead;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetReadFile(struct qemu_syscall *call)
{
    struct qemu_InternetReadFile *c = (struct qemu_InternetReadFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetReadFile(QEMU_G2H(c->hFile), QEMU_G2H(c->lpBuffer), c->dwNumOfBytesToRead, QEMU_G2H(c->pdwNumOfBytesRead));
}

#endif

struct qemu_InternetReadFileExA
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpBuffersOut;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetReadFileExA(HINTERNET hFile, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetReadFileExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETREADFILEEXA);
    call.hFile = (ULONG_PTR)hFile;
    call.lpBuffersOut = (ULONG_PTR)lpBuffersOut;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetReadFileExA(struct qemu_syscall *call)
{
    struct qemu_InternetReadFileExA *c = (struct qemu_InternetReadFileExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetReadFileExA(QEMU_G2H(c->hFile), QEMU_G2H(c->lpBuffersOut), c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetReadFileExW
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpBuffer;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetReadFileExW(HINTERNET hFile, LPINTERNET_BUFFERSW lpBuffer, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetReadFileExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETREADFILEEXW);
    call.hFile = (ULONG_PTR)hFile;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetReadFileExW(struct qemu_syscall *call)
{
    struct qemu_InternetReadFileExW *c = (struct qemu_InternetReadFileExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetReadFileExW(QEMU_G2H(c->hFile), QEMU_G2H(c->lpBuffer), c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetQueryOptionW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwOption;
    uint64_t lpBuffer;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetQueryOptionW(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, LPDWORD lpdwBufferLength)
{
    struct qemu_InternetQueryOptionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETQUERYOPTIONW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwOption = (ULONG_PTR)dwOption;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetQueryOptionW(struct qemu_syscall *call)
{
    struct qemu_InternetQueryOptionW *c = (struct qemu_InternetQueryOptionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetQueryOptionW(QEMU_G2H(c->hInternet), c->dwOption, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_InternetQueryOptionA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwOption;
    uint64_t lpBuffer;
    uint64_t lpdwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetQueryOptionA(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, LPDWORD lpdwBufferLength)
{
    struct qemu_InternetQueryOptionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETQUERYOPTIONA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwOption = (ULONG_PTR)dwOption;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetQueryOptionA(struct qemu_syscall *call)
{
    struct qemu_InternetQueryOptionA *c = (struct qemu_InternetQueryOptionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetQueryOptionA(QEMU_G2H(c->hInternet), c->dwOption, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwBufferLength));
}

#endif

struct qemu_InternetSetOptionW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwOption;
    uint64_t lpBuffer;
    uint64_t dwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetOptionW(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength)
{
    struct qemu_InternetSetOptionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETOPTIONW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwOption = (ULONG_PTR)dwOption;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwBufferLength = (ULONG_PTR)dwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetOptionW(struct qemu_syscall *call)
{
    struct qemu_InternetSetOptionW *c = (struct qemu_InternetSetOptionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetOptionW(QEMU_G2H(c->hInternet), c->dwOption, QEMU_G2H(c->lpBuffer), c->dwBufferLength);
}

#endif

struct qemu_InternetSetOptionA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwOption;
    uint64_t lpBuffer;
    uint64_t dwBufferLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetOptionA(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength)
{
    struct qemu_InternetSetOptionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETOPTIONA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwOption = (ULONG_PTR)dwOption;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwBufferLength = (ULONG_PTR)dwBufferLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetOptionA(struct qemu_syscall *call)
{
    struct qemu_InternetSetOptionA *c = (struct qemu_InternetSetOptionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetOptionA(QEMU_G2H(c->hInternet), c->dwOption, QEMU_G2H(c->lpBuffer), c->dwBufferLength);
}

#endif

struct qemu_InternetSetOptionExA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwOption;
    uint64_t lpBuffer;
    uint64_t dwBufferLength;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetOptionExA(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength, DWORD dwFlags)
{
    struct qemu_InternetSetOptionExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETOPTIONEXA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwOption = (ULONG_PTR)dwOption;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwBufferLength = (ULONG_PTR)dwBufferLength;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetOptionExA(struct qemu_syscall *call)
{
    struct qemu_InternetSetOptionExA *c = (struct qemu_InternetSetOptionExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetOptionExA(QEMU_G2H(c->hInternet), c->dwOption, QEMU_G2H(c->lpBuffer), c->dwBufferLength, c->dwFlags);
}

#endif

struct qemu_InternetSetOptionExW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwOption;
    uint64_t lpBuffer;
    uint64_t dwBufferLength;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetOptionExW(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength, DWORD dwFlags)
{
    struct qemu_InternetSetOptionExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETOPTIONEXW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwOption = (ULONG_PTR)dwOption;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.dwBufferLength = (ULONG_PTR)dwBufferLength;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetOptionExW(struct qemu_syscall *call)
{
    struct qemu_InternetSetOptionExW *c = (struct qemu_InternetSetOptionExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetOptionExW(QEMU_G2H(c->hInternet), c->dwOption, QEMU_G2H(c->lpBuffer), c->dwBufferLength, c->dwFlags);
}

#endif

struct qemu_InternetTimeFromSystemTimeA
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t format;
    uint64_t string;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetTimeFromSystemTimeA(const SYSTEMTIME* time, DWORD format, LPSTR string, DWORD size)
{
    struct qemu_InternetTimeFromSystemTimeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETTIMEFROMSYSTEMTIMEA);
    call.time = (ULONG_PTR)time;
    call.format = (ULONG_PTR)format;
    call.string = (ULONG_PTR)string;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetTimeFromSystemTimeA(struct qemu_syscall *call)
{
    struct qemu_InternetTimeFromSystemTimeA *c = (struct qemu_InternetTimeFromSystemTimeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetTimeFromSystemTimeA(QEMU_G2H(c->time), c->format, QEMU_G2H(c->string), c->size);
}

#endif

struct qemu_InternetTimeFromSystemTimeW
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t format;
    uint64_t string;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetTimeFromSystemTimeW(const SYSTEMTIME* time, DWORD format, LPWSTR string, DWORD size)
{
    struct qemu_InternetTimeFromSystemTimeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETTIMEFROMSYSTEMTIMEW);
    call.time = (ULONG_PTR)time;
    call.format = (ULONG_PTR)format;
    call.string = (ULONG_PTR)string;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetTimeFromSystemTimeW(struct qemu_syscall *call)
{
    struct qemu_InternetTimeFromSystemTimeW *c = (struct qemu_InternetTimeFromSystemTimeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetTimeFromSystemTimeW(QEMU_G2H(c->time), c->format, QEMU_G2H(c->string), c->size);
}

#endif

struct qemu_InternetTimeToSystemTimeA
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t time;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetTimeToSystemTimeA(LPCSTR string, SYSTEMTIME* time, DWORD reserved)
{
    struct qemu_InternetTimeToSystemTimeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETTIMETOSYSTEMTIMEA);
    call.string = (ULONG_PTR)string;
    call.time = (ULONG_PTR)time;
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetTimeToSystemTimeA(struct qemu_syscall *call)
{
    struct qemu_InternetTimeToSystemTimeA *c = (struct qemu_InternetTimeToSystemTimeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetTimeToSystemTimeA(QEMU_G2H(c->string), QEMU_G2H(c->time), c->reserved);
}

#endif

struct qemu_InternetTimeToSystemTimeW
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t time;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetTimeToSystemTimeW(LPCWSTR string, SYSTEMTIME* time, DWORD reserved)
{
    struct qemu_InternetTimeToSystemTimeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETTIMETOSYSTEMTIMEW);
    call.string = (ULONG_PTR)string;
    call.time = (ULONG_PTR)time;
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetTimeToSystemTimeW(struct qemu_syscall *call)
{
    struct qemu_InternetTimeToSystemTimeW *c = (struct qemu_InternetTimeToSystemTimeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetTimeToSystemTimeW(QEMU_G2H(c->string), QEMU_G2H(c->time), c->reserved);
}

#endif

struct qemu_InternetCheckConnectionW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t dwFlags;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCheckConnectionW(LPCWSTR lpszUrl, DWORD dwFlags, DWORD dwReserved)
{
    struct qemu_InternetCheckConnectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCHECKCONNECTIONW);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCheckConnectionW(struct qemu_syscall *call)
{
    struct qemu_InternetCheckConnectionW *c = (struct qemu_InternetCheckConnectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCheckConnectionW(QEMU_G2H(c->lpszUrl), c->dwFlags, c->dwReserved);
}

#endif

struct qemu_InternetCheckConnectionA
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t dwFlags;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCheckConnectionA(LPCSTR lpszUrl, DWORD dwFlags, DWORD dwReserved)
{
    struct qemu_InternetCheckConnectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCHECKCONNECTIONA);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCheckConnectionA(struct qemu_syscall *call)
{
    struct qemu_InternetCheckConnectionA *c = (struct qemu_InternetCheckConnectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCheckConnectionA(QEMU_G2H(c->lpszUrl), c->dwFlags, c->dwReserved);
}

#endif

struct qemu_InternetOpenUrlW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpszUrl;
    uint64_t lpszHeaders;
    uint64_t dwHeadersLength;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI InternetOpenUrlW(HINTERNET hInternet, LPCWSTR lpszUrl, LPCWSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetOpenUrlW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETOPENURLW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpszHeaders = (ULONG_PTR)lpszHeaders;
    call.dwHeadersLength = (ULONG_PTR)dwHeadersLength;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetOpenUrlW(struct qemu_syscall *call)
{
    struct qemu_InternetOpenUrlW *c = (struct qemu_InternetOpenUrlW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetOpenUrlW(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszHeaders), c->dwHeadersLength, c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetOpenUrlA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpszUrl;
    uint64_t lpszHeaders;
    uint64_t dwHeadersLength;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI InternetOpenUrlA(HINTERNET hInternet, LPCSTR lpszUrl, LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetOpenUrlA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETOPENURLA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpszHeaders = (ULONG_PTR)lpszHeaders;
    call.dwHeadersLength = (ULONG_PTR)dwHeadersLength;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InternetOpenUrlA(struct qemu_syscall *call)
{
    struct qemu_InternetOpenUrlA *c = (struct qemu_InternetOpenUrlA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)InternetOpenUrlA(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszHeaders), c->dwHeadersLength, c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetQueryDataAvailable
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpdwNumberOfBytesAvailable;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetQueryDataAvailable(HINTERNET hFile, LPDWORD lpdwNumberOfBytesAvailable, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_InternetQueryDataAvailable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETQUERYDATAAVAILABLE);
    call.hFile = (ULONG_PTR)hFile;
    call.lpdwNumberOfBytesAvailable = (ULONG_PTR)lpdwNumberOfBytesAvailable;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetQueryDataAvailable(struct qemu_syscall *call)
{
    struct qemu_InternetQueryDataAvailable *c = (struct qemu_InternetQueryDataAvailable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetQueryDataAvailable(QEMU_G2H(c->hFile), QEMU_G2H(c->lpdwNumberOfBytesAvailable), c->dwFlags, c->dwContext);
}

#endif

struct qemu_InternetLockRequestFile
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lphLockReqHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetLockRequestFile(HINTERNET hInternet, HANDLE *lphLockReqHandle)
{
    struct qemu_InternetLockRequestFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETLOCKREQUESTFILE);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lphLockReqHandle = (ULONG_PTR)lphLockReqHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetLockRequestFile(struct qemu_syscall *call)
{
    struct qemu_InternetLockRequestFile *c = (struct qemu_InternetLockRequestFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetLockRequestFile(QEMU_G2H(c->hInternet), QEMU_G2H(c->lphLockReqHandle));
}

#endif

struct qemu_InternetUnlockRequestFile
{
    struct qemu_syscall super;
    uint64_t hLockHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetUnlockRequestFile(HANDLE hLockHandle)
{
    struct qemu_InternetUnlockRequestFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETUNLOCKREQUESTFILE);
    call.hLockHandle = (ULONG_PTR)hLockHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetUnlockRequestFile(struct qemu_syscall *call)
{
    struct qemu_InternetUnlockRequestFile *c = (struct qemu_InternetUnlockRequestFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetUnlockRequestFile(QEMU_G2H(c->hLockHandle));
}

#endif

struct qemu_InternetAutodial
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t hwndParent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetAutodial(DWORD dwFlags, HWND hwndParent)
{
    struct qemu_InternetAutodial call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETAUTODIAL);
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.hwndParent = (ULONG_PTR)hwndParent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetAutodial(struct qemu_syscall *call)
{
    struct qemu_InternetAutodial *c = (struct qemu_InternetAutodial *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetAutodial(c->dwFlags, QEMU_G2H(c->hwndParent));
}

#endif

struct qemu_InternetAutodialHangup
{
    struct qemu_syscall super;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetAutodialHangup(DWORD dwReserved)
{
    struct qemu_InternetAutodialHangup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETAUTODIALHANGUP);
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetAutodialHangup(struct qemu_syscall *call)
{
    struct qemu_InternetAutodialHangup *c = (struct qemu_InternetAutodialHangup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetAutodialHangup(c->dwReserved);
}

#endif

struct qemu_InternetCombineUrlA
{
    struct qemu_syscall super;
    uint64_t lpszBaseUrl;
    uint64_t lpszRelativeUrl;
    uint64_t lpszBuffer;
    uint64_t lpdwBufferLength;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCombineUrlA(LPCSTR lpszBaseUrl, LPCSTR lpszRelativeUrl, LPSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)
{
    struct qemu_InternetCombineUrlA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCOMBINEURLA);
    call.lpszBaseUrl = (ULONG_PTR)lpszBaseUrl;
    call.lpszRelativeUrl = (ULONG_PTR)lpszRelativeUrl;
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCombineUrlA(struct qemu_syscall *call)
{
    struct qemu_InternetCombineUrlA *c = (struct qemu_InternetCombineUrlA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCombineUrlA(QEMU_G2H(c->lpszBaseUrl), QEMU_G2H(c->lpszRelativeUrl), QEMU_G2H(c->lpszBuffer), QEMU_G2H(c->lpdwBufferLength), c->dwFlags);
}

#endif

struct qemu_InternetCombineUrlW
{
    struct qemu_syscall super;
    uint64_t lpszBaseUrl;
    uint64_t lpszRelativeUrl;
    uint64_t lpszBuffer;
    uint64_t lpdwBufferLength;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCombineUrlW(LPCWSTR lpszBaseUrl, LPCWSTR lpszRelativeUrl, LPWSTR lpszBuffer, LPDWORD lpdwBufferLength, DWORD dwFlags)
{
    struct qemu_InternetCombineUrlW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCOMBINEURLW);
    call.lpszBaseUrl = (ULONG_PTR)lpszBaseUrl;
    call.lpszRelativeUrl = (ULONG_PTR)lpszRelativeUrl;
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.lpdwBufferLength = (ULONG_PTR)lpdwBufferLength;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCombineUrlW(struct qemu_syscall *call)
{
    struct qemu_InternetCombineUrlW *c = (struct qemu_InternetCombineUrlW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCombineUrlW(QEMU_G2H(c->lpszBaseUrl), QEMU_G2H(c->lpszRelativeUrl), QEMU_G2H(c->lpszBuffer), QEMU_G2H(c->lpdwBufferLength), c->dwFlags);
}

#endif

struct qemu_InternetCreateUrlA
{
    struct qemu_syscall super;
    uint64_t lpUrlComponents;
    uint64_t dwFlags;
    uint64_t lpszUrl;
    uint64_t lpdwUrlLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCreateUrlA(LPURL_COMPONENTSA lpUrlComponents, DWORD dwFlags, LPSTR lpszUrl, LPDWORD lpdwUrlLength)
{
    struct qemu_InternetCreateUrlA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCREATEURLA);
    call.lpUrlComponents = (ULONG_PTR)lpUrlComponents;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpdwUrlLength = (ULONG_PTR)lpdwUrlLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCreateUrlA(struct qemu_syscall *call)
{
    struct qemu_InternetCreateUrlA *c = (struct qemu_InternetCreateUrlA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCreateUrlA(QEMU_G2H(c->lpUrlComponents), c->dwFlags, QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpdwUrlLength));
}

#endif

struct qemu_InternetCreateUrlW
{
    struct qemu_syscall super;
    uint64_t lpUrlComponents;
    uint64_t dwFlags;
    uint64_t lpszUrl;
    uint64_t lpdwUrlLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetCreateUrlW(LPURL_COMPONENTSW lpUrlComponents, DWORD dwFlags, LPWSTR lpszUrl, LPDWORD lpdwUrlLength)
{
    struct qemu_InternetCreateUrlW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCREATEURLW);
    call.lpUrlComponents = (ULONG_PTR)lpUrlComponents;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpdwUrlLength = (ULONG_PTR)lpdwUrlLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetCreateUrlW(struct qemu_syscall *call)
{
    struct qemu_InternetCreateUrlW *c = (struct qemu_InternetCreateUrlW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetCreateUrlW(QEMU_G2H(c->lpUrlComponents), c->dwFlags, QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpdwUrlLength));
}

#endif

struct qemu_InternetConfirmZoneCrossingA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t szUrlPrev;
    uint64_t szUrlNew;
    uint64_t bPost;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetConfirmZoneCrossingA(HWND hWnd, LPSTR szUrlPrev, LPSTR szUrlNew, BOOL bPost)
{
    struct qemu_InternetConfirmZoneCrossingA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCONFIRMZONECROSSINGA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.szUrlPrev = (ULONG_PTR)szUrlPrev;
    call.szUrlNew = (ULONG_PTR)szUrlNew;
    call.bPost = (ULONG_PTR)bPost;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetConfirmZoneCrossingA(struct qemu_syscall *call)
{
    struct qemu_InternetConfirmZoneCrossingA *c = (struct qemu_InternetConfirmZoneCrossingA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetConfirmZoneCrossingA(QEMU_G2H(c->hWnd), QEMU_G2H(c->szUrlPrev), QEMU_G2H(c->szUrlNew), c->bPost);
}

#endif

struct qemu_InternetConfirmZoneCrossingW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t szUrlPrev;
    uint64_t szUrlNew;
    uint64_t bPost;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetConfirmZoneCrossingW(HWND hWnd, LPWSTR szUrlPrev, LPWSTR szUrlNew, BOOL bPost)
{
    struct qemu_InternetConfirmZoneCrossingW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCONFIRMZONECROSSINGW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.szUrlPrev = (ULONG_PTR)szUrlPrev;
    call.szUrlNew = (ULONG_PTR)szUrlNew;
    call.bPost = (ULONG_PTR)bPost;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetConfirmZoneCrossingW(struct qemu_syscall *call)
{
    struct qemu_InternetConfirmZoneCrossingW *c = (struct qemu_InternetConfirmZoneCrossingW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetConfirmZoneCrossingW(QEMU_G2H(c->hWnd), QEMU_G2H(c->szUrlPrev), QEMU_G2H(c->szUrlNew), c->bPost);
}

#endif

struct qemu_PrivacySetZonePreferenceW
{
    struct qemu_syscall super;
    uint64_t zone;
    uint64_t type;
    uint64_t template;
    uint64_t preference;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI PrivacySetZonePreferenceW(DWORD zone, DWORD type, DWORD template, LPCWSTR preference)
{
    struct qemu_PrivacySetZonePreferenceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVACYSETZONEPREFERENCEW);
    call.zone = (ULONG_PTR)zone;
    call.type = (ULONG_PTR)type;
    call.template = (ULONG_PTR)template;
    call.preference = (ULONG_PTR)preference;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivacySetZonePreferenceW(struct qemu_syscall *call)
{
    struct qemu_PrivacySetZonePreferenceW *c = (struct qemu_PrivacySetZonePreferenceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivacySetZonePreferenceW(c->zone, c->type, c->template, QEMU_G2H(c->preference));
}

#endif

struct qemu_PrivacyGetZonePreferenceW
{
    struct qemu_syscall super;
    uint64_t zone;
    uint64_t type;
    uint64_t template;
    uint64_t preference;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI PrivacyGetZonePreferenceW(DWORD zone, DWORD type, LPDWORD template, LPWSTR preference, LPDWORD length)
{
    struct qemu_PrivacyGetZonePreferenceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVACYGETZONEPREFERENCEW);
    call.zone = (ULONG_PTR)zone;
    call.type = (ULONG_PTR)type;
    call.template = (ULONG_PTR)template;
    call.preference = (ULONG_PTR)preference;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivacyGetZonePreferenceW(struct qemu_syscall *call)
{
    struct qemu_PrivacyGetZonePreferenceW *c = (struct qemu_PrivacyGetZonePreferenceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivacyGetZonePreferenceW(c->zone, c->type, QEMU_G2H(c->template), QEMU_G2H(c->preference), QEMU_G2H(c->length));
}

#endif

struct qemu_InternetGetSecurityInfoByURLA
{
    struct qemu_syscall super;
    uint64_t lpszURL;
    uint64_t ppCertChain;
    uint64_t pdwSecureFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetSecurityInfoByURLA(LPSTR lpszURL, PCCERT_CHAIN_CONTEXT *ppCertChain, DWORD *pdwSecureFlags)
{
    struct qemu_InternetGetSecurityInfoByURLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETSECURITYINFOBYURLA);
    call.lpszURL = (ULONG_PTR)lpszURL;
    call.ppCertChain = (ULONG_PTR)ppCertChain;
    call.pdwSecureFlags = (ULONG_PTR)pdwSecureFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InternetGetSecurityInfoByURLA to Wine headers? */
extern BOOL WINAPI InternetGetSecurityInfoByURLA(LPSTR lpszURL, PCCERT_CHAIN_CONTEXT *ppCertChain, DWORD *pdwSecureFlags);
void qemu_InternetGetSecurityInfoByURLA(struct qemu_syscall *call)
{
    struct qemu_InternetGetSecurityInfoByURLA *c = (struct qemu_InternetGetSecurityInfoByURLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetSecurityInfoByURLA(QEMU_G2H(c->lpszURL), QEMU_G2H(c->ppCertChain), QEMU_G2H(c->pdwSecureFlags));
}

#endif

struct qemu_InternetGetSecurityInfoByURLW
{
    struct qemu_syscall super;
    uint64_t lpszURL;
    uint64_t ppCertChain;
    uint64_t pdwSecureFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetSecurityInfoByURLW(LPCWSTR lpszURL, PCCERT_CHAIN_CONTEXT *ppCertChain, DWORD *pdwSecureFlags)
{
    struct qemu_InternetGetSecurityInfoByURLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETSECURITYINFOBYURLW);
    call.lpszURL = (ULONG_PTR)lpszURL;
    call.ppCertChain = (ULONG_PTR)ppCertChain;
    call.pdwSecureFlags = (ULONG_PTR)pdwSecureFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InternetGetSecurityInfoByURLW to Wine headers? */
extern BOOL WINAPI InternetGetSecurityInfoByURLW(LPCWSTR lpszURL, PCCERT_CHAIN_CONTEXT *ppCertChain, DWORD *pdwSecureFlags);
void qemu_InternetGetSecurityInfoByURLW(struct qemu_syscall *call)
{
    struct qemu_InternetGetSecurityInfoByURLW *c = (struct qemu_InternetGetSecurityInfoByURLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetSecurityInfoByURLW(QEMU_G2H(c->lpszURL), QEMU_G2H(c->ppCertChain), QEMU_G2H(c->pdwSecureFlags));
}

#endif

struct qemu_InternetDialA
{
    struct qemu_syscall super;
    uint64_t hwndParent;
    uint64_t lpszConnectoid;
    uint64_t dwFlags;
    uint64_t lpdwConnection;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetDialA(HWND hwndParent, LPSTR lpszConnectoid, DWORD dwFlags, DWORD_PTR* lpdwConnection, DWORD dwReserved)
{
    struct qemu_InternetDialA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETDIALA);
    call.hwndParent = (ULONG_PTR)hwndParent;
    call.lpszConnectoid = (ULONG_PTR)lpszConnectoid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpdwConnection = (ULONG_PTR)lpdwConnection;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetDialA(struct qemu_syscall *call)
{
    struct qemu_InternetDialA *c = (struct qemu_InternetDialA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetDialA(QEMU_G2H(c->hwndParent), QEMU_G2H(c->lpszConnectoid), c->dwFlags, QEMU_G2H(c->lpdwConnection), c->dwReserved);
}

#endif

struct qemu_InternetDialW
{
    struct qemu_syscall super;
    uint64_t hwndParent;
    uint64_t lpszConnectoid;
    uint64_t dwFlags;
    uint64_t lpdwConnection;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetDialW(HWND hwndParent, LPWSTR lpszConnectoid, DWORD dwFlags, DWORD_PTR* lpdwConnection, DWORD dwReserved)
{
    struct qemu_InternetDialW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETDIALW);
    call.hwndParent = (ULONG_PTR)hwndParent;
    call.lpszConnectoid = (ULONG_PTR)lpszConnectoid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpdwConnection = (ULONG_PTR)lpdwConnection;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetDialW(struct qemu_syscall *call)
{
    struct qemu_InternetDialW *c = (struct qemu_InternetDialW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetDialW(QEMU_G2H(c->hwndParent), QEMU_G2H(c->lpszConnectoid), c->dwFlags, QEMU_G2H(c->lpdwConnection), c->dwReserved);
}

#endif

struct qemu_InternetGoOnlineA
{
    struct qemu_syscall super;
    uint64_t lpszURL;
    uint64_t hwndParent;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGoOnlineA(LPSTR lpszURL, HWND hwndParent, DWORD dwReserved)
{
    struct qemu_InternetGoOnlineA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGOONLINEA);
    call.lpszURL = (ULONG_PTR)lpszURL;
    call.hwndParent = (ULONG_PTR)hwndParent;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGoOnlineA(struct qemu_syscall *call)
{
    struct qemu_InternetGoOnlineA *c = (struct qemu_InternetGoOnlineA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGoOnlineA(QEMU_G2H(c->lpszURL), QEMU_G2H(c->hwndParent), c->dwReserved);
}

#endif

struct qemu_InternetGoOnlineW
{
    struct qemu_syscall super;
    uint64_t lpszURL;
    uint64_t hwndParent;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGoOnlineW(LPWSTR lpszURL, HWND hwndParent, DWORD dwReserved)
{
    struct qemu_InternetGoOnlineW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGOONLINEW);
    call.lpszURL = (ULONG_PTR)lpszURL;
    call.hwndParent = (ULONG_PTR)hwndParent;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGoOnlineW(struct qemu_syscall *call)
{
    struct qemu_InternetGoOnlineW *c = (struct qemu_InternetGoOnlineW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGoOnlineW(QEMU_G2H(c->lpszURL), QEMU_G2H(c->hwndParent), c->dwReserved);
}

#endif

struct qemu_InternetHangUp
{
    struct qemu_syscall super;
    uint64_t dwConnection;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetHangUp(DWORD_PTR dwConnection, DWORD dwReserved)
{
    struct qemu_InternetHangUp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETHANGUP);
    call.dwConnection = (ULONG_PTR)dwConnection;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetHangUp(struct qemu_syscall *call)
{
    struct qemu_InternetHangUp *c = (struct qemu_InternetHangUp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetHangUp(c->dwConnection, c->dwReserved);
}

#endif

struct qemu_CreateMD5SSOHash
{
    struct qemu_syscall super;
    uint64_t pszChallengeInfo;
    uint64_t pwszRealm;
    uint64_t pwszTarget;
    uint64_t pbHexHash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateMD5SSOHash(PWSTR pszChallengeInfo, PWSTR pwszRealm, PWSTR pwszTarget, PBYTE pbHexHash)
{
    struct qemu_CreateMD5SSOHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEMD5SSOHASH);
    call.pszChallengeInfo = (ULONG_PTR)pszChallengeInfo;
    call.pwszRealm = (ULONG_PTR)pwszRealm;
    call.pwszTarget = (ULONG_PTR)pwszTarget;
    call.pbHexHash = (ULONG_PTR)pbHexHash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateMD5SSOHash(struct qemu_syscall *call)
{
    struct qemu_CreateMD5SSOHash *c = (struct qemu_CreateMD5SSOHash *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateMD5SSOHash(QEMU_G2H(c->pszChallengeInfo), QEMU_G2H(c->pwszRealm), QEMU_G2H(c->pwszTarget), QEMU_G2H(c->pbHexHash));
}

#endif

struct qemu_ResumeSuspendedDownload
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t dwError;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ResumeSuspendedDownload(HINTERNET hInternet, DWORD dwError)
{
    struct qemu_ResumeSuspendedDownload call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESUMESUSPENDEDDOWNLOAD);
    call.hInternet = (ULONG_PTR)hInternet;
    call.dwError = (ULONG_PTR)dwError;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResumeSuspendedDownload(struct qemu_syscall *call)
{
    struct qemu_ResumeSuspendedDownload *c = (struct qemu_ResumeSuspendedDownload *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ResumeSuspendedDownload(QEMU_G2H(c->hInternet), c->dwError);
}

#endif

struct qemu_InternetQueryFortezzaStatus
{
    struct qemu_syscall super;
    uint64_t a;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetQueryFortezzaStatus(DWORD *a, DWORD_PTR b)
{
    struct qemu_InternetQueryFortezzaStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETQUERYFORTEZZASTATUS);
    call.a = (ULONG_PTR)a;
    call.b = (ULONG_PTR)b;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InternetQueryFortezzaStatus to Wine headers? */
extern BOOL WINAPI InternetQueryFortezzaStatus(DWORD *a, DWORD_PTR b);
void qemu_InternetQueryFortezzaStatus(struct qemu_syscall *call)
{
    struct qemu_InternetQueryFortezzaStatus *c = (struct qemu_InternetQueryFortezzaStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetQueryFortezzaStatus(QEMU_G2H(c->a), c->b);
}

#endif

struct qemu_ShowClientAuthCerts
{
    struct qemu_syscall super;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ShowClientAuthCerts(HWND parent)
{
    struct qemu_ShowClientAuthCerts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWCLIENTAUTHCERTS);
    call.parent = (ULONG_PTR)parent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ShowClientAuthCerts to Wine headers? */
extern DWORD WINAPI ShowClientAuthCerts(HWND parent);
void qemu_ShowClientAuthCerts(struct qemu_syscall *call)
{
    struct qemu_ShowClientAuthCerts *c = (struct qemu_ShowClientAuthCerts *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ShowClientAuthCerts(QEMU_G2H(c->parent));
}

#endif

