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
    /* The following fields are DWORDs in self-relative SDs. */
    qemu_ptr Owner; /* Should be fine without conversion. Needs double-checking. */
    qemu_ptr Group;
    qemu_ptr Sacl;  /* PACL, no conversion needed. */
    qemu_ptr Dacl;
};

static inline void SECURITY_DESCRIPTOR_g2h(SECURITY_DESCRIPTOR *host, const struct qemu_SECURITY_DESCRIPTOR *guest)
{
    /* Relative SDs are handled by the caller because it needs to know if it needs a new struct. */
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
    /* Relative SDs are handled by the caller because it needs to know if it needs a new struct. */
    guest->Revision = host->Revision;
    guest->Sbz1 = host->Sbz1;
    guest->Control = host->Control;
    guest->Owner = (ULONG_PTR)host->Owner;
    guest->Group = (ULONG_PTR)host->Group;
    guest->Sacl = (ULONG_PTR)host->Sacl;
    guest->Dacl = (ULONG_PTR)host->Dacl;
}

struct qemu_SID_AND_ATTRIBUTES
{
    qemu_ptr Sid;
    DWORD Attributes;
};

static inline void SID_AND_ATTRIBUTES_g2h(SID_AND_ATTRIBUTES *host, const struct qemu_SID_AND_ATTRIBUTES *guest)
{
    host->Sid = (SID *)(ULONG_PTR)guest->Sid;
    host->Attributes = guest->Attributes;
}

static inline void SID_AND_ATTRIBUTES_h2g(struct qemu_SID_AND_ATTRIBUTES *guest, const SID_AND_ATTRIBUTES *host)
{
    guest->Sid = (ULONG_PTR)host->Sid;
    guest->Attributes = host->Attributes;
}

struct qemu_TOKEN_GROUPS
{
    DWORD GroupCount;
    struct qemu_SID_AND_ATTRIBUTES Groups[ANYSIZE_ARRAY];
};

static inline void TOKEN_GROUPS_g2h(TOKEN_GROUPS *host, const struct qemu_TOKEN_GROUPS *guest)
{
    DWORD i;
    host->GroupCount = guest->GroupCount;
    for (i = 0; i < guest->GroupCount; ++i)
        SID_AND_ATTRIBUTES_g2h(&host->Groups[i], &guest->Groups[i]);
}

static inline void TOKEN_GROUPS_h2g(struct qemu_TOKEN_GROUPS *guest, const TOKEN_GROUPS *host)
{
    DWORD i;
    guest->GroupCount = host->GroupCount;
    for (i = 0; i < guest->GroupCount; ++i)
        SID_AND_ATTRIBUTES_h2g(&guest->Groups[i], &host->Groups[i]);
}

struct qemu_TOKEN_USER
{
    struct qemu_SID_AND_ATTRIBUTES User;
};

static inline void TOKEN_USER_g2h(TOKEN_USER *host, const struct qemu_TOKEN_USER *guest)
{
    SID_AND_ATTRIBUTES_g2h(&host->User, &guest->User);
}

static inline void TOKEN_USER_h2g(struct qemu_TOKEN_USER *guest, const TOKEN_USER *host)
{
    SID_AND_ATTRIBUTES_h2g(&guest->User, &host->User);
}

struct qemu_TOKEN_DEFAULT_DACL
{
    qemu_ptr DefaultDacl;
};

static inline void TOKEN_DEFAULT_DACL_g2h(TOKEN_DEFAULT_DACL *host, const struct qemu_TOKEN_DEFAULT_DACL *guest)
{
    host->DefaultDacl = (PACL)(ULONG_PTR)guest->DefaultDacl;
}

static inline void TOKEN_DEFAULT_DACL_h2g(struct qemu_TOKEN_DEFAULT_DACL *guest, const TOKEN_DEFAULT_DACL *host)
{
    guest->DefaultDacl = (ULONG_PTR)host->DefaultDacl;
}

#endif
