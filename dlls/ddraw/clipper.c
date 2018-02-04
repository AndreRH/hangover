/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#define COBJMACROS

#include <windows.h>
#include <stdio.h>
#include <ddraw.h>
#include <d3d.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_ddraw_clipper_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_clipper *impl_from_IDirectDrawClipper(IDirectDrawClipper *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_clipper, IDirectDrawClipper_iface);
}

static HRESULT WINAPI ddraw_clipper_QueryInterface(IDirectDrawClipper *iface, REFIID iid, void **object)
{
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);

    WINE_TRACE("iface %p, iid %s, object %p.\n", iface, wine_dbgstr_guid(iid), object);

    if (IsEqualGUID(&IID_IDirectDrawClipper, iid)
            || IsEqualGUID(&IID_IUnknown, iid))
    {
        IDirectDrawClipper_AddRef(&clipper->IDirectDrawClipper_iface);
        *object = &clipper->IDirectDrawClipper_iface;
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(iid));
    *object = NULL;

    return E_NOINTERFACE;
}

static ULONG WINAPI ddraw_clipper_AddRef(IDirectDrawClipper *iface)
{
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    ULONG refcount = InterlockedIncrement(&clipper->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", clipper, refcount);

    return refcount;
}

static ULONG WINAPI ddraw_clipper_Release(IDirectDrawClipper *iface)
{
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    ULONG refcount = InterlockedDecrement(&clipper->ref);
    struct qemu_ddraw_clipper_Release call;

    WINE_TRACE("%p decreasing refcount to %u.\n", clipper, refcount);

    if (!refcount)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_RELEASE);
        call.iface = (ULONG_PTR)clipper;
        qemu_syscall(&call.super);
    }

    return refcount;
}

#else

void qemu_ddraw_clipper_Release(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_Release *c = (struct qemu_ddraw_clipper_Release *)call;
    struct qemu_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);
    c->super.iret = IDirectDrawClipper_Release(clipper->host);

    /* The wrapper object is also addref'ed when assigned to a surface, so when we end up here
     * the host ddraw shouldn't have any internal references either. */
    if (c->super.iret)
        WINE_ERR("Unexpected host refcount %lu.\n", c->super.iret);
}

#endif

struct qemu_ddraw_clipper_SetHWnd
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t window;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_clipper_SetHWnd(IDirectDrawClipper *iface, DWORD flags, HWND window)
{
    struct qemu_ddraw_clipper_SetHWnd call;
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_SETHWND);
    call.iface = (ULONG_PTR)clipper;
    call.flags = flags;
    call.window = (ULONG_PTR)window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_clipper_SetHWnd(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_SetHWnd *c = (struct qemu_ddraw_clipper_SetHWnd *)call;
    struct qemu_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawClipper_SetHWnd(clipper->host, c->flags, QEMU_G2H(c->window));
}

#endif

