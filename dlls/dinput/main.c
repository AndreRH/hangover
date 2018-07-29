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
#define INITGUID

#include <windows.h>
#include <stdio.h>
#include <dinput.h>
#include "dinputd.h"

#include "thunk/qemu_windows.h"
#include "thunk/qemu_dinput.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dinput.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dinput);

struct qemu_IDirectInputImpl_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type;
    uint64_t callback;
    uint64_t ref;
    uint64_t flags;
    uint64_t wrapper;
};

struct qemu_IDirectInputImpl_EnumDevices_cb
{
    uint64_t cb;
    uint64_t di;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dinput *impl_from_IDirectInput7A(IDirectInput7A *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput, IDirectInput7A_iface);
}

static inline struct qemu_dinput *impl_from_IDirectInput7W(IDirectInput7W *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput, IDirectInput7W_iface);
}

static inline struct qemu_dinput *impl_from_IDirectInput8A(IDirectInput8A *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput, IDirectInput8A_iface);
}

static inline struct qemu_dinput *impl_from_IDirectInput8W(IDirectInput8W *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput, IDirectInput8W_iface);
}

static inline struct qemu_dinput *impl_from_IDirectInputJoyConfig8(IDirectInputJoyConfig8 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dinput, IDirectInputJoyConfig8_iface);
}

/* FIXME: Native dinput has a hand-written assembler callback wrapper for whatever reasons. */
static BOOL __fastcall EnumDevices_guest_cb(struct qemu_IDirectInputImpl_EnumDevices_cb *data)
{
    LPDIENUMDEVICESCALLBACKW cb = (LPDIENUMDEVICESCALLBACKW)(ULONG_PTR)data->cb;
    return cb((const DIDEVICEINSTANCEW *)(ULONG_PTR)data->di, (void *)(ULONG_PTR)data->data);
}

static HRESULT WINAPI IDirectInputAImpl_EnumDevices(IDirectInput7A *iface, DWORD type,
        LPDIENUMDEVICESCALLBACKA callback, void *ref, DWORD flags)
{
    struct qemu_IDirectInputImpl_EnumDevices call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_ENUMDEVICES);
    call.iface = (ULONG_PTR)dinput;
    call.type = type;
    call.callback = (ULONG_PTR)callback;
    call.ref = (ULONG_PTR)ref;
    call.flags = flags;
    call.wrapper = (ULONG_PTR)EnumDevices_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static HRESULT WINAPI IDirectInputWImpl_EnumDevices(IDirectInput7W *iface, DWORD type,
        LPDIENUMDEVICESCALLBACKW callback, void *ref, DWORD flags)
{
    struct qemu_IDirectInputImpl_EnumDevices call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_ENUMDEVICES);
    call.iface = (ULONG_PTR)dinput;
    call.type = type;
    call.callback = (ULONG_PTR)callback;
    call.ref = (ULONG_PTR)ref;
    call.flags = flags;
    call.wrapper = (ULONG_PTR)EnumDevices_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct EnumDevices_host_ctx
{
    uint64_t guest_cb;
    uint64_t guest_data;
    uint64_t wrapper;
};

static BOOL CALLBACK EnumDevices_host_cb(const DIDEVICEINSTANCEW *instance, void *data)
{
    struct EnumDevices_host_ctx *ctx = data;
    BOOL ret;
    struct qemu_IDirectInputImpl_EnumDevices_cb call;

    call.cb = ctx->guest_cb;
    call.di = QEMU_H2G(instance);
    call.data = ctx->guest_data;

    WINE_TRACE("Calling guest callback %p(%p, %p).\n", (void *)call.cb, instance, (void *)call.data);
    ret = qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %u.\n", ret);

    return ret;
}

void qemu_IDirectInputImpl_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_IDirectInputImpl_EnumDevices *c = (struct qemu_IDirectInputImpl_EnumDevices *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);
    struct EnumDevices_host_ctx ctx;

    WINE_TRACE("\n");
    ctx.guest_cb = c->callback;
    ctx.guest_data = c->ref;
    ctx.wrapper = c->wrapper;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_ENUMDEVICES))
    {
        c->super.iret = IDirectInput_EnumDevices(dinput->host_7w, c->type,
                c->callback ? EnumDevices_host_cb : NULL, &ctx, c->flags);
    }
    else
    {
        c->super.iret = IDirectInput_EnumDevices(dinput->host_7a, c->type,
                c->callback ? (LPDIENUMDEVICESCALLBACKA)EnumDevices_host_cb : NULL, &ctx, c->flags);
    }
}

#endif

struct qemu_IDirectInputAImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IDirectInputAImpl_AddRef(IDirectInput7A *iface)
{
    struct qemu_IDirectInputAImpl_AddRef call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_ADDREF);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputAImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IDirectInputAImpl_AddRef *c = (struct qemu_IDirectInputAImpl_AddRef *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput_AddRef(dinput->host_7a);
}

#endif

struct qemu_IDirectInputWImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IDirectInputWImpl_AddRef(IDirectInput7W *iface)
{
    struct qemu_IDirectInputWImpl_AddRef call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_ADDREF);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputWImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IDirectInputWImpl_AddRef *c = (struct qemu_IDirectInputWImpl_AddRef *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput_AddRef(dinput->host_7w);
}

#endif

struct qemu_IDirectInputImpl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IDirectInputAImpl_Release(IDirectInput7A *iface)
{
    struct qemu_IDirectInputImpl_Release call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_RELEASE);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static ULONG WINAPI IDirectInputWImpl_Release(IDirectInput7W *iface)
{
    struct qemu_IDirectInputImpl_Release call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_RELEASE);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static ULONG WINAPI IDirectInput8AImpl_Release(IDirectInput8A *iface)
{
    struct qemu_IDirectInputImpl_Release call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_RELEASE);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

static ULONG WINAPI IDirectInput8WImpl_Release(IDirectInput8W *iface)
{
    struct qemu_IDirectInputImpl_Release call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_RELEASE);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG qemu_IDirectInputImpl_Release_internal(struct qemu_dinput *dinput)
{
    ULONG ref = IDirectInput_Release(dinput->host_7a);

    if (!ref)
    {
        WINE_TRACE("Destroying dinput wrapper %p.\n", dinput);
        HeapFree(GetProcessHeap(), 0, dinput);
    }
    return ref;
}

void qemu_IDirectInputImpl_Release(struct qemu_syscall *call)
{
    struct qemu_IDirectInputImpl_Release *c = (struct qemu_IDirectInputImpl_Release *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_TRACE("\n");
    c->super.iret = qemu_IDirectInputImpl_Release_internal(dinput);
}

#endif

struct qemu_IDirectInputAImpl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputAImpl_QueryInterface(IDirectInput7A *iface, const IID *iid, void **obj)
{
    struct qemu_IDirectInputAImpl_QueryInterface call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)dinput;
    call.iid = (ULONG_PTR)iid;
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
    {
        /* Don't AddRef, the host call took care of this already. */
        if (IsEqualGUID(&IID_IUnknown, iid)
                || IsEqualGUID(&IID_IDirectInputA,  iid)
                || IsEqualGUID(&IID_IDirectInput2A, iid)
                || IsEqualGUID(&IID_IDirectInput7A, iid))
        {
            *obj = &dinput->IDirectInput7A_iface;
        }
        else if (IsEqualGUID(&IID_IDirectInputW,  iid)
                || IsEqualGUID(&IID_IDirectInput2W, iid)
                || IsEqualGUID(&IID_IDirectInput7W, iid))
        {
            *obj = &dinput->IDirectInput7W_iface;
        }
        else if (IsEqualGUID(&IID_IDirectInput8A, iid))
        {
            *obj = &dinput->IDirectInput8A_iface;
        }
        else if (IsEqualGUID(&IID_IDirectInput8W, iid))
        {
            *obj = &dinput->IDirectInput8W_iface;
        }
        else if (IsEqualGUID(&IID_IDirectInputJoyConfig8, iid))
        {
            *obj = &dinput->IDirectInputJoyConfig8_iface;
        }
    }
    else if (call.super.iret != E_POINTER)
    {
        *obj = NULL;
    }

    return call.super.iret;
}

static HRESULT WINAPI IDirectInput8WImpl_QueryInterface(IDirectInput8W *iface, REFIID riid, LPVOID *ppobj)
{
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    return IDirectInputAImpl_QueryInterface(&dinput->IDirectInput7A_iface, riid, ppobj);
}

static HRESULT WINAPI IDirectInput8AImpl_QueryInterface(IDirectInput8A *iface, REFIID riid, LPVOID *ppobj)
{
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    return IDirectInputAImpl_QueryInterface(&dinput->IDirectInput7A_iface, riid, ppobj);
}

static HRESULT WINAPI IDirectInputWImpl_QueryInterface(IDirectInput7W *iface, REFIID riid, LPVOID *ppobj)
{
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    return IDirectInputAImpl_QueryInterface(&dinput->IDirectInput7A_iface, riid, ppobj);
}

#else

void qemu_IDirectInputAImpl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IDirectInputAImpl_QueryInterface *c = (struct qemu_IDirectInputAImpl_QueryInterface *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);
    void *obj;

    WINE_TRACE("\n");

    c->super.iret = IDirectInput_QueryInterface(dinput->host_7a, QEMU_G2H(c->iid), c->obj ? &obj : NULL);
}

