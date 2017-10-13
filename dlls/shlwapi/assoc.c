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
#include <shlwapi.h>
#include <shtypes.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shlwapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi);
#endif


struct qemu_AssocCreate
{
    struct qemu_syscall super;
    uint64_t clsid;
    uint64_t refiid;
    uint64_t lpInterface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocCreate(CLSID clsid, REFIID refiid, void **lpInterface)
{
    struct qemu_AssocCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCCREATE);
    call.clsid = (ULONG_PTR)&clsid;
    call.refiid = (ULONG_PTR)refiid;
    call.lpInterface = (ULONG_PTR)lpInterface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocCreate(struct qemu_syscall *call)
{
    struct qemu_AssocCreate *c = (struct qemu_AssocCreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocCreate(*((CLSID *)QEMU_G2H(c->clsid)), QEMU_G2H(c->refiid), QEMU_G2H(c->lpInterface));
}

#endif

struct qemu_AssocGetPerceivedType
{
    struct qemu_syscall super;
    uint64_t lpszExt;
    uint64_t lpType;
    uint64_t lpFlag;
    uint64_t lppszType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocGetPerceivedType(LPCWSTR lpszExt, PERCEIVED *lpType, PERCEIVEDFLAG *lpFlag, LPWSTR *lppszType)
{
    struct qemu_AssocGetPerceivedType call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCGETPERCEIVEDTYPE);
    call.lpszExt = (ULONG_PTR)lpszExt;
    call.lpType = (ULONG_PTR)lpType;
    call.lpFlag = (ULONG_PTR)lpFlag;
    call.lppszType = (ULONG_PTR)lppszType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AssocGetPerceivedType to Wine headers? */
extern HRESULT WINAPI AssocGetPerceivedType(LPCWSTR lpszExt, PERCEIVED *lpType, INT *lpFlag, LPWSTR *lppszType);
void qemu_AssocGetPerceivedType(struct qemu_syscall *call)
{
    struct qemu_AssocGetPerceivedType *c = (struct qemu_AssocGetPerceivedType *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocGetPerceivedType(QEMU_G2H(c->lpszExt), QEMU_G2H(c->lpType), QEMU_G2H(c->lpFlag), QEMU_G2H(c->lppszType));
}

#endif

struct qemu_AssocQueryKeyW
{
    struct qemu_syscall super;
    uint64_t cfFlags;
    uint64_t assockey;
    uint64_t pszAssoc;
    uint64_t pszExtra;
    uint64_t phkeyOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocQueryKeyW(ASSOCF cfFlags, ASSOCKEY assockey, LPCWSTR pszAssoc, LPCWSTR pszExtra, HKEY *phkeyOut)
{
    struct qemu_AssocQueryKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCQUERYKEYW);
    call.cfFlags = (ULONG_PTR)cfFlags;
    call.assockey = (ULONG_PTR)assockey;
    call.pszAssoc = (ULONG_PTR)pszAssoc;
    call.pszExtra = (ULONG_PTR)pszExtra;
    call.phkeyOut = (ULONG_PTR)phkeyOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocQueryKeyW(struct qemu_syscall *call)
{
    struct qemu_AssocQueryKeyW *c = (struct qemu_AssocQueryKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocQueryKeyW(c->cfFlags, c->assockey, QEMU_G2H(c->pszAssoc), QEMU_G2H(c->pszExtra), QEMU_G2H(c->phkeyOut));
}

#endif

struct qemu_AssocQueryKeyA
{
    struct qemu_syscall super;
    uint64_t cfFlags;
    uint64_t assockey;
    uint64_t pszAssoc;
    uint64_t pszExtra;
    uint64_t phkeyOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocQueryKeyA(ASSOCF cfFlags, ASSOCKEY assockey, LPCSTR pszAssoc, LPCSTR pszExtra, HKEY *phkeyOut)
{
    struct qemu_AssocQueryKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCQUERYKEYA);
    call.cfFlags = (ULONG_PTR)cfFlags;
    call.assockey = (ULONG_PTR)assockey;
    call.pszAssoc = (ULONG_PTR)pszAssoc;
    call.pszExtra = (ULONG_PTR)pszExtra;
    call.phkeyOut = (ULONG_PTR)phkeyOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocQueryKeyA(struct qemu_syscall *call)
{
    struct qemu_AssocQueryKeyA *c = (struct qemu_AssocQueryKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocQueryKeyA(c->cfFlags, c->assockey, QEMU_G2H(c->pszAssoc), QEMU_G2H(c->pszExtra), QEMU_G2H(c->phkeyOut));
}

#endif

struct qemu_AssocQueryStringW
{
    struct qemu_syscall super;
    uint64_t cfFlags;
    uint64_t str;
    uint64_t pszAssoc;
    uint64_t pszExtra;
    uint64_t pszOut;
    uint64_t pcchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocQueryStringW(ASSOCF cfFlags, ASSOCSTR str, LPCWSTR pszAssoc, LPCWSTR pszExtra, LPWSTR pszOut, DWORD *pcchOut)
{
    struct qemu_AssocQueryStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCQUERYSTRINGW);
    call.cfFlags = (ULONG_PTR)cfFlags;
    call.str = (ULONG_PTR)str;
    call.pszAssoc = (ULONG_PTR)pszAssoc;
    call.pszExtra = (ULONG_PTR)pszExtra;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocQueryStringW(struct qemu_syscall *call)
{
    struct qemu_AssocQueryStringW *c = (struct qemu_AssocQueryStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = AssocQueryStringW(c->cfFlags, c->str, QEMU_G2H(c->pszAssoc), QEMU_G2H(c->pszExtra), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut));
}

#endif

struct qemu_AssocQueryStringA
{
    struct qemu_syscall super;
    uint64_t cfFlags;
    uint64_t str;
    uint64_t pszAssoc;
    uint64_t pszExtra;
    uint64_t pszOut;
    uint64_t pcchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocQueryStringA(ASSOCF cfFlags, ASSOCSTR str, LPCSTR pszAssoc, LPCSTR pszExtra, LPSTR pszOut, DWORD *pcchOut)
{
    struct qemu_AssocQueryStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCQUERYSTRINGA);
    call.cfFlags = (ULONG_PTR)cfFlags;
    call.str = (ULONG_PTR)str;
    call.pszAssoc = (ULONG_PTR)pszAssoc;
    call.pszExtra = (ULONG_PTR)pszExtra;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocQueryStringA(struct qemu_syscall *call)
{
    struct qemu_AssocQueryStringA *c = (struct qemu_AssocQueryStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocQueryStringA(c->cfFlags, c->str, QEMU_G2H(c->pszAssoc), QEMU_G2H(c->pszExtra), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut));
}

#endif

struct qemu_AssocQueryStringByKeyW
{
    struct qemu_syscall super;
    uint64_t cfFlags;
    uint64_t str;
    uint64_t hkAssoc;
    uint64_t pszExtra;
    uint64_t pszOut;
    uint64_t pcchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocQueryStringByKeyW(ASSOCF cfFlags, ASSOCSTR str, HKEY hkAssoc, LPCWSTR pszExtra, LPWSTR pszOut, DWORD *pcchOut)
{
    struct qemu_AssocQueryStringByKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCQUERYSTRINGBYKEYW);
    call.cfFlags = (ULONG_PTR)cfFlags;
    call.str = (ULONG_PTR)str;
    call.hkAssoc = (ULONG_PTR)hkAssoc;
    call.pszExtra = (ULONG_PTR)pszExtra;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocQueryStringByKeyW(struct qemu_syscall *call)
{
    struct qemu_AssocQueryStringByKeyW *c = (struct qemu_AssocQueryStringByKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocQueryStringByKeyW(c->cfFlags, c->str, QEMU_G2H(c->hkAssoc), QEMU_G2H(c->pszExtra), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut));
}

#endif

struct qemu_AssocQueryStringByKeyA
{
    struct qemu_syscall super;
    uint64_t cfFlags;
    uint64_t str;
    uint64_t hkAssoc;
    uint64_t pszExtra;
    uint64_t pszOut;
    uint64_t pcchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI AssocQueryStringByKeyA(ASSOCF cfFlags, ASSOCSTR str, HKEY hkAssoc, LPCSTR pszExtra, LPSTR pszOut, DWORD *pcchOut)
{
    struct qemu_AssocQueryStringByKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCQUERYSTRINGBYKEYA);
    call.cfFlags = (ULONG_PTR)cfFlags;
    call.str = (ULONG_PTR)str;
    call.hkAssoc = (ULONG_PTR)hkAssoc;
    call.pszExtra = (ULONG_PTR)pszExtra;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocQueryStringByKeyA(struct qemu_syscall *call)
{
    struct qemu_AssocQueryStringByKeyA *c = (struct qemu_AssocQueryStringByKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocQueryStringByKeyA(c->cfFlags, c->str, QEMU_G2H(c->hkAssoc), QEMU_G2H(c->pszExtra), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut));
}

#endif

struct qemu_AssocIsDangerous
{
    struct qemu_syscall super;
    uint64_t lpszAssoc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AssocIsDangerous(LPCWSTR lpszAssoc)
{
    struct qemu_AssocIsDangerous call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASSOCISDANGEROUS);
    call.lpszAssoc = (ULONG_PTR)lpszAssoc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AssocIsDangerous(struct qemu_syscall *call)
{
    struct qemu_AssocIsDangerous *c = (struct qemu_AssocIsDangerous *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AssocIsDangerous(QEMU_G2H(c->lpszAssoc));
}

#endif