struct qemu_ddraw_clipper_GetClipList
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
    uint64_t clip_list;
    uint64_t clip_list_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_clipper_GetClipList(IDirectDrawClipper *iface, RECT *rect, RGNDATA *clip_list, DWORD *clip_list_size)
{
    struct qemu_ddraw_clipper_GetClipList call;
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_GETCLIPLIST);
    call.iface = (ULONG_PTR)clipper;
    call.rect = (ULONG_PTR)rect;
    call.clip_list = (ULONG_PTR)clip_list;
    call.clip_list_size = (ULONG_PTR)clip_list_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_clipper_GetClipList(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_GetClipList *c = (struct qemu_ddraw_clipper_GetClipList *)call;
    struct qemu_clipper *clipper;

    /* RGNDATA has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawClipper_GetClipList(clipper->host, QEMU_G2H(c->rect), QEMU_G2H(c->clip_list), QEMU_G2H(c->clip_list_size));
}

#endif

struct qemu_ddraw_clipper_SetClipList
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t region;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_clipper_SetClipList(IDirectDrawClipper *iface, RGNDATA *region, DWORD flags)
{
    struct qemu_ddraw_clipper_SetClipList call;
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_SETCLIPLIST);
    call.iface = (ULONG_PTR)clipper;
    call.region = (ULONG_PTR)region;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_clipper_SetClipList(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_SetClipList *c = (struct qemu_ddraw_clipper_SetClipList *)call;
    struct qemu_clipper *clipper;

    /* RGNDATA has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawClipper_SetClipList(clipper->host, QEMU_G2H(c->region), c->flags);
}

#endif

struct qemu_ddraw_clipper_GetHWnd
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_clipper_GetHWnd(IDirectDrawClipper *iface, HWND *window)
{
    struct qemu_ddraw_clipper_GetHWnd call;
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_GETHWND);
    call.iface = (ULONG_PTR)clipper;
    call.window = (ULONG_PTR)window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_clipper_GetHWnd(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_GetHWnd *c = (struct qemu_ddraw_clipper_GetHWnd *)call;
    struct qemu_clipper *clipper;

    WINE_FIXME("Unverified!\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawClipper_GetHWnd(clipper->host, QEMU_G2H(c->window));
}

#endif

struct qemu_ddraw_clipper_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_clipper_Initialize(IDirectDrawClipper *iface, IDirectDraw *ddraw, DWORD flags)
{
    struct qemu_ddraw_clipper_Initialize call;
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    struct qemu_ddraw *ddraw_impl = unsafe_impl_from_IDirectDraw(ddraw);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_INITIALIZE);
    call.iface = (ULONG_PTR)clipper;
    call.ddraw = (ULONG_PTR)ddraw_impl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_clipper_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_Initialize *c = (struct qemu_ddraw_clipper_Initialize *)call;
    struct qemu_clipper *clipper;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);
    ddraw = QEMU_G2H(c->ddraw);

    c->super.iret = IDirectDrawClipper_Initialize(clipper->host, ddraw ? ddraw->host_ddraw1 : NULL, c->flags);
}

#endif

struct qemu_ddraw_clipper_IsClipListChanged
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t changed;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_clipper_IsClipListChanged(IDirectDrawClipper *iface, BOOL *changed)
{
    struct qemu_ddraw_clipper_IsClipListChanged call;
    struct qemu_clipper *clipper = impl_from_IDirectDrawClipper(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_CLIPPER_ISCLIPLISTCHANGED);
    call.iface = (ULONG_PTR)clipper;
    call.changed = (ULONG_PTR)changed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_clipper_IsClipListChanged(struct qemu_syscall *call)
{
    struct qemu_ddraw_clipper_IsClipListChanged *c = (struct qemu_ddraw_clipper_IsClipListChanged *)call;
    struct qemu_clipper *clipper;

    WINE_FIXME("Unverified!\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawClipper_IsClipListChanged(clipper->host, QEMU_G2H(c->changed));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirectDrawClipperVtbl ddraw_clipper_vtbl =
{
    ddraw_clipper_QueryInterface,
    ddraw_clipper_AddRef,
    ddraw_clipper_Release,
    ddraw_clipper_GetClipList,
    ddraw_clipper_GetHWnd,
    ddraw_clipper_Initialize,
    ddraw_clipper_IsClipListChanged,
    ddraw_clipper_SetClipList,
    ddraw_clipper_SetHWnd,
};

void ddraw_clipper_guest_init(struct qemu_clipper *clipper)
{
    clipper->IDirectDrawClipper_iface.lpVtbl = &ddraw_clipper_vtbl;
    clipper->ref = 1;
}

struct qemu_clipper *unsafe_impl_from_IDirectDrawClipper(IDirectDrawClipper *iface)
{
    if (!iface)
        return NULL;
    if (iface->lpVtbl != &ddraw_clipper_vtbl)
        WINE_ERR("Incorrect clipper vtable %p, expect %p.\n", iface->lpVtbl, &ddraw_clipper_vtbl);

    return impl_from_IDirectDrawClipper(iface);
}

#endif
