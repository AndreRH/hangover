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

#include "windows-user-services.h"
#include "dll_list.h"
#include "advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

struct qemu_RegCloseKey
{
    struct qemu_syscall super;
    uint64_t key;
};

#ifdef QEMU_DLL_GUEST

WINADVAPI LONG WINAPI RegCloseKey(HKEY key)
{
    struct qemu_RegCloseKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGCLOSEKEY);
    call.key = (uint64_t)key;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegCloseKey(struct qemu_syscall *call)
{
    struct qemu_RegCloseKey *c = (struct qemu_RegCloseKey *)call;
    WINE_TRACE("\n");
    c->super.iret = RegCloseKey((HANDLE)c->key);
}

#endif

struct qemu_RegOpenKeyW
{
    struct qemu_syscall super;
    uint64_t key;
    uint64_t subkey;
    uint64_t result;
};

#ifdef QEMU_DLL_GUEST

WINADVAPI LONG WINAPI RegOpenKeyW(HKEY key, const wchar_t *subkey, HKEY *result)
{
    struct qemu_RegOpenKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGOPENKEY);
    call.key = (uint64_t)key;
    call.subkey = (uint64_t)subkey;
    call.result = (uint64_t)result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegOpenKeyW(struct qemu_syscall *call)
{
    struct qemu_RegOpenKeyW *c = (struct qemu_RegOpenKeyW *)call;
    WINE_TRACE("\n");
    c->super.iret = RegOpenKeyW((HANDLE)c->key, QEMU_G2H(c->subkey), QEMU_G2H(c->result));
}

#endif

struct qemu_RegQueryValueExW
{
    struct qemu_syscall super;
    uint64_t key;
    uint64_t name;
    uint64_t reserved;
    uint64_t type;
    uint64_t data;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINADVAPI LONG WINAPI RegQueryValueExW(HKEY key, const wchar_t *name, DWORD *reserved,
        DWORD *type, BYTE *data, DWORD *count)
{
    struct qemu_RegQueryValueExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REGQUERYVALUEEXW);
    call.key = (uint64_t)key;
    call.name = (uint64_t)name;
    call.reserved = (uint64_t)reserved;
    call.type = (uint64_t)type;
    call.data = (uint64_t)data;
    call.count = (uint64_t)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RegQueryValueExW(struct qemu_syscall *call)
{
    struct qemu_RegQueryValueExW *c = (struct qemu_RegQueryValueExW *)call;
    WINE_TRACE("\n");
    c->super.iret = RegQueryValueExW((HANDLE)c->key, QEMU_G2H(c->name), QEMU_G2H(c->reserved),
            QEMU_G2H(c->type), QEMU_G2H(c->data), QEMU_G2H(c->count));
}

#endif
