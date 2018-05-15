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
#include "qemu_winmm.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <wine/list.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif


struct qemu_timeGetSystemTime
{
    struct qemu_syscall super;
    uint64_t lpTime;
    uint64_t wSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI timeGetSystemTime(LPMMTIME lpTime, UINT wSize)
{
    struct qemu_timeGetSystemTime call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMEGETSYSTEMTIME);
    call.lpTime = (ULONG_PTR)lpTime;
    call.wSize = (ULONG_PTR)wSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeGetSystemTime(struct qemu_syscall *call)
{
    struct qemu_timeGetSystemTime *c = (struct qemu_timeGetSystemTime *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = timeGetSystemTime(QEMU_G2H(c->lpTime), c->wSize);
}

#endif

struct qemu_timeSetEvent
{
    struct qemu_syscall super;
    uint64_t wDelay;
    uint64_t wResol;
    uint64_t lpFunc;
    uint64_t dwUser;
    uint64_t wFlags;
    uint64_t wrapper;
};

struct qemu_timeSetEvent_cb
{
    uint64_t func;
    uint64_t id;
    uint64_t msg;
    uint64_t user;
    uint64_t dw1;
    uint64_t dw2;
};

#ifdef QEMU_DLL_GUEST

static void __fastcall qemu_timeSetEvent_guest_proc(struct qemu_timeSetEvent_cb *data)
{
    LPTIMECALLBACK func = (LPTIMECALLBACK)(ULONG_PTR)data->func;
    func(data->id, data->msg, data->user, data->dw1, data->dw2);
}

WINBASEAPI MMRESULT WINAPI timeSetEvent(UINT wDelay, UINT wResol, LPTIMECALLBACK lpFunc, DWORD_PTR dwUser, UINT wFlags)
{
    struct qemu_timeSetEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMESETEVENT);
    call.wDelay = (ULONG_PTR)wDelay;
    call.wResol = (ULONG_PTR)wResol;
    call.lpFunc = (ULONG_PTR)lpFunc;
    call.dwUser = (ULONG_PTR)dwUser;
    call.wFlags = (ULONG_PTR)wFlags;
    call.wrapper = (ULONG_PTR)qemu_timeSetEvent_guest_proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static CRITICAL_SECTION timeSetEvent_cs = {0, -1, 0, 0, 0, 0};
static struct list timeSetEvent_list = LIST_INIT(timeSetEvent_list);

struct qemu_qemu_timeSetEvent_host_data
{
    uint64_t guest_func, guest_data;
    uint64_t wrapper;
    UINT id;
    struct list entry;
    WORD flags;
};

static void CALLBACK qemu_timeSetEvent_host_proc(UINT id, UINT msg, DWORD_PTR user, DWORD_PTR dw1, DWORD_PTR dw2)
{
    struct qemu_qemu_timeSetEvent_host_data *ctx = (struct qemu_qemu_timeSetEvent_host_data *)user;
    struct qemu_timeSetEvent_cb call;
    uint64_t wrapper;

    call.func = ctx->guest_func;
    call.id = id;
    call.msg = msg;
    call.user = ctx->guest_data;
    call.dw1 = dw1;
    call.dw2 = dw2;
    wrapper = ctx->wrapper;

    if (!(ctx->flags & TIME_PERIODIC))
    {
        EnterCriticalSection(&timeSetEvent_cs);
        list_remove(&ctx->entry);
        LeaveCriticalSection(&timeSetEvent_cs);

        WINE_TRACE("Deleting existing callback data %p / id %u.\n", ctx, ctx->id);
        HeapFree(GetProcessHeap(), 0, ctx);
    }

    WINE_TRACE("Calling guest function %p(%u, %u, %p, %p, %p).\n", (void *)call.func,
            (unsigned int)call.id, (unsigned int)call.msg, (void *)call.user,
            (void *)call.dw1, (void *)call.dw2);
    qemu_ops->qemu_execute(QEMU_G2H(wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest function returned.\n");
}

static HANDLE hack;

void qemu_timeSetEvent(struct qemu_syscall *call)
{
    struct qemu_timeSetEvent *c = (struct qemu_timeSetEvent *)call;
    struct qemu_qemu_timeSetEvent_host_data *ctx;

    if (!hack)
    {
        MMRESULT hack_timer;
        hack = CreateEventA(NULL, FALSE, FALSE, NULL);
        hack_timer = timeSetEvent(65534, 1, hack, 0, TIME_CALLBACK_EVENT_SET | TIME_PERIODIC);
        WINE_ERR("hack timer %x\n", hack_timer);
    }
    WINE_TRACE("\n");
    if (c->wFlags & (TIME_CALLBACK_EVENT_SET | TIME_CALLBACK_EVENT_PULSE))
    {
        WINE_TRACE("Event based timer.\n");
        c->super.iret = timeSetEvent(c->wDelay, c->wResol,
                QEMU_G2H(c->lpFunc), (DWORD_PTR)ctx, c->wFlags);
        return;
    }

    ctx = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ctx));
    WINE_TRACE("Alloc timer %p\n", ctx);

    ctx->guest_func = c->lpFunc;
    ctx->guest_data = c->dwUser;
    ctx->wrapper = c->wrapper;
    ctx->flags = c->wFlags;

    EnterCriticalSection(&timeSetEvent_cs);
    list_add_tail(&timeSetEvent_list, &ctx->entry);
    LeaveCriticalSection(&timeSetEvent_cs);

    c->super.iret = timeSetEvent(c->wDelay, c->wResol,
            c->lpFunc ? qemu_timeSetEvent_host_proc : NULL, (DWORD_PTR)ctx,
            c->wFlags | TIME_KILL_SYNCHRONOUS);
    ctx->id = c->super.iret;

    if (!c->super.iret)
    {
        WINE_WARN("Creating the host timer failed.\n");
        EnterCriticalSection(&timeSetEvent_cs);
        list_remove(&ctx->entry);
        LeaveCriticalSection(&timeSetEvent_cs);
        HeapFree(GetProcessHeap(), 0, ctx);
    }
}

#endif

struct qemu_timeKillEvent
{
    struct qemu_syscall super;
    uint64_t wID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI timeKillEvent(UINT wID)
{
    struct qemu_timeKillEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMEKILLEVENT);
    call.wID = (ULONG_PTR)wID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeKillEvent(struct qemu_syscall *call)
{
    struct qemu_timeKillEvent *c = (struct qemu_timeKillEvent *)call;
    struct qemu_qemu_timeSetEvent_host_data *event;

    WINE_TRACE("\n");
    EnterCriticalSection(&timeSetEvent_cs);
    c->super.iret = timeKillEvent(c->wID);

    if (c->super.iret == TIMERR_NOERROR)
    {
        LIST_FOR_EACH_ENTRY(event, &timeSetEvent_list, struct qemu_qemu_timeSetEvent_host_data, entry)
        {
            if (event->id == c->wID)
            {
                WINE_TRACE("Deleting existing callback data %p / id %u.\n", event, event->id);
                list_remove(&event->entry);
                LeaveCriticalSection(&timeSetEvent_cs);
                HeapFree(GetProcessHeap(), 0, event);
                return;
            }
        }
        /* This happens when the timer is using an event instead of a callback. */
        WINE_WARN("Did not find structure for deleted event %u.\n", (unsigned int)c->wID);
    }
    LeaveCriticalSection(&timeSetEvent_cs);
}

#endif

struct qemu_timeGetDevCaps
{
    struct qemu_syscall super;
    uint64_t lpCaps;
    uint64_t wSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI timeGetDevCaps(LPTIMECAPS lpCaps, UINT wSize)
{
    struct qemu_timeGetDevCaps call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMEGETDEVCAPS);
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.wSize = wSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeGetDevCaps(struct qemu_syscall *call)
{
    struct qemu_timeGetDevCaps *c = (struct qemu_timeGetDevCaps *)call;
    WINE_TRACE("\n");
    c->super.iret = timeGetDevCaps(QEMU_G2H(c->lpCaps), c->wSize);
}

#endif

struct qemu_timeBeginPeriod
{
    struct qemu_syscall super;
    uint64_t wPeriod;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI timeBeginPeriod(UINT wPeriod)
{
    struct qemu_timeBeginPeriod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMEBEGINPERIOD);
    call.wPeriod = wPeriod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeBeginPeriod(struct qemu_syscall *call)
{
    struct qemu_timeBeginPeriod *c = (struct qemu_timeBeginPeriod *)call;
    WINE_TRACE("\n");
    c->super.iret = timeBeginPeriod(c->wPeriod);
}

#endif

struct qemu_timeEndPeriod
{
    struct qemu_syscall super;
    uint64_t wPeriod;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI timeEndPeriod(UINT wPeriod)
{
    struct qemu_timeEndPeriod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMEENDPERIOD);
    call.wPeriod = (ULONG_PTR)wPeriod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeEndPeriod(struct qemu_syscall *call)
{
    struct qemu_timeEndPeriod *c = (struct qemu_timeEndPeriod *)call;
    WINE_TRACE("\n");
    c->super.iret = timeEndPeriod(c->wPeriod);
}

#endif

