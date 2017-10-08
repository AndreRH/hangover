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


struct qemu_RegInstallA
{
    struct qemu_syscall super;
    uint64_t hm;
    uint64_t pszSection;
    uint64_t pstTable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegInstallA(HMODULE hm, LPCSTR pszSection, const STRTABLE* pstTable)
{
    struct qemu_RegInstallA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGINSTALLA);
    call.hm = (ULONG_PTR)hm;
    call.pszSection = (ULONG_PTR)pszSection;
    call.pstTable = (ULONG_PTR)pstTable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegInstallA(struct qemu_syscall *call)
{
    struct qemu_RegInstallA *c = (struct qemu_RegInstallA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegInstallA(QEMU_G2H(c->hm), QEMU_G2H(c->pszSection), QEMU_G2H(c->pstTable));
}

#endif

struct qemu_RegInstallW
{
    struct qemu_syscall super;
    uint64_t hm;
    uint64_t pszSection;
    uint64_t pstTable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegInstallW(HMODULE hm, LPCWSTR pszSection, const STRTABLE* pstTable)
{
    struct qemu_RegInstallW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGINSTALLW);
    call.hm = (ULONG_PTR)hm;
    call.pszSection = (ULONG_PTR)pszSection;
    call.pstTable = (ULONG_PTR)pstTable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegInstallW(struct qemu_syscall *call)
{
    struct qemu_RegInstallW *c = (struct qemu_RegInstallW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegInstallW(QEMU_G2H(c->hm), QEMU_G2H(c->pszSection), QEMU_G2H(c->pstTable));
}

#endif

struct qemu_RegRestoreAllA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitleString;
    uint64_t hkBackupKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegRestoreAllA(HWND hWnd, LPSTR pszTitleString, HKEY hkBackupKey)
{
    struct qemu_RegRestoreAllA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGRESTOREALLA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitleString = (ULONG_PTR)pszTitleString;
    call.hkBackupKey = (ULONG_PTR)hkBackupKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegRestoreAllA(struct qemu_syscall *call)
{
    struct qemu_RegRestoreAllA *c = (struct qemu_RegRestoreAllA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegRestoreAllA(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitleString), QEMU_G2H(c->hkBackupKey));
}

#endif

struct qemu_RegRestoreAllW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitleString;
    uint64_t hkBackupKey;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegRestoreAllW(HWND hWnd, LPWSTR pszTitleString, HKEY hkBackupKey)
{
    struct qemu_RegRestoreAllW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGRESTOREALLW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitleString = (ULONG_PTR)pszTitleString;
    call.hkBackupKey = (ULONG_PTR)hkBackupKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegRestoreAllW(struct qemu_syscall *call)
{
    struct qemu_RegRestoreAllW *c = (struct qemu_RegRestoreAllW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegRestoreAllW(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitleString), QEMU_G2H(c->hkBackupKey));
}

#endif

struct qemu_RegSaveRestoreA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitleString;
    uint64_t hkBackupKey;
    uint64_t pcszRootKey;
    uint64_t pcszSubKey;
    uint64_t pcszValueName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegSaveRestoreA(HWND hWnd, LPCSTR pszTitleString, HKEY hkBackupKey, LPCSTR pcszRootKey, LPCSTR pcszSubKey, LPCSTR pcszValueName, DWORD dwFlags)
{
    struct qemu_RegSaveRestoreA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVERESTOREA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitleString = (ULONG_PTR)pszTitleString;
    call.hkBackupKey = (ULONG_PTR)hkBackupKey;
    call.pcszRootKey = (ULONG_PTR)pcszRootKey;
    call.pcszSubKey = (ULONG_PTR)pcszSubKey;
    call.pcszValueName = (ULONG_PTR)pcszValueName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveRestoreA(struct qemu_syscall *call)
{
    struct qemu_RegSaveRestoreA *c = (struct qemu_RegSaveRestoreA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveRestoreA(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitleString), QEMU_G2H(c->hkBackupKey), QEMU_G2H(c->pcszRootKey), QEMU_G2H(c->pcszSubKey), QEMU_G2H(c->pcszValueName), c->dwFlags);
}

#endif

struct qemu_RegSaveRestoreW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitleString;
    uint64_t hkBackupKey;
    uint64_t pcszRootKey;
    uint64_t pcszSubKey;
    uint64_t pcszValueName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegSaveRestoreW(HWND hWnd, LPCWSTR pszTitleString, HKEY hkBackupKey, LPCWSTR pcszRootKey, LPCWSTR pcszSubKey, LPCWSTR pcszValueName, DWORD dwFlags)
{
    struct qemu_RegSaveRestoreW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVERESTOREW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitleString = (ULONG_PTR)pszTitleString;
    call.hkBackupKey = (ULONG_PTR)hkBackupKey;
    call.pcszRootKey = (ULONG_PTR)pcszRootKey;
    call.pcszSubKey = (ULONG_PTR)pcszSubKey;
    call.pcszValueName = (ULONG_PTR)pcszValueName;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveRestoreW(struct qemu_syscall *call)
{
    struct qemu_RegSaveRestoreW *c = (struct qemu_RegSaveRestoreW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveRestoreW(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitleString), QEMU_G2H(c->hkBackupKey), QEMU_G2H(c->pcszRootKey), QEMU_G2H(c->pcszSubKey), QEMU_G2H(c->pcszValueName), c->dwFlags);
}

#endif

struct qemu_RegSaveRestoreOnINFA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitle;
    uint64_t pszINF;
    uint64_t pszSection;
    uint64_t hHKLMBackKey;
    uint64_t hHKCUBackKey;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegSaveRestoreOnINFA(HWND hWnd, LPCSTR pszTitle, LPCSTR pszINF, LPCSTR pszSection, HKEY hHKLMBackKey, HKEY hHKCUBackKey, DWORD dwFlags)
{
    struct qemu_RegSaveRestoreOnINFA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVERESTOREONINFA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitle = (ULONG_PTR)pszTitle;
    call.pszINF = (ULONG_PTR)pszINF;
    call.pszSection = (ULONG_PTR)pszSection;
    call.hHKLMBackKey = (ULONG_PTR)hHKLMBackKey;
    call.hHKCUBackKey = (ULONG_PTR)hHKCUBackKey;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveRestoreOnINFA(struct qemu_syscall *call)
{
    struct qemu_RegSaveRestoreOnINFA *c = (struct qemu_RegSaveRestoreOnINFA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveRestoreOnINFA(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitle), QEMU_G2H(c->pszINF), QEMU_G2H(c->pszSection), QEMU_G2H(c->hHKLMBackKey), QEMU_G2H(c->hHKCUBackKey), c->dwFlags);
}

#endif

struct qemu_RegSaveRestoreOnINFW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t pszTitle;
    uint64_t pszINF;
    uint64_t pszSection;
    uint64_t hHKLMBackKey;
    uint64_t hHKCUBackKey;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegSaveRestoreOnINFW(HWND hWnd, LPCWSTR pszTitle, LPCWSTR pszINF, LPCWSTR pszSection, HKEY hHKLMBackKey, HKEY hHKCUBackKey, DWORD dwFlags)
{
    struct qemu_RegSaveRestoreOnINFW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGSAVERESTOREONINFW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.pszTitle = (ULONG_PTR)pszTitle;
    call.pszINF = (ULONG_PTR)pszINF;
    call.pszSection = (ULONG_PTR)pszSection;
    call.hHKLMBackKey = (ULONG_PTR)hHKLMBackKey;
    call.hHKCUBackKey = (ULONG_PTR)hHKCUBackKey;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegSaveRestoreOnINFW(struct qemu_syscall *call)
{
    struct qemu_RegSaveRestoreOnINFW *c = (struct qemu_RegSaveRestoreOnINFW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegSaveRestoreOnINFW(QEMU_G2H(c->hWnd), QEMU_G2H(c->pszTitle), QEMU_G2H(c->pszINF), QEMU_G2H(c->pszSection), QEMU_G2H(c->hHKLMBackKey), QEMU_G2H(c->hHKCUBackKey), c->dwFlags);
}

#endif

