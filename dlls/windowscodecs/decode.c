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

#define COBJMACROS

#include <windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>
#include <wine/rbtree.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICBitmapFrameDecode_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_decoder *impl_from_IWICBitmapDecoder(IWICBitmapDecoder *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_decoder, IWICBitmapDecoder_iface);
}

static inline struct qemu_wic_frame_decode *impl_from_IWICBitmapFrameDecode(IWICBitmapFrameDecode *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_frame_decode, IWICBitmapFrameDecode_iface);
}

static inline struct qemu_wic_frame_decode *frame_from_IWICMetadataBlockReader(IWICMetadataBlockReader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_frame_decode, IWICMetadataBlockReader_iface);
}

static HRESULT WINAPI WICBitmapFrameDecode_QueryInterface(IWICBitmapFrameDecode *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapFrameDecode_QueryInterface call;
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(iid), ppv);

    if (!ppv)
        return E_INVALIDARG;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)frame;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        *ppv = NULL;
        return call.super.iret;
    }

    if (IsEqualIID(&IID_IUnknown, iid)
            || IsEqualIID(&IID_IWICBitmapSource, iid)
            || IsEqualIID(&IID_IWICBitmapSource, iid)
            || IsEqualIID(&IID_IWICBitmapFrameDecode, iid))
    {
        *ppv = &frame->IWICBitmapFrameDecode_iface;
    }
    else if (IsEqualIID(&IID_IWICMetadataBlockReader, iid))
    {
        *ppv = &frame->IWICMetadataBlockReader_iface;
    }
    else
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(iid));
        *ppv = NULL;

        /* For the AddRef done on the host side. Luckily host and guest share a refcount, and there's
         * only one refcount for all interfaces. */
        IWICBitmapFrameDecode_Release(&frame->IWICBitmapFrameDecode_iface);
        return E_NOINTERFACE;
    }

    /* AddRef already taken care of on the host side. */
    return S_OK;

}

#else

void qemu_WICBitmapFrameDecode_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_QueryInterface *c = (struct qemu_WICBitmapFrameDecode_QueryInterface *)call;
    struct qemu_wic_frame_decode *frame;
    IUnknown *obj;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_QueryInterface(frame->host, QEMU_G2H(c->iid), (void **)&obj);
    /* Pass the reference to the guest. */
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
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_ADDREF);
    call.iface = (ULONG_PTR)frame;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_AddRef *c = (struct qemu_WICBitmapFrameDecode_AddRef *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_AddRef(frame->host);
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
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_RELEASE);
    call.iface = (ULONG_PTR)frame;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG qemu_WICBitmapDecoder_Release_internal(struct qemu_wic_decoder *decoder);
void qemu_WICBitmapFrameDecode_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_Release *c = (struct qemu_WICBitmapFrameDecode_Release *)call;
    struct qemu_wic_frame_decode *frame;
    ULONG i;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    if (frame->decoder)
    {
        /* GIF frames hold a reference to their parent decoders, ICO and TIFF frames do not. */
        IWICBitmapDecoder_AddRef(frame->decoder->host);
        c->super.iret = IWICBitmapFrameDecode_Release(frame->host);
        qemu_WICBitmapDecoder_Release_internal(frame->decoder);

        if (!c->super.iret)
        {
            /* Multi-frame decoder, destroy only the frame. */
            WINE_TRACE("Destroying frame wrapper %p for host frame %p.\n", frame, frame->host);

            for (i = 0; i < frame->reader_count; ++i)
                qemu_MetadataHandler_Release_internal(frame->readers[i]);
            HeapFree(GetProcessHeap(), 0, frame->readers);

            HeapFree(GetProcessHeap(), 0, frame);
        }
    }
    else
    {
        c->super.iret = IWICBitmapFrameDecode_Release(frame->host);
        if (!c->super.iret)
        {
            /* Single-frame decoder, destroy the entire decoder. */
            struct qemu_wic_decoder *decoder = CONTAINING_RECORD(frame, struct qemu_wic_decoder, static_frame);
            WINE_TRACE("Destroying decoder wrapper %p for host decoder %p via frame %p.\n", decoder, decoder->host, frame);

            for (i = 0; i < frame->reader_count; ++i)
                qemu_MetadataHandler_Release_internal(frame->readers[i]);
            HeapFree(GetProcessHeap(), 0, frame->readers);

            HeapFree(GetProcessHeap(), 0, decoder);
        }
    }
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
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETSIZE);
    call.iface = (ULONG_PTR)frame;
    call.puiWidth = (ULONG_PTR)puiWidth;
    call.puiHeight = (ULONG_PTR)puiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetSize *c = (struct qemu_WICBitmapFrameDecode_GetSize *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetSize(frame->host, QEMU_G2H(c->puiWidth), QEMU_G2H(c->puiHeight));
}

