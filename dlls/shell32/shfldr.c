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

#include "thunk/qemu_shtypes.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"
#include "propertybag_wrapper.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_IShellFolder2_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_shellfolder *impl_from_IShellFolder2(IShellFolder2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellfolder, IShellFolder2_iface);
}

static inline struct qemu_shellfolder *impl_from_IPersistFolder3(IPersistFolder3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellfolder, IPersistFolder3_iface);
}

static inline struct qemu_shellfolder *impl_from_IPersistPropertyBag(IPersistPropertyBag *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellfolder, IPersistPropertyBag_iface);
}

static HRESULT WINAPI qemu_shellfolder_QueryInterface(IShellFolder2 *iface, const IID *iid, void **obj)
{
    struct qemu_IShellFolder2_QueryInterface call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_QUERYINTERFACE);
    call.iface = (ULONG_PTR)folder;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    if (IsEqualGUID(iid, &IID_IUnknown) || IsEqualGUID(iid, &IID_IShellFolder) || IsEqualGUID(iid, &IID_IShellFolder2))
    {
        *obj = &folder->IShellFolder2_iface;
    }
    else if (IsEqualGUID(iid, &IID_IPersistFolder) || IsEqualGUID(iid, &IID_IPersistFolder2))
    {
        *obj = &folder->IPersistFolder3_iface;
    }
    else if (IsEqualGUID(iid, &IID_IPersistFolder3) && folder->flags & SHELLFOLDER_HAS_PERSISTFOLDER3)
    {
        *obj = &folder->IPersistFolder3_iface;
    }
    else if (IsEqualGUID(iid, &IID_IPersistPropertyBag) && folder->flags & SHELLFOLDER_HAS_PROPERTYBAG)
    {
        *obj = &folder->IPersistPropertyBag_iface;
    }
    else if (SUCCEEDED(call.super.iret))
    {
        call.iface = 0;
        qemu_syscall(&call.super);
    }
    else
    {
        *obj = NULL;
    }

    /* AddRef is handled by the host QI call. */

    return call.super.iret;
}

#else

static struct qemu_shellfolder *shellfolder_desktop;

void qemu_IShellFolder2_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_QueryInterface *c = (struct qemu_IShellFolder2_QueryInterface *)call;
    struct qemu_shellfolder *folder;
    void *out;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    if (!folder)
    {
        WINE_FIXME("Host handled IID %s, but it is not handled by the wrapper.\n",
                wine_dbgstr_guid(QEMU_G2H(c->iid)));
        DebugBreak();
    }

    c->super.iret = IShellFolder2_QueryInterface(folder->host_sf, QEMU_G2H(c->iid), &out);
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

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_Release(folder->host_sf);
    if (!c->super.iret)
    {
        WINE_TRACE("Freeing Shell folder wrapper %p.\n", folder);
        if (folder == shellfolder_desktop)
            WINE_ERR("Destroying desktop wrapper.\n");
        HeapFree(GetProcessHeap(), 0, folder);
    }
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

static HRESULT WINAPI qemu_shellfolder_ParseDisplayName (IShellFolder2 *iface, HWND hwndOwner, LPBC pbc,
        LPOLESTR lpszDisplayName, DWORD *pchEaten, LPITEMIDLIST *ppidl, DWORD *pdwAttributes)
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
    if (ppidl)
        *ppidl = (ITEMIDLIST *)(ULONG_PTR)call.ppidl;

    return call.super.iret;
}

#else

void qemu_IShellFolder2_ParseDisplayName(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_ParseDisplayName *c = (struct qemu_IShellFolder2_ParseDisplayName *)call;
    struct qemu_shellfolder *folder;
    ITEMIDLIST *list;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);
    if (c->pbc)
        WINE_FIXME("Bind Context not handled yet.\n");

    c->super.iret = IShellFolder2_ParseDisplayName(folder->host_sf, QEMU_G2H(c->hwndOwner), QEMU_G2H(c->pbc),
            QEMU_G2H(c->lpszDisplayName), QEMU_G2H(c->pchEaten), c->ppidl ? &list : NULL, QEMU_G2H(c->pdwAttributes));
    c->ppidl = QEMU_H2G(list);
}

#endif

struct qemu_IShellFolder2_EnumObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_EnumObjects (IShellFolder2 *iface, HWND hwndOwner, DWORD dwFlags,
        IEnumIDList **list)
{
    struct qemu_IShellFolder2_EnumObjects call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);
    struct qemu_enumidlist *list_obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_ENUMOBJECTS);
    call.iface = (ULONG_PTR)folder;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;
    call.list = (ULONG_PTR)list;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        list_obj = (struct qemu_enumidlist *)(ULONG_PTR)call.list;
        qemu_enumidlist_guest_init(list_obj);
        *list = &list_obj->IEnumIDList_iface;
    }

    return call.super.iret;
}

