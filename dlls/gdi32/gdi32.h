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
    CALL_COPYENHMETAFILEA,
    CALL_COPYENHMETAFILEW,
    CALL_COPYMETAFILEA,
    CALL_COPYMETAFILEW,
    CALL_CREATEFONTA,
    CALL_CREATEFONTINDIRECTA,
    CALL_CREATEFONTINDIRECTEXA,
    CALL_CREATEFONTINDIRECTEXW,
    CALL_CREATEFONTINDIRECTW,
    CALL_CREATEFONTW,
    CALL_CREATESCALABLEFONTRESOURCEA,
    CALL_CREATESCALABLEFONTRESOURCEW,
    CALL_DELETEENHMETAFILE,
    CALL_DELETEMETAFILE,
    CALL_DPTOLP,
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
    CALL_ENUMMETAFILE,
    CALL_EXTTEXTOUTA,
    CALL_EXTTEXTOUTW,
    CALL_FONTISLINKED,
    CALL_GDIGETCHARDIMENSIONS,
    CALL_GDIGETCODEPAGE,
    CALL_GDIGETSPOOLMESSAGE,
    CALL_GDIINITSPOOL,
    CALL_GETASPECTRATIOFILTEREX,
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
    CALL_GETDEVICECAPS,
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
    CALL_GETKERNINGPAIRSA,
    CALL_GETKERNINGPAIRSW,
    CALL_GETMETAFILEA,
    CALL_GETMETAFILEBITSEX,
    CALL_GETMETAFILEW,
    CALL_GETOUTLINETEXTMETRICSA,
    CALL_GETOUTLINETEXTMETRICSW,
    CALL_GETTEXTCHARACTEREXTRA,
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
    CALL_GETWINMETAFILEBITS,
    CALL_LPTODP,
    CALL_MODIFYWORLDTRANSFORM,
    CALL_OFFSETVIEWPORTORGEX,
    CALL_OFFSETWINDOWORGEX,
    CALL_PLAYENHMETAFILE,
    CALL_PLAYENHMETAFILERECORD,
    CALL_PLAYMETAFILE,
    CALL_PLAYMETAFILERECORD,
    CALL_POLYTEXTOUTA,
    CALL_POLYTEXTOUTW,
    CALL_REMOVEFONTMEMRESOURCEEX,
    CALL_REMOVEFONTRESOURCEA,
    CALL_REMOVEFONTRESOURCEEXA,
    CALL_REMOVEFONTRESOURCEEXW,
    CALL_REMOVEFONTRESOURCEW,
    CALL_SCALEVIEWPORTEXTEX,
    CALL_SCALEWINDOWEXTEX,
    CALL_SETABORTPROC,
    CALL_SETENHMETAFILEBITS,
    CALL_SETMAPMODE,
    CALL_SETMAPPERFLAGS,
    CALL_SETMETAFILEBITSEX,
    CALL_SETTEXTCHARACTEREXTRA,
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
    CALL_TEXTOUTA,
    CALL_TEXTOUTW,
    CALL_TRANSLATECHARSETINFO,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_AbortDoc(struct qemu_syscall *call);
void qemu_AddFontMemResourceEx(struct qemu_syscall *call);
void qemu_AddFontResourceA(struct qemu_syscall *call);
void qemu_AddFontResourceExA(struct qemu_syscall *call);
void qemu_AddFontResourceExW(struct qemu_syscall *call);
void qemu_AddFontResourceW(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileA(struct qemu_syscall *call);
void qemu_CopyEnhMetaFileW(struct qemu_syscall *call);
void qemu_CopyMetaFileA(struct qemu_syscall *call);
void qemu_CopyMetaFileW(struct qemu_syscall *call);
void qemu_CreateFontA(struct qemu_syscall *call);
void qemu_CreateFontIndirectA(struct qemu_syscall *call);
void qemu_CreateFontIndirectExA(struct qemu_syscall *call);
void qemu_CreateFontIndirectExW(struct qemu_syscall *call);
void qemu_CreateFontIndirectW(struct qemu_syscall *call);
void qemu_CreateFontW(struct qemu_syscall *call);
void qemu_CreateScalableFontResourceA(struct qemu_syscall *call);
void qemu_CreateScalableFontResourceW(struct qemu_syscall *call);
void qemu_DeleteEnhMetaFile(struct qemu_syscall *call);
void qemu_DeleteMetaFile(struct qemu_syscall *call);
void qemu_DPtoLP(struct qemu_syscall *call);
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
void qemu_EnumMetaFile(struct qemu_syscall *call);
void qemu_ExtTextOutA(struct qemu_syscall *call);
void qemu_ExtTextOutW(struct qemu_syscall *call);
void qemu_FontIsLinked(struct qemu_syscall *call);
void qemu_GdiGetCharDimensions(struct qemu_syscall *call);
void qemu_GdiGetCodePage(struct qemu_syscall *call);
void qemu_GdiGetSpoolMessage(struct qemu_syscall *call);
void qemu_GdiInitSpool(struct qemu_syscall *call);
void qemu_GetAspectRatioFilterEx(struct qemu_syscall *call);
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
void qemu_GetDeviceCaps(struct qemu_syscall *call);
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
void qemu_GetKerningPairsA(struct qemu_syscall *call);
void qemu_GetKerningPairsW(struct qemu_syscall *call);
void qemu_GetMetaFileA(struct qemu_syscall *call);
void qemu_GetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_GetMetaFileW(struct qemu_syscall *call);
void qemu_GetOutlineTextMetricsA(struct qemu_syscall *call);
void qemu_GetOutlineTextMetricsW(struct qemu_syscall *call);
void qemu_GetTextCharacterExtra(struct qemu_syscall *call);
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
void qemu_GetWinMetaFileBits(struct qemu_syscall *call);
void qemu_LPtoDP(struct qemu_syscall *call);
void qemu_ModifyWorldTransform(struct qemu_syscall *call);
void qemu_OffsetViewportOrgEx(struct qemu_syscall *call);
void qemu_OffsetWindowOrgEx(struct qemu_syscall *call);
void qemu_PlayEnhMetaFile(struct qemu_syscall *call);
void qemu_PlayEnhMetaFileRecord(struct qemu_syscall *call);
void qemu_PlayMetaFile(struct qemu_syscall *call);
void qemu_PlayMetaFileRecord(struct qemu_syscall *call);
void qemu_PolyTextOutA(struct qemu_syscall *call);
void qemu_PolyTextOutW(struct qemu_syscall *call);
void qemu_RemoveFontMemResourceEx(struct qemu_syscall *call);
void qemu_RemoveFontResourceA(struct qemu_syscall *call);
void qemu_RemoveFontResourceExA(struct qemu_syscall *call);
void qemu_RemoveFontResourceExW(struct qemu_syscall *call);
void qemu_RemoveFontResourceW(struct qemu_syscall *call);
void qemu_ScaleViewportExtEx(struct qemu_syscall *call);
void qemu_ScaleWindowExtEx(struct qemu_syscall *call);
void qemu_SetAbortProc(struct qemu_syscall *call);
void qemu_SetEnhMetaFileBits(struct qemu_syscall *call);
void qemu_SetMapMode(struct qemu_syscall *call);
void qemu_SetMapperFlags(struct qemu_syscall *call);
void qemu_SetMetaFileBitsEx(struct qemu_syscall *call);
void qemu_SetTextCharacterExtra(struct qemu_syscall *call);
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
void qemu_TextOutA(struct qemu_syscall *call);
void qemu_TextOutW(struct qemu_syscall *call);
void qemu_TranslateCharsetInfo(struct qemu_syscall *call);

#endif

#endif