#endif

struct qemu_WICBitmapFrameDecode_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetPixelFormat(IWICBitmapFrameDecode *iface,
        WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICBitmapFrameDecode_GetPixelFormat call;
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)frame;
    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetPixelFormat *c = (struct qemu_WICBitmapFrameDecode_GetPixelFormat *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetPixelFormat(frame->host, QEMU_G2H(c->pPixelFormat));
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
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETRESOLUTION);
    call.iface = (ULONG_PTR)frame;
    call.pDpiX = (ULONG_PTR)pDpiX;
    call.pDpiY = (ULONG_PTR)pDpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetResolution(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetResolution *c = (struct qemu_WICBitmapFrameDecode_GetResolution *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetResolution(frame->host, QEMU_G2H(c->pDpiX), QEMU_G2H(c->pDpiY));
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
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);
    struct qemu_wic_palette *palette = unsafe_impl_from_IWICPalette(pIPalette);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_COPYPALETTE);
    call.iface = (ULONG_PTR)frame;
    call.pIPalette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_CopyPalette *c = (struct qemu_WICBitmapFrameDecode_CopyPalette *)call;
    struct qemu_wic_frame_decode *frame;
    struct qemu_wic_palette *palette;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->pIPalette);

    c->super.iret = IWICBitmapFrameDecode_CopyPalette(frame->host, palette ? palette->host : NULL);
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

static HRESULT WINAPI WICBitmapFrameDecode_CopyPixels(IWICBitmapFrameDecode *iface, const WICRect *prc, UINT cbStride,
        UINT cbBufferSize, BYTE *pbBuffer)
{
    struct qemu_WICBitmapFrameDecode_CopyPixels call;
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_COPYPIXELS);
    call.iface = (ULONG_PTR)frame;
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
    struct qemu_wic_frame_decode *frame;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_CopyPixels(frame->host, QEMU_G2H(c->prc), c->cbStride,
            c->cbBufferSize, QEMU_G2H(c->pbBuffer));
}

#endif

struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIMetadataQueryReader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapFrameDecode_GetMetadataQueryReader(IWICBitmapFrameDecode *iface,
        IWICMetadataQueryReader **ppIMetadataQueryReader)
{
    struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader call;
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETMETADATAQUERYREADER);
    call.iface = (ULONG_PTR)frame;
    call.ppIMetadataQueryReader = (ULONG_PTR)ppIMetadataQueryReader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetMetadataQueryReader(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader *c =
            (struct qemu_WICBitmapFrameDecode_GetMetadataQueryReader *)call;
    struct qemu_wic_frame_decode *frame;
    IWICMetadataQueryReader *host;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetMetadataQueryReader(frame->host,
            c->ppIMetadataQueryReader ? &host : NULL);

    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host GetMetadataQueryReader succeeded, write a wrapper.\n");
        IWICMetadataQueryReader_Release(host);
        c->super.iret = E_FAIL;
    }
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

