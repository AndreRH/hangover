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

#define COBJMACROS
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_IEnumIDList_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_enumidlist *impl_from_IEnumIDList(IEnumIDList *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_enumidlist, IEnumIDList_iface);
}

static HRESULT WINAPI qemu_enumidlist_QueryInterface(IEnumIDList *iface, REFIID iid, void **obj)
{
    struct qemu_IEnumIDList_QueryInterface call;
    struct qemu_enumidlist *list = impl_from_IEnumIDList(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_QUERYINTERFACE);
    call.iface = (ULONG_PTR)list;
    call.iid = (ULONG_PTR)iid;
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_QueryInterface *c = (struct qemu_IEnumIDList_QueryInterface *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_QueryInterface(list->host, QEMU_G2H(c->iid), QEMU_G2H(c->obj));
}

#endif

struct qemu_IEnumIDList_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_enumidlist_AddRef(IEnumIDList *iface)
{
    struct qemu_IEnumIDList_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_ADDREF);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_AddRef(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_AddRef *c = (struct qemu_IEnumIDList_AddRef *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_AddRef(list->host);
}

#endif

struct qemu_IEnumIDList_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_enumidlist_Release(IEnumIDList *iface)
{
    struct qemu_IEnumIDList_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_RELEASE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_Release(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_Release *c = (struct qemu_IEnumIDList_Release *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_Release(list->host);
}

#endif

struct qemu_IEnumIDList_Next
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t celt;
    uint64_t rgelt;
    uint64_t fetched;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_enumidlist_Next(IEnumIDList *iface, ULONG celt, LPITEMIDLIST *rgelt, ULONG *fetched)
{
    struct qemu_IEnumIDList_Next call;
    struct qemu_enumidlist *list = impl_from_IEnumIDList(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_NEXT);
    call.iface = (ULONG_PTR)iface;
    call.celt = celt;
    call.rgelt = (ULONG_PTR)rgelt;
    call.fetched = (ULONG_PTR)fetched;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_Next(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_Next *c = (struct qemu_IEnumIDList_Next *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_Next(list->host, c->celt, QEMU_G2H(c->rgelt), QEMU_G2H(c->fetched));
}

#endif

struct qemu_IEnumIDList_Skip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t celt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_enumidlist_Skip(IEnumIDList *iface, ULONG celt)
{
    struct qemu_IEnumIDList_Skip call;
    struct qemu_enumidlist *list = impl_from_IEnumIDList(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_SKIP);
    call.iface = (ULONG_PTR)iface;
    call.celt = celt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_Skip(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_Skip *c = (struct qemu_IEnumIDList_Skip *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_Skip(list->host, c->celt);
}

#endif

struct qemu_IEnumIDList_Reset
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_enumidlist_Reset(IEnumIDList *iface)
{
    struct qemu_IEnumIDList_Reset call;
    struct qemu_enumidlist *list = impl_from_IEnumIDList(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_RESET);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_Reset(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_Reset *c = (struct qemu_IEnumIDList_Reset *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_Reset(list->host);
}

#endif

struct qemu_IEnumIDList_Clone
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppenum;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_enumidlist_Clone(IEnumIDList *iface, IEnumIDList **ppenum)
{
    struct qemu_IEnumIDList_Clone call;
    struct qemu_enumidlist *list = impl_from_IEnumIDList(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IENUMIDLIST_CLONE);
    call.iface = (ULONG_PTR)iface;
    call.ppenum = (ULONG_PTR)ppenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IEnumIDList_Clone(struct qemu_syscall *call)
{
    struct qemu_IEnumIDList_Clone *c = (struct qemu_IEnumIDList_Clone *)call;
    struct qemu_enumidlist *list;

    WINE_FIXME("Unverified!\n");
    list = QEMU_G2H(c->iface);

    c->super.iret = IEnumIDList_Clone(list->host, QEMU_G2H(c->ppenum));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IEnumIDListVtbl vtbl =
{
    qemu_enumidlist_QueryInterface,
    qemu_enumidlist_AddRef,
    qemu_enumidlist_Release,
    qemu_enumidlist_Next,
    qemu_enumidlist_Skip,
    qemu_enumidlist_Reset,
    qemu_enumidlist_Clone,
};

void qemu_enumidlist_guest_init(struct qemu_enumidlist *folder)
{
    folder->IEnumIDList_iface.lpVtbl = &vtbl;
}

#else

struct qemu_enumidlist *qemu_enumidlist_host_create(IEnumIDList *host)
{
    struct qemu_enumidlist *list;

    list = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*list));
    if (!list)
    {
        WINE_FIXME("Out of memory.\n");
        return NULL;
    }

    list->host = host;
    return list;
}

#endif
