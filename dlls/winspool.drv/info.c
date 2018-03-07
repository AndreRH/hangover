/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger (for CodeWeavers)
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
#include "qemu_winspool.drv.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winspool);
#endif

struct qemu_DeviceCapabilitiesA
{
    struct qemu_syscall super;
    uint64_t pDevice;
    uint64_t pPort;
    uint64_t cap;
    uint64_t pOutput;
    uint64_t lpdm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DeviceCapabilitiesA(LPCSTR pDevice,LPCSTR pPort, WORD cap, LPSTR pOutput, const DEVMODEA *lpdm)
{
    struct qemu_DeviceCapabilitiesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEVICECAPABILITIESA);
    call.pDevice = (ULONG_PTR)pDevice;
    call.pPort = (ULONG_PTR)pPort;
    call.cap = cap;
    call.pOutput = (ULONG_PTR)pOutput;
    call.lpdm = (ULONG_PTR)lpdm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeviceCapabilitiesA(struct qemu_syscall *call)
{
    struct qemu_DeviceCapabilitiesA *c = (struct qemu_DeviceCapabilitiesA *)call;
    /* Juding by wineps.drv/driver.c, PSDRV_DeviceCapabilities, all data passed in pOutput an array of WORD, char
     * or LONG, so we should be fine. */
    WINE_TRACE("\n");
    c->super.iret = DeviceCapabilitiesA(QEMU_G2H(c->pDevice), QEMU_G2H(c->pPort), c->cap, QEMU_G2H(c->pOutput), QEMU_G2H(c->lpdm));
}

#endif

struct qemu_DeviceCapabilitiesW
{
    struct qemu_syscall super;
    uint64_t pDevice;
    uint64_t pPort;
    uint64_t fwCapability;
    uint64_t pOutput;
    uint64_t pDevMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DeviceCapabilitiesW(LPCWSTR pDevice, LPCWSTR pPort, WORD fwCapability, LPWSTR pOutput, const DEVMODEW *pDevMode)
{
    struct qemu_DeviceCapabilitiesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEVICECAPABILITIESW);
    call.pDevice = (ULONG_PTR)pDevice;
    call.pPort = (ULONG_PTR)pPort;
    call.fwCapability = fwCapability;
    call.pOutput = (ULONG_PTR)pOutput;
    call.pDevMode = (ULONG_PTR)pDevMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeviceCapabilitiesW(struct qemu_syscall *call)
{
    struct qemu_DeviceCapabilitiesW *c = (struct qemu_DeviceCapabilitiesW *)call;
    /* Juding by wineps.drv/driver.c, PSDRV_DeviceCapabilities, all data passed in pOutput an array of WORD, char
     * or LONG, so we should be fine. */
    WINE_TRACE("\n");
    c->super.iret = DeviceCapabilitiesW(QEMU_G2H(c->pDevice), QEMU_G2H(c->pPort), c->fwCapability, QEMU_G2H(c->pOutput), QEMU_G2H(c->pDevMode));
}

#endif

struct qemu_DocumentPropertiesA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hPrinter;
    uint64_t pDeviceName;
    uint64_t pDevModeOutput;
    uint64_t pDevModeInput;
    uint64_t fMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI DocumentPropertiesA(HWND hWnd,HANDLE hPrinter, LPSTR pDeviceName, LPDEVMODEA pDevModeOutput,
        LPDEVMODEA pDevModeInput,DWORD fMode)
{
    struct qemu_DocumentPropertiesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOCUMENTPROPERTIESA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pDeviceName = (ULONG_PTR)pDeviceName;
    call.pDevModeOutput = (ULONG_PTR)pDevModeOutput;
    call.pDevModeInput = (ULONG_PTR)pDevModeInput;
    call.fMode = fMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DocumentPropertiesA(struct qemu_syscall *call)
{
    struct qemu_DocumentPropertiesA *c = (struct qemu_DocumentPropertiesA *)call;
    WINE_TRACE("\n");
    /* DEVMODEA has the same size in 32 and 64 bit. */
    c->super.iret = DocumentPropertiesA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hPrinter), QEMU_G2H(c->pDeviceName),
            QEMU_G2H(c->pDevModeOutput), QEMU_G2H(c->pDevModeInput), c->fMode);
}

#endif

struct qemu_DocumentPropertiesW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hPrinter;
    uint64_t pDeviceName;
    uint64_t pDevModeOutput;
    uint64_t pDevModeInput;
    uint64_t fMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI DocumentPropertiesW(HWND hWnd, HANDLE hPrinter, LPWSTR pDeviceName, LPDEVMODEW pDevModeOutput,
        LPDEVMODEW pDevModeInput, DWORD fMode)
{
    struct qemu_DocumentPropertiesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DOCUMENTPROPERTIESW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pDeviceName = (ULONG_PTR)pDeviceName;
    call.pDevModeOutput = (ULONG_PTR)pDevModeOutput;
    call.pDevModeInput = (ULONG_PTR)pDevModeInput;
    call.fMode = fMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DocumentPropertiesW(struct qemu_syscall *call)
{
    struct qemu_DocumentPropertiesW *c = (struct qemu_DocumentPropertiesW *)call;
    WINE_TRACE("\n");
    /* DEVMODEW has the same size in 32 and 64 bit. */
    c->super.iret = DocumentPropertiesW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hPrinter), QEMU_G2H(c->pDeviceName),
            QEMU_G2H(c->pDevModeOutput), QEMU_G2H(c->pDevModeInput), c->fMode);
}

#endif

struct qemu_IsValidDevmodeA
{
    struct qemu_syscall super;
    uint64_t pDevMode;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI IsValidDevmodeA(PDEVMODEA pDevMode, size_t size)
{
    struct qemu_IsValidDevmodeA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDDEVMODEA);
    call.pDevMode = (ULONG_PTR)pDevMode;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI IsValidDevmodeA(PDEVMODEA pDevMode, size_t size);
void qemu_IsValidDevmodeA(struct qemu_syscall *call)
{
    struct qemu_IsValidDevmodeA *c = (struct qemu_IsValidDevmodeA *)call;
    WINE_TRACE("\n");
    /* DEVMODEA has the same size in 32 and 64 bit. */
    c->super.iret = IsValidDevmodeA(QEMU_G2H(c->pDevMode), c->size);
}

#endif

struct qemu_IsValidDevmodeW
{
    struct qemu_syscall super;
    uint64_t pDevMode;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI IsValidDevmodeW(PDEVMODEW pDevMode, size_t size)
{
    struct qemu_IsValidDevmodeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDDEVMODEW);
    call.pDevMode = (ULONG_PTR)pDevMode;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI IsValidDevmodeW(PDEVMODEW pDevMode, size_t size);
void qemu_IsValidDevmodeW(struct qemu_syscall *call)
{
    struct qemu_IsValidDevmodeW *c = (struct qemu_IsValidDevmodeW *)call;
    WINE_TRACE("\n");
    /* DEVMODEW has the same size in 32 and 64 bit. */
    c->super.iret = IsValidDevmodeW(QEMU_G2H(c->pDevMode), c->size);
}

#endif

struct qemu_OpenPrinter
{
    struct qemu_syscall super;
    uint64_t lpPrinterName;
    uint64_t phPrinter;
    uint64_t pDefault;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI OpenPrinterA(LPSTR lpPrinterName,HANDLE *phPrinter, LPPRINTER_DEFAULTSA pDefault)
{
    struct qemu_OpenPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENPRINTERA);
    call.lpPrinterName = (ULONG_PTR)lpPrinterName;
    call.phPrinter = (ULONG_PTR)phPrinter;
    call.pDefault = (ULONG_PTR)pDefault;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phPrinter = (HANDLE)(ULONG_PTR)call.phPrinter;

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI OpenPrinterW(LPWSTR lpPrinterName,HANDLE *phPrinter, LPPRINTER_DEFAULTSW pDefault)
{
    struct qemu_OpenPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENPRINTERW);
    call.lpPrinterName = (ULONG_PTR)lpPrinterName;
    call.phPrinter = (ULONG_PTR)phPrinter;
    call.pDefault = (ULONG_PTR)pDefault;

    qemu_syscall(&call.super);
    if (call.super.iret)
        *phPrinter = (HANDLE)(ULONG_PTR)call.phPrinter;

    return call.super.iret;
}

#else

void qemu_OpenPrinter(struct qemu_syscall *call)
{
    struct qemu_OpenPrinter *c = (struct qemu_OpenPrinter *)call;
    HANDLE printer;
    PRINTER_DEFAULTSW stack, *def = &stack;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    def = QEMU_G2H(c->pDefault);
#else
    if (!c->pDefault)
        def = NULL;
    else
        PRINTER_DEFAULTS_g2h(def, QEMU_G2H(c->pDefault));
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_OPENPRINTERA))
    {
        c->super.iret = OpenPrinterA(QEMU_G2H(c->lpPrinterName), c->phPrinter ? &printer : NULL,
                (PRINTER_DEFAULTSA *)def);
    }
    else
    {
        c->super.iret = OpenPrinterW(QEMU_G2H(c->lpPrinterName), c->phPrinter ? &printer : NULL, def);
    }

    c->phPrinter = QEMU_H2G(printer);
}

#endif

struct qemu_AddMonitor
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pMonitors;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddMonitorA(LPSTR pName, DWORD Level, LPBYTE pMonitors)
{
    struct qemu_AddMonitor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDMONITORA);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pMonitors = (ULONG_PTR)pMonitors;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI AddMonitorW(LPWSTR pName, DWORD Level, LPBYTE pMonitors)
{
    struct qemu_AddMonitor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDMONITORW);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pMonitors = (ULONG_PTR)pMonitors;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddMonitor(struct qemu_syscall *call)
{
    struct qemu_AddMonitor *c = (struct qemu_AddMonitor *)call;
    MONITOR_INFO_2W stack, *monitor = &stack;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    monitor = QEMU_G2H(c->pMonitors);
#else
    if (!c->pMonitors)
        monitor = NULL;
    else
        MONITOR_INFO_2_g2h(monitor, QEMU_G2H(c->pMonitors));
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_ADDMONITORA))
        c->super.iret = AddMonitorA(QEMU_G2H(c->pName), c->Level, (BYTE *)monitor);
    else
        c->super.iret = AddMonitorW(QEMU_G2H(c->pName), c->Level, (BYTE *)monitor);
}

#endif

struct qemu_DeletePrinterDriverA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pDriverName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinterDriverA (LPSTR pName, LPSTR pEnvironment, LPSTR pDriverName)
{
    struct qemu_DeletePrinterDriverA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERDRIVERA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pDriverName = (ULONG_PTR)pDriverName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterDriverA(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterDriverA *c = (struct qemu_DeletePrinterDriverA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterDriverA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pDriverName));
}

#endif

struct qemu_DeletePrinterDriverW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pDriverName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinterDriverW (LPWSTR pName, LPWSTR pEnvironment, LPWSTR pDriverName)
{
    struct qemu_DeletePrinterDriverW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERDRIVERW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pDriverName = (ULONG_PTR)pDriverName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterDriverW(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterDriverW *c = (struct qemu_DeletePrinterDriverW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterDriverW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pDriverName));
}

#endif

