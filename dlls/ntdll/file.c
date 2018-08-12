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

#include "thunk/qemu_winternl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

static struct IOSB_data *alloc_io_wrapper(struct qemu_IO_STATUS_BLOCK *guest)
{
    OBJECT_ATTRIBUTES attr;
    struct IOSB_data *ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        WINE_ERR("Out of memory\n");

    ret->guest_iosb = guest;
    IO_STATUS_BLOCK_g2h(&ret->iosb, guest);

    ret->host_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    if (!ret)
        WINE_ERR("Out of memory\n");

    return ret;
}

DWORD CALLBACK iosb32_wait_func(void *ctx)
{
    struct IOSB_data *iosb = ctx;

    WINE_TRACE("Work item started %p\n", iosb);

    /* FIXME: This proxy event breaks the kernel32 pipe.c tests because ReadFile (on a pipe)
     * returns to the application before the WriteFile event that was previously waiting gets
     * signalled. Either this is just an unlucky race, or there is a guarantee that IO ops
     * that depend on each other finish in order. The WriteFile is started before the ReadFile,
     * but the ReadFile ends up finishing first due to the delay here. */
    WaitForSingleObjectEx(iosb->host_event, INFINITE, TRUE);
    WINE_TRACE("Event wait finished %p\n", iosb);
    IO_STATUS_BLOCK_h2g(iosb->guest_iosb, &iosb->iosb);

    WINE_TRACE("Signalling event %p\n", iosb->guest_event);
    if (iosb->guest_event)
        SetEvent(iosb->guest_event);

    CloseHandle(iosb->host_event);
    HeapFree(GetProcessHeap(), 0, iosb);

    return 0;
}

void process_io_status(uint64_t retval, struct IOSB_data *data)
{
    IO_STATUS_BLOCK_h2g(data->guest_iosb, &data->iosb);

    if (retval == STATUS_PENDING)
    {
        WINE_TRACE("Async return, starting wait thread.\n");
        if (!QueueUserWorkItem(iosb32_wait_func, data, 0))
            WINE_ERR("Failed to queue work item\n");
    }
    else
    {
        WINE_TRACE("Synchonous return return, host ptr %p, guest ptr %p.\n", data, data->guest_iosb);

        if (data->guest_event)
        {
            if (retval == STATUS_SUCCESS)
                NtSetEvent(data->guest_event, NULL);
            else
                NtResetEvent(data->guest_event, NULL);
        }

        CloseHandle(data->host_event);
        HeapFree(GetProcessHeap(), 0, data); /* Won't be needed any more. */
    }
}

#endif

struct qemu_NtOpenFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t io;
    uint64_t sharing;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenFile(PHANDLE handle, ACCESS_MASK access, POBJECT_ATTRIBUTES attr, PIO_STATUS_BLOCK io, ULONG sharing, ULONG options)
{
    struct qemu_NtOpenFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENFILE);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;
    call.io = (ULONG_PTR)io;
    call.sharing = (ULONG_PTR)sharing;
    call.options = (ULONG_PTR)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenFile(struct qemu_syscall *call)
{
    struct qemu_NtOpenFile *c = (struct qemu_NtOpenFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenFile(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr), QEMU_G2H(c->io), c->sharing, c->options);
}

#endif

struct qemu_NtCreateFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t io;
    uint64_t alloc_size;
    uint64_t attributes;
    uint64_t sharing;
    uint64_t disposition;
    uint64_t options;
    uint64_t ea_buffer;
    uint64_t ea_length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateFile(HANDLE *handle, ACCESS_MASK access, POBJECT_ATTRIBUTES attr, PIO_STATUS_BLOCK io,
        PLARGE_INTEGER alloc_size, ULONG attributes, ULONG sharing, ULONG disposition, ULONG options, PVOID ea_buffer,
        ULONG ea_length)
{
    struct qemu_NtCreateFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEFILE);
    call.access = access;
    call.attr = (ULONG_PTR)attr;
    call.io = (ULONG_PTR)io;
    call.alloc_size = (ULONG_PTR)alloc_size;
    call.attributes = attributes;
    call.sharing = sharing;
    call.disposition = disposition;
    call.options = options;
    call.ea_buffer = (ULONG_PTR)ea_buffer;
    call.ea_length = (ULONG_PTR)ea_length;

    qemu_syscall(&call.super);
    if (handle)
        *handle = (HANDLE)(ULONG_PTR)call.handle;

    return call.super.iret;
}

#else

