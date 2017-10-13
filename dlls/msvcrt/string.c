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

struct qemu__strdup
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__strdup(const char *str)
{
    struct qemu__strdup call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRDUP);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strdup(struct qemu_syscall *call)
{
    struct qemu__strdup *c = (struct qemu__strdup *)(ULONG_PTR)call;
    WINE_TRACE("\n", c->str);
    c->super.iret = QEMU_H2G(p__strdup(QEMU_G2H(c->str)));
}

#endif

struct qemu__strlwr_s_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strlwr_s_l(char *str, size_t len, MSVCRT__locale_t locale)
{
    struct qemu__strlwr_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRLWR_S_L);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strlwr_s_l(struct qemu_syscall *call)
{
    struct qemu__strlwr_s_l *c = (struct qemu__strlwr_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strlwr_s_l(QEMU_G2H(c->str), c->len, QEMU_G2H(c->locale));
}

#endif

struct qemu__strlwr_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strlwr_s(char *str, size_t len)
{
    struct qemu__strlwr_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRLWR_S);
    call.str = (ULONG_PTR)str;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strlwr_s(struct qemu_syscall *call)
{
    struct qemu__strlwr_s *c = (struct qemu__strlwr_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strlwr_s(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu__strlwr_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

char* CDECL _strlwr_l(char *str, MSVCRT__locale_t locale)
{
    struct qemu__strlwr_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRLWR_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strlwr_l(struct qemu_syscall *call)
{
    struct qemu__strlwr_l *c = (struct qemu__strlwr_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strlwr_l(QEMU_G2H(c->str), QEMU_G2H(c->locale)));
}

#endif

struct qemu__strlwr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__strlwr(char *str)
{
    struct qemu__strlwr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRLWR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strlwr(struct qemu_syscall *call)
{
    struct qemu__strlwr *c = (struct qemu__strlwr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strlwr(QEMU_G2H(c->str)));
}

#endif

struct qemu__strupr_s_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strupr_s_l(char *str, size_t len, MSVCRT__locale_t locale)
{
    struct qemu__strupr_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRUPR_S_L);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strupr_s_l(struct qemu_syscall *call)
{
    struct qemu__strupr_s_l *c = (struct qemu__strupr_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strupr_s_l(QEMU_G2H(c->str), c->len, QEMU_G2H(c->locale));
}

#endif

struct qemu__strupr_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strupr_s(char *str, size_t len)
{
    struct qemu__strupr_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRUPR_S);
    call.str = (ULONG_PTR)str;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strupr_s(struct qemu_syscall *call)
{
    struct qemu__strupr_s *c = (struct qemu__strupr_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strupr_s(QEMU_G2H(c->str), c->len);
}

#endif

struct qemu__strupr_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__strupr_l(char *str, MSVCRT__locale_t locale)
{
    struct qemu__strupr_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRUPR_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strupr_l(struct qemu_syscall *call)
{
    struct qemu__strupr_l *c = (struct qemu__strupr_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strupr_l(QEMU_G2H(c->str), QEMU_G2H(c->locale)));
}

#endif

struct qemu__strupr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__strupr(char *str)
{
    struct qemu__strupr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRUPR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strupr(struct qemu_syscall *call)
{
    struct qemu__strupr *c = (struct qemu__strupr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strupr(QEMU_G2H(c->str)));
}

#endif

struct qemu__strnset_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size;
    uint64_t c;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strnset_s(char *str, size_t size, int c, size_t count)
{
    struct qemu__strnset_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNSET_S);
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.c = c;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strnset_s(struct qemu_syscall *call)
{
    struct qemu__strnset_s *c = (struct qemu__strnset_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strnset_s(QEMU_G2H(c->str), c->size, c->c, c->count);
}

#endif

struct qemu__strnset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t value;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__strnset(char* str, int value, size_t len)
{
    struct qemu__strnset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNSET);
    call.str = (ULONG_PTR)str;
    call.value = value;
    call.len = len;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strnset(struct qemu_syscall *call)
{
    struct qemu__strnset *c = (struct qemu__strnset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strnset(QEMU_G2H(c->str), c->value, c->len));
}

#endif

struct qemu__strrev
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__strrev(char* str)
{
    struct qemu__strrev call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRREV);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strrev(struct qemu_syscall *call)
{
    struct qemu__strrev *c = (struct qemu__strrev *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strrev(QEMU_G2H(c->str)));
}

#endif

struct qemu__strset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

char* CDECL _strset(char* str, int value)
{
    struct qemu__strset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRSET);
    call.str = (ULONG_PTR)str;
    call.value = value;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strset(struct qemu_syscall *call)
{
    struct qemu__strset *c = (struct qemu__strset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strset(QEMU_G2H(c->str), c->value));
}

#endif

struct qemu_strtok
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strtok(char *str, const char *delim)
{
    struct qemu_strtok call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOK);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strtok(struct qemu_syscall *call)
{
    struct qemu_strtok *c = (struct qemu_strtok *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strtok(QEMU_G2H(c->str), QEMU_G2H(c->delim)));
}

#endif

struct qemu_strtok_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strtok_s(char *str, const char *delim, char **ctx)
{
    struct qemu_strtok_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOK_S);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strtok_s(struct qemu_syscall *call)
{
    struct qemu_strtok_s *c = (struct qemu_strtok_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strtok_s(QEMU_G2H(c->str), QEMU_G2H(c->delim), QEMU_G2H(c->ctx)));
}

#endif

struct qemu__swab
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dst;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__swab(char* src, char* dst, int len)
{
    struct qemu__swab call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SWAB);
    call.src = (ULONG_PTR)src;
    call.dst = (ULONG_PTR)dst;
    call.len = len;

    qemu_syscall(&call.super);
}

#else

void qemu__swab(struct qemu_syscall *call)
{
    struct qemu__swab *c = (struct qemu__swab *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__swab(QEMU_G2H(c->src), QEMU_G2H(c->dst), c->len);
}

#endif

struct qemu_strtod_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_strtod_l(const char *str, char **end, MSVCRT__locale_t locale)
{
    struct qemu_strtod_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOD_L);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_strtod_l(struct qemu_syscall *call)
{
    struct qemu_strtod_l *c = (struct qemu_strtod_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_strtod_l(QEMU_G2H(c->str), QEMU_G2H(c->end), QEMU_G2H(c->locale));
}

#endif

struct qemu_strtod
{
    struct qemu_syscall super;
    uint64_t str, end;
};


#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_strtod(const char *str, char **end)
{
    struct qemu_strtod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOD);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_strtod(struct qemu_syscall *call)
{
    struct qemu_strtod *c = (struct qemu_strtod *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_strtod(QEMU_G2H(c->str), QEMU_G2H(c->end));
}

#endif

struct qemu__strtof_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

float CDECL MSVCRT__strtof_l(const char *str, char **end, MSVCRT__locale_t locale)
{
    struct qemu__strtof_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTOF_L);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__strtof_l(struct qemu_syscall *call)
{
    struct qemu__strtof_l *c = (struct qemu__strtof_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__strtof_l(QEMU_G2H(c->str), QEMU_G2H(c->end), QEMU_G2H(c->locale));
}

#endif

struct qemu_strtof
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
};

#ifdef QEMU_DLL_GUEST

float CDECL MSVCRT_strtof(const char *str, char **end)
{
    struct qemu_strtof call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOF);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_strtof(struct qemu_syscall *call)
{
    struct qemu_strtof *c = (struct qemu_strtof *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p_strtof(QEMU_G2H(c->str), QEMU_G2H(c->end));
}

#endif

struct qemu_atof
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_atof(const char *str)
{
    struct qemu_atof call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATOF);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atof(struct qemu_syscall *call)
{
    struct qemu_atof *c = (struct qemu_atof *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p_atof(QEMU_G2H(c->str));
}

#endif

struct qemu__atof_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT__atof_l(const char *str, MSVCRT__locale_t locale)
{
    struct qemu__atof_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATOF_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__atof_l(struct qemu_syscall *call)
{
    struct qemu__atof_l *c = (struct qemu__atof_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.dret = p__atof_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__atoflt_l
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__atoflt_l(FLOAT *value, char *str, MSVCRT__locale_t locale)
{
    struct qemu__atoflt_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATOFLT_L);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atoflt_l(struct qemu_syscall *call)
{
    struct qemu__atoflt_l *c = (struct qemu__atoflt_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atoflt_l(QEMU_G2H(c->value), QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__atoflt
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__atoflt(FLOAT *value, char *str)
{
    struct qemu__atoflt call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATOFLT);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atoflt(struct qemu_syscall *call)
{
    struct qemu__atoflt *c = (struct qemu__atoflt *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atoflt(QEMU_G2H(c->value), QEMU_G2H(c->str));
}

#endif

struct qemu__atodbl_l
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__atodbl_l(DOUBLE *value, char *str, MSVCRT__locale_t locale)
{
    struct qemu__atodbl_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATODBL_L);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atodbl_l(struct qemu_syscall *call)
{
    struct qemu__atodbl_l *c = (struct qemu__atodbl_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atodbl_l(QEMU_G2H(c->value), QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__atodbl
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__atodbl(DOUBLE *value, char *str)
{
    struct qemu__atodbl call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATODBL);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atodbl(struct qemu_syscall *call)
{
    struct qemu__atodbl *c = (struct qemu__atodbl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atodbl(QEMU_G2H(c->value), QEMU_G2H(c->str));
}

#endif

struct qemu_strcoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strcoll_l(const char* str1, const char* str2, MSVCRT__locale_t locale)
{
    struct qemu_strcoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcoll_l(struct qemu_syscall *call)
{
    struct qemu_strcoll_l *c = (struct qemu_strcoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strcoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu_strcoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strcoll(const char* str1, const char* str2)
{
    struct qemu_strcoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcoll(struct qemu_syscall *call)
{
    struct qemu_strcoll *c = (struct qemu_strcoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strcoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu__stricoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__stricoll_l(const char* str1, const char* str2, MSVCRT__locale_t locale)
{
    struct qemu__stricoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRICOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stricoll_l(struct qemu_syscall *call)
{
    struct qemu__stricoll_l *c = (struct qemu__stricoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__stricoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu__stricoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__stricoll(const char* str1, const char* str2)
{
    struct qemu__stricoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRICOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stricoll(struct qemu_syscall *call)
{
    struct qemu__stricoll *c = (struct qemu__stricoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__stricoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu__strncoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strncoll_l(const char* str1, const char* str2, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__strncoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNCOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strncoll_l(struct qemu_syscall *call)
{
    struct qemu__strncoll_l *c = (struct qemu__strncoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strncoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu__strncoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strncoll(const char* str1, const char* str2, size_t count)
{
    struct qemu__strncoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNCOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strncoll(struct qemu_syscall *call)
{
    struct qemu__strncoll *c = (struct qemu__strncoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strncoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu__strnicoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strnicoll_l(const char* str1, const char* str2, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__strnicoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNICOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strnicoll_l(struct qemu_syscall *call)
{
    struct qemu__strnicoll_l *c = (struct qemu__strnicoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strnicoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu__strnicoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strnicoll(const char* str1, const char* str2, size_t count)
{
    struct qemu__strnicoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNICOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strnicoll(struct qemu_syscall *call)
{
    struct qemu__strnicoll *c = (struct qemu__strnicoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strnicoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu_strcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT_strcpy(char *dst, const char *src)
{
    struct qemu_strcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strcpy(struct qemu_syscall *call)
{
    struct qemu_strcpy *c = (struct qemu_strcpy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
}

#endif

/* FIXME: Calling out of the vm for strcpy_s is probably a waste of time. */
struct qemu_strcpy_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t elem;
    uint64_t src;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strcpy_s(char *dst, size_t elem, const char *src)
{
    struct qemu_strcpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPY_S);
    call.dst = (ULONG_PTR)dst;
    call.elem = elem;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcpy_s(struct qemu_syscall *call)
{
    struct qemu_strcpy_s *c = (struct qemu_strcpy_s *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_strcpy_s(QEMU_G2H(c->dst), c->elem, QEMU_G2H(c->src));
}

#endif

/* FIXME: Calling out of the vm for strcat_s is probably a waste of time. */
struct qemu_strcat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t elem;
    uint64_t src;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strcat_s(char *dst, size_t elem, const char *src)
{
    struct qemu_strcat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCAT_S);
    call.dst = (ULONG_PTR)dst;
    call.elem = elem;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcat_s(struct qemu_syscall *call)
{
    struct qemu_strcat_s *c = (struct qemu_strcat_s *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_strcat_s(QEMU_G2H(c->dst), c->elem, QEMU_G2H(c->src));
}

#endif

struct qemu_strncat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t elem;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strncat_s(char* dst, size_t elem, const char* src, size_t count)
{
    struct qemu_strncat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCAT_S);
    call.dst = (ULONG_PTR)dst;
    call.elem = elem;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strncat_s(struct qemu_syscall *call)
{
    struct qemu_strncat_s *c = (struct qemu_strncat_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strncat_s(QEMU_G2H(c->dst), c->elem, QEMU_G2H(c->src), c->count);
}

#endif

struct qemu__strxfrm_l
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t len;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT__strxfrm_l(char *dest, const char *src, size_t len, MSVCRT__locale_t locale)
{
    struct qemu__strxfrm_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRXFRM_L);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.len = len;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strxfrm_l(struct qemu_syscall *call)
{
    struct qemu__strxfrm_l *c = (struct qemu__strxfrm_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strxfrm_l(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->len, QEMU_G2H(c->locale));
}

#endif

struct qemu_strxfrm
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_strxfrm(char *dest, const char *src, size_t len)
{
    struct qemu_strxfrm call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRXFRM);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strxfrm(struct qemu_syscall *call)
{
    struct qemu_strxfrm *c = (struct qemu_strxfrm *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strxfrm(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->len);
}

#endif

struct qemu__atoldbl
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__atoldbl(long double *value, const char *str)
{
    struct qemu__atoldbl call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATOLDBL);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atoldbl(struct qemu_syscall *call)
{
    struct qemu__atoldbl *c = (struct qemu__atoldbl *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atoldbl(QEMU_G2H(c->value), QEMU_G2H(c->str));
}

#endif

struct qemu___STRINGTOLD
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t endptr;
    uint64_t str;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

int CDECL __STRINGTOLD(long double *value, char **endptr, const char *str, int flags)
{
    struct qemu___STRINGTOLD call;
    call.super.id = QEMU_SYSCALL_ID(CALL___STRINGTOLD);
    call.value = (ULONG_PTR)value;
    call.endptr = (ULONG_PTR)endptr;
    call.str = (ULONG_PTR)str;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___STRINGTOLD(struct qemu_syscall *call)
{
    struct qemu___STRINGTOLD *c = (struct qemu___STRINGTOLD *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___STRINGTOLD(QEMU_G2H(c->value), QEMU_G2H(c->endptr), QEMU_G2H(c->str), c->flags);
}

#endif

struct qemu_strnlen
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t maxlen;
};

#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_strnlen(const char *s, size_t maxlen)
{
    struct qemu_strnlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNLEN);
    call.s = (ULONG_PTR)s;
    call.maxlen = maxlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strnlen(struct qemu_syscall *call)
{
    struct qemu_strnlen *c = (struct qemu_strnlen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strnlen(QEMU_G2H(c->s), c->maxlen);
}

#endif

struct qemu_strtoi64_l
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL MSVCRT_strtoi64_l(const char *nptr, char **endptr, int base, MSVCRT__locale_t locale)
{
    struct qemu_strtoi64_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOI64_L);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoi64_l(struct qemu_syscall *call)
{
    struct qemu_strtoi64_l *c = (struct qemu_strtoi64_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoi64_l(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu_strtoi64
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

__int64 CDECL MSVCRT_strtoi64(const char *nptr, char **endptr, int base)
{
    struct qemu_strtoi64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOI64);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoi64(struct qemu_syscall *call)
{
    struct qemu_strtoi64 *c = (struct qemu_strtoi64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoi64(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu_atoi
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_atoi(const char *str)
{
    struct qemu_atoi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATOI);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_atoi(struct qemu_syscall *call)
{
    struct qemu_atoi *c = (struct qemu_atoi *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_atoi(QEMU_G2H(c->str));
}

#endif

struct qemu__atoll_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

LONGLONG CDECL MSVCRT__atoll_l(const char* str, MSVCRT__locale_t locale)
{
    struct qemu__atoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATOLL_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atoll_l(struct qemu_syscall *call)
{
    struct qemu__atoll_l *c = (struct qemu__atoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atoll_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu_atoll
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

LONGLONG CDECL MSVCRT_atoll(const char* str)
{
    struct qemu_atoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATOLL);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_atoll(struct qemu_syscall *call)
{
    struct qemu_atoll *c = (struct qemu_atoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_atoll(QEMU_G2H(c->str));
}

#endif

struct qemu__strtol_l
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t end;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT__strtol_l(const char* nptr, char** end, int base, MSVCRT__locale_t locale)
{
    struct qemu__strtol_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTOL_L);
    call.nptr = (ULONG_PTR)nptr;
    call.end = (ULONG_PTR)end;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strtol_l(struct qemu_syscall *call)
{
    struct qemu__strtol_l *c = (struct qemu__strtol_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strtol_l(QEMU_G2H(c->nptr), QEMU_G2H(c->end), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu_strtol
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t end;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

LONG CDECL MSVCRT_strtol(const char* nptr, char** end, int base)
{
    struct qemu_strtol call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOL);
    call.nptr = (ULONG_PTR)nptr;
    call.end = (ULONG_PTR)end;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtol(struct qemu_syscall *call)
{
    struct qemu_strtol *c = (struct qemu_strtol *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtol(QEMU_G2H(c->nptr), QEMU_G2H(c->end), c->base);
}

#endif

struct qemu_strtoul_l
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t end;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

ULONG CDECL MSVCRT_strtoul_l(const char* nptr, char** end, int base, MSVCRT__locale_t locale)
{
    struct qemu_strtoul_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOUL_L);
    call.nptr = (ULONG_PTR)nptr;
    call.end = (ULONG_PTR)end;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoul_l(struct qemu_syscall *call)
{
    struct qemu_strtoul_l *c = (struct qemu_strtoul_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoul_l(QEMU_G2H(c->nptr), QEMU_G2H(c->end), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu_strtoul
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t end;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

ULONG CDECL MSVCRT_strtoul(const char* nptr, char** end, int base)
{
    struct qemu_strtoul call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOUL);
    call.nptr = (ULONG_PTR)nptr;
    call.end = (ULONG_PTR)end;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoul(struct qemu_syscall *call)
{
    struct qemu_strtoul *c = (struct qemu_strtoul *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoul(QEMU_G2H(c->nptr), QEMU_G2H(c->end), c->base);
}

#endif

struct qemu_strtoui64_l
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

unsigned __int64 CDECL MSVCRT_strtoui64_l(const char *nptr, char **endptr, int base, MSVCRT__locale_t locale)
{
    struct qemu_strtoui64_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOUI64_L);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoui64_l(struct qemu_syscall *call)
{
    struct qemu_strtoui64_l *c = (struct qemu_strtoui64_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoui64_l(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu_strtoui64
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

unsigned __int64 CDECL MSVCRT_strtoui64(const char *nptr, char **endptr, int base)
{
    struct qemu_strtoui64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOUI64);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoui64(struct qemu_syscall *call)
{
    struct qemu_strtoui64 *c = (struct qemu_strtoui64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoui64(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu__ltoa_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ltoa_s(LONG value, char *str, size_t size, int radix)
{
    struct qemu__ltoa_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LTOA_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ltoa_s(struct qemu_syscall *call)
{
    struct qemu__ltoa_s *c = (struct qemu__ltoa_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ltoa_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__ltow_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ltow_s(LONG value, WCHAR *str, size_t size, int radix)
{
    struct qemu__ltow_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LTOW_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ltow_s(struct qemu_syscall *call)
{
    struct qemu__ltow_s *c = (struct qemu__ltow_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ltow_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__itoa_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__itoa_s(int value, char *str, size_t size, int radix)
{
    struct qemu__itoa_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ITOA_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__itoa_s(struct qemu_syscall *call)
{
    struct qemu__itoa_s *c = (struct qemu__itoa_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__itoa_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__itoa
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

char* CDECL MSVCRT__itoa(int value, char *str, int radix)
{
    struct qemu__itoa call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ITOA);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.radix = radix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__itoa(struct qemu_syscall *call)
{
    struct qemu__itoa *c = (struct qemu__itoa *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__itoa(c->value, QEMU_G2H(c->str), c->radix));
}

#endif

struct qemu__itow_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__itow_s(int value, WCHAR *str, size_t size, int radix)
{
    struct qemu__itow_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ITOW_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__itow_s(struct qemu_syscall *call)
{
    struct qemu__itow_s *c = (struct qemu__itow_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__itow_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__ui64toa_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ui64toa_s(unsigned __int64 value, char *str, size_t size, int radix)
{
    struct qemu__ui64toa_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UI64TOA_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ui64toa_s(struct qemu_syscall *call)
{
    struct qemu__ui64toa_s *c = (struct qemu__ui64toa_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ui64toa_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__ui64tow_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ui64tow_s(unsigned __int64 value, WCHAR *str, size_t size, int radix)
{
    struct qemu__ui64tow_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UI64TOW_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ui64tow_s(struct qemu_syscall *call)
{
    struct qemu__ui64tow_s *c = (struct qemu__ui64tow_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ui64tow_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__ultoa_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ultoa_s(ULONG value, char *str, size_t size, int radix)
{
    struct qemu__ultoa_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ULTOA_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ultoa_s(struct qemu_syscall *call)
{
    struct qemu__ultoa_s *c = (struct qemu__ultoa_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ultoa_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__ultow_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__ultow_s(ULONG value, WCHAR *str, size_t size, int radix)
{
    struct qemu__ultow_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ULTOW_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ultow_s(struct qemu_syscall *call)
{
    struct qemu__ultow_s *c = (struct qemu__ultow_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ultow_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__i64toa_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__i64toa_s(__int64 value, char *str, size_t size, int radix)
{
    struct qemu__i64toa_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__I64TOA_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__i64toa_s(struct qemu_syscall *call)
{
    struct qemu__i64toa_s *c = (struct qemu__i64toa_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__i64toa_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu__i64tow_s
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t size;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__i64tow_s(__int64 value, WCHAR *str, size_t size, int radix)
{
    struct qemu__i64tow_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__I64TOW_S);
    call.value = value;
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.radix = radix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__i64tow_s(struct qemu_syscall *call)
{
    struct qemu__i64tow_s *c = (struct qemu__i64tow_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__i64tow_s(c->value, QEMU_G2H(c->str), c->size, c->radix);
}

#endif

struct qemu_I10_OUTPUT
{
    struct qemu_syscall super;
    uint64_t ld80;
    uint64_t prec;
    uint64_t flag;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_I10_OUTPUT(long double ld80, int prec, int flag, struct _I10_OUTPUT_DATA *data)
{
    struct qemu_I10_OUTPUT call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I10_OUTPUT);
    call.ld80 = ld80;
    call.prec = prec;
    call.flag = flag;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_I10_OUTPUT(struct qemu_syscall *call)
{
    struct qemu_I10_OUTPUT *c = (struct qemu_I10_OUTPUT *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_I10_OUTPUT(c->ld80, c->prec, c->flag, QEMU_G2H(c->data));
}

#endif

/* FIXME: Calling out of the vm for _stricmp is probably a waste of time. */
struct qemu__stricmp
{
    struct qemu_syscall super;
    uint64_t s1, s2;
};

#ifdef QEMU_DLL_GUEST

int __cdecl MSVCRT__stricmp(const char *s1, const char *s2)
{
    struct qemu__stricmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRICMP);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stricmp(struct qemu_syscall *call)
{
    struct qemu__stricmp *c = (struct qemu__stricmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__stricmp(QEMU_G2H(c->s1), QEMU_G2H(c->s2));
}

#endif

struct qemu__strnicmp
{
    struct qemu_syscall super;
    uint64_t s1, s2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strnicmp(const char *s1, const char *s2, size_t count)
{
    struct qemu__strnicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNICMP);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strnicmp(struct qemu_syscall *call)
{
    struct qemu__strnicmp *c = (struct qemu__strnicmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__strnicmp(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->count);
}

#endif

/* FIXME: Calling out of the vm for _strtoui64 is probably a waste of time. */
struct qemu__strtoui64
{
    struct qemu_syscall super;
    uint64_t nptr, endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strtoui64(const char *nptr, char **endptr, int base)
{
    struct qemu__strtoui64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTOUI64);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strtoui64(struct qemu_syscall *call)
{
    struct qemu__strtoui64 *c = (struct qemu__strtoui64 *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__strtoui64(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu_memchr
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t c;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memchr(const void *ptr, int c, size_t n)
{
    struct qemu_memchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCHR);
    call.ptr = (ULONG_PTR)ptr;
    call.c = c;
    call.n = n;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memchr(struct qemu_syscall *call)
{
    struct qemu_memchr *c = (struct qemu_memchr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memchr(QEMU_G2H(c->ptr), c->c, c->n));
}

#endif

/* FIXME: Calling out of the vm for memcmp is probably a waste of time. */
struct qemu_memcmp
{
    struct qemu_syscall super;
    uint64_t ptr1, ptr2;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
    struct qemu_memcmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCMP);
    call.ptr1 = (ULONG_PTR)ptr1;
    call.ptr2 = (ULONG_PTR)ptr2;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_memcmp(struct qemu_syscall *call)
{
    struct qemu_memcmp *c = (struct qemu_memcmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memcmp(QEMU_G2H(c->ptr1), QEMU_G2H(c->ptr2), c->size));
}

#endif

/* FIXME: Calling out of the vm for memset is probably a waste of time. */
struct qemu_memset
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t c;
    uint64_t size;
};


#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memset(void *ptr,int c,size_t size)
{
    struct qemu_memset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMSET);
    call.ptr = (ULONG_PTR)ptr;
    call.c = c;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memset(struct qemu_syscall *call)
{
    struct qemu_memset *c = (struct qemu_memset *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memset(QEMU_G2H(c->ptr), c->c, c->size));
}

#endif

/* FIXME: Calling out of the vm for memcpy and memmove is probably a waste of time. */
struct qemu_memcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size)
{
    struct qemu_memcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

void * CDECL MSVCRT_memmove(void *dst, const void *src, size_t size)
{
    struct qemu_memcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMMOVE);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memmove(struct qemu_syscall *call)
{
    struct qemu_memcpy *c = (struct qemu_memcpy *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memmove(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->size));
}

void qemu_memcpy(struct qemu_syscall *call)
{
    struct qemu_memcpy *c = (struct qemu_memcpy *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->size));
}

#endif

struct qemu_strchr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
};


#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strchr(const char *str, int c)
{
    struct qemu_strchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHR);
    call.str = (ULONG_PTR)str;
    call.c = c;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strchr(struct qemu_syscall *call)
{
    struct qemu_strchr *c = (struct qemu_strchr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strchr(QEMU_G2H(c->str), c->c));
}

#endif

struct qemu_strcmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};


#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strcmp(const char *str1, const char *str2)
{
    struct qemu_strcmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strcmp(struct qemu_syscall *call)
{
    struct qemu_strcmp *c = (struct qemu_strcmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strcmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2)));
}

#endif

struct qemu_strlen
{
    struct qemu_syscall super;
    uint64_t str;
};


#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_strlen(const char *str)
{
    struct qemu_strlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRLEN);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strlen(struct qemu_syscall *call)
{
    struct qemu_strlen *c = (struct qemu_strlen *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_strlen(QEMU_G2H(c->str));
}

#endif

/* FIXME: Calling out of the vm for strncmp is probably a waste of time. */
struct qemu_strncmp
{
    struct qemu_syscall super;
    uint64_t str1, str2;
    uint64_t len;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strncmp(const char *str1, const char *str2, size_t len)
{
    struct qemu_strncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strncmp(struct qemu_syscall *call)
{
    struct qemu_strncmp *c = (struct qemu_strncmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_strncmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len);
}

#endif

struct qemu_strncpy
{
    struct qemu_syscall super;
    uint64_t dst, src;
    uint64_t len;
};


#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strncpy(char *dst, const char *src, size_t len)
{
    struct qemu_strncpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.len = len;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strncpy(struct qemu_syscall *call)
{
    struct qemu_strncpy *c = (struct qemu_strncpy *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strncpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->len));
}

#endif

struct qemu_strrchr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
};


#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strrchr(const char *str, int c)
{
    struct qemu_strrchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRCHR);
    call.str = (ULONG_PTR)str;
    call.c = c;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strrchr(struct qemu_syscall *call)
{
    struct qemu_strrchr *c = (struct qemu_strrchr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)p_strrchr(QEMU_G2H(c->str), c->c);
}

#endif

struct qemu_strstr
{
    struct qemu_syscall super;
    uint64_t haystack, needle;
};


#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT_strstr(const char *haystack, const char *needle)
{
    struct qemu_strstr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTR);
    call.haystack = (ULONG_PTR)haystack;
    call.needle = (ULONG_PTR)needle;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strstr(struct qemu_syscall *call)
{
    struct qemu_strstr *c = (struct qemu_strstr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strstr(QEMU_G2H(c->haystack), QEMU_G2H(c->needle)));
}

#endif
