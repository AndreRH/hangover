/*
 * Copyright 2017 André Hentschel
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_d3d9_device_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_device_impl *impl_from_IDirect3DDevice9Ex(IDirect3DDevice9Ex *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_device_impl, IDirect3DDevice9Ex_iface);
}

static HRESULT WINAPI d3d9_device_QueryInterface(IDirect3DDevice9Ex *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_QUERYINTERFACE);
    call.iface = (uint64_t)device;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    /* This call either returns IDirect3DDevice9 or IDirect3DDevice9Ex, but no other
     * interface. */
    if (SUCCEEDED(call.super.iret))
        *out = &device->IDirect3DDevice9Ex_iface;

    return call.super.iret;
}

#else

void qemu_d3d9_device_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_QueryInterface *c = (struct qemu_d3d9_device_QueryInterface *)call;
    struct qemu_d3d9_device_impl *device;
    GUID *iid;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    if (!IsEqualGUID(iid, &IID_IDirect3DDevice9) && !IsEqualGUID(iid, &IID_IDirect3DDevice9Ex))
        WINE_FIXME("Unexpected GUID %s.\n", wine_dbgstr_guid(iid));

    c->super.iret = IDirect3DDevice9Ex_QueryInterface(device->host, iid, QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_device_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_device_AddRef(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_ADDREF);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG d3d9_device_wrapper_addref(struct qemu_d3d9_device_impl *device)
{
    return IDirect3DDevice9Ex_AddRef(device->host);
}

void qemu_d3d9_device_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_AddRef *c = (struct qemu_d3d9_device_AddRef *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = d3d9_device_wrapper_addref(device);
}

#endif

struct qemu_d3d9_device_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_device_Release(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_RELEASE);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG d3d9_device_wrapper_release(struct qemu_d3d9_device_impl *device)
{
    struct qemu_d3d9_impl *d3d9 = device->d3d9;
    ULONG ref;

    /* The device might hold the last reference to our IDirect3D9 parent.
     * Make sure the last IDirect3D9 ref is released through our code,
     * otherwise the wrapper class will not be released correctly.
     *
     * Why not permanently hold a ref between device create and release?
     * Mostly because it changes the outside observable refcount. */
    d3d9_wrapper_addref(d3d9);
    ref = IDirect3DDevice9Ex_Release(device->host);
    d3d9_wrapper_release(d3d9);

    if (!ref)
    {
        unsigned int i;

        for (i = 0; i < device->fvf_decl_count; ++i)
            d3d9_vdecl_internal_release(device->fvf_decls[i]);
        HeapFree(GetProcessHeap(), 0, device->fvf_decls);

        HeapFree(GetProcessHeap(), 0, device);
    }

    return ref;
}

void qemu_d3d9_device_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_Release *c = (struct qemu_d3d9_device_Release *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_device_TestCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_TestCooperativeLevel(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_TestCooperativeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_TESTCOOPERATIVELEVEL);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_TestCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_TestCooperativeLevel *c = (struct qemu_d3d9_device_TestCooperativeLevel *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_TestCooperativeLevel(device->host);
}

#endif

struct qemu_d3d9_device_GetAvailableTextureMem
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT WINAPI d3d9_device_GetAvailableTextureMem(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetAvailableTextureMem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETAVAILABLETEXTUREMEM);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetAvailableTextureMem(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetAvailableTextureMem *c = (struct qemu_d3d9_device_GetAvailableTextureMem *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetAvailableTextureMem(device->host);
}

#endif

struct qemu_d3d9_device_EvictManagedResources
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_EvictManagedResources(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_EvictManagedResources call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_EVICTMANAGEDRESOURCES);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_EvictManagedResources(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_EvictManagedResources *c = (struct qemu_d3d9_device_EvictManagedResources *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_EvictManagedResources(device->host);
}

#endif

struct qemu_d3d9_device_GetDirect3D
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t d3d9;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetDirect3D(IDirect3DDevice9Ex *iface, IDirect3D9 **d3d9)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetDirect3D call;
    struct qemu_d3d9_impl *d3d;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETDIRECT3D);
    call.iface = (uint64_t)device;
    call.d3d9 = (uint64_t)&d3d;

    qemu_syscall(&call.super);

    *d3d9 = (IDirect3D9 *)&d3d->IDirect3D9Ex_iface;
    IDirect3D9_AddRef(*d3d9);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetDirect3D(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetDirect3D *c = (struct qemu_d3d9_device_GetDirect3D *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    *(uint64_t *)QEMU_G2H(c->d3d9) = QEMU_H2G(device->d3d9);

    c->super.iret = D3D_OK;
}

#endif

struct qemu_d3d9_device_GetDeviceCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetDeviceCaps(IDirect3DDevice9Ex *iface, D3DCAPS9 *caps)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetDeviceCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETDEVICECAPS);
    call.iface = (uint64_t)device;
    call.caps = (uint64_t)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetDeviceCaps(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetDeviceCaps *c = (struct qemu_d3d9_device_GetDeviceCaps *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetDeviceCaps(device->host, QEMU_G2H(c->caps));
}

#endif

struct qemu_d3d9_device_GetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetDisplayMode(IDirect3DDevice9Ex *iface, UINT swapchain, D3DDISPLAYMODE *mode)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETDISPLAYMODE);
    call.iface = (uint64_t)device;
    call.swapchain = swapchain;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetDisplayMode *c = (struct qemu_d3d9_device_GetDisplayMode *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetDisplayMode(device->host, c->swapchain, QEMU_G2H(c->mode));
}

#endif

struct qemu_d3d9_device_GetCreationParameters
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t parameters;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetCreationParameters(IDirect3DDevice9Ex *iface, D3DDEVICE_CREATION_PARAMETERS *parameters)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetCreationParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETCREATIONPARAMETERS);
    call.iface = (uint64_t)device;
    call.parameters = (uint64_t)parameters;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetCreationParameters(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetCreationParameters *c = (struct qemu_d3d9_device_GetCreationParameters *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetCreationParameters(device->host, QEMU_G2H(c->parameters));
}

#endif

struct qemu_d3d9_device_SetCursorProperties
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hotspot_x;
    uint64_t hotspot_y;
    uint64_t bitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetCursorProperties(IDirect3DDevice9Ex *iface, UINT hotspot_x, UINT hotspot_y, IDirect3DSurface9 *bitmap)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetCursorProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETCURSORPROPERTIES);
    call.iface = (uint64_t)device;
    call.hotspot_x = (uint64_t)hotspot_x;
    call.hotspot_y = (uint64_t)hotspot_y;
    call.bitmap = (uint64_t)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetCursorProperties(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetCursorProperties *c = (struct qemu_d3d9_device_SetCursorProperties *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetCursorProperties(device->host, c->hotspot_x, c->hotspot_y, QEMU_G2H(c->bitmap));
}

#endif

struct qemu_d3d9_device_SetCursorPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_device_SetCursorPosition(IDirect3DDevice9Ex *iface, int x, int y, DWORD flags)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetCursorPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETCURSORPOSITION);
    call.iface = (uint64_t)device;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_device_SetCursorPosition(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetCursorPosition *c = (struct qemu_d3d9_device_SetCursorPosition *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    IDirect3DDevice9Ex_SetCursorPosition(device->host, c->x, c->y, c->flags);
}

#endif

struct qemu_d3d9_device_ShowCursor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t show;
};

#ifdef QEMU_DLL_GUEST

static BOOL WINAPI d3d9_device_ShowCursor(IDirect3DDevice9Ex *iface, BOOL show)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_ShowCursor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SHOWCURSOR);
    call.iface = (uint64_t)device;
    call.show = (uint64_t)show;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_ShowCursor(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_ShowCursor *c = (struct qemu_d3d9_device_ShowCursor *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_ShowCursor(device->host, c->show);
}

#endif

struct qemu_d3d9_device_CreateAdditionalSwapChain
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t present_parameters;
    uint64_t swapchain;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateAdditionalSwapChain(IDirect3DDevice9Ex *iface, D3DPRESENT_PARAMETERS *present_parameters, IDirect3DSwapChain9 **swapchain)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateAdditionalSwapChain call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEADDITIONALSWAPCHAIN);
    call.iface = (uint64_t)device;
    call.present_parameters = (uint64_t)present_parameters;
    call.swapchain = (uint64_t)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateAdditionalSwapChain(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateAdditionalSwapChain *c = (struct qemu_d3d9_device_CreateAdditionalSwapChain *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateAdditionalSwapChain(device->host, QEMU_G2H(c->present_parameters), QEMU_G2H(c->swapchain));
}

#endif

struct qemu_d3d9_device_GetSwapChain
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain_idx;
    uint64_t swapchain;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetSwapChain(IDirect3DDevice9Ex *iface, UINT swapchain_idx, IDirect3DSwapChain9 **swapchain)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetSwapChain call;
    struct qemu_d3d9_swapchain_impl *swapchain_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETSWAPCHAIN);
    call.iface = (uint64_t)device;
    call.swapchain_idx = (uint64_t)swapchain_idx;
    call.swapchain = (uint64_t)&swapchain_impl;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
        *swapchain = (IDirect3DSwapChain9 *)&swapchain_impl->IDirect3DSwapChain9Ex_iface;
    else
        *swapchain = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetSwapChain(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetSwapChain *c = (struct qemu_d3d9_device_GetSwapChain *)call;
    struct qemu_d3d9_device_impl *device;
    IDirect3DSwapChain9 *swapchain;
    IDirect3DSurface9 *backbuffer;
    IUnknown *priv_data;
    DWORD size = sizeof(priv_data);
    struct qemu_d3d9_swapchain_impl *swapchain_impl;

    WINE_TRACE("TRACE!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetSwapChain(device->host, c->swapchain_idx, &swapchain);
    if (FAILED(c->super.iret))
        return;

    IDirect3DSwapChain9_GetBackBuffer(swapchain, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
    IDirect3DSurface9_GetPrivateData(backbuffer, &qemu_d3d9_swapchain_guid, &priv_data, &size);
    IDirect3DSurface9_Release(backbuffer);

    swapchain_impl = swapchain_impl_from_IUnknown(priv_data);
    WINE_TRACE("Retrieved swapchain wrapper %p from private data\n", swapchain_impl);

    priv_data->lpVtbl->Release(priv_data);

    *(uint64_t *)QEMU_G2H(c->swapchain) = QEMU_H2G(swapchain_impl);
}

#endif

struct qemu_d3d9_device_GetNumberOfSwapChains
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT WINAPI d3d9_device_GetNumberOfSwapChains(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetNumberOfSwapChains call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETNUMBEROFSWAPCHAINS);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetNumberOfSwapChains(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetNumberOfSwapChains *c = (struct qemu_d3d9_device_GetNumberOfSwapChains *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetNumberOfSwapChains(device->host);
}

#endif

struct qemu_d3d9_device_Reset
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t present_parameters;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_Reset(IDirect3DDevice9Ex *iface, D3DPRESENT_PARAMETERS *present_parameters)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_Reset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_RESET);
    call.iface = (uint64_t)device;
    call.present_parameters = (uint64_t)present_parameters;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
        d3d9_device_set_implicit_ifaces(iface);

    return call.super.iret;
}

#else

void qemu_d3d9_device_Reset(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_Reset *c = (struct qemu_d3d9_device_Reset *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_Reset(device->host, QEMU_G2H(c->present_parameters));

    if (SUCCEEDED(c->super.iret) && !d3d9_device_wrap_implicit_resources(device))
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
}

#endif

struct qemu_d3d9_device_Present
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_rect;
    uint64_t dst_window_override;
    uint64_t dirty_region;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_Present(IDirect3DDevice9Ex *iface, const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override, const RGNDATA *dirty_region)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_Present call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_PRESENT);
    call.iface = (uint64_t)device;
    call.src_rect = (uint64_t)src_rect;
    call.dst_rect = (uint64_t)dst_rect;
    call.dst_window_override = (uint64_t)dst_window_override;
    call.dirty_region = (uint64_t)dirty_region;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_Present(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_Present *c = (struct qemu_d3d9_device_Present *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_Present(device->host, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_rect), QEMU_G2H(c->dst_window_override), QEMU_G2H(c->dirty_region));
}

#endif

struct qemu_d3d9_device_GetBackBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain;
    uint64_t backbuffer_idx;
    uint64_t backbuffer_type;
    uint64_t backbuffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetBackBuffer(IDirect3DDevice9Ex *iface, UINT swapchain, UINT backbuffer_idx, D3DBACKBUFFER_TYPE backbuffer_type, IDirect3DSurface9 **backbuffer)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetBackBuffer call;
    struct qemu_d3d9_subresource_impl *surface_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETBACKBUFFER);
    call.iface = (uint64_t)device;
    call.swapchain = (uint64_t)swapchain;
    call.backbuffer_idx = (uint64_t)backbuffer_idx;
    call.backbuffer_type = (uint64_t)backbuffer_type;
    call.backbuffer = (uint64_t)&surface_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
        *backbuffer = &surface_impl->IDirect3DSurface9_iface;
    else
        *backbuffer = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetBackBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetBackBuffer *c = (struct qemu_d3d9_device_GetBackBuffer *)call;
    struct qemu_d3d9_device_impl *device;
    IDirect3DSurface9 *host;
    struct qemu_d3d9_subresource_impl *surface_impl;
    DWORD size = sizeof(surface_impl);

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetBackBuffer(device->host, c->swapchain, c->backbuffer_idx, c->backbuffer_type, &host);
    if (FAILED(c->super.iret))
        return;

    IDirect3DSurface9_GetPrivateData(host, &qemu_d3d9_surface_guid, &surface_impl, &size);
    WINE_TRACE("Got surface %p from private data from host surface %p.\n", surface_impl, host);
    *(uint64_t *)QEMU_G2H(c->backbuffer) = QEMU_H2G(surface_impl);
}

#endif

