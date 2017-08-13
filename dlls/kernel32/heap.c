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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_HeapCreate
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t initialSize;
    uint64_t maxSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI HeapCreate(DWORD flags, SIZE_T initialSize, SIZE_T maxSize)
{
    struct qemu_HeapCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPCREATE);
    call.flags = flags;
    call.initialSize = initialSize;
    call.maxSize = maxSize;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_HeapCreate(struct qemu_syscall *call)
{
    struct qemu_HeapCreate *c = (struct qemu_HeapCreate *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)HeapCreate(c->flags, c->initialSize, c->maxSize);
}

#endif

struct qemu_HeapDestroy
{
    struct qemu_syscall super;
    uint64_t heap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapDestroy(HANDLE heap)
{
    struct qemu_HeapDestroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPDESTROY);
    call.heap = (uint64_t)heap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapDestroy(struct qemu_syscall *call)
{
    struct qemu_HeapDestroy *c = (struct qemu_HeapDestroy *)call;
    WINE_TRACE("\n");
    c->super.iret = HeapDestroy((HANDLE)c->heap);
}

#endif

struct qemu_HeapCompact
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI HeapCompact(HANDLE heap, DWORD flags)
{
    struct qemu_HeapCompact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPCOMPACT);
    call.heap = (uint64_t)heap;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapCompact(struct qemu_syscall *call)
{
    struct qemu_HeapCompact *c = (struct qemu_HeapCompact *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HeapCompact(QEMU_G2H(c->heap), c->flags);
}

#endif

struct qemu_HeapValidate
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t block;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapValidate(HANDLE heap, DWORD flags, LPCVOID block)
{
    struct qemu_HeapValidate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPVALIDATE);
    call.heap = (uint64_t)heap;
    call.flags = (uint64_t)flags;
    call.block = (uint64_t)block;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapValidate(struct qemu_syscall *call)
{
    struct qemu_HeapValidate *c = (struct qemu_HeapValidate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HeapValidate(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->block));
}

#endif

struct qemu_HeapWalk
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t entry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapWalk(HANDLE heap, LPPROCESS_HEAP_ENTRY entry)
{
    struct qemu_HeapWalk call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPWALK);
    call.heap = (uint64_t)heap;
    call.entry = (uint64_t)entry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapWalk(struct qemu_syscall *call)
{
    struct qemu_HeapWalk *c = (struct qemu_HeapWalk *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HeapWalk(QEMU_G2H(c->heap), QEMU_G2H(c->entry));
}

#endif

struct qemu_HeapLock
{
    struct qemu_syscall super;
    uint64_t heap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapLock(HANDLE heap)
{
    struct qemu_HeapLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPLOCK);
    call.heap = (uint64_t)heap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapLock(struct qemu_syscall *call)
{
    struct qemu_HeapLock *c = (struct qemu_HeapLock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HeapLock(QEMU_G2H(c->heap));
}

#endif

struct qemu_HeapUnlock
{
    struct qemu_syscall super;
    uint64_t heap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapUnlock(HANDLE heap)
{
    struct qemu_HeapUnlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPUNLOCK);
    call.heap = (uint64_t)heap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapUnlock(struct qemu_syscall *call)
{
    struct qemu_HeapUnlock *c = (struct qemu_HeapUnlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HeapUnlock(QEMU_G2H(c->heap));
}

#endif

struct qemu_GetProcessHeaps
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t heaps;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetProcessHeaps(DWORD count, HANDLE *heaps)
{
    struct qemu_GetProcessHeaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSHEAPS);
    call.count = (uint64_t)count;
    call.heaps = (uint64_t)heaps;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetProcessHeaps(struct qemu_syscall *call)
{
    struct qemu_GetProcessHeaps *c = (struct qemu_GetProcessHeaps *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessHeaps(c->count, QEMU_G2H(c->heaps));
}

#endif

struct qemu_HeapAlloc
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI HeapAlloc(HANDLE heap, DWORD flags, SIZE_T size)
{
    struct qemu_HeapAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPALLOC);
    call.heap = (uint64_t)heap;
    call.flags = (uint64_t)flags;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return (LPVOID)call.super.iret;
}

#else

void qemu_HeapAlloc(struct qemu_syscall *call)
{
    struct qemu_HeapAlloc *c = (struct qemu_HeapAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)HeapAlloc(QEMU_G2H(c->heap), c->flags, c->size);
}

#endif

struct qemu_HeapFree
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapFree(HANDLE heap, DWORD flags, LPVOID ptr)
{
    struct qemu_HeapFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPFREE);
    call.heap = (uint64_t)heap;
    call.flags = (uint64_t)flags;
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapFree(struct qemu_syscall *call)
{
    struct qemu_HeapFree *c = (struct qemu_HeapFree *)call;
    WINE_TRACE("\n");
    c->super.iret = HeapFree(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr));
}

#endif

struct qemu_HeapReAlloc
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI HeapReAlloc(HANDLE heap, DWORD flags, LPVOID ptr, SIZE_T size)
{
    struct qemu_HeapReAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPREALLOC);
    call.heap = (uint64_t)heap;
    call.flags = flags;
    call.ptr = (uint64_t)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return (LPVOID)call.super.iret;
}

#else

void qemu_HeapReAlloc(struct qemu_syscall *call)
{
    struct qemu_HeapReAlloc *c = (struct qemu_HeapReAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)HeapReAlloc(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr), c->size);
}

#endif

struct qemu_HeapSize
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t flags;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI HeapSize(HANDLE heap, DWORD flags, LPCVOID ptr)
{
    struct qemu_HeapSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPSIZE);
    call.heap = (uint64_t)heap;
    call.flags = flags;
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapSize(struct qemu_syscall *call)
{
    struct qemu_HeapSize *c = (struct qemu_HeapSize *)call;
    WINE_TRACE("\n");
    c->super.iret = HeapSize(QEMU_G2H(c->heap), c->flags, QEMU_G2H(c->ptr));
}

#endif

struct qemu_HeapQueryInformation
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t info_class;
    uint64_t info;
    uint64_t size_in;
    uint64_t size_out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapQueryInformation(HANDLE heap, HEAP_INFORMATION_CLASS info_class, PVOID info, SIZE_T size_in, PSIZE_T size_out)
{
    struct qemu_HeapQueryInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPQUERYINFORMATION);
    call.heap = (uint64_t)heap;
    call.info_class = info_class;
    call.info = (uint64_t)info;
    call.size_in = size_in;
    call.size_out = (uint64_t)size_out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapQueryInformation(struct qemu_syscall *call)
{
    struct qemu_HeapQueryInformation *c = (struct qemu_HeapQueryInformation *)call;
    WINE_TRACE("\n");
    c->super.iret = HeapQueryInformation(QEMU_G2H(c->heap), c->info_class, QEMU_G2H(c->info), c->size_in, QEMU_G2H(c->size_out));
}

#endif

struct qemu_HeapSetInformation
{
    struct qemu_syscall super;
    uint64_t heap;
    uint64_t infoclass;
    uint64_t info;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI HeapSetInformation(HANDLE heap, HEAP_INFORMATION_CLASS infoclass, PVOID info, SIZE_T size)
{
    struct qemu_HeapSetInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_HEAPSETINFORMATION);
    call.heap = (uint64_t)heap;
    call.infoclass = (uint64_t)infoclass;
    call.info = (uint64_t)info;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_HeapSetInformation(struct qemu_syscall *call)
{
    struct qemu_HeapSetInformation *c = (struct qemu_HeapSetInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = HeapSetInformation(QEMU_G2H(c->heap), c->infoclass, QEMU_G2H(c->info), c->size);
}

#endif

struct qemu_GlobalAlloc
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLOBAL WINAPI GlobalAlloc(UINT flags, SIZE_T size)
{
    struct qemu_GlobalAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALALLOC);
    call.flags = (uint64_t)flags;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return (HGLOBAL)call.super.iret;
}

#else

void qemu_GlobalAlloc(struct qemu_syscall *call)
{
    struct qemu_GlobalAlloc *c = (struct qemu_GlobalAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GlobalAlloc(c->flags, c->size);
}

#endif

struct qemu_GlobalLock
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI GlobalLock(HGLOBAL hmem)
{
    struct qemu_GlobalLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALLOCK);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return (LPVOID)call.super.iret;
}

#else

void qemu_GlobalLock(struct qemu_syscall *call)
{
    struct qemu_GlobalLock *c = (struct qemu_GlobalLock *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GlobalLock(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalUnlock
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GlobalUnlock(HGLOBAL hmem)
{
    struct qemu_GlobalUnlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALUNLOCK);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalUnlock(struct qemu_syscall *call)
{
    struct qemu_GlobalUnlock *c = (struct qemu_GlobalUnlock *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalUnlock(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalHandle
{
    struct qemu_syscall super;
    uint64_t pmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLOBAL WINAPI GlobalHandle(LPCVOID pmem)
{
    struct qemu_GlobalHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALHANDLE);
    call.pmem = (uint64_t)pmem;

    qemu_syscall(&call.super);

    return (HGLOBAL)call.super.iret;
}

#else

void qemu_GlobalHandle(struct qemu_syscall *call)
{
    struct qemu_GlobalHandle *c = (struct qemu_GlobalHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GlobalHandle(QEMU_G2H(c->pmem));
}

#endif

struct qemu_GlobalReAlloc
{
    struct qemu_syscall super;
    uint64_t hmem;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hmem, SIZE_T size, UINT flags)
{
    struct qemu_GlobalReAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALREALLOC);
    call.hmem = (uint64_t)hmem;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (HGLOBAL)call.super.iret;
}

#else

void qemu_GlobalReAlloc(struct qemu_syscall *call)
{
    struct qemu_GlobalReAlloc *c = (struct qemu_GlobalReAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GlobalReAlloc(QEMU_G2H(c->hmem), c->size, c->flags);
}

#endif

struct qemu_GlobalFree
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLOBAL WINAPI GlobalFree(HGLOBAL hmem)
{
    struct qemu_GlobalFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALFREE);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return (HGLOBAL)call.super.iret;
}

#else

void qemu_GlobalFree(struct qemu_syscall *call)
{
    struct qemu_GlobalFree *c = (struct qemu_GlobalFree *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GlobalFree(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalSize
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI GlobalSize(HGLOBAL hmem)
{
    struct qemu_GlobalSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALSIZE);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalSize(struct qemu_syscall *call)
{
    struct qemu_GlobalSize *c = (struct qemu_GlobalSize *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalSize(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalWire
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI GlobalWire(HGLOBAL hmem)
{
    struct qemu_GlobalWire call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALWIRE);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return (LPVOID)call.super.iret;
}

#else

void qemu_GlobalWire(struct qemu_syscall *call)
{
    struct qemu_GlobalWire *c = (struct qemu_GlobalWire *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GlobalWire(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalUnWire
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GlobalUnWire(HGLOBAL hmem)
{
    struct qemu_GlobalUnWire call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALUNWIRE);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalUnWire(struct qemu_syscall *call)
{
    struct qemu_GlobalUnWire *c = (struct qemu_GlobalUnWire *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GlobalUnWire(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalFix
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GlobalFix(HGLOBAL hmem)
{
    struct qemu_GlobalFix call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALFIX);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);
}

#else

void qemu_GlobalFix(struct qemu_syscall *call)
{
    struct qemu_GlobalFix *c = (struct qemu_GlobalFix *)call;
    WINE_FIXME("Unverified!\n");
    GlobalFix(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalUnfix
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GlobalUnfix(HGLOBAL hmem)
{
    struct qemu_GlobalUnfix call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALUNFIX);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);
}

#else

void qemu_GlobalUnfix(struct qemu_syscall *call)
{
    struct qemu_GlobalUnfix *c = (struct qemu_GlobalUnfix *)call;
    WINE_FIXME("Unverified!\n");
    GlobalUnfix(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalFlags
{
    struct qemu_syscall super;
    uint64_t hmem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GlobalFlags(HGLOBAL hmem)
{
    struct qemu_GlobalFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALFLAGS);
    call.hmem = (uint64_t)hmem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalFlags(struct qemu_syscall *call)
{
    struct qemu_GlobalFlags *c = (struct qemu_GlobalFlags *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalFlags(QEMU_G2H(c->hmem));
}

#endif

struct qemu_GlobalCompact
{
    struct qemu_syscall super;
    uint64_t minfree;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI GlobalCompact(DWORD minfree)
{
    struct qemu_GlobalCompact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALCOMPACT);
    call.minfree = (uint64_t)minfree;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalCompact(struct qemu_syscall *call)
{
    struct qemu_GlobalCompact *c = (struct qemu_GlobalCompact *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GlobalCompact(c->minfree);
}

#endif

struct qemu_LocalAlloc
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HLOCAL WINAPI LocalAlloc(UINT flags, SIZE_T size)
{
    struct qemu_LocalAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALALLOC);
    call.flags = flags;
    call.size = size;

    qemu_syscall(&call.super);

    return (HLOCAL)call.super.iret;
}

#else

void qemu_LocalAlloc(struct qemu_syscall *call)
{
    struct qemu_LocalAlloc *c = (struct qemu_LocalAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)LocalAlloc(c->flags, c->size);
}

#endif

struct qemu_LocalCompact
{
    struct qemu_syscall super;
    uint64_t minfree;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI LocalCompact(UINT minfree)
{
    struct qemu_LocalCompact call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALCOMPACT);
    call.minfree = (uint64_t)minfree;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocalCompact(struct qemu_syscall *call)
{
    struct qemu_LocalCompact *c = (struct qemu_LocalCompact *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LocalCompact(c->minfree);
}

#endif

struct qemu_LocalFlags
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI LocalFlags(HLOCAL handle)
{
    struct qemu_LocalFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALFLAGS);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocalFlags(struct qemu_syscall *call)
{
    struct qemu_LocalFlags *c = (struct qemu_LocalFlags *)call;
    WINE_TRACE("\n");
    c->super.iret = LocalFlags(QEMU_G2H(c->handle));
}

#endif

struct qemu_LocalFree
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HLOCAL WINAPI LocalFree(HLOCAL handle)
{
    struct qemu_LocalFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALFREE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return (HLOCAL)call.super.iret;
}

#else

void qemu_LocalFree(struct qemu_syscall *call)
{
    struct qemu_LocalFree *c = (struct qemu_LocalFree *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)LocalFree(QEMU_G2H(c->handle));
}

#endif

struct qemu_LocalHandle
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HLOCAL WINAPI LocalHandle(LPCVOID ptr)
{
    struct qemu_LocalHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALHANDLE);
    call.ptr = (uint64_t)ptr;

    qemu_syscall(&call.super);

    return (HLOCAL)call.super.iret;
}

#else

void qemu_LocalHandle(struct qemu_syscall *call)
{
    struct qemu_LocalHandle *c = (struct qemu_LocalHandle *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)LocalHandle(QEMU_G2H(c->ptr));
}

#endif

struct qemu_LocalLock
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI LocalLock(HLOCAL handle)
{
    struct qemu_LocalLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALLOCK);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return (LPVOID)call.super.iret;
}

#else

void qemu_LocalLock(struct qemu_syscall *call)
{
    struct qemu_LocalLock *c = (struct qemu_LocalLock *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)LocalLock((HLOCAL)c->handle);
}

#endif

struct qemu_LocalReAlloc
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HLOCAL WINAPI LocalReAlloc(HLOCAL handle, SIZE_T size, UINT flags)
{
    struct qemu_LocalReAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALREALLOC);
    call.handle = (uint64_t)handle;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (HLOCAL)call.super.iret;
}

#else

void qemu_LocalReAlloc(struct qemu_syscall *call)
{
    struct qemu_LocalReAlloc *c = (struct qemu_LocalReAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)LocalReAlloc(QEMU_G2H(c->handle), c->size, c->flags);
}

#endif

struct qemu_LocalShrink
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t newsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI LocalShrink(HGLOBAL handle, UINT newsize)
{
    struct qemu_LocalShrink call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALSHRINK);
    call.handle = (uint64_t)handle;
    call.newsize = (uint64_t)newsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocalShrink(struct qemu_syscall *call)
{
    struct qemu_LocalShrink *c = (struct qemu_LocalShrink *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LocalShrink(QEMU_G2H(c->handle), c->newsize);
}

#endif

struct qemu_LocalSize
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI LocalSize(HLOCAL handle)
{
    struct qemu_LocalSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALSIZE);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocalSize(struct qemu_syscall *call)
{
    struct qemu_LocalSize *c = (struct qemu_LocalSize *)call;
    WINE_TRACE("\n");
    c->super.iret = LocalSize(QEMU_G2H(c->handle));
}

#endif

struct qemu_LocalUnlock
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LocalUnlock(HLOCAL handle)
{
    struct qemu_LocalUnlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCALUNLOCK);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LocalUnlock(struct qemu_syscall *call)
{
    struct qemu_LocalUnlock *c = (struct qemu_LocalUnlock *)call;
    WINE_TRACE("\n");
    c->super.iret = LocalUnlock(QEMU_G2H(c->handle));
}

#endif

struct qemu_GlobalMemoryStatusEx
{
    struct qemu_syscall super;
    uint64_t lpmemex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpmemex)
{
    struct qemu_GlobalMemoryStatusEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALMEMORYSTATUSEX);
    call.lpmemex = (uint64_t)lpmemex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalMemoryStatusEx(struct qemu_syscall *call)
{
    struct qemu_GlobalMemoryStatusEx *c = (struct qemu_GlobalMemoryStatusEx *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalMemoryStatusEx(QEMU_G2H(c->lpmemex));
}

#endif

struct qemu_GlobalMemoryStatus
{
    struct qemu_syscall super;
    uint64_t lpBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer)
{
    struct qemu_GlobalMemoryStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALMEMORYSTATUS);
    call.lpBuffer = (uint64_t)lpBuffer;

    qemu_syscall(&call.super);
}

#else

void qemu_GlobalMemoryStatus(struct qemu_syscall *call)
{
    struct qemu_GlobalMemoryStatus *c = (struct qemu_GlobalMemoryStatus *)call;
    WINE_FIXME("Unverified!\n");
    GlobalMemoryStatus(QEMU_G2H(c->lpBuffer));
}

#endif

struct qemu_GetPhysicallyInstalledSystemMemory
{
    struct qemu_syscall super;
    uint64_t total_memory;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPhysicallyInstalledSystemMemory(ULONGLONG *total_memory)
{
    struct qemu_GetPhysicallyInstalledSystemMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPHYSICALLYINSTALLEDSYSTEMMEMORY);
    call.total_memory = (uint64_t)total_memory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetPhysicallyInstalledSystemMemory to Wine headers? */
extern BOOL WINAPI GetPhysicallyInstalledSystemMemory(ULONGLONG *total_memory);
void qemu_GetPhysicallyInstalledSystemMemory(struct qemu_syscall *call)
{
    struct qemu_GetPhysicallyInstalledSystemMemory *c = (struct qemu_GetPhysicallyInstalledSystemMemory *)call;
    WINE_TRACE("\n");
    c->super.iret = GetPhysicallyInstalledSystemMemory(QEMU_G2H(c->total_memory));
}

#endif

struct qemu_GetSystemFileCacheSize
{
    struct qemu_syscall super;
    uint64_t mincache;
    uint64_t maxcache;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetSystemFileCacheSize(PSIZE_T mincache, PSIZE_T maxcache, PDWORD flags)
{
    struct qemu_GetSystemFileCacheSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMFILECACHESIZE);
    call.mincache = (uint64_t)mincache;
    call.maxcache = (uint64_t)maxcache;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetSystemFileCacheSize to Wine headers? */
extern BOOL WINAPI GetSystemFileCacheSize(PSIZE_T mincache, PSIZE_T maxcache, PDWORD flags);
void qemu_GetSystemFileCacheSize(struct qemu_syscall *call)
{
    struct qemu_GetSystemFileCacheSize *c = (struct qemu_GetSystemFileCacheSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemFileCacheSize(QEMU_G2H(c->mincache), QEMU_G2H(c->maxcache), QEMU_G2H(c->flags));
}

#endif

struct qemu_SetSystemFileCacheSize
{
    struct qemu_syscall super;
    uint64_t mincache;
    uint64_t maxcache;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetSystemFileCacheSize(SIZE_T mincache, SIZE_T maxcache, DWORD flags)
{
    struct qemu_SetSystemFileCacheSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSTEMFILECACHESIZE);
    call.mincache = (uint64_t)mincache;
    call.maxcache = (uint64_t)maxcache;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetSystemFileCacheSize to Wine headers? */
extern BOOL WINAPI SetSystemFileCacheSize(SIZE_T mincache, SIZE_T maxcache, DWORD flags);
void qemu_SetSystemFileCacheSize(struct qemu_syscall *call)
{
    struct qemu_SetSystemFileCacheSize *c = (struct qemu_SetSystemFileCacheSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSystemFileCacheSize(c->mincache, c->maxcache, c->flags);
}

#endif

struct qemu_AllocateUserPhysicalPages
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t pages;
    uint64_t userarray;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AllocateUserPhysicalPages(HANDLE process, ULONG_PTR *pages, ULONG_PTR *userarray)
{
    struct qemu_AllocateUserPhysicalPages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALLOCATEUSERPHYSICALPAGES);
    call.process = (uint64_t)process;
    call.pages = (uint64_t)pages;
    call.userarray = (uint64_t)userarray;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AllocateUserPhysicalPages to Wine headers? */
extern BOOL WINAPI AllocateUserPhysicalPages(HANDLE process, ULONG_PTR *pages, ULONG_PTR *userarray);
void qemu_AllocateUserPhysicalPages(struct qemu_syscall *call)
{
    struct qemu_AllocateUserPhysicalPages *c = (struct qemu_AllocateUserPhysicalPages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AllocateUserPhysicalPages(QEMU_G2H(c->process), QEMU_G2H(c->pages), QEMU_G2H(c->userarray));
}

#endif

struct qemu_FreeUserPhysicalPages
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t pages;
    uint64_t userarray;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeUserPhysicalPages(HANDLE process, ULONG_PTR *pages, ULONG_PTR *userarray)
{
    struct qemu_FreeUserPhysicalPages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEUSERPHYSICALPAGES);
    call.process = (uint64_t)process;
    call.pages = (uint64_t)pages;
    call.userarray = (uint64_t)userarray;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add FreeUserPhysicalPages to Wine headers? */
extern BOOL WINAPI FreeUserPhysicalPages(HANDLE process, ULONG_PTR *pages, ULONG_PTR *userarray);
void qemu_FreeUserPhysicalPages(struct qemu_syscall *call)
{
    struct qemu_FreeUserPhysicalPages *c = (struct qemu_FreeUserPhysicalPages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeUserPhysicalPages(QEMU_G2H(c->process), QEMU_G2H(c->pages), QEMU_G2H(c->userarray));
}

#endif

