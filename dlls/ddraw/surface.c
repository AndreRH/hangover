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
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_ddraw_surface1_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

struct qemu_ddraw_surface_QI_Device
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

/* FIXME: This should not be hardcoded. We should query it from the first created device before the
 * application has a chance to learn this GUID. */
const GUID IID_D3DDEVICE_WineD3D =
{
    0xaef72d43,
    0xb09a,
    0x4b7b,
    { 0xb7,0x98,0xc6,0x8a,0x77,0x2d,0x72,0x2a }
};

static struct qemu_surface *unsafe_impl_from_IDirectDrawSurface2(IDirectDrawSurface2 *iface);
static struct qemu_surface *unsafe_impl_from_IDirectDrawSurface3(IDirectDrawSurface3 *iface);

static inline struct qemu_surface *impl_from_IDirectDrawGammaControl(IDirectDrawGammaControl *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawGammaControl_iface);
}

static inline struct qemu_surface *impl_from_IDirect3DTexture(IDirect3DTexture *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirect3DTexture_iface);
}

static inline struct qemu_surface *impl_from_IDirect3DTexture2(IDirect3DTexture2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirect3DTexture2_iface);
}

static inline struct qemu_surface *impl_from_IDirectDrawSurface(IDirectDrawSurface *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface_iface);
}

static inline struct qemu_surface *impl_from_IDirectDrawSurface2(IDirectDrawSurface2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface2_iface);
}

static inline struct qemu_surface *impl_from_IDirectDrawSurface3(IDirectDrawSurface3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface3_iface);
}

static inline struct qemu_surface *impl_from_IDirectDrawSurface4(IDirectDrawSurface4 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface4_iface);
}

static inline struct qemu_surface *impl_from_IDirectDrawSurface7(IDirectDrawSurface7 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface7_iface);
}

static HRESULT WINAPI ddraw_surface7_QueryInterface(IDirectDrawSurface7 *iface, REFIID riid, void **obj)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), obj);

    /* According to COM docs, if the QueryInterface fails, obj should be set to NULL */
    *obj = NULL;

    if(!riid)
        return DDERR_INVALIDPARAMS;

    if (IsEqualGUID(riid, &IID_IDirectDrawSurface7))
    {
        IDirectDrawSurface7_AddRef(iface);
        *obj = iface;
        WINE_TRACE("(%p) returning IDirectDrawSurface7 interface at %p\n", surface, *obj);
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_IDirectDrawSurface4))
    {
        IDirectDrawSurface4_AddRef(&surface->IDirectDrawSurface4_iface);
        *obj = &surface->IDirectDrawSurface4_iface;
        WINE_TRACE("(%p) returning IDirectDrawSurface4 interface at %p\n", surface, *obj);
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_IDirectDrawSurface3))
    {
        IDirectDrawSurface3_AddRef(&surface->IDirectDrawSurface3_iface);
        *obj = &surface->IDirectDrawSurface3_iface;
        WINE_TRACE("(%p) returning IDirectDrawSurface3 interface at %p\n", surface, *obj);
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_IDirectDrawSurface2))
    {
        IDirectDrawSurface2_AddRef(&surface->IDirectDrawSurface2_iface);
        *obj = &surface->IDirectDrawSurface2_iface;
        WINE_TRACE("(%p) returning IDirectDrawSurface2 interface at %p\n", surface, *obj);
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_IDirectDrawSurface)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        IDirectDrawSurface_AddRef(&surface->IDirectDrawSurface_iface);
        *obj = &surface->IDirectDrawSurface_iface;
        WINE_TRACE("(%p) returning IDirectDrawSurface interface at %p\n", surface, *obj);
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_IDirectDrawGammaControl))
    {
        IDirectDrawGammaControl_AddRef(&surface->IDirectDrawGammaControl_iface);
        *obj = &surface->IDirectDrawGammaControl_iface;
        WINE_TRACE("(%p) returning IDirectDrawGammaControl interface at %p\n", surface, *obj);
        return S_OK;
    }

    if (IsEqualGUID(riid, &IID_IDirectDrawColorControl))
    {
        WINE_WARN("Color control not implemented.\n");
        *obj = NULL;
        return E_NOINTERFACE;
    }

    if (surface->version != 7)
    {
        if (IsEqualGUID(riid, &IID_D3DDEVICE_WineD3D)
                || IsEqualGUID(riid, &IID_IDirect3DHALDevice)
                || IsEqualGUID(riid, &IID_IDirect3DRGBDevice))
        {
            if (!surface->device1)
            {
                struct qemu_ddraw_surface_QI_Device call;
                struct qemu_device *device;

                call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE_QI_DEVICE);
                call.iface = (ULONG_PTR)iface;
                call.iid = (ULONG_PTR)riid;

                qemu_syscall(&call.super);
                if (FAILED(call.super.iret))
                {
                    *obj = NULL;
                    return call.super.iret;
                }

                device = (struct qemu_device *)(ULONG_PTR)call.device;
                ddraw_device_guest_init(device, surface->ddraw, 1, (IUnknown *)&surface->IDirectDrawSurface_iface,
                        (IUnknown *)&surface->IDirectDrawSurface_iface);
            }

            IDirect3DDevice_AddRef(&surface->device1->IDirect3DDevice_iface);
            *obj = &surface->device1->IDirect3DDevice_iface;
            return S_OK;
        }

        if (IsEqualGUID(&IID_IDirect3DTexture2, riid))
        {
            IDirect3DTexture2_AddRef(&surface->IDirect3DTexture2_iface);
            *obj = &surface->IDirect3DTexture2_iface;
            return S_OK;
        }

        if (IsEqualGUID( &IID_IDirect3DTexture, riid ))
        {
            IDirect3DTexture2_AddRef(&surface->IDirect3DTexture_iface);
            *obj = &surface->IDirect3DTexture_iface;
            return S_OK;
        }
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));

    if (surface->version != 7)
        return E_INVALIDARG;

    return E_NOINTERFACE;
}

