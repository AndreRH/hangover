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
#include "qemu_user32.h"

#ifdef QEMU_DLL_GUEST

typedef enum DPI_AWARENESS
{
    DPI_AWARENESS_INVALID = -1,
    DPI_AWARENESS_UNAWARE = 0,
    DPI_AWARENESS_SYSTEM_AWARE,
    DPI_AWARENESS_PER_MONITOR_AWARE
} DPI_AWARENESS;

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);

#endif

struct qemu_SystemParametersInfo
{
    struct qemu_syscall super;
    uint64_t uiAction;
    uint64_t uiParam;
    uint64_t pvParam;
    uint64_t fWinIni;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SystemParametersInfoW(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
    struct qemu_SystemParametersInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOW);
    call.uiAction = (ULONG_PTR)uiAction;
    call.uiParam = (ULONG_PTR)uiParam;
    call.pvParam = (ULONG_PTR)pvParam;
    call.fWinIni = (ULONG_PTR)fWinIni;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINUSERAPI BOOL WINAPI SystemParametersInfoA(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
    struct qemu_SystemParametersInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOA);
    call.uiAction = (ULONG_PTR)uiAction;
    call.uiParam = (ULONG_PTR)uiParam;
    call.pvParam = (ULONG_PTR)pvParam;
    call.fWinIni = (ULONG_PTR)fWinIni;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SystemParametersInfo(struct qemu_syscall *call)
{
    struct qemu_SystemParametersInfo *c = (struct qemu_SystemParametersInfo *)call;
    INT action;
    WINE_TRACE("\n");

    action = c->uiAction;
#if GUEST_BIT == HOST_BIT
    if (c->super.id == QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOA))
        c->super.iret = SystemParametersInfoA(action, c->uiParam, QEMU_G2H(c->pvParam), c->fWinIni);
    else
        c->super.iret = SystemParametersInfoW(action, c->uiParam, QEMU_G2H(c->pvParam), c->fWinIni);
    return;
#endif

    switch (action)
    {
        /* Everything untested */
        default:
            WINE_FIXME("Unvalidated system parameter %d\n", action);
            /* Drop through */

        /* Parameters which are known to have matching 32 and 64 bit structs. */
        case SPI_GETBEEP:
        case SPI_SETBEEP:
        case SPI_ICONVERTICALSPACING:
        case SPI_GETNONCLIENTMETRICS:
        case SPI_GETMINIMIZEDMETRICS:
        case SPI_SETMINIMIZEDMETRICS:
        case SPI_SETWORKAREA:
        case SPI_GETWORKAREA:
            if (c->super.id == QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOA))
                c->super.iret = SystemParametersInfoA(action, c->uiParam, QEMU_G2H(c->pvParam), c->fWinIni);
            else
                c->super.iret = SystemParametersInfoW(action, c->uiParam, QEMU_G2H(c->pvParam), c->fWinIni);
            break;

        /* Needs conversion */
    }
}

#endif

