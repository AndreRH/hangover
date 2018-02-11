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

#include "thunk/qemu_windows.h"

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
    WINE_TRACE("\n");
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
    WINE_TRACE("\n");
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

struct qemu_mciSendCommand
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
    struct qemu_mciSendCommand call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISENDCOMMANDW);
    call.wDevID = (ULONG_PTR)wDevID;
    call.wMsg = (ULONG_PTR)wMsg;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI DWORD WINAPI mciSendCommandA(MCIDEVICEID wDevID, UINT wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_mciSendCommand call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MCISENDCOMMANDA);
    call.wDevID = (ULONG_PTR)wDevID;
    call.wMsg = (ULONG_PTR)wMsg;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mciSendCommand(struct qemu_syscall *call)
{
    struct qemu_mciSendCommand *c = (struct qemu_mciSendCommand *)call;
    MCIDEVICEID dev;
    UINT msg;
    DWORD_PTR param1, param2;
    MCI_GETDEVCAPS_PARMS getdevcaps_parms;
    MCI_SAVE_PARMSW save_parms;
    MCI_RECORD_PARMS record_parms;
    MCI_STATUS_PARMS status_parms;
    MCI_OPEN_PARMSW open_parms;
    MCI_PLAY_PARMS play_parms;
    MCI_SYSINFO_PARMSW sysinfo_parms;
    MCI_INFO_PARMSW info_parms;
    MCI_SEEK_PARMS seek_parms;
    MCI_GENERIC_PARMS generic_parms;

    struct
    {
        MCI_SET_PARMS base;
        DWORD extras[8];
    } set_parms;

    WINE_TRACE("\n");

    dev = c->wDevID;
    msg = c->wMsg;
    param1 = c->dwParam1;
    param2 = c->dwParam2;

#if HOST_BIT != GUEST_BIT
    if (param2)
    {
        switch (msg)
        {
            case MCI_STOP:
            case MCI_CLOSE:
            case MCI_STEP:
            case MCI_RESUME:
                WINE_TRACE("Translating generic.\n");
                MCI_GENERIC_PARMS_g2h(&generic_parms, (void *)param2);
                param2 = (DWORD_PTR)&generic_parms;
                break;

            case MCI_OPEN_DRIVER:
                WINE_FIXME("Unhandled command MCI_OPEN_DRIVER.\n");
                break;
            case MCI_CLOSE_DRIVER:
                WINE_FIXME("Unhandled command MCI_CLOSE_DRIVER.\n");
                break;
            case MCI_OPEN:
                WINE_TRACE("Translating MCI_OPEN.\n");
                MCI_OPEN_PARMS_g2h(&open_parms, (void *)param2);
                param2 = (DWORD_PTR)&open_parms;
                break;

            case MCI_ESCAPE:
                WINE_FIXME("Unhandled command MCI_ESCAPE.\n");
                break;
            case MCI_PLAY:
                WINE_TRACE("Translating MCI_PLAY.\n");
                MCI_PLAY_PARMS_g2h(&play_parms, (void *)param2);
                param2 = (DWORD_PTR)&play_parms;
                break;

            case MCI_SEEK:
                WINE_TRACE("Translating MCI_SEEK.\n");
                MCI_SEEK_PARMS_g2h(&seek_parms, (void *)param2);
                param2 = (DWORD_PTR)&seek_parms;
                break;

            case MCI_PAUSE:
                WINE_FIXME("Unhandled command MCI_PAUSE.\n");
                break;
            case MCI_INFO:
                WINE_TRACE("MCI_INFO MCI_PLAY.\n");
                MCI_INFO_PARMS_g2h(&info_parms, (void *)param2);
                param2 = (DWORD_PTR)&info_parms;
                break;

            case MCI_GETDEVCAPS:
                WINE_TRACE("Translating MCI_GETDEVCAPS.\n");
                MCI_GETDEVCAPS_PARMS_g2h(&getdevcaps_parms, (void *)param2);
                param2 = (DWORD_PTR)&getdevcaps_parms;
                break;

            case MCI_SPIN:
                WINE_FIXME("Unhandled command MCI_SPIN.\n");
                break;
            case MCI_SET:
                /* The structure is device specific, and I don't see a way to know which
                * struct I have without keeping track of how the device was opened.
                *
                * MCI_SET_PARMS_g2h reads 8 extra DWORDs (MCI_WAVE_SET_PARMS). It's a
                * really ugly hack, let's see how far this gets us. */
                WINE_FIXME("Translating MCI_SET, but I don't know what struct I have.\n");
                MCI_SET_PARMS_g2h(&set_parms.base, (void *)param2);
                param2 = (DWORD_PTR)&set_parms;
                break;

                WINE_FIXME("Unhandled command MCI_STEP.\n");
                break;
            case MCI_RECORD:
                WINE_TRACE("Translating MCI_RECORD.\n");
                MCI_RECORD_PARMS_g2h(&record_parms, (void *)param2);
                param2 = (DWORD_PTR)&record_parms;
                break;

            case MCI_SYSINFO:
                WINE_TRACE("Translating MCI_SYSINFO.\n");
                MCI_SYSINFO_PARMS_g2h(&sysinfo_parms, (void *)param2);
                param2 = (DWORD_PTR)&sysinfo_parms;
                break;

            case MCI_BREAK:
                WINE_FIXME("Unhandled command MCI_BREAK.\n");
                break;
            case MCI_SOUND:
                WINE_FIXME("Unhandled command MCI_SOUND.\n");
                break;
            case MCI_SAVE:
                WINE_TRACE("Translating MCI_SAVE.\n");
                MCI_SAVE_PARMS_g2h(&save_parms, (void *)param2);
                param2 = (DWORD_PTR)&save_parms;
                break;

            case MCI_STATUS:
                WINE_TRACE("Translating MCI_STATUS.\n");
                MCI_STATUS_PARMS_g2h(&status_parms, (void *)param2);
                param2 = (DWORD_PTR)&status_parms;
                break;

            case MCI_CUE:
                WINE_FIXME("Unhandled command MCI_CUE.\n");
                break;
            case MCI_REALIZE:
                WINE_FIXME("Unhandled command MCI_REALIZE.\n");
                break;
            case MCI_WINDOW:
                WINE_FIXME("Unhandled command MCI_WINDOW.\n");
                break;
            case MCI_PUT:
                WINE_FIXME("Unhandled command MCI_PUT.\n");
                break;
            case MCI_WHERE:
                WINE_FIXME("Unhandled command MCI_WHERE.\n");
                break;
            case MCI_FREEZE:
                WINE_FIXME("Unhandled command MCI_FREEZE.\n");
                break;
            case MCI_UNFREEZE:
                WINE_FIXME("Unhandled command MCI_UNFREEZE.\n");
                break;
            case MCI_LOAD:
                WINE_FIXME("Unhandled command MCI_LOAD.\n");
                break;
            case MCI_CUT:
                WINE_FIXME("Unhandled command MCI_CUT.\n");
                break;
            case MCI_COPY:
                WINE_FIXME("Unhandled command MCI_COPY.\n");
                break;
            case MCI_PASTE:
                WINE_FIXME("Unhandled command MCI_PASTE.\n");
                break;
            case MCI_UPDATE:
                WINE_FIXME("Unhandled command MCI_UPDATE.\n");
                break;
            case MCI_DELETE:
                WINE_FIXME("Unhandled command MCI_DELETE.\n");
                break;

            default:
                WINE_FIXME("Unknown mci command 0x%x.\n", msg);
                break;
        }
    }
#endif

    /* What about dwCallback? MSDN says it is a Window handle.*/

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_MCISENDCOMMANDA):
            c->super.iret = mciSendCommandA(dev, msg, param1, param2);
            break;

        case QEMU_SYSCALL_ID(CALL_MCISENDCOMMANDW):
            c->super.iret = mciSendCommandW(dev, msg, param1, param2);
            break;
    }
