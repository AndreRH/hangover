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


struct qemu_d3d9_volume_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_subresource_impl *impl_from_IDirect3DVolume9(IDirect3DVolume9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_subresource_impl, IDirect3DVolume9_iface);
}

static HRESULT WINAPI d3d9_volume_QueryInterface(IDirect3DVolume9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_QUERYINTERFACE);
    call.iface = (ULONG_PTR)volume;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    /* This call only returns IDirect3DVolume9 and no other interface. */
    if (SUCCEEDED(call.super.iret))
        *out = iface;
    else
        *out = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_volume_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_QueryInterface *c = (struct qemu_d3d9_volume_QueryInterface *)call;
    struct qemu_d3d9_subresource_impl *volume;
    GUID *iid;
    void *out;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    c->super.iret = IDirect3DVolume9_QueryInterface(volume->host_volume, iid, &out);

    /* Note that IDirect3DVolume9 does not inherit or implement IDirect3DResource9. */
    if (SUCCEEDED(c->super.iret) && !IsEqualGUID(iid, &IID_IDirect3DVolume9)
            && !IsEqualGUID(iid, &IID_IUnknown))
        WINE_FIXME("Unexpected GUID %s.\n", wine_dbgstr_guid(iid));

}

#endif

struct qemu_d3d9_volume_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_volume_AddRef(IDirect3DVolume9 *iface)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_ADDREF);
    call.iface = (ULONG_PTR)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_AddRef *c = (struct qemu_d3d9_volume_AddRef *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_AddRef(volume->host_volume);
}

#endif