static HRESULT WINAPI WICBitmapFrameDecode_GetColorContexts(IWICBitmapFrameDecode *iface, UINT cCount,
        IWICColorContext **ppIColorContexts, UINT *pcActualCount)
{
    struct qemu_WICBitmapFrameDecode_GetColorContexts call;
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETCOLORCONTEXTS);
    call.iface = (ULONG_PTR)frame;
    call.cCount = cCount;
    call.pcActualCount = (ULONG_PTR)pcActualCount;

    if (ppIColorContexts)
        call.ppIColorContexts = (ULONG_PTR)unsafe_impl_from_IWICColorContext(ppIColorContexts[0]);
    else
        call.ppIColorContexts = 0;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapFrameDecode_GetColorContexts(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetColorContexts *c = (struct qemu_WICBitmapFrameDecode_GetColorContexts *)call;
    struct qemu_wic_frame_decode *frame;
    IWICColorContext *host;
    DWORD count;
    struct qemu_wic_color_context *context;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);
    count = c->cCount;
    context = QEMU_G2H(c->ppIColorContexts);

    if (count > 1)
    {
        WINE_FIXME("Support more than one color context.\n");
        count = 1;
    }

    c->super.iret = IWICBitmapFrameDecode_GetColorContexts(frame->host, count,
            context ? &context->host : NULL, QEMU_G2H(c->pcActualCount));
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
    struct qemu_wic_frame_decode *frame = impl_from_IWICBitmapFrameDecode(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPFRAMEDECODE_GETTHUMBNAIL);
    call.iface = (ULONG_PTR)frame;
    call.ppIThumbnail = (ULONG_PTR)ppIThumbnail;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    return IWICBitmapFrameDecode_QueryInterface(iface, &IID_IWICBitmapSource, (void **)ppIThumbnail);
}

#else

void qemu_WICBitmapFrameDecode_GetThumbnail(struct qemu_syscall *call)
{
    struct qemu_WICBitmapFrameDecode_GetThumbnail *c = (struct qemu_WICBitmapFrameDecode_GetThumbnail *)call;
    struct qemu_wic_frame_decode *frame;
    IWICBitmapSource *host;

    WINE_TRACE("\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapFrameDecode_GetThumbnail(frame->host, c->ppIThumbnail ? &host : NULL);

    if (SUCCEEDED(c->super.iret))
    {
        if (host != (IWICBitmapSource *)frame->host)
            WINE_FIXME("Expected the thumbnail to be myself.\n");
        IWICBitmapSource_Release(host);
    }
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataBlockReader_QueryInterface(IWICMetadataBlockReader *iface, REFIID iid, void **ppv)
{
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);
    return IWICBitmapFrameDecode_QueryInterface(&frame->IWICBitmapFrameDecode_iface, iid, ppv);
}

static ULONG WINAPI WICMetadataBlockReader_AddRef(IWICMetadataBlockReader *iface)
{
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);
    return IWICBitmapFrameDecode_AddRef(&frame->IWICBitmapFrameDecode_iface);
}

static ULONG WINAPI WICMetadataBlockReader_Release(IWICMetadataBlockReader *iface)
{
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);
    return IWICBitmapFrameDecode_Release(&frame->IWICBitmapFrameDecode_iface);
}

#endif

