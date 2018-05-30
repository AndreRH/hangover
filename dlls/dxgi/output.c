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
#include <initguid.h>

#include <dxgi1_2.h>
#include <debug.h>

#include <initguid.h>
DEFINE_GUID(IID_IDXGIOutput4, 0xdc7dca35, 0x2196, 0x414d, 0x9f,0x53, 0x61,0x78,0x84,0x03,0x2a,0x60);
DEFINE_GUID(IID_IDXGIOutput3, 0x8a6bb301, 0x7e7e, 0x41f4, 0xa8,0xe0, 0x5b,0x32,0xf7,0xf9,0x9b,0x18);
DEFINE_GUID(IID_IDXGIOutput2, 0x595e39d1, 0x2724, 0x4663, 0x99,0xb1, 0xda,0x96,0x9d,0xe2,0x83,0x64);
DEFINE_GUID(IID_IDXGIOutput1, 0x00cddea8, 0x939b, 0x4b83, 0xa3,0x40, 0xa6,0x85,0x22,0x66,0x66,0xcc);

#else

#include <dxgi1_5.h>
#include <wine/debug.h>

#endif

#include "thunk/qemu_dxgi.h"

#include "qemu_dxgi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dxgi);

struct qemu_dxgi_output_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dxgi_output *impl_from_IDXGIOutput4(IDXGIOutput4 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_output, IDXGIOutput4_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_output_QueryInterface(IDXGIOutput4 *iface, REFIID riid, void **object)
{
    struct qemu_dxgi_output_QueryInterface call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(riid, &IID_IDXGIOutput4)
            || IsEqualGUID(riid, &IID_IDXGIOutput3)
            || IsEqualGUID(riid, &IID_IDXGIOutput2)
            || IsEqualGUID(riid, &IID_IDXGIOutput1)
            || IsEqualGUID(riid, &IID_IDXGIOutput)
            || IsEqualGUID(riid, &IID_IDXGIObject)
            || IsEqualGUID(riid, &IID_IUnknown))
    {
        IUnknown_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)output;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);

    *object = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_dxgi_output_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_QueryInterface *c = (struct qemu_dxgi_output_QueryInterface *)call;
    struct qemu_dxgi_output *output;
    IUnknown *obj;
    HRESULT hr;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);

    hr = IDXGIOutput4_QueryInterface(output->host, QEMU_G2H(c->riid), (void **)&obj);
    if (SUCCEEDED(hr))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_dxgi_output_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE dxgi_output_AddRef(IDXGIOutput4 *iface)
{
    struct qemu_dxgi_output_AddRef call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_ADDREF);
    call.iface = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_AddRef(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_AddRef *c = (struct qemu_dxgi_output_AddRef *)call;
    struct qemu_dxgi_output *output;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_AddRef(output->host);
}

#endif

struct qemu_dxgi_output_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

void __fastcall dxgi_output_guest_destroy(struct qemu_dxgi_output *output)
{
    wined3d_private_store_cleanup(&output->private_store);
}

static ULONG STDMETHODCALLTYPE dxgi_output_Release(IDXGIOutput4 *iface)
{
    struct qemu_dxgi_output_Release call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_RELEASE);
    call.iface = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_Release(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_Release *c = (struct qemu_dxgi_output_Release *)call;
    struct qemu_dxgi_output *output;
    struct qemu_dxgi_adapter *adapter;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);
    adapter = output->adapter;

    IDXGIAdapter3_AddRef(adapter->host);
    c->super.iret = IDXGIOutput4_Release(output->host);
    qemu_dxgi_adapter_Release_internal(adapter);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_SetPrivateData(IDXGIOutput4 *iface,
        REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    WINE_TRACE("iface %p, guid %s, data_size %u, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return dxgi_set_private_data(&output->private_store, guid, data_size, data);
}

static HRESULT STDMETHODCALLTYPE dxgi_output_SetPrivateDataInterface(IDXGIOutput4 *iface,
        REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    WINE_TRACE("iface %p, guid %s, object %p.\n", iface, wine_dbgstr_guid(guid), object);

    return dxgi_set_private_data_interface(&output->private_store, guid, object);
}

static HRESULT STDMETHODCALLTYPE dxgi_output_GetPrivateData(IDXGIOutput4 *iface,
        REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    WINE_TRACE("iface %p, guid %s, data_size %p, data %p.\n", iface, wine_dbgstr_guid(guid), data_size, data);

    return dxgi_get_private_data(&output->private_store, guid, data_size, data);
}

#endif

struct qemu_dxgi_output_GetParent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t parent;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetParent(IDXGIOutput4 *iface, REFIID riid, void **parent)
{
    struct qemu_dxgi_output_GetParent call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);
    struct qemu_dxgi_adapter *adapter;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETPARENT);
    call.iface = (ULONG_PTR)output;
    call.riid = (ULONG_PTR)riid;

    qemu_syscall(&call.super);
    adapter = (struct qemu_dxgi_adapter *)(ULONG_PTR)call.parent;

    return IDXGIAdapter_QueryInterface(&adapter->IDXGIAdapter3_iface, riid, parent);
}

