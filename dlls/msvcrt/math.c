/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu___setusermatherr
{
    struct qemu_syscall super;
    uint64_t func;
};


#ifdef QEMU_DLL_GUEST

typedef int (CDECL *MSVCRT_matherr_func)(void *);
static MSVCRT_matherr_func MSVCRT_default_matherr_func = NULL;

static int matherr_callback(void *exception)
{
    if (MSVCRT_default_matherr_func)
        return MSVCRT_default_matherr_func(exception);
    return 0;
}

void CDECL MSVCRT___setusermatherr(void *func)
{
    struct qemu___setusermatherr call;
    call.super.id = QEMU_SYSCALL_ID(CALL___SETUSERMATHERR);
    call.func = (uint64_t)matherr_callback;
    MSVCRT_default_matherr_func = func;

    qemu_syscall(&call.super);
}

#else

static void *matherr_guest_func = 0;

static int host_matherr_callback(void *exception)
{
    WINE_TRACE("Calling guest function at %p.\n", matherr_guest_func);
    if (matherr_guest_func)
        return qemu_ops->qemu_execute(matherr_guest_func, QEMU_H2G(exception));

    WINE_ERR("Unhandled math error!\n");
    return 0;
}

void qemu___setusermatherr(struct qemu_syscall *call)
{
    struct qemu___setusermatherr *c = (struct qemu___setusermatherr *)call;
    WINE_TRACE("\n");
    if (!matherr_guest_func)
    {
        matherr_guest_func = QEMU_G2H(c->func);
        p___setusermatherr(host_matherr_callback);
    }
}

#endif

struct qemu__matherr
{
    struct qemu_syscall super;
    uint64_t exception;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__matherr(void *exception)
{
    struct qemu__matherr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MATHERR);
    call.exception = (uint64_t)exception;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__matherr(struct qemu_syscall *call)
{
    struct qemu__matherr *c = (struct qemu__matherr *)call;
    WINE_TRACE("\n");
    if (!matherr_guest_func)
        WINE_FIXME("Make sure the exception struct makes sense for the host.\n");
    c->super.iret = p__matherr(QEMU_G2H(c->exception));
}

#endif

#ifdef QEMU_DLL_GUEST

/* Copypaste from Wine. */
int CDECL MSVCRT_abs(int n)
{
    return n >= 0 ? n : -n;
}

#endif

struct qemu_cosf
{
    struct qemu_syscall super;
    double x;
};


#ifdef QEMU_DLL_GUEST

float CDECL MSVCRT_cosf(float x)
{
    struct qemu_cosf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COSF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_cosf(struct qemu_syscall *call)
{
    struct qemu_cosf *c = (struct qemu_cosf *)call;
    WINE_TRACE("\n");
    c->super.dret = p_cosf(c->x);
}

#endif

struct qemu_powf
{
    struct qemu_syscall super;
    double base, exp;
};


#ifdef QEMU_DLL_GUEST

float CDECL MSVCRT_powf(float base, float exp)
{
    struct qemu_powf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_POWF);
    call.base = base;
    call.exp = exp;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_powf(struct qemu_syscall *call)
{
    struct qemu_powf *c = (struct qemu_powf *)call;
    WINE_TRACE("\n");
    c->super.dret = p_powf(c->base, c->exp);
}

#endif

struct qemu_sinf
{
    struct qemu_syscall super;
    double x;
};


#ifdef QEMU_DLL_GUEST

float CDECL MSVCRT_sinf(float x)
{
    struct qemu_sinf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SINF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sinf(struct qemu_syscall *call)
{
    struct qemu_sinf *c = (struct qemu_sinf *)call;
    WINE_TRACE("\n");
    c->super.dret = p_sinf(c->x);
}

#endif

struct qemu_sqrtf
{
    struct qemu_syscall super;
    double x;
};


#ifdef QEMU_DLL_GUEST

float CDECL MSVCRT_sqrtf(float x)
{
    struct qemu_sqrtf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SQRTF);
    call.x = x;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_sqrtf(struct qemu_syscall *call)
{
    struct qemu_sqrtf *c = (struct qemu_sqrtf *)call;
    WINE_TRACE("\n");
    c->super.dret = p_sqrtf(c->x);
}

#endif
