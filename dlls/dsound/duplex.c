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
#include <dsound.h>
#include <dsconf.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dsound.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);
#endif


struct qemu_DirectSoundFullDuplexCreate
{
    struct qemu_syscall super;
    uint64_t capture_dev;
    uint64_t render_dev;
    uint64_t cbufdesc;
    uint64_t bufdesc;
    uint64_t hwnd;
    uint64_t level;
    uint64_t dsfd;
    uint64_t dscb8;
    uint64_t dsb8;
    uint64_t outer_unk;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectSoundFullDuplexCreate(const GUID *capture_dev, const GUID *render_dev, const DSCBUFFERDESC *cbufdesc, const DSBUFFERDESC *bufdesc, HWND hwnd, DWORD level, IDirectSoundFullDuplex **dsfd, IDirectSoundCaptureBuffer8 **dscb8, IDirectSoundBuffer8 **dsb8, IUnknown *outer_unk)
{
    struct qemu_DirectSoundFullDuplexCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDFULLDUPLEXCREATE);
    call.capture_dev = (ULONG_PTR)capture_dev;
    call.render_dev = (ULONG_PTR)render_dev;
    call.cbufdesc = (ULONG_PTR)cbufdesc;
    call.bufdesc = (ULONG_PTR)bufdesc;
    call.hwnd = (ULONG_PTR)hwnd;
    call.level = level;
    call.dsfd = (ULONG_PTR)dsfd;
    call.dscb8 = (ULONG_PTR)dscb8;
    call.dsb8 = (ULONG_PTR)dsb8;
    call.outer_unk = (ULONG_PTR)outer_unk;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DirectSoundFullDuplexCreate(struct qemu_syscall *call)
{
    struct qemu_DirectSoundFullDuplexCreate *c = (struct qemu_DirectSoundFullDuplexCreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectSoundFullDuplexCreate(QEMU_G2H(c->capture_dev), QEMU_G2H(c->render_dev), QEMU_G2H(c->cbufdesc), QEMU_G2H(c->bufdesc), QEMU_G2H(c->hwnd), c->level, QEMU_G2H(c->dsfd), QEMU_G2H(c->dscb8), QEMU_G2H(c->dsb8), QEMU_G2H(c->outer_unk));
}

#endif

