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
#include "qemu_shlwapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi);
#endif


struct qemu_ParseURLA
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ParseURLA(LPCSTR x, void *y)
{
    struct qemu_ParseURLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PARSEURLA);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ParseURLA(struct qemu_syscall *call)
{
    struct qemu_ParseURLA *c = (struct qemu_ParseURLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ParseURLA(QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_ParseURLW
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ParseURLW(LPCWSTR x, void *y)
{
    struct qemu_ParseURLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PARSEURLW);
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ParseURLW(struct qemu_syscall *call)
{
    struct qemu_ParseURLW *c = (struct qemu_ParseURLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ParseURLW(QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_UrlCanonicalizeA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszCanonicalized;
    uint64_t pcchCanonicalized;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlCanonicalizeA(LPCSTR pszUrl, LPSTR pszCanonicalized, LPDWORD pcchCanonicalized, DWORD dwFlags)
{
    struct qemu_UrlCanonicalizeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCANONICALIZEA);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pszCanonicalized = (ULONG_PTR)pszCanonicalized;
    call.pcchCanonicalized = (ULONG_PTR)pcchCanonicalized;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCanonicalizeA(struct qemu_syscall *call)
{
    struct qemu_UrlCanonicalizeA *c = (struct qemu_UrlCanonicalizeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCanonicalizeA(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszCanonicalized), QEMU_G2H(c->pcchCanonicalized), c->dwFlags);
}

#endif

struct qemu_UrlCanonicalizeW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszCanonicalized;
    uint64_t pcchCanonicalized;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlCanonicalizeW(LPCWSTR pszUrl, LPWSTR pszCanonicalized, LPDWORD pcchCanonicalized, DWORD dwFlags)
{
    struct qemu_UrlCanonicalizeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCANONICALIZEW);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pszCanonicalized = (ULONG_PTR)pszCanonicalized;
    call.pcchCanonicalized = (ULONG_PTR)pcchCanonicalized;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCanonicalizeW(struct qemu_syscall *call)
{
    struct qemu_UrlCanonicalizeW *c = (struct qemu_UrlCanonicalizeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCanonicalizeW(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszCanonicalized), QEMU_G2H(c->pcchCanonicalized), c->dwFlags);
}

#endif

struct qemu_UrlCombineA
{
    struct qemu_syscall super;
    uint64_t pszBase;
    uint64_t pszRelative;
    uint64_t pszCombined;
    uint64_t pcchCombined;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlCombineA(LPCSTR pszBase, LPCSTR pszRelative, LPSTR pszCombined, LPDWORD pcchCombined, DWORD dwFlags)
{
    struct qemu_UrlCombineA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCOMBINEA);
    call.pszBase = (ULONG_PTR)pszBase;
    call.pszRelative = (ULONG_PTR)pszRelative;
    call.pszCombined = (ULONG_PTR)pszCombined;
    call.pcchCombined = (ULONG_PTR)pcchCombined;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCombineA(struct qemu_syscall *call)
{
    struct qemu_UrlCombineA *c = (struct qemu_UrlCombineA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCombineA(QEMU_G2H(c->pszBase), QEMU_G2H(c->pszRelative), QEMU_G2H(c->pszCombined), QEMU_G2H(c->pcchCombined), c->dwFlags);
}

#endif

struct qemu_UrlCombineW
{
    struct qemu_syscall super;
    uint64_t pszBase;
    uint64_t pszRelative;
    uint64_t pszCombined;
    uint64_t pcchCombined;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlCombineW(LPCWSTR pszBase, LPCWSTR pszRelative, LPWSTR pszCombined, LPDWORD pcchCombined, DWORD dwFlags)
{
    struct qemu_UrlCombineW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCOMBINEW);
    call.pszBase = (ULONG_PTR)pszBase;
    call.pszRelative = (ULONG_PTR)pszRelative;
    call.pszCombined = (ULONG_PTR)pszCombined;
    call.pcchCombined = (ULONG_PTR)pcchCombined;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCombineW(struct qemu_syscall *call)
{
    struct qemu_UrlCombineW *c = (struct qemu_UrlCombineW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCombineW(QEMU_G2H(c->pszBase), QEMU_G2H(c->pszRelative), QEMU_G2H(c->pszCombined), QEMU_G2H(c->pcchCombined), c->dwFlags);
}

#endif

struct qemu_UrlEscapeA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszEscaped;
    uint64_t pcchEscaped;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlEscapeA(LPCSTR pszUrl, LPSTR pszEscaped, LPDWORD pcchEscaped, DWORD dwFlags)
{
    struct qemu_UrlEscapeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLESCAPEA);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pszEscaped = (ULONG_PTR)pszEscaped;
    call.pcchEscaped = (ULONG_PTR)pcchEscaped;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlEscapeA(struct qemu_syscall *call)
{
    struct qemu_UrlEscapeA *c = (struct qemu_UrlEscapeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlEscapeA(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszEscaped), QEMU_G2H(c->pcchEscaped), c->dwFlags);
}

#endif

struct qemu_UrlEscapeW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszEscaped;
    uint64_t pcchEscaped;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlEscapeW(LPCWSTR pszUrl, LPWSTR pszEscaped, LPDWORD pcchEscaped, DWORD dwFlags)
{
    struct qemu_UrlEscapeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLESCAPEW);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pszEscaped = (ULONG_PTR)pszEscaped;
    call.pcchEscaped = (ULONG_PTR)pcchEscaped;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlEscapeW(struct qemu_syscall *call)
{
    struct qemu_UrlEscapeW *c = (struct qemu_UrlEscapeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlEscapeW(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszEscaped), QEMU_G2H(c->pcchEscaped), c->dwFlags);
}

#endif

struct qemu_UrlUnescapeA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszUnescaped;
    uint64_t pcchUnescaped;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlUnescapeA(LPSTR pszUrl, LPSTR pszUnescaped, LPDWORD pcchUnescaped, DWORD dwFlags)
{
    struct qemu_UrlUnescapeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLUNESCAPEA);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pszUnescaped = (ULONG_PTR)pszUnescaped;
    call.pcchUnescaped = (ULONG_PTR)pcchUnescaped;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlUnescapeA(struct qemu_syscall *call)
{
    struct qemu_UrlUnescapeA *c = (struct qemu_UrlUnescapeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlUnescapeA(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszUnescaped), QEMU_G2H(c->pcchUnescaped), c->dwFlags);
}

#endif

struct qemu_UrlUnescapeW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t pszUnescaped;
    uint64_t pcchUnescaped;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlUnescapeW(LPWSTR pszUrl, LPWSTR pszUnescaped, LPDWORD pcchUnescaped, DWORD dwFlags)
{
    struct qemu_UrlUnescapeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLUNESCAPEW);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pszUnescaped = (ULONG_PTR)pszUnescaped;
    call.pcchUnescaped = (ULONG_PTR)pcchUnescaped;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlUnescapeW(struct qemu_syscall *call)
{
    struct qemu_UrlUnescapeW *c = (struct qemu_UrlUnescapeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlUnescapeW(QEMU_G2H(c->pszUrl), QEMU_G2H(c->pszUnescaped), QEMU_G2H(c->pcchUnescaped), c->dwFlags);
}

#endif

struct qemu_UrlGetLocationA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPCSTR WINAPI UrlGetLocationA(LPCSTR pszUrl)
{
    struct qemu_UrlGetLocationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLGETLOCATIONA);
    call.pszUrl = (ULONG_PTR)pszUrl;

    qemu_syscall(&call.super);

    return (LPCSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_UrlGetLocationA(struct qemu_syscall *call)
{
    struct qemu_UrlGetLocationA *c = (struct qemu_UrlGetLocationA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)UrlGetLocationA(QEMU_G2H(c->pszUrl));
}

#endif

struct qemu_UrlGetLocationW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPCWSTR WINAPI UrlGetLocationW(LPCWSTR pszUrl)
{
    struct qemu_UrlGetLocationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLGETLOCATIONW);
    call.pszUrl = (ULONG_PTR)pszUrl;

    qemu_syscall(&call.super);

    return (LPCWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_UrlGetLocationW(struct qemu_syscall *call)
{
    struct qemu_UrlGetLocationW *c = (struct qemu_UrlGetLocationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)UrlGetLocationW(QEMU_G2H(c->pszUrl));
}

#endif

struct qemu_UrlCompareA
{
    struct qemu_syscall super;
    uint64_t pszUrl1;
    uint64_t pszUrl2;
    uint64_t fIgnoreSlash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI UrlCompareA(LPCSTR pszUrl1, LPCSTR pszUrl2, BOOL fIgnoreSlash)
{
    struct qemu_UrlCompareA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCOMPAREA);
    call.pszUrl1 = (ULONG_PTR)pszUrl1;
    call.pszUrl2 = (ULONG_PTR)pszUrl2;
    call.fIgnoreSlash = (ULONG_PTR)fIgnoreSlash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCompareA(struct qemu_syscall *call)
{
    struct qemu_UrlCompareA *c = (struct qemu_UrlCompareA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCompareA(QEMU_G2H(c->pszUrl1), QEMU_G2H(c->pszUrl2), c->fIgnoreSlash);
}

#endif

struct qemu_UrlCompareW
{
    struct qemu_syscall super;
    uint64_t pszUrl1;
    uint64_t pszUrl2;
    uint64_t fIgnoreSlash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI UrlCompareW(LPCWSTR pszUrl1, LPCWSTR pszUrl2, BOOL fIgnoreSlash)
{
    struct qemu_UrlCompareW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCOMPAREW);
    call.pszUrl1 = (ULONG_PTR)pszUrl1;
    call.pszUrl2 = (ULONG_PTR)pszUrl2;
    call.fIgnoreSlash = (ULONG_PTR)fIgnoreSlash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCompareW(struct qemu_syscall *call)
{
    struct qemu_UrlCompareW *c = (struct qemu_UrlCompareW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCompareW(QEMU_G2H(c->pszUrl1), QEMU_G2H(c->pszUrl2), c->fIgnoreSlash);
}

#endif

struct qemu_HashData
{
    struct qemu_syscall super;
    uint64_t lpSrc;
    uint64_t nSrcLen;
    uint64_t lpDest;
    uint64_t nDestLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI HashData(unsigned char *lpSrc, DWORD nSrcLen, unsigned char *lpDest, DWORD nDestLen)
{
    struct qemu_HashData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HASHDATA);
    call.lpSrc = (ULONG_PTR)lpSrc;
    call.nSrcLen = (ULONG_PTR)nSrcLen;
    call.lpDest = (ULONG_PTR)lpDest;
    call.nDestLen = (ULONG_PTR)nDestLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HashData(struct qemu_syscall *call)
{
    struct qemu_HashData *c = (struct qemu_HashData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HashData(QEMU_G2H(c->lpSrc), c->nSrcLen, QEMU_G2H(c->lpDest), c->nDestLen);
}

#endif

struct qemu_UrlHashA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t lpDest;
    uint64_t nDestLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlHashA(LPCSTR pszUrl, unsigned char *lpDest, DWORD nDestLen)
{
    struct qemu_UrlHashA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLHASHA);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.lpDest = (ULONG_PTR)lpDest;
    call.nDestLen = (ULONG_PTR)nDestLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlHashA(struct qemu_syscall *call)
{
    struct qemu_UrlHashA *c = (struct qemu_UrlHashA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlHashA(QEMU_G2H(c->pszUrl), QEMU_G2H(c->lpDest), c->nDestLen);
}

#endif

struct qemu_UrlHashW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t lpDest;
    uint64_t nDestLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlHashW(LPCWSTR pszUrl, unsigned char *lpDest, DWORD nDestLen)
{
    struct qemu_UrlHashW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLHASHW);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.lpDest = (ULONG_PTR)lpDest;
    call.nDestLen = (ULONG_PTR)nDestLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlHashW(struct qemu_syscall *call)
{
    struct qemu_UrlHashW *c = (struct qemu_UrlHashW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlHashW(QEMU_G2H(c->pszUrl), QEMU_G2H(c->lpDest), c->nDestLen);
}

#endif

struct qemu_UrlApplySchemeA
{
    struct qemu_syscall super;
    uint64_t pszIn;
    uint64_t pszOut;
    uint64_t pcchOut;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlApplySchemeA(LPCSTR pszIn, LPSTR pszOut, LPDWORD pcchOut, DWORD dwFlags)
{
    struct qemu_UrlApplySchemeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLAPPLYSCHEMEA);
    call.pszIn = (ULONG_PTR)pszIn;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlApplySchemeA(struct qemu_syscall *call)
{
    struct qemu_UrlApplySchemeA *c = (struct qemu_UrlApplySchemeA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlApplySchemeA(QEMU_G2H(c->pszIn), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut), c->dwFlags);
}

#endif

struct qemu_UrlApplySchemeW
{
    struct qemu_syscall super;
    uint64_t pszIn;
    uint64_t pszOut;
    uint64_t pcchOut;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlApplySchemeW(LPCWSTR pszIn, LPWSTR pszOut, LPDWORD pcchOut, DWORD dwFlags)
{
    struct qemu_UrlApplySchemeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLAPPLYSCHEMEW);
    call.pszIn = (ULONG_PTR)pszIn;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlApplySchemeW(struct qemu_syscall *call)
{
    struct qemu_UrlApplySchemeW *c = (struct qemu_UrlApplySchemeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlApplySchemeW(QEMU_G2H(c->pszIn), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut), c->dwFlags);
}

#endif

struct qemu_UrlIsA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t Urlis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UrlIsA(LPCSTR pszUrl, URLIS Urlis)
{
    struct qemu_UrlIsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLISA);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.Urlis = (ULONG_PTR)Urlis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlIsA(struct qemu_syscall *call)
{
    struct qemu_UrlIsA *c = (struct qemu_UrlIsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlIsA(QEMU_G2H(c->pszUrl), c->Urlis);
}

#endif

struct qemu_UrlIsW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
    uint64_t Urlis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UrlIsW(LPCWSTR pszUrl, URLIS Urlis)
{
    struct qemu_UrlIsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLISW);
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.Urlis = (ULONG_PTR)Urlis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlIsW(struct qemu_syscall *call)
{
    struct qemu_UrlIsW *c = (struct qemu_UrlIsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlIsW(QEMU_G2H(c->pszUrl), c->Urlis);
}

#endif

struct qemu_UrlIsNoHistoryA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UrlIsNoHistoryA(LPCSTR pszUrl)
{
    struct qemu_UrlIsNoHistoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLISNOHISTORYA);
    call.pszUrl = (ULONG_PTR)pszUrl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlIsNoHistoryA(struct qemu_syscall *call)
{
    struct qemu_UrlIsNoHistoryA *c = (struct qemu_UrlIsNoHistoryA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlIsNoHistoryA(QEMU_G2H(c->pszUrl));
}

#endif

struct qemu_UrlIsNoHistoryW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UrlIsNoHistoryW(LPCWSTR pszUrl)
{
    struct qemu_UrlIsNoHistoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLISNOHISTORYW);
    call.pszUrl = (ULONG_PTR)pszUrl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlIsNoHistoryW(struct qemu_syscall *call)
{
    struct qemu_UrlIsNoHistoryW *c = (struct qemu_UrlIsNoHistoryW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlIsNoHistoryW(QEMU_G2H(c->pszUrl));
}

#endif

struct qemu_UrlIsOpaqueA
{
    struct qemu_syscall super;
    uint64_t pszUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UrlIsOpaqueA(LPCSTR pszUrl)
{
    struct qemu_UrlIsOpaqueA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLISOPAQUEA);
    call.pszUrl = (ULONG_PTR)pszUrl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlIsOpaqueA(struct qemu_syscall *call)
{
    struct qemu_UrlIsOpaqueA *c = (struct qemu_UrlIsOpaqueA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlIsOpaqueA(QEMU_G2H(c->pszUrl));
}

#endif

struct qemu_UrlIsOpaqueW
{
    struct qemu_syscall super;
    uint64_t pszUrl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UrlIsOpaqueW(LPCWSTR pszUrl)
{
    struct qemu_UrlIsOpaqueW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLISOPAQUEW);
    call.pszUrl = (ULONG_PTR)pszUrl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlIsOpaqueW(struct qemu_syscall *call)
{
    struct qemu_UrlIsOpaqueW *c = (struct qemu_UrlIsOpaqueW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlIsOpaqueW(QEMU_G2H(c->pszUrl));
}

#endif

struct qemu_UrlGetPartA
{
    struct qemu_syscall super;
    uint64_t pszIn;
    uint64_t pszOut;
    uint64_t pcchOut;
    uint64_t dwPart;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlGetPartA(LPCSTR pszIn, LPSTR pszOut, LPDWORD pcchOut, DWORD dwPart, DWORD dwFlags)
{
    struct qemu_UrlGetPartA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLGETPARTA);
    call.pszIn = (ULONG_PTR)pszIn;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;
    call.dwPart = (ULONG_PTR)dwPart;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlGetPartA(struct qemu_syscall *call)
{
    struct qemu_UrlGetPartA *c = (struct qemu_UrlGetPartA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlGetPartA(QEMU_G2H(c->pszIn), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut), c->dwPart, c->dwFlags);
}

#endif

struct qemu_UrlGetPartW
{
    struct qemu_syscall super;
    uint64_t pszIn;
    uint64_t pszOut;
    uint64_t pcchOut;
    uint64_t dwPart;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlGetPartW(LPCWSTR pszIn, LPWSTR pszOut, LPDWORD pcchOut, DWORD dwPart, DWORD dwFlags)
{
    struct qemu_UrlGetPartW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLGETPARTW);
    call.pszIn = (ULONG_PTR)pszIn;
    call.pszOut = (ULONG_PTR)pszOut;
    call.pcchOut = (ULONG_PTR)pcchOut;
    call.dwPart = (ULONG_PTR)dwPart;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlGetPartW(struct qemu_syscall *call)
{
    struct qemu_UrlGetPartW *c = (struct qemu_UrlGetPartW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlGetPartW(QEMU_G2H(c->pszIn), QEMU_G2H(c->pszOut), QEMU_G2H(c->pcchOut), c->dwPart, c->dwFlags);
}

#endif

struct qemu_PathIsURLA
{
    struct qemu_syscall super;
    uint64_t lpstrPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsURLA(LPCSTR lpstrPath)
{
    struct qemu_PathIsURLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISURLA);
    call.lpstrPath = (ULONG_PTR)lpstrPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsURLA(struct qemu_syscall *call)
{
    struct qemu_PathIsURLA *c = (struct qemu_PathIsURLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsURLA(QEMU_G2H(c->lpstrPath));
}

#endif

struct qemu_PathIsURLW
{
    struct qemu_syscall super;
    uint64_t lpstrPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PathIsURLW(LPCWSTR lpstrPath)
{
    struct qemu_PathIsURLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PATHISURLW);
    call.lpstrPath = (ULONG_PTR)lpstrPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PathIsURLW(struct qemu_syscall *call)
{
    struct qemu_PathIsURLW *c = (struct qemu_PathIsURLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PathIsURLW(QEMU_G2H(c->lpstrPath));
}

#endif

struct qemu_UrlCreateFromPathA
{
    struct qemu_syscall super;
    uint64_t pszPath;
    uint64_t pszUrl;
    uint64_t pcchUrl;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlCreateFromPathA(LPCSTR pszPath, LPSTR pszUrl, LPDWORD pcchUrl, DWORD dwReserved)
{
    struct qemu_UrlCreateFromPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCREATEFROMPATHA);
    call.pszPath = (ULONG_PTR)pszPath;
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pcchUrl = (ULONG_PTR)pcchUrl;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCreateFromPathA(struct qemu_syscall *call)
{
    struct qemu_UrlCreateFromPathA *c = (struct qemu_UrlCreateFromPathA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCreateFromPathA(QEMU_G2H(c->pszPath), QEMU_G2H(c->pszUrl), QEMU_G2H(c->pcchUrl), c->dwReserved);
}

#endif

struct qemu_UrlCreateFromPathW
{
    struct qemu_syscall super;
    uint64_t pszPath;
    uint64_t pszUrl;
    uint64_t pcchUrl;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlCreateFromPathW(LPCWSTR pszPath, LPWSTR pszUrl, LPDWORD pcchUrl, DWORD dwReserved)
{
    struct qemu_UrlCreateFromPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLCREATEFROMPATHW);
    call.pszPath = (ULONG_PTR)pszPath;
    call.pszUrl = (ULONG_PTR)pszUrl;
    call.pcchUrl = (ULONG_PTR)pcchUrl;
    call.dwReserved = (ULONG_PTR)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UrlCreateFromPathW(struct qemu_syscall *call)
{
    struct qemu_UrlCreateFromPathW *c = (struct qemu_UrlCreateFromPathW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlCreateFromPathW(QEMU_G2H(c->pszPath), QEMU_G2H(c->pszUrl), QEMU_G2H(c->pcchUrl), c->dwReserved);
}

#endif

struct qemu_SHAutoComplete
{
    struct qemu_syscall super;
    uint64_t hwndEdit;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHAutoComplete(HWND hwndEdit, DWORD dwFlags)
{
    struct qemu_SHAutoComplete call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHAUTOCOMPLETE);
    call.hwndEdit = (ULONG_PTR)hwndEdit;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHAutoComplete(struct qemu_syscall *call)
{
    struct qemu_SHAutoComplete *c = (struct qemu_SHAutoComplete *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHAutoComplete(QEMU_G2H(c->hwndEdit), c->dwFlags);
}

#endif

struct qemu_MLBuildResURLA
{
    struct qemu_syscall super;
    uint64_t lpszLibName;
    uint64_t hMod;
    uint64_t dwFlags;
    uint64_t lpszRes;
    uint64_t lpszDest;
    uint64_t dwDestLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI MLBuildResURLA(LPCSTR lpszLibName, HMODULE hMod, DWORD dwFlags, LPCSTR lpszRes, LPSTR lpszDest, DWORD dwDestLen)
{
    struct qemu_MLBuildResURLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MLBUILDRESURLA);
    call.lpszLibName = (ULONG_PTR)lpszLibName;
    call.hMod = (ULONG_PTR)hMod;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpszRes = (ULONG_PTR)lpszRes;
    call.lpszDest = (ULONG_PTR)lpszDest;
    call.dwDestLen = (ULONG_PTR)dwDestLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add MLBuildResURLA to Wine headers? */
extern HRESULT WINAPI MLBuildResURLA(LPCSTR lpszLibName, HMODULE hMod, DWORD dwFlags, LPCSTR lpszRes, LPSTR lpszDest, DWORD dwDestLen);
void qemu_MLBuildResURLA(struct qemu_syscall *call)
{
    struct qemu_MLBuildResURLA *c = (struct qemu_MLBuildResURLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MLBuildResURLA(QEMU_G2H(c->lpszLibName), QEMU_G2H(c->hMod), c->dwFlags, QEMU_G2H(c->lpszRes), QEMU_G2H(c->lpszDest), c->dwDestLen);
}

#endif

struct qemu_MLBuildResURLW
{
    struct qemu_syscall super;
    uint64_t lpszLibName;
    uint64_t hMod;
    uint64_t dwFlags;
    uint64_t lpszRes;
    uint64_t lpszDest;
    uint64_t dwDestLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI MLBuildResURLW(LPCWSTR lpszLibName, HMODULE hMod, DWORD dwFlags, LPCWSTR lpszRes, LPWSTR lpszDest, DWORD dwDestLen)
{
    struct qemu_MLBuildResURLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MLBUILDRESURLW);
    call.lpszLibName = (ULONG_PTR)lpszLibName;
    call.hMod = (ULONG_PTR)hMod;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpszRes = (ULONG_PTR)lpszRes;
    call.lpszDest = (ULONG_PTR)lpszDest;
    call.dwDestLen = (ULONG_PTR)dwDestLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add MLBuildResURLW to Wine headers? */
extern HRESULT WINAPI MLBuildResURLW(LPCWSTR lpszLibName, HMODULE hMod, DWORD dwFlags, LPCWSTR lpszRes, LPWSTR lpszDest, DWORD dwDestLen);
void qemu_MLBuildResURLW(struct qemu_syscall *call)
{
    struct qemu_MLBuildResURLW *c = (struct qemu_MLBuildResURLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MLBuildResURLW(QEMU_G2H(c->lpszLibName), QEMU_G2H(c->hMod), c->dwFlags, QEMU_G2H(c->lpszRes), QEMU_G2H(c->lpszDest), c->dwDestLen);
}

#endif

struct qemu_UrlFixupW
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t translatedUrl;
    uint64_t maxChars;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UrlFixupW(LPCWSTR url, LPWSTR translatedUrl, DWORD maxChars)
{
    struct qemu_UrlFixupW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_URLFIXUPW);
    call.url = (ULONG_PTR)url;
    call.translatedUrl = (ULONG_PTR)translatedUrl;
    call.maxChars = (ULONG_PTR)maxChars;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add UrlFixupW to Wine headers? */
extern HRESULT WINAPI UrlFixupW(LPCWSTR url, LPWSTR translatedUrl, DWORD maxChars);
void qemu_UrlFixupW(struct qemu_syscall *call)
{
    struct qemu_UrlFixupW *c = (struct qemu_UrlFixupW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UrlFixupW(QEMU_G2H(c->url), QEMU_G2H(c->translatedUrl), c->maxChars);
}

#endif

struct qemu_IsInternetESCEnabled
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsInternetESCEnabled(void)
{
    struct qemu_IsInternetESCEnabled call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISINTERNETESCENABLED);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsInternetESCEnabled(struct qemu_syscall *call)
{
    struct qemu_IsInternetESCEnabled *c = (struct qemu_IsInternetESCEnabled *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsInternetESCEnabled();
}

#endif

