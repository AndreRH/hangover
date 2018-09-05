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

#ifndef QEMU_WINDOWSCODECS_H
#define QEMU_WINDOWSCODECS_H

enum windowscodecs_calls
{
    CALL_COMPONENTFACTORY_ADDREF = 0,
    CALL_COMPONENTFACTORY_CREATEBITMAP,
    CALL_COMPONENTFACTORY_CREATEBITMAPCLIPPER,
    CALL_COMPONENTFACTORY_CREATEBITMAPFLIPROTATOR,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMHBITMAP,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMHICON,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMMEMORY,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMSOURCE,
    CALL_COMPONENTFACTORY_CREATEBITMAPFROMSOURCERECT,
    CALL_COMPONENTFACTORY_CREATEBITMAPSCALER,
    CALL_COMPONENTFACTORY_CREATECOLORCONTEXT,
    CALL_COMPONENTFACTORY_CREATECOLORTRANSFORMER,
    CALL_COMPONENTFACTORY_CREATECOMPONENTENUMERATOR,
    CALL_COMPONENTFACTORY_CREATECOMPONENTINFO,
    CALL_COMPONENTFACTORY_CREATEDECODER,
    CALL_COMPONENTFACTORY_CREATEDECODERFROMFILEHANDLE,
    CALL_COMPONENTFACTORY_CREATEDECODERFROMFILENAME,
    CALL_COMPONENTFACTORY_CREATEDECODERFROMSTREAM,
    CALL_COMPONENTFACTORY_CREATEENCODER,
    CALL_COMPONENTFACTORY_CREATEENCODERPROPERTYBAG,
    CALL_COMPONENTFACTORY_CREATEFASTMETADATAENCODERFROMDECODER,
    CALL_COMPONENTFACTORY_CREATEFASTMETADATAENCODERFROMFRAMEDECODE,
    CALL_COMPONENTFACTORY_CREATEFORMATCONVERTER,
    CALL_COMPONENTFACTORY_CREATEMETADATAREADER,
    CALL_COMPONENTFACTORY_CREATEMETADATAREADERFROMCONTAINER,
    CALL_COMPONENTFACTORY_CREATEMETADATAWRITER,
    CALL_COMPONENTFACTORY_CREATEMETADATAWRITERFROMREADER,
    CALL_COMPONENTFACTORY_CREATEPALETTE,
    CALL_COMPONENTFACTORY_CREATEQUERYREADERFROMBLOCKREADER,
    CALL_COMPONENTFACTORY_CREATEQUERYWRITER,
    CALL_COMPONENTFACTORY_CREATEQUERYWRITERFROMBLOCKWRITER,
    CALL_COMPONENTFACTORY_CREATEQUERYWRITERFROMREADER,
    CALL_COMPONENTFACTORY_CREATESTREAM,
    CALL_COMPONENTFACTORY_CREATE_HOST,
    CALL_COMPONENTFACTORY_QUERYINTERFACE,
    CALL_COMPONENTFACTORY_RELEASE,
    CALL_INIT_DLL,
    CALL_WICBITMAPDECODER_ADDREF,
    CALL_WICBITMAPDECODER_COPYPALETTE,
    CALL_WICBITMAPDECODER_GETCOLORCONTEXTS,
    CALL_WICBITMAPDECODER_GETCONTAINERFORMAT,
    CALL_WICBITMAPDECODER_GETDECODERINFO,
    CALL_WICBITMAPDECODER_GETFRAME,
    CALL_WICBITMAPDECODER_GETFRAMECOUNT,
    CALL_WICBITMAPDECODER_GETMETADATAQUERYREADER,
    CALL_WICBITMAPDECODER_GETPREVIEW,
    CALL_WICBITMAPDECODER_GETTHUMBNAIL,
    CALL_WICBITMAPDECODER_INITIALIZE,
    CALL_WICBITMAPDECODER_QUERYCAPABILITY,
    CALL_WICBITMAPDECODER_QUERYINTERFACE,
    CALL_WICBITMAPDECODER_RELEASE,
    CALL_WICBITMAPENCODER_ADDREF,
    CALL_WICBITMAPENCODER_COMMIT,
    CALL_WICBITMAPENCODER_CREATENEWFRAME,
    CALL_WICBITMAPENCODER_GETCONTAINERFORMAT,
    CALL_WICBITMAPENCODER_GETENCODERINFO,
    CALL_WICBITMAPENCODER_GETMETADATAQUERYWRITER,
    CALL_WICBITMAPENCODER_INITIALIZE,
    CALL_WICBITMAPENCODER_QUERYINTERFACE,
    CALL_WICBITMAPENCODER_RELEASE,
    CALL_WICBITMAPENCODER_SETCOLORCONTEXTS,
    CALL_WICBITMAPENCODER_SETPALETTE,
    CALL_WICBITMAPENCODER_SETPREVIEW,
    CALL_WICBITMAPENCODER_SETTHUMBNAIL,
    CALL_WICBITMAPFRAMEDECODE_ADDREF,
    CALL_WICBITMAPFRAMEDECODE_COPYPALETTE,
    CALL_WICBITMAPFRAMEDECODE_COPYPIXELS,
    CALL_WICBITMAPFRAMEDECODE_GETCOLORCONTEXTS,
    CALL_WICBITMAPFRAMEDECODE_GETMETADATAQUERYREADER,
    CALL_WICBITMAPFRAMEDECODE_GETPIXELFORMAT,
    CALL_WICBITMAPFRAMEDECODE_GETRESOLUTION,
    CALL_WICBITMAPFRAMEDECODE_GETSIZE,
    CALL_WICBITMAPFRAMEDECODE_GETTHUMBNAIL,
    CALL_WICBITMAPFRAMEDECODE_QUERYINTERFACE,
    CALL_WICBITMAPFRAMEDECODE_RELEASE,
    CALL_WICBITMAPFRAMEENCODE_ADDREF,
    CALL_WICBITMAPFRAMEENCODE_COMMIT,
    CALL_WICBITMAPFRAMEENCODE_GETMETADATAQUERYWRITER,
    CALL_WICBITMAPFRAMEENCODE_INITIALIZE,
    CALL_WICBITMAPFRAMEENCODE_QUERYINTERFACE,
    CALL_WICBITMAPFRAMEENCODE_RELEASE,
    CALL_WICBITMAPFRAMEENCODE_SETCOLORCONTEXTS,
    CALL_WICBITMAPFRAMEENCODE_SETPALETTE,
    CALL_WICBITMAPFRAMEENCODE_SETPIXELFORMAT,
    CALL_WICBITMAPFRAMEENCODE_SETRESOLUTION,
    CALL_WICBITMAPFRAMEENCODE_SETSIZE,
    CALL_WICBITMAPFRAMEENCODE_SETTHUMBNAIL,
    CALL_WICBITMAPFRAMEENCODE_WRITEPIXELS,
    CALL_WICBITMAPFRAMEENCODE_WRITESOURCE,
    CALL_WICCONVERTBITMAPSOURCE,
    CALL_WICCREATEBITMAPFROMSECTION,
    CALL_WICCREATEBITMAPFROMSECTIONEX,
    CALL_WICMAPGUIDTOSHORTNAME,
    CALL_WICMAPSCHEMATONAME,
    CALL_WICMAPSHORTNAMETOGUID,
};

