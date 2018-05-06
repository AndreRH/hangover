/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_RtlTimeToTimeFields
{
    struct qemu_syscall super;
    uint64_t liTime;
    uint64_t TimeFields;
};

#ifdef QEMU_DLL_GUEST

typedef void *PTIME_FIELDS, *PRTL_TIME_ZONE_INFORMATION, *RTL_DYNAMIC_TIME_ZONE_INFORMATION;

WINBASEAPI VOID WINAPI RtlTimeToTimeFields(const LARGE_INTEGER *liTime, PTIME_FIELDS TimeFields)
{
    struct qemu_RtlTimeToTimeFields call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTIMETOTIMEFIELDS);
    call.liTime = (ULONG_PTR)liTime;
    call.TimeFields = (ULONG_PTR)TimeFields;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlTimeToTimeFields(struct qemu_syscall *call)
{
    struct qemu_RtlTimeToTimeFields *c = (struct qemu_RtlTimeToTimeFields *)call;
    WINE_FIXME("Unverified!\n");
    RtlTimeToTimeFields(QEMU_G2H(c->liTime), QEMU_G2H(c->TimeFields));
}

#endif

struct qemu_RtlTimeFieldsToTime
{
    struct qemu_syscall super;
    uint64_t tfTimeFields;
    uint64_t Time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlTimeFieldsToTime(PTIME_FIELDS tfTimeFields, PLARGE_INTEGER Time)
{
    struct qemu_RtlTimeFieldsToTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTIMEFIELDSTOTIME);
    call.tfTimeFields = (ULONG_PTR)tfTimeFields;
    call.Time = (ULONG_PTR)Time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlTimeFieldsToTime(struct qemu_syscall *call)
{
    struct qemu_RtlTimeFieldsToTime *c = (struct qemu_RtlTimeFieldsToTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlTimeFieldsToTime(QEMU_G2H(c->tfTimeFields), QEMU_G2H(c->Time));
}

#endif

struct qemu_RtlLocalTimeToSystemTime
{
    struct qemu_syscall super;
    uint64_t LocalTime;
    uint64_t SystemTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlLocalTimeToSystemTime(LARGE_INTEGER *LocalTime, PLARGE_INTEGER SystemTime)
{
    struct qemu_RtlLocalTimeToSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLOCALTIMETOSYSTEMTIME);
    call.LocalTime = (ULONG_PTR)LocalTime;
    call.SystemTime = (ULONG_PTR)SystemTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLocalTimeToSystemTime(struct qemu_syscall *call)
{
    struct qemu_RtlLocalTimeToSystemTime *c = (struct qemu_RtlLocalTimeToSystemTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlLocalTimeToSystemTime(QEMU_G2H(c->LocalTime), QEMU_G2H(c->SystemTime));
}

#endif

struct qemu_RtlSystemTimeToLocalTime
{
    struct qemu_syscall super;
    uint64_t SystemTime;
    uint64_t LocalTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSystemTimeToLocalTime(const LARGE_INTEGER *SystemTime, PLARGE_INTEGER LocalTime)
{
    struct qemu_RtlSystemTimeToLocalTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSYSTEMTIMETOLOCALTIME);
    call.SystemTime = (ULONG_PTR)SystemTime;
    call.LocalTime = (ULONG_PTR)LocalTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSystemTimeToLocalTime(struct qemu_syscall *call)
{
    struct qemu_RtlSystemTimeToLocalTime *c = (struct qemu_RtlSystemTimeToLocalTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSystemTimeToLocalTime(QEMU_G2H(c->SystemTime), QEMU_G2H(c->LocalTime));
}

#endif

struct qemu_RtlTimeToSecondsSince1970
{
    struct qemu_syscall super;
    uint64_t Time;
    uint64_t Seconds;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlTimeToSecondsSince1970(LARGE_INTEGER *Time, LPDWORD Seconds)
{
    struct qemu_RtlTimeToSecondsSince1970 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTIMETOSECONDSSINCE1970);
    call.Time = (ULONG_PTR)Time;
    call.Seconds = (ULONG_PTR)Seconds;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlTimeToSecondsSince1970(struct qemu_syscall *call)
{
    struct qemu_RtlTimeToSecondsSince1970 *c = (struct qemu_RtlTimeToSecondsSince1970 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlTimeToSecondsSince1970(QEMU_G2H(c->Time), QEMU_G2H(c->Seconds));
}

#endif

struct qemu_RtlTimeToSecondsSince1980
{
    struct qemu_syscall super;
    uint64_t Time;
    uint64_t Seconds;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlTimeToSecondsSince1980(const LARGE_INTEGER *Time, LPDWORD Seconds)
{
    struct qemu_RtlTimeToSecondsSince1980 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTIMETOSECONDSSINCE1980);
    call.Time = (ULONG_PTR)Time;
    call.Seconds = (ULONG_PTR)Seconds;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlTimeToSecondsSince1980(struct qemu_syscall *call)
{
    struct qemu_RtlTimeToSecondsSince1980 *c = (struct qemu_RtlTimeToSecondsSince1980 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlTimeToSecondsSince1980(QEMU_G2H(c->Time), QEMU_G2H(c->Seconds));
}

#endif

struct qemu_RtlSecondsSince1970ToTime
{
    struct qemu_syscall super;
    uint64_t Seconds;
    uint64_t Time;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlSecondsSince1970ToTime(DWORD Seconds, LARGE_INTEGER *Time)
{
    struct qemu_RtlSecondsSince1970ToTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSECONDSSINCE1970TOTIME);
    call.Seconds = Seconds;
    call.Time = (ULONG_PTR)Time;
    call.size = sizeof(LARGE_INTEGER);

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSecondsSince1970ToTime(struct qemu_syscall *call)
{
    struct qemu_RtlSecondsSince1970ToTime *c = (struct qemu_RtlSecondsSince1970ToTime *)call;
    WINE_TRACE("\n");
    RtlSecondsSince1970ToTime(c->Seconds, QEMU_G2H(c->Time));
}

#endif

struct qemu_RtlSecondsSince1980ToTime
{
    struct qemu_syscall super;
    uint64_t Seconds;
    uint64_t Time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlSecondsSince1980ToTime(DWORD Seconds, LARGE_INTEGER *Time)
{
    struct qemu_RtlSecondsSince1980ToTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSECONDSSINCE1980TOTIME);
    call.Seconds = Seconds;
    call.Time = (ULONG_PTR)Time;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSecondsSince1980ToTime(struct qemu_syscall *call)
{
    struct qemu_RtlSecondsSince1980ToTime *c = (struct qemu_RtlSecondsSince1980ToTime *)call;
    WINE_FIXME("Unverified!\n");
    RtlSecondsSince1980ToTime(c->Seconds, QEMU_G2H(c->Time));
}

#endif

struct qemu_RtlTimeToElapsedTimeFields
{
    struct qemu_syscall super;
    uint64_t Time;
    uint64_t TimeFields;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlTimeToElapsedTimeFields(const LARGE_INTEGER *Time, PTIME_FIELDS TimeFields)
{
    struct qemu_RtlTimeToElapsedTimeFields call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTIMETOELAPSEDTIMEFIELDS);
    call.Time = (ULONG_PTR)Time;
    call.TimeFields = (ULONG_PTR)TimeFields;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlTimeToElapsedTimeFields(struct qemu_syscall *call)
{
    struct qemu_RtlTimeToElapsedTimeFields *c = (struct qemu_RtlTimeToElapsedTimeFields *)call;
    WINE_FIXME("Unverified!\n");
    RtlTimeToElapsedTimeFields(QEMU_G2H(c->Time), QEMU_G2H(c->TimeFields));
}

#endif

struct qemu_NtQuerySystemTime
{
    struct qemu_syscall super;
    uint64_t Time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySystemTime(PLARGE_INTEGER Time)
{
    struct qemu_NtQuerySystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSYSTEMTIME);
    call.Time = (ULONG_PTR)Time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySystemTime(struct qemu_syscall *call)
{
    struct qemu_NtQuerySystemTime *c = (struct qemu_NtQuerySystemTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySystemTime(QEMU_G2H(c->Time));
}

#endif

struct qemu_NtQueryPerformanceCounter
{
    struct qemu_syscall super;
    uint64_t counter;
    uint64_t frequency;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryPerformanceCounter(LARGE_INTEGER *counter, LARGE_INTEGER *frequency)
{
    struct qemu_NtQueryPerformanceCounter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYPERFORMANCECOUNTER);
    call.counter = (ULONG_PTR)counter;
    call.frequency = (ULONG_PTR)frequency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryPerformanceCounter(struct qemu_syscall *call)
{
    struct qemu_NtQueryPerformanceCounter *c = (struct qemu_NtQueryPerformanceCounter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryPerformanceCounter(QEMU_G2H(c->counter), QEMU_G2H(c->frequency));
}

#endif

struct qemu_NtGetTickCount
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI NtGetTickCount(void)
{
    struct qemu_NtGetTickCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTGETTICKCOUNT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtGetTickCount(struct qemu_syscall *call)
{
    struct qemu_NtGetTickCount *c = (struct qemu_NtGetTickCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtGetTickCount();
}

#endif

struct qemu_RtlQueryTimeZoneInformation
{
    struct qemu_syscall super;
    uint64_t ret;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueryTimeZoneInformation(PRTL_TIME_ZONE_INFORMATION ret)
{
    struct qemu_RtlQueryTimeZoneInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYTIMEZONEINFORMATION);
    call.ret = (ULONG_PTR)ret;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryTimeZoneInformation(struct qemu_syscall *call)
{
    struct qemu_RtlQueryTimeZoneInformation *c = (struct qemu_RtlQueryTimeZoneInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlQueryTimeZoneInformation(QEMU_G2H(c->ret));
}

#endif

struct qemu_RtlQueryDynamicTimeZoneInformation
{
    struct qemu_syscall super;
    uint64_t tzinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueryDynamicTimeZoneInformation(RTL_DYNAMIC_TIME_ZONE_INFORMATION *tzinfo)
{
    struct qemu_RtlQueryDynamicTimeZoneInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYDYNAMICTIMEZONEINFORMATION);
    call.tzinfo = (ULONG_PTR)tzinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryDynamicTimeZoneInformation(struct qemu_syscall *call)
{
    struct qemu_RtlQueryDynamicTimeZoneInformation *c = (struct qemu_RtlQueryDynamicTimeZoneInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlQueryDynamicTimeZoneInformation(QEMU_G2H(c->tzinfo));
}

#endif

struct qemu_RtlSetTimeZoneInformation
{
    struct qemu_syscall super;
    uint64_t tzinfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetTimeZoneInformation(const PRTL_TIME_ZONE_INFORMATION tzinfo)
{
    struct qemu_RtlSetTimeZoneInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETTIMEZONEINFORMATION);
    call.tzinfo = (ULONG_PTR)tzinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetTimeZoneInformation(struct qemu_syscall *call)
{
    struct qemu_RtlSetTimeZoneInformation *c = (struct qemu_RtlSetTimeZoneInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetTimeZoneInformation(QEMU_G2H(c->tzinfo));
}

#endif

struct qemu_NtSetSystemTime
{
    struct qemu_syscall super;
    uint64_t NewTime;
    uint64_t OldTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetSystemTime(const LARGE_INTEGER *NewTime, LARGE_INTEGER *OldTime)
{
    struct qemu_NtSetSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETSYSTEMTIME);
    call.NewTime = (ULONG_PTR)NewTime;
    call.OldTime = (ULONG_PTR)OldTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetSystemTime(struct qemu_syscall *call)
{
    struct qemu_NtSetSystemTime *c = (struct qemu_NtSetSystemTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetSystemTime(QEMU_G2H(c->NewTime), QEMU_G2H(c->OldTime));
}

#endif

struct qemu_RtlQueryUnbiasedInterruptTime
{
    struct qemu_syscall super;
    uint64_t time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueryUnbiasedInterruptTime(ULONGLONG *time)
{
    struct qemu_RtlQueryUnbiasedInterruptTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYUNBIASEDINTERRUPTTIME);
    call.time = (ULONG_PTR)time;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryUnbiasedInterruptTime(struct qemu_syscall *call)
{
    struct qemu_RtlQueryUnbiasedInterruptTime *c = (struct qemu_RtlQueryUnbiasedInterruptTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlQueryUnbiasedInterruptTime(QEMU_G2H(c->time));
}

#endif

