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
#include <shtypes.h>
#include <shlwapi.h>
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_IsLFNDriveAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsLFNDriveAW(LPCSTR lpszPath)
{
    struct qemu_IsLFNDriveAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISLFNDRIVEAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsLFNDrive to Wine headers? */
extern BOOL WINAPI IsLFNDrive(LPCSTR lpszPath);
void qemu_IsLFNDriveAW(struct qemu_syscall *call)
{
    struct qemu_IsLFNDriveAW *c = (struct qemu_IsLFNDriveAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsLFNDrive(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_IsLFNDriveA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsLFNDriveA(LPCSTR lpszPath)
{
    struct qemu_IsLFNDriveA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISLFNDRIVEA);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsLFNDriveA to Wine headers? */
extern BOOL WINAPI IsLFNDriveA(LPCSTR lpszPath);
void qemu_IsLFNDriveA(struct qemu_syscall *call)
{
    struct qemu_IsLFNDriveA *c = (struct qemu_IsLFNDriveA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsLFNDriveA(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_IsLFNDriveW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsLFNDriveW(LPCWSTR lpszPath)
{
    struct qemu_IsLFNDriveW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISLFNDRIVEW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsLFNDriveW to Wine headers? */
extern BOOL WINAPI IsLFNDriveW(LPCWSTR lpszPath);
void qemu_IsLFNDriveW(struct qemu_syscall *call)
{
    struct qemu_IsLFNDriveW *c = (struct qemu_IsLFNDriveW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsLFNDriveW(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathYetAnotherMakeUniqueName
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t path;
    uint64_t shortname;
    uint64_t longname;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathYetAnotherMakeUniqueName(LPWSTR buffer, LPCWSTR path, LPCWSTR shortname, LPCWSTR longname)
{
    struct qemu_PathYetAnotherMakeUniqueName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHYETANOTHERMAKEUNIQUENAME);
    call.buffer = (ULONG_PTR)buffer;
    call.path = (ULONG_PTR)path;
    call.shortname = (ULONG_PTR)shortname;
    call.longname = (ULONG_PTR)longname;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathYetAnotherMakeUniqueName(struct qemu_syscall *call)
{
    struct qemu_PathYetAnotherMakeUniqueName *c = (struct qemu_PathYetAnotherMakeUniqueName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathYetAnotherMakeUniqueName(QEMU_G2H(c->buffer), QEMU_G2H(c->path), QEMU_G2H(c->shortname), QEMU_G2H(c->longname));
}

#endif

struct qemu_SHGetFolderPathW
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t hToken;
    uint64_t dwFlags;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetFolderPathW(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath)
{
    struct qemu_SHGetFolderPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHW);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = dwFlags;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathW(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathW *c = (struct qemu_SHGetFolderPathW *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetFolderPathW(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwFlags, QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetFolderPathAndSubDirA
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t hToken;
    uint64_t dwFlags;
    uint64_t pszSubPath;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetFolderPathAndSubDirA(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags,
        LPCSTR pszSubPath, LPSTR pszPath)
{
    struct qemu_SHGetFolderPathAndSubDirA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHANDSUBDIRA);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = dwFlags;
    call.pszSubPath = (ULONG_PTR)pszSubPath;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathAndSubDirA(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathAndSubDirA *c = (struct qemu_SHGetFolderPathAndSubDirA *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetFolderPathAndSubDirA(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwFlags,
            QEMU_G2H(c->pszSubPath), QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetFolderPathAndSubDirW
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t hToken;
    uint64_t dwFlags;
    uint64_t pszSubPath;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetFolderPathAndSubDirW(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags,
        LPCWSTR pszSubPath, LPWSTR pszPath)
{
    struct qemu_SHGetFolderPathAndSubDirW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHANDSUBDIRW);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = dwFlags;
    call.pszSubPath = (ULONG_PTR)pszSubPath;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathAndSubDirW(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathAndSubDirW *c = (struct qemu_SHGetFolderPathAndSubDirW *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetFolderPathAndSubDirW(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwFlags,
            QEMU_G2H(c->pszSubPath), QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetFolderPathA
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t hToken;
    uint64_t dwFlags;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetFolderPathA(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPSTR pszPath)
{
    struct qemu_SHGetFolderPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHA);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = dwFlags;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathA(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathA *c = (struct qemu_SHGetFolderPathA *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetFolderPathA(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwFlags, QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetSpecialFolderPathA
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t szPath;
    uint64_t nFolder;
    uint64_t bCreate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetSpecialFolderPathA (HWND hwndOwner, LPSTR szPath, int nFolder, BOOL bCreate)
{
    struct qemu_SHGetSpecialFolderPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSPECIALFOLDERPATHA);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.szPath = (ULONG_PTR)szPath;
    call.nFolder = nFolder;
    call.bCreate = bCreate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSpecialFolderPathA(struct qemu_syscall *call)
{
    struct qemu_SHGetSpecialFolderPathA *c = (struct qemu_SHGetSpecialFolderPathA *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetSpecialFolderPathA(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->szPath), c->nFolder, c->bCreate);
}

#endif

struct qemu_SHGetSpecialFolderPathW
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t szPath;
    uint64_t nFolder;
    uint64_t bCreate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetSpecialFolderPathW (HWND hwndOwner, LPWSTR szPath, int nFolder, BOOL bCreate)
{
    struct qemu_SHGetSpecialFolderPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSPECIALFOLDERPATHW);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.szPath = (ULONG_PTR)szPath;
    call.nFolder = nFolder;
    call.bCreate = bCreate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSpecialFolderPathW(struct qemu_syscall *call)
{
    struct qemu_SHGetSpecialFolderPathW *c = (struct qemu_SHGetSpecialFolderPathW *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetSpecialFolderPathW(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->szPath), c->nFolder, c->bCreate);
}

#endif

struct qemu_SHGetFolderLocation
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t hToken;
    uint64_t dwReserved;
    uint64_t ppidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetFolderLocation(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwReserved, LPITEMIDLIST *ppidl)
{
    struct qemu_SHGetFolderLocation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERLOCATION);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwReserved = dwReserved;
    call.ppidl = (ULONG_PTR)ppidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderLocation(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderLocation *c = (struct qemu_SHGetFolderLocation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetFolderLocation(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwReserved, QEMU_G2H(c->ppidl));
}

#endif

struct qemu_SHGetSpecialFolderLocation
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t ppidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetSpecialFolderLocation(HWND hwndOwner, INT nFolder, LPITEMIDLIST * ppidl)
{
    struct qemu_SHGetSpecialFolderLocation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSPECIALFOLDERLOCATION);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = nFolder;
    call.ppidl = (ULONG_PTR)ppidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSpecialFolderLocation(struct qemu_syscall *call)
{
    struct qemu_SHGetSpecialFolderLocation *c = (struct qemu_SHGetSpecialFolderLocation *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetSpecialFolderLocation(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->ppidl));
}

#endif

struct qemu_SHGetKnownFolderPath
{
    struct qemu_syscall super;
    uint64_t rfid;
    uint64_t flags;
    uint64_t token;
    uint64_t ret_path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetKnownFolderPath(REFKNOWNFOLDERID rfid, DWORD flags, HANDLE token, WCHAR **ret_path)
{
    struct qemu_SHGetKnownFolderPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETKNOWNFOLDERPATH);
    call.rfid = (ULONG_PTR)rfid;
    call.flags = flags;
    call.token = (ULONG_PTR)token;
    call.ret_path = (ULONG_PTR)ret_path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetKnownFolderPath(struct qemu_syscall *call)
{
    struct qemu_SHGetKnownFolderPath *c = (struct qemu_SHGetKnownFolderPath *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetKnownFolderPath(QEMU_G2H(c->rfid), c->flags, QEMU_G2H(c->token), QEMU_G2H(c->ret_path));
}

#endif

struct qemu_SHGetFolderPathEx
{
    struct qemu_syscall super;
    uint64_t rfid;
    uint64_t flags;
    uint64_t token;
    uint64_t path;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetFolderPathEx(REFKNOWNFOLDERID rfid, DWORD flags, HANDLE token, LPWSTR path, DWORD len)
{
    struct qemu_SHGetFolderPathEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHEX);
    call.rfid = (ULONG_PTR)rfid;
    call.flags = flags;
    call.token = (ULONG_PTR)token;
    call.path = (ULONG_PTR)path;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetFolderPathEx to Wine headers? */
extern HRESULT WINAPI SHGetFolderPathEx(REFKNOWNFOLDERID rfid, DWORD flags, HANDLE token, LPWSTR path, DWORD len);
void qemu_SHGetFolderPathEx(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathEx *c = (struct qemu_SHGetFolderPathEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetFolderPathEx(QEMU_G2H(c->rfid), c->flags, QEMU_G2H(c->token), QEMU_G2H(c->path), c->len);
}

#endif

struct qemu_SHGetKnownFolderIDList
{
    struct qemu_syscall super;
    uint64_t rfid;
    uint64_t flags;
    uint64_t token;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetKnownFolderIDList(REFKNOWNFOLDERID rfid, DWORD flags, HANDLE token, PIDLIST_ABSOLUTE *pidl)
{
    struct qemu_SHGetKnownFolderIDList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETKNOWNFOLDERIDLIST);
    call.rfid = (ULONG_PTR)rfid;
    call.flags = flags;
    call.token = (ULONG_PTR)token;
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetKnownFolderIDList(struct qemu_syscall *call)
{
    struct qemu_SHGetKnownFolderIDList *c = (struct qemu_SHGetKnownFolderIDList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetKnownFolderIDList(QEMU_G2H(c->rfid), c->flags, QEMU_G2H(c->token), QEMU_G2H(c->pidl));
}

#endif

struct qemu_SHGetKnownFolderItem
{
    struct qemu_syscall super;
    uint64_t rfid;
    uint64_t flags;
    uint64_t hToken;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetKnownFolderItem(REFKNOWNFOLDERID rfid, KNOWN_FOLDER_FLAG flags, HANDLE hToken, REFIID riid, void **ppv)
{
    struct qemu_SHGetKnownFolderItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETKNOWNFOLDERITEM);
    call.rfid = (ULONG_PTR)rfid;
    call.flags = flags;
    call.hToken = (ULONG_PTR)hToken;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetKnownFolderItem(struct qemu_syscall *call)
{
    struct qemu_SHGetKnownFolderItem *c = (struct qemu_SHGetKnownFolderItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetKnownFolderItem(QEMU_G2H(c->rfid), c->flags, QEMU_G2H(c->hToken), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_PathAppendAW
{
    struct qemu_syscall super;
    uint64_t lpszPath1;
    uint64_t lpszPath2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathAppendAW(LPVOID lpszPath1, LPCVOID lpszPath2)
{
    struct qemu_PathAppendAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHAPPENDAW);
    call.lpszPath1 = (ULONG_PTR)lpszPath1;
    call.lpszPath2 = (ULONG_PTR)lpszPath2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathAppendAW(struct qemu_syscall *call)
{
    struct qemu_PathAppendAW *c = (struct qemu_PathAppendAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathAppend(QEMU_G2H(c->lpszPath1), QEMU_G2H(c->lpszPath2));
}

#endif

struct qemu_PathCombineAW
{
    struct qemu_syscall super;
    uint64_t szDest;
    uint64_t lpszDir;
    uint64_t lpszFile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathCombineAW(LPVOID szDest, LPCVOID lpszDir, LPCVOID lpszFile)
{
    struct qemu_PathCombineAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCOMBINEAW);
    call.szDest = (ULONG_PTR)szDest;
    call.lpszDir = (ULONG_PTR)lpszDir;
    call.lpszFile = (ULONG_PTR)lpszFile;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathCombineAW(struct qemu_syscall *call)
{
    struct qemu_PathCombineAW *c = (struct qemu_PathCombineAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_PathCombine(QEMU_G2H(c->szDest), QEMU_G2H(c->lpszDir), QEMU_G2H(c->lpszFile));
}

#endif

struct qemu_PathBuildRootAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t drive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathBuildRootAW(LPVOID lpszPath, int drive)
{
    struct qemu_PathBuildRootAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHBUILDROOTAW);
    call.lpszPath = (ULONG_PTR)lpszPath;
    call.drive = drive;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathBuildRootAW(struct qemu_syscall *call)
{
    struct qemu_PathBuildRootAW *c = (struct qemu_PathBuildRootAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_PathBuildRoot(QEMU_G2H(c->lpszPath), c->drive);
}

#endif

struct qemu_PathFindFileNameAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathFindFileNameAW(LPCVOID lpszPath)
{
    struct qemu_PathFindFileNameAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDFILENAMEAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathFindFileNameAW(struct qemu_syscall *call)
{
    struct qemu_PathFindFileNameAW *c = (struct qemu_PathFindFileNameAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_PathFindFileName(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFindExtensionAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathFindExtensionAW(LPCVOID lpszPath)
{
    struct qemu_PathFindExtensionAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDEXTENSIONAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathFindExtensionAW(struct qemu_syscall *call)
{
    struct qemu_PathFindExtensionAW *c = (struct qemu_PathFindExtensionAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_PathFindExtension(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetExtensionAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t void1;
    uint64_t void2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathGetExtensionAW(LPCVOID lpszPath,DWORD void1, DWORD void2)
{
    struct qemu_PathGetExtensionAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETEXTENSIONAW);
    call.lpszPath = (ULONG_PTR)lpszPath;
    call.void1 = void1;
    call.void2 = void2;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add PathGetExtension to Wine headers? */
extern LPVOID WINAPI PathGetExtension(LPCVOID lpszPath,DWORD void1, DWORD void2);
void qemu_PathGetExtensionAW(struct qemu_syscall *call)
{
    struct qemu_PathGetExtensionAW *c = (struct qemu_PathGetExtensionAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)PathGetExtension(QEMU_G2H(c->lpszPath), c->void1, c->void2);
}

#endif

struct qemu_PathGetArgsAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathGetArgsAW(LPVOID lpszPath)
{
    struct qemu_PathGetArgsAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETARGSAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathGetArgsAW(struct qemu_syscall *call)
{
    struct qemu_PathGetArgsAW *c = (struct qemu_PathGetArgsAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_PathGetArgs(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetDriveNumberAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathGetDriveNumberAW(LPVOID lpszPath)
{
    struct qemu_PathGetDriveNumberAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETDRIVENUMBERAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathGetDriveNumberAW(struct qemu_syscall *call)
{
    struct qemu_PathGetDriveNumberAW *c = (struct qemu_PathGetDriveNumberAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathGetDriveNumber(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathStripToRootAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathStripToRootAW(LPVOID lpszPath)
{
    struct qemu_PathStripToRootAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSTRIPTOROOTAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathStripToRootAW(struct qemu_syscall *call)
{
    struct qemu_PathStripToRootAW *c = (struct qemu_PathStripToRootAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathStripToRoot(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveArgsAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveArgsAW(LPVOID lpszPath)
{
    struct qemu_PathRemoveArgsAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEARGSAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveArgsAW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveArgsAW *c = (struct qemu_PathRemoveArgsAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathRemoveArgs(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathGetShortPathAW
{
    struct qemu_syscall super;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathGetShortPathAW(LPVOID pszPath)
{
    struct qemu_PathGetShortPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHGETSHORTPATHAW);
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathGetShortPathAW(struct qemu_syscall *call)
{
    struct qemu_PathGetShortPathAW *c = (struct qemu_PathGetShortPathAW *)call;
    WINE_FIXME("Unverified!\n");
    PathGetShortPath(QEMU_G2H(c->pszPath));
}

#endif

struct qemu_PathRemoveBlanksAW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveBlanksAW(LPVOID str)
{
    struct qemu_PathRemoveBlanksAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEBLANKSAW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveBlanksAW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveBlanksAW *c = (struct qemu_PathRemoveBlanksAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathRemoveBlanks(QEMU_G2H(c->str));
}

#endif

struct qemu_PathQuoteSpacesAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathQuoteSpacesAW (LPVOID lpszPath)
{
    struct qemu_PathQuoteSpacesAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHQUOTESPACESAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathQuoteSpacesAW(struct qemu_syscall *call)
{
    struct qemu_PathQuoteSpacesAW *c = (struct qemu_PathQuoteSpacesAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathQuoteSpaces(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathUnquoteSpacesAW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathUnquoteSpacesAW(LPVOID str)
{
    struct qemu_PathUnquoteSpacesAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHUNQUOTESPACESAW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_PathUnquoteSpacesAW(struct qemu_syscall *call)
{
    struct qemu_PathUnquoteSpacesAW *c = (struct qemu_PathUnquoteSpacesAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathUnquoteSpaces(QEMU_G2H(c->str));
}

#endif

struct qemu_PathParseIconLocationAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathParseIconLocationAW (LPVOID lpszPath)
{
    struct qemu_PathParseIconLocationAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHPARSEICONLOCATIONAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathParseIconLocationAW(struct qemu_syscall *call)
{
    struct qemu_PathParseIconLocationAW *c = (struct qemu_PathParseIconLocationAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathParseIconLocation(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsRelativeAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsRelativeAW (LPCVOID lpszPath)
{
    struct qemu_PathIsRelativeAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISRELATIVEAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsRelativeAW(struct qemu_syscall *call)
{
    struct qemu_PathIsRelativeAW *c = (struct qemu_PathIsRelativeAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathIsRelative(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsRootAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsRootAW(LPCVOID lpszPath)
{
    struct qemu_PathIsRootAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISROOTAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsRootAW(struct qemu_syscall *call)
{
    struct qemu_PathIsRootAW *c = (struct qemu_PathIsRootAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathIsRoot(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsExeAW
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsExeAW (LPCVOID path)
{
    struct qemu_PathIsExeAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISEXEAW);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathIsExe to Wine headers? */
extern BOOL WINAPI PathIsExe (LPCVOID path);
void qemu_PathIsExeAW(struct qemu_syscall *call)
{
    struct qemu_PathIsExeAW *c = (struct qemu_PathIsExeAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsExe(QEMU_G2H(c->path));
}

#endif

struct qemu_PathIsDirectoryAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsDirectoryAW (LPCVOID lpszPath)
{
    struct qemu_PathIsDirectoryAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISDIRECTORYAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsDirectoryAW(struct qemu_syscall *call)
{
    struct qemu_PathIsDirectoryAW *c = (struct qemu_PathIsDirectoryAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathIsDirectory(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathFileExistsAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFileExistsAW (LPCVOID lpszPath)
{
    struct qemu_PathFileExistsAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFILEEXISTSAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFileExistsAW(struct qemu_syscall *call)
{
    struct qemu_PathFileExistsAW *c = (struct qemu_PathFileExistsAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathFileExists(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsSameRootAW
{
    struct qemu_syscall super;
    uint64_t lpszPath1;
    uint64_t lpszPath2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsSameRootAW(LPCVOID lpszPath1, LPCVOID lpszPath2)
{
    struct qemu_PathIsSameRootAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISSAMEROOTAW);
    call.lpszPath1 = (ULONG_PTR)lpszPath1;
    call.lpszPath2 = (ULONG_PTR)lpszPath2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsSameRootAW(struct qemu_syscall *call)
{
    struct qemu_PathIsSameRootAW *c = (struct qemu_PathIsSameRootAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathIsSameRoot(QEMU_G2H(c->lpszPath1), QEMU_G2H(c->lpszPath2));
}

#endif

struct qemu_PathMakeUniqueNameAW
{
    struct qemu_syscall super;
    uint64_t lpszBuffer;
    uint64_t dwBuffSize;
    uint64_t lpszShortName;
    uint64_t lpszLongName;
    uint64_t lpszPathName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMakeUniqueNameAW(LPVOID lpszBuffer, DWORD dwBuffSize, LPCVOID lpszShortName, LPCVOID lpszLongName, LPCVOID lpszPathName)
{
    struct qemu_PathMakeUniqueNameAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMAKEUNIQUENAMEAW);
    call.lpszBuffer = (ULONG_PTR)lpszBuffer;
    call.dwBuffSize = dwBuffSize;
    call.lpszShortName = (ULONG_PTR)lpszShortName;
    call.lpszLongName = (ULONG_PTR)lpszLongName;
    call.lpszPathName = (ULONG_PTR)lpszPathName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathMakeUniqueName to Wine headers? */
extern BOOL WINAPI PathMakeUniqueName(LPVOID lpszBuffer, DWORD dwBuffSize, LPCVOID lpszShortName, LPCVOID lpszLongName, LPCVOID lpszPathName);
void qemu_PathMakeUniqueNameAW(struct qemu_syscall *call)
{
    struct qemu_PathMakeUniqueNameAW *c = (struct qemu_PathMakeUniqueNameAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathMakeUniqueName(QEMU_G2H(c->lpszBuffer), c->dwBuffSize, QEMU_G2H(c->lpszShortName), QEMU_G2H(c->lpszLongName), QEMU_G2H(c->lpszPathName));
}

#endif

struct qemu_PathFindOnPathAW
{
    struct qemu_syscall super;
    uint64_t sFile;
    uint64_t sOtherDirs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathFindOnPathAW(LPVOID sFile, LPCVOID *sOtherDirs)
{
    struct qemu_PathFindOnPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHFINDONPATHAW);
    call.sFile = (ULONG_PTR)sFile;
    call.sOtherDirs = (ULONG_PTR)sOtherDirs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathFindOnPathAW(struct qemu_syscall *call)
{
    struct qemu_PathFindOnPathAW *c = (struct qemu_PathFindOnPathAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathFindOnPath(QEMU_G2H(c->sFile), QEMU_G2H(c->sOtherDirs));
}

#endif

struct qemu_PathCleanupSpec
{
    struct qemu_syscall super;
    uint64_t lpszPathW;
    uint64_t lpszFileW;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI PathCleanupSpec(LPCWSTR lpszPathW, LPWSTR lpszFileW)
{
    struct qemu_PathCleanupSpec call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHCLEANUPSPEC);
    call.lpszPathW = (ULONG_PTR)lpszPathW;
    call.lpszFileW = (ULONG_PTR)lpszFileW;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathCleanupSpec(struct qemu_syscall *call)
{
    struct qemu_PathCleanupSpec *c = (struct qemu_PathCleanupSpec *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathCleanupSpec(QEMU_G2H(c->lpszPathW), QEMU_G2H(c->lpszFileW));
}

#endif

struct qemu_PathQualifyAW
{
    struct qemu_syscall super;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathQualifyAW(LPCVOID pszPath)
{
    struct qemu_PathQualifyAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHQUALIFYAW);
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PathQualify to Wine headers? */
extern BOOL WINAPI PathQualify(LPCVOID pszPath);
void qemu_PathQualifyAW(struct qemu_syscall *call)
{
    struct qemu_PathQualifyAW *c = (struct qemu_PathQualifyAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathQualify(QEMU_G2H(c->pszPath));
}

#endif

struct qemu_PathResolveAW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t paths;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathResolveAW(LPVOID path, LPCVOID *paths, DWORD flags)
{
    struct qemu_PathResolveAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHRESOLVEAW);
    call.path = (ULONG_PTR)path;
    call.paths = (ULONG_PTR)paths;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathResolveAW(struct qemu_syscall *call)
{
    struct qemu_PathResolveAW *c = (struct qemu_PathResolveAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathResolve(QEMU_G2H(c->path), QEMU_G2H(c->paths), c->flags);
}

#endif

struct qemu_PathProcessCommandAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t lpszBuff;
    uint64_t dwBuffSize;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI PathProcessCommandAW (LPCVOID lpszPath, LPVOID lpszBuff, DWORD dwBuffSize, DWORD dwFlags)
{
    struct qemu_PathProcessCommandAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHPROCESSCOMMANDAW);
    call.lpszPath = (ULONG_PTR)lpszPath;
    call.lpszBuff = (ULONG_PTR)lpszBuff;
    call.dwBuffSize = dwBuffSize;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathProcessCommandAW(struct qemu_syscall *call)
{
    struct qemu_PathProcessCommandAW *c = (struct qemu_PathProcessCommandAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathProcessCommand(QEMU_G2H(c->lpszPath), QEMU_G2H(c->lpszBuff), c->dwBuffSize, c->dwFlags);
}

#endif

struct qemu_PathSetDlgItemPathAW
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t id;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI PathSetDlgItemPathAW(HWND hDlg, int id, LPCVOID pszPath)
{
    struct qemu_PathSetDlgItemPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSETDLGITEMPATHAW);
    call.hDlg = (ULONG_PTR)hDlg;
    call.id = id;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathSetDlgItemPathAW(struct qemu_syscall *call)
{
    struct qemu_PathSetDlgItemPathAW *c = (struct qemu_PathSetDlgItemPathAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathSetDlgItemPath(QEMU_G2H(c->hDlg), c->id, QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetSpecialFolderPathAW
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t szPath;
    uint64_t nFolder;
    uint64_t bCreate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetSpecialFolderPathAW (HWND hwndOwner, LPVOID szPath, int nFolder, BOOL bCreate)
{
    struct qemu_SHGetSpecialFolderPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSPECIALFOLDERPATHAW);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.szPath = (ULONG_PTR)szPath;
    call.nFolder = nFolder;
    call.bCreate = bCreate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSpecialFolderPathAW(struct qemu_syscall *call)
{
    struct qemu_SHGetSpecialFolderPathAW *c = (struct qemu_SHGetSpecialFolderPathAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetSpecialFolderPath(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->szPath), c->nFolder, c->bCreate);
}

#endif

struct qemu_PathAddBackslashAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI PathAddBackslashAW(LPVOID lpszPath)
{
    struct qemu_PathAddBackslashAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHADDBACKSLASHAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_PathAddBackslashAW(struct qemu_syscall *call)
{
    struct qemu_PathAddBackslashAW *c = (struct qemu_PathAddBackslashAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_PathAddBackslash(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathIsUNCAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsUNCAW (LPCVOID lpszPath)
{
    struct qemu_PathIsUNCAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISUNCAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsUNCAW(struct qemu_syscall *call)
{
    struct qemu_PathIsUNCAW *c = (struct qemu_PathIsUNCAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathIsUNC(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathMatchSpecAW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathMatchSpecAW(LPVOID name, LPVOID mask)
{
    struct qemu_PathMatchSpecAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHMATCHSPECAW);
    call.name = (ULONG_PTR)name;
    call.mask = (ULONG_PTR)mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathMatchSpecAW(struct qemu_syscall *call)
{
    struct qemu_PathMatchSpecAW *c = (struct qemu_PathMatchSpecAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathMatchSpec(QEMU_G2H(c->name), QEMU_G2H(c->mask));
}

#endif

struct qemu_PathRemoveExtensionAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathRemoveExtensionAW(LPVOID lpszPath)
{
    struct qemu_PathRemoveExtensionAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEEXTENSIONAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathRemoveExtensionAW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveExtensionAW *c = (struct qemu_PathRemoveExtensionAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathRemoveExtension(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathRemoveFileSpecAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathRemoveFileSpecAW(LPVOID lpszPath)
{
    struct qemu_PathRemoveFileSpecAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHREMOVEFILESPECAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathRemoveFileSpecAW(struct qemu_syscall *call)
{
    struct qemu_PathRemoveFileSpecAW *c = (struct qemu_PathRemoveFileSpecAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_PathRemoveFileSpec(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_PathStripPathAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI PathStripPathAW(LPVOID lpszPath)
{
    struct qemu_PathStripPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHSTRIPPATHAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);
}

#else

void qemu_PathStripPathAW(struct qemu_syscall *call)
{
    struct qemu_PathStripPathAW *c = (struct qemu_PathStripPathAW *)call;
    WINE_FIXME("Unverified!\n");
    p_PathStripPath(QEMU_G2H(c->lpszPath));
}

#endif
