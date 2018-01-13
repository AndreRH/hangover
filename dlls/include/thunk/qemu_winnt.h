#ifndef HAVE_QEMU_WINNT_H
#define HAVE_QEMU_WINNT_H

#include "thunk/qemu_defines.h"

struct qemu_MEMORY_BASIC_INFORMATION
{
    qemu_ptr    BaseAddress;
    qemu_ptr    AllocationBase;
    DWORD       AllocationProtect;
    qemu_size_t RegionSize;
    DWORD       State;
    DWORD       Protect;
    DWORD       Type;
};

static inline void MEMORY_BASIC_INFORMATION_h2g(const MEMORY_BASIC_INFORMATION *host,
        struct qemu_MEMORY_BASIC_INFORMATION *guest)
{
    guest->BaseAddress = (ULONG_PTR)host->BaseAddress;
    guest->AllocationBase = (ULONG_PTR)host->AllocationBase;
    guest->AllocationProtect = host->AllocationProtect;
    guest->RegionSize = host->RegionSize;
    guest->State = host->State;
    guest->Protect = host->Protect;
    guest->Type = host->Type;
}

struct qemu_LIST_ENTRY
{
  qemu_ptr Flink;
  qemu_ptr Blink;
};

struct qemu_RTL_CRITICAL_SECTION_DEBUG
{
    WORD   Type;
    WORD   CreatorBackTraceIndex;
    qemu_ptr CriticalSection;
    struct qemu_LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Spare[ 2 ];
};

struct qemu_RTL_CRITICAL_SECTION
{
    qemu_ptr DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    qemu_handle OwningThread;
    qemu_handle LockSemaphore;
    qemu_ptr SpinCount;
};

struct qemu_SECURITY_DESCRIPTOR
{
    BYTE Revision;
    BYTE Sbz1;
    SECURITY_DESCRIPTOR_CONTROL Control;    /* USHORT */
    qemu_ptr Owner; /* Should be fine without conversion. Needs double-checking. */
    qemu_ptr Group;
    qemu_ptr Sacl;  /* PACL, no conversion needed. */
    qemu_ptr Dacl;
};

static inline void SECURITY_DESCRIPTOR_g2h(SECURITY_DESCRIPTOR *host, const struct qemu_SECURITY_DESCRIPTOR *guest)
{
    host->Revision = guest->Revision;
    host->Sbz1 = guest->Sbz1;
    host->Control = guest->Control;
    host->Owner = (SID *)(ULONG_PTR)guest->Owner;
    host->Group = (SID *)(ULONG_PTR)guest->Group;
    host->Sacl = (ACL *)(ULONG_PTR)guest->Sacl;
    host->Dacl = (ACL *)(ULONG_PTR)guest->Dacl;
}

static inline void SECURITY_DESCRIPTOR_h2g(struct qemu_SECURITY_DESCRIPTOR *guest, const SECURITY_DESCRIPTOR *host)
{
    guest->Revision = host->Revision;
    guest->Sbz1 = host->Sbz1;
    guest->Control = host->Control;
    guest->Owner = (ULONG_PTR)host->Owner;
    guest->Group = (ULONG_PTR)host->Group;
    guest->Sacl = (ULONG_PTR)host->Sacl;
    guest->Dacl = (ULONG_PTR)host->Dacl;
}

#endif
