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

struct qemu_d3d9_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_impl *impl_from_IDirect3D9Ex(IDirect3D9Ex *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_impl, IDirect3D9Ex_iface);
}

static HRESULT WINAPI d3d9_QueryInterface(IDirect3D9Ex *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_QUERYINTERFACE);
    call.iface = (uint64_t)d3d9;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    /* This call either returns IDirect3D9 or IDirect3D9Ex, but no other
     * interface. */
    if (SUCCEEDED(call.super.iret))
        *out = iface;

    return call.super.iret;
}

#else

void qemu_d3d9_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_QueryInterface *c = (struct qemu_d3d9_QueryInterface *)call;
    struct qemu_d3d9_impl *d3d9;
    GUID *iid;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    c->super.iret = IDirect3D9_QueryInterface(d3d9->host, iid, QEMU_G2H(c->out));

    if (SUCCEEDED(c->super.iret) && !IsEqualGUID(iid, &IID_IDirect3D9)
            && !IsEqualGUID(iid, &IID_IDirect3D9Ex) && !IsEqualGUID(iid, &IID_IUnknown))
        WINE_FIXME("Unexpected GUID %s.\n", wine_dbgstr_guid(iid));
}

#endif

struct qemu_d3d9_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_AddRef(IDirect3D9Ex *iface)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_ADDREF);
    call.iface = (uint64_t)d3d9;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG d3d9_wrapper_addref(struct qemu_d3d9_impl *d3d9)
{
    return IDirect3D9Ex_AddRef(d3d9->host);
}

void qemu_d3d9_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_AddRef *c = (struct qemu_d3d9_AddRef *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_AddRef(d3d9->host);
}

#endif

struct qemu_d3d9_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_Release(IDirect3D9Ex *iface)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_RELEASE);
    call.iface = (uint64_t)d3d9;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG d3d9_wrapper_release(struct qemu_d3d9_impl *d3d9)
{
    ULONG ref = IDirect3D9Ex_Release(d3d9->host);

    if (!ref)
        HeapFree(GetProcessHeap(), 0, d3d9);

    return ref;
}

void qemu_d3d9_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_Release *c = (struct qemu_d3d9_Release *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = d3d9_wrapper_release(d3d9);
}

#endif

