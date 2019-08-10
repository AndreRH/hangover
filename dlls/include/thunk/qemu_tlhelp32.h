#ifndef HAVE_QEMU_TLHELP32_H
#define HAVE_QEMU_TLHELP32_H

struct qemu_MODULEENTRY32W
{
    DWORD       dwSize;
    DWORD       th32ModuleID;
    DWORD       th32ProcessID;
    DWORD       GlblcntUsage;
    DWORD       ProccntUsage;
    qemu_ptr    modBaseAddr;
    DWORD       modBaseSize;
    qemu_handle hModule;
    WCHAR       szModule[MAX_MODULE_NAME32 + 1];
    WCHAR       szExePath[MAX_PATH];
};

static inline void MODULEENTRY32W_h2g(struct qemu_MODULEENTRY32W *guest, const MODULEENTRY32W *host)
{
    guest->th32ModuleID = host->th32ModuleID;
    guest->th32ProcessID = host->th32ProcessID;
    guest->GlblcntUsage = host->GlblcntUsage;
    guest->ProccntUsage = host->ProccntUsage;
    guest->modBaseAddr = (ULONG_PTR)host->modBaseAddr;
    guest->modBaseSize = host->modBaseSize;
    guest->hModule = (ULONG_PTR)host->hModule;
    memcpy(guest->szModule, host->szModule, sizeof(guest->szModule));
    memcpy(guest->szExePath, host->szExePath, sizeof(guest->szExePath));
}

struct qemu_MODULEENTRY32
{
    DWORD       dwSize;
    DWORD       th32ModuleID;
    DWORD       th32ProcessID;
    DWORD       GlblcntUsage;
    DWORD       ProccntUsage;
    qemu_ptr    modBaseAddr;
    DWORD       modBaseSize;
    qemu_handle hModule;
    char       szModule[MAX_MODULE_NAME32 + 1];
    char       szExePath[MAX_PATH];
};

static inline void MODULEENTRY32_h2g(struct qemu_MODULEENTRY32 *guest, const MODULEENTRY32 *host)
{
    guest->th32ModuleID = host->th32ModuleID;
    guest->th32ProcessID = host->th32ProcessID;
    guest->GlblcntUsage = host->GlblcntUsage;
    guest->ProccntUsage = host->ProccntUsage;
    guest->modBaseAddr = (ULONG_PTR)host->modBaseAddr;
    guest->modBaseSize = host->modBaseSize;
    guest->hModule = (ULONG_PTR)host->hModule;
    memcpy(guest->szModule, host->szModule, sizeof(guest->szModule));
    memcpy(guest->szExePath, host->szExePath, sizeof(guest->szExePath));
}

struct qemu_PROCESSENTRY32A
{
    DWORD     dwSize;
    DWORD     cntUsage;
    DWORD     th32ProcessID;
    qemu_ptr  th32DefaultHeapID;
    DWORD     th32ModuleID;
    DWORD     cntThreads;
    DWORD     th32ParentProcessID;
    LONG      pcPriClassBase;
    DWORD     dwFlags;
    char      szExeFile[MAX_PATH];
};

struct qemu_PROCESSENTRY32W
{
    DWORD     dwSize;
    DWORD     cntUsage;
    DWORD     th32ProcessID;
    qemu_ptr  th32DefaultHeapID;
    DWORD     th32ModuleID;
    DWORD     cntThreads;
    DWORD     th32ParentProcessID;
    LONG      pcPriClassBase;
    DWORD     dwFlags;
    WCHAR     szExeFile[MAX_PATH];
};

static inline void PROCESSENTRY32A_h2g(struct qemu_PROCESSENTRY32A *guest, const PROCESSENTRY32 *host)
{
    guest->cntUsage = host->cntUsage;
    guest->th32ProcessID = host->th32ProcessID;
    guest->th32DefaultHeapID = host->th32DefaultHeapID;
    guest->th32ModuleID = host->th32ModuleID;
    guest->cntThreads = host->cntThreads;
    guest->th32ParentProcessID = host->th32ParentProcessID;
    guest->pcPriClassBase = host->pcPriClassBase;
    guest->dwFlags = host->dwFlags;
    memcpy(guest->szExeFile, host->szExeFile, sizeof(guest->szExeFile));
}

static inline void PROCESSENTRY32W_h2g(struct qemu_PROCESSENTRY32W *guest, const PROCESSENTRY32W *host)
{
    guest->cntUsage = host->cntUsage;
    guest->th32ProcessID = host->th32ProcessID;
    guest->th32DefaultHeapID = host->th32DefaultHeapID;
    guest->th32ModuleID = host->th32ModuleID;
    guest->cntThreads = host->cntThreads;
    guest->th32ParentProcessID = host->th32ParentProcessID;
    guest->pcPriClassBase = host->pcPriClassBase;
    guest->dwFlags = host->dwFlags;
    memcpy(guest->szExeFile, host->szExeFile, sizeof(guest->szExeFile));
}

#endif
