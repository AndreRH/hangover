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
#include <usp10.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_ChoosePixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pfd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR *pfd)
{
    struct qemu_ChoosePixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHOOSEPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;
    call.pfd = (ULONG_PTR)pfd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ChoosePixelFormat(struct qemu_syscall *call)
{
    struct qemu_ChoosePixelFormat *c = (struct qemu_ChoosePixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ChoosePixelFormat(QEMU_G2H(c->hdc), QEMU_G2H(c->pfd));
}

#endif

struct qemu_DescribePixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t fmt;
    uint64_t size;
    uint64_t pfd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DescribePixelFormat(HDC hdc, INT fmt, UINT size, PIXELFORMATDESCRIPTOR *pfd)
{
    struct qemu_DescribePixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESCRIBEPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;
    call.fmt = (ULONG_PTR)fmt;
    call.size = (ULONG_PTR)size;
    call.pfd = (ULONG_PTR)pfd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DescribePixelFormat(struct qemu_syscall *call)
{
    struct qemu_DescribePixelFormat *c = (struct qemu_DescribePixelFormat *)call;
    WINE_TRACE("\n");
    c->super.iret = DescribePixelFormat(QEMU_G2H(c->hdc), c->fmt, c->size, QEMU_G2H(c->pfd));
}

#endif

struct qemu_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetPixelFormat(HDC hdc)
{
    struct qemu_GetPixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_GetPixelFormat *c = (struct qemu_GetPixelFormat *)call;
    WINE_TRACE("\n");
    c->super.iret = GetPixelFormat(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetPixelFormat
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t fmt;
    uint64_t pfd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetPixelFormat(HDC hdc, INT fmt, const PIXELFORMATDESCRIPTOR *pfd)
{
    struct qemu_SetPixelFormat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPIXELFORMAT);
    call.hdc = (ULONG_PTR)hdc;
    call.fmt = (ULONG_PTR)fmt;
    call.pfd = (ULONG_PTR)pfd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_SetPixelFormat *c = (struct qemu_SetPixelFormat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPixelFormat(QEMU_G2H(c->hdc), c->fmt, QEMU_G2H(c->pfd));
}

#endif

struct qemu_SwapBuffers
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SwapBuffers(HDC hdc)
{
    struct qemu_SwapBuffers call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SWAPBUFFERS);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SwapBuffers(struct qemu_syscall *call)
{
    struct qemu_SwapBuffers *c = (struct qemu_SwapBuffers *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SwapBuffers(QEMU_G2H(c->hdc));
}

#endif

