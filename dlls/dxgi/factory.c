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
#include <d3d10_1.h>

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <initguid.h>

#include <dxgi1_2.h>
#include <debug.h>

DEFINE_GUID(IID_IDXGIFactory3, 0x25483823, 0xcd46, 0x4c7d, 0x86,0xca, 0x47,0xaa,0x95,0xb8,0x37,0xbd);
DEFINE_GUID(IID_IDXGIFactory4, 0x1bc6ea02, 0xef36, 0x464f, 0xbf,0x0c, 0x21,0xca,0x39,0xe5,0x16,0x8a);
DEFINE_GUID(IID_IDXGIFactory5, 0x7632e1f5, 0xee65, 0x4dca, 0x87,0xfd, 0x84,0xcd,0x75,0xf8,0x83,0x8d);

#else

#include <dxgi1_5.h>
#include <wine/debug.h>

#endif

#include "thunk/qemu_dxgi.h"
#include "qemu_dxgi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_dxgi_factory_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dxgi_factory *impl_from_IDXGIFactory5(IDXGIFactory5 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_factory, IDXGIFactory5_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_factory_QueryInterface(IDXGIFactory5 *iface, REFIID iid, void **out)
{
    struct qemu_dxgi_factory_QueryInterface call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_QUERYINTERFACE);
    call.iface = (ULONG_PTR)factory;
    call.iid = (ULONG_PTR)iid;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        *out = NULL;
        return call.super.iret;
    }

    if (IsEqualGUID(iid, &IID_IDXGIFactory5)
            || IsEqualGUID(iid, &IID_IDXGIFactory4)
            || IsEqualGUID(iid, &IID_IDXGIFactory3)
            || IsEqualGUID(iid, &IID_IDXGIFactory2)
            || IsEqualGUID(iid, &IID_IDXGIFactory1) /* extended filter handled via failure from host side */
            || IsEqualGUID(iid, &IID_IDXGIFactory)
            || IsEqualGUID(iid, &IID_IDXGIObject)
            || IsEqualGUID(iid, &IID_IUnknown))
    {
        /* AddRef was handled on the host side. */
        *out = iface;
        return call.super.iret;
    }

    WINE_FIXME("The host returned an interface for IID %s but this wrapper does not know about it.\n",
            wine_dbgstr_guid(iid));
    IDXGIFactory_Release(iface);
    *out = NULL;

    return E_NOINTERFACE;
}

#else

void qemu_dxgi_factory_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_QueryInterface *c = (struct qemu_dxgi_factory_QueryInterface *)call;
    struct qemu_dxgi_factory *factory;
    void *out = NULL;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_QueryInterface(factory->host, QEMU_G2H(c->iid), &out);
    c->out = QEMU_H2G(out);
}

#endif

struct qemu_dxgi_factory_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_factory_AddRef(IDXGIFactory5 *iface)
{
    struct qemu_dxgi_factory_AddRef call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_ADDREF);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_AddRef(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_AddRef *c = (struct qemu_dxgi_factory_AddRef *)call;
    struct qemu_dxgi_factory *factory;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_AddRef(factory->host);
}

#endif

struct qemu_dxgi_factory_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_factory_Release(IDXGIFactory5 *iface)
{
    struct qemu_dxgi_factory_Release call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_RELEASE);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG qemu_dxgi_factory_Release_internal(struct qemu_dxgi_factory *factory)
{
    ULONG ret;

    ret = IDXGIFactory5_Release(factory->host);
    if (!ret)
    {
        WINE_TRACE("Destroying dxgi factory wrapper %p (host factory %p).\n", factory, factory->host);
        HeapFree(GetProcessHeap(), 0, factory);
    }
    return ret;
}

void qemu_dxgi_factory_Release(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_Release *c = (struct qemu_dxgi_factory_Release *)call;
    struct qemu_dxgi_factory *factory;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = qemu_dxgi_factory_Release_internal(factory);
}