struct qemu_d3d9_device_GetRasterStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain;
    uint64_t raster_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetRasterStatus(IDirect3DDevice9Ex *iface, UINT swapchain, D3DRASTER_STATUS *raster_status)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetRasterStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETRASTERSTATUS);
    call.iface = (uint64_t)device;
    call.swapchain = (uint64_t)swapchain;
    call.raster_status = (uint64_t)raster_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetRasterStatus(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetRasterStatus *c = (struct qemu_d3d9_device_GetRasterStatus *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetRasterStatus(device->host, c->swapchain, QEMU_G2H(c->raster_status));
}

#endif

struct qemu_d3d9_device_SetDialogBoxMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetDialogBoxMode(IDirect3DDevice9Ex *iface, BOOL enable)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetDialogBoxMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETDIALOGBOXMODE);
    call.iface = (uint64_t)device;
    call.enable = (uint64_t)enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetDialogBoxMode(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetDialogBoxMode *c = (struct qemu_d3d9_device_SetDialogBoxMode *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetDialogBoxMode(device->host, c->enable);
}

#endif

struct qemu_d3d9_device_SetGammaRamp
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain;
    uint64_t flags;
    uint64_t ramp;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_device_SetGammaRamp(IDirect3DDevice9Ex *iface, UINT swapchain, DWORD flags, const D3DGAMMARAMP *ramp)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetGammaRamp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETGAMMARAMP);
    call.iface = (uint64_t)device;
    call.swapchain = (uint64_t)swapchain;
    call.flags = (uint64_t)flags;
    call.ramp = (uint64_t)ramp;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_device_SetGammaRamp(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetGammaRamp *c = (struct qemu_d3d9_device_SetGammaRamp *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    IDirect3DDevice9Ex_SetGammaRamp(device->host, c->swapchain, c->flags, QEMU_G2H(c->ramp));
}

#endif

struct qemu_d3d9_device_GetGammaRamp
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain;
    uint64_t ramp;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_device_GetGammaRamp(IDirect3DDevice9Ex *iface, UINT swapchain, D3DGAMMARAMP *ramp)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetGammaRamp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETGAMMARAMP);
    call.iface = (uint64_t)device;
    call.swapchain = (uint64_t)swapchain;
    call.ramp = (uint64_t)ramp;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_device_GetGammaRamp(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetGammaRamp *c = (struct qemu_d3d9_device_GetGammaRamp *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    IDirect3DDevice9Ex_GetGammaRamp(device->host, c->swapchain, QEMU_G2H(c->ramp));
}

#endif

struct qemu_d3d9_device_CreateTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t levels;
    uint64_t usage;
    uint64_t format;
    uint64_t pool;
    uint64_t texture;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateTexture(IDirect3DDevice9Ex *iface, UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DTexture9 **texture, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateTexture call;
    struct qemu_d3d9_texture_impl *impl;

    *texture = NULL;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATETEXTURE);
    call.iface = (uint64_t)device;
    call.width = width;
    call.height = height;
    call.levels = levels;
    call.usage = usage;
    call.format = format;
    call.pool = pool;
    call.texture = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DBaseTexture9_iface.lpVtbl = (IDirect3DBaseTexture9Vtbl *)&d3d9_texture_2d_vtbl;
        d3d9_texture_set_surfaces_ifaces(&impl->IDirect3DBaseTexture9_iface);
        *texture = (IDirect3DTexture9 *)&impl->IDirect3DBaseTexture9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateTexture(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateTexture *c = (struct qemu_d3d9_device_CreateTexture *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_texture_impl *texture;
    IDirect3DTexture9 *host_texture;
    DWORD sub_resource_count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateTexture(device->host, c->width, c->height, c->levels, c->usage,
            c->format, c->pool, &host_texture, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
        return;

    sub_resource_count = IDirect3DTexture9_GetLevelCount(host_texture);

    texture = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, offsetof(struct qemu_d3d9_texture_impl, subs[sub_resource_count]));
    if (!texture)
    {
        IDirect3DTexture9_Release(host_texture);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    d3d9_texture_init(texture, (IDirect3DBaseTexture9 *)host_texture, device);
    *(uint64_t *)QEMU_G2H(c->texture) = QEMU_H2G(texture);
}

#endif

struct qemu_d3d9_device_CreateVolumeTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t depth;
    uint64_t levels;
    uint64_t usage;
    uint64_t format;
    uint64_t pool;
    uint64_t texture;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateVolumeTexture(IDirect3DDevice9Ex *iface, UINT width, UINT height, UINT depth, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DVolumeTexture9 **texture, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateVolumeTexture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEVOLUMETEXTURE);
    call.iface = (uint64_t)device;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.depth = (uint64_t)depth;
    call.levels = (uint64_t)levels;
    call.usage = (uint64_t)usage;
    call.format = (uint64_t)format;
    call.pool = (uint64_t)pool;
    call.texture = (uint64_t)texture;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateVolumeTexture(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateVolumeTexture *c = (struct qemu_d3d9_device_CreateVolumeTexture *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateVolumeTexture(device->host, c->width, c->height, c->depth, c->levels, c->usage, c->format, c->pool, QEMU_G2H(c->texture), QEMU_G2H(c->shared_handle));
}

#endif

struct qemu_d3d9_device_CreateCubeTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t edge_length;
    uint64_t levels;
    uint64_t usage;
    uint64_t format;
    uint64_t pool;
    uint64_t texture;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateCubeTexture(IDirect3DDevice9Ex *iface, UINT edge_length, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DCubeTexture9 **texture, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_texture_impl *impl;
    struct qemu_d3d9_device_CreateCubeTexture call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATECUBETEXTURE);
    call.iface = (uint64_t)device;
    call.edge_length = edge_length;
    call.levels = levels;
    call.usage = usage;
    call.format = format;
    call.pool = pool;
    call.texture = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DBaseTexture9_iface.lpVtbl = (IDirect3DBaseTexture9Vtbl *)&d3d9_texture_cube_vtbl;
        d3d9_texture_set_surfaces_ifaces(&impl->IDirect3DBaseTexture9_iface);
        *texture = (IDirect3DCubeTexture9 *)&impl->IDirect3DBaseTexture9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateCubeTexture(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateCubeTexture *c = (struct qemu_d3d9_device_CreateCubeTexture *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_texture_impl *texture;
    IDirect3DCubeTexture9 *host_texture;
    DWORD sub_resource_count;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateCubeTexture(device->host, c->edge_length, c->levels, c->usage,
            c->format, c->pool, &host_texture, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
        return;

    sub_resource_count = IDirect3DCubeTexture9_GetLevelCount(host_texture);
    sub_resource_count *= 6;

    texture = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, offsetof(struct qemu_d3d9_texture_impl, subs[sub_resource_count]));
    if (!texture)
    {
        IDirect3DCubeTexture9_Release(host_texture);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    d3d9_texture_init(texture, (IDirect3DBaseTexture9 *)host_texture, device);
    *(uint64_t *)QEMU_G2H(c->texture) = QEMU_H2G(texture);
}

#endif

struct qemu_d3d9_device_CreateVertexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t size;
    uint64_t usage;
    uint64_t fvf;
    uint64_t pool;
    uint64_t buffer;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateVertexBuffer(IDirect3DDevice9Ex *iface, UINT size, DWORD usage, DWORD fvf, D3DPOOL pool, IDirect3DVertexBuffer9 **buffer, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateVertexBuffer call;
    struct qemu_d3d9_buffer_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEVERTEXBUFFER);
    call.iface = (uint64_t)device;
    call.size = size;
    call.usage = usage;
    call.fvf = fvf;
    call.pool = pool;
    call.buffer = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DVertexBuffer9_iface.lpVtbl = &d3d9_vertexbuffer_vtbl;
        *buffer = &impl->IDirect3DVertexBuffer9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateVertexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateVertexBuffer *c = (struct qemu_d3d9_device_CreateVertexBuffer *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_buffer_impl *buffer;
    IDirect3DVertexBuffer9 *host_buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    buffer = HeapAlloc(GetProcessHeap(), 0, sizeof(*buffer));
    if (!buffer)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateVertexBuffer(device->host, c->size, c->usage, c->fvf, c->pool, &host_buffer, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, buffer);
        return;
    }

    d3d9_buffer_init(buffer, (IDirect3DResource9 *)host_buffer, device);
    *(uint64_t *)QEMU_G2H(c->buffer) = QEMU_H2G(buffer);
}

#endif

struct qemu_d3d9_device_CreateIndexBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t size;
    uint64_t usage;
    uint64_t format;
    uint64_t pool;
    uint64_t buffer;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateIndexBuffer(IDirect3DDevice9Ex *iface, UINT size, DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DIndexBuffer9 **buffer, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateIndexBuffer call;
    struct qemu_d3d9_buffer_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEINDEXBUFFER);
    call.iface = (uint64_t)device;
    call.size = size;
    call.usage = usage;
    call.format = format;
    call.pool = pool;
    call.buffer = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DIndexBuffer9_iface.lpVtbl = &d3d9_indexbuffer_vtbl;
        *buffer = &impl->IDirect3DIndexBuffer9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateIndexBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateIndexBuffer *c = (struct qemu_d3d9_device_CreateIndexBuffer *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_buffer_impl *buffer;
    IDirect3DIndexBuffer9 *host_buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    buffer = HeapAlloc(GetProcessHeap(), 0, sizeof(*buffer));
    if (!buffer)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateIndexBuffer(device->host, c->size, c->usage, c->format,
            c->pool, &host_buffer, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, buffer);
        return;
    }

    d3d9_buffer_init(buffer, (IDirect3DResource9 *)host_buffer, device);
    *(uint64_t *)QEMU_G2H(c->buffer) = QEMU_H2G(buffer);
}

#endif

struct qemu_d3d9_device_CreateRenderTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t multisample_type;
    uint64_t multisample_quality;
    uint64_t lockable;
    uint64_t surface;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateRenderTarget(IDirect3DDevice9Ex *iface, UINT width, UINT height, D3DFORMAT format, D3DMULTISAMPLE_TYPE multisample_type, DWORD multisample_quality, BOOL lockable, IDirect3DSurface9 **surface, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *impl;
    struct qemu_d3d9_device_CreateRenderTarget call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATERENDERTARGET);
    call.iface = (uint64_t)device;
    call.width = width;
    call.height = height;
    call.format = format;
    call.multisample_type = multisample_type;
    call.multisample_quality = multisample_quality;
    call.lockable = lockable;
    call.surface = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DSurface9_iface.lpVtbl = &d3d9_surface_vtbl;
        *surface = &impl->IDirect3DSurface9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateRenderTarget(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateRenderTarget *c = (struct qemu_d3d9_device_CreateRenderTarget *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_surface_impl *surface;
    IDirect3DSurface9 *host_surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    surface = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*surface));
    if (!surface)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateRenderTarget(device->host, c->width, c->height, c->format,
            c->multisample_type, c->multisample_quality, c->lockable, &host_surface, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, surface);
        return;
    }

    d3d9_standalone_surface_init(surface, host_surface, device);
    *(uint64_t *)QEMU_G2H(c->surface) = QEMU_H2G(&surface->sub_resource);
}

#endif

struct qemu_d3d9_device_CreateDepthStencilSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t multisample_type;
    uint64_t multisample_quality;
    uint64_t discard;
    uint64_t surface;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateDepthStencilSurface(IDirect3DDevice9Ex *iface, UINT width, UINT height, D3DFORMAT format, D3DMULTISAMPLE_TYPE multisample_type, DWORD multisample_quality, BOOL discard, IDirect3DSurface9 **surface, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateDepthStencilSurface call;
    struct qemu_d3d9_subresource_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEDEPTHSTENCILSURFACE);
    call.iface = (uint64_t)device;
    call.width = width;
    call.height = height;
    call.format = format;
    call.multisample_type = multisample_type;
    call.multisample_quality = multisample_quality;
    call.discard = discard;
    call.surface = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DSurface9_iface.lpVtbl = &d3d9_surface_vtbl;
        *surface = &impl->IDirect3DSurface9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateDepthStencilSurface(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateDepthStencilSurface *c = (struct qemu_d3d9_device_CreateDepthStencilSurface *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_surface_impl *surface;
    IDirect3DSurface9 *host_surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    surface = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*surface));
    if (!surface)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateDepthStencilSurface(device->host, c->width, c->height, c->format,
            c->multisample_type, c->multisample_quality, c->discard, &host_surface, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, surface);
        return;
    }

    d3d9_standalone_surface_init(surface, host_surface, device);
    *(uint64_t *)QEMU_G2H(c->surface) = QEMU_H2G(&surface->sub_resource);
}

#endif

struct qemu_d3d9_device_UpdateSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_point;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_UpdateSurface(IDirect3DDevice9Ex *iface, IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const POINT *dst_point)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *src_impl = unsafe_impl_from_IDirect3DSurface9(src_surface);
    struct qemu_d3d9_subresource_impl *dst_impl = unsafe_impl_from_IDirect3DSurface9(dst_surface);
    struct qemu_d3d9_device_UpdateSurface call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_UPDATESURFACE);
    call.iface = (uint64_t)device;
    call.src_surface = (uint64_t)src_impl;
    call.src_rect = (uint64_t)src_rect;
    call.dst_surface = (uint64_t)dst_impl;
    call.dst_point = (uint64_t)dst_point;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_UpdateSurface(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_UpdateSurface *c = (struct qemu_d3d9_device_UpdateSurface *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_subresource_impl *src, *dst;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);
    dst = QEMU_G2H(c->dst_surface);

    c->super.iret = IDirect3DDevice9Ex_UpdateSurface(device->host, src ? src->host : NULL,
            QEMU_G2H(c->src_rect), dst ? dst->host : NULL, QEMU_G2H(c->dst_point));
}

#endif

