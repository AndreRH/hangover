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

struct qemu_SetWindowsHookEx
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
    uint64_t inst;
    uint64_t tid;
    uint64_t wrapper;
};

struct qemu_cbt_hook_cb
{
    uint64_t func, inst;
    uint64_t code;
    uint64_t wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t qemu_hook_guest_cb(struct qemu_cbt_hook_cb *call)
{
    HOOKPROC proc = (HOOKPROC)call->func;
    return proc(call->code, call->wp, call->lp);
}

WINUSERAPI HHOOK WINAPI SetWindowsHookExA(INT id, HOOKPROC proc, HINSTANCE inst, DWORD tid)
{
    struct qemu_SetWindowsHookEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXA);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;
    call.inst = (uint64_t)inst;
    call.tid = (uint64_t)tid;
    call.wrapper = (uint64_t)qemu_hook_guest_cb;

    qemu_syscall(&call.super);

    return (HHOOK)call.super.iret;
}

#else

/* So somehow constant strings cannot be computed at compile time, so no debug info.
 * Presumably there's an issue with position independent code or such. */
static CRITICAL_SECTION hook_cs = {0, -1, 0, 0, 0, 0};

struct qemu_hook_data
{
    HHOOK hook_id;
    uint64_t client_cb;
    uint64_t client_inst;
};

static struct qemu_hook_data *installed_hooks[WH_MAXHOOK + 1];
static uint64_t hook_guest_wrapper;

LRESULT CALLBACK qemu_CBT_wrapper(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_CBT];
    struct qemu_cbt_hook_cb call;
    LRESULT ret;

    if (!data || !data->hook_id)
        WINE_ERR("CBT hook callback called but no hook is installed.\n");

    WINE_TRACE("Calling callback 0x%lx(%u, %lu, %lu).\n", data->client_cb, code, wp, lp);
    call.func = data->client_cb;
    call.inst = data->client_inst;
    call.code = code;
    call.wp = wp;
    call.lp = lp;

    ret = qemu_ops->qemu_execute(QEMU_G2H(hook_guest_wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest function returned %lu.\n", ret);
    return ret;
}

static HHOOK set_windows_hook(INT id, uint64_t proc, uint64_t inst, DWORD tid, BOOL unicode)
{
    HOOKPROC real_proc;
    HINSTANCE real_mod;
    HHOOK ret;
    struct qemu_hook_data *hook_data;

    WINE_FIXME("(%u, 0x%lx, 0x%lx, %x, %u).\n", id, proc, inst, tid, unicode);

    /* FIXME 1: This will not work well with foreign processes. If they are not running inside
     * qemu we can't execute the guest callback. If we're running qemu we have to load the guest
     * HINSTANCE into the foreign process somehow.
     *
     * FIXME 2: I can't use the trick I'm using with e.g. WNDPROCs where I store executable code
     * in a struct and pass the instruction pointer as an extra value to the wrapper function to
     * find my own data. Wine needs a (host-architecture) module to load into the remote process
     * and this won't work with VirtualAlloc'ed code. So far this function supports only one hook
     * of a kind. */

    EnterCriticalSection(&hook_cs);

    switch (id)
    {
        case WH_CBT:
            real_proc = qemu_CBT_wrapper;
            real_mod = 0;
            if (installed_hooks[WH_CBT])
            {
                WINE_FIXME("A WH_CBT hook is already installed.\n");
                LeaveCriticalSection(&hook_cs);
                return NULL;
            }
            hook_data = HeapAlloc(GetProcessHeap(), 0, sizeof(hook_data));
            if (!hook_data)
            {
                LeaveCriticalSection(&hook_cs);
                return NULL;
            }
            break;

        default:
            LeaveCriticalSection(&hook_cs);
            WINE_FIXME("Hook %d not implemented.\n", id);
            return NULL;
    }

    WINE_TRACE("Setting host hook (%d, %p, %p, %x).\n", id, real_proc, real_mod, tid);
    if (unicode)
        ret = SetWindowsHookExW(id, real_proc, real_mod, tid);
    else
        ret = SetWindowsHookExA(id, real_proc, real_mod, tid);
    WINE_TRACE("Got host hook %p.\n", ret);

    if (ret)
    {
        hook_data->hook_id = ret;
        hook_data->client_cb = proc;
        hook_data->client_inst = inst;
        installed_hooks[id] = hook_data;
    }

    LeaveCriticalSection(&hook_cs);
    return ret;
}

void qemu_SetWindowsHookExA(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookEx *c = (struct qemu_SetWindowsHookEx *)call;

    hook_guest_wrapper = c->wrapper;

    c->super.iret = (uint64_t)set_windows_hook(c->id, c->proc, c->inst, c->tid, FALSE);
}

#endif

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookExW(INT id, HOOKPROC proc, HINSTANCE inst, DWORD tid)
{
    struct qemu_SetWindowsHookEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXW);
    call.id = (uint64_t)id;
    call.proc = (uint64_t)proc;
    call.inst = (uint64_t)inst;
    call.tid = (uint64_t)tid;
    call.wrapper = (uint64_t)qemu_hook_guest_cb;

    qemu_syscall(&call.super);

    return (HHOOK)call.super.iret;
}

#else

void qemu_SetWindowsHookExW(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookEx *c = (struct qemu_SetWindowsHookEx *)call;

    hook_guest_wrapper = c->wrapper;

    c->super.iret = (uint64_t)set_windows_hook(c->id, c->proc, c->inst, c->tid, TRUE);
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
    HHOOK hook;

    WINE_TRACE("\n");
    hook = QEMU_G2H(c->hhook);
    c->super.iret = UnhookWindowsHookEx(hook);
    WINE_TRACE("Unhooked\n");

    if (c->super.iret)
    {
        INT i;
        INT found = -1;

        EnterCriticalSection(&hook_cs);
        for (i = 0; i < WH_MAXHOOK; ++i)
        {
            if (installed_hooks[i] && installed_hooks[i]->hook_id == hook)
            {
                if (found != -1)
                    WINE_ERR("Hook %p found in %d and %d.\n", hook, found, i);

                found = i;
                HeapFree(GetProcessHeap(), 0, installed_hooks[i]);
                installed_hooks[i] = NULL;
            }
        }
        LeaveCriticalSection(&hook_cs);

        if (found == -1)
            WINE_FIXME("Hook %p not found in our hook table.\n", hook);
    }
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