struct qemu_wic_frame_encode
{
    /* Guest fields */
    IWICBitmapFrameEncode IWICBitmapFrameEncode_iface;

    /* Host fields */
    IWICBitmapFrameEncode *host;
};

struct qemu_wic_encode
{
    /* Guest fields */
    IWICBitmapEncoder IWICBitmapEncoder_iface;
    IStream *stream;

    /* struct qemu_wic_frame_encode *frame; */

    /* Host fields */
    IWICBitmapEncoder *host;
    /* Put some stream wrapper vtable here */
};

struct qemu_wic_decode
{
    /* Host fields */
    IWICBitmapDecoder IWICBitmapDecoder_iface;
    IWICBitmapFrameDecode IWICBitmapFrameDecode_iface;

    /* Guest fields */
    IWICBitmapDecoder *host_bitmap;
    IWICBitmapFrameDecode *host_frame;
};

DEFINE_GUID(CLSID_WineTgaDecoder, 0xb11fc79a,0x67cc,0x43e6,0xa9,0xce,0xe3,0xd5,0x49,0x45,0xd3,0x04);
DEFINE_GUID(CLSID_WICIcnsEncoder, 0x312fb6f1,0xb767,0x409d,0x8a,0x6d,0x0f,0xc1,0x54,0xd4,0xf0,0x5c);
DEFINE_GUID(GUID_WineContainerFormatTga, 0x0c44fda1,0xa5c5,0x4298,0x96,0x85,0x47,0x3f,0xc1,0x7c,0xd3,0x22);
DEFINE_GUID(GUID_VendorWine, 0xddf46da1,0x7dc1,0x404e,0x98,0xf2,0xef,0xa4,0x8d,0xfc,0x95,0x0a);

