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

struct qemu_SHCreateShellItem
{
    struct qemu_syscall super;
    uint64_t pidlParent;
    uint64_t psfParent;
    uint64_t pidl;
    uint64_t ppsi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellItem(LPCITEMIDLIST pidlParent, IShellFolder *psfParent, LPCITEMIDLIST pidl, IShellItem **ppsi)
{
    struct qemu_SHCreateShellItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLITEM);
    call.pidlParent = (ULONG_PTR)pidlParent;
    call.psfParent = (ULONG_PTR)psfParent;
    call.pidl = (ULONG_PTR)pidl;
    call.ppsi = (ULONG_PTR)ppsi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellItem(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellItem *c = (struct qemu_SHCreateShellItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellItem(QEMU_G2H(c->pidlParent), QEMU_G2H(c->psfParent), QEMU_G2H(c->pidl), QEMU_G2H(c->ppsi));
}

#endif

struct qemu_SHCreateItemFromParsingName
{
    struct qemu_syscall super;
    uint64_t pszPath;
    uint64_t pbc;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateItemFromParsingName(PCWSTR pszPath, IBindCtx *pbc, REFIID riid, void **ppv)
{
    struct qemu_SHCreateItemFromParsingName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEITEMFROMPARSINGNAME);
    call.pszPath = (ULONG_PTR)pszPath;
    call.pbc = (ULONG_PTR)pbc;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateItemFromParsingName(struct qemu_syscall *call)
{
    struct qemu_SHCreateItemFromParsingName *c = (struct qemu_SHCreateItemFromParsingName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateItemFromParsingName(QEMU_G2H(c->pszPath), QEMU_G2H(c->pbc), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHCreateItemFromIDList
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateItemFromIDList(PCIDLIST_ABSOLUTE pidl, REFIID riid, void **ppv)
{
    struct qemu_SHCreateItemFromIDList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEITEMFROMIDLIST);
    call.pidl = (ULONG_PTR)pidl;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateItemFromIDList(struct qemu_syscall *call)
{
    struct qemu_SHCreateItemFromIDList *c = (struct qemu_SHCreateItemFromIDList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateItemFromIDList(QEMU_G2H(c->pidl), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHGetItemFromDataObject
{
    struct qemu_syscall super;
    uint64_t pdtobj;
    uint64_t dwFlags;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetItemFromDataObject(IDataObject *pdtobj, DATAOBJ_GET_ITEM_FLAGS dwFlags, REFIID riid, void **ppv)
{
    struct qemu_SHGetItemFromDataObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETITEMFROMDATAOBJECT);
    call.pdtobj = (ULONG_PTR)pdtobj;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetItemFromDataObject(struct qemu_syscall *call)
{
    struct qemu_SHGetItemFromDataObject *c = (struct qemu_SHGetItemFromDataObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetItemFromDataObject(QEMU_G2H(c->pdtobj), c->dwFlags, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHGetItemFromObject
{
    struct qemu_syscall super;
    uint64_t punk;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetItemFromObject(IUnknown *punk, REFIID riid, void **ppv)
{
    struct qemu_SHGetItemFromObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETITEMFROMOBJECT);
    call.punk = (ULONG_PTR)punk;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetItemFromObject(struct qemu_syscall *call)
{
    struct qemu_SHGetItemFromObject *c = (struct qemu_SHGetItemFromObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetItemFromObject(QEMU_G2H(c->punk), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHCreateShellItemArray
{
    struct qemu_syscall super;
    uint64_t pidlParent;
    uint64_t psf;
    uint64_t cidl;
    uint64_t ppidl;
    uint64_t ppsiItemArray;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellItemArray(PCIDLIST_ABSOLUTE pidlParent, IShellFolder *psf, UINT cidl, PCUITEMID_CHILD_ARRAY ppidl, IShellItemArray **ppsiItemArray)
{
    struct qemu_SHCreateShellItemArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLITEMARRAY);
    call.pidlParent = (ULONG_PTR)pidlParent;
    call.psf = (ULONG_PTR)psf;
    call.cidl = (ULONG_PTR)cidl;
    call.ppidl = (ULONG_PTR)ppidl;
    call.ppsiItemArray = (ULONG_PTR)ppsiItemArray;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellItemArray(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellItemArray *c = (struct qemu_SHCreateShellItemArray *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellItemArray(QEMU_G2H(c->pidlParent), QEMU_G2H(c->psf), c->cidl, QEMU_G2H(c->ppidl), QEMU_G2H(c->ppsiItemArray));
}

#endif

struct qemu_SHCreateShellItemArrayFromShellItem
{
    struct qemu_syscall super;
    uint64_t item;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellItemArrayFromShellItem(IShellItem *item, REFIID riid, void **ppv)
{
    struct qemu_SHCreateShellItemArrayFromShellItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLITEMARRAYFROMSHELLITEM);
    call.item = (ULONG_PTR)item;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellItemArrayFromShellItem(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellItemArrayFromShellItem *c = (struct qemu_SHCreateShellItemArrayFromShellItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellItemArrayFromShellItem(QEMU_G2H(c->item), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHCreateShellItemArrayFromDataObject
{
    struct qemu_syscall super;
    uint64_t pdo;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellItemArrayFromDataObject(IDataObject *pdo, REFIID riid, void **ppv)
{
    struct qemu_SHCreateShellItemArrayFromDataObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLITEMARRAYFROMDATAOBJECT);
    call.pdo = (ULONG_PTR)pdo;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellItemArrayFromDataObject(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellItemArrayFromDataObject *c = (struct qemu_SHCreateShellItemArrayFromDataObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellItemArrayFromDataObject(QEMU_G2H(c->pdo), QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_SHCreateShellItemArrayFromIDLists
{
    struct qemu_syscall super;
    uint64_t cidl;
    uint64_t pidl_array;
    uint64_t psia;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellItemArrayFromIDLists(UINT cidl, PCIDLIST_ABSOLUTE_ARRAY pidl_array, IShellItemArray **psia)
{
    struct qemu_SHCreateShellItemArrayFromIDLists call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLITEMARRAYFROMIDLISTS);
    call.cidl = (ULONG_PTR)cidl;
    call.pidl_array = (ULONG_PTR)pidl_array;
    call.psia = (ULONG_PTR)psia;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellItemArrayFromIDLists(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellItemArrayFromIDLists *c = (struct qemu_SHCreateShellItemArrayFromIDLists *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellItemArrayFromIDLists(c->cidl, QEMU_G2H(c->pidl_array), QEMU_G2H(c->psia));
}

#endif

struct qemu_SHGetPropertyStoreFromParsingName
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t pbc;
    uint64_t flags;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetPropertyStoreFromParsingName(const WCHAR *path, IBindCtx *pbc, GETPROPERTYSTOREFLAGS flags, REFIID riid, void **ppv)
{
    struct qemu_SHGetPropertyStoreFromParsingName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETPROPERTYSTOREFROMPARSINGNAME);
    call.path = (ULONG_PTR)path;
    call.pbc = (ULONG_PTR)pbc;
    call.flags = (ULONG_PTR)flags;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetPropertyStoreFromParsingName to Wine headers? */
extern HRESULT WINAPI SHGetPropertyStoreFromParsingName(const WCHAR *path, IBindCtx *pbc, GETPROPERTYSTOREFLAGS flags, REFIID riid, void **ppv);
void qemu_SHGetPropertyStoreFromParsingName(struct qemu_syscall *call)
{
    struct qemu_SHGetPropertyStoreFromParsingName *c = (struct qemu_SHGetPropertyStoreFromParsingName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetPropertyStoreFromParsingName(QEMU_G2H(c->path), QEMU_G2H(c->pbc), c->flags, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif
