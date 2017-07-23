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

struct qemu_d3d9_texture_2d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_texture_impl *impl_from_IDirect3DTexture9(IDirect3DTexture9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_texture_impl, IDirect3DBaseTexture9_iface);
}

static HRESULT WINAPI d3d9_texture_2d_QueryInterface(IDirect3DTexture9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_QUERYINTERFACE);
    call.iface = (uint64_t)texture;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    /* This call returns only the texture interfaces. */
    if (SUCCEEDED(call.super.iret))
        *out = &texture->IDirect3DBaseTexture9_iface;

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_QueryInterface *c = (struct qemu_d3d9_texture_2d_QueryInterface *)call;
    struct qemu_d3d9_texture_impl *texture;
    GUID *iid;
    void *out;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);
    iid = QEMU_G2H(c->riid);

    c->super.iret = IDirect3DTexture9_QueryInterface(texture->host, iid, &out);

    *(uint64_t *)QEMU_G2H(c->out) = QEMU_H2G(out);
    if (SUCCEEDED(c->super.iret) && out != texture->host)
        WINE_FIXME("Unexpected interface %p, GUID %s.\n", out, wine_dbgstr_guid(iid));
}

#endif

struct qemu_d3d9_texture_2d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_texture_2d_AddRef(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_ADDREF);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_AddRef *c = (struct qemu_d3d9_texture_2d_AddRef *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_AddRef(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_texture_2d_Release(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_RELEASE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_Release *c = (struct qemu_d3d9_texture_2d_Release *)call;
    struct qemu_d3d9_texture_impl *texture;
    struct qemu_d3d9_device_impl *device;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);
    device = texture->device;

    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DTexture9_Release(texture->host);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_texture_2d_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_GetDevice(IDirect3DTexture9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETDEVICE);
    call.iface = (uint64_t)texture;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetDevice *c = (struct qemu_d3d9_texture_2d_GetDevice *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetDevice(texture->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_texture_2d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_SetPrivateData(IDirect3DTexture9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_SetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_SETPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = data_size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_SetPrivateData *c = (struct qemu_d3d9_texture_2d_SetPrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    if (c->flags & D3DSPD_IUNKNOWN)
        WINE_FIXME("Implement an IUnknown wrapper or handle this on the guest side\n");

    c->super.iret = IDirect3DTexture9_SetPrivateData(texture->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d9_texture_2d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_GetPrivateData(IDirect3DTexture9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetPrivateData *c = (struct qemu_d3d9_texture_2d_GetPrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetPrivateData(texture->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_d3d9_texture_2d_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_FreePrivateData(IDirect3DTexture9 *iface, REFGUID guid)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_FreePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_FREEPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_FreePrivateData *c = (struct qemu_d3d9_texture_2d_FreePrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_FreePrivateData(texture->host, QEMU_G2H(c->guid));
}

#endif

struct qemu_d3d9_texture_2d_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_2d_SetPriority(IDirect3DTexture9 *iface, DWORD priority)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_SETPRIORITY);
    call.iface = (uint64_t)texture;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_SetPriority *c = (struct qemu_d3d9_texture_2d_SetPriority *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_SetPriority(texture->host, c->priority);
}

#endif

struct qemu_d3d9_texture_2d_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_2d_GetPriority(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETPRIORITY);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetPriority *c = (struct qemu_d3d9_texture_2d_GetPriority *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetPriority(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_texture_2d_PreLoad(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_PRELOAD);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_texture_2d_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_PreLoad *c = (struct qemu_d3d9_texture_2d_PreLoad *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    IDirect3DTexture9_PreLoad(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DRESOURCETYPE WINAPI d3d9_texture_2d_GetType(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETTYPE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetType *c = (struct qemu_d3d9_texture_2d_GetType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetType(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_SetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lod;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_2d_SetLOD(IDirect3DTexture9 *iface, DWORD lod)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_SetLOD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_SETLOD);
    call.iface = (uint64_t)texture;
    call.lod = (uint64_t)lod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_SetLOD(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_SetLOD *c = (struct qemu_d3d9_texture_2d_SetLOD *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_SetLOD(texture->host, c->lod);
}

#endif

struct qemu_d3d9_texture_2d_GetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_2d_GetLOD(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetLOD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETLOD);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetLOD(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetLOD *c = (struct qemu_d3d9_texture_2d_GetLOD *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetLOD(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_GetLevelCount
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_2d_GetLevelCount(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetLevelCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETLEVELCOUNT);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetLevelCount(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetLevelCount *c = (struct qemu_d3d9_texture_2d_GetLevelCount *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetLevelCount(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_SetAutoGenFilterType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t filter_type;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_SetAutoGenFilterType(IDirect3DTexture9 *iface, D3DTEXTUREFILTERTYPE filter_type)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_SetAutoGenFilterType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_SETAUTOGENFILTERTYPE);
    call.iface = (uint64_t)texture;
    call.filter_type = (uint64_t)filter_type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_SetAutoGenFilterType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_SetAutoGenFilterType *c = (struct qemu_d3d9_texture_2d_SetAutoGenFilterType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_SetAutoGenFilterType(texture->host, c->filter_type);
}

#endif

struct qemu_d3d9_texture_2d_GetAutoGenFilterType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DTEXTUREFILTERTYPE WINAPI d3d9_texture_2d_GetAutoGenFilterType(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetAutoGenFilterType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETAUTOGENFILTERTYPE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetAutoGenFilterType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetAutoGenFilterType *c = (struct qemu_d3d9_texture_2d_GetAutoGenFilterType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetAutoGenFilterType(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_GenerateMipSubLevels
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_texture_2d_GenerateMipSubLevels(IDirect3DTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GenerateMipSubLevels call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GENERATEMIPSUBLEVELS);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_texture_2d_GenerateMipSubLevels(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GenerateMipSubLevels *c = (struct qemu_d3d9_texture_2d_GenerateMipSubLevels *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    IDirect3DTexture9_GenerateMipSubLevels(texture->host);
}

#endif

struct qemu_d3d9_texture_2d_GetLevelDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_GetLevelDesc(IDirect3DTexture9 *iface, UINT level, D3DSURFACE_DESC *desc)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_GetLevelDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETLEVELDESC);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;
    call.desc = (uint64_t)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetLevelDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetLevelDesc *c = (struct qemu_d3d9_texture_2d_GetLevelDesc *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetLevelDesc((IDirect3DTexture9 *)texture->host, c->level, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d9_texture_2d_GetSurfaceLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_GetSurfaceLevel(IDirect3DTexture9 *iface, UINT level, IDirect3DSurface9 **surface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_subresource_impl *surface_impl;
    struct qemu_d3d9_texture_2d_GetSurfaceLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_GETSURFACELEVEL);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;
    call.surface = (uint64_t)&surface_impl;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
        *surface = &surface_impl->IDirect3DSurface9_iface;
    else
        *surface = NULL;

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_GetSurfaceLevel(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_GetSurfaceLevel *c = (struct qemu_d3d9_texture_2d_GetSurfaceLevel *)call;
    struct qemu_d3d9_texture_impl *texture;
    IDirect3DSurface9 *host;
    struct qemu_d3d9_subresource_impl *surface_impl;
    DWORD size = sizeof(surface_impl);

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_GetSurfaceLevel((IDirect3DTexture9 *)texture->host, c->level, &host);
    if (FAILED(c->super.iret))
        return;

    IDirect3DSurface9_GetPrivateData(host, &qemu_d3d9_surface_guid, &surface_impl, &size);
    WINE_TRACE("Got surface %p from private data from host surface %p.\n", surface_impl, host);
    *(uint64_t *)QEMU_G2H(c->surface) = QEMU_H2G(surface_impl);
}

#endif

struct qemu_d3d9_texture_2d_LockRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t locked_rect;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_LockRect(IDirect3DTexture9 *iface, UINT level, D3DLOCKED_RECT *locked_rect, const RECT *rect, DWORD flags)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_LockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_LOCKRECT);
    call.iface = (uint64_t)texture;
    call.level = level;
    call.locked_rect = (uint64_t)locked_rect;
    call.rect = (uint64_t)rect;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_LockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_LockRect *c = (struct qemu_d3d9_texture_2d_LockRect *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_LockRect((IDirect3DTexture9 *)texture->host, c->level, QEMU_G2H(c->locked_rect), QEMU_G2H(c->rect), c->flags);
}

#endif

struct qemu_d3d9_texture_2d_UnlockRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_UnlockRect(IDirect3DTexture9 *iface, UINT level)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_UnlockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_UNLOCKRECT);
    call.iface = (uint64_t)texture;
    call.level = level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_UnlockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_UnlockRect *c = (struct qemu_d3d9_texture_2d_UnlockRect *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_TRACE("\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_UnlockRect((IDirect3DTexture9 *)texture->host, c->level);
}

#endif

struct qemu_d3d9_texture_2d_AddDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dirty_rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_2d_AddDirtyRect(IDirect3DTexture9 *iface, const RECT *dirty_rect)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DTexture9(iface);
    struct qemu_d3d9_texture_2d_AddDirtyRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_2D_ADDDIRTYRECT);
    call.iface = (uint64_t)texture;
    call.dirty_rect = (uint64_t)dirty_rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_2d_AddDirtyRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_2d_AddDirtyRect *c = (struct qemu_d3d9_texture_2d_AddDirtyRect *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DTexture9_AddDirtyRect((IDirect3DTexture9 *)texture->host, QEMU_G2H(c->dirty_rect));
}

#endif

struct qemu_d3d9_texture_cube_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_texture_impl *impl_from_IDirect3DCubeTexture9(IDirect3DCubeTexture9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_texture_impl, IDirect3DBaseTexture9_iface);
}

static HRESULT WINAPI d3d9_texture_cube_QueryInterface(IDirect3DCubeTexture9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_QUERYINTERFACE);
    call.iface = (uint64_t)texture;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_QueryInterface *c = (struct qemu_d3d9_texture_cube_QueryInterface *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_QueryInterface(texture->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_texture_cube_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_texture_cube_AddRef(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_ADDREF);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_AddRef *c = (struct qemu_d3d9_texture_cube_AddRef *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_AddRef(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_texture_cube_Release(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_RELEASE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_Release *c = (struct qemu_d3d9_texture_cube_Release *)call;
    struct qemu_d3d9_texture_impl *texture;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);
    device = texture->device;

    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DCubeTexture9_Release(texture->host);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_texture_cube_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_GetDevice(IDirect3DCubeTexture9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETDEVICE);
    call.iface = (uint64_t)texture;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetDevice *c = (struct qemu_d3d9_texture_cube_GetDevice *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetDevice(texture->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_texture_cube_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_SetPrivateData(IDirect3DCubeTexture9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_SetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_SETPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_SetPrivateData *c = (struct qemu_d3d9_texture_cube_SetPrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_SetPrivateData(texture->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d9_texture_cube_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_GetPrivateData(IDirect3DCubeTexture9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetPrivateData *c = (struct qemu_d3d9_texture_cube_GetPrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetPrivateData(texture->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_d3d9_texture_cube_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_FreePrivateData(IDirect3DCubeTexture9 *iface, REFGUID guid)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_FreePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_FREEPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_FreePrivateData *c = (struct qemu_d3d9_texture_cube_FreePrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_FreePrivateData(texture->host, QEMU_G2H(c->guid));
}

#endif

struct qemu_d3d9_texture_cube_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_cube_SetPriority(IDirect3DCubeTexture9 *iface, DWORD priority)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_SETPRIORITY);
    call.iface = (uint64_t)texture;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_SetPriority *c = (struct qemu_d3d9_texture_cube_SetPriority *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_SetPriority(texture->host, c->priority);
}

#endif

struct qemu_d3d9_texture_cube_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_cube_GetPriority(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETPRIORITY);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetPriority *c = (struct qemu_d3d9_texture_cube_GetPriority *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetPriority(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_texture_cube_PreLoad(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_PRELOAD);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_texture_cube_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_PreLoad *c = (struct qemu_d3d9_texture_cube_PreLoad *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    IDirect3DTexture9_PreLoad(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DRESOURCETYPE WINAPI d3d9_texture_cube_GetType(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETTYPE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetType *c = (struct qemu_d3d9_texture_cube_GetType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetType(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_SetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lod;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_cube_SetLOD(IDirect3DCubeTexture9 *iface, DWORD lod)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_SetLOD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_SETLOD);
    call.iface = (uint64_t)texture;
    call.lod = (uint64_t)lod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_SetLOD(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_SetLOD *c = (struct qemu_d3d9_texture_cube_SetLOD *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_SetLOD(texture->host, c->lod);
}

#endif

struct qemu_d3d9_texture_cube_GetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_cube_GetLOD(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetLOD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETLOD);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetLOD(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetLOD *c = (struct qemu_d3d9_texture_cube_GetLOD *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetLOD(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_GetLevelCount
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_cube_GetLevelCount(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetLevelCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETLEVELCOUNT);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetLevelCount(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetLevelCount *c = (struct qemu_d3d9_texture_cube_GetLevelCount *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetLevelCount(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_SetAutoGenFilterType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t filter_type;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_SetAutoGenFilterType(IDirect3DCubeTexture9 *iface, D3DTEXTUREFILTERTYPE filter_type)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_SetAutoGenFilterType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_SETAUTOGENFILTERTYPE);
    call.iface = (uint64_t)texture;
    call.filter_type = (uint64_t)filter_type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_SetAutoGenFilterType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_SetAutoGenFilterType *c = (struct qemu_d3d9_texture_cube_SetAutoGenFilterType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_SetAutoGenFilterType(texture->host, c->filter_type);
}

#endif

struct qemu_d3d9_texture_cube_GetAutoGenFilterType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DTEXTUREFILTERTYPE WINAPI d3d9_texture_cube_GetAutoGenFilterType(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetAutoGenFilterType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETAUTOGENFILTERTYPE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetAutoGenFilterType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetAutoGenFilterType *c = (struct qemu_d3d9_texture_cube_GetAutoGenFilterType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetAutoGenFilterType(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_GenerateMipSubLevels
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_texture_cube_GenerateMipSubLevels(IDirect3DCubeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GenerateMipSubLevels call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GENERATEMIPSUBLEVELS);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_texture_cube_GenerateMipSubLevels(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GenerateMipSubLevels *c = (struct qemu_d3d9_texture_cube_GenerateMipSubLevels *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    IDirect3DCubeTexture9_GenerateMipSubLevels(texture->host);
}

#endif

struct qemu_d3d9_texture_cube_GetLevelDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_GetLevelDesc(IDirect3DCubeTexture9 *iface, UINT level, D3DSURFACE_DESC *desc)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetLevelDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETLEVELDESC);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;
    call.desc = (uint64_t)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetLevelDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetLevelDesc *c = (struct qemu_d3d9_texture_cube_GetLevelDesc *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetLevelDesc((IDirect3DCubeTexture9 *)texture->host, c->level, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d9_texture_cube_GetCubeMapSurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t face;
    uint64_t level;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_GetCubeMapSurface(IDirect3DCubeTexture9 *iface, D3DCUBEMAP_FACES face, UINT level, IDirect3DSurface9 **surface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_GetCubeMapSurface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_GETCUBEMAPSURFACE);
    call.iface = (uint64_t)texture;
    call.face = (uint64_t)face;
    call.level = (uint64_t)level;
    call.surface = (uint64_t)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_GetCubeMapSurface(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_GetCubeMapSurface *c = (struct qemu_d3d9_texture_cube_GetCubeMapSurface *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_GetCubeMapSurface((IDirect3DCubeTexture9 *)texture->host, c->face, c->level, QEMU_G2H(c->surface));
}

#endif

struct qemu_d3d9_texture_cube_LockRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t face;
    uint64_t level;
    uint64_t locked_rect;
    uint64_t rect;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_LockRect(IDirect3DCubeTexture9 *iface, D3DCUBEMAP_FACES face, UINT level, D3DLOCKED_RECT *locked_rect, const RECT *rect, DWORD flags)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_LockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_LOCKRECT);
    call.iface = (uint64_t)texture;
    call.face = (uint64_t)face;
    call.level = (uint64_t)level;
    call.locked_rect = (uint64_t)locked_rect;
    call.rect = (uint64_t)rect;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_LockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_LockRect *c = (struct qemu_d3d9_texture_cube_LockRect *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_LockRect((IDirect3DCubeTexture9 *)texture->host, c->face, c->level, QEMU_G2H(c->locked_rect), QEMU_G2H(c->rect), c->flags);
}

#endif

struct qemu_d3d9_texture_cube_UnlockRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t face;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_UnlockRect(IDirect3DCubeTexture9 *iface, D3DCUBEMAP_FACES face, UINT level)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_UnlockRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_UNLOCKRECT);
    call.iface = (uint64_t)texture;
    call.face = (uint64_t)face;
    call.level = (uint64_t)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_UnlockRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_UnlockRect *c = (struct qemu_d3d9_texture_cube_UnlockRect *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_UnlockRect((IDirect3DCubeTexture9 *)texture->host, c->face, c->level);
}

#endif

struct qemu_d3d9_texture_cube_AddDirtyRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t face;
    uint64_t dirty_rect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_cube_AddDirtyRect(IDirect3DCubeTexture9 *iface, D3DCUBEMAP_FACES face, const RECT *dirty_rect)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DCubeTexture9(iface);
    struct qemu_d3d9_texture_cube_AddDirtyRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_CUBE_ADDDIRTYRECT);
    call.iface = (uint64_t)texture;
    call.face = (uint64_t)face;
    call.dirty_rect = (uint64_t)dirty_rect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_cube_AddDirtyRect(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_cube_AddDirtyRect *c = (struct qemu_d3d9_texture_cube_AddDirtyRect *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DCubeTexture9_AddDirtyRect((IDirect3DCubeTexture9 *)texture->host, c->face, QEMU_G2H(c->dirty_rect));
}

#endif

struct qemu_d3d9_texture_3d_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d9_texture_impl *impl_from_IDirect3DVolumeTexture9(IDirect3DVolumeTexture9 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_texture_impl, IDirect3DBaseTexture9_iface);
}

static HRESULT WINAPI d3d9_texture_3d_QueryInterface(IDirect3DVolumeTexture9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_QUERYINTERFACE);
    call.iface = (uint64_t)texture;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_QueryInterface *c = (struct qemu_d3d9_texture_3d_QueryInterface *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_QueryInterface(texture->host, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_texture_3d_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_texture_3d_AddRef(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_ADDREF);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_AddRef *c = (struct qemu_d3d9_texture_3d_AddRef *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_AddRef(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_texture_3d_Release(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_RELEASE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_Release *c = (struct qemu_d3d9_texture_3d_Release *)call;
    struct qemu_d3d9_texture_impl *texture;
    struct qemu_d3d9_device_impl *device;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);
    device = texture->device;

    d3d9_device_wrapper_addref(device);
    c->super.iret = IDirect3DVolumeTexture9_Release(texture->host);
    d3d9_device_wrapper_release(device);
}

#endif

struct qemu_d3d9_texture_3d_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_GetDevice(IDirect3DVolumeTexture9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetDevice call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETDEVICE);
    call.iface = (uint64_t)texture;
    call.device = (uint64_t)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetDevice *c = (struct qemu_d3d9_texture_3d_GetDevice *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetDevice(texture->host, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d9_texture_3d_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_SetPrivateData(IDirect3DVolumeTexture9 *iface, REFGUID guid, const void *data, DWORD data_size, DWORD flags)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_SetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_SETPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_SetPrivateData *c = (struct qemu_d3d9_texture_3d_SetPrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_SetPrivateData(texture->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), c->data_size, c->flags);
}

#endif

struct qemu_d3d9_texture_3d_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_GetPrivateData(IDirect3DVolumeTexture9 *iface, REFGUID guid, void *data, DWORD *data_size)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetPrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetPrivateData *c = (struct qemu_d3d9_texture_3d_GetPrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetPrivateData(texture->host, QEMU_G2H(c->guid), QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_d3d9_texture_3d_FreePrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_FreePrivateData(IDirect3DVolumeTexture9 *iface, REFGUID guid)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_FreePrivateData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_FREEPRIVATEDATA);
    call.iface = (uint64_t)texture;
    call.guid = (uint64_t)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_FreePrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_FreePrivateData *c = (struct qemu_d3d9_texture_3d_FreePrivateData *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_FreePrivateData(texture->host, QEMU_G2H(c->guid));
}

#endif

struct qemu_d3d9_texture_3d_SetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_3d_SetPriority(IDirect3DVolumeTexture9 *iface, DWORD priority)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_SetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_SETPRIORITY);
    call.iface = (uint64_t)texture;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_SetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_SetPriority *c = (struct qemu_d3d9_texture_3d_SetPriority *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_SetPriority(texture->host, c->priority);
}

#endif

struct qemu_d3d9_texture_3d_GetPriority
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_3d_GetPriority(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETPRIORITY);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetPriority(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetPriority *c = (struct qemu_d3d9_texture_3d_GetPriority *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetPriority(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_PreLoad
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_texture_3d_PreLoad(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_PreLoad call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_PRELOAD);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_texture_3d_PreLoad(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_PreLoad *c = (struct qemu_d3d9_texture_3d_PreLoad *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    IDirect3DTexture9_PreLoad(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DRESOURCETYPE WINAPI d3d9_texture_3d_GetType(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETTYPE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetType *c = (struct qemu_d3d9_texture_3d_GetType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetType(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_SetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lod;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_3d_SetLOD(IDirect3DVolumeTexture9 *iface, DWORD lod)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_SetLOD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_SETLOD);
    call.iface = (uint64_t)texture;
    call.lod = (uint64_t)lod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_SetLOD(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_SetLOD *c = (struct qemu_d3d9_texture_3d_SetLOD *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_SetLOD(texture->host, c->lod);
}

#endif

struct qemu_d3d9_texture_3d_GetLOD
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_3d_GetLOD(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetLOD call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETLOD);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetLOD(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetLOD *c = (struct qemu_d3d9_texture_3d_GetLOD *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetLOD(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_GetLevelCount
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static DWORD WINAPI d3d9_texture_3d_GetLevelCount(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetLevelCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETLEVELCOUNT);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetLevelCount(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetLevelCount *c = (struct qemu_d3d9_texture_3d_GetLevelCount *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetLevelCount(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_SetAutoGenFilterType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t filter_type;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_SetAutoGenFilterType(IDirect3DVolumeTexture9 *iface, D3DTEXTUREFILTERTYPE filter_type)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_SetAutoGenFilterType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_SETAUTOGENFILTERTYPE);
    call.iface = (uint64_t)texture;
    call.filter_type = (uint64_t)filter_type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_SetAutoGenFilterType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_SetAutoGenFilterType *c = (struct qemu_d3d9_texture_3d_SetAutoGenFilterType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_SetAutoGenFilterType(texture->host, c->filter_type);
}

#endif

struct qemu_d3d9_texture_3d_GetAutoGenFilterType
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static D3DTEXTUREFILTERTYPE WINAPI d3d9_texture_3d_GetAutoGenFilterType(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetAutoGenFilterType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETAUTOGENFILTERTYPE);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetAutoGenFilterType(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetAutoGenFilterType *c = (struct qemu_d3d9_texture_3d_GetAutoGenFilterType *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetAutoGenFilterType(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_GenerateMipSubLevels
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI d3d9_texture_3d_GenerateMipSubLevels(IDirect3DVolumeTexture9 *iface)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GenerateMipSubLevels call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GENERATEMIPSUBLEVELS);
    call.iface = (uint64_t)texture;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d9_texture_3d_GenerateMipSubLevels(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GenerateMipSubLevels *c = (struct qemu_d3d9_texture_3d_GenerateMipSubLevels *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    IDirect3DVolumeTexture9_GenerateMipSubLevels(texture->host);
}

#endif

struct qemu_d3d9_texture_3d_GetLevelDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_GetLevelDesc(IDirect3DVolumeTexture9 *iface, UINT level, D3DVOLUME_DESC *desc)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetLevelDesc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETLEVELDESC);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;
    call.desc = (uint64_t)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetLevelDesc(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetLevelDesc *c = (struct qemu_d3d9_texture_3d_GetLevelDesc *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetLevelDesc((IDirect3DVolumeTexture9 *)texture->host, c->level, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d9_texture_3d_GetVolumeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t volume;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_GetVolumeLevel(IDirect3DVolumeTexture9 *iface, UINT level, IDirect3DVolume9 **volume)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_GetVolumeLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_GETVOLUMELEVEL);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;
    call.volume = (uint64_t)volume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_GetVolumeLevel(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_GetVolumeLevel *c = (struct qemu_d3d9_texture_3d_GetVolumeLevel *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_GetVolumeLevel((IDirect3DVolumeTexture9 *)texture->host, c->level, QEMU_G2H(c->volume));
}

#endif

struct qemu_d3d9_texture_3d_LockBox
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
    uint64_t locked_box;
    uint64_t box;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_LockBox(IDirect3DVolumeTexture9 *iface, UINT level, D3DLOCKED_BOX *locked_box, const D3DBOX *box, DWORD flags)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_LockBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_LOCKBOX);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;
    call.locked_box = (uint64_t)locked_box;
    call.box = (uint64_t)box;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_LockBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_LockBox *c = (struct qemu_d3d9_texture_3d_LockBox *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_LockBox((IDirect3DVolumeTexture9 *)texture->host, c->level, QEMU_G2H(c->locked_box), QEMU_G2H(c->box), c->flags);
}

#endif

struct qemu_d3d9_texture_3d_UnlockBox
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t level;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_UnlockBox(IDirect3DVolumeTexture9 *iface, UINT level)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_UnlockBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_UNLOCKBOX);
    call.iface = (uint64_t)texture;
    call.level = (uint64_t)level;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_UnlockBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_UnlockBox *c = (struct qemu_d3d9_texture_3d_UnlockBox *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_UnlockBox((IDirect3DVolumeTexture9 *)texture->host, c->level);
}

#endif

struct qemu_d3d9_texture_3d_AddDirtyBox
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dirty_box;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_texture_3d_AddDirtyBox(IDirect3DVolumeTexture9 *iface, const D3DBOX *dirty_box)
{
    struct qemu_d3d9_texture_impl *texture = impl_from_IDirect3DVolumeTexture9(iface);
    struct qemu_d3d9_texture_3d_AddDirtyBox call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_TEXTURE_3D_ADDDIRTYBOX);
    call.iface = (uint64_t)texture;
    call.dirty_box = (uint64_t)dirty_box;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_texture_3d_AddDirtyBox(struct qemu_syscall *call)
{
    struct qemu_d3d9_texture_3d_AddDirtyBox *c = (struct qemu_d3d9_texture_3d_AddDirtyBox *)call;
    struct qemu_d3d9_texture_impl *texture;

    WINE_FIXME("Unverified!\n");
    texture = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVolumeTexture9_AddDirtyBox((IDirect3DVolumeTexture9 *)texture->host, QEMU_G2H(c->dirty_box));
}

#endif

#ifdef QEMU_DLL_GUEST

const IDirect3DTexture9Vtbl d3d9_texture_2d_vtbl =
{
    /* IUnknown */
    d3d9_texture_2d_QueryInterface,
    d3d9_texture_2d_AddRef,
    d3d9_texture_2d_Release,
     /* IDirect3DResource9 */
    d3d9_texture_2d_GetDevice,
    d3d9_texture_2d_SetPrivateData,
    d3d9_texture_2d_GetPrivateData,
    d3d9_texture_2d_FreePrivateData,
    d3d9_texture_2d_SetPriority,
    d3d9_texture_2d_GetPriority,
    d3d9_texture_2d_PreLoad,
    d3d9_texture_2d_GetType,
    /* IDirect3DBaseTexture9 */
    d3d9_texture_2d_SetLOD,
    d3d9_texture_2d_GetLOD,
    d3d9_texture_2d_GetLevelCount,
    d3d9_texture_2d_SetAutoGenFilterType,
    d3d9_texture_2d_GetAutoGenFilterType,
    d3d9_texture_2d_GenerateMipSubLevels,
    /* IDirect3DTexture9 */
    d3d9_texture_2d_GetLevelDesc,
    d3d9_texture_2d_GetSurfaceLevel,
    d3d9_texture_2d_LockRect,
    d3d9_texture_2d_UnlockRect,
    d3d9_texture_2d_AddDirtyRect,
};

const IDirect3DCubeTexture9Vtbl d3d9_texture_cube_vtbl =
{
    /* IUnknown */
    d3d9_texture_cube_QueryInterface,
    d3d9_texture_cube_AddRef,
    d3d9_texture_cube_Release,
    /* IDirect3DResource9 */
    d3d9_texture_cube_GetDevice,
    d3d9_texture_cube_SetPrivateData,
    d3d9_texture_cube_GetPrivateData,
    d3d9_texture_cube_FreePrivateData,
    d3d9_texture_cube_SetPriority,
    d3d9_texture_cube_GetPriority,
    d3d9_texture_cube_PreLoad,
    d3d9_texture_cube_GetType,
    /* IDirect3DBaseTexture9 */
    d3d9_texture_cube_SetLOD,
    d3d9_texture_cube_GetLOD,
    d3d9_texture_cube_GetLevelCount,
    d3d9_texture_cube_SetAutoGenFilterType,
    d3d9_texture_cube_GetAutoGenFilterType,
    d3d9_texture_cube_GenerateMipSubLevels,
    /* IDirect3DCubeTexture9 */
    d3d9_texture_cube_GetLevelDesc,
    d3d9_texture_cube_GetCubeMapSurface,
    d3d9_texture_cube_LockRect,
    d3d9_texture_cube_UnlockRect,
    d3d9_texture_cube_AddDirtyRect,
};

const IDirect3DVolumeTexture9Vtbl d3d9_texture_3d_vtbl =
{
    /* IUnknown */
    d3d9_texture_3d_QueryInterface,
    d3d9_texture_3d_AddRef,
    d3d9_texture_3d_Release,
    /* IDirect3DResource9 */
    d3d9_texture_3d_GetDevice,
    d3d9_texture_3d_SetPrivateData,
    d3d9_texture_3d_GetPrivateData,
    d3d9_texture_3d_FreePrivateData,
    d3d9_texture_3d_SetPriority,
    d3d9_texture_3d_GetPriority,
    d3d9_texture_3d_PreLoad,
    d3d9_texture_3d_GetType,
    /* IDirect3DBaseTexture9 */
    d3d9_texture_3d_SetLOD,
    d3d9_texture_3d_GetLOD,
    d3d9_texture_3d_GetLevelCount,
    d3d9_texture_3d_SetAutoGenFilterType,
    d3d9_texture_3d_GetAutoGenFilterType,
    d3d9_texture_3d_GenerateMipSubLevels,
    /* IDirect3DVolumeTexture9 */
    d3d9_texture_3d_GetLevelDesc,
    d3d9_texture_3d_GetVolumeLevel,
    d3d9_texture_3d_LockBox,
    d3d9_texture_3d_UnlockBox,
    d3d9_texture_3d_AddDirtyBox,
};

void d3d9_texture_set_surfaces_ifaces(IDirect3DBaseTexture9 *texture)
{
    IDirect3DSurface9 *surface;
    DWORD i, level_count = IDirect3DBaseTexture9_GetLevelCount(texture);

    /* This code merrily relies on the fact that the GetSurfaceLevel AddRef call
     * happens on the host side and doesn't need the guest vtable. */
    switch (IDirect3DBaseTexture9_GetType(texture))
    {
        case D3DRTYPE_TEXTURE:
            for (i = 0; i < level_count; ++i)
            {
                IDirect3DTexture9_GetSurfaceLevel((IDirect3DTexture9 *)texture, i, &surface);
                surface->lpVtbl = &d3d9_surface_vtbl;
                IDirect3DSurface9_Release(surface);
            }
    }
}

#else

struct qemu_d3d9_texture_impl *texture_impl_from_IUnknown(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d9_texture_impl, private_data);
}

static HRESULT WINAPI d3d9_texture_priv_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d9_texture_priv_AddRef(IUnknown *iface)
{
    struct qemu_d3d9_texture_impl *texture = texture_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedIncrement(&texture->private_data_ref);

    WINE_TRACE("%p increasing refcount to %u.\n", texture, refcount);
    return refcount;
}

static ULONG WINAPI d3d9_texture_priv_Release(IUnknown *iface)
{
    struct qemu_d3d9_texture_impl *texture = texture_impl_from_IUnknown(iface);
    ULONG refcount = InterlockedDecrement(&texture->private_data_ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", texture, refcount);
    if (!refcount)
    {
        /* This means the private data has been released, which only happens
         * when the real interface has been destroyed. */
        HeapFree(GetProcessHeap(), 0, texture);
    }

    return refcount;
}

static const struct IUnknownVtbl texture_priv_vtbl =
{
    /* IUnknown */
    d3d9_texture_priv_QueryInterface,
    d3d9_texture_priv_AddRef,
    d3d9_texture_priv_Release,
};

void d3d9_texture_init(struct qemu_d3d9_texture_impl *texture, IDirect3DBaseTexture9 *host, struct qemu_d3d9_device_impl *device)
{
    DWORD i, level_count;
    IDirect3DSurface9 *surface;
    D3DRESOURCETYPE rtype;

    texture->private_data.lpVtbl = &texture_priv_vtbl;
    texture->private_data_ref = 0;
    texture->host = host;
    texture->device = device;
    IDirect3DTexture9_SetPrivateData(host, &qemu_d3d9_texture_guid, &texture->private_data,
            sizeof(IUnknown *), D3DSPD_IUNKNOWN);

    switch (IDirect3DBaseTexture9_GetType(host))
    {
        case D3DRTYPE_TEXTURE:
            level_count = IDirect3DTexture9_GetLevelCount((IDirect3DTexture9 *)host);
            for (i = 0; i < level_count; ++i)
            {
                IDirect3DTexture9_GetSurfaceLevel((IDirect3DTexture9 *)host, i, &surface);
                d3d9_surface_init(&texture->subs[i], surface, device);
                IDirect3DSurface9_Release(surface);
            }
    }
}

#endif
