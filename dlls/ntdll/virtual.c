/*
 * Copyright 2017 André Hentschel
 * Copyright 2019 Stefan Dösinger for CodeWeavers
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

typedef struct _INITIAL_TEB INITIAL_TEB;
typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation,
    MemoryWorkingSetList,
    MemorySectionName,
    MemoryBasicVlmInformation
} MEMORY_INFORMATION_CLASS;
typedef enum _SECTION_INFORMATION_CLASS
{
  SectionBasicInformation,
  SectionImageInformation,
} SECTION_INFORMATION_CLASS;
typedef enum _SECTION_INHERIT {
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlCreateUserStack
{
    struct qemu_syscall super;
    uint64_t commit;
    uint64_t reserve;
    uint64_t zero_bits;
    uint64_t commit_align;
    uint64_t reserve_align;
    uint64_t stack;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateUserStack(SIZE_T commit, SIZE_T reserve, ULONG zero_bits, SIZE_T commit_align, SIZE_T reserve_align, INITIAL_TEB *stack)
{
    struct qemu_RtlCreateUserStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEUSERSTACK);
    call.commit = commit;
    call.reserve = reserve;
    call.zero_bits = zero_bits;
    call.commit_align = commit_align;
    call.reserve_align = reserve_align;
    call.stack = (ULONG_PTR)stack;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateUserStack(struct qemu_syscall *call)
{
    struct qemu_RtlCreateUserStack *c = (struct qemu_RtlCreateUserStack *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateUserStack(c->commit, c->reserve, c->zero_bits, c->commit_align, c->reserve_align, QEMU_G2H(c->stack));
}

#endif

struct qemu_RtlFreeUserStack
{
    struct qemu_syscall super;
    uint64_t stack;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlFreeUserStack(void *stack)
{
    struct qemu_RtlFreeUserStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREEUSERSTACK);
    call.stack = (ULONG_PTR)stack;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlFreeUserStack(struct qemu_syscall *call)
{
    struct qemu_RtlFreeUserStack *c = (struct qemu_RtlFreeUserStack *)call;
    WINE_FIXME("Unverified!\n");
    RtlFreeUserStack(QEMU_G2H(c->stack));
}

#endif

struct qemu_NtAllocateVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t ret;
    uint64_t zero_bits;
    uint64_t size_ptr;
    uint64_t type;
    uint64_t protect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAllocateVirtualMemory(HANDLE process, PVOID *ret, ULONG_PTR zero_bits, SIZE_T *size_ptr, ULONG type, ULONG protect)
{
    struct qemu_NtAllocateVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTALLOCATEVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.ret = (ULONG_PTR)ret;
    call.zero_bits = zero_bits;
    call.size_ptr = (ULONG_PTR)size_ptr;
    call.type = type;
    call.protect = protect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAllocateVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtAllocateVirtualMemory *c = (struct qemu_NtAllocateVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAllocateVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->ret), c->zero_bits, QEMU_G2H(c->size_ptr), c->type, c->protect);
}

#endif

struct qemu_NtFreeVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr_ptr;
    uint64_t size_ptr;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtFreeVirtualMemory(HANDLE process, PVOID *addr_ptr, SIZE_T *size_ptr, ULONG type)
{
    struct qemu_NtFreeVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTFREEVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr_ptr = (ULONG_PTR)addr_ptr;
    call.size_ptr = (ULONG_PTR)size_ptr;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtFreeVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtFreeVirtualMemory *c = (struct qemu_NtFreeVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtFreeVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr_ptr), QEMU_G2H(c->size_ptr), c->type);
}

#endif

struct qemu_NtProtectVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr_ptr;
    uint64_t size_ptr;
    uint64_t new_prot;
    uint64_t old_prot;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtProtectVirtualMemory(HANDLE process, PVOID *addr_ptr, SIZE_T *size_ptr, ULONG new_prot, ULONG *old_prot)
{
    struct qemu_NtProtectVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTPROTECTVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr_ptr = (ULONG_PTR)addr_ptr;
    call.size_ptr = (ULONG_PTR)size_ptr;
    call.new_prot = new_prot;
    call.old_prot = (ULONG_PTR)old_prot;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtProtectVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtProtectVirtualMemory *c = (struct qemu_NtProtectVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtProtectVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr_ptr), QEMU_G2H(c->size_ptr), c->new_prot, QEMU_G2H(c->old_prot));
}

#endif

struct qemu_NtQueryVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t info_class;
    uint64_t buffer;
    uint64_t len;
    uint64_t res_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryVirtualMemory(HANDLE process, LPCVOID addr, MEMORY_INFORMATION_CLASS info_class, PVOID buffer, SIZE_T len, SIZE_T *res_len)
{
    struct qemu_NtQueryVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr = (ULONG_PTR)addr;
    call.info_class = info_class;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;
    call.res_len = (ULONG_PTR)res_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtQueryVirtualMemory *c = (struct qemu_NtQueryVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), c->info_class, QEMU_G2H(c->buffer), c->len, QEMU_G2H(c->res_len));
}

#endif

struct qemu_NtLockVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t size;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtLockVirtualMemory(HANDLE process, PVOID *addr, SIZE_T *size, ULONG unknown)
{
    struct qemu_NtLockVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTLOCKVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;
    call.unknown = unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtLockVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtLockVirtualMemory *c = (struct qemu_NtLockVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtLockVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->size), c->unknown);
}

#endif

struct qemu_NtUnlockVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t size;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtUnlockVirtualMemory(HANDLE process, PVOID *addr, SIZE_T *size, ULONG unknown)
{
    struct qemu_NtUnlockVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTUNLOCKVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr = (ULONG_PTR)addr;
    call.size = (ULONG_PTR)size;
    call.unknown = unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtUnlockVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtUnlockVirtualMemory *c = (struct qemu_NtUnlockVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtUnlockVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->size), c->unknown);
}

#endif

struct qemu_NtCreateSection
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
    uint64_t size;
    uint64_t protect;
    uint64_t sec_flags;
    uint64_t file;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreateSection(HANDLE *handle, ACCESS_MASK access,
        const OBJECT_ATTRIBUTES *attr, const LARGE_INTEGER *size, ULONG protect, ULONG sec_flags, HANDLE file)
{
    struct qemu_NtCreateSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATESECTION);
    call.access = access;
    call.attr = (ULONG_PTR)attr;
    call.size = (ULONG_PTR)size;
    call.protect = protect;
    call.sec_flags = sec_flags;
    call.file = (ULONG_PTR)file;

    qemu_syscall(&call.super);
    *handle = (HANDLE)(ULONG_PTR)call.handle;

    return call.super.iret;
}

#else

void qemu_NtCreateSection(struct qemu_syscall *call)
{
    struct qemu_NtCreateSection *c = (struct qemu_NtCreateSection *)call;
    OBJECT_ATTRIBUTES stack, *attr = &stack;
    UNICODE_STRING name;
    HANDLE handle;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    attr = QEMU_G2H(c->attr);
#else
    OBJECT_ATTRIBUTES_g2h(attr, QEMU_G2H(c->attr), &name);
#endif

    c->super.iret = NtCreateSection(&handle, c->access, attr, QEMU_G2H(c->size),
            c->protect, c->sec_flags, QEMU_G2H(c->file));
    c->handle = QEMU_H2G(handle);
    WINE_TRACE("ret %lx\n", c->super.iret);
}

#endif

struct qemu_NtOpenSection
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t access;
    uint64_t attr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenSection(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr)
{
    struct qemu_NtOpenSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENSECTION);
    call.handle = (ULONG_PTR)handle;
    call.access = access;
    call.attr = (ULONG_PTR)attr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenSection(struct qemu_syscall *call)
{
    struct qemu_NtOpenSection *c = (struct qemu_NtOpenSection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenSection(QEMU_G2H(c->handle), c->access, QEMU_G2H(c->attr));
}

#endif

struct qemu_NtMapViewOfSection
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t process;
    uint64_t addr_ptr;
    uint64_t zero_bits;
    uint64_t commit_size;
    uint64_t offset_ptr;
    uint64_t size_ptr;
    uint64_t inherit;
    uint64_t alloc_type;
    uint64_t protect;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtMapViewOfSection(HANDLE handle, HANDLE process, PVOID *addr_ptr, ULONG_PTR zero_bits,
        SIZE_T commit_size, const LARGE_INTEGER *offset_ptr, SIZE_T *size_ptr, SECTION_INHERIT inherit,
        ULONG alloc_type, ULONG protect)
{
    struct qemu_NtMapViewOfSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTMAPVIEWOFSECTION);
    call.handle = (ULONG_PTR)handle;
    call.process = guest_HANDLE_g2h(process);
    call.addr_ptr = (ULONG_PTR)addr_ptr;
    call.zero_bits = zero_bits;
    call.commit_size = commit_size;
    call.offset_ptr = (ULONG_PTR)offset_ptr;
    call.size_ptr = (ULONG_PTR)size_ptr;
    call.inherit = inherit;
    call.alloc_type = alloc_type;
    call.protect = protect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtMapViewOfSection(struct qemu_syscall *call)
{
    struct qemu_NtMapViewOfSection *c = (struct qemu_NtMapViewOfSection *)call;
    void *addr_ptr_content;
    void **addr_ptr = &addr_ptr_content;
    qemu_ptr *addr_ptr_guest, *size_ptr_guest;
    SIZE_T size_content, *size_ptr = &size_content;
    
    WINE_WARN("A lot of pitfalls here...\n");

#if GUEST_BIT == HOST_BIT
    addr_ptr = QEMU_G2H(c->addr_ptr);
    size_ptr = QEMU_G2H(c->size_ptr);
#else
    addr_ptr_guest = QEMU_G2H(c->addr_ptr);
    size_ptr_guest = QEMU_G2H(c->size_ptr);
    addr_ptr_content = QEMU_G2H((ULONG_PTR)*addr_ptr_guest);
    size_content = *size_ptr_guest;
#endif

    WINE_TRACE("handle %p ptr in %p %p size %lx\n", QEMU_G2H(c->handle), addr_ptr, *addr_ptr, *size_ptr);

    c->super.iret = NtMapViewOfSection(QEMU_G2H(c->handle), QEMU_G2H(c->process), addr_ptr, c->zero_bits,
            c->commit_size, QEMU_G2H(c->offset_ptr), size_ptr,
            c->inherit, c->alloc_type, c->protect);

    WINE_TRACE("ret %lx ptr %p\n", c->super.iret, *addr_ptr);
#if GUEST_BIT != HOST_BIT
    *addr_ptr_guest = QEMU_H2G(addr_ptr_content);
#endif
}

#endif

struct qemu_NtUnmapViewOfSection
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtUnmapViewOfSection(HANDLE process, PVOID addr)
{
    struct qemu_NtUnmapViewOfSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTUNMAPVIEWOFSECTION);
    call.process = guest_HANDLE_g2h(process);
    call.addr = (ULONG_PTR)addr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtUnmapViewOfSection(struct qemu_syscall *call)
{
    struct qemu_NtUnmapViewOfSection *c = (struct qemu_NtUnmapViewOfSection *)call;
    WINE_TRACE("\n");
    c->super.iret = NtUnmapViewOfSection(QEMU_G2H(c->process), QEMU_G2H(c->addr));
}

#endif

struct qemu_NtQuerySection
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t class;
    uint64_t ptr;
    uint64_t size;
    uint64_t ret_size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySection(HANDLE handle, SECTION_INFORMATION_CLASS class, void *ptr, SIZE_T size, SIZE_T *ret_size)
{
    struct qemu_NtQuerySection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSECTION);
    call.handle = (ULONG_PTR)handle;
    call.class = class;
    call.ptr = (ULONG_PTR)ptr;
    call.size = size;
    call.ret_size = (ULONG_PTR)ret_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySection(struct qemu_syscall *call)
{
    struct qemu_NtQuerySection *c = (struct qemu_NtQuerySection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySection(QEMU_G2H(c->handle), c->class, QEMU_G2H(c->ptr), c->size, QEMU_G2H(c->ret_size));
}

#endif

struct qemu_NtFlushVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr_ptr;
    uint64_t size_ptr;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtFlushVirtualMemory(HANDLE process, LPCVOID *addr_ptr, SIZE_T *size_ptr, ULONG unknown)
{
    struct qemu_NtFlushVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTFLUSHVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr_ptr = (ULONG_PTR)addr_ptr;
    call.size_ptr = (ULONG_PTR)size_ptr;
    call.unknown = unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtFlushVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtFlushVirtualMemory *c = (struct qemu_NtFlushVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtFlushVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr_ptr), QEMU_G2H(c->size_ptr), c->unknown);
}

#endif

struct qemu_NtGetWriteWatch
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t flags;
    uint64_t base;
    uint64_t size;
    uint64_t addresses;
    uint64_t count;
    uint64_t granularity;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtGetWriteWatch(HANDLE process, ULONG flags, PVOID base, SIZE_T size, PVOID *addresses, ULONG_PTR *count, ULONG *granularity)
{
    struct qemu_NtGetWriteWatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTGETWRITEWATCH);
    call.process = (ULONG_PTR)process;
    call.flags = flags;
    call.base = (ULONG_PTR)base;
    call.size = size;
    call.addresses = (ULONG_PTR)addresses;
    call.count = (ULONG_PTR)count;
    call.granularity = (ULONG_PTR)granularity;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtGetWriteWatch(struct qemu_syscall *call)
{
    struct qemu_NtGetWriteWatch *c = (struct qemu_NtGetWriteWatch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtGetWriteWatch(QEMU_G2H(c->process), c->flags, QEMU_G2H(c->base), c->size, QEMU_G2H(c->addresses), QEMU_G2H(c->count), QEMU_G2H(c->granularity));
}

#endif

struct qemu_NtResetWriteWatch
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t base;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtResetWriteWatch(HANDLE process, PVOID base, SIZE_T size)
{
    struct qemu_NtResetWriteWatch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTRESETWRITEWATCH);
    call.process = (ULONG_PTR)process;
    call.base = (ULONG_PTR)base;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtResetWriteWatch(struct qemu_syscall *call)
{
    struct qemu_NtResetWriteWatch *c = (struct qemu_NtResetWriteWatch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtResetWriteWatch(QEMU_G2H(c->process), QEMU_G2H(c->base), c->size);
}

#endif

struct qemu_NtReadVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t buffer;
    uint64_t size;
    uint64_t bytes_read;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtReadVirtualMemory(HANDLE process, const void *addr, void *buffer, SIZE_T size, SIZE_T *bytes_read)
{
    struct qemu_NtReadVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREADVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr = (ULONG_PTR)addr;
    call.buffer = (ULONG_PTR)buffer;
    call.size = size;
    call.bytes_read = (ULONG_PTR)bytes_read;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReadVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtReadVirtualMemory *c = (struct qemu_NtReadVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtReadVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->bytes_read));
}

#endif

struct qemu_NtWriteVirtualMemory
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t addr;
    uint64_t buffer;
    uint64_t size;
    uint64_t bytes_written;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtWriteVirtualMemory(HANDLE process, void *addr, const void *buffer, SIZE_T size, SIZE_T *bytes_written)
{
    struct qemu_NtWriteVirtualMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTWRITEVIRTUALMEMORY);
    call.process = (ULONG_PTR)process;
    call.addr = (ULONG_PTR)addr;
    call.buffer = (ULONG_PTR)buffer;
    call.size = size;
    call.bytes_written = (ULONG_PTR)bytes_written;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtWriteVirtualMemory(struct qemu_syscall *call)
{
    struct qemu_NtWriteVirtualMemory *c = (struct qemu_NtWriteVirtualMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtWriteVirtualMemory(QEMU_G2H(c->process), QEMU_G2H(c->addr), QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->bytes_written));
}

#endif

struct qemu_NtAreMappedFilesTheSame
{
    struct qemu_syscall super;
    uint64_t addr1;
    uint64_t addr2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAreMappedFilesTheSame(PVOID addr1, PVOID addr2)
{
    struct qemu_NtAreMappedFilesTheSame call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTAREMAPPEDFILESTHESAME);
    call.addr1 = (ULONG_PTR)addr1;
    call.addr2 = (ULONG_PTR)addr2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAreMappedFilesTheSame(struct qemu_syscall *call)
{
    struct qemu_NtAreMappedFilesTheSame *c = (struct qemu_NtAreMappedFilesTheSame *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAreMappedFilesTheSame(QEMU_G2H(c->addr1), QEMU_G2H(c->addr2));
}

#endif

