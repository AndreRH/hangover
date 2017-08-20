/*
 * Copyright 2017 André Hentschel
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include <wct.h>
#include <appmgmt.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_GetUserNameA
{
    struct qemu_syscall super;
    uint64_t lpszName;
    uint64_t lpSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUserNameA(LPSTR lpszName, LPDWORD lpSize)
{
    struct qemu_GetUserNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERNAMEA);
    call.lpszName = (uint64_t)lpszName;
    call.lpSize = (uint64_t)lpSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserNameA(struct qemu_syscall *call)
{
    struct qemu_GetUserNameA *c = (struct qemu_GetUserNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserNameA(QEMU_G2H(c->lpszName), QEMU_G2H(c->lpSize));
}

#endif

struct qemu_GetUserNameW
{
    struct qemu_syscall super;
    uint64_t lpszName;
    uint64_t lpSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetUserNameW(LPWSTR lpszName, LPDWORD lpSize)
{
    struct qemu_GetUserNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSERNAMEW);
    call.lpszName = (uint64_t)lpszName;
    call.lpSize = (uint64_t)lpSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserNameW(struct qemu_syscall *call)
{
    struct qemu_GetUserNameW *c = (struct qemu_GetUserNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserNameW(QEMU_G2H(c->lpszName), QEMU_G2H(c->lpSize));
}

#endif

struct qemu_GetCurrentHwProfileA
{
    struct qemu_syscall super;
    uint64_t pInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCurrentHwProfileA(LPHW_PROFILE_INFOA pInfo)
{
    struct qemu_GetCurrentHwProfileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTHWPROFILEA);
    call.pInfo = (uint64_t)pInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentHwProfileA(struct qemu_syscall *call)
{
    struct qemu_GetCurrentHwProfileA *c = (struct qemu_GetCurrentHwProfileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentHwProfileA(QEMU_G2H(c->pInfo));
}

#endif

struct qemu_GetCurrentHwProfileW
{
    struct qemu_syscall super;
    uint64_t pInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCurrentHwProfileW(LPHW_PROFILE_INFOW pInfo)
{
    struct qemu_GetCurrentHwProfileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTHWPROFILEW);
    call.pInfo = (uint64_t)pInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentHwProfileW(struct qemu_syscall *call)
{
    struct qemu_GetCurrentHwProfileW *c = (struct qemu_GetCurrentHwProfileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentHwProfileW(QEMU_G2H(c->pInfo));
}

#endif

struct qemu_IsTextUnicode
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsTextUnicode(LPCVOID buf, INT len, LPINT flags)
{
    struct qemu_IsTextUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTEXTUNICODE);
    call.buf = (uint64_t)buf;
    call.len = (uint64_t)len;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsTextUnicode(struct qemu_syscall *call)
{
    struct qemu_IsTextUnicode *c = (struct qemu_IsTextUnicode *)call;
    WINE_TRACE("\n");
    c->super.iret = IsTextUnicode(QEMU_G2H(c->buf), c->len, QEMU_G2H(c->flags));
}

#endif

struct qemu_AbortSystemShutdownA
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AbortSystemShutdownA(LPSTR lpMachineName)
{
    struct qemu_AbortSystemShutdownA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ABORTSYSTEMSHUTDOWNA);
    call.lpMachineName = (uint64_t)lpMachineName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AbortSystemShutdownA(struct qemu_syscall *call)
{
    struct qemu_AbortSystemShutdownA *c = (struct qemu_AbortSystemShutdownA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AbortSystemShutdownA(QEMU_G2H(c->lpMachineName));
}

#endif

struct qemu_AbortSystemShutdownW
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AbortSystemShutdownW(LPWSTR lpMachineName)
{
    struct qemu_AbortSystemShutdownW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ABORTSYSTEMSHUTDOWNW);
    call.lpMachineName = (uint64_t)lpMachineName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AbortSystemShutdownW(struct qemu_syscall *call)
{
    struct qemu_AbortSystemShutdownW *c = (struct qemu_AbortSystemShutdownW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AbortSystemShutdownW(QEMU_G2H(c->lpMachineName));
}

#endif

struct qemu_InitiateSystemShutdownExA
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t lpMessage;
    uint64_t dwTimeout;
    uint64_t bForceAppsClosed;
    uint64_t bRebootAfterShutdown;
    uint64_t dwReason;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitiateSystemShutdownExA(LPSTR lpMachineName, LPSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown, DWORD dwReason)
{
    struct qemu_InitiateSystemShutdownExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIATESYSTEMSHUTDOWNEXA);
    call.lpMachineName = (uint64_t)lpMachineName;
    call.lpMessage = (uint64_t)lpMessage;
    call.dwTimeout = (uint64_t)dwTimeout;
    call.bForceAppsClosed = (uint64_t)bForceAppsClosed;
    call.bRebootAfterShutdown = (uint64_t)bRebootAfterShutdown;
    call.dwReason = (uint64_t)dwReason;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitiateSystemShutdownExA(struct qemu_syscall *call)
{
    struct qemu_InitiateSystemShutdownExA *c = (struct qemu_InitiateSystemShutdownExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitiateSystemShutdownExA(QEMU_G2H(c->lpMachineName), QEMU_G2H(c->lpMessage), c->dwTimeout, c->bForceAppsClosed, c->bRebootAfterShutdown, c->dwReason);
}

#endif

struct qemu_InitiateSystemShutdownExW
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t lpMessage;
    uint64_t dwTimeout;
    uint64_t bForceAppsClosed;
    uint64_t bRebootAfterShutdown;
    uint64_t dwReason;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitiateSystemShutdownExW(LPWSTR lpMachineName, LPWSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown, DWORD dwReason)
{
    struct qemu_InitiateSystemShutdownExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIATESYSTEMSHUTDOWNEXW);
    call.lpMachineName = (uint64_t)lpMachineName;
    call.lpMessage = (uint64_t)lpMessage;
    call.dwTimeout = (uint64_t)dwTimeout;
    call.bForceAppsClosed = (uint64_t)bForceAppsClosed;
    call.bRebootAfterShutdown = (uint64_t)bRebootAfterShutdown;
    call.dwReason = (uint64_t)dwReason;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitiateSystemShutdownExW(struct qemu_syscall *call)
{
    struct qemu_InitiateSystemShutdownExW *c = (struct qemu_InitiateSystemShutdownExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitiateSystemShutdownExW(QEMU_G2H(c->lpMachineName), QEMU_G2H(c->lpMessage), c->dwTimeout, c->bForceAppsClosed, c->bRebootAfterShutdown, c->dwReason);
}

#endif

struct qemu_InitiateSystemShutdownA
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t lpMessage;
    uint64_t dwTimeout;
    uint64_t bForceAppsClosed;
    uint64_t bRebootAfterShutdown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitiateSystemShutdownA(LPSTR lpMachineName, LPSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown)
{
    struct qemu_InitiateSystemShutdownA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIATESYSTEMSHUTDOWNA);
    call.lpMachineName = (uint64_t)lpMachineName;
    call.lpMessage = (uint64_t)lpMessage;
    call.dwTimeout = (uint64_t)dwTimeout;
    call.bForceAppsClosed = (uint64_t)bForceAppsClosed;
    call.bRebootAfterShutdown = (uint64_t)bRebootAfterShutdown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitiateSystemShutdownA(struct qemu_syscall *call)
{
    struct qemu_InitiateSystemShutdownA *c = (struct qemu_InitiateSystemShutdownA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitiateSystemShutdownA(QEMU_G2H(c->lpMachineName), QEMU_G2H(c->lpMessage), c->dwTimeout, c->bForceAppsClosed, c->bRebootAfterShutdown);
}

#endif

struct qemu_InitiateSystemShutdownW
{
    struct qemu_syscall super;
    uint64_t lpMachineName;
    uint64_t lpMessage;
    uint64_t dwTimeout;
    uint64_t bForceAppsClosed;
    uint64_t bRebootAfterShutdown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitiateSystemShutdownW(LPWSTR lpMachineName, LPWSTR lpMessage, DWORD dwTimeout, BOOL bForceAppsClosed, BOOL bRebootAfterShutdown)
{
    struct qemu_InitiateSystemShutdownW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITIATESYSTEMSHUTDOWNW);
    call.lpMachineName = (uint64_t)lpMachineName;
    call.lpMessage = (uint64_t)lpMessage;
    call.dwTimeout = (uint64_t)dwTimeout;
    call.bForceAppsClosed = (uint64_t)bForceAppsClosed;
    call.bRebootAfterShutdown = (uint64_t)bRebootAfterShutdown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitiateSystemShutdownW(struct qemu_syscall *call)
{
    struct qemu_InitiateSystemShutdownW *c = (struct qemu_InitiateSystemShutdownW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitiateSystemShutdownW(QEMU_G2H(c->lpMachineName), QEMU_G2H(c->lpMessage), c->dwTimeout, c->bForceAppsClosed, c->bRebootAfterShutdown);
}

#endif

struct qemu_LogonUserA
{
    struct qemu_syscall super;
    uint64_t lpszUsername;
    uint64_t lpszDomain;
    uint64_t lpszPassword;
    uint64_t dwLogonType;
    uint64_t dwLogonProvider;
    uint64_t phToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LogonUserA(LPCSTR lpszUsername, LPCSTR lpszDomain, LPCSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken)
{
    struct qemu_LogonUserA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOGONUSERA);
    call.lpszUsername = (uint64_t)lpszUsername;
    call.lpszDomain = (uint64_t)lpszDomain;
    call.lpszPassword = (uint64_t)lpszPassword;
    call.dwLogonType = (uint64_t)dwLogonType;
    call.dwLogonProvider = (uint64_t)dwLogonProvider;
    call.phToken = (uint64_t)phToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LogonUserA(struct qemu_syscall *call)
{
    struct qemu_LogonUserA *c = (struct qemu_LogonUserA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LogonUserA(QEMU_G2H(c->lpszUsername), QEMU_G2H(c->lpszDomain), QEMU_G2H(c->lpszPassword), c->dwLogonType, c->dwLogonProvider, QEMU_G2H(c->phToken));
}

#endif

struct qemu_LogonUserW
{
    struct qemu_syscall super;
    uint64_t lpszUsername;
    uint64_t lpszDomain;
    uint64_t lpszPassword;
    uint64_t dwLogonType;
    uint64_t dwLogonProvider;
    uint64_t phToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LogonUserW(LPCWSTR lpszUsername, LPCWSTR lpszDomain, LPCWSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken)
{
    struct qemu_LogonUserW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOGONUSERW);
    call.lpszUsername = (uint64_t)lpszUsername;
    call.lpszDomain = (uint64_t)lpszDomain;
    call.lpszPassword = (uint64_t)lpszPassword;
    call.dwLogonType = (uint64_t)dwLogonType;
    call.dwLogonProvider = (uint64_t)dwLogonProvider;
    call.phToken = (uint64_t)phToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LogonUserW(struct qemu_syscall *call)
{
    struct qemu_LogonUserW *c = (struct qemu_LogonUserW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LogonUserW(QEMU_G2H(c->lpszUsername), QEMU_G2H(c->lpszDomain), QEMU_G2H(c->lpszPassword), c->dwLogonType, c->dwLogonProvider, QEMU_G2H(c->phToken));
}

#endif

struct qemu_CommandLineFromMsiDescriptor
{
    struct qemu_syscall super;
    uint64_t szDescriptor;
    uint64_t szCommandLine;
    uint64_t pcchCommandLine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CommandLineFromMsiDescriptor(WCHAR *szDescriptor, WCHAR *szCommandLine, DWORD *pcchCommandLine)
{
    struct qemu_CommandLineFromMsiDescriptor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMANDLINEFROMMSIDESCRIPTOR);
    call.szDescriptor = (uint64_t)szDescriptor;
    call.szCommandLine = (uint64_t)szCommandLine;
    call.pcchCommandLine = (uint64_t)pcchCommandLine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CommandLineFromMsiDescriptor(struct qemu_syscall *call)
{
    struct qemu_CommandLineFromMsiDescriptor *c = (struct qemu_CommandLineFromMsiDescriptor *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CommandLineFromMsiDescriptor(QEMU_G2H(c->szDescriptor), QEMU_G2H(c->szCommandLine), QEMU_G2H(c->pcchCommandLine));
}

#endif

struct qemu_RegisterWaitChainCOMCallback
{
    struct qemu_syscall super;
    uint64_t call_state_cb;
    uint64_t activation_state_cb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RegisterWaitChainCOMCallback(PCOGETCALLSTATE call_state_cb, PCOGETACTIVATIONSTATE activation_state_cb)
{
    struct qemu_RegisterWaitChainCOMCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERWAITCHAINCOMCALLBACK);
    call.call_state_cb = (uint64_t)call_state_cb;
    call.activation_state_cb = (uint64_t)activation_state_cb;

    qemu_syscall(&call.super);
}

#else

void qemu_RegisterWaitChainCOMCallback(struct qemu_syscall *call)
{
    struct qemu_RegisterWaitChainCOMCallback *c = (struct qemu_RegisterWaitChainCOMCallback *)call;
    WINE_FIXME("Unverified!\n");
    RegisterWaitChainCOMCallback(QEMU_G2H(c->call_state_cb), QEMU_G2H(c->activation_state_cb));
}

#endif

