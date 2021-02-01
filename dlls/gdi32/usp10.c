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

#include "thunk/qemu_usp10.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <wine/list.h>
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
    call.psc = (ULONG_PTR)psc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_SCRIPT_CACHE
{
    SCRIPT_CACHE host;
    struct list entry;
    DWORD refcount;
};

/* The Wine library uses a list, but it has a different data structure. Since we just have
 * pointers we could also use an rbtree quite easily. If this makes sense depends on the
 * amount of caches the average app has. */
static struct list cache_list = LIST_INIT(cache_list);
static CRITICAL_SECTION cache_cs = {0, -1, 0, 0, 0, 0};

static void SCRIPT_CACHE_create(qemu_ptr *guest, SCRIPT_CACHE host)
{
    struct qemu_SCRIPT_CACHE *cache;
    if (!host)
        return;

    EnterCriticalSection(&cache_cs);
    LIST_FOR_EACH_ENTRY(cache, &cache_list, struct qemu_SCRIPT_CACHE, entry)
    {
        if (cache->host == host)
        {
            cache->refcount++;
            LeaveCriticalSection(&cache_cs);

            WINE_TRACE("Found existing wrapper %p for host cache %p.\n", cache, host);
            *guest = (ULONG_PTR)cache;

            return;
        }
    }

    cache = HeapAlloc(GetProcessHeap(), 0, sizeof(*cache));
    cache->host = host;
    cache->refcount = 1;
    list_add_head(&cache_list, &cache->entry);
    WINE_TRACE("Created cache wrapper %p for host cache %p.\n", cache, host);

    LeaveCriticalSection(&cache_cs);

    *guest = (ULONG_PTR)cache;
}

void qemu_ScriptFreeCache(struct qemu_syscall *call)
{
    struct qemu_ScriptFreeCache *c = (struct qemu_ScriptFreeCache *)call;
    qemu_ptr *ptr32;
    struct qemu_SCRIPT_CACHE *wrapper;
    SCRIPT_CACHE host;
    WINE_TRACE("\n");

    /* Note: Functions that create the cache sometimes do not touch it, e.g. if they fail. In this
     * case we should not touch the guest pointer either. So my attempt to have a general wrapper
     * function that handles the translation or allocation in one go before calling the host usp10
     * functions was vetoed by the tests. */
#if HOST_BIT == GUEST_BIT
    c->super.iret = pScriptFreeCache(QEMU_G2H(c->psc));
#endif

    c->super.iret = S_OK;
    ptr32 = QEMU_G2H(c->psc);
    if (!ptr32 || !*ptr32)
        return;

    wrapper = QEMU_G2H((uint64_t)*ptr32);
    host = wrapper->host; /* Protect against zeroing if we have more than one ref. */
    c->super.iret = pScriptFreeCache(&host);
    if (FAILED(c->super.iret))
        WINE_ERR("Failed to free host cache %p.\n", wrapper->host);

    EnterCriticalSection(&cache_cs);
    if (!--wrapper->refcount)
    {
        list_remove(&wrapper->entry);
        WINE_TRACE("Destroyed cache wrapper %p, host cache %p.\n", wrapper, wrapper->host);
        HeapFree(GetProcessHeap(), 0, wrapper);
    }
    LeaveCriticalSection(&cache_cs);

    *ptr32 = 0;
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
    call.props = (ULONG_PTR)props;
    call.num = (ULONG_PTR)num;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret) && props)
        *props = (void *)(ULONG_PTR)call.props;

    return call.super.iret;
}

#else