#else

void qemu_dxgi_output_GetParent(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetParent *c = (struct qemu_dxgi_output_GetParent *)call;
    struct qemu_dxgi_output *output;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);
    c->parent = QEMU_H2G(output->adapter);
}

#endif

struct qemu_dxgi_output_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDesc(IDXGIOutput4 *iface, DXGI_OUTPUT_DESC *desc)
{
    struct qemu_dxgi_output_GetDesc call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETDESC);
    call.iface = (ULONG_PTR)output;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetDesc(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetDesc *c = (struct qemu_dxgi_output_GetDesc *)call;
    struct qemu_dxgi_output *output;
    DXGI_OUTPUT_DESC stack, *desc = &stack;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);

#if GUEST_BIT == HOST_BIT
    desc = QEMU_G2H(c->desc);
#else
    if (!c->desc)
        desc = NULL;
#endif

    c->super.iret = IDXGIOutput4_GetDesc(output->host, desc);

#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(c->super.iret))
        DXGI_OUTPUT_DESC_h2g(QEMU_G2H(c->desc), desc);
#endif
}

#endif

struct qemu_dxgi_output_GetDisplayModeList
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t flags;
    uint64_t mode_count;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDisplayModeList(IDXGIOutput4 *iface, DXGI_FORMAT format, UINT flags,
        UINT *mode_count, DXGI_MODE_DESC *desc)
{
    struct qemu_dxgi_output_GetDisplayModeList call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETDISPLAYMODELIST);
    call.iface = (ULONG_PTR)output;
    call.format = format;
    call.flags = flags;
    call.mode_count = (ULONG_PTR)mode_count;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetDisplayModeList(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetDisplayModeList *c = (struct qemu_dxgi_output_GetDisplayModeList *)call;
    struct qemu_dxgi_output *output;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetDisplayModeList(output->host, c->format, c->flags, QEMU_G2H(c->mode_count),
            QEMU_G2H(c->desc));
}

#endif

