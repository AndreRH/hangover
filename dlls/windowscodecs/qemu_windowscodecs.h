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
    CALL_INIT_DLL = 0,
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

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

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
