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
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

typedef void *PSHA_CTX;

struct qemu_A_SHAInit
{
    struct qemu_syscall super;
    uint64_t Context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI A_SHAInit(PSHA_CTX Context)
{
    struct qemu_A_SHAInit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_A_SHAINIT);
    call.Context = (ULONG_PTR)Context;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI A_SHAInit(PSHA_CTX Context);
void qemu_A_SHAInit(struct qemu_syscall *call)
{
    struct qemu_A_SHAInit *c = (struct qemu_A_SHAInit *)call;
    WINE_TRACE("\n");
    A_SHAInit(QEMU_G2H(c->Context));
}

#endif

struct qemu_A_SHAUpdate
{
    struct qemu_syscall super;
    uint64_t Context;
    uint64_t Buffer;
    uint64_t BufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI A_SHAUpdate(PSHA_CTX Context, const unsigned char *Buffer, UINT BufferSize)
{
    struct qemu_A_SHAUpdate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_A_SHAUPDATE);
    call.Context = (ULONG_PTR)Context;
    call.Buffer = (ULONG_PTR)Buffer;
    call.BufferSize = BufferSize;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI A_SHAUpdate(PSHA_CTX Context, const unsigned char *Buffer, UINT BufferSize);
void qemu_A_SHAUpdate(struct qemu_syscall *call)
{
    struct qemu_A_SHAUpdate *c = (struct qemu_A_SHAUpdate *)call;
    WINE_TRACE("\n");
    A_SHAUpdate(QEMU_G2H(c->Context), QEMU_G2H(c->Buffer), c->BufferSize);
}

#endif

struct qemu_A_SHAFinal
{
    struct qemu_syscall super;
    uint64_t Context;
    uint64_t Result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI A_SHAFinal(PSHA_CTX Context, PULONG Result)
{
    struct qemu_A_SHAFinal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_A_SHAFINAL);
    call.Context = (ULONG_PTR)Context;
    call.Result = (ULONG_PTR)Result;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI A_SHAFinal(PSHA_CTX Context, PULONG Result);
void qemu_A_SHAFinal(struct qemu_syscall *call)
{
    struct qemu_A_SHAFinal *c = (struct qemu_A_SHAFinal *)call;
    WINE_TRACE("\n");
    A_SHAFinal(QEMU_G2H(c->Context), QEMU_G2H(c->Result));
}

#endif

