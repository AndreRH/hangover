/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

#ifdef QEMU_DLL_GUEST

#else

#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_usp10.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_usp10);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
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
};

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
    HMODULE usp10;
    WINE_TRACE("Loading host-side usp10 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    usp10 = LoadLibraryA("usp10.dll");
    if (!usp10)
    {
        WINE_FIXME("Could not load usp10.dll\n");
        return NULL;
    }

    pScriptFreeCache = (void *)GetProcAddress(usp10, "ScriptFreeCache");
    if (!pScriptFreeCache)
        WINE_ERR("Could not find ScriptFreeCache in usp10.dll\n");

    pScriptGetProperties = (void *)GetProcAddress(usp10, "ScriptGetProperties");
    if (!pScriptGetProperties)
        WINE_ERR("Could not find ScriptGetProperties in usp10.dll\n");

    pScriptGetFontProperties = (void *)GetProcAddress(usp10, "ScriptGetFontProperties");
    if (!pScriptGetFontProperties)
        WINE_ERR("Could not find ScriptGetFontProperties in usp10.dll\n");

    pScriptRecordDigitSubstitution = (void *)GetProcAddress(usp10, "ScriptRecordDigitSubstitution");
    if (!pScriptRecordDigitSubstitution)
        WINE_ERR("Could not find ScriptRecordDigitSubstitution in usp10.dll\n");

    pScriptApplyDigitSubstitution = (void *)GetProcAddress(usp10, "ScriptApplyDigitSubstitution");
    if (!pScriptApplyDigitSubstitution)
        WINE_ERR("Could not find ScriptApplyDigitSubstitution in usp10.dll\n");

    pScriptItemizeOpenType = (void *)GetProcAddress(usp10, "ScriptItemizeOpenType");
    if (!pScriptItemizeOpenType)
        WINE_ERR("Could not find ScriptItemizeOpenType in usp10.dll\n");

    pScriptItemize = (void *)GetProcAddress(usp10, "ScriptItemize");
    if (!pScriptItemize)
        WINE_ERR("Could not find ScriptItemize in usp10.dll\n");

    pScriptStringAnalyse = (void *)GetProcAddress(usp10, "ScriptStringAnalyse");
    if (!pScriptStringAnalyse)
        WINE_ERR("Could not find ScriptStringAnalyse in usp10.dll\n");

    pScriptStringOut = (void *)GetProcAddress(usp10, "ScriptStringOut");
    if (!pScriptStringOut)
        WINE_ERR("Could not find ScriptStringOut in usp10.dll\n");

    pScriptStringCPtoX = (void *)GetProcAddress(usp10, "ScriptStringCPtoX");
    if (!pScriptStringCPtoX)
        WINE_ERR("Could not find ScriptStringCPtoX in usp10.dll\n");

    pScriptStringXtoCP = (void *)GetProcAddress(usp10, "ScriptStringXtoCP");
    if (!pScriptStringXtoCP)
        WINE_ERR("Could not find ScriptStringXtoCP in usp10.dll\n");

    pScriptStringFree = (void *)GetProcAddress(usp10, "ScriptStringFree");
    if (!pScriptStringFree)
        WINE_ERR("Could not find ScriptStringFree in usp10.dll\n");

    pScriptCPtoX = (void *)GetProcAddress(usp10, "ScriptCPtoX");
    if (!pScriptCPtoX)
        WINE_ERR("Could not find ScriptCPtoX in usp10.dll\n");

    pScriptXtoCP = (void *)GetProcAddress(usp10, "ScriptXtoCP");
    if (!pScriptXtoCP)
        WINE_ERR("Could not find ScriptXtoCP in usp10.dll\n");

    pScriptBreak = (void *)GetProcAddress(usp10, "ScriptBreak");
    if (!pScriptBreak)
        WINE_ERR("Could not find ScriptBreak in usp10.dll\n");

    pScriptIsComplex = (void *)GetProcAddress(usp10, "ScriptIsComplex");
    if (!pScriptIsComplex)
        WINE_ERR("Could not find ScriptIsComplex in usp10.dll\n");

    pScriptShapeOpenType = (void *)GetProcAddress(usp10, "ScriptShapeOpenType");
    if (!pScriptShapeOpenType)
        WINE_ERR("Could not find ScriptShapeOpenType in usp10.dll\n");

    pScriptShape = (void *)GetProcAddress(usp10, "ScriptShape");
    if (!pScriptShape)
        WINE_ERR("Could not find ScriptShape in usp10.dll\n");

    pScriptPlaceOpenType = (void *)GetProcAddress(usp10, "ScriptPlaceOpenType");
    if (!pScriptPlaceOpenType)
        WINE_ERR("Could not find ScriptPlaceOpenType in usp10.dll\n");

    pScriptPlace = (void *)GetProcAddress(usp10, "ScriptPlace");
    if (!pScriptPlace)
        WINE_ERR("Could not find ScriptPlace in usp10.dll\n");

    pScriptGetCMap = (void *)GetProcAddress(usp10, "ScriptGetCMap");
    if (!pScriptGetCMap)
        WINE_ERR("Could not find ScriptGetCMap in usp10.dll\n");

    pScriptTextOut = (void *)GetProcAddress(usp10, "ScriptTextOut");
    if (!pScriptTextOut)
        WINE_ERR("Could not find ScriptTextOut in usp10.dll\n");

    pScriptCacheGetHeight = (void *)GetProcAddress(usp10, "ScriptCacheGetHeight");
    if (!pScriptCacheGetHeight)
        WINE_ERR("Could not find ScriptCacheGetHeight in usp10.dll\n");

    pScriptGetGlyphABCWidth = (void *)GetProcAddress(usp10, "ScriptGetGlyphABCWidth");
    if (!pScriptGetGlyphABCWidth)
        WINE_ERR("Could not find ScriptGetGlyphABCWidth in usp10.dll\n");

    pScriptLayout = (void *)GetProcAddress(usp10, "ScriptLayout");
    if (!pScriptLayout)
        WINE_ERR("Could not find ScriptLayout in usp10.dll\n");

    pScriptStringGetLogicalWidths = (void *)GetProcAddress(usp10, "ScriptStringGetLogicalWidths");
    if (!pScriptStringGetLogicalWidths)
        WINE_ERR("Could not find ScriptStringGetLogicalWidths in usp10.dll\n");

    pScriptStringValidate = (void *)GetProcAddress(usp10, "ScriptStringValidate");
    if (!pScriptStringValidate)
        WINE_ERR("Could not find ScriptStringValidate in usp10.dll\n");

    pScriptStringGetOrder = (void *)GetProcAddress(usp10, "ScriptStringGetOrder");
    if (!pScriptStringGetOrder)
        WINE_ERR("Could not find ScriptStringGetOrder in usp10.dll\n");

    pScriptGetLogicalWidths = (void *)GetProcAddress(usp10, "ScriptGetLogicalWidths");
    if (!pScriptGetLogicalWidths)
        WINE_ERR("Could not find ScriptGetLogicalWidths in usp10.dll\n");

    pScriptApplyLogicalWidth = (void *)GetProcAddress(usp10, "ScriptApplyLogicalWidth");
    if (!pScriptApplyLogicalWidth)
        WINE_ERR("Could not find ScriptApplyLogicalWidth in usp10.dll\n");

    pScriptJustify = (void *)GetProcAddress(usp10, "ScriptJustify");
    if (!pScriptJustify)
        WINE_ERR("Could not find ScriptJustify in usp10.dll\n");

    pScriptGetFontScriptTags = (void *)GetProcAddress(usp10, "ScriptGetFontScriptTags");
    if (!pScriptGetFontScriptTags)
        WINE_ERR("Could not find ScriptGetFontScriptTags in usp10.dll\n");

    pScriptGetFontLanguageTags = (void *)GetProcAddress(usp10, "ScriptGetFontLanguageTags");
    if (!pScriptGetFontLanguageTags)
        WINE_ERR("Could not find ScriptGetFontLanguageTags in usp10.dll\n");

    pScriptGetFontFeatureTags = (void *)GetProcAddress(usp10, "ScriptGetFontFeatureTags");
    if (!pScriptGetFontFeatureTags)
        WINE_ERR("Could not find ScriptGetFontFeatureTags in usp10.dll\n");

    return dll_functions;
}

#endif
