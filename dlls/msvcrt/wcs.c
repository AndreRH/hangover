/*
 * Copyright 2017 André Hentschel
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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


struct qemu__get_printf_count_output
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__get_printf_count_output(void)
{
    struct qemu__get_printf_count_output call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_PRINTF_COUNT_OUTPUT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_printf_count_output(struct qemu_syscall *call)
{
    struct qemu__get_printf_count_output *c = (struct qemu__get_printf_count_output *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_printf_count_output();
}

#endif

struct qemu__set_printf_count_output
{
    struct qemu_syscall super;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__set_printf_count_output(int enable)
{
    struct qemu__set_printf_count_output call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_PRINTF_COUNT_OUTPUT);
    call.enable = enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_printf_count_output(struct qemu_syscall *call)
{
    struct qemu__set_printf_count_output *c = (struct qemu__set_printf_count_output *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_printf_count_output(c->enable);
}

#endif

struct qemu__wcsdup
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcsdup(const WCHAR* str)
{
    struct qemu__wcsdup call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSDUP);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcsdup(struct qemu_syscall *call)
{
    struct qemu__wcsdup *c = (struct qemu__wcsdup *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcsdup(QEMU_G2H(c->str)));
}

#endif

struct qemu__wcsicmp_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__wcsicmp_l(const WCHAR *str1, const WCHAR *str2, MSVCRT__locale_t locale)
{
    struct qemu__wcsicmp_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSICMP_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsicmp_l(struct qemu_syscall *call)
{
    struct qemu__wcsicmp_l *c = (struct qemu__wcsicmp_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsicmp_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu__wcsicmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__wcsicmp(const WCHAR* str1, const WCHAR* str2)
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
    struct qemu__wcsicmp *c = (struct qemu__wcsicmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__wcsicmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu__wcsnicmp_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t n;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__wcsnicmp_l(const WCHAR *str1, const WCHAR *str2, INT n, MSVCRT__locale_t locale)
{
    struct qemu__wcsnicmp_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNICMP_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.n = n;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsnicmp_l(struct qemu_syscall *call)
{
    struct qemu__wcsnicmp_l *c = (struct qemu__wcsnicmp_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsnicmp_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->n, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcsnicmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wcsnicmp(const WCHAR *str1, const WCHAR *str2, int count)
{
    struct qemu__wcsnicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNICMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsnicmp(struct qemu_syscall *call)
{
    struct qemu__wcsnicmp *c = (struct qemu__wcsnicmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__wcsnicmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu__wcsicoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcsicoll_l(const WCHAR* str1, const WCHAR* str2, MSVCRT__locale_t locale)
{
    struct qemu__wcsicoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSICOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsicoll_l(struct qemu_syscall *call)
{
    struct qemu__wcsicoll_l *c = (struct qemu__wcsicoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsicoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu__wcsicoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__wcsicoll(const WCHAR* str1, const WCHAR* str2)
{
    struct qemu__wcsicoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSICOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsicoll(struct qemu_syscall *call)
{
    struct qemu__wcsicoll *c = (struct qemu__wcsicoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsicoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu__wcsnicoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcsnicoll_l(const WCHAR* str1, const WCHAR* str2, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__wcsnicoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNICOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsnicoll_l(struct qemu_syscall *call)
{
    struct qemu__wcsnicoll_l *c = (struct qemu__wcsnicoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsnicoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcsnicoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__wcsnicoll(const WCHAR* str1, const WCHAR* str2, size_t count)
{
    struct qemu__wcsnicoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNICOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsnicoll(struct qemu_syscall *call)
{
    struct qemu__wcsnicoll *c = (struct qemu__wcsnicoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsnicoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu__wcsnset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcsnset(WCHAR* str, WCHAR c, size_t n)
{
    struct qemu__wcsnset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNSET);
    call.str = (ULONG_PTR)str;
    call.c = c;
    call.n = n;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcsnset(struct qemu_syscall *call)
{
    struct qemu__wcsnset *c = (struct qemu__wcsnset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcsnset(QEMU_G2H(c->str), c->c, c->n));
}

#endif

struct qemu__wcsrev
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcsrev(WCHAR* str)
{
    struct qemu__wcsrev call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSREV);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcsrev(struct qemu_syscall *call)
{
    struct qemu__wcsrev *c = (struct qemu__wcsrev *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcsrev(QEMU_G2H(c->str)));
}

#endif

struct qemu__wcsset_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t n;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcsset_s(WCHAR *str, size_t n, WCHAR c)
{
    struct qemu__wcsset_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSSET_S);
    call.str = (ULONG_PTR)str;
    call.n = n;
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsset_s(struct qemu_syscall *call)
{
    struct qemu__wcsset_s *c = (struct qemu__wcsset_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsset_s(QEMU_G2H(c->str), c->n, c->c);
}

#endif

struct qemu__wcsset
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcsset(WCHAR* str, WCHAR c)
{
    struct qemu__wcsset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSSET);
    call.str = (ULONG_PTR)str;
    call.c = c;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcsset(struct qemu_syscall *call)
{
    struct qemu__wcsset *c = (struct qemu__wcsset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcsset(QEMU_G2H(c->str), c->c));
}

#endif

struct qemu__wcsupr_s_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t n;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcsupr_s_l(WCHAR* str, size_t n, MSVCRT__locale_t locale)
{
    struct qemu__wcsupr_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSUPR_S_L);
    call.str = (ULONG_PTR)str;
    call.n = n;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsupr_s_l(struct qemu_syscall *call)
{
    struct qemu__wcsupr_s_l *c = (struct qemu__wcsupr_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsupr_s_l(QEMU_G2H(c->str), c->n, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcsupr_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__wcsupr_s(WCHAR* str, size_t n)
{
    struct qemu__wcsupr_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSUPR_S);
    call.str = (ULONG_PTR)str;
    call.n = n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsupr_s(struct qemu_syscall *call)
{
    struct qemu__wcsupr_s *c = (struct qemu__wcsupr_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsupr_s(QEMU_G2H(c->str), c->n);
}

#endif

struct qemu__wcsupr_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcsupr_l(WCHAR *str, MSVCRT__locale_t locale)
{
    struct qemu__wcsupr_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSUPR_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcsupr_l(struct qemu_syscall *call)
{
    struct qemu__wcsupr_l *c = (struct qemu__wcsupr_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcsupr_l(QEMU_G2H(c->str), QEMU_G2H(c->locale)));
}

#endif

struct qemu__wcslwr_s_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t n;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcslwr_s_l(WCHAR* str, size_t n, MSVCRT__locale_t locale)
{
    struct qemu__wcslwr_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSLWR_S_L);
    call.str = (ULONG_PTR)str;
    call.n = n;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcslwr_s_l(struct qemu_syscall *call)
{
    struct qemu__wcslwr_s_l *c = (struct qemu__wcslwr_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcslwr_s_l(QEMU_G2H(c->str), c->n, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcslwr_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcslwr_s(WCHAR* str, size_t n)
{
    struct qemu__wcslwr_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSLWR_S);
    call.str = (ULONG_PTR)str;
    call.n = n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcslwr_s(struct qemu_syscall *call)
{
    struct qemu__wcslwr_s *c = (struct qemu__wcslwr_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcslwr_s(QEMU_G2H(c->str), c->n);
}

#endif

struct qemu__wcslwr_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcslwr_l(WCHAR* str, MSVCRT__locale_t locale)
{
    struct qemu__wcslwr_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSLWR_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcslwr_l(struct qemu_syscall *call)
{
    struct qemu__wcslwr_l *c = (struct qemu__wcslwr_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcslwr_l(QEMU_G2H(c->str), QEMU_G2H(c->locale)));
}

#endif

struct qemu__wcslwr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wcslwr(WCHAR* str)
{
    struct qemu__wcslwr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSLWR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wcslwr(struct qemu_syscall *call)
{
    struct qemu__wcslwr *c = (struct qemu__wcslwr *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wcslwr(QEMU_G2H(c->str)));
}

#endif

struct qemu__wcsncoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcsncoll_l(const WCHAR* str1, const WCHAR* str2, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__wcsncoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNCOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsncoll_l(struct qemu_syscall *call)
{
    struct qemu__wcsncoll_l *c = (struct qemu__wcsncoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsncoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcsncoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcsncoll(const WCHAR* str1, const WCHAR* str2, size_t count)
{
    struct qemu__wcsncoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSNCOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsncoll(struct qemu_syscall *call)
{
    struct qemu__wcsncoll *c = (struct qemu__wcsncoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsncoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu__wcstod_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__wcstod_l(const WCHAR* str, WCHAR** end, MSVCRT__locale_t locale)
{
    struct qemu__wcstod_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOD_L);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstod_l(struct qemu_syscall *call)
{
    struct qemu__wcstod_l *c = (struct qemu__wcstod_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstod_l(QEMU_G2H(c->str), QEMU_G2H(c->end), QEMU_G2H(c->locale));
}

#endif

struct qemu__wcstombs_l
{
    struct qemu_syscall super;
    uint64_t mbstr;
    uint64_t wcstr;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT__wcstombs_l(char *mbstr, const WCHAR *wcstr, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__wcstombs_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOMBS_L);
    call.mbstr = (ULONG_PTR)mbstr;
    call.wcstr = (ULONG_PTR)wcstr;
    call.count = count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstombs_l(struct qemu_syscall *call)
{
    struct qemu__wcstombs_l *c = (struct qemu__wcstombs_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstombs_l(QEMU_G2H(c->mbstr), QEMU_G2H(c->wcstr), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu_wcstombs
{
    struct qemu_syscall super;
    uint64_t mbstr;
    uint64_t wcstr;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_wcstombs(char *mbstr, const WCHAR *wcstr, size_t count)
{
    struct qemu_wcstombs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOMBS);
    call.mbstr = (ULONG_PTR)mbstr;
    call.wcstr = (ULONG_PTR)wcstr;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcstombs(struct qemu_syscall *call)
{
    struct qemu_wcstombs *c = (struct qemu_wcstombs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcstombs(QEMU_G2H(c->mbstr), QEMU_G2H(c->wcstr), c->count);
}

#endif

struct qemu_wcsrtombs
{
    struct qemu_syscall super;
    uint64_t mbstr;
    uint64_t wcstr;
    uint64_t count;
    uint64_t mbstate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_wcsrtombs(char *mbstr, const WCHAR **wcstr, size_t count, MSVCRT_mbstate_t *mbstate)
{
    struct qemu_wcsrtombs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSRTOMBS);
    call.mbstr = (ULONG_PTR)mbstr;
    call.wcstr = (ULONG_PTR)wcstr;
    call.count = count;
    call.mbstate = (ULONG_PTR)mbstate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsrtombs(struct qemu_syscall *call)
{
    struct qemu_wcsrtombs *c = (struct qemu_wcsrtombs *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsrtombs(QEMU_G2H(c->mbstr), QEMU_G2H(c->wcstr), c->count, QEMU_G2H(c->mbstate));
}

#endif

struct qemu__wcstombs_s_l
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t mbstr;
    uint64_t size;
    uint64_t wcstr;
    uint64_t count;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcstombs_s_l(size_t *ret, char *mbstr, size_t size, const WCHAR *wcstr, size_t count, MSVCRT__locale_t locale)
{
    struct qemu__wcstombs_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOMBS_S_L);
    call.ret = (ULONG_PTR)ret;
    call.mbstr = (ULONG_PTR)mbstr;
    call.size = size;
    call.wcstr = (ULONG_PTR)wcstr;
    call.count = count;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstombs_s_l(struct qemu_syscall *call)
{
    struct qemu__wcstombs_s_l *c = (struct qemu__wcstombs_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstombs_s_l(QEMU_G2H(c->ret), QEMU_G2H(c->mbstr), c->size, QEMU_G2H(c->wcstr), c->count, QEMU_G2H(c->locale));
}

#endif

struct qemu_wcstombs_s
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t mbstr;
    uint64_t size;
    uint64_t wcstr;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_wcstombs_s(size_t *ret, char *mbstr, size_t size, const WCHAR *wcstr, size_t count)
{
    struct qemu_wcstombs_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOMBS_S);
    call.ret = (ULONG_PTR)ret;
    call.mbstr = (ULONG_PTR)mbstr;
    call.size = size;
    call.wcstr = (ULONG_PTR)wcstr;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcstombs_s(struct qemu_syscall *call)
{
    struct qemu_wcstombs_s *c = (struct qemu_wcstombs_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcstombs_s(QEMU_G2H(c->ret), QEMU_G2H(c->mbstr), c->size, QEMU_G2H(c->wcstr), c->count);
}

#endif

struct qemu_wcsrtombs_s
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t mbstr;
    uint64_t size;
    uint64_t wcstr;
    uint64_t count;
    uint64_t mbstate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_wcsrtombs_s(size_t *ret, char *mbstr, size_t size, const WCHAR **wcstr, size_t count, MSVCRT_mbstate_t *mbstate)
{
    struct qemu_wcsrtombs_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSRTOMBS_S);
    call.ret = (ULONG_PTR)ret;
    call.mbstr = (ULONG_PTR)mbstr;
    call.size = size;
    call.wcstr = (ULONG_PTR)wcstr;
    call.count = count;
    call.mbstate = (ULONG_PTR)mbstate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsrtombs_s(struct qemu_syscall *call)
{
    struct qemu_wcsrtombs_s *c = (struct qemu_wcsrtombs_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsrtombs_s(QEMU_G2H(c->ret), QEMU_G2H(c->mbstr), c->size, QEMU_G2H(c->wcstr), c->count, QEMU_G2H(c->mbstate));
}

#endif

struct qemu_wcstod
{
    struct qemu_syscall super;
    uint64_t str, end;
};

#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_wcstod(const WCHAR *str, WCHAR **end)
{
    struct qemu_wcstod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOD);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;

    qemu_syscall(&call.super);
    if (end)
        *end = (WCHAR *)(ULONG_PTR)call.end;

    return call.super.dret;
}

#else

void qemu_wcstod(struct qemu_syscall *call)
{
    struct qemu_wcstod *c = (struct qemu_wcstod *)(ULONG_PTR)call;
    WCHAR *end;
    WINE_TRACE("\n");

    c->super.dret = p_wcstod(QEMU_G2H(c->str), &end);
    c->end = QEMU_H2G(end);
}

#endif

struct qemu__wtof
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wtof(const WCHAR *str)
{
    struct qemu__wtof call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOF);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu__wtof(struct qemu_syscall *call)
{
    struct qemu__wtof *c = (struct qemu__wtof *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.dret = p__wtof(QEMU_G2H(c->str));
}

#endif

struct qemu__wtof_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__wtof_l(const WCHAR *str, MSVCRT__locale_t locale)
{
    struct qemu__wtof_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOF_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtof_l(struct qemu_syscall *call)
{
    struct qemu__wtof_l *c = (struct qemu__wtof_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtof_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__wcstof_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT__wcstof_l(const WCHAR *str, WCHAR **end, MSVCRT__locale_t locale)
{
    struct qemu__wcstof_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOF_L);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstof_l(struct qemu_syscall *call)
{
    struct qemu__wcstof_l *c = (struct qemu__wcstof_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstof_l(QEMU_G2H(c->str), QEMU_G2H(c->end), QEMU_G2H(c->locale));
}

#endif

struct qemu_wcstof
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t end;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI float CDECL MSVCRT_wcstof(const WCHAR *str, WCHAR **end)
{
    struct qemu_wcstof call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOF);
    call.str = (ULONG_PTR)str;
    call.end = (ULONG_PTR)end;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcstof(struct qemu_syscall *call)
{
    struct qemu_wcstof *c = (struct qemu_wcstof *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcstof(QEMU_G2H(c->str), QEMU_G2H(c->end));
}

#endif

struct qemu__wcscoll_l
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wcscoll_l(const WCHAR* str1, const WCHAR* str2, MSVCRT__locale_t locale)
{
    struct qemu__wcscoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSCOLL_L);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcscoll_l(struct qemu_syscall *call)
{
    struct qemu__wcscoll_l *c = (struct qemu__wcscoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcscoll_l(QEMU_G2H(c->str1), QEMU_G2H(c->str2), QEMU_G2H(c->locale));
}

#endif

struct qemu_wcscoll
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_wcscoll(const WCHAR* str1, const WCHAR* str2)
{
    struct qemu_wcscoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCOLL);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscoll(struct qemu_syscall *call)
{
    struct qemu_wcscoll *c = (struct qemu_wcscoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcscoll(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_wcspbrk
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t accept;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT_wcspbrk(const WCHAR* str, const WCHAR* accept)
{
    struct qemu_wcspbrk call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSPBRK);
    call.str = (ULONG_PTR)str;
    call.accept = (ULONG_PTR)accept;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcspbrk(struct qemu_syscall *call)
{
    struct qemu_wcspbrk *c = (struct qemu_wcspbrk *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcspbrk(QEMU_G2H(c->str), QEMU_G2H(c->accept)));
}

#endif

struct qemu_wcstok_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
    uint64_t next_token;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * CDECL MSVCRT_wcstok_s(WCHAR *str, const WCHAR *delim, WCHAR **next_token)
{
    struct qemu_wcstok_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOK_S);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;
    call.next_token = (ULONG_PTR)next_token;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcstok_s(struct qemu_syscall *call)
{
    struct qemu_wcstok_s *c = (struct qemu_wcstok_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_wcstok_s(QEMU_G2H(c->str), QEMU_G2H(c->delim), QEMU_G2H(c->next_token)));
}

#endif

struct qemu_wcstok
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t delim;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * CDECL MSVCRT_wcstok(WCHAR *str, const WCHAR *delim)
{
    struct qemu_wcstok call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOK);
    call.str = (ULONG_PTR)str;
    call.delim = (ULONG_PTR)delim;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcstok(struct qemu_syscall *call)
{
    struct qemu_wcstok *c = (struct qemu_wcstok *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcstok(QEMU_G2H(c->str), QEMU_G2H(c->delim)));
}

#endif

struct qemu__wctomb_s_l
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t mbchar;
    uint64_t size;
    uint64_t wch;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wctomb_s_l(int *len, char *mbchar, size_t size, WCHAR wch, MSVCRT__locale_t locale)
{
    struct qemu__wctomb_s_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTOMB_S_L);
    call.len = (ULONG_PTR)len;
    call.mbchar = (ULONG_PTR)mbchar;
    call.size = size;
    call.wch = wch;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wctomb_s_l(struct qemu_syscall *call)
{
    struct qemu__wctomb_s_l *c = (struct qemu__wctomb_s_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wctomb_s_l(QEMU_G2H(c->len), QEMU_G2H(c->mbchar), c->size, c->wch, QEMU_G2H(c->locale));
}

#endif

struct qemu_wctomb_s
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t mbchar;
    uint64_t size;
    uint64_t wch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_wctomb_s(int *len, char *mbchar, size_t size, WCHAR wch)
{
    struct qemu_wctomb_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCTOMB_S);
    call.len = (ULONG_PTR)len;
    call.mbchar = (ULONG_PTR)mbchar;
    call.size = size;
    call.wch = wch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wctomb_s(struct qemu_syscall *call)
{
    struct qemu_wctomb_s *c = (struct qemu_wctomb_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wctomb_s(QEMU_G2H(c->len), QEMU_G2H(c->mbchar), c->size, c->wch);
}

#endif

struct qemu__wctomb_l
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t ch;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wctomb_l(char *dst, WCHAR ch, MSVCRT__locale_t locale)
{
    struct qemu__wctomb_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTOMB_L);
    call.dst = (ULONG_PTR)dst;
    call.ch = ch;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wctomb_l(struct qemu_syscall *call)
{
    struct qemu__wctomb_l *c = (struct qemu__wctomb_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wctomb_l(QEMU_G2H(c->dst), c->ch, QEMU_G2H(c->locale));
}

#endif

struct qemu_wctomb
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_wctomb(char *dst, WCHAR ch)
{
    struct qemu_wctomb call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCTOMB);
    call.dst = (ULONG_PTR)dst;
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wctomb(struct qemu_syscall *call)
{
    struct qemu_wctomb *c = (struct qemu_wctomb *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wctomb(QEMU_G2H(c->dst), c->ch);
}

#endif

struct qemu_wctob
{
    struct qemu_syscall super;
    uint64_t wchar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_wctob(MSVCRT_wint_t wchar)
{
    struct qemu_wctob call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCTOB);
    call.wchar = wchar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wctob(struct qemu_syscall *call)
{
    struct qemu_wctob *c = (struct qemu_wctob *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wctob(c->wchar);
}

#endif

struct qemu_wcrtomb
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t ch;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_wcrtomb(char *dst, WCHAR ch, MSVCRT_mbstate_t *s)
{
    struct qemu_wcrtomb call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCRTOMB);
    call.dst = (ULONG_PTR)dst;
    call.ch = ch;
    call.s = (ULONG_PTR)s;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcrtomb(struct qemu_syscall *call)
{
    struct qemu_wcrtomb *c = (struct qemu_wcrtomb *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcrtomb(QEMU_G2H(c->dst), c->ch, QEMU_G2H(c->s));
}

#endif

struct qemu_iswalnum
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswalnum(WCHAR wc)
{
    struct qemu_iswalnum call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWALNUM);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswalnum(struct qemu_syscall *call)
{
    struct qemu_iswalnum *c = (struct qemu_iswalnum *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswalnum(c->wc);
}

#endif

struct qemu_iswalpha
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswalpha(WCHAR wc)
{
    struct qemu_iswalpha call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWALPHA);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswalpha(struct qemu_syscall *call)
{
    struct qemu_iswalpha *c = (struct qemu_iswalpha *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswalpha(c->wc);
}

#endif

struct qemu__iswalpha_l
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__iswalpha_l(WCHAR wc, MSVCRT__locale_t locale)
{
    struct qemu__iswalpha_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISWALPHA_L);
    call.wc = wc;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iswalpha_l(struct qemu_syscall *call)
{
    struct qemu__iswalpha_l *c = (struct qemu__iswalpha_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iswalpha_l(c->wc, QEMU_G2H(c->locale));
}

#endif

struct qemu_iswcntrl
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswcntrl(WCHAR wc)
{
    struct qemu_iswcntrl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWCNTRL);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswcntrl(struct qemu_syscall *call)
{
    struct qemu_iswcntrl *c = (struct qemu_iswcntrl *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswcntrl(c->wc);
}

#endif

struct qemu_iswdigit
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswdigit(WCHAR wc)
{
    struct qemu_iswdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWDIGIT);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswdigit(struct qemu_syscall *call)
{
    struct qemu_iswdigit *c = (struct qemu_iswdigit *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswdigit(c->wc);
}

#endif

struct qemu__iswdigit_l
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__iswdigit_l(WCHAR wc, MSVCRT__locale_t locale)
{
    struct qemu__iswdigit_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISWDIGIT_L);
    call.wc = wc;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iswdigit_l(struct qemu_syscall *call)
{
    struct qemu__iswdigit_l *c = (struct qemu__iswdigit_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iswdigit_l(c->wc, QEMU_G2H(c->locale));
}

#endif

struct qemu_iswgraph
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswgraph(WCHAR wc)
{
    struct qemu_iswgraph call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWGRAPH);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswgraph(struct qemu_syscall *call)
{
    struct qemu_iswgraph *c = (struct qemu_iswgraph *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswgraph(c->wc);
}

#endif

struct qemu_iswlower
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswlower(WCHAR wc)
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
    struct qemu_iswlower *c = (struct qemu_iswlower *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswlower(c->wc);
}

#endif

struct qemu_iswprint
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswprint(WCHAR wc)
{
    struct qemu_iswprint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWPRINT);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswprint(struct qemu_syscall *call)
{
    struct qemu_iswprint *c = (struct qemu_iswprint *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswprint(c->wc);
}

#endif

struct qemu__iswpunct_l
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__iswpunct_l(WCHAR wc, MSVCRT__locale_t locale)
{
    struct qemu__iswpunct_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISWPUNCT_L);
    call.wc = wc;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iswpunct_l(struct qemu_syscall *call)
{
    struct qemu__iswpunct_l *c = (struct qemu__iswpunct_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iswpunct_l(c->wc, QEMU_G2H(c->locale));
}

#endif

struct qemu_iswpunct
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswpunct(WCHAR wc)
{
    struct qemu_iswpunct call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWPUNCT);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswpunct(struct qemu_syscall *call)
{
    struct qemu_iswpunct *c = (struct qemu_iswpunct *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswpunct(c->wc);
}

#endif

struct qemu__iswspace_l
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__iswspace_l(WCHAR wc, MSVCRT__locale_t locale)
{
    struct qemu__iswspace_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISWSPACE_L);
    call.wc = wc;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iswspace_l(struct qemu_syscall *call)
{
    struct qemu__iswspace_l *c = (struct qemu__iswspace_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iswspace_l(c->wc, QEMU_G2H(c->locale));
}

#endif

struct qemu_iswspace
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswspace(WCHAR wc)
{
    struct qemu_iswspace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWSPACE);
    call.wc = (ULONG_PTR)wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswspace(struct qemu_syscall *call)
{
    struct qemu_iswspace *c = (struct qemu_iswspace *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_iswspace(c->wc);
}

#endif

struct qemu_iswupper
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswupper(WCHAR wc)
{
    struct qemu_iswupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWUPPER);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswupper(struct qemu_syscall *call)
{
    struct qemu_iswupper *c = (struct qemu_iswupper *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswupper(c->wc);
}

#endif

struct qemu_iswxdigit
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswxdigit(WCHAR wc)
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
    struct qemu_iswxdigit *c = (struct qemu_iswxdigit *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswxdigit(c->wc);
}

#endif

struct qemu__iswctype_l
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t type;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__iswctype_l(WCHAR wc, MSVCRT_wctype_t type, MSVCRT__locale_t locale)
{
    struct qemu__iswctype_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISWCTYPE_L);
    call.wc = wc;
    call.type = type;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iswctype_l(struct qemu_syscall *call)
{
    struct qemu__iswctype_l *c = (struct qemu__iswctype_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iswctype_l(c->wc, c->type, QEMU_G2H(c->locale));
}

#endif

struct qemu__iswblank_l
{
    struct qemu_syscall super;
    uint64_t wc;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT__iswblank_l(WCHAR wc, MSVCRT__locale_t locale)
{
    struct qemu__iswblank_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ISWBLANK_L);
    call.wc = wc;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__iswblank_l(struct qemu_syscall *call)
{
    struct qemu__iswblank_l *c = (struct qemu__iswblank_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__iswblank_l(c->wc, QEMU_G2H(c->locale));
}

#endif

struct qemu_iswblank
{
    struct qemu_syscall super;
    uint64_t wc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_iswblank(WCHAR wc)
{
    struct qemu_iswblank call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWBLANK);
    call.wc = wc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iswblank(struct qemu_syscall *call)
{
    struct qemu_iswblank *c = (struct qemu_iswblank *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iswblank(c->wc);
}

#endif

struct qemu_wcscpy_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t size;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_wcscpy_s(WCHAR *dst, size_t size, const WCHAR *src)
{
    struct qemu_wcscpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCPY_S);
    call.dst = (ULONG_PTR)dst;
    call.size = size;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscpy_s(struct qemu_syscall *call)
{
    struct qemu_wcscpy_s *c = (struct qemu_wcscpy_s *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcscpy_s(QEMU_G2H(c->dst), c->size, QEMU_G2H(c->src));
}

#endif

struct qemu_wcsncpy_s
{
    struct qemu_syscall super;
    uint64_t wcDest;
    uint64_t numElement;
    uint64_t wcSrc;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_wcsncpy_s(WCHAR* wcDest, size_t numElement, const WCHAR *wcSrc, size_t count)
{
    struct qemu_wcsncpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCPY_S);
    call.wcDest = (ULONG_PTR)wcDest;
    call.numElement = numElement;
    call.wcSrc = (ULONG_PTR)wcSrc;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsncpy_s(struct qemu_syscall *call)
{
    struct qemu_wcsncpy_s *c = (struct qemu_wcsncpy_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsncpy_s(QEMU_G2H(c->wcDest), c->numElement, QEMU_G2H(c->wcSrc), c->count);
}

#endif

struct qemu_wcscat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t count;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

INT CDECL MSVCRT_wcscat_s(WCHAR *dst, size_t count, const WCHAR *src)
{
    struct qemu_wcscat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCAT_S);
    call.dst = (ULONG_PTR)dst;
    call.count = count;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcscat_s(struct qemu_syscall *call)
{
    struct qemu_wcscat_s *c = (struct qemu_wcscat_s *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcscat_s(QEMU_G2H(c->dst), c->count, QEMU_G2H(c->src));
}

#endif

struct qemu_wcsncat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t elem;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL MSVCRT_wcsncat_s(WCHAR *dst, size_t elem, const WCHAR *src, size_t count)
{
    struct qemu_wcsncat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCAT_S);
    call.dst = (ULONG_PTR)dst;
    call.elem = elem;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsncat_s(struct qemu_syscall *call)
{
    struct qemu_wcsncat_s *c = (struct qemu_wcsncat_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsncat_s(QEMU_G2H(c->dst), c->elem, QEMU_G2H(c->src), c->count);
}

#endif

struct qemu__wcstoi64_l
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI __int64 CDECL MSVCRT__wcstoi64_l(const WCHAR *nptr, WCHAR **endptr, int base, MSVCRT__locale_t locale)
{
    struct qemu__wcstoi64_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOI64_L);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstoi64_l(struct qemu_syscall *call)
{
    struct qemu__wcstoi64_l *c = (struct qemu__wcstoi64_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstoi64_l(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcstoi64
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI __int64 CDECL MSVCRT__wcstoi64(const WCHAR *nptr, WCHAR **endptr, int base)
{
    struct qemu__wcstoi64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOI64);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstoi64(struct qemu_syscall *call)
{
    struct qemu__wcstoi64 *c = (struct qemu__wcstoi64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstoi64(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu__wcstol_l
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t end;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL MSVCRT__wcstol_l(const WCHAR *s, WCHAR **end, int base, MSVCRT__locale_t locale)
{
    struct qemu__wcstol_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOL_L);
    call.s = (ULONG_PTR)s;
    call.end = (ULONG_PTR)end;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstol_l(struct qemu_syscall *call)
{
    struct qemu__wcstol_l *c = (struct qemu__wcstol_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstol_l(QEMU_G2H(c->s), QEMU_G2H(c->end), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcstoui64_l
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned __int64 CDECL MSVCRT__wcstoui64_l(const WCHAR *nptr, WCHAR **endptr, int base, MSVCRT__locale_t locale)
{
    struct qemu__wcstoui64_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOUI64_L);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstoui64_l(struct qemu_syscall *call)
{
    struct qemu__wcstoui64_l *c = (struct qemu__wcstoui64_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstoui64_l(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base, QEMU_G2H(c->locale));
}

#endif

struct qemu__wcstoui64
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned __int64 CDECL MSVCRT__wcstoui64(const WCHAR *nptr, WCHAR **endptr, int base)
{
    struct qemu__wcstoui64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOUI64);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstoui64(struct qemu_syscall *call)
{
    struct qemu__wcstoui64 *c = (struct qemu__wcstoui64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstoui64(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu_wcsnlen
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t maxlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_wcsnlen(const WCHAR *s, size_t maxlen)
{
    struct qemu_wcsnlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNLEN);
    call.s = (ULONG_PTR)s;
    call.maxlen = maxlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsnlen(struct qemu_syscall *call)
{
    struct qemu_wcsnlen *c = (struct qemu_wcsnlen *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsnlen(QEMU_G2H(c->s), c->maxlen);
}

#endif

struct qemu__towupper_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__towupper_l(MSVCRT_wint_t c, MSVCRT__locale_t locale)
{
    struct qemu__towupper_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOWUPPER_L);
    call.c = c;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__towupper_l(struct qemu_syscall *call)
{
    struct qemu__towupper_l *c = (struct qemu__towupper_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__towupper_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_towupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_towupper(MSVCRT_wint_t c)
{
    struct qemu_towupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOWUPPER);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_towupper(struct qemu_syscall *call)
{
    struct qemu_towupper *c = (struct qemu_towupper *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_towupper(c->c);
}

#endif

struct qemu__towlower_l
{
    struct qemu_syscall super;
    uint64_t c;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__towlower_l(MSVCRT_wint_t c, MSVCRT__locale_t locale)
{
    struct qemu__towlower_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOWLOWER_L);
    call.c = c;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__towlower_l(struct qemu_syscall *call)
{
    struct qemu__towlower_l *c = (struct qemu__towlower_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__towlower_l(c->c, QEMU_G2H(c->locale));
}

#endif

struct qemu_towlower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_towlower(MSVCRT_wint_t c)
{
    struct qemu_towlower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOWLOWER);
    call.c = c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_towlower(struct qemu_syscall *call)
{
    struct qemu_towlower *c = (struct qemu_towlower *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_towlower(c->c);
}

#endif

struct qemu_wcschr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT_wcschr(const WCHAR *str, WCHAR ch)
{
    struct qemu_wcschr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCHR);
    call.str = (ULONG_PTR)str;
    call.ch = ch;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcschr(struct qemu_syscall *call)
{
    struct qemu_wcschr *c = (struct qemu_wcschr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcschr(QEMU_G2H(c->str), c->ch));
}

#endif

struct qemu_wcslen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_wcslen(const WCHAR *str)
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
    struct qemu_wcslen *c = (struct qemu_wcslen *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcslen(QEMU_G2H(c->str));
}

#endif

struct qemu_wcsstr
{
    struct qemu_syscall super;
    uint64_t str, sub;
};

#ifdef QEMU_DLL_GUEST

const WCHAR * __cdecl MSVCRT_wcsstr(const WCHAR *str, const WCHAR *sub)
{
    struct qemu_wcsstr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSSTR);
    call.str = (ULONG_PTR)str;
    call.sub = (ULONG_PTR)sub;

    qemu_syscall(&call.super);

    return (const wchar_t *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcsstr(struct qemu_syscall *call)
{
    struct qemu_wcsstr *c = (struct qemu_wcsstr *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcsstr(QEMU_G2H(c->str), QEMU_G2H(c->sub)));
}

#endif

struct qemu__wtoi64_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI __int64 CDECL MSVCRT__wtoi64_l(const WCHAR *str, MSVCRT__locale_t locale)
{
    struct qemu__wtoi64_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOI64_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtoi64_l(struct qemu_syscall *call)
{
    struct qemu__wtoi64_l *c = (struct qemu__wtoi64_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoi64_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__wtoi64
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI __int64 CDECL MSVCRT__wtoi64(const WCHAR *str)
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
    struct qemu__wtoi64 *c = (struct qemu__wtoi64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoi64(QEMU_G2H(c->str));
}

#endif

struct qemu_wcsncmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_wcsncmp(const wchar_t *str1, const wchar_t *str2, size_t count)
{
    struct qemu_wcsncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsncmp(struct qemu_syscall *call)
{
    struct qemu_wcsncmp *c = (struct qemu_wcsncmp *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p_wcsncmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->count);
}

#endif

struct qemu__wcsxfrm_l
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t len;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT__wcsxfrm_l(WCHAR *dest, const WCHAR *src, size_t len, MSVCRT__locale_t locale)
{
    struct qemu__wcsxfrm_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSXFRM_L);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.len = len;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsxfrm_l(struct qemu_syscall *call)
{
    struct qemu__wcsxfrm_l *c = (struct qemu__wcsxfrm_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsxfrm_l(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->len, QEMU_G2H(c->locale));
}

#endif

struct qemu_wcsxfrm
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_wcsxfrm(WCHAR *dest, const WCHAR *src, size_t len)
{
    struct qemu_wcsxfrm call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSXFRM);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsxfrm(struct qemu_syscall *call)
{
    struct qemu_wcsxfrm *c = (struct qemu_wcsxfrm *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsxfrm(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->len);
}

#endif

struct qemu__wtoi
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__wtoi(const WCHAR *str)
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
    struct qemu__wtoi *c = (struct qemu__wtoi *)(ULONG_PTR)call;
    WINE_TRACE("\n");

    c->super.iret = p__wtoi(QEMU_G2H(c->str));
}

#endif

struct qemu_wcscpy
{
    struct qemu_syscall super;
    uint64_t dst, src;
};

#ifdef QEMU_DLL_GUEST

WCHAR * CDECL MSVCRT_wcscpy(WCHAR *dst, const WCHAR *src)
{
    struct qemu_wcscpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcscpy(struct qemu_syscall *call)
{
    struct qemu_wcscpy *c = (struct qemu_wcscpy *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcscpy(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
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

WINBASEAPI WCHAR* CDECL MSVCRT_wcsncpy(WCHAR* s1, const WCHAR *s2, size_t n)
{
    struct qemu_wcsncpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSNCPY);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.n = n;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_wcsncpy(struct qemu_syscall *call)
{
    struct qemu_wcsncpy *c = (struct qemu_wcsncpy *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_wcsncpy(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->n));
}

#endif

struct qemu__wtoi_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wtoi_l(const WCHAR *str, MSVCRT__locale_t locale)
{
    struct qemu__wtoi_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOI_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtoi_l(struct qemu_syscall *call)
{
    struct qemu__wtoi_l *c = (struct qemu__wtoi_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoi_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__wtol_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL MSVCRT__wtol_l(const WCHAR *str, MSVCRT__locale_t locale)
{
    struct qemu__wtol_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOL_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtol_l(struct qemu_syscall *call)
{
    struct qemu__wtol_l *c = (struct qemu__wtol_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtol_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__wtol
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL MSVCRT__wtol(const WCHAR *str)
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
    struct qemu__wtol *c = (struct qemu__wtol *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtol(QEMU_G2H(c->str));
}

#endif

struct qemu__wtoll_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONGLONG CDECL MSVCRT__wtoll_l(const WCHAR *str, MSVCRT__locale_t locale)
{
    struct qemu__wtoll_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOLL_L);
    call.str = (ULONG_PTR)str;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtoll_l(struct qemu_syscall *call)
{
    struct qemu__wtoll_l *c = (struct qemu__wtoll_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoll_l(QEMU_G2H(c->str), QEMU_G2H(c->locale));
}

#endif

struct qemu__wtoll
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONGLONG CDECL MSVCRT__wtoll(const WCHAR *str)
{
    struct qemu__wtoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WTOLL);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wtoll(struct qemu_syscall *call)
{
    struct qemu__wtoll *c = (struct qemu__wtoll *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wtoll(QEMU_G2H(c->str));
}

#endif

struct qemu__wcstoul_l
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t end;
    uint64_t base;
    uint64_t locale;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG CDECL MSVCRT__wcstoul_l(const WCHAR *s, WCHAR **end, int base, MSVCRT__locale_t locale)
{
    struct qemu__wcstoul_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSTOUL_L);
    call.s = (ULONG_PTR)s;
    call.end = (ULONG_PTR)end;
    call.base = base;
    call.locale = (ULONG_PTR)locale;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcstoul_l(struct qemu_syscall *call)
{
    struct qemu__wcstoul_l *c = (struct qemu__wcstoul_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcstoul_l(QEMU_G2H(c->s), QEMU_G2H(c->end), c->base, QEMU_G2H(c->locale));
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

WINBASEAPI ULONG CDECL MSVCRT_wcstoul(const WCHAR *s, WCHAR **end, int base)
{
    struct qemu_wcstoul call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSTOUL);
    call.s = (ULONG_PTR)s;
    call.base = base;

    if (end)
        call.end = (ULONG_PTR)*end;
    qemu_syscall(&call.super);
    if (end)
        *end = (WCHAR *)(ULONG_PTR)call.end;

    return call.super.iret;
}

#else

void qemu_wcstoul(struct qemu_syscall *call)
{
    struct qemu_wcstoul *c = (struct qemu_wcstoul *)(ULONG_PTR)call;
    WCHAR *end;

    WINE_TRACE("\n");
    end = QEMU_G2H(c->end);
    c->super.iret = p_wcstoul(QEMU_G2H(c->s), &end, c->base);
    c->end = QEMU_H2G(end);
}

#endif
