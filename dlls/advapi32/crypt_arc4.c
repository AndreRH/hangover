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

struct qemu_SystemFunction032
{
    struct qemu_syscall super;
    uint64_t data;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction032(struct ustring *data, const struct ustring *key)
{
    struct qemu_SystemFunction032 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION032);
    call.data = (ULONG_PTR)data;
    call.key = (ULONG_PTR)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction032(struct ustring *data, const struct ustring *key);
void qemu_SystemFunction032(struct qemu_syscall *call)
{
    struct qemu_SystemFunction032 *c = (struct qemu_SystemFunction032 *)call;
    struct ustring key_stack, *key = &key_stack;
    struct ustring data_stack, *data = &data_stack;
    struct qemu_ustring *key32, *data32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    key = QEMU_G2H(c->key);
    data = QEMU_G2H(c->data);
#else
    key32 = QEMU_G2H(c->key);
    if (key32)
    {
        key->Length = key32->Length;
        key->MaximumLength = key32->MaximumLength;
        key->Buffer = (unsigned char *)(ULONG_PTR)key32->Buffer;
    }
    else
    {
        key = NULL;
    }

    data32 = QEMU_G2H(c->data);
    if (data32)
    {
        data->Length = data32->Length;
        data->MaximumLength = data32->MaximumLength;
        data->Buffer = (unsigned char *)(ULONG_PTR)data32->Buffer;
    }
    else
    {
        data = NULL;
    }
#endif

    c->super.iret = SystemFunction032(data, key);

#if GUEST_BIT != HOST_BIT
    if (data32)
        data32->Length = data->Length;
#endif
}

#endif

