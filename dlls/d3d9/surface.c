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

struct qemu_d3d9_surface_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_surface_impl *impl_from_IDirect3DSurface(IDirect3DSurface9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_surface_impl, IDirect3DSurface9_iface);
}

static HRESULT WINAPI d3d9_surface_QueryInterface(IDirect3DSurface9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_QUERYINTERFACE);
    call.iface = (uint64_t)surface;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_QueryInterface *c = (struct qemu_d3d9_surface_QueryInterface *)call;
    struct qemu_d3d9_surface_impl *surface;

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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_ADDREF);
    call.iface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_AddRef *c = (struct qemu_d3d9_surface_AddRef *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
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

static ULONG WINAPI d3d9_surface_Release(IDirect3DSurface9 *iface)
{
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_RELEASE);
    call.iface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_Release *c = (struct qemu_d3d9_surface_Release *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_Release(surface->host);
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETDEVICE);
    call.iface = (uint64_t)surface;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetDevice *c = (struct qemu_d3d9_surface_GetDevice *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetDevice(surface->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_surface_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_SetPrivateData(IDirect3DSurface9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_SetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_SETPRIVATEDATA);
    call.iface = (uint64_t)surface;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_SetPrivateData *c = (struct qemu_d3d9_surface_SetPrivateData *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_SetPrivateData(surface->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d9_surface_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetPrivateData(IDirect3DSurface9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETPRIVATEDATA);
    call.iface = (uint64_t)surface;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetPrivateData *c = (struct qemu_d3d9_surface_GetPrivateData *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetPrivateData(surface->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), QEMU_G2H(c->data_size));
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_FreePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_FREEPRIVATEDATA);
    call.iface = (uint64_t)surface;
    call.guid = (uint64_t)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_FreePrivateData *c = (struct qemu_d3d9_surface_FreePrivateData *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_FreePrivateData(surface->host, QEMU_G2H(c->guid));
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_SETPRIORITY);
    call.iface = (uint64_t)surface;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_SetPriority *c = (struct qemu_d3d9_surface_SetPriority *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETPRIORITY);
    call.iface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetPriority *c = (struct qemu_d3d9_surface_GetPriority *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_PRELOAD);
    call.iface = (uint64_t)surface;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_surface_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_PreLoad *c = (struct qemu_d3d9_surface_PreLoad *)call;
    struct qemu_d3d9_surface_impl *surface;

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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETTYPE);
    call.iface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetType *c = (struct qemu_d3d9_surface_GetType *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetType(surface->host);
}

#endif

struct qemu_d3d9_surface_GetContainer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t container;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_surface_GetContainer(IDirect3DSurface9 *iface, REFIID riid, void **container)
{
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetContainer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETCONTAINER);
    call.iface = (uint64_t)surface;
    call.riid = (uint64_t)riid;
    call.container = (uint64_t)container;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetContainer(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetContainer *c = (struct qemu_d3d9_surface_GetContainer *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_GetContainer(surface->host, QEMU_G2H(c->riid), QEMU_G2H(c->container));
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETDESC);
    call.iface = (uint64_t)surface;
    call.desc = (uint64_t)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetDesc *c = (struct qemu_d3d9_surface_GetDesc *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_LockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_LOCKRECT);
    call.iface = (uint64_t)surface;
    call.locked_rect = (uint64_t)locked_rect;
    call.rect = (uint64_t)rect;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_LockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_LockRect *c = (struct qemu_d3d9_surface_LockRect *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_LockRect(surface->host, QEMU_G2H(c->locked_rect), QEMU_G2H(c->rect), c->flags);
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_UnlockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_UNLOCKRECT);
    call.iface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_UnlockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_UnlockRect *c = (struct qemu_d3d9_surface_UnlockRect *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_GetDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_GETDC);
    call.iface = (uint64_t)surface;
    call.dc = (uint64_t)dc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_GetDC(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_GetDC *c = (struct qemu_d3d9_surface_GetDC *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
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
    struct qemu_d3d9_surface_impl *surface = impl_from_IDirect3DSurface(iface);
    struct qemu_d3d9_surface_ReleaseDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_SURFACE_RELEASEDC);
    call.iface = (uint64_t)surface;
    call.dc = (uint64_t)dc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_surface_ReleaseDC(struct qemu_syscall *call)
{
    struct qemu_d3d9_surface_ReleaseDC *c = (struct qemu_d3d9_surface_ReleaseDC *)call;
    struct qemu_d3d9_surface_impl *surface;

    WINE_FIXME("Unverified!\n");
    surface = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DSurface9_ReleaseDC(surface->host, QEMU_G2H(c->dc));
}

#endif

