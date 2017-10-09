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
#include <winineti.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wininet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wininet);
#endif


struct qemu_GetUrlCacheEntryInfoExA
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufSize;
    uint64_t lpszReserved;
    uint64_t lpdwReserved;
    uint64_t lpReserved;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheEntryInfoExA(LPCSTR lpszUrl, LPINTERNET_CACHE_ENTRY_INFOA lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufSize, LPSTR lpszReserved, LPDWORD lpdwReserved, LPVOID lpReserved, DWORD dwFlags)
{
    struct qemu_GetUrlCacheEntryInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHEENTRYINFOEXA);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufSize = (ULONG_PTR)lpdwCacheEntryInfoBufSize;
    call.lpszReserved = (ULONG_PTR)lpszReserved;
    call.lpdwReserved = (ULONG_PTR)lpdwReserved;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUrlCacheEntryInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheEntryInfoExA *c = (struct qemu_GetUrlCacheEntryInfoExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheEntryInfoExA(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufSize), QEMU_G2H(c->lpszReserved), QEMU_G2H(c->lpdwReserved), QEMU_G2H(c->lpReserved), c->dwFlags);
}

#endif

struct qemu_GetUrlCacheEntryInfoA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheEntryInfoA(LPCSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFOA lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize)
{
    struct qemu_GetUrlCacheEntryInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHEENTRYINFOA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufferSize = (ULONG_PTR)lpdwCacheEntryInfoBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUrlCacheEntryInfoA(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheEntryInfoA *c = (struct qemu_GetUrlCacheEntryInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheEntryInfoA(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufferSize));
}

#endif

struct qemu_GetUrlCacheEntryInfoExW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufSize;
    uint64_t lpszReserved;
    uint64_t lpdwReserved;
    uint64_t lpReserved;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheEntryInfoExW(LPCWSTR lpszUrl, LPINTERNET_CACHE_ENTRY_INFOW lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufSize, LPWSTR lpszReserved, LPDWORD lpdwReserved, LPVOID lpReserved, DWORD dwFlags)
{
    struct qemu_GetUrlCacheEntryInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHEENTRYINFOEXW);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufSize = (ULONG_PTR)lpdwCacheEntryInfoBufSize;
    call.lpszReserved = (ULONG_PTR)lpszReserved;
    call.lpdwReserved = (ULONG_PTR)lpdwReserved;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUrlCacheEntryInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheEntryInfoExW *c = (struct qemu_GetUrlCacheEntryInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheEntryInfoExW(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufSize), QEMU_G2H(c->lpszReserved), QEMU_G2H(c->lpdwReserved), QEMU_G2H(c->lpReserved), c->dwFlags);
}

#endif

struct qemu_GetUrlCacheEntryInfoW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheEntryInfoW(LPCWSTR lpszUrl, LPINTERNET_CACHE_ENTRY_INFOW lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize)
{
    struct qemu_GetUrlCacheEntryInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHEENTRYINFOW);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufferSize = (ULONG_PTR)lpdwCacheEntryInfoBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUrlCacheEntryInfoW(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheEntryInfoW *c = (struct qemu_GetUrlCacheEntryInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheEntryInfoW(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufferSize));
}

#endif

