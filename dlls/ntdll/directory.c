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

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_NtQueryDirectoryFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t event;
    uint64_t apc_routine;
    uint64_t apc_context;
    uint64_t io;
    uint64_t buffer;
    uint64_t length;
    uint64_t info_class;
    uint64_t single_entry;
    uint64_t mask;
    uint64_t restart_scan;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryDirectoryFile(HANDLE handle, HANDLE event, PIO_APC_ROUTINE apc_routine, PVOID apc_context, PIO_STATUS_BLOCK io, PVOID buffer, ULONG length, FILE_INFORMATION_CLASS info_class, BOOLEAN single_entry, PUNICODE_STRING mask, BOOLEAN restart_scan)
{
    struct qemu_NtQueryDirectoryFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYDIRECTORYFILE);
    call.handle = (ULONG_PTR)handle;
    call.event = (ULONG_PTR)event;
    call.apc_routine = (ULONG_PTR)apc_routine;
    call.apc_context = (ULONG_PTR)apc_context;
    call.io = (ULONG_PTR)io;
    call.buffer = (ULONG_PTR)buffer;
    call.length = length;
    call.info_class = info_class;
    call.single_entry = single_entry;
    call.mask = (ULONG_PTR)mask;
    call.restart_scan = restart_scan;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryDirectoryFile(struct qemu_syscall *call)
{
    struct qemu_NtQueryDirectoryFile *c = (struct qemu_NtQueryDirectoryFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryDirectoryFile(QEMU_G2H(c->handle), QEMU_G2H(c->event), QEMU_G2H(c->apc_routine), QEMU_G2H(c->apc_context), QEMU_G2H(c->io), QEMU_G2H(c->buffer), c->length, c->info_class, c->single_entry, QEMU_G2H(c->mask), c->restart_scan);
}

#endif

struct qemu_RtlWow64EnableFsRedirection
{
    struct qemu_syscall super;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlWow64EnableFsRedirection(BOOLEAN enable)
{
    struct qemu_RtlWow64EnableFsRedirection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWOW64ENABLEFSREDIRECTION);
    call.enable = enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlWow64EnableFsRedirection(struct qemu_syscall *call)
{
    struct qemu_RtlWow64EnableFsRedirection *c = (struct qemu_RtlWow64EnableFsRedirection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlWow64EnableFsRedirection(c->enable);
}

#endif

struct qemu_RtlWow64EnableFsRedirectionEx
{
    struct qemu_syscall super;
    uint64_t disable;
    uint64_t old_value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlWow64EnableFsRedirectionEx(ULONG disable, ULONG *old_value)
{
    struct qemu_RtlWow64EnableFsRedirectionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWOW64ENABLEFSREDIRECTIONEX);
    call.disable = disable;
    call.old_value = (ULONG_PTR)old_value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlWow64EnableFsRedirectionEx(struct qemu_syscall *call)
{
    struct qemu_RtlWow64EnableFsRedirectionEx *c = (struct qemu_RtlWow64EnableFsRedirectionEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlWow64EnableFsRedirectionEx(c->disable, QEMU_G2H(c->old_value));
}

#endif

struct qemu_RtlDoesFileExists_U
{
    struct qemu_syscall super;
    uint64_t file_name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlDoesFileExists_U(LPCWSTR file_name)
{
    struct qemu_RtlDoesFileExists_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOESFILEEXISTS_U);
    call.file_name = (ULONG_PTR)file_name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDoesFileExists_U(struct qemu_syscall *call)
{
    struct qemu_RtlDoesFileExists_U *c = (struct qemu_RtlDoesFileExists_U *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDoesFileExists_U(QEMU_G2H(c->file_name));
}

#endif

