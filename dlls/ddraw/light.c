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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_d3d_light_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_light *impl_from_IDirect3DLight(IDirect3DLight *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_light, IDirect3DLight_iface);
}

static HRESULT WINAPI d3d_light_QueryInterface(IDirect3DLight *iface, REFIID riid, void **object)
{
    WINE_FIXME("iface %p, riid %s, object %p stub!\n", iface, wine_dbgstr_guid(riid), object);

    *object = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d_light_AddRef(IDirect3DLight *iface)
{
    struct qemu_light *light = impl_from_IDirect3DLight(iface);
    ULONG ref = InterlockedIncrement(&light->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", light, ref);

    return ref;
}

static ULONG WINAPI d3d_light_Release(IDirect3DLight *iface)
{
    struct qemu_d3d_light_Release call;
    struct qemu_light *light = impl_from_IDirect3DLight(iface);
    ULONG ref = InterlockedDecrement(&light->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", light, ref);

    if (!ref)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_D3D_LIGHT_RELEASE);
        call.iface = (ULONG_PTR)light;
        qemu_syscall(&call.super);
    }
    return ref;
}

#else

void qemu_d3d_light_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_light_Release *c = (struct qemu_d3d_light_Release *)call;
    struct qemu_light *light;

    WINE_TRACE("\n");
    light = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DLight_Release(light->host);

    if (c->super.iret)
        WINE_ERR("Unexpected light refcount %lu.\n", c->super.iret);

    HeapFree(GetProcessHeap(), 0, light);
}

#endif

struct qemu_d3d_light_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t d3d;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_light_Initialize(IDirect3DLight *iface, IDirect3D *d3d)
{
    struct qemu_d3d_light_Initialize call;
    struct qemu_light *light = impl_from_IDirect3DLight(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_LIGHT_INITIALIZE);
    call.iface = (ULONG_PTR)light;
    call.d3d = (ULONG_PTR)d3d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_light_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d_light_Initialize *c = (struct qemu_d3d_light_Initialize *)call;
    struct qemu_light *light;

    WINE_FIXME("Unverified!\n");
    light = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DLight_Initialize(light->host, QEMU_G2H(c->d3d));
}

#endif

struct qemu_d3d_light_SetLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_light_SetLight(IDirect3DLight *iface, D3DLIGHT *data)
{
    struct qemu_d3d_light_SetLight call;
    struct qemu_light *light = impl_from_IDirect3DLight(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_LIGHT_SETLIGHT);
    call.iface = (ULONG_PTR)light;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_light_SetLight(struct qemu_syscall *call)
{
    struct qemu_d3d_light_SetLight *c = (struct qemu_d3d_light_SetLight *)call;
    struct qemu_light *light;

    WINE_TRACE("\n");
    light = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DLight_SetLight(light->host, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d_light_GetLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpLight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_light_GetLight(IDirect3DLight *iface, D3DLIGHT *lpLight)
{
    struct qemu_d3d_light_GetLight call;
    struct qemu_light *light = impl_from_IDirect3DLight(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_LIGHT_GETLIGHT);
    call.iface = (ULONG_PTR)light;
    call.lpLight = (ULONG_PTR)lpLight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_light_GetLight(struct qemu_syscall *call)
{
    struct qemu_d3d_light_GetLight *c = (struct qemu_d3d_light_GetLight *)call;
    struct qemu_light *light;

    WINE_TRACE("\n");
    light = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DLight_GetLight(light->host, QEMU_G2H(c->lpLight));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DLightVtbl d3d_light_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_light_QueryInterface,
    d3d_light_AddRef,
    d3d_light_Release,
    /*** IDirect3DLight Methods ***/
    d3d_light_Initialize,
    d3d_light_SetLight,
    d3d_light_GetLight
};

void d3d_light_guest_init(struct qemu_light *light)
{
    light->IDirect3DLight_iface.lpVtbl = &d3d_light_vtbl;
    light->ref = 1;
}

struct qemu_light *unsafe_impl_from_IDirect3DLight(IDirect3DLight *iface)
{
    if (!iface)
        return NULL;
    if (iface->lpVtbl != &d3d_light_vtbl)
        WINE_ERR("Invalid IDirect3DLight vtable.\n");

    return impl_from_IDirect3DLight(iface);
}

#endif