struct qemu_WICMetadataBlockReader_GetContainerFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataBlockReader_GetContainerFormat(IWICMetadataBlockReader *iface, GUID *guid)
{
    struct qemu_WICMetadataBlockReader_GetContainerFormat call;
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATABLOCKREADER_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)frame;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataBlockReader_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICMetadataBlockReader_GetContainerFormat *c = (struct qemu_WICMetadataBlockReader_GetContainerFormat *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_FIXME("Unverified!\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataBlockReader_GetContainerFormat(frame->host_block_reader, QEMU_G2H(c->guid));
}

#endif

struct qemu_WICMetadataBlockReader_GetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataBlockReader_GetCount(IWICMetadataBlockReader *iface, UINT *count)
{
    struct qemu_WICMetadataBlockReader_GetCount call;
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATABLOCKREADER_GETCOUNT);
    call.iface = (ULONG_PTR)frame;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataBlockReader_GetCount(struct qemu_syscall *call)
{
    struct qemu_WICMetadataBlockReader_GetCount *c = (struct qemu_WICMetadataBlockReader_GetCount *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_FIXME("Unverified!\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataBlockReader_GetCount(frame->host_block_reader, QEMU_G2H(c->count));
}

#endif

struct qemu_WICMetadataBlockReader_GetReaderByIndex
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t reader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataBlockReader_GetReaderByIndex(IWICMetadataBlockReader *iface, UINT index,
        IWICMetadataReader **reader)
{
    struct qemu_WICMetadataBlockReader_GetReaderByIndex call;
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);
    struct qemu_wic_metadata_handler *handler;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATABLOCKREADER_GETREADERBYINDEX);
    call.iface = (ULONG_PTR)frame;
    call.index = index;
    call.reader = (ULONG_PTR)reader;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    handler = (struct qemu_wic_metadata_handler *)(ULONG_PTR)call.reader;
    MetadataHandler_init_guest(handler);
    *reader = (IWICMetadataReader *)&handler->IWICMetadataWriter_iface;

    return call.super.iret;
}

#else

void qemu_WICMetadataBlockReader_GetReaderByIndex(struct qemu_syscall *call)
{
    struct qemu_WICMetadataBlockReader_GetReaderByIndex *c =
            (struct qemu_WICMetadataBlockReader_GetReaderByIndex *)call;
    struct qemu_wic_frame_decode *frame;
    IWICMetadataReader *host;
    UINT idx;

    WINE_TRACE("");
    frame = QEMU_G2H(c->iface);
    idx = c->index;

    c->super.iret = IWICMetadataBlockReader_GetReaderByIndex(frame->host_block_reader, idx, c->reader ? &host : NULL);
    if (FAILED(c->super.iret))
        return;

    if (idx >= frame->reader_count)
        WINE_ERR("I have %u readers, but getting reader %u succeeded.\n", frame->reader_count, idx);

    c->reader = QEMU_H2G(frame->readers[idx]);
    IWICMetadataWriter_AddRef(frame->readers[idx]->host_writer);
    IWICMetadataReader_Release(host);
}

#endif

struct qemu_WICMetadataBlockReader_GetEnumerator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t enumerator;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataBlockReader_GetEnumerator(IWICMetadataBlockReader *iface, IEnumUnknown **enumerator)
{
    struct qemu_WICMetadataBlockReader_GetEnumerator call;
    struct qemu_wic_frame_decode *frame = frame_from_IWICMetadataBlockReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATABLOCKREADER_GETENUMERATOR);
    call.iface = (ULONG_PTR)frame;
    call.enumerator = (ULONG_PTR)enumerator;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataBlockReader_GetEnumerator(struct qemu_syscall *call)
{
    struct qemu_WICMetadataBlockReader_GetEnumerator *c = (struct qemu_WICMetadataBlockReader_GetEnumerator *)call;
    struct qemu_wic_frame_decode *frame;

    WINE_FIXME("Unverified!\n");
    frame = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataBlockReader_GetEnumerator(frame->host_block_reader, QEMU_G2H(c->enumerator));
}

#endif

struct qemu_WICBitmapDecoder_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_QueryInterface(IWICBitmapDecoder *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapDecoder_QueryInterface call;
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);
    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(iid), ppv);

    if (!ppv) return E_INVALIDARG;

    if (IsEqualIID(&IID_IUnknown, iid) ||
            IsEqualIID(&IID_IWICBitmapDecoder, iid))
    {
        *ppv = &decoder->IWICBitmapDecoder_iface;
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)decoder;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    *ppv = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_WICBitmapDecoder_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_QueryInterface *c = (struct qemu_WICBitmapDecoder_QueryInterface *)call;
    struct qemu_wic_decoder *decoder;
    IUnknown *obj;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_QueryInterface(decoder->host, QEMU_G2H(c->iid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->iid)));
        IUnknown_Release(obj);
    }
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_ADDREF);
    call.iface = (ULONG_PTR)decoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_AddRef *c = (struct qemu_WICBitmapDecoder_AddRef *)call;
    struct qemu_wic_decoder *decoder;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_AddRef(decoder->host);
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_RELEASE);
    call.iface = (ULONG_PTR)decoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG qemu_WICBitmapDecoder_Release_internal(struct qemu_wic_decoder *decoder)
{
    ULONG ref = IWICBitmapDecoder_Release(decoder->host), i;

    if (!ref)
    {
        WINE_TRACE("Destroying decoder wrapper %p for host decoder %p.\n", decoder, decoder->host);

        for (i = 0; i < decoder->static_frame.reader_count; ++i)
            qemu_MetadataHandler_Release_internal(decoder->static_frame.readers[i]);
        HeapFree(GetProcessHeap(), 0, decoder->static_frame.readers);

        HeapFree(GetProcessHeap(), 0, decoder);
    }

    return ref;
}