void qemu_NtCreateFile(struct qemu_syscall *call)
{
    struct qemu_NtCreateFile *c = (struct qemu_NtCreateFile *)call;
    HANDLE handle;
    IO_STATUS_BLOCK status_stack, *status = &status_stack;
    OBJECT_ATTRIBUTES attr_stack, *attr = &attr_stack;
    struct qemu_OBJECT_ATTRIBUTES *guest_attr;
    UNICODE_STRING name;
    SECURITY_DESCRIPTOR sd_stack;
    struct qemu_SECURITY_DESCRIPTOR *sd32;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    status = QEMU_G2H(c->io);
    attr = QEMU_G2H(c->attr);
#else
    guest_attr = QEMU_G2H(c->attr);
    OBJECT_ATTRIBUTES_g2h(attr, guest_attr, &name);
    sd32 = (struct qemu_SECURITY_DESCRIPTOR *)attr->SecurityDescriptor;
    if (sd32 && !(sd32->Control & SE_SELF_RELATIVE))
    {
        SECURITY_DESCRIPTOR_g2h(&sd_stack, sd32);
        attr->SecurityDescriptor = &sd_stack;
    }
#endif

    c->super.iret = NtCreateFile(&handle, c->access, attr, status,
            QEMU_G2H(c->alloc_size), c->attributes, c->sharing, c->disposition, c->options,
            QEMU_G2H(c->ea_buffer), c->ea_length);
    c->handle = QEMU_H2G(handle);

#if GUEST_BIT != HOST_BIT
    IO_STATUS_BLOCK_h2g(QEMU_G2H(c->io), status);
#endif
}

#endif