struct qemu_dxgi_output_FindClosestMatchingMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t closest_match;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_FindClosestMatchingMode(IDXGIOutput4 *iface, const DXGI_MODE_DESC *mode,
        DXGI_MODE_DESC *closest_match, IUnknown *device)
{
    struct qemu_dxgi_output_FindClosestMatchingMode call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);
    IDXGIDevice *my_device;

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_FINDCLOSESTMATCHINGMODE);
    call.iface = (ULONG_PTR)output;
    call.mode = (ULONG_PTR)mode;
    call.closest_match = (ULONG_PTR)closest_match;

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

    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_FindClosestMatchingMode(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_FindClosestMatchingMode *c = (struct qemu_dxgi_output_FindClosestMatchingMode *)call;
    struct qemu_dxgi_output *output;
    struct qemu_dxgi_device *device;

    /* DXGI_MODE_DESC has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);
    device = QEMU_G2H(c->device);

    c->super.iret = IDXGIOutput4_FindClosestMatchingMode(output->host, QEMU_G2H(c->mode), QEMU_G2H(c->closest_match),
            device ? (IUnknown *)device->host : NULL);
}

#endif

struct qemu_dxgi_output_WaitForVBlank
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_WaitForVBlank(IDXGIOutput4 *iface)
{
    struct qemu_dxgi_output_WaitForVBlank call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_WAITFORVBLANK);
    call.iface = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_WaitForVBlank(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_WaitForVBlank *c = (struct qemu_dxgi_output_WaitForVBlank *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_WaitForVBlank(output->host);
}

#endif

struct qemu_dxgi_output_TakeOwnership
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t exclusive;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_TakeOwnership(IDXGIOutput4 *iface, IUnknown *device, BOOL exclusive)
{
    struct qemu_dxgi_output_TakeOwnership call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_TAKEOWNERSHIP);
    call.iface = (ULONG_PTR)output;
    call.device = (ULONG_PTR)device;
    call.exclusive = exclusive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_TakeOwnership(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_TakeOwnership *c = (struct qemu_dxgi_output_TakeOwnership *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_TakeOwnership(output->host, QEMU_G2H(c->device), c->exclusive);
}

#endif

struct qemu_dxgi_output_ReleaseOwnership
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE dxgi_output_ReleaseOwnership(IDXGIOutput4 *iface)
{
    struct qemu_dxgi_output_ReleaseOwnership call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_RELEASEOWNERSHIP);
    call.iface = (ULONG_PTR)output;

    qemu_syscall(&call.super);
}

#else

void qemu_dxgi_output_ReleaseOwnership(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_ReleaseOwnership *c = (struct qemu_dxgi_output_ReleaseOwnership *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    IDXGIOutput4_ReleaseOwnership(output->host);
}

#endif

struct qemu_dxgi_output_GetGammaControlCapabilities
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t gamma_caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetGammaControlCapabilities(IDXGIOutput4 *iface, DXGI_GAMMA_CONTROL_CAPABILITIES *gamma_caps)
{
    struct qemu_dxgi_output_GetGammaControlCapabilities call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETGAMMACONTROLCAPABILITIES);
    call.iface = (ULONG_PTR)output;
    call.gamma_caps = (ULONG_PTR)gamma_caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetGammaControlCapabilities(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetGammaControlCapabilities *c = (struct qemu_dxgi_output_GetGammaControlCapabilities *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetGammaControlCapabilities(output->host, QEMU_G2H(c->gamma_caps));
}

#endif

struct qemu_dxgi_output_SetGammaControl
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t gamma_control;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_SetGammaControl(IDXGIOutput4 *iface, const DXGI_GAMMA_CONTROL *gamma_control)
{
    struct qemu_dxgi_output_SetGammaControl call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_SETGAMMACONTROL);
    call.iface = (ULONG_PTR)output;
    call.gamma_control = (ULONG_PTR)gamma_control;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_SetGammaControl(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_SetGammaControl *c = (struct qemu_dxgi_output_SetGammaControl *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_SetGammaControl(output->host, QEMU_G2H(c->gamma_control));
}

#endif

struct qemu_dxgi_output_GetGammaControl
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t gamma_control;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetGammaControl(IDXGIOutput4 *iface, DXGI_GAMMA_CONTROL *gamma_control)
{
    struct qemu_dxgi_output_GetGammaControl call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETGAMMACONTROL);
    call.iface = (ULONG_PTR)output;
    call.gamma_control = (ULONG_PTR)gamma_control;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetGammaControl(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetGammaControl *c = (struct qemu_dxgi_output_GetGammaControl *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetGammaControl(output->host, QEMU_G2H(c->gamma_control));
}

#endif

struct qemu_dxgi_output_SetDisplaySurface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_SetDisplaySurface(IDXGIOutput4 *iface, IDXGISurface *surface)
{
    struct qemu_dxgi_output_SetDisplaySurface call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_SETDISPLAYSURFACE);
    call.iface = (ULONG_PTR)output;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_SetDisplaySurface(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_SetDisplaySurface *c = (struct qemu_dxgi_output_SetDisplaySurface *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_SetDisplaySurface(output->host, QEMU_G2H(c->surface));
}

#endif

struct qemu_dxgi_output_GetDisplaySurfaceData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDisplaySurfaceData(IDXGIOutput4 *iface, IDXGISurface *surface)
{
    struct qemu_dxgi_output_GetDisplaySurfaceData call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETDISPLAYSURFACEDATA);
    call.iface = (ULONG_PTR)output;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetDisplaySurfaceData(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetDisplaySurfaceData *c = (struct qemu_dxgi_output_GetDisplaySurfaceData *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetDisplaySurfaceData(output->host, QEMU_G2H(c->surface));
}

#endif

struct qemu_dxgi_output_GetFrameStatistics
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stats;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetFrameStatistics(IDXGIOutput4 *iface, DXGI_FRAME_STATISTICS *stats)
{
    struct qemu_dxgi_output_GetFrameStatistics call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETFRAMESTATISTICS);
    call.iface = (ULONG_PTR)output;
    call.stats = (ULONG_PTR)stats;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetFrameStatistics(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetFrameStatistics *c = (struct qemu_dxgi_output_GetFrameStatistics *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetFrameStatistics(output->host, QEMU_G2H(c->stats));
}

#endif

struct qemu_dxgi_output_GetDisplayModeList1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t flags;
    uint64_t mode_count;
    uint64_t modes;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDisplayModeList1(IDXGIOutput4 *iface, DXGI_FORMAT format, UINT flags,
        UINT *mode_count, DXGI_MODE_DESC1 *modes)
{
    struct qemu_dxgi_output_GetDisplayModeList1 call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETDISPLAYMODELIST1);
    call.iface = (ULONG_PTR)output;
    call.format = format;
    call.flags = flags;
    call.mode_count = (ULONG_PTR)mode_count;
    call.modes = (ULONG_PTR)modes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetDisplayModeList1(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetDisplayModeList1 *c = (struct qemu_dxgi_output_GetDisplayModeList1 *)call;
    struct qemu_dxgi_output *output;

    WINE_TRACE("\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetDisplayModeList1(output->host, c->format, c->flags, QEMU_G2H(c->mode_count),
            QEMU_G2H(c->modes));
}

#endif

struct qemu_dxgi_output_FindClosestMatchingMode1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t closest_match;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_FindClosestMatchingMode1(IDXGIOutput4 *iface, const DXGI_MODE_DESC1 *mode,
        DXGI_MODE_DESC1 *closest_match, IUnknown *device)
{
    struct qemu_dxgi_output_FindClosestMatchingMode1 call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_FINDCLOSESTMATCHINGMODE1);
    call.iface = (ULONG_PTR)output;
    call.mode = (ULONG_PTR)mode;
    call.closest_match = (ULONG_PTR)closest_match;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_FindClosestMatchingMode1(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_FindClosestMatchingMode1 *c = (struct qemu_dxgi_output_FindClosestMatchingMode1 *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_FindClosestMatchingMode1(output->host, QEMU_G2H(c->mode), QEMU_G2H(c->closest_match), QEMU_G2H(c->device));
}

#endif

struct qemu_dxgi_output_GetDisplaySurfaceData1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t resource;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDisplaySurfaceData1(IDXGIOutput4 *iface, IDXGIResource *resource)
{
    struct qemu_dxgi_output_GetDisplaySurfaceData1 call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETDISPLAYSURFACEDATA1);
    call.iface = (ULONG_PTR)output;
    call.resource = (ULONG_PTR)resource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetDisplaySurfaceData1(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetDisplaySurfaceData1 *c = (struct qemu_dxgi_output_GetDisplaySurfaceData1 *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetDisplaySurfaceData1(output->host, QEMU_G2H(c->resource));
}

#endif

struct qemu_dxgi_output_DuplicateOutput
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
    uint64_t output_duplication;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_DuplicateOutput(IDXGIOutput4 *iface, IUnknown *device, IDXGIOutputDuplication **output_duplication)
{
    struct qemu_dxgi_output_DuplicateOutput call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_DUPLICATEOUTPUT);
    call.iface = (ULONG_PTR)output;
    call.device = (ULONG_PTR)device;
    call.output_duplication = (ULONG_PTR)output_duplication;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_DuplicateOutput(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_DuplicateOutput *c = (struct qemu_dxgi_output_DuplicateOutput *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_DuplicateOutput(output->host, QEMU_G2H(c->device), QEMU_G2H(c->output_duplication));
}

#endif

struct qemu_dxgi_output_SupportsOverlays
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static BOOL STDMETHODCALLTYPE dxgi_output_SupportsOverlays(IDXGIOutput4 *iface)
{
    struct qemu_dxgi_output_SupportsOverlays call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_SUPPORTSOVERLAYS);
    call.iface = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_SupportsOverlays(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_SupportsOverlays *c = (struct qemu_dxgi_output_SupportsOverlays *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_SupportsOverlays(output->host);
}

#endif

struct qemu_dxgi_output_CheckOverlaySupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t device;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_CheckOverlaySupport(IDXGIOutput4 *iface, DXGI_FORMAT format, IUnknown *device, UINT *flags)
{
    struct qemu_dxgi_output_CheckOverlaySupport call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_CHECKOVERLAYSUPPORT);
    call.iface = (ULONG_PTR)output;
    call.format = format;
    call.device = (ULONG_PTR)device;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_CheckOverlaySupport(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_CheckOverlaySupport *c = (struct qemu_dxgi_output_CheckOverlaySupport *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_CheckOverlaySupport(output->host, c->format, QEMU_G2H(c->device), QEMU_G2H(c->flags));
}

#endif

struct qemu_dxgi_output_CheckOverlayColorSpaceSupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t color_space;
    uint64_t device;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_CheckOverlayColorSpaceSupport(IDXGIOutput4 *iface, DXGI_FORMAT format, DXGI_COLOR_SPACE_TYPE color_space, IUnknown *device, UINT *flags)
{
    struct qemu_dxgi_output_CheckOverlayColorSpaceSupport call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_CHECKOVERLAYCOLORSPACESUPPORT);
    call.iface = (ULONG_PTR)output;
    call.format = format;
    call.color_space = color_space;
    call.device = (ULONG_PTR)device;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_CheckOverlayColorSpaceSupport(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_CheckOverlayColorSpaceSupport *c = (struct qemu_dxgi_output_CheckOverlayColorSpaceSupport *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_CheckOverlayColorSpaceSupport(output->host, c->format, c->color_space, QEMU_G2H(c->device), QEMU_G2H(c->flags));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct
{
    IDXGIOutputVtbl vtbl1;
    void *GetDisplayModeList1;
    void *FindClosestMatchingMode1;
    void *GetDisplaySurfaceData1;
    void *DuplicateOutput;
    void *SupportsOverlays;
    void *CheckOverlaySupport;
    void *CheckOverlayColorSpaceSupport;
}
dxgi_output_vtbl =
{
    {
        dxgi_output_QueryInterface,
        dxgi_output_AddRef,
        dxgi_output_Release,
        /* IDXGIObject methods */
        dxgi_output_SetPrivateData,
        dxgi_output_SetPrivateDataInterface,
        dxgi_output_GetPrivateData,
        dxgi_output_GetParent,
        /* IDXGIOutput methods */
        dxgi_output_GetDesc,
        dxgi_output_GetDisplayModeList,
        dxgi_output_FindClosestMatchingMode,
        dxgi_output_WaitForVBlank,
        dxgi_output_TakeOwnership,
        dxgi_output_ReleaseOwnership,
        dxgi_output_GetGammaControlCapabilities,
        dxgi_output_SetGammaControl,
        dxgi_output_GetGammaControl,
        dxgi_output_SetDisplaySurface,
        dxgi_output_GetDisplaySurfaceData,
        dxgi_output_GetFrameStatistics,
    },
    /* IDXGIOutput1 methods */
    dxgi_output_GetDisplayModeList1,
    dxgi_output_FindClosestMatchingMode1,
    dxgi_output_GetDisplaySurfaceData1,
    dxgi_output_DuplicateOutput,
    /* IDXGIOutput2 methods */
    dxgi_output_SupportsOverlays,
    /* IDXGIOutput3 methods */
    dxgi_output_CheckOverlaySupport,
    /* IDXGIOutput4 methods */
    dxgi_output_CheckOverlayColorSpaceSupport,
};

