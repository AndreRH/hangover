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
#include <d3dx9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "d3dx9_43.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3dx9);
#endif

struct qemu_D3DXVec3TransformCoord
{
    struct qemu_syscall super;
    uint64_t pout;
    uint64_t pv;
    uint64_t pm;
};

#ifdef QEMU_DLL_GUEST

D3DXVECTOR3* WINAPI D3DXVec3TransformCoord(D3DXVECTOR3 *pout, const D3DXVECTOR3 *pv, const D3DXMATRIX *pm)
{
    struct qemu_D3DXVec3TransformCoord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DXVEC3TRANSFORMCOORD);
    call.pout = (uint64_t)pout;
    call.pv = (uint64_t)pv;
    call.pm = (uint64_t)pm;

    qemu_syscall(&call.super);

    return (D3DXVECTOR3 *)call.super.iret;
}

#else

void qemu_D3DXVec3TransformCoord(struct qemu_syscall *call)
{
    struct qemu_D3DXVec3TransformCoord *c = (struct qemu_D3DXVec3TransformCoord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(D3DXVec3TransformCoord(QEMU_G2H(c->pout), QEMU_G2H(c->pv), QEMU_G2H(c->pm)));
}

#endif
