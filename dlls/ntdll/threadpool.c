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
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

typedef void *PRTL_WORK_ITEM_ROUTINE, *PRTL_OVERLAPPED_COMPLETION_ROUTINE, *RTL_WAITORTIMERCALLBACKFUNC;

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlQueueWorkItem
{
    struct qemu_syscall super;
    uint64_t function;
    uint64_t context;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueueWorkItem(PRTL_WORK_ITEM_ROUTINE function, PVOID context, ULONG flags)
{
    struct qemu_RtlQueueWorkItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUEUEWORKITEM);
    call.function = (ULONG_PTR)function;
    call.context = (ULONG_PTR)context;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueueWorkItem(struct qemu_syscall *call)
{
    struct qemu_RtlQueueWorkItem *c = (struct qemu_RtlQueueWorkItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlQueueWorkItem(QEMU_G2H(c->function), QEMU_G2H(c->context), c->flags);
}

#endif

struct qemu_RtlSetIoCompletionCallback
{
    struct qemu_syscall super;
    uint64_t FileHandle;
    uint64_t Function;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetIoCompletionCallback(HANDLE FileHandle, PRTL_OVERLAPPED_COMPLETION_ROUTINE Function, ULONG Flags)
{
    struct qemu_RtlSetIoCompletionCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETIOCOMPLETIONCALLBACK);
    call.FileHandle = (ULONG_PTR)FileHandle;
    call.Function = (ULONG_PTR)Function;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetIoCompletionCallback(struct qemu_syscall *call)
{
    struct qemu_RtlSetIoCompletionCallback *c = (struct qemu_RtlSetIoCompletionCallback *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetIoCompletionCallback(QEMU_G2H(c->FileHandle), QEMU_G2H(c->Function), c->Flags);
}

#endif

struct qemu_RtlRegisterWait
{
    struct qemu_syscall super;
    uint64_t NewWaitObject;
    uint64_t Object;
    uint64_t Callback;
    uint64_t Context;
    uint64_t Milliseconds;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlRegisterWait(PHANDLE NewWaitObject, HANDLE Object, RTL_WAITORTIMERCALLBACKFUNC Callback, PVOID Context, ULONG Milliseconds, ULONG Flags)
{
    struct qemu_RtlRegisterWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLREGISTERWAIT);
    call.NewWaitObject = (ULONG_PTR)NewWaitObject;
    call.Object = (ULONG_PTR)Object;
    call.Callback = (ULONG_PTR)Callback;
    call.Context = (ULONG_PTR)Context;
    call.Milliseconds = Milliseconds;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlRegisterWait(struct qemu_syscall *call)
{
    struct qemu_RtlRegisterWait *c = (struct qemu_RtlRegisterWait *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlRegisterWait(QEMU_G2H(c->NewWaitObject), QEMU_G2H(c->Object), QEMU_G2H(c->Callback), QEMU_G2H(c->Context), c->Milliseconds, c->Flags);
}

#endif

struct qemu_RtlDeregisterWaitEx
{
    struct qemu_syscall super;
    uint64_t WaitHandle;
    uint64_t CompletionEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeregisterWaitEx(HANDLE WaitHandle, HANDLE CompletionEvent)
{
    struct qemu_RtlDeregisterWaitEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDEREGISTERWAITEX);
    call.WaitHandle = (ULONG_PTR)WaitHandle;
    call.CompletionEvent = (ULONG_PTR)CompletionEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeregisterWaitEx(struct qemu_syscall *call)
{
    struct qemu_RtlDeregisterWaitEx *c = (struct qemu_RtlDeregisterWaitEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDeregisterWaitEx(QEMU_G2H(c->WaitHandle), QEMU_G2H(c->CompletionEvent));
}

#endif

struct qemu_RtlDeregisterWait
{
    struct qemu_syscall super;
    uint64_t WaitHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeregisterWait(HANDLE WaitHandle)
{
    struct qemu_RtlDeregisterWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDEREGISTERWAIT);
    call.WaitHandle = (ULONG_PTR)WaitHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeregisterWait(struct qemu_syscall *call)
{
    struct qemu_RtlDeregisterWait *c = (struct qemu_RtlDeregisterWait *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDeregisterWait(QEMU_G2H(c->WaitHandle));
}

#endif

struct qemu_RtlCreateTimerQueue
{
    struct qemu_syscall super;
    uint64_t NewTimerQueue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateTimerQueue(PHANDLE NewTimerQueue)
{
    struct qemu_RtlCreateTimerQueue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATETIMERQUEUE);
    call.NewTimerQueue = (ULONG_PTR)NewTimerQueue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateTimerQueue(struct qemu_syscall *call)
{
    struct qemu_RtlCreateTimerQueue *c = (struct qemu_RtlCreateTimerQueue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateTimerQueue(QEMU_G2H(c->NewTimerQueue));
}

#endif

struct qemu_RtlDeleteTimerQueueEx
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
    uint64_t CompletionEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeleteTimerQueueEx(HANDLE TimerQueue, HANDLE CompletionEvent)
{
    struct qemu_RtlDeleteTimerQueueEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETETIMERQUEUEEX);
    call.TimerQueue = (ULONG_PTR)TimerQueue;
    call.CompletionEvent = (ULONG_PTR)CompletionEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeleteTimerQueueEx(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteTimerQueueEx *c = (struct qemu_RtlDeleteTimerQueueEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDeleteTimerQueueEx(QEMU_G2H(c->TimerQueue), QEMU_G2H(c->CompletionEvent));
}

#endif

struct qemu_RtlCreateTimer
{
    struct qemu_syscall super;
    uint64_t NewTimer;
    uint64_t TimerQueue;
    uint64_t Callback;
    uint64_t Parameter;
    uint64_t DueTime;
    uint64_t Period;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateTimer(PHANDLE NewTimer, HANDLE TimerQueue, RTL_WAITORTIMERCALLBACKFUNC Callback, PVOID Parameter, DWORD DueTime, DWORD Period, ULONG Flags)
{
    struct qemu_RtlCreateTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATETIMER);
    call.NewTimer = (ULONG_PTR)NewTimer;
    call.TimerQueue = (ULONG_PTR)TimerQueue;
    call.Callback = (ULONG_PTR)Callback;
    call.Parameter = (ULONG_PTR)Parameter;
    call.DueTime = DueTime;
    call.Period = Period;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateTimer(struct qemu_syscall *call)
{
    struct qemu_RtlCreateTimer *c = (struct qemu_RtlCreateTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateTimer(QEMU_G2H(c->NewTimer), QEMU_G2H(c->TimerQueue), QEMU_G2H(c->Callback), QEMU_G2H(c->Parameter), c->DueTime, c->Period, c->Flags);
}

#endif

struct qemu_RtlUpdateTimer
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
    uint64_t Timer;
    uint64_t DueTime;
    uint64_t Period;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpdateTimer(HANDLE TimerQueue, HANDLE Timer, DWORD DueTime, DWORD Period)
{
    struct qemu_RtlUpdateTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPDATETIMER);
    call.TimerQueue = (ULONG_PTR)TimerQueue;
    call.Timer = (ULONG_PTR)Timer;
    call.DueTime = DueTime;
    call.Period = Period;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpdateTimer(struct qemu_syscall *call)
{
    struct qemu_RtlUpdateTimer *c = (struct qemu_RtlUpdateTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpdateTimer(QEMU_G2H(c->TimerQueue), QEMU_G2H(c->Timer), c->DueTime, c->Period);
}

#endif

struct qemu_RtlDeleteTimer
{
    struct qemu_syscall super;
    uint64_t TimerQueue;
    uint64_t Timer;
    uint64_t CompletionEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeleteTimer(HANDLE TimerQueue, HANDLE Timer, HANDLE CompletionEvent)
{
    struct qemu_RtlDeleteTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETETIMER);
    call.TimerQueue = (ULONG_PTR)TimerQueue;
    call.Timer = (ULONG_PTR)Timer;
    call.CompletionEvent = (ULONG_PTR)CompletionEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeleteTimer(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteTimer *c = (struct qemu_RtlDeleteTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDeleteTimer(QEMU_G2H(c->TimerQueue), QEMU_G2H(c->Timer), QEMU_G2H(c->CompletionEvent));
}

#endif

struct qemu_TpAllocCleanupGroup
{
    struct qemu_syscall super;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI TpAllocCleanupGroup(TP_CLEANUP_GROUP **out)
{
    struct qemu_TpAllocCleanupGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPALLOCCLEANUPGROUP);
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpAllocCleanupGroup(struct qemu_syscall *call)
{
    struct qemu_TpAllocCleanupGroup *c = (struct qemu_TpAllocCleanupGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpAllocCleanupGroup(QEMU_G2H(c->out));
}

#endif

struct qemu_TpAllocPool
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI TpAllocPool(TP_POOL **out, PVOID reserved)
{
    struct qemu_TpAllocPool call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPALLOCPOOL);
    call.out = (ULONG_PTR)out;
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpAllocPool(struct qemu_syscall *call)
{
    struct qemu_TpAllocPool *c = (struct qemu_TpAllocPool *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpAllocPool(QEMU_G2H(c->out), QEMU_G2H(c->reserved));
}

#endif

struct qemu_TpAllocTimer
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI TpAllocTimer(TP_TIMER **out, PTP_TIMER_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_TpAllocTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPALLOCTIMER);
    call.out = (ULONG_PTR)out;
    call.callback = (ULONG_PTR)callback;
    call.userdata = (ULONG_PTR)userdata;
    call.environment = (ULONG_PTR)environment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpAllocTimer(struct qemu_syscall *call)
{
    struct qemu_TpAllocTimer *c = (struct qemu_TpAllocTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpAllocTimer(QEMU_G2H(c->out), QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment));
}

#endif

struct qemu_TpAllocWait
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI TpAllocWait(TP_WAIT **out, PTP_WAIT_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_TpAllocWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPALLOCWAIT);
    call.out = (ULONG_PTR)out;
    call.callback = (ULONG_PTR)callback;
    call.userdata = (ULONG_PTR)userdata;
    call.environment = (ULONG_PTR)environment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpAllocWait(struct qemu_syscall *call)
{
    struct qemu_TpAllocWait *c = (struct qemu_TpAllocWait *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpAllocWait(QEMU_G2H(c->out), QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment));
}

#endif

struct qemu_TpAllocWork
{
    struct qemu_syscall super;
    uint64_t out;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
    uint64_t wrapper;
};

struct qemu_TpAllocWork_cb
{
    uint64_t cb, instance, context, work;
};

#ifdef QEMU_DLL_GUEST

struct tp_work
{
    TP_WORK *host;
    uint64_t guest_cb, guest_data;
};

static void __fastcall TpAllocWork_guest_cb(struct qemu_TpAllocWork_cb *data)
{
    PTP_WORK_CALLBACK cb = (PTP_WORK_CALLBACK)(ULONG_PTR)data->cb;
    cb((PTP_CALLBACK_INSTANCE)(ULONG_PTR)data->instance, (void *)(ULONG_PTR)data->context, (TP_WORK *)(ULONG_PTR)data->work);
}

WINBASEAPI NTSTATUS WINAPI TpAllocWork(TP_WORK **out, PTP_WORK_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_TpAllocWork call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPALLOCWORK);
    call.callback = (ULONG_PTR)callback;
    call.userdata = (ULONG_PTR)userdata;
    call.environment = (ULONG_PTR)environment;
    call.wrapper = (ULONG_PTR)TpAllocWork_guest_cb;

    qemu_syscall(&call.super);

    if (call.super.iret == STATUS_SUCCESS)
        *out = (TP_WORK *)(ULONG_PTR)call.out;

    return call.super.iret;
}

#else

struct tp_work
{
    TP_WORK *host;
    uint64_t wrapper, guest_cb, guest_ctx;
};

static void WINAPI TpAllocWork_host_cb(TP_CALLBACK_INSTANCE *instance, void *context, TP_WORK *work)
{
    struct tp_work *w = (struct tp_work *)context;
    struct qemu_TpAllocWork_cb call;

    WINE_TRACE("Calling guest callback 0x%lx(%p, 0x%lx, %p).\n", (unsigned long)w->guest_cb, instance,
            (unsigned long)w->guest_ctx, w);

    call.cb = w->guest_cb;
    call.instance = (ULONG_PTR)instance;
    call.context = w->guest_ctx;
    call.work = (ULONG_PTR)w;
    qemu_ops->qemu_execute(QEMU_G2H(w->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest callback returned.\n");
}

void qemu_TpAllocWork(struct qemu_syscall *call)
{
    struct qemu_TpAllocWork *c = (struct qemu_TpAllocWork *)call;
    struct tp_work *out;

    WINE_TRACE("\n");
    out = HeapAlloc(GetProcessHeap(), 0, sizeof(*out));
    out->wrapper = c->wrapper;
    out->guest_cb = c->callback;
    out->guest_ctx = c->userdata;

    c->super.iret = TpAllocWork(&out->host, c->callback ? TpAllocWork_host_cb : NULL,
            out, QEMU_G2H(c->environment));

    if (c->super.iret == STATUS_SUCCESS)
        c->out = QEMU_H2G(out);
    else
        HeapFree(GetProcessHeap(), 0, out);
}

#endif

struct qemu_TpCallbackLeaveCriticalSectionOnCompletion
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t crit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpCallbackLeaveCriticalSectionOnCompletion(TP_CALLBACK_INSTANCE *instance, CRITICAL_SECTION *crit)
{
    struct qemu_TpCallbackLeaveCriticalSectionOnCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPCALLBACKLEAVECRITICALSECTIONONCOMPLETION);
    call.instance = (ULONG_PTR)instance;
    call.crit = (ULONG_PTR)crit;

    qemu_syscall(&call.super);
}

#else

void qemu_TpCallbackLeaveCriticalSectionOnCompletion(struct qemu_syscall *call)
{
    struct qemu_TpCallbackLeaveCriticalSectionOnCompletion *c = (struct qemu_TpCallbackLeaveCriticalSectionOnCompletion *)call;
    WINE_FIXME("Unverified!\n");
    TpCallbackLeaveCriticalSectionOnCompletion(QEMU_G2H(c->instance), QEMU_G2H(c->crit));
}

#endif

struct qemu_TpCallbackMayRunLong
{
    struct qemu_syscall super;
    uint64_t instance;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI TpCallbackMayRunLong(TP_CALLBACK_INSTANCE *instance)
{
    struct qemu_TpCallbackMayRunLong call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPCALLBACKMAYRUNLONG);
    call.instance = (ULONG_PTR)instance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpCallbackMayRunLong(struct qemu_syscall *call)
{
    struct qemu_TpCallbackMayRunLong *c = (struct qemu_TpCallbackMayRunLong *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpCallbackMayRunLong(QEMU_G2H(c->instance));
}

#endif

struct qemu_TpCallbackReleaseMutexOnCompletion
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t mutex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpCallbackReleaseMutexOnCompletion(TP_CALLBACK_INSTANCE *instance, HANDLE mutex)
{
    struct qemu_TpCallbackReleaseMutexOnCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPCALLBACKRELEASEMUTEXONCOMPLETION);
    call.instance = (ULONG_PTR)instance;
    call.mutex = (ULONG_PTR)mutex;

    qemu_syscall(&call.super);
}

#else

void qemu_TpCallbackReleaseMutexOnCompletion(struct qemu_syscall *call)
{
    struct qemu_TpCallbackReleaseMutexOnCompletion *c = (struct qemu_TpCallbackReleaseMutexOnCompletion *)call;
    WINE_FIXME("Unverified!\n");
    TpCallbackReleaseMutexOnCompletion(QEMU_G2H(c->instance), QEMU_G2H(c->mutex));
}

#endif

struct qemu_TpCallbackReleaseSemaphoreOnCompletion
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t semaphore;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpCallbackReleaseSemaphoreOnCompletion(TP_CALLBACK_INSTANCE *instance, HANDLE semaphore, DWORD count)
{
    struct qemu_TpCallbackReleaseSemaphoreOnCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPCALLBACKRELEASESEMAPHOREONCOMPLETION);
    call.instance = (ULONG_PTR)instance;
    call.semaphore = (ULONG_PTR)semaphore;
    call.count = count;

    qemu_syscall(&call.super);
}

#else

void qemu_TpCallbackReleaseSemaphoreOnCompletion(struct qemu_syscall *call)
{
    struct qemu_TpCallbackReleaseSemaphoreOnCompletion *c = (struct qemu_TpCallbackReleaseSemaphoreOnCompletion *)call;
    WINE_FIXME("Unverified!\n");
    TpCallbackReleaseSemaphoreOnCompletion(QEMU_G2H(c->instance), QEMU_G2H(c->semaphore), c->count);
}

#endif

struct qemu_TpCallbackSetEventOnCompletion
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpCallbackSetEventOnCompletion(TP_CALLBACK_INSTANCE *instance, HANDLE event)
{
    struct qemu_TpCallbackSetEventOnCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPCALLBACKSETEVENTONCOMPLETION);
    call.instance = (ULONG_PTR)instance;
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);
}

#else

void qemu_TpCallbackSetEventOnCompletion(struct qemu_syscall *call)
{
    struct qemu_TpCallbackSetEventOnCompletion *c = (struct qemu_TpCallbackSetEventOnCompletion *)call;
    WINE_FIXME("Unverified!\n");
    TpCallbackSetEventOnCompletion(QEMU_G2H(c->instance), QEMU_G2H(c->event));
}

#endif

struct qemu_TpCallbackUnloadDllOnCompletion
{
    struct qemu_syscall super;
    uint64_t instance;
    uint64_t module;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpCallbackUnloadDllOnCompletion(TP_CALLBACK_INSTANCE *instance, HMODULE module)
{
    struct qemu_TpCallbackUnloadDllOnCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPCALLBACKUNLOADDLLONCOMPLETION);
    call.instance = (ULONG_PTR)instance;
    call.module = (ULONG_PTR)module;

    qemu_syscall(&call.super);
}

#else

void qemu_TpCallbackUnloadDllOnCompletion(struct qemu_syscall *call)
{
    struct qemu_TpCallbackUnloadDllOnCompletion *c = (struct qemu_TpCallbackUnloadDllOnCompletion *)call;
    WINE_FIXME("Unverified!\n");
    TpCallbackUnloadDllOnCompletion(QEMU_G2H(c->instance), QEMU_G2H(c->module));
}

#endif

struct qemu_TpDisassociateCallback
{
    struct qemu_syscall super;
    uint64_t instance;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpDisassociateCallback(TP_CALLBACK_INSTANCE *instance)
{
    struct qemu_TpDisassociateCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPDISASSOCIATECALLBACK);
    call.instance = (ULONG_PTR)instance;

    qemu_syscall(&call.super);
}

#else

void qemu_TpDisassociateCallback(struct qemu_syscall *call)
{
    struct qemu_TpDisassociateCallback *c = (struct qemu_TpDisassociateCallback *)call;
    WINE_FIXME("Unverified!\n");
    TpDisassociateCallback(QEMU_G2H(c->instance));
}

#endif

struct qemu_TpIsTimerSet
{
    struct qemu_syscall super;
    uint64_t timer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TpIsTimerSet(TP_TIMER *timer)
{
    struct qemu_TpIsTimerSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPISTIMERSET);
    call.timer = (ULONG_PTR)timer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpIsTimerSet(struct qemu_syscall *call)
{
    struct qemu_TpIsTimerSet *c = (struct qemu_TpIsTimerSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpIsTimerSet(QEMU_G2H(c->timer));
}

#endif

struct qemu_TpPostWork
{
    struct qemu_syscall super;
    uint64_t work;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpPostWork(TP_WORK *work)
{
    struct qemu_TpPostWork call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPPOSTWORK);
    call.work = (ULONG_PTR)work;

    qemu_syscall(&call.super);
}

#else

void qemu_TpPostWork(struct qemu_syscall *call)
{
    struct qemu_TpPostWork *c = (struct qemu_TpPostWork *)call;
    struct tp_work *work;
    WINE_TRACE("\n");

    work = QEMU_G2H(c->work);
    TpPostWork(work->host);
}

#endif

struct qemu_TpReleaseCleanupGroup
{
    struct qemu_syscall super;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpReleaseCleanupGroup(TP_CLEANUP_GROUP *group)
{
    struct qemu_TpReleaseCleanupGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPRELEASECLEANUPGROUP);
    call.group = (ULONG_PTR)group;

    qemu_syscall(&call.super);
}

#else

void qemu_TpReleaseCleanupGroup(struct qemu_syscall *call)
{
    struct qemu_TpReleaseCleanupGroup *c = (struct qemu_TpReleaseCleanupGroup *)call;
    WINE_FIXME("Unverified!\n");
    TpReleaseCleanupGroup(QEMU_G2H(c->group));
}

#endif

struct qemu_TpReleaseCleanupGroupMembers
{
    struct qemu_syscall super;
    uint64_t group;
    uint64_t cancel_pending;
    uint64_t userdata;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpReleaseCleanupGroupMembers(TP_CLEANUP_GROUP *group, BOOL cancel_pending, PVOID userdata)
{
    struct qemu_TpReleaseCleanupGroupMembers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPRELEASECLEANUPGROUPMEMBERS);
    call.group = (ULONG_PTR)group;
    call.cancel_pending = cancel_pending;
    call.userdata = (ULONG_PTR)userdata;

    qemu_syscall(&call.super);
}

#else

void qemu_TpReleaseCleanupGroupMembers(struct qemu_syscall *call)
{
    struct qemu_TpReleaseCleanupGroupMembers *c = (struct qemu_TpReleaseCleanupGroupMembers *)call;
    WINE_FIXME("Unverified!\n");
    TpReleaseCleanupGroupMembers(QEMU_G2H(c->group), c->cancel_pending, QEMU_G2H(c->userdata));
}

#endif

struct qemu_TpReleasePool
{
    struct qemu_syscall super;
    uint64_t pool;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpReleasePool(TP_POOL *pool)
{
    struct qemu_TpReleasePool call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPRELEASEPOOL);
    call.pool = (ULONG_PTR)pool;

    qemu_syscall(&call.super);
}

#else

void qemu_TpReleasePool(struct qemu_syscall *call)
{
    struct qemu_TpReleasePool *c = (struct qemu_TpReleasePool *)call;
    WINE_FIXME("Unverified!\n");
    TpReleasePool(QEMU_G2H(c->pool));
}

#endif

struct qemu_TpReleaseTimer
{
    struct qemu_syscall super;
    uint64_t timer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpReleaseTimer(TP_TIMER *timer)
{
    struct qemu_TpReleaseTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPRELEASETIMER);
    call.timer = (ULONG_PTR)timer;

    qemu_syscall(&call.super);
}

#else

void qemu_TpReleaseTimer(struct qemu_syscall *call)
{
    struct qemu_TpReleaseTimer *c = (struct qemu_TpReleaseTimer *)call;
    WINE_FIXME("Unverified!\n");
    TpReleaseTimer(QEMU_G2H(c->timer));
}

#endif

struct qemu_TpReleaseWait
{
    struct qemu_syscall super;
    uint64_t wait;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpReleaseWait(TP_WAIT *wait)
{
    struct qemu_TpReleaseWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPRELEASEWAIT);
    call.wait = (ULONG_PTR)wait;

    qemu_syscall(&call.super);
}

#else

void qemu_TpReleaseWait(struct qemu_syscall *call)
{
    struct qemu_TpReleaseWait *c = (struct qemu_TpReleaseWait *)call;
    WINE_FIXME("Unverified!\n");
    TpReleaseWait(QEMU_G2H(c->wait));
}

#endif

struct qemu_TpReleaseWork
{
    struct qemu_syscall super;
    uint64_t work;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpReleaseWork(TP_WORK *work)
{
    struct qemu_TpReleaseWork call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPRELEASEWORK);
    call.work = (ULONG_PTR)work;

    qemu_syscall(&call.super);
}

#else

void qemu_TpReleaseWork(struct qemu_syscall *call)
{
    struct qemu_TpReleaseWork *c = (struct qemu_TpReleaseWork *)call;
    struct tp_work *work;
    WINE_TRACE("\n");

    work = QEMU_G2H(c->work);
    TpReleaseWork(work->host);
    HeapFree(GetProcessHeap(), 0, work);
}

#endif

struct qemu_TpSetPoolMaxThreads
{
    struct qemu_syscall super;
    uint64_t pool;
    uint64_t maximum;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpSetPoolMaxThreads(TP_POOL *pool, DWORD maximum)
{
    struct qemu_TpSetPoolMaxThreads call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPSETPOOLMAXTHREADS);
    call.pool = (ULONG_PTR)pool;
    call.maximum = maximum;

    qemu_syscall(&call.super);
}

#else

void qemu_TpSetPoolMaxThreads(struct qemu_syscall *call)
{
    struct qemu_TpSetPoolMaxThreads *c = (struct qemu_TpSetPoolMaxThreads *)call;
    WINE_FIXME("Unverified!\n");
    TpSetPoolMaxThreads(QEMU_G2H(c->pool), c->maximum);
}

#endif

struct qemu_TpSetPoolMinThreads
{
    struct qemu_syscall super;
    uint64_t pool;
    uint64_t minimum;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TpSetPoolMinThreads(TP_POOL *pool, DWORD minimum)
{
    struct qemu_TpSetPoolMinThreads call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPSETPOOLMINTHREADS);
    call.pool = (ULONG_PTR)pool;
    call.minimum = minimum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpSetPoolMinThreads(struct qemu_syscall *call)
{
    struct qemu_TpSetPoolMinThreads *c = (struct qemu_TpSetPoolMinThreads *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpSetPoolMinThreads(QEMU_G2H(c->pool), c->minimum);
}

#endif

struct qemu_TpSetTimer
{
    struct qemu_syscall super;
    uint64_t timer;
    uint64_t timeout;
    uint64_t period;
    uint64_t window_length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpSetTimer(TP_TIMER *timer, LARGE_INTEGER *timeout, LONG period, LONG window_length)
{
    struct qemu_TpSetTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPSETTIMER);
    call.timer = (ULONG_PTR)timer;
    call.timeout = (ULONG_PTR)timeout;
    call.period = period;
    call.window_length = window_length;

    qemu_syscall(&call.super);
}

#else

void qemu_TpSetTimer(struct qemu_syscall *call)
{
    struct qemu_TpSetTimer *c = (struct qemu_TpSetTimer *)call;
    WINE_FIXME("Unverified!\n");
    TpSetTimer(QEMU_G2H(c->timer), QEMU_G2H(c->timeout), c->period, c->window_length);
}

#endif

struct qemu_TpSetWait
{
    struct qemu_syscall super;
    uint64_t wait;
    uint64_t handle;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpSetWait(TP_WAIT *wait, HANDLE handle, LARGE_INTEGER *timeout)
{
    struct qemu_TpSetWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPSETWAIT);
    call.wait = (ULONG_PTR)wait;
    call.handle = (ULONG_PTR)handle;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);
}

#else

void qemu_TpSetWait(struct qemu_syscall *call)
{
    struct qemu_TpSetWait *c = (struct qemu_TpSetWait *)call;
    WINE_FIXME("Unverified!\n");
    TpSetWait(QEMU_G2H(c->wait), QEMU_G2H(c->handle), QEMU_G2H(c->timeout));
}

#endif

struct qemu_TpSimpleTryPost
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI TpSimpleTryPost(PTP_SIMPLE_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_TpSimpleTryPost call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPSIMPLETRYPOST);
    call.callback = (ULONG_PTR)callback;
    call.userdata = (ULONG_PTR)userdata;
    call.environment = (ULONG_PTR)environment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TpSimpleTryPost(struct qemu_syscall *call)
{
    struct qemu_TpSimpleTryPost *c = (struct qemu_TpSimpleTryPost *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TpSimpleTryPost(QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment));
}

#endif

struct qemu_TpWaitForTimer
{
    struct qemu_syscall super;
    uint64_t timer;
    uint64_t cancel_pending;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpWaitForTimer(TP_TIMER *timer, BOOL cancel_pending)
{
    struct qemu_TpWaitForTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPWAITFORTIMER);
    call.timer = (ULONG_PTR)timer;
    call.cancel_pending = cancel_pending;

    qemu_syscall(&call.super);
}

#else

void qemu_TpWaitForTimer(struct qemu_syscall *call)
{
    struct qemu_TpWaitForTimer *c = (struct qemu_TpWaitForTimer *)call;
    WINE_FIXME("Unverified!\n");
    TpWaitForTimer(QEMU_G2H(c->timer), c->cancel_pending);
}

#endif

struct qemu_TpWaitForWait
{
    struct qemu_syscall super;
    uint64_t wait;
    uint64_t cancel_pending;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpWaitForWait(TP_WAIT *wait, BOOL cancel_pending)
{
    struct qemu_TpWaitForWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPWAITFORWAIT);
    call.wait = (ULONG_PTR)wait;
    call.cancel_pending = cancel_pending;

    qemu_syscall(&call.super);
}

#else

void qemu_TpWaitForWait(struct qemu_syscall *call)
{
    struct qemu_TpWaitForWait *c = (struct qemu_TpWaitForWait *)call;
    WINE_FIXME("Unverified!\n");
    TpWaitForWait(QEMU_G2H(c->wait), c->cancel_pending);
}

#endif

struct qemu_TpWaitForWork
{
    struct qemu_syscall super;
    uint64_t work;
    uint64_t cancel_pending;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI TpWaitForWork(TP_WORK *work, BOOL cancel_pending)
{
    struct qemu_TpWaitForWork call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TPWAITFORWORK);
    call.work = (ULONG_PTR)work;
    call.cancel_pending = cancel_pending;

    qemu_syscall(&call.super);
}

#else

void qemu_TpWaitForWork(struct qemu_syscall *call)
{
    struct qemu_TpWaitForWork *c = (struct qemu_TpWaitForWork *)call;
    struct tp_work *work;
    WINE_TRACE("\n");

    work = QEMU_G2H(c->work);
    TpWaitForWork(work->host, c->cancel_pending);
}

#endif

