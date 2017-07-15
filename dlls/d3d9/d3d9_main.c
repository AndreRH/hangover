/*
 * Copyright 2017 Stefan Dösinger
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
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_Direct3DCreate9
{
    struct qemu_syscall super;
    uint64_t sdk_version;
};

#ifdef QEMU_DLL_GUEST

IDirect3D9 * WINAPI Direct3DCreate9(UINT sdk_version)
{
    struct qemu_Direct3DCreate9 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECT3DCREATE9);
    call.sdk_version = sdk_version;

    qemu_syscall(&call.super);

    return (IDirect3D9 *)call.super.iret;
}

#else

void qemu_Direct3DCreate9(struct qemu_syscall *call)
{
    struct qemu_Direct3DCreate9 *c = (struct qemu_Direct3DCreate9 *)call;
    WINE_FIXME("This aint gonna work!\n");
    c->super.iret = (uint64_t)Direct3DCreate9(c->sdk_version);
}

#endif
