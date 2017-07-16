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
#include <winternl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif

struct qemu_GetEnvironmentStringsA
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

/* The headers have a #define that maps GetEnvironmentStringsA to GetEnvironmentStrings. */
LPSTR WINAPI qemu_GetEnvironmentStringsA(void)
{
    struct qemu_GetEnvironmentStringsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETENVIRONMENTSTRINGSA);

    qemu_syscall(&call.super);

    return (LPSTR)call.super.iret;
}

#else

void qemu_GetEnvironmentStringsA(struct qemu_syscall *call)
{
    struct qemu_GetEnvironmentStringsA *c = (struct qemu_GetEnvironmentStringsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetEnvironmentStringsA();
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI CHAR WINAPI *GetCommandLineA(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCOMMANDLINEA);

    qemu_syscall(&call);

    return (CHAR *)call.iret;
}

#else

void qemu_GetCommandLineA(struct qemu_syscall *c)
{
    const TEB *teb;
    static char *cmdlineA;
    WINE_TRACE("\n");

    if (!cmdlineA) /* make an ansi version if we don't have it. Take from Wine. */
    {
        ANSI_STRING     ansi;

        teb = qemu_ops->qemu_getTEB();
        cmdlineA = !RtlUnicodeStringToAnsiString(&ansi, &teb->Peb->ProcessParameters->CommandLine, TRUE) ?
            ansi.Buffer : NULL;
    }

    c->iret = QEMU_H2G(cmdlineA);
}

#endif

#ifdef QEMU_DLL_GUEST

/* This just reads the PEB, so we should be able to do it without calling
 * the host, but Mingw's headers don't properly declare the PEB. So for now
 * call out of the VM to have access to Wine's winternl.h. */
WINBASEAPI WCHAR WINAPI *GetCommandLineW(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETCOMMANDLINEW);

    qemu_syscall(&call);

    return (WCHAR *)call.iret;
}

#else

void qemu_GetCommandLineW(struct qemu_syscall *c)
{
    const TEB *teb = qemu_ops->qemu_getTEB();
    WINE_TRACE("\n");
    c->iret = QEMU_H2G(teb->Peb->ProcessParameters->CommandLine.Buffer);
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI GetProcessHeap()
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GETPROCESSHEAP);

    qemu_syscall(&call);

    return (HANDLE)call.iret;
}

#else

void qemu_GetProcessHeap(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    c->iret = (uint64_t)GetProcessHeap();
}

#endif