struct qemu_d3d9_device_UpdateTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_texture;
    uint64_t dst_texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_UpdateTexture(IDirect3DDevice9Ex *iface, IDirect3DBaseTexture9 *src_texture, IDirect3DBaseTexture9 *dst_texture)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_UpdateTexture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_UPDATETEXTURE);
    call.iface = (uint64_t)device;
    call.src_texture = (uint64_t)src_texture;
    call.dst_texture = (uint64_t)dst_texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_UpdateTexture(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_UpdateTexture *c = (struct qemu_d3d9_device_UpdateTexture *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_UpdateTexture(device->host, QEMU_G2H(c->src_texture), QEMU_G2H(c->dst_texture));
}

#endif

struct qemu_d3d9_device_GetRenderTargetData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t render_target;
    uint64_t dst_surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetRenderTargetData(IDirect3DDevice9Ex *iface, IDirect3DSurface9 *render_target, IDirect3DSurface9 *dst_surface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *rt_impl = unsafe_impl_from_IDirect3DSurface9(render_target);
    struct qemu_d3d9_subresource_impl *surface_impl = unsafe_impl_from_IDirect3DSurface9(dst_surface);

    struct qemu_d3d9_device_GetRenderTargetData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETRENDERTARGETDATA);
    call.iface = (uint64_t)device;
    call.render_target = (uint64_t)rt_impl;
    call.dst_surface = (uint64_t)surface_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetRenderTargetData(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetRenderTargetData *c = (struct qemu_d3d9_device_GetRenderTargetData *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_subresource_impl *rt, *dst_surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    rt = QEMU_G2H(c->render_target);
    dst_surface = QEMU_G2H(c->dst_surface);

    c->super.iret = IDirect3DDevice9Ex_GetRenderTargetData(device->host, rt ? rt->host : NULL,
            dst_surface ? dst_surface->host : NULL);
}

#endif

struct qemu_d3d9_device_GetFrontBufferData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain;
    uint64_t dst_surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetFrontBufferData(IDirect3DDevice9Ex *iface, UINT swapchain, IDirect3DSurface9 *dst_surface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetFrontBufferData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETFRONTBUFFERDATA);
    call.iface = (uint64_t)device;
    call.swapchain = (uint64_t)swapchain;
    call.dst_surface = (uint64_t)dst_surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetFrontBufferData(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetFrontBufferData *c = (struct qemu_d3d9_device_GetFrontBufferData *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetFrontBufferData(device->host, c->swapchain, QEMU_G2H(c->dst_surface));
}

#endif

struct qemu_d3d9_device_StretchRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_surface;
    uint64_t src_rect;
    uint64_t dst_surface;
    uint64_t dst_rect;
    uint64_t filter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_StretchRect(IDirect3DDevice9Ex *iface, IDirect3DSurface9 *src_surface, const RECT *src_rect, IDirect3DSurface9 *dst_surface, const RECT *dst_rect, D3DTEXTUREFILTERTYPE filter)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *src_impl = unsafe_impl_from_IDirect3DSurface9(src_surface);
    struct qemu_d3d9_subresource_impl *dst_impl = unsafe_impl_from_IDirect3DSurface9(dst_surface);
    struct qemu_d3d9_device_StretchRect call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_STRETCHRECT);
    call.iface = (uint64_t)device;
    call.src_surface = (uint64_t)src_impl;
    call.src_rect = (uint64_t)src_rect;
    call.dst_surface = (uint64_t)dst_impl;
    call.dst_rect = (uint64_t)dst_rect;
    call.filter = filter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_StretchRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_StretchRect *c = (struct qemu_d3d9_device_StretchRect *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_subresource_impl *src, *dst;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    src = QEMU_G2H(c->src_surface);
    dst = QEMU_G2H(c->dst_surface);

    c->super.iret = IDirect3DDevice9Ex_StretchRect(device->host, src ? src->host : NULL,
            QEMU_G2H(c->src_rect), dst ? dst->host : NULL, QEMU_G2H(c->dst_rect), c->filter);
}

#endif

struct qemu_d3d9_device_ColorFill
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
    uint64_t rect;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_ColorFill(IDirect3DDevice9Ex *iface, IDirect3DSurface9 *surface, const RECT *rect, D3DCOLOR color)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *surface_impl = unsafe_impl_from_IDirect3DSurface9(surface);
    struct qemu_d3d9_device_ColorFill call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_COLORFILL);
    call.iface = (uint64_t)device;
    call.surface = (uint64_t)surface_impl;
    call.rect = (uint64_t)rect;
    call.color = color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_ColorFill(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_ColorFill *c = (struct qemu_d3d9_device_ColorFill *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    surface = QEMU_G2H(c->surface);

    c->super.iret = IDirect3DDevice9Ex_ColorFill(device->host, surface ? surface->host : NULL,
            QEMU_G2H(c->rect), c->color);
}

#endif

struct qemu_d3d9_device_CreateOffscreenPlainSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t pool;
    uint64_t surface;
    uint64_t shared_handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateOffscreenPlainSurface(IDirect3DDevice9Ex *iface, UINT width, UINT height, D3DFORMAT format, D3DPOOL pool, IDirect3DSurface9 **surface, HANDLE *shared_handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateOffscreenPlainSurface call;
    struct qemu_d3d9_subresource_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEOFFSCREENPLAINSURFACE);
    call.iface = (uint64_t)device;
    call.width = width;
    call.height = height;
    call.format = format;
    call.pool = pool;
    call.surface = (uint64_t)&impl;
    call.shared_handle = (uint64_t)shared_handle;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DSurface9_iface.lpVtbl = &d3d9_surface_vtbl;
        *surface = &impl->IDirect3DSurface9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateOffscreenPlainSurface(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateOffscreenPlainSurface *c = (struct qemu_d3d9_device_CreateOffscreenPlainSurface *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_surface_impl *surface;
    IDirect3DSurface9 *host_surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    surface = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*surface));
    if (!surface)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateOffscreenPlainSurface(device->host, c->width, c->height, c->format,
            c->pool, &host_surface, (HANDLE)c->shared_handle);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, surface);
        return;
    }

    d3d9_standalone_surface_init(surface, host_surface, device);
    *(uint64_t *)QEMU_G2H(c->surface) = QEMU_H2G(&surface->sub_resource);
}

#endif

struct qemu_d3d9_device_SetRenderTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t idx;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetRenderTarget(IDirect3DDevice9Ex *iface, DWORD idx, IDirect3DSurface9 *surface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *surface_impl = unsafe_impl_from_IDirect3DSurface9(surface);
    struct qemu_d3d9_device_SetRenderTarget call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETRENDERTARGET);
    call.iface = (uint64_t)device;
    call.idx = idx;
    call.surface = (uint64_t)surface_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetRenderTarget(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetRenderTarget *c = (struct qemu_d3d9_device_SetRenderTarget *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    surface = QEMU_G2H(c->surface);

    c->super.iret = IDirect3DDevice9Ex_SetRenderTarget(device->host, c->idx, surface ? surface->host : NULL);
}

#endif

struct qemu_d3d9_device_GetRenderTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t idx;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetRenderTarget(IDirect3DDevice9Ex *iface, DWORD idx, IDirect3DSurface9 **surface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *surface_impl;
    struct qemu_d3d9_device_GetRenderTarget call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETRENDERTARGET);
    call.iface = (uint64_t)device;
    call.idx = idx;
    call.surface = (uint64_t)&surface_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && surface_impl)
        *surface = &surface_impl->IDirect3DSurface9_iface;
    else
        *surface = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetRenderTarget(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetRenderTarget *c = (struct qemu_d3d9_device_GetRenderTarget *)call;
    struct qemu_d3d9_device_impl *device;
    IDirect3DSurface9 *host;
    struct qemu_d3d9_subresource_impl *surface_impl;
    DWORD size = sizeof(surface_impl);

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetRenderTarget(device->host, c->idx, &host);
    if (FAILED(c->super.iret))
        return;

    if (host)
    {
        IDirect3DSurface9_GetPrivateData(host, &qemu_d3d9_surface_guid, &surface_impl, &size);
        WINE_TRACE("Got surface %p from private data from host surface %p.\n", surface_impl, host);
        *(uint64_t *)QEMU_G2H(c->surface) = QEMU_H2G(surface_impl);
    }
    else
    {
        *(uint64_t *)QEMU_G2H(c->surface) = QEMU_H2G(NULL);
    }
}

#endif

struct qemu_d3d9_device_SetDepthStencilSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetDepthStencilSurface(IDirect3DDevice9Ex *iface, IDirect3DSurface9 *depth_stencil)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *surface_impl = unsafe_impl_from_IDirect3DSurface9(depth_stencil);
    struct qemu_d3d9_device_SetDepthStencilSurface call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETDEPTHSTENCILSURFACE);
    call.iface = (uint64_t)device;
    call.depth_stencil = (uint64_t)surface_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetDepthStencilSurface(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetDepthStencilSurface *c = (struct qemu_d3d9_device_SetDepthStencilSurface *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_subresource_impl *surface;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    surface = QEMU_G2H(c->depth_stencil);

    c->super.iret = IDirect3DDevice9Ex_SetDepthStencilSurface(device->host, surface ? surface->host : NULL);
}

#endif

struct qemu_d3d9_device_GetDepthStencilSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t depth_stencil;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetDepthStencilSurface(IDirect3DDevice9Ex *iface, IDirect3DSurface9 **depth_stencil)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_subresource_impl *surface_impl;
    struct qemu_d3d9_device_GetDepthStencilSurface call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETDEPTHSTENCILSURFACE);
    call.iface = (uint64_t)device;
    call.depth_stencil = (uint64_t)&surface_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && surface_impl)
        *depth_stencil = &surface_impl->IDirect3DSurface9_iface;
    else
        *depth_stencil = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetDepthStencilSurface(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetDepthStencilSurface *c = (struct qemu_d3d9_device_GetDepthStencilSurface *)call;
    struct qemu_d3d9_device_impl *device;
    IDirect3DSurface9 *host;
    struct qemu_d3d9_subresource_impl *surface_impl;
    DWORD size = sizeof(surface_impl);

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetDepthStencilSurface(device->host, &host);
    if (FAILED(c->super.iret))
        return;

    if (host)
    {
        IDirect3DSurface9_GetPrivateData(host, &qemu_d3d9_surface_guid, &surface_impl, &size);
        WINE_TRACE("Got surface %p from private data from host surface %p.\n", surface_impl, host);
        *(uint64_t *)QEMU_G2H(c->depth_stencil) = QEMU_H2G(surface_impl);
    }
    else
    {
        *(uint64_t *)QEMU_G2H(c->depth_stencil) = QEMU_H2G(NULL);
    }
}

#endif

