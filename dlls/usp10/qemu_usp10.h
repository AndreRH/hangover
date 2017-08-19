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

#endif

#endif
