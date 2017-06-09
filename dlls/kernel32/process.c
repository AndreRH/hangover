/*
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

struct qemu_CloseHandle
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI CloseHandle(HANDLE handle)
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

struct qemu_ExitProcess
{
    struct qemu_syscall super;
    uint64_t exitcode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DECLSPEC_NORETURN void WINAPI ExitProcess(UINT exitcode)
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

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetCurrentProcess(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPROCESS);
    qemu_syscall(&call);
    return (HANDLE)call.iret;
}

#else

void qemu_GetCurrentProcess(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = (uint64_t)GetCurrentProcess();
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCurrentProcessId(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCURRENTPROCESSID);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetCurrentProcessId(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetCurrentProcessId();
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetCurrentThreadId(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCURRENTTHREADID);
    qemu_syscall(&call);
    return call.iret;
}

#else

void qemu_GetCurrentThreadId(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
    call->iret = GetCurrentThreadId();
}

#endif

struct qemu_TerminateProcess
{
    struct qemu_syscall super;
    uint64_t process, exitcode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TerminateProcess(HANDLE process, UINT exitcode)
{
    struct qemu_TerminateProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TERMINATEPROCESS);
    call.process = (uint64_t)process;
    call.exitcode = exitcode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TerminateProcess(struct qemu_syscall *call)
{
    struct qemu_TerminateProcess *c = (struct qemu_TerminateProcess *)call;
    WINE_TRACE("\n");
    c->super.iret = TerminateProcess((HANDLE)c->process, c->exitcode);
}

#endif

struct qemu_TlsGetValue
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI *TlsGetValue(DWORD index)
{
    struct qemu_TlsGetValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TLSGETVALUE);
    call.index = index;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_TlsGetValue(struct qemu_syscall *call)
{
    struct qemu_TlsGetValue *c = (struct qemu_TlsGetValue *)call;
    DWORD index = c->index;
    WINE_FIXME("(%u) This is most likely wrong\n", index);
    
    /* This should read the TLS entry from the guest TEB instead of
     * reading the host TLS entries. */
    c->super.iret = QEMU_H2G(TlsGetValue(index));
}

#endif