struct qemu_d3d9_RegisterSoftwareDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t init_function;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_RegisterSoftwareDevice(IDirect3D9Ex *iface, void *init_function)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_RegisterSoftwareDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_REGISTERSOFTWAREDEVICE);
    call.iface = (uint64_t)d3d9;
    call.init_function = (uint64_t)init_function;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_RegisterSoftwareDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_RegisterSoftwareDevice *c = (struct qemu_d3d9_RegisterSoftwareDevice *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_FIXME("Unverified\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_RegisterSoftwareDevice(d3d9->host, QEMU_G2H(c->init_function));
}

#endif

struct qemu_d3d9_GetAdapterCount
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT WINAPI d3d9_GetAdapterCount(IDirect3D9Ex *iface)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERCOUNT);
    call.iface = (uint64_t)d3d9;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterCount(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterCount *c = (struct qemu_d3d9_GetAdapterCount *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_GetAdapterCount(d3d9->host);
}

#endif

struct qemu_d3d9_GetAdapterIdentifier
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t flags;
    uint64_t identifier;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_GetAdapterIdentifier(IDirect3D9Ex *iface, UINT adapter, DWORD flags, D3DADAPTER_IDENTIFIER9 *identifier)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterIdentifier call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERIDENTIFIER);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.flags = (uint64_t)flags;
    call.identifier = (uint64_t)identifier;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterIdentifier(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterIdentifier *c = (struct qemu_d3d9_GetAdapterIdentifier *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_GetAdapterIdentifier(d3d9->host, c->adapter, c->flags, QEMU_G2H(c->identifier));
}

#endif

struct qemu_d3d9_GetAdapterModeCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static UINT WINAPI d3d9_GetAdapterModeCount(IDirect3D9Ex *iface, UINT adapter, D3DFORMAT format)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterModeCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERMODECOUNT);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.format = (uint64_t)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterModeCount(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterModeCount *c = (struct qemu_d3d9_GetAdapterModeCount *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_GetAdapterModeCount(d3d9->host, c->adapter, c->format);
}

#endif

struct qemu_d3d9_EnumAdapterModes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t format;
    uint64_t mode_idx;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_EnumAdapterModes(IDirect3D9Ex *iface, UINT adapter, D3DFORMAT format, UINT mode_idx, D3DDISPLAYMODE *mode)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_EnumAdapterModes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_ENUMADAPTERMODES);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.format = (uint64_t)format;
    call.mode_idx = (uint64_t)mode_idx;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_EnumAdapterModes(struct qemu_syscall *call)
{
    struct qemu_d3d9_EnumAdapterModes *c = (struct qemu_d3d9_EnumAdapterModes *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_EnumAdapterModes(d3d9->host, c->adapter, c->format, c->mode_idx, QEMU_G2H(c->mode));
}

#endif

struct qemu_d3d9_GetAdapterDisplayMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_GetAdapterDisplayMode(IDirect3D9Ex *iface, UINT adapter, D3DDISPLAYMODE *mode)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterDisplayMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERDISPLAYMODE);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterDisplayMode(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterDisplayMode *c = (struct qemu_d3d9_GetAdapterDisplayMode *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_GetAdapterDisplayMode(d3d9->host, c->adapter, QEMU_G2H(c->mode));
}

#endif

struct qemu_d3d9_CheckDeviceType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t display_format;
    uint64_t backbuffer_format;
    uint64_t windowed;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CheckDeviceType(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT display_format, D3DFORMAT backbuffer_format, BOOL windowed)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_CheckDeviceType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CHECKDEVICETYPE);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.display_format = (uint64_t)display_format;
    call.backbuffer_format = (uint64_t)backbuffer_format;
    call.windowed = (uint64_t)windowed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_CheckDeviceType(struct qemu_syscall *call)
{
    struct qemu_d3d9_CheckDeviceType *c = (struct qemu_d3d9_CheckDeviceType *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_CheckDeviceType(d3d9->host, c->adapter, c->device_type, c->display_format, c->backbuffer_format, c->windowed);
}

#endif

struct qemu_d3d9_CheckDeviceFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t adapter_format;
    uint64_t usage;
    uint64_t resource_type;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CheckDeviceFormat(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT adapter_format, DWORD usage, D3DRESOURCETYPE resource_type, D3DFORMAT format)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_CheckDeviceFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CHECKDEVICEFORMAT);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.adapter_format = (uint64_t)adapter_format;
    call.usage = (uint64_t)usage;
    call.resource_type = (uint64_t)resource_type;
    call.format = (uint64_t)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_CheckDeviceFormat(struct qemu_syscall *call)
{
    struct qemu_d3d9_CheckDeviceFormat *c = (struct qemu_d3d9_CheckDeviceFormat *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_CheckDeviceFormat(d3d9->host, c->adapter, c->device_type, c->adapter_format, c->usage, c->resource_type, c->format);
}

#endif

struct qemu_d3d9_CheckDeviceMultiSampleType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t format;
    uint64_t windowed;
    uint64_t multisample_type;
    uint64_t levels;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CheckDeviceMultiSampleType(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT format, BOOL windowed, D3DMULTISAMPLE_TYPE multisample_type, DWORD *levels)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_CheckDeviceMultiSampleType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CHECKDEVICEMULTISAMPLETYPE);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.format = (uint64_t)format;
    call.windowed = (uint64_t)windowed;
    call.multisample_type = (uint64_t)multisample_type;
    call.levels = (uint64_t)levels;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_CheckDeviceMultiSampleType(struct qemu_syscall *call)
{
    struct qemu_d3d9_CheckDeviceMultiSampleType *c = (struct qemu_d3d9_CheckDeviceMultiSampleType *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_CheckDeviceMultiSampleType(d3d9->host, c->adapter, c->device_type, c->format, c->windowed, c->multisample_type, QEMU_G2H(c->levels));
}

#endif

struct qemu_d3d9_CheckDepthStencilMatch
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t adapter_format;
    uint64_t rt_format;
    uint64_t ds_format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CheckDepthStencilMatch(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT adapter_format, D3DFORMAT rt_format, D3DFORMAT ds_format)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_CheckDepthStencilMatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CHECKDEPTHSTENCILMATCH);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.adapter_format = (uint64_t)adapter_format;
    call.rt_format = (uint64_t)rt_format;
    call.ds_format = (uint64_t)ds_format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_CheckDepthStencilMatch(struct qemu_syscall *call)
{
    struct qemu_d3d9_CheckDepthStencilMatch *c = (struct qemu_d3d9_CheckDepthStencilMatch *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_CheckDepthStencilMatch(d3d9->host, c->adapter, c->device_type, c->adapter_format, c->rt_format, c->ds_format);
}

#endif

struct qemu_d3d9_CheckDeviceFormatConversion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t src_format;
    uint64_t dst_format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CheckDeviceFormatConversion(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, D3DFORMAT src_format, D3DFORMAT dst_format)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_CheckDeviceFormatConversion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CHECKDEVICEFORMATCONVERSION);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.src_format = (uint64_t)src_format;
    call.dst_format = (uint64_t)dst_format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_CheckDeviceFormatConversion(struct qemu_syscall *call)
{
    struct qemu_d3d9_CheckDeviceFormatConversion *c = (struct qemu_d3d9_CheckDeviceFormatConversion *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_CheckDeviceFormatConversion(d3d9->host, c->adapter, c->device_type, c->src_format, c->dst_format);
}

#endif

struct qemu_d3d9_GetDeviceCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_GetDeviceCaps(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, D3DCAPS9 *caps)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetDeviceCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETDEVICECAPS);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.caps = (uint64_t)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetDeviceCaps(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetDeviceCaps *c = (struct qemu_d3d9_GetDeviceCaps *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9_GetDeviceCaps(d3d9->host, c->adapter, c->device_type, QEMU_G2H(c->caps));
}

#endif

struct qemu_d3d9_GetAdapterMonitor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
};

