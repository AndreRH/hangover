#ifndef QEMU_USP10_H
#define QEMU_USP10_H

enum usp10_calls
{
    CALL_SCRIPTAPPLYDIGITSUBSTITUTION,
    CALL_SCRIPTAPPLYLOGICALWIDTH,
    CALL_SCRIPTBREAK,
    CALL_SCRIPTCACHEGETHEIGHT,
    CALL_SCRIPTCPTOX,
    CALL_SCRIPTFREECACHE,
    CALL_SCRIPTGETCMAP,
    CALL_SCRIPTGETFONTFEATURETAGS,
    CALL_SCRIPTGETFONTLANGUAGETAGS,
    CALL_SCRIPTGETFONTPROPERTIES,
    CALL_SCRIPTGETFONTSCRIPTTAGS,
    CALL_SCRIPTGETGLYPHABCWIDTH,
    CALL_SCRIPTGETLOGICALWIDTHS,
    CALL_SCRIPTGETPROPERTIES,
    CALL_SCRIPTISCOMPLEX,
    CALL_SCRIPTITEMIZE,
    CALL_SCRIPTITEMIZEOPENTYPE,
    CALL_SCRIPTJUSTIFY,
    CALL_SCRIPTLAYOUT,
    CALL_SCRIPTPLACE,
    CALL_SCRIPTPLACEOPENTYPE,
    CALL_SCRIPTRECORDDIGITSUBSTITUTION,
    CALL_SCRIPTSHAPE,
    CALL_SCRIPTSHAPEOPENTYPE,
    CALL_SCRIPTSTRING_PCOUTCHARS,
    CALL_SCRIPTSTRING_PLOGATTR,
    CALL_SCRIPTSTRING_PSIZE,
    CALL_SCRIPTSTRINGANALYSE,
    CALL_SCRIPTSTRINGCPTOX,
    CALL_SCRIPTSTRINGFREE,
    CALL_SCRIPTSTRINGGETLOGICALWIDTHS,
    CALL_SCRIPTSTRINGGETORDER,
    CALL_SCRIPTSTRINGOUT,
    CALL_SCRIPTSTRINGVALIDATE,
    CALL_SCRIPTSTRINGXTOCP,
    CALL_SCRIPTTEXTOUT,
    CALL_SCRIPTXTOCP,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_ScriptApplyDigitSubstitution(struct qemu_syscall *call);
void qemu_ScriptApplyLogicalWidth(struct qemu_syscall *call);
void qemu_ScriptBreak(struct qemu_syscall *call);
void qemu_ScriptCacheGetHeight(struct qemu_syscall *call);
void qemu_ScriptCPtoX(struct qemu_syscall *call);
void qemu_ScriptFreeCache(struct qemu_syscall *call);
void qemu_ScriptGetCMap(struct qemu_syscall *call);
void qemu_ScriptGetFontFeatureTags(struct qemu_syscall *call);
void qemu_ScriptGetFontLanguageTags(struct qemu_syscall *call);
void qemu_ScriptGetFontProperties(struct qemu_syscall *call);
void qemu_ScriptGetFontScriptTags(struct qemu_syscall *call);
void qemu_ScriptGetGlyphABCWidth(struct qemu_syscall *call);
void qemu_ScriptGetLogicalWidths(struct qemu_syscall *call);
void qemu_ScriptGetProperties(struct qemu_syscall *call);
void qemu_ScriptIsComplex(struct qemu_syscall *call);
void qemu_ScriptItemize(struct qemu_syscall *call);
void qemu_ScriptItemizeOpenType(struct qemu_syscall *call);
void qemu_ScriptJustify(struct qemu_syscall *call);
void qemu_ScriptLayout(struct qemu_syscall *call);
void qemu_ScriptPlace(struct qemu_syscall *call);
void qemu_ScriptPlaceOpenType(struct qemu_syscall *call);
void qemu_ScriptRecordDigitSubstitution(struct qemu_syscall *call);
void qemu_ScriptShape(struct qemu_syscall *call);
void qemu_ScriptShapeOpenType(struct qemu_syscall *call);
void qemu_ScriptString_pcOutChars(struct qemu_syscall *call);
void qemu_ScriptString_pLogAttr(struct qemu_syscall *call);
void qemu_ScriptString_pSize(struct qemu_syscall *call);
void qemu_ScriptStringAnalyse(struct qemu_syscall *call);
void qemu_ScriptStringCPtoX(struct qemu_syscall *call);
void qemu_ScriptStringFree(struct qemu_syscall *call);
void qemu_ScriptStringGetLogicalWidths(struct qemu_syscall *call);
void qemu_ScriptStringGetOrder(struct qemu_syscall *call);
void qemu_ScriptStringOut(struct qemu_syscall *call);
void qemu_ScriptStringValidate(struct qemu_syscall *call);
void qemu_ScriptStringXtoCP(struct qemu_syscall *call);
void qemu_ScriptTextOut(struct qemu_syscall *call);
void qemu_ScriptXtoCP(struct qemu_syscall *call);

extern HRESULT (WINAPI *pScriptFreeCache)(SCRIPT_CACHE *psc);
extern HRESULT (WINAPI *pScriptGetProperties)(const SCRIPT_PROPERTIES ***props, int *num);
extern HRESULT (WINAPI *pScriptGetFontProperties)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_FONTPROPERTIES *sfp);
extern HRESULT (WINAPI *pScriptRecordDigitSubstitution)(LCID locale, SCRIPT_DIGITSUBSTITUTE *sds);
extern HRESULT (WINAPI *pScriptApplyDigitSubstitution)(const SCRIPT_DIGITSUBSTITUTE *sds, SCRIPT_CONTROL *sc,
        SCRIPT_STATE *ss);