struct qemu_dxgi_output *unsafe_impl_from_IDXGIOutput(IUnknown *iface)
{
    IDXGIOutput4 *qemu_output;
    struct qemu_dxgi_output *output;
    HRESULT hr;

    if (!iface)
        return NULL;
    if (FAILED(hr = IUnknown_QueryInterface(iface, &IID_IDXGIOutput4, (void **)&qemu_output)))
    {
        WINE_ERR("Failed to get IDXGIOutput4 interface, hr %#x.\n", hr);
        return NULL;
    }
    if (qemu_output->lpVtbl != (void *)&dxgi_output_vtbl)
    {
        WINE_ERR("Handle other people's output interfaces.\n");
        output = NULL;
    }
    else
    {
        output = CONTAINING_RECORD(qemu_output, struct qemu_dxgi_output, IDXGIOutput4_iface);
    }
    IDXGIOutput_Release(qemu_output);
    return output;
}

void qemu_dxgi_output_guest_init(struct qemu_dxgi_output *output)
{
    output->IDXGIOutput4_iface.lpVtbl = &dxgi_output_vtbl.vtbl1;
    wined3d_private_store_init(&output->private_store);
}

#else

static inline struct qemu_dxgi_output *impl_from_priv_data(IUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dxgi_output, priv_data_iface);
}

