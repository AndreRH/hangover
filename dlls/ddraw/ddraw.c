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

#include "thunk/qemu_windows.h"
#include "thunk/qemu_ddraw.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#include <wine/exception.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_ddraw1_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

struct qemu_ddraw1_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_ddraw *impl_from_IDirectDraw(IDirectDraw *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirectDraw_iface);
}

static inline struct qemu_ddraw *impl_from_IDirectDraw2(IDirectDraw2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirectDraw2_iface);
}

static inline struct qemu_ddraw *impl_from_IDirectDraw4(IDirectDraw4 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirectDraw4_iface);
}

static inline struct qemu_ddraw *impl_from_IDirectDraw7(IDirectDraw7 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirectDraw7_iface);
}

static inline struct qemu_ddraw *impl_from_IDirect3D(IDirect3D *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirect3D_iface);
}

static inline struct qemu_ddraw *impl_from_IDirect3D2(IDirect3D2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirect3D2_iface);
}

static inline struct qemu_ddraw *impl_from_IDirect3D3(IDirect3D3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirect3D3_iface);
}

static inline struct qemu_ddraw *impl_from_IDirect3D7(IDirect3D7 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_ddraw, IDirect3D7_iface);
}

/* The purpose of this is to set the ddraw->d3dversion member in the host
 * object approprietly for the right enumerated devices in EnumDevices. */
static void d3d_set_version(struct qemu_ddraw *ddraw, REFIID iid)
{
    struct qemu_ddraw1_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_QUERYINTERFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.iid = (ULONG_PTR)iid;
    qemu_syscall(&call.super);
}

