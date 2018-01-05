#ifndef HAVE_QEMU_WINBASE_H
#define HAVE_QEMU_WINBASE_H

#include "thunk/qemu_defines.h"

struct qemu_STARTUPINFO
{
        DWORD cb;
        qemu_ptr lpReserved;
        qemu_ptr lpDesktop;
        qemu_ptr lpTitle;
        DWORD dwX;
        DWORD dwY;
        DWORD dwXSize;
        DWORD dwYSize;
        DWORD dwXCountChars;
        DWORD dwYCountChars;
        DWORD dwFillAttribute;
        DWORD dwFlags;
        WORD wShowWindow;
        WORD cbReserved2;
        qemu_ptr lpReserved2;
        qemu_handle hStdInput;
        qemu_handle hStdOutput;
        qemu_handle hStdError;
};

struct qemu_SYSTEM_INFO
{
    union
    {
        DWORD   dwOemId; /* Obsolete field - do not use */
        struct
        {
            WORD wProcessorArchitecture;
            WORD wReserved;
        } s1;
    } u1;
    DWORD       dwPageSize;
    qemu_ptr    lpMinimumApplicationAddress;
    qemu_ptr    lpMaximumApplicationAddress;
    qemu_ptr    dwActiveProcessorMask;
    DWORD       dwNumberOfProcessors;
    DWORD       dwProcessorType;
    DWORD       dwAllocationGranularity;
    WORD        wProcessorLevel;
    WORD        wProcessorRevision;
};

static inline void SYSTEM_INFO_h2g(struct qemu_SYSTEM_INFO *guest, const SYSTEM_INFO *host)
{
    guest->u1.s1.wProcessorArchitecture = host->wProcessorArchitecture;
    guest->u1.s1.wReserved = host->wReserved;
    guest->dwPageSize = host->dwPageSize;
    guest->lpMinimumApplicationAddress = (ULONG_PTR)host->lpMinimumApplicationAddress;
    if ((ULONG_PTR)host->lpMaximumApplicationAddress > ~0U)
        guest->lpMaximumApplicationAddress = ~0U;
    else
        guest->lpMaximumApplicationAddress = (ULONG_PTR)host->lpMaximumApplicationAddress;
    guest->dwActiveProcessorMask = host->dwActiveProcessorMask;
    guest->dwNumberOfProcessors = host->dwNumberOfProcessors;
    guest->dwProcessorType = host->dwProcessorType;
    guest->dwAllocationGranularity = host->dwAllocationGranularity;
    guest->wProcessorLevel = host->wProcessorLevel;
    guest->wProcessorRevision = host->wProcessorRevision;
}

#endif
