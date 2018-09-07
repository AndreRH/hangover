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

struct qemu_wic_palette
{
    /* Guest fields */
    IWICPalette IWICPalette_iface;

    /* Host fields */
    IWICPalette *host;
};

struct qemu_WICPalette_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_palette *impl_from_IWICPalette(IWICPalette *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_palette, IWICPalette_iface);
}

static HRESULT WINAPI WICPalette_QueryInterface(IWICPalette *iface, REFIID iid, void **ppv)
{
    struct qemu_WICPalette_QueryInterface call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)palette;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICPalette_QueryInterface *c = (struct qemu_WICPalette_QueryInterface *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_QueryInterface(palette->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICPalette_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICPalette_AddRef(IWICPalette *iface)
{
    struct qemu_WICPalette_AddRef call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_ADDREF);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICPalette_AddRef *c = (struct qemu_WICPalette_AddRef *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_AddRef(palette->host);
}

#endif

struct qemu_WICPalette_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICPalette_Release(IWICPalette *iface)
{
    struct qemu_WICPalette_Release call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_RELEASE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_Release(struct qemu_syscall *call)
{
    struct qemu_WICPalette_Release *c = (struct qemu_WICPalette_Release *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_Release(palette->host);
}

#endif

struct qemu_WICPalette_InitializePredefined
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type;
    uint64_t add_transparent;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_InitializePredefined(IWICPalette *iface, WICBitmapPaletteType type,
        BOOL add_transparent)
{
    struct qemu_WICPalette_InitializePredefined call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_INITIALIZEPREDEFINED);
    call.iface = (ULONG_PTR)iface;
    call.type = type;
    call.add_transparent = add_transparent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_InitializePredefined(struct qemu_syscall *call)
{
    struct qemu_WICPalette_InitializePredefined *c = (struct qemu_WICPalette_InitializePredefined *)call;
    struct qemu_wic_palette *palette;

    WINE_TRACE("\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_InitializePredefined(palette->host, c->type, c->add_transparent);
}

#endif

struct qemu_WICPalette_InitializeCustom
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pColors;
    uint64_t colorCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_InitializeCustom(IWICPalette *iface, WICColor *pColors, UINT colorCount)
{
    struct qemu_WICPalette_InitializeCustom call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_INITIALIZECUSTOM);
    call.iface = (ULONG_PTR)iface;
    call.pColors = (ULONG_PTR)pColors;
    call.colorCount = colorCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_InitializeCustom(struct qemu_syscall *call)
{
    struct qemu_WICPalette_InitializeCustom *c = (struct qemu_WICPalette_InitializeCustom *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_InitializeCustom(palette->host, QEMU_G2H(c->pColors), c->colorCount);
}

#endif

struct qemu_WICPalette_InitializeFromBitmap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pISurface;
    uint64_t colorCount;
    uint64_t fAddTransparentColor;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_InitializeFromBitmap(IWICPalette *iface, IWICBitmapSource *pISurface, UINT colorCount, BOOL fAddTransparentColor)
{
    struct qemu_WICPalette_InitializeFromBitmap call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_INITIALIZEFROMBITMAP);
    call.iface = (ULONG_PTR)iface;
    call.pISurface = (ULONG_PTR)pISurface;
    call.colorCount = colorCount;
    call.fAddTransparentColor = fAddTransparentColor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_InitializeFromBitmap(struct qemu_syscall *call)
{
    struct qemu_WICPalette_InitializeFromBitmap *c = (struct qemu_WICPalette_InitializeFromBitmap *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_InitializeFromBitmap(palette->host, QEMU_G2H(c->pISurface), c->colorCount, c->fAddTransparentColor);
}

#endif

struct qemu_WICPalette_InitializeFromPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_InitializeFromPalette(IWICPalette *iface, IWICPalette *source)
{
    struct qemu_WICPalette_InitializeFromPalette call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_INITIALIZEFROMPALETTE);
    call.iface = (ULONG_PTR)iface;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_InitializeFromPalette(struct qemu_syscall *call)
{
    struct qemu_WICPalette_InitializeFromPalette *c = (struct qemu_WICPalette_InitializeFromPalette *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_InitializeFromPalette(palette->host, QEMU_G2H(c->source));
}

#endif

struct qemu_WICPalette_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pePaletteType;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_GetType(IWICPalette *iface, WICBitmapPaletteType *pePaletteType)
{
    struct qemu_WICPalette_GetType call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_GETTYPE);
    call.iface = (ULONG_PTR)iface;
    call.pePaletteType = (ULONG_PTR)pePaletteType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_GetType(struct qemu_syscall *call)
{
    struct qemu_WICPalette_GetType *c = (struct qemu_WICPalette_GetType *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_GetType(palette->host, QEMU_G2H(c->pePaletteType));
}

#endif

struct qemu_WICPalette_GetColorCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pcCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_GetColorCount(IWICPalette *iface, UINT *pcCount)
{
    struct qemu_WICPalette_GetColorCount call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_GETCOLORCOUNT);
    call.iface = (ULONG_PTR)iface;
    call.pcCount = (ULONG_PTR)pcCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_GetColorCount(struct qemu_syscall *call)
{
    struct qemu_WICPalette_GetColorCount *c = (struct qemu_WICPalette_GetColorCount *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_GetColorCount(palette->host, QEMU_G2H(c->pcCount));
}

#endif

struct qemu_WICPalette_GetColors
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t colorCount;
    uint64_t pColors;
    uint64_t pcActualColors;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_GetColors(IWICPalette *iface, UINT colorCount, WICColor *pColors, UINT *pcActualColors)
{
    struct qemu_WICPalette_GetColors call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_GETCOLORS);
    call.iface = (ULONG_PTR)iface;
    call.colorCount = colorCount;
    call.pColors = (ULONG_PTR)pColors;
    call.pcActualColors = (ULONG_PTR)pcActualColors;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_GetColors(struct qemu_syscall *call)
{
    struct qemu_WICPalette_GetColors *c = (struct qemu_WICPalette_GetColors *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_GetColors(palette->host, c->colorCount, QEMU_G2H(c->pColors), QEMU_G2H(c->pcActualColors));
}

#endif

struct qemu_WICPalette_IsBlackWhite
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfIsBlackWhite;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_IsBlackWhite(IWICPalette *iface, BOOL *pfIsBlackWhite)
{
    struct qemu_WICPalette_IsBlackWhite call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_ISBLACKWHITE);
    call.iface = (ULONG_PTR)iface;
    call.pfIsBlackWhite = (ULONG_PTR)pfIsBlackWhite;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_IsBlackWhite(struct qemu_syscall *call)
{
    struct qemu_WICPalette_IsBlackWhite *c = (struct qemu_WICPalette_IsBlackWhite *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_IsBlackWhite(palette->host, QEMU_G2H(c->pfIsBlackWhite));
}

#endif

struct qemu_WICPalette_IsGrayscale
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfIsGrayscale;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_IsGrayscale(IWICPalette *iface, BOOL *pfIsGrayscale)
{
    struct qemu_WICPalette_IsGrayscale call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_ISGRAYSCALE);
    call.iface = (ULONG_PTR)iface;
    call.pfIsGrayscale = (ULONG_PTR)pfIsGrayscale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_IsGrayscale(struct qemu_syscall *call)
{
    struct qemu_WICPalette_IsGrayscale *c = (struct qemu_WICPalette_IsGrayscale *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_IsGrayscale(palette->host, QEMU_G2H(c->pfIsGrayscale));
}

#endif

struct qemu_WICPalette_HasAlpha
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfHasAlpha;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPalette_HasAlpha(IWICPalette *iface, BOOL *pfHasAlpha)
{
    struct qemu_WICPalette_HasAlpha call;
    struct qemu_wic_palette *palette = impl_from_IWICPalette(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPALETTE_HASALPHA);
    call.iface = (ULONG_PTR)iface;
    call.pfHasAlpha = (ULONG_PTR)pfHasAlpha;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPalette_HasAlpha(struct qemu_syscall *call)
{
    struct qemu_WICPalette_HasAlpha *c = (struct qemu_WICPalette_HasAlpha *)call;
    struct qemu_wic_palette *palette;

    WINE_FIXME("Unverified!\n");
    palette = QEMU_G2H(c->iface);

    c->super.iret = IWICPalette_HasAlpha(palette->host, QEMU_G2H(c->pfHasAlpha));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IWICPaletteVtbl WICPalette_Vtbl =
{
    WICPalette_QueryInterface,
    WICPalette_AddRef,
    WICPalette_Release,
    WICPalette_InitializePredefined,
    WICPalette_InitializeCustom,
    WICPalette_InitializeFromBitmap,
    WICPalette_InitializeFromPalette,
    WICPalette_GetType,
    WICPalette_GetColorCount,
    WICPalette_GetColors,
    WICPalette_IsBlackWhite,
    WICPalette_IsGrayscale,
    WICPalette_HasAlpha
};

IWICPalette *WICPalette_init_guest(struct qemu_wic_palette *palette)
{
    palette->IWICPalette_iface.lpVtbl = &WICPalette_Vtbl;
    return &palette->IWICPalette_iface;
}

#else

struct qemu_wic_palette *WICPalette_create_host(IWICPalette *host)
{
    struct qemu_wic_palette *ret;
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
