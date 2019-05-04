/*
 * Copyright 2017 André Hentschel
 * Copyright 2017-2018 Stefan Dösinger for CodeWeavers
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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif


struct qemu__Getdays
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL _Getdays(void)
{
    struct qemu__Getdays call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETDAYS);

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__Getdays(struct qemu_syscall *call)
{
    struct qemu__Getdays *c = (struct qemu__Getdays *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__Getdays());
}

#endif

struct qemu__W_Getdays
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI wchar_t* CDECL _W_Getdays(void)
{
    struct qemu__W_Getdays call;
    call.super.id = QEMU_SYSCALL_ID(CALL__W_GETDAYS);

    qemu_syscall(&call.super);

    return (wchar_t *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__W_Getdays(struct qemu_syscall *call)
{
    struct qemu__W_Getdays *c = (struct qemu__W_Getdays *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__W_Getdays());
}

#endif

struct qemu__Getmonths
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL _Getmonths(void)
{
    struct qemu__Getmonths call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETMONTHS);

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__Getmonths(struct qemu_syscall *call)
{
    struct qemu__Getmonths *c = (struct qemu__Getmonths *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__Getmonths());
}

#endif

struct qemu__W_Getmonths
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI wchar_t* CDECL _W_Getmonths(void)
{
    struct qemu__W_Getmonths call;
    call.super.id = QEMU_SYSCALL_ID(CALL__W_GETMONTHS);

    qemu_syscall(&call.super);

    return (wchar_t *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__W_Getmonths(struct qemu_syscall *call)
{
    struct qemu__W_Getmonths *c = (struct qemu__W_Getmonths *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__W_Getmonths());
}

#endif

struct qemu__Gettnames
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _Gettnames(void)
{
    struct qemu__Gettnames call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETTNAMES);

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__Gettnames(struct qemu_syscall *call)
{
    struct qemu__Gettnames *c = (struct qemu__Gettnames *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__Gettnames());
}

#endif

struct qemu__W_Gettnames
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _W_Gettnames(void)
{
    struct qemu__W_Gettnames call;
    call.super.id = QEMU_SYSCALL_ID(CALL__W_GETTNAMES);

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__W_Gettnames(struct qemu_syscall *call)
{
    struct qemu__W_Gettnames *c = (struct qemu__W_Gettnames *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__W_Gettnames());
}

#endif

struct qemu___crtLCMapStringA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t mapflags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t codepage;
    uint64_t xflag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __crtLCMapStringA(LCID lcid, DWORD mapflags, const char* src, int srclen, char* dst, int dstlen, unsigned int codepage, int xflag)
{
    struct qemu___crtLCMapStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTLCMAPSTRINGA);
    call.lcid = lcid;
    call.mapflags = mapflags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.codepage = codepage;
    call.xflag = xflag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtLCMapStringA(struct qemu_syscall *call)
{
    struct qemu___crtLCMapStringA *c = (struct qemu___crtLCMapStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtLCMapStringA(c->lcid, c->mapflags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen, c->codepage, c->xflag);
}

#endif

struct qemu___crtLCMapStringW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t mapflags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t codepage;
    uint64_t xflag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __crtLCMapStringW(LCID lcid, DWORD mapflags, const wchar_t *src, int srclen, wchar_t *dst, int dstlen, unsigned int codepage, int xflag)
{
    struct qemu___crtLCMapStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTLCMAPSTRINGW);
    call.lcid = lcid;
    call.mapflags = mapflags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.codepage = codepage;
    call.xflag = xflag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtLCMapStringW(struct qemu_syscall *call)
{
    struct qemu___crtLCMapStringW *c = (struct qemu___crtLCMapStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtLCMapStringW(c->lcid, c->mapflags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), c->dstlen, c->codepage, c->xflag);
}

#endif

struct qemu___crtCompareStringA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t src1;
    uint64_t len1;
    uint64_t src2;
    uint64_t len2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __crtCompareStringA(LCID lcid, DWORD flags, const char *src1, int len1, const char *src2, int len2)
{
    struct qemu___crtCompareStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTCOMPARESTRINGA);
    call.lcid = lcid;
    call.flags = flags;
    call.src1 = (ULONG_PTR)src1;
    call.len1 = len1;
    call.src2 = (ULONG_PTR)src2;
    call.len2 = len2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtCompareStringA(struct qemu_syscall *call)
{
    struct qemu___crtCompareStringA *c = (struct qemu___crtCompareStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtCompareStringA(c->lcid, c->flags, QEMU_G2H(c->src1), c->len1, QEMU_G2H(c->src2), c->len2);
}

#endif

struct qemu___crtCompareStringW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t src1;
    uint64_t len1;
    uint64_t src2;
    uint64_t len2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __crtCompareStringW(LCID lcid, DWORD flags, const wchar_t *src1, int len1, const wchar_t *src2, int len2)
{
    struct qemu___crtCompareStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTCOMPARESTRINGW);
    call.lcid = lcid;
    call.flags = flags;
    call.src1 = (ULONG_PTR)src1;
    call.len1 = len1;
    call.src2 = (ULONG_PTR)src2;
    call.len2 = len2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtCompareStringW(struct qemu_syscall *call)
{
    struct qemu___crtCompareStringW *c = (struct qemu___crtCompareStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtCompareStringW(c->lcid, c->flags, QEMU_G2H(c->src1), c->len1, QEMU_G2H(c->src2), c->len2);
}

#endif

struct qemu___crtGetLocaleInfoW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t type;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __crtGetLocaleInfoW(LCID lcid, LCTYPE type, wchar_t *buffer, int len)
{
    struct qemu___crtGetLocaleInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTGETLOCALEINFOW);
    call.lcid = lcid;
    call.type = type;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtGetLocaleInfoW(struct qemu_syscall *call)
{
    struct qemu___crtGetLocaleInfoW *c = (struct qemu___crtGetLocaleInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtGetLocaleInfoW(c->lcid, c->type, QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu___crtGetLocaleInfoEx
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t type;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL __crtGetLocaleInfoEx(const WCHAR *locale, LCTYPE type, wchar_t *buffer, int len)
{
    struct qemu___crtGetLocaleInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTGETLOCALEINFOEX);
    call.locale = (ULONG_PTR)locale;
    call.type = type;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtGetLocaleInfoEx(struct qemu_syscall *call)
{
    struct qemu___crtGetLocaleInfoEx *c = (struct qemu___crtGetLocaleInfoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtGetLocaleInfoEx(QEMU_G2H(c->locale), c->type, QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_btowc
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT_wint_t CDECL MSVCRT_btowc(int c)
{
    struct qemu_btowc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BTOWC);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_btowc(struct qemu_syscall *call)
{
    struct qemu_btowc *c = (struct qemu_btowc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_btowc(c->c);
}

#endif

struct qemu___crtGetStringTypeW
{
    struct qemu_syscall super;
    uint64_t unk;
    uint64_t type;
    uint64_t buffer;
    uint64_t len;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL __crtGetStringTypeW(DWORD unk, DWORD type, wchar_t *buffer, int len, WORD *out)
{
    struct qemu___crtGetStringTypeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRTGETSTRINGTYPEW);
    call.unk = unk;
    call.type = type;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___crtGetStringTypeW(struct qemu_syscall *call)
{
    struct qemu___crtGetStringTypeW *c = (struct qemu___crtGetStringTypeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___crtGetStringTypeW(c->unk, c->type, QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->out));
}

#endif

struct qemu_localeconv
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_lconv * CDECL MSVCRT_localeconv(void)
{
    struct qemu_localeconv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALECONV);

    qemu_syscall(&call.super);

    return (struct MSVCRT_lconv *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_localeconv(struct qemu_syscall *call)
{
    struct qemu_localeconv *c = (struct qemu_localeconv *)call;
#if GUEST_BIT == HOST_BIT
    WINE_TRACE("\n");
#else
    WINE_FIXME("The output will need conversion.\n");
#endif
    c->super.iret = QEMU_H2G(p_localeconv());
}

#endif

#ifdef QEMU_DLL_GUEST

int CDECL __lconv_init(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___LCONV_INIT);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu___lconv_init(struct qemu_syscall *call)
{
    /* This may be called by some other library if they use Wine's msvcrt.dll, but there is no
     * guarantee because many host-side libs will be linked against Linux libc. There is no harm
     * in calling this again it seems. */
    WINE_TRACE("\n");
    p___lconv_init();
}

