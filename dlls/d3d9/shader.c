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


struct qemu_d3d9_vertexshader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexshader_QueryInterface(IDirect3DVertexShader9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DVertexShader9(iface);
    struct qemu_d3d9_vertexshader_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXSHADER_QUERYINTERFACE);
    call.iface = (uint64_t)shader;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexshader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexshader_QueryInterface *c = (struct qemu_d3d9_vertexshader_QueryInterface *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexShader9_QueryInterface(shader->hostvs, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_vertexshader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_vertexshader_AddRef(IDirect3DVertexShader9 *iface)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DVertexShader9(iface);
    struct qemu_d3d9_vertexshader_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXSHADER_ADDREF);
    call.iface = (uint64_t)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexshader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexshader_AddRef *c = (struct qemu_d3d9_vertexshader_AddRef *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexShader9_AddRef(shader->hostvs);
}

#endif

struct qemu_d3d9_vertexshader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_vertexshader_Release(IDirect3DVertexShader9 *iface)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DVertexShader9(iface);
    struct qemu_d3d9_vertexshader_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXSHADER_RELEASE);
    call.iface = (uint64_t)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexshader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexshader_Release *c = (struct qemu_d3d9_vertexshader_Release *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    d3d9_device_wrapper_addref(shader->device);
    c->super.iret = IDirect3DVertexShader9_Release(shader->hostvs);
    d3d9_device_wrapper_release(shader->device);

    if (!c->super.iret)
        HeapFree(GetProcessHeap(), 0, shader);
}

#endif

struct qemu_d3d9_vertexshader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexshader_GetDevice(IDirect3DVertexShader9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DVertexShader9(iface);
    struct qemu_d3d9_vertexshader_GetDevice call;
    struct qemu_d3d9_device_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXSHADER_GETDEVICE);
    call.iface = (uint64_t)shader;
    call.device = (uint64_t)&impl;

    qemu_syscall(&call.super);
    *device = (IDirect3DDevice9 *)&impl->IDirect3DDevice9Ex_iface;

    return call.super.iret;
}

#else

void qemu_d3d9_vertexshader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexshader_GetDevice *c = (struct qemu_d3d9_vertexshader_GetDevice *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = D3D_OK;
    d3d9_device_wrapper_addref(shader->device);
    *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(shader->device);
}

#endif

struct qemu_d3d9_vertexshader_GetFunction
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_vertexshader_GetFunction(IDirect3DVertexShader9 *iface, void *data, UINT *data_size)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DVertexShader9(iface);
    struct qemu_d3d9_vertexshader_GetFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_VERTEXSHADER_GETFUNCTION);
    call.iface = (uint64_t)shader;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_vertexshader_GetFunction(struct qemu_syscall *call)
{
    struct qemu_d3d9_vertexshader_GetFunction *c = (struct qemu_d3d9_vertexshader_GetFunction *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DVertexShader9_GetFunction(shader->hostvs, QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

struct qemu_d3d9_pixelshader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_pixelshader_QueryInterface(IDirect3DPixelShader9 *iface, REFIID riid, void **out)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DPixelShader9(iface);
    struct qemu_d3d9_pixelshader_QueryInterface call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_PIXELSHADER_QUERYINTERFACE);
    call.iface = (uint64_t)shader;
    call.riid = (uint64_t)riid;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_pixelshader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d9_pixelshader_QueryInterface *c = (struct qemu_d3d9_pixelshader_QueryInterface *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DPixelShader9_QueryInterface(shader->hostps, QEMU_G2H(c->riid), QEMU_G2H(c->out));
}

#endif

struct qemu_d3d9_pixelshader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_pixelshader_AddRef(IDirect3DPixelShader9 *iface)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DPixelShader9(iface);
    struct qemu_d3d9_pixelshader_AddRef call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_PIXELSHADER_ADDREF);
    call.iface = (uint64_t)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_pixelshader_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d9_pixelshader_AddRef *c = (struct qemu_d3d9_pixelshader_AddRef *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DPixelShader9_AddRef(shader->hostps);
}

#endif

struct qemu_d3d9_pixelshader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI d3d9_pixelshader_Release(IDirect3DPixelShader9 *iface)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DPixelShader9(iface);
    struct qemu_d3d9_pixelshader_Release call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_PIXELSHADER_RELEASE);
    call.iface = (uint64_t)shader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_pixelshader_Release(struct qemu_syscall *call)
{
    struct qemu_d3d9_pixelshader_Release *c = (struct qemu_d3d9_pixelshader_Release *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    d3d9_device_wrapper_addref(shader->device);
    c->super.iret = IDirect3DPixelShader9_Release(shader->hostps);
    d3d9_device_wrapper_release(shader->device);

    if (!c->super.iret)
        HeapFree(GetProcessHeap(), 0, shader);
}

#endif

struct qemu_d3d9_pixelshader_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_pixelshader_GetDevice(IDirect3DPixelShader9 *iface, IDirect3DDevice9 **device)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DPixelShader9(iface);
    struct qemu_d3d9_pixelshader_GetDevice call;
    struct qemu_d3d9_device_impl *impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_PIXELSHADER_GETDEVICE);
    call.iface = (uint64_t)shader;
    call.device = (uint64_t)&impl;

    qemu_syscall(&call.super);
    *device = (IDirect3DDevice9 *)&impl->IDirect3DDevice9Ex_iface;

    return call.super.iret;

}

#else

void qemu_d3d9_pixelshader_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d9_pixelshader_GetDevice *c = (struct qemu_d3d9_pixelshader_GetDevice *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_TRACE("\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = D3D_OK;
    d3d9_device_wrapper_addref(shader->device);
    *(uint64_t *)QEMU_G2H(c->device) = QEMU_H2G(shader->device);
}

#endif

struct qemu_d3d9_pixelshader_GetFunction
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d9_pixelshader_GetFunction(IDirect3DPixelShader9 *iface, void *data, UINT *data_size)
{
    struct qemu_d3d9_shader_impl *shader = impl_from_IDirect3DPixelShader9(iface);
    struct qemu_d3d9_pixelshader_GetFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D9_PIXELSHADER_GETFUNCTION);
    call.iface = (uint64_t)shader;
    call.data = (uint64_t)data;
    call.data_size = (uint64_t)data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d9_pixelshader_GetFunction(struct qemu_syscall *call)
{
    struct qemu_d3d9_pixelshader_GetFunction *c = (struct qemu_d3d9_pixelshader_GetFunction *)call;
    struct qemu_d3d9_shader_impl *shader;

    WINE_FIXME("Unverified!\n");
    shader = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DPixelShader9_GetFunction(shader->hostps, QEMU_G2H(c->data), QEMU_G2H(c->data_size));
}

#endif

#ifdef QEMU_DLL_GUEST

const IDirect3DVertexShader9Vtbl d3d9_vertexshader_vtbl =
{
    /* IUnknown */
    d3d9_vertexshader_QueryInterface,
    d3d9_vertexshader_AddRef,
    d3d9_vertexshader_Release,
    /* IDirect3DVertexShader9 */
    d3d9_vertexshader_GetDevice,
    d3d9_vertexshader_GetFunction,
};

const IDirect3DPixelShader9Vtbl d3d9_pixelshader_vtbl =
{
    /* IUnknown */
    d3d9_pixelshader_QueryInterface,
    d3d9_pixelshader_AddRef,
    d3d9_pixelshader_Release,
    /* IDirect3DPixelShader9 */
    d3d9_pixelshader_GetDevice,
    d3d9_pixelshader_GetFunction,
};

#else


#endif
