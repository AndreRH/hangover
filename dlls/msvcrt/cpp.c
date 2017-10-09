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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__CxxThrowException(void *object, const void *type)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__CXXTHROWEXCEPTION);

    qemu_syscall(&call);
}

#else

void qemu__CxxThrowException(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_terminate(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_TERMINATE);

    qemu_syscall(&call);
}

#else

void qemu_terminate(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    p_terminate();
}

#endif

struct qemu_type_info_dtor
{
    struct qemu_syscall super;
    uint64_t this;
};

#ifdef QEMU_DLL_GUEST

void __thiscall MSVCRT_type_info_dtor(void * _this)
{
    struct qemu_type_info_dtor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TYPE_INFO_DTOR);
    call.this = (uint64_t)_this;

    qemu_syscall(&call.super);
}

#else

void qemu_type_info_dtor(struct qemu_syscall *call)
{
    struct qemu_type_info_dtor *c = (struct qemu_type_info_dtor *)call;
    WINE_FIXME("Unverified!\n");
    p_type_info_dtor(QEMU_G2H(c->this));
}

#endif
