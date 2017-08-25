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
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_SystemParametersInfoW
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
    struct qemu_SystemParametersInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOW);
    call.uiAction = (uint64_t)uiAction;
    call.uiParam = (uint64_t)uiParam;
    call.pvParam = (uint64_t)pvParam;
    call.fWinIni = (uint64_t)fWinIni;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SystemParametersInfoW(struct qemu_syscall *call)
{
    struct qemu_SystemParametersInfoW *c = (struct qemu_SystemParametersInfoW *)call;
    WINE_TRACE("\n");
    c->super.iret = SystemParametersInfoW(c->uiAction, c->uiParam, QEMU_G2H(c->pvParam), c->fWinIni);
}

#endif

struct qemu_SystemParametersInfoA
{
    struct qemu_syscall super;
    uint64_t uiAction;
    uint64_t uiParam;
    uint64_t pvParam;
    uint64_t fuWinIni;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SystemParametersInfoA(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fuWinIni)
{
    struct qemu_SystemParametersInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMPARAMETERSINFOA);
    call.uiAction = (uint64_t)uiAction;
    call.uiParam = (uint64_t)uiParam;
    call.pvParam = (uint64_t)pvParam;
    call.fuWinIni = (uint64_t)fuWinIni;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SystemParametersInfoA(struct qemu_syscall *call)
{
    struct qemu_SystemParametersInfoA *c = (struct qemu_SystemParametersInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = SystemParametersInfoA(c->uiAction, c->uiParam, QEMU_G2H(c->pvParam), c->fuWinIni);
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
    call.index = (uint64_t)index;

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
    call.fSwap = (uint64_t)fSwap;

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
    call.interval = (uint64_t)interval;

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
    call.nIndex = (uint64_t)nIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetSysColor(struct qemu_syscall *call)
{
    struct qemu_GetSysColor *c = (struct qemu_GetSysColor *)call;
    WINE_FIXME("Unverified!\n");
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
    call.count = (uint64_t)count;
    call.colors = (uint64_t)colors;
    call.values = (uint64_t)values;

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
    call.pPens = (uint64_t)pPens;
    call.pBrushes = (uint64_t)pBrushes;
    call.n = (uint64_t)n;

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
    call.index = (uint64_t)index;

    qemu_syscall(&call.super);

    return (HBRUSH)call.super.iret;
}

#else

void qemu_GetSysColorBrush(struct qemu_syscall *call)
{
    struct qemu_GetSysColorBrush *c = (struct qemu_GetSysColorBrush *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)GetSysColorBrush(c->index);
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
    call.devmode = (uint64_t)devmode;
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
    call.devmode = (uint64_t)devmode;
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
    call.devname = (uint64_t)devname;
    call.devmode = (uint64_t)devmode;
    call.hwnd = (uint64_t)hwnd;
    call.flags = (uint64_t)flags;
    call.lparam = (uint64_t)lparam;

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
    call.devname = (uint64_t)devname;
    call.devmode = (uint64_t)devmode;
    call.hwnd = (uint64_t)hwnd;
    call.flags = (uint64_t)flags;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChangeDisplaySettingsExW(struct qemu_syscall *call)
{
    struct qemu_ChangeDisplaySettingsExW *c = (struct qemu_ChangeDisplaySettingsExW *)call;
    WINE_FIXME("Unverified!\n");
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
    call.name = (uint64_t)name;
    call.n = n;
    call.devmode = (uint64_t)devmode;

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
    call.name = (uint64_t)name;
    call.n = (uint64_t)n;
    call.devmode = (uint64_t)devmode;

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
    call.lpszDeviceName = (uint64_t)lpszDeviceName;
    call.iModeNum = (uint64_t)iModeNum;
    call.lpDevMode = (uint64_t)lpDevMode;
    call.dwFlags = (uint64_t)dwFlags;

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
    call.lpszDeviceName = (uint64_t)lpszDeviceName;
    call.iModeNum = (uint64_t)iModeNum;
    call.lpDevMode = (uint64_t)lpDevMode;
    call.dwFlags = (uint64_t)dwFlags;

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

