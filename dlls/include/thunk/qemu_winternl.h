#ifndef HAVE_QEMU_WINTERNL_H
#define HAVE_QEMU_WINTERNL_H

#include "thunk/qemu_windef.h"

struct qemu_UNICODE_STRING
{
  USHORT Length;        /* bytes */
  USHORT MaximumLength; /* bytes */
  qemu_ptr  Buffer;
};

static inline void UNICODE_STRING_g2h(UNICODE_STRING *host, const struct qemu_UNICODE_STRING *guest)
{
    host->Length = guest->Length;
    host->MaximumLength = guest->MaximumLength;
    host->Buffer = (WCHAR *)(ULONG_PTR)guest->Buffer;
}

static inline void UNICODE_STRING_h2g(struct qemu_UNICODE_STRING *guest, const UNICODE_STRING *host)
{
    guest->Length = host->Length;
    guest->MaximumLength = host->MaximumLength;
    guest->Buffer = (ULONG_PTR)host->Buffer;
}

struct qemu_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    qemu_ptr Buffer;
};

static inline void STRING_g2h(STRING *host, const struct qemu_STRING *guest)
{
    host->Length = guest->Length;
    host->MaximumLength = guest->MaximumLength;
    host->Buffer = (CHAR *)(ULONG_PTR)guest->Buffer;
}

static inline void STRING_h2g(struct qemu_STRING *guest, const STRING *host)
{
    guest->Length = host->Length;
    guest->MaximumLength = host->MaximumLength;
    guest->Buffer = (ULONG_PTR)host->Buffer;
}

struct qemu_OBJECT_NAME_INFORMATION
{
    struct qemu_UNICODE_STRING Name;
};

static inline void OBJECT_NAME_INFORMATION_g2h(OBJECT_NAME_INFORMATION *host, const struct qemu_OBJECT_NAME_INFORMATION *guest)
{
    UNICODE_STRING_g2h(&host->Name, &guest->Name);
}

static inline void OBJECT_NAME_INFORMATION_h2g(struct qemu_OBJECT_NAME_INFORMATION *guest, const OBJECT_NAME_INFORMATION *host)
{
    UNICODE_STRING_h2g(&guest->Name, &host->Name);
}

struct qemu_IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        qemu_ptr Pointer;
    } DUMMYUNIONNAME;

    qemu_ptr Information;
};

static inline void IO_STATUS_BLOCK_g2h(IO_STATUS_BLOCK *host, const struct qemu_IO_STATUS_BLOCK *guest)
{
    host->Pointer = (void *)(ULONG_PTR)guest->Pointer;
    host->Information = guest->Information;
}

static inline void IO_STATUS_BLOCK_h2g(struct qemu_IO_STATUS_BLOCK *guest, const IO_STATUS_BLOCK *host)
{
    guest->Pointer = (ULONG_PTR)host->Pointer;
    guest->Information = host->Information;
}

struct qemu_OBJECT_ATTRIBUTES
{
    ULONG Length;
    qemu_handle RootDirectory;
    qemu_ptr ObjectName;
    ULONG Attributes;
    qemu_ptr SecurityDescriptor;       /* type SECURITY_DESCRIPTOR */
    qemu_ptr SecurityQualityOfService; /* type SECURITY_QUALITY_OF_SERVICE */
};

static inline void OBJECT_ATTRIBUTES_g2h(OBJECT_ATTRIBUTES *host, const struct qemu_OBJECT_ATTRIBUTES *guest,
        UNICODE_STRING *name)
{
    host->Length = sizeof(*host);
    host->RootDirectory = HANDLE_g2h(guest->RootDirectory);
    if (guest->ObjectName)
    {
        host->ObjectName = name;
        UNICODE_STRING_g2h(name, (struct qemu_UNICODE_STRING *)(ULONG_PTR)guest->ObjectName);
    }
    else
    {
        host->ObjectName = 0;
    }
    host->Attributes = guest->Attributes;
    host->SecurityDescriptor = (void *)(ULONG_PTR)guest->SecurityDescriptor;
    host->SecurityQualityOfService = (void *)(ULONG_PTR)guest->SecurityQualityOfService;
}

static inline void OBJECT_ATTRIBUTES_h2g(struct qemu_OBJECT_ATTRIBUTES *guest, const OBJECT_ATTRIBUTES *host)
{
    guest->RootDirectory = (ULONG_PTR)host->RootDirectory;
    guest->ObjectName = (ULONG_PTR)host->ObjectName;
    guest->Attributes = host->Attributes;
    guest->SecurityDescriptor = (ULONG_PTR)host->SecurityDescriptor;
    guest->SecurityQualityOfService = (ULONG_PTR)host->SecurityQualityOfService;
}

struct qemu_RTL_RWLOCK
{
    struct qemu_RTL_CRITICAL_SECTION rtlCS;

    qemu_handle hSharedReleaseSemaphore;
    UINT        uSharedWaiters;

    qemu_handle hExclusiveReleaseSemaphore;
    UINT        uExclusiveWaiters;

