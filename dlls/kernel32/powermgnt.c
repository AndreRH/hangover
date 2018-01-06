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
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_GetDevicePowerState
{
    struct qemu_syscall super;
    uint64_t hDevice;
    uint64_t pfOn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDevicePowerState(HANDLE hDevice, BOOL* pfOn)
{
    struct qemu_GetDevicePowerState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEVICEPOWERSTATE);
    call.hDevice = (LONG_PTR)hDevice;
    call.pfOn = (ULONG_PTR)pfOn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDevicePowerState(struct qemu_syscall *call)
{
    struct qemu_GetDevicePowerState *c = (struct qemu_GetDevicePowerState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDevicePowerState(QEMU_G2H(c->hDevice), QEMU_G2H(c->pfOn));
}

#endif

struct qemu_GetSystemPowerStatus
{
    struct qemu_syscall super;
    uint64_t ps;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSystemPowerStatus(LPSYSTEM_POWER_STATUS ps)
{
    struct qemu_GetSystemPowerStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMPOWERSTATUS);
    call.ps = (ULONG_PTR)ps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemPowerStatus(struct qemu_syscall *call)
{
    struct qemu_GetSystemPowerStatus *c = (struct qemu_GetSystemPowerStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemPowerStatus(QEMU_G2H(c->ps));
}

#endif

struct qemu_IsSystemResumeAutomatic
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsSystemResumeAutomatic(void)
{
    struct qemu_IsSystemResumeAutomatic call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISSYSTEMRESUMEAUTOMATIC);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsSystemResumeAutomatic(struct qemu_syscall *call)
{
    struct qemu_IsSystemResumeAutomatic *c = (struct qemu_IsSystemResumeAutomatic *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsSystemResumeAutomatic();
}

#endif

struct qemu_RequestWakeupLatency
{
    struct qemu_syscall super;
    uint64_t latency;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RequestWakeupLatency(LATENCY_TIME latency)
{
    struct qemu_RequestWakeupLatency call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REQUESTWAKEUPLATENCY);
    call.latency = (ULONG_PTR)latency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RequestWakeupLatency(struct qemu_syscall *call)
{
    struct qemu_RequestWakeupLatency *c = (struct qemu_RequestWakeupLatency *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RequestWakeupLatency(c->latency);
}

#endif

struct qemu_SetSystemPowerState
{
    struct qemu_syscall super;
    uint64_t suspend_or_hibernate;
    uint64_t force_flag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSystemPowerState(BOOL suspend_or_hibernate, BOOL force_flag)
{
    struct qemu_SetSystemPowerState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSTEMPOWERSTATE);
    call.suspend_or_hibernate = (ULONG_PTR)suspend_or_hibernate;
    call.force_flag = force_flag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSystemPowerState(struct qemu_syscall *call)
{
    struct qemu_SetSystemPowerState *c = (struct qemu_SetSystemPowerState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSystemPowerState(c->suspend_or_hibernate, c->force_flag);
}

#endif

struct qemu_SetThreadExecutionState
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI EXECUTION_STATE WINAPI SetThreadExecutionState(EXECUTION_STATE flags)
{
    struct qemu_SetThreadExecutionState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADEXECUTIONSTATE);
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadExecutionState(struct qemu_syscall *call)
{
    struct qemu_SetThreadExecutionState *c = (struct qemu_SetThreadExecutionState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadExecutionState(c->flags);
}

#endif

struct qemu_PowerCreateRequest
{
    struct qemu_syscall super;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI PowerCreateRequest(REASON_CONTEXT *context)
{
    struct qemu_PowerCreateRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POWERCREATEREQUEST);
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add PowerCreateRequest to Wine headers? */
extern HANDLE WINAPI PowerCreateRequest(REASON_CONTEXT *context);
void qemu_PowerCreateRequest(struct qemu_syscall *call)
{
    struct qemu_PowerCreateRequest *c = (struct qemu_PowerCreateRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(PowerCreateRequest(QEMU_G2H(c->context)));
}

#endif

struct qemu_PowerSetRequest
{
    struct qemu_syscall super;
    uint64_t request;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PowerSetRequest(HANDLE request, POWER_REQUEST_TYPE type)
{
    struct qemu_PowerSetRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POWERSETREQUEST);
    call.request = (LONG_PTR)request;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PowerSetRequest to Wine headers? */
extern BOOL WINAPI PowerSetRequest(HANDLE request, POWER_REQUEST_TYPE type);
void qemu_PowerSetRequest(struct qemu_syscall *call)
{
    struct qemu_PowerSetRequest *c = (struct qemu_PowerSetRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PowerSetRequest(QEMU_G2H(c->request), c->type);
}

#endif

struct qemu_PowerClearRequest
{
    struct qemu_syscall super;
    uint64_t request;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PowerClearRequest(HANDLE request, POWER_REQUEST_TYPE type)
{
    struct qemu_PowerClearRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POWERCLEARREQUEST);
    call.request = (LONG_PTR)request;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add PowerClearRequest to Wine headers? */
extern BOOL WINAPI PowerClearRequest(HANDLE request, POWER_REQUEST_TYPE type);
void qemu_PowerClearRequest(struct qemu_syscall *call)
{
    struct qemu_PowerClearRequest *c = (struct qemu_PowerClearRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PowerClearRequest(QEMU_G2H(c->request), c->type);
}

#endif

