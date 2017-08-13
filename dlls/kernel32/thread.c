/*
 * Copyright 2017 André Hentschel
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_CreateThread
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t stack;
    uint64_t start;
    uint64_t param;
    uint64_t flags;
    uint64_t id;
    uint64_t wrapper;
};

struct qemu_CreateThread_cb
{
    uint64_t context;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

/* Not strictly necessary, but seems like a good idea for future extensions. */
static DWORD WINAPI qemu_CreateThread_guest_wrapper(void *ctx)
{
    struct qemu_CreateThread_cb *cb = ctx;
    LPTHREAD_START_ROUTINE proc = (LPTHREAD_START_ROUTINE)cb->proc;
    return proc((void *)cb->context);
}

WINBASEAPI HANDLE WINAPI CreateThread(SECURITY_ATTRIBUTES *sa, SIZE_T stack, LPTHREAD_START_ROUTINE start, LPVOID param, DWORD flags, LPDWORD id)
{
    struct qemu_CreateThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETHREAD);
    call.sa = (uint64_t)sa;
    call.stack = (uint64_t)stack;
    call.start = (uint64_t)start;
    call.param = (uint64_t)param;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;
    call.wrapper = (uint64_t)qemu_CreateThread_guest_wrapper;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

struct qemu_CreateThread_context
{
    uint64_t app_param;
    uint64_t app_func;
    uint64_t guest_wrapper;
};

static DWORD WINAPI qemu_CreateThread_wrapper(void *context)
{
    struct qemu_CreateThread_context *ctx = context;
    struct qemu_CreateThread_cb cb;
    uint64_t wrapper;
    DWORD ret;

    cb.proc = ctx->app_func;
    cb.context = ctx->app_param;
    wrapper = ctx->guest_wrapper;
    HeapFree(GetProcessHeap(), 0, ctx);

    WINE_TRACE("Calling thread function 0x%lx(0x%lx).\n", cb.proc, cb.context);
    ret = qemu_ops->qemu_execute(QEMU_G2H(wrapper), QEMU_H2G(&cb));
    WINE_TRACE("Thread function 0x%lx returned %x.\n", cb.proc, ret);
    return ret;
}

void qemu_CreateThread(struct qemu_syscall *call)
{
    struct qemu_CreateThread *c = (struct qemu_CreateThread *)call;
    struct qemu_CreateThread_context *context;

    WINE_TRACE("func %lx, ctx %lx\n", c->start, c->param);

    context = HeapAlloc(GetProcessHeap(), 0, sizeof(*context));
    if (!context)
    {
        c->super.iret = 0;
        return;
    }

    context->app_param = c->param;
    context->app_func = c->start;
    context->guest_wrapper = c->wrapper;

    c->super.iret = (uint64_t)CreateThread(QEMU_G2H(c->sa), c->stack, qemu_CreateThread_wrapper,
            context, c->flags, QEMU_G2H(c->id));
}

#endif

