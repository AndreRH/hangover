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

#include <initguid.h>
#include <windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

#include "istream_wrapper_impl.h"

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t reason;
    uint64_t guest_bitmap_source_addref;
    uint64_t guest_bitmap_source_release;
    uint64_t guest_bitmap_source_getsize;
    uint64_t guest_bitmap_source_getpixelformat;
    uint64_t guest_bitmap_source_copypixels;
    uint64_t guest_bitmap_source_getresolution;
    uint64_t guest_bitmap_source_copypalette;
    struct istream_wrapper_funcs istream;
};

struct guest_bitmap_source_getsize
{
    uint64_t source;
    uint64_t width, height;
};

struct guest_bitmap_source_getpixelformat
{
    uint64_t source;
    uint64_t fmt;
};

struct guest_bitmap_source_copypixels
{
    uint64_t source;
    uint64_t rect, stride, size, buffer;
};

struct guest_bitmap_source_getresolution
{
    uint64_t source;
    uint64_t x, y;
};

struct guest_bitmap_source_copypalette
{
    uint64_t source;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static ULONG __fastcall guest_bitmap_source_addref(IWICBitmapSource *source)
{
    return IWICBitmapSource_AddRef(source);
}

static ULONG __fastcall guest_bitmap_source_release(IWICBitmapSource *source)
{
    return IWICBitmapSource_Release(source);
}

static ULONG __fastcall guest_bitmap_source_getsize(struct guest_bitmap_source_getsize *call)
{
    return IWICBitmapSource_GetSize((IWICBitmapSource *)(ULONG_PTR)call->source,
            (UINT *)(ULONG_PTR)call->width, (UINT *)(ULONG_PTR)call->height);
}

static ULONG __fastcall guest_bitmap_source_getpixelformat(struct guest_bitmap_source_getpixelformat *call)
{
    return IWICBitmapSource_GetPixelFormat((IWICBitmapSource *)(ULONG_PTR)call->source,
            (WICPixelFormatGUID *)(ULONG_PTR)call->fmt);
}

static ULONG __fastcall guest_bitmap_source_copypixels(struct guest_bitmap_source_copypixels *call)
{
    return IWICBitmapSource_CopyPixels((IWICBitmapSource *)(ULONG_PTR)call->source,
            (const WICRect *)(ULONG_PTR)call->rect, call->stride, call->size, (BYTE *)(ULONG_PTR)call->buffer);
}

static ULONG __fastcall guest_bitmap_source_getresolution(struct guest_bitmap_source_getresolution *call)
{
    return IWICBitmapSource_GetResolution((IWICBitmapSource *)(ULONG_PTR)call->source,
            (double *)(ULONG_PTR)call->x, (double *)(ULONG_PTR)call->y);
}

static ULONG __fastcall guest_bitmap_source_copypalette(struct guest_bitmap_source_copypalette *call)
{
    struct qemu_wic_palette *pal = (struct qemu_wic_palette *)(ULONG_PTR)call->palette;

    WICPalette_init_guest(pal);

    return IWICBitmapSource_CopyPalette((IWICBitmapSource *)(ULONG_PTR)call->source, &pal->IWICPalette_iface);
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;
    HMODULE dxgi;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_ATTACH;
        call.guest_bitmap_source_addref = (ULONG_PTR)guest_bitmap_source_addref;
        call.guest_bitmap_source_release = (ULONG_PTR)guest_bitmap_source_release;
        call.guest_bitmap_source_getsize = (ULONG_PTR)guest_bitmap_source_getsize;
        call.guest_bitmap_source_getpixelformat = (ULONG_PTR)guest_bitmap_source_getpixelformat;
        call.guest_bitmap_source_copypixels = (ULONG_PTR)guest_bitmap_source_copypixels;
        call.guest_bitmap_source_getresolution = (ULONG_PTR)guest_bitmap_source_getresolution;
        call.guest_bitmap_source_copypalette = (ULONG_PTR)guest_bitmap_source_copypalette;
        istream_wrapper_get_funcs(&call.istream);
        qemu_syscall(&call.super);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_DETACH;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

HRESULT WINAPI DllCanUnloadNow(void)
{
    WINE_FIXME("Stub\n");
    return S_FALSE;
}

HRESULT WINAPI DllRegisterServer(void)
{
    WINE_ERR("Should not be called on the wrapper.\n");
    return E_FAIL;
}

HRESULT WINAPI DllUnregisterServer(void)
{
    WINE_ERR("Should not be called on the wrapper.\n");
    return E_FAIL;
}

#else

static uint64_t guest_bitmap_source_addref;
static uint64_t guest_bitmap_source_release;
static uint64_t guest_bitmap_source_getsize;
static uint64_t guest_bitmap_source_getpixelformat;
static uint64_t guest_bitmap_source_copypixels;
static uint64_t guest_bitmap_source_getresolution;
static uint64_t guest_bitmap_source_copypalette;

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;

    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            guest_bitmap_source_addref = c->guest_bitmap_source_addref;
            guest_bitmap_source_release = c->guest_bitmap_source_release;
            guest_bitmap_source_getsize = c->guest_bitmap_source_getsize;
            guest_bitmap_source_getpixelformat = c->guest_bitmap_source_getpixelformat;
            guest_bitmap_source_copypixels = c->guest_bitmap_source_copypixels;
            guest_bitmap_source_getresolution = c->guest_bitmap_source_getresolution;
            guest_bitmap_source_copypalette = c->guest_bitmap_source_copypalette;
            istream_wrapper_set_funcs(&c->istream);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ComponentFactory_AddRef,
    qemu_ComponentFactory_create_host,
    qemu_ComponentFactory_CreateBitmap,
    qemu_ComponentFactory_CreateBitmapClipper,
    qemu_ComponentFactory_CreateBitmapFlipRotator,
    qemu_ComponentFactory_CreateBitmapFromHBITMAP,
    qemu_ComponentFactory_CreateBitmapFromHICON,
    qemu_ComponentFactory_CreateBitmapFromMemory,
    qemu_ComponentFactory_CreateBitmapFromSource,
    qemu_ComponentFactory_CreateBitmapFromSourceRect,
    qemu_ComponentFactory_CreateBitmapScaler,
    qemu_ComponentFactory_CreateColorContext,
    qemu_ComponentFactory_CreateColorTransformer,
    qemu_ComponentFactory_CreateComponentEnumerator,
    qemu_ComponentFactory_CreateComponentInfo,
    qemu_ComponentFactory_CreateDecoder,
    qemu_ComponentFactory_CreateDecoderFromFileHandle,
    qemu_ComponentFactory_CreateDecoderFromFilename,
    qemu_ComponentFactory_CreateDecoderFromStream,
    qemu_ComponentFactory_CreateEncoder,
    qemu_ComponentFactory_CreateEncoderPropertyBag,
    qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder,
    qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode,
    qemu_ComponentFactory_CreateFormatConverter,
    qemu_ComponentFactory_CreateMetadataReader,
    qemu_ComponentFactory_CreateMetadataReaderFromContainer,
    qemu_ComponentFactory_CreateMetadataWriter,
    qemu_ComponentFactory_CreateMetadataWriterFromReader,
    qemu_ComponentFactory_CreatePalette,
    qemu_ComponentFactory_CreateQueryReaderFromBlockReader,
    qemu_ComponentFactory_CreateQueryWriter,
    qemu_ComponentFactory_CreateQueryWriterFromBlockWriter,
    qemu_ComponentFactory_CreateQueryWriterFromReader,
    qemu_ComponentFactory_CreateStream,
    qemu_ComponentFactory_QueryInterface,
    qemu_ComponentFactory_Release,
    qemu_EnumUnknown_AddRef,
    qemu_EnumUnknown_Clone,
    qemu_EnumUnknown_Next,
    qemu_EnumUnknown_QueryInterface,
    qemu_EnumUnknown_Release,
    qemu_EnumUnknown_Reset,
    qemu_EnumUnknown_Skip,
    qemu_IMILBitmapImpl_CopyPalette,
    qemu_IMILBitmapImpl_CopyPixels,
    qemu_IMILBitmapImpl_GetPixelFormat,
    qemu_IMILBitmapImpl_GetResolution,
    qemu_IMILBitmapImpl_GetSize,
    qemu_IMILBitmapImpl_QueryInterface,
    qemu_IMILBitmapImpl_UnknownMethod1,
    qemu_IMILUnknown1Impl_QueryInterface,
    qemu_IMILUnknown2Impl_QueryInterface,
    qemu_IMILUnknown2Impl_UnknownMethod1,
    qemu_init_dll,
    qemu_WICBitmap_AddRef,
    qemu_WICBitmap_CopyPalette,
    qemu_WICBitmap_CopyPixels,
    qemu_WICBitmap_GetPixelFormat,
    qemu_WICBitmap_GetResolution,
    qemu_WICBitmap_GetSize,
    qemu_WICBitmap_Lock,
    qemu_WICBitmap_QueryInterface,
    qemu_WICBitmap_Release,
    qemu_WICBitmap_SetPalette,
    qemu_WICBitmap_SetResolution,
    qemu_WICBitmapClipper_AddRef,
    qemu_WICBitmapClipper_CopyPalette,
    qemu_WICBitmapClipper_CopyPixels,
    qemu_WICBitmapClipper_GetPixelFormat,
    qemu_WICBitmapClipper_GetResolution,
    qemu_WICBitmapClipper_GetSize,
    qemu_WICBitmapClipper_Initialize,
    qemu_WICBitmapClipper_QueryInterface,
    qemu_WICBitmapClipper_Release,
    qemu_WICBitmapDecoder_AddRef,
    qemu_WICBitmapDecoder_CopyPalette,
    qemu_WICBitmapDecoder_create_host,
    qemu_WICBitmapDecoder_GetColorContexts,
    qemu_WICBitmapDecoder_GetContainerFormat,
    qemu_WICBitmapDecoder_GetDecoderInfo,
    qemu_WICBitmapDecoder_GetFrame,
    qemu_WICBitmapDecoder_GetFrameCount,
    qemu_WICBitmapDecoder_GetMetadataQueryReader,
    qemu_WICBitmapDecoder_GetPreview,
    qemu_WICBitmapDecoder_GetThumbnail,
    qemu_WICBitmapDecoder_Initialize,
    qemu_WICBitmapDecoder_QueryCapability,
    qemu_WICBitmapDecoder_QueryInterface,
    qemu_WICBitmapDecoder_Release,
    qemu_WICBitmapDecoderInfo_CreateInstance,
    qemu_WICBitmapDecoderInfo_DoesSupportAnimation,
    qemu_WICBitmapDecoderInfo_DoesSupportChromaKey,
    qemu_WICBitmapDecoderInfo_DoesSupportLossless,
    qemu_WICBitmapDecoderInfo_DoesSupportMultiframe,
    qemu_WICBitmapDecoderInfo_GetColorManagementVersion,
    qemu_WICBitmapDecoderInfo_GetContainerFormat,
    qemu_WICBitmapDecoderInfo_GetDeviceManufacturer,
    qemu_WICBitmapDecoderInfo_GetDeviceModels,
    qemu_WICBitmapDecoderInfo_GetFileExtensions,
    qemu_WICBitmapDecoderInfo_GetMimeTypes,
    qemu_WICBitmapDecoderInfo_GetPatterns,
    qemu_WICBitmapDecoderInfo_GetPixelFormats,
    qemu_WICBitmapDecoderInfo_MatchesMimeType,
    qemu_WICBitmapDecoderInfo_MatchesPattern,
    qemu_WICBitmapEncoder_AddRef,
    qemu_WICBitmapEncoder_Commit,
    qemu_WICBitmapEncoder_CreateNewFrame,
    qemu_WICBitmapEncoder_GetContainerFormat,
    qemu_WICBitmapEncoder_GetEncoderInfo,
    qemu_WICBitmapEncoder_GetMetadataQueryWriter,
    qemu_WICBitmapEncoder_Initialize,
    qemu_WICBitmapEncoder_QueryInterface,
    qemu_WICBitmapEncoder_Release,
    qemu_WICBitmapEncoder_SetColorContexts,
    qemu_WICBitmapEncoder_SetPalette,
    qemu_WICBitmapEncoder_SetPreview,
    qemu_WICBitmapEncoder_SetThumbnail,
    qemu_WICBitmapEncoderInfo_CreateInstance,
    qemu_WICBitmapEncoderInfo_DoesSupportAnimation,
    qemu_WICBitmapEncoderInfo_DoesSupportChromaKey,
    qemu_WICBitmapEncoderInfo_DoesSupportLossless,
    qemu_WICBitmapEncoderInfo_DoesSupportMultiframe,
    qemu_WICBitmapEncoderInfo_GetColorManagementVersion,
    qemu_WICBitmapEncoderInfo_GetContainerFormat,
    qemu_WICBitmapEncoderInfo_GetDeviceManufacturer,
    qemu_WICBitmapEncoderInfo_GetDeviceModels,
    qemu_WICBitmapEncoderInfo_GetFileExtensions,
    qemu_WICBitmapEncoderInfo_GetMimeTypes,
    qemu_WICBitmapEncoderInfo_GetPixelFormats,
    qemu_WICBitmapEncoderInfo_MatchesMimeType,
    qemu_WICBitmapFrameDecode_AddRef,
    qemu_WICBitmapFrameDecode_CopyPalette,
    qemu_WICBitmapFrameDecode_CopyPixels,
    qemu_WICBitmapFrameDecode_GetColorContexts,
    qemu_WICBitmapFrameDecode_GetMetadataQueryReader,
    qemu_WICBitmapFrameDecode_GetPixelFormat,
    qemu_WICBitmapFrameDecode_GetResolution,
    qemu_WICBitmapFrameDecode_GetSize,
    qemu_WICBitmapFrameDecode_GetThumbnail,
    qemu_WICBitmapFrameDecode_QueryInterface,
    qemu_WICBitmapFrameDecode_Release,
    qemu_WICBitmapFrameEncode_AddRef,
    qemu_WICBitmapFrameEncode_Commit,
    qemu_WICBitmapFrameEncode_GetMetadataQueryWriter,
    qemu_WICBitmapFrameEncode_Initialize,
    qemu_WICBitmapFrameEncode_QueryInterface,
    qemu_WICBitmapFrameEncode_Release,
    qemu_WICBitmapFrameEncode_SetColorContexts,
    qemu_WICBitmapFrameEncode_SetPalette,
    qemu_WICBitmapFrameEncode_SetPixelFormat,
    qemu_WICBitmapFrameEncode_SetResolution,
    qemu_WICBitmapFrameEncode_SetSize,
    qemu_WICBitmapFrameEncode_SetThumbnail,
    qemu_WICBitmapFrameEncode_WritePixels,
    qemu_WICBitmapFrameEncode_WriteSource,
    qemu_WICBitmapLock_AddRef,
    qemu_WICBitmapLock_GetDataPointer,
    qemu_WICBitmapLock_GetPixelFormat,
    qemu_WICBitmapLock_GetSize,
    qemu_WICBitmapLock_GetStride,
    qemu_WICBitmapLock_QueryInterface,
    qemu_WICBitmapLock_Release,
    qemu_WICComponentInfo_AddRef,
    qemu_WICComponentInfo_GetAuthor,
    qemu_WICComponentInfo_GetCLSID,
    qemu_WICComponentInfo_GetComponentType,
    qemu_WICComponentInfo_GetFriendlyName,
    qemu_WICComponentInfo_GetSigningStatus,
    qemu_WICComponentInfo_GetSpecVersion,
    qemu_WICComponentInfo_GetVendorGUID,
    qemu_WICComponentInfo_GetVersion,
    qemu_WICComponentInfo_QueryInterface,
    qemu_WICComponentInfo_Release,
    qemu_WICConvertBitmapSource,
    qemu_WICCreateBitmapFromSectionEx,
    qemu_WICFormatConverterInfo_CreateInstance,
    qemu_WICFormatConverterInfo_GetPixelFormats,
    qemu_WICMapGuidToShortName,
    qemu_WICMapSchemaToName,
    qemu_WICMapShortNameToGuid,
    qemu_WICMetadataReaderInfo_CreateInstance,
    qemu_WICMetadataReaderInfo_DoesRequireFixedSize,
    qemu_WICMetadataReaderInfo_DoesRequireFullStream,
    qemu_WICMetadataReaderInfo_DoesSupportPadding,
    qemu_WICMetadataReaderInfo_GetContainerFormats,
    qemu_WICMetadataReaderInfo_GetDeviceManufacturer,
    qemu_WICMetadataReaderInfo_GetDeviceModels,
    qemu_WICMetadataReaderInfo_GetMetadataFormat,
    qemu_WICMetadataReaderInfo_GetPatterns,
    qemu_WICMetadataReaderInfo_MatchesPattern,
    qemu_WICPalette_AddRef,
    qemu_WICPalette_GetColorCount,
    qemu_WICPalette_GetColors,
    qemu_WICPalette_GetType,
    qemu_WICPalette_HasAlpha,
    qemu_WICPalette_InitializeCustom,
    qemu_WICPalette_InitializeFromBitmap,
    qemu_WICPalette_InitializeFromPalette,
    qemu_WICPalette_InitializePredefined,
    qemu_WICPalette_IsBlackWhite,
    qemu_WICPalette_IsGrayscale,
    qemu_WICPalette_QueryInterface,
    qemu_WICPalette_Release,
    qemu_WICPixelFormatInfo2_GetBitsPerPixel,
    qemu_WICPixelFormatInfo2_GetChannelCount,
    qemu_WICPixelFormatInfo2_GetChannelMask,
    qemu_WICPixelFormatInfo2_GetColorContext,
    qemu_WICPixelFormatInfo2_GetFormatGUID,
    qemu_WICPixelFormatInfo2_GetNumericRepresentation,
    qemu_WICPixelFormatInfo2_SupportsTransparency,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side windowscodecs wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

static inline struct qemu_bitmap_source *impl_from_IWICBitmapSource(IWICBitmapSource *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_bitmap_source, IWICBitmapSource_iface);
}

static HRESULT WINAPI qemu_bitmap_source_QueryInterface(IWICBitmapSource *iface, REFIID iid, void **ppv)
{
    if (IsEqualIID(&IID_IUnknown, iid) ||
        IsEqualIID(&IID_IWICBitmapSource, iid))
    {
        *ppv = iface;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    return S_OK;
}

static ULONG WINAPI qemu_bitmap_source_AddRef(IWICBitmapSource *iface)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    ULONG ref = InterlockedIncrement(&source->ref);

    WINE_TRACE("(%p) refcount=%u\n", iface, ref);

    return ref;
}

static ULONG WINAPI qemu_bitmap_source_Release(IWICBitmapSource *iface)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    ULONG ref = InterlockedDecrement(&source->ref), ref2;

