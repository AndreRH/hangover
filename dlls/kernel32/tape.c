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


struct qemu_BackupRead
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buffer;
    uint64_t to_read;
    uint64_t read;
    uint64_t abort;
    uint64_t security;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupRead(HANDLE file, LPBYTE buffer, DWORD to_read, LPDWORD read, BOOL abort, BOOL security, LPVOID *context)
{
    struct qemu_BackupRead call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPREAD);
    call.file = (LONG_PTR)file;
    call.buffer = (ULONG_PTR)buffer;
    call.to_read = (ULONG_PTR)to_read;
    call.read = (ULONG_PTR)read;
    call.abort = (ULONG_PTR)abort;
    call.security = (ULONG_PTR)security;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupRead(struct qemu_syscall *call)
{
    struct qemu_BackupRead *c = (struct qemu_BackupRead *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BackupRead(QEMU_G2H(c->file), QEMU_G2H(c->buffer), c->to_read, QEMU_G2H(c->read), c->abort, c->security, QEMU_G2H(c->context));
}

#endif

struct qemu_BackupSeek
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t seek_low;
    uint64_t seek_high;
    uint64_t seeked_low;
    uint64_t seeked_high;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupSeek(HANDLE file, DWORD seek_low, DWORD seek_high, LPDWORD seeked_low, LPDWORD seeked_high, LPVOID *context)
{
    struct qemu_BackupSeek call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPSEEK);
    call.file = (LONG_PTR)file;
    call.seek_low = (ULONG_PTR)seek_low;
    call.seek_high = (ULONG_PTR)seek_high;
    call.seeked_low = (ULONG_PTR)seeked_low;
    call.seeked_high = (ULONG_PTR)seeked_high;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupSeek(struct qemu_syscall *call)
{
    struct qemu_BackupSeek *c = (struct qemu_BackupSeek *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BackupSeek(QEMU_G2H(c->file), c->seek_low, c->seek_high, QEMU_G2H(c->seeked_low), QEMU_G2H(c->seeked_high), QEMU_G2H(c->context));
}

#endif

struct qemu_BackupWrite
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t buffer;
    uint64_t to_write;
    uint64_t written;
    uint64_t abort;
    uint64_t security;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BackupWrite(HANDLE file, LPBYTE buffer, DWORD to_write, LPDWORD written, BOOL abort, BOOL security, LPVOID *context)
{
    struct qemu_BackupWrite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BACKUPWRITE);
    call.file = (LONG_PTR)file;
    call.buffer = (ULONG_PTR)buffer;
    call.to_write = (ULONG_PTR)to_write;
    call.written = (ULONG_PTR)written;
    call.abort = (ULONG_PTR)abort;
    call.security = (ULONG_PTR)security;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BackupWrite(struct qemu_syscall *call)
{
    struct qemu_BackupWrite *c = (struct qemu_BackupWrite *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BackupWrite(QEMU_G2H(c->file), QEMU_G2H(c->buffer), c->to_write, QEMU_G2H(c->written), c->abort, c->security, QEMU_G2H(c->context));
}

#endif

struct qemu_CreateTapePartition
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t method;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CreateTapePartition(HANDLE device, DWORD method, DWORD count, DWORD size)
{
    struct qemu_CreateTapePartition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATETAPEPARTITION);
    call.device = (LONG_PTR)device;
    call.method = (ULONG_PTR)method;
    call.count = (ULONG_PTR)count;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CreateTapePartition(struct qemu_syscall *call)
{
    struct qemu_CreateTapePartition *c = (struct qemu_CreateTapePartition *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CreateTapePartition(QEMU_G2H(c->device), c->method, c->count, c->size);
}

#endif

struct qemu_EraseTape
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t type;
    uint64_t immediate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EraseTape(HANDLE device, DWORD type, BOOL immediate)
{
    struct qemu_EraseTape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ERASETAPE);
    call.device = (LONG_PTR)device;
    call.type = (ULONG_PTR)type;
    call.immediate = (ULONG_PTR)immediate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EraseTape(struct qemu_syscall *call)
{
    struct qemu_EraseTape *c = (struct qemu_EraseTape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EraseTape(QEMU_G2H(c->device), c->type, c->immediate);
}

#endif

struct qemu_GetTapeParameters
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t operation;
    uint64_t size;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTapeParameters(HANDLE device, DWORD operation, LPDWORD size, LPVOID info)
{
    struct qemu_GetTapeParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTAPEPARAMETERS);
    call.device = (LONG_PTR)device;
    call.operation = (ULONG_PTR)operation;
    call.size = (ULONG_PTR)size;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTapeParameters(struct qemu_syscall *call)
{
    struct qemu_GetTapeParameters *c = (struct qemu_GetTapeParameters *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTapeParameters(QEMU_G2H(c->device), c->operation, QEMU_G2H(c->size), QEMU_G2H(c->info));
}

#endif

struct qemu_GetTapePosition
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t type;
    uint64_t partition;
    uint64_t offset_low;
    uint64_t offset_high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTapePosition(HANDLE device, DWORD type, LPDWORD partition, LPDWORD offset_low, LPDWORD offset_high)
{
    struct qemu_GetTapePosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTAPEPOSITION);
    call.device = (LONG_PTR)device;
    call.type = (ULONG_PTR)type;
    call.partition = (ULONG_PTR)partition;
    call.offset_low = (ULONG_PTR)offset_low;
    call.offset_high = (ULONG_PTR)offset_high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTapePosition(struct qemu_syscall *call)
{
    struct qemu_GetTapePosition *c = (struct qemu_GetTapePosition *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTapePosition(QEMU_G2H(c->device), c->type, QEMU_G2H(c->partition), QEMU_G2H(c->offset_low), QEMU_G2H(c->offset_high));
}

#endif

struct qemu_GetTapeStatus
{
    struct qemu_syscall super;
    uint64_t device;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetTapeStatus(HANDLE device)
{
    struct qemu_GetTapeStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTAPESTATUS);
    call.device = (LONG_PTR)device;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetTapeStatus(struct qemu_syscall *call)
{
    struct qemu_GetTapeStatus *c = (struct qemu_GetTapeStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetTapeStatus(QEMU_G2H(c->device));
}

#endif

struct qemu_PrepareTape
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t operation;
    uint64_t immediate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI PrepareTape(HANDLE device, DWORD operation, BOOL immediate)
{
    struct qemu_PrepareTape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PREPARETAPE);
    call.device = (LONG_PTR)device;
    call.operation = (ULONG_PTR)operation;
    call.immediate = (ULONG_PTR)immediate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrepareTape(struct qemu_syscall *call)
{
    struct qemu_PrepareTape *c = (struct qemu_PrepareTape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrepareTape(QEMU_G2H(c->device), c->operation, c->immediate);
}

#endif

struct qemu_SetTapeParameters
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t operation;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetTapeParameters(HANDLE device, DWORD operation, LPVOID info)
{
    struct qemu_SetTapeParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTAPEPARAMETERS);
    call.device = (LONG_PTR)device;
    call.operation = (ULONG_PTR)operation;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTapeParameters(struct qemu_syscall *call)
{
    struct qemu_SetTapeParameters *c = (struct qemu_SetTapeParameters *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetTapeParameters(QEMU_G2H(c->device), c->operation, QEMU_G2H(c->info));
}

#endif

struct qemu_SetTapePosition
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t method;
    uint64_t partition;
    uint64_t offset_low;
    uint64_t offset_high;
    uint64_t immediate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetTapePosition(HANDLE device, DWORD method, DWORD partition, DWORD offset_low, DWORD offset_high, BOOL immediate)
{
    struct qemu_SetTapePosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTAPEPOSITION);
    call.device = (LONG_PTR)device;
    call.method = (ULONG_PTR)method;
    call.partition = (ULONG_PTR)partition;
    call.offset_low = (ULONG_PTR)offset_low;
    call.offset_high = (ULONG_PTR)offset_high;
    call.immediate = (ULONG_PTR)immediate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetTapePosition(struct qemu_syscall *call)
{
    struct qemu_SetTapePosition *c = (struct qemu_SetTapePosition *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetTapePosition(QEMU_G2H(c->device), c->method, c->partition, c->offset_low, c->offset_high, c->immediate);
}

#endif

struct qemu_WriteTapemark
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t type;
    uint64_t count;
    uint64_t immediate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WriteTapemark(HANDLE device, DWORD type, DWORD count, BOOL immediate)
{
    struct qemu_WriteTapemark call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITETAPEMARK);
    call.device = (LONG_PTR)device;
    call.type = (ULONG_PTR)type;
    call.count = (ULONG_PTR)count;
    call.immediate = (ULONG_PTR)immediate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WriteTapemark(struct qemu_syscall *call)
{
    struct qemu_WriteTapemark *c = (struct qemu_WriteTapemark *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WriteTapemark(QEMU_G2H(c->device), c->type, c->count, c->immediate);
}

#endif