#endif

struct qemu_IDirectInputAImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hinst;
    uint64_t version;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputAImpl_Initialize(IDirectInput7A *iface, HINSTANCE hinst, DWORD version)
{
    struct qemu_IDirectInputAImpl_Initialize call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)dinput;
    call.hinst = (ULONG_PTR)hinst;
    call.version = version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputAImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectInputAImpl_Initialize *c = (struct qemu_IDirectInputAImpl_Initialize *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    /* hinst needs to be non-NULL, but is not otherwise used by Wine. */
    WINE_TRACE("\n");

    c->super.iret = IDirectInput_Initialize(dinput->host_7a, QEMU_G2H(c->hinst), c->version);
}

#endif

struct qemu_IDirectInputWImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hinst;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputWImpl_Initialize(IDirectInput7W *iface, HINSTANCE hinst, DWORD x)
{
    struct qemu_IDirectInputWImpl_Initialize call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)dinput;
    call.hinst = (ULONG_PTR)hinst;
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputWImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectInputWImpl_Initialize *c = (struct qemu_IDirectInputWImpl_Initialize *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    /* hinst needs to be non-NULL, but is not otherwise used by Wine. */
    WINE_TRACE("\n");

    c->super.iret = IDirectInput_Initialize(dinput->host_7w, QEMU_G2H(c->hinst), c->x);
}

#endif

struct qemu_IDirectInputAImpl_GetDeviceStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputAImpl_GetDeviceStatus(IDirectInput7A *iface, const GUID *guid)
{
    struct qemu_IDirectInputAImpl_GetDeviceStatus call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_GETDEVICESTATUS);
    call.iface = (ULONG_PTR)dinput;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputAImpl_GetDeviceStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectInputAImpl_GetDeviceStatus *c = (struct qemu_IDirectInputAImpl_GetDeviceStatus *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_TRACE("\n");

    c->super.iret = IDirectInput_GetDeviceStatus(dinput->host_7a, QEMU_G2H(c->guid));
}

#endif

struct qemu_IDirectInputWImpl_GetDeviceStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputWImpl_GetDeviceStatus(IDirectInput7W *iface, const GUID *guid)
{
    struct qemu_IDirectInputWImpl_GetDeviceStatus call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_GETDEVICESTATUS);
    call.iface = (ULONG_PTR)dinput;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputWImpl_GetDeviceStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectInputWImpl_GetDeviceStatus *c = (struct qemu_IDirectInputWImpl_GetDeviceStatus *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_TRACE("\n");

    c->super.iret = IDirectInput_GetDeviceStatus(dinput->host_7w, QEMU_G2H(c->guid));
}

#endif

struct qemu_IDirectInputAImpl_RunControlPanel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputAImpl_RunControlPanel(IDirectInput7A *iface, HWND hwndOwner, DWORD dwFlags)
{
    struct qemu_IDirectInputAImpl_RunControlPanel call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_RUNCONTROLPANEL);
    call.iface = (ULONG_PTR)dinput;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputAImpl_RunControlPanel(struct qemu_syscall *call)
{
    struct qemu_IDirectInputAImpl_RunControlPanel *c = (struct qemu_IDirectInputAImpl_RunControlPanel *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput_RunControlPanel(dinput->host_7a, QEMU_G2H(c->hwndOwner), c->dwFlags);
}

#endif

struct qemu_IDirectInputWImpl_RunControlPanel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputWImpl_RunControlPanel(IDirectInput7W *iface, HWND hwndOwner, DWORD dwFlags)
{
    struct qemu_IDirectInputWImpl_RunControlPanel call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_RUNCONTROLPANEL);
    call.iface = (ULONG_PTR)dinput;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInputWImpl_RunControlPanel(struct qemu_syscall *call)
{
    struct qemu_IDirectInputWImpl_RunControlPanel *c = (struct qemu_IDirectInputWImpl_RunControlPanel *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput_RunControlPanel(dinput->host_7w, QEMU_G2H(c->hwndOwner), c->dwFlags);
}

#endif

struct qemu_IDirectInput2AImpl_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pszName;
    uint64_t pguidInstance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput2AImpl_FindDevice(IDirectInput7A *iface, REFGUID rguid, LPCSTR pszName, LPGUID pguidInstance)
{
    struct qemu_IDirectInput2AImpl_FindDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT2AIMPL_FINDDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.pszName = (ULONG_PTR)pszName;
    call.pguidInstance = (ULONG_PTR)pguidInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput2AImpl_FindDevice(struct qemu_syscall *call)
{
    struct qemu_IDirectInput2AImpl_FindDevice *c = (struct qemu_IDirectInput2AImpl_FindDevice *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput2_FindDevice(dinput->host_7a, QEMU_G2H(c->rguid), QEMU_G2H(c->pszName), QEMU_G2H(c->pguidInstance));
}

#endif

struct qemu_IDirectInput2WImpl_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pszName;
    uint64_t pguidInstance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput2WImpl_FindDevice(IDirectInput7W *iface, REFGUID rguid, LPCWSTR pszName, LPGUID pguidInstance)
{
    struct qemu_IDirectInput2WImpl_FindDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT2WIMPL_FINDDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.pszName = (ULONG_PTR)pszName;
    call.pguidInstance = (ULONG_PTR)pguidInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput2WImpl_FindDevice(struct qemu_syscall *call)
{
    struct qemu_IDirectInput2WImpl_FindDevice *c = (struct qemu_IDirectInput2WImpl_FindDevice *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput2_FindDevice(dinput->host_7w, QEMU_G2H(c->rguid), QEMU_G2H(c->pszName), QEMU_G2H(c->pguidInstance));
}

#endif

struct qemu_IDirectInput7AImpl_CreateDeviceEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t riid;
    uint64_t pvOut;
    uint64_t lpUnknownOuter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput7AImpl_CreateDeviceEx(IDirectInput7A *iface, REFGUID rguid, REFIID riid, LPVOID* pvOut, LPUNKNOWN lpUnknownOuter)
{
    struct qemu_IDirectInput7AImpl_CreateDeviceEx call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT7AIMPL_CREATEDEVICEEX);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.riid = (ULONG_PTR)riid;
    call.pvOut = (ULONG_PTR)pvOut;
    call.lpUnknownOuter = (ULONG_PTR)lpUnknownOuter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput7AImpl_CreateDeviceEx(struct qemu_syscall *call)
{
    struct qemu_IDirectInput7AImpl_CreateDeviceEx *c = (struct qemu_IDirectInput7AImpl_CreateDeviceEx *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput7_CreateDeviceEx(dinput->host_7a, QEMU_G2H(c->rguid), QEMU_G2H(c->riid), QEMU_G2H(c->pvOut), QEMU_G2H(c->lpUnknownOuter));
}

#endif

struct qemu_IDirectInput7WImpl_CreateDeviceEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t riid;
    uint64_t pvOut;
    uint64_t lpUnknownOuter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput7WImpl_CreateDeviceEx(IDirectInput7W *iface, REFGUID rguid, REFIID riid, LPVOID* pvOut, LPUNKNOWN lpUnknownOuter)
{
    struct qemu_IDirectInput7WImpl_CreateDeviceEx call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT7WIMPL_CREATEDEVICEEX);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.riid = (ULONG_PTR)riid;
    call.pvOut = (ULONG_PTR)pvOut;
    call.lpUnknownOuter = (ULONG_PTR)lpUnknownOuter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput7WImpl_CreateDeviceEx(struct qemu_syscall *call)
{
    struct qemu_IDirectInput7WImpl_CreateDeviceEx *c = (struct qemu_IDirectInput7WImpl_CreateDeviceEx *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput7_CreateDeviceEx(dinput->host_7w, QEMU_G2H(c->rguid), QEMU_G2H(c->riid), QEMU_G2H(c->pvOut), QEMU_G2H(c->lpUnknownOuter));
}

#endif

struct qemu_IDirectInputImpl_CreateDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pdev;
    uint64_t punk;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInputAImpl_CreateDevice(IDirectInput7A *iface, const GUID *rguid,
        IDirectInputDeviceA **pdev, IUnknown *punk)
{
    struct qemu_IDirectInputImpl_CreateDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7A(iface);
    struct qemu_dinput_device *device;

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTAIMPL_CREATEDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.punk = (ULONG_PTR)punk;
    call.pdev = (ULONG_PTR)pdev;

    if (pdev)
        *pdev = NULL;

    qemu_syscall(&call.super);
    device = (struct qemu_dinput_device *)(ULONG_PTR)call.pdev;

    if (SUCCEEDED(call.super.iret))
    {
        qemu_dinput_device_guest_init(device);
        *pdev = (IDirectInputDeviceA *)&device->IDirectInputDevice8A_iface;
    }

    return call.super.iret;
}

static HRESULT WINAPI IDirectInputWImpl_CreateDevice(IDirectInput7W *iface, const GUID *rguid,
        IDirectInputDeviceW **pdev, IUnknown *punk)
{
    struct qemu_IDirectInputImpl_CreateDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput7W(iface);
    struct qemu_dinput_device *device;

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_CREATEDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.punk = (ULONG_PTR)punk;
    call.pdev = (ULONG_PTR)pdev;

    if (pdev)
        *pdev = NULL;

    qemu_syscall(&call.super);
    device = (struct qemu_dinput_device *)(ULONG_PTR)call.pdev;

    if (SUCCEEDED(call.super.iret))
    {
        qemu_dinput_device_guest_init(device);
        *pdev = (IDirectInputDeviceW *)&device->IDirectInputDevice8W_iface;
    }

    return call.super.iret;
}

static HRESULT WINAPI IDirectInput8AImpl_CreateDevice(IDirectInput8A *iface, REFGUID rguid,
        IDirectInputDevice8A **pdev, IUnknown *punk)
{
    struct qemu_IDirectInputImpl_CreateDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);
    struct qemu_dinput_device *device;

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_CREATEDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.punk = (ULONG_PTR)punk;
    call.pdev = (ULONG_PTR)pdev;

    if (pdev)
        *pdev = NULL;

    qemu_syscall(&call.super);
    device = (struct qemu_dinput_device *)(ULONG_PTR)call.pdev;

    if (SUCCEEDED(call.super.iret))
    {
        qemu_dinput_device_guest_init(device);
        *pdev = &device->IDirectInputDevice8A_iface;
    }

    return call.super.iret;
}

static HRESULT WINAPI IDirectInput8WImpl_CreateDevice(IDirectInput8W *iface, REFGUID rguid,
        IDirectInputDevice8W **pdev, IUnknown *punk)
{
    struct qemu_IDirectInputImpl_CreateDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);
    struct qemu_dinput_device *device;

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_CREATEDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.punk = (ULONG_PTR)punk;
    call.pdev = (ULONG_PTR)pdev;

    if (pdev)
        *pdev = NULL;

    qemu_syscall(&call.super);
    device = (struct qemu_dinput_device *)(ULONG_PTR)call.pdev;

    if (SUCCEEDED(call.super.iret))
    {
        qemu_dinput_device_guest_init(device);
        *pdev = &device->IDirectInputDevice8W_iface;
    }

    return call.super.iret;
}

#else

void qemu_IDirectInputImpl_CreateDevice(struct qemu_syscall *call)
{
    struct qemu_IDirectInputImpl_CreateDevice *c = (struct qemu_IDirectInputImpl_CreateDevice *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);
    struct qemu_dinput_device *device;

    WINE_TRACE("\n");

    device = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*device));
    if (!device)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    device->parent = dinput;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_CREATEDEVICE))
    {
        c->super.iret = IDirectInput8_CreateDevice(dinput->host_8w, QEMU_G2H(c->rguid),
                c->pdev ? &device->host_w : NULL, QEMU_G2H(c->punk));
    }
    else if (c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_CREATEDEVICE))
    {
        c->super.iret = IDirectInput8_CreateDevice(dinput->host_8a, QEMU_G2H(c->rguid),
                c->pdev ? &device->host_a : NULL, QEMU_G2H(c->punk));
    }
    else if (c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_CREATEDEVICE))
    {
        c->super.iret = IDirectInput_CreateDevice(dinput->host_7w, QEMU_G2H(c->rguid),
                c->pdev ? (IDirectInputDeviceW **)&device->host_w : NULL, QEMU_G2H(c->punk));
    }
    else
    {
        c->super.iret = IDirectInput_CreateDevice(dinput->host_7a, QEMU_G2H(c->rguid),
                c->pdev ? (IDirectInputDeviceA **)&device->host_a : NULL, QEMU_G2H(c->punk));
    }

    if (FAILED(c->super.iret))
    {
        HeapFree(GetProcessHeap(), 0, device);
        return;
    }

    if (c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUTWIMPL_CREATEDEVICE)
            || c->super.id == QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_CREATEDEVICE))
        IDirectInputDevice8_QueryInterface(device->host_w, &IID_IDirectInputDevice8A, (void **)&device->host_a);
    else
        IDirectInputDevice8_QueryInterface(device->host_a, &IID_IDirectInputDevice8W, (void **)&device->host_w);

    /* We want to return a device with refcount 1. */
    IDirectInputDevice8_Release(device->host_a);

    c->pdev = QEMU_H2G(device);
}

