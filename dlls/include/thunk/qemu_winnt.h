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

struct qemu_RTL_CRITICAL_SECTION_DEBUG
{
    WORD   Type;
    WORD   CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
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

#endif
