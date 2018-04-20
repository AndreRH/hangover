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
#include <wct.h>
#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

typedef void MD5_CTX;

struct qemu_MD5Init
{
    struct qemu_syscall super;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MD5Init(MD5_CTX *ctx)
{
    struct qemu_MD5Init call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MD5INIT);
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI MD5Init(MD5_CTX *ctx);
void qemu_MD5Init(struct qemu_syscall *call)
{
    struct qemu_MD5Init *c = (struct qemu_MD5Init *)call;
    WINE_TRACE("\n");
    MD5Init(QEMU_G2H(c->ctx));
}

#endif

struct qemu_MD5Update
{
    struct qemu_syscall super;
    uint64_t ctx;
    uint64_t buf;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MD5Update(MD5_CTX *ctx, const unsigned char *buf, unsigned int len)
{
    struct qemu_MD5Update call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MD5UPDATE);
    call.ctx = (ULONG_PTR)ctx;
    call.buf = (ULONG_PTR)buf;
    call.len = len;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI MD5Update(MD5_CTX *ctx, const unsigned char *buf, unsigned int len);
void qemu_MD5Update(struct qemu_syscall *call)
{
    struct qemu_MD5Update *c = (struct qemu_MD5Update *)call;
    WINE_TRACE("\n");
    MD5Update(QEMU_G2H(c->ctx), QEMU_G2H(c->buf), c->len);
}

#endif

struct qemu_MD5Final
{
    struct qemu_syscall super;
    uint64_t ctx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI MD5Final(MD5_CTX *ctx)
{
    struct qemu_MD5Final call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MD5FINAL);
    call.ctx = (ULONG_PTR)ctx;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI MD5Final(MD5_CTX *ctx);
void qemu_MD5Final(struct qemu_syscall *call)
{
    struct qemu_MD5Final *c = (struct qemu_MD5Final *)call;
    WINE_TRACE("\n");
    MD5Final(QEMU_G2H(c->ctx));
}

#endif

