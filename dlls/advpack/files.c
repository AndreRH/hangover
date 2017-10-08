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
#include <setupapi.h>
#include <advpub.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "advpack.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advpack);
#endif


struct qemu_AddDelBackupEntryA
{
    struct qemu_syscall super;
    uint64_t lpcszFileList;
    uint64_t lpcszBackupDir;
    uint64_t lpcszBaseName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AddDelBackupEntryA(LPCSTR lpcszFileList, LPCSTR lpcszBackupDir, LPCSTR lpcszBaseName, DWORD dwFlags)
{
    struct qemu_AddDelBackupEntryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDDELBACKUPENTRYA);
    call.lpcszFileList = (ULONG_PTR)lpcszFileList;
    call.lpcszBackupDir = (ULONG_PTR)lpcszBackupDir;
    call.lpcszBaseName = (ULONG_PTR)lpcszBaseName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddDelBackupEntryA(struct qemu_syscall *call)
{
    struct qemu_AddDelBackupEntryA *c = (struct qemu_AddDelBackupEntryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddDelBackupEntryA(QEMU_G2H(c->lpcszFileList), QEMU_G2H(c->lpcszBackupDir), QEMU_G2H(c->lpcszBaseName), c->dwFlags);
}

#endif

struct qemu_AddDelBackupEntryW
{
    struct qemu_syscall super;
    uint64_t lpcszFileList;
    uint64_t lpcszBackupDir;
    uint64_t lpcszBaseName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AddDelBackupEntryW(LPCWSTR lpcszFileList, LPCWSTR lpcszBackupDir, LPCWSTR lpcszBaseName, DWORD dwFlags)
{
    struct qemu_AddDelBackupEntryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDDELBACKUPENTRYW);
    call.lpcszFileList = (ULONG_PTR)lpcszFileList;
    call.lpcszBackupDir = (ULONG_PTR)lpcszBackupDir;
    call.lpcszBaseName = (ULONG_PTR)lpcszBaseName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddDelBackupEntryW(struct qemu_syscall *call)
{
    struct qemu_AddDelBackupEntryW *c = (struct qemu_AddDelBackupEntryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddDelBackupEntryW(QEMU_G2H(c->lpcszFileList), QEMU_G2H(c->lpcszBackupDir), QEMU_G2H(c->lpcszBaseName), c->dwFlags);
}

#endif

struct qemu_AdvInstallFileA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpszSourceDir;
    uint64_t lpszSourceFile;
    uint64_t lpszDestDir;
    uint64_t lpszDestFile;
    uint64_t dwFlags;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AdvInstallFileA(HWND hwnd, LPCSTR lpszSourceDir, LPCSTR lpszSourceFile, LPCSTR lpszDestDir, LPCSTR lpszDestFile, DWORD dwFlags, DWORD dwReserved)
{
    struct qemu_AdvInstallFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADVINSTALLFILEA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpszSourceDir = (ULONG_PTR)lpszSourceDir;
    call.lpszSourceFile = (ULONG_PTR)lpszSourceFile;
    call.lpszDestDir = (ULONG_PTR)lpszDestDir;
    call.lpszDestFile = (ULONG_PTR)lpszDestFile;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdvInstallFileA(struct qemu_syscall *call)
{
    struct qemu_AdvInstallFileA *c = (struct qemu_AdvInstallFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AdvInstallFileA(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpszSourceDir), QEMU_G2H(c->lpszSourceFile), QEMU_G2H(c->lpszDestDir), QEMU_G2H(c->lpszDestFile), c->dwFlags, c->dwReserved);
}

#endif

struct qemu_AdvInstallFileW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lpszSourceDir;
    uint64_t lpszSourceFile;
    uint64_t lpszDestDir;
    uint64_t lpszDestFile;
    uint64_t dwFlags;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AdvInstallFileW(HWND hwnd, LPCWSTR lpszSourceDir, LPCWSTR lpszSourceFile, LPCWSTR lpszDestDir, LPCWSTR lpszDestFile, DWORD dwFlags, DWORD dwReserved)
{
    struct qemu_AdvInstallFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADVINSTALLFILEW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.lpszSourceDir = (ULONG_PTR)lpszSourceDir;
    call.lpszSourceFile = (ULONG_PTR)lpszSourceFile;
    call.lpszDestDir = (ULONG_PTR)lpszDestDir;
    call.lpszDestFile = (ULONG_PTR)lpszDestFile;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdvInstallFileW(struct qemu_syscall *call)
{
    struct qemu_AdvInstallFileW *c = (struct qemu_AdvInstallFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AdvInstallFileW(QEMU_G2H(c->hwnd), QEMU_G2H(c->lpszSourceDir), QEMU_G2H(c->lpszSourceFile), QEMU_G2H(c->lpszDestDir), QEMU_G2H(c->lpszDestFile), c->dwFlags, c->dwReserved);
}

#endif

struct qemu_DelNodeA
{
    struct qemu_syscall super;
    uint64_t pszFileOrDirName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DelNodeA(LPCSTR pszFileOrDirName, DWORD dwFlags)
{
    struct qemu_DelNodeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELNODEA);
    call.pszFileOrDirName = (ULONG_PTR)pszFileOrDirName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DelNodeA(struct qemu_syscall *call)
{
    struct qemu_DelNodeA *c = (struct qemu_DelNodeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DelNodeA(QEMU_G2H(c->pszFileOrDirName), c->dwFlags);
}

#endif

struct qemu_DelNodeW
{
    struct qemu_syscall super;
    uint64_t pszFileOrDirName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DelNodeW(LPCWSTR pszFileOrDirName, DWORD dwFlags)
{
    struct qemu_DelNodeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELNODEW);
    call.pszFileOrDirName = (ULONG_PTR)pszFileOrDirName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DelNodeW(struct qemu_syscall *call)
{
    struct qemu_DelNodeW *c = (struct qemu_DelNodeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DelNodeW(QEMU_G2H(c->pszFileOrDirName), c->dwFlags);
}

#endif

struct qemu_DelNodeRunDLL32A
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DelNodeRunDLL32A(HWND hWnd, HINSTANCE hInst, LPSTR cmdline, INT show)
{
    struct qemu_DelNodeRunDLL32A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELNODERUNDLL32A);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DelNodeRunDLL32A(struct qemu_syscall *call)
{
    struct qemu_DelNodeRunDLL32A *c = (struct qemu_DelNodeRunDLL32A *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DelNodeRunDLL32A(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_DelNodeRunDLL32W
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DelNodeRunDLL32W(HWND hWnd, HINSTANCE hInst, LPWSTR cmdline, INT show)
{
    struct qemu_DelNodeRunDLL32W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELNODERUNDLL32W);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DelNodeRunDLL32W(struct qemu_syscall *call)
{
    struct qemu_DelNodeRunDLL32W *c = (struct qemu_DelNodeRunDLL32W *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DelNodeRunDLL32W(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_ExtractFilesA
{
    struct qemu_syscall super;
    uint64_t CabName;
    uint64_t ExpandDir;
    uint64_t Flags;
    uint64_t FileList;
    uint64_t LReserved;
    uint64_t Reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ExtractFilesA(LPCSTR CabName, LPCSTR ExpandDir, DWORD Flags, LPCSTR FileList, LPVOID LReserved, DWORD Reserved)
{
    struct qemu_ExtractFilesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTFILESA);
    call.CabName = (ULONG_PTR)CabName;
    call.ExpandDir = (ULONG_PTR)ExpandDir;
    call.Flags = (ULONG_PTR)Flags;
    call.FileList = (ULONG_PTR)FileList;
    call.LReserved = (ULONG_PTR)LReserved;
    call.Reserved = (ULONG_PTR)Reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtractFilesA(struct qemu_syscall *call)
{
    struct qemu_ExtractFilesA *c = (struct qemu_ExtractFilesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtractFilesA(QEMU_G2H(c->CabName), QEMU_G2H(c->ExpandDir), c->Flags, QEMU_G2H(c->FileList), QEMU_G2H(c->LReserved), c->Reserved);
}

#endif

struct qemu_ExtractFilesW
{
    struct qemu_syscall super;
    uint64_t CabName;
    uint64_t ExpandDir;
    uint64_t Flags;
    uint64_t FileList;
    uint64_t LReserved;
    uint64_t Reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ExtractFilesW(LPCWSTR CabName, LPCWSTR ExpandDir, DWORD Flags, LPCWSTR FileList, LPVOID LReserved, DWORD Reserved)
{
    struct qemu_ExtractFilesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTFILESW);
    call.CabName = (ULONG_PTR)CabName;
    call.ExpandDir = (ULONG_PTR)ExpandDir;
    call.Flags = (ULONG_PTR)Flags;
    call.FileList = (ULONG_PTR)FileList;
    call.LReserved = (ULONG_PTR)LReserved;
    call.Reserved = (ULONG_PTR)Reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtractFilesW(struct qemu_syscall *call)
{
    struct qemu_ExtractFilesW *c = (struct qemu_ExtractFilesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtractFilesW(QEMU_G2H(c->CabName), QEMU_G2H(c->ExpandDir), c->Flags, QEMU_G2H(c->FileList), QEMU_G2H(c->LReserved), c->Reserved);
}

#endif

struct qemu_FileSaveMarkNotExistA
{
    struct qemu_syscall super;
    uint64_t pszFileList;
    uint64_t pszDir;
    uint64_t pszBaseName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI FileSaveMarkNotExistA(LPSTR pszFileList, LPSTR pszDir, LPSTR pszBaseName)
{
    struct qemu_FileSaveMarkNotExistA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILESAVEMARKNOTEXISTA);
    call.pszFileList = (ULONG_PTR)pszFileList;
    call.pszDir = (ULONG_PTR)pszDir;
    call.pszBaseName = (ULONG_PTR)pszBaseName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileSaveMarkNotExistA(struct qemu_syscall *call)
{
    struct qemu_FileSaveMarkNotExistA *c = (struct qemu_FileSaveMarkNotExistA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileSaveMarkNotExistA(QEMU_G2H(c->pszFileList), QEMU_G2H(c->pszDir), QEMU_G2H(c->pszBaseName));
}

#endif

struct qemu_FileSaveMarkNotExistW
{
    struct qemu_syscall super;
    uint64_t pszFileList;
    uint64_t pszDir;
    uint64_t pszBaseName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI FileSaveMarkNotExistW(LPWSTR pszFileList, LPWSTR pszDir, LPWSTR pszBaseName)
{
    struct qemu_FileSaveMarkNotExistW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILESAVEMARKNOTEXISTW);
    call.pszFileList = (ULONG_PTR)pszFileList;
    call.pszDir = (ULONG_PTR)pszDir;
    call.pszBaseName = (ULONG_PTR)pszBaseName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileSaveMarkNotExistW(struct qemu_syscall *call)
{
    struct qemu_FileSaveMarkNotExistW *c = (struct qemu_FileSaveMarkNotExistW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileSaveMarkNotExistW(QEMU_G2H(c->pszFileList), QEMU_G2H(c->pszDir), QEMU_G2H(c->pszBaseName));
}

#endif

struct qemu_FileSaveRestoreA
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t pszFileList;
    uint64_t pszDir;
    uint64_t pszBaseName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI FileSaveRestoreA(HWND hDlg, LPSTR pszFileList, LPSTR pszDir, LPSTR pszBaseName, DWORD dwFlags)
{
    struct qemu_FileSaveRestoreA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILESAVERESTOREA);
    call.hDlg = (ULONG_PTR)hDlg;
    call.pszFileList = (ULONG_PTR)pszFileList;
    call.pszDir = (ULONG_PTR)pszDir;
    call.pszBaseName = (ULONG_PTR)pszBaseName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileSaveRestoreA(struct qemu_syscall *call)
{
    struct qemu_FileSaveRestoreA *c = (struct qemu_FileSaveRestoreA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileSaveRestoreA(QEMU_G2H(c->hDlg), QEMU_G2H(c->pszFileList), QEMU_G2H(c->pszDir), QEMU_G2H(c->pszBaseName), c->dwFlags);
}

#endif

struct qemu_FileSaveRestoreW
{
    struct qemu_syscall super;
    uint64_t hDlg;
    uint64_t pszFileList;
    uint64_t pszDir;
    uint64_t pszBaseName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI FileSaveRestoreW(HWND hDlg, LPWSTR pszFileList, LPWSTR pszDir, LPWSTR pszBaseName, DWORD dwFlags)
{
    struct qemu_FileSaveRestoreW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILESAVERESTOREW);
    call.hDlg = (ULONG_PTR)hDlg;
    call.pszFileList = (ULONG_PTR)pszFileList;
    call.pszDir = (ULONG_PTR)pszDir;
    call.pszBaseName = (ULONG_PTR)pszBaseName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileSaveRestoreW(struct qemu_syscall *call)
{
    struct qemu_FileSaveRestoreW *c = (struct qemu_FileSaveRestoreW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileSaveRestoreW(QEMU_G2H(c->hDlg), QEMU_G2H(c->pszFileList), QEMU_G2H(c->pszDir), QEMU_G2H(c->pszBaseName), c->dwFlags);
}

#endif

struct qemu_FileSaveRestoreOnINFA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitle;
    uint64_t pszINF;
    uint64_t pszSection;
    uint64_t pszBackupDir;
    uint64_t pszBaseBackupFile;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI FileSaveRestoreOnINFA(HWND hWnd, LPCSTR pszTitle, LPCSTR pszINF, LPCSTR pszSection, LPCSTR pszBackupDir, LPCSTR pszBaseBackupFile, DWORD dwFlags)
{
    struct qemu_FileSaveRestoreOnINFA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILESAVERESTOREONINFA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitle = (ULONG_PTR)pszTitle;
    call.pszINF = (ULONG_PTR)pszINF;
    call.pszSection = (ULONG_PTR)pszSection;
    call.pszBackupDir = (ULONG_PTR)pszBackupDir;
    call.pszBaseBackupFile = (ULONG_PTR)pszBaseBackupFile;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileSaveRestoreOnINFA(struct qemu_syscall *call)
{
    struct qemu_FileSaveRestoreOnINFA *c = (struct qemu_FileSaveRestoreOnINFA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileSaveRestoreOnINFA(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitle), QEMU_G2H(c->pszINF), QEMU_G2H(c->pszSection), QEMU_G2H(c->pszBackupDir), QEMU_G2H(c->pszBaseBackupFile), c->dwFlags);
}

#endif

struct qemu_FileSaveRestoreOnINFW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitle;
    uint64_t pszINF;
    uint64_t pszSection;
    uint64_t pszBackupDir;
    uint64_t pszBaseBackupFile;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI FileSaveRestoreOnINFW(HWND hWnd, LPCWSTR pszTitle, LPCWSTR pszINF, LPCWSTR pszSection, LPCWSTR pszBackupDir, LPCWSTR pszBaseBackupFile, DWORD dwFlags)
{
    struct qemu_FileSaveRestoreOnINFW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILESAVERESTOREONINFW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitle = (ULONG_PTR)pszTitle;
    call.pszINF = (ULONG_PTR)pszINF;
    call.pszSection = (ULONG_PTR)pszSection;
    call.pszBackupDir = (ULONG_PTR)pszBackupDir;
    call.pszBaseBackupFile = (ULONG_PTR)pszBaseBackupFile;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileSaveRestoreOnINFW(struct qemu_syscall *call)
{
    struct qemu_FileSaveRestoreOnINFW *c = (struct qemu_FileSaveRestoreOnINFW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FileSaveRestoreOnINFW(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitle), QEMU_G2H(c->pszINF), QEMU_G2H(c->pszSection), QEMU_G2H(c->pszBackupDir), QEMU_G2H(c->pszBaseBackupFile), c->dwFlags);
}

#endif

struct qemu_GetVersionFromFileA
{
    struct qemu_syscall super;
    uint64_t Filename;
    uint64_t MajorVer;
    uint64_t MinorVer;
    uint64_t Version;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetVersionFromFileA(LPCSTR Filename, LPDWORD MajorVer, LPDWORD MinorVer, BOOL Version)
{
    struct qemu_GetVersionFromFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONFROMFILEA);
    call.Filename = (ULONG_PTR)Filename;
    call.MajorVer = (ULONG_PTR)MajorVer;
    call.MinorVer = (ULONG_PTR)MinorVer;
    call.Version = (ULONG_PTR)Version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVersionFromFileA(struct qemu_syscall *call)
{
    struct qemu_GetVersionFromFileA *c = (struct qemu_GetVersionFromFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetVersionFromFileA(QEMU_G2H(c->Filename), QEMU_G2H(c->MajorVer), QEMU_G2H(c->MinorVer), c->Version);
}

#endif

struct qemu_GetVersionFromFileW
{
    struct qemu_syscall super;
    uint64_t Filename;
    uint64_t MajorVer;
    uint64_t MinorVer;
    uint64_t Version;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetVersionFromFileW(LPCWSTR Filename, LPDWORD MajorVer, LPDWORD MinorVer, BOOL Version)
{
    struct qemu_GetVersionFromFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONFROMFILEW);
    call.Filename = (ULONG_PTR)Filename;
    call.MajorVer = (ULONG_PTR)MajorVer;
    call.MinorVer = (ULONG_PTR)MinorVer;
    call.Version = (ULONG_PTR)Version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVersionFromFileW(struct qemu_syscall *call)
{
    struct qemu_GetVersionFromFileW *c = (struct qemu_GetVersionFromFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetVersionFromFileW(QEMU_G2H(c->Filename), QEMU_G2H(c->MajorVer), QEMU_G2H(c->MinorVer), c->Version);
}

#endif

struct qemu_GetVersionFromFileExA
{
    struct qemu_syscall super;
    uint64_t lpszFilename;
    uint64_t pdwMSVer;
    uint64_t pdwLSVer;
    uint64_t bVersion;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetVersionFromFileExA(LPCSTR lpszFilename, LPDWORD pdwMSVer, LPDWORD pdwLSVer, BOOL bVersion)
{
    struct qemu_GetVersionFromFileExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONFROMFILEEXA);
    call.lpszFilename = (ULONG_PTR)lpszFilename;
    call.pdwMSVer = (ULONG_PTR)pdwMSVer;
    call.pdwLSVer = (ULONG_PTR)pdwLSVer;
    call.bVersion = (ULONG_PTR)bVersion;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVersionFromFileExA(struct qemu_syscall *call)
{
    struct qemu_GetVersionFromFileExA *c = (struct qemu_GetVersionFromFileExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetVersionFromFileExA(QEMU_G2H(c->lpszFilename), QEMU_G2H(c->pdwMSVer), QEMU_G2H(c->pdwLSVer), c->bVersion);
}

#endif

struct qemu_GetVersionFromFileExW
{
    struct qemu_syscall super;
    uint64_t lpszFilename;
    uint64_t pdwMSVer;
    uint64_t pdwLSVer;
    uint64_t bVersion;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetVersionFromFileExW(LPCWSTR lpszFilename, LPDWORD pdwMSVer, LPDWORD pdwLSVer, BOOL bVersion)
{
    struct qemu_GetVersionFromFileExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETVERSIONFROMFILEEXW);
    call.lpszFilename = (ULONG_PTR)lpszFilename;
    call.pdwMSVer = (ULONG_PTR)pdwMSVer;
    call.pdwLSVer = (ULONG_PTR)pdwLSVer;
    call.bVersion = (ULONG_PTR)bVersion;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetVersionFromFileExW(struct qemu_syscall *call)
{
    struct qemu_GetVersionFromFileExW *c = (struct qemu_GetVersionFromFileExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetVersionFromFileExW(QEMU_G2H(c->lpszFilename), QEMU_G2H(c->pdwMSVer), QEMU_G2H(c->pdwLSVer), c->bVersion);
}

#endif

