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
#include <usp10.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

struct qemu_abort_proc
{
    uint64_t guest_proc;
    uint64_t hdc;
    uint64_t error;
};

struct qemu_init_dll
{
    struct qemu_syscall super;
    uint64_t abort_proc_guest_wrapper;
};

#ifdef QEMU_DLL_GUEST

static BOOL __fastcall abort_proc_guest_wrapper(struct qemu_abort_proc *data)
{
    ABORTPROC proc = (ABORTPROC)(ULONG_PTR)data->guest_proc;
    return proc((HDC)(ULONG_PTR)data->hdc, data->error);
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        struct qemu_init_dll call;
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.abort_proc_guest_wrapper = (ULONG_PTR)abort_proc_guest_wrapper;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

#else

#include <wine/debug.h>
#include <assert.h>

#include "callback_helper_impl.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);

const struct qemu_ops *qemu_ops;

static struct callback_entry_table *abort_proc_wrappers;
static unsigned int abort_proc_wrapper_count;
static uint64_t abort_proc_guest_wrapper;

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_init_dll *c = (struct qemu_init_dll *)call;
    abort_proc_guest_wrapper = c->abort_proc_guest_wrapper;
}

static const syscall_handler dll_functions[] =
{
    qemu_AbortDoc,
    qemu_AbortPath,
    qemu_AddFontMemResourceEx,
    qemu_AddFontResourceA,
    qemu_AddFontResourceExA,
    qemu_AddFontResourceExW,
    qemu_AddFontResourceW,
    qemu_AngleArc,
    qemu_AnimatePalette,
    qemu_Arc,
    qemu_ArcTo,
    qemu_BeginPath,
    qemu_BitBlt,
    qemu_CancelDC,
    qemu_ChoosePixelFormat,
    qemu_Chord,
    qemu_CloseEnhMetaFile,
    qemu_CloseFigure,
    qemu_CloseMetaFile,
    qemu_CombineRgn,
    qemu_CombineTransform,
    qemu_CopyEnhMetaFileA,
    qemu_CopyEnhMetaFileW,
    qemu_CopyMetaFileA,
    qemu_CopyMetaFileW,
    qemu_CreateBitmap,
    qemu_CreateBitmapIndirect,
    qemu_CreateBrushIndirect,
    qemu_CreateColorSpaceA,
    qemu_CreateColorSpaceW,
    qemu_CreateCompatibleBitmap,
    qemu_CreateCompatibleDC,
    qemu_CreateDCA,
    qemu_CreateDCW,
    qemu_CreateDIBitmap,
    qemu_CreateDIBPatternBrush,
    qemu_CreateDIBPatternBrushPt,
    qemu_CreateDIBSection,
    qemu_CreateDiscardableBitmap,
    qemu_CreateEllipticRgn,
    qemu_CreateEllipticRgnIndirect,
    qemu_CreateEnhMetaFileA,
    qemu_CreateEnhMetaFileW,
    qemu_CreateFontA,
    qemu_CreateFontIndirectA,
    qemu_CreateFontIndirectExA,
    qemu_CreateFontIndirectExW,
    qemu_CreateFontIndirectW,
    qemu_CreateFontW,
    qemu_CreateHalftonePalette,
    qemu_CreateHatchBrush,
    qemu_CreateICA,
    qemu_CreateICW,
    qemu_CreateMetaFileA,
    qemu_CreateMetaFileW,
    qemu_CreatePalette,
    qemu_CreatePatternBrush,
    qemu_CreatePen,
    qemu_CreatePenIndirect,
    qemu_CreatePolygonRgn,
    qemu_CreatePolyPolygonRgn,
    qemu_CreateRectRgn,
    qemu_CreateRectRgnIndirect,
    qemu_CreateRoundRectRgn,
    qemu_CreateScalableFontResourceA,
    qemu_CreateScalableFontResourceW,
    qemu_CreateSolidBrush,
    qemu_D3DKMTCreateDCFromMemory,
    qemu_D3DKMTDestroyDCFromMemory,
    qemu_D3DKMTEscape,
    qemu_D3DKMTOpenAdapterFromHdc,
    qemu_DeleteColorSpace,
    qemu_DeleteDC,
    qemu_DeleteEnhMetaFile,
    qemu_DeleteMetaFile,
    qemu_DeleteObject,
    qemu_DescribePixelFormat,
    qemu_DPtoLP,
    qemu_DrawEscape,
    qemu_Ellipse,
    qemu_EnableEUDC,
    qemu_EndDoc,
    qemu_EndPage,
    qemu_EndPath,
    qemu_EnumEnhMetaFile,
    qemu_EnumFontFamiliesA,
    qemu_EnumFontFamiliesExA,
    qemu_EnumFontFamiliesExW,
    qemu_EnumFontFamiliesW,
    qemu_EnumFontsA,
    qemu_EnumFontsW,
    qemu_EnumICMProfilesA,
    qemu_EnumICMProfilesW,
    qemu_EnumMetaFile,
    qemu_EnumObjects,
    qemu_EqualRgn,
    qemu_Escape,
    qemu_ExcludeClipRect,
    qemu_ExtCreatePen,
    qemu_ExtCreateRegion,
    qemu_ExtEscape,
    qemu_ExtFloodFill,
    qemu_ExtSelectClipRgn,
    qemu_ExtTextOutA,
    qemu_ExtTextOutW,
    qemu_FillPath,
    qemu_FillRgn,
    qemu_FixBrushOrgEx,
    qemu_FlattenPath,
    qemu_FloodFill,
    qemu_FontIsLinked,
    qemu_FrameRgn,
    qemu_GdiAlphaBlend,
    qemu_GdiComment,
    qemu_GdiConvertToDevmodeW,
    qemu_GdiDescribePixelFormat,
    qemu_GdiDrawStream,
    qemu_GdiFlush,
    qemu_GdiGetBatchLimit,
    qemu_GdiGetCharDimensions,
    qemu_GdiGetCodePage,
    qemu_GdiGetSpoolMessage,
    qemu_GdiGradientFill,
    qemu_GdiInitializeLanguagePack,
    qemu_GdiInitSpool,
    qemu_GdiIsMetaFileDC,
    qemu_GdiIsMetaPrintDC,
    qemu_GdiIsPlayMetafileDC,
    qemu_GdiRealizationInfo,
    qemu_GdiSetBatchLimit,
    qemu_GdiSetPixelFormat,
    qemu_GdiSwapBuffers,
    qemu_GdiTransparentBlt,
    qemu_GetArcDirection,
    qemu_GetAspectRatioFilterEx,
    qemu_GetBitmapBits,
    qemu_GetBitmapDimensionEx,
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
    qemu_GetCharWidthInfo,
    qemu_GetClipBox,
    qemu_GetClipRgn,
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
    qemu_GetFontFileInfo,
    qemu_GetFontLanguageInfo,
    qemu_GetFontRealizationInfo,
    qemu_GetFontResourceInfoW,
    qemu_GetFontUnicodeRanges,
    qemu_GetGlyphIndicesA,
    qemu_GetGlyphIndicesW,
    qemu_GetGlyphOutlineA,
    qemu_GetGlyphOutlineW,
    qemu_GetGraphicsMode,
    qemu_GetICMProfileA,
    qemu_GetICMProfileW,
    qemu_GetKerningPairsA,
    qemu_GetKerningPairsW,
    qemu_GetLayout,
    qemu_GetLogColorSpaceA,
    qemu_GetLogColorSpaceW,
    qemu_GetMapMode,
    qemu_GetMetaFileA,
    qemu_GetMetaFileBitsEx,
    qemu_GetMetaFileW,
    qemu_GetMetaRgn,
    qemu_GetMiterLimit,
    qemu_GetNearestColor,
    qemu_GetNearestPaletteIndex,
    qemu_GetObject,
    qemu_GetObjectType,
    qemu_GetObject,
    qemu_GetOutlineTextMetricsA,
    qemu_GetOutlineTextMetricsW,
    qemu_GetPaletteEntries,
    qemu_GetPath,
    qemu_GetPixel,
    qemu_GetPixelFormat,
    qemu_GetPolyFillMode,
    qemu_GetRandomRgn,
    qemu_GetRasterizerCaps,
    qemu_GetRegionData,
    qemu_GetRelAbs,
    qemu_GetRgnBox,
    qemu_GetROP2,
    qemu_GetStockObject,
    qemu_GetStretchBltMode,
    qemu_GetSystemPaletteEntries,
    qemu_GetSystemPaletteUse,
    qemu_GetTextAlign,
    qemu_GetTextCharacterExtra,
    qemu_GetTextCharset,
    qemu_GetTextCharsetInfo,
    qemu_GetTextColor,
    qemu_GetTextExtentExPointA,
    qemu_GetTextExtentExPointI,
    qemu_GetTextExtentExPointW,
    qemu_GetTextExtentPoint32A,
    qemu_GetTextExtentPoint32W,
    qemu_GetTextExtentPointA,
    qemu_GetTextExtentPointI,
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
    qemu_init_dll,
    qemu_IntersectClipRect,
    qemu_InvertRgn,
    qemu_LineDDA,
    qemu_LineTo,
    qemu_LPtoDP,
    qemu_MaskBlt,
    qemu_MirrorRgn,
    qemu_ModifyWorldTransform,
    qemu_MoveToEx,
    qemu_NamedEscape,
    qemu_OffsetClipRgn,
    qemu_OffsetRgn,
    qemu_OffsetViewportOrgEx,
    qemu_OffsetWindowOrgEx,
    qemu_PaintRgn,
    qemu_PatBlt,
    qemu_PathToRegion,
    qemu_Pie,
    qemu_PlayEnhMetaFile,
    qemu_PlayEnhMetaFileRecord,
    qemu_PlayMetaFile,
    qemu_PlayMetaFileRecord,
    qemu_PlgBlt,
    qemu_PolyBezier,
    qemu_PolyBezierTo,
    qemu_PolyDraw,
    qemu_Polygon,
    qemu_Polyline,
    qemu_PolylineTo,
    qemu_PolyPolygon,
    qemu_PolyPolyline,
    qemu_PolyTextOutA,
    qemu_PolyTextOutW,
    qemu_PtInRegion,
    qemu_PtVisible,
    qemu_RealizePalette,
    qemu_Rectangle,
    qemu_RectInRegion,
    qemu_RectVisible,
    qemu_RemoveFontMemResourceEx,
    qemu_RemoveFontResourceA,
    qemu_RemoveFontResourceExA,
    qemu_RemoveFontResourceExW,
    qemu_RemoveFontResourceW,
    qemu_ResetDCA,
    qemu_ResetDCW,
    qemu_ResizePalette,
    qemu_RestoreDC,
    qemu_RoundRect,
    qemu_SaveDC,
    qemu_ScaleViewportExtEx,
    qemu_ScaleWindowExtEx,
    qemu_ScriptApplyDigitSubstitution,
    qemu_ScriptApplyLogicalWidth,
    qemu_ScriptBreak,
    qemu_ScriptCacheGetHeight,
    qemu_ScriptCPtoX,
    qemu_ScriptFreeCache,
    qemu_ScriptGetCMap,
    qemu_ScriptGetFontFeatureTags,
    qemu_ScriptGetFontLanguageTags,
    qemu_ScriptGetFontProperties,
    qemu_ScriptGetFontScriptTags,
    qemu_ScriptGetGlyphABCWidth,
    qemu_ScriptGetLogicalWidths,
    qemu_ScriptGetProperties,
    qemu_ScriptIsComplex,
    qemu_ScriptItemize,
    qemu_ScriptItemizeOpenType,
    qemu_ScriptJustify,
    qemu_ScriptLayout,
    qemu_ScriptPlace,
    qemu_ScriptPlaceOpenType,
    qemu_ScriptRecordDigitSubstitution,
    qemu_ScriptShape,
    qemu_ScriptShapeOpenType,
    qemu_ScriptString_pcOutChars,
    qemu_ScriptString_pLogAttr,
    qemu_ScriptString_pSize,
    qemu_ScriptStringAnalyse,
    qemu_ScriptStringCPtoX,
    qemu_ScriptStringFree,
    qemu_ScriptStringGetLogicalWidths,
    qemu_ScriptStringGetOrder,
    qemu_ScriptStringOut,
    qemu_ScriptStringValidate,
    qemu_ScriptStringXtoCP,
    qemu_ScriptTextOut,
    qemu_ScriptXtoCP,
    qemu_SelectClipPath,
    qemu_SelectClipRgn,
    qemu_SelectObject,
    qemu_SelectPalette,
    qemu_SetAbortProc,
    qemu_SetArcDirection,
    qemu_SetBitmapBits,
    qemu_SetBitmapDimensionEx,
    qemu_SetBkColor,
    qemu_SetBkMode,
    qemu_SetBoundsRect,
    qemu_SetBrushOrgEx,
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
    qemu_SetICMProfileA,
    qemu_SetICMProfileW,
    qemu_SetLayout,
    qemu_SetMagicColors,
    qemu_SetMapMode,
    qemu_SetMapperFlags,
    qemu_SetMetaFileBitsEx,
    qemu_SetMetaRgn,
    qemu_SetMiterLimit,
    qemu_SetObjectOwner,
    qemu_SetPaletteEntries,
    qemu_SetPixel,
    qemu_SetPixelFormat,
    qemu_SetPixelV,
    qemu_SetPolyFillMode,
    qemu_SetRectRgn,
    qemu_SetRelAbs,
    qemu_SetROP2,
    qemu_SetStretchBltMode,
    qemu_SetSystemPaletteUse,
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
    qemu_StretchBlt,
    qemu_StretchDIBits,
    qemu_StrokeAndFillPath,
    qemu_StrokePath,
    qemu_SwapBuffers,
    qemu_TextOutA,
    qemu_TextOutW,
    qemu_TranslateCharsetInfo,
    qemu_UnrealizeObject,
    qemu_UpdateColors,
    qemu_UpdateICMRegKeyA,
    qemu_UpdateICMRegKeyW,
    qemu_WidenPath,
};

