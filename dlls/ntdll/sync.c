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

typedef enum _SEMAPHORE_INFORMATION_CLASS
{
    SemaphoreBasicInformation
}
SEMAPHORE_INFORMATION_CLASS, *PSEMAPHORE_INFORMATION_CLASS;

typedef enum _EVENT_INFORMATION_CLASS
{
    EventBasicInformation
}
EVENT_INFORMATION_CLASS, *PEVENT_INFORMATION_CLASS;

typedef enum _MUTANT_INFORMATION_CLASS
{
    MutantBasicInformation
}
MUTANT_INFORMATION_CLASS, *PMUTANT_INFORMATION_CLASS;

typedef enum _TIMER_INFORMATION_CLASS
{
    TimerBasicInformation = 0
}
TIMER_INFORMATION_CLASS;

typedef enum _IO_COMPLETION_INFORMATION_CLASS
{
    IoCompletionBasicInformation
}
IO_COMPLETION_INFORMATION_CLASS, *PIO_COMPLETION_INFORMATION_CLASS;

typedef void *PTIMER_APC_ROUTINE;

typedef struct _FILE_IO_COMPLETION_INFORMATION FILE_IO_COMPLETION_INFORMATION;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_NtCreateSemaphore
{
    struct qemu_syscall super;
    uint64_t SemaphoreHandle;
    uint64_t access;
    uint64_t attr;
    uint64_t InitialCount;
    uint64_t MaximumCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateSemaphore(PHANDLE SemaphoreHandle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr, LONG InitialCount, LONG MaximumCount)
{
    struct qemu_NtCreateSemaphore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATESEMAPHORE);
    call.SemaphoreHandle = (ULONG_PTR)SemaphoreHandle;
    call.access = access;
    call.attr = (ULONG_PTR)attr;
    call.InitialCount = InitialCount;
    call.MaximumCount = MaximumCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateSemaphore(struct qemu_syscall *call)
{
    struct qemu_NtCreateSemaphore *c = (struct qemu_NtCreateSemaphore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateSemaphore(QEMU_G2H(c->SemaphoreHandle), c->access, QEMU_G2H(c->attr), c->InitialCount, c->MaximumCount);
}

#endif

struct qemu_NtOpenSemaphore
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenSemaphore(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenSemaphore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENSEMAPHORE);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenSemaphore(struct qemu_syscall *call)
{
    struct qemu_NtOpenSemaphore *c = (struct qemu_NtOpenSemaphore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenSemaphore(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtQuerySemaphore
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t len;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySemaphore(HANDLE handle, SEMAPHORE_INFORMATION_CLASS class, void *info, ULONG len, ULONG *ret_len)
{
    struct qemu_NtQuerySemaphore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSEMAPHORE);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySemaphore(struct qemu_syscall *call)
{
    struct qemu_NtQuerySemaphore *c = (struct qemu_NtQuerySemaphore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySemaphore(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->info), c->len, QEMU_G2H(c->ret_len));
}

#endif

struct qemu_NtReleaseSemaphore
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
    uint64_t previous;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtReleaseSemaphore(HANDLE handle, ULONG count, PULONG previous)
{
    struct qemu_NtReleaseSemaphore call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRELEASESEMAPHORE);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;
    call.previous = (ULONG_PTR)previous;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReleaseSemaphore(struct qemu_syscall *call)
{
    struct qemu_NtReleaseSemaphore *c = (struct qemu_NtReleaseSemaphore *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtReleaseSemaphore(QEMU_G2H(c->handle), c->count, QEMU_G2H(c->previous));
}

#endif

struct qemu_NtCreateEvent
{
    struct qemu_syscall super;
    uint64_t EventHandle;
    uint64_t DesiredAccess;
    uint64_t attr;
    uint64_t type;
    uint64_t InitialState;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateEvent(PHANDLE EventHandle, ACCESS_MASK DesiredAccess, const OBJECT_ATTRIBUTES *attr, EVENT_TYPE type, BOOLEAN InitialState)
{
    struct qemu_NtCreateEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEEVENT);
    call.EventHandle = (ULONG_PTR)EventHandle;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.attr = (ULONG_PTR)attr;
    call.type = (ULONG_PTR)type;
    call.InitialState = (ULONG_PTR)InitialState;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateEvent(struct qemu_syscall *call)
{
    struct qemu_NtCreateEvent *c = (struct qemu_NtCreateEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateEvent(QEMU_G2H(c->EventHandle), c->DesiredAccess, QEMU_G2H(c->attr), c->type, c->InitialState);
}

#endif

struct qemu_NtOpenEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenEvent(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENEVENT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenEvent(struct qemu_syscall *call)
{
    struct qemu_NtOpenEvent *c = (struct qemu_NtOpenEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenEvent(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtSetEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t NumberOfThreadsReleased;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetEvent(HANDLE handle, PULONG NumberOfThreadsReleased)
{
    struct qemu_NtSetEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETEVENT);
    call.handle = (ULONG_PTR)handle;
    call.NumberOfThreadsReleased = (ULONG_PTR)NumberOfThreadsReleased;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetEvent(struct qemu_syscall *call)
{
    struct qemu_NtSetEvent *c = (struct qemu_NtSetEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetEvent(QEMU_G2H(c->handle), QEMU_G2H(c->NumberOfThreadsReleased));
}

#endif

struct qemu_NtResetEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t NumberOfThreadsReleased;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtResetEvent(HANDLE handle, PULONG NumberOfThreadsReleased)
{
    struct qemu_NtResetEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRESETEVENT);
    call.handle = (ULONG_PTR)handle;
    call.NumberOfThreadsReleased = (ULONG_PTR)NumberOfThreadsReleased;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtResetEvent(struct qemu_syscall *call)
{
    struct qemu_NtResetEvent *c = (struct qemu_NtResetEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtResetEvent(QEMU_G2H(c->handle), QEMU_G2H(c->NumberOfThreadsReleased));
}

#endif

struct qemu_NtClearEvent
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtClearEvent (HANDLE handle)
{
    struct qemu_NtClearEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCLEAREVENT);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtClearEvent(struct qemu_syscall *call)
{
    struct qemu_NtClearEvent *c = (struct qemu_NtClearEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtClearEvent(QEMU_G2H(c->handle));
}

#endif

struct qemu_NtPulseEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t PulseCount;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtPulseEvent(HANDLE handle, PULONG PulseCount)
{
    struct qemu_NtPulseEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTPULSEEVENT);
    call.handle = (ULONG_PTR)handle;
    call.PulseCount = (ULONG_PTR)PulseCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtPulseEvent(struct qemu_syscall *call)
{
    struct qemu_NtPulseEvent *c = (struct qemu_NtPulseEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtPulseEvent(QEMU_G2H(c->handle), QEMU_G2H(c->PulseCount));
}

#endif

struct qemu_NtQueryEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t len;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryEvent(HANDLE handle, EVENT_INFORMATION_CLASS class, void *info, ULONG len, ULONG *ret_len)
{
    struct qemu_NtQueryEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYEVENT);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryEvent(struct qemu_syscall *call)
{
    struct qemu_NtQueryEvent *c = (struct qemu_NtQueryEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryEvent(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->info), c->len, QEMU_G2H(c->ret_len));
}

#endif

struct qemu_NtCreateMutant
{
    struct qemu_syscall super;
    uint64_t MutantHandle;
    uint64_t access;
    uint64_t attr;
    uint64_t InitialOwner;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateMutant(OUT HANDLE* MutantHandle, ACCESS_MASK access, const OBJECT_ATTRIBUTES* attr, BOOLEAN InitialOwner)
{
    struct qemu_NtCreateMutant call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEMUTANT);
    call.MutantHandle = (ULONG_PTR)MutantHandle;
    call.access = access;
    call.InitialOwner = (ULONG_PTR)attr;
    call.InitialOwner = InitialOwner;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateMutant(struct qemu_syscall *call)
{
    struct qemu_NtCreateMutant *c = (struct qemu_NtCreateMutant *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateMutant(QEMU_G2H(c->MutantHandle), c->access, QEMU_G2H(c->attr), c->InitialOwner);
}

#endif

struct qemu_NtOpenMutant
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenMutant(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenMutant call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENMUTANT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenMutant(struct qemu_syscall *call)
{
    struct qemu_NtOpenMutant *c = (struct qemu_NtOpenMutant *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenMutant(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtReleaseMutant
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t prev_count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtReleaseMutant(IN HANDLE handle,PLONG prev_count)
{
    struct qemu_NtReleaseMutant call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRELEASEMUTANT);
    call.handle = (ULONG_PTR)handle;
    call.prev_count = (ULONG_PTR)prev_count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReleaseMutant(struct qemu_syscall *call)
{
    struct qemu_NtReleaseMutant *c = (struct qemu_NtReleaseMutant *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtReleaseMutant((HANDLE)c->handle, QEMU_G2H(c->prev_count));
}

#endif

struct qemu_NtQueryMutant
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t len;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryMutant(HANDLE handle, MUTANT_INFORMATION_CLASS class, void *info, ULONG len, ULONG *ret_len)
{
    struct qemu_NtQueryMutant call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYMUTANT);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryMutant(struct qemu_syscall *call)
{
    struct qemu_NtQueryMutant *c = (struct qemu_NtQueryMutant *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryMutant(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->info), c->len, QEMU_G2H(c->ret_len));
}

#endif

struct qemu_NtCreateJobObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateJobObject(PHANDLE handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtCreateJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEJOBOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateJobObject(struct qemu_syscall *call)
{
    struct qemu_NtCreateJobObject *c = (struct qemu_NtCreateJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateJobObject(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtOpenJobObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenJobObject(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENJOBOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenJobObject(struct qemu_syscall *call)
{
    struct qemu_NtOpenJobObject *c = (struct qemu_NtOpenJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenJobObject(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtTerminateJobObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtTerminateJobObject(HANDLE handle, NTSTATUS status)
{
    struct qemu_NtTerminateJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTTERMINATEJOBOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.status = (ULONG_PTR)status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtTerminateJobObject(struct qemu_syscall *call)
{
    struct qemu_NtTerminateJobObject *c = (struct qemu_NtTerminateJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtTerminateJobObject(QEMU_G2H(c->handle), c->status);
}

#endif

struct qemu_NtQueryInformationJobObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t len;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryInformationJobObject(HANDLE handle, JOBOBJECTINFOCLASS class, PVOID info, ULONG len, PULONG ret_len)
{
    struct qemu_NtQueryInformationJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYINFORMATIONJOBOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryInformationJobObject(struct qemu_syscall *call)
{
    struct qemu_NtQueryInformationJobObject *c = (struct qemu_NtQueryInformationJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryInformationJobObject(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->info), c->len, QEMU_G2H(c->ret_len));
}

#endif

struct qemu_NtSetInformationJobObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t info;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetInformationJobObject(HANDLE handle, JOBOBJECTINFOCLASS class, PVOID info, ULONG len)
{
    struct qemu_NtSetInformationJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINFORMATIONJOBOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetInformationJobObject(struct qemu_syscall *call)
{
    struct qemu_NtSetInformationJobObject *c = (struct qemu_NtSetInformationJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetInformationJobObject(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->info), c->len);
}

#endif

struct qemu_NtIsProcessInJob
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t job;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtIsProcessInJob(HANDLE process, HANDLE job)
{
    struct qemu_NtIsProcessInJob call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTISPROCESSINJOB);
    call.process = (ULONG_PTR)process;
    call.job = (ULONG_PTR)job;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtIsProcessInJob(struct qemu_syscall *call)
{
    struct qemu_NtIsProcessInJob *c = (struct qemu_NtIsProcessInJob *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtIsProcessInJob(QEMU_G2H(c->process), QEMU_G2H(c->job));
}

#endif

struct qemu_NtAssignProcessToJobObject
{
    struct qemu_syscall super;
    uint64_t job;
    uint64_t process;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAssignProcessToJobObject(HANDLE job, HANDLE process)
{
    struct qemu_NtAssignProcessToJobObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTASSIGNPROCESSTOJOBOBJECT);
    call.job = (ULONG_PTR)job;
    call.process = (ULONG_PTR)process;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAssignProcessToJobObject(struct qemu_syscall *call)
{
    struct qemu_NtAssignProcessToJobObject *c = (struct qemu_NtAssignProcessToJobObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAssignProcessToJobObject(QEMU_G2H(c->job), QEMU_G2H(c->process));
}

#endif

struct qemu_NtCreateTimer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t timer_type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateTimer(OUT HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr, TIMER_TYPE timer_type)
{
    struct qemu_NtCreateTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATETIMER);
    call.handle = (ULONG_PTR)handle;
    call.access = access;
    call.attr = (ULONG_PTR)attr;
    call.timer_type = timer_type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateTimer(struct qemu_syscall *call)
{
    struct qemu_NtCreateTimer *c = (struct qemu_NtCreateTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateTimer(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr), c->timer_type);
}

#endif

struct qemu_NtOpenTimer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenTimer(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENTIMER);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenTimer(struct qemu_syscall *call)
{
    struct qemu_NtOpenTimer *c = (struct qemu_NtOpenTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenTimer(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtSetTimer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t when;
    uint64_t callback;
    uint64_t callback_arg;
    uint64_t resume;
    uint64_t period;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetTimer(HANDLE handle, const LARGE_INTEGER* when, PTIMER_APC_ROUTINE callback, PVOID callback_arg, BOOLEAN resume, ULONG period,PBOOLEAN state)
{
    struct qemu_NtSetTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETTIMER);
    call.handle = (ULONG_PTR)handle;
    call.when = (ULONG_PTR)when;
    call.callback = (ULONG_PTR)callback;
    call.callback_arg = (ULONG_PTR)callback_arg;
    call.resume = resume;
    call.period = period;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetTimer(struct qemu_syscall *call)
{
    struct qemu_NtSetTimer *c = (struct qemu_NtSetTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetTimer((HANDLE)c->handle, QEMU_G2H(c->when), QEMU_G2H(c->callback), QEMU_G2H(c->callback_arg), c->resume, c->period, QEMU_G2H(c->state));
}

#endif

struct qemu_NtCancelTimer
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCancelTimer(HANDLE handle,BOOLEAN* state)
{
    struct qemu_NtCancelTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCANCELTIMER);
    call.handle = (ULONG_PTR)handle;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCancelTimer(struct qemu_syscall *call)
{
    struct qemu_NtCancelTimer *c = (struct qemu_NtCancelTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCancelTimer((HANDLE)c->handle, QEMU_G2H(c->state));
}

#endif

struct qemu_NtQueryTimer
{
    struct qemu_syscall super;
    uint64_t TimerHandle;
    uint64_t TimerInformationClass;
    uint64_t TimerInformation;
    uint64_t Length;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryTimer(HANDLE TimerHandle, TIMER_INFORMATION_CLASS TimerInformationClass, PVOID TimerInformation, ULONG Length, PULONG ReturnLength)
{
    struct qemu_NtQueryTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYTIMER);
    call.TimerHandle = (ULONG_PTR)TimerHandle;
    call.TimerInformationClass = (ULONG_PTR)TimerInformationClass;
    call.TimerInformation = (ULONG_PTR)TimerInformation;
    call.Length = (ULONG_PTR)Length;
    call.ReturnLength = (ULONG_PTR)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryTimer(struct qemu_syscall *call)
{
    struct qemu_NtQueryTimer *c = (struct qemu_NtQueryTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryTimer(QEMU_G2H(c->TimerHandle), c->TimerInformationClass, QEMU_G2H(c->TimerInformation), c->Length, QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_NtQueryTimerResolution
{
    struct qemu_syscall super;
    uint64_t min_resolution;
    uint64_t max_resolution;
    uint64_t current_resolution;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryTimerResolution(OUT ULONG* min_resolution,ULONG* max_resolution,ULONG* current_resolution)
{
    struct qemu_NtQueryTimerResolution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYTIMERRESOLUTION);
    call.min_resolution = (ULONG_PTR)min_resolution;
    call.max_resolution = (ULONG_PTR)max_resolution;
    call.current_resolution = (ULONG_PTR)current_resolution;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryTimerResolution(struct qemu_syscall *call)
{
    struct qemu_NtQueryTimerResolution *c = (struct qemu_NtQueryTimerResolution *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryTimerResolution(QEMU_G2H(c->min_resolution), QEMU_G2H(c->max_resolution), QEMU_G2H(c->current_resolution));
}

#endif

struct qemu_NtSetTimerResolution
{
    struct qemu_syscall super;
    uint64_t resolution;
    uint64_t set_resolution;
    uint64_t current_resolution;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetTimerResolution(IN ULONG resolution, BOOLEAN set_resolution,ULONG* current_resolution)
{
    struct qemu_NtSetTimerResolution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETTIMERRESOLUTION);
    call.resolution = (ULONG_PTR)resolution;
    call.set_resolution = (ULONG_PTR)set_resolution;
    call.current_resolution = (ULONG_PTR)current_resolution;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetTimerResolution(struct qemu_syscall *call)
{
    struct qemu_NtSetTimerResolution *c = (struct qemu_NtSetTimerResolution *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetTimerResolution(c->resolution, c->set_resolution, QEMU_G2H(c->current_resolution));
}

#endif

struct qemu_NtWaitForMultipleObjects
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t handles;
    uint64_t wait_any;
    uint64_t alertable;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtWaitForMultipleObjects(DWORD count, const HANDLE *handles, BOOLEAN wait_any, BOOLEAN alertable, const LARGE_INTEGER *timeout)
{
    struct qemu_NtWaitForMultipleObjects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTWAITFORMULTIPLEOBJECTS);
    call.count = (ULONG_PTR)count;
    call.handles = (ULONG_PTR)handles;
    call.wait_any = (ULONG_PTR)wait_any;
    call.alertable = (ULONG_PTR)alertable;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtWaitForMultipleObjects(struct qemu_syscall *call)
{
    struct qemu_NtWaitForMultipleObjects *c = (struct qemu_NtWaitForMultipleObjects *)call;
    WINE_TRACE("\n");
    c->super.iret = NtWaitForMultipleObjects(c->count, QEMU_G2H(c->handles), c->wait_any, c->alertable, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtWaitForSingleObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t alertable;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtWaitForSingleObject(HANDLE handle, BOOLEAN alertable, LARGE_INTEGER *timeout)
{
    struct qemu_NtWaitForSingleObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTWAITFORSINGLEOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.alertable = (ULONG_PTR)alertable;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtWaitForSingleObject(struct qemu_syscall *call)
{
    struct qemu_NtWaitForSingleObject *c = (struct qemu_NtWaitForSingleObject *)call;
    WINE_TRACE("\n");
    c->super.iret = NtWaitForSingleObject(QEMU_G2H(c->handle), c->alertable, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtSignalAndWaitForSingleObject
{
    struct qemu_syscall super;
    uint64_t hSignalObject;
    uint64_t hWaitObject;
    uint64_t alertable;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSignalAndWaitForSingleObject(HANDLE hSignalObject, HANDLE hWaitObject, BOOLEAN alertable, const LARGE_INTEGER *timeout)
{
    struct qemu_NtSignalAndWaitForSingleObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSIGNALANDWAITFORSINGLEOBJECT);
    call.hSignalObject = (ULONG_PTR)hSignalObject;
    call.hWaitObject = (ULONG_PTR)hWaitObject;
    call.alertable = (ULONG_PTR)alertable;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSignalAndWaitForSingleObject(struct qemu_syscall *call)
{
    struct qemu_NtSignalAndWaitForSingleObject *c = (struct qemu_NtSignalAndWaitForSingleObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSignalAndWaitForSingleObject(QEMU_G2H(c->hSignalObject), QEMU_G2H(c->hWaitObject), c->alertable, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtYieldExecution
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtYieldExecution(void)
{
    struct qemu_NtYieldExecution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTYIELDEXECUTION);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtYieldExecution(struct qemu_syscall *call)
{
    struct qemu_NtYieldExecution *c = (struct qemu_NtYieldExecution *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtYieldExecution();
}

#endif

struct qemu_NtDelayExecution
{
    struct qemu_syscall super;
    uint64_t alertable;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtDelayExecution(BOOLEAN alertable, const LARGE_INTEGER *timeout)
{
    struct qemu_NtDelayExecution call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDELAYEXECUTION);
    call.alertable = (ULONG_PTR)alertable;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtDelayExecution(struct qemu_syscall *call)
{
    struct qemu_NtDelayExecution *c = (struct qemu_NtDelayExecution *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtDelayExecution(c->alertable, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtCreateKeyedEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_NtCreateKeyedEvent(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr, ULONG flags)
{
    struct qemu_NtCreateKeyedEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEKEYEDEVENT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);
    if (handle)
        *handle = (HANDLE)(ULONG_PTR)call.handle;

    return call.super.iret;
}

#else

void qemu_NtCreateKeyedEvent(struct qemu_syscall *call)
{
    struct qemu_NtCreateKeyedEvent *c = (struct qemu_NtCreateKeyedEvent *)call;
    HANDLE event;

    WINE_TRACE("\n");
    c->super.iret = NtCreateKeyedEvent(c->handle ? &event : NULL, c->access, QEMU_G2H(c->attr), c->flags);
    c->handle = QEMU_H2G(event);
}

#endif

struct qemu_NtOpenKeyedEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenKeyedEvent(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenKeyedEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENKEYEDEVENT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenKeyedEvent(struct qemu_syscall *call)
{
    struct qemu_NtOpenKeyedEvent *c = (struct qemu_NtOpenKeyedEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenKeyedEvent(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtWaitForKeyedEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t key;
    uint64_t alertable;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_NtWaitForKeyedEvent(HANDLE handle, const void *key, BOOLEAN alertable, const LARGE_INTEGER *timeout)
{
    struct qemu_NtWaitForKeyedEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTWAITFORKEYEDEVENT);
    call.handle = (ULONG_PTR)handle;
    call.key = (ULONG_PTR)key;
    call.alertable = (ULONG_PTR)alertable;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtWaitForKeyedEvent(struct qemu_syscall *call)
{
    struct qemu_NtWaitForKeyedEvent *c = (struct qemu_NtWaitForKeyedEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtWaitForKeyedEvent(QEMU_G2H(c->handle), QEMU_G2H(c->key), c->alertable, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtReleaseKeyedEvent
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t key;
    uint64_t alertable;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_NtReleaseKeyedEvent(HANDLE handle, const void *key, BOOLEAN alertable, const LARGE_INTEGER *timeout)
{
    struct qemu_NtReleaseKeyedEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRELEASEKEYEDEVENT);
    call.handle = (ULONG_PTR)handle;
    call.key = (ULONG_PTR)key;
    call.alertable = (ULONG_PTR)alertable;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReleaseKeyedEvent(struct qemu_syscall *call)
{
    struct qemu_NtReleaseKeyedEvent *c = (struct qemu_NtReleaseKeyedEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtReleaseKeyedEvent(QEMU_G2H(c->handle), QEMU_G2H(c->key), c->alertable, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtCreateIoCompletion
{
    struct qemu_syscall super;
    uint64_t CompletionPort;
    uint64_t DesiredAccess;
    uint64_t attr;
    uint64_t NumberOfConcurrentThreads;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateIoCompletion(PHANDLE CompletionPort, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES attr, ULONG NumberOfConcurrentThreads)
{
    struct qemu_NtCreateIoCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEIOCOMPLETION);
    call.CompletionPort = (ULONG_PTR)CompletionPort;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.attr = (ULONG_PTR)attr;
    call.NumberOfConcurrentThreads = (ULONG_PTR)NumberOfConcurrentThreads;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateIoCompletion(struct qemu_syscall *call)
{
    struct qemu_NtCreateIoCompletion *c = (struct qemu_NtCreateIoCompletion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateIoCompletion(QEMU_G2H(c->CompletionPort), c->DesiredAccess, QEMU_G2H(c->attr), c->NumberOfConcurrentThreads);
}

#endif

struct qemu_NtSetIoCompletion
{
    struct qemu_syscall super;
    uint64_t CompletionPort;
    uint64_t CompletionKey;
    uint64_t CompletionValue;
    uint64_t Status;
    uint64_t NumberOfBytesTransferred;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetIoCompletion(HANDLE CompletionPort, ULONG_PTR CompletionKey, ULONG_PTR CompletionValue, NTSTATUS Status, SIZE_T NumberOfBytesTransferred)
{
    struct qemu_NtSetIoCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETIOCOMPLETION);
    call.CompletionPort = (ULONG_PTR)CompletionPort;
    call.CompletionKey = (ULONG_PTR)CompletionKey;
    call.CompletionValue = (ULONG_PTR)CompletionValue;
    call.Status = (ULONG_PTR)Status;
    call.NumberOfBytesTransferred = (ULONG_PTR)NumberOfBytesTransferred;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetIoCompletion(struct qemu_syscall *call)
{
    struct qemu_NtSetIoCompletion *c = (struct qemu_NtSetIoCompletion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetIoCompletion(QEMU_G2H(c->CompletionPort), c->CompletionKey, c->CompletionValue, c->Status, c->NumberOfBytesTransferred);
}

#endif

struct qemu_NtRemoveIoCompletion
{
    struct qemu_syscall super;
    uint64_t CompletionPort;
    uint64_t CompletionKey;
    uint64_t CompletionValue;
    uint64_t iosb;
    uint64_t WaitTime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtRemoveIoCompletion(HANDLE CompletionPort, PULONG_PTR CompletionKey, PULONG_PTR CompletionValue, PIO_STATUS_BLOCK iosb, PLARGE_INTEGER WaitTime)
{
    struct qemu_NtRemoveIoCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREMOVEIOCOMPLETION);
    call.CompletionPort = (ULONG_PTR)CompletionPort;
    call.CompletionKey = (ULONG_PTR)CompletionKey;
    call.CompletionValue = (ULONG_PTR)CompletionValue;
    call.iosb = (ULONG_PTR)iosb;
    call.WaitTime = (ULONG_PTR)WaitTime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtRemoveIoCompletion(struct qemu_syscall *call)
{
    struct qemu_NtRemoveIoCompletion *c = (struct qemu_NtRemoveIoCompletion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtRemoveIoCompletion(QEMU_G2H(c->CompletionPort), QEMU_G2H(c->CompletionKey), QEMU_G2H(c->CompletionValue), QEMU_G2H(c->iosb), QEMU_G2H(c->WaitTime));
}

#endif

struct qemu_NtOpenIoCompletion
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenIoCompletion(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenIoCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENIOCOMPLETION);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenIoCompletion(struct qemu_syscall *call)
{
    struct qemu_NtOpenIoCompletion *c = (struct qemu_NtOpenIoCompletion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenIoCompletion(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtQueryIoCompletion
{
    struct qemu_syscall super;
    uint64_t CompletionPort;
    uint64_t InformationClass;
    uint64_t CompletionInformation;
    uint64_t BufferLength;
    uint64_t RequiredLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryIoCompletion(HANDLE CompletionPort, IO_COMPLETION_INFORMATION_CLASS InformationClass, PVOID CompletionInformation, ULONG BufferLength, PULONG RequiredLength)
{
    struct qemu_NtQueryIoCompletion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYIOCOMPLETION);
    call.CompletionPort = (ULONG_PTR)CompletionPort;
    call.InformationClass = (ULONG_PTR)InformationClass;
    call.CompletionInformation = (ULONG_PTR)CompletionInformation;
    call.BufferLength = (ULONG_PTR)BufferLength;
    call.RequiredLength = (ULONG_PTR)RequiredLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryIoCompletion(struct qemu_syscall *call)
{
    struct qemu_NtQueryIoCompletion *c = (struct qemu_NtQueryIoCompletion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryIoCompletion(QEMU_G2H(c->CompletionPort), c->InformationClass, QEMU_G2H(c->CompletionInformation), c->BufferLength, QEMU_G2H(c->RequiredLength));
}

#endif

struct qemu_RtlRunOnceInitialize
{
    struct qemu_syscall super;
    uint64_t once;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlRunOnceInitialize(RTL_RUN_ONCE *once)
{
    struct qemu_RtlRunOnceInitialize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRUNONCEINITIALIZE);
    call.once = (ULONG_PTR)once;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlRunOnceInitialize(struct qemu_syscall *call)
{
    struct qemu_RtlRunOnceInitialize *c = (struct qemu_RtlRunOnceInitialize *)call;
    WINE_TRACE("\n");
    RtlRunOnceInitialize(QEMU_G2H(c->once));
}

#endif

struct qemu_RtlRunOnceBeginInitialize
{
    struct qemu_syscall super;
    uint64_t once;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

static inline void *interlocked_cmpxchg_ptr( void **dest, void *xchg, void *compare )
{
    void *ret;
#ifdef __x86_64__
    __asm__ __volatile__( "lock; cmpxchgq %2,(%1)"
                          : "=a" (ret) : "r" (dest), "r" (xchg), "0" (compare) : "memory" );
#else
    __asm__ __volatile__( "lock; cmpxchgl %2,(%1)"
                          : "=a" (ret) : "r" (dest), "r" (xchg), "0" (compare) : "memory" );
#endif
    return ret;
}

HANDLE keyed_event = NULL;

DWORD WINAPI ntdll_RtlRunOnceBeginInitialize(RTL_RUN_ONCE *once, ULONG flags, void **context)
{
    if (flags & RTL_RUN_ONCE_CHECK_ONLY)
    {
        ULONG_PTR val = (ULONG_PTR)once->Ptr;

        if (flags & RTL_RUN_ONCE_ASYNC) return STATUS_INVALID_PARAMETER;
        if ((val & 3) != 2) return STATUS_UNSUCCESSFUL;
        if (context) *context = (void *)(val & ~3);
        return STATUS_SUCCESS;
    }

    for (;;)
    {
        ULONG_PTR next, val = (ULONG_PTR)once->Ptr;

        switch (val & 3)
        {
        case 0:  /* first time */
            if (!interlocked_cmpxchg_ptr( &once->Ptr,
                                          (flags & RTL_RUN_ONCE_ASYNC) ? (void *)3 : (void *)1, 0 ))
                return STATUS_PENDING;
            break;

        case 1:  /* in progress, wait */
            if (flags & RTL_RUN_ONCE_ASYNC) return STATUS_INVALID_PARAMETER;
            next = val & ~3;
            if (interlocked_cmpxchg_ptr( &once->Ptr, (void *)((ULONG_PTR)&next | 1),
                                         (void *)val ) == (void *)val)
                ntdll_NtWaitForKeyedEvent( keyed_event, &next, FALSE, NULL );
            break;

        case 2:  /* done */
            if (context) *context = (void *)(val & ~3);
            return STATUS_SUCCESS;

        case 3:  /* in progress, async */
            if (!(flags & RTL_RUN_ONCE_ASYNC)) return STATUS_INVALID_PARAMETER;
            return STATUS_PENDING;
        }
    }
}

#else

void qemu_RtlRunOnceBeginInitialize(struct qemu_syscall *call)
{
    struct qemu_RtlRunOnceBeginInitialize *c = (struct qemu_RtlRunOnceBeginInitialize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlRunOnceBeginInitialize(QEMU_G2H(c->once), c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_RtlRunOnceComplete
{
    struct qemu_syscall super;
    uint64_t once;
    uint64_t flags;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

DWORD WINAPI ntdll_RtlRunOnceComplete(RTL_RUN_ONCE *once, ULONG flags, void *context)
{
    if ((ULONG_PTR)context & 3) return STATUS_INVALID_PARAMETER;

    if (flags & RTL_RUN_ONCE_INIT_FAILED)
    {
        if (context) return STATUS_INVALID_PARAMETER;
        if (flags & RTL_RUN_ONCE_ASYNC) return STATUS_INVALID_PARAMETER;
    }
    else context = (void *)((ULONG_PTR)context | 2);

    for (;;)
    {
        ULONG_PTR val = (ULONG_PTR)once->Ptr;

        switch (val & 3)
        {
        case 1:  /* in progress */
            if (interlocked_cmpxchg_ptr( &once->Ptr, context, (void *)val ) != (void *)val) break;
            val &= ~3;
            while (val)
            {
                ULONG_PTR next = *(ULONG_PTR *)val;
                ntdll_NtReleaseKeyedEvent( keyed_event, (void *)val, FALSE, NULL );
                val = next;
            }
            return STATUS_SUCCESS;

        case 3:  /* in progress, async */
            if (!(flags & RTL_RUN_ONCE_ASYNC)) return STATUS_INVALID_PARAMETER;
            if (interlocked_cmpxchg_ptr( &once->Ptr, context, (void *)val ) != (void *)val) break;
            return STATUS_SUCCESS;

        default:
            return STATUS_UNSUCCESSFUL;
        }
    }
}

#else

void qemu_RtlRunOnceComplete(struct qemu_syscall *call)
{
    struct qemu_RtlRunOnceComplete *c = (struct qemu_RtlRunOnceComplete *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlRunOnceComplete(QEMU_G2H(c->once), c->flags, QEMU_G2H(c->context));
}

#endif

struct qemu_RtlRunOnceExecuteOnce
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlRunOnceExecuteOnce(RTL_RUN_ONCE *once, PRTL_RUN_ONCE_INIT_FN func, void *param, void **context)
{
    struct qemu_RtlRunOnceExecuteOnce call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRUNONCEEXECUTEONCE);

    /* For logging */
    qemu_syscall(&call.super);

    {
        DWORD ret = ntdll_RtlRunOnceBeginInitialize( once, 0, context );

        if (ret != STATUS_PENDING) return ret;

        if (!func( once, param, context ))
        {
            ntdll_RtlRunOnceComplete( once, RTL_RUN_ONCE_INIT_FAILED, NULL );
            return STATUS_UNSUCCESSFUL;
        }

        return ntdll_RtlRunOnceComplete( once, 0, context ? *context : NULL );
    }
}

#else

void qemu_RtlRunOnceExecuteOnce(struct qemu_syscall *call)
{
    struct qemu_RtlRunOnceExecuteOnce *c = (struct qemu_RtlRunOnceExecuteOnce *)call;
    WINE_TRACE("\n");
}

#endif

struct qemu_RtlInitializeSRWLock
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitializeSRWLock(RTL_SRWLOCK *lock)
{
    struct qemu_RtlInitializeSRWLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZESRWLOCK);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitializeSRWLock(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeSRWLock *c = (struct qemu_RtlInitializeSRWLock *)call;
    WINE_TRACE("\n");
    RtlInitializeSRWLock(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlAcquireSRWLockExclusive
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlAcquireSRWLockExclusive(RTL_SRWLOCK *lock)
{
    struct qemu_RtlAcquireSRWLockExclusive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLACQUIRESRWLOCKEXCLUSIVE);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlAcquireSRWLockExclusive(struct qemu_syscall *call)
{
    struct qemu_RtlAcquireSRWLockExclusive *c = (struct qemu_RtlAcquireSRWLockExclusive *)call;
    WINE_TRACE("\n");
    RtlAcquireSRWLockExclusive(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlAcquireSRWLockShared
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlAcquireSRWLockShared(RTL_SRWLOCK *lock)
{
    struct qemu_RtlAcquireSRWLockShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLACQUIRESRWLOCKSHARED);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlAcquireSRWLockShared(struct qemu_syscall *call)
{
    struct qemu_RtlAcquireSRWLockShared *c = (struct qemu_RtlAcquireSRWLockShared *)call;
    WINE_TRACE("\n");
    RtlAcquireSRWLockShared(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlReleaseSRWLockExclusive
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlReleaseSRWLockExclusive(RTL_SRWLOCK *lock)
{
    struct qemu_RtlReleaseSRWLockExclusive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRELEASESRWLOCKEXCLUSIVE);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlReleaseSRWLockExclusive(struct qemu_syscall *call)
{
    struct qemu_RtlReleaseSRWLockExclusive *c = (struct qemu_RtlReleaseSRWLockExclusive *)call;
    WINE_TRACE("\n");
    RtlReleaseSRWLockExclusive(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlReleaseSRWLockShared
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlReleaseSRWLockShared(RTL_SRWLOCK *lock)
{
    struct qemu_RtlReleaseSRWLockShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRELEASESRWLOCKSHARED);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlReleaseSRWLockShared(struct qemu_syscall *call)
{
    struct qemu_RtlReleaseSRWLockShared *c = (struct qemu_RtlReleaseSRWLockShared *)call;
    WINE_TRACE("\n");
    RtlReleaseSRWLockShared(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlTryAcquireSRWLockExclusive
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlTryAcquireSRWLockExclusive(RTL_SRWLOCK *lock)
{
    struct qemu_RtlTryAcquireSRWLockExclusive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTRYACQUIRESRWLOCKEXCLUSIVE);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlTryAcquireSRWLockExclusive(struct qemu_syscall *call)
{
    struct qemu_RtlTryAcquireSRWLockExclusive *c = (struct qemu_RtlTryAcquireSRWLockExclusive *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlTryAcquireSRWLockExclusive(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlTryAcquireSRWLockShared
{
    struct qemu_syscall super;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlTryAcquireSRWLockShared(RTL_SRWLOCK *lock)
{
    struct qemu_RtlTryAcquireSRWLockShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLTRYACQUIRESRWLOCKSHARED);
    call.lock = (ULONG_PTR)lock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlTryAcquireSRWLockShared(struct qemu_syscall *call)
{
    struct qemu_RtlTryAcquireSRWLockShared *c = (struct qemu_RtlTryAcquireSRWLockShared *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlTryAcquireSRWLockShared(QEMU_G2H(c->lock));
}

#endif

struct qemu_RtlInitializeConditionVariable
{
    struct qemu_syscall super;
    uint64_t variable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitializeConditionVariable(RTL_CONDITION_VARIABLE *variable)
{
    struct qemu_RtlInitializeConditionVariable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZECONDITIONVARIABLE);
    call.variable = (ULONG_PTR)variable;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitializeConditionVariable(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeConditionVariable *c = (struct qemu_RtlInitializeConditionVariable *)call;
    WINE_TRACE("\n");
    RtlInitializeConditionVariable(QEMU_G2H(c->variable));
}

#endif

struct qemu_RtlWakeConditionVariable
{
    struct qemu_syscall super;
    uint64_t variable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlWakeConditionVariable(RTL_CONDITION_VARIABLE *variable)
{
    struct qemu_RtlWakeConditionVariable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWAKECONDITIONVARIABLE);
    call.variable = (ULONG_PTR)variable;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlWakeConditionVariable(struct qemu_syscall *call)
{
    struct qemu_RtlWakeConditionVariable *c = (struct qemu_RtlWakeConditionVariable *)call;
    WINE_TRACE("\n");
    RtlWakeConditionVariable(QEMU_G2H(c->variable));
}

#endif

struct qemu_RtlWakeAllConditionVariable
{
    struct qemu_syscall super;
    uint64_t variable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlWakeAllConditionVariable(RTL_CONDITION_VARIABLE *variable)
{
    struct qemu_RtlWakeAllConditionVariable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWAKEALLCONDITIONVARIABLE);
    call.variable = (ULONG_PTR)variable;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlWakeAllConditionVariable(struct qemu_syscall *call)
{
    struct qemu_RtlWakeAllConditionVariable *c = (struct qemu_RtlWakeAllConditionVariable *)call;
    WINE_TRACE("\n");
    RtlWakeAllConditionVariable(QEMU_G2H(c->variable));
}

#endif

struct qemu_RtlSleepConditionVariableSRW
{
    struct qemu_syscall super;
    uint64_t variable;
    uint64_t lock;
    uint64_t timeout;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSleepConditionVariableSRW(RTL_CONDITION_VARIABLE *variable, RTL_SRWLOCK *lock, const LARGE_INTEGER *timeout, ULONG flags)
{
    struct qemu_RtlSleepConditionVariableSRW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSLEEPCONDITIONVARIABLESRW);
    call.variable = (ULONG_PTR)variable;
    call.lock = (ULONG_PTR)lock;
    call.timeout = (ULONG_PTR)timeout;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSleepConditionVariableSRW(struct qemu_syscall *call)
{
    struct qemu_RtlSleepConditionVariableSRW *c = (struct qemu_RtlSleepConditionVariableSRW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSleepConditionVariableSRW(QEMU_G2H(c->variable), QEMU_G2H(c->lock), QEMU_G2H(c->timeout), c->flags);
}

#endif

struct qemu_RtlWaitOnAddress
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t cmp;
    uint64_t size;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlWaitOnAddress(const void *addr, const void *cmp, SIZE_T size, const LARGE_INTEGER *timeout)
{
    struct qemu_RtlWaitOnAddress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWAITONADDRESS);
    call.addr = (ULONG_PTR)addr;
    call.cmp = (ULONG_PTR)cmp;
    call.size = size;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlWaitOnAddress(struct qemu_syscall *call)
{
    struct qemu_RtlWaitOnAddress *c = (struct qemu_RtlWaitOnAddress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlWaitOnAddress(QEMU_G2H(c->addr), QEMU_G2H(c->cmp), c->size, QEMU_G2H(c->timeout));
}

#endif

struct qemu_RtlWakeAddressAll
{
    struct qemu_syscall super;
    uint64_t addr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlWakeAddressAll(const void *addr)
{
    struct qemu_RtlWakeAddressAll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWAKEADDRESSALL);
    call.addr = (ULONG_PTR)addr;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlWakeAddressAll(struct qemu_syscall *call)
{
    struct qemu_RtlWakeAddressAll *c = (struct qemu_RtlWakeAddressAll *)call;
    WINE_FIXME("Unverified!\n");
    RtlWakeAddressAll(QEMU_G2H(c->addr));
}

#endif

struct qemu_RtlWakeAddressSingle
{
    struct qemu_syscall super;
    uint64_t addr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlWakeAddressSingle(const void *addr)
{
    struct qemu_RtlWakeAddressSingle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWAKEADDRESSSINGLE);
    call.addr = (ULONG_PTR)addr;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlWakeAddressSingle(struct qemu_syscall *call)
{
    struct qemu_RtlWakeAddressSingle *c = (struct qemu_RtlWakeAddressSingle *)call;
    WINE_FIXME("Unverified!\n");
    RtlWakeAddressSingle(QEMU_G2H(c->addr));
}

#endif

struct qemu_NtRemoveIoCompletionEx
{
    struct qemu_syscall super;
    uint64_t port;
    uint64_t info;
    uint64_t count;
    uint64_t written;
    uint64_t timeout;
    uint64_t alertable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtRemoveIoCompletionEx(HANDLE port, FILE_IO_COMPLETION_INFORMATION *info, ULONG count, ULONG *written, LARGE_INTEGER *timeout, BOOLEAN alertable)
{
    struct qemu_NtRemoveIoCompletionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREMOVEIOCOMPLETIONEX);
    call.port = (ULONG_PTR)port;
    call.info = (ULONG_PTR)info;
    call.count = count;
    call.written = (ULONG_PTR)written;
    call.timeout = (ULONG_PTR)timeout;
    call.alertable = alertable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtRemoveIoCompletionEx(struct qemu_syscall *call)
{
    struct qemu_NtRemoveIoCompletionEx *c = (struct qemu_NtRemoveIoCompletionEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtRemoveIoCompletionEx(QEMU_G2H(c->port), QEMU_G2H(c->info), c->count, QEMU_G2H(c->written), QEMU_G2H(c->timeout), c->alertable);
}

#endif
