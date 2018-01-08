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

static void STARTUPINFO_h2g(struct qemu_STARTUPINFO *guest, const STARTUPINFOW *host)
{
    guest->cb = sizeof(*guest);
    guest->lpReserved = (ULONG_PTR)host->lpReserved;
    guest->lpDesktop = (ULONG_PTR)host->lpDesktop;
    guest->lpTitle = (ULONG_PTR)host->lpTitle;
    guest->dwX = host->dwX;
    guest->dwY = host->dwY;
    guest->dwXSize = host->dwXSize;
    guest->dwYSize = host->dwYSize;
    guest->dwXCountChars = host->dwXCountChars;
    guest->dwYCountChars = host->dwYCountChars;
    guest->dwFillAttribute = host->dwFillAttribute;
    guest->dwFlags = host->dwFlags;
    guest->wShowWindow = host->wShowWindow;
    guest->cbReserved2 = host->cbReserved2;
    guest->lpReserved2 = (ULONG_PTR)host->lpReserved2;
    guest->hStdInput = (ULONG_PTR)host->hStdInput;
    guest->hStdOutput = (ULONG_PTR)host->hStdOutput;
    guest->hStdError = (ULONG_PTR)host->hStdError;
}

static void STARTUPINFO_g2h(STARTUPINFOW *host, const struct qemu_STARTUPINFO *guest)
{
    host->cb = sizeof(*host);
    host->lpReserved = (WCHAR *)(ULONG_PTR)guest->lpReserved;
    host->lpDesktop = (WCHAR *)(ULONG_PTR)guest->lpDesktop;
    host->lpTitle = (WCHAR *)(ULONG_PTR)guest->lpTitle;
    host->dwX = guest->dwX;
    host->dwY = guest->dwY;
    host->dwXSize = guest->dwXSize;
    host->dwYSize = guest->dwYSize;
    host->dwXCountChars = guest->dwXCountChars;
    host->dwYCountChars = guest->dwYCountChars;
    host->dwFillAttribute = guest->dwFillAttribute;
    host->dwFlags = guest->dwFlags;
    host->wShowWindow = guest->wShowWindow;
    host->cbReserved2 = guest->cbReserved2;
    host->lpReserved2 = (BYTE *)(ULONG_PTR)guest->lpReserved2;
    host->hStdInput = HANDLE_g2h(guest->hStdInput);
    host->hStdOutput = HANDLE_g2h(guest->hStdOutput);
    host->hStdError = HANDLE_g2h(guest->hStdError);
}

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

struct qemu_PROCESS_INFORMATION
{
    qemu_handle hProcess;
    qemu_handle hThread;
    DWORD       dwProcessId;
    DWORD       dwThreadId;
};

static void PROCESS_INFORMATION_h2g(struct qemu_PROCESS_INFORMATION *guest, const PROCESS_INFORMATION *host)
{
    guest->hProcess = (LONG_PTR)host->hProcess;
    guest->hThread = (LONG_PTR)host->hThread;
    guest->dwProcessId = host->dwProcessId;
    guest->dwThreadId = host->dwThreadId;
}

#endif