static BOOL WINAPI abort_proc_host_wrapper(HDC hdc, int error, struct callback_entry *wrapper)
{
    struct qemu_abort_proc call;
    BOOL ret;

    WINE_TRACE("hdc %p error %x wrapper %p\n", hdc, error, wrapper);
    call.guest_proc = wrapper->guest_proc;
    call.hdc = QEMU_H2G(hdc);
    call.error = error;

    WINE_TRACE("Calling guest abort proc 0x%lx(%p, %d).\n", (unsigned long)wrapper->guest_proc, hdc, error);
    ret = qemu_ops->qemu_execute(QEMU_G2H(abort_proc_guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest returned %x.\n", ret);

    return ret;
}

ABORTPROC abort_proc_guest_to_host(uint64_t guest_proc)
{
    struct callback_entry *entry;
    BOOL is_new;

    if (!guest_proc)
        return NULL;

    entry = callback_get(abort_proc_wrappers, guest_proc, &is_new);
    if (!entry)
    {
        WINE_FIXME("Out of guest -> host abort proc wrappers.\n");
        assert(0);
    }
    if (is_new)
    {
        WINE_TRACE("Creating host ABORTPROC %p for guest func 0x%lx.\n",
                entry, (unsigned long)guest_proc);
    }
    return (ABORTPROC)entry;
}

HRESULT (WINAPI *pScriptFreeCache)(SCRIPT_CACHE *psc);
HRESULT (WINAPI *pScriptGetProperties)(const SCRIPT_PROPERTIES ***props, int *num);
HRESULT (WINAPI *pScriptGetFontProperties)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_FONTPROPERTIES *sfp);
HRESULT (WINAPI *pScriptRecordDigitSubstitution)(LCID locale, SCRIPT_DIGITSUBSTITUTE *sds);
HRESULT (WINAPI *pScriptApplyDigitSubstitution)(const SCRIPT_DIGITSUBSTITUTE *sds, SCRIPT_CONTROL *sc,
        SCRIPT_STATE *ss);
HRESULT (WINAPI *pScriptItemizeOpenType)(const WCHAR *pwcInChars, int cInChars, int cMaxItems,
        const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems,
        OPENTYPE_TAG *pScriptTags, int *pcItems);
HRESULT (WINAPI *pScriptItemize)(const WCHAR *pwcInChars, int cInChars, int cMaxItems,
        const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems, int *pcItems);
HRESULT (WINAPI *pScriptStringAnalyse)(HDC hdc, const void *pString, int cString, int cGlyphs,
        int iCharset, DWORD dwFlags, int iReqWidth, SCRIPT_CONTROL *psControl, SCRIPT_STATE *psState,
        const int *piDx, SCRIPT_TABDEF *pTabdef, const BYTE *pbInClass, SCRIPT_STRING_ANALYSIS *pssa);
HRESULT (WINAPI *pScriptStringOut)(SCRIPT_STRING_ANALYSIS ssa, int iX, int iY, UINT uOptions, const RECT *prc,
        int iMinSel, int iMaxSel, BOOL fDisabled);
HRESULT (WINAPI *pScriptStringCPtoX)(SCRIPT_STRING_ANALYSIS ssa, int icp, BOOL fTrailing, int* pX);
HRESULT (WINAPI *pScriptStringXtoCP)(SCRIPT_STRING_ANALYSIS ssa, int iX, int* piCh, int* piTrailing);
HRESULT (WINAPI *pScriptStringFree)(SCRIPT_STRING_ANALYSIS *pssa);
HRESULT (WINAPI *pScriptCPtoX)(int iCP, BOOL fTrailing, int cChars, int cGlyphs, const WORD *pwLogClust,
        const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piX);
HRESULT (WINAPI *pScriptXtoCP)(int iX, int cChars, int cGlyphs, const WORD *pwLogClust,
        const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piCP, int *piTrailing);
HRESULT (WINAPI *pScriptBreak)(const WCHAR *chars, int count, const SCRIPT_ANALYSIS *sa, SCRIPT_LOGATTR *la);
HRESULT (WINAPI *pScriptIsComplex)(const WCHAR *chars, int len, DWORD flag);
HRESULT (WINAPI *pScriptShapeOpenType)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
        OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges,
        const WCHAR *pwcChars, int cChars, int cMaxGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps,
        WORD *pwOutGlyphs, SCRIPT_GLYPHPROP *pOutGlyphProps, int *pcGlyphs);