static HRESULT WINAPI ddraw_surface4_QueryInterface(IDirectDrawSurface4 *iface, REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static HRESULT WINAPI ddraw_surface3_QueryInterface(IDirectDrawSurface3 *iface, REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static HRESULT WINAPI ddraw_surface2_QueryInterface(IDirectDrawSurface2 *iface, REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static HRESULT WINAPI ddraw_surface1_QueryInterface(IDirectDrawSurface *iface, REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static HRESULT WINAPI ddraw_gamma_control_QueryInterface(IDirectDrawGammaControl *iface,
        REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirectDrawGammaControl(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static HRESULT WINAPI d3d_texture2_QueryInterface(IDirect3DTexture2 *iface, REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirect3DTexture2(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static HRESULT WINAPI d3d_texture1_QueryInterface(IDirect3DTexture *iface, REFIID riid, void **object)
{
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return ddraw_surface7_QueryInterface(&surface->IDirectDrawSurface7_iface, riid, object);
}

static void ddraw_surface_add_iface(struct qemu_surface *surface)
{
    ULONG iface_count = InterlockedIncrement(&surface->iface_count);
    WINE_TRACE("%p increasing iface count to %u.\n", surface, iface_count);

    if (iface_count == 1)
    {
        WINE_FIXME("Interface count raised from the dead, I should probably AddRef the host interface!\n");
        if (surface->ifaceToRelease)
            IUnknown_AddRef(surface->ifaceToRelease);
    }
}

/*****************************************************************************
 * IDirectDrawSurface7::AddRef
 *
 * A normal addref implementation
 *
 * Returns:
 *  The new refcount
 *
 *****************************************************************************/
static ULONG WINAPI ddraw_surface7_AddRef(IDirectDrawSurface7 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    ULONG refcount = InterlockedIncrement(&surface->ref7);

    WINE_TRACE("iface %p increasing refcount to %u.\n", iface, refcount);

    if (refcount == 1)
    {
        ddraw_surface_add_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface4_AddRef(IDirectDrawSurface4 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    ULONG refcount = InterlockedIncrement(&surface->ref4);

    WINE_TRACE("iface %p increasing refcount to %u.\n", iface, refcount);

    if (refcount == 1)
    {
        ddraw_surface_add_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface3_AddRef(IDirectDrawSurface3 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    ULONG refcount = InterlockedIncrement(&surface->ref3);

    WINE_TRACE("iface %p increasing refcount to %u.\n", iface, refcount);

    if (refcount == 1)
    {
        ddraw_surface_add_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface2_AddRef(IDirectDrawSurface2 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    ULONG refcount = InterlockedIncrement(&surface->ref2);

    WINE_TRACE("iface %p increasing refcount to %u.\n", iface, refcount);

    if (refcount == 1)
    {
        ddraw_surface_add_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface1_AddRef(IDirectDrawSurface *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    ULONG refcount = InterlockedIncrement(&surface->ref1);

    WINE_TRACE("iface %p increasing refcount to %u.\n", iface, refcount);

    if (refcount == 1)
    {
        ddraw_surface_add_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_gamma_control_AddRef(IDirectDrawGammaControl *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawGammaControl(iface);
    ULONG refcount = InterlockedIncrement(&surface->gamma_count);

    WINE_TRACE("iface %p increasing refcount to %u.\n", iface, refcount);

    if (refcount == 1)
    {
        ddraw_surface_add_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI d3d_texture2_AddRef(IDirect3DTexture2 *iface)
{
    struct qemu_surface *surface = impl_from_IDirect3DTexture2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(surface->texture_outer);
}

static ULONG WINAPI d3d_texture1_AddRef(IDirect3DTexture *iface)
{
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_AddRef(surface->texture_outer);
}

void __fastcall ddraw_surface_destroy_cb(struct qemu_surface *surface)
{
    WINE_TRACE("Executing destroy cb!\n");
    if (surface->clipper)
        IDirectDrawClipper_Release(&surface->clipper->IDirectDrawClipper_iface);
}

static ULONG ddraw_surface_release_iface(struct qemu_surface *surface)
{
    ULONG iface_count;
    struct qemu_ddraw_surface1_Release call;

    /* Prevent the surface from being destroyed if it's still attached to
     * another surface. It will be destroyed when the root is destroyed. */
    if (surface->iface_count == 1 && surface->attached_iface)
        IUnknown_AddRef(surface->attached_iface);
    iface_count = InterlockedDecrement(&surface->iface_count);

    WINE_TRACE("%p decreasing iface count to %u.\n", surface, iface_count);

    if (!iface_count)
    {
        IUnknown *release_iface = surface->ifaceToRelease;

        if (surface->device1)
            IUnknown_Release(&surface->device1->IUnknown_inner);

        call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_RELEASE);
        call.iface = (ULONG_PTR)surface;
        qemu_syscall(&call.super);

        /* Release this after destroying the host surface to make sure we hold the last reference
         * to the host ddraw object. Otherwise we'll get false warnings about an unexpected host
         * refcount. */
        if (release_iface)
            IUnknown_Release(release_iface);
    }

    return iface_count;
}

static ULONG WINAPI ddraw_surface7_Release(IDirectDrawSurface7 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    ULONG refcount = InterlockedDecrement(&surface->ref7);

    WINE_TRACE("iface %p decreasing refcount to %u.\n", iface, refcount);

    if (refcount == 0)
    {
        ddraw_surface_release_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface4_Release(IDirectDrawSurface4 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    ULONG refcount = InterlockedDecrement(&surface->ref4);

    WINE_TRACE("iface %p decreasing refcount to %u.\n", iface, refcount);

    if (refcount == 0)
    {
        ddraw_surface_release_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface3_Release(IDirectDrawSurface3 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    ULONG refcount = InterlockedDecrement(&surface->ref3);

    WINE_TRACE("iface %p decreasing refcount to %u.\n", iface, refcount);

    if (refcount == 0)
    {
        ddraw_surface_release_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface2_Release(IDirectDrawSurface2 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    ULONG refcount = InterlockedDecrement(&surface->ref2);

    WINE_TRACE("iface %p decreasing refcount to %u.\n", iface, refcount);

    if (refcount == 0)
    {
        ddraw_surface_release_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_surface1_Release(IDirectDrawSurface *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    ULONG refcount = InterlockedDecrement(&surface->ref1);

    WINE_TRACE("iface %p decreasing refcount to %u.\n", iface, refcount);

    if (refcount == 0)
    {
        ddraw_surface_release_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI ddraw_gamma_control_Release(IDirectDrawGammaControl *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawGammaControl(iface);
    ULONG refcount = InterlockedDecrement(&surface->gamma_count);

    WINE_TRACE("iface %p decreasing refcount to %u.\n", iface, refcount);

    if (refcount == 0)
    {
        ddraw_surface_release_iface(surface);
    }

    return refcount;
}

static ULONG WINAPI d3d_texture2_Release(IDirect3DTexture2 *iface)
{
    struct qemu_surface *surface = impl_from_IDirect3DTexture2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(surface->texture_outer);
}

static ULONG WINAPI d3d_texture1_Release(IDirect3DTexture *iface)
{
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);

    WINE_TRACE("iface %p.\n", iface);

    return IUnknown_Release(surface->texture_outer);
}

#else

void qemu_ddraw_surface_QI_Device(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface_QI_Device *c = (struct qemu_ddraw_surface_QI_Device *)call;
    struct qemu_surface *surface;
    struct qemu_device *device;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    device = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*device));
    if (!device)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirectDrawSurface_QueryInterface(surface->host_surface1,
            QEMU_G2H(c->iid), (void **)&device->host1);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, device);
        return;
    }

    c->device = QEMU_H2G(device);
}

void qemu_ddraw_surface1_Release(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_Release *c = (struct qemu_ddraw_surface1_Release *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    if (surface->host_texture1)
        IDirect3DTexture_Release(surface->host_texture1);
    if (surface->host_texture2)
        IDirect3DTexture_Release(surface->host_texture2);

    c->super.iret = IDirectDrawSurface_Release(surface->host_surface1);
    c->super.iret += IDirectDrawSurface2_Release(surface->host_surface2);
    c->super.iret += IDirectDrawSurface3_Release(surface->host_surface3);
    c->super.iret += IDirectDrawSurface4_Release(surface->host_surface4);
    c->super.iret += IDirectDrawSurface7_Release(surface->host_surface7);

    if (surface->host_gamma)
        c->super.iret += IDirectDrawGammaControl_Release(surface->host_gamma);

    if (c->super.iret)
        WINE_ERR("Unexpected host interface refcount sum %lu\n", c->super.iret);

    /* surface is released by the private data callback. */
}

#endif

struct qemu_ddraw_surface_GetAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetAttachedSurface(IDirectDrawSurface7 *iface, DDSCAPS2 *caps, IDirectDrawSurface7 **Surface)
{
    struct qemu_ddraw_surface_GetAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        struct qemu_surface *attach = (struct qemu_surface *)(ULONG_PTR)call.attachment;
        *Surface = &attach->IDirectDrawSurface7_iface;
        IDirectDrawSurface7_AddRef(*Surface);
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface4_GetAttachedSurface(IDirectDrawSurface4 *iface, DDSCAPS2 *caps, IDirectDrawSurface4 **attachment)
{
    struct qemu_ddraw_surface_GetAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        struct qemu_surface *attach = (struct qemu_surface *)(ULONG_PTR)call.attachment;
        *attachment = &attach->IDirectDrawSurface4_iface;
        IDirectDrawSurface4_AddRef(*attachment);
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface3_GetAttachedSurface(IDirectDrawSurface3 *iface, DDSCAPS *caps, IDirectDrawSurface3 **attachment)
{
    struct qemu_ddraw_surface_GetAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        struct qemu_surface *attach = (struct qemu_surface *)(ULONG_PTR)call.attachment;
        *attachment = &attach->IDirectDrawSurface3_iface;
        IDirectDrawSurface3_AddRef(*attachment);
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface2_GetAttachedSurface(IDirectDrawSurface2 *iface, DDSCAPS *caps, IDirectDrawSurface2 **attachment)
{
    struct qemu_ddraw_surface_GetAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        struct qemu_surface *attach = (struct qemu_surface *)(ULONG_PTR)call.attachment;
        *attachment = &attach->IDirectDrawSurface2_iface;
        IDirectDrawSurface2_AddRef(*attachment);
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface1_GetAttachedSurface(IDirectDrawSurface *iface, DDSCAPS *caps, IDirectDrawSurface **attachment)
{
    struct qemu_ddraw_surface_GetAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);
    {
        struct qemu_surface *attach = (struct qemu_surface *)(ULONG_PTR)call.attachment;
        *attachment = &attach->IDirectDrawSurface_iface;
        IDirectDrawSurface_AddRef(*attachment);
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface_GetAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface_GetAttachedSurface *c = (struct qemu_ddraw_surface_GetAttachedSurface *)call;
    struct qemu_surface *surface, *attach_impl;
    IUnknown *attachment;
    IDirectDrawSurface7 *host;
    IUnknown *priv;
    DWORD size = sizeof(priv);

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETATTACHEDSURFACE):
            c->super.iret = IDirectDrawSurface7_GetAttachedSurface(surface->host_surface7, QEMU_G2H(c->caps),
                    (IDirectDrawSurface7 **)&attachment);
            break;
        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETATTACHEDSURFACE):
            c->super.iret = IDirectDrawSurface4_GetAttachedSurface(surface->host_surface4, QEMU_G2H(c->caps),
                    (IDirectDrawSurface4 **)&attachment);
            break;
        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETATTACHEDSURFACE):
            c->super.iret = IDirectDrawSurface3_GetAttachedSurface(surface->host_surface3, QEMU_G2H(c->caps),
                    (IDirectDrawSurface3 **)&attachment);
            break;
        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETATTACHEDSURFACE):
            c->super.iret = IDirectDrawSurface2_GetAttachedSurface(surface->host_surface2, QEMU_G2H(c->caps),
                    (IDirectDrawSurface2 **)&attachment);
            break;
        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETATTACHEDSURFACE):
            c->super.iret = IDirectDrawSurface_GetAttachedSurface(surface->host_surface1, QEMU_G2H(c->caps),
                    (IDirectDrawSurface **)&attachment);
            break;
    }
    if (FAILED(c->super.iret))
        return;

    IUnknown_QueryInterface(attachment, &IID_IDirectDrawSurface7, (void **)&host);
    IUnknown_Release(attachment);

    /* No, this does not addref the stored IUnknown interface. */
    if (FAILED(IDirectDrawSurface7_GetPrivateData(host, &surface_priv_uuid, &priv, &size)))
        WINE_ERR("Failed to get private data.\n");

    attach_impl = surface_impl_from_IUnknown(priv);
    WINE_TRACE("Found surface implemention %p from host surface %p (v7 %p).\n", attach_impl, attachment, host);
    c->attachment = QEMU_H2G(attach_impl);

    /* Um, we really should addref the guest interface before releasing this here, but we can't easily. */
    IDirectDrawSurface7_Release(host);
}

#endif

struct qemu_ddraw_surface_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
    uint64_t surface_desc;
    uint64_t flags;
    uint64_t h;
    uint64_t version;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_Lock(IDirectDrawSurface7 *iface, RECT *rect, DDSURFACEDESC2 *surface_desc, DWORD flags, HANDLE h)
{
    struct qemu_ddraw_surface_Lock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_LOCK);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;
    call.h = (ULONG_PTR)h;
    call.version = surface->version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface4_Lock(IDirectDrawSurface4 *iface, RECT *rect, DDSURFACEDESC2 *surface_desc, DWORD flags, HANDLE h)
{
    struct qemu_ddraw_surface_Lock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_LOCK);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;
    call.h = (ULONG_PTR)h;
    call.version = surface->version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface3_Lock(IDirectDrawSurface3 *iface, RECT *rect, DDSURFACEDESC *surface_desc, DWORD flags, HANDLE h)
{
    struct qemu_ddraw_surface_Lock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_LOCK);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;
    call.h = (ULONG_PTR)h;
    call.version = surface->version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface2_Lock(IDirectDrawSurface2 *iface, RECT *rect, DDSURFACEDESC *surface_desc, DWORD flags, HANDLE h)
{
    struct qemu_ddraw_surface_Lock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_LOCK);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;
    call.h = (ULONG_PTR)h;
    call.version = surface->version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface1_Lock(IDirectDrawSurface *iface, RECT *rect, DDSURFACEDESC *surface_desc, DWORD flags, HANDLE h)
{
    struct qemu_ddraw_surface_Lock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_LOCK);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;
    call.h = (ULONG_PTR)h;
    call.version = surface->version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface_Lock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface_Lock *c = (struct qemu_ddraw_surface_Lock *)call;
    struct qemu_surface *surface;
    DDSURFACEDESC2 stack, *desc = &stack;
    struct qemu_DDSURFACEDESC2 *desc32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    desc = QEMU_G2H(c->surface_desc);
#else
    desc32 = QEMU_G2H(c->surface_desc);
    if (!desc32)
        desc = NULL;
    else if (desc32->dwSize == sizeof(*desc32))
        desc->dwSize = sizeof(*desc);
    else if (desc32->dwSize == sizeof(struct qemu_DDSURFACEDESC))
        desc->dwSize = sizeof(DDSURFACEDESC);
    else
        desc->dwSize = 0;
#endif

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_LOCK):
            c->super.iret = IDirectDrawSurface7_Lock(surface->host_surface7, QEMU_G2H(c->rect),
                    desc, c->flags, QEMU_G2H(c->h));
            break;

        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_LOCK):
            c->super.iret = IDirectDrawSurface4_Lock(surface->host_surface4, QEMU_G2H(c->rect),
                    desc, c->flags, QEMU_G2H(c->h));
            break;

        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_LOCK):
            c->super.iret = IDirectDrawSurface3_Lock(surface->host_surface3, QEMU_G2H(c->rect),
                    (DDSURFACEDESC *)desc, c->flags, QEMU_G2H(c->h));
            break;

        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_LOCK):
            c->super.iret = IDirectDrawSurface2_Lock(surface->host_surface2, QEMU_G2H(c->rect),
                    (DDSURFACEDESC *)desc, c->flags, QEMU_G2H(c->h));
            break;

        case QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_LOCK):
            c->super.iret = IDirectDrawSurface_Lock(surface->host_surface1, QEMU_G2H(c->rect),
                    (DDSURFACEDESC *)desc, c->flags, QEMU_G2H(c->h));
            break;
    }

#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(c->super.iret))
    {
        /* Managed (and sysmem) textures accept invalid lock sizes in IDirectDrawSurface7. Assume those are
         * DDSURFACEDESC2 sized. */
        if (desc32->dwSize == sizeof(*desc32) || c->version == 7)
            DDSURFACEDESC2_h2g(desc32, desc);
        else if(desc32->dwSize == sizeof(struct qemu_DDSURFACEDESC))
            DDSURFACEDESC_h2g((struct qemu_DDSURFACEDESC *)desc32, (DDSURFACEDESC *)desc);
        else
            WINE_ERR("Lock succeeded despite invalid size.\n");
    }
    else if (desc32 && desc32->dwSize == sizeof(*desc32) || desc32->dwSize == sizeof(struct qemu_DDSURFACEDESC))
    {
        desc32->lpSurface = (ULONG_PTR)desc->lpSurface;
    }
#endif
}

#endif

struct qemu_ddraw_surface7_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pRect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_Unlock(IDirectDrawSurface7 *iface, RECT *pRect)
{
    struct qemu_ddraw_surface7_Unlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_UNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.pRect = (ULONG_PTR)pRect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_Unlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_Unlock *c = (struct qemu_ddraw_surface7_Unlock *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_Unlock(surface->host_surface7, QEMU_G2H(c->pRect));
}

#endif

struct qemu_ddraw_surface4_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pRect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_Unlock(IDirectDrawSurface4 *iface, RECT *pRect)
{
    struct qemu_ddraw_surface4_Unlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_UNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.pRect = (ULONG_PTR)pRect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_Unlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_Unlock *c = (struct qemu_ddraw_surface4_Unlock *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_Unlock(surface->host_surface4, QEMU_G2H(c->pRect));
}

#endif

struct qemu_ddraw_surface3_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_Unlock(IDirectDrawSurface3 *iface, void *data)
{
    struct qemu_ddraw_surface3_Unlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_UNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_Unlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_Unlock *c = (struct qemu_ddraw_surface3_Unlock *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_Unlock(surface->host_surface3, QEMU_G2H(c->data));
}

#endif

struct qemu_ddraw_surface2_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_Unlock(IDirectDrawSurface2 *iface, void *data)
{
    struct qemu_ddraw_surface2_Unlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_UNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_Unlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_Unlock *c = (struct qemu_ddraw_surface2_Unlock *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_Unlock(surface->host_surface2, QEMU_G2H(c->data));
}

#endif

struct qemu_ddraw_surface1_Unlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_Unlock(IDirectDrawSurface *iface, void *data)
{
    struct qemu_ddraw_surface1_Unlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_UNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_Unlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_Unlock *c = (struct qemu_ddraw_surface1_Unlock *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_Unlock(surface->host_surface1, QEMU_G2H(c->data));
}

#endif

struct qemu_ddraw_surface7_Flip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_Flip(IDirectDrawSurface7 *iface, IDirectDrawSurface7 *src, DWORD flags)
{
    struct qemu_ddraw_surface7_Flip call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    struct qemu_surface *src_impl = unsafe_impl_from_IDirectDrawSurface7(src);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_FLIP);
    call.iface = (ULONG_PTR)surface;
    call.src = (ULONG_PTR)src_impl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_Flip(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_Flip *c = (struct qemu_ddraw_surface7_Flip *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src);

    c->super.iret = IDirectDrawSurface7_Flip(surface->host_surface7, src ? src->host_surface7 : NULL, c->flags);
}

#endif

struct qemu_ddraw_surface4_Flip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_Flip(IDirectDrawSurface4 *iface, IDirectDrawSurface4 *src, DWORD flags)
{
    struct qemu_ddraw_surface4_Flip call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_surface *src_impl = unsafe_impl_from_IDirectDrawSurface4(src);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_FLIP);
    call.iface = (ULONG_PTR)surface;
    call.src = (ULONG_PTR)src_impl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_Flip(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_Flip *c = (struct qemu_ddraw_surface4_Flip *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src);

    c->super.iret = IDirectDrawSurface4_Flip(surface->host_surface4, src ? src->host_surface4 : NULL, c->flags);
}

#endif

struct qemu_ddraw_surface3_Flip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_Flip(IDirectDrawSurface3 *iface, IDirectDrawSurface3 *src, DWORD flags)
{
    struct qemu_ddraw_surface3_Flip call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    struct qemu_surface *src_impl = unsafe_impl_from_IDirectDrawSurface3(src);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_FLIP);
    call.iface = (ULONG_PTR)surface;
    call.src = (ULONG_PTR)src_impl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_Flip(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_Flip *c = (struct qemu_ddraw_surface3_Flip *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src);

    c->super.iret = IDirectDrawSurface3_Flip(surface->host_surface3, src ? src->host_surface3 : NULL, c->flags);
}

#endif

struct qemu_ddraw_surface2_Flip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_Flip(IDirectDrawSurface2 *iface, IDirectDrawSurface2 *src, DWORD flags)
{
    struct qemu_ddraw_surface2_Flip call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    struct qemu_surface *src_impl = unsafe_impl_from_IDirectDrawSurface2(src);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_FLIP);
    call.iface = (ULONG_PTR)surface;
    call.src = (ULONG_PTR)src_impl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_Flip(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_Flip *c = (struct qemu_ddraw_surface2_Flip *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src);

    c->super.iret = IDirectDrawSurface2_Flip(surface->host_surface2, src ? src->host_surface2 : NULL, c->flags);
}

#endif

struct qemu_ddraw_surface1_Flip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_Flip(IDirectDrawSurface *iface, IDirectDrawSurface *src, DWORD flags)
{
    struct qemu_ddraw_surface1_Flip call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_surface *src_impl = unsafe_impl_from_IDirectDrawSurface(src);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_FLIP);
    call.iface = (ULONG_PTR)surface;
    call.src = (ULONG_PTR)src_impl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_Flip(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_Flip *c = (struct qemu_ddraw_surface1_Flip *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src);

    c->super.iret = IDirectDrawSurface_Flip(surface->host_surface1, src ? src->host_surface1 : NULL, c->flags);
}

#endif

struct qemu_ddraw_surface7_Blt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_rect;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_Blt(IDirectDrawSurface7 *iface, RECT *dst_rect, IDirectDrawSurface7 *src_surface, RECT *src_rect, DWORD flags, DDBLTFX *fx)
{
    struct qemu_ddraw_surface7_Blt call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface7(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_BLT);
    call.iface = (ULONG_PTR)surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_Blt(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_Blt *c = (struct qemu_ddraw_surface7_Blt *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;
    DDBLTFX stack, *fx = &stack;
    struct qemu_DDBLTFX *fx32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

#if HOST_BIT == GUEST_BIT
    fx = QEMU_G2H(c->fx);
#else
    fx32 = QEMU_G2H(c->fx);

    if (fx32)
        DDBLTFX_g2h(fx, fx32);
    else
        fx = NULL;
#endif

    c->super.iret = IDirectDrawSurface7_Blt(surface->host_surface7, QEMU_G2H(c->dst_rect),
            src ? src->host_surface7 : NULL, QEMU_G2H(c->src_rect), c->flags, fx);
}

#endif

struct qemu_ddraw_surface4_Blt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_rect;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_Blt(IDirectDrawSurface4 *iface, RECT *dst_rect, IDirectDrawSurface4 *src_surface,
        RECT *src_rect, DWORD flags, DDBLTFX *fx)
{
    struct qemu_ddraw_surface4_Blt call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface4(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_BLT);
    call.iface = (ULONG_PTR)surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_Blt(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_Blt *c = (struct qemu_ddraw_surface4_Blt *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;
    DDBLTFX stack, *fx = &stack;
    struct qemu_DDBLTFX *fx32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

#if HOST_BIT == GUEST_BIT
    fx = QEMU_G2H(c->fx);
#else
    fx32 = QEMU_G2H(c->fx);

    if (fx32)
        DDBLTFX_g2h(fx, fx32);
    else
        fx = NULL;
#endif

    c->super.iret = IDirectDrawSurface4_Blt(surface->host_surface4, QEMU_G2H(c->dst_rect),
            src ? src->host_surface4 : NULL, QEMU_G2H(c->src_rect), c->flags, fx);
}

#endif

struct qemu_ddraw_surface3_Blt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_rect;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_Blt(IDirectDrawSurface3 *iface, RECT *dst_rect, IDirectDrawSurface3 *src_surface,
        RECT *src_rect, DWORD flags, DDBLTFX *fx)
{
    struct qemu_ddraw_surface3_Blt call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface3(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_BLT);
    call.iface = (ULONG_PTR)surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_Blt(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_Blt *c = (struct qemu_ddraw_surface3_Blt *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;
    DDBLTFX stack, *fx = &stack;
    struct qemu_DDBLTFX *fx32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

#if HOST_BIT == GUEST_BIT
    fx = QEMU_G2H(c->fx);
#else
    fx32 = QEMU_G2H(c->fx);

    if (fx32)
        DDBLTFX_g2h(fx, fx32);
    else
        fx = NULL;
#endif

    c->super.iret = IDirectDrawSurface3_Blt(surface->host_surface3, QEMU_G2H(c->dst_rect),
            src ? src->host_surface3 : NULL, QEMU_G2H(c->src_rect), c->flags, fx);
}

#endif

struct qemu_ddraw_surface2_Blt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_rect;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_Blt(IDirectDrawSurface2 *iface, RECT *dst_rect, IDirectDrawSurface2 *src_surface,
        RECT *src_rect, DWORD flags, DDBLTFX *fx)
{
    struct qemu_ddraw_surface2_Blt call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface2(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_BLT);
    call.iface = (ULONG_PTR)surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_Blt(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_Blt *c = (struct qemu_ddraw_surface2_Blt *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;
    DDBLTFX stack, *fx = &stack;
    struct qemu_DDBLTFX *fx32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

#if HOST_BIT == GUEST_BIT
    fx = QEMU_G2H(c->fx);
#else
    fx32 = QEMU_G2H(c->fx);

    if (fx32)
        DDBLTFX_g2h(fx, fx32);
    else
        fx = NULL;
#endif

    c->super.iret = IDirectDrawSurface2_Blt(surface->host_surface2, QEMU_G2H(c->dst_rect),
            src ? src->host_surface2 : NULL, QEMU_G2H(c->src_rect), c->flags, fx);
}

#endif

struct qemu_ddraw_surface1_Blt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_rect;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_Blt(IDirectDrawSurface *iface, RECT *dst_rect, IDirectDrawSurface *src_surface,
        RECT *src_rect, DWORD flags, DDBLTFX *fx)
{
    struct qemu_ddraw_surface1_Blt call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_BLT);
    call.iface = (ULONG_PTR)surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_Blt(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_Blt *c = (struct qemu_ddraw_surface1_Blt *)call;
    struct qemu_surface *surface;
    struct qemu_surface *src;
    DDBLTFX stack, *fx = &stack;
    struct qemu_DDBLTFX *fx32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

#if HOST_BIT == GUEST_BIT
    fx = QEMU_G2H(c->fx);
#else
    fx32 = QEMU_G2H(c->fx);

    if (fx32)
        DDBLTFX_g2h(fx, fx32);
    else
        fx = NULL;
#endif

    c->super.iret = IDirectDrawSurface_Blt(surface->host_surface1, QEMU_G2H(c->dst_rect),
            src ? src->host_surface1 : NULL, QEMU_G2H(c->src_rect), c->flags, fx);
}

#endif

struct qemu_ddraw_surface7_AddAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_AddAttachedSurface(IDirectDrawSurface7 *iface, IDirectDrawSurface7 *attachment)
{
    struct qemu_ddraw_surface7_AddAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    struct qemu_surface *attach = unsafe_impl_from_IDirectDrawSurface7(attachment);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_ADDATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.attachment = (ULONG_PTR)attach;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        attach->attached_iface = (IUnknown *)attachment;
        IUnknown_AddRef(attach->attached_iface);
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_AddAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_AddAttachedSurface *c = (struct qemu_ddraw_surface7_AddAttachedSurface *)call;
    struct qemu_surface *surface;
    struct qemu_surface *attachment;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    attachment = QEMU_G2H(c->attachment);

    c->super.iret = IDirectDrawSurface7_AddAttachedSurface(surface->host_surface7,
            attachment ? attachment->host_surface7 : NULL);
}

#endif

struct qemu_ddraw_surface4_AddAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_AddAttachedSurface(IDirectDrawSurface4 *iface, IDirectDrawSurface4 *attachment)
{
    struct qemu_ddraw_surface4_AddAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_surface *attach = unsafe_impl_from_IDirectDrawSurface4(attachment);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_ADDATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.attachment = (ULONG_PTR)attach;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        attach->attached_iface = (IUnknown *)attachment;
        IUnknown_AddRef(attach->attached_iface);
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_AddAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_AddAttachedSurface *c = (struct qemu_ddraw_surface4_AddAttachedSurface *)call;
    struct qemu_surface *surface;
    struct qemu_surface *attachment;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    attachment = QEMU_G2H(c->attachment);

    c->super.iret = IDirectDrawSurface4_AddAttachedSurface(surface->host_surface4,
            attachment ? attachment->host_surface4 : NULL);
}

#endif

struct qemu_ddraw_surface3_AddAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_AddAttachedSurface(IDirectDrawSurface3 *iface, IDirectDrawSurface3 *attachment)
{
    struct qemu_ddraw_surface3_AddAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    struct qemu_surface *attach = unsafe_impl_from_IDirectDrawSurface3(attachment);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_ADDATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.attachment = (ULONG_PTR)attach;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        attach->attached_iface = (IUnknown *)attachment;
        IUnknown_AddRef(attach->attached_iface);
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_AddAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_AddAttachedSurface *c = (struct qemu_ddraw_surface3_AddAttachedSurface *)call;
    struct qemu_surface *surface;
    struct qemu_surface *attachment;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    attachment = QEMU_G2H(c->attachment);

    c->super.iret = IDirectDrawSurface3_AddAttachedSurface(surface->host_surface3,
            attachment ? attachment->host_surface3 : NULL);
}

#endif

struct qemu_ddraw_surface2_AddAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_AddAttachedSurface(IDirectDrawSurface2 *iface, IDirectDrawSurface2 *attachment)
{
    struct qemu_ddraw_surface2_AddAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    struct qemu_surface *attach = unsafe_impl_from_IDirectDrawSurface2(attachment);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_ADDATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.attachment = (ULONG_PTR)attach;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        attach->attached_iface = (IUnknown *)attachment;
        IUnknown_AddRef(attach->attached_iface);
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_AddAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_AddAttachedSurface *c = (struct qemu_ddraw_surface2_AddAttachedSurface *)call;
    struct qemu_surface *surface;
    struct qemu_surface *attachment;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    attachment = QEMU_G2H(c->attachment);

    c->super.iret = IDirectDrawSurface4_AddAttachedSurface(surface->host_surface2,
            attachment ? attachment->host_surface2 : NULL);
}

#endif

struct qemu_ddraw_surface1_AddAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_AddAttachedSurface(IDirectDrawSurface *iface, IDirectDrawSurface *attachment)
{
    struct qemu_ddraw_surface1_AddAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_surface *attach = unsafe_impl_from_IDirectDrawSurface(attachment);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_ADDATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.attachment = (ULONG_PTR)attach;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        attach->attached_iface = (IUnknown *)attachment;
        IUnknown_AddRef(attach->attached_iface);
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_AddAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_AddAttachedSurface *c = (struct qemu_ddraw_surface1_AddAttachedSurface *)call;
    struct qemu_surface *surface;
    struct qemu_surface *attachment;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    attachment = QEMU_G2H(c->attachment);

    c->super.iret = IDirectDrawSurface_AddAttachedSurface(surface->host_surface1,
            attachment ? attachment->host_surface1 : NULL);
}

#endif

struct qemu_ddraw_surface7_DeleteAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_DeleteAttachedSurface(IDirectDrawSurface7 *iface, DWORD flags, IDirectDrawSurface7 *attachment)
{
    struct qemu_ddraw_surface7_DeleteAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_DELETEATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_DeleteAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_DeleteAttachedSurface *c = (struct qemu_ddraw_surface7_DeleteAttachedSurface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_DeleteAttachedSurface(surface->host_surface7, c->flags, QEMU_G2H(c->attachment));
}

#endif

struct qemu_ddraw_surface4_DeleteAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_DeleteAttachedSurface(IDirectDrawSurface4 *iface, DWORD flags, IDirectDrawSurface4 *attachment)
{
    struct qemu_ddraw_surface4_DeleteAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_DELETEATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_DeleteAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_DeleteAttachedSurface *c = (struct qemu_ddraw_surface4_DeleteAttachedSurface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_DeleteAttachedSurface(surface->host_surface4, c->flags, QEMU_G2H(c->attachment));
}

#endif

struct qemu_ddraw_surface3_DeleteAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_DeleteAttachedSurface(IDirectDrawSurface3 *iface, DWORD flags, IDirectDrawSurface3 *attachment)
{
    struct qemu_ddraw_surface3_DeleteAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_DELETEATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_DeleteAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_DeleteAttachedSurface *c = (struct qemu_ddraw_surface3_DeleteAttachedSurface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_DeleteAttachedSurface(surface->host_surface3, c->flags, QEMU_G2H(c->attachment));
}

#endif

struct qemu_ddraw_surface2_DeleteAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_DeleteAttachedSurface(IDirectDrawSurface2 *iface, DWORD flags, IDirectDrawSurface2 *attachment)
{
    struct qemu_ddraw_surface2_DeleteAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_DELETEATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_DeleteAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_DeleteAttachedSurface *c = (struct qemu_ddraw_surface2_DeleteAttachedSurface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_DeleteAttachedSurface(surface->host_surface2, c->flags, QEMU_G2H(c->attachment));
}

#endif

struct qemu_ddraw_surface1_DeleteAttachedSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t attachment;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_DeleteAttachedSurface(IDirectDrawSurface *iface, DWORD flags, IDirectDrawSurface *attachment)
{
    struct qemu_ddraw_surface1_DeleteAttachedSurface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_DELETEATTACHEDSURFACE);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.attachment = (ULONG_PTR)attachment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_DeleteAttachedSurface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_DeleteAttachedSurface *c = (struct qemu_ddraw_surface1_DeleteAttachedSurface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_DeleteAttachedSurface(surface->host_surface1, c->flags, QEMU_G2H(c->attachment));
}

#endif

struct qemu_ddraw_surface7_AddOverlayDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_AddOverlayDirtyRect(IDirectDrawSurface7 *iface, RECT *Rect)
{
    struct qemu_ddraw_surface7_AddOverlayDirtyRect call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_ADDOVERLAYDIRTYRECT);
    call.iface = (ULONG_PTR)surface;
    call.Rect = (ULONG_PTR)Rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_AddOverlayDirtyRect(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_AddOverlayDirtyRect *c = (struct qemu_ddraw_surface7_AddOverlayDirtyRect *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_AddOverlayDirtyRect(surface->host_surface7, QEMU_G2H(c->Rect));
}

#endif

struct qemu_ddraw_surface4_AddOverlayDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_AddOverlayDirtyRect(IDirectDrawSurface4 *iface, RECT *rect)
{
    struct qemu_ddraw_surface4_AddOverlayDirtyRect call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_ADDOVERLAYDIRTYRECT);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_AddOverlayDirtyRect(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_AddOverlayDirtyRect *c = (struct qemu_ddraw_surface4_AddOverlayDirtyRect *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_AddOverlayDirtyRect(surface->host_surface4, QEMU_G2H(c->rect));
}

#endif

struct qemu_ddraw_surface3_AddOverlayDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_AddOverlayDirtyRect(IDirectDrawSurface3 *iface, RECT *rect)
{
    struct qemu_ddraw_surface3_AddOverlayDirtyRect call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_ADDOVERLAYDIRTYRECT);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_AddOverlayDirtyRect(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_AddOverlayDirtyRect *c = (struct qemu_ddraw_surface3_AddOverlayDirtyRect *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_AddOverlayDirtyRect(surface->host_surface3, QEMU_G2H(c->rect));
}

#endif

struct qemu_ddraw_surface2_AddOverlayDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_AddOverlayDirtyRect(IDirectDrawSurface2 *iface, RECT *rect)
{
    struct qemu_ddraw_surface2_AddOverlayDirtyRect call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_ADDOVERLAYDIRTYRECT);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_AddOverlayDirtyRect(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_AddOverlayDirtyRect *c = (struct qemu_ddraw_surface2_AddOverlayDirtyRect *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_AddOverlayDirtyRect(surface->host_surface2, QEMU_G2H(c->rect));
}

#endif

struct qemu_ddraw_surface1_AddOverlayDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_AddOverlayDirtyRect(IDirectDrawSurface *iface, RECT *rect)
{
    struct qemu_ddraw_surface1_AddOverlayDirtyRect call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_ADDOVERLAYDIRTYRECT);
    call.iface = (ULONG_PTR)surface;
    call.rect = (ULONG_PTR)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_AddOverlayDirtyRect(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_AddOverlayDirtyRect *c = (struct qemu_ddraw_surface1_AddOverlayDirtyRect *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_AddOverlayDirtyRect(surface->host_surface1, QEMU_G2H(c->rect));
}

#endif

struct qemu_ddraw_surface7_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetDC(IDirectDrawSurface7 *iface, HDC *dc)
{
    struct qemu_ddraw_surface7_GetDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETDC);
    call.iface = (ULONG_PTR)surface;

    /* This call is tricky. It zeroes *dc on some error conditions, but not
     * all of them. Try to pass the decision on to the host implementation. */
    if (!dc)
    {
        WINE_WARN("dc is NULL.\n");
        return DDERR_INVALIDPARAMS;
    }
    call.dc = guest_HANDLE_g2h(*dc);

    qemu_syscall(&call.super);

    *dc = (HANDLE)(ULONG_PTR)call.dc;

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetDC *c = (struct qemu_ddraw_surface7_GetDC *)call;
    struct qemu_surface *surface;
    HDC dc;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    dc = QEMU_G2H(c->dc);

    c->super.iret = IDirectDrawSurface7_GetDC(surface->host_surface7, &dc);

    c->dc = QEMU_H2G(dc);
}

#endif

struct qemu_ddraw_surface4_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetDC(IDirectDrawSurface4 *iface, HDC *dc)
{
    struct qemu_ddraw_surface4_GetDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETDC);
    call.iface = (ULONG_PTR)surface;

    if (!dc)
    {
        WINE_WARN("dc is NULL.\n");
        return DDERR_INVALIDPARAMS;
    }
    call.dc = guest_HANDLE_g2h(*dc);

    qemu_syscall(&call.super);

    *dc = (HANDLE)(ULONG_PTR)call.dc;

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetDC *c = (struct qemu_ddraw_surface4_GetDC *)call;
    struct qemu_surface *surface;
    HDC dc;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    dc = QEMU_G2H(c->dc);

    c->super.iret = IDirectDrawSurface4_GetDC(surface->host_surface4, &dc);

    c->dc = QEMU_H2G(dc);
}

#endif

struct qemu_ddraw_surface3_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetDC(IDirectDrawSurface3 *iface, HDC *dc)
{
    struct qemu_ddraw_surface3_GetDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETDC);
    call.iface = (ULONG_PTR)surface;

    if (!dc)
    {
        WINE_WARN("dc is NULL.\n");
        return DDERR_INVALIDPARAMS;
    }
    call.dc = guest_HANDLE_g2h(*dc);

    qemu_syscall(&call.super);

    *dc = (HANDLE)(ULONG_PTR)call.dc;

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetDC *c = (struct qemu_ddraw_surface3_GetDC *)call;
    struct qemu_surface *surface;
    HDC dc;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    dc = QEMU_G2H(c->dc);

    c->super.iret = IDirectDrawSurface3_GetDC(surface->host_surface3, &dc);

    c->dc = QEMU_H2G(dc);
}

#endif

struct qemu_ddraw_surface2_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetDC(IDirectDrawSurface2 *iface, HDC *dc)
{
    struct qemu_ddraw_surface2_GetDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETDC);
    call.iface = (ULONG_PTR)surface;

    if (!dc)
    {
        WINE_WARN("dc is NULL.\n");
        return DDERR_INVALIDPARAMS;
    }
    call.dc = guest_HANDLE_g2h(*dc);

    qemu_syscall(&call.super);

    *dc = (HANDLE)(ULONG_PTR)call.dc;

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetDC *c = (struct qemu_ddraw_surface2_GetDC *)call;
    struct qemu_surface *surface;
    HDC dc;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    dc = QEMU_G2H(c->dc);

    c->super.iret = IDirectDrawSurface2_GetDC(surface->host_surface2, &dc);

    c->dc = QEMU_H2G(dc);
}

#endif

struct qemu_ddraw_surface1_GetDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetDC(IDirectDrawSurface *iface, HDC *dc)
{
    struct qemu_ddraw_surface1_GetDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETDC);
    call.iface = (ULONG_PTR)surface;

    if (!dc)
    {
        WINE_WARN("dc is NULL.\n");
        return DDERR_INVALIDPARAMS;
    }
    call.dc = guest_HANDLE_g2h(*dc);

    qemu_syscall(&call.super);

    *dc = (HANDLE)(ULONG_PTR)call.dc;

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetDC *c = (struct qemu_ddraw_surface1_GetDC *)call;
    struct qemu_surface *surface;
    HDC dc;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    dc = QEMU_G2H(c->dc);

    c->super.iret = IDirectDrawSurface_GetDC(surface->host_surface1, &dc);

    c->dc = QEMU_H2G(dc);
}

#endif

struct qemu_ddraw_surface7_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_ReleaseDC(IDirectDrawSurface7 *iface, HDC dc)
{
    struct qemu_ddraw_surface7_ReleaseDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = guest_HANDLE_g2h(dc);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_ReleaseDC *c = (struct qemu_ddraw_surface7_ReleaseDC *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_ReleaseDC(surface->host_surface7, QEMU_G2H(c->dc));
}

#endif

struct qemu_ddraw_surface4_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_ReleaseDC(IDirectDrawSurface4 *iface, HDC dc)
{
    struct qemu_ddraw_surface4_ReleaseDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = guest_HANDLE_g2h(dc);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_ReleaseDC *c = (struct qemu_ddraw_surface4_ReleaseDC *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_ReleaseDC(surface->host_surface4, QEMU_G2H(c->dc));
}

#endif

struct qemu_ddraw_surface3_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_ReleaseDC(IDirectDrawSurface3 *iface, HDC dc)
{
    struct qemu_ddraw_surface3_ReleaseDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = guest_HANDLE_g2h(dc);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_ReleaseDC *c = (struct qemu_ddraw_surface3_ReleaseDC *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_ReleaseDC(surface->host_surface3, QEMU_G2H(c->dc));
}

#endif

struct qemu_ddraw_surface2_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_ReleaseDC(IDirectDrawSurface2 *iface, HDC dc)
{
    struct qemu_ddraw_surface2_ReleaseDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = guest_HANDLE_g2h(dc);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_ReleaseDC *c = (struct qemu_ddraw_surface2_ReleaseDC *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_ReleaseDC(surface->host_surface2, QEMU_G2H(c->dc));
}

#endif

struct qemu_ddraw_surface1_ReleaseDC
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_ReleaseDC(IDirectDrawSurface *iface, HDC dc)
{
    struct qemu_ddraw_surface1_ReleaseDC call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_RELEASEDC);
    call.iface = (ULONG_PTR)surface;
    call.dc = guest_HANDLE_g2h(dc);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_ReleaseDC *c = (struct qemu_ddraw_surface1_ReleaseDC *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_ReleaseDC(surface->host_surface1, QEMU_G2H(c->dc));
}

#endif

struct qemu_ddraw_surface7_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetCaps(IDirectDrawSurface7 *iface, DDSCAPS2 *Caps)
{
    struct qemu_ddraw_surface7_GetCaps call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETCAPS);
    call.iface = (ULONG_PTR)surface;
    call.Caps = (ULONG_PTR)Caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetCaps *c = (struct qemu_ddraw_surface7_GetCaps *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetCaps(surface->host_surface7, QEMU_G2H(c->Caps));
}

#endif

struct qemu_ddraw_surface4_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetCaps(IDirectDrawSurface4 *iface, DDSCAPS2 *caps)
{
    struct qemu_ddraw_surface4_GetCaps call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETCAPS);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetCaps *c = (struct qemu_ddraw_surface4_GetCaps *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetCaps(surface->host_surface4, QEMU_G2H(c->caps));
}

#endif

struct qemu_ddraw_surface3_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetCaps(IDirectDrawSurface3 *iface, DDSCAPS *caps)
{
    struct qemu_ddraw_surface3_GetCaps call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETCAPS);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetCaps *c = (struct qemu_ddraw_surface3_GetCaps *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetCaps(surface->host_surface3, QEMU_G2H(c->caps));
}

#endif

struct qemu_ddraw_surface2_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetCaps(IDirectDrawSurface2 *iface, DDSCAPS *caps)
{
    struct qemu_ddraw_surface2_GetCaps call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETCAPS);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetCaps *c = (struct qemu_ddraw_surface2_GetCaps *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetCaps(surface->host_surface2, QEMU_G2H(c->caps));
}

#endif

struct qemu_ddraw_surface1_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetCaps(IDirectDrawSurface *iface, DDSCAPS *caps)
{
    struct qemu_ddraw_surface1_GetCaps call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETCAPS);
    call.iface = (ULONG_PTR)surface;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetCaps *c = (struct qemu_ddraw_surface1_GetCaps *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetCaps(surface->host_surface1, QEMU_G2H(c->caps));
}

#endif

struct qemu_ddraw_surface7_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetPriority(IDirectDrawSurface7 *iface, DWORD priority)
{
    struct qemu_ddraw_surface7_SetPriority call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETPRIORITY);
    call.iface = (ULONG_PTR)surface;
    call.priority = priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetPriority(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetPriority *c = (struct qemu_ddraw_surface7_SetPriority *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_SetPriority(surface->host_surface7, c->priority);
}

#endif

struct qemu_ddraw_surface7_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetPriority(IDirectDrawSurface7 *iface, DWORD *priority)
{
    struct qemu_ddraw_surface7_GetPriority call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETPRIORITY);
    call.iface = (ULONG_PTR)surface;
    call.priority = (ULONG_PTR)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetPriority(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetPriority *c = (struct qemu_ddraw_surface7_GetPriority *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetPriority(surface->host_surface7, QEMU_G2H(c->priority));
}

#endif

struct qemu_ddraw_surface7_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tag;
    uint64_t data;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetPrivateData(IDirectDrawSurface7 *iface, REFGUID tag, void *data, DWORD size, DWORD flags)
{
    struct qemu_ddraw_surface7_SetPrivateData call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.tag = (ULONG_PTR)tag;
    call.data = (ULONG_PTR)data;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetPrivateData *c = (struct qemu_ddraw_surface7_SetPrivateData *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_SetPrivateData(surface->host_surface7, QEMU_G2H(c->tag), QEMU_G2H(c->data), c->size, c->flags);
}

#endif

struct qemu_ddraw_surface4_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tag;
    uint64_t data;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_SetPrivateData(IDirectDrawSurface4 *iface, REFGUID tag, void *data, DWORD size, DWORD flags)
{
    struct qemu_ddraw_surface4_SetPrivateData call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.tag = (ULONG_PTR)tag;
    call.data = (ULONG_PTR)data;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_SetPrivateData *c = (struct qemu_ddraw_surface4_SetPrivateData *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_SetPrivateData(surface->host_surface4, QEMU_G2H(c->tag), QEMU_G2H(c->data), c->size, c->flags);
}

#endif

struct qemu_ddraw_surface7_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tag;
    uint64_t data;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetPrivateData(IDirectDrawSurface7 *iface, REFGUID tag, void *data, DWORD *size)
{
    struct qemu_ddraw_surface7_GetPrivateData call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.tag = (ULONG_PTR)tag;
    call.data = (ULONG_PTR)data;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetPrivateData *c = (struct qemu_ddraw_surface7_GetPrivateData *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetPrivateData(surface->host_surface7, QEMU_G2H(c->tag), QEMU_G2H(c->data), QEMU_G2H(c->size));
}

#endif

struct qemu_ddraw_surface4_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tag;
    uint64_t data;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetPrivateData(IDirectDrawSurface4 *iface, REFGUID tag, void *data, DWORD *size)
{
    struct qemu_ddraw_surface4_GetPrivateData call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.tag = (ULONG_PTR)tag;
    call.data = (ULONG_PTR)data;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetPrivateData *c = (struct qemu_ddraw_surface4_GetPrivateData *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetPrivateData(surface->host_surface4, QEMU_G2H(c->tag), QEMU_G2H(c->data), QEMU_G2H(c->size));
}

#endif

struct qemu_ddraw_surface7_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tag;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_FreePrivateData(IDirectDrawSurface7 *iface, REFGUID tag)
{
    struct qemu_ddraw_surface7_FreePrivateData call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_FREEPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.tag = (ULONG_PTR)tag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_FreePrivateData *c = (struct qemu_ddraw_surface7_FreePrivateData *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_FreePrivateData(surface->host_surface7, QEMU_G2H(c->tag));
}

#endif

struct qemu_ddraw_surface4_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t tag;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_FreePrivateData(IDirectDrawSurface4 *iface, REFGUID tag)
{
    struct qemu_ddraw_surface4_FreePrivateData call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_FREEPRIVATEDATA);
    call.iface = (ULONG_PTR)surface;
    call.tag = (ULONG_PTR)tag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_FreePrivateData *c = (struct qemu_ddraw_surface4_FreePrivateData *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_FreePrivateData(surface->host_surface4, QEMU_G2H(c->tag));
}

#endif

struct qemu_ddraw_surface7_PageLock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_PageLock(IDirectDrawSurface7 *iface, DWORD Flags)
{
    struct qemu_ddraw_surface7_PageLock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_PAGELOCK);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_PageLock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_PageLock *c = (struct qemu_ddraw_surface7_PageLock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_PageLock(surface->host_surface7, c->Flags);
}

#endif

struct qemu_ddraw_surface4_PageLock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_PageLock(IDirectDrawSurface4 *iface, DWORD flags)
{
    struct qemu_ddraw_surface4_PageLock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_PAGELOCK);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_PageLock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_PageLock *c = (struct qemu_ddraw_surface4_PageLock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_PageLock(surface->host_surface4, c->flags);
}

#endif

struct qemu_ddraw_surface3_PageLock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_PageLock(IDirectDrawSurface3 *iface, DWORD flags)
{
    struct qemu_ddraw_surface3_PageLock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_PAGELOCK);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_PageLock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_PageLock *c = (struct qemu_ddraw_surface3_PageLock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_PageLock(surface->host_surface3, c->flags);
}

#endif

struct qemu_ddraw_surface2_PageLock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_PageLock(IDirectDrawSurface2 *iface, DWORD flags)
{
    struct qemu_ddraw_surface2_PageLock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_PAGELOCK);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_PageLock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_PageLock *c = (struct qemu_ddraw_surface2_PageLock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_PageLock(surface->host_surface2, c->flags);
}

#endif

struct qemu_ddraw_surface7_PageUnlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_PageUnlock(IDirectDrawSurface7 *iface, DWORD Flags)
{
    struct qemu_ddraw_surface7_PageUnlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_PAGEUNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_PageUnlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_PageUnlock *c = (struct qemu_ddraw_surface7_PageUnlock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_PageUnlock(surface->host_surface7, c->Flags);
}

#endif

struct qemu_ddraw_surface4_PageUnlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_PageUnlock(IDirectDrawSurface4 *iface, DWORD flags)
{
    struct qemu_ddraw_surface4_PageUnlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_PAGEUNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_PageUnlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_PageUnlock *c = (struct qemu_ddraw_surface4_PageUnlock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_PageUnlock(surface->host_surface4, c->flags);
}

#endif

struct qemu_ddraw_surface3_PageUnlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_PageUnlock(IDirectDrawSurface3 *iface, DWORD flags)
{
    struct qemu_ddraw_surface3_PageUnlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_PAGEUNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_PageUnlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_PageUnlock *c = (struct qemu_ddraw_surface3_PageUnlock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_PageUnlock(surface->host_surface3, c->flags);
}

#endif

struct qemu_ddraw_surface2_PageUnlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_PageUnlock(IDirectDrawSurface2 *iface, DWORD flags)
{
    struct qemu_ddraw_surface2_PageUnlock call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_PAGEUNLOCK);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_PageUnlock(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_PageUnlock *c = (struct qemu_ddraw_surface2_PageUnlock *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_PageUnlock(surface->host_surface2, c->flags);
}

#endif

struct qemu_ddraw_surface7_BltBatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Batch;
    uint64_t Count;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_BltBatch(IDirectDrawSurface7 *iface, DDBLTBATCH *Batch, DWORD Count, DWORD Flags)
{
    struct qemu_ddraw_surface7_BltBatch call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_BLTBATCH);
    call.iface = (ULONG_PTR)surface;
    call.Batch = (ULONG_PTR)Batch;
    call.Count = Count;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_BltBatch(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_BltBatch *c = (struct qemu_ddraw_surface7_BltBatch *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_BltBatch(surface->host_surface7, QEMU_G2H(c->Batch), c->Count, c->Flags);
}

#endif

struct qemu_ddraw_surface4_BltBatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t batch;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_BltBatch(IDirectDrawSurface4 *iface, DDBLTBATCH *batch, DWORD count, DWORD flags)
{
    struct qemu_ddraw_surface4_BltBatch call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_BLTBATCH);
    call.iface = (ULONG_PTR)surface;
    call.batch = (ULONG_PTR)batch;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_BltBatch(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_BltBatch *c = (struct qemu_ddraw_surface4_BltBatch *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_BltBatch(surface->host_surface4, QEMU_G2H(c->batch), c->count, c->flags);
}

#endif

struct qemu_ddraw_surface3_BltBatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t batch;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_BltBatch(IDirectDrawSurface3 *iface, DDBLTBATCH *batch, DWORD count, DWORD flags)
{
    struct qemu_ddraw_surface3_BltBatch call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_BLTBATCH);
    call.iface = (ULONG_PTR)surface;
    call.batch = (ULONG_PTR)batch;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_BltBatch(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_BltBatch *c = (struct qemu_ddraw_surface3_BltBatch *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_BltBatch(surface->host_surface3, QEMU_G2H(c->batch), c->count, c->flags);
}

#endif

struct qemu_ddraw_surface2_BltBatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t batch;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_BltBatch(IDirectDrawSurface2 *iface, DDBLTBATCH *batch, DWORD count, DWORD flags)
{
    struct qemu_ddraw_surface2_BltBatch call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_BLTBATCH);
    call.iface = (ULONG_PTR)surface;
    call.batch = (ULONG_PTR)batch;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_BltBatch(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_BltBatch *c = (struct qemu_ddraw_surface2_BltBatch *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_BltBatch(surface->host_surface2, QEMU_G2H(c->batch), c->count, c->flags);
}

#endif

struct qemu_ddraw_surface1_BltBatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t batch;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_BltBatch(IDirectDrawSurface *iface, DDBLTBATCH *batch, DWORD count, DWORD flags)
{
    struct qemu_ddraw_surface1_BltBatch call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_BLTBATCH);
    call.iface = (ULONG_PTR)surface;
    call.batch = (ULONG_PTR)batch;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_BltBatch(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_BltBatch *c = (struct qemu_ddraw_surface1_BltBatch *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_BltBatch(surface->host_surface1, QEMU_G2H(c->batch), c->count, c->flags);
}

#endif

struct qemu_ddraw_surface7_EnumAttachedSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t context;
    uint64_t cb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_EnumAttachedSurfaces(IDirectDrawSurface7 *iface, void *context, LPDDENUMSURFACESCALLBACK7 cb)
{
    struct qemu_ddraw_surface7_EnumAttachedSurfaces call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_ENUMATTACHEDSURFACES);
    call.iface = (ULONG_PTR)surface;
    call.context = (ULONG_PTR)context;
    call.cb = (ULONG_PTR)cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_EnumAttachedSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_EnumAttachedSurfaces *c = (struct qemu_ddraw_surface7_EnumAttachedSurfaces *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_EnumAttachedSurfaces(surface->host_surface7, QEMU_G2H(c->context), QEMU_G2H(c->cb));
}

#endif

struct qemu_ddraw_surface4_EnumAttachedSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_EnumAttachedSurfaces(IDirectDrawSurface4 *iface, void *context, LPDDENUMSURFACESCALLBACK2 callback)
{
    struct qemu_ddraw_surface4_EnumAttachedSurfaces call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_ENUMATTACHEDSURFACES);
    call.iface = (ULONG_PTR)surface;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_EnumAttachedSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_EnumAttachedSurfaces *c = (struct qemu_ddraw_surface4_EnumAttachedSurfaces *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_EnumAttachedSurfaces(surface->host_surface4, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface3_EnumAttachedSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_EnumAttachedSurfaces(IDirectDrawSurface3 *iface, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw_surface3_EnumAttachedSurfaces call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_ENUMATTACHEDSURFACES);
    call.iface = (ULONG_PTR)surface;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_EnumAttachedSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_EnumAttachedSurfaces *c = (struct qemu_ddraw_surface3_EnumAttachedSurfaces *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_EnumAttachedSurfaces(surface->host_surface3, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface2_EnumAttachedSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_EnumAttachedSurfaces(IDirectDrawSurface2 *iface, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw_surface2_EnumAttachedSurfaces call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_ENUMATTACHEDSURFACES);
    call.iface = (ULONG_PTR)surface;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_EnumAttachedSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_EnumAttachedSurfaces *c = (struct qemu_ddraw_surface2_EnumAttachedSurfaces *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_EnumAttachedSurfaces(surface->host_surface2, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface1_EnumAttachedSurfaces
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_EnumAttachedSurfaces(IDirectDrawSurface *iface, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw_surface1_EnumAttachedSurfaces call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_ENUMATTACHEDSURFACES);
    call.iface = (ULONG_PTR)surface;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_EnumAttachedSurfaces(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_EnumAttachedSurfaces *c = (struct qemu_ddraw_surface1_EnumAttachedSurfaces *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_EnumAttachedSurfaces(surface->host_surface1, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface7_EnumOverlayZOrders
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
    uint64_t context;
    uint64_t cb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_EnumOverlayZOrders(IDirectDrawSurface7 *iface, DWORD Flags, void *context, LPDDENUMSURFACESCALLBACK7 cb)
{
    struct qemu_ddraw_surface7_EnumOverlayZOrders call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_ENUMOVERLAYZORDERS);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;
    call.context = (ULONG_PTR)context;
    call.cb = (ULONG_PTR)cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_EnumOverlayZOrders(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_EnumOverlayZOrders *c = (struct qemu_ddraw_surface7_EnumOverlayZOrders *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_EnumOverlayZOrders(surface->host_surface7, c->Flags, QEMU_G2H(c->context), QEMU_G2H(c->cb));
}

#endif

struct qemu_ddraw_surface4_EnumOverlayZOrders
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_EnumOverlayZOrders(IDirectDrawSurface4 *iface, DWORD flags, void *context, LPDDENUMSURFACESCALLBACK2 callback)
{
    struct qemu_ddraw_surface4_EnumOverlayZOrders call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_ENUMOVERLAYZORDERS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_EnumOverlayZOrders(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_EnumOverlayZOrders *c = (struct qemu_ddraw_surface4_EnumOverlayZOrders *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_EnumOverlayZOrders(surface->host_surface4, c->flags, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface3_EnumOverlayZOrders
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_EnumOverlayZOrders(IDirectDrawSurface3 *iface, DWORD flags, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw_surface3_EnumOverlayZOrders call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_ENUMOVERLAYZORDERS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_EnumOverlayZOrders(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_EnumOverlayZOrders *c = (struct qemu_ddraw_surface3_EnumOverlayZOrders *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_EnumOverlayZOrders(surface->host_surface3, c->flags, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface2_EnumOverlayZOrders
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_EnumOverlayZOrders(IDirectDrawSurface2 *iface, DWORD flags, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw_surface2_EnumOverlayZOrders call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_ENUMOVERLAYZORDERS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_EnumOverlayZOrders(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_EnumOverlayZOrders *c = (struct qemu_ddraw_surface2_EnumOverlayZOrders *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_EnumOverlayZOrders(surface->host_surface2, c->flags, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface1_EnumOverlayZOrders
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t context;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_EnumOverlayZOrders(IDirectDrawSurface *iface, DWORD flags, void *context, LPDDENUMSURFACESCALLBACK callback)
{
    struct qemu_ddraw_surface1_EnumOverlayZOrders call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_ENUMOVERLAYZORDERS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.context = (ULONG_PTR)context;
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_EnumOverlayZOrders(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_EnumOverlayZOrders *c = (struct qemu_ddraw_surface1_EnumOverlayZOrders *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_EnumOverlayZOrders(surface->host_surface1, c->flags, QEMU_G2H(c->context), QEMU_G2H(c->callback));
}

#endif

struct qemu_ddraw_surface7_GetBltStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetBltStatus(IDirectDrawSurface7 *iface, DWORD Flags)
{
    struct qemu_ddraw_surface7_GetBltStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETBLTSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetBltStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetBltStatus *c = (struct qemu_ddraw_surface7_GetBltStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetBltStatus(surface->host_surface7, c->Flags);
}

#endif

struct qemu_ddraw_surface4_GetBltStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetBltStatus(IDirectDrawSurface4 *iface, DWORD flags)
{
    struct qemu_ddraw_surface4_GetBltStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETBLTSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetBltStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetBltStatus *c = (struct qemu_ddraw_surface4_GetBltStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetBltStatus(surface->host_surface4, c->flags);
}

#endif

struct qemu_ddraw_surface3_GetBltStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetBltStatus(IDirectDrawSurface3 *iface, DWORD flags)
{
    struct qemu_ddraw_surface3_GetBltStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETBLTSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetBltStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetBltStatus *c = (struct qemu_ddraw_surface3_GetBltStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetBltStatus(surface->host_surface3, c->flags);
}

#endif

struct qemu_ddraw_surface2_GetBltStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetBltStatus(IDirectDrawSurface2 *iface, DWORD flags)
{
    struct qemu_ddraw_surface2_GetBltStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETBLTSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetBltStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetBltStatus *c = (struct qemu_ddraw_surface2_GetBltStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetBltStatus(surface->host_surface2, c->flags);
}

#endif

struct qemu_ddraw_surface1_GetBltStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetBltStatus(IDirectDrawSurface *iface, DWORD flags)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_ddraw_surface1_GetBltStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETBLTSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetBltStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetBltStatus *c = (struct qemu_ddraw_surface1_GetBltStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetBltStatus(surface->host_surface1, c->flags);
}

#endif

struct qemu_ddraw_surface7_GetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
    uint64_t CKey;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetColorKey(IDirectDrawSurface7 *iface, DWORD Flags, DDCOLORKEY *CKey)
{
    struct qemu_ddraw_surface7_GetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;
    call.CKey = (ULONG_PTR)CKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetColorKey *c = (struct qemu_ddraw_surface7_GetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetColorKey(surface->host_surface7, c->Flags, QEMU_G2H(c->CKey));
}

#endif

struct qemu_ddraw_surface4_GetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetColorKey(IDirectDrawSurface4 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface4_GetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetColorKey *c = (struct qemu_ddraw_surface4_GetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetColorKey(surface->host_surface4, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface3_GetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetColorKey(IDirectDrawSurface3 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface3_GetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetColorKey *c = (struct qemu_ddraw_surface3_GetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetColorKey(surface->host_surface3, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface2_GetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetColorKey(IDirectDrawSurface2 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface2_GetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetColorKey *c = (struct qemu_ddraw_surface2_GetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetColorKey(surface->host_surface2, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface1_GetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetColorKey(IDirectDrawSurface *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface1_GetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetColorKey *c = (struct qemu_ddraw_surface1_GetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetColorKey(surface->host_surface1, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface7_GetFlipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetFlipStatus(IDirectDrawSurface7 *iface, DWORD Flags)
{
    struct qemu_ddraw_surface7_GetFlipStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETFLIPSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetFlipStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetFlipStatus *c = (struct qemu_ddraw_surface7_GetFlipStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetFlipStatus(surface->host_surface7, c->Flags);
}

#endif

struct qemu_ddraw_surface4_GetFlipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetFlipStatus(IDirectDrawSurface4 *iface, DWORD flags)
{
    struct qemu_ddraw_surface4_GetFlipStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETFLIPSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetFlipStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetFlipStatus *c = (struct qemu_ddraw_surface4_GetFlipStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetFlipStatus(surface->host_surface4, c->flags);
}

#endif

struct qemu_ddraw_surface3_GetFlipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetFlipStatus(IDirectDrawSurface3 *iface, DWORD flags)
{
    struct qemu_ddraw_surface3_GetFlipStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETFLIPSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetFlipStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetFlipStatus *c = (struct qemu_ddraw_surface3_GetFlipStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetFlipStatus(surface->host_surface3, c->flags);
}

#endif

struct qemu_ddraw_surface2_GetFlipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetFlipStatus(IDirectDrawSurface2 *iface, DWORD flags)
{
    struct qemu_ddraw_surface2_GetFlipStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETFLIPSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetFlipStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetFlipStatus *c = (struct qemu_ddraw_surface2_GetFlipStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetFlipStatus(surface->host_surface2, c->flags);
}

#endif

struct qemu_ddraw_surface1_GetFlipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetFlipStatus(IDirectDrawSurface *iface, DWORD flags)
{
    struct qemu_ddraw_surface1_GetFlipStatus call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETFLIPSTATUS);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetFlipStatus(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetFlipStatus *c = (struct qemu_ddraw_surface1_GetFlipStatus *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetFlipStatus(surface->host_surface1, c->flags);
}

#endif

struct qemu_ddraw_surface7_GetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetOverlayPosition(IDirectDrawSurface7 *iface, LONG *x, LONG *y)
{
    struct qemu_ddraw_surface7_GetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetOverlayPosition *c = (struct qemu_ddraw_surface7_GetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetOverlayPosition(surface->host_surface7, QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_ddraw_surface4_GetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetOverlayPosition(IDirectDrawSurface4 *iface, LONG *x, LONG *y)
{
    struct qemu_ddraw_surface4_GetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetOverlayPosition *c = (struct qemu_ddraw_surface4_GetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetOverlayPosition(surface->host_surface4, QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_ddraw_surface3_GetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetOverlayPosition(IDirectDrawSurface3 *iface, LONG *x, LONG *y)
{
    struct qemu_ddraw_surface3_GetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetOverlayPosition *c = (struct qemu_ddraw_surface3_GetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetOverlayPosition(surface->host_surface3, QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_ddraw_surface2_GetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetOverlayPosition(IDirectDrawSurface2 *iface, LONG *x, LONG *y)
{
    struct qemu_ddraw_surface2_GetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetOverlayPosition *c = (struct qemu_ddraw_surface2_GetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetOverlayPosition(surface->host_surface2, QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_ddraw_surface1_GetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetOverlayPosition(IDirectDrawSurface *iface, LONG *x, LONG *y)
{
    struct qemu_ddraw_surface1_GetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetOverlayPosition *c = (struct qemu_ddraw_surface1_GetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetOverlayPosition(surface->host_surface1, QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_ddraw_surface7_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t PixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetPixelFormat(IDirectDrawSurface7 *iface, DDPIXELFORMAT *PixelFormat)
{
    struct qemu_ddraw_surface7_GetPixelFormat call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)surface;
    call.PixelFormat = (ULONG_PTR)PixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetPixelFormat *c = (struct qemu_ddraw_surface7_GetPixelFormat *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetPixelFormat(surface->host_surface7, QEMU_G2H(c->PixelFormat));
}

#endif

struct qemu_ddraw_surface4_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pixel_format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetPixelFormat(IDirectDrawSurface4 *iface, DDPIXELFORMAT *pixel_format)
{
    struct qemu_ddraw_surface4_GetPixelFormat call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)surface;
    call.pixel_format = (ULONG_PTR)pixel_format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetPixelFormat *c = (struct qemu_ddraw_surface4_GetPixelFormat *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetPixelFormat(surface->host_surface4, QEMU_G2H(c->pixel_format));
}

#endif

struct qemu_ddraw_surface3_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pixel_format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetPixelFormat(IDirectDrawSurface3 *iface, DDPIXELFORMAT *pixel_format)
{
    struct qemu_ddraw_surface3_GetPixelFormat call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)surface;
    call.pixel_format = (ULONG_PTR)pixel_format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetPixelFormat *c = (struct qemu_ddraw_surface3_GetPixelFormat *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetPixelFormat(surface->host_surface3, QEMU_G2H(c->pixel_format));
}

#endif

struct qemu_ddraw_surface2_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pixel_format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetPixelFormat(IDirectDrawSurface2 *iface, DDPIXELFORMAT *pixel_format)
{
    struct qemu_ddraw_surface2_GetPixelFormat call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)surface;
    call.pixel_format = (ULONG_PTR)pixel_format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetPixelFormat *c = (struct qemu_ddraw_surface2_GetPixelFormat *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetPixelFormat(surface->host_surface2, QEMU_G2H(c->pixel_format));
}

#endif

struct qemu_ddraw_surface1_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pixel_format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetPixelFormat(IDirectDrawSurface *iface, DDPIXELFORMAT *pixel_format)
{
    struct qemu_ddraw_surface1_GetPixelFormat call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)surface;
    call.pixel_format = (ULONG_PTR)pixel_format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetPixelFormat *c = (struct qemu_ddraw_surface1_GetPixelFormat *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetPixelFormat(surface->host_surface1, QEMU_G2H(c->pixel_format));
}

#endif

struct qemu_ddraw_surface7_GetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDSD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetSurfaceDesc(IDirectDrawSurface7 *iface, DDSURFACEDESC2 *DDSD)
{
    struct qemu_ddraw_surface7_GetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.DDSD = (ULONG_PTR)DDSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetSurfaceDesc *c = (struct qemu_ddraw_surface7_GetSurfaceDesc *)call;
    struct qemu_surface *surface;
    DDSURFACEDESC2 stack, *desc = &stack;
    struct qemu_DDSURFACEDESC2 *desc32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->DDSD);
#else
    desc32 = QEMU_G2H(c->DDSD);
    if (!desc32)
        desc = NULL;
    else if (desc32->dwSize == sizeof(*desc32))
        desc->dwSize = sizeof(*desc);
    else
        desc->dwSize = 0;
#endif

    c->super.iret = IDirectDrawSurface7_GetSurfaceDesc(surface->host_surface7, desc);

#if HOST_BIT != GUEST_BIT
    if (SUCCEEDED(c->super.iret))
        DDSURFACEDESC2_h2g(desc32, desc);
#endif
}

#endif

struct qemu_ddraw_surface4_GetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDSD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetSurfaceDesc(IDirectDrawSurface4 *iface, DDSURFACEDESC2 *DDSD)
{
    struct qemu_ddraw_surface4_GetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.DDSD = (ULONG_PTR)DDSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetSurfaceDesc *c = (struct qemu_ddraw_surface4_GetSurfaceDesc *)call;
    struct qemu_surface *surface;
    DDSURFACEDESC2 stack, *desc = &stack;
    struct qemu_DDSURFACEDESC2 *desc32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->DDSD);
#else
    desc32 = QEMU_G2H(c->DDSD);
    if (!desc32)
        desc = NULL;
    else if (desc32->dwSize == sizeof(*desc32))
        desc->dwSize = sizeof(*desc);
    else
        desc->dwSize = 0;
#endif

    c->super.iret = IDirectDrawSurface4_GetSurfaceDesc(surface->host_surface4, desc);

#if HOST_BIT != GUEST_BIT
    if (SUCCEEDED(c->super.iret))
        DDSURFACEDESC2_h2g(desc32, desc);
#endif
}

#endif

struct qemu_ddraw_surface3_GetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetSurfaceDesc(IDirectDrawSurface3 *iface, DDSURFACEDESC *surface_desc)
{
    struct qemu_ddraw_surface3_GetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetSurfaceDesc *c = (struct qemu_ddraw_surface3_GetSurfaceDesc *)call;
    struct qemu_surface *surface;
    DDSURFACEDESC stack, *desc = &stack;
    struct qemu_DDSURFACEDESC *desc32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->surface_desc);
#else
    desc32 = QEMU_G2H(c->surface_desc);
    if (!desc32)
        desc = NULL;
    else if (desc32->dwSize == sizeof(*desc32))
        desc->dwSize = sizeof(*desc);
    else
        desc->dwSize = 0;
#endif

    c->super.iret = IDirectDrawSurface3_GetSurfaceDesc(surface->host_surface3, desc);

#if HOST_BIT != GUEST_BIT
    if (SUCCEEDED(c->super.iret))
        DDSURFACEDESC_h2g(desc32, desc);
#endif
}

#endif

struct qemu_ddraw_surface2_GetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDSD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetSurfaceDesc(IDirectDrawSurface2 *iface, DDSURFACEDESC *DDSD)
{
    struct qemu_ddraw_surface2_GetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.DDSD = (ULONG_PTR)DDSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetSurfaceDesc *c = (struct qemu_ddraw_surface2_GetSurfaceDesc *)call;
    struct qemu_surface *surface;
    DDSURFACEDESC stack, *desc = &stack;
    struct qemu_DDSURFACEDESC *desc32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->DDSD);
#else
    desc32 = QEMU_G2H(c->DDSD);
    if (!desc32)
        desc = NULL;
    else if (desc32->dwSize == sizeof(*desc32))
        desc->dwSize = sizeof(*desc);
    else
        desc->dwSize = 0;
#endif

    c->super.iret = IDirectDrawSurface2_GetSurfaceDesc(surface->host_surface2, desc);

#if HOST_BIT != GUEST_BIT
    if (SUCCEEDED(c->super.iret))
        DDSURFACEDESC_h2g(desc32, desc);
#endif
}

#endif

struct qemu_ddraw_surface1_GetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDSD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetSurfaceDesc(IDirectDrawSurface *iface, DDSURFACEDESC *DDSD)
{
    struct qemu_ddraw_surface1_GetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.DDSD = (ULONG_PTR)DDSD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetSurfaceDesc *c = (struct qemu_ddraw_surface1_GetSurfaceDesc *)call;
    struct qemu_surface *surface;
    DDSURFACEDESC stack, *desc = &stack;
    struct qemu_DDSURFACEDESC *desc32;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

#if HOST_BIT == GUEST_BIT
    desc = QEMU_G2H(c->DDSD);
#else
    desc32 = QEMU_G2H(c->DDSD);
    if (!desc32)
        desc = NULL;
    else if (desc32->dwSize == sizeof(*desc32))
        desc->dwSize = sizeof(*desc);
    else
        desc->dwSize = 0;
#endif

    c->super.iret = IDirectDrawSurface_GetSurfaceDesc(surface->host_surface1, desc);

#if HOST_BIT != GUEST_BIT
    if (SUCCEEDED(c->super.iret))
        DDSURFACEDESC_h2g(desc32, desc);
#endif
}

#endif

struct qemu_ddraw_surface7_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_Initialize(IDirectDrawSurface7 *iface, IDirectDraw *ddraw, DDSURFACEDESC2 *surface_desc)
{
    struct qemu_ddraw_surface7_Initialize call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_INITIALIZE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_Initialize *c = (struct qemu_ddraw_surface7_Initialize *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_Initialize(surface->host_surface7, QEMU_G2H(c->ddraw), QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw_surface4_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_Initialize(IDirectDrawSurface4 *iface, IDirectDraw *ddraw, DDSURFACEDESC2 *surface_desc)
{
    struct qemu_ddraw_surface4_Initialize call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_INITIALIZE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_Initialize *c = (struct qemu_ddraw_surface4_Initialize *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_Initialize(surface->host_surface4, QEMU_G2H(c->ddraw), QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw_surface3_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_Initialize(IDirectDrawSurface3 *iface, IDirectDraw *ddraw, DDSURFACEDESC *surface_desc)
{
    struct qemu_ddraw_surface3_Initialize call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_INITIALIZE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_Initialize *c = (struct qemu_ddraw_surface3_Initialize *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_Initialize(surface->host_surface3, QEMU_G2H(c->ddraw), QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw_surface2_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_Initialize(IDirectDrawSurface2 *iface, IDirectDraw *ddraw, DDSURFACEDESC *surface_desc)
{
    struct qemu_ddraw_surface2_Initialize call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_INITIALIZE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_Initialize *c = (struct qemu_ddraw_surface2_Initialize *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_Initialize(surface->host_surface2, QEMU_G2H(c->ddraw), QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_ddraw_surface1_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t surface_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_Initialize(IDirectDrawSurface *iface, IDirectDraw *ddraw, DDSURFACEDESC *surface_desc)
{
    struct qemu_ddraw_surface1_Initialize call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_INITIALIZE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;
    call.surface_desc = (ULONG_PTR)surface_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_Initialize *c = (struct qemu_ddraw_surface1_Initialize *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_Initialize(surface->host_surface1, QEMU_G2H(c->ddraw), QEMU_G2H(c->surface_desc));
}

#endif

struct qemu_d3d_texture1_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture1_Initialize(IDirect3DTexture *iface, IDirect3DDevice *device, IDirectDrawSurface *src)
{
    struct qemu_d3d_texture1_Initialize call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE1_INITIALIZE);
    call.iface = (ULONG_PTR)src;
    call.device = (ULONG_PTR)device;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture1_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d_texture1_Initialize *c = (struct qemu_d3d_texture1_Initialize *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture_Initialize(surface->host_texture1, QEMU_G2H(c->device), QEMU_G2H(c->src));
}

#endif

struct qemu_ddraw_surface7_IsLost
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_IsLost(IDirectDrawSurface7 *iface)
{
    struct qemu_ddraw_surface7_IsLost call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_ISLOST);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_IsLost(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_IsLost *c = (struct qemu_ddraw_surface7_IsLost *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_IsLost(surface->host_surface7);
}

#endif

struct qemu_ddraw_surface4_IsLost
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_IsLost(IDirectDrawSurface4 *iface)
{
    struct qemu_ddraw_surface4_IsLost call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_ISLOST);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_IsLost(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_IsLost *c = (struct qemu_ddraw_surface4_IsLost *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_IsLost(surface->host_surface4);
}

#endif

struct qemu_ddraw_surface3_IsLost
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_IsLost(IDirectDrawSurface3 *iface)
{
    struct qemu_ddraw_surface3_IsLost call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_ISLOST);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_IsLost(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_IsLost *c = (struct qemu_ddraw_surface3_IsLost *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_IsLost(surface->host_surface3);
}

#endif

struct qemu_ddraw_surface2_IsLost
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_IsLost(IDirectDrawSurface2 *iface)
{
    struct qemu_ddraw_surface2_IsLost call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_ISLOST);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_IsLost(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_IsLost *c = (struct qemu_ddraw_surface2_IsLost *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_IsLost(surface->host_surface2);
}

#endif

struct qemu_ddraw_surface1_IsLost
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_IsLost(IDirectDrawSurface *iface)
{
    struct qemu_ddraw_surface1_IsLost call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_ISLOST);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_IsLost(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_IsLost *c = (struct qemu_ddraw_surface1_IsLost *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_IsLost(surface->host_surface1);
}

#endif

struct qemu_ddraw_surface7_Restore
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_Restore(IDirectDrawSurface7 *iface)
{
    struct qemu_ddraw_surface7_Restore call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_RESTORE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_Restore(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_Restore *c = (struct qemu_ddraw_surface7_Restore *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_Restore(surface->host_surface7);
}

#endif

struct qemu_ddraw_surface4_Restore
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_Restore(IDirectDrawSurface4 *iface)
{
    struct qemu_ddraw_surface4_Restore call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_RESTORE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_Restore(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_Restore *c = (struct qemu_ddraw_surface4_Restore *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_Restore(surface->host_surface4);
}

#endif

struct qemu_ddraw_surface3_Restore
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_Restore(IDirectDrawSurface3 *iface)
{
    struct qemu_ddraw_surface3_Restore call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_RESTORE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_Restore(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_Restore *c = (struct qemu_ddraw_surface3_Restore *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_Restore(surface->host_surface3);
}

#endif

struct qemu_ddraw_surface2_Restore
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_Restore(IDirectDrawSurface2 *iface)
{
    struct qemu_ddraw_surface2_Restore call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_RESTORE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_Restore(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_Restore *c = (struct qemu_ddraw_surface2_Restore *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_Restore(surface->host_surface2);
}

#endif

struct qemu_ddraw_surface1_Restore
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_Restore(IDirectDrawSurface *iface)
{
    struct qemu_ddraw_surface1_Restore call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_RESTORE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_Restore(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_Restore *c = (struct qemu_ddraw_surface1_Restore *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_Restore(surface->host_surface1);
}

#endif

struct qemu_ddraw_surface7_SetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetOverlayPosition(IDirectDrawSurface7 *iface, LONG x, LONG y)
{
    struct qemu_ddraw_surface7_SetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetOverlayPosition *c = (struct qemu_ddraw_surface7_SetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_SetOverlayPosition(surface->host_surface7, c->x, c->y);
}

#endif

struct qemu_ddraw_surface4_SetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_SetOverlayPosition(IDirectDrawSurface4 *iface, LONG x, LONG y)
{
    struct qemu_ddraw_surface4_SetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_SETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_SetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_SetOverlayPosition *c = (struct qemu_ddraw_surface4_SetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_SetOverlayPosition(surface->host_surface4, c->x, c->y);
}

#endif

struct qemu_ddraw_surface3_SetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_SetOverlayPosition(IDirectDrawSurface3 *iface, LONG x, LONG y)
{
    struct qemu_ddraw_surface3_SetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_SETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_SetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_SetOverlayPosition *c = (struct qemu_ddraw_surface3_SetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_SetOverlayPosition(surface->host_surface3, c->x, c->y);
}

#endif

struct qemu_ddraw_surface2_SetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_SetOverlayPosition(IDirectDrawSurface2 *iface, LONG x, LONG y)
{
    struct qemu_ddraw_surface2_SetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_SETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_SetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_SetOverlayPosition *c = (struct qemu_ddraw_surface2_SetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_SetOverlayPosition(surface->host_surface2, c->x, c->y);
}

#endif

struct qemu_ddraw_surface1_SetOverlayPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_SetOverlayPosition(IDirectDrawSurface *iface, LONG x, LONG y)
{
    struct qemu_ddraw_surface1_SetOverlayPosition call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_SETOVERLAYPOSITION);
    call.iface = (ULONG_PTR)surface;
    call.x = x;
    call.y = y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_SetOverlayPosition(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_SetOverlayPosition *c = (struct qemu_ddraw_surface1_SetOverlayPosition *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_SetOverlayPosition(surface->host_surface1, c->x, c->y);
}

#endif

struct qemu_ddraw_surface7_UpdateOverlay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_UpdateOverlay(IDirectDrawSurface7 *iface, RECT *src_rect, IDirectDrawSurface7 *dst_surface, RECT *dst_rect, DWORD flags, DDOVERLAYFX *fx)
{
    struct qemu_ddraw_surface7_UpdateOverlay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_UPDATEOVERLAY);
    call.iface = (ULONG_PTR)surface;
    call.src_rect = (ULONG_PTR)src_rect;
    call.dst_surface = (ULONG_PTR)dst_surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_UpdateOverlay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_UpdateOverlay *c = (struct qemu_ddraw_surface7_UpdateOverlay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_UpdateOverlay(surface->host_surface7, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_surface), QEMU_G2H(c->dst_rect), c->flags, QEMU_G2H(c->fx));
}

#endif

struct qemu_ddraw_surface4_UpdateOverlay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_UpdateOverlay(IDirectDrawSurface4 *iface, RECT *src_rect, IDirectDrawSurface4 *dst_surface, RECT *dst_rect, DWORD flags, DDOVERLAYFX *fx)
{
    struct qemu_ddraw_surface4_UpdateOverlay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_UPDATEOVERLAY);
    call.iface = (ULONG_PTR)surface;
    call.src_rect = (ULONG_PTR)src_rect;
    call.dst_surface = (ULONG_PTR)dst_surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_UpdateOverlay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_UpdateOverlay *c = (struct qemu_ddraw_surface4_UpdateOverlay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_UpdateOverlay(surface->host_surface4, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_surface), QEMU_G2H(c->dst_rect), c->flags, QEMU_G2H(c->fx));
}

#endif

struct qemu_ddraw_surface3_UpdateOverlay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_UpdateOverlay(IDirectDrawSurface3 *iface, RECT *src_rect, IDirectDrawSurface3 *dst_surface, RECT *dst_rect, DWORD flags, DDOVERLAYFX *fx)
{
    struct qemu_ddraw_surface3_UpdateOverlay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_UPDATEOVERLAY);
    call.iface = (ULONG_PTR)surface;
    call.src_rect = (ULONG_PTR)src_rect;
    call.dst_surface = (ULONG_PTR)dst_surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_UpdateOverlay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_UpdateOverlay *c = (struct qemu_ddraw_surface3_UpdateOverlay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_UpdateOverlay(surface->host_surface3, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_surface), QEMU_G2H(c->dst_rect), c->flags, QEMU_G2H(c->fx));
}

#endif

struct qemu_ddraw_surface2_UpdateOverlay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_UpdateOverlay(IDirectDrawSurface2 *iface, RECT *src_rect, IDirectDrawSurface2 *dst_surface, RECT *dst_rect, DWORD flags, DDOVERLAYFX *fx)
{
    struct qemu_ddraw_surface2_UpdateOverlay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_UPDATEOVERLAY);
    call.iface = (ULONG_PTR)surface;
    call.src_rect = (ULONG_PTR)src_rect;
    call.dst_surface = (ULONG_PTR)dst_surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_UpdateOverlay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_UpdateOverlay *c = (struct qemu_ddraw_surface2_UpdateOverlay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_UpdateOverlay(surface->host_surface2, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_surface), QEMU_G2H(c->dst_rect), c->flags, QEMU_G2H(c->fx));
}

#endif

struct qemu_ddraw_surface1_UpdateOverlay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_rect;
    uint64_t flags;
    uint64_t fx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_UpdateOverlay(IDirectDrawSurface *iface, RECT *src_rect, IDirectDrawSurface *dst_surface, RECT *dst_rect, DWORD flags, DDOVERLAYFX *fx)
{
    struct qemu_ddraw_surface1_UpdateOverlay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_UPDATEOVERLAY);
    call.iface = (ULONG_PTR)surface;
    call.src_rect = (ULONG_PTR)src_rect;
    call.dst_surface = (ULONG_PTR)dst_surface;
    call.dst_rect = (ULONG_PTR)dst_rect;
    call.flags = flags;
    call.fx = (ULONG_PTR)fx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_UpdateOverlay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_UpdateOverlay *c = (struct qemu_ddraw_surface1_UpdateOverlay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_UpdateOverlay(surface->host_surface1, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_surface), QEMU_G2H(c->dst_rect), c->flags, QEMU_G2H(c->fx));
}

#endif

struct qemu_ddraw_surface7_UpdateOverlayDisplay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_UpdateOverlayDisplay(IDirectDrawSurface7 *iface, DWORD Flags)
{
    struct qemu_ddraw_surface7_UpdateOverlayDisplay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_UPDATEOVERLAYDISPLAY);
    call.iface = (ULONG_PTR)surface;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_UpdateOverlayDisplay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_UpdateOverlayDisplay *c = (struct qemu_ddraw_surface7_UpdateOverlayDisplay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_UpdateOverlayDisplay(surface->host_surface7, c->Flags);
}

#endif

struct qemu_ddraw_surface4_UpdateOverlayDisplay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_UpdateOverlayDisplay(IDirectDrawSurface4 *iface, DWORD flags)
{
    struct qemu_ddraw_surface4_UpdateOverlayDisplay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_UPDATEOVERLAYDISPLAY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_UpdateOverlayDisplay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_UpdateOverlayDisplay *c = (struct qemu_ddraw_surface4_UpdateOverlayDisplay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_UpdateOverlayDisplay(surface->host_surface4, c->flags);
}

#endif

struct qemu_ddraw_surface3_UpdateOverlayDisplay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_UpdateOverlayDisplay(IDirectDrawSurface3 *iface, DWORD flags)
{
    struct qemu_ddraw_surface3_UpdateOverlayDisplay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_UPDATEOVERLAYDISPLAY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_UpdateOverlayDisplay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_UpdateOverlayDisplay *c = (struct qemu_ddraw_surface3_UpdateOverlayDisplay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_UpdateOverlayDisplay(surface->host_surface3, c->flags);
}

#endif

struct qemu_ddraw_surface2_UpdateOverlayDisplay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_UpdateOverlayDisplay(IDirectDrawSurface2 *iface, DWORD flags)
{
    struct qemu_ddraw_surface2_UpdateOverlayDisplay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_UPDATEOVERLAYDISPLAY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_UpdateOverlayDisplay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_UpdateOverlayDisplay *c = (struct qemu_ddraw_surface2_UpdateOverlayDisplay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_UpdateOverlayDisplay(surface->host_surface2, c->flags);
}

#endif

struct qemu_ddraw_surface1_UpdateOverlayDisplay
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_UpdateOverlayDisplay(IDirectDrawSurface *iface, DWORD flags)
{
    struct qemu_ddraw_surface1_UpdateOverlayDisplay call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_UPDATEOVERLAYDISPLAY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_UpdateOverlayDisplay(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_UpdateOverlayDisplay *c = (struct qemu_ddraw_surface1_UpdateOverlayDisplay *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_UpdateOverlayDisplay(surface->host_surface1, c->flags);
}

#endif

struct qemu_ddraw_surface7_UpdateOverlayZOrder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t reference;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_UpdateOverlayZOrder(IDirectDrawSurface7 *iface, DWORD flags, IDirectDrawSurface7 *reference)
{
    struct qemu_ddraw_surface7_UpdateOverlayZOrder call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_UPDATEOVERLAYZORDER);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.reference = (ULONG_PTR)reference;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_UpdateOverlayZOrder(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_UpdateOverlayZOrder *c = (struct qemu_ddraw_surface7_UpdateOverlayZOrder *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_UpdateOverlayZOrder(surface->host_surface7, c->flags, QEMU_G2H(c->reference));
}

#endif

struct qemu_ddraw_surface4_UpdateOverlayZOrder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t reference;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_UpdateOverlayZOrder(IDirectDrawSurface4 *iface, DWORD flags, IDirectDrawSurface4 *reference)
{
    struct qemu_ddraw_surface4_UpdateOverlayZOrder call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_UPDATEOVERLAYZORDER);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.reference = (ULONG_PTR)reference;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_UpdateOverlayZOrder(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_UpdateOverlayZOrder *c = (struct qemu_ddraw_surface4_UpdateOverlayZOrder *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_UpdateOverlayZOrder(surface->host_surface4, c->flags, QEMU_G2H(c->reference));
}

#endif

struct qemu_ddraw_surface3_UpdateOverlayZOrder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t reference;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_UpdateOverlayZOrder(IDirectDrawSurface3 *iface, DWORD flags, IDirectDrawSurface3 *reference)
{
    struct qemu_ddraw_surface3_UpdateOverlayZOrder call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_UPDATEOVERLAYZORDER);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.reference = (ULONG_PTR)reference;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_UpdateOverlayZOrder(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_UpdateOverlayZOrder *c = (struct qemu_ddraw_surface3_UpdateOverlayZOrder *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_UpdateOverlayZOrder(surface->host_surface3, c->flags, QEMU_G2H(c->reference));
}

#endif

struct qemu_ddraw_surface2_UpdateOverlayZOrder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t reference;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_UpdateOverlayZOrder(IDirectDrawSurface2 *iface, DWORD flags, IDirectDrawSurface2 *reference)
{
    struct qemu_ddraw_surface2_UpdateOverlayZOrder call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_UPDATEOVERLAYZORDER);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.reference = (ULONG_PTR)reference;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_UpdateOverlayZOrder(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_UpdateOverlayZOrder *c = (struct qemu_ddraw_surface2_UpdateOverlayZOrder *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_UpdateOverlayZOrder(surface->host_surface2, c->flags, QEMU_G2H(c->reference));
}

#endif

struct qemu_ddraw_surface1_UpdateOverlayZOrder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t reference;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_UpdateOverlayZOrder(IDirectDrawSurface *iface, DWORD flags, IDirectDrawSurface *reference)
{
    struct qemu_ddraw_surface1_UpdateOverlayZOrder call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_UPDATEOVERLAYZORDER);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.reference = (ULONG_PTR)reference;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_UpdateOverlayZOrder(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_UpdateOverlayZOrder *c = (struct qemu_ddraw_surface1_UpdateOverlayZOrder *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_UpdateOverlayZOrder(surface->host_surface1, c->flags, QEMU_G2H(c->reference));
}

#endif

struct qemu_ddraw_surface7_GetDDInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetDDInterface(IDirectDrawSurface7 *iface, void **DD)
{
    struct qemu_ddraw_surface7_GetDDInterface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETDDINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.DD = (ULONG_PTR)DD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetDDInterface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetDDInterface *c = (struct qemu_ddraw_surface7_GetDDInterface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetDDInterface(surface->host_surface7, QEMU_G2H(c->DD));
}

#endif

struct qemu_ddraw_surface4_GetDDInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetDDInterface(IDirectDrawSurface4 *iface, void **ddraw)
{
    struct qemu_ddraw_surface4_GetDDInterface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETDDINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetDDInterface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetDDInterface *c = (struct qemu_ddraw_surface4_GetDDInterface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetDDInterface(surface->host_surface4, QEMU_G2H(c->ddraw));
}

#endif

struct qemu_ddraw_surface3_GetDDInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetDDInterface(IDirectDrawSurface3 *iface, void **ddraw)
{
    struct qemu_ddraw_surface3_GetDDInterface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETDDINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetDDInterface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetDDInterface *c = (struct qemu_ddraw_surface3_GetDDInterface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetDDInterface(surface->host_surface3, QEMU_G2H(c->ddraw));
}

#endif

struct qemu_ddraw_surface2_GetDDInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetDDInterface(IDirectDrawSurface2 *iface, void **ddraw)
{
    struct qemu_ddraw_surface2_GetDDInterface call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETDDINTERFACE);
    call.iface = (ULONG_PTR)surface;
    call.ddraw = (ULONG_PTR)ddraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetDDInterface(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetDDInterface *c = (struct qemu_ddraw_surface2_GetDDInterface *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetDDInterface(surface->host_surface2, QEMU_G2H(c->ddraw));
}

#endif

struct qemu_ddraw_surface7_ChangeUniquenessValue
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_ChangeUniquenessValue(IDirectDrawSurface7 *iface)
{
    struct qemu_ddraw_surface7_ChangeUniquenessValue call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_CHANGEUNIQUENESSVALUE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_ChangeUniquenessValue(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_ChangeUniquenessValue *c = (struct qemu_ddraw_surface7_ChangeUniquenessValue *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_ChangeUniquenessValue(surface->host_surface7);
}

#endif

struct qemu_ddraw_surface4_ChangeUniquenessValue
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_ChangeUniquenessValue(IDirectDrawSurface4 *iface)
{
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_ddraw_surface4_ChangeUniquenessValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_CHANGEUNIQUENESSVALUE);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_ChangeUniquenessValue(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_ChangeUniquenessValue *c = (struct qemu_ddraw_surface4_ChangeUniquenessValue *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_ChangeUniquenessValue(surface->host_surface4);
}

#endif

struct qemu_ddraw_surface7_GetUniquenessValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pValue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetUniquenessValue(IDirectDrawSurface7 *iface, DWORD *pValue)
{
    struct qemu_ddraw_surface7_GetUniquenessValue call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETUNIQUENESSVALUE);
    call.iface = (ULONG_PTR)surface;
    call.pValue = (ULONG_PTR)pValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetUniquenessValue(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetUniquenessValue *c = (struct qemu_ddraw_surface7_GetUniquenessValue *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetUniquenessValue(surface->host_surface7, QEMU_G2H(c->pValue));
}

#endif

struct qemu_ddraw_surface4_GetUniquenessValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pValue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetUniquenessValue(IDirectDrawSurface4 *iface, DWORD *pValue)
{
    struct qemu_ddraw_surface4_GetUniquenessValue call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETUNIQUENESSVALUE);
    call.iface = (ULONG_PTR)surface;
    call.pValue = (ULONG_PTR)pValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetUniquenessValue(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetUniquenessValue *c = (struct qemu_ddraw_surface4_GetUniquenessValue *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetUniquenessValue(surface->host_surface4, QEMU_G2H(c->pValue));
}

#endif

struct qemu_ddraw_surface7_SetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t MaxLOD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetLOD(IDirectDrawSurface7 *iface, DWORD MaxLOD)
{
    struct qemu_ddraw_surface7_SetLOD call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETLOD);
    call.iface = (ULONG_PTR)surface;
    call.MaxLOD = MaxLOD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetLOD(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetLOD *c = (struct qemu_ddraw_surface7_SetLOD *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_SetLOD(surface->host_surface7, c->MaxLOD);
}

#endif

struct qemu_ddraw_surface7_GetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t MaxLOD;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetLOD(IDirectDrawSurface7 *iface, DWORD *MaxLOD)
{
    struct qemu_ddraw_surface7_GetLOD call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETLOD);
    call.iface = (ULONG_PTR)surface;
    call.MaxLOD = (ULONG_PTR)MaxLOD;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetLOD(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetLOD *c = (struct qemu_ddraw_surface7_GetLOD *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetLOD(surface->host_surface7, QEMU_G2H(c->MaxLOD));
}

#endif

struct qemu_ddraw_surface7_BltFast
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t trans;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_BltFast(IDirectDrawSurface7 *iface, DWORD dst_x, DWORD dst_y,
        IDirectDrawSurface7 *src_surface, RECT *src_rect, DWORD trans)
{
    struct qemu_ddraw_surface7_BltFast call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface7(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_BLTFAST);
    call.iface = (ULONG_PTR)surface;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.trans = trans;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_BltFast(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_BltFast *c = (struct qemu_ddraw_surface7_BltFast *)call;
    struct qemu_surface *surface, *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

    c->super.iret = IDirectDrawSurface7_BltFast(surface->host_surface7, c->dst_x, c->dst_y,
            src ? src->host_surface7 : NULL, QEMU_G2H(c->src_rect), c->trans);
}

#endif

struct qemu_ddraw_surface4_BltFast
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_BltFast(IDirectDrawSurface4 *iface, DWORD dst_x, DWORD dst_y,
        IDirectDrawSurface4 *src_surface, RECT *src_rect, DWORD flags)
{
    struct qemu_ddraw_surface4_BltFast call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface4(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_BLTFAST);
    call.iface = (ULONG_PTR)surface;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_BltFast(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_BltFast *c = (struct qemu_ddraw_surface4_BltFast *)call;
    struct qemu_surface *surface, *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

    c->super.iret = IDirectDrawSurface4_BltFast(surface->host_surface4, c->dst_x, c->dst_y,
            src ? src->host_surface4 : NULL, QEMU_G2H(c->src_rect), c->flags);
}

#endif

struct qemu_ddraw_surface3_BltFast
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_BltFast(IDirectDrawSurface3 *iface, DWORD dst_x, DWORD dst_y,
        IDirectDrawSurface3 *src_surface, RECT *src_rect, DWORD flags)
{
    struct qemu_ddraw_surface3_BltFast call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_BLTFAST);
    call.iface = (ULONG_PTR)surface;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.src_surface = (ULONG_PTR)src_surface;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_BltFast(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_BltFast *c = (struct qemu_ddraw_surface3_BltFast *)call;
    struct qemu_surface *surface, *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

    c->super.iret = IDirectDrawSurface3_BltFast(surface->host_surface3, c->dst_x, c->dst_y,
            src ? src->host_surface3 : NULL, QEMU_G2H(c->src_rect), c->flags);
}

#endif

struct qemu_ddraw_surface2_BltFast
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_BltFast(IDirectDrawSurface2 *iface, DWORD dst_x, DWORD dst_y,
            IDirectDrawSurface2 *src_surface, RECT *src_rect, DWORD flags)
{
    struct qemu_ddraw_surface2_BltFast call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface2(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_BLTFAST);
    call.iface = (ULONG_PTR)surface;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_BltFast(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_BltFast *c = (struct qemu_ddraw_surface2_BltFast *)call;
    struct qemu_surface *surface, *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

    c->super.iret = IDirectDrawSurface2_BltFast(surface->host_surface2, c->dst_x, c->dst_y,
            src ? src->host_surface2 : NULL, QEMU_G2H(c->src_rect), c->flags);
}

#endif

struct qemu_ddraw_surface1_BltFast
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_x;
    uint64_t dst_y;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_BltFast(IDirectDrawSurface *iface, DWORD dst_x, DWORD dst_y,
        IDirectDrawSurface *src_surface, RECT *src_rect, DWORD flags)
{
    struct qemu_ddraw_surface1_BltFast call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_surface *src = unsafe_impl_from_IDirectDrawSurface(src_surface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_BLTFAST);
    call.iface = (ULONG_PTR)surface;
    call.dst_x = dst_x;
    call.dst_y = dst_y;
    call.src_surface = (ULONG_PTR)src;
    call.src_rect = (ULONG_PTR)src_rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_BltFast(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_BltFast *c = (struct qemu_ddraw_surface1_BltFast *)call;
    struct qemu_surface *surface, *src;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);

    c->super.iret = IDirectDrawSurface_BltFast(surface->host_surface1, c->dst_x, c->dst_y,
            src ? src->host_surface1 : NULL, QEMU_G2H(c->src_rect), c->flags);
}

#endif

struct qemu_ddraw_surface7_GetClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t Clipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetClipper(IDirectDrawSurface7 *iface, IDirectDrawClipper **Clipper)
{
    struct qemu_ddraw_surface7_GetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.Clipper = (ULONG_PTR)Clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetClipper(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetClipper *c = (struct qemu_ddraw_surface7_GetClipper *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetClipper(surface->host_surface7, QEMU_G2H(c->Clipper));
}

#endif

struct qemu_ddraw_surface4_GetClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetClipper(IDirectDrawSurface4 *iface, IDirectDrawClipper **clipper)
{
    struct qemu_ddraw_surface4_GetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetClipper(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetClipper *c = (struct qemu_ddraw_surface4_GetClipper *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetClipper(surface->host_surface4, QEMU_G2H(c->clipper));
}

#endif

struct qemu_ddraw_surface3_GetClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetClipper(IDirectDrawSurface3 *iface, IDirectDrawClipper **clipper)
{
    struct qemu_ddraw_surface3_GetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetClipper(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetClipper *c = (struct qemu_ddraw_surface3_GetClipper *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetClipper(surface->host_surface3, QEMU_G2H(c->clipper));
}

#endif

struct qemu_ddraw_surface2_GetClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetClipper(IDirectDrawSurface2 *iface, IDirectDrawClipper **clipper)
{
    struct qemu_ddraw_surface2_GetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetClipper(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetClipper *c = (struct qemu_ddraw_surface2_GetClipper *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetClipper(surface->host_surface2, QEMU_G2H(c->clipper));
}

#endif

struct qemu_ddraw_surface1_GetClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetClipper(IDirectDrawSurface *iface, IDirectDrawClipper **clipper)
{
    struct qemu_ddraw_surface1_GetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetClipper(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetClipper *c = (struct qemu_ddraw_surface1_GetClipper *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetClipper(surface->host_surface1, QEMU_G2H(c->clipper));
}

#endif

struct qemu_ddraw_surface_SetClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetClipper(IDirectDrawSurface7 *iface, IDirectDrawClipper *iclipper)
{
    struct qemu_ddraw_surface_SetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    struct qemu_clipper *clipper = unsafe_impl_from_IDirectDrawClipper(iclipper);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && clipper != surface->clipper)
    {
        if (clipper)
            IDirectDrawClipper_AddRef(&clipper->IDirectDrawClipper_iface);
        if (surface->clipper)
            IDirectDrawClipper_Release(&surface->clipper->IDirectDrawClipper_iface);
        surface->clipper = clipper;
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface4_SetClipper(IDirectDrawSurface4 *iface, IDirectDrawClipper *iclipper)
{
    struct qemu_ddraw_surface_SetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_clipper *clipper = unsafe_impl_from_IDirectDrawClipper(iclipper);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_SETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && clipper != surface->clipper)
    {
        if (clipper)
            IDirectDrawClipper_AddRef(&clipper->IDirectDrawClipper_iface);
        if (surface->clipper)
            IDirectDrawClipper_Release(&surface->clipper->IDirectDrawClipper_iface);
        surface->clipper = clipper;
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface3_SetClipper(IDirectDrawSurface3 *iface, IDirectDrawClipper *iclipper)
{
    struct qemu_ddraw_surface_SetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    struct qemu_clipper *clipper = unsafe_impl_from_IDirectDrawClipper(iclipper);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_SETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && clipper != surface->clipper)
    {
        if (clipper)
            IDirectDrawClipper_AddRef(&clipper->IDirectDrawClipper_iface);
        if (surface->clipper)
            IDirectDrawClipper_Release(&surface->clipper->IDirectDrawClipper_iface);
        surface->clipper = clipper;
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface2_SetClipper(IDirectDrawSurface2 *iface, IDirectDrawClipper *iclipper)
{
    struct qemu_ddraw_surface_SetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    struct qemu_clipper *clipper = unsafe_impl_from_IDirectDrawClipper(iclipper);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_SETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && clipper != surface->clipper)
    {
        if (clipper)
            IDirectDrawClipper_AddRef(&clipper->IDirectDrawClipper_iface);
        if (surface->clipper)
            IDirectDrawClipper_Release(&surface->clipper->IDirectDrawClipper_iface);
        surface->clipper = clipper;
    }

    return call.super.iret;
}

static HRESULT WINAPI ddraw_surface1_SetClipper(IDirectDrawSurface *iface, IDirectDrawClipper *iclipper)
{
    struct qemu_ddraw_surface_SetClipper call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_clipper *clipper = unsafe_impl_from_IDirectDrawClipper(iclipper);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_SETCLIPPER);
    call.iface = (ULONG_PTR)surface;
    call.clipper = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && clipper != surface->clipper)
    {
        if (clipper)
            IDirectDrawClipper_AddRef(&clipper->IDirectDrawClipper_iface);
        if (surface->clipper)
            IDirectDrawClipper_Release(&surface->clipper->IDirectDrawClipper_iface);
        surface->clipper = clipper;
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface_SetClipper(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface_SetClipper *c = (struct qemu_ddraw_surface_SetClipper *)call;
    struct qemu_surface *surface;
    struct qemu_clipper *clipper;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    clipper = QEMU_G2H(c->clipper);

    c->super.iret = IDirectDrawSurface_SetClipper(surface->host_surface1, clipper ? clipper->host : NULL);
}

#endif

struct qemu_ddraw_surface7_SetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t DDSD;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetSurfaceDesc(IDirectDrawSurface7 *iface, DDSURFACEDESC2 *DDSD, DWORD Flags)
{
    struct qemu_ddraw_surface7_SetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.DDSD = (ULONG_PTR)DDSD;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetSurfaceDesc *c = (struct qemu_ddraw_surface7_SetSurfaceDesc *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_SetSurfaceDesc(surface->host_surface7, QEMU_G2H(c->DDSD), c->Flags);
}

#endif

struct qemu_ddraw_surface4_SetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_SetSurfaceDesc(IDirectDrawSurface4 *iface, DDSURFACEDESC2 *surface_desc, DWORD flags)
{
    struct qemu_ddraw_surface4_SetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_SETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_SetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_SetSurfaceDesc *c = (struct qemu_ddraw_surface4_SetSurfaceDesc *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_SetSurfaceDesc(surface->host_surface4, QEMU_G2H(c->surface_desc), c->flags);
}

#endif

struct qemu_ddraw_surface3_SetSurfaceDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface_desc;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_SetSurfaceDesc(IDirectDrawSurface3 *iface, DDSURFACEDESC *surface_desc, DWORD flags)
{
    struct qemu_ddraw_surface3_SetSurfaceDesc call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_SETSURFACEDESC);
    call.iface = (ULONG_PTR)surface;
    call.surface_desc = (ULONG_PTR)surface_desc;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_SetSurfaceDesc(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_SetSurfaceDesc *c = (struct qemu_ddraw_surface3_SetSurfaceDesc *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_SetSurfaceDesc(surface->host_surface3, QEMU_G2H(c->surface_desc), c->flags);
}

#endif

struct qemu_ddraw_surface7_GetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_GetPalette(IDirectDrawSurface7 *iface, IDirectDrawPalette **palette)
{
    struct qemu_ddraw_surface7_GetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_GETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_GetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_GetPalette *c = (struct qemu_ddraw_surface7_GetPalette *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_GetPalette(surface->host_surface7, QEMU_G2H(c->palette));
}

#endif

struct qemu_ddraw_surface4_GetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_GetPalette(IDirectDrawSurface4 *iface, IDirectDrawPalette **palette)
{
    struct qemu_ddraw_surface4_GetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_GETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_GetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_GetPalette *c = (struct qemu_ddraw_surface4_GetPalette *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_GetPalette(surface->host_surface4, QEMU_G2H(c->palette));
}

#endif

struct qemu_ddraw_surface3_GetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_GetPalette(IDirectDrawSurface3 *iface, IDirectDrawPalette **palette)
{
    struct qemu_ddraw_surface3_GetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_GETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_GetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_GetPalette *c = (struct qemu_ddraw_surface3_GetPalette *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_GetPalette(surface->host_surface3, QEMU_G2H(c->palette));
}

#endif

struct qemu_ddraw_surface2_GetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_GetPalette(IDirectDrawSurface2 *iface, IDirectDrawPalette **palette)
{
    struct qemu_ddraw_surface2_GetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_GETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_GetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_GetPalette *c = (struct qemu_ddraw_surface2_GetPalette *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_GetPalette(surface->host_surface2, QEMU_G2H(c->palette));
}

#endif

struct qemu_ddraw_surface1_GetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_GetPalette(IDirectDrawSurface *iface, IDirectDrawPalette **palette)
{
    struct qemu_ddraw_surface1_GetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_GETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_GetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_GetPalette *c = (struct qemu_ddraw_surface1_GetPalette *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_GetPalette(surface->host_surface1, QEMU_G2H(c->palette));
}

#endif

struct qemu_ddraw_surface7_SetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetColorKey(IDirectDrawSurface7 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface7_SetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetColorKey *c = (struct qemu_ddraw_surface7_SetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface7_SetColorKey(surface->host_surface7, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface4_SetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_SetColorKey(IDirectDrawSurface4 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface4_SetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_SETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_SetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_SetColorKey *c = (struct qemu_ddraw_surface4_SetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface4_SetColorKey(surface->host_surface4, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface3_SetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_SetColorKey(IDirectDrawSurface3 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface3_SetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_SETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_SetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_SetColorKey *c = (struct qemu_ddraw_surface3_SetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface3_SetColorKey(surface->host_surface3, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface2_SetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_SetColorKey(IDirectDrawSurface2 *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface2_SetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_SETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_SetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_SetColorKey *c = (struct qemu_ddraw_surface2_SetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface2_SetColorKey(surface->host_surface2, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface1_SetColorKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t color_key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_SetColorKey(IDirectDrawSurface *iface, DWORD flags, DDCOLORKEY *color_key)
{
    struct qemu_ddraw_surface1_SetColorKey call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_SETCOLORKEY);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.color_key = (ULONG_PTR)color_key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_SetColorKey(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_SetColorKey *c = (struct qemu_ddraw_surface1_SetColorKey *)call;
    struct qemu_surface *surface;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawSurface_SetColorKey(surface->host_surface1, c->flags, QEMU_G2H(c->color_key));
}

#endif

struct qemu_ddraw_surface7_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface7_SetPalette(IDirectDrawSurface7 *iface, IDirectDrawPalette *palette)
{
    struct qemu_ddraw_surface7_SetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface7(iface);
    struct qemu_palette *pal_impl = unsafe_impl_from_IDirectDrawPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE7_SETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && pal_impl != surface->palette)
    {
        if (palette)
            IDirectDrawPalette_AddRef(palette);
        if (surface->palette)
            IDirectDrawPalette_Release(&surface->palette->IDirectDrawPalette_iface);
        surface->palette = pal_impl;
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface7_SetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface7_SetPalette *c = (struct qemu_ddraw_surface7_SetPalette *)call;
    struct qemu_surface *surface;
    struct qemu_palette *palette;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IDirectDrawSurface7_SetPalette(surface->host_surface7, palette ? palette->host : NULL);
}

#endif

struct qemu_ddraw_surface4_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface4_SetPalette(IDirectDrawSurface4 *iface, IDirectDrawPalette *palette)
{
    struct qemu_ddraw_surface4_SetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface4(iface);
    struct qemu_palette *pal_impl = unsafe_impl_from_IDirectDrawPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE4_SETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && pal_impl != surface->palette)
    {
        if (palette)
            IDirectDrawPalette_AddRef(palette);
        if (surface->palette)
            IDirectDrawPalette_Release(&surface->palette->IDirectDrawPalette_iface);
        surface->palette = pal_impl;
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface4_SetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface4_SetPalette *c = (struct qemu_ddraw_surface4_SetPalette *)call;
    struct qemu_surface *surface;
    struct qemu_palette *palette;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IDirectDrawSurface4_SetPalette(surface->host_surface4, palette ? palette->host : NULL);
}

#endif

struct qemu_ddraw_surface3_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface3_SetPalette(IDirectDrawSurface3 *iface, IDirectDrawPalette *palette)
{
    struct qemu_ddraw_surface3_SetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface3(iface);
    struct qemu_palette *pal_impl = unsafe_impl_from_IDirectDrawPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE3_SETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && pal_impl != surface->palette)
    {
        if (palette)
            IDirectDrawPalette_AddRef(palette);
        if (surface->palette)
            IDirectDrawPalette_Release(&surface->palette->IDirectDrawPalette_iface);
        surface->palette = pal_impl;
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface3_SetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface3_SetPalette *c = (struct qemu_ddraw_surface3_SetPalette *)call;
    struct qemu_surface *surface;
    struct qemu_palette *palette;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IDirectDrawSurface3_SetPalette(surface->host_surface3, palette ? palette->host : NULL);
}

#endif

struct qemu_ddraw_surface2_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface2_SetPalette(IDirectDrawSurface2 *iface, IDirectDrawPalette *palette)
{
    struct qemu_ddraw_surface2_SetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface2(iface);
    struct qemu_palette *pal_impl = unsafe_impl_from_IDirectDrawPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE2_SETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && pal_impl != surface->palette)
    {
        if (palette)
            IDirectDrawPalette_AddRef(palette);
        if (surface->palette)
            IDirectDrawPalette_Release(&surface->palette->IDirectDrawPalette_iface);
        surface->palette = pal_impl;
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface2_SetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface2_SetPalette *c = (struct qemu_ddraw_surface2_SetPalette *)call;
    struct qemu_surface *surface;
    struct qemu_palette *palette;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IDirectDrawSurface2_SetPalette(surface->host_surface2, palette ? palette->host : NULL);
}

#endif

struct qemu_ddraw_surface1_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_surface1_SetPalette(IDirectDrawSurface *iface, IDirectDrawPalette *palette)
{
    struct qemu_ddraw_surface1_SetPalette call;
    struct qemu_surface *surface = impl_from_IDirectDrawSurface(iface);
    struct qemu_palette *pal_impl = unsafe_impl_from_IDirectDrawPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_SURFACE1_SETPALETTE);
    call.iface = (ULONG_PTR)surface;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && pal_impl != surface->palette)
    {
        if (palette)
            IDirectDrawPalette_AddRef(palette);
        if (surface->palette)
            IDirectDrawPalette_Release(&surface->palette->IDirectDrawPalette_iface);
        surface->palette = pal_impl;
    }

    return call.super.iret;
}

#else

void qemu_ddraw_surface1_SetPalette(struct qemu_syscall *call)
{
    struct qemu_ddraw_surface1_SetPalette *c = (struct qemu_ddraw_surface1_SetPalette *)call;
    struct qemu_surface *surface;
    struct qemu_palette *palette;

    WINE_TRACE("\n");
    surface = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IDirectDrawSurface_SetPalette(surface->host_surface1, palette ? palette->host : NULL);
}

#endif

struct qemu_ddraw_gamma_control_GetGammaRamp
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t gamma_ramp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_gamma_control_GetGammaRamp(IDirectDrawGammaControl *iface, DWORD flags, DDGAMMARAMP *gamma_ramp)
{
    struct qemu_ddraw_gamma_control_GetGammaRamp call;
    struct qemu_surface *surface = impl_from_IDirectDrawGammaControl(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_GAMMA_CONTROL_GETGAMMARAMP);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.gamma_ramp = (ULONG_PTR)gamma_ramp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_gamma_control_GetGammaRamp(struct qemu_syscall *call)
{
    struct qemu_ddraw_gamma_control_GetGammaRamp *c = (struct qemu_ddraw_gamma_control_GetGammaRamp *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawGammaControl_GetGammaRamp(surface->host_gamma, c->flags, QEMU_G2H(c->gamma_ramp));
}

#endif

struct qemu_ddraw_gamma_control_SetGammaRamp
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t gamma_ramp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_gamma_control_SetGammaRamp(IDirectDrawGammaControl *iface, DWORD flags, DDGAMMARAMP *gamma_ramp)
{
    struct qemu_ddraw_gamma_control_SetGammaRamp call;
    struct qemu_surface *surface = impl_from_IDirectDrawGammaControl(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_GAMMA_CONTROL_SETGAMMARAMP);
    call.iface = (ULONG_PTR)surface;
    call.flags = flags;
    call.gamma_ramp = (ULONG_PTR)gamma_ramp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_gamma_control_SetGammaRamp(struct qemu_syscall *call)
{
    struct qemu_ddraw_gamma_control_SetGammaRamp *c = (struct qemu_ddraw_gamma_control_SetGammaRamp *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawGammaControl_SetGammaRamp(surface->host_gamma, c->flags, QEMU_G2H(c->gamma_ramp));
}

#endif

struct qemu_d3d_texture2_PaletteChanged
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture2_PaletteChanged(IDirect3DTexture2 *iface, DWORD start, DWORD count)
{
    struct qemu_d3d_texture2_PaletteChanged call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE2_PALETTECHANGED);
    call.iface = (ULONG_PTR)surface;
    call.start = start;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture2_PaletteChanged(struct qemu_syscall *call)
{
    struct qemu_d3d_texture2_PaletteChanged *c = (struct qemu_d3d_texture2_PaletteChanged *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture2_PaletteChanged(surface->host_texture2, c->start, c->count);
}

#endif

struct qemu_d3d_texture1_PaletteChanged
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture1_PaletteChanged(IDirect3DTexture *iface, DWORD start, DWORD count)
{
    struct qemu_d3d_texture1_PaletteChanged call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE1_PALETTECHANGED);
    call.iface = (ULONG_PTR)surface;
    call.start = start;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture1_PaletteChanged(struct qemu_syscall *call)
{
    struct qemu_d3d_texture1_PaletteChanged *c = (struct qemu_d3d_texture1_PaletteChanged *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture_PaletteChanged(surface->host_texture1, c->start, c->count);
}

#endif

struct qemu_d3d_texture1_Unload
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture1_Unload(IDirect3DTexture *iface)
{
    struct qemu_d3d_texture1_Unload call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE1_UNLOAD);
    call.iface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture1_Unload(struct qemu_syscall *call)
{
    struct qemu_d3d_texture1_Unload *c = (struct qemu_d3d_texture1_Unload *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture_Unload(surface->host_texture1);
}

#endif

struct qemu_d3d_texture2_GetHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture2_GetHandle(IDirect3DTexture2 *iface, IDirect3DDevice2 *device, D3DTEXTUREHANDLE *handle)
{
    struct qemu_d3d_texture2_GetHandle call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE2_GETHANDLE);
    call.iface = (ULONG_PTR)surface;
    call.device = (ULONG_PTR)device;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture2_GetHandle(struct qemu_syscall *call)
{
    struct qemu_d3d_texture2_GetHandle *c = (struct qemu_d3d_texture2_GetHandle *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture2_GetHandle(surface->host_texture2, QEMU_G2H(c->device), QEMU_G2H(c->handle));
}

#endif

struct qemu_d3d_texture1_GetHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture1_GetHandle(IDirect3DTexture *iface, IDirect3DDevice *device, D3DTEXTUREHANDLE *handle)
{
    struct qemu_d3d_texture1_GetHandle call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE1_GETHANDLE);
    call.iface = (ULONG_PTR)surface;
    call.device = (ULONG_PTR)device;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture1_GetHandle(struct qemu_syscall *call)
{
    struct qemu_d3d_texture1_GetHandle *c = (struct qemu_d3d_texture1_GetHandle *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture_GetHandle(surface->host_texture1, QEMU_G2H(c->device), QEMU_G2H(c->handle));
}

#endif

struct qemu_d3d_texture2_Load
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture2_Load(IDirect3DTexture2 *iface, IDirect3DTexture2 *src_texture)
{
    struct qemu_d3d_texture2_Load call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE2_LOAD);
    call.iface = (ULONG_PTR)surface;
    call.src_texture = (ULONG_PTR)src_texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture2_Load(struct qemu_syscall *call)
{
    struct qemu_d3d_texture2_Load *c = (struct qemu_d3d_texture2_Load *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture2_Load(surface->host_texture2, QEMU_G2H(c->src_texture));
}

#endif

struct qemu_d3d_texture1_Load
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_texture1_Load(IDirect3DTexture *iface, IDirect3DTexture *src_texture)
{
    struct qemu_d3d_texture1_Load call;
    struct qemu_surface *surface = impl_from_IDirect3DTexture(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_TEXTURE1_LOAD);
    call.iface = (ULONG_PTR)surface;
    call.src_texture = (ULONG_PTR)src_texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_texture1_Load(struct qemu_syscall *call)
{
    struct qemu_d3d_texture1_Load *c = (struct qemu_d3d_texture1_Load *)call;
    struct qemu_surface *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture_Load(surface->host_texture1, QEMU_G2H(c->src_texture));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirectDrawSurface7Vtbl ddraw_surface7_vtbl =
{
    /* IUnknown */
    ddraw_surface7_QueryInterface,
    ddraw_surface7_AddRef,
    ddraw_surface7_Release,
    /* IDirectDrawSurface */
    ddraw_surface7_AddAttachedSurface,
    ddraw_surface7_AddOverlayDirtyRect,
    ddraw_surface7_Blt,
    ddraw_surface7_BltBatch,
    ddraw_surface7_BltFast,
    ddraw_surface7_DeleteAttachedSurface,
    ddraw_surface7_EnumAttachedSurfaces,
    ddraw_surface7_EnumOverlayZOrders,
    ddraw_surface7_Flip,
    ddraw_surface7_GetAttachedSurface,
    ddraw_surface7_GetBltStatus,
    ddraw_surface7_GetCaps,
    ddraw_surface7_GetClipper,
    ddraw_surface7_GetColorKey,
    ddraw_surface7_GetDC,
    ddraw_surface7_GetFlipStatus,
    ddraw_surface7_GetOverlayPosition,
    ddraw_surface7_GetPalette,
    ddraw_surface7_GetPixelFormat,
    ddraw_surface7_GetSurfaceDesc,
    ddraw_surface7_Initialize,
    ddraw_surface7_IsLost,
    ddraw_surface7_Lock,
    ddraw_surface7_ReleaseDC,
    ddraw_surface7_Restore,
    ddraw_surface7_SetClipper,
    ddraw_surface7_SetColorKey,
    ddraw_surface7_SetOverlayPosition,
    ddraw_surface7_SetPalette,
    ddraw_surface7_Unlock,
    ddraw_surface7_UpdateOverlay,
    ddraw_surface7_UpdateOverlayDisplay,
    ddraw_surface7_UpdateOverlayZOrder,
    /* IDirectDrawSurface2 */
    ddraw_surface7_GetDDInterface,
    ddraw_surface7_PageLock,
    ddraw_surface7_PageUnlock,
    /* IDirectDrawSurface3 */
    ddraw_surface7_SetSurfaceDesc,
    /* IDirectDrawSurface4 */
    ddraw_surface7_SetPrivateData,
    ddraw_surface7_GetPrivateData,
    ddraw_surface7_FreePrivateData,
    ddraw_surface7_GetUniquenessValue,
    ddraw_surface7_ChangeUniquenessValue,
    /* IDirectDrawSurface7 */
    ddraw_surface7_SetPriority,
    ddraw_surface7_GetPriority,
    ddraw_surface7_SetLOD,
    ddraw_surface7_GetLOD,
};

static const struct IDirectDrawSurface4Vtbl ddraw_surface4_vtbl =
{
    /* IUnknown */
    ddraw_surface4_QueryInterface,
    ddraw_surface4_AddRef,
    ddraw_surface4_Release,
    /* IDirectDrawSurface */
    ddraw_surface4_AddAttachedSurface,
    ddraw_surface4_AddOverlayDirtyRect,
    ddraw_surface4_Blt,
    ddraw_surface4_BltBatch,
    ddraw_surface4_BltFast,
    ddraw_surface4_DeleteAttachedSurface,
    ddraw_surface4_EnumAttachedSurfaces,
    ddraw_surface4_EnumOverlayZOrders,
    ddraw_surface4_Flip,
    ddraw_surface4_GetAttachedSurface,
    ddraw_surface4_GetBltStatus,
    ddraw_surface4_GetCaps,
    ddraw_surface4_GetClipper,
    ddraw_surface4_GetColorKey,
    ddraw_surface4_GetDC,
    ddraw_surface4_GetFlipStatus,
    ddraw_surface4_GetOverlayPosition,
    ddraw_surface4_GetPalette,
    ddraw_surface4_GetPixelFormat,
    ddraw_surface4_GetSurfaceDesc,
    ddraw_surface4_Initialize,
    ddraw_surface4_IsLost,
    ddraw_surface4_Lock,
    ddraw_surface4_ReleaseDC,
    ddraw_surface4_Restore,
    ddraw_surface4_SetClipper,
    ddraw_surface4_SetColorKey,
    ddraw_surface4_SetOverlayPosition,
    ddraw_surface4_SetPalette,
    ddraw_surface4_Unlock,
    ddraw_surface4_UpdateOverlay,
    ddraw_surface4_UpdateOverlayDisplay,
    ddraw_surface4_UpdateOverlayZOrder,
    /* IDirectDrawSurface2 */
    ddraw_surface4_GetDDInterface,
    ddraw_surface4_PageLock,
    ddraw_surface4_PageUnlock,
    /* IDirectDrawSurface3 */
    ddraw_surface4_SetSurfaceDesc,
    /* IDirectDrawSurface4 */
    ddraw_surface4_SetPrivateData,
    ddraw_surface4_GetPrivateData,
    ddraw_surface4_FreePrivateData,
    ddraw_surface4_GetUniquenessValue,
    ddraw_surface4_ChangeUniquenessValue,
};

static const struct IDirectDrawSurface3Vtbl ddraw_surface3_vtbl =
{
    /* IUnknown */
    ddraw_surface3_QueryInterface,
    ddraw_surface3_AddRef,
    ddraw_surface3_Release,
    /* IDirectDrawSurface */
    ddraw_surface3_AddAttachedSurface,
    ddraw_surface3_AddOverlayDirtyRect,
    ddraw_surface3_Blt,
    ddraw_surface3_BltBatch,
    ddraw_surface3_BltFast,
    ddraw_surface3_DeleteAttachedSurface,
    ddraw_surface3_EnumAttachedSurfaces,
    ddraw_surface3_EnumOverlayZOrders,
    ddraw_surface3_Flip,
    ddraw_surface3_GetAttachedSurface,
    ddraw_surface3_GetBltStatus,
    ddraw_surface3_GetCaps,
    ddraw_surface3_GetClipper,
    ddraw_surface3_GetColorKey,
    ddraw_surface3_GetDC,
    ddraw_surface3_GetFlipStatus,
    ddraw_surface3_GetOverlayPosition,
    ddraw_surface3_GetPalette,
    ddraw_surface3_GetPixelFormat,
    ddraw_surface3_GetSurfaceDesc,
    ddraw_surface3_Initialize,
    ddraw_surface3_IsLost,
    ddraw_surface3_Lock,
    ddraw_surface3_ReleaseDC,
    ddraw_surface3_Restore,
    ddraw_surface3_SetClipper,
    ddraw_surface3_SetColorKey,
    ddraw_surface3_SetOverlayPosition,
    ddraw_surface3_SetPalette,
    ddraw_surface3_Unlock,
    ddraw_surface3_UpdateOverlay,
    ddraw_surface3_UpdateOverlayDisplay,
    ddraw_surface3_UpdateOverlayZOrder,
    /* IDirectDrawSurface2 */
    ddraw_surface3_GetDDInterface,
    ddraw_surface3_PageLock,
    ddraw_surface3_PageUnlock,
    /* IDirectDrawSurface3 */
    ddraw_surface3_SetSurfaceDesc,
};

static const struct IDirectDrawSurface2Vtbl ddraw_surface2_vtbl =
{
    /* IUnknown */
    ddraw_surface2_QueryInterface,
    ddraw_surface2_AddRef,
    ddraw_surface2_Release,
    /* IDirectDrawSurface */
    ddraw_surface2_AddAttachedSurface,
    ddraw_surface2_AddOverlayDirtyRect,
    ddraw_surface2_Blt,
    ddraw_surface2_BltBatch,
    ddraw_surface2_BltFast,
    ddraw_surface2_DeleteAttachedSurface,
    ddraw_surface2_EnumAttachedSurfaces,
    ddraw_surface2_EnumOverlayZOrders,
    ddraw_surface2_Flip,
    ddraw_surface2_GetAttachedSurface,
    ddraw_surface2_GetBltStatus,
    ddraw_surface2_GetCaps,
    ddraw_surface2_GetClipper,
    ddraw_surface2_GetColorKey,
    ddraw_surface2_GetDC,
    ddraw_surface2_GetFlipStatus,
    ddraw_surface2_GetOverlayPosition,
    ddraw_surface2_GetPalette,
    ddraw_surface2_GetPixelFormat,
    ddraw_surface2_GetSurfaceDesc,
    ddraw_surface2_Initialize,
    ddraw_surface2_IsLost,
    ddraw_surface2_Lock,
    ddraw_surface2_ReleaseDC,
    ddraw_surface2_Restore,
    ddraw_surface2_SetClipper,
    ddraw_surface2_SetColorKey,
    ddraw_surface2_SetOverlayPosition,
    ddraw_surface2_SetPalette,
    ddraw_surface2_Unlock,
    ddraw_surface2_UpdateOverlay,
    ddraw_surface2_UpdateOverlayDisplay,
    ddraw_surface2_UpdateOverlayZOrder,
    /* IDirectDrawSurface2 */
    ddraw_surface2_GetDDInterface,
    ddraw_surface2_PageLock,
    ddraw_surface2_PageUnlock,
};

static const struct IDirectDrawSurfaceVtbl ddraw_surface1_vtbl =
{
    /* IUnknown */
    ddraw_surface1_QueryInterface,
    ddraw_surface1_AddRef,
    ddraw_surface1_Release,
    /* IDirectDrawSurface */
    ddraw_surface1_AddAttachedSurface,
    ddraw_surface1_AddOverlayDirtyRect,
    ddraw_surface1_Blt,
    ddraw_surface1_BltBatch,
    ddraw_surface1_BltFast,
    ddraw_surface1_DeleteAttachedSurface,
    ddraw_surface1_EnumAttachedSurfaces,
    ddraw_surface1_EnumOverlayZOrders,
    ddraw_surface1_Flip,
    ddraw_surface1_GetAttachedSurface,
    ddraw_surface1_GetBltStatus,
    ddraw_surface1_GetCaps,
    ddraw_surface1_GetClipper,
    ddraw_surface1_GetColorKey,
    ddraw_surface1_GetDC,
    ddraw_surface1_GetFlipStatus,
    ddraw_surface1_GetOverlayPosition,
    ddraw_surface1_GetPalette,
    ddraw_surface1_GetPixelFormat,
    ddraw_surface1_GetSurfaceDesc,
    ddraw_surface1_Initialize,
    ddraw_surface1_IsLost,
    ddraw_surface1_Lock,
    ddraw_surface1_ReleaseDC,
    ddraw_surface1_Restore,
    ddraw_surface1_SetClipper,
    ddraw_surface1_SetColorKey,
    ddraw_surface1_SetOverlayPosition,
    ddraw_surface1_SetPalette,
    ddraw_surface1_Unlock,
    ddraw_surface1_UpdateOverlay,
    ddraw_surface1_UpdateOverlayDisplay,
    ddraw_surface1_UpdateOverlayZOrder,
};

static const struct IDirectDrawGammaControlVtbl ddraw_gamma_control_vtbl =
{
    ddraw_gamma_control_QueryInterface,
    ddraw_gamma_control_AddRef,
    ddraw_gamma_control_Release,
    ddraw_gamma_control_GetGammaRamp,
    ddraw_gamma_control_SetGammaRamp,
};

static const struct IDirect3DTexture2Vtbl d3d_texture2_vtbl =
{
    d3d_texture2_QueryInterface,
    d3d_texture2_AddRef,
    d3d_texture2_Release,
    d3d_texture2_GetHandle,
    d3d_texture2_PaletteChanged,
    d3d_texture2_Load,
};

static const struct IDirect3DTextureVtbl d3d_texture1_vtbl =
{
    d3d_texture1_QueryInterface,
    d3d_texture1_AddRef,
    d3d_texture1_Release,
    d3d_texture1_Initialize,
    d3d_texture1_GetHandle,
    d3d_texture1_PaletteChanged,
    d3d_texture1_Load,
    d3d_texture1_Unload,
};

void qemu_surface_guest_init(struct qemu_surface *surface, struct qemu_ddraw *ddraw, unsigned int version)
{
    surface->IDirectDrawSurface7_iface.lpVtbl = &ddraw_surface7_vtbl;
    surface->IDirectDrawSurface4_iface.lpVtbl = &ddraw_surface4_vtbl;
    surface->IDirectDrawSurface3_iface.lpVtbl = &ddraw_surface3_vtbl;
    surface->IDirectDrawSurface2_iface.lpVtbl = &ddraw_surface2_vtbl;
    surface->IDirectDrawSurface_iface.lpVtbl = &ddraw_surface1_vtbl;
    surface->IDirectDrawGammaControl_iface.lpVtbl = &ddraw_gamma_control_vtbl;
    surface->IDirect3DTexture2_iface.lpVtbl = &d3d_texture2_vtbl;
    surface->IDirect3DTexture_iface.lpVtbl = &d3d_texture1_vtbl;
    surface->iface_count = 1;
    surface->version = version;
    surface->ddraw = ddraw;

    if (version == 7)
    {
        surface->ref7 = 1;
        surface->texture_outer = (IUnknown *)&surface->IDirectDrawSurface7_iface;
    }
    else if (version == 4)
    {
        surface->ref4 = 1;
        surface->texture_outer = (IUnknown *)&surface->IDirectDrawSurface4_iface;
    }
    else
    {
        surface->ref1 = 1;
        surface->texture_outer = (IUnknown *)&surface->IDirectDrawSurface_iface;
    }
}

/* Some games (e.g. Tomb Raider 3) pass the wrong version of the
 * IDirectDrawSurface interface to ddraw methods. */
struct qemu_surface *unsafe_impl_from_IDirectDrawSurface7(IDirectDrawSurface7 *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &ddraw_surface7_vtbl)
    {
        HRESULT hr = IDirectDrawSurface7_QueryInterface(iface, &IID_IDirectDrawSurface7, (void **)&iface);
        if (FAILED(hr))
        {
            WINE_WARN("Object %p doesn't expose interface IDirectDrawSurface7.\n", iface);
            return NULL;
        }
        IDirectDrawSurface7_Release(iface);
    }
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface7_iface);
}

struct qemu_surface *unsafe_impl_from_IDirectDrawSurface4(IDirectDrawSurface4 *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &ddraw_surface4_vtbl)
    {
        HRESULT hr = IDirectDrawSurface4_QueryInterface(iface, &IID_IDirectDrawSurface4, (void **)&iface);
        if (FAILED(hr))
        {
            WINE_WARN("Object %p doesn't expose interface IDirectDrawSurface4.\n", iface);
            return NULL;
        }
        IDirectDrawSurface4_Release(iface);
    }
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface4_iface);
}

static struct qemu_surface *unsafe_impl_from_IDirectDrawSurface3(IDirectDrawSurface3 *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &ddraw_surface3_vtbl)
    {
        HRESULT hr = IDirectDrawSurface3_QueryInterface(iface, &IID_IDirectDrawSurface3, (void **)&iface);
        if (FAILED(hr))
        {
            WINE_WARN("Object %p doesn't expose interface IDirectDrawSurface3.\n", iface);
            return NULL;
        }
        IDirectDrawSurface3_Release(iface);
    }
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface3_iface);
}

static struct qemu_surface *unsafe_impl_from_IDirectDrawSurface2(IDirectDrawSurface2 *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &ddraw_surface2_vtbl)
    {
        HRESULT hr = IDirectDrawSurface2_QueryInterface(iface, &IID_IDirectDrawSurface2, (void **)&iface);
        if (FAILED(hr))
        {
            WINE_WARN("Object %p doesn't expose interface IDirectDrawSurface2.\n", iface);
            return NULL;
        }
        IDirectDrawSurface2_Release(iface);
    }
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface2_iface);
}

struct qemu_surface *unsafe_impl_from_IDirectDrawSurface(IDirectDrawSurface *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &ddraw_surface1_vtbl)
    {
        HRESULT hr = IDirectDrawSurface_QueryInterface(iface, &IID_IDirectDrawSurface, (void **)&iface);
        if (FAILED(hr))
        {
            WINE_WARN("Object %p doesn't expose interface IDirectDrawSurface.\n", iface);
            return NULL;
        }
        IDirectDrawSurface_Release(iface);
    }
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirectDrawSurface_iface);
}

struct qemu_surface *unsafe_impl_from_IDirect3DTexture2(IDirect3DTexture2 *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &d3d_texture2_vtbl)
        WINE_ERR("Invalid IDirect3DTexture2 vtable!\n");
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirect3DTexture2_iface);
}

struct qemu_surface *unsafe_impl_from_IDirect3DTexture(IDirect3DTexture *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &d3d_texture1_vtbl)
        WINE_ERR("Invalid IDirect3DTexture2 vtable!\n");
    return CONTAINING_RECORD(iface, struct qemu_surface, IDirect3DTexture_iface);
}

#else

static HRESULT WINAPI qemu_surface_priv_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI qemu_surface_priv_AddRef(IUnknown *iface)
{
    struct qemu_surface *surface = surface_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedIncrement(&surface->private_data_ref);

    WINE_TRACE("%p increasing refcount to %u.\n", surface, refcount);
    return refcount;
}

static ULONG WINAPI qemu_surface_priv_Release(IUnknown *iface)
{
    struct qemu_surface *surface = surface_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedDecrement(&surface->private_data_ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", surface, refcount);
    if (!refcount)
    {
        /* This means the private data has been released, which only happens
         * when the real interface has been destroyed. */
        qemu_ops->qemu_execute(QEMU_G2H(ddraw_surface_destroy_cb), QEMU_H2G(surface));
        HeapFree(GetProcessHeap(), 0, surface);
    }

    return refcount;
}

const struct IUnknownVtbl surface_priv_vtbl =
{
    /* IUnknown */
    qemu_surface_priv_QueryInterface,
    qemu_surface_priv_AddRef,
    qemu_surface_priv_Release,
};

const GUID surface_priv_uuid =
{
    0xa52c4f8a,
    0xb032,
    0x4d67,
    { 0x88,0x5c,0x64,0x79,0x76,0xb1,0x00,0x05 }
};

#endif