extern HRESULT (WINAPI *pScriptItemizeOpenType)(const WCHAR *pwcInChars, int cInChars, int cMaxItems,
        const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems,
        OPENTYPE_TAG *pScriptTags, int *pcItems);
extern HRESULT (WINAPI *pScriptItemize)(const WCHAR *pwcInChars, int cInChars, int cMaxItems,
        const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems, int *pcItems);
extern HRESULT (WINAPI *pScriptStringAnalyse)(HDC hdc, const void *pString, int cString, int cGlyphs,
        int iCharset, DWORD dwFlags, int iReqWidth, SCRIPT_CONTROL *psControl, SCRIPT_STATE *psState,
        const int *piDx, SCRIPT_TABDEF *pTabdef, const BYTE *pbInClass, SCRIPT_STRING_ANALYSIS *pssa);
extern HRESULT (WINAPI *pScriptStringOut)(SCRIPT_STRING_ANALYSIS ssa, int iX, int iY, UINT uOptions, const RECT *prc,
        int iMinSel, int iMaxSel, BOOL fDisabled);
extern HRESULT (WINAPI *pScriptStringCPtoX)(SCRIPT_STRING_ANALYSIS ssa, int icp, BOOL fTrailing, int* pX);
extern HRESULT (WINAPI *pScriptStringXtoCP)(SCRIPT_STRING_ANALYSIS ssa, int iX, int* piCh, int* piTrailing);
extern HRESULT (WINAPI *pScriptStringFree)(SCRIPT_STRING_ANALYSIS *pssa);
extern HRESULT (WINAPI *pScriptCPtoX)(int iCP, BOOL fTrailing, int cChars, int cGlyphs, const WORD *pwLogClust,
        const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piX);
extern HRESULT (WINAPI *pScriptXtoCP)(int iX, int cChars, int cGlyphs, const WORD *pwLogClust,
        const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piCP, int *piTrailing);
extern HRESULT (WINAPI *pScriptBreak)(const WCHAR *chars, int count, const SCRIPT_ANALYSIS *sa, SCRIPT_LOGATTR *la);
extern HRESULT (WINAPI *pScriptIsComplex)(const WCHAR *chars, int len, DWORD flag);
extern HRESULT (WINAPI *pScriptShapeOpenType)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
        OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges,
        const WCHAR *pwcChars, int cChars, int cMaxGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps,
        WORD *pwOutGlyphs, SCRIPT_GLYPHPROP *pOutGlyphProps, int *pcGlyphs);
