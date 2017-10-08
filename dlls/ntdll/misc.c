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
#include "ntdll.h"

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

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add EtwRegisterTraceGuidsW to Wine headers? */
extern ULONG WINAPI EtwRegisterTraceGuidsW(WMIDPREQUEST RequestAddress, void *RequestContext, const GUID *ControlGuid, ULONG GuidCount, TRACE_GUID_REGISTRATION *TraceGuidReg, const WCHAR *MofImagePath, const WCHAR *MofResourceName, TRACEHANDLE *RegistrationHandle);
void qemu_EtwRegisterTraceGuidsW(struct qemu_syscall *call)
{
    struct qemu_EtwRegisterTraceGuidsW *c = (struct qemu_EtwRegisterTraceGuidsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EtwRegisterTraceGuidsW(QEMU_G2H(c->RequestAddress), QEMU_G2H(c->RequestContext), QEMU_G2H(c->ControlGuid), c->GuidCount, QEMU_G2H(c->TraceGuidReg), QEMU_G2H(c->MofImagePath), QEMU_G2H(c->MofResourceName), QEMU_G2H(c->RegistrationHandle));
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