void qemu_WICBitmapDecoder_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_Release *c = (struct qemu_WICBitmapDecoder_Release *)call;
    struct qemu_wic_decoder *decoder;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = qemu_WICBitmapDecoder_Release_internal(decoder);
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_QUERYCAPABILITY);
    call.iface = (ULONG_PTR)decoder;
    call.stream = (ULONG_PTR)stream;
    call.capability = (ULONG_PTR)capability;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_QueryCapability(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_QueryCapability *c = (struct qemu_WICBitmapDecoder_QueryCapability *)call;
    struct qemu_wic_decoder *decoder;
    struct istream_wrapper *stream;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);
    stream = istream_wrapper_create(c->stream);

    c->super.iret = IWICBitmapDecoder_QueryCapability(decoder->host, istream_wrapper_host_iface(stream),
            QEMU_G2H(c->capability));

    if (stream)
        IStream_Release(istream_wrapper_host_iface(stream));
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

static HRESULT WINAPI WICBitmapDecoder_Initialize(IWICBitmapDecoder *iface, IStream *pIStream,
        WICDecodeOptions cacheOptions)
{
    struct qemu_WICBitmapDecoder_Initialize call;
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_INITIALIZE);
    call.iface = (ULONG_PTR)decoder;
    call.pIStream = (ULONG_PTR)pIStream;
    call.cacheOptions = cacheOptions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_Initialize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_Initialize *c = (struct qemu_WICBitmapDecoder_Initialize *)call;
    struct qemu_wic_decoder *decoder;
    struct istream_wrapper *stream;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);
    stream = istream_wrapper_create(c->pIStream);

    c->super.iret = IWICBitmapDecoder_Initialize(decoder->host, istream_wrapper_host_iface(stream),
            c->cacheOptions);

    if (stream)
        IStream_Release(istream_wrapper_host_iface(stream));
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)decoder;
    call.pguidContainerFormat = (ULONG_PTR)pguidContainerFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetContainerFormat *c = (struct qemu_WICBitmapDecoder_GetContainerFormat *)call;
    struct qemu_wic_decoder *decoder;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetContainerFormat(decoder->host, QEMU_G2H(c->pguidContainerFormat));
}

#endif

