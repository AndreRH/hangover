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
#include <d3d11_1.h>

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <dxgi1_2.h>
#include <debug.h>
#else
#include <dxgi1_5.h>
#include <wine/debug.h>
#endif

#include "thunk/qemu_dxgi.h"
#include "qemu_dxgi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_dxgi_swapchain_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dxgi_swapchain *impl_from_IDXGISwapChain1(IDXGISwapChain1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_swapchain, IDXGISwapChain1_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_QueryInterface(IDXGISwapChain1 *iface, REFIID riid, void **object)
{
    struct qemu_dxgi_swapchain_QueryInterface call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    WINE_TRACE("iface %p, riid %s, object %p\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(riid, &IID_IUnknown)
            || IsEqualGUID(riid, &IID_IDXGIObject)
            || IsEqualGUID(riid, &IID_IDXGIDeviceSubObject)
            || IsEqualGUID(riid, &IID_IDXGISwapChain)
            || IsEqualGUID(riid, &IID_IDXGISwapChain1))
    {
        IUnknown_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_QUERYINTERFACE);
    call.iface = (ULONG_PTR)swapchain;
    call.riid = (ULONG_PTR)riid;
    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_dxgi_swapchain_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_QueryInterface *c = (struct qemu_dxgi_swapchain_QueryInterface *)call;
    struct qemu_dxgi_swapchain *swapchain;
    IUnknown *obj;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_QueryInterface(swapchain->host, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_dxgi_swapchain_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_swapchain_AddRef(IDXGISwapChain1 *iface)
{
    struct qemu_dxgi_swapchain_AddRef call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_ADDREF);
    call.iface = (ULONG_PTR)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_AddRef(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_AddRef *c = (struct qemu_dxgi_swapchain_AddRef *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_AddRef(swapchain->host);
}

#endif

struct qemu_dxgi_swapchain_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_swapchain_Release(IDXGISwapChain1 *iface)
{
    struct qemu_dxgi_swapchain_Release call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_RELEASE);
    call.iface = (ULONG_PTR)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_Release(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_Release *c = (struct qemu_dxgi_swapchain_Release *)call;
    struct qemu_dxgi_swapchain *swapchain;
    struct qemu_dxgi_factory *factory;
    struct qemu_dxgi_device *device;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);
    factory = swapchain->factory;
    device = swapchain->device;

    IDXGIDevice2_AddRef(device->host);
    if (factory)
        IDXGIFactory5_AddRef(factory->host);

    c->super.iret = IDXGISwapChain1_Release(swapchain->host);

    qemu_dxgi_device_Release_internal(device);
    if (factory)
        qemu_dxgi_factory_Release_internal(factory);

    if (!c->super.iret)
        HeapFree(GetProcessHeap(), 0, swapchain);
}

#endif

struct qemu_dxgi_swapchain_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_SetPrivateData(IDXGISwapChain1 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_swapchain_SetPrivateData call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)swapchain;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_SetPrivateData *c = (struct qemu_dxgi_swapchain_SetPrivateData *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_SetPrivateData(swapchain->host, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_swapchain_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_SetPrivateDataInterface(IDXGISwapChain1 *iface, REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_swapchain_SetPrivateDataInterface call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)swapchain;
    call.guid = (ULONG_PTR)guid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_SetPrivateDataInterface *c = (struct qemu_dxgi_swapchain_SetPrivateDataInterface *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_SetPrivateDataInterface(swapchain->host, QEMU_G2H(c->guid), QEMU_G2H(c->object));
}

#endif

struct qemu_dxgi_swapchain_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetPrivateData(IDXGISwapChain1 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_swapchain_GetPrivateData call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)swapchain;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetPrivateData *c = (struct qemu_dxgi_swapchain_GetPrivateData *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetPrivateData(swapchain->host, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_swapchain_GetParent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetParent(IDXGISwapChain1 *iface, REFIID riid, void **parent)
{
    struct qemu_dxgi_swapchain_GetParent call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);
    struct qemu_dxgi_factory *factory;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETPARENT);
    call.iface = (ULONG_PTR)swapchain;
    call.riid = (ULONG_PTR)riid;
    call.parent = (ULONG_PTR)parent;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *parent = NULL;
        return call.super.iret;
    }

    factory = (struct qemu_dxgi_factory *)(ULONG_PTR)call.parent;
    return IDXGIFactory_QueryInterface(&factory->IDXGIFactory5_iface, riid, parent);
}

#else

void qemu_dxgi_swapchain_GetParent(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetParent *c = (struct qemu_dxgi_swapchain_GetParent *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    if (!swapchain->factory)
    {
        WINE_ERR("Implicit swapchain does not store reference to parent.\n");
        c->super.iret = E_NOINTERFACE;
    }
    else
    {
        c->super.iret = S_OK;
        c->parent = QEMU_H2G(swapchain->factory);
    }
}

#endif

struct qemu_dxgi_swapchain_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetDevice(IDXGISwapChain1 *iface, REFIID riid, void **device)
{
    struct qemu_dxgi_swapchain_GetDevice call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETDEVICE);
    call.iface = (ULONG_PTR)swapchain;
    call.riid = (ULONG_PTR)riid;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetDevice(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetDevice *c = (struct qemu_dxgi_swapchain_GetDevice *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetDevice(swapchain->host, QEMU_G2H(c->riid), QEMU_G2H(c->device));
}

#endif

struct qemu_dxgi_swapchain_Present
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sync_interval;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_Present(IDXGISwapChain1 *iface, UINT sync_interval, UINT flags)
{
    struct qemu_dxgi_swapchain_Present call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_PRESENT);
    call.iface = (ULONG_PTR)swapchain;
    call.sync_interval = sync_interval;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_Present(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_Present *c = (struct qemu_dxgi_swapchain_Present *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_Present(swapchain->host, c->sync_interval, c->flags);
}

#endif

struct qemu_dxgi_swapchain_GetBuffer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer_idx;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetBuffer(IDXGISwapChain1 *iface, UINT buffer_idx, REFIID riid, void **surface)
{
    struct qemu_dxgi_swapchain_GetBuffer call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);
    struct qemu_dxgi_surface *impl;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETBUFFER);
    call.iface = (ULONG_PTR)swapchain;
    call.buffer_idx = buffer_idx;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    impl = (struct qemu_dxgi_surface *)(ULONG_PTR)call.surface;

    if (impl->IDXGISurface1_iface.lpVtbl)
    {
        hr = IDXGISurface_QueryInterface(&impl->IDXGISurface1_iface, riid, surface);
        IDXGISurface_Release(&impl->IDXGISurface1_iface);
        return hr;
    }
    /* Ok, this is the call from qemu_dxgi_swapchain_guest_init. We can't call QI because we don't have a
     * vtable yet. Keep the reference from the host call and return the interface manually. */
    if (!IsEqualGUID(riid, &IID_IDXGISurface1))
        WINE_ERR("Unexpected GUID.\n");
    *surface = &impl->IDXGISurface1_iface;
    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetBuffer(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetBuffer *c = (struct qemu_dxgi_swapchain_GetBuffer *)call;
    struct qemu_dxgi_swapchain *swapchain;
    IDXGISurface1 *host;
    struct qemu_dxgi_surface *surface;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetBuffer(swapchain->host, c->buffer_idx, &IID_IDXGISurface1, (void **)&host);
    if (FAILED(c->super.iret))
        return;

    surface = surface_from_host(host);
    c->surface = QEMU_H2G(surface);
}

#endif

struct qemu_dxgi_swapchain_SetFullscreenState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fullscreen;
    uint64_t target;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_SetFullscreenState(IDXGISwapChain1 *iface, BOOL fullscreen,
        IDXGIOutput *target)
{
    struct qemu_dxgi_swapchain_SetFullscreenState call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_SETFULLSCREENSTATE);
    call.iface = (ULONG_PTR)swapchain;
    call.fullscreen = fullscreen;

    if (target)
    {
        call.target = (ULONG_PTR)unsafe_impl_from_IDXGIOutput((IUnknown *)target);
        if (!call.target)
        {
            WINE_FIXME("This is not the output we're looking for.\n");
            return E_FAIL;
        }
    }
    else
    {
        call.target = (ULONG_PTR)0;
    }

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_SetFullscreenState(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_SetFullscreenState *c = (struct qemu_dxgi_swapchain_SetFullscreenState *)call;
    struct qemu_dxgi_swapchain *swapchain;
    struct qemu_dxgi_output *target;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);
    target = QEMU_G2H(c->target);

    c->super.iret = IDXGISwapChain1_SetFullscreenState(swapchain->host, c->fullscreen,
            target ? (IDXGIOutput *)target->host : NULL);
}

#endif

struct qemu_dxgi_swapchain_GetFullscreenState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fullscreen;
    uint64_t target;
    uint64_t new_output;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetFullscreenState(IDXGISwapChain1 *iface, BOOL *fullscreen,
        IDXGIOutput **target)
{
    struct qemu_dxgi_swapchain_GetFullscreenState call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);
    struct qemu_dxgi_output *output_impl = NULL;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETFULLSCREENSTATE);
    call.iface = (ULONG_PTR)swapchain;
    call.fullscreen = (ULONG_PTR)fullscreen;
    call.target = (ULONG_PTR)target;

    qemu_syscall(&call.super);

    if (call.target)
    {
        output_impl = (struct qemu_dxgi_output *)(ULONG_PTR)call.target;
        if (call.new_output)
            qemu_dxgi_output_guest_init(output_impl);
        *target = (IDXGIOutput *)&output_impl->IDXGIOutput4_iface;
    }
    else if(target)
        *target = NULL;

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetFullscreenState(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetFullscreenState *c = (struct qemu_dxgi_swapchain_GetFullscreenState *)call;
    struct qemu_dxgi_swapchain *swapchain;
    IDXGIOutput4 *output = NULL;
    struct qemu_dxgi_output *output_impl = NULL;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->new_output = FALSE;
    c->super.iret = IDXGISwapChain1_GetFullscreenState(swapchain->host, QEMU_G2H(c->fullscreen),
            c->target ? (IDXGIOutput **)&output : NULL);

    if (output)
    {
        output_impl = output_from_host(output);
        if (!output_impl)
        {
            c->new_output = 1;
            c->super.iret = qemu_dxgi_output_create(swapchain->device->adapter, output, &output_impl);
            if (FAILED(c->super.iret))
                WINE_ERR("Failed to create an output wrapper.\n");
        }
    }
    c->target = QEMU_H2G(output_impl);
}

#endif

struct qemu_dxgi_swapchain_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetDesc(IDXGISwapChain1 *iface, DXGI_SWAP_CHAIN_DESC *desc)
{
    struct qemu_dxgi_swapchain_GetDesc call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETDESC);
    call.iface = (ULONG_PTR)swapchain;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetDesc(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetDesc *c = (struct qemu_dxgi_swapchain_GetDesc *)call;
    struct qemu_dxgi_swapchain *swapchain;
    DXGI_SWAP_CHAIN_DESC stack, *desc = &stack;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    desc = QEMU_G2H(c->desc);
#else
    if (!c->desc)
        desc = NULL;
#endif

    c->super.iret = IDXGISwapChain1_GetDesc(swapchain->host, desc);

#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(c->super.iret))
        DXGI_SWAP_CHAIN_DESC_h2g(QEMU_G2H(c->desc), desc);
#endif
}

#endif

struct qemu_dxgi_swapchain_ResizeBuffers
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t buffer_count;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_ResizeBuffers(IDXGISwapChain1 *iface, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT format, UINT flags)
{
    struct qemu_dxgi_swapchain_ResizeBuffers call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_RESIZEBUFFERS);
    call.iface = (ULONG_PTR)swapchain;
    call.buffer_count = buffer_count;
    call.width = width;
    call.height = height;
    call.format = format;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_ResizeBuffers(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_ResizeBuffers *c = (struct qemu_dxgi_swapchain_ResizeBuffers *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_ResizeBuffers(swapchain->host, c->buffer_count, c->width, c->height, c->format, c->flags);
}

#endif

struct qemu_dxgi_swapchain_ResizeTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t target_mode_desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_ResizeTarget(IDXGISwapChain1 *iface, const DXGI_MODE_DESC *target_mode_desc)
{
    struct qemu_dxgi_swapchain_ResizeTarget call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_RESIZETARGET);
    call.iface = (ULONG_PTR)swapchain;
    call.target_mode_desc = (ULONG_PTR)target_mode_desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_ResizeTarget(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_ResizeTarget *c = (struct qemu_dxgi_swapchain_ResizeTarget *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_ResizeTarget(swapchain->host, QEMU_G2H(c->target_mode_desc));
}

#endif

struct qemu_dxgi_swapchain_GetContainingOutput
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t output;
    uint64_t new_output;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetContainingOutput(IDXGISwapChain1 *iface, IDXGIOutput **output)
{
    struct qemu_dxgi_swapchain_GetContainingOutput call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);
    struct qemu_dxgi_output *output_impl;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETCONTAININGOUTPUT);
    call.iface = (ULONG_PTR)swapchain;
    call.output = (ULONG_PTR)output;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    output_impl = (struct qemu_dxgi_output *)(ULONG_PTR)call.output;

    if (call.new_output)
        qemu_dxgi_output_guest_init(output_impl);

    *output = (IDXGIOutput *)&output_impl->IDXGIOutput4_iface;

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetContainingOutput(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetContainingOutput *c = (struct qemu_dxgi_swapchain_GetContainingOutput *)call;
    struct qemu_dxgi_swapchain *swapchain;
    IDXGIOutput4 *host;
    struct qemu_dxgi_output *output_impl;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetContainingOutput(swapchain->host, c->output ? (IDXGIOutput **)&host : NULL);
    if (FAILED(c->super.iret))
        return;

    output_impl = output_from_host(host);
    if (!output_impl)
    {
        WINE_TRACE("Creating new output wrapper for host output %p.\n", host);
        c->new_output = 1;
        c->super.iret = qemu_dxgi_output_create(swapchain->device->adapter, host, &output_impl);
        if (FAILED(c->super.iret))
            IDXGIOutput4_Release(host);
    }
    c->output = QEMU_H2G(output_impl);
}

#endif

struct qemu_dxgi_swapchain_GetFrameStatistics
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetFrameStatistics(IDXGISwapChain1 *iface, DXGI_FRAME_STATISTICS *stats)
{
    struct qemu_dxgi_swapchain_GetFrameStatistics call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETFRAMESTATISTICS);
    call.iface = (ULONG_PTR)swapchain;
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetFrameStatistics(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetFrameStatistics *c = (struct qemu_dxgi_swapchain_GetFrameStatistics *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetFrameStatistics(swapchain->host, QEMU_G2H(c->stats));
}

#endif

struct qemu_dxgi_swapchain_GetLastPresentCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t last_present_count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetLastPresentCount(IDXGISwapChain1 *iface, UINT *last_present_count)
{
    struct qemu_dxgi_swapchain_GetLastPresentCount call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETLASTPRESENTCOUNT);
    call.iface = (ULONG_PTR)swapchain;
    call.last_present_count = (ULONG_PTR)last_present_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetLastPresentCount(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetLastPresentCount *c = (struct qemu_dxgi_swapchain_GetLastPresentCount *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetLastPresentCount(swapchain->host, QEMU_G2H(c->last_present_count));
}

#endif

struct qemu_dxgi_swapchain_GetDesc1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetDesc1(IDXGISwapChain1 *iface, DXGI_SWAP_CHAIN_DESC1 *desc)
{
    struct qemu_dxgi_swapchain_GetDesc1 call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETDESC1);
    call.iface = (ULONG_PTR)swapchain;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetDesc1(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetDesc1 *c = (struct qemu_dxgi_swapchain_GetDesc1 *)call;
    struct qemu_dxgi_swapchain *swapchain;

    /* DXGI_SWAP_CHAIN_DESC1 (unlike the base DXGI_SWAP_CHAIN_DESC) has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetDesc1(swapchain->host, QEMU_G2H(c->desc));
}

#endif

struct qemu_dxgi_swapchain_GetFullscreenDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetFullscreenDesc(IDXGISwapChain1 *iface,
        DXGI_SWAP_CHAIN_FULLSCREEN_DESC *desc)
{
    struct qemu_dxgi_swapchain_GetFullscreenDesc call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETFULLSCREENDESC);
    call.iface = (ULONG_PTR)swapchain;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetFullscreenDesc(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetFullscreenDesc *c = (struct qemu_dxgi_swapchain_GetFullscreenDesc *)call;
    struct qemu_dxgi_swapchain *swapchain;

    /* DXGI_SWAP_CHAIN_FULLSCREEN_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetFullscreenDesc(swapchain->host, QEMU_G2H(c->desc));
}

#endif

struct qemu_dxgi_swapchain_GetHwnd
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetHwnd(IDXGISwapChain1 *iface, HWND *hwnd)
{
    struct qemu_dxgi_swapchain_GetHwnd call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETHWND);
    call.iface = (ULONG_PTR)swapchain;
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
        *hwnd = (HWND)(ULONG_PTR)call.hwnd;

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetHwnd(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetHwnd *c = (struct qemu_dxgi_swapchain_GetHwnd *)call;
    struct qemu_dxgi_swapchain *swapchain;
    HWND hwnd;

    WINE_TRACE("\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetHwnd(swapchain->host, c->hwnd ? &hwnd : NULL);
    c->hwnd = QEMU_H2G(hwnd);
}

#endif

struct qemu_dxgi_swapchain_GetCoreWindow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t core_window;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetCoreWindow(IDXGISwapChain1 *iface, REFIID iid, void **core_window)
{
    struct qemu_dxgi_swapchain_GetCoreWindow call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETCOREWINDOW);
    call.iface = (ULONG_PTR)swapchain;
    call.iid = (ULONG_PTR)iid;
    call.core_window = (ULONG_PTR)core_window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetCoreWindow(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetCoreWindow *c = (struct qemu_dxgi_swapchain_GetCoreWindow *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetCoreWindow(swapchain->host, QEMU_G2H(c->iid), QEMU_G2H(c->core_window));
}

#endif

struct qemu_dxgi_swapchain_Present1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sync_interval;
    uint64_t flags;
    uint64_t present_parameters;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_Present1(IDXGISwapChain1 *iface, UINT sync_interval, UINT flags, const DXGI_PRESENT_PARAMETERS *present_parameters)
{
    struct qemu_dxgi_swapchain_Present1 call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_PRESENT1);
    call.iface = (ULONG_PTR)swapchain;
    call.sync_interval = sync_interval;
    call.flags = flags;
    call.present_parameters = (ULONG_PTR)present_parameters;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_Present1(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_Present1 *c = (struct qemu_dxgi_swapchain_Present1 *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_Present1(swapchain->host, c->sync_interval, c->flags, QEMU_G2H(c->present_parameters));
}

#endif

struct qemu_dxgi_swapchain_IsTemporaryMonoSupported
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static BOOL STDMETHODCALLTYPE dxgi_swapchain_IsTemporaryMonoSupported(IDXGISwapChain1 *iface)
{
    struct qemu_dxgi_swapchain_IsTemporaryMonoSupported call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_ISTEMPORARYMONOSUPPORTED);
    call.iface = (ULONG_PTR)swapchain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_IsTemporaryMonoSupported(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_IsTemporaryMonoSupported *c = (struct qemu_dxgi_swapchain_IsTemporaryMonoSupported *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_IsTemporaryMonoSupported(swapchain->host);
}

#endif

struct qemu_dxgi_swapchain_GetRestrictToOutput
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t output;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetRestrictToOutput(IDXGISwapChain1 *iface, IDXGIOutput **output)
{
    struct qemu_dxgi_swapchain_GetRestrictToOutput call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETRESTRICTTOOUTPUT);
    call.iface = (ULONG_PTR)swapchain;
    call.output = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetRestrictToOutput(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetRestrictToOutput *c = (struct qemu_dxgi_swapchain_GetRestrictToOutput *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetRestrictToOutput(swapchain->host, QEMU_G2H(c->output));
}

#endif

struct qemu_dxgi_swapchain_SetBackgroundColor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_SetBackgroundColor(IDXGISwapChain1 *iface, const DXGI_RGBA *color)
{
    struct qemu_dxgi_swapchain_SetBackgroundColor call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_SETBACKGROUNDCOLOR);
    call.iface = (ULONG_PTR)swapchain;
    call.color = (ULONG_PTR)color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_SetBackgroundColor(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_SetBackgroundColor *c = (struct qemu_dxgi_swapchain_SetBackgroundColor *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_SetBackgroundColor(swapchain->host, QEMU_G2H(c->color));
}

#endif

struct qemu_dxgi_swapchain_GetBackgroundColor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t color;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetBackgroundColor(IDXGISwapChain1 *iface, DXGI_RGBA *color)
{
    struct qemu_dxgi_swapchain_GetBackgroundColor call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETBACKGROUNDCOLOR);
    call.iface = (ULONG_PTR)swapchain;
    call.color = (ULONG_PTR)color;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetBackgroundColor(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetBackgroundColor *c = (struct qemu_dxgi_swapchain_GetBackgroundColor *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetBackgroundColor(swapchain->host, QEMU_G2H(c->color));
}

#endif

struct qemu_dxgi_swapchain_SetRotation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rotation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_SetRotation(IDXGISwapChain1 *iface, DXGI_MODE_ROTATION rotation)
{
    struct qemu_dxgi_swapchain_SetRotation call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_SETROTATION);
    call.iface = (ULONG_PTR)swapchain;
    call.rotation = rotation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_SetRotation(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_SetRotation *c = (struct qemu_dxgi_swapchain_SetRotation *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_SetRotation(swapchain->host, c->rotation);
}

#endif

struct qemu_dxgi_swapchain_GetRotation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rotation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_swapchain_GetRotation(IDXGISwapChain1 *iface, DXGI_MODE_ROTATION *rotation)
{
    struct qemu_dxgi_swapchain_GetRotation call;
    struct qemu_dxgi_swapchain *swapchain = impl_from_IDXGISwapChain1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_SWAPCHAIN_GETROTATION);
    call.iface = (ULONG_PTR)swapchain;
    call.rotation = (ULONG_PTR)rotation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_swapchain_GetRotation(struct qemu_syscall *call)
{
    struct qemu_dxgi_swapchain_GetRotation *c = (struct qemu_dxgi_swapchain_GetRotation *)call;
    struct qemu_dxgi_swapchain *swapchain;

    WINE_FIXME("Unverified!\n");
    swapchain = QEMU_G2H(c->iface);

    c->super.iret = IDXGISwapChain1_GetRotation(swapchain->host, QEMU_G2H(c->rotation));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDXGISwapChain1Vtbl dxgi_swapchain_vtbl =
{
    /* IUnknown methods */
    dxgi_swapchain_QueryInterface,
    dxgi_swapchain_AddRef,
    dxgi_swapchain_Release,
    /* IDXGIObject methods */
    dxgi_swapchain_SetPrivateData,
    dxgi_swapchain_SetPrivateDataInterface,
    dxgi_swapchain_GetPrivateData,
    dxgi_swapchain_GetParent,
    /* IDXGIDeviceSubObject methods */
    dxgi_swapchain_GetDevice,
    /* IDXGISwapChain methods */
    dxgi_swapchain_Present,
    dxgi_swapchain_GetBuffer,
    dxgi_swapchain_SetFullscreenState,
    dxgi_swapchain_GetFullscreenState,
    dxgi_swapchain_GetDesc,
    dxgi_swapchain_ResizeBuffers,
    dxgi_swapchain_ResizeTarget,
    dxgi_swapchain_GetContainingOutput,
    dxgi_swapchain_GetFrameStatistics,
    dxgi_swapchain_GetLastPresentCount,
    /* IDXGISwapChain1 methods */
    dxgi_swapchain_GetDesc1,
    dxgi_swapchain_GetFullscreenDesc,
    dxgi_swapchain_GetHwnd,
    dxgi_swapchain_GetCoreWindow,
    dxgi_swapchain_Present1,
    dxgi_swapchain_IsTemporaryMonoSupported,
    dxgi_swapchain_GetRestrictToOutput,
    dxgi_swapchain_SetBackgroundColor,
    dxgi_swapchain_GetBackgroundColor,
    dxgi_swapchain_SetRotation,
    dxgi_swapchain_GetRotation,
};

void qemu_dxgi_swapchain_guest_init(struct qemu_dxgi_swapchain *swapchain)
{
    DXGI_SWAP_CHAIN_DESC desc;
    UINT i;
    struct qemu_dxgi_surface *surface;
    IDXGISurface1 *surface_iface;
    HRESULT hr;

    swapchain->IDXGISwapChain1_iface.lpVtbl = &dxgi_swapchain_vtbl;

    hr = IDXGISwapChain_GetDesc(&swapchain->IDXGISwapChain1_iface, &desc);
    if (FAILED(hr))
        WINE_ERR("Failed to get swapchain desc.\n");

    for (i = 0; i < desc.BufferCount; ++i)
    {
        hr = IDXGISwapChain_GetBuffer(&swapchain->IDXGISwapChain1_iface, i, &IID_IDXGISurface1,
                (void **)&surface_iface);
        if (FAILED(hr))
            WINE_ERR("Failed to get buffer %u.\n", i);

        surface = impl_from_IDXGISurface1(surface_iface);
        qemu_dxgi_surface_guest_init(surface, NULL);
        IDXGISurface_Release(surface_iface);
    }
}

#else

HRESULT qemu_dxgi_swapchain_create(IDXGISwapChain1 *host, struct qemu_dxgi_device *device,
        struct qemu_dxgi_factory *factory, struct qemu_dxgi_swapchain **swapchain)
{
    struct qemu_dxgi_swapchain *obj;
    DXGI_SWAP_CHAIN_DESC desc;
    HRESULT hr;
    IDXGISurface1 *buffer;
    struct qemu_dxgi_surface *surface;
    UINT i;

    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory.\n");
        return E_OUTOFMEMORY;
    }

    obj->host = host;
    obj->device = device;
    obj->factory = factory;

    hr = IDXGISwapChain1_GetDesc(host, &desc);
    if (FAILED(hr))
        WINE_ERR("Failed to get swapchain desc.\n");

    for (i = 0; i < desc.BufferCount; ++i)
    {
        hr = IDXGISwapChain1_GetBuffer(host, i, &IID_IDXGISurface1, (void **)&buffer);
        if (FAILED(hr))
            WINE_ERR("Failed to get buffer %u.\n", i);

        hr = qemu_dxgi_surface_create(buffer, device, &surface);
        IDXGISurface1_Release(buffer);

        /* Freeing the swapchain will free already created wrappers. */
        if (FAILED(hr))
        {
            WINE_WARN("Creating a surface wrapper for buffer %u failed.\n", i);
            return hr;
        }
    }
    *swapchain = obj;

    return S_OK;
}

#endif
