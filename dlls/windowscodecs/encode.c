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

struct qemu_WICBitmapFrameEncode_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_frame_encode *impl_from_IWICBitmapFrameEncode(IWICBitmapFrameEncode *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_frame_encode, IWICBitmapFrameEncode_iface);
}

static HRESULT WINAPI WICBitmapFrameEncode_QueryInterface(IWICBitmapFrameEncode *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapFrameEncode_QueryInterface call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)frame_encode;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_QueryInterface *c = (struct qemu_WICBitmapFrameEncode_QueryInterface *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_QueryInterface(frame_encode->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICBitmapFrameEncode_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapFrameEncode_AddRef(IWICBitmapFrameEncode *iface)
{
    struct qemu_WICBitmapFrameEncode_AddRef call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_ADDREF);
    call.iface = (ULONG_PTR)frame_encode;
    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_AddRef *c = (struct qemu_WICBitmapFrameEncode_AddRef *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_AddRef(frame_encode->host);
}

#endif

struct qemu_WICBitmapFrameEncode_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapFrameEncode_Release(IWICBitmapFrameEncode *iface)
{
    struct qemu_WICBitmapFrameEncode_Release call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_RELEASE);
    call.iface = (ULONG_PTR)frame_encode;
    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG qemu_WICBitmapEncoder_Release_internal(struct qemu_wic_encoder *wic_encoder);
void qemu_WICBitmapFrameEncode_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_Release *c = (struct qemu_WICBitmapFrameEncode_Release *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_TRACE("\n");
    frame_encode = QEMU_G2H(c->iface);

    IWICBitmapEncoder_AddRef(frame_encode->encoder->host);
    c->super.iret = IWICBitmapFrameEncode_Release(frame_encode->host);
    qemu_WICBitmapEncoder_Release_internal(frame_encode->encoder);

    if (!c->super.iret)
    {
        WINE_TRACE("Destroying frame encoder wrapper %p for host frame %p.\n", frame_encode, frame_encode->host);
        HeapFree(GetProcessHeap(), 0, frame_encode);
    }
}

#endif

struct qemu_WICBitmapFrameEncode_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIEncoderOptions;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_Initialize(IWICBitmapFrameEncode *iface, IPropertyBag2 *pIEncoderOptions)
{
    struct qemu_WICBitmapFrameEncode_Initialize call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_INITIALIZE);
    call.iface = (ULONG_PTR)frame_encode;
    call.pIEncoderOptions = (ULONG_PTR)pIEncoderOptions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_Initialize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_Initialize *c = (struct qemu_WICBitmapFrameEncode_Initialize *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_Initialize(frame_encode->host, QEMU_G2H(c->pIEncoderOptions));
}

#endif

struct qemu_WICBitmapFrameEncode_SetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t uiWidth;
    uint64_t uiHeight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetSize(IWICBitmapFrameEncode *iface, UINT uiWidth, UINT uiHeight)
{
    struct qemu_WICBitmapFrameEncode_SetSize call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETSIZE);
    call.iface = (ULONG_PTR)frame_encode;
    call.uiWidth = uiWidth;
    call.uiHeight = uiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetSize *c = (struct qemu_WICBitmapFrameEncode_SetSize *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_TRACE("\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetSize(frame_encode->host, c->uiWidth, c->uiHeight);
}

#endif

struct qemu_WICBitmapFrameEncode_SetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    double dpiX;
    double dpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetResolution(IWICBitmapFrameEncode *iface, double dpiX, double dpiY)
{
    struct qemu_WICBitmapFrameEncode_SetResolution call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETRESOLUTION);
    call.iface = (ULONG_PTR)frame_encode;
    call.dpiX = dpiX;
    call.dpiY = dpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetResolution(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetResolution *c = (struct qemu_WICBitmapFrameEncode_SetResolution *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetResolution(frame_encode->host, c->dpiX, c->dpiY);
}

#endif

struct qemu_WICBitmapFrameEncode_SetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetPixelFormat(IWICBitmapFrameEncode *iface,
        WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICBitmapFrameEncode_SetPixelFormat call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETPIXELFORMAT);
    call.iface = (ULONG_PTR)frame_encode;
    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetPixelFormat *c = (struct qemu_WICBitmapFrameEncode_SetPixelFormat *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_TRACE("\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetPixelFormat(frame_encode->host, QEMU_G2H(c->pPixelFormat));
}

#endif

struct qemu_WICBitmapFrameEncode_SetColorContexts
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cCount;
    uint64_t ppIColorContext;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetColorContexts(IWICBitmapFrameEncode *iface, UINT cCount, IWICColorContext **ppIColorContext)
{
    struct qemu_WICBitmapFrameEncode_SetColorContexts call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETCOLORCONTEXTS);
    call.iface = (ULONG_PTR)frame_encode;
    call.cCount = cCount;
    call.ppIColorContext = (ULONG_PTR)ppIColorContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetColorContexts(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetColorContexts *c = (struct qemu_WICBitmapFrameEncode_SetColorContexts *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetColorContexts(frame_encode->host, c->cCount, QEMU_G2H(c->ppIColorContext));
}

#endif

struct qemu_WICBitmapFrameEncode_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetPalette(IWICBitmapFrameEncode *iface, IWICPalette *palette)
{
    struct qemu_WICBitmapFrameEncode_SetPalette call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);
    struct qemu_wic_palette *pal_impl = unsafe_impl_from_IWICPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETPALETTE);
    call.iface = (ULONG_PTR)frame_encode;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetPalette *c = (struct qemu_WICBitmapFrameEncode_SetPalette *)call;
    struct qemu_wic_frame_encode *frame_encode;
    struct qemu_wic_palette *palette;

    WINE_TRACE("\n");
    frame_encode = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IWICBitmapFrameEncode_SetPalette(frame_encode->host, palette ? palette->host : NULL);
}

#endif

struct qemu_WICBitmapFrameEncode_SetThumbnail
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIThumbnail;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetThumbnail(IWICBitmapFrameEncode *iface, IWICBitmapSource *pIThumbnail)
{
    struct qemu_WICBitmapFrameEncode_SetThumbnail call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETTHUMBNAIL);
    call.iface = (ULONG_PTR)frame_encode;
    call.pIThumbnail = (ULONG_PTR)pIThumbnail;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetThumbnail(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetThumbnail *c = (struct qemu_WICBitmapFrameEncode_SetThumbnail *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetThumbnail(frame_encode->host, QEMU_G2H(c->pIThumbnail));
}

#endif

struct qemu_WICBitmapFrameEncode_WritePixels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lineCount;
    uint64_t cbStride;
    uint64_t cbBufferSize;
    uint64_t pbPixels;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_WritePixels(IWICBitmapFrameEncode *iface, UINT lineCount, UINT cbStride, UINT cbBufferSize, BYTE *pbPixels)
{
    struct qemu_WICBitmapFrameEncode_WritePixels call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_WRITEPIXELS);
    call.iface = (ULONG_PTR)frame_encode;
    call.lineCount = lineCount;
    call.cbStride = cbStride;
    call.cbBufferSize = cbBufferSize;
    call.pbPixels = (ULONG_PTR)pbPixels;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_WritePixels(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_WritePixels *c = (struct qemu_WICBitmapFrameEncode_WritePixels *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_WritePixels(frame_encode->host, c->lineCount, c->cbStride, c->cbBufferSize, QEMU_G2H(c->pbPixels));
}

#endif

struct qemu_WICBitmapFrameEncode_WriteSource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t bitmap, clipper, converter, custom;
    uint64_t prc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_WriteSource(IWICBitmapFrameEncode *iface,
        IWICBitmapSource *pIBitmapSource, WICRect *prc)
{
    struct qemu_WICBitmapFrameEncode_WriteSource call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_WRITESOURCE);
    call.iface = (ULONG_PTR)frame_encode;
    if (!pIBitmapSource)
    {
        call.bitmap = call.clipper = call.custom = call.converter = 0;
    }
    else if (((IWICBitmap *)pIBitmapSource)->lpVtbl == &WICBitmap_Vtbl)
    {
        struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap((IWICBitmap *)pIBitmapSource);
        call.bitmap = (ULONG_PTR)bitmap;
        call.clipper = call.custom = call.converter = 0;
    }
    else if (((IWICBitmapClipper *)pIBitmapSource)->lpVtbl == &WICBitmapClipper_Vtbl)
    {
        struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper((IWICBitmapClipper *)pIBitmapSource);
        call.clipper = (ULONG_PTR)clipper;
        call.bitmap = call.custom = call.converter = 0;
    }
    else if (((IWICFormatConverter *)pIBitmapSource)->lpVtbl == &WICFormatConverter_Vtbl)
    {
        struct qemu_wic_converter *converter = impl_from_IWICFormatConverter((IWICFormatConverter *)pIBitmapSource);
        call.converter = (ULONG_PTR)converter;
        call.clipper = call.bitmap = call.custom = 0;
    }
    else
    {
        call.bitmap = call.clipper = call.converter = 0;
        call.custom = (ULONG_PTR)pIBitmapSource;
    }
    call.prc = (ULONG_PTR)prc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_WriteSource(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_WriteSource *c = (struct qemu_WICBitmapFrameEncode_WriteSource *)call;
    struct qemu_wic_frame_encode *frame_encode;
    struct qemu_bitmap_source *source_wrapper = NULL;
    IWICBitmapSource *host_source;
    struct qemu_wic_bitmap *bitmap = NULL;
    struct qemu_wic_converter *converter = NULL;
    struct qemu_wic_clipper *clipper = NULL;

    WINE_TRACE("\n");
    frame_encode = QEMU_G2H(c->iface);

    if (c->bitmap)
    {
        bitmap = QEMU_G2H(c->bitmap);
        host_source = (IWICBitmapSource *)bitmap->bitmap_host;
        WINE_TRACE("Found our bitmap %p, passing host %p.\n", bitmap, host_source);
    }
    else if (c->clipper)
    {
        clipper = QEMU_G2H(c->clipper);
        host_source = (IWICBitmapSource *)clipper->host;
        WINE_TRACE("Found our clipper %p, passing host %p.\n", clipper, host_source);
    }
    else if (c->converter)
    {
        converter = QEMU_G2H(c->converter);
        host_source = (IWICBitmapSource *)converter->host;
        WINE_TRACE("Found our converter %p, passing host %p.\n", converter, host_source);
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

    c->super.iret = IWICBitmapFrameEncode_WriteSource(frame_encode->host, host_source, QEMU_G2H(c->prc));

    if (source_wrapper)
        IWICBitmapSource_Release(&source_wrapper->IWICBitmapSource_iface);
}

#endif

struct qemu_WICBitmapFrameEncode_Commit
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_Commit(IWICBitmapFrameEncode *iface)
{
    struct qemu_WICBitmapFrameEncode_Commit call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_COMMIT);
    call.iface = (ULONG_PTR)frame_encode;
    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_Commit(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_Commit *c = (struct qemu_WICBitmapFrameEncode_Commit *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_Commit(frame_encode->host);
}

#endif

struct qemu_WICBitmapFrameEncode_GetMetadataQueryWriter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIMetadataQueryWriter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_GetMetadataQueryWriter(IWICBitmapFrameEncode *iface, IWICMetadataQueryWriter **ppIMetadataQueryWriter)
{
    struct qemu_WICBitmapFrameEncode_GetMetadataQueryWriter call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_GETMETADATAQUERYWRITER);
    call.iface = (ULONG_PTR)frame_encode;
    call.ppIMetadataQueryWriter = (ULONG_PTR)ppIMetadataQueryWriter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_GetMetadataQueryWriter(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_GetMetadataQueryWriter *c = (struct qemu_WICBitmapFrameEncode_GetMetadataQueryWriter *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_GetMetadataQueryWriter(frame_encode->host, QEMU_G2H(c->ppIMetadataQueryWriter));
}

#endif

struct qemu_WICBitmapEncoder_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_encoder *impl_from_IWICBitmapEncoder(IWICBitmapEncoder *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_encoder, IWICBitmapEncoder_iface);
}

static HRESULT WINAPI WICBitmapEncoder_QueryInterface(IWICBitmapEncoder *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapEncoder_QueryInterface call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(iid), ppv);

    if (!ppv)
        return E_INVALIDARG;

    if (IsEqualIID(&IID_IUnknown, iid) || IsEqualIID(&IID_IWICBitmapEncoder, iid))
    {
        *ppv = &wic_encoder->IWICBitmapEncoder_iface;
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }


    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)wic_encoder;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    *ppv = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_WICBitmapEncoder_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_QueryInterface *c = (struct qemu_WICBitmapEncoder_QueryInterface *)call;
    struct qemu_wic_encoder *wic_encoder;
    IUnknown *obj;

    WINE_TRACE("\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_QueryInterface(wic_encoder->host, QEMU_G2H(c->iid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->iid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_WICBitmapEncoder_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapEncoder_AddRef(IWICBitmapEncoder *iface)
{
    struct qemu_WICBitmapEncoder_AddRef call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_ADDREF);
    call.iface = (ULONG_PTR)wic_encoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_AddRef *c = (struct qemu_WICBitmapEncoder_AddRef *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_TRACE("\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_AddRef(wic_encoder->host);
}

#endif

struct qemu_WICBitmapEncoder_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapEncoder_Release(IWICBitmapEncoder *iface)
{
    struct qemu_WICBitmapEncoder_Release call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_RELEASE);
    call.iface = (ULONG_PTR)wic_encoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG qemu_WICBitmapEncoder_Release_internal(struct qemu_wic_encoder *wic_encoder)
{
    ULONG ref = IWICBitmapEncoder_Release(wic_encoder->host);
    if (!ref)
    {
        WINE_TRACE("Destroying encoder wrapper %p for host encoder %p.\n", wic_encoder, wic_encoder->host);
        HeapFree(GetProcessHeap(), 0, wic_encoder);
    }

    return ref;
}

void qemu_WICBitmapEncoder_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_Release *c = (struct qemu_WICBitmapEncoder_Release *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_TRACE("\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = qemu_WICBitmapEncoder_Release_internal(wic_encoder);
}

#endif

struct qemu_WICBitmapEncoder_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t cacheOption;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_Initialize(IWICBitmapEncoder *iface, IStream *pIStream,
        WICBitmapEncoderCacheOption cacheOption)
{
    struct qemu_WICBitmapEncoder_Initialize call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_INITIALIZE);
    call.iface = (ULONG_PTR)wic_encoder;
    call.pIStream = (ULONG_PTR)pIStream;
    call.cacheOption = cacheOption;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_Initialize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_Initialize *c = (struct qemu_WICBitmapEncoder_Initialize *)call;
    struct qemu_wic_encoder *wic_encoder;
    struct istream_wrapper *stream;

    WINE_TRACE("\n");
    wic_encoder = QEMU_G2H(c->iface);
    stream = istream_wrapper_create(c->pIStream);

    c->super.iret = IWICBitmapEncoder_Initialize(wic_encoder->host, istream_wrapper_host_iface(stream),
            c->cacheOption);
    if (stream)
        IStream_Release(istream_wrapper_host_iface(stream));
}

#endif

struct qemu_WICBitmapEncoder_GetContainerFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidContainerFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_GetContainerFormat(IWICBitmapEncoder *iface, GUID *pguidContainerFormat)
{
    struct qemu_WICBitmapEncoder_GetContainerFormat call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)wic_encoder;
    call.pguidContainerFormat = (ULONG_PTR)pguidContainerFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_GetContainerFormat *c = (struct qemu_WICBitmapEncoder_GetContainerFormat *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_GetContainerFormat(wic_encoder->host, QEMU_G2H(c->pguidContainerFormat));
}

#endif

struct qemu_WICBitmapEncoder_GetEncoderInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIEncoderInfo;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_GetEncoderInfo(IWICBitmapEncoder *iface, IWICBitmapEncoderInfo **ppIEncoderInfo)
{
    struct qemu_WICBitmapEncoder_GetEncoderInfo call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_GETENCODERINFO);
    call.iface = (ULONG_PTR)wic_encoder;
    call.ppIEncoderInfo = (ULONG_PTR)ppIEncoderInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_GetEncoderInfo(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_GetEncoderInfo *c = (struct qemu_WICBitmapEncoder_GetEncoderInfo *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_GetEncoderInfo(wic_encoder->host, QEMU_G2H(c->ppIEncoderInfo));
}

#endif

struct qemu_WICBitmapEncoder_SetColorContexts
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cCount;
    uint64_t ppIColorContext;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_SetColorContexts(IWICBitmapEncoder *iface, UINT cCount, IWICColorContext **ppIColorContext)
{
    struct qemu_WICBitmapEncoder_SetColorContexts call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_SETCOLORCONTEXTS);
    call.iface = (ULONG_PTR)wic_encoder;
    call.cCount = cCount;
    call.ppIColorContext = (ULONG_PTR)ppIColorContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_SetColorContexts(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_SetColorContexts *c = (struct qemu_WICBitmapEncoder_SetColorContexts *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_SetColorContexts(wic_encoder->host, c->cCount, QEMU_G2H(c->ppIColorContext));
}

#endif

struct qemu_WICBitmapEncoder_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_SetPalette(IWICBitmapEncoder *iface, IWICPalette *palette)
{
    struct qemu_WICBitmapEncoder_SetPalette call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);
    struct qemu_wic_palette *pal_impl = unsafe_impl_from_IWICPalette(palette);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_SETPALETTE);
    call.iface = (ULONG_PTR)wic_encoder;
    call.palette = (ULONG_PTR)pal_impl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_SetPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_SetPalette *c = (struct qemu_WICBitmapEncoder_SetPalette *)call;
    struct qemu_wic_encoder *wic_encoder;
    struct qemu_wic_palette *palette;

    WINE_TRACE("\n");
    wic_encoder = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->palette);

    c->super.iret = IWICBitmapEncoder_SetPalette(wic_encoder->host, palette ? palette->host : NULL);
}

#endif

struct qemu_WICBitmapEncoder_SetThumbnail
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIThumbnail;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_SetThumbnail(IWICBitmapEncoder *iface, IWICBitmapSource *pIThumbnail)
{
    struct qemu_WICBitmapEncoder_SetThumbnail call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_SETTHUMBNAIL);
    call.iface = (ULONG_PTR)wic_encoder;
    call.pIThumbnail = (ULONG_PTR)pIThumbnail;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_SetThumbnail(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_SetThumbnail *c = (struct qemu_WICBitmapEncoder_SetThumbnail *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_SetThumbnail(wic_encoder->host, QEMU_G2H(c->pIThumbnail));
}

#endif

struct qemu_WICBitmapEncoder_SetPreview
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIPreview;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_SetPreview(IWICBitmapEncoder *iface, IWICBitmapSource *pIPreview)
{
    struct qemu_WICBitmapEncoder_SetPreview call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_SETPREVIEW);
    call.iface = (ULONG_PTR)wic_encoder;
    call.pIPreview = (ULONG_PTR)pIPreview;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_SetPreview(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_SetPreview *c = (struct qemu_WICBitmapEncoder_SetPreview *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_SetPreview(wic_encoder->host, QEMU_G2H(c->pIPreview));
}

#endif

struct qemu_WICBitmapEncoder_CreateNewFrame
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIFrameEncode;
    uint64_t ppIEncoderOptions;
};

#ifdef QEMU_DLL_GUEST

static const IWICBitmapFrameEncodeVtbl WICBitmapFrameEncode_Vtbl =
{
    WICBitmapFrameEncode_QueryInterface,
    WICBitmapFrameEncode_AddRef,
    WICBitmapFrameEncode_Release,
    WICBitmapFrameEncode_Initialize,
    WICBitmapFrameEncode_SetSize,
    WICBitmapFrameEncode_SetResolution,
    WICBitmapFrameEncode_SetPixelFormat,
    WICBitmapFrameEncode_SetColorContexts,
    WICBitmapFrameEncode_SetPalette,
    WICBitmapFrameEncode_SetThumbnail,
    WICBitmapFrameEncode_WritePixels,
    WICBitmapFrameEncode_WriteSource,
    WICBitmapFrameEncode_Commit,
    WICBitmapFrameEncode_GetMetadataQueryWriter
};


static HRESULT WINAPI WICBitmapEncoder_CreateNewFrame(IWICBitmapEncoder *iface, IWICBitmapFrameEncode **ppIFrameEncode,
        IPropertyBag2 **ppIEncoderOptions)
{
    struct qemu_WICBitmapEncoder_CreateNewFrame call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);
    struct qemu_wic_frame_encode *frame_encode;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_CREATENEWFRAME);
    call.iface = (ULONG_PTR)wic_encoder;
    call.ppIFrameEncode = (ULONG_PTR)ppIFrameEncode;
    call.ppIEncoderOptions = (ULONG_PTR)ppIEncoderOptions;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    frame_encode = (struct qemu_wic_frame_encode *)(ULONG_PTR)call.ppIFrameEncode;
    frame_encode->IWICBitmapFrameEncode_iface.lpVtbl = &WICBitmapFrameEncode_Vtbl;
    *ppIFrameEncode = &frame_encode->IWICBitmapFrameEncode_iface;

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_CreateNewFrame(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_CreateNewFrame *c = (struct qemu_WICBitmapEncoder_CreateNewFrame *)call;
    struct qemu_wic_encoder *wic_encoder;
    struct qemu_wic_frame_encode *frame_encode;
    IWICBitmapFrameEncode *host;

    WINE_TRACE("\n");
    wic_encoder = QEMU_G2H(c->iface);
    if (c->ppIEncoderOptions)
        WINE_FIXME("Encoder options not supported yet.\n");

    c->super.iret = IWICBitmapEncoder_CreateNewFrame(wic_encoder->host, c->ppIFrameEncode ? &host : NULL, NULL);
    if (FAILED(c->super.iret))
        return;

    frame_encode = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*frame_encode));
    if (!frame_encode)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = E_OUTOFMEMORY;
        IWICBitmapFrameEncode_Release(host);
        return;
    }

    frame_encode->host = host;
    frame_encode->encoder = wic_encoder;
    c->ppIFrameEncode = QEMU_H2G(frame_encode);
}

#endif

struct qemu_WICBitmapEncoder_Commit
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_Commit(IWICBitmapEncoder *iface)
{
    struct qemu_WICBitmapEncoder_Commit call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_COMMIT);
    call.iface = (ULONG_PTR)wic_encoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_Commit(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_Commit *c = (struct qemu_WICBitmapEncoder_Commit *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_Commit(wic_encoder->host);
}

#endif

struct qemu_WICBitmapEncoder_GetMetadataQueryWriter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIMetadataQueryWriter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoder_GetMetadataQueryWriter(IWICBitmapEncoder *iface, IWICMetadataQueryWriter **ppIMetadataQueryWriter)
{
    struct qemu_WICBitmapEncoder_GetMetadataQueryWriter call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_GETMETADATAQUERYWRITER);
    call.iface = (ULONG_PTR)wic_encoder;
    call.ppIMetadataQueryWriter = (ULONG_PTR)ppIMetadataQueryWriter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_GetMetadataQueryWriter(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_GetMetadataQueryWriter *c = (struct qemu_WICBitmapEncoder_GetMetadataQueryWriter *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_GetMetadataQueryWriter(wic_encoder->host, QEMU_G2H(c->ppIMetadataQueryWriter));
}

#endif

struct qemu_WICBitmapEncoder_create_host
{
    struct qemu_syscall super;
    uint64_t clsid;
    uint64_t encoder;
};

#ifdef QEMU_DLL_GUEST

static const IWICBitmapEncoderVtbl WICBitmapEncoder_Vtbl =
{
    WICBitmapEncoder_QueryInterface,
    WICBitmapEncoder_AddRef,
    WICBitmapEncoder_Release,
    WICBitmapEncoder_Initialize,
    WICBitmapEncoder_GetContainerFormat,
    WICBitmapEncoder_GetEncoderInfo,
    WICBitmapEncoder_SetColorContexts,
    WICBitmapEncoder_SetPalette,
    WICBitmapEncoder_SetThumbnail,
    WICBitmapEncoder_SetPreview,
    WICBitmapEncoder_CreateNewFrame,
    WICBitmapEncoder_Commit,
    WICBitmapEncoder_GetMetadataQueryWriter
};

void WICBitmapEncoder_init_guest(struct qemu_wic_encoder *encoder)
{
    encoder->IWICBitmapEncoder_iface.lpVtbl = &WICBitmapEncoder_Vtbl;
}

HRESULT Encoder_CreateInstance(const CLSID *clsid, const IID *iid, void **obj)
{
    struct qemu_WICBitmapEncoder_create_host call;
    struct qemu_wic_encoder *encoder;
    HRESULT hr;

    WINE_TRACE("(%s,%p)\n", wine_dbgstr_guid(iid), obj);

    *obj = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_CREATE_HOST);
    call.clsid = (ULONG_PTR)clsid;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    encoder = (struct qemu_wic_encoder *)(ULONG_PTR)call.encoder;
    WICBitmapEncoder_init_guest(encoder);

    hr = IWICBitmapEncoder_QueryInterface(&encoder->IWICBitmapEncoder_iface, iid, obj);
    IWICBitmapEncoder_Release(&encoder->IWICBitmapEncoder_iface);

    return hr;
}

#else

struct qemu_wic_encoder *WICBitmapEncoder_create_host(IWICBitmapEncoder *host)
{
    struct qemu_wic_encoder *ret;
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

void qemu_WICBitmapEncoder_create_host(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_create_host *c = (struct qemu_WICBitmapEncoder_create_host *)call;
    struct qemu_wic_encoder *encoder;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *host_factory;
    HRESULT hr;
    IWICBitmapEncoder *host;

    lib = GetModuleHandleA("windowscodecs");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(QEMU_G2H(c->clsid), &IID_IClassFactory, (void *)&host_factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(host_factory, NULL, &IID_IWICBitmapEncoder, (void **)&host);
    IClassFactory_Release(host_factory);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IID_IWICBitmapEncoder object.\n");
        c->super.iret = hr;
        return;
    }

    encoder = WICBitmapEncoder_create_host(host);
    if (!encoder)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->encoder = QEMU_H2G(encoder);
    c->super.iret = hr;
}

#endif