#ifdef QEMU_DLL_GUEST

static HMONITOR WINAPI d3d9_GetAdapterMonitor(IDirect3D9Ex *iface, UINT adapter)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterMonitor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERMONITOR);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;

    qemu_syscall(&call.super);

    return (HMONITOR)call.super.iret;
}

#else

void qemu_d3d9_GetAdapterMonitor(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterMonitor *c = (struct qemu_d3d9_GetAdapterMonitor *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = (uint64_t)IDirect3D9_GetAdapterMonitor(d3d9->host, c->adapter);
}

#endif

struct qemu_d3d9_CreateDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t focus_window;
    uint64_t flags;
    uint64_t parameters;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CreateDevice(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, HWND focus_window, DWORD flags, D3DPRESENT_PARAMETERS *parameters, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_CreateDevice call;
    struct qemu_d3d9_device_impl *ret;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CREATEDEVICE);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.device_type = (uint64_t)device_type;
    call.focus_window = (uint64_t)focus_window;
    call.flags = (uint64_t)flags;
    call.parameters = (uint64_t)parameters;
    call.device = (uint64_t)&ret;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *device = NULL;
        return call.super.iret;
    }

    ret->IDirect3DDevice9Ex_iface.lpVtbl = &d3d9_device_vtbl;
    *device = (IDirect3DDevice9 *)&ret->IDirect3DDevice9Ex_iface;
    d3d9_device_set_implicit_ifaces(&ret->IDirect3DDevice9Ex_iface);

    return call.super.iret;
}

#else

