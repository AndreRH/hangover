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


struct qemu_SetWindowsHookA
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookA(INT id, HOOKPROC proc)
{
    struct qemu_SetWindowsHookA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKA);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;

    qemu_syscall(&call.super);

    return (HHOOK)call.super.iret;
}

#else

void qemu_SetWindowsHookA(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookA *c = (struct qemu_SetWindowsHookA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetWindowsHookA(c->id, QEMU_G2H(c->proc));
}

#endif

struct qemu_SetWindowsHookW
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookW(INT id, HOOKPROC proc)
{
    struct qemu_SetWindowsHookW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKW);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;

    qemu_syscall(&call.super);

    return (HHOOK)call.super.iret;
}

#else

void qemu_SetWindowsHookW(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookW *c = (struct qemu_SetWindowsHookW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetWindowsHookW(c->id, QEMU_G2H(c->proc));
}

#endif

struct qemu_SetWindowsHookExA
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
    uint64_t inst;
    uint64_t tid;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookExA(INT id, HOOKPROC proc, HINSTANCE inst, DWORD tid)
{
    struct qemu_SetWindowsHookExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXA);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;
    call.inst = (uint64_t)inst;
    call.tid = (uint64_t)tid;

    qemu_syscall(&call.super);

    return (HHOOK)call.super.iret;
}

#else

void qemu_SetWindowsHookExA(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookExA *c = (struct qemu_SetWindowsHookExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetWindowsHookExA(c->id, QEMU_G2H(c->proc), QEMU_G2H(c->inst), c->tid);
}

#endif

struct qemu_SetWindowsHookExW
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
    uint64_t inst;
    uint64_t tid;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookExW(INT id, HOOKPROC proc, HINSTANCE inst, DWORD tid)
{
    struct qemu_SetWindowsHookExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXW);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;
    call.inst = (uint64_t)inst;
    call.tid = (uint64_t)tid;

    qemu_syscall(&call.super);

    return (HHOOK)call.super.iret;
}

#else