HRESULT (WINAPI *pScriptShape)(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcChars, int cChars, int cMaxGlyphs,
        SCRIPT_ANALYSIS *psa, WORD *pwOutGlyphs, WORD *pwLogClust, SCRIPT_VISATTR *psva, int *pcGlyphs);
HRESULT (WINAPI *pScriptPlaceOpenType)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
        OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges,
        const WCHAR *pwcChars, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, int cChars, const WORD *pwGlyphs,
        const SCRIPT_GLYPHPROP *pGlyphProps, int cGlyphs, int *piAdvance, GOFFSET *pGoffset, ABC *pABC);
HRESULT (WINAPI *pScriptPlace)(HDC hdc, SCRIPT_CACHE *psc, const WORD *pwGlyphs, int cGlyphs,
        const SCRIPT_VISATTR *psva, SCRIPT_ANALYSIS *psa, int *piAdvance, GOFFSET *pGoffset, ABC *pABC);
HRESULT (WINAPI *pScriptGetCMap)(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcInChars, int cChars,
        DWORD dwFlags, WORD *pwOutGlyphs);
HRESULT (WINAPI *pScriptTextOut)(const HDC hdc, SCRIPT_CACHE *psc, int x, int y, UINT fuOptions,
        const RECT *lprc, const SCRIPT_ANALYSIS *psa, const WCHAR *pwcReserved, int iReserved, const WORD *pwGlyphs,
        int cGlyphs, const int *piAdvance, const int *piJustify, const GOFFSET *pGoffset);
