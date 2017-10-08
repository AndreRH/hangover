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
#include <ntdef.h>
#include <ntsecapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

typedef void MD4_CTX;

struct qemu_MD4Init
{
    struct qemu_syscall super;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MD4Init(MD4_CTX *ctx)
{
    struct qemu_MD4Init call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MD4INIT);
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI MD4Init( MD4_CTX *ctx );
void qemu_MD4Init(struct qemu_syscall *call)
{
    struct qemu_MD4Init *c = (struct qemu_MD4Init *)call;
    WINE_FIXME("Unverified!\n");
    MD4Init(QEMU_G2H(c->ctx));
}

#endif

struct qemu_MD4Update
{
    struct qemu_syscall super;
    uint64_t ctx;
    uint64_t buf;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MD4Update(MD4_CTX *ctx, const unsigned char *buf, unsigned int len)
{
    struct qemu_MD4Update call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MD4UPDATE);
    call.ctx = (ULONG_PTR)ctx;
    call.buf = (ULONG_PTR)buf;
    call.len = len;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI MD4Update( MD4_CTX *ctx, const unsigned char *buf, unsigned int len );
void qemu_MD4Update(struct qemu_syscall *call)
{
    struct qemu_MD4Update *c = (struct qemu_MD4Update *)call;
    WINE_FIXME("Unverified!\n");
    MD4Update(QEMU_G2H(c->ctx), QEMU_G2H(c->buf), c->len);
}

#endif

struct qemu_MD4Final
{
    struct qemu_syscall super;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MD4Final(MD4_CTX *ctx)
{
    struct qemu_MD4Final call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MD4FINAL);
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI MD4Final( MD4_CTX *ctx );
void qemu_MD4Final(struct qemu_syscall *call)
{
    struct qemu_MD4Final *c = (struct qemu_MD4Final *)call;
    WINE_FIXME("Unverified!\n");
    MD4Final(QEMU_G2H(c->ctx));
}

#endif

struct qemu_SystemFunction007
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t hash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction007(const UNICODE_STRING *string, LPBYTE hash)
{
    struct qemu_SystemFunction007 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION007);
    call.string = (ULONG_PTR)string;
    call.hash = (ULONG_PTR)hash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction007(const UNICODE_STRING *string, LPBYTE hash);
void qemu_SystemFunction007(struct qemu_syscall *call)
{
    struct qemu_SystemFunction007 *c = (struct qemu_SystemFunction007 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction007(QEMU_G2H(c->string), QEMU_G2H(c->hash));
}

#endif

struct qemu_SystemFunction010
{
    struct qemu_syscall super;
    uint64_t unknown;
    uint64_t data;
    uint64_t hash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction010(LPVOID unknown, const BYTE *data, LPBYTE hash)
{
    struct qemu_SystemFunction010 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION010);
    call.unknown = (ULONG_PTR)unknown;
    call.data = (ULONG_PTR)data;
    call.hash = (ULONG_PTR)hash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction010(LPVOID unknown, const BYTE *data, LPBYTE hash);
void qemu_SystemFunction010(struct qemu_syscall *call)
{
    struct qemu_SystemFunction010 *c = (struct qemu_SystemFunction010 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction010(QEMU_G2H(c->unknown), QEMU_G2H(c->data), QEMU_G2H(c->hash));
}

#endif

