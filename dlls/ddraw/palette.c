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
#include <wine/exception.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_ddraw_palette_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_palette *impl_from_IDirectDrawPalette(IDirectDrawPalette *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_palette, IDirectDrawPalette_iface);
}

static HRESULT WINAPI ddraw_palette_QueryInterface(IDirectDrawPalette *iface, REFIID refiid, void **obj)
{
    WINE_TRACE("iface %p, riid %s, object %p.\n", iface, wine_dbgstr_guid(refiid), obj);

    if (IsEqualGUID(refiid, &IID_IUnknown) || IsEqualGUID(refiid, &IID_IDirectDrawPalette))
    {
        *obj = iface;
        IDirectDrawPalette_AddRef(iface);
        return S_OK;
    }
    else
    {
        *obj = NULL;
        return E_NOINTERFACE;
    }
}

static ULONG WINAPI ddraw_palette_AddRef(IDirectDrawPalette *iface)
{
    struct qemu_palette *palette = impl_from_IDirectDrawPalette(iface);
    ULONG ref = InterlockedIncrement(&palette->ref);

    WINE_TRACE("%p increasing refcount to %u.\n", palette, ref);

    return ref;
}

static ULONG WINAPI ddraw_palette_Release(IDirectDrawPalette *iface)
{
    struct qemu_ddraw_palette_Release call;
    struct qemu_palette *palette = impl_from_IDirectDrawPalette(iface);
    ULONG ref = InterlockedDecrement(&palette->ref);

    WINE_TRACE("%p decreasing refcount to %u.\n", palette, ref);

    if (ref == 0)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_PALETTE_RELEASE);
        call.iface = (ULONG_PTR)palette;
    }

    return ref;
}

#else

void qemu_ddraw_palette_Release(struct qemu_syscall *call)
{
    struct qemu_ddraw_palette_Release *c = (struct qemu_ddraw_palette_Release *)call;
    struct qemu_palette *palette;

    WINE_TRACE("\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawPalette_Release(palette->host);
    if (c->super.iret)
        WINE_ERR("Unexpected palette refcount %lu.\n", c->super.iret);
    HeapFree(GetProcessHeap(), 0, palette);
}

#endif

struct qemu_ddraw_palette_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ddraw;
    uint64_t flags;
    uint64_t entries;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_palette_Initialize(IDirectDrawPalette *iface, IDirectDraw *ddraw, DWORD flags,
        PALETTEENTRY *entries)
{
    struct qemu_ddraw_palette_Initialize call;
    struct qemu_palette *palette = impl_from_IDirectDrawPalette(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_PALETTE_INITIALIZE);
    call.iface = (ULONG_PTR)palette;
    call.ddraw = (ULONG_PTR)ddraw;
    call.flags = flags;
    call.entries = (ULONG_PTR)entries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_palette_Initialize(struct qemu_syscall *call)
{
    struct qemu_ddraw_palette_Initialize *c = (struct qemu_ddraw_palette_Initialize *)call;
    struct qemu_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawPalette_Initialize(palette->host, QEMU_G2H(c->ddraw), c->flags, QEMU_G2H(c->entries));
}

#endif

struct qemu_ddraw_palette_GetCaps
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t caps;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_palette_GetCaps(IDirectDrawPalette *iface, DWORD *caps)
{
    struct qemu_ddraw_palette_GetCaps call;
    struct qemu_palette *palette = impl_from_IDirectDrawPalette(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_PALETTE_GETCAPS);
    call.iface = (ULONG_PTR)palette;
    call.caps = (ULONG_PTR)caps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_palette_GetCaps(struct qemu_syscall *call)
{
    struct qemu_ddraw_palette_GetCaps *c = (struct qemu_ddraw_palette_GetCaps *)call;
    struct qemu_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawPalette_GetCaps(palette->host, QEMU_G2H(c->caps));
}

#endif

struct qemu_ddraw_palette_SetEntries
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t start;
    uint64_t count;
    uint64_t entries;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_palette_SetEntries(IDirectDrawPalette *iface, DWORD flags, DWORD start, DWORD count,
        PALETTEENTRY *entries)
{
    struct qemu_ddraw_palette_SetEntries call;
    struct qemu_palette *palette = impl_from_IDirectDrawPalette(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_PALETTE_SETENTRIES);
    call.iface = (ULONG_PTR)palette;
    call.flags = flags;
    call.start = start;
    call.count = count;
    call.entries = (ULONG_PTR)entries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_palette_SetEntries(struct qemu_syscall *call)
{
    struct qemu_ddraw_palette_SetEntries *c = (struct qemu_ddraw_palette_SetEntries *)call;
    struct qemu_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawPalette_SetEntries(palette->host, c->flags, c->start, c->count, QEMU_G2H(c->entries));
}

#endif

struct qemu_ddraw_palette_GetEntries
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t start;
    uint64_t count;
    uint64_t entries;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ddraw_palette_GetEntries(IDirectDrawPalette *iface, DWORD flags, DWORD start, DWORD count,
        PALETTEENTRY *entries)
{
    struct qemu_ddraw_palette_GetEntries call;
    struct qemu_palette *palette = impl_from_IDirectDrawPalette(iface);
    call.super.id = QEMU_SYSCALL_ID(CALL_DDRAW_PALETTE_GETENTRIES);
    call.iface = (ULONG_PTR)palette;
    call.flags = flags;
    call.start = start;
    call.count = count;
    call.entries = (ULONG_PTR)entries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ddraw_palette_GetEntries(struct qemu_syscall *call)
{
    struct qemu_ddraw_palette_GetEntries *c = (struct qemu_ddraw_palette_GetEntries *)call;
    struct qemu_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IDirectDrawPalette_GetEntries(palette->host, c->flags, c->start, c->count, QEMU_G2H(c->entries));
}

#endif

#ifdef QEMU_DLL_GUEST

static const struct IDirectDrawPaletteVtbl ddraw_palette_vtbl =
{
    /*** IUnknown ***/
    ddraw_palette_QueryInterface,
    ddraw_palette_AddRef,
    ddraw_palette_Release,
    /*** IDirectDrawPalette ***/
    ddraw_palette_GetCaps,
    ddraw_palette_GetEntries,
    ddraw_palette_Initialize,
    ddraw_palette_SetEntries
};

struct qemu_palette *unsafe_impl_from_IDirectDrawPalette(IDirectDrawPalette *iface)
{
    if (!iface) return NULL;
    if (iface->lpVtbl != &ddraw_palette_vtbl)
        WINE_ERR("Invalid IDirectDrawPalette vtable!\n");
    return CONTAINING_RECORD(iface, struct qemu_palette, IDirectDrawPalette_iface);
}

void ddraw_palette_init(struct qemu_palette *palette)
{
    palette->IDirectDrawPalette_iface.lpVtbl = &ddraw_palette_vtbl;
    palette->ref = 1;
}

#endif