struct qemu_d3d9_device_BeginScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_BeginScene(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_BeginScene call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_BEGINSCENE);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_BeginScene(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_BeginScene *c = (struct qemu_d3d9_device_BeginScene *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_BeginScene(device->host);
}

#endif

struct qemu_d3d9_device_EndScene
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_EndScene(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_EndScene call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_ENDSCENE);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_EndScene(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_EndScene *c = (struct qemu_d3d9_device_EndScene *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_EndScene(device->host);
}

#endif

struct qemu_d3d9_device_Clear
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
    uint64_t flags;
    uint64_t color;
    double z;
    uint64_t stencil;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_Clear(IDirect3DDevice9Ex *iface, DWORD rect_count, const D3DRECT *rects, DWORD flags, D3DCOLOR color, float z, DWORD stencil)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_Clear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CLEAR);
    call.iface = (uint64_t)device;
    call.rect_count = (uint64_t)rect_count;
    call.rects = (uint64_t)rects;
    call.flags = (uint64_t)flags;
    call.color = (uint64_t)color;
    call.z = z;
    call.stencil = (uint64_t)stencil;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_Clear(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_Clear *c = (struct qemu_d3d9_device_Clear *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_Clear(device->host, c->rect_count, QEMU_G2H(c->rects), c->flags, c->color, c->z, c->stencil);
}

#endif

struct qemu_d3d9_device_SetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetTransform(IDirect3DDevice9Ex *iface, D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETTRANSFORM);
    call.iface = (uint64_t)device;
    call.state = state;
    call.matrix = (uint64_t)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetTransform *c = (struct qemu_d3d9_device_SetTransform *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetTransform(device->host, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d9_device_GetTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetTransform(IDirect3DDevice9Ex *iface, D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETTRANSFORM);
    call.iface = (uint64_t)device;
    call.state = (uint64_t)state;
    call.matrix = (uint64_t)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetTransform(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetTransform *c = (struct qemu_d3d9_device_GetTransform *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetTransform(device->host, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d9_device_MultiplyTransform
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t matrix;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_MultiplyTransform(IDirect3DDevice9Ex *iface, D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_MultiplyTransform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_MULTIPLYTRANSFORM);
    call.iface = (uint64_t)device;
    call.state = (uint64_t)state;
    call.matrix = (uint64_t)matrix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_MultiplyTransform(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_MultiplyTransform *c = (struct qemu_d3d9_device_MultiplyTransform *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_MultiplyTransform(device->host, c->state, QEMU_G2H(c->matrix));
}

#endif

struct qemu_d3d9_device_SetViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetViewport(IDirect3DDevice9Ex *iface, const D3DVIEWPORT9 *viewport)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETVIEWPORT);
    call.iface = (uint64_t)device;
    call.viewport = (uint64_t)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetViewport(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetViewport *c = (struct qemu_d3d9_device_SetViewport *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetViewport(device->host, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d9_device_GetViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t viewport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetViewport(IDirect3DDevice9Ex *iface, D3DVIEWPORT9 *viewport)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETVIEWPORT);
    call.iface = (uint64_t)device;
    call.viewport = (uint64_t)viewport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetViewport(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetViewport *c = (struct qemu_d3d9_device_GetViewport *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetViewport(device->host, QEMU_G2H(c->viewport));
}

#endif

struct qemu_d3d9_device_SetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetMaterial(IDirect3DDevice9Ex *iface, const D3DMATERIAL9 *material)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetMaterial call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETMATERIAL);
    call.iface = (uint64_t)device;
    call.material = (uint64_t)material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetMaterial *c = (struct qemu_d3d9_device_SetMaterial *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetMaterial(device->host, QEMU_G2H(c->material));
}

#endif

struct qemu_d3d9_device_GetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetMaterial(IDirect3DDevice9Ex *iface, D3DMATERIAL9 *material)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetMaterial call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETMATERIAL);
    call.iface = (uint64_t)device;
    call.material = (uint64_t)material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetMaterial *c = (struct qemu_d3d9_device_GetMaterial *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetMaterial(device->host, QEMU_G2H(c->material));
}

#endif

struct qemu_d3d9_device_SetLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t light;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetLight(IDirect3DDevice9Ex *iface, DWORD index, const D3DLIGHT9 *light)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETLIGHT);
    call.iface = (uint64_t)device;
    call.index = index;
    call.light = (uint64_t)light;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetLight(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetLight *c = (struct qemu_d3d9_device_SetLight *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetLight(device->host, c->index, QEMU_G2H(c->light));
}

#endif

struct qemu_d3d9_device_GetLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t light;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetLight(IDirect3DDevice9Ex *iface, DWORD index, D3DLIGHT9 *light)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETLIGHT);
    call.iface = (uint64_t)device;
    call.index = (uint64_t)index;
    call.light = (uint64_t)light;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetLight(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetLight *c = (struct qemu_d3d9_device_GetLight *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetLight(device->host, c->index, QEMU_G2H(c->light));
}

#endif

struct qemu_d3d9_device_LightEnable
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_LightEnable(IDirect3DDevice9Ex *iface, DWORD index, BOOL enable)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_LightEnable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_LIGHTENABLE);
    call.iface = (uint64_t)device;
    call.index = index;
    call.enable = enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_LightEnable(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_LightEnable *c = (struct qemu_d3d9_device_LightEnable *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_LightEnable(device->host, c->index, c->enable);
}

#endif

struct qemu_d3d9_device_GetLightEnable
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetLightEnable(IDirect3DDevice9Ex *iface, DWORD index, BOOL *enable)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetLightEnable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETLIGHTENABLE);
    call.iface = (uint64_t)device;
    call.index = (uint64_t)index;
    call.enable = (uint64_t)enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetLightEnable(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetLightEnable *c = (struct qemu_d3d9_device_GetLightEnable *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetLightEnable(device->host, c->index, QEMU_G2H(c->enable));
}

#endif

struct qemu_d3d9_device_SetClipPlane
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t plane;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetClipPlane(IDirect3DDevice9Ex *iface, DWORD index, const float *plane)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetClipPlane call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETCLIPPLANE);
    call.iface = (uint64_t)device;
    call.index = (uint64_t)index;
    call.plane = (uint64_t)plane;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetClipPlane(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetClipPlane *c = (struct qemu_d3d9_device_SetClipPlane *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetClipPlane(device->host, c->index, QEMU_G2H(c->plane));
}

#endif

struct qemu_d3d9_device_GetClipPlane
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t plane;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetClipPlane(IDirect3DDevice9Ex *iface, DWORD index, float *plane)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetClipPlane call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETCLIPPLANE);
    call.iface = (uint64_t)device;
    call.index = (uint64_t)index;
    call.plane = (uint64_t)plane;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetClipPlane(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetClipPlane *c = (struct qemu_d3d9_device_GetClipPlane *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetClipPlane(device->host, c->index, QEMU_G2H(c->plane));
}

#endif

struct qemu_d3d9_device_SetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetRenderState(IDirect3DDevice9Ex *iface, D3DRENDERSTATETYPE state, DWORD value)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetRenderState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETRENDERSTATE);
    call.iface = (uint64_t)device;
    call.state = (uint64_t)state;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetRenderState *c = (struct qemu_d3d9_device_SetRenderState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetRenderState(device->host, c->state, c->value);
}

#endif

struct qemu_d3d9_device_GetRenderState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetRenderState(IDirect3DDevice9Ex *iface, D3DRENDERSTATETYPE state, DWORD *value)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetRenderState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETRENDERSTATE);
    call.iface = (uint64_t)device;
    call.state = state;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetRenderState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetRenderState *c = (struct qemu_d3d9_device_GetRenderState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetRenderState(device->host, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d9_device_CreateStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateStateBlock(IDirect3DDevice9Ex *iface, D3DSTATEBLOCKTYPE type, IDirect3DStateBlock9 **stateblock)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateStateBlock call;
    struct qemu_d3d9_stateblock_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATESTATEBLOCK);
    call.iface = (uint64_t)device;
    call.type = type;
    call.stateblock = (uint64_t)&impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DStateBlock9_iface.lpVtbl = &d3d9_stateblock_vtbl;
        *stateblock = &impl->IDirect3DStateBlock9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateStateBlock *c = (struct qemu_d3d9_device_CreateStateBlock *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_stateblock_impl *stateblock;
    IDirect3DStateBlock9 *host_stateblock;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    stateblock = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*stateblock));
    if (!stateblock)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateStateBlock(device->host, c->type, &host_stateblock);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, stateblock);
        return;
    }

    stateblock->host = host_stateblock;
    stateblock->device = device;
    switch (c->type)
    {
        case D3DSBT_VERTEXSTATE:
            stateblock->state.flags = QEMU_D3D_STATE_HAS_VS | QEMU_D3D_STATE_HAS_VDECL;
            stateblock->state.vs = device->dev_state.vs;
            stateblock->state.vdecl = device->dev_state.vdecl;
            break;

        case D3DSBT_PIXELSTATE:
            stateblock->state.flags = QEMU_D3D_STATE_HAS_PS;
            stateblock->state.ps = device->dev_state.ps;
            break;

        case D3DSBT_ALL:
            stateblock->state.flags = QEMU_D3D_STATE_HAS_VS | QEMU_D3D_STATE_HAS_PS | QEMU_D3D_STATE_HAS_VDECL;
            stateblock->state.vs = device->dev_state.vs;
            stateblock->state.ps = device->dev_state.ps;
            stateblock->state.vdecl = device->dev_state.vdecl;
            break;
    }

    if (stateblock->state.vdecl)
        d3d9_vdecl_internal_addref(stateblock->state.vdecl);
    if (stateblock->state.vs)
        d3d9_shader_internal_addref(stateblock->state.vs);
    if (stateblock->state.ps)
        d3d9_shader_internal_addref(stateblock->state.ps);

    *(uint64_t *)QEMU_G2H(c->stateblock) = QEMU_H2G(stateblock);
}

#endif

struct qemu_d3d9_device_BeginStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_BeginStateBlock(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_BeginStateBlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_BEGINSTATEBLOCK);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_BeginStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_BeginStateBlock *c = (struct qemu_d3d9_device_BeginStateBlock *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_stateblock_impl *stateblock;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    stateblock = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof (*stateblock));
    if (!stateblock)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_BeginStateBlock(device->host);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, stateblock);
        return;
    }

    device->record_stateblock = stateblock;
    device->state = &device->record_stateblock->state;
}

#endif

struct qemu_d3d9_device_EndStateBlock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stateblock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_EndStateBlock(IDirect3DDevice9Ex *iface, IDirect3DStateBlock9 **stateblock)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_EndStateBlock call;
    struct qemu_d3d9_stateblock_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_ENDSTATEBLOCK);
    call.iface = (uint64_t)device;
    call.stateblock = (uint64_t)&impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DStateBlock9_iface.lpVtbl = &d3d9_stateblock_vtbl;
        *stateblock = &impl->IDirect3DStateBlock9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_EndStateBlock(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_EndStateBlock *c = (struct qemu_d3d9_device_EndStateBlock *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_stateblock_impl *stateblock;
    IDirect3DStateBlock9 *host_stateblock;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    stateblock = device->record_stateblock;

    c->super.iret = IDirect3DDevice9Ex_EndStateBlock(device->host, &host_stateblock);

    device->record_stateblock = NULL;
    device->state = &device->dev_state;

    if (FAILED(c->super.iret))
    {
        qemu_d3d9_stateblock_destroy(stateblock);
        return;
    }

    stateblock->device = device;
    stateblock->host = host_stateblock;
    *(uint64_t *)QEMU_G2H(c->stateblock) = QEMU_H2G(stateblock);
}

#endif

struct qemu_d3d9_device_SetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetClipStatus(IDirect3DDevice9Ex *iface, const D3DCLIPSTATUS9 *clip_status)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetClipStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETCLIPSTATUS);
    call.iface = (uint64_t)device;
    call.clip_status = (uint64_t)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetClipStatus *c = (struct qemu_d3d9_device_SetClipStatus *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetClipStatus(device->host, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d9_device_GetClipStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clip_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetClipStatus(IDirect3DDevice9Ex *iface, D3DCLIPSTATUS9 *clip_status)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetClipStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETCLIPSTATUS);
    call.iface = (uint64_t)device;
    call.clip_status = (uint64_t)clip_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetClipStatus(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetClipStatus *c = (struct qemu_d3d9_device_GetClipStatus *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetClipStatus(device->host, QEMU_G2H(c->clip_status));
}

#endif

struct qemu_d3d9_device_GetTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetTexture(IDirect3DDevice9Ex *iface, DWORD stage, IDirect3DBaseTexture9 **texture)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetTexture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETTEXTURE);
    call.iface = (uint64_t)device;
    call.stage = (uint64_t)stage;
    call.texture = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetTexture(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetTexture *c = (struct qemu_d3d9_device_GetTexture *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetTexture(device->host, c->stage, QEMU_G2H(c->texture));
}

#endif

struct qemu_d3d9_device_SetTexture
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t texture;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetTexture(IDirect3DDevice9Ex *iface, DWORD stage, IDirect3DBaseTexture9 *texture)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_texture_impl *texture_impl = unsafe_impl_from_IDirect3DBaseTexture9(texture);
    struct qemu_d3d9_device_SetTexture call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETTEXTURE);
    call.iface = (uint64_t)device;
    call.stage = stage;
    call.texture = (uint64_t)texture_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetTexture(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetTexture *c = (struct qemu_d3d9_device_SetTexture *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    texture = QEMU_G2H(c->texture);

    c->super.iret = IDirect3DDevice9Ex_SetTexture(device->host, c->stage, texture ? texture->host : NULL);
}

#endif

struct qemu_d3d9_device_GetTextureStageState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetTextureStageState(IDirect3DDevice9Ex *iface, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD *value)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetTextureStageState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETTEXTURESTAGESTATE);
    call.iface = (uint64_t)device;
    call.stage = stage;
    call.state = state;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetTextureStageState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetTextureStageState *c = (struct qemu_d3d9_device_GetTextureStageState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetTextureStageState(device->host, c->stage, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d9_device_SetTextureStageState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stage;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetTextureStageState(IDirect3DDevice9Ex *iface, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD value)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetTextureStageState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETTEXTURESTAGESTATE);
    call.iface = (uint64_t)device;
    call.stage = stage;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetTextureStageState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetTextureStageState *c = (struct qemu_d3d9_device_SetTextureStageState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetTextureStageState(device->host, c->stage, c->state, c->value);
}

#endif

struct qemu_d3d9_device_GetSamplerState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sampler;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetSamplerState(IDirect3DDevice9Ex *iface, DWORD sampler, D3DSAMPLERSTATETYPE state, DWORD *value)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetSamplerState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETSAMPLERSTATE);
    call.iface = (uint64_t)device;
    call.sampler = (uint64_t)sampler;
    call.state = (uint64_t)state;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetSamplerState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetSamplerState *c = (struct qemu_d3d9_device_GetSamplerState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetSamplerState(device->host, c->sampler, c->state, QEMU_G2H(c->value));
}

#endif

struct qemu_d3d9_device_SetSamplerState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sampler;
    uint64_t state;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetSamplerState(IDirect3DDevice9Ex *iface, DWORD sampler, D3DSAMPLERSTATETYPE state, DWORD value)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetSamplerState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETSAMPLERSTATE);
    call.iface = (uint64_t)device;
    call.sampler = sampler;
    call.state = state;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetSamplerState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetSamplerState *c = (struct qemu_d3d9_device_SetSamplerState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetSamplerState(device->host, c->sampler, c->state, c->value);
}

#endif

struct qemu_d3d9_device_ValidateDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pass_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_ValidateDevice(IDirect3DDevice9Ex *iface, DWORD *pass_count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_ValidateDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_VALIDATEDEVICE);
    call.iface = (uint64_t)device;
    call.pass_count = (uint64_t)pass_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_ValidateDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_ValidateDevice *c = (struct qemu_d3d9_device_ValidateDevice *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_ValidateDevice(device->host, QEMU_G2H(c->pass_count));
}

#endif

struct qemu_d3d9_device_SetPaletteEntries
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette_idx;
    uint64_t entries;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetPaletteEntries(IDirect3DDevice9Ex *iface, UINT palette_idx, const PALETTEENTRY *entries)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetPaletteEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETPALETTEENTRIES);
    call.iface = (uint64_t)device;
    call.palette_idx = (uint64_t)palette_idx;
    call.entries = (uint64_t)entries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetPaletteEntries(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetPaletteEntries *c = (struct qemu_d3d9_device_SetPaletteEntries *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetPaletteEntries(device->host, c->palette_idx, QEMU_G2H(c->entries));
}

#endif

struct qemu_d3d9_device_GetPaletteEntries
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette_idx;
    uint64_t entries;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetPaletteEntries(IDirect3DDevice9Ex *iface, UINT palette_idx, PALETTEENTRY *entries)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetPaletteEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETPALETTEENTRIES);
    call.iface = (uint64_t)device;
    call.palette_idx = (uint64_t)palette_idx;
    call.entries = (uint64_t)entries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetPaletteEntries(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetPaletteEntries *c = (struct qemu_d3d9_device_GetPaletteEntries *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetPaletteEntries(device->host, c->palette_idx, QEMU_G2H(c->entries));
}

#endif

struct qemu_d3d9_device_SetCurrentTexturePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette_idx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetCurrentTexturePalette(IDirect3DDevice9Ex *iface, UINT palette_idx)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetCurrentTexturePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETCURRENTTEXTUREPALETTE);
    call.iface = (uint64_t)device;
    call.palette_idx = (uint64_t)palette_idx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetCurrentTexturePalette(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetCurrentTexturePalette *c = (struct qemu_d3d9_device_SetCurrentTexturePalette *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetCurrentTexturePalette(device->host, c->palette_idx);
}

#endif

struct qemu_d3d9_device_GetCurrentTexturePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette_idx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetCurrentTexturePalette(IDirect3DDevice9Ex *iface, UINT *palette_idx)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetCurrentTexturePalette call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETCURRENTTEXTUREPALETTE);
    call.iface = (uint64_t)device;
    call.palette_idx = (uint64_t)palette_idx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetCurrentTexturePalette(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetCurrentTexturePalette *c = (struct qemu_d3d9_device_GetCurrentTexturePalette *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetCurrentTexturePalette(device->host, QEMU_G2H(c->palette_idx));
}

#endif

struct qemu_d3d9_device_SetScissorRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetScissorRect(IDirect3DDevice9Ex *iface, const RECT *rect)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetScissorRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETSCISSORRECT);
    call.iface = (uint64_t)device;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetScissorRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetScissorRect *c = (struct qemu_d3d9_device_SetScissorRect *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetScissorRect(device->host, QEMU_G2H(c->rect));
}

