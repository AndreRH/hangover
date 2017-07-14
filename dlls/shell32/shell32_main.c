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
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_CommandLineToArgvW
{
    struct qemu_syscall super;
    uint64_t lpCmdline;
    uint64_t numargs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR* WINAPI CommandLineToArgvW(LPCWSTR lpCmdline, int* numargs)
{
    struct qemu_CommandLineToArgvW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMANDLINETOARGVW);
    call.lpCmdline = (uint64_t)lpCmdline;
    call.numargs = (uint64_t)numargs;

    qemu_syscall(&call.super);

    return (LPWSTR*)call.super.iret;
}

#else

void qemu_CommandLineToArgvW(struct qemu_syscall *call)
{
    struct qemu_CommandLineToArgvW *c = (struct qemu_CommandLineToArgvW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CommandLineToArgvW(QEMU_G2H(c->lpCmdline), QEMU_G2H(c->numargs));
}

#endif

struct qemu_SHGetFileInfoW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t dwFileAttributes;
    uint64_t psfi;
    uint64_t sizeofpsfi;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD_PTR WINAPI SHGetFileInfoW(LPCWSTR path,DWORD dwFileAttributes, SHFILEINFOW *psfi, UINT sizeofpsfi, UINT flags)
{
    struct qemu_SHGetFileInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFILEINFOW);
    call.path = (uint64_t)path;
    call.dwFileAttributes = (uint64_t)dwFileAttributes;
    call.psfi = (uint64_t)psfi;
    call.sizeofpsfi = (uint64_t)sizeofpsfi;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFileInfoW(struct qemu_syscall *call)
{
    struct qemu_SHGetFileInfoW *c = (struct qemu_SHGetFileInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetFileInfoW(QEMU_G2H(c->path), c->dwFileAttributes, QEMU_G2H(c->psfi), c->sizeofpsfi, c->flags);
}

#endif

struct qemu_SHGetFileInfoA
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t dwFileAttributes;
    uint64_t psfi;
    uint64_t sizeofpsfi;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD_PTR WINAPI SHGetFileInfoA(LPCSTR path,DWORD dwFileAttributes, SHFILEINFOA *psfi, UINT sizeofpsfi, UINT flags)
{
    struct qemu_SHGetFileInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETFILEINFOA);
    call.path = (uint64_t)path;
    call.dwFileAttributes = (uint64_t)dwFileAttributes;
    call.psfi = (uint64_t)psfi;
    call.sizeofpsfi = (uint64_t)sizeofpsfi;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetFileInfoA(struct qemu_syscall *call)
{
    struct qemu_SHGetFileInfoA *c = (struct qemu_SHGetFileInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetFileInfoA(QEMU_G2H(c->path), c->dwFileAttributes, QEMU_G2H(c->psfi), c->sizeofpsfi, c->flags);
}

#endif

struct qemu_DuplicateIcon
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t hIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI DuplicateIcon(HINSTANCE hInstance, HICON hIcon)
{
    struct qemu_DuplicateIcon call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DUPLICATEICON);
    call.hInstance = (uint64_t)hInstance;
    call.hIcon = (uint64_t)hIcon;

    qemu_syscall(&call.super);

    return (HICON)call.super.iret;
}

#else

/* TODO: Add DuplicateIcon to Wine headers? */
extern HICON WINAPI DuplicateIcon(HINSTANCE hInstance, HICON hIcon);
void qemu_DuplicateIcon(struct qemu_syscall *call)
{
    struct qemu_DuplicateIcon *c = (struct qemu_DuplicateIcon *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)DuplicateIcon(QEMU_G2H(c->hInstance), QEMU_G2H(c->hIcon));
}

#endif

struct qemu_ExtractIconA
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t file;
    uint64_t nIconIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ExtractIconA(HINSTANCE hInstance, const char *file, UINT nIconIndex)
{
    struct qemu_ExtractIconA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTICONA);
    call.hInstance = (uint64_t)hInstance;
    call.file = (uint64_t)file;
    call.nIconIndex = (uint64_t)nIconIndex;

    qemu_syscall(&call.super);

    return (HICON)call.super.iret;
}

#else

void qemu_ExtractIconA(struct qemu_syscall *call)
{
    struct qemu_ExtractIconA *c = (struct qemu_ExtractIconA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ExtractIconA(QEMU_G2H(c->hInstance), QEMU_G2H(c->file), c->nIconIndex);
}

#endif

struct qemu_ExtractIconW
{
    struct qemu_syscall super;
    uint64_t hInstance;
    uint64_t lpszFile;
    uint64_t nIconIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ExtractIconW(HINSTANCE hInstance, LPCWSTR lpszFile, UINT nIconIndex)
{
    struct qemu_ExtractIconW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTICONW);
    call.hInstance = (uint64_t)hInstance;
    call.lpszFile = (uint64_t)lpszFile;
    call.nIconIndex = (uint64_t)nIconIndex;

    qemu_syscall(&call.super);

    return (HICON)call.super.iret;
}

#else

void qemu_ExtractIconW(struct qemu_syscall *call)
{
    struct qemu_ExtractIconW *c = (struct qemu_ExtractIconW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ExtractIconW(QEMU_G2H(c->hInstance), QEMU_G2H(c->lpszFile), c->nIconIndex);
}

#endif

struct qemu_SHCreateFileExtractIconW
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t attribs;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateFileExtractIconW(LPCWSTR file, DWORD attribs, REFIID riid, void **ppv)
{
    struct qemu_SHCreateFileExtractIconW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEFILEEXTRACTICONW);
    call.file = (uint64_t)file;
    call.attribs = (uint64_t)attribs;
    call.riid = (uint64_t)riid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHCreateFileExtractIconW to Wine headers? */
extern HRESULT WINAPI SHCreateFileExtractIconW(LPCWSTR file, DWORD attribs, REFIID riid, void **ppv);
void qemu_SHCreateFileExtractIconW(struct qemu_syscall *call)
{
    struct qemu_SHCreateFileExtractIconW *c = (struct qemu_SHCreateFileExtractIconW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateFileExtractIconW(QEMU_G2H(c->file), c->attribs, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_Printer_LoadIconsW
{
    struct qemu_syscall super;
    uint64_t wsPrinterName;
    uint64_t pLargeIcon;
    uint64_t pSmallIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI Printer_LoadIconsW(LPCWSTR wsPrinterName, HICON * pLargeIcon, HICON * pSmallIcon)
{
    struct qemu_Printer_LoadIconsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTER_LOADICONSW);
    call.wsPrinterName = (uint64_t)wsPrinterName;
    call.pLargeIcon = (uint64_t)pLargeIcon;
    call.pSmallIcon = (uint64_t)pSmallIcon;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add Printer_LoadIconsW to Wine headers? */
extern VOID WINAPI Printer_LoadIconsW(LPCWSTR wsPrinterName, HICON * pLargeIcon, HICON * pSmallIcon);
void qemu_Printer_LoadIconsW(struct qemu_syscall *call)
{
    struct qemu_Printer_LoadIconsW *c = (struct qemu_Printer_LoadIconsW *)call;
    WINE_FIXME("Unverified!\n");
    Printer_LoadIconsW(QEMU_G2H(c->wsPrinterName), QEMU_G2H(c->pLargeIcon), QEMU_G2H(c->pSmallIcon));
}

#endif

struct qemu_Printers_RegisterWindowW
{
    struct qemu_syscall super;
    uint64_t wsPrinter;
    uint64_t dwType;
    uint64_t phClassPidl;
    uint64_t phwnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Printers_RegisterWindowW(LPCWSTR wsPrinter, DWORD dwType, HANDLE * phClassPidl, HWND * phwnd)
{
    struct qemu_Printers_RegisterWindowW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTERS_REGISTERWINDOWW);
    call.wsPrinter = (uint64_t)wsPrinter;
    call.dwType = (uint64_t)dwType;
    call.phClassPidl = (uint64_t)phClassPidl;
    call.phwnd = (uint64_t)phwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add Printers_RegisterWindowW to Wine headers? */
extern BOOL WINAPI Printers_RegisterWindowW(LPCWSTR wsPrinter, DWORD dwType, HANDLE * phClassPidl, HWND * phwnd);
void qemu_Printers_RegisterWindowW(struct qemu_syscall *call)
{
    struct qemu_Printers_RegisterWindowW *c = (struct qemu_Printers_RegisterWindowW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Printers_RegisterWindowW(QEMU_G2H(c->wsPrinter), c->dwType, QEMU_G2H(c->phClassPidl), QEMU_G2H(c->phwnd));
}

#endif

struct qemu_Printers_UnregisterWindow
{
    struct qemu_syscall super;
    uint64_t hClassPidl;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI Printers_UnregisterWindow(HANDLE hClassPidl, HWND hwnd)
{
    struct qemu_Printers_UnregisterWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTERS_UNREGISTERWINDOW);
    call.hClassPidl = (uint64_t)hClassPidl;
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add Printers_UnregisterWindow to Wine headers? */
extern VOID WINAPI Printers_UnregisterWindow(HANDLE hClassPidl, HWND hwnd);
void qemu_Printers_UnregisterWindow(struct qemu_syscall *call)
{
    struct qemu_Printers_UnregisterWindow *c = (struct qemu_Printers_UnregisterWindow *)call;
    WINE_FIXME("Unverified!\n");
    Printers_UnregisterWindow(QEMU_G2H(c->hClassPidl), QEMU_G2H(c->hwnd));
}

#endif

struct qemu_SHGetPropertyStoreForWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetPropertyStoreForWindow(HWND hwnd, REFIID riid, void **ppv)
{
    struct qemu_SHGetPropertyStoreForWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETPROPERTYSTOREFORWINDOW);
    call.hwnd = (uint64_t)hwnd;
    call.riid = (uint64_t)riid;
    call.ppv = (uint64_t)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetPropertyStoreForWindow(struct qemu_syscall *call)
{
    struct qemu_SHGetPropertyStoreForWindow *c = (struct qemu_SHGetPropertyStoreForWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetPropertyStoreForWindow(QEMU_G2H(c->hwnd), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHHelpShortcuts_RunDLLA
{
    struct qemu_syscall super;
    uint64_t dwArg1;
    uint64_t dwArg2;
    uint64_t dwArg3;
    uint64_t dwArg4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHHelpShortcuts_RunDLLA(DWORD dwArg1, DWORD dwArg2, DWORD dwArg3, DWORD dwArg4)
{
    struct qemu_SHHelpShortcuts_RunDLLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHHELPSHORTCUTS_RUNDLLA);
    call.dwArg1 = (uint64_t)dwArg1;
    call.dwArg2 = (uint64_t)dwArg2;
    call.dwArg3 = (uint64_t)dwArg3;
    call.dwArg4 = (uint64_t)dwArg4;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHHelpShortcuts_RunDLLA to Wine headers? */
extern DWORD WINAPI SHHelpShortcuts_RunDLLA(DWORD dwArg1, DWORD dwArg2, DWORD dwArg3, DWORD dwArg4);
void qemu_SHHelpShortcuts_RunDLLA(struct qemu_syscall *call)
{
    struct qemu_SHHelpShortcuts_RunDLLA *c = (struct qemu_SHHelpShortcuts_RunDLLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHHelpShortcuts_RunDLLA(c->dwArg1, c->dwArg2, c->dwArg3, c->dwArg4);
}

#endif

struct qemu_SHHelpShortcuts_RunDLLW
{
    struct qemu_syscall super;
    uint64_t dwArg1;
    uint64_t dwArg2;
    uint64_t dwArg3;
    uint64_t dwArg4;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHHelpShortcuts_RunDLLW(DWORD dwArg1, DWORD dwArg2, DWORD dwArg3, DWORD dwArg4)
{
    struct qemu_SHHelpShortcuts_RunDLLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHHELPSHORTCUTS_RUNDLLW);
    call.dwArg1 = (uint64_t)dwArg1;
    call.dwArg2 = (uint64_t)dwArg2;
    call.dwArg3 = (uint64_t)dwArg3;
    call.dwArg4 = (uint64_t)dwArg4;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHHelpShortcuts_RunDLLW to Wine headers? */
extern DWORD WINAPI SHHelpShortcuts_RunDLLW(DWORD dwArg1, DWORD dwArg2, DWORD dwArg3, DWORD dwArg4);
void qemu_SHHelpShortcuts_RunDLLW(struct qemu_syscall *call)
{
    struct qemu_SHHelpShortcuts_RunDLLW *c = (struct qemu_SHHelpShortcuts_RunDLLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHHelpShortcuts_RunDLLW(c->dwArg1, c->dwArg2, c->dwArg3, c->dwArg4);
}

#endif

struct qemu_SHLoadInProc
{
    struct qemu_syscall super;
    uint64_t rclsid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHLoadInProc (REFCLSID rclsid)
{
    struct qemu_SHLoadInProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLOADINPROC);
    call.rclsid = (uint64_t)rclsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHLoadInProc to Wine headers? */
extern HRESULT WINAPI SHLoadInProc (REFCLSID rclsid);
void qemu_SHLoadInProc(struct qemu_syscall *call)
{
    struct qemu_SHLoadInProc *c = (struct qemu_SHLoadInProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHLoadInProc(QEMU_G2H(c->rclsid));
}

#endif

struct qemu_ShellAboutA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t szApp;
    uint64_t szOtherStuff;
    uint64_t hIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ShellAboutA(HWND hWnd, LPCSTR szApp, LPCSTR szOtherStuff, HICON hIcon)
{
    struct qemu_ShellAboutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLABOUTA);
    call.hWnd = (uint64_t)hWnd;
    call.szApp = (uint64_t)szApp;
    call.szOtherStuff = (uint64_t)szOtherStuff;
    call.hIcon = (uint64_t)hIcon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShellAboutA(struct qemu_syscall *call)
{
    struct qemu_ShellAboutA *c = (struct qemu_ShellAboutA *)call;
    WINE_TRACE("\n");
    c->super.iret = ShellAboutA(QEMU_G2H(c->hWnd), QEMU_G2H(c->szApp), QEMU_G2H(c->szOtherStuff), QEMU_G2H(c->hIcon));
}

#endif

struct qemu_ShellAboutW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t szApp;
    uint64_t szOtherStuff;
    uint64_t hIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ShellAboutW(HWND hWnd, LPCWSTR szApp, LPCWSTR szOtherStuff, HICON hIcon)
{
    struct qemu_ShellAboutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLABOUTW);
    call.hWnd = (uint64_t)hWnd;
    call.szApp = (uint64_t)szApp;
    call.szOtherStuff = (uint64_t)szOtherStuff;
    call.hIcon = (uint64_t)hIcon;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ShellAboutW(struct qemu_syscall *call)
{
    struct qemu_ShellAboutW *c = (struct qemu_ShellAboutW *)call;
    WINE_TRACE("\n");
    c->super.iret = ShellAboutW(QEMU_G2H(c->hWnd), QEMU_G2H(c->szApp), QEMU_G2H(c->szOtherStuff), QEMU_G2H(c->hIcon));
}

#endif

struct qemu_FreeIconList
{
    struct qemu_syscall super;
    uint64_t dw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FreeIconList(DWORD dw)
{
    struct qemu_FreeIconList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEICONLIST);
    call.dw = (uint64_t)dw;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add FreeIconList to Wine headers? */
extern void WINAPI FreeIconList(DWORD dw);
void qemu_FreeIconList(struct qemu_syscall *call)
{
    struct qemu_FreeIconList *c = (struct qemu_FreeIconList *)call;
    WINE_FIXME("Unverified!\n");
    FreeIconList(c->dw);
}

#endif

struct qemu_SHLoadNonloadedIconOverlayIdentifiers
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHLoadNonloadedIconOverlayIdentifiers(VOID)
{
    struct qemu_SHLoadNonloadedIconOverlayIdentifiers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLOADNONLOADEDICONOVERLAYIDENTIFIERS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHLoadNonloadedIconOverlayIdentifiers to Wine headers? */
extern HRESULT WINAPI SHLoadNonloadedIconOverlayIdentifiers(VOID);
void qemu_SHLoadNonloadedIconOverlayIdentifiers(struct qemu_syscall *call)
{
    struct qemu_SHLoadNonloadedIconOverlayIdentifiers *c = (struct qemu_SHLoadNonloadedIconOverlayIdentifiers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHLoadNonloadedIconOverlayIdentifiers();
}

#endif

struct qemu_DllGetVersion
{
    struct qemu_syscall super;
    uint64_t pdvi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetVersion (DLLVERSIONINFO *pdvi)
{
    struct qemu_DllGetVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLGETVERSION);
    call.pdvi = (uint64_t)pdvi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DllGetVersion to Wine headers? */
extern HRESULT WINAPI DllGetVersion (DLLVERSIONINFO *pdvi);
void qemu_DllGetVersion(struct qemu_syscall *call)
{
    struct qemu_DllGetVersion *c = (struct qemu_DllGetVersion *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = E_FAIL;
}

#endif

struct qemu_DllInstall
{
    struct qemu_syscall super;
    uint64_t bInstall;
    uint64_t cmdline;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllInstall(BOOL bInstall, LPCWSTR cmdline)
{
    struct qemu_DllInstall call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLINSTALL);
    call.bInstall = (uint64_t)bInstall;
    call.cmdline = (uint64_t)cmdline;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DllInstall to Wine headers? */
extern HRESULT WINAPI DllInstall(BOOL bInstall, LPCWSTR cmdline);
void qemu_DllInstall(struct qemu_syscall *call)
{
    struct qemu_DllInstall *c = (struct qemu_DllInstall *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = E_FAIL;
}

#endif

struct qemu_DllCanUnloadNow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllCanUnloadNow(void)
{
    struct qemu_DllCanUnloadNow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLCANUNLOADNOW);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllCanUnloadNow(struct qemu_syscall *call)
{
    struct qemu_DllCanUnloadNow *c = (struct qemu_DllCanUnloadNow *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = FALSE;
}

#endif

struct qemu_DllRegisterServer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllRegisterServer(void)
{
    struct qemu_DllRegisterServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLREGISTERSERVER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DllRegisterServer to Wine headers? */
extern HRESULT WINAPI DllRegisterServer(void);
void qemu_DllRegisterServer(struct qemu_syscall *call)
{
    struct qemu_DllRegisterServer *c = (struct qemu_DllRegisterServer *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = FALSE;
}

#endif

struct qemu_DllUnregisterServer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllUnregisterServer(void)
{
    struct qemu_DllUnregisterServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLUNREGISTERSERVER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DllUnregisterServer to Wine headers? */
extern HRESULT WINAPI DllUnregisterServer(void);
void qemu_DllUnregisterServer(struct qemu_syscall *call)
{
    struct qemu_DllUnregisterServer *c = (struct qemu_DllUnregisterServer *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = FALSE;
}

#endif

struct qemu_ExtractVersionResource16W
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ExtractVersionResource16W(LPWSTR s, DWORD d)
{
    struct qemu_ExtractVersionResource16W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTVERSIONRESOURCE16W);
    call.s = (uint64_t)s;
    call.d = (uint64_t)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ExtractVersionResource16W to Wine headers? */
extern BOOL WINAPI ExtractVersionResource16W(LPWSTR s, DWORD d);
void qemu_ExtractVersionResource16W(struct qemu_syscall *call)
{
    struct qemu_ExtractVersionResource16W *c = (struct qemu_ExtractVersionResource16W *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtractVersionResource16W(QEMU_G2H(c->s), c->d);
}

#endif

struct qemu_InitNetworkAddressControl
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitNetworkAddressControl(void)
{
    struct qemu_InitNetworkAddressControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITNETWORKADDRESSCONTROL);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InitNetworkAddressControl to Wine headers? */
extern BOOL WINAPI InitNetworkAddressControl(void);
void qemu_InitNetworkAddressControl(struct qemu_syscall *call)
{
    struct qemu_InitNetworkAddressControl *c = (struct qemu_InitNetworkAddressControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitNetworkAddressControl();
}

#endif

struct qemu_SHGetLocalizedName
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t module;
    uint64_t size;
    uint64_t res;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetLocalizedName(LPCWSTR path, LPWSTR module, UINT size, INT *res)
{
    struct qemu_SHGetLocalizedName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETLOCALIZEDNAME);
    call.path = (uint64_t)path;
    call.module = (uint64_t)module;
    call.size = (uint64_t)size;
    call.res = (uint64_t)res;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetLocalizedName to Wine headers? */
extern HRESULT WINAPI SHGetLocalizedName(LPCWSTR path, LPWSTR module, UINT size, INT *res);
void qemu_SHGetLocalizedName(struct qemu_syscall *call)
{
    struct qemu_SHGetLocalizedName *c = (struct qemu_SHGetLocalizedName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetLocalizedName(QEMU_G2H(c->path), QEMU_G2H(c->module), c->size, QEMU_G2H(c->res));
}

#endif

struct qemu_SetCurrentProcessExplicitAppUserModelID
{
    struct qemu_syscall super;
    uint64_t appid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SetCurrentProcessExplicitAppUserModelID(PCWSTR appid)
{
    struct qemu_SetCurrentProcessExplicitAppUserModelID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCURRENTPROCESSEXPLICITAPPUSERMODELID);
    call.appid = (uint64_t)appid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetCurrentProcessExplicitAppUserModelID to Wine headers? */
extern HRESULT WINAPI SetCurrentProcessExplicitAppUserModelID(PCWSTR appid);
void qemu_SetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call)
{
    struct qemu_SetCurrentProcessExplicitAppUserModelID *c = (struct qemu_SetCurrentProcessExplicitAppUserModelID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCurrentProcessExplicitAppUserModelID(QEMU_G2H(c->appid));
}

#endif

struct qemu_GetCurrentProcessExplicitAppUserModelID
{
    struct qemu_syscall super;
    uint64_t appid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetCurrentProcessExplicitAppUserModelID(PWSTR *appid)
{
    struct qemu_GetCurrentProcessExplicitAppUserModelID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPROCESSEXPLICITAPPUSERMODELID);
    call.appid = (uint64_t)appid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetCurrentProcessExplicitAppUserModelID to Wine headers? */
extern HRESULT WINAPI GetCurrentProcessExplicitAppUserModelID(PWSTR *appid);
void qemu_GetCurrentProcessExplicitAppUserModelID(struct qemu_syscall *call)
{
    struct qemu_GetCurrentProcessExplicitAppUserModelID *c = (struct qemu_GetCurrentProcessExplicitAppUserModelID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentProcessExplicitAppUserModelID(QEMU_G2H(c->appid));
}

#endif

struct qemu_SHSetUnreadMailCountW
{
    struct qemu_syscall super;
    uint64_t mailaddress;
    uint64_t count;
    uint64_t executecommand;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHSetUnreadMailCountW(LPCWSTR mailaddress, DWORD count, LPCWSTR executecommand)
{
    struct qemu_SHSetUnreadMailCountW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSETUNREADMAILCOUNTW);
    call.mailaddress = (uint64_t)mailaddress;
    call.count = (uint64_t)count;
    call.executecommand = (uint64_t)executecommand;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHSetUnreadMailCountW to Wine headers? */
extern HRESULT WINAPI SHSetUnreadMailCountW(LPCWSTR mailaddress, DWORD count, LPCWSTR executecommand);
void qemu_SHSetUnreadMailCountW(struct qemu_syscall *call)
{
    struct qemu_SHSetUnreadMailCountW *c = (struct qemu_SHSetUnreadMailCountW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHSetUnreadMailCountW(QEMU_G2H(c->mailaddress), c->count, QEMU_G2H(c->executecommand));
}

#endif

struct qemu_SHEnumerateUnreadMailAccountsW
{
    struct qemu_syscall super;
    uint64_t user;
    uint64_t idx;
    uint64_t mailaddress;
    uint64_t mailaddresslen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHEnumerateUnreadMailAccountsW(HKEY user, DWORD idx, LPWSTR mailaddress, INT mailaddresslen)
{
    struct qemu_SHEnumerateUnreadMailAccountsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHENUMERATEUNREADMAILACCOUNTSW);
    call.user = (uint64_t)user;
    call.idx = (uint64_t)idx;
    call.mailaddress = (uint64_t)mailaddress;
    call.mailaddresslen = (uint64_t)mailaddresslen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHEnumerateUnreadMailAccountsW(struct qemu_syscall *call)
{
    struct qemu_SHEnumerateUnreadMailAccountsW *c = (struct qemu_SHEnumerateUnreadMailAccountsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHEnumerateUnreadMailAccountsW(QEMU_G2H(c->user), c->idx, QEMU_G2H(c->mailaddress), c->mailaddresslen);
}

#endif

struct qemu_SHQueryUserNotificationState
{
    struct qemu_syscall super;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

/* FIXME: Include shellapi.h and figure out the right defines. */
WINBASEAPI HRESULT WINAPI SHQueryUserNotificationState(void *state)
{
    struct qemu_SHQueryUserNotificationState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHQUERYUSERNOTIFICATIONSTATE);
    call.state = (uint64_t)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHQueryUserNotificationState(struct qemu_syscall *call)
{
    struct qemu_SHQueryUserNotificationState *c = (struct qemu_SHQueryUserNotificationState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHQueryUserNotificationState(QEMU_G2H(c->state));
}

#endif

