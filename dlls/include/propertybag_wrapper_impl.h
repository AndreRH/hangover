/*
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

#include "propertybag_wrapper.h"

#include "thunk/qemu_windows.h"
#include "thunk/qemu_oaidl.h"

struct propertybag_wrapper
{
    IPropertyBag IPropertyBag_iface;
    uint64_t guest_iface;
};

struct propertybag_wrapper_funcs
{
    uint64_t read;
    uint64_t write;
};

struct propertybag_wrapper_ReadWrite
{
    uint64_t iface;
    uint64_t name, var, log;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall propertybag_wrapper_Read(struct propertybag_wrapper_ReadWrite *call)
{
    IPropertyBag *bag = (IPropertyBag *)(ULONG_PTR)call->iface;
    HRESULT hr;
    hr = bag->lpVtbl->Read(bag, (LPCOLESTR)(ULONG_PTR)call->name, (VARIANT *)(ULONG_PTR)call->var,
            (IErrorLog *)(ULONG_PTR)call->log);
    call->iface = sizeof(VARIANT);
    return hr;
}

static HRESULT __fastcall propertybag_wrapper_Write(struct propertybag_wrapper_ReadWrite *call)
{
    IPropertyBag *bag = (IPropertyBag *)(ULONG_PTR)call->iface;
    return bag->lpVtbl->Write(bag, (LPCOLESTR)(ULONG_PTR)call->name, (VARIANT *)(ULONG_PTR)call->var);
}

static void propertybag_wrapper_get_funcs(struct propertybag_wrapper_funcs *funcs)
{
    funcs->read = (ULONG_PTR)propertybag_wrapper_Read;
    funcs->write = (ULONG_PTR)propertybag_wrapper_Write;
}

#else

static uint64_t propertybag_wrapper_Read_guest;
static uint64_t propertybag_wrapper_Write_guest;

static void propertybag_wrapper_set_funcs(const struct propertybag_wrapper_funcs *funcs)
{
    if (funcs)
    {
        propertybag_wrapper_Read_guest = funcs->read;
        propertybag_wrapper_Write_guest = funcs->write;
    }
    else
    {
        propertybag_wrapper_Read_guest = 0;
        propertybag_wrapper_Write_guest = 0;
    }
}

struct propertybag_wrapper *propertybag_wrapper_from_IPropertyBag(IPropertyBag *iface)
{
    return CONTAINING_RECORD(iface, struct propertybag_wrapper, IPropertyBag_iface);
}

static HRESULT STDMETHODCALLTYPE propertybag_wrapper_QueryInterface(IPropertyBag *iface, const IID *iid,
        void **out)
{
    WINE_FIXME("Not implemented.\n");
    return E_NOTIMPL;
}

static ULONG STDMETHODCALLTYPE propertybag_wrapper_AddRef(IPropertyBag *iface)
{
    WINE_FIXME("Not implemented.\n");
    return 2;
}

static ULONG STDMETHODCALLTYPE propertybag_wrapper_Release(IPropertyBag *iface)
{
    WINE_FIXME("Not implemented.\n");
    return 1;
}

static HRESULT STDMETHODCALLTYPE propertybag_wrapper_Read(IPropertyBag *iface, LPCOLESTR name, VARIANT *var,
        IErrorLog *log)
{
    struct propertybag_wrapper *bag = propertybag_wrapper_from_IPropertyBag(iface);
    struct propertybag_wrapper_ReadWrite call;
    WCHAR *copy = NULL;
    HRESULT hr;
    struct qemu_VARIANT var32;

    WINE_TRACE("\n");
    call.iface = propertybag_wrapper_guest_iface(bag);
    call.name = QEMU_H2G(name);
#if GUEST_BIT == HOST_BIT
    call.var = QEMU_H2G(var);
#else
    if (call.name > ~0U)
    {
        size_t len = lstrlenW(name) + 1;
        copy = HeapAlloc(GetProcessHeap(), 0, len * sizeof(*copy));
        memcpy(copy, name, len * sizeof(*copy));
        call.name = QEMU_H2G(copy);
    }
    VARIANT_h2g(&var32, var);
    call.var = QEMU_H2G(&var32);
#endif
    call.log = QEMU_H2G(log);

    WINE_TRACE("Calling guest callback %p.\n", (void *)propertybag_wrapper_Read_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(propertybag_wrapper_Read_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, copy);
    VARIANT_g2h(var, &var32);
#endif

    return hr;
}

static HRESULT STDMETHODCALLTYPE propertybag_wrapper_Write(IPropertyBag *iface, LPCOLESTR name, VARIANT *var)
{
    struct propertybag_wrapper *bag = propertybag_wrapper_from_IPropertyBag(iface);
    struct propertybag_wrapper_ReadWrite call;
    HRESULT hr;

    WINE_FIXME("\n");
    call.iface = propertybag_wrapper_guest_iface(bag);
    call.name = QEMU_H2G(name);
    call.var = QEMU_H2G(var);

    WINE_TRACE("Calling guest callback %p.\n", (void *)propertybag_wrapper_Write_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(propertybag_wrapper_Write_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}


static const IPropertyBagVtbl propertybag_wrapper_Vtbl =
{
    propertybag_wrapper_QueryInterface,
    propertybag_wrapper_AddRef,
    propertybag_wrapper_Release,
    propertybag_wrapper_Read,
    propertybag_wrapper_Write,
};

struct propertybag_wrapper *propertybag_wrapper_create(uint64_t guest_iface)
{
    struct propertybag_wrapper *ret;

    if (!guest_iface)
        return NULL;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        return NULL;

    ret->guest_iface = guest_iface;
    ret->IPropertyBag_iface.lpVtbl = &propertybag_wrapper_Vtbl;

    return ret;
}

void propertybag_wrapper_destroy(struct propertybag_wrapper *wrapper)
{
    HeapFree(GetProcessHeap(), 0, wrapper);
}

uint64_t propertybag_wrapper_guest_iface(struct propertybag_wrapper *wrapper)
{
    return wrapper ? wrapper->guest_iface : 0;
}

IPropertyBag *propertybag_wrapper_host_iface(struct propertybag_wrapper *wrapper)
{
    return wrapper ? &wrapper->IPropertyBag_iface : NULL;
}

#endif