#endif

struct qemu_d3d9_device_GetScissorRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetScissorRect(IDirect3DDevice9Ex *iface, RECT *rect)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetScissorRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETSCISSORRECT);
    call.iface = (uint64_t)device;
    call.rect = (uint64_t)rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetScissorRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetScissorRect *c = (struct qemu_d3d9_device_GetScissorRect *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetScissorRect(device->host, QEMU_G2H(c->rect));
}

#endif

struct qemu_d3d9_device_SetSoftwareVertexProcessing
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t software;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetSoftwareVertexProcessing(IDirect3DDevice9Ex *iface, BOOL software)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetSoftwareVertexProcessing call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETSOFTWAREVERTEXPROCESSING);
    call.iface = (uint64_t)device;
    call.software = (uint64_t)software;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetSoftwareVertexProcessing(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetSoftwareVertexProcessing *c = (struct qemu_d3d9_device_SetSoftwareVertexProcessing *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetSoftwareVertexProcessing(device->host, c->software);
}

#endif

struct qemu_d3d9_device_GetSoftwareVertexProcessing
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static BOOL WINAPI d3d9_device_GetSoftwareVertexProcessing(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetSoftwareVertexProcessing call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETSOFTWAREVERTEXPROCESSING);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetSoftwareVertexProcessing(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetSoftwareVertexProcessing *c = (struct qemu_d3d9_device_GetSoftwareVertexProcessing *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetSoftwareVertexProcessing(device->host);
}

#endif

struct qemu_d3d9_device_SetNPatchMode
{
    struct qemu_syscall super;
    uint64_t iface;
    double segment_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetNPatchMode(IDirect3DDevice9Ex *iface, float segment_count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetNPatchMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETNPATCHMODE);
    call.iface = (uint64_t)device;
    call.segment_count = segment_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetNPatchMode(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetNPatchMode *c = (struct qemu_d3d9_device_SetNPatchMode *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetNPatchMode(device->host, c->segment_count);
}

#endif

struct qemu_d3d9_device_GetNPatchMode
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static float WINAPI d3d9_device_GetNPatchMode(IDirect3DDevice9Ex *iface)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetNPatchMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETNPATCHMODE);
    call.iface = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_d3d9_device_GetNPatchMode(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetNPatchMode *c = (struct qemu_d3d9_device_GetNPatchMode *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.dret = IDirect3DDevice9Ex_GetNPatchMode(device->host);
}

#endif

struct qemu_d3d9_device_DrawPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t start_vertex;
    uint64_t primitive_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DrawPrimitive(IDirect3DDevice9Ex *iface, D3DPRIMITIVETYPE primitive_type, UINT start_vertex, UINT primitive_count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DrawPrimitive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DRAWPRIMITIVE);
    call.iface = (uint64_t)device;
    call.primitive_type = primitive_type;
    call.start_vertex = start_vertex;
    call.primitive_count = primitive_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DrawPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DrawPrimitive *c = (struct qemu_d3d9_device_DrawPrimitive *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DrawPrimitive(device->host, c->primitive_type, c->start_vertex, c->primitive_count);
}

#endif

struct qemu_d3d9_device_DrawIndexedPrimitive
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t base_vertex_idx;
    uint64_t min_vertex_idx;
    uint64_t vertex_count;
    uint64_t start_idx;
    uint64_t primitive_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DrawIndexedPrimitive(IDirect3DDevice9Ex *iface, D3DPRIMITIVETYPE primitive_type, INT base_vertex_idx, UINT min_vertex_idx, UINT vertex_count, UINT start_idx, UINT primitive_count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DrawIndexedPrimitive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DRAWINDEXEDPRIMITIVE);
    call.iface = (uint64_t)device;
    call.primitive_type = (uint64_t)primitive_type;
    call.base_vertex_idx = (uint64_t)base_vertex_idx;
    call.min_vertex_idx = (uint64_t)min_vertex_idx;
    call.vertex_count = (uint64_t)vertex_count;
    call.start_idx = (uint64_t)start_idx;
    call.primitive_count = (uint64_t)primitive_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DrawIndexedPrimitive(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DrawIndexedPrimitive *c = (struct qemu_d3d9_device_DrawIndexedPrimitive *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DrawIndexedPrimitive(device->host, c->primitive_type, c->base_vertex_idx, c->min_vertex_idx, c->vertex_count, c->start_idx, c->primitive_count);
}

#endif

struct qemu_d3d9_device_DrawPrimitiveUP
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t primitive_count;
    uint64_t data;
    uint64_t stride;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DrawPrimitiveUP(IDirect3DDevice9Ex *iface, D3DPRIMITIVETYPE primitive_type, UINT primitive_count, const void *data, UINT stride)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DrawPrimitiveUP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DRAWPRIMITIVEUP);
    call.iface = (uint64_t)device;
    call.primitive_type = primitive_type;
    call.primitive_count = primitive_count;
    call.data = (uint64_t)data;
    call.stride = stride;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DrawPrimitiveUP(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DrawPrimitiveUP *c = (struct qemu_d3d9_device_DrawPrimitiveUP *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DrawPrimitiveUP(device->host, c->primitive_type, c->primitive_count, QEMU_G2H(c->data), c->stride);
}

#endif

struct qemu_d3d9_device_DrawIndexedPrimitiveUP
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t primitive_type;
    uint64_t min_vertex_idx;
    uint64_t vertex_count;
    uint64_t primitive_count;
    uint64_t index_data;
    uint64_t index_format;
    uint64_t vertex_data;
    uint64_t vertex_stride;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DrawIndexedPrimitiveUP(IDirect3DDevice9Ex *iface, D3DPRIMITIVETYPE primitive_type, UINT min_vertex_idx, UINT vertex_count, UINT primitive_count, const void *index_data, D3DFORMAT index_format, const void *vertex_data, UINT vertex_stride)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DrawIndexedPrimitiveUP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DRAWINDEXEDPRIMITIVEUP);
    call.iface = (uint64_t)device;
    call.primitive_type = primitive_type;
    call.min_vertex_idx = min_vertex_idx;
    call.vertex_count = vertex_count;
    call.primitive_count = primitive_count;
    call.index_data = (uint64_t)index_data;
    call.index_format = index_format;
    call.vertex_data = (uint64_t)vertex_data;
    call.vertex_stride = vertex_stride;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DrawIndexedPrimitiveUP(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DrawIndexedPrimitiveUP *c = (struct qemu_d3d9_device_DrawIndexedPrimitiveUP *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DrawIndexedPrimitiveUP(device->host, c->primitive_type, c->min_vertex_idx, c->vertex_count, c->primitive_count, QEMU_G2H(c->index_data), c->index_format, QEMU_G2H(c->vertex_data), c->vertex_stride);
}

#endif

struct qemu_d3d9_device_ProcessVertices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_start_idx;
    uint64_t dst_idx;
    uint64_t vertex_count;
    uint64_t dst_buffer;
    uint64_t declaration;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_ProcessVertices(IDirect3DDevice9Ex *iface, UINT src_start_idx, UINT dst_idx, UINT vertex_count, IDirect3DVertexBuffer9 *dst_buffer, IDirect3DVertexDeclaration9 *declaration, DWORD flags)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_ProcessVertices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_PROCESSVERTICES);
    call.iface = (uint64_t)device;
    call.src_start_idx = (uint64_t)src_start_idx;
    call.dst_idx = (uint64_t)dst_idx;
    call.vertex_count = (uint64_t)vertex_count;
    call.dst_buffer = (uint64_t)dst_buffer;
    call.declaration = (uint64_t)declaration;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_ProcessVertices(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_ProcessVertices *c = (struct qemu_d3d9_device_ProcessVertices *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_ProcessVertices(device->host, c->src_start_idx, c->dst_idx, c->vertex_count, QEMU_G2H(c->dst_buffer), QEMU_G2H(c->declaration), c->flags);
}

#endif

struct qemu_d3d9_device_CreateVertexDeclaration
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t elements;
    uint64_t declaration;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateVertexDeclaration(IDirect3DDevice9Ex *iface, const D3DVERTEXELEMENT9 *elements, IDirect3DVertexDeclaration9 **declaration)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateVertexDeclaration call;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEVERTEXDECLARATION);
    call.iface = (uint64_t)device;
    call.elements = (uint64_t)elements;
    call.declaration = (uint64_t)&decl;

    *declaration = NULL;
    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        decl->IDirect3DVertexDeclaration9_iface.lpVtbl = &d3d9_vertex_declaration_vtbl;
        *declaration = &decl->IDirect3DVertexDeclaration9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateVertexDeclaration(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateVertexDeclaration *c = (struct qemu_d3d9_device_CreateVertexDeclaration *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_vertex_declaration_impl *decl;
    IDirect3DVertexDeclaration9 *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    decl = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*decl));
    if (!decl)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateVertexDeclaration(device->host, QEMU_G2H(c->elements), &host);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, decl);
        return;
    }

    decl->host = host;
    decl->device = device;
    decl->internal_ref = 1;
    *(uint64_t *)QEMU_G2H(c->declaration) = QEMU_H2G(decl);
}

#endif

struct qemu_d3d9_device_SetVertexDeclaration
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t declaration;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetVertexDeclaration(IDirect3DDevice9Ex *iface, IDirect3DVertexDeclaration9 *declaration)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_vertex_declaration_impl *decl_impl = unsafe_impl_from_IDirect3DVertexDeclaration9(declaration);
    struct qemu_d3d9_device_SetVertexDeclaration call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETVERTEXDECLARATION);
    call.iface = (uint64_t)device;
    call.declaration = (uint64_t)decl_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static HRESULT qemu_d3d9_device_SetVertexDeclaration_helper(struct qemu_d3d9_device_impl *device,
        struct qemu_d3d9_vertex_declaration_impl *decl)
{
    HRESULT hr;
    struct qemu_d3d9_vertex_declaration_impl *old = device->state->vdecl;;

    hr = IDirect3DDevice9Ex_SetVertexDeclaration(device->host, decl ? decl->host : NULL);

    if (SUCCEEDED(hr) && decl != old)
    {
        device->state->vdecl = decl;
        device->state->flags |= QEMU_D3D_STATE_HAS_VDECL;

        if (decl)
            d3d9_vdecl_internal_addref(decl);
        if (old)
            d3d9_vdecl_internal_release(old);
    }

    return hr;
}

void qemu_d3d9_device_SetVertexDeclaration(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetVertexDeclaration *c = (struct qemu_d3d9_device_SetVertexDeclaration *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_vertex_declaration_impl *decl;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    decl = QEMU_G2H(c->declaration);

    c->super.iret = qemu_d3d9_device_SetVertexDeclaration_helper(device, decl);
}

#endif

struct qemu_d3d9_device_GetVertexDeclaration
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t declaration;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetVertexDeclaration(IDirect3DDevice9Ex *iface, IDirect3DVertexDeclaration9 **declaration)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetVertexDeclaration call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETVERTEXDECLARATION);
    call.iface = (uint64_t)device;
    call.declaration = (uint64_t)declaration;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetVertexDeclaration(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetVertexDeclaration *c = (struct qemu_d3d9_device_GetVertexDeclaration *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetVertexDeclaration(device->host, QEMU_G2H(c->declaration));
}

#endif

struct qemu_d3d9_device_SetFVF
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fvf;
    uint64_t init_decl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetFVF(IDirect3DDevice9Ex *iface, DWORD fvf)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_vertex_declaration_impl *init_decl = NULL;
    struct qemu_d3d9_device_SetFVF call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETFVF);
    call.iface = (uint64_t)device;
    call.fvf = (uint64_t)fvf;
    call.init_decl = (uint64_t)&init_decl;

    qemu_syscall(&call.super);

    if (init_decl)
        init_decl->IDirect3DVertexDeclaration9_iface.lpVtbl = &d3d9_vertex_declaration_vtbl;

    return call.super.iret;
}

#else

/* Copypasted from Wine and adapted. The main difference is that we don't need to translate
 * FVFs to a declaration array. All we have to do is set the FVF, get the d3d9 declaration
 * and manage the wrapper around it. */
static struct qemu_d3d9_vertex_declaration_impl *device_get_fvf_declaration(
        struct qemu_d3d9_device_impl *device, DWORD fvf, BOOL *init)
{
    struct qemu_d3d9_vertex_declaration_impl *ret;
    struct qemu_d3d9_vertex_declaration_impl **fvf_decls = device->fvf_decls;
    struct IDirect3DVertexDeclaration9 *host_decl;
    int p, low, high; /* deliberately signed */
    HRESULT hr;

    WINE_TRACE("Searching for declaration for fvf %08x... ", fvf);

    low = 0;
    high = device->fvf_decl_count - 1;
    *init = FALSE;
    while (low <= high)
    {
        p = (low + high) >> 1;
        WINE_TRACE("%d ", p);

        if (fvf_decls[p]->fvf == fvf)
        {
            WINE_TRACE("found %p.\n", fvf_decls[p]);
            return fvf_decls[p];
        }

        if (fvf_decls[p]->fvf < fvf)
            low = p + 1;
        else
            high = p - 1;
    }
    WINE_TRACE("not found. Creating and inserting at position %d.\n", low);

    if (FAILED(IDirect3DDevice9_SetFVF(device->host, fvf)))
        return NULL;
    if (FAILED(IDirect3DDevice9_GetVertexDeclaration(device->host, &host_decl)))
        return NULL;

    /* This kind of implicit declaration is perfectly healthy at ref = 0. It has
     * the lifetime of the device. If it has a ref != 0 it will hold a reference
     * on the device, so we can't keep a reference to it. */
    IDirect3DVertexDeclaration9_Release(host_decl);

    if (device->fvf_decl_size == device->fvf_decl_count)
    {
        UINT grow = max(device->fvf_decl_size / 2, 8);

        if (!fvf_decls)
            fvf_decls = HeapAlloc(GetProcessHeap(), 0, sizeof(*fvf_decls) * grow);
        else
            fvf_decls = HeapReAlloc(GetProcessHeap(), 0, fvf_decls, sizeof(*fvf_decls) * (device->fvf_decl_size + grow));
        if (!fvf_decls)
            return NULL;
        device->fvf_decls = fvf_decls;
        device->fvf_decl_size += grow;
    }

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        return NULL;