#if HOST_BIT != GUEST_BIT
    if (param2)
    {
        switch (msg)
        {
            case MCI_GETDEVCAPS:
                WINE_TRACE("Translating MCI_GETDEVCAPS back.\n");
                MCI_GETDEVCAPS_PARMS_h2g((void *)c->dwParam2, &getdevcaps_parms);
                break;

            case MCI_SAVE:
                WINE_TRACE("Translating MCI_SAVE back.\n");
                MCI_SAVE_PARMS_h2g((void *)c->dwParam2, &save_parms);
                break;

            case MCI_RECORD:
                WINE_TRACE("Translating MCI_RECORD back.\n");
                MCI_RECORD_PARMS_h2g((void *)c->dwParam2, &record_parms);
                break;

            case MCI_STATUS:
                WINE_TRACE("Translating MCI_STATUS back.\n");
                MCI_STATUS_PARMS_h2g((void *)c->dwParam2, &status_parms);
                break;

            case MCI_OPEN:
                WINE_TRACE("Translating MCI_OPEN back.\n");
                MCI_OPEN_PARMS_h2g((void *)c->dwParam2, &open_parms);
                break;

            case MCI_SET:
                WINE_TRACE("Translating MCI_SET back.\n");
                MCI_SET_PARMS_h2g((void *)c->dwParam2, &set_parms.base);
                break;

            case MCI_PLAY:
                WINE_TRACE("Translating MCI_PLAY back.\n");
                MCI_PLAY_PARMS_h2g((void *)c->dwParam2, &play_parms);
                break;

            case MCI_SYSINFO:
                WINE_TRACE("Translating MCI_SYSINFO back.\n");
                MCI_SYSINFO_PARMS_h2g((void *)c->dwParam2, &sysinfo_parms);
                break;

            case MCI_INFO:
                WINE_TRACE("Translating MCI_INFO back.\n");
                MCI_INFO_PARMS_h2g((void *)c->dwParam2, &info_parms);
                break;

            case MCI_SEEK:
                WINE_TRACE("Translating MCI_SEEK back.\n");
                MCI_SEEK_PARMS_h2g((void *)c->dwParam2, &seek_parms);
                break;

            case MCI_STOP:
            case MCI_CLOSE:
            case MCI_STEP:
            case MCI_RESUME:
                WINE_TRACE("Translating generic parameter back.\n");
                MCI_GENERIC_PARMS_h2g((void *)c->dwParam2, &generic_parms);
                break;
        }
    }
#endif
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

