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

struct qemu_ACTCTX
{
    ULONG       cbSize;
    DWORD       dwFlags;
    qemu_ptr    lpSource;
    USHORT      wProcessorArchitecture;
    LANGID      wLangId;
    qemu_ptr    lpAssemblyDirectory;
    qemu_ptr    lpResourceName;
    qemu_ptr    lpApplicationName;
    qemu_handle hModule;
};

static void ACTCTX_h2g(struct qemu_ACTCTX *guest, const ACTCTXW *host)
{
    guest->dwFlags = host->dwFlags;
    guest->lpSource = (ULONG_PTR)host->lpSource;
    guest->wProcessorArchitecture = host->wProcessorArchitecture;
    guest->wLangId = host->wLangId;
    guest->lpAssemblyDirectory = (ULONG_PTR)host->lpAssemblyDirectory;
    guest->lpResourceName = (ULONG_PTR)host->lpResourceName;
    guest->lpApplicationName = (ULONG_PTR)host->lpApplicationName;
    guest->hModule = (ULONG_PTR)host->hModule;
}

static void ACTCTX_g2h(ACTCTXW *host, const struct qemu_ACTCTX *guest)
{
    host->dwFlags = guest->dwFlags;
    host->lpSource = (WCHAR *)(ULONG_PTR)guest->lpSource;
    host->wProcessorArchitecture = guest->wProcessorArchitecture;
    host->wLangId = guest->wLangId;
    host->lpAssemblyDirectory = (WCHAR *)(ULONG_PTR)guest->lpAssemblyDirectory;
    host->lpResourceName = (WCHAR *)(ULONG_PTR)guest->lpResourceName;
    host->lpApplicationName = (WCHAR *)(ULONG_PTR)guest->lpApplicationName;
    host->hModule = HANDLE_g2h(guest->hModule);
}

struct qemu_ACTIVATION_CONTEXT_BASIC_INFORMATION
{
    qemu_handle hActCtx;
    DWORD       dwFlags;
};

static void ACTIVATION_CONTEXT_BASIC_INFORMATION_h2g(struct qemu_ACTIVATION_CONTEXT_BASIC_INFORMATION *guest,
        const ACTIVATION_CONTEXT_BASIC_INFORMATION *host)
{
    guest->hActCtx = (ULONG_PTR)host->hActCtx;
    guest->dwFlags = host->dwFlags;
}

struct qemu_ACTIVATION_CONTEXT_DETAILED_INFORMATION
{
    DWORD dwFlags;
    DWORD ulFormatVersion;
    DWORD ulAssemblyCount;
    DWORD ulRootManifestPathType;
    DWORD ulRootManifestPathChars;
    DWORD ulRootConfigurationPathType;
    DWORD ulRootConfigurationPathChars;
    DWORD ulAppDirPathType;
    DWORD ulAppDirPathChars;
    qemu_ptr lpRootManifestPath;
    qemu_ptr lpRootConfigurationPath;
    qemu_ptr lpAppDirPath;
};

static void ACTIVATION_CONTEXT_DETAILED_INFORMATION_h2g(struct qemu_ACTIVATION_CONTEXT_DETAILED_INFORMATION *guest,
        const ACTIVATION_CONTEXT_DETAILED_INFORMATION *host)
{
    guest->dwFlags = host->dwFlags;
    guest->ulFormatVersion = host->ulFormatVersion;
    guest->ulAssemblyCount = host->ulAssemblyCount;
    guest->ulRootManifestPathType = host->ulRootManifestPathType;
    guest->ulRootManifestPathChars = host->ulRootManifestPathChars;
    guest->ulRootConfigurationPathType = host->ulRootConfigurationPathType;
    guest->ulRootConfigurationPathChars = host->ulRootConfigurationPathChars;
    guest->ulAppDirPathType = host->ulAppDirPathType;
    guest->ulAppDirPathChars = host->ulAppDirPathChars;
    guest->lpRootManifestPath = (ULONG_PTR)host->lpRootManifestPath;
    guest->lpRootConfigurationPath = (ULONG_PTR)host->lpRootConfigurationPath;
    guest->lpAppDirPath = (ULONG_PTR)host->lpAppDirPath;
}

