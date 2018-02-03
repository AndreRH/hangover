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

struct qemu_GetSurfaceFromDC
{
    struct qemu_syscall super;
    uint64_t dc;
    uint64_t surface;
    uint64_t device_dc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetSurfaceFromDC(HDC dc, IDirectDrawSurface4 **surface, HDC *device_dc)
{
    struct qemu_GetSurfaceFromDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSURFACEFROMDC);
    call.dc = (ULONG_PTR)dc;
    call.surface = (ULONG_PTR)surface;
    call.device_dc = (ULONG_PTR)device_dc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* This function is not in the PSDK headers or Wine's headers, but it is in the import library. */
extern HRESULT WINAPI GetSurfaceFromDC(HDC dc, struct IDirectDrawSurface **surface, HDC *device_dc);
static void qemu_GetSurfaceFromDC(struct qemu_syscall *call)
{
    struct qemu_GetSurfaceFromDC *c = (struct qemu_GetSurfaceFromDC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSurfaceFromDC(QEMU_G2H(c->dc), QEMU_G2H(c->surface), QEMU_G2H(c->device_dc));
}

#endif

struct qemu_DirectDrawCreate
{
    struct qemu_syscall super;
    uint64_t driver_guid;
    uint64_t object;
    uint64_t outer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawCreate(GUID *driver_guid, IDirectDraw **ddraw, IUnknown *outer)
{
    struct qemu_DirectDrawCreate call;
    struct qemu_ddraw *object;

    WINE_TRACE("driver_guid %s, ddraw %p, outer %p.\n", wine_dbgstr_guid(driver_guid), ddraw, outer);

    *ddraw = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWCREATE);
    call.driver_guid = (ULONG_PTR)driver_guid;
    call.outer = (ULONG_PTR)outer;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    object = (struct qemu_ddraw *)(ULONG_PTR)call.object;
    ddraw_guest_init(object);
    *ddraw = &object->IDirectDraw_iface;

    return call.super.iret;
}

#else

static void qemu_DirectDrawCreate(struct qemu_syscall *call)
{
    struct qemu_DirectDrawCreate *c = (struct qemu_DirectDrawCreate *)call;
    struct qemu_ddraw *object;
    WINE_TRACE("\n");

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = DirectDrawCreate(QEMU_G2H(c->driver_guid), &object->host_ddraw1, QEMU_G2H(c->outer));
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, object);
        return;
    }

    IDirectDraw_QueryInterface(object->host_ddraw1, &IID_IDirectDraw2, (void **)&object->host_ddraw2);
    IDirectDraw_QueryInterface(object->host_ddraw1, &IID_IDirectDraw4, (void **)&object->host_ddraw4);
    IDirectDraw_QueryInterface(object->host_ddraw1, &IID_IDirectDraw7, (void **)&object->host_ddraw7);

    IDirectDraw_QueryInterface(object->host_ddraw1, &IID_IDirect3D, (void **)&object->host_d3d1);
    IDirectDraw_QueryInterface(object->host_ddraw1, &IID_IDirect3D2, (void **)&object->host_d3d2);
    IDirectDraw_QueryInterface(object->host_ddraw1, &IID_IDirect3D3, (void **)&object->host_d3d3);

    c->object = QEMU_H2G(object);
}

#endif

struct qemu_DirectDrawCreateEx
{
    struct qemu_syscall super;
    uint64_t driver_guid;
    uint64_t object;
    uint64_t outer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawCreateEx(GUID *driver_guid, void **ddraw, REFIID interface_iid, IUnknown *outer)
{
    struct qemu_DirectDrawCreateEx call;
    struct qemu_ddraw *object;
    HRESULT hr;

    WINE_TRACE("driver_guid %s, ddraw %p, interface_iid %s, outer %p.\n",
            wine_dbgstr_guid(driver_guid), ddraw, wine_dbgstr_guid(interface_iid), outer);

    if (!IsEqualGUID(interface_iid, &IID_IDirectDraw7))
        return DDERR_INVALIDPARAMS;

    *ddraw = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWCREATEEX);
    call.driver_guid = (ULONG_PTR)driver_guid;
    call.outer = (ULONG_PTR)outer;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    object = (struct qemu_ddraw *)(ULONG_PTR)call.object;
    ddraw_guest_init(object);

    hr = IDirectDraw_QueryInterface(&object->IDirectDraw_iface, interface_iid, ddraw);
    IDirectDraw_Release(&object->IDirectDraw_iface);

    return hr;
}

#else

static void qemu_DirectDrawCreateEx(struct qemu_syscall *call)
{
    struct qemu_DirectDrawCreateEx *c = (struct qemu_DirectDrawCreateEx *)call;
    struct qemu_ddraw *object;
    WINE_TRACE("\n");

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = DirectDrawCreateEx(QEMU_G2H(c->driver_guid), (void **)&object->host_ddraw7,
            &IID_IDirectDraw7, QEMU_G2H(c->outer));
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, object);
        return;
    }

    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirectDraw, (void **)&object->host_ddraw1);
    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirectDraw2, (void **)&object->host_ddraw2);
    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirectDraw4, (void **)&object->host_ddraw4);

    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirect3D, (void **)&object->host_d3d1);
    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirect3D2, (void **)&object->host_d3d2);
    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirect3D3, (void **)&object->host_d3d3);
    IDirectDraw_QueryInterface(object->host_ddraw7, &IID_IDirect3D7, (void **)&object->host_d3d7);

    c->object = QEMU_H2G(object);
}

#endif

struct qemu_DirectDrawEnumerate
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
    uint64_t wrapper;
};

struct qemu_DirectDrawEnumerate_cb
{
    uint64_t func;
    uint64_t guid;
    uint64_t desc;
    uint64_t name;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static BOOL __fastcall DirectDrawEnumerate_host_cb(struct qemu_DirectDrawEnumerate_cb *data)
{
    LPDDENUMCALLBACKA cb = (LPDDENUMCALLBACKA)(ULONG_PTR)data->func;
    return cb((GUID *)(ULONG_PTR)data->guid, (char *)(ULONG_PTR)data->desc, (char *)(ULONG_PTR)data->name,
            (void *)(ULONG_PTR)data->context);
}

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA callback, void *context)
{
    struct qemu_DirectDrawEnumerate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEA);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)DirectDrawEnumerate_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW callback, void *context)
{
    struct qemu_DirectDrawEnumerate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEW);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.wrapper = (ULONG_PTR)DirectDrawEnumerate_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_DirectDrawEnumerate_host_data
{
    uint64_t guest_func, wrapper, guest_context;
    BOOL wchar;
};

