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
#include <winnt.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif


struct qemu_RtlRaiseStatus
{
    struct qemu_syscall super;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

void WINAPI ntdll_RtlRaiseStatus(NTSTATUS status)
{
    struct qemu_RtlRaiseStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRAISESTATUS);
    call.status = (uint64_t)status;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlRaiseStatus(struct qemu_syscall *call)
{
    struct qemu_RtlRaiseStatus *c = (struct qemu_RtlRaiseStatus *)call;
    WINE_FIXME("Unverified!\n");
    RtlRaiseStatus(c->status);
}

#endif

struct qemu_RtlAddVectoredContinueHandler
{
    struct qemu_syscall super;
    uint64_t first;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI RtlAddVectoredContinueHandler(ULONG first, PVECTORED_EXCEPTION_HANDLER func)
{
    struct qemu_RtlAddVectoredContinueHandler call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDVECTOREDCONTINUEHANDLER);
    call.first = (uint64_t)first;
    call.func = (uint64_t)func;

    qemu_syscall(&call.super);

    return (PVOID)call.super.iret;
}

#else

/* TODO: Add RtlAddVectoredContinueHandler to Wine headers? */
extern PVOID WINAPI RtlAddVectoredContinueHandler(ULONG first, PVECTORED_EXCEPTION_HANDLER func);
void qemu_RtlAddVectoredContinueHandler(struct qemu_syscall *call)
{
    struct qemu_RtlAddVectoredContinueHandler *c = (struct qemu_RtlAddVectoredContinueHandler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RtlAddVectoredContinueHandler(c->first, QEMU_G2H(c->func));
}

#endif

struct qemu_RtlRemoveVectoredContinueHandler
{
    struct qemu_syscall super;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlRemoveVectoredContinueHandler(PVOID handler)
{
    struct qemu_RtlRemoveVectoredContinueHandler call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLREMOVEVECTOREDCONTINUEHANDLER);
    call.handler = (uint64_t)handler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlRemoveVectoredContinueHandler to Wine headers? */
extern ULONG WINAPI RtlRemoveVectoredContinueHandler(PVOID handler);
void qemu_RtlRemoveVectoredContinueHandler(struct qemu_syscall *call)
{
    struct qemu_RtlRemoveVectoredContinueHandler *c = (struct qemu_RtlRemoveVectoredContinueHandler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlRemoveVectoredContinueHandler(QEMU_G2H(c->handler));
}

#endif

struct qemu_RtlAddVectoredExceptionHandler
{
    struct qemu_syscall super;
    uint64_t first;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI RtlAddVectoredExceptionHandler(ULONG first, PVECTORED_EXCEPTION_HANDLER func)
{
    struct qemu_RtlAddVectoredExceptionHandler call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDVECTOREDEXCEPTIONHANDLER);
    call.first = (uint64_t)first;
    call.func = (uint64_t)func;

    qemu_syscall(&call.super);

    return (PVOID)call.super.iret;
}

#else

void qemu_RtlAddVectoredExceptionHandler(struct qemu_syscall *call)
{
    struct qemu_RtlAddVectoredExceptionHandler *c = (struct qemu_RtlAddVectoredExceptionHandler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RtlAddVectoredExceptionHandler(c->first, QEMU_G2H(c->func));
}

#endif

struct qemu_RtlRemoveVectoredExceptionHandler
{
    struct qemu_syscall super;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlRemoveVectoredExceptionHandler(PVOID handler)
{
    struct qemu_RtlRemoveVectoredExceptionHandler call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLREMOVEVECTOREDEXCEPTIONHANDLER);
    call.handler = (uint64_t)handler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlRemoveVectoredExceptionHandler(struct qemu_syscall *call)
{
    struct qemu_RtlRemoveVectoredExceptionHandler *c = (struct qemu_RtlRemoveVectoredExceptionHandler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlRemoveVectoredExceptionHandler(QEMU_G2H(c->handler));
}

#endif

struct qemu_RtlDeleteFunctionTable
{
    struct qemu_syscall super;
    uint64_t table;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN CDECL RtlDeleteFunctionTable(RUNTIME_FUNCTION *table)
{
    struct qemu_RtlDeleteFunctionTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETEFUNCTIONTABLE);
    call.table = (uint64_t)table;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeleteFunctionTable(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteFunctionTable *c = (struct qemu_RtlDeleteFunctionTable *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret =TRUE;
}

#endif

