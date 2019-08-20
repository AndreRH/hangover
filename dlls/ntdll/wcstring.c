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
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu__wcsicmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL__wcsicmp(LPCWSTR str1, LPCWSTR str2)
{
    struct qemu__wcsicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSICMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsicmp(struct qemu_syscall *call)
{
    struct qemu__wcsicmp *c = (struct qemu__wcsicmp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsicmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu__wcslwr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL__wcslwr(LPWSTR str)
{
    struct qemu__wcslwr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSLWR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcslwr(struct qemu_syscall *call)
{
    struct qemu__wcslwr *c = (struct qemu__wcslwr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__wcslwr(QEMU_G2H(c->str));
}

#endif

struct qemu__wcsnicmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL__wcsnicmp(LPCWSTR str1, LPCWSTR str2, INT n)
{
    struct qemu__wcsnicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNICMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.n = n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsnicmp(struct qemu_syscall *call)
{
    struct qemu__wcsnicmp *c = (struct qemu__wcsnicmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p__wcsnicmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->n);
}

#endif

struct qemu__wcsupr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL__wcsupr(LPWSTR str)
{
    struct qemu__wcsupr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSUPR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcsupr(struct qemu_syscall *call)
{
    struct qemu__wcsupr *c = (struct qemu__wcsupr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__wcsupr(QEMU_G2H(c->str));
}

#endif

struct qemu_towlower
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL NTDLL_towlower(WCHAR ch)
{
    struct qemu_towlower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOWLOWER);
    call.ch = ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_towlower(struct qemu_syscall *call)
{
    struct qemu_towlower *c = (struct qemu_towlower *)call;
    WINE_TRACE("\n");
    c->super.iret = p_towlower(c->ch);
}

#endif

struct qemu_towupper
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR CDECL NTDLL_towupper(WCHAR ch)
{
    struct qemu_towupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOWUPPER);
    call.ch = ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_towupper(struct qemu_syscall *call)
{
    struct qemu_towupper *c = (struct qemu_towupper *)call;
    WINE_TRACE("\n");
    c->super.iret = p_towupper(c->ch);
}

#endif

struct qemu_wcscat
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcscat(LPWSTR dst, LPCWSTR src)
{
    struct qemu_wcscat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCAT);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcscat(struct qemu_syscall *call)
{
    struct qemu_wcscat *c = (struct qemu_wcscat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wcscat(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_wcschr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcschr(LPCWSTR str, WCHAR ch)
{
    struct qemu_wcschr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCHR);
    call.str = (ULONG_PTR)str;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcschr(struct qemu_syscall *call)
{
    struct qemu_wcschr *c = (struct qemu_wcschr *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_wcschr(QEMU_G2H(c->str), c->ch);
}

#endif

struct qemu_wcscmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_wcscmp(LPCWSTR str1, LPCWSTR str2)
{
    struct qemu_wcscmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscmp(struct qemu_syscall *call)
{
    struct qemu_wcscmp *c = (struct qemu_wcscmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcscmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_wcscpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcscpy(LPWSTR dst, LPCWSTR src)
{
    struct qemu_wcscpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcscpy(struct qemu_syscall *call)
{
    struct qemu_wcscpy *c = (struct qemu_wcscpy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wcscpy(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_wcscspn
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t reject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_wcscspn(LPCWSTR str, LPCWSTR reject)
{
    struct qemu_wcscspn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCSPN);
    call.str = (ULONG_PTR)str;
    call.reject = (ULONG_PTR)reject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscspn(struct qemu_syscall *call)
{
    struct qemu_wcscspn *c = (struct qemu_wcscspn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcscspn(QEMU_G2H(c->str), QEMU_G2H(c->reject));
}

#endif

struct qemu_wcslen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_wcslen(LPCWSTR str)
{
    struct qemu_wcslen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSLEN);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcslen(struct qemu_syscall *call)
{
    struct qemu_wcslen *c = (struct qemu_wcslen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcslen(QEMU_G2H(c->str));
}

#endif

struct qemu_wcsncat
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcsncat(LPWSTR s1, LPCWSTR s2, INT n)
{
    struct qemu_wcsncat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCAT);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.n = n;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcsncat(struct qemu_syscall *call)
{
    struct qemu_wcsncat *c = (struct qemu_wcsncat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wcsncat(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->n);
}

#endif

struct qemu_wcsncmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_wcsncmp(LPCWSTR str1, LPCWSTR str2, INT n)
{
    struct qemu_wcsncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.n = n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsncmp(struct qemu_syscall *call)
{
    struct qemu_wcsncmp *c = (struct qemu_wcsncmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcsncmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->n);
}

#endif

struct qemu_wcsncpy
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcsncpy(LPWSTR s1, LPCWSTR s2, INT n)
{
    struct qemu_wcsncpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCPY);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.n = n;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcsncpy(struct qemu_syscall *call)
{
    struct qemu_wcsncpy *c = (struct qemu_wcsncpy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wcsncpy(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->n);
}

#endif

struct qemu_wcspbrk
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t accept;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcspbrk(LPCWSTR str, LPCWSTR accept)
{
    struct qemu_wcspbrk call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSPBRK);
    call.str = (ULONG_PTR)str;
    call.accept = (ULONG_PTR)accept;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcspbrk(struct qemu_syscall *call)
{
    struct qemu_wcspbrk *c = (struct qemu_wcspbrk *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_wcspbrk(QEMU_G2H(c->str), QEMU_G2H(c->accept));
}

#endif

struct qemu_wcsrchr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcsrchr(LPWSTR str, WCHAR ch)
{
    struct qemu_wcsrchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSRCHR);
    call.str = (ULONG_PTR)str;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcsrchr(struct qemu_syscall *call)
{
    struct qemu_wcsrchr *c = (struct qemu_wcsrchr *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_wcsrchr(QEMU_G2H(c->str), c->ch);
}

#endif

struct qemu_wcsspn
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t accept;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_wcsspn(LPCWSTR str, LPCWSTR accept)
{
    struct qemu_wcsspn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSSPN);
    call.str = (ULONG_PTR)str;
    call.accept = (ULONG_PTR)accept;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsspn(struct qemu_syscall *call)
{
    struct qemu_wcsspn *c = (struct qemu_wcsspn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsspn(QEMU_G2H(c->str), QEMU_G2H(c->accept));
}

#endif

struct qemu_wcsstr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t sub;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcsstr(LPCWSTR str, LPCWSTR sub)
{
    struct qemu_wcsstr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSSTR);
    call.str = (ULONG_PTR)str;
    call.sub = (ULONG_PTR)sub;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcsstr(struct qemu_syscall *call)
{
    struct qemu_wcsstr *c = (struct qemu_wcsstr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p_wcsstr(QEMU_G2H(c->str), QEMU_G2H(c->sub));
}

#endif

struct qemu_wcstok
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL NTDLL_wcstok(LPWSTR str, LPCWSTR delim)
{
    struct qemu_wcstok call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOK);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcstok(struct qemu_syscall *call)
{
    struct qemu_wcstok *c = (struct qemu_wcstok *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)p_wcstok(QEMU_G2H(c->str), QEMU_G2H(c->delim));
}

#endif

struct qemu_wcstombs
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_wcstombs(LPSTR dst, LPCWSTR src, INT n)
{
    struct qemu_wcstombs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOMBS);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcstombs(struct qemu_syscall *call)
{
    struct qemu_wcstombs *c = (struct qemu_wcstombs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcstombs(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n);
}

#endif

struct qemu_mbstowcs
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_mbstowcs(LPWSTR dst, LPCSTR src, INT n)
{
    struct qemu_mbstowcs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBSTOWCS);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbstowcs(struct qemu_syscall *call)
{
    struct qemu_mbstowcs *c = (struct qemu_mbstowcs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbstowcs(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n);
}

#endif

struct qemu_wcstol
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t end;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL NTDLL_wcstol(LPCWSTR s, WCHAR **end, INT base)
{
    struct qemu_wcstol call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOL);
    call.s = (ULONG_PTR)s;
    if (end)
        call.end = (ULONG_PTR)*end;
    call.base = base;

    qemu_syscall(&call.super);

    if (end)
        *end = (WCHAR *)(ULONG_PTR)call.end;

    return call.super.iret;
}

#else

void qemu_wcstol(struct qemu_syscall *call)
{
    struct qemu_wcstol *c = (struct qemu_wcstol *)call;
    WCHAR *end;
    WINE_TRACE("\n");

    end = QEMU_G2H(c->end);
    c->super.iret = p_wcstol(QEMU_G2H(c->s), &end, c->base);
    c->end = QEMU_H2G(end);
}

#endif

struct qemu_wcstoul
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t end;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG CDECL NTDLL_wcstoul(LPCWSTR s, LPWSTR *end, INT base)
{
    struct qemu_wcstoul call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOUL);
    call.s = (ULONG_PTR)s;
    call.end = (ULONG_PTR)end;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcstoul(struct qemu_syscall *call)
{
    struct qemu_wcstoul *c = (struct qemu_wcstoul *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcstoul(QEMU_G2H(c->s), QEMU_G2H(c->end), c->base);
}

#endif

struct qemu_iswctype
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t wct;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_iswctype(WCHAR wc, WCHAR wct)
{
    struct qemu_iswctype call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWCTYPE);
    call.wc = wc;
    call.wct = wct;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswctype(struct qemu_syscall *call)
{
    struct qemu_iswctype *c = (struct qemu_iswctype *)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswctype(c->wc, c->wct);
}

#endif

struct qemu_iswalpha
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_iswalpha(WCHAR wc)
{
    struct qemu_iswalpha call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWALPHA);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswalpha(struct qemu_syscall *call)
{
    struct qemu_iswalpha *c = (struct qemu_iswalpha *)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswalpha(c->wc);
}

#endif

struct qemu_iswdigit
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_iswdigit(WCHAR wc)
{
    struct qemu_iswdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWDIGIT);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswdigit(struct qemu_syscall *call)
{
    struct qemu_iswdigit *c = (struct qemu_iswdigit *)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswdigit(c->wc);
}

#endif

struct qemu_iswlower
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_iswlower(WCHAR wc)
{
    struct qemu_iswlower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWLOWER);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswlower(struct qemu_syscall *call)
{
    struct qemu_iswlower *c = (struct qemu_iswlower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswlower(c->wc);
}

#endif

struct qemu_iswspace
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_iswspace(WCHAR wc)
{
    struct qemu_iswspace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWSPACE);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswspace(struct qemu_syscall *call)
{
    struct qemu_iswspace *c = (struct qemu_iswspace *)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswspace(c->wc);
}

#endif

struct qemu_iswxdigit
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL_iswxdigit(WCHAR wc)
{
    struct qemu_iswxdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWXDIGIT);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswxdigit(struct qemu_syscall *call)
{
    struct qemu_iswxdigit *c = (struct qemu_iswxdigit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswxdigit(c->wc);
}

#endif

struct qemu__ultow
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL _ultow(ULONG value, LPWSTR str, INT radix)
{
    struct qemu__ultow call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ULTOW);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.radix = radix;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ultow(struct qemu_syscall *call)
{
    struct qemu__ultow *c = (struct qemu__ultow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__ultow(c->value, QEMU_G2H(c->str), c->radix);
}

#endif

struct qemu__ltow
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL _ltow(LONG value, LPWSTR str, INT radix)
{
    struct qemu__ltow call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LTOW);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.radix = radix;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ltow(struct qemu_syscall *call)
{
    struct qemu__ltow *c = (struct qemu__ltow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__ltow(c->value, QEMU_G2H(c->str), c->radix);
}

#endif

struct qemu__itow
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL _itow(int value, LPWSTR str, INT radix)
{
    struct qemu__itow call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ITOW);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.radix = radix;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__itow(struct qemu_syscall *call)
{
    struct qemu__itow *c = (struct qemu__itow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__itow(c->value, QEMU_G2H(c->str), c->radix);
}

#endif

struct qemu__ui64tow
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL _ui64tow(ULONGLONG value, LPWSTR str, INT radix)
{
    struct qemu__ui64tow call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UI64TOW);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.radix = radix;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ui64tow(struct qemu_syscall *call)
{
    struct qemu__ui64tow *c = (struct qemu__ui64tow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__ui64tow(c->value, QEMU_G2H(c->str), c->radix);
}

#endif

struct qemu__i64tow
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR CDECL _i64tow(LONGLONG value, LPWSTR str, INT radix)
{
    struct qemu__i64tow call;
    call.super.id = QEMU_SYSCALL_ID(CALL__I64TOW);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.radix = radix;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__i64tow(struct qemu_syscall *call)
{
    struct qemu__i64tow *c = (struct qemu__i64tow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)p__i64tow(c->value, QEMU_G2H(c->str), c->radix);
}

#endif

struct qemu__wtol
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL _wtol(LPCWSTR str)
{
    struct qemu__wtol call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOL);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtol(struct qemu_syscall *call)
{
    struct qemu__wtol *c = (struct qemu__wtol *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtol(QEMU_G2H(c->str));
}

#endif

struct qemu__wtoi
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _wtoi(LPCWSTR str)
{
    struct qemu__wtoi call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOI);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtoi(struct qemu_syscall *call)
{
    struct qemu__wtoi *c = (struct qemu__wtoi *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoi(QEMU_G2H(c->str));
}

#endif

struct qemu__wtoi64
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONGLONG CDECL _wtoi64(LPCWSTR str)
{
    struct qemu__wtoi64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOI64);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtoi64(struct qemu_syscall *call)
{
    struct qemu__wtoi64 *c = (struct qemu__wtoi64 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoi64(QEMU_G2H(c->str));
}

#endif
