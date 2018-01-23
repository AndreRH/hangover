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
#include "qemu_kernel32.h"

#ifdef QEMU_DLL_GUEST

#define EH_NONCONTINUABLE   0x01

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);

#endif

struct qemu_RaiseException
{
    struct qemu_syscall super;
    uint64_t code;
    uint64_t flags;
    uint64_t nbargs;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

void WINAPI kernel32_RaiseException(DWORD code, DWORD flags, DWORD nbargs, const ULONG_PTR *args)
{
    struct qemu_RaiseException call;
    EXCEPTION_RECORD record;
    call.super.id = QEMU_SYSCALL_ID(CALL_RAISEEXCEPTION);
    call.code = code;
    call.flags = flags;
    call.nbargs = nbargs;
    call.args = (ULONG_PTR)args;

    /* For logging. */
    qemu_syscall(&call.super);

    record.ExceptionCode    = code;
    record.ExceptionFlags   = flags & EH_NONCONTINUABLE;
    record.ExceptionRecord  = NULL;
    record.ExceptionAddress = kernel32_RaiseException;
    if (nbargs && args)
    {
        if (nbargs > EXCEPTION_MAXIMUM_PARAMETERS) nbargs = EXCEPTION_MAXIMUM_PARAMETERS;
        record.NumberParameters = nbargs;
        memcpy( record.ExceptionInformation, args, nbargs * sizeof(*args) );
    }
    else record.NumberParameters = 0;

    pRtlRaiseException( &record );
}

#else

void qemu_RaiseException(struct qemu_syscall *call)
{
    struct qemu_RaiseException *c = (struct qemu_RaiseException *)call;
    WINE_FIXME("\n");
}

#endif

struct qemu_UnhandledExceptionFilter
{
    struct qemu_syscall super;
    uint64_t epointers;
    uint64_t filter;
};

#ifdef QEMU_DLL_GUEST

static PTOP_LEVEL_EXCEPTION_FILTER top_filter;

LONG WINAPI kernel32_UnhandledExceptionFilter(PEXCEPTION_POINTERS epointers)
{
    struct qemu_UnhandledExceptionFilter call;

    /* For logging. */
    call.super.id = QEMU_SYSCALL_ID(CALL_UNHANDLEDEXCEPTIONFILTER);
    call.epointers = (ULONG_PTR)epointers;
    call.filter = (ULONG_PTR)top_filter;
    qemu_syscall(&call.super);

    if (top_filter)
    {
        LONG ret = top_filter(epointers);
        if (ret != EXCEPTION_CONTINUE_SEARCH) return ret;
    }

    /* FIXME: Check for debuggers. */

    return EXCEPTION_EXECUTE_HANDLER;
}

#else

void qemu_UnhandledExceptionFilter(struct qemu_syscall *call)
{
    struct qemu_UnhandledExceptionFilter *c = (struct qemu_UnhandledExceptionFilter *)call;
    WINE_TRACE("Application filter %p.\n", QEMU_G2H(c->filter));
}

#endif

struct qemu_SetUnhandledExceptionFilter
{
    struct qemu_syscall super;
    uint64_t filter;
    uint64_t old;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPTOP_LEVEL_EXCEPTION_FILTER WINAPI SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER filter)
{
    struct qemu_SetUnhandledExceptionFilter call;
    LPTOP_LEVEL_EXCEPTION_FILTER old = top_filter;

    call.super.id = QEMU_SYSCALL_ID(CALL_SETUNHANDLEDEXCEPTIONFILTER);
    call.filter = (ULONG_PTR)filter;
    call.old = (ULONG_PTR)old;

    /* For logging. */
    qemu_syscall(&call.super);

    top_filter = filter;
    return old;
}

#else

void qemu_SetUnhandledExceptionFilter(struct qemu_syscall *call)
{
    struct qemu_SetUnhandledExceptionFilter *c = (struct qemu_SetUnhandledExceptionFilter *)call;
    WINE_TRACE("Setting filter %p, old %p.\n", QEMU_G2H(c->filter), QEMU_G2H(c->old));
}

#endif

struct qemu_FatalAppExitA
{
    struct qemu_syscall super;
    uint64_t action;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FatalAppExitA(UINT action, LPCSTR str)
{
    struct qemu_FatalAppExitA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FATALAPPEXITA);
    call.action = action;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_FatalAppExitA(struct qemu_syscall *call)
{
    struct qemu_FatalAppExitA *c = (struct qemu_FatalAppExitA *)call;
    WINE_FIXME("Unverified!\n");
    FatalAppExitA(c->action, QEMU_G2H(c->str));
}

#endif

struct qemu_FatalAppExitW
{
    struct qemu_syscall super;
    uint64_t action;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FatalAppExitW(UINT action, LPCWSTR str)
{
    struct qemu_FatalAppExitW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FATALAPPEXITW);
    call.action = action;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_FatalAppExitW(struct qemu_syscall *call)
{
    struct qemu_FatalAppExitW *c = (struct qemu_FatalAppExitW *)call;
    WINE_FIXME("Unverified!\n");
    FatalAppExitW(c->action, QEMU_G2H(c->str));
}

#endif

struct qemu_FatalExit
{
    struct qemu_syscall super;
    uint64_t ExitCode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FatalExit(int ExitCode)
{
    struct qemu_FatalExit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FATALEXIT);
    call.ExitCode = ExitCode;

    qemu_syscall(&call.super);
}

#else

void qemu_FatalExit(struct qemu_syscall *call)
{
    struct qemu_FatalExit *c = (struct qemu_FatalExit *)call;
    WINE_FIXME("Unverified!\n");
    FatalExit(c->ExitCode);
}

#endif
