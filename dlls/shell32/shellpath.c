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
#include <shlobj.h>
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
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
    call.nFolder = (ULONG_PTR)nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = (ULONG_PTR)dwFlags;
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

WINBASEAPI HRESULT WINAPI SHGetFolderPathAndSubDirA(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPCSTR pszSubPath, LPSTR pszPath)
{
    struct qemu_SHGetFolderPathAndSubDirA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHANDSUBDIRA);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = (ULONG_PTR)nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pszSubPath = (ULONG_PTR)pszSubPath;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathAndSubDirA(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathAndSubDirA *c = (struct qemu_SHGetFolderPathAndSubDirA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetFolderPathAndSubDirA(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwFlags, QEMU_G2H(c->pszSubPath), QEMU_G2H(c->pszPath));
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

WINBASEAPI HRESULT WINAPI SHGetFolderPathAndSubDirW(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPCWSTR pszSubPath, LPWSTR pszPath)
{
    struct qemu_SHGetFolderPathAndSubDirW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFOLDERPATHANDSUBDIRW);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = (ULONG_PTR)nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pszSubPath = (ULONG_PTR)pszSubPath;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathAndSubDirW(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathAndSubDirW *c = (struct qemu_SHGetFolderPathAndSubDirW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetFolderPathAndSubDirW(QEMU_G2H(c->hwndOwner), c->nFolder, QEMU_G2H(c->hToken), c->dwFlags, QEMU_G2H(c->pszSubPath), QEMU_G2H(c->pszPath));
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
    call.nFolder = (ULONG_PTR)nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFolderPathA(struct qemu_syscall *call)
{
    struct qemu_SHGetFolderPathA *c = (struct qemu_SHGetFolderPathA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.nFolder = (ULONG_PTR)nFolder;
    call.bCreate = (ULONG_PTR)bCreate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSpecialFolderPathA(struct qemu_syscall *call)
{
    struct qemu_SHGetSpecialFolderPathA *c = (struct qemu_SHGetSpecialFolderPathA *)call;
    WINE_FIXME("Unverified!\n");
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
    call.nFolder = (ULONG_PTR)nFolder;
    call.bCreate = (ULONG_PTR)bCreate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSpecialFolderPathW(struct qemu_syscall *call)
{
    struct qemu_SHGetSpecialFolderPathW *c = (struct qemu_SHGetSpecialFolderPathW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.nFolder = (ULONG_PTR)nFolder;
    call.hToken = (ULONG_PTR)hToken;
    call.dwReserved = (ULONG_PTR)dwReserved;
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
    call.nFolder = (ULONG_PTR)nFolder;
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
    call.flags = (ULONG_PTR)flags;
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
    call.flags = (ULONG_PTR)flags;
    call.token = (ULONG_PTR)token;
    call.path = (ULONG_PTR)path;
    call.len = (ULONG_PTR)len;

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
    call.flags = (ULONG_PTR)flags;
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
    call.flags = (ULONG_PTR)flags;
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