struct qemu_NtReadFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t hEvent;
    uint64_t apc;
    uint64_t apc_user;
    uint64_t io_status;
    uint64_t buffer;
    uint64_t length;
    uint64_t offset;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtReadFile(HANDLE hFile, HANDLE hEvent, PIO_APC_ROUTINE apc, void* apc_user, PIO_STATUS_BLOCK io_status, void* buffer, ULONG length, PLARGE_INTEGER offset, PULONG key)
{
    struct qemu_NtReadFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREADFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.hEvent = (ULONG_PTR)hEvent;
    call.apc = (ULONG_PTR)apc;
    call.apc_user = (ULONG_PTR)apc_user;
    call.io_status = (ULONG_PTR)io_status;
    call.buffer = (ULONG_PTR)buffer;
    call.length = (ULONG_PTR)length;
    call.offset = (ULONG_PTR)offset;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReadFile(struct qemu_syscall *call)
{
    struct qemu_NtReadFile *c = (struct qemu_NtReadFile *)call;
    struct IOSB_data *io_wrapper;
    IO_STATUS_BLOCK *iosb;
    HANDLE guest_event, host_event;

    WINE_TRACE("\n");
    if (c->apc)
        WINE_FIXME("Handle APC routine.\n");

#if GUEST_BIT == HOST_BIT
    iosb = QEMU_G2H(c->io_status);
    host_event = QEMU_G2H(c->hEvent);
#else
    if (!c->io_status)
    {
        /* This will do nothing and just return an error. */
        c->super.iret = NtReadFile(QEMU_G2H(c->hFile), QEMU_G2H(c->hEvent), QEMU_G2H(c->apc),
                QEMU_G2H(c->apc_user), NULL, QEMU_G2H(c->buffer), c->length,
                QEMU_G2H(c->offset), QEMU_G2H(c->key));
        return;
    }
    io_wrapper = alloc_io_wrapper(QEMU_G2H(c->io_status));

    iosb = &io_wrapper->iosb;
    guest_event = QEMU_G2H(c->hEvent);
    host_event = io_wrapper->host_event;
    io_wrapper->guest_event = guest_event;
#endif

    c->super.iret = NtReadFile(QEMU_G2H(c->hFile), host_event, QEMU_G2H(c->apc),
            QEMU_G2H(c->apc_user), iosb, QEMU_G2H(c->buffer), c->length,
            QEMU_G2H(c->offset), QEMU_G2H(c->key));

#if GUEST_BIT != HOST_BIT
    process_io_status(c->super.iret, io_wrapper);
#endif
}

#endif

struct qemu_NtReadFileScatter
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t event;
    uint64_t apc;
    uint64_t apc_user;
    uint64_t io_status;
    uint64_t segments;
    uint64_t length;
    uint64_t offset;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtReadFileScatter(HANDLE file, HANDLE event, PIO_APC_ROUTINE apc, void *apc_user, PIO_STATUS_BLOCK io_status, FILE_SEGMENT_ELEMENT *segments, ULONG length, PLARGE_INTEGER offset, PULONG key)
{
    struct qemu_NtReadFileScatter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREADFILESCATTER);
    call.file = (ULONG_PTR)file;
    call.event = (ULONG_PTR)event;
    call.apc = (ULONG_PTR)apc;
    call.apc_user = (ULONG_PTR)apc_user;
    call.io_status = (ULONG_PTR)io_status;
    call.segments = (ULONG_PTR)segments;
    call.length = (ULONG_PTR)length;
    call.offset = (ULONG_PTR)offset;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReadFileScatter(struct qemu_syscall *call)
{
    struct qemu_NtReadFileScatter *c = (struct qemu_NtReadFileScatter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtReadFileScatter(QEMU_G2H(c->file), QEMU_G2H(c->event), QEMU_G2H(c->apc), QEMU_G2H(c->apc_user), QEMU_G2H(c->io_status), QEMU_G2H(c->segments), c->length, QEMU_G2H(c->offset), QEMU_G2H(c->key));
}

#endif

struct qemu_NtWriteFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t hEvent;
    uint64_t apc;
    uint64_t apc_user;
    uint64_t io_status;
    uint64_t buffer;
    uint64_t length;
    uint64_t offset;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtWriteFile(HANDLE hFile, HANDLE hEvent, PIO_APC_ROUTINE apc, void* apc_user,
        PIO_STATUS_BLOCK io_status, const void* buffer, ULONG length, PLARGE_INTEGER offset, PULONG key)
{
    struct qemu_NtWriteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTWRITEFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.hEvent = (ULONG_PTR)hEvent;
    call.apc = (ULONG_PTR)apc;
    call.apc_user = (ULONG_PTR)apc_user;
    call.io_status = (ULONG_PTR)io_status;
    call.buffer = (ULONG_PTR)buffer;
    call.length = (ULONG_PTR)length;
    call.offset = (ULONG_PTR)offset;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtWriteFile(struct qemu_syscall *call)
{
    struct qemu_NtWriteFile *c = (struct qemu_NtWriteFile *)call;
    struct IOSB_data *io_wrapper;
    IO_STATUS_BLOCK *iosb;
    HANDLE guest_event, host_event;

    WINE_TRACE("\n");
    if (c->apc)
        WINE_FIXME("Handle APC routine.\n");

#if GUEST_BIT == HOST_BIT
    iosb = QEMU_G2H(c->io_status);
    host_event = QEMU_G2H(c->hEvent);
#else
    if (!c->io_status)
    {
        /* This will do nothing and just return an error. */
        c->super.iret = NtWriteFile(QEMU_G2H(c->hFile), QEMU_G2H(c->hEvent), QEMU_G2H(c->apc),
            QEMU_G2H(c->apc_user), NULL, QEMU_G2H(c->buffer), c->length, QEMU_G2H(c->offset),
            QEMU_G2H(c->key));
        return;
    }
    io_wrapper = alloc_io_wrapper(QEMU_G2H(c->io_status));

    iosb = &io_wrapper->iosb;
    guest_event = QEMU_G2H(c->hEvent);
    host_event = io_wrapper->host_event;
    io_wrapper->guest_event = guest_event;
#endif


    c->super.iret = NtWriteFile(QEMU_G2H(c->hFile), QEMU_G2H(c->hEvent), QEMU_G2H(c->apc),
            QEMU_G2H(c->apc_user), iosb, QEMU_G2H(c->buffer), c->length, QEMU_G2H(c->offset),
            QEMU_G2H(c->key));

#if GUEST_BIT != HOST_BIT
    process_io_status(c->super.iret, io_wrapper);
#endif
}

#endif

struct qemu_NtWriteFileGather
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t event;
    uint64_t apc;
    uint64_t apc_user;
    uint64_t io_status;
    uint64_t segments;
    uint64_t length;
    uint64_t offset;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtWriteFileGather(HANDLE file, HANDLE event, PIO_APC_ROUTINE apc, void *apc_user, PIO_STATUS_BLOCK io_status, FILE_SEGMENT_ELEMENT *segments, ULONG length, PLARGE_INTEGER offset, PULONG key)
{
    struct qemu_NtWriteFileGather call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTWRITEFILEGATHER);
    call.file = (ULONG_PTR)file;
    call.event = (ULONG_PTR)event;
    call.apc = (ULONG_PTR)apc;
    call.apc_user = (ULONG_PTR)apc_user;
    call.io_status = (ULONG_PTR)io_status;
    call.segments = (ULONG_PTR)segments;
    call.length = (ULONG_PTR)length;
    call.offset = (ULONG_PTR)offset;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtWriteFileGather(struct qemu_syscall *call)
{
    struct qemu_NtWriteFileGather *c = (struct qemu_NtWriteFileGather *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtWriteFileGather(QEMU_G2H(c->file), QEMU_G2H(c->event), QEMU_G2H(c->apc), QEMU_G2H(c->apc_user), QEMU_G2H(c->io_status), QEMU_G2H(c->segments), c->length, QEMU_G2H(c->offset), QEMU_G2H(c->key));
}

#endif

struct qemu_NtDeviceIoControlFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t event;
    uint64_t apc;
    uint64_t apc_context;
    uint64_t io;
    uint64_t code;
    uint64_t in_buffer;
    uint64_t in_size;
    uint64_t out_buffer;
    uint64_t out_size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtDeviceIoControlFile(HANDLE handle, HANDLE event, PIO_APC_ROUTINE apc, PVOID apc_context, PIO_STATUS_BLOCK io, ULONG code, PVOID in_buffer, ULONG in_size, PVOID out_buffer, ULONG out_size)
{
    struct qemu_NtDeviceIoControlFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDEVICEIOCONTROLFILE);
    call.handle = (ULONG_PTR)handle;
    call.event = (ULONG_PTR)event;
    call.apc = (ULONG_PTR)apc;
    call.apc_context = (ULONG_PTR)apc_context;
    call.io = (ULONG_PTR)io;
    call.code = (ULONG_PTR)code;
    call.in_buffer = (ULONG_PTR)in_buffer;
    call.in_size = (ULONG_PTR)in_size;
    call.out_buffer = (ULONG_PTR)out_buffer;
    call.out_size = (ULONG_PTR)out_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtDeviceIoControlFile(struct qemu_syscall *call)
{
    struct qemu_NtDeviceIoControlFile *c = (struct qemu_NtDeviceIoControlFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtDeviceIoControlFile(QEMU_G2H(c->handle), QEMU_G2H(c->event), QEMU_G2H(c->apc), QEMU_G2H(c->apc_context), QEMU_G2H(c->io), c->code, QEMU_G2H(c->in_buffer), c->in_size, QEMU_G2H(c->out_buffer), c->out_size);
}

#endif

struct qemu_NtFsControlFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t event;
    uint64_t apc;
    uint64_t apc_context;
    uint64_t io;
    uint64_t code;
    uint64_t in_buffer;
    uint64_t in_size;
    uint64_t out_buffer;
    uint64_t out_size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtFsControlFile(HANDLE handle, HANDLE event, PIO_APC_ROUTINE apc, PVOID apc_context, PIO_STATUS_BLOCK io, ULONG code, PVOID in_buffer, ULONG in_size, PVOID out_buffer, ULONG out_size)
{
    struct qemu_NtFsControlFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTFSCONTROLFILE);
    call.handle = (ULONG_PTR)handle;
    call.event = (ULONG_PTR)event;
    call.apc = (ULONG_PTR)apc;
    call.apc_context = (ULONG_PTR)apc_context;
    call.io = (ULONG_PTR)io;
    call.code = (ULONG_PTR)code;
    call.in_buffer = (ULONG_PTR)in_buffer;
    call.in_size = (ULONG_PTR)in_size;
    call.out_buffer = (ULONG_PTR)out_buffer;
    call.out_size = (ULONG_PTR)out_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtFsControlFile(struct qemu_syscall *call)
{
    struct qemu_NtFsControlFile *c = (struct qemu_NtFsControlFile *)call;
    IO_STATUS_BLOCK stack, *iosb = &stack;
    WINE_TRACE("\n");
    if (c->apc)
        WINE_FIXME("Handle APC routine.\n");

#if GUEST_BIT == HOST_BIT
    iosb = QEMU_G2H(c->io);
#else
    if (c->io)
        IO_STATUS_BLOCK_g2h(iosb, QEMU_G2H(c->io));
    else
        iosb = NULL;
#endif

    c->super.iret = NtFsControlFile(QEMU_G2H(c->handle), QEMU_G2H(c->event), QEMU_G2H(c->apc),
            QEMU_G2H(c->apc_context), iosb, c->code, QEMU_G2H(c->in_buffer), c->in_size,
            QEMU_G2H(c->out_buffer), c->out_size);

#if GUEST_BIT != HOST_BIT
    if (c->io)
        IO_STATUS_BLOCK_h2g(QEMU_G2H(c->io), iosb);
#endif
}

#endif

struct qemu_NtNotifyChangeDirectoryFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t event;
    uint64_t apc;
    uint64_t apc_context;
    uint64_t iosb;
    uint64_t buffer;
    uint64_t buffer_size;
    uint64_t filter;
    uint64_t subtree;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtNotifyChangeDirectoryFile(HANDLE handle, HANDLE event, PIO_APC_ROUTINE apc, void *apc_context, PIO_STATUS_BLOCK iosb, void *buffer, ULONG buffer_size, ULONG filter, BOOLEAN subtree)
{
    struct qemu_NtNotifyChangeDirectoryFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTNOTIFYCHANGEDIRECTORYFILE);
    call.handle = (ULONG_PTR)handle;
    call.event = (ULONG_PTR)event;
    call.apc = (ULONG_PTR)apc;
    call.apc_context = (ULONG_PTR)apc_context;
    call.iosb = (ULONG_PTR)iosb;
    call.buffer = (ULONG_PTR)buffer;
    call.buffer_size = (ULONG_PTR)buffer_size;
    call.filter = (ULONG_PTR)filter;
    call.subtree = (ULONG_PTR)subtree;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtNotifyChangeDirectoryFile(struct qemu_syscall *call)
{
    struct qemu_NtNotifyChangeDirectoryFile *c = (struct qemu_NtNotifyChangeDirectoryFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtNotifyChangeDirectoryFile(QEMU_G2H(c->handle), QEMU_G2H(c->event), QEMU_G2H(c->apc), QEMU_G2H(c->apc_context), QEMU_G2H(c->iosb), QEMU_G2H(c->buffer), c->buffer_size, c->filter, c->subtree);
}

#endif

struct qemu_NtSetVolumeInformationFile
{
    struct qemu_syscall super;
    uint64_t FileHandle;
    uint64_t IoStatusBlock;
    uint64_t FsInformation;
    uint64_t Length;
    uint64_t FsInformationClass;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetVolumeInformationFile(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FsInformation, ULONG Length, FILE_INFORMATION_CLASS FsInformationClass)
{
    struct qemu_NtSetVolumeInformationFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETVOLUMEINFORMATIONFILE);
    call.FileHandle = (ULONG_PTR)FileHandle;
    call.IoStatusBlock = (ULONG_PTR)IoStatusBlock;
    call.FsInformation = (ULONG_PTR)FsInformation;
    call.Length = (ULONG_PTR)Length;
    call.FsInformationClass = (ULONG_PTR)FsInformationClass;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetVolumeInformationFile(struct qemu_syscall *call)
{
    struct qemu_NtSetVolumeInformationFile *c = (struct qemu_NtSetVolumeInformationFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetVolumeInformationFile((HANDLE)c->FileHandle, QEMU_G2H(c->IoStatusBlock), QEMU_G2H(c->FsInformation), c->Length, c->FsInformationClass);
}

#endif

struct qemu_NtQueryInformationFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t io;
    uint64_t ptr;
    uint64_t len;
    uint64_t class;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryInformationFile(HANDLE hFile, PIO_STATUS_BLOCK io, PVOID ptr, ULONG len, FILE_INFORMATION_CLASS class)
{
    struct qemu_NtQueryInformationFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYINFORMATIONFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.io = (ULONG_PTR)io;
    call.ptr = (ULONG_PTR)ptr;
    call.len = (ULONG_PTR)len;
    call.class = (ULONG_PTR)class;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryInformationFile(struct qemu_syscall *call)
{
    struct qemu_NtQueryInformationFile *c = (struct qemu_NtQueryInformationFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryInformationFile(QEMU_G2H(c->hFile), QEMU_G2H(c->io), QEMU_G2H(c->ptr), c->len, c->class);
}

#endif

struct qemu_NtSetInformationFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t io;
    uint64_t ptr;
    uint64_t len;
    uint64_t class;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetInformationFile(HANDLE handle, PIO_STATUS_BLOCK io, PVOID ptr, ULONG len, FILE_INFORMATION_CLASS class)
{
    struct qemu_NtSetInformationFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINFORMATIONFILE);
    call.handle = (ULONG_PTR)handle;
    call.io = (ULONG_PTR)io;
    call.ptr = (ULONG_PTR)ptr;
    call.len = (ULONG_PTR)len;
    call.class = (ULONG_PTR)class;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetInformationFile(struct qemu_syscall *call)
{
    struct qemu_NtSetInformationFile *c = (struct qemu_NtSetInformationFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetInformationFile(QEMU_G2H(c->handle), QEMU_G2H(c->io), QEMU_G2H(c->ptr), c->len, c->class);
}

#endif

struct qemu_NtQueryFullAttributesFile
{
    struct qemu_syscall super;
    uint64_t attr;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryFullAttributesFile(const OBJECT_ATTRIBUTES *attr, FILE_NETWORK_OPEN_INFORMATION *info)
{
    struct qemu_NtQueryFullAttributesFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYFULLATTRIBUTESFILE);
    call.attr = (ULONG_PTR)attr;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryFullAttributesFile(struct qemu_syscall *call)
{
    struct qemu_NtQueryFullAttributesFile *c = (struct qemu_NtQueryFullAttributesFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryFullAttributesFile(QEMU_G2H(c->attr), QEMU_G2H(c->info));
}

#endif

struct qemu_NtQueryAttributesFile
{
    struct qemu_syscall super;
    uint64_t attr;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryAttributesFile(const OBJECT_ATTRIBUTES *attr, FILE_BASIC_INFORMATION *info)
{
    struct qemu_NtQueryAttributesFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYATTRIBUTESFILE);
    call.attr = (ULONG_PTR)attr;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryAttributesFile(struct qemu_syscall *call)
{
    struct qemu_NtQueryAttributesFile *c = (struct qemu_NtQueryAttributesFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryAttributesFile(QEMU_G2H(c->attr), QEMU_G2H(c->info));
}

#endif

struct qemu_NtQueryVolumeInformationFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t io;
    uint64_t buffer;
    uint64_t length;
    uint64_t info_class;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryVolumeInformationFile(HANDLE handle, PIO_STATUS_BLOCK io, PVOID buffer, ULONG length, FS_INFORMATION_CLASS info_class)
{
    struct qemu_NtQueryVolumeInformationFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYVOLUMEINFORMATIONFILE);
    call.handle = (ULONG_PTR)handle;
    call.io = (ULONG_PTR)io;
    call.buffer = (ULONG_PTR)buffer;
    call.length = (ULONG_PTR)length;
    call.info_class = (ULONG_PTR)info_class;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryVolumeInformationFile(struct qemu_syscall *call)
{
    struct qemu_NtQueryVolumeInformationFile *c = (struct qemu_NtQueryVolumeInformationFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryVolumeInformationFile(QEMU_G2H(c->handle), QEMU_G2H(c->io), QEMU_G2H(c->buffer), c->length, c->info_class);
}

#endif

struct qemu_NtQueryEaFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t iosb;
    uint64_t buffer;
    uint64_t length;
    uint64_t single_entry;
    uint64_t ea_list;
    uint64_t ea_list_len;
    uint64_t ea_index;
    uint64_t restart;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryEaFile(HANDLE hFile, PIO_STATUS_BLOCK iosb, PVOID buffer, ULONG length, BOOLEAN single_entry, PVOID ea_list, ULONG ea_list_len, PULONG ea_index, BOOLEAN restart)
{
    struct qemu_NtQueryEaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYEAFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.iosb = (ULONG_PTR)iosb;
    call.buffer = (ULONG_PTR)buffer;
    call.length = (ULONG_PTR)length;
    call.single_entry = (ULONG_PTR)single_entry;
    call.ea_list = (ULONG_PTR)ea_list;
    call.ea_list_len = (ULONG_PTR)ea_list_len;
    call.ea_index = (ULONG_PTR)ea_index;
    call.restart = (ULONG_PTR)restart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryEaFile(struct qemu_syscall *call)
{
    struct qemu_NtQueryEaFile *c = (struct qemu_NtQueryEaFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryEaFile(QEMU_G2H(c->hFile), QEMU_G2H(c->iosb), QEMU_G2H(c->buffer), c->length, c->single_entry, QEMU_G2H(c->ea_list), c->ea_list_len, QEMU_G2H(c->ea_index), c->restart);
}

#endif

struct qemu_NtSetEaFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t iosb;
    uint64_t buffer;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetEaFile(HANDLE hFile, PIO_STATUS_BLOCK iosb, PVOID buffer, ULONG length)
{
    struct qemu_NtSetEaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETEAFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.iosb = (ULONG_PTR)iosb;
    call.buffer = (ULONG_PTR)buffer;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetEaFile(struct qemu_syscall *call)
{
    struct qemu_NtSetEaFile *c = (struct qemu_NtSetEaFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetEaFile(QEMU_G2H(c->hFile), QEMU_G2H(c->iosb), QEMU_G2H(c->buffer), c->length);
}

#endif

struct qemu_NtFlushBuffersFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t IoStatusBlock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtFlushBuffersFile(HANDLE hFile, IO_STATUS_BLOCK* IoStatusBlock)
{
    struct qemu_NtFlushBuffersFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTFLUSHBUFFERSFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.IoStatusBlock = (ULONG_PTR)IoStatusBlock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtFlushBuffersFile(struct qemu_syscall *call)
{
    struct qemu_NtFlushBuffersFile *c = (struct qemu_NtFlushBuffersFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtFlushBuffersFile(QEMU_G2H(c->hFile), QEMU_G2H(c->IoStatusBlock));
}

#endif

struct qemu_NtLockFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lock_granted_event;
    uint64_t apc;
    uint64_t apc_user;
    uint64_t io_status;
    uint64_t offset;
    uint64_t count;
    uint64_t key;
    uint64_t dont_wait;
    uint64_t exclusive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtLockFile(HANDLE hFile, HANDLE lock_granted_event, PIO_APC_ROUTINE apc, void* apc_user, PIO_STATUS_BLOCK io_status, PLARGE_INTEGER offset, PLARGE_INTEGER count, ULONG* key, BOOLEAN dont_wait, BOOLEAN exclusive)
{
    struct qemu_NtLockFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTLOCKFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.lock_granted_event = (ULONG_PTR)lock_granted_event;
    call.apc = (ULONG_PTR)apc;
    call.apc_user = (ULONG_PTR)apc_user;
    call.io_status = (ULONG_PTR)io_status;
    call.offset = (ULONG_PTR)offset;
    call.count = (ULONG_PTR)count;
    call.key = (ULONG_PTR)key;
    call.dont_wait = (ULONG_PTR)dont_wait;
    call.exclusive = (ULONG_PTR)exclusive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtLockFile(struct qemu_syscall *call)
{
    struct qemu_NtLockFile *c = (struct qemu_NtLockFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtLockFile(QEMU_G2H(c->hFile), QEMU_G2H(c->lock_granted_event), QEMU_G2H(c->apc), QEMU_G2H(c->apc_user), QEMU_G2H(c->io_status), QEMU_G2H(c->offset), QEMU_G2H(c->count), QEMU_G2H(c->key), c->dont_wait, c->exclusive);
}

#endif

struct qemu_NtUnlockFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t io_status;
    uint64_t offset;
    uint64_t count;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtUnlockFile(HANDLE hFile, PIO_STATUS_BLOCK io_status, PLARGE_INTEGER offset, PLARGE_INTEGER count, PULONG key)
{
    struct qemu_NtUnlockFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTUNLOCKFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.io_status = (ULONG_PTR)io_status;
    call.offset = (ULONG_PTR)offset;
    call.count = (ULONG_PTR)count;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtUnlockFile(struct qemu_syscall *call)
{
    struct qemu_NtUnlockFile *c = (struct qemu_NtUnlockFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtUnlockFile(QEMU_G2H(c->hFile), QEMU_G2H(c->io_status), QEMU_G2H(c->offset), QEMU_G2H(c->count), QEMU_G2H(c->key));
}

#endif

struct qemu_NtCreateNamedPipeFile
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t iosb;
    uint64_t sharing;
    uint64_t dispo;
    uint64_t options;
    uint64_t pipe_type;
    uint64_t read_mode;
    uint64_t completion_mode;
    uint64_t max_inst;
    uint64_t inbound_quota;
    uint64_t outbound_quota;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateNamedPipeFile(PHANDLE handle, ULONG access, POBJECT_ATTRIBUTES attr, PIO_STATUS_BLOCK iosb, ULONG sharing, ULONG dispo, ULONG options, ULONG pipe_type, ULONG read_mode, ULONG completion_mode, ULONG max_inst, ULONG inbound_quota, ULONG outbound_quota, PLARGE_INTEGER timeout)
{
    struct qemu_NtCreateNamedPipeFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATENAMEDPIPEFILE);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;
    call.iosb = (ULONG_PTR)iosb;
    call.sharing = (ULONG_PTR)sharing;
    call.dispo = (ULONG_PTR)dispo;
    call.options = (ULONG_PTR)options;
    call.pipe_type = (ULONG_PTR)pipe_type;
    call.read_mode = (ULONG_PTR)read_mode;
    call.completion_mode = (ULONG_PTR)completion_mode;
    call.max_inst = (ULONG_PTR)max_inst;
    call.inbound_quota = (ULONG_PTR)inbound_quota;
    call.outbound_quota = (ULONG_PTR)outbound_quota;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateNamedPipeFile(struct qemu_syscall *call)
{
    struct qemu_NtCreateNamedPipeFile *c = (struct qemu_NtCreateNamedPipeFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateNamedPipeFile(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr), QEMU_G2H(c->iosb), c->sharing, c->dispo, c->options, c->pipe_type, c->read_mode, c->completion_mode, c->max_inst, c->inbound_quota, c->outbound_quota, QEMU_G2H(c->timeout));
}

#endif

struct qemu_NtDeleteFile
{
    struct qemu_syscall super;
    uint64_t ObjectAttributes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtDeleteFile(POBJECT_ATTRIBUTES ObjectAttributes)
{
    struct qemu_NtDeleteFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDELETEFILE);
    call.ObjectAttributes = (ULONG_PTR)ObjectAttributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtDeleteFile(struct qemu_syscall *call)
{
    struct qemu_NtDeleteFile *c = (struct qemu_NtDeleteFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtDeleteFile(QEMU_G2H(c->ObjectAttributes));
}

#endif

struct qemu_NtCancelIoFileEx
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t iosb;
    uint64_t io_status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCancelIoFileEx(HANDLE hFile, PIO_STATUS_BLOCK iosb, PIO_STATUS_BLOCK io_status)
{
    struct qemu_NtCancelIoFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCANCELIOFILEEX);
    call.hFile = (ULONG_PTR)hFile;
    call.iosb = (ULONG_PTR)iosb;
    call.io_status = (ULONG_PTR)io_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCancelIoFileEx(struct qemu_syscall *call)
{
    struct qemu_NtCancelIoFileEx *c = (struct qemu_NtCancelIoFileEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCancelIoFileEx(QEMU_G2H(c->hFile), QEMU_G2H(c->iosb), QEMU_G2H(c->io_status));
}

#endif

struct qemu_NtCancelIoFile
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t io_status;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCancelIoFile(HANDLE hFile, PIO_STATUS_BLOCK io_status)
{
    struct qemu_NtCancelIoFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCANCELIOFILE);
    call.hFile = (ULONG_PTR)hFile;
    call.io_status = (ULONG_PTR)io_status;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCancelIoFile(struct qemu_syscall *call)
{
    struct qemu_NtCancelIoFile *c = (struct qemu_NtCancelIoFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCancelIoFile(QEMU_G2H(c->hFile), QEMU_G2H(c->io_status));
}

#endif

struct qemu_NtCreateMailslotFile
{
    struct qemu_syscall super;
    uint64_t pHandle;
    uint64_t DesiredAccess;
    uint64_t attr;
    uint64_t IoStatusBlock;
    uint64_t CreateOptions;
    uint64_t MailslotQuota;
    uint64_t MaxMessageSize;
    uint64_t TimeOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateMailslotFile(PHANDLE pHandle, ULONG DesiredAccess, POBJECT_ATTRIBUTES attr, PIO_STATUS_BLOCK IoStatusBlock, ULONG CreateOptions, ULONG MailslotQuota, ULONG MaxMessageSize, PLARGE_INTEGER TimeOut)
{
    struct qemu_NtCreateMailslotFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEMAILSLOTFILE);
    call.pHandle = (ULONG_PTR)pHandle;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.attr = (ULONG_PTR)attr;
    call.IoStatusBlock = (ULONG_PTR)IoStatusBlock;
    call.CreateOptions = (ULONG_PTR)CreateOptions;
    call.MailslotQuota = (ULONG_PTR)MailslotQuota;
    call.MaxMessageSize = (ULONG_PTR)MaxMessageSize;
    call.TimeOut = (ULONG_PTR)TimeOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateMailslotFile(struct qemu_syscall *call)
{
    struct qemu_NtCreateMailslotFile *c = (struct qemu_NtCreateMailslotFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateMailslotFile(QEMU_G2H(c->pHandle), c->DesiredAccess, QEMU_G2H(c->attr), QEMU_G2H(c->IoStatusBlock), c->CreateOptions, c->MailslotQuota, c->MaxMessageSize, QEMU_G2H(c->TimeOut));
}

#endif

