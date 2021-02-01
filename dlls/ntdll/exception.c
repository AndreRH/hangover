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
#include "qemu_ntdll.h"

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
    call.status = (ULONG_PTR)status;

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
    call.first = (ULONG_PTR)first;
    call.func = (ULONG_PTR)func;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add RtlAddVectoredContinueHandler to Wine headers? */
extern PVOID WINAPI RtlAddVectoredContinueHandler(ULONG first, PVECTORED_EXCEPTION_HANDLER func);
void qemu_RtlAddVectoredContinueHandler(struct qemu_syscall *call)
{
    struct qemu_RtlAddVectoredContinueHandler *c = (struct qemu_RtlAddVectoredContinueHandler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RtlAddVectoredContinueHandler(c->first, QEMU_G2H(c->func));
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
    call.handler = (ULONG_PTR)handler;

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
    call.first = (ULONG_PTR)first;
    call.func = (ULONG_PTR)func;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlAddVectoredExceptionHandler(struct qemu_syscall *call)
{
    struct qemu_RtlAddVectoredExceptionHandler *c = (struct qemu_RtlAddVectoredExceptionHandler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = 0xdeadbeef;
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
    call.handler = (ULONG_PTR)handler;

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

#ifdef _WIN64
WINBASEAPI BOOLEAN CDECL RtlDeleteFunctionTable(RUNTIME_FUNCTION *table)
{
    struct qemu_RtlDeleteFunctionTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETEFUNCTIONTABLE);
    call.table = (ULONG_PTR)table;

    qemu_syscall(&call.super);

    return call.super.iret;
}
#else
/* Dummy because we can't do arch-specific .spec files yet. */
WINBASEAPI BOOLEAN CDECL RtlDeleteFunctionTable(void *table)
{
    return FALSE;
}
#endif

#else

void qemu_RtlDeleteFunctionTable(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteFunctionTable *c = (struct qemu_RtlDeleteFunctionTable *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret =TRUE;
}

#endif

#ifdef QEMU_DLL_GUEST
/*************************************************************
 *            __wine_spec_unimplemented_stub
 *
 * ntdll-specific implementation to avoid depending on kernel functions.
 * Can be removed once ntdll.spec no longer contains stubs.
 */
void WINAPI RtlRaiseException(PEXCEPTION_RECORD);
void __cdecl __wine_spec_unimplemented_stub( const char *module, const char *function )
{
    EXCEPTION_RECORD record;

    record.ExceptionCode    = 0x80000100;
    record.ExceptionFlags   = 0x01;
    record.ExceptionRecord  = NULL;
    record.ExceptionAddress = __wine_spec_unimplemented_stub;
    record.NumberParameters = 2;
    record.ExceptionInformation[0] = (ULONG_PTR)module;
    record.ExceptionInformation[1] = (ULONG_PTR)function;
    for (;;) RtlRaiseException( &record );
}
#endif

struct qemu_RtlCopyExtendedContext
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t context_flags;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST
typedef struct _CONTEXT_EX CONTEXT_EX;

WINBASEAPI NTSTATUS WINAPI RtlCopyExtendedContext(CONTEXT_EX *dst, ULONG context_flags, CONTEXT_EX *src)
{
    struct qemu_RtlCopyExtendedContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYEXTENDEDCONTEXT);
    call.dst = (ULONG_PTR)dst;
    call.context_flags = context_flags;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCopyExtendedContext(struct qemu_syscall *call)
{
    struct qemu_RtlCopyExtendedContext *c = (struct qemu_RtlCopyExtendedContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCopyExtendedContext(QEMU_G2H(c->dst), c->context_flags, QEMU_G2H(c->src));
}

#endif

struct qemu_RtlGetEnabledExtendedFeatures
{
    struct qemu_syscall super;
    uint64_t feature_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG64 WINAPI RtlGetEnabledExtendedFeatures(ULONG64 feature_mask)
{
    struct qemu_RtlGetEnabledExtendedFeatures call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETENABLEDEXTENDEDFEATURES);
    call.feature_mask = feature_mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetEnabledExtendedFeatures(struct qemu_syscall *call)
{
    struct qemu_RtlGetEnabledExtendedFeatures *c = (struct qemu_RtlGetEnabledExtendedFeatures *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetEnabledExtendedFeatures(c->feature_mask);
}

#endif

struct qemu_RtlGetExtendedContextLength2
{
    struct qemu_syscall super;
    uint64_t context_flags;
    uint64_t length;
    uint64_t compaction_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetExtendedContextLength2(ULONG context_flags, ULONG *length, ULONG64 compaction_mask)
{
    struct qemu_RtlGetExtendedContextLength2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETEXTENDEDCONTEXTLENGTH2);
    call.context_flags = context_flags;
    call.length = (ULONG_PTR)length;
    call.compaction_mask = compaction_mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetExtendedContextLength2(struct qemu_syscall *call)
{
    struct qemu_RtlGetExtendedContextLength2 *c = (struct qemu_RtlGetExtendedContextLength2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetExtendedContextLength2(c->context_flags, QEMU_G2H(c->length), c->compaction_mask);
}

#endif

struct qemu_RtlGetExtendedFeaturesMask
{
    struct qemu_syscall super;
    uint64_t context_ex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG64 WINAPI RtlGetExtendedFeaturesMask(CONTEXT_EX *context_ex)
{
    struct qemu_RtlGetExtendedFeaturesMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETEXTENDEDFEATURESMASK);
    call.context_ex = (ULONG_PTR)context_ex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetExtendedFeaturesMask(struct qemu_syscall *call)
{
    struct qemu_RtlGetExtendedFeaturesMask *c = (struct qemu_RtlGetExtendedFeaturesMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetExtendedFeaturesMask(QEMU_G2H(c->context_ex));
}

#endif

struct qemu_RtlInitializeExtendedContext2
{
    struct qemu_syscall super;
    uint64_t context;
    uint64_t context_flags;
    uint64_t context_ex;
    uint64_t compaction_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlInitializeExtendedContext2(void *context, ULONG context_flags, CONTEXT_EX **context_ex, ULONG64 compaction_mask)
{
    struct qemu_RtlInitializeExtendedContext2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZEEXTENDEDCONTEXT2);
    call.context = (ULONG_PTR)context;
    call.context_flags = context_flags;
    call.context_ex = (ULONG_PTR)context_ex;
    call.compaction_mask = compaction_mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitializeExtendedContext2(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeExtendedContext2 *c = (struct qemu_RtlInitializeExtendedContext2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlInitializeExtendedContext2(QEMU_G2H(c->context), c->context_flags, QEMU_G2H(c->context_ex), c->compaction_mask);
}

#endif

struct qemu_RtlLocateExtendedFeature2
{
    struct qemu_syscall super;
    uint64_t context_ex;
    uint64_t feature_id;
    uint64_t xstate_config;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI RtlLocateExtendedFeature2(CONTEXT_EX *context_ex, ULONG feature_id, XSTATE_CONFIGURATION *xstate_config, ULONG *length)
{
    struct qemu_RtlLocateExtendedFeature2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLOCATEEXTENDEDFEATURE2);
    call.context_ex = (ULONG_PTR)context_ex;
    call.feature_id = feature_id;
    call.xstate_config = (ULONG_PTR)xstate_config;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlLocateExtendedFeature2(struct qemu_syscall *call)
{
    struct qemu_RtlLocateExtendedFeature2 *c = (struct qemu_RtlLocateExtendedFeature2 *)call;
    WINE_FIXME("Unverified!\n");
    RtlLocateExtendedFeature2(QEMU_G2H(c->context_ex), c->feature_id, QEMU_G2H(c->xstate_config), QEMU_G2H(c->length));
}

#endif

struct qemu_RtlSetExtendedFeaturesMask
{
    struct qemu_syscall super;
    uint64_t context_ex;
    uint64_t feature_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlSetExtendedFeaturesMask(CONTEXT_EX *context_ex, ULONG64 feature_mask)
{
    struct qemu_RtlSetExtendedFeaturesMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETEXTENDEDFEATURESMASK);
    call.context_ex = (ULONG_PTR)context_ex;
    call.feature_mask = feature_mask;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlSetExtendedFeaturesMask(struct qemu_syscall *call)
{
    struct qemu_RtlSetExtendedFeaturesMask *c = (struct qemu_RtlSetExtendedFeaturesMask *)call;
    WINE_FIXME("Unverified!\n");
    RtlSetExtendedFeaturesMask(QEMU_G2H(c->context_ex), c->feature_mask);
}

#endif

struct qemu_RtlLocateExtendedFeature
{
    struct qemu_syscall super;
    uint64_t context_ex;
    uint64_t feature_id;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * WINAPI RtlLocateExtendedFeature(CONTEXT_EX *context_ex, ULONG feature_id, ULONG *length)
{
    struct qemu_RtlLocateExtendedFeature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLOCATEEXTENDEDFEATURE);
    call.context_ex = (ULONG_PTR)context_ex;
    call.feature_id = feature_id;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlLocateExtendedFeature(struct qemu_syscall *call)
{
    struct qemu_RtlLocateExtendedFeature *c = (struct qemu_RtlLocateExtendedFeature *)call;
    WINE_FIXME("Unverified!\n");
    RtlLocateExtendedFeature(QEMU_G2H(c->context_ex), c->feature_id, QEMU_G2H(c->length));
}

#endif