struct qemu_GetSystemMetrics
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI GetSystemMetrics(INT index)
{
    struct qemu_GetSystemMetrics call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMMETRICS);
    call.index = (ULONG_PTR)index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSystemMetrics(struct qemu_syscall *call)
{
    struct qemu_GetSystemMetrics *c = (struct qemu_GetSystemMetrics *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemMetrics(c->index);
}

#endif

struct qemu_SwapMouseButton
{
    struct qemu_syscall super;
    uint64_t fSwap;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SwapMouseButton(BOOL fSwap)
{
    struct qemu_SwapMouseButton call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SWAPMOUSEBUTTON);
    call.fSwap = (ULONG_PTR)fSwap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SwapMouseButton(struct qemu_syscall *call)
{
    struct qemu_SwapMouseButton *c = (struct qemu_SwapMouseButton *)call;
    WINE_TRACE("\n");
    c->super.iret = SwapMouseButton(c->fSwap);
}

#endif

struct qemu_SetDoubleClickTime
{
    struct qemu_syscall super;
    uint64_t interval;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetDoubleClickTime(UINT interval)
{
    struct qemu_SetDoubleClickTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDOUBLECLICKTIME);
    call.interval = (ULONG_PTR)interval;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetDoubleClickTime(struct qemu_syscall *call)
{
    struct qemu_SetDoubleClickTime *c = (struct qemu_SetDoubleClickTime *)call;
    WINE_TRACE("\n");
    c->super.iret = SetDoubleClickTime(c->interval);
}

#endif

struct qemu_GetDoubleClickTime
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI GetDoubleClickTime(void)
{
    struct qemu_GetDoubleClickTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDOUBLECLICKTIME);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDoubleClickTime(struct qemu_syscall *call)
{
    struct qemu_GetDoubleClickTime *c = (struct qemu_GetDoubleClickTime *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDoubleClickTime();
}

#endif

struct qemu_GetSysColor
{
    struct qemu_syscall super;
    uint64_t nIndex;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI COLORREF WINAPI GetSysColor(INT nIndex)
{
    struct qemu_GetSysColor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSCOLOR);
    call.nIndex = (ULONG_PTR)nIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSysColor(struct qemu_syscall *call)
{
    struct qemu_GetSysColor *c = (struct qemu_GetSysColor *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSysColor(c->nIndex);
}

#endif

struct qemu_SetSysColors
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t colors;
    uint64_t values;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetSysColors(INT count, const INT *colors, const COLORREF *values)
{
    struct qemu_SetSysColors call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSCOLORS);
    call.count = (ULONG_PTR)count;
    call.colors = (ULONG_PTR)colors;
    call.values = (ULONG_PTR)values;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetSysColors(struct qemu_syscall *call)
{
    struct qemu_SetSysColors *c = (struct qemu_SetSysColors *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSysColors(c->count, QEMU_G2H(c->colors), QEMU_G2H(c->values));
}

#endif

struct qemu_SetSysColorsTemp
{
    struct qemu_syscall super;
    uint64_t pPens;
    uint64_t pBrushes;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD_PTR WINAPI SetSysColorsTemp(const COLORREF *pPens, const HBRUSH *pBrushes, DWORD_PTR n)
{
    struct qemu_SetSysColorsTemp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSYSCOLORSTEMP);
    call.pPens = (ULONG_PTR)pPens;
    call.pBrushes = (ULONG_PTR)pBrushes;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetSysColorsTemp to Wine headers? */
extern DWORD_PTR WINAPI SetSysColorsTemp(const COLORREF *pPens, const HBRUSH *pBrushes, DWORD_PTR n);
void qemu_SetSysColorsTemp(struct qemu_syscall *call)
{
    struct qemu_SetSysColorsTemp *c = (struct qemu_SetSysColorsTemp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetSysColorsTemp(QEMU_G2H(c->pPens), QEMU_G2H(c->pBrushes), c->n);
}

#endif

struct qemu_GetSysColorBrush
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HBRUSH WINAPI GetSysColorBrush(INT index)
{
    struct qemu_GetSysColorBrush call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSCOLORBRUSH);
    call.index = (ULONG_PTR)index;

    qemu_syscall(&call.super);

    return (HBRUSH)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetSysColorBrush(struct qemu_syscall *call)
{
    struct qemu_GetSysColorBrush *c = (struct qemu_GetSysColorBrush *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetSysColorBrush(c->index);
}

#endif

struct qemu_ChangeDisplaySettingsA
{
    struct qemu_syscall super;
    uint64_t devmode;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI ChangeDisplaySettingsA(LPDEVMODEA devmode, DWORD flags)
{
    struct qemu_ChangeDisplaySettingsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEDISPLAYSETTINGSA);
    call.devmode = (ULONG_PTR)devmode;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeDisplaySettingsA(struct qemu_syscall *call)
{
    struct qemu_ChangeDisplaySettingsA *c = (struct qemu_ChangeDisplaySettingsA *)call;
    WINE_TRACE("\n");
    c->super.iret = ChangeDisplaySettingsA(QEMU_G2H(c->devmode), c->flags);
}

#endif

struct qemu_ChangeDisplaySettingsW
{
    struct qemu_syscall super;
    uint64_t devmode;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI ChangeDisplaySettingsW(LPDEVMODEW devmode, DWORD flags)
{
    struct qemu_ChangeDisplaySettingsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEDISPLAYSETTINGSW);
    call.devmode = (ULONG_PTR)devmode;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeDisplaySettingsW(struct qemu_syscall *call)
{
    struct qemu_ChangeDisplaySettingsW *c = (struct qemu_ChangeDisplaySettingsW *)call;
    WINE_TRACE("\n");
    c->super.iret = ChangeDisplaySettingsW(QEMU_G2H(c->devmode), c->flags);
}

#endif

struct qemu_ChangeDisplaySettingsExA
{
    struct qemu_syscall super;
    uint64_t devname;
    uint64_t devmode;
    uint64_t hwnd;
    uint64_t flags;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI ChangeDisplaySettingsExA(LPCSTR devname, LPDEVMODEA devmode, HWND hwnd, DWORD flags, LPVOID lparam)
{
    struct qemu_ChangeDisplaySettingsExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEDISPLAYSETTINGSEXA);
    call.devname = (ULONG_PTR)devname;
    call.devmode = (ULONG_PTR)devmode;
    call.hwnd = (ULONG_PTR)hwnd;
    call.flags = (ULONG_PTR)flags;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeDisplaySettingsExA(struct qemu_syscall *call)
{
    struct qemu_ChangeDisplaySettingsExA *c = (struct qemu_ChangeDisplaySettingsExA *)call;
    WINE_TRACE("\n");
    c->super.iret = ChangeDisplaySettingsExA(QEMU_G2H(c->devname), QEMU_G2H(c->devmode), QEMU_G2H(c->hwnd), c->flags, QEMU_G2H(c->lparam));
}

#endif

struct qemu_ChangeDisplaySettingsExW
{
    struct qemu_syscall super;
    uint64_t devname;
    uint64_t devmode;
    uint64_t hwnd;
    uint64_t flags;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI ChangeDisplaySettingsExW(LPCWSTR devname, LPDEVMODEW devmode, HWND hwnd, DWORD flags, LPVOID lparam)
{
    struct qemu_ChangeDisplaySettingsExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHANGEDISPLAYSETTINGSEXW);
    call.devname = (ULONG_PTR)devname;
    call.devmode = (ULONG_PTR)devmode;
    call.hwnd = (ULONG_PTR)hwnd;
    call.flags = (ULONG_PTR)flags;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeDisplaySettingsExW(struct qemu_syscall *call)
{
    struct qemu_ChangeDisplaySettingsExW *c = (struct qemu_ChangeDisplaySettingsExW *)call;
    WINE_TRACE("\n");
    c->super.iret = ChangeDisplaySettingsExW(QEMU_G2H(c->devname), QEMU_G2H(c->devmode), QEMU_G2H(c->hwnd), c->flags, QEMU_G2H(c->lparam));
}

#endif

struct qemu_EnumDisplaySettingsW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t n;
    uint64_t devmode;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDisplaySettingsW(LPCWSTR name, DWORD n, LPDEVMODEW devmode)
{
    struct qemu_EnumDisplaySettingsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYSETTINGSW);
    call.name = (ULONG_PTR)name;
    call.n = n;
    call.devmode = (ULONG_PTR)devmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDisplaySettingsW(struct qemu_syscall *call)
{
    struct qemu_EnumDisplaySettingsW *c = (struct qemu_EnumDisplaySettingsW *)call;
    WINE_TRACE("\n");
    c->super.iret = EnumDisplaySettingsW(QEMU_G2H(c->name), c->n, QEMU_G2H(c->devmode));
}

#endif

struct qemu_EnumDisplaySettingsA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t n;
    uint64_t devmode;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDisplaySettingsA(LPCSTR name,DWORD n,LPDEVMODEA devmode)
{
    struct qemu_EnumDisplaySettingsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYSETTINGSA);
    call.name = (ULONG_PTR)name;
    call.n = (ULONG_PTR)n;
    call.devmode = (ULONG_PTR)devmode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDisplaySettingsA(struct qemu_syscall *call)
{
    struct qemu_EnumDisplaySettingsA *c = (struct qemu_EnumDisplaySettingsA *)call;
    WINE_TRACE("\n");
    c->super.iret = EnumDisplaySettingsA(QEMU_G2H(c->name), c->n, QEMU_G2H(c->devmode));
}

#endif

struct qemu_EnumDisplaySettingsExA
{
    struct qemu_syscall super;
    uint64_t lpszDeviceName;
    uint64_t iModeNum;
    uint64_t lpDevMode;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDisplaySettingsExA(LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode, DWORD dwFlags)
{
    struct qemu_EnumDisplaySettingsExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYSETTINGSEXA);
    call.lpszDeviceName = (ULONG_PTR)lpszDeviceName;
    call.iModeNum = (ULONG_PTR)iModeNum;
    call.lpDevMode = (ULONG_PTR)lpDevMode;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDisplaySettingsExA(struct qemu_syscall *call)
{
    struct qemu_EnumDisplaySettingsExA *c = (struct qemu_EnumDisplaySettingsExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDisplaySettingsExA(QEMU_G2H(c->lpszDeviceName), c->iModeNum, QEMU_G2H(c->lpDevMode), c->dwFlags);
}

#endif

struct qemu_EnumDisplaySettingsExW
{
    struct qemu_syscall super;
    uint64_t lpszDeviceName;
    uint64_t iModeNum;
    uint64_t lpDevMode;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDisplaySettingsExW(LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode, DWORD dwFlags)
{
    struct qemu_EnumDisplaySettingsExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYSETTINGSEXW);
    call.lpszDeviceName = (ULONG_PTR)lpszDeviceName;
    call.iModeNum = (ULONG_PTR)iModeNum;
    call.lpDevMode = (ULONG_PTR)lpDevMode;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDisplaySettingsExW(struct qemu_syscall *call)
{
    struct qemu_EnumDisplaySettingsExW *c = (struct qemu_EnumDisplaySettingsExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDisplaySettingsExW(QEMU_G2H(c->lpszDeviceName), c->iModeNum, QEMU_G2H(c->lpDevMode), c->dwFlags);
}

#endif

struct qemu_SetProcessDPIAware
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetProcessDPIAware(void)
{
    struct qemu_SetProcessDPIAware call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSDPIAWARE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessDPIAware(struct qemu_syscall *call)
{
    struct qemu_SetProcessDPIAware *c = (struct qemu_SetProcessDPIAware *)call;
    WINE_TRACE("\n");
    c->super.iret = SetProcessDPIAware();
}

#endif

struct qemu_IsProcessDPIAware
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsProcessDPIAware(void)
{
    struct qemu_IsProcessDPIAware call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPROCESSDPIAWARE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsProcessDPIAware(struct qemu_syscall *call)
{
    struct qemu_IsProcessDPIAware *c = (struct qemu_IsProcessDPIAware *)call;
    WINE_TRACE("\n");
    c->super.iret = IsProcessDPIAware();
}

#endif

struct qemu_GetAutoRotationState
{
    struct qemu_syscall super;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetAutoRotationState(AR_STATE *state)
{
    struct qemu_GetAutoRotationState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETAUTOROTATIONSTATE);
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAutoRotationState(struct qemu_syscall *call)
{
    struct qemu_GetAutoRotationState *c = (struct qemu_GetAutoRotationState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAutoRotationState(QEMU_G2H(c->state));
}

#endif
struct qemu_DisplayConfigGetDeviceInfo
{
    struct qemu_syscall super;
    uint64_t packet;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI DisplayConfigGetDeviceInfo(DISPLAYCONFIG_DEVICE_INFO_HEADER *packet)
{
    struct qemu_DisplayConfigGetDeviceInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DISPLAYCONFIGGETDEVICEINFO);
    call.packet = (ULONG_PTR)packet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DisplayConfigGetDeviceInfo(struct qemu_syscall *call)
{
    struct qemu_DisplayConfigGetDeviceInfo *c = (struct qemu_DisplayConfigGetDeviceInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DisplayConfigGetDeviceInfo(QEMU_G2H(c->packet));
}

#endif
struct qemu_GetDisplayAutoRotationPreferences
{
    struct qemu_syscall super;
    uint64_t orientation;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDisplayAutoRotationPreferences(ORIENTATION_PREFERENCE *orientation)
{
    struct qemu_GetDisplayAutoRotationPreferences call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISPLAYAUTOROTATIONPREFERENCES);
    call.orientation = (ULONG_PTR)orientation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDisplayAutoRotationPreferences(struct qemu_syscall *call)
{
    struct qemu_GetDisplayAutoRotationPreferences *c = (struct qemu_GetDisplayAutoRotationPreferences *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDisplayAutoRotationPreferences(QEMU_G2H(c->orientation));
}

#endif

struct qemu_AreDpiAwarenessContextsEqual
{
    struct qemu_syscall super;
    uint64_t ctx1;
    uint64_t ctx2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI AreDpiAwarenessContextsEqual(DPI_AWARENESS_CONTEXT ctx1, DPI_AWARENESS_CONTEXT ctx2)
{
    struct qemu_AreDpiAwarenessContextsEqual call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AREDPIAWARENESSCONTEXTSEQUAL);
    call.ctx1 = (ULONG_PTR)ctx1;
    call.ctx2 = (ULONG_PTR)ctx2;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_AreDpiAwarenessContextsEqual(struct qemu_syscall *call)
{
    struct qemu_AreDpiAwarenessContextsEqual *c = (struct qemu_AreDpiAwarenessContextsEqual *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AreDpiAwarenessContextsEqual(QEMU_G2H(c->ctx1), QEMU_G2H(c->ctx2));
}

#endif

struct qemu_GetAwarenessFromDpiAwarenessContext
{
    struct qemu_syscall super;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DPI_AWARENESS WINAPI GetAwarenessFromDpiAwarenessContext(DPI_AWARENESS_CONTEXT context)
{
    struct qemu_GetAwarenessFromDpiAwarenessContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETAWARENESSFROMDPIAWARENESSCONTEXT);
    call.context = (ULONG_PTR)context;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_GetAwarenessFromDpiAwarenessContext(struct qemu_syscall *call)
{
    struct qemu_GetAwarenessFromDpiAwarenessContext *c = (struct qemu_GetAwarenessFromDpiAwarenessContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAwarenessFromDpiAwarenessContext(QEMU_G2H(c->context));
}

#endif

struct qemu_GetDpiForMonitorInternal
{
    struct qemu_syscall super;
    uint64_t monitor;
    uint64_t type;
    uint64_t x;
    uint64_t y;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetDpiForMonitorInternal(HMONITOR monitor, UINT type, UINT *x, UINT *y)
{
    struct qemu_GetDpiForMonitorInternal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDPIFORMONITORINTERNAL);
    call.monitor = (ULONG_PTR)monitor;
    call.type = type;
    call.x = (ULONG_PTR)x;
    call.y = (ULONG_PTR)y;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_GetDpiForMonitorInternal(struct qemu_syscall *call)
{
    struct qemu_GetDpiForMonitorInternal *c = (struct qemu_GetDpiForMonitorInternal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDpiForMonitorInternal(QEMU_G2H(c->monitor), c->type, QEMU_G2H(c->x), QEMU_G2H(c->y));
}

#endif

struct qemu_GetDpiForSystem
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetDpiForSystem(void)
{
    struct qemu_GetDpiForSystem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDPIFORSYSTEM);
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_GetDpiForSystem(struct qemu_syscall *call)
{
    struct qemu_GetDpiForSystem *c = (struct qemu_GetDpiForSystem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDpiForSystem();
}

#endif

struct qemu_GetProcessDpiAwarenessInternal
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t awareness;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetProcessDpiAwarenessInternal(HANDLE process, DPI_AWARENESS *awareness)
{
    struct qemu_GetProcessDpiAwarenessInternal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSDPIAWARENESSINTERNAL);
    call.process = (ULONG_PTR)process;
    call.awareness = (ULONG_PTR)awareness;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_GetProcessDpiAwarenessInternal(struct qemu_syscall *call)
{
    struct qemu_GetProcessDpiAwarenessInternal *c = (struct qemu_GetProcessDpiAwarenessInternal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetProcessDpiAwarenessInternal(QEMU_G2H(c->process), QEMU_G2H(c->awareness));
}

#endif

struct qemu_GetSystemMetricsForDpi
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t dpi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetSystemMetricsForDpi(INT index, UINT dpi)
{
    struct qemu_GetSystemMetricsForDpi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMMETRICSFORDPI);
    call.index = index;
    call.dpi = dpi;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_GetSystemMetricsForDpi(struct qemu_syscall *call)
{
    struct qemu_GetSystemMetricsForDpi *c = (struct qemu_GetSystemMetricsForDpi *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSystemMetricsForDpi(c->index, c->dpi);
}

#endif

struct qemu_GetThreadDpiAwarenessContext
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DPI_AWARENESS_CONTEXT WINAPI GetThreadDpiAwarenessContext(void)
{
    struct qemu_GetThreadDpiAwarenessContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADDPIAWARENESSCONTEXT);
    
    qemu_syscall(&call.super);
    
    return (DPI_AWARENESS_CONTEXT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetThreadDpiAwarenessContext(struct qemu_syscall *call)
{
    struct qemu_GetThreadDpiAwarenessContext *c = (struct qemu_GetThreadDpiAwarenessContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(GetThreadDpiAwarenessContext());
}

#endif

struct qemu_IsValidDpiAwarenessContext
{
    struct qemu_syscall super;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsValidDpiAwarenessContext(DPI_AWARENESS_CONTEXT context)
{
    struct qemu_IsValidDpiAwarenessContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISVALIDDPIAWARENESSCONTEXT);
    call.context = (ULONG_PTR)context;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_IsValidDpiAwarenessContext(struct qemu_syscall *call)
{
    struct qemu_IsValidDpiAwarenessContext *c = (struct qemu_IsValidDpiAwarenessContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsValidDpiAwarenessContext(QEMU_G2H(c->context));
}

#endif

struct qemu_SetThreadDpiAwarenessContext
{
    struct qemu_syscall super;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DPI_AWARENESS_CONTEXT WINAPI SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT context)
{
    struct qemu_SetThreadDpiAwarenessContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADDPIAWARENESSCONTEXT);
    call.context = (ULONG_PTR)context;
    
    qemu_syscall(&call.super);
}

#else

void qemu_SetThreadDpiAwarenessContext(struct qemu_syscall *call)
{
    struct qemu_SetThreadDpiAwarenessContext *c = (struct qemu_SetThreadDpiAwarenessContext *)call;
    WINE_FIXME("Unverified!\n");
    SetThreadDpiAwarenessContext(QEMU_G2H(c->context));
}

#endif

struct qemu_SystemParametersInfoForDpi
{
    struct qemu_syscall super;
    uint64_t action;
    uint64_t val;
    uint64_t ptr;
    uint64_t winini;
    uint64_t dpi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SystemParametersInfoForDpi(UINT action, UINT val, PVOID ptr, UINT winini, UINT dpi)
{
    struct qemu_SystemParametersInfoForDpi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOFORDPI);
    call.action = action;
    call.val = val;
    call.ptr = (ULONG_PTR)ptr;
    call.winini = winini;
    call.dpi = dpi;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_SystemParametersInfoForDpi(struct qemu_syscall *call)
{
    struct qemu_SystemParametersInfoForDpi *c = (struct qemu_SystemParametersInfoForDpi *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemParametersInfoForDpi(c->action, c->val, QEMU_G2H(c->ptr), c->winini, c->dpi);
}

#endif

struct qemu_LogicalToPhysicalPointForPerMonitorDPI
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI LogicalToPhysicalPointForPerMonitorDPI(HWND hwnd, POINT *pt)
{
    struct qemu_LogicalToPhysicalPointForPerMonitorDPI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOGICALTOPHYSICALPOINTFORPERMONITORDPI);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pt = (ULONG_PTR)pt;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_LogicalToPhysicalPointForPerMonitorDPI(struct qemu_syscall *call)
{
    struct qemu_LogicalToPhysicalPointForPerMonitorDPI *c = (struct qemu_LogicalToPhysicalPointForPerMonitorDPI *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LogicalToPhysicalPointForPerMonitorDPI(QEMU_G2H(c->hwnd), QEMU_G2H(c->pt));
}

#endif

struct qemu_PhysicalToLogicalPointForPerMonitorDPI
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PhysicalToLogicalPointForPerMonitorDPI(HWND hwnd, POINT *pt)
{
    struct qemu_PhysicalToLogicalPointForPerMonitorDPI call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PHYSICALTOLOGICALPOINTFORPERMONITORDPI);
    call.hwnd = (ULONG_PTR)hwnd;
    call.pt = (ULONG_PTR)pt;
    
    qemu_syscall(&call.super);
    
    return call.super.iret;
}

#else

void qemu_PhysicalToLogicalPointForPerMonitorDPI(struct qemu_syscall *call)
{
    struct qemu_PhysicalToLogicalPointForPerMonitorDPI *c = (struct qemu_PhysicalToLogicalPointForPerMonitorDPI *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PhysicalToLogicalPointForPerMonitorDPI(QEMU_G2H(c->hwnd), QEMU_G2H(c->pt));
}

#endif

struct qemu_SetProcessDpiAwarenessInternal
{
    struct qemu_syscall super;
    uint64_t awareness;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetProcessDpiAwarenessInternal(DPI_AWARENESS awareness)
{
    struct qemu_SetProcessDpiAwarenessInternal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSDPIAWARENESSINTERNAL);
    call.awareness = awareness;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessDpiAwarenessInternal(struct qemu_syscall *call)
{
    struct qemu_SetProcessDpiAwarenessInternal *c = (struct qemu_SetProcessDpiAwarenessInternal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetProcessDpiAwarenessInternal(c->awareness);
}

#endif
