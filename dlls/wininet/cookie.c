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
#include <wininet.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wininet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wininet);
#endif


struct qemu_InternetGetCookieExW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpszCookieName;
    uint64_t lpCookieData;
    uint64_t lpdwSize;
    uint64_t flags;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetCookieExW(LPCWSTR lpszUrl, LPCWSTR lpszCookieName, LPWSTR lpCookieData, LPDWORD lpdwSize, DWORD flags, void *reserved)
{
    struct qemu_InternetGetCookieExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCOOKIEEXW);
    call.lpszUrl = (uint64_t)lpszUrl;
    call.lpszCookieName = (uint64_t)lpszCookieName;
    call.lpCookieData = (uint64_t)lpCookieData;
    call.lpdwSize = (uint64_t)lpdwSize;
    call.flags = (uint64_t)flags;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetCookieExW(struct qemu_syscall *call)
{
    struct qemu_InternetGetCookieExW *c = (struct qemu_InternetGetCookieExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetCookieExW(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszCookieName), QEMU_G2H(c->lpCookieData), QEMU_G2H(c->lpdwSize), c->flags, QEMU_G2H(c->reserved));
}

#endif

struct qemu_InternetGetCookieW
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t name;
    uint64_t data;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetCookieW(const WCHAR *url, const WCHAR *name, WCHAR *data, DWORD *size)
{
    struct qemu_InternetGetCookieW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCOOKIEW);
    call.url = (uint64_t)url;
    call.name = (uint64_t)name;
    call.data = (uint64_t)data;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetCookieW(struct qemu_syscall *call)
{
    struct qemu_InternetGetCookieW *c = (struct qemu_InternetGetCookieW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetCookieW(QEMU_G2H(c->url), QEMU_G2H(c->name), QEMU_G2H(c->data), QEMU_G2H(c->size));
}

#endif

struct qemu_InternetGetCookieExA
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpszCookieName;
    uint64_t lpCookieData;
    uint64_t lpdwSize;
    uint64_t flags;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetCookieExA(LPCSTR lpszUrl, LPCSTR lpszCookieName, LPSTR lpCookieData, LPDWORD lpdwSize, DWORD flags, void *reserved)
{
    struct qemu_InternetGetCookieExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCOOKIEEXA);
    call.lpszUrl = (uint64_t)lpszUrl;
    call.lpszCookieName = (uint64_t)lpszCookieName;
    call.lpCookieData = (uint64_t)lpCookieData;
    call.lpdwSize = (uint64_t)lpdwSize;
    call.flags = (uint64_t)flags;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetCookieExA(struct qemu_syscall *call)
{
    struct qemu_InternetGetCookieExA *c = (struct qemu_InternetGetCookieExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetCookieExA(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszCookieName), QEMU_G2H(c->lpCookieData), QEMU_G2H(c->lpdwSize), c->flags, QEMU_G2H(c->reserved));
}

#endif

struct qemu_InternetGetCookieA
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t name;
    uint64_t data;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetCookieA(const char *url, const char *name, char *data, DWORD *size)
{
    struct qemu_InternetGetCookieA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETCOOKIEA);
    call.url = (uint64_t)url;
    call.name = (uint64_t)name;
    call.data = (uint64_t)data;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetCookieA(struct qemu_syscall *call)
{
    struct qemu_InternetGetCookieA *c = (struct qemu_InternetGetCookieA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetCookieA(QEMU_G2H(c->url), QEMU_G2H(c->name), QEMU_G2H(c->data), QEMU_G2H(c->size));
}

#endif

struct qemu_IsDomainLegalCookieDomainW
{
    struct qemu_syscall super;
    uint64_t domain;
    uint64_t full_domain;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsDomainLegalCookieDomainW(const WCHAR *domain, const WCHAR *full_domain)
{
    struct qemu_IsDomainLegalCookieDomainW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDOMAINLEGALCOOKIEDOMAINW);
    call.domain = (uint64_t)domain;
    call.full_domain = (uint64_t)full_domain;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsDomainLegalCookieDomainW to Wine headers? */
extern BOOL WINAPI IsDomainLegalCookieDomainW(const WCHAR *domain, const WCHAR *full_domain);
void qemu_IsDomainLegalCookieDomainW(struct qemu_syscall *call)
{
    struct qemu_IsDomainLegalCookieDomainW *c = (struct qemu_IsDomainLegalCookieDomainW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsDomainLegalCookieDomainW(QEMU_G2H(c->domain), QEMU_G2H(c->full_domain));
}

#endif

struct qemu_InternetSetCookieExW
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpszCookieName;
    uint64_t lpCookieData;
    uint64_t flags;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetSetCookieExW(LPCWSTR lpszUrl, LPCWSTR lpszCookieName, LPCWSTR lpCookieData, DWORD flags, DWORD_PTR reserved)
{
    struct qemu_InternetSetCookieExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETCOOKIEEXW);
    call.lpszUrl = (uint64_t)lpszUrl;
    call.lpszCookieName = (uint64_t)lpszCookieName;
    call.lpCookieData = (uint64_t)lpCookieData;
    call.flags = (uint64_t)flags;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetCookieExW(struct qemu_syscall *call)
{
    struct qemu_InternetSetCookieExW *c = (struct qemu_InternetSetCookieExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetCookieExW(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszCookieName), QEMU_G2H(c->lpCookieData), c->flags, c->reserved);
}

#endif

struct qemu_InternetSetCookieW
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t name;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetCookieW(const WCHAR *url, const WCHAR *name, const WCHAR *data)
{
    struct qemu_InternetSetCookieW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETCOOKIEW);
    call.url = (uint64_t)url;
    call.name = (uint64_t)name;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetCookieW(struct qemu_syscall *call)
{
    struct qemu_InternetSetCookieW *c = (struct qemu_InternetSetCookieW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetCookieW(QEMU_G2H(c->url), QEMU_G2H(c->name), QEMU_G2H(c->data));
}

#endif

struct qemu_InternetSetCookieA
{
    struct qemu_syscall super;
    uint64_t lpszUrl;
    uint64_t lpszCookieName;
    uint64_t lpCookieData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetCookieA(LPCSTR lpszUrl, LPCSTR lpszCookieName, LPCSTR lpCookieData)
{
    struct qemu_InternetSetCookieA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETCOOKIEA);
    call.lpszUrl = (uint64_t)lpszUrl;
    call.lpszCookieName = (uint64_t)lpszCookieName;
    call.lpCookieData = (uint64_t)lpCookieData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetCookieA(struct qemu_syscall *call)
{
    struct qemu_InternetSetCookieA *c = (struct qemu_InternetSetCookieA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetCookieA(QEMU_G2H(c->lpszUrl), QEMU_G2H(c->lpszCookieName), QEMU_G2H(c->lpCookieData));
}

#endif

struct qemu_InternetSetCookieExA
{
    struct qemu_syscall super;
    uint64_t lpszURL;
    uint64_t lpszCookieName;
    uint64_t lpszCookieData;
    uint64_t dwFlags;
    uint64_t dwReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetSetCookieExA(LPCSTR lpszURL, LPCSTR lpszCookieName, LPCSTR lpszCookieData, DWORD dwFlags, DWORD_PTR dwReserved)
{
    struct qemu_InternetSetCookieExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETCOOKIEEXA);
    call.lpszURL = (uint64_t)lpszURL;
    call.lpszCookieName = (uint64_t)lpszCookieName;
    call.lpszCookieData = (uint64_t)lpszCookieData;
    call.dwFlags = (uint64_t)dwFlags;
    call.dwReserved = (uint64_t)dwReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetCookieExA(struct qemu_syscall *call)
{
    struct qemu_InternetSetCookieExA *c = (struct qemu_InternetSetCookieExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetCookieExA(QEMU_G2H(c->lpszURL), QEMU_G2H(c->lpszCookieName), QEMU_G2H(c->lpszCookieData), c->dwFlags, c->dwReserved);
}

#endif

struct qemu_InternetClearAllPerSiteCookieDecisions
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetClearAllPerSiteCookieDecisions(VOID)
{
    struct qemu_InternetClearAllPerSiteCookieDecisions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETCLEARALLPERSITECOOKIEDECISIONS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetClearAllPerSiteCookieDecisions(struct qemu_syscall *call)
{
    struct qemu_InternetClearAllPerSiteCookieDecisions *c = (struct qemu_InternetClearAllPerSiteCookieDecisions *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetClearAllPerSiteCookieDecisions();
}

#endif

struct qemu_InternetEnumPerSiteCookieDecisionA
{
    struct qemu_syscall super;
    uint64_t pszSiteName;
    uint64_t pcSiteNameSize;
    uint64_t pdwDecision;
    uint64_t dwIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetEnumPerSiteCookieDecisionA(LPSTR pszSiteName, ULONG *pcSiteNameSize, ULONG *pdwDecision, ULONG dwIndex)
{
    struct qemu_InternetEnumPerSiteCookieDecisionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETENUMPERSITECOOKIEDECISIONA);
    call.pszSiteName = (uint64_t)pszSiteName;
    call.pcSiteNameSize = (uint64_t)pcSiteNameSize;
    call.pdwDecision = (uint64_t)pdwDecision;
    call.dwIndex = (uint64_t)dwIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetEnumPerSiteCookieDecisionA(struct qemu_syscall *call)
{
    struct qemu_InternetEnumPerSiteCookieDecisionA *c = (struct qemu_InternetEnumPerSiteCookieDecisionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetEnumPerSiteCookieDecisionA(QEMU_G2H(c->pszSiteName), QEMU_G2H(c->pcSiteNameSize), QEMU_G2H(c->pdwDecision), c->dwIndex);
}

#endif

struct qemu_InternetEnumPerSiteCookieDecisionW
{
    struct qemu_syscall super;
    uint64_t pszSiteName;
    uint64_t pcSiteNameSize;
    uint64_t pdwDecision;
    uint64_t dwIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetEnumPerSiteCookieDecisionW(LPWSTR pszSiteName, ULONG *pcSiteNameSize, ULONG *pdwDecision, ULONG dwIndex)
{
    struct qemu_InternetEnumPerSiteCookieDecisionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETENUMPERSITECOOKIEDECISIONW);
    call.pszSiteName = (uint64_t)pszSiteName;
    call.pcSiteNameSize = (uint64_t)pcSiteNameSize;
    call.pdwDecision = (uint64_t)pdwDecision;
    call.dwIndex = (uint64_t)dwIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetEnumPerSiteCookieDecisionW(struct qemu_syscall *call)
{
    struct qemu_InternetEnumPerSiteCookieDecisionW *c = (struct qemu_InternetEnumPerSiteCookieDecisionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetEnumPerSiteCookieDecisionW(QEMU_G2H(c->pszSiteName), QEMU_G2H(c->pcSiteNameSize), QEMU_G2H(c->pdwDecision), c->dwIndex);
}

#endif

struct qemu_InternetGetPerSiteCookieDecisionA
{
    struct qemu_syscall super;
    uint64_t pwchHostName;
    uint64_t pResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetPerSiteCookieDecisionA(LPCSTR pwchHostName, ULONG *pResult)
{
    struct qemu_InternetGetPerSiteCookieDecisionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETPERSITECOOKIEDECISIONA);
    call.pwchHostName = (uint64_t)pwchHostName;
    call.pResult = (uint64_t)pResult;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetPerSiteCookieDecisionA(struct qemu_syscall *call)
{
    struct qemu_InternetGetPerSiteCookieDecisionA *c = (struct qemu_InternetGetPerSiteCookieDecisionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetPerSiteCookieDecisionA(QEMU_G2H(c->pwchHostName), QEMU_G2H(c->pResult));
}

#endif

struct qemu_InternetGetPerSiteCookieDecisionW
{
    struct qemu_syscall super;
    uint64_t pwchHostName;
    uint64_t pResult;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetGetPerSiteCookieDecisionW(LPCWSTR pwchHostName, ULONG *pResult)
{
    struct qemu_InternetGetPerSiteCookieDecisionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETGETPERSITECOOKIEDECISIONW);
    call.pwchHostName = (uint64_t)pwchHostName;
    call.pResult = (uint64_t)pResult;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetGetPerSiteCookieDecisionW(struct qemu_syscall *call)
{
    struct qemu_InternetGetPerSiteCookieDecisionW *c = (struct qemu_InternetGetPerSiteCookieDecisionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetGetPerSiteCookieDecisionW(QEMU_G2H(c->pwchHostName), QEMU_G2H(c->pResult));
}

#endif

struct qemu_InternetSetPerSiteCookieDecisionA
{
    struct qemu_syscall super;
    uint64_t pchHostName;
    uint64_t dwDecision;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetPerSiteCookieDecisionA(LPCSTR pchHostName, DWORD dwDecision)
{
    struct qemu_InternetSetPerSiteCookieDecisionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETPERSITECOOKIEDECISIONA);
    call.pchHostName = (uint64_t)pchHostName;
    call.dwDecision = (uint64_t)dwDecision;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetPerSiteCookieDecisionA(struct qemu_syscall *call)
{
    struct qemu_InternetSetPerSiteCookieDecisionA *c = (struct qemu_InternetSetPerSiteCookieDecisionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetPerSiteCookieDecisionA(QEMU_G2H(c->pchHostName), c->dwDecision);
}

#endif

struct qemu_InternetSetPerSiteCookieDecisionW
{
    struct qemu_syscall super;
    uint64_t pchHostName;
    uint64_t dwDecision;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetSetPerSiteCookieDecisionW(LPCWSTR pchHostName, DWORD dwDecision)
{
    struct qemu_InternetSetPerSiteCookieDecisionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSETPERSITECOOKIEDECISIONW);
    call.pchHostName = (uint64_t)pchHostName;
    call.dwDecision = (uint64_t)dwDecision;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetSetPerSiteCookieDecisionW(struct qemu_syscall *call)
{
    struct qemu_InternetSetPerSiteCookieDecisionW *c = (struct qemu_InternetSetPerSiteCookieDecisionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetSetPerSiteCookieDecisionW(QEMU_G2H(c->pchHostName), c->dwDecision);
}

#endif

