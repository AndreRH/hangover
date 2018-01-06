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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_BuildCommDCBA
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t lpdcb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BuildCommDCBA(LPCSTR device, LPDCB lpdcb)
{
    struct qemu_BuildCommDCBA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDCOMMDCBA);
    call.device = (ULONG_PTR)device;
    call.lpdcb = (ULONG_PTR)lpdcb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BuildCommDCBA(struct qemu_syscall *call)
{
    struct qemu_BuildCommDCBA *c = (struct qemu_BuildCommDCBA *)call;
    WINE_TRACE("\n");
    c->super.iret = BuildCommDCBA(QEMU_G2H(c->device), QEMU_G2H(c->lpdcb));
}

#endif

struct qemu_BuildCommDCBAndTimeoutsA
{
    struct qemu_syscall super;
    uint64_t device;
    uint64_t lpdcb;
    uint64_t lptimeouts;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BuildCommDCBAndTimeoutsA(LPCSTR device, LPDCB lpdcb, LPCOMMTIMEOUTS lptimeouts)
{
    struct qemu_BuildCommDCBAndTimeoutsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDCOMMDCBANDTIMEOUTSA);
    call.device = (ULONG_PTR)device;
    call.lpdcb = (ULONG_PTR)lpdcb;
    call.lptimeouts = (ULONG_PTR)lptimeouts;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BuildCommDCBAndTimeoutsA(struct qemu_syscall *call)
{
    struct qemu_BuildCommDCBAndTimeoutsA *c = (struct qemu_BuildCommDCBAndTimeoutsA *)call;
    WINE_TRACE("\n");
    c->super.iret = BuildCommDCBAndTimeoutsA(QEMU_G2H(c->device), QEMU_G2H(c->lpdcb), QEMU_G2H(c->lptimeouts));
}

#endif

struct qemu_BuildCommDCBAndTimeoutsW
{
    struct qemu_syscall super;
    uint64_t devid;
    uint64_t lpdcb;
    uint64_t lptimeouts;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BuildCommDCBAndTimeoutsW(LPCWSTR devid, LPDCB lpdcb, LPCOMMTIMEOUTS lptimeouts)
{
    struct qemu_BuildCommDCBAndTimeoutsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDCOMMDCBANDTIMEOUTSW);
    call.devid = (ULONG_PTR)devid;
    call.lpdcb = (ULONG_PTR)lpdcb;
    call.lptimeouts = (ULONG_PTR)lptimeouts;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BuildCommDCBAndTimeoutsW(struct qemu_syscall *call)
{
    struct qemu_BuildCommDCBAndTimeoutsW *c = (struct qemu_BuildCommDCBAndTimeoutsW *)call;
    WINE_TRACE("\n");
    c->super.iret = BuildCommDCBAndTimeoutsW(QEMU_G2H(c->devid), QEMU_G2H(c->lpdcb), QEMU_G2H(c->lptimeouts));
}

#endif

struct qemu_BuildCommDCBW
{
    struct qemu_syscall super;
    uint64_t devid;
    uint64_t lpdcb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI BuildCommDCBW(LPCWSTR devid, LPDCB lpdcb)
{
    struct qemu_BuildCommDCBW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BUILDCOMMDCBW);
    call.devid = (ULONG_PTR)devid;
    call.lpdcb = (ULONG_PTR)lpdcb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_BuildCommDCBW(struct qemu_syscall *call)
{
    struct qemu_BuildCommDCBW *c = (struct qemu_BuildCommDCBW *)call;
    WINE_TRACE("\n");
    c->super.iret = BuildCommDCBW(QEMU_G2H(c->devid), QEMU_G2H(c->lpdcb));
}

#endif

struct qemu_SetCommBreak
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCommBreak(HANDLE handle)
{
    struct qemu_SetCommBreak call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMMBREAK);
    call.handle = (LONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCommBreak(struct qemu_syscall *call)
{
    struct qemu_SetCommBreak *c = (struct qemu_SetCommBreak *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCommBreak(QEMU_G2H(c->handle));
}

#endif

struct qemu_ClearCommBreak
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClearCommBreak(HANDLE handle)
{
    struct qemu_ClearCommBreak call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEARCOMMBREAK);
    call.handle = (LONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClearCommBreak(struct qemu_syscall *call)
{
    struct qemu_ClearCommBreak *c = (struct qemu_ClearCommBreak *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ClearCommBreak(QEMU_G2H(c->handle));
}

#endif

struct qemu_EscapeCommFunction
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EscapeCommFunction(HANDLE handle, DWORD func)
{
    struct qemu_EscapeCommFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ESCAPECOMMFUNCTION);
    call.handle = (LONG_PTR)handle;
    call.func = func;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EscapeCommFunction(struct qemu_syscall *call)
{
    struct qemu_EscapeCommFunction *c = (struct qemu_EscapeCommFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EscapeCommFunction(QEMU_G2H(c->handle), c->func);
}

#endif

struct qemu_PurgeComm
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PurgeComm(HANDLE handle, DWORD flags)
{
    struct qemu_PurgeComm call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PURGECOMM);
    call.handle = (LONG_PTR)handle;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PurgeComm(struct qemu_syscall *call)
{
    struct qemu_PurgeComm *c = (struct qemu_PurgeComm *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PurgeComm(QEMU_G2H(c->handle), c->flags);
}

#endif

struct qemu_ClearCommError
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t errors;
    uint64_t lpStat;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClearCommError(HANDLE handle, LPDWORD errors, LPCOMSTAT lpStat)
{
    struct qemu_ClearCommError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLEARCOMMERROR);
    call.handle = (LONG_PTR)handle;
    call.errors = (ULONG_PTR)errors;
    call.lpStat = (ULONG_PTR)lpStat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClearCommError(struct qemu_syscall *call)
{
    struct qemu_ClearCommError *c = (struct qemu_ClearCommError *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ClearCommError(QEMU_G2H(c->handle), QEMU_G2H(c->errors), QEMU_G2H(c->lpStat));
}

#endif

struct qemu_SetupComm
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t insize;
    uint64_t outsize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetupComm(HANDLE handle, DWORD insize, DWORD outsize)
{
    struct qemu_SetupComm call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETUPCOMM);
    call.handle = (LONG_PTR)handle;
    call.insize = insize;
    call.outsize = outsize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetupComm(struct qemu_syscall *call)
{
    struct qemu_SetupComm *c = (struct qemu_SetupComm *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetupComm(QEMU_G2H(c->handle), c->insize, c->outsize);
}

#endif

struct qemu_GetCommMask
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t evtmask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCommMask(HANDLE handle, LPDWORD evtmask)
{
    struct qemu_GetCommMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMMMASK);
    call.handle = (LONG_PTR)handle;
    call.evtmask = (ULONG_PTR)evtmask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCommMask(struct qemu_syscall *call)
{
    struct qemu_GetCommMask *c = (struct qemu_GetCommMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCommMask(QEMU_G2H(c->handle), QEMU_G2H(c->evtmask));
}

#endif

struct qemu_SetCommMask
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t evtmask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCommMask(HANDLE handle, DWORD evtmask)
{
    struct qemu_SetCommMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMMMASK);
    call.handle = (LONG_PTR)handle;
    call.evtmask = evtmask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCommMask(struct qemu_syscall *call)
{
    struct qemu_SetCommMask *c = (struct qemu_SetCommMask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCommMask(QEMU_G2H(c->handle), c->evtmask);
}

#endif

struct qemu_SetCommState
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t lpdcb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCommState(HANDLE handle, LPDCB lpdcb)
{
    struct qemu_SetCommState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMMSTATE);
    call.handle = (LONG_PTR)handle;
    call.lpdcb = (ULONG_PTR)lpdcb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCommState(struct qemu_syscall *call)
{
    struct qemu_SetCommState *c = (struct qemu_SetCommState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCommState(QEMU_G2H(c->handle), QEMU_G2H(c->lpdcb));
}

#endif

struct qemu_GetCommState
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t lpdcb;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCommState(HANDLE handle, LPDCB lpdcb)
{
    struct qemu_GetCommState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMMSTATE);
    call.handle = (LONG_PTR)handle;
    call.lpdcb = (ULONG_PTR)lpdcb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCommState(struct qemu_syscall *call)
{
    struct qemu_GetCommState *c = (struct qemu_GetCommState *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCommState(QEMU_G2H(c->handle), QEMU_G2H(c->lpdcb));
}

#endif

struct qemu_TransmitCommChar
{
    struct qemu_syscall super;
    uint64_t hComm;
    uint64_t chTransmit;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI TransmitCommChar(HANDLE hComm, CHAR chTransmit)
{
    struct qemu_TransmitCommChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TRANSMITCOMMCHAR);
    call.hComm = (LONG_PTR)hComm;
    call.chTransmit = chTransmit;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_TransmitCommChar(struct qemu_syscall *call)
{
    struct qemu_TransmitCommChar *c = (struct qemu_TransmitCommChar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = TransmitCommChar(QEMU_G2H(c->hComm), c->chTransmit);
}

#endif

struct qemu_GetCommTimeouts
{
    struct qemu_syscall super;
    uint64_t hComm;
    uint64_t lptimeouts;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCommTimeouts(HANDLE hComm, LPCOMMTIMEOUTS lptimeouts)
{
    struct qemu_GetCommTimeouts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMMTIMEOUTS);
    call.hComm = (LONG_PTR)hComm;
    call.lptimeouts = (ULONG_PTR)lptimeouts;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCommTimeouts(struct qemu_syscall *call)
{
    struct qemu_GetCommTimeouts *c = (struct qemu_GetCommTimeouts *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCommTimeouts(QEMU_G2H(c->hComm), QEMU_G2H(c->lptimeouts));
}

#endif

struct qemu_SetCommTimeouts
{
    struct qemu_syscall super;
    uint64_t hComm;
    uint64_t lptimeouts;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCommTimeouts(HANDLE hComm, LPCOMMTIMEOUTS lptimeouts)
{
    struct qemu_SetCommTimeouts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMMTIMEOUTS);
    call.hComm = (LONG_PTR)hComm;
    call.lptimeouts = (ULONG_PTR)lptimeouts;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCommTimeouts(struct qemu_syscall *call)
{
    struct qemu_SetCommTimeouts *c = (struct qemu_SetCommTimeouts *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCommTimeouts(QEMU_G2H(c->hComm), QEMU_G2H(c->lptimeouts));
}

#endif

struct qemu_GetCommModemStatus
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpModemStat;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCommModemStatus(HANDLE hFile, LPDWORD lpModemStat)
{
    struct qemu_GetCommModemStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMMMODEMSTATUS);
    call.hFile = (LONG_PTR)hFile;
    call.lpModemStat = (ULONG_PTR)lpModemStat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCommModemStatus(struct qemu_syscall *call)
{
    struct qemu_GetCommModemStatus *c = (struct qemu_GetCommModemStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCommModemStatus(QEMU_G2H(c->hFile), QEMU_G2H(c->lpModemStat));
}

#endif

struct qemu_WaitCommEvent
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpdwEvents;
    uint64_t lpOverlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WaitCommEvent(HANDLE hFile, LPDWORD lpdwEvents, LPOVERLAPPED lpOverlapped)
{
    struct qemu_WaitCommEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAITCOMMEVENT);
    call.hFile = (LONG_PTR)hFile;
    call.lpdwEvents = (ULONG_PTR)lpdwEvents;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WaitCommEvent(struct qemu_syscall *call)
{
    struct qemu_WaitCommEvent *c = (struct qemu_WaitCommEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WaitCommEvent(QEMU_G2H(c->hFile), QEMU_G2H(c->lpdwEvents), QEMU_G2H(c->lpOverlapped));
}

#endif

struct qemu_GetCommProperties
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpCommProp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCommProperties(HANDLE hFile, LPCOMMPROP lpCommProp)
{
    struct qemu_GetCommProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMMPROPERTIES);
    call.hFile = (LONG_PTR)hFile;
    call.lpCommProp = (ULONG_PTR)lpCommProp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCommProperties(struct qemu_syscall *call)
{
    struct qemu_GetCommProperties *c = (struct qemu_GetCommProperties *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCommProperties(QEMU_G2H(c->hFile), QEMU_G2H(c->lpCommProp));
}

#endif

struct qemu_CommConfigDialogA
{
    struct qemu_syscall super;
    uint64_t lpszDevice;
    uint64_t hWnd;
    uint64_t lpCommConfig;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CommConfigDialogA(LPCSTR lpszDevice, HWND hWnd, LPCOMMCONFIG lpCommConfig)
{
    struct qemu_CommConfigDialogA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMCONFIGDIALOGA);
    call.lpszDevice = (ULONG_PTR)lpszDevice;
    call.hWnd = (ULONG_PTR)hWnd;
    call.lpCommConfig = (ULONG_PTR)lpCommConfig;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CommConfigDialogA(struct qemu_syscall *call)
{
    struct qemu_CommConfigDialogA *c = (struct qemu_CommConfigDialogA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CommConfigDialogA(QEMU_G2H(c->lpszDevice), QEMU_G2H(c->hWnd), QEMU_G2H(c->lpCommConfig));
}

#endif

struct qemu_CommConfigDialogW
{
    struct qemu_syscall super;
    uint64_t lpszDevice;
    uint64_t hWnd;
    uint64_t lpCommConfig;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CommConfigDialogW(LPCWSTR lpszDevice, HWND hWnd, LPCOMMCONFIG lpCommConfig)
{
    struct qemu_CommConfigDialogW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMMCONFIGDIALOGW);
    call.lpszDevice = (ULONG_PTR)lpszDevice;
    call.hWnd = (ULONG_PTR)hWnd;
    call.lpCommConfig = (ULONG_PTR)lpCommConfig;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CommConfigDialogW(struct qemu_syscall *call)
{
    struct qemu_CommConfigDialogW *c = (struct qemu_CommConfigDialogW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CommConfigDialogW(QEMU_G2H(c->lpszDevice), QEMU_G2H(c->hWnd), QEMU_G2H(c->lpCommConfig));
}

#endif

struct qemu_GetCommConfig
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpCommConfig;
    uint64_t lpdwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCommConfig(HANDLE hFile, LPCOMMCONFIG lpCommConfig, LPDWORD lpdwSize)
{
    struct qemu_GetCommConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCOMMCONFIG);
    call.hFile = (LONG_PTR)hFile;
    call.lpCommConfig = (ULONG_PTR)lpCommConfig;
    call.lpdwSize = (ULONG_PTR)lpdwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCommConfig(struct qemu_syscall *call)
{
    struct qemu_GetCommConfig *c = (struct qemu_GetCommConfig *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCommConfig(QEMU_G2H(c->hFile), QEMU_G2H(c->lpCommConfig), QEMU_G2H(c->lpdwSize));
}

#endif

struct qemu_SetCommConfig
{
    struct qemu_syscall super;
    uint64_t hFile;
    uint64_t lpCommConfig;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetCommConfig(HANDLE hFile, LPCOMMCONFIG lpCommConfig, DWORD dwSize)
{
    struct qemu_SetCommConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETCOMMCONFIG);
    call.hFile = (LONG_PTR)hFile;
    call.lpCommConfig = (ULONG_PTR)lpCommConfig;
    call.dwSize = dwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetCommConfig(struct qemu_syscall *call)
{
    struct qemu_SetCommConfig *c = (struct qemu_SetCommConfig *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetCommConfig(QEMU_G2H(c->hFile), QEMU_G2H(c->lpCommConfig), c->dwSize);
}

#endif

struct qemu_SetDefaultCommConfigW
{
    struct qemu_syscall super;
    uint64_t lpszDevice;
    uint64_t lpCommConfig;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDefaultCommConfigW(LPCWSTR lpszDevice, LPCOMMCONFIG lpCommConfig, DWORD dwSize)
{
    struct qemu_SetDefaultCommConfigW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEFAULTCOMMCONFIGW);
    call.lpszDevice = (ULONG_PTR)lpszDevice;
    call.lpCommConfig = (ULONG_PTR)lpCommConfig;
    call.dwSize = dwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDefaultCommConfigW(struct qemu_syscall *call)
{
    struct qemu_SetDefaultCommConfigW *c = (struct qemu_SetDefaultCommConfigW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDefaultCommConfigW(QEMU_G2H(c->lpszDevice), QEMU_G2H(c->lpCommConfig), c->dwSize);
}

#endif

struct qemu_SetDefaultCommConfigA
{
    struct qemu_syscall super;
    uint64_t lpszDevice;
    uint64_t lpCommConfig;
    uint64_t dwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDefaultCommConfigA(LPCSTR lpszDevice, LPCOMMCONFIG lpCommConfig, DWORD dwSize)
{
    struct qemu_SetDefaultCommConfigA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEFAULTCOMMCONFIGA);
    call.lpszDevice = (ULONG_PTR)lpszDevice;
    call.lpCommConfig = (ULONG_PTR)lpCommConfig;
    call.dwSize = dwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDefaultCommConfigA(struct qemu_syscall *call)
{
    struct qemu_SetDefaultCommConfigA *c = (struct qemu_SetDefaultCommConfigA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDefaultCommConfigA(QEMU_G2H(c->lpszDevice), QEMU_G2H(c->lpCommConfig), c->dwSize);
}

#endif

struct qemu_GetDefaultCommConfigW
{
    struct qemu_syscall super;
    uint64_t lpszName;
    uint64_t lpCC;
    uint64_t lpdwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDefaultCommConfigW(LPCWSTR lpszName, LPCOMMCONFIG lpCC, LPDWORD lpdwSize)
{
    struct qemu_GetDefaultCommConfigW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEFAULTCOMMCONFIGW);
    call.lpszName = (ULONG_PTR)lpszName;
    call.lpCC = (ULONG_PTR)lpCC;
    call.lpdwSize = (ULONG_PTR)lpdwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDefaultCommConfigW(struct qemu_syscall *call)
{
    struct qemu_GetDefaultCommConfigW *c = (struct qemu_GetDefaultCommConfigW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDefaultCommConfigW(QEMU_G2H(c->lpszName), QEMU_G2H(c->lpCC), QEMU_G2H(c->lpdwSize));
}

#endif

struct qemu_GetDefaultCommConfigA
{
    struct qemu_syscall super;
    uint64_t lpszName;
    uint64_t lpCC;
    uint64_t lpdwSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDefaultCommConfigA(LPCSTR lpszName, LPCOMMCONFIG lpCC, LPDWORD lpdwSize)
{
    struct qemu_GetDefaultCommConfigA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEFAULTCOMMCONFIGA);
    call.lpszName = (ULONG_PTR)lpszName;
    call.lpCC = (ULONG_PTR)lpCC;
    call.lpdwSize = (ULONG_PTR)lpdwSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDefaultCommConfigA(struct qemu_syscall *call)
{
    struct qemu_GetDefaultCommConfigA *c = (struct qemu_GetDefaultCommConfigA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDefaultCommConfigA(QEMU_G2H(c->lpszName), QEMU_G2H(c->lpCC), QEMU_G2H(c->lpdwSize));
}

#endif