void qemu_ScriptGetProperties(struct qemu_syscall *call)
{
    struct qemu_ScriptGetProperties *c = (struct qemu_ScriptGetProperties *)call;
    const SCRIPT_PROPERTIES **props;
    SCRIPT_PROPERTIES *copy;
    static qemu_ptr *guest_props;
    int num, i;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    c->super.iret = pScriptGetProperties(QEMU_G2H(c->props), QEMU_G2H(c->num));
    return;
#endif

    if (!c->props)
    {
        c->super.iret = pScriptGetProperties(NULL, QEMU_G2H(c->num));
        return;
    }

    c->super.iret = pScriptGetProperties(&props, &num);
    if (FAILED(c->super.iret))
        return;

    /* SCRIPT_PROPERTIES is compatible. But we have to repack the pointers,
     * and since this is static const data in the host lib we have to copy it
     * below 32 bit. */
    if (!guest_props)
    {
        guest_props = HeapAlloc(GetProcessHeap(), 0, num * sizeof(*guest_props));
        if (!guest_props)
        {
            WINE_WARN("Out of memory\n");
            c->super.iret = E_OUTOFMEMORY;
            return;
        }
        copy = HeapAlloc(GetProcessHeap(), 0, num * sizeof(*copy));
        if (!copy)
        {
            WINE_WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, guest_props);
            guest_props = NULL;
            c->super.iret = E_OUTOFMEMORY;
        }

        for (i = 0; i < num; ++i)
        {
            copy[i] = *props[i];
            guest_props[i] = (ULONG_PTR)&copy[i];
        }
    }

    c->props = QEMU_H2G(guest_props);
    if (c->num)
        *(int *)(QEMU_G2H(c->num)) = num;
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
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.sfp = (ULONG_PTR)sfp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetFontProperties(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontProperties *c = (struct qemu_ScriptGetFontProperties *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptGetFontProperties(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->sfp));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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
    call.locale = locale;
    call.sds = (ULONG_PTR)sds;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptRecordDigitSubstitution(struct qemu_syscall *call)
{
    struct qemu_ScriptRecordDigitSubstitution *c = (struct qemu_ScriptRecordDigitSubstitution *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptRecordDigitSubstitution(c->locale, QEMU_G2H(c->sds));
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

WINBASEAPI HRESULT WINAPI ScriptApplyDigitSubstitution(const SCRIPT_DIGITSUBSTITUTE *sds, SCRIPT_CONTROL *sc,
        SCRIPT_STATE *ss)
{
    struct qemu_ScriptApplyDigitSubstitution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTAPPLYDIGITSUBSTITUTION);
    call.sds = (ULONG_PTR)sds;
    call.sc = (ULONG_PTR)sc;
    call.ss = (ULONG_PTR)ss;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptApplyDigitSubstitution(struct qemu_syscall *call)
{
    struct qemu_ScriptApplyDigitSubstitution *c = (struct qemu_ScriptApplyDigitSubstitution *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptApplyDigitSubstitution(QEMU_G2H(c->sds), QEMU_G2H(c->sc), QEMU_G2H(c->ss));
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

WINBASEAPI HRESULT WINAPI ScriptItemizeOpenType(const WCHAR *pwcInChars, int cInChars, int cMaxItems,
        const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems,
        OPENTYPE_TAG *pScriptTags, int *pcItems)
{
    struct qemu_ScriptItemizeOpenType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTITEMIZEOPENTYPE);
    call.pwcInChars = (ULONG_PTR)pwcInChars;
    call.cInChars = cInChars;
    call.cMaxItems = cMaxItems;
    call.psControl = (ULONG_PTR)psControl;
    call.psState = (ULONG_PTR)psState;
    call.pItems = (ULONG_PTR)pItems;
    call.pScriptTags = (ULONG_PTR)pScriptTags;
    call.pcItems = (ULONG_PTR)pcItems;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptItemizeOpenType(struct qemu_syscall *call)
{
    struct qemu_ScriptItemizeOpenType *c = (struct qemu_ScriptItemizeOpenType *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptItemizeOpenType(QEMU_G2H(c->pwcInChars), c->cInChars, c->cMaxItems, QEMU_G2H(c->psControl),
            QEMU_G2H(c->psState), QEMU_G2H(c->pItems), QEMU_G2H(c->pScriptTags), QEMU_G2H(c->pcItems));
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

WINBASEAPI HRESULT WINAPI ScriptItemize(const WCHAR *pwcInChars, int cInChars, int cMaxItems,
        const SCRIPT_CONTROL *psControl, const SCRIPT_STATE *psState, SCRIPT_ITEM *pItems, int *pcItems)
{
    struct qemu_ScriptItemize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTITEMIZE);
    call.pwcInChars = (ULONG_PTR)pwcInChars;
    call.cInChars = cInChars;
    call.cMaxItems = cMaxItems;
    call.psControl = (ULONG_PTR)psControl;
    call.psState = (ULONG_PTR)psState;
    call.pItems = (ULONG_PTR)pItems;
    call.pcItems = (ULONG_PTR)pcItems;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptItemize(struct qemu_syscall *call)
{
    struct qemu_ScriptItemize *c = (struct qemu_ScriptItemize *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptItemize(QEMU_G2H(c->pwcInChars), c->cInChars, c->cMaxItems, QEMU_G2H(c->psControl),
            QEMU_G2H(c->psState), QEMU_G2H(c->pItems), QEMU_G2H(c->pcItems));
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

WINBASEAPI HRESULT WINAPI ScriptStringAnalyse(HDC hdc, const void *pString, int cString, int cGlyphs,
        int iCharset, DWORD dwFlags, int iReqWidth, SCRIPT_CONTROL *psControl, SCRIPT_STATE *psState,
        const int *piDx, SCRIPT_TABDEF *pTabdef, const BYTE *pbInClass, SCRIPT_STRING_ANALYSIS *pssa)
{
    struct qemu_ScriptStringAnalyse call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGANALYSE);
    call.hdc = (ULONG_PTR)hdc;
    call.pString = (ULONG_PTR)pString;
    call.cString = cString;
    call.cGlyphs = cGlyphs;
    call.iCharset = iCharset;
    call.dwFlags = dwFlags;
    call.iReqWidth = iReqWidth;
    call.psControl = (ULONG_PTR)psControl;
    call.psState = (ULONG_PTR)psState;
    call.piDx = (ULONG_PTR)piDx;
    call.pTabdef = (ULONG_PTR)pTabdef;
    call.pbInClass = (ULONG_PTR)pbInClass;
    call.pssa = (ULONG_PTR)pssa;

    qemu_syscall(&call.super);
    if (SUCCEEDED(call.super.iret))
        *pssa = (SCRIPT_STRING_ANALYSIS)(ULONG_PTR)call.pssa;

    return call.super.iret;
}

#else

void qemu_ScriptStringAnalyse(struct qemu_syscall *call)
{
    struct qemu_ScriptStringAnalyse *c = (struct qemu_ScriptStringAnalyse *)call;
    SCRIPT_STRING_ANALYSIS host;
    SCRIPT_TABDEF stack, *tabdef = &stack;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    tabdef = QEMU_G2H(c->pTabdef);
#else
    if (c->pTabdef)
        SCRIPT_TABDEF_g2h(tabdef, QEMU_G2H(c->pTabdef));
    else
        tabdef = NULL;
#endif

    c->super.iret = pScriptStringAnalyse(QEMU_G2H(c->hdc), QEMU_G2H(c->pString), c->cString, c->cGlyphs,
            c->iCharset, c->dwFlags, c->iReqWidth, QEMU_G2H(c->psControl), QEMU_G2H(c->psState),
            QEMU_G2H(c->piDx), tabdef, QEMU_G2H(c->pbInClass), c->pssa ? &host : NULL);
    c->pssa = QEMU_H2G(host);
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

WINBASEAPI HRESULT WINAPI ScriptStringOut(SCRIPT_STRING_ANALYSIS ssa, int iX, int iY, UINT uOptions, const RECT *prc,
        int iMinSel, int iMaxSel, BOOL fDisabled)
{
    struct qemu_ScriptStringOut call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGOUT);
    call.ssa = (ULONG_PTR)ssa;
    call.iX = iX;
    call.iY = iY;
    call.uOptions = uOptions;
    call.prc = (ULONG_PTR)prc;
    call.iMinSel = iMinSel;
    call.iMaxSel = iMaxSel;
    call.fDisabled = fDisabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringOut(struct qemu_syscall *call)
{
    struct qemu_ScriptStringOut *c = (struct qemu_ScriptStringOut *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptStringOut(QEMU_G2H(c->ssa), c->iX, c->iY, c->uOptions, QEMU_G2H(c->prc), c->iMinSel,
            c->iMaxSel, c->fDisabled);
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
    call.ssa = (ULONG_PTR)ssa;
    call.icp = icp;
    call.fTrailing = fTrailing;
    call.pX = (ULONG_PTR)pX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringCPtoX(struct qemu_syscall *call)
{
    struct qemu_ScriptStringCPtoX *c = (struct qemu_ScriptStringCPtoX *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptStringCPtoX(QEMU_G2H(c->ssa), c->icp, c->fTrailing, QEMU_G2H(c->pX));
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
    call.ssa = (ULONG_PTR)ssa;
    call.iX = iX;
    call.piCh = (ULONG_PTR)piCh;
    call.piTrailing = (ULONG_PTR)piTrailing;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringXtoCP(struct qemu_syscall *call)
{
    struct qemu_ScriptStringXtoCP *c = (struct qemu_ScriptStringXtoCP *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptStringXtoCP(QEMU_G2H(c->ssa), c->iX, QEMU_G2H(c->piCh), QEMU_G2H(c->piTrailing));
}

#endif

struct qemu_ScriptStringFree
{
    struct qemu_syscall super;
    uint64_t pssa;
    uint64_t has_ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ScriptStringFree(SCRIPT_STRING_ANALYSIS *pssa)
{
    struct qemu_ScriptStringFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSTRINGFREE);
    call.pssa = (ULONG_PTR)(pssa ? *pssa : NULL);
    call.has_ptr = !!pssa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringFree(struct qemu_syscall *call)
{
    struct qemu_ScriptStringFree *c = (struct qemu_ScriptStringFree *)call;
    SCRIPT_STRING_ANALYSIS ptr;
    WINE_TRACE("\n");

    ptr = QEMU_G2H(c->pssa);
    c->super.iret = pScriptStringFree(c->has_ptr ? &ptr : NULL);
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

WINBASEAPI HRESULT WINAPI ScriptCPtoX(int iCP, BOOL fTrailing, int cChars, int cGlyphs, const WORD *pwLogClust,
        const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piX)
{
    struct qemu_ScriptCPtoX call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTCPTOX);
    call.iCP = (ULONG_PTR)iCP;
    call.fTrailing = fTrailing;
    call.cChars = cChars;
    call.cGlyphs = cGlyphs;
    call.pwLogClust = (ULONG_PTR)pwLogClust;
    call.psva = (ULONG_PTR)psva;
    call.piAdvance = (ULONG_PTR)piAdvance;
    call.psa = (ULONG_PTR)psa;
    call.piX = (ULONG_PTR)piX;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptCPtoX(struct qemu_syscall *call)
{
    struct qemu_ScriptCPtoX *c = (struct qemu_ScriptCPtoX *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptCPtoX(c->iCP, c->fTrailing, c->cChars, c->cGlyphs, QEMU_G2H(c->pwLogClust),
            QEMU_G2H(c->psva), QEMU_G2H(c->piAdvance), QEMU_G2H(c->psa), QEMU_G2H(c->piX));
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

WINBASEAPI HRESULT WINAPI ScriptXtoCP(int iX, int cChars, int cGlyphs, const WORD *pwLogClust,
        const SCRIPT_VISATTR *psva, const int *piAdvance, const SCRIPT_ANALYSIS *psa, int *piCP, int *piTrailing)
{
    struct qemu_ScriptXtoCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTXTOCP);
    call.iX = iX;
    call.cChars = cChars;
    call.cGlyphs = cGlyphs;
    call.pwLogClust = (ULONG_PTR)pwLogClust;
    call.psva = (ULONG_PTR)psva;
    call.piAdvance = (ULONG_PTR)piAdvance;
    call.psa = (ULONG_PTR)psa;
    call.piCP = (ULONG_PTR)piCP;
    call.piTrailing = (ULONG_PTR)piTrailing;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptXtoCP(struct qemu_syscall *call)
{
    struct qemu_ScriptXtoCP *c = (struct qemu_ScriptXtoCP *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptXtoCP(c->iX, c->cChars, c->cGlyphs, QEMU_G2H(c->pwLogClust), QEMU_G2H(c->psva),
            QEMU_G2H(c->piAdvance), QEMU_G2H(c->psa), QEMU_G2H(c->piCP), QEMU_G2H(c->piTrailing));
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
    call.chars = (ULONG_PTR)chars;
    call.count = count;
    call.sa = (ULONG_PTR)sa;
    call.la = (ULONG_PTR)la;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptBreak(struct qemu_syscall *call)
{
    struct qemu_ScriptBreak *c = (struct qemu_ScriptBreak *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptBreak(QEMU_G2H(c->chars), c->count, QEMU_G2H(c->sa), QEMU_G2H(c->la));
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
    call.chars = (ULONG_PTR)chars;
    call.len = len;
    call.flag = flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptIsComplex(struct qemu_syscall *call)
{
    struct qemu_ScriptIsComplex *c = (struct qemu_ScriptIsComplex *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptIsComplex(QEMU_G2H(c->chars), c->len, c->flag);
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

WINBASEAPI HRESULT WINAPI ScriptShapeOpenType(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
        OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges,
        const WCHAR *pwcChars, int cChars, int cMaxGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps,
        WORD *pwOutGlyphs, SCRIPT_GLYPHPROP *pOutGlyphProps, int *pcGlyphs)
{
    struct qemu_ScriptShapeOpenType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSHAPEOPENTYPE);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.psa = (ULONG_PTR)psa;
    call.tagScript = tagScript;
    call.tagLangSys = tagLangSys;
    call.rcRangeChars = (ULONG_PTR)rcRangeChars;
    call.rpRangeProperties = (ULONG_PTR)rpRangeProperties;
    call.cRanges = cRanges;
    call.pwcChars = (ULONG_PTR)pwcChars;
    call.cChars = cChars;
    call.cMaxGlyphs = cMaxGlyphs;
    call.pwLogClust = (ULONG_PTR)pwLogClust;
    call.pCharProps = (ULONG_PTR)pCharProps;
    call.pwOutGlyphs = (ULONG_PTR)pwOutGlyphs;
    call.pOutGlyphProps = (ULONG_PTR)pOutGlyphProps;
    call.pcGlyphs = (ULONG_PTR)pcGlyphs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptShapeOpenType(struct qemu_syscall *call)
{
    struct qemu_ScriptShapeOpenType *c = (struct qemu_ScriptShapeOpenType *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    if (c->rpRangeProperties)
        WINE_FIXME("Translate TEXTRANGE_PROPERTIES\n");

    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptShapeOpenType(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->psa), c->tagScript, c->tagLangSys,
            QEMU_G2H(c->rcRangeChars), QEMU_G2H(c->rpRangeProperties), c->cRanges, QEMU_G2H(c->pwcChars), c->cChars,
            c->cMaxGlyphs, QEMU_G2H(c->pwLogClust), QEMU_G2H(c->pCharProps), QEMU_G2H(c->pwOutGlyphs),
            QEMU_G2H(c->pOutGlyphProps), QEMU_G2H(c->pcGlyphs));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptShape(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcChars, int cChars, int cMaxGlyphs,
        SCRIPT_ANALYSIS *psa, WORD *pwOutGlyphs, WORD *pwLogClust, SCRIPT_VISATTR *psva, int *pcGlyphs)
{
    struct qemu_ScriptShape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTSHAPE);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.pwcChars = (ULONG_PTR)pwcChars;
    call.cChars = cChars;
    call.cMaxGlyphs = cMaxGlyphs;
    call.psa = (ULONG_PTR)psa;
    call.pwOutGlyphs = (ULONG_PTR)pwOutGlyphs;
    call.pwLogClust = (ULONG_PTR)pwLogClust;
    call.psva = (ULONG_PTR)psva;
    call.pcGlyphs = (ULONG_PTR)pcGlyphs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptShape(struct qemu_syscall *call)
{
    struct qemu_ScriptShape *c = (struct qemu_ScriptShape *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptShape(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->pwcChars), c->cChars, c->cMaxGlyphs,
            QEMU_G2H(c->psa), QEMU_G2H(c->pwOutGlyphs), QEMU_G2H(c->pwLogClust), QEMU_G2H(c->psva),
            QEMU_G2H(c->pcGlyphs));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptPlaceOpenType(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, OPENTYPE_TAG tagScript,
        OPENTYPE_TAG tagLangSys, int *rcRangeChars, TEXTRANGE_PROPERTIES **rpRangeProperties, int cRanges,
        const WCHAR *pwcChars, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProps, int cChars, const WORD *pwGlyphs,
        const SCRIPT_GLYPHPROP *pGlyphProps, int cGlyphs, int *piAdvance, GOFFSET *pGoffset, ABC *pABC)
{
    struct qemu_ScriptPlaceOpenType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTPLACEOPENTYPE);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.psa = (ULONG_PTR)psa;
    call.tagScript = tagScript;
    call.tagLangSys = tagLangSys;
    call.rcRangeChars = (ULONG_PTR)rcRangeChars;
    call.rpRangeProperties = (ULONG_PTR)rpRangeProperties;
    call.cRanges = cRanges;
    call.pwcChars = (ULONG_PTR)pwcChars;
    call.pwLogClust = (ULONG_PTR)pwLogClust;
    call.pCharProps = (ULONG_PTR)pCharProps;
    call.cChars = cChars;
    call.pwGlyphs = (ULONG_PTR)pwGlyphs;
    call.pGlyphProps = (ULONG_PTR)pGlyphProps;
    call.cGlyphs = cGlyphs;
    call.piAdvance = (ULONG_PTR)piAdvance;
    call.pGoffset = (ULONG_PTR)pGoffset;
    call.pABC = (ULONG_PTR)pABC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptPlaceOpenType(struct qemu_syscall *call)
{
    struct qemu_ScriptPlaceOpenType *c = (struct qemu_ScriptPlaceOpenType *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    if (c->rpRangeProperties)
        WINE_FIXME("Translate TEXTRANGE_PROPERTIES\n");

    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptPlaceOpenType(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->psa),
            c->tagScript, c->tagLangSys, QEMU_G2H(c->rcRangeChars), QEMU_G2H(c->rpRangeProperties), c->cRanges,
            QEMU_G2H(c->pwcChars), QEMU_G2H(c->pwLogClust), QEMU_G2H(c->pCharProps), c->cChars, QEMU_G2H(c->pwGlyphs),
            QEMU_G2H(c->pGlyphProps), c->cGlyphs, QEMU_G2H(c->piAdvance), QEMU_G2H(c->pGoffset), QEMU_G2H(c->pABC));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptPlace(HDC hdc, SCRIPT_CACHE *psc, const WORD *pwGlyphs, int cGlyphs,
        const SCRIPT_VISATTR *psva, SCRIPT_ANALYSIS *psa, int *piAdvance, GOFFSET *pGoffset, ABC *pABC)
{
    struct qemu_ScriptPlace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTPLACE);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.pwGlyphs = (ULONG_PTR)pwGlyphs;
    call.cGlyphs = cGlyphs;
    call.psva = (ULONG_PTR)psva;
    call.psa = (ULONG_PTR)psa;
    call.piAdvance = (ULONG_PTR)piAdvance;
    call.pGoffset = (ULONG_PTR)pGoffset;
    call.pABC = (ULONG_PTR)pABC;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptPlace(struct qemu_syscall *call)
{
    struct qemu_ScriptPlace *c = (struct qemu_ScriptPlace *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptPlace(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->pwGlyphs), c->cGlyphs, QEMU_G2H(c->psva),
            QEMU_G2H(c->psa), QEMU_G2H(c->piAdvance), QEMU_G2H(c->pGoffset), QEMU_G2H(c->pABC));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptGetCMap(HDC hdc, SCRIPT_CACHE *psc, const WCHAR *pwcInChars, int cChars,
        DWORD dwFlags, WORD *pwOutGlyphs)
{
    struct qemu_ScriptGetCMap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETCMAP);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.pwcInChars = (ULONG_PTR)pwcInChars;
    call.cChars = cChars;
    call.dwFlags = dwFlags;
    call.pwOutGlyphs = (ULONG_PTR)pwOutGlyphs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetCMap(struct qemu_syscall *call)
{
    struct qemu_ScriptGetCMap *c = (struct qemu_ScriptGetCMap *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptGetCMap(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->pwcInChars), c->cChars,
            c->dwFlags, QEMU_G2H(c->pwOutGlyphs));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptTextOut(const HDC hdc, SCRIPT_CACHE *psc, int x, int y, UINT fuOptions,
        const RECT *lprc, const SCRIPT_ANALYSIS *psa, const WCHAR *pwcReserved, int iReserved, const WORD *pwGlyphs,
        int cGlyphs, const int *piAdvance, const int *piJustify, const GOFFSET *pGoffset)
{
    struct qemu_ScriptTextOut call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTTEXTOUT);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.x = x;
    call.y = y;
    call.fuOptions = fuOptions;
    call.lprc = (ULONG_PTR)lprc;
    call.psa = (ULONG_PTR)psa;
    call.pwcReserved = (ULONG_PTR)pwcReserved;
    call.iReserved = iReserved;
    call.pwGlyphs = (ULONG_PTR)pwGlyphs;
    call.cGlyphs = cGlyphs;
    call.piAdvance = (ULONG_PTR)piAdvance;
    call.piJustify = (ULONG_PTR)piJustify;
    call.pGoffset = (ULONG_PTR)pGoffset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptTextOut(struct qemu_syscall *call)
{
    struct qemu_ScriptTextOut *c = (struct qemu_ScriptTextOut *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;

    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptTextOut((HDC)c->hdc, cache, c->x, c->y, c->fuOptions,
            QEMU_G2H(c->lprc), QEMU_G2H(c->psa), QEMU_G2H(c->pwcReserved), c->iReserved, QEMU_G2H(c->pwGlyphs),
            c->cGlyphs, QEMU_G2H(c->piAdvance), QEMU_G2H(c->piJustify), QEMU_G2H(c->pGoffset));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.height = (ULONG_PTR)height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptCacheGetHeight(struct qemu_syscall *call)
{
    struct qemu_ScriptCacheGetHeight *c = (struct qemu_ScriptCacheGetHeight *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptCacheGetHeight(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->height));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.glyph = glyph;
    call.abc = (ULONG_PTR)abc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetGlyphABCWidth(struct qemu_syscall *call)
{
    struct qemu_ScriptGetGlyphABCWidth *c = (struct qemu_ScriptGetGlyphABCWidth *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptGetGlyphABCWidth(QEMU_G2H(c->hdc), cache, c->glyph, QEMU_G2H(c->abc));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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
    call.runs = runs;
    call.level = (ULONG_PTR)level;
    call.vistolog = (ULONG_PTR)vistolog;
    call.logtovis = (ULONG_PTR)logtovis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptLayout(struct qemu_syscall *call)
{
    struct qemu_ScriptLayout *c = (struct qemu_ScriptLayout *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptLayout(c->runs, QEMU_G2H(c->level), QEMU_G2H(c->vistolog), QEMU_G2H(c->logtovis));
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
    call.ssa = (ULONG_PTR)ssa;
    call.piDx = (ULONG_PTR)piDx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringGetLogicalWidths(struct qemu_syscall *call)
{
    struct qemu_ScriptStringGetLogicalWidths *c = (struct qemu_ScriptStringGetLogicalWidths *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = pScriptStringGetLogicalWidths(QEMU_G2H(c->ssa), QEMU_G2H(c->piDx));
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
    call.ssa = (ULONG_PTR)ssa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringValidate(struct qemu_syscall *call)
{
    struct qemu_ScriptStringValidate *c = (struct qemu_ScriptStringValidate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = pScriptStringValidate(QEMU_G2H(c->ssa));
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
    call.ssa = (ULONG_PTR)ssa;

    qemu_syscall(&call.super);

    return (const SIZE *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ScriptString_pSize(struct qemu_syscall *call)
{
    struct qemu_ScriptString_pSize *c = (struct qemu_ScriptString_pSize *)call;
    /* Note that the return SIZE is a struct consisting of two LONGs, nothing size_t related. */
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(pScriptString_pSize(QEMU_G2H(c->ssa)));
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
    call.ssa = (ULONG_PTR)ssa;

    qemu_syscall(&call.super);

    return (const SCRIPT_LOGATTR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ScriptString_pLogAttr(struct qemu_syscall *call)
{
    struct qemu_ScriptString_pLogAttr *c = (struct qemu_ScriptString_pLogAttr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(pScriptString_pLogAttr(QEMU_G2H(c->ssa)));
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
    call.ssa = (ULONG_PTR)ssa;

    qemu_syscall(&call.super);

    return (const int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ScriptString_pcOutChars(struct qemu_syscall *call)
{
    struct qemu_ScriptString_pcOutChars *c = (struct qemu_ScriptString_pcOutChars *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(pScriptString_pcOutChars(QEMU_G2H(c->ssa)));
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
    call.ssa = (ULONG_PTR)ssa;
    call.order = (ULONG_PTR)order;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptStringGetOrder(struct qemu_syscall *call)
{
    struct qemu_ScriptStringGetOrder *c = (struct qemu_ScriptStringGetOrder *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptStringGetOrder(QEMU_G2H(c->ssa), QEMU_G2H(c->order));
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

WINBASEAPI HRESULT WINAPI ScriptGetLogicalWidths(const SCRIPT_ANALYSIS *sa, int nbchars, int nbglyphs,
        const int *advances, const WORD *log_clust, const SCRIPT_VISATTR *sva, int *widths)
{
    struct qemu_ScriptGetLogicalWidths call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETLOGICALWIDTHS);
    call.sa = (ULONG_PTR)sa;
    call.nbchars = (ULONG_PTR)nbchars;
    call.nbglyphs = nbglyphs;
    call.advances = (ULONG_PTR)advances;
    call.log_clust = (ULONG_PTR)log_clust;
    call.sva = (ULONG_PTR)sva;
    call.widths = (ULONG_PTR)widths;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetLogicalWidths(struct qemu_syscall *call)
{
    struct qemu_ScriptGetLogicalWidths *c = (struct qemu_ScriptGetLogicalWidths *)call;
    WINE_TRACE("\n");
    c->super.iret = pScriptGetLogicalWidths(QEMU_G2H(c->sa), c->nbchars, c->nbglyphs, QEMU_G2H(c->advances),
            QEMU_G2H(c->log_clust), QEMU_G2H(c->sva), QEMU_G2H(c->widths));
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

WINBASEAPI HRESULT WINAPI ScriptApplyLogicalWidth(const int *dx, int num_chars, int num_glyphs, const WORD *log_clust,
        const SCRIPT_VISATTR *sva, const int *advance, const SCRIPT_ANALYSIS *sa, ABC *abc, int *justify)
{
    struct qemu_ScriptApplyLogicalWidth call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTAPPLYLOGICALWIDTH);
    call.dx = (ULONG_PTR)dx;
    call.num_chars = num_chars;
    call.num_glyphs = num_glyphs;
    call.log_clust = (ULONG_PTR)log_clust;
    call.sva = (ULONG_PTR)sva;
    call.advance = (ULONG_PTR)advance;
    call.sa = (ULONG_PTR)sa;
    call.abc = (ULONG_PTR)abc;
    call.justify = (ULONG_PTR)justify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptApplyLogicalWidth(struct qemu_syscall *call)
{
    struct qemu_ScriptApplyLogicalWidth *c = (struct qemu_ScriptApplyLogicalWidth *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = pScriptApplyLogicalWidth(QEMU_G2H(c->dx), c->num_chars, c->num_glyphs, QEMU_G2H(c->log_clust),
            QEMU_G2H(c->sva), QEMU_G2H(c->advance), QEMU_G2H(c->sa), QEMU_G2H(c->abc), QEMU_G2H(c->justify));
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

WINBASEAPI HRESULT WINAPI ScriptJustify(const SCRIPT_VISATTR *sva, const int *advance, int num_glyphs, int dx,
        int min_kashida, int *justify)
{
    struct qemu_ScriptJustify call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTJUSTIFY);
    call.sva = (ULONG_PTR)sva;
    call.advance = (ULONG_PTR)advance;
    call.num_glyphs = num_glyphs;
    call.dx = dx;
    call.min_kashida = min_kashida;
    call.justify = (ULONG_PTR)justify;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptJustify(struct qemu_syscall *call)
{
    struct qemu_ScriptJustify *c = (struct qemu_ScriptJustify *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = pScriptJustify(QEMU_G2H(c->sva), QEMU_G2H(c->advance), c->num_glyphs, c->dx,
            c->min_kashida, QEMU_G2H(c->justify));
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

WINBASEAPI HRESULT WINAPI ScriptGetFontScriptTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa, int cMaxTags,
        OPENTYPE_TAG *pScriptTags, int *pcTags)
{
    struct qemu_ScriptGetFontScriptTags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTSCRIPTTAGS);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.psa = (ULONG_PTR)psa;
    call.cMaxTags = cMaxTags;
    call.pScriptTags = (ULONG_PTR)pScriptTags;
    call.pcTags = (ULONG_PTR)pcTags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetFontScriptTags(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontScriptTags *c = (struct qemu_ScriptGetFontScriptTags *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptGetFontScriptTags(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->psa), c->cMaxTags,
            QEMU_G2H(c->pScriptTags), QEMU_G2H(c->pcTags));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptGetFontLanguageTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa,
        OPENTYPE_TAG tagScript, int cMaxTags, OPENTYPE_TAG *pLangSysTags, int *pcTags)
{
    struct qemu_ScriptGetFontLanguageTags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTLANGUAGETAGS);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.psa = (ULONG_PTR)psa;
    call.tagScript = (ULONG_PTR)tagScript;
    call.cMaxTags = cMaxTags;
    call.pLangSysTags = (ULONG_PTR)pLangSysTags;
    call.pcTags = (ULONG_PTR)pcTags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetFontLanguageTags(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontLanguageTags *c = (struct qemu_ScriptGetFontLanguageTags *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptGetFontLanguageTags(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->psa), c->tagScript,
            c->cMaxTags, QEMU_G2H(c->pLangSysTags), QEMU_G2H(c->pcTags));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
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

WINBASEAPI HRESULT WINAPI ScriptGetFontFeatureTags(HDC hdc, SCRIPT_CACHE *psc, SCRIPT_ANALYSIS *psa,
        OPENTYPE_TAG tagScript, OPENTYPE_TAG tagLangSys, int cMaxTags, OPENTYPE_TAG *pFeatureTags, int *pcTags)
{
    struct qemu_ScriptGetFontFeatureTags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCRIPTGETFONTFEATURETAGS);
    call.hdc = (ULONG_PTR)hdc;
    call.psc = (ULONG_PTR)psc;
    call.psa = (ULONG_PTR)psa;
    call.tagScript = tagScript;
    call.tagLangSys = tagLangSys;
    call.cMaxTags = cMaxTags;
    call.pFeatureTags = (ULONG_PTR)pFeatureTags;
    call.pcTags = (ULONG_PTR)pcTags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScriptGetFontFeatureTags(struct qemu_syscall *call)
{
    struct qemu_ScriptGetFontFeatureTags *c = (struct qemu_ScriptGetFontFeatureTags *)call;
    SCRIPT_CACHE stack = NULL, *cache = &stack;
    qemu_ptr *cache32;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    cache = QEMU_G2H(c->psc);
#else
    cache32 = QEMU_G2H(c->psc);
    if (!cache32)
        cache = NULL;
    else if (*cache32)
        cache = &((struct qemu_SCRIPT_CACHE *)QEMU_G2H((uint64_t)*cache32))->host;
#endif

    c->super.iret = pScriptGetFontFeatureTags(QEMU_G2H(c->hdc), cache, QEMU_G2H(c->psa), c->tagScript,
            c->tagLangSys, c->cMaxTags, QEMU_G2H(c->pFeatureTags), QEMU_G2H(c->pcTags));

#if HOST_BIT != GUEST_BIT
    SCRIPT_CACHE_create(cache32, stack);
#endif
}

#endif