#endif

struct qemu_IDirectInput8AImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IDirectInput8AImpl_AddRef(IDirectInput8A *iface)
{
    struct qemu_IDirectInput8AImpl_AddRef call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_ADDREF);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_AddRef *c = (struct qemu_IDirectInput8AImpl_AddRef *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_AddRef(dinput->host_8a);
}

#endif

struct qemu_IDirectInput8WImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IDirectInput8WImpl_AddRef(IDirectInput8W *iface)
{
    struct qemu_IDirectInput8WImpl_AddRef call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_ADDREF);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_AddRef *c = (struct qemu_IDirectInput8WImpl_AddRef *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_AddRef(dinput->host_8w);
}

#endif

struct qemu_IDirectInput8AImpl_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwDevType;
    uint64_t lpCallback;
    uint64_t pvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8AImpl_EnumDevices(IDirectInput8A *iface, DWORD dwDevType,
        LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    struct qemu_IDirectInput8AImpl_EnumDevices call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_ENUMDEVICES);
    call.iface = (ULONG_PTR)dinput;
    call.dwDevType = dwDevType;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.pvRef = (ULONG_PTR)pvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_EnumDevices *c = (struct qemu_IDirectInput8AImpl_EnumDevices *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_EnumDevices(dinput->host_8a, c->dwDevType, QEMU_G2H(c->lpCallback), QEMU_G2H(c->pvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInput8WImpl_EnumDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwDevType;
    uint64_t lpCallback;
    uint64_t pvRef;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8WImpl_EnumDevices(IDirectInput8W *iface, DWORD dwDevType,
        LPDIENUMDEVICESCALLBACKW lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    struct qemu_IDirectInput8WImpl_EnumDevices call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_ENUMDEVICES);
    call.iface = (ULONG_PTR)dinput;
    call.dwDevType = dwDevType;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.pvRef = (ULONG_PTR)pvRef;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_EnumDevices(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_EnumDevices *c = (struct qemu_IDirectInput8WImpl_EnumDevices *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_EnumDevices(dinput->host_8w, c->dwDevType, QEMU_G2H(c->lpCallback), QEMU_G2H(c->pvRef), c->dwFlags);
}

#endif

struct qemu_IDirectInput8AImpl_GetDeviceStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8AImpl_GetDeviceStatus(IDirectInput8A *iface, REFGUID rguid)
{
    struct qemu_IDirectInput8AImpl_GetDeviceStatus call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_GETDEVICESTATUS);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_GetDeviceStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_GetDeviceStatus *c = (struct qemu_IDirectInput8AImpl_GetDeviceStatus *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_GetDeviceStatus(dinput->host_8a, QEMU_G2H(c->rguid));
}

#endif

struct qemu_IDirectInput8WImpl_GetDeviceStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8WImpl_GetDeviceStatus(IDirectInput8W *iface, REFGUID rguid)
{
    struct qemu_IDirectInput8WImpl_GetDeviceStatus call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_GETDEVICESTATUS);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_GetDeviceStatus(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_GetDeviceStatus *c = (struct qemu_IDirectInput8WImpl_GetDeviceStatus *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_GetDeviceStatus(dinput->host_8w, QEMU_G2H(c->rguid));
}

#endif

struct qemu_IDirectInput8AImpl_RunControlPanel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8AImpl_RunControlPanel(IDirectInput8A *iface, HWND hwndOwner, DWORD dwFlags)
{
    struct qemu_IDirectInput8AImpl_RunControlPanel call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_RUNCONTROLPANEL);
    call.iface = (ULONG_PTR)dinput;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_RunControlPanel(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_RunControlPanel *c = (struct qemu_IDirectInput8AImpl_RunControlPanel *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_RunControlPanel(dinput->host_8a, QEMU_G2H(c->hwndOwner), c->dwFlags);
}

#endif

struct qemu_IDirectInput8WImpl_RunControlPanel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwndOwner;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8WImpl_RunControlPanel(IDirectInput8W *iface, HWND hwndOwner, DWORD dwFlags)
{
    struct qemu_IDirectInput8WImpl_RunControlPanel call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_RUNCONTROLPANEL);
    call.iface = (ULONG_PTR)dinput;
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_RunControlPanel(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_RunControlPanel *c = (struct qemu_IDirectInput8WImpl_RunControlPanel *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_RunControlPanel(dinput->host_8w, QEMU_G2H(c->hwndOwner), c->dwFlags);
}

#endif

struct qemu_IDirectInput8AImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hinst;
    uint64_t version;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8AImpl_Initialize(IDirectInput8A *iface, HINSTANCE hinst, DWORD version)
{
    struct qemu_IDirectInput8AImpl_Initialize call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)dinput;
    call.hinst = (ULONG_PTR)hinst;
    call.version = version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_Initialize *c = (struct qemu_IDirectInput8AImpl_Initialize *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    /* hinst needs to be non-NULL, but is not otherwise used by Wine. */
    WINE_TRACE("\n");

    c->super.iret = IDirectInput8_Initialize(dinput->host_8a, QEMU_G2H(c->hinst), c->version);
}

#endif

struct qemu_IDirectInput8WImpl_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hinst;
    uint64_t version;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8WImpl_Initialize(IDirectInput8W *iface, HINSTANCE hinst, DWORD version)
{
    struct qemu_IDirectInput8WImpl_Initialize call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_INITIALIZE);
    call.iface = (ULONG_PTR)dinput;
    call.hinst = (ULONG_PTR)hinst;
    call.version = version;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_Initialize(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_Initialize *c = (struct qemu_IDirectInput8WImpl_Initialize *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    /* hinst needs to be non-NULL, but is not otherwise used by Wine. */
    WINE_TRACE("\n");

    c->super.iret = IDirectInput8_Initialize(dinput->host_8w, QEMU_G2H(c->hinst), c->version);
}

#endif

struct qemu_IDirectInput8AImpl_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pszName;
    uint64_t pguidInstance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8AImpl_FindDevice(IDirectInput8A *iface, REFGUID rguid, LPCSTR pszName, LPGUID pguidInstance)
{
    struct qemu_IDirectInput8AImpl_FindDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_FINDDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.pszName = (ULONG_PTR)pszName;
    call.pguidInstance = (ULONG_PTR)pguidInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_FindDevice(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_FindDevice *c = (struct qemu_IDirectInput8AImpl_FindDevice *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_FindDevice(dinput->host_8a, QEMU_G2H(c->rguid), QEMU_G2H(c->pszName), QEMU_G2H(c->pguidInstance));
}

#endif

struct qemu_IDirectInput8WImpl_FindDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rguid;
    uint64_t pszName;
    uint64_t pguidInstance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8WImpl_FindDevice(IDirectInput8W *iface, REFGUID rguid, LPCWSTR pszName, LPGUID pguidInstance)
{
    struct qemu_IDirectInput8WImpl_FindDevice call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_FINDDEVICE);
    call.iface = (ULONG_PTR)dinput;
    call.rguid = (ULONG_PTR)rguid;
    call.pszName = (ULONG_PTR)pszName;
    call.pguidInstance = (ULONG_PTR)pguidInstance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_FindDevice(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_FindDevice *c = (struct qemu_IDirectInput8WImpl_FindDevice *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_FindDevice(dinput->host_8w, QEMU_G2H(c->rguid), QEMU_G2H(c->pszName), QEMU_G2H(c->pguidInstance));
}

#endif

struct qemu_IDirectInput8AImpl_EnumDevicesBySemantics
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ptszUserName;
    uint64_t lpdiActionFormat;
    uint64_t lpCallback;
    uint64_t pvRef;
    uint64_t dwFlags;
    uint64_t wrapper;
};

struct qemu_IDirectInput8Impl_EnumDevicesBySemantics_cb
{
    uint64_t cb;
    uint64_t instance;
    uint64_t dev;
    uint64_t flags;
    uint64_t remain;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static BOOL __fastcall EnumDevicesBySemanticsA_guest_cb(
        const struct qemu_IDirectInput8Impl_EnumDevicesBySemantics_cb *data)
{
    LPDIENUMDEVICESBYSEMANTICSCBA cb = (LPDIENUMDEVICESBYSEMANTICSCBA)(ULONG_PTR)data->cb;
    struct qemu_dinput_device *device;

    device = (struct qemu_dinput_device *)(ULONG_PTR)data->dev;
    qemu_dinput_device_guest_init(device);

    return cb((const DIDEVICEINSTANCEA *)(ULONG_PTR)data->instance, &device->IDirectInputDevice8A_iface,
            data->flags, data->remain, (void *)(ULONG_PTR)data->ctx);
}

static HRESULT WINAPI IDirectInput8AImpl_EnumDevicesBySemantics(IDirectInput8A *iface, LPCSTR ptszUserName,
        LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    struct qemu_IDirectInput8AImpl_EnumDevicesBySemantics call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_ENUMDEVICESBYSEMANTICS);
    call.iface = (ULONG_PTR)dinput;
    call.ptszUserName = (ULONG_PTR)ptszUserName;
    call.lpdiActionFormat = (ULONG_PTR)lpdiActionFormat;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.pvRef = (ULONG_PTR)pvRef;
    call.dwFlags = dwFlags;
    call.wrapper = (ULONG_PTR)EnumDevicesBySemanticsA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct EnumDevicesBySemantics_cb_data
{
    uint64_t guest_func, wrapper, guest_ctx;
    struct qemu_dinput *dinput;
};

static BOOL CALLBACK EnumDevicesBySemanticsA_host_cb(const DIDEVICEINSTANCEA *inst, IDirectInputDevice8A *dev,
        DWORD flags, DWORD remain, void *context)
{
    struct EnumDevicesBySemantics_cb_data *data = context;
    struct qemu_IDirectInput8Impl_EnumDevicesBySemantics_cb call;
    BOOL ret;
    struct qemu_dinput_device *device;

    device = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*device));
    if (!device)
        WINE_ERR("Out of memory\n");
    device->parent = data->dinput;
    device->host_a = dev;
    IDirectInputDevice8_QueryInterface(dev, &IID_IDirectInputDevice8W, (void **)&device->host_w);
    IDirectInputDevice8_Release(device->host_w);

    call.cb = data->guest_func;
    call.instance = QEMU_H2G(inst); /* DIDEVICEINSTANCEA has the same size in 32 and 64 bit. */
    call.dev = QEMU_H2G(device);
    call.flags = flags;
    call.remain = remain;
    call.ctx = data->guest_ctx;

    WINE_TRACE("Calling guest callback.\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest wrapper returned %x.\n", ret);

    return ret;
}

void qemu_IDirectInput8AImpl_EnumDevicesBySemantics(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_EnumDevicesBySemantics *c = (struct qemu_IDirectInput8AImpl_EnumDevicesBySemantics *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);
    DIACTIONFORMATA stack, *fmt = &stack;
    struct qemu_DIACTIONFORMATA *fmt32;
    DIACTIONA *actions = NULL;
    struct EnumDevicesBySemantics_cb_data data;

    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    fmt = QEMU_G2H(c->lpdiActionFormat);
#else
    /* Wine does not care about dwSize. */
    fmt32 = QEMU_G2H(c->lpdiActionFormat);
    if (!fmt32)
        fmt = NULL;
    else
    {
        actions = HeapAlloc(GetProcessHeap(), 0, sizeof(*actions) * fmt32->dwNumActions);
        if (!actions)
            WINE_ERR("Out of memory\n");
        DIACTIONFORMATA_g2h(fmt, fmt32, actions);
    }
#endif

    data.guest_func = c->lpCallback;
    data.guest_ctx = c->pvRef;
    data.wrapper = c->wrapper;
    data.dinput = dinput;

    c->super.iret = IDirectInput8_EnumDevicesBySemantics(dinput->host_8a, QEMU_G2H(c->ptszUserName),
            fmt, c->lpCallback ? EnumDevicesBySemanticsA_host_cb : NULL, &data, c->dwFlags);

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, actions);
#endif
}

#endif

struct qemu_IDirectInput8WImpl_EnumDevicesBySemantics
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ptszUserName;
    uint64_t lpdiActionFormat;
    uint64_t lpCallback;
    uint64_t pvRef;
    uint64_t dwFlags;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

static BOOL __fastcall EnumDevicesBySemanticsW_guest_cb(
        const struct qemu_IDirectInput8Impl_EnumDevicesBySemantics_cb *data)
{
    LPDIENUMDEVICESBYSEMANTICSCBW cb = (LPDIENUMDEVICESBYSEMANTICSCBW)(ULONG_PTR)data->cb;
    struct qemu_dinput_device *device;

    device = (struct qemu_dinput_device *)(ULONG_PTR)data->dev;
    qemu_dinput_device_guest_init(device);

    return cb((const DIDEVICEINSTANCEW *)(ULONG_PTR)data->instance, &device->IDirectInputDevice8W_iface,
            data->flags, data->remain, (void *)(ULONG_PTR)data->ctx);
}


static HRESULT WINAPI IDirectInput8WImpl_EnumDevicesBySemantics(IDirectInput8W *iface, LPCWSTR ptszUserName,
        LPDIACTIONFORMATW lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBW lpCallback, LPVOID pvRef, DWORD dwFlags)
{
    struct qemu_IDirectInput8WImpl_EnumDevicesBySemantics call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_ENUMDEVICESBYSEMANTICS);
    call.iface = (ULONG_PTR)dinput;
    call.ptszUserName = (ULONG_PTR)ptszUserName;
    call.lpdiActionFormat = (ULONG_PTR)lpdiActionFormat;
    call.lpCallback = (ULONG_PTR)lpCallback;
    call.pvRef = (ULONG_PTR)pvRef;
    call.dwFlags = dwFlags;
    call.wrapper = (ULONG_PTR)EnumDevicesBySemanticsW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK EnumDevicesBySemanticsW_host_cb(const DIDEVICEINSTANCEW *inst, IDirectInputDevice8W *dev,
        DWORD flags, DWORD remain, void *context)
{
    struct EnumDevicesBySemantics_cb_data *data = context;
    struct qemu_IDirectInput8Impl_EnumDevicesBySemantics_cb call;
    BOOL ret;
    struct qemu_dinput_device *device;

    device = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*device));
    if (!device)
        WINE_ERR("Out of memory\n");
    device->parent = data->dinput;
    device->host_w = dev;
    IDirectInputDevice8_QueryInterface(dev, &IID_IDirectInputDevice8A, (void **)&device->host_a);
    IDirectInputDevice8_Release(device->host_a);

    call.cb = data->guest_func;
    call.instance = QEMU_H2G(inst); /* DIDEVICEINSTANCEW has the same size in 32 and 64 bit. */
    call.dev = QEMU_H2G(device);
    call.flags = flags;
    call.remain = remain;
    call.ctx = data->guest_ctx;

    WINE_TRACE("Calling guest callback.\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest wrapper returned %x.\n", ret);

    return ret;
}

void qemu_IDirectInput8WImpl_EnumDevicesBySemantics(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_EnumDevicesBySemantics *c = (struct qemu_IDirectInput8WImpl_EnumDevicesBySemantics *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);
    struct qemu_DIACTIONFORMATW *fmt32;
    DIACTIONW *actions = NULL;
    DIACTIONFORMATW stack, *fmt = &stack;
    struct EnumDevicesBySemantics_cb_data data;

    WINE_FIXME("Untested\n"); /* Just copypasted from A, but not tested by tests. */

#if GUEST_BIT == HOST_BIT
    fmt = QEMU_G2H(c->lpdiActionFormat);
#else
    /* Wine does not care about dwSize. */
    fmt32 = QEMU_G2H(c->lpdiActionFormat);
    if (!fmt32)
        fmt = NULL;
    else
    {
        actions = HeapAlloc(GetProcessHeap(), 0, sizeof(*actions) * fmt32->dwNumActions);
        if (!actions)
            WINE_ERR("Out of memory\n");
        DIACTIONFORMATW_g2h(fmt, fmt32, actions);
    }
#endif

    data.guest_func = c->lpCallback;
    data.guest_ctx = c->pvRef;
    data.wrapper = c->wrapper;
    data.dinput = dinput;

    c->super.iret = IDirectInput8_EnumDevicesBySemantics(dinput->host_8w, QEMU_G2H(c->ptszUserName),
            fmt, c->lpCallback ? EnumDevicesBySemanticsW_host_cb : NULL, &data, c->dwFlags);

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, actions);
#endif
}

#endif

struct qemu_IDirectInput8WImpl_ConfigureDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiCallback;
    uint64_t lpdiCDParams;
    uint64_t dwFlags;
    uint64_t pvRefData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8WImpl_ConfigureDevices(IDirectInput8W *iface, LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSW lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
    struct qemu_IDirectInput8WImpl_ConfigureDevices call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8W(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8WIMPL_CONFIGUREDEVICES);
    call.iface = (ULONG_PTR)dinput;
    call.lpdiCallback = (ULONG_PTR)lpdiCallback;
    call.lpdiCDParams = (ULONG_PTR)lpdiCDParams;
    call.dwFlags = dwFlags;
    call.pvRefData = (ULONG_PTR)pvRefData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8WImpl_ConfigureDevices(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8WImpl_ConfigureDevices *c = (struct qemu_IDirectInput8WImpl_ConfigureDevices *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_ConfigureDevices(dinput->host_8w, QEMU_G2H(c->lpdiCallback), QEMU_G2H(c->lpdiCDParams), c->dwFlags, QEMU_G2H(c->pvRefData));
}

#endif

struct qemu_IDirectInput8AImpl_ConfigureDevices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdiCallback;
    uint64_t lpdiCDParams;
    uint64_t dwFlags;
    uint64_t pvRefData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectInput8AImpl_ConfigureDevices(IDirectInput8A *iface, LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
    struct qemu_IDirectInput8AImpl_ConfigureDevices call;
    struct qemu_dinput *dinput = impl_from_IDirectInput8A(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTINPUT8AIMPL_CONFIGUREDEVICES);
    call.iface = (ULONG_PTR)dinput;
    call.lpdiCallback = (ULONG_PTR)lpdiCallback;
    call.lpdiCDParams = (ULONG_PTR)lpdiCDParams;
    call.dwFlags = dwFlags;
    call.pvRefData = (ULONG_PTR)pvRefData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectInput8AImpl_ConfigureDevices(struct qemu_syscall *call)
{
    struct qemu_IDirectInput8AImpl_ConfigureDevices *c = (struct qemu_IDirectInput8AImpl_ConfigureDevices *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInput8_ConfigureDevices(dinput->host_8a, QEMU_G2H(c->lpdiCallback), QEMU_G2H(c->lpdiCDParams), c->dwFlags, QEMU_G2H(c->pvRefData));
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_QueryInterface(IDirectInputJoyConfig8 *iface, REFIID riid, void** ppobj)
{
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    return IDirectInputAImpl_QueryInterface(&dinput->IDirectInput7A_iface, riid, ppobj);
}

static ULONG WINAPI JoyConfig8Impl_AddRef(IDirectInputJoyConfig8 *iface)
{
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    return IDirectInputAImpl_AddRef( &dinput->IDirectInput7A_iface );
}

static ULONG WINAPI JoyConfig8Impl_Release(IDirectInputJoyConfig8 *iface)
{
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    return IDirectInputAImpl_Release( &dinput->IDirectInput7A_iface );
}

#endif

struct qemu_JoyConfig8Impl_Acquire
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_Acquire(IDirectInputJoyConfig8 *iface)
{
    struct qemu_JoyConfig8Impl_Acquire call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_ACQUIRE);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_Acquire(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_Acquire *c = (struct qemu_JoyConfig8Impl_Acquire *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_Acquire(dinput->host_joy_config);
}

#endif

struct qemu_JoyConfig8Impl_Unacquire
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_Unacquire(IDirectInputJoyConfig8 *iface)
{
    struct qemu_JoyConfig8Impl_Unacquire call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_UNACQUIRE);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_Unacquire(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_Unacquire *c = (struct qemu_JoyConfig8Impl_Unacquire *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_Unacquire(dinput->host_joy_config);
}

#endif

struct qemu_JoyConfig8Impl_SetCooperativeLevel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwnd;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_SetCooperativeLevel(IDirectInputJoyConfig8 *iface, HWND hwnd, DWORD flags)
{
    struct qemu_JoyConfig8Impl_SetCooperativeLevel call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_SETCOOPERATIVELEVEL);
    call.iface = (ULONG_PTR)dinput;
    call.hwnd = (ULONG_PTR)hwnd;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_SetCooperativeLevel(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_SetCooperativeLevel *c = (struct qemu_JoyConfig8Impl_SetCooperativeLevel *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_SetCooperativeLevel(dinput->host_joy_config, QEMU_G2H(c->hwnd), c->flags);
}

#endif

struct qemu_JoyConfig8Impl_SendNotify
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_SendNotify(IDirectInputJoyConfig8 *iface)
{
    struct qemu_JoyConfig8Impl_SendNotify call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_SENDNOTIFY);
    call.iface = (ULONG_PTR)dinput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_SendNotify(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_SendNotify *c = (struct qemu_JoyConfig8Impl_SendNotify *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_SendNotify(dinput->host_joy_config);
}

#endif

struct qemu_JoyConfig8Impl_EnumTypes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cb;
    uint64_t ref;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_EnumTypes(IDirectInputJoyConfig8 *iface, LPDIJOYTYPECALLBACK cb, void *ref)
{
    struct qemu_JoyConfig8Impl_EnumTypes call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_ENUMTYPES);
    call.iface = (ULONG_PTR)dinput;
    call.cb = (ULONG_PTR)cb;
    call.ref = (ULONG_PTR)ref;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_EnumTypes(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_EnumTypes *c = (struct qemu_JoyConfig8Impl_EnumTypes *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_EnumTypes(dinput->host_joy_config, QEMU_G2H(c->cb), QEMU_G2H(c->ref));
}

#endif

struct qemu_JoyConfig8Impl_GetTypeInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t info;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_GetTypeInfo(IDirectInputJoyConfig8 *iface, LPCWSTR name, LPDIJOYTYPEINFO info, DWORD flags)
{
    struct qemu_JoyConfig8Impl_GetTypeInfo call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_GETTYPEINFO);
    call.iface = (ULONG_PTR)dinput;
    call.name = (ULONG_PTR)name;
    call.info = (ULONG_PTR)info;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_GetTypeInfo(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_GetTypeInfo *c = (struct qemu_JoyConfig8Impl_GetTypeInfo *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_GetTypeInfo(dinput->host_joy_config, QEMU_G2H(c->name), QEMU_G2H(c->info), c->flags);
}

#endif

struct qemu_JoyConfig8Impl_SetTypeInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t info;
    uint64_t flags;
    uint64_t new_name;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_SetTypeInfo(IDirectInputJoyConfig8 *iface, LPCWSTR name, LPCDIJOYTYPEINFO info, DWORD flags, LPWSTR new_name)
{
    struct qemu_JoyConfig8Impl_SetTypeInfo call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_SETTYPEINFO);
    call.iface = (ULONG_PTR)dinput;
    call.name = (ULONG_PTR)name;
    call.info = (ULONG_PTR)info;
    call.flags = flags;
    call.new_name = (ULONG_PTR)new_name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_SetTypeInfo(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_SetTypeInfo *c = (struct qemu_JoyConfig8Impl_SetTypeInfo *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_SetTypeInfo(dinput->host_joy_config, QEMU_G2H(c->name), QEMU_G2H(c->info), c->flags, QEMU_G2H(c->new_name));
}

#endif

struct qemu_JoyConfig8Impl_DeleteType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_DeleteType(IDirectInputJoyConfig8 *iface, LPCWSTR name)
{
    struct qemu_JoyConfig8Impl_DeleteType call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_DELETETYPE);
    call.iface = (ULONG_PTR)dinput;
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_DeleteType(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_DeleteType *c = (struct qemu_JoyConfig8Impl_DeleteType *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_DeleteType(dinput->host_joy_config, QEMU_G2H(c->name));
}

#endif

struct qemu_JoyConfig8Impl_GetConfig
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t id;
    uint64_t info;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_GetConfig(IDirectInputJoyConfig8 *iface, UINT id, LPDIJOYCONFIG info, DWORD flags)
{
    struct qemu_JoyConfig8Impl_GetConfig call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_GETCONFIG);
    call.iface = (ULONG_PTR)dinput;
    call.id = id;
    call.info = (ULONG_PTR)info;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_GetConfig(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_GetConfig *c = (struct qemu_JoyConfig8Impl_GetConfig *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_GetConfig(dinput->host_joy_config, c->id, QEMU_G2H(c->info), c->flags);
}

#endif

struct qemu_JoyConfig8Impl_SetConfig
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t id;
    uint64_t info;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_SetConfig(IDirectInputJoyConfig8 *iface, UINT id, LPCDIJOYCONFIG info, DWORD flags)
{
    struct qemu_JoyConfig8Impl_SetConfig call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_SETCONFIG);
    call.iface = (ULONG_PTR)dinput;
    call.id = id;
    call.info = (ULONG_PTR)info;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_SetConfig(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_SetConfig *c = (struct qemu_JoyConfig8Impl_SetConfig *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_SetConfig(dinput->host_joy_config, c->id, QEMU_G2H(c->info), c->flags);
}

#endif

struct qemu_JoyConfig8Impl_DeleteConfig
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_DeleteConfig(IDirectInputJoyConfig8 *iface, UINT id)
{
    struct qemu_JoyConfig8Impl_DeleteConfig call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_DELETECONFIG);
    call.iface = (ULONG_PTR)dinput;
    call.id = id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_DeleteConfig(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_DeleteConfig *c = (struct qemu_JoyConfig8Impl_DeleteConfig *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_DeleteConfig(dinput->host_joy_config, c->id);
}

#endif

struct qemu_JoyConfig8Impl_GetUserValues
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t info;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_GetUserValues(IDirectInputJoyConfig8 *iface, LPDIJOYUSERVALUES info, DWORD flags)
{
    struct qemu_JoyConfig8Impl_GetUserValues call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_GETUSERVALUES);
    call.iface = (ULONG_PTR)dinput;
    call.info = (ULONG_PTR)info;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_GetUserValues(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_GetUserValues *c = (struct qemu_JoyConfig8Impl_GetUserValues *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_GetUserValues(dinput->host_joy_config, QEMU_G2H(c->info), c->flags);
}

#endif

struct qemu_JoyConfig8Impl_SetUserValues
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t info;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_SetUserValues(IDirectInputJoyConfig8 *iface, LPCDIJOYUSERVALUES info, DWORD flags)
{
    struct qemu_JoyConfig8Impl_SetUserValues call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_SETUSERVALUES);
    call.iface = (ULONG_PTR)dinput;
    call.info = (ULONG_PTR)info;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_SetUserValues(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_SetUserValues *c = (struct qemu_JoyConfig8Impl_SetUserValues *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_SetUserValues(dinput->host_joy_config, QEMU_G2H(c->info), c->flags);
}

#endif

struct qemu_JoyConfig8Impl_AddNewHardware
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwnd;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_AddNewHardware(IDirectInputJoyConfig8 *iface, HWND hwnd, REFGUID guid)
{
    struct qemu_JoyConfig8Impl_AddNewHardware call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_ADDNEWHARDWARE);
    call.iface = (ULONG_PTR)dinput;
    call.hwnd = (ULONG_PTR)hwnd;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_AddNewHardware(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_AddNewHardware *c = (struct qemu_JoyConfig8Impl_AddNewHardware *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_AddNewHardware(dinput->host_joy_config, QEMU_G2H(c->hwnd), QEMU_G2H(c->guid));
}

#endif

struct qemu_JoyConfig8Impl_OpenTypeKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t security;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_OpenTypeKey(IDirectInputJoyConfig8 *iface, LPCWSTR name, DWORD security, PHKEY key)
{
    struct qemu_JoyConfig8Impl_OpenTypeKey call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_OPENTYPEKEY);
    call.iface = (ULONG_PTR)dinput;
    call.name = (ULONG_PTR)name;
    call.security = security;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_OpenTypeKey(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_OpenTypeKey *c = (struct qemu_JoyConfig8Impl_OpenTypeKey *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_OpenTypeKey(dinput->host_joy_config, QEMU_G2H(c->name), c->security, QEMU_G2H(c->key));
}

#endif

struct qemu_JoyConfig8Impl_OpenAppStatusKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI JoyConfig8Impl_OpenAppStatusKey(IDirectInputJoyConfig8 *iface, PHKEY key)
{
    struct qemu_JoyConfig8Impl_OpenAppStatusKey call;
    struct qemu_dinput *dinput = impl_from_IDirectInputJoyConfig8(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIG8IMPL_OPENAPPSTATUSKEY);
    call.iface = (ULONG_PTR)dinput;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_JoyConfig8Impl_OpenAppStatusKey(struct qemu_syscall *call)
{
    struct qemu_JoyConfig8Impl_OpenAppStatusKey *c = (struct qemu_JoyConfig8Impl_OpenAppStatusKey *)call;
    struct qemu_dinput *dinput = QEMU_G2H(c->iface);

    WINE_FIXME("Unverified!\n");

    c->super.iret = IDirectInputJoyConfig8_OpenAppStatusKey(dinput->host_joy_config, QEMU_G2H(c->key));
}

#endif

struct qemu_init_dll
{
    struct qemu_syscall super;
    uint64_t reason;
};

struct qemu_directinput_create
{
    struct qemu_syscall super;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_init_dll call;

    call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
    call.reason = reason;
    qemu_syscall(&call.super);

    return TRUE;
}

static const IDirectInput7AVtbl ddi7avt =
{
    IDirectInputAImpl_QueryInterface,
    IDirectInputAImpl_AddRef,
    IDirectInputAImpl_Release,
    IDirectInputAImpl_CreateDevice,
    IDirectInputAImpl_EnumDevices,
    IDirectInputAImpl_GetDeviceStatus,
    IDirectInputAImpl_RunControlPanel,
    IDirectInputAImpl_Initialize,
    IDirectInput2AImpl_FindDevice,
    IDirectInput7AImpl_CreateDeviceEx
};

static const IDirectInput7WVtbl ddi7wvt =
{
    IDirectInputWImpl_QueryInterface,
    IDirectInputWImpl_AddRef,
    IDirectInputWImpl_Release,
    IDirectInputWImpl_CreateDevice,
    IDirectInputWImpl_EnumDevices,
    IDirectInputWImpl_GetDeviceStatus,
    IDirectInputWImpl_RunControlPanel,
    IDirectInputWImpl_Initialize,
    IDirectInput2WImpl_FindDevice,
    IDirectInput7WImpl_CreateDeviceEx
};

static const IDirectInput8AVtbl ddi8avt =
{
    IDirectInput8AImpl_QueryInterface,
    IDirectInput8AImpl_AddRef,
    IDirectInput8AImpl_Release,
    IDirectInput8AImpl_CreateDevice,
    IDirectInput8AImpl_EnumDevices,
    IDirectInput8AImpl_GetDeviceStatus,
    IDirectInput8AImpl_RunControlPanel,
    IDirectInput8AImpl_Initialize,
    IDirectInput8AImpl_FindDevice,
    IDirectInput8AImpl_EnumDevicesBySemantics,
    IDirectInput8AImpl_ConfigureDevices
};

static const IDirectInput8WVtbl ddi8wvt =
{
    IDirectInput8WImpl_QueryInterface,
    IDirectInput8WImpl_AddRef,
    IDirectInput8WImpl_Release,
    IDirectInput8WImpl_CreateDevice,
    IDirectInput8WImpl_EnumDevices,
    IDirectInput8WImpl_GetDeviceStatus,
    IDirectInput8WImpl_RunControlPanel,
    IDirectInput8WImpl_Initialize,
    IDirectInput8WImpl_FindDevice,
    IDirectInput8WImpl_EnumDevicesBySemantics,
    IDirectInput8WImpl_ConfigureDevices
};

static const IDirectInputJoyConfig8Vtbl JoyConfig8vt =
{
    JoyConfig8Impl_QueryInterface,
    JoyConfig8Impl_AddRef,
    JoyConfig8Impl_Release,
    JoyConfig8Impl_Acquire,
    JoyConfig8Impl_Unacquire,
    JoyConfig8Impl_SetCooperativeLevel,
    JoyConfig8Impl_SendNotify,
    JoyConfig8Impl_EnumTypes,
    JoyConfig8Impl_GetTypeInfo,
    JoyConfig8Impl_SetTypeInfo,
    JoyConfig8Impl_DeleteType,
    JoyConfig8Impl_GetConfig,
    JoyConfig8Impl_SetConfig,
    JoyConfig8Impl_DeleteConfig,
    JoyConfig8Impl_GetUserValues,
    JoyConfig8Impl_SetUserValues,
    JoyConfig8Impl_AddNewHardware,
    JoyConfig8Impl_OpenTypeKey,
    JoyConfig8Impl_OpenAppStatusKey
};

static HRESULT create_directinput_instance(const IID *iid, void **iface_out, struct qemu_dinput **impl)
{
    struct qemu_directinput_create call;
    struct qemu_dinput *object;
    HRESULT hr;
    ULONG ref;

    if (!iid || !iface_out)
    {
        WINE_WARN("Invalid pointer.\n");
        return E_POINTER;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTINPUT_CREATE);
    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    object = (struct qemu_dinput *)(ULONG_PTR)call.object;

    object->IDirectInput7A_iface.lpVtbl = &ddi7avt;
    object->IDirectInput7W_iface.lpVtbl = &ddi7wvt;
    object->IDirectInput8A_iface.lpVtbl = &ddi8avt;
    object->IDirectInput8W_iface.lpVtbl = &ddi8wvt;
    object->IDirectInputJoyConfig8_iface.lpVtbl = &JoyConfig8vt;

    hr = IDirectInput7_QueryInterface(&object->IDirectInput7A_iface, iid, iface_out);
    if (FAILED(hr))
        WINE_ERR("Guest-side QI failed, but host side succeeded for %s.\n", wine_dbgstr_guid(iid));

    /* Host ref == guest ref, and the host interface started with ref 1. We want to return an interface
     * with ref 1, so release the one on the interface we originally created. */
    ref = IDirectInput7_Release(&object->IDirectInput7A_iface);
    if (ref != 1)
        WINE_ERR("Unexpected reference count %u.\n", ref);

    if (impl)
        *impl = object;

    return DI_OK;
}

/******************************************************************************
 *	DirectInputCreateEx (DINPUT.@)
 */
HRESULT WINAPI DirectInputCreateEx(HINSTANCE inst, DWORD version, const IID *iid, void **out, IUnknown *outer)
{
    struct qemu_dinput *dinput;
    HRESULT hr;

    WINE_TRACE("(%p,%04x,%s,%p,%p)\n", inst, version, wine_dbgstr_guid(iid), out, outer);

    if (IsEqualGUID(&IID_IDirectInputA, iid) ||
            IsEqualGUID(&IID_IDirectInput2A, iid) ||
            IsEqualGUID(&IID_IDirectInput7A, iid) ||
            IsEqualGUID(&IID_IDirectInputW,  iid) ||
            IsEqualGUID(&IID_IDirectInput2W, iid) ||
            IsEqualGUID(&IID_IDirectInput7W, iid))
    {
        hr = create_directinput_instance(iid, out, &dinput);
        if (FAILED(hr))
            return hr;
    }
    else
    {
        return DIERR_NOINTERFACE;
    }

    hr = IDirectInput_Initialize(&dinput->IDirectInput7A_iface, inst, version);
    if (FAILED(hr))
    {
        IDirectInput_Release(&dinput->IDirectInput7A_iface);
        *out = NULL;
        return hr;
    }

    return DI_OK;
}

HRESULT WINAPI DirectInputCreateA(HINSTANCE inst, DWORD version, IDirectInputA *out, IUnknown *outer)
{
    return DirectInputCreateEx(inst, version, &IID_IDirectInput7A, (void **)out, outer);
}

HRESULT WINAPI DirectInputCreateW(HINSTANCE inst, DWORD version, IDirectInputW *out, IUnknown *outer)
{
    return DirectInputCreateEx(inst, version, &IID_IDirectInput7W, (void **)out, outer);
}

HRESULT WINAPI DllCanUnloadNow(void)
{
    return S_FALSE;
}

struct class_factory
{
    IClassFactory IClassFactory_iface;
    LONG          ref;
};

static inline struct class_factory *impl_from_IClassFactory(IClassFactory *iface)
{
    return CONTAINING_RECORD(iface, struct class_factory, IClassFactory_iface);
}

static HRESULT WINAPI class_factory_QueryInterface(IClassFactory *iface, const IID *iid, void **obj)
{
    struct class_factory *fac = impl_from_IClassFactory(iface);

    WINE_FIXME("(%p)->(%s,%p),stub!\n", fac, wine_dbgstr_guid(iid), obj);
    return E_NOINTERFACE;
}

static ULONG WINAPI class_factory_AddRef(IClassFactory *iface)
{
    struct class_factory *fac = impl_from_IClassFactory(iface);
    return InterlockedIncrement(&(fac->ref));
}

static ULONG WINAPI class_factory_Release(IClassFactory *iface)
{
    struct class_factory *fac = impl_from_IClassFactory(iface);
    /* static class, won't be  freed */
    return InterlockedDecrement(&(fac->ref));
}

static HRESULT WINAPI class_factory_CreateInstance(IClassFactory *iface, IUnknown *outer,
        const IID *iid, void **obj)
{
    struct class_factory *fac = impl_from_IClassFactory(iface);

    WINE_TRACE("(%p)->(%p,%s,%p)\n", fac, outer, wine_dbgstr_guid(iid), obj);
    if (IsEqualGUID(&IID_IUnknown, iid) ||
            IsEqualGUID(&IID_IDirectInputA, iid) ||
            IsEqualGUID(&IID_IDirectInputW, iid) ||
            IsEqualGUID(&IID_IDirectInput2A, iid) ||
            IsEqualGUID(&IID_IDirectInput2W, iid) ||
            IsEqualGUID(&IID_IDirectInput7A, iid) ||
            IsEqualGUID(&IID_IDirectInput7W, iid))
    {
        return create_directinput_instance(iid, obj, NULL);
    }

    WINE_FIXME("(%p,%p,%s,%p) Interface not found!\n", fac, outer, wine_dbgstr_guid(iid), obj);	
    return E_NOINTERFACE;
}

static HRESULT WINAPI class_factory_LockServer(IClassFactory *iface, BOOL dolock)
{
    struct class_factory *fac = impl_from_IClassFactory(iface);
    WINE_FIXME("(%p)->(%d),stub!\n", fac, dolock);
    return S_OK;
}

static const IClassFactoryVtbl class_factory_Vtbl =
{
    class_factory_QueryInterface,
    class_factory_AddRef,
    class_factory_Release,
    class_factory_CreateInstance,
    class_factory_LockServer
};

static struct class_factory class_factory = {{&class_factory_Vtbl}, 1};

HRESULT WINAPI DllGetClassObject(const CLSID *rclsid, const IID *iid, void **obj)
{
    WINE_TRACE("(%s,%s,%p)\n", wine_dbgstr_guid(rclsid), wine_dbgstr_guid(iid), obj);
    if (IsEqualCLSID( &IID_IClassFactory, iid))
    {
        *obj = &class_factory;
        IClassFactory_AddRef((IClassFactory *)*obj);
        return S_OK;
    }

    WINE_FIXME("(%s,%s,%p): no interface found.\n", wine_dbgstr_guid(rclsid), wine_dbgstr_guid(iid), obj);
    return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT WINAPI DllRegisterServer(void)
{
    WINE_ERR("Not expected to be called on guest DLLs.\n");
    return E_FAIL;
}

HRESULT WINAPI DllUnregisterServer(void)
{
    WINE_ERR("Not expected to be called on guest DLLs.\n");
    return E_FAIL;
}

#else

static HMODULE dinput_mod;

static void qemu_init_dll(struct qemu_syscall *call)
{

    struct qemu_init_dll *c = (struct qemu_init_dll *)call;

    /* dinput.dll links to comctl32, which we don't want to load unless the guest app loads it to be
     * able to switch between comctl32 v6 and older comctl32. */
    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            dinput_mod = LoadLibraryA("dinput");
            if (!dinput_mod)
                WINE_ERR("Failed to load dinput.dll.\n");
            break;

        case DLL_PROCESS_DETACH:
            FreeLibrary(dinput_mod);
            dinput_mod = NULL;
            break;
    }
}

static void qemu_directinput_create(struct qemu_syscall *call)
{
    struct qemu_directinput_create *c = (struct qemu_directinput_create *)call;
    struct qemu_dinput *object;
    HRESULT hr;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *factory;

    /* Because we copypasted the init code from Wine we'll call Initialize with the
     * desired device GUID later. Don't call DirectInputCreate here and instead use
     * CoCreateInstance to create an uninitialized object. We also need to be able
     * to create uninitialized devices if the guest calls us through CoCreateInstance.
     *
     * Except that we can't use CoCreateInstance because the host-side ole32 is
     * probably not initialized. So navigate out way through DllGetClassObject like
     * ole32 would. */
    p_DllGetClassObject = (void *)GetProcAddress(dinput_mod, "DllGetClassObject");

    hr = p_DllGetClassObject(&CLSID_DirectInput, &IID_IClassFactory, (void *)&factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = E_OUTOFMEMORY;
        IClassFactory_Release(factory);
        return;
    }

    hr = IClassFactory_CreateInstance(factory, NULL, &IID_IDirectInput7A, (void **)&object->host_7a);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IDirectInput object.\n");
        HeapFree(GetProcessHeap(), 0, object);
        object = NULL;
    }

    IDirectInput7_QueryInterface(object->host_7a, &IID_IDirectInput7W, (void **)&object->host_7w);
    IDirectInput7_QueryInterface(object->host_7a, &IID_IDirectInput8A, (void **)&object->host_8a);
    IDirectInput7_QueryInterface(object->host_7a, &IID_IDirectInput8W, (void **)&object->host_8w);
    IDirectInput7_QueryInterface(object->host_7a, &IID_IDirectInputJoyConfig8,
            (void **)&object->host_joy_config);

    /* We need all 4 interfaces, but because host ref == guest ref we want to leave only 1 reference
     * behind. */
    IDirectInput7_Release(object->host_7w);
    IDirectInput8_Release(object->host_8a);
    IDirectInput8_Release(object->host_8w);
    IDirectInput8_Release(object->host_joy_config);

    c->object = QEMU_H2G(object);
    c->super.iret = hr;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_directinput_create,
    qemu_IDirectInput2AImpl_FindDevice,
    qemu_IDirectInput2WImpl_FindDevice,
    qemu_IDirectInput7AImpl_CreateDeviceEx,
    qemu_IDirectInput7WImpl_CreateDeviceEx,
    qemu_IDirectInput8AImpl_AddRef,
    qemu_IDirectInput8AImpl_ConfigureDevices,
    qemu_IDirectInputImpl_CreateDevice,
    qemu_IDirectInput8AImpl_EnumDevices,
    qemu_IDirectInput8AImpl_EnumDevicesBySemantics,
    qemu_IDirectInput8AImpl_FindDevice,
    qemu_IDirectInput8AImpl_GetDeviceStatus,
    qemu_IDirectInput8AImpl_Initialize,
    qemu_IDirectInputImpl_Release,
    qemu_IDirectInput8AImpl_RunControlPanel,
    qemu_IDirectInput8WImpl_AddRef,
    qemu_IDirectInput8WImpl_ConfigureDevices,
    qemu_IDirectInputImpl_CreateDevice,
    qemu_IDirectInput8WImpl_EnumDevices,
    qemu_IDirectInput8WImpl_EnumDevicesBySemantics,
    qemu_IDirectInput8WImpl_FindDevice,
    qemu_IDirectInput8WImpl_GetDeviceStatus,
    qemu_IDirectInput8WImpl_Initialize,
    qemu_IDirectInputImpl_Release,
    qemu_IDirectInput8WImpl_RunControlPanel,
    qemu_IDirectInputAImpl_AddRef,
    qemu_IDirectInputImpl_CreateDevice,
    qemu_IDirectInputImpl_EnumDevices,
    qemu_IDirectInputAImpl_GetDeviceStatus,
    qemu_IDirectInputAImpl_Initialize,
    qemu_IDirectInputAImpl_QueryInterface,
    qemu_IDirectInputImpl_Release,
    qemu_IDirectInputAImpl_RunControlPanel,
    qemu_IDirectInputDeviceAImpl_Acquire,
    qemu_IDirectInputDeviceAImpl_AddRef,
    qemu_IDirectInputDeviceAImpl_BuildActionMap,
    qemu_IDirectInputDeviceAImpl_CreateEffect,
    qemu_IDirectInputDeviceAImpl_EnumCreatedEffectObjects,
    qemu_IDirectInputDeviceAImpl_EnumEffects,
    qemu_IDirectInputDeviceAImpl_EnumEffectsInFile,
    qemu_IDirectInputDeviceImpl_EnumObjects,
    qemu_IDirectInputDeviceAImpl_Escape,
    qemu_IDirectInputDeviceAImpl_GetCapabilities,
    qemu_IDirectInputDeviceImpl_GetDeviceData,
    qemu_IDirectInputDeviceAImpl_GetDeviceInfo,
    qemu_IDirectInputDeviceAImpl_GetDeviceState,
    qemu_IDirectInputDeviceAImpl_GetEffectInfo,
    qemu_IDirectInputDeviceAImpl_GetForceFeedbackState,
    qemu_IDirectInputDeviceAImpl_GetImageInfo,
    qemu_IDirectInputDeviceAImpl_GetObjectInfo,
    qemu_IDirectInputDeviceAImpl_GetProperty,
    qemu_IDirectInputDeviceAImpl_Initialize,
    qemu_IDirectInputDeviceAImpl_Poll,
    qemu_IDirectInputDeviceImpl_Release,
    qemu_IDirectInputDeviceAImpl_RunControlPanel,
    qemu_IDirectInputDeviceAImpl_SendDeviceData,
    qemu_IDirectInputDeviceAImpl_SendForceFeedbackCommand,
    qemu_IDirectInputDeviceAImpl_SetActionMap,
    qemu_IDirectInputDeviceAImpl_SetCooperativeLevel,
    qemu_IDirectInputDeviceImpl_SetDataFormat,
    qemu_IDirectInputDeviceAImpl_SetEventNotification,
    qemu_IDirectInputDeviceAImpl_SetProperty,
    qemu_IDirectInputDeviceAImpl_Unacquire,
    qemu_IDirectInputDeviceAImpl_WriteEffectToFile,
    qemu_IDirectInputDeviceWImpl_Acquire,
    qemu_IDirectInputDeviceWImpl_AddRef,
    qemu_IDirectInputDeviceWImpl_BuildActionMap,
    qemu_IDirectInputDeviceWImpl_CreateEffect,
    qemu_IDirectInputDeviceWImpl_EnumCreatedEffectObjects,
    qemu_IDirectInputDeviceWImpl_EnumEffects,
    qemu_IDirectInputDeviceWImpl_EnumEffectsInFile,
    qemu_IDirectInputDeviceImpl_EnumObjects,
    qemu_IDirectInputDeviceWImpl_Escape,
    qemu_IDirectInputDeviceWImpl_GetCapabilities,
    qemu_IDirectInputDeviceImpl_GetDeviceData,
    qemu_IDirectInputDeviceWImpl_GetDeviceInfo,
    qemu_IDirectInputDeviceWImpl_GetDeviceState,
    qemu_IDirectInputDeviceWImpl_GetEffectInfo,
    qemu_IDirectInputDeviceWImpl_GetForceFeedbackState,
    qemu_IDirectInputDeviceWImpl_GetImageInfo,
    qemu_IDirectInputDeviceWImpl_GetObjectInfo,
    qemu_IDirectInputDeviceWImpl_GetProperty,
    qemu_IDirectInputDeviceWImpl_Initialize,
    qemu_IDirectInputDeviceWImpl_Poll,
    qemu_IDirectInputDeviceImpl_QueryInterface,
    qemu_IDirectInputDeviceImpl_Release,
    qemu_IDirectInputDeviceWImpl_RunControlPanel,
    qemu_IDirectInputDeviceWImpl_SendDeviceData,
    qemu_IDirectInputDeviceWImpl_SendForceFeedbackCommand,
    qemu_IDirectInputDeviceWImpl_SetActionMap,
    qemu_IDirectInputDeviceWImpl_SetCooperativeLevel,
    qemu_IDirectInputDeviceImpl_SetDataFormat,
    qemu_IDirectInputDeviceWImpl_SetEventNotification,
    qemu_IDirectInputDeviceWImpl_SetProperty,
    qemu_IDirectInputDeviceWImpl_Unacquire,
    qemu_IDirectInputDeviceWImpl_WriteEffectToFile,
    qemu_IDirectInputWImpl_AddRef,
    qemu_IDirectInputImpl_CreateDevice,
    qemu_IDirectInputImpl_EnumDevices,
    qemu_IDirectInputWImpl_GetDeviceStatus,
    qemu_IDirectInputWImpl_Initialize,
    qemu_IDirectInputImpl_Release,
    qemu_IDirectInputWImpl_RunControlPanel,
    qemu_init_dll,
    qemu_JoyConfig8Impl_Acquire,
    qemu_JoyConfig8Impl_AddNewHardware,
    qemu_JoyConfig8Impl_DeleteConfig,
    qemu_JoyConfig8Impl_DeleteType,
    qemu_JoyConfig8Impl_EnumTypes,
    qemu_JoyConfig8Impl_GetConfig,
    qemu_JoyConfig8Impl_GetTypeInfo,
    qemu_JoyConfig8Impl_GetUserValues,
    qemu_JoyConfig8Impl_OpenAppStatusKey,
    qemu_JoyConfig8Impl_OpenTypeKey,
    qemu_JoyConfig8Impl_SendNotify,
    qemu_JoyConfig8Impl_SetConfig,
    qemu_JoyConfig8Impl_SetCooperativeLevel,
    qemu_JoyConfig8Impl_SetTypeInfo,
    qemu_JoyConfig8Impl_SetUserValues,
    qemu_JoyConfig8Impl_Unacquire,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side dinput wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