static HRESULT STDMETHODCALLTYPE dxgi_surface_priv_data_QueryInterface(IUnknown *iface, REFIID riid, void **out)
{
    WINE_ERR("Unexpected call\n");
    *out = NULL;
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE dxgi_surface_priv_data_AddRef(IUnknown *iface)
{
    struct qemu_dxgi_output *output = impl_from_priv_data(iface);
    ULONG refcount = InterlockedIncrement(&output->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", output, refcount);

    return refcount;
}

static ULONG STDMETHODCALLTYPE dxgi_surface_priv_data_Release(IUnknown *iface)
{
    struct qemu_dxgi_output *output = impl_from_priv_data(iface);
    ULONG refcount = InterlockedDecrement(&output->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", output, refcount);

    if (!refcount)
    {
        WINE_TRACE("Destroying output wrapper %p for host output %p.\n", output, output->host);
        qemu_ops->qemu_execute(QEMU_G2H(dxgi_output_guest_destroy), QEMU_H2G(output));
        HeapFree(GetProcessHeap(), 0, output);
    }

    return refcount;
}

static const struct IUnknownVtbl priv_data_vtbl =
{
    /* IUnknown methods */
    dxgi_surface_priv_data_QueryInterface,
    dxgi_surface_priv_data_AddRef,
    dxgi_surface_priv_data_Release,
};

#include <initguid.h>

DEFINE_GUID(IID_Qemu_output_priv_data, 0xfd2efa6f, 0xaf8d, 0x4b6b, 0xbd, 0x1d, 0x12, 0x06, 0x3e, 0x15, 0x23, 0x33);

struct qemu_dxgi_output *output_from_host(IDXGIOutput4 *host)
{
    IUnknown *priv;
    DWORD size = sizeof(priv);
    HRESULT hr;

    hr = IDXGIOutput4_GetPrivateData(host, &IID_Qemu_output_priv_data, &size, &priv);
    if (FAILED(hr))
        return NULL;

    IUnknown_Release(priv);
    return impl_from_priv_data(priv);
}

HRESULT qemu_dxgi_output_create(struct qemu_dxgi_adapter *adapter, IDXGIOutput4 *host, struct qemu_dxgi_output **output)
{
    struct qemu_dxgi_output *obj;

    *output = NULL;
    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }
    obj->adapter = adapter;
    obj->host = host;

    obj->priv_data_iface.lpVtbl = &priv_data_vtbl;
    /* Leave the ref at 0, we want the host obj to own the only / final reference. */
    IDXGIOutput4_SetPrivateDataInterface(obj->host, &IID_Qemu_output_priv_data, &obj->priv_data_iface);

    *output = obj;
    return S_OK;
}

#endif
