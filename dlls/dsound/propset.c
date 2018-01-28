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
#include <dsound.h>
#include <dsconf.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_dsound.h"
#include "thunk/qemu_dsconf.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dsound.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);

struct qemu_propset
{
    /* Guest members */
    IKsPropertySet IKsPropertySet_iface;
    LONG ref;

    /* Host members */
    IKsPropertySet *host;
};

struct qemu_IKsPrivatePropertySetImpl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static struct qemu_propset *impl_from_IKsPropertySet(IKsPropertySet *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_propset, IKsPropertySet_iface);
}

static HRESULT WINAPI IKsPrivatePropertySetImpl_QueryInterface(IKsPropertySet *iface, REFIID riid, void **obj)
{
    struct qemu_propset *propset = impl_from_IKsPropertySet(iface);
    WINE_TRACE("(%p,%s,%p)\n", propset, wine_dbgstr_guid(riid), obj);

    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IKsPropertySet))
    {
        *obj = iface;
        IKsPropertySet_AddRef(iface);
        return S_OK;
    }

    *obj = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI IKsPrivatePropertySetImpl_AddRef(IKsPropertySet *iface)
{
    struct qemu_propset *propset = impl_from_IKsPropertySet(iface);
    ULONG ref = InterlockedIncrement(&(propset->ref));
    WINE_TRACE("(%p) ref was %d\n", propset, ref - 1);
    return ref;
}

static ULONG WINAPI IKsPrivatePropertySetImpl_Release(IKsPropertySet *iface)
{
    struct qemu_propset *propset = impl_from_IKsPropertySet(iface);
    ULONG ref = InterlockedDecrement(&(propset->ref));
    WINE_TRACE("(%p) ref was %d\n", propset, ref + 1);

    if (!ref)
    {
        struct qemu_IKsPrivatePropertySetImpl_Release call;
        call.super.id = QEMU_SYSCALL_ID(CALL_IKSPRIVATEPROPERTYSETIMPL_RELEASE);
        call.iface = (ULONG_PTR)propset;

        qemu_syscall(&call.super);
    }
    return ref;
}

#else

void qemu_IKsPrivatePropertySetImpl_Release(struct qemu_syscall *call)
{
    struct qemu_propset *propset;
    struct qemu_IKsPrivatePropertySetImpl_Release *c = (struct qemu_IKsPrivatePropertySetImpl_Release *)call;

    WINE_TRACE("\n");
    propset = QEMU_G2H(c->iface);

    c->super.iret = IKsPropertySet_Release(propset->host);
    if (c->super.iret)
        WINE_ERR("Ref is %lu, expected 0.\n", c->super.iret);
}

#endif

struct qemu_IKsPrivatePropertySetImpl_Get
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidPropSet;
    uint64_t dwPropID;
    uint64_t pInstanceData;
    uint64_t cbInstanceData;
    uint64_t pPropData;
    uint64_t cbPropData;
    uint64_t pcbReturned;
    uint64_t wrapper;
};

