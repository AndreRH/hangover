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


struct qemu_SetActiveWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetActiveWindow(HWND hwnd)
{
    struct qemu_SetActiveWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETACTIVEWINDOW);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_SetActiveWindow(struct qemu_syscall *call)
{
    struct qemu_SetActiveWindow *c = (struct qemu_SetActiveWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetActiveWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_SetFocus
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetFocus(HWND hwnd)
{
    struct qemu_SetFocus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFOCUS);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_SetFocus(struct qemu_syscall *call)
{
    struct qemu_SetFocus *c = (struct qemu_SetFocus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetFocus(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_SetForegroundWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetForegroundWindow(HWND hwnd)
{
    struct qemu_SetForegroundWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETFOREGROUNDWINDOW);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetForegroundWindow(struct qemu_syscall *call)
{
    struct qemu_SetForegroundWindow *c = (struct qemu_SetForegroundWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetForegroundWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetActiveWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetActiveWindow(void)
{
    struct qemu_GetActiveWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETACTIVEWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetActiveWindow(struct qemu_syscall *call)
{
    struct qemu_GetActiveWindow *c = (struct qemu_GetActiveWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetActiveWindow();
}

#endif

struct qemu_GetFocus
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetFocus(void)
{
    struct qemu_GetFocus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFOCUS);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetFocus(struct qemu_syscall *call)
{
    struct qemu_GetFocus *c = (struct qemu_GetFocus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetFocus();
}

#endif

struct qemu_GetForegroundWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetForegroundWindow(void)
{
    struct qemu_GetForegroundWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFOREGROUNDWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetForegroundWindow(struct qemu_syscall *call)
{
    struct qemu_GetForegroundWindow *c = (struct qemu_GetForegroundWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetForegroundWindow();
}

#endif

struct qemu_SetShellWindowEx
{
    struct qemu_syscall super;
    uint64_t hwndShell;
    uint64_t hwndListView;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetShellWindowEx(HWND hwndShell, HWND hwndListView)
{
    struct qemu_SetShellWindowEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSHELLWINDOWEX);
    call.hwndShell = (uint64_t)hwndShell;
    call.hwndListView = (uint64_t)hwndListView;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetShellWindowEx to Wine headers? */
extern BOOL WINAPI SetShellWindowEx(HWND hwndShell, HWND hwndListView);
void qemu_SetShellWindowEx(struct qemu_syscall *call)
{
    struct qemu_SetShellWindowEx *c = (struct qemu_SetShellWindowEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetShellWindowEx(QEMU_G2H(c->hwndShell), QEMU_G2H(c->hwndListView));
}

#endif

struct qemu_SetShellWindow
{
    struct qemu_syscall super;
    uint64_t hwndShell;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetShellWindow(HWND hwndShell)
{
    struct qemu_SetShellWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETSHELLWINDOW);
    call.hwndShell = (uint64_t)hwndShell;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SetShellWindow to Wine headers? */
extern BOOL WINAPI SetShellWindow(HWND hwndShell);
void qemu_SetShellWindow(struct qemu_syscall *call)
{
    struct qemu_SetShellWindow *c = (struct qemu_SetShellWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetShellWindow(QEMU_G2H(c->hwndShell));
}

#endif

struct qemu_GetShellWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetShellWindow(void)
{
    struct qemu_GetShellWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSHELLWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

void qemu_GetShellWindow(struct qemu_syscall *call)
{
    struct qemu_GetShellWindow *c = (struct qemu_GetShellWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetShellWindow();
}

#endif

struct qemu_SetProgmanWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetProgmanWindow (HWND hwnd)
{
    struct qemu_SetProgmanWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROGMANWINDOW);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

/* TODO: Add SetProgmanWindow to Wine headers? */
extern HWND WINAPI SetProgmanWindow (HWND hwnd);
void qemu_SetProgmanWindow(struct qemu_syscall *call)
{
    struct qemu_SetProgmanWindow *c = (struct qemu_SetProgmanWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetProgmanWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetProgmanWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetProgmanWindow(void)
{
    struct qemu_GetProgmanWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROGMANWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

/* TODO: Add GetProgmanWindow to Wine headers? */
extern HWND WINAPI GetProgmanWindow(void);
void qemu_GetProgmanWindow(struct qemu_syscall *call)
{
    struct qemu_GetProgmanWindow *c = (struct qemu_GetProgmanWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetProgmanWindow();
}

#endif

struct qemu_SetTaskmanWindow
{
    struct qemu_syscall super;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI SetTaskmanWindow (HWND hwnd)
{
    struct qemu_SetTaskmanWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETTASKMANWINDOW);
    call.hwnd = (uint64_t)hwnd;

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

/* TODO: Add SetTaskmanWindow to Wine headers? */
extern HWND WINAPI SetTaskmanWindow (HWND hwnd);
void qemu_SetTaskmanWindow(struct qemu_syscall *call)
{
    struct qemu_SetTaskmanWindow *c = (struct qemu_SetTaskmanWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetTaskmanWindow(QEMU_G2H(c->hwnd));
}

#endif

struct qemu_GetTaskmanWindow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWND WINAPI GetTaskmanWindow(void)
{
    struct qemu_GetTaskmanWindow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETTASKMANWINDOW);

    qemu_syscall(&call.super);

    return (HWND)call.super.iret;
}

#else

/* TODO: Add GetTaskmanWindow to Wine headers? */
extern HWND WINAPI GetTaskmanWindow(void);
void qemu_GetTaskmanWindow(struct qemu_syscall *call)
{
    struct qemu_GetTaskmanWindow *c = (struct qemu_GetTaskmanWindow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetTaskmanWindow();
}

#endif