struct qemu_ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION
{
    DWORD ulFlags;
    DWORD ulEncodedAssemblyIdentityLength;
    DWORD ulManifestPathType;
    DWORD ulManifestPathLength;
    LARGE_INTEGER liManifestLastWriteTime;
    DWORD ulPolicyPathType;
    DWORD ulPolicyPathLength;
    LARGE_INTEGER liPolicyLastWriteTime;
    DWORD ulMetadataSatelliteRosterIndex;
    DWORD ulManifestVersionMajor;
    DWORD ulManifestVersionMinor;
    DWORD ulPolicyVersionMajor;
    DWORD ulPolicyVersionMinor;
    DWORD ulAssemblyDirectoryNameLength;
    qemu_ptr lpAssemblyEncodedAssemblyIdentity;
    qemu_ptr lpAssemblyManifestPath;
    qemu_ptr lpAssemblyPolicyPath;
    qemu_ptr lpAssemblyDirectoryName;
    DWORD  ulFileCount;
};

static void ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION_h2g(
        struct qemu_ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION *guest,
        const ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION *host)
{
    guest->ulFlags = host->ulFlags;
    guest->ulEncodedAssemblyIdentityLength = host->ulEncodedAssemblyIdentityLength;
    guest->ulManifestPathType = host->ulManifestPathType;
    guest->ulManifestPathLength = host->ulManifestPathLength;
    guest->liManifestLastWriteTime = host->liManifestLastWriteTime;
    guest->ulPolicyPathType = host->ulPolicyPathType;
    guest->ulPolicyPathLength = host->ulPolicyPathLength;
    guest->liPolicyLastWriteTime = host->liPolicyLastWriteTime;
    guest->ulMetadataSatelliteRosterIndex = host->ulMetadataSatelliteRosterIndex;
    guest->ulManifestVersionMajor = host->ulManifestVersionMajor;
    guest->ulManifestVersionMinor = host->ulManifestVersionMinor;
    guest->ulPolicyVersionMajor = host->ulPolicyVersionMajor;
    guest->ulPolicyVersionMinor = host->ulPolicyVersionMinor;
    guest->ulAssemblyDirectoryNameLength = host->ulAssemblyDirectoryNameLength;
    guest->lpAssemblyEncodedAssemblyIdentity = (ULONG_PTR)host->lpAssemblyEncodedAssemblyIdentity;
    guest->lpAssemblyManifestPath = (ULONG_PTR)host->lpAssemblyManifestPath;
    guest->lpAssemblyPolicyPath = (ULONG_PTR)host->lpAssemblyPolicyPath;
    guest->lpAssemblyDirectoryName = (ULONG_PTR)host->lpAssemblyDirectoryName;
    guest->ulFileCount = host->ulFileCount;
}

struct qemu_ASSEMBLY_FILE_DETAILED_INFORMATION
{
    DWORD       ulFlags;
    DWORD       ulFilenameLength;
    DWORD       ulPathLength;
    qemu_ptr    lpFileName;
    qemu_ptr    lpFilePath;
};

static void ASSEMBLY_FILE_DETAILED_INFORMATION_h2g(struct qemu_ASSEMBLY_FILE_DETAILED_INFORMATION *guest,
        const ASSEMBLY_FILE_DETAILED_INFORMATION *host)
{
    guest->ulFlags = host->ulFlags;
    guest->ulFilenameLength = host->ulFilenameLength;
    guest->ulPathLength = host->ulPathLength;
    guest->lpFileName = (ULONG_PTR)host->lpFileName;
    guest->lpFilePath = (ULONG_PTR)host->lpFilePath;
}

struct qemu_ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA
{
    qemu_ptr    lpInformation;
    qemu_ptr    lpSectionBase;
    ULONG       ulSectionLength;
    qemu_ptr    lpSectionGlobalDataBase;
    ULONG       ulSectionGlobalDataLength;
};