    INT         iNumberActive;
    qemu_handle hOwningThreadId;
    DWORD       dwTimeoutBoost;
    qemu_ptr    pDebugInfo;
};

struct qemu_LDR_RESOURCE_INFO
{
    qemu_ptr Type;
    qemu_ptr Name;
    ULONG Language;
};

#ifndef QEMU_DLL_GUEST
static inline void LDR_RESOURCE_INFO_g2h(LDR_RESOURCE_INFO *host, const struct qemu_LDR_RESOURCE_INFO *guest)
{
    host->Type = guest->Type;
    host->Name = guest->Name;
    host->Language = guest->Language;
}

static inline void LDR_RESOURCE_INFO_h2g(struct qemu_LDR_RESOURCE_INFO *guest, const LDR_RESOURCE_INFO *host)
{
    guest->Type = host->Type;
    guest->Name = host->Name;
    guest->Language = host->Language;
}
#endif

struct qemu_CPTABLEINFO
{
    USHORT   CodePage;
    USHORT   MaximumCharacterSize;
    USHORT   DefaultChar;
    USHORT   UniDefaultChar;
    USHORT   TransDefaultChar;
    USHORT   TransUniDefaultChar;
    USHORT   DBCSCodePage;
    UCHAR    LeadByte[12];
    qemu_ptr MultiByteTable;
    qemu_ptr WideCharTable;
    qemu_ptr DBCSRanges;
    qemu_ptr DBCSOffsets;
};

#ifndef QEMU_DLL_GUEST
static inline void CPTABLEINFO_g2h(CPTABLEINFO *host, const struct qemu_CPTABLEINFO *guest)
{
    host->CodePage = guest->CodePage;
    host->MaximumCharacterSize = guest->MaximumCharacterSize;
    host->DefaultChar = guest->DefaultChar;
    host->UniDefaultChar = guest->UniDefaultChar;
    host->TransDefaultChar = guest->TransDefaultChar;
    host->TransUniDefaultChar = guest->TransUniDefaultChar;
    host->DBCSCodePage = guest->DBCSCodePage;
    memcpy(host->LeadByte, guest->LeadByte, sizeof(host->LeadByte));
    host->MultiByteTable = (USHORT *)(ULONG_PTR)guest->MultiByteTable;
    host->WideCharTable = (void *)(ULONG_PTR)guest->WideCharTable;
    host->DBCSRanges = (USHORT *)(ULONG_PTR)guest->DBCSRanges;
    host->DBCSOffsets = (USHORT *)(ULONG_PTR)guest->DBCSOffsets;
}

static inline void CPTABLEINFO_h2g(struct qemu_CPTABLEINFO *guest, const CPTABLEINFO *host)
{
    guest->CodePage = host->CodePage;
    guest->MaximumCharacterSize = host->MaximumCharacterSize;
    guest->DefaultChar = host->DefaultChar;
    guest->UniDefaultChar = host->UniDefaultChar;
    guest->TransDefaultChar = host->TransDefaultChar;
    guest->TransUniDefaultChar = host->TransUniDefaultChar;
    guest->DBCSCodePage = host->DBCSCodePage;
    memcpy(guest->LeadByte, host->LeadByte, sizeof(guest->LeadByte));
    guest->MultiByteTable = (ULONG_PTR)host->MultiByteTable;
    guest->WideCharTable = (ULONG_PTR)host->WideCharTable;
    guest->DBCSRanges = (ULONG_PTR)host->DBCSRanges;
    guest->DBCSOffsets = (ULONG_PTR)host->DBCSOffsets;
}
#endif

struct qemu_NLSTABLEINFO
{
    struct qemu_CPTABLEINFO OemTableInfo;
    struct qemu_CPTABLEINFO AnsiTableInfo;
    qemu_ptr    UpperCaseTable;
    qemu_ptr    LowerCaseTable;
};

#ifndef QEMU_DLL_GUEST
static inline void NLSTABLEINFO_g2h(NLSTABLEINFO *host, const struct qemu_NLSTABLEINFO *guest)
{
    CPTABLEINFO_g2h(&host->OemTableInfo, &guest->OemTableInfo);
    CPTABLEINFO_g2h(&host->AnsiTableInfo, &guest->AnsiTableInfo);
    host->UpperCaseTable = (USHORT *)(ULONG_PTR)guest->UpperCaseTable;
    host->LowerCaseTable = (USHORT *)(ULONG_PTR)guest->LowerCaseTable;
}

static inline void NLSTABLEINFO_h2g(struct qemu_NLSTABLEINFO *guest, const NLSTABLEINFO *host)
{
    CPTABLEINFO_h2g(&guest->OemTableInfo, &host->OemTableInfo);
    CPTABLEINFO_h2g(&guest->AnsiTableInfo, &host->AnsiTableInfo);
    guest->UpperCaseTable = (ULONG_PTR)host->UpperCaseTable;
    guest->LowerCaseTable = (ULONG_PTR)host->LowerCaseTable;
}
#endif

#endif
