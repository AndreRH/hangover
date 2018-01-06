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

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_CreateWindowStationA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t reserved;
    uint64_t access;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWINSTA WINAPI CreateWindowStationA(LPCSTR name, DWORD reserved, ACCESS_MASK access, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateWindowStationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWINDOWSTATIONA);
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HWINSTA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWindowStationA(struct qemu_syscall *call)
{
    struct qemu_CreateWindowStationA *c = (struct qemu_CreateWindowStationA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateWindowStationA(QEMU_G2H(c->name), c->reserved, c->access, QEMU_G2H(c->sa));
}

#endif

struct qemu_CreateWindowStationW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t reserved;
    uint64_t access;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWINSTA WINAPI CreateWindowStationW(LPCWSTR name, DWORD reserved, ACCESS_MASK access, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateWindowStationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEWINDOWSTATIONW);
    call.name = (ULONG_PTR)name;
    call.reserved = (ULONG_PTR)reserved;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HWINSTA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateWindowStationW(struct qemu_syscall *call)
{
    struct qemu_CreateWindowStationW *c = (struct qemu_CreateWindowStationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateWindowStationW(QEMU_G2H(c->name), c->reserved, c->access, QEMU_G2H(c->sa));
}

#endif

struct qemu_OpenWindowStationA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t inherit;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWINSTA WINAPI OpenWindowStationA(LPCSTR name, BOOL inherit, ACCESS_MASK access)
{
    struct qemu_OpenWindowStationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENWINDOWSTATIONA);
    call.name = (ULONG_PTR)name;
    call.inherit = (ULONG_PTR)inherit;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HWINSTA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenWindowStationA(struct qemu_syscall *call)
{
    struct qemu_OpenWindowStationA *c = (struct qemu_OpenWindowStationA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenWindowStationA(QEMU_G2H(c->name), c->inherit, c->access);
}

#endif

struct qemu_OpenWindowStationW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t inherit;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWINSTA WINAPI OpenWindowStationW(LPCWSTR name, BOOL inherit, ACCESS_MASK access)
{
    struct qemu_OpenWindowStationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENWINDOWSTATIONW);
    call.name = (ULONG_PTR)name;
    call.inherit = (ULONG_PTR)inherit;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HWINSTA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenWindowStationW(struct qemu_syscall *call)
{
    struct qemu_OpenWindowStationW *c = (struct qemu_OpenWindowStationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenWindowStationW(QEMU_G2H(c->name), c->inherit, c->access);
}

#endif

struct qemu_CloseWindowStation
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CloseWindowStation(HWINSTA handle)
{
    struct qemu_CloseWindowStation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEWINDOWSTATION);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseWindowStation(struct qemu_syscall *call)
{
    struct qemu_CloseWindowStation *c = (struct qemu_CloseWindowStation *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseWindowStation(QEMU_G2H(c->handle));
}

#endif

struct qemu_GetProcessWindowStation
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWINSTA WINAPI GetProcessWindowStation(void)
{
    struct qemu_GetProcessWindowStation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROCESSWINDOWSTATION);

    qemu_syscall(&call.super);

    return (HWINSTA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetProcessWindowStation(struct qemu_syscall *call)
{
    struct qemu_GetProcessWindowStation *c = (struct qemu_GetProcessWindowStation *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetProcessWindowStation();
}

#endif

struct qemu_SetProcessWindowStation
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetProcessWindowStation(HWINSTA handle)
{
    struct qemu_SetProcessWindowStation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROCESSWINDOWSTATION);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetProcessWindowStation(struct qemu_syscall *call)
{
    struct qemu_SetProcessWindowStation *c = (struct qemu_SetProcessWindowStation *)call;
    WINE_TRACE("\n");
    c->super.iret = SetProcessWindowStation(QEMU_G2H(c->handle));
}

#endif

struct qemu_EnumWindowStationsA
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t lparam;
    uint64_t wrapper;
};

struct qemu_EnumWindowStations_cb
{
    uint64_t func;
    uint64_t winsta;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumWindowStationsA_guest_cb(struct qemu_EnumWindowStations_cb *call)
{
    WINSTAENUMPROCA func = (WINSTAENUMPROCA)(ULONG_PTR)call->func;
    return func((char *)(ULONG_PTR)call->winsta, call->param);
}

WINUSERAPI BOOL WINAPI EnumWindowStationsA(WINSTAENUMPROCA func, LPARAM lparam)
{
    struct qemu_EnumWindowStationsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMWINDOWSTATIONSA);
    call.func = (ULONG_PTR)func;
    call.lparam = (ULONG_PTR)lparam;
    call.wrapper = (ULONG_PTR)EnumWindowStationsA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_EnumWindowStations_host_param
{
    uint64_t wrapper, guest_cb, guest_param;
};

static BOOL CALLBACK qemu_EnumWindowStationsA_host_cb(char *winsta, LPARAM lp)
{
    struct qemu_EnumWindowStations_host_param *param = (struct qemu_EnumWindowStations_host_param *)lp;
    struct qemu_EnumWindowStations_cb call;
    BOOL ret;

    WINE_TRACE("Calling guest func 0x%lx(%s, 0x%lx).\n", (unsigned long)param->guest_cb, winsta,
            (unsigned long)param->guest_param);
    call.func = param->guest_cb;
    call.winsta = QEMU_H2G(winsta);
    call.param = param->guest_param;

    ret = qemu_ops->qemu_execute(QEMU_G2H(param->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumWindowStationsA(struct qemu_syscall *call)
{
    struct qemu_EnumWindowStationsA *c = (struct qemu_EnumWindowStationsA *)call;
    struct qemu_EnumWindowStations_host_param param;

    WINE_TRACE("\n");
    param.wrapper = c->wrapper;
    param.guest_cb = c->func;
    param.guest_param = c->lparam;

    c->super.iret = EnumWindowStationsA(c->func ? qemu_EnumWindowStationsA_host_cb : NULL, (LPARAM)&param);
}

#endif

struct qemu_EnumWindowStationsW
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t lparam;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumWindowStationsW_guest_cb(struct qemu_EnumWindowStations_cb *call)
{
    WINSTAENUMPROCW func = (WINSTAENUMPROCW)(ULONG_PTR)call->func;
    return func((WCHAR *)(ULONG_PTR)call->winsta, call->param);
}

WINUSERAPI BOOL WINAPI EnumWindowStationsW(WINSTAENUMPROCW func, LPARAM lparam)
{
    struct qemu_EnumWindowStationsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMWINDOWSTATIONSW);
    call.func = (ULONG_PTR)func;
    call.lparam = (ULONG_PTR)lparam;
    call.wrapper = (ULONG_PTR)EnumWindowStationsW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK qemu_EnumWindowStationsW_host_cb(WCHAR *winsta, LPARAM lp)
{
    struct qemu_EnumWindowStations_host_param *param = (struct qemu_EnumWindowStations_host_param *)lp;
    struct qemu_EnumWindowStations_cb call;
    BOOL ret;

    WINE_TRACE("Calling guest func 0x%lx(%s, 0x%lx).\n", (unsigned long)param->guest_cb,
            wine_dbgstr_w(winsta), (unsigned long)param->guest_param);
    call.func = param->guest_cb;
    call.winsta = QEMU_H2G(winsta);
    call.param = param->guest_param;

    ret = qemu_ops->qemu_execute(QEMU_G2H(param->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumWindowStationsW(struct qemu_syscall *call)
{
    struct qemu_EnumWindowStationsW *c = (struct qemu_EnumWindowStationsW *)call;
    struct qemu_EnumWindowStations_host_param param;

    WINE_TRACE("\n");
    param.wrapper = c->wrapper;
    param.guest_cb = c->func;
    param.guest_param = c->lparam;

    c->super.iret = EnumWindowStationsW(c->func ? qemu_EnumWindowStationsW_host_cb : NULL, (LPARAM)&param);
}

#endif

struct qemu_CreateDesktopA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t device;
    uint64_t devmode;
    uint64_t flags;
    uint64_t access;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDESK WINAPI CreateDesktopA(LPCSTR name, LPCSTR device, LPDEVMODEA devmode, DWORD flags, ACCESS_MASK access, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateDesktopA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDESKTOPA);
    call.name = (ULONG_PTR)name;
    call.device = (ULONG_PTR)device;
    call.devmode = (ULONG_PTR)devmode;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HDESK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateDesktopA(struct qemu_syscall *call)
{
    struct qemu_CreateDesktopA *c = (struct qemu_CreateDesktopA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CreateDesktopA(QEMU_G2H(c->name), QEMU_G2H(c->device), QEMU_G2H(c->devmode), c->flags, c->access, QEMU_G2H(c->sa));
}

#endif

struct qemu_CreateDesktopW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t device;
    uint64_t devmode;
    uint64_t flags;
    uint64_t access;
    uint64_t sa;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDESK WINAPI CreateDesktopW(LPCWSTR name, LPCWSTR device, LPDEVMODEW devmode, DWORD flags, ACCESS_MASK access, LPSECURITY_ATTRIBUTES sa)
{
    struct qemu_CreateDesktopW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEDESKTOPW);
    call.name = (ULONG_PTR)name;
    call.device = (ULONG_PTR)device;
    call.devmode = (ULONG_PTR)devmode;
    call.flags = (ULONG_PTR)flags;
    call.access = (ULONG_PTR)access;
    call.sa = (ULONG_PTR)sa;

    qemu_syscall(&call.super);

    return (HDESK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateDesktopW(struct qemu_syscall *call)
{
    struct qemu_CreateDesktopW *c = (struct qemu_CreateDesktopW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreateDesktopW(QEMU_G2H(c->name), QEMU_G2H(c->device), QEMU_G2H(c->devmode), c->flags, c->access, QEMU_G2H(c->sa));
}

#endif

struct qemu_OpenDesktopA
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t flags;
    uint64_t inherit;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDESK WINAPI OpenDesktopA(LPCSTR name, DWORD flags, BOOL inherit, ACCESS_MASK access)
{
    struct qemu_OpenDesktopA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENDESKTOPA);
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.inherit = (ULONG_PTR)inherit;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HDESK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenDesktopA(struct qemu_syscall *call)
{
    struct qemu_OpenDesktopA *c = (struct qemu_OpenDesktopA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenDesktopA(QEMU_G2H(c->name), c->flags, c->inherit, c->access);
}

#endif

struct qemu_OpenDesktopW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t flags;
    uint64_t inherit;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDESK WINAPI OpenDesktopW(LPCWSTR name, DWORD flags, BOOL inherit, ACCESS_MASK access)
{
    struct qemu_OpenDesktopW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENDESKTOPW);
    call.name = (ULONG_PTR)name;
    call.flags = (ULONG_PTR)flags;
    call.inherit = (ULONG_PTR)inherit;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HDESK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenDesktopW(struct qemu_syscall *call)
{
    struct qemu_OpenDesktopW *c = (struct qemu_OpenDesktopW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)OpenDesktopW(QEMU_G2H(c->name), c->flags, c->inherit, c->access);
}

#endif

struct qemu_CloseDesktop
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CloseDesktop(HDESK handle)
{
    struct qemu_CloseDesktop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CLOSEDESKTOP);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CloseDesktop(struct qemu_syscall *call)
{
    struct qemu_CloseDesktop *c = (struct qemu_CloseDesktop *)call;
    WINE_TRACE("\n");
    c->super.iret = CloseDesktop(QEMU_G2H(c->handle));
}

#endif

struct qemu_GetThreadDesktop
{
    struct qemu_syscall super;
    uint64_t thread;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDESK WINAPI GetThreadDesktop(DWORD thread)
{
    struct qemu_GetThreadDesktop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTHREADDESKTOP);
    call.thread = (ULONG_PTR)thread;

    qemu_syscall(&call.super);

    return (HDESK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetThreadDesktop(struct qemu_syscall *call)
{
    struct qemu_GetThreadDesktop *c = (struct qemu_GetThreadDesktop *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)GetThreadDesktop(c->thread);
}

#endif

struct qemu_SetThreadDesktop
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetThreadDesktop(HDESK handle)
{
    struct qemu_SetThreadDesktop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTHREADDESKTOP);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetThreadDesktop(struct qemu_syscall *call)
{
    struct qemu_SetThreadDesktop *c = (struct qemu_SetThreadDesktop *)call;
    WINE_TRACE("\n");
    c->super.iret = SetThreadDesktop(QEMU_G2H(c->handle));
}

#endif

struct qemu_EnumDesktopsA
{
    struct qemu_syscall super;
    uint64_t winsta;
    uint64_t func;
    uint64_t lparam;
    uint64_t wrapper;
};

struct qemu_EnumDesktops_cb
{
    uint64_t func;
    uint64_t desktop;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumDesktopsA_guest_cb(struct qemu_EnumDesktops_cb *call)
{
    DESKTOPENUMPROCA func = (DESKTOPENUMPROCA)(ULONG_PTR)call->func;
    return func((char *)(ULONG_PTR)call->desktop, call->param);
}

WINUSERAPI BOOL WINAPI EnumDesktopsA(HWINSTA winsta, DESKTOPENUMPROCA func, LPARAM lparam)
{
    struct qemu_EnumDesktopsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDESKTOPSA);
    call.winsta = (ULONG_PTR)winsta;
    call.func = (ULONG_PTR)func;
    call.lparam = (ULONG_PTR)lparam;
    call.wrapper = (ULONG_PTR)EnumDesktopsA_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_EnumDesktops_host_param
{
    uint64_t wrapper, guest_cb, guest_param;
};

static BOOL CALLBACK EnumDesktopsA_host_cb(char *desktop, LPARAM lp)
{
    struct qemu_EnumDesktops_host_param *param = (struct qemu_EnumDesktops_host_param *)lp;
    struct qemu_EnumDesktops_cb call;
    BOOL ret;

    WINE_TRACE("Calling guest func 0x%lx(%s, 0x%lx).\n", (unsigned long)param->guest_cb, desktop,
            (unsigned long)param->guest_param);
    call.func = param->guest_cb;
    call.desktop = QEMU_H2G(desktop);
    call.param = param->guest_param;

    ret = qemu_ops->qemu_execute(QEMU_G2H(param->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumDesktopsA(struct qemu_syscall *call)
{
    struct qemu_EnumDesktopsA *c = (struct qemu_EnumDesktopsA *)call;
    struct qemu_EnumDesktops_host_param param;

    WINE_TRACE("\n");
    param.wrapper = c->wrapper;
    param.guest_cb = c->func;
    param.guest_param = c->lparam;

    c->super.iret = EnumDesktopsA(QEMU_G2H(c->winsta), c->func ? EnumDesktopsA_host_cb : NULL, (LPARAM)&param);
}

#endif

struct qemu_EnumDesktopsW
{
    struct qemu_syscall super;
    uint64_t winsta;
    uint64_t func;
    uint64_t lparam;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumDesktopsW_guest_cb(struct qemu_EnumDesktops_cb *call)
{
    DESKTOPENUMPROCW func = (DESKTOPENUMPROCW)(ULONG_PTR)call->func;
    return func((WCHAR *)(ULONG_PTR)call->desktop, call->param);
}

WINUSERAPI BOOL WINAPI EnumDesktopsW(HWINSTA winsta, DESKTOPENUMPROCW func, LPARAM lparam)
{
    struct qemu_EnumDesktopsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMDESKTOPSW);
    call.winsta = (ULONG_PTR)winsta;
    call.func = (ULONG_PTR)func;
    call.lparam = (ULONG_PTR)lparam;
    call.wrapper = (ULONG_PTR)EnumDesktopsW_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static BOOL CALLBACK EnumDesktopsW_host_cb(WCHAR *desktop, LPARAM lp)
{
    struct qemu_EnumDesktops_host_param *param = (struct qemu_EnumDesktops_host_param *)lp;
    struct qemu_EnumDesktops_cb call;
    BOOL ret;

    WINE_TRACE("Calling guest func 0x%lx(%s, 0x%lx).\n", (unsigned long)param->guest_cb,
            wine_dbgstr_w(desktop), (unsigned long)param->guest_param);
    call.func = param->guest_cb;
    call.desktop = QEMU_H2G(desktop);
    call.param = param->guest_param;

    ret = qemu_ops->qemu_execute(QEMU_G2H(param->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %u.\n", ret);
    return ret;
}

void qemu_EnumDesktopsW(struct qemu_syscall *call)
{
    struct qemu_EnumDesktopsW *c = (struct qemu_EnumDesktopsW *)call;
    struct qemu_EnumDesktops_host_param param;

    WINE_TRACE("\n");
    param.wrapper = c->wrapper;
    param.guest_cb = c->func;
    param.guest_param = c->lparam;

    c->super.iret = EnumDesktopsW(QEMU_G2H(c->winsta), c->func ? EnumDesktopsW_host_cb : NULL, (LPARAM)&param);
}

#endif

struct qemu_OpenInputDesktop
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t inherit;
    uint64_t access;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HDESK WINAPI OpenInputDesktop(DWORD flags, BOOL inherit, ACCESS_MASK access)
{
    struct qemu_OpenInputDesktop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPENINPUTDESKTOP);
    call.flags = (ULONG_PTR)flags;
    call.inherit = (ULONG_PTR)inherit;
    call.access = (ULONG_PTR)access;

    qemu_syscall(&call.super);

    return (HDESK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_OpenInputDesktop(struct qemu_syscall *call)
{
    struct qemu_OpenInputDesktop *c = (struct qemu_OpenInputDesktop *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)OpenInputDesktop(c->flags, c->inherit, c->access);
}

#endif

struct qemu_GetUserObjectInformationA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t index;
    uint64_t info;
    uint64_t len;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetUserObjectInformationA(HANDLE handle, INT index, LPVOID info, DWORD len, LPDWORD needed)
{
    struct qemu_GetUserObjectInformationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSEROBJECTINFORMATIONA);
    call.handle = (ULONG_PTR)handle;
    call.index = (ULONG_PTR)index;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserObjectInformationA(struct qemu_syscall *call)
{
    struct qemu_GetUserObjectInformationA *c = (struct qemu_GetUserObjectInformationA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetUserObjectInformationA(QEMU_G2H(c->handle), c->index, QEMU_G2H(c->info), c->len, QEMU_G2H(c->needed));
}

#endif

struct qemu_GetUserObjectInformationW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t index;
    uint64_t info;
    uint64_t len;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetUserObjectInformationW(HANDLE handle, INT index, LPVOID info, DWORD len, LPDWORD needed)
{
    struct qemu_GetUserObjectInformationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSEROBJECTINFORMATIONW);
    call.handle = (ULONG_PTR)handle;
    call.index = (ULONG_PTR)index;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserObjectInformationW(struct qemu_syscall *call)
{
    struct qemu_GetUserObjectInformationW *c = (struct qemu_GetUserObjectInformationW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetUserObjectInformationW(QEMU_G2H(c->handle), c->index, QEMU_G2H(c->info), c->len, QEMU_G2H(c->needed));
}

#endif

struct qemu_SetUserObjectInformationA
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t index;
    uint64_t info;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetUserObjectInformationA(HANDLE handle, INT index, LPVOID info, DWORD len)
{
    struct qemu_SetUserObjectInformationA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETUSEROBJECTINFORMATIONA);
    call.handle = (ULONG_PTR)handle;
    call.index = (ULONG_PTR)index;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUserObjectInformationA(struct qemu_syscall *call)
{
    struct qemu_SetUserObjectInformationA *c = (struct qemu_SetUserObjectInformationA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUserObjectInformationA(QEMU_G2H(c->handle), c->index, QEMU_G2H(c->info), c->len);
}

#endif

struct qemu_SetUserObjectInformationW
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t index;
    uint64_t info;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetUserObjectInformationW(HANDLE handle, INT index, LPVOID info, DWORD len)
{
    struct qemu_SetUserObjectInformationW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETUSEROBJECTINFORMATIONW);
    call.handle = (ULONG_PTR)handle;
    call.index = (ULONG_PTR)index;
    call.info = (ULONG_PTR)info;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUserObjectInformationW(struct qemu_syscall *call)
{
    struct qemu_SetUserObjectInformationW *c = (struct qemu_SetUserObjectInformationW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUserObjectInformationW(QEMU_G2H(c->handle), c->index, QEMU_G2H(c->info), c->len);
}

#endif

struct qemu_GetUserObjectSecurity
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t info;
    uint64_t sid;
    uint64_t len;
    uint64_t needed;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI GetUserObjectSecurity(HANDLE handle, PSECURITY_INFORMATION info, PSECURITY_DESCRIPTOR sid, DWORD len, LPDWORD needed)
{
    struct qemu_GetUserObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETUSEROBJECTSECURITY);
    call.handle = (ULONG_PTR)handle;
    call.info = (ULONG_PTR)info;
    call.sid = (ULONG_PTR)sid;
    call.len = (ULONG_PTR)len;
    call.needed = (ULONG_PTR)needed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetUserObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_GetUserObjectSecurity *c = (struct qemu_GetUserObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetUserObjectSecurity(QEMU_G2H(c->handle), QEMU_G2H(c->info), QEMU_G2H(c->sid), c->len, QEMU_G2H(c->needed));
}

#endif

struct qemu_SetUserObjectSecurity
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t info;
    uint64_t sid;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetUserObjectSecurity(HANDLE handle, PSECURITY_INFORMATION info, PSECURITY_DESCRIPTOR sid)
{
    struct qemu_SetUserObjectSecurity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETUSEROBJECTSECURITY);
    call.handle = (ULONG_PTR)handle;
    call.info = (ULONG_PTR)info;
    call.sid = (ULONG_PTR)sid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetUserObjectSecurity(struct qemu_syscall *call)
{
    struct qemu_SetUserObjectSecurity *c = (struct qemu_SetUserObjectSecurity *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetUserObjectSecurity(QEMU_G2H(c->handle), QEMU_G2H(c->info), QEMU_G2H(c->sid));
}

#endif