void qemu_d3d9_CreateDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_CreateDevice *c = (struct qemu_d3d9_CreateDevice *)call;
    struct qemu_d3d9_impl *d3d9;
    struct qemu_d3d9_device_impl *device_impl;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    device_impl = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*device_impl));
    if (!device_impl)
    {
        c->super.iret = E_OUTOFMEMORY;
        goto error;
    }

    c->super.iret = IDirect3D9_CreateDevice(d3d9->host, c->adapter, c->device_type,
            QEMU_G2H(c->focus_window), c->flags, QEMU_G2H(c->parameters),
            (IDirect3DDevice9 **)&device_impl->host);
    if (FAILED(c->super.iret))
        goto error;

    /* The host library takes care of refcounting here. */
    device_impl->d3d9 = d3d9;
    device_impl->state = &device_impl->dev_state;
    if (!d3d9_device_wrap_implicit_resources(device_impl))
    {
        c->super.iret = E_OUTOFMEMORY;
        goto error;
    }

    *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(device_impl);

    return;

error:
    if (device_impl->host)
        IDirect3DDevice9Ex_Release(device_impl->host);
    HeapFree(GetProcessHeap(), 0, device_impl);
}

#endif

struct qemu_d3d9_GetAdapterModeCountEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t filter;
};

#ifdef QEMU_DLL_GUEST

static UINT WINAPI d3d9_GetAdapterModeCountEx(IDirect3D9Ex *iface, UINT adapter, const D3DDISPLAYMODEFILTER *filter)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterModeCountEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERMODECOUNTEX);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.filter = (uint64_t)filter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterModeCountEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterModeCountEx *c = (struct qemu_d3d9_GetAdapterModeCountEx *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9Ex_GetAdapterModeCountEx(d3d9->host, c->adapter, QEMU_G2H(c->filter));
}

#endif

struct qemu_d3d9_EnumAdapterModesEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t filter;
    uint64_t mode_idx;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_EnumAdapterModesEx(IDirect3D9Ex *iface, UINT adapter, const D3DDISPLAYMODEFILTER *filter, UINT mode_idx, D3DDISPLAYMODEEX *mode)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_EnumAdapterModesEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_ENUMADAPTERMODESEX);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.filter = (uint64_t)filter;
    call.mode_idx = (uint64_t)mode_idx;
    call.mode = (uint64_t)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_EnumAdapterModesEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_EnumAdapterModesEx *c = (struct qemu_d3d9_EnumAdapterModesEx *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9Ex_EnumAdapterModesEx(d3d9->host, c->adapter, QEMU_G2H(c->filter), c->mode_idx, QEMU_G2H(c->mode));
}

#endif

struct qemu_d3d9_GetAdapterDisplayModeEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t mode;
    uint64_t rotation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_GetAdapterDisplayModeEx(IDirect3D9Ex *iface, UINT adapter, D3DDISPLAYMODEEX *mode, D3DDISPLAYROTATION *rotation)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterDisplayModeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERDISPLAYMODEEX);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.mode = (uint64_t)mode;
    call.rotation = (uint64_t)rotation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterDisplayModeEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterDisplayModeEx *c = (struct qemu_d3d9_GetAdapterDisplayModeEx *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9Ex_GetAdapterDisplayModeEx(d3d9->host, c->adapter, QEMU_G2H(c->mode), QEMU_G2H(c->rotation));
}

#endif

struct qemu_d3d9_CreateDeviceEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t device_type;
    uint64_t focus_window;
    uint64_t flags;
    uint64_t parameters;
    uint64_t mode;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_CreateDeviceEx(IDirect3D9Ex *iface, UINT adapter, D3DDEVTYPE device_type, HWND focus_window, DWORD flags, D3DPRESENT_PARAMETERS *parameters, D3DDISPLAYMODEEX *mode, IDirect3DDevice9Ex **device)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_device_impl *ret;
    struct qemu_d3d9_CreateDeviceEx call;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_CREATEDEVICEEX);
    call.iface = (uint64_t)d3d9;
    call.adapter = adapter;
    call.device_type = device_type;
    call.focus_window = (uint64_t)focus_window;
    call.flags = flags;
    call.parameters = (uint64_t)parameters;
    call.mode = (uint64_t)mode;
    call.device = (uint64_t)&ret;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *device = NULL;
        return call.super.iret;
    }

    ret->IDirect3DDevice9Ex_iface.lpVtbl = &d3d9_device_vtbl;
    *device = &ret->IDirect3DDevice9Ex_iface;
    d3d9_device_set_implicit_ifaces(&ret->IDirect3DDevice9Ex_iface);

    return call.super.iret;
}