#else

void qemu_IShellFolder2_EnumObjects(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_EnumObjects *c = (struct qemu_IShellFolder2_EnumObjects *)call;
    struct qemu_shellfolder *folder;
    struct qemu_enumidlist *list;
    IEnumIDList *host_list;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_EnumObjects(folder->host_sf, QEMU_G2H(c->hwndOwner), c->dwFlags,
            c->list ? &host_list : NULL);
    if (FAILED(c->super.iret))
        return;

    list = qemu_enumidlist_host_create(host_list);
    if (!list)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->list = QEMU_H2G(list);
}

#endif

struct qemu_IShellFolder2_BindToObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t pbcReserved;
    uint64_t iid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_BindToObject (IShellFolder2 *iface, LPCITEMIDLIST pidl, LPBC pbcReserved,
        const IID *iid, void **out)
{
    struct qemu_IShellFolder2_BindToObject call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_BINDTOOBJECT);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;
    call.pbcReserved = (ULONG_PTR)pbcReserved;
    call.iid = (ULONG_PTR)iid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        struct qemu_shellfolder *retobj = (struct qemu_shellfolder *)(ULONG_PTR)call.out;
        qemu_shellfolder_guest_init(retobj);
        IShellFolder2_QueryInterface(&retobj->IShellFolder2_iface, iid, out);
        IShellFolder2_Release(&retobj->IShellFolder2_iface);
    }

    return call.super.iret;
}

#else

