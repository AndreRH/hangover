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
typedef void *PDIRECTORY_BASIC_INFORMATION;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_NtQueryObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t info_class;
    uint64_t ptr;
    uint64_t len;
    uint64_t used_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryObject(IN HANDLE handle, IN OBJECT_INFORMATION_CLASS info_class, OUT PVOID ptr, IN ULONG len, OUT PULONG used_len)
{
    struct qemu_NtQueryObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.info_class = (ULONG_PTR)info_class;
    call.ptr = (ULONG_PTR)ptr;
    call.len = (ULONG_PTR)len;
    call.used_len = (ULONG_PTR)used_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryObject(struct qemu_syscall *call)
{
    struct qemu_NtQueryObject *c = (struct qemu_NtQueryObject *)call;
    OBJECT_NAME_INFORMATION *name;
    struct qemu_OBJECT_NAME_INFORMATION *guest_name;
    ULONG alloc_len;
    ULONG *len_out;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    c->super.iret = NtQueryObject((HANDLE)c->handle, c->info_class, QEMU_G2H(c->ptr), c->len, QEMU_G2H(c->used_len));
    return;
#endif

    len_out = QEMU_G2H(c->used_len);
    switch (c->info_class)
    {
        case ObjectBasicInformation:
            /* OBJECT_BASIC_INFORMATION is the same in 32 and 64 bit */
            c->super.iret = NtQueryObject((HANDLE)c->handle, c->info_class, QEMU_G2H(c->ptr), c->len, len_out);
            break;

        case ObjectNameInformation:
            WINE_TRACE("Translating OBJECT_NAME_INFORMATION\n");

            if (len_out)
                *len_out = 0;
            if (c->len < sizeof(struct qemu_OBJECT_NAME_INFORMATION))
            {
                WINE_WARN("Expect %u, got %lu\n", (unsigned int)c->len,
                        sizeof(struct qemu_OBJECT_NAME_INFORMATION));
                c->super.iret = STATUS_INFO_LENGTH_MISMATCH;
                return;
            }

            alloc_len = c->len + sizeof(*name) - sizeof(*guest_name);
            name = HeapAlloc(GetProcessHeap(), 0, alloc_len);
            guest_name = QEMU_G2H(c->ptr);

            c->super.iret = NtQueryObject((HANDLE)c->handle, ObjectNameInformation, name, alloc_len, &alloc_len);

            if (!c->super.iret)
            {
                OBJECT_NAME_INFORMATION_h2g(guest_name, name);
                memcpy((char *)guest_name + sizeof(*guest_name),
                        (char *)name + sizeof(*name),
                        alloc_len - sizeof(*name));
                guest_name->Name.Buffer = (ULONG_PTR)(guest_name + 1);

                if (len_out)
                    *len_out = alloc_len - sizeof(*name) + sizeof(*guest_name);
            }

            HeapFree(GetProcessHeap(), 0, name);
            break;

        default:
            WINE_FIXME("Unsupported info class 0x%x\n", (unsigned int)c->info_class);
            c->super.iret = NtQueryObject((HANDLE)c->handle, c->info_class, QEMU_G2H(c->ptr), c->len, len_out);
    }
}

#endif

struct qemu_NtSetInformationObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t info_class;
    uint64_t ptr;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetInformationObject(IN HANDLE handle, IN OBJECT_INFORMATION_CLASS info_class, IN PVOID ptr, IN ULONG len)
{
    struct qemu_NtSetInformationObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINFORMATIONOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.info_class = (ULONG_PTR)info_class;
    call.ptr = (ULONG_PTR)ptr;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetInformationObject(struct qemu_syscall *call)
{
    struct qemu_NtSetInformationObject *c = (struct qemu_NtSetInformationObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetInformationObject((HANDLE)c->handle, c->info_class, QEMU_G2H(c->ptr), c->len);
}

#endif

struct qemu_NtQuerySecurityObject
{
    struct qemu_syscall super;
    uint64_t Object;
    uint64_t RequestedInformation;
    uint64_t pSecurityDescriptor;
    uint64_t Length;
    uint64_t ResultLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySecurityObject(IN HANDLE Object, IN SECURITY_INFORMATION RequestedInformation, OUT PSECURITY_DESCRIPTOR pSecurityDescriptor, IN ULONG Length, OUT PULONG ResultLength)
{
    struct qemu_NtQuerySecurityObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSECURITYOBJECT);
    call.Object = (ULONG_PTR)Object;
    call.RequestedInformation = (ULONG_PTR)RequestedInformation;
    call.pSecurityDescriptor = (ULONG_PTR)pSecurityDescriptor;
    call.Length = (ULONG_PTR)Length;
    call.ResultLength = (ULONG_PTR)ResultLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySecurityObject(struct qemu_syscall *call)
{
    struct qemu_NtQuerySecurityObject *c = (struct qemu_NtQuerySecurityObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySecurityObject((HANDLE)c->Object, c->RequestedInformation, QEMU_G2H(c->pSecurityDescriptor), c->Length, QEMU_G2H(c->ResultLength));
}

#endif

struct qemu_NtDuplicateObject
{
    struct qemu_syscall super;
    uint64_t source_process;
    uint64_t source;
    uint64_t dest_process;
    uint64_t dest;
    uint64_t access;
    uint64_t attributes;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtDuplicateObject(HANDLE source_process, HANDLE source, HANDLE dest_process, PHANDLE dest, ACCESS_MASK access, ULONG attributes, ULONG options)
{
    struct qemu_NtDuplicateObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDUPLICATEOBJECT);
    call.source_process = (ULONG_PTR)source_process;
    call.source = (ULONG_PTR)source;
    call.dest_process = (ULONG_PTR)dest_process;
    call.dest = (ULONG_PTR)dest;
    call.access = (ULONG_PTR)access;
    call.attributes = (ULONG_PTR)attributes;
    call.options = (ULONG_PTR)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtDuplicateObject(struct qemu_syscall *call)
{
    struct qemu_NtDuplicateObject *c = (struct qemu_NtDuplicateObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtDuplicateObject(QEMU_G2H(c->source_process), QEMU_G2H(c->source), QEMU_G2H(c->dest_process), QEMU_G2H(c->dest), c->access, c->attributes, c->options);
}

#endif

struct qemu_NtClose
{
    struct qemu_syscall super;
    uint64_t Handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtClose(HANDLE Handle)
{
    struct qemu_NtClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCLOSE);
    call.Handle = (ULONG_PTR)Handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtClose(struct qemu_syscall *call)
{
    struct qemu_NtClose *c = (struct qemu_NtClose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtClose(QEMU_G2H(c->Handle));
}

#endif

struct qemu_NtOpenDirectoryObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenDirectoryObject(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenDirectoryObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENDIRECTORYOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenDirectoryObject(struct qemu_syscall *call)
{
    struct qemu_NtOpenDirectoryObject *c = (struct qemu_NtOpenDirectoryObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenDirectoryObject(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtCreateDirectoryObject
{
    struct qemu_syscall super;
    uint64_t DirectoryHandle;
    uint64_t DesiredAccess;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateDirectoryObject(PHANDLE DirectoryHandle, ACCESS_MASK DesiredAccess, OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtCreateDirectoryObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEDIRECTORYOBJECT);
    call.DirectoryHandle = (ULONG_PTR)DirectoryHandle;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateDirectoryObject(struct qemu_syscall *call)
{
    struct qemu_NtCreateDirectoryObject *c = (struct qemu_NtCreateDirectoryObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateDirectoryObject(QEMU_G2H(c->DirectoryHandle), c->DesiredAccess, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtQueryDirectoryObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t size;
    uint64_t single_entry;
    uint64_t restart;
    uint64_t context;
    uint64_t ret_size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryDirectoryObject(HANDLE handle, PDIRECTORY_BASIC_INFORMATION buffer, ULONG size, BOOLEAN single_entry, BOOLEAN restart, PULONG context, PULONG ret_size)
{
    struct qemu_NtQueryDirectoryObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYDIRECTORYOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;
    call.single_entry = (ULONG_PTR)single_entry;
    call.restart = (ULONG_PTR)restart;
    call.context = (ULONG_PTR)context;
    call.ret_size = (ULONG_PTR)ret_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryDirectoryObject(struct qemu_syscall *call)
{
    struct qemu_NtQueryDirectoryObject *c = (struct qemu_NtQueryDirectoryObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryDirectoryObject(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->size, c->single_entry, c->restart, QEMU_G2H(c->context), QEMU_G2H(c->ret_size));
}

#endif

struct qemu_NtOpenSymbolicLinkObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenSymbolicLinkObject(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenSymbolicLinkObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENSYMBOLICLINKOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.access = (ULONG_PTR)access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenSymbolicLinkObject(struct qemu_syscall *call)
{
    struct qemu_NtOpenSymbolicLinkObject *c = (struct qemu_NtOpenSymbolicLinkObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenSymbolicLinkObject(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtCreateSymbolicLinkObject
{
    struct qemu_syscall super;
    uint64_t SymbolicLinkHandle;
    uint64_t DesiredAccess;
    uint64_t attr;
    uint64_t TargetName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateSymbolicLinkObject(OUT PHANDLE SymbolicLinkHandle,IN ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES attr, PUNICODE_STRING TargetName)
{
    struct qemu_NtCreateSymbolicLinkObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATESYMBOLICLINKOBJECT);
    call.SymbolicLinkHandle = (ULONG_PTR)SymbolicLinkHandle;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.attr = (ULONG_PTR)attr;
    call.TargetName = (ULONG_PTR)TargetName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreateSymbolicLinkObject(struct qemu_syscall *call)
{
    struct qemu_NtCreateSymbolicLinkObject *c = (struct qemu_NtCreateSymbolicLinkObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreateSymbolicLinkObject(QEMU_G2H(c->SymbolicLinkHandle), c->DesiredAccess, QEMU_G2H(c->attr), QEMU_G2H(c->TargetName));
}

#endif

struct qemu_NtQuerySymbolicLinkObject
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t target;
    uint64_t length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySymbolicLinkObject(HANDLE handle, PUNICODE_STRING target, PULONG length)
{
    struct qemu_NtQuerySymbolicLinkObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSYMBOLICLINKOBJECT);
    call.handle = (ULONG_PTR)handle;
    call.target = (ULONG_PTR)target;
    call.length = (ULONG_PTR)length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySymbolicLinkObject(struct qemu_syscall *call)
{
    struct qemu_NtQuerySymbolicLinkObject *c = (struct qemu_NtQuerySymbolicLinkObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySymbolicLinkObject(QEMU_G2H(c->handle), QEMU_G2H(c->target), QEMU_G2H(c->length));
}

#endif

struct qemu_NtAllocateUuids
{
    struct qemu_syscall super;
    uint64_t Time;
    uint64_t Range;
    uint64_t Sequence;
    uint64_t seed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAllocateUuids(PULARGE_INTEGER Time, PULONG Range, PULONG Sequence, UCHAR *seed)
{
    struct qemu_NtAllocateUuids call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTALLOCATEUUIDS);
    call.Time = (ULONG_PTR)Time;
    call.Range = (ULONG_PTR)Range;
    call.Sequence = (ULONG_PTR)Sequence;
    call.seed = (ULONG_PTR)seed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAllocateUuids(struct qemu_syscall *call)
{
    struct qemu_NtAllocateUuids *c = (struct qemu_NtAllocateUuids *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAllocateUuids(QEMU_G2H(c->Time), QEMU_G2H(c->Range), QEMU_G2H(c->Sequence),
            QEMU_G2H(c->seed));
}

#endif

struct qemu_NtMakeTemporaryObject
{
    struct qemu_syscall super;
    uint64_t Handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtMakeTemporaryObject(HANDLE Handle)
{
    struct qemu_NtMakeTemporaryObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTMAKETEMPORARYOBJECT);
    call.Handle = (ULONG_PTR)Handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtMakeTemporaryObject(struct qemu_syscall *call)
{
    struct qemu_NtMakeTemporaryObject *c = (struct qemu_NtMakeTemporaryObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtMakeTemporaryObject(QEMU_G2H(c->Handle));
}

#endif

