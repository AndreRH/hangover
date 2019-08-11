/*
 * Copyright 2017 André Hentschel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <winsvc.h>
#include <lmserver.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_StartServiceCtrlDispatcherA
{
    struct qemu_syscall super;
    uint64_t servent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StartServiceCtrlDispatcherA(const SERVICE_TABLE_ENTRYA *servent)
{
    struct qemu_StartServiceCtrlDispatcherA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTSERVICECTRLDISPATCHERA);
    call.servent = (ULONG_PTR)servent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartServiceCtrlDispatcherA(struct qemu_syscall *call)
{
    struct qemu_StartServiceCtrlDispatcherA *c = (struct qemu_StartServiceCtrlDispatcherA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartServiceCtrlDispatcherA(QEMU_G2H(c->servent));
}

#endif

struct qemu_StartServiceCtrlDispatcherW
{
    struct qemu_syscall super;
    uint64_t servent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StartServiceCtrlDispatcherW(const SERVICE_TABLE_ENTRYW *servent)
{
    struct qemu_StartServiceCtrlDispatcherW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTSERVICECTRLDISPATCHERW);
    call.servent = (ULONG_PTR)servent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartServiceCtrlDispatcherW(struct qemu_syscall *call)
{
    struct qemu_StartServiceCtrlDispatcherW *c = (struct qemu_StartServiceCtrlDispatcherW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartServiceCtrlDispatcherW(QEMU_G2H(c->servent));
}

#endif

struct qemu_LockServiceDatabase
{
    struct qemu_syscall super;
    uint64_t hSCManager;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_LOCK WINAPI LockServiceDatabase (SC_HANDLE hSCManager)
{
    struct qemu_LockServiceDatabase call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCKSERVICEDATABASE);
    call.hSCManager = (ULONG_PTR)hSCManager;

    qemu_syscall(&call.super);

    return (SC_LOCK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LockServiceDatabase(struct qemu_syscall *call)
{
    struct qemu_LockServiceDatabase *c = (struct qemu_LockServiceDatabase *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)LockServiceDatabase(QEMU_G2H(c->hSCManager));
}

#endif

struct qemu_UnlockServiceDatabase
{
    struct qemu_syscall super;
    uint64_t ScLock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UnlockServiceDatabase (SC_LOCK ScLock)
{
    struct qemu_UnlockServiceDatabase call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNLOCKSERVICEDATABASE);
    call.ScLock = (ULONG_PTR)ScLock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnlockServiceDatabase(struct qemu_syscall *call)
{
    struct qemu_UnlockServiceDatabase *c = (struct qemu_UnlockServiceDatabase *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnlockServiceDatabase(QEMU_G2H(c->ScLock));
}

#endif

struct qemu_SetServiceStatus
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t lpStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetServiceStatus(SERVICE_STATUS_HANDLE hService, LPSERVICE_STATUS lpStatus)
{
    struct qemu_SetServiceStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSERVICESTATUS);
    call.hService = (ULONG_PTR)hService;
    call.lpStatus = (ULONG_PTR)lpStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetServiceStatus(struct qemu_syscall *call)
{
    struct qemu_SetServiceStatus *c = (struct qemu_SetServiceStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetServiceStatus(QEMU_G2H(c->hService), QEMU_G2H(c->lpStatus));
}

#endif

struct qemu_OpenSCManagerA
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t lpDatabaseName;
    uint64_t dwDesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_HANDLE WINAPI OpenSCManagerA(LPCSTR lpMachineName, LPCSTR lpDatabaseName,
        DWORD dwDesiredAccess)
{
    struct qemu_OpenSCManagerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENSCMANAGERA);
    call.lpMachineName = (ULONG_PTR)lpMachineName;
    call.lpDatabaseName = (ULONG_PTR)lpDatabaseName;
    call.dwDesiredAccess = (ULONG_PTR)dwDesiredAccess;

    qemu_syscall(&call.super);

    return (SC_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenSCManagerA(struct qemu_syscall *call)
{
    struct qemu_OpenSCManagerA *c = (struct qemu_OpenSCManagerA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenSCManagerA(QEMU_G2H(c->lpMachineName),
            QEMU_G2H(c->lpDatabaseName), c->dwDesiredAccess);
}

#endif

struct qemu_OpenSCManagerW
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t lpDatabaseName;
    uint64_t dwDesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_HANDLE WINAPI OpenSCManagerW(LPCWSTR lpMachineName, LPCWSTR lpDatabaseName,
    DWORD dwDesiredAccess)
{
    struct qemu_OpenSCManagerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENSCMANAGERW);
    call.lpMachineName = (ULONG_PTR)lpMachineName;
    call.lpDatabaseName = (ULONG_PTR)lpDatabaseName;
    call.dwDesiredAccess = (ULONG_PTR)dwDesiredAccess;

    qemu_syscall(&call.super);

    return (SC_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenSCManagerW(struct qemu_syscall *call)
{
    struct qemu_OpenSCManagerW *c = (struct qemu_OpenSCManagerW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenSCManagerW(QEMU_G2H(c->lpMachineName),
            QEMU_G2H(c->lpDatabaseName), c->dwDesiredAccess);
}

#endif

struct qemu_ControlService
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwControl;
    uint64_t lpServiceStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ControlService(SC_HANDLE hService, DWORD dwControl, LPSERVICE_STATUS lpServiceStatus)
{
    struct qemu_ControlService call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONTROLSERVICE);
    call.hService = (ULONG_PTR)hService;
    call.dwControl = (ULONG_PTR)dwControl;
    call.lpServiceStatus = (ULONG_PTR)lpServiceStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ControlService(struct qemu_syscall *call)
{
    struct qemu_ControlService *c = (struct qemu_ControlService *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ControlService(QEMU_G2H(c->hService), c->dwControl, QEMU_G2H(c->lpServiceStatus));
}

#endif

struct qemu_CloseServiceHandle
{
    struct qemu_syscall super;
    uint64_t hSCObject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CloseServiceHandle(SC_HANDLE hSCObject)
{
    struct qemu_CloseServiceHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSESERVICEHANDLE);
    call.hSCObject = (ULONG_PTR)hSCObject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseServiceHandle(struct qemu_syscall *call)
{
    struct qemu_CloseServiceHandle *c = (struct qemu_CloseServiceHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CloseServiceHandle(QEMU_G2H(c->hSCObject));
}

#endif

struct qemu_OpenServiceA
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpServiceName;
    uint64_t dwDesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_HANDLE WINAPI OpenServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, DWORD dwDesiredAccess)
{
    struct qemu_OpenServiceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENSERVICEA);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.dwDesiredAccess = (ULONG_PTR)dwDesiredAccess;

    qemu_syscall(&call.super);

    return (SC_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenServiceA(struct qemu_syscall *call)
{
    struct qemu_OpenServiceA *c = (struct qemu_OpenServiceA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenServiceA(QEMU_G2H(c->hSCManager),
            QEMU_G2H(c->lpServiceName), c->dwDesiredAccess);
}

#endif

struct qemu_OpenServiceW
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpServiceName;
    uint64_t dwDesiredAccess;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_HANDLE WINAPI OpenServiceW(SC_HANDLE hSCManager, LPCWSTR lpServiceName, DWORD dwDesiredAccess)
{
    struct qemu_OpenServiceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENSERVICEW);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.dwDesiredAccess = (ULONG_PTR)dwDesiredAccess;

    qemu_syscall(&call.super);

    return (SC_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenServiceW(struct qemu_syscall *call)
{
    struct qemu_OpenServiceW *c = (struct qemu_OpenServiceW *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenServiceW(QEMU_G2H(c->hSCManager),
            QEMU_G2H(c->lpServiceName), c->dwDesiredAccess);
}

#endif

struct qemu_CreateServiceW
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpServiceName;
    uint64_t lpDisplayName;
    uint64_t dwDesiredAccess;
    uint64_t dwServiceType;
    uint64_t dwStartType;
    uint64_t dwErrorControl;
    uint64_t lpBinaryPathName;
    uint64_t lpLoadOrderGroup;
    uint64_t lpdwTagId;
    uint64_t lpDependencies;
    uint64_t lpServiceStartName;
    uint64_t lpPassword;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_HANDLE WINAPI CreateServiceW(SC_HANDLE hSCManager, LPCWSTR lpServiceName,
        LPCWSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType,
        DWORD dwErrorControl, LPCWSTR lpBinaryPathName, LPCWSTR lpLoadOrderGroup,
        LPDWORD lpdwTagId, LPCWSTR lpDependencies, LPCWSTR lpServiceStartName,
        LPCWSTR lpPassword)
{
    struct qemu_CreateServiceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESERVICEW);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;
    call.dwDesiredAccess = (ULONG_PTR)dwDesiredAccess;
    call.dwServiceType = (ULONG_PTR)dwServiceType;
    call.dwStartType = (ULONG_PTR)dwStartType;
    call.dwErrorControl = (ULONG_PTR)dwErrorControl;
    call.lpBinaryPathName = (ULONG_PTR)lpBinaryPathName;
    call.lpLoadOrderGroup = (ULONG_PTR)lpLoadOrderGroup;
    call.lpdwTagId = (ULONG_PTR)lpdwTagId;
    call.lpDependencies = (ULONG_PTR)lpDependencies;
    call.lpServiceStartName = (ULONG_PTR)lpServiceStartName;
    call.lpPassword = (ULONG_PTR)lpPassword;

    qemu_syscall(&call.super);

    return (SC_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateServiceW(struct qemu_syscall *call)
{
    struct qemu_CreateServiceW *c = (struct qemu_CreateServiceW *)call;
    WINE_FIXME("Binary %s.\n", wine_dbgstr_w(QEMU_G2H(c->lpBinaryPathName)));
    c->super.iret = (ULONG_PTR)CreateServiceW(QEMU_G2H(c->hSCManager),
            QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpDisplayName),
            c->dwDesiredAccess, c->dwServiceType, c->dwStartType,
            c->dwErrorControl, QEMU_G2H(c->lpBinaryPathName),
            QEMU_G2H(c->lpLoadOrderGroup), QEMU_G2H(c->lpdwTagId),
            QEMU_G2H(c->lpDependencies), QEMU_G2H(c->lpServiceStartName),
            QEMU_G2H(c->lpPassword));
}

#endif

struct qemu_CreateServiceA
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpServiceName;
    uint64_t lpDisplayName;
    uint64_t dwDesiredAccess;
    uint64_t dwServiceType;
    uint64_t dwStartType;
    uint64_t dwErrorControl;
    uint64_t lpBinaryPathName;
    uint64_t lpLoadOrderGroup;
    uint64_t lpdwTagId;
    uint64_t lpDependencies;
    uint64_t lpServiceStartName;
    uint64_t lpPassword;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SC_HANDLE WINAPI CreateServiceA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPCSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword)
{
    struct qemu_CreateServiceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATESERVICEA);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;
    call.dwDesiredAccess = (ULONG_PTR)dwDesiredAccess;
    call.dwServiceType = (ULONG_PTR)dwServiceType;
    call.dwStartType = (ULONG_PTR)dwStartType;
    call.dwErrorControl = (ULONG_PTR)dwErrorControl;
    call.lpBinaryPathName = (ULONG_PTR)lpBinaryPathName;
    call.lpLoadOrderGroup = (ULONG_PTR)lpLoadOrderGroup;
    call.lpdwTagId = (ULONG_PTR)lpdwTagId;
    call.lpDependencies = (ULONG_PTR)lpDependencies;
    call.lpServiceStartName = (ULONG_PTR)lpServiceStartName;
    call.lpPassword = (ULONG_PTR)lpPassword;

    qemu_syscall(&call.super);

    return (SC_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateServiceA(struct qemu_syscall *call)
{
    struct qemu_CreateServiceA *c = (struct qemu_CreateServiceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateServiceA(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpDisplayName), c->dwDesiredAccess, c->dwServiceType, c->dwStartType, c->dwErrorControl, QEMU_G2H(c->lpBinaryPathName), QEMU_G2H(c->lpLoadOrderGroup), QEMU_G2H(c->lpdwTagId), QEMU_G2H(c->lpDependencies), QEMU_G2H(c->lpServiceStartName), QEMU_G2H(c->lpPassword));
}

#endif

struct qemu_DeleteService
{
    struct qemu_syscall super;
    uint64_t hService;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteService(SC_HANDLE hService)
{
    struct qemu_DeleteService call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETESERVICE);
    call.hService = (ULONG_PTR)hService;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteService(struct qemu_syscall *call)
{
    struct qemu_DeleteService *c = (struct qemu_DeleteService *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteService(QEMU_G2H(c->hService));
}

#endif

struct qemu_StartServiceA
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwNumServiceArgs;
    uint64_t lpServiceArgVectors;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StartServiceA(SC_HANDLE hService, DWORD dwNumServiceArgs, LPCSTR *lpServiceArgVectors)
{
    struct qemu_StartServiceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTSERVICEA);
    call.hService = (ULONG_PTR)hService;
    call.dwNumServiceArgs = (ULONG_PTR)dwNumServiceArgs;
    call.lpServiceArgVectors = (ULONG_PTR)lpServiceArgVectors;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartServiceA(struct qemu_syscall *call)
{
    struct qemu_StartServiceA *c = (struct qemu_StartServiceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartServiceA(QEMU_G2H(c->hService), c->dwNumServiceArgs, QEMU_G2H(c->lpServiceArgVectors));
}

#endif

struct qemu_StartServiceW
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwNumServiceArgs;
    uint64_t lpServiceArgVectors;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StartServiceW(SC_HANDLE hService, DWORD dwNumServiceArgs, LPCWSTR *lpServiceArgVectors)
{
    struct qemu_StartServiceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTSERVICEW);
    call.hService = (ULONG_PTR)hService;
    call.dwNumServiceArgs = (ULONG_PTR)dwNumServiceArgs;
    call.lpServiceArgVectors = (ULONG_PTR)lpServiceArgVectors;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartServiceW(struct qemu_syscall *call)
{
    struct qemu_StartServiceW *c = (struct qemu_StartServiceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartServiceW(QEMU_G2H(c->hService), c->dwNumServiceArgs, QEMU_G2H(c->lpServiceArgVectors));
}

#endif

struct qemu_QueryServiceStatus
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t lpservicestatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceStatus(SC_HANDLE hService, LPSERVICE_STATUS lpservicestatus)
{
    struct qemu_QueryServiceStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICESTATUS);
    call.hService = (ULONG_PTR)hService;
    call.lpservicestatus = (ULONG_PTR)lpservicestatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceStatus(struct qemu_syscall *call)
{
    struct qemu_QueryServiceStatus *c = (struct qemu_QueryServiceStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceStatus(QEMU_G2H(c->hService), QEMU_G2H(c->lpservicestatus));
}

#endif

struct qemu_QueryServiceStatusEx
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t InfoLevel;
    uint64_t lpBuffer;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceStatusEx(SC_HANDLE hService, SC_STATUS_TYPE InfoLevel, LPBYTE lpBuffer, DWORD cbBufSize, LPDWORD pcbBytesNeeded)
{
    struct qemu_QueryServiceStatusEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICESTATUSEX);
    call.hService = (ULONG_PTR)hService;
    call.InfoLevel = (ULONG_PTR)InfoLevel;
    call.lpBuffer = (ULONG_PTR)lpBuffer;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceStatusEx(struct qemu_syscall *call)
{
    struct qemu_QueryServiceStatusEx *c = (struct qemu_QueryServiceStatusEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceStatusEx(QEMU_G2H(c->hService), c->InfoLevel, QEMU_G2H(c->lpBuffer), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
}

#endif

struct qemu_QueryServiceConfigA
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t config;
    uint64_t size;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceConfigA(SC_HANDLE hService, LPQUERY_SERVICE_CONFIGA config, DWORD size, LPDWORD needed)
{
    struct qemu_QueryServiceConfigA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICECONFIGA);
    call.hService = (ULONG_PTR)hService;
    call.config = (ULONG_PTR)config;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceConfigA(struct qemu_syscall *call)
{
    struct qemu_QueryServiceConfigA *c = (struct qemu_QueryServiceConfigA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceConfigA(QEMU_G2H(c->hService), QEMU_G2H(c->config), c->size, QEMU_G2H(c->needed));
}

#endif

struct qemu_QueryServiceConfigW
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t lpServiceConfig;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceConfigW(SC_HANDLE hService, LPQUERY_SERVICE_CONFIGW lpServiceConfig,
        DWORD cbBufSize, LPDWORD pcbBytesNeeded)
{
    struct qemu_QueryServiceConfigW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICECONFIGW);
    call.hService = (ULONG_PTR)hService;
    call.lpServiceConfig = (ULONG_PTR)lpServiceConfig;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return TRUE;
}

#else

void qemu_QueryServiceConfigW(struct qemu_syscall *call)
{
    struct qemu_QueryServiceConfigW *c = (struct qemu_QueryServiceConfigW *)call;
    WINE_TRACE("\n");
    c->super.iret = QueryServiceConfigW(QEMU_G2H(c->hService), QEMU_G2H(c->lpServiceConfig),
            c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
#if GUEST_BIT != HOST_BIT
    if (c->super.iret)
    {
        QUERY_SERVICE_CONFIG_h2g(QEMU_G2H(c->lpServiceConfig), QEMU_G2H(c->lpServiceConfig));
    }
#endif
}

#endif

struct qemu_QueryServiceConfig2A
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwLevel;
    uint64_t buffer;
    uint64_t size;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceConfig2A(SC_HANDLE hService, DWORD dwLevel, LPBYTE buffer, DWORD size, LPDWORD needed)
{
    struct qemu_QueryServiceConfig2A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICECONFIG2A);
    call.hService = (ULONG_PTR)hService;
    call.dwLevel = (ULONG_PTR)dwLevel;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceConfig2A(struct qemu_syscall *call)
{
    struct qemu_QueryServiceConfig2A *c = (struct qemu_QueryServiceConfig2A *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceConfig2A(QEMU_G2H(c->hService), c->dwLevel, QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->needed));
}

#endif

struct qemu_QueryServiceConfig2W
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwLevel;
    uint64_t buffer;
    uint64_t size;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceConfig2W(SC_HANDLE hService, DWORD dwLevel, LPBYTE buffer, DWORD size, LPDWORD needed)
{
    struct qemu_QueryServiceConfig2W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICECONFIG2W);
    call.hService = (ULONG_PTR)hService;
    call.dwLevel = (ULONG_PTR)dwLevel;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceConfig2W(struct qemu_syscall *call)
{
    struct qemu_QueryServiceConfig2W *c = (struct qemu_QueryServiceConfig2W *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceConfig2W(QEMU_G2H(c->hService), c->dwLevel, QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->needed));
}

#endif

struct qemu_EnumServicesStatusA
{
    struct qemu_syscall super;
    uint64_t hmngr;
    uint64_t type;
    uint64_t state;
    uint64_t services;
    uint64_t size;
    uint64_t needed;
    uint64_t returned;
    uint64_t resume_handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumServicesStatusA(SC_HANDLE hmngr, DWORD type, DWORD state, LPENUM_SERVICE_STATUSA services, DWORD size, LPDWORD needed, LPDWORD returned, LPDWORD resume_handle)
{
    struct qemu_EnumServicesStatusA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSERVICESSTATUSA);
    call.hmngr = (ULONG_PTR)hmngr;
    call.type = (ULONG_PTR)type;
    call.state = (ULONG_PTR)state;
    call.services = (ULONG_PTR)services;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;
    call.returned = (ULONG_PTR)returned;
    call.resume_handle = (ULONG_PTR)resume_handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumServicesStatusA(struct qemu_syscall *call)
{
    struct qemu_EnumServicesStatusA *c = (struct qemu_EnumServicesStatusA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumServicesStatusA(QEMU_G2H(c->hmngr), c->type, c->state, QEMU_G2H(c->services), c->size, QEMU_G2H(c->needed), QEMU_G2H(c->returned), QEMU_G2H(c->resume_handle));
}

#endif

struct qemu_EnumServicesStatusW
{
    struct qemu_syscall super;
    uint64_t hmngr;
    uint64_t type;
    uint64_t state;
    uint64_t services;
    uint64_t size;
    uint64_t needed;
    uint64_t returned;
    uint64_t resume_handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumServicesStatusW(SC_HANDLE hmngr, DWORD type, DWORD state, LPENUM_SERVICE_STATUSW services, DWORD size, LPDWORD needed, LPDWORD returned, LPDWORD resume_handle)
{
    struct qemu_EnumServicesStatusW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSERVICESSTATUSW);
    call.hmngr = (ULONG_PTR)hmngr;
    call.type = (ULONG_PTR)type;
    call.state = (ULONG_PTR)state;
    call.services = (ULONG_PTR)services;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;
    call.returned = (ULONG_PTR)returned;
    call.resume_handle = (ULONG_PTR)resume_handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumServicesStatusW(struct qemu_syscall *call)
{
    struct qemu_EnumServicesStatusW *c = (struct qemu_EnumServicesStatusW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumServicesStatusW(QEMU_G2H(c->hmngr), c->type, c->state, QEMU_G2H(c->services), c->size, QEMU_G2H(c->needed), QEMU_G2H(c->returned), QEMU_G2H(c->resume_handle));
}

#endif

struct qemu_EnumServicesStatusExA
{
    struct qemu_syscall super;
    uint64_t hmngr;
    uint64_t level;
    uint64_t type;
    uint64_t state;
    uint64_t buffer;
    uint64_t size;
    uint64_t needed;
    uint64_t returned;
    uint64_t resume_handle;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumServicesStatusExA(SC_HANDLE hmngr, SC_ENUM_TYPE level, DWORD type, DWORD state, LPBYTE buffer, DWORD size, LPDWORD needed, LPDWORD returned, LPDWORD resume_handle, LPCSTR group)
{
    struct qemu_EnumServicesStatusExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSERVICESSTATUSEXA);
    call.hmngr = (ULONG_PTR)hmngr;
    call.level = (ULONG_PTR)level;
    call.type = (ULONG_PTR)type;
    call.state = (ULONG_PTR)state;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;
    call.returned = (ULONG_PTR)returned;
    call.resume_handle = (ULONG_PTR)resume_handle;
    call.group = (ULONG_PTR)group;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumServicesStatusExA(struct qemu_syscall *call)
{
    struct qemu_EnumServicesStatusExA *c = (struct qemu_EnumServicesStatusExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumServicesStatusExA(QEMU_G2H(c->hmngr), c->level, c->type, c->state, QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->needed), QEMU_G2H(c->returned), QEMU_G2H(c->resume_handle), QEMU_G2H(c->group));
}

#endif

struct qemu_EnumServicesStatusExW
{
    struct qemu_syscall super;
    uint64_t hmngr;
    uint64_t level;
    uint64_t type;
    uint64_t state;
    uint64_t buffer;
    uint64_t size;
    uint64_t needed;
    uint64_t returned;
    uint64_t resume_handle;
    uint64_t group;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumServicesStatusExW(SC_HANDLE hmngr, SC_ENUM_TYPE level, DWORD type, DWORD state, LPBYTE buffer, DWORD size, LPDWORD needed, LPDWORD returned, LPDWORD resume_handle, LPCWSTR group)
{
    struct qemu_EnumServicesStatusExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMSERVICESSTATUSEXW);
    call.hmngr = (ULONG_PTR)hmngr;
    call.level = (ULONG_PTR)level;
    call.type = (ULONG_PTR)type;
    call.state = (ULONG_PTR)state;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;
    call.needed = (ULONG_PTR)needed;
    call.returned = (ULONG_PTR)returned;
    call.resume_handle = (ULONG_PTR)resume_handle;
    call.group = (ULONG_PTR)group;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumServicesStatusExW(struct qemu_syscall *call)
{
    struct qemu_EnumServicesStatusExW *c = (struct qemu_EnumServicesStatusExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumServicesStatusExW(QEMU_G2H(c->hmngr), c->level, c->type, c->state, QEMU_G2H(c->buffer), c->size, QEMU_G2H(c->needed), QEMU_G2H(c->returned), QEMU_G2H(c->resume_handle), QEMU_G2H(c->group));
}

#endif

struct qemu_GetServiceKeyNameA
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpDisplayName;
    uint64_t lpServiceName;
    uint64_t lpcchBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetServiceKeyNameA(SC_HANDLE hSCManager, LPCSTR lpDisplayName, LPSTR lpServiceName, LPDWORD lpcchBuffer)
{
    struct qemu_GetServiceKeyNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSERVICEKEYNAMEA);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpcchBuffer = (ULONG_PTR)lpcchBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetServiceKeyNameA(struct qemu_syscall *call)
{
    struct qemu_GetServiceKeyNameA *c = (struct qemu_GetServiceKeyNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetServiceKeyNameA(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpDisplayName), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpcchBuffer));
}

#endif

struct qemu_GetServiceKeyNameW
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpDisplayName;
    uint64_t lpServiceName;
    uint64_t lpcchBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetServiceKeyNameW(SC_HANDLE hSCManager, LPCWSTR lpDisplayName, LPWSTR lpServiceName, LPDWORD lpcchBuffer)
{
    struct qemu_GetServiceKeyNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSERVICEKEYNAMEW);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpcchBuffer = (ULONG_PTR)lpcchBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetServiceKeyNameW(struct qemu_syscall *call)
{
    struct qemu_GetServiceKeyNameW *c = (struct qemu_GetServiceKeyNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetServiceKeyNameW(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpDisplayName), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpcchBuffer));
}

#endif

struct qemu_QueryServiceLockStatusA
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpLockStatus;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceLockStatusA(SC_HANDLE hSCManager, LPQUERY_SERVICE_LOCK_STATUSA lpLockStatus, DWORD cbBufSize, LPDWORD pcbBytesNeeded)
{
    struct qemu_QueryServiceLockStatusA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICELOCKSTATUSA);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpLockStatus = (ULONG_PTR)lpLockStatus;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceLockStatusA(struct qemu_syscall *call)
{
    struct qemu_QueryServiceLockStatusA *c = (struct qemu_QueryServiceLockStatusA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceLockStatusA(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpLockStatus), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
}

#endif

struct qemu_QueryServiceLockStatusW
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpLockStatus;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceLockStatusW(SC_HANDLE hSCManager, LPQUERY_SERVICE_LOCK_STATUSW lpLockStatus, DWORD cbBufSize, LPDWORD pcbBytesNeeded)
{
    struct qemu_QueryServiceLockStatusW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICELOCKSTATUSW);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpLockStatus = (ULONG_PTR)lpLockStatus;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceLockStatusW(struct qemu_syscall *call)
{
    struct qemu_QueryServiceLockStatusW *c = (struct qemu_QueryServiceLockStatusW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceLockStatusW(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpLockStatus), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
}

#endif

struct qemu_GetServiceDisplayNameA
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpServiceName;
    uint64_t lpDisplayName;
    uint64_t lpcchBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetServiceDisplayNameA(SC_HANDLE hSCManager, LPCSTR lpServiceName, LPSTR lpDisplayName, LPDWORD lpcchBuffer)
{
    struct qemu_GetServiceDisplayNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSERVICEDISPLAYNAMEA);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;
    call.lpcchBuffer = (ULONG_PTR)lpcchBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetServiceDisplayNameA(struct qemu_syscall *call)
{
    struct qemu_GetServiceDisplayNameA *c = (struct qemu_GetServiceDisplayNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetServiceDisplayNameA(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpDisplayName), QEMU_G2H(c->lpcchBuffer));
}

#endif

struct qemu_GetServiceDisplayNameW
{
    struct qemu_syscall super;
    uint64_t hSCManager;
    uint64_t lpServiceName;
    uint64_t lpDisplayName;
    uint64_t lpcchBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetServiceDisplayNameW(SC_HANDLE hSCManager, LPCWSTR lpServiceName, LPWSTR lpDisplayName, LPDWORD lpcchBuffer)
{
    struct qemu_GetServiceDisplayNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSERVICEDISPLAYNAMEW);
    call.hSCManager = (ULONG_PTR)hSCManager;
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;
    call.lpcchBuffer = (ULONG_PTR)lpcchBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetServiceDisplayNameW(struct qemu_syscall *call)
{
    struct qemu_GetServiceDisplayNameW *c = (struct qemu_GetServiceDisplayNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetServiceDisplayNameW(QEMU_G2H(c->hSCManager), QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpDisplayName), QEMU_G2H(c->lpcchBuffer));
}

#endif

struct qemu_ChangeServiceConfigW
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwServiceType;
    uint64_t dwStartType;
    uint64_t dwErrorControl;
    uint64_t lpBinaryPathName;
    uint64_t lpLoadOrderGroup;
    uint64_t lpdwTagId;
    uint64_t lpDependencies;
    uint64_t lpServiceStartName;
    uint64_t lpPassword;
    uint64_t lpDisplayName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChangeServiceConfigW(SC_HANDLE hService, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCWSTR lpBinaryPathName, LPCWSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCWSTR lpDependencies, LPCWSTR lpServiceStartName, LPCWSTR lpPassword, LPCWSTR lpDisplayName)
{
    struct qemu_ChangeServiceConfigW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGESERVICECONFIGW);
    call.hService = (ULONG_PTR)hService;
    call.dwServiceType = (ULONG_PTR)dwServiceType;
    call.dwStartType = (ULONG_PTR)dwStartType;
    call.dwErrorControl = (ULONG_PTR)dwErrorControl;
    call.lpBinaryPathName = (ULONG_PTR)lpBinaryPathName;
    call.lpLoadOrderGroup = (ULONG_PTR)lpLoadOrderGroup;
    call.lpdwTagId = (ULONG_PTR)lpdwTagId;
    call.lpDependencies = (ULONG_PTR)lpDependencies;
    call.lpServiceStartName = (ULONG_PTR)lpServiceStartName;
    call.lpPassword = (ULONG_PTR)lpPassword;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeServiceConfigW(struct qemu_syscall *call)
{
    struct qemu_ChangeServiceConfigW *c = (struct qemu_ChangeServiceConfigW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeServiceConfigW(QEMU_G2H(c->hService), c->dwServiceType, c->dwStartType, c->dwErrorControl, QEMU_G2H(c->lpBinaryPathName), QEMU_G2H(c->lpLoadOrderGroup), QEMU_G2H(c->lpdwTagId), QEMU_G2H(c->lpDependencies), QEMU_G2H(c->lpServiceStartName), QEMU_G2H(c->lpPassword), QEMU_G2H(c->lpDisplayName));
}

#endif

struct qemu_ChangeServiceConfigA
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwServiceType;
    uint64_t dwStartType;
    uint64_t dwErrorControl;
    uint64_t lpBinaryPathName;
    uint64_t lpLoadOrderGroup;
    uint64_t lpdwTagId;
    uint64_t lpDependencies;
    uint64_t lpServiceStartName;
    uint64_t lpPassword;
    uint64_t lpDisplayName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChangeServiceConfigA(SC_HANDLE hService, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCSTR lpBinaryPathName, LPCSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCSTR lpDependencies, LPCSTR lpServiceStartName, LPCSTR lpPassword, LPCSTR lpDisplayName)
{
    struct qemu_ChangeServiceConfigA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGESERVICECONFIGA);
    call.hService = (ULONG_PTR)hService;
    call.dwServiceType = (ULONG_PTR)dwServiceType;
    call.dwStartType = (ULONG_PTR)dwStartType;
    call.dwErrorControl = (ULONG_PTR)dwErrorControl;
    call.lpBinaryPathName = (ULONG_PTR)lpBinaryPathName;
    call.lpLoadOrderGroup = (ULONG_PTR)lpLoadOrderGroup;
    call.lpdwTagId = (ULONG_PTR)lpdwTagId;
    call.lpDependencies = (ULONG_PTR)lpDependencies;
    call.lpServiceStartName = (ULONG_PTR)lpServiceStartName;
    call.lpPassword = (ULONG_PTR)lpPassword;
    call.lpDisplayName = (ULONG_PTR)lpDisplayName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeServiceConfigA(struct qemu_syscall *call)
{
    struct qemu_ChangeServiceConfigA *c = (struct qemu_ChangeServiceConfigA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeServiceConfigA(QEMU_G2H(c->hService), c->dwServiceType, c->dwStartType, c->dwErrorControl, QEMU_G2H(c->lpBinaryPathName), QEMU_G2H(c->lpLoadOrderGroup), QEMU_G2H(c->lpdwTagId), QEMU_G2H(c->lpDependencies), QEMU_G2H(c->lpServiceStartName), QEMU_G2H(c->lpPassword), QEMU_G2H(c->lpDisplayName));
}

#endif

struct qemu_ChangeServiceConfig2A
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwInfoLevel;
    uint64_t lpInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChangeServiceConfig2A(SC_HANDLE hService, DWORD dwInfoLevel, LPVOID lpInfo)
{
    struct qemu_ChangeServiceConfig2A call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGESERVICECONFIG2A);
    call.hService = (ULONG_PTR)hService;
    call.dwInfoLevel = (ULONG_PTR)dwInfoLevel;
    call.lpInfo = (ULONG_PTR)lpInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeServiceConfig2A(struct qemu_syscall *call)
{
    struct qemu_ChangeServiceConfig2A *c = (struct qemu_ChangeServiceConfig2A *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChangeServiceConfig2A(QEMU_G2H(c->hService), c->dwInfoLevel, QEMU_G2H(c->lpInfo));
}

#endif

struct qemu_ChangeServiceConfig2W
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwInfoLevel;
    uint64_t lpInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ChangeServiceConfig2W(SC_HANDLE hService, DWORD dwInfoLevel, LPVOID lpInfo)
{
    struct qemu_ChangeServiceConfig2W call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGESERVICECONFIG2W);
    call.hService = (ULONG_PTR)hService;
    call.dwInfoLevel = (ULONG_PTR)dwInfoLevel;
    call.lpInfo = (ULONG_PTR)lpInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeServiceConfig2W(struct qemu_syscall *call)
{
    struct qemu_ChangeServiceConfig2W *c = (struct qemu_ChangeServiceConfig2W *)call;
    DWORD level;
    void *info;
    SERVICE_FAILURE_ACTIONSW fail_actions;
    SERVICE_DESCRIPTIONW description;
    SERVICE_REQUIRED_PRIVILEGES_INFOW priv;

    WINE_TRACE("\n");
    level = c->dwInfoLevel;
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->lpInfo);
#else
    switch (level)
    {
        case SERVICE_CONFIG_DESCRIPTION:
            SERVICE_DESCRIPTION_g2h(&description, QEMU_G2H(c->lpInfo));
            info = &description;
            break;

        case SERVICE_CONFIG_FAILURE_ACTIONS:
            SERVICE_FAILURE_ACTIONS_g2h(&fail_actions, QEMU_G2H(c->lpInfo));
            info = &fail_actions;
            break;

        case SERVICE_CONFIG_REQUIRED_PRIVILEGES_INFO:
            SERVICE_REQUIRED_PRIVILEGES_INFO_g2h(&priv, QEMU_G2H(c->lpInfo));
            info = &priv;
            break;

        default:
            WINE_FIXME("Unhandled info level %u.\n", level);
            info = QEMU_G2H(c->lpInfo);
    }
#endif

    c->super.iret = ChangeServiceConfig2W(QEMU_G2H(c->hService), level, info);
}

#endif

struct qemu_QueryServiceObjectSecurity
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwSecurityInformation;
    uint64_t lpSecurityDescriptor;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryServiceObjectSecurity(SC_HANDLE hService, SECURITY_INFORMATION dwSecurityInformation, PSECURITY_DESCRIPTOR lpSecurityDescriptor, DWORD cbBufSize, LPDWORD pcbBytesNeeded)
{
    struct qemu_QueryServiceObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYSERVICEOBJECTSECURITY);
    call.hService = (ULONG_PTR)hService;
    call.dwSecurityInformation = (ULONG_PTR)dwSecurityInformation;
    call.lpSecurityDescriptor = (ULONG_PTR)lpSecurityDescriptor;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryServiceObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_QueryServiceObjectSecurity *c = (struct qemu_QueryServiceObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryServiceObjectSecurity(QEMU_G2H(c->hService), c->dwSecurityInformation, QEMU_G2H(c->lpSecurityDescriptor), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded));
}

#endif

struct qemu_SetServiceObjectSecurity
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwSecurityInformation;
    uint64_t lpSecurityDescriptor;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetServiceObjectSecurity(SC_HANDLE hService, SECURITY_INFORMATION dwSecurityInformation, PSECURITY_DESCRIPTOR lpSecurityDescriptor)
{
    struct qemu_SetServiceObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSERVICEOBJECTSECURITY);
    call.hService = (ULONG_PTR)hService;
    call.dwSecurityInformation = (ULONG_PTR)dwSecurityInformation;
    call.lpSecurityDescriptor = (ULONG_PTR)lpSecurityDescriptor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetServiceObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_SetServiceObjectSecurity *c = (struct qemu_SetServiceObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetServiceObjectSecurity(QEMU_G2H(c->hService), c->dwSecurityInformation, QEMU_G2H(c->lpSecurityDescriptor));
}

#endif

struct qemu_SetServiceBits
{
    struct qemu_syscall super;
    uint64_t hServiceStatus;
    uint64_t dwServiceBits;
    uint64_t bSetBitsOn;
    uint64_t bUpdateImmediately;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetServiceBits(SERVICE_STATUS_HANDLE hServiceStatus, DWORD dwServiceBits, BOOL bSetBitsOn, BOOL bUpdateImmediately)
{
    struct qemu_SetServiceBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSERVICEBITS);
    call.hServiceStatus = (ULONG_PTR)hServiceStatus;
    call.dwServiceBits = (ULONG_PTR)dwServiceBits;
    call.bSetBitsOn = (ULONG_PTR)bSetBitsOn;
    call.bUpdateImmediately = (ULONG_PTR)bUpdateImmediately;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetServiceBits(struct qemu_syscall *call)
{
    struct qemu_SetServiceBits *c = (struct qemu_SetServiceBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetServiceBits(QEMU_G2H(c->hServiceStatus), c->dwServiceBits, c->bSetBitsOn, c->bUpdateImmediately);
}

#endif

struct qemu_RegisterServiceCtrlHandlerA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SERVICE_STATUS_HANDLE WINAPI RegisterServiceCtrlHandlerA(LPCSTR name, LPHANDLER_FUNCTION handler)
{
    struct qemu_RegisterServiceCtrlHandlerA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSERVICECTRLHANDLERA);
    call.name = (ULONG_PTR)name;
    call.handler = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return (SERVICE_STATUS_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterServiceCtrlHandlerA(struct qemu_syscall *call)
{
    struct qemu_RegisterServiceCtrlHandlerA *c = (struct qemu_RegisterServiceCtrlHandlerA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterServiceCtrlHandlerA(QEMU_G2H(c->name), QEMU_G2H(c->handler));
}

#endif

struct qemu_RegisterServiceCtrlHandlerW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SERVICE_STATUS_HANDLE WINAPI RegisterServiceCtrlHandlerW(LPCWSTR name, LPHANDLER_FUNCTION handler)
{
    struct qemu_RegisterServiceCtrlHandlerW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSERVICECTRLHANDLERW);
    call.name = (ULONG_PTR)name;
    call.handler = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return (SERVICE_STATUS_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterServiceCtrlHandlerW(struct qemu_syscall *call)
{
    struct qemu_RegisterServiceCtrlHandlerW *c = (struct qemu_RegisterServiceCtrlHandlerW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterServiceCtrlHandlerW(QEMU_G2H(c->name), QEMU_G2H(c->handler));
}

#endif

struct qemu_RegisterServiceCtrlHandlerExA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t handler;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SERVICE_STATUS_HANDLE WINAPI RegisterServiceCtrlHandlerExA(LPCSTR name, LPHANDLER_FUNCTION_EX handler, LPVOID context)
{
    struct qemu_RegisterServiceCtrlHandlerExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSERVICECTRLHANDLEREXA);
    call.name = (ULONG_PTR)name;
    call.handler = (ULONG_PTR)handler;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return (SERVICE_STATUS_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterServiceCtrlHandlerExA(struct qemu_syscall *call)
{
    struct qemu_RegisterServiceCtrlHandlerExA *c = (struct qemu_RegisterServiceCtrlHandlerExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterServiceCtrlHandlerExA(QEMU_G2H(c->name), QEMU_G2H(c->handler), QEMU_G2H(c->context));
}

#endif

struct qemu_RegisterServiceCtrlHandlerExW
{
    struct qemu_syscall super;
    uint64_t lpServiceName;
    uint64_t lpHandlerProc;
    uint64_t lpContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SERVICE_STATUS_HANDLE WINAPI RegisterServiceCtrlHandlerExW(LPCWSTR lpServiceName, LPHANDLER_FUNCTION_EX lpHandlerProc, LPVOID lpContext)
{
    struct qemu_RegisterServiceCtrlHandlerExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSERVICECTRLHANDLEREXW);
    call.lpServiceName = (ULONG_PTR)lpServiceName;
    call.lpHandlerProc = (ULONG_PTR)lpHandlerProc;
    call.lpContext = (ULONG_PTR)lpContext;

    qemu_syscall(&call.super);

    return (SERVICE_STATUS_HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_RegisterServiceCtrlHandlerExW(struct qemu_syscall *call)
{
    struct qemu_RegisterServiceCtrlHandlerExW *c = (struct qemu_RegisterServiceCtrlHandlerExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)RegisterServiceCtrlHandlerExW(QEMU_G2H(c->lpServiceName), QEMU_G2H(c->lpHandlerProc), QEMU_G2H(c->lpContext));
}

#endif

struct qemu_EnumDependentServicesA
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwServiceState;
    uint64_t lpServices;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
    uint64_t lpServicesReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDependentServicesA(SC_HANDLE hService, DWORD dwServiceState, LPENUM_SERVICE_STATUSA lpServices, DWORD cbBufSize, LPDWORD pcbBytesNeeded, LPDWORD lpServicesReturned)
{
    struct qemu_EnumDependentServicesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDEPENDENTSERVICESA);
    call.hService = (ULONG_PTR)hService;
    call.dwServiceState = (ULONG_PTR)dwServiceState;
    call.lpServices = (ULONG_PTR)lpServices;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;
    call.lpServicesReturned = (ULONG_PTR)lpServicesReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDependentServicesA(struct qemu_syscall *call)
{
    struct qemu_EnumDependentServicesA *c = (struct qemu_EnumDependentServicesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDependentServicesA(QEMU_G2H(c->hService), c->dwServiceState, QEMU_G2H(c->lpServices), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded), QEMU_G2H(c->lpServicesReturned));
}

#endif

struct qemu_EnumDependentServicesW
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwServiceState;
    uint64_t lpServices;
    uint64_t cbBufSize;
    uint64_t pcbBytesNeeded;
    uint64_t lpServicesReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumDependentServicesW(SC_HANDLE hService, DWORD dwServiceState, LPENUM_SERVICE_STATUSW lpServices, DWORD cbBufSize, LPDWORD pcbBytesNeeded, LPDWORD lpServicesReturned)
{
    struct qemu_EnumDependentServicesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDEPENDENTSERVICESW);
    call.hService = (ULONG_PTR)hService;
    call.dwServiceState = (ULONG_PTR)dwServiceState;
    call.lpServices = (ULONG_PTR)lpServices;
    call.cbBufSize = (ULONG_PTR)cbBufSize;
    call.pcbBytesNeeded = (ULONG_PTR)pcbBytesNeeded;
    call.lpServicesReturned = (ULONG_PTR)lpServicesReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDependentServicesW(struct qemu_syscall *call)
{
    struct qemu_EnumDependentServicesW *c = (struct qemu_EnumDependentServicesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDependentServicesW(QEMU_G2H(c->hService), c->dwServiceState, QEMU_G2H(c->lpServices), c->cbBufSize, QEMU_G2H(c->pcbBytesNeeded), QEMU_G2H(c->lpServicesReturned));
}

#endif

struct qemu_NotifyServiceStatusChangeW
{
    struct qemu_syscall super;
    uint64_t hService;
    uint64_t dwNotifyMask;
    uint64_t pNotifyBuffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI NotifyServiceStatusChangeW(SC_HANDLE hService, DWORD dwNotifyMask, SERVICE_NOTIFYW *pNotifyBuffer)
{
    struct qemu_NotifyServiceStatusChangeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYSERVICESTATUSCHANGEW);
    call.hService = (ULONG_PTR)hService;
    call.dwNotifyMask = (ULONG_PTR)dwNotifyMask;
    call.pNotifyBuffer = (ULONG_PTR)pNotifyBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NotifyServiceStatusChangeW(struct qemu_syscall *call)
{
    struct qemu_NotifyServiceStatusChangeW *c = (struct qemu_NotifyServiceStatusChangeW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NotifyServiceStatusChangeW(QEMU_G2H(c->hService), c->dwNotifyMask, QEMU_G2H(c->pNotifyBuffer));
}

#endif