    WINE_TRACE("(%p) refcount=%u\n", iface, ref);

    if (ref == 0)
    {
        WINE_TRACE("Calling guest release method.\n");
        ref2 = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_release), source->guest);
        WINE_TRACE("Guest release method returned %u.\n", ref2);
        HeapFree(GetProcessHeap(), 0, source);
    }

    return ref;
}

static HRESULT WINAPI qemu_bitmap_source_GetSize(IWICBitmapSource *iface, UINT *width, UINT *height)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    struct guest_bitmap_source_getsize call;
    HRESULT hr;

    WINE_TRACE("\n");
    call.source = source->guest;
    call.width = QEMU_H2G(width);
    call.height = QEMU_H2G(height);

    hr = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_getsize), QEMU_H2G(&call));

    return hr;
}

static HRESULT WINAPI qemu_bitmap_source_GetPixelFormat(IWICBitmapSource *iface,
        WICPixelFormatGUID *format)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    struct guest_bitmap_source_getpixelformat call;
    HRESULT hr;

    WINE_TRACE("\n");
    call.source = source->guest;
    call.fmt = QEMU_H2G(format);

    hr = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_getpixelformat), QEMU_H2G(&call));

    return hr;
}

static HRESULT WINAPI qemu_bitmap_source_GetResolution(IWICBitmapSource *iface,
        double *dpiX, double *dpiY)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    struct guest_bitmap_source_getresolution call;
    HRESULT hr;

    WINE_TRACE("\n");
    call.source = source->guest;
    call.x = QEMU_H2G(dpiX);
    call.y = QEMU_H2G(dpiY);

    hr = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_getresolution), QEMU_H2G(&call));

    return hr;
}

