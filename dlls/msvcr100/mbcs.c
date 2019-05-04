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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif


struct qemu___p__mbctype
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL __p__mbctype(void)
{
    struct qemu___p__mbctype call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__MBCTYPE);

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___p__mbctype(struct qemu_syscall *call)
{
    struct qemu___p__mbctype *c = (struct qemu___p__mbctype *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__mbctype());
}

#endif

struct qemu___p___mb_cur_max
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int* CDECL __p___mb_cur_max(void)
{
    struct qemu___p___mb_cur_max call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P___MB_CUR_MAX);

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___p___mb_cur_max(struct qemu_syscall *call)
{
    struct qemu___p___mb_cur_max *c = (struct qemu___p___mb_cur_max *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p___mb_cur_max());
}

#endif

struct qemu____mb_cur_max_func
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT____mb_cur_max_func(void)
{
    struct qemu____mb_cur_max_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____MB_CUR_MAX_FUNC);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu____mb_cur_max_func(struct qemu_syscall *call)
{
    struct qemu____mb_cur_max_func *c = (struct qemu____mb_cur_max_func *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p____mb_cur_max_func();
}

#endif

struct qemu____mb_cur_max_l_func
{
    struct qemu_syscall super;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int* CDECL ___mb_cur_max_l_func(MSVCRT__locale_t locale)
{
    struct qemu____mb_cur_max_l_func call;
    call.super.id = QEMU_SYSCALL_ID(CALL____MB_CUR_MAX_L_FUNC);
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu____mb_cur_max_l_func(struct qemu_syscall *call)
{
    struct qemu____mb_cur_max_l_func *c = (struct qemu____mb_cur_max_l_func *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p____mb_cur_max_l_func(QEMU_G2H(c->locale)));
}

#endif

struct qemu__setmbcp
{
    struct qemu_syscall super;
    uint64_t cp;
};

#ifdef QEMU_DLL_GUEST

int CDECL _setmbcp(int cp)
{
    struct qemu__setmbcp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SETMBCP);
    call.cp = (ULONG_PTR)cp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__setmbcp(struct qemu_syscall *call)
{
    struct qemu__setmbcp *c = (struct qemu__setmbcp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__setmbcp(c->cp);
}

#endif

struct qemu__getmbcp
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

int CDECL _getmbcp(void)
{
    struct qemu__getmbcp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GETMBCP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__getmbcp(struct qemu_syscall *call)
{
    struct qemu__getmbcp *c = (struct qemu__getmbcp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__getmbcp();
}

#endif

struct qemu__mbsnextc
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbsnextc(const unsigned char* str)
{
    struct qemu__mbsnextc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNEXTC);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnextc(struct qemu_syscall *call)
{
    struct qemu__mbsnextc *c = (struct qemu__mbsnextc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnextc(QEMU_G2H(c->str));
}

#endif

struct qemu__mbctolower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbctolower(unsigned int c)
{
    struct qemu__mbctolower call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCTOLOWER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbctolower(struct qemu_syscall *call)
{
    struct qemu__mbctolower *c = (struct qemu__mbctolower *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbctolower(c->c);
}

#endif

struct qemu__mbctoupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbctoupper(unsigned int c)
{
    struct qemu__mbctoupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCTOUPPER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbctoupper(struct qemu_syscall *call)
{
    struct qemu__mbctoupper *c = (struct qemu__mbctoupper *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbctoupper(c->c);
}

#endif

struct qemu__mbctombb
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbctombb(unsigned int c)
{
    struct qemu__mbctombb call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCTOMBB);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbctombb(struct qemu_syscall *call)
{
    struct qemu__mbctombb *c = (struct qemu__mbctombb *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbctombb(c->c);
}

#endif

struct qemu__mbcjistojms
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbcjistojms(unsigned int c)
{
    struct qemu__mbcjistojms call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCJISTOJMS);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbcjistojms(struct qemu_syscall *call)
{
    struct qemu__mbcjistojms *c = (struct qemu__mbcjistojms *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbcjistojms(c->c);
}

#endif

struct qemu__mbcjmstojis
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbcjmstojis(unsigned int c)
{
    struct qemu__mbcjmstojis call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCJMSTOJIS);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbcjmstojis(struct qemu_syscall *call)
{
    struct qemu__mbcjmstojis *c = (struct qemu__mbcjmstojis *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbcjmstojis(c->c);
}

#endif

struct qemu__mbsdec
{
    struct qemu_syscall super;
    uint64_t start;
    uint64_t cur;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsdec(const unsigned char* start, const unsigned char* cur)
{
    struct qemu__mbsdec call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSDEC);
    call.start = (ULONG_PTR)start;
    call.cur = (ULONG_PTR)cur;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsdec(struct qemu_syscall *call)
{
    struct qemu__mbsdec *c = (struct qemu__mbsdec *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsdec(QEMU_G2H(c->start), QEMU_G2H(c->cur)));
}

#endif

struct qemu__mbclen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbclen(const unsigned char* str)
{
    struct qemu__mbclen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCLEN);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbclen(struct qemu_syscall *call)
{
    struct qemu__mbclen *c = (struct qemu__mbclen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbclen(QEMU_G2H(c->str));
}

#endif

struct qemu__mbsinc
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsinc(const unsigned char* str)
{
    struct qemu__mbsinc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSINC);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsinc(struct qemu_syscall *call)
{
    struct qemu__mbsinc *c = (struct qemu__mbsinc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsinc(QEMU_G2H(c->str)));
}

#endif

struct qemu__mbsninc
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t num;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsninc(const unsigned char* str, size_t num)
{
    struct qemu__mbsninc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNINC);
    call.str = (ULONG_PTR)str;
    call.num = (ULONG_PTR)num;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsninc(struct qemu_syscall *call)
{
    struct qemu__mbsninc *c = (struct qemu__mbsninc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsninc(QEMU_G2H(c->str), c->num));
}

#endif

struct qemu__mbslen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL _mbslen(const unsigned char* str)
{
    struct qemu__mbslen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSLEN);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbslen(struct qemu_syscall *call)
{
    struct qemu__mbslen *c = (struct qemu__mbslen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbslen(QEMU_G2H(c->str));
}

#endif

struct qemu__mbccpy
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

void CDECL _mbccpy(unsigned char* dest, const unsigned char* src)
{
    struct qemu__mbccpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCCPY);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);
}

#else

void qemu__mbccpy(struct qemu_syscall *call)
{
    struct qemu__mbccpy *c = (struct qemu__mbccpy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__mbccpy(QEMU_G2H(c->dest), QEMU_G2H(c->src));
}

#endif

struct qemu__mbsncpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsncpy(unsigned char* dst, const unsigned char* src, size_t n)
{
    struct qemu__mbsncpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsncpy(struct qemu_syscall *call)
{
    struct qemu__mbsncpy *c = (struct qemu__mbsncpy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsncpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n));
}

#endif

struct qemu__mbsnbcpy_s_l
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
    uint64_t n;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbcpy_s_l(unsigned char* dst, size_t size, const unsigned char* src, size_t n, MSVCRT__locale_t locale)
{
    struct qemu__mbsnbcpy_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCPY_S_L);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;
    call.n = (ULONG_PTR)n;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcpy_s_l(struct qemu_syscall *call)
{
    struct qemu__mbsnbcpy_s_l *c = (struct qemu__mbsnbcpy_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcpy_s_l(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src), c->n, QEMU_G2H(c->locale));
}

#endif

struct qemu__mbsnbcpy_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbcpy_s(unsigned char* dst, size_t size, const unsigned char* src, size_t n)
{
    struct qemu__mbsnbcpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCPY_S);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcpy_s(struct qemu_syscall *call)
{
    struct qemu__mbsnbcpy_s *c = (struct qemu__mbsnbcpy_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcpy_s(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src), c->n);
}

#endif

struct qemu__mbscpy_s_l
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscpy_s_l(unsigned char *dst, size_t size, const unsigned char *src, MSVCRT__locale_t locale)
{
    struct qemu__mbscpy_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCPY_S_L);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscpy_s_l(struct qemu_syscall *call)
{
    struct qemu__mbscpy_s_l *c = (struct qemu__mbscpy_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscpy_s_l(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src), QEMU_G2H(c->locale));
}

#endif

struct qemu__mbscpy_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscpy_s(unsigned char *dst, size_t size, const unsigned char *src)
{
    struct qemu__mbscpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCPY_S);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscpy_s(struct qemu_syscall *call)
{
    struct qemu__mbscpy_s *c = (struct qemu__mbscpy_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscpy_s(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src));
}

#endif

struct qemu__mbsnbcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsnbcpy(unsigned char* dst, const unsigned char* src, size_t n)
{
    struct qemu__mbsnbcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsnbcpy(struct qemu_syscall *call)
{
    struct qemu__mbsnbcpy *c = (struct qemu__mbsnbcpy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsnbcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n));
}

#endif

struct qemu__mbscmp
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscmp(const unsigned char* str, const unsigned char* cmp)
{
    struct qemu__mbscmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCMP);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscmp(struct qemu_syscall *call)
{
    struct qemu__mbscmp *c = (struct qemu__mbscmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscmp(QEMU_G2H(c->str), QEMU_G2H(c->cmp));
}

#endif

struct qemu__mbsnbicoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t len;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbicoll_l(const unsigned char *str1, const unsigned char *str2, size_t len, MSVCRT__locale_t locale)
{
    struct qemu__mbsnbicoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBICOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.len = (ULONG_PTR)len;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbicoll_l(struct qemu_syscall *call)
{
    struct qemu__mbsnbicoll_l *c = (struct qemu__mbsnbicoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbicoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len, QEMU_G2H(c->locale));
}

#endif

struct qemu__mbsicoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsicoll_l(const unsigned char *str1, const unsigned char *str2, MSVCRT__locale_t locale)
{
    struct qemu__mbsicoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSICOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsicoll_l(struct qemu_syscall *call)
{
    struct qemu__mbsicoll_l *c = (struct qemu__mbsicoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsicoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu__mbsnbicoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbicoll(const unsigned char *str1, const unsigned char *str2, size_t len)
{
    struct qemu__mbsnbicoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBICOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbicoll(struct qemu_syscall *call)
{
    struct qemu__mbsnbicoll *c = (struct qemu__mbsnbicoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbicoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len);
}

#endif

struct qemu__mbsicoll
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsicoll(const unsigned char* str, const unsigned char* cmp)
{
    struct qemu__mbsicoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSICOLL);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsicoll(struct qemu_syscall *call)
{
    struct qemu__mbsicoll *c = (struct qemu__mbsicoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsicoll(QEMU_G2H(c->str), QEMU_G2H(c->cmp));
}

#endif

struct qemu__mbsnbcoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t len;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbcoll_l(const unsigned char *str1, const unsigned char *str2, size_t len, MSVCRT__locale_t locale)
{
    struct qemu__mbsnbcoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.len = (ULONG_PTR)len;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcoll_l(struct qemu_syscall *call)
{
    struct qemu__mbsnbcoll_l *c = (struct qemu__mbsnbcoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len, QEMU_G2H(c->locale));
}

#endif

struct qemu__mbscoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscoll_l(const unsigned char *str1, const unsigned char *str2, MSVCRT__locale_t locale)
{
    struct qemu__mbscoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscoll_l(struct qemu_syscall *call)
{
    struct qemu__mbscoll_l *c = (struct qemu__mbscoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu__mbsnbcoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbcoll(const unsigned char *str1, const unsigned char *str2, size_t len)
{
    struct qemu__mbsnbcoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcoll(struct qemu_syscall *call)
{
    struct qemu__mbsnbcoll *c = (struct qemu__mbsnbcoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len);
}

#endif

struct qemu__mbscoll
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscoll(const unsigned char* str, const unsigned char* cmp)
{
    struct qemu__mbscoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCOLL);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscoll(struct qemu_syscall *call)
{
    struct qemu__mbscoll *c = (struct qemu__mbscoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscoll(QEMU_G2H(c->str), QEMU_G2H(c->cmp));
}

#endif

struct qemu__mbsicmp
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsicmp(const unsigned char* str, const unsigned char* cmp)
{
    struct qemu__mbsicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSICMP);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsicmp(struct qemu_syscall *call)
{
    struct qemu__mbsicmp *c = (struct qemu__mbsicmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsicmp(QEMU_G2H(c->str), QEMU_G2H(c->cmp));
}

#endif

struct qemu__mbsncmp
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsncmp(const unsigned char* str, const unsigned char* cmp, size_t len)
{
    struct qemu__mbsncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNCMP);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsncmp(struct qemu_syscall *call)
{
    struct qemu__mbsncmp *c = (struct qemu__mbsncmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsncmp(QEMU_G2H(c->str), QEMU_G2H(c->cmp), c->len);
}

#endif

struct qemu__mbsnbcmp
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbcmp(const unsigned char* str, const unsigned char* cmp, size_t len)
{
    struct qemu__mbsnbcmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCMP);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcmp(struct qemu_syscall *call)
{
    struct qemu__mbsnbcmp *c = (struct qemu__mbsnbcmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcmp(QEMU_G2H(c->str), QEMU_G2H(c->cmp), c->len);
}

#endif

struct qemu__mbsnicmp
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnicmp(const unsigned char* str, const unsigned char* cmp, size_t len)
{
    struct qemu__mbsnicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNICMP);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnicmp(struct qemu_syscall *call)
{
    struct qemu__mbsnicmp *c = (struct qemu__mbsnicmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnicmp(QEMU_G2H(c->str), QEMU_G2H(c->cmp), c->len);
}

#endif

struct qemu__mbsnbicmp
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbicmp(const unsigned char* str, const unsigned char* cmp, size_t len)
{
    struct qemu__mbsnbicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBICMP);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbicmp(struct qemu_syscall *call)
{
    struct qemu__mbsnbicmp *c = (struct qemu__mbsnbicmp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbicmp(QEMU_G2H(c->str), QEMU_G2H(c->cmp), c->len);
}

#endif

struct qemu__mbscat
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

unsigned char * CDECL _mbscat(unsigned char *dst, const unsigned char *src)
{
    struct qemu__mbscat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCAT);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbscat(struct qemu_syscall *call)
{
    struct qemu__mbscat *c = (struct qemu__mbscat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbscat(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
}

#endif

struct qemu__mbscat_s_l
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscat_s_l(unsigned char *dst, size_t size, const unsigned char *src, MSVCRT__locale_t locale)
{
    struct qemu__mbscat_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCAT_S_L);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscat_s_l(struct qemu_syscall *call)
{
    struct qemu__mbscat_s_l *c = (struct qemu__mbscat_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscat_s_l(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src), QEMU_G2H(c->locale));
}

#endif

struct qemu__mbscat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbscat_s(unsigned char *dst, size_t size, const unsigned char *src)
{
    struct qemu__mbscat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCAT_S);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscat_s(struct qemu_syscall *call)
{
    struct qemu__mbscat_s *c = (struct qemu__mbscat_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscat_s(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src));
}

#endif

struct qemu__mbscpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbscpy(unsigned char *dst, const unsigned char *src)
{
    struct qemu__mbscpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbscpy(struct qemu_syscall *call)
{
    struct qemu__mbscpy *c = (struct qemu__mbscpy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbscpy(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
}

#endif

struct qemu__mbsstr
{
    struct qemu_syscall super;
    uint64_t haystack;
    uint64_t needle;
};

#ifdef QEMU_DLL_GUEST

unsigned char * CDECL _mbsstr(const unsigned char *haystack, const unsigned char *needle)
{
    struct qemu__mbsstr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSSTR);
    call.haystack = (ULONG_PTR)haystack;
    call.needle = (ULONG_PTR)needle;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsstr(struct qemu_syscall *call)
{
    struct qemu__mbsstr *c = (struct qemu__mbsstr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsstr(QEMU_G2H(c->haystack), QEMU_G2H(c->needle)));
}

#endif

struct qemu__mbschr
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbschr(const unsigned char* s, unsigned int x)
{
    struct qemu__mbschr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCHR);
    call.s = (ULONG_PTR)s;
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbschr(struct qemu_syscall *call)
{
    struct qemu__mbschr *c = (struct qemu__mbschr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbschr(QEMU_G2H(c->s), c->x));
}

#endif

struct qemu__mbsrchr
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsrchr(const unsigned char* s, unsigned int x)
{
    struct qemu__mbsrchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSRCHR);
    call.s = (ULONG_PTR)s;
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsrchr(struct qemu_syscall *call)
{
    struct qemu__mbsrchr *c = (struct qemu__mbsrchr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsrchr(QEMU_G2H(c->s), c->x));
}

#endif

struct qemu__mbstok_s_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
    uint64_t ctx;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbstok_s_l(unsigned char *str, const unsigned char *delim, unsigned char **ctx, MSVCRT__locale_t locale)
{
    struct qemu__mbstok_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTOK_S_L);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;
    call.ctx = (ULONG_PTR)ctx;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbstok_s_l(struct qemu_syscall *call)
{
    struct qemu__mbstok_s_l *c = (struct qemu__mbstok_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbstok_s_l(QEMU_G2H(c->str), QEMU_G2H(c->delim), QEMU_G2H(c->ctx), QEMU_G2H(c->locale)));
}

#endif

struct qemu__mbstok_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbstok_s(unsigned char *str, const unsigned char *delim, unsigned char **ctx)
{
    struct qemu__mbstok_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTOK_S);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbstok_s(struct qemu_syscall *call)
{
    struct qemu__mbstok_s *c = (struct qemu__mbstok_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbstok_s(QEMU_G2H(c->str), QEMU_G2H(c->delim), QEMU_G2H(c->ctx)));
}

#endif

struct qemu__mbstok_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbstok_l(unsigned char *str, const unsigned char *delim, MSVCRT__locale_t locale)
{
    struct qemu__mbstok_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTOK_L);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbstok_l(struct qemu_syscall *call)
{
    struct qemu__mbstok_l *c = (struct qemu__mbstok_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbstok_l(QEMU_G2H(c->str), QEMU_G2H(c->delim), QEMU_G2H(c->locale)));
}

#endif

struct qemu__mbstok
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbstok(unsigned char *str, const unsigned char *delim)
{
    struct qemu__mbstok call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTOK);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbstok(struct qemu_syscall *call)
{
    struct qemu__mbstok *c = (struct qemu__mbstok *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbstok(QEMU_G2H(c->str), QEMU_G2H(c->delim)));
}

#endif

struct qemu__mbbtombc
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbbtombc(unsigned int c)
{
    struct qemu__mbbtombc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBBTOMBC);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbbtombc(struct qemu_syscall *call)
{
    struct qemu__mbbtombc *c = (struct qemu__mbbtombc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbbtombc(c->c);
}

#endif

struct qemu__mbbtype
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbbtype(unsigned char c, int type)
{
    struct qemu__mbbtype call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBBTYPE);
    call.c = (ULONG_PTR)c;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbbtype(struct qemu_syscall *call)
{
    struct qemu__mbbtype *c = (struct qemu__mbbtype *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbbtype(c->c, c->type);
}

#endif

struct qemu__ismbbkana
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbbkana(unsigned int c)
{
    struct qemu__ismbbkana call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBBKANA);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbbkana(struct qemu_syscall *call)
{
    struct qemu__ismbbkana *c = (struct qemu__ismbbkana *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbbkana(c->c);
}

#endif

struct qemu__ismbcdigit
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcdigit(unsigned int ch)
{
    struct qemu__ismbcdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCDIGIT);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcdigit(struct qemu_syscall *call)
{
    struct qemu__ismbcdigit *c = (struct qemu__ismbcdigit *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcdigit(c->ch);
}

#endif

struct qemu__ismbcgraph
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcgraph(unsigned int ch)
{
    struct qemu__ismbcgraph call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCGRAPH);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcgraph(struct qemu_syscall *call)
{
    struct qemu__ismbcgraph *c = (struct qemu__ismbcgraph *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcgraph(c->ch);
}

#endif

struct qemu__ismbcalpha
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcalpha(unsigned int ch)
{
    struct qemu__ismbcalpha call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCALPHA);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcalpha(struct qemu_syscall *call)
{
    struct qemu__ismbcalpha *c = (struct qemu__ismbcalpha *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcalpha(c->ch);
}

#endif

struct qemu__ismbclower
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbclower(unsigned int ch)
{
    struct qemu__ismbclower call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCLOWER);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbclower(struct qemu_syscall *call)
{
    struct qemu__ismbclower *c = (struct qemu__ismbclower *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbclower(c->ch);
}

#endif

struct qemu__ismbcupper
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcupper(unsigned int ch)
{
    struct qemu__ismbcupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCUPPER);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcupper(struct qemu_syscall *call)
{
    struct qemu__ismbcupper *c = (struct qemu__ismbcupper *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcupper(c->ch);
}

#endif

struct qemu__ismbcsymbol
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcsymbol(unsigned int ch)
{
    struct qemu__ismbcsymbol call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCSYMBOL);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcsymbol(struct qemu_syscall *call)
{
    struct qemu__ismbcsymbol *c = (struct qemu__ismbcsymbol *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcsymbol(c->ch);
}

#endif

struct qemu__ismbcalnum
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcalnum(unsigned int ch)
{
    struct qemu__ismbcalnum call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCALNUM);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcalnum(struct qemu_syscall *call)
{
    struct qemu__ismbcalnum *c = (struct qemu__ismbcalnum *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcalnum(c->ch);
}

#endif

struct qemu__ismbcspace
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcspace(unsigned int ch)
{
    struct qemu__ismbcspace call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCSPACE);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcspace(struct qemu_syscall *call)
{
    struct qemu__ismbcspace *c = (struct qemu__ismbcspace *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcspace(c->ch);
}

#endif

struct qemu__ismbcprint
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcprint(unsigned int ch)
{
    struct qemu__ismbcprint call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCPRINT);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcprint(struct qemu_syscall *call)
{
    struct qemu__ismbcprint *c = (struct qemu__ismbcprint *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcprint(c->ch);
}

#endif

struct qemu__ismbcpunct
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbcpunct(unsigned int ch)
{
    struct qemu__ismbcpunct call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCPUNCT);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbcpunct(struct qemu_syscall *call)
{
    struct qemu__ismbcpunct *c = (struct qemu__ismbcpunct *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbcpunct(c->ch);
}

#endif

struct qemu__ismbchira
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbchira(unsigned int c)
{
    struct qemu__ismbchira call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCHIRA);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbchira(struct qemu_syscall *call)
{
    struct qemu__ismbchira *c = (struct qemu__ismbchira *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbchira(c->c);
}

#endif

struct qemu__ismbckata
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbckata(unsigned int c)
{
    struct qemu__ismbckata call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCKATA);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbckata(struct qemu_syscall *call)
{
    struct qemu__ismbckata *c = (struct qemu__ismbckata *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbckata(c->c);
}

#endif

struct qemu__ismbblead_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbblead_l(unsigned int c, MSVCRT__locale_t locale)
{
    struct qemu__ismbblead_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBBLEAD_L);
    call.c = (ULONG_PTR)c;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbblead_l(struct qemu_syscall *call)
{
    struct qemu__ismbblead_l *c = (struct qemu__ismbblead_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbblead_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu__ismbblead
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbblead(unsigned int c)
{
    struct qemu__ismbblead call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBBLEAD);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbblead(struct qemu_syscall *call)
{
    struct qemu__ismbblead *c = (struct qemu__ismbblead *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__ismbblead(c->c);
}

#endif

struct qemu__ismbbtrail
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbbtrail(unsigned int c)
{
    struct qemu__ismbbtrail call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBBTRAIL);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbbtrail(struct qemu_syscall *call)
{
    struct qemu__ismbbtrail *c = (struct qemu__ismbbtrail *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbbtrail(c->c);
}

#endif

struct qemu__ismbclegal
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbclegal(unsigned int c)
{
    struct qemu__ismbclegal call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBCLEGAL);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbclegal(struct qemu_syscall *call)
{
    struct qemu__ismbclegal *c = (struct qemu__ismbclegal *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbclegal(c->c);
}

#endif

struct qemu__ismbslead
{
    struct qemu_syscall super;
    uint64_t start;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbslead(const unsigned char* start, const unsigned char* str)
{
    struct qemu__ismbslead call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBSLEAD);
    call.start = (ULONG_PTR)start;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbslead(struct qemu_syscall *call)
{
    struct qemu__ismbslead *c = (struct qemu__ismbslead *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbslead(QEMU_G2H(c->start), QEMU_G2H(c->str));
}

#endif

struct qemu__ismbstrail
{
    struct qemu_syscall super;
    uint64_t start;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL _ismbstrail(const unsigned char* start, const unsigned char* str)
{
    struct qemu__ismbstrail call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISMBSTRAIL);
    call.start = (ULONG_PTR)start;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ismbstrail(struct qemu_syscall *call)
{
    struct qemu__ismbstrail *c = (struct qemu__ismbstrail *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ismbstrail(QEMU_G2H(c->start), QEMU_G2H(c->str));
}

#endif

struct qemu__mbsbtype
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsbtype(const unsigned char *str, size_t count)
{
    struct qemu__mbsbtype call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSBTYPE);
    call.str = (ULONG_PTR)str;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsbtype(struct qemu_syscall *call)
{
    struct qemu__mbsbtype *c = (struct qemu__mbsbtype *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsbtype(QEMU_G2H(c->str), c->count);
}

#endif

struct qemu__mbsset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsset(unsigned char* str, unsigned int c)
{
    struct qemu__mbsset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSSET);
    call.str = (ULONG_PTR)str;
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsset(struct qemu_syscall *call)
{
    struct qemu__mbsset *c = (struct qemu__mbsset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsset(QEMU_G2H(c->str), c->c));
}

#endif

struct qemu__mbsnbset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsnbset(unsigned char *str, unsigned int c, size_t len)
{
    struct qemu__mbsnbset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBSET);
    call.str = (ULONG_PTR)str;
    call.c = (ULONG_PTR)c;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsnbset(struct qemu_syscall *call)
{
    struct qemu__mbsnbset *c = (struct qemu__mbsnbset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsnbset(QEMU_G2H(c->str), c->c, c->len));
}

#endif

struct qemu__mbsnset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsnset(unsigned char* str, unsigned int c, size_t len)
{
    struct qemu__mbsnset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNSET);
    call.str = (ULONG_PTR)str;
    call.c = (ULONG_PTR)c;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsnset(struct qemu_syscall *call)
{
    struct qemu__mbsnset *c = (struct qemu__mbsnset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsnset(QEMU_G2H(c->str), c->c, c->len));
}

#endif

struct qemu__mbsnccnt
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL _mbsnccnt(const unsigned char* str, size_t len)
{
    struct qemu__mbsnccnt call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNCCNT);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnccnt(struct qemu_syscall *call)
{
    struct qemu__mbsnccnt *c = (struct qemu__mbsnccnt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnccnt(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu__mbsnbcnt
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL _mbsnbcnt(const unsigned char* str, size_t len)
{
    struct qemu__mbsnbcnt call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCNT);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcnt(struct qemu_syscall *call)
{
    struct qemu__mbsnbcnt *c = (struct qemu__mbsnbcnt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcnt(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu__mbsnbcat
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsnbcat(unsigned char* dst, const unsigned char* src, size_t len)
{
    struct qemu__mbsnbcat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCAT);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsnbcat(struct qemu_syscall *call)
{
    struct qemu__mbsnbcat *c = (struct qemu__mbsnbcat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsnbcat(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->len));
}

#endif

struct qemu__mbsnbcat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsnbcat_s(unsigned char *dst, size_t size, const unsigned char *src, size_t len)
{
    struct qemu__mbsnbcat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNBCAT_S);
    call.dst = (ULONG_PTR)dst;
    call.size = (ULONG_PTR)size;
    call.src = (ULONG_PTR)src;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsnbcat_s(struct qemu_syscall *call)
{
    struct qemu__mbsnbcat_s *c = (struct qemu__mbsnbcat_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsnbcat_s(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src), c->len);
}

#endif

struct qemu__mbsncat
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsncat(unsigned char* dst, const unsigned char* src, size_t len)
{
    struct qemu__mbsncat call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSNCAT);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsncat(struct qemu_syscall *call)
{
    struct qemu__mbsncat *c = (struct qemu__mbsncat *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsncat(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->len));
}

#endif

struct qemu__mbslwr
{
    struct qemu_syscall super;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbslwr(unsigned char* s)
{
    struct qemu__mbslwr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSLWR);
    call.s = (ULONG_PTR)s;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbslwr(struct qemu_syscall *call)
{
    struct qemu__mbslwr *c = (struct qemu__mbslwr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbslwr(QEMU_G2H(c->s)));
}

#endif

struct qemu__mbslwr_s
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbslwr_s(unsigned char* s, size_t len)
{
    struct qemu__mbslwr_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSLWR_S);
    call.s = (ULONG_PTR)s;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbslwr_s(struct qemu_syscall *call)
{
    struct qemu__mbslwr_s *c = (struct qemu__mbslwr_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbslwr_s(QEMU_G2H(c->s), c->len);
}

#endif

struct qemu__mbsupr
{
    struct qemu_syscall super;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsupr(unsigned char* s)
{
    struct qemu__mbsupr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSUPR);
    call.s = (ULONG_PTR)s;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsupr(struct qemu_syscall *call)
{
    struct qemu__mbsupr *c = (struct qemu__mbsupr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsupr(QEMU_G2H(c->s)));
}

#endif

struct qemu__mbsupr_s
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL _mbsupr_s(unsigned char* s, size_t len)
{
    struct qemu__mbsupr_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSUPR_S);
    call.s = (ULONG_PTR)s;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsupr_s(struct qemu_syscall *call)
{
    struct qemu__mbsupr_s *c = (struct qemu__mbsupr_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsupr_s(QEMU_G2H(c->s), c->len);
}

#endif

struct qemu__mbsspn
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t set;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL _mbsspn(const unsigned char* string, const unsigned char* set)
{
    struct qemu__mbsspn call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSSPN);
    call.string = (ULONG_PTR)string;
    call.set = (ULONG_PTR)set;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbsspn(struct qemu_syscall *call)
{
    struct qemu__mbsspn *c = (struct qemu__mbsspn *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbsspn(QEMU_G2H(c->string), QEMU_G2H(c->set));
}

#endif

struct qemu__mbsspnp
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t set;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsspnp(const unsigned char* string, const unsigned char* set)
{
    struct qemu__mbsspnp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSSPNP);
    call.string = (ULONG_PTR)string;
    call.set = (ULONG_PTR)set;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsspnp(struct qemu_syscall *call)
{
    struct qemu__mbsspnp *c = (struct qemu__mbsspnp *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsspnp(QEMU_G2H(c->string), QEMU_G2H(c->set)));
}

#endif

struct qemu__mbscspn
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t cmp;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL _mbscspn(const unsigned char* str, const unsigned char* cmp)
{
    struct qemu__mbscspn call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSCSPN);
    call.str = (ULONG_PTR)str;
    call.cmp = (ULONG_PTR)cmp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbscspn(struct qemu_syscall *call)
{
    struct qemu__mbscspn *c = (struct qemu__mbscspn *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbscspn(QEMU_G2H(c->str), QEMU_G2H(c->cmp));
}

#endif

struct qemu__mbsrev
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbsrev(unsigned char* str)
{
    struct qemu__mbsrev call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSREV);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbsrev(struct qemu_syscall *call)
{
    struct qemu__mbsrev *c = (struct qemu__mbsrev *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbsrev(QEMU_G2H(c->str)));
}

#endif

struct qemu__mbspbrk
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t accept;
};

#ifdef QEMU_DLL_GUEST

unsigned char* CDECL _mbspbrk(const unsigned char* str, const unsigned char* accept)
{
    struct qemu__mbspbrk call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSPBRK);
    call.str = (ULONG_PTR)str;
    call.accept = (ULONG_PTR)accept;

    qemu_syscall(&call.super);

    return (unsigned char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__mbspbrk(struct qemu_syscall *call)
{
    struct qemu__mbspbrk *c = (struct qemu__mbspbrk *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__mbspbrk(QEMU_G2H(c->str), QEMU_G2H(c->accept)));
}

#endif

struct qemu_mblen
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_mblen(const char* str, size_t size)
{
    struct qemu_mblen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBLEN);
    call.str = (ULONG_PTR)str;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mblen(struct qemu_syscall *call)
{
    struct qemu_mblen *c = (struct qemu_mblen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mblen(QEMU_G2H(c->str), c->size);
}

#endif

struct qemu_mbrlen
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_mbrlen(const char *str, size_t len, void *state)
{
    struct qemu_mbrlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBRLEN);
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbrlen(struct qemu_syscall *call)
{
    struct qemu_mbrlen *c = (struct qemu_mbrlen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbrlen(QEMU_G2H(c->str), c->len, QEMU_G2H(c->state));
}

#endif

struct qemu__mbstrlen_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__mbstrlen_l(const char* str, MSVCRT__locale_t locale)
{
    struct qemu__mbstrlen_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTRLEN_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbstrlen_l(struct qemu_syscall *call)
{
    struct qemu__mbstrlen_l *c = (struct qemu__mbstrlen_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbstrlen_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__mbstrlen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__mbstrlen(const char* str)
{
    struct qemu__mbstrlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTRLEN);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbstrlen(struct qemu_syscall *call)
{
    struct qemu__mbstrlen *c = (struct qemu__mbstrlen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbstrlen(QEMU_G2H(c->str));
}

#endif

struct qemu_mbtowc_l
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t str;
    uint64_t n;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_mbtowc_l(WCHAR *dst, const char* str, size_t n, MSVCRT__locale_t locale)
{
    struct qemu_mbtowc_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBTOWC_L);
    call.dst = (ULONG_PTR)dst;
    call.str = (ULONG_PTR)str;
    call.n = (ULONG_PTR)n;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbtowc_l(struct qemu_syscall *call)
{
    struct qemu_mbtowc_l *c = (struct qemu_mbtowc_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbtowc_l(QEMU_G2H(c->dst), QEMU_G2H(c->str), c->n, QEMU_G2H(c->locale));
}

#endif

struct qemu_mbtowc
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t str;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_mbtowc(WCHAR *dst, const char* str, size_t n)
{
    struct qemu_mbtowc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBTOWC);
    call.dst = (ULONG_PTR)dst;
    call.str = (ULONG_PTR)str;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbtowc(struct qemu_syscall *call)
{
    struct qemu_mbtowc *c = (struct qemu_mbtowc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbtowc(QEMU_G2H(c->dst), QEMU_G2H(c->str), c->n);
}

#endif

struct qemu_mbrtowc
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t str;
    uint64_t n;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_mbrtowc(WCHAR *dst, const char *str, size_t n, void *state)
{
    struct qemu_mbrtowc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBRTOWC);
    call.dst = (ULONG_PTR)dst;
    call.str = (ULONG_PTR)str;
    call.n = (ULONG_PTR)n;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbrtowc(struct qemu_syscall *call)
{
    struct qemu_mbrtowc *c = (struct qemu_mbrtowc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbrtowc(QEMU_G2H(c->dst), QEMU_G2H(c->str), c->n, QEMU_G2H(c->state));
}

#endif

struct qemu__mbstowcs_l
{
    struct qemu_syscall super;
    uint64_t wcstr;
    uint64_t mbstr;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__mbstowcs_l(WCHAR *wcstr, const char *mbstr, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__mbstowcs_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTOWCS_L);
    call.wcstr = (ULONG_PTR)wcstr;
    call.mbstr = (ULONG_PTR)mbstr;
    call.count = (ULONG_PTR)count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbstowcs_l(struct qemu_syscall *call)
{
    struct qemu__mbstowcs_l *c = (struct qemu__mbstowcs_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbstowcs_l(QEMU_G2H(c->wcstr), QEMU_G2H(c->mbstr), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu_mbstowcs
{
    struct qemu_syscall super;
    uint64_t wcstr;
    uint64_t mbstr;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_mbstowcs(WCHAR *wcstr, const char *mbstr, size_t count)
{
    struct qemu_mbstowcs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBSTOWCS);
    call.wcstr = (ULONG_PTR)wcstr;
    call.mbstr = (ULONG_PTR)mbstr;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbstowcs(struct qemu_syscall *call)
{
    struct qemu_mbstowcs *c = (struct qemu_mbstowcs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbstowcs(QEMU_G2H(c->wcstr), QEMU_G2H(c->mbstr), c->count);
}

#endif

struct qemu__mbstowcs_s_l
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t wcstr;
    uint64_t size;
    uint64_t mbstr;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__mbstowcs_s_l(size_t *ret, WCHAR *wcstr, size_t size, const char *mbstr, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__mbstowcs_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBSTOWCS_S_L);
    call.ret = (ULONG_PTR)ret;
    call.wcstr = (ULONG_PTR)wcstr;
    call.size = (ULONG_PTR)size;
    call.mbstr = (ULONG_PTR)mbstr;
    call.count = (ULONG_PTR)count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbstowcs_s_l(struct qemu_syscall *call)
{
    struct qemu__mbstowcs_s_l *c = (struct qemu__mbstowcs_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbstowcs_s_l(QEMU_G2H(c->ret), QEMU_G2H(c->wcstr), c->size, QEMU_G2H(c->mbstr), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu_mbstowcs_s
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t wcstr;
    uint64_t size;
    uint64_t mbstr;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__mbstowcs_s(size_t *ret, WCHAR *wcstr, size_t size, const char *mbstr, size_t count)
{
    struct qemu_mbstowcs_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBSTOWCS_S);
    call.ret = (ULONG_PTR)ret;
    call.wcstr = (ULONG_PTR)wcstr;
    call.size = (ULONG_PTR)size;
    call.mbstr = (ULONG_PTR)mbstr;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbstowcs_s(struct qemu_syscall *call)
{
    struct qemu_mbstowcs_s *c = (struct qemu_mbstowcs_s *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_mbstowcs_s(QEMU_G2H(c->ret), QEMU_G2H(c->wcstr), c->size, QEMU_G2H(c->mbstr), c->count);
}

#endif

struct qemu_mbsrtowcs
{
    struct qemu_syscall super;
    uint64_t wcstr;
    uint64_t pmbstr;
    uint64_t count;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_mbsrtowcs(WCHAR *wcstr, const char **pmbstr, size_t count, void *state)
{
    struct qemu_mbsrtowcs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBSRTOWCS);
    call.wcstr = (ULONG_PTR)wcstr;
    call.pmbstr = (ULONG_PTR)pmbstr;
    call.count = (ULONG_PTR)count;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbsrtowcs(struct qemu_syscall *call)
{
    struct qemu_mbsrtowcs *c = (struct qemu_mbsrtowcs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbsrtowcs(QEMU_G2H(c->wcstr), QEMU_G2H(c->pmbstr), c->count, QEMU_G2H(c->state));
}

#endif

struct qemu_mbsrtowcs_s
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t wcstr;
    uint64_t len;
    uint64_t mbstr;
    uint64_t count;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_mbsrtowcs_s(size_t *ret, WCHAR *wcstr, size_t len, const char **mbstr, size_t count, void *state)
{
    struct qemu_mbsrtowcs_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MBSRTOWCS_S);
    call.ret = (ULONG_PTR)ret;
    call.wcstr = (ULONG_PTR)wcstr;
    call.len = (ULONG_PTR)len;
    call.mbstr = (ULONG_PTR)mbstr;
    call.count = (ULONG_PTR)count;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mbsrtowcs_s(struct qemu_syscall *call)
{
    struct qemu_mbsrtowcs_s *c = (struct qemu_mbsrtowcs_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mbsrtowcs_s(QEMU_G2H(c->ret), QEMU_G2H(c->wcstr), c->len, QEMU_G2H(c->mbstr), c->count, QEMU_G2H(c->state));
}

#endif

struct qemu__mbctohira
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbctohira(unsigned int c)
{
    struct qemu__mbctohira call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCTOHIRA);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbctohira(struct qemu_syscall *call)
{
    struct qemu__mbctohira *c = (struct qemu__mbctohira *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbctohira(c->c);
}

#endif

struct qemu__mbctokata
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

unsigned int CDECL _mbctokata(unsigned int c)
{
    struct qemu__mbctokata call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MBCTOKATA);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mbctokata(struct qemu_syscall *call)
{
    struct qemu__mbctokata *c = (struct qemu__mbctokata *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mbctokata(c->c);
}

#endif

