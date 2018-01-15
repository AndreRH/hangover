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
typedef void *LPRTL_RWLOCK, *PRTL_AVL_TABLE, *PRTL_AVL_COMPARE_ROUTINE, *PRTL_AVL_ALLOCATE_ROUTINE;
typedef void RTL_USER_PROCESS_INFORMATION, *PRTL_AVL_FREE_ROUTINE;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif


struct qemu_RtlInitializeResource
{
    struct qemu_syscall super;
    uint64_t rwl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitializeResource(LPRTL_RWLOCK rwl)
{
    struct qemu_RtlInitializeResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZERESOURCE);
    call.rwl = (ULONG_PTR)rwl;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitializeResource(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeResource *c = (struct qemu_RtlInitializeResource *)call;
    WINE_FIXME("Unverified!\n");
    RtlInitializeResource(QEMU_G2H(c->rwl));
}

#endif

struct qemu_RtlDeleteResource
{
    struct qemu_syscall super;
    uint64_t rwl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlDeleteResource(LPRTL_RWLOCK rwl)
{
    struct qemu_RtlDeleteResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETERESOURCE);
    call.rwl = (ULONG_PTR)rwl;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlDeleteResource(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteResource *c = (struct qemu_RtlDeleteResource *)call;
    WINE_FIXME("Unverified!\n");
    RtlDeleteResource(QEMU_G2H(c->rwl));
}

#endif

struct qemu_RtlAcquireResourceExclusive
{
    struct qemu_syscall super;
    uint64_t rwl;
    uint64_t fWait;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BYTE WINAPI RtlAcquireResourceExclusive(LPRTL_RWLOCK rwl, BYTE fWait)
{
    struct qemu_RtlAcquireResourceExclusive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLACQUIRERESOURCEEXCLUSIVE);
    call.rwl = (ULONG_PTR)rwl;
    call.fWait = (ULONG_PTR)fWait;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAcquireResourceExclusive(struct qemu_syscall *call)
{
    struct qemu_RtlAcquireResourceExclusive *c = (struct qemu_RtlAcquireResourceExclusive *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAcquireResourceExclusive(QEMU_G2H(c->rwl), c->fWait);
}

#endif

struct qemu_RtlAcquireResourceShared
{
    struct qemu_syscall super;
    uint64_t rwl;
    uint64_t fWait;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BYTE WINAPI RtlAcquireResourceShared(LPRTL_RWLOCK rwl, BYTE fWait)
{
    struct qemu_RtlAcquireResourceShared call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLACQUIRERESOURCESHARED);
    call.rwl = (ULONG_PTR)rwl;
    call.fWait = (ULONG_PTR)fWait;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAcquireResourceShared(struct qemu_syscall *call)
{
    struct qemu_RtlAcquireResourceShared *c = (struct qemu_RtlAcquireResourceShared *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAcquireResourceShared(QEMU_G2H(c->rwl), c->fWait);
}

#endif

struct qemu_RtlReleaseResource
{
    struct qemu_syscall super;
    uint64_t rwl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlReleaseResource(LPRTL_RWLOCK rwl)
{
    struct qemu_RtlReleaseResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRELEASERESOURCE);
    call.rwl = (ULONG_PTR)rwl;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlReleaseResource(struct qemu_syscall *call)
{
    struct qemu_RtlReleaseResource *c = (struct qemu_RtlReleaseResource *)call;
    WINE_FIXME("Unverified!\n");
    RtlReleaseResource(QEMU_G2H(c->rwl));
}

#endif

struct qemu_RtlDumpResource
{
    struct qemu_syscall super;
    uint64_t rwl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlDumpResource(LPRTL_RWLOCK rwl)
{
    struct qemu_RtlDumpResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDUMPRESOURCE);
    call.rwl = (ULONG_PTR)rwl;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlDumpResource(struct qemu_syscall *call)
{
    struct qemu_RtlDumpResource *c = (struct qemu_RtlDumpResource *)call;
    WINE_FIXME("Unverified!\n");
    RtlDumpResource(QEMU_G2H(c->rwl));
}

#endif

struct qemu_RtlAcquirePebLock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlAcquirePebLock(void)
{
    struct qemu_RtlAcquirePebLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLACQUIREPEBLOCK);

    qemu_syscall(&call.super);
}

#else

void qemu_RtlAcquirePebLock(struct qemu_syscall *call)
{
    struct qemu_RtlAcquirePebLock *c = (struct qemu_RtlAcquirePebLock *)call;
    WINE_FIXME("Unverified!\n");
    RtlAcquirePebLock();
}

#endif

struct qemu_RtlReleasePebLock
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlReleasePebLock(void)
{
    struct qemu_RtlReleasePebLock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRELEASEPEBLOCK);

    qemu_syscall(&call.super);
}

#else

void qemu_RtlReleasePebLock(struct qemu_syscall *call)
{
    struct qemu_RtlReleasePebLock *c = (struct qemu_RtlReleasePebLock *)call;
    WINE_FIXME("Unverified!\n");
    RtlReleasePebLock();
}

#endif

struct qemu_RtlNewSecurityObject
{
    struct qemu_syscall super;
    uint64_t ParentDescriptor;
    uint64_t CreatorDescriptor;
    uint64_t NewDescriptor;
    uint64_t IsDirectoryObject;
    uint64_t Token;
    uint64_t GenericMapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlNewSecurityObject(PSECURITY_DESCRIPTOR ParentDescriptor, PSECURITY_DESCRIPTOR CreatorDescriptor, PSECURITY_DESCRIPTOR *NewDescriptor, BOOLEAN IsDirectoryObject, HANDLE Token, PGENERIC_MAPPING GenericMapping)
{
    struct qemu_RtlNewSecurityObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNEWSECURITYOBJECT);
    call.ParentDescriptor = (ULONG_PTR)ParentDescriptor;
    call.CreatorDescriptor = (ULONG_PTR)CreatorDescriptor;
    call.NewDescriptor = (ULONG_PTR)NewDescriptor;
    call.IsDirectoryObject = (ULONG_PTR)IsDirectoryObject;
    call.Token = (ULONG_PTR)Token;
    call.GenericMapping = (ULONG_PTR)GenericMapping;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlNewSecurityObject(struct qemu_syscall *call)
{
    struct qemu_RtlNewSecurityObject *c = (struct qemu_RtlNewSecurityObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlNewSecurityObject(QEMU_G2H(c->ParentDescriptor), QEMU_G2H(c->CreatorDescriptor), QEMU_G2H(c->NewDescriptor), c->IsDirectoryObject, QEMU_G2H(c->Token), QEMU_G2H(c->GenericMapping));
}

#endif

struct qemu_RtlDeleteSecurityObject
{
    struct qemu_syscall super;
    uint64_t ObjectDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDeleteSecurityObject(PSECURITY_DESCRIPTOR *ObjectDescriptor)
{
    struct qemu_RtlDeleteSecurityObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDELETESECURITYOBJECT);
    call.ObjectDescriptor = (ULONG_PTR)ObjectDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDeleteSecurityObject(struct qemu_syscall *call)
{
    struct qemu_RtlDeleteSecurityObject *c = (struct qemu_RtlDeleteSecurityObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDeleteSecurityObject(QEMU_G2H(c->ObjectDescriptor));
}

#endif

struct qemu_RtlInitializeGenericTable
{
    struct qemu_syscall super;
    uint64_t pTable;
    uint64_t arg2;
    uint64_t arg3;
    uint64_t arg4;
    uint64_t arg5;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI RtlInitializeGenericTable(PVOID pTable, PVOID arg2, PVOID arg3, PVOID arg4, PVOID arg5)
{
    struct qemu_RtlInitializeGenericTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZEGENERICTABLE);
    call.pTable = (ULONG_PTR)pTable;
    call.arg2 = (ULONG_PTR)arg2;
    call.arg3 = (ULONG_PTR)arg3;
    call.arg4 = (ULONG_PTR)arg4;
    call.arg5 = (ULONG_PTR)arg5;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add RtlInitializeGenericTable to Wine headers? */
extern PVOID WINAPI RtlInitializeGenericTable(PVOID pTable, PVOID arg2, PVOID arg3, PVOID arg4, PVOID arg5);
void qemu_RtlInitializeGenericTable(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeGenericTable *c = (struct qemu_RtlInitializeGenericTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RtlInitializeGenericTable(QEMU_G2H(c->pTable), QEMU_G2H(c->arg2), QEMU_G2H(c->arg3), QEMU_G2H(c->arg4), QEMU_G2H(c->arg5));
}

#endif

struct qemu_RtlZeroMemory
{
    struct qemu_syscall super;
    uint64_t Destination;
    uint64_t Length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI ntdll_RtlZeroMemory(VOID *Destination, SIZE_T Length)
{
    struct qemu_RtlZeroMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLZEROMEMORY);
    call.Destination = (ULONG_PTR)Destination;
    call.Length = (ULONG_PTR)Length;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlZeroMemory(struct qemu_syscall *call)
{
    struct qemu_RtlZeroMemory *c = (struct qemu_RtlZeroMemory *)call;
    WINE_FIXME("Unverified!\n");
    RtlZeroMemory(QEMU_G2H(c->Destination), c->Length);
}

#endif

struct qemu_RtlMoveMemory
{
    struct qemu_syscall super;
    uint64_t Destination;
    uint64_t Source;
    uint64_t Length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI ntdll_RtlMoveMemory(void *Destination, const void *Source, SIZE_T Length)
{
    struct qemu_RtlMoveMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMOVEMEMORY);
    call.Destination = (ULONG_PTR)Destination;
    call.Source = (ULONG_PTR)Source;
    call.Length = (ULONG_PTR)Length;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlMoveMemory(struct qemu_syscall *call)
{
    struct qemu_RtlMoveMemory *c = (struct qemu_RtlMoveMemory *)call;
    WINE_FIXME("Unverified!\n");
    RtlMoveMemory(QEMU_G2H(c->Destination), QEMU_G2H(c->Source), c->Length);
}

#endif

struct qemu_RtlCopyMemory
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ntdll_RtlCopyMemory(void *dest, const void *src, SIZE_T len)
{
    struct qemu_RtlCopyMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYMEMORY);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlCopyMemory(struct qemu_syscall *call)
{
    struct qemu_RtlCopyMemory *c = (struct qemu_RtlCopyMemory *)call;
    WINE_FIXME("Unverified!\n");
    RtlCopyMemory(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->len);
}

#endif

struct qemu_RtlFillMemory
{
    struct qemu_syscall super;
    uint64_t Destination;
    uint64_t Length;
    uint64_t Fill;
};

#ifdef QEMU_DLL_GUEST

void WINAPI ntdll_RtlFillMemory(VOID *Destination, SIZE_T Length, BYTE Fill)
{
    struct qemu_RtlFillMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFILLMEMORY);
    call.Destination = (ULONG_PTR)Destination;
    call.Length = (ULONG_PTR)Length;
    call.Fill = (ULONG_PTR)Fill;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlFillMemory(struct qemu_syscall *call)
{
    struct qemu_RtlFillMemory *c = (struct qemu_RtlFillMemory *)call;
    WINE_FIXME("Unverified!\n");
    RtlFillMemory(QEMU_G2H(c->Destination), c->Length, c->Fill);
}

#endif

struct qemu_RtlCompareMemory
{
    struct qemu_syscall super;
    uint64_t Source1;
    uint64_t Source2;
    uint64_t Length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI RtlCompareMemory(const void *Source1, const void *Source2, SIZE_T Length)
{
    struct qemu_RtlCompareMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPAREMEMORY);
    call.Source1 = (ULONG_PTR)Source1;
    call.Source2 = (ULONG_PTR)Source2;
    call.Length = (ULONG_PTR)Length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlCompareMemory to Wine headers? */
extern SIZE_T WINAPI RtlCompareMemory(const void *Source1, const void *Source2, SIZE_T Length);
void qemu_RtlCompareMemory(struct qemu_syscall *call)
{
    struct qemu_RtlCompareMemory *c = (struct qemu_RtlCompareMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompareMemory(QEMU_G2H(c->Source1), QEMU_G2H(c->Source2), c->Length);
}

#endif

struct qemu_RtlCompareMemoryUlong
{
    struct qemu_syscall super;
    uint64_t Source1;
    uint64_t Length;
    uint64_t dwVal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SIZE_T WINAPI RtlCompareMemoryUlong(const ULONG *Source1, SIZE_T Length, ULONG dwVal)
{
    struct qemu_RtlCompareMemoryUlong call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPAREMEMORYULONG);
    call.Source1 = (ULONG_PTR)Source1;
    call.Length = (ULONG_PTR)Length;
    call.dwVal = (ULONG_PTR)dwVal;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlCompareMemoryUlong to Wine headers? */
extern SIZE_T WINAPI RtlCompareMemoryUlong(const ULONG *Source1, SIZE_T Length, ULONG dwVal);
void qemu_RtlCompareMemoryUlong(struct qemu_syscall *call)
{
    struct qemu_RtlCompareMemoryUlong *c = (struct qemu_RtlCompareMemoryUlong *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompareMemoryUlong(QEMU_G2H(c->Source1), c->Length, c->dwVal);
}

#endif

struct qemu_RtlAssert
{
    struct qemu_syscall super;
    uint64_t assertion;
    uint64_t filename;
    uint64_t linenumber;
    uint64_t message;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlAssert(void *assertion, void *filename, ULONG linenumber, char *message)
{
    struct qemu_RtlAssert call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLASSERT);
    call.assertion = (ULONG_PTR)assertion;
    call.filename = (ULONG_PTR)filename;
    call.linenumber = (ULONG_PTR)linenumber;
    call.message = (ULONG_PTR)message;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add RtlAssert to Wine headers? */
extern void WINAPI RtlAssert(void *assertion, void *filename, ULONG linenumber, char *message);
void qemu_RtlAssert(struct qemu_syscall *call)
{
    struct qemu_RtlAssert *c = (struct qemu_RtlAssert *)call;
    WINE_FIXME("Unverified!\n");
    RtlAssert(QEMU_G2H(c->assertion), QEMU_G2H(c->filename), c->linenumber, QEMU_G2H(c->message));
}

#endif

struct qemu_RtlFillMemoryUlong
{
    struct qemu_syscall super;
    uint64_t lpDest;
    uint64_t ulCount;
    uint64_t ulValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlFillMemoryUlong(ULONG* lpDest, ULONG ulCount, ULONG ulValue)
{
    struct qemu_RtlFillMemoryUlong call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFILLMEMORYULONG);
    call.lpDest = (ULONG_PTR)lpDest;
    call.ulCount = (ULONG_PTR)ulCount;
    call.ulValue = (ULONG_PTR)ulValue;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add RtlFillMemoryUlong to Wine headers? */
extern void WINAPI RtlFillMemoryUlong(ULONG* lpDest, ULONG ulCount, ULONG ulValue);
void qemu_RtlFillMemoryUlong(struct qemu_syscall *call)
{
    struct qemu_RtlFillMemoryUlong *c = (struct qemu_RtlFillMemoryUlong *)call;
    WINE_FIXME("Unverified!\n");
    RtlFillMemoryUlong(QEMU_G2H(c->lpDest), c->ulCount, c->ulValue);
}

#endif

struct qemu_RtlComputeCrc32
{
    struct qemu_syscall super;
    uint64_t dwInitial;
    uint64_t pData;
    uint64_t iLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlComputeCrc32(DWORD dwInitial, const BYTE *pData, INT iLen)
{
    struct qemu_RtlComputeCrc32 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPUTECRC32);
    call.dwInitial = (ULONG_PTR)dwInitial;
    call.pData = (ULONG_PTR)pData;
    call.iLen = (ULONG_PTR)iLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlComputeCrc32(struct qemu_syscall *call)
{
    struct qemu_RtlComputeCrc32 *c = (struct qemu_RtlComputeCrc32 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlComputeCrc32(c->dwInitial, QEMU_G2H(c->pData), c->iLen);
}

#endif

struct qemu_RtlUniform
{
    struct qemu_syscall super;
    uint64_t seed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlUniform (PULONG seed)
{
    struct qemu_RtlUniform call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNIFORM);
    call.seed = (ULONG_PTR)seed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUniform(struct qemu_syscall *call)
{
    struct qemu_RtlUniform *c = (struct qemu_RtlUniform *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUniform(QEMU_G2H(c->seed));
}

#endif

struct qemu_RtlRandom
{
    struct qemu_syscall super;
    uint64_t seed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI RtlRandom (PULONG seed)
{
    struct qemu_RtlRandom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRANDOM);
    call.seed = (ULONG_PTR)seed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlRandom(struct qemu_syscall *call)
{
    struct qemu_RtlRandom *c = (struct qemu_RtlRandom *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlRandom(QEMU_G2H(c->seed));
}

#endif

struct qemu_RtlAreAllAccessesGranted
{
    struct qemu_syscall super;
    uint64_t GrantedAccess;
    uint64_t DesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlAreAllAccessesGranted(ACCESS_MASK GrantedAccess, ACCESS_MASK DesiredAccess)
{
    struct qemu_RtlAreAllAccessesGranted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAREALLACCESSESGRANTED);
    call.GrantedAccess = (ULONG_PTR)GrantedAccess;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAreAllAccessesGranted(struct qemu_syscall *call)
{
    struct qemu_RtlAreAllAccessesGranted *c = (struct qemu_RtlAreAllAccessesGranted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAreAllAccessesGranted(c->GrantedAccess, c->DesiredAccess);
}

#endif

struct qemu_RtlAreAnyAccessesGranted
{
    struct qemu_syscall super;
    uint64_t GrantedAccess;
    uint64_t DesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlAreAnyAccessesGranted(ACCESS_MASK GrantedAccess, ACCESS_MASK DesiredAccess)
{
    struct qemu_RtlAreAnyAccessesGranted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAREANYACCESSESGRANTED);
    call.GrantedAccess = (ULONG_PTR)GrantedAccess;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAreAnyAccessesGranted(struct qemu_syscall *call)
{
    struct qemu_RtlAreAnyAccessesGranted *c = (struct qemu_RtlAreAnyAccessesGranted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAreAnyAccessesGranted(c->GrantedAccess, c->DesiredAccess);
}

#endif

struct qemu_RtlMapGenericMask
{
    struct qemu_syscall super;
    uint64_t AccessMask;
    uint64_t GenericMapping;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlMapGenericMask(PACCESS_MASK AccessMask, const GENERIC_MAPPING *GenericMapping)
{
    struct qemu_RtlMapGenericMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMAPGENERICMASK);
    call.AccessMask = (ULONG_PTR)AccessMask;
    call.GenericMapping = (ULONG_PTR)GenericMapping;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlMapGenericMask(struct qemu_syscall *call)
{
    struct qemu_RtlMapGenericMask *c = (struct qemu_RtlMapGenericMask *)call;
    WINE_FIXME("Unverified!\n");
    RtlMapGenericMask(QEMU_G2H(c->AccessMask), QEMU_G2H(c->GenericMapping));
}

#endif

struct qemu_RtlCopyLuid
{
    struct qemu_syscall super;
    uint64_t LuidDest;
    uint64_t LuidSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlCopyLuid (PLUID LuidDest, const LUID *LuidSrc)
{
    struct qemu_RtlCopyLuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYLUID);
    call.LuidDest = (ULONG_PTR)LuidDest;
    call.LuidSrc = (ULONG_PTR)LuidSrc;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlCopyLuid(struct qemu_syscall *call)
{
    struct qemu_RtlCopyLuid *c = (struct qemu_RtlCopyLuid *)call;
    WINE_FIXME("Unverified!\n");
    RtlCopyLuid(QEMU_G2H(c->LuidDest), QEMU_G2H(c->LuidSrc));
}

#endif

struct qemu_RtlEqualLuid
{
    struct qemu_syscall super;
    uint64_t Luid1;
    uint64_t Luid2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlEqualLuid (const LUID *Luid1, const LUID *Luid2)
{
    struct qemu_RtlEqualLuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALLUID);
    call.Luid1 = (ULONG_PTR)Luid1;
    call.Luid2 = (ULONG_PTR)Luid2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualLuid(struct qemu_syscall *call)
{
    struct qemu_RtlEqualLuid *c = (struct qemu_RtlEqualLuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualLuid(QEMU_G2H(c->Luid1), QEMU_G2H(c->Luid2));
}

#endif

struct qemu_RtlCopyLuidAndAttributesArray
{
    struct qemu_syscall super;
    uint64_t Count;
    uint64_t Src;
    uint64_t Dest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlCopyLuidAndAttributesArray(ULONG Count, const LUID_AND_ATTRIBUTES *Src, PLUID_AND_ATTRIBUTES Dest)
{
    struct qemu_RtlCopyLuidAndAttributesArray call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYLUIDANDATTRIBUTESARRAY);
    call.Count = (ULONG_PTR)Count;
    call.Src = (ULONG_PTR)Src;
    call.Dest = (ULONG_PTR)Dest;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlCopyLuidAndAttributesArray(struct qemu_syscall *call)
{
    struct qemu_RtlCopyLuidAndAttributesArray *c = (struct qemu_RtlCopyLuidAndAttributesArray *)call;
    WINE_FIXME("Unverified!\n");
    RtlCopyLuidAndAttributesArray(c->Count, QEMU_G2H(c->Src), QEMU_G2H(c->Dest));
}

#endif

struct qemu_RtlIpv4StringToAddressExW
{
    struct qemu_syscall super;
    uint64_t IP;
    uint64_t Port;
    uint64_t Buffer;
    uint64_t MaxSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIpv4StringToAddressExW(PULONG IP, PULONG Port, LPCWSTR Buffer, PULONG MaxSize)
{
    struct qemu_RtlIpv4StringToAddressExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIPV4STRINGTOADDRESSEXW);
    call.IP = (ULONG_PTR)IP;
    call.Port = (ULONG_PTR)Port;
    call.Buffer = (ULONG_PTR)Buffer;
    call.MaxSize = (ULONG_PTR)MaxSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlIpv4StringToAddressExW to Wine headers? */
extern NTSTATUS WINAPI RtlIpv4StringToAddressExW(PULONG IP, PULONG Port, LPCWSTR Buffer, PULONG MaxSize);
void qemu_RtlIpv4StringToAddressExW(struct qemu_syscall *call)
{
    struct qemu_RtlIpv4StringToAddressExW *c = (struct qemu_RtlIpv4StringToAddressExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIpv4StringToAddressExW(QEMU_G2H(c->IP), QEMU_G2H(c->Port), QEMU_G2H(c->Buffer), QEMU_G2H(c->MaxSize));
}

#endif

struct qemu_RtlIpv4AddressToStringExW
{
    struct qemu_syscall super;
    uint64_t pin;
    uint64_t port;
    uint64_t buffer;
    uint64_t psize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIpv4AddressToStringExW(const IN_ADDR *pin, USHORT port, LPWSTR buffer, PULONG psize)
{
    struct qemu_RtlIpv4AddressToStringExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIPV4ADDRESSTOSTRINGEXW);
    call.pin = (ULONG_PTR)pin;
    call.port = (ULONG_PTR)port;
    call.buffer = (ULONG_PTR)buffer;
    call.psize = (ULONG_PTR)psize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlIpv4AddressToStringExW to Wine headers? */
extern NTSTATUS WINAPI RtlIpv4AddressToStringExW(const IN_ADDR *pin, USHORT port, LPWSTR buffer, PULONG psize);
void qemu_RtlIpv4AddressToStringExW(struct qemu_syscall *call)
{
    struct qemu_RtlIpv4AddressToStringExW *c = (struct qemu_RtlIpv4AddressToStringExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIpv4AddressToStringExW(QEMU_G2H(c->pin), c->port, QEMU_G2H(c->buffer), QEMU_G2H(c->psize));
}

#endif

struct qemu_RtlIpv4AddressToStringExA
{
    struct qemu_syscall super;
    uint64_t pin;
    uint64_t port;
    uint64_t buffer;
    uint64_t psize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIpv4AddressToStringExA(const IN_ADDR *pin, USHORT port, LPSTR buffer, PULONG psize)
{
    struct qemu_RtlIpv4AddressToStringExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIPV4ADDRESSTOSTRINGEXA);
    call.pin = (ULONG_PTR)pin;
    call.port = (ULONG_PTR)port;
    call.buffer = (ULONG_PTR)buffer;
    call.psize = (ULONG_PTR)psize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlIpv4AddressToStringExA to Wine headers? */
extern NTSTATUS WINAPI RtlIpv4AddressToStringExA(const IN_ADDR *pin, USHORT port, LPSTR buffer, PULONG psize);
void qemu_RtlIpv4AddressToStringExA(struct qemu_syscall *call)
{
    struct qemu_RtlIpv4AddressToStringExA *c = (struct qemu_RtlIpv4AddressToStringExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIpv4AddressToStringExA(QEMU_G2H(c->pin), c->port, QEMU_G2H(c->buffer), QEMU_G2H(c->psize));
}

#endif

struct qemu_RtlIpv4AddressToStringW
{
    struct qemu_syscall super;
    uint64_t pin;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR * WINAPI RtlIpv4AddressToStringW(const IN_ADDR *pin, LPWSTR buffer)
{
    struct qemu_RtlIpv4AddressToStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIPV4ADDRESSTOSTRINGW);
    call.pin = (ULONG_PTR)pin;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return (WCHAR *)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add RtlIpv4AddressToStringW to Wine headers? */
extern WCHAR * WINAPI RtlIpv4AddressToStringW(const IN_ADDR *pin, LPWSTR buffer);
void qemu_RtlIpv4AddressToStringW(struct qemu_syscall *call)
{
    struct qemu_RtlIpv4AddressToStringW *c = (struct qemu_RtlIpv4AddressToStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(RtlIpv4AddressToStringW(QEMU_G2H(c->pin), QEMU_G2H(c->buffer)));
}

#endif

struct qemu_RtlIpv4AddressToStringA
{
    struct qemu_syscall super;
    uint64_t pin;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI CHAR * WINAPI RtlIpv4AddressToStringA(const IN_ADDR *pin, LPSTR buffer)
{
    struct qemu_RtlIpv4AddressToStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIPV4ADDRESSTOSTRINGA);
    call.pin = (ULONG_PTR)pin;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return (CHAR *)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add RtlIpv4AddressToStringA to Wine headers? */
extern CHAR * WINAPI RtlIpv4AddressToStringA(const IN_ADDR *pin, LPSTR buffer);
void qemu_RtlIpv4AddressToStringA(struct qemu_syscall *call)
{
    struct qemu_RtlIpv4AddressToStringA *c = (struct qemu_RtlIpv4AddressToStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(RtlIpv4AddressToStringA(QEMU_G2H(c->pin), QEMU_G2H(c->buffer)));
}

#endif

struct qemu_RtlEncodePointer
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI RtlEncodePointer(PVOID ptr)
{
    struct qemu_RtlEncodePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLENCODEPOINTER);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlEncodePointer(struct qemu_syscall *call)
{
    struct qemu_RtlEncodePointer *c = (struct qemu_RtlEncodePointer *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlEncodePointer(QEMU_G2H(c->ptr));
}

#endif

struct qemu_RtlDecodePointer
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI RtlDecodePointer(PVOID ptr)
{
    struct qemu_RtlDecodePointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDECODEPOINTER);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return (PVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RtlDecodePointer(struct qemu_syscall *call)
{
    struct qemu_RtlDecodePointer *c = (struct qemu_RtlDecodePointer *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlDecodePointer(QEMU_G2H(c->ptr));
}

#endif

struct qemu_RtlInitializeSListHead
{
    struct qemu_syscall super;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI RtlInitializeSListHead(PSLIST_HEADER list)
{
#ifdef _WIN64
    list->Alignment = list->Region = 0;
    list->HeaderX64.HeaderType = 1;  /* we use the 16-byte header */
#else
    list->Alignment = 0;
#endif
}

#else

void qemu_RtlInitializeSListHead(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeSListHead *c = (struct qemu_RtlInitializeSListHead *)call;
    WINE_TRACE("\n");
    RtlInitializeSListHead(QEMU_G2H(c->list));
}

#endif

struct qemu_RtlQueryDepthSList
{
    struct qemu_syscall super;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WORD WINAPI RtlQueryDepthSList(PSLIST_HEADER list)
{
#ifdef _WIN64
    return list->HeaderX64.Depth;
#else
    return list->Depth;
#endif
}

#else

void qemu_RtlQueryDepthSList(struct qemu_syscall *call)
{
    struct qemu_RtlQueryDepthSList *c = (struct qemu_RtlQueryDepthSList *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlQueryDepthSList(QEMU_G2H(c->list));
}

#endif

struct qemu_RtlFirstEntrySList
{
    struct qemu_syscall super;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PSLIST_ENTRY WINAPI RtlFirstEntrySList(const SLIST_HEADER* list)
{
#ifdef _WIN64
    return (SLIST_ENTRY *)((ULONG_PTR)list->HeaderX64.NextEntry << 4);
#else
    return list->Next.Next;
#endif
}

#else

void qemu_RtlFirstEntrySList(struct qemu_syscall *call)
{
    struct qemu_RtlFirstEntrySList *c = (struct qemu_RtlFirstEntrySList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RtlFirstEntrySList(QEMU_G2H(c->list));
}

#endif

struct qemu_RtlInterlockedFlushSList
{
    struct qemu_syscall super;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

static inline __int64 interlocked_cmpxchg64( __int64 *dest, __int64 xchg, __int64 compare )
{
    return __sync_val_compare_and_swap( dest, compare, xchg );
}

#ifdef _WIN64
static inline unsigned char interlocked_cmpxchg128( __int64 *dest, __int64 xchg_high,
                                                    __int64 xchg_low, __int64 *compare )
{
    unsigned char ret;
    __asm__ __volatile__( "lock cmpxchg16b %0; setz %b2"
                          : "=m" (dest[0]), "=m" (dest[1]), "=r" (ret),
                            "=a" (compare[0]), "=d" (compare[1])
                          : "m" (dest[0]), "m" (dest[1]), "3" (compare[0]), "4" (compare[1]),
                            "c" (xchg_high), "b" (xchg_low) );
    return ret;
}
#endif

WINBASEAPI PSLIST_ENTRY WINAPI RtlInterlockedFlushSList(PSLIST_HEADER list)
{
    SLIST_HEADER old, new;

#ifdef _WIN64
    if (!list->HeaderX64.NextEntry) return NULL;
    new.Alignment = new.Region = 0;
    new.HeaderX64.HeaderType = 1;  /* we use the 16-byte header */
    do
    {
        old = *list;
        new.HeaderX64.Sequence = old.HeaderX64.Sequence + 1;
    } while (!interlocked_cmpxchg128((__int64 *)list, new.Region, new.Alignment, (__int64 *)&old));
    return (SLIST_ENTRY *)((ULONG_PTR)old.HeaderX64.NextEntry << 4);
#else
    if (!list->Next.Next) return NULL;
    new.Alignment = 0;
    do
    {
        old = *list;
        new.Sequence = old.Sequence + 1;
    } while (interlocked_cmpxchg64((__int64 *)&list->Alignment, new.Alignment,
                                   old.Alignment) != old.Alignment);
    return old.Next.Next;
#endif
}

#else

void qemu_RtlInterlockedFlushSList(struct qemu_syscall *call)
{
    struct qemu_RtlInterlockedFlushSList *c = (struct qemu_RtlInterlockedFlushSList *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlInterlockedFlushSList(QEMU_G2H(c->list));
}

#endif

struct qemu_RtlInterlockedPushEntrySList
{
    struct qemu_syscall super;
    uint64_t list;
    uint64_t entry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PSLIST_ENTRY WINAPI RtlInterlockedPushEntrySList(PSLIST_HEADER list, PSLIST_ENTRY entry)
{
    SLIST_HEADER old, new;

#ifdef _WIN64
    new.HeaderX64.NextEntry = (ULONG_PTR)entry >> 4;
    do
    {
        old = *list;
        entry->Next = (SLIST_ENTRY *)((ULONG_PTR)old.HeaderX64.NextEntry << 4);
        new.HeaderX64.Depth = old.HeaderX64.Depth + 1;
        new.HeaderX64.Sequence = old.HeaderX64.Sequence + 1;
    } while (!interlocked_cmpxchg128((__int64 *)list, new.Region, new.Alignment, (__int64 *)&old));
    return (SLIST_ENTRY *)((ULONG_PTR)old.HeaderX64.NextEntry << 4);
#else
    new.Next.Next = entry;
    do
    {
        old = *list;
        entry->Next = old.Next.Next;
        new.Depth = old.Depth + 1;
        new.Sequence = old.Sequence + 1;
    } while (interlocked_cmpxchg64((__int64 *)&list->Alignment, new.Alignment,
                                   old.Alignment) != old.Alignment);
    return old.Next.Next;
#endif
}

#else

void qemu_RtlInterlockedPushEntrySList(struct qemu_syscall *call)
{
    struct qemu_RtlInterlockedPushEntrySList *c = (struct qemu_RtlInterlockedPushEntrySList *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlInterlockedPushEntrySList(QEMU_G2H(c->list), QEMU_G2H(c->entry));
}

#endif

struct qemu_RtlInterlockedPopEntrySList
{
    struct qemu_syscall super;
    uint64_t list;
};

#ifdef QEMU_DLL_GUEST

#ifdef _WIN64
long CALLBACK wndproc_except_handler(EXCEPTION_POINTERS *pointers, ULONG64 frame)
{
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif

WINBASEAPI PSLIST_ENTRY WINAPI RtlInterlockedPopEntrySList(PSLIST_HEADER list)
{
    SLIST_HEADER old, new;
    PSLIST_ENTRY entry;

#ifdef _WIN64
    do
    {
        old = *list;
        if (!(entry = (SLIST_ENTRY *)((ULONG_PTR)old.HeaderX64.NextEntry << 4))) return NULL;
        /* entry could be deleted by another thread */
        __try1(wndproc_except_handler)
        {
            new.HeaderX64.NextEntry = (ULONG_PTR)entry->Next >> 4;
            new.HeaderX64.Depth = old.HeaderX64.Depth - 1;
            new.HeaderX64.Sequence = old.HeaderX64.Sequence + 1;
        }
        __except1
        {
        }
    } while (!interlocked_cmpxchg128((__int64 *)list, new.Region, new.Alignment, (__int64 *)&old));
#else
    do
    {
        old = *list;
        if (!(entry = old.Next.Next)) return NULL;
        /* entry could be deleted by another thread */
//         __TRY
//         {
            new.Next.Next = entry->Next;
            new.Depth = old.Depth - 1;
            new.Sequence = old.Sequence + 1;
//         }
//         __EXCEPT_PAGE_FAULT
//         {
//         }
//         __ENDTRY
    } while (interlocked_cmpxchg64((__int64 *)&list->Alignment, new.Alignment,
                                   old.Alignment) != old.Alignment);
#endif
    return entry;
}

#else

void qemu_RtlInterlockedPopEntrySList(struct qemu_syscall *call)
{
    struct qemu_RtlInterlockedPopEntrySList *c = (struct qemu_RtlInterlockedPopEntrySList *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlInterlockedPopEntrySList(QEMU_G2H(c->list));
}

#endif

struct qemu_RtlInterlockedPushListSListEx
{
    struct qemu_syscall super;
    uint64_t list;
    uint64_t first;
    uint64_t last;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

PSLIST_ENTRY WINAPI qemu_RtlInterlockedPushListSListEx(PSLIST_HEADER list, PSLIST_ENTRY first,
                                                  PSLIST_ENTRY last, ULONG count)
{
    SLIST_HEADER old, new;

#ifdef _WIN64
    new.HeaderX64.NextEntry = (ULONG_PTR)first >> 4;
    do
    {
        old = *list;
        new.HeaderX64.Depth = old.HeaderX64.Depth + count;
        new.HeaderX64.Sequence = old.HeaderX64.Sequence + 1;
        last->Next = (SLIST_ENTRY *)((ULONG_PTR)old.HeaderX64.NextEntry << 4);
    } while (!interlocked_cmpxchg128((__int64 *)list, new.Region, new.Alignment, (__int64 *)&old));
    return (SLIST_ENTRY *)((ULONG_PTR)old.HeaderX64.NextEntry << 4);
#else
    new.Next.Next = first;
    do
    {
        old = *list;
        new.Depth = old.Depth + count;
        new.Sequence = old.Sequence + 1;
        last->Next = old.Next.Next;
    } while (interlocked_cmpxchg64((__int64 *)&list->Alignment, new.Alignment,
                                   old.Alignment) != old.Alignment);
    return old.Next.Next;
#endif
}

#else

/* TODO: Add RtlInterlockedPushListSListEx to Wine headers? */
extern PSLIST_ENTRY WINAPI RtlInterlockedPushListSListEx(PSLIST_HEADER list, PSLIST_ENTRY first, PSLIST_ENTRY last, ULONG count);
void qemu_RtlInterlockedPushListSListEx(struct qemu_syscall *call)
{
    struct qemu_RtlInterlockedPushListSListEx *c = (struct qemu_RtlInterlockedPushListSListEx *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlInterlockedPushListSListEx(QEMU_G2H(c->list), QEMU_G2H(c->first), QEMU_G2H(c->last), c->count);
}

#endif

struct qemu_RtlInterlockedPushListSList
{
    struct qemu_syscall super;
    uint64_t list;
    uint64_t first;
    uint64_t last;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PSLIST_ENTRY __fastcall RtlInterlockedPushListSList(PSLIST_HEADER list, PSLIST_ENTRY first, PSLIST_ENTRY last, ULONG count)
{
    return qemu_RtlInterlockedPushListSListEx(list, first, last, count);
}

#else

/* TODO: Add RtlInterlockedPushListSList to Wine headers? */
extern PSLIST_ENTRY WINAPI RtlInterlockedPushListSList(PSLIST_HEADER list, PSLIST_ENTRY first, PSLIST_ENTRY last, ULONG count);
void qemu_RtlInterlockedPushListSList(struct qemu_syscall *call)
{
    struct qemu_RtlInterlockedPushListSList *c = (struct qemu_RtlInterlockedPushListSList *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)RtlInterlockedPushListSList(QEMU_G2H(c->list), QEMU_G2H(c->first), QEMU_G2H(c->last), c->count);
}

#endif

struct qemu_RtlGetCompressionWorkSpaceSize
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t compress_workspace;
    uint64_t decompress_workspace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetCompressionWorkSpaceSize(USHORT format, PULONG compress_workspace, PULONG decompress_workspace)
{
    struct qemu_RtlGetCompressionWorkSpaceSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETCOMPRESSIONWORKSPACESIZE);
    call.format = (ULONG_PTR)format;
    call.compress_workspace = (ULONG_PTR)compress_workspace;
    call.decompress_workspace = (ULONG_PTR)decompress_workspace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetCompressionWorkSpaceSize(struct qemu_syscall *call)
{
    struct qemu_RtlGetCompressionWorkSpaceSize *c = (struct qemu_RtlGetCompressionWorkSpaceSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetCompressionWorkSpaceSize(c->format, QEMU_G2H(c->compress_workspace), QEMU_G2H(c->decompress_workspace));
}

#endif

struct qemu_RtlCompressBuffer
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t uncompressed;
    uint64_t uncompressed_size;
    uint64_t compressed;
    uint64_t compressed_size;
    uint64_t chunk_size;
    uint64_t final_size;
    uint64_t workspace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCompressBuffer(USHORT format, PUCHAR uncompressed, ULONG uncompressed_size, PUCHAR compressed, ULONG compressed_size, ULONG chunk_size, PULONG final_size, PVOID workspace)
{
    struct qemu_RtlCompressBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPRESSBUFFER);
    call.format = (ULONG_PTR)format;
    call.uncompressed = (ULONG_PTR)uncompressed;
    call.uncompressed_size = (ULONG_PTR)uncompressed_size;
    call.compressed = (ULONG_PTR)compressed;
    call.compressed_size = (ULONG_PTR)compressed_size;
    call.chunk_size = (ULONG_PTR)chunk_size;
    call.final_size = (ULONG_PTR)final_size;
    call.workspace = (ULONG_PTR)workspace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCompressBuffer(struct qemu_syscall *call)
{
    struct qemu_RtlCompressBuffer *c = (struct qemu_RtlCompressBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompressBuffer(c->format, QEMU_G2H(c->uncompressed), c->uncompressed_size, QEMU_G2H(c->compressed), c->compressed_size, c->chunk_size, QEMU_G2H(c->final_size), QEMU_G2H(c->workspace));
}

#endif

struct qemu_RtlDecompressFragment
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t uncompressed;
    uint64_t uncompressed_size;
    uint64_t compressed;
    uint64_t compressed_size;
    uint64_t offset;
    uint64_t final_size;
    uint64_t workspace;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDecompressFragment(USHORT format, PUCHAR uncompressed, ULONG uncompressed_size, PUCHAR compressed, ULONG compressed_size, ULONG offset, PULONG final_size, PVOID workspace)
{
    struct qemu_RtlDecompressFragment call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDECOMPRESSFRAGMENT);
    call.format = (ULONG_PTR)format;
    call.uncompressed = (ULONG_PTR)uncompressed;
    call.uncompressed_size = (ULONG_PTR)uncompressed_size;
    call.compressed = (ULONG_PTR)compressed;
    call.compressed_size = (ULONG_PTR)compressed_size;
    call.offset = (ULONG_PTR)offset;
    call.final_size = (ULONG_PTR)final_size;
    call.workspace = (ULONG_PTR)workspace;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlDecompressFragment to Wine headers? */
extern NTSTATUS WINAPI RtlDecompressFragment(USHORT format, PUCHAR uncompressed, ULONG uncompressed_size, PUCHAR compressed, ULONG compressed_size, ULONG offset, PULONG final_size, PVOID workspace);
void qemu_RtlDecompressFragment(struct qemu_syscall *call)
{
    struct qemu_RtlDecompressFragment *c = (struct qemu_RtlDecompressFragment *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDecompressFragment(c->format, QEMU_G2H(c->uncompressed), c->uncompressed_size, QEMU_G2H(c->compressed), c->compressed_size, c->offset, QEMU_G2H(c->final_size), QEMU_G2H(c->workspace));
}

#endif

struct qemu_RtlDecompressBuffer
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t uncompressed;
    uint64_t uncompressed_size;
    uint64_t compressed;
    uint64_t compressed_size;
    uint64_t final_size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDecompressBuffer(USHORT format, PUCHAR uncompressed, ULONG uncompressed_size, PUCHAR compressed, ULONG compressed_size, PULONG final_size)
{
    struct qemu_RtlDecompressBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDECOMPRESSBUFFER);
    call.format = (ULONG_PTR)format;
    call.uncompressed = (ULONG_PTR)uncompressed;
    call.uncompressed_size = (ULONG_PTR)uncompressed_size;
    call.compressed = (ULONG_PTR)compressed;
    call.compressed_size = (ULONG_PTR)compressed_size;
    call.final_size = (ULONG_PTR)final_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDecompressBuffer(struct qemu_syscall *call)
{
    struct qemu_RtlDecompressBuffer *c = (struct qemu_RtlDecompressBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDecompressBuffer(c->format, QEMU_G2H(c->uncompressed), c->uncompressed_size, QEMU_G2H(c->compressed), c->compressed_size, QEMU_G2H(c->final_size));
}

#endif

struct qemu_RtlSetThreadErrorMode
{
    struct qemu_syscall super;
    uint64_t mode;
    uint64_t oldmode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetThreadErrorMode(DWORD mode, LPDWORD oldmode)
{
    struct qemu_RtlSetThreadErrorMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETTHREADERRORMODE);
    call.mode = (ULONG_PTR)mode;
    call.oldmode = (ULONG_PTR)oldmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetThreadErrorMode(struct qemu_syscall *call)
{
    struct qemu_RtlSetThreadErrorMode *c = (struct qemu_RtlSetThreadErrorMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetThreadErrorMode(c->mode, QEMU_G2H(c->oldmode));
}

#endif

struct qemu_RtlGetThreadErrorMode
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlGetThreadErrorMode(void)
{
    struct qemu_RtlGetThreadErrorMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETTHREADERRORMODE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetThreadErrorMode(struct qemu_syscall *call)
{
    struct qemu_RtlGetThreadErrorMode *c = (struct qemu_RtlGetThreadErrorMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetThreadErrorMode();
}

#endif

struct qemu_RtlGetCurrentTransaction
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI RtlGetCurrentTransaction(void)
{
    struct qemu_RtlGetCurrentTransaction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETCURRENTTRANSACTION);

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add RtlGetCurrentTransaction to Wine headers? */
extern HANDLE WINAPI RtlGetCurrentTransaction(void);
void qemu_RtlGetCurrentTransaction(struct qemu_syscall *call)
{
    struct qemu_RtlGetCurrentTransaction *c = (struct qemu_RtlGetCurrentTransaction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RtlGetCurrentTransaction();
}

#endif

struct qemu_RtlSetCurrentTransaction
{
    struct qemu_syscall super;
    uint64_t new_transaction;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI RtlSetCurrentTransaction(HANDLE new_transaction)
{
    struct qemu_RtlSetCurrentTransaction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETCURRENTTRANSACTION);
    call.new_transaction = (ULONG_PTR)new_transaction;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlSetCurrentTransaction to Wine headers? */
extern BOOL WINAPI RtlSetCurrentTransaction(HANDLE new_transaction);
void qemu_RtlSetCurrentTransaction(struct qemu_syscall *call)
{
    struct qemu_RtlSetCurrentTransaction *c = (struct qemu_RtlSetCurrentTransaction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetCurrentTransaction(QEMU_G2H(c->new_transaction));
}

#endif

struct qemu_RtlGetCurrentProcessorNumberEx
{
    struct qemu_syscall super;
    uint64_t processor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlGetCurrentProcessorNumberEx(PROCESSOR_NUMBER *processor)
{
    struct qemu_RtlGetCurrentProcessorNumberEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETCURRENTPROCESSORNUMBEREX);
    call.processor = (ULONG_PTR)processor;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add RtlGetCurrentProcessorNumberEx to Wine headers? */
extern void WINAPI RtlGetCurrentProcessorNumberEx(PROCESSOR_NUMBER *processor);
void qemu_RtlGetCurrentProcessorNumberEx(struct qemu_syscall *call)
{
    struct qemu_RtlGetCurrentProcessorNumberEx *c = (struct qemu_RtlGetCurrentProcessorNumberEx *)call;
    WINE_FIXME("Unverified!\n");
    RtlGetCurrentProcessorNumberEx(QEMU_G2H(c->processor));
}

#endif

struct qemu_RtlInitializeGenericTableAvl
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t compare;
    uint64_t allocate;
    uint64_t free;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitializeGenericTableAvl(PRTL_AVL_TABLE table, PRTL_AVL_COMPARE_ROUTINE compare, PRTL_AVL_ALLOCATE_ROUTINE allocate, PRTL_AVL_FREE_ROUTINE free, void *context)
{
    struct qemu_RtlInitializeGenericTableAvl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITIALIZEGENERICTABLEAVL);
    call.table = (ULONG_PTR)table;
    call.compare = (ULONG_PTR)compare;
    call.allocate = (ULONG_PTR)allocate;
    call.free = (ULONG_PTR)free;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitializeGenericTableAvl(struct qemu_syscall *call)
{
    struct qemu_RtlInitializeGenericTableAvl *c = (struct qemu_RtlInitializeGenericTableAvl *)call;
    WINE_FIXME("Unverified!\n");
    RtlInitializeGenericTableAvl(QEMU_G2H(c->table), QEMU_G2H(c->compare), QEMU_G2H(c->allocate), QEMU_G2H(c->free), QEMU_G2H(c->context));
}

#endif

struct qemu_RtlInsertElementGenericTableAvl
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t buffer;
    uint64_t size;
    uint64_t element;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInsertElementGenericTableAvl(PRTL_AVL_TABLE table, void *buffer, ULONG size, BOOL *element)
{
    struct qemu_RtlInsertElementGenericTableAvl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINSERTELEMENTGENERICTABLEAVL);
    call.table = (ULONG_PTR)table;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;
    call.element = (ULONG_PTR)element;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInsertElementGenericTableAvl(struct qemu_syscall *call)
{
    struct qemu_RtlInsertElementGenericTableAvl *c = (struct qemu_RtlInsertElementGenericTableAvl *)call;
    WINE_FIXME("Unverified!\n");
    RtlInsertElementGenericTableAvl(QEMU_G2H(c->table), QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->element));
}

#endif

struct qemu_RtlCreateUserProcess
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t attributes;
    uint64_t parameters;
    uint64_t process_descriptor;
    uint64_t thread_descriptor;
    uint64_t parent;
    uint64_t inherit;
    uint64_t debug;
    uint64_t exception;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateUserProcess(UNICODE_STRING *path, ULONG attributes, RTL_USER_PROCESS_PARAMETERS *parameters, SECURITY_DESCRIPTOR *process_descriptor, SECURITY_DESCRIPTOR *thread_descriptor, HANDLE parent, BOOLEAN inherit, HANDLE debug, HANDLE exception, RTL_USER_PROCESS_INFORMATION *info)
{
    struct qemu_RtlCreateUserProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEUSERPROCESS);
    call.path = (ULONG_PTR)path;
    call.attributes = (ULONG_PTR)attributes;
    call.parameters = (ULONG_PTR)parameters;
    call.process_descriptor = (ULONG_PTR)process_descriptor;
    call.thread_descriptor = (ULONG_PTR)thread_descriptor;
    call.parent = (ULONG_PTR)parent;
    call.inherit = (ULONG_PTR)inherit;
    call.debug = (ULONG_PTR)debug;
    call.exception = (ULONG_PTR)exception;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateUserProcess(struct qemu_syscall *call)
{
    struct qemu_RtlCreateUserProcess *c = (struct qemu_RtlCreateUserProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateUserProcess(QEMU_G2H(c->path), c->attributes, QEMU_G2H(c->parameters), QEMU_G2H(c->process_descriptor), QEMU_G2H(c->thread_descriptor), QEMU_G2H(c->parent), c->inherit, QEMU_G2H(c->debug), QEMU_G2H(c->exception), QEMU_G2H(c->info));
}

#endif

#ifdef QEMU_DLL_GUEST

/* These are implemented as __fastcall, so we can't let Winelib apps link with them */
static inline USHORT RtlUshortByteSwap(USHORT s)
{
    return (s >> 8) | (s << 8);
}
static inline ULONG RtlUlongByteSwap(ULONG i)
{
#if defined(__i386__) && defined(__GNUC__)
    ULONG ret;
    __asm__("bswap %0" : "=r" (ret) : "0" (i) );
    return ret;
#else
    return ((ULONG)RtlUshortByteSwap((USHORT)i) << 16) | RtlUshortByteSwap((USHORT)(i >> 16));
#endif
}

ULONGLONG __cdecl RtlUlonglongByteSwap(ULONGLONG i)
{
    return ((ULONGLONG)RtlUlongByteSwap(i) << 32) | RtlUlongByteSwap(i>>32);
}

#endif

