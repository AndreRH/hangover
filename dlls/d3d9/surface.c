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

#define COBJMACROS
#include <windows.h>
#include <stdio.h>
#include <d3d9.h>

#include "thunk/qemu_d3d9.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_d3d9_surface_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_subresource_impl *impl_from_IDirect3DSurface(IDirect3DSurface9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_subresource_impl, IDirect3DSurface9_iface);
}

static HRESULT WINAPI d3d9_surface_QueryInterface(IDirect3DSurface9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_QueryInterface *c = (struct qemu_d3d9_surface_QueryInterface *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_QueryInterface(surface->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_surface_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_surface_AddRef(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_ADDREF);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_AddRef *c = (struct qemu_d3d9_surface_AddRef *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_AddRef(surface->host);
}

#endif

struct qemu_d3d9_surface_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

void __fastcall qemu_d3d9_subresource_destroyed(struct qemu_d3d9_subresource_impl *res)
{
    wined3d_private_store_cleanup(&res->private_store);
}

static ULONG WINAPI d3d9_surface_Release(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_RELEASE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_Release *c = (struct qemu_d3d9_surface_Release *)call;
    struct qemu_d3d9_subresource_impl *surface;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    device = surface->device;

    /* In case of stand-alone surfaces, or that the app releases the last reference
     * it holds to a texture through IDirect3DSurface9. */
    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DSurface9_Release(surface->host);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_surface_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetDevice(IDirect3DSurface9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_device_impl *dev_impl;

    struct qemu_d3d9_surface_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETDEVICE);
    call.iface = (ULONG_PTR)surface;
    call.device = (ULONG_PTR)&dev_impl;

    qemu_syscall(&call.super);

    *device = (IDirect3DDevice9 *)&dev_impl->IDirect3DDevice9Ex_iface;
    IDirect3DDevice9_AddRef(*device);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetDevice *c = (struct qemu_d3d9_surface_GetDevice *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(surface->device);
    c->super.iret = D3D_OK;
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_SetPrivateData(IDirect3DSurface9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    return qemu_d3d9_set_private_data(&surface->private_store, guid, data, data_size, flags);;
}

#else

void qemu_d3d9_surface_SetPrivateData(struct qemu_syscall *call)
{
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetPrivateData(IDirect3DSurface9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    return qemu_d3d9_get_private_data(&surface->private_store, guid, data, data_size);
}

#else

void qemu_d3d9_surface_GetPrivateData(struct qemu_syscall *call)
{
}

#endif

struct qemu_d3d9_surface_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_FreePrivateData(IDirect3DSurface9 *iface, REFGUID guid)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    return qemu_d3d9_free_private_data(&surface->private_store, guid);
}

#else

void qemu_d3d9_surface_FreePrivateData(struct qemu_syscall *call)
{
}

#endif

struct qemu_d3d9_surface_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_surface_SetPriority(IDirect3DSurface9 *iface, DWORD priority)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_SETPRIORITY);
    call.iface = (ULONG_PTR)surface;
    call.priority = priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_SetPriority *c = (struct qemu_d3d9_surface_SetPriority *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_SetPriority(surface->host, c->priority);
}

#endif

struct qemu_d3d9_surface_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_surface_GetPriority(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETPRIORITY);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetPriority *c = (struct qemu_d3d9_surface_GetPriority *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetPriority(surface->host);
}

#endif

struct qemu_d3d9_surface_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_surface_PreLoad(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_PRELOAD);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_surface_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_PreLoad *c = (struct qemu_d3d9_surface_PreLoad *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    IDirect3DSurface9_PreLoad(surface->host);
}

#endif

struct qemu_d3d9_surface_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DRESOURCETYPE WINAPI d3d9_surface_GetType(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETTYPE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetType *c = (struct qemu_d3d9_surface_GetType *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetType(surface->host);
}

#endif

struct qemu_d3d9_surface_GetContainer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t texture;
    uint64_t swapchain;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetContainer(IDirect3DSurface9 *iface, REFIID riid, void **container)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetContainer call;
    struct qemu_d3d9_texture_impl *texture = NULL;
    struct qemu_d3d9_swapchain_impl *swapchain = NULL;
    struct qemu_d3d9_device_impl *device = NULL;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETCONTAINER);
    call.iface = (ULONG_PTR)surface;
    call.riid = (ULONG_PTR)riid;
    call.texture = (ULONG_PTR)&texture;
    call.swapchain = (ULONG_PTR)&swapchain;
    call.device = (ULONG_PTR)&device;

    qemu_syscall(&call.super);

    if (texture)
        *container = &texture->IDirect3DBaseTexture9_iface;
    else if (swapchain)
        *container = &swapchain->IDirect3DSwapChain9Ex_iface;
    else if (device)
        *container = &device->IDirect3DDevice9Ex_iface;
    else
        *container = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetContainer(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetContainer *c = (struct qemu_d3d9_surface_GetContainer *)call;
    struct qemu_d3d9_subresource_impl *surface;
    void *container;
    GUID *iid;
    struct qemu_d3d9_texture_impl *texture;
    struct qemu_d3d9_swapchain_impl *swapchain;
    IDirect3DSurface9 *backbuffer;
    IUnknown *priv_data;
    DWORD size = sizeof(priv_data);

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    c->super.iret = IDirect3DSurface9_GetContainer(surface->host, iid, &container);
    if (FAILED(c->super.iret))
        return;

    if (IsEqualGUID(iid, &IID_IDirect3DSwapChain9) || IsEqualGUID(iid, &IID_IDirect3DSwapChain9Ex))
    {
        IDirect3DSwapChain9_GetBackBuffer((IDirect3DSwapChain9 *)container, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
        IDirect3DSurface9_GetPrivateData(backbuffer, &qemu_d3d9_swapchain_guid, &priv_data, &size);
        IDirect3DSurface9_Release(backbuffer);

        swapchain = swapchain_impl_from_IUnknown(priv_data);
        WINE_TRACE("Retrieved swapchain wrapper %p from private data.\n", swapchain);
        priv_data->lpVtbl->Release(priv_data);

        *(uint64_t *)QEMU_G2H(c->swapchain) = QEMU_H2G(swapchain);
    }
    else if (IsEqualGUID(iid, &IID_IDirect3DTexture9) || IsEqualGUID(iid, &IID_IDirect3DCubeTexture9)
            || IsEqualGUID(iid, &IID_IDirect3DBaseTexture9) || IsEqualGUID(iid, &IID_IDirect3DResource9)
            || IsEqualGUID(iid, &IID_IUnknown))
    {
        IDirect3DBaseTexture9_GetPrivateData((IDirect3DBaseTexture9 *)container,
                &qemu_d3d9_texture_guid, &priv_data, &size);
        texture = texture_impl_from_IUnknown(priv_data);
        WINE_TRACE("Retrieved texture wrapper %p from private data.\n", texture);
        priv_data->lpVtbl->Release(priv_data);

        *(uint64_t *)QEMU_G2H(c->texture) = QEMU_H2G(texture);
    }
    else if (IsEqualGUID(iid, &IID_IDirect3DDevice9))
    {
        /* Do not release the container returned by GetContainer, we pass the reference on! */
        *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(surface->device);
    }
    else
    {
        WINE_FIXME("Unexpected GUID %s.\n", wine_dbgstr_guid(iid));
        c->super.iret = E_FAIL;
        ((IUnknown *)container)->lpVtbl->Release(container);

    }
}

#endif

struct qemu_d3d9_surface_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetDesc(IDirect3DSurface9 *iface, D3DSURFACE_DESC *desc)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETDESC);
    call.iface = (ULONG_PTR)surface;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetDesc *c = (struct qemu_d3d9_surface_GetDesc *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetDesc(surface->host, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d9_surface_LockRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t locked_rect;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_LockRect(IDirect3DSurface9 *iface, D3DLOCKED_RECT *locked_rect, const RECT *rect, DWORD flags)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_LockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_LOCKRECT);
    call.iface = (ULONG_PTR)surface;
    call.locked_rect = (ULONG_PTR)locked_rect;
    call.rect = (ULONG_PTR)rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_LockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_LockRect *c = (struct qemu_d3d9_surface_LockRect *)call;
    struct qemu_d3d9_subresource_impl *surface;
    D3DLOCKED_RECT stack, *lr = &stack;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    lr = QEMU_G2H(c->locked_rect);
#else
    if (!c->locked_rect)
        lr = NULL;
#endif

    c->super.iret = IDirect3DSurface9_LockRect(surface->host, lr, QEMU_G2H(c->rect), c->flags);

#if GUEST_BIT != HOST_BIT
    if (c->locked_rect)
        D3DLOCKED_RECT_h2g(QEMU_G2H(c->locked_rect), lr);
#endif
}

#endif

struct qemu_d3d9_surface_UnlockRect
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_UnlockRect(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_UnlockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_UNLOCKRECT);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_UnlockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_UnlockRect *c = (struct qemu_d3d9_surface_UnlockRect *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_UnlockRect(surface->host);
}

#endif

struct qemu_d3d9_surface_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetDC(IDirect3DSurface9 *iface, HDC *dc)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = (ULONG_PTR)dc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetDC(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetDC *c = (struct qemu_d3d9_surface_GetDC *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetDC(surface->host, QEMU_G2H(c->dc));
}

#endif

struct qemu_d3d9_surface_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_ReleaseDC(IDirect3DSurface9 *iface, HDC dc)
{
    struct qemu_d3d9_subresource_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_ReleaseDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = (ULONG_PTR)dc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_ReleaseDC *c = (struct qemu_d3d9_surface_ReleaseDC *)call;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_ReleaseDC(surface->host, (HDC)c->dc);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DSurface9Vtbl d3d9_surface_vtbl =
{
    /* IUnknown */
    d3d9_surface_QueryInterface,
    d3d9_surface_AddRef,
    d3d9_surface_Release,
    /* IDirect3DResource9 */
    d3d9_surface_GetDevice,
    d3d9_surface_SetPrivateData,
    d3d9_surface_GetPrivateData,
    d3d9_surface_FreePrivateData,
    d3d9_surface_SetPriority,
    d3d9_surface_GetPriority,
    d3d9_surface_PreLoad,
    d3d9_surface_GetType,
    /* IDirect3DSurface9 */
    d3d9_surface_GetContainer,
    d3d9_surface_GetDesc,
    d3d9_surface_LockRect,
    d3d9_surface_UnlockRect,
    d3d9_surface_GetDC,
    d3d9_surface_ReleaseDC,
};

void qemu_d3d9_surface_init_guest(IDirect3DSurface9 *surface)
{
    struct qemu_d3d9_subresource_impl *impl = impl_from_IDirect3DSurface(surface);
    if (!impl->initialized)
    {
        impl->IDirect3DSurface9_iface.lpVtbl = &d3d9_surface_vtbl;
        wined3d_private_store_init(&impl->private_store);
        impl->initialized = TRUE;
    }
}

#else

struct qemu_d3d9_surface_impl *surface_impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_surface_impl, private_data);
}

static HRESULT WINAPI d3d9_surface_priv_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d9_surface_priv_AddRef(IUnknown *iface)
{
    struct qemu_d3d9_surface_impl *surface = surface_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedIncrement(&surface->private_data_ref);

    WINE_TRACE("%p increasing refcount to %u.\n", surface, refcount);
    return refcount;
}

static ULONG WINAPI d3d9_surface_priv_Release(IUnknown *iface)
{
    struct qemu_d3d9_surface_impl *surface = surface_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedDecrement(&surface->private_data_ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", surface, refcount);
    if (!refcount)
    {
        /* This means the private data has been released, which only happens
         * when the real interface has been destroyed. */
        qemu_ops->qemu_execute(QEMU_G2H(qemu_d3d9_subresource_destroyed),
                QEMU_H2G(&surface->sub_resource));
        HeapFree(GetProcessHeap(), 0, surface);
    }

    return refcount;
}

static const struct IUnknownVtbl surface_priv_vtbl =
{
    /* IUnknown */
    d3d9_surface_priv_QueryInterface,
    d3d9_surface_priv_AddRef,
    d3d9_surface_priv_Release,
};

void d3d9_surface_init(struct qemu_d3d9_subresource_impl *surface, IDirect3DSurface9 *host_surface,
        struct qemu_d3d9_device_impl *device)
{
    WINE_TRACE("Init surface %p, host %p.\n", surface, host_surface);
    surface->host = host_surface;
    surface->device = device;
    IDirect3DSurface9_SetPrivateData(host_surface, &qemu_d3d9_surface_guid, &surface, sizeof(surface), 0);
}

void d3d9_standalone_surface_init(struct qemu_d3d9_surface_impl *surface, IDirect3DSurface9 *host,
        struct qemu_d3d9_device_impl *device)
{
    surface->private_data.lpVtbl = &surface_priv_vtbl;
    surface->private_data_ref = 0;
    IDirect3DSurface9_SetPrivateData(host, &qemu_d3d9_standalone_surface_guid, &surface->private_data,
            sizeof(IUnknown *), D3DSPD_IUNKNOWN);

    d3d9_surface_init(&surface->sub_resource, host, device);
}

#endif