static inline void ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA_g2h(
        ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA *host,
        const struct qemu_ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA *guest)
{
    host->lpInformation = (void *)(ULONG_PTR)guest->lpInformation;
    host->lpSectionBase = (void *)(ULONG_PTR)guest->lpSectionBase;
    host->ulSectionLength = guest->ulSectionLength;
    host->lpSectionGlobalDataBase = (void *)(ULONG_PTR)guest->lpSectionGlobalDataBase;
    host->ulSectionGlobalDataLength = guest->ulSectionGlobalDataLength;
}

static inline void ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA_h2g(
        struct qemu_ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA *guest,
        const ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA *host)
{
    guest->lpInformation = (ULONG_PTR)host->lpInformation;
    guest->lpSectionBase = (ULONG_PTR)host->lpSectionBase;
    guest->ulSectionLength = host->ulSectionLength;
    guest->lpSectionGlobalDataBase = (ULONG_PTR)host->lpSectionGlobalDataBase;
    guest->ulSectionGlobalDataLength = host->ulSectionGlobalDataLength;
}

struct qemu_ACTCTX_SECTION_KEYED_DATA
{
    ULONG       cbSize;
    ULONG       ulDataFormatVersion;
    qemu_ptr    lpData;
    ULONG       ulLength;
    qemu_ptr    lpSectionGlobalData;
    ULONG       ulSectionGlobalDataLength;
    qemu_ptr    lpSectionBase;
    ULONG       ulSectionTotalLength;
    qemu_handle hActCtx;
    ULONG       ulAssemblyRosterIndex;

    /* Non 2600 extra fields */
    ULONG ulFlags;
    struct qemu_ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA AssemblyMetadata;
};

static inline void ACTCTX_SECTION_KEYED_DATA_g2h(
        ACTCTX_SECTION_KEYED_DATA *host,
        const struct qemu_ACTCTX_SECTION_KEYED_DATA *guest)
{
    host->cbSize = sizeof(*host);
    host->ulDataFormatVersion = guest->ulDataFormatVersion;
    host->lpData = (void *)(ULONG_PTR)guest->lpData;
    host->ulLength = guest->ulLength;
    host->lpSectionGlobalData = (void *)(ULONG_PTR)guest->lpSectionGlobalData;
    host->ulSectionGlobalDataLength = guest->ulSectionGlobalDataLength;
    host->lpSectionBase = (void *)(ULONG_PTR)guest->lpSectionBase;
    host->ulSectionTotalLength = guest->ulSectionTotalLength;
    host->hActCtx = HANDLE_g2h(guest->hActCtx);
    host->ulAssemblyRosterIndex = guest->ulAssemblyRosterIndex;

    if (guest->cbSize == sizeof(*guest))
    {
        host->ulFlags = guest->ulFlags;
        ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA_g2h(&host->AssemblyMetadata, &guest->AssemblyMetadata);
    }
    else
    {
        host->ulFlags = 0;
        memset(&host->AssemblyMetadata, 0, sizeof(host->AssemblyMetadata));
    }
}

static inline void ACTCTX_SECTION_KEYED_DATA_h2g(
        struct qemu_ACTCTX_SECTION_KEYED_DATA *guest,
        const ACTCTX_SECTION_KEYED_DATA *host)
{
    guest->ulDataFormatVersion = host->ulDataFormatVersion;
    guest->lpData = (ULONG_PTR)host->lpData;
    guest->ulLength = host->ulLength;
    guest->lpSectionGlobalData = (ULONG_PTR)host->lpSectionGlobalData;
    guest->ulSectionGlobalDataLength = host->ulSectionGlobalDataLength;
    guest->lpSectionBase = (ULONG_PTR)host->lpSectionBase;
    guest->ulSectionTotalLength = host->ulSectionTotalLength;
    guest->hActCtx = (ULONG_PTR)host->hActCtx;
    guest->ulAssemblyRosterIndex = host->ulAssemblyRosterIndex;

    if (guest->cbSize == sizeof(*guest))
    {
        if (host->cbSize == sizeof(*host))
        {
            guest->ulFlags = guest->ulFlags;
            ACTCTX_SECTION_KEYED_DATA_ASSEMBLY_METADATA_h2g(&guest->AssemblyMetadata, &host->AssemblyMetadata);
        }
        else
        {
            guest->ulFlags = 0;
            memset(&guest->AssemblyMetadata, 0, sizeof(guest->AssemblyMetadata));
        }
    }
}

