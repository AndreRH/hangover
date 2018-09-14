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

#define COBJMACROS

#include <windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_PropertyBag_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_propery_bag *impl_from_IPropertyBag2(IPropertyBag2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_propery_bag, IPropertyBag2_iface);
}

static HRESULT WINAPI PropertyBag_QueryInterface(IPropertyBag2 *iface, REFIID iid, void **ppv)
{
    struct qemu_PropertyBag_QueryInterface call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_QUERYINTERFACE);
    call.iface = (ULONG_PTR)bag;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_QueryInterface *c = (struct qemu_PropertyBag_QueryInterface *)call;
    struct qemu_propery_bag *bag;

    WINE_FIXME("Unverified!\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_QueryInterface(bag->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_PropertyBag_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI PropertyBag_AddRef(IPropertyBag2 *iface)
{
    struct qemu_PropertyBag_AddRef call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_ADDREF);
    call.iface = (ULONG_PTR)bag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_AddRef(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_AddRef *c = (struct qemu_PropertyBag_AddRef *)call;
    struct qemu_propery_bag *bag;

    WINE_TRACE("\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_AddRef(bag->host);
}

#endif

struct qemu_PropertyBag_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI PropertyBag_Release(IPropertyBag2 *iface)
{
    struct qemu_PropertyBag_Release call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_RELEASE);
    call.iface = (ULONG_PTR)bag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_Release(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_Release *c = (struct qemu_PropertyBag_Release *)call;
    struct qemu_propery_bag *bag;

    WINE_TRACE("\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_Release(bag->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying property bag wrapper %p for host bag %p.\n", bag, bag->host);
        HeapFree(GetProcessHeap(), 0, bag);
    }
}

#endif

struct qemu_PropertyBag_Read
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cProperties;
    uint64_t pPropBag;
    uint64_t pErrLog;
    uint64_t pvarValue;
    uint64_t phrError;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI PropertyBag_Read(IPropertyBag2 *iface, ULONG cProperties, PROPBAG2 *pPropBag,
        IErrorLog *pErrLog, VARIANT *pvarValue, HRESULT *phrError)
{
    struct qemu_PropertyBag_Read call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_READ);
    call.iface = (ULONG_PTR)bag;
    call.cProperties = cProperties;
    call.pPropBag = (ULONG_PTR)pPropBag;
    call.pErrLog = (ULONG_PTR)pErrLog;
    call.pvarValue = (ULONG_PTR)pvarValue;
    call.phrError = (ULONG_PTR)phrError;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_Read(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_Read *c = (struct qemu_PropertyBag_Read *)call;
    struct qemu_propery_bag *bag;

    WINE_FIXME("Unverified!\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_Read(bag->host, c->cProperties, QEMU_G2H(c->pPropBag), QEMU_G2H(c->pErrLog),
            QEMU_G2H(c->pvarValue), QEMU_G2H(c->phrError));
}

#endif

struct qemu_PropertyBag_Write
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cProperties;
    uint64_t pPropBag;
    uint64_t pvarValue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI PropertyBag_Write(IPropertyBag2 *iface, ULONG cProperties, PROPBAG2 *pPropBag,
        VARIANT *pvarValue)
{
    struct qemu_PropertyBag_Write call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_WRITE);
    call.iface = (ULONG_PTR)bag;
    call.cProperties = cProperties;
    call.pPropBag = (ULONG_PTR)pPropBag;
    call.pvarValue = (ULONG_PTR)pvarValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_Write(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_Write *c = (struct qemu_PropertyBag_Write *)call;
    struct qemu_propery_bag *bag;

    WINE_FIXME("Unverified!\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_Write(bag->host, c->cProperties, QEMU_G2H(c->pPropBag), QEMU_G2H(c->pvarValue));
}

#endif

struct qemu_PropertyBag_CountProperties
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pcProperties;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI PropertyBag_CountProperties(IPropertyBag2 *iface, ULONG *pcProperties)
{
    struct qemu_PropertyBag_CountProperties call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_COUNTPROPERTIES);
    call.iface = (ULONG_PTR)bag;
    call.pcProperties = (ULONG_PTR)pcProperties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_CountProperties(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_CountProperties *c = (struct qemu_PropertyBag_CountProperties *)call;
    struct qemu_propery_bag *bag;

    WINE_FIXME("Unverified!\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_CountProperties(bag->host, QEMU_G2H(c->pcProperties));
}

#endif

struct qemu_PropertyBag_GetPropertyInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iProperty;
    uint64_t cProperties;
    uint64_t pPropBag;
    uint64_t pcProperties;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI PropertyBag_GetPropertyInfo(IPropertyBag2 *iface, ULONG iProperty, ULONG cProperties,
        PROPBAG2 *pPropBag, ULONG *pcProperties)
{
    struct qemu_PropertyBag_GetPropertyInfo call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_GETPROPERTYINFO);
    call.iface = (ULONG_PTR)bag;
    call.iProperty = iProperty;
    call.cProperties = cProperties;
    call.pPropBag = (ULONG_PTR)pPropBag;
    call.pcProperties = (ULONG_PTR)pcProperties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_GetPropertyInfo(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_GetPropertyInfo *c = (struct qemu_PropertyBag_GetPropertyInfo *)call;
    struct qemu_propery_bag *bag;

    WINE_FIXME("Unverified!\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_GetPropertyInfo(bag->host, c->iProperty, c->cProperties, QEMU_G2H(c->pPropBag),
            QEMU_G2H(c->pcProperties));
}

#endif

struct qemu_PropertyBag_LoadObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pstrName;
    uint64_t dwHint;
    uint64_t pUnkObject;
    uint64_t pErrLog;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI PropertyBag_LoadObject(IPropertyBag2 *iface, LPCOLESTR pstrName, DWORD dwHint,
        IUnknown *pUnkObject, IErrorLog *pErrLog)
{
    struct qemu_PropertyBag_LoadObject call;
    struct qemu_propery_bag *bag = impl_from_IPropertyBag2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYBAG_LOADOBJECT);
    call.iface = (ULONG_PTR)bag;
    call.pstrName = (ULONG_PTR)pstrName;
    call.dwHint = dwHint;
    call.pUnkObject = (ULONG_PTR)pUnkObject;
    call.pErrLog = (ULONG_PTR)pErrLog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertyBag_LoadObject(struct qemu_syscall *call)
{
    struct qemu_PropertyBag_LoadObject *c = (struct qemu_PropertyBag_LoadObject *)call;
    struct qemu_propery_bag *bag;

    WINE_FIXME("Unverified!\n");
    bag = QEMU_G2H(c->iface);

    c->super.iret = IPropertyBag2_LoadObject(bag->host, QEMU_G2H(c->pstrName), c->dwHint,
            QEMU_G2H(c->pUnkObject), QEMU_G2H(c->pErrLog));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IPropertyBag2Vtbl PropertyBag_Vtbl =
{
    PropertyBag_QueryInterface,
    PropertyBag_AddRef,
    PropertyBag_Release,
    PropertyBag_Read,
    PropertyBag_Write,
    PropertyBag_CountProperties,
    PropertyBag_GetPropertyInfo,
    PropertyBag_LoadObject
};

void PropertyBag_init_guest(struct qemu_propery_bag *bag)
{
    bag->IPropertyBag2_iface.lpVtbl = &PropertyBag_Vtbl;
}

#else

struct qemu_propery_bag *PropertyBag_create_host(IPropertyBag2 *host)
{
    struct qemu_propery_bag *ret;
    HRESULT hr;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    ret->host = host;

    return ret;
}

#endif
