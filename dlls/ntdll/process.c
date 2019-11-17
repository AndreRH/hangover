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
typedef void RTL_USER_PROCESS_INFORMATION;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_NtTerminateProcess
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

NTSTATUS WINAPI ntdll_NtTerminateProcess(HANDLE handle, LONG exit_code)
{
    struct qemu_NtTerminateProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTTERMINATEPROCESS);
    call.handle = guest_HANDLE_g2h(handle);
    call.exit_code = (ULONG_PTR)exit_code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtTerminateProcess(struct qemu_syscall *call)
{
    struct qemu_NtTerminateProcess *c = (struct qemu_NtTerminateProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtTerminateProcess(QEMU_G2H(c->handle), c->exit_code);
}

#endif

struct qemu_RtlGetCurrentPeb
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PEB * WINAPI RtlGetCurrentPeb(void)
{
    struct qemu_RtlGetCurrentPeb call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETCURRENTPEB);

    qemu_syscall(&call.super);

    return (PEB *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlGetCurrentPeb(struct qemu_syscall *call)
{
    struct qemu_RtlGetCurrentPeb *c = (struct qemu_RtlGetCurrentPeb *)call;
    WINE_FIXME("Probably not going to work!\n");
    c->super.iret = QEMU_H2G(RtlGetCurrentPeb());
}

#endif

struct qemu_NtQueryInformationProcess
{
    struct qemu_syscall super;
    uint64_t ProcessHandle;
    uint64_t ProcessInformationClass;
    uint64_t ProcessInformation;
    uint64_t ProcessInformationLength;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryInformationProcess(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength)
{
    struct qemu_NtQueryInformationProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYINFORMATIONPROCESS);
    call.ProcessHandle = guest_HANDLE_g2h(ProcessHandle);
    call.ProcessInformationClass = (ULONG_PTR)ProcessInformationClass;
    call.ProcessInformation = (ULONG_PTR)ProcessInformation;
    call.ProcessInformationLength = (ULONG_PTR)ProcessInformationLength;
    call.ReturnLength = (ULONG_PTR)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryInformationProcess(struct qemu_syscall *call)
{
    struct qemu_NtQueryInformationProcess *c = (struct qemu_NtQueryInformationProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryInformationProcess((HANDLE)c->ProcessHandle, c->ProcessInformationClass, QEMU_G2H(c->ProcessInformation), c->ProcessInformationLength, QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_NtSetInformationProcess
{
    struct qemu_syscall super;
    uint64_t ProcessHandle;
    uint64_t ProcessInformationClass;
    uint64_t ProcessInformation;
    uint64_t ProcessInformationLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetInformationProcess(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, IN PVOID ProcessInformation, IN ULONG ProcessInformationLength)
{
    struct qemu_NtSetInformationProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINFORMATIONPROCESS);
    call.ProcessHandle = guest_HANDLE_g2h(ProcessHandle);
    call.ProcessInformationClass = (ULONG_PTR)ProcessInformationClass;
    call.ProcessInformation = (ULONG_PTR)ProcessInformation;
    call.ProcessInformationLength = (ULONG_PTR)ProcessInformationLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetInformationProcess(struct qemu_syscall *call)
{
    struct qemu_NtSetInformationProcess *c = (struct qemu_NtSetInformationProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetInformationProcess((HANDLE)c->ProcessHandle, c->ProcessInformationClass, QEMU_G2H(c->ProcessInformation), c->ProcessInformationLength);
}

#endif

struct qemu_NtFlushInstructionCache
{
    struct qemu_syscall super;
    uint64_t ProcessHandle;
    uint64_t BaseAddress;
    uint64_t Size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtFlushInstructionCache(IN HANDLE ProcessHandle, IN LPCVOID BaseAddress, IN SIZE_T Size)
{
    struct qemu_NtFlushInstructionCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTFLUSHINSTRUCTIONCACHE);
    call.ProcessHandle = guest_HANDLE_g2h(ProcessHandle);
    call.BaseAddress = (ULONG_PTR)BaseAddress;
    call.Size = (ULONG_PTR)Size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtFlushInstructionCache(struct qemu_syscall *call)
{
    struct qemu_NtFlushInstructionCache *c = (struct qemu_NtFlushInstructionCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtFlushInstructionCache((HANDLE)c->ProcessHandle, QEMU_G2H(c->BaseAddress), c->Size);
}

#endif

struct qemu_NtOpenProcess
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t cid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenProcess(PHANDLE handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES* attr, const CLIENT_ID* cid)
{
    struct qemu_NtOpenProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENPROCESS);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;
    call.cid = (ULONG_PTR)cid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenProcess(struct qemu_syscall *call)
{
    struct qemu_NtOpenProcess *c = (struct qemu_NtOpenProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenProcess(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr), QEMU_G2H(c->cid));
}

#endif

struct qemu_NtResumeProcess
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtResumeProcess(HANDLE handle)
{
    struct qemu_NtResumeProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRESUMEPROCESS);
    call.handle = guest_HANDLE_g2h(handle);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NtResumeProcess to Wine headers? */
extern NTSTATUS WINAPI NtResumeProcess(HANDLE handle);
void qemu_NtResumeProcess(struct qemu_syscall *call)
{
    struct qemu_NtResumeProcess *c = (struct qemu_NtResumeProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtResumeProcess(QEMU_G2H(c->handle));
}

#endif

struct qemu_NtSuspendProcess
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSuspendProcess(HANDLE handle)
{
    struct qemu_NtSuspendProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSUSPENDPROCESS);
    call.handle = guest_HANDLE_g2h(handle);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NtSuspendProcess to Wine headers? */
extern NTSTATUS WINAPI NtSuspendProcess(HANDLE handle);
void qemu_NtSuspendProcess(struct qemu_syscall *call)
{
    struct qemu_NtSuspendProcess *c = (struct qemu_NtSuspendProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSuspendProcess(QEMU_G2H(c->handle));
}

#endif

struct qemu_DbgUiIssueRemoteBreakin
{
    struct qemu_syscall super;
    uint64_t process;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI DbgUiIssueRemoteBreakin(HANDLE process)
{
    struct qemu_DbgUiIssueRemoteBreakin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DBGUIISSUEREMOTEBREAKIN);
    call.process = (ULONG_PTR)process;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DbgUiIssueRemoteBreakin(struct qemu_syscall *call)
{
    struct qemu_DbgUiIssueRemoteBreakin *c = (struct qemu_DbgUiIssueRemoteBreakin *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DbgUiIssueRemoteBreakin(QEMU_G2H(c->process));
}

#endif

struct qemu_DbgUiRemoteBreakin
{
    struct qemu_syscall super;
    uint64_t arg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DbgUiRemoteBreakin(void *arg)
{
    struct qemu_DbgUiRemoteBreakin call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DBGUIREMOTEBREAKIN);
    call.arg = (ULONG_PTR)arg;

    qemu_syscall(&call.super);
}

#else

void qemu_DbgUiRemoteBreakin(struct qemu_syscall *call)
{
    struct qemu_DbgUiRemoteBreakin *c = (struct qemu_DbgUiRemoteBreakin *)call;
    WINE_FIXME("Unverified!\n");
    DbgUiRemoteBreakin(QEMU_G2H(c->arg));
}

#endif

struct qemu_RtlCreateUserProcess
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t attributes;
    uint64_t params;
    uint64_t process_descr;
    uint64_t thread_descr;
    uint64_t parent;
    uint64_t inherit;
    uint64_t debug;
    uint64_t exception;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateUserProcess(UNICODE_STRING *path, ULONG attributes, RTL_USER_PROCESS_PARAMETERS *params, SECURITY_DESCRIPTOR *process_descr, SECURITY_DESCRIPTOR *thread_descr, HANDLE parent, BOOLEAN inherit, HANDLE debug, HANDLE exception, RTL_USER_PROCESS_INFORMATION *info)
{
    struct qemu_RtlCreateUserProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEUSERPROCESS);
    call.path = (ULONG_PTR)path;
    call.attributes = attributes;
    call.params = (ULONG_PTR)params;
    call.process_descr = (ULONG_PTR)process_descr;
    call.thread_descr = (ULONG_PTR)thread_descr;
    call.parent = (ULONG_PTR)parent;
    call.inherit = inherit;
    call.debug = (ULONG_PTR)debug;
    call.exception = (ULONG_PTR)exception;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateUserProcess(struct qemu_syscall *call)
{
    struct qemu_RtlCreateUserProcess *c = (struct qemu_RtlCreateUserProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateUserProcess(QEMU_G2H(c->path), c->attributes, QEMU_G2H(c->params), QEMU_G2H(c->process_descr), QEMU_G2H(c->thread_descr), QEMU_G2H(c->parent), c->inherit, QEMU_G2H(c->debug), QEMU_G2H(c->exception), QEMU_G2H(c->info));
}

#endif
