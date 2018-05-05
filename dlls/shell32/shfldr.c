/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger (for CodeWeavers)
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

#define COBJMACROS
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_IShellFolder2_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_shellfolder *impl_from_IShellFolder2(IShellFolder2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellfolder, IShellFolder2_iface);
}

static inline struct qemu_shellfolder *impl_from_IPersistFolder2( IPersistFolder2 *iface )
{
    return CONTAINING_RECORD(iface, struct qemu_shellfolder, IPersistFolder2_iface);
}

static HRESULT WINAPI qemu_shellfolder_QueryInterface(IShellFolder2 *iface, REFIID riid, void **obj)
{
    struct qemu_IShellFolder2_QueryInterface call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_QUERYINTERFACE);
    call.iface = (ULONG_PTR)folder;
    call.riid = (ULONG_PTR)riid;
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_QueryInterface *c = (struct qemu_IShellFolder2_QueryInterface *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_QueryInterface(folder->host_sf, QEMU_G2H(c->riid), QEMU_G2H(c->obj));
}

#endif

struct qemu_IShellFolder2_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_shellfolder_AddRef (IShellFolder2 *iface)
{
    struct qemu_IShellFolder2_AddRef call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_ADDREF);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_AddRef(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_AddRef *c = (struct qemu_IShellFolder2_AddRef *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_AddRef(folder->host_sf);
}

#endif

struct qemu_IShellFolder2_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_shellfolder_Release (IShellFolder2 *iface)
{
    struct qemu_IShellFolder2_Release call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_RELEASE);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_Release(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_Release *c = (struct qemu_IShellFolder2_Release *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_Release(folder->host_sf);
}

#endif

struct qemu_IShellFolder2_ParseDisplayName
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t pbc;
    uint64_t lpszDisplayName;
    uint64_t pchEaten;
    uint64_t ppidl;
    uint64_t pdwAttributes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_ParseDisplayName (IShellFolder2 *iface, HWND hwndOwner, LPBC pbc, LPOLESTR lpszDisplayName, DWORD * pchEaten, LPITEMIDLIST * ppidl, DWORD * pdwAttributes)
{
    struct qemu_IShellFolder2_ParseDisplayName call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_PARSEDISPLAYNAME);
    call.iface = (ULONG_PTR)folder;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.pbc = (ULONG_PTR)pbc;
    call.lpszDisplayName = (ULONG_PTR)lpszDisplayName;
    call.pchEaten = (ULONG_PTR)pchEaten;
    call.ppidl = (ULONG_PTR)ppidl;
    call.pdwAttributes = (ULONG_PTR)pdwAttributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_ParseDisplayName(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_ParseDisplayName *c = (struct qemu_IShellFolder2_ParseDisplayName *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_ParseDisplayName(folder->host_sf, QEMU_G2H(c->hwndOwner), QEMU_G2H(c->pbc), QEMU_G2H(c->lpszDisplayName), QEMU_G2H(c->pchEaten), QEMU_G2H(c->ppidl), QEMU_G2H(c->pdwAttributes));
}

#endif

struct qemu_IShellFolder2_EnumObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
    uint64_t ppEnumIDList;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_EnumObjects (IShellFolder2 *iface, HWND hwndOwner, DWORD dwFlags, LPENUMIDLIST * ppEnumIDList)
{
    struct qemu_IShellFolder2_EnumObjects call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_ENUMOBJECTS);
    call.iface = (ULONG_PTR)folder;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;
    call.ppEnumIDList = (ULONG_PTR)ppEnumIDList;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_EnumObjects(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_EnumObjects *c = (struct qemu_IShellFolder2_EnumObjects *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_EnumObjects(folder->host_sf, QEMU_G2H(c->hwndOwner), c->dwFlags, QEMU_G2H(c->ppEnumIDList));
}

#endif

struct qemu_IShellFolder2_BindToObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t pbcReserved;
    uint64_t riid;
    uint64_t ppvOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_BindToObject (IShellFolder2 *iface, LPCITEMIDLIST pidl, LPBC pbcReserved, REFIID riid, LPVOID * ppvOut)
{
    struct qemu_IShellFolder2_BindToObject call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_BINDTOOBJECT);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;
    call.pbcReserved = (ULONG_PTR)pbcReserved;
    call.riid = (ULONG_PTR)riid;
    call.ppvOut = (ULONG_PTR)ppvOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_BindToObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_BindToObject *c = (struct qemu_IShellFolder2_BindToObject *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_BindToObject(folder->host_sf, QEMU_G2H(c->pidl), QEMU_G2H(c->pbcReserved), QEMU_G2H(c->riid), QEMU_G2H(c->ppvOut));
}

#endif

struct qemu_IShellFolder2_BindToStorage
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t pbcReserved;
    uint64_t riid;
    uint64_t ppvOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_BindToStorage (IShellFolder2 *iface, LPCITEMIDLIST pidl, LPBC pbcReserved, REFIID riid, LPVOID * ppvOut)
{
    struct qemu_IShellFolder2_BindToStorage call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_BINDTOSTORAGE);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;
    call.pbcReserved = (ULONG_PTR)pbcReserved;
    call.riid = (ULONG_PTR)riid;
    call.ppvOut = (ULONG_PTR)ppvOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_BindToStorage(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_BindToStorage *c = (struct qemu_IShellFolder2_BindToStorage *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_BindToStorage(folder->host_sf, QEMU_G2H(c->pidl), QEMU_G2H(c->pbcReserved), QEMU_G2H(c->riid), QEMU_G2H(c->ppvOut));
}

#endif

struct qemu_IShellFolder2_CompareIDs
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lParam;
    uint64_t pidl1;
    uint64_t pidl2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_CompareIDs (IShellFolder2 *iface, LPARAM lParam, LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    struct qemu_IShellFolder2_CompareIDs call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_COMPAREIDS);
    call.iface = (ULONG_PTR)folder;
    call.lParam = lParam;
    call.pidl1 = (ULONG_PTR)pidl1;
    call.pidl2 = (ULONG_PTR)pidl2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_CompareIDs(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_CompareIDs *c = (struct qemu_IShellFolder2_CompareIDs *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_CompareIDs(folder->host_sf, c->lParam, QEMU_G2H(c->pidl1), QEMU_G2H(c->pidl2));
}

#endif

struct qemu_IShellFolder2_CreateViewObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t riid;
    uint64_t ppvOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_CreateViewObject (IShellFolder2 *iface, HWND hwndOwner, REFIID riid, LPVOID * ppvOut)
{
    struct qemu_IShellFolder2_CreateViewObject call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_CREATEVIEWOBJECT);
    call.iface = (ULONG_PTR)folder;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.riid = (ULONG_PTR)riid;
    call.ppvOut = (ULONG_PTR)ppvOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_CreateViewObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_CreateViewObject *c = (struct qemu_IShellFolder2_CreateViewObject *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_CreateViewObject(folder->host_sf, QEMU_G2H(c->hwndOwner), QEMU_G2H(c->riid), QEMU_G2H(c->ppvOut));
}

#endif

struct qemu_IShellFolder2_GetAttributesOf
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cidl;
    uint64_t apidl;
    uint64_t rgfInOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetAttributesOf (IShellFolder2 *iface, UINT cidl, LPCITEMIDLIST * apidl, DWORD * rgfInOut)
{
    struct qemu_IShellFolder2_GetAttributesOf call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETATTRIBUTESOF);
    call.iface = (ULONG_PTR)folder;
    call.cidl = cidl;
    call.apidl = (ULONG_PTR)apidl;
    call.rgfInOut = (ULONG_PTR)rgfInOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetAttributesOf(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetAttributesOf *c = (struct qemu_IShellFolder2_GetAttributesOf *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetAttributesOf(folder->host_sf, c->cidl, QEMU_G2H(c->apidl), QEMU_G2H(c->rgfInOut));
}

#endif

struct qemu_IShellFolder2_GetUIObjectOf
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t cidl;
    uint64_t apidl;
    uint64_t riid;
    uint64_t prgfInOut;
    uint64_t ppvOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetUIObjectOf (IShellFolder2 *iface, HWND hwndOwner, UINT cidl, LPCITEMIDLIST * apidl, REFIID riid, UINT * prgfInOut, LPVOID * ppvOut)
{
    struct qemu_IShellFolder2_GetUIObjectOf call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETUIOBJECTOF);
    call.iface = (ULONG_PTR)folder;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.cidl = cidl;
    call.apidl = (ULONG_PTR)apidl;
    call.riid = (ULONG_PTR)riid;
    call.prgfInOut = (ULONG_PTR)prgfInOut;
    call.ppvOut = (ULONG_PTR)ppvOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetUIObjectOf(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetUIObjectOf *c = (struct qemu_IShellFolder2_GetUIObjectOf *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetUIObjectOf(folder->host_sf, QEMU_G2H(c->hwndOwner), c->cidl, QEMU_G2H(c->apidl), QEMU_G2H(c->riid), QEMU_G2H(c->prgfInOut), QEMU_G2H(c->ppvOut));
}

#endif

struct qemu_IShellFolder2_GetDisplayNameOf
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t dwFlags;
    uint64_t strRet;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetDisplayNameOf (IShellFolder2 *iface, LPCITEMIDLIST pidl, DWORD dwFlags, LPSTRRET strRet)
{
    struct qemu_IShellFolder2_GetDisplayNameOf call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETDISPLAYNAMEOF);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;
    call.dwFlags = dwFlags;
    call.strRet = (ULONG_PTR)strRet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetDisplayNameOf(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetDisplayNameOf *c = (struct qemu_IShellFolder2_GetDisplayNameOf *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetDisplayNameOf(folder->host_sf, QEMU_G2H(c->pidl), c->dwFlags, QEMU_G2H(c->strRet));
}

#endif

struct qemu_IShellFolder2_SetNameOf
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t pidl;
    uint64_t lpName;
    uint64_t dwFlags;
    uint64_t pPidlOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_SetNameOf (IShellFolder2 *iface, HWND hwndOwner, LPCITEMIDLIST pidl, LPCOLESTR lpName, DWORD dwFlags, LPITEMIDLIST * pPidlOut)
{
    struct qemu_IShellFolder2_SetNameOf call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_SETNAMEOF);
    call.iface = (ULONG_PTR)folder;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.pidl = (ULONG_PTR)pidl;
    call.lpName = (ULONG_PTR)lpName;
    call.dwFlags = dwFlags;
    call.pPidlOut = (ULONG_PTR)pPidlOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_SetNameOf(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_SetNameOf *c = (struct qemu_IShellFolder2_SetNameOf *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_SetNameOf(folder->host_sf, QEMU_G2H(c->hwndOwner), QEMU_G2H(c->pidl), QEMU_G2H(c->lpName), c->dwFlags, QEMU_G2H(c->pPidlOut));
}

#endif

struct qemu_IShellFolder2_GetDefaultSearchGUID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetDefaultSearchGUID(IShellFolder2 *iface, GUID *guid)
{
    struct qemu_IShellFolder2_GetDefaultSearchGUID call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETDEFAULTSEARCHGUID);
    call.iface = (ULONG_PTR)folder;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetDefaultSearchGUID(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetDefaultSearchGUID *c = (struct qemu_IShellFolder2_GetDefaultSearchGUID *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetDefaultSearchGUID(folder->host_sf, QEMU_G2H(c->guid));
}

#endif

struct qemu_IShellFolder2_EnumSearches
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppenum;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_EnumSearches (IShellFolder2 *iface, IEnumExtraSearch ** ppenum)
{
    struct qemu_IShellFolder2_EnumSearches call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_ENUMSEARCHES);
    call.iface = (ULONG_PTR)folder;
    call.ppenum = (ULONG_PTR)ppenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_EnumSearches(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_EnumSearches *c = (struct qemu_IShellFolder2_EnumSearches *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_EnumSearches(folder->host_sf, QEMU_G2H(c->ppenum));
}

#endif

struct qemu_IShellFolder2_GetDefaultColumn
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reserved;
    uint64_t sort;
    uint64_t display;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetDefaultColumn(IShellFolder2 *iface, DWORD reserved, ULONG *sort, ULONG *display)
{
    struct qemu_IShellFolder2_GetDefaultColumn call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETDEFAULTCOLUMN);
    call.iface = (ULONG_PTR)folder;
    call.reserved = reserved;
    call.sort = (ULONG_PTR)sort;
    call.display = (ULONG_PTR)display;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetDefaultColumn(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetDefaultColumn *c = (struct qemu_IShellFolder2_GetDefaultColumn *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetDefaultColumn(folder->host_sf, c->reserved, QEMU_G2H(c->sort), QEMU_G2H(c->display));
}

#endif

struct qemu_IShellFolder2_GetDefaultColumnState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iColumn;
    uint64_t pcsFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetDefaultColumnState (IShellFolder2 *iface, UINT iColumn, DWORD * pcsFlags)
{
    struct qemu_IShellFolder2_GetDefaultColumnState call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETDEFAULTCOLUMNSTATE);
    call.iface = (ULONG_PTR)folder;
    call.iColumn = iColumn;
    call.pcsFlags = (ULONG_PTR)pcsFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetDefaultColumnState(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetDefaultColumnState *c = (struct qemu_IShellFolder2_GetDefaultColumnState *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetDefaultColumnState(folder->host_sf, c->iColumn, QEMU_G2H(c->pcsFlags));
}

#endif

struct qemu_IShellFolder2_GetDetailsEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t pscid;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetDetailsEx (IShellFolder2 *iface, LPCITEMIDLIST pidl, const SHCOLUMNID * pscid, VARIANT * pv)
{
    struct qemu_IShellFolder2_GetDetailsEx call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETDETAILSEX);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;
    call.pscid = (ULONG_PTR)pscid;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetDetailsEx(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetDetailsEx *c = (struct qemu_IShellFolder2_GetDetailsEx *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetDetailsEx(folder->host_sf, QEMU_G2H(c->pidl), QEMU_G2H(c->pscid), QEMU_G2H(c->pv));
}

#endif

struct qemu_IShellFolder2_GetDetailsOf
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t iColumn;
    uint64_t psd;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_GetDetailsOf (IShellFolder2 *iface, LPCITEMIDLIST pidl, UINT iColumn, SHELLDETAILS * psd)
{
    struct qemu_IShellFolder2_GetDetailsOf call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_GETDETAILSOF);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;
    call.iColumn = iColumn;
    call.psd = (ULONG_PTR)psd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_GetDetailsOf(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_GetDetailsOf *c = (struct qemu_IShellFolder2_GetDetailsOf *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetDetailsOf(folder->host_sf, QEMU_G2H(c->pidl), c->iColumn, QEMU_G2H(c->psd));
}

#endif

struct qemu_IShellFolder2_MapColumnToSCID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t column;
    uint64_t scid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_MapColumnToSCID(IShellFolder2 *iface, UINT column, SHCOLUMNID *scid)
{
    struct qemu_IShellFolder2_MapColumnToSCID call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_MAPCOLUMNTOSCID);
    call.iface = (ULONG_PTR)folder;
    call.column = column;
    call.scid = (ULONG_PTR)scid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_MapColumnToSCID(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_MapColumnToSCID *c = (struct qemu_IShellFolder2_MapColumnToSCID *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_MapColumnToSCID(folder->host_sf, c->column, QEMU_G2H(c->scid));
}

#endif

struct qemu_IPersistFolder2_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_QueryInterface(IPersistFolder2 *iface, REFIID riid, LPVOID *ppvObj)
{
    struct qemu_IPersistFolder2_QueryInterface call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER2_QUERYINTERFACE);
    call.iface = (ULONG_PTR)folder;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder2_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder2_QueryInterface *c = (struct qemu_IPersistFolder2_QueryInterface *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder2_QueryInterface(folder->host_pf, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_IPersistFolder2_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_persistfolder_AddRef(IPersistFolder2 *iface)
{
    struct qemu_IPersistFolder2_AddRef call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER2_ADDREF);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder2_AddRef(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder2_AddRef *c = (struct qemu_IPersistFolder2_AddRef *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder2_AddRef(folder->host_pf);
}

#endif

struct qemu_IPersistFolder2_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_persistfolder_Release(IPersistFolder2 *iface)
{
    struct qemu_IPersistFolder2_Release call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER2_RELEASE);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder2_Release(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder2_Release *c = (struct qemu_IPersistFolder2_Release *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder2_Release(folder->host_pf);
}

#endif

struct qemu_IPersistFolder2_GetClassID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clsid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_GetClassID(IPersistFolder2 *iface, CLSID *clsid)
{
    struct qemu_IPersistFolder2_GetClassID call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER2_GETCLASSID);
    call.iface = (ULONG_PTR)folder;
    call.clsid = (ULONG_PTR)clsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder2_GetClassID(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder2_GetClassID *c = (struct qemu_IPersistFolder2_GetClassID *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder2_GetClassID(folder->host_pf, QEMU_G2H(c->clsid));
}

#endif

struct qemu_IPersistFolder2_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_Initialize(IPersistFolder2 *iface, LPCITEMIDLIST pidl)
{
    struct qemu_IPersistFolder2_Initialize call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER2_INITIALIZE);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder2_Initialize(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder2_Initialize *c = (struct qemu_IPersistFolder2_Initialize *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder2_Initialize(folder->host_pf, QEMU_G2H(c->pidl));
}

#endif

struct qemu_IPersistFolder2_GetCurFolder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppidl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_GetCurFolder(IPersistFolder2 *iface, LPITEMIDLIST *ppidl)
{
    struct qemu_IPersistFolder2_GetCurFolder call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER2_GETCURFOLDER);
    call.iface = (ULONG_PTR)folder;
    call.ppidl = (ULONG_PTR)ppidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder2_GetCurFolder(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder2_GetCurFolder *c = (struct qemu_IPersistFolder2_GetCurFolder *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder2_GetCurFolder(folder->host_pf, QEMU_G2H(c->ppidl));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IShellFolder2Vtbl vtbl_ShellFolder2 =
{
    qemu_shellfolder_QueryInterface,
    qemu_shellfolder_AddRef,
    qemu_shellfolder_Release,
    qemu_shellfolder_ParseDisplayName,
    qemu_shellfolder_EnumObjects,
    qemu_shellfolder_BindToObject,
    qemu_shellfolder_BindToStorage,
    qemu_shellfolder_CompareIDs,
    qemu_shellfolder_CreateViewObject,
    qemu_shellfolder_GetAttributesOf,
    qemu_shellfolder_GetUIObjectOf,
    qemu_shellfolder_GetDisplayNameOf,
    qemu_shellfolder_SetNameOf,
    /* ShellFolder2 */
    qemu_shellfolder_GetDefaultSearchGUID,
    qemu_shellfolder_EnumSearches,
    qemu_shellfolder_GetDefaultColumn,
    qemu_shellfolder_GetDefaultColumnState,
    qemu_shellfolder_GetDetailsEx,
    qemu_shellfolder_GetDetailsOf,
    qemu_shellfolder_MapColumnToSCID
};

static const IPersistFolder2Vtbl vtbl_PersistFolder2 =
{
    qemu_persistfolder_QueryInterface,
    qemu_persistfolder_AddRef,
    qemu_persistfolder_Release,
    qemu_persistfolder_GetClassID,
    qemu_persistfolder_Initialize,
    qemu_persistfolder_GetCurFolder
};

void qemu_shellfolder_guest_init(struct qemu_shellfolder *folder)
{
    folder->IShellFolder2_iface.lpVtbl = &vtbl_ShellFolder2;
    folder->IPersistFolder2_iface.lpVtbl = &vtbl_PersistFolder2;
}

#else

struct qemu_shellfolder *qemu_shellfolder_host_create(IShellFolder2 *host)
{
    struct qemu_shellfolder *folder;

    folder = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*folder));
    if (!folder)
        return NULL;

    folder->host_sf = host;
    IShellFolder2_QueryInterface(host, &IID_IPersistFolder2, (void **)&folder->host_pf);
    /* The wrapper does not have its own refcount, don't hold references to the inteface ourselves. */
    IPersistFolder2_Release(folder->host_pf);

    return folder;
}

#endif
