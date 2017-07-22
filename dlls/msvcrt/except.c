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
#include <signal.h>
#include <setjmp.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

EXCEPTION_DISPOSITION CDECL __CxxFrameHandler(EXCEPTION_RECORD *rec, ULONG64 frame,
        CONTEXT *context, DISPATCHER_CONTEXT *dispatch)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___CXXFRAMEHANDLER);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu___cxxframehandler(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

void __cdecl MSVCRT__setjmp(jmp_buf buf, void *ctx)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__SETJMP);

    qemu_syscall(&call);
}

#else

void qemu__setjmp(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

int __cdecl MSVCRT__XcptFilter(unsigned long exception_num, struct _EXCEPTION_POINTERS *ptr)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__XCPTFILTER);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu__xcptfilter(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

void __cdecl MSVCRT_longjmp(jmp_buf jmp, int retval)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_LONGJMP);

    qemu_syscall(&call);
}

#else

void qemu_longjmp(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

__p_sig_fn_t CDECL MSVCRT_signal(int sig, __p_sig_fn_t func)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_SIGNAL);

    qemu_syscall(&call);

    return NULL;
}

#else

void qemu_signal(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_raise(int signum)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_RAISE);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu_raise(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif
