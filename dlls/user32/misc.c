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

struct qemu_UserSignalProc
{
    struct qemu_syscall super;
    uint64_t uCode;
    uint64_t dwThreadOrProcessID;
    uint64_t dwFlags;
    uint64_t hModule;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI WORD WINAPI UserSignalProc(UINT uCode, DWORD dwThreadOrProcessID, DWORD dwFlags, void *hModule)
{
    struct qemu_UserSignalProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERSIGNALPROC);
    call.uCode = (uint64_t)uCode;
    call.dwThreadOrProcessID = (uint64_t)dwThreadOrProcessID;
    call.dwFlags = (uint64_t)dwFlags;
    call.hModule = (uint64_t)hModule;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add UserSignalProc to Wine headers? */
extern WORD WINAPI UserSignalProc(UINT uCode, DWORD dwThreadOrProcessID, DWORD dwFlags, void *hModule);
void qemu_UserSignalProc(struct qemu_syscall *call)
{
    struct qemu_UserSignalProc *c = (struct qemu_UserSignalProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserSignalProc(c->uCode, c->dwThreadOrProcessID, c->dwFlags, QEMU_G2H(c->hModule));
}

#endif

struct qemu_SetLastErrorEx
{
    struct qemu_syscall super;
    uint64_t error;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI SetLastErrorEx(DWORD error, DWORD type)
{
    struct qemu_SetLastErrorEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLASTERROREX);
    call.error = (uint64_t)error;
    call.type = (uint64_t)type;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_SetLastErrorEx(struct qemu_syscall *call)
{
    struct qemu_SetLastErrorEx *c = (struct qemu_SetLastErrorEx *)call;
    WINE_FIXME("Unverified!\n");
    SetLastErrorEx(c->error, c->type);
}

#endif

struct qemu_GetAltTabInfoA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t iItem;
    uint64_t pati;
    uint64_t pszItemText;
    uint64_t cchItemText;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetAltTabInfoA(HWND hwnd, int iItem, PALTTABINFO pati, LPSTR pszItemText, UINT cchItemText)
{
    struct qemu_GetAltTabInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETALTTABINFOA);
    call.hwnd = (uint64_t)hwnd;
    call.iItem = (uint64_t)iItem;
    call.pati = (uint64_t)pati;
    call.pszItemText = (uint64_t)pszItemText;
    call.cchItemText = (uint64_t)cchItemText;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAltTabInfoA(struct qemu_syscall *call)
{
    struct qemu_GetAltTabInfoA *c = (struct qemu_GetAltTabInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAltTabInfoA(QEMU_G2H(c->hwnd), c->iItem, QEMU_G2H(c->pati), QEMU_G2H(c->pszItemText), c->cchItemText);
}

#endif

struct qemu_GetAltTabInfoW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t iItem;
    uint64_t pati;
    uint64_t pszItemText;
    uint64_t cchItemText;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetAltTabInfoW(HWND hwnd, int iItem, PALTTABINFO pati, LPWSTR pszItemText, UINT cchItemText)
{
    struct qemu_GetAltTabInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETALTTABINFOW);
    call.hwnd = (uint64_t)hwnd;
    call.iItem = (uint64_t)iItem;
    call.pati = (uint64_t)pati;
    call.pszItemText = (uint64_t)pszItemText;
    call.cchItemText = (uint64_t)cchItemText;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAltTabInfoW(struct qemu_syscall *call)
{
    struct qemu_GetAltTabInfoW *c = (struct qemu_GetAltTabInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAltTabInfoW(QEMU_G2H(c->hwnd), c->iItem, QEMU_G2H(c->pati), QEMU_G2H(c->pszItemText), c->cchItemText);
}

#endif

struct qemu_SetDebugErrorLevel
{
    struct qemu_syscall super;
    uint64_t dwLevel;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI VOID WINAPI SetDebugErrorLevel(DWORD dwLevel)
{
    struct qemu_SetDebugErrorLevel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETDEBUGERRORLEVEL);
    call.dwLevel = (uint64_t)dwLevel;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_SetDebugErrorLevel(struct qemu_syscall *call)
{
    struct qemu_SetDebugErrorLevel *c = (struct qemu_SetDebugErrorLevel *)call;
    WINE_FIXME("Unverified!\n");
    SetDebugErrorLevel(c->dwLevel);
}

#endif

struct qemu_SetWindowStationUser
{
    struct qemu_syscall super;
    uint64_t x1;
    uint64_t x2;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI SetWindowStationUser(DWORD x1,DWORD x2)
{
    struct qemu_SetWindowStationUser call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSTATIONUSER);
    call.x1 = (uint64_t)x1;
    call.x2 = (uint64_t)x2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetWindowStationUser to Wine headers? */
extern DWORD WINAPI SetWindowStationUser(DWORD x1,DWORD x2);
void qemu_SetWindowStationUser(struct qemu_syscall *call)
{
    struct qemu_SetWindowStationUser *c = (struct qemu_SetWindowStationUser *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetWindowStationUser(c->x1, c->x2);
}

#endif

struct qemu_RegisterLogonProcess
{
    struct qemu_syscall super;
    uint64_t hprocess;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI RegisterLogonProcess(HANDLE hprocess,BOOL x)
{
    struct qemu_RegisterLogonProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERLOGONPROCESS);
    call.hprocess = (uint64_t)hprocess;
    call.x = (uint64_t)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterLogonProcess to Wine headers? */
extern DWORD WINAPI RegisterLogonProcess(HANDLE hprocess,BOOL x);
void qemu_RegisterLogonProcess(struct qemu_syscall *call)
{
    struct qemu_RegisterLogonProcess *c = (struct qemu_RegisterLogonProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterLogonProcess(QEMU_G2H(c->hprocess), c->x);
}

#endif

struct qemu_SetLogonNotifyWindow
{
    struct qemu_syscall super;
    uint64_t hwinsta;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI SetLogonNotifyWindow(HWINSTA hwinsta,HWND hwnd)
{
    struct qemu_SetLogonNotifyWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETLOGONNOTIFYWINDOW);
    call.hwinsta = (uint64_t)hwinsta;
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetLogonNotifyWindow to Wine headers? */
extern DWORD WINAPI SetLogonNotifyWindow(HWINSTA hwinsta,HWND hwnd);
void qemu_SetLogonNotifyWindow(struct qemu_syscall *call)
{
    struct qemu_SetLogonNotifyWindow *c = (struct qemu_SetLogonNotifyWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetLogonNotifyWindow(QEMU_G2H(c->hwinsta), QEMU_G2H(c->hwnd));
}

#endif

struct qemu_EnumDisplayDevicesA
{
    struct qemu_syscall super;
    uint64_t lpDevice;
    uint64_t i;
    uint64_t lpDispDev;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDisplayDevicesA(LPCSTR lpDevice, DWORD i, LPDISPLAY_DEVICEA lpDispDev, DWORD dwFlags)
{
    struct qemu_EnumDisplayDevicesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYDEVICESA);
    call.lpDevice = (uint64_t)lpDevice;
    call.i = (uint64_t)i;
    call.lpDispDev = (uint64_t)lpDispDev;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDisplayDevicesA(struct qemu_syscall *call)
{
    struct qemu_EnumDisplayDevicesA *c = (struct qemu_EnumDisplayDevicesA *)call;
    WINE_TRACE("\n");
    c->super.iret = EnumDisplayDevicesA(QEMU_G2H(c->lpDevice), c->i, QEMU_G2H(c->lpDispDev), c->dwFlags);
}

#endif

struct qemu_EnumDisplayDevicesW
{
    struct qemu_syscall super;
    uint64_t lpDevice;
    uint64_t i;
    uint64_t lpDisplayDevice;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI EnumDisplayDevicesW(LPCWSTR lpDevice, DWORD i, LPDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags)
{
    struct qemu_EnumDisplayDevicesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYDEVICESW);
    call.lpDevice = (uint64_t)lpDevice;
    call.i = (uint64_t)i;
    call.lpDisplayDevice = (uint64_t)lpDisplayDevice;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumDisplayDevicesW(struct qemu_syscall *call)
{
    struct qemu_EnumDisplayDevicesW *c = (struct qemu_EnumDisplayDevicesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumDisplayDevicesW(QEMU_G2H(c->lpDevice), c->i, QEMU_G2H(c->lpDisplayDevice), c->dwFlags);
}

#endif

struct qemu_MonitorFromRect
{
    struct qemu_syscall super;
    uint64_t lprc;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMONITOR WINAPI MonitorFromRect(LPCRECT lprc,DWORD dwFlags)
{
    struct qemu_MonitorFromRect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MONITORFROMRECT);
    call.lprc = (uint64_t)lprc;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return (HMONITOR)call.super.iret;
}

#else

void qemu_MonitorFromRect(struct qemu_syscall *call)
{
    struct qemu_MonitorFromRect *c = (struct qemu_MonitorFromRect *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)MonitorFromRect(QEMU_G2H(c->lprc), c->dwFlags);
}

#endif

struct qemu_MonitorFromPoint
{
    struct qemu_syscall super;
    uint64_t ptX, ptY;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMONITOR WINAPI MonitorFromPoint(POINT pt, DWORD flags)
{
    struct qemu_MonitorFromPoint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MONITORFROMPOINT);
    call.ptX = pt.x;
    call.ptY = pt.y;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HMONITOR)call.super.iret;
}

#else

void qemu_MonitorFromPoint(struct qemu_syscall *call)
{
    struct qemu_MonitorFromPoint *c = (struct qemu_MonitorFromPoint *)call;
    POINT pt;

    WINE_TRACE("\n");
    pt.x = c->ptX;
    pt.y = c->ptY;
    c->super.iret = (uint64_t)MonitorFromPoint(pt, c->flags);
}

#endif

struct qemu_MonitorFromWindow
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HMONITOR WINAPI MonitorFromWindow(HWND hWnd, DWORD dwFlags)
{
    struct qemu_MonitorFromWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MONITORFROMWINDOW);
    call.hWnd = (uint64_t)hWnd;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return (HMONITOR)call.super.iret;
}

#else

void qemu_MonitorFromWindow(struct qemu_syscall *call)
{
    struct qemu_MonitorFromWindow *c = (struct qemu_MonitorFromWindow *)call;
    WINE_TRACE("\n");
    c->super.iret = (uint64_t)MonitorFromWindow(QEMU_G2H(c->hWnd), c->dwFlags);
}

#endif

struct qemu_GetMonitorInfoA
{
    struct qemu_syscall super;
    uint64_t hMonitor;
    uint64_t lpMonitorInfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMonitorInfoA(HMONITOR hMonitor, LPMONITORINFO lpMonitorInfo)
{
    struct qemu_GetMonitorInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMONITORINFOA);
    call.hMonitor = (uint64_t)hMonitor;
    call.lpMonitorInfo = (uint64_t)lpMonitorInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMonitorInfoA(struct qemu_syscall *call)
{
    struct qemu_GetMonitorInfoA *c = (struct qemu_GetMonitorInfoA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMonitorInfoA(QEMU_G2H(c->hMonitor), QEMU_G2H(c->lpMonitorInfo));
}

#endif

struct qemu_GetMonitorInfoW
{
    struct qemu_syscall super;
    uint64_t hMonitor;
    uint64_t lpMonitorInfo;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetMonitorInfoW(HMONITOR hMonitor, LPMONITORINFO lpMonitorInfo)
{
    struct qemu_GetMonitorInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMONITORINFOW);
    call.hMonitor = (uint64_t)hMonitor;
    call.lpMonitorInfo = (uint64_t)lpMonitorInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMonitorInfoW(struct qemu_syscall *call)
{
    struct qemu_GetMonitorInfoW *c = (struct qemu_GetMonitorInfoW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetMonitorInfoW(QEMU_G2H(c->hMonitor), QEMU_G2H(c->lpMonitorInfo));
}

#endif

struct qemu_EnumDisplayMonitors
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t lprcClip;
    uint64_t lpfnEnum;
    uint64_t dwData;
    uint64_t wrapper;
};

struct qemu_EnumDisplayMonitors_cb
{
    uint64_t func, param;
    uint64_t monitor, dc, rect;
};

#ifdef QEMU_DLL_GUEST

static uint64_t EnumDisplayMonitors_cb(struct qemu_EnumDisplayMonitors_cb *call)
{
    MONITORENUMPROC func = (MONITORENUMPROC)call->func;
    return func((HMONITOR)call->monitor, (HDC)call->dc, (RECT *)call->rect, call->param);
}

WINUSERAPI WINBOOL WINAPI EnumDisplayMonitors(HDC hdc,LPCRECT lprcClip,MONITORENUMPROC lpfnEnum,LPARAM dwData)
{
    struct qemu_EnumDisplayMonitors call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDISPLAYMONITORS);
    call.hdc = (uint64_t)hdc;
    call.lprcClip = (uint64_t)lprcClip;
    call.lpfnEnum = (uint64_t)lpfnEnum;
    call.dwData = (uint64_t)dwData;
    call.wrapper = (uint64_t)EnumDisplayMonitors_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_EnumDisplayMonitors_host_data
{
    uint64_t wrapper, guest_func, guest_param;
};

static BOOL CALLBACK qemu_EnumDisplayMonitors_host_cb(HMONITOR monitor, HDC dc, RECT *rect, LPARAM param)
{
    struct qemu_EnumDisplayMonitors_host_data *data = (struct qemu_EnumDisplayMonitors_host_data *)param;
    BOOL ret;
    struct qemu_EnumDisplayMonitors_cb call;

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %p, 0x%lx).\n", data->guest_func, monitor, dc, rect, data->guest_param);
    call.func = data->guest_func;
    call.monitor = QEMU_H2G(monitor);
    call.dc = QEMU_H2G(dc);
    call.rect = QEMU_H2G(rect);
    call.param = data->guest_param;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumDisplayMonitors(struct qemu_syscall *call)
{
    struct qemu_EnumDisplayMonitors *c = (struct qemu_EnumDisplayMonitors *)call;
    struct qemu_EnumDisplayMonitors_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->lpfnEnum;
    data.guest_param = c->dwData;

    c->super.iret = EnumDisplayMonitors(QEMU_G2H(c->hdc), QEMU_G2H(c->lprcClip),
            c->lpfnEnum ? qemu_EnumDisplayMonitors_host_cb : NULL, (LPARAM)&data);
}

#endif

struct qemu_QueryDisplayConfig
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t numpathelements;
    uint64_t pathinfo;
    uint64_t numinfoelements;
    uint64_t modeinfo;
    uint64_t topologyid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI QueryDisplayConfig(UINT32 flags, UINT32 *numpathelements, DISPLAYCONFIG_PATH_INFO *pathinfo, UINT32 *numinfoelements, DISPLAYCONFIG_MODE_INFO *modeinfo, DISPLAYCONFIG_TOPOLOGY_ID *topologyid)
{
    struct qemu_QueryDisplayConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYDISPLAYCONFIG);
    call.flags = (uint64_t)flags;
    call.numpathelements = (uint64_t)numpathelements;
    call.pathinfo = (uint64_t)pathinfo;
    call.numinfoelements = (uint64_t)numinfoelements;
    call.modeinfo = (uint64_t)modeinfo;
    call.topologyid = (uint64_t)topologyid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add QueryDisplayConfig to Wine headers? */
extern LONG WINAPI QueryDisplayConfig(UINT32 flags, UINT32 *numpathelements, void *pathinfo, UINT32 *numinfoelements, void *modeinfo, void *topologyid);
void qemu_QueryDisplayConfig(struct qemu_syscall *call)
{
    struct qemu_QueryDisplayConfig *c = (struct qemu_QueryDisplayConfig *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryDisplayConfig(c->flags, QEMU_G2H(c->numpathelements), QEMU_G2H(c->pathinfo), QEMU_G2H(c->numinfoelements), QEMU_G2H(c->modeinfo), QEMU_G2H(c->topologyid));
}

#endif

struct qemu_RegisterSystemThread
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI RegisterSystemThread(DWORD flags, DWORD reserved)
{
    struct qemu_RegisterSystemThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSYSTEMTHREAD);
    call.flags = (uint64_t)flags;
    call.reserved = (uint64_t)reserved;

    qemu_syscall(&call.super);

    return;
}

#else

/* TODO: Add RegisterSystemThread to Wine headers? */
extern void WINAPI RegisterSystemThread(DWORD flags, DWORD reserved);
void qemu_RegisterSystemThread(struct qemu_syscall *call)
{
    struct qemu_RegisterSystemThread *c = (struct qemu_RegisterSystemThread *)call;
    WINE_FIXME("Unverified!\n");
    RegisterSystemThread(c->flags, c->reserved);
}

#endif

struct qemu_RegisterShellHookWindow
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI RegisterShellHookWindow(HWND hWnd)
{
    struct qemu_RegisterShellHookWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERSHELLHOOKWINDOW);
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterShellHookWindow to Wine headers? */
extern BOOL WINAPI RegisterShellHookWindow(HWND hWnd);
void qemu_RegisterShellHookWindow(struct qemu_syscall *call)
{
    struct qemu_RegisterShellHookWindow *c = (struct qemu_RegisterShellHookWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterShellHookWindow(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_DeregisterShellHookWindow
{
    struct qemu_syscall super;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI DeregisterShellHookWindow(HWND hWnd)
{
    struct qemu_DeregisterShellHookWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEREGISTERSHELLHOOKWINDOW);
    call.hWnd = (uint64_t)hWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add DeregisterShellHookWindow to Wine headers? */
extern BOOL WINAPI DeregisterShellHookWindow(HWND hWnd);
void qemu_DeregisterShellHookWindow(struct qemu_syscall *call)
{
    struct qemu_DeregisterShellHookWindow *c = (struct qemu_DeregisterShellHookWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeregisterShellHookWindow(QEMU_G2H(c->hWnd));
}

#endif

struct qemu_RegisterTasklist
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI RegisterTasklist (DWORD x)
{
    struct qemu_RegisterTasklist call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERTASKLIST);
    call.x = (uint64_t)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RegisterTasklist to Wine headers? */
extern DWORD WINAPI RegisterTasklist (DWORD x);
void qemu_RegisterTasklist(struct qemu_syscall *call)
{
    struct qemu_RegisterTasklist *c = (struct qemu_RegisterTasklist *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RegisterTasklist(c->x);
}

#endif

struct qemu_RegisterDeviceNotificationA
{
    struct qemu_syscall super;
    uint64_t hnd;
    uint64_t notifyfilter;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDEVNOTIFY WINAPI RegisterDeviceNotificationA(HANDLE hnd, LPVOID notifyfilter, DWORD flags)
{
    struct qemu_RegisterDeviceNotificationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERDEVICENOTIFICATIONA);
    call.hnd = (uint64_t)hnd;
    call.notifyfilter = (uint64_t)notifyfilter;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HDEVNOTIFY)call.super.iret;
}

#else

void qemu_RegisterDeviceNotificationA(struct qemu_syscall *call)
{
    struct qemu_RegisterDeviceNotificationA *c = (struct qemu_RegisterDeviceNotificationA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RegisterDeviceNotificationA(QEMU_G2H(c->hnd), QEMU_G2H(c->notifyfilter), c->flags);
}

#endif

struct qemu_RegisterDeviceNotificationW
{
    struct qemu_syscall super;
    uint64_t hRecipient;
    uint64_t pNotificationFilter;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDEVNOTIFY WINAPI RegisterDeviceNotificationW(HANDLE hRecipient, LPVOID pNotificationFilter, DWORD dwFlags)
{
    struct qemu_RegisterDeviceNotificationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERDEVICENOTIFICATIONW);
    call.hRecipient = (uint64_t)hRecipient;
    call.pNotificationFilter = (uint64_t)pNotificationFilter;
    call.dwFlags = (uint64_t)dwFlags;

    qemu_syscall(&call.super);

    return (HDEVNOTIFY)call.super.iret;
}

#else

void qemu_RegisterDeviceNotificationW(struct qemu_syscall *call)
{
    struct qemu_RegisterDeviceNotificationW *c = (struct qemu_RegisterDeviceNotificationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RegisterDeviceNotificationW(QEMU_G2H(c->hRecipient), QEMU_G2H(c->pNotificationFilter), c->dwFlags);
}

#endif

struct qemu_UnregisterDeviceNotification
{
    struct qemu_syscall super;
    uint64_t hnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnregisterDeviceNotification(HDEVNOTIFY hnd)
{
    struct qemu_UnregisterDeviceNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERDEVICENOTIFICATION);
    call.hnd = (uint64_t)hnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterDeviceNotification(struct qemu_syscall *call)
{
    struct qemu_UnregisterDeviceNotification *c = (struct qemu_UnregisterDeviceNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnregisterDeviceNotification(QEMU_G2H(c->hnd));
}

#endif

struct qemu_GetAppCompatFlags
{
    struct qemu_syscall super;
    uint64_t hTask;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetAppCompatFlags(HTASK hTask)
{
    struct qemu_GetAppCompatFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETAPPCOMPATFLAGS);
    call.hTask = (uint64_t)hTask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAppCompatFlags(struct qemu_syscall *call)
{
    struct qemu_GetAppCompatFlags *c = (struct qemu_GetAppCompatFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAppCompatFlags(QEMU_G2H(c->hTask));
}

#endif

struct qemu_GetAppCompatFlags2
{
    struct qemu_syscall super;
    uint64_t hTask;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI DWORD WINAPI GetAppCompatFlags2(HTASK hTask)
{
    struct qemu_GetAppCompatFlags2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETAPPCOMPATFLAGS2);
    call.hTask = (uint64_t)hTask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GetAppCompatFlags2 to Wine headers? */
extern DWORD WINAPI GetAppCompatFlags2(HTASK hTask);
void qemu_GetAppCompatFlags2(struct qemu_syscall *call)
{
    struct qemu_GetAppCompatFlags2 *c = (struct qemu_GetAppCompatFlags2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAppCompatFlags2(QEMU_G2H(c->hTask));
}

#endif

struct qemu_AlignRects
{
    struct qemu_syscall super;
    uint64_t rect;
    uint64_t b;
    uint64_t c;
    uint64_t d;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI AlignRects(LPRECT rect, DWORD b, DWORD c, DWORD d)
{
    struct qemu_AlignRects call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ALIGNRECTS);
    call.rect = (uint64_t)rect;
    call.b = (uint64_t)b;
    call.c = (uint64_t)c;
    call.d = (uint64_t)d;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add AlignRects to Wine headers? */
extern BOOL WINAPI AlignRects(LPRECT rect, DWORD b, DWORD c, DWORD d);
void qemu_AlignRects(struct qemu_syscall *call)
{
    struct qemu_AlignRects *c = (struct qemu_AlignRects *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AlignRects(QEMU_G2H(c->rect), c->b, c->c, c->d);
}

#endif

struct qemu_LoadLocalFonts
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI VOID WINAPI LoadLocalFonts(VOID)
{
    struct qemu_LoadLocalFonts call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADLOCALFONTS);

    qemu_syscall(&call.super);

    return;
}

#else

/* TODO: Add LoadLocalFonts to Wine headers? */
extern VOID WINAPI LoadLocalFonts(VOID);
void qemu_LoadLocalFonts(struct qemu_syscall *call)
{
    struct qemu_LoadLocalFonts *c = (struct qemu_LoadLocalFonts *)call;
    WINE_FIXME("Unverified!\n");
    LoadLocalFonts();
}

#endif

struct qemu_User32InitializeImmEntryTable
{
    struct qemu_syscall super;
    uint64_t magic;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI User32InitializeImmEntryTable(DWORD magic)
{
    struct qemu_User32InitializeImmEntryTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USER32INITIALIZEIMMENTRYTABLE);
    call.magic = (uint64_t)magic;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add User32InitializeImmEntryTable to Wine headers? */
extern BOOL WINAPI User32InitializeImmEntryTable(DWORD magic);
void qemu_User32InitializeImmEntryTable(struct qemu_syscall *call)
{
    struct qemu_User32InitializeImmEntryTable *c = (struct qemu_User32InitializeImmEntryTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = User32InitializeImmEntryTable(c->magic);
}

#endif

struct qemu_WINNLSGetIMEHotkey
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI WINNLSGetIMEHotkey(HWND hwnd)
{
    struct qemu_WINNLSGetIMEHotkey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINNLSGETIMEHOTKEY);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WINNLSGetIMEHotkey to Wine headers? */
extern UINT WINAPI WINNLSGetIMEHotkey(HWND hwnd);
void qemu_WINNLSGetIMEHotkey(struct qemu_syscall *call)
{
    struct qemu_WINNLSGetIMEHotkey *c = (struct qemu_WINNLSGetIMEHotkey *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WINNLSGetIMEHotkey(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_WINNLSEnableIME
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI WINNLSEnableIME(HWND hwnd, BOOL enable)
{
    struct qemu_WINNLSEnableIME call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINNLSENABLEIME);
    call.hwnd = (uint64_t)hwnd;
    call.enable = (uint64_t)enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WINNLSEnableIME to Wine headers? */
extern BOOL WINAPI WINNLSEnableIME(HWND hwnd, BOOL enable);
void qemu_WINNLSEnableIME(struct qemu_syscall *call)
{
    struct qemu_WINNLSEnableIME *c = (struct qemu_WINNLSEnableIME *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WINNLSEnableIME(QEMU_G2H(c->hwnd), c->enable);
}

#endif

struct qemu_WINNLSGetEnableStatus
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI WINNLSGetEnableStatus(HWND hwnd)
{
    struct qemu_WINNLSGetEnableStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WINNLSGETENABLESTATUS);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WINNLSGetEnableStatus to Wine headers? */
extern BOOL WINAPI WINNLSGetEnableStatus(HWND hwnd);
void qemu_WINNLSGetEnableStatus(struct qemu_syscall *call)
{
    struct qemu_WINNLSGetEnableStatus *c = (struct qemu_WINNLSGetEnableStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WINNLSGetEnableStatus(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_SendIMEMessageExA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendIMEMessageExA(HWND hwnd, LPARAM lparam)
{
    struct qemu_SendIMEMessageExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDIMEMESSAGEEXA);
    call.hwnd = (uint64_t)hwnd;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SendIMEMessageExA to Wine headers? */
extern LRESULT WINAPI SendIMEMessageExA(HWND hwnd, LPARAM lparam);
void qemu_SendIMEMessageExA(struct qemu_syscall *call)
{
    struct qemu_SendIMEMessageExA *c = (struct qemu_SendIMEMessageExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendIMEMessageExA(QEMU_G2H(c->hwnd), c->lparam);
}

#endif

struct qemu_SendIMEMessageExW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI SendIMEMessageExW(HWND hwnd, LPARAM lparam)
{
    struct qemu_SendIMEMessageExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SENDIMEMESSAGEEXW);
    call.hwnd = (uint64_t)hwnd;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SendIMEMessageExW to Wine headers? */
extern LRESULT WINAPI SendIMEMessageExW(HWND hwnd, LPARAM lparam);
void qemu_SendIMEMessageExW(struct qemu_syscall *call)
{
    struct qemu_SendIMEMessageExW *c = (struct qemu_SendIMEMessageExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SendIMEMessageExW(QEMU_G2H(c->hwnd), c->lparam);
}

#endif

struct qemu_DisableProcessWindowsGhosting
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI VOID WINAPI DisableProcessWindowsGhosting(VOID)
{
    struct qemu_DisableProcessWindowsGhosting call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DISABLEPROCESSWINDOWSGHOSTING);

    qemu_syscall(&call.super);

    return;
}

#else

/* TODO: Add DisableProcessWindowsGhosting to Wine headers? */
extern VOID WINAPI DisableProcessWindowsGhosting(VOID);
void qemu_DisableProcessWindowsGhosting(struct qemu_syscall *call)
{
    struct qemu_DisableProcessWindowsGhosting *c = (struct qemu_DisableProcessWindowsGhosting *)call;
    WINE_FIXME("Unverified!\n");
    DisableProcessWindowsGhosting();
}

#endif

struct qemu_UserHandleGrantAccess
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t job;
    uint64_t grant;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UserHandleGrantAccess(HANDLE handle, HANDLE job, BOOL grant)
{
    struct qemu_UserHandleGrantAccess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_USERHANDLEGRANTACCESS);
    call.handle = (uint64_t)handle;
    call.job = (uint64_t)job;
    call.grant = (uint64_t)grant;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UserHandleGrantAccess(struct qemu_syscall *call)
{
    struct qemu_UserHandleGrantAccess *c = (struct qemu_UserHandleGrantAccess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UserHandleGrantAccess(QEMU_G2H(c->handle), QEMU_G2H(c->job), c->grant);
}

#endif

struct qemu_RegisterPowerSettingNotification
{
    struct qemu_syscall super;
    uint64_t recipient;
    uint64_t guid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HPOWERNOTIFY WINAPI RegisterPowerSettingNotification(HANDLE recipient, const GUID *guid, DWORD flags)
{
    struct qemu_RegisterPowerSettingNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGISTERPOWERSETTINGNOTIFICATION);
    call.recipient = (uint64_t)recipient;
    call.guid = (uint64_t)guid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HPOWERNOTIFY)call.super.iret;
}

#else

void qemu_RegisterPowerSettingNotification(struct qemu_syscall *call)
{
    struct qemu_RegisterPowerSettingNotification *c = (struct qemu_RegisterPowerSettingNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RegisterPowerSettingNotification(QEMU_G2H(c->recipient), QEMU_G2H(c->guid), c->flags);
}

#endif

struct qemu_UnregisterPowerSettingNotification
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnregisterPowerSettingNotification(HPOWERNOTIFY handle)
{
    struct qemu_UnregisterPowerSettingNotification call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNREGISTERPOWERSETTINGNOTIFICATION);
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnregisterPowerSettingNotification(struct qemu_syscall *call)
{
    struct qemu_UnregisterPowerSettingNotification *c = (struct qemu_UnregisterPowerSettingNotification *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnregisterPowerSettingNotification(QEMU_G2H(c->handle));
}

#endif

struct qemu_GetGestureConfig
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t reserved;
    uint64_t flags;
    uint64_t count;
    uint64_t config;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetGestureConfig(HWND hwnd, DWORD reserved, DWORD flags, UINT *count, GESTURECONFIG *config, UINT size)
{
    struct qemu_GetGestureConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETGESTURECONFIG);
    call.hwnd = (uint64_t)hwnd;
    call.reserved = (uint64_t)reserved;
    call.flags = (uint64_t)flags;
    call.count = (uint64_t)count;
    call.config = (uint64_t)config;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetGestureConfig(struct qemu_syscall *call)
{
    struct qemu_GetGestureConfig *c = (struct qemu_GetGestureConfig *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetGestureConfig(QEMU_G2H(c->hwnd), c->reserved, c->flags, QEMU_G2H(c->count), QEMU_G2H(c->config), c->size);
}

#endif

struct qemu_SetGestureConfig
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t reserved;
    uint64_t id;
    uint64_t config;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetGestureConfig(HWND hwnd, DWORD reserved, UINT id, PGESTURECONFIG config, UINT size)
{
    struct qemu_SetGestureConfig call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETGESTURECONFIG);
    call.hwnd = (uint64_t)hwnd;
    call.reserved = (uint64_t)reserved;
    call.id = (uint64_t)id;
    call.config = (uint64_t)config;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetGestureConfig(struct qemu_syscall *call)
{
    struct qemu_SetGestureConfig *c = (struct qemu_SetGestureConfig *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetGestureConfig(QEMU_G2H(c->hwnd), c->reserved, c->id, QEMU_G2H(c->config), c->size);
}

#endif

struct qemu_IsTouchWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsTouchWindow(HWND hwnd, PULONG flags)
{
    struct qemu_IsTouchWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTOUCHWINDOW);
    call.hwnd = (uint64_t)hwnd;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsTouchWindow(struct qemu_syscall *call)
{
    struct qemu_IsTouchWindow *c = (struct qemu_IsTouchWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsTouchWindow(QEMU_G2H(c->hwnd), QEMU_G2H(c->flags));
}

#endif

struct qemu_IsWindowRedirectedForPrint
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsWindowRedirectedForPrint(HWND hwnd)
{
    struct qemu_IsWindowRedirectedForPrint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWINDOWREDIRECTEDFORPRINT);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsWindowRedirectedForPrint to Wine headers? */
extern BOOL WINAPI IsWindowRedirectedForPrint(HWND hwnd);
void qemu_IsWindowRedirectedForPrint(struct qemu_syscall *call)
{
    struct qemu_IsWindowRedirectedForPrint *c = (struct qemu_IsWindowRedirectedForPrint *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsWindowRedirectedForPrint(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetDisplayConfigBufferSizes
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t num_path_info;
    uint64_t num_mode_info;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LONG WINAPI GetDisplayConfigBufferSizes(UINT32 flags, UINT32 *num_path_info, UINT32 *num_mode_info)
{
    struct qemu_GetDisplayConfigBufferSizes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDISPLAYCONFIGBUFFERSIZES);
    call.flags = (uint64_t)flags;
    call.num_path_info = (uint64_t)num_path_info;
    call.num_mode_info = (uint64_t)num_mode_info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDisplayConfigBufferSizes(struct qemu_syscall *call)
{
    struct qemu_GetDisplayConfigBufferSizes *c = (struct qemu_GetDisplayConfigBufferSizes *)call;
    WINE_TRACE("\n");
    c->super.iret = GetDisplayConfigBufferSizes(c->flags, QEMU_G2H(c->num_path_info), QEMU_G2H(c->num_mode_info));
}

#endif