void qemu_SetWindowsHookExW(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookExW *c = (struct qemu_SetWindowsHookExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetWindowsHookExW(c->id, QEMU_G2H(c->proc), QEMU_G2H(c->inst), c->tid);
}

#endif

struct qemu_UnhookWindowsHook
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnhookWindowsHook(INT id, HOOKPROC proc)
{
    struct qemu_UnhookWindowsHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNHOOKWINDOWSHOOK);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnhookWindowsHook(struct qemu_syscall *call)
{
    struct qemu_UnhookWindowsHook *c = (struct qemu_UnhookWindowsHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnhookWindowsHook(c->id, QEMU_G2H(c->proc));
}

#endif

struct qemu_UnhookWindowsHookEx
{
    struct qemu_syscall super;
    uint64_t hhook;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnhookWindowsHookEx(HHOOK hhook)
{
    struct qemu_UnhookWindowsHookEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNHOOKWINDOWSHOOKEX);
    call.hhook = (uint64_t)hhook;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnhookWindowsHookEx(struct qemu_syscall *call)
{
    struct qemu_UnhookWindowsHookEx *c = (struct qemu_UnhookWindowsHookEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnhookWindowsHookEx(QEMU_G2H(c->hhook));
}

#endif

struct qemu_CallNextHookEx
{
    struct qemu_syscall super;
    uint64_t hhook;
    uint64_t code;
    uint64_t wparam;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI LRESULT WINAPI CallNextHookEx(HHOOK hhook, INT code, WPARAM wparam, LPARAM lparam)
{
    struct qemu_CallNextHookEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLNEXTHOOKEX);
    call.hhook = (uint64_t)hhook;
    call.code = (uint64_t)code;
    call.wparam = (uint64_t)wparam;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallNextHookEx(struct qemu_syscall *call)
{
    struct qemu_CallNextHookEx *c = (struct qemu_CallNextHookEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallNextHookEx(QEMU_G2H(c->hhook), c->code, c->wparam, c->lparam);
}

#endif

struct qemu_CallMsgFilterA
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t code;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CallMsgFilterA(LPMSG msg, INT code)
{
    struct qemu_CallMsgFilterA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLMSGFILTERA);
    call.msg = (uint64_t)msg;
    call.code = (uint64_t)code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallMsgFilterA(struct qemu_syscall *call)
{
    struct qemu_CallMsgFilterA *c = (struct qemu_CallMsgFilterA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallMsgFilterA(QEMU_G2H(c->msg), c->code);
}

#endif

struct qemu_CallMsgFilterW
{
    struct qemu_syscall super;
    uint64_t msg;
    uint64_t code;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI CallMsgFilterW(LPMSG msg, INT code)
{
    struct qemu_CallMsgFilterW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLMSGFILTERW);
    call.msg = (uint64_t)msg;
    call.code = (uint64_t)code;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallMsgFilterW(struct qemu_syscall *call)
{
    struct qemu_CallMsgFilterW *c = (struct qemu_CallMsgFilterW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CallMsgFilterW(QEMU_G2H(c->msg), c->code);
}

#endif

struct qemu_SetWinEventHook
{
    struct qemu_syscall super;
    uint64_t event_min;
    uint64_t event_max;
    uint64_t inst;
    uint64_t proc;
    uint64_t pid;
    uint64_t tid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HWINEVENTHOOK WINAPI SetWinEventHook(DWORD event_min, DWORD event_max, HMODULE inst, WINEVENTPROC proc, DWORD pid, DWORD tid, DWORD flags)
{
    struct qemu_SetWinEventHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINEVENTHOOK);
    call.event_min = (uint64_t)event_min;
    call.event_max = (uint64_t)event_max;
    call.inst = (uint64_t)inst;
    call.proc = (uint64_t)proc;
    call.pid = (uint64_t)pid;
    call.tid = (uint64_t)tid;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return (HWINEVENTHOOK)call.super.iret;
}

#else

void qemu_SetWinEventHook(struct qemu_syscall *call)
{
    struct qemu_SetWinEventHook *c = (struct qemu_SetWinEventHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetWinEventHook(c->event_min, c->event_max, QEMU_G2H(c->inst), QEMU_G2H(c->proc), c->pid, c->tid, c->flags);
}

#endif

struct qemu_UnhookWinEvent
{
    struct qemu_syscall super;
    uint64_t hEventHook;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI UnhookWinEvent(HWINEVENTHOOK hEventHook)
{
    struct qemu_UnhookWinEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UNHOOKWINEVENT);
    call.hEventHook = (uint64_t)hEventHook;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnhookWinEvent(struct qemu_syscall *call)
{
    struct qemu_UnhookWinEvent *c = (struct qemu_UnhookWinEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UnhookWinEvent(QEMU_G2H(c->hEventHook));
}

#endif

struct qemu_NotifyWinEvent
{
    struct qemu_syscall super;
    uint64_t event;
    uint64_t hwnd;
    uint64_t object_id;
    uint64_t child_id;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI void WINAPI NotifyWinEvent(DWORD event, HWND hwnd, LONG object_id, LONG child_id)
{
    struct qemu_NotifyWinEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NOTIFYWINEVENT);
    call.event = (uint64_t)event;
    call.hwnd = (uint64_t)hwnd;
    call.object_id = (uint64_t)object_id;
    call.child_id = (uint64_t)child_id;

    qemu_syscall(&call.super);

    return;
}

#else

void qemu_NotifyWinEvent(struct qemu_syscall *call)
{
    struct qemu_NotifyWinEvent *c = (struct qemu_NotifyWinEvent *)call;
    WINE_FIXME("Unverified!\n");
    NotifyWinEvent(c->event, QEMU_G2H(c->hwnd), c->object_id, c->child_id);
}

#endif

struct qemu_IsWinEventHookInstalled
{
    struct qemu_syscall super;
    uint64_t dwEvent;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI IsWinEventHookInstalled(DWORD dwEvent)
{
    struct qemu_IsWinEventHookInstalled call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISWINEVENTHOOKINSTALLED);
    call.dwEvent = (uint64_t)dwEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IsWinEventHookInstalled(struct qemu_syscall *call)
{
    struct qemu_IsWinEventHookInstalled *c = (struct qemu_IsWinEventHookInstalled *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsWinEventHookInstalled(c->dwEvent);
}

#endif

