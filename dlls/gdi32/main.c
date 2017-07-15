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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "gdi32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AbortDoc,
    qemu_AddFontMemResourceEx,
    qemu_AddFontResourceA,
    qemu_AddFontResourceExA,
    qemu_AddFontResourceExW,
    qemu_AddFontResourceW,
    qemu_CancelDC,
    qemu_CombineTransform,
    qemu_CopyEnhMetaFileA,
    qemu_CopyEnhMetaFileW,
    qemu_CopyMetaFileA,
    qemu_CopyMetaFileW,
    qemu_CreateColorSpaceA,
    qemu_CreateColorSpaceW,
    qemu_CreateCompatibleDC,
    qemu_CreateDCA,
    qemu_CreateDCW,
    qemu_CreateDIBitmap,
    qemu_CreateDIBSection,
    qemu_CreateFontA,
    qemu_CreateFontIndirectA,
    qemu_CreateFontIndirectExA,
    qemu_CreateFontIndirectExW,
    qemu_CreateFontIndirectW,
    qemu_CreateFontW,
    qemu_CreateICA,
    qemu_CreateICW,
    qemu_CreateScalableFontResourceA,
    qemu_CreateScalableFontResourceW,
    qemu_D3DKMTCreateDCFromMemory,
    qemu_D3DKMTDestroyDCFromMemory,
    qemu_DeleteColorSpace,
    qemu_DeleteDC,
    qemu_DeleteEnhMetaFile,
    qemu_DeleteMetaFile,
    qemu_DeleteObject,
    qemu_DPtoLP,
    qemu_EnableEUDC,
    qemu_EndDoc,
    qemu_EndPage,
    qemu_EnumEnhMetaFile,
    qemu_EnumFontFamiliesA,
    qemu_EnumFontFamiliesExA,
    qemu_EnumFontFamiliesExW,
    qemu_EnumFontFamiliesW,
    qemu_EnumFontsA,
    qemu_EnumFontsW,
    qemu_EnumMetaFile,
    qemu_EnumObjects,
    qemu_ExtTextOutA,
    qemu_ExtTextOutW,
    qemu_FontIsLinked,
    qemu_GdiComment,
    qemu_GdiFlush,
    qemu_GdiGetBatchLimit,
    qemu_GdiGetCharDimensions,
    qemu_GdiGetCodePage,
    qemu_GdiGetSpoolMessage,
    qemu_GdiInitializeLanguagePack,
    qemu_GdiInitSpool,
    qemu_GdiIsMetaFileDC,
    qemu_GdiIsMetaPrintDC,
    qemu_GdiIsPlayMetafileDC,
    qemu_GdiSetBatchLimit,
    qemu_GetArcDirection,
    qemu_GetAspectRatioFilterEx,
    qemu_GetBkColor,
    qemu_GetBkMode,
    qemu_GetBoundsRect,
    qemu_GetBrushOrgEx,
    qemu_GetCharABCWidthsA,
    qemu_GetCharABCWidthsFloatA,
    qemu_GetCharABCWidthsFloatW,
    qemu_GetCharABCWidthsI,
    qemu_GetCharABCWidthsW,
    qemu_GetCharacterPlacementA,
    qemu_GetCharacterPlacementW,
    qemu_GetCharWidth32A,
    qemu_GetCharWidth32W,
    qemu_GetCharWidthFloatA,
    qemu_GetCharWidthFloatW,
    qemu_GetCharWidthI,
    qemu_GetColorAdjustment,
    qemu_GetColorSpace,
    qemu_GetCurrentObject,
    qemu_GetCurrentPositionEx,
    qemu_GetDCBrushColor,
    qemu_GetDCOrgEx,
    qemu_GetDCPenColor,
    qemu_GetDeviceCaps,
    qemu_GetDeviceGammaRamp,
    qemu_GetDIBColorTable,
    qemu_GetDIBits,
    qemu_GetEnhMetaFileA,
    qemu_GetEnhMetaFileBits,
    qemu_GetEnhMetaFileDescriptionA,
    qemu_GetEnhMetaFileDescriptionW,
    qemu_GetEnhMetaFileHeader,
    qemu_GetEnhMetaFilePaletteEntries,
    qemu_GetEnhMetaFileW,
    qemu_GetFontData,
    qemu_GetFontLanguageInfo,
    qemu_GetFontResourceInfoW,
    qemu_GetFontUnicodeRanges,
    qemu_GetGlyphIndicesA,
    qemu_GetGlyphIndicesW,
    qemu_GetGlyphOutlineA,
    qemu_GetGlyphOutlineW,
    qemu_GetGraphicsMode,
    qemu_GetKerningPairsA,
    qemu_GetKerningPairsW,
    qemu_GetLayout,
    qemu_GetMapMode,
    qemu_GetMetaFileA,
    qemu_GetMetaFileBitsEx,
    qemu_GetMetaFileW,
    qemu_GetMiterLimit,
    qemu_GetObjectA,
    qemu_GetObjectType,
    qemu_GetObjectW,
    qemu_GetOutlineTextMetricsA,
    qemu_GetOutlineTextMetricsW,
    qemu_GetPolyFillMode,
    qemu_GetRelAbs,
    qemu_GetROP2,
    qemu_GetStockObject,
    qemu_GetStretchBltMode,
    qemu_GetTextAlign,
    qemu_GetTextCharacterExtra,
    qemu_GetTextColor,
    qemu_GetTextExtentExPointA,
    qemu_GetTextExtentExPointW,
    qemu_GetTextExtentPoint32A,
    qemu_GetTextExtentPoint32W,
    qemu_GetTextExtentPointA,
    qemu_GetTextExtentPointW,
    qemu_GetTextFaceA,
    qemu_GetTextFaceW,
    qemu_GetTextMetricsA,
    qemu_GetTextMetricsW,
    qemu_GetTransform,
    qemu_GetViewportExtEx,
    qemu_GetViewportOrgEx,
    qemu_GetWindowExtEx,
    qemu_GetWindowOrgEx,
    qemu_GetWinMetaFileBits,
    qemu_GetWorldTransform,
    qemu_LPtoDP,
    qemu_ModifyWorldTransform,
    qemu_OffsetViewportOrgEx,
    qemu_OffsetWindowOrgEx,
    qemu_PlayEnhMetaFile,
    qemu_PlayEnhMetaFileRecord,
    qemu_PlayMetaFile,
    qemu_PlayMetaFileRecord,
    qemu_PolyTextOutA,
    qemu_PolyTextOutW,
    qemu_RemoveFontMemResourceEx,
    qemu_RemoveFontResourceA,
    qemu_RemoveFontResourceExA,
    qemu_RemoveFontResourceExW,
    qemu_RemoveFontResourceW,
    qemu_ResetDCA,
    qemu_ResetDCW,
    qemu_RestoreDC,
    qemu_SaveDC,
    qemu_ScaleViewportExtEx,
    qemu_ScaleWindowExtEx,
    qemu_SelectObject,
    qemu_SetAbortProc,
    qemu_SetArcDirection,
    qemu_SetBkColor,
    qemu_SetBkMode,
    qemu_SetBoundsRect,
    qemu_SetColorAdjustment,
    qemu_SetColorSpace,
    qemu_SetDCBrushColor,
    qemu_SetDCPenColor,
    qemu_SetDeviceGammaRamp,
    qemu_SetDIBColorTable,
    qemu_SetDIBits,
    qemu_SetDIBitsToDevice,
    qemu_SetEnhMetaFileBits,
    qemu_SetGraphicsMode,
    qemu_SetHookFlags,
    qemu_SetICMMode,
    qemu_SetLayout,
    qemu_SetMapMode,
    qemu_SetMapperFlags,
    qemu_SetMetaFileBitsEx,
    qemu_SetMiterLimit,
    qemu_SetObjectOwner,
    qemu_SetPolyFillMode,
    qemu_SetRelAbs,
    qemu_SetROP2,
    qemu_SetStretchBltMode,
    qemu_SetTextAlign,
    qemu_SetTextCharacterExtra,
    qemu_SetTextColor,
    qemu_SetTextJustification,
    qemu_SetViewportExtEx,
    qemu_SetViewportOrgEx,
    qemu_SetVirtualResolution,
    qemu_SetWindowExtEx,
    qemu_SetWindowOrgEx,
    qemu_SetWinMetaFileBits,
    qemu_SetWorldTransform,
    qemu_StartDocA,
    qemu_StartDocW,
    qemu_StartPage,
    qemu_StretchDIBits,
    qemu_TextOutA,
    qemu_TextOutW,
    qemu_TranslateCharsetInfo,
    qemu_UnrealizeObject,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side gdi32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
