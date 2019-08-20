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

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlCreateHeap
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t addr;
    uint64_t totalSize;
    uint64_t commitSize;
    uint64_t unknown;
    uint64_t definition;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RtlCreateHeap(ULONG flags, PVOID addr, SIZE_T totalSize, SIZE_T commitSize, PVOID unknown, PRTL_HEAP_PARAMETERS definition)
{
    struct qemu_RtlCreateHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEHEAP);
    call.flags = (ULONG_PTR)flags;
    call.addr = (ULONG_PTR)addr;
    call.totalSize = (ULONG_PTR)totalSize;
    call.commitSize = (ULONG_PTR)commitSize;
    call.unknown = (ULONG_PTR)unknown;
    call.definition = (ULONG_PTR)definition;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlCreateHeap(struct qemu_syscall *call)
{
    struct qemu_RtlCreateHeap *c = (struct qemu_RtlCreateHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RtlCreateHeap(c->flags, QEMU_G2H(c->addr), c->totalSize, c->commitSize, QEMU_G2H(c->unknown), QEMU_G2H(c->definition));
}

#endif

struct qemu_RtlDestroyHeap
{
    struct qemu_syscall super;
    uint64_t heap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RtlDestroyHeap(HANDLE heap)
{
    struct qemu_RtlDestroyHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDESTROYHEAP);
    call.heap = (ULONG_PTR)heap;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlDestroyHeap(struct qemu_syscall *call)
{
    struct qemu_RtlDestroyHeap *c = (struct qemu_RtlDestroyHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RtlDestroyHeap(QEMU_G2H(c->heap));
}

#endif

struct qemu_RtlAllocateHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI ntdll_RtlAllocateHeap(HANDLE heap, ULONG flags, SIZE_T size)
{
    struct qemu_RtlAllocateHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLALLOCATEHEAP);
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlAllocateHeap(struct qemu_syscall *call)
{
    struct qemu_RtlAllocateHeap *c = (struct qemu_RtlAllocateHeap *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlAllocateHeap(QEMU_G2H(c->heap), c->flags, c->size);
}

#endif

struct qemu_RtlFreeHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

BOOLEAN WINAPI ntdll_RtlFreeHeap(HANDLE heap, ULONG flags, PVOID ptr)
{
    struct qemu_RtlFreeHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREEHEAP);
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFreeHeap(struct qemu_syscall *call)
{
    struct qemu_RtlFreeHeap *c = (struct qemu_RtlFreeHeap *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlFreeHeap(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr));
}

#endif

struct qemu_RtlReAllocateHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI RtlReAllocateHeap(HANDLE heap, ULONG flags, PVOID ptr, SIZE_T size)
{
    struct qemu_RtlReAllocateHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLREALLOCATEHEAP);
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;
    call.ptr = (ULONG_PTR)ptr;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlReAllocateHeap(struct qemu_syscall *call)
{
    struct qemu_RtlReAllocateHeap *c = (struct qemu_RtlReAllocateHeap *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlReAllocateHeap(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr), c->size);
}

#endif

struct qemu_RtlCompactHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlCompactHeap(HANDLE heap, ULONG flags)
{
    struct qemu_RtlCompactHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPACTHEAP);
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCompactHeap(struct qemu_syscall *call)
{
    struct qemu_RtlCompactHeap *c = (struct qemu_RtlCompactHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompactHeap(QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_RtlLockHeap
{
    struct qemu_syscall super;
    uint64_t heap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlLockHeap(HANDLE heap)
{
    struct qemu_RtlLockHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLOCKHEAP);
    call.heap = (ULONG_PTR)heap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLockHeap(struct qemu_syscall *call)
{
    struct qemu_RtlLockHeap *c = (struct qemu_RtlLockHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlLockHeap(QEMU_G2H(c->heap));
}

#endif

struct qemu_RtlUnlockHeap
{
    struct qemu_syscall super;
    uint64_t heap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlUnlockHeap(HANDLE heap)
{
    struct qemu_RtlUnlockHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNLOCKHEAP);
    call.heap = (ULONG_PTR)heap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnlockHeap(struct qemu_syscall *call)
{
    struct qemu_RtlUnlockHeap *c = (struct qemu_RtlUnlockHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnlockHeap(QEMU_G2H(c->heap));
}

#endif

struct qemu_RtlSizeHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI RtlSizeHeap(HANDLE heap, ULONG flags, const void *ptr)
{
    struct qemu_RtlSizeHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSIZEHEAP);
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSizeHeap(struct qemu_syscall *call)
{
    struct qemu_RtlSizeHeap *c = (struct qemu_RtlSizeHeap *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlSizeHeap(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr));
}

#endif

struct qemu_RtlValidateHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlValidateHeap(HANDLE heap, ULONG flags, LPCVOID ptr)
{
    struct qemu_RtlValidateHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLVALIDATEHEAP);
    call.heap = (ULONG_PTR)heap;
    call.flags = (ULONG_PTR)flags;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlValidateHeap(struct qemu_syscall *call)
{
    struct qemu_RtlValidateHeap *c = (struct qemu_RtlValidateHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlValidateHeap(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr));
}

#endif

struct qemu_RtlWalkHeap
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t entry_ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlWalkHeap(HANDLE heap, PVOID entry_ptr)
{
    struct qemu_RtlWalkHeap call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLWALKHEAP);
    call.heap = (ULONG_PTR)heap;
    call.entry_ptr = (ULONG_PTR)entry_ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlWalkHeap(struct qemu_syscall *call)
{
    struct qemu_RtlWalkHeap *c = (struct qemu_RtlWalkHeap *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlWalkHeap(QEMU_G2H(c->heap), QEMU_G2H(c->entry_ptr));
}

#endif

struct qemu_RtlGetProcessHeaps
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t heaps;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlGetProcessHeaps(ULONG count, HANDLE *heaps)
{
    struct qemu_RtlGetProcessHeaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETPROCESSHEAPS);
    call.count = (ULONG_PTR)count;
    call.heaps = (ULONG_PTR)heaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetProcessHeaps(struct qemu_syscall *call)
{
    struct qemu_RtlGetProcessHeaps *c = (struct qemu_RtlGetProcessHeaps *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetProcessHeaps(c->count, QEMU_G2H(c->heaps));
}

#endif

struct qemu_RtlQueryHeapInformation
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t info_class;
    uint64_t info;
    uint64_t size_in;
    uint64_t size_out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlQueryHeapInformation(HANDLE heap, HEAP_INFORMATION_CLASS info_class, PVOID info, SIZE_T size_in, PSIZE_T size_out)
{
    struct qemu_RtlQueryHeapInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYHEAPINFORMATION);
    call.heap = (ULONG_PTR)heap;
    call.info_class = (ULONG_PTR)info_class;
    call.info = (ULONG_PTR)info;
    call.size_in = (ULONG_PTR)size_in;
    call.size_out = (ULONG_PTR)size_out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryHeapInformation(struct qemu_syscall *call)
{
    struct qemu_RtlQueryHeapInformation *c = (struct qemu_RtlQueryHeapInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlQueryHeapInformation(QEMU_G2H(c->heap), c->info_class, QEMU_G2H(c->info), c->size_in, QEMU_G2H(c->size_out));
}

#endif

struct qemu_RtlSetHeapInformation
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t info_class;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlSetHeapInformation(void *heap, HEAP_INFORMATION_CLASS info_class, PVOID info, SIZE_T size)
{
    struct qemu_RtlSetHeapInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETHEAPINFORMATION);
    call.heap = (ULONG_PTR)heap;
    call.info_class = (ULONG_PTR)info_class;
    call.info = (ULONG_PTR)info;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetHeapInformation(struct qemu_syscall *call)
{
    struct qemu_RtlSetHeapInformation *c = (struct qemu_RtlSetHeapInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetHeapInformation(QEMU_G2H(c->heap), c->info_class, QEMU_G2H(c->info), c->size);
}

#endif

