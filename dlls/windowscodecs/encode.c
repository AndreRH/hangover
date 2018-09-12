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

void qemu_WICBitmapFrameEncode_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_Release *c = (struct qemu_WICBitmapFrameEncode_Release *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_Release(frame_encode->host);
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
    call.iface = (ULONG_PTR)frame_encode;    call.pIEncoderOptions = (ULONG_PTR)pIEncoderOptions;

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
    call.iface = (ULONG_PTR)frame_encode;    call.uiWidth = uiWidth;
    call.uiHeight = uiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetSize *c = (struct qemu_WICBitmapFrameEncode_SetSize *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetSize(frame_encode->host, c->uiWidth, c->uiHeight);
}

#endif

struct qemu_WICBitmapFrameEncode_SetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dpiX;
    uint64_t dpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_SetResolution(IWICBitmapFrameEncode *iface, double dpiX, double dpiY)
{
    struct qemu_WICBitmapFrameEncode_SetResolution call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETRESOLUTION);
    call.iface = (ULONG_PTR)frame_encode;    call.dpiX = dpiX;
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

static HRESULT WINAPI WICBitmapFrameEncode_SetPixelFormat(IWICBitmapFrameEncode *iface, WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICBitmapFrameEncode_SetPixelFormat call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETPIXELFORMAT);
    call.iface = (ULONG_PTR)frame_encode;    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetPixelFormat *c = (struct qemu_WICBitmapFrameEncode_SetPixelFormat *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
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
    call.iface = (ULONG_PTR)frame_encode;    call.cCount = cCount;
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

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_SETPALETTE);
    call.iface = (ULONG_PTR)frame_encode;    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_SetPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_SetPalette *c = (struct qemu_WICBitmapFrameEncode_SetPalette *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_SetPalette(frame_encode->host, QEMU_G2H(c->palette));
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
    call.iface = (ULONG_PTR)frame_encode;    call.pIThumbnail = (ULONG_PTR)pIThumbnail;

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
    call.iface = (ULONG_PTR)frame_encode;    call.lineCount = lineCount;
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
    uint64_t pIBitmapSource;
    uint64_t prc;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameEncode_WriteSource(IWICBitmapFrameEncode *iface, IWICBitmapSource *pIBitmapSource, WICRect *prc)
{
    struct qemu_WICBitmapFrameEncode_WriteSource call;
    struct qemu_wic_frame_encode *frame_encode = impl_from_IWICBitmapFrameEncode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEENCODE_WRITESOURCE);
    call.iface = (ULONG_PTR)frame_encode;    call.pIBitmapSource = (ULONG_PTR)pIBitmapSource;
    call.prc = (ULONG_PTR)prc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameEncode_WriteSource(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameEncode_WriteSource *c = (struct qemu_WICBitmapFrameEncode_WriteSource *)call;
    struct qemu_wic_frame_encode *frame_encode;

    WINE_FIXME("Unverified!\n");
    frame_encode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameEncode_WriteSource(frame_encode->host, QEMU_G2H(c->pIBitmapSource), QEMU_G2H(c->prc));
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
    call.iface = (ULONG_PTR)frame_encode;    call.ppIMetadataQueryWriter = (ULONG_PTR)ppIMetadataQueryWriter;

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
    uint64_t ppv;
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

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)wic_encoder;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_QueryInterface *c = (struct qemu_WICBitmapEncoder_QueryInterface *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_QueryInterface(wic_encoder->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
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

    WINE_FIXME("Unverified!\n");
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

void qemu_WICBitmapEncoder_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_Release *c = (struct qemu_WICBitmapEncoder_Release *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_Release(wic_encoder->host);
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

static HRESULT WINAPI WICBitmapEncoder_Initialize(IWICBitmapEncoder *iface, IStream *pIStream, WICBitmapEncoderCacheOption cacheOption)
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

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_Initialize(wic_encoder->host, QEMU_G2H(c->pIStream), c->cacheOption);
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

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_SETPALETTE);
    call.iface = (ULONG_PTR)wic_encoder;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_SetPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_SetPalette *c = (struct qemu_WICBitmapEncoder_SetPalette *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_SetPalette(wic_encoder->host, QEMU_G2H(c->palette));
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

static HRESULT WINAPI WICBitmapEncoder_CreateNewFrame(IWICBitmapEncoder *iface, IWICBitmapFrameEncode **ppIFrameEncode, IPropertyBag2 **ppIEncoderOptions)
{
    struct qemu_WICBitmapEncoder_CreateNewFrame call;
    struct qemu_wic_encoder *wic_encoder = impl_from_IWICBitmapEncoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODER_CREATENEWFRAME);
    call.iface = (ULONG_PTR)wic_encoder;
    call.ppIFrameEncode = (ULONG_PTR)ppIFrameEncode;
    call.ppIEncoderOptions = (ULONG_PTR)ppIEncoderOptions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoder_CreateNewFrame(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoder_CreateNewFrame *c = (struct qemu_WICBitmapEncoder_CreateNewFrame *)call;
    struct qemu_wic_encoder *wic_encoder;

    WINE_FIXME("Unverified!\n");
    wic_encoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoder_CreateNewFrame(wic_encoder->host, QEMU_G2H(c->ppIFrameEncode), QEMU_G2H(c->ppIEncoderOptions));
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

#ifdef QEMU_DLL_GUEST

HRESULT Encoder_CreateInstance(const CLSID *clsid, const IID *iid, void **obj)
{
#if 0
    BmpEncoder *This;
    HRESULT ret;

    TRACE("(%s,%p)\n", debugstr_guid(iid), ppv);

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(BmpEncoder));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapEncoder_iface.lpVtbl = &BmpEncoder_Vtbl;
    This->ref = 1;
    This->stream = NULL;
    This->frame = NULL;

    ret = IWICBitmapEncoder_QueryInterface(&This->IWICBitmapEncoder_iface, iid, ppv);
    IWICBitmapEncoder_Release(&This->IWICBitmapEncoder_iface);

    return ret;
#endif
    WINE_FIXME("Stub\n");
    return E_FAIL;
}

#endif