static HRESULT WINAPI ddraw7_QueryInterface(IDirectDraw7 *iface, REFIID riid, void **out)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);

    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (!riid)
    {
        *out = NULL;
        return DDERR_INVALIDPARAMS;
    }

    /* The refcount unit test revealed that an IDirect3D7 interface can only
     * be queried from a DirectDraw object that was created as an IDirectDraw7
     * interface. The older interfaces can query any IDirect3D version except
     * 7, because they are all initially created as IDirectDraw. This isn't
     * really crucial behavior, and messy to implement with the common
     * creation function, so it has been left out here. */
    if (IsEqualGUID(&IID_IDirectDraw7, riid)
            || IsEqualGUID(&IID_IUnknown, riid))
    {
        *out = &ddraw->IDirectDraw7_iface;
        WINE_TRACE("Returning IDirectDraw7 interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirectDraw4, riid))
    {
        *out = &ddraw->IDirectDraw4_iface;
        WINE_TRACE("Returning IDirectDraw4 interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirectDraw2, riid))
    {
        *out = &ddraw->IDirectDraw2_iface;
        WINE_TRACE("Returning IDirectDraw2 interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirectDraw, riid))
    {
        *out = &ddraw->IDirectDraw_iface;
        WINE_TRACE("Returning IDirectDraw interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirect3D7, riid))
    {
        d3d_set_version(ddraw, &IID_IDirect3D7);
        *out = &ddraw->IDirect3D7_iface;
        WINE_TRACE("Returning Direct3D7 interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirect3D3, riid))
    {
        d3d_set_version(ddraw, &IID_IDirect3D3);
        *out = &ddraw->IDirect3D3_iface;
        WINE_TRACE("Returning Direct3D3 interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirect3D2, riid))
    {
        d3d_set_version(ddraw, &IID_IDirect3D2);
        *out = &ddraw->IDirect3D2_iface;
        WINE_TRACE("Returning Direct3D2 interface %p.\n", *out);
    }
    else if (IsEqualGUID(&IID_IDirect3D, riid))
    {
        d3d_set_version(ddraw, &IID_IDirect3D);
        *out = &ddraw->IDirect3D_iface;
        WINE_TRACE("Returning Direct3D interface %p.\n", *out);
    }
    /* Unknown interface */
    else
    {
        WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));
        *out = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown *)*out);
    return S_OK;
}

static HRESULT WINAPI ddraw4_QueryInterface(IDirectDraw4 *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static HRESULT WINAPI ddraw2_QueryInterface(IDirectDraw2 *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static HRESULT WINAPI ddraw1_QueryInterface(IDirectDraw *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static HRESULT WINAPI d3d7_QueryInterface(IDirect3D7 *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static HRESULT WINAPI d3d3_QueryInterface(IDirect3D3 *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static HRESULT WINAPI d3d2_QueryInterface(IDirect3D2 *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static HRESULT WINAPI d3d1_QueryInterface(IDirect3D *iface, REFIID riid, void **object)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw7_QueryInterface(&ddraw->IDirectDraw7_iface, riid, object);
}

static ULONG WINAPI ddraw7_AddRef(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    ULONG ref = InterlockedIncrement(&ddraw->ref7);

    WINE_TRACE("%p increasing refcount to %u.\n", ddraw, ref);

    if(ref == 1) InterlockedIncrement(&ddraw->numIfaces);

    return ref;
}

static ULONG WINAPI ddraw4_AddRef(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    ULONG ref = InterlockedIncrement(&ddraw->ref4);

    WINE_TRACE("%p increasing refcount to %u.\n", ddraw, ref);

    if (ref == 1) InterlockedIncrement(&ddraw->numIfaces);

    return ref;
}

static ULONG WINAPI ddraw2_AddRef(IDirectDraw2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    ULONG ref = InterlockedIncrement(&ddraw->ref2);

    WINE_TRACE("%p increasing refcount to %u.\n", ddraw, ref);

    if (ref == 1) InterlockedIncrement(&ddraw->numIfaces);

    return ref;
}

static ULONG WINAPI ddraw1_AddRef(IDirectDraw *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    ULONG ref = InterlockedIncrement(&ddraw->ref1);

    WINE_TRACE("%p increasing refcount to %u.\n", ddraw, ref);

    if (ref == 1) InterlockedIncrement(&ddraw->numIfaces);

    return ref;
}

static ULONG WINAPI d3d7_AddRef(IDirect3D7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw7_AddRef(&ddraw->IDirectDraw7_iface);
}

static ULONG WINAPI d3d3_AddRef(IDirect3D3 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw1_AddRef(&ddraw->IDirectDraw_iface);
}

static ULONG WINAPI d3d2_AddRef(IDirect3D2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw1_AddRef(&ddraw->IDirectDraw_iface);
}

static ULONG WINAPI d3d1_AddRef(IDirect3D *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw1_AddRef(&ddraw->IDirectDraw_iface);
}

static void ddraw_destroy(struct qemu_ddraw *ddraw)
{
    struct qemu_ddraw1_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_RELEASE);
    call.iface = (ULONG_PTR)ddraw;
    qemu_syscall(&call.super);
}

static ULONG WINAPI ddraw7_Release(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    ULONG ref = InterlockedDecrement(&ddraw->ref7);

    WINE_TRACE("%p decreasing refcount to %u.\n", ddraw, ref);

    if (!ref && !InterlockedDecrement(&ddraw->numIfaces))
        ddraw_destroy(ddraw);

    return ref;
}

static ULONG WINAPI ddraw4_Release(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    ULONG ref = InterlockedDecrement(&ddraw->ref4);

    WINE_TRACE("%p decreasing refcount to %u.\n", ddraw, ref);

    if (!ref && !InterlockedDecrement(&ddraw->numIfaces))
        ddraw_destroy(ddraw);

    return ref;
}

static ULONG WINAPI ddraw2_Release(IDirectDraw2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    ULONG ref = InterlockedDecrement(&ddraw->ref2);

    WINE_TRACE("%p decreasing refcount to %u.\n", ddraw, ref);

    if (!ref && !InterlockedDecrement(&ddraw->numIfaces))
        ddraw_destroy(ddraw);

    return ref;
}

static ULONG WINAPI ddraw1_Release(IDirectDraw *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    ULONG ref = InterlockedDecrement(&ddraw->ref1);

    WINE_TRACE("%p decreasing refcount to %u.\n", ddraw, ref);

    if (!ref && !InterlockedDecrement(&ddraw->numIfaces))
        ddraw_destroy(ddraw);

    return ref;
}

static ULONG WINAPI d3d7_Release(IDirect3D7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw7_Release(&ddraw->IDirectDraw7_iface);
}

static ULONG WINAPI d3d3_Release(IDirect3D3 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw1_Release(&ddraw->IDirectDraw_iface);
}

static ULONG WINAPI d3d2_Release(IDirect3D2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw1_Release(&ddraw->IDirectDraw_iface);
}

static ULONG WINAPI d3d1_Release(IDirect3D *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);

    WINE_TRACE("iface %p.\n", iface);

    return ddraw1_Release(&ddraw->IDirectDraw_iface);
}

#else

void qemu_ddraw1_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ddraw1_QueryInterface *c = (struct qemu_ddraw1_QueryInterface *)call;
    struct qemu_ddraw *ddraw;
    IUnknown *obj;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    IDirectDraw_QueryInterface(ddraw->host_ddraw1, QEMU_G2H(c->iid), (void **)&obj);
    IUnknown_Release(obj);
}

void qemu_ddraw1_Release(struct qemu_syscall *call)
{
    struct qemu_ddraw1_Release *c = (struct qemu_ddraw1_Release *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    if (ddraw->host_d3d7)
        IDirect3D7_Release(ddraw->host_d3d7);
    IDirect3D3_Release(ddraw->host_d3d3);
    IDirect3D2_Release(ddraw->host_d3d2);
    IDirect3D_Release(ddraw->host_d3d1);

    c->super.iret = IDirectDraw_Release(ddraw->host_ddraw1);
    c->super.iret += IDirectDraw2_Release(ddraw->host_ddraw2);
    c->super.iret += IDirectDraw4_Release(ddraw->host_ddraw4);
    c->super.iret += IDirectDraw7_Release(ddraw->host_ddraw7);

    if (c->super.iret)
        WINE_ERR("Unexpected host interface refcount sum %lu\n", c->super.iret);
}

#endif

struct qemu_ddraw7_RestoreDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_RestoreDisplayMode(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_RestoreDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_RESTOREDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_RestoreDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw7_RestoreDisplayMode *c = (struct qemu_ddraw7_RestoreDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_RestoreDisplayMode(ddraw->host_ddraw7);
}

#endif

struct qemu_ddraw4_RestoreDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_RestoreDisplayMode(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_RestoreDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_RESTOREDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_RestoreDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw4_RestoreDisplayMode *c = (struct qemu_ddraw4_RestoreDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_RestoreDisplayMode(ddraw->host_ddraw4);
}

#endif

struct qemu_ddraw2_RestoreDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_RestoreDisplayMode(IDirectDraw2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_RestoreDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_RESTOREDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_RestoreDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw2_RestoreDisplayMode *c = (struct qemu_ddraw2_RestoreDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_RestoreDisplayMode(ddraw->host_ddraw2);
}

#endif

struct qemu_ddraw1_RestoreDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_RestoreDisplayMode(IDirectDraw *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_RestoreDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_RESTOREDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_RestoreDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw1_RestoreDisplayMode *c = (struct qemu_ddraw1_RestoreDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_RestoreDisplayMode(ddraw->host_ddraw1);
}

#endif

struct qemu_ddraw7_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_SetCooperativeLevel(IDirectDraw7 *iface, HWND window, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_SetCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)ddraw;
    call.window = (ULONG_PTR)window;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_ddraw7_SetCooperativeLevel *c = (struct qemu_ddraw7_SetCooperativeLevel *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_SetCooperativeLevel(ddraw->host_ddraw7, QEMU_G2H(c->window), c->flags);
}

#endif

struct qemu_ddraw4_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_SetCooperativeLevel(IDirectDraw4 *iface, HWND window, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_SetCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)ddraw;
    call.window = (ULONG_PTR)window;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_ddraw4_SetCooperativeLevel *c = (struct qemu_ddraw4_SetCooperativeLevel *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_SetCooperativeLevel(ddraw->host_ddraw4, QEMU_G2H(c->window), c->flags);
}

#endif

struct qemu_ddraw2_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_SetCooperativeLevel(IDirectDraw2 *iface, HWND window, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_SetCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)ddraw;
    call.window = (ULONG_PTR)window;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_ddraw2_SetCooperativeLevel *c = (struct qemu_ddraw2_SetCooperativeLevel *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_SetCooperativeLevel(ddraw->host_ddraw2, QEMU_G2H(c->window), c->flags);
}

#endif

struct qemu_ddraw1_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_SetCooperativeLevel(IDirectDraw *iface, HWND window, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_SetCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)ddraw;
    call.window = (ULONG_PTR)window;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_ddraw1_SetCooperativeLevel *c = (struct qemu_ddraw1_SetCooperativeLevel *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_SetCooperativeLevel(ddraw->host_ddraw1, QEMU_G2H(c->window), c->flags);
}

#endif

struct qemu_ddraw7_SetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t bpp;
    uint64_t refresh_rate;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_SetDisplayMode(IDirectDraw7 *iface, DWORD width, DWORD height, DWORD bpp, DWORD refresh_rate, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_SetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_SETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.width = width;
    call.height = height;
    call.bpp = bpp;
    call.refresh_rate = refresh_rate;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_SetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw7_SetDisplayMode *c = (struct qemu_ddraw7_SetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_SetDisplayMode(ddraw->host_ddraw7, c->width, c->height, c->bpp, c->refresh_rate, c->flags);
}

#endif

struct qemu_ddraw4_SetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t bpp;
    uint64_t refresh_rate;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_SetDisplayMode(IDirectDraw4 *iface, DWORD width, DWORD height, DWORD bpp, DWORD refresh_rate, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_SetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_SETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.width = width;
    call.height = height;
    call.bpp = bpp;
    call.refresh_rate = refresh_rate;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_SetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw4_SetDisplayMode *c = (struct qemu_ddraw4_SetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_SetDisplayMode(ddraw->host_ddraw4, c->width, c->height, c->bpp, c->refresh_rate, c->flags);
}

#endif

struct qemu_ddraw2_SetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t bpp;
    uint64_t refresh_rate;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_SetDisplayMode(IDirectDraw2 *iface, DWORD width, DWORD height, DWORD bpp, DWORD refresh_rate, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_SetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_SETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.width = width;
    call.height = height;
    call.bpp = bpp;
    call.refresh_rate = refresh_rate;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_SetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw2_SetDisplayMode *c = (struct qemu_ddraw2_SetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_SetDisplayMode(ddraw->host_ddraw2, c->width, c->height, c->bpp, c->refresh_rate, c->flags);
}

#endif

struct qemu_ddraw1_SetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t bpp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_SetDisplayMode(IDirectDraw *iface, DWORD width, DWORD height, DWORD bpp)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_SetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_SETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.width = width;
    call.height = height;
    call.bpp = bpp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_SetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw1_SetDisplayMode *c = (struct qemu_ddraw1_SetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_SetDisplayMode(ddraw->host_ddraw1, c->width, c->height, c->bpp);
}

#endif

struct qemu_ddraw7_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DriverCaps;
    uint64_t HELCaps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetCaps(IDirectDraw7 *iface, DDCAPS *DriverCaps, DDCAPS *HELCaps)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETCAPS);
    call.iface = (ULONG_PTR)ddraw;
    call.DriverCaps = (ULONG_PTR)DriverCaps;
    call.HELCaps = (ULONG_PTR)HELCaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetCaps *c = (struct qemu_ddraw7_GetCaps *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetCaps(ddraw->host_ddraw7, QEMU_G2H(c->DriverCaps), QEMU_G2H(c->HELCaps));
}

#endif

struct qemu_ddraw4_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t driver_caps;
    uint64_t hel_caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetCaps(IDirectDraw4 *iface, DDCAPS *driver_caps, DDCAPS *hel_caps)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETCAPS);
    call.iface = (ULONG_PTR)ddraw;
    call.driver_caps = (ULONG_PTR)driver_caps;
    call.hel_caps = (ULONG_PTR)hel_caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetCaps *c = (struct qemu_ddraw4_GetCaps *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetCaps(ddraw->host_ddraw4, QEMU_G2H(c->driver_caps), QEMU_G2H(c->hel_caps));
}

#endif

struct qemu_ddraw2_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t driver_caps;
    uint64_t hel_caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetCaps(IDirectDraw2 *iface, DDCAPS *driver_caps, DDCAPS *hel_caps)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETCAPS);
    call.iface = (ULONG_PTR)ddraw;
    call.driver_caps = (ULONG_PTR)driver_caps;
    call.hel_caps = (ULONG_PTR)hel_caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetCaps *c = (struct qemu_ddraw2_GetCaps *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetCaps(ddraw->host_ddraw2, QEMU_G2H(c->driver_caps), QEMU_G2H(c->hel_caps));
}

#endif

struct qemu_ddraw1_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t driver_caps;
    uint64_t hel_caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetCaps(IDirectDraw *iface, DDCAPS *driver_caps, DDCAPS *hel_caps)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETCAPS);
    call.iface = (ULONG_PTR)ddraw;
    call.driver_caps = (ULONG_PTR)driver_caps;
    call.hel_caps = (ULONG_PTR)hel_caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetCaps *c = (struct qemu_ddraw1_GetCaps *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetCaps(ddraw->host_ddraw1, QEMU_G2H(c->driver_caps), QEMU_G2H(c->hel_caps));
}

#endif

struct qemu_ddraw7_Compact
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_Compact(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_Compact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_COMPACT);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_Compact(struct qemu_syscall *call)
{
    struct qemu_ddraw7_Compact *c = (struct qemu_ddraw7_Compact *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_Compact(ddraw->host_ddraw7);
}

#endif

struct qemu_ddraw4_Compact
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_Compact(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_Compact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_COMPACT);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_Compact(struct qemu_syscall *call)
{
    struct qemu_ddraw4_Compact *c = (struct qemu_ddraw4_Compact *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_Compact(ddraw->host_ddraw4);
}

#endif

struct qemu_ddraw2_Compact
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_Compact(IDirectDraw2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_Compact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_COMPACT);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_Compact(struct qemu_syscall *call)
{
    struct qemu_ddraw2_Compact *c = (struct qemu_ddraw2_Compact *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_Compact(ddraw->host_ddraw2);
}

#endif

struct qemu_ddraw1_Compact
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_Compact(IDirectDraw *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_Compact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_COMPACT);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_Compact(struct qemu_syscall *call)
{
    struct qemu_ddraw1_Compact *c = (struct qemu_ddraw1_Compact *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_Compact(ddraw->host_ddraw1);
}

#endif

struct qemu_ddraw7_GetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDSD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetDisplayMode(IDirectDraw7 *iface, DDSURFACEDESC2 *DDSD)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.DDSD = (ULONG_PTR)DDSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetDisplayMode *c = (struct qemu_ddraw7_GetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetDisplayMode(ddraw->host_ddraw7, QEMU_G2H(c->DDSD));
}

#endif

struct qemu_ddraw4_GetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetDisplayMode(IDirectDraw4 *iface, DDSURFACEDESC2 *surface_desc)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetDisplayMode *c = (struct qemu_ddraw4_GetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetDisplayMode(ddraw->host_ddraw4, QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw2_GetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetDisplayMode(IDirectDraw2 *iface, DDSURFACEDESC *surface_desc)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetDisplayMode *c = (struct qemu_ddraw2_GetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetDisplayMode(ddraw->host_ddraw2, QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw1_GetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetDisplayMode(IDirectDraw *iface, DDSURFACEDESC *surface_desc)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETDISPLAYMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetDisplayMode *c = (struct qemu_ddraw1_GetDisplayMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetDisplayMode(ddraw->host_ddraw1, QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw7_GetFourCCCodes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t NumCodes;
    uint64_t Codes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetFourCCCodes(IDirectDraw7 *iface, DWORD *NumCodes, DWORD *Codes)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetFourCCCodes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETFOURCCCODES);
    call.iface = (ULONG_PTR)ddraw;
    call.NumCodes = (ULONG_PTR)NumCodes;
    call.Codes = (ULONG_PTR)Codes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetFourCCCodes(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetFourCCCodes *c = (struct qemu_ddraw7_GetFourCCCodes *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetFourCCCodes(ddraw->host_ddraw7, QEMU_G2H(c->NumCodes), QEMU_G2H(c->Codes));
}

#endif

struct qemu_ddraw4_GetFourCCCodes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t codes_count;
    uint64_t codes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetFourCCCodes(IDirectDraw4 *iface, DWORD *codes_count, DWORD *codes)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetFourCCCodes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETFOURCCCODES);
    call.iface = (ULONG_PTR)ddraw;
    call.codes_count = (ULONG_PTR)codes_count;
    call.codes = (ULONG_PTR)codes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetFourCCCodes(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetFourCCCodes *c = (struct qemu_ddraw4_GetFourCCCodes *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetFourCCCodes(ddraw->host_ddraw4, QEMU_G2H(c->codes_count), QEMU_G2H(c->codes));
}

#endif

struct qemu_ddraw2_GetFourCCCodes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t codes_count;
    uint64_t codes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetFourCCCodes(IDirectDraw2 *iface, DWORD *codes_count, DWORD *codes)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetFourCCCodes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETFOURCCCODES);
    call.iface = (ULONG_PTR)ddraw;
    call.codes_count = (ULONG_PTR)codes_count;
    call.codes = (ULONG_PTR)codes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetFourCCCodes(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetFourCCCodes *c = (struct qemu_ddraw2_GetFourCCCodes *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetFourCCCodes(ddraw->host_ddraw2, QEMU_G2H(c->codes_count), QEMU_G2H(c->codes));
}

#endif

struct qemu_ddraw1_GetFourCCCodes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t codes_count;
    uint64_t codes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetFourCCCodes(IDirectDraw *iface, DWORD *codes_count, DWORD *codes)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetFourCCCodes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETFOURCCCODES);
    call.iface = (ULONG_PTR)ddraw;
    call.codes_count = (ULONG_PTR)codes_count;
    call.codes = (ULONG_PTR)codes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetFourCCCodes(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetFourCCCodes *c = (struct qemu_ddraw1_GetFourCCCodes *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetFourCCCodes(ddraw->host_ddraw1, QEMU_G2H(c->codes_count), QEMU_G2H(c->codes));
}

#endif

struct qemu_ddraw7_GetMonitorFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t frequency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetMonitorFrequency(IDirectDraw7 *iface, DWORD *frequency)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetMonitorFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETMONITORFREQUENCY);
    call.iface = (ULONG_PTR)ddraw;
    call.frequency = (ULONG_PTR)frequency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetMonitorFrequency(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetMonitorFrequency *c = (struct qemu_ddraw7_GetMonitorFrequency *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetMonitorFrequency(ddraw->host_ddraw7, QEMU_G2H(c->frequency));
}

#endif

struct qemu_ddraw4_GetMonitorFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t frequency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetMonitorFrequency(IDirectDraw4 *iface, DWORD *frequency)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetMonitorFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETMONITORFREQUENCY);
    call.iface = (ULONG_PTR)ddraw;
    call.frequency = (ULONG_PTR)frequency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetMonitorFrequency(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetMonitorFrequency *c = (struct qemu_ddraw4_GetMonitorFrequency *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetMonitorFrequency(ddraw->host_ddraw4, QEMU_G2H(c->frequency));
}

#endif

struct qemu_ddraw2_GetMonitorFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t frequency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetMonitorFrequency(IDirectDraw2 *iface, DWORD *frequency)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetMonitorFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETMONITORFREQUENCY);
    call.iface = (ULONG_PTR)ddraw;
    call.frequency = (ULONG_PTR)frequency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetMonitorFrequency(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetMonitorFrequency *c = (struct qemu_ddraw2_GetMonitorFrequency *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetMonitorFrequency(ddraw->host_ddraw2, QEMU_G2H(c->frequency));
}

#endif

struct qemu_ddraw1_GetMonitorFrequency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t frequency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetMonitorFrequency(IDirectDraw *iface, DWORD *frequency)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetMonitorFrequency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETMONITORFREQUENCY);
    call.iface = (ULONG_PTR)ddraw;
    call.frequency = (ULONG_PTR)frequency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetMonitorFrequency(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetMonitorFrequency *c = (struct qemu_ddraw1_GetMonitorFrequency *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetMonitorFrequency(ddraw->host_ddraw1, QEMU_G2H(c->frequency));
}

#endif

struct qemu_ddraw7_GetVerticalBlankStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetVerticalBlankStatus(IDirectDraw7 *iface, BOOL *status)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetVerticalBlankStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETVERTICALBLANKSTATUS);
    call.iface = (ULONG_PTR)ddraw;
    call.status = (ULONG_PTR)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetVerticalBlankStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetVerticalBlankStatus *c = (struct qemu_ddraw7_GetVerticalBlankStatus *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetVerticalBlankStatus(ddraw->host_ddraw7, QEMU_G2H(c->status));
}

#endif

struct qemu_ddraw4_GetVerticalBlankStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetVerticalBlankStatus(IDirectDraw4 *iface, BOOL *status)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetVerticalBlankStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETVERTICALBLANKSTATUS);
    call.iface = (ULONG_PTR)ddraw;
    call.status = (ULONG_PTR)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetVerticalBlankStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetVerticalBlankStatus *c = (struct qemu_ddraw4_GetVerticalBlankStatus *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetVerticalBlankStatus(ddraw->host_ddraw4, QEMU_G2H(c->status));
}

#endif

struct qemu_ddraw2_GetVerticalBlankStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetVerticalBlankStatus(IDirectDraw2 *iface, BOOL *status)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetVerticalBlankStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETVERTICALBLANKSTATUS);
    call.iface = (ULONG_PTR)ddraw;
    call.status = (ULONG_PTR)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetVerticalBlankStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetVerticalBlankStatus *c = (struct qemu_ddraw2_GetVerticalBlankStatus *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetVerticalBlankStatus(ddraw->host_ddraw2, QEMU_G2H(c->status));
}

#endif

struct qemu_ddraw1_GetVerticalBlankStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetVerticalBlankStatus(IDirectDraw *iface, BOOL *status)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetVerticalBlankStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETVERTICALBLANKSTATUS);
    call.iface = (ULONG_PTR)ddraw;
    call.status = (ULONG_PTR)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetVerticalBlankStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetVerticalBlankStatus *c = (struct qemu_ddraw1_GetVerticalBlankStatus *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetVerticalBlankStatus(ddraw->host_ddraw1, QEMU_G2H(c->status));
}

#endif

struct qemu_ddraw7_GetAvailableVidMem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
    uint64_t total;
    uint64_t free;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetAvailableVidMem(IDirectDraw7 *iface, DDSCAPS2 *caps, DWORD *total, DWORD *free)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetAvailableVidMem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETAVAILABLEVIDMEM);
    call.iface = (ULONG_PTR)ddraw;
    call.caps = (ULONG_PTR)caps;
    call.total = (ULONG_PTR)total;
    call.free = (ULONG_PTR)free;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetAvailableVidMem(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetAvailableVidMem *c = (struct qemu_ddraw7_GetAvailableVidMem *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetAvailableVidMem(ddraw->host_ddraw7, QEMU_G2H(c->caps), QEMU_G2H(c->total), QEMU_G2H(c->free));
}

#endif

struct qemu_ddraw4_GetAvailableVidMem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
    uint64_t total;
    uint64_t free;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetAvailableVidMem(IDirectDraw4 *iface, DDSCAPS2 *caps, DWORD *total, DWORD *free)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetAvailableVidMem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETAVAILABLEVIDMEM);
    call.iface = (ULONG_PTR)ddraw;
    call.caps = (ULONG_PTR)caps;
    call.total = (ULONG_PTR)total;
    call.free = (ULONG_PTR)free;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetAvailableVidMem(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetAvailableVidMem *c = (struct qemu_ddraw4_GetAvailableVidMem *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetAvailableVidMem(ddraw->host_ddraw4, QEMU_G2H(c->caps), QEMU_G2H(c->total), QEMU_G2H(c->free));
}

#endif

struct qemu_ddraw2_GetAvailableVidMem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
    uint64_t total;
    uint64_t free;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetAvailableVidMem(IDirectDraw2 *iface, DDSCAPS *caps, DWORD *total, DWORD *free)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetAvailableVidMem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETAVAILABLEVIDMEM);
    call.iface = (ULONG_PTR)ddraw;
    call.caps = (ULONG_PTR)caps;
    call.total = (ULONG_PTR)total;
    call.free = (ULONG_PTR)free;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetAvailableVidMem(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetAvailableVidMem *c = (struct qemu_ddraw2_GetAvailableVidMem *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetAvailableVidMem(ddraw->host_ddraw2, QEMU_G2H(c->caps), QEMU_G2H(c->total), QEMU_G2H(c->free));
}

#endif

struct qemu_ddraw7_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_Initialize(IDirectDraw7 *iface, GUID *guid)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_INITIALIZE);
    call.iface = (ULONG_PTR)ddraw;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw7_Initialize *c = (struct qemu_ddraw7_Initialize *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_Initialize(ddraw->host_ddraw7, QEMU_G2H(c->guid));
}

#endif

struct qemu_ddraw4_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_Initialize(IDirectDraw4 *iface, GUID *guid)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_INITIALIZE);
    call.iface = (ULONG_PTR)ddraw;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw4_Initialize *c = (struct qemu_ddraw4_Initialize *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_Initialize(ddraw->host_ddraw4, QEMU_G2H(c->guid));
}

#endif

struct qemu_ddraw2_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_Initialize(IDirectDraw2 *iface, GUID *guid)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_INITIALIZE);
    call.iface = (ULONG_PTR)ddraw;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw2_Initialize *c = (struct qemu_ddraw2_Initialize *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_Initialize(ddraw->host_ddraw2, QEMU_G2H(c->guid));
}

#endif

struct qemu_ddraw1_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_Initialize(IDirectDraw *iface, GUID *guid)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_INITIALIZE);
    call.iface = (ULONG_PTR)ddraw;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw1_Initialize *c = (struct qemu_ddraw1_Initialize *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_Initialize(ddraw->host_ddraw1, QEMU_G2H(c->guid));
}

#endif

struct qemu_d3d1_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d1_Initialize(IDirect3D *iface, REFIID riid)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);
    struct qemu_d3d1_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D1_INITIALIZE);
    call.iface = (ULONG_PTR)ddraw;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d1_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d1_Initialize *c = (struct qemu_d3d1_Initialize *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D_Initialize(ddraw->host_d3d1, QEMU_G2H(c->riid));
}

#endif

struct qemu_ddraw7_FlipToGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_FlipToGDISurface(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_FlipToGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_FLIPTOGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_FlipToGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw7_FlipToGDISurface *c = (struct qemu_ddraw7_FlipToGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_FlipToGDISurface(ddraw->host_ddraw7);
}

#endif

struct qemu_ddraw4_FlipToGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_FlipToGDISurface(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_FlipToGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_FLIPTOGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_FlipToGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw4_FlipToGDISurface *c = (struct qemu_ddraw4_FlipToGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_FlipToGDISurface(ddraw->host_ddraw4);
}

#endif

struct qemu_ddraw2_FlipToGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_FlipToGDISurface(IDirectDraw2 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_FlipToGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_FLIPTOGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_FlipToGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw2_FlipToGDISurface *c = (struct qemu_ddraw2_FlipToGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_FlipToGDISurface(ddraw->host_ddraw2);
}

#endif

struct qemu_ddraw1_FlipToGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_FlipToGDISurface(IDirectDraw *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_FlipToGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_FLIPTOGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_FlipToGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw1_FlipToGDISurface *c = (struct qemu_ddraw1_FlipToGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_FlipToGDISurface(ddraw->host_ddraw1);
}

#endif

struct qemu_ddraw7_WaitForVerticalBlank
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_WaitForVerticalBlank(IDirectDraw7 *iface, DWORD Flags, HANDLE event)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_WaitForVerticalBlank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_WAITFORVERTICALBLANK);
    call.iface = (ULONG_PTR)ddraw;
    call.Flags = Flags;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_WaitForVerticalBlank(struct qemu_syscall *call)
{
    struct qemu_ddraw7_WaitForVerticalBlank *c = (struct qemu_ddraw7_WaitForVerticalBlank *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_WaitForVerticalBlank(ddraw->host_ddraw7, c->Flags, QEMU_G2H(c->event));
}

#endif

struct qemu_ddraw4_WaitForVerticalBlank
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_WaitForVerticalBlank(IDirectDraw4 *iface, DWORD flags, HANDLE event)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_WaitForVerticalBlank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_WAITFORVERTICALBLANK);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_WaitForVerticalBlank(struct qemu_syscall *call)
{
    struct qemu_ddraw4_WaitForVerticalBlank *c = (struct qemu_ddraw4_WaitForVerticalBlank *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_WaitForVerticalBlank(ddraw->host_ddraw4, c->flags, QEMU_G2H(c->event));
}

#endif

struct qemu_ddraw2_WaitForVerticalBlank
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_WaitForVerticalBlank(IDirectDraw2 *iface, DWORD flags, HANDLE event)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_WaitForVerticalBlank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_WAITFORVERTICALBLANK);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_WaitForVerticalBlank(struct qemu_syscall *call)
{
    struct qemu_ddraw2_WaitForVerticalBlank *c = (struct qemu_ddraw2_WaitForVerticalBlank *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_WaitForVerticalBlank(ddraw->host_ddraw2, c->flags, QEMU_G2H(c->event));
}

#endif

struct qemu_ddraw1_WaitForVerticalBlank
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_WaitForVerticalBlank(IDirectDraw *iface, DWORD flags, HANDLE event)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_WaitForVerticalBlank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_WAITFORVERTICALBLANK);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_WaitForVerticalBlank(struct qemu_syscall *call)
{
    struct qemu_ddraw1_WaitForVerticalBlank *c = (struct qemu_ddraw1_WaitForVerticalBlank *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_WaitForVerticalBlank(ddraw->host_ddraw1, c->flags, QEMU_G2H(c->event));
}

#endif

struct qemu_ddraw7_GetScanLine
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Scanline;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetScanLine(IDirectDraw7 *iface, DWORD *Scanline)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetScanLine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETSCANLINE);
    call.iface = (ULONG_PTR)ddraw;
    call.Scanline = (ULONG_PTR)Scanline;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetScanLine(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetScanLine *c = (struct qemu_ddraw7_GetScanLine *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetScanLine(ddraw->host_ddraw7, QEMU_G2H(c->Scanline));
}

#endif

struct qemu_ddraw4_GetScanLine
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t line;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetScanLine(IDirectDraw4 *iface, DWORD *line)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetScanLine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETSCANLINE);
    call.iface = (ULONG_PTR)ddraw;
    call.line = (ULONG_PTR)line;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetScanLine(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetScanLine *c = (struct qemu_ddraw4_GetScanLine *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetScanLine(ddraw->host_ddraw4, QEMU_G2H(c->line));
}

#endif

struct qemu_ddraw2_GetScanLine
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t line;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetScanLine(IDirectDraw2 *iface, DWORD *line)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetScanLine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETSCANLINE);
    call.iface = (ULONG_PTR)ddraw;
    call.line = (ULONG_PTR)line;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetScanLine(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetScanLine *c = (struct qemu_ddraw2_GetScanLine *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetScanLine(ddraw->host_ddraw2, QEMU_G2H(c->line));
}

#endif

struct qemu_ddraw1_GetScanLine
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t line;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetScanLine(IDirectDraw *iface, DWORD *line)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetScanLine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETSCANLINE);
    call.iface = (ULONG_PTR)ddraw;
    call.line = (ULONG_PTR)line;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetScanLine(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetScanLine *c = (struct qemu_ddraw1_GetScanLine *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetScanLine(ddraw->host_ddraw1, QEMU_G2H(c->line));
}

#endif

struct qemu_ddraw7_TestCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_TestCooperativeLevel(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_TestCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_TESTCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_TestCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_ddraw7_TestCooperativeLevel *c = (struct qemu_ddraw7_TestCooperativeLevel *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_TestCooperativeLevel(ddraw->host_ddraw7);
}

#endif

struct qemu_ddraw4_TestCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_TestCooperativeLevel(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_TestCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_TESTCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_TestCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_ddraw4_TestCooperativeLevel *c = (struct qemu_ddraw4_TestCooperativeLevel *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_TestCooperativeLevel(ddraw->host_ddraw4);
}

#endif

struct qemu_ddraw7_GetGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t GDISurface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetGDISurface(IDirectDraw7 *iface, IDirectDrawSurface7 **GDISurface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.GDISurface = (ULONG_PTR)GDISurface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetGDISurface *c = (struct qemu_ddraw7_GetGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetGDISurface(ddraw->host_ddraw7, QEMU_G2H(c->GDISurface));
}

#endif

struct qemu_ddraw4_GetGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetGDISurface(IDirectDraw4 *iface, IDirectDrawSurface4 **surface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetGDISurface *c = (struct qemu_ddraw4_GetGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetGDISurface(ddraw->host_ddraw4, QEMU_G2H(c->surface));
}

#endif

struct qemu_ddraw2_GetGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_GetGDISurface(IDirectDraw2 *iface, IDirectDrawSurface **surface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_GetGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_GETGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_GetGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw2_GetGDISurface *c = (struct qemu_ddraw2_GetGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_GetGDISurface(ddraw->host_ddraw2, QEMU_G2H(c->surface));
}

#endif

struct qemu_ddraw1_GetGDISurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_GetGDISurface(IDirectDraw *iface, IDirectDrawSurface **surface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_GetGDISurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_GETGDISURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_GetGDISurface(struct qemu_syscall *call)
{
    struct qemu_ddraw1_GetGDISurface *c = (struct qemu_ddraw1_GetGDISurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_GetGDISurface(ddraw->host_ddraw1, QEMU_G2H(c->surface));
}

#endif

struct qemu_ddraw7_EnumDisplayModes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t surface_desc;
    uint64_t context;
    uint64_t cb;
    uint64_t wrapper;
};

struct qemu_ddraw_EnumDisplayModes_cb
{
    uint64_t func, desc, context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall ddraw7_EnumDisplayModes_guest_cb(struct qemu_ddraw_EnumDisplayModes_cb *data)
{
    LPDDENUMMODESCALLBACK2 cb = (LPDDENUMMODESCALLBACK2)(ULONG_PTR)data->func;
    return cb((DDSURFACEDESC2 *)(ULONG_PTR)data->desc, (void *)(ULONG_PTR)data->context);
}

static HRESULT WINAPI ddraw7_EnumDisplayModes(IDirectDraw7 *iface, DWORD flags, DDSURFACEDESC2 *surface_desc,
            void *context, LPDDENUMMODESCALLBACK2 cb)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_EnumDisplayModes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_ENUMDISPLAYMODES);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.context = (ULONG_PTR)context;
    call.cb = (ULONG_PTR)cb;
    call.wrapper = (ULONG_PTR)ddraw7_EnumDisplayModes_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI ddraw4_EnumDisplayModes(IDirectDraw4 *iface, DWORD flags, DDSURFACEDESC2 *surface_desc, void *context, LPDDENUMMODESCALLBACK2 callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);

    WINE_TRACE("iface %p, flags %#x, surface_desc %p, context %p, callback %p.\n",
            iface, flags, surface_desc, context, callback);

    return ddraw7_EnumDisplayModes(&ddraw->IDirectDraw7_iface, flags, surface_desc, context, callback);
}

#else

struct qemu_ddraw7_EnumDisplayModes_host_data
{
    uint64_t guest_cb, guest_ctx, wrapper;
};

static HRESULT WINAPI ddraw7_EnumDisplayModes_host_cb(DDSURFACEDESC2 *desc, void *context)
{
    struct qemu_ddraw7_EnumDisplayModes_host_data *ctx = context;
    struct qemu_DDSURFACEDESC2 desc32;
    struct qemu_ddraw_EnumDisplayModes_cb call;
    HRESULT hr;

    call.func = ctx->guest_cb;
    call.context = ctx->guest_ctx;
#if GUEST_BIT == HOST_BIT
    call.desc = QEMU_H2G(desc);
#else
    desc32.dwSize = sizeof(desc32);
    DDSURFACEDESC2_h2g(&desc32, desc);
    call.desc = QEMU_H2G(&desc32);
#endif

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx).\n", call.func, call.context, call.desc);
    hr = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest function returned 0x%x.\n", hr);

    return hr;
}

void qemu_ddraw7_EnumDisplayModes(struct qemu_syscall *call)
{
    struct qemu_ddraw7_EnumDisplayModes *c = (struct qemu_ddraw7_EnumDisplayModes *)call;
    struct qemu_ddraw *ddraw;
    DDSURFACEDESC2 stack, *desc = &stack;
    struct qemu_DDSURFACEDESC2 *desc32;
    struct qemu_ddraw7_EnumDisplayModes_host_data ctx;

    WINE_TRACE("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->surface_desc);
#else
    desc32 = QEMU_G2H(c->surface_desc);
    /* Wine's implementation just assumes the size is right. */
    if (desc32)
        DDSURFACEDESC2_g2h(desc, desc32);
    else
        desc = NULL;
#endif

    ctx.guest_cb = c->cb;
    ctx.guest_ctx = c->context;
    ctx.wrapper = c->wrapper;

    c->super.iret = IDirectDraw7_EnumDisplayModes(ddraw->host_ddraw7, c->flags, desc, &ctx,
            c->cb ? ddraw7_EnumDisplayModes_host_cb : NULL);
}

#endif

struct qemu_ddraw2_EnumDisplayModes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t surface_desc;
    uint64_t context;
    uint64_t callback;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall ddraw2_EnumDisplayModes_guest_cb(struct qemu_ddraw_EnumDisplayModes_cb *data)
{
    LPDDENUMMODESCALLBACK cb = (LPDDENUMMODESCALLBACK)(ULONG_PTR)data->func;
    return cb((DDSURFACEDESC *)(ULONG_PTR)data->desc, (void *)(ULONG_PTR)data->context);
}

static HRESULT WINAPI ddraw2_EnumDisplayModes(IDirectDraw2 *iface, DWORD flags, DDSURFACEDESC *surface_desc, void *context, LPDDENUMMODESCALLBACK callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_EnumDisplayModes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_ENUMDISPLAYMODES);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;
    call.wrapper = (ULONG_PTR)ddraw2_EnumDisplayModes_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI ddraw1_EnumDisplayModes(IDirectDraw *iface, DWORD flags, DDSURFACEDESC *surface_desc, void *context, LPDDENUMMODESCALLBACK callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);

    WINE_TRACE("iface %p, flags %#x, surface_desc %p, context %p, callback %p.\n",
            iface, flags, surface_desc, context, callback);

    return ddraw2_EnumDisplayModes(&ddraw->IDirectDraw2_iface, flags, surface_desc, context, callback);
}

#else

static HRESULT WINAPI ddraw2_EnumDisplayModes_host_cb(DDSURFACEDESC *desc, void *context)
{
    struct qemu_ddraw7_EnumDisplayModes_host_data *ctx = context;
    struct qemu_DDSURFACEDESC desc32;
    struct qemu_ddraw_EnumDisplayModes_cb call;
    HRESULT hr;

    call.func = ctx->guest_cb;
    call.context = ctx->guest_ctx;
#if GUEST_BIT == HOST_BIT
    call.desc = QEMU_H2G(desc);
#else
    desc32.dwSize = sizeof(desc32);
    DDSURFACEDESC_h2g(&desc32, desc);
    call.desc = QEMU_H2G(&desc32);
#endif

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx).\n", call.func, call.context, call.desc);
    hr = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest function returned 0x%x.\n", hr);

    return hr;
}

void qemu_ddraw2_EnumDisplayModes(struct qemu_syscall *call)
{
    struct qemu_ddraw2_EnumDisplayModes *c = (struct qemu_ddraw2_EnumDisplayModes *)call;
    struct qemu_ddraw *ddraw;
    DDSURFACEDESC stack, *desc = &stack;
    struct qemu_DDSURFACEDESC *desc32;
    struct qemu_ddraw7_EnumDisplayModes_host_data ctx;

    WINE_TRACE("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->surface_desc);
#else
    desc32 = QEMU_G2H(c->surface_desc);
    /* Wine's implementation just assumes the size is right. */
    if (desc32)
        DDSURFACEDESC_g2h(desc, desc32);
    else
        desc = NULL;
#endif

    ctx.guest_cb = c->callback;
    ctx.guest_ctx = c->context;
    ctx.wrapper = c->wrapper;

    c->super.iret = IDirectDraw2_EnumDisplayModes(ddraw->host_ddraw2, c->flags, desc, &ctx,
            c->callback ? ddraw2_EnumDisplayModes_host_cb : NULL);
}

#endif

struct qemu_ddraw7_EvaluateMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
    uint64_t Timeout;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_EvaluateMode(IDirectDraw7 *iface, DWORD Flags, DWORD *Timeout)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_EvaluateMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_EVALUATEMODE);
    call.iface = (ULONG_PTR)ddraw;
    call.Flags = Flags;
    call.Timeout = (ULONG_PTR)Timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_EvaluateMode(struct qemu_syscall *call)
{
    struct qemu_ddraw7_EvaluateMode *c = (struct qemu_ddraw7_EvaluateMode *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_EvaluateMode(ddraw->host_ddraw7, c->Flags, QEMU_G2H(c->Timeout));
}

#endif

struct qemu_ddraw7_GetDeviceIdentifier
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDDI;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetDeviceIdentifier(IDirectDraw7 *iface, DDDEVICEIDENTIFIER2 *DDDI, DWORD Flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetDeviceIdentifier call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETDEVICEIDENTIFIER);
    call.iface = (ULONG_PTR)ddraw;
    call.DDDI = (ULONG_PTR)DDDI;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetDeviceIdentifier(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetDeviceIdentifier *c = (struct qemu_ddraw7_GetDeviceIdentifier *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    /* DDDEVICEIDENTIFIER has the same size in 32 and 64 bit. */
    c->super.iret = IDirectDraw7_GetDeviceIdentifier(ddraw->host_ddraw7, QEMU_G2H(c->DDDI), c->Flags);
}

#endif

struct qemu_ddraw4_GetDeviceIdentifier
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t identifier;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetDeviceIdentifier(IDirectDraw4 *iface, DDDEVICEIDENTIFIER *identifier, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetDeviceIdentifier call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETDEVICEIDENTIFIER);
    call.iface = (ULONG_PTR)ddraw;
    call.identifier = (ULONG_PTR)identifier;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetDeviceIdentifier(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetDeviceIdentifier *c = (struct qemu_ddraw4_GetDeviceIdentifier *)call;
    struct qemu_ddraw *ddraw;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    /* DDDEVICEIDENTIFIER has the same size in 32 and 64 bit. */
    c->super.iret = IDirectDraw4_GetDeviceIdentifier(ddraw->host_ddraw4, QEMU_G2H(c->identifier), c->flags);
}

#endif

struct qemu_ddraw7_GetSurfaceFromDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_GetSurfaceFromDC(IDirectDraw7 *iface, HDC dc, IDirectDrawSurface7 **surface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_GetSurfaceFromDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_GETSURFACEFROMDC);
    call.iface = (ULONG_PTR)ddraw;
    call.dc = (ULONG_PTR)dc;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_GetSurfaceFromDC(struct qemu_syscall *call)
{
    struct qemu_ddraw7_GetSurfaceFromDC *c = (struct qemu_ddraw7_GetSurfaceFromDC *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_GetSurfaceFromDC(ddraw->host_ddraw7, QEMU_G2H(c->dc), QEMU_G2H(c->surface));
}

#endif

struct qemu_ddraw4_GetSurfaceFromDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_GetSurfaceFromDC(IDirectDraw4 *iface, HDC dc, IDirectDrawSurface4 **surface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_GetSurfaceFromDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_GETSURFACEFROMDC);
    call.iface = (ULONG_PTR)ddraw;
    call.dc = (ULONG_PTR)dc;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_GetSurfaceFromDC(struct qemu_syscall *call)
{
    struct qemu_ddraw4_GetSurfaceFromDC *c = (struct qemu_ddraw4_GetSurfaceFromDC *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_GetSurfaceFromDC(ddraw->host_ddraw4, QEMU_G2H(c->dc), QEMU_G2H(c->surface));
}

#endif

struct qemu_ddraw7_RestoreAllSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_RestoreAllSurfaces(IDirectDraw7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_RestoreAllSurfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_RESTOREALLSURFACES);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_RestoreAllSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw7_RestoreAllSurfaces *c = (struct qemu_ddraw7_RestoreAllSurfaces *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_RestoreAllSurfaces(ddraw->host_ddraw7);
}

#endif

struct qemu_ddraw4_RestoreAllSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_RestoreAllSurfaces(IDirectDraw4 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_RestoreAllSurfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_RESTOREALLSURFACES);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_RestoreAllSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw4_RestoreAllSurfaces *c = (struct qemu_ddraw4_RestoreAllSurfaces *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_RestoreAllSurfaces(ddraw->host_ddraw4);
}

#endif

struct qemu_ddraw7_StartModeTest
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Modes;
    uint64_t NumModes;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_StartModeTest(IDirectDraw7 *iface, SIZE *Modes, DWORD NumModes, DWORD Flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_StartModeTest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_STARTMODETEST);
    call.iface = (ULONG_PTR)ddraw;
    call.Modes = (ULONG_PTR)Modes;
    call.NumModes = NumModes;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_StartModeTest(struct qemu_syscall *call)
{
    struct qemu_ddraw7_StartModeTest *c = (struct qemu_ddraw7_StartModeTest *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_StartModeTest(ddraw->host_ddraw7, QEMU_G2H(c->Modes), c->NumModes, c->Flags);
}

#endif

struct qemu_ddraw7_CreateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
    uint64_t surface;
    uint64_t outer_unknown;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_CreateSurface(IDirectDraw7 *iface, DDSURFACEDESC2 *surface_desc,
        IDirectDrawSurface7 **surface, IUnknown *outer_unknown)
{
    struct qemu_ddraw7_CreateSurface call;
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_surface *object;

    if(surface_desc == NULL || surface_desc->dwSize != sizeof(*surface_desc))
    {
        WINE_WARN("Application supplied invalid surface descriptor\n");
        return DDERR_INVALIDPARAMS;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_CREATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.surface = (ULONG_PTR)surface;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_surface *)(ULONG_PTR)call.object;
        qemu_surface_guest_init(object, ddraw, 7);
        *surface = &object->IDirectDrawSurface7_iface;

        IDirectDraw7_AddRef(iface);
        object->ifaceToRelease = (IUnknown *)iface;
    }

    return call.super.iret;
}

#else

static void surface_host_init(struct qemu_surface *surface, IUnknown *host)
{
    IUnknown_QueryInterface(host, &IID_IDirectDrawSurface, (void **)&surface->host_surface1);
    IUnknown_QueryInterface(host, &IID_IDirectDrawSurface2, (void **)&surface->host_surface2);
    IUnknown_QueryInterface(host, &IID_IDirectDrawSurface3, (void **)&surface->host_surface3);
    IUnknown_QueryInterface(host, &IID_IDirectDrawSurface4, (void **)&surface->host_surface4);
    IUnknown_QueryInterface(host, &IID_IDirectDrawSurface7, (void **)&surface->host_surface7);
    IUnknown_QueryInterface(host, &IID_IDirectDrawGammaControl, (void **)&surface->host_gamma);

    IUnknown_QueryInterface(host, &IID_IDirect3DTexture, (void **)&surface->host_texture1);
    IUnknown_QueryInterface(host, &IID_IDirect3DTexture, (void **)&surface->host_texture2);

    surface->private_data.lpVtbl = &surface_priv_vtbl;
    IDirectDrawSurface7_SetPrivateData(surface->host_surface7, &surface_priv_uuid,
            (IUnknown *)&surface->private_data.lpVtbl, sizeof(&surface->private_data.lpVtbl),
            DDSPD_IUNKNOWNPOINTER);
}

void qemu_ddraw7_CreateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw7_CreateSurface *c = (struct qemu_ddraw7_CreateSurface *)call;
    IDirectDrawSurface7 *host;
    struct qemu_ddraw *ddraw;
    struct qemu_surface *object;
#if HOST_BIT == GUEST_BIT
    DDSURFACEDESC2 *desc = QEMU_G2H(c->surface_desc);
    ULONG_PTR *out_ptr;
#else
    DDSURFACEDESC2 stack, *desc = &stack;
    qemu_ptr *out_ptr;
    DDSURFACEDESC2_g2h(desc, QEMU_G2H(c->surface_desc));
#endif

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    out_ptr = QEMU_G2H(c->surface);
    __TRY
    {
        *out_ptr = 0;
    }
    __EXCEPT_PAGE_FAULT
    {
        WINE_WARN("Surface pointer %p is invalid.\n", out_ptr);
        c->super.iret = DDERR_INVALIDPARAMS;
        return;
    }
    __ENDTRY;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirectDraw7_CreateSurface(ddraw->host_ddraw7, desc, &host, QEMU_G2H(c->outer_unknown));

    if (SUCCEEDED(c->super.iret))
    {
        surface_host_init(object, (IUnknown *)host);
        IDirectDrawSurface7_Release(host);
        c->object = QEMU_H2G(object);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, object);
    }
}

#endif

struct qemu_ddraw4_CreateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
    uint64_t surface;
    uint64_t outer_unknown;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_CreateSurface(IDirectDraw4 *iface, DDSURFACEDESC2 *surface_desc, IDirectDrawSurface4 **surface, IUnknown *outer_unknown)
{
    struct qemu_ddraw4_CreateSurface call;
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_surface *object;

    if(surface_desc == NULL || surface_desc->dwSize != sizeof(*surface_desc))
    {
        WINE_WARN("Application supplied invalid surface descriptor\n");
        return DDERR_INVALIDPARAMS;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_CREATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.surface = (ULONG_PTR)surface;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_surface *)(ULONG_PTR)call.object;
        qemu_surface_guest_init(object, ddraw, 4);
        *surface = &object->IDirectDrawSurface4_iface;

        IDirectDraw7_AddRef(iface);
        object->ifaceToRelease = (IUnknown *)iface;
    }

    return call.super.iret;
}

#else

void qemu_ddraw4_CreateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw4_CreateSurface *c = (struct qemu_ddraw4_CreateSurface *)call;
    IDirectDrawSurface4 *host;
    struct qemu_ddraw *ddraw;
    struct qemu_surface *object;
#if HOST_BIT == GUEST_BIT
    DDSURFACEDESC2 *desc = QEMU_G2H(c->surface_desc);
    ULONG_PTR *out_ptr;
#else
    DDSURFACEDESC2 stack, *desc = &stack;
    qemu_ptr *out_ptr;
    DDSURFACEDESC2_g2h(desc, QEMU_G2H(c->surface_desc));
#endif

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    out_ptr = QEMU_G2H(c->surface);
    __TRY
    {
        *out_ptr = 0;
    }
    __EXCEPT_PAGE_FAULT
    {
        WINE_WARN("Surface pointer %p is invalid.\n", out_ptr);
        c->super.iret = DDERR_INVALIDPARAMS;
        return;
    }
    __ENDTRY;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirectDraw4_CreateSurface(ddraw->host_ddraw4, desc, &host, QEMU_G2H(c->outer_unknown));

    if (SUCCEEDED(c->super.iret))
    {
        surface_host_init(object, (IUnknown *)host);
        IDirectDrawSurface4_Release(host);
        c->object = QEMU_H2G(object);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, object);
    }
}

#endif

struct qemu_ddraw2_CreateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
    uint64_t surface;
    uint64_t outer_unknown;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_CreateSurface(IDirectDraw2 *iface, DDSURFACEDESC *surface_desc, IDirectDrawSurface **surface, IUnknown *outer_unknown)
{
    struct qemu_ddraw2_CreateSurface call;
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_surface *object;

    if(surface_desc == NULL || surface_desc->dwSize != sizeof(*surface_desc))
    {
        WINE_WARN("Application supplied invalid surface descriptor\n");
        return DDERR_INVALIDPARAMS;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_CREATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.surface = (ULONG_PTR)surface;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_surface *)(ULONG_PTR)call.object;
        qemu_surface_guest_init(object, ddraw, 2);
        *surface = &object->IDirectDrawSurface_iface;
    }

    return call.super.iret;
}

#else

void qemu_ddraw2_CreateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw2_CreateSurface *c = (struct qemu_ddraw2_CreateSurface *)call;
    IDirectDrawSurface *host;
    struct qemu_ddraw *ddraw;
    struct qemu_surface *object;
#if HOST_BIT == GUEST_BIT
    DDSURFACEDESC *desc = QEMU_G2H(c->surface_desc);
    ULONG_PTR *out_ptr;
#else
    DDSURFACEDESC stack, *desc = &stack;
    qemu_ptr *out_ptr;
    DDSURFACEDESC_g2h(desc, QEMU_G2H(c->surface_desc));
#endif

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    out_ptr = QEMU_G2H(c->surface);
    __TRY
    {
        *out_ptr = 0;
    }
    __EXCEPT_PAGE_FAULT
    {
        WINE_WARN("Surface pointer %p is invalid.\n", out_ptr);
        c->super.iret = DDERR_INVALIDPARAMS;
        return;
    }
    __ENDTRY;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirectDraw2_CreateSurface(ddraw->host_ddraw2, desc, &host, QEMU_G2H(c->outer_unknown));

    if (SUCCEEDED(c->super.iret))
    {
        surface_host_init(object, (IUnknown *)host);
        IDirectDrawSurface_Release(host);
        c->object = QEMU_H2G(object);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, object);
    }
}

#endif

struct qemu_ddraw1_CreateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
    uint64_t surface;
    uint64_t outer_unknown;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_CreateSurface(IDirectDraw *iface, DDSURFACEDESC *surface_desc, IDirectDrawSurface **surface, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_CreateSurface call;
    struct qemu_surface *object;

    if(surface_desc == NULL || surface_desc->dwSize != sizeof(*surface_desc))
    {
        WINE_WARN("Application supplied invalid surface descriptor\n");
        return DDERR_INVALIDPARAMS;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_CREATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.surface = (ULONG_PTR)surface;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_surface *)(ULONG_PTR)call.object;
        qemu_surface_guest_init(object, ddraw, 1);
        *surface = &object->IDirectDrawSurface_iface;
    }

    return call.super.iret;
}

#else

void qemu_ddraw1_CreateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw1_CreateSurface *c = (struct qemu_ddraw1_CreateSurface *)call;
    IDirectDrawSurface *host;
    struct qemu_ddraw *ddraw;
    struct qemu_surface *object;
#if HOST_BIT == GUEST_BIT
    DDSURFACEDESC *desc = QEMU_G2H(c->surface_desc);
    ULONG_PTR *out_ptr;
#else
    DDSURFACEDESC stack, *desc = &stack;
    qemu_ptr *out_ptr;
    DDSURFACEDESC_g2h(desc, QEMU_G2H(c->surface_desc));
#endif

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    out_ptr = QEMU_G2H(c->surface);
    __TRY
    {
        *out_ptr = 0;
    }
    __EXCEPT_PAGE_FAULT
    {
        WINE_WARN("Surface pointer %p is invalid.\n", out_ptr);
        c->super.iret = DDERR_INVALIDPARAMS;
        return;
    }
    __ENDTRY;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirectDraw_CreateSurface(ddraw->host_ddraw1, desc, &host, QEMU_G2H(c->outer_unknown));

    if (SUCCEEDED(c->super.iret))
    {
        surface_host_init(object, (IUnknown *)host);
        IDirectDrawSurface_Release(host);
        c->object = QEMU_H2G(object);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, object);
    }
}

#endif

struct qemu_ddraw7_EnumSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
    uint64_t DDSD;
    uint64_t Context;
    uint64_t Callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_EnumSurfaces(IDirectDraw7 *iface, DWORD Flags, DDSURFACEDESC2 *DDSD, void *Context, LPDDENUMSURFACESCALLBACK7 Callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_EnumSurfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_ENUMSURFACES);
    call.iface = (ULONG_PTR)ddraw;
    call.Flags = Flags;
    call.DDSD = (ULONG_PTR)DDSD;
    call.Context = (ULONG_PTR)Context;
    call.Callback = (ULONG_PTR)Callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_EnumSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw7_EnumSurfaces *c = (struct qemu_ddraw7_EnumSurfaces *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_EnumSurfaces(ddraw->host_ddraw7, c->Flags, QEMU_G2H(c->DDSD), QEMU_G2H(c->Context), QEMU_G2H(c->Callback));
}

#endif

struct qemu_ddraw4_EnumSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t surface_desc;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_EnumSurfaces(IDirectDraw4 *iface, DWORD flags, DDSURFACEDESC2 *surface_desc, void *context, LPDDENUMSURFACESCALLBACK2 callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_EnumSurfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_ENUMSURFACES);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_EnumSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw4_EnumSurfaces *c = (struct qemu_ddraw4_EnumSurfaces *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_EnumSurfaces(ddraw->host_ddraw4, c->flags, QEMU_G2H(c->surface_desc), QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw2_EnumSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t surface_desc;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_EnumSurfaces(IDirectDraw2 *iface, DWORD flags, DDSURFACEDESC *surface_desc, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_EnumSurfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_ENUMSURFACES);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_EnumSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw2_EnumSurfaces *c = (struct qemu_ddraw2_EnumSurfaces *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_EnumSurfaces(ddraw->host_ddraw2, c->flags, QEMU_G2H(c->surface_desc), QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw1_EnumSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t surface_desc;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_EnumSurfaces(IDirectDraw *iface, DWORD flags, DDSURFACEDESC *surface_desc, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_EnumSurfaces call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_ENUMSURFACES);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_EnumSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw1_EnumSurfaces *c = (struct qemu_ddraw1_EnumSurfaces *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_EnumSurfaces(ddraw->host_ddraw1, c->flags, QEMU_G2H(c->surface_desc), QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_DirectDrawCreateClipper
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t clipper;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

HRESULT WINAPI qemu_guest_DirectDrawCreateClipper(DWORD flags, IDirectDrawClipper **clipper, IUnknown *outer_unknown)
{
    struct qemu_DirectDrawCreateClipper call;
    struct qemu_clipper *object;

    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWCREATECLIPPER);
    call.flags = flags;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    object = (struct qemu_clipper *)(ULONG_PTR)call.clipper;
    ddraw_clipper_guest_init(object);

    *clipper = &object->IDirectDrawClipper_iface;
    return call.super.iret;
}

#else

void qemu_DirectDrawCreateClipper(struct qemu_syscall *call)
{
    struct qemu_DirectDrawCreateClipper *c = (struct qemu_DirectDrawCreateClipper *)call;
    struct qemu_clipper *clipper;

    WINE_TRACE("\n");

    clipper = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*clipper));
    if (!clipper)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = DirectDrawCreateClipper(c->flags, &clipper->host, QEMU_G2H(c->outer_unknown));
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, clipper);
        clipper = NULL;
    }

    c->clipper = QEMU_H2G(clipper);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_CreateClipper(IDirectDraw *iface, DWORD flags, IDirectDrawClipper **clipper, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);

    WINE_TRACE("iface %p, flags %#x, clipper %p, outer_unknown %p.\n", iface, flags, clipper, outer_unknown);

    return qemu_guest_DirectDrawCreateClipper(flags, clipper, outer_unknown);
}

static HRESULT WINAPI ddraw7_CreateClipper(IDirectDraw7 *iface, DWORD flags, IDirectDrawClipper **clipper, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);

    WINE_TRACE("iface %p, flags %#x, clipper %p, outer_unknown %p.\n", iface, flags, clipper, outer_unknown);

    return ddraw1_CreateClipper(&ddraw->IDirectDraw_iface, flags, clipper, outer_unknown);
}

static HRESULT WINAPI ddraw4_CreateClipper(IDirectDraw4 *iface, DWORD flags, IDirectDrawClipper **clipper, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);

    WINE_TRACE("iface %p, flags %#x, clipper %p, outer_unknown %p.\n", iface, flags, clipper, outer_unknown);

    return ddraw1_CreateClipper(&ddraw->IDirectDraw_iface, flags, clipper, outer_unknown);
}

static HRESULT WINAPI ddraw2_CreateClipper(IDirectDraw2 *iface, DWORD flags, IDirectDrawClipper **clipper, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);

    WINE_TRACE("iface %p, flags %#x, clipper %p, outer_unknown %p.\n", iface, flags, clipper, outer_unknown);

    return ddraw1_CreateClipper(&ddraw->IDirectDraw_iface, flags, clipper, outer_unknown);
}

#endif

struct qemu_ddraw7_CreatePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
    uint64_t ColorTable;
    uint64_t Palette;
    uint64_t pUnkOuter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_CreatePalette(IDirectDraw7 *iface, DWORD Flags, PALETTEENTRY *ColorTable, IDirectDrawPalette **Palette, IUnknown *pUnkOuter)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_CreatePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_CREATEPALETTE);
    call.iface = (ULONG_PTR)ddraw;
    call.Flags = Flags;
    call.ColorTable = (ULONG_PTR)ColorTable;
    call.Palette = (ULONG_PTR)Palette;
    call.pUnkOuter = (ULONG_PTR)pUnkOuter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_CreatePalette(struct qemu_syscall *call)
{
    struct qemu_ddraw7_CreatePalette *c = (struct qemu_ddraw7_CreatePalette *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_CreatePalette(ddraw->host_ddraw7, c->Flags, QEMU_G2H(c->ColorTable), QEMU_G2H(c->Palette), QEMU_G2H(c->pUnkOuter));
}

#endif

struct qemu_ddraw4_CreatePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t entries;
    uint64_t palette;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_CreatePalette(IDirectDraw4 *iface, DWORD flags, PALETTEENTRY *entries, IDirectDrawPalette **palette, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_CreatePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_CREATEPALETTE);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.entries = (ULONG_PTR)entries;
    call.palette = (ULONG_PTR)palette;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_CreatePalette(struct qemu_syscall *call)
{
    struct qemu_ddraw4_CreatePalette *c = (struct qemu_ddraw4_CreatePalette *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_CreatePalette(ddraw->host_ddraw4, c->flags, QEMU_G2H(c->entries), QEMU_G2H(c->palette), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_ddraw2_CreatePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t entries;
    uint64_t palette;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_CreatePalette(IDirectDraw2 *iface, DWORD flags, PALETTEENTRY *entries, IDirectDrawPalette **palette, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_CreatePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_CREATEPALETTE);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.entries = (ULONG_PTR)entries;
    call.palette = (ULONG_PTR)palette;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_CreatePalette(struct qemu_syscall *call)
{
    struct qemu_ddraw2_CreatePalette *c = (struct qemu_ddraw2_CreatePalette *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_CreatePalette(ddraw->host_ddraw2, c->flags, QEMU_G2H(c->entries), QEMU_G2H(c->palette), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_ddraw1_CreatePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t entries;
    uint64_t palette;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_CreatePalette(IDirectDraw *iface, DWORD flags, PALETTEENTRY *entries, IDirectDrawPalette **palette, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_CreatePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_CREATEPALETTE);
    call.iface = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.entries = (ULONG_PTR)entries;
    call.palette = (ULONG_PTR)palette;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_CreatePalette(struct qemu_syscall *call)
{
    struct qemu_ddraw1_CreatePalette *c = (struct qemu_ddraw1_CreatePalette *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_CreatePalette(ddraw->host_ddraw1, c->flags, QEMU_G2H(c->entries), QEMU_G2H(c->palette), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_ddraw7_DuplicateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Src;
    uint64_t Dest;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw7_DuplicateSurface(IDirectDraw7 *iface, IDirectDrawSurface7 *Src, IDirectDrawSurface7 **Dest)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw7(iface);
    struct qemu_ddraw7_DuplicateSurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW7_DUPLICATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.Src = (ULONG_PTR)Src;
    call.Dest = (ULONG_PTR)Dest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw7_DuplicateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw7_DuplicateSurface *c = (struct qemu_ddraw7_DuplicateSurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw7_DuplicateSurface(ddraw->host_ddraw7, QEMU_G2H(c->Src), QEMU_G2H(c->Dest));
}

#endif

struct qemu_ddraw4_DuplicateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t dst;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw4_DuplicateSurface(IDirectDraw4 *iface, IDirectDrawSurface4 *src, IDirectDrawSurface4 **dst)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw4(iface);
    struct qemu_ddraw4_DuplicateSurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW4_DUPLICATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw4_DuplicateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw4_DuplicateSurface *c = (struct qemu_ddraw4_DuplicateSurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw4_DuplicateSurface(ddraw->host_ddraw4, QEMU_G2H(c->src), QEMU_G2H(c->dst));
}

#endif

struct qemu_ddraw2_DuplicateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t dst;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw2_DuplicateSurface(IDirectDraw2 *iface, IDirectDrawSurface *src, IDirectDrawSurface **dst)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw2(iface);
    struct qemu_ddraw2_DuplicateSurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW2_DUPLICATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw2_DuplicateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw2_DuplicateSurface *c = (struct qemu_ddraw2_DuplicateSurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw2_DuplicateSurface(ddraw->host_ddraw2, QEMU_G2H(c->src), QEMU_G2H(c->dst));
}

#endif

struct qemu_ddraw1_DuplicateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t dst;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw1_DuplicateSurface(IDirectDraw *iface, IDirectDrawSurface *src, IDirectDrawSurface **dst)
{
    struct qemu_ddraw *ddraw = impl_from_IDirectDraw(iface);
    struct qemu_ddraw1_DuplicateSurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW1_DUPLICATESURFACE);
    call.iface = (ULONG_PTR)ddraw;
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw1_DuplicateSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw1_DuplicateSurface *c = (struct qemu_ddraw1_DuplicateSurface *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirectDraw_DuplicateSurface(ddraw->host_ddraw1, QEMU_G2H(c->src), QEMU_G2H(c->dst));
}

#endif

struct qemu_d3d7_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t callback;
    uint64_t context;
    uint64_t wrapper;
};

struct qemu_d3d7_EnumDevices_cb
{
    uint64_t func;
    uint64_t context;
    uint64_t desc_str, name;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall d3d7_EnumDevices_guest_cb(struct qemu_d3d7_EnumDevices_cb *data)
{
    LPD3DENUMDEVICESCALLBACK7 func = (LPD3DENUMDEVICESCALLBACK7)(ULONG_PTR)data->func;
    return func((char *)(ULONG_PTR)data->desc_str, (char *)(ULONG_PTR)data->name,
            (D3DDEVICEDESC7 *)(ULONG_PTR)data->desc, (void *)(ULONG_PTR)data->context);
}

static HRESULT WINAPI d3d7_EnumDevices(IDirect3D7 *iface, LPD3DENUMDEVICESCALLBACK7 callback, void *context)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);
    struct qemu_d3d7_EnumDevices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D7_ENUMDEVICES);
    call.iface = (ULONG_PTR)ddraw;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)d3d7_EnumDevices_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_d3d7_enum_host_data
{
    uint64_t func, wrapper, context;
};

static HRESULT WINAPI qemu_d3d7_EnumDevices_host_cb(char *desc_str, char *name, D3DDEVICEDESC7 *desc, void *context)
{
    struct qemu_d3d7_enum_host_data *ctx = context;
    struct qemu_d3d7_EnumDevices_cb call;
    HRESULT ret;
    void *copy_desc = NULL, *copy_name = NULL;
    size_t len;

    call.func = ctx->func;
    call.context = ctx->context;
    call.desc_str = QEMU_H2G(desc_str);
    call.name = QEMU_H2G(name);
    call.desc = QEMU_H2G(desc);

    if (call.desc_str > ~0U)
    {
        WINE_TRACE("Copying description string to guest-readable memory.\n");
        len = strlen(desc_str) + 1;
        copy_desc = HeapAlloc(GetProcessHeap(), 0, len);
        memcpy(copy_desc, desc_str, len);
        call.desc_str = QEMU_H2G(copy_desc);
    }
    if (call.name > ~0U)
    {
        WINE_TRACE("Copying description string to guest-readable memory.\n");
        len = strlen(name) + 1;
        copy_name = HeapAlloc(GetProcessHeap(), 0, len);
        memcpy(copy_name, name, len);
        call.name = QEMU_H2G(copy_name);
    }
    if (call.desc > ~0U)
        WINE_ERR("D3DDEVICEDESC7 is %p, unreachable.\n", desc);

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx(\"%s\"), 0x%lx(\"%s\"), 0x%lx, 0x%lx).\n",
            call.func, call.desc_str, desc_str, call.name, name, call.desc, call.context);
    ret = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest wrapper returned 0x%x.\n", ret);

    HeapFree(GetProcessHeap(), 0, copy_desc);
    HeapFree(GetProcessHeap(), 0, copy_name);

    return ret;
}

void qemu_d3d7_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_d3d7_EnumDevices *c = (struct qemu_d3d7_EnumDevices *)call;
    struct qemu_ddraw *ddraw;
    struct qemu_d3d7_enum_host_data ctx;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    ctx.func = c->callback;
    ctx.wrapper = c->wrapper;
    ctx.context = c->context;

    c->super.iret = IDirect3D7_EnumDevices(ddraw->host_d3d7, c->callback ? qemu_d3d7_EnumDevices_host_cb : NULL, &ctx);
}

#endif

struct qemu_d3d3_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d3_EnumDevices(IDirect3D3 *iface, LPD3DENUMDEVICESCALLBACK callback, void *context)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d3_EnumDevices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_ENUMDEVICES);
    call.iface = (ULONG_PTR)ddraw;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d3_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_d3d3_EnumDevices *c = (struct qemu_d3d3_EnumDevices *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D3_EnumDevices(ddraw->host_d3d3, QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_d3d2_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d2_EnumDevices(IDirect3D2 *iface, LPD3DENUMDEVICESCALLBACK callback, void *context)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);
    struct qemu_d3d2_EnumDevices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D2_ENUMDEVICES);
    call.iface = (ULONG_PTR)ddraw;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d2_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_d3d2_EnumDevices *c = (struct qemu_d3d2_EnumDevices *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D2_EnumDevices(ddraw->host_d3d2, QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_d3d1_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d1_EnumDevices(IDirect3D *iface, LPD3DENUMDEVICESCALLBACK callback, void *context)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);
    struct qemu_d3d1_EnumDevices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D1_ENUMDEVICES);
    call.iface = (ULONG_PTR)ddraw;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d1_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_d3d1_EnumDevices *c = (struct qemu_d3d1_EnumDevices *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D_EnumDevices(ddraw->host_d3d1, QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_d3d3_CreateLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d3_CreateLight(IDirect3D3 *iface, IDirect3DLight **light, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d3_CreateLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_CREATELIGHT);
    call.iface = (ULONG_PTR)ddraw;
    call.light = (ULONG_PTR)light;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d3_CreateLight(struct qemu_syscall *call)
{
    struct qemu_d3d3_CreateLight *c = (struct qemu_d3d3_CreateLight *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D3_CreateLight(ddraw->host_d3d3, QEMU_G2H(c->light), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d2_CreateLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d2_CreateLight(IDirect3D2 *iface, IDirect3DLight **light, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);
    struct qemu_d3d2_CreateLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D2_CREATELIGHT);
    call.iface = (ULONG_PTR)ddraw;
    call.light = (ULONG_PTR)light;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d2_CreateLight(struct qemu_syscall *call)
{
    struct qemu_d3d2_CreateLight *c = (struct qemu_d3d2_CreateLight *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D2_CreateLight(ddraw->host_d3d2, QEMU_G2H(c->light), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d1_CreateLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t light;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d1_CreateLight(IDirect3D *iface, IDirect3DLight **light, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);
    struct qemu_d3d1_CreateLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D1_CREATELIGHT);
    call.iface = (ULONG_PTR)ddraw;
    call.light = (ULONG_PTR)light;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d1_CreateLight(struct qemu_syscall *call)
{
    struct qemu_d3d1_CreateLight *c = (struct qemu_d3d1_CreateLight *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D_CreateLight(ddraw->host_d3d1, QEMU_G2H(c->light), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d3_CreateMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d3_CreateMaterial(IDirect3D3 *iface, IDirect3DMaterial3 **material, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d3_CreateMaterial call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_CREATEMATERIAL);
    call.iface = (ULONG_PTR)ddraw;
    call.material = (ULONG_PTR)material;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d3_CreateMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d3_CreateMaterial *c = (struct qemu_d3d3_CreateMaterial *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D3_CreateMaterial(ddraw->host_d3d3, QEMU_G2H(c->material), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d2_CreateMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d2_CreateMaterial(IDirect3D2 *iface, IDirect3DMaterial2 **material, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);
    struct qemu_d3d2_CreateMaterial call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D2_CREATEMATERIAL);
    call.iface = (ULONG_PTR)ddraw;
    call.material = (ULONG_PTR)material;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d2_CreateMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d2_CreateMaterial *c = (struct qemu_d3d2_CreateMaterial *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D2_CreateMaterial(ddraw->host_d3d2, QEMU_G2H(c->material), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d1_CreateMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d1_CreateMaterial(IDirect3D *iface, IDirect3DMaterial **material, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);
    struct qemu_d3d1_CreateMaterial call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D1_CREATEMATERIAL);
    call.iface = (ULONG_PTR)ddraw;
    call.material = (ULONG_PTR)material;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d1_CreateMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d1_CreateMaterial *c = (struct qemu_d3d1_CreateMaterial *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D_CreateMaterial(ddraw->host_d3d1, QEMU_G2H(c->material), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d3_CreateViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d3_CreateViewport(IDirect3D3 *iface, IDirect3DViewport3 **viewport, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d3_CreateViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_CREATEVIEWPORT);
    call.iface = (ULONG_PTR)ddraw;
    call.viewport = (ULONG_PTR)viewport;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d3_CreateViewport(struct qemu_syscall *call)
{
    struct qemu_d3d3_CreateViewport *c = (struct qemu_d3d3_CreateViewport *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D3_CreateViewport(ddraw->host_d3d3, QEMU_G2H(c->viewport), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d2_CreateViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d2_CreateViewport(IDirect3D2 *iface, IDirect3DViewport2 **viewport, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);
    struct qemu_d3d2_CreateViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D2_CREATEVIEWPORT);
    call.iface = (ULONG_PTR)ddraw;
    call.viewport = (ULONG_PTR)viewport;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d2_CreateViewport(struct qemu_syscall *call)
{
    struct qemu_d3d2_CreateViewport *c = (struct qemu_d3d2_CreateViewport *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D2_CreateViewport(ddraw->host_d3d2, QEMU_G2H(c->viewport), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d1_CreateViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d1_CreateViewport(IDirect3D *iface, IDirect3DViewport **viewport, IUnknown *outer_unknown)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);
    struct qemu_d3d1_CreateViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D1_CREATEVIEWPORT);
    call.iface = (ULONG_PTR)ddraw;
    call.viewport = (ULONG_PTR)viewport;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d1_CreateViewport(struct qemu_syscall *call)
{
    struct qemu_d3d1_CreateViewport *c = (struct qemu_d3d1_CreateViewport *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D_CreateViewport(ddraw->host_d3d1, QEMU_G2H(c->viewport), QEMU_G2H(c->outer_unknown));
}

#endif

struct qemu_d3d3_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fds;
    uint64_t fdr;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d3_FindDevice(IDirect3D3 *iface, D3DFINDDEVICESEARCH *fds, D3DFINDDEVICERESULT *fdr)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d3_FindDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_FINDDEVICE);
    call.iface = (ULONG_PTR)ddraw;
    call.fds = (ULONG_PTR)fds;
    call.fdr = (ULONG_PTR)fdr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d3_FindDevice(struct qemu_syscall *call)
{
    struct qemu_d3d3_FindDevice *c = (struct qemu_d3d3_FindDevice *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D3_FindDevice(ddraw->host_d3d3, QEMU_G2H(c->fds), QEMU_G2H(c->fdr));
}

#endif

struct qemu_d3d2_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fds;
    uint64_t fdr;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d2_FindDevice(IDirect3D2 *iface, D3DFINDDEVICESEARCH *fds, D3DFINDDEVICERESULT *fdr)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);
    struct qemu_d3d2_FindDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D2_FINDDEVICE);
    call.iface = (ULONG_PTR)ddraw;
    call.fds = (ULONG_PTR)fds;
    call.fdr = (ULONG_PTR)fdr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d2_FindDevice(struct qemu_syscall *call)
{
    struct qemu_d3d2_FindDevice *c = (struct qemu_d3d2_FindDevice *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D2_FindDevice(ddraw->host_d3d2, QEMU_G2H(c->fds), QEMU_G2H(c->fdr));
}

#endif

struct qemu_d3d1_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fds;
    uint64_t fdr;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d1_FindDevice(IDirect3D *iface, D3DFINDDEVICESEARCH *fds, D3DFINDDEVICERESULT *fdr)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D(iface);
    struct qemu_d3d1_FindDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D1_FINDDEVICE);
    call.iface = (ULONG_PTR)ddraw;
    call.fds = (ULONG_PTR)fds;
    call.fdr = (ULONG_PTR)fdr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d1_FindDevice(struct qemu_syscall *call)
{
    struct qemu_d3d1_FindDevice *c = (struct qemu_d3d1_FindDevice *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D_FindDevice(ddraw->host_d3d1, QEMU_G2H(c->fds), QEMU_G2H(c->fdr));
}

#endif

struct qemu_d3d_CreateDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t surface;
    uint64_t device;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d7_CreateDevice(IDirect3D7 *iface, REFCLSID riid, IDirectDrawSurface7 *surface,
        IDirect3DDevice7 **device)
{
    struct qemu_d3d_CreateDevice call;
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);
    struct qemu_surface *surface_impl = unsafe_impl_from_IDirectDrawSurface7(surface);
    struct qemu_device *object;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D7_CREATEDEVICE);
    call.iface = (ULONG_PTR)ddraw;
    call.riid = (ULONG_PTR)riid;
    call.surface = (ULONG_PTR)surface_impl;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_device *)(ULONG_PTR)call.device;
        ddraw_device_guest_init(object, ddraw, 7, (IUnknown *)surface, NULL);
        *device = &object->IDirect3DDevice7_iface;
    }
    else
    {
        *device = NULL;
    }

    return call.super.iret;
}

static HRESULT WINAPI d3d3_CreateDevice(IDirect3D3 *iface, REFCLSID riid, IDirectDrawSurface4 *surface,
        IDirect3DDevice3 **device, IUnknown *outer_unknown)
{
    struct qemu_d3d_CreateDevice call;
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_surface *surface_impl = unsafe_impl_from_IDirectDrawSurface4(surface);
    struct qemu_device *object;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_CREATEDEVICE);
    call.iface = (ULONG_PTR)ddraw;
    call.riid = (ULONG_PTR)riid;
    call.surface = (ULONG_PTR)surface_impl;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_device *)(ULONG_PTR)call.device;
        ddraw_device_guest_init(object, ddraw, 3, (IUnknown *)surface, NULL);
        *device = &object->IDirect3DDevice3_iface;
    }
    else
    {
        *device = NULL;
    }

    return call.super.iret;
}

static HRESULT WINAPI d3d2_CreateDevice(IDirect3D2 *iface, REFCLSID riid, IDirectDrawSurface *surface,
        IDirect3DDevice2 **device)
{
    struct qemu_d3d_CreateDevice call;
    struct qemu_ddraw *ddraw = impl_from_IDirect3D2(iface);
    struct qemu_surface *surface_impl = unsafe_impl_from_IDirectDrawSurface(surface);
    struct qemu_device *object;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D2_CREATEDEVICE);
    call.iface = (ULONG_PTR)ddraw;
    call.riid = (ULONG_PTR)riid;
    call.surface = (ULONG_PTR)surface_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_device *)(ULONG_PTR)call.device;
        ddraw_device_guest_init(object, ddraw, 2, (IUnknown *)surface, NULL);
        *device = &object->IDirect3DDevice2_iface;
    }
    else
    {
        *device = NULL;
    }

    return call.super.iret;
}

#else

void qemu_d3d_CreateDevice(struct qemu_syscall *call)
{
    struct qemu_d3d_CreateDevice *c = (struct qemu_d3d_CreateDevice *)call;
    struct qemu_ddraw *ddraw;
    struct qemu_device *object;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);
    surface = QEMU_G2H(c->surface);

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_D3D7_CREATEDEVICE):
            c->super.iret = IDirect3D7_CreateDevice(ddraw->host_d3d7, QEMU_G2H(c->riid),
                    surface ? surface->host_surface7 : NULL, &object->host7);
            break;

        case QEMU_SYSCALL_ID(CALL_D3D3_CREATEDEVICE):
            c->super.iret = IDirect3D3_CreateDevice(ddraw->host_d3d3, QEMU_G2H(c->riid),
                    surface ? surface->host_surface4 : NULL, &object->host3, QEMU_G2H(c->outer_unknown));
            if (SUCCEEDED(c->super.iret))
            {
                IDirect3DDevice3_QueryInterface(object->host3, &IID_IDirect3DDevice, (void **)&object->host1);
                IDirect3DDevice3_QueryInterface(object->host3, &IID_IDirect3DDevice2, (void **)&object->host2);
            }
            break;

        case QEMU_SYSCALL_ID(CALL_D3D2_CREATEDEVICE):
            c->super.iret = IDirect3D2_CreateDevice(ddraw->host_d3d2, QEMU_G2H(c->riid),
                    surface ? surface->host_surface1 : NULL, &object->host2);
            if (SUCCEEDED(c->super.iret))
            {
                IDirect3DDevice2_QueryInterface(object->host2, &IID_IDirect3DDevice, (void **)&object->host1);
            }
            break;
    }

    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, object);
        object = NULL;
    }
    c->device = QEMU_H2G(object);
}

#endif

struct qemu_d3d_CreateVertexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
    uint64_t vertex_buffer;
    uint64_t flags;
    uint64_t outer_unknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d7_CreateVertexBuffer(IDirect3D7 *iface, D3DVERTEXBUFFERDESC *desc,
        IDirect3DVertexBuffer7 **vertex_buffer, DWORD flags)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);
    struct qemu_d3d_CreateVertexBuffer call;
    struct qemu_vertex_buffer *object;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D7_CREATEVERTEXBUFFER);
    call.iface = (ULONG_PTR)ddraw;
    call.desc = (ULONG_PTR)desc;
    call.flags = flags;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_vertex_buffer *)(ULONG_PTR)call.vertex_buffer;
        ddraw_vertex_buffer_guest_init(object, ddraw, 7);
        *vertex_buffer = &object->IDirect3DVertexBuffer7_iface;
    }
    else
    {
        *vertex_buffer = NULL;
    }

    return call.super.iret;
}

static HRESULT WINAPI d3d3_CreateVertexBuffer(IDirect3D3 *iface, D3DVERTEXBUFFERDESC *desc,
        IDirect3DVertexBuffer **vertex_buffer, DWORD flags, IUnknown *outer_unknown)
{
    struct qemu_d3d_CreateVertexBuffer call;
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_vertex_buffer *object;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_CREATEVERTEXBUFFER);
    call.iface = (ULONG_PTR)ddraw;
    call.desc = (ULONG_PTR)desc;
    call.flags = flags;
    call.outer_unknown = (ULONG_PTR)outer_unknown;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        object = (struct qemu_vertex_buffer *)(ULONG_PTR)call.vertex_buffer;
        ddraw_vertex_buffer_guest_init(object, ddraw, 3);
        *vertex_buffer = (IDirect3DVertexBuffer *)&object->IDirect3DVertexBuffer7_iface;
    }
    else
    {
        *vertex_buffer = NULL;
    }

    return call.super.iret;
}

#else

void qemu_d3d_CreateVertexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d_CreateVertexBuffer *c = (struct qemu_d3d_CreateVertexBuffer *)call;
    struct qemu_ddraw *ddraw;
    struct qemu_vertex_buffer *object;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    object = HeapAlloc(GetProcessHeap(), 0, sizeof(*object));
    if (!object)
    {
        WINE_WARN("Out of memory.\n");
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    /* D3DVERTEXBUFFERDESC has the same size in 32 and 64 bit. */
    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_D3D3_CREATEVERTEXBUFFER):
            c->super.iret = IDirect3D3_CreateVertexBuffer(ddraw->host_d3d3,
                    QEMU_G2H(c->desc), (IDirect3DVertexBuffer **)&object->host, c->flags,
                    QEMU_G2H(c->outer_unknown));
            break;

        case QEMU_SYSCALL_ID(CALL_D3D7_CREATEVERTEXBUFFER):
            c->super.iret = IDirect3D7_CreateVertexBuffer(ddraw->host_d3d7,
                    QEMU_G2H(c->desc), &object->host, c->flags);
            break;
    }

    if (FAILED(c->super.id))
    {
        HeapFree(GetProcessHeap(), 0, object);
        return;
    }

    c->vertex_buffer = QEMU_H2G(object);
}

#endif

struct qemu_d3d_EnumZBufferFormats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device_iid;
    uint64_t callback;
    uint64_t context;
    uint64_t wrapper;
};

struct qemu_d3d_EnumZBufferFormats_cb
{
    uint64_t func;
    uint64_t fmt;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall qemu_d3d_EnumZBufferFormats_host_cb(struct qemu_d3d_EnumZBufferFormats_cb *data)
{
    LPD3DENUMPIXELFORMATSCALLBACK func = (LPD3DENUMPIXELFORMATSCALLBACK)(ULONG_PTR)data->func;
    return func((DDPIXELFORMAT *)(ULONG_PTR)data->fmt, (void *)(ULONG_PTR)data->context);
}

static HRESULT WINAPI d3d7_EnumZBufferFormats(IDirect3D7 *iface, REFCLSID device_iid, LPD3DENUMPIXELFORMATSCALLBACK callback, void *context)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);
    struct qemu_d3d_EnumZBufferFormats call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D7_ENUMZBUFFERFORMATS);
    call.iface = (ULONG_PTR)ddraw;
    call.device_iid = (ULONG_PTR)device_iid;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)qemu_d3d_EnumZBufferFormats_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI d3d3_EnumZBufferFormats(IDirect3D3 *iface, REFCLSID device_iid, LPD3DENUMPIXELFORMATSCALLBACK callback, void *context)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d_EnumZBufferFormats call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_ENUMZBUFFERFORMATS);
    call.iface = (ULONG_PTR)ddraw;
    call.device_iid = (ULONG_PTR)device_iid;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)qemu_d3d_EnumZBufferFormats_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static HRESULT CALLBACK qemu_d3d_EnumZBufferFormats_host_cb(DDPIXELFORMAT *format, void *context)
{
    struct qemu_d3d7_enum_host_data *ctx = context;
    struct qemu_d3d_EnumZBufferFormats_cb call;
    HRESULT ret;

    call.func = ctx->func;
    call.fmt = QEMU_H2G(format);
    call.context = ctx->context;

    WINE_TRACE("Calling guest wrapper 0x%lx(0x%lx, 0x%lx).\n", call.func, call.fmt, call.context);
    ret = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest wrapper returned 0x%x.\n", ret);

    return ret;
}

void qemu_d3d_EnumZBufferFormats(struct qemu_syscall *call)
{
    struct qemu_d3d_EnumZBufferFormats *c = (struct qemu_d3d_EnumZBufferFormats *)call;
    struct qemu_ddraw *ddraw;
    struct qemu_d3d7_enum_host_data ctx;

    WINE_TRACE("\n");
    ddraw = QEMU_G2H(c->iface);

    ctx.func = c->callback;
    ctx.wrapper = c->wrapper;
    ctx.context = c->context;

    c->super.iret = IDirect3D3_EnumZBufferFormats(ddraw->host_d3d7, QEMU_G2H(c->device_iid),
            c->callback ? qemu_d3d_EnumZBufferFormats_host_cb : NULL, &ctx);
}

#endif

struct qemu_d3d7_EvictManagedTextures
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d7_EvictManagedTextures(IDirect3D7 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D7(iface);
    struct qemu_d3d7_EvictManagedTextures call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D7_EVICTMANAGEDTEXTURES);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d7_EvictManagedTextures(struct qemu_syscall *call)
{
    struct qemu_d3d7_EvictManagedTextures *c = (struct qemu_d3d7_EvictManagedTextures *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D7_EvictManagedTextures(ddraw->host_d3d7);
}

#endif

struct qemu_d3d3_EvictManagedTextures
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d3_EvictManagedTextures(IDirect3D3 *iface)
{
    struct qemu_ddraw *ddraw = impl_from_IDirect3D3(iface);
    struct qemu_d3d3_EvictManagedTextures call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D3_EVICTMANAGEDTEXTURES);
    call.iface = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d3_EvictManagedTextures(struct qemu_syscall *call)
{
    struct qemu_d3d3_EvictManagedTextures *c = (struct qemu_d3d3_EvictManagedTextures *)call;
    struct qemu_ddraw *ddraw;

    WINE_FIXME("Unverified!\n");
    ddraw = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D3_EvictManagedTextures(ddraw->host_d3d3);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirectDraw7Vtbl ddraw7_vtbl =
{
    /* IUnknown */
    ddraw7_QueryInterface,
    ddraw7_AddRef,
    ddraw7_Release,
    /* IDirectDraw */
    ddraw7_Compact,
    ddraw7_CreateClipper,
    ddraw7_CreatePalette,
    ddraw7_CreateSurface,
    ddraw7_DuplicateSurface,
    ddraw7_EnumDisplayModes,
    ddraw7_EnumSurfaces,
    ddraw7_FlipToGDISurface,
    ddraw7_GetCaps,
    ddraw7_GetDisplayMode,
    ddraw7_GetFourCCCodes,
    ddraw7_GetGDISurface,
    ddraw7_GetMonitorFrequency,
    ddraw7_GetScanLine,
    ddraw7_GetVerticalBlankStatus,
    ddraw7_Initialize,
    ddraw7_RestoreDisplayMode,
    ddraw7_SetCooperativeLevel,
    ddraw7_SetDisplayMode,
    ddraw7_WaitForVerticalBlank,
    /* IDirectDraw2 */
    ddraw7_GetAvailableVidMem,
    /* IDirectDraw3 */
    ddraw7_GetSurfaceFromDC,
    /* IDirectDraw4 */
    ddraw7_RestoreAllSurfaces,
    ddraw7_TestCooperativeLevel,
    ddraw7_GetDeviceIdentifier,
    /* IDirectDraw7 */
    ddraw7_StartModeTest,
    ddraw7_EvaluateMode
};

static const struct IDirectDraw4Vtbl ddraw4_vtbl =
{
    /* IUnknown */
    ddraw4_QueryInterface,
    ddraw4_AddRef,
    ddraw4_Release,
    /* IDirectDraw */
    ddraw4_Compact,
    ddraw4_CreateClipper,
    ddraw4_CreatePalette,
    ddraw4_CreateSurface,
    ddraw4_DuplicateSurface,
    ddraw4_EnumDisplayModes,
    ddraw4_EnumSurfaces,
    ddraw4_FlipToGDISurface,
    ddraw4_GetCaps,
    ddraw4_GetDisplayMode,
    ddraw4_GetFourCCCodes,
    ddraw4_GetGDISurface,
    ddraw4_GetMonitorFrequency,
    ddraw4_GetScanLine,
    ddraw4_GetVerticalBlankStatus,
    ddraw4_Initialize,
    ddraw4_RestoreDisplayMode,
    ddraw4_SetCooperativeLevel,
    ddraw4_SetDisplayMode,
    ddraw4_WaitForVerticalBlank,
    /* IDirectDraw2 */
    ddraw4_GetAvailableVidMem,
    /* IDirectDraw3 */
    ddraw4_GetSurfaceFromDC,
    /* IDirectDraw4 */
    ddraw4_RestoreAllSurfaces,
    ddraw4_TestCooperativeLevel,
    ddraw4_GetDeviceIdentifier,
};

static const struct IDirectDraw2Vtbl ddraw2_vtbl =
{
    /* IUnknown */
    ddraw2_QueryInterface,
    ddraw2_AddRef,
    ddraw2_Release,
    /* IDirectDraw */
    ddraw2_Compact,
    ddraw2_CreateClipper,
    ddraw2_CreatePalette,
    ddraw2_CreateSurface,
    ddraw2_DuplicateSurface,
    ddraw2_EnumDisplayModes,
    ddraw2_EnumSurfaces,
    ddraw2_FlipToGDISurface,
    ddraw2_GetCaps,
    ddraw2_GetDisplayMode,
    ddraw2_GetFourCCCodes,
    ddraw2_GetGDISurface,
    ddraw2_GetMonitorFrequency,
    ddraw2_GetScanLine,
    ddraw2_GetVerticalBlankStatus,
    ddraw2_Initialize,
    ddraw2_RestoreDisplayMode,
    ddraw2_SetCooperativeLevel,
    ddraw2_SetDisplayMode,
    ddraw2_WaitForVerticalBlank,
    /* IDirectDraw2 */
    ddraw2_GetAvailableVidMem,
};

static const struct IDirectDrawVtbl ddraw1_vtbl =
{
    /* IUnknown */
    ddraw1_QueryInterface,
    ddraw1_AddRef,
    ddraw1_Release,
    /* IDirectDraw */
    ddraw1_Compact,
    ddraw1_CreateClipper,
    ddraw1_CreatePalette,
    ddraw1_CreateSurface,
    ddraw1_DuplicateSurface,
    ddraw1_EnumDisplayModes,
    ddraw1_EnumSurfaces,
    ddraw1_FlipToGDISurface,
    ddraw1_GetCaps,
    ddraw1_GetDisplayMode,
    ddraw1_GetFourCCCodes,
    ddraw1_GetGDISurface,
    ddraw1_GetMonitorFrequency,
    ddraw1_GetScanLine,
    ddraw1_GetVerticalBlankStatus,
    ddraw1_Initialize,
    ddraw1_RestoreDisplayMode,
    ddraw1_SetCooperativeLevel,
    ddraw1_SetDisplayMode,
    ddraw1_WaitForVerticalBlank,
};

static const struct IDirect3D7Vtbl d3d7_vtbl =
{
    /* IUnknown methods */
    d3d7_QueryInterface,
    d3d7_AddRef,
    d3d7_Release,
    /* IDirect3D7 methods */
    d3d7_EnumDevices,
    d3d7_CreateDevice,
    d3d7_CreateVertexBuffer,
    d3d7_EnumZBufferFormats,
    d3d7_EvictManagedTextures
};

static const struct IDirect3D3Vtbl d3d3_vtbl =
{
    /* IUnknown methods */
    d3d3_QueryInterface,
    d3d3_AddRef,
    d3d3_Release,
    /* IDirect3D3 methods */
    d3d3_EnumDevices,
    d3d3_CreateLight,
    d3d3_CreateMaterial,
    d3d3_CreateViewport,
    d3d3_FindDevice,
    d3d3_CreateDevice,
    d3d3_CreateVertexBuffer,
    d3d3_EnumZBufferFormats,
    d3d3_EvictManagedTextures
};

static const struct IDirect3D2Vtbl d3d2_vtbl =
{
    /* IUnknown methods */
    d3d2_QueryInterface,
    d3d2_AddRef,
    d3d2_Release,
    /* IDirect3D2 methods */
    d3d2_EnumDevices,
    d3d2_CreateLight,
    d3d2_CreateMaterial,
    d3d2_CreateViewport,
    d3d2_FindDevice,
    d3d2_CreateDevice
};

static const struct IDirect3DVtbl d3d1_vtbl =
{
    /* IUnknown methods */
    d3d1_QueryInterface,
    d3d1_AddRef,
    d3d1_Release,
    /* IDirect3D methods */
    d3d1_Initialize,
    d3d1_EnumDevices,
    d3d1_CreateLight,
    d3d1_CreateMaterial,
    d3d1_CreateViewport,
    d3d1_FindDevice
};

struct qemu_ddraw *unsafe_impl_from_IDirectDraw(IDirectDraw *iface)
{
    if (!iface)
        return NULL;
    if (iface->lpVtbl != &ddraw1_vtbl)
        WINE_ERR("Incorrect clipper vtable %p, expect %p.\n", iface->lpVtbl, &ddraw1_vtbl);

    return impl_from_IDirectDraw(iface);
}

void ddraw_guest_init(struct qemu_ddraw *ddraw)
{
    ddraw->IDirectDraw7_iface.lpVtbl = &ddraw7_vtbl;
    ddraw->IDirectDraw_iface.lpVtbl = &ddraw1_vtbl;
    ddraw->IDirectDraw2_iface.lpVtbl = &ddraw2_vtbl;
    ddraw->IDirectDraw4_iface.lpVtbl = &ddraw4_vtbl;
    ddraw->IDirect3D_iface.lpVtbl = &d3d1_vtbl;
    ddraw->IDirect3D2_iface.lpVtbl = &d3d2_vtbl;
    ddraw->IDirect3D3_iface.lpVtbl = &d3d3_vtbl;
    ddraw->IDirect3D7_iface.lpVtbl = &d3d7_vtbl;
    ddraw->numIfaces = 1;
    ddraw->ref1 = 1;
}

#endif