struct qemu_WICBitmapDecoder_GetDecoderInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIDecoderInfo;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetDecoderInfo(IWICBitmapDecoder *iface, IWICBitmapDecoderInfo **ppIDecoderInfo)
{
    struct qemu_WICBitmapDecoder_GetDecoderInfo call;
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);
    struct qemu_wic_info *info;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETDECODERINFO);
    call.iface = (ULONG_PTR)decoder;
    call.ppIDecoderInfo = (ULONG_PTR)ppIDecoderInfo;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    info = (struct qemu_wic_info *)(ULONG_PTR)call.ppIDecoderInfo;
    WICComponentInfo_init_guest(info, call.type);
    *ppIDecoderInfo = (IWICBitmapDecoderInfo *)&info->IWICComponentInfo_iface;

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetDecoderInfo(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetDecoderInfo *c = (struct qemu_WICBitmapDecoder_GetDecoderInfo *)call;
    struct qemu_wic_decoder *decoder;
    IWICBitmapDecoderInfo *host;
    struct qemu_wic_info *info;
    enum component_info_type type;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetDecoderInfo(decoder->host, c->ppIDecoderInfo ? &host : NULL);
    if (FAILED(c->super.iret))
        return;

    info = WICComponentInfo_create_host((IWICComponentInfo *)host, &type);
    if (!info)
    {
        c->super.iret = E_OUTOFMEMORY;
        IWICComponentInfo_Release(host);
        return;
    }

    c->type = type;
    c->ppIDecoderInfo = QEMU_H2G(info);
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);
    struct qemu_wic_palette *palette = unsafe_impl_from_IWICPalette(pIPalette);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_COPYPALETTE);
    call.iface = (ULONG_PTR)decoder;
    call.pIPalette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_CopyPalette *c = (struct qemu_WICBitmapDecoder_CopyPalette *)call;
    struct qemu_wic_decoder *decoder;
    struct qemu_wic_palette *palette;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);
    palette = QEMU_G2H(c->pIPalette);

    c->super.iret = IWICBitmapDecoder_CopyPalette(decoder->host, palette ? palette->host : NULL);
}

#endif

struct qemu_WICBitmapDecoder_GetMetadataQueryReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIMetadataQueryReader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoder_GetMetadataQueryReader(IWICBitmapDecoder *iface,
        IWICMetadataQueryReader **ppIMetadataQueryReader)
{
    struct qemu_WICBitmapDecoder_GetMetadataQueryReader call;
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETMETADATAQUERYREADER);
    call.iface = (ULONG_PTR)decoder;
    call.ppIMetadataQueryReader = (ULONG_PTR)ppIMetadataQueryReader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetMetadataQueryReader(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetMetadataQueryReader *c =
            (struct qemu_WICBitmapDecoder_GetMetadataQueryReader *)call;
    struct qemu_wic_decoder *decoder;
    IWICMetadataQueryReader *host;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetMetadataQueryReader(decoder->host,
            c->ppIMetadataQueryReader ? &host : NULL);

    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host GetMetadataQueryReader succeeded, write a wrapper.\n");
        IWICMetadataQueryReader_Release(host);
        c->super.iret = E_FAIL;
    }
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETPREVIEW);
    call.iface = (ULONG_PTR)decoder;
    call.ppIBitmapSource = (ULONG_PTR)ppIBitmapSource;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetPreview(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetPreview *c = (struct qemu_WICBitmapDecoder_GetPreview *)call;
    struct qemu_wic_decoder *decoder;
    IWICBitmapSource *host;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetPreview(decoder->host, c->ppIBitmapSource ? &host : NULL);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host GetColorContexts succeeded, write a wrapper.\n");
        IWICBitmapSource_Release(host);
        c->super.iret = E_FAIL;
    }
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