extern HRESULT (WINAPI *pScriptShape)(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcChars, int cChars, int cMaxGlyphs,
        SCRIPT_ANALYSIS *psa, WORD *pwOutGlyphs, WORD *pwLogClust, SCRIPT_VISATTR *psva, int *pcGlyphs);
extern HRESULT (WINAPI *pScriptPlaceOpenType)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
        OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges,
        const WCHAR *pwcChars, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, int cChars, const WORD *pwGlyphs,
        const SCRIPT_GLYPHPROP *pGlyphProps, int cGlyphs, int *piAdvance, GOFFSET *pGoffset, ABC *pABC);
extern HRESULT (WINAPI *pScriptPlace)(HDC hdc, SCRIPT_CACHE *psc, const WORD *pwGlyphs, int cGlyphs,
        const SCRIPT_VISATTR *psva, SCRIPT_ANALYSIS *psa, int *piAdvance, GOFFSET *pGoffset, ABC *pABC);
extern HRESULT (WINAPI *pScriptGetCMap)(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcInChars, int cChars,
        DWORD dwFlags, WORD *pwOutGlyphs);
extern HRESULT (WINAPI *pScriptTextOut)(const HDC hdc, SCRIPT_CACHE *psc, int x, int y, UINT fuOptions,
        const RECT *lprc, const SCRIPT_ANALYSIS *psa, const WCHAR *pwcReserved, int iReserved, const WORD *pwGlyphs,
        int cGlyphs, const int *piAdvance, const int *piJustify, const GOFFSET *pGoffset);
extern HRESULT (WINAPI *pScriptCacheGetHeight)(HDC hdc, SCRIPT_CACHE *psc, LONG *height);
extern HRESULT (WINAPI *pScriptGetGlyphABCWidth)(HDC hdc, SCRIPT_CACHE *psc, WORD glyph, ABC *abc);
extern HRESULT (WINAPI *pScriptLayout)(int runs, const BYTE *level, int *vistolog, int *logtovis);
extern HRESULT (WINAPI *pScriptStringGetLogicalWidths)(SCRIPT_STRING_ANALYSIS ssa, int *piDx);
extern HRESULT (WINAPI *pScriptStringValidate)(SCRIPT_STRING_ANALYSIS ssa);
extern const SIZE * (WINAPI *pScriptString_pSize)(SCRIPT_STRING_ANALYSIS ssa);
extern const SCRIPT_LOGATTR * (WINAPI *pScriptString_pLogAttr)(SCRIPT_STRING_ANALYSIS ssa);
extern const int * (WINAPI *pScriptString_pcOutChars)(SCRIPT_STRING_ANALYSIS ssa);
extern HRESULT (WINAPI *pScriptStringGetOrder)(SCRIPT_STRING_ANALYSIS ssa, UINT *order);
extern HRESULT (WINAPI *pScriptGetLogicalWidths)(const SCRIPT_ANALYSIS *sa, int nbchars, int nbglyphs,
        const int *advances, const WORD *log_clust, const SCRIPT_VISATTR *sva, int *widths);
extern HRESULT (WINAPI *pScriptApplyLogicalWidth)(const int *dx, int num_chars, int num_glyphs, const WORD *log_clust,
        const SCRIPT_VISATTR *sva, const int *advance, const SCRIPT_ANALYSIS *sa, ABC *abc, int *justify);
extern HRESULT (WINAPI *pScriptJustify)(const SCRIPT_VISATTR *sva, const int *advance, int num_glyphs, int dx,
        int min_kashida, int *justify);
extern HRESULT (WINAPI *pScriptGetFontScriptTags)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, int cMaxTags,
        OPENTYPE_TAG *pScriptTags, int *pcTags);
extern HRESULT (WINAPI *pScriptGetFontLanguageTags)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa,
        OPENTYPE_TAG tagScript, int cMaxTags, OPENTYPE_TAG *pLangSysTags, int *pcTags);
extern HRESULT (WINAPI *pScriptGetFontFeatureTags)(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa,
        OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int cMaxTags, OPENTYPE_TAG *pFeatureTags, int *pcTags);

#endif

#endif
