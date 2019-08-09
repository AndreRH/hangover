#ifndef HAVE_QEMU_THUNK_WINSVC_H
#define HAVE_QEMU_THUNK_WINSVC_H

struct qemu_QUERY_SERVICE_CONFIG
{
    DWORD    dwServiceType;
    DWORD    dwStartType;
    DWORD    dwErrorControl;
    qemu_ptr lpBinaryPathName;
    qemu_ptr lpLoadOrderGroup;
    DWORD    dwTagId;
    qemu_ptr lpDependencies;
    qemu_ptr lpServiceStartName;
    qemu_ptr lpDisplayName;
};

static inline void QUERY_SERVICE_CONFIG_g2h(QUERY_SERVICE_CONFIGW *host,
        const struct qemu_QUERY_SERVICE_CONFIG *guest)
{
    host->dwServiceType = guest->dwServiceType;
    host->dwStartType = guest->dwStartType;
    host->dwErrorControl = guest->dwErrorControl;
    host->lpBinaryPathName = (WCHAR *)(ULONG_PTR)guest->lpBinaryPathName;
    host->lpLoadOrderGroup = (WCHAR *)(ULONG_PTR)guest->lpLoadOrderGroup;
    host->dwTagId = guest->dwTagId;
    host->lpDependencies = (WCHAR *)(ULONG_PTR)guest->lpDependencies;
    host->lpServiceStartName = (WCHAR *)(ULONG_PTR)guest->lpServiceStartName;
    host->lpDisplayName = (WCHAR *)(ULONG_PTR)guest->lpDisplayName;
}

static inline void QUERY_SERVICE_CONFIG_h2g(struct qemu_QUERY_SERVICE_CONFIG *guest,
        const QUERY_SERVICE_CONFIGW *host)
{
    guest->dwServiceType = host->dwServiceType;
    guest->dwStartType = host->dwStartType;
    guest->dwErrorControl = host->dwErrorControl;
    guest->lpBinaryPathName = (ULONG_PTR)host->lpBinaryPathName;
    guest->lpLoadOrderGroup = (ULONG_PTR)host->lpLoadOrderGroup;
    guest->dwTagId = host->dwTagId;
    guest->lpDependencies = (ULONG_PTR)host->lpDependencies;
    guest->lpServiceStartName = (ULONG_PTR)host->lpServiceStartName;
    guest->lpDisplayName = (ULONG_PTR)host->lpDisplayName;
}

#endif