    ret->host = host_decl;
    ret->device = device;
    ret->internal_ref = 1;
    ret->fvf = fvf;

    memmove(fvf_decls + low + 1, fvf_decls + low, sizeof(*fvf_decls) * (device->fvf_decl_count - low));
    fvf_decls[low] = ret;
    ++device->fvf_decl_count;

    WINE_TRACE("Returning %p. %u declarations in array.\n", ret, device->fvf_decl_count);

    *init = TRUE;
    return ret;
}

void qemu_d3d9_device_SetFVF(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetFVF *c = (struct qemu_d3d9_device_SetFVF *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_vertex_declaration_impl *decl;
    BOOL init;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    decl = device_get_fvf_declaration(device, c->fvf, &init);

    if (!decl)
    {
        c->super.iret = D3DERR_INVALIDCALL;
        return;
    }

    if (init)
        *(uint64_t *)QEMU_G2H(c->init_decl) = QEMU_H2G(decl);

    c->super.iret = qemu_d3d9_device_SetVertexDeclaration_helper(device, decl);
}

#endif

struct qemu_d3d9_device_GetFVF
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fvf;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetFVF(IDirect3DDevice9Ex *iface, DWORD *fvf)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetFVF call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETFVF);
    call.iface = (uint64_t)device;
    call.fvf = (uint64_t)fvf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetFVF(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetFVF *c = (struct qemu_d3d9_device_GetFVF *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    if (!device->state->vdecl)
        *(DWORD *)QEMU_G2H(c->fvf) = 0;
    else
        *(DWORD *)QEMU_G2H(c->fvf) = device->state->vdecl->fvf;

    c->super.iret = D3D_OK;
}

#endif

struct qemu_d3d9_device_CreateVertexShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateVertexShader(IDirect3DDevice9Ex *iface, const DWORD *byte_code, IDirect3DVertexShader9 **shader)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateVertexShader call;
    struct qemu_d3d9_shader_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEVERTEXSHADER);
    call.iface = (uint64_t)device;
    call.byte_code = (uint64_t)byte_code;
    call.shader = (uint64_t)&impl;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DVertexShader9_iface.lpVtbl = &d3d9_vertexshader_vtbl;
        *shader = &impl->IDirect3DVertexShader9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateVertexShader(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateVertexShader *c = (struct qemu_d3d9_device_CreateVertexShader *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_shader_impl *shader;
    IDirect3DVertexShader9 *host_shader;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    shader = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*shader));
    if (!shader)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateVertexShader(device->host, QEMU_G2H(c->byte_code), &host_shader);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, shader);
        return;
    }

    shader->hostvs = host_shader;
    shader->device = device;
    shader->internal_ref = 1;
    *(uint64_t *)QEMU_G2H(c->shader) = QEMU_H2G(shader);
}

#endif

