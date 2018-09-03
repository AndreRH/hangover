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

#define COBJMACROS

#include <windows.h>
#include <wincodec.h>

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#include <list.h>
#else
#include <wine/debug.h>
#include <wine/list.h>
#endif

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICMapGuidToShortName
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t len;
    uint64_t name;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICMapGuidToShortName(REFGUID guid, UINT len, WCHAR *name, UINT *ret_len)
{
    struct qemu_WICMapGuidToShortName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICMAPGUIDTOSHORTNAME);
    call.guid = (ULONG_PTR)guid;
    call.len = len;
    call.name = (ULONG_PTR)name;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMapGuidToShortName(struct qemu_syscall *call)
{
    struct qemu_WICMapGuidToShortName *c = (struct qemu_WICMapGuidToShortName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICMapGuidToShortName(QEMU_G2H(c->guid), c->len, QEMU_G2H(c->name), QEMU_G2H(c->ret_len));
}

#endif

struct qemu_WICMapShortNameToGuid
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICMapShortNameToGuid(PCWSTR name, GUID *guid)
{
    struct qemu_WICMapShortNameToGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICMAPSHORTNAMETOGUID);
    call.name = (ULONG_PTR)name;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMapShortNameToGuid(struct qemu_syscall *call)
{
    struct qemu_WICMapShortNameToGuid *c = (struct qemu_WICMapShortNameToGuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICMapShortNameToGuid(QEMU_G2H(c->name), QEMU_G2H(c->guid));
}

#endif

struct qemu_WICMapSchemaToName
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t schema;
    uint64_t len;
    uint64_t name;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICMapSchemaToName(REFGUID format, LPWSTR schema, UINT len, WCHAR *name, UINT *ret_len)
{
    struct qemu_WICMapSchemaToName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICMAPSCHEMATONAME);
    call.format = (ULONG_PTR)format;
    call.schema = (ULONG_PTR)schema;
    call.len = len;
    call.name = (ULONG_PTR)name;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMapSchemaToName(struct qemu_syscall *call)
{
    struct qemu_WICMapSchemaToName *c = (struct qemu_WICMapSchemaToName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICMapSchemaToName(QEMU_G2H(c->format), QEMU_G2H(c->schema), c->len,
            QEMU_G2H(c->name), QEMU_G2H(c->ret_len));
}

#endif

