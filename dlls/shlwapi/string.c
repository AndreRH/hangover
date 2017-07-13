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

#include "windows-user-services.h"
#include "dll_list.h"
#include "shlwapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi);
#endif


struct qemu_ChrCmpIA
{
    struct qemu_syscall super;
    uint64_t ch1;
    uint64_t ch2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChrCmpIA(WORD ch1, WORD ch2)
{
    struct qemu_ChrCmpIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHRCMPIA);
    call.ch1 = (uint64_t)ch1;
    call.ch2 = (uint64_t)ch2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ChrCmpIA to Wine headers? */
extern BOOL WINAPI ChrCmpIA(WORD ch1, WORD ch2);
void qemu_ChrCmpIA(struct qemu_syscall *call)
{
    struct qemu_ChrCmpIA *c = (struct qemu_ChrCmpIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChrCmpIA(c->ch1, c->ch2);
}

#endif

struct qemu_ChrCmpIW
{
    struct qemu_syscall super;
    uint64_t ch1;
    uint64_t ch2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChrCmpIW(WCHAR ch1, WCHAR ch2)
{
    struct qemu_ChrCmpIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHRCMPIW);
    call.ch1 = (uint64_t)ch1;
    call.ch2 = (uint64_t)ch2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ChrCmpIW to Wine headers? */
extern BOOL WINAPI ChrCmpIW(WCHAR ch1, WCHAR ch2);
void qemu_ChrCmpIW(struct qemu_syscall *call)
{
    struct qemu_ChrCmpIW *c = (struct qemu_ChrCmpIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChrCmpIW(c->ch1, c->ch2);
}

#endif

struct qemu_StrChrA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrChrA(LPCSTR lpszStr, WORD ch)
{
    struct qemu_StrChrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHRA);
    call.lpszStr = (uint64_t)lpszStr;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrChrA to Wine headers? */
extern LPSTR WINAPI StrChrA(LPCSTR lpszStr, WORD ch);
void qemu_StrChrA(struct qemu_syscall *call)
{
    struct qemu_StrChrA *c = (struct qemu_StrChrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrChrA(QEMU_G2H(c->lpszStr), c->ch);
}

#endif

struct qemu_StrChrW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrChrW(LPCWSTR lpszStr, WCHAR ch)
{
    struct qemu_StrChrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHRW);
    call.lpszStr = (uint64_t)lpszStr;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrChrW to Wine headers? */
extern LPWSTR WINAPI StrChrW(LPCWSTR lpszStr, WCHAR ch);
void qemu_StrChrW(struct qemu_syscall *call)
{
    struct qemu_StrChrW *c = (struct qemu_StrChrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrChrW(QEMU_G2H(c->lpszStr), c->ch);
}

#endif

struct qemu_StrChrIA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrChrIA(LPCSTR lpszStr, WORD ch)
{
    struct qemu_StrChrIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHRIA);
    call.lpszStr = (uint64_t)lpszStr;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrChrIA to Wine headers? */
extern LPSTR WINAPI StrChrIA(LPCSTR lpszStr, WORD ch);
void qemu_StrChrIA(struct qemu_syscall *call)
{
    struct qemu_StrChrIA *c = (struct qemu_StrChrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrChrIA(QEMU_G2H(c->lpszStr), c->ch);
}

#endif

struct qemu_StrChrIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrChrIW(LPCWSTR lpszStr, WCHAR ch)
{
    struct qemu_StrChrIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHRIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrChrIW to Wine headers? */
extern LPWSTR WINAPI StrChrIW(LPCWSTR lpszStr, WCHAR ch);
void qemu_StrChrIW(struct qemu_syscall *call)
{
    struct qemu_StrChrIW *c = (struct qemu_StrChrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrChrIW(QEMU_G2H(c->lpszStr), c->ch);
}

#endif

struct qemu_StrChrNW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t ch;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrChrNW(LPCWSTR lpszStr, WCHAR ch, UINT cchMax)
{
    struct qemu_StrChrNW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHRNW);
    call.lpszStr = (uint64_t)lpszStr;
    call.ch = (uint64_t)ch;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrChrNW to Wine headers? */
extern LPWSTR WINAPI StrChrNW(LPCWSTR lpszStr, WCHAR ch, UINT cchMax);
void qemu_StrChrNW(struct qemu_syscall *call)
{
    struct qemu_StrChrNW *c = (struct qemu_StrChrNW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrChrNW(QEMU_G2H(c->lpszStr), c->ch, c->cchMax);
}

#endif

struct qemu_StrCmpIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCmpIW(LPCWSTR lpszStr, LPCWSTR lpszComp)
{
    struct qemu_StrCmpIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpIW to Wine headers? */
extern int WINAPI StrCmpIW(LPCWSTR lpszStr, LPCWSTR lpszComp);
void qemu_StrCmpIW(struct qemu_syscall *call)
{
    struct qemu_StrCmpIW *c = (struct qemu_StrCmpIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp));
}

#endif

struct qemu_StrCmpNA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrCmpNA(LPCSTR lpszStr, LPCSTR lpszComp, INT iLen)
{
    struct qemu_StrCmpNA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpNA to Wine headers? */
extern INT WINAPI StrCmpNA(LPCSTR lpszStr, LPCSTR lpszComp, INT iLen);
void qemu_StrCmpNA(struct qemu_syscall *call)
{
    struct qemu_StrCmpNA *c = (struct qemu_StrCmpNA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpNA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_StrCmpNW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrCmpNW(LPCWSTR lpszStr, LPCWSTR lpszComp, INT iLen)
{
    struct qemu_StrCmpNW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpNW to Wine headers? */
extern INT WINAPI StrCmpNW(LPCWSTR lpszStr, LPCWSTR lpszComp, INT iLen);
void qemu_StrCmpNW(struct qemu_syscall *call)
{
    struct qemu_StrCmpNW *c = (struct qemu_StrCmpNW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpNW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_StrCmpNIA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCmpNIA(LPCSTR lpszStr, LPCSTR lpszComp, int iLen)
{
    struct qemu_StrCmpNIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNIA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpNIA to Wine headers? */
extern int WINAPI StrCmpNIA(LPCSTR lpszStr, LPCSTR lpszComp, int iLen);
void qemu_StrCmpNIA(struct qemu_syscall *call)
{
    struct qemu_StrCmpNIA *c = (struct qemu_StrCmpNIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpNIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_StrCmpNIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrCmpNIW(LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen)
{
    struct qemu_StrCmpNIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpNIW to Wine headers? */
extern INT WINAPI StrCmpNIW(LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen);
void qemu_StrCmpNIW(struct qemu_syscall *call)
{
    struct qemu_StrCmpNIW *c = (struct qemu_StrCmpNIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpNIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_StrCmpW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCmpW(LPCWSTR lpszStr, LPCWSTR lpszComp)
{
    struct qemu_StrCmpW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpW to Wine headers? */
extern int WINAPI StrCmpW(LPCWSTR lpszStr, LPCWSTR lpszComp);
void qemu_StrCmpW(struct qemu_syscall *call)
{
    struct qemu_StrCmpW *c = (struct qemu_StrCmpW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp));
}

#endif

struct qemu_StrCatW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrCatW(LPWSTR lpszStr, LPCWSTR lpszSrc)
{
    struct qemu_StrCatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCATW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszSrc = (uint64_t)lpszSrc;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrCatW to Wine headers? */
extern LPWSTR WINAPI StrCatW(LPWSTR lpszStr, LPCWSTR lpszSrc);
void qemu_StrCatW(struct qemu_syscall *call)
{
    struct qemu_StrCatW *c = (struct qemu_StrCatW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCatW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSrc));
}

#endif

struct qemu_StrCatChainW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t cchMax;
    uint64_t ichAt;
    uint64_t lpszCat;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI StrCatChainW(LPWSTR lpszStr, DWORD cchMax, DWORD ichAt, LPCWSTR lpszCat)
{
    struct qemu_StrCatChainW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCATCHAINW);
    call.lpszStr = (uint64_t)lpszStr;
    call.cchMax = (uint64_t)cchMax;
    call.ichAt = (uint64_t)ichAt;
    call.lpszCat = (uint64_t)lpszCat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCatChainW to Wine headers? */
extern DWORD WINAPI StrCatChainW(LPWSTR lpszStr, DWORD cchMax, DWORD ichAt, LPCWSTR lpszCat);
void qemu_StrCatChainW(struct qemu_syscall *call)
{
    struct qemu_StrCatChainW *c = (struct qemu_StrCatChainW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCatChainW(QEMU_G2H(c->lpszStr), c->cchMax, c->ichAt, QEMU_G2H(c->lpszCat));
}

#endif

struct qemu_StrCpyW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrCpyW(LPWSTR lpszStr, LPCWSTR lpszSrc)
{
    struct qemu_StrCpyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPYW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszSrc = (uint64_t)lpszSrc;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrCpyW to Wine headers? */
extern LPWSTR WINAPI StrCpyW(LPWSTR lpszStr, LPCWSTR lpszSrc);
void qemu_StrCpyW(struct qemu_syscall *call)
{
    struct qemu_StrCpyW *c = (struct qemu_StrCpyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCpyW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSrc));
}

#endif

struct qemu_StrCpyNW
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrCpyNW(LPWSTR dst, LPCWSTR src, int count)
{
    struct qemu_StrCpyNW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPYNW);
    call.dst = (uint64_t)dst;
    call.src = (uint64_t)src;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrCpyNW to Wine headers? */
extern LPWSTR WINAPI StrCpyNW(LPWSTR dst, LPCWSTR src, int count);
void qemu_StrCpyNW(struct qemu_syscall *call)
{
    struct qemu_StrCpyNW *c = (struct qemu_StrCpyNW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCpyNW(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->count);
}

#endif

struct qemu_StrStrA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszSearch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrStrA(LPCSTR lpszStr, LPCSTR lpszSearch)
{
    struct qemu_StrStrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTRA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszSearch = (uint64_t)lpszSearch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrStrA to Wine headers? */
extern LPSTR WINAPI StrStrA(LPCSTR lpszStr, LPCSTR lpszSearch);
void qemu_StrStrA(struct qemu_syscall *call)
{
    struct qemu_StrStrA *c = (struct qemu_StrStrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrStrA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrStrW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszSearch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrStrW(LPCWSTR lpszStr, LPCWSTR lpszSearch)
{
    struct qemu_StrStrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTRW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszSearch = (uint64_t)lpszSearch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrStrW to Wine headers? */
extern LPWSTR WINAPI StrStrW(LPCWSTR lpszStr, LPCWSTR lpszSearch);
void qemu_StrStrW(struct qemu_syscall *call)
{
    struct qemu_StrStrW *c = (struct qemu_StrStrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrStrW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrRStrIA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszEnd;
    uint64_t lpszSearch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrRStrIA(LPCSTR lpszStr, LPCSTR lpszEnd, LPCSTR lpszSearch)
{
    struct qemu_StrRStrIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRSTRIA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszEnd = (uint64_t)lpszEnd;
    call.lpszSearch = (uint64_t)lpszSearch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrRStrIA to Wine headers? */
extern LPSTR WINAPI StrRStrIA(LPCSTR lpszStr, LPCSTR lpszEnd, LPCSTR lpszSearch);
void qemu_StrRStrIA(struct qemu_syscall *call)
{
    struct qemu_StrRStrIA *c = (struct qemu_StrRStrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrRStrIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrRStrIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszEnd;
    uint64_t lpszSearch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrRStrIW(LPCWSTR lpszStr, LPCWSTR lpszEnd, LPCWSTR lpszSearch)
{
    struct qemu_StrRStrIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRSTRIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszEnd = (uint64_t)lpszEnd;
    call.lpszSearch = (uint64_t)lpszSearch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrRStrIW to Wine headers? */
extern LPWSTR WINAPI StrRStrIW(LPCWSTR lpszStr, LPCWSTR lpszEnd, LPCWSTR lpszSearch);
void qemu_StrRStrIW(struct qemu_syscall *call)
{
    struct qemu_StrRStrIW *c = (struct qemu_StrRStrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrRStrIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrStrIA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszSearch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrStrIA(LPCSTR lpszStr, LPCSTR lpszSearch)
{
    struct qemu_StrStrIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTRIA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszSearch = (uint64_t)lpszSearch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrStrIA to Wine headers? */
extern LPSTR WINAPI StrStrIA(LPCSTR lpszStr, LPCSTR lpszSearch);
void qemu_StrStrIA(struct qemu_syscall *call)
{
    struct qemu_StrStrIA *c = (struct qemu_StrStrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrStrIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrStrIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszSearch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrStrIW(LPCWSTR lpszStr, LPCWSTR lpszSearch)
{
    struct qemu_StrStrIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTRIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszSearch = (uint64_t)lpszSearch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrStrIW to Wine headers? */
extern LPWSTR WINAPI StrStrIW(LPCWSTR lpszStr, LPCWSTR lpszSearch);
void qemu_StrStrIW(struct qemu_syscall *call)
{
    struct qemu_StrStrIW *c = (struct qemu_StrStrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrStrIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrStrNW
{
    struct qemu_syscall super;
    uint64_t lpFirst;
    uint64_t lpSrch;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrStrNW(LPCWSTR lpFirst, LPCWSTR lpSrch, UINT cchMax)
{
    struct qemu_StrStrNW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTRNW);
    call.lpFirst = (uint64_t)lpFirst;
    call.lpSrch = (uint64_t)lpSrch;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrStrNW to Wine headers? */
extern LPWSTR WINAPI StrStrNW(LPCWSTR lpFirst, LPCWSTR lpSrch, UINT cchMax);
void qemu_StrStrNW(struct qemu_syscall *call)
{
    struct qemu_StrStrNW *c = (struct qemu_StrStrNW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrStrNW(QEMU_G2H(c->lpFirst), QEMU_G2H(c->lpSrch), c->cchMax);
}

#endif

struct qemu_StrStrNIW
{
    struct qemu_syscall super;
    uint64_t lpFirst;
    uint64_t lpSrch;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrStrNIW(LPCWSTR lpFirst, LPCWSTR lpSrch, UINT cchMax)
{
    struct qemu_StrStrNIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTRNIW);
    call.lpFirst = (uint64_t)lpFirst;
    call.lpSrch = (uint64_t)lpSrch;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrStrNIW to Wine headers? */
extern LPWSTR WINAPI StrStrNIW(LPCWSTR lpFirst, LPCWSTR lpSrch, UINT cchMax);
void qemu_StrStrNIW(struct qemu_syscall *call)
{
    struct qemu_StrStrNIW *c = (struct qemu_StrStrNIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrStrNIW(QEMU_G2H(c->lpFirst), QEMU_G2H(c->lpSrch), c->cchMax);
}

#endif

struct qemu_StrToIntA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrToIntA(LPCSTR lpszStr)
{
    struct qemu_StrToIntA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINTA);
    call.lpszStr = (uint64_t)lpszStr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrToIntA to Wine headers? */
extern int WINAPI StrToIntA(LPCSTR lpszStr);
void qemu_StrToIntA(struct qemu_syscall *call)
{
    struct qemu_StrToIntA *c = (struct qemu_StrToIntA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrToIntA(QEMU_G2H(c->lpszStr));
}

#endif

struct qemu_StrToIntW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrToIntW(LPCWSTR lpszStr)
{
    struct qemu_StrToIntW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINTW);
    call.lpszStr = (uint64_t)lpszStr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrToIntW to Wine headers? */
extern int WINAPI StrToIntW(LPCWSTR lpszStr);
void qemu_StrToIntW(struct qemu_syscall *call)
{
    struct qemu_StrToIntW *c = (struct qemu_StrToIntW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrToIntW(QEMU_G2H(c->lpszStr));
}

#endif

struct qemu_StrToIntExA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t dwFlags;
    uint64_t lpiRet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrToIntExA(LPCSTR lpszStr, DWORD dwFlags, LPINT lpiRet)
{
    struct qemu_StrToIntExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINTEXA);
    call.lpszStr = (uint64_t)lpszStr;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpiRet = (uint64_t)lpiRet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrToIntExA to Wine headers? */
extern BOOL WINAPI StrToIntExA(LPCSTR lpszStr, DWORD dwFlags, LPINT lpiRet);
void qemu_StrToIntExA(struct qemu_syscall *call)
{
    struct qemu_StrToIntExA *c = (struct qemu_StrToIntExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrToIntExA(QEMU_G2H(c->lpszStr), c->dwFlags, QEMU_G2H(c->lpiRet));
}

#endif

struct qemu_StrToInt64ExA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t dwFlags;
    uint64_t lpiRet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrToInt64ExA(LPCSTR lpszStr, DWORD dwFlags, LONGLONG *lpiRet)
{
    struct qemu_StrToInt64ExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINT64EXA);
    call.lpszStr = (uint64_t)lpszStr;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpiRet = (uint64_t)lpiRet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrToInt64ExA to Wine headers? */
extern BOOL WINAPI StrToInt64ExA(LPCSTR lpszStr, DWORD dwFlags, LONGLONG *lpiRet);
void qemu_StrToInt64ExA(struct qemu_syscall *call)
{
    struct qemu_StrToInt64ExA *c = (struct qemu_StrToInt64ExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrToInt64ExA(QEMU_G2H(c->lpszStr), c->dwFlags, QEMU_G2H(c->lpiRet));
}

#endif

struct qemu_StrToIntExW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t dwFlags;
    uint64_t lpiRet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrToIntExW(LPCWSTR lpszStr, DWORD dwFlags, LPINT lpiRet)
{
    struct qemu_StrToIntExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINTEXW);
    call.lpszStr = (uint64_t)lpszStr;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpiRet = (uint64_t)lpiRet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrToIntExW to Wine headers? */
extern BOOL WINAPI StrToIntExW(LPCWSTR lpszStr, DWORD dwFlags, LPINT lpiRet);
void qemu_StrToIntExW(struct qemu_syscall *call)
{
    struct qemu_StrToIntExW *c = (struct qemu_StrToIntExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrToIntExW(QEMU_G2H(c->lpszStr), c->dwFlags, QEMU_G2H(c->lpiRet));
}

#endif

struct qemu_StrToInt64ExW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t dwFlags;
    uint64_t lpiRet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrToInt64ExW(LPCWSTR lpszStr, DWORD dwFlags, LONGLONG *lpiRet)
{
    struct qemu_StrToInt64ExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINT64EXW);
    call.lpszStr = (uint64_t)lpszStr;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpiRet = (uint64_t)lpiRet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrToInt64ExW to Wine headers? */
extern BOOL WINAPI StrToInt64ExW(LPCWSTR lpszStr, DWORD dwFlags, LONGLONG *lpiRet);
void qemu_StrToInt64ExW(struct qemu_syscall *call)
{
    struct qemu_StrToInt64ExW *c = (struct qemu_StrToInt64ExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrToInt64ExW(QEMU_G2H(c->lpszStr), c->dwFlags, QEMU_G2H(c->lpiRet));
}

#endif

struct qemu_StrDupA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrDupA(LPCSTR lpszStr)
{
    struct qemu_StrDupA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRDUPA);
    call.lpszStr = (uint64_t)lpszStr;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrDupA to Wine headers? */
extern LPSTR WINAPI StrDupA(LPCSTR lpszStr);
void qemu_StrDupA(struct qemu_syscall *call)
{
    struct qemu_StrDupA *c = (struct qemu_StrDupA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrDupA(QEMU_G2H(c->lpszStr));
}

#endif

struct qemu_StrDupW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrDupW(LPCWSTR lpszStr)
{
    struct qemu_StrDupW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRDUPW);
    call.lpszStr = (uint64_t)lpszStr;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrDupW to Wine headers? */
extern LPWSTR WINAPI StrDupW(LPCWSTR lpszStr);
void qemu_StrDupW(struct qemu_syscall *call)
{
    struct qemu_StrDupW *c = (struct qemu_StrDupW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrDupW(QEMU_G2H(c->lpszStr));
}

#endif

struct qemu_StrSpnA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrSpnA(LPCSTR lpszStr, LPCSTR lpszMatch)
{
    struct qemu_StrSpnA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSPNA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrSpnA to Wine headers? */
extern int WINAPI StrSpnA(LPCSTR lpszStr, LPCSTR lpszMatch);
void qemu_StrSpnA(struct qemu_syscall *call)
{
    struct qemu_StrSpnA *c = (struct qemu_StrSpnA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrSpnA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrSpnW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrSpnW(LPCWSTR lpszStr, LPCWSTR lpszMatch)
{
    struct qemu_StrSpnW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSPNW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrSpnW to Wine headers? */
extern int WINAPI StrSpnW(LPCWSTR lpszStr, LPCWSTR lpszMatch);
void qemu_StrSpnW(struct qemu_syscall *call)
{
    struct qemu_StrSpnW *c = (struct qemu_StrSpnW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrSpnW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrCSpnA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCSpnA(LPCSTR lpszStr, LPCSTR lpszMatch)
{
    struct qemu_StrCSpnA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCSPNA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCSpnA to Wine headers? */
extern int WINAPI StrCSpnA(LPCSTR lpszStr, LPCSTR lpszMatch);
void qemu_StrCSpnA(struct qemu_syscall *call)
{
    struct qemu_StrCSpnA *c = (struct qemu_StrCSpnA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCSpnA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrCSpnW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCSpnW(LPCWSTR lpszStr, LPCWSTR lpszMatch)
{
    struct qemu_StrCSpnW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCSPNW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCSpnW to Wine headers? */
extern int WINAPI StrCSpnW(LPCWSTR lpszStr, LPCWSTR lpszMatch);
void qemu_StrCSpnW(struct qemu_syscall *call)
{
    struct qemu_StrCSpnW *c = (struct qemu_StrCSpnW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCSpnW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrCSpnIA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCSpnIA(LPCSTR lpszStr, LPCSTR lpszMatch)
{
    struct qemu_StrCSpnIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCSPNIA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCSpnIA to Wine headers? */
extern int WINAPI StrCSpnIA(LPCSTR lpszStr, LPCSTR lpszMatch);
void qemu_StrCSpnIA(struct qemu_syscall *call)
{
    struct qemu_StrCSpnIA *c = (struct qemu_StrCSpnIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCSpnIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrCSpnIW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI StrCSpnIW(LPCWSTR lpszStr, LPCWSTR lpszMatch)
{
    struct qemu_StrCSpnIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCSPNIW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCSpnIW to Wine headers? */
extern int WINAPI StrCSpnIW(LPCWSTR lpszStr, LPCWSTR lpszMatch);
void qemu_StrCSpnIW(struct qemu_syscall *call)
{
    struct qemu_StrCSpnIW *c = (struct qemu_StrCSpnIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCSpnIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrPBrkA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrPBrkA(LPCSTR lpszStr, LPCSTR lpszMatch)
{
    struct qemu_StrPBrkA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRPBRKA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrPBrkA to Wine headers? */
extern LPSTR WINAPI StrPBrkA(LPCSTR lpszStr, LPCSTR lpszMatch);
void qemu_StrPBrkA(struct qemu_syscall *call)
{
    struct qemu_StrPBrkA *c = (struct qemu_StrPBrkA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrPBrkA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrPBrkW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszMatch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrPBrkW(LPCWSTR lpszStr, LPCWSTR lpszMatch)
{
    struct qemu_StrPBrkW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRPBRKW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszMatch = (uint64_t)lpszMatch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrPBrkW to Wine headers? */
extern LPWSTR WINAPI StrPBrkW(LPCWSTR lpszStr, LPCWSTR lpszMatch);
void qemu_StrPBrkW(struct qemu_syscall *call)
{
    struct qemu_StrPBrkW *c = (struct qemu_StrPBrkW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrPBrkW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_StrRChrA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszEnd;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrRChrA(LPCSTR lpszStr, LPCSTR lpszEnd, WORD ch)
{
    struct qemu_StrRChrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRCHRA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszEnd = (uint64_t)lpszEnd;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrRChrA to Wine headers? */
extern LPSTR WINAPI StrRChrA(LPCSTR lpszStr, LPCSTR lpszEnd, WORD ch);
void qemu_StrRChrA(struct qemu_syscall *call)
{
    struct qemu_StrRChrA *c = (struct qemu_StrRChrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrRChrA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), c->ch);
}

#endif

struct qemu_StrRChrW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrRChrW(LPCWSTR str, LPCWSTR end, WORD ch)
{
    struct qemu_StrRChrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRCHRW);
    call.str = (uint64_t)str;
    call.end = (uint64_t)end;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrRChrW to Wine headers? */
extern LPWSTR WINAPI StrRChrW(LPCWSTR str, LPCWSTR end, WORD ch);
void qemu_StrRChrW(struct qemu_syscall *call)
{
    struct qemu_StrRChrW *c = (struct qemu_StrRChrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrRChrW(QEMU_G2H(c->str), QEMU_G2H(c->end), c->ch);
}

#endif

struct qemu_StrRChrIA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszEnd;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrRChrIA(LPCSTR lpszStr, LPCSTR lpszEnd, WORD ch)
{
    struct qemu_StrRChrIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRCHRIA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszEnd = (uint64_t)lpszEnd;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrRChrIA to Wine headers? */
extern LPSTR WINAPI StrRChrIA(LPCSTR lpszStr, LPCSTR lpszEnd, WORD ch);
void qemu_StrRChrIA(struct qemu_syscall *call)
{
    struct qemu_StrRChrIA *c = (struct qemu_StrRChrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrRChrIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), c->ch);
}

#endif

struct qemu_StrRChrIW
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrRChrIW(LPCWSTR str, LPCWSTR end, WORD ch)
{
    struct qemu_StrRChrIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRCHRIW);
    call.str = (uint64_t)str;
    call.end = (uint64_t)end;
    call.ch = (uint64_t)ch;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrRChrIW to Wine headers? */
extern LPWSTR WINAPI StrRChrIW(LPCWSTR str, LPCWSTR end, WORD ch);
void qemu_StrRChrIW(struct qemu_syscall *call)
{
    struct qemu_StrRChrIW *c = (struct qemu_StrRChrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrRChrIW(QEMU_G2H(c->str), QEMU_G2H(c->end), c->ch);
}

#endif

struct qemu_StrCatBuffA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszCat;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrCatBuffA(LPSTR lpszStr, LPCSTR lpszCat, INT cchMax)
{
    struct qemu_StrCatBuffA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCATBUFFA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszCat = (uint64_t)lpszCat;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrCatBuffA to Wine headers? */
extern LPSTR WINAPI StrCatBuffA(LPSTR lpszStr, LPCSTR lpszCat, INT cchMax);
void qemu_StrCatBuffA(struct qemu_syscall *call)
{
    struct qemu_StrCatBuffA *c = (struct qemu_StrCatBuffA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCatBuffA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszCat), c->cchMax);
}

#endif

struct qemu_StrCatBuffW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszCat;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrCatBuffW(LPWSTR lpszStr, LPCWSTR lpszCat, INT cchMax)
{
    struct qemu_StrCatBuffW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCATBUFFW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszCat = (uint64_t)lpszCat;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrCatBuffW to Wine headers? */
extern LPWSTR WINAPI StrCatBuffW(LPWSTR lpszStr, LPCWSTR lpszCat, INT cchMax);
void qemu_StrCatBuffW(struct qemu_syscall *call)
{
    struct qemu_StrCatBuffW *c = (struct qemu_StrCatBuffW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCatBuffW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszCat), c->cchMax);
}

#endif

struct qemu_StrRetToBufA
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t pidl;
    uint64_t dest;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI StrRetToBufA (LPSTRRET src, const ITEMIDLIST *pidl, LPSTR dest, UINT len)
{
    struct qemu_StrRetToBufA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRETTOBUFA);
    call.src = (uint64_t)src;
    call.pidl = (uint64_t)pidl;
    call.dest = (uint64_t)dest;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrRetToBufA to Wine headers? */
extern HRESULT WINAPI StrRetToBufA (LPSTRRET src, const ITEMIDLIST *pidl, LPSTR dest, UINT len);
void qemu_StrRetToBufA(struct qemu_syscall *call)
{
    struct qemu_StrRetToBufA *c = (struct qemu_StrRetToBufA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrRetToBufA(QEMU_G2H(c->src), QEMU_G2H(c->pidl), QEMU_G2H(c->dest), c->len);
}

#endif

struct qemu_StrRetToBufW
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t pidl;
    uint64_t dest;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI StrRetToBufW (LPSTRRET src, const ITEMIDLIST *pidl, LPWSTR dest, UINT len)
{
    struct qemu_StrRetToBufW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRETTOBUFW);
    call.src = (uint64_t)src;
    call.pidl = (uint64_t)pidl;
    call.dest = (uint64_t)dest;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrRetToBufW to Wine headers? */
extern HRESULT WINAPI StrRetToBufW (LPSTRRET src, const ITEMIDLIST *pidl, LPWSTR dest, UINT len);
void qemu_StrRetToBufW(struct qemu_syscall *call)
{
    struct qemu_StrRetToBufW *c = (struct qemu_StrRetToBufW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrRetToBufW(QEMU_G2H(c->src), QEMU_G2H(c->pidl), QEMU_G2H(c->dest), c->len);
}

#endif

struct qemu_StrRetToStrA
{
    struct qemu_syscall super;
    uint64_t lpStrRet;
    uint64_t pidl;
    uint64_t ppszName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI StrRetToStrA(LPSTRRET lpStrRet, const ITEMIDLIST *pidl, LPSTR *ppszName)
{
    struct qemu_StrRetToStrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRETTOSTRA);
    call.lpStrRet = (uint64_t)lpStrRet;
    call.pidl = (uint64_t)pidl;
    call.ppszName = (uint64_t)ppszName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrRetToStrA to Wine headers? */
extern HRESULT WINAPI StrRetToStrA(LPSTRRET lpStrRet, const ITEMIDLIST *pidl, LPSTR *ppszName);
void qemu_StrRetToStrA(struct qemu_syscall *call)
{
    struct qemu_StrRetToStrA *c = (struct qemu_StrRetToStrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrRetToStrA(QEMU_G2H(c->lpStrRet), QEMU_G2H(c->pidl), QEMU_G2H(c->ppszName));
}

#endif

struct qemu_StrRetToStrW
{
    struct qemu_syscall super;
    uint64_t lpStrRet;
    uint64_t pidl;
    uint64_t ppszName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI StrRetToStrW(LPSTRRET lpStrRet, const ITEMIDLIST *pidl, LPWSTR *ppszName)
{
    struct qemu_StrRetToStrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRETTOSTRW);
    call.lpStrRet = (uint64_t)lpStrRet;
    call.pidl = (uint64_t)pidl;
    call.ppszName = (uint64_t)ppszName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrRetToStrW to Wine headers? */
extern HRESULT WINAPI StrRetToStrW(LPSTRRET lpStrRet, const ITEMIDLIST *pidl, LPWSTR *ppszName);
void qemu_StrRetToStrW(struct qemu_syscall *call)
{
    struct qemu_StrRetToStrW *c = (struct qemu_StrRetToStrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrRetToStrW(QEMU_G2H(c->lpStrRet), QEMU_G2H(c->pidl), QEMU_G2H(c->ppszName));
}

#endif

struct qemu_StrRetToBSTR
{
    struct qemu_syscall super;
    uint64_t lpStrRet;
    uint64_t pidl;
    uint64_t pBstrOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI StrRetToBSTR(STRRET *lpStrRet, LPCITEMIDLIST pidl, BSTR* pBstrOut)
{
    struct qemu_StrRetToBSTR call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRETTOBSTR);
    call.lpStrRet = (uint64_t)lpStrRet;
    call.pidl = (uint64_t)pidl;
    call.pBstrOut = (uint64_t)pBstrOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrRetToBSTR to Wine headers? */
extern HRESULT WINAPI StrRetToBSTR(STRRET *lpStrRet, LPCITEMIDLIST pidl, BSTR* pBstrOut);
void qemu_StrRetToBSTR(struct qemu_syscall *call)
{
    struct qemu_StrRetToBSTR *c = (struct qemu_StrRetToBSTR *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrRetToBSTR(QEMU_G2H(c->lpStrRet), QEMU_G2H(c->pidl), QEMU_G2H(c->pBstrOut));
}

#endif

struct qemu_StrFormatKBSizeA
{
    struct qemu_syscall super;
    uint64_t llBytes;
    uint64_t lpszDest;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrFormatKBSizeA(LONGLONG llBytes, LPSTR lpszDest, UINT cchMax)
{
    struct qemu_StrFormatKBSizeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFORMATKBSIZEA);
    call.llBytes = (uint64_t)llBytes;
    call.lpszDest = (uint64_t)lpszDest;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrFormatKBSizeA to Wine headers? */
extern LPSTR WINAPI StrFormatKBSizeA(LONGLONG llBytes, LPSTR lpszDest, UINT cchMax);
void qemu_StrFormatKBSizeA(struct qemu_syscall *call)
{
    struct qemu_StrFormatKBSizeA *c = (struct qemu_StrFormatKBSizeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrFormatKBSizeA(c->llBytes, QEMU_G2H(c->lpszDest), c->cchMax);
}

#endif

struct qemu_StrFormatKBSizeW
{
    struct qemu_syscall super;
    uint64_t llBytes;
    uint64_t lpszDest;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrFormatKBSizeW(LONGLONG llBytes, LPWSTR lpszDest, UINT cchMax)
{
    struct qemu_StrFormatKBSizeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFORMATKBSIZEW);
    call.llBytes = (uint64_t)llBytes;
    call.lpszDest = (uint64_t)lpszDest;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrFormatKBSizeW to Wine headers? */
extern LPWSTR WINAPI StrFormatKBSizeW(LONGLONG llBytes, LPWSTR lpszDest, UINT cchMax);
void qemu_StrFormatKBSizeW(struct qemu_syscall *call)
{
    struct qemu_StrFormatKBSizeW *c = (struct qemu_StrFormatKBSizeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrFormatKBSizeW(c->llBytes, QEMU_G2H(c->lpszDest), c->cchMax);
}

#endif

struct qemu_StrNCatA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszCat;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrNCatA(LPSTR lpszStr, LPCSTR lpszCat, INT cchMax)
{
    struct qemu_StrNCatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCATA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszCat = (uint64_t)lpszCat;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrNCatA to Wine headers? */
extern LPSTR WINAPI StrNCatA(LPSTR lpszStr, LPCSTR lpszCat, INT cchMax);
void qemu_StrNCatA(struct qemu_syscall *call)
{
    struct qemu_StrNCatA *c = (struct qemu_StrNCatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrNCatA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszCat), c->cchMax);
}

#endif

struct qemu_StrNCatW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszCat;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrNCatW(LPWSTR lpszStr, LPCWSTR lpszCat, INT cchMax)
{
    struct qemu_StrNCatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCATW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszCat = (uint64_t)lpszCat;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrNCatW to Wine headers? */
extern LPWSTR WINAPI StrNCatW(LPWSTR lpszStr, LPCWSTR lpszCat, INT cchMax);
void qemu_StrNCatW(struct qemu_syscall *call)
{
    struct qemu_StrNCatW *c = (struct qemu_StrNCatW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrNCatW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszCat), c->cchMax);
}

#endif

struct qemu_StrTrimA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszTrim;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrTrimA(LPSTR lpszStr, LPCSTR lpszTrim)
{
    struct qemu_StrTrimA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTRIMA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszTrim = (uint64_t)lpszTrim;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrTrimA to Wine headers? */
extern BOOL WINAPI StrTrimA(LPSTR lpszStr, LPCSTR lpszTrim);
void qemu_StrTrimA(struct qemu_syscall *call)
{
    struct qemu_StrTrimA *c = (struct qemu_StrTrimA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrTrimA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszTrim));
}

#endif

struct qemu_StrTrimW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszTrim;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrTrimW(LPWSTR lpszStr, LPCWSTR lpszTrim)
{
    struct qemu_StrTrimW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTRIMW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszTrim = (uint64_t)lpszTrim;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrTrimW to Wine headers? */
extern BOOL WINAPI StrTrimW(LPWSTR lpszStr, LPCWSTR lpszTrim);
void qemu_StrTrimW(struct qemu_syscall *call)
{
    struct qemu_StrTrimW *c = (struct qemu_StrTrimW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrTrimW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszTrim));
}

#endif

struct qemu_SHStrDupA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lppszDest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHStrDupA(LPCSTR lpszStr, LPWSTR * lppszDest)
{
    struct qemu_SHStrDupA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSTRDUPA);
    call.lpszStr = (uint64_t)lpszStr;
    call.lppszDest = (uint64_t)lppszDest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHStrDupA to Wine headers? */
extern HRESULT WINAPI SHStrDupA(LPCSTR lpszStr, LPWSTR * lppszDest);
void qemu_SHStrDupA(struct qemu_syscall *call)
{
    struct qemu_SHStrDupA *c = (struct qemu_SHStrDupA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHStrDupA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lppszDest));
}

#endif

struct qemu_SHStrDupW
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHStrDupW(LPCWSTR src, LPWSTR * dest)
{
    struct qemu_SHStrDupW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSTRDUPW);
    call.src = (uint64_t)src;
    call.dest = (uint64_t)dest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHStrDupW to Wine headers? */
extern HRESULT WINAPI SHStrDupW(LPCWSTR src, LPWSTR * dest);
void qemu_SHStrDupW(struct qemu_syscall *call)
{
    struct qemu_SHStrDupW *c = (struct qemu_SHStrDupW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHStrDupW(QEMU_G2H(c->src), QEMU_G2H(c->dest));
}

#endif

struct qemu_StrFromTimeIntervalA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t cchMax;
    uint64_t dwMS;
    uint64_t iDigits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrFromTimeIntervalA(LPSTR lpszStr, UINT cchMax, DWORD dwMS, int iDigits)
{
    struct qemu_StrFromTimeIntervalA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFROMTIMEINTERVALA);
    call.lpszStr = (uint64_t)lpszStr;
    call.cchMax = (uint64_t)cchMax;
    call.dwMS = (uint64_t)dwMS;
    call.iDigits = (uint64_t)iDigits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrFromTimeIntervalA to Wine headers? */
extern INT WINAPI StrFromTimeIntervalA(LPSTR lpszStr, UINT cchMax, DWORD dwMS, int iDigits);
void qemu_StrFromTimeIntervalA(struct qemu_syscall *call)
{
    struct qemu_StrFromTimeIntervalA *c = (struct qemu_StrFromTimeIntervalA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrFromTimeIntervalA(QEMU_G2H(c->lpszStr), c->cchMax, c->dwMS, c->iDigits);
}

#endif

struct qemu_StrFromTimeIntervalW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t cchMax;
    uint64_t dwMS;
    uint64_t iDigits;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrFromTimeIntervalW(LPWSTR lpszStr, UINT cchMax, DWORD dwMS, int iDigits)
{
    struct qemu_StrFromTimeIntervalW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFROMTIMEINTERVALW);
    call.lpszStr = (uint64_t)lpszStr;
    call.cchMax = (uint64_t)cchMax;
    call.dwMS = (uint64_t)dwMS;
    call.iDigits = (uint64_t)iDigits;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrFromTimeIntervalW to Wine headers? */
extern INT WINAPI StrFromTimeIntervalW(LPWSTR lpszStr, UINT cchMax, DWORD dwMS, int iDigits);
void qemu_StrFromTimeIntervalW(struct qemu_syscall *call)
{
    struct qemu_StrFromTimeIntervalW *c = (struct qemu_StrFromTimeIntervalW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrFromTimeIntervalW(QEMU_G2H(c->lpszStr), c->cchMax, c->dwMS, c->iDigits);
}

#endif

struct qemu_StrIsIntlEqualA
{
    struct qemu_syscall super;
    uint64_t bCase;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrIsIntlEqualA(BOOL bCase, LPCSTR lpszStr, LPCSTR lpszComp, int iLen)
{
    struct qemu_StrIsIntlEqualA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRISINTLEQUALA);
    call.bCase = (uint64_t)bCase;
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrIsIntlEqualA to Wine headers? */
extern BOOL WINAPI StrIsIntlEqualA(BOOL bCase, LPCSTR lpszStr, LPCSTR lpszComp, int iLen);
void qemu_StrIsIntlEqualA(struct qemu_syscall *call)
{
    struct qemu_StrIsIntlEqualA *c = (struct qemu_StrIsIntlEqualA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrIsIntlEqualA(c->bCase, QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_StrIsIntlEqualW
{
    struct qemu_syscall super;
    uint64_t bCase;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrIsIntlEqualW(BOOL bCase, LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen)
{
    struct qemu_StrIsIntlEqualW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRISINTLEQUALW);
    call.bCase = (uint64_t)bCase;
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrIsIntlEqualW to Wine headers? */
extern BOOL WINAPI StrIsIntlEqualW(BOOL bCase, LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen);
void qemu_StrIsIntlEqualW(struct qemu_syscall *call)
{
    struct qemu_StrIsIntlEqualW *c = (struct qemu_StrIsIntlEqualW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrIsIntlEqualW(c->bCase, QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_StrCpyNXA
{
    struct qemu_syscall super;
    uint64_t lpszDest;
    uint64_t lpszSrc;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrCpyNXA(LPSTR lpszDest, LPCSTR lpszSrc, int iLen)
{
    struct qemu_StrCpyNXA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPYNXA);
    call.lpszDest = (uint64_t)lpszDest;
    call.lpszSrc = (uint64_t)lpszSrc;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrCpyNXA to Wine headers? */
extern LPSTR WINAPI StrCpyNXA(LPSTR lpszDest, LPCSTR lpszSrc, int iLen);
void qemu_StrCpyNXA(struct qemu_syscall *call)
{
    struct qemu_StrCpyNXA *c = (struct qemu_StrCpyNXA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCpyNXA(QEMU_G2H(c->lpszDest), QEMU_G2H(c->lpszSrc), c->iLen);
}

#endif

struct qemu_StrCpyNXW
{
    struct qemu_syscall super;
    uint64_t lpszDest;
    uint64_t lpszSrc;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrCpyNXW(LPWSTR lpszDest, LPCWSTR lpszSrc, int iLen)
{
    struct qemu_StrCpyNXW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPYNXW);
    call.lpszDest = (uint64_t)lpszDest;
    call.lpszSrc = (uint64_t)lpszSrc;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrCpyNXW to Wine headers? */
extern LPWSTR WINAPI StrCpyNXW(LPWSTR lpszDest, LPCWSTR lpszSrc, int iLen);
void qemu_StrCpyNXW(struct qemu_syscall *call)
{
    struct qemu_StrCpyNXW *c = (struct qemu_StrCpyNXW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrCpyNXW(QEMU_G2H(c->lpszDest), QEMU_G2H(c->lpszSrc), c->iLen);
}

#endif

struct qemu_StrCmpLogicalW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
    uint64_t lpszComp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrCmpLogicalW(LPCWSTR lpszStr, LPCWSTR lpszComp)
{
    struct qemu_StrCmpLogicalW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPLOGICALW);
    call.lpszStr = (uint64_t)lpszStr;
    call.lpszComp = (uint64_t)lpszComp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StrCmpLogicalW to Wine headers? */
extern INT WINAPI StrCmpLogicalW(LPCWSTR lpszStr, LPCWSTR lpszComp);
void qemu_StrCmpLogicalW(struct qemu_syscall *call)
{
    struct qemu_StrCmpLogicalW *c = (struct qemu_StrCmpLogicalW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StrCmpLogicalW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp));
}

#endif

struct qemu_StrFormatByteSizeW
{
    struct qemu_syscall super;
    uint64_t llBytes;
    uint64_t lpszDest;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StrFormatByteSizeW(LONGLONG llBytes, LPWSTR lpszDest, UINT cchMax)
{
    struct qemu_StrFormatByteSizeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFORMATBYTESIZEW);
    call.llBytes = (uint64_t)llBytes;
    call.lpszDest = (uint64_t)lpszDest;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPWSTR)call.super.iret;
}

#else

/* TODO: Add StrFormatByteSizeW to Wine headers? */
extern LPWSTR WINAPI StrFormatByteSizeW(LONGLONG llBytes, LPWSTR lpszDest, UINT cchMax);
void qemu_StrFormatByteSizeW(struct qemu_syscall *call)
{
    struct qemu_StrFormatByteSizeW *c = (struct qemu_StrFormatByteSizeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrFormatByteSizeW(c->llBytes, QEMU_G2H(c->lpszDest), c->cchMax);
}

#endif

struct qemu_StrFormatByteSize64A
{
    struct qemu_syscall super;
    uint64_t llBytes;
    uint64_t lpszDest;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrFormatByteSize64A(LONGLONG llBytes, LPSTR lpszDest, UINT cchMax)
{
    struct qemu_StrFormatByteSize64A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFORMATBYTESIZE64A);
    call.llBytes = (uint64_t)llBytes;
    call.lpszDest = (uint64_t)lpszDest;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrFormatByteSize64A to Wine headers? */
extern LPSTR WINAPI StrFormatByteSize64A(LONGLONG llBytes, LPSTR lpszDest, UINT cchMax);
void qemu_StrFormatByteSize64A(struct qemu_syscall *call)
{
    struct qemu_StrFormatByteSize64A *c = (struct qemu_StrFormatByteSize64A *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrFormatByteSize64A(c->llBytes, QEMU_G2H(c->lpszDest), c->cchMax);
}

#endif

struct qemu_StrFormatByteSizeA
{
    struct qemu_syscall super;
    uint64_t dwBytes;
    uint64_t lpszDest;
    uint64_t cchMax;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StrFormatByteSizeA(DWORD dwBytes, LPSTR lpszDest, UINT cchMax)
{
    struct qemu_StrFormatByteSizeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFORMATBYTESIZEA);
    call.dwBytes = (uint64_t)dwBytes;
    call.lpszDest = (uint64_t)lpszDest;
    call.cchMax = (uint64_t)cchMax;

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

/* TODO: Add StrFormatByteSizeA to Wine headers? */
extern LPSTR WINAPI StrFormatByteSizeA(DWORD dwBytes, LPSTR lpszDest, UINT cchMax);
void qemu_StrFormatByteSizeA(struct qemu_syscall *call)
{
    struct qemu_StrFormatByteSizeA *c = (struct qemu_StrFormatByteSizeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StrFormatByteSizeA(c->dwBytes, QEMU_G2H(c->lpszDest), c->cchMax);
}

#endif

struct qemu_SHTruncateString
{
    struct qemu_syscall super;
    uint64_t lpStr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHTruncateString(LPSTR lpStr, DWORD size)
{
    struct qemu_SHTruncateString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHTRUNCATESTRING);
    call.lpStr = (uint64_t)lpStr;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHTruncateString to Wine headers? */
extern DWORD WINAPI SHTruncateString(LPSTR lpStr, DWORD size);
void qemu_SHTruncateString(struct qemu_syscall *call)
{
    struct qemu_SHTruncateString *c = (struct qemu_SHTruncateString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHTruncateString(QEMU_G2H(c->lpStr), c->size);
}

#endif

struct qemu_SHStripMneumonicA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char WINAPI SHStripMneumonicA(LPCSTR lpszStr)
{
    struct qemu_SHStripMneumonicA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSTRIPMNEUMONICA);
    call.lpszStr = (uint64_t)lpszStr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHStripMneumonicA to Wine headers? */
extern char WINAPI SHStripMneumonicA(LPCSTR lpszStr);
void qemu_SHStripMneumonicA(struct qemu_syscall *call)
{
    struct qemu_SHStripMneumonicA *c = (struct qemu_SHStripMneumonicA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHStripMneumonicA(QEMU_G2H(c->lpszStr));
}

#endif

struct qemu_SHStripMneumonicW
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR WINAPI SHStripMneumonicW(LPCWSTR lpszStr)
{
    struct qemu_SHStripMneumonicW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSTRIPMNEUMONICW);
    call.lpszStr = (uint64_t)lpszStr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHStripMneumonicW to Wine headers? */
extern WCHAR WINAPI SHStripMneumonicW(LPCWSTR lpszStr);
void qemu_SHStripMneumonicW(struct qemu_syscall *call)
{
    struct qemu_SHStripMneumonicW *c = (struct qemu_SHStripMneumonicW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHStripMneumonicW(QEMU_G2H(c->lpszStr));
}

#endif

struct qemu_SHAnsiToUnicodeCP
{
    struct qemu_syscall super;
    uint64_t dwCp;
    uint64_t lpSrcStr;
    uint64_t lpDstStr;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHAnsiToUnicodeCP(DWORD dwCp, LPCSTR lpSrcStr, LPWSTR lpDstStr, int iLen)
{
    struct qemu_SHAnsiToUnicodeCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHANSITOUNICODECP);
    call.dwCp = (uint64_t)dwCp;
    call.lpSrcStr = (uint64_t)lpSrcStr;
    call.lpDstStr = (uint64_t)lpDstStr;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHAnsiToUnicodeCP to Wine headers? */
extern DWORD WINAPI SHAnsiToUnicodeCP(DWORD dwCp, LPCSTR lpSrcStr, LPWSTR lpDstStr, int iLen);
void qemu_SHAnsiToUnicodeCP(struct qemu_syscall *call)
{
    struct qemu_SHAnsiToUnicodeCP *c = (struct qemu_SHAnsiToUnicodeCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAnsiToUnicodeCP(c->dwCp, QEMU_G2H(c->lpSrcStr), QEMU_G2H(c->lpDstStr), c->iLen);
}

#endif

struct qemu_SHAnsiToUnicode
{
    struct qemu_syscall super;
    uint64_t lpSrcStr;
    uint64_t lpDstStr;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHAnsiToUnicode(LPCSTR lpSrcStr, LPWSTR lpDstStr, int iLen)
{
    struct qemu_SHAnsiToUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHANSITOUNICODE);
    call.lpSrcStr = (uint64_t)lpSrcStr;
    call.lpDstStr = (uint64_t)lpDstStr;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHAnsiToUnicode to Wine headers? */
extern DWORD WINAPI SHAnsiToUnicode(LPCSTR lpSrcStr, LPWSTR lpDstStr, int iLen);
void qemu_SHAnsiToUnicode(struct qemu_syscall *call)
{
    struct qemu_SHAnsiToUnicode *c = (struct qemu_SHAnsiToUnicode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAnsiToUnicode(QEMU_G2H(c->lpSrcStr), QEMU_G2H(c->lpDstStr), c->iLen);
}

#endif

struct qemu_SHUnicodeToAnsiCP
{
    struct qemu_syscall super;
    uint64_t CodePage;
    uint64_t lpSrcStr;
    uint64_t lpDstStr;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHUnicodeToAnsiCP(UINT CodePage, LPCWSTR lpSrcStr, LPSTR lpDstStr, int dstlen)
{
    struct qemu_SHUnicodeToAnsiCP call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUNICODETOANSICP);
    call.CodePage = (uint64_t)CodePage;
    call.lpSrcStr = (uint64_t)lpSrcStr;
    call.lpDstStr = (uint64_t)lpDstStr;
    call.dstlen = (uint64_t)dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHUnicodeToAnsiCP to Wine headers? */
extern DWORD WINAPI SHUnicodeToAnsiCP(UINT CodePage, LPCWSTR lpSrcStr, LPSTR lpDstStr, int dstlen);
void qemu_SHUnicodeToAnsiCP(struct qemu_syscall *call)
{
    struct qemu_SHUnicodeToAnsiCP *c = (struct qemu_SHUnicodeToAnsiCP *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHUnicodeToAnsiCP(c->CodePage, QEMU_G2H(c->lpSrcStr), QEMU_G2H(c->lpDstStr), c->dstlen);
}

#endif

struct qemu_SHUnicodeToAnsi
{
    struct qemu_syscall super;
    uint64_t lpSrcStr;
    uint64_t lpDstStr;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SHUnicodeToAnsi(LPCWSTR lpSrcStr, LPSTR lpDstStr, INT iLen)
{
    struct qemu_SHUnicodeToAnsi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUNICODETOANSI);
    call.lpSrcStr = (uint64_t)lpSrcStr;
    call.lpDstStr = (uint64_t)lpDstStr;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHUnicodeToAnsi to Wine headers? */
extern INT WINAPI SHUnicodeToAnsi(LPCWSTR lpSrcStr, LPSTR lpDstStr, INT iLen);
void qemu_SHUnicodeToAnsi(struct qemu_syscall *call)
{
    struct qemu_SHUnicodeToAnsi *c = (struct qemu_SHUnicodeToAnsi *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHUnicodeToAnsi(QEMU_G2H(c->lpSrcStr), QEMU_G2H(c->lpDstStr), c->iLen);
}

#endif

struct qemu_SHAnsiToAnsi
{
    struct qemu_syscall super;
    uint64_t lpszSrc;
    uint64_t lpszDst;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHAnsiToAnsi(LPCSTR lpszSrc, LPSTR lpszDst, int iLen)
{
    struct qemu_SHAnsiToAnsi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHANSITOANSI);
    call.lpszSrc = (uint64_t)lpszSrc;
    call.lpszDst = (uint64_t)lpszDst;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHAnsiToAnsi to Wine headers? */
extern DWORD WINAPI SHAnsiToAnsi(LPCSTR lpszSrc, LPSTR lpszDst, int iLen);
void qemu_SHAnsiToAnsi(struct qemu_syscall *call)
{
    struct qemu_SHAnsiToAnsi *c = (struct qemu_SHAnsiToAnsi *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAnsiToAnsi(QEMU_G2H(c->lpszSrc), QEMU_G2H(c->lpszDst), c->iLen);
}

#endif

struct qemu_SHUnicodeToUnicode
{
    struct qemu_syscall super;
    uint64_t lpszSrc;
    uint64_t lpszDst;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHUnicodeToUnicode(LPCWSTR lpszSrc, LPWSTR lpszDst, int iLen)
{
    struct qemu_SHUnicodeToUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHUNICODETOUNICODE);
    call.lpszSrc = (uint64_t)lpszSrc;
    call.lpszDst = (uint64_t)lpszDst;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHUnicodeToUnicode to Wine headers? */
extern DWORD WINAPI SHUnicodeToUnicode(LPCWSTR lpszSrc, LPWSTR lpszDst, int iLen);
void qemu_SHUnicodeToUnicode(struct qemu_syscall *call)
{
    struct qemu_SHUnicodeToUnicode *c = (struct qemu_SHUnicodeToUnicode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHUnicodeToUnicode(QEMU_G2H(c->lpszSrc), QEMU_G2H(c->lpszDst), c->iLen);
}

#endif

struct qemu_DoesStringRoundTripA
{
    struct qemu_syscall super;
    uint64_t lpSrcStr;
    uint64_t lpDst;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DoesStringRoundTripA(LPCSTR lpSrcStr, LPSTR lpDst, INT iLen)
{
    struct qemu_DoesStringRoundTripA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOESSTRINGROUNDTRIPA);
    call.lpSrcStr = (uint64_t)lpSrcStr;
    call.lpDst = (uint64_t)lpDst;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DoesStringRoundTripA to Wine headers? */
extern BOOL WINAPI DoesStringRoundTripA(LPCSTR lpSrcStr, LPSTR lpDst, INT iLen);
void qemu_DoesStringRoundTripA(struct qemu_syscall *call)
{
    struct qemu_DoesStringRoundTripA *c = (struct qemu_DoesStringRoundTripA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DoesStringRoundTripA(QEMU_G2H(c->lpSrcStr), QEMU_G2H(c->lpDst), c->iLen);
}

#endif

struct qemu_DoesStringRoundTripW
{
    struct qemu_syscall super;
    uint64_t lpSrcStr;
    uint64_t lpDst;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DoesStringRoundTripW(LPCWSTR lpSrcStr, LPSTR lpDst, INT iLen)
{
    struct qemu_DoesStringRoundTripW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOESSTRINGROUNDTRIPW);
    call.lpSrcStr = (uint64_t)lpSrcStr;
    call.lpDst = (uint64_t)lpDst;
    call.iLen = (uint64_t)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DoesStringRoundTripW to Wine headers? */
extern BOOL WINAPI DoesStringRoundTripW(LPCWSTR lpSrcStr, LPSTR lpDst, INT iLen);
void qemu_DoesStringRoundTripW(struct qemu_syscall *call)
{
    struct qemu_DoesStringRoundTripW *c = (struct qemu_DoesStringRoundTripW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DoesStringRoundTripW(QEMU_G2H(c->lpSrcStr), QEMU_G2H(c->lpDst), c->iLen);
}

#endif

struct qemu_SHLoadIndirectString
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dst;
    uint64_t dst_len;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHLoadIndirectString(LPCWSTR src, LPWSTR dst, UINT dst_len, void **reserved)
{
    struct qemu_SHLoadIndirectString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLOADINDIRECTSTRING);
    call.src = (uint64_t)src;
    call.dst = (uint64_t)dst;
    call.dst_len = (uint64_t)dst_len;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHLoadIndirectString to Wine headers? */
extern HRESULT WINAPI SHLoadIndirectString(LPCWSTR src, LPWSTR dst, UINT dst_len, void **reserved);
void qemu_SHLoadIndirectString(struct qemu_syscall *call)
{
    struct qemu_SHLoadIndirectString *c = (struct qemu_SHLoadIndirectString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHLoadIndirectString(QEMU_G2H(c->src), QEMU_G2H(c->dst), c->dst_len, QEMU_G2H(c->reserved));
}

#endif

struct qemu_IsCharSpaceA
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsCharSpaceA(CHAR c)
{
    struct qemu_IsCharSpaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARSPACEA);
    call.c = (uint64_t)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsCharSpaceA to Wine headers? */
extern BOOL WINAPI IsCharSpaceA(CHAR c);
void qemu_IsCharSpaceA(struct qemu_syscall *call)
{
    struct qemu_IsCharSpaceA *c = (struct qemu_IsCharSpaceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharSpaceA(c->c);
}

#endif

struct qemu_IsCharSpaceW
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsCharSpaceW(WCHAR wc)
{
    struct qemu_IsCharSpaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCHARSPACEW);
    call.wc = (uint64_t)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsCharSpaceW to Wine headers? */
extern BOOL WINAPI IsCharSpaceW(WCHAR wc);
void qemu_IsCharSpaceW(struct qemu_syscall *call)
{
    struct qemu_IsCharSpaceW *c = (struct qemu_IsCharSpaceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsCharSpaceW(c->wc);
}

#endif

