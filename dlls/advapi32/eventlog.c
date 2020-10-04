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

#include <windows.h>
#include <stdio.h>
#include <wct.h>
#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_evntrace.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

struct qemu_BackupEventLogA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupEventLogA(HANDLE hEventLog, LPCSTR lpBackupFileName)
{
    struct qemu_BackupEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPEVENTLOGA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupEventLogA(struct qemu_syscall *call)
{
    struct qemu_BackupEventLogA *c = (struct qemu_BackupEventLogA *)call;
    WINE_TRACE("\n");
    c->super.iret = BackupEventLogA(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_BackupEventLogW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupEventLogW(HANDLE hEventLog, LPCWSTR lpBackupFileName)
{
    struct qemu_BackupEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPEVENTLOGW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupEventLogW(struct qemu_syscall *call)
{
    struct qemu_BackupEventLogW *c = (struct qemu_BackupEventLogW *)call;
    WINE_TRACE("\n");
    c->super.iret = BackupEventLogW(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_ClearEventLogA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClearEventLogA(HANDLE hEventLog, LPCSTR lpBackupFileName)
{
    struct qemu_ClearEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEAREVENTLOGA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClearEventLogA(struct qemu_syscall *call)
{
    struct qemu_ClearEventLogA *c = (struct qemu_ClearEventLogA *)call;
    WINE_TRACE("\n");
    c->super.iret = ClearEventLogA(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_ClearEventLogW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t lpBackupFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClearEventLogW(HANDLE hEventLog, LPCWSTR lpBackupFileName)
{
    struct qemu_ClearEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEAREVENTLOGW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.lpBackupFileName = (ULONG_PTR)lpBackupFileName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClearEventLogW(struct qemu_syscall *call)
{
    struct qemu_ClearEventLogW *c = (struct qemu_ClearEventLogW *)call;
    WINE_TRACE("\n");
    c->super.iret = ClearEventLogW(QEMU_G2H(c->hEventLog), QEMU_G2H(c->lpBackupFileName));
}

#endif

struct qemu_CloseEventLog
{
    struct qemu_syscall super;
    uint64_t hEventLog;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseEventLog(HANDLE hEventLog)
{
    struct qemu_CloseEventLog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEEVENTLOG);
    call.hEventLog = (ULONG_PTR)hEventLog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseEventLog(struct qemu_syscall *call)
{
    struct qemu_CloseEventLog *c = (struct qemu_CloseEventLog *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseEventLog(QEMU_G2H(c->hEventLog));
}

#endif

struct qemu_ControlTrace
{
    struct qemu_syscall super;
    uint64_t hSession;
    uint64_t SessionName;
    uint64_t Properties;
    uint64_t control;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI ControlTraceW(TRACEHANDLE hSession, LPCWSTR SessionName, EVENT_TRACE_PROPERTIES *Properties,
        ULONG control)
{
    struct qemu_ControlTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROLTRACEW);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;
    call.control = (ULONG_PTR)control;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI ULONG WINAPI ControlTraceA(TRACEHANDLE hSession, LPCSTR SessionName, EVENT_TRACE_PROPERTIES *Properties,
        ULONG control)
{
    struct qemu_ControlTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROLTRACEA);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;
    call.control = (ULONG_PTR)control;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ControlTrace(struct qemu_syscall *call)
{
    struct qemu_ControlTrace *c = (struct qemu_ControlTrace *)call;
    EVENT_TRACE_PROPERTIES stack, *props = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HSOT_BIT
    props = QEMU_G2H(c->Properties);
#else
    if (c->Properties)
        EVENT_TRACE_PROPERTIES_g2h(props, QEMU_G2H(c->Properties));
    else
        props = NULL;
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_CONTROLTRACEW))
        c->super.iret = ControlTraceW(c->hSession, QEMU_G2H(c->SessionName), props, c->control);
    else
        c->super.iret = ControlTraceA(c->hSession, QEMU_G2H(c->SessionName), props, c->control);
}

#endif

struct qemu_FlushTrace
{
    struct qemu_syscall super;
    uint64_t hSession;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI FlushTraceA (TRACEHANDLE hSession, LPCSTR SessionName, EVENT_TRACE_PROPERTIES *Properties)
{
    struct qemu_FlushTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHTRACEA);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI ULONG WINAPI FlushTraceW (TRACEHANDLE hSession, LPCWSTR SessionName, EVENT_TRACE_PROPERTIES *Properties)
{
    struct qemu_FlushTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHTRACEW);
    call.hSession = (ULONG_PTR)hSession;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushTrace(struct qemu_syscall *call)
{
    struct qemu_FlushTrace *c = (struct qemu_FlushTrace *)call;
    EVENT_TRACE_PROPERTIES stack, *props = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HSOT_BIT
    props = QEMU_G2H(c->Properties);
#else
    if (c->Properties)
        EVENT_TRACE_PROPERTIES_g2h(props, QEMU_G2H(c->Properties));
    else
        props = NULL;
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_FLUSHTRACEW))
        c->super.iret = FlushTraceW(c->hSession, QEMU_G2H(c->SessionName), props);
    else
        c->super.iret = FlushTraceA(c->hSession, QEMU_G2H(c->SessionName), props);
}

#endif

struct qemu_DeregisterEventSource
{
    struct qemu_syscall super;
    uint64_t hEventLog;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeregisterEventSource(HANDLE hEventLog)
{
    struct qemu_DeregisterEventSource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEREGISTEREVENTSOURCE);
    call.hEventLog = (ULONG_PTR)hEventLog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeregisterEventSource(struct qemu_syscall *call)
{
    struct qemu_DeregisterEventSource *c = (struct qemu_DeregisterEventSource *)call;
    WINE_TRACE("\n");
    c->super.iret = DeregisterEventSource(QEMU_G2H(c->hEventLog));
}

#endif

struct qemu_EnableTraceEx
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t source;
    uint64_t hSession;
    uint64_t enable;
    uint64_t level;
    uint64_t anykeyword;
    uint64_t allkeyword;
    uint64_t enableprop;
    uint64_t filterdesc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnableTraceEx(LPCGUID provider, LPCGUID source, TRACEHANDLE hSession, ULONG enable,
        UCHAR level, ULONGLONG anykeyword, ULONGLONG allkeyword, ULONG enableprop, PEVENT_FILTER_DESCRIPTOR filterdesc)
{
    struct qemu_EnableTraceEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLETRACEEX);
    call.provider = (ULONG_PTR)provider;
    call.source = (ULONG_PTR)source;
    call.hSession = (ULONG_PTR)hSession;
    call.enable = (ULONG_PTR)enable;
    call.level = (ULONG_PTR)level;
    call.anykeyword = (ULONG_PTR)anykeyword;
    call.allkeyword = (ULONG_PTR)allkeyword;
    call.enableprop = (ULONG_PTR)enableprop;
    call.filterdesc = (ULONG_PTR)filterdesc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EnableTraceEx to Wine headers? */
extern ULONG WINAPI EnableTraceEx(LPCGUID provider, LPCGUID source, TRACEHANDLE hSession, ULONG enable, UCHAR level,
        ULONGLONG anykeyword, ULONGLONG allkeyword, ULONG enableprop, PEVENT_FILTER_DESCRIPTOR filterdesc);
void qemu_EnableTraceEx(struct qemu_syscall *call)
{
    struct qemu_EnableTraceEx *c = (struct qemu_EnableTraceEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableTraceEx(QEMU_G2H(c->provider), QEMU_G2H(c->source), c->hSession, c->enable, c->level, c->anykeyword, c->allkeyword, c->enableprop, QEMU_G2H(c->filterdesc));
}

#endif

struct qemu_EnableTraceEx2
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t provider;
    uint64_t control;
    uint64_t level;
    uint64_t match_any;
    uint64_t match_all;
    uint64_t timeout;
    uint64_t params;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnableTraceEx2(TRACEHANDLE handle, LPCGUID provider, ULONG control, UCHAR level,
        ULONGLONG match_any, ULONGLONG match_all, ULONG timeout, PENABLE_TRACE_PARAMETERS params)
{
    struct qemu_EnableTraceEx2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLETRACEEX2);
    call.handle = (ULONG_PTR)handle;
    call.provider = (ULONG_PTR)provider;
    call.control = (ULONG_PTR)control;
    call.level = (ULONG_PTR)level;
    call.match_any = (ULONG_PTR)match_any;
    call.match_all = (ULONG_PTR)match_all;
    call.timeout = (ULONG_PTR)timeout;
    call.params = (ULONG_PTR)params;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableTraceEx2(struct qemu_syscall *call)
{
    struct qemu_EnableTraceEx2 *c = (struct qemu_EnableTraceEx2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnableTraceEx2(c->handle, QEMU_G2H(c->provider), c->control, c->level, c->match_any, c->match_all,
            c->timeout, QEMU_G2H(c->params));
}

#endif

struct qemu_EnableTrace
{
    struct qemu_syscall super;
    uint64_t enable;
    uint64_t flag;
    uint64_t level;
    uint64_t guid;
    uint64_t hSession;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnableTrace(ULONG enable, ULONG flag, ULONG level, LPCGUID guid, TRACEHANDLE hSession)
{
    struct qemu_EnableTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENABLETRACE);
    call.enable = (ULONG_PTR)enable;
    call.flag = (ULONG_PTR)flag;
    call.level = (ULONG_PTR)level;
    call.guid = (ULONG_PTR)guid;
    call.hSession = (ULONG_PTR)hSession;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnableTrace(struct qemu_syscall *call)
{
    struct qemu_EnableTrace *c = (struct qemu_EnableTrace *)call;
    WINE_TRACE("\n");
    c->super.iret = EnableTrace(c->enable, c->flag, c->level, QEMU_G2H(c->guid), c->hSession);
}

#endif

struct qemu_GetEventLogInformation
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t dwInfoLevel;
    uint64_t lpBuffer;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetEventLogInformation(HANDLE hEventLog, DWORD dwInfoLevel, LPVOID lpBuffer, DWORD cbBufSize,
        LPDWORD pcbBytesNeeded)
{
    struct qemu_GetEventLogInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEVENTLOGINFORMATION);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.dwInfoLevel = (ULONG_PTR)dwInfoLevel;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetEventLogInformation(struct qemu_syscall *call)
{
    struct qemu_GetEventLogInformation *c = (struct qemu_GetEventLogInformation *)call;

    /* The only supported info level is EVENTLOG_FULL_INFORMATION, which is a struct that contains 1 DWORD. */
    WINE_TRACE("\n");
    c->super.iret = GetEventLogInformation(QEMU_G2H(c->hEventLog), c->dwInfoLevel, QEMU_G2H(c->lpBuffer),
            c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
}

#endif

struct qemu_GetNumberOfEventLogRecords
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t NumberOfRecords;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumberOfEventLogRecords(HANDLE hEventLog, PDWORD NumberOfRecords)
{
    struct qemu_GetNumberOfEventLogRecords call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMBEROFEVENTLOGRECORDS);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.NumberOfRecords = (ULONG_PTR)NumberOfRecords;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumberOfEventLogRecords(struct qemu_syscall *call)
{
    struct qemu_GetNumberOfEventLogRecords *c = (struct qemu_GetNumberOfEventLogRecords *)call;
    WINE_TRACE("\n");
    c->super.iret = GetNumberOfEventLogRecords(QEMU_G2H(c->hEventLog), QEMU_G2H(c->NumberOfRecords));
}

#endif

struct qemu_GetOldestEventLogRecord
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t OldestRecord;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetOldestEventLogRecord(HANDLE hEventLog, PDWORD OldestRecord)
{
    struct qemu_GetOldestEventLogRecord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOLDESTEVENTLOGRECORD);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.OldestRecord = (ULONG_PTR)OldestRecord;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetOldestEventLogRecord(struct qemu_syscall *call)
{
    struct qemu_GetOldestEventLogRecord *c = (struct qemu_GetOldestEventLogRecord *)call;
    WINE_TRACE("\n");
    c->super.iret = GetOldestEventLogRecord(QEMU_G2H(c->hEventLog), QEMU_G2H(c->OldestRecord));
}

#endif

struct qemu_GetTraceEnableFlags
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI GetTraceEnableFlags(TRACEHANDLE handle)
{
    struct qemu_GetTraceEnableFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRACEENABLEFLAGS);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTraceEnableFlags(struct qemu_syscall *call)
{
    struct qemu_GetTraceEnableFlags *c = (struct qemu_GetTraceEnableFlags *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTraceEnableFlags(c->handle);
}

#endif

struct qemu_GetTraceEnableLevel
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UCHAR WINAPI GetTraceEnableLevel(TRACEHANDLE handle)
{
    struct qemu_GetTraceEnableLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRACEENABLELEVEL);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTraceEnableLevel(struct qemu_syscall *call)
{
    struct qemu_GetTraceEnableLevel *c = (struct qemu_GetTraceEnableLevel *)call;
    WINE_TRACE("\n");
    c->super.iret = GetTraceEnableLevel(c->handle);
}

#endif

struct qemu_GetTraceLoggerHandle
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI GetTraceLoggerHandle(PVOID buf)
{
    struct qemu_GetTraceLoggerHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTRACELOGGERHANDLE);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTraceLoggerHandle(struct qemu_syscall *call)
{
    struct qemu_GetTraceLoggerHandle *c = (struct qemu_GetTraceLoggerHandle *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTraceLoggerHandle(QEMU_G2H(c->buf));
}

#endif

struct qemu_NotifyChangeEventLog
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t hEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI NotifyChangeEventLog(HANDLE hEventLog, HANDLE hEvent)
{
    struct qemu_NotifyChangeEventLog call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYCHANGEEVENTLOG);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.hEvent = (ULONG_PTR)hEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NotifyChangeEventLog(struct qemu_syscall *call)
{
    struct qemu_NotifyChangeEventLog *c = (struct qemu_NotifyChangeEventLog *)call;
    WINE_TRACE("\n");
    c->super.iret = NotifyChangeEventLog(QEMU_G2H(c->hEventLog), QEMU_G2H(c->hEvent));
}

#endif

struct qemu_OpenBackupEventLogA
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenBackupEventLogA(LPCSTR lpUNCServerName, LPCSTR lpFileName)
{
    struct qemu_OpenBackupEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENBACKUPEVENTLOGA);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpFileName = (ULONG_PTR)lpFileName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenBackupEventLogA(struct qemu_syscall *call)
{
    struct qemu_OpenBackupEventLogA *c = (struct qemu_OpenBackupEventLogA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenBackupEventLogA(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpFileName));
}

#endif

struct qemu_OpenBackupEventLogW
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpFileName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenBackupEventLogW(LPCWSTR lpUNCServerName, LPCWSTR lpFileName)
{
    struct qemu_OpenBackupEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENBACKUPEVENTLOGW);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpFileName = (ULONG_PTR)lpFileName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenBackupEventLogW(struct qemu_syscall *call)
{
    struct qemu_OpenBackupEventLogW *c = (struct qemu_OpenBackupEventLogW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenBackupEventLogW(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpFileName));
}

#endif

struct qemu_OpenEventLogA
{
    struct qemu_syscall super;
    uint64_t uncname;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenEventLogA(LPCSTR uncname, LPCSTR source)
{
    struct qemu_OpenEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENEVENTLOGA);
    call.uncname = (ULONG_PTR)uncname;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenEventLogA(struct qemu_syscall *call)
{
    struct qemu_OpenEventLogA *c = (struct qemu_OpenEventLogA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenEventLogA(QEMU_G2H(c->uncname), QEMU_G2H(c->source));
}

#endif

struct qemu_OpenEventLogW
{
    struct qemu_syscall super;
    uint64_t uncname;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenEventLogW(LPCWSTR uncname, LPCWSTR source)
{
    struct qemu_OpenEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENEVENTLOGW);
    call.uncname = (ULONG_PTR)uncname;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenEventLogW(struct qemu_syscall *call)
{
    struct qemu_OpenEventLogW *c = (struct qemu_OpenEventLogW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenEventLogW(QEMU_G2H(c->uncname), QEMU_G2H(c->source));
}

#endif

struct qemu_QueryAllTracesW
{
    struct qemu_syscall super;
    uint64_t parray;
    uint64_t arraycount;
    uint64_t psessioncount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI QueryAllTracesW(PEVENT_TRACE_PROPERTIES * parray, ULONG arraycount, PULONG psessioncount)
{
    struct qemu_QueryAllTracesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYALLTRACESW);
    call.parray = (ULONG_PTR)parray;
    call.arraycount = (ULONG_PTR)arraycount;
    call.psessioncount = (ULONG_PTR)psessioncount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryAllTracesW(struct qemu_syscall *call)
{
    struct qemu_QueryAllTracesW *c = (struct qemu_QueryAllTracesW *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryAllTracesW(QEMU_G2H(c->parray), c->arraycount, QEMU_G2H(c->psessioncount));
}

#endif

struct qemu_QueryAllTracesA
{
    struct qemu_syscall super;
    uint64_t parray;
    uint64_t arraycount;
    uint64_t psessioncount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI QueryAllTracesA(PEVENT_TRACE_PROPERTIES * parray, ULONG arraycount, PULONG psessioncount)
{
    struct qemu_QueryAllTracesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYALLTRACESA);
    call.parray = (ULONG_PTR)parray;
    call.arraycount = (ULONG_PTR)arraycount;
    call.psessioncount = (ULONG_PTR)psessioncount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryAllTracesA(struct qemu_syscall *call)
{
    struct qemu_QueryAllTracesA *c = (struct qemu_QueryAllTracesA *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryAllTracesA(QEMU_G2H(c->parray), c->arraycount, QEMU_G2H(c->psessioncount));
}

#endif

struct qemu_ReadEventLogA
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t dwReadFlags;
    uint64_t dwRecordOffset;
    uint64_t lpBuffer;
    uint64_t nNumberOfBytesToRead;
    uint64_t pnBytesRead;
    uint64_t pnMinNumberOfBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadEventLogA(HANDLE hEventLog, DWORD dwReadFlags, DWORD dwRecordOffset, LPVOID lpBuffer,
        DWORD nNumberOfBytesToRead, DWORD *pnBytesRead, DWORD *pnMinNumberOfBytesNeeded)
{
    struct qemu_ReadEventLogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READEVENTLOGA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.dwReadFlags = (ULONG_PTR)dwReadFlags;
    call.dwRecordOffset = (ULONG_PTR)dwRecordOffset;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.nNumberOfBytesToRead = (ULONG_PTR)nNumberOfBytesToRead;
    call.pnBytesRead = (ULONG_PTR)pnBytesRead;
    call.pnMinNumberOfBytesNeeded = (ULONG_PTR)pnMinNumberOfBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadEventLogA(struct qemu_syscall *call)
{
    struct qemu_ReadEventLogA *c = (struct qemu_ReadEventLogA *)call;
    WINE_FIXME("Unverified!\n");
    /* At the time of the writing of this comment this function is a stub in Wine. */
    c->super.iret = ReadEventLogA(QEMU_G2H(c->hEventLog), c->dwReadFlags, c->dwRecordOffset, QEMU_G2H(c->lpBuffer),
            c->nNumberOfBytesToRead, QEMU_G2H(c->pnBytesRead), QEMU_G2H(c->pnMinNumberOfBytesNeeded));
}

#endif

struct qemu_ReadEventLogW
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t dwReadFlags;
    uint64_t dwRecordOffset;
    uint64_t lpBuffer;
    uint64_t nNumberOfBytesToRead;
    uint64_t pnBytesRead;
    uint64_t pnMinNumberOfBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadEventLogW(HANDLE hEventLog, DWORD dwReadFlags, DWORD dwRecordOffset, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, DWORD *pnBytesRead, DWORD *pnMinNumberOfBytesNeeded)
{
    struct qemu_ReadEventLogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READEVENTLOGW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.dwReadFlags = (ULONG_PTR)dwReadFlags;
    call.dwRecordOffset = (ULONG_PTR)dwRecordOffset;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.nNumberOfBytesToRead = (ULONG_PTR)nNumberOfBytesToRead;
    call.pnBytesRead = (ULONG_PTR)pnBytesRead;
    call.pnMinNumberOfBytesNeeded = (ULONG_PTR)pnMinNumberOfBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadEventLogW(struct qemu_syscall *call)
{
    struct qemu_ReadEventLogW *c = (struct qemu_ReadEventLogW *)call;
    WINE_FIXME("Unverified!\n");
    /* At the time of the writing of this comment this function is a stub in Wine. */
    c->super.iret = ReadEventLogW(QEMU_G2H(c->hEventLog), c->dwReadFlags, c->dwRecordOffset, QEMU_G2H(c->lpBuffer),
            c->nNumberOfBytesToRead, QEMU_G2H(c->pnBytesRead), QEMU_G2H(c->pnMinNumberOfBytesNeeded));
}

#endif

struct qemu_RegisterEventSourceA
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpSourceName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RegisterEventSourceA(LPCSTR lpUNCServerName, LPCSTR lpSourceName)
{
    struct qemu_RegisterEventSourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTEREVENTSOURCEA);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpSourceName = (ULONG_PTR)lpSourceName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterEventSourceA(struct qemu_syscall *call)
{
    struct qemu_RegisterEventSourceA *c = (struct qemu_RegisterEventSourceA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RegisterEventSourceA(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpSourceName));
}

#endif

struct qemu_RegisterEventSourceW
{
    struct qemu_syscall super;
    uint64_t lpUNCServerName;
    uint64_t lpSourceName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RegisterEventSourceW(LPCWSTR lpUNCServerName, LPCWSTR lpSourceName)
{
    struct qemu_RegisterEventSourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTEREVENTSOURCEW);
    call.lpUNCServerName = (ULONG_PTR)lpUNCServerName;
    call.lpSourceName = (ULONG_PTR)lpSourceName;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterEventSourceW(struct qemu_syscall *call)
{
    struct qemu_RegisterEventSourceW *c = (struct qemu_RegisterEventSourceW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RegisterEventSourceW(QEMU_G2H(c->lpUNCServerName), QEMU_G2H(c->lpSourceName));
}

#endif

struct qemu_ReportEvent
{
    struct qemu_syscall super;
    uint64_t hEventLog;
    uint64_t wType;
    uint64_t wCategory;
    uint64_t dwEventID;
    uint64_t lpUserSid;
    uint64_t wNumStrings;
    uint64_t dwDataSize;
    uint64_t lpStrings;
    uint64_t lpRawData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReportEventW(HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid,
        WORD wNumStrings, DWORD dwDataSize, LPCWSTR *lpStrings, LPVOID lpRawData)
{
    struct qemu_ReportEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPORTEVENTW);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.wType = (ULONG_PTR)wType;
    call.wCategory = (ULONG_PTR)wCategory;
    call.dwEventID = (ULONG_PTR)dwEventID;
    call.lpUserSid = (ULONG_PTR)lpUserSid;
    call.wNumStrings = (ULONG_PTR)wNumStrings;
    call.dwDataSize = (ULONG_PTR)dwDataSize;
    call.lpStrings = (ULONG_PTR)lpStrings;
    call.lpRawData = (ULONG_PTR)lpRawData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI ReportEventA (HANDLE hEventLog, WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid,
        WORD wNumStrings, DWORD dwDataSize, LPCSTR *lpStrings, LPVOID lpRawData)
{
    struct qemu_ReportEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REPORTEVENTA);
    call.hEventLog = (ULONG_PTR)hEventLog;
    call.wType = (ULONG_PTR)wType;
    call.wCategory = (ULONG_PTR)wCategory;
    call.dwEventID = (ULONG_PTR)dwEventID;
    call.lpUserSid = (ULONG_PTR)lpUserSid;
    call.wNumStrings = (ULONG_PTR)wNumStrings;
    call.dwDataSize = (ULONG_PTR)dwDataSize;
    call.lpStrings = (ULONG_PTR)lpStrings;
    call.lpRawData = (ULONG_PTR)lpRawData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReportEvent(struct qemu_syscall *call)
{
    struct qemu_ReportEvent *c = (struct qemu_ReportEvent *)call;
    WCHAR **strings;
    qemu_ptr *strings32;
    WORD i;

    /* This function is a semi-stub in Wine, so the wrapper is poorly tested. */
    WINE_WARN("\n");

#if GUEST_BIT == HOST_BIT
    strings = QEMU_G2H(c->lpStrings);
#else
    strings32 = QEMU_G2H(c->lpStrings);
    if (strings32)
    {
        strings = HeapAlloc(GetProcessHeap(), 0, sizeof(*strings) * c->wNumStrings);
        if (!strings)
        {
            WINE_ERR("Out of memory\n");
            c->super.iret = 0;
            return;
        }

        for (i = 0; i < c->wNumStrings; ++i)
            strings[i] = (WCHAR *)(ULONG_PTR)strings32[i];
    }
    else
    {
        strings = NULL;
    }
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_REPORTEVENTW))
    {
        c->super.iret = ReportEventW(QEMU_G2H(c->hEventLog), c->wType, c->wCategory, c->dwEventID,
                QEMU_G2H(c->lpUserSid), c->wNumStrings, c->dwDataSize, (const WCHAR **)strings,
                QEMU_G2H(c->lpRawData));
    }
    else
    {
        c->super.iret = ReportEventA(QEMU_G2H(c->hEventLog), c->wType, c->wCategory, c->dwEventID,
                QEMU_G2H(c->lpUserSid), c->wNumStrings, c->dwDataSize, (const char **)strings,
                QEMU_G2H(c->lpRawData));
    }

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, strings);
#endif
}

#endif

struct qemu_StartTraceW
{
    struct qemu_syscall super;
    uint64_t pSessionHandle;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StartTraceW(TRACEHANDLE *pSessionHandle, LPCWSTR SessionName, PEVENT_TRACE_PROPERTIES Properties)
{
    struct qemu_StartTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTTRACEW);
    call.pSessionHandle = (ULONG_PTR)pSessionHandle;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS && pSessionHandle)
        *pSessionHandle = (TRACEHANDLE)(ULONG_PTR)call.pSessionHandle;

    return call.super.iret;
}

#else

void qemu_StartTraceW(struct qemu_syscall *call)
{
    struct qemu_StartTraceW *c = (struct qemu_StartTraceW *)call;
    TRACEHANDLE handle;

    /* At the time of the writing of this comment this function is a semi-stub in Wine. */
    WINE_WARN("\n");

    c->super.iret = StartTraceW(c->pSessionHandle ? &handle : NULL, QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties));
    c->pSessionHandle = QEMU_H2G(handle);
}

#endif

struct qemu_StartTraceA
{
    struct qemu_syscall super;
    uint64_t pSessionHandle;
    uint64_t SessionName;
    uint64_t Properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StartTraceA(PTRACEHANDLE pSessionHandle, LPCSTR SessionName, PEVENT_TRACE_PROPERTIES Properties)
{
    struct qemu_StartTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTTRACEA);
    call.pSessionHandle = (ULONG_PTR)pSessionHandle;
    call.SessionName = (ULONG_PTR)SessionName;
    call.Properties = (ULONG_PTR)Properties;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS && pSessionHandle)
        *pSessionHandle = (TRACEHANDLE)(ULONG_PTR)call.pSessionHandle;

    return call.super.iret;
}

#else

void qemu_StartTraceA(struct qemu_syscall *call)
{
    struct qemu_StartTraceA *c = (struct qemu_StartTraceA *)call;
    TRACEHANDLE handle;

    /* At the time of the writing of this comment this function is a semi-stub in Wine. */
    WINE_WARN("\n");

    c->super.iret = StartTraceA(c->pSessionHandle ? &handle : NULL, QEMU_G2H(c->SessionName), QEMU_G2H(c->Properties));
    c->pSessionHandle = QEMU_H2G(handle);
}

#endif

struct qemu_StopTraceW
{
    struct qemu_syscall super;
    uint64_t session;
    uint64_t session_name;
    uint64_t properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StopTraceW(TRACEHANDLE session, LPCWSTR session_name, PEVENT_TRACE_PROPERTIES properties)
{
    struct qemu_StopTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STOPTRACEW);
    call.session = (ULONG_PTR)session;
    call.session_name = (ULONG_PTR)session_name;
    call.properties = (ULONG_PTR)properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StopTraceW to Wine headers? */
extern ULONG WINAPI StopTraceW(TRACEHANDLE session, LPCWSTR session_name, PEVENT_TRACE_PROPERTIES properties);
void qemu_StopTraceW(struct qemu_syscall *call)
{
    struct qemu_StopTraceW *c = (struct qemu_StopTraceW *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = StopTraceW(c->session, QEMU_G2H(c->session_name), QEMU_G2H(c->properties));
}

#endif

struct qemu_StopTraceA
{
    struct qemu_syscall super;
    uint64_t session;
    uint64_t session_name;
    uint64_t properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI StopTraceA(TRACEHANDLE session, LPCSTR session_name, PEVENT_TRACE_PROPERTIES properties)
{
    struct qemu_StopTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STOPTRACEA);
    call.session = (ULONG_PTR)session;
    call.session_name = (ULONG_PTR)session_name;
    call.properties = (ULONG_PTR)properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add StopTraceA to Wine headers? */
extern ULONG WINAPI StopTraceA(TRACEHANDLE session, LPCSTR session_name, PEVENT_TRACE_PROPERTIES properties);
void qemu_StopTraceA(struct qemu_syscall *call)
{
    struct qemu_StopTraceA *c = (struct qemu_StopTraceA *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = StopTraceA(c->session, QEMU_G2H(c->session_name), QEMU_G2H(c->properties));
}

#endif

struct qemu_TraceEvent
{
    struct qemu_syscall super;
    uint64_t SessionHandle;
    uint64_t EventTrace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI TraceEvent(TRACEHANDLE SessionHandle, PEVENT_TRACE_HEADER EventTrace)
{
    struct qemu_TraceEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACEEVENT);
    call.SessionHandle = (ULONG_PTR)SessionHandle;
    call.EventTrace = (ULONG_PTR)EventTrace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TraceEvent(struct qemu_syscall *call)
{
    struct qemu_TraceEvent *c = (struct qemu_TraceEvent *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = TraceEvent(c->SessionHandle, QEMU_G2H(c->EventTrace));
}

#endif

struct qemu_QueryTraceW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t sessionname;
    uint64_t properties;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI QueryTraceW(TRACEHANDLE handle, LPCWSTR sessionname, PEVENT_TRACE_PROPERTIES properties)
{
    struct qemu_QueryTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYTRACEW);
    call.handle = (ULONG_PTR)handle;
    call.sessionname = (ULONG_PTR)sessionname;
    call.properties = (ULONG_PTR)properties;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add QueryTraceW to Wine headers? */
extern ULONG WINAPI QueryTraceW(TRACEHANDLE handle, LPCWSTR sessionname, PEVENT_TRACE_PROPERTIES properties);
void qemu_QueryTraceW(struct qemu_syscall *call)
{
    struct qemu_QueryTraceW *c = (struct qemu_QueryTraceW *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryTraceW(c->handle, QEMU_G2H(c->sessionname), QEMU_G2H(c->properties));
}

#endif

struct qemu_OpenTraceA
{
    struct qemu_syscall super;
    uint64_t logfile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI OpenTraceA(PEVENT_TRACE_LOGFILEA logfile)
{
    struct qemu_OpenTraceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENTRACEA);
    call.logfile = (ULONG_PTR)logfile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add OpenTraceA to Wine headers? */
extern TRACEHANDLE WINAPI OpenTraceA(PEVENT_TRACE_LOGFILEA logfile);
void qemu_OpenTraceA(struct qemu_syscall *call)
{
    struct qemu_OpenTraceA *c = (struct qemu_OpenTraceA *)call;
    /* At the time of the writing of this comment this function is a stub in Wine, with a silenced FIXME. */
    WINE_WARN("Unverified!\n");
    c->super.iret = OpenTraceA(QEMU_G2H(c->logfile));
}

#endif

struct qemu_OpenTraceW
{
    struct qemu_syscall super;
    uint64_t logfile;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI OpenTraceW(PEVENT_TRACE_LOGFILEW logfile)
{
    struct qemu_OpenTraceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENTRACEW);
    call.logfile = (ULONG_PTR)logfile;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add OpenTraceW to Wine headers? */
extern TRACEHANDLE WINAPI OpenTraceW(PEVENT_TRACE_LOGFILEW logfile);
void qemu_OpenTraceW(struct qemu_syscall *call)
{
    struct qemu_OpenTraceW *c = (struct qemu_OpenTraceW *)call;
    /* At the time of the writing of this comment this function is a stub in Wine, with a silenced FIXME. */
    WINE_WARN("Unverified!\n");
    c->super.iret = OpenTraceW(QEMU_G2H(c->logfile));
}

#endif

struct qemu_ProcessTrace
{
    struct qemu_syscall super;
    uint64_t HandleArray;
    uint64_t HandleCount;
    uint64_t StartTime;
    uint64_t EndTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI ProcessTrace(PTRACEHANDLE HandleArray, ULONG HandleCount, LPFILETIME StartTime, LPFILETIME EndTime)
{
    struct qemu_ProcessTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESSTRACE);
    call.HandleArray = (ULONG_PTR)HandleArray;
    call.HandleCount = (ULONG_PTR)HandleCount;
    call.StartTime = (ULONG_PTR)StartTime;
    call.EndTime = (ULONG_PTR)EndTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ProcessTrace to Wine headers? */
extern ULONG WINAPI ProcessTrace(PTRACEHANDLE HandleArray, ULONG HandleCount, LPFILETIME StartTime, LPFILETIME EndTime);
void qemu_ProcessTrace(struct qemu_syscall *call)
{
    struct qemu_ProcessTrace *c = (struct qemu_ProcessTrace *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = ProcessTrace(QEMU_G2H(c->HandleArray), c->HandleCount, QEMU_G2H(c->StartTime), QEMU_G2H(c->EndTime));
}

#endif

struct qemu_TraceMessageVa
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
    uint64_t guid;
    uint64_t number;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

ULONG WINAPI advapi32_TraceMessageVa(TRACEHANDLE handle, ULONG flags, LPCGUID guid, USHORT number, va_list args)
{
    struct qemu_TraceMessageVa call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRACEMESSAGEVA);
    call.handle = (ULONG_PTR)handle;
    call.flags = (ULONG_PTR)flags;
    call.guid = (ULONG_PTR)guid;
    call.number = (ULONG_PTR)number;

    qemu_syscall(&call.super);

    return call.super.iret;
}

ULONG WINAPIV TraceMessage(TRACEHANDLE handle, ULONG flags, LPCGUID guid, USHORT number, ...)
{
    va_list valist;
    ULONG ret;

    va_start( valist, number );
    ret = advapi32_TraceMessageVa( handle, flags, guid, number, valist );
    va_end( valist );
    return ret;
}

#else

void qemu_TraceMessageVa(struct qemu_syscall *call)
{
    struct qemu_TraceMessageVa *c = (struct qemu_TraceMessageVa *)call;
    /* Just FYI, this is also a stub in Wine, so don't worry too much. */
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif

struct qemu_CloseTrace
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI CloseTrace(TRACEHANDLE handle)
{
    struct qemu_CloseTrace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSETRACE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseTrace(struct qemu_syscall *call)
{
    struct qemu_CloseTrace *c = (struct qemu_CloseTrace *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseTrace(c->handle);
}

#endif

struct qemu_EnumerateTraceGuids
{
    struct qemu_syscall super;
    uint64_t propertiesarray;
    uint64_t arraycount;
    uint64_t guidcount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EnumerateTraceGuids(PTRACE_GUID_PROPERTIES *propertiesarray, ULONG arraycount, PULONG guidcount)
{
    struct qemu_EnumerateTraceGuids call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMERATETRACEGUIDS);
    call.propertiesarray = (ULONG_PTR)propertiesarray;
    call.arraycount = (ULONG_PTR)arraycount;
    call.guidcount = (ULONG_PTR)guidcount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EnumerateTraceGuids to Wine headers? */
extern ULONG WINAPI EnumerateTraceGuids(PTRACE_GUID_PROPERTIES *propertiesarray, ULONG arraycount, PULONG guidcount);
void qemu_EnumerateTraceGuids(struct qemu_syscall *call)
{
    struct qemu_EnumerateTraceGuids *c = (struct qemu_EnumerateTraceGuids *)call;
    /* At the time of the writing of this comment this function is a stub in Wine. */
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumerateTraceGuids(QEMU_G2H(c->propertiesarray), c->arraycount, QEMU_G2H(c->guidcount));
}

#endif

