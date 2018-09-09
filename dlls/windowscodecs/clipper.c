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

struct qemu_WICBitmapClipper_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_QueryInterface(IWICBitmapClipper *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapClipper_QueryInterface call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)clipper;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_QueryInterface *c = (struct qemu_WICBitmapClipper_QueryInterface *)call;
    struct qemu_wic_clipper *clipper;

    WINE_FIXME("Unverified!\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_QueryInterface(clipper->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICBitmapClipper_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapClipper_AddRef(IWICBitmapClipper *iface)
{
    struct qemu_WICBitmapClipper_AddRef call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_ADDREF);
    call.iface = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_AddRef *c = (struct qemu_WICBitmapClipper_AddRef *)call;
    struct qemu_wic_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_AddRef(clipper->host);
}

#endif

struct qemu_WICBitmapClipper_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapClipper_Release(IWICBitmapClipper *iface)
{
    struct qemu_WICBitmapClipper_Release call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_RELEASE);
    call.iface = (ULONG_PTR)clipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG qemu_WICBitmapClipper_Release_internal(struct qemu_wic_clipper *clipper)
{
    ULONG ref;

    if (clipper->source_clipper)
        IWICBitmapClipper_AddRef(clipper->source_clipper->host);
    else if (clipper->source_bitmap)
        IWICBitmap_AddRef(clipper->source_bitmap->bitmap_host);

    ref = IWICBitmapClipper_Release(clipper->host);

    if (clipper->source_clipper)
        qemu_WICBitmapClipper_Release_internal(clipper->source_clipper);
    else if (clipper->source_bitmap)
        qemu_WICBitmap_Release_internal(clipper->source_bitmap);

    if (!ref)
    {
        WINE_TRACE("Destroying clipper wrapper %p for host clipper %p.\n", clipper, clipper->host);
        HeapFree(GetProcessHeap(), 0, clipper);
    }

    return ref;
}

void qemu_WICBitmapClipper_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_Release *c = (struct qemu_WICBitmapClipper_Release *)call;
    struct qemu_wic_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);
    c->super.iret = qemu_WICBitmapClipper_Release_internal(clipper);
}

#endif

struct qemu_WICBitmapClipper_GetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_GetSize(IWICBitmapClipper *iface, UINT *width, UINT *height)
{
    struct qemu_WICBitmapClipper_GetSize call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_GETSIZE);
    call.iface = (ULONG_PTR)clipper;
    call.width = (ULONG_PTR)width;
    call.height = (ULONG_PTR)height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_GetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_GetSize *c = (struct qemu_WICBitmapClipper_GetSize *)call;
    struct qemu_wic_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_GetSize(clipper->host, QEMU_G2H(c->width), QEMU_G2H(c->height));
}

#endif

struct qemu_WICBitmapClipper_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_GetPixelFormat(IWICBitmapClipper *iface, WICPixelFormatGUID *format)
{
    struct qemu_WICBitmapClipper_GetPixelFormat call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)clipper;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_GetPixelFormat *c = (struct qemu_WICBitmapClipper_GetPixelFormat *)call;
    struct qemu_wic_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_GetPixelFormat(clipper->host, QEMU_G2H(c->format));
}

#endif

struct qemu_WICBitmapClipper_GetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dpiX;
    uint64_t dpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_GetResolution(IWICBitmapClipper *iface, double *dpiX, double *dpiY)
{
    struct qemu_WICBitmapClipper_GetResolution call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_GETRESOLUTION);
    call.iface = (ULONG_PTR)clipper;
    call.dpiX = (ULONG_PTR)dpiX;
    call.dpiY = (ULONG_PTR)dpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_GetResolution(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_GetResolution *c = (struct qemu_WICBitmapClipper_GetResolution *)call;
    struct qemu_wic_clipper *clipper;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_GetResolution(clipper->host, QEMU_G2H(c->dpiX), QEMU_G2H(c->dpiY));
}

#endif

struct qemu_WICBitmapClipper_CopyPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_CopyPalette(IWICBitmapClipper *iface, IWICPalette *palette)
{
    struct qemu_WICBitmapClipper_CopyPalette call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_COPYPALETTE);
    call.iface = (ULONG_PTR)clipper;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_CopyPalette *c = (struct qemu_WICBitmapClipper_CopyPalette *)call;
    struct qemu_wic_clipper *clipper;

    WINE_FIXME("Unverified!\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_CopyPalette(clipper->host, QEMU_G2H(c->palette));
}

#endif

