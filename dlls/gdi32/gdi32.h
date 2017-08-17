#ifndef GDI32_H
#define GDI32_H

#include <stdlib.h>

enum gdi32_calls
{
    CALL_ABORTDOC = 0,
    CALL_ADDFONTMEMRESOURCEEX,
    CALL_ADDFONTRESOURCEA,
    CALL_ADDFONTRESOURCEEXA,
    CALL_ADDFONTRESOURCEEXW,
    CALL_ADDFONTRESOURCEW,
    CALL_ANGLEARC,
    CALL_ANIMATEPALETTE,
    CALL_ARC,
    CALL_ARCTO,
    CALL_BITBLT,
    CALL_CANCELDC,
    CALL_CHOOSEPIXELFORMAT,
    CALL_CHORD,
    CALL_COMBINETRANSFORM,
    CALL_COPYENHMETAFILEA,
    CALL_COPYENHMETAFILEW,
    CALL_COPYMETAFILEA,
    CALL_COPYMETAFILEW,
    CALL_CREATEBITMAP,
    CALL_CREATEBITMAPINDIRECT,
    CALL_CREATEBRUSHINDIRECT,
    CALL_CREATECOLORSPACEA,
    CALL_CREATECOLORSPACEW,
    CALL_CREATECOMPATIBLEBITMAP,
    CALL_CREATECOMPATIBLEDC,
    CALL_CREATEDCA,
    CALL_CREATEDCW,
    CALL_CREATEDIBITMAP,
    CALL_CREATEDIBPATTERNBRUSH,
    CALL_CREATEDIBPATTERNBRUSHPT,
    CALL_CREATEDIBSECTION,
    CALL_CREATEDISCARDABLEBITMAP,
    CALL_CREATEFONTA,
    CALL_CREATEFONTINDIRECTA,
    CALL_CREATEFONTINDIRECTEXA,
    CALL_CREATEFONTINDIRECTEXW,
    CALL_CREATEFONTINDIRECTW,
    CALL_CREATEFONTW,
    CALL_CREATEHALFTONEPALETTE,
    CALL_CREATEHATCHBRUSH,
    CALL_CREATEICA,
    CALL_CREATEICW,
    CALL_CREATEPALETTE,
    CALL_CREATEPATTERNBRUSH,
    CALL_CREATESCALABLEFONTRESOURCEA,
    CALL_CREATESCALABLEFONTRESOURCEW,
    CALL_CREATESOLIDBRUSH,
    CALL_D3DKMTCREATEDCFROMMEMORY,
    CALL_D3DKMTDESTROYDCFROMMEMORY,
    CALL_D3DKMTESCAPE,
    CALL_D3DKMTOPENADAPTERFROMHDC,
    CALL_DELETECOLORSPACE,
    CALL_DELETEDC,
    CALL_DELETEENHMETAFILE,
    CALL_DELETEMETAFILE,
    CALL_DELETEOBJECT,
    CALL_DESCRIBEPIXELFORMAT,
    CALL_DPTOLP,
    CALL_DRAWESCAPE,
    CALL_ELLIPSE,
    CALL_ENABLEEUDC,
    CALL_ENDDOC,
    CALL_ENDPAGE,
    CALL_ENUMENHMETAFILE,
    CALL_ENUMFONTFAMILIESA,
    CALL_ENUMFONTFAMILIESEXA,
    CALL_ENUMFONTFAMILIESEXW,
    CALL_ENUMFONTFAMILIESW,
    CALL_ENUMFONTSA,
    CALL_ENUMFONTSW,
    CALL_ENUMICMPROFILESA,
    CALL_ENUMICMPROFILESW,
    CALL_ENUMMETAFILE,
    CALL_ENUMOBJECTS,
    CALL_ESCAPE,
    CALL_EXCLUDECLIPRECT,
    CALL_EXTESCAPE,
    CALL_EXTFLOODFILL,
    CALL_EXTSELECTCLIPRGN,
    CALL_EXTTEXTOUTA,
    CALL_EXTTEXTOUTW,
    CALL_FILLRGN,
    CALL_FIXBRUSHORGEX,
    CALL_FLOODFILL,
    CALL_FONTISLINKED,
    CALL_FRAMERGN,
    CALL_GDIALPHABLEND,
    CALL_GDICOMMENT,
    CALL_GDICONVERTTODEVMODEW,
    CALL_GDIDESCRIBEPIXELFORMAT,
    CALL_GDIDRAWSTREAM,
    CALL_GDIFLUSH,
    CALL_GDIGETBATCHLIMIT,
    CALL_GDIGETCHARDIMENSIONS,
    CALL_GDIGETCODEPAGE,
    CALL_GDIGETSPOOLMESSAGE,
    CALL_GDIGRADIENTFILL,
    CALL_GDIINITIALIZELANGUAGEPACK,
    CALL_GDIINITSPOOL,
    CALL_GDIISMETAFILEDC,
    CALL_GDIISMETAPRINTDC,
    CALL_GDIISPLAYMETAFILEDC,
    CALL_GDISETBATCHLIMIT,
    CALL_GDISETPIXELFORMAT,
    CALL_GDISWAPBUFFERS,
    CALL_GDITRANSPARENTBLT,
    CALL_GETARCDIRECTION,
    CALL_GETASPECTRATIOFILTEREX,
    CALL_GETBITMAPBITS,
    CALL_GETBITMAPDIMENSIONEX,
    CALL_GETBKCOLOR,
    CALL_GETBKMODE,
    CALL_GETBOUNDSRECT,
    CALL_GETBRUSHORGEX,
    CALL_GETCHARABCWIDTHSA,
    CALL_GETCHARABCWIDTHSFLOATA,
    CALL_GETCHARABCWIDTHSFLOATW,
    CALL_GETCHARABCWIDTHSI,
    CALL_GETCHARABCWIDTHSW,
    CALL_GETCHARACTERPLACEMENTA,
    CALL_GETCHARACTERPLACEMENTW,
    CALL_GETCHARWIDTH32A,
    CALL_GETCHARWIDTH32W,
    CALL_GETCHARWIDTHFLOATA,
    CALL_GETCHARWIDTHFLOATW,
    CALL_GETCHARWIDTHI,
    CALL_GETCLIPBOX,
    CALL_GETCLIPRGN,
    CALL_GETCOLORADJUSTMENT,
    CALL_GETCOLORSPACE,
    CALL_GETCURRENTOBJECT,
    CALL_GETCURRENTPOSITIONEX,
    CALL_GETDCBRUSHCOLOR,
    CALL_GETDCORGEX,
    CALL_GETDCPENCOLOR,
    CALL_GETDEVICECAPS,
    CALL_GETDEVICEGAMMARAMP,
    CALL_GETDIBCOLORTABLE,
    CALL_GETDIBITS,
    CALL_GETENHMETAFILEA,
    CALL_GETENHMETAFILEBITS,
    CALL_GETENHMETAFILEDESCRIPTIONA,
    CALL_GETENHMETAFILEDESCRIPTIONW,
    CALL_GETENHMETAFILEHEADER,
    CALL_GETENHMETAFILEPALETTEENTRIES,
    CALL_GETENHMETAFILEW,
    CALL_GETFONTDATA,
    CALL_GETFONTLANGUAGEINFO,
    CALL_GETFONTRESOURCEINFOW,
    CALL_GETFONTUNICODERANGES,
    CALL_GETGLYPHINDICESA,
    CALL_GETGLYPHINDICESW,
    CALL_GETGLYPHOUTLINEA,
    CALL_GETGLYPHOUTLINEW,
    CALL_GETGRAPHICSMODE,
    CALL_GETICMPROFILEA,
    CALL_GETICMPROFILEW,
    CALL_GETKERNINGPAIRSA,
    CALL_GETKERNINGPAIRSW,
    CALL_GETLAYOUT,
    CALL_GETLOGCOLORSPACEA,
    CALL_GETLOGCOLORSPACEW,
    CALL_GETMAPMODE,
    CALL_GETMETAFILEA,
    CALL_GETMETAFILEBITSEX,
    CALL_GETMETAFILEW,
    CALL_GETMETARGN,
    CALL_GETMITERLIMIT,
    CALL_GETNEARESTCOLOR,
    CALL_GETNEARESTPALETTEINDEX,
    CALL_GETOBJECTA,
    CALL_GETOBJECTTYPE,
    CALL_GETOBJECTW,
    CALL_GETOUTLINETEXTMETRICSA,
    CALL_GETOUTLINETEXTMETRICSW,
    CALL_GETPALETTEENTRIES,
    CALL_GETPIXEL,
    CALL_GETPIXELFORMAT,
    CALL_GETPOLYFILLMODE,
    CALL_GETRANDOMRGN,
    CALL_GETRELABS,
    CALL_GETROP2,
    CALL_GETSTOCKOBJECT,
    CALL_GETSTRETCHBLTMODE,
    CALL_GETSYSTEMPALETTEENTRIES,
    CALL_GETSYSTEMPALETTEUSE,
    CALL_GETTEXTALIGN,
    CALL_GETTEXTCHARACTEREXTRA,
    CALL_GETTEXTCOLOR,
    CALL_GETTEXTEXTENTEXPOINTA,
    CALL_GETTEXTEXTENTEXPOINTW,
    CALL_GETTEXTEXTENTPOINT32A,
    CALL_GETTEXTEXTENTPOINT32W,
    CALL_GETTEXTEXTENTPOINTA,
    CALL_GETTEXTEXTENTPOINTW,
    CALL_GETTEXTFACEA,
    CALL_GETTEXTFACEW,
    CALL_GETTEXTMETRICSA,
    CALL_GETTEXTMETRICSW,
    CALL_GETTRANSFORM,
    CALL_GETVIEWPORTEXTEX,
    CALL_GETVIEWPORTORGEX,
    CALL_GETWINDOWEXTEX,
    CALL_GETWINDOWORGEX,
    CALL_GETWINMETAFILEBITS,
    CALL_GETWORLDTRANSFORM,
    CALL_INTERSECTCLIPRECT,
    CALL_INVERTRGN,
    CALL_LINEDDA,
    CALL_LINETO,
    CALL_LPTODP,
    CALL_MASKBLT,
    CALL_MODIFYWORLDTRANSFORM,
    CALL_MOVETOEX,
    CALL_NAMEDESCAPE,
    CALL_OFFSETCLIPRGN,
    CALL_OFFSETVIEWPORTORGEX,
    CALL_OFFSETWINDOWORGEX,
    CALL_PAINTRGN,
    CALL_PATBLT,
    CALL_PIE,
    CALL_PLAYENHMETAFILE,
    CALL_PLAYENHMETAFILERECORD,
    CALL_PLAYMETAFILE,
    CALL_PLAYMETAFILERECORD,
    CALL_PLGBLT,
    CALL_POLYBEZIER,
    CALL_POLYBEZIERTO,
    CALL_POLYDRAW,
    CALL_POLYGON,
    CALL_POLYLINE,
    CALL_POLYLINETO,
    CALL_POLYPOLYGON,
    CALL_POLYPOLYLINE,
    CALL_POLYTEXTOUTA,
    CALL_POLYTEXTOUTW,
    CALL_PTVISIBLE,
    CALL_REALIZEPALETTE,
    CALL_RECTANGLE,
    CALL_RECTVISIBLE,
    CALL_REMOVEFONTMEMRESOURCEEX,
    CALL_REMOVEFONTRESOURCEA,
    CALL_REMOVEFONTRESOURCEEXA,
    CALL_REMOVEFONTRESOURCEEXW,
    CALL_REMOVEFONTRESOURCEW,
    CALL_RESETDCA,
    CALL_RESETDCW,
    CALL_RESIZEPALETTE,
    CALL_RESTOREDC,
    CALL_ROUNDRECT,
    CALL_SAVEDC,
    CALL_SCALEVIEWPORTEXTEX,
    CALL_SCALEWINDOWEXTEX,
    CALL_SELECTCLIPRGN,
    CALL_SELECTOBJECT,
    CALL_SELECTPALETTE,
    CALL_SETABORTPROC,
    CALL_SETARCDIRECTION,
    CALL_SETBITMAPBITS,
    CALL_SETBITMAPDIMENSIONEX,
    CALL_SETBKCOLOR,
    CALL_SETBKMODE,
    CALL_SETBOUNDSRECT,
    CALL_SETBRUSHORGEX,
    CALL_SETCOLORADJUSTMENT,
    CALL_SETCOLORSPACE,
    CALL_SETDCBRUSHCOLOR,
    CALL_SETDCPENCOLOR,
    CALL_SETDEVICEGAMMARAMP,
    CALL_SETDIBCOLORTABLE,
    CALL_SETDIBITS,
    CALL_SETDIBITSTODEVICE,
    CALL_SETENHMETAFILEBITS,
    CALL_SETGRAPHICSMODE,
    CALL_SETHOOKFLAGS,
    CALL_SETICMMODE,
    CALL_SETICMPROFILEA,
    CALL_SETICMPROFILEW,
    CALL_SETLAYOUT,
    CALL_SETMAGICCOLORS,
    CALL_SETMAPMODE,
    CALL_SETMAPPERFLAGS,
    CALL_SETMETAFILEBITSEX,
    CALL_SETMETARGN,
    CALL_SETMITERLIMIT,
    CALL_SETOBJECTOWNER,
    CALL_SETPALETTEENTRIES,
    CALL_SETPIXEL,
    CALL_SETPIXELFORMAT,
    CALL_SETPIXELV,
    CALL_SETPOLYFILLMODE,
    CALL_SETRELABS,
    CALL_SETROP2,
    CALL_SETSTRETCHBLTMODE,
    CALL_SETSYSTEMPALETTEUSE,
    CALL_SETTEXTALIGN,
    CALL_SETTEXTCHARACTEREXTRA,
    CALL_SETTEXTCOLOR,
    CALL_SETTEXTJUSTIFICATION,
    CALL_SETVIEWPORTEXTEX,
    CALL_SETVIEWPORTORGEX,
    CALL_SETVIRTUALRESOLUTION,
    CALL_SETWINDOWEXTEX,
    CALL_SETWINDOWORGEX,
    CALL_SETWINMETAFILEBITS,
    CALL_SETWORLDTRANSFORM,
    CALL_STARTDOCA,
    CALL_STARTDOCW,
    CALL_STARTPAGE,
    CALL_STRETCHBLT,
    CALL_STRETCHDIBITS,
    CALL_SWAPBUFFERS,
    CALL_TEXTOUTA,
    CALL_TEXTOUTW,
    CALL_TRANSLATECHARSETINFO,
    CALL_UNREALIZEOBJECT,
    CALL_UPDATECOLORS,
    CALL_UPDATEICMREGKEYA,
    CALL_UPDATEICMREGKEYW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_AbortDoc(struct qemu_syscall *call);
void qemu_AddFontMemResourceEx(struct qemu_syscall *call);
void qemu_AddFontResourceA(struct qemu_syscall *call);
void qemu_AddFontResourceExA(struct qemu_syscall *call);
void qemu_AddFontResourceExW(struct qemu_syscall *call);
void qemu_AddFontResourceW(struct qemu_syscall *call);
void qemu_AngleArc(struct qemu_syscall *call);
void qemu_AnimatePalette(struct qemu_syscall *call);
void qemu_Arc(struct qemu_syscall *call);
void qemu_ArcTo(struct qemu_syscall *call);
void qemu_BitBlt(struct qemu_syscall *call);
void qemu_CancelDC(struct qemu_syscall *call);
void qemu_ChoosePixelFormat(struct qemu_syscall *call);
void qemu_Chord(struct qemu_syscall *call);
void qemu_CombineTransform(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileA(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileW(struct qemu_syscall *call);
void qemu_CopyMetaFileA(struct qemu_syscall *call);
void qemu_CopyMetaFileW(struct qemu_syscall *call);
void qemu_CreateBitmap(struct qemu_syscall *call);
void qemu_CreateBitmapIndirect(struct qemu_syscall *call);
void qemu_CreateBrushIndirect(struct qemu_syscall *call);
void qemu_CreateColorSpaceA(struct qemu_syscall *call);
void qemu_CreateColorSpaceW(struct qemu_syscall *call);
void qemu_CreateCompatibleBitmap(struct qemu_syscall *call);
void qemu_CreateCompatibleDC(struct qemu_syscall *call);
void qemu_CreateDCA(struct qemu_syscall *call);
void qemu_CreateDCW(struct qemu_syscall *call);
void qemu_CreateDIBitmap(struct qemu_syscall *call);
void qemu_CreateDIBPatternBrush(struct qemu_syscall *call);
void qemu_CreateDIBPatternBrushPt(struct qemu_syscall *call);
void qemu_CreateDIBSection(struct qemu_syscall *call);
void qemu_CreateDiscardableBitmap(struct qemu_syscall *call);
void qemu_CreateFontA(struct qemu_syscall *call);
void qemu_CreateFontIndirectA(struct qemu_syscall *call);
void qemu_CreateFontIndirectExA(struct qemu_syscall *call);
void qemu_CreateFontIndirectExW(struct qemu_syscall *call);
void qemu_CreateFontIndirectW(struct qemu_syscall *call);
void qemu_CreateFontW(struct qemu_syscall *call);
void qemu_CreateHalftonePalette(struct qemu_syscall *call);
void qemu_CreateHatchBrush(struct qemu_syscall *call);
void qemu_CreateICA(struct qemu_syscall *call);
void qemu_CreateICW(struct qemu_syscall *call);
void qemu_CreatePalette(struct qemu_syscall *call);
void qemu_CreatePatternBrush(struct qemu_syscall *call);
void qemu_CreateScalableFontResourceA(struct qemu_syscall *call);
void qemu_CreateScalableFontResourceW(struct qemu_syscall *call);
void qemu_CreateSolidBrush(struct qemu_syscall *call);
void qemu_D3DKMTCreateDCFromMemory(struct qemu_syscall *call);
void qemu_D3DKMTDestroyDCFromMemory(struct qemu_syscall *call);
void qemu_D3DKMTEscape(struct qemu_syscall *call);
void qemu_D3DKMTOpenAdapterFromHdc(struct qemu_syscall *call);
void qemu_DeleteColorSpace(struct qemu_syscall *call);
void qemu_DeleteDC(struct qemu_syscall *call);
void qemu_DeleteEnhMetaFile(struct qemu_syscall *call);
void qemu_DeleteMetaFile(struct qemu_syscall *call);
void qemu_DeleteObject(struct qemu_syscall *call);
void qemu_DescribePixelFormat(struct qemu_syscall *call);
void qemu_DPtoLP(struct qemu_syscall *call);
void qemu_DrawEscape(struct qemu_syscall *call);
void qemu_Ellipse(struct qemu_syscall *call);
void qemu_EnableEUDC(struct qemu_syscall *call);
void qemu_EndDoc(struct qemu_syscall *call);
void qemu_EndPage(struct qemu_syscall *call);
void qemu_EnumEnhMetaFile(struct qemu_syscall *call);
void qemu_EnumFontFamiliesA(struct qemu_syscall *call);
void qemu_EnumFontFamiliesExA(struct qemu_syscall *call);
void qemu_EnumFontFamiliesExW(struct qemu_syscall *call);
void qemu_EnumFontFamiliesW(struct qemu_syscall *call);
void qemu_EnumFontsA(struct qemu_syscall *call);
void qemu_EnumFontsW(struct qemu_syscall *call);
void qemu_EnumICMProfilesA(struct qemu_syscall *call);
void qemu_EnumICMProfilesW(struct qemu_syscall *call);
void qemu_EnumMetaFile(struct qemu_syscall *call);
void qemu_EnumObjects(struct qemu_syscall *call);
void qemu_Escape(struct qemu_syscall *call);
void qemu_ExcludeClipRect(struct qemu_syscall *call);
void qemu_ExtEscape(struct qemu_syscall *call);
void qemu_ExtFloodFill(struct qemu_syscall *call);
void qemu_ExtSelectClipRgn(struct qemu_syscall *call);
void qemu_ExtTextOutA(struct qemu_syscall *call);
void qemu_ExtTextOutW(struct qemu_syscall *call);
void qemu_FillRgn(struct qemu_syscall *call);
void qemu_FixBrushOrgEx(struct qemu_syscall *call);
void qemu_FloodFill(struct qemu_syscall *call);
void qemu_FontIsLinked(struct qemu_syscall *call);
void qemu_FrameRgn(struct qemu_syscall *call);
void qemu_GdiAlphaBlend(struct qemu_syscall *call);
void qemu_GdiComment(struct qemu_syscall *call);
void qemu_GdiConvertToDevmodeW(struct qemu_syscall *call);
void qemu_GdiDescribePixelFormat(struct qemu_syscall *call);
void qemu_GdiDrawStream(struct qemu_syscall *call);
void qemu_GdiFlush(struct qemu_syscall *call);
void qemu_GdiGetBatchLimit(struct qemu_syscall *call);
void qemu_GdiGetCharDimensions(struct qemu_syscall *call);
void qemu_GdiGetCodePage(struct qemu_syscall *call);
void qemu_GdiGetSpoolMessage(struct qemu_syscall *call);
void qemu_GdiGradientFill(struct qemu_syscall *call);
void qemu_GdiInitializeLanguagePack(struct qemu_syscall *call);
void qemu_GdiInitSpool(struct qemu_syscall *call);
void qemu_GdiIsMetaFileDC(struct qemu_syscall *call);
void qemu_GdiIsMetaPrintDC(struct qemu_syscall *call);
void qemu_GdiIsPlayMetafileDC(struct qemu_syscall *call);
void qemu_GdiSetBatchLimit(struct qemu_syscall *call);
void qemu_GdiSetPixelFormat(struct qemu_syscall *call);
void qemu_GdiSwapBuffers(struct qemu_syscall *call);
void qemu_GdiTransparentBlt(struct qemu_syscall *call);
void qemu_GetArcDirection(struct qemu_syscall *call);
void qemu_GetAspectRatioFilterEx(struct qemu_syscall *call);
void qemu_GetBitmapBits(struct qemu_syscall *call);
void qemu_GetBitmapDimensionEx(struct qemu_syscall *call);
void qemu_GetBkColor(struct qemu_syscall *call);
void qemu_GetBkMode(struct qemu_syscall *call);
void qemu_GetBoundsRect(struct qemu_syscall *call);
void qemu_GetBrushOrgEx(struct qemu_syscall *call);
void qemu_GetCharABCWidthsA(struct qemu_syscall *call);
void qemu_GetCharABCWidthsFloatA(struct qemu_syscall *call);
void qemu_GetCharABCWidthsFloatW(struct qemu_syscall *call);
void qemu_GetCharABCWidthsI(struct qemu_syscall *call);
void qemu_GetCharABCWidthsW(struct qemu_syscall *call);
void qemu_GetCharacterPlacementA(struct qemu_syscall *call);
void qemu_GetCharacterPlacementW(struct qemu_syscall *call);
void qemu_GetCharWidth32A(struct qemu_syscall *call);
void qemu_GetCharWidth32W(struct qemu_syscall *call);
void qemu_GetCharWidthFloatA(struct qemu_syscall *call);
void qemu_GetCharWidthFloatW(struct qemu_syscall *call);
void qemu_GetCharWidthI(struct qemu_syscall *call);
void qemu_GetClipBox(struct qemu_syscall *call);
void qemu_GetClipRgn(struct qemu_syscall *call);
void qemu_GetColorAdjustment(struct qemu_syscall *call);
void qemu_GetColorSpace(struct qemu_syscall *call);
void qemu_GetCurrentObject(struct qemu_syscall *call);
void qemu_GetCurrentPositionEx(struct qemu_syscall *call);
void qemu_GetDCBrushColor(struct qemu_syscall *call);
void qemu_GetDCOrgEx(struct qemu_syscall *call);
void qemu_GetDCPenColor(struct qemu_syscall *call);
void qemu_GetDeviceCaps(struct qemu_syscall *call);
void qemu_GetDeviceGammaRamp(struct qemu_syscall *call);
void qemu_GetDIBColorTable(struct qemu_syscall *call);
void qemu_GetDIBits(struct qemu_syscall *call);
void qemu_GetEnhMetaFileA(struct qemu_syscall *call);
void qemu_GetEnhMetaFileBits(struct qemu_syscall *call);
void qemu_GetEnhMetaFileDescriptionA(struct qemu_syscall *call);
void qemu_GetEnhMetaFileDescriptionW(struct qemu_syscall *call);
void qemu_GetEnhMetaFileHeader(struct qemu_syscall *call);
void qemu_GetEnhMetaFilePaletteEntries(struct qemu_syscall *call);
void qemu_GetEnhMetaFileW(struct qemu_syscall *call);
void qemu_GetFontData(struct qemu_syscall *call);
void qemu_GetFontLanguageInfo(struct qemu_syscall *call);
void qemu_GetFontResourceInfoW(struct qemu_syscall *call);
void qemu_GetFontUnicodeRanges(struct qemu_syscall *call);
void qemu_GetGlyphIndicesA(struct qemu_syscall *call);
void qemu_GetGlyphIndicesW(struct qemu_syscall *call);
void qemu_GetGlyphOutlineA(struct qemu_syscall *call);
void qemu_GetGlyphOutlineW(struct qemu_syscall *call);
void qemu_GetGraphicsMode(struct qemu_syscall *call);
void qemu_GetICMProfileA(struct qemu_syscall *call);
void qemu_GetICMProfileW(struct qemu_syscall *call);
void qemu_GetKerningPairsA(struct qemu_syscall *call);
void qemu_GetKerningPairsW(struct qemu_syscall *call);
void qemu_GetLayout(struct qemu_syscall *call);
void qemu_GetLogColorSpaceA(struct qemu_syscall *call);
void qemu_GetLogColorSpaceW(struct qemu_syscall *call);
void qemu_GetMapMode(struct qemu_syscall *call);
void qemu_GetMetaFileA(struct qemu_syscall *call);
void qemu_GetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_GetMetaFileW(struct qemu_syscall *call);
void qemu_GetMetaRgn(struct qemu_syscall *call);
void qemu_GetMiterLimit(struct qemu_syscall *call);
void qemu_GetNearestColor(struct qemu_syscall *call);
void qemu_GetNearestPaletteIndex(struct qemu_syscall *call);
void qemu_GetObjectA(struct qemu_syscall *call);
void qemu_GetObjectType(struct qemu_syscall *call);
void qemu_GetObjectW(struct qemu_syscall *call);
void qemu_GetOutlineTextMetricsA(struct qemu_syscall *call);
void qemu_GetOutlineTextMetricsW(struct qemu_syscall *call);
void qemu_GetPaletteEntries(struct qemu_syscall *call);
void qemu_GetPixel(struct qemu_syscall *call);
void qemu_GetPixelFormat(struct qemu_syscall *call);
void qemu_GetPolyFillMode(struct qemu_syscall *call);
void qemu_GetRandomRgn(struct qemu_syscall *call);
void qemu_GetRelAbs(struct qemu_syscall *call);
void qemu_GetROP2(struct qemu_syscall *call);
void qemu_GetStockObject(struct qemu_syscall *call);
void qemu_GetStretchBltMode(struct qemu_syscall *call);
void qemu_GetSystemPaletteEntries(struct qemu_syscall *call);
void qemu_GetSystemPaletteUse(struct qemu_syscall *call);
void qemu_GetTextAlign(struct qemu_syscall *call);
void qemu_GetTextCharacterExtra(struct qemu_syscall *call);
void qemu_GetTextColor(struct qemu_syscall *call);
void qemu_GetTextExtentExPointA(struct qemu_syscall *call);
void qemu_GetTextExtentExPointW(struct qemu_syscall *call);
void qemu_GetTextExtentPoint32A(struct qemu_syscall *call);
void qemu_GetTextExtentPoint32W(struct qemu_syscall *call);
void qemu_GetTextExtentPointA(struct qemu_syscall *call);
void qemu_GetTextExtentPointW(struct qemu_syscall *call);
void qemu_GetTextFaceA(struct qemu_syscall *call);
void qemu_GetTextFaceW(struct qemu_syscall *call);
void qemu_GetTextMetricsA(struct qemu_syscall *call);
void qemu_GetTextMetricsW(struct qemu_syscall *call);
void qemu_GetTransform(struct qemu_syscall *call);
void qemu_GetViewportExtEx(struct qemu_syscall *call);
void qemu_GetViewportOrgEx(struct qemu_syscall *call);
void qemu_GetWindowExtEx(struct qemu_syscall *call);
void qemu_GetWindowOrgEx(struct qemu_syscall *call);
void qemu_GetWinMetaFileBits(struct qemu_syscall *call);
void qemu_GetWorldTransform(struct qemu_syscall *call);
void qemu_IntersectClipRect(struct qemu_syscall *call);
void qemu_InvertRgn(struct qemu_syscall *call);
void qemu_LineDDA(struct qemu_syscall *call);
void qemu_LineTo(struct qemu_syscall *call);
void qemu_LPtoDP(struct qemu_syscall *call);
void qemu_MaskBlt(struct qemu_syscall *call);
void qemu_ModifyWorldTransform(struct qemu_syscall *call);
void qemu_MoveToEx(struct qemu_syscall *call);
void qemu_NamedEscape(struct qemu_syscall *call);
void qemu_OffsetClipRgn(struct qemu_syscall *call);
void qemu_OffsetViewportOrgEx(struct qemu_syscall *call);
void qemu_OffsetWindowOrgEx(struct qemu_syscall *call);
void qemu_PaintRgn(struct qemu_syscall *call);
void qemu_PatBlt(struct qemu_syscall *call);
void qemu_Pie(struct qemu_syscall *call);
void qemu_PlayEnhMetaFile(struct qemu_syscall *call);
void qemu_PlayEnhMetaFileRecord(struct qemu_syscall *call);
void qemu_PlayMetaFile(struct qemu_syscall *call);
void qemu_PlayMetaFileRecord(struct qemu_syscall *call);
void qemu_PlgBlt(struct qemu_syscall *call);
void qemu_PolyBezier(struct qemu_syscall *call);
void qemu_PolyBezierTo(struct qemu_syscall *call);
void qemu_PolyDraw(struct qemu_syscall *call);
void qemu_Polygon(struct qemu_syscall *call);
void qemu_Polyline(struct qemu_syscall *call);
void qemu_PolylineTo(struct qemu_syscall *call);
void qemu_PolyPolygon(struct qemu_syscall *call);
void qemu_PolyPolyline(struct qemu_syscall *call);
void qemu_PolyTextOutA(struct qemu_syscall *call);
void qemu_PolyTextOutW(struct qemu_syscall *call);
void qemu_PtVisible(struct qemu_syscall *call);
void qemu_RealizePalette(struct qemu_syscall *call);
void qemu_Rectangle(struct qemu_syscall *call);
void qemu_RectVisible(struct qemu_syscall *call);
void qemu_RemoveFontMemResourceEx(struct qemu_syscall *call);
void qemu_RemoveFontResourceA(struct qemu_syscall *call);
void qemu_RemoveFontResourceExA(struct qemu_syscall *call);
void qemu_RemoveFontResourceExW(struct qemu_syscall *call);
void qemu_RemoveFontResourceW(struct qemu_syscall *call);
void qemu_ResetDCA(struct qemu_syscall *call);
void qemu_ResetDCW(struct qemu_syscall *call);
void qemu_ResizePalette(struct qemu_syscall *call);
void qemu_RestoreDC(struct qemu_syscall *call);
void qemu_RoundRect(struct qemu_syscall *call);
void qemu_SaveDC(struct qemu_syscall *call);
void qemu_ScaleViewportExtEx(struct qemu_syscall *call);
void qemu_ScaleWindowExtEx(struct qemu_syscall *call);
void qemu_SelectClipRgn(struct qemu_syscall *call);
void qemu_SelectObject(struct qemu_syscall *call);
void qemu_SelectPalette(struct qemu_syscall *call);
void qemu_SetAbortProc(struct qemu_syscall *call);
void qemu_SetArcDirection(struct qemu_syscall *call);
void qemu_SetBitmapBits(struct qemu_syscall *call);
void qemu_SetBitmapDimensionEx(struct qemu_syscall *call);
void qemu_SetBkColor(struct qemu_syscall *call);
void qemu_SetBkMode(struct qemu_syscall *call);
void qemu_SetBoundsRect(struct qemu_syscall *call);
void qemu_SetBrushOrgEx(struct qemu_syscall *call);
void qemu_SetColorAdjustment(struct qemu_syscall *call);
void qemu_SetColorSpace(struct qemu_syscall *call);
void qemu_SetDCBrushColor(struct qemu_syscall *call);
void qemu_SetDCPenColor(struct qemu_syscall *call);
void qemu_SetDeviceGammaRamp(struct qemu_syscall *call);
void qemu_SetDIBColorTable(struct qemu_syscall *call);
void qemu_SetDIBits(struct qemu_syscall *call);
void qemu_SetDIBitsToDevice(struct qemu_syscall *call);
void qemu_SetEnhMetaFileBits(struct qemu_syscall *call);
void qemu_SetGraphicsMode(struct qemu_syscall *call);
void qemu_SetHookFlags(struct qemu_syscall *call);
void qemu_SetICMMode(struct qemu_syscall *call);
void qemu_SetICMProfileA(struct qemu_syscall *call);
void qemu_SetICMProfileW(struct qemu_syscall *call);
void qemu_SetLayout(struct qemu_syscall *call);
void qemu_SetMagicColors(struct qemu_syscall *call);
void qemu_SetMapMode(struct qemu_syscall *call);
void qemu_SetMapperFlags(struct qemu_syscall *call);
void qemu_SetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_SetMetaRgn(struct qemu_syscall *call);
void qemu_SetMiterLimit(struct qemu_syscall *call);
void qemu_SetObjectOwner(struct qemu_syscall *call);
void qemu_SetPaletteEntries(struct qemu_syscall *call);
void qemu_SetPixel(struct qemu_syscall *call);
void qemu_SetPixelFormat(struct qemu_syscall *call);
void qemu_SetPixelV(struct qemu_syscall *call);
void qemu_SetPolyFillMode(struct qemu_syscall *call);
void qemu_SetRelAbs(struct qemu_syscall *call);
void qemu_SetROP2(struct qemu_syscall *call);
void qemu_SetStretchBltMode(struct qemu_syscall *call);
void qemu_SetSystemPaletteUse(struct qemu_syscall *call);
void qemu_SetTextAlign(struct qemu_syscall *call);
void qemu_SetTextCharacterExtra(struct qemu_syscall *call);
void qemu_SetTextColor(struct qemu_syscall *call);
void qemu_SetTextJustification(struct qemu_syscall *call);
void qemu_SetViewportExtEx(struct qemu_syscall *call);
void qemu_SetViewportOrgEx(struct qemu_syscall *call);
void qemu_SetVirtualResolution(struct qemu_syscall *call);
void qemu_SetWindowExtEx(struct qemu_syscall *call);
void qemu_SetWindowOrgEx(struct qemu_syscall *call);
void qemu_SetWinMetaFileBits(struct qemu_syscall *call);
void qemu_SetWorldTransform(struct qemu_syscall *call);
void qemu_StartDocA(struct qemu_syscall *call);
void qemu_StartDocW(struct qemu_syscall *call);
void qemu_StartPage(struct qemu_syscall *call);
void qemu_StretchBlt(struct qemu_syscall *call);
void qemu_StretchDIBits(struct qemu_syscall *call);
void qemu_SwapBuffers(struct qemu_syscall *call);
void qemu_TextOutA(struct qemu_syscall *call);
void qemu_TextOutW(struct qemu_syscall *call);
void qemu_TranslateCharsetInfo(struct qemu_syscall *call);
void qemu_UnrealizeObject(struct qemu_syscall *call);
void qemu_UpdateColors(struct qemu_syscall *call);
void qemu_UpdateICMRegKeyA(struct qemu_syscall *call);
void qemu_UpdateICMRegKeyW(struct qemu_syscall *call);

#endif

#endif
