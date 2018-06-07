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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST

#include <d3d11.h>
#include <debug.h>

#include <initguid.h>

#else

#include <d3d11_2.h>
#include <wine/debug.h>

#endif

#include "thunk/qemu_d3d11.h"

#include "qemudxgi.h"
#include "qemu_d3d11.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d11);

struct qemu_d3d11_blend_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_state *impl_from_ID3D11BlendState(ID3D11BlendState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D11BlendState_iface);
}

static inline struct qemu_d3d11_state *impl_from_ID3D10BlendState1(ID3D10BlendState1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D10BlendState1_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_blend_state_QueryInterface(ID3D11BlendState *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_blend_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_blend_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_QueryInterface *c = (struct qemu_d3d11_blend_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11BlendState_QueryInterface(state->host_bs11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_blend_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_blend_state_AddRef(ID3D11BlendState *iface)
{
    struct qemu_d3d11_blend_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_blend_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_AddRef *c = (struct qemu_d3d11_blend_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11BlendState_AddRef(state->host_bs11);
}

#endif

struct qemu_d3d11_blend_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_blend_state_Release(ID3D11BlendState *iface)
{
    struct qemu_d3d11_blend_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_blend_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_Release *c = (struct qemu_d3d11_blend_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11BlendState_Release(state->host_bs11);
}

#endif

struct qemu_d3d11_blend_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_blend_state_GetDevice(ID3D11BlendState *iface, ID3D11Device **device)
{
    struct qemu_d3d11_blend_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_blend_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_GetDevice *c = (struct qemu_d3d11_blend_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11BlendState_GetDevice(state->host_bs11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_blend_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_blend_state_GetPrivateData(ID3D11BlendState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_blend_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_blend_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_GetPrivateData *c = (struct qemu_d3d11_blend_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11BlendState_GetPrivateData(state->host_bs11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_blend_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_blend_state_SetPrivateData(ID3D11BlendState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_blend_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_blend_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_SetPrivateData *c = (struct qemu_d3d11_blend_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11BlendState_SetPrivateData(state->host_bs11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_blend_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_blend_state_SetPrivateDataInterface(ID3D11BlendState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_blend_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_blend_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_SetPrivateDataInterface *c = (struct qemu_d3d11_blend_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11BlendState_SetPrivateDataInterface(state->host_bs11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_blend_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_blend_state_GetDesc(ID3D11BlendState *iface, D3D11_BLEND_DESC *desc)
{
    struct qemu_d3d11_blend_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D11BlendState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_BLEND_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_blend_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_blend_state_GetDesc *c = (struct qemu_d3d11_blend_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11BlendState_GetDesc(state->host_bs11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_blend_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_blend_state_QueryInterface(ID3D10BlendState1 *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_blend_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_blend_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_QueryInterface *c = (struct qemu_d3d10_blend_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10BlendState1_QueryInterface(state->host_bs10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_blend_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_blend_state_AddRef(ID3D10BlendState1 *iface)
{
    struct qemu_d3d10_blend_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_blend_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_AddRef *c = (struct qemu_d3d10_blend_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10BlendState1_AddRef(state->host_bs10);
}

#endif

struct qemu_d3d10_blend_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_blend_state_Release(ID3D10BlendState1 *iface)
{
    struct qemu_d3d10_blend_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_blend_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_Release *c = (struct qemu_d3d10_blend_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10BlendState1_Release(state->host_bs10);
}

#endif

struct qemu_d3d10_blend_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_blend_state_GetDevice(ID3D10BlendState1 *iface, ID3D10Device **device)
{
    struct qemu_d3d10_blend_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_blend_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_GetDevice *c = (struct qemu_d3d10_blend_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10BlendState1_GetDevice(state->host_bs10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_blend_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_blend_state_GetPrivateData(ID3D10BlendState1 *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_blend_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_blend_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_GetPrivateData *c = (struct qemu_d3d10_blend_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10BlendState1_GetPrivateData(state->host_bs10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_blend_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_blend_state_SetPrivateData(ID3D10BlendState1 *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_blend_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_blend_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_SetPrivateData *c = (struct qemu_d3d10_blend_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10BlendState1_SetPrivateData(state->host_bs10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_blend_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_blend_state_SetPrivateDataInterface(ID3D10BlendState1 *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_blend_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_blend_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_SetPrivateDataInterface *c = (struct qemu_d3d10_blend_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10BlendState1_SetPrivateDataInterface(state->host_bs10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_blend_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_blend_state_GetDesc(ID3D10BlendState1 *iface, D3D10_BLEND_DESC *desc)
{
    struct qemu_d3d10_blend_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_blend_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_GetDesc *c = (struct qemu_d3d10_blend_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10BlendState1_GetDesc(state->host_bs10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_blend_state_GetDesc1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_blend_state_GetDesc1(ID3D10BlendState1 *iface, D3D10_BLEND_DESC1 *desc)
{
    struct qemu_d3d10_blend_state_GetDesc1 call;
    struct qemu_d3d11_state *state = impl_from_ID3D10BlendState1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_BLEND_STATE_GETDESC1);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_blend_state_GetDesc1(struct qemu_syscall *call)
{
    struct qemu_d3d10_blend_state_GetDesc1 *c = (struct qemu_d3d10_blend_state_GetDesc1 *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10BlendState1_GetDesc1(state->host_bs10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_depthstencil_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_state *impl_from_ID3D11DepthStencilState(ID3D11DepthStencilState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D11DepthStencilState_iface);
}

static inline struct qemu_d3d11_state *impl_from_ID3D10DepthStencilState(ID3D10DepthStencilState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D10DepthStencilState_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_state_QueryInterface(ID3D11DepthStencilState *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_depthstencil_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_QueryInterface *c = (struct qemu_d3d11_depthstencil_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilState_QueryInterface(state->host_ds11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_depthstencil_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_depthstencil_state_AddRef(ID3D11DepthStencilState *iface)
{
    struct qemu_d3d11_depthstencil_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_AddRef *c = (struct qemu_d3d11_depthstencil_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilState_AddRef(state->host_ds11);
}

#endif

struct qemu_d3d11_depthstencil_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_depthstencil_state_Release(ID3D11DepthStencilState *iface)
{
    struct qemu_d3d11_depthstencil_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_Release *c = (struct qemu_d3d11_depthstencil_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilState_Release(state->host_ds11);
}

#endif

struct qemu_d3d11_depthstencil_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_depthstencil_state_GetDevice(ID3D11DepthStencilState *iface, ID3D11Device **device)
{
    struct qemu_d3d11_depthstencil_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_depthstencil_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_GetDevice *c = (struct qemu_d3d11_depthstencil_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11DepthStencilState_GetDevice(state->host_ds11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_depthstencil_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_state_GetPrivateData(ID3D11DepthStencilState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_depthstencil_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_GetPrivateData *c = (struct qemu_d3d11_depthstencil_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilState_GetPrivateData(state->host_ds11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_depthstencil_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_state_SetPrivateData(ID3D11DepthStencilState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_depthstencil_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_SetPrivateData *c = (struct qemu_d3d11_depthstencil_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilState_SetPrivateData(state->host_ds11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_depthstencil_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_depthstencil_state_SetPrivateDataInterface(ID3D11DepthStencilState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_depthstencil_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_depthstencil_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_SetPrivateDataInterface *c = (struct qemu_d3d11_depthstencil_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11DepthStencilState_SetPrivateDataInterface(state->host_ds11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_depthstencil_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_depthstencil_state_GetDesc(ID3D11DepthStencilState *iface, D3D11_DEPTH_STENCIL_DESC *desc)
{
    struct qemu_d3d11_depthstencil_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D11DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_DEPTHSTENCIL_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_depthstencil_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_depthstencil_state_GetDesc *c = (struct qemu_d3d11_depthstencil_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11DepthStencilState_GetDesc(state->host_ds11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_depthstencil_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_state_QueryInterface(ID3D10DepthStencilState *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_depthstencil_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_QueryInterface *c = (struct qemu_d3d10_depthstencil_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilState_QueryInterface(state->host_ds10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_depthstencil_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_depthstencil_state_AddRef(ID3D10DepthStencilState *iface)
{
    struct qemu_d3d10_depthstencil_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_AddRef *c = (struct qemu_d3d10_depthstencil_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilState_AddRef(state->host_ds10);
}

#endif

struct qemu_d3d10_depthstencil_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_depthstencil_state_Release(ID3D10DepthStencilState *iface)
{
    struct qemu_d3d10_depthstencil_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_Release *c = (struct qemu_d3d10_depthstencil_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilState_Release(state->host_ds10);
}

#endif

struct qemu_d3d10_depthstencil_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_depthstencil_state_GetDevice(ID3D10DepthStencilState *iface, ID3D10Device **device)
{
    struct qemu_d3d10_depthstencil_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_depthstencil_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_GetDevice *c = (struct qemu_d3d10_depthstencil_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10DepthStencilState_GetDevice(state->host_ds10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_depthstencil_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_state_GetPrivateData(ID3D10DepthStencilState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_depthstencil_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_GetPrivateData *c = (struct qemu_d3d10_depthstencil_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilState_GetPrivateData(state->host_ds10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_depthstencil_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_state_SetPrivateData(ID3D10DepthStencilState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_depthstencil_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_SetPrivateData *c = (struct qemu_d3d10_depthstencil_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilState_SetPrivateData(state->host_ds10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_depthstencil_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_depthstencil_state_SetPrivateDataInterface(ID3D10DepthStencilState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_depthstencil_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_depthstencil_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_SetPrivateDataInterface *c = (struct qemu_d3d10_depthstencil_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10DepthStencilState_SetPrivateDataInterface(state->host_ds10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_depthstencil_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_depthstencil_state_GetDesc(ID3D10DepthStencilState *iface, D3D10_DEPTH_STENCIL_DESC *desc)
{
    struct qemu_d3d10_depthstencil_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D10DepthStencilState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_DEPTHSTENCIL_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_depthstencil_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_depthstencil_state_GetDesc *c = (struct qemu_d3d10_depthstencil_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10DepthStencilState_GetDesc(state->host_ds10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_rasterizer_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_state *impl_from_ID3D11RasterizerState(ID3D11RasterizerState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D11RasterizerState_iface);
}

static inline struct qemu_d3d11_state *impl_from_ID3D10RasterizerState(ID3D10RasterizerState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D10RasterizerState_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_rasterizer_state_QueryInterface(ID3D11RasterizerState *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_rasterizer_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rasterizer_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_QueryInterface *c = (struct qemu_d3d11_rasterizer_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RasterizerState_QueryInterface(state->host_rs11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_rasterizer_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_rasterizer_state_AddRef(ID3D11RasterizerState *iface)
{
    struct qemu_d3d11_rasterizer_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rasterizer_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_AddRef *c = (struct qemu_d3d11_rasterizer_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RasterizerState_AddRef(state->host_rs11);
}

#endif

struct qemu_d3d11_rasterizer_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_rasterizer_state_Release(ID3D11RasterizerState *iface)
{
    struct qemu_d3d11_rasterizer_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rasterizer_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_Release *c = (struct qemu_d3d11_rasterizer_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RasterizerState_Release(state->host_rs11);
}

#endif

struct qemu_d3d11_rasterizer_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_rasterizer_state_GetDevice(ID3D11RasterizerState *iface, ID3D11Device **device)
{
    struct qemu_d3d11_rasterizer_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_rasterizer_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_GetDevice *c = (struct qemu_d3d11_rasterizer_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11RasterizerState_GetDevice(state->host_rs11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_rasterizer_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_rasterizer_state_GetPrivateData(ID3D11RasterizerState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_rasterizer_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rasterizer_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_GetPrivateData *c = (struct qemu_d3d11_rasterizer_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RasterizerState_GetPrivateData(state->host_rs11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_rasterizer_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_rasterizer_state_SetPrivateData(ID3D11RasterizerState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_rasterizer_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rasterizer_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_SetPrivateData *c = (struct qemu_d3d11_rasterizer_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RasterizerState_SetPrivateData(state->host_rs11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_rasterizer_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_rasterizer_state_SetPrivateDataInterface(ID3D11RasterizerState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_rasterizer_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_rasterizer_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_SetPrivateDataInterface *c = (struct qemu_d3d11_rasterizer_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11RasterizerState_SetPrivateDataInterface(state->host_rs11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_rasterizer_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_rasterizer_state_GetDesc(ID3D11RasterizerState *iface, D3D11_RASTERIZER_DESC *desc)
{
    struct qemu_d3d11_rasterizer_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D11RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_RASTERIZER_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_rasterizer_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_rasterizer_state_GetDesc *c = (struct qemu_d3d11_rasterizer_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11RasterizerState_GetDesc(state->host_rs11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_rasterizer_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rasterizer_state_QueryInterface(ID3D10RasterizerState *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_rasterizer_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rasterizer_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_QueryInterface *c = (struct qemu_d3d10_rasterizer_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RasterizerState_QueryInterface(state->host_rs10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_rasterizer_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_rasterizer_state_AddRef(ID3D10RasterizerState *iface)
{
    struct qemu_d3d10_rasterizer_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rasterizer_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_AddRef *c = (struct qemu_d3d10_rasterizer_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RasterizerState_AddRef(state->host_rs10);
}

#endif

struct qemu_d3d10_rasterizer_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_rasterizer_state_Release(ID3D10RasterizerState *iface)
{
    struct qemu_d3d10_rasterizer_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rasterizer_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_Release *c = (struct qemu_d3d10_rasterizer_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RasterizerState_Release(state->host_rs10);
}

#endif

struct qemu_d3d10_rasterizer_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_rasterizer_state_GetDevice(ID3D10RasterizerState *iface, ID3D10Device **device)
{
    struct qemu_d3d10_rasterizer_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_rasterizer_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_GetDevice *c = (struct qemu_d3d10_rasterizer_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10RasterizerState_GetDevice(state->host_rs10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_rasterizer_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rasterizer_state_GetPrivateData(ID3D10RasterizerState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_rasterizer_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rasterizer_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_GetPrivateData *c = (struct qemu_d3d10_rasterizer_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RasterizerState_GetPrivateData(state->host_rs10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_rasterizer_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rasterizer_state_SetPrivateData(ID3D10RasterizerState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_rasterizer_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rasterizer_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_SetPrivateData *c = (struct qemu_d3d10_rasterizer_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RasterizerState_SetPrivateData(state->host_rs10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_rasterizer_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_rasterizer_state_SetPrivateDataInterface(ID3D10RasterizerState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_rasterizer_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_rasterizer_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_SetPrivateDataInterface *c = (struct qemu_d3d10_rasterizer_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10RasterizerState_SetPrivateDataInterface(state->host_rs10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_rasterizer_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_rasterizer_state_GetDesc(ID3D10RasterizerState *iface, D3D10_RASTERIZER_DESC *desc)
{
    struct qemu_d3d10_rasterizer_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D10RasterizerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_RASTERIZER_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_rasterizer_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_rasterizer_state_GetDesc *c = (struct qemu_d3d10_rasterizer_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10RasterizerState_GetDesc(state->host_rs10, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d11_sampler_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_d3d11_state *impl_from_ID3D11SamplerState(ID3D11SamplerState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D11SamplerState_iface);
}

static inline struct qemu_d3d11_state *impl_from_ID3D10SamplerState(ID3D10SamplerState *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_d3d11_state, ID3D10SamplerState_iface);
}

static HRESULT STDMETHODCALLTYPE d3d11_sampler_state_QueryInterface(ID3D11SamplerState *iface, REFIID riid, void **object)
{
    struct qemu_d3d11_sampler_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_sampler_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_QueryInterface *c = (struct qemu_d3d11_sampler_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11SamplerState_QueryInterface(state->host_ss11, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d11_sampler_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_sampler_state_AddRef(ID3D11SamplerState *iface)
{
    struct qemu_d3d11_sampler_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_sampler_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_AddRef *c = (struct qemu_d3d11_sampler_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11SamplerState_AddRef(state->host_ss11);
}

#endif

struct qemu_d3d11_sampler_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d11_sampler_state_Release(ID3D11SamplerState *iface)
{
    struct qemu_d3d11_sampler_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_sampler_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_Release *c = (struct qemu_d3d11_sampler_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11SamplerState_Release(state->host_ss11);
}

#endif

struct qemu_d3d11_sampler_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_sampler_state_GetDevice(ID3D11SamplerState *iface, ID3D11Device **device)
{
    struct qemu_d3d11_sampler_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_sampler_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_GetDevice *c = (struct qemu_d3d11_sampler_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11SamplerState_GetDevice(state->host_ss11, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d11_sampler_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_sampler_state_GetPrivateData(ID3D11SamplerState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d11_sampler_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_sampler_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_GetPrivateData *c = (struct qemu_d3d11_sampler_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11SamplerState_GetPrivateData(state->host_ss11, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_sampler_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_sampler_state_SetPrivateData(ID3D11SamplerState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d11_sampler_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_sampler_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_SetPrivateData *c = (struct qemu_d3d11_sampler_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11SamplerState_SetPrivateData(state->host_ss11, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_sampler_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d11_sampler_state_SetPrivateDataInterface(ID3D11SamplerState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d11_sampler_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d11_sampler_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_SetPrivateDataInterface *c = (struct qemu_d3d11_sampler_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D11SamplerState_SetPrivateDataInterface(state->host_ss11, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d11_sampler_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d11_sampler_state_GetDesc(ID3D11SamplerState *iface, D3D11_SAMPLER_DESC *desc)
{
    struct qemu_d3d11_sampler_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D11SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D11_SAMPLER_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d11_sampler_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d11_sampler_state_GetDesc *c = (struct qemu_d3d11_sampler_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D11SamplerState_GetDesc(state->host_ss11, QEMU_G2H(c->desc));
}

#endif

struct qemu_d3d10_sampler_state_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_sampler_state_QueryInterface(ID3D10SamplerState *iface, REFIID riid, void **object)
{
    struct qemu_d3d10_sampler_state_QueryInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.riid = (ULONG_PTR)riid;
    call.object = (ULONG_PTR)object;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_sampler_state_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_QueryInterface *c = (struct qemu_d3d10_sampler_state_QueryInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10SamplerState_QueryInterface(state->host_ss10, QEMU_G2H(c->riid), QEMU_G2H(c->object));
}

#endif

struct qemu_d3d10_sampler_state_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_sampler_state_AddRef(ID3D10SamplerState *iface)
{
    struct qemu_d3d10_sampler_state_AddRef call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_ADDREF);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_sampler_state_AddRef(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_AddRef *c = (struct qemu_d3d10_sampler_state_AddRef *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10SamplerState_AddRef(state->host_ss10);
}

#endif

struct qemu_d3d10_sampler_state_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG STDMETHODCALLTYPE d3d10_sampler_state_Release(ID3D10SamplerState *iface)
{
    struct qemu_d3d10_sampler_state_Release call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_RELEASE);
    call.iface = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_sampler_state_Release(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_Release *c = (struct qemu_d3d10_sampler_state_Release *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10SamplerState_Release(state->host_ss10);
}

#endif

struct qemu_d3d10_sampler_state_GetDevice
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_sampler_state_GetDevice(ID3D10SamplerState *iface, ID3D10Device **device)
{
    struct qemu_d3d10_sampler_state_GetDevice call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_GETDEVICE);
    call.iface = (ULONG_PTR)state;
    call.device = (ULONG_PTR)device;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_sampler_state_GetDevice(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_GetDevice *c = (struct qemu_d3d10_sampler_state_GetDevice *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10SamplerState_GetDevice(state->host_ss10, QEMU_G2H(c->device));
}

#endif

struct qemu_d3d10_sampler_state_GetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_sampler_state_GetPrivateData(ID3D10SamplerState *iface, REFGUID guid, UINT *data_size, void *data)
{
    struct qemu_d3d10_sampler_state_GetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_GETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = (ULONG_PTR)data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_sampler_state_GetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_GetPrivateData *c = (struct qemu_d3d10_sampler_state_GetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10SamplerState_GetPrivateData(state->host_ss10, QEMU_G2H(c->guid), QEMU_G2H(c->data_size), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_sampler_state_SetPrivateData
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data_size;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_sampler_state_SetPrivateData(ID3D10SamplerState *iface, REFGUID guid, UINT data_size, const void *data)
{
    struct qemu_d3d10_sampler_state_SetPrivateData call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_SETPRIVATEDATA);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data_size = data_size;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_sampler_state_SetPrivateData(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_SetPrivateData *c = (struct qemu_d3d10_sampler_state_SetPrivateData *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10SamplerState_SetPrivateData(state->host_ss10, QEMU_G2H(c->guid), c->data_size, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_sampler_state_SetPrivateDataInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT STDMETHODCALLTYPE d3d10_sampler_state_SetPrivateDataInterface(ID3D10SamplerState *iface, REFGUID guid, const IUnknown *data)
{
    struct qemu_d3d10_sampler_state_SetPrivateDataInterface call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_SETPRIVATEDATAINTERFACE);
    call.iface = (ULONG_PTR)state;
    call.guid = (ULONG_PTR)guid;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d10_sampler_state_SetPrivateDataInterface(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_SetPrivateDataInterface *c = (struct qemu_d3d10_sampler_state_SetPrivateDataInterface *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    c->super.iret = ID3D10SamplerState_SetPrivateDataInterface(state->host_ss10, QEMU_G2H(c->guid), QEMU_G2H(c->data));
}

#endif

struct qemu_d3d10_sampler_state_GetDesc
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t desc;
};

#ifdef QEMU_DLL_GUEST

static void STDMETHODCALLTYPE d3d10_sampler_state_GetDesc(ID3D10SamplerState *iface, D3D10_SAMPLER_DESC *desc)
{
    struct qemu_d3d10_sampler_state_GetDesc call;
    struct qemu_d3d11_state *state = impl_from_ID3D10SamplerState(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_D3D10_SAMPLER_STATE_GETDESC);
    call.iface = (ULONG_PTR)state;
    call.desc = (ULONG_PTR)desc;

    qemu_syscall(&call.super);
}

#else

void qemu_d3d10_sampler_state_GetDesc(struct qemu_syscall *call)
{
    struct qemu_d3d10_sampler_state_GetDesc *c = (struct qemu_d3d10_sampler_state_GetDesc *)call;
    struct qemu_d3d11_state *state;

    WINE_FIXME("Unverified!\n");
    state = QEMU_G2H(c->iface);

    ID3D10SamplerState_GetDesc(state->host_ss10, QEMU_G2H(c->desc));
}

#endif
