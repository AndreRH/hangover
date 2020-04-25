/*
 * Copyright 2017 André Hentschel
 * Copyright 2019 Stefan Dösinger for CodeWeavers
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

#include "thunk/qemu_winternl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST
typedef struct _LDR_RESOURCE_INFO LDR_RESOURCE_INFO;
#else
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_LdrFindResourceDirectory_U
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t info;
    uint64_t level;
    uint64_t dir;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrFindResourceDirectory_U(HMODULE hmod, const LDR_RESOURCE_INFO *info, ULONG level,
        const IMAGE_RESOURCE_DIRECTORY **dir)
{
    struct qemu_LdrFindResourceDirectory_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRFINDRESOURCEDIRECTORY_U);
    call.hmod = (ULONG_PTR)hmod;
    call.info = (ULONG_PTR)info;
    call.level = level;
    call.dir = (ULONG_PTR)dir;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrFindResourceDirectory_U(struct qemu_syscall *call)
{
    struct qemu_LdrFindResourceDirectory_U *c = (struct qemu_LdrFindResourceDirectory_U *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrFindResourceDirectory_U(QEMU_G2H(c->hmod), QEMU_G2H(c->info), c->level, QEMU_G2H(c->dir));
}

#endif

struct qemu_LdrFindResource_U
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t info;
    uint64_t level;
    uint64_t entry;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrFindResource_U(HMODULE hmod, const LDR_RESOURCE_INFO *info, ULONG level,
        const IMAGE_RESOURCE_DATA_ENTRY **entry)
{
    struct qemu_LdrFindResource_U call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRFINDRESOURCE_U);
    call.hmod = (ULONG_PTR)hmod;
    call.info = (ULONG_PTR)info;
    call.level = level;
    call.entry = (ULONG_PTR)entry;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrFindResource_U(struct qemu_syscall *call)
{
    struct qemu_LdrFindResource_U *c = (struct qemu_LdrFindResource_U *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrFindResource_U(QEMU_G2H(c->hmod), QEMU_G2H(c->info), c->level, QEMU_G2H(c->entry));
}

#endif

struct qemu_LdrAccessResource
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t entry;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LdrAccessResource(HMODULE hmod, const IMAGE_RESOURCE_DATA_ENTRY *entry,
        void **ptr, ULONG *size)
{
    struct qemu_LdrAccessResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LDRACCESSRESOURCE);
    call.hmod = (ULONG_PTR)hmod;
    call.entry = (ULONG_PTR)entry;
    call.ptr = (ULONG_PTR)ptr;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LdrAccessResource(struct qemu_syscall *call)
{
    struct qemu_LdrAccessResource *c = (struct qemu_LdrAccessResource *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LdrAccessResource(QEMU_G2H(c->hmod), QEMU_G2H(c->entry), QEMU_G2H(c->ptr), QEMU_G2H(c->size));
}

#endif

struct qemu_RtlFindMessage
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t lang;
    uint64_t msg_id;
    uint64_t ret;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlFindMessage(HMODULE hmod, ULONG type, ULONG lang, ULONG msg_id,
        const MESSAGE_RESOURCE_ENTRY **ret)
{
    struct qemu_RtlFindMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDMESSAGE);
    call.hmod = (ULONG_PTR)hmod;
    call.type = type;
    call.lang = lang;
    call.msg_id = msg_id;
    call.ret = (ULONG_PTR)ret;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindMessage(struct qemu_syscall *call)
{
    struct qemu_RtlFindMessage *c = (struct qemu_RtlFindMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindMessage(QEMU_G2H(c->hmod), c->type, c->lang, c->msg_id, QEMU_G2H(c->ret));
}

#endif

struct qemu_RtlFormatMessage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlFormatMessage(LPWSTR Message, UCHAR MaxWidth, BOOLEAN IgnoreInserts, BOOLEAN Ansi,
        BOOLEAN ArgumentIsArray, va_list * Arguments, LPWSTR Buffer, ULONG BufferSize)
{
    struct qemu_RtlFormatMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFORMATMESSAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFormatMessage(struct qemu_syscall *call)
{
    struct qemu_RtlFormatMessage *c = (struct qemu_RtlFormatMessage *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = STATUS_NOT_IMPLEMENTED;
}

#endif