#else

void qemu_d3d9_CreateDeviceEx(struct qemu_syscall *call)
{
    struct qemu_d3d9_CreateDeviceEx *c = (struct qemu_d3d9_CreateDeviceEx *)call;
    struct qemu_d3d9_impl *d3d9;
    struct qemu_d3d9_device_impl *device_impl;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    device_impl = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*device_impl));
    if (!device_impl)
    {
        c->super.iret = E_OUTOFMEMORY;
        goto error;
    }

    c->super.iret = IDirect3D9Ex_CreateDeviceEx(d3d9->host, c->adapter, c->device_type, QEMU_G2H(c->focus_window),
            c->flags, QEMU_G2H(c->parameters), QEMU_G2H(c->mode), &device_impl->host);
    if (FAILED(c->super.iret))
        goto error;

    /* The host library takes care of refcounting here. */
    device_impl->d3d9 = d3d9;
    device_impl->state = &device_impl->dev_state;
    if (!d3d9_device_wrap_implicit_resources(device_impl))
    {
        c->super.iret = E_OUTOFMEMORY;
        goto error;
    }

    *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(device_impl);

    return;

error:
    if (device_impl->host)
        IDirect3DDevice9Ex_Release(device_impl->host);
    HeapFree(GetProcessHeap(), 0, device_impl);
}

#endif

struct qemu_d3d9_GetAdapterLUID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter;
    uint64_t luid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_GetAdapterLUID(IDirect3D9Ex *iface, UINT adapter, LUID *luid)
{
    struct qemu_d3d9_impl *d3d9 = impl_from_IDirect3D9Ex(iface);
    struct qemu_d3d9_GetAdapterLUID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_GETADAPTERLUID);
    call.iface = (uint64_t)d3d9;
    call.adapter = (uint64_t)adapter;
    call.luid = (uint64_t)luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_GetAdapterLUID(struct qemu_syscall *call)
{
    struct qemu_d3d9_GetAdapterLUID *c = (struct qemu_d3d9_GetAdapterLUID *)call;
    struct qemu_d3d9_impl *d3d9;

    WINE_TRACE("\n");
    d3d9 = QEMU_G2H(c->iface);

    c->super.iret = IDirect3D9Ex_GetAdapterLUID(d3d9->host, c->adapter, QEMU_G2H(c->luid));
}

#endif

#ifdef QEMU_DLL_GUEST

const struct IDirect3D9ExVtbl d3d9_vtbl =
{
    /* IUnknown */
    d3d9_QueryInterface,
    d3d9_AddRef,
    d3d9_Release,
    /* IDirect3D9 */
    d3d9_RegisterSoftwareDevice,
    d3d9_GetAdapterCount,
    d3d9_GetAdapterIdentifier,
    d3d9_GetAdapterModeCount,
    d3d9_EnumAdapterModes,
    d3d9_GetAdapterDisplayMode,
    d3d9_CheckDeviceType,
    d3d9_CheckDeviceFormat,
    d3d9_CheckDeviceMultiSampleType,
    d3d9_CheckDepthStencilMatch,
    d3d9_CheckDeviceFormatConversion,
    d3d9_GetDeviceCaps,
    d3d9_GetAdapterMonitor,
    d3d9_CreateDevice,
    /* IDirect3D9Ex */
    d3d9_GetAdapterModeCountEx,
    d3d9_EnumAdapterModesEx,
    d3d9_GetAdapterDisplayModeEx,
    d3d9_CreateDeviceEx,
    d3d9_GetAdapterLUID,
};

#endif
