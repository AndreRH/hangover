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

/* I can't make mingw's ddk headers work :-( . */
typedef void *PRTL_THREAD_START_ROUTINE, *PNTAPCFUNC;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlCreateUserThread
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t descr;
    uint64_t suspended;
    uint64_t stack_addr;
    uint64_t stack_reserve;
    uint64_t stack_commit;
    uint64_t start;
    uint64_t param;
    uint64_t handle_ptr;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateUserThread(HANDLE process, const SECURITY_DESCRIPTOR *descr, BOOLEAN suspended, PVOID stack_addr, SIZE_T stack_reserve, SIZE_T stack_commit, PRTL_THREAD_START_ROUTINE start, void *param, HANDLE *handle_ptr, CLIENT_ID *id)
{
    struct qemu_RtlCreateUserThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEUSERTHREAD);
    call.process = (ULONG_PTR)process;
    call.descr = (ULONG_PTR)descr;
    call.suspended = (ULONG_PTR)suspended;
    call.stack_addr = (ULONG_PTR)stack_addr;
    call.stack_reserve = (ULONG_PTR)stack_reserve;
    call.stack_commit = (ULONG_PTR)stack_commit;
    call.start = (ULONG_PTR)start;
    call.param = (ULONG_PTR)param;
    call.handle_ptr = (ULONG_PTR)handle_ptr;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateUserThread(struct qemu_syscall *call)
{
    struct qemu_RtlCreateUserThread *c = (struct qemu_RtlCreateUserThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateUserThread(QEMU_G2H(c->process), QEMU_G2H(c->descr), c->suspended, QEMU_G2H(c->stack_addr), c->stack_reserve, c->stack_commit, QEMU_G2H(c->start), QEMU_G2H(c->param), QEMU_G2H(c->handle_ptr), QEMU_G2H(c->id));
}

#endif

struct qemu_RtlGetNtGlobalFlags
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlGetNtGlobalFlags(void)
{
    struct qemu_RtlGetNtGlobalFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETNTGLOBALFLAGS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetNtGlobalFlags(struct qemu_syscall *call)
{
    struct qemu_RtlGetNtGlobalFlags *c = (struct qemu_RtlGetNtGlobalFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetNtGlobalFlags();
}

#endif

struct qemu_NtOpenThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenThread(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr, const CLIENT_ID *id)
{
    struct qemu_NtOpenThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENTHREAD);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenThread(struct qemu_syscall *call)
{
    struct qemu_NtOpenThread *c = (struct qemu_NtOpenThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenThread(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr), QEMU_G2H(c->id));
}

#endif

struct qemu_NtSuspendThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSuspendThread(HANDLE handle, PULONG count)
{
    struct qemu_NtSuspendThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSUSPENDTHREAD);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSuspendThread(struct qemu_syscall *call)
{
    struct qemu_NtSuspendThread *c = (struct qemu_NtSuspendThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSuspendThread(QEMU_G2H(c->handle), QEMU_G2H(c->count));
}

#endif

struct qemu_NtResumeThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtResumeThread(HANDLE handle, PULONG count)
{
    struct qemu_NtResumeThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRESUMETHREAD);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtResumeThread(struct qemu_syscall *call)
{
    struct qemu_NtResumeThread *c = (struct qemu_NtResumeThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtResumeThread(QEMU_G2H(c->handle), QEMU_G2H(c->count));
}

#endif

struct qemu_NtAlertResumeThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAlertResumeThread(HANDLE handle, PULONG count)
{
    struct qemu_NtAlertResumeThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTALERTRESUMETHREAD);
    call.handle = (ULONG_PTR)handle;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAlertResumeThread(struct qemu_syscall *call)
{
    struct qemu_NtAlertResumeThread *c = (struct qemu_NtAlertResumeThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAlertResumeThread(QEMU_G2H(c->handle), QEMU_G2H(c->count));
}

#endif

struct qemu_NtAlertThread
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAlertThread(HANDLE handle)
{
    struct qemu_NtAlertThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTALERTTHREAD);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAlertThread(struct qemu_syscall *call)
{
    struct qemu_NtAlertThread *c = (struct qemu_NtAlertThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAlertThread(QEMU_G2H(c->handle));
}

#endif

struct qemu_NtTerminateThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtTerminateThread(HANDLE handle, LONG exit_code)
{
    struct qemu_NtTerminateThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTTERMINATETHREAD);
    call.handle = (ULONG_PTR)handle;
    call.exit_code = (ULONG_PTR)exit_code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtTerminateThread(struct qemu_syscall *call)
{
    struct qemu_NtTerminateThread *c = (struct qemu_NtTerminateThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtTerminateThread(QEMU_G2H(c->handle), c->exit_code);
}

#endif

struct qemu_NtQueueApcThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t func;
    uint64_t arg1;
    uint64_t arg2;
    uint64_t arg3;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueueApcThread(HANDLE handle, PNTAPCFUNC func, ULONG_PTR arg1, ULONG_PTR arg2, ULONG_PTR arg3)
{
    struct qemu_NtQueueApcThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUEUEAPCTHREAD);
    call.handle = (ULONG_PTR)handle;
    call.func = (ULONG_PTR)func;
    call.arg1 = (ULONG_PTR)arg1;
    call.arg2 = (ULONG_PTR)arg2;
    call.arg3 = (ULONG_PTR)arg3;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueueApcThread(struct qemu_syscall *call)
{
    struct qemu_NtQueueApcThread *c = (struct qemu_NtQueueApcThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueueApcThread(QEMU_G2H(c->handle), QEMU_G2H(c->func), c->arg1, c->arg2, c->arg3);
}

#endif

struct qemu_NtQueryInformationThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t data;
    uint64_t length;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryInformationThread(HANDLE handle, THREADINFOCLASS class, void *data, ULONG length, ULONG *ret_len)
{
    struct qemu_NtQueryInformationThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYINFORMATIONTHREAD);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.data = (ULONG_PTR)data;
    call.length = (ULONG_PTR)length;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryInformationThread(struct qemu_syscall *call)
{
    struct qemu_NtQueryInformationThread *c = (struct qemu_NtQueryInformationThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryInformationThread(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->data), c->length, QEMU_G2H(c->ret_len));
}

#endif

struct qemu_NtSetInformationThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t data;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetInformationThread(HANDLE handle, THREADINFOCLASS class, LPCVOID data, ULONG length)
{
    struct qemu_NtSetInformationThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINFORMATIONTHREAD);
    call.handle = (ULONG_PTR)handle;
    call.class = (ULONG_PTR)class;
    call.data = (ULONG_PTR)data;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetInformationThread(struct qemu_syscall *call)
{
    struct qemu_NtSetInformationThread *c = (struct qemu_NtSetInformationThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetInformationThread(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->data), c->length);
}

#endif

struct qemu_NtGetCurrentProcessorNumber
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI NtGetCurrentProcessorNumber(void)
{
    struct qemu_NtGetCurrentProcessorNumber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTGETCURRENTPROCESSORNUMBER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtGetCurrentProcessorNumber(struct qemu_syscall *call)
{
    struct qemu_NtGetCurrentProcessorNumber *c = (struct qemu_NtGetCurrentProcessorNumber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtGetCurrentProcessorNumber();
}

#endif

