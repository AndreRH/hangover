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


struct qemu_joyConfigChanged
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyConfigChanged(DWORD flags)
{
    struct qemu_joyConfigChanged call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYCONFIGCHANGED);
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add joyConfigChanged to Wine headers? */
extern MMRESULT WINAPI joyConfigChanged(DWORD flags);
void qemu_joyConfigChanged(struct qemu_syscall *call)
{
    struct qemu_joyConfigChanged *c = (struct qemu_joyConfigChanged *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyConfigChanged(c->flags);
}

#endif

struct qemu_joyGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI joyGetNumDevs(void)
{
    struct qemu_joyGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_joyGetNumDevs *c = (struct qemu_joyGetNumDevs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyGetNumDevs();
}

#endif

struct qemu_joyGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t wID;
    uint64_t lpCaps;
    uint64_t wSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyGetDevCapsW(UINT_PTR wID, LPJOYCAPSW lpCaps, UINT wSize)
{
    struct qemu_joyGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYGETDEVCAPSW);
    call.wID = (uint64_t)wID;
    call.lpCaps = (uint64_t)lpCaps;
    call.wSize = (uint64_t)wSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_joyGetDevCapsW *c = (struct qemu_joyGetDevCapsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyGetDevCapsW(c->wID, QEMU_G2H(c->lpCaps), c->wSize);
}

#endif

struct qemu_joyGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t wID;
    uint64_t lpCaps;
    uint64_t wSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyGetDevCapsA(UINT_PTR wID, LPJOYCAPSA lpCaps, UINT wSize)
{
    struct qemu_joyGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYGETDEVCAPSA);
    call.wID = (uint64_t)wID;
    call.lpCaps = (uint64_t)lpCaps;
    call.wSize = (uint64_t)wSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_joyGetDevCapsA *c = (struct qemu_joyGetDevCapsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyGetDevCapsA(c->wID, QEMU_G2H(c->lpCaps), c->wSize);
}

#endif

struct qemu_joyGetPosEx
{
    struct qemu_syscall super;
    uint64_t wID;
    uint64_t lpInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyGetPosEx(UINT wID, LPJOYINFOEX lpInfo)
{
    struct qemu_joyGetPosEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYGETPOSEX);
    call.wID = (uint64_t)wID;
    call.lpInfo = (uint64_t)lpInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyGetPosEx(struct qemu_syscall *call)
{
    struct qemu_joyGetPosEx *c = (struct qemu_joyGetPosEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyGetPosEx(c->wID, QEMU_G2H(c->lpInfo));
}

#endif

struct qemu_joyGetPos
{
    struct qemu_syscall super;
    uint64_t wID;
    uint64_t lpInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyGetPos(UINT wID, LPJOYINFO lpInfo)
{
    struct qemu_joyGetPos call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYGETPOS);
    call.wID = (uint64_t)wID;
    call.lpInfo = (uint64_t)lpInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyGetPos(struct qemu_syscall *call)
{
    struct qemu_joyGetPos *c = (struct qemu_joyGetPos *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyGetPos(c->wID, QEMU_G2H(c->lpInfo));
}

#endif

struct qemu_joyGetThreshold
{
    struct qemu_syscall super;
    uint64_t wID;
    uint64_t lpThreshold;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyGetThreshold(UINT wID, LPUINT lpThreshold)
{
    struct qemu_joyGetThreshold call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYGETTHRESHOLD);
    call.wID = (uint64_t)wID;
    call.lpThreshold = (uint64_t)lpThreshold;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyGetThreshold(struct qemu_syscall *call)
{
    struct qemu_joyGetThreshold *c = (struct qemu_joyGetThreshold *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyGetThreshold(c->wID, QEMU_G2H(c->lpThreshold));
}

#endif

struct qemu_joyReleaseCapture
{
    struct qemu_syscall super;
    uint64_t wID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joyReleaseCapture(UINT wID)
{
    struct qemu_joyReleaseCapture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYRELEASECAPTURE);
    call.wID = (uint64_t)wID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joyReleaseCapture(struct qemu_syscall *call)
{
    struct qemu_joyReleaseCapture *c = (struct qemu_joyReleaseCapture *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joyReleaseCapture(c->wID);
}

#endif

struct qemu_joySetCapture
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t wID;
    uint64_t wPeriod;
    uint64_t bChanged;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joySetCapture(HWND hWnd, UINT wID, UINT wPeriod, BOOL bChanged)
{
    struct qemu_joySetCapture call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYSETCAPTURE);
    call.hWnd = (uint64_t)hWnd;
    call.wID = (uint64_t)wID;
    call.wPeriod = (uint64_t)wPeriod;
    call.bChanged = (uint64_t)bChanged;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joySetCapture(struct qemu_syscall *call)
{
    struct qemu_joySetCapture *c = (struct qemu_joySetCapture *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joySetCapture(QEMU_G2H(c->hWnd), c->wID, c->wPeriod, c->bChanged);
}

#endif

struct qemu_joySetThreshold
{
    struct qemu_syscall super;
    uint64_t wID;
    uint64_t wThreshold;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI joySetThreshold(UINT wID, UINT wThreshold)
{
    struct qemu_joySetThreshold call;
    call.super.id = QEMU_SYSCALL_ID(CALL_JOYSETTHRESHOLD);
    call.wID = (uint64_t)wID;
    call.wThreshold = (uint64_t)wThreshold;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_joySetThreshold(struct qemu_syscall *call)
{
    struct qemu_joySetThreshold *c = (struct qemu_joySetThreshold *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = joySetThreshold(c->wID, c->wThreshold);
}

#endif

