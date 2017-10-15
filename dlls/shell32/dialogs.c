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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_PickIconDlg
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t path;
    uint64_t path_len;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI PickIconDlg(HWND hwndOwner, WCHAR *path, UINT path_len, INT *index)
{
    struct qemu_PickIconDlg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PICKICONDLG);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.path = (ULONG_PTR)path;
    call.path_len = path_len;
    call.index = (ULONG_PTR)index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PickIconDlg(struct qemu_syscall *call)
{
    struct qemu_PickIconDlg *c = (struct qemu_PickIconDlg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PickIconDlg(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->path), c->path_len, QEMU_G2H(c->index));
}

#endif

struct qemu_SHOpenWithDialog
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHOpenWithDialog(HWND parent, const OPENASINFO *info)
{
    struct qemu_SHOpenWithDialog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOPENWITHDIALOG);
    call.parent = (ULONG_PTR)parent;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHOpenWithDialog(struct qemu_syscall *call)
{
    struct qemu_SHOpenWithDialog *c = (struct qemu_SHOpenWithDialog *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHOpenWithDialog(QEMU_G2H(c->parent), QEMU_G2H(c->info));
}

#endif

struct qemu_RunFileDlgAW
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t hIcon;
    uint64_t lpstrDirectory;
    uint64_t lpstrTitle;
    uint64_t lpstrDescription;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RunFileDlgAW(HWND hwndOwner, HICON hIcon, LPCVOID lpstrDirectory, LPCVOID lpstrTitle, LPCVOID lpstrDescription, UINT uFlags)
{
    struct qemu_RunFileDlgAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RUNFILEDLGAW);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.hIcon = (ULONG_PTR)hIcon;
    call.lpstrDirectory = (ULONG_PTR)lpstrDirectory;
    call.lpstrTitle = (ULONG_PTR)lpstrTitle;
    call.lpstrDescription = (ULONG_PTR)lpstrDescription;
    call.uFlags = uFlags;

    qemu_syscall(&call.super);
}

#else

void qemu_RunFileDlgAW(struct qemu_syscall *call)
{
    struct qemu_RunFileDlgAW *c = (struct qemu_RunFileDlgAW *)call;
    WINE_FIXME("Unverified!\n");
    p_RunFileDlgAW(QEMU_G2H(c->hwndOwner), QEMU_G2H(c->hIcon), QEMU_G2H(c->lpstrDirectory), QEMU_G2H(c->lpstrTitle), QEMU_G2H(c->lpstrDescription), c->uFlags);
}

#endif

struct qemu_RestartDialogEx
{
    struct qemu_syscall super;
    uint64_t hWndOwner;
    uint64_t lpwstrReason;
    uint64_t uFlags;
    uint64_t uReason;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI RestartDialogEx(HWND hWndOwner, LPCWSTR lpwstrReason, DWORD uFlags, DWORD uReason)
{
    struct qemu_RestartDialogEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESTARTDIALOGEX);
    call.hWndOwner = (ULONG_PTR)hWndOwner;
    call.lpwstrReason = (ULONG_PTR)lpwstrReason;
    call.uFlags = uFlags;
    call.uReason = uReason;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RestartDialogEx(struct qemu_syscall *call)
{
    struct qemu_RestartDialogEx *c = (struct qemu_RestartDialogEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RestartDialogEx(QEMU_G2H(c->hWndOwner), QEMU_G2H(c->lpwstrReason), c->uFlags, c->uReason);
}

#endif

struct qemu_RestartDialog
{
    struct qemu_syscall super;
    uint64_t hWndOwner;
    uint64_t lpstrReason;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI RestartDialog(HWND hWndOwner, LPCWSTR lpstrReason, DWORD uFlags)
{
    struct qemu_RestartDialog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESTARTDIALOG);
    call.hWndOwner = (ULONG_PTR)hWndOwner;
    call.lpstrReason = (ULONG_PTR)lpstrReason;
    call.uFlags = uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RestartDialog(struct qemu_syscall *call)
{
    struct qemu_RestartDialog *c = (struct qemu_RestartDialog *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RestartDialog(QEMU_G2H(c->hWndOwner), QEMU_G2H(c->lpstrReason), c->uFlags);
}

#endif

struct qemu_ExitWindowsDialog
{
    struct qemu_syscall super;
    uint64_t hWndOwner;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ExitWindowsDialog (HWND hWndOwner)
{
    struct qemu_ExitWindowsDialog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXITWINDOWSDIALOG);
    call.hWndOwner = (ULONG_PTR)hWndOwner;

    qemu_syscall(&call.super);
}

#else

void qemu_ExitWindowsDialog(struct qemu_syscall *call)
{
    struct qemu_ExitWindowsDialog *c = (struct qemu_ExitWindowsDialog *)call;
    WINE_FIXME("Unverified!\n");
    p_ExitWindowsDialog(QEMU_G2H(c->hWndOwner));
}

#endif

