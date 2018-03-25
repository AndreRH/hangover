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

#include <windows.h>
#include <stdio.h>
#include <dinput.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_dinput.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dinput.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_dinput);
#endif

struct qemu_IDirectInputDeviceWImpl_Unacquire
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dinput_device *impl_from_IDirectInputDevice8A(IDirectInputDevice8A *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput_device, IDirectInputDevice8A_iface);
}
static inline struct qemu_dinput_device *impl_from_IDirectInputDevice8W(IDirectInputDevice8W *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput_device, IDirectInputDevice8W_iface);
}

static HRESULT WINAPI IDirectInputDeviceWImpl_Unacquire(IDirectInputDevice8W *iface)
{
    struct qemu_IDirectInputDeviceWImpl_Unacquire call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_UNACQUIRE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_Unacquire(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_Unacquire *c = (struct qemu_IDirectInputDeviceWImpl_Unacquire *)call;
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Unacquire(device->host_w);
}

#endif

struct qemu_IDirectInputDeviceAImpl_Unacquire
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_Unacquire(IDirectInputDevice8A *iface)
{
    struct qemu_IDirectInputDeviceAImpl_Unacquire call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_UNACQUIRE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_Unacquire(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_Unacquire *c = (struct qemu_IDirectInputDeviceAImpl_Unacquire *)call;
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Unacquire(device->host_a);
}

#endif

struct qemu_IDirectInputDeviceImpl_SetDataFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t df;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SetDataFormat(IDirectInputDevice8W *iface, LPCDIDATAFORMAT df)
{
    struct qemu_IDirectInputDeviceImpl_SetDataFormat call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SETDATAFORMAT);
    call.iface = (ULONG_PTR)device;
    call.df = (ULONG_PTR)df;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI IDirectInputDeviceAImpl_SetDataFormat(IDirectInputDevice8A *iface, LPCDIDATAFORMAT df)
{
    struct qemu_IDirectInputDeviceImpl_SetDataFormat call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SETDATAFORMAT);
    call.iface = (ULONG_PTR)device;
    call.df = (ULONG_PTR)df;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceImpl_SetDataFormat(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceImpl_SetDataFormat *c = (struct qemu_IDirectInputDeviceImpl_SetDataFormat *)call;
    struct qemu_dinput_device *device;
    DIOBJECTDATAFORMAT *obj_fmt = NULL;
    struct qemu_DIOBJECTDATAFORMAT *obj_fmt32;
    DIDATAFORMAT stack, *fmt = &stack;
    struct qemu_DIDATAFORMAT *fmt32;
    DWORD i;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    fmt = QEMU_G2H(c->df);
#else
    fmt32 = QEMU_G2H(c->df);
    if (!fmt32)
    {
        fmt = NULL;
    }
    else if (fmt32->dwSize != sizeof(*fmt32))
    {
        fmt->dwSize = 0;
    }
    else
    {
        DIDATAFORMAT_g2h(fmt, fmt32);
        obj_fmt32 = (struct qemu_DIOBJECTDATAFORMAT *)fmt->rgodf;
        if (obj_fmt32)
        {
            obj_fmt = HeapAlloc(GetProcessHeap(), 0, fmt->dwNumObjs * sizeof(*fmt->rgodf));
            if (!obj_fmt)
                WINE_ERR("Out of memory.\n");

            for (i = 0; i < fmt->dwNumObjs; ++i)
                DIOBJECTDATAFORMAT_g2h(&obj_fmt[i], &obj_fmt32[i]);

            fmt->rgodf = obj_fmt;
        }
    }
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SETDATAFORMAT))
        c->super.iret = IDirectInputDevice8_SetDataFormat(device->host_w, fmt);
    else
        c->super.iret = IDirectInputDevice8_SetDataFormat(device->host_a, fmt);

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, obj_fmt);
#endif
}

#endif

