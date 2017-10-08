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

#ifdef QEMU_DLL_GUEST

typedef CABINFO CABINFOA, CABINFOW;

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advpack);

#endif

typedef struct _SETUPCOMMAND_PARAMS SETUPCOMMAND_PARAMS;

struct qemu_DoInfInstall
{
    struct qemu_syscall super;
    uint64_t setup;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DoInfInstall(const SETUPCOMMAND_PARAMS *setup)
{
    struct qemu_DoInfInstall call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOINFINSTALL);
    call.setup = (ULONG_PTR)setup;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DoInfInstall to Wine headers? */
extern HRESULT WINAPI DoInfInstall(const SETUPCOMMAND_PARAMS *setup);
void qemu_DoInfInstall(struct qemu_syscall *call)
{
    struct qemu_DoInfInstall *c = (struct qemu_DoInfInstall *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DoInfInstall(QEMU_G2H(c->setup));
}

#endif

struct qemu_ExecuteCabA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pCab;
    uint64_t pReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ExecuteCabA(HWND hwnd, CABINFOA* pCab, LPVOID pReserved)
{
    struct qemu_ExecuteCabA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXECUTECABA);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pCab = (ULONG_PTR)pCab;
    call.pReserved = (ULONG_PTR)pReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExecuteCabA(struct qemu_syscall *call)
{
    struct qemu_ExecuteCabA *c = (struct qemu_ExecuteCabA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExecuteCabA(QEMU_G2H(c->hwnd), QEMU_G2H(c->pCab), QEMU_G2H(c->pReserved));
}

#endif

struct qemu_ExecuteCabW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pCab;
    uint64_t pReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ExecuteCabW(HWND hwnd, CABINFOW* pCab, LPVOID pReserved)
{
    struct qemu_ExecuteCabW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXECUTECABW);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pCab = (ULONG_PTR)pCab;
    call.pReserved = (ULONG_PTR)pReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExecuteCabW(struct qemu_syscall *call)
{
    struct qemu_ExecuteCabW *c = (struct qemu_ExecuteCabW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExecuteCabW(QEMU_G2H(c->hwnd), QEMU_G2H(c->pCab), QEMU_G2H(c->pReserved));
}

#endif

struct qemu_LaunchINFSectionA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LaunchINFSectionA(HWND hWnd, HINSTANCE hInst, LPSTR cmdline, INT show)
{
    struct qemu_LaunchINFSectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LAUNCHINFSECTIONA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LaunchINFSectionA(struct qemu_syscall *call)
{
    struct qemu_LaunchINFSectionA *c = (struct qemu_LaunchINFSectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LaunchINFSectionA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_LaunchINFSectionW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LaunchINFSectionW(HWND hWnd, HINSTANCE hInst, LPWSTR cmdline, INT show)
{
    struct qemu_LaunchINFSectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LAUNCHINFSECTIONW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LaunchINFSectionW(struct qemu_syscall *call)
{
    struct qemu_LaunchINFSectionW *c = (struct qemu_LaunchINFSectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LaunchINFSectionW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_LaunchINFSectionExA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI LaunchINFSectionExA(HWND hWnd, HINSTANCE hInst, LPSTR cmdline, INT show)
{
    struct qemu_LaunchINFSectionExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LAUNCHINFSECTIONEXA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LaunchINFSectionExA(struct qemu_syscall *call)
{
    struct qemu_LaunchINFSectionExA *c = (struct qemu_LaunchINFSectionExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LaunchINFSectionExA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_LaunchINFSectionExW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t cmdline;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI LaunchINFSectionExW(HWND hWnd, HINSTANCE hInst, LPWSTR cmdline, INT show)
{
    struct qemu_LaunchINFSectionExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LAUNCHINFSECTIONEXW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.cmdline = (ULONG_PTR)cmdline;
    call.show = (ULONG_PTR)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LaunchINFSectionExW(struct qemu_syscall *call)
{
    struct qemu_LaunchINFSectionExW *c = (struct qemu_LaunchINFSectionExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LaunchINFSectionExW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->cmdline), c->show);
}

#endif

struct qemu_RunSetupCommandA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t szCmdName;
    uint64_t szInfSection;
    uint64_t szDir;
    uint64_t lpszTitle;
    uint64_t phEXE;
    uint64_t dwFlags;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RunSetupCommandA(HWND hWnd, LPCSTR szCmdName, LPCSTR szInfSection, LPCSTR szDir, LPCSTR lpszTitle, HANDLE *phEXE, DWORD dwFlags, LPVOID pvReserved)
{
    struct qemu_RunSetupCommandA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RUNSETUPCOMMANDA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.szCmdName = (ULONG_PTR)szCmdName;
    call.szInfSection = (ULONG_PTR)szInfSection;
    call.szDir = (ULONG_PTR)szDir;
    call.lpszTitle = (ULONG_PTR)lpszTitle;
    call.phEXE = (ULONG_PTR)phEXE;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RunSetupCommandA(struct qemu_syscall *call)
{
    struct qemu_RunSetupCommandA *c = (struct qemu_RunSetupCommandA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RunSetupCommandA(QEMU_G2H(c->hWnd), QEMU_G2H(c->szCmdName), QEMU_G2H(c->szInfSection), QEMU_G2H(c->szDir), QEMU_G2H(c->lpszTitle), QEMU_G2H(c->phEXE), c->dwFlags, QEMU_G2H(c->pvReserved));
}

#endif

struct qemu_RunSetupCommandW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t szCmdName;
    uint64_t szInfSection;
    uint64_t szDir;
    uint64_t lpszTitle;
    uint64_t phEXE;
    uint64_t dwFlags;
    uint64_t pvReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RunSetupCommandW(HWND hWnd, LPCWSTR szCmdName, LPCWSTR szInfSection, LPCWSTR szDir, LPCWSTR lpszTitle, HANDLE *phEXE, DWORD dwFlags, LPVOID pvReserved)
{
    struct qemu_RunSetupCommandW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RUNSETUPCOMMANDW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.szCmdName = (ULONG_PTR)szCmdName;
    call.szInfSection = (ULONG_PTR)szInfSection;
    call.szDir = (ULONG_PTR)szDir;
    call.lpszTitle = (ULONG_PTR)lpszTitle;
    call.phEXE = (ULONG_PTR)phEXE;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.pvReserved = (ULONG_PTR)pvReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RunSetupCommandW(struct qemu_syscall *call)
{
    struct qemu_RunSetupCommandW *c = (struct qemu_RunSetupCommandW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RunSetupCommandW(QEMU_G2H(c->hWnd), QEMU_G2H(c->szCmdName), QEMU_G2H(c->szInfSection), QEMU_G2H(c->szDir), QEMU_G2H(c->lpszTitle), QEMU_G2H(c->phEXE), c->dwFlags, QEMU_G2H(c->pvReserved));
}

#endif

