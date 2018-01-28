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
#include "qemu_version.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_version);
#endif


struct qemu_GetFileVersionInfoSizeW
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileVersionInfoSizeW(LPCWSTR filename, LPDWORD handle)
{
    struct qemu_GetFileVersionInfoSizeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOSIZEW);
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoSizeW(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoSizeW *c = (struct qemu_GetFileVersionInfoSizeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoSizeW(QEMU_G2H(c->filename), QEMU_G2H(c->handle));
}

#endif

struct qemu_GetFileVersionInfoSizeA
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileVersionInfoSizeA(LPCSTR filename, LPDWORD handle)
{
    struct qemu_GetFileVersionInfoSizeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOSIZEA);
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoSizeA(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoSizeA *c = (struct qemu_GetFileVersionInfoSizeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoSizeA(QEMU_G2H(c->filename), QEMU_G2H(c->handle));
}

#endif

struct qemu_GetFileVersionInfoSizeExW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t filename;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileVersionInfoSizeExW(DWORD flags, LPCWSTR filename, LPDWORD handle)
{
    struct qemu_GetFileVersionInfoSizeExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOSIZEEXW);
    call.flags = (ULONG_PTR)flags;
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoSizeExW(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoSizeExW *c = (struct qemu_GetFileVersionInfoSizeExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoSizeExW(c->flags, QEMU_G2H(c->filename), QEMU_G2H(c->handle));
}

#endif

struct qemu_GetFileVersionInfoSizeExA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t filename;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetFileVersionInfoSizeExA(DWORD flags, LPCSTR filename, LPDWORD handle)
{
    struct qemu_GetFileVersionInfoSizeExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOSIZEEXA);
    call.flags = (ULONG_PTR)flags;
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoSizeExA(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoSizeExA *c = (struct qemu_GetFileVersionInfoSizeExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoSizeExA(c->flags, QEMU_G2H(c->filename), QEMU_G2H(c->handle));
}

#endif

struct qemu_GetFileVersionInfoExW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t filename;
    uint64_t handle;
    uint64_t datasize;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileVersionInfoExW(DWORD flags, LPCWSTR filename, DWORD handle, DWORD datasize, LPVOID data)
{
    struct qemu_GetFileVersionInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOEXW);
    call.flags = (ULONG_PTR)flags;
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;
    call.datasize = (ULONG_PTR)datasize;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoExW *c = (struct qemu_GetFileVersionInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoExW(c->flags, QEMU_G2H(c->filename), c->handle, c->datasize, QEMU_G2H(c->data));
}

#endif

struct qemu_GetFileVersionInfoExA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t filename;
    uint64_t handle;
    uint64_t datasize;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileVersionInfoExA(DWORD flags, LPCSTR filename, DWORD handle, DWORD datasize, LPVOID data)
{
    struct qemu_GetFileVersionInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOEXA);
    call.flags = (ULONG_PTR)flags;
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;
    call.datasize = (ULONG_PTR)datasize;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoExA(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoExA *c = (struct qemu_GetFileVersionInfoExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoExA(c->flags, QEMU_G2H(c->filename), c->handle, c->datasize, QEMU_G2H(c->data));
}

#endif

struct qemu_GetFileVersionInfoW
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t handle;
    uint64_t datasize;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileVersionInfoW(LPCWSTR filename, DWORD handle, DWORD datasize, LPVOID data)
{
    struct qemu_GetFileVersionInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOW);
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;
    call.datasize = (ULONG_PTR)datasize;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoW(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoW *c = (struct qemu_GetFileVersionInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoW(QEMU_G2H(c->filename), c->handle, c->datasize, QEMU_G2H(c->data));
}

#endif

struct qemu_GetFileVersionInfoA
{
    struct qemu_syscall super;
    uint64_t filename;
    uint64_t handle;
    uint64_t datasize;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFileVersionInfoA(LPCSTR filename, DWORD handle, DWORD datasize, LPVOID data)
{
    struct qemu_GetFileVersionInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILEVERSIONINFOA);
    call.filename = (ULONG_PTR)filename;
    call.handle = (ULONG_PTR)handle;
    call.datasize = (ULONG_PTR)datasize;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileVersionInfoA(struct qemu_syscall *call)
{
    struct qemu_GetFileVersionInfoA *c = (struct qemu_GetFileVersionInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFileVersionInfoA(QEMU_G2H(c->filename), c->handle, c->datasize, QEMU_G2H(c->data));
}

#endif

struct qemu_VerQueryValueA
{
    struct qemu_syscall super;
    uint64_t pBlock;
    uint64_t lpSubBlock;
    uint64_t lplpBuffer;
    uint64_t puLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerQueryValueA(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen)
{
    struct qemu_VerQueryValueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERQUERYVALUEA);
    call.pBlock = (ULONG_PTR)pBlock;
    call.lpSubBlock = (ULONG_PTR)lpSubBlock;
    call.lplpBuffer = !!lplpBuffer;
    call.puLen = (ULONG_PTR)puLen;

    qemu_syscall(&call.super);
    if (lplpBuffer)
        *lplpBuffer = (void *)(ULONG_PTR)call.lplpBuffer;

    return call.super.iret;
}

#else

void qemu_VerQueryValueA(struct qemu_syscall *call)
{
    struct qemu_VerQueryValueA *c = (struct qemu_VerQueryValueA *)call;
    void *buffer;
    WINE_FIXME("Unverified!\n");

    c->super.iret = VerQueryValueA(QEMU_G2H(c->pBlock), QEMU_G2H(c->lpSubBlock), c->lplpBuffer ? &buffer : NULL,
            QEMU_G2H(c->puLen));
    c->lplpBuffer = QEMU_H2G(buffer);
}

#endif

struct qemu_VerQueryValueW
{
    struct qemu_syscall super;
    uint64_t pBlock;
    uint64_t lpSubBlock;
    uint64_t lplpBuffer;
    uint64_t puLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI VerQueryValueW(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen)
{
    struct qemu_VerQueryValueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERQUERYVALUEW);
    call.pBlock = (ULONG_PTR)pBlock;
    call.lpSubBlock = (ULONG_PTR)lpSubBlock;
    call.lplpBuffer = (ULONG_PTR)lplpBuffer;
    call.puLen = (ULONG_PTR)puLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerQueryValueW(struct qemu_syscall *call)
{
    struct qemu_VerQueryValueW *c = (struct qemu_VerQueryValueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerQueryValueW(QEMU_G2H(c->pBlock), QEMU_G2H(c->lpSubBlock), QEMU_G2H(c->lplpBuffer), QEMU_G2H(c->puLen));
}

#endif

struct qemu_VerFindFileA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t lpszFilename;
    uint64_t lpszWinDir;
    uint64_t lpszAppDir;
    uint64_t lpszCurDir;
    uint64_t lpuCurDirLen;
    uint64_t lpszDestDir;
    uint64_t lpuDestDirLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI VerFindFileA(DWORD flags, LPSTR lpszFilename, LPSTR lpszWinDir, LPSTR lpszAppDir, LPSTR lpszCurDir, PUINT lpuCurDirLen, LPSTR lpszDestDir, PUINT lpuDestDirLen)
{
    struct qemu_VerFindFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERFINDFILEA);
    call.flags = (ULONG_PTR)flags;
    call.lpszFilename = (ULONG_PTR)lpszFilename;
    call.lpszWinDir = (ULONG_PTR)lpszWinDir;
    call.lpszAppDir = (ULONG_PTR)lpszAppDir;
    call.lpszCurDir = (ULONG_PTR)lpszCurDir;
    call.lpuCurDirLen = (ULONG_PTR)lpuCurDirLen;
    call.lpszDestDir = (ULONG_PTR)lpszDestDir;
    call.lpuDestDirLen = (ULONG_PTR)lpuDestDirLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerFindFileA(struct qemu_syscall *call)
{
    struct qemu_VerFindFileA *c = (struct qemu_VerFindFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerFindFileA(c->flags, QEMU_G2H(c->lpszFilename), QEMU_G2H(c->lpszWinDir), QEMU_G2H(c->lpszAppDir), QEMU_G2H(c->lpszCurDir), QEMU_G2H(c->lpuCurDirLen), QEMU_G2H(c->lpszDestDir), QEMU_G2H(c->lpuDestDirLen));
}

#endif

struct qemu_VerFindFileW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t lpszFilename;
    uint64_t lpszWinDir;
    uint64_t lpszAppDir;
    uint64_t lpszCurDir;
    uint64_t lpuCurDirLen;
    uint64_t lpszDestDir;
    uint64_t lpuDestDirLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI VerFindFileW(DWORD flags,LPWSTR lpszFilename,LPWSTR lpszWinDir, LPWSTR lpszAppDir, LPWSTR lpszCurDir,PUINT lpuCurDirLen, LPWSTR lpszDestDir,PUINT lpuDestDirLen)
{
    struct qemu_VerFindFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERFINDFILEW);
    call.flags = (ULONG_PTR)flags;
    call.lpszFilename = (ULONG_PTR)lpszFilename;
    call.lpszWinDir = (ULONG_PTR)lpszWinDir;
    call.lpszAppDir = (ULONG_PTR)lpszAppDir;
    call.lpszCurDir = (ULONG_PTR)lpszCurDir;
    call.lpuCurDirLen = (ULONG_PTR)lpuCurDirLen;
    call.lpszDestDir = (ULONG_PTR)lpszDestDir;
    call.lpuDestDirLen = (ULONG_PTR)lpuDestDirLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerFindFileW(struct qemu_syscall *call)
{
    struct qemu_VerFindFileW *c = (struct qemu_VerFindFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerFindFileW(c->flags, QEMU_G2H(c->lpszFilename), QEMU_G2H(c->lpszWinDir), QEMU_G2H(c->lpszAppDir), QEMU_G2H(c->lpszCurDir), QEMU_G2H(c->lpuCurDirLen), QEMU_G2H(c->lpszDestDir), QEMU_G2H(c->lpuDestDirLen));
}

#endif

struct qemu_VerInstallFileA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t srcfilename;
    uint64_t destfilename;
    uint64_t srcdir;
    uint64_t destdir;
    uint64_t curdir;
    uint64_t tmpfile;
    uint64_t tmpfilelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI VerInstallFileA(DWORD flags,LPSTR srcfilename,LPSTR destfilename,LPSTR srcdir, LPSTR destdir,LPSTR curdir,LPSTR tmpfile,PUINT tmpfilelen)
{
    struct qemu_VerInstallFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERINSTALLFILEA);
    call.flags = (ULONG_PTR)flags;
    call.srcfilename = (ULONG_PTR)srcfilename;
    call.destfilename = (ULONG_PTR)destfilename;
    call.srcdir = (ULONG_PTR)srcdir;
    call.destdir = (ULONG_PTR)destdir;
    call.curdir = (ULONG_PTR)curdir;
    call.tmpfile = (ULONG_PTR)tmpfile;
    call.tmpfilelen = (ULONG_PTR)tmpfilelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerInstallFileA(struct qemu_syscall *call)
{
    struct qemu_VerInstallFileA *c = (struct qemu_VerInstallFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerInstallFileA(c->flags, QEMU_G2H(c->srcfilename), QEMU_G2H(c->destfilename), QEMU_G2H(c->srcdir), QEMU_G2H(c->destdir), QEMU_G2H(c->curdir), QEMU_G2H(c->tmpfile), QEMU_G2H(c->tmpfilelen));
}

#endif

struct qemu_VerInstallFileW
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t srcfilename;
    uint64_t destfilename;
    uint64_t srcdir;
    uint64_t destdir;
    uint64_t curdir;
    uint64_t tmpfile;
    uint64_t tmpfilelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI VerInstallFileW(DWORD flags,LPWSTR srcfilename,LPWSTR destfilename,LPWSTR srcdir, LPWSTR destdir,LPWSTR curdir,LPWSTR tmpfile,PUINT tmpfilelen)
{
    struct qemu_VerInstallFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERINSTALLFILEW);
    call.flags = (ULONG_PTR)flags;
    call.srcfilename = (ULONG_PTR)srcfilename;
    call.destfilename = (ULONG_PTR)destfilename;
    call.srcdir = (ULONG_PTR)srcdir;
    call.destdir = (ULONG_PTR)destdir;
    call.curdir = (ULONG_PTR)curdir;
    call.tmpfile = (ULONG_PTR)tmpfile;
    call.tmpfilelen = (ULONG_PTR)tmpfilelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerInstallFileW(struct qemu_syscall *call)
{
    struct qemu_VerInstallFileW *c = (struct qemu_VerInstallFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VerInstallFileW(c->flags, QEMU_G2H(c->srcfilename), QEMU_G2H(c->destfilename), QEMU_G2H(c->srcdir), QEMU_G2H(c->destdir), QEMU_G2H(c->curdir), QEMU_G2H(c->tmpfile), QEMU_G2H(c->tmpfilelen));
}

#endif

