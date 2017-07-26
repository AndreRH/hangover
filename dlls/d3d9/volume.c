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
    uint64_t out;
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
    call.iface = (uint64_t)volume;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    /* This call only returns IDirect3DVolume9 and no other interface. */
    if (SUCCEEDED(call.super.iret))
        *out = iface;

    return call.super.iret;
}

#else

void qemu_d3d9_volume_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_QueryInterface *c = (struct qemu_d3d9_volume_QueryInterface *)call;
    struct qemu_d3d9_subresource_impl *volume;
    GUID *iid;

    WINE_TRACE("\n");
    volume = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    c->super.iret = IDirect3DVolume9_QueryInterface(volume->host_volume, iid, QEMU_G2H(c->out));

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
    call.iface = (uint64_t)volume;

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
    call.iface = (uint64_t)volume;

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
    call.iface = (uint64_t)volume;
    call.device = (uint64_t)device;

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
    call.iface = (uint64_t)volume;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;
    call.flags = (uint64_t)flags;

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
    call.iface = (uint64_t)volume;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

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
    call.iface = (uint64_t)volume;
    call.guid = (uint64_t)guid;

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
    struct qemu_d3d9_texture_impl *texture = NULL;
    struct qemu_d3d9_device_impl *device = NULL;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VOLUME_GETCONTAINER);
    call.iface = (uint64_t)volume;
    call.riid = (uint64_t)riid;
    call.texture = (uint64_t)&texture;
    call.device = (uint64_t)&device;

    qemu_syscall(&call.super);

    if (texture)
        *container = &texture->IDirect3DBaseTexture9_iface;
    else if (device)
        *container = &device->IDirect3DDevice9Ex_iface;
    else
        *container = NULL;

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

        *(uint64_t *)QEMU_G2H(c->texture) = QEMU_H2G(texture);
    }
    else if (IsEqualGUID(iid, &IID_IDirect3DDevice9))
    {
        /* Do not release the container returned by GetContainer, we pass the reference on! */
        *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(volume->device);
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
    call.iface = (uint64_t)volume;
    call.desc = (uint64_t)desc;

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
    call.iface = (uint64_t)volume;
    call.locked_box = (uint64_t)locked_box;
    call.box = (uint64_t)box;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_LockBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_LockBox *c = (struct qemu_d3d9_volume_LockBox *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_LockBox(volume->host_volume, QEMU_G2H(c->locked_box), QEMU_G2H(c->box), c->flags);
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
    call.iface = (uint64_t)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_volume_UnlockBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_volume_UnlockBox *c = (struct qemu_d3d9_volume_UnlockBox *)call;
    struct qemu_d3d9_subresource_impl *volume;

    WINE_FIXME("Unverified!\n");
    volume = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolume9_UnlockBox(volume->host_volume);
}

#endif

#ifdef QEMU_DLL_GUEST

const struct IDirect3DVolume9Vtbl d3d9_volume_vtbl =
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
