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

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICBitmapFrameDecode_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_decode *impl_from_IWICBitmapDecoder(IWICBitmapDecoder *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_decode, IWICBitmapDecoder_iface);
}

static inline struct qemu_wic_decode *impl_from_IWICBitmapFrameDecode(IWICBitmapFrameDecode *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_decode, IWICBitmapFrameDecode_iface);
}

static HRESULT WINAPI WICBitmapFrameDecode_QueryInterface(IWICBitmapFrameDecode *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapFrameDecode_QueryInterface call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)decode;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_QueryInterface *c = (struct qemu_WICBitmapFrameDecode_QueryInterface *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_QueryInterface(decode->host_frame, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICBitmapFrameDecode_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapFrameDecode_AddRef(IWICBitmapFrameDecode *iface)
{
    struct qemu_WICBitmapFrameDecode_AddRef call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_ADDREF);
    call.iface = (ULONG_PTR)decode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_AddRef *c = (struct qemu_WICBitmapFrameDecode_AddRef *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_AddRef(decode->host_frame);
}

#endif

struct qemu_WICBitmapFrameDecode_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapFrameDecode_Release(IWICBitmapFrameDecode *iface)
{
    struct qemu_WICBitmapFrameDecode_Release call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_RELEASE);
    call.iface = (ULONG_PTR)decode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_Release *c = (struct qemu_WICBitmapFrameDecode_Release *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_Release(decode->host_frame);
}

#endif

struct qemu_WICBitmapFrameDecode_GetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t puiWidth;
    uint64_t puiHeight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetSize(IWICBitmapFrameDecode *iface, UINT *puiWidth, UINT *puiHeight)
{
    struct qemu_WICBitmapFrameDecode_GetSize call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETSIZE);
    call.iface = (ULONG_PTR)decode;
    call.puiWidth = (ULONG_PTR)puiWidth;
    call.puiHeight = (ULONG_PTR)puiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetSize *c = (struct qemu_WICBitmapFrameDecode_GetSize *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetSize(decode->host_frame, QEMU_G2H(c->puiWidth), QEMU_G2H(c->puiHeight));
}

#endif

struct qemu_WICBitmapFrameDecode_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetPixelFormat(IWICBitmapFrameDecode *iface, WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICBitmapFrameDecode_GetPixelFormat call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)decode;
    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetPixelFormat *c = (struct qemu_WICBitmapFrameDecode_GetPixelFormat *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetPixelFormat(decode->host_frame, QEMU_G2H(c->pPixelFormat));
}

#endif

struct qemu_WICBitmapFrameDecode_GetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pDpiX;
    uint64_t pDpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetResolution(IWICBitmapFrameDecode *iface, double *pDpiX, double *pDpiY)
{
    struct qemu_WICBitmapFrameDecode_GetResolution call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETRESOLUTION);
    call.iface = (ULONG_PTR)decode;
    call.pDpiX = (ULONG_PTR)pDpiX;
    call.pDpiY = (ULONG_PTR)pDpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetResolution(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetResolution *c = (struct qemu_WICBitmapFrameDecode_GetResolution *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetResolution(decode->host_frame, QEMU_G2H(c->pDpiX), QEMU_G2H(c->pDpiY));
}

#endif

struct qemu_WICBitmapFrameDecode_CopyPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIPalette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_CopyPalette(IWICBitmapFrameDecode *iface, IWICPalette *pIPalette)
{
    struct qemu_WICBitmapFrameDecode_CopyPalette call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_COPYPALETTE);
    call.iface = (ULONG_PTR)decode;
    call.pIPalette = (ULONG_PTR)pIPalette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_CopyPalette *c = (struct qemu_WICBitmapFrameDecode_CopyPalette *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_CopyPalette(decode->host_frame, QEMU_G2H(c->pIPalette));
}

#endif

struct qemu_WICBitmapFrameDecode_CopyPixels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prc;
    uint64_t cbStride;
    uint64_t cbBufferSize;
    uint64_t pbBuffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_CopyPixels(IWICBitmapFrameDecode *iface, const WICRect *prc, UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer)
{
    struct qemu_WICBitmapFrameDecode_CopyPixels call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_COPYPIXELS);
    call.iface = (ULONG_PTR)decode;
    call.prc = (ULONG_PTR)prc;
    call.cbStride = cbStride;
    call.cbBufferSize = cbBufferSize;
    call.pbBuffer = (ULONG_PTR)pbBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_CopyPixels(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_CopyPixels *c = (struct qemu_WICBitmapFrameDecode_CopyPixels *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_CopyPixels(decode->host_frame, QEMU_G2H(c->prc), c->cbStride, c->cbBufferSize, QEMU_G2H(c->pbBuffer));
}

#endif

struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIMetadataQueryReader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetMetadataQueryReader(IWICBitmapFrameDecode *iface, IWICMetadataQueryReader **ppIMetadataQueryReader)
{
    struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETMETADATAQUERYREADER);
    call.iface = (ULONG_PTR)decode;
    call.ppIMetadataQueryReader = (ULONG_PTR)ppIMetadataQueryReader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetMetadataQueryReader(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader *c = (struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetMetadataQueryReader(decode->host_frame, QEMU_G2H(c->ppIMetadataQueryReader));
}

#endif

struct qemu_WICBitmapFrameDecode_GetColorContexts
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cCount;
    uint64_t ppIColorContexts;
    uint64_t pcActualCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetColorContexts(IWICBitmapFrameDecode *iface, UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount)
{
    struct qemu_WICBitmapFrameDecode_GetColorContexts call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETCOLORCONTEXTS);
    call.iface = (ULONG_PTR)decode;
    call.cCount = cCount;
    call.ppIColorContexts = (ULONG_PTR)ppIColorContexts;
    call.pcActualCount = (ULONG_PTR)pcActualCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetColorContexts(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetColorContexts *c = (struct qemu_WICBitmapFrameDecode_GetColorContexts *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetColorContexts(decode->host_frame, c->cCount, QEMU_G2H(c->ppIColorContexts), QEMU_G2H(c->pcActualCount));
}

#endif

struct qemu_WICBitmapFrameDecode_GetThumbnail
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIThumbnail;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetThumbnail(IWICBitmapFrameDecode *iface, IWICBitmapSource **ppIThumbnail)
{
    struct qemu_WICBitmapFrameDecode_GetThumbnail call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETTHUMBNAIL);
    call.iface = (ULONG_PTR)decode;
    call.ppIThumbnail = (ULONG_PTR)ppIThumbnail;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetThumbnail(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetThumbnail *c = (struct qemu_WICBitmapFrameDecode_GetThumbnail *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetThumbnail(decode->host_frame, QEMU_G2H(c->ppIThumbnail));
}

#endif

struct qemu_WICBitmapDecoder_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_QueryInterface(IWICBitmapDecoder *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapDecoder_QueryInterface call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)decode;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_QueryInterface *c = (struct qemu_WICBitmapDecoder_QueryInterface *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_QueryInterface(decode->host_bitmap, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICBitmapDecoder_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapDecoder_AddRef(IWICBitmapDecoder *iface)
{
    struct qemu_WICBitmapDecoder_AddRef call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_ADDREF);
    call.iface = (ULONG_PTR)decode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_AddRef *c = (struct qemu_WICBitmapDecoder_AddRef *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_AddRef(decode->host_bitmap);
}

#endif

struct qemu_WICBitmapDecoder_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapDecoder_Release(IWICBitmapDecoder *iface)
{
    struct qemu_WICBitmapDecoder_Release call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_RELEASE);
    call.iface = (ULONG_PTR)decode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_Release *c = (struct qemu_WICBitmapDecoder_Release *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_Release(decode->host_bitmap);
}

#endif

struct qemu_WICBitmapDecoder_QueryCapability
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t stream;
    uint64_t capability;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_QueryCapability(IWICBitmapDecoder *iface, IStream *stream, DWORD *capability)
{
    struct qemu_WICBitmapDecoder_QueryCapability call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_QUERYCAPABILITY);
    call.iface = (ULONG_PTR)decode;
    call.stream = (ULONG_PTR)stream;
    call.capability = (ULONG_PTR)capability;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_QueryCapability(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_QueryCapability *c = (struct qemu_WICBitmapDecoder_QueryCapability *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_QueryCapability(decode->host_bitmap, QEMU_G2H(c->stream), QEMU_G2H(c->capability));
}

#endif

struct qemu_WICBitmapDecoder_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t cacheOptions;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_Initialize(IWICBitmapDecoder *iface, IStream *pIStream, WICDecodeOptions cacheOptions)
{
    struct qemu_WICBitmapDecoder_Initialize call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_INITIALIZE);
    call.iface = (ULONG_PTR)decode;
    call.pIStream = (ULONG_PTR)pIStream;
    call.cacheOptions = cacheOptions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_Initialize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_Initialize *c = (struct qemu_WICBitmapDecoder_Initialize *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_Initialize(decode->host_bitmap, QEMU_G2H(c->pIStream), c->cacheOptions);
}

#endif

struct qemu_WICBitmapDecoder_GetContainerFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidContainerFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetContainerFormat(IWICBitmapDecoder *iface, GUID *pguidContainerFormat)
{
    struct qemu_WICBitmapDecoder_GetContainerFormat call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)decode;
    call.pguidContainerFormat = (ULONG_PTR)pguidContainerFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetContainerFormat *c = (struct qemu_WICBitmapDecoder_GetContainerFormat *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetContainerFormat(decode->host_bitmap, QEMU_G2H(c->pguidContainerFormat));
}

#endif

struct qemu_WICBitmapDecoder_GetDecoderInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIDecoderInfo;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetDecoderInfo(IWICBitmapDecoder *iface, IWICBitmapDecoderInfo **ppIDecoderInfo)
{
    struct qemu_WICBitmapDecoder_GetDecoderInfo call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETDECODERINFO);
    call.iface = (ULONG_PTR)decode;
    call.ppIDecoderInfo = (ULONG_PTR)ppIDecoderInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetDecoderInfo(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetDecoderInfo *c = (struct qemu_WICBitmapDecoder_GetDecoderInfo *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetDecoderInfo(decode->host_bitmap, QEMU_G2H(c->ppIDecoderInfo));
}

#endif

struct qemu_WICBitmapDecoder_CopyPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIPalette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_CopyPalette(IWICBitmapDecoder *iface, IWICPalette *pIPalette)
{
    struct qemu_WICBitmapDecoder_CopyPalette call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_COPYPALETTE);
    call.iface = (ULONG_PTR)decode;
    call.pIPalette = (ULONG_PTR)pIPalette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_CopyPalette *c = (struct qemu_WICBitmapDecoder_CopyPalette *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_CopyPalette(decode->host_bitmap, QEMU_G2H(c->pIPalette));
}

#endif

struct qemu_WICBitmapDecoder_GetMetadataQueryReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIMetadataQueryReader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetMetadataQueryReader(IWICBitmapDecoder *iface, IWICMetadataQueryReader **ppIMetadataQueryReader)
{
    struct qemu_WICBitmapDecoder_GetMetadataQueryReader call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETMETADATAQUERYREADER);
    call.iface = (ULONG_PTR)decode;
    call.ppIMetadataQueryReader = (ULONG_PTR)ppIMetadataQueryReader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetMetadataQueryReader(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetMetadataQueryReader *c = (struct qemu_WICBitmapDecoder_GetMetadataQueryReader *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetMetadataQueryReader(decode->host_bitmap, QEMU_G2H(c->ppIMetadataQueryReader));
}

#endif

struct qemu_WICBitmapDecoder_GetPreview
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIBitmapSource;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetPreview(IWICBitmapDecoder *iface, IWICBitmapSource **ppIBitmapSource)
{
    struct qemu_WICBitmapDecoder_GetPreview call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETPREVIEW);
    call.iface = (ULONG_PTR)decode;
    call.ppIBitmapSource = (ULONG_PTR)ppIBitmapSource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetPreview(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetPreview *c = (struct qemu_WICBitmapDecoder_GetPreview *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetPreview(decode->host_bitmap, QEMU_G2H(c->ppIBitmapSource));
}

#endif

struct qemu_WICBitmapDecoder_GetColorContexts
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cCount;
    uint64_t ppIColorContexts;
    uint64_t pcActualCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetColorContexts(IWICBitmapDecoder *iface, UINT cCount, IWICColorContext **ppIColorContexts, UINT *pcActualCount)
{
    struct qemu_WICBitmapDecoder_GetColorContexts call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETCOLORCONTEXTS);
    call.iface = (ULONG_PTR)decode;
    call.cCount = cCount;
    call.ppIColorContexts = (ULONG_PTR)ppIColorContexts;
    call.pcActualCount = (ULONG_PTR)pcActualCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetColorContexts(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetColorContexts *c = (struct qemu_WICBitmapDecoder_GetColorContexts *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetColorContexts(decode->host_bitmap, c->cCount, QEMU_G2H(c->ppIColorContexts), QEMU_G2H(c->pcActualCount));
}

#endif

struct qemu_WICBitmapDecoder_GetThumbnail
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIThumbnail;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetThumbnail(IWICBitmapDecoder *iface, IWICBitmapSource **ppIThumbnail)
{
    struct qemu_WICBitmapDecoder_GetThumbnail call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETTHUMBNAIL);
    call.iface = (ULONG_PTR)decode;
    call.ppIThumbnail = (ULONG_PTR)ppIThumbnail;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetThumbnail(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetThumbnail *c = (struct qemu_WICBitmapDecoder_GetThumbnail *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetThumbnail(decode->host_bitmap, QEMU_G2H(c->ppIThumbnail));
}

#endif

struct qemu_WICBitmapDecoder_GetFrameCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetFrameCount(IWICBitmapDecoder *iface, UINT *pCount)
{
    struct qemu_WICBitmapDecoder_GetFrameCount call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETFRAMECOUNT);
    call.iface = (ULONG_PTR)decode;
    call.pCount = (ULONG_PTR)pCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetFrameCount(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetFrameCount *c = (struct qemu_WICBitmapDecoder_GetFrameCount *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetFrameCount(decode->host_bitmap, QEMU_G2H(c->pCount));
}

#endif

struct qemu_WICBitmapDecoder_GetFrame
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t ppIBitmapFrame;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetFrame(IWICBitmapDecoder *iface, UINT index, IWICBitmapFrameDecode **ppIBitmapFrame)
{
    struct qemu_WICBitmapDecoder_GetFrame call;
    struct qemu_wic_decode *decode = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETFRAME);
    call.iface = (ULONG_PTR)decode;
    call.index = index;
    call.ppIBitmapFrame = (ULONG_PTR)ppIBitmapFrame;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetFrame(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetFrame *c = (struct qemu_WICBitmapDecoder_GetFrame *)call;
    struct qemu_wic_decode *decode;

    WINE_FIXME("Unverified!\n");
    decode = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetFrame(decode->host_bitmap, c->index, QEMU_G2H(c->ppIBitmapFrame));
}

#endif

struct qemu_WICBitmapDecoder_create_host
{
    struct qemu_syscall super;
    uint64_t decoder;
};

#ifdef QEMU_DLL_GUEST

static const IWICBitmapDecoderVtbl WICBitmapDecoder_Vtbl =
{
    WICBitmapDecoder_QueryInterface,
    WICBitmapDecoder_AddRef,
    WICBitmapDecoder_Release,
    WICBitmapDecoder_QueryCapability,
    WICBitmapDecoder_Initialize,
    WICBitmapDecoder_GetContainerFormat,
    WICBitmapDecoder_GetDecoderInfo,
    WICBitmapDecoder_CopyPalette,
    WICBitmapDecoder_GetMetadataQueryReader,
    WICBitmapDecoder_GetPreview,
    WICBitmapDecoder_GetColorContexts,
    WICBitmapDecoder_GetThumbnail,
    WICBitmapDecoder_GetFrameCount,
    WICBitmapDecoder_GetFrame
};

HRESULT Decoder_CreateInstance(const IID *iid, void **obj)
{
    struct qemu_WICBitmapDecoder_create_host call;
    struct qemu_wic_decode *decoder;
    HRESULT hr;

    WINE_TRACE("(%s,%p)\n", wine_dbgstr_guid(iid), obj);

    *obj = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_CREATE_HOST);
    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    decoder = (struct qemu_wic_decode *)(ULONG_PTR)call.decoder;
    decoder->IWICBitmapDecoder_iface.lpVtbl = &WICBitmapDecoder_Vtbl;

    hr = IWICBitmapDecoder_QueryInterface(&decoder->IWICBitmapDecoder_iface, iid, obj);
    IWICBitmapDecoder_Release(&decoder->IWICBitmapDecoder_iface);

    return hr;
}

#else

void qemu_WICBitmapDecoder_create_host(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_create_host *c = (struct qemu_WICBitmapDecoder_create_host *)call;
    struct qemu_wic_decode *decoder;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *host_factory;
    HRESULT hr;

    decoder = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*decoder));
    if (!decoder)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    lib = GetModuleHandleA("windowscodecs");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(&CLSID_WICImagingFactory, &IID_IClassFactory, (void *)&host_factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(host_factory, NULL, &IID_IWICBitmapDecoder, (void **)&decoder->host_bitmap);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IID_IWICBitmapDecoder object.\n");
        HeapFree(GetProcessHeap(), 0, decoder);
        decoder = NULL;
    }
    IClassFactory_Release(host_factory);

    c->decoder = QEMU_H2G(decoder);
    c->super.iret = hr;
}

#endif