#endif

struct qemu_dxgi_factory_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_SetPrivateData(IDXGIFactory5 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_factory_SetPrivateData call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)factory;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_SetPrivateData *c = (struct qemu_dxgi_factory_SetPrivateData *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_SetPrivateData(factory->host, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_factory_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_SetPrivateDataInterface(IDXGIFactory5 *iface, REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_factory_SetPrivateDataInterface call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)factory;
    call.guid = (ULONG_PTR)guid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_SetPrivateDataInterface *c = (struct qemu_dxgi_factory_SetPrivateDataInterface *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_SetPrivateDataInterface(factory->host, QEMU_G2H(c->guid), QEMU_G2H(c->object));
}

#endif

struct qemu_dxgi_factory_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_GetPrivateData(IDXGIFactory5 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_factory_GetPrivateData call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)factory;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_GetPrivateData *c = (struct qemu_dxgi_factory_GetPrivateData *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_GetPrivateData(factory->host, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_factory_GetParent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_GetParent(IDXGIFactory5 *iface, REFIID iid, void **parent)
{
    struct qemu_dxgi_factory_GetParent call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_GETPARENT);
    call.iface = (ULONG_PTR)factory;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);
    *parent = NULL;

    return E_NOINTERFACE;
}

#else

void qemu_dxgi_factory_GetParent(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_GetParent *c = (struct qemu_dxgi_factory_GetParent *)call;
    struct qemu_dxgi_factory *factory;
    IUnknown *parent = (void *)0xdeadbeef;
    HRESULT hr;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    hr = IDXGIFactory5_GetParent(factory->host, QEMU_G2H(c->iid), (void **)&parent);
    if (hr != E_NOINTERFACE || parent)
        WINE_FIXME("Unexpected response from host factory: %#x, %p.\n", hr, parent);
}

#endif

struct qemu_dxgi_factory_EnumAdapters
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t adapter_idx;
    uint64_t adapter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_EnumAdapters1(IDXGIFactory5 *iface, UINT adapter_idx,
        IDXGIAdapter1 **adapter)
{
    struct qemu_dxgi_factory_EnumAdapters call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);
    struct qemu_dxgi_adapter *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_ENUMADAPTERS);
    call.iface = (ULONG_PTR)factory;
    call.adapter_idx = adapter_idx;
    call.adapter = (ULONG_PTR)adapter;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        if (adapter)
            *adapter = NULL;
        return call.super.iret;
    }

    obj = (struct qemu_dxgi_adapter *)(ULONG_PTR)call.adapter;
    qemu_dxgi_adapter_guest_init(obj);
    *adapter = (IDXGIAdapter1 *)&obj->IDXGIAdapter3_iface;

    return call.super.iret;
}

static HRESULT STDMETHODCALLTYPE dxgi_factory_EnumAdapters(IDXGIFactory5 *iface, UINT adapter_idx, IDXGIAdapter **adapter)
{
    WINE_TRACE("iface %p, adapter_idx %u, adapter %p.\n", iface, adapter_idx, adapter);

    return dxgi_factory_EnumAdapters1(iface, adapter_idx, (IDXGIAdapter1 **)adapter);
}


#else

void qemu_dxgi_factory_EnumAdapters(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_EnumAdapters *c = (struct qemu_dxgi_factory_EnumAdapters *)call;
    struct qemu_dxgi_factory *factory;
    struct qemu_dxgi_adapter *adapter;
    IDXGIAdapter3 *host;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    if (!c->adapter)
    {
        c->super.iret = IDXGIFactory5_EnumAdapters1(factory->host, c->adapter_idx, NULL);
        return;
    }

    c->super.iret = IDXGIFactory5_EnumAdapters1(factory->host, c->adapter_idx, (IDXGIAdapter1 **)&host);
    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_dxgi_adapter_create(factory, host, &adapter);
    if (FAILED(c->super.iret))
        IDXGIAdapter3_Release(host);

    c->adapter = QEMU_H2G(adapter);
}