HRESULT (WINAPI *pScriptCacheGetHeight)(HDC hdc, SCRIPT_CACHE *psc, LONG *height);
HRESULT (WINAPI *pScriptGetGlyphABCWidth)(HDC hdc, SCRIPT_CACHE *psc, WORD glyph, ABC *abc);
HRESULT (WINAPI *pScriptLayout)(int runs, const BYTE *level, int *vistolog, int *logtovis);
HRESULT (WINAPI *pScriptStringGetLogicalWidths)(SCRIPT_STRING_ANALYSIS ssa, int *piDx);
HRESULT (WINAPI *pScriptStringValidate)(SCRIPT_STRING_ANALYSIS ssa);
const SIZE * (WINAPI *pScriptString_pSize)(SCRIPT_STRING_ANALYSIS ssa);
const SCRIPT_LOGATTR * (WINAPI *pScriptString_pLogAttr)(SCRIPT_STRING_ANALYSIS ssa);
const int * (WINAPI *pScriptString_pcOutChars)(SCRIPT_STRING_ANALYSIS ssa);
HRESULT (WINAPI *pScriptStringGetOrder)(SCRIPT_STRING_ANALYSIS ssa, UINT *order);
HRESULT (WINAPI *pScriptGetLogicalWidths)(const SCRIPT_ANALYSIS *sa, int nbchars, int nbglyphs,
        const int *advances, const WORD *log_clust, const SCRIPT_VISATTR *sva, int *widths);
