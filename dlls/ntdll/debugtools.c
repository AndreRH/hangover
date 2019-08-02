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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"


#ifdef QEMU_DLL_GUEST
struct __wine_debug_channel;
enum __wine_debug_class
{
    __WINE_DBCL_FIXME,
    __WINE_DBCL_ERR,
    __WINE_DBCL_WARN,
    __WINE_DBCL_TRACE,
    
    __WINE_DBCL_INIT = 7  /* lazy init flag */
};

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu___wine_dbg_strdup
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI const char * __cdecl __wine_dbg_strdup(const char *str)
{
    struct qemu___wine_dbg_strdup call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WINE_DBG_STRDUP);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (const char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu___wine_dbg_strdup(struct qemu_syscall *call)
{
    struct qemu___wine_dbg_strdup *c = (struct qemu___wine_dbg_strdup *)call;
    WINE_TRACE("\n");
    c->super.iret = __wine_dbg_strdup(QEMU_G2H(c->str));
}

#endif

struct qemu___wine_dbg_output
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int __cdecl __wine_dbg_output(const char *str)
{
    struct qemu___wine_dbg_output call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WINE_DBG_OUTPUT);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___wine_dbg_output(struct qemu_syscall *call)
{
    struct qemu___wine_dbg_output *c = (struct qemu___wine_dbg_output *)call;
    WINE_TRACE("\n");
    c->super.iret = __wine_dbg_output(QEMU_G2H(c->str));
}

#endif

struct qemu___wine_dbg_get_channel_flags
{
    struct qemu_syscall super;
    uint64_t channel;
};

#ifdef QEMU_DLL_GUEST

unsigned char __cdecl __wine_dbg_get_channel_flags(struct __wine_debug_channel *channel)
{
    struct qemu___wine_dbg_get_channel_flags call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WINE_DBG_GET_CHANNEL_FLAGS);
    call.channel = (ULONG_PTR)channel;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___wine_dbg_get_channel_flags(struct qemu_syscall *call)
{
    struct qemu___wine_dbg_get_channel_flags *c = (struct qemu___wine_dbg_get_channel_flags *)call;
    WINE_TRACE("\n");
    c->super.iret = __wine_dbg_get_channel_flags(QEMU_G2H(c->channel));
}

#endif

struct qemu___wine_dbg_header
{
    struct qemu_syscall super;
    uint64_t cls;
    uint64_t channel;
    uint64_t function;
};

#ifdef QEMU_DLL_GUEST

int __cdecl __wine_dbg_header(enum __wine_debug_class cls, struct __wine_debug_channel *channel, const char *function)
{
    struct qemu___wine_dbg_header call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WINE_DBG_HEADER);
    call.cls = cls;
    call.channel = (ULONG_PTR)channel;
    call.function = (ULONG_PTR)function;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___wine_dbg_header(struct qemu_syscall *call)
{
    struct qemu___wine_dbg_header *c = (struct qemu___wine_dbg_header *)call;
    WINE_TRACE("\n");
    c->super.iret = __wine_dbg_header(c->cls, QEMU_G2H(c->channel), QEMU_G2H(c->function));
}

#endif

