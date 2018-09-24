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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
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

struct qemu_SetWindowsHookA
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
    uint64_t wrapper;
};

struct qemu_cbt_hook_cb
{
    uint64_t func, inst;
    uint64_t code;
    uint64_t wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall qemu_hook_guest_cb(struct qemu_cbt_hook_cb *call)
{
    HOOKPROC proc = (HOOKPROC)(ULONG_PTR)call->func;
    return proc(call->code, call->wp, call->lp);
}

WINUSERAPI HHOOK WINAPI SetWindowsHookA(INT id, HOOKPROC proc)
{
    struct qemu_SetWindowsHookA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKA);
    call.id = (ULONG_PTR)id;
    call.proc = (ULONG_PTR)proc;
    call.wrapper = (ULONG_PTR)qemu_hook_guest_cb;

    qemu_syscall(&call.super);

    return (HHOOK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetWindowsHookA(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookA *c = (struct qemu_SetWindowsHookA *)call;
    struct qemu_SetWindowsHookEx fwd;

    /* I had some problems importing GetCurrentProcessId from the guest-side kernel32.dll.
     * Do the forward on the host side, it is faster anyway. */
    WINE_TRACE("Host side forward.\n");
    fwd.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXA);
    fwd.id = c->id;
    fwd.proc = c->proc;
    fwd.inst = 0;
    fwd.tid = GetCurrentThreadId();
    fwd.wrapper = c->wrapper;
    qemu_SetWindowsHookExA(&fwd.super);
    c->super.iret = fwd.super.iret;
}

#endif

struct qemu_SetWindowsHookW
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t proc;
    uint64_t wrapper;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookW(INT id, HOOKPROC proc)
{
    struct qemu_SetWindowsHookW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKW);
    call.id = (ULONG_PTR)id;
    call.proc = (ULONG_PTR)proc;
    call.wrapper = (ULONG_PTR)qemu_hook_guest_cb;

    qemu_syscall(&call.super);

    return (HHOOK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetWindowsHookW(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookW *c = (struct qemu_SetWindowsHookW *)call;
    struct qemu_SetWindowsHookEx fwd;

    WINE_TRACE("Host side forward.\n");
    fwd.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXW);
    fwd.id = c->id;
    fwd.proc = c->proc;
    fwd.inst = 0;
    fwd.tid = GetCurrentThreadId();
    fwd.wrapper = c->wrapper;
    qemu_SetWindowsHookExW(&fwd.super);
    c->super.iret = fwd.super.iret;
}

#endif

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookExA(INT id, HOOKPROC proc, HINSTANCE inst, DWORD tid)
{
    struct qemu_SetWindowsHookEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXA);
    call.id = (ULONG_PTR)id;
    call.proc = (ULONG_PTR)proc;
    call.inst = (ULONG_PTR)inst;
    call.tid = (ULONG_PTR)tid;
    call.wrapper = (ULONG_PTR)qemu_hook_guest_cb;

    qemu_syscall(&call.super);

    return (HHOOK)(ULONG_PTR)call.super.iret;
}

#else

/* So somehow constant strings cannot be computed at compile time, so no debug info.
 * Presumably there's an issue with position independent code or such. */
static CRITICAL_SECTION hook_cs = {0, -1, 0, 0, 0, 0};

struct qemu_hook_data
{
    HHOOK hook_id;
    INT type;
    uint64_t client_cb;
    uint64_t client_inst;
    HOOKPROC real_proc;
};

static struct qemu_hook_data *installed_hooks[WH_MAXHOOK + 1 - WH_MIN][2];
static uint64_t hook_guest_wrapper;
static __thread struct qemu_hook_data *current_hook;

struct hook_conv_data
{
    LPARAM orig_lp;
    union
    {
        struct qemu_MSG msg32;
    } conv;
};