static HRESULT WINAPI WICBitmapDecoder_GetColorContexts(IWICBitmapDecoder *iface, UINT cCount,
        IWICColorContext **ppIColorContexts, UINT *pcActualCount)
{
    struct qemu_WICBitmapDecoder_GetColorContexts call;
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETCOLORCONTEXTS);
    call.iface = (ULONG_PTR)decoder;
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
    struct qemu_wic_decoder *decoder;
    IWICColorContext *host;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetColorContexts(decoder->host, c->cCount,
            c->ppIColorContexts ? & host : NULL, QEMU_G2H(c->pcActualCount));

    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host GetColorContexts succeeded, write a wrapper.\n");
        IWICColorContext_Release(host);
        c->super.iret = E_FAIL;
    }
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETTHUMBNAIL);
    call.iface = (ULONG_PTR)decoder;
    call.ppIThumbnail = (ULONG_PTR)ppIThumbnail;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetThumbnail(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetThumbnail *c = (struct qemu_WICBitmapDecoder_GetThumbnail *)call;
    struct qemu_wic_decoder *decoder;
    IWICBitmapSource *host;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetThumbnail(decoder->host, c->ppIThumbnail ? &host : NULL);

    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host GetColorContexts succeeded, write a wrapper.\n");
        IWICBitmapSource_Release(host);
        c->super.iret = E_FAIL;
    }
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
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETFRAMECOUNT);
    call.iface = (ULONG_PTR)decoder;
    call.pCount = (ULONG_PTR)pCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetFrameCount(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetFrameCount *c = (struct qemu_WICBitmapDecoder_GetFrameCount *)call;
    struct qemu_wic_decoder *decoder;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoder_GetFrameCount(decoder->host, QEMU_G2H(c->pCount));
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

static HRESULT WINAPI WICBitmapDecoder_GetFrame(IWICBitmapDecoder *iface, UINT index,
        IWICBitmapFrameDecode **ppIBitmapFrame)
{
    struct qemu_WICBitmapDecoder_GetFrame call;
    struct qemu_wic_decoder *decoder = impl_from_IWICBitmapDecoder(iface);
    struct qemu_wic_frame_decode *frame;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_GETFRAME);
    call.iface = (ULONG_PTR)decoder;
    call.index = index;
    call.ppIBitmapFrame = (ULONG_PTR)ppIBitmapFrame;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    frame = (struct qemu_wic_frame_decode *)(ULONG_PTR)call.ppIBitmapFrame;
    frame->IWICBitmapFrameDecode_iface.lpVtbl = &WICBitmapFrameDecode_FrameVtbl;
    frame->IWICMetadataBlockReader_iface.lpVtbl = &IWICMetadataBlockReader_BlockVtbl;
    *ppIBitmapFrame = &frame->IWICBitmapFrameDecode_iface;

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoder_GetFrame(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_GetFrame *c = (struct qemu_WICBitmapDecoder_GetFrame *)call;
    struct qemu_wic_decoder *decoder;
    IWICBitmapFrameDecode *host, *host2;
    struct qemu_wic_frame_decode *frame;
    BOOL multi_obj;
    UINT count, i;
    HRESULT hr;

    WINE_TRACE("\n");
    decoder = QEMU_G2H(c->iface);

    /* Pass the reference to the app. */
    c->super.iret = IWICBitmapDecoder_GetFrame(decoder->host, c->index, 
            c->ppIBitmapFrame ? &host : NULL);

    if (SUCCEEDED(c->super.iret))
    {
        /* Some decoders (bitmap) always return the same frame interface when asked for the same frame number,
         * others create a new interface all the time (gif). Note that the gif decoder will happily create a
         * new interface when decoding a single-frame gif, so the count is a poor way to figure out what is
         * what.
         *
         * Because we rely on the host refcount to free our own objects, we have to be careful here. When we
         * have single-frame object and use multiple wrappers we won't free our wrappers properly. A single
         * wrapper for multiple objects doesn't work anyway. */
        if (c->index)
        {
            multi_obj = TRUE;
        }
        else
        {
            IWICBitmapDecoder_GetFrame(decoder->host, 0, &host2);
            multi_obj = host != host2;
            IWICBitmapFrameDecode_Release(host2);
        }

        if (multi_obj)
        {
            frame = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*frame));
            if (!frame)
            {
                WINE_WARN("Out of memory\n");
                IWICBitmapFrameDecode_Release(host);
                c->super.iret = E_OUTOFMEMORY;
                return;
            }
            frame->decoder = decoder;
        }
        else
        {
            frame = &decoder->static_frame;
        }

        frame->host = host;
        if (SUCCEEDED(IWICBitmapFrameDecode_QueryInterface(host, &IID_IWICMetadataBlockReader,
                (void **)&frame->host_block_reader)))
        {
            IWICMetadataBlockReader_GetCount(frame->host_block_reader, &count);
            frame->reader_count = count;

            frame->readers = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, count * sizeof(*frame->readers));
            if (!frame->readers)
                WINE_ERR("Out of memory\n");

            for (i = 0; i < count; ++i)
            {
                IWICMetadataReader *host_reader;
                hr = IWICMetadataBlockReader_GetReaderByIndex(frame->host_block_reader, i, &host_reader);
                if (FAILED(hr))
                    WINE_ERR("Failed to get reader %u\n", i);

                frame->readers[i] = MetadataHandler_create_host(host_reader);
                if (!frame->readers[i])
                    WINE_ERR("Out of memory\n");
            }

            IWICMetadataBlockReader_Release(frame->host_block_reader);
        }

        c->ppIBitmapFrame = QEMU_H2G(frame);
    }
}