static BOOL WINAPI qemu_DirectDrawEnumerate_host_cb(GUID *guid, char *desc, char *name, void *context)
{
    struct qemu_DirectDrawEnumerate_host_data *ctx = context;
    struct qemu_DirectDrawEnumerate_cb call;
    void *copy_desc = NULL, *copy_name = NULL;
    BOOL ret;
    size_t len;

    call.func = ctx->guest_func;
    call.context = ctx->guest_context;
    call.guid = QEMU_H2G(guid);
    call.desc = QEMU_H2G(desc);
    call.name = QEMU_H2G(name);

#if GUEST_BIT != HOST_BIT
    if (call.desc > ~0U)
    {
        WINE_TRACE("Copying description string to guest-readable memory.\n");
        if (ctx->wchar)
            len = (lstrlenW((WCHAR *)desc) + 1) * sizeof(WCHAR);
        else
            len = strlen(desc) + 1;

        copy_desc = HeapAlloc(GetProcessHeap(), 0, len);
        memcpy(copy_desc, desc, len);
        call.desc = QEMU_H2G(copy_desc);
    }
    if (call.name > ~0U)
    {
        WINE_TRACE("Copying description string to guest-readable memory.\n");
        if (ctx->wchar)
            len = (lstrlenW((WCHAR *)name) + 1) * sizeof(WCHAR);
        else
            len = strlen(name) + 1;

        copy_name = HeapAlloc(GetProcessHeap(), 0, len);
        memcpy(copy_name, name, len);
        call.name = QEMU_H2G(copy_name);
    }
    if (call.guid > ~0U)
        WINE_ERR("GUID is %p, unreachable.\n", guid);
#endif

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx, 0x%lx, 0x%lx).\n",
            call.func, call.guid, call.desc, call.name, call.context);
    ret = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %u\n", ret);

    HeapFree(GetProcessHeap(), 0, copy_desc);
    HeapFree(GetProcessHeap(), 0, copy_name);

    return ret;
}

static void qemu_DirectDrawEnumerate(struct qemu_syscall *call)
{
    struct qemu_DirectDrawEnumerate *c = (struct qemu_DirectDrawEnumerate *)call;
    struct qemu_DirectDrawEnumerate_host_data ctx;

    WINE_TRACE("\n");
    ctx.guest_func = c->callback;
    ctx.wrapper = c->wrapper;
    ctx.guest_context = c->context;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEA))
    {
        ctx.wchar = FALSE;
        c->super.iret = DirectDrawEnumerateA(c->callback ? qemu_DirectDrawEnumerate_host_cb : NULL, &ctx);
    }
    else
    {
        ctx.wchar = TRUE;
        c->super.iret = DirectDrawEnumerateW(c->callback ?
                (LPDDENUMCALLBACKW)qemu_DirectDrawEnumerate_host_cb : NULL, &ctx);
    }
}

#endif

struct qemu_DirectDrawEnumerateEx
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
    uint64_t flags;
    uint64_t wrapper;
};

struct qemu_DirectDrawEnumerateEx_cb
{
    uint64_t func;
    uint64_t guid;
    uint64_t desc;
    uint64_t name;
    uint64_t context;
    uint64_t monitor;
};

#ifdef QEMU_DLL_GUEST

static BOOL __fastcall DirectDrawEnumerateEx_host_cb(struct qemu_DirectDrawEnumerateEx_cb *data)
{
    LPDDENUMCALLBACKEXA cb = (LPDDENUMCALLBACKEXA)(ULONG_PTR)data->func;
    return cb((GUID *)(ULONG_PTR)data->guid, (char *)(ULONG_PTR)data->desc, (char *)(ULONG_PTR)data->name,
            (void *)(ULONG_PTR)data->context, (HMONITOR)(ULONG_PTR)data->monitor);
}

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA callback, void *context, DWORD flags)
{
    struct qemu_DirectDrawEnumerateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEEXA);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.flags = flags;
    call.wrapper = (ULONG_PTR)DirectDrawEnumerateEx_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW callback, void *context, DWORD flags)
{
    struct qemu_DirectDrawEnumerateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEEXW);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.flags = flags;
    call.wrapper = (ULONG_PTR)DirectDrawEnumerateEx_host_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL WINAPI qemu_DirectDrawEnumerateEx_host_cb(GUID *guid, char *desc, char *name,
        void *context, HMONITOR monitor)
{
    struct qemu_DirectDrawEnumerate_host_data *ctx = context;
    struct qemu_DirectDrawEnumerateEx_cb call;
    void *copy_desc = NULL, *copy_name = NULL;
    BOOL ret;
    size_t len;

    call.func = ctx->guest_func;
    call.context = ctx->guest_context;
    call.guid = QEMU_H2G(guid);
    call.desc = QEMU_H2G(desc);
    call.name = QEMU_H2G(name);
    call.monitor = QEMU_H2G(monitor);

#if GUEST_BIT != HOST_BIT
    if (call.desc > ~0U)
    {
        WINE_TRACE("Copying description string to guest-readable memory.\n");
        if (ctx->wchar)
            len = (lstrlenW((WCHAR *)desc) + 1) * sizeof(WCHAR);
        else
            len = strlen(desc) + 1;

        copy_desc = HeapAlloc(GetProcessHeap(), 0, len);
        memcpy(copy_desc, desc, len);
        call.desc = QEMU_H2G(copy_desc);
    }
    if (call.name > ~0U)
    {
        WINE_TRACE("Copying description string to guest-readable memory.\n");
        if (ctx->wchar)
            len = (lstrlenW((WCHAR *)name) + 1) * sizeof(WCHAR);
        else
            len = strlen(name) + 1;

        copy_name = HeapAlloc(GetProcessHeap(), 0, len);
        memcpy(copy_name, name, len);
        call.name = QEMU_H2G(copy_name);
    }
    if (call.guid > ~0U)
        WINE_ERR("GUID is %p, unreachable.\n", guid);
#endif

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx).\n",
            call.func, call.guid, call.desc, call.name, call.context, call.monitor);
    ret = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %u\n", ret);

    HeapFree(GetProcessHeap(), 0, copy_desc);
    HeapFree(GetProcessHeap(), 0, copy_name);

    return ret;
}