struct qemu_SetUrlCacheEntryInfoA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpCacheEntryInfo;
    uint64_t dwFieldControl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheEntryInfoA(LPCSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFOA lpCacheEntryInfo, DWORD dwFieldControl)
{
    struct qemu_SetUrlCacheEntryInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHEENTRYINFOA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.dwFieldControl = (ULONG_PTR)dwFieldControl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUrlCacheEntryInfoA(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheEntryInfoA *c = (struct qemu_SetUrlCacheEntryInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheEntryInfoA(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpCacheEntryInfo), c->dwFieldControl);
}

#endif

struct qemu_SetUrlCacheEntryInfoW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpCacheEntryInfo;
    uint64_t dwFieldControl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheEntryInfoW(LPCWSTR lpszUrl, LPINTERNET_CACHE_ENTRY_INFOW lpCacheEntryInfo, DWORD dwFieldControl)
{
    struct qemu_SetUrlCacheEntryInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHEENTRYINFOW);
    call.lpszUrl = (ULONG_PTR)lpszUrl;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.dwFieldControl = (ULONG_PTR)dwFieldControl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUrlCacheEntryInfoW(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheEntryInfoW *c = (struct qemu_SetUrlCacheEntryInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheEntryInfoW(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpCacheEntryInfo), c->dwFieldControl);
}

#endif

struct qemu_RetrieveUrlCacheEntryFileA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufferSize;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RetrieveUrlCacheEntryFileA(LPCSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFOA lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, DWORD dwReserved)
{
    struct qemu_RetrieveUrlCacheEntryFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RETRIEVEURLCACHEENTRYFILEA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufferSize = (ULONG_PTR)lpdwCacheEntryInfoBufferSize;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RetrieveUrlCacheEntryFileA(struct qemu_syscall *call)
{
    struct qemu_RetrieveUrlCacheEntryFileA *c = (struct qemu_RetrieveUrlCacheEntryFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RetrieveUrlCacheEntryFileA(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufferSize), c->dwReserved);
}

#endif

struct qemu_RetrieveUrlCacheEntryFileW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufferSize;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RetrieveUrlCacheEntryFileW(LPCWSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFOW lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, DWORD dwReserved)
{
    struct qemu_RetrieveUrlCacheEntryFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RETRIEVEURLCACHEENTRYFILEW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufferSize = (ULONG_PTR)lpdwCacheEntryInfoBufferSize;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RetrieveUrlCacheEntryFileW(struct qemu_syscall *call)
{
    struct qemu_RetrieveUrlCacheEntryFileW *c = (struct qemu_RetrieveUrlCacheEntryFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RetrieveUrlCacheEntryFileW(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufferSize), c->dwReserved);
}

#endif

struct qemu_FreeUrlCacheSpaceW
{
    struct qemu_syscall super;
    uint64_t cache_path;
    uint64_t size;
    uint64_t filter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeUrlCacheSpaceW(LPCWSTR cache_path, DWORD size, DWORD filter)
{
    struct qemu_FreeUrlCacheSpaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEURLCACHESPACEW);
    call.cache_path = (ULONG_PTR)cache_path;
    call.size = (ULONG_PTR)size;
    call.filter = (ULONG_PTR)filter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeUrlCacheSpaceW(struct qemu_syscall *call)
{
    struct qemu_FreeUrlCacheSpaceW *c = (struct qemu_FreeUrlCacheSpaceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeUrlCacheSpaceW(QEMU_G2H(c->cache_path), c->size, c->filter);
}

#endif

struct qemu_FreeUrlCacheSpaceA
{
    struct qemu_syscall super;
    uint64_t lpszCachePath;
    uint64_t dwSize;
    uint64_t dwFilter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeUrlCacheSpaceA(LPCSTR lpszCachePath, DWORD dwSize, DWORD dwFilter)
{
    struct qemu_FreeUrlCacheSpaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEURLCACHESPACEA);
    call.lpszCachePath = (ULONG_PTR)lpszCachePath;
    call.dwSize = (ULONG_PTR)dwSize;
    call.dwFilter = (ULONG_PTR)dwFilter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeUrlCacheSpaceA(struct qemu_syscall *call)
{
    struct qemu_FreeUrlCacheSpaceA *c = (struct qemu_FreeUrlCacheSpaceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeUrlCacheSpaceA(QEMU_G2H(c->lpszCachePath), c->dwSize, c->dwFilter);
}

#endif

struct qemu_UnlockUrlCacheEntryFileA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnlockUrlCacheEntryFileA(LPCSTR lpszUrlName, DWORD dwReserved)
{
    struct qemu_UnlockUrlCacheEntryFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOCKURLCACHEENTRYFILEA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnlockUrlCacheEntryFileA(struct qemu_syscall *call)
{
    struct qemu_UnlockUrlCacheEntryFileA *c = (struct qemu_UnlockUrlCacheEntryFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnlockUrlCacheEntryFileA(QEMU_G2H(c->lpszUrlName), c->dwReserved);
}

#endif

struct qemu_UnlockUrlCacheEntryFileW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnlockUrlCacheEntryFileW(LPCWSTR lpszUrlName, DWORD dwReserved)
{
    struct qemu_UnlockUrlCacheEntryFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOCKURLCACHEENTRYFILEW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnlockUrlCacheEntryFileW(struct qemu_syscall *call)
{
    struct qemu_UnlockUrlCacheEntryFileW *c = (struct qemu_UnlockUrlCacheEntryFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnlockUrlCacheEntryFileW(QEMU_G2H(c->lpszUrlName), c->dwReserved);
}

#endif

struct qemu_CreateUrlCacheEntryA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t dwExpectedFileSize;
    uint64_t lpszFileExtension;
    uint64_t lpszFileName;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateUrlCacheEntryA(LPCSTR lpszUrlName, DWORD dwExpectedFileSize, LPCSTR lpszFileExtension, LPSTR lpszFileName, DWORD dwReserved)
{
    struct qemu_CreateUrlCacheEntryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEURLCACHEENTRYA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.dwExpectedFileSize = (ULONG_PTR)dwExpectedFileSize;
    call.lpszFileExtension = (ULONG_PTR)lpszFileExtension;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateUrlCacheEntryA(struct qemu_syscall *call)
{
    struct qemu_CreateUrlCacheEntryA *c = (struct qemu_CreateUrlCacheEntryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateUrlCacheEntryA(QEMU_G2H(c->lpszUrlName), c->dwExpectedFileSize, QEMU_G2H(c->lpszFileExtension), QEMU_G2H(c->lpszFileName), c->dwReserved);
}

#endif

struct qemu_CreateUrlCacheEntryW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t dwExpectedFileSize;
    uint64_t lpszFileExtension;
    uint64_t lpszFileName;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateUrlCacheEntryW(LPCWSTR lpszUrlName, DWORD dwExpectedFileSize, LPCWSTR lpszFileExtension, LPWSTR lpszFileName, DWORD dwReserved)
{
    struct qemu_CreateUrlCacheEntryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEURLCACHEENTRYW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.dwExpectedFileSize = (ULONG_PTR)dwExpectedFileSize;
    call.lpszFileExtension = (ULONG_PTR)lpszFileExtension;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateUrlCacheEntryW(struct qemu_syscall *call)
{
    struct qemu_CreateUrlCacheEntryW *c = (struct qemu_CreateUrlCacheEntryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateUrlCacheEntryW(QEMU_G2H(c->lpszUrlName), c->dwExpectedFileSize, QEMU_G2H(c->lpszFileExtension), QEMU_G2H(c->lpszFileName), c->dwReserved);
}

#endif

struct qemu_CommitUrlCacheEntryA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpszLocalFileName;
    uint64_t ExpireTimeHigh;
    uint64_t ExpireTimeLow;
    uint64_t LastModifiedTimeHigh;
    uint64_t LastModifiedTimeLow;
    uint64_t CacheEntryType;
    uint64_t lpHeaderInfo;
    uint64_t dwHeaderSize;
    uint64_t lpszFileExtension;
    uint64_t lpszOriginalUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CommitUrlCacheEntryA(LPCSTR lpszUrlName, LPCSTR lpszLocalFileName, FILETIME ExpireTime, FILETIME LastModifiedTime, DWORD CacheEntryType, LPBYTE lpHeaderInfo, DWORD dwHeaderSize, LPCSTR lpszFileExtension, LPCSTR lpszOriginalUrl)
{
    struct qemu_CommitUrlCacheEntryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMITURLCACHEENTRYA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpszLocalFileName = (ULONG_PTR)lpszLocalFileName;
    call.LastModifiedTimeHigh = ExpireTime.dwHighDateTime;
    call.LastModifiedTimeLow = ExpireTime.dwLowDateTime;
    call.LastModifiedTimeHigh = LastModifiedTime.dwHighDateTime;
    call.LastModifiedTimeLow = LastModifiedTime.dwLowDateTime;
    call.CacheEntryType = (ULONG_PTR)CacheEntryType;
    call.lpHeaderInfo = (ULONG_PTR)lpHeaderInfo;
    call.dwHeaderSize = (ULONG_PTR)dwHeaderSize;
    call.lpszFileExtension = (ULONG_PTR)lpszFileExtension;
    call.lpszOriginalUrl = (ULONG_PTR)lpszOriginalUrl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CommitUrlCacheEntryA(struct qemu_syscall *call)
{
    struct qemu_CommitUrlCacheEntryA *c = (struct qemu_CommitUrlCacheEntryA *)call;
    FILETIME expire, modify;

    WINE_FIXME("Unverified!\n");
    expire.dwHighDateTime = c->ExpireTimeHigh;
    expire.dwLowDateTime = c->ExpireTimeLow;
    modify.dwHighDateTime = c->LastModifiedTimeHigh;
    modify.dwLowDateTime = c->LastModifiedTimeLow;

    c->super.iret = CommitUrlCacheEntryA(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpszLocalFileName), expire, modify, c->CacheEntryType, QEMU_G2H(c->lpHeaderInfo), c->dwHeaderSize, QEMU_G2H(c->lpszFileExtension), QEMU_G2H(c->lpszOriginalUrl));
}

#endif

struct qemu_CommitUrlCacheEntryW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpszLocalFileName;
    uint64_t ExpireTimeHigh;
    uint64_t ExpireTimeLow;
    uint64_t LastModifiedTimeHigh;
    uint64_t LastModifiedTimeLow;
    uint64_t CacheEntryType;
    uint64_t lpHeaderInfo;
    uint64_t dwHeaderSize;
    uint64_t lpszFileExtension;
    uint64_t lpszOriginalUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CommitUrlCacheEntryW(LPCWSTR lpszUrlName, LPCWSTR lpszLocalFileName, FILETIME ExpireTime, FILETIME LastModifiedTime, DWORD CacheEntryType, LPWSTR lpHeaderInfo, DWORD dwHeaderSize, LPCWSTR lpszFileExtension, LPCWSTR lpszOriginalUrl)
{
    struct qemu_CommitUrlCacheEntryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMITURLCACHEENTRYW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpszLocalFileName = (ULONG_PTR)lpszLocalFileName;
    call.LastModifiedTimeHigh = ExpireTime.dwHighDateTime;
    call.LastModifiedTimeLow = ExpireTime.dwLowDateTime;
    call.LastModifiedTimeHigh = LastModifiedTime.dwHighDateTime;
    call.LastModifiedTimeLow = LastModifiedTime.dwLowDateTime;
    call.CacheEntryType = (ULONG_PTR)CacheEntryType;
    call.lpHeaderInfo = (ULONG_PTR)lpHeaderInfo;
    call.dwHeaderSize = (ULONG_PTR)dwHeaderSize;
    call.lpszFileExtension = (ULONG_PTR)lpszFileExtension;
    call.lpszOriginalUrl = (ULONG_PTR)lpszOriginalUrl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CommitUrlCacheEntryW(struct qemu_syscall *call)
{
    struct qemu_CommitUrlCacheEntryW *c = (struct qemu_CommitUrlCacheEntryW *)call;
    FILETIME expire, modify;

    WINE_FIXME("Unverified!\n");
    expire.dwHighDateTime = c->ExpireTimeHigh;
    expire.dwLowDateTime = c->ExpireTimeLow;
    modify.dwHighDateTime = c->LastModifiedTimeHigh;
    modify.dwLowDateTime = c->LastModifiedTimeLow;


    c->super.iret = CommitUrlCacheEntryW(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpszLocalFileName), expire, modify, c->CacheEntryType, QEMU_G2H(c->lpHeaderInfo), c->dwHeaderSize, QEMU_G2H(c->lpszFileExtension), QEMU_G2H(c->lpszOriginalUrl));
}

#endif

struct qemu_ReadUrlCacheEntryStream
{
    struct qemu_syscall super;
    uint64_t hUrlCacheStream;
    uint64_t dwLocation;
    uint64_t lpBuffer;
    uint64_t lpdwLen;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadUrlCacheEntryStream(IN HANDLE hUrlCacheStream, IN DWORD dwLocation, IN OUT LPVOID lpBuffer, IN OUT LPDWORD lpdwLen, IN DWORD dwReserved)
{
    struct qemu_ReadUrlCacheEntryStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READURLCACHEENTRYSTREAM);
    call.hUrlCacheStream = (ULONG_PTR)hUrlCacheStream;
    call.dwLocation = (ULONG_PTR)dwLocation;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.lpdwLen = (ULONG_PTR)lpdwLen;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadUrlCacheEntryStream(struct qemu_syscall *call)
{
    struct qemu_ReadUrlCacheEntryStream *c = (struct qemu_ReadUrlCacheEntryStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadUrlCacheEntryStream((HANDLE)c->hUrlCacheStream, c->dwLocation, QEMU_G2H(c->lpBuffer), QEMU_G2H(c->lpdwLen), c->dwReserved);
}

#endif

struct qemu_RetrieveUrlCacheEntryStreamA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufferSize;
    uint64_t fRandomRead;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RetrieveUrlCacheEntryStreamA(LPCSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFOA lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, BOOL fRandomRead, DWORD dwReserved)
{
    struct qemu_RetrieveUrlCacheEntryStreamA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RETRIEVEURLCACHEENTRYSTREAMA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufferSize = (ULONG_PTR)lpdwCacheEntryInfoBufferSize;
    call.fRandomRead = (ULONG_PTR)fRandomRead;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RetrieveUrlCacheEntryStreamA(struct qemu_syscall *call)
{
    struct qemu_RetrieveUrlCacheEntryStreamA *c = (struct qemu_RetrieveUrlCacheEntryStreamA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RetrieveUrlCacheEntryStreamA(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufferSize), c->fRandomRead, c->dwReserved);
}

#endif

struct qemu_RetrieveUrlCacheEntryStreamW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t lpCacheEntryInfo;
    uint64_t lpdwCacheEntryInfoBufferSize;
    uint64_t fRandomRead;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RetrieveUrlCacheEntryStreamW(LPCWSTR lpszUrlName, LPINTERNET_CACHE_ENTRY_INFOW lpCacheEntryInfo, LPDWORD lpdwCacheEntryInfoBufferSize, BOOL fRandomRead, DWORD dwReserved)
{
    struct qemu_RetrieveUrlCacheEntryStreamW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RETRIEVEURLCACHEENTRYSTREAMW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.lpCacheEntryInfo = (ULONG_PTR)lpCacheEntryInfo;
    call.lpdwCacheEntryInfoBufferSize = (ULONG_PTR)lpdwCacheEntryInfoBufferSize;
    call.fRandomRead = (ULONG_PTR)fRandomRead;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RetrieveUrlCacheEntryStreamW(struct qemu_syscall *call)
{
    struct qemu_RetrieveUrlCacheEntryStreamW *c = (struct qemu_RetrieveUrlCacheEntryStreamW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RetrieveUrlCacheEntryStreamW(QEMU_G2H(c->lpszUrlName), QEMU_G2H(c->lpCacheEntryInfo), QEMU_G2H(c->lpdwCacheEntryInfoBufferSize), c->fRandomRead, c->dwReserved);
}

#endif

struct qemu_UnlockUrlCacheEntryStream
{
    struct qemu_syscall super;
    uint64_t hUrlCacheStream;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnlockUrlCacheEntryStream(IN HANDLE hUrlCacheStream, IN DWORD dwReserved)
{
    struct qemu_UnlockUrlCacheEntryStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOCKURLCACHEENTRYSTREAM);
    call.hUrlCacheStream = (ULONG_PTR)hUrlCacheStream;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnlockUrlCacheEntryStream(struct qemu_syscall *call)
{
    struct qemu_UnlockUrlCacheEntryStream *c = (struct qemu_UnlockUrlCacheEntryStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnlockUrlCacheEntryStream((HANDLE)c->hUrlCacheStream, c->dwReserved);
}

#endif

struct qemu_DeleteUrlCacheEntryA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteUrlCacheEntryA(LPCSTR lpszUrlName)
{
    struct qemu_DeleteUrlCacheEntryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEURLCACHEENTRYA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteUrlCacheEntryA(struct qemu_syscall *call)
{
    struct qemu_DeleteUrlCacheEntryA *c = (struct qemu_DeleteUrlCacheEntryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteUrlCacheEntryA(QEMU_G2H(c->lpszUrlName));
}

#endif

struct qemu_DeleteUrlCacheEntryW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteUrlCacheEntryW(LPCWSTR lpszUrlName)
{
    struct qemu_DeleteUrlCacheEntryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEURLCACHEENTRYW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteUrlCacheEntryW(struct qemu_syscall *call)
{
    struct qemu_DeleteUrlCacheEntryW *c = (struct qemu_DeleteUrlCacheEntryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteUrlCacheEntryW(QEMU_G2H(c->lpszUrlName));
}

#endif

struct qemu_DeleteUrlCacheContainerA
{
    struct qemu_syscall super;
    uint64_t d1;
    uint64_t d2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteUrlCacheContainerA(DWORD d1, DWORD d2)
{
    struct qemu_DeleteUrlCacheContainerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEURLCACHECONTAINERA);
    call.d1 = (ULONG_PTR)d1;
    call.d2 = (ULONG_PTR)d2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DeleteUrlCacheContainerA to Wine headers? */
extern BOOL WINAPI DeleteUrlCacheContainerA(DWORD d1, DWORD d2);
void qemu_DeleteUrlCacheContainerA(struct qemu_syscall *call)
{
    struct qemu_DeleteUrlCacheContainerA *c = (struct qemu_DeleteUrlCacheContainerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteUrlCacheContainerA(c->d1, c->d2);
}

#endif

struct qemu_DeleteUrlCacheContainerW
{
    struct qemu_syscall super;
    uint64_t d1;
    uint64_t d2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteUrlCacheContainerW(DWORD d1, DWORD d2)
{
    struct qemu_DeleteUrlCacheContainerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEURLCACHECONTAINERW);
    call.d1 = (ULONG_PTR)d1;
    call.d2 = (ULONG_PTR)d2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DeleteUrlCacheContainerW to Wine headers? */
extern BOOL WINAPI DeleteUrlCacheContainerW(DWORD d1, DWORD d2);
void qemu_DeleteUrlCacheContainerW(struct qemu_syscall *call)
{
    struct qemu_DeleteUrlCacheContainerW *c = (struct qemu_DeleteUrlCacheContainerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteUrlCacheContainerW(c->d1, c->d2);
}

#endif

struct qemu_CreateUrlCacheContainerA
{
    struct qemu_syscall super;
    uint64_t d1;
    uint64_t d2;
    uint64_t d3;
    uint64_t d4;
    uint64_t d5;
    uint64_t d6;
    uint64_t d7;
    uint64_t d8;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateUrlCacheContainerA(DWORD d1, DWORD d2, DWORD d3, DWORD d4, DWORD d5, DWORD d6, DWORD d7, DWORD d8)
{
    struct qemu_CreateUrlCacheContainerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEURLCACHECONTAINERA);
    call.d1 = (ULONG_PTR)d1;
    call.d2 = (ULONG_PTR)d2;
    call.d3 = (ULONG_PTR)d3;
    call.d4 = (ULONG_PTR)d4;
    call.d5 = (ULONG_PTR)d5;
    call.d6 = (ULONG_PTR)d6;
    call.d7 = (ULONG_PTR)d7;
    call.d8 = (ULONG_PTR)d8;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CreateUrlCacheContainerA to Wine headers? */
extern BOOL WINAPI CreateUrlCacheContainerA(DWORD d1, DWORD d2, DWORD d3, DWORD d4, DWORD d5, DWORD d6, DWORD d7, DWORD d8);
void qemu_CreateUrlCacheContainerA(struct qemu_syscall *call)
{
    struct qemu_CreateUrlCacheContainerA *c = (struct qemu_CreateUrlCacheContainerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateUrlCacheContainerA(c->d1, c->d2, c->d3, c->d4, c->d5, c->d6, c->d7, c->d8);
}

#endif

struct qemu_CreateUrlCacheContainerW
{
    struct qemu_syscall super;
    uint64_t d1;
    uint64_t d2;
    uint64_t d3;
    uint64_t d4;
    uint64_t d5;
    uint64_t d6;
    uint64_t d7;
    uint64_t d8;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateUrlCacheContainerW(DWORD d1, DWORD d2, DWORD d3, DWORD d4, DWORD d5, DWORD d6, DWORD d7, DWORD d8)
{
    struct qemu_CreateUrlCacheContainerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEURLCACHECONTAINERW);
    call.d1 = (ULONG_PTR)d1;
    call.d2 = (ULONG_PTR)d2;
    call.d3 = (ULONG_PTR)d3;
    call.d4 = (ULONG_PTR)d4;
    call.d5 = (ULONG_PTR)d5;
    call.d6 = (ULONG_PTR)d6;
    call.d7 = (ULONG_PTR)d7;
    call.d8 = (ULONG_PTR)d8;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CreateUrlCacheContainerW to Wine headers? */
extern BOOL WINAPI CreateUrlCacheContainerW(DWORD d1, DWORD d2, DWORD d3, DWORD d4, DWORD d5, DWORD d6, DWORD d7, DWORD d8);
void qemu_CreateUrlCacheContainerW(struct qemu_syscall *call)
{
    struct qemu_CreateUrlCacheContainerW *c = (struct qemu_CreateUrlCacheContainerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateUrlCacheContainerW(c->d1, c->d2, c->d3, c->d4, c->d5, c->d6, c->d7, c->d8);
}

#endif

struct qemu_FindFirstUrlCacheContainerA
{
    struct qemu_syscall super;
    uint64_t p1;
    uint64_t p2;
    uint64_t p3;
    uint64_t d1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheContainerA(LPVOID p1, LPVOID p2, LPVOID p3, DWORD d1)
{
    struct qemu_FindFirstUrlCacheContainerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHECONTAINERA);
    call.p1 = (ULONG_PTR)p1;
    call.p2 = (ULONG_PTR)p2;
    call.p3 = (ULONG_PTR)p3;
    call.d1 = (ULONG_PTR)d1;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add FindFirstUrlCacheContainerA to Wine headers? */
extern HANDLE WINAPI FindFirstUrlCacheContainerA(LPVOID p1, LPVOID p2, LPVOID p3, DWORD d1);
void qemu_FindFirstUrlCacheContainerA(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheContainerA *c = (struct qemu_FindFirstUrlCacheContainerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheContainerA(QEMU_G2H(c->p1), QEMU_G2H(c->p2), QEMU_G2H(c->p3), c->d1);
}

#endif

struct qemu_FindFirstUrlCacheContainerW
{
    struct qemu_syscall super;
    uint64_t p1;
    uint64_t p2;
    uint64_t p3;
    uint64_t d1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheContainerW(LPVOID p1, LPVOID p2, LPVOID p3, DWORD d1)
{
    struct qemu_FindFirstUrlCacheContainerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHECONTAINERW);
    call.p1 = (ULONG_PTR)p1;
    call.p2 = (ULONG_PTR)p2;
    call.p3 = (ULONG_PTR)p3;
    call.d1 = (ULONG_PTR)d1;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add FindFirstUrlCacheContainerW to Wine headers? */
extern HANDLE WINAPI FindFirstUrlCacheContainerW(LPVOID p1, LPVOID p2, LPVOID p3, DWORD d1);
void qemu_FindFirstUrlCacheContainerW(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheContainerW *c = (struct qemu_FindFirstUrlCacheContainerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheContainerW(QEMU_G2H(c->p1), QEMU_G2H(c->p2), QEMU_G2H(c->p3), c->d1);
}

#endif

struct qemu_FindNextUrlCacheContainerA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t p1;
    uint64_t p2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheContainerA(HANDLE handle, LPVOID p1, LPVOID p2)
{
    struct qemu_FindNextUrlCacheContainerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHECONTAINERA);
    call.handle = (ULONG_PTR)handle;
    call.p1 = (ULONG_PTR)p1;
    call.p2 = (ULONG_PTR)p2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FindNextUrlCacheContainerA to Wine headers? */
extern BOOL WINAPI FindNextUrlCacheContainerA(HANDLE handle, LPVOID p1, LPVOID p2);
void qemu_FindNextUrlCacheContainerA(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheContainerA *c = (struct qemu_FindNextUrlCacheContainerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheContainerA(QEMU_G2H(c->handle), QEMU_G2H(c->p1), QEMU_G2H(c->p2));
}

#endif

struct qemu_FindNextUrlCacheContainerW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t p1;
    uint64_t p2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheContainerW(HANDLE handle, LPVOID p1, LPVOID p2)
{
    struct qemu_FindNextUrlCacheContainerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHECONTAINERW);
    call.handle = (ULONG_PTR)handle;
    call.p1 = (ULONG_PTR)p1;
    call.p2 = (ULONG_PTR)p2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FindNextUrlCacheContainerW to Wine headers? */
extern BOOL WINAPI FindNextUrlCacheContainerW(HANDLE handle, LPVOID p1, LPVOID p2);
void qemu_FindNextUrlCacheContainerW(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheContainerW *c = (struct qemu_FindNextUrlCacheContainerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheContainerW(QEMU_G2H(c->handle), QEMU_G2H(c->p1), QEMU_G2H(c->p2));
}

#endif

struct qemu_FindFirstUrlCacheEntryExA
{
    struct qemu_syscall super;
    uint64_t lpszUrlSearchPattern;
    uint64_t dwFlags;
    uint64_t dwFilter;
    uint64_t GroupId;
    uint64_t lpFirstCacheEntryInfo;
    uint64_t lpdwFirstCacheEntryInfoBufferSize;
    uint64_t lpReserved;
    uint64_t pcbReserved2;
    uint64_t lpReserved3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheEntryExA(LPCSTR lpszUrlSearchPattern, DWORD dwFlags, DWORD dwFilter, GROUPID GroupId, LPINTERNET_CACHE_ENTRY_INFOA lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize, LPVOID lpReserved, LPDWORD pcbReserved2, LPVOID lpReserved3)
{
    struct qemu_FindFirstUrlCacheEntryExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHEENTRYEXA);
    call.lpszUrlSearchPattern = (ULONG_PTR)lpszUrlSearchPattern;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwFilter = (ULONG_PTR)dwFilter;
    call.GroupId = (ULONG_PTR)GroupId;
    call.lpFirstCacheEntryInfo = (ULONG_PTR)lpFirstCacheEntryInfo;
    call.lpdwFirstCacheEntryInfoBufferSize = (ULONG_PTR)lpdwFirstCacheEntryInfoBufferSize;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.pcbReserved2 = (ULONG_PTR)pcbReserved2;
    call.lpReserved3 = (ULONG_PTR)lpReserved3;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstUrlCacheEntryExA(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheEntryExA *c = (struct qemu_FindFirstUrlCacheEntryExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheEntryExA(QEMU_G2H(c->lpszUrlSearchPattern), c->dwFlags, c->dwFilter, c->GroupId, QEMU_G2H(c->lpFirstCacheEntryInfo), QEMU_G2H(c->lpdwFirstCacheEntryInfoBufferSize), QEMU_G2H(c->lpReserved), QEMU_G2H(c->pcbReserved2), QEMU_G2H(c->lpReserved3));
}

#endif

struct qemu_FindFirstUrlCacheEntryExW
{
    struct qemu_syscall super;
    uint64_t lpszUrlSearchPattern;
    uint64_t dwFlags;
    uint64_t dwFilter;
    uint64_t GroupId;
    uint64_t lpFirstCacheEntryInfo;
    uint64_t lpdwFirstCacheEntryInfoBufferSize;
    uint64_t lpReserved;
    uint64_t pcbReserved2;
    uint64_t lpReserved3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheEntryExW(LPCWSTR lpszUrlSearchPattern, DWORD dwFlags, DWORD dwFilter, GROUPID GroupId, LPINTERNET_CACHE_ENTRY_INFOW lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize, LPVOID lpReserved, LPDWORD pcbReserved2, LPVOID lpReserved3)
{
    struct qemu_FindFirstUrlCacheEntryExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHEENTRYEXW);
    call.lpszUrlSearchPattern = (ULONG_PTR)lpszUrlSearchPattern;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwFilter = (ULONG_PTR)dwFilter;
    call.GroupId = (ULONG_PTR)GroupId;
    call.lpFirstCacheEntryInfo = (ULONG_PTR)lpFirstCacheEntryInfo;
    call.lpdwFirstCacheEntryInfoBufferSize = (ULONG_PTR)lpdwFirstCacheEntryInfoBufferSize;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.pcbReserved2 = (ULONG_PTR)pcbReserved2;
    call.lpReserved3 = (ULONG_PTR)lpReserved3;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstUrlCacheEntryExW(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheEntryExW *c = (struct qemu_FindFirstUrlCacheEntryExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheEntryExW(QEMU_G2H(c->lpszUrlSearchPattern), c->dwFlags, c->dwFilter, c->GroupId, QEMU_G2H(c->lpFirstCacheEntryInfo), QEMU_G2H(c->lpdwFirstCacheEntryInfoBufferSize), QEMU_G2H(c->lpReserved), QEMU_G2H(c->pcbReserved2), QEMU_G2H(c->lpReserved3));
}

#endif

struct qemu_FindFirstUrlCacheEntryA
{
    struct qemu_syscall super;
    uint64_t lpszUrlSearchPattern;
    uint64_t lpFirstCacheEntryInfo;
    uint64_t lpdwFirstCacheEntryInfoBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheEntryA(LPCSTR lpszUrlSearchPattern, LPINTERNET_CACHE_ENTRY_INFOA lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize)
{
    struct qemu_FindFirstUrlCacheEntryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHEENTRYA);
    call.lpszUrlSearchPattern = (ULONG_PTR)lpszUrlSearchPattern;
    call.lpFirstCacheEntryInfo = (ULONG_PTR)lpFirstCacheEntryInfo;
    call.lpdwFirstCacheEntryInfoBufferSize = (ULONG_PTR)lpdwFirstCacheEntryInfoBufferSize;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstUrlCacheEntryA(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheEntryA *c = (struct qemu_FindFirstUrlCacheEntryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheEntryA(QEMU_G2H(c->lpszUrlSearchPattern), QEMU_G2H(c->lpFirstCacheEntryInfo), QEMU_G2H(c->lpdwFirstCacheEntryInfoBufferSize));
}

#endif

struct qemu_FindFirstUrlCacheEntryW
{
    struct qemu_syscall super;
    uint64_t lpszUrlSearchPattern;
    uint64_t lpFirstCacheEntryInfo;
    uint64_t lpdwFirstCacheEntryInfoBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheEntryW(LPCWSTR lpszUrlSearchPattern, LPINTERNET_CACHE_ENTRY_INFOW lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize)
{
    struct qemu_FindFirstUrlCacheEntryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHEENTRYW);
    call.lpszUrlSearchPattern = (ULONG_PTR)lpszUrlSearchPattern;
    call.lpFirstCacheEntryInfo = (ULONG_PTR)lpFirstCacheEntryInfo;
    call.lpdwFirstCacheEntryInfoBufferSize = (ULONG_PTR)lpdwFirstCacheEntryInfoBufferSize;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstUrlCacheEntryW(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheEntryW *c = (struct qemu_FindFirstUrlCacheEntryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheEntryW(QEMU_G2H(c->lpszUrlSearchPattern), QEMU_G2H(c->lpFirstCacheEntryInfo), QEMU_G2H(c->lpdwFirstCacheEntryInfoBufferSize));
}

#endif

struct qemu_FindNextUrlCacheEntryA
{
    struct qemu_syscall super;
    uint64_t hEnumHandle;
    uint64_t lpNextCacheEntryInfo;
    uint64_t lpdwNextCacheEntryInfoBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheEntryA(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFOA lpNextCacheEntryInfo, LPDWORD lpdwNextCacheEntryInfoBufferSize)
{
    struct qemu_FindNextUrlCacheEntryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHEENTRYA);
    call.hEnumHandle = (ULONG_PTR)hEnumHandle;
    call.lpNextCacheEntryInfo = (ULONG_PTR)lpNextCacheEntryInfo;
    call.lpdwNextCacheEntryInfoBufferSize = (ULONG_PTR)lpdwNextCacheEntryInfoBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextUrlCacheEntryA(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheEntryA *c = (struct qemu_FindNextUrlCacheEntryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheEntryA(QEMU_G2H(c->hEnumHandle), QEMU_G2H(c->lpNextCacheEntryInfo), QEMU_G2H(c->lpdwNextCacheEntryInfoBufferSize));
}

#endif

struct qemu_FindNextUrlCacheEntryW
{
    struct qemu_syscall super;
    uint64_t hEnumHandle;
    uint64_t lpNextCacheEntryInfo;
    uint64_t lpdwNextCacheEntryInfoBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheEntryW(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFOW lpNextCacheEntryInfo, LPDWORD lpdwNextCacheEntryInfoBufferSize)
{
    struct qemu_FindNextUrlCacheEntryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHEENTRYW);
    call.hEnumHandle = (ULONG_PTR)hEnumHandle;
    call.lpNextCacheEntryInfo = (ULONG_PTR)lpNextCacheEntryInfo;
    call.lpdwNextCacheEntryInfoBufferSize = (ULONG_PTR)lpdwNextCacheEntryInfoBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextUrlCacheEntryW(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheEntryW *c = (struct qemu_FindNextUrlCacheEntryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheEntryW(QEMU_G2H(c->hEnumHandle), QEMU_G2H(c->lpNextCacheEntryInfo), QEMU_G2H(c->lpdwNextCacheEntryInfoBufferSize));
}

#endif

struct qemu_FindCloseUrlCache
{
    struct qemu_syscall super;
    uint64_t hEnumHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindCloseUrlCache(HANDLE hEnumHandle)
{
    struct qemu_FindCloseUrlCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDCLOSEURLCACHE);
    call.hEnumHandle = (ULONG_PTR)hEnumHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindCloseUrlCache(struct qemu_syscall *call)
{
    struct qemu_FindCloseUrlCache *c = (struct qemu_FindCloseUrlCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindCloseUrlCache(QEMU_G2H(c->hEnumHandle));
}

#endif

struct qemu_FindFirstUrlCacheGroup
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t dwFilter;
    uint64_t lpSearchCondition;
    uint64_t dwSearchCondition;
    uint64_t lpGroupId;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstUrlCacheGroup(DWORD dwFlags, DWORD dwFilter, LPVOID lpSearchCondition, DWORD dwSearchCondition, GROUPID* lpGroupId, LPVOID lpReserved)
{
    struct qemu_FindFirstUrlCacheGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTURLCACHEGROUP);
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwFilter = (ULONG_PTR)dwFilter;
    call.lpSearchCondition = (ULONG_PTR)lpSearchCondition;
    call.dwSearchCondition = (ULONG_PTR)dwSearchCondition;
    call.lpGroupId = (ULONG_PTR)lpGroupId;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindFirstUrlCacheGroup(struct qemu_syscall *call)
{
    struct qemu_FindFirstUrlCacheGroup *c = (struct qemu_FindFirstUrlCacheGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindFirstUrlCacheGroup(c->dwFlags, c->dwFilter, QEMU_G2H(c->lpSearchCondition), c->dwSearchCondition, QEMU_G2H(c->lpGroupId), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_FindNextUrlCacheEntryExA
{
    struct qemu_syscall super;
    uint64_t hEnumHandle;
    uint64_t lpFirstCacheEntryInfo;
    uint64_t lpdwFirstCacheEntryInfoBufferSize;
    uint64_t lpReserved;
    uint64_t pcbReserved2;
    uint64_t lpReserved3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheEntryExA(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFOA lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize, LPVOID lpReserved, LPDWORD pcbReserved2, LPVOID lpReserved3)
{
    struct qemu_FindNextUrlCacheEntryExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHEENTRYEXA);
    call.hEnumHandle = (ULONG_PTR)hEnumHandle;
    call.lpFirstCacheEntryInfo = (ULONG_PTR)lpFirstCacheEntryInfo;
    call.lpdwFirstCacheEntryInfoBufferSize = (ULONG_PTR)lpdwFirstCacheEntryInfoBufferSize;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.pcbReserved2 = (ULONG_PTR)pcbReserved2;
    call.lpReserved3 = (ULONG_PTR)lpReserved3;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextUrlCacheEntryExA(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheEntryExA *c = (struct qemu_FindNextUrlCacheEntryExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheEntryExA(QEMU_G2H(c->hEnumHandle), QEMU_G2H(c->lpFirstCacheEntryInfo), QEMU_G2H(c->lpdwFirstCacheEntryInfoBufferSize), QEMU_G2H(c->lpReserved), QEMU_G2H(c->pcbReserved2), QEMU_G2H(c->lpReserved3));
}

#endif

struct qemu_FindNextUrlCacheEntryExW
{
    struct qemu_syscall super;
    uint64_t hEnumHandle;
    uint64_t lpFirstCacheEntryInfo;
    uint64_t lpdwFirstCacheEntryInfoBufferSize;
    uint64_t lpReserved;
    uint64_t pcbReserved2;
    uint64_t lpReserved3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheEntryExW(HANDLE hEnumHandle, LPINTERNET_CACHE_ENTRY_INFOW lpFirstCacheEntryInfo, LPDWORD lpdwFirstCacheEntryInfoBufferSize, LPVOID lpReserved, LPDWORD pcbReserved2, LPVOID lpReserved3)
{
    struct qemu_FindNextUrlCacheEntryExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHEENTRYEXW);
    call.hEnumHandle = (ULONG_PTR)hEnumHandle;
    call.lpFirstCacheEntryInfo = (ULONG_PTR)lpFirstCacheEntryInfo;
    call.lpdwFirstCacheEntryInfoBufferSize = (ULONG_PTR)lpdwFirstCacheEntryInfoBufferSize;
    call.lpReserved = (ULONG_PTR)lpReserved;
    call.pcbReserved2 = (ULONG_PTR)pcbReserved2;
    call.lpReserved3 = (ULONG_PTR)lpReserved3;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextUrlCacheEntryExW(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheEntryExW *c = (struct qemu_FindNextUrlCacheEntryExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheEntryExW(QEMU_G2H(c->hEnumHandle), QEMU_G2H(c->lpFirstCacheEntryInfo), QEMU_G2H(c->lpdwFirstCacheEntryInfoBufferSize), QEMU_G2H(c->lpReserved), QEMU_G2H(c->pcbReserved2), QEMU_G2H(c->lpReserved3));
}

#endif

struct qemu_FindNextUrlCacheGroup
{
    struct qemu_syscall super;
    uint64_t hFind;
    uint64_t lpGroupId;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextUrlCacheGroup(HANDLE hFind, GROUPID* lpGroupId, LPVOID lpReserved)
{
    struct qemu_FindNextUrlCacheGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTURLCACHEGROUP);
    call.hFind = (ULONG_PTR)hFind;
    call.lpGroupId = (ULONG_PTR)lpGroupId;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextUrlCacheGroup(struct qemu_syscall *call)
{
    struct qemu_FindNextUrlCacheGroup *c = (struct qemu_FindNextUrlCacheGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextUrlCacheGroup(QEMU_G2H(c->hFind), QEMU_G2H(c->lpGroupId), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_CreateUrlCacheGroup
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI GROUPID WINAPI CreateUrlCacheGroup(DWORD dwFlags, LPVOID lpReserved)
{
    struct qemu_CreateUrlCacheGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEURLCACHEGROUP);
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateUrlCacheGroup(struct qemu_syscall *call)
{
    struct qemu_CreateUrlCacheGroup *c = (struct qemu_CreateUrlCacheGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateUrlCacheGroup(c->dwFlags, QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_DeleteUrlCacheGroup
{
    struct qemu_syscall super;
    uint64_t GroupId;
    uint64_t dwFlags;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteUrlCacheGroup(GROUPID GroupId, DWORD dwFlags, LPVOID lpReserved)
{
    struct qemu_DeleteUrlCacheGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEURLCACHEGROUP);
    call.GroupId = (ULONG_PTR)GroupId;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteUrlCacheGroup(struct qemu_syscall *call)
{
    struct qemu_DeleteUrlCacheGroup *c = (struct qemu_DeleteUrlCacheGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteUrlCacheGroup(c->GroupId, c->dwFlags, QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_DeleteWpadCacheForNetworks
{
    struct qemu_syscall super;
    uint64_t unk1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteWpadCacheForNetworks(DWORD unk1)
{
    struct qemu_DeleteWpadCacheForNetworks call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEWPADCACHEFORNETWORKS);
    call.unk1 = (ULONG_PTR)unk1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DeleteWpadCacheForNetworks to Wine headers? */
extern BOOL WINAPI DeleteWpadCacheForNetworks(DWORD unk1);
void qemu_DeleteWpadCacheForNetworks(struct qemu_syscall *call)
{
    struct qemu_DeleteWpadCacheForNetworks *c = (struct qemu_DeleteWpadCacheForNetworks *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteWpadCacheForNetworks(c->unk1);
}

#endif

struct qemu_SetUrlCacheEntryGroupA
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t dwFlags;
    uint64_t GroupId;
    uint64_t pbGroupAttributes;
    uint64_t cbGroupAttributes;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheEntryGroupA(LPCSTR lpszUrlName, DWORD dwFlags, GROUPID GroupId, LPBYTE pbGroupAttributes, DWORD cbGroupAttributes, LPVOID lpReserved)
{
    struct qemu_SetUrlCacheEntryGroupA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHEENTRYGROUPA);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.GroupId = (ULONG_PTR)GroupId;
    call.pbGroupAttributes = (ULONG_PTR)pbGroupAttributes;
    call.cbGroupAttributes = (ULONG_PTR)cbGroupAttributes;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUrlCacheEntryGroupA(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheEntryGroupA *c = (struct qemu_SetUrlCacheEntryGroupA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheEntryGroupA(QEMU_G2H(c->lpszUrlName), c->dwFlags, c->GroupId, QEMU_G2H(c->pbGroupAttributes), c->cbGroupAttributes, QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SetUrlCacheEntryGroupW
{
    struct qemu_syscall super;
    uint64_t lpszUrlName;
    uint64_t dwFlags;
    uint64_t GroupId;
    uint64_t pbGroupAttributes;
    uint64_t cbGroupAttributes;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheEntryGroupW(LPCWSTR lpszUrlName, DWORD dwFlags, GROUPID GroupId, LPBYTE pbGroupAttributes, DWORD cbGroupAttributes, LPVOID lpReserved)
{
    struct qemu_SetUrlCacheEntryGroupW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHEENTRYGROUPW);
    call.lpszUrlName = (ULONG_PTR)lpszUrlName;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.GroupId = (ULONG_PTR)GroupId;
    call.pbGroupAttributes = (ULONG_PTR)pbGroupAttributes;
    call.cbGroupAttributes = (ULONG_PTR)cbGroupAttributes;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUrlCacheEntryGroupW(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheEntryGroupW *c = (struct qemu_SetUrlCacheEntryGroupW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheEntryGroupW(QEMU_G2H(c->lpszUrlName), c->dwFlags, c->GroupId, QEMU_G2H(c->pbGroupAttributes), c->cbGroupAttributes, QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_GetUrlCacheConfigInfoW
{
    struct qemu_syscall super;
    uint64_t CacheInfo;
    uint64_t size;
    uint64_t bitmask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheConfigInfoW(LPINTERNET_CACHE_CONFIG_INFOW CacheInfo, LPDWORD size, DWORD bitmask)
{
    struct qemu_GetUrlCacheConfigInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHECONFIGINFOW);
    call.CacheInfo = (ULONG_PTR)CacheInfo;
    call.size = (ULONG_PTR)size;
    call.bitmask = (ULONG_PTR)bitmask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetUrlCacheConfigInfoW to Wine headers? */
extern BOOL WINAPI GetUrlCacheConfigInfoW(LPINTERNET_CACHE_CONFIG_INFOW CacheInfo, LPDWORD size, DWORD bitmask);
void qemu_GetUrlCacheConfigInfoW(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheConfigInfoW *c = (struct qemu_GetUrlCacheConfigInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheConfigInfoW(QEMU_G2H(c->CacheInfo), QEMU_G2H(c->size), c->bitmask);
}

#endif

struct qemu_GetUrlCacheConfigInfoA
{
    struct qemu_syscall super;
    uint64_t CacheInfo;
    uint64_t size;
    uint64_t bitmask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheConfigInfoA(LPINTERNET_CACHE_CONFIG_INFOA CacheInfo, LPDWORD size, DWORD bitmask)
{
    struct qemu_GetUrlCacheConfigInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHECONFIGINFOA);
    call.CacheInfo = (ULONG_PTR)CacheInfo;
    call.size = (ULONG_PTR)size;
    call.bitmask = (ULONG_PTR)bitmask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetUrlCacheConfigInfoA to Wine headers? */
extern BOOL WINAPI GetUrlCacheConfigInfoA(LPINTERNET_CACHE_CONFIG_INFOA CacheInfo, LPDWORD size, DWORD bitmask);
void qemu_GetUrlCacheConfigInfoA(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheConfigInfoA *c = (struct qemu_GetUrlCacheConfigInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheConfigInfoA(QEMU_G2H(c->CacheInfo), QEMU_G2H(c->size), c->bitmask);
}

#endif

struct qemu_GetUrlCacheGroupAttributeA
{
    struct qemu_syscall super;
    uint64_t gid;
    uint64_t dwFlags;
    uint64_t dwAttributes;
    uint64_t lpGroupInfo;
    uint64_t lpdwGroupInfo;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheGroupAttributeA(GROUPID gid, DWORD dwFlags, DWORD dwAttributes, LPINTERNET_CACHE_GROUP_INFOA lpGroupInfo, LPDWORD lpdwGroupInfo, LPVOID lpReserved)
{
    struct qemu_GetUrlCacheGroupAttributeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHEGROUPATTRIBUTEA);
    call.gid = (ULONG_PTR)gid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwAttributes = (ULONG_PTR)dwAttributes;
    call.lpGroupInfo = (ULONG_PTR)lpGroupInfo;
    call.lpdwGroupInfo = (ULONG_PTR)lpdwGroupInfo;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUrlCacheGroupAttributeA(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheGroupAttributeA *c = (struct qemu_GetUrlCacheGroupAttributeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheGroupAttributeA(c->gid, c->dwFlags, c->dwAttributes, QEMU_G2H(c->lpGroupInfo), QEMU_G2H(c->lpdwGroupInfo), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_GetUrlCacheGroupAttributeW
{
    struct qemu_syscall super;
    uint64_t gid;
    uint64_t dwFlags;
    uint64_t dwAttributes;
    uint64_t lpGroupInfo;
    uint64_t lpdwGroupInfo;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUrlCacheGroupAttributeW(GROUPID gid, DWORD dwFlags, DWORD dwAttributes, LPINTERNET_CACHE_GROUP_INFOW lpGroupInfo, LPDWORD lpdwGroupInfo, LPVOID lpReserved)
{
    struct qemu_GetUrlCacheGroupAttributeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETURLCACHEGROUPATTRIBUTEW);
    call.gid = (ULONG_PTR)gid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwAttributes = (ULONG_PTR)dwAttributes;
    call.lpGroupInfo = (ULONG_PTR)lpGroupInfo;
    call.lpdwGroupInfo = (ULONG_PTR)lpdwGroupInfo;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUrlCacheGroupAttributeW(struct qemu_syscall *call)
{
    struct qemu_GetUrlCacheGroupAttributeW *c = (struct qemu_GetUrlCacheGroupAttributeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUrlCacheGroupAttributeW(c->gid, c->dwFlags, c->dwAttributes, QEMU_G2H(c->lpGroupInfo), QEMU_G2H(c->lpdwGroupInfo), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SetUrlCacheGroupAttributeA
{
    struct qemu_syscall super;
    uint64_t gid;
    uint64_t dwFlags;
    uint64_t dwAttributes;
    uint64_t lpGroupInfo;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheGroupAttributeA(GROUPID gid, DWORD dwFlags, DWORD dwAttributes, LPINTERNET_CACHE_GROUP_INFOA lpGroupInfo, LPVOID lpReserved)
{
    struct qemu_SetUrlCacheGroupAttributeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHEGROUPATTRIBUTEA);
    call.gid = (ULONG_PTR)gid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwAttributes = (ULONG_PTR)dwAttributes;
    call.lpGroupInfo = (ULONG_PTR)lpGroupInfo;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUrlCacheGroupAttributeA(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheGroupAttributeA *c = (struct qemu_SetUrlCacheGroupAttributeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheGroupAttributeA(c->gid, c->dwFlags, c->dwAttributes, QEMU_G2H(c->lpGroupInfo), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SetUrlCacheGroupAttributeW
{
    struct qemu_syscall super;
    uint64_t gid;
    uint64_t dwFlags;
    uint64_t dwAttributes;
    uint64_t lpGroupInfo;
    uint64_t lpReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheGroupAttributeW(GROUPID gid, DWORD dwFlags, DWORD dwAttributes, LPINTERNET_CACHE_GROUP_INFOW lpGroupInfo, LPVOID lpReserved)
{
    struct qemu_SetUrlCacheGroupAttributeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHEGROUPATTRIBUTEW);
    call.gid = (ULONG_PTR)gid;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwAttributes = (ULONG_PTR)dwAttributes;
    call.lpGroupInfo = (ULONG_PTR)lpGroupInfo;
    call.lpReserved = (ULONG_PTR)lpReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUrlCacheGroupAttributeW(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheGroupAttributeW *c = (struct qemu_SetUrlCacheGroupAttributeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheGroupAttributeW(c->gid, c->dwFlags, c->dwAttributes, QEMU_G2H(c->lpGroupInfo), QEMU_G2H(c->lpReserved));
}

#endif

struct qemu_SetUrlCacheConfigInfoA
{
    struct qemu_syscall super;
    uint64_t lpCacheConfigInfo;
    uint64_t dwFieldControl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheConfigInfoA(LPINTERNET_CACHE_CONFIG_INFOA lpCacheConfigInfo, DWORD dwFieldControl)
{
    struct qemu_SetUrlCacheConfigInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHECONFIGINFOA);
    call.lpCacheConfigInfo = (ULONG_PTR)lpCacheConfigInfo;
    call.dwFieldControl = (ULONG_PTR)dwFieldControl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetUrlCacheConfigInfoA to Wine headers? */
extern BOOL WINAPI SetUrlCacheConfigInfoA(LPINTERNET_CACHE_CONFIG_INFOA lpCacheConfigInfo, DWORD dwFieldControl);
void qemu_SetUrlCacheConfigInfoA(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheConfigInfoA *c = (struct qemu_SetUrlCacheConfigInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheConfigInfoA(QEMU_G2H(c->lpCacheConfigInfo), c->dwFieldControl);
}

#endif

struct qemu_SetUrlCacheConfigInfoW
{
    struct qemu_syscall super;
    uint64_t lpCacheConfigInfo;
    uint64_t dwFieldControl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetUrlCacheConfigInfoW(LPINTERNET_CACHE_CONFIG_INFOW lpCacheConfigInfo, DWORD dwFieldControl)
{
    struct qemu_SetUrlCacheConfigInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETURLCACHECONFIGINFOW);
    call.lpCacheConfigInfo = (ULONG_PTR)lpCacheConfigInfo;
    call.dwFieldControl = (ULONG_PTR)dwFieldControl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetUrlCacheConfigInfoW to Wine headers? */
extern BOOL WINAPI SetUrlCacheConfigInfoW(LPINTERNET_CACHE_CONFIG_INFOW lpCacheConfigInfo, DWORD dwFieldControl);
void qemu_SetUrlCacheConfigInfoW(struct qemu_syscall *call)
{
    struct qemu_SetUrlCacheConfigInfoW *c = (struct qemu_SetUrlCacheConfigInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUrlCacheConfigInfoW(QEMU_G2H(c->lpCacheConfigInfo), c->dwFieldControl);
}

#endif

struct qemu_DeleteIE3Cache
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t lpszCmdLine;
    uint64_t nCmdShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeleteIE3Cache(HWND hWnd, HINSTANCE hInst, LPSTR lpszCmdLine, int nCmdShow)
{
    struct qemu_DeleteIE3Cache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEIE3CACHE);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.lpszCmdLine = (ULONG_PTR)lpszCmdLine;
    call.nCmdShow = (ULONG_PTR)nCmdShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DeleteIE3Cache to Wine headers? */
extern DWORD WINAPI DeleteIE3Cache(HWND hWnd, HINSTANCE hInst, LPSTR lpszCmdLine, int nCmdShow);
void qemu_DeleteIE3Cache(struct qemu_syscall *call)
{
    struct qemu_DeleteIE3Cache *c = (struct qemu_DeleteIE3Cache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteIE3Cache(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->lpszCmdLine), c->nCmdShow);
}

#endif

struct qemu_IsUrlCacheEntryExpiredA
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t dwFlags;
    uint64_t pftLastModified;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsUrlCacheEntryExpiredA(LPCSTR url, DWORD dwFlags, FILETIME* pftLastModified)
{
    struct qemu_IsUrlCacheEntryExpiredA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISURLCACHEENTRYEXPIREDA);
    call.url = (ULONG_PTR)url;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pftLastModified = (ULONG_PTR)pftLastModified;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsUrlCacheEntryExpiredA to Wine headers? */
extern BOOL WINAPI IsUrlCacheEntryExpiredA(LPCSTR url, DWORD dwFlags, FILETIME* pftLastModified);
void qemu_IsUrlCacheEntryExpiredA(struct qemu_syscall *call)
{
    struct qemu_IsUrlCacheEntryExpiredA *c = (struct qemu_IsUrlCacheEntryExpiredA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsUrlCacheEntryExpiredA(QEMU_G2H(c->url), c->dwFlags, QEMU_G2H(c->pftLastModified));
}

#endif

struct qemu_IsUrlCacheEntryExpiredW
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t dwFlags;
    uint64_t pftLastModified;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsUrlCacheEntryExpiredW(LPCWSTR url, DWORD dwFlags, FILETIME* pftLastModified)
{
    struct qemu_IsUrlCacheEntryExpiredW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISURLCACHEENTRYEXPIREDW);
    call.url = (ULONG_PTR)url;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pftLastModified = (ULONG_PTR)pftLastModified;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsUrlCacheEntryExpiredW to Wine headers? */
extern BOOL WINAPI IsUrlCacheEntryExpiredW(LPCWSTR url, DWORD dwFlags, FILETIME* pftLastModified);
void qemu_IsUrlCacheEntryExpiredW(struct qemu_syscall *call)
{
    struct qemu_IsUrlCacheEntryExpiredW *c = (struct qemu_IsUrlCacheEntryExpiredW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsUrlCacheEntryExpiredW(QEMU_G2H(c->url), c->dwFlags, QEMU_G2H(c->pftLastModified));
}

#endif

struct qemu_GetDiskInfoA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t cluster_size;
    uint64_t free;
    uint64_t total;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDiskInfoA(PCSTR path, PDWORD cluster_size, PDWORDLONG free, PDWORDLONG total)
{
    struct qemu_GetDiskInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISKINFOA);
    call.path = (ULONG_PTR)path;
    call.cluster_size = (ULONG_PTR)cluster_size;
    call.free = (ULONG_PTR)free;
    call.total = (ULONG_PTR)total;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetDiskInfoA to Wine headers? */
extern BOOL WINAPI GetDiskInfoA(PCSTR path, PDWORD cluster_size, PDWORDLONG free, PDWORDLONG total);
void qemu_GetDiskInfoA(struct qemu_syscall *call)
{
    struct qemu_GetDiskInfoA *c = (struct qemu_GetDiskInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDiskInfoA(QEMU_G2H(c->path), QEMU_G2H(c->cluster_size), QEMU_G2H(c->free), QEMU_G2H(c->total));
}

#endif

struct qemu_RegisterUrlCacheNotification
{
    struct qemu_syscall super;
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t e;
    uint64_t f;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RegisterUrlCacheNotification(LPVOID a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f)
{
    struct qemu_RegisterUrlCacheNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERURLCACHENOTIFICATION);
    call.a = (ULONG_PTR)a;
    call.b = (ULONG_PTR)b;
    call.c = (ULONG_PTR)c;
    call.d = (ULONG_PTR)d;
    call.e = (ULONG_PTR)e;
    call.f = (ULONG_PTR)f;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterUrlCacheNotification to Wine headers? */
extern DWORD WINAPI RegisterUrlCacheNotification(LPVOID a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f);
void qemu_RegisterUrlCacheNotification(struct qemu_syscall *call)
{
    struct qemu_RegisterUrlCacheNotification *c = (struct qemu_RegisterUrlCacheNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterUrlCacheNotification(QEMU_G2H(c->a), c->b, c->c, c->d, c->e, c->f);
}

#endif

struct qemu_IncrementUrlCacheHeaderData
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IncrementUrlCacheHeaderData(DWORD index, LPDWORD data)
{
    struct qemu_IncrementUrlCacheHeaderData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INCREMENTURLCACHEHEADERDATA);
    call.index = (ULONG_PTR)index;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IncrementUrlCacheHeaderData to Wine headers? */
extern BOOL WINAPI IncrementUrlCacheHeaderData(DWORD index, LPDWORD data);
void qemu_IncrementUrlCacheHeaderData(struct qemu_syscall *call)
{
    struct qemu_IncrementUrlCacheHeaderData *c = (struct qemu_IncrementUrlCacheHeaderData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IncrementUrlCacheHeaderData(c->index, QEMU_G2H(c->data));
}

#endif

struct qemu_RunOnceUrlCache
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t hinst;
    uint64_t cmd;
    uint64_t cmdshow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RunOnceUrlCache(HWND hwnd, HINSTANCE hinst, LPSTR cmd, int cmdshow)
{
    struct qemu_RunOnceUrlCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RUNONCEURLCACHE);
    call.hwnd = (ULONG_PTR)hwnd;
    call.hinst = (ULONG_PTR)hinst;
    call.cmd = (ULONG_PTR)cmd;
    call.cmdshow = (ULONG_PTR)cmdshow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RunOnceUrlCache to Wine headers? */
extern DWORD WINAPI RunOnceUrlCache(HWND hwnd, HINSTANCE hinst, LPSTR cmd, int cmdshow);
void qemu_RunOnceUrlCache(struct qemu_syscall *call)
{
    struct qemu_RunOnceUrlCache *c = (struct qemu_RunOnceUrlCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RunOnceUrlCache(QEMU_G2H(c->hwnd), QEMU_G2H(c->hinst), QEMU_G2H(c->cmd), c->cmdshow);
}

#endif

struct qemu_LoadUrlCacheContent
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LoadUrlCacheContent(void)
{
    struct qemu_LoadUrlCacheContent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADURLCACHECONTENT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add LoadUrlCacheContent to Wine headers? */
extern BOOL WINAPI LoadUrlCacheContent(void);
void qemu_LoadUrlCacheContent(struct qemu_syscall *call)
{
    struct qemu_LoadUrlCacheContent *c = (struct qemu_LoadUrlCacheContent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LoadUrlCacheContent();
}

#endif

