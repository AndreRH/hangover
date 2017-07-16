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
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_d3d9_swapchain_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_swapchain_impl *impl_from_IDirect3DSwapChain9Ex(IDirect3DSwapChain9Ex *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_swapchain_impl, IDirect3DSwapChain9Ex_iface);
}

static HRESULT WINAPI d3d9_swapchain_QueryInterface(IDirect3DSwapChain9Ex *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_QUERYINTERFACE);
    call.iface = (uint64_t)swapchain;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_QueryInterface *c = (struct qemu_d3d9_swapchain_QueryInterface *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_QueryInterface(swapchain->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_swapchain_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_swapchain_AddRef(IDirect3DSwapChain9Ex *iface)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_ADDREF);
    call.iface = (uint64_t)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_AddRef *c = (struct qemu_d3d9_swapchain_AddRef *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_AddRef(swapchain->host);
}

#endif

struct qemu_d3d9_swapchain_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_swapchain_Release(IDirect3DSwapChain9Ex *iface)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_RELEASE);
    call.iface = (uint64_t)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_Release *c = (struct qemu_d3d9_swapchain_Release *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_Release(swapchain->host);
}

#endif

struct qemu_d3d9_swapchain_Present
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

static HRESULT WINAPI d3d9_swapchain_Present(IDirect3DSwapChain9Ex *iface, const RECT *src_rect, const RECT *dst_rect, HWND dst_window_override, const RGNDATA *dirty_region, DWORD flags)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_Present call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_PRESENT);
    call.iface = (uint64_t)swapchain;
    call.src_rect = (uint64_t)src_rect;
    call.dst_rect = (uint64_t)dst_rect;
    call.dst_window_override = (uint64_t)dst_window_override;
    call.dirty_region = (uint64_t)dirty_region;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_Present(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_Present *c = (struct qemu_d3d9_swapchain_Present *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_Present(swapchain->host, QEMU_G2H(c->src_rect), QEMU_G2H(c->dst_rect), QEMU_G2H(c->dst_window_override), QEMU_G2H(c->dirty_region), c->flags);
}

#endif

struct qemu_d3d9_swapchain_GetFrontBufferData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetFrontBufferData(IDirect3DSwapChain9Ex *iface, IDirect3DSurface9 *surface)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetFrontBufferData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETFRONTBUFFERDATA);
    call.iface = (uint64_t)swapchain;
    call.surface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetFrontBufferData(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetFrontBufferData *c = (struct qemu_d3d9_swapchain_GetFrontBufferData *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_GetFrontBufferData(swapchain->host, QEMU_G2H(c->surface));
}

#endif

struct qemu_d3d9_swapchain_GetBackBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t backbuffer_idx;
    uint64_t backbuffer_type;
    uint64_t backbuffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetBackBuffer(IDirect3DSwapChain9Ex *iface, UINT backbuffer_idx, D3DBACKBUFFER_TYPE backbuffer_type, IDirect3DSurface9 **backbuffer)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetBackBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETBACKBUFFER);
    call.iface = (uint64_t)swapchain;
    call.backbuffer_idx = (uint64_t)backbuffer_idx;
    call.backbuffer_type = (uint64_t)backbuffer_type;
    call.backbuffer = (uint64_t)backbuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetBackBuffer(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetBackBuffer *c = (struct qemu_d3d9_swapchain_GetBackBuffer *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_GetBackBuffer(swapchain->host, c->backbuffer_idx, c->backbuffer_type, QEMU_G2H(c->backbuffer));
}

#endif

struct qemu_d3d9_swapchain_GetRasterStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t raster_status;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetRasterStatus(IDirect3DSwapChain9Ex *iface, D3DRASTER_STATUS *raster_status)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetRasterStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETRASTERSTATUS);
    call.iface = (uint64_t)swapchain;
    call.raster_status = (uint64_t)raster_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetRasterStatus(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetRasterStatus *c = (struct qemu_d3d9_swapchain_GetRasterStatus *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_GetRasterStatus(swapchain->host, QEMU_G2H(c->raster_status));
}

#endif

struct qemu_d3d9_swapchain_GetDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetDisplayMode(IDirect3DSwapChain9Ex *iface, D3DDISPLAYMODE *mode)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETDISPLAYMODE);
    call.iface = (uint64_t)swapchain;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetDisplayMode(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetDisplayMode *c = (struct qemu_d3d9_swapchain_GetDisplayMode *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_GetDisplayMode(swapchain->host, QEMU_G2H(c->mode));
}

#endif

struct qemu_d3d9_swapchain_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetDevice(IDirect3DSwapChain9Ex *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETDEVICE);
    call.iface = (uint64_t)swapchain;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetDevice *c = (struct qemu_d3d9_swapchain_GetDevice *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_GetDevice(swapchain->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_swapchain_GetPresentParameters
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t parameters;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetPresentParameters(IDirect3DSwapChain9Ex *iface, D3DPRESENT_PARAMETERS *parameters)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetPresentParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETPRESENTPARAMETERS);
    call.iface = (uint64_t)swapchain;
    call.parameters = (uint64_t)parameters;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetPresentParameters(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetPresentParameters *c = (struct qemu_d3d9_swapchain_GetPresentParameters *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9_GetPresentParameters(swapchain->host, QEMU_G2H(c->parameters));
}

#endif

struct qemu_d3d9_swapchain_GetLastPresentCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t last_present_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetLastPresentCount(IDirect3DSwapChain9Ex *iface, UINT *last_present_count)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetLastPresentCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETLASTPRESENTCOUNT);
    call.iface = (uint64_t)swapchain;
    call.last_present_count = (uint64_t)last_present_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetLastPresentCount(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetLastPresentCount *c = (struct qemu_d3d9_swapchain_GetLastPresentCount *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9Ex_GetLastPresentCount(swapchain->host, QEMU_G2H(c->last_present_count));
}

#endif

struct qemu_d3d9_swapchain_GetPresentStatistics
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t present_stats;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetPresentStatistics(IDirect3DSwapChain9Ex *iface, D3DPRESENTSTATS *present_stats)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetPresentStatistics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETPRESENTSTATISTICS);
    call.iface = (uint64_t)swapchain;
    call.present_stats = (uint64_t)present_stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetPresentStatistics(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetPresentStatistics *c = (struct qemu_d3d9_swapchain_GetPresentStatistics *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9Ex_GetPresentStats(swapchain->host, QEMU_G2H(c->present_stats));
}

#endif

struct qemu_d3d9_swapchain_GetDisplayModeEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t rotation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_swapchain_GetDisplayModeEx(IDirect3DSwapChain9Ex *iface, D3DDISPLAYMODEEX *mode, D3DDISPLAYROTATION *rotation)
{
    struct qemu_d3d9_swapchain_impl *swapchain = impl_from_IDirect3DSwapChain9Ex(iface);
    struct qemu_d3d9_swapchain_GetDisplayModeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SWAPCHAIN_GETDISPLAYMODEEX);
    call.iface = (uint64_t)swapchain;
    call.mode = (uint64_t)mode;
    call.rotation = (uint64_t)rotation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_swapchain_GetDisplayModeEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_swapchain_GetDisplayModeEx *c = (struct qemu_d3d9_swapchain_GetDisplayModeEx *)call;
    struct qemu_d3d9_swapchain_impl *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSwapChain9Ex_GetDisplayModeEx(swapchain->host, QEMU_G2H(c->mode), QEMU_G2H(c->rotation));
}

#endif

