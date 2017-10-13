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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif


struct qemu_Context_CurrentContext
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI Context* CDECL Context_CurrentContext(void)
{
    struct qemu_Context_CurrentContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_CURRENTCONTEXT);

    qemu_syscall(&call.super);

    return (Context *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_Context_CurrentContext(struct qemu_syscall *call)
{
    struct qemu_Context_CurrentContext *c = (struct qemu_Context_CurrentContext *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_Context_CurrentContext());
}

#endif

struct qemu_Context_Id
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL Context_Id(void)
{
    struct qemu_Context_Id call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_ID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Context_Id(struct qemu_syscall *call)
{
    struct qemu_Context_Id *c = (struct qemu_Context_Id *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_Context_Id();
}

#endif

struct qemu_Context_Block
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Context_Block(void)
{
    struct qemu_Context_Block call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_BLOCK);

    qemu_syscall(&call.super);
}

#else

void qemu_Context_Block(struct qemu_syscall *call)
{
    struct qemu_Context_Block *c = (struct qemu_Context_Block *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Context_Block();
}

#endif

struct qemu_Context_Yield
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Context_Yield(void)
{
    struct qemu_Context_Yield call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_YIELD);

    qemu_syscall(&call.super);
}

#else

void qemu_Context_Yield(struct qemu_syscall *call)
{
    struct qemu_Context_Yield *c = (struct qemu_Context_Yield *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Context_Yield();
}

#endif

struct qemu_Context__SpinYield
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Context__SpinYield(void)
{
    struct qemu_Context__SpinYield call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT__SPINYIELD);

    qemu_syscall(&call.super);
}

#else

void qemu_Context__SpinYield(struct qemu_syscall *call)
{
    struct qemu_Context__SpinYield *c = (struct qemu_Context__SpinYield *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Context__SpinYield();
}

#endif

struct qemu_Context_IsCurrentTaskCollectionCanceling
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL Context_IsCurrentTaskCollectionCanceling(void)
{
    struct qemu_Context_IsCurrentTaskCollectionCanceling call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_ISCURRENTTASKCOLLECTIONCANCELING);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Context_IsCurrentTaskCollectionCanceling(struct qemu_syscall *call)
{
    struct qemu_Context_IsCurrentTaskCollectionCanceling *c = (struct qemu_Context_IsCurrentTaskCollectionCanceling *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_Context_IsCurrentTaskCollectionCanceling();
}

#endif

struct qemu_Context_Oversubscribe
{
    struct qemu_syscall super;
    uint64_t begin;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Context_Oversubscribe(BOOL begin)
{
    struct qemu_Context_Oversubscribe call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_OVERSUBSCRIBE);
    call.begin = begin;

    qemu_syscall(&call.super);
}

#else

void qemu_Context_Oversubscribe(struct qemu_syscall *call)
{
    struct qemu_Context_Oversubscribe *c = (struct qemu_Context_Oversubscribe *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Context_Oversubscribe(c->begin);
}

#endif

struct qemu_Context_ScheduleGroupId
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL Context_ScheduleGroupId(void)
{
    struct qemu_Context_ScheduleGroupId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_SCHEDULEGROUPID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Context_ScheduleGroupId(struct qemu_syscall *call)
{
    struct qemu_Context_ScheduleGroupId *c = (struct qemu_Context_ScheduleGroupId *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_Context_ScheduleGroupId();
}

#endif

struct qemu_Context_VirtualProcessorId
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL Context_VirtualProcessorId(void)
{
    struct qemu_Context_VirtualProcessorId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTEXT_VIRTUALPROCESSORID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Context_VirtualProcessorId(struct qemu_syscall *call)
{
    struct qemu_Context_VirtualProcessorId *c = (struct qemu_Context_VirtualProcessorId *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_Context_VirtualProcessorId();
}

#endif

struct qemu_Concurrency_Alloc
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL Concurrency_Alloc(size_t size)
{
    struct qemu_Concurrency_Alloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONCURRENCY_ALLOC);
    call.size = size;

    qemu_syscall(&call.super);
}

#else

void qemu_Concurrency_Alloc(struct qemu_syscall *call)
{
    struct qemu_Concurrency_Alloc *c = (struct qemu_Concurrency_Alloc *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Concurrency_Alloc(c->size);
}

#endif

struct qemu_Concurrency_Free
{
    struct qemu_syscall super;
    uint64_t mem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Concurrency_Free(void* mem)
{
    struct qemu_Concurrency_Free call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONCURRENCY_FREE);
    call.mem = (ULONG_PTR)mem;

    qemu_syscall(&call.super);
}

#else

void qemu_Concurrency_Free(struct qemu_syscall *call)
{
    struct qemu_Concurrency_Free *c = (struct qemu_Concurrency_Free *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Concurrency_Free(QEMU_G2H(c->mem));
}

#endif

struct qemu_Scheduler_Create
{
    struct qemu_syscall super;
    uint64_t policy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI Scheduler* CDECL Scheduler_Create(const SchedulerPolicy *policy)
{
    struct qemu_Scheduler_Create call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCHEDULER_CREATE);
    call.policy = (ULONG_PTR)policy;

    qemu_syscall(&call.super);

    return (Scheduler *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_Scheduler_Create(struct qemu_syscall *call)
{
    struct qemu_Scheduler_Create *c = (struct qemu_Scheduler_Create *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_Scheduler_Create(QEMU_G2H(c->policy)));
}

#endif

struct qemu_Scheduler_ResetDefaultSchedulerPolicy
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Scheduler_ResetDefaultSchedulerPolicy(void)
{
    struct qemu_Scheduler_ResetDefaultSchedulerPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCHEDULER_RESETDEFAULTSCHEDULERPOLICY);

    qemu_syscall(&call.super);
}

#else

void qemu_Scheduler_ResetDefaultSchedulerPolicy(struct qemu_syscall *call)
{
    struct qemu_Scheduler_ResetDefaultSchedulerPolicy *c = (struct qemu_Scheduler_ResetDefaultSchedulerPolicy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Scheduler_ResetDefaultSchedulerPolicy();
}

#endif

struct qemu_Scheduler_SetDefaultSchedulerPolicy
{
    struct qemu_syscall super;
    uint64_t policy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL Scheduler_SetDefaultSchedulerPolicy(const SchedulerPolicy *policy)
{
    struct qemu_Scheduler_SetDefaultSchedulerPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCHEDULER_SETDEFAULTSCHEDULERPOLICY);
    call.policy = (ULONG_PTR)policy;

    qemu_syscall(&call.super);
}

#else

void qemu_Scheduler_SetDefaultSchedulerPolicy(struct qemu_syscall *call)
{
    struct qemu_Scheduler_SetDefaultSchedulerPolicy *c = (struct qemu_Scheduler_SetDefaultSchedulerPolicy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_Scheduler_SetDefaultSchedulerPolicy(QEMU_G2H(c->policy));
}

#endif

struct qemu_CurrentScheduler_Create
{
    struct qemu_syscall super;
    uint64_t policy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL CurrentScheduler_Create(const SchedulerPolicy *policy)
{
    struct qemu_CurrentScheduler_Create call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_CREATE);
    call.policy = (ULONG_PTR)policy;

    qemu_syscall(&call.super);
}

#else

void qemu_CurrentScheduler_Create(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_Create *c = (struct qemu_CurrentScheduler_Create *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_CurrentScheduler_Create(QEMU_G2H(c->policy));
}

#endif

struct qemu_CurrentScheduler_Detach
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL CurrentScheduler_Detach(void)
{
    struct qemu_CurrentScheduler_Detach call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_DETACH);

    qemu_syscall(&call.super);
}

#else

void qemu_CurrentScheduler_Detach(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_Detach *c = (struct qemu_CurrentScheduler_Detach *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_CurrentScheduler_Detach();
}

#endif

struct qemu_CurrentScheduler_Get
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI Scheduler* CDECL CurrentScheduler_Get(void)
{
    struct qemu_CurrentScheduler_Get call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_GET);

    qemu_syscall(&call.super);

    return (Scheduler *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CurrentScheduler_Get(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_Get *c = (struct qemu_CurrentScheduler_Get *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_CurrentScheduler_Get());
}

#endif

struct qemu_CurrentScheduler_CreateScheduleGroup
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL CurrentScheduler_CreateScheduleGroup(void)
{
    struct qemu_CurrentScheduler_CreateScheduleGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_CREATESCHEDULEGROUP);

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CurrentScheduler_CreateScheduleGroup(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_CreateScheduleGroup *c = (struct qemu_CurrentScheduler_CreateScheduleGroup *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_CurrentScheduler_CreateScheduleGroup());
}

#endif

struct qemu_CurrentScheduler_GetNumberOfVirtualProcessors
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL CurrentScheduler_GetNumberOfVirtualProcessors(void)
{
    struct qemu_CurrentScheduler_GetNumberOfVirtualProcessors call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_GETNUMBEROFVIRTUALPROCESSORS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CurrentScheduler_GetNumberOfVirtualProcessors(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_GetNumberOfVirtualProcessors *c = (struct qemu_CurrentScheduler_GetNumberOfVirtualProcessors *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_CurrentScheduler_GetNumberOfVirtualProcessors();
}

#endif

struct qemu_CurrentScheduler_GetPolicy
{
    struct qemu_syscall super;
    uint64_t policy;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SchedulerPolicy* CDECL CurrentScheduler_GetPolicy(SchedulerPolicy *policy)
{
    struct qemu_CurrentScheduler_GetPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_GETPOLICY);
    call.policy = (ULONG_PTR)policy;

    qemu_syscall(&call.super);

    return (SchedulerPolicy *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CurrentScheduler_GetPolicy(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_GetPolicy *c = (struct qemu_CurrentScheduler_GetPolicy *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_CurrentScheduler_GetPolicy(QEMU_G2H(c->policy)));
}

#endif

struct qemu_CurrentScheduler_Id
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL CurrentScheduler_Id(void)
{
    struct qemu_CurrentScheduler_Id call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_ID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CurrentScheduler_Id(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_Id *c = (struct qemu_CurrentScheduler_Id *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_CurrentScheduler_Id();
}

#endif

struct qemu_CurrentScheduler_IsAvailableLocation
{
    struct qemu_syscall super;
    uint64_t placement;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL CurrentScheduler_IsAvailableLocation(const void *placement)
{
    struct qemu_CurrentScheduler_IsAvailableLocation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_ISAVAILABLELOCATION);
    call.placement = (ULONG_PTR)placement;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CurrentScheduler_IsAvailableLocation(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_IsAvailableLocation *c = (struct qemu_CurrentScheduler_IsAvailableLocation *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_CurrentScheduler_IsAvailableLocation(QEMU_G2H(c->placement));
}

#endif

struct qemu_CurrentScheduler_RegisterShutdownEvent
{
    struct qemu_syscall super;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL CurrentScheduler_RegisterShutdownEvent(HANDLE event)
{
    struct qemu_CurrentScheduler_RegisterShutdownEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CURRENTSCHEDULER_REGISTERSHUTDOWNEVENT);
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);
}

#else

void qemu_CurrentScheduler_RegisterShutdownEvent(struct qemu_syscall *call)
{
    struct qemu_CurrentScheduler_RegisterShutdownEvent *c = (struct qemu_CurrentScheduler_RegisterShutdownEvent *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    p_CurrentScheduler_RegisterShutdownEvent(QEMU_G2H(c->event));
}

#endif

struct qemu__CurrentScheduler__Get
{
    struct qemu_syscall super;
    uint64_t ret;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI _Scheduler* CDECL _CurrentScheduler__Get(_Scheduler *ret)
{
    struct qemu__CurrentScheduler__Get call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CURRENTSCHEDULER__GET);
    call.ret = (ULONG_PTR)ret;

    qemu_syscall(&call.super);

    return (_Scheduler *)(ULONG_PTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__CurrentScheduler__Get(struct qemu_syscall *call)
{
    struct qemu__CurrentScheduler__Get *c = (struct qemu__CurrentScheduler__Get *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__CurrentScheduler__Get(QEMU_G2H(c->ret)));
}

#endif

struct qemu__CurrentScheduler__GetNumberOfVirtualProcessors
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL _CurrentScheduler__GetNumberOfVirtualProcessors(void)
{
    struct qemu__CurrentScheduler__GetNumberOfVirtualProcessors call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CURRENTSCHEDULER__GETNUMBEROFVIRTUALPROCESSORS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__CurrentScheduler__GetNumberOfVirtualProcessors(struct qemu_syscall *call)
{
    struct qemu__CurrentScheduler__GetNumberOfVirtualProcessors *c = (struct qemu__CurrentScheduler__GetNumberOfVirtualProcessors *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__CurrentScheduler__GetNumberOfVirtualProcessors());
}

#endif

struct qemu__CurrentScheduler__Id
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int CDECL _CurrentScheduler__Id(void)
{
    struct qemu__CurrentScheduler__Id call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CURRENTSCHEDULER__ID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__CurrentScheduler__Id(struct qemu_syscall *call)
{
    struct qemu__CurrentScheduler__Id *c = (struct qemu__CurrentScheduler__Id *)(ULONG_PTR)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__CurrentScheduler__Id();
}

#endif