static LRESULT CALLBACK qemu_hook_wrapper(int code, WPARAM wp, LPARAM lp, struct qemu_hook_data *data)
{
    struct qemu_cbt_hook_cb call;
    LRESULT ret;
    struct qemu_CBT_CREATEWND createwnd;
    struct qemu_CREATESTRUCT createstruct;
    struct hook_conv_data conv_data;
    MSG *msg, msg_copy;
    struct qemu_hook_data *old;

    WINE_TRACE("Calling callback 0x%lx(%u, %lu, %lu).\n", (unsigned long)data->client_cb, code, wp, lp);
    call.func = data->client_cb;
    call.inst = data->client_inst;
    call.code = code;
    call.wp = wp;
    call.lp = lp;

#if GUEST_BIT != HOST_BIT
    if (data->type == WH_CBT && code == HCBT_CREATEWND)
    {
        CREATESTRUCT_h2g(&createstruct, ((CBT_CREATEWNDW *)lp)->lpcs);
        createwnd.lpcs = (ULONG_PTR)&createstruct;
        createwnd.hwndInsertAfter = (ULONG_PTR)((CBT_CREATEWNDW *)lp)->hwndInsertAfter;
        call.lp = (LPARAM)&createwnd;
    }
    else if (data->type == WH_GETMESSAGE)
    {
        msg = (MSG *)lp;
        msg_host_to_guest(&msg_copy, msg);

        conv_data.orig_lp = lp;
        MSG_h2g(&conv_data.conv.msg32, &msg_copy);
        call.lp = QEMU_H2G(&conv_data.conv.msg32);
    }
#endif

    old = current_hook;
    current_hook = data;
    ret = qemu_ops->qemu_execute(QEMU_G2H(hook_guest_wrapper), QEMU_H2G(&call));
    current_hook = old;

    WINE_TRACE("Guest function returned %lu.\n", ret);

#if GUEST_BIT != HOST_BIT
    if (data->type == WH_GETMESSAGE)
    {
        msg_host_to_guest_return(msg, &msg_copy);
    }
#endif

    return ret;
}