struct qemu_d3d9_volume_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_volume_Release(IDirect3DVolume9 *iface)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_RELEASE);
    call.iface = (ULONG_PTR)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_Release *c = (struct qemu_d3d9_volume_Release *)call;
    struct qemu_d3d9_subresource_impl *volume;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);
    device = volume->device;

    /* In case that the app releases the last reference
     * it holds to a texture through IDirect3DVolume9. */
    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DVolume9_Release(volume->host_volume);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_volume_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_GetDevice(IDirect3DVolume9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_GETDEVICE);
    call.iface = (ULONG_PTR)volume;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_GetDevice *c = (struct qemu_d3d9_volume_GetDevice *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_GetDevice(volume->host_volume, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_volume_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_SetPrivateData(IDirect3DVolume9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_SetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)volume;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;
    call.data_size = (ULONG_PTR)data_size;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_SetPrivateData *c = (struct qemu_d3d9_volume_SetPrivateData *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_SetPrivateData(volume->host_volume, QEMU_G2H(c->guid), QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d9_volume_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_GetPrivateData(IDirect3DVolume9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_GetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)volume;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;
    call.data_size = (ULONG_PTR)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_GetPrivateData *c = (struct qemu_d3d9_volume_GetPrivateData *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_GetPrivateData(volume->host_volume, QEMU_G2H(c->guid), QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_d3d9_volume_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_FreePrivateData(IDirect3DVolume9 *iface, REFGUID guid)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_FreePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_FREEPRIVATEDATA);
    call.iface = (ULONG_PTR)volume;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_FreePrivateData *c = (struct qemu_d3d9_volume_FreePrivateData *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_FreePrivateData(volume->host_volume, QEMU_G2H(c->guid));
}

#endif

struct qemu_d3d9_volume_GetContainer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t texture;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_GetContainer(IDirect3DVolume9 *iface, REFIID riid, void **container)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_GetContainer call;
    struct qemu_d3d9_texture_impl *texture;
    struct qemu_d3d9_device_impl *device;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_GETCONTAINER);
    call.iface = (ULONG_PTR)volume;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    if (call.texture)
    {
        texture = (struct qemu_d3d9_texture_impl *)(ULONG_PTR)call.texture;
        *container = &texture->IDirect3DBaseTexture9_iface;
    }
    else if (call.device)
    {
        device = (struct qemu_d3d9_device_impl *)(ULONG_PTR)call.device;
        *container = &device->IDirect3DDevice9Ex_iface;
    }
    else
    {
        *container = NULL;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_volume_GetContainer(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_GetContainer *c = (struct qemu_d3d9_volume_GetContainer *)call;
    struct qemu_d3d9_subresource_impl *volume;
    void *container;
    GUID *iid;
    struct qemu_d3d9_texture_impl *texture;
    struct qemu_d3d9_swapchain_impl *swapchain;
    IDirect3DSurface9 *backbuffer;
    IUnknown *priv_data;
    DWORD size = sizeof(priv_data);

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);
    c->texture = 0;
    c->device = 0;

    c->super.iret = IDirect3DVolume9_GetContainer(volume->host_volume, iid, &container);
    if (FAILED(c->super.iret))
        return;

    if (IsEqualGUID(iid, &IID_IDirect3DVolumeTexture9) || IsEqualGUID(iid, &IID_IDirect3DBaseTexture9)
            || IsEqualGUID(iid, &IID_IDirect3DResource9) || IsEqualGUID(iid, &IID_IUnknown))
    {
        IDirect3DBaseTexture9_GetPrivateData((IDirect3DBaseTexture9 *)container,
                &qemu_d3d9_texture_guid, &priv_data, &size);
        texture = texture_impl_from_IUnknown(priv_data);
        WINE_TRACE("Retrieved texture wrapper %p from private data.\n", texture);
        priv_data->lpVtbl->Release(priv_data);

        c->texture = QEMU_H2G(texture);
    }
    else if (IsEqualGUID(iid, &IID_IDirect3DDevice9))
    {
        /* Do not release the container returned by GetContainer, we pass the reference on! */
        c->device = QEMU_H2G(volume->device);
    }
    else
    {
        WINE_FIXME("Unexpected GUID %s.\n", wine_dbgstr_guid(iid));
        c->super.iret = E_FAIL;
        ((IUnknown *)container)->lpVtbl->Release(container);

    }
}

#endif

struct qemu_d3d9_volume_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_GetDesc(IDirect3DVolume9 *iface, D3DVOLUME_DESC *desc)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_GetDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_GETDESC);
    call.iface = (ULONG_PTR)volume;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_GetDesc *c = (struct qemu_d3d9_volume_GetDesc *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_GetDesc(volume->host_volume, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d9_volume_LockBox
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t locked_box;
    uint64_t box;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_LockBox(IDirect3DVolume9 *iface, D3DLOCKED_BOX *locked_box, const D3DBOX *box, DWORD flags)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_LockBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_LOCKBOX);
    call.iface = (ULONG_PTR)volume;
    call.locked_box = (ULONG_PTR)locked_box;
    call.box = (ULONG_PTR)box;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_LockBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_LockBox *c = (struct qemu_d3d9_volume_LockBox *)call;
    struct qemu_d3d9_subresource_impl *volume;
    D3DLOCKED_BOX stack, *lb = &stack;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    lb = QEMU_G2H(c->locked_box);
#else
    if (!c->locked_box)
        lb = NULL;
#endif

    c->super.iret = IDirect3DVolume9_LockBox(volume->host_volume, lb, QEMU_G2H(c->box), c->flags);
#if GUEST_BIT != HOST_BIT
    if (c->locked_box)
        D3DLOCKED_BOX_h2g(QEMU_G2H(c->locked_box), lb);
#endif
}

#endif

struct qemu_d3d9_volume_UnlockBox
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_volume_UnlockBox(IDirect3DVolume9 *iface)
{
    struct qemu_d3d9_subresource_impl *volume = impl_from_IDirect3DVolume9(iface);
    struct qemu_d3d9_volume_UnlockBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_UNLOCKBOX);
    call.iface = (ULONG_PTR)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_UnlockBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_UnlockBox *c = (struct qemu_d3d9_volume_UnlockBox *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_UnlockBox(volume->host_volume);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DVolume9Vtbl d3d9_volume_vtbl =
{
    /* IUnknown */
    d3d9_volume_QueryInterface,
    d3d9_volume_AddRef,
    d3d9_volume_Release,
    /* IDirect3DVolume9 */
    d3d9_volume_GetDevice,
    d3d9_volume_SetPrivateData,
    d3d9_volume_GetPrivateData,
    d3d9_volume_FreePrivateData,
    d3d9_volume_GetContainer,
    d3d9_volume_GetDesc,
    d3d9_volume_LockBox,
    d3d9_volume_UnlockBox,
};

void qemu_d3d9_volume_init_guest(IDirect3DVolume9 *volume)
{
    struct qemu_d3d9_subresource_impl *impl = impl_from_IDirect3DVolume9(volume);
    impl->IDirect3DVolume9_iface.lpVtbl = &d3d9_volume_vtbl;
    wined3d_private_store_init(&impl->private_store);
}

#else

void qemu_d3d9_volume_init(struct qemu_d3d9_subresource_impl *volume, IDirect3DVolume9 *host_volume,
        struct qemu_d3d9_device_impl *device)
{
    WINE_TRACE("Init volume %p, host %p.\n", volume, host_volume);
    volume->host_volume = host_volume;
    volume->device = device;
    IDirect3DVolume9_SetPrivateData(host_volume, &qemu_d3d9_volume_guid, &volume, sizeof(volume), 0);
}

#endif