struct qemu_IDirectInputDeviceWImpl_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwnd;
    uint64_t dwflags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SetCooperativeLevel(IDirectInputDevice8W *iface, HWND hwnd, DWORD dwflags)
{
    struct qemu_IDirectInputDeviceWImpl_SetCooperativeLevel call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)device;
    call.hwnd = (ULONG_PTR)hwnd;
    call.dwflags = dwflags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_SetCooperativeLevel *c = (struct qemu_IDirectInputDeviceWImpl_SetCooperativeLevel *)call;
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetCooperativeLevel(device->host_w, QEMU_G2H(c->hwnd), c->dwflags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwnd;
    uint64_t dwflags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_SetCooperativeLevel(IDirectInputDevice8A *iface, HWND hwnd, DWORD dwflags)
{
    struct qemu_IDirectInputDeviceAImpl_SetCooperativeLevel call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)device;
    call.hwnd = (ULONG_PTR)hwnd;
    call.dwflags = dwflags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_SetCooperativeLevel *c = (struct qemu_IDirectInputDeviceAImpl_SetCooperativeLevel *)call;
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetCooperativeLevel(device->host_a, QEMU_G2H(c->hwnd), c->dwflags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_SetEventNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SetEventNotification(IDirectInputDevice8W *iface, HANDLE event)
{
    struct qemu_IDirectInputDeviceWImpl_SetEventNotification call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SETEVENTNOTIFICATION);
    call.iface = (ULONG_PTR)device;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_SetEventNotification(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_SetEventNotification *c = (struct qemu_IDirectInputDeviceWImpl_SetEventNotification *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetEventNotification(device->host_w, QEMU_G2H(c->event));
}

#endif

struct qemu_IDirectInputDeviceAImpl_SetEventNotification
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_SetEventNotification(IDirectInputDevice8A *iface, HANDLE event)
{
    struct qemu_IDirectInputDeviceAImpl_SetEventNotification call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SETEVENTNOTIFICATION);
    call.iface = (ULONG_PTR)device;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_SetEventNotification(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_SetEventNotification *c = (struct qemu_IDirectInputDeviceAImpl_SetEventNotification *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetEventNotification(device->host_a, QEMU_G2H(c->event));
}

#endif

struct qemu_IDirectInputDeviceImpl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI IDirectInputDeviceWImpl_Release(IDirectInputDevice8W *iface)
{
    struct qemu_IDirectInputDeviceImpl_Release call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI ULONG WINAPI IDirectInputDeviceAImpl_Release(IDirectInputDevice8A *iface)
{
    struct qemu_IDirectInputDeviceImpl_Release call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceImpl_Release(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceImpl_Release *c = (struct qemu_IDirectInputDeviceImpl_Release *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    /* TODO: AddRef the IDirectInput parent */
    c->super.iret = IDirectInputDevice8_Release(device->host_w);
    /* TODO: Release the parent via our own release function. */

    if (!c->super.iret)
    {
        WINE_TRACE("Destroying IDirectInputDevice wrapper %p.\n", device);
        HeapFree(GetProcessHeap(), 0, device);
    }
}

#endif

struct qemu_IDirectInputDeviceWImpl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppobj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_QueryInterface(IDirectInputDevice8W *iface, REFIID riid, LPVOID *ppobj)
{
    struct qemu_IDirectInputDeviceWImpl_QueryInterface call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.ppobj = (ULONG_PTR)ppobj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_QueryInterface *c = (struct qemu_IDirectInputDeviceWImpl_QueryInterface *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_QueryInterface(device->host_w, QEMU_G2H(c->riid), QEMU_G2H(c->ppobj));
}

#endif

struct qemu_IDirectInputDeviceAImpl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppobj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_QueryInterface(IDirectInputDevice8A *iface, REFIID riid, LPVOID *ppobj)
{
    struct qemu_IDirectInputDeviceAImpl_QueryInterface call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.ppobj = (ULONG_PTR)ppobj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_QueryInterface *c = (struct qemu_IDirectInputDeviceAImpl_QueryInterface *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_QueryInterface(device->host_a, QEMU_G2H(c->riid), QEMU_G2H(c->ppobj));
}

#endif

struct qemu_IDirectInputDeviceWImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI IDirectInputDeviceWImpl_AddRef(IDirectInputDevice8W *iface)
{
    struct qemu_IDirectInputDeviceWImpl_AddRef call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_AddRef *c = (struct qemu_IDirectInputDeviceWImpl_AddRef *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_AddRef(device->host_w);
}

#endif

struct qemu_IDirectInputDeviceAImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI IDirectInputDeviceAImpl_AddRef(IDirectInputDevice8A *iface)
{
    struct qemu_IDirectInputDeviceAImpl_AddRef call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_AddRef *c = (struct qemu_IDirectInputDeviceAImpl_AddRef *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_AddRef(device->host_a);
}

#endif

struct qemu_IDirectInputDeviceAImpl_EnumObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpCallback;
    uint64_t lpvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_EnumObjects(IDirectInputDevice8A *iface, LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID lpvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_EnumObjects call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ENUMOBJECTS);
    call.iface = (ULONG_PTR)device;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.lpvRef = (ULONG_PTR)lpvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_EnumObjects(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_EnumObjects *c = (struct qemu_IDirectInputDeviceAImpl_EnumObjects *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumObjects(device->host_a, QEMU_G2H(c->lpCallback), QEMU_G2H(c->lpvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_EnumObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpCallback;
    uint64_t lpvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_EnumObjects(IDirectInputDevice8W *iface, LPDIENUMDEVICEOBJECTSCALLBACKW lpCallback, LPVOID lpvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_EnumObjects call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ENUMOBJECTS);
    call.iface = (ULONG_PTR)device;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.lpvRef = (ULONG_PTR)lpvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_EnumObjects(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_EnumObjects *c = (struct qemu_IDirectInputDeviceWImpl_EnumObjects *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumObjects(device->host_w, QEMU_G2H(c->lpCallback), QEMU_G2H(c->lpvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_SetProperty
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pdiph;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SetProperty(IDirectInputDevice8W *iface, REFGUID rguid, LPCDIPROPHEADER pdiph)
{
    struct qemu_IDirectInputDeviceWImpl_SetProperty call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SETPROPERTY);
    call.iface = (ULONG_PTR)device;
    call.rguid = (ULONG_PTR)rguid;
    call.pdiph = (ULONG_PTR)pdiph;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_SetProperty(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_SetProperty *c = (struct qemu_IDirectInputDeviceWImpl_SetProperty *)call;
    struct qemu_dinput_device *device;

    /* All DIPROPHEADER based structs have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetProperty(device->host_w, QEMU_G2H(c->rguid), QEMU_G2H(c->pdiph));
}

#endif

struct qemu_IDirectInputDeviceAImpl_SetProperty
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pdiph;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_SetProperty(IDirectInputDevice8A *iface, REFGUID rguid, LPCDIPROPHEADER pdiph)
{
    struct qemu_IDirectInputDeviceAImpl_SetProperty call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SETPROPERTY);
    call.iface = (ULONG_PTR)device;
    call.rguid = (ULONG_PTR)rguid;
    call.pdiph = (ULONG_PTR)pdiph;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_SetProperty(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_SetProperty *c = (struct qemu_IDirectInputDeviceAImpl_SetProperty *)call;
    struct qemu_dinput_device *device;

    /* All DIPROPHEADER based structs have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetProperty(device->host_a, QEMU_G2H(c->rguid), QEMU_G2H(c->pdiph));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetDeviceData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dodsize;
    uint64_t dod;
    uint64_t entries;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetDeviceData(IDirectInputDevice8W *iface, DWORD dodsize, LPDIDEVICEOBJECTDATA dod, LPDWORD entries, DWORD flags)
{
    struct qemu_IDirectInputDeviceWImpl_GetDeviceData call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETDEVICEDATA);
    call.iface = (ULONG_PTR)device;
    call.dodsize = dodsize;
    call.dod = (ULONG_PTR)dod;
    call.entries = (ULONG_PTR)entries;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetDeviceData(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetDeviceData *c = (struct qemu_IDirectInputDeviceWImpl_GetDeviceData *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetDeviceData(device->host_w, c->dodsize, QEMU_G2H(c->dod), QEMU_G2H(c->entries), c->flags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetDeviceData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dodsize;
    uint64_t dod;
    uint64_t entries;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetDeviceData(IDirectInputDevice8A *iface, DWORD dodsize, LPDIDEVICEOBJECTDATA dod, LPDWORD entries, DWORD flags)
{
    struct qemu_IDirectInputDeviceAImpl_GetDeviceData call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETDEVICEDATA);
    call.iface = (ULONG_PTR)device;
    call.dodsize = dodsize;
    call.dod = (ULONG_PTR)dod;
    call.entries = (ULONG_PTR)entries;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetDeviceData(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetDeviceData *c = (struct qemu_IDirectInputDeviceAImpl_GetDeviceData *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetDeviceData(device->host_a, c->dodsize, QEMU_G2H(c->dod), QEMU_G2H(c->entries), c->flags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_RunControlPanel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_RunControlPanel(IDirectInputDevice8W *iface, HWND hwndOwner, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_RunControlPanel call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_RUNCONTROLPANEL);
    call.iface = (ULONG_PTR)device;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_RunControlPanel(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_RunControlPanel *c = (struct qemu_IDirectInputDeviceWImpl_RunControlPanel *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_RunControlPanel(device->host_w, QEMU_G2H(c->hwndOwner), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_RunControlPanel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_RunControlPanel(IDirectInputDevice8A *iface, HWND hwndOwner, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_RunControlPanel call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_RUNCONTROLPANEL);
    call.iface = (ULONG_PTR)device;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_RunControlPanel(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_RunControlPanel *c = (struct qemu_IDirectInputDeviceAImpl_RunControlPanel *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_RunControlPanel(device->host_a, QEMU_G2H(c->hwndOwner), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hinst;
    uint64_t dwVersion;
    uint64_t rguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_Initialize(IDirectInputDevice8W *iface, HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
    struct qemu_IDirectInputDeviceWImpl_Initialize call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)device;
    call.hinst = (ULONG_PTR)hinst;
    call.dwVersion = dwVersion;
    call.rguid = (ULONG_PTR)rguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_Initialize *c = (struct qemu_IDirectInputDeviceWImpl_Initialize *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Initialize(device->host_w, QEMU_G2H(c->hinst), c->dwVersion, QEMU_G2H(c->rguid));
}

#endif

struct qemu_IDirectInputDeviceAImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hinst;
    uint64_t dwVersion;
    uint64_t rguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_Initialize(IDirectInputDevice8A *iface, HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
    struct qemu_IDirectInputDeviceAImpl_Initialize call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)device;
    call.hinst = (ULONG_PTR)hinst;
    call.dwVersion = dwVersion;
    call.rguid = (ULONG_PTR)rguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_Initialize *c = (struct qemu_IDirectInputDeviceAImpl_Initialize *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Initialize(device->host_a, QEMU_G2H(c->hinst), c->dwVersion, QEMU_G2H(c->rguid));
}

#endif

struct qemu_IDirectInputDeviceWImpl_CreateEffect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t lpeff;
    uint64_t ppdef;
    uint64_t pUnkOuter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_CreateEffect(IDirectInputDevice8W *iface, REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdef, LPUNKNOWN pUnkOuter)
{
    struct qemu_IDirectInputDeviceWImpl_CreateEffect call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_CREATEEFFECT);
    call.iface = (ULONG_PTR)device;
    call.rguid = (ULONG_PTR)rguid;
    call.lpeff = (ULONG_PTR)lpeff;
    call.ppdef = (ULONG_PTR)ppdef;
    call.pUnkOuter = (ULONG_PTR)pUnkOuter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_CreateEffect(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_CreateEffect *c = (struct qemu_IDirectInputDeviceWImpl_CreateEffect *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_CreateEffect(device->host_w, QEMU_G2H(c->rguid), QEMU_G2H(c->lpeff), QEMU_G2H(c->ppdef), QEMU_G2H(c->pUnkOuter));
}

#endif

struct qemu_IDirectInputDeviceAImpl_CreateEffect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t lpeff;
    uint64_t ppdef;
    uint64_t pUnkOuter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_CreateEffect(IDirectInputDevice8A *iface, REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdef, LPUNKNOWN pUnkOuter)
{
    struct qemu_IDirectInputDeviceAImpl_CreateEffect call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_CREATEEFFECT);
    call.iface = (ULONG_PTR)device;
    call.rguid = (ULONG_PTR)rguid;
    call.lpeff = (ULONG_PTR)lpeff;
    call.ppdef = (ULONG_PTR)ppdef;
    call.pUnkOuter = (ULONG_PTR)pUnkOuter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_CreateEffect(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_CreateEffect *c = (struct qemu_IDirectInputDeviceAImpl_CreateEffect *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_CreateEffect(device->host_a, QEMU_G2H(c->rguid), QEMU_G2H(c->lpeff), QEMU_G2H(c->ppdef), QEMU_G2H(c->pUnkOuter));
}

#endif

struct qemu_IDirectInputDeviceAImpl_EnumEffects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpCallback;
    uint64_t lpvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_EnumEffects(IDirectInputDevice8A *iface, LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID lpvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_EnumEffects call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ENUMEFFECTS);
    call.iface = (ULONG_PTR)device;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.lpvRef = (ULONG_PTR)lpvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_EnumEffects(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_EnumEffects *c = (struct qemu_IDirectInputDeviceAImpl_EnumEffects *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumEffects(device->host_a, QEMU_G2H(c->lpCallback), QEMU_G2H(c->lpvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_EnumEffects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpCallback;
    uint64_t lpvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_EnumEffects(IDirectInputDevice8W *iface, LPDIENUMEFFECTSCALLBACKW lpCallback, LPVOID lpvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_EnumEffects call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ENUMEFFECTS);
    call.iface = (ULONG_PTR)device;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.lpvRef = (ULONG_PTR)lpvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_EnumEffects(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_EnumEffects *c = (struct qemu_IDirectInputDeviceWImpl_EnumEffects *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumEffects(device->host_w, QEMU_G2H(c->lpCallback), QEMU_G2H(c->lpvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetEffectInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdei;
    uint64_t rguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetEffectInfo(IDirectInputDevice8A *iface, LPDIEFFECTINFOA lpdei, REFGUID rguid)
{
    struct qemu_IDirectInputDeviceAImpl_GetEffectInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETEFFECTINFO);
    call.iface = (ULONG_PTR)device;
    call.lpdei = (ULONG_PTR)lpdei;
    call.rguid = (ULONG_PTR)rguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetEffectInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetEffectInfo *c = (struct qemu_IDirectInputDeviceAImpl_GetEffectInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetEffectInfo(device->host_a, QEMU_G2H(c->lpdei), QEMU_G2H(c->rguid));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetEffectInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdei;
    uint64_t rguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetEffectInfo(IDirectInputDevice8W *iface, LPDIEFFECTINFOW lpdei, REFGUID rguid)
{
    struct qemu_IDirectInputDeviceWImpl_GetEffectInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETEFFECTINFO);
    call.iface = (ULONG_PTR)device;
    call.lpdei = (ULONG_PTR)lpdei;
    call.rguid = (ULONG_PTR)rguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetEffectInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetEffectInfo *c = (struct qemu_IDirectInputDeviceWImpl_GetEffectInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetEffectInfo(device->host_w, QEMU_G2H(c->lpdei), QEMU_G2H(c->rguid));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetForceFeedbackState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pdwOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetForceFeedbackState(IDirectInputDevice8W *iface, LPDWORD pdwOut)
{
    struct qemu_IDirectInputDeviceWImpl_GetForceFeedbackState call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETFORCEFEEDBACKSTATE);
    call.iface = (ULONG_PTR)device;
    call.pdwOut = (ULONG_PTR)pdwOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetForceFeedbackState(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetForceFeedbackState *c = (struct qemu_IDirectInputDeviceWImpl_GetForceFeedbackState *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetForceFeedbackState(device->host_w, QEMU_G2H(c->pdwOut));
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetForceFeedbackState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pdwOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetForceFeedbackState(IDirectInputDevice8A *iface, LPDWORD pdwOut)
{
    struct qemu_IDirectInputDeviceAImpl_GetForceFeedbackState call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETFORCEFEEDBACKSTATE);
    call.iface = (ULONG_PTR)device;
    call.pdwOut = (ULONG_PTR)pdwOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetForceFeedbackState(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetForceFeedbackState *c = (struct qemu_IDirectInputDeviceAImpl_GetForceFeedbackState *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetForceFeedbackState(device->host_a, QEMU_G2H(c->pdwOut));
}

#endif

struct qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SendForceFeedbackCommand(IDirectInputDevice8W *iface, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SENDFORCEFEEDBACKCOMMAND);
    call.iface = (ULONG_PTR)device;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand *c = (struct qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SendForceFeedbackCommand(device->host_w, c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_SendForceFeedbackCommand(IDirectInputDevice8A *iface, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SENDFORCEFEEDBACKCOMMAND);
    call.iface = (ULONG_PTR)device;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand *c = (struct qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SendForceFeedbackCommand(device->host_a, c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpCallback;
    uint64_t lpvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_EnumCreatedEffectObjects(IDirectInputDevice8W *iface, LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID lpvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ENUMCREATEDEFFECTOBJECTS);
    call.iface = (ULONG_PTR)device;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.lpvRef = (ULONG_PTR)lpvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects *c = (struct qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumCreatedEffectObjects(device->host_w, QEMU_G2H(c->lpCallback), QEMU_G2H(c->lpvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpCallback;
    uint64_t lpvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_EnumCreatedEffectObjects(IDirectInputDevice8A *iface, LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID lpvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ENUMCREATEDEFFECTOBJECTS);
    call.iface = (ULONG_PTR)device;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.lpvRef = (ULONG_PTR)lpvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects *c = (struct qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumCreatedEffectObjects(device->host_a, QEMU_G2H(c->lpCallback), QEMU_G2H(c->lpvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_Escape
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDIEEsc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_Escape(IDirectInputDevice8W *iface, LPDIEFFESCAPE lpDIEEsc)
{
    struct qemu_IDirectInputDeviceWImpl_Escape call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ESCAPE);
    call.iface = (ULONG_PTR)device;
    call.lpDIEEsc = (ULONG_PTR)lpDIEEsc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_Escape(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_Escape *c = (struct qemu_IDirectInputDeviceWImpl_Escape *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Escape(device->host_w, QEMU_G2H(c->lpDIEEsc));
}

#endif

struct qemu_IDirectInputDeviceAImpl_Escape
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDIEEsc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_Escape(IDirectInputDevice8A *iface, LPDIEFFESCAPE lpDIEEsc)
{
    struct qemu_IDirectInputDeviceAImpl_Escape call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ESCAPE);
    call.iface = (ULONG_PTR)device;
    call.lpDIEEsc = (ULONG_PTR)lpDIEEsc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_Escape(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_Escape *c = (struct qemu_IDirectInputDeviceAImpl_Escape *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Escape(device->host_a, QEMU_G2H(c->lpDIEEsc));
}

#endif

struct qemu_IDirectInputDeviceWImpl_Poll
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_Poll(IDirectInputDevice8W *iface)
{
    struct qemu_IDirectInputDeviceWImpl_Poll call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_POLL);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_Poll(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_Poll *c = (struct qemu_IDirectInputDeviceWImpl_Poll *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Poll(device->host_w);
}

#endif

struct qemu_IDirectInputDeviceAImpl_Poll
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_Poll(IDirectInputDevice8A *iface)
{
    struct qemu_IDirectInputDeviceAImpl_Poll call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_POLL);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_Poll(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_Poll *c = (struct qemu_IDirectInputDeviceAImpl_Poll *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Poll(device->host_a);
}

#endif

struct qemu_IDirectInputDeviceWImpl_SendDeviceData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cbObjectData;
    uint64_t rgdod;
    uint64_t pdwInOut;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SendDeviceData(IDirectInputDevice8W *iface, DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_SendDeviceData call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SENDDEVICEDATA);
    call.iface = (ULONG_PTR)device;
    call.cbObjectData = cbObjectData;
    call.rgdod = (ULONG_PTR)rgdod;
    call.pdwInOut = (ULONG_PTR)pdwInOut;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_SendDeviceData(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_SendDeviceData *c = (struct qemu_IDirectInputDeviceWImpl_SendDeviceData *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SendDeviceData(device->host_w, c->cbObjectData, QEMU_G2H(c->rgdod), QEMU_G2H(c->pdwInOut), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_SendDeviceData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cbObjectData;
    uint64_t rgdod;
    uint64_t pdwInOut;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_SendDeviceData(IDirectInputDevice8A *iface, DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_SendDeviceData call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SENDDEVICEDATA);
    call.iface = (ULONG_PTR)device;
    call.cbObjectData = cbObjectData;
    call.rgdod = (ULONG_PTR)rgdod;
    call.pdwInOut = (ULONG_PTR)pdwInOut;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_SendDeviceData(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_SendDeviceData *c = (struct qemu_IDirectInputDeviceAImpl_SendDeviceData *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SendDeviceData(device->host_a, c->cbObjectData, QEMU_G2H(c->rgdod), QEMU_G2H(c->pdwInOut), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_EnumEffectsInFile
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpszFileName;
    uint64_t pec;
    uint64_t pvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_EnumEffectsInFile(IDirectInputDevice8A *iface, LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_EnumEffectsInFile call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ENUMEFFECTSINFILE);
    call.iface = (ULONG_PTR)device;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.pec = (ULONG_PTR)pec;
    call.pvRef = (ULONG_PTR)pvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_EnumEffectsInFile(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_EnumEffectsInFile *c = (struct qemu_IDirectInputDeviceAImpl_EnumEffectsInFile *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumEffectsInFile(device->host_a, QEMU_G2H(c->lpszFileName), QEMU_G2H(c->pec), QEMU_G2H(c->pvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_EnumEffectsInFile
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpszFileName;
    uint64_t pec;
    uint64_t pvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_EnumEffectsInFile(IDirectInputDevice8W *iface, LPCWSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_EnumEffectsInFile call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ENUMEFFECTSINFILE);
    call.iface = (ULONG_PTR)device;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.pec = (ULONG_PTR)pec;
    call.pvRef = (ULONG_PTR)pvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_EnumEffectsInFile(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_EnumEffectsInFile *c = (struct qemu_IDirectInputDeviceWImpl_EnumEffectsInFile *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_EnumEffectsInFile(device->host_w, QEMU_G2H(c->lpszFileName), QEMU_G2H(c->pec), QEMU_G2H(c->pvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_WriteEffectToFile
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpszFileName;
    uint64_t dwEntries;
    uint64_t rgDiFileEft;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_WriteEffectToFile(IDirectInputDevice8A *iface, LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_WriteEffectToFile call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_WRITEEFFECTTOFILE);
    call.iface = (ULONG_PTR)device;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.dwEntries = dwEntries;
    call.rgDiFileEft = (ULONG_PTR)rgDiFileEft;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_WriteEffectToFile(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_WriteEffectToFile *c = (struct qemu_IDirectInputDeviceAImpl_WriteEffectToFile *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_WriteEffectToFile(device->host_a, QEMU_G2H(c->lpszFileName), c->dwEntries, QEMU_G2H(c->rgDiFileEft), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_WriteEffectToFile
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpszFileName;
    uint64_t dwEntries;
    uint64_t rgDiFileEft;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_WriteEffectToFile(IDirectInputDevice8W *iface, LPCWSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_WriteEffectToFile call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_WRITEEFFECTTOFILE);
    call.iface = (ULONG_PTR)device;
    call.lpszFileName = (ULONG_PTR)lpszFileName;
    call.dwEntries = dwEntries;
    call.rgDiFileEft = (ULONG_PTR)rgDiFileEft;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_WriteEffectToFile(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_WriteEffectToFile *c = (struct qemu_IDirectInputDeviceWImpl_WriteEffectToFile *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_WriteEffectToFile(device->host_w, QEMU_G2H(c->lpszFileName), c->dwEntries, QEMU_G2H(c->rgDiFileEft), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetImageInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiDevImageInfoHeader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetImageInfo(IDirectInputDevice8A *iface, LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
{
    struct qemu_IDirectInputDeviceAImpl_GetImageInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETIMAGEINFO);
    call.iface = (ULONG_PTR)device;
    call.lpdiDevImageInfoHeader = (ULONG_PTR)lpdiDevImageInfoHeader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetImageInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetImageInfo *c = (struct qemu_IDirectInputDeviceAImpl_GetImageInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetImageInfo(device->host_a, QEMU_G2H(c->lpdiDevImageInfoHeader));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetImageInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiDevImageInfoHeader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetImageInfo(IDirectInputDevice8W *iface, LPDIDEVICEIMAGEINFOHEADERW lpdiDevImageInfoHeader)
{
    struct qemu_IDirectInputDeviceWImpl_GetImageInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETIMAGEINFO);
    call.iface = (ULONG_PTR)device;
    call.lpdiDevImageInfoHeader = (ULONG_PTR)lpdiDevImageInfoHeader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetImageInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetImageInfo *c = (struct qemu_IDirectInputDeviceWImpl_GetImageInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetImageInfo(device->host_w, QEMU_G2H(c->lpdiDevImageInfoHeader));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetDeviceState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t len;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetDeviceState(IDirectInputDevice8W *iface, DWORD len, void *ptr)
{
    struct qemu_IDirectInputDeviceWImpl_GetDeviceState call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETDEVICESTATE);
    call.iface = (ULONG_PTR)device;
    call.len = len;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetDeviceState(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetDeviceState *c = (struct qemu_IDirectInputDeviceWImpl_GetDeviceState *)call;
    struct qemu_dinput_device *device;

    /* DIMOUSESTATE2 and DIJOYSTATE2 have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetDeviceState(device->host_w, c->len, QEMU_G2H(c->ptr));
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetDeviceState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t len;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetDeviceState(IDirectInputDevice8A *iface, DWORD len, void *ptr)
{
    struct qemu_IDirectInputDeviceAImpl_GetDeviceState call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETDEVICESTATE);
    call.iface = (ULONG_PTR)device;
    call.len = len;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetDeviceState(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetDeviceState *c = (struct qemu_IDirectInputDeviceAImpl_GetDeviceState *)call;
    struct qemu_dinput_device *device;

    /* DIMOUSESTATE2 and DIJOYSTATE2 have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetDeviceState(device->host_a, c->len, QEMU_G2H(c->ptr));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetCapabilities
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDIDevCaps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetCapabilities(IDirectInputDevice8W *iface, LPDIDEVCAPS lpDIDevCaps)
{
    struct qemu_IDirectInputDeviceWImpl_GetCapabilities call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETCAPABILITIES);
    call.iface = (ULONG_PTR)device;
    call.lpDIDevCaps = (ULONG_PTR)lpDIDevCaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetCapabilities(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetCapabilities *c = (struct qemu_IDirectInputDeviceWImpl_GetCapabilities *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetCapabilities(device->host_w, QEMU_G2H(c->lpDIDevCaps));
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetCapabilities
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDIDevCaps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetCapabilities(IDirectInputDevice8A *iface, LPDIDEVCAPS lpDIDevCaps)
{
    struct qemu_IDirectInputDeviceAImpl_GetCapabilities call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETCAPABILITIES);
    call.iface = (ULONG_PTR)device;
    call.lpDIDevCaps = (ULONG_PTR)lpDIDevCaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetCapabilities(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetCapabilities *c = (struct qemu_IDirectInputDeviceAImpl_GetCapabilities *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetCapabilities(device->host_a, QEMU_G2H(c->lpDIDevCaps));
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetObjectInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pdidoi;
    uint64_t dwObj;
    uint64_t dwHow;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetObjectInfo(IDirectInputDevice8A *iface, LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
{
    struct qemu_IDirectInputDeviceAImpl_GetObjectInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETOBJECTINFO);
    call.iface = (ULONG_PTR)device;
    call.pdidoi = (ULONG_PTR)pdidoi;
    call.dwObj = dwObj;
    call.dwHow = dwHow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetObjectInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetObjectInfo *c = (struct qemu_IDirectInputDeviceAImpl_GetObjectInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetObjectInfo(device->host_a, QEMU_G2H(c->pdidoi), c->dwObj, c->dwHow);
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetObjectInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pdidoi;
    uint64_t dwObj;
    uint64_t dwHow;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetObjectInfo(IDirectInputDevice8W *iface, LPDIDEVICEOBJECTINSTANCEW pdidoi, DWORD dwObj, DWORD dwHow)
{
    struct qemu_IDirectInputDeviceWImpl_GetObjectInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETOBJECTINFO);
    call.iface = (ULONG_PTR)device;
    call.pdidoi = (ULONG_PTR)pdidoi;
    call.dwObj = dwObj;
    call.dwHow = dwHow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetObjectInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetObjectInfo *c = (struct qemu_IDirectInputDeviceWImpl_GetObjectInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetObjectInfo(device->host_w, QEMU_G2H(c->pdidoi), c->dwObj, c->dwHow);
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetDeviceInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pdidi;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetDeviceInfo(IDirectInputDevice8A *iface, LPDIDEVICEINSTANCEA pdidi)
{
    struct qemu_IDirectInputDeviceAImpl_GetDeviceInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETDEVICEINFO);
    call.iface = (ULONG_PTR)device;
    call.pdidi = (ULONG_PTR)pdidi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetDeviceInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetDeviceInfo *c = (struct qemu_IDirectInputDeviceAImpl_GetDeviceInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetDeviceInfo(device->host_a, QEMU_G2H(c->pdidi));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetDeviceInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pdidi;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetDeviceInfo(IDirectInputDevice8W *iface, LPDIDEVICEINSTANCEW pdidi)
{
    struct qemu_IDirectInputDeviceWImpl_GetDeviceInfo call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETDEVICEINFO);
    call.iface = (ULONG_PTR)device;
    call.pdidi = (ULONG_PTR)pdidi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetDeviceInfo(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetDeviceInfo *c = (struct qemu_IDirectInputDeviceWImpl_GetDeviceInfo *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetDeviceInfo(device->host_w, QEMU_G2H(c->pdidi));
}

#endif

struct qemu_IDirectInputDeviceWImpl_GetProperty
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pdiph;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_GetProperty(IDirectInputDevice8W *iface, REFGUID rguid, LPDIPROPHEADER pdiph)
{
    struct qemu_IDirectInputDeviceWImpl_GetProperty call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_GETPROPERTY);
    call.iface = (ULONG_PTR)device;
    call.rguid = (ULONG_PTR)rguid;
    call.pdiph = (ULONG_PTR)pdiph;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_GetProperty(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_GetProperty *c = (struct qemu_IDirectInputDeviceWImpl_GetProperty *)call;
    struct qemu_dinput_device *device;

    /* All DIPROPHEADER based structs have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetProperty(device->host_w, QEMU_G2H(c->rguid), QEMU_G2H(c->pdiph));
}

#endif

struct qemu_IDirectInputDeviceAImpl_GetProperty
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pdiph;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_GetProperty(IDirectInputDevice8A *iface, REFGUID rguid, LPDIPROPHEADER pdiph)
{
    struct qemu_IDirectInputDeviceAImpl_GetProperty call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_GETPROPERTY);
    call.iface = (ULONG_PTR)device;
    call.rguid = (ULONG_PTR)rguid;
    call.pdiph = (ULONG_PTR)pdiph;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_GetProperty(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_GetProperty *c = (struct qemu_IDirectInputDeviceAImpl_GetProperty *)call;
    struct qemu_dinput_device *device;

    /* All DIPROPHEADER based structs have the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_GetProperty(device->host_a, QEMU_G2H(c->rguid), QEMU_G2H(c->pdiph));
}

#endif

struct qemu_IDirectInputDeviceWImpl_Acquire
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_Acquire(IDirectInputDevice8W *iface)
{
    struct qemu_IDirectInputDeviceWImpl_Acquire call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_ACQUIRE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_Acquire(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_Acquire *c = (struct qemu_IDirectInputDeviceWImpl_Acquire *)call;
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Acquire(device->host_w);
}

#endif

struct qemu_IDirectInputDeviceAImpl_Acquire
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_Acquire(IDirectInputDevice8A *iface)
{
    struct qemu_IDirectInputDeviceAImpl_Acquire call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_ACQUIRE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_Acquire(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_Acquire *c = (struct qemu_IDirectInputDeviceAImpl_Acquire *)call;
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_Acquire(device->host_a);
}

#endif

struct qemu_IDirectInputDeviceWImpl_BuildActionMap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiaf;
    uint64_t lpszUserName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_BuildActionMap(IDirectInputDevice8W *iface, LPDIACTIONFORMATW lpdiaf, LPCWSTR lpszUserName, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_BuildActionMap call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_BUILDACTIONMAP);
    call.iface = (ULONG_PTR)device;
    call.lpdiaf = (ULONG_PTR)lpdiaf;
    call.lpszUserName = (ULONG_PTR)lpszUserName;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_BuildActionMap(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_BuildActionMap *c = (struct qemu_IDirectInputDeviceWImpl_BuildActionMap *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_BuildActionMap(device->host_w, QEMU_G2H(c->lpdiaf), QEMU_G2H(c->lpszUserName), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_BuildActionMap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiaf;
    uint64_t lpszUserName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_BuildActionMap(IDirectInputDevice8A *iface, LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_BuildActionMap call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_BUILDACTIONMAP);
    call.iface = (ULONG_PTR)device;
    call.lpdiaf = (ULONG_PTR)lpdiaf;
    call.lpszUserName = (ULONG_PTR)lpszUserName;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_BuildActionMap(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_BuildActionMap *c = (struct qemu_IDirectInputDeviceAImpl_BuildActionMap *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_BuildActionMap(device->host_a, QEMU_G2H(c->lpdiaf), QEMU_G2H(c->lpszUserName), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceWImpl_SetActionMap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiaf;
    uint64_t lpszUserName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceWImpl_SetActionMap(IDirectInputDevice8W *iface, LPDIACTIONFORMATW lpdiaf, LPCWSTR lpszUserName, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceWImpl_SetActionMap call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEWIMPL_SETACTIONMAP);
    call.iface = (ULONG_PTR)device;
    call.lpdiaf = (ULONG_PTR)lpdiaf;
    call.lpszUserName = (ULONG_PTR)lpszUserName;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceWImpl_SetActionMap(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceWImpl_SetActionMap *c = (struct qemu_IDirectInputDeviceWImpl_SetActionMap *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetActionMap(device->host_w, QEMU_G2H(c->lpdiaf), QEMU_G2H(c->lpszUserName), c->dwFlags);
}

#endif

struct qemu_IDirectInputDeviceAImpl_SetActionMap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiaf;
    uint64_t lpszUserName;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputDeviceAImpl_SetActionMap(IDirectInputDevice8A *iface, LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
{
    struct qemu_IDirectInputDeviceAImpl_SetActionMap call;
    struct qemu_dinput_device *device = impl_from_IDirectInputDevice8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTDEVICEAIMPL_SETACTIONMAP);
    call.iface = (ULONG_PTR)device;
    call.lpdiaf = (ULONG_PTR)lpdiaf;
    call.lpszUserName = (ULONG_PTR)lpszUserName;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputDeviceAImpl_SetActionMap(struct qemu_syscall *call)
{
    struct qemu_IDirectInputDeviceAImpl_SetActionMap *c = (struct qemu_IDirectInputDeviceAImpl_SetActionMap *)call;
    struct qemu_dinput_device *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IDirectInputDevice8_SetActionMap(device->host_a, QEMU_G2H(c->lpdiaf), QEMU_G2H(c->lpszUserName), c->dwFlags);
}

#endif


#ifdef QEMU_DLL_GUEST

static const IDirectInputDevice8AVtbl device_a_vtbl =
{
    IDirectInputDeviceAImpl_QueryInterface,
    IDirectInputDeviceAImpl_AddRef,
    IDirectInputDeviceAImpl_Release,
    IDirectInputDeviceAImpl_GetCapabilities,
    IDirectInputDeviceAImpl_EnumObjects,
    IDirectInputDeviceAImpl_GetProperty,
    IDirectInputDeviceAImpl_SetProperty,
    IDirectInputDeviceAImpl_Acquire,
    IDirectInputDeviceAImpl_Unacquire,
    IDirectInputDeviceAImpl_GetDeviceState,
    IDirectInputDeviceAImpl_GetDeviceData,
    IDirectInputDeviceAImpl_SetDataFormat,
    IDirectInputDeviceAImpl_SetEventNotification,
    IDirectInputDeviceAImpl_SetCooperativeLevel,
    IDirectInputDeviceAImpl_GetObjectInfo,
    IDirectInputDeviceAImpl_GetDeviceInfo,
    IDirectInputDeviceAImpl_RunControlPanel,
    IDirectInputDeviceAImpl_Initialize,
    IDirectInputDeviceAImpl_CreateEffect,
    IDirectInputDeviceAImpl_EnumEffects,
    IDirectInputDeviceAImpl_GetEffectInfo,
    IDirectInputDeviceAImpl_GetForceFeedbackState,
    IDirectInputDeviceAImpl_SendForceFeedbackCommand,
    IDirectInputDeviceAImpl_EnumCreatedEffectObjects,
    IDirectInputDeviceAImpl_Escape,
    IDirectInputDeviceAImpl_Poll,
    IDirectInputDeviceAImpl_SendDeviceData,
    IDirectInputDeviceAImpl_EnumEffectsInFile,
    IDirectInputDeviceAImpl_WriteEffectToFile,
    IDirectInputDeviceAImpl_BuildActionMap,
    IDirectInputDeviceAImpl_SetActionMap,
    IDirectInputDeviceAImpl_GetImageInfo
};

static const IDirectInputDevice8WVtbl device_w_vtbl =
{
    IDirectInputDeviceWImpl_QueryInterface,
    IDirectInputDeviceWImpl_AddRef,
    IDirectInputDeviceWImpl_Release,
    IDirectInputDeviceWImpl_GetCapabilities,
    IDirectInputDeviceWImpl_EnumObjects,
    IDirectInputDeviceWImpl_GetProperty,
    IDirectInputDeviceWImpl_SetProperty,
    IDirectInputDeviceWImpl_Acquire,
    IDirectInputDeviceWImpl_Unacquire,
    IDirectInputDeviceWImpl_GetDeviceState,
    IDirectInputDeviceWImpl_GetDeviceData,
    IDirectInputDeviceWImpl_SetDataFormat,
    IDirectInputDeviceWImpl_SetEventNotification,
    IDirectInputDeviceWImpl_SetCooperativeLevel,
    IDirectInputDeviceWImpl_GetObjectInfo,
    IDirectInputDeviceWImpl_GetDeviceInfo,
    IDirectInputDeviceWImpl_RunControlPanel,
    IDirectInputDeviceWImpl_Initialize,
    IDirectInputDeviceWImpl_CreateEffect,
    IDirectInputDeviceWImpl_EnumEffects,
    IDirectInputDeviceWImpl_GetEffectInfo,
    IDirectInputDeviceWImpl_GetForceFeedbackState,
    IDirectInputDeviceWImpl_SendForceFeedbackCommand,
    IDirectInputDeviceWImpl_EnumCreatedEffectObjects,
    IDirectInputDeviceWImpl_Escape,
    IDirectInputDeviceWImpl_Poll,
    IDirectInputDeviceWImpl_SendDeviceData,
    IDirectInputDeviceWImpl_EnumEffectsInFile,
    IDirectInputDeviceWImpl_WriteEffectToFile,
    IDirectInputDeviceWImpl_BuildActionMap,
    IDirectInputDeviceWImpl_SetActionMap,
    IDirectInputDeviceWImpl_GetImageInfo
};

void qemu_dinput_device_guest_init(struct qemu_dinput_device *device)
{
    device->IDirectInputDevice8A_iface.lpVtbl = &device_a_vtbl;
    device->IDirectInputDevice8W_iface.lpVtbl = &device_w_vtbl;
}

#endif
