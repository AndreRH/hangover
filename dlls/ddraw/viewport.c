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
#include <ddraw.h>
#include <d3d.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_d3d_viewport_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_viewport *impl_from_IDirect3DViewport3(IDirect3DViewport3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_viewport, IDirect3DViewport3_iface);
}

static HRESULT WINAPI d3d_viewport_QueryInterface(IDirect3DViewport3 *iface, REFIID riid, void **object)
{
    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(riid), object);

    if (IsEqualGUID(&IID_IDirect3DViewport3, riid) || IsEqualGUID(&IID_IDirect3DViewport2, riid)
            || IsEqualGUID(&IID_IDirect3DViewport, riid) || IsEqualGUID(&IID_IUnknown, riid))
    {
        IDirect3DViewport3_AddRef(iface);
        *object = iface;
        return S_OK;
    }

    WINE_WARN("%s not implemented, returning E_NOINTERFACE.\n", wine_dbgstr_guid(riid));

    *object = NULL;
    return E_NOINTERFACE;
}

static ULONG WINAPI d3d_viewport_AddRef(IDirect3DViewport3 *iface)
{
    struct qemu_viewport *viewport = impl_from_IDirect3DViewport3(iface);
    ULONG ref = InterlockedIncrement(&viewport->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", viewport, ref);

    return ref;
}

static ULONG WINAPI d3d_viewport_Release(IDirect3DViewport3 *iface)
{
    struct qemu_viewport *viewport = impl_from_IDirect3DViewport3(iface);
    ULONG ref = InterlockedDecrement(&viewport->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", viewport, ref);

    if (!ref)
    {
        WINE_FIXME("Implement destroy!\n");
    }

    return ref;
}

#else

void qemu_d3d_viewport_Release(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_Release *c = (struct qemu_d3d_viewport_Release *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_Release(viewport->host);

    HeapFree(GetProcessHeap(), 0, viewport);
}

#endif

struct qemu_d3d_viewport_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t d3d;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_Initialize(IDirect3DViewport3 *iface, IDirect3D *d3d)
{
    struct qemu_d3d_viewport_Initialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_INITIALIZE);
    call.iface = (ULONG_PTR)iface;
    call.d3d = (ULONG_PTR)d3d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_Initialize(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_Initialize *c = (struct qemu_d3d_viewport_Initialize *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_Initialize(viewport->host, QEMU_G2H(c->d3d));
}

#endif

struct qemu_d3d_viewport_GetViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_GetViewport(IDirect3DViewport3 *iface, D3DVIEWPORT *lpData)
{
    struct qemu_d3d_viewport_GetViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_GETVIEWPORT);
    call.iface = (ULONG_PTR)iface;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_GetViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_GetViewport *c = (struct qemu_d3d_viewport_GetViewport *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_GetViewport(viewport->host, QEMU_G2H(c->lpData));
}

#endif

struct qemu_d3d_viewport_SetViewport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_SetViewport(IDirect3DViewport3 *iface, D3DVIEWPORT *lpData)
{
    struct qemu_d3d_viewport_SetViewport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_SETVIEWPORT);
    call.iface = (ULONG_PTR)iface;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_SetViewport(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_SetViewport *c = (struct qemu_d3d_viewport_SetViewport *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_SetViewport(viewport->host, QEMU_G2H(c->lpData));
}

#endif

struct qemu_d3d_viewport_TransformVertices
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwVertexCount;
    uint64_t data;
    uint64_t dwFlags;
    uint64_t offscreen;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_TransformVertices(IDirect3DViewport3 *iface, DWORD dwVertexCount, D3DTRANSFORMDATA *data, DWORD dwFlags, DWORD *offscreen)
{
    struct qemu_d3d_viewport_TransformVertices call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_TRANSFORMVERTICES);
    call.iface = (ULONG_PTR)iface;
    call.dwVertexCount = dwVertexCount;
    call.data = (ULONG_PTR)data;
    call.dwFlags = dwFlags;
    call.offscreen = (ULONG_PTR)offscreen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_TransformVertices(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_TransformVertices *c = (struct qemu_d3d_viewport_TransformVertices *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_TransformVertices(viewport->host, c->dwVertexCount, QEMU_G2H(c->data), c->dwFlags, QEMU_G2H(c->offscreen));
}

#endif

struct qemu_d3d_viewport_LightElements
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t element_count;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_LightElements(IDirect3DViewport3 *iface, DWORD element_count, D3DLIGHTDATA *data)
{
    struct qemu_d3d_viewport_LightElements call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_LIGHTELEMENTS);
    call.iface = (ULONG_PTR)iface;
    call.element_count = element_count;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_LightElements(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_LightElements *c = (struct qemu_d3d_viewport_LightElements *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_LightElements(viewport->host, c->element_count, QEMU_G2H(c->data));
}

#endif

struct qemu_d3d_viewport_SetBackground
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_SetBackground(IDirect3DViewport3 *iface, D3DMATERIALHANDLE material)
{
    struct qemu_d3d_viewport_SetBackground call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_SETBACKGROUND);
    call.iface = (ULONG_PTR)iface;
    call.material = material;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_SetBackground(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_SetBackground *c = (struct qemu_d3d_viewport_SetBackground *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_SetBackground(viewport->host, c->material);
}

#endif

struct qemu_d3d_viewport_GetBackground
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t material;
    uint64_t valid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_GetBackground(IDirect3DViewport3 *iface, D3DMATERIALHANDLE *material, BOOL *valid)
{
    struct qemu_d3d_viewport_GetBackground call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_GETBACKGROUND);
    call.iface = (ULONG_PTR)iface;
    call.material = (ULONG_PTR)material;
    call.valid = (ULONG_PTR)valid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_GetBackground(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_GetBackground *c = (struct qemu_d3d_viewport_GetBackground *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_GetBackground(viewport->host, QEMU_G2H(c->material), QEMU_G2H(c->valid));
}

#endif

struct qemu_d3d_viewport_SetBackgroundDepth
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_SetBackgroundDepth(IDirect3DViewport3 *iface, IDirectDrawSurface *surface)
{
    struct qemu_d3d_viewport_SetBackgroundDepth call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_SETBACKGROUNDDEPTH);
    call.iface = (ULONG_PTR)iface;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_SetBackgroundDepth(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_SetBackgroundDepth *c = (struct qemu_d3d_viewport_SetBackgroundDepth *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_SetBackgroundDepth(viewport->host, QEMU_G2H(c->surface));
}

#endif

struct qemu_d3d_viewport_GetBackgroundDepth
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
    uint64_t valid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_GetBackgroundDepth(IDirect3DViewport3 *iface, IDirectDrawSurface **surface, BOOL *valid)
{
    struct qemu_d3d_viewport_GetBackgroundDepth call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_GETBACKGROUNDDEPTH);
    call.iface = (ULONG_PTR)iface;
    call.surface = (ULONG_PTR)surface;
    call.valid = (ULONG_PTR)valid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_GetBackgroundDepth(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_GetBackgroundDepth *c = (struct qemu_d3d_viewport_GetBackgroundDepth *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_GetBackgroundDepth(viewport->host, QEMU_G2H(c->surface), QEMU_G2H(c->valid));
}

#endif

struct qemu_d3d_viewport_Clear
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_Clear(IDirect3DViewport3 *iface, DWORD rect_count, D3DRECT *rects, DWORD flags)
{
    struct qemu_d3d_viewport_Clear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_CLEAR);
    call.iface = (ULONG_PTR)iface;
    call.rect_count = rect_count;
    call.rects = (ULONG_PTR)rects;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_Clear(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_Clear *c = (struct qemu_d3d_viewport_Clear *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_Clear(viewport->host, c->rect_count, QEMU_G2H(c->rects), c->flags);
}

#endif

struct qemu_d3d_viewport_AddLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDirect3DLight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_AddLight(IDirect3DViewport3 *iface, IDirect3DLight *lpDirect3DLight)
{
    struct qemu_d3d_viewport_AddLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_ADDLIGHT);
    call.iface = (ULONG_PTR)iface;
    call.lpDirect3DLight = (ULONG_PTR)lpDirect3DLight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_AddLight(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_AddLight *c = (struct qemu_d3d_viewport_AddLight *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_AddLight(viewport->host, QEMU_G2H(c->lpDirect3DLight));
}

#endif

struct qemu_d3d_viewport_DeleteLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDirect3DLight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_DeleteLight(IDirect3DViewport3 *iface, IDirect3DLight *lpDirect3DLight)
{
    struct qemu_d3d_viewport_DeleteLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_DELETELIGHT);
    call.iface = (ULONG_PTR)iface;
    call.lpDirect3DLight = (ULONG_PTR)lpDirect3DLight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_DeleteLight(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_DeleteLight *c = (struct qemu_d3d_viewport_DeleteLight *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_DeleteLight(viewport->host, QEMU_G2H(c->lpDirect3DLight));
}

#endif

struct qemu_d3d_viewport_NextLight
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDirect3DLight;
    uint64_t lplpDirect3DLight;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_NextLight(IDirect3DViewport3 *iface, IDirect3DLight *lpDirect3DLight, IDirect3DLight **lplpDirect3DLight, DWORD flags)
{
    struct qemu_d3d_viewport_NextLight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_NEXTLIGHT);
    call.iface = (ULONG_PTR)iface;
    call.lpDirect3DLight = (ULONG_PTR)lpDirect3DLight;
    call.lplpDirect3DLight = (ULONG_PTR)lplpDirect3DLight;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_NextLight(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_NextLight *c = (struct qemu_d3d_viewport_NextLight *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_NextLight(viewport->host, QEMU_G2H(c->lpDirect3DLight), QEMU_G2H(c->lplpDirect3DLight), c->flags);
}

#endif

struct qemu_d3d_viewport_GetViewport2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_GetViewport2(IDirect3DViewport3 *iface, D3DVIEWPORT2 *lpData)
{
    struct qemu_d3d_viewport_GetViewport2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_GETVIEWPORT2);
    call.iface = (ULONG_PTR)iface;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_GetViewport2(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_GetViewport2 *c = (struct qemu_d3d_viewport_GetViewport2 *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_GetViewport2(viewport->host, QEMU_G2H(c->lpData));
}

#endif

struct qemu_d3d_viewport_SetViewport2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_SetViewport2(IDirect3DViewport3 *iface, D3DVIEWPORT2 *lpData)
{
    struct qemu_d3d_viewport_SetViewport2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_SETVIEWPORT2);
    call.iface = (ULONG_PTR)iface;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_SetViewport2(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_SetViewport2 *c = (struct qemu_d3d_viewport_SetViewport2 *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_SetViewport2(viewport->host, QEMU_G2H(c->lpData));
}

#endif

struct qemu_d3d_viewport_SetBackgroundDepth2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_SetBackgroundDepth2(IDirect3DViewport3 *iface, IDirectDrawSurface4 *surface)
{
    struct qemu_d3d_viewport_SetBackgroundDepth2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_SETBACKGROUNDDEPTH2);
    call.iface = (ULONG_PTR)iface;
    call.surface = (ULONG_PTR)surface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_SetBackgroundDepth2(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_SetBackgroundDepth2 *c = (struct qemu_d3d_viewport_SetBackgroundDepth2 *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_SetBackgroundDepth2(viewport->host, QEMU_G2H(c->surface));
}

#endif

struct qemu_d3d_viewport_GetBackgroundDepth2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t surface;
    uint64_t valid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_GetBackgroundDepth2(IDirect3DViewport3 *iface, IDirectDrawSurface4 **surface, BOOL *valid)
{
    struct qemu_d3d_viewport_GetBackgroundDepth2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_GETBACKGROUNDDEPTH2);
    call.iface = (ULONG_PTR)iface;
    call.surface = (ULONG_PTR)surface;
    call.valid = (ULONG_PTR)valid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_GetBackgroundDepth2(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_GetBackgroundDepth2 *c = (struct qemu_d3d_viewport_GetBackgroundDepth2 *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_GetBackgroundDepth2(viewport->host, QEMU_G2H(c->surface), QEMU_G2H(c->valid));
}

#endif

struct qemu_d3d_viewport_Clear2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rect_count;
    uint64_t rects;
    uint64_t flags;
    uint64_t color;
    uint64_t depth;
    uint64_t stencil;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI d3d_viewport_Clear2(IDirect3DViewport3 *iface, DWORD rect_count, D3DRECT *rects, DWORD flags, DWORD color, D3DVALUE depth, DWORD stencil)
{
    struct qemu_d3d_viewport_Clear2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3D_VIEWPORT_CLEAR2);
    call.iface = (ULONG_PTR)iface;
    call.rect_count = rect_count;
    call.rects = (ULONG_PTR)rects;
    call.flags = flags;
    call.color = color;
    call.depth = depth;
    call.stencil = stencil;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_d3d_viewport_Clear2(struct qemu_syscall *call)
{
    struct qemu_d3d_viewport_Clear2 *c = (struct qemu_d3d_viewport_Clear2 *)call;
    struct qemu_viewport *viewport;

    WINE_FIXME("Unverified!\n");
    viewport = QEMU_G2H(c->iface);

    c->super.iret = IDirect3DViewport3_Clear2(viewport->host, c->rect_count, QEMU_G2H(c->rects), c->flags, c->color, c->depth, c->stencil);
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirect3DViewport3Vtbl d3d_viewport_vtbl =
{
    /*** IUnknown Methods ***/
    d3d_viewport_QueryInterface,
    d3d_viewport_AddRef,
    d3d_viewport_Release,
    /*** IDirect3DViewport Methods */
    d3d_viewport_Initialize,
    d3d_viewport_GetViewport,
    d3d_viewport_SetViewport,
    d3d_viewport_TransformVertices,
    d3d_viewport_LightElements,
    d3d_viewport_SetBackground,
    d3d_viewport_GetBackground,
    d3d_viewport_SetBackgroundDepth,
    d3d_viewport_GetBackgroundDepth,
    d3d_viewport_Clear,
    d3d_viewport_AddLight,
    d3d_viewport_DeleteLight,
    d3d_viewport_NextLight,
    /*** IDirect3DViewport2 Methods ***/
    d3d_viewport_GetViewport2,
    d3d_viewport_SetViewport2,
    /*** IDirect3DViewport3 Methods ***/
    d3d_viewport_SetBackgroundDepth2,
    d3d_viewport_GetBackgroundDepth2,
    d3d_viewport_Clear2,
};

void d3d_viewport_guest_init(struct qemu_viewport *viewport)
{
    viewport->IDirect3DViewport3_iface.lpVtbl = &d3d_viewport_vtbl;
    viewport->ref = 1;
}

#endif
