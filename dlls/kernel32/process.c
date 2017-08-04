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
#include <psapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CreateProcessA
{
    struct qemu_syscall super;
    uint64_t app_name;
    uint64_t cmd_line;
    uint64_t process_attr;
    uint64_t thread_attr;
    uint64_t inherit;
    uint64_t flags;
    uint64_t env;
    uint64_t cur_dir;
    uint64_t startup_info;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateProcessA(LPCSTR app_name, LPSTR cmd_line, LPSECURITY_ATTRIBUTES process_attr, LPSECURITY_ATTRIBUTES thread_attr, BOOL inherit, DWORD flags, LPVOID env, LPCSTR cur_dir, LPSTARTUPINFOA startup_info, LPPROCESS_INFORMATION info)
{
    struct qemu_CreateProcessA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROCESSA);
    call.app_name = (uint64_t)app_name;
    call.cmd_line = (uint64_t)cmd_line;
    call.process_attr = (uint64_t)process_attr;
    call.thread_attr = (uint64_t)thread_attr;
    call.inherit = (uint64_t)inherit;
    call.flags = (uint64_t)flags;
    call.env = (uint64_t)env;
    call.cur_dir = (uint64_t)cur_dir;
    call.startup_info = (uint64_t)startup_info;
    call.info = (uint64_t)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateProcessA(struct qemu_syscall *call)
{
    struct qemu_CreateProcessA *c = (struct qemu_CreateProcessA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProcessA(QEMU_G2H(c->app_name), QEMU_G2H(c->cmd_line), QEMU_G2H(c->process_attr), QEMU_G2H(c->thread_attr), c->inherit, c->flags, QEMU_G2H(c->env), QEMU_G2H(c->cur_dir), QEMU_G2H(c->startup_info), QEMU_G2H(c->info));
}

#endif

struct qemu_CreateProcessW
{
    struct qemu_syscall super;
    uint64_t app_name;
    uint64_t cmd_line;
    uint64_t process_attr;
    uint64_t thread_attr;
    uint64_t inherit;
    uint64_t flags;
    uint64_t env;
    uint64_t cur_dir;
    uint64_t startup_info;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CreateProcessW(LPCWSTR app_name, LPWSTR cmd_line, LPSECURITY_ATTRIBUTES process_attr, LPSECURITY_ATTRIBUTES thread_attr, BOOL inherit, DWORD flags, LPVOID env, LPCWSTR cur_dir, LPSTARTUPINFOW startup_info, LPPROCESS_INFORMATION info)
{
    struct qemu_CreateProcessW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROCESSW);
    call.app_name = (uint64_t)app_name;
    call.cmd_line = (uint64_t)cmd_line;
    call.process_attr = (uint64_t)process_attr;
    call.thread_attr = (uint64_t)thread_attr;
    call.inherit = (uint64_t)inherit;
    call.flags = (uint64_t)flags;
    call.env = (uint64_t)env;
    call.cur_dir = (uint64_t)cur_dir;
    call.startup_info = (uint64_t)startup_info;
    call.info = (uint64_t)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateProcessW(struct qemu_syscall *call)
{
    struct qemu_CreateProcessW *c = (struct qemu_CreateProcessW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateProcessW(QEMU_G2H(c->app_name), QEMU_G2H(c->cmd_line), QEMU_G2H(c->process_attr), QEMU_G2H(c->thread_attr), c->inherit, c->flags, QEMU_G2H(c->env), QEMU_G2H(c->cur_dir), QEMU_G2H(c->startup_info), QEMU_G2H(c->info));
}

#endif

struct qemu_WinExec
{
    struct qemu_syscall super;
    uint64_t lpCmdLine;
    uint64_t nCmdShow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI WinExec(LPCSTR lpCmdLine, UINT nCmdShow)
{
    struct qemu_WinExec call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINEXEC);
    call.lpCmdLine = (uint64_t)lpCmdLine;
    call.nCmdShow = (uint64_t)nCmdShow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WinExec(struct qemu_syscall *call)
{
    struct qemu_WinExec *c = (struct qemu_WinExec *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WinExec(QEMU_G2H(c->lpCmdLine), c->nCmdShow);
}

#endif

struct qemu_LoadModule
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t paramBlock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI LoadModule(LPCSTR name, LPVOID paramBlock)
{
    struct qemu_LoadModule call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADMODULE);
    call.name = (uint64_t)name;
    call.paramBlock = (uint64_t)paramBlock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LoadModule(struct qemu_syscall *call)
{
    struct qemu_LoadModule *c = (struct qemu_LoadModule *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LoadModule(QEMU_G2H(c->name), QEMU_G2H(c->paramBlock));
}

#endif

struct qemu_TerminateProcess
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t exit_code;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI TerminateProcess(HANDLE handle, UINT exit_code)
{
    struct qemu_TerminateProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TERMINATEPROCESS);
    call.handle = (uint64_t)handle;
    call.exit_code = exit_code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TerminateProcess(struct qemu_syscall *call)
{
    struct qemu_TerminateProcess *c = (struct qemu_TerminateProcess *)call;
    WINE_TRACE("\n");
    c->super.iret = TerminateProcess((HANDLE)c->handle, c->exit_code);
}

#endif

struct qemu_ExitProcess
{
    struct qemu_syscall super;
    uint64_t exitcode;
};

#ifdef QEMU_DLL_GUEST

DECLSPEC_NORETURN void WINAPI kernel32_ExitProcess(UINT exitcode)
{
    struct qemu_ExitProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXITPROCESS);
    call.exitcode = exitcode;

    qemu_syscall(&call.super);

    while(1); /* The syscall does not exit, but gcc does not know that. */
}

#else

void qemu_ExitProcess(struct qemu_syscall *call)
{
    struct qemu_ExitProcess *c = (struct qemu_ExitProcess *)call;
    WINE_TRACE("\n");
    ExitProcess(c->exitcode);
}

#endif

struct qemu_GetExitCodeProcess
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t lpExitCode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode)
{
    struct qemu_GetExitCodeProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXITCODEPROCESS);
    call.hProcess = (uint64_t)hProcess;
    call.lpExitCode = (uint64_t)lpExitCode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExitCodeProcess(struct qemu_syscall *call)
{
    struct qemu_GetExitCodeProcess *c = (struct qemu_GetExitCodeProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExitCodeProcess(QEMU_G2H(c->hProcess), QEMU_G2H(c->lpExitCode));
}

#endif

struct qemu_SetErrorMode
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI SetErrorMode(UINT mode)
{
    struct qemu_SetErrorMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETERRORMODE);
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetErrorMode(struct qemu_syscall *call)
{
    struct qemu_SetErrorMode *c = (struct qemu_SetErrorMode *)call;
    WINE_WARN("Need integration with guest-side error handlers.\n");
    c->super.iret = SetErrorMode(c->mode);
}

#endif

struct qemu_GetErrorMode
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetErrorMode(void)
{
    struct qemu_GetErrorMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETERRORMODE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetErrorMode(struct qemu_syscall *call)
{
    struct qemu_GetErrorMode *c = (struct qemu_GetErrorMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetErrorMode();
}

#endif

struct qemu_TlsAlloc
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI TlsAlloc(void)
{
    struct qemu_TlsAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TLSALLOC);

    /* This should be done on the guest side using the guest TEB. */
    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TlsAlloc(struct qemu_syscall *call)
{
    struct qemu_TlsAlloc *c = (struct qemu_TlsAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = TlsAlloc();
}

#endif

struct qemu_TlsFree
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TlsFree(DWORD index)
{
    struct qemu_TlsFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TLSFREE);
    call.index = (uint64_t)index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TlsFree(struct qemu_syscall *call)
{
    struct qemu_TlsFree *c = (struct qemu_TlsFree *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TlsFree(c->index);
}

#endif

struct qemu_TlsGetValue
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI TlsGetValue(DWORD index)
{
    struct qemu_TlsGetValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TLSGETVALUE);
    call.index = (uint64_t)index;

    /* This should be done on the guest side using the guest TEB. */
    qemu_syscall(&call.super);

    return (LPVOID)call.super.iret;
}

#else

void qemu_TlsGetValue(struct qemu_syscall *call)
{
    struct qemu_TlsGetValue *c = (struct qemu_TlsGetValue *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)TlsGetValue(c->index);
}

#endif

struct qemu_TlsSetValue
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TlsSetValue(DWORD index, LPVOID value)
{
    struct qemu_TlsSetValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TLSSETVALUE);
    call.index = (uint64_t)index;
    call.value = (uint64_t)value;

    /* This should be done on the guest side using the guest TEB. */
    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TlsSetValue(struct qemu_syscall *call)
{
    struct qemu_TlsSetValue *c = (struct qemu_TlsSetValue *)call;
    WINE_TRACE("\n");
    c->super.iret = TlsSetValue(c->index, QEMU_G2H(c->value));
}

#endif

struct qemu_GetProcessFlags
{
    struct qemu_syscall super;
    uint64_t processid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProcessFlags(DWORD processid)
{
    struct qemu_GetProcessFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSFLAGS);
    call.processid = (uint64_t)processid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetProcessFlags to Wine headers? */
extern DWORD WINAPI GetProcessFlags(DWORD processid);
void qemu_GetProcessFlags(struct qemu_syscall *call)
{
    struct qemu_GetProcessFlags *c = (struct qemu_GetProcessFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessFlags(c->processid);
}

#endif

struct qemu_OpenProcess
{
    struct qemu_syscall super;
    uint64_t access;
    uint64_t inherit;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI OpenProcess(DWORD access, BOOL inherit, DWORD id)
{
    struct qemu_OpenProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENPROCESS);
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.id = (uint64_t)id;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_OpenProcess(struct qemu_syscall *call)
{
    struct qemu_OpenProcess *c = (struct qemu_OpenProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)OpenProcess(c->access, c->inherit, c->id);
}

#endif

struct qemu_GetProcessId
{
    struct qemu_syscall super;
    uint64_t hProcess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProcessId(HANDLE hProcess)
{
    struct qemu_GetProcessId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSID);
    call.hProcess = (uint64_t)hProcess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessId(struct qemu_syscall *call)
{
    struct qemu_GetProcessId *c = (struct qemu_GetProcessId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessId(QEMU_G2H(c->hProcess));
}

#endif

struct qemu_CloseHandle
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseHandle(HANDLE handle)
{
    struct qemu_CloseHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEHANDLE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseHandle(struct qemu_syscall *call)
{
    struct qemu_CloseHandle *c = (struct qemu_CloseHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseHandle((HANDLE)c->handle);
}

#endif

struct qemu_GetHandleInformation
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetHandleInformation(HANDLE handle, LPDWORD flags)
{
    struct qemu_GetHandleInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETHANDLEINFORMATION);
    call.handle = (uint64_t)handle;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetHandleInformation(struct qemu_syscall *call)
{
    struct qemu_GetHandleInformation *c = (struct qemu_GetHandleInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetHandleInformation(QEMU_G2H(c->handle), QEMU_G2H(c->flags));
}

#endif

struct qemu_SetHandleInformation
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t mask;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetHandleInformation(HANDLE handle, DWORD mask, DWORD flags)
{
    struct qemu_SetHandleInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETHANDLEINFORMATION);
    call.handle = (uint64_t)handle;
    call.mask = (uint64_t)mask;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetHandleInformation(struct qemu_syscall *call)
{
    struct qemu_SetHandleInformation *c = (struct qemu_SetHandleInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetHandleInformation(QEMU_G2H(c->handle), c->mask, c->flags);
}

#endif

struct qemu_DuplicateHandle
{
    struct qemu_syscall super;
    uint64_t source_process;
    uint64_t source;
    uint64_t dest_process;
    uint64_t dest;
    uint64_t access;
    uint64_t inherit;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DuplicateHandle(HANDLE source_process, HANDLE source, HANDLE dest_process, HANDLE *dest, DWORD access, BOOL inherit, DWORD options)
{
    struct qemu_DuplicateHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DUPLICATEHANDLE);
    call.source_process = (uint64_t)source_process;
    call.source = (uint64_t)source;
    call.dest_process = (uint64_t)dest_process;
    call.dest = (uint64_t)dest;
    call.access = (uint64_t)access;
    call.inherit = (uint64_t)inherit;
    call.options = (uint64_t)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DuplicateHandle(struct qemu_syscall *call)
{
    struct qemu_DuplicateHandle *c = (struct qemu_DuplicateHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DuplicateHandle(QEMU_G2H(c->source_process), QEMU_G2H(c->source), QEMU_G2H(c->dest_process), QEMU_G2H(c->dest), c->access, c->inherit, c->options);
}

#endif

struct qemu_ConvertToGlobalHandle
{
    struct qemu_syscall super;
    uint64_t hSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI ConvertToGlobalHandle(HANDLE hSrc)
{
    struct qemu_ConvertToGlobalHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTTOGLOBALHANDLE);
    call.hSrc = (uint64_t)hSrc;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_ConvertToGlobalHandle(struct qemu_syscall *call)
{
    struct qemu_ConvertToGlobalHandle *c = (struct qemu_ConvertToGlobalHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ConvertToGlobalHandle(QEMU_G2H(c->hSrc));
}

#endif

struct qemu_SetHandleContext
{
    struct qemu_syscall super;
    uint64_t hnd;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetHandleContext(HANDLE hnd,DWORD context)
{
    struct qemu_SetHandleContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETHANDLECONTEXT);
    call.hnd = (uint64_t)hnd;
    call.context = (uint64_t)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetHandleContext to Wine headers? */
extern BOOL WINAPI SetHandleContext(HANDLE hnd,DWORD context);
void qemu_SetHandleContext(struct qemu_syscall *call)
{
    struct qemu_SetHandleContext *c = (struct qemu_SetHandleContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetHandleContext(QEMU_G2H(c->hnd), c->context);
}

#endif

struct qemu_GetHandleContext
{
    struct qemu_syscall super;
    uint64_t hnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetHandleContext(HANDLE hnd)
{
    struct qemu_GetHandleContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETHANDLECONTEXT);
    call.hnd = (uint64_t)hnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetHandleContext to Wine headers? */
extern DWORD WINAPI GetHandleContext(HANDLE hnd);
void qemu_GetHandleContext(struct qemu_syscall *call)
{
    struct qemu_GetHandleContext *c = (struct qemu_GetHandleContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetHandleContext(QEMU_G2H(c->hnd));
}

#endif

struct qemu_CreateSocketHandle
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateSocketHandle(void)
{
    struct qemu_CreateSocketHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESOCKETHANDLE);

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

/* TODO: Add CreateSocketHandle to Wine headers? */
extern HANDLE WINAPI CreateSocketHandle(void);
void qemu_CreateSocketHandle(struct qemu_syscall *call)
{
    struct qemu_CreateSocketHandle *c = (struct qemu_CreateSocketHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateSocketHandle();
}

#endif

struct qemu_SetPriorityClass
{
    struct qemu_syscall super;
    uint64_t hprocess;
    uint64_t priorityclass;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetPriorityClass(HANDLE hprocess, DWORD priorityclass)
{
    struct qemu_SetPriorityClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRIORITYCLASS);
    call.hprocess = (uint64_t)hprocess;
    call.priorityclass = (uint64_t)priorityclass;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPriorityClass(struct qemu_syscall *call)
{
    struct qemu_SetPriorityClass *c = (struct qemu_SetPriorityClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPriorityClass(QEMU_G2H(c->hprocess), c->priorityclass);
}

#endif

struct qemu_GetPriorityClass
{
    struct qemu_syscall super;
    uint64_t hProcess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPriorityClass(HANDLE hProcess)
{
    struct qemu_GetPriorityClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRIORITYCLASS);
    call.hProcess = (uint64_t)hProcess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPriorityClass(struct qemu_syscall *call)
{
    struct qemu_GetPriorityClass *c = (struct qemu_GetPriorityClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPriorityClass(QEMU_G2H(c->hProcess));
}

#endif

struct qemu_SetProcessAffinityMask
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t affmask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetProcessAffinityMask(HANDLE hProcess, DWORD_PTR affmask)
{
    struct qemu_SetProcessAffinityMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSAFFINITYMASK);
    call.hProcess = (uint64_t)hProcess;
    call.affmask = (uint64_t)affmask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessAffinityMask(struct qemu_syscall *call)
{
    struct qemu_SetProcessAffinityMask *c = (struct qemu_SetProcessAffinityMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetProcessAffinityMask(QEMU_G2H(c->hProcess), c->affmask);
}

#endif

struct qemu_GetProcessAffinityMask
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t process_mask;
    uint64_t system_mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessAffinityMask(HANDLE hProcess, PDWORD_PTR process_mask, PDWORD_PTR system_mask)
{
    struct qemu_GetProcessAffinityMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSAFFINITYMASK);
    call.hProcess = (uint64_t)hProcess;
    call.process_mask = (uint64_t)process_mask;
    call.system_mask = (uint64_t)system_mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessAffinityMask(struct qemu_syscall *call)
{
    struct qemu_GetProcessAffinityMask *c = (struct qemu_GetProcessAffinityMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessAffinityMask(QEMU_G2H(c->hProcess), QEMU_G2H(c->process_mask), QEMU_G2H(c->system_mask));
}

#endif

struct qemu_GetProcessVersion
{
    struct qemu_syscall super;
    uint64_t pid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProcessVersion(DWORD pid)
{
    struct qemu_GetProcessVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSVERSION);
    call.pid = (uint64_t)pid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessVersion(struct qemu_syscall *call)
{
    struct qemu_GetProcessVersion *c = (struct qemu_GetProcessVersion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessVersion(c->pid);
}

#endif

struct qemu_SetProcessWorkingSetSize
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t minset;
    uint64_t maxset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetProcessWorkingSetSize(HANDLE hProcess, SIZE_T minset, SIZE_T maxset)
{
    struct qemu_SetProcessWorkingSetSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSWORKINGSETSIZE);
    call.hProcess = (uint64_t)hProcess;
    call.minset = (uint64_t)minset;
    call.maxset = (uint64_t)maxset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessWorkingSetSize(struct qemu_syscall *call)
{
    struct qemu_SetProcessWorkingSetSize *c = (struct qemu_SetProcessWorkingSetSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetProcessWorkingSetSize(QEMU_G2H(c->hProcess), c->minset, c->maxset);
}

#endif

struct qemu_K32EmptyWorkingSet
{
    struct qemu_syscall super;
    uint64_t hProcess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EmptyWorkingSet(HANDLE hProcess)
{
    struct qemu_K32EmptyWorkingSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32EMPTYWORKINGSET);
    call.hProcess = (uint64_t)hProcess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32EmptyWorkingSet(struct qemu_syscall *call)
{
    struct qemu_K32EmptyWorkingSet *c = (struct qemu_K32EmptyWorkingSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EmptyWorkingSet(QEMU_G2H(c->hProcess));
}

#endif

struct qemu_GetProcessWorkingSetSize
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t minset;
    uint64_t maxset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessWorkingSetSize(HANDLE hProcess, PSIZE_T minset, PSIZE_T maxset)
{
    struct qemu_GetProcessWorkingSetSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSWORKINGSETSIZE);
    call.hProcess = (uint64_t)hProcess;
    call.minset = (uint64_t)minset;
    call.maxset = (uint64_t)maxset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessWorkingSetSize(struct qemu_syscall *call)
{
    struct qemu_GetProcessWorkingSetSize *c = (struct qemu_GetProcessWorkingSetSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessWorkingSetSize(QEMU_G2H(c->hProcess), QEMU_G2H(c->minset), QEMU_G2H(c->maxset));
}

#endif

struct qemu_SetProcessShutdownParameters
{
    struct qemu_syscall super;
    uint64_t level;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetProcessShutdownParameters(DWORD level, DWORD flags)
{
    struct qemu_SetProcessShutdownParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSSHUTDOWNPARAMETERS);
    call.level = (uint64_t)level;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessShutdownParameters(struct qemu_syscall *call)
{
    struct qemu_SetProcessShutdownParameters *c = (struct qemu_SetProcessShutdownParameters *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetProcessShutdownParameters(c->level, c->flags);
}

#endif

struct qemu_GetProcessShutdownParameters
{
    struct qemu_syscall super;
    uint64_t lpdwLevel;
    uint64_t lpdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessShutdownParameters(LPDWORD lpdwLevel, LPDWORD lpdwFlags)
{
    struct qemu_GetProcessShutdownParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSSHUTDOWNPARAMETERS);
    call.lpdwLevel = (uint64_t)lpdwLevel;
    call.lpdwFlags = (uint64_t)lpdwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessShutdownParameters(struct qemu_syscall *call)
{
    struct qemu_GetProcessShutdownParameters *c = (struct qemu_GetProcessShutdownParameters *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessShutdownParameters(QEMU_G2H(c->lpdwLevel), QEMU_G2H(c->lpdwFlags));
}

#endif

struct qemu_GetProcessPriorityBoost
{
    struct qemu_syscall super;
    uint64_t hprocess;
    uint64_t pDisablePriorityBoost;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessPriorityBoost(HANDLE hprocess,PBOOL pDisablePriorityBoost)
{
    struct qemu_GetProcessPriorityBoost call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSPRIORITYBOOST);
    call.hprocess = (uint64_t)hprocess;
    call.pDisablePriorityBoost = (uint64_t)pDisablePriorityBoost;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessPriorityBoost(struct qemu_syscall *call)
{
    struct qemu_GetProcessPriorityBoost *c = (struct qemu_GetProcessPriorityBoost *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessPriorityBoost(QEMU_G2H(c->hprocess), QEMU_G2H(c->pDisablePriorityBoost));
}

#endif

struct qemu_SetProcessPriorityBoost
{
    struct qemu_syscall super;
    uint64_t hprocess;
    uint64_t disableboost;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetProcessPriorityBoost(HANDLE hprocess,BOOL disableboost)
{
    struct qemu_SetProcessPriorityBoost call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSPRIORITYBOOST);
    call.hprocess = (uint64_t)hprocess;
    call.disableboost = (uint64_t)disableboost;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessPriorityBoost(struct qemu_syscall *call)
{
    struct qemu_SetProcessPriorityBoost *c = (struct qemu_SetProcessPriorityBoost *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetProcessPriorityBoost(QEMU_G2H(c->hprocess), c->disableboost);
}

#endif

struct qemu_ReadProcessMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t buffer;
    uint64_t size;
    uint64_t bytes_read;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadProcessMemory(HANDLE process, LPCVOID addr, LPVOID buffer, SIZE_T size, SIZE_T *bytes_read)
{
    struct qemu_ReadProcessMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READPROCESSMEMORY);
    call.process = (uint64_t)process;
    call.addr = (uint64_t)addr;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;
    call.bytes_read = (uint64_t)bytes_read;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadProcessMemory(struct qemu_syscall *call)
{
    struct qemu_ReadProcessMemory *c = (struct qemu_ReadProcessMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadProcessMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->bytes_read));
}

#endif

struct qemu_WriteProcessMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t buffer;
    uint64_t size;
    uint64_t bytes_written;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WriteProcessMemory(HANDLE process, LPVOID addr, LPCVOID buffer, SIZE_T size, SIZE_T *bytes_written)
{
    struct qemu_WriteProcessMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPROCESSMEMORY);
    call.process = (uint64_t)process;
    call.addr = (uint64_t)addr;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;
    call.bytes_written = (uint64_t)bytes_written;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteProcessMemory(struct qemu_syscall *call)
{
    struct qemu_WriteProcessMemory *c = (struct qemu_WriteProcessMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteProcessMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->bytes_written));
}

#endif

struct qemu_FlushInstructionCache
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t lpBaseAddress;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize)
{
    struct qemu_FlushInstructionCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHINSTRUCTIONCACHE);
    call.hProcess = (uint64_t)hProcess;
    call.lpBaseAddress = (uint64_t)lpBaseAddress;
    call.dwSize = (uint64_t)dwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlushInstructionCache(struct qemu_syscall *call)
{
    struct qemu_FlushInstructionCache *c = (struct qemu_FlushInstructionCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FlushInstructionCache(QEMU_G2H(c->hProcess), QEMU_G2H(c->lpBaseAddress), c->dwSize);
}

#endif

struct qemu_GetProcessIoCounters
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t ioc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessIoCounters(HANDLE hProcess, PIO_COUNTERS ioc)
{
    struct qemu_GetProcessIoCounters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSIOCOUNTERS);
    call.hProcess = (uint64_t)hProcess;
    call.ioc = (uint64_t)ioc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessIoCounters(struct qemu_syscall *call)
{
    struct qemu_GetProcessIoCounters *c = (struct qemu_GetProcessIoCounters *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessIoCounters(QEMU_G2H(c->hProcess), QEMU_G2H(c->ioc));
}

#endif

struct qemu_GetProcessHandleCount
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t cnt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessHandleCount(HANDLE hProcess, DWORD *cnt)
{
    struct qemu_GetProcessHandleCount call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSHANDLECOUNT);
    call.hProcess = (uint64_t)hProcess;
    call.cnt = (uint64_t)cnt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetProcessHandleCount to Wine headers? */
extern BOOL WINAPI GetProcessHandleCount(HANDLE hProcess, DWORD *cnt);
void qemu_GetProcessHandleCount(struct qemu_syscall *call)
{
    struct qemu_GetProcessHandleCount *c = (struct qemu_GetProcessHandleCount *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessHandleCount(QEMU_G2H(c->hProcess), QEMU_G2H(c->cnt));
}

#endif

struct qemu_QueryFullProcessImageNameA
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t dwFlags;
    uint64_t lpExeName;
    uint64_t pdwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryFullProcessImageNameA(HANDLE hProcess, DWORD dwFlags, LPSTR lpExeName, PDWORD pdwSize)
{
    struct qemu_QueryFullProcessImageNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYFULLPROCESSIMAGENAMEA);
    call.hProcess = (uint64_t)hProcess;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpExeName = (uint64_t)lpExeName;
    call.pdwSize = (uint64_t)pdwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryFullProcessImageNameA(struct qemu_syscall *call)
{
    struct qemu_QueryFullProcessImageNameA *c = (struct qemu_QueryFullProcessImageNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryFullProcessImageNameA(QEMU_G2H(c->hProcess), c->dwFlags, QEMU_G2H(c->lpExeName), QEMU_G2H(c->pdwSize));
}

#endif

struct qemu_QueryFullProcessImageNameW
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t dwFlags;
    uint64_t lpExeName;
    uint64_t pdwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryFullProcessImageNameW(HANDLE hProcess, DWORD dwFlags, LPWSTR lpExeName, PDWORD pdwSize)
{
    struct qemu_QueryFullProcessImageNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYFULLPROCESSIMAGENAMEW);
    call.hProcess = (uint64_t)hProcess;
    call.dwFlags = (uint64_t)dwFlags;
    call.lpExeName = (uint64_t)lpExeName;
    call.pdwSize = (uint64_t)pdwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryFullProcessImageNameW(struct qemu_syscall *call)
{
    struct qemu_QueryFullProcessImageNameW *c = (struct qemu_QueryFullProcessImageNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryFullProcessImageNameW(QEMU_G2H(c->hProcess), c->dwFlags, QEMU_G2H(c->lpExeName), QEMU_G2H(c->pdwSize));
}

#endif

struct qemu_K32GetProcessImageFileNameA
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t file;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetProcessImageFileNameA(HANDLE process, LPSTR file, DWORD size)
{
    struct qemu_K32GetProcessImageFileNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETPROCESSIMAGEFILENAMEA);
    call.process = (uint64_t)process;
    call.file = (uint64_t)file;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetProcessImageFileNameA(struct qemu_syscall *call)
{
    struct qemu_K32GetProcessImageFileNameA *c = (struct qemu_K32GetProcessImageFileNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetProcessImageFileNameA(QEMU_G2H(c->process), QEMU_G2H(c->file), c->size);
}

#endif

struct qemu_K32GetProcessImageFileNameW
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t file;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI K32GetProcessImageFileNameW(HANDLE process, LPWSTR file, DWORD size)
{
    struct qemu_K32GetProcessImageFileNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETPROCESSIMAGEFILENAMEW);
    call.process = (uint64_t)process;
    call.file = (uint64_t)file;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetProcessImageFileNameW(struct qemu_syscall *call)
{
    struct qemu_K32GetProcessImageFileNameW *c = (struct qemu_K32GetProcessImageFileNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetProcessImageFileNameW(QEMU_G2H(c->process), QEMU_G2H(c->file), c->size);
}

#endif

struct qemu_K32EnumProcesses
{
    struct qemu_syscall super;
    uint64_t lpdwProcessIDs;
    uint64_t cb;
    uint64_t lpcbUsed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32EnumProcesses(DWORD *lpdwProcessIDs, DWORD cb, DWORD *lpcbUsed)
{
    struct qemu_K32EnumProcesses call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32ENUMPROCESSES);
    call.lpdwProcessIDs = (uint64_t)lpdwProcessIDs;
    call.cb = (uint64_t)cb;
    call.lpcbUsed = (uint64_t)lpcbUsed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32EnumProcesses(struct qemu_syscall *call)
{
    struct qemu_K32EnumProcesses *c = (struct qemu_K32EnumProcesses *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32EnumProcesses(QEMU_G2H(c->lpdwProcessIDs), c->cb, QEMU_G2H(c->lpcbUsed));
}

#endif

struct qemu_K32QueryWorkingSet
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32QueryWorkingSet(HANDLE process, LPVOID buffer, DWORD size)
{
    struct qemu_K32QueryWorkingSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32QUERYWORKINGSET);
    call.process = (uint64_t)process;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32QueryWorkingSet(struct qemu_syscall *call)
{
    struct qemu_K32QueryWorkingSet *c = (struct qemu_K32QueryWorkingSet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32QueryWorkingSet(QEMU_G2H(c->process), QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_K32QueryWorkingSetEx
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32QueryWorkingSetEx(HANDLE process, LPVOID buffer, DWORD size)
{
    struct qemu_K32QueryWorkingSetEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32QUERYWORKINGSETEX);
    call.process = (uint64_t)process;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32QueryWorkingSetEx(struct qemu_syscall *call)
{
    struct qemu_K32QueryWorkingSetEx *c = (struct qemu_K32QueryWorkingSetEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32QueryWorkingSetEx(QEMU_G2H(c->process), QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_K32GetProcessMemoryInfo
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t pmc;
    uint64_t cb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI K32GetProcessMemoryInfo(HANDLE process, PPROCESS_MEMORY_COUNTERS pmc, DWORD cb)
{
    struct qemu_K32GetProcessMemoryInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_K32GETPROCESSMEMORYINFO);
    call.process = (uint64_t)process;
    call.pmc = (uint64_t)pmc;
    call.cb = (uint64_t)cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_K32GetProcessMemoryInfo(struct qemu_syscall *call)
{
    struct qemu_K32GetProcessMemoryInfo *c = (struct qemu_K32GetProcessMemoryInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = K32GetProcessMemoryInfo(QEMU_G2H(c->process), QEMU_G2H(c->pmc), c->cb);
}

#endif

struct qemu_ProcessIdToSessionId
{
    struct qemu_syscall super;
    uint64_t procid;
    uint64_t sessionid_ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ProcessIdToSessionId(DWORD procid, DWORD *sessionid_ptr)
{
    struct qemu_ProcessIdToSessionId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROCESSIDTOSESSIONID);
    call.procid = (uint64_t)procid;
    call.sessionid_ptr = (uint64_t)sessionid_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ProcessIdToSessionId(struct qemu_syscall *call)
{
    struct qemu_ProcessIdToSessionId *c = (struct qemu_ProcessIdToSessionId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ProcessIdToSessionId(c->procid, QEMU_G2H(c->sessionid_ptr));
}

#endif

struct qemu_RegisterServiceProcess
{
    struct qemu_syscall super;
    uint64_t dwProcessId;
    uint64_t dwType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RegisterServiceProcess(DWORD dwProcessId, DWORD dwType)
{
    struct qemu_RegisterServiceProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSERVICEPROCESS);
    call.dwProcessId = (uint64_t)dwProcessId;
    call.dwType = (uint64_t)dwType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterServiceProcess to Wine headers? */
extern DWORD WINAPI RegisterServiceProcess(DWORD dwProcessId, DWORD dwType);
void qemu_RegisterServiceProcess(struct qemu_syscall *call)
{
    struct qemu_RegisterServiceProcess *c = (struct qemu_RegisterServiceProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterServiceProcess(c->dwProcessId, c->dwType);
}

#endif

struct qemu_IsWow64Process
{
    struct qemu_syscall super;
    uint64_t hProcess;
    uint64_t Wow64Process;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsWow64Process(HANDLE hProcess, PBOOL Wow64Process)
{
    struct qemu_IsWow64Process call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWOW64PROCESS);
    call.hProcess = (uint64_t)hProcess;
    call.Wow64Process = (uint64_t)Wow64Process;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWow64Process(struct qemu_syscall *call)
{
    struct qemu_IsWow64Process *c = (struct qemu_IsWow64Process *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsWow64Process(QEMU_G2H(c->hProcess), QEMU_G2H(c->Wow64Process));
}

#endif

struct qemu_GetCurrentProcess
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetCurrentProcess(void)
{
    struct qemu_GetCurrentProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPROCESS);

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_GetCurrentProcess(struct qemu_syscall *call)
{
    struct qemu_GetCurrentProcess *c = (struct qemu_GetCurrentProcess *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetCurrentProcess();
}

#endif

struct qemu_GetLogicalProcessorInformation
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t pBufLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetLogicalProcessorInformation(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer, PDWORD pBufLen)
{
    struct qemu_GetLogicalProcessorInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGICALPROCESSORINFORMATION);
    call.buffer = (uint64_t)buffer;
    call.pBufLen = (uint64_t)pBufLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogicalProcessorInformation(struct qemu_syscall *call)
{
    struct qemu_GetLogicalProcessorInformation *c = (struct qemu_GetLogicalProcessorInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLogicalProcessorInformation(QEMU_G2H(c->buffer), QEMU_G2H(c->pBufLen));
}

#endif

struct qemu_GetLogicalProcessorInformationEx
{
    struct qemu_syscall super;
    uint64_t relationship;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetLogicalProcessorInformationEx(LOGICAL_PROCESSOR_RELATIONSHIP relationship, SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *buffer, DWORD *len)
{
    struct qemu_GetLogicalProcessorInformationEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGICALPROCESSORINFORMATIONEX);
    call.relationship = (uint64_t)relationship;
    call.buffer = (uint64_t)buffer;
    call.len = (uint64_t)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogicalProcessorInformationEx(struct qemu_syscall *call)
{
    struct qemu_GetLogicalProcessorInformationEx *c = (struct qemu_GetLogicalProcessorInformationEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLogicalProcessorInformationEx(c->relationship, QEMU_G2H(c->buffer), QEMU_G2H(c->len));
}

#endif

struct qemu_CmdBatNotification
{
    struct qemu_syscall super;
    uint64_t bBatchRunning;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CmdBatNotification(BOOL bBatchRunning)
{
    struct qemu_CmdBatNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CMDBATNOTIFICATION);
    call.bBatchRunning = (uint64_t)bBatchRunning;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CmdBatNotification to Wine headers? */
extern BOOL WINAPI CmdBatNotification(BOOL bBatchRunning);
void qemu_CmdBatNotification(struct qemu_syscall *call)
{
    struct qemu_CmdBatNotification *c = (struct qemu_CmdBatNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CmdBatNotification(c->bBatchRunning);
}

#endif

struct qemu_RegisterApplicationRestart
{
    struct qemu_syscall super;
    uint64_t pwzCommandLine;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegisterApplicationRestart(PCWSTR pwzCommandLine, DWORD dwFlags)
{
    struct qemu_RegisterApplicationRestart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERAPPLICATIONRESTART);
    call.pwzCommandLine = (uint64_t)pwzCommandLine;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterApplicationRestart to Wine headers? */
extern HRESULT WINAPI RegisterApplicationRestart(PCWSTR pwzCommandLine, DWORD dwFlags);
void qemu_RegisterApplicationRestart(struct qemu_syscall *call)
{
    struct qemu_RegisterApplicationRestart *c = (struct qemu_RegisterApplicationRestart *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterApplicationRestart(QEMU_G2H(c->pwzCommandLine), c->dwFlags);
}

#endif

struct qemu_WTSGetActiveConsoleSessionId
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WTSGetActiveConsoleSessionId(void)
{
    struct qemu_WTSGetActiveConsoleSessionId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WTSGETACTIVECONSOLESESSIONID);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WTSGetActiveConsoleSessionId(struct qemu_syscall *call)
{
    struct qemu_WTSGetActiveConsoleSessionId *c = (struct qemu_WTSGetActiveConsoleSessionId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WTSGetActiveConsoleSessionId();
}

#endif

struct qemu_GetSystemDEPPolicy
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DEP_SYSTEM_POLICY_TYPE WINAPI GetSystemDEPPolicy(void)
{
    struct qemu_GetSystemDEPPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMDEPPOLICY);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetSystemDEPPolicy to Wine headers? */
extern DEP_SYSTEM_POLICY_TYPE WINAPI GetSystemDEPPolicy(void);
void qemu_GetSystemDEPPolicy(struct qemu_syscall *call)
{
    struct qemu_GetSystemDEPPolicy *c = (struct qemu_GetSystemDEPPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemDEPPolicy();
}

#endif

struct qemu_SetProcessDEPPolicy
{
    struct qemu_syscall super;
    uint64_t newDEP;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetProcessDEPPolicy(DWORD newDEP)
{
    struct qemu_SetProcessDEPPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSDEPPOLICY);
    call.newDEP = (uint64_t)newDEP;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetProcessDEPPolicy to Wine headers? */
extern BOOL WINAPI SetProcessDEPPolicy(DWORD newDEP);
void qemu_SetProcessDEPPolicy(struct qemu_syscall *call)
{
    struct qemu_SetProcessDEPPolicy *c = (struct qemu_SetProcessDEPPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetProcessDEPPolicy(c->newDEP);
}

#endif

struct qemu_ApplicationRecoveryFinished
{
    struct qemu_syscall super;
    uint64_t success;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI ApplicationRecoveryFinished(BOOL success)
{
    struct qemu_ApplicationRecoveryFinished call;
    call.super.id = QEMU_SYSCALL_ID(CALL_APPLICATIONRECOVERYFINISHED);
    call.success = (uint64_t)success;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add ApplicationRecoveryFinished to Wine headers? */
extern VOID WINAPI ApplicationRecoveryFinished(BOOL success);
void qemu_ApplicationRecoveryFinished(struct qemu_syscall *call)
{
    struct qemu_ApplicationRecoveryFinished *c = (struct qemu_ApplicationRecoveryFinished *)call;
    WINE_FIXME("Unverified!\n");
    ApplicationRecoveryFinished(c->success);
}

#endif

struct qemu_ApplicationRecoveryInProgress
{
    struct qemu_syscall super;
    uint64_t canceled;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ApplicationRecoveryInProgress(PBOOL canceled)
{
    struct qemu_ApplicationRecoveryInProgress call;
    call.super.id = QEMU_SYSCALL_ID(CALL_APPLICATIONRECOVERYINPROGRESS);
    call.canceled = (uint64_t)canceled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ApplicationRecoveryInProgress to Wine headers? */
extern HRESULT WINAPI ApplicationRecoveryInProgress(PBOOL canceled);
void qemu_ApplicationRecoveryInProgress(struct qemu_syscall *call)
{
    struct qemu_ApplicationRecoveryInProgress *c = (struct qemu_ApplicationRecoveryInProgress *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ApplicationRecoveryInProgress(QEMU_G2H(c->canceled));
}

#endif

struct qemu_RegisterApplicationRecoveryCallback
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t param;
    uint64_t pingint;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI RegisterApplicationRecoveryCallback(APPLICATION_RECOVERY_CALLBACK callback, PVOID param, DWORD pingint, DWORD flags)
{
    struct qemu_RegisterApplicationRecoveryCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERAPPLICATIONRECOVERYCALLBACK);
    call.callback = (uint64_t)callback;
    call.param = (uint64_t)param;
    call.pingint = (uint64_t)pingint;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterApplicationRecoveryCallback to Wine headers? */
extern HRESULT WINAPI RegisterApplicationRecoveryCallback(APPLICATION_RECOVERY_CALLBACK callback, PVOID param, DWORD pingint, DWORD flags);
void qemu_RegisterApplicationRecoveryCallback(struct qemu_syscall *call)
{
    struct qemu_RegisterApplicationRecoveryCallback *c = (struct qemu_RegisterApplicationRecoveryCallback *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterApplicationRecoveryCallback(QEMU_G2H(c->callback), QEMU_G2H(c->param), c->pingint, c->flags);
}

#endif

struct qemu_GetNumaHighestNodeNumber
{
    struct qemu_syscall super;
    uint64_t highestnode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumaHighestNodeNumber(PULONG highestnode)
{
    struct qemu_GetNumaHighestNodeNumber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMAHIGHESTNODENUMBER);
    call.highestnode = (uint64_t)highestnode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNumaHighestNodeNumber to Wine headers? */
extern BOOL WINAPI GetNumaHighestNodeNumber(PULONG highestnode);
void qemu_GetNumaHighestNodeNumber(struct qemu_syscall *call)
{
    struct qemu_GetNumaHighestNodeNumber *c = (struct qemu_GetNumaHighestNodeNumber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumaHighestNodeNumber(QEMU_G2H(c->highestnode));
}

#endif

struct qemu_GetNumaNodeProcessorMask
{
    struct qemu_syscall super;
    uint64_t node;
    uint64_t mask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumaNodeProcessorMask(UCHAR node, PULONGLONG mask)
{
    struct qemu_GetNumaNodeProcessorMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMANODEPROCESSORMASK);
    call.node = (uint64_t)node;
    call.mask = (uint64_t)mask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNumaNodeProcessorMask to Wine headers? */
extern BOOL WINAPI GetNumaNodeProcessorMask(UCHAR node, PULONGLONG mask);
void qemu_GetNumaNodeProcessorMask(struct qemu_syscall *call)
{
    struct qemu_GetNumaNodeProcessorMask *c = (struct qemu_GetNumaNodeProcessorMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumaNodeProcessorMask(c->node, QEMU_G2H(c->mask));
}

#endif

struct qemu_GetNumaAvailableMemoryNode
{
    struct qemu_syscall super;
    uint64_t node;
    uint64_t available_bytes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumaAvailableMemoryNode(UCHAR node, PULONGLONG available_bytes)
{
    struct qemu_GetNumaAvailableMemoryNode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMAAVAILABLEMEMORYNODE);
    call.node = (uint64_t)node;
    call.available_bytes = (uint64_t)available_bytes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetNumaAvailableMemoryNode to Wine headers? */
extern BOOL WINAPI GetNumaAvailableMemoryNode(UCHAR node, PULONGLONG available_bytes);
void qemu_GetNumaAvailableMemoryNode(struct qemu_syscall *call)
{
    struct qemu_GetNumaAvailableMemoryNode *c = (struct qemu_GetNumaAvailableMemoryNode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumaAvailableMemoryNode(c->node, QEMU_G2H(c->available_bytes));
}

#endif

struct qemu_GetNumaProcessorNode
{
    struct qemu_syscall super;
    uint64_t processor;
    uint64_t node;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetNumaProcessorNode(UCHAR processor, PUCHAR node)
{
    struct qemu_GetNumaProcessorNode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNUMAPROCESSORNODE);
    call.processor = (uint64_t)processor;
    call.node = (uint64_t)node;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNumaProcessorNode(struct qemu_syscall *call)
{
    struct qemu_GetNumaProcessorNode *c = (struct qemu_GetNumaProcessorNode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNumaProcessorNode(c->processor, QEMU_G2H(c->node));
}

#endif

struct qemu_GetProcessDEPPolicy
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t flags;
    uint64_t permanent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessDEPPolicy(HANDLE process, LPDWORD flags, PBOOL permanent)
{
    struct qemu_GetProcessDEPPolicy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSDEPPOLICY);
    call.process = (uint64_t)process;
    call.flags = (uint64_t)flags;
    call.permanent = (uint64_t)permanent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetProcessDEPPolicy to Wine headers? */
extern BOOL WINAPI GetProcessDEPPolicy(HANDLE process, LPDWORD flags, PBOOL permanent);
void qemu_GetProcessDEPPolicy(struct qemu_syscall *call)
{
    struct qemu_GetProcessDEPPolicy *c = (struct qemu_GetProcessDEPPolicy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessDEPPolicy(QEMU_G2H(c->process), QEMU_G2H(c->flags), QEMU_G2H(c->permanent));
}

#endif

struct qemu_FlushProcessWriteBuffers
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI FlushProcessWriteBuffers(void)
{
    struct qemu_FlushProcessWriteBuffers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLUSHPROCESSWRITEBUFFERS);

    qemu_syscall(&call.super);
}

#else

void qemu_FlushProcessWriteBuffers(struct qemu_syscall *call)
{
    struct qemu_FlushProcessWriteBuffers *c = (struct qemu_FlushProcessWriteBuffers *)call;
    WINE_FIXME("Unverified!\n");
    FlushProcessWriteBuffers();
}

#endif

struct qemu_UnregisterApplicationRestart
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UnregisterApplicationRestart(void)
{
    struct qemu_UnregisterApplicationRestart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERAPPLICATIONRESTART);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterApplicationRestart(struct qemu_syscall *call)
{
    struct qemu_UnregisterApplicationRestart *c = (struct qemu_UnregisterApplicationRestart *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnregisterApplicationRestart();
}

#endif

struct qemu_GetSystemFirmwareTable
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t id;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetSystemFirmwareTable(DWORD provider, DWORD id, PVOID buffer, DWORD size)
{
    struct qemu_GetSystemFirmwareTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMFIRMWARETABLE);
    call.provider = (uint64_t)provider;
    call.id = (uint64_t)id;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemFirmwareTable(struct qemu_syscall *call)
{
    struct qemu_GetSystemFirmwareTable *c = (struct qemu_GetSystemFirmwareTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemFirmwareTable(c->provider, c->id, QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_InitializeProcThreadAttributeList
{
    struct qemu_syscall super;
    uint64_t list;
    uint64_t count;
    uint64_t flags;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitializeProcThreadAttributeList(struct _PROC_THREAD_ATTRIBUTE_LIST *list, DWORD count, DWORD flags, SIZE_T *size)
{
    struct qemu_InitializeProcThreadAttributeList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIALIZEPROCTHREADATTRIBUTELIST);
    call.list = (uint64_t)list;
    call.count = (uint64_t)count;
    call.flags = (uint64_t)flags;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitializeProcThreadAttributeList(struct qemu_syscall *call)
{
    struct qemu_InitializeProcThreadAttributeList *c = (struct qemu_InitializeProcThreadAttributeList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitializeProcThreadAttributeList(QEMU_G2H(c->list), c->count, c->flags, QEMU_G2H(c->size));
}

#endif

struct qemu_UpdateProcThreadAttribute
{
    struct qemu_syscall super;
    uint64_t list;
    uint64_t flags;
    uint64_t attr;
    uint64_t value;
    uint64_t size;
    uint64_t prev_ret;
    uint64_t size_ret;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UpdateProcThreadAttribute(struct _PROC_THREAD_ATTRIBUTE_LIST *list, DWORD flags, DWORD_PTR attr, void *value, SIZE_T size, void *prev_ret, SIZE_T *size_ret)
{
    struct qemu_UpdateProcThreadAttribute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATEPROCTHREADATTRIBUTE);
    call.list = (uint64_t)list;
    call.flags = (uint64_t)flags;
    call.attr = (uint64_t)attr;
    call.value = (uint64_t)value;
    call.size = (uint64_t)size;
    call.prev_ret = (uint64_t)prev_ret;
    call.size_ret = (uint64_t)size_ret;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateProcThreadAttribute(struct qemu_syscall *call)
{
    struct qemu_UpdateProcThreadAttribute *c = (struct qemu_UpdateProcThreadAttribute *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UpdateProcThreadAttribute(QEMU_G2H(c->list), c->flags, c->attr, QEMU_G2H(c->value), c->size, QEMU_G2H(c->prev_ret), QEMU_G2H(c->size_ret));
}

#endif

struct qemu_DeleteProcThreadAttributeList
{
    struct qemu_syscall super;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DeleteProcThreadAttributeList(struct _PROC_THREAD_ATTRIBUTE_LIST *list)
{
    struct qemu_DeleteProcThreadAttributeList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPROCTHREADATTRIBUTELIST);
    call.list = (uint64_t)list;

    qemu_syscall(&call.super);
}

#else

void qemu_DeleteProcThreadAttributeList(struct qemu_syscall *call)
{
    struct qemu_DeleteProcThreadAttributeList *c = (struct qemu_DeleteProcThreadAttributeList *)call;
    WINE_FIXME("Unverified!\n");
    DeleteProcThreadAttributeList(QEMU_G2H(c->list));
}

#endif

struct qemu_BaseFlushAppcompatCache
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BaseFlushAppcompatCache(void)
{
    struct qemu_BaseFlushAppcompatCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BASEFLUSHAPPCOMPATCACHE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add BaseFlushAppcompatCache to Wine headers? */
extern BOOL WINAPI BaseFlushAppcompatCache(void);
void qemu_BaseFlushAppcompatCache(struct qemu_syscall *call)
{
    struct qemu_BaseFlushAppcompatCache *c = (struct qemu_BaseFlushAppcompatCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BaseFlushAppcompatCache();
}

#endif

