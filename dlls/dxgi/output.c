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
    uint64_t object;
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

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)output;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_QueryInterface *c = (struct qemu_dxgi_output_QueryInterface *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_QueryInterface(output->host, QEMU_G2H(c->riid), QEMU_G2H(c->object));
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

    if (!c->super.iret)
    {
        WINE_TRACE("Destroying dxgi output wrapper %p (host output %p).\n", output, output->host);
        HeapFree(GetProcessHeap(), 0, output);
    }
}

#endif

struct qemu_dxgi_output_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_SetPrivateData(IDXGIOutput4 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_dxgi_output_SetPrivateData call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)output;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_SetPrivateData *c = (struct qemu_dxgi_output_SetPrivateData *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_SetPrivateData(output->host, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_dxgi_output_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_SetPrivateDataInterface(IDXGIOutput4 *iface, REFGUID guid, const IUnknown *object)
{
    struct qemu_dxgi_output_SetPrivateDataInterface call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)output;
    call.guid = (ULONG_PTR)guid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_SetPrivateDataInterface *c = (struct qemu_dxgi_output_SetPrivateDataInterface *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_SetPrivateDataInterface(output->host, QEMU_G2H(c->guid), QEMU_G2H(c->object));
}

#endif

struct qemu_dxgi_output_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE dxgi_output_GetPrivateData(IDXGIOutput4 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_dxgi_output_GetPrivateData call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)output;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_GetPrivateData *c = (struct qemu_dxgi_output_GetPrivateData *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetPrivateData(output->host, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
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

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDisplayModeList(IDXGIOutput4 *iface, DXGI_FORMAT format, UINT flags, UINT *mode_count, DXGI_MODE_DESC *desc)
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

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetDisplayModeList(output->host, c->format, c->flags, QEMU_G2H(c->mode_count), QEMU_G2H(c->desc));
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

static HRESULT STDMETHODCALLTYPE dxgi_output_FindClosestMatchingMode(IDXGIOutput4 *iface, const DXGI_MODE_DESC *mode, DXGI_MODE_DESC *closest_match, IUnknown *device)
{
    struct qemu_dxgi_output_FindClosestMatchingMode call;
    struct qemu_dxgi_output *output = impl_from_IDXGIOutput4(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_DXGI_OUTPUT_FINDCLOSESTMATCHINGMODE);
    call.iface = (ULONG_PTR)output;
    call.mode = (ULONG_PTR)mode;
    call.closest_match = (ULONG_PTR)closest_match;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_dxgi_output_FindClosestMatchingMode(struct qemu_syscall *call)
{
    struct qemu_dxgi_output_FindClosestMatchingMode *c = (struct qemu_dxgi_output_FindClosestMatchingMode *)call;
    struct qemu_dxgi_output *output;

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_FindClosestMatchingMode(output->host, QEMU_G2H(c->mode), QEMU_G2H(c->closest_match), QEMU_G2H(c->device));
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

static HRESULT STDMETHODCALLTYPE dxgi_output_GetDisplayModeList1(IDXGIOutput4 *iface, DXGI_FORMAT format, UINT flags, UINT *mode_count, DXGI_MODE_DESC1 *modes)
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

    WINE_FIXME("Unverified!\n");
    output = QEMU_G2H(c->iface);

    c->super.iret = IDXGIOutput4_GetDisplayModeList1(output->host, c->format, c->flags, QEMU_G2H(c->mode_count), QEMU_G2H(c->modes));
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

static HRESULT STDMETHODCALLTYPE dxgi_output_FindClosestMatchingMode1(IDXGIOutput4 *iface, const DXGI_MODE_DESC1 *mode, DXGI_MODE_DESC1 *closest_match, IUnknown *device)
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

void qemu_dxgi_output_guest_init(struct qemu_dxgi_output *output)
{
    output->IDXGIOutput4_iface.lpVtbl = &dxgi_output_vtbl.vtbl1;
}

#else

HRESULT qemu_dxgi_output_create(struct qemu_dxgi_adapter *adapter, UINT idx, struct qemu_dxgi_output **output)
{
    HRESULT hr;
    struct qemu_dxgi_output *obj;

    *output = NULL;
    obj = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*obj));
    if (!obj)
    {
        WINE_WARN("Out of memory\n");
        return E_OUTOFMEMORY;
    }
    obj->adapter = adapter;

    hr = IDXGIAdapter3_EnumOutputs(adapter->host, idx, (IDXGIOutput **)&obj->host);
    if (SUCCEEDED(hr))
        *output = obj;
    else
        HeapFree(GetProcessHeap(), 0, obj);
    return hr;
}

#endif
