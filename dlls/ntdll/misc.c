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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>
#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif


struct qemu_WinSqmEndSession
{
    struct qemu_syscall super;
    uint64_t session;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI WinSqmEndSession(HANDLE session)
{
    struct qemu_WinSqmEndSession call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINSQMENDSESSION);
    call.session = (ULONG_PTR)session;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WinSqmEndSession to Wine headers? */
extern NTSTATUS WINAPI WinSqmEndSession(HANDLE session);
void qemu_WinSqmEndSession(struct qemu_syscall *call)
{
    struct qemu_WinSqmEndSession *c = (struct qemu_WinSqmEndSession *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WinSqmEndSession(QEMU_G2H(c->session));
}

#endif

struct qemu_WinSqmIsOptedIn
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WinSqmIsOptedIn(void)
{
    struct qemu_WinSqmIsOptedIn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINSQMISOPTEDIN);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WinSqmIsOptedIn to Wine headers? */
extern BOOL WINAPI WinSqmIsOptedIn(void);
void qemu_WinSqmIsOptedIn(struct qemu_syscall *call)
{
    struct qemu_WinSqmIsOptedIn *c = (struct qemu_WinSqmIsOptedIn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WinSqmIsOptedIn();
}

#endif

struct qemu_WinSqmStartSession
{
    struct qemu_syscall super;
    uint64_t sessionguid;
    uint64_t sessionid;
    uint64_t unknown1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WinSqmStartSession(GUID *sessionguid, DWORD sessionid, DWORD unknown1)
{
    struct qemu_WinSqmStartSession call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINSQMSTARTSESSION);
    call.sessionguid = (ULONG_PTR)sessionguid;
    call.sessionid = (ULONG_PTR)sessionid;
    call.unknown1 = (ULONG_PTR)unknown1;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add WinSqmStartSession to Wine headers? */
extern HANDLE WINAPI WinSqmStartSession(GUID *sessionguid, DWORD sessionid, DWORD unknown1);
void qemu_WinSqmStartSession(struct qemu_syscall *call)
{
    struct qemu_WinSqmStartSession *c = (struct qemu_WinSqmStartSession *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WinSqmStartSession(QEMU_G2H(c->sessionguid), c->sessionid, c->unknown1);
}

#endif

struct qemu_EtwEventRegister
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t callback;
    uint64_t context;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventRegister(LPCGUID provider, PENABLECALLBACK callback, PVOID context, PREGHANDLE handle)
{
    struct qemu_EtwEventRegister call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTREGISTER);
    call.provider = (ULONG_PTR)provider;
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwEventRegister to Wine headers? */
extern ULONG WINAPI EtwEventRegister(LPCGUID provider, PENABLECALLBACK callback, PVOID context, PREGHANDLE handle);
void qemu_EtwEventRegister(struct qemu_syscall *call)
{
    struct qemu_EtwEventRegister *c = (struct qemu_EtwEventRegister *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwEventRegister(QEMU_G2H(c->provider), QEMU_G2H(c->callback), QEMU_G2H(c->context), QEMU_G2H(c->handle));
}

#endif

struct qemu_EtwEventUnregister
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventUnregister(REGHANDLE handle)
{
    struct qemu_EtwEventUnregister call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTUNREGISTER);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwEventUnregister to Wine headers? */
extern ULONG WINAPI EtwEventUnregister(REGHANDLE handle);
void qemu_EtwEventUnregister(struct qemu_syscall *call)
{
    struct qemu_EtwEventUnregister *c = (struct qemu_EtwEventUnregister *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwEventUnregister(c->handle);
}

#endif

struct qemu_EtwEventSetInformation
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventSetInformation(REGHANDLE handle, EVENT_INFO_CLASS class, void *info, ULONG length)
{
    struct qemu_EtwEventSetInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTSETINFORMATION);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwEventSetInformation to Wine headers? */
extern ULONG WINAPI EtwEventSetInformation(REGHANDLE handle, EVENT_INFO_CLASS class, void *info, ULONG length);
void qemu_EtwEventSetInformation(struct qemu_syscall *call)
{
    struct qemu_EtwEventSetInformation *c = (struct qemu_EtwEventSetInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwEventSetInformation(c->handle, c->class, QEMU_G2H(c->info), c->length);
}

#endif

struct qemu_EtwRegisterTraceGuidsW
{
    struct qemu_syscall super;
    uint64_t RequestAddress;
    uint64_t RequestContext;
    uint64_t ControlGuid;
    uint64_t GuidCount;
    uint64_t TraceGuidReg;
    uint64_t MofImagePath;
    uint64_t MofResourceName;
    uint64_t RegistrationHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwRegisterTraceGuidsW(WMIDPREQUEST RequestAddress, void *RequestContext, const GUID *ControlGuid, ULONG GuidCount, TRACE_GUID_REGISTRATION *TraceGuidReg, const WCHAR *MofImagePath, const WCHAR *MofResourceName, TRACEHANDLE *RegistrationHandle)
{
    struct qemu_EtwRegisterTraceGuidsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWREGISTERTRACEGUIDSW);
    call.RequestAddress = (ULONG_PTR)RequestAddress;
    call.RequestContext = (ULONG_PTR)RequestContext;
    call.ControlGuid = (ULONG_PTR)ControlGuid;
    call.GuidCount = (ULONG_PTR)GuidCount;
    call.TraceGuidReg = (ULONG_PTR)TraceGuidReg;
    call.MofImagePath = (ULONG_PTR)MofImagePath;
    call.MofResourceName = (ULONG_PTR)MofResourceName;
    call.RegistrationHandle = (ULONG_PTR)RegistrationHandle;

    return 0;
    qemu_syscall(&call.super);
    *RegistrationHandle = (TRACEHANDLE)(ULONG_PTR)call.RegistrationHandle;

    return call.super.iret;
}

#else

/* TODO: Add EtwRegisterTraceGuidsW to Wine headers? */
extern ULONG WINAPI EtwRegisterTraceGuidsW(WMIDPREQUEST RequestAddress, void *RequestContext, const GUID *ControlGuid, ULONG GuidCount, TRACE_GUID_REGISTRATION *TraceGuidReg, const WCHAR *MofImagePath, const WCHAR *MofResourceName, TRACEHANDLE *RegistrationHandle);
void qemu_EtwRegisterTraceGuidsW(struct qemu_syscall *call)
{
    struct qemu_EtwRegisterTraceGuidsW *c = (struct qemu_EtwRegisterTraceGuidsW *)call;
    TRACEHANDLE h;

    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwRegisterTraceGuidsW(QEMU_G2H(c->RequestAddress), QEMU_G2H(c->RequestContext), QEMU_G2H(c->ControlGuid), c->GuidCount, QEMU_G2H(c->TraceGuidReg), QEMU_G2H(c->MofImagePath), QEMU_G2H(c->MofResourceName), &h);
    c->RegistrationHandle = QEMU_H2G(h);
}

#endif

struct qemu_EtwRegisterTraceGuidsA
{
    struct qemu_syscall super;
    uint64_t RequestAddress;
    uint64_t RequestContext;
    uint64_t ControlGuid;
    uint64_t GuidCount;
    uint64_t TraceGuidReg;
    uint64_t MofImagePath;
    uint64_t MofResourceName;
    uint64_t RegistrationHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwRegisterTraceGuidsA(WMIDPREQUEST RequestAddress, void *RequestContext, const GUID *ControlGuid, ULONG GuidCount, TRACE_GUID_REGISTRATION *TraceGuidReg, const char *MofImagePath, const char *MofResourceName, TRACEHANDLE *RegistrationHandle)
{
    struct qemu_EtwRegisterTraceGuidsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWREGISTERTRACEGUIDSA);
    call.RequestAddress = (ULONG_PTR)RequestAddress;
    call.RequestContext = (ULONG_PTR)RequestContext;
    call.ControlGuid = (ULONG_PTR)ControlGuid;
    call.GuidCount = (ULONG_PTR)GuidCount;
    call.TraceGuidReg = (ULONG_PTR)TraceGuidReg;
    call.MofImagePath = (ULONG_PTR)MofImagePath;
    call.MofResourceName = (ULONG_PTR)MofResourceName;
    call.RegistrationHandle = (ULONG_PTR)RegistrationHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwRegisterTraceGuidsA to Wine headers? */
extern ULONG WINAPI EtwRegisterTraceGuidsA(WMIDPREQUEST RequestAddress, void *RequestContext, const GUID *ControlGuid, ULONG GuidCount, TRACE_GUID_REGISTRATION *TraceGuidReg, const char *MofImagePath, const char *MofResourceName, TRACEHANDLE *RegistrationHandle);
void qemu_EtwRegisterTraceGuidsA(struct qemu_syscall *call)
{
    struct qemu_EtwRegisterTraceGuidsA *c = (struct qemu_EtwRegisterTraceGuidsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwRegisterTraceGuidsA(QEMU_G2H(c->RequestAddress), QEMU_G2H(c->RequestContext), QEMU_G2H(c->ControlGuid), c->GuidCount, QEMU_G2H(c->TraceGuidReg), QEMU_G2H(c->MofImagePath), QEMU_G2H(c->MofResourceName), QEMU_G2H(c->RegistrationHandle));
}

#endif

struct qemu_EtwUnregisterTraceGuids
{
    struct qemu_syscall super;
    uint64_t RegistrationHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwUnregisterTraceGuids(TRACEHANDLE RegistrationHandle)
{
    struct qemu_EtwUnregisterTraceGuids call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWUNREGISTERTRACEGUIDS);
    call.RegistrationHandle = (ULONG_PTR)RegistrationHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwUnregisterTraceGuids to Wine headers? */
extern ULONG WINAPI EtwUnregisterTraceGuids(TRACEHANDLE RegistrationHandle);
void qemu_EtwUnregisterTraceGuids(struct qemu_syscall *call)
{
    struct qemu_EtwUnregisterTraceGuids *c = (struct qemu_EtwUnregisterTraceGuids *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwUnregisterTraceGuids(c->RegistrationHandle);
}

#endif

struct qemu_EtwEventEnabled
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t descriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI EtwEventEnabled(REGHANDLE handle, const EVENT_DESCRIPTOR *descriptor)
{
    struct qemu_EtwEventEnabled call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTENABLED);
    call.handle = (ULONG_PTR)handle;
    call.descriptor = (ULONG_PTR)descriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwEventEnabled to Wine headers? */
extern BOOLEAN WINAPI EtwEventEnabled(REGHANDLE handle, const EVENT_DESCRIPTOR *descriptor);
void qemu_EtwEventEnabled(struct qemu_syscall *call)
{
    struct qemu_EtwEventEnabled *c = (struct qemu_EtwEventEnabled *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwEventEnabled(c->handle, QEMU_G2H(c->descriptor));
}

#endif

struct qemu_EtwEventWrite
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t descriptor;
    uint64_t count;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventWrite(REGHANDLE handle, const EVENT_DESCRIPTOR *descriptor, ULONG count, EVENT_DATA_DESCRIPTOR *data)
{
    struct qemu_EtwEventWrite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTWRITE);
    call.handle = (ULONG_PTR)handle;
    call.descriptor = (ULONG_PTR)descriptor;
    call.count = (ULONG_PTR)count;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwEventWrite to Wine headers? */
extern ULONG WINAPI EtwEventWrite(REGHANDLE handle, const EVENT_DESCRIPTOR *descriptor, ULONG count, EVENT_DATA_DESCRIPTOR *data);
void qemu_EtwEventWrite(struct qemu_syscall *call)
{
    struct qemu_EtwEventWrite *c = (struct qemu_EtwEventWrite *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwEventWrite(c->handle, QEMU_G2H(c->descriptor), c->count, QEMU_G2H(c->data));
}

#endif

struct qemu_wine_server_call
{
    struct qemu_syscall super;
    uint64_t req_ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL wine_server_call(void *req_ptr)
{
    struct qemu_wine_server_call call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINE_SERVER_CALL);
    call.req_ptr = (ULONG_PTR)req_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wine_server_call(struct qemu_syscall *call)
{
    struct qemu_wine_server_call *c = (struct qemu_wine_server_call *)call;
    WINE_FIXME("Server call out of the VM? I am not playing any more!\n");
    ExitProcess(1);
}

#endif

struct qemu_qsort
{
    struct qemu_syscall super;
    uint64_t base;
    uint64_t nmemb;
    uint64_t size;
    uint64_t compar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void __cdecl NTDLL_qsort(void *base, size_t nmemb, size_t size, int(__cdecl *compar)(const void *, const void *))
{
    struct qemu_qsort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QSORT);
    call.base = (ULONG_PTR)base;
    call.nmemb = nmemb;
    call.size = size;
    call.compar = (ULONG_PTR)compar;

    qemu_syscall(&call.super);
}

#else

void qemu_qsort(struct qemu_syscall *call)
{
    struct qemu_qsort *c = (struct qemu_qsort *)call;
    WINE_FIXME("Stub!\n");
}

#endif

struct qemu_EtwEventActivityIdControl
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventActivityIdControl(ULONG code, GUID *guid)
{
    struct qemu_EtwEventActivityIdControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTACTIVITYIDCONTROL);
    call.code = code;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI EtwEventActivityIdControl(ULONG code, GUID *guid);
void qemu_EtwEventActivityIdControl(struct qemu_syscall *call)
{
    struct qemu_EtwEventActivityIdControl *c = (struct qemu_EtwEventActivityIdControl *)call;
    WINE_TRACE("\n");
    c->super.iret = EtwEventActivityIdControl(c->code, QEMU_G2H(c->guid));
}

#endif

struct qemu_EtwEventProviderEnabled
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t level;
    uint64_t keyword;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI EtwEventProviderEnabled(REGHANDLE handle, UCHAR level, ULONGLONG keyword)
{
    struct qemu_EtwEventProviderEnabled call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTPROVIDERENABLED);
    call.handle = handle;
    call.level = level;
    call.keyword = keyword;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOLEAN WINAPI EtwEventProviderEnabled(REGHANDLE handle, UCHAR level, ULONGLONG keyword);
void qemu_EtwEventProviderEnabled(struct qemu_syscall *call)
{
    struct qemu_EtwEventProviderEnabled *c = (struct qemu_EtwEventProviderEnabled *)call;
    WINE_TRACE("\n");
    c->super.iret = EtwEventProviderEnabled(c->handle, c->level, c->keyword);
}

#endif

struct qemu_EtwEventWriteString
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t level;
    uint64_t keyword;
    uint64_t string;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventWriteString(REGHANDLE handle, UCHAR level, ULONGLONG keyword, PCWSTR string)
{
    struct qemu_EtwEventWriteString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTWRITESTRING);
    call.handle = handle;
    call.level = level;
    call.keyword = keyword;
    call.string = (ULONG_PTR)string;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI EtwEventWriteString(REGHANDLE handle, UCHAR level, ULONGLONG keyword, PCWSTR string);
void qemu_EtwEventWriteString(struct qemu_syscall *call)
{
    struct qemu_EtwEventWriteString *c = (struct qemu_EtwEventWriteString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwEventWriteString(c->handle, c->level, c->keyword, QEMU_G2H(c->string));
}

#endif

struct qemu_EtwEventWriteTransfer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t descriptor;
    uint64_t activity;
    uint64_t related;
    uint64_t count;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwEventWriteTransfer(REGHANDLE handle, PCEVENT_DESCRIPTOR descriptor, LPCGUID activity, LPCGUID related, ULONG count, PEVENT_DATA_DESCRIPTOR data)
{
    struct qemu_EtwEventWriteTransfer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWEVENTWRITETRANSFER);
    call.handle = handle;
    call.descriptor = (ULONG_PTR)descriptor;
    call.activity = (ULONG_PTR)activity;
    call.related = (ULONG_PTR)related;
    call.count = count;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI ULONG WINAPI EtwEventWriteTransfer(REGHANDLE handle, PCEVENT_DESCRIPTOR descriptor, LPCGUID activity, LPCGUID related, ULONG count, PEVENT_DATA_DESCRIPTOR data);
void qemu_EtwEventWriteTransfer(struct qemu_syscall *call)
{
    struct qemu_EtwEventWriteTransfer *c = (struct qemu_EtwEventWriteTransfer *)call;
    WINE_FIXME("\n");
    c->super.iret = EtwEventWriteTransfer(c->handle, QEMU_G2H(c->descriptor), QEMU_G2H(c->activity), QEMU_G2H(c->related), c->count, QEMU_G2H(c->data));
}

#endif

struct qemu_EtwGetTraceEnableFlags
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwGetTraceEnableFlags(TRACEHANDLE handle)
{
    struct qemu_EtwGetTraceEnableFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWGETTRACEENABLEFLAGS);
    call.handle = handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI ULONG WINAPI EtwGetTraceEnableFlags(TRACEHANDLE handle);
void qemu_EtwGetTraceEnableFlags(struct qemu_syscall *call)
{
    struct qemu_EtwGetTraceEnableFlags *c = (struct qemu_EtwGetTraceEnableFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwGetTraceEnableFlags(c->handle);
}

#endif

struct qemu_EtwGetTraceEnableLevel
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UCHAR WINAPI EtwGetTraceEnableLevel(TRACEHANDLE handle)
{
    struct qemu_EtwGetTraceEnableLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWGETTRACEENABLELEVEL);
    call.handle = handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern UCHAR WINAPI EtwGetTraceEnableLevel(TRACEHANDLE handle);
void qemu_EtwGetTraceEnableLevel(struct qemu_syscall *call)
{
    struct qemu_EtwGetTraceEnableLevel *c = (struct qemu_EtwGetTraceEnableLevel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwGetTraceEnableLevel(c->handle);
}

#endif

struct qemu_EtwGetTraceLoggerHandle
{
    struct qemu_syscall super;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI TRACEHANDLE WINAPI EtwGetTraceLoggerHandle(PVOID buf)
{
    struct qemu_EtwGetTraceLoggerHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWGETTRACELOGGERHANDLE);
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern TRACEHANDLE WINAPI EtwGetTraceLoggerHandle(PVOID buf);
void qemu_EtwGetTraceLoggerHandle(struct qemu_syscall *call)
{
    struct qemu_EtwGetTraceLoggerHandle *c = (struct qemu_EtwGetTraceLoggerHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwGetTraceLoggerHandle(QEMU_G2H(c->buf));
}

#endif

struct qemu_EtwLogTraceEvent
{
    struct qemu_syscall super;
    uint64_t SessionHandle;
    uint64_t EventTrace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwLogTraceEvent(TRACEHANDLE SessionHandle, PEVENT_TRACE_HEADER EventTrace)
{
    struct qemu_EtwLogTraceEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWLOGTRACEEVENT);
    call.SessionHandle = SessionHandle;
    call.EventTrace = (ULONG_PTR)EventTrace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI EtwLogTraceEvent(TRACEHANDLE SessionHandle, PEVENT_TRACE_HEADER EventTrace);
void qemu_EtwLogTraceEvent(struct qemu_syscall *call)
{
    struct qemu_EtwLogTraceEvent *c = (struct qemu_EtwLogTraceEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwLogTraceEvent(c->SessionHandle, QEMU_G2H(c->EventTrace));
}

#endif

struct qemu_EtwTraceMessageVa
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
    uint64_t guid;
    uint64_t number;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwTraceMessageVa(TRACEHANDLE handle, ULONG flags, LPGUID guid, USHORT number, va_list va)
{
    struct qemu_EtwTraceMessageVa call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWTRACEMESSAGEVA);
    call.handle = handle;
    call.flags = flags;
    call.guid = (ULONG_PTR)guid;
    call.number = number;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EtwTraceMessageVa(struct qemu_syscall *call)
{
    struct qemu_EtwTraceMessageVa *c = (struct qemu_EtwTraceMessageVa *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif

struct qemu_EtwTraceMessage
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
    uint64_t guid;
    uint64_t number;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI EtwTraceMessage(TRACEHANDLE handle, ULONG flags, LPGUID guid, ULONG number, ...)
{
    struct qemu_EtwTraceMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ETWTRACEMESSAGE);
    call.handle = handle;
    call.flags = flags;
    call.guid = (ULONG_PTR)guid;
    call.number = number;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EtwTraceMessage(struct qemu_syscall *call)
{
    struct qemu_EtwTraceMessage *c = (struct qemu_EtwTraceMessage *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = 0;
}

#endif
