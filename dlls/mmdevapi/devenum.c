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
#include <mmdeviceapi.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

#include "qemu_mmdevapi.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_mmdevapi);

struct qemu_mmdevcol
{
    /* Guest fields */
    IMMDeviceCollection IMMDeviceCollection_iface;

    /* Host fields */
    IMMDeviceCollection *host;
};

struct qemu_mmdevenum
{
    /* Guest fields */
    IMMDeviceEnumerator IMMDeviceEnumerator_iface;

    /* Host fields */
    IMMDeviceEnumerator *host;
};

struct qemu_mmpropstore
{
    /* Guest fields */
    IPropertyStore IPropertyStore_iface;

    /* Host fields */
    IPropertyStore *host;
};

struct qemu_MMDevice_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmdevice *impl_from_IMMDevice(IMMDevice *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevice, IMMDevice_iface);
}

static inline struct qemu_mmdevice *impl_from_IMMEndpoint(IMMEndpoint *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevice, IMMEndpoint_iface);
}

static HRESULT WINAPI MMDevice_QueryInterface(IMMDevice *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevice_QueryInterface call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevice_QueryInterface *c = (struct qemu_MMDevice_QueryInterface *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_QueryInterface(device->host_device, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevice_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevice_AddRef(IMMDevice *iface)
{
    struct qemu_MMDevice_AddRef call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevice_AddRef *c = (struct qemu_MMDevice_AddRef *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_AddRef(device->host_device);
}

#endif

struct qemu_MMDevice_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevice_Release(IMMDevice *iface)
{
    struct qemu_MMDevice_Release call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevice_Release *c = (struct qemu_MMDevice_Release *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_Release(device->host_device);
}

#endif

struct qemu_MMDevice_Activate
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t clsctx;
    uint64_t params;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_Activate(IMMDevice *iface, REFIID riid, DWORD clsctx, PROPVARIANT *params, void **ppv)
{
    struct qemu_MMDevice_Activate call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_ACTIVATE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.clsctx = clsctx;
    call.params = (ULONG_PTR)params;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_Activate(struct qemu_syscall *call)
{
    struct qemu_MMDevice_Activate *c = (struct qemu_MMDevice_Activate *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_Activate(device->host_device, QEMU_G2H(c->riid), c->clsctx, QEMU_G2H(c->params), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevice_OpenPropertyStore
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t access;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_OpenPropertyStore(IMMDevice *iface, DWORD access, IPropertyStore **ppv)
{
    struct qemu_MMDevice_OpenPropertyStore call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_OPENPROPERTYSTORE);
    call.iface = (ULONG_PTR)device;
    call.access = access;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_OpenPropertyStore(struct qemu_syscall *call)
{
    struct qemu_MMDevice_OpenPropertyStore *c = (struct qemu_MMDevice_OpenPropertyStore *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_OpenPropertyStore(device->host_device, c->access, QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevice_GetId
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t itemid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_GetId(IMMDevice *iface, WCHAR **itemid)
{
    struct qemu_MMDevice_GetId call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_GETID);
    call.iface = (ULONG_PTR)device;
    call.itemid = (ULONG_PTR)itemid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_GetId(struct qemu_syscall *call)
{
    struct qemu_MMDevice_GetId *c = (struct qemu_MMDevice_GetId *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_GetId(device->host_device, QEMU_G2H(c->itemid));
}

#endif

struct qemu_MMDevice_GetState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevice_GetState(IMMDevice *iface, DWORD *state)
{
    struct qemu_MMDevice_GetState call;
    struct qemu_mmdevice *device = impl_from_IMMDevice(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVICE_GETSTATE);
    call.iface = (ULONG_PTR)device;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevice_GetState(struct qemu_syscall *call)
{
    struct qemu_MMDevice_GetState *c = (struct qemu_MMDevice_GetState *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMDevice_GetState(device->host_device, QEMU_G2H(c->state));
}

#endif

struct qemu_MMEndpoint_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMEndpoint_QueryInterface(IMMEndpoint *iface, REFIID riid, void **ppv)
{
    struct qemu_MMEndpoint_QueryInterface call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)device;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_QueryInterface *c = (struct qemu_MMEndpoint_QueryInterface *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_QueryInterface(device->host_endpoint, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMEndpoint_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMEndpoint_AddRef(IMMEndpoint *iface)
{
    struct qemu_MMEndpoint_AddRef call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_ADDREF);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_AddRef *c = (struct qemu_MMEndpoint_AddRef *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_AddRef(device->host_endpoint);
}

#endif

struct qemu_MMEndpoint_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMEndpoint_Release(IMMEndpoint *iface)
{
    struct qemu_MMEndpoint_Release call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_RELEASE);
    call.iface = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_Release(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_Release *c = (struct qemu_MMEndpoint_Release *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_Release(device->host_endpoint);
}

#endif

struct qemu_MMEndpoint_GetDataFlow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flow;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMEndpoint_GetDataFlow(IMMEndpoint *iface, EDataFlow *flow)
{
    struct qemu_MMEndpoint_GetDataFlow call;
    struct qemu_mmdevice *device = impl_from_IMMEndpoint(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMENDPOINT_GETDATAFLOW);
    call.iface = (ULONG_PTR)device;
    call.flow = (ULONG_PTR)flow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMEndpoint_GetDataFlow(struct qemu_syscall *call)
{
    struct qemu_MMEndpoint_GetDataFlow *c = (struct qemu_MMEndpoint_GetDataFlow *)call;
    struct qemu_mmdevice *device;

    WINE_FIXME("Unverified!\n");
    device = QEMU_G2H(c->iface);

    c->super.iret = IMMEndpoint_GetDataFlow(device->host_endpoint, QEMU_G2H(c->flow));
}

#endif

struct qemu_MMDevCol_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmdevcol *impl_from_IMMDeviceCollection(IMMDeviceCollection *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevcol, IMMDeviceCollection_iface);
}

static HRESULT WINAPI MMDevCol_QueryInterface(IMMDeviceCollection *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevCol_QueryInterface call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)col;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_QueryInterface *c = (struct qemu_MMDevCol_QueryInterface *)call;
    struct qemu_mmdevcol *col;

    WINE_FIXME("Unverified!\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_QueryInterface(col->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevCol_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevCol_AddRef(IMMDeviceCollection *iface)
{
    struct qemu_MMDevCol_AddRef call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_ADDREF);
    call.iface = (ULONG_PTR)col;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_AddRef *c = (struct qemu_MMDevCol_AddRef *)call;
    struct qemu_mmdevcol *col;

    WINE_FIXME("Unverified!\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_AddRef(col->host);
}

#endif

struct qemu_MMDevCol_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevCol_Release(IMMDeviceCollection *iface)
{
    struct qemu_MMDevCol_Release call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_RELEASE);
    call.iface = (ULONG_PTR)col;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_Release *c = (struct qemu_MMDevCol_Release *)call;
    struct qemu_mmdevcol *col;

    WINE_FIXME("Unverified!\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_Release(col->host);
}

#endif

struct qemu_MMDevCol_GetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t numdevs;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevCol_GetCount(IMMDeviceCollection *iface, UINT *numdevs)
{
    struct qemu_MMDevCol_GetCount call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_GETCOUNT);
    call.iface = (ULONG_PTR)col;
    call.numdevs = (ULONG_PTR)numdevs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_GetCount(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_GetCount *c = (struct qemu_MMDevCol_GetCount *)call;
    struct qemu_mmdevcol *col;

    WINE_FIXME("Unverified!\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_GetCount(col->host, QEMU_G2H(c->numdevs));
}

#endif

struct qemu_MMDevCol_Item
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t n;
    uint64_t dev;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevCol_Item(IMMDeviceCollection *iface, UINT n, IMMDevice **dev)
{
    struct qemu_MMDevCol_Item call;
    struct qemu_mmdevcol *col = impl_from_IMMDeviceCollection(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVCOL_ITEM);
    call.iface = (ULONG_PTR)col;
    call.n = n;
    call.dev = (ULONG_PTR)dev;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevCol_Item(struct qemu_syscall *call)
{
    struct qemu_MMDevCol_Item *c = (struct qemu_MMDevCol_Item *)call;
    struct qemu_mmdevcol *col;

    WINE_FIXME("Unverified!\n");
    col = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceCollection_Item(col->host, c->n, QEMU_G2H(c->dev));
}

#endif

struct qemu_MMDevEnum_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmdevenum *impl_from_IMMDeviceEnumerator(IMMDeviceEnumerator *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmdevenum, IMMDeviceEnumerator_iface);
}

static HRESULT WINAPI MMDevEnum_QueryInterface(IMMDeviceEnumerator *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevEnum_QueryInterface call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_QUERYINTERFACE);
    call.iface = (ULONG_PTR)devenum;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_QueryInterface *c = (struct qemu_MMDevEnum_QueryInterface *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_QueryInterface(devenum->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevEnum_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevEnum_AddRef(IMMDeviceEnumerator *iface)
{
    struct qemu_MMDevEnum_AddRef call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_ADDREF);
    call.iface = (ULONG_PTR)devenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_AddRef *c = (struct qemu_MMDevEnum_AddRef *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_AddRef(devenum->host);
}

#endif

struct qemu_MMDevEnum_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevEnum_Release(IMMDeviceEnumerator *iface)
{
    struct qemu_MMDevEnum_Release call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_RELEASE);
    call.iface = (ULONG_PTR)devenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_Release *c = (struct qemu_MMDevEnum_Release *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_Release(devenum->host);
}

#endif

struct qemu_MMDevEnum_EnumAudioEndpoints
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flow;
    uint64_t mask;
    uint64_t devices;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_EnumAudioEndpoints(IMMDeviceEnumerator *iface, EDataFlow flow, DWORD mask, IMMDeviceCollection **devices)
{
    struct qemu_MMDevEnum_EnumAudioEndpoints call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_ENUMAUDIOENDPOINTS);
    call.iface = (ULONG_PTR)devenum;
    call.flow = flow;
    call.mask = mask;
    call.devices = (ULONG_PTR)devices;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_EnumAudioEndpoints(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_EnumAudioEndpoints *c = (struct qemu_MMDevEnum_EnumAudioEndpoints *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_EnumAudioEndpoints(devenum->host, c->flow, c->mask, QEMU_G2H(c->devices));
}

#endif

struct qemu_MMDevEnum_GetDefaultAudioEndpoint
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flow;
    uint64_t role;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_GetDefaultAudioEndpoint(IMMDeviceEnumerator *iface, EDataFlow flow, ERole role, IMMDevice **device)
{
    struct qemu_MMDevEnum_GetDefaultAudioEndpoint call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_GETDEFAULTAUDIOENDPOINT);
    call.iface = (ULONG_PTR)devenum;
    call.flow = flow;
    call.role = role;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_GetDefaultAudioEndpoint(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_GetDefaultAudioEndpoint *c = (struct qemu_MMDevEnum_GetDefaultAudioEndpoint *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_GetDefaultAudioEndpoint(devenum->host, c->flow, c->role, QEMU_G2H(c->device));
}

#endif

struct qemu_MMDevEnum_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t name;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_GetDevice(IMMDeviceEnumerator *iface, const WCHAR *name, IMMDevice **device)
{
    struct qemu_MMDevEnum_GetDevice call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_GETDEVICE);
    call.iface = (ULONG_PTR)devenum;
    call.name = (ULONG_PTR)name;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_GetDevice(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_GetDevice *c = (struct qemu_MMDevEnum_GetDevice *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_GetDevice(devenum->host, QEMU_G2H(c->name), QEMU_G2H(c->device));
}

#endif

struct qemu_MMDevEnum_RegisterEndpointNotificationCallback
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t client;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_RegisterEndpointNotificationCallback(IMMDeviceEnumerator *iface, IMMNotificationClient *client)
{
    struct qemu_MMDevEnum_RegisterEndpointNotificationCallback call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_REGISTERENDPOINTNOTIFICATIONCALLBACK);
    call.iface = (ULONG_PTR)devenum;
    call.client = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_RegisterEndpointNotificationCallback(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_RegisterEndpointNotificationCallback *c = (struct qemu_MMDevEnum_RegisterEndpointNotificationCallback *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_RegisterEndpointNotificationCallback(devenum->host, QEMU_G2H(c->client));
}

#endif

struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t client;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevEnum_UnregisterEndpointNotificationCallback(IMMDeviceEnumerator *iface, IMMNotificationClient *client)
{
    struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback call;
    struct qemu_mmdevenum *devenum = impl_from_IMMDeviceEnumerator(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVENUM_UNREGISTERENDPOINTNOTIFICATIONCALLBACK);
    call.iface = (ULONG_PTR)devenum;
    call.client = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevEnum_UnregisterEndpointNotificationCallback(struct qemu_syscall *call)
{
    struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback *c = (struct qemu_MMDevEnum_UnregisterEndpointNotificationCallback *)call;
    struct qemu_mmdevenum *devenum;

    WINE_FIXME("Unverified!\n");
    devenum = QEMU_G2H(c->iface);

    c->super.iret = IMMDeviceEnumerator_UnregisterEndpointNotificationCallback(devenum->host, QEMU_G2H(c->client));
}

#endif

struct qemu_MMDevPropStore_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_mmpropstore *impl_from_IPropertyStore(IPropertyStore *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_mmpropstore, IPropertyStore_iface);
}

static HRESULT WINAPI MMDevPropStore_QueryInterface(IPropertyStore *iface, REFIID riid, void **ppv)
{
    struct qemu_MMDevPropStore_QueryInterface call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)store;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_QueryInterface *c = (struct qemu_MMDevPropStore_QueryInterface *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_QueryInterface(store->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_MMDevPropStore_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevPropStore_AddRef(IPropertyStore *iface)
{
    struct qemu_MMDevPropStore_AddRef call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_ADDREF);
    call.iface = (ULONG_PTR)store;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_AddRef(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_AddRef *c = (struct qemu_MMDevPropStore_AddRef *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_AddRef(store->host);
}

#endif

struct qemu_MMDevPropStore_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MMDevPropStore_Release(IPropertyStore *iface)
{
    struct qemu_MMDevPropStore_Release call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_RELEASE);
    call.iface = (ULONG_PTR)store;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_Release(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_Release *c = (struct qemu_MMDevPropStore_Release *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_Release(store->host);
}

#endif

struct qemu_MMDevPropStore_GetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t nprops;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_GetCount(IPropertyStore *iface, DWORD *nprops)
{
    struct qemu_MMDevPropStore_GetCount call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_GETCOUNT);
    call.iface = (ULONG_PTR)store;
    call.nprops = (ULONG_PTR)nprops;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_GetCount(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_GetCount *c = (struct qemu_MMDevPropStore_GetCount *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_GetCount(store->host, QEMU_G2H(c->nprops));
}

#endif

struct qemu_MMDevPropStore_GetAt
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prop;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_GetAt(IPropertyStore *iface, DWORD prop, PROPERTYKEY *key)
{
    struct qemu_MMDevPropStore_GetAt call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_GETAT);
    call.iface = (ULONG_PTR)store;
    call.prop = prop;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_GetAt(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_GetAt *c = (struct qemu_MMDevPropStore_GetAt *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_GetAt(store->host, c->prop, QEMU_G2H(c->key));
}

#endif

struct qemu_MMDevPropStore_GetValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t key;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_GetValue(IPropertyStore *iface, REFPROPERTYKEY key, PROPVARIANT *pv)
{
    struct qemu_MMDevPropStore_GetValue call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_GETVALUE);
    call.iface = (ULONG_PTR)store;
    call.key = (ULONG_PTR)key;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_GetValue(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_GetValue *c = (struct qemu_MMDevPropStore_GetValue *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_GetValue(store->host, QEMU_G2H(c->key), QEMU_G2H(c->pv));
}

#endif

struct qemu_MMDevPropStore_SetValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t key;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_SetValue(IPropertyStore *iface, REFPROPERTYKEY key, REFPROPVARIANT pv)
{
    struct qemu_MMDevPropStore_SetValue call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_SETVALUE);
    call.iface = (ULONG_PTR)store;
    call.key = (ULONG_PTR)key;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_SetValue(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_SetValue *c = (struct qemu_MMDevPropStore_SetValue *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_SetValue(store->host, QEMU_G2H(c->key), QEMU_G2H(c->pv));
}

#endif

struct qemu_MMDevPropStore_Commit
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MMDevPropStore_Commit(IPropertyStore *iface)
{
    struct qemu_MMDevPropStore_Commit call;
    struct qemu_mmpropstore *store = impl_from_IPropertyStore(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_MMDEVPROPSTORE_COMMIT);
    call.iface = (ULONG_PTR)store;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MMDevPropStore_Commit(struct qemu_syscall *call)
{
    struct qemu_MMDevPropStore_Commit *c = (struct qemu_MMDevPropStore_Commit *)call;
    struct qemu_mmpropstore *store;

    WINE_FIXME("Unverified!\n");
    store = QEMU_G2H(c->iface);

    c->super.iret = IPropertyStore_Commit(store->host);
}

#endif
