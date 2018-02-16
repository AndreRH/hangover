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
#include <commctrl.h>
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif

/* FIXME: Most of these import the host counterpart from shlwapi.dll, not comctl32.dll because
 * the comctl32 exports are private ordinal-only exports and I don't feel like collecting them
 * with GetProcAddress at the moment. */

struct qemu_Str_GetPtrA
{
    struct qemu_syscall super;
    uint64_t lpSrc;
    uint64_t lpDest;
    uint64_t nMaxLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI Str_GetPtrA (LPCSTR lpSrc, LPSTR lpDest, INT nMaxLen)
{
    struct qemu_Str_GetPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STR_GETPTRA);
    call.lpSrc = (ULONG_PTR)lpSrc;
    call.lpDest = (ULONG_PTR)lpDest;
    call.nMaxLen = nMaxLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI Str_GetPtrA (LPCSTR lpSrc, LPSTR lpDest, INT nMaxLen);
void qemu_Str_GetPtrA(struct qemu_syscall *call)
{
    struct qemu_Str_GetPtrA *c = (struct qemu_Str_GetPtrA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_Str_GetPtrA(QEMU_G2H(c->lpSrc), QEMU_G2H(c->lpDest), c->nMaxLen);
}

#endif

struct qemu_Str_SetPtrA
{
    struct qemu_syscall super;
    uint64_t lppDest;
    uint64_t lpSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Str_SetPtrA (LPSTR *lppDest, LPCSTR lpSrc)
{
    struct qemu_Str_SetPtrA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STR_SETPTRA);
    call.lppDest = (ULONG_PTR)lppDest;
    call.lpSrc = (ULONG_PTR)lpSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI Str_SetPtrA (LPSTR *lppDest, LPCSTR lpSrc);
void qemu_Str_SetPtrA(struct qemu_syscall *call)
{
    struct qemu_Str_SetPtrA *c = (struct qemu_Str_SetPtrA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_Str_SetPtrA(QEMU_G2H(c->lppDest), QEMU_G2H(c->lpSrc));
}

#endif

struct qemu_Str_GetPtrW
{
    struct qemu_syscall super;
    uint64_t lpSrc;
    uint64_t lpDest;
    uint64_t nMaxLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI Str_GetPtrW (LPCWSTR lpSrc, LPWSTR lpDest, INT nMaxLen)
{
    struct qemu_Str_GetPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STR_GETPTRW);
    call.lpSrc = (ULONG_PTR)lpSrc;
    call.lpDest = (ULONG_PTR)lpDest;
    call.nMaxLen = nMaxLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI Str_GetPtrW (LPCWSTR lpSrc, LPWSTR lpDest, INT nMaxLen);
void qemu_Str_GetPtrW(struct qemu_syscall *call)
{
    struct qemu_Str_GetPtrW *c = (struct qemu_Str_GetPtrW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_Str_GetPtrW(QEMU_G2H(c->lpSrc), QEMU_G2H(c->lpDest), c->nMaxLen);
}

#endif

struct qemu_Str_SetPtrW
{
    struct qemu_syscall super;
    uint64_t lppDest;
    uint64_t lpSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Str_SetPtrW (LPWSTR *lppDest, LPCWSTR lpSrc)
{
    struct qemu_Str_SetPtrW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STR_SETPTRW);
    call.lppDest = (ULONG_PTR)lppDest;
    call.lpSrc = (ULONG_PTR)lpSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Str_SetPtrW(struct qemu_syscall *call)
{
    struct qemu_Str_SetPtrW *c = (struct qemu_Str_SetPtrW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_Str_SetPtrW(QEMU_G2H(c->lppDest), QEMU_G2H(c->lpSrc));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrChrA(struct qemu_syscall *call)
{
    struct qemu_StrChrA *c = (struct qemu_StrChrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrChrA(QEMU_G2H(c->lpszStr), c->ch);
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

WINBASEAPI INT WINAPI StrCmpNIA(LPCSTR lpszStr, LPCSTR lpszComp, INT iLen)
{
    struct qemu_StrCmpNIA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNIA);
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszComp = (ULONG_PTR)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCmpNIA(struct qemu_syscall *call)
{
    struct qemu_StrCmpNIA *c = (struct qemu_StrCmpNIA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCmpNIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
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

WINBASEAPI INT WINAPI StrCmpNIW(LPCWSTR lpszStr, LPCWSTR lpszComp, INT iLen)
{
    struct qemu_StrCmpNIW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMPNIW);
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszComp = (ULONG_PTR)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCmpNIW(struct qemu_syscall *call)
{
    struct qemu_StrCmpNIW *c = (struct qemu_StrCmpNIW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCmpNIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszSearch = (ULONG_PTR)lpszSearch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrStrIA(struct qemu_syscall *call)
{
    struct qemu_StrStrIA *c = (struct qemu_StrStrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrStrIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrToIntA
{
    struct qemu_syscall super;
    uint64_t lpszStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrToIntA (LPCSTR lpszStr)
{
    struct qemu_StrToIntA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINTA);
    call.lpszStr = (ULONG_PTR)lpszStr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrToIntA(struct qemu_syscall *call)
{
    struct qemu_StrToIntA *c = (struct qemu_StrToIntA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrToIntA(QEMU_G2H(c->lpszStr));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszSearch = (ULONG_PTR)lpszSearch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrStrIW(struct qemu_syscall *call)
{
    struct qemu_StrStrIW *c = (struct qemu_StrStrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrStrIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
}

#endif

struct qemu_StrToIntW
{
    struct qemu_syscall super;
    uint64_t lpString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI StrToIntW (LPCWSTR lpString)
{
    struct qemu_StrToIntW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOINTW);
    call.lpString = (ULONG_PTR)lpString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrToIntW(struct qemu_syscall *call)
{
    struct qemu_StrToIntW *c = (struct qemu_StrToIntW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrToIntW(QEMU_G2H(c->lpString));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszMatch = (ULONG_PTR)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCSpnA(struct qemu_syscall *call)
{
    struct qemu_StrCSpnA *c = (struct qemu_StrCSpnA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCSpnA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrChrW(struct qemu_syscall *call)
{
    struct qemu_StrChrW *c = (struct qemu_StrChrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrChrW(QEMU_G2H(c->lpszStr), c->ch);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszComp = (ULONG_PTR)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCmpNA(struct qemu_syscall *call)
{
    struct qemu_StrCmpNA *c = (struct qemu_StrCmpNA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCmpNA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszComp = (ULONG_PTR)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCmpNW(struct qemu_syscall *call)
{
    struct qemu_StrCmpNW *c = (struct qemu_StrCmpNW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCmpNW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszEnd = (ULONG_PTR)lpszEnd;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrRChrA(struct qemu_syscall *call)
{
    struct qemu_StrRChrA *c = (struct qemu_StrRChrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrRChrA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), c->ch);
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
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrRChrW(struct qemu_syscall *call)
{
    struct qemu_StrRChrW *c = (struct qemu_StrRChrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrRChrW(QEMU_G2H(c->str), QEMU_G2H(c->end), c->ch);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszSearch = (ULONG_PTR)lpszSearch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrStrA(struct qemu_syscall *call)
{
    struct qemu_StrStrA *c = (struct qemu_StrStrA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrStrA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszSearch = (ULONG_PTR)lpszSearch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrStrW(struct qemu_syscall *call)
{
    struct qemu_StrStrW *c = (struct qemu_StrStrW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrStrW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszSearch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrChrIA(struct qemu_syscall *call)
{
    struct qemu_StrChrIA *c = (struct qemu_StrChrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrChrIA(QEMU_G2H(c->lpszStr), c->ch);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrChrIW(struct qemu_syscall *call)
{
    struct qemu_StrChrIW *c = (struct qemu_StrChrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrChrIW(QEMU_G2H(c->lpszStr), c->ch);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszEnd = (ULONG_PTR)lpszEnd;
    call.lpszSearch = (ULONG_PTR)lpszSearch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrRStrIA(struct qemu_syscall *call)
{
    struct qemu_StrRStrIA *c = (struct qemu_StrRStrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrRStrIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), QEMU_G2H(c->lpszSearch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszEnd = (ULONG_PTR)lpszEnd;
    call.lpszSearch = (ULONG_PTR)lpszSearch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrRStrIW(struct qemu_syscall *call)
{
    struct qemu_StrRStrIW *c = (struct qemu_StrRStrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrRStrIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), QEMU_G2H(c->lpszSearch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszMatch = (ULONG_PTR)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCSpnIA(struct qemu_syscall *call)
{
    struct qemu_StrCSpnIA *c = (struct qemu_StrCSpnIA *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCSpnIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszMatch = (ULONG_PTR)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCSpnIW(struct qemu_syscall *call)
{
    struct qemu_StrCSpnIW *c = (struct qemu_StrCSpnIW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCSpnIW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszEnd = (ULONG_PTR)lpszEnd;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrRChrIA(struct qemu_syscall *call)
{
    struct qemu_StrRChrIA *c = (struct qemu_StrRChrIA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrRChrIA(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszEnd), c->ch);
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
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StrRChrIW(struct qemu_syscall *call)
{
    struct qemu_StrRChrIW *c = (struct qemu_StrRChrIW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)StrRChrIW(QEMU_G2H(c->str), QEMU_G2H(c->end), c->ch);
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
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszMatch = (ULONG_PTR)lpszMatch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrCSpnW(struct qemu_syscall *call)
{
    struct qemu_StrCSpnW *c = (struct qemu_StrCSpnW *)call;
    WINE_FIXME("Unverified!\n");
     c->super.iret = p_StrCSpnW(QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszMatch));
}

#endif

struct qemu_IntlStrEqWorkerA
{
    struct qemu_syscall super;
    uint64_t bCase;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IntlStrEqWorkerA(BOOL bCase, LPCSTR lpszStr, LPCSTR lpszComp, int iLen)
{
    struct qemu_IntlStrEqWorkerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTLSTREQWORKERA);
    call.bCase = bCase;
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszComp = (ULONG_PTR)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IntlStrEqWorkerA(struct qemu_syscall *call)
{
    struct qemu_IntlStrEqWorkerA *c = (struct qemu_IntlStrEqWorkerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IntlStrEqWorkerA(c->bCase, QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

struct qemu_IntlStrEqWorkerW
{
    struct qemu_syscall super;
    uint64_t bCase;
    uint64_t lpszStr;
    uint64_t lpszComp;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IntlStrEqWorkerW(BOOL bCase, LPCWSTR lpszStr, LPCWSTR lpszComp, int iLen)
{
    struct qemu_IntlStrEqWorkerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTLSTREQWORKERW);
    call.bCase = bCase;
    call.lpszStr = (ULONG_PTR)lpszStr;
    call.lpszComp = (ULONG_PTR)lpszComp;
    call.iLen = iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IntlStrEqWorkerW(struct qemu_syscall *call)
{
    struct qemu_IntlStrEqWorkerW *c = (struct qemu_IntlStrEqWorkerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IntlStrEqWorkerW(c->bCase, QEMU_G2H(c->lpszStr), QEMU_G2H(c->lpszComp), c->iLen);
}

#endif