#endif

struct qemu____lc_handle_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LCID* CDECL ___lc_handle_func(void)
{
    struct qemu____lc_handle_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____LC_HANDLE_FUNC);

    qemu_syscall(&call.super);

    return (LCID *)(ULONG_PTR)call.super.iret;
}

#else

void qemu____lc_handle_func(struct qemu_syscall *call)
{
    /* This should be fine on 32 bit as long as the host lib is loaded < 4 GB. */
    struct qemu____lc_handle_func *c = (struct qemu____lc_handle_func *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p____lc_handle_func());
}

#endif

struct qemu____lc_locale_name_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI wchar_t** CDECL ___lc_locale_name_func(void)
{
    struct qemu____lc_locale_name_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____LC_LOCALE_NAME_FUNC);

    qemu_syscall(&call.super);

    return (wchar_t **)(ULONG_PTR)call.super.iret;
}

#else

void qemu____lc_locale_name_func(struct qemu_syscall *call)
{
    struct qemu____lc_locale_name_func *c = (struct qemu____lc_locale_name_func *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p____lc_locale_name_func());
}

#endif

struct qemu____lc_codepage_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL ___lc_codepage_func(void)
{
    struct qemu____lc_codepage_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____LC_CODEPAGE_FUNC);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu____lc_codepage_func(struct qemu_syscall *call)
{
    struct qemu____lc_codepage_func *c = (struct qemu____lc_codepage_func *)call;
    WINE_TRACE("\n");
    c->super.iret = p____lc_codepage_func();
}