static LRESULT CALLBACK qemu_CBT_wrapper0(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_CBT - WH_MIN][0];

    if (!data || !data->hook_id)
        WINE_ERR("CBT hook callback 0 called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_CBT_wrapper1(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_CBT - WH_MIN][1];

    if (!data || !data->hook_id)
        WINE_ERR("CBT hook callback 1 called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_KEYBOARD_LL_wrapper(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_KEYBOARD_LL - WH_MIN][0];

    if (!data || !data->hook_id)
        WINE_ERR("KEYBOARD_LL hook callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_MOUSE_LL_wrapper0(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_MOUSE_LL - WH_MIN][0];

    if (!data || !data->hook_id)
        WINE_ERR("MOUSE_LL hook 0 callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_MOUSE_LL_wrapper1(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_MOUSE_LL - WH_MIN][1];

    if (!data || !data->hook_id)
        WINE_ERR("MOUSE_LL hook 1 callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_MSGFILTER_wrapper(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_MSGFILTER - WH_MIN][0];

    if (!data || !data->hook_id)
        WINE_ERR("MSGFILTER hook callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_GETMESSAGE_wrapper0(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_GETMESSAGE - WH_MIN][0];

    if (!data || !data->hook_id)
        WINE_ERR("GETMESSAGE hook callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_GETMESSAGE_wrapper1(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_GETMESSAGE - WH_MIN][1];

    if (!data || !data->hook_id)
        WINE_ERR("GETMESSAGE hook callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_GETMESSAGE_wrapper2(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_GETMESSAGE - WH_MIN][2];

    if (!data || !data->hook_id)
        WINE_ERR("GETMESSAGE hook callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static LRESULT CALLBACK qemu_CALLWNDPROC_wrapper(int code, WPARAM wp, LPARAM lp)
{
    struct qemu_hook_data *data = installed_hooks[WH_CALLWNDPROC - WH_MIN][0];

    if (!data || !data->hook_id)
        WINE_ERR("CALLWNDPROC hook callback called but no hook is installed.\n");

    return qemu_hook_wrapper(code, wp, lp, data);
}

static HHOOK set_windows_hook(INT id, uint64_t proc, uint64_t inst, DWORD tid, BOOL unicode)
{
    HOOKPROC real_proc;
    HINSTANCE real_mod;
    HHOOK ret;
    struct qemu_hook_data *hook_data;
    unsigned int hook_no = 0;

    /* FIXME 1: This will not work well with foreign processes. If they are not running inside
     * qemu we can't execute the guest callback. If we're running qemu we have to load the guest
     * HINSTANCE into the foreign process somehow.
     *
     * FIXME 2: I can't use the trick I'm using with e.g. WNDPROCs where I store executable code
     * in a struct and pass the instruction pointer as an extra value to the wrapper function to
     * find my own data. Wine needs a (host-architecture) module to load into the remote process
     * and this won't work with VirtualAlloc'ed code. So far this function supports only one or
     * teo hooks of a kind. The arbitrary limit is whatever makes the tests happy. */

    hook_data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*hook_data));
    if (!hook_data)
        return NULL;
    hook_data->type = id;

    EnterCriticalSection(&hook_cs);

    switch (id)
    {
        case WH_CBT:
            /* This hook can be global. */
            WINE_FIXME("(WH_CBT, 0x%lx, 0x%lx, %x, %u).\n", (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);

            real_mod = 0;
            if (!installed_hooks[WH_CBT - WH_MIN][0])
            {
                real_proc = qemu_CBT_wrapper0;
            }
            else if (!installed_hooks[WH_CBT - WH_MIN][1])
            {
                real_proc = qemu_CBT_wrapper1;
                hook_no = 1;
            }
            else
            {
                WINE_FIXME("Two WH_CBT hooks are already installed.\n");
                LeaveCriticalSection(&hook_cs);
                HeapFree(GetProcessHeap(), 0, hook_data);
                return NULL;
            }
            break;

        case WH_KEYBOARD_LL:
            /* This is a global hook, but always called on the registering thread. */
            WINE_TRACE("(WH_KEYBOARD_LL, 0x%lx, 0x%lx, %x, %u).\n", (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);

            real_proc = qemu_KEYBOARD_LL_wrapper;
            real_mod = 0;
            if (installed_hooks[WH_KEYBOARD_LL - WH_MIN][0])
            {
                WINE_FIXME("A WH_KEYBOARD_LL hook is already installed.\n");
                LeaveCriticalSection(&hook_cs);
                HeapFree(GetProcessHeap(), 0, hook_data);
                return NULL;
            }
            break;

        case WH_MOUSE_LL:
            /* This is a global hook, but always called on the registering thread. */
            WINE_TRACE("(WH_MOUSE_LL, 0x%lx, 0x%lx, %x, %u).\n", (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);

            real_mod = 0;
            if (!installed_hooks[WH_MOUSE_LL - WH_MIN][0])
            {
                real_proc = qemu_MOUSE_LL_wrapper0;
            }
            else if (!installed_hooks[WH_MOUSE_LL - WH_MIN][1])
            {
                real_proc = qemu_MOUSE_LL_wrapper1;
                hook_no = 1;
            }
            else
            {
                WINE_FIXME("Two WH_MOUSE_LL hooks are already installed.\n");
                LeaveCriticalSection(&hook_cs);
                HeapFree(GetProcessHeap(), 0, hook_data);
                return NULL;
            }
            break;

        case WH_MSGFILTER:
            /* This hook can be global. */
            WINE_FIXME("(WH_MSGFILTER, 0x%lx, 0x%lx, %x, %u).\n", (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);

            real_proc = qemu_MSGFILTER_wrapper;
            real_mod = 0;
            if (installed_hooks[WH_MSGFILTER - WH_MIN][0])
            {
                WINE_FIXME("A WH_MSGFILTER hook is already installed.\n");
                LeaveCriticalSection(&hook_cs);
                HeapFree(GetProcessHeap(), 0, hook_data);
                return NULL;
            }
            break;

        case WH_GETMESSAGE:
            /* This hook can be global. */
            WINE_FIXME("(WH_GETMESSAGE, 0x%lx, 0x%lx, %x, %u).\n", (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);

            real_mod = 0;
            if (!installed_hooks[WH_GETMESSAGE - WH_MIN][0])
            {
                real_proc = qemu_GETMESSAGE_wrapper0;
            }
            else if (!installed_hooks[WH_GETMESSAGE - WH_MIN][1])
            {
                real_proc = qemu_GETMESSAGE_wrapper1;
                hook_no = 1;
            }
            else if (!installed_hooks[WH_GETMESSAGE - WH_MIN][2])
            {
                real_proc = qemu_GETMESSAGE_wrapper2;
                hook_no = 2;
            }
            else
            {
                WINE_FIXME("Three WH_GETMESSAGE hooks are already installed.\n");
                LeaveCriticalSection(&hook_cs);
                HeapFree(GetProcessHeap(), 0, hook_data);
                return NULL;
            }
            break;

        case WH_CALLWNDPROC:
            /* This hook can be global. */
            WINE_FIXME("(WH_CALLWNDPROC, 0x%lx, 0x%lx, %x, %u).\n", (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);

            real_proc = qemu_CALLWNDPROC_wrapper;
            real_mod = 0;
            if (installed_hooks[WH_CALLWNDPROC - WH_MIN][0])
            {
                WINE_FIXME("A WH_CALLWNDPROC hook is already installed.\n");
                LeaveCriticalSection(&hook_cs);
                HeapFree(GetProcessHeap(), 0, hook_data);
                return NULL;
            }
            break;

        default:
            WINE_FIXME("(%d, 0x%lx, 0x%lx, %x, %u).\n", id, (unsigned long)proc, (unsigned long)inst,
                    tid, unicode);
            LeaveCriticalSection(&hook_cs);
            HeapFree(GetProcessHeap(), 0, hook_data);
            WINE_FIXME("Hook %d not implemented.\n", id);
            return NULL;
    }

    WINE_TRACE("Setting host hook (%d, %p, %p, %x).\n", id, real_proc, real_mod, tid);
    if (unicode)
        ret = SetWindowsHookExW(id, proc ? real_proc : NULL, real_mod, tid);
    else
        ret = SetWindowsHookExA(id, proc ? real_proc : NULL, real_mod, tid);
    WINE_TRACE("Got host hook %p.\n", ret);

    if (ret)
    {
        hook_data->hook_id = ret;
        hook_data->client_cb = proc;
        hook_data->client_inst = inst;
        hook_data->real_proc = real_proc;
        installed_hooks[id - WH_MIN][hook_no] = hook_data;
    }

    LeaveCriticalSection(&hook_cs);
    return ret;
}

void qemu_SetWindowsHookExA(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookEx *c = (struct qemu_SetWindowsHookEx *)call;

    hook_guest_wrapper = c->wrapper;

    c->super.iret = (ULONG_PTR)set_windows_hook(c->id, c->proc, c->inst, c->tid, FALSE);
}

#endif

#ifdef QEMU_DLL_GUEST

WINUSERAPI HHOOK WINAPI SetWindowsHookExW(INT id, HOOKPROC proc, HINSTANCE inst, DWORD tid)
{
    struct qemu_SetWindowsHookEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINDOWSHOOKEXW);
    call.id = (ULONG_PTR)id;
    call.proc = (ULONG_PTR)proc;
    call.inst = (ULONG_PTR)inst;
    call.tid = (ULONG_PTR)tid;
    call.wrapper = (ULONG_PTR)qemu_hook_guest_cb;

    qemu_syscall(&call.super);

    return (HHOOK)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetWindowsHookExW(struct qemu_syscall *call)
{
    struct qemu_SetWindowsHookEx *c = (struct qemu_SetWindowsHookEx *)call;

    hook_guest_wrapper = c->wrapper;

    c->super.iret = (ULONG_PTR)set_windows_hook(c->id, c->proc, c->inst, c->tid, TRUE);
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
    call.id = (ULONG_PTR)id;
    call.proc = (ULONG_PTR)proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnhookWindowsHook(struct qemu_syscall *call)
{
    struct qemu_UnhookWindowsHook *c = (struct qemu_UnhookWindowsHook *)call;
    const unsigned int max_hooks = sizeof(installed_hooks[0]) / sizeof(installed_hooks[0][0]);
    INT id = c->id, found = WH_MIN - 1, hook_no;

    WINE_TRACE("\n");

    EnterCriticalSection(&hook_cs);
    for (hook_no = 0; hook_no < max_hooks; ++hook_no)
    {
        if (installed_hooks[id - WH_MIN][hook_no] && installed_hooks[id - WH_MIN][hook_no]->client_cb == c->proc)
        {
            if (found != WH_MIN - 1)
                WINE_ERR("Hook %p found in %d and %d.\n", (void *)c->proc, found, id);

            c->super.iret = UnhookWindowsHook(id, installed_hooks[id - WH_MIN][hook_no]->real_proc);
            if (!c->super.iret)
                WINE_ERR("Failed to uninstall host side hook.\n");
            HeapFree(GetProcessHeap(), 0, installed_hooks[id - WH_MIN][hook_no]);
            installed_hooks[id - WH_MIN][hook_no] = NULL;
            found = TRUE;
        }
    }
    LeaveCriticalSection(&hook_cs);

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
    call.hhook = (ULONG_PTR)hhook;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnhookWindowsHookEx(struct qemu_syscall *call)
{
    struct qemu_UnhookWindowsHookEx *c = (struct qemu_UnhookWindowsHookEx *)call;
    HHOOK hook;
    unsigned int hook_no;
    const unsigned int max_hooks = sizeof(installed_hooks[0]) / sizeof(installed_hooks[0][0]);

    WINE_TRACE("\n");
    hook = QEMU_G2H(c->hhook);
    c->super.iret = UnhookWindowsHookEx(hook);
    WINE_TRACE("Unhooked\n");

    if (c->super.iret)
    {
        INT i;
        INT found = WH_MIN - 1;

        EnterCriticalSection(&hook_cs);
        for (i = WH_MIN; i < WH_MAXHOOK + 1; ++i)
        {
            for (hook_no = 0; hook_no < max_hooks; ++hook_no)
            {
                if (installed_hooks[i - WH_MIN][hook_no] && installed_hooks[i - WH_MIN][hook_no]->hook_id == hook)
                {
                    if (found != WH_MIN - 1)
                        WINE_ERR("Hook %p found in %d and %d.\n", hook, found, i);

                    found = i;
                    HeapFree(GetProcessHeap(), 0, installed_hooks[i - WH_MIN][hook_no]);
                    installed_hooks[i - WH_MIN][hook_no] = NULL;
                }
            }
        }
        LeaveCriticalSection(&hook_cs);

        if (found == WH_MIN - 1)
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
    call.hhook = (ULONG_PTR)hhook;
    call.code = (ULONG_PTR)code;
    call.wparam = (ULONG_PTR)wparam;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CallNextHookEx(struct qemu_syscall *call)
{
    struct qemu_CallNextHookEx *c = (struct qemu_CallNextHookEx *)call;
    LPARAM lp;
    struct hook_conv_data *conv_data;

    WINE_TRACE("\n");
    lp = c->lparam;

#if GUEST_BIT != HOST_BIT
    if (current_hook->type == WH_GETMESSAGE)
    {
        conv_data = CONTAINING_RECORD((void *)lp, struct hook_conv_data, conv.msg32);
        lp = conv_data->orig_lp;
    }
#endif

    c->super.iret = CallNextHookEx(QEMU_G2H(c->hhook), c->code, c->wparam, lp);
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
    call.msg = (ULONG_PTR)msg;
    call.code = (ULONG_PTR)code;

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
    call.msg = (ULONG_PTR)msg;
    call.code = (ULONG_PTR)code;

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

struct qemu_SetWinEventHook_cb
{
    uint64_t func;
    uint64_t hevent;
    uint64_t event;
    uint64_t hwnd;
    uint64_t object_id;
    uint64_t child_id;
    uint64_t thread_id;
    uint64_t event_time;
};

#ifdef QEMU_DLL_GUEST

void __fastcall guest_win_event_wrapper(struct qemu_SetWinEventHook_cb *data)
{
    WINEVENTPROC func = (WINEVENTPROC)(ULONG_PTR)data->func;
    func((HWINEVENTHOOK)(ULONG_PTR)data->hevent, data->event, (HWND)(ULONG_PTR)data->hwnd, data->object_id, data->child_id,
            data->thread_id, data->event_time);
}

WINUSERAPI HWINEVENTHOOK WINAPI SetWinEventHook(DWORD event_min, DWORD event_max, HMODULE inst, WINEVENTPROC proc, DWORD pid, DWORD tid, DWORD flags)
{
    struct qemu_SetWinEventHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETWINEVENTHOOK);
    call.event_min = (ULONG_PTR)event_min;
    call.event_max = (ULONG_PTR)event_max;
    call.inst = (ULONG_PTR)inst;
    call.proc = (ULONG_PTR)proc;
    call.pid = (ULONG_PTR)pid;
    call.tid = (ULONG_PTR)tid;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return (HWINEVENTHOOK)(ULONG_PTR)call.super.iret;
}

#else

struct win_event_entry
{
    struct wine_rb_entry entry;
    HWINEVENTHOOK hook;
    uint64_t guest_func;
};

struct wine_rb_tree win_event_tree;
uint64_t guest_win_event_wrapper;

int win_event_compare(const void *key, const struct wine_rb_entry *entry)
{
    struct win_event_entry *event_entry;

    event_entry = WINE_RB_ENTRY_VALUE(entry, struct win_event_entry, entry);
    if ((HWINEVENTHOOK)key < event_entry->hook) return -1;
    if ((HWINEVENTHOOK)key == event_entry->hook) return 0;
    return 1;
}

static void CALLBACK win_event_host_proc(HWINEVENTHOOK hevent, DWORD event, HWND hwnd,
        LONG object_id, LONG child_id, DWORD thread_id, DWORD event_time)
{
    struct win_event_entry *event_entry;
    struct wine_rb_entry *rb_entry;
    struct qemu_SetWinEventHook_cb call;

    EnterCriticalSection(&hook_cs);

    rb_entry = wine_rb_get(&win_event_tree, hevent);
    if (!rb_entry)
        WINE_ERR("Could not get entry for win event hook %p.\n", hevent);

    event_entry = WINE_RB_ENTRY_VALUE(rb_entry, struct win_event_entry, entry);
    call.func = event_entry->guest_func;

    LeaveCriticalSection(&hook_cs);

    WINE_TRACE("Calling guest hook function 0x%lx(%p, %x, %p, %x, %x, %x, %x).\n",
            (unsigned long)call.func, hevent, event, hwnd, object_id, child_id, thread_id, event_time);
    call.hevent = (ULONG_PTR)hevent;
    call.event = event;
    call.hwnd = (ULONG_PTR)hwnd;
    call.object_id = object_id;
    call.child_id = child_id;
    call.thread_id = thread_id;
    call.event_time = event_time;

    qemu_ops->qemu_execute(QEMU_G2H(guest_win_event_wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest func returned.\n");
}

void qemu_SetWinEventHook(struct qemu_syscall *call)
{
    struct qemu_SetWinEventHook *c = (struct qemu_SetWinEventHook *)call;
    HWINEVENTHOOK hook;
    struct win_event_entry *entry;

    WINE_TRACE("\n");

    if (c->flags & WINEVENT_INCONTEXT && c->pid != GetCurrentProcessId()
            && c->tid != GetCurrentThreadId())
    {
        WINE_FIXME("INCONTEXT hooks in other processes not supported yet.\n");
        c->super.iret = 0;
        return;
    }

    entry = HeapAlloc(GetProcessHeap(), 0, sizeof(*entry));
    if (!entry)
    {
        c->super.iret = 0;
        return;
    }

    EnterCriticalSection(&hook_cs);
    entry->guest_func = c->proc;

    hook = SetWinEventHook(c->event_min, c->event_max, c->inst ? wrapper_mod : NULL,
            c->proc ? win_event_host_proc : NULL, c->pid, c->tid, c->flags);
    c->super.iret = (ULONG_PTR)hook;
    if (!hook)
    {
        HeapFree(GetProcessHeap(), 0, entry);
        LeaveCriticalSection(&hook_cs);
        return;
    }

    entry->hook = hook;
    if (wine_rb_put(&win_event_tree, entry->hook, &entry->entry))
        WINE_ERR("Failed to insert hook entry.\n");

    LeaveCriticalSection(&hook_cs);
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
    call.hEventHook = (ULONG_PTR)hEventHook;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UnhookWinEvent(struct qemu_syscall *call)
{
    struct qemu_UnhookWinEvent *c = (struct qemu_UnhookWinEvent *)call;
    struct win_event_entry *event_entry;
    struct wine_rb_entry *rb_entry;
    HWINEVENTHOOK hook;

    WINE_TRACE("\n");
    hook = QEMU_G2H(c->hEventHook);

    EnterCriticalSection(&hook_cs);
    c->super.iret = UnhookWinEvent(hook);
    if (!c->super.iret)
    {
        LeaveCriticalSection(&hook_cs);
        return;
    }

    rb_entry = wine_rb_get(&win_event_tree, hook);
    if (!rb_entry)
        WINE_ERR("Could not get entry for win event hook %p.\n", hook);

    event_entry = WINE_RB_ENTRY_VALUE(rb_entry, struct win_event_entry, entry);
    wine_rb_remove(&win_event_tree, &event_entry->entry);

    LeaveCriticalSection(&hook_cs);
    HeapFree(GetProcessHeap(), 0, event_entry);
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
    call.event = (ULONG_PTR)event;
    call.hwnd = (ULONG_PTR)hwnd;
    call.object_id = (ULONG_PTR)object_id;
    call.child_id = (ULONG_PTR)child_id;

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
    call.dwEvent = (ULONG_PTR)dwEvent;

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

