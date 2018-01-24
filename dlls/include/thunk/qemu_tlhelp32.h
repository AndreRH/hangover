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

#endif