struct qemu_SECURITY_ATTRIBUTES
{
    DWORD       nLength;
    qemu_ptr    lpSecurityDescriptor;
    BOOL        bInheritHandle;
};

struct SA_conv_struct
{
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
};

static inline void SECURITY_ATTRIBUTES_g2h(struct SA_conv_struct *host, const struct qemu_SECURITY_ATTRIBUTES *guest)
{
    host->sa.nLength = sizeof(host->sa.nLength);
    if (guest->lpSecurityDescriptor)
    {
        host->sa.lpSecurityDescriptor = &host->sd;
        SECURITY_DESCRIPTOR_g2h(&host->sd, (struct qemu_SECURITY_DESCRIPTOR *)(ULONG_PTR)guest->lpSecurityDescriptor);
    }
    else
    {
        host->sa.lpSecurityDescriptor = NULL;
    }
    host->sa.bInheritHandle = guest->bInheritHandle;
}

struct qemu_OVERLAPPED
{
#ifdef WORDS_BIGENDIAN
        qemu_ptr InternalHigh;
        qemu_ptr Internal;
#else
        qemu_ptr Internal;
        qemu_ptr InternalHigh;
#endif
        union
        {
            struct
            {
#ifdef WORDS_BIGENDIAN
                DWORD OffsetHigh;
                DWORD Offset;
#else
                DWORD Offset;
                DWORD OffsetHigh;
#endif
            } DUMMYSTRUCTNAME;
            qemu_ptr Pointer;
        } DUMMYUNIONNAME;
        qemu_handle hEvent;
};

static inline void OVERLAPPED_g2h(OVERLAPPED *host, const struct qemu_OVERLAPPED *guest)
{
    host->InternalHigh = guest->InternalHigh;
    host->Internal = guest->Internal;
    host->OffsetHigh = guest->OffsetHigh;
    host->Offset = guest->Offset;
    host->hEvent = HANDLE_g2h(guest->hEvent);
}

static inline void OVERLAPPED_h2g(struct qemu_OVERLAPPED *guest, const OVERLAPPED *host)
{
    guest->InternalHigh = host->InternalHigh;
    guest->Internal = host->Internal;
    guest->OffsetHigh = host->OffsetHigh;
    guest->Offset = host->Offset;
    guest->hEvent = (ULONG_PTR)host->hEvent;
}

struct qemu_MEMORYSTATUS
{
    DWORD       dwLength;
    DWORD       dwMemoryLoad;
    qemu_ptr    dwTotalPhys;
    qemu_ptr    dwAvailPhys;
    qemu_ptr    dwTotalPageFile;
    qemu_ptr    dwAvailPageFile;
    qemu_ptr    dwTotalVirtual;
    qemu_ptr    dwAvailVirtual;
};

static inline void MEMORYSTATUS_h2g(struct qemu_MEMORYSTATUS *guest, const MEMORYSTATUS *host)
{
    guest->dwLength = sizeof(*guest);
    guest->dwMemoryLoad = host->dwMemoryLoad;
    guest->dwTotalPhys = host->dwTotalPhys;
    guest->dwAvailPhys = host->dwAvailPhys;
    guest->dwTotalPageFile = host->dwTotalPageFile;
    guest->dwAvailPageFile = host->dwAvailPageFile;
    guest->dwTotalVirtual = host->dwTotalVirtual;
    guest->dwAvailVirtual = host->dwAvailVirtual;
}

#endif