struct qemu_DeleteMonitorA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pMonitorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteMonitorA (LPSTR pName, LPSTR pEnvironment, LPSTR pMonitorName)
{
    struct qemu_DeleteMonitorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEMONITORA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pMonitorName = (ULONG_PTR)pMonitorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteMonitorA(struct qemu_syscall *call)
{
    struct qemu_DeleteMonitorA *c = (struct qemu_DeleteMonitorA *)call;
    WINE_TRACE("\n");
    c->super.iret = DeleteMonitorA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pMonitorName));
}

#endif

struct qemu_DeleteMonitorW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pMonitorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteMonitorW(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pMonitorName)
{
    struct qemu_DeleteMonitorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEMONITORW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pMonitorName = (ULONG_PTR)pMonitorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteMonitorW(struct qemu_syscall *call)
{
    struct qemu_DeleteMonitorW *c = (struct qemu_DeleteMonitorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteMonitorW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pMonitorName));
}

#endif

struct qemu_DeletePortA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t hWnd;
    uint64_t pPortName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePortA (LPSTR pName, HWND hWnd, LPSTR pPortName)
{
    struct qemu_DeletePortA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPORTA);
    call.pName = (ULONG_PTR)pName;
    call.hWnd = (ULONG_PTR)hWnd;
    call.pPortName = (ULONG_PTR)pPortName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePortA(struct qemu_syscall *call)
{
    struct qemu_DeletePortA *c = (struct qemu_DeletePortA *)call;
    WINE_TRACE("\n");
    c->super.iret = DeletePortA(QEMU_G2H(c->pName), QEMU_G2H(c->hWnd), QEMU_G2H(c->pPortName));
}

#endif

struct qemu_DeletePortW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t hWnd;
    uint64_t pPortName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePortW (LPWSTR pName, HWND hWnd, LPWSTR pPortName)
{
    struct qemu_DeletePortW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPORTW);
    call.pName = (ULONG_PTR)pName;
    call.hWnd = (ULONG_PTR)hWnd;
    call.pPortName = (ULONG_PTR)pPortName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePortW(struct qemu_syscall *call)
{
    struct qemu_DeletePortW *c = (struct qemu_DeletePortW *)call;
    WINE_TRACE("\n");
    c->super.iret = DeletePortW(QEMU_G2H(c->pName), QEMU_G2H(c->hWnd), QEMU_G2H(c->pPortName));
}

#endif

