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


struct qemu_FtpPutFileA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocalFile;
    uint64_t lpszNewRemoteFile;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpPutFileA(HINTERNET hConnect, LPCSTR lpszLocalFile, LPCSTR lpszNewRemoteFile, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpPutFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPPUTFILEA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocalFile = (ULONG_PTR)lpszLocalFile;
    call.lpszNewRemoteFile = (ULONG_PTR)lpszNewRemoteFile;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpPutFileA(struct qemu_syscall *call)
{
    struct qemu_FtpPutFileA *c = (struct qemu_FtpPutFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpPutFileA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocalFile), QEMU_G2H(c->lpszNewRemoteFile), c->dwFlags, c->dwContext);
}

#endif

struct qemu_FtpPutFileW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszLocalFile;
    uint64_t lpszNewRemoteFile;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpPutFileW(HINTERNET hConnect, LPCWSTR lpszLocalFile, LPCWSTR lpszNewRemoteFile, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpPutFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPPUTFILEW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszLocalFile = (ULONG_PTR)lpszLocalFile;
    call.lpszNewRemoteFile = (ULONG_PTR)lpszNewRemoteFile;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpPutFileW(struct qemu_syscall *call)
{
    struct qemu_FtpPutFileW *c = (struct qemu_FtpPutFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpPutFileW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszLocalFile), QEMU_G2H(c->lpszNewRemoteFile), c->dwFlags, c->dwContext);
}

#endif

struct qemu_FtpSetCurrentDirectoryA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpSetCurrentDirectoryA(HINTERNET hConnect, LPCSTR lpszDirectory)
{
    struct qemu_FtpSetCurrentDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPSETCURRENTDIRECTORYA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszDirectory = (ULONG_PTR)lpszDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpSetCurrentDirectoryA(struct qemu_syscall *call)
{
    struct qemu_FtpSetCurrentDirectoryA *c = (struct qemu_FtpSetCurrentDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpSetCurrentDirectoryA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszDirectory));
}

#endif

struct qemu_FtpSetCurrentDirectoryW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpSetCurrentDirectoryW(HINTERNET hConnect, LPCWSTR lpszDirectory)
{
    struct qemu_FtpSetCurrentDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPSETCURRENTDIRECTORYW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszDirectory = (ULONG_PTR)lpszDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpSetCurrentDirectoryW(struct qemu_syscall *call)
{
    struct qemu_FtpSetCurrentDirectoryW *c = (struct qemu_FtpSetCurrentDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpSetCurrentDirectoryW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszDirectory));
}

#endif

struct qemu_FtpCreateDirectoryA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpCreateDirectoryA(HINTERNET hConnect, LPCSTR lpszDirectory)
{
    struct qemu_FtpCreateDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPCREATEDIRECTORYA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszDirectory = (ULONG_PTR)lpszDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpCreateDirectoryA(struct qemu_syscall *call)
{
    struct qemu_FtpCreateDirectoryA *c = (struct qemu_FtpCreateDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpCreateDirectoryA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszDirectory));
}

#endif

struct qemu_FtpCreateDirectoryW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpCreateDirectoryW(HINTERNET hConnect, LPCWSTR lpszDirectory)
{
    struct qemu_FtpCreateDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPCREATEDIRECTORYW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszDirectory = (ULONG_PTR)lpszDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpCreateDirectoryW(struct qemu_syscall *call)
{
    struct qemu_FtpCreateDirectoryW *c = (struct qemu_FtpCreateDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpCreateDirectoryW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszDirectory));
}

#endif

