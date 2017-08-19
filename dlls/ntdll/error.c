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

#include "windows-user-services.h"
#include "dll_list.h"
#include "ntdll.h"

#ifdef QEMU_DLL_GUEST

typedef enum _HARDERROR_RESPONSE_OPTION
{
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem
} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;

typedef enum _HARDERROR_RESPONSE
{
    ResponseReturnToCaller,
    ResponseNotHandled,
    ResponseAbort,
    ResponseCancel,
    ResponseIgnore,
    ResponseNo,
    ResponseOk,
    ResponseRetry,
    ResponseYes
} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif


struct qemu_RtlNtStatusToDosErrorNoTeb
{
    struct qemu_syscall super;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlNtStatusToDosErrorNoTeb(NTSTATUS status)
{
    struct qemu_RtlNtStatusToDosErrorNoTeb call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNTSTATUSTODOSERRORNOTEB);
    call.status = (uint64_t)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlNtStatusToDosErrorNoTeb(struct qemu_syscall *call)
{
    struct qemu_RtlNtStatusToDosErrorNoTeb *c = (struct qemu_RtlNtStatusToDosErrorNoTeb *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlNtStatusToDosErrorNoTeb(c->status);
}

#endif

struct qemu_RtlNtStatusToDosError
{
    struct qemu_syscall super;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlNtStatusToDosError(NTSTATUS status)
{
    struct qemu_RtlNtStatusToDosError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNTSTATUSTODOSERROR);
    call.status = (uint64_t)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlNtStatusToDosError(struct qemu_syscall *call)
{
    struct qemu_RtlNtStatusToDosError *c = (struct qemu_RtlNtStatusToDosError *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlNtStatusToDosError(c->status);
}

#endif

struct qemu_RtlGetLastNtStatus
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetLastNtStatus(void)
{
    struct qemu_RtlGetLastNtStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETLASTNTSTATUS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetLastNtStatus(struct qemu_syscall *call)
{
    struct qemu_RtlGetLastNtStatus *c = (struct qemu_RtlGetLastNtStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetLastNtStatus();
}

#endif

struct qemu_RtlGetLastWin32Error
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlGetLastWin32Error(void)
{
    struct qemu_RtlGetLastWin32Error call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETLASTWIN32ERROR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetLastWin32Error(struct qemu_syscall *call)
{
    struct qemu_RtlGetLastWin32Error *c = (struct qemu_RtlGetLastWin32Error *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetLastWin32Error();
}

#endif

struct qemu_NtRaiseHardError
{
    struct qemu_syscall super;
    uint64_t ErrorStatus;
    uint64_t NumberOfParameters;
    uint64_t UnicodeStringParameterMask;
    uint64_t Parameters;
    uint64_t ResponseOption;
    uint64_t Response;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, PUNICODE_STRING UnicodeStringParameterMask, PVOID *Parameters, HARDERROR_RESPONSE_OPTION ResponseOption, PHARDERROR_RESPONSE Response)
{
    struct qemu_NtRaiseHardError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRAISEHARDERROR);
    call.ErrorStatus = (uint64_t)ErrorStatus;
    call.NumberOfParameters = (uint64_t)NumberOfParameters;
    call.UnicodeStringParameterMask = (uint64_t)UnicodeStringParameterMask;
    call.Parameters = (uint64_t)Parameters;
    call.ResponseOption = (uint64_t)ResponseOption;
    call.Response = (uint64_t)Response;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtRaiseHardError(struct qemu_syscall *call)
{
    struct qemu_NtRaiseHardError *c = (struct qemu_NtRaiseHardError *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtRaiseHardError(c->ErrorStatus, c->NumberOfParameters, QEMU_G2H(c->UnicodeStringParameterMask), QEMU_G2H(c->Parameters), c->ResponseOption, QEMU_G2H(c->Response));
}

#endif

struct qemu_RtlSetLastWin32Error
{
    struct qemu_syscall super;
    uint64_t err;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlSetLastWin32Error(DWORD err)
{
    struct qemu_RtlSetLastWin32Error call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETLASTWIN32ERROR);
    call.err = (uint64_t)err;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSetLastWin32Error(struct qemu_syscall *call)
{
    struct qemu_RtlSetLastWin32Error *c = (struct qemu_RtlSetLastWin32Error *)call;
    WINE_FIXME("Unverified!\n");
    RtlSetLastWin32Error(c->err);
}

#endif

struct qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus
{
    struct qemu_syscall super;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlSetLastWin32ErrorAndNtStatusFromNtStatus(NTSTATUS status)
{
    struct qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETLASTWIN32ERRORANDNTSTATUSFROMNTSTATUS);
    call.status = (uint64_t)status;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus(struct qemu_syscall *call)
{
    struct qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus *c = (struct qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus *)call;
    WINE_FIXME("Unverified!\n");
    RtlSetLastWin32ErrorAndNtStatusFromNtStatus(c->status);
}

#endif