static HRESULT WINAPI qemu_bitmap_source_CopyPalette(IWICBitmapSource *iface,
        IWICPalette *palette)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    struct qemu_wic_palette temp_palette = {0};
    struct guest_bitmap_source_copypalette call;
    HRESULT hr;

    WINE_FIXME("The stack alloc is begging for trouble.\n");
    temp_palette.host = palette;
    call.source = source->guest;
    call.palette = QEMU_H2G(&temp_palette);

    hr = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_copypalette), QEMU_H2G(&call));

    return hr;
}

static HRESULT WINAPI qemu_bitmap_source_CopyPixels(IWICBitmapSource *iface,
        const WICRect *rc, UINT stride, UINT buffer_size, BYTE *buffer)
{
    struct qemu_bitmap_source *source = impl_from_IWICBitmapSource(iface);
    struct guest_bitmap_source_copypixels call;
    HRESULT hr;

    WINE_TRACE("\n");
    call.source = source->guest;
    call.rect = QEMU_H2G(rc);
    call.stride = stride;
    call.size = buffer_size;
    call.buffer = QEMU_H2G(buffer);

    hr = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_copypixels), QEMU_H2G(&call));

    return hr;
}

static const IWICBitmapSourceVtbl qemu_bitmap_source_vtbl =
{
    qemu_bitmap_source_QueryInterface,
    qemu_bitmap_source_AddRef,
    qemu_bitmap_source_Release,
    qemu_bitmap_source_GetSize,
    qemu_bitmap_source_GetPixelFormat,
    qemu_bitmap_source_GetResolution,
    qemu_bitmap_source_CopyPalette,
    qemu_bitmap_source_CopyPixels
};

struct qemu_bitmap_source *bitmap_source_wrapper_create(uint64_t guest)
{
    struct qemu_bitmap_source *ret;
    ULONG ref;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        return NULL;

    ret->IWICBitmapSource_iface.lpVtbl = &qemu_bitmap_source_vtbl;
    ret->guest = guest;
    ret->ref = 1;

    WINE_TRACE("Calling guest addref method.\n");
    ref = qemu_ops->qemu_execute(QEMU_G2H(guest_bitmap_source_addref), guest);
    WINE_TRACE("Guest addref returned %u.\n", ref);

    return ret;
}

#endif