struct qemu_WICBitmapClipper_CopyPixels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rc;
    uint64_t stride;
    uint64_t buffer_size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_CopyPixels(IWICBitmapClipper *iface, const WICRect *rc, UINT stride,
        UINT buffer_size, BYTE *buffer)
{
    struct qemu_WICBitmapClipper_CopyPixels call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_COPYPIXELS);
    call.iface = (ULONG_PTR)clipper;
    call.rc = (ULONG_PTR)rc;
    call.stride = stride;
    call.buffer_size = buffer_size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_CopyPixels(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_CopyPixels *c = (struct qemu_WICBitmapClipper_CopyPixels *)call;
    struct qemu_wic_clipper *clipper;

    /* WICRect has the same size in 32 and 64 bit. */
    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapClipper_CopyPixels(clipper->host, QEMU_G2H(c->rc), c->stride, c->buffer_size,
            QEMU_G2H(c->buffer));
}

#endif

struct qemu_WICBitmapClipper_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t bitmap, clipper, custom;
    uint64_t rc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapClipper_Initialize(IWICBitmapClipper *iface, IWICBitmapSource *source,
        const WICRect *rc)
{
    struct qemu_WICBitmapClipper_Initialize call;
    struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPCLIPPER_INITIALIZE);
    call.iface = (ULONG_PTR)clipper;

    if (!source)
    {
        call.bitmap = call.clipper = call.custom = 0;
    }
    else if (((IWICBitmap *)source)->lpVtbl == &WICBitmap_Vtbl)
    {
        struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap((IWICBitmap *)source);
        call.bitmap = (ULONG_PTR)bitmap;
        call.clipper = call.custom = 0;
    }
    else if (((IWICBitmapClipper *)source)->lpVtbl == &WICBitmapClipper_Vtbl)
    {
        struct qemu_wic_clipper *other = impl_from_IWICBitmapClipper((IWICBitmapClipper *)source);
        call.clipper = (ULONG_PTR)other;
        call.bitmap = call.custom = 0;
    }
    else
    {
        call.bitmap = call.clipper = 0;
        call.custom = (ULONG_PTR)source;
    }

    call.rc = (ULONG_PTR)rc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapClipper_Initialize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapClipper_Initialize *c = (struct qemu_WICBitmapClipper_Initialize *)call;
    struct qemu_wic_clipper *clipper, *other = NULL;
    struct qemu_bitmap_source *source_wrapper = NULL;
    IWICBitmapSource *host_source;
    struct qemu_wic_bitmap *bitmap = NULL;

    WINE_TRACE("\n");
    clipper = QEMU_G2H(c->iface);

    if (c->bitmap)
    {
        bitmap = QEMU_G2H(c->bitmap);
        host_source = (IWICBitmapSource *)bitmap->bitmap_host;
        WINE_TRACE("Found our bitmap %p, passing host %p.\n", bitmap, host_source);
        IWICBitmapSource_AddRef(host_source);
    }
    else if (c->clipper)
    {
        other = QEMU_G2H(c->clipper);
        host_source = (IWICBitmapSource *)other->host;
        WINE_TRACE("Found our clipper %p, passing host %p.\n", other, host_source);
        IWICBitmapSource_AddRef(host_source);
    }
    else if (c->custom)
    {
        WINE_TRACE("Creating a wrapper for unrecognized source %p.\n", (void *)c->custom);
        source_wrapper = bitmap_source_wrapper_create(c->custom);
        if (!source_wrapper)
        {
            WINE_WARN("Out of memory.\n");
            c->super.iret = E_OUTOFMEMORY;
            return;
        }
        host_source = &source_wrapper->IWICBitmapSource_iface;
    }
    else
    {
        host_source = NULL;
    }

    c->super.iret = IWICBitmapClipper_Initialize(clipper->host, host_source, QEMU_G2H(c->rc));

    /* Release our ref, the host clipper has its own if it wants one. */
    if (host_source)
        IWICBitmapSource_Release(host_source);

    if (SUCCEEDED(c->super.iret))
    {
        clipper->source_bitmap = bitmap;
        clipper->source_clipper = other;
    }
}

#endif

#ifdef QEMU_DLL_GUEST

const IWICBitmapClipperVtbl WICBitmapClipper_Vtbl =
{
    WICBitmapClipper_QueryInterface,
    WICBitmapClipper_AddRef,
    WICBitmapClipper_Release,
    WICBitmapClipper_GetSize,
    WICBitmapClipper_GetPixelFormat,
    WICBitmapClipper_GetResolution,
    WICBitmapClipper_CopyPalette,
    WICBitmapClipper_CopyPixels,
    WICBitmapClipper_Initialize
};

void WICBitmapClipper_init_guest(struct qemu_wic_clipper *clipper)
{
    clipper->IWICBitmapClipper_iface.lpVtbl = &WICBitmapClipper_Vtbl;
}

#else

struct qemu_wic_clipper *WICBitmapClipper_create_host(IWICBitmapClipper *host)
{
    struct qemu_wic_clipper *ret;
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
