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
#include <dinput.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dinput.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dinput);

struct qemu_init_dll
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_init_dll call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        qemu_syscall(&call.super);
    }

    return TRUE;
}

static HRESULT create_directinput_instance(REFIID riid, void **iface_out, struct qemu_dinput **impl)
{
    WINE_FIXME("Not yet implemented.\"n");
#if 0
    struct qemu_dinput *This = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct qemu_dinput) );
    HRESULT hr;

    if (!This)
        return E_OUTOFMEMORY;

    This->IDirectInput7A_iface.lpVtbl = &ddi7avt;
    This->IDirectInput7W_iface.lpVtbl = &ddi7wvt;
    This->IDirectInput8A_iface.lpVtbl = &ddi8avt;
    This->IDirectInput8W_iface.lpVtbl = &ddi8wvt;
    This->IDirectInputJoyConfig8_iface.lpVtbl = &JoyConfig8vt;

    hr = IDirectInput_QueryInterface( &This->IDirectInput7A_iface, riid, ppDI );
    if (FAILED(hr))
    {
        HeapFree( GetProcessHeap(), 0, This );
        return hr;
    }

    if (out) *out = This;
    return DI_OK;
#endif
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

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_init_dll *c = (struct qemu_init_dll *)call;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_init_dll,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side dinput wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