struct qemu_FtpFindFirstFileA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszSearchFile;
    uint64_t lpFindFileData;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI FtpFindFirstFileA(HINTERNET hConnect, LPCSTR lpszSearchFile, LPWIN32_FIND_DATAA lpFindFileData, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpFindFirstFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPFINDFIRSTFILEA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszSearchFile = (ULONG_PTR)lpszSearchFile;
    call.lpFindFileData = (ULONG_PTR)lpFindFileData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FtpFindFirstFileA(struct qemu_syscall *call)
{
    struct qemu_FtpFindFirstFileA *c = (struct qemu_FtpFindFirstFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FtpFindFirstFileA(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszSearchFile), QEMU_G2H(c->lpFindFileData), c->dwFlags, c->dwContext);
}

#endif

struct qemu_FtpFindFirstFileW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t lpszSearchFile;
    uint64_t lpFindFileData;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI FtpFindFirstFileW(HINTERNET hConnect, LPCWSTR lpszSearchFile, LPWIN32_FIND_DATAW lpFindFileData, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpFindFirstFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPFINDFIRSTFILEW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.lpszSearchFile = (ULONG_PTR)lpszSearchFile;
    call.lpFindFileData = (ULONG_PTR)lpFindFileData;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FtpFindFirstFileW(struct qemu_syscall *call)
{
    struct qemu_FtpFindFirstFileW *c = (struct qemu_FtpFindFirstFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FtpFindFirstFileW(QEMU_G2H(c->hConnect), QEMU_G2H(c->lpszSearchFile), QEMU_G2H(c->lpFindFileData), c->dwFlags, c->dwContext);
}

#endif

struct qemu_FtpGetCurrentDirectoryA
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszCurrentDirectory;
    uint64_t lpdwCurrentDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpGetCurrentDirectoryA(HINTERNET hFtpSession, LPSTR lpszCurrentDirectory, LPDWORD lpdwCurrentDirectory)
{
    struct qemu_FtpGetCurrentDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPGETCURRENTDIRECTORYA);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszCurrentDirectory = (ULONG_PTR)lpszCurrentDirectory;
    call.lpdwCurrentDirectory = (ULONG_PTR)lpdwCurrentDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpGetCurrentDirectoryA(struct qemu_syscall *call)
{
    struct qemu_FtpGetCurrentDirectoryA *c = (struct qemu_FtpGetCurrentDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpGetCurrentDirectoryA(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszCurrentDirectory), QEMU_G2H(c->lpdwCurrentDirectory));
}

#endif

struct qemu_FtpGetCurrentDirectoryW
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszCurrentDirectory;
    uint64_t lpdwCurrentDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpGetCurrentDirectoryW(HINTERNET hFtpSession, LPWSTR lpszCurrentDirectory, LPDWORD lpdwCurrentDirectory)
{
    struct qemu_FtpGetCurrentDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPGETCURRENTDIRECTORYW);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszCurrentDirectory = (ULONG_PTR)lpszCurrentDirectory;
    call.lpdwCurrentDirectory = (ULONG_PTR)lpdwCurrentDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpGetCurrentDirectoryW(struct qemu_syscall *call)
{
    struct qemu_FtpGetCurrentDirectoryW *c = (struct qemu_FtpGetCurrentDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpGetCurrentDirectoryW(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszCurrentDirectory), QEMU_G2H(c->lpdwCurrentDirectory));
}

#endif

struct qemu_FtpOpenFileA
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszFileName;
    uint64_t fdwAccess;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI FtpOpenFileA(HINTERNET hFtpSession, LPCSTR lpszFileName, DWORD fdwAccess, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpOpenFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPOPENFILEA);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.fdwAccess = (ULONG_PTR)fdwAccess;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FtpOpenFileA(struct qemu_syscall *call)
{
    struct qemu_FtpOpenFileA *c = (struct qemu_FtpOpenFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FtpOpenFileA(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszFileName), c->fdwAccess, c->dwFlags, c->dwContext);
}

#endif

struct qemu_FtpOpenFileW
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszFileName;
    uint64_t fdwAccess;
    uint64_t dwFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HINTERNET WINAPI FtpOpenFileW(HINTERNET hFtpSession, LPCWSTR lpszFileName, DWORD fdwAccess, DWORD dwFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpOpenFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPOPENFILEW);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.fdwAccess = (ULONG_PTR)fdwAccess;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return (HINTERNET)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FtpOpenFileW(struct qemu_syscall *call)
{
    struct qemu_FtpOpenFileW *c = (struct qemu_FtpOpenFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FtpOpenFileW(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszFileName), c->fdwAccess, c->dwFlags, c->dwContext);
}

#endif

struct qemu_FtpGetFileA
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpszRemoteFile;
    uint64_t lpszNewFile;
    uint64_t fFailIfExists;
    uint64_t dwLocalFlagsAttribute;
    uint64_t dwInternetFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpGetFileA(HINTERNET hInternet, LPCSTR lpszRemoteFile, LPCSTR lpszNewFile, BOOL fFailIfExists, DWORD dwLocalFlagsAttribute, DWORD dwInternetFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpGetFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPGETFILEA);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpszRemoteFile = (ULONG_PTR)lpszRemoteFile;
    call.lpszNewFile = (ULONG_PTR)lpszNewFile;
    call.fFailIfExists = (ULONG_PTR)fFailIfExists;
    call.dwLocalFlagsAttribute = (ULONG_PTR)dwLocalFlagsAttribute;
    call.dwInternetFlags = (ULONG_PTR)dwInternetFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpGetFileA(struct qemu_syscall *call)
{
    struct qemu_FtpGetFileA *c = (struct qemu_FtpGetFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpGetFileA(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpszRemoteFile), QEMU_G2H(c->lpszNewFile), c->fFailIfExists, c->dwLocalFlagsAttribute, c->dwInternetFlags, c->dwContext);
}

#endif

struct qemu_FtpGetFileW
{
    struct qemu_syscall super;
    uint64_t hInternet;
    uint64_t lpszRemoteFile;
    uint64_t lpszNewFile;
    uint64_t fFailIfExists;
    uint64_t dwLocalFlagsAttribute;
    uint64_t dwInternetFlags;
    uint64_t dwContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpGetFileW(HINTERNET hInternet, LPCWSTR lpszRemoteFile, LPCWSTR lpszNewFile, BOOL fFailIfExists, DWORD dwLocalFlagsAttribute, DWORD dwInternetFlags, DWORD_PTR dwContext)
{
    struct qemu_FtpGetFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPGETFILEW);
    call.hInternet = (ULONG_PTR)hInternet;
    call.lpszRemoteFile = (ULONG_PTR)lpszRemoteFile;
    call.lpszNewFile = (ULONG_PTR)lpszNewFile;
    call.fFailIfExists = (ULONG_PTR)fFailIfExists;
    call.dwLocalFlagsAttribute = (ULONG_PTR)dwLocalFlagsAttribute;
    call.dwInternetFlags = (ULONG_PTR)dwInternetFlags;
    call.dwContext = (ULONG_PTR)dwContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpGetFileW(struct qemu_syscall *call)
{
    struct qemu_FtpGetFileW *c = (struct qemu_FtpGetFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpGetFileW(QEMU_G2H(c->hInternet), QEMU_G2H(c->lpszRemoteFile), QEMU_G2H(c->lpszNewFile), c->fFailIfExists, c->dwLocalFlagsAttribute, c->dwInternetFlags, c->dwContext);
}

#endif

struct qemu_FtpGetFileSize
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpdwFileSizeHigh;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI FtpGetFileSize(HINTERNET hFile, LPDWORD lpdwFileSizeHigh)
{
    struct qemu_FtpGetFileSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPGETFILESIZE);
    call.hFile = (ULONG_PTR)hFile;
    call.lpdwFileSizeHigh = (ULONG_PTR)lpdwFileSizeHigh;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpGetFileSize(struct qemu_syscall *call)
{
    struct qemu_FtpGetFileSize *c = (struct qemu_FtpGetFileSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpGetFileSize(QEMU_G2H(c->hFile), QEMU_G2H(c->lpdwFileSizeHigh));
}

#endif

struct qemu_FtpDeleteFileA
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpDeleteFileA(HINTERNET hFtpSession, LPCSTR lpszFileName)
{
    struct qemu_FtpDeleteFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPDELETEFILEA);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszFileName = (ULONG_PTR)lpszFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpDeleteFileA(struct qemu_syscall *call)
{
    struct qemu_FtpDeleteFileA *c = (struct qemu_FtpDeleteFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpDeleteFileA(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszFileName));
}

#endif

struct qemu_FtpDeleteFileW
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpDeleteFileW(HINTERNET hFtpSession, LPCWSTR lpszFileName)
{
    struct qemu_FtpDeleteFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPDELETEFILEW);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszFileName = (ULONG_PTR)lpszFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpDeleteFileW(struct qemu_syscall *call)
{
    struct qemu_FtpDeleteFileW *c = (struct qemu_FtpDeleteFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpDeleteFileW(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszFileName));
}

#endif

struct qemu_FtpRemoveDirectoryA
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpRemoveDirectoryA(HINTERNET hFtpSession, LPCSTR lpszDirectory)
{
    struct qemu_FtpRemoveDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPREMOVEDIRECTORYA);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszDirectory = (ULONG_PTR)lpszDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpRemoveDirectoryA(struct qemu_syscall *call)
{
    struct qemu_FtpRemoveDirectoryA *c = (struct qemu_FtpRemoveDirectoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpRemoveDirectoryA(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszDirectory));
}

#endif

struct qemu_FtpRemoveDirectoryW
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszDirectory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpRemoveDirectoryW(HINTERNET hFtpSession, LPCWSTR lpszDirectory)
{
    struct qemu_FtpRemoveDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPREMOVEDIRECTORYW);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszDirectory = (ULONG_PTR)lpszDirectory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpRemoveDirectoryW(struct qemu_syscall *call)
{
    struct qemu_FtpRemoveDirectoryW *c = (struct qemu_FtpRemoveDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpRemoveDirectoryW(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszDirectory));
}

#endif

struct qemu_FtpRenameFileA
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszSrc;
    uint64_t lpszDest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpRenameFileA(HINTERNET hFtpSession, LPCSTR lpszSrc, LPCSTR lpszDest)
{
    struct qemu_FtpRenameFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPRENAMEFILEA);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszSrc = (ULONG_PTR)lpszSrc;
    call.lpszDest = (ULONG_PTR)lpszDest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpRenameFileA(struct qemu_syscall *call)
{
    struct qemu_FtpRenameFileA *c = (struct qemu_FtpRenameFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpRenameFileA(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszSrc), QEMU_G2H(c->lpszDest));
}

#endif

struct qemu_FtpRenameFileW
{
    struct qemu_syscall super;
    uint64_t hFtpSession;
    uint64_t lpszSrc;
    uint64_t lpszDest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpRenameFileW(HINTERNET hFtpSession, LPCWSTR lpszSrc, LPCWSTR lpszDest)
{
    struct qemu_FtpRenameFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPRENAMEFILEW);
    call.hFtpSession = (ULONG_PTR)hFtpSession;
    call.lpszSrc = (ULONG_PTR)lpszSrc;
    call.lpszDest = (ULONG_PTR)lpszDest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpRenameFileW(struct qemu_syscall *call)
{
    struct qemu_FtpRenameFileW *c = (struct qemu_FtpRenameFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpRenameFileW(QEMU_G2H(c->hFtpSession), QEMU_G2H(c->lpszSrc), QEMU_G2H(c->lpszDest));
}

#endif

struct qemu_FtpCommandA
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t fExpectResponse;
    uint64_t dwFlags;
    uint64_t lpszCommand;
    uint64_t dwContext;
    uint64_t phFtpCommand;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpCommandA(HINTERNET hConnect, BOOL fExpectResponse, DWORD dwFlags, LPCSTR lpszCommand, DWORD_PTR dwContext, HINTERNET* phFtpCommand)
{
    struct qemu_FtpCommandA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPCOMMANDA);
    call.hConnect = (ULONG_PTR)hConnect;
    call.fExpectResponse = (ULONG_PTR)fExpectResponse;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpszCommand = (ULONG_PTR)lpszCommand;
    call.dwContext = (ULONG_PTR)dwContext;
    call.phFtpCommand = (ULONG_PTR)phFtpCommand;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpCommandA(struct qemu_syscall *call)
{
    struct qemu_FtpCommandA *c = (struct qemu_FtpCommandA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpCommandA(QEMU_G2H(c->hConnect), c->fExpectResponse, c->dwFlags, QEMU_G2H(c->lpszCommand), c->dwContext, QEMU_G2H(c->phFtpCommand));
}

#endif

struct qemu_FtpCommandW
{
    struct qemu_syscall super;
    uint64_t hConnect;
    uint64_t fExpectResponse;
    uint64_t dwFlags;
    uint64_t lpszCommand;
    uint64_t dwContext;
    uint64_t phFtpCommand;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FtpCommandW(HINTERNET hConnect, BOOL fExpectResponse, DWORD dwFlags, LPCWSTR lpszCommand, DWORD_PTR dwContext, HINTERNET* phFtpCommand)
{
    struct qemu_FtpCommandW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FTPCOMMANDW);
    call.hConnect = (ULONG_PTR)hConnect;
    call.fExpectResponse = (ULONG_PTR)fExpectResponse;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpszCommand = (ULONG_PTR)lpszCommand;
    call.dwContext = (ULONG_PTR)dwContext;
    call.phFtpCommand = (ULONG_PTR)phFtpCommand;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FtpCommandW(struct qemu_syscall *call)
{
    struct qemu_FtpCommandW *c = (struct qemu_FtpCommandW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FtpCommandW(QEMU_G2H(c->hConnect), c->fExpectResponse, c->dwFlags, QEMU_G2H(c->lpszCommand), c->dwContext, QEMU_G2H(c->phFtpCommand));
}

#endif