struct qemu_IKsPrivatePropertySetImpl_Get_cb
{
    uint64_t func;
    uint64_t data;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

static BOOL __fastcall qemu_IKsPrivatePropertySetImpl_Get_guest_cb(struct qemu_IKsPrivatePropertySetImpl_Get_cb *data)
{
    LPFNDIRECTSOUNDDEVICEENUMERATECALLBACK1 cb = (LPFNDIRECTSOUNDDEVICEENUMERATECALLBACK1)(ULONG_PTR)data->func;
    return cb((void *)(ULONG_PTR)data->data, (void *)(ULONG_PTR)data->ctx);
}

static HRESULT WINAPI IKsPrivatePropertySetImpl_Get(IKsPropertySet *iface, REFGUID guidPropSet, ULONG dwPropID,
        void *pInstanceData, ULONG cbInstanceData, void *pPropData, ULONG cbPropData, ULONG *pcbReturned)
{
    struct qemu_propset *propset = impl_from_IKsPropertySet(iface);
    struct qemu_IKsPrivatePropertySetImpl_Get call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPRIVATEPROPERTYSETIMPL_GET);
    call.iface = (ULONG_PTR)propset;
    call.guidPropSet = (ULONG_PTR)guidPropSet;
    call.dwPropID = dwPropID;
    call.pInstanceData = (ULONG_PTR)pInstanceData;
    call.cbInstanceData = cbInstanceData;
    call.pPropData = (ULONG_PTR)pPropData;
    call.cbPropData = cbPropData;
    call.pcbReturned = (ULONG_PTR)pcbReturned;
    call.wrapper = (ULONG_PTR)qemu_IKsPrivatePropertySetImpl_Get_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_property_enum_data
{
    uint64_t wrapper;
    uint64_t guest_func;
    uint64_t guest_ctx;
    DWORD id;
};

static BOOL CALLBACK qemu_IKsPrivatePropertySetImpl_Get_host_cb(
        DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1_DATA *data, void *context)
{
    struct qemu_property_enum_data *ctx = context;
    struct qemu_DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA desc;
    struct qemu_IKsPrivatePropertySetImpl_Get_cb call;
    BOOL ret;
    void *copy;

    call.func = ctx->guest_func;
    call.data = QEMU_H2G(data);
    call.ctx = ctx->guest_ctx;

#if HOST_BIT != GUEST_BIT
    switch (ctx->id)
    {
        /*
         * DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1_DATA matches on 32 and 64 bit.
        case DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_1:
            break;
         */

        case DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_A:
        {
            /* The Interface string is hardcoded, so it's in the host library and above 4 GB. */
            char *host_str = ((DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_A_DATA *)data)->Interface;

            copy = alloca(strlen(host_str) + 1);
            strcpy(copy, host_str);

            DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA_h2g(&desc, (void *)data);
            desc.Interface = QEMU_H2G(copy);
            call.data = QEMU_H2G(&desc);
            break;
        }

        case DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_W:
        {
            WCHAR *host_str = ((DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W_DATA *)data)->Interface;
            size_t len = (lstrlenW(host_str) + 1) * sizeof(WCHAR);

            copy = alloca(len);
            memcpy(copy, host_str, len);

            DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_DATA_h2g(&desc, (void *)data);
            desc.Interface = QEMU_H2G(copy);
            call.data = QEMU_H2G(&desc);
            break;
            break;
        }
    }
#endif

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx).\n", call.func, call.data, call.ctx);
    qemu_ops->qemu_execute(QEMU_G2H(ctx->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest wrapper returned %u.\n", ret);

    return ret;
}

void qemu_IKsPrivatePropertySetImpl_Get(struct qemu_syscall *call)
{
    struct qemu_propset *propset;
    struct qemu_IKsPrivatePropertySetImpl_Get *c = (struct qemu_IKsPrivatePropertySetImpl_Get *)call;
    const GUID *guid;
    void *instance_data, *prop_data;
    ULONG *ret_size;
    DWORD id;
    BOOL conv_back = FALSE;
    ULONG prop_data_size;
    DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_1_DATA enumdata;
    struct qemu_property_enum_data enum_host_data;

    WINE_TRACE("\n");
    propset = QEMU_G2H(c->iface);
    guid = QEMU_G2H(c->guidPropSet);
    instance_data = QEMU_G2H(c->pInstanceData);
    prop_data = QEMU_G2H(c->pPropData);
    prop_data_size = c->cbPropData;
    ret_size = QEMU_G2H(c->pcbReturned);
    id = c->dwPropID;

    if (IsEqualGUID( &DSPROPSETID_DirectSoundDevice, guid))
    {
        switch (id)
        {
            default:
                WINE_FIXME("Forward unknown ID: %d\n", id);
            case DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_1:
                /* Just forward, structs are compatible, no callbacks. */
                break;

            case DSPROPERTY_DIRECTSOUNDDEVICE_WAVEDEVICEMAPPING_A:
            case DSPROPERTY_DIRECTSOUNDDEVICE_WAVEDEVICEMAPPING_W:
#if GUEST_BIT != HOST_BIT
                WINE_FIXME("DSPROPERTY_DIRECTSOUNDDEVICE_WAVEDEVICEMAPPING\n");
                //DSPROPERTY_DIRECTSOUNDDEVICE_WAVEDEVICEMAPPING_A_DATA
                conv_back = TRUE;
#endif
                break;

            case DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_A:
            case DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_W:
#if GUEST_BIT != HOST_BIT
                WINE_FIXME("DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION\n");
                //_DSPROPERTY_DIRECTSOUNDDEVICE_DESCRIPTION_A_DATA
                conv_back = TRUE;
#endif
                break;

            case DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_1:
            case DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_A:
            case DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_W:
                if (!prop_data)
                    break;
#if GUEST_BIT == HOST_BIT
                enumdata = *(DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_1_DATA *)prop_data;
#else
                DSPROPERTY_DIRECTSOUNDDEVICE_ENUMERATE_X_DATA_g2h(&enumdata, prop_data);
#endif
                enum_host_data.wrapper = c->wrapper;
                enum_host_data.guest_func = (ULONG_PTR)enumdata.Callback;
                enum_host_data.guest_ctx = (ULONG_PTR)enumdata.Context;
                enum_host_data.id = id;

                enumdata.Callback = enumdata.Callback ? qemu_IKsPrivatePropertySetImpl_Get_host_cb : NULL;
                enumdata.Context = &enum_host_data;
                prop_data = &enumdata;
                prop_data_size = sizeof(enumdata);

                /* No need to convert anything back, the enumerations don't write to prop or instance data. */
        }
    }
    else
    {
        WINE_FIXME("Forward unknown property set.\n");
    }

    c->super.iret = IKsPropertySet_Get(propset->host, guid, id, instance_data, c->cbInstanceData,
            prop_data, c->cbPropData, ret_size);
}

#endif

struct qemu_IKsPrivatePropertySetImpl_Set
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidPropSet;
    uint64_t dwPropID;
    uint64_t pInstanceData;
    uint64_t cbInstanceData;
    uint64_t pPropData;
    uint64_t cbPropData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IKsPrivatePropertySetImpl_Set(IKsPropertySet *iface, REFGUID guidPropSet, ULONG dwPropID, LPVOID pInstanceData, ULONG cbInstanceData, LPVOID pPropData, ULONG cbPropData)
{
    struct qemu_propset *propset = impl_from_IKsPropertySet(iface);
    struct qemu_IKsPrivatePropertySetImpl_Set call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPRIVATEPROPERTYSETIMPL_SET);
    call.iface = (ULONG_PTR)propset;
    call.guidPropSet = (ULONG_PTR)guidPropSet;
    call.dwPropID = dwPropID;
    call.pInstanceData = (ULONG_PTR)pInstanceData;
    call.cbInstanceData = cbInstanceData;
    call.pPropData = (ULONG_PTR)pPropData;
    call.cbPropData = cbPropData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IKsPrivatePropertySetImpl_Set(struct qemu_syscall *call)
{
    struct qemu_IKsPrivatePropertySetImpl_Set *c = (struct qemu_IKsPrivatePropertySetImpl_Set *)call;
    struct qemu_propset *propset;

    WINE_FIXME("Unverified!\n");
    propset = QEMU_G2H(c->iface);

    c->super.iret = IKsPropertySet_Set(propset->host, QEMU_G2H(c->guidPropSet), c->dwPropID,
            QEMU_G2H(c->pInstanceData), c->cbInstanceData, QEMU_G2H(c->pPropData), c->cbPropData);
}

#endif

struct qemu_IKsPrivatePropertySetImpl_QuerySupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidPropSet;
    uint64_t dwPropID;
    uint64_t pTypeSupport;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IKsPrivatePropertySetImpl_QuerySupport(IKsPropertySet *iface, REFGUID guidPropSet,
        ULONG dwPropID, ULONG *pTypeSupport)
{
    struct qemu_propset *propset = impl_from_IKsPropertySet(iface);
    struct qemu_IKsPrivatePropertySetImpl_QuerySupport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPRIVATEPROPERTYSETIMPL_QUERYSUPPORT);
    call.iface = (ULONG_PTR)propset;
    call.guidPropSet = (ULONG_PTR)guidPropSet;
    call.dwPropID = dwPropID;
    call.pTypeSupport = (ULONG_PTR)pTypeSupport;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IKsPrivatePropertySetImpl_QuerySupport(struct qemu_syscall *call)
{
    struct qemu_IKsPrivatePropertySetImpl_QuerySupport *c = (struct qemu_IKsPrivatePropertySetImpl_QuerySupport *)call;
    struct qemu_propset *propset;

    WINE_FIXME("Unverified!\n");
    propset = QEMU_G2H(c->iface);

    c->super.iret = IKsPropertySet_QuerySupport(propset->host, QEMU_G2H(c->guidPropSet),
            c->dwPropID, QEMU_G2H(c->pTypeSupport));
}

#endif

struct qemu_propset_Create
{
    struct qemu_syscall super;
    uint64_t propset;
};

#ifdef QEMU_DLL_GUEST

static const IKsPropertySetVtbl ikspvt =
{
    IKsPrivatePropertySetImpl_QueryInterface,
    IKsPrivatePropertySetImpl_AddRef,
    IKsPrivatePropertySetImpl_Release,
    IKsPrivatePropertySetImpl_Get,
    IKsPrivatePropertySetImpl_Set,
    IKsPrivatePropertySetImpl_QuerySupport
};

HRESULT IKsPrivatePropertySetImpl_Create(REFIID riid, void **ppv)
{
    struct qemu_propset *propset;
    struct qemu_propset_Create call;
    HRESULT hr;

    WINE_TRACE("(%s, %p)\n", wine_dbgstr_guid(riid), ppv);

    call.super.id = QEMU_SYSCALL_ID(CALL_IKSPRIVATEPROPERTYSETIMPL_CREATE);
    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    propset = (struct qemu_propset *)(ULONG_PTR)call.propset;

    propset->ref = 1;
    propset->IKsPropertySet_iface.lpVtbl = &ikspvt;

    hr = IKsPropertySet_QueryInterface(&propset->IKsPropertySet_iface, riid, ppv);
    IKsPropertySet_Release(&propset->IKsPropertySet_iface);

    return hr;
}

#else

void qemu_IKsPrivatePropertySetImpl_Create(struct qemu_syscall *call)
{
    struct qemu_propset_Create *c = (struct qemu_propset_Create *)call;
    struct qemu_propset *propset;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *factory;
    HRESULT hr;
    WINE_TRACE("\n");

    lib = GetModuleHandleA("dsound");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(&CLSID_DirectSoundPrivate, &IID_IClassFactory, (void *)&factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    c->propset = 0;
    propset = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*propset));
    if (!propset)
    {
        WINE_WARN("out of memory\n");
        IClassFactory_Release(factory);
        c->super.iret = DSERR_OUTOFMEMORY;
        return;
    }

    hr = IClassFactory_CreateInstance(factory, NULL, &IID_IKsPropertySet, (void **)&propset->host);
    IClassFactory_Release(factory);
    if (FAILED(hr))
    {
        WINE_FIXME("Could not create a host property set.\n");
        HeapFree(GetProcessHeap(), 0, propset);
        propset = NULL;
    }

    c->super.iret = hr;
    c->propset = QEMU_H2G(propset);
}

#endif
