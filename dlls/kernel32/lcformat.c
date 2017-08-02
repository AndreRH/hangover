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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetDateFormatA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpTime;
    uint64_t lpFormat;
    uint64_t lpDateStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetDateFormatA(LCID lcid, DWORD dwFlags, const SYSTEMTIME* lpTime, LPCSTR lpFormat, LPSTR lpDateStr, INT cchOut)
{
    struct qemu_GetDateFormatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDATEFORMATA);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpTime = (uint64_t)lpTime;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpDateStr = (uint64_t)lpDateStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDateFormatA(struct qemu_syscall *call)
{
    struct qemu_GetDateFormatA *c = (struct qemu_GetDateFormatA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDateFormatA(c->lcid, c->dwFlags, QEMU_G2H(c->lpTime), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpDateStr), c->cchOut);
}

#endif

struct qemu_GetDateFormatEx
{
    struct qemu_syscall super;
    uint64_t localename;
    uint64_t flags;
    uint64_t date;
    uint64_t format;
    uint64_t outbuf;
    uint64_t bufsize;
    uint64_t calendar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetDateFormatEx(LPCWSTR localename, DWORD flags, const SYSTEMTIME* date, LPCWSTR format, LPWSTR outbuf, INT bufsize, LPCWSTR calendar)
{
    struct qemu_GetDateFormatEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDATEFORMATEX);
    call.localename = (uint64_t)localename;
    call.flags = (uint64_t)flags;
    call.date = (uint64_t)date;
    call.format = (uint64_t)format;
    call.outbuf = (uint64_t)outbuf;
    call.bufsize = (uint64_t)bufsize;
    call.calendar = (uint64_t)calendar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDateFormatEx(struct qemu_syscall *call)
{
    struct qemu_GetDateFormatEx *c = (struct qemu_GetDateFormatEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDateFormatEx(QEMU_G2H(c->localename), c->flags, QEMU_G2H(c->date), QEMU_G2H(c->format), QEMU_G2H(c->outbuf), c->bufsize, QEMU_G2H(c->calendar));
}

#endif

struct qemu_GetDateFormatW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpTime;
    uint64_t lpFormat;
    uint64_t lpDateStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetDateFormatW(LCID lcid, DWORD dwFlags, const SYSTEMTIME* lpTime, LPCWSTR lpFormat, LPWSTR lpDateStr, INT cchOut)
{
    struct qemu_GetDateFormatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDATEFORMATW);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpTime = (uint64_t)lpTime;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpDateStr = (uint64_t)lpDateStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDateFormatW(struct qemu_syscall *call)
{
    struct qemu_GetDateFormatW *c = (struct qemu_GetDateFormatW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDateFormatW(c->lcid, c->dwFlags, QEMU_G2H(c->lpTime), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpDateStr), c->cchOut);
}

#endif

struct qemu_GetTimeFormatA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpTime;
    uint64_t lpFormat;
    uint64_t lpTimeStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetTimeFormatA(LCID lcid, DWORD dwFlags, const SYSTEMTIME* lpTime, LPCSTR lpFormat, LPSTR lpTimeStr, INT cchOut)
{
    struct qemu_GetTimeFormatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTIMEFORMATA);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpTime = (uint64_t)lpTime;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpTimeStr = (uint64_t)lpTimeStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTimeFormatA(struct qemu_syscall *call)
{
    struct qemu_GetTimeFormatA *c = (struct qemu_GetTimeFormatA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTimeFormatA(c->lcid, c->dwFlags, QEMU_G2H(c->lpTime), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpTimeStr), c->cchOut);
}

#endif

struct qemu_GetTimeFormatEx
{
    struct qemu_syscall super;
    uint64_t localename;
    uint64_t flags;
    uint64_t time;
    uint64_t format;
    uint64_t outbuf;
    uint64_t bufsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetTimeFormatEx(LPCWSTR localename, DWORD flags, const SYSTEMTIME* time, LPCWSTR format, LPWSTR outbuf, INT bufsize)
{
    struct qemu_GetTimeFormatEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTIMEFORMATEX);
    call.localename = (uint64_t)localename;
    call.flags = (uint64_t)flags;
    call.time = (uint64_t)time;
    call.format = (uint64_t)format;
    call.outbuf = (uint64_t)outbuf;
    call.bufsize = (uint64_t)bufsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTimeFormatEx(struct qemu_syscall *call)
{
    struct qemu_GetTimeFormatEx *c = (struct qemu_GetTimeFormatEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTimeFormatEx(QEMU_G2H(c->localename), c->flags, QEMU_G2H(c->time), QEMU_G2H(c->format), QEMU_G2H(c->outbuf), c->bufsize);
}

#endif

struct qemu_GetTimeFormatW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpTime;
    uint64_t lpFormat;
    uint64_t lpTimeStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetTimeFormatW(LCID lcid, DWORD dwFlags, const SYSTEMTIME* lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, INT cchOut)
{
    struct qemu_GetTimeFormatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTIMEFORMATW);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpTime = (uint64_t)lpTime;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpTimeStr = (uint64_t)lpTimeStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTimeFormatW(struct qemu_syscall *call)
{
    struct qemu_GetTimeFormatW *c = (struct qemu_GetTimeFormatW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTimeFormatW(c->lcid, c->dwFlags, QEMU_G2H(c->lpTime), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpTimeStr), c->cchOut);
}

#endif

struct qemu_GetNumberFormatA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpszValue;
    uint64_t lpFormat;
    uint64_t lpNumberStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetNumberFormatA(LCID lcid, DWORD dwFlags, LPCSTR lpszValue, const NUMBERFMTA *lpFormat, LPSTR lpNumberStr, int cchOut)
{
    struct qemu_GetNumberFormatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBERFORMATA);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpszValue = (uint64_t)lpszValue;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpNumberStr = (uint64_t)lpNumberStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberFormatA(struct qemu_syscall *call)
{
    struct qemu_GetNumberFormatA *c = (struct qemu_GetNumberFormatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberFormatA(c->lcid, c->dwFlags, QEMU_G2H(c->lpszValue), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpNumberStr), c->cchOut);
}

#endif

struct qemu_GetNumberFormatW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpszValue;
    uint64_t lpFormat;
    uint64_t lpNumberStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetNumberFormatW(LCID lcid, DWORD dwFlags, LPCWSTR lpszValue, const NUMBERFMTW *lpFormat, LPWSTR lpNumberStr, int cchOut)
{
    struct qemu_GetNumberFormatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBERFORMATW);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpszValue = (uint64_t)lpszValue;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpNumberStr = (uint64_t)lpNumberStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberFormatW(struct qemu_syscall *call)
{
    struct qemu_GetNumberFormatW *c = (struct qemu_GetNumberFormatW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberFormatW(c->lcid, c->dwFlags, QEMU_G2H(c->lpszValue), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpNumberStr), c->cchOut);
}

#endif

struct qemu_GetNumberFormatEx
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t flags;
    uint64_t value;
    uint64_t format;
    uint64_t number;
    uint64_t numout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetNumberFormatEx(LPCWSTR name, DWORD flags, LPCWSTR value, const NUMBERFMTW *format, LPWSTR number, int numout)
{
    struct qemu_GetNumberFormatEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBERFORMATEX);
    call.name = (uint64_t)name;
    call.flags = (uint64_t)flags;
    call.value = (uint64_t)value;
    call.format = (uint64_t)format;
    call.number = (uint64_t)number;
    call.numout = (uint64_t)numout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNumberFormatEx to Wine headers? */
extern INT WINAPI GetNumberFormatEx(LPCWSTR name, DWORD flags, LPCWSTR value, const NUMBERFMTW *format, LPWSTR number, int numout);
void qemu_GetNumberFormatEx(struct qemu_syscall *call)
{
    struct qemu_GetNumberFormatEx *c = (struct qemu_GetNumberFormatEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumberFormatEx(QEMU_G2H(c->name), c->flags, QEMU_G2H(c->value), QEMU_G2H(c->format), QEMU_G2H(c->number), c->numout);
}

#endif

struct qemu_GetCurrencyFormatA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpszValue;
    uint64_t lpFormat;
    uint64_t lpCurrencyStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetCurrencyFormatA(LCID lcid, DWORD dwFlags, LPCSTR lpszValue, const CURRENCYFMTA *lpFormat, LPSTR lpCurrencyStr, int cchOut)
{
    struct qemu_GetCurrencyFormatA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENCYFORMATA);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpszValue = (uint64_t)lpszValue;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpCurrencyStr = (uint64_t)lpCurrencyStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrencyFormatA(struct qemu_syscall *call)
{
    struct qemu_GetCurrencyFormatA *c = (struct qemu_GetCurrencyFormatA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrencyFormatA(c->lcid, c->dwFlags, QEMU_G2H(c->lpszValue), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpCurrencyStr), c->cchOut);
}

#endif

struct qemu_GetCurrencyFormatW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t dwFlags;
    uint64_t lpszValue;
    uint64_t lpFormat;
    uint64_t lpCurrencyStr;
    uint64_t cchOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetCurrencyFormatW(LCID lcid, DWORD dwFlags, LPCWSTR lpszValue, const CURRENCYFMTW *lpFormat, LPWSTR lpCurrencyStr, int cchOut)
{
    struct qemu_GetCurrencyFormatW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENCYFORMATW);
    call.lcid = (uint64_t)lcid;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpszValue = (uint64_t)lpszValue;
    call.lpFormat = (uint64_t)lpFormat;
    call.lpCurrencyStr = (uint64_t)lpCurrencyStr;
    call.cchOut = (uint64_t)cchOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrencyFormatW(struct qemu_syscall *call)
{
    struct qemu_GetCurrencyFormatW *c = (struct qemu_GetCurrencyFormatW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrencyFormatW(c->lcid, c->dwFlags, QEMU_G2H(c->lpszValue), QEMU_G2H(c->lpFormat), QEMU_G2H(c->lpCurrencyStr), c->cchOut);
}

#endif

struct qemu_EnumDateFormatsExA
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDateFormatsExA(DATEFMT_ENUMPROCEXA proc, LCID lcid, DWORD flags)
{
    struct qemu_EnumDateFormatsExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDATEFORMATSEXA);
    call.proc = (uint64_t)proc;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDateFormatsExA(struct qemu_syscall *call)
{
    struct qemu_EnumDateFormatsExA *c = (struct qemu_EnumDateFormatsExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDateFormatsExA(QEMU_G2H(c->proc), c->lcid, c->flags);
}

#endif

struct qemu_EnumDateFormatsExW
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDateFormatsExW(DATEFMT_ENUMPROCEXW proc, LCID lcid, DWORD flags)
{
    struct qemu_EnumDateFormatsExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDATEFORMATSEXW);
    call.proc = (uint64_t)proc;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDateFormatsExW(struct qemu_syscall *call)
{
    struct qemu_EnumDateFormatsExW *c = (struct qemu_EnumDateFormatsExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDateFormatsExW(QEMU_G2H(c->proc), c->lcid, c->flags);
}

#endif

struct qemu_EnumDateFormatsA
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDateFormatsA(DATEFMT_ENUMPROCA proc, LCID lcid, DWORD flags)
{
    struct qemu_EnumDateFormatsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDATEFORMATSA);
    call.proc = (uint64_t)proc;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDateFormatsA(struct qemu_syscall *call)
{
    struct qemu_EnumDateFormatsA *c = (struct qemu_EnumDateFormatsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDateFormatsA(QEMU_G2H(c->proc), c->lcid, c->flags);
}

#endif

struct qemu_EnumDateFormatsW
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDateFormatsW(DATEFMT_ENUMPROCW proc, LCID lcid, DWORD flags)
{
    struct qemu_EnumDateFormatsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDATEFORMATSW);
    call.proc = (uint64_t)proc;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDateFormatsW(struct qemu_syscall *call)
{
    struct qemu_EnumDateFormatsW *c = (struct qemu_EnumDateFormatsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDateFormatsW(QEMU_G2H(c->proc), c->lcid, c->flags);
}

#endif

struct qemu_EnumDateFormatsExEx
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t locale;
    uint64_t flags;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDateFormatsExEx(DATEFMT_ENUMPROCEXEX proc, const WCHAR *locale, DWORD flags, LPARAM lParam)
{
    struct qemu_EnumDateFormatsExEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDATEFORMATSEXEX);
    call.proc = (uint64_t)proc;
    call.locale = (uint64_t)locale;
    call.flags = (uint64_t)flags;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDateFormatsExEx(struct qemu_syscall *call)
{
    struct qemu_EnumDateFormatsExEx *c = (struct qemu_EnumDateFormatsExEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDateFormatsExEx(QEMU_G2H(c->proc), QEMU_G2H(c->locale), c->flags, c->lParam);
}

#endif

struct qemu_EnumTimeFormatsA
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumTimeFormatsA(TIMEFMT_ENUMPROCA proc, LCID lcid, DWORD flags)
{
    struct qemu_EnumTimeFormatsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMTIMEFORMATSA);
    call.proc = (uint64_t)proc;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumTimeFormatsA(struct qemu_syscall *call)
{
    struct qemu_EnumTimeFormatsA *c = (struct qemu_EnumTimeFormatsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumTimeFormatsA(QEMU_G2H(c->proc), c->lcid, c->flags);
}

#endif

struct qemu_EnumTimeFormatsW
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumTimeFormatsW(TIMEFMT_ENUMPROCW proc, LCID lcid, DWORD flags)
{
    struct qemu_EnumTimeFormatsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMTIMEFORMATSW);
    call.proc = (uint64_t)proc;
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumTimeFormatsW(struct qemu_syscall *call)
{
    struct qemu_EnumTimeFormatsW *c = (struct qemu_EnumTimeFormatsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumTimeFormatsW(QEMU_G2H(c->proc), c->lcid, c->flags);
}

#endif

struct qemu_EnumTimeFormatsEx
{
    struct qemu_syscall super;
    uint64_t proc;
    uint64_t locale;
    uint64_t flags;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumTimeFormatsEx(TIMEFMT_ENUMPROCEX proc, const WCHAR *locale, DWORD flags, LPARAM lParam)
{
    struct qemu_EnumTimeFormatsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMTIMEFORMATSEX);
    call.proc = (uint64_t)proc;
    call.locale = (uint64_t)locale;
    call.flags = (uint64_t)flags;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumTimeFormatsEx(struct qemu_syscall *call)
{
    struct qemu_EnumTimeFormatsEx *c = (struct qemu_EnumTimeFormatsEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumTimeFormatsEx(QEMU_G2H(c->proc), QEMU_G2H(c->locale), c->flags, c->lParam);
}

#endif

struct qemu_EnumCalendarInfoA
{
    struct qemu_syscall super;
    uint64_t calinfoproc;
    uint64_t locale;
    uint64_t calendar;
    uint64_t caltype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumCalendarInfoA(CALINFO_ENUMPROCA calinfoproc,LCID locale, CALID calendar,CALTYPE caltype)
{
    struct qemu_EnumCalendarInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCALENDARINFOA);
    call.calinfoproc = (uint64_t)calinfoproc;
    call.locale = (uint64_t)locale;
    call.calendar = (uint64_t)calendar;
    call.caltype = (uint64_t)caltype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumCalendarInfoA(struct qemu_syscall *call)
{
    struct qemu_EnumCalendarInfoA *c = (struct qemu_EnumCalendarInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumCalendarInfoA(QEMU_G2H(c->calinfoproc), c->locale, c->calendar, c->caltype);
}

#endif

struct qemu_EnumCalendarInfoW
{
    struct qemu_syscall super;
    uint64_t calinfoproc;
    uint64_t locale;
    uint64_t calendar;
    uint64_t caltype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumCalendarInfoW(CALINFO_ENUMPROCW calinfoproc,LCID locale, CALID calendar,CALTYPE caltype)
{
    struct qemu_EnumCalendarInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCALENDARINFOW);
    call.calinfoproc = (uint64_t)calinfoproc;
    call.locale = (uint64_t)locale;
    call.calendar = (uint64_t)calendar;
    call.caltype = (uint64_t)caltype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumCalendarInfoW(struct qemu_syscall *call)
{
    struct qemu_EnumCalendarInfoW *c = (struct qemu_EnumCalendarInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumCalendarInfoW(QEMU_G2H(c->calinfoproc), c->locale, c->calendar, c->caltype);
}

#endif

struct qemu_EnumCalendarInfoExA
{
    struct qemu_syscall super;
    uint64_t calinfoproc;
    uint64_t locale;
    uint64_t calendar;
    uint64_t caltype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumCalendarInfoExA(CALINFO_ENUMPROCEXA calinfoproc,LCID locale, CALID calendar,CALTYPE caltype)
{
    struct qemu_EnumCalendarInfoExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCALENDARINFOEXA);
    call.calinfoproc = (uint64_t)calinfoproc;
    call.locale = (uint64_t)locale;
    call.calendar = (uint64_t)calendar;
    call.caltype = (uint64_t)caltype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumCalendarInfoExA(struct qemu_syscall *call)
{
    struct qemu_EnumCalendarInfoExA *c = (struct qemu_EnumCalendarInfoExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumCalendarInfoExA(QEMU_G2H(c->calinfoproc), c->locale, c->calendar, c->caltype);
}

#endif

struct qemu_EnumCalendarInfoExW
{
    struct qemu_syscall super;
    uint64_t calinfoproc;
    uint64_t locale;
    uint64_t calendar;
    uint64_t caltype;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumCalendarInfoExW(CALINFO_ENUMPROCEXW calinfoproc,LCID locale, CALID calendar,CALTYPE caltype)
{
    struct qemu_EnumCalendarInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCALENDARINFOEXW);
    call.calinfoproc = (uint64_t)calinfoproc;
    call.locale = (uint64_t)locale;
    call.calendar = (uint64_t)calendar;
    call.caltype = (uint64_t)caltype;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumCalendarInfoExW(struct qemu_syscall *call)
{
    struct qemu_EnumCalendarInfoExW *c = (struct qemu_EnumCalendarInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumCalendarInfoExW(QEMU_G2H(c->calinfoproc), c->locale, c->calendar, c->caltype);
}

#endif

struct qemu_EnumCalendarInfoExEx
{
    struct qemu_syscall super;
    uint64_t calinfoproc;
    uint64_t locale;
    uint64_t calendar;
    uint64_t reserved;
    uint64_t caltype;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumCalendarInfoExEx(CALINFO_ENUMPROCEXEX calinfoproc, LPCWSTR locale, CALID calendar, LPCWSTR reserved, CALTYPE caltype, LPARAM lParam)
{
    struct qemu_EnumCalendarInfoExEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMCALENDARINFOEXEX);
    call.calinfoproc = (uint64_t)calinfoproc;
    call.locale = (uint64_t)locale;
    call.calendar = (uint64_t)calendar;
    call.reserved = (uint64_t)reserved;
    call.caltype = (uint64_t)caltype;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumCalendarInfoExEx(struct qemu_syscall *call)
{
    struct qemu_EnumCalendarInfoExEx *c = (struct qemu_EnumCalendarInfoExEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumCalendarInfoExEx(QEMU_G2H(c->calinfoproc), QEMU_G2H(c->locale), c->calendar, QEMU_G2H(c->reserved), c->caltype, c->lParam);
}

#endif