struct qemu_WritePrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pBuf;
    uint64_t cbBuf;
    uint64_t pcWritten;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WritePrinter(HANDLE hPrinter, LPVOID pBuf, DWORD cbBuf, LPDWORD pcWritten)
{
    struct qemu_WritePrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WRITEPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pBuf = (ULONG_PTR)pBuf;
    call.cbBuf = cbBuf;
    call.pcWritten = (ULONG_PTR)pcWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WritePrinter(struct qemu_syscall *call)
{
    struct qemu_WritePrinter *c = (struct qemu_WritePrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WritePrinter(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pBuf), c->cbBuf, QEMU_G2H(c->pcWritten));
}

#endif

struct qemu_AddFormA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pForm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddFormA(HANDLE hPrinter, DWORD Level, LPBYTE pForm)
{
    struct qemu_AddFormA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFORMA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddFormA(struct qemu_syscall *call)
{
    struct qemu_AddFormA *c = (struct qemu_AddFormA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddFormA(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pForm));
}

#endif

struct qemu_AddFormW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pForm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddFormW(HANDLE hPrinter, DWORD Level, LPBYTE pForm)
{
    struct qemu_AddFormW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDFORMW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddFormW(struct qemu_syscall *call)
{
    struct qemu_AddFormW *c = (struct qemu_AddFormW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddFormW(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pForm));
}

#endif

struct qemu_AddJobA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pData;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddJobA(HANDLE hPrinter, DWORD Level, LPBYTE pData, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_AddJobA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDJOBA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pData = (ULONG_PTR)pData;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddJobA(struct qemu_syscall *call)
{
    struct qemu_AddJobA *c = (struct qemu_AddJobA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddJobA(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pData), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_AddJobW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pData;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddJobW(HANDLE hPrinter, DWORD Level, LPBYTE pData, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_AddJobW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDJOBW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pData = (ULONG_PTR)pData;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddJobW(struct qemu_syscall *call)
{
    struct qemu_AddJobW *c = (struct qemu_AddJobW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddJobW(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pData), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrintProcessorDirectoryA
{
    struct qemu_syscall super;
    uint64_t server;
    uint64_t env;
    uint64_t level;
    uint64_t Info;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrintProcessorDirectoryA(LPSTR server, LPSTR env, DWORD level, LPBYTE Info,
        DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrintProcessorDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTPROCESSORDIRECTORYA);
    call.server = (ULONG_PTR)server;
    call.env = (ULONG_PTR)env;
    call.level = level;
    call.Info = (ULONG_PTR)Info;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrintProcessorDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetPrintProcessorDirectoryA *c = (struct qemu_GetPrintProcessorDirectoryA *)call;
    WINE_TRACE("\n");
    /* pDriverDirectory is just a char * */
    c->super.iret = GetPrintProcessorDirectoryA(QEMU_G2H(c->server), QEMU_G2H(c->env), c->level,
            QEMU_G2H(c->Info), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrintProcessorDirectoryW
{
    struct qemu_syscall super;
    uint64_t server;
    uint64_t env;
    uint64_t level;
    uint64_t Info;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrintProcessorDirectoryW(LPWSTR server, LPWSTR env, DWORD level, LPBYTE Info,
        DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrintProcessorDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTPROCESSORDIRECTORYW);
    call.server = (ULONG_PTR)server;
    call.env = (ULONG_PTR)env;
    call.level = level;
    call.Info = (ULONG_PTR)Info;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrintProcessorDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetPrintProcessorDirectoryW *c = (struct qemu_GetPrintProcessorDirectoryW *)call;
    WINE_FIXME("Unverified!\n");
    WINE_TRACE("\n");
    /* pDriverDirectory is just a WCHAR * */
    c->super.iret = GetPrintProcessorDirectoryW(QEMU_G2H(c->server), QEMU_G2H(c->env), c->level,
            QEMU_G2H(c->Info), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_AddPrinterW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI AddPrinterW(LPWSTR pName, DWORD Level, LPBYTE pPrinter)
{
    struct qemu_AddPrinterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERW);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pPrinter = (ULONG_PTR)pPrinter;

    qemu_syscall(&call.super);

        return (HANDLE)(ULONG_PTR)call.super.iret;
;
}

#else

void qemu_AddPrinterW(struct qemu_syscall *call)
{
    struct qemu_AddPrinterW *c = (struct qemu_AddPrinterW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)AddPrinterW(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pPrinter));
}

#endif

struct qemu_AddPrinterA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI AddPrinterA(LPSTR pName, DWORD Level, LPBYTE pPrinter)
{
    struct qemu_AddPrinterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERA);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pPrinter = (ULONG_PTR)pPrinter;

    qemu_syscall(&call.super);

        return (HANDLE)(ULONG_PTR)call.super.iret;
;
}

#else

void qemu_AddPrinterA(struct qemu_syscall *call)
{
    struct qemu_AddPrinterA *c = (struct qemu_AddPrinterA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)AddPrinterA(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pPrinter));
}

#endif

struct qemu_ClosePrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ClosePrinter(HANDLE hPrinter)
{
    struct qemu_ClosePrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ClosePrinter(struct qemu_syscall *call)
{
    struct qemu_ClosePrinter *c = (struct qemu_ClosePrinter *)call;
    WINE_TRACE("\n");
    c->super.iret = ClosePrinter(QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_DeleteFormA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pFormName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteFormA(HANDLE hPrinter, LPSTR pFormName)
{
    struct qemu_DeleteFormA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEFORMA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pFormName = (ULONG_PTR)pFormName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteFormA(struct qemu_syscall *call)
{
    struct qemu_DeleteFormA *c = (struct qemu_DeleteFormA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteFormA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pFormName));
}

#endif

struct qemu_DeleteFormW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pFormName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeleteFormW(HANDLE hPrinter, LPWSTR pFormName)
{
    struct qemu_DeleteFormW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEFORMW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pFormName = (ULONG_PTR)pFormName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteFormW(struct qemu_syscall *call)
{
    struct qemu_DeleteFormW *c = (struct qemu_DeleteFormW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteFormW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pFormName));
}

#endif

struct qemu_DeletePrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinter(HANDLE hPrinter)
{
    struct qemu_DeletePrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinter(struct qemu_syscall *call)
{
    struct qemu_DeletePrinter *c = (struct qemu_DeletePrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinter(QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_SetPrinterA
{
    struct qemu_syscall super;
    uint64_t printer;
    uint64_t level;
    uint64_t data;
    uint64_t command;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetPrinterA(HANDLE printer, DWORD level, LPBYTE data, DWORD command)
{
    struct qemu_SetPrinterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRINTERA);
    call.printer = (ULONG_PTR)printer;
    call.level = level;
    call.data = (ULONG_PTR)data;
    call.command = command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrinterA(struct qemu_syscall *call)
{
    struct qemu_SetPrinterA *c = (struct qemu_SetPrinterA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrinterA(QEMU_G2H(c->printer), c->level, QEMU_G2H(c->data), c->command);
}

#endif

struct qemu_SetPrinterW
{
    struct qemu_syscall super;
    uint64_t printer;
    uint64_t level;
    uint64_t data;
    uint64_t command;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetPrinterW(HANDLE printer, DWORD level, LPBYTE data, DWORD command)
{
    struct qemu_SetPrinterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRINTERW);
    call.printer = (ULONG_PTR)printer;
    call.level = level;
    call.data = (ULONG_PTR)data;
    call.command = command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrinterW(struct qemu_syscall *call)
{
    struct qemu_SetPrinterW *c = (struct qemu_SetPrinterW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrinterW(QEMU_G2H(c->printer), c->level, QEMU_G2H(c->data), c->command);
}

#endif

struct qemu_SetJobA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t JobId;
    uint64_t Level;
    uint64_t pJob;
    uint64_t Command;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetJobA(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD Command)
{
    struct qemu_SetJobA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETJOBA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.JobId = JobId;
    call.Level = Level;
    call.pJob = (ULONG_PTR)pJob;
    call.Command = Command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetJobA(struct qemu_syscall *call)
{
    struct qemu_SetJobA *c = (struct qemu_SetJobA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetJobA(QEMU_G2H(c->hPrinter), c->JobId, c->Level, QEMU_G2H(c->pJob), c->Command);
}

#endif

struct qemu_SetJobW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t JobId;
    uint64_t Level;
    uint64_t pJob;
    uint64_t Command;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetJobW(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD Command)
{
    struct qemu_SetJobW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETJOBW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.JobId = JobId;
    call.Level = Level;
    call.pJob = (ULONG_PTR)pJob;
    call.Command = Command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetJobW(struct qemu_syscall *call)
{
    struct qemu_SetJobW *c = (struct qemu_SetJobW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetJobW(QEMU_G2H(c->hPrinter), c->JobId, c->Level, QEMU_G2H(c->pJob), c->Command);
}

#endif

struct qemu_EndDocPrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EndDocPrinter(HANDLE hPrinter)
{
    struct qemu_EndDocPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDDOCPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndDocPrinter(struct qemu_syscall *call)
{
    struct qemu_EndDocPrinter *c = (struct qemu_EndDocPrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndDocPrinter(QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_EndPagePrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EndPagePrinter(HANDLE hPrinter)
{
    struct qemu_EndPagePrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDPAGEPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndPagePrinter(struct qemu_syscall *call)
{
    struct qemu_EndPagePrinter *c = (struct qemu_EndPagePrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndPagePrinter(QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_StartDocPrinterA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pDocInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI StartDocPrinterA(HANDLE hPrinter, DWORD Level, LPBYTE pDocInfo)
{
    struct qemu_StartDocPrinterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTDOCPRINTERA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pDocInfo = (ULONG_PTR)pDocInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartDocPrinterA(struct qemu_syscall *call)
{
    struct qemu_StartDocPrinterA *c = (struct qemu_StartDocPrinterA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartDocPrinterA(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pDocInfo));
}

#endif

struct qemu_StartDocPrinterW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pDocInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI StartDocPrinterW(HANDLE hPrinter, DWORD Level, LPBYTE pDocInfo)
{
    struct qemu_StartDocPrinterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTDOCPRINTERW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pDocInfo = (ULONG_PTR)pDocInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartDocPrinterW(struct qemu_syscall *call)
{
    struct qemu_StartDocPrinterW *c = (struct qemu_StartDocPrinterW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartDocPrinterW(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pDocInfo));
}

#endif

struct qemu_StartPagePrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StartPagePrinter(HANDLE hPrinter)
{
    struct qemu_StartPagePrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTPAGEPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartPagePrinter(struct qemu_syscall *call)
{
    struct qemu_StartPagePrinter *c = (struct qemu_StartPagePrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartPagePrinter(QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_GetFormA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pFormName;
    uint64_t Level;
    uint64_t pForm;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFormA(HANDLE hPrinter, LPSTR pFormName, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetFormA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFORMA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pFormName = (ULONG_PTR)pFormName;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFormA(struct qemu_syscall *call)
{
    struct qemu_GetFormA *c = (struct qemu_GetFormA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFormA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pFormName), c->Level, QEMU_G2H(c->pForm), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetFormW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pFormName;
    uint64_t Level;
    uint64_t pForm;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetFormW(HANDLE hPrinter, LPWSTR pFormName, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetFormW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFORMW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pFormName = (ULONG_PTR)pFormName;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFormW(struct qemu_syscall *call)
{
    struct qemu_GetFormW *c = (struct qemu_GetFormW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetFormW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pFormName), c->Level, QEMU_G2H(c->pForm), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_SetFormA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pFormName;
    uint64_t Level;
    uint64_t pForm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFormA(HANDLE hPrinter, LPSTR pFormName, DWORD Level, LPBYTE pForm)
{
    struct qemu_SetFormA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFORMA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pFormName = (ULONG_PTR)pFormName;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFormA(struct qemu_syscall *call)
{
    struct qemu_SetFormA *c = (struct qemu_SetFormA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetFormA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pFormName), c->Level, QEMU_G2H(c->pForm));
}

#endif

struct qemu_SetFormW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pFormName;
    uint64_t Level;
    uint64_t pForm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetFormW(HANDLE hPrinter, LPWSTR pFormName, DWORD Level, LPBYTE pForm)
{
    struct qemu_SetFormW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFORMW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pFormName = (ULONG_PTR)pFormName;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetFormW(struct qemu_syscall *call)
{
    struct qemu_SetFormW *c = (struct qemu_SetFormW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetFormW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pFormName), c->Level, QEMU_G2H(c->pForm));
}

#endif

struct qemu_ReadPrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pBuf;
    uint64_t cbBuf;
    uint64_t pNoBytesRead;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ReadPrinter(HANDLE hPrinter, LPVOID pBuf, DWORD cbBuf, LPDWORD pNoBytesRead)
{
    struct qemu_ReadPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_READPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pBuf = (ULONG_PTR)pBuf;
    call.cbBuf = cbBuf;
    call.pNoBytesRead = (ULONG_PTR)pNoBytesRead;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ReadPrinter(struct qemu_syscall *call)
{
    struct qemu_ReadPrinter *c = (struct qemu_ReadPrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ReadPrinter(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pBuf), c->cbBuf, QEMU_G2H(c->pNoBytesRead));
}

#endif

struct qemu_ResetPrinterA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pDefault;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ResetPrinterA(HANDLE hPrinter, LPPRINTER_DEFAULTSA pDefault)
{
    struct qemu_ResetPrinterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESETPRINTERA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pDefault = (ULONG_PTR)pDefault;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResetPrinterA(struct qemu_syscall *call)
{
    struct qemu_ResetPrinterA *c = (struct qemu_ResetPrinterA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ResetPrinterA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pDefault));
}

#endif

struct qemu_ResetPrinterW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pDefault;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ResetPrinterW(HANDLE hPrinter, LPPRINTER_DEFAULTSW pDefault)
{
    struct qemu_ResetPrinterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RESETPRINTERW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pDefault = (ULONG_PTR)pDefault;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ResetPrinterW(struct qemu_syscall *call)
{
    struct qemu_ResetPrinterW *c = (struct qemu_ResetPrinterW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ResetPrinterW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pDefault));
}

#endif

struct qemu_GetPrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pPrinter;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrinterW(HANDLE hPrinter, DWORD Level, LPBYTE pPrinter, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pPrinter = (ULONG_PTR)pPrinter;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.size = sizeof(PRINTER_INFO_9W);

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI GetPrinterA(HANDLE hPrinter, DWORD Level, LPBYTE pPrinter, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pPrinter = (ULONG_PTR)pPrinter;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinter(struct qemu_syscall *call)
{
    struct qemu_GetPrinter *c = (struct qemu_GetPrinter *)call;
    WINE_TRACE("\n");

    /* The pPrinter buffer is a struct header + strings that the struct header points to. The application has to deal
     * with different sizes due to the strings. This code here hopes that they don't notice the size difference of
     * the 32 vs 64 bit struct headers and the gap between the 32 bit struct header and first string. */
    c->super.iret = GetPrinterW(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pPrinter), c->cbBuf, QEMU_G2H(c->pcbNeeded));
#if HOST_BIT == GUEST_BIT
    return;
#endif

    if (!c->super.iret || !QEMU_G2H(c->pPrinter))
        return;

    switch (c->Level)
    {
        case 1:
            PRINTER_INFO_1_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 2:
            PRINTER_INFO_2_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 3:
            WINE_FIXME("check SECURITY_DESCRIPTOR size.\n");
            PRINTER_INFO_3_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 4:
            PRINTER_INFO_4_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 5:
            PRINTER_INFO_5_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 6:
            /* Just a DWORD, nothing to do. */
            break;

        case 7:
            PRINTER_INFO_7_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 8:
            PRINTER_INFO_8_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        case 9:
            PRINTER_INFO_8_h2g(QEMU_G2H(c->pPrinter), QEMU_G2H(c->pPrinter));
            break;

        default:
            WINE_FIXME("Unexpected info level %u.\n", (DWORD)c->Level);
    }
}

#endif

struct qemu_EnumPrintersW
{
    struct qemu_syscall super;
    uint64_t dwType;
    uint64_t lpszName;
    uint64_t dwLevel;
    uint64_t lpbPrinters;
    uint64_t cbBuf;
    uint64_t lpdwNeeded;
    uint64_t lpdwReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrintersW(DWORD dwType, LPWSTR lpszName, DWORD dwLevel, LPBYTE lpbPrinters, DWORD cbBuf, LPDWORD lpdwNeeded, LPDWORD lpdwReturned)
{
    struct qemu_EnumPrintersW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERSW);
    call.dwType = dwType;
    call.lpszName = (ULONG_PTR)lpszName;
    call.dwLevel = dwLevel;
    call.lpbPrinters = (ULONG_PTR)lpbPrinters;
    call.cbBuf = cbBuf;
    call.lpdwNeeded = (ULONG_PTR)lpdwNeeded;
    call.lpdwReturned = (ULONG_PTR)lpdwReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrintersW(struct qemu_syscall *call)
{
    struct qemu_EnumPrintersW *c = (struct qemu_EnumPrintersW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrintersW(c->dwType, QEMU_G2H(c->lpszName), c->dwLevel, QEMU_G2H(c->lpbPrinters), c->cbBuf, QEMU_G2H(c->lpdwNeeded), QEMU_G2H(c->lpdwReturned));
}

#endif

struct qemu_EnumPrintersA
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t pName;
    uint64_t level;
    uint64_t pPrinters;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrintersA(DWORD flags, LPSTR pName, DWORD level, LPBYTE pPrinters, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrintersA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERSA);
    call.flags = flags;
    call.pName = (ULONG_PTR)pName;
    call.level = level;
    call.pPrinters = (ULONG_PTR)pPrinters;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrintersA(struct qemu_syscall *call)
{
    struct qemu_EnumPrintersA *c = (struct qemu_EnumPrintersA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrintersA(c->flags, QEMU_G2H(c->pName), c->level, QEMU_G2H(c->pPrinters), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_GetPrinterDriverW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pDriverInfo;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrinterDriverW(HANDLE hPrinter, LPWSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDriverW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDRIVERW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDriverW(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDriverW *c = (struct qemu_GetPrinterDriverW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrinterDriverW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pEnvironment), c->Level, QEMU_G2H(c->pDriverInfo), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrinterDriverA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pDriverInfo;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrinterDriverA(HANDLE hPrinter, LPSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDriverA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDRIVERA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDriverA(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDriverA *c = (struct qemu_GetPrinterDriverA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrinterDriverA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pEnvironment), c->Level, QEMU_G2H(c->pDriverInfo), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrinterDriverDirectoryW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pDriverDirectory;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrinterDriverDirectoryW(LPWSTR pName, LPWSTR pEnvironment, DWORD Level,
        LPBYTE pDriverDirectory, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDriverDirectoryW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDRIVERDIRECTORYW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pDriverDirectory = (ULONG_PTR)pDriverDirectory;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDriverDirectoryW(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDriverDirectoryW *c = (struct qemu_GetPrinterDriverDirectoryW *)call;
    WINE_TRACE("\n");
    /* pDriverDirectory is just a WCHAR * */
    c->super.iret = GetPrinterDriverDirectoryW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), c->Level,
            QEMU_G2H(c->pDriverDirectory), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrinterDriverDirectoryA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pDriverDirectory;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetPrinterDriverDirectoryA(LPSTR pName, LPSTR pEnvironment, DWORD Level,
        LPBYTE pDriverDirectory, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDriverDirectoryA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDRIVERDIRECTORYA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pDriverDirectory = (ULONG_PTR)pDriverDirectory;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDriverDirectoryA(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDriverDirectoryA *c = (struct qemu_GetPrinterDriverDirectoryA *)call;
    WINE_TRACE("\n");
    /* pDriverDirectory is just a char * */
    c->super.iret = GetPrinterDriverDirectoryA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), c->Level,
            QEMU_G2H(c->pDriverDirectory), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_AddPrinterDriverA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t level;
    uint64_t pDriverInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrinterDriverA(LPSTR pName, DWORD level, LPBYTE pDriverInfo)
{
    struct qemu_AddPrinterDriverA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERDRIVERA);
    call.pName = (ULONG_PTR)pName;
    call.level = level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrinterDriverA(struct qemu_syscall *call)
{
    struct qemu_AddPrinterDriverA *c = (struct qemu_AddPrinterDriverA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrinterDriverA(QEMU_G2H(c->pName), c->level, QEMU_G2H(c->pDriverInfo));
}

#endif

struct qemu_AddPrinterDriverW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t level;
    uint64_t pDriverInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrinterDriverW(LPWSTR pName, DWORD level, LPBYTE pDriverInfo)
{
    struct qemu_AddPrinterDriverW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERDRIVERW);
    call.pName = (ULONG_PTR)pName;
    call.level = level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrinterDriverW(struct qemu_syscall *call)
{
    struct qemu_AddPrinterDriverW *c = (struct qemu_AddPrinterDriverW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrinterDriverW(QEMU_G2H(c->pName), c->level, QEMU_G2H(c->pDriverInfo));
}

#endif

struct qemu_AddPrintProcessorA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pPathName;
    uint64_t pPrintProcessorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrintProcessorA(LPSTR pName, LPSTR pEnvironment, LPSTR pPathName, LPSTR pPrintProcessorName)
{
    struct qemu_AddPrintProcessorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTPROCESSORA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pPathName = (ULONG_PTR)pPathName;
    call.pPrintProcessorName = (ULONG_PTR)pPrintProcessorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrintProcessorA(struct qemu_syscall *call)
{
    struct qemu_AddPrintProcessorA *c = (struct qemu_AddPrintProcessorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrintProcessorA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pPathName), QEMU_G2H(c->pPrintProcessorName));
}

#endif

struct qemu_AddPrintProcessorW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pPathName;
    uint64_t pPrintProcessorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrintProcessorW(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pPathName, LPWSTR pPrintProcessorName)
{
    struct qemu_AddPrintProcessorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTPROCESSORW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pPathName = (ULONG_PTR)pPathName;
    call.pPrintProcessorName = (ULONG_PTR)pPrintProcessorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrintProcessorW(struct qemu_syscall *call)
{
    struct qemu_AddPrintProcessorW *c = (struct qemu_AddPrintProcessorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrintProcessorW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pPathName), QEMU_G2H(c->pPrintProcessorName));
}

#endif

struct qemu_AddPrintProvidorA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pProviderInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrintProvidorA(LPSTR pName, DWORD Level, LPBYTE pProviderInfo)
{
    struct qemu_AddPrintProvidorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTPROVIDORA);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pProviderInfo = (ULONG_PTR)pProviderInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrintProvidorA(struct qemu_syscall *call)
{
    struct qemu_AddPrintProvidorA *c = (struct qemu_AddPrintProvidorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrintProvidorA(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pProviderInfo));
}

#endif

struct qemu_AddPrintProvidorW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pProviderInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrintProvidorW(LPWSTR pName, DWORD Level, LPBYTE pProviderInfo)
{
    struct qemu_AddPrintProvidorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTPROVIDORW);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pProviderInfo = (ULONG_PTR)pProviderInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrintProvidorW(struct qemu_syscall *call)
{
    struct qemu_AddPrintProvidorW *c = (struct qemu_AddPrintProvidorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrintProvidorW(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pProviderInfo));
}

#endif

struct qemu_AdvancedDocumentPropertiesA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hPrinter;
    uint64_t pDeviceName;
    uint64_t pDevModeOutput;
    uint64_t pDevModeInput;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI AdvancedDocumentPropertiesA(HWND hWnd, HANDLE hPrinter, LPSTR pDeviceName, PDEVMODEA pDevModeOutput, PDEVMODEA pDevModeInput)
{
    struct qemu_AdvancedDocumentPropertiesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADVANCEDDOCUMENTPROPERTIESA);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pDeviceName = (ULONG_PTR)pDeviceName;
    call.pDevModeOutput = (ULONG_PTR)pDevModeOutput;
    call.pDevModeInput = (ULONG_PTR)pDevModeInput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdvancedDocumentPropertiesA(struct qemu_syscall *call)
{
    struct qemu_AdvancedDocumentPropertiesA *c = (struct qemu_AdvancedDocumentPropertiesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AdvancedDocumentPropertiesA(QEMU_G2H(c->hWnd), QEMU_G2H(c->hPrinter), QEMU_G2H(c->pDeviceName), QEMU_G2H(c->pDevModeOutput), QEMU_G2H(c->pDevModeInput));
}

#endif

struct qemu_AdvancedDocumentPropertiesW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hPrinter;
    uint64_t pDeviceName;
    uint64_t pDevModeOutput;
    uint64_t pDevModeInput;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI AdvancedDocumentPropertiesW(HWND hWnd, HANDLE hPrinter, LPWSTR pDeviceName, PDEVMODEW pDevModeOutput, PDEVMODEW pDevModeInput)
{
    struct qemu_AdvancedDocumentPropertiesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADVANCEDDOCUMENTPROPERTIESW);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pDeviceName = (ULONG_PTR)pDeviceName;
    call.pDevModeOutput = (ULONG_PTR)pDevModeOutput;
    call.pDevModeInput = (ULONG_PTR)pDevModeInput;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AdvancedDocumentPropertiesW(struct qemu_syscall *call)
{
    struct qemu_AdvancedDocumentPropertiesW *c = (struct qemu_AdvancedDocumentPropertiesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AdvancedDocumentPropertiesW(QEMU_G2H(c->hWnd), QEMU_G2H(c->hPrinter), QEMU_G2H(c->pDeviceName), QEMU_G2H(c->pDevModeOutput), QEMU_G2H(c->pDevModeInput));
}

#endif

struct qemu_PrinterProperties
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PrinterProperties(HWND hWnd, HANDLE hPrinter)
{
    struct qemu_PrinterProperties call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRINTERPROPERTIES);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrinterProperties(struct qemu_syscall *call)
{
    struct qemu_PrinterProperties *c = (struct qemu_PrinterProperties *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrinterProperties(QEMU_G2H(c->hWnd), QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_EnumJobsA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t FirstJob;
    uint64_t NoJobs;
    uint64_t Level;
    uint64_t pJob;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumJobsA(HANDLE hPrinter, DWORD FirstJob, DWORD NoJobs, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumJobsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMJOBSA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.FirstJob = FirstJob;
    call.NoJobs = NoJobs;
    call.Level = Level;
    call.pJob = (ULONG_PTR)pJob;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumJobsA(struct qemu_syscall *call)
{
    struct qemu_EnumJobsA *c = (struct qemu_EnumJobsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumJobsA(QEMU_G2H(c->hPrinter), c->FirstJob, c->NoJobs, c->Level, QEMU_G2H(c->pJob), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumJobsW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t FirstJob;
    uint64_t NoJobs;
    uint64_t Level;
    uint64_t pJob;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumJobsW(HANDLE hPrinter, DWORD FirstJob, DWORD NoJobs, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumJobsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMJOBSW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.FirstJob = FirstJob;
    call.NoJobs = NoJobs;
    call.Level = Level;
    call.pJob = (ULONG_PTR)pJob;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumJobsW(struct qemu_syscall *call)
{
    struct qemu_EnumJobsW *c = (struct qemu_EnumJobsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumJobsW(QEMU_G2H(c->hPrinter), c->FirstJob, c->NoJobs, c->Level, QEMU_G2H(c->pJob), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumPrinterDrivers
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pDriverInfo;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrinterDriversW(LPWSTR pName, LPWSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo,
        DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrinterDrivers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERDRIVERSW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI EnumPrinterDriversA(LPSTR pName, LPSTR pEnvironment, DWORD Level, LPBYTE pDriverInfo,
        DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrinterDrivers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERDRIVERSA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterDrivers(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterDrivers *c = (struct qemu_EnumPrinterDrivers *)call;
    DWORD returned, i, level;
    BYTE *conv_in, *conv_out;
    WINE_TRACE("\n");

    level = c->Level;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_ENUMPRINTERDRIVERSA))
    {
        c->super.iret = EnumPrinterDriversA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), level,
                QEMU_G2H(c->pDriverInfo), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
    }
    else
    {
        c->super.iret = EnumPrinterDriversW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), level,
                QEMU_G2H(c->pDriverInfo), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
    }

#if GUEST_BIT == HOST_BIT
    return;
#endif
    if (!c->super.iret)
        return;

    returned = *(DWORD *)QEMU_G2H(c->pcReturned);
    conv_in = conv_out = QEMU_G2H(c->pDriverInfo);
    WINE_TRACE("returned %u lvl %u\n", returned, level);
    for (i = 0; i < returned; ++i)
    {
        switch (level)
        {
            case 1:
                DRIVER_INFO_1_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_1W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_1);
                break;
            case 2:
                DRIVER_INFO_2_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_2W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_2);
                break;
            case 3:
                DRIVER_INFO_3_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_3W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_3);
                break;
            case 4:
                DRIVER_INFO_4_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_4W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_4);
                break;
            case 5:
                DRIVER_INFO_5_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_5W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_5);
                break;
            case 6:
                DRIVER_INFO_6_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_6W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_6);
                break;
            case 8:
                DRIVER_INFO_8_h2g((void *)conv_out, (void *)conv_in);
                conv_in += sizeof(DRIVER_INFO_8W);
                conv_out += sizeof(struct qemu_DRIVER_INFO_8);
                break;
            default:
                WINE_ERR("Unexpected driver level %u.\n", level);
                break;
        }
    }
}

#endif

struct qemu_EnumPortsA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pPorts;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPortsA(LPSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPortsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPORTSA);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pPorts = (ULONG_PTR)pPorts;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPortsA(struct qemu_syscall *call)
{
    struct qemu_EnumPortsA *c = (struct qemu_EnumPortsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPortsA(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pPorts), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumPortsW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pPorts;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPortsW(LPWSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPortsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPORTSW);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pPorts = (ULONG_PTR)pPorts;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPortsW(struct qemu_syscall *call)
{
    struct qemu_EnumPortsW *c = (struct qemu_EnumPortsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPortsW(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pPorts), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_GetDefaultPrinterW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t namesize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDefaultPrinterW(LPWSTR name, LPDWORD namesize)
{
    struct qemu_GetDefaultPrinterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEFAULTPRINTERW);
    call.name = (ULONG_PTR)name;
    call.namesize = (ULONG_PTR)namesize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDefaultPrinterW(struct qemu_syscall *call)
{
    struct qemu_GetDefaultPrinterW *c = (struct qemu_GetDefaultPrinterW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDefaultPrinterW(QEMU_G2H(c->name), QEMU_G2H(c->namesize));
}

#endif

struct qemu_GetDefaultPrinterA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t namesize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDefaultPrinterA(LPSTR name, LPDWORD namesize)
{
    struct qemu_GetDefaultPrinterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEFAULTPRINTERA);
    call.name = (ULONG_PTR)name;
    call.namesize = (ULONG_PTR)namesize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDefaultPrinterA(struct qemu_syscall *call)
{
    struct qemu_GetDefaultPrinterA *c = (struct qemu_GetDefaultPrinterA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDefaultPrinterA(QEMU_G2H(c->name), QEMU_G2H(c->namesize));
}

#endif

struct qemu_SetDefaultPrinterW
{
    struct qemu_syscall super;
    uint64_t pszPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDefaultPrinterW(LPCWSTR pszPrinter)
{
    struct qemu_SetDefaultPrinterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEFAULTPRINTERW);
    call.pszPrinter = (ULONG_PTR)pszPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDefaultPrinterW(struct qemu_syscall *call)
{
    struct qemu_SetDefaultPrinterW *c = (struct qemu_SetDefaultPrinterW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDefaultPrinterW(QEMU_G2H(c->pszPrinter));
}

#endif

struct qemu_SetDefaultPrinterA
{
    struct qemu_syscall super;
    uint64_t pszPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetDefaultPrinterA(LPCSTR pszPrinter)
{
    struct qemu_SetDefaultPrinterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEFAULTPRINTERA);
    call.pszPrinter = (ULONG_PTR)pszPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDefaultPrinterA(struct qemu_syscall *call)
{
    struct qemu_SetDefaultPrinterA *c = (struct qemu_SetDefaultPrinterA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetDefaultPrinterA(QEMU_G2H(c->pszPrinter));
}

#endif

struct qemu_SetPrinterDataExA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pValueName;
    uint64_t Type;
    uint64_t pData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetPrinterDataExA(HANDLE hPrinter, LPCSTR pKeyName, LPCSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData)
{
    struct qemu_SetPrinterDataExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRINTERDATAEXA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pValueName = (ULONG_PTR)pValueName;
    call.Type = Type;
    call.pData = (ULONG_PTR)pData;
    call.cbData = cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrinterDataExA(struct qemu_syscall *call)
{
    struct qemu_SetPrinterDataExA *c = (struct qemu_SetPrinterDataExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrinterDataExA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pValueName), c->Type, QEMU_G2H(c->pData), c->cbData);
}

#endif

struct qemu_SetPrinterDataExW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pValueName;
    uint64_t Type;
    uint64_t pData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetPrinterDataExW(HANDLE hPrinter, LPCWSTR pKeyName, LPCWSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData)
{
    struct qemu_SetPrinterDataExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRINTERDATAEXW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pValueName = (ULONG_PTR)pValueName;
    call.Type = Type;
    call.pData = (ULONG_PTR)pData;
    call.cbData = cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrinterDataExW(struct qemu_syscall *call)
{
    struct qemu_SetPrinterDataExW *c = (struct qemu_SetPrinterDataExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrinterDataExW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pValueName), c->Type, QEMU_G2H(c->pData), c->cbData);
}

#endif

struct qemu_SetPrinterDataA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pValueName;
    uint64_t Type;
    uint64_t pData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetPrinterDataA(HANDLE hPrinter, LPSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData)
{
    struct qemu_SetPrinterDataA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRINTERDATAA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pValueName = (ULONG_PTR)pValueName;
    call.Type = Type;
    call.pData = (ULONG_PTR)pData;
    call.cbData = cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrinterDataA(struct qemu_syscall *call)
{
    struct qemu_SetPrinterDataA *c = (struct qemu_SetPrinterDataA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrinterDataA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pValueName), c->Type, QEMU_G2H(c->pData), c->cbData);
}

#endif

struct qemu_SetPrinterDataW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pValueName;
    uint64_t Type;
    uint64_t pData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SetPrinterDataW(HANDLE hPrinter, LPWSTR pValueName, DWORD Type, LPBYTE pData, DWORD cbData)
{
    struct qemu_SetPrinterDataW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPRINTERDATAW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pValueName = (ULONG_PTR)pValueName;
    call.Type = Type;
    call.pData = (ULONG_PTR)pData;
    call.cbData = cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPrinterDataW(struct qemu_syscall *call)
{
    struct qemu_SetPrinterDataW *c = (struct qemu_SetPrinterDataW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPrinterDataW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pValueName), c->Type, QEMU_G2H(c->pData), c->cbData);
}

#endif

struct qemu_GetPrinterDataExA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pValueName;
    uint64_t pType;
    uint64_t pData;
    uint64_t nSize;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrinterDataExA(HANDLE hPrinter, LPCSTR pKeyName, LPCSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDataExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDATAEXA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pValueName = (ULONG_PTR)pValueName;
    call.pType = (ULONG_PTR)pType;
    call.pData = (ULONG_PTR)pData;
    call.nSize = nSize;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDataExA(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDataExA *c = (struct qemu_GetPrinterDataExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrinterDataExA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pValueName), QEMU_G2H(c->pType), QEMU_G2H(c->pData), c->nSize, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrinterDataExW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pValueName;
    uint64_t pType;
    uint64_t pData;
    uint64_t nSize;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrinterDataExW(HANDLE hPrinter, LPCWSTR pKeyName, LPCWSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDataExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDATAEXW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pValueName = (ULONG_PTR)pValueName;
    call.pType = (ULONG_PTR)pType;
    call.pData = (ULONG_PTR)pData;
    call.nSize = nSize;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDataExW(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDataExW *c = (struct qemu_GetPrinterDataExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrinterDataExW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pValueName), QEMU_G2H(c->pType), QEMU_G2H(c->pData), c->nSize, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrinterDataA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pValueName;
    uint64_t pType;
    uint64_t pData;
    uint64_t nSize;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrinterDataA(HANDLE hPrinter, LPSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDataA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDATAA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pValueName = (ULONG_PTR)pValueName;
    call.pType = (ULONG_PTR)pType;
    call.pData = (ULONG_PTR)pData;
    call.nSize = nSize;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDataA(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDataA *c = (struct qemu_GetPrinterDataA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrinterDataA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pValueName), QEMU_G2H(c->pType), QEMU_G2H(c->pData), c->nSize, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetPrinterDataW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pValueName;
    uint64_t pType;
    uint64_t pData;
    uint64_t nSize;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI GetPrinterDataW(HANDLE hPrinter, LPWSTR pValueName, LPDWORD pType, LPBYTE pData, DWORD nSize, LPDWORD pcbNeeded)
{
    struct qemu_GetPrinterDataW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPRINTERDATAW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pValueName = (ULONG_PTR)pValueName;
    call.pType = (ULONG_PTR)pType;
    call.pData = (ULONG_PTR)pData;
    call.nSize = nSize;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPrinterDataW(struct qemu_syscall *call)
{
    struct qemu_GetPrinterDataW *c = (struct qemu_GetPrinterDataW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetPrinterDataW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pValueName), QEMU_G2H(c->pType), QEMU_G2H(c->pData), c->nSize, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_EnumPrinterDataExW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pEnumValues;
    uint64_t cbEnumValues;
    uint64_t pcbEnumValues;
    uint64_t pnEnumValues;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnumPrinterDataExW(HANDLE hPrinter, LPCWSTR pKeyName, LPBYTE pEnumValues, DWORD cbEnumValues, LPDWORD pcbEnumValues, LPDWORD pnEnumValues)
{
    struct qemu_EnumPrinterDataExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERDATAEXW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pEnumValues = (ULONG_PTR)pEnumValues;
    call.cbEnumValues = cbEnumValues;
    call.pcbEnumValues = (ULONG_PTR)pcbEnumValues;
    call.pnEnumValues = (ULONG_PTR)pnEnumValues;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterDataExW(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterDataExW *c = (struct qemu_EnumPrinterDataExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrinterDataExW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pEnumValues), c->cbEnumValues, QEMU_G2H(c->pcbEnumValues), QEMU_G2H(c->pnEnumValues));
}

#endif

struct qemu_EnumPrinterDataExA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pEnumValues;
    uint64_t cbEnumValues;
    uint64_t pcbEnumValues;
    uint64_t pnEnumValues;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnumPrinterDataExA(HANDLE hPrinter, LPCSTR pKeyName, LPBYTE pEnumValues, DWORD cbEnumValues, LPDWORD pcbEnumValues, LPDWORD pnEnumValues)
{
    struct qemu_EnumPrinterDataExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERDATAEXA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pEnumValues = (ULONG_PTR)pEnumValues;
    call.cbEnumValues = cbEnumValues;
    call.pcbEnumValues = (ULONG_PTR)pcbEnumValues;
    call.pnEnumValues = (ULONG_PTR)pnEnumValues;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterDataExA(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterDataExA *c = (struct qemu_EnumPrinterDataExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrinterDataExA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pEnumValues), c->cbEnumValues, QEMU_G2H(c->pcbEnumValues), QEMU_G2H(c->pnEnumValues));
}

#endif

struct qemu_AbortPrinter
{
    struct qemu_syscall super;
    uint64_t hPrinter;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AbortPrinter(HANDLE hPrinter)
{
    struct qemu_AbortPrinter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ABORTPRINTER);
    call.hPrinter = (ULONG_PTR)hPrinter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AbortPrinter(struct qemu_syscall *call)
{
    struct qemu_AbortPrinter *c = (struct qemu_AbortPrinter *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AbortPrinter(QEMU_G2H(c->hPrinter));
}

#endif

struct qemu_AddPortA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t hWnd;
    uint64_t pMonitorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPortA(LPSTR pName, HWND hWnd, LPSTR pMonitorName)
{
    struct qemu_AddPortA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPORTA);
    call.pName = (ULONG_PTR)pName;
    call.hWnd = (ULONG_PTR)hWnd;
    call.pMonitorName = (ULONG_PTR)pMonitorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPortA(struct qemu_syscall *call)
{
    struct qemu_AddPortA *c = (struct qemu_AddPortA *)call;
    WINE_TRACE("\n");
    c->super.iret = AddPortA(QEMU_G2H(c->pName), QEMU_G2H(c->hWnd), QEMU_G2H(c->pMonitorName));
}

#endif

struct qemu_AddPortW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t hWnd;
    uint64_t pMonitorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPortW(LPWSTR pName, HWND hWnd, LPWSTR pMonitorName)
{
    struct qemu_AddPortW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPORTW);
    call.pName = (ULONG_PTR)pName;
    call.hWnd = (ULONG_PTR)hWnd;
    call.pMonitorName = (ULONG_PTR)pMonitorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPortW(struct qemu_syscall *call)
{
    struct qemu_AddPortW *c = (struct qemu_AddPortW *)call;
    WINE_TRACE("\n");
    c->super.iret = AddPortW(QEMU_G2H(c->pName), QEMU_G2H(c->hWnd), QEMU_G2H(c->pMonitorName));
}

#endif

struct qemu_AddPortEx
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t level;
    uint64_t pBuffer;
    uint64_t pMonitorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPortExA(LPSTR pName, DWORD level, LPBYTE pBuffer, LPSTR pMonitorName)
{
    struct qemu_AddPortEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPORTEXA);
    call.pName = (ULONG_PTR)pName;
    call.level = level;
    call.pBuffer = (ULONG_PTR)pBuffer;
    call.pMonitorName = (ULONG_PTR)pMonitorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI AddPortExW(LPWSTR pName, DWORD level, LPBYTE pBuffer, LPWSTR pMonitorName)
{
    struct qemu_AddPortEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPORTEXW);
    call.pName = (ULONG_PTR)pName;
    call.level = level;
    call.pBuffer = (ULONG_PTR)pBuffer;
    call.pMonitorName = (ULONG_PTR)pMonitorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPortEx(struct qemu_syscall *call)
{
    struct qemu_AddPortEx *c = (struct qemu_AddPortEx *)call;
    PORT_INFO_2W stack, *port = &stack;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    port = QEMU_G2H(c->pBuffer);
#else
    if (!c->pBuffer)
        port = NULL;
    else
        PORT_INFO_2_g2h(port, QEMU_G2H(c->pBuffer));
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_ADDPORTEXA))
        c->super.iret = AddPortExA(QEMU_G2H(c->pName), c->level, (BYTE *)port, QEMU_G2H(c->pMonitorName));
    else
        c->super.iret = AddPortExW(QEMU_G2H(c->pName), c->level, (BYTE *)port, QEMU_G2H(c->pMonitorName));
}

#endif

struct qemu_AddPrinterConnectionA
{
    struct qemu_syscall super;
    uint64_t pName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrinterConnectionA(LPSTR pName)
{
    struct qemu_AddPrinterConnectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERCONNECTIONA);
    call.pName = (ULONG_PTR)pName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrinterConnectionA(struct qemu_syscall *call)
{
    struct qemu_AddPrinterConnectionA *c = (struct qemu_AddPrinterConnectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrinterConnectionA(QEMU_G2H(c->pName));
}

#endif

struct qemu_AddPrinterConnectionW
{
    struct qemu_syscall super;
    uint64_t pName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrinterConnectionW(LPWSTR pName)
{
    struct qemu_AddPrinterConnectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERCONNECTIONW);
    call.pName = (ULONG_PTR)pName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrinterConnectionW(struct qemu_syscall *call)
{
    struct qemu_AddPrinterConnectionW *c = (struct qemu_AddPrinterConnectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrinterConnectionW(QEMU_G2H(c->pName));
}

#endif

struct qemu_AddPrinterDriverExW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t level;
    uint64_t pDriverInfo;
    uint64_t dwFileCopyFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrinterDriverExW(LPWSTR pName, DWORD level, LPBYTE pDriverInfo, DWORD dwFileCopyFlags)
{
    struct qemu_AddPrinterDriverExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERDRIVEREXW);
    call.pName = (ULONG_PTR)pName;
    call.level = level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;
    call.dwFileCopyFlags = dwFileCopyFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrinterDriverExW(struct qemu_syscall *call)
{
    struct qemu_AddPrinterDriverExW *c = (struct qemu_AddPrinterDriverExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrinterDriverExW(QEMU_G2H(c->pName), c->level, QEMU_G2H(c->pDriverInfo), c->dwFileCopyFlags);
}

#endif

struct qemu_AddPrinterDriverExA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pDriverInfo;
    uint64_t dwFileCopyFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AddPrinterDriverExA(LPSTR pName, DWORD Level, LPBYTE pDriverInfo, DWORD dwFileCopyFlags)
{
    struct qemu_AddPrinterDriverExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDPRINTERDRIVEREXA);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pDriverInfo = (ULONG_PTR)pDriverInfo;
    call.dwFileCopyFlags = dwFileCopyFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddPrinterDriverExA(struct qemu_syscall *call)
{
    struct qemu_AddPrinterDriverExA *c = (struct qemu_AddPrinterDriverExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AddPrinterDriverExA(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pDriverInfo), c->dwFileCopyFlags);
}

#endif

struct qemu_ConfigurePortA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t hWnd;
    uint64_t pPortName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConfigurePortA(LPSTR pName, HWND hWnd, LPSTR pPortName)
{
    struct qemu_ConfigurePortA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONFIGUREPORTA);
    call.pName = (ULONG_PTR)pName;
    call.hWnd = (ULONG_PTR)hWnd;
    call.pPortName = (ULONG_PTR)pPortName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConfigurePortA(struct qemu_syscall *call)
{
    struct qemu_ConfigurePortA *c = (struct qemu_ConfigurePortA *)call;
    WINE_TRACE("\n");
    c->super.iret = ConfigurePortA(QEMU_G2H(c->pName), QEMU_G2H(c->hWnd), QEMU_G2H(c->pPortName));
}

#endif

struct qemu_ConfigurePortW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t hWnd;
    uint64_t pPortName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConfigurePortW(LPWSTR pName, HWND hWnd, LPWSTR pPortName)
{
    struct qemu_ConfigurePortW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONFIGUREPORTW);
    call.pName = (ULONG_PTR)pName;
    call.hWnd = (ULONG_PTR)hWnd;
    call.pPortName = (ULONG_PTR)pPortName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConfigurePortW(struct qemu_syscall *call)
{
    struct qemu_ConfigurePortW *c = (struct qemu_ConfigurePortW *)call;
    WINE_TRACE("\n");
    c->super.iret = ConfigurePortW(QEMU_G2H(c->pName), QEMU_G2H(c->hWnd), QEMU_G2H(c->pPortName));
}

#endif

struct qemu_ConnectToPrinterDlg
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI ConnectToPrinterDlg(HWND hWnd, DWORD Flags)
{
    struct qemu_ConnectToPrinterDlg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONNECTTOPRINTERDLG);
    call.hWnd = (ULONG_PTR)hWnd;
    call.Flags = Flags;

    qemu_syscall(&call.super);

        return (HANDLE)(ULONG_PTR)call.super.iret;
;
}

#else

void qemu_ConnectToPrinterDlg(struct qemu_syscall *call)
{
    struct qemu_ConnectToPrinterDlg *c = (struct qemu_ConnectToPrinterDlg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ConnectToPrinterDlg(QEMU_G2H(c->hWnd), c->Flags);
}

#endif

struct qemu_DeletePrinterConnectionA
{
    struct qemu_syscall super;
    uint64_t pName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinterConnectionA(LPSTR pName)
{
    struct qemu_DeletePrinterConnectionA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERCONNECTIONA);
    call.pName = (ULONG_PTR)pName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterConnectionA(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterConnectionA *c = (struct qemu_DeletePrinterConnectionA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterConnectionA(QEMU_G2H(c->pName));
}

#endif

struct qemu_DeletePrinterConnectionW
{
    struct qemu_syscall super;
    uint64_t pName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinterConnectionW(LPWSTR pName)
{
    struct qemu_DeletePrinterConnectionW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERCONNECTIONW);
    call.pName = (ULONG_PTR)pName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterConnectionW(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterConnectionW *c = (struct qemu_DeletePrinterConnectionW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterConnectionW(QEMU_G2H(c->pName));
}

#endif

struct qemu_DeletePrinterDriverExW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pDriverName;
    uint64_t dwDeleteFlag;
    uint64_t dwVersionFlag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinterDriverExW(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pDriverName, DWORD dwDeleteFlag, DWORD dwVersionFlag)
{
    struct qemu_DeletePrinterDriverExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERDRIVEREXW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pDriverName = (ULONG_PTR)pDriverName;
    call.dwDeleteFlag = dwDeleteFlag;
    call.dwVersionFlag = dwVersionFlag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterDriverExW(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterDriverExW *c = (struct qemu_DeletePrinterDriverExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterDriverExW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pDriverName), c->dwDeleteFlag, c->dwVersionFlag);
}

#endif

struct qemu_DeletePrinterDriverExA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pDriverName;
    uint64_t dwDeleteFlag;
    uint64_t dwVersionFlag;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrinterDriverExA(LPSTR pName, LPSTR pEnvironment, LPSTR pDriverName, DWORD dwDeleteFlag, DWORD dwVersionFlag)
{
    struct qemu_DeletePrinterDriverExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERDRIVEREXA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pDriverName = (ULONG_PTR)pDriverName;
    call.dwDeleteFlag = dwDeleteFlag;
    call.dwVersionFlag = dwVersionFlag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterDriverExA(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterDriverExA *c = (struct qemu_DeletePrinterDriverExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterDriverExA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pDriverName), c->dwDeleteFlag, c->dwVersionFlag);
}

#endif

struct qemu_DeletePrinterDataExW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pValueName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeletePrinterDataExW(HANDLE hPrinter, LPCWSTR pKeyName, LPCWSTR pValueName)
{
    struct qemu_DeletePrinterDataExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERDATAEXW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pValueName = (ULONG_PTR)pValueName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterDataExW(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterDataExW *c = (struct qemu_DeletePrinterDataExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterDataExW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pValueName));
}

#endif

struct qemu_DeletePrinterDataExA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t pKeyName;
    uint64_t pValueName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI DeletePrinterDataExA(HANDLE hPrinter, LPCSTR pKeyName, LPCSTR pValueName)
{
    struct qemu_DeletePrinterDataExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTERDATAEXA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.pKeyName = (ULONG_PTR)pKeyName;
    call.pValueName = (ULONG_PTR)pValueName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrinterDataExA(struct qemu_syscall *call)
{
    struct qemu_DeletePrinterDataExA *c = (struct qemu_DeletePrinterDataExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrinterDataExA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->pKeyName), QEMU_G2H(c->pValueName));
}

#endif

struct qemu_DeletePrintProcessorA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pPrintProcessorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrintProcessorA(LPSTR pName, LPSTR pEnvironment, LPSTR pPrintProcessorName)
{
    struct qemu_DeletePrintProcessorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTPROCESSORA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pPrintProcessorName = (ULONG_PTR)pPrintProcessorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrintProcessorA(struct qemu_syscall *call)
{
    struct qemu_DeletePrintProcessorA *c = (struct qemu_DeletePrintProcessorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrintProcessorA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pPrintProcessorName));
}

#endif

struct qemu_DeletePrintProcessorW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pPrintProcessorName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrintProcessorW(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pPrintProcessorName)
{
    struct qemu_DeletePrintProcessorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTPROCESSORW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pPrintProcessorName = (ULONG_PTR)pPrintProcessorName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrintProcessorW(struct qemu_syscall *call)
{
    struct qemu_DeletePrintProcessorW *c = (struct qemu_DeletePrintProcessorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrintProcessorW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pPrintProcessorName));
}

#endif

struct qemu_DeletePrintProvidorA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pPrintProviderName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrintProvidorA(LPSTR pName, LPSTR pEnvironment, LPSTR pPrintProviderName)
{
    struct qemu_DeletePrintProvidorA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTPROVIDORA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pPrintProviderName = (ULONG_PTR)pPrintProviderName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrintProvidorA(struct qemu_syscall *call)
{
    struct qemu_DeletePrintProvidorA *c = (struct qemu_DeletePrintProvidorA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrintProvidorA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pPrintProviderName));
}

#endif

struct qemu_DeletePrintProvidorW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t pPrintProviderName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeletePrintProvidorW(LPWSTR pName, LPWSTR pEnvironment, LPWSTR pPrintProviderName)
{
    struct qemu_DeletePrintProvidorW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEPRINTPROVIDORW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.pPrintProviderName = (ULONG_PTR)pPrintProviderName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeletePrintProvidorW(struct qemu_syscall *call)
{
    struct qemu_DeletePrintProvidorW *c = (struct qemu_DeletePrintProvidorW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeletePrintProvidorW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), QEMU_G2H(c->pPrintProviderName));
}

#endif

struct qemu_EnumFormsA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pForm;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumFormsA(HANDLE hPrinter, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumFormsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFORMSA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFormsA(struct qemu_syscall *call)
{
    struct qemu_EnumFormsA *c = (struct qemu_EnumFormsA *)call;
    WINE_WARN("Not handling because not implemented in Wine.\n");
    /* This function is not implemented in Wine. */
    c->super.iret = EnumFormsA(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pForm), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
    if (c->super.iret)
        WINE_FIXME("EnumFormsA succeeded, implement a proper wrapper.\n");
}

#endif

struct qemu_EnumFormsW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t Level;
    uint64_t pForm;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumFormsW(HANDLE hPrinter, DWORD Level, LPBYTE pForm, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumFormsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMFORMSW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.Level = Level;
    call.pForm = (ULONG_PTR)pForm;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumFormsW(struct qemu_syscall *call)
{
    struct qemu_EnumFormsW *c = (struct qemu_EnumFormsW *)call;
    WINE_WARN("Not handling because not implemented in Wine.\n");
    /* This function is not implemented in Wine. */
    c->super.iret = EnumFormsW(QEMU_G2H(c->hPrinter), c->Level, QEMU_G2H(c->pForm), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
    if (c->super.iret)
        WINE_FIXME("EnumFormsA succeeded, implement a proper wrapper.\n");
}

#endif

struct qemu_EnumMonitorsA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pMonitors;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumMonitorsA(LPSTR pName, DWORD Level, LPBYTE pMonitors, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumMonitorsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMMONITORSA);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pMonitors = (ULONG_PTR)pMonitors;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumMonitorsA(struct qemu_syscall *call)
{
    struct qemu_EnumMonitorsA *c = (struct qemu_EnumMonitorsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumMonitorsA(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pMonitors), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumMonitorsW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t Level;
    uint64_t pMonitors;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumMonitorsW(LPWSTR pName, DWORD Level, LPBYTE pMonitors, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumMonitorsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMMONITORSW);
    call.pName = (ULONG_PTR)pName;
    call.Level = Level;
    call.pMonitors = (ULONG_PTR)pMonitors;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumMonitorsW(struct qemu_syscall *call)
{
    struct qemu_EnumMonitorsW *c = (struct qemu_EnumMonitorsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumMonitorsW(QEMU_G2H(c->pName), c->Level, QEMU_G2H(c->pMonitors), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_SpoolerInit
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SpoolerInit(void)
{
    struct qemu_SpoolerInit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SPOOLERINIT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI SpoolerInit(void);
void qemu_SpoolerInit(struct qemu_syscall *call)
{
    struct qemu_SpoolerInit *c = (struct qemu_SpoolerInit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SpoolerInit();
}

#endif

struct qemu_XcvDataW
{
    struct qemu_syscall super;
    uint64_t hXcv;
    uint64_t pszDataName;
    uint64_t pInputData;
    uint64_t cbInputData;
    uint64_t pOutputData;
    uint64_t cbOutputData;
    uint64_t pcbOutputNeeded;
    uint64_t pdwStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI XcvDataW(HANDLE hXcv, LPCWSTR pszDataName, PBYTE pInputData, DWORD cbInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded, PDWORD pdwStatus)
{
    struct qemu_XcvDataW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XCVDATAW);
    call.hXcv = (ULONG_PTR)hXcv;
    call.pszDataName = (ULONG_PTR)pszDataName;
    call.pInputData = (ULONG_PTR)pInputData;
    call.cbInputData = cbInputData;
    call.pOutputData = (ULONG_PTR)pOutputData;
    call.cbOutputData = cbOutputData;
    call.pcbOutputNeeded = (ULONG_PTR)pcbOutputNeeded;
    call.pdwStatus = (ULONG_PTR)pdwStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XcvDataW(struct qemu_syscall *call)
{
    struct qemu_XcvDataW *c = (struct qemu_XcvDataW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XcvDataW(QEMU_G2H(c->hXcv), QEMU_G2H(c->pszDataName), QEMU_G2H(c->pInputData), c->cbInputData, QEMU_G2H(c->pOutputData), c->cbOutputData, QEMU_G2H(c->pcbOutputNeeded), QEMU_G2H(c->pdwStatus));
}

#endif

struct qemu_EnumPrinterDataA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t dwIndex;
    uint64_t pValueName;
    uint64_t cbValueName;
    uint64_t pcbValueName;
    uint64_t pType;
    uint64_t pData;
    uint64_t cbData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnumPrinterDataA(HANDLE hPrinter, DWORD dwIndex, LPSTR pValueName, DWORD cbValueName, LPDWORD pcbValueName, LPDWORD pType, LPBYTE pData, DWORD cbData, LPDWORD pcbData)
{
    struct qemu_EnumPrinterDataA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERDATAA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.dwIndex = dwIndex;
    call.pValueName = (ULONG_PTR)pValueName;
    call.cbValueName = cbValueName;
    call.pcbValueName = (ULONG_PTR)pcbValueName;
    call.pType = (ULONG_PTR)pType;
    call.pData = (ULONG_PTR)pData;
    call.cbData = cbData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterDataA(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterDataA *c = (struct qemu_EnumPrinterDataA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrinterDataA(QEMU_G2H(c->hPrinter), c->dwIndex, QEMU_G2H(c->pValueName), c->cbValueName, QEMU_G2H(c->pcbValueName), QEMU_G2H(c->pType), QEMU_G2H(c->pData), c->cbData, QEMU_G2H(c->pcbData));
}

#endif

struct qemu_EnumPrinterDataW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t dwIndex;
    uint64_t pValueName;
    uint64_t cbValueName;
    uint64_t pcbValueName;
    uint64_t pType;
    uint64_t pData;
    uint64_t cbData;
    uint64_t pcbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnumPrinterDataW(HANDLE hPrinter, DWORD dwIndex, LPWSTR pValueName, DWORD cbValueName, LPDWORD pcbValueName, LPDWORD pType, LPBYTE pData, DWORD cbData, LPDWORD pcbData)
{
    struct qemu_EnumPrinterDataW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERDATAW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.dwIndex = dwIndex;
    call.pValueName = (ULONG_PTR)pValueName;
    call.cbValueName = cbValueName;
    call.pcbValueName = (ULONG_PTR)pcbValueName;
    call.pType = (ULONG_PTR)pType;
    call.pData = (ULONG_PTR)pData;
    call.cbData = cbData;
    call.pcbData = (ULONG_PTR)pcbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterDataW(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterDataW *c = (struct qemu_EnumPrinterDataW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrinterDataW(QEMU_G2H(c->hPrinter), c->dwIndex, QEMU_G2H(c->pValueName), c->cbValueName, QEMU_G2H(c->pcbValueName), QEMU_G2H(c->pType), QEMU_G2H(c->pData), c->cbData, QEMU_G2H(c->pcbData));
}

#endif

struct qemu_EnumPrinterKeyA
{
    struct qemu_syscall super;
    uint64_t printer;
    uint64_t key;
    uint64_t subkey;
    uint64_t size;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnumPrinterKeyA(HANDLE printer, const CHAR *key, CHAR *subkey, DWORD size, DWORD *needed)
{
    struct qemu_EnumPrinterKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERKEYA);
    call.printer = (ULONG_PTR)printer;
    call.key = (ULONG_PTR)key;
    call.subkey = (ULONG_PTR)subkey;
    call.size = size;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterKeyA(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterKeyA *c = (struct qemu_EnumPrinterKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrinterKeyA(QEMU_G2H(c->printer), QEMU_G2H(c->key), QEMU_G2H(c->subkey), c->size, QEMU_G2H(c->needed));
}

#endif

struct qemu_EnumPrinterKeyW
{
    struct qemu_syscall super;
    uint64_t printer;
    uint64_t key;
    uint64_t subkey;
    uint64_t size;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI EnumPrinterKeyW(HANDLE printer, const WCHAR *key, WCHAR *subkey, DWORD size, DWORD *needed)
{
    struct qemu_EnumPrinterKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTERKEYW);
    call.printer = (ULONG_PTR)printer;
    call.key = (ULONG_PTR)key;
    call.subkey = (ULONG_PTR)subkey;
    call.size = size;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrinterKeyW(struct qemu_syscall *call)
{
    struct qemu_EnumPrinterKeyW *c = (struct qemu_EnumPrinterKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrinterKeyW(QEMU_G2H(c->printer), QEMU_G2H(c->key), QEMU_G2H(c->subkey), c->size, QEMU_G2H(c->needed));
}

#endif

struct qemu_EnumPrintProcessorDatatypesA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pPrintProcessorName;
    uint64_t Level;
    uint64_t pDatatypes;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrintProcessorDatatypesA(LPSTR pName, LPSTR pPrintProcessorName, DWORD Level, LPBYTE pDatatypes, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrintProcessorDatatypesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTPROCESSORDATATYPESA);
    call.pName = (ULONG_PTR)pName;
    call.pPrintProcessorName = (ULONG_PTR)pPrintProcessorName;
    call.Level = Level;
    call.pDatatypes = (ULONG_PTR)pDatatypes;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrintProcessorDatatypesA(struct qemu_syscall *call)
{
    struct qemu_EnumPrintProcessorDatatypesA *c = (struct qemu_EnumPrintProcessorDatatypesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrintProcessorDatatypesA(QEMU_G2H(c->pName), QEMU_G2H(c->pPrintProcessorName), c->Level, QEMU_G2H(c->pDatatypes), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumPrintProcessorDatatypesW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pPrintProcessorName;
    uint64_t Level;
    uint64_t pDatatypes;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrintProcessorDatatypesW(LPWSTR pName, LPWSTR pPrintProcessorName, DWORD Level, LPBYTE pDatatypes, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrintProcessorDatatypesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTPROCESSORDATATYPESW);
    call.pName = (ULONG_PTR)pName;
    call.pPrintProcessorName = (ULONG_PTR)pPrintProcessorName;
    call.Level = Level;
    call.pDatatypes = (ULONG_PTR)pDatatypes;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrintProcessorDatatypesW(struct qemu_syscall *call)
{
    struct qemu_EnumPrintProcessorDatatypesW *c = (struct qemu_EnumPrintProcessorDatatypesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrintProcessorDatatypesW(QEMU_G2H(c->pName), QEMU_G2H(c->pPrintProcessorName), c->Level, QEMU_G2H(c->pDatatypes), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumPrintProcessorsA
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pPPInfo;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrintProcessorsA(LPSTR pName, LPSTR pEnvironment, DWORD Level, LPBYTE pPPInfo, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrintProcessorsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTPROCESSORSA);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pPPInfo = (ULONG_PTR)pPPInfo;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrintProcessorsA(struct qemu_syscall *call)
{
    struct qemu_EnumPrintProcessorsA *c = (struct qemu_EnumPrintProcessorsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrintProcessorsA(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), c->Level, QEMU_G2H(c->pPPInfo), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_EnumPrintProcessorsW
{
    struct qemu_syscall super;
    uint64_t pName;
    uint64_t pEnvironment;
    uint64_t Level;
    uint64_t pPPInfo;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
    uint64_t pcReturned;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumPrintProcessorsW(LPWSTR pName, LPWSTR pEnvironment, DWORD Level, LPBYTE pPPInfo, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
    struct qemu_EnumPrintProcessorsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPRINTPROCESSORSW);
    call.pName = (ULONG_PTR)pName;
    call.pEnvironment = (ULONG_PTR)pEnvironment;
    call.Level = Level;
    call.pPPInfo = (ULONG_PTR)pPPInfo;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;
    call.pcReturned = (ULONG_PTR)pcReturned;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPrintProcessorsW(struct qemu_syscall *call)
{
    struct qemu_EnumPrintProcessorsW *c = (struct qemu_EnumPrintProcessorsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPrintProcessorsW(QEMU_G2H(c->pName), QEMU_G2H(c->pEnvironment), c->Level, QEMU_G2H(c->pPPInfo), c->cbBuf, QEMU_G2H(c->pcbNeeded), QEMU_G2H(c->pcReturned));
}

#endif

struct qemu_ExtDeviceMode
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hInst;
    uint64_t pDevModeOutput;
    uint64_t pDeviceName;
    uint64_t pPort;
    uint64_t pDevModeInput;
    uint64_t pProfile;
    uint64_t fMode;
};

#ifdef QEMU_DLL_GUEST

/* Mingw's headers don't declare this as WINAPI. Bug? */
LONG WINAPI qemu_ExtDeviceMode(HWND hWnd, HANDLE hInst, LPDEVMODEA pDevModeOutput, LPSTR pDeviceName, LPSTR pPort, LPDEVMODEA pDevModeInput, LPSTR pProfile, DWORD fMode)
{
    struct qemu_ExtDeviceMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTDEVICEMODE);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hInst = (ULONG_PTR)hInst;
    call.pDevModeOutput = (ULONG_PTR)pDevModeOutput;
    call.pDeviceName = (ULONG_PTR)pDeviceName;
    call.pPort = (ULONG_PTR)pPort;
    call.pDevModeInput = (ULONG_PTR)pDevModeInput;
    call.pProfile = (ULONG_PTR)pProfile;
    call.fMode = fMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtDeviceMode(struct qemu_syscall *call)
{
    struct qemu_ExtDeviceMode *c = (struct qemu_ExtDeviceMode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtDeviceMode(QEMU_G2H(c->hWnd), QEMU_G2H(c->hInst), QEMU_G2H(c->pDevModeOutput), QEMU_G2H(c->pDeviceName), QEMU_G2H(c->pPort), QEMU_G2H(c->pDevModeInput), QEMU_G2H(c->pProfile), c->fMode);
}

#endif

struct qemu_FindClosePrinterChangeNotification
{
    struct qemu_syscall super;
    uint64_t hChange;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindClosePrinterChangeNotification(HANDLE hChange)
{
    struct qemu_FindClosePrinterChangeNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDCLOSEPRINTERCHANGENOTIFICATION);
    call.hChange = (ULONG_PTR)hChange;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindClosePrinterChangeNotification(struct qemu_syscall *call)
{
    struct qemu_FindClosePrinterChangeNotification *c = (struct qemu_FindClosePrinterChangeNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindClosePrinterChangeNotification(QEMU_G2H(c->hChange));
}

#endif

struct qemu_FindFirstPrinterChangeNotification
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t fdwFlags;
    uint64_t fdwOptions;
    uint64_t pPrinterNotifyOptions;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI FindFirstPrinterChangeNotification(HANDLE hPrinter, DWORD fdwFlags, DWORD fdwOptions, LPVOID pPrinterNotifyOptions)
{
    struct qemu_FindFirstPrinterChangeNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDFIRSTPRINTERCHANGENOTIFICATION);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.fdwFlags = fdwFlags;
    call.fdwOptions = fdwOptions;
    call.pPrinterNotifyOptions = (ULONG_PTR)pPrinterNotifyOptions;

    qemu_syscall(&call.super);

        return (HANDLE)(ULONG_PTR)call.super.iret;
;
}

#else

void qemu_FindFirstPrinterChangeNotification(struct qemu_syscall *call)
{
    struct qemu_FindFirstPrinterChangeNotification *c = (struct qemu_FindFirstPrinterChangeNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)FindFirstPrinterChangeNotification(QEMU_G2H(c->hPrinter), c->fdwFlags, c->fdwOptions, QEMU_G2H(c->pPrinterNotifyOptions));
}

#endif

struct qemu_FindNextPrinterChangeNotification
{
    struct qemu_syscall super;
    uint64_t hChange;
    uint64_t pdwChange;
    uint64_t pPrinterNotifyOptions;
    uint64_t ppPrinterNotifyInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindNextPrinterChangeNotification(HANDLE hChange, PDWORD pdwChange, LPVOID pPrinterNotifyOptions, LPVOID *ppPrinterNotifyInfo)
{
    struct qemu_FindNextPrinterChangeNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDNEXTPRINTERCHANGENOTIFICATION);
    call.hChange = (ULONG_PTR)hChange;
    call.pdwChange = (ULONG_PTR)pdwChange;
    call.pPrinterNotifyOptions = (ULONG_PTR)pPrinterNotifyOptions;
    call.ppPrinterNotifyInfo = (ULONG_PTR)ppPrinterNotifyInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindNextPrinterChangeNotification(struct qemu_syscall *call)
{
    struct qemu_FindNextPrinterChangeNotification *c = (struct qemu_FindNextPrinterChangeNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindNextPrinterChangeNotification(QEMU_G2H(c->hChange), QEMU_G2H(c->pdwChange), QEMU_G2H(c->pPrinterNotifyOptions), QEMU_G2H(c->ppPrinterNotifyInfo));
}

#endif

struct qemu_FreePrinterNotifyInfo
{
    struct qemu_syscall super;
    uint64_t pPrinterNotifyInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreePrinterNotifyInfo(PPRINTER_NOTIFY_INFO pPrinterNotifyInfo)
{
    struct qemu_FreePrinterNotifyInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEPRINTERNOTIFYINFO);
    call.pPrinterNotifyInfo = (ULONG_PTR)pPrinterNotifyInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreePrinterNotifyInfo(struct qemu_syscall *call)
{
    struct qemu_FreePrinterNotifyInfo *c = (struct qemu_FreePrinterNotifyInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreePrinterNotifyInfo(QEMU_G2H(c->pPrinterNotifyInfo));
}

#endif

struct qemu_GetJobA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t JobId;
    uint64_t Level;
    uint64_t pJob;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetJobA(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetJobA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETJOBA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.JobId = JobId;
    call.Level = Level;
    call.pJob = (ULONG_PTR)pJob;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetJobA(struct qemu_syscall *call)
{
    struct qemu_GetJobA *c = (struct qemu_GetJobA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetJobA(QEMU_G2H(c->hPrinter), c->JobId, c->Level, QEMU_G2H(c->pJob), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_GetJobW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t JobId;
    uint64_t Level;
    uint64_t pJob;
    uint64_t cbBuf;
    uint64_t pcbNeeded;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetJobW(HANDLE hPrinter, DWORD JobId, DWORD Level, LPBYTE pJob, DWORD cbBuf, LPDWORD pcbNeeded)
{
    struct qemu_GetJobW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETJOBW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.JobId = JobId;
    call.Level = Level;
    call.pJob = (ULONG_PTR)pJob;
    call.cbBuf = cbBuf;
    call.pcbNeeded = (ULONG_PTR)pcbNeeded;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetJobW(struct qemu_syscall *call)
{
    struct qemu_GetJobW *c = (struct qemu_GetJobW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetJobW(QEMU_G2H(c->hPrinter), c->JobId, c->Level, QEMU_G2H(c->pJob), c->cbBuf, QEMU_G2H(c->pcbNeeded));
}

#endif

struct qemu_ScheduleJob
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t dwJobID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ScheduleJob(HANDLE hPrinter, DWORD dwJobID)
{
    struct qemu_ScheduleJob call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SCHEDULEJOB);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.dwJobID = dwJobID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ScheduleJob(struct qemu_syscall *call)
{
    struct qemu_ScheduleJob *c = (struct qemu_ScheduleJob *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ScheduleJob(QEMU_G2H(c->hPrinter), c->dwJobID);
}

#endif

struct qemu_StartDocDlgA
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t doc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR WINAPI StartDocDlgA(HANDLE hPrinter, DOCINFOA *doc)
{
    struct qemu_StartDocDlgA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTDOCDLGA);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.doc = (ULONG_PTR)doc;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StartDocDlgA(struct qemu_syscall *call)
{
    struct qemu_StartDocDlgA *c = (struct qemu_StartDocDlgA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StartDocDlgA(QEMU_G2H(c->hPrinter), QEMU_G2H(c->doc));
}

#endif

struct qemu_StartDocDlgW
{
    struct qemu_syscall super;
    uint64_t hPrinter;
    uint64_t doc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPWSTR WINAPI StartDocDlgW(HANDLE hPrinter, DOCINFOW *doc)
{
    struct qemu_StartDocDlgW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTDOCDLGW);
    call.hPrinter = (ULONG_PTR)hPrinter;
    call.doc = (ULONG_PTR)doc;

    qemu_syscall(&call.super);

    return (LPWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_StartDocDlgW(struct qemu_syscall *call)
{
    struct qemu_StartDocDlgW *c = (struct qemu_StartDocDlgW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)StartDocDlgW(QEMU_G2H(c->hPrinter), QEMU_G2H(c->doc));
}

#endif

struct qemu_UploadPrinterDriverPackageA
{
    struct qemu_syscall super;
    uint64_t server;
    uint64_t path;
    uint64_t env;
    uint64_t flags;
    uint64_t hwnd;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UploadPrinterDriverPackageA(LPCSTR server, LPCSTR path, LPCSTR env, DWORD flags, HWND hwnd, LPSTR dst, PULONG dstlen)
{
    struct qemu_UploadPrinterDriverPackageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPLOADPRINTERDRIVERPACKAGEA);
    call.server = (ULONG_PTR)server;
    call.path = (ULONG_PTR)path;
    call.env = (ULONG_PTR)env;
    call.flags = flags;
    call.hwnd = (ULONG_PTR)hwnd;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UploadPrinterDriverPackageA(struct qemu_syscall *call)
{
    struct qemu_UploadPrinterDriverPackageA *c = (struct qemu_UploadPrinterDriverPackageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UploadPrinterDriverPackageA(QEMU_G2H(c->server), QEMU_G2H(c->path), QEMU_G2H(c->env), c->flags, QEMU_G2H(c->hwnd), QEMU_G2H(c->dst), QEMU_G2H(c->dstlen));
}

#endif

struct qemu_UploadPrinterDriverPackageW
{
    struct qemu_syscall super;
    uint64_t server;
    uint64_t path;
    uint64_t env;
    uint64_t flags;
    uint64_t hwnd;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI UploadPrinterDriverPackageW(LPCWSTR server, LPCWSTR path, LPCWSTR env, DWORD flags, HWND hwnd, LPWSTR dst, PULONG dstlen)
{
    struct qemu_UploadPrinterDriverPackageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPLOADPRINTERDRIVERPACKAGEW);
    call.server = (ULONG_PTR)server;
    call.path = (ULONG_PTR)path;
    call.env = (ULONG_PTR)env;
    call.flags = flags;
    call.hwnd = (ULONG_PTR)hwnd;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UploadPrinterDriverPackageW(struct qemu_syscall *call)
{
    struct qemu_UploadPrinterDriverPackageW *c = (struct qemu_UploadPrinterDriverPackageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UploadPrinterDriverPackageW(QEMU_G2H(c->server), QEMU_G2H(c->path), QEMU_G2H(c->env), c->flags, QEMU_G2H(c->hwnd), QEMU_G2H(c->dst), QEMU_G2H(c->dstlen));
}

#endif