struct qemu_d3d9_device_SetVertexShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetVertexShader(IDirect3DDevice9Ex *iface, IDirect3DVertexShader9 *shader)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_shader_impl *shader_impl = unsafe_impl_from_IDirect3DVertexShader9(shader);
    struct qemu_d3d9_device_SetVertexShader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETVERTEXSHADER);
    call.iface = (uint64_t)device;
    call.shader = (uint64_t)shader_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetVertexShader(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetVertexShader *c = (struct qemu_d3d9_device_SetVertexShader *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_shader_impl *shader, *old;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    old = device->state->vs;
    shader = QEMU_G2H(c->shader);

    c->super.iret = IDirect3DDevice9Ex_SetVertexShader(device->host, shader ? shader->hostvs : NULL);

    if (SUCCEEDED(c->super.iret) && shader != old)
    {
        device->state->vs = shader;
        device->state->flags |= QEMU_D3D_STATE_HAS_VS;

        if (shader)
            d3d9_shader_internal_addref(shader);
        if (old)
            d3d9_shader_internal_release(old);
    }
}

#endif

struct qemu_d3d9_device_GetVertexShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetVertexShader(IDirect3DDevice9Ex *iface, IDirect3DVertexShader9 **shader)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetVertexShader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETVERTEXSHADER);
    call.iface = (uint64_t)device;
    call.shader = (uint64_t)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetVertexShader(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetVertexShader *c = (struct qemu_d3d9_device_GetVertexShader *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetVertexShader(device->host, QEMU_G2H(c->shader));
}

#endif

struct qemu_d3d9_device_SetVertexShaderConstantF
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetVertexShaderConstantF(IDirect3DDevice9Ex *iface, UINT reg_idx, const float *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetVertexShaderConstantF call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETVERTEXSHADERCONSTANTF);
    call.iface = (uint64_t)device;
    call.reg_idx = reg_idx;
    call.data = (uint64_t)data;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetVertexShaderConstantF(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetVertexShaderConstantF *c = (struct qemu_d3d9_device_SetVertexShaderConstantF *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetVertexShaderConstantF(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_GetVertexShaderConstantF
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetVertexShaderConstantF(IDirect3DDevice9Ex *iface, UINT reg_idx, float *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetVertexShaderConstantF call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETVERTEXSHADERCONSTANTF);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetVertexShaderConstantF(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetVertexShaderConstantF *c = (struct qemu_d3d9_device_GetVertexShaderConstantF *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetVertexShaderConstantF(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_SetVertexShaderConstantI
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetVertexShaderConstantI(IDirect3DDevice9Ex *iface, UINT reg_idx, const int *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetVertexShaderConstantI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETVERTEXSHADERCONSTANTI);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetVertexShaderConstantI(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetVertexShaderConstantI *c = (struct qemu_d3d9_device_SetVertexShaderConstantI *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetVertexShaderConstantI(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_GetVertexShaderConstantI
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetVertexShaderConstantI(IDirect3DDevice9Ex *iface, UINT reg_idx, int *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetVertexShaderConstantI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETVERTEXSHADERCONSTANTI);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetVertexShaderConstantI(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetVertexShaderConstantI *c = (struct qemu_d3d9_device_GetVertexShaderConstantI *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetVertexShaderConstantI(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_SetVertexShaderConstantB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetVertexShaderConstantB(IDirect3DDevice9Ex *iface, UINT reg_idx, const BOOL *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetVertexShaderConstantB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETVERTEXSHADERCONSTANTB);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetVertexShaderConstantB(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetVertexShaderConstantB *c = (struct qemu_d3d9_device_SetVertexShaderConstantB *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetVertexShaderConstantB(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_GetVertexShaderConstantB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetVertexShaderConstantB(IDirect3DDevice9Ex *iface, UINT reg_idx, BOOL *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetVertexShaderConstantB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETVERTEXSHADERCONSTANTB);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetVertexShaderConstantB(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetVertexShaderConstantB *c = (struct qemu_d3d9_device_GetVertexShaderConstantB *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetVertexShaderConstantB(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_SetStreamSource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stream_idx;
    uint64_t buffer;
    uint64_t offset;
    uint64_t stride;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetStreamSource(IDirect3DDevice9Ex *iface, UINT stream_idx, IDirect3DVertexBuffer9 *buffer, UINT offset, UINT stride)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_buffer_impl *buffer_impl = unsafe_impl_from_IDirect3DVertexBuffer9(buffer);
    struct qemu_d3d9_device_SetStreamSource call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETSTREAMSOURCE);
    call.iface = (uint64_t)device;
    call.stream_idx = stream_idx;
    call.buffer = (uint64_t)buffer_impl;
    call.offset = offset;
    call.stride = stride;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetStreamSource(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetStreamSource *c = (struct qemu_d3d9_device_SetStreamSource *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    c->super.iret = IDirect3DDevice9Ex_SetStreamSource(device->host, c->stream_idx, buffer ? buffer->hostvb : NULL, c->offset, c->stride);
}

#endif

struct qemu_d3d9_device_GetStreamSource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stream_idx;
    uint64_t buffer;
    uint64_t offset;
    uint64_t stride;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetStreamSource(IDirect3DDevice9Ex *iface, UINT stream_idx, IDirect3DVertexBuffer9 **buffer, UINT *offset, UINT *stride)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetStreamSource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETSTREAMSOURCE);
    call.iface = (uint64_t)device;
    call.stream_idx = (uint64_t)stream_idx;
    call.buffer = (uint64_t)buffer;
    call.offset = (uint64_t)offset;
    call.stride = (uint64_t)stride;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetStreamSource(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetStreamSource *c = (struct qemu_d3d9_device_GetStreamSource *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetStreamSource(device->host, c->stream_idx, QEMU_G2H(c->buffer), QEMU_G2H(c->offset), QEMU_G2H(c->stride));
}

#endif

struct qemu_d3d9_device_SetStreamSourceFreq
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stream_idx;
    uint64_t freq;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetStreamSourceFreq(IDirect3DDevice9Ex *iface, UINT stream_idx, UINT freq)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetStreamSourceFreq call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETSTREAMSOURCEFREQ);
    call.iface = (uint64_t)device;
    call.stream_idx = stream_idx;
    call.freq = freq;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetStreamSourceFreq(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetStreamSourceFreq *c = (struct qemu_d3d9_device_SetStreamSourceFreq *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetStreamSourceFreq(device->host, c->stream_idx, c->freq);
}

#endif

struct qemu_d3d9_device_GetStreamSourceFreq
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stream_idx;
    uint64_t freq;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetStreamSourceFreq(IDirect3DDevice9Ex *iface, UINT stream_idx, UINT *freq)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetStreamSourceFreq call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETSTREAMSOURCEFREQ);
    call.iface = (uint64_t)device;
    call.stream_idx = (uint64_t)stream_idx;
    call.freq = (uint64_t)freq;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetStreamSourceFreq(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetStreamSourceFreq *c = (struct qemu_d3d9_device_GetStreamSourceFreq *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetStreamSourceFreq(device->host, c->stream_idx, QEMU_G2H(c->freq));
}

#endif

struct qemu_d3d9_device_SetIndices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetIndices(IDirect3DDevice9Ex *iface, IDirect3DIndexBuffer9 *buffer)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_buffer_impl *buffer_impl = unsafe_impl_from_IDirect3DIndexBuffer9(buffer);
    struct qemu_d3d9_device_SetIndices call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETINDICES);
    call.iface = (uint64_t)device;
    call.buffer = (uint64_t)buffer_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetIndices(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetIndices *c = (struct qemu_d3d9_device_SetIndices *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_buffer_impl *buffer;

    WINE_TRACE("Unverified!\n");
    device = QEMU_G2H(c->iface);
    buffer = QEMU_G2H(c->buffer);

    c->super.iret = IDirect3DDevice9Ex_SetIndices(device->host, buffer ? buffer->hostib : NULL);
}

#endif

struct qemu_d3d9_device_GetIndices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetIndices(IDirect3DDevice9Ex *iface, IDirect3DIndexBuffer9 **buffer)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetIndices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETINDICES);
    call.iface = (uint64_t)device;
    call.buffer = (uint64_t)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetIndices(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetIndices *c = (struct qemu_d3d9_device_GetIndices *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetIndices(device->host, QEMU_G2H(c->buffer));
}

#endif

struct qemu_d3d9_device_CreatePixelShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t byte_code;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreatePixelShader(IDirect3DDevice9Ex *iface, const DWORD *byte_code, IDirect3DPixelShader9 **shader)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreatePixelShader call;
    struct qemu_d3d9_shader_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEPIXELSHADER);
    call.iface = (uint64_t)device;
    call.byte_code = (uint64_t)byte_code;
    call.shader = (uint64_t)&impl;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DPixelShader9_iface.lpVtbl = &d3d9_pixelshader_vtbl;
        *shader = &impl->IDirect3DPixelShader9_iface;
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreatePixelShader(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreatePixelShader *c = (struct qemu_d3d9_device_CreatePixelShader *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_shader_impl *shader;
    IDirect3DPixelShader9 *host_shader;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    shader = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*shader));
    if (!shader)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreatePixelShader(device->host, QEMU_G2H(c->byte_code), &host_shader);
    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, shader);
        return;
    }

    shader->hostps = host_shader;
    shader->device = device;
    shader->internal_ref = 1;
    *(uint64_t *)QEMU_G2H(c->shader) = QEMU_H2G(shader);
}

#endif

struct qemu_d3d9_device_SetPixelShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetPixelShader(IDirect3DDevice9Ex *iface, IDirect3DPixelShader9 *shader)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_shader_impl *shader_impl = unsafe_impl_from_IDirect3DPixelShader9(shader);
    struct qemu_d3d9_device_SetPixelShader call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETPIXELSHADER);
    call.iface = (uint64_t)device;
    call.shader = (uint64_t)shader_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetPixelShader(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetPixelShader *c = (struct qemu_d3d9_device_SetPixelShader *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_shader_impl *shader, *old;

    WINE_TRACE("Unverified!\n");
    device = QEMU_G2H(c->iface);
    old = device->state->ps;
    shader = QEMU_G2H(c->shader);

    c->super.iret = IDirect3DDevice9Ex_SetPixelShader(device->host, shader ? shader->hostps : NULL);

    if (SUCCEEDED(c->super.iret) && shader != old)
    {
        device->state->ps = shader;
        device->state->flags |= QEMU_D3D_STATE_HAS_PS;

        if (shader)
            d3d9_shader_internal_addref(shader);
        if (old)
            d3d9_shader_internal_release(old);
    }
}

#endif

struct qemu_d3d9_device_GetPixelShader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t shader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetPixelShader(IDirect3DDevice9Ex *iface, IDirect3DPixelShader9 **shader)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetPixelShader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETPIXELSHADER);
    call.iface = (uint64_t)device;
    call.shader = (uint64_t)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetPixelShader(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetPixelShader *c = (struct qemu_d3d9_device_GetPixelShader *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetPixelShader(device->host, QEMU_G2H(c->shader));
}

#endif

struct qemu_d3d9_device_SetPixelShaderConstantF
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetPixelShaderConstantF(IDirect3DDevice9Ex *iface, UINT reg_idx, const float *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetPixelShaderConstantF call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETPIXELSHADERCONSTANTF);
    call.iface = (uint64_t)device;
    call.reg_idx = reg_idx;
    call.data = (uint64_t)data;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetPixelShaderConstantF(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetPixelShaderConstantF *c = (struct qemu_d3d9_device_SetPixelShaderConstantF *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetPixelShaderConstantF(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_GetPixelShaderConstantF
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetPixelShaderConstantF(IDirect3DDevice9Ex *iface, UINT reg_idx, float *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetPixelShaderConstantF call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETPIXELSHADERCONSTANTF);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetPixelShaderConstantF(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetPixelShaderConstantF *c = (struct qemu_d3d9_device_GetPixelShaderConstantF *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetPixelShaderConstantF(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_SetPixelShaderConstantI
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetPixelShaderConstantI(IDirect3DDevice9Ex *iface, UINT reg_idx, const int *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetPixelShaderConstantI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETPIXELSHADERCONSTANTI);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetPixelShaderConstantI(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetPixelShaderConstantI *c = (struct qemu_d3d9_device_SetPixelShaderConstantI *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetPixelShaderConstantI(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_GetPixelShaderConstantI
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetPixelShaderConstantI(IDirect3DDevice9Ex *iface, UINT reg_idx, int *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetPixelShaderConstantI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETPIXELSHADERCONSTANTI);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetPixelShaderConstantI(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetPixelShaderConstantI *c = (struct qemu_d3d9_device_GetPixelShaderConstantI *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetPixelShaderConstantI(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_SetPixelShaderConstantB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetPixelShaderConstantB(IDirect3DDevice9Ex *iface, UINT reg_idx, const BOOL *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetPixelShaderConstantB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETPIXELSHADERCONSTANTB);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetPixelShaderConstantB(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetPixelShaderConstantB *c = (struct qemu_d3d9_device_SetPixelShaderConstantB *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetPixelShaderConstantB(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_GetPixelShaderConstantB
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reg_idx;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetPixelShaderConstantB(IDirect3DDevice9Ex *iface, UINT reg_idx, BOOL *data, UINT count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetPixelShaderConstantB call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETPIXELSHADERCONSTANTB);
    call.iface = (uint64_t)device;
    call.reg_idx = (uint64_t)reg_idx;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetPixelShaderConstantB(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetPixelShaderConstantB *c = (struct qemu_d3d9_device_GetPixelShaderConstantB *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetPixelShaderConstantB(device->host, c->reg_idx, QEMU_G2H(c->data), c->count);
}

#endif

struct qemu_d3d9_device_DrawRectPatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t handle;
    uint64_t segment_count;
    uint64_t patch_info;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DrawRectPatch(IDirect3DDevice9Ex *iface, UINT handle, const float *segment_count, const D3DRECTPATCH_INFO *patch_info)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DrawRectPatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DRAWRECTPATCH);
    call.iface = (uint64_t)device;
    call.handle = (uint64_t)handle;
    call.segment_count = (uint64_t)segment_count;
    call.patch_info = (uint64_t)patch_info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DrawRectPatch(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DrawRectPatch *c = (struct qemu_d3d9_device_DrawRectPatch *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DrawRectPatch(device->host, c->handle, QEMU_G2H(c->segment_count), QEMU_G2H(c->patch_info));
}

#endif

struct qemu_d3d9_device_DrawTriPatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t handle;
    uint64_t segment_count;
    uint64_t patch_info;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DrawTriPatch(IDirect3DDevice9Ex *iface, UINT handle, const float *segment_count, const D3DTRIPATCH_INFO *patch_info)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DrawTriPatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DRAWTRIPATCH);
    call.iface = (uint64_t)device;
    call.handle = (uint64_t)handle;
    call.segment_count = (uint64_t)segment_count;
    call.patch_info = (uint64_t)patch_info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DrawTriPatch(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DrawTriPatch *c = (struct qemu_d3d9_device_DrawTriPatch *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DrawTriPatch(device->host, c->handle, QEMU_G2H(c->segment_count), QEMU_G2H(c->patch_info));
}

#endif

struct qemu_d3d9_device_DeletePatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_DeletePatch(IDirect3DDevice9Ex *iface, UINT handle)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_DeletePatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_DELETEPATCH);
    call.iface = (uint64_t)device;
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_DeletePatch(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_DeletePatch *c = (struct qemu_d3d9_device_DeletePatch *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_DeletePatch(device->host, c->handle);
}

#endif

struct qemu_d3d9_device_CreateQuery
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type;
    uint64_t query;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateQuery(IDirect3DDevice9Ex *iface, D3DQUERYTYPE type, IDirect3DQuery9 **query)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateQuery call;
    struct qemu_d3d9_query_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEQUERY);
    call.iface = (uint64_t)device;
    call.type = type;
    call.query = (uint64_t)&impl;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        impl->IDirect3DQuery9_iface.lpVtbl = &d3d9_query_vtbl;
        if (query)
            *query = &impl->IDirect3DQuery9_iface;
        else
            IDirect3DQuery9_Release(&impl->IDirect3DQuery9_iface);
    }

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateQuery(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateQuery *c = (struct qemu_d3d9_device_CreateQuery *)call;
    struct qemu_d3d9_device_impl *device;
    struct qemu_d3d9_query_impl *query;
    IDirect3DQuery9 *host;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    query = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*query));
    if (!query)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->super.iret = IDirect3DDevice9Ex_CreateQuery(device->host, c->type, &host);
    if (FAILED(c->super.iret))
    {
        c->query = QEMU_H2G(NULL);
        HeapFree(GetProcessHeap(), 0, query);
        return;
    }

    query->host = host;
    query->device = device;
    *(uint64_t *)QEMU_G2H(c->query) = QEMU_H2G(query);
}

#endif

struct qemu_d3d9_device_SetConvolutionMonoKernel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t rows;
    uint64_t columns;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetConvolutionMonoKernel(IDirect3DDevice9Ex *iface, UINT width, UINT height, float *rows, float *columns)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetConvolutionMonoKernel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETCONVOLUTIONMONOKERNEL);
    call.iface = (uint64_t)device;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.rows = (uint64_t)rows;
    call.columns = (uint64_t)columns;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetConvolutionMonoKernel(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetConvolutionMonoKernel *c = (struct qemu_d3d9_device_SetConvolutionMonoKernel *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetConvolutionMonoKernel(device->host, c->width, c->height, QEMU_G2H(c->rows), QEMU_G2H(c->columns));
}

#endif

struct qemu_d3d9_device_ComposeRects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_surface;
    uint64_t dst_surface;
    uint64_t src_descs;
    uint64_t rect_count;
    uint64_t dst_descs;
    uint64_t operation;
    uint64_t offset_x;
    uint64_t offset_y;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_ComposeRects(IDirect3DDevice9Ex *iface, IDirect3DSurface9 *src_surface, IDirect3DSurface9 *dst_surface, IDirect3DVertexBuffer9 *src_descs, UINT rect_count, IDirect3DVertexBuffer9 *dst_descs, D3DCOMPOSERECTSOP operation, INT offset_x, INT offset_y)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_ComposeRects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_COMPOSERECTS);
    call.iface = (uint64_t)device;
    call.src_surface = (uint64_t)src_surface;
    call.dst_surface = (uint64_t)dst_surface;
    call.src_descs = (uint64_t)src_descs;
    call.rect_count = (uint64_t)rect_count;
    call.dst_descs = (uint64_t)dst_descs;
    call.operation = (uint64_t)operation;
    call.offset_x = (uint64_t)offset_x;
    call.offset_y = (uint64_t)offset_y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_ComposeRects(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_ComposeRects *c = (struct qemu_d3d9_device_ComposeRects *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_ComposeRects(device->host, QEMU_G2H(c->src_surface), QEMU_G2H(c->dst_surface), QEMU_G2H(c->src_descs), c->rect_count, QEMU_G2H(c->dst_descs), c->operation, c->offset_x, c->offset_y);
}

#endif

struct qemu_d3d9_device_PresentEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t src_rect;
    uint64_t dst_rect;
    uint64_t dst_window_override;
    uint64_t dirty_region;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_PresentEx(IDirect3DDevice9Ex *iface, const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override, const RGNDATA *dirty_region, DWORD flags)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_PresentEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_PRESENTEX);
    call.iface = (uint64_t)device;
    call.src_rect = (uint64_t)src_rect;
    call.dst_rect = (uint64_t)dst_rect;
    call.dst_window_override = (uint64_t)dst_window_override;
    call.dirty_region = (uint64_t)dirty_region;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_PresentEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_PresentEx *c = (struct qemu_d3d9_device_PresentEx *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_PresentEx(device->host, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_rect), QEMU_G2H(c->dst_window_override), QEMU_G2H(c->dirty_region), c->flags);
}

#endif

struct qemu_d3d9_device_GetGPUThreadPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetGPUThreadPriority(IDirect3DDevice9Ex *iface, INT *priority)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetGPUThreadPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETGPUTHREADPRIORITY);
    call.iface = (uint64_t)device;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetGPUThreadPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetGPUThreadPriority *c = (struct qemu_d3d9_device_GetGPUThreadPriority *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetGPUThreadPriority(device->host, QEMU_G2H(c->priority));
}

#endif

struct qemu_d3d9_device_SetGPUThreadPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetGPUThreadPriority(IDirect3DDevice9Ex *iface, INT priority)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetGPUThreadPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETGPUTHREADPRIORITY);
    call.iface = (uint64_t)device;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetGPUThreadPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetGPUThreadPriority *c = (struct qemu_d3d9_device_SetGPUThreadPriority *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetGPUThreadPriority(device->host, c->priority);
}

#endif

struct qemu_d3d9_device_WaitForVBlank
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain_idx;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_WaitForVBlank(IDirect3DDevice9Ex *iface, UINT swapchain_idx)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_WaitForVBlank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_WAITFORVBLANK);
    call.iface = (uint64_t)device;
    call.swapchain_idx = (uint64_t)swapchain_idx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_WaitForVBlank(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_WaitForVBlank *c = (struct qemu_d3d9_device_WaitForVBlank *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_WaitForVBlank(device->host, c->swapchain_idx);
}

#endif

struct qemu_d3d9_device_CheckResourceResidency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resources;
    uint64_t resource_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CheckResourceResidency(IDirect3DDevice9Ex *iface, IDirect3DResource9 **resources, UINT32 resource_count)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CheckResourceResidency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CHECKRESOURCERESIDENCY);
    call.iface = (uint64_t)device;
    call.resources = (uint64_t)resources;
    call.resource_count = (uint64_t)resource_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CheckResourceResidency(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CheckResourceResidency *c = (struct qemu_d3d9_device_CheckResourceResidency *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CheckResourceResidency(device->host, QEMU_G2H(c->resources), c->resource_count);
}

#endif

struct qemu_d3d9_device_SetMaximumFrameLatency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t max_latency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_SetMaximumFrameLatency(IDirect3DDevice9Ex *iface, UINT max_latency)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_SetMaximumFrameLatency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_SETMAXIMUMFRAMELATENCY);
    call.iface = (uint64_t)device;
    call.max_latency = (uint64_t)max_latency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_SetMaximumFrameLatency(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_SetMaximumFrameLatency *c = (struct qemu_d3d9_device_SetMaximumFrameLatency *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_SetMaximumFrameLatency(device->host, c->max_latency);
}

#endif

struct qemu_d3d9_device_GetMaximumFrameLatency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t max_latency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetMaximumFrameLatency(IDirect3DDevice9Ex *iface, UINT *max_latency)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetMaximumFrameLatency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETMAXIMUMFRAMELATENCY);
    call.iface = (uint64_t)device;
    call.max_latency = (uint64_t)max_latency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetMaximumFrameLatency(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetMaximumFrameLatency *c = (struct qemu_d3d9_device_GetMaximumFrameLatency *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetMaximumFrameLatency(device->host, QEMU_G2H(c->max_latency));
}

#endif

struct qemu_d3d9_device_CheckDeviceState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dst_window;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CheckDeviceState(IDirect3DDevice9Ex *iface, HWND dst_window)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CheckDeviceState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CHECKDEVICESTATE);
    call.iface = (uint64_t)device;
    call.dst_window = (uint64_t)dst_window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CheckDeviceState(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CheckDeviceState *c = (struct qemu_d3d9_device_CheckDeviceState *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CheckDeviceState(device->host, QEMU_G2H(c->dst_window));
}

#endif

struct qemu_d3d9_device_CreateRenderTargetEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t multisample_type;
    uint64_t multisample_quality;
    uint64_t lockable;
    uint64_t surface;
    uint64_t shared_handle;
    uint64_t usage;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateRenderTargetEx(IDirect3DDevice9Ex *iface, UINT width, UINT height, D3DFORMAT format, D3DMULTISAMPLE_TYPE multisample_type, DWORD multisample_quality, BOOL lockable, IDirect3DSurface9 **surface, HANDLE *shared_handle, DWORD usage)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateRenderTargetEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATERENDERTARGETEX);
    call.iface = (uint64_t)device;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.format = (uint64_t)format;
    call.multisample_type = (uint64_t)multisample_type;
    call.multisample_quality = (uint64_t)multisample_quality;
    call.lockable = (uint64_t)lockable;
    call.surface = (uint64_t)surface;
    call.shared_handle = (uint64_t)shared_handle;
    call.usage = (uint64_t)usage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateRenderTargetEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateRenderTargetEx *c = (struct qemu_d3d9_device_CreateRenderTargetEx *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateRenderTargetEx(device->host, c->width, c->height, c->format, c->multisample_type, c->multisample_quality, c->lockable, QEMU_G2H(c->surface), QEMU_G2H(c->shared_handle), c->usage);
}

#endif

struct qemu_d3d9_device_CreateOffscreenPlainSurfaceEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t pool;
    uint64_t surface;
    uint64_t shared_handle;
    uint64_t usage;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateOffscreenPlainSurfaceEx(IDirect3DDevice9Ex *iface, UINT width, UINT height, D3DFORMAT format, D3DPOOL pool, IDirect3DSurface9 **surface, HANDLE *shared_handle, DWORD usage)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateOffscreenPlainSurfaceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEOFFSCREENPLAINSURFACEEX);
    call.iface = (uint64_t)device;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.format = (uint64_t)format;
    call.pool = (uint64_t)pool;
    call.surface = (uint64_t)surface;
    call.shared_handle = (uint64_t)shared_handle;
    call.usage = (uint64_t)usage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateOffscreenPlainSurfaceEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateOffscreenPlainSurfaceEx *c = (struct qemu_d3d9_device_CreateOffscreenPlainSurfaceEx *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateOffscreenPlainSurfaceEx(device->host, c->width, c->height, c->format, c->pool, QEMU_G2H(c->surface), QEMU_G2H(c->shared_handle), c->usage);
}

#endif

struct qemu_d3d9_device_CreateDepthStencilSurfaceEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t multisample_type;
    uint64_t multisample_quality;
    uint64_t discard;
    uint64_t surface;
    uint64_t shared_handle;
    uint64_t usage;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_CreateDepthStencilSurfaceEx(IDirect3DDevice9Ex *iface, UINT width, UINT height, D3DFORMAT format, D3DMULTISAMPLE_TYPE multisample_type, DWORD multisample_quality, BOOL discard, IDirect3DSurface9 **surface, HANDLE *shared_handle, DWORD usage)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_CreateDepthStencilSurfaceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_CREATEDEPTHSTENCILSURFACEEX);
    call.iface = (uint64_t)device;
    call.width = (uint64_t)width;
    call.height = (uint64_t)height;
    call.format = (uint64_t)format;
    call.multisample_type = (uint64_t)multisample_type;
    call.multisample_quality = (uint64_t)multisample_quality;
    call.discard = (uint64_t)discard;
    call.surface = (uint64_t)surface;
    call.shared_handle = (uint64_t)shared_handle;
    call.usage = (uint64_t)usage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_CreateDepthStencilSurfaceEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_CreateDepthStencilSurfaceEx *c = (struct qemu_d3d9_device_CreateDepthStencilSurfaceEx *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_CreateDepthStencilSurfaceEx(device->host, c->width, c->height, c->format, c->multisample_type, c->multisample_quality, c->discard, QEMU_G2H(c->surface), QEMU_G2H(c->shared_handle), c->usage);
}

#endif

struct qemu_d3d9_device_ResetEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t present_parameters;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_ResetEx(IDirect3DDevice9Ex *iface, D3DPRESENT_PARAMETERS *present_parameters, D3DDISPLAYMODEEX *mode)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_ResetEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_RESETEX);
    call.iface = (uint64_t)device;
    call.present_parameters = (uint64_t)present_parameters;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
        d3d9_device_set_implicit_ifaces(iface);

    return call.super.iret;
}

#else

void qemu_d3d9_device_ResetEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_ResetEx *c = (struct qemu_d3d9_device_ResetEx *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_ResetEx(device->host, QEMU_G2H(c->present_parameters), QEMU_G2H(c->mode));

    if (SUCCEEDED(c->super.iret) && !d3d9_device_wrap_implicit_resources(device))
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
}

#endif

struct qemu_d3d9_device_GetDisplayModeEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swapchain_idx;
    uint64_t mode;
    uint64_t rotation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_device_GetDisplayModeEx(IDirect3DDevice9Ex *iface, UINT swapchain_idx, D3DDISPLAYMODEEX *mode, D3DDISPLAYROTATION *rotation)
{
    struct qemu_d3d9_device_impl *device = impl_from_IDirect3DDevice9Ex(iface);
    struct qemu_d3d9_device_GetDisplayModeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_DEVICE_GETDISPLAYMODEEX);
    call.iface = (uint64_t)device;
    call.swapchain_idx = (uint64_t)swapchain_idx;
    call.mode = (uint64_t)mode;
    call.rotation = (uint64_t)rotation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_device_GetDisplayModeEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_device_GetDisplayModeEx *c = (struct qemu_d3d9_device_GetDisplayModeEx *)call;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DDevice9Ex_GetDisplayModeEx(device->host, c->swapchain_idx, QEMU_G2H(c->mode), QEMU_G2H(c->rotation));
}

#endif

#ifdef QEMU_DLL_GUEST

const struct IDirect3DDevice9ExVtbl d3d9_device_vtbl =
{
    /* IUnknown */
    d3d9_device_QueryInterface,
    d3d9_device_AddRef,
    d3d9_device_Release,
    /* IDirect3DDevice9 */
    d3d9_device_TestCooperativeLevel,
    d3d9_device_GetAvailableTextureMem,
    d3d9_device_EvictManagedResources,
    d3d9_device_GetDirect3D,
    d3d9_device_GetDeviceCaps,
    d3d9_device_GetDisplayMode,
    d3d9_device_GetCreationParameters,
    d3d9_device_SetCursorProperties,
    d3d9_device_SetCursorPosition,
    d3d9_device_ShowCursor,
    d3d9_device_CreateAdditionalSwapChain,
    d3d9_device_GetSwapChain,
    d3d9_device_GetNumberOfSwapChains,
    d3d9_device_Reset,
    d3d9_device_Present,
    d3d9_device_GetBackBuffer,
    d3d9_device_GetRasterStatus,
    d3d9_device_SetDialogBoxMode,
    d3d9_device_SetGammaRamp,
    d3d9_device_GetGammaRamp,
    d3d9_device_CreateTexture,
    d3d9_device_CreateVolumeTexture,
    d3d9_device_CreateCubeTexture,
    d3d9_device_CreateVertexBuffer,
    d3d9_device_CreateIndexBuffer,
    d3d9_device_CreateRenderTarget,
    d3d9_device_CreateDepthStencilSurface,
    d3d9_device_UpdateSurface,
    d3d9_device_UpdateTexture,
    d3d9_device_GetRenderTargetData,
    d3d9_device_GetFrontBufferData,
    d3d9_device_StretchRect,
    d3d9_device_ColorFill,
    d3d9_device_CreateOffscreenPlainSurface,
    d3d9_device_SetRenderTarget,
    d3d9_device_GetRenderTarget,
    d3d9_device_SetDepthStencilSurface,
    d3d9_device_GetDepthStencilSurface,
    d3d9_device_BeginScene,
    d3d9_device_EndScene,
    d3d9_device_Clear,
    d3d9_device_SetTransform,
    d3d9_device_GetTransform,
    d3d9_device_MultiplyTransform,
    d3d9_device_SetViewport,
    d3d9_device_GetViewport,
    d3d9_device_SetMaterial,
    d3d9_device_GetMaterial,
    d3d9_device_SetLight,
    d3d9_device_GetLight,
    d3d9_device_LightEnable,
    d3d9_device_GetLightEnable,
    d3d9_device_SetClipPlane,
    d3d9_device_GetClipPlane,
    d3d9_device_SetRenderState,
    d3d9_device_GetRenderState,
    d3d9_device_CreateStateBlock,
    d3d9_device_BeginStateBlock,
    d3d9_device_EndStateBlock,
    d3d9_device_SetClipStatus,
    d3d9_device_GetClipStatus,
    d3d9_device_GetTexture,
    d3d9_device_SetTexture,
    d3d9_device_GetTextureStageState,
    d3d9_device_SetTextureStageState,
    d3d9_device_GetSamplerState,
    d3d9_device_SetSamplerState,
    d3d9_device_ValidateDevice,
    d3d9_device_SetPaletteEntries,
    d3d9_device_GetPaletteEntries,
    d3d9_device_SetCurrentTexturePalette,
    d3d9_device_GetCurrentTexturePalette,
    d3d9_device_SetScissorRect,
    d3d9_device_GetScissorRect,
    d3d9_device_SetSoftwareVertexProcessing,
    d3d9_device_GetSoftwareVertexProcessing,
    d3d9_device_SetNPatchMode,
    d3d9_device_GetNPatchMode,
    d3d9_device_DrawPrimitive,
    d3d9_device_DrawIndexedPrimitive,
    d3d9_device_DrawPrimitiveUP,
    d3d9_device_DrawIndexedPrimitiveUP,
    d3d9_device_ProcessVertices,
    d3d9_device_CreateVertexDeclaration,
    d3d9_device_SetVertexDeclaration,
    d3d9_device_GetVertexDeclaration,
    d3d9_device_SetFVF,
    d3d9_device_GetFVF,
    d3d9_device_CreateVertexShader,
    d3d9_device_SetVertexShader,
    d3d9_device_GetVertexShader,
    d3d9_device_SetVertexShaderConstantF,
    d3d9_device_GetVertexShaderConstantF,
    d3d9_device_SetVertexShaderConstantI,
    d3d9_device_GetVertexShaderConstantI,
    d3d9_device_SetVertexShaderConstantB,
    d3d9_device_GetVertexShaderConstantB,
    d3d9_device_SetStreamSource,
    d3d9_device_GetStreamSource,
    d3d9_device_SetStreamSourceFreq,
    d3d9_device_GetStreamSourceFreq,
    d3d9_device_SetIndices,
    d3d9_device_GetIndices,
    d3d9_device_CreatePixelShader,
    d3d9_device_SetPixelShader,
    d3d9_device_GetPixelShader,
    d3d9_device_SetPixelShaderConstantF,
    d3d9_device_GetPixelShaderConstantF,
    d3d9_device_SetPixelShaderConstantI,
    d3d9_device_GetPixelShaderConstantI,
    d3d9_device_SetPixelShaderConstantB,
    d3d9_device_GetPixelShaderConstantB,
    d3d9_device_DrawRectPatch,
    d3d9_device_DrawTriPatch,
    d3d9_device_DeletePatch,
    d3d9_device_CreateQuery,
    /* IDirect3DDevice9Ex */
    d3d9_device_SetConvolutionMonoKernel,
    d3d9_device_ComposeRects,
    d3d9_device_PresentEx,
    d3d9_device_GetGPUThreadPriority,
    d3d9_device_SetGPUThreadPriority,
    d3d9_device_WaitForVBlank,
    d3d9_device_CheckResourceResidency,
    d3d9_device_SetMaximumFrameLatency,
    d3d9_device_GetMaximumFrameLatency,
    d3d9_device_CheckDeviceState,
    d3d9_device_CreateRenderTargetEx,
    d3d9_device_CreateOffscreenPlainSurfaceEx,
    d3d9_device_CreateDepthStencilSurfaceEx,
    d3d9_device_ResetEx,
    d3d9_device_GetDisplayModeEx,
};

void d3d9_device_set_implicit_ifaces(IDirect3DDevice9Ex *device)
{
    UINT swapchain_count, i;
    IDirect3DSwapChain9Ex *swapchain;
    IDirect3DSurface9 *ds = NULL;

    /* This code merrily relies on the fact that the GetSwapChain AddRef call
     * happens on the host side and doesn't need the guest vtable. */
    swapchain_count = IDirect3DDevice9Ex_GetNumberOfSwapChains(device);
    for (i = 0; i < swapchain_count; ++i)
    {
        IDirect3DDevice9Ex_GetSwapChain(device, i, (IDirect3DSwapChain9 **)&swapchain);
        swapchain->lpVtbl = &d3d9_swapchain_vtbl;
        d3d9_swapchain_set_surfaces_ifaces(swapchain);
        IDirect3DSwapChain9Ex_Release(swapchain);
    }

    IDirect3DDevice9Ex_GetDepthStencilSurface(device, &ds);
    if (ds)
    {
        ds->lpVtbl = &d3d9_surface_vtbl;
        IDirect3DSurface9_Release(ds);
    }
}

#else

BOOL d3d9_device_wrap_implicit_resources(struct qemu_d3d9_device_impl *device)
{
    UINT swapchain_count, i;
    struct qemu_d3d9_swapchain_impl *swapchain;
    IDirect3DSwapChain9Ex *host_swapchain;
    D3DPRESENT_PARAMETERS pp;
    IDirect3DSurface9 *surface;
    struct qemu_d3d9_surface_impl *ds_impl;
    struct qemu_d3d9_subresource_impl *subresource_impl;
    IUnknown *priv_data;
    DWORD size;
    HRESULT hr;

    swapchain_count = IDirect3DDevice9_GetNumberOfSwapChains(device->host);
    for (i = 0; i < swapchain_count; ++i)
    {
        IDirect3DDevice9_GetSwapChain(device->host, i, (IDirect3DSwapChain9 **)&host_swapchain);
        IDirect3DSwapChain9_GetPresentParameters(host_swapchain, &pp);

        /* Take care in case of calls from _Reset(), we might already have our private data. */
        IDirect3DSwapChain9_GetBackBuffer(host_swapchain, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
        size = sizeof(priv_data);
        hr = IDirect3DSurface9_GetPrivateData(surface, &qemu_d3d9_swapchain_guid, &priv_data, &size);
        IDirect3DSurface9_Release(surface);

        if (SUCCEEDED(hr))
        {
            swapchain = swapchain_impl_from_IUnknown(priv_data);
            if (swapchain->back_buffer_count != pp.BackBufferCount)
            {
                /* Not as easy as re-allocating the wrapper because the external
                 * pointer should probably remain the same, just as the host pointer
                 * did. May need a separate allocation for the backbuffer array. But
                 * maybe if we grow from 2 backbuffers to 4 backbuffers 0 and 1 should
                 * remain in place too. Needs tests. */
                WINE_FIXME("Backbuffer count changed from %u to %u.\n",
                        swapchain->back_buffer_count, pp.BackBufferCount);
            }
            priv_data->lpVtbl->Release(priv_data);
        }
        else
        {
            swapchain = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                    offsetof(struct qemu_d3d9_swapchain_impl, backbuffers[pp.BackBufferCount]));
            WINE_TRACE("Allocated swapchain wrapper %p.\n", swapchain);
            if (!swapchain)
            {
                IDirect3DSwapChain9_Release(host_swapchain);
                goto error;
            }
            swapchain->back_buffer_count = pp.BackBufferCount;
            d3d9_swapchain_init(swapchain, host_swapchain, device);
        }
        IDirect3DSwapChain9_Release(host_swapchain);
    }

    IDirect3DDevice9Ex_GetDepthStencilSurface(device->host, &surface);
    if (surface)
    {
        /* Take care in case of calls from _Reset(), we might already have our private data. */
        size = sizeof(subresource_impl);
        hr = IDirect3DSurface9_GetPrivateData(surface, &qemu_d3d9_surface_guid, &subresource_impl, &size);
        if (FAILED(hr))
        {
            ds_impl = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ds_impl));
            if (!ds_impl)
            {
                IDirect3DSurface9_Release(surface);
                goto error;
            }
            d3d9_standalone_surface_init(ds_impl, surface, device);
        }
        IDirect3DSurface9_Release(surface);
    }

    return TRUE;

error:
    WINE_ERR("Something went wrong when setting up wrapper interfaces.\n");
    /* TODO: Free stuff */
    return FALSE;
}

#endif