#endif

struct qemu_dxgi_factory_MakeWindowAssociation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_MakeWindowAssociation(IDXGIFactory5 *iface, HWND window, UINT flags)
{
    struct qemu_dxgi_factory_MakeWindowAssociation call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_MAKEWINDOWASSOCIATION);
    call.iface = (ULONG_PTR)factory;
    call.window = (ULONG_PTR)window;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_MakeWindowAssociation(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_MakeWindowAssociation *c = (struct qemu_dxgi_factory_MakeWindowAssociation *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_MakeWindowAssociation(factory->host, QEMU_G2H(c->window), c->flags);
}

#endif

struct qemu_dxgi_factory_GetWindowAssociation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_GetWindowAssociation(IDXGIFactory5 *iface, HWND *window)
{
    struct qemu_dxgi_factory_GetWindowAssociation call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_GETWINDOWASSOCIATION);
    call.iface = (ULONG_PTR)factory;
    call.window = (ULONG_PTR)window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_GetWindowAssociation(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_GetWindowAssociation *c = (struct qemu_dxgi_factory_GetWindowAssociation *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_GetWindowAssociation(factory->host, QEMU_G2H(c->window));
}

#endif

struct qemu_dxgi_factory_CreateSwapChain
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t desc;
    uint64_t swapchain;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_CreateSwapChain(IDXGIFactory5 *iface, IUnknown *device,
        DXGI_SWAP_CHAIN_DESC *desc, IDXGISwapChain **swapchain)
{
    struct qemu_dxgi_factory_CreateSwapChain call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);
    struct qemu_dxgi_swapchain *obj;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_CREATESWAPCHAIN);
    call.iface = (ULONG_PTR)factory;
    call.desc = (ULONG_PTR)desc;
    call.swapchain = (ULONG_PTR)swapchain;

    if (device)
    {
        struct qemu_dxgi_device *device_impl = unsafe_impl_from_IDXGIDevice(device);
        if (!device)
        {
            WINE_WARN("This is not the device we are looking for.\n");
            return E_FAIL;
        }
        call.device = (ULONG_PTR)device_impl;
    }
    else
    {
        call.device = 0;
    }

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    obj = (struct qemu_dxgi_swapchain *)(ULONG_PTR)call.swapchain;
    qemu_dxgi_swapchain_guest_init(obj);
    *swapchain = (IDXGISwapChain *)&obj->IDXGISwapChain1_iface;

    return call.super.iret;
}

#else

void qemu_dxgi_factory_CreateSwapChain(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_CreateSwapChain *c = (struct qemu_dxgi_factory_CreateSwapChain *)call;
    struct qemu_dxgi_factory *factory;
    struct qemu_dxgi_device *device;
    DXGI_SWAP_CHAIN_DESC stack, *desc = &stack;
    IDXGISwapChain1 *host;
    struct qemu_dxgi_swapchain *obj;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);
    device = QEMU_G2H(c->device);
#if GUEST_BIT == HOST_BIT
    desc = QEMU_G2H(c->desc);
#else
    if (c->desc)
        DXGI_SWAP_CHAIN_DESC_g2h(desc, QEMU_G2H(c->desc));
    else
        desc = NULL;
#endif

    c->super.iret = IDXGIFactory5_CreateSwapChain(factory->host, device ? (IUnknown *)device->host : NULL,
            desc, c->swapchain ? (IDXGISwapChain **)&host : NULL);
    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_dxgi_swapchain_create(host, device, &obj);
    if (FAILED(c->super.iret))
    {
        IDXGISwapChain1_Release(host);
        return;
    }
    c->swapchain = QEMU_H2G(obj);
}

#endif