#ifdef QEMU_DLL_GUEST

typedef HRESULT (*class_constructor)(const IID *, void **);
extern HRESULT Decoder_CreateInstance(const IID *iid, void **obj);
extern HRESULT Encoder_CreateInstance(const IID *iid, void **obj);
HRESULT ComponentFactory_CreateInstance(const IID *iid, void **obj);

#else

extern const struct qemu_ops *qemu_ops;

void qemu_ComponentFactory_AddRef(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmap(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapClipper(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFlipRotator(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromHBITMAP(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromHICON(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromMemory(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromSource(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapFromSourceRect(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateBitmapScaler(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateColorContext(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateColorTransformer(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateComponentEnumerator(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateComponentInfo(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoder(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoderFromFileHandle(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoderFromFilename(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateDecoderFromStream(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateEncoder(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateEncoderPropertyBag(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateFormatConverter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataReaderFromContainer(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataWriter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateMetadataWriterFromReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreatePalette(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryReaderFromBlockReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryWriter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryWriterFromBlockWriter(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateQueryWriterFromReader(struct qemu_syscall *call);
void qemu_ComponentFactory_CreateStream(struct qemu_syscall *call);
void qemu_ComponentFactory_QueryInterface(struct qemu_syscall *call);
void qemu_ComponentFactory_Release(struct qemu_syscall *call);
void qemu_ComponentFactory_create_host(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_CopyPalette(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetContainerFormat(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetDecoderInfo(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetFrame(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetFrameCount(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetMetadataQueryReader(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetPreview(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_GetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_QueryCapability(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapDecoder_Release(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_Commit(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_CreateNewFrame(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_GetContainerFormat(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_GetEncoderInfo(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_GetMetadataQueryWriter(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_Release(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetPalette(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetPreview(struct qemu_syscall *call);
void qemu_WICBitmapEncoder_SetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_CopyPalette(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_CopyPixels(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetMetadataQueryReader(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetResolution(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetSize(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_GetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapFrameDecode_Release(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_AddRef(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_Commit(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_GetMetadataQueryWriter(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_Initialize(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_QueryInterface(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_Release(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetColorContexts(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetPalette(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetPixelFormat(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetResolution(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetSize(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_SetThumbnail(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_WritePixels(struct qemu_syscall *call);
void qemu_WICBitmapFrameEncode_WriteSource(struct qemu_syscall *call);
void qemu_WICConvertBitmapSource(struct qemu_syscall *call);
void qemu_WICCreateBitmapFromSection(struct qemu_syscall *call);
void qemu_WICCreateBitmapFromSectionEx(struct qemu_syscall *call);
void qemu_WICMapGuidToShortName(struct qemu_syscall *call);
void qemu_WICMapSchemaToName(struct qemu_syscall *call);
void qemu_WICMapShortNameToGuid(struct qemu_syscall *call);

#endif

#endif