#endif

struct qemu____lc_collate_cp_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL ___lc_collate_cp_func(void)
{
    struct qemu____lc_collate_cp_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____LC_COLLATE_CP_FUNC);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu____lc_collate_cp_func(struct qemu_syscall *call)
{
    struct qemu____lc_collate_cp_func *c = (struct qemu____lc_collate_cp_func *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p____lc_collate_cp_func();
}

#endif

struct qemu__get_current_locale
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT__locale_t CDECL MSVCRT__get_current_locale(void)
{
    struct qemu__get_current_locale call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_CURRENT_LOCALE);

    qemu_syscall(&call.super);

    return (MSVCRT__locale_t)(ULONG_PTR)call.super.iret;
}

#else

void qemu__get_current_locale(struct qemu_syscall *call)
{
    struct qemu__get_current_locale *c = (struct qemu__get_current_locale *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__get_current_locale());
}

#endif

struct qemu__free_locale
{
    struct qemu_syscall super;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__free_locale(MSVCRT__locale_t locale)
{
    struct qemu__free_locale call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FREE_LOCALE);
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);
}

#else

void qemu__free_locale(struct qemu_syscall *call)
{
    struct qemu__free_locale *c = (struct qemu__free_locale *)call;
    WINE_FIXME("Unverified!\n");
    p__free_locale(QEMU_G2H(c->locale));
}

#endif

struct qemu__lock_locales
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _lock_locales(void)
{
    struct qemu__lock_locales call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCK_LOCALES);

    qemu_syscall(&call.super);
}

#else

void qemu__lock_locales(struct qemu_syscall *call)
{
    struct qemu__lock_locales *c = (struct qemu__lock_locales *)call;
    WINE_FIXME("Unverified!\n");
    p__lock_locales();
}

#endif

struct qemu__unlock_locales
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _unlock_locales(void)
{
    struct qemu__unlock_locales call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UNLOCK_LOCALES);

    qemu_syscall(&call.super);
}

#else

void qemu__unlock_locales(struct qemu_syscall *call)
{
    struct qemu__unlock_locales *c = (struct qemu__unlock_locales *)call;
    WINE_FIXME("Unverified!\n");
    p__unlock_locales();
}

#endif

struct qemu__create_locale
{
    struct qemu_syscall super;
    uint64_t category;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT__locale_t CDECL MSVCRT__create_locale(int category, const char *locale)
{
    struct qemu__create_locale call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CREATE_LOCALE);
    call.category = category;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (MSVCRT__locale_t)(ULONG_PTR)call.super.iret;
}

#else

void qemu__create_locale(struct qemu_syscall *call)
{
    struct qemu__create_locale *c = (struct qemu__create_locale *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__create_locale(c->category, QEMU_G2H(c->locale)));
}

#endif

struct qemu__wcreate_locale
{
    struct qemu_syscall super;
    uint64_t category;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT__locale_t CDECL MSVCRT__wcreate_locale(int category, const wchar_t *locale)
{
    struct qemu__wcreate_locale call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCREATE_LOCALE);
    call.category = category;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (MSVCRT__locale_t)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcreate_locale(struct qemu_syscall *call)
{
    struct qemu__wcreate_locale *c = (struct qemu__wcreate_locale *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcreate_locale(c->category, QEMU_G2H(c->locale)));
}

#endif

struct qemu_setlocale
{
    struct qemu_syscall super;
    uint64_t category;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_setlocale(int category, const char *locale)
{
    struct qemu_setlocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLOCALE);
    call.category = category;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_setlocale(struct qemu_syscall *call)
{
    struct qemu_setlocale *c = (struct qemu_setlocale *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_setlocale(c->category, QEMU_G2H(c->locale)));
}

#endif

struct qemu__wsetlocale
{
    struct qemu_syscall super;
    uint64_t category;
    uint64_t wlocale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI wchar_t* CDECL MSVCRT__wsetlocale(int category, const wchar_t* wlocale)
{
    struct qemu__wsetlocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSETLOCALE);
    call.category = category;
    call.wlocale = (ULONG_PTR)wlocale;

    qemu_syscall(&call.super);

    return (wchar_t *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wsetlocale(struct qemu_syscall *call)
{
    struct qemu__wsetlocale *c = (struct qemu__wsetlocale *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wsetlocale(c->category, QEMU_G2H(c->wlocale)));
}

#endif

struct qemu__configthreadlocale
{
    struct qemu_syscall super;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

int CDECL _configthreadlocale(int type)
{
    struct qemu__configthreadlocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CONFIGTHREADLOCALE);
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__configthreadlocale(struct qemu_syscall *call)
{
    struct qemu__configthreadlocale *c = (struct qemu__configthreadlocale *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__configthreadlocale(c->type);
}

#endif