static void qemu_DirectDrawEnumerateEx(struct qemu_syscall *call)
{
    struct qemu_DirectDrawEnumerateEx *c = (struct qemu_DirectDrawEnumerateEx *)call;
    struct qemu_DirectDrawEnumerate_host_data ctx;

    WINE_TRACE("\n");
    ctx.guest_func = c->callback;
    ctx.wrapper = c->wrapper;
    ctx.guest_context = c->context;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEEXA))
    {
        ctx.wchar = FALSE;
        c->super.iret = DirectDrawEnumerateExA(c->callback ? qemu_DirectDrawEnumerateEx_host_cb : NULL, &ctx, c->flags);
    }
    else
    {
        ctx.wchar = TRUE;
        c->super.iret = DirectDrawEnumerateExW(c->callback ?
                (LPDDENUMCALLBACKEXW)qemu_DirectDrawEnumerateEx_host_cb : NULL, &ctx, c->flags);
    }
}

#endif

enum create_what
{
    CF_DDRAW,
    CF_DDRAW7,
    CF_CLIPPER,
};

struct qemu_CF_CreateObject
{
    struct qemu_syscall super;
    uint64_t what;
    uint64_t fac_id;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT CF_CreateObject(IUnknown* UnkOuter, REFIID iid, void **obj, enum create_what what, const CLSID *fac_id)
{
    struct qemu_CF_CreateObject call;
    struct qemu_ddraw *ddraw;
    struct qemu_clipper *clipper;
    IUnknown *unk;
    HRESULT hr;

    WINE_TRACE("outer_unknown %p, riid %s, object %p.\n", UnkOuter, wine_dbgstr_guid(iid), obj);

    call.super.id = QEMU_SYSCALL_ID(CALL_CF_CREATEOBJECT);
    call.what = what;
    call.fac_id = (ULONG_PTR)fac_id;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *obj = NULL;
        return call.super.iret;
    }

    if (what == CF_CLIPPER)
    {
        clipper = (struct qemu_clipper *)(ULONG_PTR)call.object;
        ddraw_clipper_guest_init(clipper);
        unk = (IUnknown *)&clipper->IDirectDrawClipper_iface;
    }
    else
    {
        ddraw = (struct qemu_ddraw *)(ULONG_PTR)call.object;
        ddraw_guest_init(ddraw);
        unk = (IUnknown *)&ddraw->IDirectDraw_iface;
    }

    hr = IUnknown_QueryInterface(unk, iid, obj);
    IUnknown_Release(unk);

    return hr;
}

#else

static void qemu_CF_CreateObject(struct qemu_syscall *call)
{
    struct qemu_CF_CreateObject *c = (struct qemu_CF_CreateObject *)call;
    HRESULT hr;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *factory;
    struct qemu_ddraw *ddraw = NULL;
    struct qemu_clipper *clipper = NULL;

    WINE_TRACE("\n");

    /* We can't use CoCreateInstance because the host-side ole32 is probably not initialized.
     * So navigate out way through DllGetClassObject like ole32 would. */

    lib = GetModuleHandleA("ddraw");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(QEMU_G2H(c->fac_id), &IID_IClassFactory, (void *)&factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    if (c->what == CF_DDRAW || c->what == CF_DDRAW7)
    {

        ddraw = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ddraw));
        if (!ddraw)
        {
            WINE_WARN("Out of memory.\n");
            hr = E_OUTOFMEMORY;
            goto err;
        }

        if (c->what == CF_DDRAW)
        {
            hr = IClassFactory_CreateInstance(factory, NULL, &IID_IDirectDraw, (void **)&ddraw->host_ddraw1);
            if (FAILED(hr))
                goto err;
            IDirectDraw_QueryInterface(ddraw->host_ddraw1, &IID_IDirectDraw7, (void **)&ddraw->host_ddraw7);
        }
        else
        {
            hr = IClassFactory_CreateInstance(factory, NULL, &IID_IDirectDraw7, (void **)&ddraw->host_ddraw7);
            if (FAILED(hr))
                goto err;

            IDirectDraw7_QueryInterface(ddraw->host_ddraw7, &IID_IDirectDraw, (void **)&ddraw->host_ddraw1);
            IDirectDraw7_QueryInterface(ddraw->host_ddraw7, &IID_IDirect3D7, (void **)&ddraw->host_d3d7);
        }
        IDirectDraw_QueryInterface(ddraw->host_ddraw1, &IID_IDirectDraw2, (void **)&ddraw->host_ddraw2);
        IDirectDraw_QueryInterface(ddraw->host_ddraw1, &IID_IDirectDraw4, (void **)&ddraw->host_ddraw4);

        IDirectDraw_QueryInterface(ddraw->host_ddraw1, &IID_IDirect3D, (void **)&ddraw->host_d3d1);
        IDirectDraw_QueryInterface(ddraw->host_ddraw1, &IID_IDirect3D2, (void **)&ddraw->host_d3d2);
        IDirectDraw_QueryInterface(ddraw->host_ddraw1, &IID_IDirect3D3, (void **)&ddraw->host_d3d3);

        c->object = QEMU_H2G(ddraw);
    }
    else
    {
        clipper = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*clipper));
        if (!clipper)
        {
            WINE_WARN("Out of memory.\n");
            hr = E_OUTOFMEMORY;
            goto err;
        }

        hr = IClassFactory_CreateInstance(factory, NULL, &IID_IDirectDrawClipper, (void **)&clipper->host);
        if (FAILED(hr))
            goto err;

        c->object = QEMU_H2G(clipper);
    }

    IClassFactory_Release(factory);

    c->super.iret = DD_OK;
    return;

err:
    WINE_FIXME("Creating a host object failed.\n");
    HeapFree(GetProcessHeap(), 0, ddraw);
    HeapFree(GetProcessHeap(), 0, clipper);
    IClassFactory_Release(factory);
    c->super.iret = hr;
}

