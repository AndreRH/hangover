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
#include "qemu_usp10.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_usp10);
#endif


struct qemu_ScriptFreeCache
{
    struct qemu_syscall super;
    uint64_t psc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptFreeCache(SCRIPT_CACHE *psc)
{
    struct qemu_ScriptFreeCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTFREECACHE);
    call.psc = (uint64_t)psc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptFreeCache(struct qemu_syscall *call)
{
    struct qemu_ScriptFreeCache *c = (struct qemu_ScriptFreeCache *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptFreeCache(QEMU_G2H(c->psc));
}

#endif

struct qemu_ScriptGetProperties
{
    struct qemu_syscall super;
    uint64_t props;
    uint64_t num;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetProperties(const SCRIPT_PROPERTIES ***props, int *num)
{
    struct qemu_ScriptGetProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETPROPERTIES);
    call.props = (uint64_t)props;
    call.num = (uint64_t)num;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetProperties(struct qemu_syscall *call)
{
    struct qemu_ScriptGetProperties *c = (struct qemu_ScriptGetProperties *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetProperties(QEMU_G2H(c->props), QEMU_G2H(c->num));
}

#endif

struct qemu_ScriptGetFontProperties
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t sfp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetFontProperties(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_FONTPROPERTIES *sfp)
{
    struct qemu_ScriptGetFontProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTPROPERTIES);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.sfp = (uint64_t)sfp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetFontProperties(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontProperties *c = (struct qemu_ScriptGetFontProperties *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetFontProperties(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->sfp));
}

#endif

struct qemu_ScriptRecordDigitSubstitution
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t sds;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptRecordDigitSubstitution(LCID locale, SCRIPT_DIGITSUBSTITUTE *sds)
{
    struct qemu_ScriptRecordDigitSubstitution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTRECORDDIGITSUBSTITUTION);
    call.locale = (uint64_t)locale;
    call.sds = (uint64_t)sds;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptRecordDigitSubstitution(struct qemu_syscall *call)
{
    struct qemu_ScriptRecordDigitSubstitution *c = (struct qemu_ScriptRecordDigitSubstitution *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptRecordDigitSubstitution(c->locale, QEMU_G2H(c->sds));
}

#endif

struct qemu_ScriptApplyDigitSubstitution
{
    struct qemu_syscall super;
    uint64_t sds;
    uint64_t sc;
    uint64_t ss;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptApplyDigitSubstitution(const SCRIPT_DIGITSUBSTITUTE *sds, SCRIPT_CONTROL *sc, SCRIPT_STATE *ss)
{
    struct qemu_ScriptApplyDigitSubstitution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTAPPLYDIGITSUBSTITUTION);
    call.sds = (uint64_t)sds;
    call.sc = (uint64_t)sc;
    call.ss = (uint64_t)ss;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptApplyDigitSubstitution(struct qemu_syscall *call)
{
    struct qemu_ScriptApplyDigitSubstitution *c = (struct qemu_ScriptApplyDigitSubstitution *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptApplyDigitSubstitution(QEMU_G2H(c->sds), QEMU_G2H(c->sc), QEMU_G2H(c->ss));
}

#endif

struct qemu_ScriptItemizeOpenType
{
    struct qemu_syscall super;
    uint64_t pwcInChars;
    uint64_t cInChars;
    uint64_t cMaxItems;
    uint64_t psControl;
    uint64_t psState;
    uint64_t pItems;
    uint64_t pScriptTags;
    uint64_t pcItems;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptItemizeOpenType(const WCHAR *pwcInChars, int cInChars, int cMaxItems, const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems, OPENTYPE_TAG *pScriptTags, int *pcItems)
{
    struct qemu_ScriptItemizeOpenType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTITEMIZEOPENTYPE);
    call.pwcInChars = (uint64_t)pwcInChars;
    call.cInChars = (uint64_t)cInChars;
    call.cMaxItems = (uint64_t)cMaxItems;
    call.psControl = (uint64_t)psControl;
    call.psState = (uint64_t)psState;
    call.pItems = (uint64_t)pItems;
    call.pScriptTags = (uint64_t)pScriptTags;
    call.pcItems = (uint64_t)pcItems;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ScriptItemizeOpenType to Wine headers? */
extern HRESULT WINAPI ScriptItemizeOpenType(const WCHAR *pwcInChars, int cInChars, int cMaxItems, const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems, OPENTYPE_TAG *pScriptTags, int *pcItems);
void qemu_ScriptItemizeOpenType(struct qemu_syscall *call)
{
    struct qemu_ScriptItemizeOpenType *c = (struct qemu_ScriptItemizeOpenType *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptItemizeOpenType(QEMU_G2H(c->pwcInChars), c->cInChars, c->cMaxItems, QEMU_G2H(c->psControl), QEMU_G2H(c->psState), QEMU_G2H(c->pItems), QEMU_G2H(c->pScriptTags), QEMU_G2H(c->pcItems));
}

#endif

struct qemu_ScriptItemize
{
    struct qemu_syscall super;
    uint64_t pwcInChars;
    uint64_t cInChars;
    uint64_t cMaxItems;
    uint64_t psControl;
    uint64_t psState;
    uint64_t pItems;
    uint64_t pcItems;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptItemize(const WCHAR *pwcInChars, int cInChars, int cMaxItems, const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems, int *pcItems)
{
    struct qemu_ScriptItemize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTITEMIZE);
    call.pwcInChars = (uint64_t)pwcInChars;
    call.cInChars = (uint64_t)cInChars;
    call.cMaxItems = (uint64_t)cMaxItems;
    call.psControl = (uint64_t)psControl;
    call.psState = (uint64_t)psState;
    call.pItems = (uint64_t)pItems;
    call.pcItems = (uint64_t)pcItems;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptItemize(struct qemu_syscall *call)
{
    struct qemu_ScriptItemize *c = (struct qemu_ScriptItemize *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptItemize(QEMU_G2H(c->pwcInChars), c->cInChars, c->cMaxItems, QEMU_G2H(c->psControl), QEMU_G2H(c->psState), QEMU_G2H(c->pItems), QEMU_G2H(c->pcItems));
}

#endif

struct qemu_ScriptStringAnalyse
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pString;
    uint64_t cString;
    uint64_t cGlyphs;
    uint64_t iCharset;
    uint64_t dwFlags;
    uint64_t iReqWidth;
    uint64_t psControl;
    uint64_t psState;
    uint64_t piDx;
    uint64_t pTabdef;
    uint64_t pbInClass;
    uint64_t pssa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringAnalyse(HDC hdc, const void *pString, int cString, int cGlyphs, int iCharset, DWORD dwFlags, int iReqWidth, SCRIPT_CONTROL *psControl, SCRIPT_STATE *psState, const int *piDx, SCRIPT_TABDEF *pTabdef, const BYTE *pbInClass, SCRIPT_STRING_ANALYSIS *pssa)
{
    struct qemu_ScriptStringAnalyse call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGANALYSE);
    call.hdc = (uint64_t)hdc;
    call.pString = (uint64_t)pString;
    call.cString = (uint64_t)cString;
    call.cGlyphs = (uint64_t)cGlyphs;
    call.iCharset = (uint64_t)iCharset;
    call.dwFlags = (uint64_t)dwFlags;
    call.iReqWidth = (uint64_t)iReqWidth;
    call.psControl = (uint64_t)psControl;
    call.psState = (uint64_t)psState;
    call.piDx = (uint64_t)piDx;
    call.pTabdef = (uint64_t)pTabdef;
    call.pbInClass = (uint64_t)pbInClass;
    call.pssa = (uint64_t)pssa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringAnalyse(struct qemu_syscall *call)
{
    struct qemu_ScriptStringAnalyse *c = (struct qemu_ScriptStringAnalyse *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptStringAnalyse(QEMU_G2H(c->hdc), QEMU_G2H(c->pString), c->cString, c->cGlyphs, c->iCharset, c->dwFlags, c->iReqWidth, QEMU_G2H(c->psControl), QEMU_G2H(c->psState), QEMU_G2H(c->piDx), QEMU_G2H(c->pTabdef), QEMU_G2H(c->pbInClass), QEMU_G2H(c->pssa));
}

#endif

struct qemu_ScriptStringOut
{
    struct qemu_syscall super;
    uint64_t ssa;
    uint64_t iX;
    uint64_t iY;
    uint64_t uOptions;
    uint64_t prc;
    uint64_t iMinSel;
    uint64_t iMaxSel;
    uint64_t fDisabled;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringOut(SCRIPT_STRING_ANALYSIS ssa, int iX, int iY, UINT uOptions, const RECT *prc, int iMinSel, int iMaxSel, BOOL fDisabled)
{
    struct qemu_ScriptStringOut call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGOUT);
    call.ssa = (uint64_t)ssa;
    call.iX = (uint64_t)iX;
    call.iY = (uint64_t)iY;
    call.uOptions = (uint64_t)uOptions;
    call.prc = (uint64_t)prc;
    call.iMinSel = (uint64_t)iMinSel;
    call.iMaxSel = (uint64_t)iMaxSel;
    call.fDisabled = (uint64_t)fDisabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringOut(struct qemu_syscall *call)
{
    struct qemu_ScriptStringOut *c = (struct qemu_ScriptStringOut *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptStringOut(QEMU_G2H(c->ssa), c->iX, c->iY, c->uOptions, QEMU_G2H(c->prc), c->iMinSel, c->iMaxSel, c->fDisabled);
}

#endif

struct qemu_ScriptStringCPtoX
{
    struct qemu_syscall super;
    uint64_t ssa;
    uint64_t icp;
    uint64_t fTrailing;
    uint64_t pX;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringCPtoX(SCRIPT_STRING_ANALYSIS ssa, int icp, BOOL fTrailing, int* pX)
{
    struct qemu_ScriptStringCPtoX call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGCPTOX);
    call.ssa = (uint64_t)ssa;
    call.icp = (uint64_t)icp;
    call.fTrailing = (uint64_t)fTrailing;
    call.pX = (uint64_t)pX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringCPtoX(struct qemu_syscall *call)
{
    struct qemu_ScriptStringCPtoX *c = (struct qemu_ScriptStringCPtoX *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptStringCPtoX(QEMU_G2H(c->ssa), c->icp, c->fTrailing, QEMU_G2H(c->pX));
}

#endif

struct qemu_ScriptStringXtoCP
{
    struct qemu_syscall super;
    uint64_t ssa;
    uint64_t iX;
    uint64_t piCh;
    uint64_t piTrailing;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringXtoCP(SCRIPT_STRING_ANALYSIS ssa, int iX, int* piCh, int* piTrailing)
{
    struct qemu_ScriptStringXtoCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGXTOCP);
    call.ssa = (uint64_t)ssa;
    call.iX = (uint64_t)iX;
    call.piCh = (uint64_t)piCh;
    call.piTrailing = (uint64_t)piTrailing;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringXtoCP(struct qemu_syscall *call)
{
    struct qemu_ScriptStringXtoCP *c = (struct qemu_ScriptStringXtoCP *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptStringXtoCP(QEMU_G2H(c->ssa), c->iX, QEMU_G2H(c->piCh), QEMU_G2H(c->piTrailing));
}

#endif

struct qemu_ScriptStringFree
{
    struct qemu_syscall super;
    uint64_t pssa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringFree(SCRIPT_STRING_ANALYSIS *pssa)
{
    struct qemu_ScriptStringFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGFREE);
    call.pssa = (uint64_t)pssa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringFree(struct qemu_syscall *call)
{
    struct qemu_ScriptStringFree *c = (struct qemu_ScriptStringFree *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptStringFree(QEMU_G2H(c->pssa));
}

#endif

struct qemu_ScriptCPtoX
{
    struct qemu_syscall super;
    uint64_t iCP;
    uint64_t fTrailing;
    uint64_t cChars;
    uint64_t cGlyphs;
    uint64_t pwLogClust;
    uint64_t psva;
    uint64_t piAdvance;
    uint64_t psa;
    uint64_t piX;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptCPtoX(int iCP, BOOL fTrailing, int cChars, int cGlyphs, const WORD *pwLogClust, const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piX)
{
    struct qemu_ScriptCPtoX call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTCPTOX);
    call.iCP = (uint64_t)iCP;
    call.fTrailing = (uint64_t)fTrailing;
    call.cChars = (uint64_t)cChars;
    call.cGlyphs = (uint64_t)cGlyphs;
    call.pwLogClust = (uint64_t)pwLogClust;
    call.psva = (uint64_t)psva;
    call.piAdvance = (uint64_t)piAdvance;
    call.psa = (uint64_t)psa;
    call.piX = (uint64_t)piX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptCPtoX(struct qemu_syscall *call)
{
    struct qemu_ScriptCPtoX *c = (struct qemu_ScriptCPtoX *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptCPtoX(c->iCP, c->fTrailing, c->cChars, c->cGlyphs, QEMU_G2H(c->pwLogClust), QEMU_G2H(c->psva), QEMU_G2H(c->piAdvance), QEMU_G2H(c->psa), QEMU_G2H(c->piX));
}

#endif

struct qemu_ScriptXtoCP
{
    struct qemu_syscall super;
    uint64_t iX;
    uint64_t cChars;
    uint64_t cGlyphs;
    uint64_t pwLogClust;
    uint64_t psva;
    uint64_t piAdvance;
    uint64_t psa;
    uint64_t piCP;
    uint64_t piTrailing;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptXtoCP(int iX, int cChars, int cGlyphs, const WORD *pwLogClust, const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piCP, int *piTrailing)
{
    struct qemu_ScriptXtoCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTXTOCP);
    call.iX = (uint64_t)iX;
    call.cChars = (uint64_t)cChars;
    call.cGlyphs = (uint64_t)cGlyphs;
    call.pwLogClust = (uint64_t)pwLogClust;
    call.psva = (uint64_t)psva;
    call.piAdvance = (uint64_t)piAdvance;
    call.psa = (uint64_t)psa;
    call.piCP = (uint64_t)piCP;
    call.piTrailing = (uint64_t)piTrailing;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptXtoCP(struct qemu_syscall *call)
{
    struct qemu_ScriptXtoCP *c = (struct qemu_ScriptXtoCP *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptXtoCP(c->iX, c->cChars, c->cGlyphs, QEMU_G2H(c->pwLogClust), QEMU_G2H(c->psva), QEMU_G2H(c->piAdvance), QEMU_G2H(c->psa), QEMU_G2H(c->piCP), QEMU_G2H(c->piTrailing));
}

#endif

struct qemu_ScriptBreak
{
    struct qemu_syscall super;
    uint64_t chars;
    uint64_t count;
    uint64_t sa;
    uint64_t la;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptBreak(const WCHAR *chars, int count, const SCRIPT_ANALYSIS *sa, SCRIPT_LOGATTR *la)
{
    struct qemu_ScriptBreak call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTBREAK);
    call.chars = (uint64_t)chars;
    call.count = (uint64_t)count;
    call.sa = (uint64_t)sa;
    call.la = (uint64_t)la;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptBreak(struct qemu_syscall *call)
{
    struct qemu_ScriptBreak *c = (struct qemu_ScriptBreak *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptBreak(QEMU_G2H(c->chars), c->count, QEMU_G2H(c->sa), QEMU_G2H(c->la));
}

#endif

struct qemu_ScriptIsComplex
{
    struct qemu_syscall super;
    uint64_t chars;
    uint64_t len;
    uint64_t flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptIsComplex(const WCHAR *chars, int len, DWORD flag)
{
    struct qemu_ScriptIsComplex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTISCOMPLEX);
    call.chars = (uint64_t)chars;
    call.len = (uint64_t)len;
    call.flag = (uint64_t)flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptIsComplex(struct qemu_syscall *call)
{
    struct qemu_ScriptIsComplex *c = (struct qemu_ScriptIsComplex *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptIsComplex(QEMU_G2H(c->chars), c->len, c->flag);
}

#endif

struct qemu_ScriptShapeOpenType
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t psa;
    uint64_t tagScript;
    uint64_t tagLangSys;
    uint64_t rcRangeChars;
    uint64_t rpRangeProperties;
    uint64_t cRanges;
    uint64_t pwcChars;
    uint64_t cChars;
    uint64_t cMaxGlyphs;
    uint64_t pwLogClust;
    uint64_t pCharProps;
    uint64_t pwOutGlyphs;
    uint64_t pOutGlyphProps;
    uint64_t pcGlyphs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptShapeOpenType(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges, const WCHAR *pwcChars, int cChars, int cMaxGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, WORD *pwOutGlyphs, SCRIPT_GLYPHPROP *pOutGlyphProps, int *pcGlyphs)
{
    struct qemu_ScriptShapeOpenType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSHAPEOPENTYPE);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.psa = (uint64_t)psa;
    call.tagScript = (uint64_t)tagScript;
    call.tagLangSys = (uint64_t)tagLangSys;
    call.rcRangeChars = (uint64_t)rcRangeChars;
    call.rpRangeProperties = (uint64_t)rpRangeProperties;
    call.cRanges = (uint64_t)cRanges;
    call.pwcChars = (uint64_t)pwcChars;
    call.cChars = (uint64_t)cChars;
    call.cMaxGlyphs = (uint64_t)cMaxGlyphs;
    call.pwLogClust = (uint64_t)pwLogClust;
    call.pCharProps = (uint64_t)pCharProps;
    call.pwOutGlyphs = (uint64_t)pwOutGlyphs;
    call.pOutGlyphProps = (uint64_t)pOutGlyphProps;
    call.pcGlyphs = (uint64_t)pcGlyphs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ScriptShapeOpenType to Wine headers? */
extern HRESULT WINAPI ScriptShapeOpenType(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges, const WCHAR *pwcChars, int cChars, int cMaxGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, WORD *pwOutGlyphs, SCRIPT_GLYPHPROP *pOutGlyphProps, int *pcGlyphs);
void qemu_ScriptShapeOpenType(struct qemu_syscall *call)
{
    struct qemu_ScriptShapeOpenType *c = (struct qemu_ScriptShapeOpenType *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptShapeOpenType(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->psa), c->tagScript, c->tagLangSys, QEMU_G2H(c->rcRangeChars), QEMU_G2H(c->rpRangeProperties), c->cRanges, QEMU_G2H(c->pwcChars), c->cChars, c->cMaxGlyphs, QEMU_G2H(c->pwLogClust), QEMU_G2H(c->pCharProps), QEMU_G2H(c->pwOutGlyphs), QEMU_G2H(c->pOutGlyphProps), QEMU_G2H(c->pcGlyphs));
}

#endif

struct qemu_ScriptShape
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t pwcChars;
    uint64_t cChars;
    uint64_t cMaxGlyphs;
    uint64_t psa;
    uint64_t pwOutGlyphs;
    uint64_t pwLogClust;
    uint64_t psva;
    uint64_t pcGlyphs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptShape(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcChars, int cChars, int cMaxGlyphs, SCRIPT_ANALYSIS *psa, WORD *pwOutGlyphs, WORD *pwLogClust, SCRIPT_VISATTR *psva, int *pcGlyphs)
{
    struct qemu_ScriptShape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSHAPE);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.pwcChars = (uint64_t)pwcChars;
    call.cChars = (uint64_t)cChars;
    call.cMaxGlyphs = (uint64_t)cMaxGlyphs;
    call.psa = (uint64_t)psa;
    call.pwOutGlyphs = (uint64_t)pwOutGlyphs;
    call.pwLogClust = (uint64_t)pwLogClust;
    call.psva = (uint64_t)psva;
    call.pcGlyphs = (uint64_t)pcGlyphs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptShape(struct qemu_syscall *call)
{
    struct qemu_ScriptShape *c = (struct qemu_ScriptShape *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptShape(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->pwcChars), c->cChars, c->cMaxGlyphs, QEMU_G2H(c->psa), QEMU_G2H(c->pwOutGlyphs), QEMU_G2H(c->pwLogClust), QEMU_G2H(c->psva), QEMU_G2H(c->pcGlyphs));
}

#endif

struct qemu_ScriptPlaceOpenType
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t psa;
    uint64_t tagScript;
    uint64_t tagLangSys;
    uint64_t rcRangeChars;
    uint64_t rpRangeProperties;
    uint64_t cRanges;
    uint64_t pwcChars;
    uint64_t pwLogClust;
    uint64_t pCharProps;
    uint64_t cChars;
    uint64_t pwGlyphs;
    uint64_t pGlyphProps;
    uint64_t cGlyphs;
    uint64_t piAdvance;
    uint64_t pGoffset;
    uint64_t pABC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptPlaceOpenType(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges, const WCHAR *pwcChars, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, int cChars, const WORD *pwGlyphs, const SCRIPT_GLYPHPROP *pGlyphProps, int cGlyphs, int *piAdvance, GOFFSET *pGoffset, ABC *pABC)
{
    struct qemu_ScriptPlaceOpenType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTPLACEOPENTYPE);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.psa = (uint64_t)psa;
    call.tagScript = (uint64_t)tagScript;
    call.tagLangSys = (uint64_t)tagLangSys;
    call.rcRangeChars = (uint64_t)rcRangeChars;
    call.rpRangeProperties = (uint64_t)rpRangeProperties;
    call.cRanges = (uint64_t)cRanges;
    call.pwcChars = (uint64_t)pwcChars;
    call.pwLogClust = (uint64_t)pwLogClust;
    call.pCharProps = (uint64_t)pCharProps;
    call.cChars = (uint64_t)cChars;
    call.pwGlyphs = (uint64_t)pwGlyphs;
    call.pGlyphProps = (uint64_t)pGlyphProps;
    call.cGlyphs = (uint64_t)cGlyphs;
    call.piAdvance = (uint64_t)piAdvance;
    call.pGoffset = (uint64_t)pGoffset;
    call.pABC = (uint64_t)pABC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ScriptPlaceOpenType to Wine headers? */
extern HRESULT WINAPI ScriptPlaceOpenType(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges, const WCHAR *pwcChars, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, int cChars, const WORD *pwGlyphs, const SCRIPT_GLYPHPROP *pGlyphProps, int cGlyphs, int *piAdvance, GOFFSET *pGoffset, ABC *pABC);
void qemu_ScriptPlaceOpenType(struct qemu_syscall *call)
{
    struct qemu_ScriptPlaceOpenType *c = (struct qemu_ScriptPlaceOpenType *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptPlaceOpenType(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->psa), c->tagScript, c->tagLangSys, QEMU_G2H(c->rcRangeChars), QEMU_G2H(c->rpRangeProperties), c->cRanges, QEMU_G2H(c->pwcChars), QEMU_G2H(c->pwLogClust), QEMU_G2H(c->pCharProps), c->cChars, QEMU_G2H(c->pwGlyphs), QEMU_G2H(c->pGlyphProps), c->cGlyphs, QEMU_G2H(c->piAdvance), QEMU_G2H(c->pGoffset), QEMU_G2H(c->pABC));
}

#endif

struct qemu_ScriptPlace
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t pwGlyphs;
    uint64_t cGlyphs;
    uint64_t psva;
    uint64_t psa;
    uint64_t piAdvance;
    uint64_t pGoffset;
    uint64_t pABC;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptPlace(HDC hdc, SCRIPT_CACHE *psc, const WORD *pwGlyphs, int cGlyphs, const SCRIPT_VISATTR *psva, SCRIPT_ANALYSIS *psa, int *piAdvance, GOFFSET *pGoffset, ABC *pABC)
{
    struct qemu_ScriptPlace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTPLACE);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.pwGlyphs = (uint64_t)pwGlyphs;
    call.cGlyphs = (uint64_t)cGlyphs;
    call.psva = (uint64_t)psva;
    call.psa = (uint64_t)psa;
    call.piAdvance = (uint64_t)piAdvance;
    call.pGoffset = (uint64_t)pGoffset;
    call.pABC = (uint64_t)pABC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptPlace(struct qemu_syscall *call)
{
    struct qemu_ScriptPlace *c = (struct qemu_ScriptPlace *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptPlace(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->pwGlyphs), c->cGlyphs, QEMU_G2H(c->psva), QEMU_G2H(c->psa), QEMU_G2H(c->piAdvance), QEMU_G2H(c->pGoffset), QEMU_G2H(c->pABC));
}

#endif

struct qemu_ScriptGetCMap
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t pwcInChars;
    uint64_t cChars;
    uint64_t dwFlags;
    uint64_t pwOutGlyphs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetCMap(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcInChars, int cChars, DWORD dwFlags, WORD *pwOutGlyphs)
{
    struct qemu_ScriptGetCMap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETCMAP);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.pwcInChars = (uint64_t)pwcInChars;
    call.cChars = (uint64_t)cChars;
    call.dwFlags = (uint64_t)dwFlags;
    call.pwOutGlyphs = (uint64_t)pwOutGlyphs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetCMap(struct qemu_syscall *call)
{
    struct qemu_ScriptGetCMap *c = (struct qemu_ScriptGetCMap *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetCMap(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->pwcInChars), c->cChars, c->dwFlags, QEMU_G2H(c->pwOutGlyphs));
}

#endif

struct qemu_ScriptTextOut
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t x;
    uint64_t y;
    uint64_t fuOptions;
    uint64_t lprc;
    uint64_t psa;
    uint64_t pwcReserved;
    uint64_t iReserved;
    uint64_t pwGlyphs;
    uint64_t cGlyphs;
    uint64_t piAdvance;
    uint64_t piJustify;
    uint64_t pGoffset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptTextOut(const HDC hdc, SCRIPT_CACHE *psc, int x, int y, UINT fuOptions, const RECT *lprc, const SCRIPT_ANALYSIS *psa, const WCHAR *pwcReserved, int iReserved, const WORD *pwGlyphs, int cGlyphs, const int *piAdvance, const int *piJustify, const GOFFSET *pGoffset)
{
    struct qemu_ScriptTextOut call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTTEXTOUT);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;
    call.fuOptions = (uint64_t)fuOptions;
    call.lprc = (uint64_t)lprc;
    call.psa = (uint64_t)psa;
    call.pwcReserved = (uint64_t)pwcReserved;
    call.iReserved = (uint64_t)iReserved;
    call.pwGlyphs = (uint64_t)pwGlyphs;
    call.cGlyphs = (uint64_t)cGlyphs;
    call.piAdvance = (uint64_t)piAdvance;
    call.piJustify = (uint64_t)piJustify;
    call.pGoffset = (uint64_t)pGoffset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptTextOut(struct qemu_syscall *call)
{
    struct qemu_ScriptTextOut *c = (struct qemu_ScriptTextOut *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptTextOut((HDC)c->hdc, QEMU_G2H(c->psc), c->x, c->y, c->fuOptions, QEMU_G2H(c->lprc), QEMU_G2H(c->psa), QEMU_G2H(c->pwcReserved), c->iReserved, QEMU_G2H(c->pwGlyphs), c->cGlyphs, QEMU_G2H(c->piAdvance), QEMU_G2H(c->piJustify), QEMU_G2H(c->pGoffset));
}

#endif

struct qemu_ScriptCacheGetHeight
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptCacheGetHeight(HDC hdc, SCRIPT_CACHE *psc, LONG *height)
{
    struct qemu_ScriptCacheGetHeight call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTCACHEGETHEIGHT);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.height = (uint64_t)height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptCacheGetHeight(struct qemu_syscall *call)
{
    struct qemu_ScriptCacheGetHeight *c = (struct qemu_ScriptCacheGetHeight *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptCacheGetHeight(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->height));
}

#endif

struct qemu_ScriptGetGlyphABCWidth
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t glyph;
    uint64_t abc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetGlyphABCWidth(HDC hdc, SCRIPT_CACHE *psc, WORD glyph, ABC *abc)
{
    struct qemu_ScriptGetGlyphABCWidth call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETGLYPHABCWIDTH);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.glyph = (uint64_t)glyph;
    call.abc = (uint64_t)abc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetGlyphABCWidth(struct qemu_syscall *call)
{
    struct qemu_ScriptGetGlyphABCWidth *c = (struct qemu_ScriptGetGlyphABCWidth *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetGlyphABCWidth(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), c->glyph, QEMU_G2H(c->abc));
}

#endif

struct qemu_ScriptLayout
{
    struct qemu_syscall super;
    uint64_t runs;
    uint64_t level;
    uint64_t vistolog;
    uint64_t logtovis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptLayout(int runs, const BYTE *level, int *vistolog, int *logtovis)
{
    struct qemu_ScriptLayout call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTLAYOUT);
    call.runs = (uint64_t)runs;
    call.level = (uint64_t)level;
    call.vistolog = (uint64_t)vistolog;
    call.logtovis = (uint64_t)logtovis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptLayout(struct qemu_syscall *call)
{
    struct qemu_ScriptLayout *c = (struct qemu_ScriptLayout *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptLayout(c->runs, QEMU_G2H(c->level), QEMU_G2H(c->vistolog), QEMU_G2H(c->logtovis));
}

#endif

struct qemu_ScriptStringGetLogicalWidths
{
    struct qemu_syscall super;
    uint64_t ssa;
    uint64_t piDx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringGetLogicalWidths(SCRIPT_STRING_ANALYSIS ssa, int *piDx)
{
    struct qemu_ScriptStringGetLogicalWidths call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGGETLOGICALWIDTHS);
    call.ssa = (uint64_t)ssa;
    call.piDx = (uint64_t)piDx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringGetLogicalWidths(struct qemu_syscall *call)
{
    struct qemu_ScriptStringGetLogicalWidths *c = (struct qemu_ScriptStringGetLogicalWidths *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScriptStringGetLogicalWidths(QEMU_G2H(c->ssa), QEMU_G2H(c->piDx));
}

#endif

struct qemu_ScriptStringValidate
{
    struct qemu_syscall super;
    uint64_t ssa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringValidate(SCRIPT_STRING_ANALYSIS ssa)
{
    struct qemu_ScriptStringValidate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGVALIDATE);
    call.ssa = (uint64_t)ssa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringValidate(struct qemu_syscall *call)
{
    struct qemu_ScriptStringValidate *c = (struct qemu_ScriptStringValidate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScriptStringValidate(QEMU_G2H(c->ssa));
}

#endif

struct qemu_ScriptString_pSize
{
    struct qemu_syscall super;
    uint64_t ssa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const SIZE * WINAPI ScriptString_pSize(SCRIPT_STRING_ANALYSIS ssa)
{
    struct qemu_ScriptString_pSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRING_PSIZE);
    call.ssa = (uint64_t)ssa;

    qemu_syscall(&call.super);

    return (const SIZE *)call.super.iret;
}

#else

void qemu_ScriptString_pSize(struct qemu_syscall *call)
{
    struct qemu_ScriptString_pSize *c = (struct qemu_ScriptString_pSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(ScriptString_pSize(QEMU_G2H(c->ssa)));
}

#endif

struct qemu_ScriptString_pLogAttr
{
    struct qemu_syscall super;
    uint64_t ssa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const SCRIPT_LOGATTR * WINAPI ScriptString_pLogAttr(SCRIPT_STRING_ANALYSIS ssa)
{
    struct qemu_ScriptString_pLogAttr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRING_PLOGATTR);
    call.ssa = (uint64_t)ssa;

    qemu_syscall(&call.super);

    return (const SCRIPT_LOGATTR *)call.super.iret;
}

#else

void qemu_ScriptString_pLogAttr(struct qemu_syscall *call)
{
    struct qemu_ScriptString_pLogAttr *c = (struct qemu_ScriptString_pLogAttr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(ScriptString_pLogAttr(QEMU_G2H(c->ssa)));
}

#endif

struct qemu_ScriptString_pcOutChars
{
    struct qemu_syscall super;
    uint64_t ssa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const int * WINAPI ScriptString_pcOutChars(SCRIPT_STRING_ANALYSIS ssa)
{
    struct qemu_ScriptString_pcOutChars call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRING_PCOUTCHARS);
    call.ssa = (uint64_t)ssa;

    qemu_syscall(&call.super);

    return (const int *)call.super.iret;
}

#else

void qemu_ScriptString_pcOutChars(struct qemu_syscall *call)
{
    struct qemu_ScriptString_pcOutChars *c = (struct qemu_ScriptString_pcOutChars *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(ScriptString_pcOutChars(QEMU_G2H(c->ssa)));
}

#endif

struct qemu_ScriptStringGetOrder
{
    struct qemu_syscall super;
    uint64_t ssa;
    uint64_t order;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringGetOrder(SCRIPT_STRING_ANALYSIS ssa, UINT *order)
{
    struct qemu_ScriptStringGetOrder call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGGETORDER);
    call.ssa = (uint64_t)ssa;
    call.order = (uint64_t)order;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringGetOrder(struct qemu_syscall *call)
{
    struct qemu_ScriptStringGetOrder *c = (struct qemu_ScriptStringGetOrder *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptStringGetOrder(QEMU_G2H(c->ssa), QEMU_G2H(c->order));
}

#endif

struct qemu_ScriptGetLogicalWidths
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t nbchars;
    uint64_t nbglyphs;
    uint64_t advances;
    uint64_t log_clust;
    uint64_t sva;
    uint64_t widths;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetLogicalWidths(const SCRIPT_ANALYSIS *sa, int nbchars, int nbglyphs, const int *advances, const WORD *log_clust, const SCRIPT_VISATTR *sva, int *widths)
{
    struct qemu_ScriptGetLogicalWidths call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETLOGICALWIDTHS);
    call.sa = (uint64_t)sa;
    call.nbchars = (uint64_t)nbchars;
    call.nbglyphs = (uint64_t)nbglyphs;
    call.advances = (uint64_t)advances;
    call.log_clust = (uint64_t)log_clust;
    call.sva = (uint64_t)sva;
    call.widths = (uint64_t)widths;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetLogicalWidths(struct qemu_syscall *call)
{
    struct qemu_ScriptGetLogicalWidths *c = (struct qemu_ScriptGetLogicalWidths *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetLogicalWidths(QEMU_G2H(c->sa), c->nbchars, c->nbglyphs, QEMU_G2H(c->advances), QEMU_G2H(c->log_clust), QEMU_G2H(c->sva), QEMU_G2H(c->widths));
}

#endif

struct qemu_ScriptApplyLogicalWidth
{
    struct qemu_syscall super;
    uint64_t dx;
    uint64_t num_chars;
    uint64_t num_glyphs;
    uint64_t log_clust;
    uint64_t sva;
    uint64_t advance;
    uint64_t sa;
    uint64_t abc;
    uint64_t justify;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptApplyLogicalWidth(const int *dx, int num_chars, int num_glyphs, const WORD *log_clust, const SCRIPT_VISATTR *sva, const int *advance, const SCRIPT_ANALYSIS *sa, ABC *abc, int *justify)
{
    struct qemu_ScriptApplyLogicalWidth call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTAPPLYLOGICALWIDTH);
    call.dx = (uint64_t)dx;
    call.num_chars = (uint64_t)num_chars;
    call.num_glyphs = (uint64_t)num_glyphs;
    call.log_clust = (uint64_t)log_clust;
    call.sva = (uint64_t)sva;
    call.advance = (uint64_t)advance;
    call.sa = (uint64_t)sa;
    call.abc = (uint64_t)abc;
    call.justify = (uint64_t)justify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptApplyLogicalWidth(struct qemu_syscall *call)
{
    struct qemu_ScriptApplyLogicalWidth *c = (struct qemu_ScriptApplyLogicalWidth *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScriptApplyLogicalWidth(QEMU_G2H(c->dx), c->num_chars, c->num_glyphs, QEMU_G2H(c->log_clust), QEMU_G2H(c->sva), QEMU_G2H(c->advance), QEMU_G2H(c->sa), QEMU_G2H(c->abc), QEMU_G2H(c->justify));
}

#endif

struct qemu_ScriptJustify
{
    struct qemu_syscall super;
    uint64_t sva;
    uint64_t advance;
    uint64_t num_glyphs;
    uint64_t dx;
    uint64_t min_kashida;
    uint64_t justify;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptJustify(const SCRIPT_VISATTR *sva, const int *advance, int num_glyphs, int dx, int min_kashida, int *justify)
{
    struct qemu_ScriptJustify call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTJUSTIFY);
    call.sva = (uint64_t)sva;
    call.advance = (uint64_t)advance;
    call.num_glyphs = (uint64_t)num_glyphs;
    call.dx = (uint64_t)dx;
    call.min_kashida = (uint64_t)min_kashida;
    call.justify = (uint64_t)justify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptJustify(struct qemu_syscall *call)
{
    struct qemu_ScriptJustify *c = (struct qemu_ScriptJustify *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScriptJustify(QEMU_G2H(c->sva), QEMU_G2H(c->advance), c->num_glyphs, c->dx, c->min_kashida, QEMU_G2H(c->justify));
}

#endif

struct qemu_ScriptGetFontScriptTags
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t psa;
    uint64_t cMaxTags;
    uint64_t pScriptTags;
    uint64_t pcTags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetFontScriptTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, int cMaxTags, OPENTYPE_TAG *pScriptTags, int *pcTags)
{
    struct qemu_ScriptGetFontScriptTags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTSCRIPTTAGS);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.psa = (uint64_t)psa;
    call.cMaxTags = (uint64_t)cMaxTags;
    call.pScriptTags = (uint64_t)pScriptTags;
    call.pcTags = (uint64_t)pcTags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ScriptGetFontScriptTags to Wine headers? */
extern HRESULT WINAPI ScriptGetFontScriptTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, int cMaxTags, OPENTYPE_TAG *pScriptTags, int *pcTags);
void qemu_ScriptGetFontScriptTags(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontScriptTags *c = (struct qemu_ScriptGetFontScriptTags *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetFontScriptTags(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->psa), c->cMaxTags, QEMU_G2H(c->pScriptTags), QEMU_G2H(c->pcTags));
}

#endif

struct qemu_ScriptGetFontLanguageTags
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t psa;
    uint64_t tagScript;
    uint64_t cMaxTags;
    uint64_t pLangSysTags;
    uint64_t pcTags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetFontLanguageTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, int cMaxTags, OPENTYPE_TAG *pLangSysTags, int *pcTags)
{
    struct qemu_ScriptGetFontLanguageTags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTLANGUAGETAGS);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.psa = (uint64_t)psa;
    call.tagScript = (uint64_t)tagScript;
    call.cMaxTags = (uint64_t)cMaxTags;
    call.pLangSysTags = (uint64_t)pLangSysTags;
    call.pcTags = (uint64_t)pcTags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ScriptGetFontLanguageTags to Wine headers? */
extern HRESULT WINAPI ScriptGetFontLanguageTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, int cMaxTags, OPENTYPE_TAG *pLangSysTags, int *pcTags);
void qemu_ScriptGetFontLanguageTags(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontLanguageTags *c = (struct qemu_ScriptGetFontLanguageTags *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetFontLanguageTags(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->psa), c->tagScript, c->cMaxTags, QEMU_G2H(c->pLangSysTags), QEMU_G2H(c->pcTags));
}

#endif

struct qemu_ScriptGetFontFeatureTags
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t psc;
    uint64_t psa;
    uint64_t tagScript;
    uint64_t tagLangSys;
    uint64_t cMaxTags;
    uint64_t pFeatureTags;
    uint64_t pcTags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptGetFontFeatureTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int cMaxTags, OPENTYPE_TAG *pFeatureTags, int *pcTags)
{
    struct qemu_ScriptGetFontFeatureTags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTFEATURETAGS);
    call.hdc = (uint64_t)hdc;
    call.psc = (uint64_t)psc;
    call.psa = (uint64_t)psa;
    call.tagScript = (uint64_t)tagScript;
    call.tagLangSys = (uint64_t)tagLangSys;
    call.cMaxTags = (uint64_t)cMaxTags;
    call.pFeatureTags = (uint64_t)pFeatureTags;
    call.pcTags = (uint64_t)pcTags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ScriptGetFontFeatureTags to Wine headers? */
extern HRESULT WINAPI ScriptGetFontFeatureTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int cMaxTags, OPENTYPE_TAG *pFeatureTags, int *pcTags);
void qemu_ScriptGetFontFeatureTags(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontFeatureTags *c = (struct qemu_ScriptGetFontFeatureTags *)call;
    WINE_TRACE("\n");
    c->super.iret = ScriptGetFontFeatureTags(QEMU_G2H(c->hdc), QEMU_G2H(c->psc), QEMU_G2H(c->psa), c->tagScript, c->tagLangSys, c->cMaxTags, QEMU_G2H(c->pFeatureTags), QEMU_G2H(c->pcTags));
}

#endif

