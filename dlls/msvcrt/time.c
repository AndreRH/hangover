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


struct qemu__tzset
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__tzset(void)
{
    struct qemu__tzset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TZSET);

    qemu_syscall(&call.super);
}

#else

void qemu__tzset(struct qemu_syscall *call)
{
    struct qemu__tzset *c = (struct qemu__tzset *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__tzset();
}

#endif

struct qemu__mktime64
{
    struct qemu_syscall super;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time64_t CDECL MSVCRT__mktime64(struct MSVCRT_tm *mstm)
{
    struct qemu__mktime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKTIME64);
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mktime64(struct qemu_syscall *call)
{
    struct qemu__mktime64 *c = (struct qemu__mktime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mktime64(QEMU_G2H(c->mstm));
}

#endif

struct qemu__mktime32
{
    struct qemu_syscall super;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time32_t CDECL MSVCRT__mktime32(struct MSVCRT_tm *mstm)
{
    struct qemu__mktime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKTIME32);
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mktime32(struct qemu_syscall *call)
{
    struct qemu__mktime32 *c = (struct qemu__mktime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mktime32(QEMU_G2H(c->mstm));
}

#endif

struct qemu_mktime
{
    struct qemu_syscall super;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time64_t CDECL MSVCRT_mktime(struct MSVCRT_tm *mstm)
{
    struct qemu_mktime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MKTIME);
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mktime(struct qemu_syscall *call)
{
    struct qemu_mktime *c = (struct qemu_mktime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_mktime(QEMU_G2H(c->mstm));
}

#endif

struct qemu__mkgmtime64
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time64_t CDECL MSVCRT__mkgmtime64(struct MSVCRT_tm *time)
{
    struct qemu__mkgmtime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKGMTIME64);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mkgmtime64(struct qemu_syscall *call)
{
    struct qemu__mkgmtime64 *c = (struct qemu__mkgmtime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mkgmtime64(QEMU_G2H(c->time));
}

#endif

struct qemu__mkgmtime32
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time32_t CDECL MSVCRT__mkgmtime32(struct MSVCRT_tm *time)
{
    struct qemu__mkgmtime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKGMTIME32);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mkgmtime32(struct qemu_syscall *call)
{
    struct qemu__mkgmtime32 *c = (struct qemu__mkgmtime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mkgmtime32(QEMU_G2H(c->time));
}

#endif

struct qemu__mkgmtime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time32_t CDECL MSVCRT__mkgmtime(struct MSVCRT_tm *time)
{
    struct qemu__mkgmtime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MKGMTIME);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__mkgmtime(struct qemu_syscall *call)
{
    struct qemu__mkgmtime *c = (struct qemu__mkgmtime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__mkgmtime(QEMU_G2H(c->time));
}

#endif

struct qemu__localtime64_s
{
    struct qemu_syscall super;
    uint64_t res;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__localtime64_s(struct MSVCRT_tm *res, const MSVCRT___time64_t *secs)
{
    struct qemu__localtime64_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCALTIME64_S);
    call.res = (ULONG_PTR)res;
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__localtime64_s(struct qemu_syscall *call)
{
    struct qemu__localtime64_s *c = (struct qemu__localtime64_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__localtime64_s(QEMU_G2H(c->res), QEMU_G2H(c->secs));
}

#endif

struct qemu__localtime64
{
    struct qemu_syscall super;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_tm* CDECL MSVCRT__localtime64(const MSVCRT___time64_t* secs)
{
    struct qemu__localtime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCALTIME64);
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return (struct MSVCRT_tm *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__localtime64(struct qemu_syscall *call)
{
    struct qemu__localtime64 *c = (struct qemu__localtime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__localtime64(QEMU_G2H(c->secs)));
}

#endif

struct qemu__localtime32
{
    struct qemu_syscall super;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_tm* CDECL MSVCRT__localtime32(const MSVCRT___time32_t* secs)
{
    struct qemu__localtime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCALTIME32);
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return (struct MSVCRT_tm *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__localtime32(struct qemu_syscall *call)
{
    struct qemu__localtime32 *c = (struct qemu__localtime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__localtime32(QEMU_G2H(c->secs)));
}

#endif

struct qemu__localtime32_s
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__localtime32_s(struct MSVCRT_tm *time, const MSVCRT___time32_t *secs)
{
    struct qemu__localtime32_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LOCALTIME32_S);
    call.time = (ULONG_PTR)time;
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__localtime32_s(struct qemu_syscall *call)
{
    struct qemu__localtime32_s *c = (struct qemu__localtime32_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__localtime32_s(QEMU_G2H(c->time), QEMU_G2H(c->secs));
}

#endif

struct qemu_localtime
{
    struct qemu_syscall super;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_tm* CDECL MSVCRT_localtime(const MSVCRT___time64_t* secs)
{
    struct qemu_localtime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALTIME);
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return (struct MSVCRT_tm *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_localtime(struct qemu_syscall *call)
{
    struct qemu_localtime *c = (struct qemu_localtime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_localtime(QEMU_G2H(c->secs)));
}

#endif

struct qemu__gmtime64_s
{
    struct qemu_syscall super;
    uint64_t res;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__gmtime64_s(struct MSVCRT_tm *res, const MSVCRT___time64_t *secs)
{
    struct qemu__gmtime64_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GMTIME64_S);
    call.res = (ULONG_PTR)res;
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__gmtime64_s(struct qemu_syscall *call)
{
    struct qemu__gmtime64_s *c = (struct qemu__gmtime64_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__gmtime64_s(QEMU_G2H(c->res), QEMU_G2H(c->secs));
}

#endif

struct qemu__gmtime64
{
    struct qemu_syscall super;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_tm* CDECL MSVCRT__gmtime64(const MSVCRT___time64_t *secs)
{
    struct qemu__gmtime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GMTIME64);
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return (struct MSVCRT_tm *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__gmtime64(struct qemu_syscall *call)
{
    struct qemu__gmtime64 *c = (struct qemu__gmtime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__gmtime64(QEMU_G2H(c->secs)));
}

#endif

struct qemu__gmtime32_s
{
    struct qemu_syscall super;
    uint64_t res;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__gmtime32_s(struct MSVCRT_tm *res, const MSVCRT___time32_t *secs)
{
    struct qemu__gmtime32_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GMTIME32_S);
    call.res = (ULONG_PTR)res;
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__gmtime32_s(struct qemu_syscall *call)
{
    struct qemu__gmtime32_s *c = (struct qemu__gmtime32_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__gmtime32_s(QEMU_G2H(c->res), QEMU_G2H(c->secs));
}

#endif

struct qemu__gmtime32
{
    struct qemu_syscall super;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_tm* CDECL MSVCRT__gmtime32(const MSVCRT___time32_t* secs)
{
    struct qemu__gmtime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GMTIME32);
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return (struct MSVCRT_tm *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__gmtime32(struct qemu_syscall *call)
{
    struct qemu__gmtime32 *c = (struct qemu__gmtime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__gmtime32(QEMU_G2H(c->secs)));
}

#endif

struct qemu_gmtime
{
    struct qemu_syscall super;
    uint64_t secs;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct MSVCRT_tm* CDECL MSVCRT_gmtime(const MSVCRT___time64_t* secs)
{
    struct qemu_gmtime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GMTIME);
    call.secs = (ULONG_PTR)secs;

    qemu_syscall(&call.super);

    return (struct MSVCRT_tm *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_gmtime(struct qemu_syscall *call)
{
    struct qemu_gmtime *c = (struct qemu_gmtime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_gmtime(QEMU_G2H(c->secs)));
}

#endif

struct qemu__strdate
{
    struct qemu_syscall super;
    uint64_t date;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL MSVCRT__strdate(char* date)
{
    struct qemu__strdate call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRDATE);
    call.date = (ULONG_PTR)date;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strdate(struct qemu_syscall *call)
{
    struct qemu__strdate *c = (struct qemu__strdate *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strdate(QEMU_G2H(c->date)));
}

#endif

struct qemu__strdate_s
{
    struct qemu_syscall super;
    uint64_t date;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _strdate_s(char* date, size_t size)
{
    struct qemu__strdate_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRDATE_S);
    call.date = (ULONG_PTR)date;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strdate_s(struct qemu_syscall *call)
{
    struct qemu__strdate_s *c = (struct qemu__strdate_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strdate_s(QEMU_G2H(c->date), c->size);
}

#endif

struct qemu__wstrdate
{
    struct qemu_syscall super;
    uint64_t date;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wstrdate(WCHAR* date)
{
    struct qemu__wstrdate call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTRDATE);
    call.date = (ULONG_PTR)date;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wstrdate(struct qemu_syscall *call)
{
    struct qemu__wstrdate *c = (struct qemu__wstrdate *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wstrdate(QEMU_G2H(c->date)));
}

#endif

struct qemu__wstrdate_s
{
    struct qemu_syscall super;
    uint64_t date;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _wstrdate_s(WCHAR* date, size_t size)
{
    struct qemu__wstrdate_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTRDATE_S);
    call.date = (ULONG_PTR)date;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstrdate_s(struct qemu_syscall *call)
{
    struct qemu__wstrdate_s *c = (struct qemu__wstrdate_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstrdate_s(QEMU_G2H(c->date), c->size);
}

#endif

struct qemu__strtime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* CDECL MSVCRT__strtime(char* time)
{
    struct qemu__strtime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTIME);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strtime(struct qemu_syscall *call)
{
    struct qemu__strtime *c = (struct qemu__strtime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strtime(QEMU_G2H(c->time)));
}

#endif

struct qemu__strtime_s
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _strtime_s(char* time, size_t size)
{
    struct qemu__strtime_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTIME_S);
    call.time = (ULONG_PTR)time;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strtime_s(struct qemu_syscall *call)
{
    struct qemu__strtime_s *c = (struct qemu__strtime_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strtime_s(QEMU_G2H(c->time), c->size);
}

#endif

struct qemu__wstrtime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR* CDECL MSVCRT__wstrtime(WCHAR* time)
{
    struct qemu__wstrtime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTRTIME);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wstrtime(struct qemu_syscall *call)
{
    struct qemu__wstrtime *c = (struct qemu__wstrtime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wstrtime(QEMU_G2H(c->time)));
}

#endif

struct qemu__wstrtime_s
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _wstrtime_s(WCHAR* time, size_t size)
{
    struct qemu__wstrtime_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WSTRTIME_S);
    call.time = (ULONG_PTR)time;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wstrtime_s(struct qemu_syscall *call)
{
    struct qemu__wstrtime_s *c = (struct qemu__wstrtime_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wstrtime_s(QEMU_G2H(c->time), c->size);
}

#endif

struct qemu_clock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT_clock_t CDECL MSVCRT_clock(void)
{
    struct qemu_clock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOCK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_clock(struct qemu_syscall *call)
{
    struct qemu_clock *c = (struct qemu_clock *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_clock();
}

#endif

struct qemu__difftime64
{
    struct qemu_syscall super;
    uint64_t time1;
    uint64_t time2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__difftime64(MSVCRT___time64_t time1, MSVCRT___time64_t time2)
{
    struct qemu__difftime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DIFFTIME64);
    call.time1 = time1;
    call.time2 = time2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__difftime64(struct qemu_syscall *call)
{
    struct qemu__difftime64 *c = (struct qemu__difftime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__difftime64(c->time1, c->time2);
}

#endif

struct qemu__difftime32
{
    struct qemu_syscall super;
    uint64_t time1;
    uint64_t time2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT__difftime32(MSVCRT___time32_t time1, MSVCRT___time32_t time2)
{
    struct qemu__difftime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__DIFFTIME32);
    call.time1 = time1;
    call.time2 = time2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__difftime32(struct qemu_syscall *call)
{
    struct qemu__difftime32 *c = (struct qemu__difftime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__difftime32(c->time1, c->time2);
}

#endif

struct qemu_difftime
{
    struct qemu_syscall super;
    uint64_t time1;
    uint64_t time2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI double CDECL MSVCRT_difftime(MSVCRT___time64_t time1, MSVCRT___time64_t time2)
{
    struct qemu_difftime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIFFTIME);
    call.time1 = time1;
    call.time2 = time2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_difftime(struct qemu_syscall *call)
{
    struct qemu_difftime *c = (struct qemu_difftime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_difftime(c->time1, c->time2);
}

#endif

struct qemu__ftime64
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__ftime64(struct MSVCRT___timeb64 *buf)
{
    struct qemu__ftime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTIME64);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);
}

#else

void qemu__ftime64(struct qemu_syscall *call)
{
    struct qemu__ftime64 *c = (struct qemu__ftime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__ftime64(QEMU_G2H(c->buf));
}

#endif

struct qemu__ftime64_s
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__ftime64_s(struct MSVCRT___timeb64 *buf)
{
    struct qemu__ftime64_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTIME64_S);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ftime64_s(struct qemu_syscall *call)
{
    struct qemu__ftime64_s *c = (struct qemu__ftime64_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ftime64_s(QEMU_G2H(c->buf));
}

#endif

struct qemu__ftime32
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__ftime32(struct MSVCRT___timeb32 *buf)
{
    struct qemu__ftime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTIME32);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);
}

#else

void qemu__ftime32(struct qemu_syscall *call)
{
    struct qemu__ftime32 *c = (struct qemu__ftime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__ftime32(QEMU_G2H(c->buf));
}

#endif

struct qemu__ftime32_s
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__ftime32_s(struct MSVCRT___timeb32 *buf)
{
    struct qemu__ftime32_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTIME32_S);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ftime32_s(struct qemu_syscall *call)
{
    struct qemu__ftime32_s *c = (struct qemu__ftime32_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ftime32_s(QEMU_G2H(c->buf));
}

#endif

struct qemu__ftime
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__ftime(struct MSVCRT___timeb64 *buf)
{
    struct qemu__ftime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FTIME);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);
}

#else

void qemu__ftime(struct qemu_syscall *call)
{
    struct qemu__ftime *c = (struct qemu__ftime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p__ftime(QEMU_G2H(c->buf));
}

#endif

struct qemu__time64
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time64_t CDECL MSVCRT__time64(MSVCRT___time64_t *buf)
{
    struct qemu__time64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TIME64);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__time64(struct qemu_syscall *call)
{
    struct qemu__time64 *c = (struct qemu__time64 *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    c->super.iret = p__time64(QEMU_G2H(c->buf));
}

#endif

struct qemu__time32
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time32_t CDECL MSVCRT__time32(MSVCRT___time32_t *buf)
{
    struct qemu__time32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TIME32);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__time32(struct qemu_syscall *call)
{
    struct qemu__time32 *c = (struct qemu__time32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__time32(QEMU_G2H(c->buf));
}

#endif

struct qemu_time
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT___time64_t CDECL MSVCRT_time(MSVCRT___time64_t* buf)
{
    struct qemu_time call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIME);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_time(struct qemu_syscall *call)
{
    struct qemu_time *c = (struct qemu_time *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_time(QEMU_G2H(c->buf));
}

#endif

struct qemu___p__daylight
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int * CDECL MSVCRT___p__daylight(void)
{
    struct qemu___p__daylight call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__DAYLIGHT);

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___p__daylight(struct qemu_syscall *call)
{
    struct qemu___p__daylight *c = (struct qemu___p__daylight *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__daylight());
}

#endif

struct qemu___p__dstbias
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int * CDECL MSVCRT___p__dstbias(void)
{
    struct qemu___p__dstbias call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__DSTBIAS);

    qemu_syscall(&call.super);

    return (int *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___p__dstbias(struct qemu_syscall *call)
{
    struct qemu___p__dstbias *c = (struct qemu___p__dstbias *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__dstbias());
}

#endif

struct qemu__get_dstbias
{
    struct qemu_syscall super;
    uint64_t seconds;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__get_dstbias(int *seconds)
{
    struct qemu__get_dstbias call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_DSTBIAS);
    call.seconds = (ULONG_PTR)seconds;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_dstbias(struct qemu_syscall *call)
{
    struct qemu__get_dstbias *c = (struct qemu__get_dstbias *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_dstbias(QEMU_G2H(c->seconds));
}

#endif

struct qemu___p__timezone
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG * CDECL MSVCRT___p__timezone(void)
{
    struct qemu___p__timezone call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__TIMEZONE);

    qemu_syscall(&call.super);

    return (LONG *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___p__timezone(struct qemu_syscall *call)
{
    struct qemu___p__timezone *c = (struct qemu___p__timezone *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__timezone());
}

#endif

struct qemu__get_tzname
{
    struct qemu_syscall super;
    uint64_t ret;
    uint64_t buf;
    uint64_t bufsize;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__get_tzname(size_t *ret, char *buf, size_t bufsize, int index)
{
    struct qemu__get_tzname call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_TZNAME);
    call.ret = (ULONG_PTR)ret;
    call.buf = (ULONG_PTR)buf;
    call.bufsize = bufsize;
    call.index = index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_tzname(struct qemu_syscall *call)
{
    struct qemu__get_tzname *c = (struct qemu__get_tzname *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_tzname(QEMU_G2H(c->ret), QEMU_G2H(c->buf), c->bufsize, c->index);
}

#endif

struct qemu___p__tzname
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char ** CDECL __p__tzname(void)
{
    struct qemu___p__tzname call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__TZNAME);

    qemu_syscall(&call.super);

    return (char **)(ULONG_PTR)call.super.iret;
}

#else

void qemu___p__tzname(struct qemu_syscall *call)
{
    struct qemu___p__tzname *c = (struct qemu___p__tzname *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__tzname());
}

#endif

struct qemu__strftime_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
    uint64_t format;
    uint64_t mstm;
    uint64_t loc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT__strftime_l(char *str, size_t max, const char *format, const struct MSVCRT_tm *mstm, MSVCRT__locale_t loc)
{
    struct qemu__strftime_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRFTIME_L);
    call.str = (ULONG_PTR)str;
    call.max = max;
    call.format = (ULONG_PTR)format;
    call.mstm = (ULONG_PTR)mstm;
    call.loc = (ULONG_PTR)loc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strftime_l(struct qemu_syscall *call)
{
    struct qemu__strftime_l *c = (struct qemu__strftime_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strftime_l(QEMU_G2H(c->str), c->max, QEMU_G2H(c->format), QEMU_G2H(c->mstm), QEMU_G2H(c->loc));
}

#endif

struct qemu__Strftime
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
    uint64_t format;
    uint64_t mstm;
    uint64_t time_data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL _Strftime(char *str, size_t max, const char *format, const struct MSVCRT_tm *mstm, MSVCRT___lc_time_data *time_data)
{
    struct qemu__Strftime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRFTIME);
    call.str = (ULONG_PTR)str;
    call.max = max;
    call.format = (ULONG_PTR)format;
    call.mstm = (ULONG_PTR)mstm;
    call.time_data = (ULONG_PTR)time_data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__Strftime(struct qemu_syscall *call)
{
    struct qemu__Strftime *c = (struct qemu__Strftime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__Strftime(QEMU_G2H(c->str), c->max, QEMU_G2H(c->format), QEMU_G2H(c->mstm), QEMU_G2H(c->time_data));
}

#endif

struct qemu_strftime
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
    uint64_t format;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_strftime(char *str, size_t max, const char *format, const struct MSVCRT_tm *mstm)
{
    struct qemu_strftime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRFTIME);
    call.str = (ULONG_PTR)str;
    call.max = max;
    call.format = (ULONG_PTR)format;
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strftime(struct qemu_syscall *call)
{
    struct qemu_strftime *c = (struct qemu_strftime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strftime(QEMU_G2H(c->str), c->max, QEMU_G2H(c->format), QEMU_G2H(c->mstm));
}

#endif

struct qemu__wcsftime_l
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
    uint64_t format;
    uint64_t mstm;
    uint64_t loc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT__wcsftime_l(WCHAR *str, size_t max, const WCHAR *format, const struct MSVCRT_tm *mstm, MSVCRT__locale_t loc)
{
    struct qemu__wcsftime_l call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSFTIME_L);
    call.str = (ULONG_PTR)str;
    call.max = max;
    call.format = (ULONG_PTR)format;
    call.mstm = (ULONG_PTR)mstm;
    call.loc = (ULONG_PTR)loc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wcsftime_l(struct qemu_syscall *call)
{
    struct qemu__wcsftime_l *c = (struct qemu__wcsftime_l *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wcsftime_l(QEMU_G2H(c->str), c->max, QEMU_G2H(c->format), QEMU_G2H(c->mstm), QEMU_G2H(c->loc));
}

#endif

struct qemu_wcsftime
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
    uint64_t format;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL MSVCRT_wcsftime(WCHAR *str, size_t max, const WCHAR *format, const struct MSVCRT_tm *mstm)
{
    struct qemu_wcsftime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WCSFTIME);
    call.str = (ULONG_PTR)str;
    call.max = max;
    call.format = (ULONG_PTR)format;
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wcsftime(struct qemu_syscall *call)
{
    struct qemu_wcsftime *c = (struct qemu_wcsftime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wcsftime(QEMU_G2H(c->str), c->max, QEMU_G2H(c->format), QEMU_G2H(c->mstm));
}

#endif

struct qemu__Wcsftime
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t max;
    uint64_t format;
    uint64_t mstm;
    uint64_t time_data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL _Wcsftime(WCHAR *str, size_t max, const WCHAR *format, const struct MSVCRT_tm *mstm, MSVCRT___lc_time_data *time_data)
{
    struct qemu__Wcsftime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCSFTIME);
    call.str = (ULONG_PTR)str;
    call.max = max;
    call.format = (ULONG_PTR)format;
    call.mstm = (ULONG_PTR)mstm;
    call.time_data = (ULONG_PTR)time_data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__Wcsftime(struct qemu_syscall *call)
{
    struct qemu__Wcsftime *c = (struct qemu__Wcsftime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__Wcsftime(QEMU_G2H(c->str), c->max, QEMU_G2H(c->format), QEMU_G2H(c->mstm), QEMU_G2H(c->time_data));
}

#endif

struct qemu_asctime
{
    struct qemu_syscall super;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT_asctime(const struct MSVCRT_tm *mstm)
{
    struct qemu_asctime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASCTIME);
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_asctime(struct qemu_syscall *call)
{
    struct qemu_asctime *c = (struct qemu_asctime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_asctime(QEMU_G2H(c->mstm)));
}

#endif

struct qemu_asctime_s
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t size;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_asctime_s(char* time, size_t size, const struct MSVCRT_tm *mstm)
{
    struct qemu_asctime_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ASCTIME_S);
    call.time = (ULONG_PTR)time;
    call.size = size;
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_asctime_s(struct qemu_syscall *call)
{
    struct qemu_asctime_s *c = (struct qemu_asctime_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_asctime_s(QEMU_G2H(c->time), c->size, QEMU_G2H(c->mstm));
}

#endif

struct qemu__wasctime
{
    struct qemu_syscall super;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * CDECL MSVCRT__wasctime(const struct MSVCRT_tm *mstm)
{
    struct qemu__wasctime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WASCTIME);
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wasctime(struct qemu_syscall *call)
{
    struct qemu__wasctime *c = (struct qemu__wasctime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wasctime(QEMU_G2H(c->mstm)));
}

#endif

struct qemu__wasctime_s
{
    struct qemu_syscall super;
    uint64_t time;
    uint64_t size;
    uint64_t mstm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wasctime_s(WCHAR* time, size_t size, const struct MSVCRT_tm *mstm)
{
    struct qemu__wasctime_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WASCTIME_S);
    call.time = (ULONG_PTR)time;
    call.size = size;
    call.mstm = (ULONG_PTR)mstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wasctime_s(struct qemu_syscall *call)
{
    struct qemu__wasctime_s *c = (struct qemu__wasctime_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wasctime_s(QEMU_G2H(c->time), c->size, QEMU_G2H(c->mstm));
}

#endif

struct qemu__ctime64
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT__ctime64(const MSVCRT___time64_t *time)
{
    struct qemu__ctime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CTIME64);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ctime64(struct qemu_syscall *call)
{
    struct qemu__ctime64 *c = (struct qemu__ctime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__ctime64(QEMU_G2H(c->time)));
}

#endif

struct qemu__ctime64_s
{
    struct qemu_syscall super;
    uint64_t res;
    uint64_t len;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__ctime64_s(char *res, size_t len, const MSVCRT___time64_t *time)
{
    struct qemu__ctime64_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CTIME64_S);
    call.res = (ULONG_PTR)res;
    call.len = len;
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ctime64_s(struct qemu_syscall *call)
{
    struct qemu__ctime64_s *c = (struct qemu__ctime64_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ctime64_s(QEMU_G2H(c->res), c->len, QEMU_G2H(c->time));
}

#endif

struct qemu__ctime32
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT__ctime32(const MSVCRT___time32_t *time)
{
    struct qemu__ctime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CTIME32);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ctime32(struct qemu_syscall *call)
{
    struct qemu__ctime32 *c = (struct qemu__ctime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__ctime32(QEMU_G2H(c->time)));
}

#endif

struct qemu__ctime32_s
{
    struct qemu_syscall super;
    uint64_t res;
    uint64_t len;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__ctime32_s(char *res, size_t len, const MSVCRT___time32_t *time)
{
    struct qemu__ctime32_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CTIME32_S);
    call.res = (ULONG_PTR)res;
    call.len = len;
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__ctime32_s(struct qemu_syscall *call)
{
    struct qemu__ctime32_s *c = (struct qemu__ctime32_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__ctime32_s(QEMU_G2H(c->res), c->len, QEMU_G2H(c->time));
}

#endif

struct qemu_ctime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL MSVCRT_ctime(const MSVCRT___time64_t *time)
{
    struct qemu_ctime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CTIME);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ctime(struct qemu_syscall *call)
{
    struct qemu_ctime *c = (struct qemu_ctime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_ctime(QEMU_G2H(c->time)));
}

#endif

struct qemu__wctime64
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * CDECL MSVCRT__wctime64(const MSVCRT___time64_t *time)
{
    struct qemu__wctime64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTIME64);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wctime64(struct qemu_syscall *call)
{
    struct qemu__wctime64 *c = (struct qemu__wctime64 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wctime64(QEMU_G2H(c->time)));
}

#endif

struct qemu__wctime32
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * CDECL MSVCRT__wctime32(const MSVCRT___time32_t *time)
{
    struct qemu__wctime32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTIME32);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wctime32(struct qemu_syscall *call)
{
    struct qemu__wctime32 *c = (struct qemu__wctime32 *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wctime32(QEMU_G2H(c->time)));
}

#endif

struct qemu__wctime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * CDECL MSVCRT__wctime(const MSVCRT___time64_t *time)
{
    struct qemu__wctime call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTIME);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__wctime(struct qemu_syscall *call)
{
    struct qemu__wctime *c = (struct qemu__wctime *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__wctime(QEMU_G2H(c->time)));
}

#endif

struct qemu__wctime64_s
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t size;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wctime64_s(WCHAR *buf, size_t size, const MSVCRT___time64_t *time)
{
    struct qemu__wctime64_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTIME64_S);
    call.buf = (ULONG_PTR)buf;
    call.size = size;
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wctime64_s(struct qemu_syscall *call)
{
    struct qemu__wctime64_s *c = (struct qemu__wctime64_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wctime64_s(QEMU_G2H(c->buf), c->size, QEMU_G2H(c->time));
}

#endif

struct qemu__wctime32_s
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t size;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__wctime32_s(WCHAR *buf, size_t size, const MSVCRT___time32_t *time)
{
    struct qemu__wctime32_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__WCTIME32_S);
    call.buf = (ULONG_PTR)buf;
    call.size = size;
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__wctime32_s(struct qemu_syscall *call)
{
    struct qemu__wctime32_s *c = (struct qemu__wctime32_s *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__wctime32_s(QEMU_G2H(c->buf), c->size, QEMU_G2H(c->time));
}

#endif

struct qemu__get_timezone
{
    struct qemu_syscall super;
    uint64_t timezone;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _get_timezone(LONG *timezone)
{
    struct qemu__get_timezone call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_TIMEZONE);
    call.timezone = (ULONG_PTR)timezone;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_timezone(struct qemu_syscall *call)
{
    struct qemu__get_timezone *c = (struct qemu__get_timezone *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_timezone(QEMU_G2H(c->timezone));
}

#endif

struct qemu__get_daylight
{
    struct qemu_syscall super;
    uint64_t hours;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _get_daylight(int *hours)
{
    struct qemu__get_daylight call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_DAYLIGHT);
    call.hours = (ULONG_PTR)hours;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_daylight(struct qemu_syscall *call)
{
    struct qemu__get_daylight *c = (struct qemu__get_daylight *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_daylight(QEMU_G2H(c->hours));
}

#endif