#endif

struct qemu_init_dll
{
    struct qemu_syscall super;
    uint64_t ddraw_surface_destroy_cb;
    uint64_t surface_guest_init_complex;
};

#ifdef QEMU_DLL_GUEST

struct object_creation_info
{
    const CLSID *clsid;
    enum create_what what;
};

static const struct object_creation_info object_creation[] =
{
    { &CLSID_DirectDraw,        CF_DDRAW },
    { &CLSID_DirectDraw7,       CF_DDRAW7 },
    { &CLSID_DirectDrawClipper, CF_CLIPPER }
};

struct ddraw_class_factory
{
    IClassFactory IClassFactory_iface;

    LONG ref;
    enum create_what what;
    const CLSID *fac_id;
};

static inline struct ddraw_class_factory *impl_from_IClassFactory(IClassFactory *iface)
{
    return CONTAINING_RECORD(iface, struct ddraw_class_factory, IClassFactory_iface);
}

static HRESULT WINAPI ddraw_class_factory_QueryInterface(IClassFactory *iface, REFIID riid, void **out)
{
    WINE_TRACE("iface %p, riid %s, out %p.\n", iface, wine_dbgstr_guid(riid), out);

    if (IsEqualGUID(riid, &IID_IUnknown) || IsEqualGUID(riid, &IID_IClassFactory))
    {
        IClassFactory_AddRef(iface);
        *out = iface;
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));

    return E_NOINTERFACE;
}

static ULONG WINAPI ddraw_class_factory_AddRef(IClassFactory *iface)
{
    struct ddraw_class_factory *factory = impl_from_IClassFactory(iface);
    ULONG ref = InterlockedIncrement(&factory->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", factory, ref);

    return ref;
}

static ULONG WINAPI ddraw_class_factory_Release(IClassFactory *iface)
{
    struct ddraw_class_factory *factory = impl_from_IClassFactory(iface);
    ULONG ref = InterlockedDecrement(&factory->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", factory, ref);

    if (!ref)
        HeapFree(GetProcessHeap(), 0, factory);

    return ref;
}

static HRESULT WINAPI ddraw_class_factory_CreateInstance(IClassFactory *iface,
        IUnknown *outer_unknown, REFIID riid, void **out)
{
    struct ddraw_class_factory *factory = impl_from_IClassFactory(iface);

    WINE_TRACE("iface %p, outer_unknown %p, riid %s, out %p.\n",
            iface, outer_unknown, wine_dbgstr_guid(riid), out);

    return CF_CreateObject(outer_unknown, riid, out, factory->what, factory->fac_id);
}

static HRESULT WINAPI ddraw_class_factory_LockServer(IClassFactory *iface, BOOL dolock)
{
    WINE_FIXME("iface %p, dolock %#x stub!\n", iface, dolock);

    return S_OK;
}

static const IClassFactoryVtbl IClassFactory_Vtbl =
{
    ddraw_class_factory_QueryInterface,
    ddraw_class_factory_AddRef,
    ddraw_class_factory_Release,
    ddraw_class_factory_CreateInstance,
    ddraw_class_factory_LockServer
};

WINBASEAPI HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **out)
{
    struct ddraw_class_factory *factory;
    unsigned int i;

    WINE_TRACE("rclsid %s, riid %s, out %p.\n", wine_dbgstr_guid(rclsid), wine_dbgstr_guid(riid), out);

    if (!IsEqualGUID(&IID_IClassFactory, riid) && !IsEqualGUID(&IID_IUnknown, riid))
        return E_NOINTERFACE;

    for (i = 0; i < sizeof(object_creation) / sizeof(object_creation[0]); i++)
    {
        if (IsEqualGUID(object_creation[i].clsid, rclsid))
            break;
    }

    if (i == sizeof(object_creation) / sizeof(object_creation[0]))
    {
        WINE_FIXME("%s: no class found.\n", wine_dbgstr_guid(rclsid));
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    factory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*factory));
    if (factory == NULL)
        return E_OUTOFMEMORY;

    factory->IClassFactory_iface.lpVtbl = &IClassFactory_Vtbl;
    factory->ref = 1;

    factory->what = object_creation[i].what;
    factory->fac_id = object_creation[i].clsid;

    *out = factory;
    return S_OK;
}

WINBASEAPI HRESULT WINAPI DllCanUnloadNow(void)
{
    WINE_FIXME("Stub!\n");
    return FALSE;
}

WINBASEAPI HRESULT WINAPI DllRegisterServer(void)
{
    WINE_ERR("Not expected to be called on the wrapper DLL!\n");
    return E_FAIL;
}

WINBASEAPI HRESULT WINAPI DllUnregisterServer(void)
{
    WINE_ERR("Not expected to be called on the wrapper DLL!\n");
    return E_FAIL;
}

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_init_dll call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.ddraw_surface_destroy_cb = (ULONG_PTR)ddraw_surface_destroy_cb;
        call.surface_guest_init_complex = (ULONG_PTR)surface_guest_init_complex;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

#else