struct qemu_dxgi_factory_CreateSoftwareAdapter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t swrast;
    uint64_t adapter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_CreateSoftwareAdapter(IDXGIFactory5 *iface, HMODULE swrast, IDXGIAdapter **adapter)
{
    struct qemu_dxgi_factory_CreateSoftwareAdapter call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_CREATESOFTWAREADAPTER);
    call.iface = (ULONG_PTR)factory;
    call.swrast = (ULONG_PTR)swrast;
    call.adapter = (ULONG_PTR)adapter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_CreateSoftwareAdapter(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_CreateSoftwareAdapter *c = (struct qemu_dxgi_factory_CreateSoftwareAdapter *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_CreateSoftwareAdapter(factory->host, QEMU_G2H(c->swrast), QEMU_G2H(c->adapter));
}

#endif

struct qemu_dxgi_factory_IsCurrent
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static BOOL STDMETHODCALLTYPE dxgi_factory_IsCurrent(IDXGIFactory5 *iface)
{
    struct qemu_dxgi_factory_IsCurrent call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_ISCURRENT);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_IsCurrent(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_IsCurrent *c = (struct qemu_dxgi_factory_IsCurrent *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_IsCurrent(factory->host);
}

#endif

struct qemu_dxgi_factory_IsWindowedStereoEnabled
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static BOOL STDMETHODCALLTYPE dxgi_factory_IsWindowedStereoEnabled(IDXGIFactory5 *iface)
{
    struct qemu_dxgi_factory_IsWindowedStereoEnabled call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_ISWINDOWEDSTEREOENABLED);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_IsWindowedStereoEnabled(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_IsWindowedStereoEnabled *c = (struct qemu_dxgi_factory_IsWindowedStereoEnabled *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_IsWindowedStereoEnabled(factory->host);
}

#endif

struct qemu_dxgi_factory_CreateSwapChainForHwnd
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t window;
    uint64_t swapchain_desc;
    uint64_t fullscreen_desc;
    uint64_t output;
    uint64_t swapchain;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_CreateSwapChainForHwnd(IDXGIFactory5 *iface, IUnknown *device, HWND window, const DXGI_SWAP_CHAIN_DESC1 *swapchain_desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *fullscreen_desc, IDXGIOutput *output, IDXGISwapChain1 **swapchain)
{
    struct qemu_dxgi_factory_CreateSwapChainForHwnd call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_CREATESWAPCHAINFORHWND);
    call.iface = (ULONG_PTR)factory;
    call.device = (ULONG_PTR)device;
    call.window = (ULONG_PTR)window;
    call.swapchain_desc = (ULONG_PTR)swapchain_desc;
    call.fullscreen_desc = (ULONG_PTR)fullscreen_desc;
    call.output = (ULONG_PTR)output;
    call.swapchain = (ULONG_PTR)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_CreateSwapChainForHwnd(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_CreateSwapChainForHwnd *c = (struct qemu_dxgi_factory_CreateSwapChainForHwnd *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_CreateSwapChainForHwnd(factory->host, QEMU_G2H(c->device), QEMU_G2H(c->window),
            QEMU_G2H(c->swapchain_desc), QEMU_G2H(c->fullscreen_desc), QEMU_G2H(c->output), QEMU_G2H(c->swapchain));
}

#endif

struct qemu_dxgi_factory_CreateSwapChainForCoreWindow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t window;
    uint64_t desc;
    uint64_t output;
    uint64_t swapchain;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_CreateSwapChainForCoreWindow(IDXGIFactory5 *iface, IUnknown *device,
        IUnknown *window, const DXGI_SWAP_CHAIN_DESC1 *desc, IDXGIOutput *output, IDXGISwapChain1 **swapchain)
{
    struct qemu_dxgi_factory_CreateSwapChainForCoreWindow call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_CREATESWAPCHAINFORCOREWINDOW);
    call.iface = (ULONG_PTR)factory;
    call.device = (ULONG_PTR)device;
    call.window = (ULONG_PTR)window;
    call.desc = (ULONG_PTR)desc;
    call.output = (ULONG_PTR)output;
    call.swapchain = (ULONG_PTR)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_CreateSwapChainForCoreWindow(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_CreateSwapChainForCoreWindow *c =
            (struct qemu_dxgi_factory_CreateSwapChainForCoreWindow *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_CreateSwapChainForCoreWindow(factory->host, QEMU_G2H(c->device),
            QEMU_G2H(c->window), QEMU_G2H(c->desc), QEMU_G2H(c->output), QEMU_G2H(c->swapchain));
}

#endif

struct qemu_dxgi_factory_GetSharedResourceAdapterLuid
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
    uint64_t luid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_GetSharedResourceAdapterLuid(IDXGIFactory5 *iface, HANDLE resource,
        LUID *luid)
{
    struct qemu_dxgi_factory_GetSharedResourceAdapterLuid call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_GETSHAREDRESOURCEADAPTERLUID);
    call.iface = (ULONG_PTR)factory;
    call.resource = (ULONG_PTR)resource;
    call.luid = (ULONG_PTR)luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_GetSharedResourceAdapterLuid(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_GetSharedResourceAdapterLuid *c =
            (struct qemu_dxgi_factory_GetSharedResourceAdapterLuid *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_GetSharedResourceAdapterLuid(factory->host, QEMU_G2H(c->resource), QEMU_G2H(c->luid));
}

#endif

struct qemu_dxgi_factory_RegisterOcclusionStatusWindow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t message;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_RegisterOcclusionStatusWindow(IDXGIFactory5 *iface, HWND window,
        UINT message, DWORD *cookie)
{
    struct qemu_dxgi_factory_RegisterOcclusionStatusWindow call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_REGISTEROCCLUSIONSTATUSWINDOW);
    call.iface = (ULONG_PTR)factory;
    call.window = (ULONG_PTR)window;
    call.message = message;
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_RegisterOcclusionStatusWindow(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_RegisterOcclusionStatusWindow *c =
            (struct qemu_dxgi_factory_RegisterOcclusionStatusWindow *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_RegisterOcclusionStatusWindow(factory->host, QEMU_G2H(c->window), c->message,
            QEMU_G2H(c->cookie));
}

#endif

struct qemu_dxgi_factory_RegisterStereoStatusEvent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t event;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_RegisterStereoStatusEvent(IDXGIFactory5 *iface, HANDLE event,
        DWORD *cookie)
{
    struct qemu_dxgi_factory_RegisterStereoStatusEvent call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_REGISTERSTEREOSTATUSEVENT);
    call.iface = (ULONG_PTR)factory;
    call.event = (ULONG_PTR)event;
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_RegisterStereoStatusEvent(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_RegisterStereoStatusEvent *c = (struct qemu_dxgi_factory_RegisterStereoStatusEvent *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_RegisterStereoStatusEvent(factory->host, QEMU_G2H(c->event), QEMU_G2H(c->cookie));
}

#endif

struct qemu_dxgi_factory_UnregisterStereoStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE dxgi_factory_UnregisterStereoStatus(IDXGIFactory5 *iface, DWORD cookie)
{
    struct qemu_dxgi_factory_UnregisterStereoStatus call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_UNREGISTERSTEREOSTATUS);
    call.iface = (ULONG_PTR)factory;
    call.cookie = cookie;

    qemu_syscall(&call.super);
}

#else

void qemu_dxgi_factory_UnregisterStereoStatus(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_UnregisterStereoStatus *c = (struct qemu_dxgi_factory_UnregisterStereoStatus *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    IDXGIFactory5_UnregisterStereoStatus(factory->host, c->cookie);
}

#endif

struct qemu_dxgi_factory_RegisterStereoStatusWindow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t window;
    uint64_t message;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_RegisterStereoStatusWindow(IDXGIFactory5 *iface, HWND window,
        UINT message, DWORD *cookie)
{
    struct qemu_dxgi_factory_RegisterStereoStatusWindow call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_REGISTERSTEREOSTATUSWINDOW);
    call.iface = (ULONG_PTR)factory;
    call.window = (ULONG_PTR)window;
    call.message = message;
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_RegisterStereoStatusWindow(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_RegisterStereoStatusWindow *c =
            (struct qemu_dxgi_factory_RegisterStereoStatusWindow *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_RegisterStereoStatusWindow(factory->host, QEMU_G2H(c->window), c->message,
            QEMU_G2H(c->cookie));
}

#endif

struct qemu_dxgi_factory_RegisterOcclusionStatusEvent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t event;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_RegisterOcclusionStatusEvent(IDXGIFactory5 *iface, HANDLE event,
        DWORD *cookie)
{
    struct qemu_dxgi_factory_RegisterOcclusionStatusEvent call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_REGISTEROCCLUSIONSTATUSEVENT);
    call.iface = (ULONG_PTR)factory;
    call.event = (ULONG_PTR)event;
    call.cookie = (ULONG_PTR)cookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_RegisterOcclusionStatusEvent(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_RegisterOcclusionStatusEvent *c =
            (struct qemu_dxgi_factory_RegisterOcclusionStatusEvent *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_RegisterOcclusionStatusEvent(factory->host, QEMU_G2H(c->event), QEMU_G2H(c->cookie));
}

#endif

struct qemu_dxgi_factory_UnregisterOcclusionStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE dxgi_factory_UnregisterOcclusionStatus(IDXGIFactory5 *iface, DWORD cookie)
{
    struct qemu_dxgi_factory_UnregisterOcclusionStatus call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_UNREGISTEROCCLUSIONSTATUS);
    call.iface = (ULONG_PTR)factory;
    call.cookie = cookie;

    qemu_syscall(&call.super);
}

#else

void qemu_dxgi_factory_UnregisterOcclusionStatus(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_UnregisterOcclusionStatus *c = (struct qemu_dxgi_factory_UnregisterOcclusionStatus *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    IDXGIFactory5_UnregisterOcclusionStatus(factory->host, c->cookie);
}

#endif

struct qemu_dxgi_factory_CreateSwapChainForComposition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t desc;
    uint64_t output;
    uint64_t swapchain;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_CreateSwapChainForComposition(IDXGIFactory5 *iface, IUnknown *device,
        const DXGI_SWAP_CHAIN_DESC1 *desc, IDXGIOutput *output, IDXGISwapChain1 **swapchain)
{
    struct qemu_dxgi_factory_CreateSwapChainForComposition call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_CREATESWAPCHAINFORCOMPOSITION);
    call.iface = (ULONG_PTR)factory;
    call.device = (ULONG_PTR)device;
    call.desc = (ULONG_PTR)desc;
    call.output = (ULONG_PTR)output;
    call.swapchain = (ULONG_PTR)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_CreateSwapChainForComposition(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_CreateSwapChainForComposition *c = (struct qemu_dxgi_factory_CreateSwapChainForComposition *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_CreateSwapChainForComposition(factory->host, QEMU_G2H(c->device), QEMU_G2H(c->desc), QEMU_G2H(c->output), QEMU_G2H(c->swapchain));
}

#endif

struct qemu_dxgi_factory_GetCreationFlags
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static UINT STDMETHODCALLTYPE dxgi_factory_GetCreationFlags(IDXGIFactory5 *iface)
{
    struct qemu_dxgi_factory_GetCreationFlags call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_GETCREATIONFLAGS);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_GetCreationFlags(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_GetCreationFlags *c = (struct qemu_dxgi_factory_GetCreationFlags *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_GetCreationFlags(factory->host);
}

#endif

struct qemu_dxgi_factory_EnumAdapterByLuid
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t luid_low, luid_high;
    uint64_t adapter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_EnumAdapterByLuid(IDXGIFactory5 *iface, LUID luid, REFIID iid,
        void **adapter)
{
    struct qemu_dxgi_factory_EnumAdapterByLuid call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);
    struct qemu_dxgi_adapter *adapter_impl;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_ENUMADAPTERBYLUID);
    call.iface = (ULONG_PTR)factory;
    call.luid_low = luid.LowPart;
    call.luid_high = luid.HighPart;

    qemu_syscall(&call.super);
    hr = call.super.iret;
    if (FAILED(hr))
        return hr;

    adapter_impl = (struct qemu_dxgi_adapter *)(ULONG_PTR)call.adapter;
    qemu_dxgi_adapter_guest_init(adapter_impl);
    hr = IDXGIAdapter_QueryInterface(&adapter_impl->IDXGIAdapter3_iface, iid, adapter);
    IDXGIAdapter_Release(&adapter_impl->IDXGIAdapter3_iface);

    return hr;
}

#else

void qemu_dxgi_factory_EnumAdapterByLuid(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_EnumAdapterByLuid *c = (struct qemu_dxgi_factory_EnumAdapterByLuid *)call;
    struct qemu_dxgi_factory *factory;
    struct qemu_dxgi_adapter *adapter;
    IDXGIAdapter3 *host;
    LUID luid;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);
    luid.LowPart = c->luid_low;
    luid.HighPart = c->luid_high;

    c->super.iret = IDXGIFactory5_EnumAdapterByLuid(factory->host, luid, &IID_IDXGIAdapter3, (void **)&host);
    if (FAILED(c->super.iret))
        return;

    c->super.iret = qemu_dxgi_adapter_create(factory, host, &adapter);
    if (FAILED(c->super.iret))
        IDXGIAdapter3_Release(host);

    c->adapter = QEMU_H2G(adapter);
}

#endif

struct qemu_dxgi_factory_EnumWarpAdapter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t adapter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_EnumWarpAdapter(IDXGIFactory5 *iface, REFIID iid, void **adapter)
{
    struct qemu_dxgi_factory_EnumWarpAdapter call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_ENUMWARPADAPTER);
    call.iface = (ULONG_PTR)factory;
    call.iid = (ULONG_PTR)iid;
    call.adapter = (ULONG_PTR)adapter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_EnumWarpAdapter(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_EnumWarpAdapter *c = (struct qemu_dxgi_factory_EnumWarpAdapter *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_EnumWarpAdapter(factory->host, QEMU_G2H(c->iid), QEMU_G2H(c->adapter));
}

#endif

struct qemu_dxgi_factory_CheckFeatureSupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t feature;
    uint64_t feature_data;
    uint64_t data_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_factory_CheckFeatureSupport(IDXGIFactory5 *iface, DXGI_FEATURE feature, void *feature_data, UINT data_size)
{
    struct qemu_dxgi_factory_CheckFeatureSupport call;
    struct qemu_dxgi_factory *factory = impl_from_IDXGIFactory5(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_FACTORY_CHECKFEATURESUPPORT);
    call.iface = (ULONG_PTR)factory;
    call.feature = feature;
    call.feature_data = (ULONG_PTR)feature_data;
    call.data_size = data_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_factory_CheckFeatureSupport(struct qemu_syscall *call)
{
    struct qemu_dxgi_factory_CheckFeatureSupport *c = (struct qemu_dxgi_factory_CheckFeatureSupport *)call;
    struct qemu_dxgi_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IDXGIFactory5_CheckFeatureSupport(factory->host, c->feature, QEMU_G2H(c->feature_data), c->data_size);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct
{
    IDXGIFactory2Vtbl vtbl2;
    void *GetCreationFlags;
    void *EnumAdapterByLuid;
    void *EnumWarpAdapter;
    void *CheckFeatureSupport;
}
dxgi_factory_vtbl =
{
    {
        dxgi_factory_QueryInterface,
        dxgi_factory_AddRef,
        dxgi_factory_Release,
        dxgi_factory_SetPrivateData,
        dxgi_factory_SetPrivateDataInterface,
        dxgi_factory_GetPrivateData,
        dxgi_factory_GetParent,
        dxgi_factory_EnumAdapters,
        dxgi_factory_MakeWindowAssociation,
        dxgi_factory_GetWindowAssociation,
        dxgi_factory_CreateSwapChain,
        dxgi_factory_CreateSoftwareAdapter,
        /* IDXGIFactory1 methods */
        dxgi_factory_EnumAdapters1,
        dxgi_factory_IsCurrent,
        /* IDXGIFactory2 methods */
        dxgi_factory_IsWindowedStereoEnabled,
        dxgi_factory_CreateSwapChainForHwnd,
        dxgi_factory_CreateSwapChainForCoreWindow,
        dxgi_factory_GetSharedResourceAdapterLuid,
        dxgi_factory_RegisterOcclusionStatusWindow,
        dxgi_factory_RegisterStereoStatusEvent,
        dxgi_factory_UnregisterStereoStatus,
        dxgi_factory_RegisterStereoStatusWindow,
        dxgi_factory_RegisterOcclusionStatusEvent,
        dxgi_factory_UnregisterOcclusionStatus,
        dxgi_factory_CreateSwapChainForComposition,
    },
    /* IDXGIFactory3 methods */
    dxgi_factory_GetCreationFlags,
    /* IDXGIFactory4 methods */
    dxgi_factory_EnumAdapterByLuid,
    dxgi_factory_EnumWarpAdapter,
    /* IDXIGFactory5 methods */
    dxgi_factory_CheckFeatureSupport,
};

void qemu_dxgi_factory_guest_init(struct qemu_dxgi_factory *factory)
{
    factory->IDXGIFactory5_iface.lpVtbl = &dxgi_factory_vtbl.vtbl2;
}

struct qemu_dxgi_factory *unsafe_impl_from_IDXGIFactory(IDXGIFactory *iface)
{
    struct qemu_dxgi_factory *factory;
    HRESULT hr;

    if (!iface)
        return NULL;
    if (iface->lpVtbl != (void *)&dxgi_factory_vtbl)
    {
        /* FIXME: The reason of IWineDXGIFactory is apparently to QI our own factory interface through an
         * application-provided proxy... */
        WINE_FIXME("Handle other people's factory interfaces.\n");
        return NULL;
    }

    factory = impl_from_IDXGIFactory5((IDXGIFactory5 *)iface);
    return factory;
}


#else

HRESULT qemu_dxgi_factory_create(DWORD flags, DWORD version, struct qemu_dxgi_factory **factory)
{
    struct qemu_dxgi_factory *out;
    HRESULT hr;

    *factory = NULL;
    out = HeapAlloc(GetProcessHeap(), 0, sizeof(*out));
    if (!factory)
    {
        WINE_ERR("Out of memory\n");
        return E_OUTOFMEMORY;
    }

    switch (version)
    {
        case 0:
            hr = CreateDXGIFactory(&IID_IDXGIFactory5, (void **)&out->host);
            break;
        case 1:
            hr = CreateDXGIFactory1(&IID_IDXGIFactory5, (void **)&out->host);
            break;
        case 2:
            hr = CreateDXGIFactory2(flags, &IID_IDXGIFactory5, (void **)&out->host);
            break;
    }
    if (FAILED(hr))
    {
        WINE_FIXME("Creating the host factory failed: %#x.\n", hr);
        HeapFree(GetProcessHeap(), 0, out);
        out = NULL;
    }
    WINE_TRACE("Created factory wrapper %p, host factory %p.\n", out, out->host);

    *factory = out;
    return hr;
}

#endif