struct qemu_CreateRemoteThread
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t sa;
    uint64_t stack;
    uint64_t start;
    uint64_t param;
    uint64_t flags;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateRemoteThread(HANDLE hProcess, SECURITY_ATTRIBUTES *sa, SIZE_T stack, LPTHREAD_START_ROUTINE start, LPVOID param, DWORD flags, LPDWORD id)
{
    struct qemu_CreateRemoteThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEREMOTETHREAD);
    call.hProcess = (uint64_t)hProcess;
    call.sa = (uint64_t)sa;
    call.stack = (uint64_t)stack;
    call.start = (uint64_t)start;
    call.param = (uint64_t)param;
    call.flags = (uint64_t)flags;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateRemoteThread(struct qemu_syscall *call)
{
    struct qemu_CreateRemoteThread *c = (struct qemu_CreateRemoteThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateRemoteThread(QEMU_G2H(c->hProcess), QEMU_G2H(c->sa), c->stack, QEMU_G2H(c->start), QEMU_G2H(c->param), c->flags, QEMU_G2H(c->id));
}

#endif

struct qemu_OpenThread
{
    struct qemu_syscall super;
    uint64_t dwDesiredAccess;
    uint64_t bInheritHandle;
    uint64_t dwThreadId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId)
{
    struct qemu_OpenThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENTHREAD);
    call.dwDesiredAccess = (uint64_t)dwDesiredAccess;
    call.bInheritHandle = (uint64_t)bInheritHandle;
    call.dwThreadId = (uint64_t)dwThreadId;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenThread(struct qemu_syscall *call)
{
    struct qemu_OpenThread *c = (struct qemu_OpenThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenThread(c->dwDesiredAccess, c->bInheritHandle, c->dwThreadId);
}

#endif

struct qemu_ExitThread
{
    struct qemu_syscall super;
    uint64_t code;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ExitThread(DWORD code)
{
    struct qemu_ExitThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXITTHREAD);
    call.code = code;

    qemu_syscall(&call.super);

    __builtin_unreachable();
}

#else

void qemu_ExitThread(struct qemu_syscall *call)
{
    struct qemu_ExitThread *c = (struct qemu_ExitThread *)call;
    WINE_TRACE("\n");
    ExitThread(c->code);
}

#endif

struct qemu_TerminateThread
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TerminateThread(HANDLE handle, DWORD exit_code)
{
    struct qemu_TerminateThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TERMINATETHREAD);
    call.handle = (uint64_t)handle;
    call.exit_code = (uint64_t)exit_code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TerminateThread(struct qemu_syscall *call)
{
    struct qemu_TerminateThread *c = (struct qemu_TerminateThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TerminateThread(QEMU_G2H(c->handle), c->exit_code);
}

#endif

struct qemu_FreeLibraryAndExitThread
{
    struct qemu_syscall super;
    uint64_t hLibModule;
    uint64_t dwExitCode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FreeLibraryAndExitThread(HINSTANCE hLibModule, DWORD dwExitCode)
{
    struct qemu_FreeLibraryAndExitThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREELIBRARYANDEXITTHREAD);
    call.hLibModule = (uint64_t)hLibModule;
    call.dwExitCode = (uint64_t)dwExitCode;

    qemu_syscall(&call.super);

    __builtin_unreachable();
}

#else

void qemu_FreeLibraryAndExitThread(struct qemu_syscall *call)
{
    struct qemu_FreeLibraryAndExitThread *c = (struct qemu_FreeLibraryAndExitThread *)call;
    WINE_FIXME("Unverified!\n");
    FreeLibraryAndExitThread(QEMU_G2H(c->hLibModule), c->dwExitCode);
}

#endif

struct qemu_GetExitCodeThread
{
    struct qemu_syscall super;
    uint64_t hthread;
    uint64_t exitcode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetExitCodeThread(HANDLE hthread, LPDWORD exitcode)
{
    struct qemu_GetExitCodeThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXITCODETHREAD);
    call.hthread = (uint64_t)hthread;
    call.exitcode = (uint64_t)exitcode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExitCodeThread(struct qemu_syscall *call)
{
    struct qemu_GetExitCodeThread *c = (struct qemu_GetExitCodeThread *)call;
    WINE_TRACE("\n");
    c->super.iret = GetExitCodeThread((HANDLE)c->hthread, QEMU_G2H(c->exitcode));
}

#endif

struct qemu_SetThreadContext
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadContext(HANDLE handle, const CONTEXT *context)
{
    struct qemu_SetThreadContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADCONTEXT);
    call.handle = (uint64_t)handle;
    call.context = (uint64_t)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadContext(struct qemu_syscall *call)
{
    struct qemu_SetThreadContext *c = (struct qemu_SetThreadContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadContext(QEMU_G2H(c->handle), QEMU_G2H(c->context));
}

#endif

struct qemu_GetThreadContext
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadContext(HANDLE handle, CONTEXT *context)
{
    struct qemu_GetThreadContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADCONTEXT);
    call.handle = (uint64_t)handle;
    call.context = (uint64_t)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadContext(struct qemu_syscall *call)
{
    struct qemu_GetThreadContext *c = (struct qemu_GetThreadContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadContext(QEMU_G2H(c->handle), QEMU_G2H(c->context));
}

#endif

struct qemu_SuspendThread
{
    struct qemu_syscall super;
    uint64_t hthread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SuspendThread(HANDLE hthread)
{
    struct qemu_SuspendThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SUSPENDTHREAD);
    call.hthread = (uint64_t)hthread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SuspendThread(struct qemu_syscall *call)
{
    struct qemu_SuspendThread *c = (struct qemu_SuspendThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SuspendThread(QEMU_G2H(c->hthread));
}

#endif

struct qemu_ResumeThread
{
    struct qemu_syscall super;
    uint64_t hthread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ResumeThread(HANDLE hthread)
{
    struct qemu_ResumeThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESUMETHREAD);
    call.hthread = (uint64_t)hthread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResumeThread(struct qemu_syscall *call)
{
    struct qemu_ResumeThread *c = (struct qemu_ResumeThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ResumeThread(QEMU_G2H(c->hthread));
}

#endif

struct qemu_GetThreadPriority
{
    struct qemu_syscall super;
    uint64_t hthread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetThreadPriority(HANDLE hthread)
{
    struct qemu_GetThreadPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADPRIORITY);
    call.hthread = (uint64_t)hthread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadPriority(struct qemu_syscall *call)
{
    struct qemu_GetThreadPriority *c = (struct qemu_GetThreadPriority *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadPriority(QEMU_G2H(c->hthread));
}

#endif

struct qemu_SetThreadPriority
{
    struct qemu_syscall super;
    uint64_t hthread;
    uint64_t priority;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadPriority(HANDLE hthread, INT priority)
{
    struct qemu_SetThreadPriority call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADPRIORITY);
    call.hthread = (uint64_t)hthread;
    call.priority = (uint64_t)priority;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadPriority(struct qemu_syscall *call)
{
    struct qemu_SetThreadPriority *c = (struct qemu_SetThreadPriority *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadPriority(QEMU_G2H(c->hthread), c->priority);
}

#endif

struct qemu_GetThreadPriorityBoost
{
    struct qemu_syscall super;
    uint64_t hthread;
    uint64_t pstate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadPriorityBoost(HANDLE hthread, PBOOL pstate)
{
    struct qemu_GetThreadPriorityBoost call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADPRIORITYBOOST);
    call.hthread = (uint64_t)hthread;
    call.pstate = (uint64_t)pstate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadPriorityBoost(struct qemu_syscall *call)
{
    struct qemu_GetThreadPriorityBoost *c = (struct qemu_GetThreadPriorityBoost *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadPriorityBoost(QEMU_G2H(c->hthread), QEMU_G2H(c->pstate));
}

#endif

struct qemu_SetThreadPriorityBoost
{
    struct qemu_syscall super;
    uint64_t hthread;
    uint64_t disable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadPriorityBoost(HANDLE hthread, BOOL disable)
{
    struct qemu_SetThreadPriorityBoost call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADPRIORITYBOOST);
    call.hthread = (uint64_t)hthread;
    call.disable = (uint64_t)disable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadPriorityBoost(struct qemu_syscall *call)
{
    struct qemu_SetThreadPriorityBoost *c = (struct qemu_SetThreadPriorityBoost *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadPriorityBoost(QEMU_G2H(c->hthread), c->disable);
}

#endif

struct qemu_SetThreadStackGuarantee
{
    struct qemu_syscall super;
    uint64_t stacksize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadStackGuarantee(PULONG stacksize)
{
    struct qemu_SetThreadStackGuarantee call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADSTACKGUARANTEE);
    call.stacksize = (uint64_t)stacksize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetThreadStackGuarantee to Wine headers? */
extern BOOL WINAPI SetThreadStackGuarantee(PULONG stacksize);
void qemu_SetThreadStackGuarantee(struct qemu_syscall *call)
{
    struct qemu_SetThreadStackGuarantee *c = (struct qemu_SetThreadStackGuarantee *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadStackGuarantee(QEMU_G2H(c->stacksize));
}

#endif

struct qemu_GetThreadGroupAffinity
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t affinity;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadGroupAffinity(HANDLE thread, GROUP_AFFINITY *affinity)
{
    struct qemu_GetThreadGroupAffinity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADGROUPAFFINITY);
    call.thread = (uint64_t)thread;
    call.affinity = (uint64_t)affinity;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetThreadGroupAffinity to Wine headers? */
extern BOOL WINAPI GetThreadGroupAffinity(HANDLE thread, GROUP_AFFINITY *affinity);
void qemu_GetThreadGroupAffinity(struct qemu_syscall *call)
{
    struct qemu_GetThreadGroupAffinity *c = (struct qemu_GetThreadGroupAffinity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadGroupAffinity(QEMU_G2H(c->thread), QEMU_G2H(c->affinity));
}

#endif

struct qemu_SetThreadGroupAffinity
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t affinity_new;
    uint64_t affinity_old;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadGroupAffinity(HANDLE thread, const GROUP_AFFINITY *affinity_new, GROUP_AFFINITY *affinity_old)
{
    struct qemu_SetThreadGroupAffinity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADGROUPAFFINITY);
    call.thread = (uint64_t)thread;
    call.affinity_new = (uint64_t)affinity_new;
    call.affinity_old = (uint64_t)affinity_old;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetThreadGroupAffinity to Wine headers? */
extern BOOL WINAPI SetThreadGroupAffinity(HANDLE thread, const GROUP_AFFINITY *affinity_new, GROUP_AFFINITY *affinity_old);
void qemu_SetThreadGroupAffinity(struct qemu_syscall *call)
{
    struct qemu_SetThreadGroupAffinity *c = (struct qemu_SetThreadGroupAffinity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadGroupAffinity(QEMU_G2H(c->thread), QEMU_G2H(c->affinity_new), QEMU_G2H(c->affinity_old));
}

#endif

struct qemu_SetThreadAffinityMask
{
    struct qemu_syscall super;
    uint64_t hThread;
    uint64_t dwThreadAffinityMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD_PTR WINAPI SetThreadAffinityMask(HANDLE hThread, DWORD_PTR dwThreadAffinityMask)
{
    struct qemu_SetThreadAffinityMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADAFFINITYMASK);
    call.hThread = (uint64_t)hThread;
    call.dwThreadAffinityMask = (uint64_t)dwThreadAffinityMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadAffinityMask(struct qemu_syscall *call)
{
    struct qemu_SetThreadAffinityMask *c = (struct qemu_SetThreadAffinityMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadAffinityMask(QEMU_G2H(c->hThread), c->dwThreadAffinityMask);
}

#endif

struct qemu_SetThreadIdealProcessor
{
    struct qemu_syscall super;
    uint64_t hThread;
    uint64_t dwIdealProcessor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetThreadIdealProcessor(HANDLE hThread, DWORD dwIdealProcessor)
{
    struct qemu_SetThreadIdealProcessor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADIDEALPROCESSOR);
    call.hThread = (uint64_t)hThread;
    call.dwIdealProcessor = (uint64_t)dwIdealProcessor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadIdealProcessor(struct qemu_syscall *call)
{
    struct qemu_SetThreadIdealProcessor *c = (struct qemu_SetThreadIdealProcessor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadIdealProcessor(QEMU_G2H(c->hThread), c->dwIdealProcessor);
}

#endif

struct qemu_SetThreadIdealProcessorEx
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t ideal;
    uint64_t previous;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadIdealProcessorEx(HANDLE thread, PROCESSOR_NUMBER *ideal, PROCESSOR_NUMBER *previous)
{
    struct qemu_SetThreadIdealProcessorEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADIDEALPROCESSOREX);
    call.thread = (uint64_t)thread;
    call.ideal = (uint64_t)ideal;
    call.previous = (uint64_t)previous;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetThreadIdealProcessorEx to Wine headers? */
extern BOOL WINAPI SetThreadIdealProcessorEx(HANDLE thread, PROCESSOR_NUMBER *ideal, PROCESSOR_NUMBER *previous);
void qemu_SetThreadIdealProcessorEx(struct qemu_syscall *call)
{
    struct qemu_SetThreadIdealProcessorEx *c = (struct qemu_SetThreadIdealProcessorEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadIdealProcessorEx(QEMU_G2H(c->thread), QEMU_G2H(c->ideal), QEMU_G2H(c->previous));
}

#endif

struct qemu_GetThreadSelectorEntry
{
    struct qemu_syscall super;
    uint64_t hthread;
    uint64_t sel;
    uint64_t ldtent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadSelectorEntry(HANDLE hthread, DWORD sel, LPLDT_ENTRY ldtent)
{
    struct qemu_GetThreadSelectorEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADSELECTORENTRY);
    call.hthread = (uint64_t)hthread;
    call.sel = (uint64_t)sel;
    call.ldtent = (uint64_t)ldtent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadSelectorEntry(struct qemu_syscall *call)
{
    struct qemu_GetThreadSelectorEntry *c = (struct qemu_GetThreadSelectorEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadSelectorEntry(QEMU_G2H(c->hthread), c->sel, QEMU_G2H(c->ldtent));
}

#endif

struct qemu_QueueUserAPC
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t hthread;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI QueueUserAPC(PAPCFUNC func, HANDLE hthread, ULONG_PTR data)
{
    struct qemu_QueueUserAPC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUEUEUSERAPC);
    call.func = (uint64_t)func;
    call.hthread = (uint64_t)hthread;
    call.data = (uint64_t)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct apc_data
{
    uint64_t guest_data;
    uint64_t func;
};

static void CALLBACK host_user_apc_cb(ULONG_PTR param)
{
    struct apc_data *data = (struct apc_data *)param;
    uint64_t func = data->func;
    uint64_t guest_data = data->guest_data;

    HeapFree(GetProcessHeap(), 0, data);
    WINE_TRACE("Executing user APC callback 0x%lx(0x%lx).\n", func, guest_data);
    qemu_ops->qemu_execute(QEMU_G2H(func), guest_data);
    WINE_TRACE("User callback returned.\n");
}

void qemu_QueueUserAPC(struct qemu_syscall *call)
{
    struct qemu_QueueUserAPC *c = (struct qemu_QueueUserAPC *)call;
    struct apc_data *data;

    WINE_TRACE("\n");

    /* Note that this will fail spectacularly if the thread is in a different process. Fixing
     * this not only requires allocating the wrapper structure in the foreign process, but
     * also figuring out the address of host_user_apc_cb (which presumably is at an identical
     * offset from qemu_dll_register as it is in this process).
     *
     * And that's not even talking about host-native processes like explorer.exe which don't
     * even have QEMU loaded. */
    data = HeapAlloc(GetProcessHeap(), 0, sizeof(*data));
    if (!data)
    {
        c->super.iret = 0;
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return;
    }

    data->guest_data = c->data;
    data->func = c->func;

    c->super.iret = QueueUserAPC(host_user_apc_cb, (HANDLE)c->hthread, (ULONG_PTR)data);
    if (!c->super.iret)
        HeapFree(GetProcessHeap(), 0, data);
}

#endif

struct qemu_QueueUserWorkItem
{
    struct qemu_syscall super;
    uint64_t Function;
    uint64_t Context;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueueUserWorkItem(LPTHREAD_START_ROUTINE Function, PVOID Context, ULONG Flags)
{
    struct qemu_QueueUserWorkItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUEUEUSERWORKITEM);
    call.Function = (uint64_t)Function;
    call.Context = (uint64_t)Context;
    call.Flags = (uint64_t)Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueueUserWorkItem(struct qemu_syscall *call)
{
    struct qemu_QueueUserWorkItem *c = (struct qemu_QueueUserWorkItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueueUserWorkItem(QEMU_G2H(c->Function), QEMU_G2H(c->Context), c->Flags);
}

#endif

struct qemu_GetThreadTimes
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t creationtime;
    uint64_t exittime;
    uint64_t kerneltime;
    uint64_t usertime;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadTimes(HANDLE thread, LPFILETIME creationtime, LPFILETIME exittime, LPFILETIME kerneltime, LPFILETIME usertime)
{
    struct qemu_GetThreadTimes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADTIMES);
    call.thread = (uint64_t)thread;
    call.creationtime = (uint64_t)creationtime;
    call.exittime = (uint64_t)exittime;
    call.kerneltime = (uint64_t)kerneltime;
    call.usertime = (uint64_t)usertime;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadTimes(struct qemu_syscall *call)
{
    struct qemu_GetThreadTimes *c = (struct qemu_GetThreadTimes *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadTimes(QEMU_G2H(c->thread), QEMU_G2H(c->creationtime), QEMU_G2H(c->exittime), QEMU_G2H(c->kerneltime), QEMU_G2H(c->usertime));
}

#endif

struct qemu_GetThreadId
{
    struct qemu_syscall super;
    uint64_t Thread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetThreadId(HANDLE Thread)
{
    struct qemu_GetThreadId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADID);
    call.Thread = (uint64_t)Thread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadId(struct qemu_syscall *call)
{
    struct qemu_GetThreadId *c = (struct qemu_GetThreadId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadId(QEMU_G2H(c->Thread));
}

#endif

struct qemu_GetProcessIdOfThread
{
    struct qemu_syscall super;
    uint64_t Thread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProcessIdOfThread(HANDLE Thread)
{
    struct qemu_GetProcessIdOfThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSIDOFTHREAD);
    call.Thread = (uint64_t)Thread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessIdOfThread(struct qemu_syscall *call)
{
    struct qemu_GetProcessIdOfThread *c = (struct qemu_GetProcessIdOfThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessIdOfThread(QEMU_G2H(c->Thread));
}

#endif

struct qemu_GetCurrentThread
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetCurrentThread(void)
{
    struct qemu_GetCurrentThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTTHREAD);

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_GetCurrentThread(struct qemu_syscall *call)
{
    struct qemu_GetCurrentThread *c = (struct qemu_GetCurrentThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetCurrentThread();
}

#endif

struct qemu_SetLastError
{
    struct qemu_syscall super;
    uint64_t error;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SetLastError(DWORD error)
{
    struct qemu_SetLastError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLASTERROR);
    call.error = error;
    qemu_syscall(&call.super);
}

#else

void qemu_SetLastError(struct qemu_syscall *call)
{
    struct qemu_SetLastError *c = (struct qemu_SetLastError *)call;
    WINE_TRACE("\n");
    SetLastError(c->error);
}

#endif

#ifdef QEMU_DLL_GUEST

DWORD WINAPI kernel32_GetLastError()
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETLASTERROR);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetLastError(struct qemu_syscall *call)
{
    /* FIXME: This reads the result from the host-side TEB. Ab application
     * that manually reads the TEB will read from the client-side TEB and
     * get a different result. A possible solution is to hook the host-side
     * SetLastError function and update both TEBs. */
    WINE_TRACE("\n");
    call->iret = GetLastError();
}

#endif

struct qemu_SetThreadErrorMode
{
    struct qemu_syscall super;
    uint64_t mode;
    uint64_t oldmode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetThreadErrorMode(DWORD mode, LPDWORD oldmode)
{
    struct qemu_SetThreadErrorMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADERRORMODE);
    call.mode = (uint64_t)mode;
    call.oldmode = (uint64_t)oldmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadErrorMode(struct qemu_syscall *call)
{
    struct qemu_SetThreadErrorMode *c = (struct qemu_SetThreadErrorMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetThreadErrorMode(c->mode, QEMU_G2H(c->oldmode));
}

#endif

struct qemu_GetThreadErrorMode
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetThreadErrorMode(void)
{
    struct qemu_GetThreadErrorMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADERRORMODE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadErrorMode(struct qemu_syscall *call)
{
    struct qemu_GetThreadErrorMode *c = (struct qemu_GetThreadErrorMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadErrorMode();
}

#endif

struct qemu_GetThreadUILanguage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LANGID WINAPI GetThreadUILanguage(void)
{
    struct qemu_GetThreadUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADUILANGUAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadUILanguage(struct qemu_syscall *call)
{
    struct qemu_GetThreadUILanguage *c = (struct qemu_GetThreadUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadUILanguage();
}

#endif

struct qemu_GetThreadIOPendingFlag
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t io_pending;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetThreadIOPendingFlag(HANDLE thread, PBOOL io_pending)
{
    struct qemu_GetThreadIOPendingFlag call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADIOPENDINGFLAG);
    call.thread = (uint64_t)thread;
    call.io_pending = (uint64_t)io_pending;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetThreadIOPendingFlag(struct qemu_syscall *call)
{
    struct qemu_GetThreadIOPendingFlag *c = (struct qemu_GetThreadIOPendingFlag *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetThreadIOPendingFlag(QEMU_G2H(c->thread), QEMU_G2H(c->io_pending));
}

#endif

struct qemu_CallbackMayRunLong
{
    struct qemu_syscall super;
    uint64_t instance;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CallbackMayRunLong(TP_CALLBACK_INSTANCE *instance)
{
    struct qemu_CallbackMayRunLong call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLBACKMAYRUNLONG);
    call.instance = (uint64_t)instance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CallbackMayRunLong to Wine headers? */
extern BOOL WINAPI CallbackMayRunLong(TP_CALLBACK_INSTANCE *instance);
void qemu_CallbackMayRunLong(struct qemu_syscall *call)
{
    struct qemu_CallbackMayRunLong *c = (struct qemu_CallbackMayRunLong *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallbackMayRunLong(QEMU_G2H(c->instance));
}

#endif

struct qemu_CreateThreadpool
{
    struct qemu_syscall super;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PTP_POOL WINAPI CreateThreadpool(PVOID reserved)
{
    struct qemu_CreateThreadpool call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETHREADPOOL);
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return (PTP_POOL)call.super.iret;
}

#else

void qemu_CreateThreadpool(struct qemu_syscall *call)
{
    struct qemu_CreateThreadpool *c = (struct qemu_CreateThreadpool *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateThreadpool(QEMU_G2H(c->reserved)));
}

#endif

struct qemu_CreateThreadpoolCleanupGroup
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PTP_CLEANUP_GROUP WINAPI CreateThreadpoolCleanupGroup(void)
{
    struct qemu_CreateThreadpoolCleanupGroup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETHREADPOOLCLEANUPGROUP);

    qemu_syscall(&call.super);

    return (PTP_CLEANUP_GROUP)call.super.iret;
}

#else

void qemu_CreateThreadpoolCleanupGroup(struct qemu_syscall *call)
{
    struct qemu_CreateThreadpoolCleanupGroup *c = (struct qemu_CreateThreadpoolCleanupGroup *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateThreadpoolCleanupGroup());
}

#endif

struct qemu_CreateThreadpoolTimer
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PTP_TIMER WINAPI CreateThreadpoolTimer(PTP_TIMER_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_CreateThreadpoolTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETHREADPOOLTIMER);
    call.callback = (uint64_t)callback;
    call.userdata = (uint64_t)userdata;
    call.environment = (uint64_t)environment;

    qemu_syscall(&call.super);

    return (PTP_TIMER)call.super.iret;
}

#else

void qemu_CreateThreadpoolTimer(struct qemu_syscall *call)
{
    struct qemu_CreateThreadpoolTimer *c = (struct qemu_CreateThreadpoolTimer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateThreadpoolTimer(QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment)));
}

#endif

struct qemu_CreateThreadpoolWait
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PTP_WAIT WINAPI CreateThreadpoolWait(PTP_WAIT_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_CreateThreadpoolWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETHREADPOOLWAIT);
    call.callback = (uint64_t)callback;
    call.userdata = (uint64_t)userdata;
    call.environment = (uint64_t)environment;

    qemu_syscall(&call.super);

    return (PTP_WAIT)call.super.iret;
}

#else

void qemu_CreateThreadpoolWait(struct qemu_syscall *call)
{
    struct qemu_CreateThreadpoolWait *c = (struct qemu_CreateThreadpoolWait *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateThreadpoolWait(QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment)));
}

#endif

struct qemu_CreateThreadpoolWork
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PTP_WORK WINAPI CreateThreadpoolWork(PTP_WORK_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_CreateThreadpoolWork call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETHREADPOOLWORK);
    call.callback = (uint64_t)callback;
    call.userdata = (uint64_t)userdata;
    call.environment = (uint64_t)environment;

    qemu_syscall(&call.super);

    return (PTP_WORK)call.super.iret;
}

#else

void qemu_CreateThreadpoolWork(struct qemu_syscall *call)
{
    struct qemu_CreateThreadpoolWork *c = (struct qemu_CreateThreadpoolWork *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateThreadpoolWork(QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment)));
}

#endif

struct qemu_SetThreadpoolTimer
{
    struct qemu_syscall super;
    uint64_t timer;
    uint64_t due_time;
    uint64_t period;
    uint64_t window_length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SetThreadpoolTimer(TP_TIMER *timer, FILETIME *due_time, DWORD period, DWORD window_length)
{
    struct qemu_SetThreadpoolTimer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADPOOLTIMER);
    call.timer = (uint64_t)timer;
    call.due_time = (uint64_t)due_time;
    call.period = (uint64_t)period;
    call.window_length = (uint64_t)window_length;

    qemu_syscall(&call.super);
}

#else

void qemu_SetThreadpoolTimer(struct qemu_syscall *call)
{
    struct qemu_SetThreadpoolTimer *c = (struct qemu_SetThreadpoolTimer *)call;
    WINE_FIXME("Unverified!\n");
    SetThreadpoolTimer(QEMU_G2H(c->timer), QEMU_G2H(c->due_time), c->period, c->window_length);
}

#endif

struct qemu_SetThreadpoolWait
{
    struct qemu_syscall super;
    uint64_t wait;
    uint64_t handle;
    uint64_t due_time;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI SetThreadpoolWait(TP_WAIT *wait, HANDLE handle, FILETIME *due_time)
{
    struct qemu_SetThreadpoolWait call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADPOOLWAIT);
    call.wait = (uint64_t)wait;
    call.handle = (uint64_t)handle;
    call.due_time = (uint64_t)due_time;

    qemu_syscall(&call.super);
}

#else

void qemu_SetThreadpoolWait(struct qemu_syscall *call)
{
    struct qemu_SetThreadpoolWait *c = (struct qemu_SetThreadpoolWait *)call;
    WINE_FIXME("Unverified!\n");
    SetThreadpoolWait(QEMU_G2H(c->wait), QEMU_G2H(c->handle), QEMU_G2H(c->due_time));
}

#endif

struct qemu_TrySubmitThreadpoolCallback
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t userdata;
    uint64_t environment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TrySubmitThreadpoolCallback(PTP_SIMPLE_CALLBACK callback, PVOID userdata, TP_CALLBACK_ENVIRON *environment)
{
    struct qemu_TrySubmitThreadpoolCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRYSUBMITTHREADPOOLCALLBACK);
    call.callback = (uint64_t)callback;
    call.userdata = (uint64_t)userdata;
    call.environment = (uint64_t)environment;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TrySubmitThreadpoolCallback(struct qemu_syscall *call)
{
    struct qemu_TrySubmitThreadpoolCallback *c = (struct qemu_TrySubmitThreadpoolCallback *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TrySubmitThreadpoolCallback(QEMU_G2H(c->callback), QEMU_G2H(c->userdata), QEMU_G2H(c->environment));
}

#endif