uint64_t ddraw_surface_destroy_cb;
uint64_t surface_guest_init_complex;

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_init_dll *c = (struct qemu_init_dll *)call;
    ddraw_surface_destroy_cb = c->ddraw_surface_destroy_cb;
    surface_guest_init_complex = c->surface_guest_init_complex;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CF_CreateObject,
    qemu_d3d1_CreateLight,
    qemu_d3d1_CreateMaterial,
    qemu_d3d1_CreateViewport,
    qemu_d3d1_EnumDevices,
    qemu_d3d1_FindDevice,
    qemu_d3d1_Initialize,
    qemu_d3d_CreateDevice,
    qemu_d3d2_CreateLight,
    qemu_d3d2_CreateMaterial,
    qemu_d3d2_CreateViewport,
    qemu_d3d2_EnumDevices,
    qemu_d3d2_FindDevice,
    qemu_d3d_CreateDevice,
    qemu_d3d3_CreateLight,
    qemu_d3d3_CreateMaterial,
    qemu_d3d_CreateVertexBuffer,
    qemu_d3d3_CreateViewport,
    qemu_d3d3_EnumDevices,
    qemu_d3d_EnumZBufferFormats,
    qemu_d3d3_EvictManagedTextures,
    qemu_d3d3_FindDevice,
    qemu_d3d_CreateDevice,
    qemu_d3d_CreateVertexBuffer,
    qemu_d3d7_EnumDevices,
    qemu_d3d_EnumZBufferFormats,
    qemu_d3d7_EvictManagedTextures,
    qemu_d3d_device1_AddViewport,
    qemu_d3d_device1_BeginScene,
    qemu_d3d_device1_CreateExecuteBuffer,
    qemu_d3d_device1_CreateMatrix,
    qemu_d3d_device1_DeleteMatrix,
    qemu_d3d_device1_DeleteViewport,
    qemu_d3d_device1_EndScene,
    qemu_d3d_device_EnumTextureFormats,
    qemu_d3d_device1_Execute,
    qemu_d3d_device1_GetCaps,
    qemu_d3d_device1_GetMatrix,
    qemu_d3d_device1_GetPickRecords,
    qemu_d3d_device1_GetStats,
    qemu_d3d_device1_Initialize,
    qemu_d3d_device1_NextViewport,
    qemu_d3d_device1_Pick,
    qemu_d3d_device1_SetMatrix,
    qemu_d3d_device1_SwapTextureHandles,
    qemu_d3d_device2_AddViewport,
    qemu_d3d_device2_Begin,
    qemu_d3d_device2_BeginIndexed,
    qemu_d3d_device2_BeginScene,
    qemu_d3d_device2_DeleteViewport,
    qemu_d3d_device2_DrawIndexedPrimitive,
    qemu_d3d_device2_DrawPrimitive,
    qemu_d3d_device2_End,
    qemu_d3d_device2_EndScene,
    qemu_d3d_device_EnumTextureFormats,
    qemu_d3d_device2_GetCaps,
    qemu_d3d_device2_GetClipStatus,
    qemu_d3d_device2_GetCurrentViewport,
    qemu_d3d_device2_GetLightState,
    qemu_d3d_device2_GetRenderState,
    qemu_d3d_device2_GetStats,
    qemu_d3d_device2_GetTransform,
    qemu_d3d_device2_Index,
    qemu_d3d_device2_MultiplyTransform,
    qemu_d3d_device2_NextViewport,
    qemu_d3d_device2_SetClipStatus,
    qemu_d3d_device2_SetCurrentViewport,
    qemu_d3d_device2_SetLightState,
    qemu_d3d_device2_SetRenderState,
    qemu_d3d_device2_SetRenderTarget,
    qemu_d3d_device2_SetTransform,
    qemu_d3d_device2_SwapTextureHandles,
    qemu_d3d_device2_Vertex,
    qemu_d3d_device3_AddViewport,
    qemu_d3d_device3_Begin,
    qemu_d3d_device3_BeginIndexed,
    qemu_d3d_device3_BeginScene,
    qemu_d3d_device3_ComputeSphereVisibility,
    qemu_d3d_device3_DeleteViewport,
    qemu_d3d_device3_DrawIndexedPrimitive,
    qemu_d3d_device3_DrawIndexedPrimitiveStrided,
    qemu_d3d_device3_DrawIndexedPrimitiveVB,
    qemu_d3d_device3_DrawPrimitive,
    qemu_d3d_device3_DrawPrimitiveStrided,
    qemu_d3d_device3_DrawPrimitiveVB,
    qemu_d3d_device3_End,
    qemu_d3d_device3_EndScene,
    qemu_d3d_device_EnumTextureFormats,
    qemu_d3d_device3_GetCaps,
    qemu_d3d_device3_GetClipStatus,
    qemu_d3d_device3_GetCurrentViewport,
    qemu_d3d_device3_GetLightState,
    qemu_d3d_device3_GetRenderState,
    qemu_d3d_device3_GetStats,
    qemu_d3d_device3_GetTexture,
    qemu_d3d_device3_GetTextureStageState,
    qemu_d3d_device3_GetTransform,
    qemu_d3d_device3_Index,
    qemu_d3d_device3_MultiplyTransform,
    qemu_d3d_device3_NextViewport,
    qemu_d3d_device3_SetClipStatus,
    qemu_d3d_device3_SetCurrentViewport,
    qemu_d3d_device3_SetLightState,
    qemu_d3d_device3_SetRenderState,
    qemu_d3d_device3_SetRenderTarget,
    qemu_d3d_device3_SetTexture,
    qemu_d3d_device3_SetTextureStageState,
    qemu_d3d_device3_SetTransform,
    qemu_d3d_device3_ValidateDevice,
    qemu_d3d_device3_Vertex,
    qemu_d3d_device7_ApplyStateBlock,
    qemu_d3d_device7_BeginScene,
    qemu_d3d_device7_BeginStateBlock,
    qemu_d3d_device7_CaptureStateBlock,
    qemu_d3d_device7_Clear,
    qemu_d3d_device7_ComputeSphereVisibility,
    qemu_d3d_device7_CreateStateBlock,
    qemu_d3d_device7_DeleteStateBlock,
    qemu_d3d_device7_DrawIndexedPrimitive,
    qemu_d3d_device7_DrawIndexedPrimitiveStrided,
    qemu_d3d_device7_DrawIndexedPrimitiveVB,
    qemu_d3d_device7_DrawPrimitive,
    qemu_d3d_device7_DrawPrimitiveStrided,
    qemu_d3d_device7_DrawPrimitiveVB,
    qemu_d3d_device7_EndScene,
    qemu_d3d_device7_EndStateBlock,
    qemu_d3d_device_EnumTextureFormats,
    qemu_d3d_device7_GetCaps,
    qemu_d3d_device7_GetClipPlane,
    qemu_d3d_device7_GetClipStatus,
    qemu_d3d_device7_GetInfo,
    qemu_d3d_device7_GetLight,
    qemu_d3d_device7_GetLightEnable,
    qemu_d3d_device7_GetMaterial,
    qemu_d3d_device7_GetRenderState,
    qemu_d3d_device7_GetTexture,
    qemu_d3d_device7_GetTextureStageState,
    qemu_d3d_device7_GetTransform,
    qemu_d3d_device7_GetViewport,
    qemu_d3d_device7_LightEnable,
    qemu_d3d_device7_Load,
    qemu_d3d_device7_MultiplyTransform,
    qemu_d3d_device7_PreLoad,
    qemu_d3d_device_Release,
    qemu_d3d_device7_SetClipPlane,
    qemu_d3d_device7_SetClipStatus,
    qemu_d3d_device7_SetLight,
    qemu_d3d_device7_SetMaterial,
    qemu_d3d_device7_SetRenderState,
    qemu_d3d_device7_SetRenderTarget,
    qemu_d3d_device7_SetTexture,
    qemu_d3d_device7_SetTextureStageState,
    qemu_d3d_device7_SetTransform,
    qemu_d3d_device7_SetViewport,
    qemu_d3d_device7_ValidateDevice,
    qemu_d3d_texture1_GetHandle,
    qemu_d3d_texture1_Initialize,
    qemu_d3d_texture1_Load,
    qemu_d3d_texture1_PaletteChanged,
    qemu_d3d_texture1_Unload,
    qemu_d3d_texture2_GetHandle,
    qemu_d3d_texture2_Load,
    qemu_d3d_texture2_PaletteChanged,
    qemu_d3d_vertex_buffer7_GetVertexBufferDesc,
    qemu_d3d_vertex_buffer7_Lock,
    qemu_d3d_vertex_buffer7_Optimize,
    qemu_d3d_vertex_buffer7_ProcessVertices,
    qemu_d3d_vertex_buffer7_ProcessVerticesStrided,
    qemu_d3d_vertex_buffer7_Release,
    qemu_d3d_vertex_buffer7_Unlock,
    qemu_ddraw1_Compact,
    qemu_ddraw1_CreatePalette,
    qemu_ddraw1_CreateSurface,
    qemu_ddraw1_DuplicateSurface,
    qemu_ddraw1_EnumSurfaces,
    qemu_ddraw1_FlipToGDISurface,
    qemu_ddraw1_GetCaps,
    qemu_ddraw_GetDisplayMode,
    qemu_ddraw1_GetFourCCCodes,
    qemu_ddraw1_GetGDISurface,
    qemu_ddraw1_GetMonitorFrequency,
    qemu_ddraw1_GetScanLine,
    qemu_ddraw1_GetVerticalBlankStatus,
    qemu_ddraw1_Initialize,
    qemu_ddraw1_QueryInterface,
    qemu_ddraw1_Release,
    qemu_ddraw1_RestoreDisplayMode,
    qemu_ddraw1_SetCooperativeLevel,
    qemu_ddraw1_SetDisplayMode,
    qemu_ddraw1_WaitForVerticalBlank,
    qemu_ddraw2_Compact,
    qemu_ddraw2_CreatePalette,
    qemu_ddraw2_CreateSurface,
    qemu_ddraw2_DuplicateSurface,
    qemu_ddraw2_EnumDisplayModes,
    qemu_ddraw2_EnumSurfaces,
    qemu_ddraw2_FlipToGDISurface,
    qemu_ddraw2_GetAvailableVidMem,
    qemu_ddraw2_GetCaps,
    qemu_ddraw_GetDisplayMode,
    qemu_ddraw2_GetFourCCCodes,
    qemu_ddraw2_GetGDISurface,
    qemu_ddraw2_GetMonitorFrequency,
    qemu_ddraw2_GetScanLine,
    qemu_ddraw2_GetVerticalBlankStatus,
    qemu_ddraw2_Initialize,
    qemu_ddraw2_RestoreDisplayMode,
    qemu_ddraw2_SetCooperativeLevel,
    qemu_ddraw2_SetDisplayMode,
    qemu_ddraw2_WaitForVerticalBlank,
    qemu_ddraw4_Compact,
    qemu_ddraw4_CreatePalette,
    qemu_ddraw4_CreateSurface,
    qemu_ddraw4_DuplicateSurface,
    qemu_ddraw4_EnumSurfaces,
    qemu_ddraw4_FlipToGDISurface,
    qemu_ddraw4_GetAvailableVidMem,
    qemu_ddraw4_GetCaps,
    qemu_ddraw4_GetDeviceIdentifier,
    qemu_ddraw_GetDisplayMode,
    qemu_ddraw4_GetFourCCCodes,
    qemu_ddraw4_GetGDISurface,
    qemu_ddraw4_GetMonitorFrequency,
    qemu_ddraw4_GetScanLine,
    qemu_ddraw4_GetSurfaceFromDC,
    qemu_ddraw4_GetVerticalBlankStatus,
    qemu_ddraw4_Initialize,
    qemu_ddraw4_RestoreAllSurfaces,
    qemu_ddraw4_RestoreDisplayMode,
    qemu_ddraw4_SetCooperativeLevel,
    qemu_ddraw4_SetDisplayMode,
    qemu_ddraw4_TestCooperativeLevel,
    qemu_ddraw4_WaitForVerticalBlank,
    qemu_ddraw7_Compact,
    qemu_ddraw7_CreatePalette,
    qemu_ddraw7_CreateSurface,
    qemu_ddraw7_DuplicateSurface,
    qemu_ddraw7_EnumDisplayModes,
    qemu_ddraw7_EnumSurfaces,
    qemu_ddraw7_EvaluateMode,
    qemu_ddraw7_FlipToGDISurface,
    qemu_ddraw7_GetAvailableVidMem,
    qemu_ddraw7_GetCaps,
    qemu_ddraw7_GetDeviceIdentifier,
    qemu_ddraw_GetDisplayMode,
    qemu_ddraw7_GetFourCCCodes,
    qemu_ddraw7_GetGDISurface,
    qemu_ddraw7_GetMonitorFrequency,
    qemu_ddraw7_GetScanLine,
    qemu_ddraw7_GetSurfaceFromDC,
    qemu_ddraw7_GetVerticalBlankStatus,
    qemu_ddraw7_Initialize,
    qemu_ddraw7_RestoreAllSurfaces,
    qemu_ddraw7_RestoreDisplayMode,
    qemu_ddraw7_SetCooperativeLevel,
    qemu_ddraw7_SetDisplayMode,
    qemu_ddraw7_StartModeTest,
    qemu_ddraw7_TestCooperativeLevel,
    qemu_ddraw7_WaitForVerticalBlank,
    qemu_ddraw_clipper_GetClipList,
    qemu_ddraw_clipper_GetHWnd,
    qemu_ddraw_clipper_Initialize,
    qemu_ddraw_clipper_IsClipListChanged,
    qemu_ddraw_clipper_Release,
    qemu_ddraw_clipper_SetClipList,
    qemu_ddraw_clipper_SetHWnd,
    qemu_ddraw_gamma_control_GetGammaRamp,
    qemu_ddraw_gamma_control_SetGammaRamp,
    qemu_ddraw_palette_GetCaps,
    qemu_ddraw_palette_GetEntries,
    qemu_ddraw_palette_Initialize,
    qemu_ddraw_palette_Release,
    qemu_ddraw_palette_SetEntries,
    qemu_ddraw_surface1_AddAttachedSurface,
    qemu_ddraw_surface1_AddOverlayDirtyRect,
    qemu_ddraw_surface1_Blt,
    qemu_ddraw_surface1_BltBatch,
    qemu_ddraw_surface1_BltFast,
    qemu_ddraw_surface1_DeleteAttachedSurface,
    qemu_ddraw_surface1_EnumAttachedSurfaces,
    qemu_ddraw_surface1_EnumOverlayZOrders,
    qemu_ddraw_surface1_Flip,
    qemu_ddraw_surface_GetAttachedSurface,
    qemu_ddraw_surface1_GetBltStatus,
    qemu_ddraw_surface1_GetCaps,
    qemu_ddraw_surface1_GetClipper,
    qemu_ddraw_surface1_GetColorKey,
    qemu_ddraw_surface1_GetDC,
    qemu_ddraw_surface1_GetFlipStatus,
    qemu_ddraw_surface1_GetOverlayPosition,
    qemu_ddraw_surface1_GetPalette,
    qemu_ddraw_surface1_GetPixelFormat,
    qemu_ddraw_surface1_GetSurfaceDesc,
    qemu_ddraw_surface1_Initialize,
    qemu_ddraw_surface1_IsLost,
    qemu_ddraw_surface_Lock,
    qemu_ddraw_surface1_Release,
    qemu_ddraw_surface1_ReleaseDC,
    qemu_ddraw_surface1_Restore,
    qemu_ddraw_surface_SetClipper,
    qemu_ddraw_surface1_SetColorKey,
    qemu_ddraw_surface1_SetOverlayPosition,
    qemu_ddraw_surface1_SetPalette,
    qemu_ddraw_surface1_Unlock,
    qemu_ddraw_surface1_UpdateOverlay,
    qemu_ddraw_surface1_UpdateOverlayDisplay,
    qemu_ddraw_surface1_UpdateOverlayZOrder,
    qemu_ddraw_surface2_AddAttachedSurface,
    qemu_ddraw_surface2_AddOverlayDirtyRect,
    qemu_ddraw_surface2_Blt,
    qemu_ddraw_surface2_BltBatch,
    qemu_ddraw_surface2_BltFast,
    qemu_ddraw_surface2_DeleteAttachedSurface,
    qemu_ddraw_surface2_EnumAttachedSurfaces,
    qemu_ddraw_surface2_EnumOverlayZOrders,
    qemu_ddraw_surface2_Flip,
    qemu_ddraw_surface_GetAttachedSurface,
    qemu_ddraw_surface2_GetBltStatus,
    qemu_ddraw_surface2_GetCaps,
    qemu_ddraw_surface2_GetClipper,
    qemu_ddraw_surface2_GetColorKey,
    qemu_ddraw_surface2_GetDC,
    qemu_ddraw_surface2_GetDDInterface,
    qemu_ddraw_surface2_GetFlipStatus,
    qemu_ddraw_surface2_GetOverlayPosition,
    qemu_ddraw_surface2_GetPalette,
    qemu_ddraw_surface2_GetPixelFormat,
    qemu_ddraw_surface2_GetSurfaceDesc,
    qemu_ddraw_surface2_Initialize,
    qemu_ddraw_surface2_IsLost,
    qemu_ddraw_surface_Lock,
    qemu_ddraw_surface2_PageLock,
    qemu_ddraw_surface2_PageUnlock,
    qemu_ddraw_surface2_ReleaseDC,
    qemu_ddraw_surface2_Restore,
    qemu_ddraw_surface_SetClipper,
    qemu_ddraw_surface2_SetColorKey,
    qemu_ddraw_surface2_SetOverlayPosition,
    qemu_ddraw_surface2_SetPalette,
    qemu_ddraw_surface2_Unlock,
    qemu_ddraw_surface2_UpdateOverlay,
    qemu_ddraw_surface2_UpdateOverlayDisplay,
    qemu_ddraw_surface2_UpdateOverlayZOrder,
    qemu_ddraw_surface3_AddAttachedSurface,
    qemu_ddraw_surface3_AddOverlayDirtyRect,
    qemu_ddraw_surface3_Blt,
    qemu_ddraw_surface3_BltBatch,
    qemu_ddraw_surface3_BltFast,
    qemu_ddraw_surface3_DeleteAttachedSurface,
    qemu_ddraw_surface3_EnumAttachedSurfaces,
    qemu_ddraw_surface3_EnumOverlayZOrders,
    qemu_ddraw_surface3_Flip,
    qemu_ddraw_surface_GetAttachedSurface,
    qemu_ddraw_surface3_GetBltStatus,
    qemu_ddraw_surface3_GetCaps,
    qemu_ddraw_surface3_GetClipper,
    qemu_ddraw_surface3_GetColorKey,
    qemu_ddraw_surface3_GetDC,
    qemu_ddraw_surface3_GetDDInterface,
    qemu_ddraw_surface3_GetFlipStatus,
    qemu_ddraw_surface3_GetOverlayPosition,
    qemu_ddraw_surface3_GetPalette,
    qemu_ddraw_surface3_GetPixelFormat,
    qemu_ddraw_surface3_GetSurfaceDesc,
    qemu_ddraw_surface3_Initialize,
    qemu_ddraw_surface3_IsLost,
    qemu_ddraw_surface_Lock,
    qemu_ddraw_surface3_PageLock,
    qemu_ddraw_surface3_PageUnlock,
    qemu_ddraw_surface3_ReleaseDC,
    qemu_ddraw_surface3_Restore,
    qemu_ddraw_surface_SetClipper,
    qemu_ddraw_surface3_SetColorKey,
    qemu_ddraw_surface3_SetOverlayPosition,
    qemu_ddraw_surface3_SetPalette,
    qemu_ddraw_surface3_SetSurfaceDesc,
    qemu_ddraw_surface3_Unlock,
    qemu_ddraw_surface3_UpdateOverlay,
    qemu_ddraw_surface3_UpdateOverlayDisplay,
    qemu_ddraw_surface3_UpdateOverlayZOrder,
    qemu_ddraw_surface4_AddAttachedSurface,
    qemu_ddraw_surface4_AddOverlayDirtyRect,
    qemu_ddraw_surface4_Blt,
    qemu_ddraw_surface4_BltBatch,
    qemu_ddraw_surface4_BltFast,
    qemu_ddraw_surface4_ChangeUniquenessValue,
    qemu_ddraw_surface4_DeleteAttachedSurface,
    qemu_ddraw_surface4_EnumAttachedSurfaces,
    qemu_ddraw_surface4_EnumOverlayZOrders,
    qemu_ddraw_surface4_Flip,
    qemu_ddraw_surface4_FreePrivateData,
    qemu_ddraw_surface_GetAttachedSurface,
    qemu_ddraw_surface4_GetBltStatus,
    qemu_ddraw_surface4_GetCaps,
    qemu_ddraw_surface4_GetClipper,
    qemu_ddraw_surface4_GetColorKey,
    qemu_ddraw_surface4_GetDC,
    qemu_ddraw_surface4_GetDDInterface,
    qemu_ddraw_surface4_GetFlipStatus,
    qemu_ddraw_surface4_GetOverlayPosition,
    qemu_ddraw_surface4_GetPalette,
    qemu_ddraw_surface4_GetPixelFormat,
    qemu_ddraw_surface4_GetPrivateData,
    qemu_ddraw_surface4_GetSurfaceDesc,
    qemu_ddraw_surface4_GetUniquenessValue,
    qemu_ddraw_surface4_Initialize,
    qemu_ddraw_surface4_IsLost,
    qemu_ddraw_surface_Lock,
    qemu_ddraw_surface4_PageLock,
    qemu_ddraw_surface4_PageUnlock,
    qemu_ddraw_surface4_ReleaseDC,
    qemu_ddraw_surface4_Restore,
    qemu_ddraw_surface_SetClipper,
    qemu_ddraw_surface4_SetColorKey,
    qemu_ddraw_surface4_SetOverlayPosition,
    qemu_ddraw_surface4_SetPalette,
    qemu_ddraw_surface4_SetPrivateData,
    qemu_ddraw_surface4_SetSurfaceDesc,
    qemu_ddraw_surface4_Unlock,
    qemu_ddraw_surface4_UpdateOverlay,
    qemu_ddraw_surface4_UpdateOverlayDisplay,
    qemu_ddraw_surface4_UpdateOverlayZOrder,
    qemu_ddraw_surface7_AddAttachedSurface,
    qemu_ddraw_surface7_AddOverlayDirtyRect,
    qemu_ddraw_surface7_Blt,
    qemu_ddraw_surface7_BltBatch,
    qemu_ddraw_surface7_BltFast,
    qemu_ddraw_surface7_ChangeUniquenessValue,
    qemu_ddraw_surface7_DeleteAttachedSurface,
    qemu_ddraw_surface7_EnumAttachedSurfaces,
    qemu_ddraw_surface7_EnumOverlayZOrders,
    qemu_ddraw_surface7_Flip,
    qemu_ddraw_surface7_FreePrivateData,
    qemu_ddraw_surface_GetAttachedSurface,
    qemu_ddraw_surface7_GetBltStatus,
    qemu_ddraw_surface7_GetCaps,
    qemu_ddraw_surface7_GetClipper,
    qemu_ddraw_surface7_GetColorKey,
    qemu_ddraw_surface7_GetDC,
    qemu_ddraw_surface7_GetDDInterface,
    qemu_ddraw_surface7_GetFlipStatus,
    qemu_ddraw_surface7_GetLOD,
    qemu_ddraw_surface7_GetOverlayPosition,
    qemu_ddraw_surface7_GetPalette,
    qemu_ddraw_surface7_GetPixelFormat,
    qemu_ddraw_surface7_GetPriority,
    qemu_ddraw_surface7_GetPrivateData,
    qemu_ddraw_surface7_GetSurfaceDesc,
    qemu_ddraw_surface7_GetUniquenessValue,
    qemu_ddraw_surface7_Initialize,
    qemu_ddraw_surface7_IsLost,
    qemu_ddraw_surface_Lock,
    qemu_ddraw_surface7_PageLock,
    qemu_ddraw_surface7_PageUnlock,
    qemu_ddraw_surface7_ReleaseDC,
    qemu_ddraw_surface7_Restore,
    qemu_ddraw_surface_SetClipper,
    qemu_ddraw_surface7_SetColorKey,
    qemu_ddraw_surface7_SetLOD,
    qemu_ddraw_surface7_SetOverlayPosition,
    qemu_ddraw_surface7_SetPalette,
    qemu_ddraw_surface7_SetPriority,
    qemu_ddraw_surface7_SetPrivateData,
    qemu_ddraw_surface7_SetSurfaceDesc,
    qemu_ddraw_surface7_Unlock,
    qemu_ddraw_surface7_UpdateOverlay,
    qemu_ddraw_surface7_UpdateOverlayDisplay,
    qemu_ddraw_surface7_UpdateOverlayZOrder,
    qemu_ddraw_surface_QI_Device,
    qemu_DirectDrawCreate,
    qemu_DirectDrawCreateClipper,
    qemu_DirectDrawCreateEx,
    qemu_DirectDrawEnumerate,
    qemu_DirectDrawEnumerateEx,
    qemu_DirectDrawEnumerateEx,
    qemu_DirectDrawEnumerate,
    qemu_GetSurfaceFromDC,
    qemu_init_dll,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side ddraw wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