#endif

struct qemu_WICBitmapDecoder_create_host
{
    struct qemu_syscall super;
    uint64_t clsid;
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

const IWICBitmapFrameDecodeVtbl WICBitmapFrameDecode_FrameVtbl =
{
    WICBitmapFrameDecode_QueryInterface,
    WICBitmapFrameDecode_AddRef,
    WICBitmapFrameDecode_Release,
    WICBitmapFrameDecode_GetSize,
    WICBitmapFrameDecode_GetPixelFormat,
    WICBitmapFrameDecode_GetResolution,
    WICBitmapFrameDecode_CopyPalette,
    WICBitmapFrameDecode_CopyPixels,
    WICBitmapFrameDecode_GetMetadataQueryReader,
    WICBitmapFrameDecode_GetColorContexts,
    WICBitmapFrameDecode_GetThumbnail
};

const IWICMetadataBlockReaderVtbl IWICMetadataBlockReader_BlockVtbl =
{
    WICMetadataBlockReader_QueryInterface,
    WICMetadataBlockReader_AddRef,
    WICMetadataBlockReader_Release,
    WICMetadataBlockReader_GetContainerFormat,
    WICMetadataBlockReader_GetCount,
    WICMetadataBlockReader_GetReaderByIndex,
    WICMetadataBlockReader_GetEnumerator
};

void WICBitmapDecoder_init_guest(struct qemu_wic_decoder *decoder)
{
    decoder->IWICBitmapDecoder_iface.lpVtbl = &WICBitmapDecoder_Vtbl;
}

HRESULT Decoder_CreateInstance(const CLSID *clsid, const IID *iid, void **obj)
{
    struct qemu_WICBitmapDecoder_create_host call;
    struct qemu_wic_decoder *decoder;
    HRESULT hr;

    WINE_TRACE("(%s,%p)\n", wine_dbgstr_guid(iid), obj);

    *obj = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODER_CREATE_HOST);
    call.clsid = (ULONG_PTR)clsid;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    decoder = (struct qemu_wic_decoder *)(ULONG_PTR)call.decoder;
    WICBitmapDecoder_init_guest(decoder);

    hr = IWICBitmapDecoder_QueryInterface(&decoder->IWICBitmapDecoder_iface, iid, obj);
    IWICBitmapDecoder_Release(&decoder->IWICBitmapDecoder_iface);

    return hr;
}

#else

struct qemu_wic_decoder *WICBitmapDecoder_create_host(IWICBitmapDecoder *host)
{
    struct qemu_wic_decoder *ret;
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

void qemu_WICBitmapDecoder_create_host(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoder_create_host *c = (struct qemu_WICBitmapDecoder_create_host *)call;
    struct qemu_wic_decoder *decoder;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *host_factory;
    HRESULT hr;
    IWICBitmapDecoder *host;

    lib = GetModuleHandleA("windowscodecs");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(QEMU_G2H(c->clsid), &IID_IClassFactory, (void *)&host_factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(host_factory, NULL, &IID_IWICBitmapDecoder, (void **)&host);
    IClassFactory_Release(host_factory);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IID_IWICBitmapDecoder object.\n");
        c->super.iret = hr;
        return;
    }

    decoder = WICBitmapDecoder_create_host(host);
    if (!decoder)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->decoder = QEMU_H2G(decoder);
    c->super.iret = hr;
}

#endif

