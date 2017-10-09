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
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif


struct qemu_PlaySoundA
{
    struct qemu_syscall super;
    uint64_t pszSoundA;
    uint64_t hmod;
    uint64_t fdwSound;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PlaySoundA(LPCSTR pszSoundA, HMODULE hmod, DWORD fdwSound)
{
    struct qemu_PlaySoundA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLAYSOUNDA);
    call.pszSoundA = (ULONG_PTR)pszSoundA;
    call.hmod = (ULONG_PTR)hmod;
    call.fdwSound = (ULONG_PTR)fdwSound;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlaySoundA(struct qemu_syscall *call)
{
    struct qemu_PlaySoundA *c = (struct qemu_PlaySoundA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PlaySoundA(QEMU_G2H(c->pszSoundA), QEMU_G2H(c->hmod), c->fdwSound);
}

#endif

struct qemu_PlaySoundW
{
    struct qemu_syscall super;
    uint64_t pszSoundW;
    uint64_t hmod;
    uint64_t fdwSound;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI PlaySoundW(LPCWSTR pszSoundW, HMODULE hmod, DWORD fdwSound)
{
    struct qemu_PlaySoundW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLAYSOUNDW);
    call.pszSoundW = (ULONG_PTR)pszSoundW;
    call.hmod = (ULONG_PTR)hmod;
    call.fdwSound = (ULONG_PTR)fdwSound;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlaySoundW(struct qemu_syscall *call)
{
    struct qemu_PlaySoundW *c = (struct qemu_PlaySoundW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PlaySoundW(QEMU_G2H(c->pszSoundW), QEMU_G2H(c->hmod), c->fdwSound);
}

#endif

struct qemu_sndPlaySoundA
{
    struct qemu_syscall super;
    uint64_t pszSoundA;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI sndPlaySoundA(LPCSTR pszSoundA, UINT uFlags)
{
    struct qemu_sndPlaySoundA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SNDPLAYSOUNDA);
    call.pszSoundA = (ULONG_PTR)pszSoundA;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_sndPlaySoundA(struct qemu_syscall *call)
{
    struct qemu_sndPlaySoundA *c = (struct qemu_sndPlaySoundA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = sndPlaySoundA(QEMU_G2H(c->pszSoundA), c->uFlags);
}

#endif

struct qemu_sndPlaySoundW
{
    struct qemu_syscall super;
    uint64_t pszSound;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI sndPlaySoundW(LPCWSTR pszSound, UINT uFlags)
{
    struct qemu_sndPlaySoundW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SNDPLAYSOUNDW);
    call.pszSound = (ULONG_PTR)pszSound;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_sndPlaySoundW(struct qemu_syscall *call)
{
    struct qemu_sndPlaySoundW *c = (struct qemu_sndPlaySoundW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = sndPlaySoundW(QEMU_G2H(c->pszSound), c->uFlags);
}

#endif

struct qemu_mmsystemGetVersion
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mmsystemGetVersion(void)
{
    struct qemu_mmsystemGetVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMSYSTEMGETVERSION);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmsystemGetVersion(struct qemu_syscall *call)
{
    struct qemu_mmsystemGetVersion *c = (struct qemu_mmsystemGetVersion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmsystemGetVersion();
}

#endif

