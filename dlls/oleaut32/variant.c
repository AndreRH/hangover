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
#include "oleaut32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_oleaut32);
#endif


struct qemu_VariantInit
{
    struct qemu_syscall super;
    uint64_t pVarg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI VariantInit(VARIANTARG* pVarg)
{
    struct qemu_VariantInit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTINIT);
    call.pVarg = (uint64_t)pVarg;

    qemu_syscall(&call.super);
}

#else

void qemu_VariantInit(struct qemu_syscall *call)
{
    struct qemu_VariantInit *c = (struct qemu_VariantInit *)call;
    WINE_FIXME("Unverified!\n");
    VariantInit(QEMU_G2H(c->pVarg));
}

#endif

struct qemu_VariantClear
{
    struct qemu_syscall super;
    uint64_t pVarg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VariantClear(VARIANTARG* pVarg)
{
    struct qemu_VariantClear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTCLEAR);
    call.pVarg = (uint64_t)pVarg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantClear(struct qemu_syscall *call)
{
    struct qemu_VariantClear *c = (struct qemu_VariantClear *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantClear(QEMU_G2H(c->pVarg));
}

#endif

struct qemu_VariantCopy
{
    struct qemu_syscall super;
    uint64_t pvargDest;
    uint64_t pvargSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VariantCopy(VARIANTARG* pvargDest, VARIANTARG* pvargSrc)
{
    struct qemu_VariantCopy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTCOPY);
    call.pvargDest = (uint64_t)pvargDest;
    call.pvargSrc = (uint64_t)pvargSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantCopy(struct qemu_syscall *call)
{
    struct qemu_VariantCopy *c = (struct qemu_VariantCopy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantCopy(QEMU_G2H(c->pvargDest), QEMU_G2H(c->pvargSrc));
}

#endif

struct qemu_VariantCopyInd
{
    struct qemu_syscall super;
    uint64_t pvargDest;
    uint64_t pvargSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VariantCopyInd(VARIANT* pvargDest, VARIANTARG* pvargSrc)
{
    struct qemu_VariantCopyInd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTCOPYIND);
    call.pvargDest = (uint64_t)pvargDest;
    call.pvargSrc = (uint64_t)pvargSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantCopyInd(struct qemu_syscall *call)
{
    struct qemu_VariantCopyInd *c = (struct qemu_VariantCopyInd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantCopyInd(QEMU_G2H(c->pvargDest), QEMU_G2H(c->pvargSrc));
}

#endif

struct qemu_VariantChangeType
{
    struct qemu_syscall super;
    uint64_t pvargDest;
    uint64_t pvargSrc;
    uint64_t wFlags;
    uint64_t vt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VariantChangeType(VARIANTARG* pvargDest, VARIANTARG* pvargSrc, USHORT wFlags, VARTYPE vt)
{
    struct qemu_VariantChangeType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTCHANGETYPE);
    call.pvargDest = (uint64_t)pvargDest;
    call.pvargSrc = (uint64_t)pvargSrc;
    call.wFlags = (uint64_t)wFlags;
    call.vt = (uint64_t)vt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantChangeType(struct qemu_syscall *call)
{
    struct qemu_VariantChangeType *c = (struct qemu_VariantChangeType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantChangeType(QEMU_G2H(c->pvargDest), QEMU_G2H(c->pvargSrc), c->wFlags, c->vt);
}

#endif

struct qemu_VariantChangeTypeEx
{
    struct qemu_syscall super;
    uint64_t pvargDest;
    uint64_t pvargSrc;
    uint64_t lcid;
    uint64_t wFlags;
    uint64_t vt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VariantChangeTypeEx(VARIANTARG* pvargDest, VARIANTARG* pvargSrc, LCID lcid, USHORT wFlags, VARTYPE vt)
{
    struct qemu_VariantChangeTypeEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTCHANGETYPEEX);
    call.pvargDest = (uint64_t)pvargDest;
    call.pvargSrc = (uint64_t)pvargSrc;
    call.lcid = (uint64_t)lcid;
    call.wFlags = (uint64_t)wFlags;
    call.vt = (uint64_t)vt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantChangeTypeEx(struct qemu_syscall *call)
{
    struct qemu_VariantChangeTypeEx *c = (struct qemu_VariantChangeTypeEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantChangeTypeEx(QEMU_G2H(c->pvargDest), QEMU_G2H(c->pvargSrc), c->lcid, c->wFlags, c->vt);
}

#endif

struct qemu_DosDateTimeToVariantTime
{
    struct qemu_syscall super;
    uint64_t wDosDate;
    uint64_t wDosTime;
    uint64_t pDateOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DosDateTimeToVariantTime(USHORT wDosDate, USHORT wDosTime, double *pDateOut)
{
    struct qemu_DosDateTimeToVariantTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOSDATETIMETOVARIANTTIME);
    call.wDosDate = (uint64_t)wDosDate;
    call.wDosTime = (uint64_t)wDosTime;
    call.pDateOut = (uint64_t)pDateOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DosDateTimeToVariantTime(struct qemu_syscall *call)
{
    struct qemu_DosDateTimeToVariantTime *c = (struct qemu_DosDateTimeToVariantTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DosDateTimeToVariantTime(c->wDosDate, c->wDosTime, QEMU_G2H(c->pDateOut));
}

#endif

struct qemu_VariantTimeToDosDateTime
{
    struct qemu_syscall super;
    uint64_t dateIn;
    uint64_t pwDosDate;
    uint64_t pwDosTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI VariantTimeToDosDateTime(double dateIn, USHORT *pwDosDate, USHORT *pwDosTime)
{
    struct qemu_VariantTimeToDosDateTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTTIMETODOSDATETIME);
    call.dateIn = (uint64_t)dateIn;
    call.pwDosDate = (uint64_t)pwDosDate;
    call.pwDosTime = (uint64_t)pwDosTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantTimeToDosDateTime(struct qemu_syscall *call)
{
    struct qemu_VariantTimeToDosDateTime *c = (struct qemu_VariantTimeToDosDateTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantTimeToDosDateTime(c->dateIn, QEMU_G2H(c->pwDosDate), QEMU_G2H(c->pwDosTime));
}

#endif

struct qemu_SystemTimeToVariantTime
{
    struct qemu_syscall super;
    uint64_t lpSt;
    uint64_t pDateOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SystemTimeToVariantTime(LPSYSTEMTIME lpSt, double *pDateOut)
{
    struct qemu_SystemTimeToVariantTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMTIMETOVARIANTTIME);
    call.lpSt = (uint64_t)lpSt;
    call.pDateOut = (uint64_t)pDateOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SystemTimeToVariantTime(struct qemu_syscall *call)
{
    struct qemu_SystemTimeToVariantTime *c = (struct qemu_SystemTimeToVariantTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemTimeToVariantTime(QEMU_G2H(c->lpSt), QEMU_G2H(c->pDateOut));
}

#endif

struct qemu_VariantTimeToSystemTime
{
    struct qemu_syscall super;
    uint64_t dateIn;
    uint64_t lpSt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI VariantTimeToSystemTime(double dateIn, LPSYSTEMTIME lpSt)
{
    struct qemu_VariantTimeToSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIANTTIMETOSYSTEMTIME);
    call.dateIn = (uint64_t)dateIn;
    call.lpSt = (uint64_t)lpSt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VariantTimeToSystemTime(struct qemu_syscall *call)
{
    struct qemu_VariantTimeToSystemTime *c = (struct qemu_VariantTimeToSystemTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VariantTimeToSystemTime(c->dateIn, QEMU_G2H(c->lpSt));
}

#endif

struct qemu_VarDateFromUdateEx
{
    struct qemu_syscall super;
    uint64_t pUdateIn;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t pDateOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarDateFromUdateEx(UDATE *pUdateIn, LCID lcid, ULONG dwFlags, DATE *pDateOut)
{
    struct qemu_VarDateFromUdateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARDATEFROMUDATEEX);
    call.pUdateIn = (uint64_t)pUdateIn;
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.pDateOut = (uint64_t)pDateOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarDateFromUdateEx(struct qemu_syscall *call)
{
    struct qemu_VarDateFromUdateEx *c = (struct qemu_VarDateFromUdateEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarDateFromUdateEx(QEMU_G2H(c->pUdateIn), c->lcid, c->dwFlags, QEMU_G2H(c->pDateOut));
}

#endif

struct qemu_VarDateFromUdate
{
    struct qemu_syscall super;
    uint64_t pUdateIn;
    uint64_t dwFlags;
    uint64_t pDateOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarDateFromUdate(UDATE *pUdateIn, ULONG dwFlags, DATE *pDateOut)
{
    struct qemu_VarDateFromUdate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARDATEFROMUDATE);
    call.pUdateIn = (uint64_t)pUdateIn;
    call.dwFlags = (uint64_t)dwFlags;
    call.pDateOut = (uint64_t)pDateOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarDateFromUdate(struct qemu_syscall *call)
{
    struct qemu_VarDateFromUdate *c = (struct qemu_VarDateFromUdate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarDateFromUdate(QEMU_G2H(c->pUdateIn), c->dwFlags, QEMU_G2H(c->pDateOut));
}

#endif

struct qemu_VarUdateFromDate
{
    struct qemu_syscall super;
    uint64_t dateIn;
    uint64_t dwFlags;
    uint64_t lpUdate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarUdateFromDate(DATE dateIn, ULONG dwFlags, UDATE *lpUdate)
{
    struct qemu_VarUdateFromDate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARUDATEFROMDATE);
    call.dateIn = (uint64_t)dateIn;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpUdate = (uint64_t)lpUdate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarUdateFromDate(struct qemu_syscall *call)
{
    struct qemu_VarUdateFromDate *c = (struct qemu_VarUdateFromDate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarUdateFromDate(c->dateIn, c->dwFlags, QEMU_G2H(c->lpUdate));
}

#endif

struct qemu_VarParseNumFromStr
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t pNumprs;
    uint64_t rgbDig;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarParseNumFromStr(OLECHAR *lpszStr, LCID lcid, ULONG dwFlags, NUMPARSE *pNumprs, BYTE *rgbDig)
{
    struct qemu_VarParseNumFromStr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARPARSENUMFROMSTR);
    call.lpszStr = (uint64_t)lpszStr;
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.pNumprs = (uint64_t)pNumprs;
    call.rgbDig = (uint64_t)rgbDig;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarParseNumFromStr(struct qemu_syscall *call)
{
    struct qemu_VarParseNumFromStr *c = (struct qemu_VarParseNumFromStr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarParseNumFromStr(QEMU_G2H(c->lpszStr), c->lcid, c->dwFlags, QEMU_G2H(c->pNumprs), QEMU_G2H(c->rgbDig));
}

#endif

struct qemu_VarNumFromParseNum
{
    struct qemu_syscall super;
    uint64_t pNumprs;
    uint64_t rgbDig;
    uint64_t dwVtBits;
    uint64_t pVarDst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarNumFromParseNum(NUMPARSE *pNumprs, BYTE *rgbDig, ULONG dwVtBits, VARIANT *pVarDst)
{
    struct qemu_VarNumFromParseNum call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARNUMFROMPARSENUM);
    call.pNumprs = (uint64_t)pNumprs;
    call.rgbDig = (uint64_t)rgbDig;
    call.dwVtBits = (uint64_t)dwVtBits;
    call.pVarDst = (uint64_t)pVarDst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarNumFromParseNum(struct qemu_syscall *call)
{
    struct qemu_VarNumFromParseNum *c = (struct qemu_VarNumFromParseNum *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarNumFromParseNum(QEMU_G2H(c->pNumprs), QEMU_G2H(c->rgbDig), c->dwVtBits, QEMU_G2H(c->pVarDst));
}

#endif

struct qemu_VarCat
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarCat(LPVARIANT left, LPVARIANT right, LPVARIANT out)
{
    struct qemu_VarCat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARCAT);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.out = (uint64_t)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarCat(struct qemu_syscall *call)
{
    struct qemu_VarCat *c = (struct qemu_VarCat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarCat(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->out));
}

#endif

struct qemu_VarCmp
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarCmp(LPVARIANT left, LPVARIANT right, LCID lcid, DWORD flags)
{
    struct qemu_VarCmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARCMP);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarCmp(struct qemu_syscall *call)
{
    struct qemu_VarCmp *c = (struct qemu_VarCmp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarCmp(QEMU_G2H(c->left), QEMU_G2H(c->right), c->lcid, c->flags);
}

#endif

struct qemu_VarAnd
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarAnd(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarAnd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARAND);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarAnd(struct qemu_syscall *call)
{
    struct qemu_VarAnd *c = (struct qemu_VarAnd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarAnd(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarAdd
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarAdd(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarAdd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARADD);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarAdd(struct qemu_syscall *call)
{
    struct qemu_VarAdd *c = (struct qemu_VarAdd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarAdd(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarMul
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarMul(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarMul call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARMUL);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarMul(struct qemu_syscall *call)
{
    struct qemu_VarMul *c = (struct qemu_VarMul *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarMul(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarDiv
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarDiv(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarDiv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARDIV);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarDiv(struct qemu_syscall *call)
{
    struct qemu_VarDiv *c = (struct qemu_VarDiv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarDiv(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarSub
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarSub(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarSub call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARSUB);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarSub(struct qemu_syscall *call)
{
    struct qemu_VarSub *c = (struct qemu_VarSub *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarSub(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarOr
{
    struct qemu_syscall super;
    uint64_t pVarLeft;
    uint64_t pVarRight;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarOr(LPVARIANT pVarLeft, LPVARIANT pVarRight, LPVARIANT pVarOut)
{
    struct qemu_VarOr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VAROR);
    call.pVarLeft = (uint64_t)pVarLeft;
    call.pVarRight = (uint64_t)pVarRight;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarOr(struct qemu_syscall *call)
{
    struct qemu_VarOr *c = (struct qemu_VarOr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarOr(QEMU_G2H(c->pVarLeft), QEMU_G2H(c->pVarRight), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarAbs
{
    struct qemu_syscall super;
    uint64_t pVarIn;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarAbs(LPVARIANT pVarIn, LPVARIANT pVarOut)
{
    struct qemu_VarAbs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARABS);
    call.pVarIn = (uint64_t)pVarIn;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarAbs(struct qemu_syscall *call)
{
    struct qemu_VarAbs *c = (struct qemu_VarAbs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarAbs(QEMU_G2H(c->pVarIn), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarFix
{
    struct qemu_syscall super;
    uint64_t pVarIn;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarFix(LPVARIANT pVarIn, LPVARIANT pVarOut)
{
    struct qemu_VarFix call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARFIX);
    call.pVarIn = (uint64_t)pVarIn;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarFix(struct qemu_syscall *call)
{
    struct qemu_VarFix *c = (struct qemu_VarFix *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarFix(QEMU_G2H(c->pVarIn), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarInt
{
    struct qemu_syscall super;
    uint64_t pVarIn;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarInt(LPVARIANT pVarIn, LPVARIANT pVarOut)
{
    struct qemu_VarInt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARINT);
    call.pVarIn = (uint64_t)pVarIn;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarInt(struct qemu_syscall *call)
{
    struct qemu_VarInt *c = (struct qemu_VarInt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarInt(QEMU_G2H(c->pVarIn), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarXor
{
    struct qemu_syscall super;
    uint64_t pVarLeft;
    uint64_t pVarRight;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarXor(LPVARIANT pVarLeft, LPVARIANT pVarRight, LPVARIANT pVarOut)
{
    struct qemu_VarXor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARXOR);
    call.pVarLeft = (uint64_t)pVarLeft;
    call.pVarRight = (uint64_t)pVarRight;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarXor(struct qemu_syscall *call)
{
    struct qemu_VarXor *c = (struct qemu_VarXor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarXor(QEMU_G2H(c->pVarLeft), QEMU_G2H(c->pVarRight), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarEqv
{
    struct qemu_syscall super;
    uint64_t pVarLeft;
    uint64_t pVarRight;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarEqv(LPVARIANT pVarLeft, LPVARIANT pVarRight, LPVARIANT pVarOut)
{
    struct qemu_VarEqv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VAREQV);
    call.pVarLeft = (uint64_t)pVarLeft;
    call.pVarRight = (uint64_t)pVarRight;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarEqv(struct qemu_syscall *call)
{
    struct qemu_VarEqv *c = (struct qemu_VarEqv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarEqv(QEMU_G2H(c->pVarLeft), QEMU_G2H(c->pVarRight), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarNeg
{
    struct qemu_syscall super;
    uint64_t pVarIn;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarNeg(LPVARIANT pVarIn, LPVARIANT pVarOut)
{
    struct qemu_VarNeg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARNEG);
    call.pVarIn = (uint64_t)pVarIn;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarNeg(struct qemu_syscall *call)
{
    struct qemu_VarNeg *c = (struct qemu_VarNeg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarNeg(QEMU_G2H(c->pVarIn), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarNot
{
    struct qemu_syscall super;
    uint64_t pVarIn;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarNot(LPVARIANT pVarIn, LPVARIANT pVarOut)
{
    struct qemu_VarNot call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARNOT);
    call.pVarIn = (uint64_t)pVarIn;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarNot(struct qemu_syscall *call)
{
    struct qemu_VarNot *c = (struct qemu_VarNot *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarNot(QEMU_G2H(c->pVarIn), QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarRound
{
    struct qemu_syscall super;
    uint64_t pVarIn;
    uint64_t deci;
    uint64_t pVarOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarRound(LPVARIANT pVarIn, int deci, LPVARIANT pVarOut)
{
    struct qemu_VarRound call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARROUND);
    call.pVarIn = (uint64_t)pVarIn;
    call.deci = (uint64_t)deci;
    call.pVarOut = (uint64_t)pVarOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarRound(struct qemu_syscall *call)
{
    struct qemu_VarRound *c = (struct qemu_VarRound *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarRound(QEMU_G2H(c->pVarIn), c->deci, QEMU_G2H(c->pVarOut));
}

#endif

struct qemu_VarIdiv
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarIdiv(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarIdiv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIDIV);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarIdiv(struct qemu_syscall *call)
{
    struct qemu_VarIdiv *c = (struct qemu_VarIdiv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarIdiv(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarMod
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarMod(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarMod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARMOD);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarMod(struct qemu_syscall *call)
{
    struct qemu_VarMod *c = (struct qemu_VarMod *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarMod(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarPow
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarPow(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarPow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARPOW);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarPow(struct qemu_syscall *call)
{
    struct qemu_VarPow *c = (struct qemu_VarPow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarPow(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

struct qemu_VarImp
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI VarImp(LPVARIANT left, LPVARIANT right, LPVARIANT result)
{
    struct qemu_VarImp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VARIMP);
    call.left = (uint64_t)left;
    call.right = (uint64_t)right;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VarImp(struct qemu_syscall *call)
{
    struct qemu_VarImp *c = (struct qemu_VarImp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = VarImp(QEMU_G2H(c->left), QEMU_G2H(c->right), QEMU_G2H(c->result));
}

#endif

