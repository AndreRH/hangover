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


struct qemu_SetLocalTime
{
    struct qemu_syscall super;
    uint64_t systime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetLocalTime(const SYSTEMTIME *systime)
{
    struct qemu_SetLocalTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLOCALTIME);
    call.systime = (uint64_t)systime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetLocalTime(struct qemu_syscall *call)
{
    struct qemu_SetLocalTime *c = (struct qemu_SetLocalTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetLocalTime(QEMU_G2H(c->systime));
}

#endif

struct qemu_GetSystemTimeAdjustment
{
    struct qemu_syscall super;
    uint64_t lpTimeAdjustment;
    uint64_t lpTimeIncrement;
    uint64_t lpTimeAdjustmentDisabled;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSystemTimeAdjustment(PDWORD lpTimeAdjustment, PDWORD lpTimeIncrement, PBOOL lpTimeAdjustmentDisabled)
{
    struct qemu_GetSystemTimeAdjustment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMTIMEADJUSTMENT);
    call.lpTimeAdjustment = (uint64_t)lpTimeAdjustment;
    call.lpTimeIncrement = (uint64_t)lpTimeIncrement;
    call.lpTimeAdjustmentDisabled = (uint64_t)lpTimeAdjustmentDisabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemTimeAdjustment(struct qemu_syscall *call)
{
    struct qemu_GetSystemTimeAdjustment *c = (struct qemu_GetSystemTimeAdjustment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemTimeAdjustment(QEMU_G2H(c->lpTimeAdjustment), QEMU_G2H(c->lpTimeIncrement), QEMU_G2H(c->lpTimeAdjustmentDisabled));
}

#endif

struct qemu_SetSystemTime
{
    struct qemu_syscall super;
    uint64_t systime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSystemTime(const SYSTEMTIME *systime)
{
    struct qemu_SetSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSTEMTIME);
    call.systime = (uint64_t)systime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSystemTime(struct qemu_syscall *call)
{
    struct qemu_SetSystemTime *c = (struct qemu_SetSystemTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSystemTime(QEMU_G2H(c->systime));
}

#endif

struct qemu_SetSystemTimeAdjustment
{
    struct qemu_syscall super;
    uint64_t dwTimeAdjustment;
    uint64_t bTimeAdjustmentDisabled;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSystemTimeAdjustment(DWORD dwTimeAdjustment, BOOL bTimeAdjustmentDisabled)
{
    struct qemu_SetSystemTimeAdjustment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSTEMTIMEADJUSTMENT);
    call.dwTimeAdjustment = (uint64_t)dwTimeAdjustment;
    call.bTimeAdjustmentDisabled = (uint64_t)bTimeAdjustmentDisabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSystemTimeAdjustment(struct qemu_syscall *call)
{
    struct qemu_SetSystemTimeAdjustment *c = (struct qemu_SetSystemTimeAdjustment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSystemTimeAdjustment(c->dwTimeAdjustment, c->bTimeAdjustmentDisabled);
}

#endif

struct qemu_GetTimeZoneInformation
{
    struct qemu_syscall super;
    uint64_t tzinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTimeZoneInformation(LPTIME_ZONE_INFORMATION tzinfo)
{
    struct qemu_GetTimeZoneInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTIMEZONEINFORMATION);
    call.tzinfo = (uint64_t)tzinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTimeZoneInformation(struct qemu_syscall *call)
{
    struct qemu_GetTimeZoneInformation *c = (struct qemu_GetTimeZoneInformation *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTimeZoneInformation(QEMU_G2H(c->tzinfo));
}

#endif

struct qemu_GetTimeZoneInformationForYear
{
    struct qemu_syscall super;
    uint64_t wYear;
    uint64_t pdtzi;
    uint64_t ptzi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetTimeZoneInformationForYear(USHORT wYear, PDYNAMIC_TIME_ZONE_INFORMATION pdtzi, LPTIME_ZONE_INFORMATION ptzi)
{
    struct qemu_GetTimeZoneInformationForYear call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTIMEZONEINFORMATIONFORYEAR);
    call.wYear = (uint64_t)wYear;
    call.pdtzi = (uint64_t)pdtzi;
    call.ptzi = (uint64_t)ptzi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetTimeZoneInformationForYear to Wine headers? */
extern BOOL WINAPI GetTimeZoneInformationForYear(USHORT wYear, PDYNAMIC_TIME_ZONE_INFORMATION pdtzi, LPTIME_ZONE_INFORMATION ptzi);
void qemu_GetTimeZoneInformationForYear(struct qemu_syscall *call)
{
    struct qemu_GetTimeZoneInformationForYear *c = (struct qemu_GetTimeZoneInformationForYear *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTimeZoneInformationForYear(c->wYear, QEMU_G2H(c->pdtzi), QEMU_G2H(c->ptzi));
}

#endif

struct qemu_SetTimeZoneInformation
{
    struct qemu_syscall super;
    uint64_t tzinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetTimeZoneInformation(const TIME_ZONE_INFORMATION *tzinfo)
{
    struct qemu_SetTimeZoneInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTIMEZONEINFORMATION);
    call.tzinfo = (uint64_t)tzinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTimeZoneInformation(struct qemu_syscall *call)
{
    struct qemu_SetTimeZoneInformation *c = (struct qemu_SetTimeZoneInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetTimeZoneInformation(QEMU_G2H(c->tzinfo));
}

#endif

struct qemu_SystemTimeToTzSpecificLocalTime
{
    struct qemu_syscall super;
    uint64_t lpTimeZoneInformation;
    uint64_t lpUniversalTime;
    uint64_t lpLocalTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SystemTimeToTzSpecificLocalTime(const TIME_ZONE_INFORMATION *lpTimeZoneInformation, const SYSTEMTIME *lpUniversalTime, LPSYSTEMTIME lpLocalTime)
{
    struct qemu_SystemTimeToTzSpecificLocalTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMTIMETOTZSPECIFICLOCALTIME);
    call.lpTimeZoneInformation = (uint64_t)lpTimeZoneInformation;
    call.lpUniversalTime = (uint64_t)lpUniversalTime;
    call.lpLocalTime = (uint64_t)lpLocalTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SystemTimeToTzSpecificLocalTime(struct qemu_syscall *call)
{
    struct qemu_SystemTimeToTzSpecificLocalTime *c = (struct qemu_SystemTimeToTzSpecificLocalTime *)call;
    WINE_TRACE("\n");
    c->super.iret = SystemTimeToTzSpecificLocalTime(QEMU_G2H(c->lpTimeZoneInformation), QEMU_G2H(c->lpUniversalTime), QEMU_G2H(c->lpLocalTime));
}

#endif

struct qemu_TzSpecificLocalTimeToSystemTime
{
    struct qemu_syscall super;
    uint64_t lpTimeZoneInformation;
    uint64_t lpLocalTime;
    uint64_t lpUniversalTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TzSpecificLocalTimeToSystemTime(const TIME_ZONE_INFORMATION *lpTimeZoneInformation, const SYSTEMTIME *lpLocalTime, LPSYSTEMTIME lpUniversalTime)
{
    struct qemu_TzSpecificLocalTimeToSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TZSPECIFICLOCALTIMETOSYSTEMTIME);
    call.lpTimeZoneInformation = (uint64_t)lpTimeZoneInformation;
    call.lpLocalTime = (uint64_t)lpLocalTime;
    call.lpUniversalTime = (uint64_t)lpUniversalTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TzSpecificLocalTimeToSystemTime(struct qemu_syscall *call)
{
    struct qemu_TzSpecificLocalTimeToSystemTime *c = (struct qemu_TzSpecificLocalTimeToSystemTime *)call;
    WINE_TRACE("\n");
    c->super.iret = TzSpecificLocalTimeToSystemTime(QEMU_G2H(c->lpTimeZoneInformation), QEMU_G2H(c->lpLocalTime), QEMU_G2H(c->lpUniversalTime));
}

#endif

struct qemu_GetSystemTimeAsFileTime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetSystemTimeAsFileTime(LPFILETIME time)
{
    struct qemu_GetSystemTimeAsFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMTIMEASFILETIME);
    call.time = (uint64_t)time;

    qemu_syscall(&call.super);
}

#else

void qemu_GetSystemTimeAsFileTime(struct qemu_syscall *call)
{
    struct qemu_GetSystemTimeAsFileTime *c = (struct qemu_GetSystemTimeAsFileTime *)call;
    WINE_TRACE("\n");
    GetSystemTimeAsFileTime(QEMU_G2H(c->time));
}

#endif

struct qemu_GetSystemTimePreciseAsFileTime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME time)
{
    struct qemu_GetSystemTimePreciseAsFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMTIMEPRECISEASFILETIME);
    call.time = (uint64_t)time;

    qemu_syscall(&call.super);
}

#else

void qemu_GetSystemTimePreciseAsFileTime(struct qemu_syscall *call)
{
    struct qemu_GetSystemTimePreciseAsFileTime *c = (struct qemu_GetSystemTimePreciseAsFileTime *)call;
    WINE_TRACE("\n");
    GetSystemTimePreciseAsFileTime(QEMU_G2H(c->time));
}

#endif

struct qemu_GetProcessTimes
{
    struct qemu_syscall super;
    uint64_t hprocess;
    uint64_t lpCreationTime;
    uint64_t lpExitTime;
    uint64_t lpKernelTime;
    uint64_t lpUserTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessTimes(HANDLE hprocess, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime)
{
    struct qemu_GetProcessTimes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSTIMES);
    call.hprocess = (uint64_t)hprocess;
    call.lpCreationTime = (uint64_t)lpCreationTime;
    call.lpExitTime = (uint64_t)lpExitTime;
    call.lpKernelTime = (uint64_t)lpKernelTime;
    call.lpUserTime = (uint64_t)lpUserTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessTimes(struct qemu_syscall *call)
{
    struct qemu_GetProcessTimes *c = (struct qemu_GetProcessTimes *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessTimes(QEMU_G2H(c->hprocess), QEMU_G2H(c->lpCreationTime), QEMU_G2H(c->lpExitTime), QEMU_G2H(c->lpKernelTime), QEMU_G2H(c->lpUserTime));
}

#endif

struct qemu_GetCalendarInfoA
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t Calendar;
    uint64_t CalType;
    uint64_t lpCalData;
    uint64_t cchData;
    uint64_t lpValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetCalendarInfoA(LCID lcid, CALID Calendar, CALTYPE CalType, LPSTR lpCalData, int cchData, LPDWORD lpValue)
{
    struct qemu_GetCalendarInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCALENDARINFOA);
    call.lcid = lcid;
    call.Calendar = Calendar;
    call.CalType = CalType;
    call.lpCalData = (uint64_t)lpCalData;
    call.cchData = cchData;
    call.lpValue = (uint64_t)lpValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCalendarInfoA(struct qemu_syscall *call)
{
    struct qemu_GetCalendarInfoA *c = (struct qemu_GetCalendarInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCalendarInfoA(c->lcid, c->Calendar, c->CalType, QEMU_G2H(c->lpCalData), c->cchData, QEMU_G2H(c->lpValue));
}

#endif

struct qemu_GetCalendarInfoW
{
    struct qemu_syscall super;
    uint64_t Locale;
    uint64_t Calendar;
    uint64_t CalType;
    uint64_t lpCalData;
    uint64_t cchData;
    uint64_t lpValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetCalendarInfoW(LCID Locale, CALID Calendar, CALTYPE CalType, LPWSTR lpCalData, int cchData, LPDWORD lpValue)
{
    struct qemu_GetCalendarInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCALENDARINFOW);
    call.Locale = Locale;
    call.Calendar = Calendar;
    call.CalType = CalType;
    call.lpCalData = (uint64_t)lpCalData;
    call.cchData = cchData;
    call.lpValue = (uint64_t)lpValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCalendarInfoW(struct qemu_syscall *call)
{
    struct qemu_GetCalendarInfoW *c = (struct qemu_GetCalendarInfoW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCalendarInfoW(c->Locale, c->Calendar, c->CalType, QEMU_G2H(c->lpCalData), c->cchData, QEMU_G2H(c->lpValue));
}

#endif

struct qemu_GetCalendarInfoEx
{
    struct qemu_syscall super;
    uint64_t locale;
    uint64_t calendar;
    uint64_t lpReserved;
    uint64_t caltype;
    uint64_t data;
    uint64_t len;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetCalendarInfoEx(LPCWSTR locale, CALID calendar, LPCWSTR lpReserved, CALTYPE caltype, LPWSTR data, int len, DWORD *value)
{
    struct qemu_GetCalendarInfoEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCALENDARINFOEX);
    call.locale = (uint64_t)locale;
    call.calendar = (uint64_t)calendar;
    call.lpReserved = (uint64_t)lpReserved;
    call.caltype = (uint64_t)caltype;
    call.data = (uint64_t)data;
    call.len = (uint64_t)len;
    call.value = (uint64_t)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetCalendarInfoEx to Wine headers? */
extern int WINAPI GetCalendarInfoEx(LPCWSTR locale, CALID calendar, LPCWSTR lpReserved, CALTYPE caltype, LPWSTR data, int len, DWORD *value);
void qemu_GetCalendarInfoEx(struct qemu_syscall *call)
{
    struct qemu_GetCalendarInfoEx *c = (struct qemu_GetCalendarInfoEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCalendarInfoEx(QEMU_G2H(c->locale), c->calendar, QEMU_G2H(c->lpReserved), c->caltype, QEMU_G2H(c->data), c->len, QEMU_G2H(c->value));
}

#endif

struct qemu_SetCalendarInfoA
{
    struct qemu_syscall super;
    uint64_t Locale;
    uint64_t Calendar;
    uint64_t CalType;
    uint64_t lpCalData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SetCalendarInfoA(LCID Locale, CALID Calendar, CALTYPE CalType, LPCSTR lpCalData)
{
    struct qemu_SetCalendarInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCALENDARINFOA);
    call.Locale = (uint64_t)Locale;
    call.Calendar = (uint64_t)Calendar;
    call.CalType = (uint64_t)CalType;
    call.lpCalData = (uint64_t)lpCalData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCalendarInfoA(struct qemu_syscall *call)
{
    struct qemu_SetCalendarInfoA *c = (struct qemu_SetCalendarInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCalendarInfoA(c->Locale, c->Calendar, c->CalType, QEMU_G2H(c->lpCalData));
}

#endif

struct qemu_SetCalendarInfoW
{
    struct qemu_syscall super;
    uint64_t Locale;
    uint64_t Calendar;
    uint64_t CalType;
    uint64_t lpCalData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SetCalendarInfoW(LCID Locale, CALID Calendar, CALTYPE CalType, LPCWSTR lpCalData)
{
    struct qemu_SetCalendarInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCALENDARINFOW);
    call.Locale = (uint64_t)Locale;
    call.Calendar = (uint64_t)Calendar;
    call.CalType = (uint64_t)CalType;
    call.lpCalData = (uint64_t)lpCalData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCalendarInfoW(struct qemu_syscall *call)
{
    struct qemu_SetCalendarInfoW *c = (struct qemu_SetCalendarInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCalendarInfoW(c->Locale, c->Calendar, c->CalType, QEMU_G2H(c->lpCalData));
}

#endif

struct qemu_LocalFileTimeToFileTime
{
    struct qemu_syscall super;
    uint64_t localft;
    uint64_t utcft;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LocalFileTimeToFileTime(const FILETIME *localft, LPFILETIME utcft)
{
    struct qemu_LocalFileTimeToFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALFILETIMETOFILETIME);
    call.localft = (uint64_t)localft;
    call.utcft = (uint64_t)utcft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocalFileTimeToFileTime(struct qemu_syscall *call)
{
    struct qemu_LocalFileTimeToFileTime *c = (struct qemu_LocalFileTimeToFileTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LocalFileTimeToFileTime(QEMU_G2H(c->localft), QEMU_G2H(c->utcft));
}

#endif

struct qemu_FileTimeToLocalFileTime
{
    struct qemu_syscall super;
    uint64_t utcft;
    uint64_t localft;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileTimeToLocalFileTime(const FILETIME *utcft, LPFILETIME localft)
{
    struct qemu_FileTimeToLocalFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILETIMETOLOCALFILETIME);
    call.utcft = (uint64_t)utcft;
    call.localft = (uint64_t)localft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileTimeToLocalFileTime(struct qemu_syscall *call)
{
    struct qemu_FileTimeToLocalFileTime *c = (struct qemu_FileTimeToLocalFileTime *)call;
    WINE_TRACE("\n");
    c->super.iret = FileTimeToLocalFileTime(QEMU_G2H(c->utcft), QEMU_G2H(c->localft));
}

#endif

struct qemu_FileTimeToSystemTime
{
    struct qemu_syscall super;
    uint64_t ft;
    uint64_t syst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileTimeToSystemTime(const FILETIME *ft, LPSYSTEMTIME syst)
{
    struct qemu_FileTimeToSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILETIMETOSYSTEMTIME);
    call.ft = (uint64_t)ft;
    call.syst = (uint64_t)syst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileTimeToSystemTime(struct qemu_syscall *call)
{
    struct qemu_FileTimeToSystemTime *c = (struct qemu_FileTimeToSystemTime *)call;
    WINE_TRACE("\n");
    c->super.iret = FileTimeToSystemTime(QEMU_G2H(c->ft), QEMU_G2H(c->syst));
}

#endif

struct qemu_SystemTimeToFileTime
{
    struct qemu_syscall super;
    uint64_t syst;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SystemTimeToFileTime(const SYSTEMTIME *syst, LPFILETIME ft)
{
    struct qemu_SystemTimeToFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMTIMETOFILETIME);
    call.syst = (uint64_t)syst;
    call.ft = (uint64_t)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SystemTimeToFileTime(struct qemu_syscall *call)
{
    struct qemu_SystemTimeToFileTime *c = (struct qemu_SystemTimeToFileTime *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = SystemTimeToFileTime(QEMU_G2H(c->syst), QEMU_G2H(c->ft));
}

#endif

struct qemu_CompareFileTime
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI CompareFileTime(const FILETIME *x, const FILETIME *y)
{
    struct qemu_CompareFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPAREFILETIME);
    call.x = (uint64_t)x;
    call.y = (uint64_t)y;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareFileTime(struct qemu_syscall *call)
{
    struct qemu_CompareFileTime *c = (struct qemu_CompareFileTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CompareFileTime(QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_GetLocalTime
{
    struct qemu_syscall super;
    uint64_t systime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetLocalTime(LPSYSTEMTIME systime)
{
    struct qemu_GetLocalTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOCALTIME);
    call.systime = (uint64_t)systime;

    qemu_syscall(&call.super);
}

#else

void qemu_GetLocalTime(struct qemu_syscall *call)
{
    struct qemu_GetLocalTime *c = (struct qemu_GetLocalTime *)call;
    WINE_TRACE("\n");
    GetLocalTime(QEMU_G2H(c->systime));
}

#endif

struct qemu_GetSystemTime
{
    struct qemu_syscall super;
    uint64_t systime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GetSystemTime(LPSYSTEMTIME systime)
{
    struct qemu_GetSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMTIME);
    call.systime = (uint64_t)systime;

    qemu_syscall(&call.super);
}

#else

void qemu_GetSystemTime(struct qemu_syscall *call)
{
    struct qemu_GetSystemTime *c = (struct qemu_GetSystemTime *)call;
    WINE_TRACE("\n");
    GetSystemTime(QEMU_G2H(c->systime));
}

#endif

struct qemu_GetDaylightFlag
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDaylightFlag(void)
{
    struct qemu_GetDaylightFlag call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDAYLIGHTFLAG);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetDaylightFlag to Wine headers? */
extern BOOL WINAPI GetDaylightFlag(void);
void qemu_GetDaylightFlag(struct qemu_syscall *call)
{
    struct qemu_GetDaylightFlag *c = (struct qemu_GetDaylightFlag *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDaylightFlag();
}

#endif

struct qemu_DosDateTimeToFileTime
{
    struct qemu_syscall super;
    uint64_t fatdate;
    uint64_t fattime;
    uint64_t ft;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DosDateTimeToFileTime(WORD fatdate, WORD fattime, LPFILETIME ft)
{
    struct qemu_DosDateTimeToFileTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOSDATETIMETOFILETIME);
    call.fatdate = (uint64_t)fatdate;
    call.fattime = (uint64_t)fattime;
    call.ft = (uint64_t)ft;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DosDateTimeToFileTime(struct qemu_syscall *call)
{
    struct qemu_DosDateTimeToFileTime *c = (struct qemu_DosDateTimeToFileTime *)call;
    WINE_TRACE("Unverified!\n");
    c->super.iret = DosDateTimeToFileTime(c->fatdate, c->fattime, QEMU_G2H(c->ft));
}

#endif

struct qemu_FileTimeToDosDateTime
{
    struct qemu_syscall super;
    uint64_t ft;
    uint64_t fatdate;
    uint64_t fattime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FileTimeToDosDateTime(const FILETIME *ft, LPWORD fatdate, LPWORD fattime)
{
    struct qemu_FileTimeToDosDateTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FILETIMETODOSDATETIME);
    call.ft = (uint64_t)ft;
    call.fatdate = (uint64_t)fatdate;
    call.fattime = (uint64_t)fattime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FileTimeToDosDateTime(struct qemu_syscall *call)
{
    struct qemu_FileTimeToDosDateTime *c = (struct qemu_FileTimeToDosDateTime *)call;
    WINE_TRACE("\n");
    c->super.iret = FileTimeToDosDateTime(QEMU_G2H(c->ft), QEMU_G2H(c->fatdate), QEMU_G2H(c->fattime));
}

#endif

struct qemu_GetSystemTimes
{
    struct qemu_syscall super;
    uint64_t lpIdleTime;
    uint64_t lpKernelTime;
    uint64_t lpUserTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSystemTimes(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime)
{
    struct qemu_GetSystemTimes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMTIMES);
    call.lpIdleTime = (uint64_t)lpIdleTime;
    call.lpKernelTime = (uint64_t)lpKernelTime;
    call.lpUserTime = (uint64_t)lpUserTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetSystemTimes to Wine headers? */
extern BOOL WINAPI GetSystemTimes(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime);
void qemu_GetSystemTimes(struct qemu_syscall *call)
{
    struct qemu_GetSystemTimes *c = (struct qemu_GetSystemTimes *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemTimes(QEMU_G2H(c->lpIdleTime), QEMU_G2H(c->lpKernelTime), QEMU_G2H(c->lpUserTime));
}

#endif

struct qemu_GetDynamicTimeZoneInformation
{
    struct qemu_syscall super;
    uint64_t tzinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetDynamicTimeZoneInformation(DYNAMIC_TIME_ZONE_INFORMATION *tzinfo)
{
    struct qemu_GetDynamicTimeZoneInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDYNAMICTIMEZONEINFORMATION);
    call.tzinfo = (uint64_t)tzinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDynamicTimeZoneInformation(struct qemu_syscall *call)
{
    struct qemu_GetDynamicTimeZoneInformation *c = (struct qemu_GetDynamicTimeZoneInformation *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDynamicTimeZoneInformation(QEMU_G2H(c->tzinfo));
}

#endif

struct qemu_QueryThreadCycleTime
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t cycle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryThreadCycleTime(HANDLE thread, PULONG64 cycle)
{
    struct qemu_QueryThreadCycleTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYTHREADCYCLETIME);
    call.thread = (uint64_t)thread;
    call.cycle = (uint64_t)cycle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryThreadCycleTime(struct qemu_syscall *call)
{
    struct qemu_QueryThreadCycleTime *c = (struct qemu_QueryThreadCycleTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryThreadCycleTime(QEMU_G2H(c->thread), QEMU_G2H(c->cycle));
}

#endif

struct qemu_QueryUnbiasedInterruptTime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryUnbiasedInterruptTime(ULONGLONG *time)
{
    struct qemu_QueryUnbiasedInterruptTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYUNBIASEDINTERRUPTTIME);
    call.time = (uint64_t)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add QueryUnbiasedInterruptTime to Wine headers? */
extern BOOL WINAPI QueryUnbiasedInterruptTime(ULONGLONG *time);
void qemu_QueryUnbiasedInterruptTime(struct qemu_syscall *call)
{
    struct qemu_QueryUnbiasedInterruptTime *c = (struct qemu_QueryUnbiasedInterruptTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryUnbiasedInterruptTime(QEMU_G2H(c->time));
}

#endif

