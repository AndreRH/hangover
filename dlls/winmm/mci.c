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
#include "qemu_winmm.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif


struct qemu_mciSendStringW
{
    struct qemu_syscall super;
    uint64_t lpstrCommand;
    uint64_t lpstrRet;
    uint64_t uRetLen;
    uint64_t hwndCallback;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI mciSendStringW(LPCWSTR lpstrCommand, LPWSTR lpstrRet, UINT uRetLen, HWND hwndCallback)
{
    struct qemu_mciSendStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISENDSTRINGW);
    call.lpstrCommand = (ULONG_PTR)lpstrCommand;
    call.lpstrRet = (ULONG_PTR)lpstrRet;
    call.uRetLen = (ULONG_PTR)uRetLen;
    call.hwndCallback = (ULONG_PTR)hwndCallback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciSendStringW(struct qemu_syscall *call)
{
    struct qemu_mciSendStringW *c = (struct qemu_mciSendStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciSendStringW(QEMU_G2H(c->lpstrCommand), QEMU_G2H(c->lpstrRet), c->uRetLen, QEMU_G2H(c->hwndCallback));
}

#endif

struct qemu_mciSendStringA
{
    struct qemu_syscall super;
    uint64_t lpstrCommand;
    uint64_t lpstrRet;
    uint64_t uRetLen;
    uint64_t hwndCallback;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI mciSendStringA(LPCSTR lpstrCommand, LPSTR lpstrRet, UINT uRetLen, HWND hwndCallback)
{
    struct qemu_mciSendStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISENDSTRINGA);
    call.lpstrCommand = (ULONG_PTR)lpstrCommand;
    call.lpstrRet = (ULONG_PTR)lpstrRet;
    call.uRetLen = (ULONG_PTR)uRetLen;
    call.hwndCallback = (ULONG_PTR)hwndCallback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciSendStringA(struct qemu_syscall *call)
{
    struct qemu_mciSendStringA *c = (struct qemu_mciSendStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciSendStringA(QEMU_G2H(c->lpstrCommand), QEMU_G2H(c->lpstrRet), c->uRetLen, QEMU_G2H(c->hwndCallback));
}

#endif

struct qemu_mciExecute
{
    struct qemu_syscall super;
    uint64_t lpstrCommand;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciExecute(LPCSTR lpstrCommand)
{
    struct qemu_mciExecute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIEXECUTE);
    call.lpstrCommand = (ULONG_PTR)lpstrCommand;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciExecute(struct qemu_syscall *call)
{
    struct qemu_mciExecute *c = (struct qemu_mciExecute *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciExecute(QEMU_G2H(c->lpstrCommand));
}

#endif

struct qemu_mciLoadCommandResource
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t resNameW;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mciLoadCommandResource(HINSTANCE hInst, LPCWSTR resNameW, UINT type)
{
    struct qemu_mciLoadCommandResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCILOADCOMMANDRESOURCE);
    call.hInst = (ULONG_PTR)hInst;
    call.resNameW = (ULONG_PTR)resNameW;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add mciLoadCommandResource to Wine headers? */
extern UINT WINAPI mciLoadCommandResource(HINSTANCE hInst, LPCWSTR resNameW, UINT type);
void qemu_mciLoadCommandResource(struct qemu_syscall *call)
{
    struct qemu_mciLoadCommandResource *c = (struct qemu_mciLoadCommandResource *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciLoadCommandResource(QEMU_G2H(c->hInst), QEMU_G2H(c->resNameW), c->type);
}

#endif

struct qemu_mciFreeCommandResource
{
    struct qemu_syscall super;
    uint64_t uTable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciFreeCommandResource(UINT uTable)
{
    struct qemu_mciFreeCommandResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIFREECOMMANDRESOURCE);
    call.uTable = (ULONG_PTR)uTable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add mciFreeCommandResource to Wine headers? */
extern BOOL WINAPI mciFreeCommandResource(UINT uTable);
void qemu_mciFreeCommandResource(struct qemu_syscall *call)
{
    struct qemu_mciFreeCommandResource *c = (struct qemu_mciFreeCommandResource *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciFreeCommandResource(c->uTable);
}

#endif

struct qemu_mciGetErrorStringW
{
    struct qemu_syscall super;
    uint64_t wError;
    uint64_t lpstrBuffer;
    uint64_t uLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciGetErrorStringW(MCIERROR wError, LPWSTR lpstrBuffer, UINT uLength)
{
    struct qemu_mciGetErrorStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETERRORSTRINGW);
    call.wError = (ULONG_PTR)wError;
    call.lpstrBuffer = (ULONG_PTR)lpstrBuffer;
    call.uLength = (ULONG_PTR)uLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciGetErrorStringW(struct qemu_syscall *call)
{
    struct qemu_mciGetErrorStringW *c = (struct qemu_mciGetErrorStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetErrorStringW(c->wError, QEMU_G2H(c->lpstrBuffer), c->uLength);
}

#endif

struct qemu_mciGetErrorStringA
{
    struct qemu_syscall super;
    uint64_t dwError;
    uint64_t lpstrBuffer;
    uint64_t uLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciGetErrorStringA(MCIERROR dwError, LPSTR lpstrBuffer, UINT uLength)
{
    struct qemu_mciGetErrorStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETERRORSTRINGA);
    call.dwError = (ULONG_PTR)dwError;
    call.lpstrBuffer = (ULONG_PTR)lpstrBuffer;
    call.uLength = (ULONG_PTR)uLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciGetErrorStringA(struct qemu_syscall *call)
{
    struct qemu_mciGetErrorStringA *c = (struct qemu_mciGetErrorStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetErrorStringA(c->dwError, QEMU_G2H(c->lpstrBuffer), c->uLength);
}

#endif

struct qemu_mciDriverNotify
{
    struct qemu_syscall super;
    uint64_t hWndCallBack;
    uint64_t wDevID;
    uint64_t wStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciDriverNotify(HWND hWndCallBack, MCIDEVICEID wDevID, UINT wStatus)
{
    struct qemu_mciDriverNotify call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIDRIVERNOTIFY);
    call.hWndCallBack = (ULONG_PTR)hWndCallBack;
    call.wDevID = (ULONG_PTR)wDevID;
    call.wStatus = (ULONG_PTR)wStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add mciDriverNotify to Wine headers? */
extern BOOL WINAPI mciDriverNotify(HWND hWndCallBack, MCIDEVICEID wDevID, UINT wStatus);
void qemu_mciDriverNotify(struct qemu_syscall *call)
{
    struct qemu_mciDriverNotify *c = (struct qemu_mciDriverNotify *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciDriverNotify(QEMU_G2H(c->hWndCallBack), c->wDevID, c->wStatus);
}

#endif

struct qemu_mciGetDriverData
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD_PTR WINAPI mciGetDriverData(MCIDEVICEID uDeviceID)
{
    struct qemu_mciGetDriverData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETDRIVERDATA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add mciGetDriverData to Wine headers? */
extern DWORD_PTR WINAPI mciGetDriverData(MCIDEVICEID uDeviceID);
void qemu_mciGetDriverData(struct qemu_syscall *call)
{
    struct qemu_mciGetDriverData *c = (struct qemu_mciGetDriverData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetDriverData(c->uDeviceID);
}

#endif

struct qemu_mciSetDriverData
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciSetDriverData(MCIDEVICEID uDeviceID, DWORD_PTR data)
{
    struct qemu_mciSetDriverData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISETDRIVERDATA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.data = (ULONG_PTR)data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add mciSetDriverData to Wine headers? */
extern BOOL WINAPI mciSetDriverData(MCIDEVICEID uDeviceID, DWORD_PTR data);
void qemu_mciSetDriverData(struct qemu_syscall *call)
{
    struct qemu_mciSetDriverData *c = (struct qemu_mciSetDriverData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciSetDriverData(c->uDeviceID, c->data);
}

#endif

struct qemu_mciSendCommandW
{
    struct qemu_syscall super;
    uint64_t wDevID;
    uint64_t wMsg;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI mciSendCommandW(MCIDEVICEID wDevID, UINT wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_mciSendCommandW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISENDCOMMANDW);
    call.wDevID = (ULONG_PTR)wDevID;
    call.wMsg = (ULONG_PTR)wMsg;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciSendCommandW(struct qemu_syscall *call)
{
    struct qemu_mciSendCommandW *c = (struct qemu_mciSendCommandW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciSendCommandW(c->wDevID, c->wMsg, c->dwParam1, c->dwParam2);
}

#endif

struct qemu_mciSendCommandA
{
    struct qemu_syscall super;
    uint64_t wDevID;
    uint64_t wMsg;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI mciSendCommandA(MCIDEVICEID wDevID, UINT wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_mciSendCommandA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISENDCOMMANDA);
    call.wDevID = (ULONG_PTR)wDevID;
    call.wMsg = (ULONG_PTR)wMsg;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciSendCommandA(struct qemu_syscall *call)
{
    struct qemu_mciSendCommandA *c = (struct qemu_mciSendCommandA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciSendCommandA(c->wDevID, c->wMsg, c->dwParam1, c->dwParam2);
}

#endif

struct qemu_mciGetDeviceIDA
{
    struct qemu_syscall super;
    uint64_t lpstrName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mciGetDeviceIDA(LPCSTR lpstrName)
{
    struct qemu_mciGetDeviceIDA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETDEVICEIDA);
    call.lpstrName = (ULONG_PTR)lpstrName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciGetDeviceIDA(struct qemu_syscall *call)
{
    struct qemu_mciGetDeviceIDA *c = (struct qemu_mciGetDeviceIDA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetDeviceIDA(QEMU_G2H(c->lpstrName));
}

#endif

struct qemu_mciGetDeviceIDW
{
    struct qemu_syscall super;
    uint64_t lpwstrName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mciGetDeviceIDW(LPCWSTR lpwstrName)
{
    struct qemu_mciGetDeviceIDW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETDEVICEIDW);
    call.lpwstrName = (ULONG_PTR)lpwstrName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciGetDeviceIDW(struct qemu_syscall *call)
{
    struct qemu_mciGetDeviceIDW *c = (struct qemu_mciGetDeviceIDW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetDeviceIDW(QEMU_G2H(c->lpwstrName));
}

#endif

struct qemu_mciSetYieldProc
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t fpYieldProc;
    uint64_t dwYieldData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mciSetYieldProc(MCIDEVICEID uDeviceID, YIELDPROC fpYieldProc, DWORD dwYieldData)
{
    struct qemu_mciSetYieldProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISETYIELDPROC);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.fpYieldProc = (ULONG_PTR)fpYieldProc;
    call.dwYieldData = (ULONG_PTR)dwYieldData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciSetYieldProc(struct qemu_syscall *call)
{
    struct qemu_mciSetYieldProc *c = (struct qemu_mciSetYieldProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciSetYieldProc(c->uDeviceID, QEMU_G2H(c->fpYieldProc), c->dwYieldData);
}

#endif

struct qemu_mciGetDeviceIDFromElementIDA
{
    struct qemu_syscall super;
    uint64_t dwElementID;
    uint64_t lpstrType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mciGetDeviceIDFromElementIDA(DWORD dwElementID, LPCSTR lpstrType)
{
    struct qemu_mciGetDeviceIDFromElementIDA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETDEVICEIDFROMELEMENTIDA);
    call.dwElementID = (ULONG_PTR)dwElementID;
    call.lpstrType = (ULONG_PTR)lpstrType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciGetDeviceIDFromElementIDA(struct qemu_syscall *call)
{
    struct qemu_mciGetDeviceIDFromElementIDA *c = (struct qemu_mciGetDeviceIDFromElementIDA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetDeviceIDFromElementIDA(c->dwElementID, QEMU_G2H(c->lpstrType));
}

#endif

struct qemu_mciGetDeviceIDFromElementIDW
{
    struct qemu_syscall super;
    uint64_t dwElementID;
    uint64_t lpstrType;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mciGetDeviceIDFromElementIDW(DWORD dwElementID, LPCWSTR lpstrType)
{
    struct qemu_mciGetDeviceIDFromElementIDW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETDEVICEIDFROMELEMENTIDW);
    call.dwElementID = (ULONG_PTR)dwElementID;
    call.lpstrType = (ULONG_PTR)lpstrType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciGetDeviceIDFromElementIDW(struct qemu_syscall *call)
{
    struct qemu_mciGetDeviceIDFromElementIDW *c = (struct qemu_mciGetDeviceIDFromElementIDW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciGetDeviceIDFromElementIDW(c->dwElementID, QEMU_G2H(c->lpstrType));
}

#endif

struct qemu_mciGetYieldProc
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpdwYieldData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI YIELDPROC WINAPI mciGetYieldProc(MCIDEVICEID uDeviceID, DWORD* lpdwYieldData)
{
    struct qemu_mciGetYieldProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETYIELDPROC);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpdwYieldData = (ULONG_PTR)lpdwYieldData;

    qemu_syscall(&call.super);

    return (YIELDPROC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_mciGetYieldProc(struct qemu_syscall *call)
{
    struct qemu_mciGetYieldProc *c = (struct qemu_mciGetYieldProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)mciGetYieldProc(c->uDeviceID, QEMU_G2H(c->lpdwYieldData));
}

#endif

struct qemu_mciGetCreatorTask
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HTASK WINAPI mciGetCreatorTask(MCIDEVICEID uDeviceID)
{
    struct qemu_mciGetCreatorTask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIGETCREATORTASK);
    call.uDeviceID = (ULONG_PTR)uDeviceID;

    qemu_syscall(&call.super);

    return (HTASK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_mciGetCreatorTask(struct qemu_syscall *call)
{
    struct qemu_mciGetCreatorTask *c = (struct qemu_mciGetCreatorTask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)mciGetCreatorTask(c->uDeviceID);
}

#endif

struct qemu_mciDriverYield
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mciDriverYield(MCIDEVICEID uDeviceID)
{
    struct qemu_mciDriverYield call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCIDRIVERYIELD);
    call.uDeviceID = (ULONG_PTR)uDeviceID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add mciDriverYield to Wine headers? */
extern UINT WINAPI mciDriverYield(MCIDEVICEID uDeviceID);
void qemu_mciDriverYield(struct qemu_syscall *call)
{
    struct qemu_mciDriverYield *c = (struct qemu_mciDriverYield *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mciDriverYield(c->uDeviceID);
}

#endif