void qemu_IShellFolder2_BindToObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_BindToObject *c = (struct qemu_IShellFolder2_BindToObject *)call;
    struct qemu_shellfolder *folder, *retobj;
    IShellFolder2 *out;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);
    if (c->pbcReserved)
        WINE_FIXME("Bind context not handled yet.\n");

    c->super.iret = IShellFolder2_BindToObject(folder->host_sf, QEMU_G2H(c->pidl), QEMU_G2H(c->pbcReserved),
            &IID_IShellFolder2, (void **)&out);
    if (FAILED(c->super.iret))
        return;

    retobj = qemu_shellfolder_host_create(out);
    if (!retobj)
    {
        IShellFolder2_Release(out);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    c->out = QEMU_H2G(retobj);
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
    uint64_t list1;
    uint64_t list2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellfolder_CompareIDs (IShellFolder2 *iface, LPARAM lParam,
        const ITEMIDLIST *list1, const ITEMIDLIST *list2)
{
    struct qemu_IShellFolder2_CompareIDs call;
    struct qemu_shellfolder *folder = impl_from_IShellFolder2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDER2_COMPAREIDS);
    call.iface = (ULONG_PTR)folder;
    call.lParam = lParam;
    call.list1 = (ULONG_PTR)list1;
    call.list2 = (ULONG_PTR)list2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolder2_CompareIDs(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_CompareIDs *c = (struct qemu_IShellFolder2_CompareIDs *)call;
    struct qemu_shellfolder *folder;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_CompareIDs(folder->host_sf, c->lParam, QEMU_G2H(c->list1), QEMU_G2H(c->list2));
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

static HRESULT WINAPI qemu_shellfolder_GetAttributesOf (IShellFolder2 *iface, UINT cidl,
        LPCITEMIDLIST *apidl, DWORD *rgfInOut)
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
    ITEMIDLIST *stack[16], **list = stack;
    qemu_ptr *list32;
    UINT i;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    list = QEMU_G2H(c->apidl);
#else
    list32 = QEMU_G2H(c->apidl);
    if (!list32)
    {
        list = NULL;
    }
    else
    {
        if (c->cidl > sizeof(stack) / sizeof(*stack))
        {
            list = HeapAlloc(GetProcessHeap(), 0, sizeof(*list) * c->cidl);
            if (!list)
                WINE_ERR("Out of memory\n");
        }

        for (i = 0; i < c->cidl; ++i)
            list[i] = QEMU_G2H((uint64_t)list32[i]);
    }
#endif
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_GetAttributesOf(folder->host_sf, c->cidl, (const ITEMIDLIST **)list,
            QEMU_G2H(c->rgfInOut));

#if GUEST_BIT != HOST_BIT
    if (list != stack)
        HeapFree(GetProcessHeap(), 0, list);
#endif
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

static HRESULT WINAPI qemu_shellfolder_GetDisplayNameOf (IShellFolder2 *iface, LPCITEMIDLIST pidl,
        DWORD dwFlags, LPSTRRET strRet)
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
    STRRET stack, *ret = &stack;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    ret = QEMU_G2H(c->strRet);
#else
    if (!c->strRet)
        ret = NULL;
#endif

    c->super.iret = IShellFolder2_GetDisplayNameOf(folder->host_sf, QEMU_G2H(c->pidl), c->dwFlags, ret);
#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(c->super.iret))
        STRRET_h2g(QEMU_G2H(c->strRet), ret);
#endif
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

static HRESULT WINAPI qemu_shellfolder_SetNameOf (IShellFolder2 *iface, HWND hwndOwner,
        LPCITEMIDLIST pidl, LPCOLESTR lpName, DWORD dwFlags, LPITEMIDLIST * pPidlOut)
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
    if (SUCCEEDED(call.super.iret) && pPidlOut)
        *pPidlOut = (ITEMIDLIST *)(ULONG_PTR)call.pPidlOut;

    return call.super.iret;
}

#else

void qemu_IShellFolder2_SetNameOf(struct qemu_syscall *call)
{
    struct qemu_IShellFolder2_SetNameOf *c = (struct qemu_IShellFolder2_SetNameOf *)call;
    struct qemu_shellfolder *folder;
    ITEMIDLIST *out;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IShellFolder2_SetNameOf(folder->host_sf, QEMU_G2H(c->hwndOwner), QEMU_G2H(c->pidl),
            QEMU_G2H(c->lpName), c->dwFlags, c->pPidlOut ? &out : NULL);
    c->pPidlOut = QEMU_H2G(out);
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

struct qemu_IPersistFolder3_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_QueryInterface(IPersistFolder3 *iface, REFIID riid, LPVOID *ppvObj)
{
    struct qemu_IPersistFolder3_QueryInterface call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_QUERYINTERFACE);
    call.iface = (ULONG_PTR)folder;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_QueryInterface *c = (struct qemu_IPersistFolder3_QueryInterface *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_QueryInterface(folder->host_pf, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_IPersistFolder3_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_persistfolder_AddRef(IPersistFolder3 *iface)
{
    struct qemu_IPersistFolder3_AddRef call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_ADDREF);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_AddRef(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_AddRef *c = (struct qemu_IPersistFolder3_AddRef *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_AddRef(folder->host_pf);
}

#endif

struct qemu_IPersistFolder3_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_persistfolder_Release(IPersistFolder3 *iface)
{
    struct qemu_IPersistFolder3_Release call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_RELEASE);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_Release(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_Release *c = (struct qemu_IPersistFolder3_Release *)call;
    struct qemu_shellfolder *folder;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_Release(folder->host_pf);
    if (!c->super.iret)
    {
        WINE_TRACE("Freeing Shell folder wrapper %p.\n", folder);
        HeapFree(GetProcessHeap(), 0, folder);
    }
}

#endif

struct qemu_IPersistFolder3_GetClassID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clsid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_GetClassID(IPersistFolder3 *iface, CLSID *clsid)
{
    struct qemu_IPersistFolder3_GetClassID call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_GETCLASSID);
    call.iface = (ULONG_PTR)folder;
    call.clsid = (ULONG_PTR)clsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_GetClassID(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_GetClassID *c = (struct qemu_IPersistFolder3_GetClassID *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_GetClassID(folder->host_pf, QEMU_G2H(c->clsid));
}

#endif

struct qemu_IPersistFolder3_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_Initialize(IPersistFolder3 *iface, LPCITEMIDLIST pidl)
{
    struct qemu_IPersistFolder3_Initialize call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_INITIALIZE);
    call.iface = (ULONG_PTR)folder;
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_Initialize(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_Initialize *c = (struct qemu_IPersistFolder3_Initialize *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_Initialize(folder->host_pf, QEMU_G2H(c->pidl));
}

#endif

struct qemu_IPersistFolder3_GetCurFolder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppidl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_GetCurFolder(IPersistFolder3 *iface, LPITEMIDLIST *ppidl)
{
    struct qemu_IPersistFolder3_GetCurFolder call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_GETCURFOLDER);
    call.iface = (ULONG_PTR)folder;
    call.ppidl = (ULONG_PTR)ppidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_GetCurFolder(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_GetCurFolder *c = (struct qemu_IPersistFolder3_GetCurFolder *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_GetCurFolder(folder->host_pf, QEMU_G2H(c->ppidl));
}

#endif

struct qemu_IPersistFolder3_InitializeEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pbc;
    uint64_t pidlRoot;
    uint64_t ppfti;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_InitializeEx(IPersistFolder3 *iface, IBindCtx *pbc,
        LPCITEMIDLIST pidlRoot, const PERSIST_FOLDER_TARGET_INFO *ppfti)
{
    struct qemu_IPersistFolder3_InitializeEx call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_INITIALIZEEX);
    call.iface = (ULONG_PTR)folder;
    call.pbc = (ULONG_PTR)pbc;
    call.pidlRoot = (ULONG_PTR)pidlRoot;
    call.ppfti = (ULONG_PTR)ppfti;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_InitializeEx(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_InitializeEx *c = (struct qemu_IPersistFolder3_InitializeEx *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_InitializeEx(folder->host_pf, QEMU_G2H(c->pbc), QEMU_G2H(c->pidlRoot), QEMU_G2H(c->ppfti));
}

#endif

struct qemu_IPersistFolder3_GetFolderTargetInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppfti;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_persistfolder_GetFolderTargetInfo(IPersistFolder3 *iface, PERSIST_FOLDER_TARGET_INFO *ppfti)
{
    struct qemu_IPersistFolder3_GetFolderTargetInfo call;
    struct qemu_shellfolder *folder = impl_from_IPersistFolder3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IPERSISTFOLDER3_GETFOLDERTARGETINFO);
    call.iface = (ULONG_PTR)folder;
    call.ppfti = (ULONG_PTR)ppfti;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IPersistFolder3_GetFolderTargetInfo(struct qemu_syscall *call)
{
    struct qemu_IPersistFolder3_GetFolderTargetInfo *c = (struct qemu_IPersistFolder3_GetFolderTargetInfo *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistFolder3_GetFolderTargetInfo(folder->host_pf, QEMU_G2H(c->ppfti));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_property_bag_QueryInterface(IPersistPropertyBag* iface, REFIID iid, void **obj)
{
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);
    return qemu_shellfolder_QueryInterface(&folder->IShellFolder2_iface, iid, obj);
}

static ULONG WINAPI qemu_property_bag_AddRef(IPersistPropertyBag* iface)
{
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);
    return qemu_shellfolder_AddRef(&folder->IShellFolder2_iface);
}

static ULONG WINAPI qemu_property_bag_Release(IPersistPropertyBag* iface)
{
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);
    return qemu_shellfolder_Release(&folder->IShellFolder2_iface);
}

#endif

struct qemu_PersistPropertyBag_GetClassID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pClassID;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_property_bag_GetClassID(IPersistPropertyBag* iface, CLSID* pClassID)
{
    struct qemu_PersistPropertyBag_GetClassID call;
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PERSISTPROPERTYBAG_GETCLASSID);
    call.iface = (ULONG_PTR)folder;
    call.pClassID = (ULONG_PTR)pClassID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PersistPropertyBag_GetClassID(struct qemu_syscall *call)
{
    struct qemu_PersistPropertyBag_GetClassID *c = (struct qemu_PersistPropertyBag_GetClassID *)call;
    struct qemu_shellfolder *folder;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistPropertyBag_GetClassID(folder->host_bag, QEMU_G2H(c->pClassID));
}

#endif

struct qemu_PersistPropertyBag_InitNew
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_property_bag_InitNew(IPersistPropertyBag* iface)
{
    struct qemu_PersistPropertyBag_InitNew call;
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PERSISTPROPERTYBAG_INITNEW);
    call.iface = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PersistPropertyBag_InitNew(struct qemu_syscall *call)
{
    struct qemu_PersistPropertyBag_InitNew *c = (struct qemu_PersistPropertyBag_InitNew *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistPropertyBag_InitNew(folder->host_bag);
}

#endif

struct qemu_PersistPropertyBag_Load
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPropertyBag;
    uint64_t pErrorLog;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_property_bag_Load(IPersistPropertyBag *iface, IPropertyBag *pPropertyBag, IErrorLog *pErrorLog)
{
    struct qemu_PersistPropertyBag_Load call;
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PERSISTPROPERTYBAG_LOAD);
    call.iface = (ULONG_PTR)folder;
    call.pPropertyBag = (ULONG_PTR)pPropertyBag;
    call.pErrorLog = (ULONG_PTR)pErrorLog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PersistPropertyBag_Load(struct qemu_syscall *call)
{
    struct qemu_PersistPropertyBag_Load *c = (struct qemu_PersistPropertyBag_Load *)call;
    struct qemu_shellfolder *folder;
    struct propertybag_wrapper *wrapper;

    WINE_TRACE("\n");
    folder = QEMU_G2H(c->iface);

    wrapper = propertybag_wrapper_create(c->pPropertyBag);
    if (!wrapper)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    if (c->pErrorLog)
        WINE_FIXME("Error log %p not handled yet.\n", QEMU_G2H(c->pErrorLog));

    c->super.iret = IPersistPropertyBag_Load(folder->host_bag, propertybag_wrapper_host_iface(wrapper), NULL);

    propertybag_wrapper_destroy(wrapper);
}

#endif

struct qemu_PersistPropertyBag_Save
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPropertyBag;
    uint64_t fClearDirty;
    uint64_t fSaveAllProperties;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_property_bag_Save(IPersistPropertyBag *iface, IPropertyBag *pPropertyBag, BOOL fClearDirty, BOOL fSaveAllProperties)
{
    struct qemu_PersistPropertyBag_Save call;
    struct qemu_shellfolder *folder = impl_from_IPersistPropertyBag(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PERSISTPROPERTYBAG_SAVE);
    call.iface = (ULONG_PTR)folder;
    call.pPropertyBag = (ULONG_PTR)pPropertyBag;
    call.fClearDirty = fClearDirty;
    call.fSaveAllProperties = fSaveAllProperties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PersistPropertyBag_Save(struct qemu_syscall *call)
{
    struct qemu_PersistPropertyBag_Save *c = (struct qemu_PersistPropertyBag_Save *)call;
    struct qemu_shellfolder *folder;

    WINE_FIXME("Unverified!\n");
    folder = QEMU_G2H(c->iface);

    c->super.iret = IPersistPropertyBag_Save(folder->host_bag, QEMU_G2H(c->pPropertyBag), c->fClearDirty, c->fSaveAllProperties);
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

static const IPersistFolder3Vtbl vtbl_PersistFolder3 =
{
    qemu_persistfolder_QueryInterface,
    qemu_persistfolder_AddRef,
    qemu_persistfolder_Release,
    qemu_persistfolder_GetClassID,
    qemu_persistfolder_Initialize,
    qemu_persistfolder_GetCurFolder,
    qemu_persistfolder_InitializeEx,
    qemu_persistfolder_GetFolderTargetInfo,
};

static const IPersistPropertyBagVtbl vtbl_PersistPropertyBag =
{
    qemu_property_bag_QueryInterface,
    qemu_property_bag_AddRef,
    qemu_property_bag_Release,
    qemu_property_bag_GetClassID,
    qemu_property_bag_InitNew,
    qemu_property_bag_Load,
    qemu_property_bag_Save
};

void qemu_shellfolder_guest_init(struct qemu_shellfolder *folder)
{
    folder->IShellFolder2_iface.lpVtbl = &vtbl_ShellFolder2;
    folder->IPersistFolder3_iface.lpVtbl = &vtbl_PersistFolder3;
    folder->IPersistPropertyBag_iface.lpVtbl = &vtbl_PersistPropertyBag;
}

#else

struct qemu_shellfolder *qemu_shellfolder_host_create(IShellFolder2 *host)
{
    struct qemu_shellfolder *folder;

    if (shellfolder_desktop && host == shellfolder_desktop->host_sf)
    {
        WINE_TRACE("Returning existing Desktop IShellFolder %p.\n", shellfolder_desktop);
        return shellfolder_desktop;
    }

    folder = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*folder));
    if (!folder)
        return NULL;

    folder->host_sf = host;
    IShellFolder2_QueryInterface(host, &IID_IPersistFolder3, (void **)&folder->host_pf);

    /* Not all host shell folders implement IPersistFolder3. */
    if (!folder->host_pf)
        IShellFolder2_QueryInterface(host, &IID_IPersistFolder2, (void **)&folder->host_pf);
    else
        folder->flags |= SHELLFOLDER_HAS_PERSISTFOLDER3;

    /* The wrapper does not have its own refcount, don't hold references to the inteface ourselves. */
    IPersistFolder3_Release(folder->host_pf);

    IShellFolder2_QueryInterface(host, &IID_IPersistPropertyBag, (void **)&folder->host_bag);
    if (folder->host_bag)
    {
        folder->flags |= SHELLFOLDER_HAS_PROPERTYBAG;
        IPersistPropertyBag_Release(folder->host_bag);
    }

    if (!shellfolder_desktop)
    {
        IShellFolder *desktop;
        SHGetDesktopFolder(&desktop);
        if (host == (IShellFolder2 *)desktop)
        {
            WINE_TRACE("Caching desktop wrapper object %p.\n", folder);
            shellfolder_desktop = folder;
        }
        IShellFolder_Release(desktop);
    }

    return folder;
}

#endif