HRESULT (WINAPI *pScriptApplyLogicalWidth)(const int *dx, int num_chars, int num_glyphs, const WORD *log_clust,
        const SCRIPT_VISATTR *sva, const int *advance, const SCRIPT_ANALYSIS *sa, ABC *abc, int *justify);
HRESULT (WINAPI *pScriptJustify)(const SCRIPT_VISATTR *sva, const int *advance, int num_glyphs, int dx,
        int min_kashida, int *justify);
HRESULT (WINAPI *pScriptGetFontScriptTags)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, int cMaxTags,
        OPENTYPE_TAG *pScriptTags, int *pcTags);
HRESULT (WINAPI *pScriptGetFontLanguageTags)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa,
        OPENTYPE_TAG tagScript, int cMaxTags, OPENTYPE_TAG *pLangSysTags, int *pcTags);
HRESULT (WINAPI *pScriptGetFontFeatureTags)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa,
        OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int cMaxTags, OPENTYPE_TAG *pFeatureTags, int *pcTags);

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE gdi32;

    WINE_TRACE("Loading host-side gdi32 wrapper.\n");
    gdi32 = GetModuleHandleA("gdi32");

    abort_proc_wrapper_count = 16;
    if (!callback_alloc_table(&abort_proc_wrappers, abort_proc_wrapper_count, sizeof(struct callback_entry),
            abort_proc_host_wrapper, 2))
    {
        WINE_ERR("Failed to allocate memory for abort proc wrappers.\n");
        return NULL;
    }

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    pScriptFreeCache = (void *)GetProcAddress(gdi32, "ScriptFreeCache");
    if (!pScriptFreeCache)
        WINE_ERR("Could not find ScriptFreeCache in gdi32.dll\n");

    pScriptGetProperties = (void *)GetProcAddress(gdi32, "ScriptGetProperties");
    if (!pScriptGetProperties)
        WINE_ERR("Could not find ScriptGetProperties in gdi32.dll\n");

    pScriptGetFontProperties = (void *)GetProcAddress(gdi32, "ScriptGetFontProperties");
    if (!pScriptGetFontProperties)
        WINE_ERR("Could not find ScriptGetFontProperties in gdi32.dll\n");

    pScriptRecordDigitSubstitution = (void *)GetProcAddress(gdi32, "ScriptRecordDigitSubstitution");
    if (!pScriptRecordDigitSubstitution)
        WINE_ERR("Could not find ScriptRecordDigitSubstitution in gdi32.dll\n");

    pScriptApplyDigitSubstitution = (void *)GetProcAddress(gdi32, "ScriptApplyDigitSubstitution");
    if (!pScriptApplyDigitSubstitution)
        WINE_ERR("Could not find ScriptApplyDigitSubstitution in gdi32.dll\n");

    pScriptItemizeOpenType = (void *)GetProcAddress(gdi32, "ScriptItemizeOpenType");
    if (!pScriptItemizeOpenType)
        WINE_ERR("Could not find ScriptItemizeOpenType in gdi32.dll\n");

    pScriptItemize = (void *)GetProcAddress(gdi32, "ScriptItemize");
    if (!pScriptItemize)
        WINE_ERR("Could not find ScriptItemize in gdi32.dll\n");

    pScriptStringAnalyse = (void *)GetProcAddress(gdi32, "ScriptStringAnalyse");
    if (!pScriptStringAnalyse)
        WINE_ERR("Could not find ScriptStringAnalyse in gdi32.dll\n");

    pScriptStringOut = (void *)GetProcAddress(gdi32, "ScriptStringOut");
    if (!pScriptStringOut)
        WINE_ERR("Could not find ScriptStringOut in gdi32.dll\n");

    pScriptStringCPtoX = (void *)GetProcAddress(gdi32, "ScriptStringCPtoX");
    if (!pScriptStringCPtoX)
        WINE_ERR("Could not find ScriptStringCPtoX in gdi32.dll\n");

    pScriptStringXtoCP = (void *)GetProcAddress(gdi32, "ScriptStringXtoCP");
    if (!pScriptStringXtoCP)
        WINE_ERR("Could not find ScriptStringXtoCP in gdi32.dll\n");

    pScriptStringFree = (void *)GetProcAddress(gdi32, "ScriptStringFree");
    if (!pScriptStringFree)
        WINE_ERR("Could not find ScriptStringFree in gdi32.dll\n");

    pScriptCPtoX = (void *)GetProcAddress(gdi32, "ScriptCPtoX");
    if (!pScriptCPtoX)
        WINE_ERR("Could not find ScriptCPtoX in gdi32.dll\n");

    pScriptXtoCP = (void *)GetProcAddress(gdi32, "ScriptXtoCP");
    if (!pScriptXtoCP)
        WINE_ERR("Could not find ScriptXtoCP in gdi32.dll\n");

    pScriptBreak = (void *)GetProcAddress(gdi32, "ScriptBreak");
    if (!pScriptBreak)
        WINE_ERR("Could not find ScriptBreak in gdi32.dll\n");

    pScriptIsComplex = (void *)GetProcAddress(gdi32, "ScriptIsComplex");
    if (!pScriptIsComplex)
        WINE_ERR("Could not find ScriptIsComplex in gdi32.dll\n");

    pScriptShapeOpenType = (void *)GetProcAddress(gdi32, "ScriptShapeOpenType");
    if (!pScriptShapeOpenType)
        WINE_ERR("Could not find ScriptShapeOpenType in gdi32.dll\n");

    pScriptShape = (void *)GetProcAddress(gdi32, "ScriptShape");
    if (!pScriptShape)
        WINE_ERR("Could not find ScriptShape in gdi32.dll\n");

    pScriptPlaceOpenType = (void *)GetProcAddress(gdi32, "ScriptPlaceOpenType");
    if (!pScriptPlaceOpenType)
        WINE_ERR("Could not find ScriptPlaceOpenType in gdi32.dll\n");

    pScriptPlace = (void *)GetProcAddress(gdi32, "ScriptPlace");
    if (!pScriptPlace)
        WINE_ERR("Could not find ScriptPlace in gdi32.dll\n");

    pScriptGetCMap = (void *)GetProcAddress(gdi32, "ScriptGetCMap");
    if (!pScriptGetCMap)
        WINE_ERR("Could not find ScriptGetCMap in gdi32.dll\n");

    pScriptTextOut = (void *)GetProcAddress(gdi32, "ScriptTextOut");
    if (!pScriptTextOut)
        WINE_ERR("Could not find ScriptTextOut in gdi32.dll\n");

    pScriptCacheGetHeight = (void *)GetProcAddress(gdi32, "ScriptCacheGetHeight");
    if (!pScriptCacheGetHeight)
        WINE_ERR("Could not find ScriptCacheGetHeight in gdi32.dll\n");

    pScriptGetGlyphABCWidth = (void *)GetProcAddress(gdi32, "ScriptGetGlyphABCWidth");
    if (!pScriptGetGlyphABCWidth)
        WINE_ERR("Could not find ScriptGetGlyphABCWidth in gdi32.dll\n");

    pScriptLayout = (void *)GetProcAddress(gdi32, "ScriptLayout");
    if (!pScriptLayout)
        WINE_ERR("Could not find ScriptLayout in gdi32.dll\n");

    pScriptStringGetLogicalWidths = (void *)GetProcAddress(gdi32, "ScriptStringGetLogicalWidths");
    if (!pScriptStringGetLogicalWidths)
        WINE_ERR("Could not find ScriptStringGetLogicalWidths in gdi32.dll\n");

    pScriptStringValidate = (void *)GetProcAddress(gdi32, "ScriptStringValidate");
    if (!pScriptStringValidate)
        WINE_ERR("Could not find ScriptStringValidate in gdi32.dll\n");

    pScriptStringGetOrder = (void *)GetProcAddress(gdi32, "ScriptStringGetOrder");
    if (!pScriptStringGetOrder)
        WINE_ERR("Could not find ScriptStringGetOrder in gdi32.dll\n");

    pScriptGetLogicalWidths = (void *)GetProcAddress(gdi32, "ScriptGetLogicalWidths");
    if (!pScriptGetLogicalWidths)
        WINE_ERR("Could not find ScriptGetLogicalWidths in gdi32.dll\n");

    pScriptApplyLogicalWidth = (void *)GetProcAddress(gdi32, "ScriptApplyLogicalWidth");
    if (!pScriptApplyLogicalWidth)
        WINE_ERR("Could not find ScriptApplyLogicalWidth in gdi32.dll\n");

    pScriptJustify = (void *)GetProcAddress(gdi32, "ScriptJustify");
    if (!pScriptJustify)
        WINE_ERR("Could not find ScriptJustify in gdi32.dll\n");

    pScriptGetFontScriptTags = (void *)GetProcAddress(gdi32, "ScriptGetFontScriptTags");
    if (!pScriptGetFontScriptTags)
        WINE_ERR("Could not find ScriptGetFontScriptTags in gdi32.dll\n");

    pScriptGetFontLanguageTags = (void *)GetProcAddress(gdi32, "ScriptGetFontLanguageTags");
    if (!pScriptGetFontLanguageTags)
        WINE_ERR("Could not find ScriptGetFontLanguageTags in gdi32.dll\n");

    pScriptGetFontFeatureTags = (void *)GetProcAddress(gdi32, "ScriptGetFontFeatureTags");
    if (!pScriptGetFontFeatureTags)
        WINE_ERR("Could not find ScriptGetFontFeatureTags in gdi32.dll\n");
    return dll_functions;
}

#endif
