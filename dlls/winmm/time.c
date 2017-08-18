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
#include "winmm.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
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
    call.lpTime = (uint64_t)lpTime;
    call.wSize = (uint64_t)wSize;

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
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI timeSetEvent(UINT wDelay, UINT wResol, LPTIMECALLBACK lpFunc, DWORD_PTR dwUser, UINT wFlags)
{
    struct qemu_timeSetEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TIMESETEVENT);
    call.wDelay = (uint64_t)wDelay;
    call.wResol = (uint64_t)wResol;
    call.lpFunc = (uint64_t)lpFunc;
    call.dwUser = (uint64_t)dwUser;
    call.wFlags = (uint64_t)wFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeSetEvent(struct qemu_syscall *call)
{
    struct qemu_timeSetEvent *c = (struct qemu_timeSetEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = timeSetEvent(c->wDelay, c->wResol, QEMU_G2H(c->lpFunc), c->dwUser, c->wFlags);
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
    call.wID = (uint64_t)wID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeKillEvent(struct qemu_syscall *call)
{
    struct qemu_timeKillEvent *c = (struct qemu_timeKillEvent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = timeKillEvent(c->wID);
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
    call.lpCaps = (uint64_t)lpCaps;
    call.wSize = (uint64_t)wSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeGetDevCaps(struct qemu_syscall *call)
{
    struct qemu_timeGetDevCaps *c = (struct qemu_timeGetDevCaps *)call;
    WINE_FIXME("Unverified!\n");
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
    call.wPeriod = (uint64_t)wPeriod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeBeginPeriod(struct qemu_syscall *call)
{
    struct qemu_timeBeginPeriod *c = (struct qemu_timeBeginPeriod *)call;
    WINE_FIXME("Unverified!\n");
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
    call.wPeriod = (uint64_t)wPeriod;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_timeEndPeriod(struct qemu_syscall *call)
{
    struct qemu_timeEndPeriod *c = (struct qemu_timeEndPeriod *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = timeEndPeriod(c->wPeriod);
}

#endif

