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


struct qemu_SHCreateLinks
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t lpszDir;
    uint64_t lpDataObject;
    uint64_t uFlags;
    uint64_t lppidlLinks;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateLinks(HWND hWnd, LPCSTR lpszDir, LPDATAOBJECT lpDataObject, UINT uFlags, LPITEMIDLIST *lppidlLinks)
{
    struct qemu_SHCreateLinks call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATELINKS);
    call.hWnd = (uint64_t)hWnd;
    call.lpszDir = (uint64_t)lpszDir;
    call.lpDataObject = (uint64_t)lpDataObject;
    call.uFlags = (uint64_t)uFlags;
    call.lppidlLinks = (uint64_t)lppidlLinks;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHCreateLinks to Wine headers? */
extern HRESULT WINAPI SHCreateLinks(HWND hWnd, LPCSTR lpszDir, LPDATAOBJECT lpDataObject, UINT uFlags, LPITEMIDLIST *lppidlLinks);
void qemu_SHCreateLinks(struct qemu_syscall *call)
{
    struct qemu_SHCreateLinks *c = (struct qemu_SHCreateLinks *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateLinks(QEMU_G2H(c->hWnd), QEMU_G2H(c->lpszDir), QEMU_G2H(c->lpDataObject), c->uFlags, QEMU_G2H(c->lppidlLinks));
}

#endif

struct qemu_SHOpenFolderAndSelectItems
{
    struct qemu_syscall super;
    uint64_t pidlFolder;
    uint64_t cidl;
    uint64_t apidl;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHOpenFolderAndSelectItems(PCIDLIST_ABSOLUTE pidlFolder, UINT cidl, PCUITEMID_CHILD_ARRAY apidl, DWORD flags)
{
    struct qemu_SHOpenFolderAndSelectItems call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOPENFOLDERANDSELECTITEMS);
    call.pidlFolder = (uint64_t)pidlFolder;
    call.cidl = (uint64_t)cidl;
    call.apidl = (uint64_t)apidl;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHOpenFolderAndSelectItems to Wine headers? */
extern HRESULT WINAPI SHOpenFolderAndSelectItems(PCIDLIST_ABSOLUTE pidlFolder, UINT cidl, PCUITEMID_CHILD_ARRAY *apidl, DWORD flags);
void qemu_SHOpenFolderAndSelectItems(struct qemu_syscall *call)
{
    struct qemu_SHOpenFolderAndSelectItems *c = (struct qemu_SHOpenFolderAndSelectItems *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHOpenFolderAndSelectItems(QEMU_G2H(c->pidlFolder), c->cidl, QEMU_G2H(c->apidl), c->flags);
}

#endif

struct qemu_SHGetSetFolderCustomSettings
{
    struct qemu_syscall super;
    uint64_t fcs;
    uint64_t path;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetSetFolderCustomSettings(LPSHFOLDERCUSTOMSETTINGS fcs, LPCWSTR path, DWORD flag)
{
    struct qemu_SHGetSetFolderCustomSettings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSETFOLDERCUSTOMSETTINGS);
    call.fcs = (uint64_t)fcs;
    call.path = (uint64_t)path;
    call.flag = (uint64_t)flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetSetFolderCustomSettings(struct qemu_syscall *call)
{
    struct qemu_SHGetSetFolderCustomSettings *c = (struct qemu_SHGetSetFolderCustomSettings *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetSetFolderCustomSettings(QEMU_G2H(c->fcs), QEMU_G2H(c->path), c->flag);
}

#endif

struct qemu_SHLimitInputEdit
{
    struct qemu_syscall super;
    uint64_t textbox;
    uint64_t folder;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHLimitInputEdit(HWND textbox, IShellFolder *folder)
{
    struct qemu_SHLimitInputEdit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLIMITINPUTEDIT);
    call.textbox = (uint64_t)textbox;
    call.folder = (uint64_t)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHLimitInputEdit to Wine headers? */
extern HRESULT WINAPI SHLimitInputEdit(HWND textbox, IShellFolder *folder);
void qemu_SHLimitInputEdit(struct qemu_syscall *call)
{
    struct qemu_SHLimitInputEdit *c = (struct qemu_SHLimitInputEdit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHLimitInputEdit(QEMU_G2H(c->textbox), QEMU_G2H(c->folder));
}

#endif

