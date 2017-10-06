/*
 * Copyright 2017 André Hentschel
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include "shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_SHIsFileAvailableOffline
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHIsFileAvailableOffline(LPCWSTR path, LPDWORD status)
{
    struct qemu_SHIsFileAvailableOffline call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHISFILEAVAILABLEOFFLINE);
    call.path = (uint64_t)path;
    call.status = (uint64_t)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHIsFileAvailableOffline to Wine headers? */
extern HRESULT WINAPI SHIsFileAvailableOffline(LPCWSTR path, LPDWORD status);
void qemu_SHIsFileAvailableOffline(struct qemu_syscall *call)
{
    struct qemu_SHIsFileAvailableOffline *c = (struct qemu_SHIsFileAvailableOffline *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHIsFileAvailableOffline(QEMU_G2H(c->path), QEMU_G2H(c->status));
}

#endif

struct qemu_Win32CreateDirectory
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t sec;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Win32CreateDirectory(LPCVOID path, LPSECURITY_ATTRIBUTES sec)
{
    struct qemu_Win32CreateDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WIN32CREATEDIRECTORY);
    call.path = (uint64_t)path;
    call.sec = (uint64_t)sec;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add Win32CreateDirectory to Wine headers? */
extern BOOL WINAPI Win32CreateDirectory(LPCVOID path, LPSECURITY_ATTRIBUTES sec);
void qemu_Win32CreateDirectory(struct qemu_syscall *call)
{
    struct qemu_Win32CreateDirectory *c = (struct qemu_Win32CreateDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Win32CreateDirectory(QEMU_G2H(c->path), QEMU_G2H(c->sec));
}

#endif

struct qemu_Win32RemoveDirectory
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Win32RemoveDirectory(LPCVOID path)
{
    struct qemu_Win32RemoveDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WIN32REMOVEDIRECTORY);
    call.path = (uint64_t)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add Win32RemoveDirectory to Wine headers? */
extern BOOL WINAPI Win32RemoveDirectory(LPCVOID path);
void qemu_Win32RemoveDirectory(struct qemu_syscall *call)
{
    struct qemu_Win32RemoveDirectory *c = (struct qemu_Win32RemoveDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Win32RemoveDirectory(QEMU_G2H(c->path));
}

#endif

struct qemu_Win32DeleteFile
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI Win32DeleteFile(const WCHAR *path)
{
    struct qemu_Win32DeleteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WIN32DELETEFILE);
    call.path = (uint64_t)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Win32DeleteFile(struct qemu_syscall *call)
{
    struct qemu_Win32DeleteFile *c = (struct qemu_Win32DeleteFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Win32DeleteFile(QEMU_G2H(c->path));
}

#endif

struct qemu_SHCreateDirectory
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHCreateDirectory(HWND hWnd, const WCHAR *path)
{
    struct qemu_SHCreateDirectory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEDIRECTORY);
    call.hWnd = (uint64_t)hWnd;
    call.path = (uint64_t)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateDirectory(struct qemu_syscall *call)
{
    struct qemu_SHCreateDirectory *c = (struct qemu_SHCreateDirectory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateDirectory(QEMU_G2H(c->hWnd), QEMU_G2H(c->path));
}

#endif

struct qemu_SHCreateDirectoryExA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t path;
    uint64_t sec;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHCreateDirectoryExA(HWND hWnd, LPCSTR path, const SECURITY_ATTRIBUTES *sec)
{
    struct qemu_SHCreateDirectoryExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEDIRECTORYEXA);
    call.hWnd = (uint64_t)hWnd;
    call.path = (uint64_t)path;
    call.sec = (uint64_t)sec;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateDirectoryExA(struct qemu_syscall *call)
{
    struct qemu_SHCreateDirectoryExA *c = (struct qemu_SHCreateDirectoryExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateDirectoryExA(QEMU_G2H(c->hWnd), QEMU_G2H(c->path), QEMU_G2H(c->sec));
}

#endif

struct qemu_SHCreateDirectoryExW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t path;
    uint64_t sec;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHCreateDirectoryExW(HWND hWnd, LPCWSTR path, const SECURITY_ATTRIBUTES *sec)
{
    struct qemu_SHCreateDirectoryExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEDIRECTORYEXW);
    call.hWnd = (uint64_t)hWnd;
    call.path = (uint64_t)path;
    call.sec = (uint64_t)sec;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateDirectoryExW(struct qemu_syscall *call)
{
    struct qemu_SHCreateDirectoryExW *c = (struct qemu_SHCreateDirectoryExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateDirectoryExW(QEMU_G2H(c->hWnd), QEMU_G2H(c->path), QEMU_G2H(c->sec));
}

#endif

struct qemu_SHFileOperationA
{
    struct qemu_syscall super;
    uint64_t lpFileOp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHFileOperationA(LPSHFILEOPSTRUCTA lpFileOp)
{
    struct qemu_SHFileOperationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFILEOPERATIONA);
    call.lpFileOp = (uint64_t)lpFileOp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHFileOperationA(struct qemu_syscall *call)
{
    struct qemu_SHFileOperationA *c = (struct qemu_SHFileOperationA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHFileOperationA(QEMU_G2H(c->lpFileOp));
}

#endif

struct qemu_SHFileOperationW
{
    struct qemu_syscall super;
    uint64_t lpFileOp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHFileOperationW(LPSHFILEOPSTRUCTW lpFileOp)
{
    struct qemu_SHFileOperationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFILEOPERATIONW);
    call.lpFileOp = (uint64_t)lpFileOp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHFileOperationW(struct qemu_syscall *call)
{
    struct qemu_SHFileOperationW *c = (struct qemu_SHFileOperationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHFileOperationW(QEMU_G2H(c->lpFileOp));
}

#endif

struct qemu_SHFreeNameMappings
{
    struct qemu_syscall super;
    uint64_t hNameMapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHFreeNameMappings(HANDLE hNameMapping)
{
    struct qemu_SHFreeNameMappings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFREENAMEMAPPINGS);
    call.hNameMapping = (uint64_t)hNameMapping;

    qemu_syscall(&call.super);
}

#else

void qemu_SHFreeNameMappings(struct qemu_syscall *call)
{
    struct qemu_SHFreeNameMappings *c = (struct qemu_SHFreeNameMappings *)call;
    WINE_FIXME("Unverified!\n");
    SHFreeNameMappings(QEMU_G2H(c->hNameMapping));
}

#endif

struct qemu_SheGetDirA
{
    struct qemu_syscall super;
    uint64_t drive;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SheGetDirA(DWORD drive, LPSTR buffer)
{
    struct qemu_SheGetDirA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHEGETDIRA);
    call.drive = (uint64_t)drive;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SheGetDirA to Wine headers? */
extern DWORD WINAPI SheGetDirA(DWORD drive, LPSTR buffer);
void qemu_SheGetDirA(struct qemu_syscall *call)
{
    struct qemu_SheGetDirA *c = (struct qemu_SheGetDirA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SheGetDirA(c->drive, QEMU_G2H(c->buffer));
}

#endif

struct qemu_SheGetDirW
{
    struct qemu_syscall super;
    uint64_t drive;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SheGetDirW(DWORD drive, LPWSTR buffer)
{
    struct qemu_SheGetDirW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHEGETDIRW);
    call.drive = (uint64_t)drive;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SheGetDirW to Wine headers? */
extern DWORD WINAPI SheGetDirW(DWORD drive, LPWSTR buffer);
void qemu_SheGetDirW(struct qemu_syscall *call)
{
    struct qemu_SheGetDirW *c = (struct qemu_SheGetDirW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SheGetDirW(c->drive, QEMU_G2H(c->buffer));
}

#endif

struct qemu_SheChangeDirA
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SheChangeDirA(LPSTR path)
{
    struct qemu_SheChangeDirA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHECHANGEDIRA);
    call.path = (uint64_t)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SheChangeDirA to Wine headers? */
extern DWORD WINAPI SheChangeDirA(LPSTR path);
void qemu_SheChangeDirA(struct qemu_syscall *call)
{
    struct qemu_SheChangeDirA *c = (struct qemu_SheChangeDirA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SheChangeDirA(QEMU_G2H(c->path));
}

#endif

struct qemu_SheChangeDirW
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SheChangeDirW(LPWSTR path)
{
    struct qemu_SheChangeDirW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHECHANGEDIRW);
    call.path = (uint64_t)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SheChangeDirW to Wine headers? */
extern DWORD WINAPI SheChangeDirW(LPWSTR path);
void qemu_SheChangeDirW(struct qemu_syscall *call)
{
    struct qemu_SheChangeDirW *c = (struct qemu_SheChangeDirW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SheChangeDirW(QEMU_G2H(c->path));
}

#endif

struct qemu_IsNetDrive
{
    struct qemu_syscall super;
    uint64_t drive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI IsNetDrive(int drive)
{
    struct qemu_IsNetDrive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISNETDRIVE);
    call.drive = (uint64_t)drive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsNetDrive(struct qemu_syscall *call)
{
    struct qemu_IsNetDrive *c = (struct qemu_IsNetDrive *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsNetDrive(c->drive);
}

#endif

struct qemu_RealDriveType
{
    struct qemu_syscall super;
    uint64_t drive;
    uint64_t bQueryNet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI RealDriveType(int drive, BOOL bQueryNet)
{
    struct qemu_RealDriveType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALDRIVETYPE);
    call.drive = (uint64_t)drive;
    call.bQueryNet = (uint64_t)bQueryNet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RealDriveType(struct qemu_syscall *call)
{
    struct qemu_RealDriveType *c = (struct qemu_RealDriveType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RealDriveType(c->drive, c->bQueryNet);
}

#endif

struct qemu_SHPathPrepareForWriteA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t modless;
    uint64_t path;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHPathPrepareForWriteA(HWND hwnd, IUnknown *modless, LPCSTR path, DWORD flags)
{
    struct qemu_SHPathPrepareForWriteA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHPATHPREPAREFORWRITEA);
    call.hwnd = (uint64_t)hwnd;
    call.modless = (uint64_t)modless;
    call.path = (uint64_t)path;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHPathPrepareForWriteA(struct qemu_syscall *call)
{
    struct qemu_SHPathPrepareForWriteA *c = (struct qemu_SHPathPrepareForWriteA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHPathPrepareForWriteA(QEMU_G2H(c->hwnd), QEMU_G2H(c->modless), QEMU_G2H(c->path), c->flags);
}

#endif

struct qemu_SHPathPrepareForWriteW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t modless;
    uint64_t path;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHPathPrepareForWriteW(HWND hwnd, IUnknown *modless, LPCWSTR path, DWORD flags)
{
    struct qemu_SHPathPrepareForWriteW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHPATHPREPAREFORWRITEW);
    call.hwnd = (uint64_t)hwnd;
    call.modless = (uint64_t)modless;
    call.path = (uint64_t)path;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHPathPrepareForWriteW(struct qemu_syscall *call)
{
    struct qemu_SHPathPrepareForWriteW *c = (struct qemu_SHPathPrepareForWriteW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHPathPrepareForWriteW(QEMU_G2H(c->hwnd), QEMU_G2H(c->modless), QEMU_G2H(c->path), c->flags);
}

#endif

