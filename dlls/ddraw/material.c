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

struct qemu_d3d_material_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_material *impl_from_IDirect3DMaterial(IDirect3DMaterial *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_material, IDirect3DMaterial_iface);
}

static inline struct qemu_material *impl_from_IDirect3DMaterial2(IDirect3DMaterial2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_material, IDirect3DMaterial2_iface);
}

static inline struct qemu_material *impl_from_IDirect3DMaterial3(IDirect3DMaterial3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_material, IDirect3DMaterial3_iface);
}

static HRESULT WINAPI d3d_material3_QueryInterface(IDirect3DMaterial3 *iface, REFIID riid, void **obp)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial3(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), obp);

    *obp = NULL;

    if (IsEqualGUID(&IID_IUnknown, riid))
    {
        IDirect3DMaterial3_AddRef(iface);
        *obp = iface;
        WINE_TRACE("  Creating IUnknown interface at %p.\n", *obp);
        return S_OK;
    }
    if (IsEqualGUID(&IID_IDirect3DMaterial, riid))
    {
        IDirect3DMaterial_AddRef(&material->IDirect3DMaterial_iface);
        *obp = &material->IDirect3DMaterial_iface;
        WINE_TRACE("  Creating IDirect3DMaterial interface %p\n", *obp);
        return S_OK;
    }
    if (IsEqualGUID(&IID_IDirect3DMaterial2, riid))
    {
        IDirect3DMaterial2_AddRef(&material->IDirect3DMaterial2_iface);
        *obp = &material->IDirect3DMaterial2_iface;
        WINE_TRACE("  Creating IDirect3DMaterial2 interface %p\n", *obp);
        return S_OK;
    }
    if (IsEqualGUID(&IID_IDirect3DMaterial3, riid))
    {
        IDirect3DMaterial3_AddRef(&material->IDirect3DMaterial3_iface);
        *obp = &material->IDirect3DMaterial3_iface;
        WINE_TRACE("  Creating IDirect3DMaterial3 interface %p\n", *obp);
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));

    return E_NOINTERFACE;
}

static HRESULT WINAPI d3d_material2_QueryInterface(IDirect3DMaterial2 *iface, REFIID riid, void **object)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial2(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return d3d_material3_QueryInterface(&material->IDirect3DMaterial3_iface, riid, object);
}

static HRESULT WINAPI d3d_material1_QueryInterface(IDirect3DMaterial *iface, REFIID riid, void **object)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    return d3d_material3_QueryInterface(&material->IDirect3DMaterial3_iface, riid, object);
}

static ULONG WINAPI d3d_material3_AddRef(IDirect3DMaterial3 *iface)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial3(iface);
    ULONG ref = InterlockedIncrement(&material->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", material, ref);

    return ref;
}

static ULONG WINAPI d3d_material2_AddRef(IDirect3DMaterial2 *iface)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return d3d_material3_AddRef(&material->IDirect3DMaterial3_iface);
}

static ULONG WINAPI d3d_material1_AddRef(IDirect3DMaterial *iface)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);

    WINE_TRACE("iface %p.\n", iface);

    return d3d_material3_AddRef(&material->IDirect3DMaterial3_iface);
}

static ULONG WINAPI d3d_material3_Release(IDirect3DMaterial3 *iface)
{
    struct qemu_d3d_material_Release call;
    struct qemu_material *material = impl_from_IDirect3DMaterial3(iface);
    ULONG ref = InterlockedDecrement(&material->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", material, ref);

    if (!ref)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_RELEASE);
        call.iface = (ULONG_PTR)material;
        qemu_syscall(&call.super);
    }

    return ref;
}

static ULONG WINAPI d3d_material2_Release(IDirect3DMaterial2 *iface)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial2(iface);

    WINE_TRACE("iface %p.\n", iface);

    return d3d_material3_Release(&material->IDirect3DMaterial3_iface);
}

static ULONG WINAPI d3d_material1_Release(IDirect3DMaterial *iface)
{
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);

    WINE_TRACE("iface %p.\n", iface);

    return d3d_material3_Release(&material->IDirect3DMaterial3_iface);
}

#else

void qemu_d3d_material1_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_material_Release *c = (struct qemu_d3d_material_Release *)call;
    struct qemu_material *material;

    WINE_TRACE("\n");
    material = QEMU_G2H(c->iface);

    IDirect3DMaterial3_Release(material->host3);
    IDirect3DMaterial2_Release(material->host2);
    c->super.iret = IDirect3DMaterial_Release(material->host1);

    if (c->super.iret)
        WINE_ERR("Unexpected material refcount %lu.\n", c->super.iret);

    HeapFree(GetProcessHeap(), 0, material);
}

#endif

