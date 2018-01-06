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
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_WaitForDebugEvent
{
    struct qemu_syscall super;
    uint64_t event;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WaitForDebugEvent(LPDEBUG_EVENT event, DWORD timeout)
{
    struct qemu_WaitForDebugEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITFORDEBUGEVENT);
    call.event = (ULONG_PTR)event;
    call.timeout = timeout;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_WaitForDebugEvent(struct qemu_syscall *call)
{
    struct qemu_WaitForDebugEvent *c = (struct qemu_WaitForDebugEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(WaitForDebugEvent(QEMU_G2H(c->event), c->timeout));
}

#endif

struct qemu_ContinueDebugEvent
{
    struct qemu_syscall super;
    uint64_t pid;
    uint64_t tid;
    uint64_t status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ContinueDebugEvent(DWORD pid, DWORD tid, DWORD status)
{
    struct qemu_ContinueDebugEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTINUEDEBUGEVENT);
    call.pid = pid;
    call.tid = tid;
    call.status = status;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_ContinueDebugEvent(struct qemu_syscall *call)
{
    struct qemu_ContinueDebugEvent *c = (struct qemu_ContinueDebugEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(ContinueDebugEvent(c->pid, c->tid, c->status));
}

#endif

struct qemu_DebugActiveProcess
{
    struct qemu_syscall super;
    uint64_t pid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DebugActiveProcess(DWORD pid)
{
    struct qemu_DebugActiveProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEBUGACTIVEPROCESS);
    call.pid = pid;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_DebugActiveProcess(struct qemu_syscall *call)
{
    struct qemu_DebugActiveProcess *c = (struct qemu_DebugActiveProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DebugActiveProcess(c->pid);
}

#endif

struct qemu_DebugActiveProcessStop
{
    struct qemu_syscall super;
    uint64_t pid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DebugActiveProcessStop(DWORD pid)
{
    struct qemu_DebugActiveProcessStop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEBUGACTIVEPROCESSSTOP);
    call.pid = pid;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_DebugActiveProcessStop(struct qemu_syscall *call)
{
    struct qemu_DebugActiveProcessStop *c = (struct qemu_DebugActiveProcessStop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DebugActiveProcessStop(c->pid);
}

#endif

struct qemu_OutputDebugStringA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI OutputDebugStringA(LPCSTR str)
{
    struct qemu_OutputDebugStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OUTPUTDEBUGSTRINGA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_OutputDebugStringA(struct qemu_syscall *call)
{
    struct qemu_OutputDebugStringA *c = (struct qemu_OutputDebugStringA *)call;
    WINE_FIXME("Unverified!\n");
    OutputDebugStringA(QEMU_G2H(c->str));
}

#endif

struct qemu_OutputDebugStringW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI OutputDebugStringW(LPCWSTR str)
{
    struct qemu_OutputDebugStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OUTPUTDEBUGSTRINGW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_OutputDebugStringW(struct qemu_syscall *call)
{
    struct qemu_OutputDebugStringW *c = (struct qemu_OutputDebugStringW *)call;
    WINE_TRACE("\n");
    OutputDebugStringW(QEMU_G2H(c->str));
}

#endif

struct qemu_DebugBreak
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DebugBreak(void)
{
    struct qemu_DebugBreak call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEBUGBREAK);

    qemu_syscall(&call.super);
}

#else

void qemu_DebugBreak(struct qemu_syscall *call)
{
    struct qemu_DebugBreak *c = (struct qemu_DebugBreak *)call;
    WINE_FIXME("Unverified!\n");
    DebugBreak();
}

#endif

struct qemu_DebugBreakProcess
{
    struct qemu_syscall super;
    uint64_t hProc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DebugBreakProcess(HANDLE hProc)
{
    struct qemu_DebugBreakProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEBUGBREAKPROCESS);
    call.hProc = (LONG_PTR)hProc;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_DebugBreakProcess(struct qemu_syscall *call)
{
    struct qemu_DebugBreakProcess *c = (struct qemu_DebugBreakProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DebugBreakProcess(QEMU_G2H(c->hProc));
}

#endif

struct qemu_IsDebuggerPresent
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsDebuggerPresent(void)
{
    struct qemu_IsDebuggerPresent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDEBUGGERPRESENT);

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_IsDebuggerPresent(struct qemu_syscall *call)
{
    struct qemu_IsDebuggerPresent *c = (struct qemu_IsDebuggerPresent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsDebuggerPresent();
}

#endif

struct qemu_CheckRemoteDebuggerPresent
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t DebuggerPresent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CheckRemoteDebuggerPresent(HANDLE process, PBOOL DebuggerPresent)
{
    struct qemu_CheckRemoteDebuggerPresent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKREMOTEDEBUGGERPRESENT);
    call.process = (LONG_PTR)process;
    call.DebuggerPresent = (ULONG_PTR)DebuggerPresent;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_CheckRemoteDebuggerPresent(struct qemu_syscall *call)
{
    struct qemu_CheckRemoteDebuggerPresent *c = (struct qemu_CheckRemoteDebuggerPresent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckRemoteDebuggerPresent(QEMU_G2H(c->process), QEMU_G2H(c->DebuggerPresent));
}

#endif

struct qemu_DebugSetProcessKillOnExit
{
    struct qemu_syscall super;
    uint64_t kill;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DebugSetProcessKillOnExit(BOOL kill)
{
    struct qemu_DebugSetProcessKillOnExit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEBUGSETPROCESSKILLONEXIT);
    call.kill = kill;

    qemu_syscall(&call.super);

    return (BOOL)call.super.iret;
}

#else

void qemu_DebugSetProcessKillOnExit(struct qemu_syscall *call)
{
    struct qemu_DebugSetProcessKillOnExit *c = (struct qemu_DebugSetProcessKillOnExit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DebugSetProcessKillOnExit(c->kill);
}

#endif