struct qemu_d3d_material1_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t d3d;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material1_Initialize(IDirect3DMaterial *iface, IDirect3D *d3d)
{
    struct qemu_d3d_material1_Initialize call;
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_INITIALIZE);
    call.iface = (ULONG_PTR)material;
    call.d3d = (ULONG_PTR)d3d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material1_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d_material1_Initialize *c = (struct qemu_d3d_material1_Initialize *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial_Initialize(material->host1, QEMU_G2H(c->d3d));
}

#endif

struct qemu_d3d_material1_Reserve
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material1_Reserve(IDirect3DMaterial *iface)
{
    struct qemu_d3d_material1_Reserve call;
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_RESERVE);
    call.iface = (ULONG_PTR)material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material1_Reserve(struct qemu_syscall *call)
{
    struct qemu_d3d_material1_Reserve *c = (struct qemu_d3d_material1_Reserve *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial_Reserve(material->host1);
}

#endif

struct qemu_d3d_material1_Unreserve
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material1_Unreserve(IDirect3DMaterial *iface)
{
    struct qemu_d3d_material1_Unreserve call;
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_UNRESERVE);
    call.iface = (ULONG_PTR)material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material1_Unreserve(struct qemu_syscall *call)
{
    struct qemu_d3d_material1_Unreserve *c = (struct qemu_d3d_material1_Unreserve *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial_Unreserve(material->host1);
}

#endif

struct qemu_d3d_material3_SetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material3_SetMaterial(IDirect3DMaterial3 *iface, D3DMATERIAL *mat)
{
    struct qemu_d3d_material3_SetMaterial call;
    struct qemu_material *material = impl_from_IDirect3DMaterial3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL3_SETMATERIAL);
    call.iface = (ULONG_PTR)material;
    call.mat = (ULONG_PTR)mat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material3_SetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_material3_SetMaterial *c = (struct qemu_d3d_material3_SetMaterial *)call;
    struct qemu_material *material;

    WINE_TRACE("\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial3_SetMaterial(material->host3, QEMU_G2H(c->mat));
}

#endif

struct qemu_d3d_material3_GetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material3_GetMaterial(IDirect3DMaterial3 *iface, D3DMATERIAL *mat)
{
    struct qemu_d3d_material3_GetMaterial call;
    struct qemu_material *material = impl_from_IDirect3DMaterial3(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL3_GETMATERIAL);
    call.iface = (ULONG_PTR)material;
    call.mat = (ULONG_PTR)mat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material3_GetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_material3_GetMaterial *c = (struct qemu_d3d_material3_GetMaterial *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial3_GetMaterial(material->host3, QEMU_G2H(c->mat));
}

#endif

struct qemu_d3d_material3_GetHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material3_GetHandle(IDirect3DMaterial3 *iface, IDirect3DDevice3 *device,
        D3DMATERIALHANDLE *handle)
{
    struct qemu_d3d_material3_GetHandle call;
    struct qemu_material *material = impl_from_IDirect3DMaterial3(iface);
    struct qemu_device *dev_impl = unsafe_impl_from_IDirect3DDevice3(device);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL3_GETHANDLE);
    call.iface = (ULONG_PTR)material;
    call.device = (ULONG_PTR)dev_impl;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material3_GetHandle(struct qemu_syscall *call)
{
    struct qemu_d3d_material3_GetHandle *c = (struct qemu_d3d_material3_GetHandle *)call;
    struct qemu_material *material;
    struct qemu_device *device;

    WINE_TRACE("\n");
    material = QEMU_G2H(c->iface);
    device = QEMU_G2H(c->device);

    c->super.iret = IDirect3DMaterial3_GetHandle(material->host3, device ? device->host3 : NULL, QEMU_G2H(c->handle));
}

#endif

struct qemu_d3d_material2_GetHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material2_GetHandle(IDirect3DMaterial2 *iface, IDirect3DDevice2 *device,
        D3DMATERIALHANDLE *handle)
{
    struct qemu_d3d_material2_GetHandle call;
    struct qemu_material *material = impl_from_IDirect3DMaterial2(iface);
    struct qemu_device *dev_impl = unsafe_impl_from_IDirect3DDevice2(device);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL2_GETHANDLE);
    call.iface = (ULONG_PTR)material;
    call.device = (ULONG_PTR)dev_impl;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material2_GetHandle(struct qemu_syscall *call)
{
    struct qemu_d3d_material2_GetHandle *c = (struct qemu_d3d_material2_GetHandle *)call;
    struct qemu_material *material;
    struct qemu_device *device;

    WINE_TRACE("\n");
    material = QEMU_G2H(c->iface);
    device = QEMU_G2H(c->device);

    c->super.iret = IDirect3DMaterial2_GetHandle(material->host2, device ? device->host2 : NULL, QEMU_G2H(c->handle));
}

#endif

struct qemu_d3d_material1_GetHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material1_GetHandle(IDirect3DMaterial *iface, IDirect3DDevice *device,
        D3DMATERIALHANDLE *handle)
{
    struct qemu_d3d_material1_GetHandle call;
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);
    struct qemu_device *dev_impl = unsafe_impl_from_IDirect3DDevice(device);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_GETHANDLE);
    call.iface = (ULONG_PTR)material;
    call.device = (ULONG_PTR)dev_impl;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material1_GetHandle(struct qemu_syscall *call)
{
    struct qemu_d3d_material1_GetHandle *c = (struct qemu_d3d_material1_GetHandle *)call;
    struct qemu_material *material;
    struct qemu_device *device;

    WINE_TRACE("\n");
    material = QEMU_G2H(c->iface);
    device = QEMU_G2H(c->device);

    c->super.iret = IDirect3DMaterial_GetHandle(material->host1, device ? device->host1 : NULL, QEMU_G2H(c->handle));
}

#endif

struct qemu_d3d_material2_SetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material2_SetMaterial(IDirect3DMaterial2 *iface, D3DMATERIAL *mat)
{
    struct qemu_d3d_material2_SetMaterial call;
    struct qemu_material *material = impl_from_IDirect3DMaterial2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL2_SETMATERIAL);
    call.iface = (ULONG_PTR)material;
    call.mat = (ULONG_PTR)mat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material2_SetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_material2_SetMaterial *c = (struct qemu_d3d_material2_SetMaterial *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial2_SetMaterial(material->host2, QEMU_G2H(c->mat));
}

#endif

struct qemu_d3d_material1_SetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material1_SetMaterial(IDirect3DMaterial *iface, D3DMATERIAL *mat)
{
    struct qemu_d3d_material1_SetMaterial call;
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_SETMATERIAL);
    call.iface = (ULONG_PTR)material;
    call.mat = (ULONG_PTR)mat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material1_SetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_material1_SetMaterial *c = (struct qemu_d3d_material1_SetMaterial *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial_SetMaterial(material->host1, QEMU_G2H(c->mat));
}

#endif

struct qemu_d3d_material2_GetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material2_GetMaterial(IDirect3DMaterial2 *iface, D3DMATERIAL *mat)
{
    struct qemu_d3d_material2_GetMaterial call;
    struct qemu_material *material = impl_from_IDirect3DMaterial2(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL2_GETMATERIAL);
    call.iface = (ULONG_PTR)material;
    call.mat = (ULONG_PTR)mat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material2_GetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_material2_GetMaterial *c = (struct qemu_d3d_material2_GetMaterial *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial2_GetMaterial(material->host2, QEMU_G2H(c->mat));
}

#endif

struct qemu_d3d_material1_GetMaterial
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_material1_GetMaterial(IDirect3DMaterial *iface, D3DMATERIAL *mat)
{
    struct qemu_d3d_material1_GetMaterial call;
    struct qemu_material *material = impl_from_IDirect3DMaterial(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_MATERIAL1_GETMATERIAL);
    call.iface = (ULONG_PTR)material;
    call.mat = (ULONG_PTR)mat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_material1_GetMaterial(struct qemu_syscall *call)
{
    struct qemu_d3d_material1_GetMaterial *c = (struct qemu_d3d_material1_GetMaterial *)call;
    struct qemu_material *material;

    WINE_FIXME("Unverified!\n");
    material = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DMaterial_GetMaterial(material->host1, QEMU_G2H(c->mat));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DMaterial3Vtbl d3d_material3_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_material3_QueryInterface,
    d3d_material3_AddRef,
    d3d_material3_Release,
    /*** IDirect3DMaterial3 Methods ***/
    d3d_material3_SetMaterial,
    d3d_material3_GetMaterial,
    d3d_material3_GetHandle,
};

static const struct IDirect3DMaterial2Vtbl d3d_material2_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_material2_QueryInterface,
    d3d_material2_AddRef,
    d3d_material2_Release,
    /*** IDirect3DMaterial2 Methods ***/
    d3d_material2_SetMaterial,
    d3d_material2_GetMaterial,
    d3d_material2_GetHandle,
};

static const struct IDirect3DMaterialVtbl d3d_material1_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_material1_QueryInterface,
    d3d_material1_AddRef,
    d3d_material1_Release,
    /*** IDirect3DMaterial1 Methods ***/
    d3d_material1_Initialize,
    d3d_material1_SetMaterial,
    d3d_material1_GetMaterial,
    d3d_material1_GetHandle,
    d3d_material1_Reserve,
    d3d_material1_Unreserve,
};

struct qemu_material *d3d_material_guest_init(struct qemu_material *material)
{
    material->IDirect3DMaterial3_iface.lpVtbl = &d3d_material3_vtbl;
    material->IDirect3DMaterial2_iface.lpVtbl = &d3d_material2_vtbl;
    material->IDirect3DMaterial_iface.lpVtbl = &d3d_material1_vtbl;
    material->ref = 1;
}

#endif
